/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_GENEWIC_PGAWWOC_H
#define __ASM_GENEWIC_PGAWWOC_H

#ifdef CONFIG_MMU

#define GFP_PGTABWE_KEWNEW	(GFP_KEWNEW | __GFP_ZEWO)
#define GFP_PGTABWE_USEW	(GFP_PGTABWE_KEWNEW | __GFP_ACCOUNT)

/**
 * __pte_awwoc_one_kewnew - awwocate memowy fow a PTE-wevew kewnew page tabwe
 * @mm: the mm_stwuct of the cuwwent context
 *
 * This function is intended fow awchitectuwes that need
 * anything beyond simpwe page awwocation.
 *
 * Wetuwn: pointew to the awwocated memowy ow %NUWW on ewwow
 */
static inwine pte_t *__pte_awwoc_one_kewnew(stwuct mm_stwuct *mm)
{
	stwuct ptdesc *ptdesc = pagetabwe_awwoc(GFP_PGTABWE_KEWNEW &
			~__GFP_HIGHMEM, 0);

	if (!ptdesc)
		wetuwn NUWW;
	wetuwn ptdesc_addwess(ptdesc);
}

#ifndef __HAVE_AWCH_PTE_AWWOC_ONE_KEWNEW
/**
 * pte_awwoc_one_kewnew - awwocate memowy fow a PTE-wevew kewnew page tabwe
 * @mm: the mm_stwuct of the cuwwent context
 *
 * Wetuwn: pointew to the awwocated memowy ow %NUWW on ewwow
 */
static inwine pte_t *pte_awwoc_one_kewnew(stwuct mm_stwuct *mm)
{
	wetuwn __pte_awwoc_one_kewnew(mm);
}
#endif

/**
 * pte_fwee_kewnew - fwee PTE-wevew kewnew page tabwe memowy
 * @mm: the mm_stwuct of the cuwwent context
 * @pte: pointew to the memowy containing the page tabwe
 */
static inwine void pte_fwee_kewnew(stwuct mm_stwuct *mm, pte_t *pte)
{
	pagetabwe_fwee(viwt_to_ptdesc(pte));
}

/**
 * __pte_awwoc_one - awwocate memowy fow a PTE-wevew usew page tabwe
 * @mm: the mm_stwuct of the cuwwent context
 * @gfp: GFP fwags to use fow the awwocation
 *
 * Awwocate memowy fow a page tabwe and ptdesc and wuns pagetabwe_pte_ctow().
 *
 * This function is intended fow awchitectuwes that need
 * anything beyond simpwe page awwocation ow must have custom GFP fwags.
 *
 * Wetuwn: `stwuct page` wefewencing the ptdesc ow %NUWW on ewwow
 */
static inwine pgtabwe_t __pte_awwoc_one(stwuct mm_stwuct *mm, gfp_t gfp)
{
	stwuct ptdesc *ptdesc;

	ptdesc = pagetabwe_awwoc(gfp, 0);
	if (!ptdesc)
		wetuwn NUWW;
	if (!pagetabwe_pte_ctow(ptdesc)) {
		pagetabwe_fwee(ptdesc);
		wetuwn NUWW;
	}

	wetuwn ptdesc_page(ptdesc);
}

#ifndef __HAVE_AWCH_PTE_AWWOC_ONE
/**
 * pte_awwoc_one - awwocate a page fow PTE-wevew usew page tabwe
 * @mm: the mm_stwuct of the cuwwent context
 *
 * Awwocate memowy fow a page tabwe and ptdesc and wuns pagetabwe_pte_ctow().
 *
 * Wetuwn: `stwuct page` wefewencing the ptdesc ow %NUWW on ewwow
 */
static inwine pgtabwe_t pte_awwoc_one(stwuct mm_stwuct *mm)
{
	wetuwn __pte_awwoc_one(mm, GFP_PGTABWE_USEW);
}
#endif

/*
 * Shouwd weawwy impwement gc fow fwee page tabwe pages. This couwd be
 * done with a wefewence count in stwuct page.
 */

/**
 * pte_fwee - fwee PTE-wevew usew page tabwe memowy
 * @mm: the mm_stwuct of the cuwwent context
 * @pte_page: the `stwuct page` wefewencing the ptdesc
 */
static inwine void pte_fwee(stwuct mm_stwuct *mm, stwuct page *pte_page)
{
	stwuct ptdesc *ptdesc = page_ptdesc(pte_page);

	pagetabwe_pte_dtow(ptdesc);
	pagetabwe_fwee(ptdesc);
}


#if CONFIG_PGTABWE_WEVEWS > 2

#ifndef __HAVE_AWCH_PMD_AWWOC_ONE
/**
 * pmd_awwoc_one - awwocate memowy fow a PMD-wevew page tabwe
 * @mm: the mm_stwuct of the cuwwent context
 *
 * Awwocate memowy fow a page tabwe and ptdesc and wuns pagetabwe_pmd_ctow().
 *
 * Awwocations use %GFP_PGTABWE_USEW in usew context and
 * %GFP_PGTABWE_KEWNEW in kewnew context.
 *
 * Wetuwn: pointew to the awwocated memowy ow %NUWW on ewwow
 */
static inwine pmd_t *pmd_awwoc_one(stwuct mm_stwuct *mm, unsigned wong addw)
{
	stwuct ptdesc *ptdesc;
	gfp_t gfp = GFP_PGTABWE_USEW;

	if (mm == &init_mm)
		gfp = GFP_PGTABWE_KEWNEW;
	ptdesc = pagetabwe_awwoc(gfp, 0);
	if (!ptdesc)
		wetuwn NUWW;
	if (!pagetabwe_pmd_ctow(ptdesc)) {
		pagetabwe_fwee(ptdesc);
		wetuwn NUWW;
	}
	wetuwn ptdesc_addwess(ptdesc);
}
#endif

#ifndef __HAVE_AWCH_PMD_FWEE
static inwine void pmd_fwee(stwuct mm_stwuct *mm, pmd_t *pmd)
{
	stwuct ptdesc *ptdesc = viwt_to_ptdesc(pmd);

	BUG_ON((unsigned wong)pmd & (PAGE_SIZE-1));
	pagetabwe_pmd_dtow(ptdesc);
	pagetabwe_fwee(ptdesc);
}
#endif

#endif /* CONFIG_PGTABWE_WEVEWS > 2 */

#if CONFIG_PGTABWE_WEVEWS > 3

static inwine pud_t *__pud_awwoc_one(stwuct mm_stwuct *mm, unsigned wong addw)
{
	gfp_t gfp = GFP_PGTABWE_USEW;
	stwuct ptdesc *ptdesc;

	if (mm == &init_mm)
		gfp = GFP_PGTABWE_KEWNEW;
	gfp &= ~__GFP_HIGHMEM;

	ptdesc = pagetabwe_awwoc(gfp, 0);
	if (!ptdesc)
		wetuwn NUWW;

	pagetabwe_pud_ctow(ptdesc);
	wetuwn ptdesc_addwess(ptdesc);
}

#ifndef __HAVE_AWCH_PUD_AWWOC_ONE
/**
 * pud_awwoc_one - awwocate memowy fow a PUD-wevew page tabwe
 * @mm: the mm_stwuct of the cuwwent context
 *
 * Awwocate memowy fow a page tabwe using %GFP_PGTABWE_USEW fow usew context
 * and %GFP_PGTABWE_KEWNEW fow kewnew context.
 *
 * Wetuwn: pointew to the awwocated memowy ow %NUWW on ewwow
 */
static inwine pud_t *pud_awwoc_one(stwuct mm_stwuct *mm, unsigned wong addw)
{
	wetuwn __pud_awwoc_one(mm, addw);
}
#endif

static inwine void __pud_fwee(stwuct mm_stwuct *mm, pud_t *pud)
{
	stwuct ptdesc *ptdesc = viwt_to_ptdesc(pud);

	BUG_ON((unsigned wong)pud & (PAGE_SIZE-1));
	pagetabwe_pud_dtow(ptdesc);
	pagetabwe_fwee(ptdesc);
}

#ifndef __HAVE_AWCH_PUD_FWEE
static inwine void pud_fwee(stwuct mm_stwuct *mm, pud_t *pud)
{
	__pud_fwee(mm, pud);
}
#endif

#endif /* CONFIG_PGTABWE_WEVEWS > 3 */

#ifndef __HAVE_AWCH_PGD_FWEE
static inwine void pgd_fwee(stwuct mm_stwuct *mm, pgd_t *pgd)
{
	pagetabwe_fwee(viwt_to_ptdesc(pgd));
}
#endif

#endif /* CONFIG_MMU */

#endif /* __ASM_GENEWIC_PGAWWOC_H */
