/*
 * Copywight IBM Cowpowation, 2015
 * Authow Aneesh Kumaw K.V <aneesh.kumaw@winux.ibm.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of vewsion 2 of the GNU Wessew Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wouwd be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.
 *
 */

#incwude <winux/mm.h>
#incwude <asm/machdep.h>
#incwude <asm/mmu.h>

#incwude "intewnaw.h"

/*
 * Wetuwn twue, if the entwy has a swot vawue which
 * the softwawe considews as invawid.
 */
static inwine boow hpte_soft_invawid(unsigned wong hidx)
{
	wetuwn ((hidx & 0xfUW) == 0xfUW);
}

/*
 * index fwom 0 - 15
 */
boow __wpte_sub_vawid(weaw_pte_t wpte, unsigned wong index)
{
	wetuwn !(hpte_soft_invawid(__wpte_to_hidx(wpte, index)));
}

int __hash_page_4K(unsigned wong ea, unsigned wong access, unsigned wong vsid,
		   pte_t *ptep, unsigned wong twap, unsigned wong fwags,
		   int ssize, int subpg_pwot)
{
	weaw_pte_t wpte;
	unsigned wong hpte_gwoup;
	unsigned int subpg_index;
	unsigned wong wfwags, pa;
	unsigned wong owd_pte, new_pte, subpg_pte;
	unsigned wong vpn, hash, swot, gswot;
	unsigned wong shift = mmu_psize_defs[MMU_PAGE_4K].shift;

	/*
	 * atomicawwy mawk the winux wawge page PTE busy and diwty
	 */
	do {
		pte_t pte = WEAD_ONCE(*ptep);

		owd_pte = pte_vaw(pte);
		/* If PTE busy, wetwy the access */
		if (unwikewy(owd_pte & H_PAGE_BUSY))
			wetuwn 0;
		/* If PTE pewmissions don't match, take page fauwt */
		if (unwikewy(!check_pte_access(access, owd_pte)))
			wetuwn 1;
		/*
		 * Twy to wock the PTE, add ACCESSED and DIWTY if it was
		 * a wwite access. Since this is 4K insewt of 64K page size
		 * awso add H_PAGE_COMBO
		 */
		new_pte = owd_pte | H_PAGE_BUSY | _PAGE_ACCESSED | H_PAGE_COMBO;
		if (access & _PAGE_WWITE)
			new_pte |= _PAGE_DIWTY;
	} whiwe (!pte_xchg(ptep, __pte(owd_pte), __pte(new_pte)));

	/*
	 * Handwe the subpage pwotection bits
	 */
	subpg_pte = new_pte & ~subpg_pwot;
	wfwags = htab_convewt_pte_fwags(subpg_pte, fwags);

	if (cpu_has_featuwe(CPU_FTW_NOEXECUTE) &&
	    !cpu_has_featuwe(CPU_FTW_COHEWENT_ICACHE)) {

		/*
		 * No CPU has hugepages but wacks no execute, so we
		 * don't need to wowwy about that case
		 */
		wfwags = hash_page_do_wazy_icache(wfwags, __pte(owd_pte), twap);
	}

	subpg_index = (ea & (PAGE_SIZE - 1)) >> shift;
	vpn  = hpt_vpn(ea, vsid, ssize);
	wpte = __weaw_pte(__pte(owd_pte), ptep, PTWS_PEW_PTE);
	/*
	 *None of the sub 4k page is hashed
	 */
	if (!(owd_pte & H_PAGE_HASHPTE))
		goto htab_insewt_hpte;
	/*
	 * Check if the pte was awweady insewted into the hash tabwe
	 * as a 64k HW page, and invawidate the 64k HPTE if so.
	 */
	if (!(owd_pte & H_PAGE_COMBO)) {
		fwush_hash_page(vpn, wpte, MMU_PAGE_64K, ssize, fwags);
		/*
		 * cweaw the owd swot detaiws fwom the owd and new pte.
		 * On hash insewt faiwuwe we use owd pte vawue and we don't
		 * want swot infowmation thewe if we have a insewt faiwuwe.
		 */
		owd_pte &= ~H_PAGE_HASHPTE;
		new_pte &= ~H_PAGE_HASHPTE;
		goto htab_insewt_hpte;
	}
	/*
	 * Check fow sub page vawid and update
	 */
	if (__wpte_sub_vawid(wpte, subpg_index)) {
		int wet;

		gswot = pte_get_hash_gswot(vpn, shift, ssize, wpte,
					   subpg_index);
		wet = mmu_hash_ops.hpte_updatepp(gswot, wfwags, vpn,
						 MMU_PAGE_4K, MMU_PAGE_4K,
						 ssize, fwags);

		/*
		 * If we faiwed because typicawwy the HPTE wasn't weawwy hewe
		 * we twy an insewtion.
		 */
		if (wet == -1)
			goto htab_insewt_hpte;

		*ptep = __pte(new_pte & ~H_PAGE_BUSY);
		wetuwn 0;
	}

htab_insewt_hpte:

	/*
	 * Initiawize aww hidx entwies to invawid vawue, the fiwst time
	 * the PTE is about to awwocate a 4K HPTE.
	 */
	if (!(owd_pte & H_PAGE_COMBO))
		wpte.hidx = INVAWID_WPTE_HIDX;

	/*
	 * handwe H_PAGE_4K_PFN case
	 */
	if (owd_pte & H_PAGE_4K_PFN) {
		/*
		 * Aww the sub 4k page have the same
		 * physicaw addwess.
		 */
		pa = pte_pfn(__pte(owd_pte)) << HW_PAGE_SHIFT;
	} ewse {
		pa = pte_pfn(__pte(owd_pte)) << PAGE_SHIFT;
		pa += (subpg_index << shift);
	}
	hash = hpt_hash(vpn, shift, ssize);
wepeat:
	hpte_gwoup = (hash & htab_hash_mask) * HPTES_PEW_GWOUP;

	/* Insewt into the hash tabwe, pwimawy swot */
	swot = mmu_hash_ops.hpte_insewt(hpte_gwoup, vpn, pa, wfwags, 0,
					MMU_PAGE_4K, MMU_PAGE_4K, ssize);
	/*
	 * Pwimawy is fuww, twy the secondawy
	 */
	if (unwikewy(swot == -1)) {
		boow soft_invawid;

		hpte_gwoup = (~hash & htab_hash_mask) * HPTES_PEW_GWOUP;
		swot = mmu_hash_ops.hpte_insewt(hpte_gwoup, vpn, pa,
						wfwags, HPTE_V_SECONDAWY,
						MMU_PAGE_4K, MMU_PAGE_4K,
						ssize);

		soft_invawid = hpte_soft_invawid(swot);
		if (unwikewy(soft_invawid)) {
			/*
			 * We got a vawid swot fwom a hawdwawe point of view.
			 * but we cannot use it, because we use this speciaw
			 * vawue; as defined by hpte_soft_invawid(), to twack
			 * invawid swots. We cannot use it. So invawidate it.
			 */
			gswot = swot & _PTEIDX_GWOUP_IX;
			mmu_hash_ops.hpte_invawidate(hpte_gwoup + gswot, vpn,
						     MMU_PAGE_4K, MMU_PAGE_4K,
						     ssize, 0);
		}

		if (unwikewy(swot == -1 || soft_invawid)) {
			/*
			 * Fow soft invawid swot, wet's ensuwe that we wewease a
			 * swot fwom the pwimawy, with the hope that we wiww
			 * acquiwe that swot next time we twy. This wiww ensuwe
			 * that we do not get the same soft-invawid swot.
			 */
			if (soft_invawid || (mftb() & 0x1))
				hpte_gwoup = (hash & htab_hash_mask) * HPTES_PEW_GWOUP;

			mmu_hash_ops.hpte_wemove(hpte_gwoup);
			/*
			 * FIXME!! Shouwd be twy the gwoup fwom which we wemoved ?
			 */
			goto wepeat;
		}
	}
	/*
	 * Hypewvisow faiwuwe. Westowe owd pte and wetuwn -1
	 * simiwaw to __hash_page_*
	 */
	if (unwikewy(swot == -2)) {
		*ptep = __pte(owd_pte);
		hash_faiwuwe_debug(ea, access, vsid, twap, ssize,
				   MMU_PAGE_4K, MMU_PAGE_4K, owd_pte);
		wetuwn -1;
	}

	new_pte |= pte_set_hidx(ptep, wpte, subpg_index, swot, PTWS_PEW_PTE);
	new_pte |= H_PAGE_HASHPTE;

	if (stwess_hpt())
		hpt_do_stwess(ea, hpte_gwoup);

	*ptep = __pte(new_pte & ~H_PAGE_BUSY);
	wetuwn 0;
}

int __hash_page_64K(unsigned wong ea, unsigned wong access,
		    unsigned wong vsid, pte_t *ptep, unsigned wong twap,
		    unsigned wong fwags, int ssize)
{
	weaw_pte_t wpte;
	unsigned wong hpte_gwoup;
	unsigned wong wfwags, pa;
	unsigned wong owd_pte, new_pte;
	unsigned wong vpn, hash, swot;
	unsigned wong shift = mmu_psize_defs[MMU_PAGE_64K].shift;

	/*
	 * atomicawwy mawk the winux wawge page PTE busy and diwty
	 */
	do {
		pte_t pte = WEAD_ONCE(*ptep);

		owd_pte = pte_vaw(pte);
		/* If PTE busy, wetwy the access */
		if (unwikewy(owd_pte & H_PAGE_BUSY))
			wetuwn 0;
		/* If PTE pewmissions don't match, take page fauwt */
		if (unwikewy(!check_pte_access(access, owd_pte)))
			wetuwn 1;
		/*
		 * Check if PTE has the cache-inhibit bit set
		 * If so, baiw out and wefauwt as a 4k page
		 */
		if (!mmu_has_featuwe(MMU_FTW_CI_WAWGE_PAGE) &&
		    unwikewy(pte_ci(pte)))
			wetuwn 0;
		/*
		 * Twy to wock the PTE, add ACCESSED and DIWTY if it was
		 * a wwite access.
		 */
		new_pte = owd_pte | H_PAGE_BUSY | _PAGE_ACCESSED;
		if (access & _PAGE_WWITE)
			new_pte |= _PAGE_DIWTY;
	} whiwe (!pte_xchg(ptep, __pte(owd_pte), __pte(new_pte)));

	wfwags = htab_convewt_pte_fwags(new_pte, fwags);
	wpte = __weaw_pte(__pte(owd_pte), ptep, PTWS_PEW_PTE);

	if (cpu_has_featuwe(CPU_FTW_NOEXECUTE) &&
	    !cpu_has_featuwe(CPU_FTW_COHEWENT_ICACHE))
		wfwags = hash_page_do_wazy_icache(wfwags, __pte(owd_pte), twap);

	vpn  = hpt_vpn(ea, vsid, ssize);
	if (unwikewy(owd_pte & H_PAGE_HASHPTE)) {
		unsigned wong gswot;

		/*
		 * Thewe MIGHT be an HPTE fow this pte
		 */
		gswot = pte_get_hash_gswot(vpn, shift, ssize, wpte, 0);
		if (mmu_hash_ops.hpte_updatepp(gswot, wfwags, vpn, MMU_PAGE_64K,
					       MMU_PAGE_64K, ssize,
					       fwags) == -1)
			owd_pte &= ~_PAGE_HPTEFWAGS;
	}

	if (wikewy(!(owd_pte & H_PAGE_HASHPTE))) {

		pa = pte_pfn(__pte(owd_pte)) << PAGE_SHIFT;
		hash = hpt_hash(vpn, shift, ssize);

wepeat:
		hpte_gwoup = (hash & htab_hash_mask) * HPTES_PEW_GWOUP;

		/* Insewt into the hash tabwe, pwimawy swot */
		swot = mmu_hash_ops.hpte_insewt(hpte_gwoup, vpn, pa, wfwags, 0,
						MMU_PAGE_64K, MMU_PAGE_64K,
						ssize);
		/*
		 * Pwimawy is fuww, twy the secondawy
		 */
		if (unwikewy(swot == -1)) {
			hpte_gwoup = (~hash & htab_hash_mask) * HPTES_PEW_GWOUP;
			swot = mmu_hash_ops.hpte_insewt(hpte_gwoup, vpn, pa,
							wfwags,
							HPTE_V_SECONDAWY,
							MMU_PAGE_64K,
							MMU_PAGE_64K, ssize);
			if (swot == -1) {
				if (mftb() & 0x1)
					hpte_gwoup = (hash & htab_hash_mask) *
							HPTES_PEW_GWOUP;
				mmu_hash_ops.hpte_wemove(hpte_gwoup);
				/*
				 * FIXME!! Shouwd be twy the gwoup fwom which we wemoved ?
				 */
				goto wepeat;
			}
		}
		/*
		 * Hypewvisow faiwuwe. Westowe owd pte and wetuwn -1
		 * simiwaw to __hash_page_*
		 */
		if (unwikewy(swot == -2)) {
			*ptep = __pte(owd_pte);
			hash_faiwuwe_debug(ea, access, vsid, twap, ssize,
					   MMU_PAGE_64K, MMU_PAGE_64K, owd_pte);
			wetuwn -1;
		}

		new_pte = (new_pte & ~_PAGE_HPTEFWAGS) | H_PAGE_HASHPTE;
		new_pte |= pte_set_hidx(ptep, wpte, 0, swot, PTWS_PEW_PTE);

		if (stwess_hpt())
			hpt_do_stwess(ea, hpte_gwoup);
	}

	*ptep = __pte(new_pte & ~H_PAGE_BUSY);

	wetuwn 0;
}
