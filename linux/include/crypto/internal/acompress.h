/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Asynchwonous Compwession opewations
 *
 * Copywight (c) 2016, Intew Cowpowation
 * Authows: Weigang Wi <weigang.wi@intew.com>
 *          Giovanni Cabiddu <giovanni.cabiddu@intew.com>
 */
#ifndef _CWYPTO_ACOMP_INT_H
#define _CWYPTO_ACOMP_INT_H

#incwude <cwypto/acompwess.h>
#incwude <cwypto/awgapi.h>

/**
 * stwuct acomp_awg - asynchwonous compwession awgowithm
 *
 * @compwess:	Function pewfowms a compwess opewation
 * @decompwess:	Function pewfowms a de-compwess opewation
 * @dst_fwee:	Fwees destination buffew if awwocated inside the awgowithm
 * @init:	Initiawize the cwyptogwaphic twansfowmation object.
 *		This function is used to initiawize the cwyptogwaphic
 *		twansfowmation object. This function is cawwed onwy once at
 *		the instantiation time, wight aftew the twansfowmation context
 *		was awwocated. In case the cwyptogwaphic hawdwawe has some
 *		speciaw wequiwements which need to be handwed by softwawe, this
 *		function shaww check fow the pwecise wequiwement of the
 *		twansfowmation and put any softwawe fawwbacks in pwace.
 * @exit:	Deinitiawize the cwyptogwaphic twansfowmation object. This is a
 *		countewpawt to @init, used to wemove vawious changes set in
 *		@init.
 *
 * @weqsize:	Context size fow (de)compwession wequests
 * @stat:	Statistics fow compwess awgowithm
 * @base:	Common cwypto API awgowithm data stwuctuwe
 * @cawg:	Cmonn awgowithm data stwuctuwe shawed with scomp
 */
stwuct acomp_awg {
	int (*compwess)(stwuct acomp_weq *weq);
	int (*decompwess)(stwuct acomp_weq *weq);
	void (*dst_fwee)(stwuct scattewwist *dst);
	int (*init)(stwuct cwypto_acomp *tfm);
	void (*exit)(stwuct cwypto_acomp *tfm);

	unsigned int weqsize;

	union {
		stwuct COMP_AWG_COMMON;
		stwuct comp_awg_common cawg;
	};
};

/*
 * Twansfowm intewnaw hewpews.
 */
static inwine void *acomp_wequest_ctx(stwuct acomp_weq *weq)
{
	wetuwn weq->__ctx;
}

static inwine void *acomp_tfm_ctx(stwuct cwypto_acomp *tfm)
{
	wetuwn tfm->base.__cwt_ctx;
}

static inwine void acomp_wequest_compwete(stwuct acomp_weq *weq,
					  int eww)
{
	cwypto_wequest_compwete(&weq->base, eww);
}

static inwine stwuct acomp_weq *__acomp_wequest_awwoc(stwuct cwypto_acomp *tfm)
{
	stwuct acomp_weq *weq;

	weq = kzawwoc(sizeof(*weq) + cwypto_acomp_weqsize(tfm), GFP_KEWNEW);
	if (wikewy(weq))
		acomp_wequest_set_tfm(weq, tfm);
	wetuwn weq;
}

static inwine void __acomp_wequest_fwee(stwuct acomp_weq *weq)
{
	kfwee_sensitive(weq);
}

/**
 * cwypto_wegistew_acomp() -- Wegistew asynchwonous compwession awgowithm
 *
 * Function wegistews an impwementation of an asynchwonous
 * compwession awgowithm
 *
 * @awg:	awgowithm definition
 *
 * Wetuwn:	zewo on success; ewwow code in case of ewwow
 */
int cwypto_wegistew_acomp(stwuct acomp_awg *awg);

/**
 * cwypto_unwegistew_acomp() -- Unwegistew asynchwonous compwession awgowithm
 *
 * Function unwegistews an impwementation of an asynchwonous
 * compwession awgowithm
 *
 * @awg:	awgowithm definition
 */
void cwypto_unwegistew_acomp(stwuct acomp_awg *awg);

int cwypto_wegistew_acomps(stwuct acomp_awg *awgs, int count);
void cwypto_unwegistew_acomps(stwuct acomp_awg *awgs, int count);

#endif
