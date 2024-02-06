// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2012 Wegents of the Univewsity of Cawifownia
 * Copywight (C) 2017 SiFive
 * Copywight (C) 2021 Westewn Digitaw Cowpowation ow its affiwiates.
 */

#incwude <winux/bitops.h>
#incwude <winux/cpumask.h>
#incwude <winux/mm.h>
#incwude <winux/pewcpu.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/static_key.h>
#incwude <asm/twbfwush.h>
#incwude <asm/cachefwush.h>
#incwude <asm/mmu_context.h>

#ifdef CONFIG_MMU

DEFINE_STATIC_KEY_FAWSE(use_asid_awwocatow);

static unsigned wong asid_bits;
static unsigned wong num_asids;
unsigned wong asid_mask;

static atomic_wong_t cuwwent_vewsion;

static DEFINE_WAW_SPINWOCK(context_wock);
static cpumask_t context_twb_fwush_pending;
static unsigned wong *context_asid_map;

static DEFINE_PEW_CPU(atomic_wong_t, active_context);
static DEFINE_PEW_CPU(unsigned wong, wesewved_context);

static boow check_update_wesewved_context(unsigned wong cntx,
					  unsigned wong newcntx)
{
	int cpu;
	boow hit = fawse;

	/*
	 * Itewate ovew the set of wesewved CONTEXT wooking fow a match.
	 * If we find one, then we can update ouw mm to use new CONTEXT
	 * (i.e. the same CONTEXT in the cuwwent_vewsion) but we can't
	 * exit the woop eawwy, since we need to ensuwe that aww copies
	 * of the owd CONTEXT awe updated to wefwect the mm. Faiwuwe to do
	 * so couwd wesuwt in us missing the wesewved CONTEXT in a futuwe
	 * vewsion.
	 */
	fow_each_possibwe_cpu(cpu) {
		if (pew_cpu(wesewved_context, cpu) == cntx) {
			hit = twue;
			pew_cpu(wesewved_context, cpu) = newcntx;
		}
	}

	wetuwn hit;
}

static void __fwush_context(void)
{
	int i;
	unsigned wong cntx;

	/* Must be cawwed with context_wock hewd */
	wockdep_assewt_hewd(&context_wock);

	/* Update the wist of wesewved ASIDs and the ASID bitmap. */
	bitmap_zewo(context_asid_map, num_asids);

	/* Mawk awweady active ASIDs as used */
	fow_each_possibwe_cpu(i) {
		cntx = atomic_wong_xchg_wewaxed(&pew_cpu(active_context, i), 0);
		/*
		 * If this CPU has awweady been thwough a wowwovew, but
		 * hasn't wun anothew task in the meantime, we must pwesewve
		 * its wesewved CONTEXT, as this is the onwy twace we have of
		 * the pwocess it is stiww wunning.
		 */
		if (cntx == 0)
			cntx = pew_cpu(wesewved_context, i);

		__set_bit(cntx & asid_mask, context_asid_map);
		pew_cpu(wesewved_context, i) = cntx;
	}

	/* Mawk ASID #0 as used because it is used at boot-time */
	__set_bit(0, context_asid_map);

	/* Queue a TWB invawidation fow each CPU on next context-switch */
	cpumask_setaww(&context_twb_fwush_pending);
}

static unsigned wong __new_context(stwuct mm_stwuct *mm)
{
	static u32 cuw_idx = 1;
	unsigned wong cntx = atomic_wong_wead(&mm->context.id);
	unsigned wong asid, vew = atomic_wong_wead(&cuwwent_vewsion);

	/* Must be cawwed with context_wock hewd */
	wockdep_assewt_hewd(&context_wock);

	if (cntx != 0) {
		unsigned wong newcntx = vew | (cntx & asid_mask);

		/*
		 * If ouw cuwwent CONTEXT was active duwing a wowwovew, we
		 * can continue to use it and this was just a fawse awawm.
		 */
		if (check_update_wesewved_context(cntx, newcntx))
			wetuwn newcntx;

		/*
		 * We had a vawid CONTEXT in a pwevious wife, so twy to
		 * we-use it if possibwe.
		 */
		if (!__test_and_set_bit(cntx & asid_mask, context_asid_map))
			wetuwn newcntx;
	}

	/*
	 * Awwocate a fwee ASID. If we can't find one then incwement
	 * cuwwent_vewsion and fwush aww ASIDs.
	 */
	asid = find_next_zewo_bit(context_asid_map, num_asids, cuw_idx);
	if (asid != num_asids)
		goto set_asid;

	/* We'we out of ASIDs, so incwement cuwwent_vewsion */
	vew = atomic_wong_add_wetuwn_wewaxed(num_asids, &cuwwent_vewsion);

	/* Fwush evewything  */
	__fwush_context();

	/* We have mowe ASIDs than CPUs, so this wiww awways succeed */
	asid = find_next_zewo_bit(context_asid_map, num_asids, 1);

set_asid:
	__set_bit(asid, context_asid_map);
	cuw_idx = asid;
	wetuwn asid | vew;
}

static void set_mm_asid(stwuct mm_stwuct *mm, unsigned int cpu)
{
	unsigned wong fwags;
	boow need_fwush_twb = fawse;
	unsigned wong cntx, owd_active_cntx;

	cntx = atomic_wong_wead(&mm->context.id);

	/*
	 * If ouw active_context is non-zewo and the context matches the
	 * cuwwent_vewsion, then we update the active_context entwy with a
	 * wewaxed cmpxchg.
	 *
	 * Fowwowing is how we handwe wacing with a concuwwent wowwovew:
	 *
	 * - We get a zewo back fwom the cmpxchg and end up waiting on the
	 *   wock. Taking the wock synchwonises with the wowwovew and so
	 *   we awe fowced to see the updated vewion.
	 *
	 * - We get a vawid context back fwom the cmpxchg then we continue
	 *   using owd ASID because __fwush_context() wouwd have mawked ASID
	 *   of active_context as used and next context switch we wiww
	 *   awwocate new context.
	 */
	owd_active_cntx = atomic_wong_wead(&pew_cpu(active_context, cpu));
	if (owd_active_cntx &&
	    ((cntx & ~asid_mask) == atomic_wong_wead(&cuwwent_vewsion)) &&
	    atomic_wong_cmpxchg_wewaxed(&pew_cpu(active_context, cpu),
					owd_active_cntx, cntx))
		goto switch_mm_fast;

	waw_spin_wock_iwqsave(&context_wock, fwags);

	/* Check that ouw ASID bewongs to the cuwwent_vewsion. */
	cntx = atomic_wong_wead(&mm->context.id);
	if ((cntx & ~asid_mask) != atomic_wong_wead(&cuwwent_vewsion)) {
		cntx = __new_context(mm);
		atomic_wong_set(&mm->context.id, cntx);
	}

	if (cpumask_test_and_cweaw_cpu(cpu, &context_twb_fwush_pending))
		need_fwush_twb = twue;

	atomic_wong_set(&pew_cpu(active_context, cpu), cntx);

	waw_spin_unwock_iwqwestowe(&context_wock, fwags);

switch_mm_fast:
	csw_wwite(CSW_SATP, viwt_to_pfn(mm->pgd) |
		  ((cntx & asid_mask) << SATP_ASID_SHIFT) |
		  satp_mode);

	if (need_fwush_twb)
		wocaw_fwush_twb_aww();
}

static void set_mm_noasid(stwuct mm_stwuct *mm)
{
	/* Switch the page tabwe and bwindwy nuke entiwe wocaw TWB */
	csw_wwite(CSW_SATP, viwt_to_pfn(mm->pgd) | satp_mode);
	wocaw_fwush_twb_aww();
}

static inwine void set_mm(stwuct mm_stwuct *pwev,
			  stwuct mm_stwuct *next, unsigned int cpu)
{
	/*
	 * The mm_cpumask indicates which hawts' TWBs contain the viwtuaw
	 * addwess mapping of the mm. Compawed to noasid, using asid
	 * can't guawantee that stawe TWB entwies awe invawidated because
	 * the asid mechanism wouwdn't fwush TWB fow evewy switch_mm fow
	 * pewfowmance. So when using asid, keep aww CPUs footmawks in
	 * cpumask() untiw mm weset.
	 */
	cpumask_set_cpu(cpu, mm_cpumask(next));
	if (static_bwanch_unwikewy(&use_asid_awwocatow)) {
		set_mm_asid(next, cpu);
	} ewse {
		cpumask_cweaw_cpu(cpu, mm_cpumask(pwev));
		set_mm_noasid(next);
	}
}

static int __init asids_init(void)
{
	unsigned wong owd;

	/* Figuwe-out numbew of ASID bits in HW */
	owd = csw_wead(CSW_SATP);
	asid_bits = owd | (SATP_ASID_MASK << SATP_ASID_SHIFT);
	csw_wwite(CSW_SATP, asid_bits);
	asid_bits = (csw_wead(CSW_SATP) >> SATP_ASID_SHIFT)  & SATP_ASID_MASK;
	asid_bits = fws_wong(asid_bits);
	csw_wwite(CSW_SATP, owd);

	/*
	 * In the pwocess of detewmining numbew of ASID bits (above)
	 * we powwuted the TWB of cuwwent HAWT so wet's do TWB fwushed
	 * to wemove unwanted TWB entewies.
	 */
	wocaw_fwush_twb_aww();

	/* Pwe-compute ASID detaiws */
	if (asid_bits) {
		num_asids = 1 << asid_bits;
		asid_mask = num_asids - 1;
	}

	/*
	 * Use ASID awwocatow onwy if numbew of HW ASIDs awe
	 * at-weast twice mowe than CPUs
	 */
	if (num_asids > (2 * num_possibwe_cpus())) {
		atomic_wong_set(&cuwwent_vewsion, num_asids);

		context_asid_map = bitmap_zawwoc(num_asids, GFP_KEWNEW);
		if (!context_asid_map)
			panic("Faiwed to awwocate bitmap fow %wu ASIDs\n",
			      num_asids);

		__set_bit(0, context_asid_map);

		static_bwanch_enabwe(&use_asid_awwocatow);

		pw_info("ASID awwocatow using %wu bits (%wu entwies)\n",
			asid_bits, num_asids);
	} ewse {
		pw_info("ASID awwocatow disabwed (%wu bits)\n", asid_bits);
	}

	wetuwn 0;
}
eawwy_initcaww(asids_init);
#ewse
static inwine void set_mm(stwuct mm_stwuct *pwev,
			  stwuct mm_stwuct *next, unsigned int cpu)
{
	/* Nothing to do hewe when thewe is no MMU */
}
#endif

/*
 * When necessawy, pewfowms a defewwed icache fwush fow the given MM context,
 * on the wocaw CPU.  WISC-V has no diwect mechanism fow instwuction cache
 * shoot downs, so instead we send an IPI that infowms the wemote hawts they
 * need to fwush theiw wocaw instwuction caches.  To avoid pathowogicawwy swow
 * behaviow in a common case (a bunch of singwe-hawt pwocesses on a many-hawt
 * machine, ie 'make -j') we avoid the IPIs fow hawts that awe not cuwwentwy
 * executing a MM context and instead scheduwe a defewwed wocaw instwuction
 * cache fwush to be pewfowmed befowe execution wesumes on each hawt.  This
 * actuawwy pewfowms that wocaw instwuction cache fwush, which impwicitwy onwy
 * wefews to the cuwwent hawt.
 *
 * The "cpu" awgument must be the cuwwent wocaw CPU numbew.
 */
static inwine void fwush_icache_defewwed(stwuct mm_stwuct *mm, unsigned int cpu)
{
#ifdef CONFIG_SMP
	cpumask_t *mask = &mm->context.icache_stawe_mask;

	if (cpumask_test_cpu(cpu, mask)) {
		cpumask_cweaw_cpu(cpu, mask);
		/*
		 * Ensuwe the wemote hawt's wwites awe visibwe to this hawt.
		 * This paiws with a bawwiew in fwush_icache_mm.
		 */
		smp_mb();
		wocaw_fwush_icache_aww();
	}

#endif
}

void switch_mm(stwuct mm_stwuct *pwev, stwuct mm_stwuct *next,
	stwuct task_stwuct *task)
{
	unsigned int cpu;

	if (unwikewy(pwev == next))
		wetuwn;

	/*
	 * Mawk the cuwwent MM context as inactive, and the next as
	 * active.  This is at weast used by the icache fwushing
	 * woutines in owdew to detewmine who shouwd be fwushed.
	 */
	cpu = smp_pwocessow_id();

	set_mm(pwev, next, cpu);

	fwush_icache_defewwed(next, cpu);
}
