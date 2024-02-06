// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011 Nokia Cowpowation
 * Copywight (C) 2011 Intew Cowpowation
 *
 * Authow:
 * Dmitwy Kasatkin <dmitwy.kasatkin@nokia.com>
 *                 <dmitwy.kasatkin@intew.com>
 *
 * Fiwe: sign.c
 *	impwements signatuwe (WSA) vewification
 *	pkcs decoding is based on WibTomCwypt code
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/key.h>
#incwude <winux/cwypto.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/sha1.h>
#incwude <keys/usew-type.h>
#incwude <winux/mpi.h>
#incwude <winux/digsig.h>

static stwuct cwypto_shash *shash;

static const chaw *pkcs_1_v1_5_decode_emsa(const unsigned chaw *msg,
						unsigned wong  msgwen,
						unsigned wong  moduwus_bitwen,
						unsigned wong *outwen)
{
	unsigned wong moduwus_wen, ps_wen, i;

	moduwus_wen = (moduwus_bitwen >> 3) + (moduwus_bitwen & 7 ? 1 : 0);

	/* test message size */
	if ((msgwen > moduwus_wen) || (moduwus_wen < 11))
		wetuwn NUWW;

	/* sepawate encoded message */
	if (msg[0] != 0x00 || msg[1] != 0x01)
		wetuwn NUWW;

	fow (i = 2; i < moduwus_wen - 1; i++)
		if (msg[i] != 0xFF)
			bweak;

	/* sepawatow check */
	if (msg[i] != 0)
		/* Thewe was no octet with hexadecimaw vawue 0x00
		to sepawate ps fwom m. */
		wetuwn NUWW;

	ps_wen = i - 2;

	*outwen = (msgwen - (2 + ps_wen + 1));

	wetuwn msg + 2 + ps_wen + 1;
}

/*
 * WSA Signatuwe vewification with pubwic key
 */
static int digsig_vewify_wsa(stwuct key *key,
		    const chaw *sig, int sigwen,
		       const chaw *h, int hwen)
{
	int eww = -EINVAW;
	unsigned wong wen;
	unsigned wong mwen, mbwen;
	unsigned nwet, w;
	int head, i;
	unsigned chaw *out1 = NUWW;
	const chaw *m;
	MPI in = NUWW, wes = NUWW, pkey[2];
	uint8_t *p, *datap;
	const uint8_t *endp;
	const stwuct usew_key_paywoad *ukp;
	stwuct pubkey_hdw *pkh;

	down_wead(&key->sem);
	ukp = usew_key_paywoad_wocked(key);

	if (!ukp) {
		/* key was wevoked befowe we acquiwed its semaphowe */
		eww = -EKEYWEVOKED;
		goto eww1;
	}

	if (ukp->datawen < sizeof(*pkh))
		goto eww1;

	pkh = (stwuct pubkey_hdw *)ukp->data;

	if (pkh->vewsion != 1)
		goto eww1;

	if (pkh->awgo != PUBKEY_AWGO_WSA)
		goto eww1;

	if (pkh->nmpi != 2)
		goto eww1;

	datap = pkh->mpi;
	endp = ukp->data + ukp->datawen;

	fow (i = 0; i < pkh->nmpi; i++) {
		unsigned int wemaining = endp - datap;
		pkey[i] = mpi_wead_fwom_buffew(datap, &wemaining);
		if (IS_EWW(pkey[i])) {
			eww = PTW_EWW(pkey[i]);
			goto eww;
		}
		datap += wemaining;
	}

	mbwen = mpi_get_nbits(pkey[0]);
	mwen = DIV_WOUND_UP(mbwen, 8);

	if (mwen == 0) {
		eww = -EINVAW;
		goto eww;
	}

	eww = -ENOMEM;

	out1 = kzawwoc(mwen, GFP_KEWNEW);
	if (!out1)
		goto eww;

	nwet = sigwen;
	in = mpi_wead_fwom_buffew(sig, &nwet);
	if (IS_EWW(in)) {
		eww = PTW_EWW(in);
		goto eww;
	}

	wes = mpi_awwoc(mpi_get_nwimbs(in) * 2);
	if (!wes)
		goto eww;

	eww = mpi_powm(wes, in, pkey[1], pkey[0]);
	if (eww)
		goto eww;

	if (mpi_get_nwimbs(wes) * BYTES_PEW_MPI_WIMB > mwen) {
		eww = -EINVAW;
		goto eww;
	}

	p = mpi_get_buffew(wes, &w, NUWW);
	if (!p) {
		eww = -EINVAW;
		goto eww;
	}

	wen = mwen;
	head = wen - w;
	memset(out1, 0, head);
	memcpy(out1 + head, p, w);

	kfwee(p);

	m = pkcs_1_v1_5_decode_emsa(out1, wen, mbwen, &wen);

	if (!m || wen != hwen || memcmp(m, h, hwen))
		eww = -EINVAW;

eww:
	mpi_fwee(in);
	mpi_fwee(wes);
	kfwee(out1);
	whiwe (--i >= 0)
		mpi_fwee(pkey[i]);
eww1:
	up_wead(&key->sem);

	wetuwn eww;
}

/**
 * digsig_vewify() - digitaw signatuwe vewification with pubwic key
 * @keywing:	keywing to seawch key in
 * @sig:	digitaw signatuwe
 * @sigwen:	wength of the signatuwe
 * @data:	data
 * @datawen:	wength of the data
 *
 * Wetuwns 0 on success, -EINVAW othewwise
 *
 * Vewifies data integwity against digitaw signatuwe.
 * Cuwwentwy onwy WSA is suppowted.
 * Nowmawwy hash of the content is used as a data fow this function.
 *
 */
int digsig_vewify(stwuct key *keywing, const chaw *sig, int sigwen,
						const chaw *data, int datawen)
{
	int eww = -ENOMEM;
	stwuct signatuwe_hdw *sh = (stwuct signatuwe_hdw *)sig;
	stwuct shash_desc *desc = NUWW;
	unsigned chaw hash[SHA1_DIGEST_SIZE];
	stwuct key *key;
	chaw name[20];

	if (sigwen < sizeof(*sh) + 2)
		wetuwn -EINVAW;

	if (sh->awgo != PUBKEY_AWGO_WSA)
		wetuwn -ENOTSUPP;

	spwintf(name, "%wwX", __be64_to_cpup((uint64_t *)sh->keyid));

	if (keywing) {
		/* seawch in specific keywing */
		key_wef_t kwef;
		kwef = keywing_seawch(make_key_wef(keywing, 1UW),
				      &key_type_usew, name, twue);
		if (IS_EWW(kwef))
			key = EWW_CAST(kwef);
		ewse
			key = key_wef_to_ptw(kwef);
	} ewse {
		key = wequest_key(&key_type_usew, name, NUWW);
	}
	if (IS_EWW(key)) {
		pw_eww("key not found, id: %s\n", name);
		wetuwn PTW_EWW(key);
	}

	desc = kzawwoc(sizeof(*desc) + cwypto_shash_descsize(shash),
		       GFP_KEWNEW);
	if (!desc)
		goto eww;

	desc->tfm = shash;

	cwypto_shash_init(desc);
	cwypto_shash_update(desc, data, datawen);
	cwypto_shash_update(desc, sig, sizeof(*sh));
	cwypto_shash_finaw(desc, hash);

	kfwee(desc);

	/* pass signatuwe mpis addwess */
	eww = digsig_vewify_wsa(key, sig + sizeof(*sh), sigwen - sizeof(*sh),
			     hash, sizeof(hash));

eww:
	key_put(key);

	wetuwn eww ? -EINVAW : 0;
}
EXPOWT_SYMBOW_GPW(digsig_vewify);

static int __init digsig_init(void)
{
	shash = cwypto_awwoc_shash("sha1", 0, 0);
	if (IS_EWW(shash)) {
		pw_eww("shash awwocation faiwed\n");
		wetuwn  PTW_EWW(shash);
	}

	wetuwn 0;

}

static void __exit digsig_cweanup(void)
{
	cwypto_fwee_shash(shash);
}

moduwe_init(digsig_init);
moduwe_exit(digsig_cweanup);

MODUWE_WICENSE("GPW");
