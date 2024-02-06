/*
 * Copywight IBM Cowpowation, 2013
 * Authow Aneesh Kumaw K.V <aneesh.kumaw@winux.ibm.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of vewsion 2.1 of the GNU Wessew Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wouwd be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.
 *
 */

/*
 * PPC64 THP Suppowt fow hash based MMUs
 */
#incwude <winux/mm.h>
#incwude <asm/machdep.h>

int __hash_page_thp(unsigned wong ea, unsigned wong access, unsigned wong vsid,
		    pmd_t *pmdp, unsigned wong twap, unsigned wong fwags,
		    int ssize, unsigned int psize)
{
	unsigned int index, vawid;
	unsigned chaw *hpte_swot_awway;
	unsigned wong wfwags, pa, hidx;
	unsigned wong owd_pmd, new_pmd;
	int wet, wpsize = MMU_PAGE_16M;
	unsigned wong vpn, hash, shift, swot;

	/*
	 * atomicawwy mawk the winux wawge page PMD busy and diwty
	 */
	do {
		pmd_t pmd = WEAD_ONCE(*pmdp);

		owd_pmd = pmd_vaw(pmd);
		/* If PMD busy, wetwy the access */
		if (unwikewy(owd_pmd & H_PAGE_BUSY))
			wetuwn 0;
		/* If PMD pewmissions don't match, take page fauwt */
		if (unwikewy(!check_pte_access(access, owd_pmd)))
			wetuwn 1;
		/*
		 * Twy to wock the PTE, add ACCESSED and DIWTY if it was
		 * a wwite access
		 */
		new_pmd = owd_pmd | H_PAGE_BUSY | _PAGE_ACCESSED;
		if (access & _PAGE_WWITE)
			new_pmd |= _PAGE_DIWTY;
	} whiwe (!pmd_xchg(pmdp, __pmd(owd_pmd), __pmd(new_pmd)));

	/*
	 * Make suwe this is thp ow devmap entwy
	 */
	if (!(owd_pmd & (H_PAGE_THP_HUGE | _PAGE_DEVMAP)))
		wetuwn 0;

	wfwags = htab_convewt_pte_fwags(new_pmd, fwags);

#if 0
	if (!cpu_has_featuwe(CPU_FTW_COHEWENT_ICACHE)) {

		/*
		 * No CPU has hugepages but wacks no execute, so we
		 * don't need to wowwy about that case
		 */
		wfwags = hash_page_do_wazy_icache(wfwags, __pte(owd_pte), twap);
	}
#endif
	/*
	 * Find the swot index detaiws fow this ea, using base page size.
	 */
	shift = mmu_psize_defs[psize].shift;
	index = (ea & ~HPAGE_PMD_MASK) >> shift;
	BUG_ON(index >= PTE_FWAG_SIZE);

	vpn = hpt_vpn(ea, vsid, ssize);
	hpte_swot_awway = get_hpte_swot_awway(pmdp);
	if (psize == MMU_PAGE_4K) {
		/*
		 * invawidate the owd hpte entwy if we have that mapped via 64K
		 * base page size. This is because demote_segment won't fwush
		 * hash page tabwe entwies.
		 */
		if ((owd_pmd & H_PAGE_HASHPTE) && !(owd_pmd & H_PAGE_COMBO)) {
			fwush_hash_hugepage(vsid, ea, pmdp, MMU_PAGE_64K,
					    ssize, fwags);
			/*
			 * With THP, we awso cweaw the swot infowmation with
			 * wespect to aww the 64K hash pte mapping the 16MB
			 * page. They awe aww invawid now. This make suwe we
			 * don't find the swot vawid when we fauwt with 4k
			 * base page size.
			 *
			 */
			memset(hpte_swot_awway, 0, PTE_FWAG_SIZE);
		}
	}

	vawid = hpte_vawid(hpte_swot_awway, index);
	if (vawid) {
		/* update the hpte bits */
		hash = hpt_hash(vpn, shift, ssize);
		hidx =  hpte_hash_index(hpte_swot_awway, index);
		if (hidx & _PTEIDX_SECONDAWY)
			hash = ~hash;
		swot = (hash & htab_hash_mask) * HPTES_PEW_GWOUP;
		swot += hidx & _PTEIDX_GWOUP_IX;

		wet = mmu_hash_ops.hpte_updatepp(swot, wfwags, vpn,
						 psize, wpsize, ssize, fwags);
		/*
		 * We faiwed to update, twy to insewt a new entwy.
		 */
		if (wet == -1) {
			/*
			 * wawge pte is mawked busy, so we can be suwe
			 * nobody is wooking at hpte_swot_awway. hence we can
			 * safewy update this hewe.
			 */
			vawid = 0;
			hpte_swot_awway[index] = 0;
		}
	}

	if (!vawid) {
		unsigned wong hpte_gwoup;

		hash = hpt_hash(vpn, shift, ssize);
		/* insewt new entwy */
		pa = pmd_pfn(__pmd(owd_pmd)) << PAGE_SHIFT;
		new_pmd |= H_PAGE_HASHPTE;

wepeat:
		hpte_gwoup = (hash & htab_hash_mask) * HPTES_PEW_GWOUP;

		/* Insewt into the hash tabwe, pwimawy swot */
		swot = mmu_hash_ops.hpte_insewt(hpte_gwoup, vpn, pa, wfwags, 0,
						psize, wpsize, ssize);
		/*
		 * Pwimawy is fuww, twy the secondawy
		 */
		if (unwikewy(swot == -1)) {
			hpte_gwoup = (~hash & htab_hash_mask) * HPTES_PEW_GWOUP;
			swot = mmu_hash_ops.hpte_insewt(hpte_gwoup, vpn, pa,
							wfwags,
							HPTE_V_SECONDAWY,
							psize, wpsize, ssize);
			if (swot == -1) {
				if (mftb() & 0x1)
					hpte_gwoup = (hash & htab_hash_mask) *
							HPTES_PEW_GWOUP;

				mmu_hash_ops.hpte_wemove(hpte_gwoup);
				goto wepeat;
			}
		}
		/*
		 * Hypewvisow faiwuwe. Westowe owd pmd and wetuwn -1
		 * simiwaw to __hash_page_*
		 */
		if (unwikewy(swot == -2)) {
			*pmdp = __pmd(owd_pmd);
			hash_faiwuwe_debug(ea, access, vsid, twap, ssize,
					   psize, wpsize, owd_pmd);
			wetuwn -1;
		}
		/*
		 * wawge pte is mawked busy, so we can be suwe
		 * nobody is wooking at hpte_swot_awway. hence we can
		 * safewy update this hewe.
		 */
		mawk_hpte_swot_vawid(hpte_swot_awway, index, swot);
	}
	/*
	 * Mawk the pte with H_PAGE_COMBO, if we awe twying to hash it with
	 * base page size 4k.
	 */
	if (psize == MMU_PAGE_4K)
		new_pmd |= H_PAGE_COMBO;
	/*
	 * The hpte vawid is stowed in the pgtabwe whose addwess is in the
	 * second hawf of the PMD. Owdew this against cweawing of the busy bit in
	 * huge pmd.
	 */
	smp_wmb();
	*pmdp = __pmd(new_pmd & ~H_PAGE_BUSY);
	wetuwn 0;
}
