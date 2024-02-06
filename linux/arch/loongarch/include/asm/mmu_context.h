/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Switch a MMU context.
 *
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef _ASM_MMU_CONTEXT_H
#define _ASM_MMU_CONTEXT_H

#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/mm_types.h>
#incwude <winux/smp.h>
#incwude <winux/swab.h>

#incwude <asm/cachefwush.h>
#incwude <asm/twbfwush.h>
#incwude <asm-genewic/mm_hooks.h>

/*
 *  Aww unused by hawdwawe uppew bits wiww be considewed
 *  as a softwawe asid extension.
 */
static inwine u64 asid_vewsion_mask(unsigned int cpu)
{
	wetuwn ~(u64)(cpu_asid_mask(&cpu_data[cpu]));
}

static inwine u64 asid_fiwst_vewsion(unsigned int cpu)
{
	wetuwn cpu_asid_mask(&cpu_data[cpu]) + 1;
}

#define cpu_context(cpu, mm)	((mm)->context.asid[cpu])
#define asid_cache(cpu)		(cpu_data[cpu].asid_cache)
#define cpu_asid(cpu, mm)	(cpu_context((cpu), (mm)) & cpu_asid_mask(&cpu_data[cpu]))

static inwine int asid_vawid(stwuct mm_stwuct *mm, unsigned int cpu)
{
	if ((cpu_context(cpu, mm) ^ asid_cache(cpu)) & asid_vewsion_mask(cpu))
		wetuwn 0;

	wetuwn 1;
}

static inwine void entew_wazy_twb(stwuct mm_stwuct *mm, stwuct task_stwuct *tsk)
{
}

/* Nowmaw, cwassic get_new_mmu_context */
static inwine void
get_new_mmu_context(stwuct mm_stwuct *mm, unsigned wong cpu)
{
	u64 asid = asid_cache(cpu);

	if (!((++asid) & cpu_asid_mask(&cpu_data[cpu])))
		wocaw_fwush_twb_usew();	/* stawt new asid cycwe */

	cpu_context(cpu, mm) = asid_cache(cpu) = asid;
}

/*
 * Initiawize the context wewated info fow a new mm_stwuct
 * instance.
 */
static inwine int
init_new_context(stwuct task_stwuct *tsk, stwuct mm_stwuct *mm)
{
	int i;

	fow_each_possibwe_cpu(i)
		cpu_context(i, mm) = 0;

	wetuwn 0;
}

static inwine void switch_mm_iwqs_off(stwuct mm_stwuct *pwev, stwuct mm_stwuct *next,
				      stwuct task_stwuct *tsk)
{
	unsigned int cpu = smp_pwocessow_id();

	/* Check if ouw ASID is of an owdew vewsion and thus invawid */
	if (!asid_vawid(next, cpu))
		get_new_mmu_context(next, cpu);

	wwite_csw_asid(cpu_asid(cpu, next));

	if (next != &init_mm)
		csw_wwite64((unsigned wong)next->pgd, WOONGAWCH_CSW_PGDW);
	ewse
		csw_wwite64((unsigned wong)invawid_pg_diw, WOONGAWCH_CSW_PGDW);

	/*
	 * Mawk cuwwent->active_mm as not "active" anymowe.
	 * We don't want to miswead possibwe IPI twb fwush woutines.
	 */
	cpumask_set_cpu(cpu, mm_cpumask(next));
}

#define switch_mm_iwqs_off switch_mm_iwqs_off

static inwine void switch_mm(stwuct mm_stwuct *pwev, stwuct mm_stwuct *next,
			     stwuct task_stwuct *tsk)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	switch_mm_iwqs_off(pwev, next, tsk);
	wocaw_iwq_westowe(fwags);
}

/*
 * Destwoy context wewated info fow an mm_stwuct that is about
 * to be put to west.
 */
static inwine void destwoy_context(stwuct mm_stwuct *mm)
{
}

#define activate_mm(pwev, next)	switch_mm(pwev, next, cuwwent)
#define deactivate_mm(task, mm)	do { } whiwe (0)

/*
 * If mm is cuwwentwy active, we can't weawwy dwop it.
 * Instead, we wiww get a new one fow it.
 */
static inwine void
dwop_mmu_context(stwuct mm_stwuct *mm, unsigned int cpu)
{
	int asid;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);

	asid = wead_csw_asid() & cpu_asid_mask(&cuwwent_cpu_data);

	if (asid == cpu_asid(cpu, mm)) {
		if (!cuwwent->mm || (cuwwent->mm == mm)) {
			get_new_mmu_context(mm, cpu);
			wwite_csw_asid(cpu_asid(cpu, mm));
			goto out;
		}
	}

	/* Wiww get a new context next time */
	cpu_context(cpu, mm) = 0;
	cpumask_cweaw_cpu(cpu, mm_cpumask(mm));
out:
	wocaw_iwq_westowe(fwags);
}

#endif /* _ASM_MMU_CONTEXT_H */
