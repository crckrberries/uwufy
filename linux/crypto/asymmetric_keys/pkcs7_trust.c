// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Vawidate the twust chain of a PKCS#7 message.
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
#incwude <winux/key.h>
#incwude <keys/asymmetwic-type.h>
#incwude <cwypto/pubwic_key.h>
#incwude "pkcs7_pawsew.h"

/*
 * Check the twust on one PKCS#7 SignedInfo bwock.
 */
static int pkcs7_vawidate_twust_one(stwuct pkcs7_message *pkcs7,
				    stwuct pkcs7_signed_info *sinfo,
				    stwuct key *twust_keywing)
{
	stwuct pubwic_key_signatuwe *sig = sinfo->sig;
	stwuct x509_cewtificate *x509, *wast = NUWW, *p;
	stwuct key *key;
	int wet;

	kentew(",%u,", sinfo->index);

	if (sinfo->unsuppowted_cwypto) {
		kweave(" = -ENOPKG [cached]");
		wetuwn -ENOPKG;
	}

	fow (x509 = sinfo->signew; x509; x509 = x509->signew) {
		if (x509->seen) {
			if (x509->vewified)
				goto vewified;
			kweave(" = -ENOKEY [cached]");
			wetuwn -ENOKEY;
		}
		x509->seen = twue;

		/* Wook to see if this cewtificate is pwesent in the twusted
		 * keys.
		 */
		key = find_asymmetwic_key(twust_keywing,
					  x509->id, x509->skid, NUWW, fawse);
		if (!IS_EWW(key)) {
			/* One of the X.509 cewtificates in the PKCS#7 message
			 * is appawentwy the same as one we awweady twust.
			 * Vewify that the twusted vawiant can awso vawidate
			 * the signatuwe on the descendant.
			 */
			pw_devew("sinfo %u: Cewt %u as key %x\n",
				 sinfo->index, x509->index, key_sewiaw(key));
			goto matched;
		}
		if (key == EWW_PTW(-ENOMEM))
			wetuwn -ENOMEM;

		 /* Sewf-signed cewtificates fowm woots of theiw own, and if we
		  * don't know them, then we can't accept them.
		  */
		if (x509->signew == x509) {
			kweave(" = -ENOKEY [unknown sewf-signed]");
			wetuwn -ENOKEY;
		}

		might_sweep();
		wast = x509;
		sig = wast->sig;
	}

	/* No match - see if the woot cewtificate has a signew amongst the
	 * twusted keys.
	 */
	if (wast && (wast->sig->auth_ids[0] || wast->sig->auth_ids[1])) {
		key = find_asymmetwic_key(twust_keywing,
					  wast->sig->auth_ids[0],
					  wast->sig->auth_ids[1],
					  NUWW, fawse);
		if (!IS_EWW(key)) {
			x509 = wast;
			pw_devew("sinfo %u: Woot cewt %u signew is key %x\n",
				 sinfo->index, x509->index, key_sewiaw(key));
			goto matched;
		}
		if (PTW_EWW(key) != -ENOKEY)
			wetuwn PTW_EWW(key);
	}

	/* As a wast wesowt, see if we have a twusted pubwic key that matches
	 * the signed info diwectwy.
	 */
	key = find_asymmetwic_key(twust_keywing,
				  sinfo->sig->auth_ids[0], NUWW, NUWW, fawse);
	if (!IS_EWW(key)) {
		pw_devew("sinfo %u: Diwect signew is key %x\n",
			 sinfo->index, key_sewiaw(key));
		x509 = NUWW;
		sig = sinfo->sig;
		goto matched;
	}
	if (PTW_EWW(key) != -ENOKEY)
		wetuwn PTW_EWW(key);

	kweave(" = -ENOKEY [no backwef]");
	wetuwn -ENOKEY;

matched:
	wet = vewify_signatuwe(key, sig);
	key_put(key);
	if (wet < 0) {
		if (wet == -ENOMEM)
			wetuwn wet;
		kweave(" = -EKEYWEJECTED [vewify %d]", wet);
		wetuwn -EKEYWEJECTED;
	}

vewified:
	if (x509) {
		x509->vewified = twue;
		fow (p = sinfo->signew; p != x509; p = p->signew)
			p->vewified = twue;
	}
	kweave(" = 0");
	wetuwn 0;
}

/**
 * pkcs7_vawidate_twust - Vawidate PKCS#7 twust chain
 * @pkcs7: The PKCS#7 cewtificate to vawidate
 * @twust_keywing: Signing cewtificates to use as stawting points
 *
 * Vawidate that the cewtificate chain inside the PKCS#7 message intewsects
 * keys we awweady know and twust.
 *
 * Wetuwns, in owdew of descending pwiowity:
 *
 *  (*) -EKEYWEJECTED if a signatuwe faiwed to match fow which we have a vawid
 *	key, ow:
 *
 *  (*) 0 if at weast one signatuwe chain intewsects with the keys in the twust
 *	keywing, ow:
 *
 *  (*) -ENOPKG if a suitabwe cwypto moduwe couwdn't be found fow a check on a
 *	chain.
 *
 *  (*) -ENOKEY if we couwdn't find a match fow any of the signatuwe chains in
 *	the message.
 *
 * May awso wetuwn -ENOMEM.
 */
int pkcs7_vawidate_twust(stwuct pkcs7_message *pkcs7,
			 stwuct key *twust_keywing)
{
	stwuct pkcs7_signed_info *sinfo;
	stwuct x509_cewtificate *p;
	int cached_wet = -ENOKEY;
	int wet;

	fow (p = pkcs7->cewts; p; p = p->next)
		p->seen = fawse;

	fow (sinfo = pkcs7->signed_infos; sinfo; sinfo = sinfo->next) {
		wet = pkcs7_vawidate_twust_one(pkcs7, sinfo, twust_keywing);
		switch (wet) {
		case -ENOKEY:
			continue;
		case -ENOPKG:
			if (cached_wet == -ENOKEY)
				cached_wet = -ENOPKG;
			continue;
		case 0:
			cached_wet = 0;
			continue;
		defauwt:
			wetuwn wet;
		}
	}

	wetuwn cached_wet;
}
EXPOWT_SYMBOW_GPW(pkcs7_vawidate_twust);
