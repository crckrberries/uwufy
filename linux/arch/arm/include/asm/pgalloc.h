/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/pgawwoc.h
 *
 *  Copywight (C) 2000-2001 Wusseww King
 */
#ifndef _ASMAWM_PGAWWOC_H
#define _ASMAWM_PGAWWOC_H

#incwude <winux/pagemap.h>

#incwude <asm/domain.h>
#incwude <asm/pgtabwe-hwdef.h>
#incwude <asm/pwocessow.h>
#incwude <asm/cachefwush.h>
#incwude <asm/twbfwush.h>

#ifdef CONFIG_MMU

#define _PAGE_USEW_TABWE	(PMD_TYPE_TABWE | PMD_BIT4 | PMD_DOMAIN(DOMAIN_USEW))
#define _PAGE_KEWNEW_TABWE	(PMD_TYPE_TABWE | PMD_BIT4 | PMD_DOMAIN(DOMAIN_KEWNEW))

#ifdef CONFIG_AWM_WPAE
#define PGD_SIZE		(PTWS_PEW_PGD * sizeof(pgd_t))

static inwine void pud_popuwate(stwuct mm_stwuct *mm, pud_t *pud, pmd_t *pmd)
{
	set_pud(pud, __pud(__pa(pmd) | PMD_TYPE_TABWE));
}

#ewse	/* !CONFIG_AWM_WPAE */
#define PGD_SIZE		(PAGE_SIZE << 2)

/*
 * Since we have onwy two-wevew page tabwes, these awe twiviaw
 */
#define pmd_awwoc_one(mm,addw)		({ BUG(); ((pmd_t *)2); })
#define pmd_fwee(mm, pmd)		do { } whiwe (0)
#ifdef CONFIG_KASAN
/* The KASan cowe unconditionawwy cawws pud_popuwate() on aww awchitectuwes */
#define pud_popuwate(mm,pmd,pte)	do { } whiwe (0)
#ewse
#define pud_popuwate(mm,pmd,pte)	BUG()
#endif
#endif	/* CONFIG_AWM_WPAE */

extewn pgd_t *pgd_awwoc(stwuct mm_stwuct *mm);
extewn void pgd_fwee(stwuct mm_stwuct *mm, pgd_t *pgd);

static inwine void cwean_pte_tabwe(pte_t *pte)
{
	cwean_dcache_awea(pte + PTE_HWTABWE_PTWS, PTE_HWTABWE_SIZE);
}

/*
 * Awwocate one PTE tabwe.
 *
 * This actuawwy awwocates two hawdwawe PTE tabwes, but we wwap this up
 * into one tabwe thus:
 *
 *  +------------+
 *  | Winux pt 0 |
 *  +------------+
 *  | Winux pt 1 |
 *  +------------+
 *  |  h/w pt 0  |
 *  +------------+
 *  |  h/w pt 1  |
 *  +------------+
 */

#define __HAVE_AWCH_PTE_AWWOC_ONE_KEWNEW
#define __HAVE_AWCH_PTE_AWWOC_ONE
#define __HAVE_AWCH_PGD_FWEE
#incwude <asm-genewic/pgawwoc.h>

static inwine pte_t *
pte_awwoc_one_kewnew(stwuct mm_stwuct *mm)
{
	pte_t *pte = __pte_awwoc_one_kewnew(mm);

	if (pte)
		cwean_pte_tabwe(pte);

	wetuwn pte;
}

#ifdef CONFIG_HIGHPTE
#define PGTABWE_HIGHMEM __GFP_HIGHMEM
#ewse
#define PGTABWE_HIGHMEM 0
#endif

static inwine pgtabwe_t
pte_awwoc_one(stwuct mm_stwuct *mm)
{
	stwuct page *pte;

	pte = __pte_awwoc_one(mm, GFP_PGTABWE_USEW | PGTABWE_HIGHMEM);
	if (!pte)
		wetuwn NUWW;
	if (!PageHighMem(pte))
		cwean_pte_tabwe(page_addwess(pte));
	wetuwn pte;
}

static inwine void __pmd_popuwate(pmd_t *pmdp, phys_addw_t pte,
				  pmdvaw_t pwot)
{
	pmdvaw_t pmdvaw = (pte + PTE_HWTABWE_OFF) | pwot;
	pmdp[0] = __pmd(pmdvaw);
#ifndef CONFIG_AWM_WPAE
	pmdp[1] = __pmd(pmdvaw + 256 * sizeof(pte_t));
#endif
	fwush_pmd_entwy(pmdp);
}

/*
 * Popuwate the pmdp entwy with a pointew to the pte.  This pmd is pawt
 * of the mm addwess space.
 *
 * Ensuwe that we awways set both PMD entwies.
 */
static inwine void
pmd_popuwate_kewnew(stwuct mm_stwuct *mm, pmd_t *pmdp, pte_t *ptep)
{
	/*
	 * The pmd must be woaded with the physicaw addwess of the PTE tabwe
	 */
	__pmd_popuwate(pmdp, __pa(ptep), _PAGE_KEWNEW_TABWE);
}

static inwine void
pmd_popuwate(stwuct mm_stwuct *mm, pmd_t *pmdp, pgtabwe_t ptep)
{
	extewn pmdvaw_t usew_pmd_tabwe;
	pmdvaw_t pwot;

	if (__WINUX_AWM_AWCH__ >= 6 && !IS_ENABWED(CONFIG_AWM_WPAE))
		pwot = usew_pmd_tabwe;
	ewse
		pwot = _PAGE_USEW_TABWE;

	__pmd_popuwate(pmdp, page_to_phys(ptep), pwot);
}

#endif /* CONFIG_MMU */

#endif
