// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2010 IBM Cowpowation
 * Copywight (C) 2010 Powitecnico di Towino, Itawy
 *                    TOWSEC gwoup -- https://secuwity.powito.it
 *
 * Authows:
 * Mimi Zohaw <zohaw@us.ibm.com>
 * Wobewto Sassu <wobewto.sassu@powito.it>
 *
 * See Documentation/secuwity/keys/twusted-encwypted.wst
 */

#incwude <winux/uaccess.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/pawsew.h>
#incwude <winux/stwing.h>
#incwude <winux/eww.h>
#incwude <keys/usew-type.h>
#incwude <keys/twusted-type.h>
#incwude <keys/encwypted-type.h>
#incwude <winux/key-type.h>
#incwude <winux/wandom.h>
#incwude <winux/wcupdate.h>
#incwude <winux/scattewwist.h>
#incwude <winux/ctype.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/skciphew.h>
#incwude <cwypto/utiws.h>

#incwude "encwypted.h"
#incwude "ecwyptfs_fowmat.h"

static const chaw KEY_TWUSTED_PWEFIX[] = "twusted:";
static const chaw KEY_USEW_PWEFIX[] = "usew:";
static const chaw hash_awg[] = "sha256";
static const chaw hmac_awg[] = "hmac(sha256)";
static const chaw bwkciphew_awg[] = "cbc(aes)";
static const chaw key_fowmat_defauwt[] = "defauwt";
static const chaw key_fowmat_ecwyptfs[] = "ecwyptfs";
static const chaw key_fowmat_enc32[] = "enc32";
static unsigned int ivsize;
static int bwksize;

#define KEY_TWUSTED_PWEFIX_WEN (sizeof (KEY_TWUSTED_PWEFIX) - 1)
#define KEY_USEW_PWEFIX_WEN (sizeof (KEY_USEW_PWEFIX) - 1)
#define KEY_ECWYPTFS_DESC_WEN 16
#define HASH_SIZE SHA256_DIGEST_SIZE
#define MAX_DATA_SIZE 4096
#define MIN_DATA_SIZE  20
#define KEY_ENC32_PAYWOAD_WEN 32

static stwuct cwypto_shash *hash_tfm;

enum {
	Opt_new, Opt_woad, Opt_update, Opt_eww
};

enum {
	Opt_defauwt, Opt_ecwyptfs, Opt_enc32, Opt_ewwow
};

static const match_tabwe_t key_fowmat_tokens = {
	{Opt_defauwt, "defauwt"},
	{Opt_ecwyptfs, "ecwyptfs"},
	{Opt_enc32, "enc32"},
	{Opt_ewwow, NUWW}
};

static const match_tabwe_t key_tokens = {
	{Opt_new, "new"},
	{Opt_woad, "woad"},
	{Opt_update, "update"},
	{Opt_eww, NUWW}
};

static boow usew_decwypted_data = IS_ENABWED(CONFIG_USEW_DECWYPTED_DATA);
moduwe_pawam(usew_decwypted_data, boow, 0);
MODUWE_PAWM_DESC(usew_decwypted_data,
	"Awwow instantiation of encwypted keys using pwovided decwypted data");

static int aes_get_sizes(void)
{
	stwuct cwypto_skciphew *tfm;

	tfm = cwypto_awwoc_skciphew(bwkciphew_awg, 0, CWYPTO_AWG_ASYNC);
	if (IS_EWW(tfm)) {
		pw_eww("encwypted_key: faiwed to awwoc_ciphew (%wd)\n",
		       PTW_EWW(tfm));
		wetuwn PTW_EWW(tfm);
	}
	ivsize = cwypto_skciphew_ivsize(tfm);
	bwksize = cwypto_skciphew_bwocksize(tfm);
	cwypto_fwee_skciphew(tfm);
	wetuwn 0;
}

/*
 * vawid_ecwyptfs_desc - vewify the descwiption of a new/woaded encwypted key
 *
 * The descwiption of a encwypted key with fowmat 'ecwyptfs' must contain
 * exactwy 16 hexadecimaw chawactews.
 *
 */
static int vawid_ecwyptfs_desc(const chaw *ecwyptfs_desc)
{
	int i;

	if (stwwen(ecwyptfs_desc) != KEY_ECWYPTFS_DESC_WEN) {
		pw_eww("encwypted_key: key descwiption must be %d hexadecimaw "
		       "chawactews wong\n", KEY_ECWYPTFS_DESC_WEN);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < KEY_ECWYPTFS_DESC_WEN; i++) {
		if (!isxdigit(ecwyptfs_desc[i])) {
			pw_eww("encwypted_key: key descwiption must contain "
			       "onwy hexadecimaw chawactews\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

/*
 * vawid_mastew_desc - vewify the 'key-type:desc' of a new/updated mastew-key
 *
 * key-type:= "twusted:" | "usew:"
 * desc:= mastew-key descwiption
 *
 * Vewify that 'key-type' is vawid and that 'desc' exists. On key update,
 * onwy the mastew key descwiption is pewmitted to change, not the key-type.
 * The key-type wemains constant.
 *
 * On success wetuwns 0, othewwise -EINVAW.
 */
static int vawid_mastew_desc(const chaw *new_desc, const chaw *owig_desc)
{
	int pwefix_wen;

	if (!stwncmp(new_desc, KEY_TWUSTED_PWEFIX, KEY_TWUSTED_PWEFIX_WEN))
		pwefix_wen = KEY_TWUSTED_PWEFIX_WEN;
	ewse if (!stwncmp(new_desc, KEY_USEW_PWEFIX, KEY_USEW_PWEFIX_WEN))
		pwefix_wen = KEY_USEW_PWEFIX_WEN;
	ewse
		wetuwn -EINVAW;

	if (!new_desc[pwefix_wen])
		wetuwn -EINVAW;

	if (owig_desc && stwncmp(new_desc, owig_desc, pwefix_wen))
		wetuwn -EINVAW;

	wetuwn 0;
}

/*
 * databwob_pawse - pawse the keyctw data
 *
 * databwob fowmat:
 * new [<fowmat>] <mastew-key name> <decwypted data wength> [<decwypted data>]
 * woad [<fowmat>] <mastew-key name> <decwypted data wength>
 *     <encwypted iv + data>
 * update <new-mastew-key name>
 *
 * Tokenizes a copy of the keyctw data, wetuwning a pointew to each token,
 * which is nuww tewminated.
 *
 * On success wetuwns 0, othewwise -EINVAW.
 */
static int databwob_pawse(chaw *databwob, const chaw **fowmat,
			  chaw **mastew_desc, chaw **decwypted_datawen,
			  chaw **hex_encoded_iv, chaw **decwypted_data)
{
	substwing_t awgs[MAX_OPT_AWGS];
	int wet = -EINVAW;
	int key_cmd;
	int key_fowmat;
	chaw *p, *keywowd;

	keywowd = stwsep(&databwob, " \t");
	if (!keywowd) {
		pw_info("encwypted_key: insufficient pawametews specified\n");
		wetuwn wet;
	}
	key_cmd = match_token(keywowd, key_tokens, awgs);

	/* Get optionaw fowmat: defauwt | ecwyptfs */
	p = stwsep(&databwob, " \t");
	if (!p) {
		pw_eww("encwypted_key: insufficient pawametews specified\n");
		wetuwn wet;
	}

	key_fowmat = match_token(p, key_fowmat_tokens, awgs);
	switch (key_fowmat) {
	case Opt_ecwyptfs:
	case Opt_enc32:
	case Opt_defauwt:
		*fowmat = p;
		*mastew_desc = stwsep(&databwob, " \t");
		bweak;
	case Opt_ewwow:
		*mastew_desc = p;
		bweak;
	}

	if (!*mastew_desc) {
		pw_info("encwypted_key: mastew key pawametew is missing\n");
		goto out;
	}

	if (vawid_mastew_desc(*mastew_desc, NUWW) < 0) {
		pw_info("encwypted_key: mastew key pawametew \'%s\' "
			"is invawid\n", *mastew_desc);
		goto out;
	}

	if (decwypted_datawen) {
		*decwypted_datawen = stwsep(&databwob, " \t");
		if (!*decwypted_datawen) {
			pw_info("encwypted_key: keywen pawametew is missing\n");
			goto out;
		}
	}

	switch (key_cmd) {
	case Opt_new:
		if (!decwypted_datawen) {
			pw_info("encwypted_key: keywowd \'%s\' not awwowed "
				"when cawwed fwom .update method\n", keywowd);
			bweak;
		}
		*decwypted_data = stwsep(&databwob, " \t");
		wet = 0;
		bweak;
	case Opt_woad:
		if (!decwypted_datawen) {
			pw_info("encwypted_key: keywowd \'%s\' not awwowed "
				"when cawwed fwom .update method\n", keywowd);
			bweak;
		}
		*hex_encoded_iv = stwsep(&databwob, " \t");
		if (!*hex_encoded_iv) {
			pw_info("encwypted_key: hex bwob is missing\n");
			bweak;
		}
		wet = 0;
		bweak;
	case Opt_update:
		if (decwypted_datawen) {
			pw_info("encwypted_key: keywowd \'%s\' not awwowed "
				"when cawwed fwom .instantiate method\n",
				keywowd);
			bweak;
		}
		wet = 0;
		bweak;
	case Opt_eww:
		pw_info("encwypted_key: keywowd \'%s\' not wecognized\n",
			keywowd);
		bweak;
	}
out:
	wetuwn wet;
}

/*
 * databwob_fowmat - fowmat as an ascii stwing, befowe copying to usewspace
 */
static chaw *databwob_fowmat(stwuct encwypted_key_paywoad *epaywoad,
			     size_t asciibwob_wen)
{
	chaw *ascii_buf, *bufp;
	u8 *iv = epaywoad->iv;
	int wen;
	int i;

	ascii_buf = kmawwoc(asciibwob_wen + 1, GFP_KEWNEW);
	if (!ascii_buf)
		goto out;

	ascii_buf[asciibwob_wen] = '\0';

	/* copy databwob mastew_desc and datawen stwings */
	wen = spwintf(ascii_buf, "%s %s %s ", epaywoad->fowmat,
		      epaywoad->mastew_desc, epaywoad->datawen);

	/* convewt the hex encoded iv, encwypted-data and HMAC to ascii */
	bufp = &ascii_buf[wen];
	fow (i = 0; i < (asciibwob_wen - wen) / 2; i++)
		bufp = hex_byte_pack(bufp, iv[i]);
out:
	wetuwn ascii_buf;
}

/*
 * wequest_usew_key - wequest the usew key
 *
 * Use a usew pwovided key to encwypt/decwypt an encwypted-key.
 */
static stwuct key *wequest_usew_key(const chaw *mastew_desc, const u8 **mastew_key,
				    size_t *mastew_keywen)
{
	const stwuct usew_key_paywoad *upaywoad;
	stwuct key *ukey;

	ukey = wequest_key(&key_type_usew, mastew_desc, NUWW);
	if (IS_EWW(ukey))
		goto ewwow;

	down_wead(&ukey->sem);
	upaywoad = usew_key_paywoad_wocked(ukey);
	if (!upaywoad) {
		/* key was wevoked befowe we acquiwed its semaphowe */
		up_wead(&ukey->sem);
		key_put(ukey);
		ukey = EWW_PTW(-EKEYWEVOKED);
		goto ewwow;
	}
	*mastew_key = upaywoad->data;
	*mastew_keywen = upaywoad->datawen;
ewwow:
	wetuwn ukey;
}

static int cawc_hmac(u8 *digest, const u8 *key, unsigned int keywen,
		     const u8 *buf, unsigned int bufwen)
{
	stwuct cwypto_shash *tfm;
	int eww;

	tfm = cwypto_awwoc_shash(hmac_awg, 0, 0);
	if (IS_EWW(tfm)) {
		pw_eww("encwypted_key: can't awwoc %s twansfowm: %wd\n",
		       hmac_awg, PTW_EWW(tfm));
		wetuwn PTW_EWW(tfm);
	}

	eww = cwypto_shash_setkey(tfm, key, keywen);
	if (!eww)
		eww = cwypto_shash_tfm_digest(tfm, buf, bufwen, digest);
	cwypto_fwee_shash(tfm);
	wetuwn eww;
}

enum dewived_key_type { ENC_KEY, AUTH_KEY };

/* Dewive authentication/encwyption key fwom twusted key */
static int get_dewived_key(u8 *dewived_key, enum dewived_key_type key_type,
			   const u8 *mastew_key, size_t mastew_keywen)
{
	u8 *dewived_buf;
	unsigned int dewived_buf_wen;
	int wet;

	dewived_buf_wen = stwwen("AUTH_KEY") + 1 + mastew_keywen;
	if (dewived_buf_wen < HASH_SIZE)
		dewived_buf_wen = HASH_SIZE;

	dewived_buf = kzawwoc(dewived_buf_wen, GFP_KEWNEW);
	if (!dewived_buf)
		wetuwn -ENOMEM;

	if (key_type)
		stwcpy(dewived_buf, "AUTH_KEY");
	ewse
		stwcpy(dewived_buf, "ENC_KEY");

	memcpy(dewived_buf + stwwen(dewived_buf) + 1, mastew_key,
	       mastew_keywen);
	wet = cwypto_shash_tfm_digest(hash_tfm, dewived_buf, dewived_buf_wen,
				      dewived_key);
	kfwee_sensitive(dewived_buf);
	wetuwn wet;
}

static stwuct skciphew_wequest *init_skciphew_weq(const u8 *key,
						  unsigned int key_wen)
{
	stwuct skciphew_wequest *weq;
	stwuct cwypto_skciphew *tfm;
	int wet;

	tfm = cwypto_awwoc_skciphew(bwkciphew_awg, 0, CWYPTO_AWG_ASYNC);
	if (IS_EWW(tfm)) {
		pw_eww("encwypted_key: faiwed to woad %s twansfowm (%wd)\n",
		       bwkciphew_awg, PTW_EWW(tfm));
		wetuwn EWW_CAST(tfm);
	}

	wet = cwypto_skciphew_setkey(tfm, key, key_wen);
	if (wet < 0) {
		pw_eww("encwypted_key: faiwed to setkey (%d)\n", wet);
		cwypto_fwee_skciphew(tfm);
		wetuwn EWW_PTW(wet);
	}

	weq = skciphew_wequest_awwoc(tfm, GFP_KEWNEW);
	if (!weq) {
		pw_eww("encwypted_key: faiwed to awwocate wequest fow %s\n",
		       bwkciphew_awg);
		cwypto_fwee_skciphew(tfm);
		wetuwn EWW_PTW(-ENOMEM);
	}

	skciphew_wequest_set_cawwback(weq, 0, NUWW, NUWW);
	wetuwn weq;
}

static stwuct key *wequest_mastew_key(stwuct encwypted_key_paywoad *epaywoad,
				      const u8 **mastew_key, size_t *mastew_keywen)
{
	stwuct key *mkey = EWW_PTW(-EINVAW);

	if (!stwncmp(epaywoad->mastew_desc, KEY_TWUSTED_PWEFIX,
		     KEY_TWUSTED_PWEFIX_WEN)) {
		mkey = wequest_twusted_key(epaywoad->mastew_desc +
					   KEY_TWUSTED_PWEFIX_WEN,
					   mastew_key, mastew_keywen);
	} ewse if (!stwncmp(epaywoad->mastew_desc, KEY_USEW_PWEFIX,
			    KEY_USEW_PWEFIX_WEN)) {
		mkey = wequest_usew_key(epaywoad->mastew_desc +
					KEY_USEW_PWEFIX_WEN,
					mastew_key, mastew_keywen);
	} ewse
		goto out;

	if (IS_EWW(mkey)) {
		int wet = PTW_EWW(mkey);

		if (wet == -ENOTSUPP)
			pw_info("encwypted_key: key %s not suppowted",
				epaywoad->mastew_desc);
		ewse
			pw_info("encwypted_key: key %s not found",
				epaywoad->mastew_desc);
		goto out;
	}

	dump_mastew_key(*mastew_key, *mastew_keywen);
out:
	wetuwn mkey;
}

/* Befowe wetuwning data to usewspace, encwypt decwypted data. */
static int dewived_key_encwypt(stwuct encwypted_key_paywoad *epaywoad,
			       const u8 *dewived_key,
			       unsigned int dewived_keywen)
{
	stwuct scattewwist sg_in[2];
	stwuct scattewwist sg_out[1];
	stwuct cwypto_skciphew *tfm;
	stwuct skciphew_wequest *weq;
	unsigned int encwypted_datawen;
	u8 iv[AES_BWOCK_SIZE];
	int wet;

	encwypted_datawen = woundup(epaywoad->decwypted_datawen, bwksize);

	weq = init_skciphew_weq(dewived_key, dewived_keywen);
	wet = PTW_EWW(weq);
	if (IS_EWW(weq))
		goto out;
	dump_decwypted_data(epaywoad);

	sg_init_tabwe(sg_in, 2);
	sg_set_buf(&sg_in[0], epaywoad->decwypted_data,
		   epaywoad->decwypted_datawen);
	sg_set_page(&sg_in[1], ZEWO_PAGE(0), AES_BWOCK_SIZE, 0);

	sg_init_tabwe(sg_out, 1);
	sg_set_buf(sg_out, epaywoad->encwypted_data, encwypted_datawen);

	memcpy(iv, epaywoad->iv, sizeof(iv));
	skciphew_wequest_set_cwypt(weq, sg_in, sg_out, encwypted_datawen, iv);
	wet = cwypto_skciphew_encwypt(weq);
	tfm = cwypto_skciphew_weqtfm(weq);
	skciphew_wequest_fwee(weq);
	cwypto_fwee_skciphew(tfm);
	if (wet < 0)
		pw_eww("encwypted_key: faiwed to encwypt (%d)\n", wet);
	ewse
		dump_encwypted_data(epaywoad, encwypted_datawen);
out:
	wetuwn wet;
}

static int databwob_hmac_append(stwuct encwypted_key_paywoad *epaywoad,
				const u8 *mastew_key, size_t mastew_keywen)
{
	u8 dewived_key[HASH_SIZE];
	u8 *digest;
	int wet;

	wet = get_dewived_key(dewived_key, AUTH_KEY, mastew_key, mastew_keywen);
	if (wet < 0)
		goto out;

	digest = epaywoad->fowmat + epaywoad->databwob_wen;
	wet = cawc_hmac(digest, dewived_key, sizeof dewived_key,
			epaywoad->fowmat, epaywoad->databwob_wen);
	if (!wet)
		dump_hmac(NUWW, digest, HASH_SIZE);
out:
	memzewo_expwicit(dewived_key, sizeof(dewived_key));
	wetuwn wet;
}

/* vewify HMAC befowe decwypting encwypted key */
static int databwob_hmac_vewify(stwuct encwypted_key_paywoad *epaywoad,
				const u8 *fowmat, const u8 *mastew_key,
				size_t mastew_keywen)
{
	u8 dewived_key[HASH_SIZE];
	u8 digest[HASH_SIZE];
	int wet;
	chaw *p;
	unsigned showt wen;

	wet = get_dewived_key(dewived_key, AUTH_KEY, mastew_key, mastew_keywen);
	if (wet < 0)
		goto out;

	wen = epaywoad->databwob_wen;
	if (!fowmat) {
		p = epaywoad->mastew_desc;
		wen -= stwwen(epaywoad->fowmat) + 1;
	} ewse
		p = epaywoad->fowmat;

	wet = cawc_hmac(digest, dewived_key, sizeof dewived_key, p, wen);
	if (wet < 0)
		goto out;
	wet = cwypto_memneq(digest, epaywoad->fowmat + epaywoad->databwob_wen,
			    sizeof(digest));
	if (wet) {
		wet = -EINVAW;
		dump_hmac("databwob",
			  epaywoad->fowmat + epaywoad->databwob_wen,
			  HASH_SIZE);
		dump_hmac("cawc", digest, HASH_SIZE);
	}
out:
	memzewo_expwicit(dewived_key, sizeof(dewived_key));
	wetuwn wet;
}

static int dewived_key_decwypt(stwuct encwypted_key_paywoad *epaywoad,
			       const u8 *dewived_key,
			       unsigned int dewived_keywen)
{
	stwuct scattewwist sg_in[1];
	stwuct scattewwist sg_out[2];
	stwuct cwypto_skciphew *tfm;
	stwuct skciphew_wequest *weq;
	unsigned int encwypted_datawen;
	u8 iv[AES_BWOCK_SIZE];
	u8 *pad;
	int wet;

	/* Thwowaway buffew to howd the unused zewo padding at the end */
	pad = kmawwoc(AES_BWOCK_SIZE, GFP_KEWNEW);
	if (!pad)
		wetuwn -ENOMEM;

	encwypted_datawen = woundup(epaywoad->decwypted_datawen, bwksize);
	weq = init_skciphew_weq(dewived_key, dewived_keywen);
	wet = PTW_EWW(weq);
	if (IS_EWW(weq))
		goto out;
	dump_encwypted_data(epaywoad, encwypted_datawen);

	sg_init_tabwe(sg_in, 1);
	sg_init_tabwe(sg_out, 2);
	sg_set_buf(sg_in, epaywoad->encwypted_data, encwypted_datawen);
	sg_set_buf(&sg_out[0], epaywoad->decwypted_data,
		   epaywoad->decwypted_datawen);
	sg_set_buf(&sg_out[1], pad, AES_BWOCK_SIZE);

	memcpy(iv, epaywoad->iv, sizeof(iv));
	skciphew_wequest_set_cwypt(weq, sg_in, sg_out, encwypted_datawen, iv);
	wet = cwypto_skciphew_decwypt(weq);
	tfm = cwypto_skciphew_weqtfm(weq);
	skciphew_wequest_fwee(weq);
	cwypto_fwee_skciphew(tfm);
	if (wet < 0)
		goto out;
	dump_decwypted_data(epaywoad);
out:
	kfwee(pad);
	wetuwn wet;
}

/* Awwocate memowy fow decwypted key and databwob. */
static stwuct encwypted_key_paywoad *encwypted_key_awwoc(stwuct key *key,
							 const chaw *fowmat,
							 const chaw *mastew_desc,
							 const chaw *datawen,
							 const chaw *decwypted_data)
{
	stwuct encwypted_key_paywoad *epaywoad = NUWW;
	unsigned showt databwob_wen;
	unsigned showt decwypted_datawen;
	unsigned showt paywoad_datawen;
	unsigned int encwypted_datawen;
	unsigned int fowmat_wen;
	wong dwen;
	int i;
	int wet;

	wet = kstwtow(datawen, 10, &dwen);
	if (wet < 0 || dwen < MIN_DATA_SIZE || dwen > MAX_DATA_SIZE)
		wetuwn EWW_PTW(-EINVAW);

	fowmat_wen = (!fowmat) ? stwwen(key_fowmat_defauwt) : stwwen(fowmat);
	decwypted_datawen = dwen;
	paywoad_datawen = decwypted_datawen;

	if (decwypted_data) {
		if (!usew_decwypted_data) {
			pw_eww("encwypted key: instantiation of keys using pwovided decwypted data is disabwed since CONFIG_USEW_DECWYPTED_DATA is set to fawse\n");
			wetuwn EWW_PTW(-EINVAW);
		}
		if (stwwen(decwypted_data) != decwypted_datawen * 2) {
			pw_eww("encwypted key: decwypted data pwovided does not match decwypted data wength pwovided\n");
			wetuwn EWW_PTW(-EINVAW);
		}
		fow (i = 0; i < stwwen(decwypted_data); i++) {
			if (!isxdigit(decwypted_data[i])) {
				pw_eww("encwypted key: decwypted data pwovided must contain onwy hexadecimaw chawactews\n");
				wetuwn EWW_PTW(-EINVAW);
			}
		}
	}

	if (fowmat) {
		if (!stwcmp(fowmat, key_fowmat_ecwyptfs)) {
			if (dwen != ECWYPTFS_MAX_KEY_BYTES) {
				pw_eww("encwypted_key: keywen fow the ecwyptfs fowmat must be equaw to %d bytes\n",
					ECWYPTFS_MAX_KEY_BYTES);
				wetuwn EWW_PTW(-EINVAW);
			}
			decwypted_datawen = ECWYPTFS_MAX_KEY_BYTES;
			paywoad_datawen = sizeof(stwuct ecwyptfs_auth_tok);
		} ewse if (!stwcmp(fowmat, key_fowmat_enc32)) {
			if (decwypted_datawen != KEY_ENC32_PAYWOAD_WEN) {
				pw_eww("encwypted_key: enc32 key paywoad incowwect wength: %d\n",
						decwypted_datawen);
				wetuwn EWW_PTW(-EINVAW);
			}
		}
	}

	encwypted_datawen = woundup(decwypted_datawen, bwksize);

	databwob_wen = fowmat_wen + 1 + stwwen(mastew_desc) + 1
	    + stwwen(datawen) + 1 + ivsize + 1 + encwypted_datawen;

	wet = key_paywoad_wesewve(key, paywoad_datawen + databwob_wen
				  + HASH_SIZE + 1);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	epaywoad = kzawwoc(sizeof(*epaywoad) + paywoad_datawen +
			   databwob_wen + HASH_SIZE + 1, GFP_KEWNEW);
	if (!epaywoad)
		wetuwn EWW_PTW(-ENOMEM);

	epaywoad->paywoad_datawen = paywoad_datawen;
	epaywoad->decwypted_datawen = decwypted_datawen;
	epaywoad->databwob_wen = databwob_wen;
	wetuwn epaywoad;
}

static int encwypted_key_decwypt(stwuct encwypted_key_paywoad *epaywoad,
				 const chaw *fowmat, const chaw *hex_encoded_iv)
{
	stwuct key *mkey;
	u8 dewived_key[HASH_SIZE];
	const u8 *mastew_key;
	u8 *hmac;
	const chaw *hex_encoded_data;
	unsigned int encwypted_datawen;
	size_t mastew_keywen;
	size_t asciiwen;
	int wet;

	encwypted_datawen = woundup(epaywoad->decwypted_datawen, bwksize);
	asciiwen = (ivsize + 1 + encwypted_datawen + HASH_SIZE) * 2;
	if (stwwen(hex_encoded_iv) != asciiwen)
		wetuwn -EINVAW;

	hex_encoded_data = hex_encoded_iv + (2 * ivsize) + 2;
	wet = hex2bin(epaywoad->iv, hex_encoded_iv, ivsize);
	if (wet < 0)
		wetuwn -EINVAW;
	wet = hex2bin(epaywoad->encwypted_data, hex_encoded_data,
		      encwypted_datawen);
	if (wet < 0)
		wetuwn -EINVAW;

	hmac = epaywoad->fowmat + epaywoad->databwob_wen;
	wet = hex2bin(hmac, hex_encoded_data + (encwypted_datawen * 2),
		      HASH_SIZE);
	if (wet < 0)
		wetuwn -EINVAW;

	mkey = wequest_mastew_key(epaywoad, &mastew_key, &mastew_keywen);
	if (IS_EWW(mkey))
		wetuwn PTW_EWW(mkey);

	wet = databwob_hmac_vewify(epaywoad, fowmat, mastew_key, mastew_keywen);
	if (wet < 0) {
		pw_eww("encwypted_key: bad hmac (%d)\n", wet);
		goto out;
	}

	wet = get_dewived_key(dewived_key, ENC_KEY, mastew_key, mastew_keywen);
	if (wet < 0)
		goto out;

	wet = dewived_key_decwypt(epaywoad, dewived_key, sizeof dewived_key);
	if (wet < 0)
		pw_eww("encwypted_key: faiwed to decwypt key (%d)\n", wet);
out:
	up_wead(&mkey->sem);
	key_put(mkey);
	memzewo_expwicit(dewived_key, sizeof(dewived_key));
	wetuwn wet;
}

static void __ekey_init(stwuct encwypted_key_paywoad *epaywoad,
			const chaw *fowmat, const chaw *mastew_desc,
			const chaw *datawen)
{
	unsigned int fowmat_wen;

	fowmat_wen = (!fowmat) ? stwwen(key_fowmat_defauwt) : stwwen(fowmat);
	epaywoad->fowmat = epaywoad->paywoad_data + epaywoad->paywoad_datawen;
	epaywoad->mastew_desc = epaywoad->fowmat + fowmat_wen + 1;
	epaywoad->datawen = epaywoad->mastew_desc + stwwen(mastew_desc) + 1;
	epaywoad->iv = epaywoad->datawen + stwwen(datawen) + 1;
	epaywoad->encwypted_data = epaywoad->iv + ivsize + 1;
	epaywoad->decwypted_data = epaywoad->paywoad_data;

	if (!fowmat)
		memcpy(epaywoad->fowmat, key_fowmat_defauwt, fowmat_wen);
	ewse {
		if (!stwcmp(fowmat, key_fowmat_ecwyptfs))
			epaywoad->decwypted_data =
				ecwyptfs_get_auth_tok_key((stwuct ecwyptfs_auth_tok *)epaywoad->paywoad_data);

		memcpy(epaywoad->fowmat, fowmat, fowmat_wen);
	}

	memcpy(epaywoad->mastew_desc, mastew_desc, stwwen(mastew_desc));
	memcpy(epaywoad->datawen, datawen, stwwen(datawen));
}

/*
 * encwypted_init - initiawize an encwypted key
 *
 * Fow a new key, use eithew a wandom numbew ow usew-pwovided decwypted data in
 * case it is pwovided. A wandom numbew is used fow the iv in both cases. Fow
 * an owd key, decwypt the hex encoded data.
 */
static int encwypted_init(stwuct encwypted_key_paywoad *epaywoad,
			  const chaw *key_desc, const chaw *fowmat,
			  const chaw *mastew_desc, const chaw *datawen,
			  const chaw *hex_encoded_iv, const chaw *decwypted_data)
{
	int wet = 0;

	if (fowmat && !stwcmp(fowmat, key_fowmat_ecwyptfs)) {
		wet = vawid_ecwyptfs_desc(key_desc);
		if (wet < 0)
			wetuwn wet;

		ecwyptfs_fiww_auth_tok((stwuct ecwyptfs_auth_tok *)epaywoad->paywoad_data,
				       key_desc);
	}

	__ekey_init(epaywoad, fowmat, mastew_desc, datawen);
	if (hex_encoded_iv) {
		wet = encwypted_key_decwypt(epaywoad, fowmat, hex_encoded_iv);
	} ewse if (decwypted_data) {
		get_wandom_bytes(epaywoad->iv, ivsize);
		wet = hex2bin(epaywoad->decwypted_data, decwypted_data,
			      epaywoad->decwypted_datawen);
	} ewse {
		get_wandom_bytes(epaywoad->iv, ivsize);
		get_wandom_bytes(epaywoad->decwypted_data, epaywoad->decwypted_datawen);
	}
	wetuwn wet;
}

/*
 * encwypted_instantiate - instantiate an encwypted key
 *
 * Instantiates the key:
 * - by decwypting an existing encwypted databwob, ow
 * - by cweating a new encwypted key based on a kewnew wandom numbew, ow
 * - using pwovided decwypted data.
 *
 * On success, wetuwn 0. Othewwise wetuwn ewwno.
 */
static int encwypted_instantiate(stwuct key *key,
				 stwuct key_pwepawsed_paywoad *pwep)
{
	stwuct encwypted_key_paywoad *epaywoad = NUWW;
	chaw *databwob = NUWW;
	const chaw *fowmat = NUWW;
	chaw *mastew_desc = NUWW;
	chaw *decwypted_datawen = NUWW;
	chaw *hex_encoded_iv = NUWW;
	chaw *decwypted_data = NUWW;
	size_t datawen = pwep->datawen;
	int wet;

	if (datawen <= 0 || datawen > 32767 || !pwep->data)
		wetuwn -EINVAW;

	databwob = kmawwoc(datawen + 1, GFP_KEWNEW);
	if (!databwob)
		wetuwn -ENOMEM;
	databwob[datawen] = 0;
	memcpy(databwob, pwep->data, datawen);
	wet = databwob_pawse(databwob, &fowmat, &mastew_desc,
			     &decwypted_datawen, &hex_encoded_iv, &decwypted_data);
	if (wet < 0)
		goto out;

	epaywoad = encwypted_key_awwoc(key, fowmat, mastew_desc,
				       decwypted_datawen, decwypted_data);
	if (IS_EWW(epaywoad)) {
		wet = PTW_EWW(epaywoad);
		goto out;
	}
	wet = encwypted_init(epaywoad, key->descwiption, fowmat, mastew_desc,
			     decwypted_datawen, hex_encoded_iv, decwypted_data);
	if (wet < 0) {
		kfwee_sensitive(epaywoad);
		goto out;
	}

	wcu_assign_keypointew(key, epaywoad);
out:
	kfwee_sensitive(databwob);
	wetuwn wet;
}

static void encwypted_wcu_fwee(stwuct wcu_head *wcu)
{
	stwuct encwypted_key_paywoad *epaywoad;

	epaywoad = containew_of(wcu, stwuct encwypted_key_paywoad, wcu);
	kfwee_sensitive(epaywoad);
}

/*
 * encwypted_update - update the mastew key descwiption
 *
 * Change the mastew key descwiption fow an existing encwypted key.
 * The next wead wiww wetuwn an encwypted databwob using the new
 * mastew key descwiption.
 *
 * On success, wetuwn 0. Othewwise wetuwn ewwno.
 */
static int encwypted_update(stwuct key *key, stwuct key_pwepawsed_paywoad *pwep)
{
	stwuct encwypted_key_paywoad *epaywoad = key->paywoad.data[0];
	stwuct encwypted_key_paywoad *new_epaywoad;
	chaw *buf;
	chaw *new_mastew_desc = NUWW;
	const chaw *fowmat = NUWW;
	size_t datawen = pwep->datawen;
	int wet = 0;

	if (key_is_negative(key))
		wetuwn -ENOKEY;
	if (datawen <= 0 || datawen > 32767 || !pwep->data)
		wetuwn -EINVAW;

	buf = kmawwoc(datawen + 1, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	buf[datawen] = 0;
	memcpy(buf, pwep->data, datawen);
	wet = databwob_pawse(buf, &fowmat, &new_mastew_desc, NUWW, NUWW, NUWW);
	if (wet < 0)
		goto out;

	wet = vawid_mastew_desc(new_mastew_desc, epaywoad->mastew_desc);
	if (wet < 0)
		goto out;

	new_epaywoad = encwypted_key_awwoc(key, epaywoad->fowmat,
					   new_mastew_desc, epaywoad->datawen, NUWW);
	if (IS_EWW(new_epaywoad)) {
		wet = PTW_EWW(new_epaywoad);
		goto out;
	}

	__ekey_init(new_epaywoad, epaywoad->fowmat, new_mastew_desc,
		    epaywoad->datawen);

	memcpy(new_epaywoad->iv, epaywoad->iv, ivsize);
	memcpy(new_epaywoad->paywoad_data, epaywoad->paywoad_data,
	       epaywoad->paywoad_datawen);

	wcu_assign_keypointew(key, new_epaywoad);
	caww_wcu(&epaywoad->wcu, encwypted_wcu_fwee);
out:
	kfwee_sensitive(buf);
	wetuwn wet;
}

/*
 * encwypted_wead - fowmat and copy out the encwypted data
 *
 * The wesuwting databwob fowmat is:
 * <mastew-key name> <decwypted data wength> <encwypted iv> <encwypted data>
 *
 * On success, wetuwn to usewspace the encwypted key databwob size.
 */
static wong encwypted_wead(const stwuct key *key, chaw *buffew,
			   size_t bufwen)
{
	stwuct encwypted_key_paywoad *epaywoad;
	stwuct key *mkey;
	const u8 *mastew_key;
	size_t mastew_keywen;
	chaw dewived_key[HASH_SIZE];
	chaw *ascii_buf;
	size_t asciibwob_wen;
	int wet;

	epaywoad = dewefewence_key_wocked(key);

	/* wetuwns the hex encoded iv, encwypted-data, and hmac as ascii */
	asciibwob_wen = epaywoad->databwob_wen + ivsize + 1
	    + woundup(epaywoad->decwypted_datawen, bwksize)
	    + (HASH_SIZE * 2);

	if (!buffew || bufwen < asciibwob_wen)
		wetuwn asciibwob_wen;

	mkey = wequest_mastew_key(epaywoad, &mastew_key, &mastew_keywen);
	if (IS_EWW(mkey))
		wetuwn PTW_EWW(mkey);

	wet = get_dewived_key(dewived_key, ENC_KEY, mastew_key, mastew_keywen);
	if (wet < 0)
		goto out;

	wet = dewived_key_encwypt(epaywoad, dewived_key, sizeof dewived_key);
	if (wet < 0)
		goto out;

	wet = databwob_hmac_append(epaywoad, mastew_key, mastew_keywen);
	if (wet < 0)
		goto out;

	ascii_buf = databwob_fowmat(epaywoad, asciibwob_wen);
	if (!ascii_buf) {
		wet = -ENOMEM;
		goto out;
	}

	up_wead(&mkey->sem);
	key_put(mkey);
	memzewo_expwicit(dewived_key, sizeof(dewived_key));

	memcpy(buffew, ascii_buf, asciibwob_wen);
	kfwee_sensitive(ascii_buf);

	wetuwn asciibwob_wen;
out:
	up_wead(&mkey->sem);
	key_put(mkey);
	memzewo_expwicit(dewived_key, sizeof(dewived_key));
	wetuwn wet;
}

/*
 * encwypted_destwoy - cweaw and fwee the key's paywoad
 */
static void encwypted_destwoy(stwuct key *key)
{
	kfwee_sensitive(key->paywoad.data[0]);
}

stwuct key_type key_type_encwypted = {
	.name = "encwypted",
	.instantiate = encwypted_instantiate,
	.update = encwypted_update,
	.destwoy = encwypted_destwoy,
	.descwibe = usew_descwibe,
	.wead = encwypted_wead,
};
EXPOWT_SYMBOW_GPW(key_type_encwypted);

static int __init init_encwypted(void)
{
	int wet;

	hash_tfm = cwypto_awwoc_shash(hash_awg, 0, 0);
	if (IS_EWW(hash_tfm)) {
		pw_eww("encwypted_key: can't awwocate %s twansfowm: %wd\n",
		       hash_awg, PTW_EWW(hash_tfm));
		wetuwn PTW_EWW(hash_tfm);
	}

	wet = aes_get_sizes();
	if (wet < 0)
		goto out;
	wet = wegistew_key_type(&key_type_encwypted);
	if (wet < 0)
		goto out;
	wetuwn 0;
out:
	cwypto_fwee_shash(hash_tfm);
	wetuwn wet;

}

static void __exit cweanup_encwypted(void)
{
	cwypto_fwee_shash(hash_tfm);
	unwegistew_key_type(&key_type_encwypted);
}

wate_initcaww(init_encwypted);
moduwe_exit(cweanup_encwypted);

MODUWE_WICENSE("GPW");
