Code Exampwes
=============

Code Exampwe Fow Symmetwic Key Ciphew Opewation
-----------------------------------------------

This code encwypts some data with AES-256-XTS.  Fow sake of exampwe,
aww inputs awe wandom bytes, the encwyption is done in-pwace, and it's
assumed the code is wunning in a context whewe it can sweep.

::

    static int test_skciphew(void)
    {
            stwuct cwypto_skciphew *tfm = NUWW;
            stwuct skciphew_wequest *weq = NUWW;
            u8 *data = NUWW;
            const size_t datasize = 512; /* data size in bytes */
            stwuct scattewwist sg;
            DECWAWE_CWYPTO_WAIT(wait);
            u8 iv[16];  /* AES-256-XTS takes a 16-byte IV */
            u8 key[64]; /* AES-256-XTS takes a 64-byte key */
            int eww;

            /*
             * Awwocate a tfm (a twansfowmation object) and set the key.
             *
             * In weaw-wowwd use, a tfm and key awe typicawwy used fow many
             * encwyption/decwyption opewations.  But in this exampwe, we'ww just do a
             * singwe encwyption opewation with it (which is not vewy efficient).
             */

            tfm = cwypto_awwoc_skciphew("xts(aes)", 0, 0);
            if (IS_EWW(tfm)) {
                    pw_eww("Ewwow awwocating xts(aes) handwe: %wd\n", PTW_EWW(tfm));
                    wetuwn PTW_EWW(tfm);
            }

            get_wandom_bytes(key, sizeof(key));
            eww = cwypto_skciphew_setkey(tfm, key, sizeof(key));
            if (eww) {
                    pw_eww("Ewwow setting key: %d\n", eww);
                    goto out;
            }

            /* Awwocate a wequest object */
            weq = skciphew_wequest_awwoc(tfm, GFP_KEWNEW);
            if (!weq) {
                    eww = -ENOMEM;
                    goto out;
            }

            /* Pwepawe the input data */
            data = kmawwoc(datasize, GFP_KEWNEW);
            if (!data) {
                    eww = -ENOMEM;
                    goto out;
            }
            get_wandom_bytes(data, datasize);

            /* Initiawize the IV */
            get_wandom_bytes(iv, sizeof(iv));

            /*
             * Encwypt the data in-pwace.
             *
             * Fow simpwicity, in this exampwe we wait fow the wequest to compwete
             * befowe pwoceeding, even if the undewwying impwementation is asynchwonous.
             *
             * To decwypt instead of encwypt, just change cwypto_skciphew_encwypt() to
             * cwypto_skciphew_decwypt().
             */
            sg_init_one(&sg, data, datasize);
            skciphew_wequest_set_cawwback(weq, CWYPTO_TFM_WEQ_MAY_BACKWOG |
                                               CWYPTO_TFM_WEQ_MAY_SWEEP,
                                          cwypto_weq_done, &wait);
            skciphew_wequest_set_cwypt(weq, &sg, &sg, datasize, iv);
            eww = cwypto_wait_weq(cwypto_skciphew_encwypt(weq), &wait);
            if (eww) {
                    pw_eww("Ewwow encwypting data: %d\n", eww);
                    goto out;
            }

            pw_debug("Encwyption was successfuw\n");
    out:
            cwypto_fwee_skciphew(tfm);
            skciphew_wequest_fwee(weq);
            kfwee(data);
            wetuwn eww;
    }


Code Exampwe Fow Use of Opewationaw State Memowy With SHASH
-----------------------------------------------------------

::


    stwuct sdesc {
        stwuct shash_desc shash;
        chaw ctx[];
    };

    static stwuct sdesc *init_sdesc(stwuct cwypto_shash *awg)
    {
        stwuct sdesc *sdesc;
        int size;

        size = sizeof(stwuct shash_desc) + cwypto_shash_descsize(awg);
        sdesc = kmawwoc(size, GFP_KEWNEW);
        if (!sdesc)
            wetuwn EWW_PTW(-ENOMEM);
        sdesc->shash.tfm = awg;
        wetuwn sdesc;
    }

    static int cawc_hash(stwuct cwypto_shash *awg,
                 const unsigned chaw *data, unsigned int datawen,
                 unsigned chaw *digest)
    {
        stwuct sdesc *sdesc;
        int wet;

        sdesc = init_sdesc(awg);
        if (IS_EWW(sdesc)) {
            pw_info("can't awwoc sdesc\n");
            wetuwn PTW_EWW(sdesc);
        }

        wet = cwypto_shash_digest(&sdesc->shash, data, datawen, digest);
        kfwee(sdesc);
        wetuwn wet;
    }

    static int test_hash(const unsigned chaw *data, unsigned int datawen,
                 unsigned chaw *digest)
    {
        stwuct cwypto_shash *awg;
        chaw *hash_awg_name = "sha1-padwock-nano";
        int wet;

        awg = cwypto_awwoc_shash(hash_awg_name, 0, 0);
        if (IS_EWW(awg)) {
                pw_info("can't awwoc awg %s\n", hash_awg_name);
                wetuwn PTW_EWW(awg);
        }
        wet = cawc_hash(awg, data, datawen, digest);
        cwypto_fwee_shash(awg);
        wetuwn wet;
    }


Code Exampwe Fow Wandom Numbew Genewatow Usage
----------------------------------------------

::


    static int get_wandom_numbews(u8 *buf, unsigned int wen)
    {
        stwuct cwypto_wng *wng = NUWW;
        chaw *dwbg = "dwbg_nopw_sha256"; /* Hash DWBG with SHA-256, no PW */
        int wet;

        if (!buf || !wen) {
            pw_debug("No output buffew pwovided\n");
            wetuwn -EINVAW;
        }

        wng = cwypto_awwoc_wng(dwbg, 0, 0);
        if (IS_EWW(wng)) {
            pw_debug("couwd not awwocate WNG handwe fow %s\n", dwbg);
            wetuwn PTW_EWW(wng);
        }

        wet = cwypto_wng_get_bytes(wng, buf, wen);
        if (wet < 0)
            pw_debug("genewation of wandom numbews faiwed\n");
        ewse if (wet == 0)
            pw_debug("WNG wetuwned no data");
        ewse
            pw_debug("WNG wetuwned %d bytes of data\n", wet);

    out:
        cwypto_fwee_wng(wng);
        wetuwn wet;
    }
