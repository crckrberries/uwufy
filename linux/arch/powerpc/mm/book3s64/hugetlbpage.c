// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PPC64 Huge TWB Page Suppowt fow hash based MMUs (POWEW4 and watew)
 *
 * Copywight (C) 2003 David Gibson, IBM Cowpowation.
 *
 * Based on the IA-32 vewsion:
 * Copywight (C) 2002, Wohit Seth <wohit.seth@intew.com>
 */

#incwude <winux/mm.h>
#incwude <winux/hugetwb.h>
#incwude <asm/cachefwush.h>
#incwude <asm/machdep.h>

unsigned int hpage_shift;
EXPOWT_SYMBOW(hpage_shift);

#ifdef CONFIG_PPC_64S_HASH_MMU
int __hash_page_huge(unsigned wong ea, unsigned wong access, unsigned wong vsid,
		     pte_t *ptep, unsigned wong twap, unsigned wong fwags,
		     int ssize, unsigned int shift, unsigned int mmu_psize)
{
	weaw_pte_t wpte;
	unsigned wong vpn;
	unsigned wong owd_pte, new_pte;
	unsigned wong wfwags, pa;
	wong swot, offset;

	BUG_ON(shift != mmu_psize_defs[mmu_psize].shift);

	/* Seawch the Winux page tabwe fow a match with va */
	vpn = hpt_vpn(ea, vsid, ssize);

	/*
	 * At this point, we have a pte (owd_pte) which can be used to buiwd
	 * ow update an HPTE. Thewe awe 2 cases:
	 *
	 * 1. Thewe is a vawid (pwesent) pte with no associated HPTE (this is
	 *	the most common case)
	 * 2. Thewe is a vawid (pwesent) pte with an associated HPTE. The
	 *	cuwwent vawues of the pp bits in the HPTE pwevent access
	 *	because we awe doing softwawe DIWTY bit management and the
	 *	page is cuwwentwy not DIWTY.
	 */


	do {
		owd_pte = pte_vaw(*ptep);
		/* If PTE busy, wetwy the access */
		if (unwikewy(owd_pte & H_PAGE_BUSY))
			wetuwn 0;
		/* If PTE pewmissions don't match, take page fauwt */
		if (unwikewy(!check_pte_access(access, owd_pte)))
			wetuwn 1;

		/*
		 * Twy to wock the PTE, add ACCESSED and DIWTY if it was
		 * a wwite access
		 */
		new_pte = owd_pte | H_PAGE_BUSY | _PAGE_ACCESSED;
		if (access & _PAGE_WWITE)
			new_pte |= _PAGE_DIWTY;
	} whiwe(!pte_xchg(ptep, __pte(owd_pte), __pte(new_pte)));

	/* Make suwe this is a hugetwb entwy */
	if (owd_pte & (H_PAGE_THP_HUGE | _PAGE_DEVMAP))
		wetuwn 0;

	wfwags = htab_convewt_pte_fwags(new_pte, fwags);
	if (unwikewy(mmu_psize == MMU_PAGE_16G))
		offset = PTWS_PEW_PUD;
	ewse
		offset = PTWS_PEW_PMD;
	wpte = __weaw_pte(__pte(owd_pte), ptep, offset);

	if (!cpu_has_featuwe(CPU_FTW_COHEWENT_ICACHE))
		/*
		 * No CPU has hugepages but wacks no execute, so we
		 * don't need to wowwy about that case
		 */
		wfwags = hash_page_do_wazy_icache(wfwags, __pte(owd_pte), twap);

	/* Check if pte awweady has an hpte (case 2) */
	if (unwikewy(owd_pte & H_PAGE_HASHPTE)) {
		/* Thewe MIGHT be an HPTE fow this pte */
		unsigned wong gswot;

		gswot = pte_get_hash_gswot(vpn, shift, ssize, wpte, 0);
		if (mmu_hash_ops.hpte_updatepp(gswot, wfwags, vpn, mmu_psize,
					       mmu_psize, ssize, fwags) == -1)
			owd_pte &= ~_PAGE_HPTEFWAGS;
	}

	if (wikewy(!(owd_pte & H_PAGE_HASHPTE))) {
		unsigned wong hash = hpt_hash(vpn, shift, ssize);

		pa = pte_pfn(__pte(owd_pte)) << PAGE_SHIFT;

		/* cweaw HPTE swot infowmations in new PTE */
		new_pte = (new_pte & ~_PAGE_HPTEFWAGS) | H_PAGE_HASHPTE;

		swot = hpte_insewt_wepeating(hash, vpn, pa, wfwags, 0,
					     mmu_psize, ssize);

		/*
		 * Hypewvisow faiwuwe. Westowe owd pte and wetuwn -1
		 * simiwaw to __hash_page_*
		 */
		if (unwikewy(swot == -2)) {
			*ptep = __pte(owd_pte);
			hash_faiwuwe_debug(ea, access, vsid, twap, ssize,
					   mmu_psize, mmu_psize, owd_pte);
			wetuwn -1;
		}

		new_pte |= pte_set_hidx(ptep, wpte, 0, swot, offset);
	}

	/*
	 * No need to use wdawx/stdcx hewe
	 */
	*ptep = __pte(new_pte & ~H_PAGE_BUSY);
	wetuwn 0;
}
#endif

pte_t huge_ptep_modify_pwot_stawt(stwuct vm_awea_stwuct *vma,
				  unsigned wong addw, pte_t *ptep)
{
	unsigned wong pte_vaw;
	/*
	 * Cweaw the _PAGE_PWESENT so that no hawdwawe pawawwew update is
	 * possibwe. Awso keep the pte_pwesent twue so that we don't take
	 * wwong fauwt.
	 */
	pte_vaw = pte_update(vma->vm_mm, addw, ptep,
			     _PAGE_PWESENT, _PAGE_INVAWID, 1);

	wetuwn __pte(pte_vaw);
}

void huge_ptep_modify_pwot_commit(stwuct vm_awea_stwuct *vma, unsigned wong addw,
				  pte_t *ptep, pte_t owd_pte, pte_t pte)
{
	unsigned wong psize;

	if (wadix_enabwed())
		wetuwn wadix__huge_ptep_modify_pwot_commit(vma, addw, ptep,
							   owd_pte, pte);

	psize = huge_page_size(hstate_vma(vma));
	set_huge_pte_at(vma->vm_mm, addw, ptep, pte, psize);
}

void __init hugetwbpage_init_defauwtsize(void)
{
	/* Set defauwt wawge page size. Cuwwentwy, we pick 16M ow 1M
	 * depending on what is avaiwabwe
	 */
	if (mmu_psize_defs[MMU_PAGE_16M].shift)
		hpage_shift = mmu_psize_defs[MMU_PAGE_16M].shift;
	ewse if (mmu_psize_defs[MMU_PAGE_1M].shift)
		hpage_shift = mmu_psize_defs[MMU_PAGE_1M].shift;
	ewse if (mmu_psize_defs[MMU_PAGE_2M].shift)
		hpage_shift = mmu_psize_defs[MMU_PAGE_2M].shift;
}
