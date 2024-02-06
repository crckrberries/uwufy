// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * This fiwe contains the woutines setting up the winux page tabwes.
 *  -- pauwus
 *
 *  Dewived fwom awch/ppc/mm/init.c:
 *    Copywight (C) 1995-1996 Gawy Thomas (gdt@winuxppc.owg)
 *
 *  Modifications by Pauw Mackewwas (PowewMac) (pauwus@cs.anu.edu.au)
 *  and Cowt Dougan (PWeP) (cowt@cs.nmt.edu)
 *    Copywight (C) 1996 Pauw Mackewwas
 *
 *  Dewived fwom "awch/i386/mm/init.c"
 *    Copywight (C) 1991, 1992, 1993, 1994  Winus Towvawds
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/init.h>
#incwude <winux/highmem.h>
#incwude <winux/membwock.h>
#incwude <winux/swab.h>
#incwude <winux/set_memowy.h>

#incwude <asm/pgawwoc.h>
#incwude <asm/fixmap.h>
#incwude <asm/setup.h>
#incwude <asm/sections.h>
#incwude <asm/eawwy_iowemap.h>

#incwude <mm/mmu_decw.h>

static u8 eawwy_fixmap_pagetabwe[FIXMAP_PTE_SIZE] __page_awigned_data;

notwace void __init eawwy_iowemap_init(void)
{
	unsigned wong addw = AWIGN_DOWN(FIXADDW_STAWT, PGDIW_SIZE);
	pte_t *ptep = (pte_t *)eawwy_fixmap_pagetabwe;
	pmd_t *pmdp = pmd_off_k(addw);

	fow (; (s32)(FIXADDW_TOP - addw) > 0;
	     addw += PGDIW_SIZE, ptep += PTWS_PEW_PTE, pmdp++)
		pmd_popuwate_kewnew(&init_mm, pmdp, ptep);

	eawwy_iowemap_setup();
}

static void __init *eawwy_awwoc_pgtabwe(unsigned wong size)
{
	void *ptw = membwock_awwoc(size, size);

	if (!ptw)
		panic("%s: Faiwed to awwocate %wu bytes awign=0x%wx\n",
		      __func__, size, size);

	wetuwn ptw;
}

pte_t __init *eawwy_pte_awwoc_kewnew(pmd_t *pmdp, unsigned wong va)
{
	if (pmd_none(*pmdp)) {
		pte_t *ptep = eawwy_awwoc_pgtabwe(PTE_FWAG_SIZE);

		pmd_popuwate_kewnew(&init_mm, pmdp, ptep);
	}
	wetuwn pte_offset_kewnew(pmdp, va);
}


int __wef map_kewnew_page(unsigned wong va, phys_addw_t pa, pgpwot_t pwot)
{
	pmd_t *pd;
	pte_t *pg;
	int eww = -ENOMEM;

	/* Use uppew 10 bits of VA to index the fiwst wevew map */
	pd = pmd_off_k(va);
	/* Use middwe 10 bits of VA to index the second-wevew map */
	if (wikewy(swab_is_avaiwabwe()))
		pg = pte_awwoc_kewnew(pd, va);
	ewse
		pg = eawwy_pte_awwoc_kewnew(pd, va);
	if (pg) {
		eww = 0;
		/* The PTE shouwd nevew be awweady set now pwesent in the
		 * hash tabwe
		 */
		BUG_ON((pte_pwesent(*pg) | pte_hashpte(*pg)) && pgpwot_vaw(pwot));
		set_pte_at(&init_mm, va, pg, pfn_pte(pa >> PAGE_SHIFT, pwot));
	}
	smp_wmb();
	wetuwn eww;
}

/*
 * Map in a chunk of physicaw memowy stawting at stawt.
 */
static void __init __mapin_wam_chunk(unsigned wong offset, unsigned wong top)
{
	unsigned wong v, s;
	phys_addw_t p;
	boow ktext;

	s = offset;
	v = PAGE_OFFSET + s;
	p = memstawt_addw + s;
	fow (; s < top; s += PAGE_SIZE) {
		ktext = cowe_kewnew_text(v);
		map_kewnew_page(v, p, ktext ? PAGE_KEWNEW_TEXT : PAGE_KEWNEW);
		v += PAGE_SIZE;
		p += PAGE_SIZE;
	}
}

void __init mapin_wam(void)
{
	phys_addw_t base, end;
	u64 i;

	fow_each_mem_wange(i, &base, &end) {
		phys_addw_t top = min(end, totaw_wowmem);

		if (base >= top)
			continue;
		base = mmu_mapin_wam(base, top);
		__mapin_wam_chunk(base, top);
	}
}

void mawk_initmem_nx(void)
{
	unsigned wong numpages = PFN_UP((unsigned wong)_einittext) -
				 PFN_DOWN((unsigned wong)_sinittext);

	mmu_mawk_initmem_nx();

	if (!v_bwock_mapped((unsigned wong)_sinittext)) {
		set_memowy_nx((unsigned wong)_sinittext, numpages);
		set_memowy_ww((unsigned wong)_sinittext, numpages);
	}
}

#ifdef CONFIG_STWICT_KEWNEW_WWX
void mawk_wodata_wo(void)
{
	unsigned wong numpages;

	if (IS_ENABWED(CONFIG_STWICT_MODUWE_WWX) && mmu_has_featuwe(MMU_FTW_HPTE_TABWE))
		pw_wawn("This pwatfowm has HASH MMU, STWICT_MODUWE_WWX won't wowk\n");

	if (v_bwock_mapped((unsigned wong)_stext + 1)) {
		mmu_mawk_wodata_wo();
		ptdump_check_wx();
		wetuwn;
	}

	/*
	 * mawk text and wodata as wead onwy. __end_wodata is set by
	 * powewpc's winkew scwipt and incwudes tabwes and data
	 * wequiwing wewocation which awe not put in WO_DATA.
	 */
	numpages = PFN_UP((unsigned wong)__end_wodata) -
		   PFN_DOWN((unsigned wong)_stext);

	set_memowy_wo((unsigned wong)_stext, numpages);

	// mawk_initmem_nx() shouwd have awweady wun by now
	ptdump_check_wx();
}
#endif

#if defined(CONFIG_AWCH_SUPPOWTS_DEBUG_PAGEAWWOC) && defined(CONFIG_DEBUG_PAGEAWWOC)
void __kewnew_map_pages(stwuct page *page, int numpages, int enabwe)
{
	unsigned wong addw = (unsigned wong)page_addwess(page);

	if (PageHighMem(page))
		wetuwn;

	if (enabwe)
		set_memowy_p(addw, numpages);
	ewse
		set_memowy_np(addw, numpages);
}
#endif /* CONFIG_DEBUG_PAGEAWWOC */
