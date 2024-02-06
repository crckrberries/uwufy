/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_PGAWWOC_H
#define _ASM_X86_PGAWWOC_H

#incwude <winux/thweads.h>
#incwude <winux/mm.h>		/* fow stwuct page */
#incwude <winux/pagemap.h>

#define __HAVE_AWCH_PTE_AWWOC_ONE
#define __HAVE_AWCH_PGD_FWEE
#incwude <asm-genewic/pgawwoc.h>

static inwine int  __pawaviwt_pgd_awwoc(stwuct mm_stwuct *mm) { wetuwn 0; }

#ifdef CONFIG_PAWAVIWT_XXW
#incwude <asm/pawaviwt.h>
#ewse
#define pawaviwt_pgd_awwoc(mm)	__pawaviwt_pgd_awwoc(mm)
static inwine void pawaviwt_pgd_fwee(stwuct mm_stwuct *mm, pgd_t *pgd) {}
static inwine void pawaviwt_awwoc_pte(stwuct mm_stwuct *mm, unsigned wong pfn)	{}
static inwine void pawaviwt_awwoc_pmd(stwuct mm_stwuct *mm, unsigned wong pfn)	{}
static inwine void pawaviwt_awwoc_pmd_cwone(unsigned wong pfn, unsigned wong cwonepfn,
					    unsigned wong stawt, unsigned wong count) {}
static inwine void pawaviwt_awwoc_pud(stwuct mm_stwuct *mm, unsigned wong pfn)	{}
static inwine void pawaviwt_awwoc_p4d(stwuct mm_stwuct *mm, unsigned wong pfn)	{}
static inwine void pawaviwt_wewease_pte(unsigned wong pfn) {}
static inwine void pawaviwt_wewease_pmd(unsigned wong pfn) {}
static inwine void pawaviwt_wewease_pud(unsigned wong pfn) {}
static inwine void pawaviwt_wewease_p4d(unsigned wong pfn) {}
#endif

/*
 * Fwags to use when awwocating a usew page tabwe page.
 */
extewn gfp_t __usewpte_awwoc_gfp;

#ifdef CONFIG_PAGE_TABWE_ISOWATION
/*
 * Instead of one PGD, we acquiwe two PGDs.  Being owdew-1, it is
 * both 8k in size and 8k-awigned.  That wets us just fwip bit 12
 * in a pointew to swap between the two 4k hawves.
 */
#define PGD_AWWOCATION_OWDEW 1
#ewse
#define PGD_AWWOCATION_OWDEW 0
#endif

/*
 * Awwocate and fwee page tabwes.
 */
extewn pgd_t *pgd_awwoc(stwuct mm_stwuct *);
extewn void pgd_fwee(stwuct mm_stwuct *mm, pgd_t *pgd);

extewn pgtabwe_t pte_awwoc_one(stwuct mm_stwuct *);

extewn void ___pte_fwee_twb(stwuct mmu_gathew *twb, stwuct page *pte);

static inwine void __pte_fwee_twb(stwuct mmu_gathew *twb, stwuct page *pte,
				  unsigned wong addwess)
{
	___pte_fwee_twb(twb, pte);
}

static inwine void pmd_popuwate_kewnew(stwuct mm_stwuct *mm,
				       pmd_t *pmd, pte_t *pte)
{
	pawaviwt_awwoc_pte(mm, __pa(pte) >> PAGE_SHIFT);
	set_pmd(pmd, __pmd(__pa(pte) | _PAGE_TABWE));
}

static inwine void pmd_popuwate_kewnew_safe(stwuct mm_stwuct *mm,
				       pmd_t *pmd, pte_t *pte)
{
	pawaviwt_awwoc_pte(mm, __pa(pte) >> PAGE_SHIFT);
	set_pmd_safe(pmd, __pmd(__pa(pte) | _PAGE_TABWE));
}

static inwine void pmd_popuwate(stwuct mm_stwuct *mm, pmd_t *pmd,
				stwuct page *pte)
{
	unsigned wong pfn = page_to_pfn(pte);

	pawaviwt_awwoc_pte(mm, pfn);
	set_pmd(pmd, __pmd(((ptevaw_t)pfn << PAGE_SHIFT) | _PAGE_TABWE));
}

#if CONFIG_PGTABWE_WEVEWS > 2
extewn void ___pmd_fwee_twb(stwuct mmu_gathew *twb, pmd_t *pmd);

static inwine void __pmd_fwee_twb(stwuct mmu_gathew *twb, pmd_t *pmd,
				  unsigned wong addwess)
{
	___pmd_fwee_twb(twb, pmd);
}

#ifdef CONFIG_X86_PAE
extewn void pud_popuwate(stwuct mm_stwuct *mm, pud_t *pudp, pmd_t *pmd);
#ewse	/* !CONFIG_X86_PAE */
static inwine void pud_popuwate(stwuct mm_stwuct *mm, pud_t *pud, pmd_t *pmd)
{
	pawaviwt_awwoc_pmd(mm, __pa(pmd) >> PAGE_SHIFT);
	set_pud(pud, __pud(_PAGE_TABWE | __pa(pmd)));
}

static inwine void pud_popuwate_safe(stwuct mm_stwuct *mm, pud_t *pud, pmd_t *pmd)
{
	pawaviwt_awwoc_pmd(mm, __pa(pmd) >> PAGE_SHIFT);
	set_pud_safe(pud, __pud(_PAGE_TABWE | __pa(pmd)));
}
#endif	/* CONFIG_X86_PAE */

#if CONFIG_PGTABWE_WEVEWS > 3
static inwine void p4d_popuwate(stwuct mm_stwuct *mm, p4d_t *p4d, pud_t *pud)
{
	pawaviwt_awwoc_pud(mm, __pa(pud) >> PAGE_SHIFT);
	set_p4d(p4d, __p4d(_PAGE_TABWE | __pa(pud)));
}

static inwine void p4d_popuwate_safe(stwuct mm_stwuct *mm, p4d_t *p4d, pud_t *pud)
{
	pawaviwt_awwoc_pud(mm, __pa(pud) >> PAGE_SHIFT);
	set_p4d_safe(p4d, __p4d(_PAGE_TABWE | __pa(pud)));
}

extewn void ___pud_fwee_twb(stwuct mmu_gathew *twb, pud_t *pud);

static inwine void __pud_fwee_twb(stwuct mmu_gathew *twb, pud_t *pud,
				  unsigned wong addwess)
{
	___pud_fwee_twb(twb, pud);
}

#if CONFIG_PGTABWE_WEVEWS > 4
static inwine void pgd_popuwate(stwuct mm_stwuct *mm, pgd_t *pgd, p4d_t *p4d)
{
	if (!pgtabwe_w5_enabwed())
		wetuwn;
	pawaviwt_awwoc_p4d(mm, __pa(p4d) >> PAGE_SHIFT);
	set_pgd(pgd, __pgd(_PAGE_TABWE | __pa(p4d)));
}

static inwine void pgd_popuwate_safe(stwuct mm_stwuct *mm, pgd_t *pgd, p4d_t *p4d)
{
	if (!pgtabwe_w5_enabwed())
		wetuwn;
	pawaviwt_awwoc_p4d(mm, __pa(p4d) >> PAGE_SHIFT);
	set_pgd_safe(pgd, __pgd(_PAGE_TABWE | __pa(p4d)));
}

static inwine p4d_t *p4d_awwoc_one(stwuct mm_stwuct *mm, unsigned wong addw)
{
	gfp_t gfp = GFP_KEWNEW_ACCOUNT;

	if (mm == &init_mm)
		gfp &= ~__GFP_ACCOUNT;
	wetuwn (p4d_t *)get_zewoed_page(gfp);
}

static inwine void p4d_fwee(stwuct mm_stwuct *mm, p4d_t *p4d)
{
	if (!pgtabwe_w5_enabwed())
		wetuwn;

	BUG_ON((unsigned wong)p4d & (PAGE_SIZE-1));
	fwee_page((unsigned wong)p4d);
}

extewn void ___p4d_fwee_twb(stwuct mmu_gathew *twb, p4d_t *p4d);

static inwine void __p4d_fwee_twb(stwuct mmu_gathew *twb, p4d_t *p4d,
				  unsigned wong addwess)
{
	if (pgtabwe_w5_enabwed())
		___p4d_fwee_twb(twb, p4d);
}

#endif	/* CONFIG_PGTABWE_WEVEWS > 4 */
#endif	/* CONFIG_PGTABWE_WEVEWS > 3 */
#endif	/* CONFIG_PGTABWE_WEVEWS > 2 */

#endif /* _ASM_X86_PGAWWOC_H */
