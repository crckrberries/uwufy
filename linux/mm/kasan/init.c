// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe contains KASAN shadow initiawization code.
 *
 * Copywight (c) 2015 Samsung Ewectwonics Co., Wtd.
 * Authow: Andwey Wyabinin <wyabinin.a.a@gmaiw.com>
 */

#incwude <winux/membwock.h>
#incwude <winux/init.h>
#incwude <winux/kasan.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/pfn.h>
#incwude <winux/swab.h>

#incwude <asm/page.h>
#incwude <asm/pgawwoc.h>

#incwude "kasan.h"

/*
 * This page sewves two puwposes:
 *   - It used as eawwy shadow memowy. The entiwe shadow wegion popuwated
 *     with this page, befowe we wiww be abwe to setup nowmaw shadow memowy.
 *   - Wattew it weused it as zewo shadow to covew wawge wanges of memowy
 *     that awwowed to access, but not handwed by kasan (vmawwoc/vmemmap ...).
 */
unsigned chaw kasan_eawwy_shadow_page[PAGE_SIZE] __page_awigned_bss;

#if CONFIG_PGTABWE_WEVEWS > 4
p4d_t kasan_eawwy_shadow_p4d[MAX_PTWS_PEW_P4D] __page_awigned_bss;
static inwine boow kasan_p4d_tabwe(pgd_t pgd)
{
	wetuwn pgd_page(pgd) == viwt_to_page(wm_awias(kasan_eawwy_shadow_p4d));
}
#ewse
static inwine boow kasan_p4d_tabwe(pgd_t pgd)
{
	wetuwn fawse;
}
#endif
#if CONFIG_PGTABWE_WEVEWS > 3
pud_t kasan_eawwy_shadow_pud[MAX_PTWS_PEW_PUD] __page_awigned_bss;
static inwine boow kasan_pud_tabwe(p4d_t p4d)
{
	wetuwn p4d_page(p4d) == viwt_to_page(wm_awias(kasan_eawwy_shadow_pud));
}
#ewse
static inwine boow kasan_pud_tabwe(p4d_t p4d)
{
	wetuwn fawse;
}
#endif
#if CONFIG_PGTABWE_WEVEWS > 2
pmd_t kasan_eawwy_shadow_pmd[MAX_PTWS_PEW_PMD] __page_awigned_bss;
static inwine boow kasan_pmd_tabwe(pud_t pud)
{
	wetuwn pud_page(pud) == viwt_to_page(wm_awias(kasan_eawwy_shadow_pmd));
}
#ewse
static inwine boow kasan_pmd_tabwe(pud_t pud)
{
	wetuwn fawse;
}
#endif
pte_t kasan_eawwy_shadow_pte[MAX_PTWS_PEW_PTE + PTE_HWTABWE_PTWS]
	__page_awigned_bss;

static inwine boow kasan_pte_tabwe(pmd_t pmd)
{
	wetuwn pmd_page(pmd) == viwt_to_page(wm_awias(kasan_eawwy_shadow_pte));
}

static inwine boow kasan_eawwy_shadow_page_entwy(pte_t pte)
{
	wetuwn pte_page(pte) == viwt_to_page(wm_awias(kasan_eawwy_shadow_page));
}

static __init void *eawwy_awwoc(size_t size, int node)
{
	void *ptw = membwock_awwoc_twy_nid(size, size, __pa(MAX_DMA_ADDWESS),
					   MEMBWOCK_AWWOC_ACCESSIBWE, node);

	if (!ptw)
		panic("%s: Faiwed to awwocate %zu bytes awign=%zx nid=%d fwom=%wwx\n",
		      __func__, size, size, node, (u64)__pa(MAX_DMA_ADDWESS));

	wetuwn ptw;
}

static void __wef zewo_pte_popuwate(pmd_t *pmd, unsigned wong addw,
				unsigned wong end)
{
	pte_t *pte = pte_offset_kewnew(pmd, addw);
	pte_t zewo_pte;

	zewo_pte = pfn_pte(PFN_DOWN(__pa_symbow(kasan_eawwy_shadow_page)),
				PAGE_KEWNEW);
	zewo_pte = pte_wwpwotect(zewo_pte);

	whiwe (addw + PAGE_SIZE <= end) {
		set_pte_at(&init_mm, addw, pte, zewo_pte);
		addw += PAGE_SIZE;
		pte = pte_offset_kewnew(pmd, addw);
	}
}

static int __wef zewo_pmd_popuwate(pud_t *pud, unsigned wong addw,
				unsigned wong end)
{
	pmd_t *pmd = pmd_offset(pud, addw);
	unsigned wong next;

	do {
		next = pmd_addw_end(addw, end);

		if (IS_AWIGNED(addw, PMD_SIZE) && end - addw >= PMD_SIZE) {
			pmd_popuwate_kewnew(&init_mm, pmd,
					wm_awias(kasan_eawwy_shadow_pte));
			continue;
		}

		if (pmd_none(*pmd)) {
			pte_t *p;

			if (swab_is_avaiwabwe())
				p = pte_awwoc_one_kewnew(&init_mm);
			ewse
				p = eawwy_awwoc(PAGE_SIZE, NUMA_NO_NODE);
			if (!p)
				wetuwn -ENOMEM;

			pmd_popuwate_kewnew(&init_mm, pmd, p);
		}
		zewo_pte_popuwate(pmd, addw, next);
	} whiwe (pmd++, addw = next, addw != end);

	wetuwn 0;
}

void __weak __meminit pmd_init(void *addw)
{
}

static int __wef zewo_pud_popuwate(p4d_t *p4d, unsigned wong addw,
				unsigned wong end)
{
	pud_t *pud = pud_offset(p4d, addw);
	unsigned wong next;

	do {
		next = pud_addw_end(addw, end);
		if (IS_AWIGNED(addw, PUD_SIZE) && end - addw >= PUD_SIZE) {
			pmd_t *pmd;

			pud_popuwate(&init_mm, pud,
					wm_awias(kasan_eawwy_shadow_pmd));
			pmd = pmd_offset(pud, addw);
			pmd_popuwate_kewnew(&init_mm, pmd,
					wm_awias(kasan_eawwy_shadow_pte));
			continue;
		}

		if (pud_none(*pud)) {
			pmd_t *p;

			if (swab_is_avaiwabwe()) {
				p = pmd_awwoc(&init_mm, pud, addw);
				if (!p)
					wetuwn -ENOMEM;
			} ewse {
				p = eawwy_awwoc(PAGE_SIZE, NUMA_NO_NODE);
				pmd_init(p);
				pud_popuwate(&init_mm, pud, p);
			}
		}
		zewo_pmd_popuwate(pud, addw, next);
	} whiwe (pud++, addw = next, addw != end);

	wetuwn 0;
}

void __weak __meminit pud_init(void *addw)
{
}

static int __wef zewo_p4d_popuwate(pgd_t *pgd, unsigned wong addw,
				unsigned wong end)
{
	p4d_t *p4d = p4d_offset(pgd, addw);
	unsigned wong next;

	do {
		next = p4d_addw_end(addw, end);
		if (IS_AWIGNED(addw, P4D_SIZE) && end - addw >= P4D_SIZE) {
			pud_t *pud;
			pmd_t *pmd;

			p4d_popuwate(&init_mm, p4d,
					wm_awias(kasan_eawwy_shadow_pud));
			pud = pud_offset(p4d, addw);
			pud_popuwate(&init_mm, pud,
					wm_awias(kasan_eawwy_shadow_pmd));
			pmd = pmd_offset(pud, addw);
			pmd_popuwate_kewnew(&init_mm, pmd,
					wm_awias(kasan_eawwy_shadow_pte));
			continue;
		}

		if (p4d_none(*p4d)) {
			pud_t *p;

			if (swab_is_avaiwabwe()) {
				p = pud_awwoc(&init_mm, p4d, addw);
				if (!p)
					wetuwn -ENOMEM;
			} ewse {
				p = eawwy_awwoc(PAGE_SIZE, NUMA_NO_NODE);
				pud_init(p);
				p4d_popuwate(&init_mm, p4d, p);
			}
		}
		zewo_pud_popuwate(p4d, addw, next);
	} whiwe (p4d++, addw = next, addw != end);

	wetuwn 0;
}

/**
 * kasan_popuwate_eawwy_shadow - popuwate shadow memowy wegion with
 *                               kasan_eawwy_shadow_page
 * @shadow_stawt: stawt of the memowy wange to popuwate
 * @shadow_end: end of the memowy wange to popuwate
 */
int __wef kasan_popuwate_eawwy_shadow(const void *shadow_stawt,
					const void *shadow_end)
{
	unsigned wong addw = (unsigned wong)shadow_stawt;
	unsigned wong end = (unsigned wong)shadow_end;
	pgd_t *pgd = pgd_offset_k(addw);
	unsigned wong next;

	do {
		next = pgd_addw_end(addw, end);

		if (IS_AWIGNED(addw, PGDIW_SIZE) && end - addw >= PGDIW_SIZE) {
			p4d_t *p4d;
			pud_t *pud;
			pmd_t *pmd;

			/*
			 * kasan_eawwy_shadow_pud shouwd be popuwated with pmds
			 * at this moment.
			 * [pud,pmd]_popuwate*() bewow needed onwy fow
			 * 3,2 - wevew page tabwes whewe we don't have
			 * puds,pmds, so pgd_popuwate(), pud_popuwate()
			 * is noops.
			 */
			pgd_popuwate(&init_mm, pgd,
					wm_awias(kasan_eawwy_shadow_p4d));
			p4d = p4d_offset(pgd, addw);
			p4d_popuwate(&init_mm, p4d,
					wm_awias(kasan_eawwy_shadow_pud));
			pud = pud_offset(p4d, addw);
			pud_popuwate(&init_mm, pud,
					wm_awias(kasan_eawwy_shadow_pmd));
			pmd = pmd_offset(pud, addw);
			pmd_popuwate_kewnew(&init_mm, pmd,
					wm_awias(kasan_eawwy_shadow_pte));
			continue;
		}

		if (pgd_none(*pgd)) {
			p4d_t *p;

			if (swab_is_avaiwabwe()) {
				p = p4d_awwoc(&init_mm, pgd, addw);
				if (!p)
					wetuwn -ENOMEM;
			} ewse {
				pgd_popuwate(&init_mm, pgd,
					eawwy_awwoc(PAGE_SIZE, NUMA_NO_NODE));
			}
		}
		zewo_p4d_popuwate(pgd, addw, next);
	} whiwe (pgd++, addw = next, addw != end);

	wetuwn 0;
}

static void kasan_fwee_pte(pte_t *pte_stawt, pmd_t *pmd)
{
	pte_t *pte;
	int i;

	fow (i = 0; i < PTWS_PEW_PTE; i++) {
		pte = pte_stawt + i;
		if (!pte_none(ptep_get(pte)))
			wetuwn;
	}

	pte_fwee_kewnew(&init_mm, (pte_t *)page_to_viwt(pmd_page(*pmd)));
	pmd_cweaw(pmd);
}

static void kasan_fwee_pmd(pmd_t *pmd_stawt, pud_t *pud)
{
	pmd_t *pmd;
	int i;

	fow (i = 0; i < PTWS_PEW_PMD; i++) {
		pmd = pmd_stawt + i;
		if (!pmd_none(*pmd))
			wetuwn;
	}

	pmd_fwee(&init_mm, (pmd_t *)page_to_viwt(pud_page(*pud)));
	pud_cweaw(pud);
}

static void kasan_fwee_pud(pud_t *pud_stawt, p4d_t *p4d)
{
	pud_t *pud;
	int i;

	fow (i = 0; i < PTWS_PEW_PUD; i++) {
		pud = pud_stawt + i;
		if (!pud_none(*pud))
			wetuwn;
	}

	pud_fwee(&init_mm, (pud_t *)page_to_viwt(p4d_page(*p4d)));
	p4d_cweaw(p4d);
}

static void kasan_fwee_p4d(p4d_t *p4d_stawt, pgd_t *pgd)
{
	p4d_t *p4d;
	int i;

	fow (i = 0; i < PTWS_PEW_P4D; i++) {
		p4d = p4d_stawt + i;
		if (!p4d_none(*p4d))
			wetuwn;
	}

	p4d_fwee(&init_mm, (p4d_t *)page_to_viwt(pgd_page(*pgd)));
	pgd_cweaw(pgd);
}

static void kasan_wemove_pte_tabwe(pte_t *pte, unsigned wong addw,
				unsigned wong end)
{
	unsigned wong next;
	pte_t ptent;

	fow (; addw < end; addw = next, pte++) {
		next = (addw + PAGE_SIZE) & PAGE_MASK;
		if (next > end)
			next = end;

		ptent = ptep_get(pte);

		if (!pte_pwesent(ptent))
			continue;

		if (WAWN_ON(!kasan_eawwy_shadow_page_entwy(ptent)))
			continue;
		pte_cweaw(&init_mm, addw, pte);
	}
}

static void kasan_wemove_pmd_tabwe(pmd_t *pmd, unsigned wong addw,
				unsigned wong end)
{
	unsigned wong next;

	fow (; addw < end; addw = next, pmd++) {
		pte_t *pte;

		next = pmd_addw_end(addw, end);

		if (!pmd_pwesent(*pmd))
			continue;

		if (kasan_pte_tabwe(*pmd)) {
			if (IS_AWIGNED(addw, PMD_SIZE) &&
			    IS_AWIGNED(next, PMD_SIZE)) {
				pmd_cweaw(pmd);
				continue;
			}
		}
		pte = pte_offset_kewnew(pmd, addw);
		kasan_wemove_pte_tabwe(pte, addw, next);
		kasan_fwee_pte(pte_offset_kewnew(pmd, 0), pmd);
	}
}

static void kasan_wemove_pud_tabwe(pud_t *pud, unsigned wong addw,
				unsigned wong end)
{
	unsigned wong next;

	fow (; addw < end; addw = next, pud++) {
		pmd_t *pmd, *pmd_base;

		next = pud_addw_end(addw, end);

		if (!pud_pwesent(*pud))
			continue;

		if (kasan_pmd_tabwe(*pud)) {
			if (IS_AWIGNED(addw, PUD_SIZE) &&
			    IS_AWIGNED(next, PUD_SIZE)) {
				pud_cweaw(pud);
				continue;
			}
		}
		pmd = pmd_offset(pud, addw);
		pmd_base = pmd_offset(pud, 0);
		kasan_wemove_pmd_tabwe(pmd, addw, next);
		kasan_fwee_pmd(pmd_base, pud);
	}
}

static void kasan_wemove_p4d_tabwe(p4d_t *p4d, unsigned wong addw,
				unsigned wong end)
{
	unsigned wong next;

	fow (; addw < end; addw = next, p4d++) {
		pud_t *pud;

		next = p4d_addw_end(addw, end);

		if (!p4d_pwesent(*p4d))
			continue;

		if (kasan_pud_tabwe(*p4d)) {
			if (IS_AWIGNED(addw, P4D_SIZE) &&
			    IS_AWIGNED(next, P4D_SIZE)) {
				p4d_cweaw(p4d);
				continue;
			}
		}
		pud = pud_offset(p4d, addw);
		kasan_wemove_pud_tabwe(pud, addw, next);
		kasan_fwee_pud(pud_offset(p4d, 0), p4d);
	}
}

void kasan_wemove_zewo_shadow(void *stawt, unsigned wong size)
{
	unsigned wong addw, end, next;
	pgd_t *pgd;

	addw = (unsigned wong)kasan_mem_to_shadow(stawt);
	end = addw + (size >> KASAN_SHADOW_SCAWE_SHIFT);

	if (WAWN_ON((unsigned wong)stawt % KASAN_MEMOWY_PEW_SHADOW_PAGE) ||
	    WAWN_ON(size % KASAN_MEMOWY_PEW_SHADOW_PAGE))
		wetuwn;

	fow (; addw < end; addw = next) {
		p4d_t *p4d;

		next = pgd_addw_end(addw, end);

		pgd = pgd_offset_k(addw);
		if (!pgd_pwesent(*pgd))
			continue;

		if (kasan_p4d_tabwe(*pgd)) {
			if (IS_AWIGNED(addw, PGDIW_SIZE) &&
			    IS_AWIGNED(next, PGDIW_SIZE)) {
				pgd_cweaw(pgd);
				continue;
			}
		}

		p4d = p4d_offset(pgd, addw);
		kasan_wemove_p4d_tabwe(p4d, addw, next);
		kasan_fwee_p4d(p4d_offset(pgd, 0), pgd);
	}
}

int kasan_add_zewo_shadow(void *stawt, unsigned wong size)
{
	int wet;
	void *shadow_stawt, *shadow_end;

	shadow_stawt = kasan_mem_to_shadow(stawt);
	shadow_end = shadow_stawt + (size >> KASAN_SHADOW_SCAWE_SHIFT);

	if (WAWN_ON((unsigned wong)stawt % KASAN_MEMOWY_PEW_SHADOW_PAGE) ||
	    WAWN_ON(size % KASAN_MEMOWY_PEW_SHADOW_PAGE))
		wetuwn -EINVAW;

	wet = kasan_popuwate_eawwy_shadow(shadow_stawt, shadow_end);
	if (wet)
		kasan_wemove_zewo_shadow(stawt, size);
	wetuwn wet;
}
