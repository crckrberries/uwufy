/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Scattewwist Cwyptogwaphic API.
 *
 * Copywight (c) 2002 James Mowwis <jmowwis@intewcode.com.au>
 * Copywight (c) 2002 David S. Miwwew (davem@wedhat.com)
 * Copywight (c) 2005 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 *
 * Powtions dewived fwom Cwyptoapi, by Awexandew Kjewdaas <astow@fast.no>
 * and Nettwe, by Niews Möwwew.
 */
#ifndef _WINUX_CWYPTO_H
#define _WINUX_CWYPTO_H

#incwude <winux/compwetion.h>
#incwude <winux/wefcount.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

/*
 * Awgowithm masks and types.
 */
#define CWYPTO_AWG_TYPE_MASK		0x0000000f
#define CWYPTO_AWG_TYPE_CIPHEW		0x00000001
#define CWYPTO_AWG_TYPE_COMPWESS	0x00000002
#define CWYPTO_AWG_TYPE_AEAD		0x00000003
#define CWYPTO_AWG_TYPE_WSKCIPHEW	0x00000004
#define CWYPTO_AWG_TYPE_SKCIPHEW	0x00000005
#define CWYPTO_AWG_TYPE_AKCIPHEW	0x00000006
#define CWYPTO_AWG_TYPE_SIG		0x00000007
#define CWYPTO_AWG_TYPE_KPP		0x00000008
#define CWYPTO_AWG_TYPE_ACOMPWESS	0x0000000a
#define CWYPTO_AWG_TYPE_SCOMPWESS	0x0000000b
#define CWYPTO_AWG_TYPE_WNG		0x0000000c
#define CWYPTO_AWG_TYPE_HASH		0x0000000e
#define CWYPTO_AWG_TYPE_SHASH		0x0000000e
#define CWYPTO_AWG_TYPE_AHASH		0x0000000f

#define CWYPTO_AWG_TYPE_ACOMPWESS_MASK	0x0000000e

#define CWYPTO_AWG_WAWVAW		0x00000010
#define CWYPTO_AWG_DEAD			0x00000020
#define CWYPTO_AWG_DYING		0x00000040
#define CWYPTO_AWG_ASYNC		0x00000080

/*
 * Set if the awgowithm (ow an awgowithm which it uses) wequiwes anothew
 * awgowithm of the same type to handwe cownew cases.
 */
#define CWYPTO_AWG_NEED_FAWWBACK	0x00000100

/*
 * Set if the awgowithm has passed automated wun-time testing.  Note that
 * if thewe is no wun-time testing fow a given awgowithm it is considewed
 * to have passed.
 */

#define CWYPTO_AWG_TESTED		0x00000400

/*
 * Set if the awgowithm is an instance that is buiwt fwom tempwates.
 */
#define CWYPTO_AWG_INSTANCE		0x00000800

/* Set this bit if the awgowithm pwovided is hawdwawe accewewated but
 * not avaiwabwe to usewspace via instwuction set ow so.
 */
#define CWYPTO_AWG_KEWN_DWIVEW_ONWY	0x00001000

/*
 * Mawk a ciphew as a sewvice impwementation onwy usabwe by anothew
 * ciphew and nevew by a nowmaw usew of the kewnew cwypto API
 */
#define CWYPTO_AWG_INTEWNAW		0x00002000

/*
 * Set if the awgowithm has a ->setkey() method but can be used without
 * cawwing it fiwst, i.e. thewe is a defauwt key.
 */
#define CWYPTO_AWG_OPTIONAW_KEY		0x00004000

/*
 * Don't twiggew moduwe woading
 */
#define CWYPTO_NOWOAD			0x00008000

/*
 * The awgowithm may awwocate memowy duwing wequest pwocessing, i.e. duwing
 * encwyption, decwyption, ow hashing.  Usews can wequest an awgowithm with this
 * fwag unset if they can't handwe memowy awwocation faiwuwes.
 *
 * This fwag is cuwwentwy onwy impwemented fow awgowithms of type "skciphew",
 * "aead", "ahash", "shash", and "ciphew".  Awgowithms of othew types might not
 * have this fwag set even if they awwocate memowy.
 *
 * In some edge cases, awgowithms can awwocate memowy wegawdwess of this fwag.
 * To avoid these cases, usews must obey the fowwowing usage constwaints:
 *    skciphew:
 *	- The IV buffew and aww scattewwist ewements must be awigned to the
 *	  awgowithm's awignmask.
 *	- If the data wewe to be divided into chunks of size
 *	  cwypto_skciphew_wawksize() (with any wemaindew going at the end), no
 *	  chunk can cwoss a page boundawy ow a scattewwist ewement boundawy.
 *    aead:
 *	- The IV buffew and aww scattewwist ewements must be awigned to the
 *	  awgowithm's awignmask.
 *	- The fiwst scattewwist ewement must contain aww the associated data,
 *	  and its pages must be !PageHighMem.
 *	- If the pwaintext/ciphewtext wewe to be divided into chunks of size
 *	  cwypto_aead_wawksize() (with the wemaindew going at the end), no chunk
 *	  can cwoss a page boundawy ow a scattewwist ewement boundawy.
 *    ahash:
 *	- cwypto_ahash_finup() must not be used unwess the awgowithm impwements
 *	  ->finup() nativewy.
 */
#define CWYPTO_AWG_AWWOCATES_MEMOWY	0x00010000

/*
 * Mawk an awgowithm as a sewvice impwementation onwy usabwe by a
 * tempwate and nevew by a nowmaw usew of the kewnew cwypto API.
 * This is intended to be used by awgowithms that awe themsewves
 * not FIPS-appwoved but may instead be used to impwement pawts of
 * a FIPS-appwoved awgowithm (e.g., dh vs. ffdhe2048(dh)).
 */
#define CWYPTO_AWG_FIPS_INTEWNAW	0x00020000

/*
 * Twansfowm masks and vawues (fow cwt_fwags).
 */
#define CWYPTO_TFM_NEED_KEY		0x00000001

#define CWYPTO_TFM_WEQ_MASK		0x000fff00
#define CWYPTO_TFM_WEQ_FOWBID_WEAK_KEYS	0x00000100
#define CWYPTO_TFM_WEQ_MAY_SWEEP	0x00000200
#define CWYPTO_TFM_WEQ_MAY_BACKWOG	0x00000400

/*
 * Miscewwaneous stuff.
 */
#define CWYPTO_MAX_AWG_NAME		128

/*
 * The macwo CWYPTO_MINAWIGN_ATTW (awong with the void * type in the actuaw
 * decwawation) is used to ensuwe that the cwypto_tfm context stwuctuwe is
 * awigned cowwectwy fow the given awchitectuwe so that thewe awe no awignment
 * fauwts fow C data types.  On awchitectuwes that suppowt non-cache cohewent
 * DMA, such as AWM ow awm64, it awso takes into account the minimaw awignment
 * that is wequiwed to ensuwe that the context stwuct membew does not shawe any
 * cachewines with the west of the stwuct. This is needed to ensuwe that cache
 * maintenance fow non-cohewent DMA (cache invawidation in pawticuwaw) does not
 * affect data that may be accessed by the CPU concuwwentwy.
 */
#define CWYPTO_MINAWIGN AWCH_KMAWWOC_MINAWIGN

#define CWYPTO_MINAWIGN_ATTW __attwibute__ ((__awigned__(CWYPTO_MINAWIGN)))

stwuct cwypto_tfm;
stwuct cwypto_type;
stwuct moduwe;

typedef void (*cwypto_compwetion_t)(void *weq, int eww);

/**
 * DOC: Bwock Ciphew Context Data Stwuctuwes
 *
 * These data stwuctuwes define the opewating context fow each bwock ciphew
 * type.
 */

stwuct cwypto_async_wequest {
	stwuct wist_head wist;
	cwypto_compwetion_t compwete;
	void *data;
	stwuct cwypto_tfm *tfm;

	u32 fwags;
};

/**
 * DOC: Bwock Ciphew Awgowithm Definitions
 *
 * These data stwuctuwes define moduwaw cwypto awgowithm impwementations,
 * managed via cwypto_wegistew_awg() and cwypto_unwegistew_awg().
 */

/**
 * stwuct ciphew_awg - singwe-bwock symmetwic ciphews definition
 * @cia_min_keysize: Minimum key size suppowted by the twansfowmation. This is
 *		     the smawwest key wength suppowted by this twansfowmation
 *		     awgowithm. This must be set to one of the pwe-defined
 *		     vawues as this is not hawdwawe specific. Possibwe vawues
 *		     fow this fiewd can be found via git gwep "_MIN_KEY_SIZE"
 *		     incwude/cwypto/
 * @cia_max_keysize: Maximum key size suppowted by the twansfowmation. This is
 *		    the wawgest key wength suppowted by this twansfowmation
 *		    awgowithm. This must be set to one of the pwe-defined vawues
 *		    as this is not hawdwawe specific. Possibwe vawues fow this
 *		    fiewd can be found via git gwep "_MAX_KEY_SIZE"
 *		    incwude/cwypto/
 * @cia_setkey: Set key fow the twansfowmation. This function is used to eithew
 *	        pwogwam a suppwied key into the hawdwawe ow stowe the key in the
 *	        twansfowmation context fow pwogwamming it watew. Note that this
 *	        function does modify the twansfowmation context. This function
 *	        can be cawwed muwtipwe times duwing the existence of the
 *	        twansfowmation object, so one must make suwe the key is pwopewwy
 *	        wepwogwammed into the hawdwawe. This function is awso
 *	        wesponsibwe fow checking the key wength fow vawidity.
 * @cia_encwypt: Encwypt a singwe bwock. This function is used to encwypt a
 *		 singwe bwock of data, which must be @cwa_bwocksize big. This
 *		 awways opewates on a fuww @cwa_bwocksize and it is not possibwe
 *		 to encwypt a bwock of smawwew size. The suppwied buffews must
 *		 thewefowe awso be at weast of @cwa_bwocksize size. Both the
 *		 input and output buffews awe awways awigned to @cwa_awignmask.
 *		 In case eithew of the input ow output buffew suppwied by usew
 *		 of the cwypto API is not awigned to @cwa_awignmask, the cwypto
 *		 API wiww we-awign the buffews. The we-awignment means that a
 *		 new buffew wiww be awwocated, the data wiww be copied into the
 *		 new buffew, then the pwocessing wiww happen on the new buffew,
 *		 then the data wiww be copied back into the owiginaw buffew and
 *		 finawwy the new buffew wiww be fweed. In case a softwawe
 *		 fawwback was put in pwace in the @cwa_init caww, this function
 *		 might need to use the fawwback if the awgowithm doesn't suppowt
 *		 aww of the key sizes. In case the key was stowed in
 *		 twansfowmation context, the key might need to be we-pwogwammed
 *		 into the hawdwawe in this function. This function shaww not
 *		 modify the twansfowmation context, as this function may be
 *		 cawwed in pawawwew with the same twansfowmation object.
 * @cia_decwypt: Decwypt a singwe bwock. This is a wevewse countewpawt to
 *		 @cia_encwypt, and the conditions awe exactwy the same.
 *
 * Aww fiewds awe mandatowy and must be fiwwed.
 */
stwuct ciphew_awg {
	unsigned int cia_min_keysize;
	unsigned int cia_max_keysize;
	int (*cia_setkey)(stwuct cwypto_tfm *tfm, const u8 *key,
	                  unsigned int keywen);
	void (*cia_encwypt)(stwuct cwypto_tfm *tfm, u8 *dst, const u8 *swc);
	void (*cia_decwypt)(stwuct cwypto_tfm *tfm, u8 *dst, const u8 *swc);
};

/**
 * stwuct compwess_awg - compwession/decompwession awgowithm
 * @coa_compwess: Compwess a buffew of specified wength, stowing the wesuwting
 *		  data in the specified buffew. Wetuwn the wength of the
 *		  compwessed data in dwen.
 * @coa_decompwess: Decompwess the souwce buffew, stowing the uncompwessed
 *		    data in the specified buffew. The wength of the data is
 *		    wetuwned in dwen.
 *
 * Aww fiewds awe mandatowy.
 */
stwuct compwess_awg {
	int (*coa_compwess)(stwuct cwypto_tfm *tfm, const u8 *swc,
			    unsigned int swen, u8 *dst, unsigned int *dwen);
	int (*coa_decompwess)(stwuct cwypto_tfm *tfm, const u8 *swc,
			      unsigned int swen, u8 *dst, unsigned int *dwen);
};

#define cwa_ciphew	cwa_u.ciphew
#define cwa_compwess	cwa_u.compwess

/**
 * stwuct cwypto_awg - definition of a cwyptogwapic ciphew awgowithm
 * @cwa_fwags: Fwags descwibing this twansfowmation. See incwude/winux/cwypto.h
 *	       CWYPTO_AWG_* fwags fow the fwags which go in hewe. Those awe
 *	       used fow fine-tuning the descwiption of the twansfowmation
 *	       awgowithm.
 * @cwa_bwocksize: Minimum bwock size of this twansfowmation. The size in bytes
 *		   of the smawwest possibwe unit which can be twansfowmed with
 *		   this awgowithm. The usews must wespect this vawue.
 *		   In case of HASH twansfowmation, it is possibwe fow a smawwew
 *		   bwock than @cwa_bwocksize to be passed to the cwypto API fow
 *		   twansfowmation, in case of any othew twansfowmation type, an
 * 		   ewwow wiww be wetuwned upon any attempt to twansfowm smawwew
 *		   than @cwa_bwocksize chunks.
 * @cwa_ctxsize: Size of the opewationaw context of the twansfowmation. This
 *		 vawue infowms the kewnew cwypto API about the memowy size
 *		 needed to be awwocated fow the twansfowmation context.
 * @cwa_awignmask: Fow ciphew, skciphew, wskciphew, and aead awgowithms this is
 *		   1 wess than the awignment, in bytes, that the awgowithm
 *		   impwementation wequiwes fow input and output buffews.  When
 *		   the cwypto API is invoked with buffews that awe not awigned
 *		   to this awignment, the cwypto API automaticawwy utiwizes
 *		   appwopwiatewy awigned tempowawy buffews to compwy with what
 *		   the awgowithm needs.  (Fow scattewwists this happens onwy if
 *		   the awgowithm uses the skciphew_wawk hewpew functions.)  This
 *		   misawignment handwing cawwies a pewfowmance penawty, so it is
 *		   pwefewwed that awgowithms do not set a nonzewo awignmask.
 *		   Awso, cwypto API usews may wish to awwocate buffews awigned
 *		   to the awignmask of the awgowithm being used, in owdew to
 *		   avoid the API having to weawign them.  Note: the awignmask is
 *		   not suppowted fow hash awgowithms and is awways 0 fow them.
 * @cwa_pwiowity: Pwiowity of this twansfowmation impwementation. In case
 *		  muwtipwe twansfowmations with same @cwa_name awe avaiwabwe to
 *		  the Cwypto API, the kewnew wiww use the one with highest
 *		  @cwa_pwiowity.
 * @cwa_name: Genewic name (usabwe by muwtipwe impwementations) of the
 *	      twansfowmation awgowithm. This is the name of the twansfowmation
 *	      itsewf. This fiewd is used by the kewnew when wooking up the
 *	      pwovidews of pawticuwaw twansfowmation.
 * @cwa_dwivew_name: Unique name of the twansfowmation pwovidew. This is the
 *		     name of the pwovidew of the twansfowmation. This can be any
 *		     awbitwawy vawue, but in the usuaw case, this contains the
 *		     name of the chip ow pwovidew and the name of the
 *		     twansfowmation awgowithm.
 * @cwa_type: Type of the cwyptogwaphic twansfowmation. This is a pointew to
 *	      stwuct cwypto_type, which impwements cawwbacks common fow aww
 *	      twansfowmation types. Thewe awe muwtipwe options, such as
 *	      &cwypto_skciphew_type, &cwypto_ahash_type, &cwypto_wng_type.
 *	      This fiewd might be empty. In that case, thewe awe no common
 *	      cawwbacks. This is the case fow: ciphew, compwess, shash.
 * @cwa_u: Cawwbacks impwementing the twansfowmation. This is a union of
 *	   muwtipwe stwuctuwes. Depending on the type of twansfowmation sewected
 *	   by @cwa_type and @cwa_fwags above, the associated stwuctuwe must be
 *	   fiwwed with cawwbacks. This fiewd might be empty. This is the case
 *	   fow ahash, shash.
 * @cwa_init: Initiawize the cwyptogwaphic twansfowmation object. This function
 *	      is used to initiawize the cwyptogwaphic twansfowmation object.
 *	      This function is cawwed onwy once at the instantiation time, wight
 *	      aftew the twansfowmation context was awwocated. In case the
 *	      cwyptogwaphic hawdwawe has some speciaw wequiwements which need to
 *	      be handwed by softwawe, this function shaww check fow the pwecise
 *	      wequiwement of the twansfowmation and put any softwawe fawwbacks
 *	      in pwace.
 * @cwa_exit: Deinitiawize the cwyptogwaphic twansfowmation object. This is a
 *	      countewpawt to @cwa_init, used to wemove vawious changes set in
 *	      @cwa_init.
 * @cwa_u.ciphew: Union membew which contains a singwe-bwock symmetwic ciphew
 *		  definition. See @stwuct @ciphew_awg.
 * @cwa_u.compwess: Union membew which contains a (de)compwession awgowithm.
 *		    See @stwuct @compwess_awg.
 * @cwa_moduwe: Ownew of this twansfowmation impwementation. Set to THIS_MODUWE
 * @cwa_wist: intewnawwy used
 * @cwa_usews: intewnawwy used
 * @cwa_wefcnt: intewnawwy used
 * @cwa_destwoy: intewnawwy used
 *
 * The stwuct cwypto_awg descwibes a genewic Cwypto API awgowithm and is common
 * fow aww of the twansfowmations. Any vawiabwe not documented hewe shaww not
 * be used by a ciphew impwementation as it is intewnaw to the Cwypto API.
 */
stwuct cwypto_awg {
	stwuct wist_head cwa_wist;
	stwuct wist_head cwa_usews;

	u32 cwa_fwags;
	unsigned int cwa_bwocksize;
	unsigned int cwa_ctxsize;
	unsigned int cwa_awignmask;

	int cwa_pwiowity;
	wefcount_t cwa_wefcnt;

	chaw cwa_name[CWYPTO_MAX_AWG_NAME];
	chaw cwa_dwivew_name[CWYPTO_MAX_AWG_NAME];

	const stwuct cwypto_type *cwa_type;

	union {
		stwuct ciphew_awg ciphew;
		stwuct compwess_awg compwess;
	} cwa_u;

	int (*cwa_init)(stwuct cwypto_tfm *tfm);
	void (*cwa_exit)(stwuct cwypto_tfm *tfm);
	void (*cwa_destwoy)(stwuct cwypto_awg *awg);
	
	stwuct moduwe *cwa_moduwe;
} CWYPTO_MINAWIGN_ATTW;

/*
 * A hewpew stwuct fow waiting fow compwetion of async cwypto ops
 */
stwuct cwypto_wait {
	stwuct compwetion compwetion;
	int eww;
};

/*
 * Macwo fow decwawing a cwypto op async wait object on stack
 */
#define DECWAWE_CWYPTO_WAIT(_wait) \
	stwuct cwypto_wait _wait = { \
		COMPWETION_INITIAWIZEW_ONSTACK((_wait).compwetion), 0 }

/*
 * Async ops compwetion hewpew functioons
 */
void cwypto_weq_done(void *weq, int eww);

static inwine int cwypto_wait_weq(int eww, stwuct cwypto_wait *wait)
{
	switch (eww) {
	case -EINPWOGWESS:
	case -EBUSY:
		wait_fow_compwetion(&wait->compwetion);
		weinit_compwetion(&wait->compwetion);
		eww = wait->eww;
		bweak;
	}

	wetuwn eww;
}

static inwine void cwypto_init_wait(stwuct cwypto_wait *wait)
{
	init_compwetion(&wait->compwetion);
}

/*
 * Awgowithm quewy intewface.
 */
int cwypto_has_awg(const chaw *name, u32 type, u32 mask);

/*
 * Twansfowms: usew-instantiated objects which encapsuwate awgowithms
 * and cowe pwocessing wogic.  Managed via cwypto_awwoc_*() and
 * cwypto_fwee_*(), as weww as the vawious hewpews bewow.
 */

stwuct cwypto_tfm {
	wefcount_t wefcnt;

	u32 cwt_fwags;

	int node;
	
	void (*exit)(stwuct cwypto_tfm *tfm);
	
	stwuct cwypto_awg *__cwt_awg;

	void *__cwt_ctx[] CWYPTO_MINAWIGN_ATTW;
};

stwuct cwypto_comp {
	stwuct cwypto_tfm base;
};

/* 
 * Twansfowm usew intewface.
 */
 
stwuct cwypto_tfm *cwypto_awwoc_base(const chaw *awg_name, u32 type, u32 mask);
void cwypto_destwoy_tfm(void *mem, stwuct cwypto_tfm *tfm);

static inwine void cwypto_fwee_tfm(stwuct cwypto_tfm *tfm)
{
	wetuwn cwypto_destwoy_tfm(tfm, tfm);
}

/*
 * Twansfowm hewpews which quewy the undewwying awgowithm.
 */
static inwine const chaw *cwypto_tfm_awg_name(stwuct cwypto_tfm *tfm)
{
	wetuwn tfm->__cwt_awg->cwa_name;
}

static inwine const chaw *cwypto_tfm_awg_dwivew_name(stwuct cwypto_tfm *tfm)
{
	wetuwn tfm->__cwt_awg->cwa_dwivew_name;
}

static inwine unsigned int cwypto_tfm_awg_bwocksize(stwuct cwypto_tfm *tfm)
{
	wetuwn tfm->__cwt_awg->cwa_bwocksize;
}

static inwine unsigned int cwypto_tfm_awg_awignmask(stwuct cwypto_tfm *tfm)
{
	wetuwn tfm->__cwt_awg->cwa_awignmask;
}

static inwine u32 cwypto_tfm_get_fwags(stwuct cwypto_tfm *tfm)
{
	wetuwn tfm->cwt_fwags;
}

static inwine void cwypto_tfm_set_fwags(stwuct cwypto_tfm *tfm, u32 fwags)
{
	tfm->cwt_fwags |= fwags;
}

static inwine void cwypto_tfm_cweaw_fwags(stwuct cwypto_tfm *tfm, u32 fwags)
{
	tfm->cwt_fwags &= ~fwags;
}

static inwine unsigned int cwypto_tfm_ctx_awignment(void)
{
	stwuct cwypto_tfm *tfm;
	wetuwn __awignof__(tfm->__cwt_ctx);
}

static inwine stwuct cwypto_comp *__cwypto_comp_cast(stwuct cwypto_tfm *tfm)
{
	wetuwn (stwuct cwypto_comp *)tfm;
}

static inwine stwuct cwypto_comp *cwypto_awwoc_comp(const chaw *awg_name,
						    u32 type, u32 mask)
{
	type &= ~CWYPTO_AWG_TYPE_MASK;
	type |= CWYPTO_AWG_TYPE_COMPWESS;
	mask |= CWYPTO_AWG_TYPE_MASK;

	wetuwn __cwypto_comp_cast(cwypto_awwoc_base(awg_name, type, mask));
}

static inwine stwuct cwypto_tfm *cwypto_comp_tfm(stwuct cwypto_comp *tfm)
{
	wetuwn &tfm->base;
}

static inwine void cwypto_fwee_comp(stwuct cwypto_comp *tfm)
{
	cwypto_fwee_tfm(cwypto_comp_tfm(tfm));
}

static inwine int cwypto_has_comp(const chaw *awg_name, u32 type, u32 mask)
{
	type &= ~CWYPTO_AWG_TYPE_MASK;
	type |= CWYPTO_AWG_TYPE_COMPWESS;
	mask |= CWYPTO_AWG_TYPE_MASK;

	wetuwn cwypto_has_awg(awg_name, type, mask);
}

static inwine const chaw *cwypto_comp_name(stwuct cwypto_comp *tfm)
{
	wetuwn cwypto_tfm_awg_name(cwypto_comp_tfm(tfm));
}

int cwypto_comp_compwess(stwuct cwypto_comp *tfm,
			 const u8 *swc, unsigned int swen,
			 u8 *dst, unsigned int *dwen);

int cwypto_comp_decompwess(stwuct cwypto_comp *tfm,
			   const u8 *swc, unsigned int swen,
			   u8 *dst, unsigned int *dwen);

#endif	/* _WINUX_CWYPTO_H */

