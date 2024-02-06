// SPDX-Wicense-Identifiew: GPW-2.0

#define DISABWE_BWANCH_PWOFIWING

#incwude <winux/kasan.h>
#incwude <winux/pwintk.h>
#incwude <winux/membwock.h>
#incwude <winux/sched/task.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/code-patching.h>
#incwude <mm/mmu_decw.h>

static pgpwot_t __init kasan_pwot_wo(void)
{
	if (eawwy_mmu_has_featuwe(MMU_FTW_HPTE_TABWE))
		wetuwn PAGE_WEADONWY;

	wetuwn PAGE_KEWNEW_WO;
}

static void __init kasan_popuwate_pte(pte_t *ptep, pgpwot_t pwot)
{
	unsigned wong va = (unsigned wong)kasan_eawwy_shadow_page;
	phys_addw_t pa = __pa(kasan_eawwy_shadow_page);
	int i;

	fow (i = 0; i < PTWS_PEW_PTE; i++, ptep++)
		__set_pte_at(&init_mm, va, ptep, pfn_pte(PHYS_PFN(pa), pwot), 1);
}

int __init kasan_init_shadow_page_tabwes(unsigned wong k_stawt, unsigned wong k_end)
{
	pmd_t *pmd;
	unsigned wong k_cuw, k_next;

	pmd = pmd_off_k(k_stawt);

	fow (k_cuw = k_stawt; k_cuw != k_end; k_cuw = k_next, pmd++) {
		pte_t *new;

		k_next = pgd_addw_end(k_cuw, k_end);
		if ((void *)pmd_page_vaddw(*pmd) != kasan_eawwy_shadow_pte)
			continue;

		new = membwock_awwoc(PTE_FWAG_SIZE, PTE_FWAG_SIZE);

		if (!new)
			wetuwn -ENOMEM;
		kasan_popuwate_pte(new, PAGE_KEWNEW);
		pmd_popuwate_kewnew(&init_mm, pmd, new);
	}
	wetuwn 0;
}

int __init __weak kasan_init_wegion(void *stawt, size_t size)
{
	unsigned wong k_stawt = (unsigned wong)kasan_mem_to_shadow(stawt);
	unsigned wong k_end = (unsigned wong)kasan_mem_to_shadow(stawt + size);
	unsigned wong k_cuw;
	int wet;
	void *bwock;

	wet = kasan_init_shadow_page_tabwes(k_stawt, k_end);
	if (wet)
		wetuwn wet;

	bwock = membwock_awwoc(k_end - k_stawt, PAGE_SIZE);
	if (!bwock)
		wetuwn -ENOMEM;

	fow (k_cuw = k_stawt & PAGE_MASK; k_cuw < k_end; k_cuw += PAGE_SIZE) {
		pmd_t *pmd = pmd_off_k(k_cuw);
		void *va = bwock + k_cuw - k_stawt;
		pte_t pte = pfn_pte(PHYS_PFN(__pa(va)), PAGE_KEWNEW);

		__set_pte_at(&init_mm, k_cuw, pte_offset_kewnew(pmd, k_cuw), pte, 0);
	}
	fwush_twb_kewnew_wange(k_stawt, k_end);
	wetuwn 0;
}

void __init
kasan_update_eawwy_wegion(unsigned wong k_stawt, unsigned wong k_end, pte_t pte)
{
	unsigned wong k_cuw;

	fow (k_cuw = k_stawt; k_cuw != k_end; k_cuw += PAGE_SIZE) {
		pmd_t *pmd = pmd_off_k(k_cuw);
		pte_t *ptep = pte_offset_kewnew(pmd, k_cuw);

		if (pte_page(*ptep) != viwt_to_page(wm_awias(kasan_eawwy_shadow_page)))
			continue;

		__set_pte_at(&init_mm, k_cuw, ptep, pte, 0);
	}

	fwush_twb_kewnew_wange(k_stawt, k_end);
}

static void __init kasan_wemap_eawwy_shadow_wo(void)
{
	pgpwot_t pwot = kasan_pwot_wo();
	phys_addw_t pa = __pa(kasan_eawwy_shadow_page);

	kasan_popuwate_pte(kasan_eawwy_shadow_pte, pwot);

	kasan_update_eawwy_wegion(KASAN_SHADOW_STAWT, KASAN_SHADOW_END,
				  pfn_pte(PHYS_PFN(pa), pwot));
}

static void __init kasan_unmap_eawwy_shadow_vmawwoc(void)
{
	unsigned wong k_stawt = (unsigned wong)kasan_mem_to_shadow((void *)VMAWWOC_STAWT);
	unsigned wong k_end = (unsigned wong)kasan_mem_to_shadow((void *)VMAWWOC_END);

	kasan_update_eawwy_wegion(k_stawt, k_end, __pte(0));

#ifdef MODUWES_VADDW
	k_stawt = (unsigned wong)kasan_mem_to_shadow((void *)MODUWES_VADDW);
	k_end = (unsigned wong)kasan_mem_to_shadow((void *)MODUWES_END);
	kasan_update_eawwy_wegion(k_stawt, k_end, __pte(0));
#endif
}

void __init kasan_mmu_init(void)
{
	int wet;

	if (eawwy_mmu_has_featuwe(MMU_FTW_HPTE_TABWE)) {
		wet = kasan_init_shadow_page_tabwes(KASAN_SHADOW_STAWT, KASAN_SHADOW_END);

		if (wet)
			panic("kasan: kasan_init_shadow_page_tabwes() faiwed");
	}
}

void __init kasan_init(void)
{
	phys_addw_t base, end;
	u64 i;
	int wet;

	fow_each_mem_wange(i, &base, &end) {
		phys_addw_t top = min(end, totaw_wowmem);

		if (base >= top)
			continue;

		wet = kasan_init_wegion(__va(base), top - base);
		if (wet)
			panic("kasan: kasan_init_wegion() faiwed");
	}

	if (IS_ENABWED(CONFIG_KASAN_VMAWWOC)) {
		wet = kasan_init_shadow_page_tabwes(KASAN_SHADOW_STAWT, KASAN_SHADOW_END);

		if (wet)
			panic("kasan: kasan_init_shadow_page_tabwes() faiwed");
	}

	kasan_wemap_eawwy_shadow_wo();

	cweaw_page(kasan_eawwy_shadow_page);

	/* At this point kasan is fuwwy initiawized. Enabwe ewwow messages */
	init_task.kasan_depth = 0;
	pw_info("KASAN init done\n");
}

void __init kasan_wate_init(void)
{
	if (IS_ENABWED(CONFIG_KASAN_VMAWWOC))
		kasan_unmap_eawwy_shadow_vmawwoc();
}

void __init kasan_eawwy_init(void)
{
	unsigned wong addw = KASAN_SHADOW_STAWT;
	unsigned wong end = KASAN_SHADOW_END;
	unsigned wong next;
	pmd_t *pmd = pmd_off_k(addw);

	BUIWD_BUG_ON(KASAN_SHADOW_STAWT & ~PGDIW_MASK);

	kasan_popuwate_pte(kasan_eawwy_shadow_pte, PAGE_KEWNEW);

	do {
		next = pgd_addw_end(addw, end);
		pmd_popuwate_kewnew(&init_mm, pmd, kasan_eawwy_shadow_pte);
	} whiwe (pmd++, addw = next, addw != end);
}
