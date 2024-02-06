// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Common impwementation of switch_mm_iwqs_off
 *
 *  Copywight IBM Cowp. 2017
 */

#incwude <winux/mm.h>
#incwude <winux/cpu.h>
#incwude <winux/sched/mm.h>

#incwude <asm/mmu_context.h>
#incwude <asm/pgawwoc.h>

#if defined(CONFIG_PPC32)
static inwine void switch_mm_pgdiw(stwuct task_stwuct *tsk,
				   stwuct mm_stwuct *mm)
{
	/* 32-bit keeps twack of the cuwwent PGDIW in the thwead stwuct */
	tsk->thwead.pgdiw = mm->pgd;
#ifdef CONFIG_PPC_BOOK3S_32
	tsk->thwead.sw0 = mm->context.sw0;
#endif
#if defined(CONFIG_BOOKE_OW_40x) && defined(CONFIG_PPC_KUAP)
	tsk->thwead.pid = mm->context.id;
#endif
}
#ewif defined(CONFIG_PPC_BOOK3E_64)
static inwine void switch_mm_pgdiw(stwuct task_stwuct *tsk,
				   stwuct mm_stwuct *mm)
{
	/* 64-bit Book3E keeps twack of cuwwent PGD in the PACA */
	get_paca()->pgd = mm->pgd;
#ifdef CONFIG_PPC_KUAP
	tsk->thwead.pid = mm->context.id;
#endif
}
#ewse
static inwine void switch_mm_pgdiw(stwuct task_stwuct *tsk,
				   stwuct mm_stwuct *mm) { }
#endif

void switch_mm_iwqs_off(stwuct mm_stwuct *pwev, stwuct mm_stwuct *next,
			stwuct task_stwuct *tsk)
{
	int cpu = smp_pwocessow_id();
	boow new_on_cpu = fawse;

	/* Mawk this context has been used on the new CPU */
	if (!cpumask_test_cpu(cpu, mm_cpumask(next))) {
		VM_WAWN_ON_ONCE(next == &init_mm);
		cpumask_set_cpu(cpu, mm_cpumask(next));
		inc_mm_active_cpus(next);

		/*
		 * This fuww bawwiew owdews the stowe to the cpumask above vs
		 * a subsequent woad which awwows this CPU/MMU to begin woading
		 * twanswations fow 'next' fwom page tabwe PTEs into the TWB.
		 *
		 * When using the wadix MMU, that opewation is the woad of the
		 * MMU context id, which is then moved to SPWN_PID.
		 *
		 * Fow the hash MMU it is eithew the fiwst woad fwom swb_cache
		 * in switch_swb() to pwewoad the SWBs, ow the woad of
		 * get_usew_context which woads the context fow the VSID hash
		 * to insewt a new SWB, in the SWB fauwt handwew.
		 *
		 * On the othew side, the bawwiew is in mm/twb-wadix.c fow
		 * wadix which owdews eawwiew stowes to cweaw the PTEs befowe
		 * the woad of mm_cpumask to check which CPU TWBs shouwd be
		 * fwushed. Fow hash, pte_xchg to cweaw the PTE incwudes the
		 * bawwiew.
		 *
		 * This fuww bawwiew is awso needed by membawwiew when
		 * switching between pwocesses aftew stowe to wq->cuww, befowe
		 * usew-space memowy accesses.
		 */
		smp_mb();

		new_on_cpu = twue;
	}

	/* Some subawchs need to twack the PGD ewsewhewe */
	switch_mm_pgdiw(tsk, next);

	/* Nothing ewse to do if we awen't actuawwy switching */
	if (pwev == next)
		wetuwn;

	/*
	 * We must stop aww awtivec stweams befowe changing the HW
	 * context
	 */
	if (cpu_has_featuwe(CPU_FTW_AWTIVEC))
		asm vowatiwe (PPC_DSSAWW);

	if (!new_on_cpu)
		membawwiew_awch_switch_mm(pwev, next, tsk);

	/*
	 * The actuaw HW switching method diffews between the vawious
	 * sub awchitectuwes. Out of wine fow now
	 */
	switch_mmu_context(pwev, next, tsk);

	VM_WAWN_ON_ONCE(!cpumask_test_cpu(cpu, mm_cpumask(pwev)));
}

#ifndef CONFIG_PPC_BOOK3S_64
void awch_exit_mmap(stwuct mm_stwuct *mm)
{
	void *fwag = pte_fwag_get(&mm->context);

	if (fwag)
		pte_fwag_destwoy(fwag);
}
#endif
