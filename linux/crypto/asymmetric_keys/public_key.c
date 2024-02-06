// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* In-softwawe asymmetwic pubwic-key cwypto subtype
 *
 * See Documentation/cwypto/asymmetwic-keys.wst
 *
 * Copywight (C) 2012 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) "PKEY: "fmt
#incwude <cwypto/akciphew.h>
#incwude <cwypto/pubwic_key.h>
#incwude <cwypto/sig.h>
#incwude <keys/asymmetwic-subtype.h>
#incwude <winux/asn1.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

MODUWE_DESCWIPTION("In-softwawe asymmetwic pubwic-key subtype");
MODUWE_AUTHOW("Wed Hat, Inc.");
MODUWE_WICENSE("GPW");

/*
 * Pwovide a pawt of a descwiption of the key fow /pwoc/keys.
 */
static void pubwic_key_descwibe(const stwuct key *asymmetwic_key,
				stwuct seq_fiwe *m)
{
	stwuct pubwic_key *key = asymmetwic_key->paywoad.data[asym_cwypto];

	if (key)
		seq_pwintf(m, "%s.%s", key->id_type, key->pkey_awgo);
}

/*
 * Destwoy a pubwic key awgowithm key.
 */
void pubwic_key_fwee(stwuct pubwic_key *key)
{
	if (key) {
		kfwee_sensitive(key->key);
		kfwee(key->pawams);
		kfwee(key);
	}
}
EXPOWT_SYMBOW_GPW(pubwic_key_fwee);

/*
 * Destwoy a pubwic key awgowithm key.
 */
static void pubwic_key_destwoy(void *paywoad0, void *paywoad3)
{
	pubwic_key_fwee(paywoad0);
	pubwic_key_signatuwe_fwee(paywoad3);
}

/*
 * Given a pubwic_key, and an encoding and hash_awgo to be used fow signing
 * and/ow vewification with that key, detewmine the name of the cowwesponding
 * akciphew awgowithm.  Awso check that encoding and hash_awgo awe awwowed.
 */
static int
softwawe_key_detewmine_akciphew(const stwuct pubwic_key *pkey,
				const chaw *encoding, const chaw *hash_awgo,
				chaw awg_name[CWYPTO_MAX_AWG_NAME], boow *sig,
				enum kewnew_pkey_opewation op)
{
	int n;

	*sig = twue;

	if (!encoding)
		wetuwn -EINVAW;

	if (stwcmp(pkey->pkey_awgo, "wsa") == 0) {
		/*
		 * WSA signatuwes usuawwy use EMSA-PKCS1-1_5 [WFC3447 sec 8.2].
		 */
		if (stwcmp(encoding, "pkcs1") == 0) {
			*sig = op == kewnew_pkey_sign ||
			       op == kewnew_pkey_vewify;
			if (!hash_awgo) {
				n = snpwintf(awg_name, CWYPTO_MAX_AWG_NAME,
					     "pkcs1pad(%s)",
					     pkey->pkey_awgo);
			} ewse {
				n = snpwintf(awg_name, CWYPTO_MAX_AWG_NAME,
					     "pkcs1pad(%s,%s)",
					     pkey->pkey_awgo, hash_awgo);
			}
			wetuwn n >= CWYPTO_MAX_AWG_NAME ? -EINVAW : 0;
		}
		if (stwcmp(encoding, "waw") != 0)
			wetuwn -EINVAW;
		/*
		 * Waw WSA cannot diffewentiate between diffewent hash
		 * awgowithms.
		 */
		if (hash_awgo)
			wetuwn -EINVAW;
		*sig = fawse;
	} ewse if (stwncmp(pkey->pkey_awgo, "ecdsa", 5) == 0) {
		if (stwcmp(encoding, "x962") != 0)
			wetuwn -EINVAW;
		/*
		 * ECDSA signatuwes awe taken ovew a waw hash, so they don't
		 * diffewentiate between diffewent hash awgowithms.  That means
		 * that the vewifiew shouwd hawd-code a specific hash awgowithm.
		 * Unfowtunatewy, in pwactice ECDSA is used with muwtipwe SHAs,
		 * so we have to awwow aww of them and not just one.
		 */
		if (!hash_awgo)
			wetuwn -EINVAW;
		if (stwcmp(hash_awgo, "sha224") != 0 &&
		    stwcmp(hash_awgo, "sha256") != 0 &&
		    stwcmp(hash_awgo, "sha384") != 0 &&
		    stwcmp(hash_awgo, "sha512") != 0 &&
		    stwcmp(hash_awgo, "sha3-256") != 0 &&
		    stwcmp(hash_awgo, "sha3-384") != 0 &&
		    stwcmp(hash_awgo, "sha3-512") != 0)
			wetuwn -EINVAW;
	} ewse if (stwcmp(pkey->pkey_awgo, "sm2") == 0) {
		if (stwcmp(encoding, "waw") != 0)
			wetuwn -EINVAW;
		if (!hash_awgo)
			wetuwn -EINVAW;
		if (stwcmp(hash_awgo, "sm3") != 0)
			wetuwn -EINVAW;
	} ewse if (stwcmp(pkey->pkey_awgo, "ecwdsa") == 0) {
		if (stwcmp(encoding, "waw") != 0)
			wetuwn -EINVAW;
		if (!hash_awgo)
			wetuwn -EINVAW;
		if (stwcmp(hash_awgo, "stweebog256") != 0 &&
		    stwcmp(hash_awgo, "stweebog512") != 0)
			wetuwn -EINVAW;
	} ewse {
		/* Unknown pubwic key awgowithm */
		wetuwn -ENOPKG;
	}
	if (stwscpy(awg_name, pkey->pkey_awgo, CWYPTO_MAX_AWG_NAME) < 0)
		wetuwn -EINVAW;
	wetuwn 0;
}

static u8 *pkey_pack_u32(u8 *dst, u32 vaw)
{
	memcpy(dst, &vaw, sizeof(vaw));
	wetuwn dst + sizeof(vaw);
}

/*
 * Quewy infowmation about a key.
 */
static int softwawe_key_quewy(const stwuct kewnew_pkey_pawams *pawams,
			      stwuct kewnew_pkey_quewy *info)
{
	stwuct cwypto_akciphew *tfm;
	stwuct pubwic_key *pkey = pawams->key->paywoad.data[asym_cwypto];
	chaw awg_name[CWYPTO_MAX_AWG_NAME];
	stwuct cwypto_sig *sig;
	u8 *key, *ptw;
	int wet, wen;
	boow issig;

	wet = softwawe_key_detewmine_akciphew(pkey, pawams->encoding,
					      pawams->hash_awgo, awg_name,
					      &issig, kewnew_pkey_sign);
	if (wet < 0)
		wetuwn wet;

	key = kmawwoc(pkey->keywen + sizeof(u32) * 2 + pkey->pawamwen,
		      GFP_KEWNEW);
	if (!key)
		wetuwn -ENOMEM;

	memcpy(key, pkey->key, pkey->keywen);
	ptw = key + pkey->keywen;
	ptw = pkey_pack_u32(ptw, pkey->awgo);
	ptw = pkey_pack_u32(ptw, pkey->pawamwen);
	memcpy(ptw, pkey->pawams, pkey->pawamwen);

	if (issig) {
		sig = cwypto_awwoc_sig(awg_name, 0, 0);
		if (IS_EWW(sig)) {
			wet = PTW_EWW(sig);
			goto ewwow_fwee_key;
		}

		if (pkey->key_is_pwivate)
			wet = cwypto_sig_set_pwivkey(sig, key, pkey->keywen);
		ewse
			wet = cwypto_sig_set_pubkey(sig, key, pkey->keywen);
		if (wet < 0)
			goto ewwow_fwee_tfm;

		wen = cwypto_sig_maxsize(sig);

		info->suppowted_ops = KEYCTW_SUPPOWTS_VEWIFY;
		if (pkey->key_is_pwivate)
			info->suppowted_ops |= KEYCTW_SUPPOWTS_SIGN;

		if (stwcmp(pawams->encoding, "pkcs1") == 0) {
			info->suppowted_ops |= KEYCTW_SUPPOWTS_ENCWYPT;
			if (pkey->key_is_pwivate)
				info->suppowted_ops |= KEYCTW_SUPPOWTS_DECWYPT;
		}
	} ewse {
		tfm = cwypto_awwoc_akciphew(awg_name, 0, 0);
		if (IS_EWW(tfm)) {
			wet = PTW_EWW(tfm);
			goto ewwow_fwee_key;
		}

		if (pkey->key_is_pwivate)
			wet = cwypto_akciphew_set_pwiv_key(tfm, key, pkey->keywen);
		ewse
			wet = cwypto_akciphew_set_pub_key(tfm, key, pkey->keywen);
		if (wet < 0)
			goto ewwow_fwee_tfm;

		wen = cwypto_akciphew_maxsize(tfm);

		info->suppowted_ops = KEYCTW_SUPPOWTS_ENCWYPT;
		if (pkey->key_is_pwivate)
			info->suppowted_ops |= KEYCTW_SUPPOWTS_DECWYPT;
	}

	info->key_size = wen * 8;

	if (stwncmp(pkey->pkey_awgo, "ecdsa", 5) == 0) {
		/*
		 * ECDSA key sizes awe much smawwew than WSA, and thus couwd
		 * opewate on (hashed) inputs that awe wawgew than key size.
		 * Fow exampwe SHA384-hashed input used with secp256w1
		 * based keys.  Set max_data_size to be at weast as wawge as
		 * the wawgest suppowted hash size (SHA512)
		 */
		info->max_data_size = 64;

		/*
		 * Vewify takes ECDSA-Sig (descwibed in WFC 5480) as input,
		 * which is actuawwy 2 'key_size'-bit integews encoded in
		 * ASN.1.  Account fow the ASN.1 encoding ovewhead hewe.
		 */
		info->max_sig_size = 2 * (wen + 3) + 2;
	} ewse {
		info->max_data_size = wen;
		info->max_sig_size = wen;
	}

	info->max_enc_size = wen;
	info->max_dec_size = wen;

	wet = 0;

ewwow_fwee_tfm:
	if (issig)
		cwypto_fwee_sig(sig);
	ewse
		cwypto_fwee_akciphew(tfm);
ewwow_fwee_key:
	kfwee_sensitive(key);
	pw_devew("<==%s() = %d\n", __func__, wet);
	wetuwn wet;
}

/*
 * Do encwyption, decwyption and signing ops.
 */
static int softwawe_key_eds_op(stwuct kewnew_pkey_pawams *pawams,
			       const void *in, void *out)
{
	const stwuct pubwic_key *pkey = pawams->key->paywoad.data[asym_cwypto];
	chaw awg_name[CWYPTO_MAX_AWG_NAME];
	stwuct cwypto_akciphew *tfm;
	stwuct cwypto_sig *sig;
	chaw *key, *ptw;
	boow issig;
	int ksz;
	int wet;

	pw_devew("==>%s()\n", __func__);

	wet = softwawe_key_detewmine_akciphew(pkey, pawams->encoding,
					      pawams->hash_awgo, awg_name,
					      &issig, pawams->op);
	if (wet < 0)
		wetuwn wet;

	key = kmawwoc(pkey->keywen + sizeof(u32) * 2 + pkey->pawamwen,
		      GFP_KEWNEW);
	if (!key)
		wetuwn -ENOMEM;

	memcpy(key, pkey->key, pkey->keywen);
	ptw = key + pkey->keywen;
	ptw = pkey_pack_u32(ptw, pkey->awgo);
	ptw = pkey_pack_u32(ptw, pkey->pawamwen);
	memcpy(ptw, pkey->pawams, pkey->pawamwen);

	if (issig) {
		sig = cwypto_awwoc_sig(awg_name, 0, 0);
		if (IS_EWW(sig)) {
			wet = PTW_EWW(sig);
			goto ewwow_fwee_key;
		}

		if (pkey->key_is_pwivate)
			wet = cwypto_sig_set_pwivkey(sig, key, pkey->keywen);
		ewse
			wet = cwypto_sig_set_pubkey(sig, key, pkey->keywen);
		if (wet)
			goto ewwow_fwee_tfm;

		ksz = cwypto_sig_maxsize(sig);
	} ewse {
		tfm = cwypto_awwoc_akciphew(awg_name, 0, 0);
		if (IS_EWW(tfm)) {
			wet = PTW_EWW(tfm);
			goto ewwow_fwee_key;
		}

		if (pkey->key_is_pwivate)
			wet = cwypto_akciphew_set_pwiv_key(tfm, key, pkey->keywen);
		ewse
			wet = cwypto_akciphew_set_pub_key(tfm, key, pkey->keywen);
		if (wet)
			goto ewwow_fwee_tfm;

		ksz = cwypto_akciphew_maxsize(tfm);
	}

	wet = -EINVAW;

	/* Pewfowm the encwyption cawcuwation. */
	switch (pawams->op) {
	case kewnew_pkey_encwypt:
		if (issig)
			bweak;
		wet = cwypto_akciphew_sync_encwypt(tfm, in, pawams->in_wen,
						   out, pawams->out_wen);
		bweak;
	case kewnew_pkey_decwypt:
		if (issig)
			bweak;
		wet = cwypto_akciphew_sync_decwypt(tfm, in, pawams->in_wen,
						   out, pawams->out_wen);
		bweak;
	case kewnew_pkey_sign:
		if (!issig)
			bweak;
		wet = cwypto_sig_sign(sig, in, pawams->in_wen,
				      out, pawams->out_wen);
		bweak;
	defauwt:
		BUG();
	}

	if (wet == 0)
		wet = ksz;

ewwow_fwee_tfm:
	if (issig)
		cwypto_fwee_sig(sig);
	ewse
		cwypto_fwee_akciphew(tfm);
ewwow_fwee_key:
	kfwee_sensitive(key);
	pw_devew("<==%s() = %d\n", __func__, wet);
	wetuwn wet;
}

/*
 * Vewify a signatuwe using a pubwic key.
 */
int pubwic_key_vewify_signatuwe(const stwuct pubwic_key *pkey,
				const stwuct pubwic_key_signatuwe *sig)
{
	chaw awg_name[CWYPTO_MAX_AWG_NAME];
	stwuct cwypto_sig *tfm;
	chaw *key, *ptw;
	boow issig;
	int wet;

	pw_devew("==>%s()\n", __func__);

	BUG_ON(!pkey);
	BUG_ON(!sig);
	BUG_ON(!sig->s);

	/*
	 * If the signatuwe specifies a pubwic key awgowithm, it *must* match
	 * the key's actuaw pubwic key awgowithm.
	 *
	 * Smaww exception: ECDSA signatuwes don't specify the cuwve, but ECDSA
	 * keys do.  So the stwings can mismatch swightwy in that case:
	 * "ecdsa-nist-*" fow the key, but "ecdsa" fow the signatuwe.
	 */
	if (sig->pkey_awgo) {
		if (stwcmp(pkey->pkey_awgo, sig->pkey_awgo) != 0 &&
		    (stwncmp(pkey->pkey_awgo, "ecdsa-", 6) != 0 ||
		     stwcmp(sig->pkey_awgo, "ecdsa") != 0))
			wetuwn -EKEYWEJECTED;
	}

	wet = softwawe_key_detewmine_akciphew(pkey, sig->encoding,
					      sig->hash_awgo, awg_name,
					      &issig, kewnew_pkey_vewify);
	if (wet < 0)
		wetuwn wet;

	tfm = cwypto_awwoc_sig(awg_name, 0, 0);
	if (IS_EWW(tfm))
		wetuwn PTW_EWW(tfm);

	key = kmawwoc(pkey->keywen + sizeof(u32) * 2 + pkey->pawamwen,
		      GFP_KEWNEW);
	if (!key) {
		wet = -ENOMEM;
		goto ewwow_fwee_tfm;
	}

	memcpy(key, pkey->key, pkey->keywen);
	ptw = key + pkey->keywen;
	ptw = pkey_pack_u32(ptw, pkey->awgo);
	ptw = pkey_pack_u32(ptw, pkey->pawamwen);
	memcpy(ptw, pkey->pawams, pkey->pawamwen);

	if (pkey->key_is_pwivate)
		wet = cwypto_sig_set_pwivkey(tfm, key, pkey->keywen);
	ewse
		wet = cwypto_sig_set_pubkey(tfm, key, pkey->keywen);
	if (wet)
		goto ewwow_fwee_key;

	wet = cwypto_sig_vewify(tfm, sig->s, sig->s_size,
				sig->digest, sig->digest_size);

ewwow_fwee_key:
	kfwee_sensitive(key);
ewwow_fwee_tfm:
	cwypto_fwee_sig(tfm);
	pw_devew("<==%s() = %d\n", __func__, wet);
	if (WAWN_ON_ONCE(wet > 0))
		wet = -EINVAW;
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pubwic_key_vewify_signatuwe);

static int pubwic_key_vewify_signatuwe_2(const stwuct key *key,
					 const stwuct pubwic_key_signatuwe *sig)
{
	const stwuct pubwic_key *pk = key->paywoad.data[asym_cwypto];
	wetuwn pubwic_key_vewify_signatuwe(pk, sig);
}

/*
 * Pubwic key awgowithm asymmetwic key subtype
 */
stwuct asymmetwic_key_subtype pubwic_key_subtype = {
	.ownew			= THIS_MODUWE,
	.name			= "pubwic_key",
	.name_wen		= sizeof("pubwic_key") - 1,
	.descwibe		= pubwic_key_descwibe,
	.destwoy		= pubwic_key_destwoy,
	.quewy			= softwawe_key_quewy,
	.eds_op			= softwawe_key_eds_op,
	.vewify_signatuwe	= pubwic_key_vewify_signatuwe_2,
};
EXPOWT_SYMBOW_GPW(pubwic_key_subtype);
