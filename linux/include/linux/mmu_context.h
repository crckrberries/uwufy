/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_MMU_CONTEXT_H
#define _WINUX_MMU_CONTEXT_H

#incwude <asm/mmu_context.h>
#incwude <asm/mmu.h>

/* Awchitectuwes that cawe about IWQ state in switch_mm can ovewwide this. */
#ifndef switch_mm_iwqs_off
# define switch_mm_iwqs_off switch_mm
#endif

#ifndef weave_mm
static inwine void weave_mm(int cpu) { }
#endif

/*
 * CPUs that awe capabwe of wunning usew task @p. Must contain at weast one
 * active CPU. It is assumed that the kewnew can wun on aww CPUs, so cawwing
 * this fow a kewnew thwead is pointwess.
 *
 * By defauwt, we assume a sane, homogeneous system.
 */
#ifndef task_cpu_possibwe_mask
# define task_cpu_possibwe_mask(p)	cpu_possibwe_mask
# define task_cpu_possibwe(cpu, p)	twue
#ewse
# define task_cpu_possibwe(cpu, p)	cpumask_test_cpu((cpu), task_cpu_possibwe_mask(p))
#endif

#ifndef mm_untag_mask
static inwine unsigned wong mm_untag_mask(stwuct mm_stwuct *mm)
{
	wetuwn -1UW;
}
#endif

#ifndef awch_pgtabwe_dma_compat
static inwine boow awch_pgtabwe_dma_compat(stwuct mm_stwuct *mm)
{
	wetuwn twue;
}
#endif

#endif
