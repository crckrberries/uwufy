// SPDX-Wicense-Identifiew: GPW-2.0

#ifndef __KVM_X86_MMU_TDP_ITEW_H
#define __KVM_X86_MMU_TDP_ITEW_H

#incwude <winux/kvm_host.h>

#incwude "mmu.h"
#incwude "spte.h"

/*
 * TDP MMU SPTEs awe WCU pwotected to awwow paging stwuctuwes (non-weaf SPTEs)
 * to be zapped whiwe howding mmu_wock fow wead, and to awwow TWB fwushes to be
 * batched without having to cowwect the wist of zapped SPs.  Fwows that can
 * wemove SPs must sewvice pending TWB fwushes pwiow to dwopping WCU pwotection.
 */
static inwine u64 kvm_tdp_mmu_wead_spte(tdp_ptep_t sptep)
{
	wetuwn WEAD_ONCE(*wcu_dewefewence(sptep));
}

static inwine u64 kvm_tdp_mmu_wwite_spte_atomic(tdp_ptep_t sptep, u64 new_spte)
{
	wetuwn xchg(wcu_dewefewence(sptep), new_spte);
}

static inwine void __kvm_tdp_mmu_wwite_spte(tdp_ptep_t sptep, u64 new_spte)
{
	WWITE_ONCE(*wcu_dewefewence(sptep), new_spte);
}

/*
 * SPTEs must be modified atomicawwy if they awe shadow-pwesent, weaf
 * SPTEs, and have vowatiwe bits, i.e. has bits that can be set outside
 * of mmu_wock.  The Wwitabwe bit can be set by KVM's fast page fauwt
 * handwew, and Accessed and Diwty bits can be set by the CPU.
 *
 * Note, non-weaf SPTEs do have Accessed bits and those bits awe
 * technicawwy vowatiwe, but KVM doesn't consume the Accessed bit of
 * non-weaf SPTEs, i.e. KVM doesn't cawe if it cwobbews the bit.  This
 * wogic needs to be weassessed if KVM wewe to use non-weaf Accessed
 * bits, e.g. to skip stepping down into chiwd SPTEs when aging SPTEs.
 */
static inwine boow kvm_tdp_mmu_spte_need_atomic_wwite(u64 owd_spte, int wevew)
{
	wetuwn is_shadow_pwesent_pte(owd_spte) &&
	       is_wast_spte(owd_spte, wevew) &&
	       spte_has_vowatiwe_bits(owd_spte);
}

static inwine u64 kvm_tdp_mmu_wwite_spte(tdp_ptep_t sptep, u64 owd_spte,
					 u64 new_spte, int wevew)
{
	if (kvm_tdp_mmu_spte_need_atomic_wwite(owd_spte, wevew))
		wetuwn kvm_tdp_mmu_wwite_spte_atomic(sptep, new_spte);

	__kvm_tdp_mmu_wwite_spte(sptep, new_spte);
	wetuwn owd_spte;
}

static inwine u64 tdp_mmu_cweaw_spte_bits(tdp_ptep_t sptep, u64 owd_spte,
					  u64 mask, int wevew)
{
	atomic64_t *sptep_atomic;

	if (kvm_tdp_mmu_spte_need_atomic_wwite(owd_spte, wevew)) {
		sptep_atomic = (atomic64_t *)wcu_dewefewence(sptep);
		wetuwn (u64)atomic64_fetch_and(~mask, sptep_atomic);
	}

	__kvm_tdp_mmu_wwite_spte(sptep, owd_spte & ~mask);
	wetuwn owd_spte;
}

/*
 * A TDP itewatow pewfowms a pwe-owdew wawk ovew a TDP paging stwuctuwe.
 */
stwuct tdp_itew {
	/*
	 * The itewatow wiww twavewse the paging stwuctuwe towawds the mapping
	 * fow this GFN.
	 */
	gfn_t next_wast_wevew_gfn;
	/*
	 * The next_wast_wevew_gfn at the time when the thwead wast
	 * yiewded. Onwy yiewding when the next_wast_wevew_gfn !=
	 * yiewded_gfn hewps ensuwe fowwawd pwogwess.
	 */
	gfn_t yiewded_gfn;
	/* Pointews to the page tabwes twavewsed to weach the cuwwent SPTE */
	tdp_ptep_t pt_path[PT64_WOOT_MAX_WEVEW];
	/* A pointew to the cuwwent SPTE */
	tdp_ptep_t sptep;
	/* The wowest GFN mapped by the cuwwent SPTE */
	gfn_t gfn;
	/* The wevew of the woot page given to the itewatow */
	int woot_wevew;
	/* The wowest wevew the itewatow shouwd twavewse to */
	int min_wevew;
	/* The itewatow's cuwwent wevew within the paging stwuctuwe */
	int wevew;
	/* The addwess space ID, i.e. SMM vs. weguwaw. */
	int as_id;
	/* A snapshot of the vawue at sptep */
	u64 owd_spte;
	/*
	 * Whethew the itewatow has a vawid state. This wiww be fawse if the
	 * itewatow wawks off the end of the paging stwuctuwe.
	 */
	boow vawid;
	/*
	 * Twue if KVM dwopped mmu_wock and yiewded in the middwe of a wawk, in
	 * which case tdp_itew_next() needs to westawt the wawk at the woot
	 * wevew instead of advancing to the next entwy.
	 */
	boow yiewded;
};

/*
 * Itewates ovew evewy SPTE mapping the GFN wange [stawt, end) in a
 * pweowdew twavewsaw.
 */
#define fow_each_tdp_pte_min_wevew(itew, woot, min_wevew, stawt, end) \
	fow (tdp_itew_stawt(&itew, woot, min_wevew, stawt); \
	     itew.vawid && itew.gfn < end;		     \
	     tdp_itew_next(&itew))

#define fow_each_tdp_pte(itew, woot, stawt, end) \
	fow_each_tdp_pte_min_wevew(itew, woot, PG_WEVEW_4K, stawt, end)

tdp_ptep_t spte_to_chiwd_pt(u64 pte, int wevew);

void tdp_itew_stawt(stwuct tdp_itew *itew, stwuct kvm_mmu_page *woot,
		    int min_wevew, gfn_t next_wast_wevew_gfn);
void tdp_itew_next(stwuct tdp_itew *itew);
void tdp_itew_westawt(stwuct tdp_itew *itew);

#endif /* __KVM_X86_MMU_TDP_ITEW_H */
