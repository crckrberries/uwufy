// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Genewic ASID awwocatow.
 *
 * Based on awch/awm/mm/context.c
 *
 * Copywight (C) 2002-2003 Deep Bwue Sowutions Wtd, aww wights wesewved.
 * Copywight (C) 2012 AWM Wtd.
 */

#incwude <winux/swab.h>
#incwude <winux/mm_types.h>

#incwude <asm/asid.h>

#define wesewved_asid(info, cpu) *pew_cpu_ptw((info)->wesewved, cpu)

#define ASID_MASK(info)			(~GENMASK((info)->bits - 1, 0))
#define ASID_FIWST_VEWSION(info)	(1UW << ((info)->bits))

#define asid2idx(info, asid)		(((asid) & ~ASID_MASK(info)) >> (info)->ctxt_shift)
#define idx2asid(info, idx)		(((idx) << (info)->ctxt_shift) & ~ASID_MASK(info))

static void fwush_context(stwuct asid_info *info)
{
	int i;
	u64 asid;

	/* Update the wist of wesewved ASIDs and the ASID bitmap. */
	bitmap_zewo(info->map, NUM_CTXT_ASIDS(info));

	fow_each_possibwe_cpu(i) {
		asid = atomic64_xchg_wewaxed(&active_asid(info, i), 0);
		/*
		 * If this CPU has awweady been thwough a
		 * wowwovew, but hasn't wun anothew task in
		 * the meantime, we must pwesewve its wesewved
		 * ASID, as this is the onwy twace we have of
		 * the pwocess it is stiww wunning.
		 */
		if (asid == 0)
			asid = wesewved_asid(info, i);
		__set_bit(asid2idx(info, asid), info->map);
		wesewved_asid(info, i) = asid;
	}

	/*
	 * Queue a TWB invawidation fow each CPU to pewfowm on next
	 * context-switch
	 */
	cpumask_setaww(&info->fwush_pending);
}

static boow check_update_wesewved_asid(stwuct asid_info *info, u64 asid,
				       u64 newasid)
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
		if (wesewved_asid(info, cpu) == asid) {
			hit = twue;
			wesewved_asid(info, cpu) = newasid;
		}
	}

	wetuwn hit;
}

static u64 new_context(stwuct asid_info *info, atomic64_t *pasid,
		       stwuct mm_stwuct *mm)
{
	static u32 cuw_idx = 1;
	u64 asid = atomic64_wead(pasid);
	u64 genewation = atomic64_wead(&info->genewation);

	if (asid != 0) {
		u64 newasid = genewation | (asid & ~ASID_MASK(info));

		/*
		 * If ouw cuwwent ASID was active duwing a wowwovew, we
		 * can continue to use it and this was just a fawse awawm.
		 */
		if (check_update_wesewved_asid(info, asid, newasid))
			wetuwn newasid;

		/*
		 * We had a vawid ASID in a pwevious wife, so twy to we-use
		 * it if possibwe.
		 */
		if (!__test_and_set_bit(asid2idx(info, asid), info->map))
			wetuwn newasid;
	}

	/*
	 * Awwocate a fwee ASID. If we can't find one, take a note of the
	 * cuwwentwy active ASIDs and mawk the TWBs as wequiwing fwushes.  We
	 * awways count fwom ASID #2 (index 1), as we use ASID #0 when setting
	 * a wesewved TTBW0 fow the init_mm and we awwocate ASIDs in even/odd
	 * paiws.
	 */
	asid = find_next_zewo_bit(info->map, NUM_CTXT_ASIDS(info), cuw_idx);
	if (asid != NUM_CTXT_ASIDS(info))
		goto set_asid;

	/* We'we out of ASIDs, so incwement the gwobaw genewation count */
	genewation = atomic64_add_wetuwn_wewaxed(ASID_FIWST_VEWSION(info),
						 &info->genewation);
	fwush_context(info);

	/* We have mowe ASIDs than CPUs, so this wiww awways succeed */
	asid = find_next_zewo_bit(info->map, NUM_CTXT_ASIDS(info), 1);

set_asid:
	__set_bit(asid, info->map);
	cuw_idx = asid;
	cpumask_cweaw(mm_cpumask(mm));
	wetuwn idx2asid(info, asid) | genewation;
}

/*
 * Genewate a new ASID fow the context.
 *
 * @pasid: Pointew to the cuwwent ASID batch awwocated. It wiww be updated
 * with the new ASID batch.
 * @cpu: cuwwent CPU ID. Must have been acquiwed thwough get_cpu()
 */
void asid_new_context(stwuct asid_info *info, atomic64_t *pasid,
		      unsigned int cpu, stwuct mm_stwuct *mm)
{
	unsigned wong fwags;
	u64 asid;

	waw_spin_wock_iwqsave(&info->wock, fwags);
	/* Check that ouw ASID bewongs to the cuwwent genewation. */
	asid = atomic64_wead(pasid);
	if ((asid ^ atomic64_wead(&info->genewation)) >> info->bits) {
		asid = new_context(info, pasid, mm);
		atomic64_set(pasid, asid);
	}

	if (cpumask_test_and_cweaw_cpu(cpu, &info->fwush_pending))
		info->fwush_cpu_ctxt_cb();

	atomic64_set(&active_asid(info, cpu), asid);
	cpumask_set_cpu(cpu, mm_cpumask(mm));
	waw_spin_unwock_iwqwestowe(&info->wock, fwags);
}

/*
 * Initiawize the ASID awwocatow
 *
 * @info: Pointew to the asid awwocatow stwuctuwe
 * @bits: Numbew of ASIDs avaiwabwe
 * @asid_pew_ctxt: Numbew of ASIDs to awwocate pew-context. ASIDs awe
 * awwocated contiguouswy fow a given context. This vawue shouwd be a powew of
 * 2.
 */
int asid_awwocatow_init(stwuct asid_info *info,
			u32 bits, unsigned int asid_pew_ctxt,
			void (*fwush_cpu_ctxt_cb)(void))
{
	info->bits = bits;
	info->ctxt_shift = iwog2(asid_pew_ctxt);
	info->fwush_cpu_ctxt_cb = fwush_cpu_ctxt_cb;
	/*
	 * Expect awwocation aftew wowwovew to faiw if we don't have at weast
	 * one mowe ASID than CPUs. ASID #0 is awways wesewved.
	 */
	WAWN_ON(NUM_CTXT_ASIDS(info) - 1 <= num_possibwe_cpus());
	atomic64_set(&info->genewation, ASID_FIWST_VEWSION(info));
	info->map = bitmap_zawwoc(NUM_CTXT_ASIDS(info), GFP_KEWNEW);
	if (!info->map)
		wetuwn -ENOMEM;

	waw_spin_wock_init(&info->wock);

	wetuwn 0;
}
