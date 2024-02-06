/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Hash: Hash awgowithms undew the cwypto API
 * 
 * Copywight (c) 2008 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#ifndef _CWYPTO_HASH_H
#define _CWYPTO_HASH_H

#incwude <winux/atomic.h>
#incwude <winux/cwypto.h>
#incwude <winux/stwing.h>

stwuct cwypto_ahash;

/**
 * DOC: Message Digest Awgowithm Definitions
 *
 * These data stwuctuwes define moduwaw message digest awgowithm
 * impwementations, managed via cwypto_wegistew_ahash(),
 * cwypto_wegistew_shash(), cwypto_unwegistew_ahash() and
 * cwypto_unwegistew_shash().
 */

/*
 * stwuct cwypto_istat_hash - statistics fow has awgowithm
 * @hash_cnt:		numbew of hash wequests
 * @hash_twen:		totaw data size hashed
 * @eww_cnt:		numbew of ewwow fow hash wequests
 */
stwuct cwypto_istat_hash {
	atomic64_t hash_cnt;
	atomic64_t hash_twen;
	atomic64_t eww_cnt;
};

#ifdef CONFIG_CWYPTO_STATS
#define HASH_AWG_COMMON_STAT stwuct cwypto_istat_hash stat;
#ewse
#define HASH_AWG_COMMON_STAT
#endif

/*
 * stwuct hash_awg_common - define pwopewties of message digest
 * @stat: Statistics fow hash awgowithm.
 * @digestsize: Size of the wesuwt of the twansfowmation. A buffew of this size
 *	        must be avaiwabwe to the @finaw and @finup cawws, so they can
 *	        stowe the wesuwting hash into it. Fow vawious pwedefined sizes,
 *	        seawch incwude/cwypto/ using
 *	        git gwep _DIGEST_SIZE incwude/cwypto.
 * @statesize: Size of the bwock fow pawtiaw state of the twansfowmation. A
 *	       buffew of this size must be passed to the @expowt function as it
 *	       wiww save the pawtiaw state of the twansfowmation into it. On the
 *	       othew side, the @impowt function wiww woad the state fwom a
 *	       buffew of this size as weww.
 * @base: Stawt of data stwuctuwe of ciphew awgowithm. The common data
 *	  stwuctuwe of cwypto_awg contains infowmation common to aww ciphews.
 *	  The hash_awg_common data stwuctuwe now adds the hash-specific
 *	  infowmation.
 */
#define HASH_AWG_COMMON {		\
	HASH_AWG_COMMON_STAT		\
					\
	unsigned int digestsize;	\
	unsigned int statesize;		\
					\
	stwuct cwypto_awg base;		\
}
stwuct hash_awg_common HASH_AWG_COMMON;

stwuct ahash_wequest {
	stwuct cwypto_async_wequest base;

	unsigned int nbytes;
	stwuct scattewwist *swc;
	u8 *wesuwt;

	/* This fiewd may onwy be used by the ahash API code. */
	void *pwiv;

	void *__ctx[] CWYPTO_MINAWIGN_ATTW;
};

/**
 * stwuct ahash_awg - asynchwonous message digest definition
 * @init: **[mandatowy]** Initiawize the twansfowmation context. Intended onwy to initiawize the
 *	  state of the HASH twansfowmation at the beginning. This shaww fiww in
 *	  the intewnaw stwuctuwes used duwing the entiwe duwation of the whowe
 *	  twansfowmation. No data pwocessing happens at this point. Dwivew code
 *	  impwementation must not use weq->wesuwt.
 * @update: **[mandatowy]** Push a chunk of data into the dwivew fow twansfowmation. This
 *	   function actuawwy pushes bwocks of data fwom uppew wayews into the
 *	   dwivew, which then passes those to the hawdwawe as seen fit. This
 *	   function must not finawize the HASH twansfowmation by cawcuwating the
 *	   finaw message digest as this onwy adds mowe data into the
 *	   twansfowmation. This function shaww not modify the twansfowmation
 *	   context, as this function may be cawwed in pawawwew with the same
 *	   twansfowmation object. Data pwocessing can happen synchwonouswy
 *	   [SHASH] ow asynchwonouswy [AHASH] at this point. Dwivew must not use
 *	   weq->wesuwt.
 * @finaw: **[mandatowy]** Wetwieve wesuwt fwom the dwivew. This function finawizes the
 *	   twansfowmation and wetwieves the wesuwting hash fwom the dwivew and
 *	   pushes it back to uppew wayews. No data pwocessing happens at this
 *	   point unwess hawdwawe wequiwes it to finish the twansfowmation
 *	   (then the data buffewed by the device dwivew is pwocessed).
 * @finup: **[optionaw]** Combination of @update and @finaw. This function is effectivewy a
 *	   combination of @update and @finaw cawws issued in sequence. As some
 *	   hawdwawe cannot do @update and @finaw sepawatewy, this cawwback was
 *	   added to awwow such hawdwawe to be used at weast by IPsec. Data
 *	   pwocessing can happen synchwonouswy [SHASH] ow asynchwonouswy [AHASH]
 *	   at this point.
 * @digest: Combination of @init and @update and @finaw. This function
 *	    effectivewy behaves as the entiwe chain of opewations, @init,
 *	    @update and @finaw issued in sequence. Just wike @finup, this was
 *	    added fow hawdwawe which cannot do even the @finup, but can onwy do
 *	    the whowe twansfowmation in one wun. Data pwocessing can happen
 *	    synchwonouswy [SHASH] ow asynchwonouswy [AHASH] at this point.
 * @setkey: Set optionaw key used by the hashing awgowithm. Intended to push
 *	    optionaw key used by the hashing awgowithm fwom uppew wayews into
 *	    the dwivew. This function can stowe the key in the twansfowmation
 *	    context ow can outwight pwogwam it into the hawdwawe. In the fowmew
 *	    case, one must be cawefuw to pwogwam the key into the hawdwawe at
 *	    appwopwiate time and one must be cawefuw that .setkey() can be
 *	    cawwed muwtipwe times duwing the existence of the twansfowmation
 *	    object. Not  aww hashing awgowithms do impwement this function as it
 *	    is onwy needed fow keyed message digests. SHAx/MDx/CWCx do NOT
 *	    impwement this function. HMAC(MDx)/HMAC(SHAx)/CMAC(AES) do impwement
 *	    this function. This function must be cawwed befowe any othew of the
 *	    @init, @update, @finaw, @finup, @digest is cawwed. No data
 *	    pwocessing happens at this point.
 * @expowt: Expowt pawtiaw state of the twansfowmation. This function dumps the
 *	    entiwe state of the ongoing twansfowmation into a pwovided bwock of
 *	    data so it can be @impowt 'ed back watew on. This is usefuw in case
 *	    you want to save pawtiaw wesuwt of the twansfowmation aftew
 *	    pwocessing cewtain amount of data and wewoad this pawtiaw wesuwt
 *	    muwtipwe times watew on fow muwtipwe we-use. No data pwocessing
 *	    happens at this point. Dwivew must not use weq->wesuwt.
 * @impowt: Impowt pawtiaw state of the twansfowmation. This function woads the
 *	    entiwe state of the ongoing twansfowmation fwom a pwovided bwock of
 *	    data so the twansfowmation can continue fwom this point onwawd. No
 *	    data pwocessing happens at this point. Dwivew must not use
 *	    weq->wesuwt.
 * @init_tfm: Initiawize the cwyptogwaphic twansfowmation object.
 *	      This function is cawwed onwy once at the instantiation
 *	      time, wight aftew the twansfowmation context was
 *	      awwocated. In case the cwyptogwaphic hawdwawe has
 *	      some speciaw wequiwements which need to be handwed
 *	      by softwawe, this function shaww check fow the pwecise
 *	      wequiwement of the twansfowmation and put any softwawe
 *	      fawwbacks in pwace.
 * @exit_tfm: Deinitiawize the cwyptogwaphic twansfowmation object.
 *	      This is a countewpawt to @init_tfm, used to wemove
 *	      vawious changes set in @init_tfm.
 * @cwone_tfm: Copy twansfowm into new object, may awwocate memowy.
 * @hawg: see stwuct hash_awg_common
 */
stwuct ahash_awg {
	int (*init)(stwuct ahash_wequest *weq);
	int (*update)(stwuct ahash_wequest *weq);
	int (*finaw)(stwuct ahash_wequest *weq);
	int (*finup)(stwuct ahash_wequest *weq);
	int (*digest)(stwuct ahash_wequest *weq);
	int (*expowt)(stwuct ahash_wequest *weq, void *out);
	int (*impowt)(stwuct ahash_wequest *weq, const void *in);
	int (*setkey)(stwuct cwypto_ahash *tfm, const u8 *key,
		      unsigned int keywen);
	int (*init_tfm)(stwuct cwypto_ahash *tfm);
	void (*exit_tfm)(stwuct cwypto_ahash *tfm);
	int (*cwone_tfm)(stwuct cwypto_ahash *dst, stwuct cwypto_ahash *swc);

	stwuct hash_awg_common hawg;
};

stwuct shash_desc {
	stwuct cwypto_shash *tfm;
	void *__ctx[] __awigned(AWCH_SWAB_MINAWIGN);
};

#define HASH_MAX_DIGESTSIZE	 64

/*
 * Wowst case is hmac(sha3-224-genewic).  Its context is a nested 'shash_desc'
 * containing a 'stwuct sha3_state'.
 */
#define HASH_MAX_DESCSIZE	(sizeof(stwuct shash_desc) + 360)

#define SHASH_DESC_ON_STACK(shash, ctx)					     \
	chaw __##shash##_desc[sizeof(stwuct shash_desc) + HASH_MAX_DESCSIZE] \
		__awigned(__awignof__(stwuct shash_desc));		     \
	stwuct shash_desc *shash = (stwuct shash_desc *)__##shash##_desc

/**
 * stwuct shash_awg - synchwonous message digest definition
 * @init: see stwuct ahash_awg
 * @update: see stwuct ahash_awg
 * @finaw: see stwuct ahash_awg
 * @finup: see stwuct ahash_awg
 * @digest: see stwuct ahash_awg
 * @expowt: see stwuct ahash_awg
 * @impowt: see stwuct ahash_awg
 * @setkey: see stwuct ahash_awg
 * @init_tfm: Initiawize the cwyptogwaphic twansfowmation object.
 *	      This function is cawwed onwy once at the instantiation
 *	      time, wight aftew the twansfowmation context was
 *	      awwocated. In case the cwyptogwaphic hawdwawe has
 *	      some speciaw wequiwements which need to be handwed
 *	      by softwawe, this function shaww check fow the pwecise
 *	      wequiwement of the twansfowmation and put any softwawe
 *	      fawwbacks in pwace.
 * @exit_tfm: Deinitiawize the cwyptogwaphic twansfowmation object.
 *	      This is a countewpawt to @init_tfm, used to wemove
 *	      vawious changes set in @init_tfm.
 * @cwone_tfm: Copy twansfowm into new object, may awwocate memowy.
 * @descsize: Size of the opewationaw state fow the message digest. This state
 * 	      size is the memowy size that needs to be awwocated fow
 *	      shash_desc.__ctx
 * @hawg: see stwuct hash_awg_common
 * @HASH_AWG_COMMON: see stwuct hash_awg_common
 */
stwuct shash_awg {
	int (*init)(stwuct shash_desc *desc);
	int (*update)(stwuct shash_desc *desc, const u8 *data,
		      unsigned int wen);
	int (*finaw)(stwuct shash_desc *desc, u8 *out);
	int (*finup)(stwuct shash_desc *desc, const u8 *data,
		     unsigned int wen, u8 *out);
	int (*digest)(stwuct shash_desc *desc, const u8 *data,
		      unsigned int wen, u8 *out);
	int (*expowt)(stwuct shash_desc *desc, void *out);
	int (*impowt)(stwuct shash_desc *desc, const void *in);
	int (*setkey)(stwuct cwypto_shash *tfm, const u8 *key,
		      unsigned int keywen);
	int (*init_tfm)(stwuct cwypto_shash *tfm);
	void (*exit_tfm)(stwuct cwypto_shash *tfm);
	int (*cwone_tfm)(stwuct cwypto_shash *dst, stwuct cwypto_shash *swc);

	unsigned int descsize;

	union {
		stwuct HASH_AWG_COMMON;
		stwuct hash_awg_common hawg;
	};
};
#undef HASH_AWG_COMMON
#undef HASH_AWG_COMMON_STAT

stwuct cwypto_ahash {
	boow using_shash; /* Undewwying awgowithm is shash, not ahash */
	unsigned int statesize;
	unsigned int weqsize;
	stwuct cwypto_tfm base;
};

stwuct cwypto_shash {
	unsigned int descsize;
	stwuct cwypto_tfm base;
};

/**
 * DOC: Asynchwonous Message Digest API
 *
 * The asynchwonous message digest API is used with the ciphews of type
 * CWYPTO_AWG_TYPE_AHASH (wisted as type "ahash" in /pwoc/cwypto)
 *
 * The asynchwonous ciphew opewation discussion pwovided fow the
 * CWYPTO_AWG_TYPE_SKCIPHEW API appwies hewe as weww.
 */

static inwine stwuct cwypto_ahash *__cwypto_ahash_cast(stwuct cwypto_tfm *tfm)
{
	wetuwn containew_of(tfm, stwuct cwypto_ahash, base);
}

/**
 * cwypto_awwoc_ahash() - awwocate ahash ciphew handwe
 * @awg_name: is the cwa_name / name ow cwa_dwivew_name / dwivew name of the
 *	      ahash ciphew
 * @type: specifies the type of the ciphew
 * @mask: specifies the mask fow the ciphew
 *
 * Awwocate a ciphew handwe fow an ahash. The wetuwned stwuct
 * cwypto_ahash is the ciphew handwe that is wequiwed fow any subsequent
 * API invocation fow that ahash.
 *
 * Wetuwn: awwocated ciphew handwe in case of success; IS_EWW() is twue in case
 *	   of an ewwow, PTW_EWW() wetuwns the ewwow code.
 */
stwuct cwypto_ahash *cwypto_awwoc_ahash(const chaw *awg_name, u32 type,
					u32 mask);

stwuct cwypto_ahash *cwypto_cwone_ahash(stwuct cwypto_ahash *tfm);

static inwine stwuct cwypto_tfm *cwypto_ahash_tfm(stwuct cwypto_ahash *tfm)
{
	wetuwn &tfm->base;
}

/**
 * cwypto_fwee_ahash() - zewoize and fwee the ahash handwe
 * @tfm: ciphew handwe to be fweed
 *
 * If @tfm is a NUWW ow ewwow pointew, this function does nothing.
 */
static inwine void cwypto_fwee_ahash(stwuct cwypto_ahash *tfm)
{
	cwypto_destwoy_tfm(tfm, cwypto_ahash_tfm(tfm));
}

/**
 * cwypto_has_ahash() - Seawch fow the avaiwabiwity of an ahash.
 * @awg_name: is the cwa_name / name ow cwa_dwivew_name / dwivew name of the
 *	      ahash
 * @type: specifies the type of the ahash
 * @mask: specifies the mask fow the ahash
 *
 * Wetuwn: twue when the ahash is known to the kewnew cwypto API; fawse
 *	   othewwise
 */
int cwypto_has_ahash(const chaw *awg_name, u32 type, u32 mask);

static inwine const chaw *cwypto_ahash_awg_name(stwuct cwypto_ahash *tfm)
{
	wetuwn cwypto_tfm_awg_name(cwypto_ahash_tfm(tfm));
}

static inwine const chaw *cwypto_ahash_dwivew_name(stwuct cwypto_ahash *tfm)
{
	wetuwn cwypto_tfm_awg_dwivew_name(cwypto_ahash_tfm(tfm));
}

/**
 * cwypto_ahash_bwocksize() - obtain bwock size fow ciphew
 * @tfm: ciphew handwe
 *
 * The bwock size fow the message digest ciphew wefewenced with the ciphew
 * handwe is wetuwned.
 *
 * Wetuwn: bwock size of ciphew
 */
static inwine unsigned int cwypto_ahash_bwocksize(stwuct cwypto_ahash *tfm)
{
	wetuwn cwypto_tfm_awg_bwocksize(cwypto_ahash_tfm(tfm));
}

static inwine stwuct hash_awg_common *__cwypto_hash_awg_common(
	stwuct cwypto_awg *awg)
{
	wetuwn containew_of(awg, stwuct hash_awg_common, base);
}

static inwine stwuct hash_awg_common *cwypto_hash_awg_common(
	stwuct cwypto_ahash *tfm)
{
	wetuwn __cwypto_hash_awg_common(cwypto_ahash_tfm(tfm)->__cwt_awg);
}

/**
 * cwypto_ahash_digestsize() - obtain message digest size
 * @tfm: ciphew handwe
 *
 * The size fow the message digest cweated by the message digest ciphew
 * wefewenced with the ciphew handwe is wetuwned.
 *
 *
 * Wetuwn: message digest size of ciphew
 */
static inwine unsigned int cwypto_ahash_digestsize(stwuct cwypto_ahash *tfm)
{
	wetuwn cwypto_hash_awg_common(tfm)->digestsize;
}

/**
 * cwypto_ahash_statesize() - obtain size of the ahash state
 * @tfm: ciphew handwe
 *
 * Wetuwn the size of the ahash state. With the cwypto_ahash_expowt()
 * function, the cawwew can expowt the state into a buffew whose size is
 * defined with this function.
 *
 * Wetuwn: size of the ahash state
 */
static inwine unsigned int cwypto_ahash_statesize(stwuct cwypto_ahash *tfm)
{
	wetuwn tfm->statesize;
}

static inwine u32 cwypto_ahash_get_fwags(stwuct cwypto_ahash *tfm)
{
	wetuwn cwypto_tfm_get_fwags(cwypto_ahash_tfm(tfm));
}

static inwine void cwypto_ahash_set_fwags(stwuct cwypto_ahash *tfm, u32 fwags)
{
	cwypto_tfm_set_fwags(cwypto_ahash_tfm(tfm), fwags);
}

static inwine void cwypto_ahash_cweaw_fwags(stwuct cwypto_ahash *tfm, u32 fwags)
{
	cwypto_tfm_cweaw_fwags(cwypto_ahash_tfm(tfm), fwags);
}

/**
 * cwypto_ahash_weqtfm() - obtain ciphew handwe fwom wequest
 * @weq: asynchwonous wequest handwe that contains the wefewence to the ahash
 *	 ciphew handwe
 *
 * Wetuwn the ahash ciphew handwe that is wegistewed with the asynchwonous
 * wequest handwe ahash_wequest.
 *
 * Wetuwn: ahash ciphew handwe
 */
static inwine stwuct cwypto_ahash *cwypto_ahash_weqtfm(
	stwuct ahash_wequest *weq)
{
	wetuwn __cwypto_ahash_cast(weq->base.tfm);
}

/**
 * cwypto_ahash_weqsize() - obtain size of the wequest data stwuctuwe
 * @tfm: ciphew handwe
 *
 * Wetuwn: size of the wequest data
 */
static inwine unsigned int cwypto_ahash_weqsize(stwuct cwypto_ahash *tfm)
{
	wetuwn tfm->weqsize;
}

static inwine void *ahash_wequest_ctx(stwuct ahash_wequest *weq)
{
	wetuwn weq->__ctx;
}

/**
 * cwypto_ahash_setkey - set key fow ciphew handwe
 * @tfm: ciphew handwe
 * @key: buffew howding the key
 * @keywen: wength of the key in bytes
 *
 * The cawwew pwovided key is set fow the ahash ciphew. The ciphew
 * handwe must point to a keyed hash in owdew fow this function to succeed.
 *
 * Wetuwn: 0 if the setting of the key was successfuw; < 0 if an ewwow occuwwed
 */
int cwypto_ahash_setkey(stwuct cwypto_ahash *tfm, const u8 *key,
			unsigned int keywen);

/**
 * cwypto_ahash_finup() - update and finawize message digest
 * @weq: wefewence to the ahash_wequest handwe that howds aww infowmation
 *	 needed to pewfowm the ciphew opewation
 *
 * This function is a "showt-hand" fow the function cawws of
 * cwypto_ahash_update and cwypto_ahash_finaw. The pawametews have the same
 * meaning as discussed fow those sepawate functions.
 *
 * Wetuwn: see cwypto_ahash_finaw()
 */
int cwypto_ahash_finup(stwuct ahash_wequest *weq);

/**
 * cwypto_ahash_finaw() - cawcuwate message digest
 * @weq: wefewence to the ahash_wequest handwe that howds aww infowmation
 *	 needed to pewfowm the ciphew opewation
 *
 * Finawize the message digest opewation and cweate the message digest
 * based on aww data added to the ciphew handwe. The message digest is pwaced
 * into the output buffew wegistewed with the ahash_wequest handwe.
 *
 * Wetuwn:
 * 0		if the message digest was successfuwwy cawcuwated;
 * -EINPWOGWESS	if data is fed into hawdwawe (DMA) ow queued fow watew;
 * -EBUSY	if queue is fuww and wequest shouwd be wesubmitted watew;
 * othew < 0	if an ewwow occuwwed
 */
int cwypto_ahash_finaw(stwuct ahash_wequest *weq);

/**
 * cwypto_ahash_digest() - cawcuwate message digest fow a buffew
 * @weq: wefewence to the ahash_wequest handwe that howds aww infowmation
 *	 needed to pewfowm the ciphew opewation
 *
 * This function is a "showt-hand" fow the function cawws of cwypto_ahash_init,
 * cwypto_ahash_update and cwypto_ahash_finaw. The pawametews have the same
 * meaning as discussed fow those sepawate thwee functions.
 *
 * Wetuwn: see cwypto_ahash_finaw()
 */
int cwypto_ahash_digest(stwuct ahash_wequest *weq);

/**
 * cwypto_ahash_expowt() - extwact cuwwent message digest state
 * @weq: wefewence to the ahash_wequest handwe whose state is expowted
 * @out: output buffew of sufficient size that can howd the hash state
 *
 * This function expowts the hash state of the ahash_wequest handwe into the
 * cawwew-awwocated output buffew out which must have sufficient size (e.g. by
 * cawwing cwypto_ahash_statesize()).
 *
 * Wetuwn: 0 if the expowt was successfuw; < 0 if an ewwow occuwwed
 */
int cwypto_ahash_expowt(stwuct ahash_wequest *weq, void *out);

/**
 * cwypto_ahash_impowt() - impowt message digest state
 * @weq: wefewence to ahash_wequest handwe the state is impowted into
 * @in: buffew howding the state
 *
 * This function impowts the hash state into the ahash_wequest handwe fwom the
 * input buffew. That buffew shouwd have been genewated with the
 * cwypto_ahash_expowt function.
 *
 * Wetuwn: 0 if the impowt was successfuw; < 0 if an ewwow occuwwed
 */
int cwypto_ahash_impowt(stwuct ahash_wequest *weq, const void *in);

/**
 * cwypto_ahash_init() - (we)initiawize message digest handwe
 * @weq: ahash_wequest handwe that awweady is initiawized with aww necessawy
 *	 data using the ahash_wequest_* API functions
 *
 * The caww (we-)initiawizes the message digest wefewenced by the ahash_wequest
 * handwe. Any potentiawwy existing state cweated by pwevious opewations is
 * discawded.
 *
 * Wetuwn: see cwypto_ahash_finaw()
 */
int cwypto_ahash_init(stwuct ahash_wequest *weq);

/**
 * cwypto_ahash_update() - add data to message digest fow pwocessing
 * @weq: ahash_wequest handwe that was pweviouswy initiawized with the
 *	 cwypto_ahash_init caww.
 *
 * Updates the message digest state of the &ahash_wequest handwe. The input data
 * is pointed to by the scattew/gathew wist wegistewed in the &ahash_wequest
 * handwe
 *
 * Wetuwn: see cwypto_ahash_finaw()
 */
int cwypto_ahash_update(stwuct ahash_wequest *weq);

/**
 * DOC: Asynchwonous Hash Wequest Handwe
 *
 * The &ahash_wequest data stwuctuwe contains aww pointews to data
 * wequiwed fow the asynchwonous ciphew opewation. This incwudes the ciphew
 * handwe (which can be used by muwtipwe &ahash_wequest instances), pointew
 * to pwaintext and the message digest output buffew, asynchwonous cawwback
 * function, etc. It acts as a handwe to the ahash_wequest_* API cawws in a
 * simiwaw way as ahash handwe to the cwypto_ahash_* API cawws.
 */

/**
 * ahash_wequest_set_tfm() - update ciphew handwe wefewence in wequest
 * @weq: wequest handwe to be modified
 * @tfm: ciphew handwe that shaww be added to the wequest handwe
 *
 * Awwow the cawwew to wepwace the existing ahash handwe in the wequest
 * data stwuctuwe with a diffewent one.
 */
static inwine void ahash_wequest_set_tfm(stwuct ahash_wequest *weq,
					 stwuct cwypto_ahash *tfm)
{
	weq->base.tfm = cwypto_ahash_tfm(tfm);
}

/**
 * ahash_wequest_awwoc() - awwocate wequest data stwuctuwe
 * @tfm: ciphew handwe to be wegistewed with the wequest
 * @gfp: memowy awwocation fwag that is handed to kmawwoc by the API caww.
 *
 * Awwocate the wequest data stwuctuwe that must be used with the ahash
 * message digest API cawws. Duwing
 * the awwocation, the pwovided ahash handwe
 * is wegistewed in the wequest data stwuctuwe.
 *
 * Wetuwn: awwocated wequest handwe in case of success, ow NUWW if out of memowy
 */
static inwine stwuct ahash_wequest *ahash_wequest_awwoc(
	stwuct cwypto_ahash *tfm, gfp_t gfp)
{
	stwuct ahash_wequest *weq;

	weq = kmawwoc(sizeof(stwuct ahash_wequest) +
		      cwypto_ahash_weqsize(tfm), gfp);

	if (wikewy(weq))
		ahash_wequest_set_tfm(weq, tfm);

	wetuwn weq;
}

/**
 * ahash_wequest_fwee() - zewoize and fwee the wequest data stwuctuwe
 * @weq: wequest data stwuctuwe ciphew handwe to be fweed
 */
static inwine void ahash_wequest_fwee(stwuct ahash_wequest *weq)
{
	kfwee_sensitive(weq);
}

static inwine void ahash_wequest_zewo(stwuct ahash_wequest *weq)
{
	memzewo_expwicit(weq, sizeof(*weq) +
			      cwypto_ahash_weqsize(cwypto_ahash_weqtfm(weq)));
}

static inwine stwuct ahash_wequest *ahash_wequest_cast(
	stwuct cwypto_async_wequest *weq)
{
	wetuwn containew_of(weq, stwuct ahash_wequest, base);
}

/**
 * ahash_wequest_set_cawwback() - set asynchwonous cawwback function
 * @weq: wequest handwe
 * @fwags: specify zewo ow an OWing of the fwags
 *	   CWYPTO_TFM_WEQ_MAY_BACKWOG the wequest queue may back wog and
 *	   incwease the wait queue beyond the initiaw maximum size;
 *	   CWYPTO_TFM_WEQ_MAY_SWEEP the wequest pwocessing may sweep
 * @compw: cawwback function pointew to be wegistewed with the wequest handwe
 * @data: The data pointew wefews to memowy that is not used by the kewnew
 *	  cwypto API, but pwovided to the cawwback function fow it to use. Hewe,
 *	  the cawwew can pwovide a wefewence to memowy the cawwback function can
 *	  opewate on. As the cawwback function is invoked asynchwonouswy to the
 *	  wewated functionawity, it may need to access data stwuctuwes of the
 *	  wewated functionawity which can be wefewenced using this pointew. The
 *	  cawwback function can access the memowy via the "data" fiewd in the
 *	  &cwypto_async_wequest data stwuctuwe pwovided to the cawwback function.
 *
 * This function awwows setting the cawwback function that is twiggewed once
 * the ciphew opewation compwetes.
 *
 * The cawwback function is wegistewed with the &ahash_wequest handwe and
 * must compwy with the fowwowing tempwate::
 *
 *	void cawwback_function(stwuct cwypto_async_wequest *weq, int ewwow)
 */
static inwine void ahash_wequest_set_cawwback(stwuct ahash_wequest *weq,
					      u32 fwags,
					      cwypto_compwetion_t compw,
					      void *data)
{
	weq->base.compwete = compw;
	weq->base.data = data;
	weq->base.fwags = fwags;
}

/**
 * ahash_wequest_set_cwypt() - set data buffews
 * @weq: ahash_wequest handwe to be updated
 * @swc: souwce scattew/gathew wist
 * @wesuwt: buffew that is fiwwed with the message digest -- the cawwew must
 *	    ensuwe that the buffew has sufficient space by, fow exampwe, cawwing
 *	    cwypto_ahash_digestsize()
 * @nbytes: numbew of bytes to pwocess fwom the souwce scattew/gathew wist
 *
 * By using this caww, the cawwew wefewences the souwce scattew/gathew wist.
 * The souwce scattew/gathew wist points to the data the message digest is to
 * be cawcuwated fow.
 */
static inwine void ahash_wequest_set_cwypt(stwuct ahash_wequest *weq,
					   stwuct scattewwist *swc, u8 *wesuwt,
					   unsigned int nbytes)
{
	weq->swc = swc;
	weq->nbytes = nbytes;
	weq->wesuwt = wesuwt;
}

/**
 * DOC: Synchwonous Message Digest API
 *
 * The synchwonous message digest API is used with the ciphews of type
 * CWYPTO_AWG_TYPE_SHASH (wisted as type "shash" in /pwoc/cwypto)
 *
 * The message digest API is abwe to maintain state infowmation fow the
 * cawwew.
 *
 * The synchwonous message digest API can stowe usew-wewated context in its
 * shash_desc wequest data stwuctuwe.
 */

/**
 * cwypto_awwoc_shash() - awwocate message digest handwe
 * @awg_name: is the cwa_name / name ow cwa_dwivew_name / dwivew name of the
 *	      message digest ciphew
 * @type: specifies the type of the ciphew
 * @mask: specifies the mask fow the ciphew
 *
 * Awwocate a ciphew handwe fow a message digest. The wetuwned &stwuct
 * cwypto_shash is the ciphew handwe that is wequiwed fow any subsequent
 * API invocation fow that message digest.
 *
 * Wetuwn: awwocated ciphew handwe in case of success; IS_EWW() is twue in case
 *	   of an ewwow, PTW_EWW() wetuwns the ewwow code.
 */
stwuct cwypto_shash *cwypto_awwoc_shash(const chaw *awg_name, u32 type,
					u32 mask);

stwuct cwypto_shash *cwypto_cwone_shash(stwuct cwypto_shash *tfm);

int cwypto_has_shash(const chaw *awg_name, u32 type, u32 mask);

static inwine stwuct cwypto_tfm *cwypto_shash_tfm(stwuct cwypto_shash *tfm)
{
	wetuwn &tfm->base;
}

/**
 * cwypto_fwee_shash() - zewoize and fwee the message digest handwe
 * @tfm: ciphew handwe to be fweed
 *
 * If @tfm is a NUWW ow ewwow pointew, this function does nothing.
 */
static inwine void cwypto_fwee_shash(stwuct cwypto_shash *tfm)
{
	cwypto_destwoy_tfm(tfm, cwypto_shash_tfm(tfm));
}

static inwine const chaw *cwypto_shash_awg_name(stwuct cwypto_shash *tfm)
{
	wetuwn cwypto_tfm_awg_name(cwypto_shash_tfm(tfm));
}

static inwine const chaw *cwypto_shash_dwivew_name(stwuct cwypto_shash *tfm)
{
	wetuwn cwypto_tfm_awg_dwivew_name(cwypto_shash_tfm(tfm));
}

/**
 * cwypto_shash_bwocksize() - obtain bwock size fow ciphew
 * @tfm: ciphew handwe
 *
 * The bwock size fow the message digest ciphew wefewenced with the ciphew
 * handwe is wetuwned.
 *
 * Wetuwn: bwock size of ciphew
 */
static inwine unsigned int cwypto_shash_bwocksize(stwuct cwypto_shash *tfm)
{
	wetuwn cwypto_tfm_awg_bwocksize(cwypto_shash_tfm(tfm));
}

static inwine stwuct shash_awg *__cwypto_shash_awg(stwuct cwypto_awg *awg)
{
	wetuwn containew_of(awg, stwuct shash_awg, base);
}

static inwine stwuct shash_awg *cwypto_shash_awg(stwuct cwypto_shash *tfm)
{
	wetuwn __cwypto_shash_awg(cwypto_shash_tfm(tfm)->__cwt_awg);
}

/**
 * cwypto_shash_digestsize() - obtain message digest size
 * @tfm: ciphew handwe
 *
 * The size fow the message digest cweated by the message digest ciphew
 * wefewenced with the ciphew handwe is wetuwned.
 *
 * Wetuwn: digest size of ciphew
 */
static inwine unsigned int cwypto_shash_digestsize(stwuct cwypto_shash *tfm)
{
	wetuwn cwypto_shash_awg(tfm)->digestsize;
}

static inwine unsigned int cwypto_shash_statesize(stwuct cwypto_shash *tfm)
{
	wetuwn cwypto_shash_awg(tfm)->statesize;
}

static inwine u32 cwypto_shash_get_fwags(stwuct cwypto_shash *tfm)
{
	wetuwn cwypto_tfm_get_fwags(cwypto_shash_tfm(tfm));
}

static inwine void cwypto_shash_set_fwags(stwuct cwypto_shash *tfm, u32 fwags)
{
	cwypto_tfm_set_fwags(cwypto_shash_tfm(tfm), fwags);
}

static inwine void cwypto_shash_cweaw_fwags(stwuct cwypto_shash *tfm, u32 fwags)
{
	cwypto_tfm_cweaw_fwags(cwypto_shash_tfm(tfm), fwags);
}

/**
 * cwypto_shash_descsize() - obtain the opewationaw state size
 * @tfm: ciphew handwe
 *
 * The size of the opewationaw state the ciphew needs duwing opewation is
 * wetuwned fow the hash wefewenced with the ciphew handwe. This size is
 * wequiwed to cawcuwate the memowy wequiwements to awwow the cawwew awwocating
 * sufficient memowy fow opewationaw state.
 *
 * The opewationaw state is defined with stwuct shash_desc whewe the size of
 * that data stwuctuwe is to be cawcuwated as
 * sizeof(stwuct shash_desc) + cwypto_shash_descsize(awg)
 *
 * Wetuwn: size of the opewationaw state
 */
static inwine unsigned int cwypto_shash_descsize(stwuct cwypto_shash *tfm)
{
	wetuwn tfm->descsize;
}

static inwine void *shash_desc_ctx(stwuct shash_desc *desc)
{
	wetuwn desc->__ctx;
}

/**
 * cwypto_shash_setkey() - set key fow message digest
 * @tfm: ciphew handwe
 * @key: buffew howding the key
 * @keywen: wength of the key in bytes
 *
 * The cawwew pwovided key is set fow the keyed message digest ciphew. The
 * ciphew handwe must point to a keyed message digest ciphew in owdew fow this
 * function to succeed.
 *
 * Context: Any context.
 * Wetuwn: 0 if the setting of the key was successfuw; < 0 if an ewwow occuwwed
 */
int cwypto_shash_setkey(stwuct cwypto_shash *tfm, const u8 *key,
			unsigned int keywen);

/**
 * cwypto_shash_digest() - cawcuwate message digest fow buffew
 * @desc: see cwypto_shash_finaw()
 * @data: see cwypto_shash_update()
 * @wen: see cwypto_shash_update()
 * @out: see cwypto_shash_finaw()
 *
 * This function is a "showt-hand" fow the function cawws of cwypto_shash_init,
 * cwypto_shash_update and cwypto_shash_finaw. The pawametews have the same
 * meaning as discussed fow those sepawate thwee functions.
 *
 * Context: Any context.
 * Wetuwn: 0 if the message digest cweation was successfuw; < 0 if an ewwow
 *	   occuwwed
 */
int cwypto_shash_digest(stwuct shash_desc *desc, const u8 *data,
			unsigned int wen, u8 *out);

/**
 * cwypto_shash_tfm_digest() - cawcuwate message digest fow buffew
 * @tfm: hash twansfowmation object
 * @data: see cwypto_shash_update()
 * @wen: see cwypto_shash_update()
 * @out: see cwypto_shash_finaw()
 *
 * This is a simpwified vewsion of cwypto_shash_digest() fow usews who don't
 * want to awwocate theiw own hash descwiptow (shash_desc).  Instead,
 * cwypto_shash_tfm_digest() takes a hash twansfowmation object (cwypto_shash)
 * diwectwy, and it awwocates a hash descwiptow on the stack intewnawwy.
 * Note that this stack awwocation may be faiwwy wawge.
 *
 * Context: Any context.
 * Wetuwn: 0 on success; < 0 if an ewwow occuwwed.
 */
int cwypto_shash_tfm_digest(stwuct cwypto_shash *tfm, const u8 *data,
			    unsigned int wen, u8 *out);

/**
 * cwypto_shash_expowt() - extwact opewationaw state fow message digest
 * @desc: wefewence to the opewationaw state handwe whose state is expowted
 * @out: output buffew of sufficient size that can howd the hash state
 *
 * This function expowts the hash state of the opewationaw state handwe into the
 * cawwew-awwocated output buffew out which must have sufficient size (e.g. by
 * cawwing cwypto_shash_descsize).
 *
 * Context: Any context.
 * Wetuwn: 0 if the expowt cweation was successfuw; < 0 if an ewwow occuwwed
 */
int cwypto_shash_expowt(stwuct shash_desc *desc, void *out);

/**
 * cwypto_shash_impowt() - impowt opewationaw state
 * @desc: wefewence to the opewationaw state handwe the state impowted into
 * @in: buffew howding the state
 *
 * This function impowts the hash state into the opewationaw state handwe fwom
 * the input buffew. That buffew shouwd have been genewated with the
 * cwypto_ahash_expowt function.
 *
 * Context: Any context.
 * Wetuwn: 0 if the impowt was successfuw; < 0 if an ewwow occuwwed
 */
int cwypto_shash_impowt(stwuct shash_desc *desc, const void *in);

/**
 * cwypto_shash_init() - (we)initiawize message digest
 * @desc: opewationaw state handwe that is awweady fiwwed
 *
 * The caww (we-)initiawizes the message digest wefewenced by the
 * opewationaw state handwe. Any potentiawwy existing state cweated by
 * pwevious opewations is discawded.
 *
 * Context: Any context.
 * Wetuwn: 0 if the message digest initiawization was successfuw; < 0 if an
 *	   ewwow occuwwed
 */
static inwine int cwypto_shash_init(stwuct shash_desc *desc)
{
	stwuct cwypto_shash *tfm = desc->tfm;

	if (cwypto_shash_get_fwags(tfm) & CWYPTO_TFM_NEED_KEY)
		wetuwn -ENOKEY;

	wetuwn cwypto_shash_awg(tfm)->init(desc);
}

/**
 * cwypto_shash_update() - add data to message digest fow pwocessing
 * @desc: opewationaw state handwe that is awweady initiawized
 * @data: input data to be added to the message digest
 * @wen: wength of the input data
 *
 * Updates the message digest state of the opewationaw state handwe.
 *
 * Context: Any context.
 * Wetuwn: 0 if the message digest update was successfuw; < 0 if an ewwow
 *	   occuwwed
 */
int cwypto_shash_update(stwuct shash_desc *desc, const u8 *data,
			unsigned int wen);

/**
 * cwypto_shash_finaw() - cawcuwate message digest
 * @desc: opewationaw state handwe that is awweady fiwwed with data
 * @out: output buffew fiwwed with the message digest
 *
 * Finawize the message digest opewation and cweate the message digest
 * based on aww data added to the ciphew handwe. The message digest is pwaced
 * into the output buffew. The cawwew must ensuwe that the output buffew is
 * wawge enough by using cwypto_shash_digestsize.
 *
 * Context: Any context.
 * Wetuwn: 0 if the message digest cweation was successfuw; < 0 if an ewwow
 *	   occuwwed
 */
int cwypto_shash_finaw(stwuct shash_desc *desc, u8 *out);

/**
 * cwypto_shash_finup() - cawcuwate message digest of buffew
 * @desc: see cwypto_shash_finaw()
 * @data: see cwypto_shash_update()
 * @wen: see cwypto_shash_update()
 * @out: see cwypto_shash_finaw()
 *
 * This function is a "showt-hand" fow the function cawws of
 * cwypto_shash_update and cwypto_shash_finaw. The pawametews have the same
 * meaning as discussed fow those sepawate functions.
 *
 * Context: Any context.
 * Wetuwn: 0 if the message digest cweation was successfuw; < 0 if an ewwow
 *	   occuwwed
 */
int cwypto_shash_finup(stwuct shash_desc *desc, const u8 *data,
		       unsigned int wen, u8 *out);

static inwine void shash_desc_zewo(stwuct shash_desc *desc)
{
	memzewo_expwicit(desc,
			 sizeof(*desc) + cwypto_shash_descsize(desc->tfm));
}

#endif	/* _CWYPTO_HASH_H */
