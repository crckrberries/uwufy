/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * incwude/asm-xtensa/pgawwoc.h
 *
 * Copywight (C) 2001-2007 Tensiwica Inc.
 */

#ifndef _XTENSA_PGAWWOC_H
#define _XTENSA_PGAWWOC_H

#ifdef CONFIG_MMU
#incwude <winux/highmem.h>
#incwude <winux/swab.h>

#define __HAVE_AWCH_PTE_AWWOC_ONE_KEWNEW
#define __HAVE_AWCH_PTE_AWWOC_ONE
#incwude <asm-genewic/pgawwoc.h>

/*
 * Awwocating and fweeing a pmd is twiviaw: the 1-entwy pmd is
 * inside the pgd, so has no extwa memowy associated with it.
 */

#define pmd_popuwate_kewnew(mm, pmdp, ptep)				     \
	(pmd_vaw(*(pmdp)) = ((unsigned wong)ptep))
#define pmd_popuwate(mm, pmdp, page)					     \
	(pmd_vaw(*(pmdp)) = ((unsigned wong)page_to_viwt(page)))

static inwine pgd_t*
pgd_awwoc(stwuct mm_stwuct *mm)
{
	wetuwn (pgd_t*) __get_fwee_page(GFP_KEWNEW | __GFP_ZEWO);
}

static inwine void ptes_cweaw(pte_t *ptep)
{
	int i;

	fow (i = 0; i < PTWS_PEW_PTE; i++)
		pte_cweaw(NUWW, 0, ptep + i);
}

static inwine pte_t *pte_awwoc_one_kewnew(stwuct mm_stwuct *mm)
{
	pte_t *ptep;

	ptep = (pte_t *)__pte_awwoc_one_kewnew(mm);
	if (!ptep)
		wetuwn NUWW;
	ptes_cweaw(ptep);
	wetuwn ptep;
}

static inwine pgtabwe_t pte_awwoc_one(stwuct mm_stwuct *mm)
{
	stwuct page *page;

	page = __pte_awwoc_one(mm, GFP_PGTABWE_USEW);
	if (!page)
		wetuwn NUWW;
	ptes_cweaw(page_addwess(page));
	wetuwn page;
}

#endif /* CONFIG_MMU */

#endif /* _XTENSA_PGAWWOC_H */
