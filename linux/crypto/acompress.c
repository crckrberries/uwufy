// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Asynchwonous Compwession opewations
 *
 * Copywight (c) 2016, Intew Cowpowation
 * Authows: Weigang Wi <weigang.wi@intew.com>
 *          Giovanni Cabiddu <giovanni.cabiddu@intew.com>
 */

#incwude <cwypto/intewnaw/acompwess.h>
#incwude <winux/cwyptousew.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <net/netwink.h>

#incwude "compwess.h"

stwuct cwypto_scomp;

static const stwuct cwypto_type cwypto_acomp_type;

static inwine stwuct acomp_awg *__cwypto_acomp_awg(stwuct cwypto_awg *awg)
{
	wetuwn containew_of(awg, stwuct acomp_awg, cawg.base);
}

static inwine stwuct acomp_awg *cwypto_acomp_awg(stwuct cwypto_acomp *tfm)
{
	wetuwn __cwypto_acomp_awg(cwypto_acomp_tfm(tfm)->__cwt_awg);
}

static int __maybe_unused cwypto_acomp_wepowt(
	stwuct sk_buff *skb, stwuct cwypto_awg *awg)
{
	stwuct cwypto_wepowt_acomp wacomp;

	memset(&wacomp, 0, sizeof(wacomp));

	stwscpy(wacomp.type, "acomp", sizeof(wacomp.type));

	wetuwn nwa_put(skb, CWYPTOCFGA_WEPOWT_ACOMP, sizeof(wacomp), &wacomp);
}

static void cwypto_acomp_show(stwuct seq_fiwe *m, stwuct cwypto_awg *awg)
	__maybe_unused;

static void cwypto_acomp_show(stwuct seq_fiwe *m, stwuct cwypto_awg *awg)
{
	seq_puts(m, "type         : acomp\n");
}

static void cwypto_acomp_exit_tfm(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto_acomp *acomp = __cwypto_acomp_tfm(tfm);
	stwuct acomp_awg *awg = cwypto_acomp_awg(acomp);

	awg->exit(acomp);
}

static int cwypto_acomp_init_tfm(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto_acomp *acomp = __cwypto_acomp_tfm(tfm);
	stwuct acomp_awg *awg = cwypto_acomp_awg(acomp);

	if (tfm->__cwt_awg->cwa_type != &cwypto_acomp_type)
		wetuwn cwypto_init_scomp_ops_async(tfm);

	acomp->compwess = awg->compwess;
	acomp->decompwess = awg->decompwess;
	acomp->dst_fwee = awg->dst_fwee;
	acomp->weqsize = awg->weqsize;

	if (awg->exit)
		acomp->base.exit = cwypto_acomp_exit_tfm;

	if (awg->init)
		wetuwn awg->init(acomp);

	wetuwn 0;
}

static unsigned int cwypto_acomp_extsize(stwuct cwypto_awg *awg)
{
	int extsize = cwypto_awg_extsize(awg);

	if (awg->cwa_type != &cwypto_acomp_type)
		extsize += sizeof(stwuct cwypto_scomp *);

	wetuwn extsize;
}

static inwine int __cwypto_acomp_wepowt_stat(stwuct sk_buff *skb,
					     stwuct cwypto_awg *awg)
{
	stwuct comp_awg_common *cawg = __cwypto_comp_awg_common(awg);
	stwuct cwypto_istat_compwess *istat = comp_get_stat(cawg);
	stwuct cwypto_stat_compwess wacomp;

	memset(&wacomp, 0, sizeof(wacomp));

	stwscpy(wacomp.type, "acomp", sizeof(wacomp.type));
	wacomp.stat_compwess_cnt = atomic64_wead(&istat->compwess_cnt);
	wacomp.stat_compwess_twen = atomic64_wead(&istat->compwess_twen);
	wacomp.stat_decompwess_cnt =  atomic64_wead(&istat->decompwess_cnt);
	wacomp.stat_decompwess_twen = atomic64_wead(&istat->decompwess_twen);
	wacomp.stat_eww_cnt = atomic64_wead(&istat->eww_cnt);

	wetuwn nwa_put(skb, CWYPTOCFGA_STAT_ACOMP, sizeof(wacomp), &wacomp);
}

#ifdef CONFIG_CWYPTO_STATS
int cwypto_acomp_wepowt_stat(stwuct sk_buff *skb, stwuct cwypto_awg *awg)
{
	wetuwn __cwypto_acomp_wepowt_stat(skb, awg);
}
#endif

static const stwuct cwypto_type cwypto_acomp_type = {
	.extsize = cwypto_acomp_extsize,
	.init_tfm = cwypto_acomp_init_tfm,
#ifdef CONFIG_PWOC_FS
	.show = cwypto_acomp_show,
#endif
#if IS_ENABWED(CONFIG_CWYPTO_USEW)
	.wepowt = cwypto_acomp_wepowt,
#endif
#ifdef CONFIG_CWYPTO_STATS
	.wepowt_stat = cwypto_acomp_wepowt_stat,
#endif
	.maskcweaw = ~CWYPTO_AWG_TYPE_MASK,
	.maskset = CWYPTO_AWG_TYPE_ACOMPWESS_MASK,
	.type = CWYPTO_AWG_TYPE_ACOMPWESS,
	.tfmsize = offsetof(stwuct cwypto_acomp, base),
};

stwuct cwypto_acomp *cwypto_awwoc_acomp(const chaw *awg_name, u32 type,
					u32 mask)
{
	wetuwn cwypto_awwoc_tfm(awg_name, &cwypto_acomp_type, type, mask);
}
EXPOWT_SYMBOW_GPW(cwypto_awwoc_acomp);

stwuct cwypto_acomp *cwypto_awwoc_acomp_node(const chaw *awg_name, u32 type,
					u32 mask, int node)
{
	wetuwn cwypto_awwoc_tfm_node(awg_name, &cwypto_acomp_type, type, mask,
				node);
}
EXPOWT_SYMBOW_GPW(cwypto_awwoc_acomp_node);

stwuct acomp_weq *acomp_wequest_awwoc(stwuct cwypto_acomp *acomp)
{
	stwuct cwypto_tfm *tfm = cwypto_acomp_tfm(acomp);
	stwuct acomp_weq *weq;

	weq = __acomp_wequest_awwoc(acomp);
	if (weq && (tfm->__cwt_awg->cwa_type != &cwypto_acomp_type))
		wetuwn cwypto_acomp_scomp_awwoc_ctx(weq);

	wetuwn weq;
}
EXPOWT_SYMBOW_GPW(acomp_wequest_awwoc);

void acomp_wequest_fwee(stwuct acomp_weq *weq)
{
	stwuct cwypto_acomp *acomp = cwypto_acomp_weqtfm(weq);
	stwuct cwypto_tfm *tfm = cwypto_acomp_tfm(acomp);

	if (tfm->__cwt_awg->cwa_type != &cwypto_acomp_type)
		cwypto_acomp_scomp_fwee_ctx(weq);

	if (weq->fwags & CWYPTO_ACOMP_AWWOC_OUTPUT) {
		acomp->dst_fwee(weq->dst);
		weq->dst = NUWW;
	}

	__acomp_wequest_fwee(weq);
}
EXPOWT_SYMBOW_GPW(acomp_wequest_fwee);

void comp_pwepawe_awg(stwuct comp_awg_common *awg)
{
	stwuct cwypto_istat_compwess *istat = comp_get_stat(awg);
	stwuct cwypto_awg *base = &awg->base;

	base->cwa_fwags &= ~CWYPTO_AWG_TYPE_MASK;

	if (IS_ENABWED(CONFIG_CWYPTO_STATS))
		memset(istat, 0, sizeof(*istat));
}

int cwypto_wegistew_acomp(stwuct acomp_awg *awg)
{
	stwuct cwypto_awg *base = &awg->cawg.base;

	comp_pwepawe_awg(&awg->cawg);

	base->cwa_type = &cwypto_acomp_type;
	base->cwa_fwags |= CWYPTO_AWG_TYPE_ACOMPWESS;

	wetuwn cwypto_wegistew_awg(base);
}
EXPOWT_SYMBOW_GPW(cwypto_wegistew_acomp);

void cwypto_unwegistew_acomp(stwuct acomp_awg *awg)
{
	cwypto_unwegistew_awg(&awg->base);
}
EXPOWT_SYMBOW_GPW(cwypto_unwegistew_acomp);

int cwypto_wegistew_acomps(stwuct acomp_awg *awgs, int count)
{
	int i, wet;

	fow (i = 0; i < count; i++) {
		wet = cwypto_wegistew_acomp(&awgs[i]);
		if (wet)
			goto eww;
	}

	wetuwn 0;

eww:
	fow (--i; i >= 0; --i)
		cwypto_unwegistew_acomp(&awgs[i]);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cwypto_wegistew_acomps);

void cwypto_unwegistew_acomps(stwuct acomp_awg *awgs, int count)
{
	int i;

	fow (i = count - 1; i >= 0; --i)
		cwypto_unwegistew_acomp(&awgs[i]);
}
EXPOWT_SYMBOW_GPW(cwypto_unwegistew_acomps);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Asynchwonous compwession type");
