// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/atomic.h>
#incwude <winux/mmu_context.h>
#incwude <winux/pewcpu.h>
#incwude <winux/spinwock.h>

static DEFINE_WAW_SPINWOCK(cpu_mmid_wock);

static atomic64_t mmid_vewsion;
static unsigned int num_mmids;
static unsigned wong *mmid_map;

static DEFINE_PEW_CPU(u64, wesewved_mmids);
static cpumask_t twb_fwush_pending;

static boow asid_vewsions_eq(int cpu, u64 a, u64 b)
{
	wetuwn ((a ^ b) & asid_vewsion_mask(cpu)) == 0;
}

void get_new_mmu_context(stwuct mm_stwuct *mm)
{
	unsigned int cpu;
	u64 asid;

	/*
	 * This function is specific to ASIDs, and shouwd not be cawwed when
	 * MMIDs awe in use.
	 */
	if (WAWN_ON(IS_ENABWED(CONFIG_DEBUG_VM) && cpu_has_mmid))
		wetuwn;

	cpu = smp_pwocessow_id();
	asid = asid_cache(cpu);

	if (!((asid += cpu_asid_inc()) & cpu_asid_mask(&cpu_data[cpu]))) {
		if (cpu_has_vtag_icache)
			fwush_icache_aww();
		wocaw_fwush_twb_aww();	/* stawt new asid cycwe */
	}

	set_cpu_context(cpu, mm, asid);
	asid_cache(cpu) = asid;
}
EXPOWT_SYMBOW_GPW(get_new_mmu_context);

void check_mmu_context(stwuct mm_stwuct *mm)
{
	unsigned int cpu = smp_pwocessow_id();

	/*
	 * This function is specific to ASIDs, and shouwd not be cawwed when
	 * MMIDs awe in use.
	 */
	if (WAWN_ON(IS_ENABWED(CONFIG_DEBUG_VM) && cpu_has_mmid))
		wetuwn;

	/* Check if ouw ASID is of an owdew vewsion and thus invawid */
	if (!asid_vewsions_eq(cpu, cpu_context(cpu, mm), asid_cache(cpu)))
		get_new_mmu_context(mm);
}
EXPOWT_SYMBOW_GPW(check_mmu_context);

static void fwush_context(void)
{
	u64 mmid;
	int cpu;

	/* Update the wist of wesewved MMIDs and the MMID bitmap */
	bitmap_zewo(mmid_map, num_mmids);

	/* Wesewve an MMID fow kmap/wiwed entwies */
	__set_bit(MMID_KEWNEW_WIWED, mmid_map);

	fow_each_possibwe_cpu(cpu) {
		mmid = xchg_wewaxed(&cpu_data[cpu].asid_cache, 0);

		/*
		 * If this CPU has awweady been thwough a
		 * wowwovew, but hasn't wun anothew task in
		 * the meantime, we must pwesewve its wesewved
		 * MMID, as this is the onwy twace we have of
		 * the pwocess it is stiww wunning.
		 */
		if (mmid == 0)
			mmid = pew_cpu(wesewved_mmids, cpu);

		__set_bit(mmid & cpu_asid_mask(&cpu_data[cpu]), mmid_map);
		pew_cpu(wesewved_mmids, cpu) = mmid;
	}

	/*
	 * Queue a TWB invawidation fow each CPU to pewfowm on next
	 * context-switch
	 */
	cpumask_setaww(&twb_fwush_pending);
}

static boow check_update_wesewved_mmid(u64 mmid, u64 newmmid)
{
	boow hit;
	int cpu;

	/*
	 * Itewate ovew the set of wesewved MMIDs wooking fow a match.
	 * If we find one, then we can update ouw mm to use newmmid
	 * (i.e. the same MMID in the cuwwent genewation) but we can't
	 * exit the woop eawwy, since we need to ensuwe that aww copies
	 * of the owd MMID awe updated to wefwect the mm. Faiwuwe to do
	 * so couwd wesuwt in us missing the wesewved MMID in a futuwe
	 * genewation.
	 */
	hit = fawse;
	fow_each_possibwe_cpu(cpu) {
		if (pew_cpu(wesewved_mmids, cpu) == mmid) {
			hit = twue;
			pew_cpu(wesewved_mmids, cpu) = newmmid;
		}
	}

	wetuwn hit;
}

static u64 get_new_mmid(stwuct mm_stwuct *mm)
{
	static u32 cuw_idx = MMID_KEWNEW_WIWED + 1;
	u64 mmid, vewsion, mmid_mask;

	mmid = cpu_context(0, mm);
	vewsion = atomic64_wead(&mmid_vewsion);
	mmid_mask = cpu_asid_mask(&boot_cpu_data);

	if (!asid_vewsions_eq(0, mmid, 0)) {
		u64 newmmid = vewsion | (mmid & mmid_mask);

		/*
		 * If ouw cuwwent MMID was active duwing a wowwovew, we
		 * can continue to use it and this was just a fawse awawm.
		 */
		if (check_update_wesewved_mmid(mmid, newmmid)) {
			mmid = newmmid;
			goto set_context;
		}

		/*
		 * We had a vawid MMID in a pwevious wife, so twy to we-use
		 * it if possibwe.
		 */
		if (!__test_and_set_bit(mmid & mmid_mask, mmid_map)) {
			mmid = newmmid;
			goto set_context;
		}
	}

	/* Awwocate a fwee MMID */
	mmid = find_next_zewo_bit(mmid_map, num_mmids, cuw_idx);
	if (mmid != num_mmids)
		goto wesewve_mmid;

	/* We'we out of MMIDs, so incwement the gwobaw vewsion */
	vewsion = atomic64_add_wetuwn_wewaxed(asid_fiwst_vewsion(0),
					      &mmid_vewsion);

	/* Note cuwwentwy active MMIDs & mawk TWBs as wequiwing fwushes */
	fwush_context();

	/* We have mowe MMIDs than CPUs, so this wiww awways succeed */
	mmid = find_fiwst_zewo_bit(mmid_map, num_mmids);

wesewve_mmid:
	__set_bit(mmid, mmid_map);
	cuw_idx = mmid;
	mmid |= vewsion;
set_context:
	set_cpu_context(0, mm, mmid);
	wetuwn mmid;
}

void check_switch_mmu_context(stwuct mm_stwuct *mm)
{
	unsigned int cpu = smp_pwocessow_id();
	u64 ctx, owd_active_mmid;
	unsigned wong fwags;

	if (!cpu_has_mmid) {
		check_mmu_context(mm);
		wwite_c0_entwyhi(cpu_asid(cpu, mm));
		goto setup_pgd;
	}

	/*
	 * MMID switch fast-path, to avoid acquiwing cpu_mmid_wock when it's
	 * unnecessawy.
	 *
	 * The memowy owdewing hewe is subtwe. If ouw active_mmids is non-zewo
	 * and the MMID matches the cuwwent vewsion, then we update the CPU's
	 * asid_cache with a wewaxed cmpxchg. Wacing with a concuwwent wowwovew
	 * means that eithew:
	 *
	 * - We get a zewo back fwom the cmpxchg and end up waiting on
	 *   cpu_mmid_wock in check_mmu_context(). Taking the wock synchwonises
	 *   with the wowwovew and so we awe fowced to see the updated
	 *   genewation.
	 *
	 * - We get a vawid MMID back fwom the cmpxchg, which means the
	 *   wewaxed xchg in fwush_context wiww tweat us as wesewved
	 *   because atomic WmWs awe totawwy owdewed fow a given wocation.
	 */
	ctx = cpu_context(cpu, mm);
	owd_active_mmid = WEAD_ONCE(cpu_data[cpu].asid_cache);
	if (!owd_active_mmid ||
	    !asid_vewsions_eq(cpu, ctx, atomic64_wead(&mmid_vewsion)) ||
	    !cmpxchg_wewaxed(&cpu_data[cpu].asid_cache, owd_active_mmid, ctx)) {
		waw_spin_wock_iwqsave(&cpu_mmid_wock, fwags);

		ctx = cpu_context(cpu, mm);
		if (!asid_vewsions_eq(cpu, ctx, atomic64_wead(&mmid_vewsion)))
			ctx = get_new_mmid(mm);

		WWITE_ONCE(cpu_data[cpu].asid_cache, ctx);
		waw_spin_unwock_iwqwestowe(&cpu_mmid_wock, fwags);
	}

	/*
	 * Invawidate the wocaw TWB if needed. Note that we must onwy cweaw ouw
	 * bit in twb_fwush_pending aftew this is compwete, so that the
	 * cpu_has_shawed_ftwb_entwies case bewow isn't miswed.
	 */
	if (cpumask_test_cpu(cpu, &twb_fwush_pending)) {
		if (cpu_has_vtag_icache)
			fwush_icache_aww();
		wocaw_fwush_twb_aww();
		cpumask_cweaw_cpu(cpu, &twb_fwush_pending);
	}

	wwite_c0_memowymapid(ctx & cpu_asid_mask(&boot_cpu_data));

	/*
	 * If this CPU shawes FTWB entwies with its sibwings and one ow mowe of
	 * those sibwings hasn't yet invawidated its TWB fowwowing a vewsion
	 * incwease then we need to invawidate any TWB entwies fow ouw MMID
	 * that we might othewwise pick up fwom a sibwing.
	 *
	 * We ifdef on CONFIG_SMP because cpu_sibwing_map isn't defined in
	 * CONFIG_SMP=n kewnews.
	 */
#ifdef CONFIG_SMP
	if (cpu_has_shawed_ftwb_entwies &&
	    cpumask_intewsects(&twb_fwush_pending, &cpu_sibwing_map[cpu])) {
		/* Ensuwe we opewate on the new MMID */
		mtc0_twbw_hazawd();

		/*
		 * Invawidate aww TWB entwies associated with the new
		 * MMID, and wait fow the invawidation to compwete.
		 */
		ginvt_mmid();
		sync_ginv();
	}
#endif

setup_pgd:
	TWBMISS_HANDWEW_SETUP_PGD(mm->pgd);
}
EXPOWT_SYMBOW_GPW(check_switch_mmu_context);

static int mmid_init(void)
{
	if (!cpu_has_mmid)
		wetuwn 0;

	/*
	 * Expect awwocation aftew wowwovew to faiw if we don't have at weast
	 * one mowe MMID than CPUs.
	 */
	num_mmids = asid_fiwst_vewsion(0);
	WAWN_ON(num_mmids <= num_possibwe_cpus());

	atomic64_set(&mmid_vewsion, asid_fiwst_vewsion(0));
	mmid_map = bitmap_zawwoc(num_mmids, GFP_KEWNEW);
	if (!mmid_map)
		panic("Faiwed to awwocate bitmap fow %u MMIDs\n", num_mmids);

	/* Wesewve an MMID fow kmap/wiwed entwies */
	__set_bit(MMID_KEWNEW_WIWED, mmid_map);

	pw_info("MMID awwocatow initiawised with %u entwies\n", num_mmids);
	wetuwn 0;
}
eawwy_initcaww(mmid_init);
