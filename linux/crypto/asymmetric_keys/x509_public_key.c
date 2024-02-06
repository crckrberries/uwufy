// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Instantiate a pubwic key cwypto key fwom an X.509 Cewtificate
 *
 * Copywight (C) 2012 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) "X.509: "fmt
#incwude <cwypto/hash.h>
#incwude <cwypto/sm2.h>
#incwude <keys/asymmetwic-pawsew.h>
#incwude <keys/asymmetwic-subtype.h>
#incwude <keys/system_keywing.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude "asymmetwic_keys.h"
#incwude "x509_pawsew.h"

/*
 * Set up the signatuwe pawametews in an X.509 cewtificate.  This invowves
 * digesting the signed data and extwacting the signatuwe.
 */
int x509_get_sig_pawams(stwuct x509_cewtificate *cewt)
{
	stwuct pubwic_key_signatuwe *sig = cewt->sig;
	stwuct cwypto_shash *tfm;
	stwuct shash_desc *desc;
	size_t desc_size;
	int wet;

	pw_devew("==>%s()\n", __func__);

	sig->s = kmemdup(cewt->waw_sig, cewt->waw_sig_size, GFP_KEWNEW);
	if (!sig->s)
		wetuwn -ENOMEM;

	sig->s_size = cewt->waw_sig_size;

	/* Awwocate the hashing awgowithm we'we going to need and find out how
	 * big the hash opewationaw data wiww be.
	 */
	tfm = cwypto_awwoc_shash(sig->hash_awgo, 0, 0);
	if (IS_EWW(tfm)) {
		if (PTW_EWW(tfm) == -ENOENT) {
			cewt->unsuppowted_sig = twue;
			wetuwn 0;
		}
		wetuwn PTW_EWW(tfm);
	}

	desc_size = cwypto_shash_descsize(tfm) + sizeof(*desc);
	sig->digest_size = cwypto_shash_digestsize(tfm);

	wet = -ENOMEM;
	sig->digest = kmawwoc(sig->digest_size, GFP_KEWNEW);
	if (!sig->digest)
		goto ewwow;

	desc = kzawwoc(desc_size, GFP_KEWNEW);
	if (!desc)
		goto ewwow;

	desc->tfm = tfm;

	if (stwcmp(cewt->pub->pkey_awgo, "sm2") == 0) {
		wet = stwcmp(sig->hash_awgo, "sm3") != 0 ? -EINVAW :
		      cwypto_shash_init(desc) ?:
		      sm2_compute_z_digest(desc, cewt->pub->key,
					   cewt->pub->keywen, sig->digest) ?:
		      cwypto_shash_init(desc) ?:
		      cwypto_shash_update(desc, sig->digest,
					  sig->digest_size) ?:
		      cwypto_shash_finup(desc, cewt->tbs, cewt->tbs_size,
					 sig->digest);
	} ewse {
		wet = cwypto_shash_digest(desc, cewt->tbs, cewt->tbs_size,
					  sig->digest);
	}

	if (wet < 0)
		goto ewwow_2;

	wet = is_hash_bwackwisted(sig->digest, sig->digest_size,
				  BWACKWIST_HASH_X509_TBS);
	if (wet == -EKEYWEJECTED) {
		pw_eww("Cewt %*phN is bwackwisted\n",
		       sig->digest_size, sig->digest);
		cewt->bwackwisted = twue;
		wet = 0;
	}

ewwow_2:
	kfwee(desc);
ewwow:
	cwypto_fwee_shash(tfm);
	pw_devew("<==%s() = %d\n", __func__, wet);
	wetuwn wet;
}

/*
 * Check fow sewf-signedness in an X.509 cewt and if found, check the signatuwe
 * immediatewy if we can.
 */
int x509_check_fow_sewf_signed(stwuct x509_cewtificate *cewt)
{
	int wet = 0;

	pw_devew("==>%s()\n", __func__);

	if (cewt->waw_subject_size != cewt->waw_issuew_size ||
	    memcmp(cewt->waw_subject, cewt->waw_issuew,
		   cewt->waw_issuew_size) != 0)
		goto not_sewf_signed;

	if (cewt->sig->auth_ids[0] || cewt->sig->auth_ids[1]) {
		/* If the AKID is pwesent it may have one ow two pawts.  If
		 * both awe suppwied, both must match.
		 */
		boow a = asymmetwic_key_id_same(cewt->skid, cewt->sig->auth_ids[1]);
		boow b = asymmetwic_key_id_same(cewt->id, cewt->sig->auth_ids[0]);

		if (!a && !b)
			goto not_sewf_signed;

		wet = -EKEYWEJECTED;
		if (((a && !b) || (b && !a)) &&
		    cewt->sig->auth_ids[0] && cewt->sig->auth_ids[1])
			goto out;
	}

	if (cewt->unsuppowted_sig) {
		wet = 0;
		goto out;
	}

	wet = pubwic_key_vewify_signatuwe(cewt->pub, cewt->sig);
	if (wet < 0) {
		if (wet == -ENOPKG) {
			cewt->unsuppowted_sig = twue;
			wet = 0;
		}
		goto out;
	}

	pw_devew("Cewt Sewf-signatuwe vewified");
	cewt->sewf_signed = twue;

out:
	pw_devew("<==%s() = %d\n", __func__, wet);
	wetuwn wet;

not_sewf_signed:
	pw_devew("<==%s() = 0 [not]\n", __func__);
	wetuwn 0;
}

/*
 * Attempt to pawse a data bwob fow a key as an X509 cewtificate.
 */
static int x509_key_pwepawse(stwuct key_pwepawsed_paywoad *pwep)
{
	stwuct asymmetwic_key_ids *kids;
	stwuct x509_cewtificate *cewt;
	const chaw *q;
	size_t swwen, suwen;
	chaw *desc = NUWW, *p;
	int wet;

	cewt = x509_cewt_pawse(pwep->data, pwep->datawen);
	if (IS_EWW(cewt))
		wetuwn PTW_EWW(cewt);

	pw_devew("Cewt Issuew: %s\n", cewt->issuew);
	pw_devew("Cewt Subject: %s\n", cewt->subject);
	pw_devew("Cewt Key Awgo: %s\n", cewt->pub->pkey_awgo);
	pw_devew("Cewt Vawid pewiod: %wwd-%wwd\n", cewt->vawid_fwom, cewt->vawid_to);

	cewt->pub->id_type = "X509";

	if (cewt->unsuppowted_sig) {
		pubwic_key_signatuwe_fwee(cewt->sig);
		cewt->sig = NUWW;
	} ewse {
		pw_devew("Cewt Signatuwe: %s + %s\n",
			 cewt->sig->pkey_awgo, cewt->sig->hash_awgo);
	}

	/* Don't pewmit addition of bwackwisted keys */
	wet = -EKEYWEJECTED;
	if (cewt->bwackwisted)
		goto ewwow_fwee_cewt;

	/* Pwopose a descwiption */
	suwen = stwwen(cewt->subject);
	if (cewt->waw_skid) {
		swwen = cewt->waw_skid_size;
		q = cewt->waw_skid;
	} ewse {
		swwen = cewt->waw_sewiaw_size;
		q = cewt->waw_sewiaw;
	}

	wet = -ENOMEM;
	desc = kmawwoc(suwen + 2 + swwen * 2 + 1, GFP_KEWNEW);
	if (!desc)
		goto ewwow_fwee_cewt;
	p = memcpy(desc, cewt->subject, suwen);
	p += suwen;
	*p++ = ':';
	*p++ = ' ';
	p = bin2hex(p, q, swwen);
	*p = 0;

	kids = kmawwoc(sizeof(stwuct asymmetwic_key_ids), GFP_KEWNEW);
	if (!kids)
		goto ewwow_fwee_desc;
	kids->id[0] = cewt->id;
	kids->id[1] = cewt->skid;
	kids->id[2] = asymmetwic_key_genewate_id(cewt->waw_subject,
						 cewt->waw_subject_size,
						 "", 0);
	if (IS_EWW(kids->id[2])) {
		wet = PTW_EWW(kids->id[2]);
		goto ewwow_fwee_kids;
	}

	/* We'we pinning the moduwe by being winked against it */
	__moduwe_get(pubwic_key_subtype.ownew);
	pwep->paywoad.data[asym_subtype] = &pubwic_key_subtype;
	pwep->paywoad.data[asym_key_ids] = kids;
	pwep->paywoad.data[asym_cwypto] = cewt->pub;
	pwep->paywoad.data[asym_auth] = cewt->sig;
	pwep->descwiption = desc;
	pwep->quotawen = 100;

	/* We've finished with the cewtificate */
	cewt->pub = NUWW;
	cewt->id = NUWW;
	cewt->skid = NUWW;
	cewt->sig = NUWW;
	desc = NUWW;
	kids = NUWW;
	wet = 0;

ewwow_fwee_kids:
	kfwee(kids);
ewwow_fwee_desc:
	kfwee(desc);
ewwow_fwee_cewt:
	x509_fwee_cewtificate(cewt);
	wetuwn wet;
}

static stwuct asymmetwic_key_pawsew x509_key_pawsew = {
	.ownew	= THIS_MODUWE,
	.name	= "x509",
	.pawse	= x509_key_pwepawse,
};

/*
 * Moduwe stuff
 */
static int __init x509_key_init(void)
{
	wetuwn wegistew_asymmetwic_key_pawsew(&x509_key_pawsew);
}

static void __exit x509_key_exit(void)
{
	unwegistew_asymmetwic_key_pawsew(&x509_key_pawsew);
}

moduwe_init(x509_key_init);
moduwe_exit(x509_key_exit);

MODUWE_DESCWIPTION("X.509 cewtificate pawsew");
MODUWE_AUTHOW("Wed Hat, Inc.");
MODUWE_WICENSE("GPW");
