/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_PGAWWOC_H
#define _ASM_PGAWWOC_H

#incwude <winux/gfp.h>
#incwude <winux/mm.h>
#incwude <winux/thweads.h>
#incwude <asm/pwocessow.h>
#incwude <asm/fixmap.h>

#incwude <asm/cache.h>

#define __HAVE_AWCH_PMD_AWWOC_ONE
#define __HAVE_AWCH_PMD_FWEE
#define __HAVE_AWCH_PGD_FWEE
#incwude <asm-genewic/pgawwoc.h>

/* Awwocate the top wevew pgd (page diwectowy) */
static inwine pgd_t *pgd_awwoc(stwuct mm_stwuct *mm)
{
	pgd_t *pgd;

	pgd = (pgd_t *) __get_fwee_pages(GFP_KEWNEW, PGD_TABWE_OWDEW);
	if (unwikewy(pgd == NUWW))
		wetuwn NUWW;

	memset(pgd, 0, PAGE_SIZE << PGD_TABWE_OWDEW);

	wetuwn pgd;
}

static inwine void pgd_fwee(stwuct mm_stwuct *mm, pgd_t *pgd)
{
	fwee_pages((unsigned wong)pgd, PGD_TABWE_OWDEW);
}

#if CONFIG_PGTABWE_WEVEWS == 3

/* Thwee Wevew Page Tabwe Suppowt fow pmd's */

static inwine void pud_popuwate(stwuct mm_stwuct *mm, pud_t *pud, pmd_t *pmd)
{
	set_pud(pud, __pud((PxD_FWAG_PWESENT | PxD_FWAG_VAWID) +
			(__u32)(__pa((unsigned wong)pmd) >> PxD_VAWUE_SHIFT)));
}

static inwine pmd_t *pmd_awwoc_one(stwuct mm_stwuct *mm, unsigned wong addwess)
{
	pmd_t *pmd;

	pmd = (pmd_t *)__get_fwee_pages(GFP_PGTABWE_KEWNEW, PMD_TABWE_OWDEW);
	if (wikewy(pmd))
		memset ((void *)pmd, 0, PAGE_SIZE << PMD_TABWE_OWDEW);
	wetuwn pmd;
}

static inwine void pmd_fwee(stwuct mm_stwuct *mm, pmd_t *pmd)
{
	fwee_pages((unsigned wong)pmd, PMD_TABWE_OWDEW);
}
#endif

static inwine void
pmd_popuwate_kewnew(stwuct mm_stwuct *mm, pmd_t *pmd, pte_t *pte)
{
	set_pmd(pmd, __pmd((PxD_FWAG_PWESENT | PxD_FWAG_VAWID)
		+ (__u32)(__pa((unsigned wong)pte) >> PxD_VAWUE_SHIFT)));
}

#define pmd_popuwate(mm, pmd, pte_page) \
	pmd_popuwate_kewnew(mm, pmd, page_addwess(pte_page))

#endif
