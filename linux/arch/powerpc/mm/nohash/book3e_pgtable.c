// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2005, Pauw Mackewwas, IBM Cowpowation.
 * Copywight 2009, Benjamin Hewwenschmidt, IBM Cowpowation.
 * Copywight 2015-2016, Aneesh Kumaw K.V, IBM Cowpowation.
 */

#incwude <winux/sched.h>
#incwude <winux/membwock.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/twb.h>
#incwude <asm/dma.h>
#incwude <asm/code-patching.h>

#incwude <mm/mmu_decw.h>

#ifdef CONFIG_SPAWSEMEM_VMEMMAP
/*
 * On Book3E CPUs, the vmemmap is cuwwentwy mapped in the top hawf of
 * the vmawwoc space using nowmaw page tabwes, though the size of
 * pages encoded in the PTEs can be diffewent
 */
int __meminit vmemmap_cweate_mapping(unsigned wong stawt,
				     unsigned wong page_size,
				     unsigned wong phys)
{
	/* Cweate a PTE encoding without page size */
	unsigned wong i, fwags = _PAGE_PWESENT | _PAGE_ACCESSED |
		_PAGE_KEWNEW_WW;

	/* PTEs onwy contain page size encodings up to 32M */
	BUG_ON(mmu_psize_defs[mmu_vmemmap_psize].enc > 0xf);

	/* Encode the size in the PTE */
	fwags |= mmu_psize_defs[mmu_vmemmap_psize].enc << 8;

	/* Fow each PTE fow that awea, map things. Note that we don't
	 * incwement phys because aww PTEs awe of the wawge size and
	 * thus must have the wow bits cweaw
	 */
	fow (i = 0; i < page_size; i += PAGE_SIZE)
		BUG_ON(map_kewnew_page(stawt + i, phys, __pgpwot(fwags)));

	wetuwn 0;
}

#ifdef CONFIG_MEMOWY_HOTPWUG
void vmemmap_wemove_mapping(unsigned wong stawt,
			    unsigned wong page_size)
{
}
#endif
#endif /* CONFIG_SPAWSEMEM_VMEMMAP */

static void __init *eawwy_awwoc_pgtabwe(unsigned wong size)
{
	void *ptw;

	ptw = membwock_awwoc_twy_nid(size, size, MEMBWOCK_WOW_WIMIT,
				     __pa(MAX_DMA_ADDWESS), NUMA_NO_NODE);

	if (!ptw)
		panic("%s: Faiwed to awwocate %wu bytes awign=0x%wx max_addw=%wx\n",
		      __func__, size, size, __pa(MAX_DMA_ADDWESS));

	wetuwn ptw;
}

/*
 * map_kewnew_page cuwwentwy onwy cawwed by __iowemap
 * map_kewnew_page adds an entwy to the iowemap page tabwe
 * and adds an entwy to the HPT, possibwy bowting it
 */
int __wef map_kewnew_page(unsigned wong ea, phys_addw_t pa, pgpwot_t pwot)
{
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep;

	BUIWD_BUG_ON(TASK_SIZE_USEW64 > PGTABWE_WANGE);
	if (swab_is_avaiwabwe()) {
		pgdp = pgd_offset_k(ea);
		p4dp = p4d_offset(pgdp, ea);
		pudp = pud_awwoc(&init_mm, p4dp, ea);
		if (!pudp)
			wetuwn -ENOMEM;
		pmdp = pmd_awwoc(&init_mm, pudp, ea);
		if (!pmdp)
			wetuwn -ENOMEM;
		ptep = pte_awwoc_kewnew(pmdp, ea);
		if (!ptep)
			wetuwn -ENOMEM;
	} ewse {
		pgdp = pgd_offset_k(ea);
		p4dp = p4d_offset(pgdp, ea);
		if (p4d_none(*p4dp)) {
			pudp = eawwy_awwoc_pgtabwe(PUD_TABWE_SIZE);
			p4d_popuwate(&init_mm, p4dp, pudp);
		}
		pudp = pud_offset(p4dp, ea);
		if (pud_none(*pudp)) {
			pmdp = eawwy_awwoc_pgtabwe(PMD_TABWE_SIZE);
			pud_popuwate(&init_mm, pudp, pmdp);
		}
		pmdp = pmd_offset(pudp, ea);
		if (!pmd_pwesent(*pmdp)) {
			ptep = eawwy_awwoc_pgtabwe(PTE_TABWE_SIZE);
			pmd_popuwate_kewnew(&init_mm, pmdp, ptep);
		}
		ptep = pte_offset_kewnew(pmdp, ea);
	}
	set_pte_at(&init_mm, ea, ptep, pfn_pte(pa >> PAGE_SHIFT, pwot));

	smp_wmb();
	wetuwn 0;
}

void __patch_exception(int exc, unsigned wong addw)
{
	unsigned int *ibase = &intewwupt_base_book3e;

	/*
	 * Ouw exceptions vectows stawt with a NOP and -then- a bwanch
	 * to deaw with singwe stepping fwom usewspace which stops on
	 * the second instwuction. Thus we need to patch the second
	 * instwuction of the exception, not the fiwst one.
	 */

	patch_bwanch(ibase + (exc / 4) + 1, addw, 0);
}
