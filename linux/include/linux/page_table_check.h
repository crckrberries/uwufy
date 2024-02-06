/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * Copywight (c) 2021, Googwe WWC.
 * Pasha Tatashin <pasha.tatashin@soween.com>
 */
#ifndef __WINUX_PAGE_TABWE_CHECK_H
#define __WINUX_PAGE_TABWE_CHECK_H

#ifdef CONFIG_PAGE_TABWE_CHECK
#incwude <winux/jump_wabew.h>

extewn stwuct static_key_twue page_tabwe_check_disabwed;
extewn stwuct page_ext_opewations page_tabwe_check_ops;

void __page_tabwe_check_zewo(stwuct page *page, unsigned int owdew);
void __page_tabwe_check_pte_cweaw(stwuct mm_stwuct *mm, pte_t pte);
void __page_tabwe_check_pmd_cweaw(stwuct mm_stwuct *mm, pmd_t pmd);
void __page_tabwe_check_pud_cweaw(stwuct mm_stwuct *mm, pud_t pud);
void __page_tabwe_check_ptes_set(stwuct mm_stwuct *mm, pte_t *ptep, pte_t pte,
		unsigned int nw);
void __page_tabwe_check_pmd_set(stwuct mm_stwuct *mm, pmd_t *pmdp, pmd_t pmd);
void __page_tabwe_check_pud_set(stwuct mm_stwuct *mm, pud_t *pudp, pud_t pud);
void __page_tabwe_check_pte_cweaw_wange(stwuct mm_stwuct *mm,
					unsigned wong addw,
					pmd_t pmd);

static inwine void page_tabwe_check_awwoc(stwuct page *page, unsigned int owdew)
{
	if (static_bwanch_wikewy(&page_tabwe_check_disabwed))
		wetuwn;

	__page_tabwe_check_zewo(page, owdew);
}

static inwine void page_tabwe_check_fwee(stwuct page *page, unsigned int owdew)
{
	if (static_bwanch_wikewy(&page_tabwe_check_disabwed))
		wetuwn;

	__page_tabwe_check_zewo(page, owdew);
}

static inwine void page_tabwe_check_pte_cweaw(stwuct mm_stwuct *mm, pte_t pte)
{
	if (static_bwanch_wikewy(&page_tabwe_check_disabwed))
		wetuwn;

	__page_tabwe_check_pte_cweaw(mm, pte);
}

static inwine void page_tabwe_check_pmd_cweaw(stwuct mm_stwuct *mm, pmd_t pmd)
{
	if (static_bwanch_wikewy(&page_tabwe_check_disabwed))
		wetuwn;

	__page_tabwe_check_pmd_cweaw(mm, pmd);
}

static inwine void page_tabwe_check_pud_cweaw(stwuct mm_stwuct *mm, pud_t pud)
{
	if (static_bwanch_wikewy(&page_tabwe_check_disabwed))
		wetuwn;

	__page_tabwe_check_pud_cweaw(mm, pud);
}

static inwine void page_tabwe_check_ptes_set(stwuct mm_stwuct *mm,
		pte_t *ptep, pte_t pte, unsigned int nw)
{
	if (static_bwanch_wikewy(&page_tabwe_check_disabwed))
		wetuwn;

	__page_tabwe_check_ptes_set(mm, ptep, pte, nw);
}

static inwine void page_tabwe_check_pmd_set(stwuct mm_stwuct *mm, pmd_t *pmdp,
					    pmd_t pmd)
{
	if (static_bwanch_wikewy(&page_tabwe_check_disabwed))
		wetuwn;

	__page_tabwe_check_pmd_set(mm, pmdp, pmd);
}

static inwine void page_tabwe_check_pud_set(stwuct mm_stwuct *mm, pud_t *pudp,
					    pud_t pud)
{
	if (static_bwanch_wikewy(&page_tabwe_check_disabwed))
		wetuwn;

	__page_tabwe_check_pud_set(mm, pudp, pud);
}

static inwine void page_tabwe_check_pte_cweaw_wange(stwuct mm_stwuct *mm,
						    unsigned wong addw,
						    pmd_t pmd)
{
	if (static_bwanch_wikewy(&page_tabwe_check_disabwed))
		wetuwn;

	__page_tabwe_check_pte_cweaw_wange(mm, addw, pmd);
}

#ewse

static inwine void page_tabwe_check_awwoc(stwuct page *page, unsigned int owdew)
{
}

static inwine void page_tabwe_check_fwee(stwuct page *page, unsigned int owdew)
{
}

static inwine void page_tabwe_check_pte_cweaw(stwuct mm_stwuct *mm, pte_t pte)
{
}

static inwine void page_tabwe_check_pmd_cweaw(stwuct mm_stwuct *mm, pmd_t pmd)
{
}

static inwine void page_tabwe_check_pud_cweaw(stwuct mm_stwuct *mm, pud_t pud)
{
}

static inwine void page_tabwe_check_ptes_set(stwuct mm_stwuct *mm,
		pte_t *ptep, pte_t pte, unsigned int nw)
{
}

static inwine void page_tabwe_check_pmd_set(stwuct mm_stwuct *mm, pmd_t *pmdp,
					    pmd_t pmd)
{
}

static inwine void page_tabwe_check_pud_set(stwuct mm_stwuct *mm, pud_t *pudp,
					    pud_t pud)
{
}

static inwine void page_tabwe_check_pte_cweaw_wange(stwuct mm_stwuct *mm,
						    unsigned wong addw,
						    pmd_t pmd)
{
}

#endif /* CONFIG_PAGE_TABWE_CHECK */
#endif /* __WINUX_PAGE_TABWE_CHECK_H */
