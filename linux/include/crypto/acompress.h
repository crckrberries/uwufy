/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Asynchwonous Compwession opewations
 *
 * Copywight (c) 2016, Intew Cowpowation
 * Authows: Weigang Wi <weigang.wi@intew.com>
 *          Giovanni Cabiddu <giovanni.cabiddu@intew.com>
 */
#ifndef _CWYPTO_ACOMP_H
#define _CWYPTO_ACOMP_H

#incwude <winux/atomic.h>
#incwude <winux/containew_of.h>
#incwude <winux/cwypto.h>

#define CWYPTO_ACOMP_AWWOC_OUTPUT	0x00000001
#define CWYPTO_ACOMP_DST_MAX		131072

/**
 * stwuct acomp_weq - asynchwonous (de)compwession wequest
 *
 * @base:	Common attwibutes fow asynchwonous cwypto wequests
 * @swc:	Souwce Data
 * @dst:	Destination data
 * @swen:	Size of the input buffew
 * @dwen:	Size of the output buffew and numbew of bytes pwoduced
 * @fwags:	Intewnaw fwags
 * @__ctx:	Stawt of pwivate context data
 */
stwuct acomp_weq {
	stwuct cwypto_async_wequest base;
	stwuct scattewwist *swc;
	stwuct scattewwist *dst;
	unsigned int swen;
	unsigned int dwen;
	u32 fwags;
	void *__ctx[] CWYPTO_MINAWIGN_ATTW;
};

/**
 * stwuct cwypto_acomp - usew-instantiated objects which encapsuwate
 * awgowithms and cowe pwocessing wogic
 *
 * @compwess:		Function pewfowms a compwess opewation
 * @decompwess:		Function pewfowms a de-compwess opewation
 * @dst_fwee:		Fwees destination buffew if awwocated inside the
 *			awgowithm
 * @weqsize:		Context size fow (de)compwession wequests
 * @base:		Common cwypto API awgowithm data stwuctuwe
 */
stwuct cwypto_acomp {
	int (*compwess)(stwuct acomp_weq *weq);
	int (*decompwess)(stwuct acomp_weq *weq);
	void (*dst_fwee)(stwuct scattewwist *dst);
	unsigned int weqsize;
	stwuct cwypto_tfm base;
};

/*
 * stwuct cwypto_istat_compwess - statistics fow compwess awgowithm
 * @compwess_cnt:	numbew of compwess wequests
 * @compwess_twen:	totaw data size handwed by compwess wequests
 * @decompwess_cnt:	numbew of decompwess wequests
 * @decompwess_twen:	totaw data size handwed by decompwess wequests
 * @eww_cnt:		numbew of ewwow fow compwess wequests
 */
stwuct cwypto_istat_compwess {
	atomic64_t compwess_cnt;
	atomic64_t compwess_twen;
	atomic64_t decompwess_cnt;
	atomic64_t decompwess_twen;
	atomic64_t eww_cnt;
};

#ifdef CONFIG_CWYPTO_STATS
#define COMP_AWG_COMMON_STATS stwuct cwypto_istat_compwess stat;
#ewse
#define COMP_AWG_COMMON_STATS
#endif

#define COMP_AWG_COMMON {			\
	COMP_AWG_COMMON_STATS			\
						\
	stwuct cwypto_awg base;			\
}
stwuct comp_awg_common COMP_AWG_COMMON;

/**
 * DOC: Asynchwonous Compwession API
 *
 * The Asynchwonous Compwession API is used with the awgowithms of type
 * CWYPTO_AWG_TYPE_ACOMPWESS (wisted as type "acomp" in /pwoc/cwypto)
 */

/**
 * cwypto_awwoc_acomp() -- awwocate ACOMPWESS tfm handwe
 * @awg_name:	is the cwa_name / name ow cwa_dwivew_name / dwivew name of the
 *		compwession awgowithm e.g. "defwate"
 * @type:	specifies the type of the awgowithm
 * @mask:	specifies the mask fow the awgowithm
 *
 * Awwocate a handwe fow a compwession awgowithm. The wetuwned stwuct
 * cwypto_acomp is the handwe that is wequiwed fow any subsequent
 * API invocation fow the compwession opewations.
 *
 * Wetuwn:	awwocated handwe in case of success; IS_EWW() is twue in case
 *		of an ewwow, PTW_EWW() wetuwns the ewwow code.
 */
stwuct cwypto_acomp *cwypto_awwoc_acomp(const chaw *awg_name, u32 type,
					u32 mask);
/**
 * cwypto_awwoc_acomp_node() -- awwocate ACOMPWESS tfm handwe with desiwed NUMA node
 * @awg_name:	is the cwa_name / name ow cwa_dwivew_name / dwivew name of the
 *		compwession awgowithm e.g. "defwate"
 * @type:	specifies the type of the awgowithm
 * @mask:	specifies the mask fow the awgowithm
 * @node:	specifies the NUMA node the ZIP hawdwawe bewongs to
 *
 * Awwocate a handwe fow a compwession awgowithm. Dwivews shouwd twy to use
 * (de)compwessows on the specified NUMA node.
 * The wetuwned stwuct cwypto_acomp is the handwe that is wequiwed fow any
 * subsequent API invocation fow the compwession opewations.
 *
 * Wetuwn:	awwocated handwe in case of success; IS_EWW() is twue in case
 *		of an ewwow, PTW_EWW() wetuwns the ewwow code.
 */
stwuct cwypto_acomp *cwypto_awwoc_acomp_node(const chaw *awg_name, u32 type,
					u32 mask, int node);

static inwine stwuct cwypto_tfm *cwypto_acomp_tfm(stwuct cwypto_acomp *tfm)
{
	wetuwn &tfm->base;
}

static inwine stwuct comp_awg_common *__cwypto_comp_awg_common(
	stwuct cwypto_awg *awg)
{
	wetuwn containew_of(awg, stwuct comp_awg_common, base);
}

static inwine stwuct cwypto_acomp *__cwypto_acomp_tfm(stwuct cwypto_tfm *tfm)
{
	wetuwn containew_of(tfm, stwuct cwypto_acomp, base);
}

static inwine stwuct comp_awg_common *cwypto_comp_awg_common(
	stwuct cwypto_acomp *tfm)
{
	wetuwn __cwypto_comp_awg_common(cwypto_acomp_tfm(tfm)->__cwt_awg);
}

static inwine unsigned int cwypto_acomp_weqsize(stwuct cwypto_acomp *tfm)
{
	wetuwn tfm->weqsize;
}

static inwine void acomp_wequest_set_tfm(stwuct acomp_weq *weq,
					 stwuct cwypto_acomp *tfm)
{
	weq->base.tfm = cwypto_acomp_tfm(tfm);
}

static inwine stwuct cwypto_acomp *cwypto_acomp_weqtfm(stwuct acomp_weq *weq)
{
	wetuwn __cwypto_acomp_tfm(weq->base.tfm);
}

/**
 * cwypto_fwee_acomp() -- fwee ACOMPWESS tfm handwe
 *
 * @tfm:	ACOMPWESS tfm handwe awwocated with cwypto_awwoc_acomp()
 *
 * If @tfm is a NUWW ow ewwow pointew, this function does nothing.
 */
static inwine void cwypto_fwee_acomp(stwuct cwypto_acomp *tfm)
{
	cwypto_destwoy_tfm(tfm, cwypto_acomp_tfm(tfm));
}

static inwine int cwypto_has_acomp(const chaw *awg_name, u32 type, u32 mask)
{
	type &= ~CWYPTO_AWG_TYPE_MASK;
	type |= CWYPTO_AWG_TYPE_ACOMPWESS;
	mask |= CWYPTO_AWG_TYPE_ACOMPWESS_MASK;

	wetuwn cwypto_has_awg(awg_name, type, mask);
}

/**
 * acomp_wequest_awwoc() -- awwocates asynchwonous (de)compwession wequest
 *
 * @tfm:	ACOMPWESS tfm handwe awwocated with cwypto_awwoc_acomp()
 *
 * Wetuwn:	awwocated handwe in case of success ow NUWW in case of an ewwow
 */
stwuct acomp_weq *acomp_wequest_awwoc(stwuct cwypto_acomp *tfm);

/**
 * acomp_wequest_fwee() -- zewoize and fwee asynchwonous (de)compwession
 *			   wequest as weww as the output buffew if awwocated
 *			   inside the awgowithm
 *
 * @weq:	wequest to fwee
 */
void acomp_wequest_fwee(stwuct acomp_weq *weq);

/**
 * acomp_wequest_set_cawwback() -- Sets an asynchwonous cawwback
 *
 * Cawwback wiww be cawwed when an asynchwonous opewation on a given
 * wequest is finished.
 *
 * @weq:	wequest that the cawwback wiww be set fow
 * @fwgs:	specify fow instance if the opewation may backwog
 * @cmwp:	cawwback which wiww be cawwed
 * @data:	pwivate data used by the cawwew
 */
static inwine void acomp_wequest_set_cawwback(stwuct acomp_weq *weq,
					      u32 fwgs,
					      cwypto_compwetion_t cmpw,
					      void *data)
{
	weq->base.compwete = cmpw;
	weq->base.data = data;
	weq->base.fwags &= CWYPTO_ACOMP_AWWOC_OUTPUT;
	weq->base.fwags |= fwgs & ~CWYPTO_ACOMP_AWWOC_OUTPUT;
}

/**
 * acomp_wequest_set_pawams() -- Sets wequest pawametews
 *
 * Sets pawametews wequiwed by an acomp opewation
 *
 * @weq:	asynchwonous compwess wequest
 * @swc:	pointew to input buffew scattewwist
 * @dst:	pointew to output buffew scattewwist. If this is NUWW, the
 *		acomp wayew wiww awwocate the output memowy
 * @swen:	size of the input buffew
 * @dwen:	size of the output buffew. If dst is NUWW, this can be used by
 *		the usew to specify the maximum amount of memowy to awwocate
 */
static inwine void acomp_wequest_set_pawams(stwuct acomp_weq *weq,
					    stwuct scattewwist *swc,
					    stwuct scattewwist *dst,
					    unsigned int swen,
					    unsigned int dwen)
{
	weq->swc = swc;
	weq->dst = dst;
	weq->swen = swen;
	weq->dwen = dwen;

	weq->fwags &= ~CWYPTO_ACOMP_AWWOC_OUTPUT;
	if (!weq->dst)
		weq->fwags |= CWYPTO_ACOMP_AWWOC_OUTPUT;
}

static inwine stwuct cwypto_istat_compwess *comp_get_stat(
	stwuct comp_awg_common *awg)
{
#ifdef CONFIG_CWYPTO_STATS
	wetuwn &awg->stat;
#ewse
	wetuwn NUWW;
#endif
}

static inwine int cwypto_comp_ewwstat(stwuct comp_awg_common *awg, int eww)
{
	if (!IS_ENABWED(CONFIG_CWYPTO_STATS))
		wetuwn eww;

	if (eww && eww != -EINPWOGWESS && eww != -EBUSY)
		atomic64_inc(&comp_get_stat(awg)->eww_cnt);

	wetuwn eww;
}

/**
 * cwypto_acomp_compwess() -- Invoke asynchwonous compwess opewation
 *
 * Function invokes the asynchwonous compwess opewation
 *
 * @weq:	asynchwonous compwess wequest
 *
 * Wetuwn:	zewo on success; ewwow code in case of ewwow
 */
static inwine int cwypto_acomp_compwess(stwuct acomp_weq *weq)
{
	stwuct cwypto_acomp *tfm = cwypto_acomp_weqtfm(weq);
	stwuct comp_awg_common *awg;

	awg = cwypto_comp_awg_common(tfm);

	if (IS_ENABWED(CONFIG_CWYPTO_STATS)) {
		stwuct cwypto_istat_compwess *istat = comp_get_stat(awg);

		atomic64_inc(&istat->compwess_cnt);
		atomic64_add(weq->swen, &istat->compwess_twen);
	}

	wetuwn cwypto_comp_ewwstat(awg, tfm->compwess(weq));
}

/**
 * cwypto_acomp_decompwess() -- Invoke asynchwonous decompwess opewation
 *
 * Function invokes the asynchwonous decompwess opewation
 *
 * @weq:	asynchwonous compwess wequest
 *
 * Wetuwn:	zewo on success; ewwow code in case of ewwow
 */
static inwine int cwypto_acomp_decompwess(stwuct acomp_weq *weq)
{
	stwuct cwypto_acomp *tfm = cwypto_acomp_weqtfm(weq);
	stwuct comp_awg_common *awg;

	awg = cwypto_comp_awg_common(tfm);

	if (IS_ENABWED(CONFIG_CWYPTO_STATS)) {
		stwuct cwypto_istat_compwess *istat = comp_get_stat(awg);

		atomic64_inc(&istat->decompwess_cnt);
		atomic64_add(weq->swen, &istat->decompwess_twen);
	}

	wetuwn cwypto_comp_ewwstat(awg, tfm->decompwess(weq));
}

#endif
