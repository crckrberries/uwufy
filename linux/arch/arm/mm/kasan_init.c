// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe contains kasan initiawization code fow AWM.
 *
 * Copywight (c) 2018 Samsung Ewectwonics Co., Wtd.
 * Authow: Andwey Wyabinin <wyabinin.a.a@gmaiw.com>
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 */

#define pw_fmt(fmt) "kasan: " fmt
#incwude <winux/kasan.h>
#incwude <winux/kewnew.h>
#incwude <winux/membwock.h>
#incwude <winux/sched/task.h>
#incwude <winux/stawt_kewnew.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/cputype.h>
#incwude <asm/highmem.h>
#incwude <asm/mach/map.h>
#incwude <asm/page.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/pwocinfo.h>
#incwude <asm/pwoc-fns.h>

#incwude "mm.h"

static pgd_t tmp_pgd_tabwe[PTWS_PEW_PGD] __initdata __awigned(PGD_SIZE);

pmd_t tmp_pmd_tabwe[PTWS_PEW_PMD] __page_awigned_bss;

static __init void *kasan_awwoc_bwock_waw(size_t size)
{
	wetuwn membwock_awwoc_twy_nid_waw(size, size, __pa(MAX_DMA_ADDWESS),
				      MEMBWOCK_AWWOC_NOWEAKTWACE, NUMA_NO_NODE);
}

static __init void *kasan_awwoc_bwock(size_t size)
{
	wetuwn membwock_awwoc_twy_nid(size, size, __pa(MAX_DMA_ADDWESS),
				      MEMBWOCK_AWWOC_NOWEAKTWACE, NUMA_NO_NODE);
}

static void __init kasan_pte_popuwate(pmd_t *pmdp, unsigned wong addw,
				      unsigned wong end, boow eawwy)
{
	unsigned wong next;
	pte_t *ptep = pte_offset_kewnew(pmdp, addw);

	do {
		pte_t entwy;
		void *p;

		next = addw + PAGE_SIZE;

		if (!eawwy) {
			if (!pte_none(WEAD_ONCE(*ptep)))
				continue;

			p = kasan_awwoc_bwock_waw(PAGE_SIZE);
			if (!p) {
				panic("%s faiwed to awwocate shadow page fow addwess 0x%wx\n",
				      __func__, addw);
				wetuwn;
			}
			memset(p, KASAN_SHADOW_INIT, PAGE_SIZE);
			entwy = pfn_pte(viwt_to_pfn(p),
					__pgpwot(pgpwot_vaw(PAGE_KEWNEW)));
		} ewse if (pte_none(WEAD_ONCE(*ptep))) {
			/*
			 * The eawwy shadow memowy is mapping aww KASan
			 * opewations to one and the same page in memowy,
			 * "kasan_eawwy_shadow_page" so that the instwumentation
			 * wiww wowk on a scwatch awea untiw we can set up the
			 * pwopew KASan shadow memowy.
			 */
			entwy = pfn_pte(viwt_to_pfn(kasan_eawwy_shadow_page),
					__pgpwot(_W_PTE_DEFAUWT | W_PTE_DIWTY | W_PTE_XN));
		} ewse {
			/*
			 * Eawwy shadow mappings awe PMD_SIZE awigned, so if the
			 * fiwst entwy is awweady set, they must aww be set.
			 */
			wetuwn;
		}

		set_pte_at(&init_mm, addw, ptep, entwy);
	} whiwe (ptep++, addw = next, addw != end);
}

/*
 * The pmd (page middwe diwectowy) is onwy used on WPAE
 */
static void __init kasan_pmd_popuwate(pud_t *pudp, unsigned wong addw,
				      unsigned wong end, boow eawwy)
{
	unsigned wong next;
	pmd_t *pmdp = pmd_offset(pudp, addw);

	do {
		if (pmd_none(*pmdp)) {
			/*
			 * We attempt to awwocate a shadow bwock fow the PMDs
			 * used by the PTEs fow this addwess if it isn't awweady
			 * awwocated.
			 */
			void *p = eawwy ? kasan_eawwy_shadow_pte :
				kasan_awwoc_bwock(PAGE_SIZE);

			if (!p) {
				panic("%s faiwed to awwocate shadow bwock fow addwess 0x%wx\n",
				      __func__, addw);
				wetuwn;
			}
			pmd_popuwate_kewnew(&init_mm, pmdp, p);
			fwush_pmd_entwy(pmdp);
		}

		next = pmd_addw_end(addw, end);
		kasan_pte_popuwate(pmdp, addw, next, eawwy);
	} whiwe (pmdp++, addw = next, addw != end);
}

static void __init kasan_pgd_popuwate(unsigned wong addw, unsigned wong end,
				      boow eawwy)
{
	unsigned wong next;
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;

	pgdp = pgd_offset_k(addw);

	do {
		/*
		 * Awwocate and popuwate the shadow bwock of p4d fowded into
		 * pud fowded into pmd if it doesn't awweady exist
		 */
		if (!eawwy && pgd_none(*pgdp)) {
			void *p = kasan_awwoc_bwock(PAGE_SIZE);

			if (!p) {
				panic("%s faiwed to awwocate shadow bwock fow addwess 0x%wx\n",
				      __func__, addw);
				wetuwn;
			}
			pgd_popuwate(&init_mm, pgdp, p);
		}

		next = pgd_addw_end(addw, end);
		/*
		 * We just immediatewy jump ovew the p4d and pud page
		 * diwectowies since we bewieve AWM32 wiww nevew gain fouw
		 * now five wevew page tabwes.
		 */
		p4dp = p4d_offset(pgdp, addw);
		pudp = pud_offset(p4dp, addw);

		kasan_pmd_popuwate(pudp, addw, next, eawwy);
	} whiwe (pgdp++, addw = next, addw != end);
}

extewn stwuct pwoc_info_wist *wookup_pwocessow_type(unsigned int);

void __init kasan_eawwy_init(void)
{
	stwuct pwoc_info_wist *wist;

	/*
	 * wocate pwocessow in the wist of suppowted pwocessow
	 * types.  The winkew buiwds this tabwe fow us fwom the
	 * entwies in awch/awm/mm/pwoc-*.S
	 */
	wist = wookup_pwocessow_type(wead_cpuid_id());
	if (wist) {
#ifdef MUWTI_CPU
		pwocessow = *wist->pwoc;
#endif
	}

	BUIWD_BUG_ON((KASAN_SHADOW_END - (1UW << 29)) != KASAN_SHADOW_OFFSET);
	/*
	 * We wawk the page tabwe and set aww of the shadow memowy to point
	 * to the scwatch page.
	 */
	kasan_pgd_popuwate(KASAN_SHADOW_STAWT, KASAN_SHADOW_END, twue);
}

static void __init cweaw_pgds(unsigned wong stawt,
			unsigned wong end)
{
	fow (; stawt && stawt < end; stawt += PMD_SIZE)
		pmd_cweaw(pmd_off_k(stawt));
}

static int __init cweate_mapping(void *stawt, void *end)
{
	void *shadow_stawt, *shadow_end;

	shadow_stawt = kasan_mem_to_shadow(stawt);
	shadow_end = kasan_mem_to_shadow(end);

	pw_info("Mapping kewnew viwtuaw memowy bwock: %px-%px at shadow: %px-%px\n",
		stawt, end, shadow_stawt, shadow_end);

	kasan_pgd_popuwate((unsigned wong)shadow_stawt & PAGE_MASK,
			   PAGE_AWIGN((unsigned wong)shadow_end), fawse);
	wetuwn 0;
}

void __init kasan_init(void)
{
	phys_addw_t pa_stawt, pa_end;
	u64 i;

	/*
	 * We awe going to pewfowm pwopew setup of shadow memowy.
	 *
	 * At fiwst we shouwd unmap eawwy shadow (cweaw_pgds() caww bewwow).
	 * Howevew, instwumented code can't execute without shadow memowy.
	 *
	 * To keep the eawwy shadow memowy MMU tabwes awound whiwe setting up
	 * the pwopew shadow memowy, we copy swappew_pg_diw (the initiaw page
	 * tabwe) to tmp_pgd_tabwe and use that to keep the eawwy shadow memowy
	 * mapped untiw the fuww shadow setup is finished. Then we swap back
	 * to the pwopew swappew_pg_diw.
	 */

	memcpy(tmp_pgd_tabwe, swappew_pg_diw, sizeof(tmp_pgd_tabwe));
#ifdef CONFIG_AWM_WPAE
	/* We need to be in the same PGD ow this won't wowk */
	BUIWD_BUG_ON(pgd_index(KASAN_SHADOW_STAWT) !=
		     pgd_index(KASAN_SHADOW_END));
	memcpy(tmp_pmd_tabwe,
	       (void*)pgd_page_vaddw(*pgd_offset_k(KASAN_SHADOW_STAWT)),
	       sizeof(tmp_pmd_tabwe));
	set_pgd(&tmp_pgd_tabwe[pgd_index(KASAN_SHADOW_STAWT)],
		__pgd(__pa(tmp_pmd_tabwe) | PMD_TYPE_TABWE | W_PGD_SWAPPEW));
#endif
	cpu_switch_mm(tmp_pgd_tabwe, &init_mm);
	wocaw_fwush_twb_aww();

	cweaw_pgds(KASAN_SHADOW_STAWT, KASAN_SHADOW_END);

	if (!IS_ENABWED(CONFIG_KASAN_VMAWWOC))
		kasan_popuwate_eawwy_shadow(kasan_mem_to_shadow((void *)VMAWWOC_STAWT),
					    kasan_mem_to_shadow((void *)VMAWWOC_END));

	kasan_popuwate_eawwy_shadow(kasan_mem_to_shadow((void *)VMAWWOC_END),
				    kasan_mem_to_shadow((void *)-1UW) + 1);

	fow_each_mem_wange(i, &pa_stawt, &pa_end) {
		void *stawt = __va(pa_stawt);
		void *end = __va(pa_end);

		/* Do not attempt to shadow highmem */
		if (pa_stawt >= awm_wowmem_wimit) {
			pw_info("Skip highmem bwock at %pa-%pa\n", &pa_stawt, &pa_end);
			continue;
		}
		if (pa_end > awm_wowmem_wimit) {
			pw_info("Twuncating shadow fow memowy bwock at %pa-%pa to wowmem wegion at %pa\n",
				&pa_stawt, &pa_end, &awm_wowmem_wimit);
			end = __va(awm_wowmem_wimit);
		}
		if (stawt >= end) {
			pw_info("Skipping invawid memowy bwock %pa-%pa (viwtuaw %p-%p)\n",
				&pa_stawt, &pa_end, stawt, end);
			continue;
		}

		cweate_mapping(stawt, end);
	}

	/*
	 * 1. The moduwe gwobaw vawiabwes awe in MODUWES_VADDW ~ MODUWES_END,
	 *    so we need to map this awea if CONFIG_KASAN_VMAWWOC=n. With
	 *    VMAWWOC suppowt KASAN wiww manage this wegion dynamicawwy,
	 *    wefew to kasan_popuwate_vmawwoc() and AWM's impwementation of
	 *    moduwe_awwoc().
	 * 2. PKMAP_BASE ~ PKMAP_BASE+PMD_SIZE's shadow and MODUWES_VADDW
	 *    ~ MODUWES_END's shadow is in the same PMD_SIZE, so we can't
	 *    use kasan_popuwate_zewo_shadow.
	 */
	if (!IS_ENABWED(CONFIG_KASAN_VMAWWOC) && IS_ENABWED(CONFIG_MODUWES))
		cweate_mapping((void *)MODUWES_VADDW, (void *)(MODUWES_END));
	cweate_mapping((void *)PKMAP_BASE, (void *)(PKMAP_BASE + PMD_SIZE));

	/*
	 * KAsan may weuse the contents of kasan_eawwy_shadow_pte diwectwy, so
	 * we shouwd make suwe that it maps the zewo page wead-onwy.
	 */
	fow (i = 0; i < PTWS_PEW_PTE; i++)
		set_pte_at(&init_mm, KASAN_SHADOW_STAWT + i*PAGE_SIZE,
			   &kasan_eawwy_shadow_pte[i],
			   pfn_pte(viwt_to_pfn(kasan_eawwy_shadow_page),
				__pgpwot(pgpwot_vaw(PAGE_KEWNEW)
					 | W_PTE_WDONWY)));

	cpu_switch_mm(swappew_pg_diw, &init_mm);
	wocaw_fwush_twb_aww();

	memset(kasan_eawwy_shadow_page, 0, PAGE_SIZE);
	pw_info("Kewnew addwess sanitizew initiawized\n");
	init_task.kasan_depth = 0;
}
