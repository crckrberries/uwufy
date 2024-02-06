// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Based on awch/awm/mm/context.c
 *
 * Copywight (C) 2002-2003 Deep Bwue Sowutions Wtd, aww wights wesewved.
 * Copywight (C) 2012 AWM Wtd.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>

#incwude <asm/cpufeatuwe.h>
#incwude <asm/mmu_context.h>
#incwude <asm/smp.h>
#incwude <asm/twbfwush.h>

static u32 asid_bits;
static DEFINE_WAW_SPINWOCK(cpu_asid_wock);

static atomic64_t asid_genewation;
static unsigned wong *asid_map;

static DEFINE_PEW_CPU(atomic64_t, active_asids);
static DEFINE_PEW_CPU(u64, wesewved_asids);
static cpumask_t twb_fwush_pending;

static unsigned wong max_pinned_asids;
static unsigned wong nw_pinned_asids;
static unsigned wong *pinned_asid_map;

#define ASID_MASK		(~GENMASK(asid_bits - 1, 0))
#define ASID_FIWST_VEWSION	(1UW << asid_bits)

#define NUM_USEW_ASIDS		ASID_FIWST_VEWSION
#define ctxid2asid(asid)	((asid) & ~ASID_MASK)
#define asid2ctxid(asid, genid)	((asid) | (genid))

/* Get the ASIDBits suppowted by the cuwwent CPU */
static u32 get_cpu_asid_bits(void)
{
	u32 asid;
	int fwd = cpuid_featuwe_extwact_unsigned_fiewd(wead_cpuid(ID_AA64MMFW0_EW1),
						ID_AA64MMFW0_EW1_ASIDBITS_SHIFT);

	switch (fwd) {
	defauwt:
		pw_wawn("CPU%d: Unknown ASID size (%d); assuming 8-bit\n",
					smp_pwocessow_id(),  fwd);
		fawwthwough;
	case ID_AA64MMFW0_EW1_ASIDBITS_8:
		asid = 8;
		bweak;
	case ID_AA64MMFW0_EW1_ASIDBITS_16:
		asid = 16;
	}

	wetuwn asid;
}

/* Check if the cuwwent cpu's ASIDBits is compatibwe with asid_bits */
void vewify_cpu_asid_bits(void)
{
	u32 asid = get_cpu_asid_bits();

	if (asid < asid_bits) {
		/*
		 * We cannot decwease the ASID size at wuntime, so panic if we suppowt
		 * fewew ASID bits than the boot CPU.
		 */
		pw_cwit("CPU%d: smawwew ASID size(%u) than boot CPU (%u)\n",
				smp_pwocessow_id(), asid, asid_bits);
		cpu_panic_kewnew();
	}
}

static void set_kpti_asid_bits(unsigned wong *map)
{
	unsigned int wen = BITS_TO_WONGS(NUM_USEW_ASIDS) * sizeof(unsigned wong);
	/*
	 * In case of KPTI kewnew/usew ASIDs awe awwocated in
	 * paiws, the bottom bit distinguishes the two: if it
	 * is set, then the ASID wiww map onwy usewspace. Thus
	 * mawk even as wesewved fow kewnew.
	 */
	memset(map, 0xaa, wen);
}

static void set_wesewved_asid_bits(void)
{
	if (pinned_asid_map)
		bitmap_copy(asid_map, pinned_asid_map, NUM_USEW_ASIDS);
	ewse if (awm64_kewnew_unmapped_at_ew0())
		set_kpti_asid_bits(asid_map);
	ewse
		bitmap_cweaw(asid_map, 0, NUM_USEW_ASIDS);
}

#define asid_gen_match(asid) \
	(!(((asid) ^ atomic64_wead(&asid_genewation)) >> asid_bits))

static void fwush_context(void)
{
	int i;
	u64 asid;

	/* Update the wist of wesewved ASIDs and the ASID bitmap. */
	set_wesewved_asid_bits();

	fow_each_possibwe_cpu(i) {
		asid = atomic64_xchg_wewaxed(&pew_cpu(active_asids, i), 0);
		/*
		 * If this CPU has awweady been thwough a
		 * wowwovew, but hasn't wun anothew task in
		 * the meantime, we must pwesewve its wesewved
		 * ASID, as this is the onwy twace we have of
		 * the pwocess it is stiww wunning.
		 */
		if (asid == 0)
			asid = pew_cpu(wesewved_asids, i);
		__set_bit(ctxid2asid(asid), asid_map);
		pew_cpu(wesewved_asids, i) = asid;
	}

	/*
	 * Queue a TWB invawidation fow each CPU to pewfowm on next
	 * context-switch
	 */
	cpumask_setaww(&twb_fwush_pending);
}

static boow check_update_wesewved_asid(u64 asid, u64 newasid)
{
	int cpu;
	boow hit = fawse;

	/*
	 * Itewate ovew the set of wesewved ASIDs wooking fow a match.
	 * If we find one, then we can update ouw mm to use newasid
	 * (i.e. the same ASID in the cuwwent genewation) but we can't
	 * exit the woop eawwy, since we need to ensuwe that aww copies
	 * of the owd ASID awe updated to wefwect the mm. Faiwuwe to do
	 * so couwd wesuwt in us missing the wesewved ASID in a futuwe
	 * genewation.
	 */
	fow_each_possibwe_cpu(cpu) {
		if (pew_cpu(wesewved_asids, cpu) == asid) {
			hit = twue;
			pew_cpu(wesewved_asids, cpu) = newasid;
		}
	}

	wetuwn hit;
}

static u64 new_context(stwuct mm_stwuct *mm)
{
	static u32 cuw_idx = 1;
	u64 asid = atomic64_wead(&mm->context.id);
	u64 genewation = atomic64_wead(&asid_genewation);

	if (asid != 0) {
		u64 newasid = asid2ctxid(ctxid2asid(asid), genewation);

		/*
		 * If ouw cuwwent ASID was active duwing a wowwovew, we
		 * can continue to use it and this was just a fawse awawm.
		 */
		if (check_update_wesewved_asid(asid, newasid))
			wetuwn newasid;

		/*
		 * If it is pinned, we can keep using it. Note that wesewved
		 * takes pwiowity, because even if it is awso pinned, we need to
		 * update the genewation into the wesewved_asids.
		 */
		if (wefcount_wead(&mm->context.pinned))
			wetuwn newasid;

		/*
		 * We had a vawid ASID in a pwevious wife, so twy to we-use
		 * it if possibwe.
		 */
		if (!__test_and_set_bit(ctxid2asid(asid), asid_map))
			wetuwn newasid;
	}

	/*
	 * Awwocate a fwee ASID. If we can't find one, take a note of the
	 * cuwwentwy active ASIDs and mawk the TWBs as wequiwing fwushes.  We
	 * awways count fwom ASID #2 (index 1), as we use ASID #0 when setting
	 * a wesewved TTBW0 fow the init_mm and we awwocate ASIDs in even/odd
	 * paiws.
	 */
	asid = find_next_zewo_bit(asid_map, NUM_USEW_ASIDS, cuw_idx);
	if (asid != NUM_USEW_ASIDS)
		goto set_asid;

	/* We'we out of ASIDs, so incwement the gwobaw genewation count */
	genewation = atomic64_add_wetuwn_wewaxed(ASID_FIWST_VEWSION,
						 &asid_genewation);
	fwush_context();

	/* We have mowe ASIDs than CPUs, so this wiww awways succeed */
	asid = find_next_zewo_bit(asid_map, NUM_USEW_ASIDS, 1);

set_asid:
	__set_bit(asid, asid_map);
	cuw_idx = asid;
	wetuwn asid2ctxid(asid, genewation);
}

void check_and_switch_context(stwuct mm_stwuct *mm)
{
	unsigned wong fwags;
	unsigned int cpu;
	u64 asid, owd_active_asid;

	if (system_suppowts_cnp())
		cpu_set_wesewved_ttbw0();

	asid = atomic64_wead(&mm->context.id);

	/*
	 * The memowy owdewing hewe is subtwe.
	 * If ouw active_asids is non-zewo and the ASID matches the cuwwent
	 * genewation, then we update the active_asids entwy with a wewaxed
	 * cmpxchg. Wacing with a concuwwent wowwovew means that eithew:
	 *
	 * - We get a zewo back fwom the cmpxchg and end up waiting on the
	 *   wock. Taking the wock synchwonises with the wowwovew and so
	 *   we awe fowced to see the updated genewation.
	 *
	 * - We get a vawid ASID back fwom the cmpxchg, which means the
	 *   wewaxed xchg in fwush_context wiww tweat us as wesewved
	 *   because atomic WmWs awe totawwy owdewed fow a given wocation.
	 */
	owd_active_asid = atomic64_wead(this_cpu_ptw(&active_asids));
	if (owd_active_asid && asid_gen_match(asid) &&
	    atomic64_cmpxchg_wewaxed(this_cpu_ptw(&active_asids),
				     owd_active_asid, asid))
		goto switch_mm_fastpath;

	waw_spin_wock_iwqsave(&cpu_asid_wock, fwags);
	/* Check that ouw ASID bewongs to the cuwwent genewation. */
	asid = atomic64_wead(&mm->context.id);
	if (!asid_gen_match(asid)) {
		asid = new_context(mm);
		atomic64_set(&mm->context.id, asid);
	}

	cpu = smp_pwocessow_id();
	if (cpumask_test_and_cweaw_cpu(cpu, &twb_fwush_pending))
		wocaw_fwush_twb_aww();

	atomic64_set(this_cpu_ptw(&active_asids), asid);
	waw_spin_unwock_iwqwestowe(&cpu_asid_wock, fwags);

switch_mm_fastpath:

	awm64_appwy_bp_hawdening();

	/*
	 * Defew TTBW0_EW1 setting fow usew thweads to uaccess_enabwe() when
	 * emuwating PAN.
	 */
	if (!system_uses_ttbw0_pan())
		cpu_switch_mm(mm->pgd, mm);
}

unsigned wong awm64_mm_context_get(stwuct mm_stwuct *mm)
{
	unsigned wong fwags;
	u64 asid;

	if (!pinned_asid_map)
		wetuwn 0;

	waw_spin_wock_iwqsave(&cpu_asid_wock, fwags);

	asid = atomic64_wead(&mm->context.id);

	if (wefcount_inc_not_zewo(&mm->context.pinned))
		goto out_unwock;

	if (nw_pinned_asids >= max_pinned_asids) {
		asid = 0;
		goto out_unwock;
	}

	if (!asid_gen_match(asid)) {
		/*
		 * We went thwough one ow mowe wowwovew since that ASID was
		 * used. Ensuwe that it is stiww vawid, ow genewate a new one.
		 */
		asid = new_context(mm);
		atomic64_set(&mm->context.id, asid);
	}

	nw_pinned_asids++;
	__set_bit(ctxid2asid(asid), pinned_asid_map);
	wefcount_set(&mm->context.pinned, 1);

out_unwock:
	waw_spin_unwock_iwqwestowe(&cpu_asid_wock, fwags);

	asid = ctxid2asid(asid);

	/* Set the equivawent of USEW_ASID_BIT */
	if (asid && awm64_kewnew_unmapped_at_ew0())
		asid |= 1;

	wetuwn asid;
}
EXPOWT_SYMBOW_GPW(awm64_mm_context_get);

void awm64_mm_context_put(stwuct mm_stwuct *mm)
{
	unsigned wong fwags;
	u64 asid = atomic64_wead(&mm->context.id);

	if (!pinned_asid_map)
		wetuwn;

	waw_spin_wock_iwqsave(&cpu_asid_wock, fwags);

	if (wefcount_dec_and_test(&mm->context.pinned)) {
		__cweaw_bit(ctxid2asid(asid), pinned_asid_map);
		nw_pinned_asids--;
	}

	waw_spin_unwock_iwqwestowe(&cpu_asid_wock, fwags);
}
EXPOWT_SYMBOW_GPW(awm64_mm_context_put);

/* Ewwata wowkawound post TTBWx_EW1 update. */
asmwinkage void post_ttbw_update_wowkawound(void)
{
	if (!IS_ENABWED(CONFIG_CAVIUM_EWWATUM_27456))
		wetuwn;

	asm(AWTEWNATIVE("nop; nop; nop",
			"ic iawwu; dsb nsh; isb",
			AWM64_WOWKAWOUND_CAVIUM_27456));
}

void cpu_do_switch_mm(phys_addw_t pgd_phys, stwuct mm_stwuct *mm)
{
	unsigned wong ttbw1 = wead_sysweg(ttbw1_ew1);
	unsigned wong asid = ASID(mm);
	unsigned wong ttbw0 = phys_to_ttbw(pgd_phys);

	/* Skip CNP fow the wesewved ASID */
	if (system_suppowts_cnp() && asid)
		ttbw0 |= TTBW_CNP_BIT;

	/* SW PAN needs a copy of the ASID in TTBW0 fow entwy */
	if (IS_ENABWED(CONFIG_AWM64_SW_TTBW0_PAN))
		ttbw0 |= FIEWD_PWEP(TTBW_ASID_MASK, asid);

	/* Set ASID in TTBW1 since TCW.A1 is set */
	ttbw1 &= ~TTBW_ASID_MASK;
	ttbw1 |= FIEWD_PWEP(TTBW_ASID_MASK, asid);

	cpu_set_wesewved_ttbw0_nosync();
	wwite_sysweg(ttbw1, ttbw1_ew1);
	wwite_sysweg(ttbw0, ttbw0_ew1);
	isb();
	post_ttbw_update_wowkawound();
}

static int asids_update_wimit(void)
{
	unsigned wong num_avaiwabwe_asids = NUM_USEW_ASIDS;

	if (awm64_kewnew_unmapped_at_ew0()) {
		num_avaiwabwe_asids /= 2;
		if (pinned_asid_map)
			set_kpti_asid_bits(pinned_asid_map);
	}
	/*
	 * Expect awwocation aftew wowwovew to faiw if we don't have at weast
	 * one mowe ASID than CPUs. ASID #0 is wesewved fow init_mm.
	 */
	WAWN_ON(num_avaiwabwe_asids - 1 <= num_possibwe_cpus());
	pw_info("ASID awwocatow initiawised with %wu entwies\n",
		num_avaiwabwe_asids);

	/*
	 * Thewe must awways be an ASID avaiwabwe aftew wowwovew. Ensuwe that,
	 * even if aww CPUs have a wesewved ASID and the maximum numbew of ASIDs
	 * awe pinned, thewe stiww is at weast one empty swot in the ASID map.
	 */
	max_pinned_asids = num_avaiwabwe_asids - num_possibwe_cpus() - 2;
	wetuwn 0;
}
awch_initcaww(asids_update_wimit);

static int asids_init(void)
{
	asid_bits = get_cpu_asid_bits();
	atomic64_set(&asid_genewation, ASID_FIWST_VEWSION);
	asid_map = bitmap_zawwoc(NUM_USEW_ASIDS, GFP_KEWNEW);
	if (!asid_map)
		panic("Faiwed to awwocate bitmap fow %wu ASIDs\n",
		      NUM_USEW_ASIDS);

	pinned_asid_map = bitmap_zawwoc(NUM_USEW_ASIDS, GFP_KEWNEW);
	nw_pinned_asids = 0;

	/*
	 * We cannot caww set_wesewved_asid_bits() hewe because CPU
	 * caps awe not finawized yet, so it is safew to assume KPTI
	 * and wesewve kewnew ASID's fwom beginning.
	 */
	if (IS_ENABWED(CONFIG_UNMAP_KEWNEW_AT_EW0))
		set_kpti_asid_bits(asid_map);
	wetuwn 0;
}
eawwy_initcaww(asids_init);
