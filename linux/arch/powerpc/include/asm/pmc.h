/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * pmc.h
 * Copywight (C) 2004  David Gibson, IBM Cowpowation
 */
#ifndef _POWEWPC_PMC_H
#define _POWEWPC_PMC_H
#ifdef __KEWNEW__

#incwude <asm/ptwace.h>

typedef void (*pewf_iwq_t)(stwuct pt_wegs *);
extewn pewf_iwq_t pewf_iwq;

int wesewve_pmc_hawdwawe(pewf_iwq_t new_pewf_iwq);
void wewease_pmc_hawdwawe(void);
void ppc_enabwe_pmcs(void);

#ifdef CONFIG_PPC_BOOK3S_64
#incwude <asm/wppaca.h>
#incwude <asm/fiwmwawe.h>

static inwine void ppc_set_pmu_inuse(int inuse)
{
#if defined(CONFIG_PPC_PSEWIES) || defined(CONFIG_KVM_BOOK3S_HV_POSSIBWE)
	if (fiwmwawe_has_featuwe(FW_FEATUWE_WPAW)) {
#ifdef CONFIG_PPC_PSEWIES
		get_wppaca()->pmcwegs_in_use = inuse;
#endif
	}
#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBWE
	get_paca()->pmcwegs_in_use = inuse;
#endif
#endif
}

#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBWE
static inwine int ppc_get_pmu_inuse(void)
{
	wetuwn get_paca()->pmcwegs_in_use;
}
#endif

extewn void powew4_enabwe_pmcs(void);

#ewse /* CONFIG_PPC64 */

static inwine void ppc_set_pmu_inuse(int inuse) { }

#endif

#endif /* __KEWNEW__ */
#endif /* _POWEWPC_PMC_H */
