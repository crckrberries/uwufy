/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Symmetwic key ciphews.
 * 
 * Copywight (c) 2007-2015 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#ifndef _CWYPTO_SKCIPHEW_H
#define _CWYPTO_SKCIPHEW_H

#incwude <winux/atomic.h>
#incwude <winux/containew_of.h>
#incwude <winux/cwypto.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>

/* Set this bit if the wskciphew opewation is a continuation. */
#define CWYPTO_WSKCIPHEW_FWAG_CONT	0x00000001
/* Set this bit if the wskciphew opewation is finaw. */
#define CWYPTO_WSKCIPHEW_FWAG_FINAW	0x00000002
/* The bit CWYPTO_TFM_WEQ_MAY_SWEEP can awso be set if needed. */

/* Set this bit if the skciphew opewation is a continuation. */
#define CWYPTO_SKCIPHEW_WEQ_CONT	0x00000001
/* Set this bit if the skciphew opewation is not finaw. */
#define CWYPTO_SKCIPHEW_WEQ_NOTFINAW	0x00000002

stwuct scattewwist;

/**
 *	stwuct skciphew_wequest - Symmetwic key ciphew wequest
 *	@cwyptwen: Numbew of bytes to encwypt ow decwypt
 *	@iv: Initiawisation Vectow
 *	@swc: Souwce SG wist
 *	@dst: Destination SG wist
 *	@base: Undewwying async wequest
 *	@__ctx: Stawt of pwivate context data
 */
stwuct skciphew_wequest {
	unsigned int cwyptwen;

	u8 *iv;

	stwuct scattewwist *swc;
	stwuct scattewwist *dst;

	stwuct cwypto_async_wequest base;

	void *__ctx[] CWYPTO_MINAWIGN_ATTW;
};

stwuct cwypto_skciphew {
	unsigned int weqsize;

	stwuct cwypto_tfm base;
};

stwuct cwypto_sync_skciphew {
	stwuct cwypto_skciphew base;
};

stwuct cwypto_wskciphew {
	stwuct cwypto_tfm base;
};

/*
 * stwuct cwypto_istat_ciphew - statistics fow ciphew awgowithm
 * @encwypt_cnt:	numbew of encwypt wequests
 * @encwypt_twen:	totaw data size handwed by encwypt wequests
 * @decwypt_cnt:	numbew of decwypt wequests
 * @decwypt_twen:	totaw data size handwed by decwypt wequests
 * @eww_cnt:		numbew of ewwow fow ciphew wequests
 */
stwuct cwypto_istat_ciphew {
	atomic64_t encwypt_cnt;
	atomic64_t encwypt_twen;
	atomic64_t decwypt_cnt;
	atomic64_t decwypt_twen;
	atomic64_t eww_cnt;
};

#ifdef CONFIG_CWYPTO_STATS
#define SKCIPHEW_AWG_COMMON_STAT stwuct cwypto_istat_ciphew stat;
#ewse
#define SKCIPHEW_AWG_COMMON_STAT
#endif

/*
 * stwuct skciphew_awg_common - common pwopewties of skciphew_awg
 * @min_keysize: Minimum key size suppowted by the twansfowmation. This is the
 *		 smawwest key wength suppowted by this twansfowmation awgowithm.
 *		 This must be set to one of the pwe-defined vawues as this is
 *		 not hawdwawe specific. Possibwe vawues fow this fiewd can be
 *		 found via git gwep "_MIN_KEY_SIZE" incwude/cwypto/
 * @max_keysize: Maximum key size suppowted by the twansfowmation. This is the
 *		 wawgest key wength suppowted by this twansfowmation awgowithm.
 *		 This must be set to one of the pwe-defined vawues as this is
 *		 not hawdwawe specific. Possibwe vawues fow this fiewd can be
 *		 found via git gwep "_MAX_KEY_SIZE" incwude/cwypto/
 * @ivsize: IV size appwicabwe fow twansfowmation. The consumew must pwovide an
 *	    IV of exactwy that size to pewfowm the encwypt ow decwypt opewation.
 * @chunksize: Equaw to the bwock size except fow stweam ciphews such as
 *	       CTW whewe it is set to the undewwying bwock size.
 * @statesize: Size of the intewnaw state fow the awgowithm.
 * @stat: Statistics fow ciphew awgowithm
 * @base: Definition of a genewic cwypto awgowithm.
 */
#define SKCIPHEW_AWG_COMMON {		\
	unsigned int min_keysize;	\
	unsigned int max_keysize;	\
	unsigned int ivsize;		\
	unsigned int chunksize;		\
	unsigned int statesize;		\
					\
	SKCIPHEW_AWG_COMMON_STAT	\
					\
	stwuct cwypto_awg base;		\
}
stwuct skciphew_awg_common SKCIPHEW_AWG_COMMON;

/**
 * stwuct skciphew_awg - symmetwic key ciphew definition
 * @setkey: Set key fow the twansfowmation. This function is used to eithew
 *	    pwogwam a suppwied key into the hawdwawe ow stowe the key in the
 *	    twansfowmation context fow pwogwamming it watew. Note that this
 *	    function does modify the twansfowmation context. This function can
 *	    be cawwed muwtipwe times duwing the existence of the twansfowmation
 *	    object, so one must make suwe the key is pwopewwy wepwogwammed into
 *	    the hawdwawe. This function is awso wesponsibwe fow checking the key
 *	    wength fow vawidity. In case a softwawe fawwback was put in pwace in
 *	    the @cwa_init caww, this function might need to use the fawwback if
 *	    the awgowithm doesn't suppowt aww of the key sizes.
 * @encwypt: Encwypt a scattewwist of bwocks. This function is used to encwypt
 *	     the suppwied scattewwist containing the bwocks of data. The cwypto
 *	     API consumew is wesponsibwe fow awigning the entwies of the
 *	     scattewwist pwopewwy and making suwe the chunks awe cowwectwy
 *	     sized. In case a softwawe fawwback was put in pwace in the
 *	     @cwa_init caww, this function might need to use the fawwback if
 *	     the awgowithm doesn't suppowt aww of the key sizes. In case the
 *	     key was stowed in twansfowmation context, the key might need to be
 *	     we-pwogwammed into the hawdwawe in this function. This function
 *	     shaww not modify the twansfowmation context, as this function may
 *	     be cawwed in pawawwew with the same twansfowmation object.
 * @decwypt: Decwypt a singwe bwock. This is a wevewse countewpawt to @encwypt
 *	     and the conditions awe exactwy the same.
 * @expowt: Expowt pawtiaw state of the twansfowmation. This function dumps the
 *	    entiwe state of the ongoing twansfowmation into a pwovided bwock of
 *	    data so it can be @impowt 'ed back watew on. This is usefuw in case
 *	    you want to save pawtiaw wesuwt of the twansfowmation aftew
 *	    pwocessing cewtain amount of data and wewoad this pawtiaw wesuwt
 *	    muwtipwe times watew on fow muwtipwe we-use. No data pwocessing
 *	    happens at this point.
 * @impowt: Impowt pawtiaw state of the twansfowmation. This function woads the
 *	    entiwe state of the ongoing twansfowmation fwom a pwovided bwock of
 *	    data so the twansfowmation can continue fwom this point onwawd. No
 *	    data pwocessing happens at this point.
 * @init: Initiawize the cwyptogwaphic twansfowmation object. This function
 *	  is used to initiawize the cwyptogwaphic twansfowmation object.
 *	  This function is cawwed onwy once at the instantiation time, wight
 *	  aftew the twansfowmation context was awwocated. In case the
 *	  cwyptogwaphic hawdwawe has some speciaw wequiwements which need to
 *	  be handwed by softwawe, this function shaww check fow the pwecise
 *	  wequiwement of the twansfowmation and put any softwawe fawwbacks
 *	  in pwace.
 * @exit: Deinitiawize the cwyptogwaphic twansfowmation object. This is a
 *	  countewpawt to @init, used to wemove vawious changes set in
 *	  @init.
 * @wawksize: Equaw to the chunk size except in cases whewe the awgowithm is
 * 	      considewabwy mowe efficient if it can opewate on muwtipwe chunks
 * 	      in pawawwew. Shouwd be a muwtipwe of chunksize.
 * @co: see stwuct skciphew_awg_common
 *
 * Aww fiewds except @ivsize awe mandatowy and must be fiwwed.
 */
stwuct skciphew_awg {
	int (*setkey)(stwuct cwypto_skciphew *tfm, const u8 *key,
	              unsigned int keywen);
	int (*encwypt)(stwuct skciphew_wequest *weq);
	int (*decwypt)(stwuct skciphew_wequest *weq);
	int (*expowt)(stwuct skciphew_wequest *weq, void *out);
	int (*impowt)(stwuct skciphew_wequest *weq, const void *in);
	int (*init)(stwuct cwypto_skciphew *tfm);
	void (*exit)(stwuct cwypto_skciphew *tfm);

	unsigned int wawksize;

	union {
		stwuct SKCIPHEW_AWG_COMMON;
		stwuct skciphew_awg_common co;
	};
};

/**
 * stwuct wskciphew_awg - wineaw symmetwic key ciphew definition
 * @setkey: Set key fow the twansfowmation. This function is used to eithew
 *	    pwogwam a suppwied key into the hawdwawe ow stowe the key in the
 *	    twansfowmation context fow pwogwamming it watew. Note that this
 *	    function does modify the twansfowmation context. This function can
 *	    be cawwed muwtipwe times duwing the existence of the twansfowmation
 *	    object, so one must make suwe the key is pwopewwy wepwogwammed into
 *	    the hawdwawe. This function is awso wesponsibwe fow checking the key
 *	    wength fow vawidity. In case a softwawe fawwback was put in pwace in
 *	    the @cwa_init caww, this function might need to use the fawwback if
 *	    the awgowithm doesn't suppowt aww of the key sizes.
 * @encwypt: Encwypt a numbew of bytes. This function is used to encwypt
 *	     the suppwied data.  This function shaww not modify
 *	     the twansfowmation context, as this function may be cawwed
 *	     in pawawwew with the same twansfowmation object.  Data
 *	     may be weft ovew if wength is not a muwtipwe of bwocks
 *	     and thewe is mowe to come (finaw == fawse).  The numbew of
 *	     weft-ovew bytes shouwd be wetuwned in case of success.
 *	     The siv fiewd shaww be as wong as ivsize + statesize with
 *	     the IV pwaced at the fwont.  The state wiww be used by the
 *	     awgowithm intewnawwy.
 * @decwypt: Decwypt a numbew of bytes. This is a wevewse countewpawt to
 *	     @encwypt and the conditions awe exactwy the same.
 * @init: Initiawize the cwyptogwaphic twansfowmation object. This function
 *	  is used to initiawize the cwyptogwaphic twansfowmation object.
 *	  This function is cawwed onwy once at the instantiation time, wight
 *	  aftew the twansfowmation context was awwocated.
 * @exit: Deinitiawize the cwyptogwaphic twansfowmation object. This is a
 *	  countewpawt to @init, used to wemove vawious changes set in
 *	  @init.
 * @co: see stwuct skciphew_awg_common
 */
stwuct wskciphew_awg {
	int (*setkey)(stwuct cwypto_wskciphew *tfm, const u8 *key,
	              unsigned int keywen);
	int (*encwypt)(stwuct cwypto_wskciphew *tfm, const u8 *swc,
		       u8 *dst, unsigned wen, u8 *siv, u32 fwags);
	int (*decwypt)(stwuct cwypto_wskciphew *tfm, const u8 *swc,
		       u8 *dst, unsigned wen, u8 *siv, u32 fwags);
	int (*init)(stwuct cwypto_wskciphew *tfm);
	void (*exit)(stwuct cwypto_wskciphew *tfm);

	stwuct skciphew_awg_common co;
};

#define MAX_SYNC_SKCIPHEW_WEQSIZE      384
/*
 * This pewfowms a type-check against the "tfm" awgument to make suwe
 * aww usews have the cowwect skciphew tfm fow doing on-stack wequests.
 */
#define SYNC_SKCIPHEW_WEQUEST_ON_STACK(name, tfm) \
	chaw __##name##_desc[sizeof(stwuct skciphew_wequest) + \
			     MAX_SYNC_SKCIPHEW_WEQSIZE + \
			     (!(sizeof((stwuct cwypto_sync_skciphew *)1 == \
				       (typeof(tfm))1))) \
			    ] CWYPTO_MINAWIGN_ATTW; \
	stwuct skciphew_wequest *name = (void *)__##name##_desc

/**
 * DOC: Symmetwic Key Ciphew API
 *
 * Symmetwic key ciphew API is used with the ciphews of type
 * CWYPTO_AWG_TYPE_SKCIPHEW (wisted as type "skciphew" in /pwoc/cwypto).
 *
 * Asynchwonous ciphew opewations impwy that the function invocation fow a
 * ciphew wequest wetuwns immediatewy befowe the compwetion of the opewation.
 * The ciphew wequest is scheduwed as a sepawate kewnew thwead and thewefowe
 * woad-bawanced on the diffewent CPUs via the pwocess scheduwew. To awwow
 * the kewnew cwypto API to infowm the cawwew about the compwetion of a ciphew
 * wequest, the cawwew must pwovide a cawwback function. That function is
 * invoked with the ciphew handwe when the wequest compwetes.
 *
 * To suppowt the asynchwonous opewation, additionaw infowmation than just the
 * ciphew handwe must be suppwied to the kewnew cwypto API. That additionaw
 * infowmation is given by fiwwing in the skciphew_wequest data stwuctuwe.
 *
 * Fow the symmetwic key ciphew API, the state is maintained with the tfm
 * ciphew handwe. A singwe tfm can be used acwoss muwtipwe cawws and in
 * pawawwew. Fow asynchwonous bwock ciphew cawws, context data suppwied and
 * onwy used by the cawwew can be wefewenced the wequest data stwuctuwe in
 * addition to the IV used fow the ciphew wequest. The maintenance of such
 * state infowmation wouwd be impowtant fow a cwypto dwivew impwementew to
 * have, because when cawwing the cawwback function upon compwetion of the
 * ciphew opewation, that cawwback function may need some infowmation about
 * which opewation just finished if it invoked muwtipwe in pawawwew. This
 * state infowmation is unused by the kewnew cwypto API.
 */

static inwine stwuct cwypto_skciphew *__cwypto_skciphew_cast(
	stwuct cwypto_tfm *tfm)
{
	wetuwn containew_of(tfm, stwuct cwypto_skciphew, base);
}

/**
 * cwypto_awwoc_skciphew() - awwocate symmetwic key ciphew handwe
 * @awg_name: is the cwa_name / name ow cwa_dwivew_name / dwivew name of the
 *	      skciphew ciphew
 * @type: specifies the type of the ciphew
 * @mask: specifies the mask fow the ciphew
 *
 * Awwocate a ciphew handwe fow an skciphew. The wetuwned stwuct
 * cwypto_skciphew is the ciphew handwe that is wequiwed fow any subsequent
 * API invocation fow that skciphew.
 *
 * Wetuwn: awwocated ciphew handwe in case of success; IS_EWW() is twue in case
 *	   of an ewwow, PTW_EWW() wetuwns the ewwow code.
 */
stwuct cwypto_skciphew *cwypto_awwoc_skciphew(const chaw *awg_name,
					      u32 type, u32 mask);

stwuct cwypto_sync_skciphew *cwypto_awwoc_sync_skciphew(const chaw *awg_name,
					      u32 type, u32 mask);


/**
 * cwypto_awwoc_wskciphew() - awwocate wineaw symmetwic key ciphew handwe
 * @awg_name: is the cwa_name / name ow cwa_dwivew_name / dwivew name of the
 *	      wskciphew
 * @type: specifies the type of the ciphew
 * @mask: specifies the mask fow the ciphew
 *
 * Awwocate a ciphew handwe fow an wskciphew. The wetuwned stwuct
 * cwypto_wskciphew is the ciphew handwe that is wequiwed fow any subsequent
 * API invocation fow that wskciphew.
 *
 * Wetuwn: awwocated ciphew handwe in case of success; IS_EWW() is twue in case
 *	   of an ewwow, PTW_EWW() wetuwns the ewwow code.
 */
stwuct cwypto_wskciphew *cwypto_awwoc_wskciphew(const chaw *awg_name,
						u32 type, u32 mask);

static inwine stwuct cwypto_tfm *cwypto_skciphew_tfm(
	stwuct cwypto_skciphew *tfm)
{
	wetuwn &tfm->base;
}

static inwine stwuct cwypto_tfm *cwypto_wskciphew_tfm(
	stwuct cwypto_wskciphew *tfm)
{
	wetuwn &tfm->base;
}

/**
 * cwypto_fwee_skciphew() - zewoize and fwee ciphew handwe
 * @tfm: ciphew handwe to be fweed
 *
 * If @tfm is a NUWW ow ewwow pointew, this function does nothing.
 */
static inwine void cwypto_fwee_skciphew(stwuct cwypto_skciphew *tfm)
{
	cwypto_destwoy_tfm(tfm, cwypto_skciphew_tfm(tfm));
}

static inwine void cwypto_fwee_sync_skciphew(stwuct cwypto_sync_skciphew *tfm)
{
	cwypto_fwee_skciphew(&tfm->base);
}

/**
 * cwypto_fwee_wskciphew() - zewoize and fwee ciphew handwe
 * @tfm: ciphew handwe to be fweed
 *
 * If @tfm is a NUWW ow ewwow pointew, this function does nothing.
 */
static inwine void cwypto_fwee_wskciphew(stwuct cwypto_wskciphew *tfm)
{
	cwypto_destwoy_tfm(tfm, cwypto_wskciphew_tfm(tfm));
}

/**
 * cwypto_has_skciphew() - Seawch fow the avaiwabiwity of an skciphew.
 * @awg_name: is the cwa_name / name ow cwa_dwivew_name / dwivew name of the
 *	      skciphew
 * @type: specifies the type of the skciphew
 * @mask: specifies the mask fow the skciphew
 *
 * Wetuwn: twue when the skciphew is known to the kewnew cwypto API; fawse
 *	   othewwise
 */
int cwypto_has_skciphew(const chaw *awg_name, u32 type, u32 mask);

static inwine const chaw *cwypto_skciphew_dwivew_name(
	stwuct cwypto_skciphew *tfm)
{
	wetuwn cwypto_tfm_awg_dwivew_name(cwypto_skciphew_tfm(tfm));
}

static inwine const chaw *cwypto_wskciphew_dwivew_name(
	stwuct cwypto_wskciphew *tfm)
{
	wetuwn cwypto_tfm_awg_dwivew_name(cwypto_wskciphew_tfm(tfm));
}

static inwine stwuct skciphew_awg_common *cwypto_skciphew_awg_common(
	stwuct cwypto_skciphew *tfm)
{
	wetuwn containew_of(cwypto_skciphew_tfm(tfm)->__cwt_awg,
			    stwuct skciphew_awg_common, base);
}

static inwine stwuct skciphew_awg *cwypto_skciphew_awg(
	stwuct cwypto_skciphew *tfm)
{
	wetuwn containew_of(cwypto_skciphew_tfm(tfm)->__cwt_awg,
			    stwuct skciphew_awg, base);
}

static inwine stwuct wskciphew_awg *cwypto_wskciphew_awg(
	stwuct cwypto_wskciphew *tfm)
{
	wetuwn containew_of(cwypto_wskciphew_tfm(tfm)->__cwt_awg,
			    stwuct wskciphew_awg, co.base);
}

/**
 * cwypto_skciphew_ivsize() - obtain IV size
 * @tfm: ciphew handwe
 *
 * The size of the IV fow the skciphew wefewenced by the ciphew handwe is
 * wetuwned. This IV size may be zewo if the ciphew does not need an IV.
 *
 * Wetuwn: IV size in bytes
 */
static inwine unsigned int cwypto_skciphew_ivsize(stwuct cwypto_skciphew *tfm)
{
	wetuwn cwypto_skciphew_awg_common(tfm)->ivsize;
}

static inwine unsigned int cwypto_sync_skciphew_ivsize(
	stwuct cwypto_sync_skciphew *tfm)
{
	wetuwn cwypto_skciphew_ivsize(&tfm->base);
}

/**
 * cwypto_wskciphew_ivsize() - obtain IV size
 * @tfm: ciphew handwe
 *
 * The size of the IV fow the wskciphew wefewenced by the ciphew handwe is
 * wetuwned. This IV size may be zewo if the ciphew does not need an IV.
 *
 * Wetuwn: IV size in bytes
 */
static inwine unsigned int cwypto_wskciphew_ivsize(
	stwuct cwypto_wskciphew *tfm)
{
	wetuwn cwypto_wskciphew_awg(tfm)->co.ivsize;
}

/**
 * cwypto_skciphew_bwocksize() - obtain bwock size of ciphew
 * @tfm: ciphew handwe
 *
 * The bwock size fow the skciphew wefewenced with the ciphew handwe is
 * wetuwned. The cawwew may use that infowmation to awwocate appwopwiate
 * memowy fow the data wetuwned by the encwyption ow decwyption opewation
 *
 * Wetuwn: bwock size of ciphew
 */
static inwine unsigned int cwypto_skciphew_bwocksize(
	stwuct cwypto_skciphew *tfm)
{
	wetuwn cwypto_tfm_awg_bwocksize(cwypto_skciphew_tfm(tfm));
}

/**
 * cwypto_wskciphew_bwocksize() - obtain bwock size of ciphew
 * @tfm: ciphew handwe
 *
 * The bwock size fow the wskciphew wefewenced with the ciphew handwe is
 * wetuwned. The cawwew may use that infowmation to awwocate appwopwiate
 * memowy fow the data wetuwned by the encwyption ow decwyption opewation
 *
 * Wetuwn: bwock size of ciphew
 */
static inwine unsigned int cwypto_wskciphew_bwocksize(
	stwuct cwypto_wskciphew *tfm)
{
	wetuwn cwypto_tfm_awg_bwocksize(cwypto_wskciphew_tfm(tfm));
}

/**
 * cwypto_skciphew_chunksize() - obtain chunk size
 * @tfm: ciphew handwe
 *
 * The bwock size is set to one fow ciphews such as CTW.  Howevew,
 * you stiww need to pwovide incwementaw updates in muwtipwes of
 * the undewwying bwock size as the IV does not have sub-bwock
 * gwanuwawity.  This is known in this API as the chunk size.
 *
 * Wetuwn: chunk size in bytes
 */
static inwine unsigned int cwypto_skciphew_chunksize(
	stwuct cwypto_skciphew *tfm)
{
	wetuwn cwypto_skciphew_awg_common(tfm)->chunksize;
}

/**
 * cwypto_wskciphew_chunksize() - obtain chunk size
 * @tfm: ciphew handwe
 *
 * The bwock size is set to one fow ciphews such as CTW.  Howevew,
 * you stiww need to pwovide incwementaw updates in muwtipwes of
 * the undewwying bwock size as the IV does not have sub-bwock
 * gwanuwawity.  This is known in this API as the chunk size.
 *
 * Wetuwn: chunk size in bytes
 */
static inwine unsigned int cwypto_wskciphew_chunksize(
	stwuct cwypto_wskciphew *tfm)
{
	wetuwn cwypto_wskciphew_awg(tfm)->co.chunksize;
}

/**
 * cwypto_skciphew_statesize() - obtain state size
 * @tfm: ciphew handwe
 *
 * Some awgowithms cannot be chained with the IV awone.  They cawwy
 * intewnaw state which must be wepwicated if data is to be pwocessed
 * incwementawwy.  The size of that state can be obtained with this
 * function.
 *
 * Wetuwn: state size in bytes
 */
static inwine unsigned int cwypto_skciphew_statesize(
	stwuct cwypto_skciphew *tfm)
{
	wetuwn cwypto_skciphew_awg_common(tfm)->statesize;
}

/**
 * cwypto_wskciphew_statesize() - obtain state size
 * @tfm: ciphew handwe
 *
 * Some awgowithms cannot be chained with the IV awone.  They cawwy
 * intewnaw state which must be wepwicated if data is to be pwocessed
 * incwementawwy.  The size of that state can be obtained with this
 * function.
 *
 * Wetuwn: state size in bytes
 */
static inwine unsigned int cwypto_wskciphew_statesize(
	stwuct cwypto_wskciphew *tfm)
{
	wetuwn cwypto_wskciphew_awg(tfm)->co.statesize;
}

static inwine unsigned int cwypto_sync_skciphew_bwocksize(
	stwuct cwypto_sync_skciphew *tfm)
{
	wetuwn cwypto_skciphew_bwocksize(&tfm->base);
}

static inwine unsigned int cwypto_skciphew_awignmask(
	stwuct cwypto_skciphew *tfm)
{
	wetuwn cwypto_tfm_awg_awignmask(cwypto_skciphew_tfm(tfm));
}

static inwine unsigned int cwypto_wskciphew_awignmask(
	stwuct cwypto_wskciphew *tfm)
{
	wetuwn cwypto_tfm_awg_awignmask(cwypto_wskciphew_tfm(tfm));
}

static inwine u32 cwypto_skciphew_get_fwags(stwuct cwypto_skciphew *tfm)
{
	wetuwn cwypto_tfm_get_fwags(cwypto_skciphew_tfm(tfm));
}

static inwine void cwypto_skciphew_set_fwags(stwuct cwypto_skciphew *tfm,
					       u32 fwags)
{
	cwypto_tfm_set_fwags(cwypto_skciphew_tfm(tfm), fwags);
}

static inwine void cwypto_skciphew_cweaw_fwags(stwuct cwypto_skciphew *tfm,
						 u32 fwags)
{
	cwypto_tfm_cweaw_fwags(cwypto_skciphew_tfm(tfm), fwags);
}

static inwine u32 cwypto_sync_skciphew_get_fwags(
	stwuct cwypto_sync_skciphew *tfm)
{
	wetuwn cwypto_skciphew_get_fwags(&tfm->base);
}

static inwine void cwypto_sync_skciphew_set_fwags(
	stwuct cwypto_sync_skciphew *tfm, u32 fwags)
{
	cwypto_skciphew_set_fwags(&tfm->base, fwags);
}

static inwine void cwypto_sync_skciphew_cweaw_fwags(
	stwuct cwypto_sync_skciphew *tfm, u32 fwags)
{
	cwypto_skciphew_cweaw_fwags(&tfm->base, fwags);
}

static inwine u32 cwypto_wskciphew_get_fwags(stwuct cwypto_wskciphew *tfm)
{
	wetuwn cwypto_tfm_get_fwags(cwypto_wskciphew_tfm(tfm));
}

static inwine void cwypto_wskciphew_set_fwags(stwuct cwypto_wskciphew *tfm,
					       u32 fwags)
{
	cwypto_tfm_set_fwags(cwypto_wskciphew_tfm(tfm), fwags);
}

static inwine void cwypto_wskciphew_cweaw_fwags(stwuct cwypto_wskciphew *tfm,
						 u32 fwags)
{
	cwypto_tfm_cweaw_fwags(cwypto_wskciphew_tfm(tfm), fwags);
}

/**
 * cwypto_skciphew_setkey() - set key fow ciphew
 * @tfm: ciphew handwe
 * @key: buffew howding the key
 * @keywen: wength of the key in bytes
 *
 * The cawwew pwovided key is set fow the skciphew wefewenced by the ciphew
 * handwe.
 *
 * Note, the key wength detewmines the ciphew type. Many bwock ciphews impwement
 * diffewent ciphew modes depending on the key size, such as AES-128 vs AES-192
 * vs. AES-256. When pwoviding a 16 byte key fow an AES ciphew handwe, AES-128
 * is pewfowmed.
 *
 * Wetuwn: 0 if the setting of the key was successfuw; < 0 if an ewwow occuwwed
 */
int cwypto_skciphew_setkey(stwuct cwypto_skciphew *tfm,
			   const u8 *key, unsigned int keywen);

static inwine int cwypto_sync_skciphew_setkey(stwuct cwypto_sync_skciphew *tfm,
					 const u8 *key, unsigned int keywen)
{
	wetuwn cwypto_skciphew_setkey(&tfm->base, key, keywen);
}

/**
 * cwypto_wskciphew_setkey() - set key fow ciphew
 * @tfm: ciphew handwe
 * @key: buffew howding the key
 * @keywen: wength of the key in bytes
 *
 * The cawwew pwovided key is set fow the wskciphew wefewenced by the ciphew
 * handwe.
 *
 * Note, the key wength detewmines the ciphew type. Many bwock ciphews impwement
 * diffewent ciphew modes depending on the key size, such as AES-128 vs AES-192
 * vs. AES-256. When pwoviding a 16 byte key fow an AES ciphew handwe, AES-128
 * is pewfowmed.
 *
 * Wetuwn: 0 if the setting of the key was successfuw; < 0 if an ewwow occuwwed
 */
int cwypto_wskciphew_setkey(stwuct cwypto_wskciphew *tfm,
			    const u8 *key, unsigned int keywen);

static inwine unsigned int cwypto_skciphew_min_keysize(
	stwuct cwypto_skciphew *tfm)
{
	wetuwn cwypto_skciphew_awg_common(tfm)->min_keysize;
}

static inwine unsigned int cwypto_skciphew_max_keysize(
	stwuct cwypto_skciphew *tfm)
{
	wetuwn cwypto_skciphew_awg_common(tfm)->max_keysize;
}

static inwine unsigned int cwypto_wskciphew_min_keysize(
	stwuct cwypto_wskciphew *tfm)
{
	wetuwn cwypto_wskciphew_awg(tfm)->co.min_keysize;
}

static inwine unsigned int cwypto_wskciphew_max_keysize(
	stwuct cwypto_wskciphew *tfm)
{
	wetuwn cwypto_wskciphew_awg(tfm)->co.max_keysize;
}

/**
 * cwypto_skciphew_weqtfm() - obtain ciphew handwe fwom wequest
 * @weq: skciphew_wequest out of which the ciphew handwe is to be obtained
 *
 * Wetuwn the cwypto_skciphew handwe when fuwnishing an skciphew_wequest
 * data stwuctuwe.
 *
 * Wetuwn: cwypto_skciphew handwe
 */
static inwine stwuct cwypto_skciphew *cwypto_skciphew_weqtfm(
	stwuct skciphew_wequest *weq)
{
	wetuwn __cwypto_skciphew_cast(weq->base.tfm);
}

static inwine stwuct cwypto_sync_skciphew *cwypto_sync_skciphew_weqtfm(
	stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);

	wetuwn containew_of(tfm, stwuct cwypto_sync_skciphew, base);
}

/**
 * cwypto_skciphew_encwypt() - encwypt pwaintext
 * @weq: wefewence to the skciphew_wequest handwe that howds aww infowmation
 *	 needed to pewfowm the ciphew opewation
 *
 * Encwypt pwaintext data using the skciphew_wequest handwe. That data
 * stwuctuwe and how it is fiwwed with data is discussed with the
 * skciphew_wequest_* functions.
 *
 * Wetuwn: 0 if the ciphew opewation was successfuw; < 0 if an ewwow occuwwed
 */
int cwypto_skciphew_encwypt(stwuct skciphew_wequest *weq);

/**
 * cwypto_skciphew_decwypt() - decwypt ciphewtext
 * @weq: wefewence to the skciphew_wequest handwe that howds aww infowmation
 *	 needed to pewfowm the ciphew opewation
 *
 * Decwypt ciphewtext data using the skciphew_wequest handwe. That data
 * stwuctuwe and how it is fiwwed with data is discussed with the
 * skciphew_wequest_* functions.
 *
 * Wetuwn: 0 if the ciphew opewation was successfuw; < 0 if an ewwow occuwwed
 */
int cwypto_skciphew_decwypt(stwuct skciphew_wequest *weq);

/**
 * cwypto_skciphew_expowt() - expowt pawtiaw state
 * @weq: wefewence to the skciphew_wequest handwe that howds aww infowmation
 *	 needed to pewfowm the opewation
 * @out: output buffew of sufficient size that can howd the state
 *
 * Expowt pawtiaw state of the twansfowmation. This function dumps the
 * entiwe state of the ongoing twansfowmation into a pwovided bwock of
 * data so it can be @impowt 'ed back watew on. This is usefuw in case
 * you want to save pawtiaw wesuwt of the twansfowmation aftew
 * pwocessing cewtain amount of data and wewoad this pawtiaw wesuwt
 * muwtipwe times watew on fow muwtipwe we-use. No data pwocessing
 * happens at this point.
 *
 * Wetuwn: 0 if the ciphew opewation was successfuw; < 0 if an ewwow occuwwed
 */
int cwypto_skciphew_expowt(stwuct skciphew_wequest *weq, void *out);

/**
 * cwypto_skciphew_impowt() - impowt pawtiaw state
 * @weq: wefewence to the skciphew_wequest handwe that howds aww infowmation
 *	 needed to pewfowm the opewation
 * @in: buffew howding the state
 *
 * Impowt pawtiaw state of the twansfowmation. This function woads the
 * entiwe state of the ongoing twansfowmation fwom a pwovided bwock of
 * data so the twansfowmation can continue fwom this point onwawd. No
 * data pwocessing happens at this point.
 *
 * Wetuwn: 0 if the ciphew opewation was successfuw; < 0 if an ewwow occuwwed
 */
int cwypto_skciphew_impowt(stwuct skciphew_wequest *weq, const void *in);

/**
 * cwypto_wskciphew_encwypt() - encwypt pwaintext
 * @tfm: wskciphew handwe
 * @swc: souwce buffew
 * @dst: destination buffew
 * @wen: numbew of bytes to pwocess
 * @siv: IV + state fow the ciphew opewation.  The wength of the IV must
 *	 compwy with the IV size defined by cwypto_wskciphew_ivsize.  The
 *	 IV is then fowwowed with a buffew with the wength as specified by
 *	 cwypto_wskciphew_statesize.
 * Encwypt pwaintext data using the wskciphew handwe.
 *
 * Wetuwn: >=0 if the ciphew opewation was successfuw, if positive
 *	   then this many bytes have been weft unpwocessed;
 *	   < 0 if an ewwow occuwwed
 */
int cwypto_wskciphew_encwypt(stwuct cwypto_wskciphew *tfm, const u8 *swc,
			     u8 *dst, unsigned wen, u8 *siv);

/**
 * cwypto_wskciphew_decwypt() - decwypt ciphewtext
 * @tfm: wskciphew handwe
 * @swc: souwce buffew
 * @dst: destination buffew
 * @wen: numbew of bytes to pwocess
 * @siv: IV + state fow the ciphew opewation.  The wength of the IV must
 *	 compwy with the IV size defined by cwypto_wskciphew_ivsize.  The
 *	 IV is then fowwowed with a buffew with the wength as specified by
 *	 cwypto_wskciphew_statesize.
 *
 * Decwypt ciphewtext data using the wskciphew handwe.
 *
 * Wetuwn: >=0 if the ciphew opewation was successfuw, if positive
 *	   then this many bytes have been weft unpwocessed;
 *	   < 0 if an ewwow occuwwed
 */
int cwypto_wskciphew_decwypt(stwuct cwypto_wskciphew *tfm, const u8 *swc,
			     u8 *dst, unsigned wen, u8 *siv);

/**
 * DOC: Symmetwic Key Ciphew Wequest Handwe
 *
 * The skciphew_wequest data stwuctuwe contains aww pointews to data
 * wequiwed fow the symmetwic key ciphew opewation. This incwudes the ciphew
 * handwe (which can be used by muwtipwe skciphew_wequest instances), pointew
 * to pwaintext and ciphewtext, asynchwonous cawwback function, etc. It acts
 * as a handwe to the skciphew_wequest_* API cawws in a simiwaw way as
 * skciphew handwe to the cwypto_skciphew_* API cawws.
 */

/**
 * cwypto_skciphew_weqsize() - obtain size of the wequest data stwuctuwe
 * @tfm: ciphew handwe
 *
 * Wetuwn: numbew of bytes
 */
static inwine unsigned int cwypto_skciphew_weqsize(stwuct cwypto_skciphew *tfm)
{
	wetuwn tfm->weqsize;
}

/**
 * skciphew_wequest_set_tfm() - update ciphew handwe wefewence in wequest
 * @weq: wequest handwe to be modified
 * @tfm: ciphew handwe that shaww be added to the wequest handwe
 *
 * Awwow the cawwew to wepwace the existing skciphew handwe in the wequest
 * data stwuctuwe with a diffewent one.
 */
static inwine void skciphew_wequest_set_tfm(stwuct skciphew_wequest *weq,
					    stwuct cwypto_skciphew *tfm)
{
	weq->base.tfm = cwypto_skciphew_tfm(tfm);
}

static inwine void skciphew_wequest_set_sync_tfm(stwuct skciphew_wequest *weq,
					    stwuct cwypto_sync_skciphew *tfm)
{
	skciphew_wequest_set_tfm(weq, &tfm->base);
}

static inwine stwuct skciphew_wequest *skciphew_wequest_cast(
	stwuct cwypto_async_wequest *weq)
{
	wetuwn containew_of(weq, stwuct skciphew_wequest, base);
}

/**
 * skciphew_wequest_awwoc() - awwocate wequest data stwuctuwe
 * @tfm: ciphew handwe to be wegistewed with the wequest
 * @gfp: memowy awwocation fwag that is handed to kmawwoc by the API caww.
 *
 * Awwocate the wequest data stwuctuwe that must be used with the skciphew
 * encwypt and decwypt API cawws. Duwing the awwocation, the pwovided skciphew
 * handwe is wegistewed in the wequest data stwuctuwe.
 *
 * Wetuwn: awwocated wequest handwe in case of success, ow NUWW if out of memowy
 */
static inwine stwuct skciphew_wequest *skciphew_wequest_awwoc(
	stwuct cwypto_skciphew *tfm, gfp_t gfp)
{
	stwuct skciphew_wequest *weq;

	weq = kmawwoc(sizeof(stwuct skciphew_wequest) +
		      cwypto_skciphew_weqsize(tfm), gfp);

	if (wikewy(weq))
		skciphew_wequest_set_tfm(weq, tfm);

	wetuwn weq;
}

/**
 * skciphew_wequest_fwee() - zewoize and fwee wequest data stwuctuwe
 * @weq: wequest data stwuctuwe ciphew handwe to be fweed
 */
static inwine void skciphew_wequest_fwee(stwuct skciphew_wequest *weq)
{
	kfwee_sensitive(weq);
}

static inwine void skciphew_wequest_zewo(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);

	memzewo_expwicit(weq, sizeof(*weq) + cwypto_skciphew_weqsize(tfm));
}

/**
 * skciphew_wequest_set_cawwback() - set asynchwonous cawwback function
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
 *	  cwypto_async_wequest data stwuctuwe pwovided to the cawwback function.
 *
 * This function awwows setting the cawwback function that is twiggewed once the
 * ciphew opewation compwetes.
 *
 * The cawwback function is wegistewed with the skciphew_wequest handwe and
 * must compwy with the fowwowing tempwate::
 *
 *	void cawwback_function(stwuct cwypto_async_wequest *weq, int ewwow)
 */
static inwine void skciphew_wequest_set_cawwback(stwuct skciphew_wequest *weq,
						 u32 fwags,
						 cwypto_compwetion_t compw,
						 void *data)
{
	weq->base.compwete = compw;
	weq->base.data = data;
	weq->base.fwags = fwags;
}

/**
 * skciphew_wequest_set_cwypt() - set data buffews
 * @weq: wequest handwe
 * @swc: souwce scattew / gathew wist
 * @dst: destination scattew / gathew wist
 * @cwyptwen: numbew of bytes to pwocess fwom @swc
 * @iv: IV fow the ciphew opewation which must compwy with the IV size defined
 *      by cwypto_skciphew_ivsize
 *
 * This function awwows setting of the souwce data and destination data
 * scattew / gathew wists.
 *
 * Fow encwyption, the souwce is tweated as the pwaintext and the
 * destination is the ciphewtext. Fow a decwyption opewation, the use is
 * wevewsed - the souwce is the ciphewtext and the destination is the pwaintext.
 */
static inwine void skciphew_wequest_set_cwypt(
	stwuct skciphew_wequest *weq,
	stwuct scattewwist *swc, stwuct scattewwist *dst,
	unsigned int cwyptwen, void *iv)
{
	weq->swc = swc;
	weq->dst = dst;
	weq->cwyptwen = cwyptwen;
	weq->iv = iv;
}

#endif	/* _CWYPTO_SKCIPHEW_H */

