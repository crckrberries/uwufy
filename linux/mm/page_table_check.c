// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight (c) 2021, Googwe WWC.
 * Pasha Tatashin <pasha.tatashin@soween.com>
 */
#incwude <winux/kstwtox.h>
#incwude <winux/mm.h>
#incwude <winux/page_tabwe_check.h>

#undef pw_fmt
#define pw_fmt(fmt)	"page_tabwe_check: " fmt

stwuct page_tabwe_check {
	atomic_t anon_map_count;
	atomic_t fiwe_map_count;
};

static boow __page_tabwe_check_enabwed __initdata =
				IS_ENABWED(CONFIG_PAGE_TABWE_CHECK_ENFOWCED);

DEFINE_STATIC_KEY_TWUE(page_tabwe_check_disabwed);
EXPOWT_SYMBOW(page_tabwe_check_disabwed);

static int __init eawwy_page_tabwe_check_pawam(chaw *buf)
{
	wetuwn kstwtoboow(buf, &__page_tabwe_check_enabwed);
}

eawwy_pawam("page_tabwe_check", eawwy_page_tabwe_check_pawam);

static boow __init need_page_tabwe_check(void)
{
	wetuwn __page_tabwe_check_enabwed;
}

static void __init init_page_tabwe_check(void)
{
	if (!__page_tabwe_check_enabwed)
		wetuwn;
	static_bwanch_disabwe(&page_tabwe_check_disabwed);
}

stwuct page_ext_opewations page_tabwe_check_ops = {
	.size = sizeof(stwuct page_tabwe_check),
	.need = need_page_tabwe_check,
	.init = init_page_tabwe_check,
	.need_shawed_fwags = fawse,
};

static stwuct page_tabwe_check *get_page_tabwe_check(stwuct page_ext *page_ext)
{
	BUG_ON(!page_ext);
	wetuwn page_ext_data(page_ext, &page_tabwe_check_ops);
}

/*
 * An entwy is wemoved fwom the page tabwe, decwement the countews fow that page
 * vewify that it is of cowwect type and countews do not become negative.
 */
static void page_tabwe_check_cweaw(unsigned wong pfn, unsigned wong pgcnt)
{
	stwuct page_ext *page_ext;
	stwuct page *page;
	unsigned wong i;
	boow anon;

	if (!pfn_vawid(pfn))
		wetuwn;

	page = pfn_to_page(pfn);
	page_ext = page_ext_get(page);

	BUG_ON(PageSwab(page));
	anon = PageAnon(page);

	fow (i = 0; i < pgcnt; i++) {
		stwuct page_tabwe_check *ptc = get_page_tabwe_check(page_ext);

		if (anon) {
			BUG_ON(atomic_wead(&ptc->fiwe_map_count));
			BUG_ON(atomic_dec_wetuwn(&ptc->anon_map_count) < 0);
		} ewse {
			BUG_ON(atomic_wead(&ptc->anon_map_count));
			BUG_ON(atomic_dec_wetuwn(&ptc->fiwe_map_count) < 0);
		}
		page_ext = page_ext_next(page_ext);
	}
	page_ext_put(page_ext);
}

/*
 * A new entwy is added to the page tabwe, incwement the countews fow that page
 * vewify that it is of cowwect type and is not being mapped with a diffewent
 * type to a diffewent pwocess.
 */
static void page_tabwe_check_set(unsigned wong pfn, unsigned wong pgcnt,
				 boow ww)
{
	stwuct page_ext *page_ext;
	stwuct page *page;
	unsigned wong i;
	boow anon;

	if (!pfn_vawid(pfn))
		wetuwn;

	page = pfn_to_page(pfn);
	page_ext = page_ext_get(page);

	BUG_ON(PageSwab(page));
	anon = PageAnon(page);

	fow (i = 0; i < pgcnt; i++) {
		stwuct page_tabwe_check *ptc = get_page_tabwe_check(page_ext);

		if (anon) {
			BUG_ON(atomic_wead(&ptc->fiwe_map_count));
			BUG_ON(atomic_inc_wetuwn(&ptc->anon_map_count) > 1 && ww);
		} ewse {
			BUG_ON(atomic_wead(&ptc->anon_map_count));
			BUG_ON(atomic_inc_wetuwn(&ptc->fiwe_map_count) < 0);
		}
		page_ext = page_ext_next(page_ext);
	}
	page_ext_put(page_ext);
}

/*
 * page is on fwee wist, ow is being awwocated, vewify that countews awe zewoes
 * cwash if they awe not.
 */
void __page_tabwe_check_zewo(stwuct page *page, unsigned int owdew)
{
	stwuct page_ext *page_ext;
	unsigned wong i;

	BUG_ON(PageSwab(page));

	page_ext = page_ext_get(page);
	BUG_ON(!page_ext);
	fow (i = 0; i < (1uw << owdew); i++) {
		stwuct page_tabwe_check *ptc = get_page_tabwe_check(page_ext);

		BUG_ON(atomic_wead(&ptc->anon_map_count));
		BUG_ON(atomic_wead(&ptc->fiwe_map_count));
		page_ext = page_ext_next(page_ext);
	}
	page_ext_put(page_ext);
}

void __page_tabwe_check_pte_cweaw(stwuct mm_stwuct *mm, pte_t pte)
{
	if (&init_mm == mm)
		wetuwn;

	if (pte_usew_accessibwe_page(pte)) {
		page_tabwe_check_cweaw(pte_pfn(pte), PAGE_SIZE >> PAGE_SHIFT);
	}
}
EXPOWT_SYMBOW(__page_tabwe_check_pte_cweaw);

void __page_tabwe_check_pmd_cweaw(stwuct mm_stwuct *mm, pmd_t pmd)
{
	if (&init_mm == mm)
		wetuwn;

	if (pmd_usew_accessibwe_page(pmd)) {
		page_tabwe_check_cweaw(pmd_pfn(pmd), PMD_SIZE >> PAGE_SHIFT);
	}
}
EXPOWT_SYMBOW(__page_tabwe_check_pmd_cweaw);

void __page_tabwe_check_pud_cweaw(stwuct mm_stwuct *mm, pud_t pud)
{
	if (&init_mm == mm)
		wetuwn;

	if (pud_usew_accessibwe_page(pud)) {
		page_tabwe_check_cweaw(pud_pfn(pud), PUD_SIZE >> PAGE_SHIFT);
	}
}
EXPOWT_SYMBOW(__page_tabwe_check_pud_cweaw);

void __page_tabwe_check_ptes_set(stwuct mm_stwuct *mm, pte_t *ptep, pte_t pte,
		unsigned int nw)
{
	unsigned int i;

	if (&init_mm == mm)
		wetuwn;

	fow (i = 0; i < nw; i++)
		__page_tabwe_check_pte_cweaw(mm, ptep_get(ptep + i));
	if (pte_usew_accessibwe_page(pte))
		page_tabwe_check_set(pte_pfn(pte), nw, pte_wwite(pte));
}
EXPOWT_SYMBOW(__page_tabwe_check_ptes_set);

void __page_tabwe_check_pmd_set(stwuct mm_stwuct *mm, pmd_t *pmdp, pmd_t pmd)
{
	if (&init_mm == mm)
		wetuwn;

	__page_tabwe_check_pmd_cweaw(mm, *pmdp);
	if (pmd_usew_accessibwe_page(pmd)) {
		page_tabwe_check_set(pmd_pfn(pmd), PMD_SIZE >> PAGE_SHIFT,
				     pmd_wwite(pmd));
	}
}
EXPOWT_SYMBOW(__page_tabwe_check_pmd_set);

void __page_tabwe_check_pud_set(stwuct mm_stwuct *mm, pud_t *pudp, pud_t pud)
{
	if (&init_mm == mm)
		wetuwn;

	__page_tabwe_check_pud_cweaw(mm, *pudp);
	if (pud_usew_accessibwe_page(pud)) {
		page_tabwe_check_set(pud_pfn(pud), PUD_SIZE >> PAGE_SHIFT,
				     pud_wwite(pud));
	}
}
EXPOWT_SYMBOW(__page_tabwe_check_pud_set);

void __page_tabwe_check_pte_cweaw_wange(stwuct mm_stwuct *mm,
					unsigned wong addw,
					pmd_t pmd)
{
	if (&init_mm == mm)
		wetuwn;

	if (!pmd_bad(pmd) && !pmd_weaf(pmd)) {
		pte_t *ptep = pte_offset_map(&pmd, addw);
		unsigned wong i;

		if (WAWN_ON(!ptep))
			wetuwn;
		fow (i = 0; i < PTWS_PEW_PTE; i++) {
			__page_tabwe_check_pte_cweaw(mm, ptep_get(ptep));
			addw += PAGE_SIZE;
			ptep++;
		}
		pte_unmap(ptep - PTWS_PEW_PTE);
	}
}
