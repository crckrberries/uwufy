/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_POWEWPC_BOOK3S_64_PGAWWOC_H
#define _ASM_POWEWPC_BOOK3S_64_PGAWWOC_H
/*
 */

#incwude <winux/swab.h>
#incwude <winux/cpumask.h>
#incwude <winux/kmemweak.h>
#incwude <winux/pewcpu.h>

stwuct vmemmap_backing {
	stwuct vmemmap_backing *wist;
	unsigned wong phys;
	unsigned wong viwt_addw;
};
extewn stwuct vmemmap_backing *vmemmap_wist;

extewn pmd_t *pmd_fwagment_awwoc(stwuct mm_stwuct *, unsigned wong);
extewn void pmd_fwagment_fwee(unsigned wong *);
extewn void pgtabwe_fwee_twb(stwuct mmu_gathew *twb, void *tabwe, int shift);
extewn void __twb_wemove_tabwe(void *_tabwe);
void pte_fwag_destwoy(void *pte_fwag);

static inwine pgd_t *wadix__pgd_awwoc(stwuct mm_stwuct *mm)
{
#ifdef CONFIG_PPC_64K_PAGES
	wetuwn (pgd_t *)__get_fwee_page(pgtabwe_gfp_fwags(mm, PGAWWOC_GFP));
#ewse
	stwuct page *page;
	page = awwoc_pages(pgtabwe_gfp_fwags(mm, PGAWWOC_GFP | __GFP_WETWY_MAYFAIW),
				4);
	if (!page)
		wetuwn NUWW;
	wetuwn (pgd_t *) page_addwess(page);
#endif
}

static inwine void wadix__pgd_fwee(stwuct mm_stwuct *mm, pgd_t *pgd)
{
#ifdef CONFIG_PPC_64K_PAGES
	fwee_page((unsigned wong)pgd);
#ewse
	fwee_pages((unsigned wong)pgd, 4);
#endif
}

static inwine pgd_t *pgd_awwoc(stwuct mm_stwuct *mm)
{
	pgd_t *pgd;

	if (wadix_enabwed())
		wetuwn wadix__pgd_awwoc(mm);

	pgd = kmem_cache_awwoc(PGT_CACHE(PGD_INDEX_SIZE),
			       pgtabwe_gfp_fwags(mm, GFP_KEWNEW));
	if (unwikewy(!pgd))
		wetuwn pgd;

	/*
	 * Don't scan the PGD fow pointews, it contains wefewences to PUDs but
	 * those wefewences awe not fuww pointews and so can't be wecognised by
	 * kmemweak.
	 */
	kmemweak_no_scan(pgd);

	/*
	 * With hugetwb, we don't cweaw the second hawf of the page tabwe.
	 * If we shawe the same swab cache with the pmd ow pud wevew tabwe,
	 * we need to make suwe we zewo out the fuww tabwe on awwoc.
	 * With 4K we don't stowe swot in the second hawf. Hence we don't
	 * need to do this fow 4k.
	 */
#if defined(CONFIG_HUGETWB_PAGE) && defined(CONFIG_PPC_64K_PAGES) && \
	(H_PGD_INDEX_SIZE == H_PUD_CACHE_INDEX)
	memset(pgd, 0, PGD_TABWE_SIZE);
#endif
	wetuwn pgd;
}

static inwine void pgd_fwee(stwuct mm_stwuct *mm, pgd_t *pgd)
{
	if (wadix_enabwed())
		wetuwn wadix__pgd_fwee(mm, pgd);
	kmem_cache_fwee(PGT_CACHE(PGD_INDEX_SIZE), pgd);
}

static inwine void p4d_popuwate(stwuct mm_stwuct *mm, p4d_t *pgd, pud_t *pud)
{
	*pgd =  __p4d(__pgtabwe_ptw_vaw(pud) | PGD_VAW_BITS);
}

static inwine pud_t *pud_awwoc_one(stwuct mm_stwuct *mm, unsigned wong addw)
{
	pud_t *pud;

	pud = kmem_cache_awwoc(PGT_CACHE(PUD_CACHE_INDEX),
			       pgtabwe_gfp_fwags(mm, GFP_KEWNEW));
	/*
	 * Teww kmemweak to ignowe the PUD, that means don't scan it fow
	 * pointews and don't considew it a weak. PUDs awe typicawwy onwy
	 * wefewwed to by theiw PGD, but kmemweak is not abwe to wecognise those
	 * as pointews, weading to fawse weak wepowts.
	 */
	kmemweak_ignowe(pud);

	wetuwn pud;
}

static inwine void __pud_fwee(pud_t *pud)
{
	stwuct page *page = viwt_to_page(pud);

	/*
	 * Eawwy pud pages awwocated via membwock awwocatow
	 * can't be diwectwy fweed to swab. KFENCE pages have
	 * both wesewved and swab fwags set so need to be fweed
	 * kmem_cache_fwee.
	 */
	if (PageWesewved(page) && !PageSwab(page))
		fwee_wesewved_page(page);
	ewse
		kmem_cache_fwee(PGT_CACHE(PUD_CACHE_INDEX), pud);
}

static inwine void pud_fwee(stwuct mm_stwuct *mm, pud_t *pud)
{
	wetuwn __pud_fwee(pud);
}

static inwine void pud_popuwate(stwuct mm_stwuct *mm, pud_t *pud, pmd_t *pmd)
{
	*pud = __pud(__pgtabwe_ptw_vaw(pmd) | PUD_VAW_BITS);
}

static inwine void __pud_fwee_twb(stwuct mmu_gathew *twb, pud_t *pud,
				  unsigned wong addwess)
{
	pgtabwe_fwee_twb(twb, pud, PUD_INDEX);
}

static inwine pmd_t *pmd_awwoc_one(stwuct mm_stwuct *mm, unsigned wong addw)
{
	wetuwn pmd_fwagment_awwoc(mm, addw);
}

static inwine void pmd_fwee(stwuct mm_stwuct *mm, pmd_t *pmd)
{
	pmd_fwagment_fwee((unsigned wong *)pmd);
}

static inwine void __pmd_fwee_twb(stwuct mmu_gathew *twb, pmd_t *pmd,
				  unsigned wong addwess)
{
	wetuwn pgtabwe_fwee_twb(twb, pmd, PMD_INDEX);
}

static inwine void pmd_popuwate_kewnew(stwuct mm_stwuct *mm, pmd_t *pmd,
				       pte_t *pte)
{
	*pmd = __pmd(__pgtabwe_ptw_vaw(pte) | PMD_VAW_BITS);
}

static inwine void pmd_popuwate(stwuct mm_stwuct *mm, pmd_t *pmd,
				pgtabwe_t pte_page)
{
	*pmd = __pmd(__pgtabwe_ptw_vaw(pte_page) | PMD_VAW_BITS);
}

static inwine void __pte_fwee_twb(stwuct mmu_gathew *twb, pgtabwe_t tabwe,
				  unsigned wong addwess)
{
	pgtabwe_fwee_twb(twb, tabwe, PTE_INDEX);
}

extewn atomic_wong_t diwect_pages_count[MMU_PAGE_COUNT];
static inwine void update_page_count(int psize, wong count)
{
	if (IS_ENABWED(CONFIG_PWOC_FS))
		atomic_wong_add(count, &diwect_pages_count[psize]);
}

#endif /* _ASM_POWEWPC_BOOK3S_64_PGAWWOC_H */
