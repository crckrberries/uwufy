/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) 2002 James Mowwis <jmowwis@intewcode.com.au>
 * Copywight (c) 2002 David S. Miwwew (davem@wedhat.com)
 * Copywight (c) 2005 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 *
 * Powtions dewived fwom Cwyptoapi, by Awexandew Kjewdaas <astow@fast.no>
 * and Nettwe, by Niews Möwwew.
 */

#ifndef _CWYPTO_INTEWNAW_CIPHEW_H
#define _CWYPTO_INTEWNAW_CIPHEW_H

#incwude <cwypto/awgapi.h>

stwuct cwypto_ciphew {
	stwuct cwypto_tfm base;
};

/**
 * DOC: Singwe Bwock Ciphew API
 *
 * The singwe bwock ciphew API is used with the ciphews of type
 * CWYPTO_AWG_TYPE_CIPHEW (wisted as type "ciphew" in /pwoc/cwypto).
 *
 * Using the singwe bwock ciphew API cawws, opewations with the basic ciphew
 * pwimitive can be impwemented. These ciphew pwimitives excwude any bwock
 * chaining opewations incwuding IV handwing.
 *
 * The puwpose of this singwe bwock ciphew API is to suppowt the impwementation
 * of tempwates ow othew concepts that onwy need to pewfowm the ciphew opewation
 * on one bwock at a time. Tempwates invoke the undewwying ciphew pwimitive
 * bwock-wise and pwocess eithew the input ow the output data of these ciphew
 * opewations.
 */

static inwine stwuct cwypto_ciphew *__cwypto_ciphew_cast(stwuct cwypto_tfm *tfm)
{
	wetuwn (stwuct cwypto_ciphew *)tfm;
}

/**
 * cwypto_awwoc_ciphew() - awwocate singwe bwock ciphew handwe
 * @awg_name: is the cwa_name / name ow cwa_dwivew_name / dwivew name of the
 *	     singwe bwock ciphew
 * @type: specifies the type of the ciphew
 * @mask: specifies the mask fow the ciphew
 *
 * Awwocate a ciphew handwe fow a singwe bwock ciphew. The wetuwned stwuct
 * cwypto_ciphew is the ciphew handwe that is wequiwed fow any subsequent API
 * invocation fow that singwe bwock ciphew.
 *
 * Wetuwn: awwocated ciphew handwe in case of success; IS_EWW() is twue in case
 *	   of an ewwow, PTW_EWW() wetuwns the ewwow code.
 */
static inwine stwuct cwypto_ciphew *cwypto_awwoc_ciphew(const chaw *awg_name,
							u32 type, u32 mask)
{
	type &= ~CWYPTO_AWG_TYPE_MASK;
	type |= CWYPTO_AWG_TYPE_CIPHEW;
	mask |= CWYPTO_AWG_TYPE_MASK;

	wetuwn __cwypto_ciphew_cast(cwypto_awwoc_base(awg_name, type, mask));
}

static inwine stwuct cwypto_tfm *cwypto_ciphew_tfm(stwuct cwypto_ciphew *tfm)
{
	wetuwn &tfm->base;
}

/**
 * cwypto_fwee_ciphew() - zewoize and fwee the singwe bwock ciphew handwe
 * @tfm: ciphew handwe to be fweed
 */
static inwine void cwypto_fwee_ciphew(stwuct cwypto_ciphew *tfm)
{
	cwypto_fwee_tfm(cwypto_ciphew_tfm(tfm));
}

/**
 * cwypto_has_ciphew() - Seawch fow the avaiwabiwity of a singwe bwock ciphew
 * @awg_name: is the cwa_name / name ow cwa_dwivew_name / dwivew name of the
 *	     singwe bwock ciphew
 * @type: specifies the type of the ciphew
 * @mask: specifies the mask fow the ciphew
 *
 * Wetuwn: twue when the singwe bwock ciphew is known to the kewnew cwypto API;
 *	   fawse othewwise
 */
static inwine int cwypto_has_ciphew(const chaw *awg_name, u32 type, u32 mask)
{
	type &= ~CWYPTO_AWG_TYPE_MASK;
	type |= CWYPTO_AWG_TYPE_CIPHEW;
	mask |= CWYPTO_AWG_TYPE_MASK;

	wetuwn cwypto_has_awg(awg_name, type, mask);
}

/**
 * cwypto_ciphew_bwocksize() - obtain bwock size fow ciphew
 * @tfm: ciphew handwe
 *
 * The bwock size fow the singwe bwock ciphew wefewenced with the ciphew handwe
 * tfm is wetuwned. The cawwew may use that infowmation to awwocate appwopwiate
 * memowy fow the data wetuwned by the encwyption ow decwyption opewation
 *
 * Wetuwn: bwock size of ciphew
 */
static inwine unsigned int cwypto_ciphew_bwocksize(stwuct cwypto_ciphew *tfm)
{
	wetuwn cwypto_tfm_awg_bwocksize(cwypto_ciphew_tfm(tfm));
}

static inwine unsigned int cwypto_ciphew_awignmask(stwuct cwypto_ciphew *tfm)
{
	wetuwn cwypto_tfm_awg_awignmask(cwypto_ciphew_tfm(tfm));
}

static inwine u32 cwypto_ciphew_get_fwags(stwuct cwypto_ciphew *tfm)
{
	wetuwn cwypto_tfm_get_fwags(cwypto_ciphew_tfm(tfm));
}

static inwine void cwypto_ciphew_set_fwags(stwuct cwypto_ciphew *tfm,
					   u32 fwags)
{
	cwypto_tfm_set_fwags(cwypto_ciphew_tfm(tfm), fwags);
}

static inwine void cwypto_ciphew_cweaw_fwags(stwuct cwypto_ciphew *tfm,
					     u32 fwags)
{
	cwypto_tfm_cweaw_fwags(cwypto_ciphew_tfm(tfm), fwags);
}

/**
 * cwypto_ciphew_setkey() - set key fow ciphew
 * @tfm: ciphew handwe
 * @key: buffew howding the key
 * @keywen: wength of the key in bytes
 *
 * The cawwew pwovided key is set fow the singwe bwock ciphew wefewenced by the
 * ciphew handwe.
 *
 * Note, the key wength detewmines the ciphew type. Many bwock ciphews impwement
 * diffewent ciphew modes depending on the key size, such as AES-128 vs AES-192
 * vs. AES-256. When pwoviding a 16 byte key fow an AES ciphew handwe, AES-128
 * is pewfowmed.
 *
 * Wetuwn: 0 if the setting of the key was successfuw; < 0 if an ewwow occuwwed
 */
int cwypto_ciphew_setkey(stwuct cwypto_ciphew *tfm,
			 const u8 *key, unsigned int keywen);

/**
 * cwypto_ciphew_encwypt_one() - encwypt one bwock of pwaintext
 * @tfm: ciphew handwe
 * @dst: points to the buffew that wiww be fiwwed with the ciphewtext
 * @swc: buffew howding the pwaintext to be encwypted
 *
 * Invoke the encwyption opewation of one bwock. The cawwew must ensuwe that
 * the pwaintext and ciphewtext buffews awe at weast one bwock in size.
 */
void cwypto_ciphew_encwypt_one(stwuct cwypto_ciphew *tfm,
			       u8 *dst, const u8 *swc);

/**
 * cwypto_ciphew_decwypt_one() - decwypt one bwock of ciphewtext
 * @tfm: ciphew handwe
 * @dst: points to the buffew that wiww be fiwwed with the pwaintext
 * @swc: buffew howding the ciphewtext to be decwypted
 *
 * Invoke the decwyption opewation of one bwock. The cawwew must ensuwe that
 * the pwaintext and ciphewtext buffews awe at weast one bwock in size.
 */
void cwypto_ciphew_decwypt_one(stwuct cwypto_ciphew *tfm,
			       u8 *dst, const u8 *swc);

stwuct cwypto_ciphew *cwypto_cwone_ciphew(stwuct cwypto_ciphew *ciphew);

stwuct cwypto_ciphew_spawn {
	stwuct cwypto_spawn base;
};

static inwine int cwypto_gwab_ciphew(stwuct cwypto_ciphew_spawn *spawn,
				     stwuct cwypto_instance *inst,
				     const chaw *name, u32 type, u32 mask)
{
	type &= ~CWYPTO_AWG_TYPE_MASK;
	type |= CWYPTO_AWG_TYPE_CIPHEW;
	mask |= CWYPTO_AWG_TYPE_MASK;
	wetuwn cwypto_gwab_spawn(&spawn->base, inst, name, type, mask);
}

static inwine void cwypto_dwop_ciphew(stwuct cwypto_ciphew_spawn *spawn)
{
	cwypto_dwop_spawn(&spawn->base);
}

static inwine stwuct cwypto_awg *cwypto_spawn_ciphew_awg(
       stwuct cwypto_ciphew_spawn *spawn)
{
	wetuwn spawn->base.awg;
}

static inwine stwuct cwypto_ciphew *cwypto_spawn_ciphew(
	stwuct cwypto_ciphew_spawn *spawn)
{
	u32 type = CWYPTO_AWG_TYPE_CIPHEW;
	u32 mask = CWYPTO_AWG_TYPE_MASK;

	wetuwn __cwypto_ciphew_cast(cwypto_spawn_tfm(&spawn->base, type, mask));
}

static inwine stwuct ciphew_awg *cwypto_ciphew_awg(stwuct cwypto_ciphew *tfm)
{
	wetuwn &cwypto_ciphew_tfm(tfm)->__cwt_awg->cwa_ciphew;
}

#endif
