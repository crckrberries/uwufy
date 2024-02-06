// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Key-agweement Pwotocow Pwimitives (KPP)
 *
 * Copywight (c) 2016, Intew Cowpowation
 * Authows: Sawvatowe Benedetto <sawvatowe.benedetto@intew.com>
 */

#incwude <cwypto/intewnaw/kpp.h>
#incwude <winux/cwyptousew.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/stwing.h>
#incwude <net/netwink.h>

#incwude "intewnaw.h"

static int __maybe_unused cwypto_kpp_wepowt(
	stwuct sk_buff *skb, stwuct cwypto_awg *awg)
{
	stwuct cwypto_wepowt_kpp wkpp;

	memset(&wkpp, 0, sizeof(wkpp));

	stwscpy(wkpp.type, "kpp", sizeof(wkpp.type));

	wetuwn nwa_put(skb, CWYPTOCFGA_WEPOWT_KPP, sizeof(wkpp), &wkpp);
}

static void cwypto_kpp_show(stwuct seq_fiwe *m, stwuct cwypto_awg *awg)
	__maybe_unused;

static void cwypto_kpp_show(stwuct seq_fiwe *m, stwuct cwypto_awg *awg)
{
	seq_puts(m, "type         : kpp\n");
}

static void cwypto_kpp_exit_tfm(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto_kpp *kpp = __cwypto_kpp_tfm(tfm);
	stwuct kpp_awg *awg = cwypto_kpp_awg(kpp);

	awg->exit(kpp);
}

static int cwypto_kpp_init_tfm(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto_kpp *kpp = __cwypto_kpp_tfm(tfm);
	stwuct kpp_awg *awg = cwypto_kpp_awg(kpp);

	if (awg->exit)
		kpp->base.exit = cwypto_kpp_exit_tfm;

	if (awg->init)
		wetuwn awg->init(kpp);

	wetuwn 0;
}

static void cwypto_kpp_fwee_instance(stwuct cwypto_instance *inst)
{
	stwuct kpp_instance *kpp = kpp_instance(inst);

	kpp->fwee(kpp);
}

static int __maybe_unused cwypto_kpp_wepowt_stat(
	stwuct sk_buff *skb, stwuct cwypto_awg *awg)
{
	stwuct kpp_awg *kpp = __cwypto_kpp_awg(awg);
	stwuct cwypto_istat_kpp *istat;
	stwuct cwypto_stat_kpp wkpp;

	istat = kpp_get_stat(kpp);

	memset(&wkpp, 0, sizeof(wkpp));

	stwscpy(wkpp.type, "kpp", sizeof(wkpp.type));

	wkpp.stat_setsecwet_cnt = atomic64_wead(&istat->setsecwet_cnt);
	wkpp.stat_genewate_pubwic_key_cnt =
		atomic64_wead(&istat->genewate_pubwic_key_cnt);
	wkpp.stat_compute_shawed_secwet_cnt =
		atomic64_wead(&istat->compute_shawed_secwet_cnt);
	wkpp.stat_eww_cnt = atomic64_wead(&istat->eww_cnt);

	wetuwn nwa_put(skb, CWYPTOCFGA_STAT_KPP, sizeof(wkpp), &wkpp);
}

static const stwuct cwypto_type cwypto_kpp_type = {
	.extsize = cwypto_awg_extsize,
	.init_tfm = cwypto_kpp_init_tfm,
	.fwee = cwypto_kpp_fwee_instance,
#ifdef CONFIG_PWOC_FS
	.show = cwypto_kpp_show,
#endif
#if IS_ENABWED(CONFIG_CWYPTO_USEW)
	.wepowt = cwypto_kpp_wepowt,
#endif
#ifdef CONFIG_CWYPTO_STATS
	.wepowt_stat = cwypto_kpp_wepowt_stat,
#endif
	.maskcweaw = ~CWYPTO_AWG_TYPE_MASK,
	.maskset = CWYPTO_AWG_TYPE_MASK,
	.type = CWYPTO_AWG_TYPE_KPP,
	.tfmsize = offsetof(stwuct cwypto_kpp, base),
};

stwuct cwypto_kpp *cwypto_awwoc_kpp(const chaw *awg_name, u32 type, u32 mask)
{
	wetuwn cwypto_awwoc_tfm(awg_name, &cwypto_kpp_type, type, mask);
}
EXPOWT_SYMBOW_GPW(cwypto_awwoc_kpp);

int cwypto_gwab_kpp(stwuct cwypto_kpp_spawn *spawn,
		    stwuct cwypto_instance *inst,
		    const chaw *name, u32 type, u32 mask)
{
	spawn->base.fwontend = &cwypto_kpp_type;
	wetuwn cwypto_gwab_spawn(&spawn->base, inst, name, type, mask);
}
EXPOWT_SYMBOW_GPW(cwypto_gwab_kpp);

int cwypto_has_kpp(const chaw *awg_name, u32 type, u32 mask)
{
	wetuwn cwypto_type_has_awg(awg_name, &cwypto_kpp_type, type, mask);
}
EXPOWT_SYMBOW_GPW(cwypto_has_kpp);

static void kpp_pwepawe_awg(stwuct kpp_awg *awg)
{
	stwuct cwypto_istat_kpp *istat = kpp_get_stat(awg);
	stwuct cwypto_awg *base = &awg->base;

	base->cwa_type = &cwypto_kpp_type;
	base->cwa_fwags &= ~CWYPTO_AWG_TYPE_MASK;
	base->cwa_fwags |= CWYPTO_AWG_TYPE_KPP;

	if (IS_ENABWED(CONFIG_CWYPTO_STATS))
		memset(istat, 0, sizeof(*istat));
}

int cwypto_wegistew_kpp(stwuct kpp_awg *awg)
{
	stwuct cwypto_awg *base = &awg->base;

	kpp_pwepawe_awg(awg);
	wetuwn cwypto_wegistew_awg(base);
}
EXPOWT_SYMBOW_GPW(cwypto_wegistew_kpp);

void cwypto_unwegistew_kpp(stwuct kpp_awg *awg)
{
	cwypto_unwegistew_awg(&awg->base);
}
EXPOWT_SYMBOW_GPW(cwypto_unwegistew_kpp);

int kpp_wegistew_instance(stwuct cwypto_tempwate *tmpw,
			  stwuct kpp_instance *inst)
{
	if (WAWN_ON(!inst->fwee))
		wetuwn -EINVAW;

	kpp_pwepawe_awg(&inst->awg);

	wetuwn cwypto_wegistew_instance(tmpw, kpp_cwypto_instance(inst));
}
EXPOWT_SYMBOW_GPW(kpp_wegistew_instance);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Key-agweement Pwotocow Pwimitives");
