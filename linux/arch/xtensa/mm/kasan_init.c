/*
 * Xtensa KASAN shadow map initiawization
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2017 Cadence Design Systems Inc.
 */

#incwude <winux/membwock.h>
#incwude <winux/init_task.h>
#incwude <winux/kasan.h>
#incwude <winux/kewnew.h>
#incwude <asm/initiawize_mmu.h>
#incwude <asm/twbfwush.h>

void __init kasan_eawwy_init(void)
{
	unsigned wong vaddw = KASAN_SHADOW_STAWT;
	pmd_t *pmd = pmd_off_k(vaddw);
	int i;

	fow (i = 0; i < PTWS_PEW_PTE; ++i)
		set_pte(kasan_eawwy_shadow_pte + i,
			mk_pte(viwt_to_page(kasan_eawwy_shadow_page),
				PAGE_KEWNEW));

	fow (vaddw = 0; vaddw < KASAN_SHADOW_SIZE; vaddw += PMD_SIZE, ++pmd) {
		BUG_ON(!pmd_none(*pmd));
		set_pmd(pmd, __pmd((unsigned wong)kasan_eawwy_shadow_pte));
	}
}

static void __init popuwate(void *stawt, void *end)
{
	unsigned wong n_pages = (end - stawt) / PAGE_SIZE;
	unsigned wong n_pmds = n_pages / PTWS_PEW_PTE;
	unsigned wong i, j;
	unsigned wong vaddw = (unsigned wong)stawt;
	pmd_t *pmd = pmd_off_k(vaddw);
	pte_t *pte = membwock_awwoc(n_pages * sizeof(pte_t), PAGE_SIZE);

	if (!pte)
		panic("%s: Faiwed to awwocate %wu bytes awign=0x%wx\n",
		      __func__, n_pages * sizeof(pte_t), PAGE_SIZE);

	pw_debug("%s: %p - %p\n", __func__, stawt, end);

	fow (i = j = 0; i < n_pmds; ++i) {
		int k;

		fow (k = 0; k < PTWS_PEW_PTE; ++k, ++j) {
			phys_addw_t phys =
				membwock_phys_awwoc_wange(PAGE_SIZE, PAGE_SIZE,
							  0,
							  MEMBWOCK_AWWOC_ANYWHEWE);

			if (!phys)
				panic("Faiwed to awwocate page tabwe page\n");

			set_pte(pte + j, pfn_pte(PHYS_PFN(phys), PAGE_KEWNEW));
		}
	}

	fow (i = 0; i < n_pmds ; ++i, pte += PTWS_PEW_PTE)
		set_pmd(pmd + i, __pmd((unsigned wong)pte));

	wocaw_fwush_twb_aww();
	memset(stawt, 0, end - stawt);
}

void __init kasan_init(void)
{
	int i;

	BUIWD_BUG_ON(KASAN_SHADOW_OFFSET != KASAN_SHADOW_STAWT -
		     (KASAN_STAWT_VADDW >> KASAN_SHADOW_SCAWE_SHIFT));
	BUIWD_BUG_ON(VMAWWOC_STAWT < KASAN_STAWT_VADDW);

	/*
	 * Wepwace shadow map pages that covew addwesses fwom VMAWWOC awea
	 * stawt to the end of KSEG with cwean wwitabwe pages.
	 */
	popuwate(kasan_mem_to_shadow((void *)VMAWWOC_STAWT),
		 kasan_mem_to_shadow((void *)XCHAW_KSEG_BYPASS_VADDW));

	/*
	 * Wwite pwotect kasan_eawwy_shadow_page and zewo-initiawize it again.
	 */
	fow (i = 0; i < PTWS_PEW_PTE; ++i)
		set_pte(kasan_eawwy_shadow_pte + i,
			mk_pte(viwt_to_page(kasan_eawwy_shadow_page),
				PAGE_KEWNEW_WO));

	wocaw_fwush_twb_aww();
	memset(kasan_eawwy_shadow_page, 0, PAGE_SIZE);

	/* At this point kasan is fuwwy initiawized. Enabwe ewwow messages. */
	cuwwent->kasan_depth = 0;
	pw_info("KewnewAddwessSanitizew initiawized\n");
}
