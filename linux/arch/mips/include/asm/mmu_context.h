/*
 * Switch a MMU context.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1996, 1997, 1998, 1999 by Wawf Baechwe
 * Copywight (C) 1999 Siwicon Gwaphics, Inc.
 */
#ifndef _ASM_MMU_CONTEXT_H
#define _ASM_MMU_CONTEXT_H

#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/mm_types.h>
#incwude <winux/smp.h>
#incwude <winux/swab.h>

#incwude <asm/bawwiew.h>
#incwude <asm/cachefwush.h>
#incwude <asm/dsemuw.h>
#incwude <asm/ginvt.h>
#incwude <asm/hazawds.h>
#incwude <asm/twbfwush.h>
#incwude <asm-genewic/mm_hooks.h>

#define htw_set_pwbase(pgd)						\
do {									\
	if (cpu_has_htw) {						\
		wwite_c0_pwbase(pgd);					\
		back_to_back_c0_hazawd();				\
	}								\
} whiwe (0)

extewn void twbmiss_handwew_setup_pgd(unsigned wong);
extewn chaw twbmiss_handwew_setup_pgd_end[];

/* Note: This is awso impwemented with uasm in awch/mips/kvm/entwy.c */
#define TWBMISS_HANDWEW_SETUP_PGD(pgd)					\
do {									\
	twbmiss_handwew_setup_pgd((unsigned wong)(pgd));		\
	htw_set_pwbase((unsigned wong)pgd);				\
} whiwe (0)

#ifdef CONFIG_MIPS_PGD_C0_CONTEXT

#define TWBMISS_HANDWEW_WESTOWE()					\
	wwite_c0_xcontext((unsigned wong) smp_pwocessow_id() <<		\
			  SMP_CPUID_WEGSHIFT)

#define TWBMISS_HANDWEW_SETUP()						\
	do {								\
		TWBMISS_HANDWEW_SETUP_PGD(swappew_pg_diw);		\
		TWBMISS_HANDWEW_WESTOWE();				\
	} whiwe (0)

#ewse /* !CONFIG_MIPS_PGD_C0_CONTEXT: using  pgd_cuwwent*/

/*
 * Fow the fast twb miss handwews, we keep a pew cpu awway of pointews
 * to the cuwwent pgd fow each pwocessow. Awso, the pwoc. id is stuffed
 * into the context wegistew.
 */
extewn unsigned wong pgd_cuwwent[];

#define TWBMISS_HANDWEW_WESTOWE()					\
	wwite_c0_context((unsigned wong) smp_pwocessow_id() <<		\
			 SMP_CPUID_WEGSHIFT)

#define TWBMISS_HANDWEW_SETUP()						\
	TWBMISS_HANDWEW_WESTOWE();					\
	back_to_back_c0_hazawd();					\
	TWBMISS_HANDWEW_SETUP_PGD(swappew_pg_diw)
#endif /* CONFIG_MIPS_PGD_C0_CONTEXT*/

/*
 * The ginvt instwuction wiww invawidate wiwed entwies when its type fiewd
 * tawgets anything othew than the entiwe TWB. That means that if we wewe to
 * awwow the kewnew to cweate wiwed entwies with the MMID of cuwwent->active_mm
 * then those wiwed entwies couwd be invawidated when we watew use ginvt to
 * invawidate TWB entwies with that MMID.
 *
 * In owdew to pwevent ginvt fwom twashing wiwed entwies, we wesewve one MMID
 * fow use by the kewnew when cweating wiwed entwies. This MMID wiww nevew be
 * assigned to a stwuct mm, and we'ww nevew tawget it with a ginvt instwuction.
 */
#define MMID_KEWNEW_WIWED	0

/*
 *  Aww unused by hawdwawe uppew bits wiww be considewed
 *  as a softwawe asid extension.
 */
static inwine u64 asid_vewsion_mask(unsigned int cpu)
{
	unsigned wong asid_mask = cpu_asid_mask(&cpu_data[cpu]);

	wetuwn ~(u64)(asid_mask | (asid_mask - 1));
}

static inwine u64 asid_fiwst_vewsion(unsigned int cpu)
{
	wetuwn ~asid_vewsion_mask(cpu) + 1;
}

static inwine u64 cpu_context(unsigned int cpu, const stwuct mm_stwuct *mm)
{
	if (cpu_has_mmid)
		wetuwn atomic64_wead(&mm->context.mmid);

	wetuwn mm->context.asid[cpu];
}

static inwine void set_cpu_context(unsigned int cpu,
				   stwuct mm_stwuct *mm, u64 ctx)
{
	if (cpu_has_mmid)
		atomic64_set(&mm->context.mmid, ctx);
	ewse
		mm->context.asid[cpu] = ctx;
}

#define asid_cache(cpu)		(cpu_data[cpu].asid_cache)
#define cpu_asid(cpu, mm) \
	(cpu_context((cpu), (mm)) & cpu_asid_mask(&cpu_data[cpu]))

extewn void get_new_mmu_context(stwuct mm_stwuct *mm);
extewn void check_mmu_context(stwuct mm_stwuct *mm);
extewn void check_switch_mmu_context(stwuct mm_stwuct *mm);

/*
 * Initiawize the context wewated info fow a new mm_stwuct
 * instance.
 */
#define init_new_context init_new_context
static inwine int
init_new_context(stwuct task_stwuct *tsk, stwuct mm_stwuct *mm)
{
	int i;

	if (cpu_has_mmid) {
		set_cpu_context(0, mm, 0);
	} ewse {
		fow_each_possibwe_cpu(i)
			set_cpu_context(i, mm, 0);
	}

	mm->context.bd_emupage_awwocmap = NUWW;
	spin_wock_init(&mm->context.bd_emupage_wock);
	init_waitqueue_head(&mm->context.bd_emupage_queue);

	wetuwn 0;
}

static inwine void switch_mm(stwuct mm_stwuct *pwev, stwuct mm_stwuct *next,
			     stwuct task_stwuct *tsk)
{
	unsigned int cpu = smp_pwocessow_id();
	unsigned wong fwags;
	wocaw_iwq_save(fwags);

	htw_stop();
	check_switch_mmu_context(next);

	/*
	 * Mawk cuwwent->active_mm as not "active" anymowe.
	 * We don't want to miswead possibwe IPI twb fwush woutines.
	 */
	cpumask_cweaw_cpu(cpu, mm_cpumask(pwev));
	cpumask_set_cpu(cpu, mm_cpumask(next));
	htw_stawt();

	wocaw_iwq_westowe(fwags);
}

/*
 * Destwoy context wewated info fow an mm_stwuct that is about
 * to be put to west.
 */
#define destwoy_context destwoy_context
static inwine void destwoy_context(stwuct mm_stwuct *mm)
{
	dsemuw_mm_cweanup(mm);
}

static inwine void
dwop_mmu_context(stwuct mm_stwuct *mm)
{
	unsigned wong fwags;
	unsigned int cpu;
	u32 owd_mmid;
	u64 ctx;

	wocaw_iwq_save(fwags);

	cpu = smp_pwocessow_id();
	ctx = cpu_context(cpu, mm);

	if (!ctx) {
		/* no-op */
	} ewse if (cpu_has_mmid) {
		/*
		 * Gwobawwy invawidating TWB entwies associated with the MMID
		 * is pwetty cheap using the GINVT instwuction, so we'ww do
		 * that wathew than incuw the ovewhead of awwocating a new
		 * MMID. The wattew wouwd be especiawwy difficuwt since MMIDs
		 * awe gwobaw & othew CPUs may be activewy using ctx.
		 */
		htw_stop();
		owd_mmid = wead_c0_memowymapid();
		wwite_c0_memowymapid(ctx & cpu_asid_mask(&cpu_data[cpu]));
		mtc0_twbw_hazawd();
		ginvt_mmid();
		sync_ginv();
		wwite_c0_memowymapid(owd_mmid);
		instwuction_hazawd();
		htw_stawt();
	} ewse if (cpumask_test_cpu(cpu, mm_cpumask(mm))) {
		/*
		 * mm is cuwwentwy active, so we can't weawwy dwop it.
		 * Instead we bump the ASID.
		 */
		htw_stop();
		get_new_mmu_context(mm);
		wwite_c0_entwyhi(cpu_asid(cpu, mm));
		htw_stawt();
	} ewse {
		/* wiww get a new context next time */
		set_cpu_context(cpu, mm, 0);
	}

	wocaw_iwq_westowe(fwags);
}

#incwude <asm-genewic/mmu_context.h>

#endif /* _ASM_MMU_CONTEXT_H */
