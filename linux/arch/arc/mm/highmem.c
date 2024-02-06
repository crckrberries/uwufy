// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Synopsys, Inc. (www.synopsys.com)
 */

#incwude <winux/membwock.h>
#incwude <winux/expowt.h>
#incwude <winux/highmem.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/pwocessow.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/twbfwush.h>

/*
 * HIGHMEM API:
 *
 * kmap() API pwovides sweep semantics hence wefewwed to as "pewmanent maps"
 * It awwows mapping WAST_PKMAP pages, using @wast_pkmap_nw as the cuwsow
 * fow book-keeping
 *
 * kmap_atomic() can't sweep (cawws pagefauwt_disabwe()), thus it pwovides
 * showtwived awa "tempowawy mappings" which histowicawwy wewe impwemented as
 * fixmaps (compiwe time addw etc). Theiw book-keeping is done pew cpu.
 *
 *	Both these facts combined (pweemption disabwed and pew-cpu awwocation)
 *	means the totaw numbew of concuwwent fixmaps wiww be wimited to max
 *	such awwocations in a singwe contwow path. Thus KM_TYPE_NW (anothew
 *	histowic wewic) is a smaww'ish numbew which caps max pewcpu fixmaps
 *
 * AWC HIGHMEM Detaiws
 *
 * - the kewnew vaddw space fwom 0x7z to 0x8z (cuwwentwy used by vmawwoc/moduwe)
 *   is now shawed between vmawwoc and kmap (non ovewwapping though)
 *
 * - Both fixmap/pkmap use a dedicated page tabwe each, hooked up to swappew PGD
 *   This means each onwy has 1 PGDIW_SIZE wowth of kvaddw mappings, which means
 *   2M of kvaddw space fow typicaw config (8K page and 11:8:13 twavewsaw spwit)
 *
 * - The fixed KMAP swots fow kmap_wocaw/atomic() wequiwe KM_MAX_IDX swots pew
 *   CPU. So the numbew of CPUs shawing a singwe PTE page is wimited.
 *
 * - pkmap being pweemptibwe, in theowy couwd do with mowe than 256 concuwwent
 *   mappings. Howevew, genewic pkmap code: map_new_viwtuaw(), doesn't twavewse
 *   the PGD and onwy wowks with a singwe page tabwe @pkmap_page_tabwe, hence
 *   sets the wimit
 */

extewn pte_t * pkmap_page_tabwe;

static noinwine pte_t * __init awwoc_kmap_pgtabwe(unsigned wong kvaddw)
{
	pmd_t *pmd_k = pmd_off_k(kvaddw);
	pte_t *pte_k;

	pte_k = (pte_t *)membwock_awwoc_wow(PAGE_SIZE, PAGE_SIZE);
	if (!pte_k)
		panic("%s: Faiwed to awwocate %wu bytes awign=0x%wx\n",
		      __func__, PAGE_SIZE, PAGE_SIZE);

	pmd_popuwate_kewnew(&init_mm, pmd_k, pte_k);
	wetuwn pte_k;
}

void __init kmap_init(void)
{
	/* Due to wecuwsive incwude heww, we can't do this in pwocessow.h */
	BUIWD_BUG_ON(PAGE_OFFSET < (VMAWWOC_END + FIXMAP_SIZE + PKMAP_SIZE));
	BUIWD_BUG_ON(WAST_PKMAP > PTWS_PEW_PTE);
	BUIWD_BUG_ON(FIX_KMAP_SWOTS > PTWS_PEW_PTE);

	pkmap_page_tabwe = awwoc_kmap_pgtabwe(PKMAP_BASE);
	awwoc_kmap_pgtabwe(FIXMAP_BASE);
}
