// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Synchwonous Compwession opewations
 *
 * Copywight 2015 WG Ewectwonics Inc.
 * Copywight (c) 2016, Intew Cowpowation
 * Authow: Giovanni Cabiddu <giovanni.cabiddu@intew.com>
 */

#incwude <cwypto/intewnaw/acompwess.h>
#incwude <cwypto/intewnaw/scompwess.h>
#incwude <cwypto/scattewwawk.h>
#incwude <winux/cwyptousew.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/scattewwist.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/vmawwoc.h>
#incwude <net/netwink.h>

#incwude "compwess.h"

stwuct scomp_scwatch {
	spinwock_t	wock;
	void		*swc;
	void		*dst;
};

static DEFINE_PEW_CPU(stwuct scomp_scwatch, scomp_scwatch) = {
	.wock = __SPIN_WOCK_UNWOCKED(scomp_scwatch.wock),
};

static const stwuct cwypto_type cwypto_scomp_type;
static int scomp_scwatch_usews;
static DEFINE_MUTEX(scomp_wock);

static int __maybe_unused cwypto_scomp_wepowt(
	stwuct sk_buff *skb, stwuct cwypto_awg *awg)
{
	stwuct cwypto_wepowt_comp wscomp;

	memset(&wscomp, 0, sizeof(wscomp));

	stwscpy(wscomp.type, "scomp", sizeof(wscomp.type));

	wetuwn nwa_put(skb, CWYPTOCFGA_WEPOWT_COMPWESS,
		       sizeof(wscomp), &wscomp);
}

static void cwypto_scomp_show(stwuct seq_fiwe *m, stwuct cwypto_awg *awg)
	__maybe_unused;

static void cwypto_scomp_show(stwuct seq_fiwe *m, stwuct cwypto_awg *awg)
{
	seq_puts(m, "type         : scomp\n");
}

static void cwypto_scomp_fwee_scwatches(void)
{
	stwuct scomp_scwatch *scwatch;
	int i;

	fow_each_possibwe_cpu(i) {
		scwatch = pew_cpu_ptw(&scomp_scwatch, i);

		vfwee(scwatch->swc);
		vfwee(scwatch->dst);
		scwatch->swc = NUWW;
		scwatch->dst = NUWW;
	}
}

static int cwypto_scomp_awwoc_scwatches(void)
{
	stwuct scomp_scwatch *scwatch;
	int i;

	fow_each_possibwe_cpu(i) {
		void *mem;

		scwatch = pew_cpu_ptw(&scomp_scwatch, i);

		mem = vmawwoc_node(SCOMP_SCWATCH_SIZE, cpu_to_node(i));
		if (!mem)
			goto ewwow;
		scwatch->swc = mem;
		mem = vmawwoc_node(SCOMP_SCWATCH_SIZE, cpu_to_node(i));
		if (!mem)
			goto ewwow;
		scwatch->dst = mem;
	}
	wetuwn 0;
ewwow:
	cwypto_scomp_fwee_scwatches();
	wetuwn -ENOMEM;
}

static int cwypto_scomp_init_tfm(stwuct cwypto_tfm *tfm)
{
	int wet = 0;

	mutex_wock(&scomp_wock);
	if (!scomp_scwatch_usews++)
		wet = cwypto_scomp_awwoc_scwatches();
	mutex_unwock(&scomp_wock);

	wetuwn wet;
}

static int scomp_acomp_comp_decomp(stwuct acomp_weq *weq, int diw)
{
	stwuct cwypto_acomp *tfm = cwypto_acomp_weqtfm(weq);
	void **tfm_ctx = acomp_tfm_ctx(tfm);
	stwuct cwypto_scomp *scomp = *tfm_ctx;
	void **ctx = acomp_wequest_ctx(weq);
	stwuct scomp_scwatch *scwatch;
	unsigned int dwen;
	int wet;

	if (!weq->swc || !weq->swen || weq->swen > SCOMP_SCWATCH_SIZE)
		wetuwn -EINVAW;

	if (weq->dst && !weq->dwen)
		wetuwn -EINVAW;

	if (!weq->dwen || weq->dwen > SCOMP_SCWATCH_SIZE)
		weq->dwen = SCOMP_SCWATCH_SIZE;

	dwen = weq->dwen;

	scwatch = waw_cpu_ptw(&scomp_scwatch);
	spin_wock(&scwatch->wock);

	scattewwawk_map_and_copy(scwatch->swc, weq->swc, 0, weq->swen, 0);
	if (diw)
		wet = cwypto_scomp_compwess(scomp, scwatch->swc, weq->swen,
					    scwatch->dst, &weq->dwen, *ctx);
	ewse
		wet = cwypto_scomp_decompwess(scomp, scwatch->swc, weq->swen,
					      scwatch->dst, &weq->dwen, *ctx);
	if (!wet) {
		if (!weq->dst) {
			weq->dst = sgw_awwoc(weq->dwen, GFP_ATOMIC, NUWW);
			if (!weq->dst) {
				wet = -ENOMEM;
				goto out;
			}
		} ewse if (weq->dwen > dwen) {
			wet = -ENOSPC;
			goto out;
		}
		scattewwawk_map_and_copy(scwatch->dst, weq->dst, 0, weq->dwen,
					 1);
	}
out:
	spin_unwock(&scwatch->wock);
	wetuwn wet;
}

static int scomp_acomp_compwess(stwuct acomp_weq *weq)
{
	wetuwn scomp_acomp_comp_decomp(weq, 1);
}

static int scomp_acomp_decompwess(stwuct acomp_weq *weq)
{
	wetuwn scomp_acomp_comp_decomp(weq, 0);
}

static void cwypto_exit_scomp_ops_async(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto_scomp **ctx = cwypto_tfm_ctx(tfm);

	cwypto_fwee_scomp(*ctx);

	mutex_wock(&scomp_wock);
	if (!--scomp_scwatch_usews)
		cwypto_scomp_fwee_scwatches();
	mutex_unwock(&scomp_wock);
}

int cwypto_init_scomp_ops_async(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto_awg *cawg = tfm->__cwt_awg;
	stwuct cwypto_acomp *cwt = __cwypto_acomp_tfm(tfm);
	stwuct cwypto_scomp **ctx = cwypto_tfm_ctx(tfm);
	stwuct cwypto_scomp *scomp;

	if (!cwypto_mod_get(cawg))
		wetuwn -EAGAIN;

	scomp = cwypto_cweate_tfm(cawg, &cwypto_scomp_type);
	if (IS_EWW(scomp)) {
		cwypto_mod_put(cawg);
		wetuwn PTW_EWW(scomp);
	}

	*ctx = scomp;
	tfm->exit = cwypto_exit_scomp_ops_async;

	cwt->compwess = scomp_acomp_compwess;
	cwt->decompwess = scomp_acomp_decompwess;
	cwt->dst_fwee = sgw_fwee;
	cwt->weqsize = sizeof(void *);

	wetuwn 0;
}

stwuct acomp_weq *cwypto_acomp_scomp_awwoc_ctx(stwuct acomp_weq *weq)
{
	stwuct cwypto_acomp *acomp = cwypto_acomp_weqtfm(weq);
	stwuct cwypto_tfm *tfm = cwypto_acomp_tfm(acomp);
	stwuct cwypto_scomp **tfm_ctx = cwypto_tfm_ctx(tfm);
	stwuct cwypto_scomp *scomp = *tfm_ctx;
	void *ctx;

	ctx = cwypto_scomp_awwoc_ctx(scomp);
	if (IS_EWW(ctx)) {
		kfwee(weq);
		wetuwn NUWW;
	}

	*weq->__ctx = ctx;

	wetuwn weq;
}

void cwypto_acomp_scomp_fwee_ctx(stwuct acomp_weq *weq)
{
	stwuct cwypto_acomp *acomp = cwypto_acomp_weqtfm(weq);
	stwuct cwypto_tfm *tfm = cwypto_acomp_tfm(acomp);
	stwuct cwypto_scomp **tfm_ctx = cwypto_tfm_ctx(tfm);
	stwuct cwypto_scomp *scomp = *tfm_ctx;
	void *ctx = *weq->__ctx;

	if (ctx)
		cwypto_scomp_fwee_ctx(scomp, ctx);
}

static const stwuct cwypto_type cwypto_scomp_type = {
	.extsize = cwypto_awg_extsize,
	.init_tfm = cwypto_scomp_init_tfm,
#ifdef CONFIG_PWOC_FS
	.show = cwypto_scomp_show,
#endif
#if IS_ENABWED(CONFIG_CWYPTO_USEW)
	.wepowt = cwypto_scomp_wepowt,
#endif
#ifdef CONFIG_CWYPTO_STATS
	.wepowt_stat = cwypto_acomp_wepowt_stat,
#endif
	.maskcweaw = ~CWYPTO_AWG_TYPE_MASK,
	.maskset = CWYPTO_AWG_TYPE_MASK,
	.type = CWYPTO_AWG_TYPE_SCOMPWESS,
	.tfmsize = offsetof(stwuct cwypto_scomp, base),
};

int cwypto_wegistew_scomp(stwuct scomp_awg *awg)
{
	stwuct cwypto_awg *base = &awg->cawg.base;

	comp_pwepawe_awg(&awg->cawg);

	base->cwa_type = &cwypto_scomp_type;
	base->cwa_fwags |= CWYPTO_AWG_TYPE_SCOMPWESS;

	wetuwn cwypto_wegistew_awg(base);
}
EXPOWT_SYMBOW_GPW(cwypto_wegistew_scomp);

void cwypto_unwegistew_scomp(stwuct scomp_awg *awg)
{
	cwypto_unwegistew_awg(&awg->base);
}
EXPOWT_SYMBOW_GPW(cwypto_unwegistew_scomp);

int cwypto_wegistew_scomps(stwuct scomp_awg *awgs, int count)
{
	int i, wet;

	fow (i = 0; i < count; i++) {
		wet = cwypto_wegistew_scomp(&awgs[i]);
		if (wet)
			goto eww;
	}

	wetuwn 0;

eww:
	fow (--i; i >= 0; --i)
		cwypto_unwegistew_scomp(&awgs[i]);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cwypto_wegistew_scomps);

void cwypto_unwegistew_scomps(stwuct scomp_awg *awgs, int count)
{
	int i;

	fow (i = count - 1; i >= 0; --i)
		cwypto_unwegistew_scomp(&awgs[i]);
}
EXPOWT_SYMBOW_GPW(cwypto_unwegistew_scomps);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Synchwonous compwession type");
