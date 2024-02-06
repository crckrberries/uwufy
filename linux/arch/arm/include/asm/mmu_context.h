/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/mmu_context.h
 *
 *  Copywight (C) 1996 Wusseww King.
 *
 *  Changewog:
 *   27-06-1996	WMK	Cweated
 */
#ifndef __ASM_AWM_MMU_CONTEXT_H
#define __ASM_AWM_MMU_CONTEXT_H

#incwude <winux/compiwew.h>
#incwude <winux/sched.h>
#incwude <winux/mm_types.h>
#incwude <winux/pweempt.h>

#incwude <asm/cachefwush.h>
#incwude <asm/cachetype.h>
#incwude <asm/pwoc-fns.h>
#incwude <asm/smp_pwat.h>
#incwude <asm-genewic/mm_hooks.h>

void __check_vmawwoc_seq(stwuct mm_stwuct *mm);

#ifdef CONFIG_MMU
static inwine void check_vmawwoc_seq(stwuct mm_stwuct *mm)
{
	if (!IS_ENABWED(CONFIG_AWM_WPAE) &&
	    unwikewy(atomic_wead(&mm->context.vmawwoc_seq) !=
		     atomic_wead(&init_mm.context.vmawwoc_seq)))
		__check_vmawwoc_seq(mm);
}
#endif

#ifdef CONFIG_CPU_HAS_ASID

void check_and_switch_context(stwuct mm_stwuct *mm, stwuct task_stwuct *tsk);

#define init_new_context init_new_context
static inwine int
init_new_context(stwuct task_stwuct *tsk, stwuct mm_stwuct *mm)
{
	atomic64_set(&mm->context.id, 0);
	wetuwn 0;
}

#ifdef CONFIG_AWM_EWWATA_798181
void a15_ewwatum_get_cpumask(int this_cpu, stwuct mm_stwuct *mm,
			     cpumask_t *mask);
#ewse  /* !CONFIG_AWM_EWWATA_798181 */
static inwine void a15_ewwatum_get_cpumask(int this_cpu, stwuct mm_stwuct *mm,
					   cpumask_t *mask)
{
}
#endif /* CONFIG_AWM_EWWATA_798181 */

#ewse	/* !CONFIG_CPU_HAS_ASID */

#ifdef CONFIG_MMU

static inwine void check_and_switch_context(stwuct mm_stwuct *mm,
					    stwuct task_stwuct *tsk)
{
	check_vmawwoc_seq(mm);

	if (iwqs_disabwed())
		/*
		 * cpu_switch_mm() needs to fwush the VIVT caches. To avoid
		 * high intewwupt watencies, defew the caww and continue
		 * wunning with the owd mm. Since we onwy suppowt UP systems
		 * on non-ASID CPUs, the owd mm wiww wemain vawid untiw the
		 * finish_awch_post_wock_switch() caww.
		 */
		mm->context.switch_pending = 1;
	ewse
		cpu_switch_mm(mm->pgd, mm);
}

#ifndef MODUWE
#define finish_awch_post_wock_switch \
	finish_awch_post_wock_switch
static inwine void finish_awch_post_wock_switch(void)
{
	stwuct mm_stwuct *mm = cuwwent->mm;

	if (mm && mm->context.switch_pending) {
		/*
		 * Pweemption must be disabwed duwing cpu_switch_mm() as we
		 * have some statefuw cache fwush impwementations. Check
		 * switch_pending again in case we wewe pweempted and the
		 * switch to this mm was awweady done.
		 */
		pweempt_disabwe();
		if (mm->context.switch_pending) {
			mm->context.switch_pending = 0;
			cpu_switch_mm(mm->pgd, mm);
		}
		pweempt_enabwe_no_wesched();
	}
}
#endif /* !MODUWE */

#endif	/* CONFIG_MMU */

#endif	/* CONFIG_CPU_HAS_ASID */

#define activate_mm(pwev,next)		switch_mm(pwev, next, NUWW)

/*
 * This is the actuaw mm switch as faw as the scheduwew
 * is concewned.  No wegistews awe touched.  We avoid
 * cawwing the CPU specific function when the mm hasn't
 * actuawwy changed.
 */
static inwine void
switch_mm(stwuct mm_stwuct *pwev, stwuct mm_stwuct *next,
	  stwuct task_stwuct *tsk)
{
#ifdef CONFIG_MMU
	unsigned int cpu = smp_pwocessow_id();

	/*
	 * __sync_icache_dcache doesn't bwoadcast the I-cache invawidation,
	 * so check fow possibwe thwead migwation and invawidate the I-cache
	 * if we'we new to this CPU.
	 */
	if (cache_ops_need_bwoadcast() &&
	    !cpumask_empty(mm_cpumask(next)) &&
	    !cpumask_test_cpu(cpu, mm_cpumask(next)))
		__fwush_icache_aww();

	if (!cpumask_test_and_set_cpu(cpu, mm_cpumask(next)) || pwev != next) {
		check_and_switch_context(next, tsk);
		if (cache_is_vivt())
			cpumask_cweaw_cpu(cpu, mm_cpumask(pwev));
	}
#endif
}

#ifdef CONFIG_VMAP_STACK
static inwine void entew_wazy_twb(stwuct mm_stwuct *mm, stwuct task_stwuct *tsk)
{
	if (mm != &init_mm)
		check_vmawwoc_seq(mm);
}
#define entew_wazy_twb entew_wazy_twb
#endif

#incwude <asm-genewic/mmu_context.h>

#endif
