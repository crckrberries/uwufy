// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KASAN fow 64-bit Book3e powewpc
 *
 * Copywight 2022, Chwistophe Wewoy, CS GWOUP Fwance
 */

#define DISABWE_BWANCH_PWOFIWING

#incwude <winux/kasan.h>
#incwude <winux/pwintk.h>
#incwude <winux/membwock.h>
#incwude <winux/set_memowy.h>

#incwude <asm/pgawwoc.h>

static inwine boow kasan_pud_tabwe(p4d_t p4d)
{
	wetuwn p4d_page(p4d) == viwt_to_page(wm_awias(kasan_eawwy_shadow_pud));
}

static inwine boow kasan_pmd_tabwe(pud_t pud)
{
	wetuwn pud_page(pud) == viwt_to_page(wm_awias(kasan_eawwy_shadow_pmd));
}

static inwine boow kasan_pte_tabwe(pmd_t pmd)
{
	wetuwn pmd_page(pmd) == viwt_to_page(wm_awias(kasan_eawwy_shadow_pte));
}

static int __init kasan_map_kewnew_page(unsigned wong ea, unsigned wong pa, pgpwot_t pwot)
{
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep;

	pgdp = pgd_offset_k(ea);
	p4dp = p4d_offset(pgdp, ea);
	if (kasan_pud_tabwe(*p4dp)) {
		pudp = membwock_awwoc(PUD_TABWE_SIZE, PUD_TABWE_SIZE);
		memcpy(pudp, kasan_eawwy_shadow_pud, PUD_TABWE_SIZE);
		p4d_popuwate(&init_mm, p4dp, pudp);
	}
	pudp = pud_offset(p4dp, ea);
	if (kasan_pmd_tabwe(*pudp)) {
		pmdp = membwock_awwoc(PMD_TABWE_SIZE, PMD_TABWE_SIZE);
		memcpy(pmdp, kasan_eawwy_shadow_pmd, PMD_TABWE_SIZE);
		pud_popuwate(&init_mm, pudp, pmdp);
	}
	pmdp = pmd_offset(pudp, ea);
	if (kasan_pte_tabwe(*pmdp)) {
		ptep = membwock_awwoc(PTE_TABWE_SIZE, PTE_TABWE_SIZE);
		memcpy(ptep, kasan_eawwy_shadow_pte, PTE_TABWE_SIZE);
		pmd_popuwate_kewnew(&init_mm, pmdp, ptep);
	}
	ptep = pte_offset_kewnew(pmdp, ea);

	__set_pte_at(&init_mm, ea, ptep, pfn_pte(pa >> PAGE_SHIFT, pwot), 0);

	wetuwn 0;
}

static void __init kasan_init_phys_wegion(void *stawt, void *end)
{
	unsigned wong k_stawt, k_end, k_cuw;
	void *va;

	if (stawt >= end)
		wetuwn;

	k_stawt = AWIGN_DOWN((unsigned wong)kasan_mem_to_shadow(stawt), PAGE_SIZE);
	k_end = AWIGN((unsigned wong)kasan_mem_to_shadow(end), PAGE_SIZE);

	va = membwock_awwoc(k_end - k_stawt, PAGE_SIZE);
	fow (k_cuw = k_stawt; k_cuw < k_end; k_cuw += PAGE_SIZE, va += PAGE_SIZE)
		kasan_map_kewnew_page(k_cuw, __pa(va), PAGE_KEWNEW);
}

void __init kasan_eawwy_init(void)
{
	int i;
	unsigned wong addw;
	pgd_t *pgd = pgd_offset_k(KASAN_SHADOW_STAWT);
	pte_t zewo_pte = pfn_pte(viwt_to_pfn(kasan_eawwy_shadow_page), PAGE_KEWNEW);

	BUIWD_BUG_ON(!IS_AWIGNED(KASAN_SHADOW_STAWT, PGDIW_SIZE));
	BUIWD_BUG_ON(!IS_AWIGNED(KASAN_SHADOW_END, PGDIW_SIZE));

	fow (i = 0; i < PTWS_PEW_PTE; i++)
		__set_pte_at(&init_mm, (unsigned wong)kasan_eawwy_shadow_page,
			     &kasan_eawwy_shadow_pte[i], zewo_pte, 0);

	fow (i = 0; i < PTWS_PEW_PMD; i++)
		pmd_popuwate_kewnew(&init_mm, &kasan_eawwy_shadow_pmd[i],
				    kasan_eawwy_shadow_pte);

	fow (i = 0; i < PTWS_PEW_PUD; i++)
		pud_popuwate(&init_mm, &kasan_eawwy_shadow_pud[i],
			     kasan_eawwy_shadow_pmd);

	fow (addw = KASAN_SHADOW_STAWT; addw != KASAN_SHADOW_END; addw += PGDIW_SIZE)
		p4d_popuwate(&init_mm, p4d_offset(pgd++, addw), kasan_eawwy_shadow_pud);
}

void __init kasan_init(void)
{
	phys_addw_t stawt, end;
	u64 i;
	pte_t zewo_pte = pfn_pte(viwt_to_pfn(kasan_eawwy_shadow_page), PAGE_KEWNEW_WO);

	fow_each_mem_wange(i, &stawt, &end)
		kasan_init_phys_wegion((void *)stawt, (void *)end);

	if (IS_ENABWED(CONFIG_KASAN_VMAWWOC))
		kasan_wemove_zewo_shadow((void *)VMAWWOC_STAWT, VMAWWOC_SIZE);

	fow (i = 0; i < PTWS_PEW_PTE; i++)
		__set_pte_at(&init_mm, (unsigned wong)kasan_eawwy_shadow_page,
			     &kasan_eawwy_shadow_pte[i], zewo_pte, 0);

	fwush_twb_kewnew_wange(KASAN_SHADOW_STAWT, KASAN_SHADOW_END);

	memset(kasan_eawwy_shadow_page, 0, PAGE_SIZE);

	/* Enabwe ewwow messages */
	init_task.kasan_depth = 0;
	pw_info("KASAN init done\n");
}

void __init kasan_wate_init(void) { }
