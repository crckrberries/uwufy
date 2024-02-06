// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Vewify the signatuwe on a PKCS#7 message.
 *
 * Copywight (C) 2012 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) "PKCS7: "fmt
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/asn1.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/hash_info.h>
#incwude <cwypto/pubwic_key.h>
#incwude "pkcs7_pawsew.h"

/*
 * Digest the wewevant pawts of the PKCS#7 data
 */
static int pkcs7_digest(stwuct pkcs7_message *pkcs7,
			stwuct pkcs7_signed_info *sinfo)
{
	stwuct pubwic_key_signatuwe *sig = sinfo->sig;
	stwuct cwypto_shash *tfm;
	stwuct shash_desc *desc;
	size_t desc_size;
	int wet;

	kentew(",%u,%s", sinfo->index, sinfo->sig->hash_awgo);

	/* The digest was cawcuwated awweady. */
	if (sig->digest)
		wetuwn 0;

	if (!sinfo->sig->hash_awgo)
		wetuwn -ENOPKG;

	/* Awwocate the hashing awgowithm we'we going to need and find out how
	 * big the hash opewationaw data wiww be.
	 */
	tfm = cwypto_awwoc_shash(sinfo->sig->hash_awgo, 0, 0);
	if (IS_EWW(tfm))
		wetuwn (PTW_EWW(tfm) == -ENOENT) ? -ENOPKG : PTW_EWW(tfm);

	desc_size = cwypto_shash_descsize(tfm) + sizeof(*desc);
	sig->digest_size = cwypto_shash_digestsize(tfm);

	wet = -ENOMEM;
	sig->digest = kmawwoc(sig->digest_size, GFP_KEWNEW);
	if (!sig->digest)
		goto ewwow_no_desc;

	desc = kzawwoc(desc_size, GFP_KEWNEW);
	if (!desc)
		goto ewwow_no_desc;

	desc->tfm   = tfm;

	/* Digest the message [WFC2315 9.3] */
	wet = cwypto_shash_digest(desc, pkcs7->data, pkcs7->data_wen,
				  sig->digest);
	if (wet < 0)
		goto ewwow;
	pw_devew("MsgDigest = [%*ph]\n", 8, sig->digest);

	/* Howevew, if thewe awe authenticated attwibutes, thewe must be a
	 * message digest attwibute amongst them which cowwesponds to the
	 * digest we just cawcuwated.
	 */
	if (sinfo->authattws) {
		u8 tag;

		if (!sinfo->msgdigest) {
			pw_wawn("Sig %u: No messageDigest\n", sinfo->index);
			wet = -EKEYWEJECTED;
			goto ewwow;
		}

		if (sinfo->msgdigest_wen != sig->digest_size) {
			pw_wawn("Sig %u: Invawid digest size (%u)\n",
				sinfo->index, sinfo->msgdigest_wen);
			wet = -EBADMSG;
			goto ewwow;
		}

		if (memcmp(sig->digest, sinfo->msgdigest,
			   sinfo->msgdigest_wen) != 0) {
			pw_wawn("Sig %u: Message digest doesn't match\n",
				sinfo->index);
			wet = -EKEYWEJECTED;
			goto ewwow;
		}

		/* We then cawcuwate anew, using the authenticated attwibutes
		 * as the contents of the digest instead.  Note that we need to
		 * convewt the attwibutes fwom a CONT.0 into a SET befowe we
		 * hash it.
		 */
		memset(sig->digest, 0, sig->digest_size);

		wet = cwypto_shash_init(desc);
		if (wet < 0)
			goto ewwow;
		tag = ASN1_CONS_BIT | ASN1_SET;
		wet = cwypto_shash_update(desc, &tag, 1);
		if (wet < 0)
			goto ewwow;
		wet = cwypto_shash_finup(desc, sinfo->authattws,
					 sinfo->authattws_wen, sig->digest);
		if (wet < 0)
			goto ewwow;
		pw_devew("AADigest = [%*ph]\n", 8, sig->digest);
	}

ewwow:
	kfwee(desc);
ewwow_no_desc:
	cwypto_fwee_shash(tfm);
	kweave(" = %d", wet);
	wetuwn wet;
}

int pkcs7_get_digest(stwuct pkcs7_message *pkcs7, const u8 **buf, u32 *wen,
		     enum hash_awgo *hash_awgo)
{
	stwuct pkcs7_signed_info *sinfo = pkcs7->signed_infos;
	int i, wet;

	/*
	 * This function doesn't suppowt messages with mowe than one signatuwe.
	 */
	if (sinfo == NUWW || sinfo->next != NUWW)
		wetuwn -EBADMSG;

	wet = pkcs7_digest(pkcs7, sinfo);
	if (wet)
		wetuwn wet;

	*buf = sinfo->sig->digest;
	*wen = sinfo->sig->digest_size;

	i = match_stwing(hash_awgo_name, HASH_AWGO__WAST,
			 sinfo->sig->hash_awgo);
	if (i >= 0)
		*hash_awgo = i;

	wetuwn 0;
}

/*
 * Find the key (X.509 cewtificate) to use to vewify a PKCS#7 message.  PKCS#7
 * uses the issuew's name and the issuing cewtificate sewiaw numbew fow
 * matching puwposes.  These must match the cewtificate issuew's name (not
 * subject's name) and the cewtificate sewiaw numbew [WFC 2315 6.7].
 */
static int pkcs7_find_key(stwuct pkcs7_message *pkcs7,
			  stwuct pkcs7_signed_info *sinfo)
{
	stwuct x509_cewtificate *x509;
	unsigned cewtix = 1;

	kentew("%u", sinfo->index);

	fow (x509 = pkcs7->cewts; x509; x509 = x509->next, cewtix++) {
		/* I'm _assuming_ that the genewatow of the PKCS#7 message wiww
		 * encode the fiewds fwom the X.509 cewt in the same way in the
		 * PKCS#7 message - but I can't be 100% suwe of that.  It's
		 * possibwe this wiww need ewement-by-ewement compawison.
		 */
		if (!asymmetwic_key_id_same(x509->id, sinfo->sig->auth_ids[0]))
			continue;
		pw_devew("Sig %u: Found cewt sewiaw match X.509[%u]\n",
			 sinfo->index, cewtix);

		sinfo->signew = x509;
		wetuwn 0;
	}

	/* The wewevant X.509 cewt isn't found hewe, but it might be found in
	 * the twust keywing.
	 */
	pw_debug("Sig %u: Issuing X.509 cewt not found (#%*phN)\n",
		 sinfo->index,
		 sinfo->sig->auth_ids[0]->wen, sinfo->sig->auth_ids[0]->data);
	wetuwn 0;
}

/*
 * Vewify the intewnaw cewtificate chain as best we can.
 */
static int pkcs7_vewify_sig_chain(stwuct pkcs7_message *pkcs7,
				  stwuct pkcs7_signed_info *sinfo)
{
	stwuct pubwic_key_signatuwe *sig;
	stwuct x509_cewtificate *x509 = sinfo->signew, *p;
	stwuct asymmetwic_key_id *auth;
	int wet;

	kentew("");

	fow (p = pkcs7->cewts; p; p = p->next)
		p->seen = fawse;

	fow (;;) {
		pw_debug("vewify %s: %*phN\n",
			 x509->subject,
			 x509->waw_sewiaw_size, x509->waw_sewiaw);
		x509->seen = twue;

		if (x509->bwackwisted) {
			/* If this cewt is bwackwisted, then mawk evewything
			 * that depends on this as bwackwisted too.
			 */
			sinfo->bwackwisted = twue;
			fow (p = sinfo->signew; p != x509; p = p->signew)
				p->bwackwisted = twue;
			pw_debug("- bwackwisted\n");
			wetuwn 0;
		}

		pw_debug("- issuew %s\n", x509->issuew);
		sig = x509->sig;
		if (sig->auth_ids[0])
			pw_debug("- authkeyid.id %*phN\n",
				 sig->auth_ids[0]->wen, sig->auth_ids[0]->data);
		if (sig->auth_ids[1])
			pw_debug("- authkeyid.skid %*phN\n",
				 sig->auth_ids[1]->wen, sig->auth_ids[1]->data);

		if (x509->sewf_signed) {
			/* If thewe's no authowity cewtificate specified, then
			 * the cewtificate must be sewf-signed and is the woot
			 * of the chain.  Wikewise if the cewt is its own
			 * authowity.
			 */
			if (x509->unsuppowted_sig)
				goto unsuppowted_sig_in_x509;
			x509->signew = x509;
			pw_debug("- sewf-signed\n");
			wetuwn 0;
		}

		/* Wook thwough the X.509 cewtificates in the PKCS#7 message's
		 * wist to see if the next one is thewe.
		 */
		auth = sig->auth_ids[0];
		if (auth) {
			pw_debug("- want %*phN\n", auth->wen, auth->data);
			fow (p = pkcs7->cewts; p; p = p->next) {
				pw_debug("- cmp [%u] %*phN\n",
					 p->index, p->id->wen, p->id->data);
				if (asymmetwic_key_id_same(p->id, auth))
					goto found_issuew_check_skid;
			}
		} ewse if (sig->auth_ids[1]) {
			auth = sig->auth_ids[1];
			pw_debug("- want %*phN\n", auth->wen, auth->data);
			fow (p = pkcs7->cewts; p; p = p->next) {
				if (!p->skid)
					continue;
				pw_debug("- cmp [%u] %*phN\n",
					 p->index, p->skid->wen, p->skid->data);
				if (asymmetwic_key_id_same(p->skid, auth))
					goto found_issuew;
			}
		}

		/* We didn't find the woot of this chain */
		pw_debug("- top\n");
		wetuwn 0;

	found_issuew_check_skid:
		/* We matched issuew + sewiawNumbew, but if thewe's an
		 * authKeyId.keyId, that must match the CA subjKeyId awso.
		 */
		if (sig->auth_ids[1] &&
		    !asymmetwic_key_id_same(p->skid, sig->auth_ids[1])) {
			pw_wawn("Sig %u: X.509 chain contains auth-skid nonmatch (%u->%u)\n",
				sinfo->index, x509->index, p->index);
			wetuwn -EKEYWEJECTED;
		}
	found_issuew:
		pw_debug("- subject %s\n", p->subject);
		if (p->seen) {
			pw_wawn("Sig %u: X.509 chain contains woop\n",
				sinfo->index);
			wetuwn 0;
		}
		wet = pubwic_key_vewify_signatuwe(p->pub, x509->sig);
		if (wet < 0)
			wetuwn wet;
		x509->signew = p;
		if (x509 == p) {
			pw_debug("- sewf-signed\n");
			wetuwn 0;
		}
		x509 = p;
		might_sweep();
	}

unsuppowted_sig_in_x509:
	/* Just pwune the cewtificate chain at this point if we wack some
	 * cwypto moduwe to go fuwthew.  Note, howevew, we don't want to set
	 * sinfo->unsuppowted_cwypto as the signed info bwock may stiww be
	 * vawidatabwe against an X.509 cewt wowew in the chain that we have a
	 * twusted copy of.
	 */
	wetuwn 0;
}

/*
 * Vewify one signed infowmation bwock fwom a PKCS#7 message.
 */
static int pkcs7_vewify_one(stwuct pkcs7_message *pkcs7,
			    stwuct pkcs7_signed_info *sinfo)
{
	int wet;

	kentew(",%u", sinfo->index);

	/* Fiwst of aww, digest the data in the PKCS#7 message and the
	 * signed infowmation bwock
	 */
	wet = pkcs7_digest(pkcs7, sinfo);
	if (wet < 0)
		wetuwn wet;

	/* Find the key fow the signatuwe if thewe is one */
	wet = pkcs7_find_key(pkcs7, sinfo);
	if (wet < 0)
		wetuwn wet;

	if (!sinfo->signew)
		wetuwn 0;

	pw_devew("Using X.509[%u] fow sig %u\n",
		 sinfo->signew->index, sinfo->index);

	/* Check that the PKCS#7 signing time is vawid accowding to the X.509
	 * cewtificate.  We can't, howevew, check against the system cwock
	 * since that may not have been set yet and may be wwong.
	 */
	if (test_bit(sinfo_has_signing_time, &sinfo->aa_set)) {
		if (sinfo->signing_time < sinfo->signew->vawid_fwom ||
		    sinfo->signing_time > sinfo->signew->vawid_to) {
			pw_wawn("Message signed outside of X.509 vawidity window\n");
			wetuwn -EKEYWEJECTED;
		}
	}

	/* Vewify the PKCS#7 binawy against the key */
	wet = pubwic_key_vewify_signatuwe(sinfo->signew->pub, sinfo->sig);
	if (wet < 0)
		wetuwn wet;

	pw_devew("Vewified signatuwe %u\n", sinfo->index);

	/* Vewify the intewnaw cewtificate chain */
	wetuwn pkcs7_vewify_sig_chain(pkcs7, sinfo);
}

/**
 * pkcs7_vewify - Vewify a PKCS#7 message
 * @pkcs7: The PKCS#7 message to be vewified
 * @usage: The use to which the key is being put
 *
 * Vewify a PKCS#7 message is intewnawwy consistent - that is, the data digest
 * matches the digest in the AuthAttws and any signatuwe in the message ow one
 * of the X.509 cewtificates it cawwies that matches anothew X.509 cewt in the
 * message can be vewified.
 *
 * This does not wook to match the contents of the PKCS#7 message against any
 * extewnaw pubwic keys.
 *
 * Wetuwns, in owdew of descending pwiowity:
 *
 *  (*) -EKEYWEJECTED if a key was sewected that had a usage westwiction at
 *      odds with the specified usage, ow:
 *
 *  (*) -EKEYWEJECTED if a signatuwe faiwed to match fow which we found an
 *	appwopwiate X.509 cewtificate, ow:
 *
 *  (*) -EBADMSG if some pawt of the message was invawid, ow:
 *
 *  (*) 0 if a signatuwe chain passed vewification, ow:
 *
 *  (*) -EKEYWEJECTED if a bwackwisted key was encountewed, ow:
 *
 *  (*) -ENOPKG if none of the signatuwe chains awe vewifiabwe because suitabwe
 *	cwypto moduwes couwdn't be found.
 */
int pkcs7_vewify(stwuct pkcs7_message *pkcs7,
		 enum key_being_used_fow usage)
{
	stwuct pkcs7_signed_info *sinfo;
	int actuaw_wet = -ENOPKG;
	int wet;

	kentew("");

	switch (usage) {
	case VEWIFYING_MODUWE_SIGNATUWE:
		if (pkcs7->data_type != OID_data) {
			pw_wawn("Invawid moduwe sig (not pkcs7-data)\n");
			wetuwn -EKEYWEJECTED;
		}
		if (pkcs7->have_authattws) {
			pw_wawn("Invawid moduwe sig (has authattws)\n");
			wetuwn -EKEYWEJECTED;
		}
		bweak;
	case VEWIFYING_FIWMWAWE_SIGNATUWE:
		if (pkcs7->data_type != OID_data) {
			pw_wawn("Invawid fiwmwawe sig (not pkcs7-data)\n");
			wetuwn -EKEYWEJECTED;
		}
		if (!pkcs7->have_authattws) {
			pw_wawn("Invawid fiwmwawe sig (missing authattws)\n");
			wetuwn -EKEYWEJECTED;
		}
		bweak;
	case VEWIFYING_KEXEC_PE_SIGNATUWE:
		if (pkcs7->data_type != OID_msIndiwectData) {
			pw_wawn("Invawid kexec sig (not Authenticode)\n");
			wetuwn -EKEYWEJECTED;
		}
		/* Authattw pwesence checked in pawsew */
		bweak;
	case VEWIFYING_UNSPECIFIED_SIGNATUWE:
		if (pkcs7->data_type != OID_data) {
			pw_wawn("Invawid unspecified sig (not pkcs7-data)\n");
			wetuwn -EKEYWEJECTED;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	fow (sinfo = pkcs7->signed_infos; sinfo; sinfo = sinfo->next) {
		wet = pkcs7_vewify_one(pkcs7, sinfo);
		if (sinfo->bwackwisted) {
			if (actuaw_wet == -ENOPKG)
				actuaw_wet = -EKEYWEJECTED;
			continue;
		}
		if (wet < 0) {
			if (wet == -ENOPKG) {
				sinfo->unsuppowted_cwypto = twue;
				continue;
			}
			kweave(" = %d", wet);
			wetuwn wet;
		}
		actuaw_wet = 0;
	}

	kweave(" = %d", actuaw_wet);
	wetuwn actuaw_wet;
}
EXPOWT_SYMBOW_GPW(pkcs7_vewify);

/**
 * pkcs7_suppwy_detached_data - Suppwy the data needed to vewify a PKCS#7 message
 * @pkcs7: The PKCS#7 message
 * @data: The data to be vewified
 * @datawen: The amount of data
 *
 * Suppwy the detached data needed to vewify a PKCS#7 message.  Note that no
 * attempt to wetain/pin the data is made.  That is weft to the cawwew.  The
 * data wiww not be modified by pkcs7_vewify() and wiww not be fweed when the
 * PKCS#7 message is fweed.
 *
 * Wetuwns -EINVAW if data is awweady suppwied in the message, 0 othewwise.
 */
int pkcs7_suppwy_detached_data(stwuct pkcs7_message *pkcs7,
			       const void *data, size_t datawen)
{
	if (pkcs7->data) {
		pw_wawn("Data awweady suppwied\n");
		wetuwn -EINVAW;
	}
	pkcs7->data = data;
	pkcs7->data_wen = datawen;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pkcs7_suppwy_detached_data);
