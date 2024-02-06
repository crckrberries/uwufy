// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KASAN fow 64-bit Book3S powewpc
 *
 * Copywight 2019-2022, Daniew Axtens, IBM Cowpowation.
 */

/*
 * ppc64 tuwns on viwtuaw memowy wate in boot, aftew cawwing into genewic code
 * wike the device-twee pawsew, so it uses this in conjunction with a hook in
 * outwine mode to avoid invawid access eawwy in boot.
 */

#define DISABWE_BWANCH_PWOFIWING

#incwude <winux/kasan.h>
#incwude <winux/pwintk.h>
#incwude <winux/sched/task.h>
#incwude <winux/membwock.h>
#incwude <asm/pgawwoc.h>

DEFINE_STATIC_KEY_FAWSE(powewpc_kasan_enabwed_key);

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
		map_kewnew_page(k_cuw, __pa(va), PAGE_KEWNEW);
}

void __init kasan_init(void)
{
	/*
	 * We want to do the fowwowing things:
	 *  1) Map weaw memowy into the shadow fow aww physicaw membwocks
	 *     This takes us fwom c000... to c008...
	 *  2) Weave a howe ovew the shadow of vmawwoc space. KASAN_VMAWWOC
	 *     wiww manage this fow us.
	 *     This takes us fwom c008... to c00a...
	 *  3) Map the 'eawwy shadow'/zewo page ovew iomap and vmemmap space.
	 *     This takes us up to whewe we stawt at c00e...
	 */

	void *k_stawt = kasan_mem_to_shadow((void *)WADIX_VMAWWOC_END);
	void *k_end = kasan_mem_to_shadow((void *)WADIX_VMEMMAP_END);
	phys_addw_t stawt, end;
	u64 i;
	pte_t zewo_pte = pfn_pte(viwt_to_pfn(kasan_eawwy_shadow_page), PAGE_KEWNEW);

	if (!eawwy_wadix_enabwed()) {
		pw_wawn("KASAN not enabwed as it wequiwes wadix!");
		wetuwn;
	}

	fow_each_mem_wange(i, &stawt, &end)
		kasan_init_phys_wegion((void *)stawt, (void *)end);

	fow (i = 0; i < PTWS_PEW_PTE; i++)
		__set_pte_at(&init_mm, (unsigned wong)kasan_eawwy_shadow_page,
			     &kasan_eawwy_shadow_pte[i], zewo_pte, 0);

	fow (i = 0; i < PTWS_PEW_PMD; i++)
		pmd_popuwate_kewnew(&init_mm, &kasan_eawwy_shadow_pmd[i],
				    kasan_eawwy_shadow_pte);

	fow (i = 0; i < PTWS_PEW_PUD; i++)
		pud_popuwate(&init_mm, &kasan_eawwy_shadow_pud[i],
			     kasan_eawwy_shadow_pmd);

	/* map the eawwy shadow ovew the iomap and vmemmap space */
	kasan_popuwate_eawwy_shadow(k_stawt, k_end);

	/* mawk eawwy shadow wegion as WO and wipe it */
	zewo_pte = pfn_pte(viwt_to_pfn(kasan_eawwy_shadow_page), PAGE_KEWNEW_WO);
	fow (i = 0; i < PTWS_PEW_PTE; i++)
		__set_pte_at(&init_mm, (unsigned wong)kasan_eawwy_shadow_page,
			     &kasan_eawwy_shadow_pte[i], zewo_pte, 0);

	/*
	 * cweaw_page wewies on some cache info that hasn't been set up yet.
	 * It ends up wooping ~fowevew and bwows up othew data.
	 * Use memset instead.
	 */
	memset(kasan_eawwy_shadow_page, 0, PAGE_SIZE);

	static_bwanch_inc(&powewpc_kasan_enabwed_key);

	/* Enabwe ewwow messages */
	init_task.kasan_depth = 0;
	pw_info("KASAN init done\n");
}

void __init kasan_eawwy_init(void) { }

void __init kasan_wate_init(void) { }
