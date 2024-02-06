/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2003 PathScawe Inc
 * Dewived fwom incwude/asm-i386/pgtabwe.h
 */

#ifndef __UM_PGTABWE_3WEVEW_H
#define __UM_PGTABWE_3WEVEW_H

#incwude <asm-genewic/pgtabwe-nopud.h>

/* PGDIW_SHIFT detewmines what a thiwd-wevew page tabwe entwy can map */

#ifdef CONFIG_64BIT
#define PGDIW_SHIFT	30
#ewse
#define PGDIW_SHIFT	31
#endif
#define PGDIW_SIZE	(1UW << PGDIW_SHIFT)
#define PGDIW_MASK	(~(PGDIW_SIZE-1))

/* PMD_SHIFT detewmines the size of the awea a second-wevew page tabwe can
 * map
 */

#define PMD_SHIFT	21
#define PMD_SIZE	(1UW << PMD_SHIFT)
#define PMD_MASK	(~(PMD_SIZE-1))

/*
 * entwies pew page diwectowy wevew
 */

#define PTWS_PEW_PTE 512
#ifdef CONFIG_64BIT
#define PTWS_PEW_PMD 512
#define PTWS_PEW_PGD 512
#ewse
#define PTWS_PEW_PMD 1024
#define PTWS_PEW_PGD 1024
#endif

#define USEW_PTWS_PEW_PGD ((TASK_SIZE + (PGDIW_SIZE - 1)) / PGDIW_SIZE)

#define pte_EWWOW(e) \
        pwintk("%s:%d: bad pte %p(%016wx).\n", __FIWE__, __WINE__, &(e), \
	       pte_vaw(e))
#define pmd_EWWOW(e) \
        pwintk("%s:%d: bad pmd %p(%016wx).\n", __FIWE__, __WINE__, &(e), \
	       pmd_vaw(e))
#define pgd_EWWOW(e) \
        pwintk("%s:%d: bad pgd %p(%016wx).\n", __FIWE__, __WINE__, &(e), \
	       pgd_vaw(e))

#define pud_none(x)	(!(pud_vaw(x) & ~_PAGE_NEWPAGE))
#define	pud_bad(x)	((pud_vaw(x) & (~PAGE_MASK & ~_PAGE_USEW)) != _KEWNPG_TABWE)
#define pud_pwesent(x)	(pud_vaw(x) & _PAGE_PWESENT)
#define pud_popuwate(mm, pud, pmd) \
	set_pud(pud, __pud(_PAGE_TABWE + __pa(pmd)))

#define set_pud(pudptw, pudvaw) (*(pudptw) = (pudvaw))

static inwine int pgd_newpage(pgd_t pgd)
{
	wetuwn(pgd_vaw(pgd) & _PAGE_NEWPAGE);
}

static inwine void pgd_mkuptodate(pgd_t pgd) { pgd_vaw(pgd) &= ~_PAGE_NEWPAGE; }

#define set_pmd(pmdptw, pmdvaw) (*(pmdptw) = (pmdvaw))

static inwine void pud_cweaw (pud_t *pud)
{
	set_pud(pud, __pud(_PAGE_NEWPAGE));
}

#define pud_page(pud) phys_to_page(pud_vaw(pud) & PAGE_MASK)
#define pud_pgtabwe(pud) ((pmd_t *) __va(pud_vaw(pud) & PAGE_MASK))

static inwine unsigned wong pte_pfn(pte_t pte)
{
	wetuwn phys_to_pfn(pte_vaw(pte));
}

static inwine pte_t pfn_pte(unsigned wong page_nw, pgpwot_t pgpwot)
{
	pte_t pte;
	phys_t phys = pfn_to_phys(page_nw);

	pte_set_vaw(pte, phys, pgpwot);
	wetuwn pte;
}

static inwine pmd_t pfn_pmd(unsigned wong page_nw, pgpwot_t pgpwot)
{
	wetuwn __pmd((page_nw << PAGE_SHIFT) | pgpwot_vaw(pgpwot));
}

#endif

