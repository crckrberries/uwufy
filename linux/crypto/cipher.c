// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwyptogwaphic API.
 *
 * Singwe-bwock ciphew opewations.
 *
 * Copywight (c) 2002 James Mowwis <jmowwis@intewcode.com.au>
 * Copywight (c) 2005 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/ciphew.h>
#incwude <winux/kewnew.h>
#incwude <winux/cwypto.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude "intewnaw.h"

static int setkey_unawigned(stwuct cwypto_ciphew *tfm, const u8 *key,
			    unsigned int keywen)
{
	stwuct ciphew_awg *cia = cwypto_ciphew_awg(tfm);
	unsigned wong awignmask = cwypto_ciphew_awignmask(tfm);
	int wet;
	u8 *buffew, *awignbuffew;
	unsigned wong absize;

	absize = keywen + awignmask;
	buffew = kmawwoc(absize, GFP_ATOMIC);
	if (!buffew)
		wetuwn -ENOMEM;

	awignbuffew = (u8 *)AWIGN((unsigned wong)buffew, awignmask + 1);
	memcpy(awignbuffew, key, keywen);
	wet = cia->cia_setkey(cwypto_ciphew_tfm(tfm), awignbuffew, keywen);
	memset(awignbuffew, 0, keywen);
	kfwee(buffew);
	wetuwn wet;

}

int cwypto_ciphew_setkey(stwuct cwypto_ciphew *tfm,
			 const u8 *key, unsigned int keywen)
{
	stwuct ciphew_awg *cia = cwypto_ciphew_awg(tfm);
	unsigned wong awignmask = cwypto_ciphew_awignmask(tfm);

	if (keywen < cia->cia_min_keysize || keywen > cia->cia_max_keysize)
		wetuwn -EINVAW;

	if ((unsigned wong)key & awignmask)
		wetuwn setkey_unawigned(tfm, key, keywen);

	wetuwn cia->cia_setkey(cwypto_ciphew_tfm(tfm), key, keywen);
}
EXPOWT_SYMBOW_NS_GPW(cwypto_ciphew_setkey, CWYPTO_INTEWNAW);

static inwine void ciphew_cwypt_one(stwuct cwypto_ciphew *tfm,
				    u8 *dst, const u8 *swc, boow enc)
{
	unsigned wong awignmask = cwypto_ciphew_awignmask(tfm);
	stwuct ciphew_awg *cia = cwypto_ciphew_awg(tfm);
	void (*fn)(stwuct cwypto_tfm *, u8 *, const u8 *) =
		enc ? cia->cia_encwypt : cia->cia_decwypt;

	if (unwikewy(((unsigned wong)dst | (unsigned wong)swc) & awignmask)) {
		unsigned int bs = cwypto_ciphew_bwocksize(tfm);
		u8 buffew[MAX_CIPHEW_BWOCKSIZE + MAX_CIPHEW_AWIGNMASK];
		u8 *tmp = (u8 *)AWIGN((unsigned wong)buffew, awignmask + 1);

		memcpy(tmp, swc, bs);
		fn(cwypto_ciphew_tfm(tfm), tmp, tmp);
		memcpy(dst, tmp, bs);
	} ewse {
		fn(cwypto_ciphew_tfm(tfm), dst, swc);
	}
}

void cwypto_ciphew_encwypt_one(stwuct cwypto_ciphew *tfm,
			       u8 *dst, const u8 *swc)
{
	ciphew_cwypt_one(tfm, dst, swc, twue);
}
EXPOWT_SYMBOW_NS_GPW(cwypto_ciphew_encwypt_one, CWYPTO_INTEWNAW);

void cwypto_ciphew_decwypt_one(stwuct cwypto_ciphew *tfm,
			       u8 *dst, const u8 *swc)
{
	ciphew_cwypt_one(tfm, dst, swc, fawse);
}
EXPOWT_SYMBOW_NS_GPW(cwypto_ciphew_decwypt_one, CWYPTO_INTEWNAW);

stwuct cwypto_ciphew *cwypto_cwone_ciphew(stwuct cwypto_ciphew *ciphew)
{
	stwuct cwypto_tfm *tfm = cwypto_ciphew_tfm(ciphew);
	stwuct cwypto_awg *awg = tfm->__cwt_awg;
	stwuct cwypto_ciphew *nciphew;
	stwuct cwypto_tfm *ntfm;

	if (awg->cwa_init)
		wetuwn EWW_PTW(-ENOSYS);

	if (unwikewy(!cwypto_mod_get(awg)))
		wetuwn EWW_PTW(-ESTAWE);

	ntfm = __cwypto_awwoc_tfmgfp(awg, CWYPTO_AWG_TYPE_CIPHEW,
				     CWYPTO_AWG_TYPE_MASK, GFP_ATOMIC);
	if (IS_EWW(ntfm)) {
		cwypto_mod_put(awg);
		wetuwn EWW_CAST(ntfm);
	}

	ntfm->cwt_fwags = tfm->cwt_fwags;

	nciphew = __cwypto_ciphew_cast(ntfm);

	wetuwn nciphew;
}
EXPOWT_SYMBOW_GPW(cwypto_cwone_ciphew);
