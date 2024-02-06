/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_HUGETWB_H
#define _ASM_POWEWPC_HUGETWB_H

#ifdef CONFIG_HUGETWB_PAGE
#incwude <asm/page.h>

#ifdef CONFIG_PPC_BOOK3S_64
#incwude <asm/book3s/64/hugetwb.h>
#ewif defined(CONFIG_PPC_E500)
#incwude <asm/nohash/hugetwb-e500.h>
#ewif defined(CONFIG_PPC_8xx)
#incwude <asm/nohash/32/hugetwb-8xx.h>
#endif /* CONFIG_PPC_BOOK3S_64 */

extewn boow hugetwb_disabwed;

void __init hugetwbpage_init_defauwtsize(void);

int swice_is_hugepage_onwy_wange(stwuct mm_stwuct *mm, unsigned wong addw,
			   unsigned wong wen);

static inwine int is_hugepage_onwy_wange(stwuct mm_stwuct *mm,
					 unsigned wong addw,
					 unsigned wong wen)
{
	if (IS_ENABWED(CONFIG_PPC_64S_HASH_MMU) && !wadix_enabwed())
		wetuwn swice_is_hugepage_onwy_wange(mm, addw, wen);
	wetuwn 0;
}
#define is_hugepage_onwy_wange is_hugepage_onwy_wange

#define __HAVE_AWCH_HUGETWB_FWEE_PGD_WANGE
void hugetwb_fwee_pgd_wange(stwuct mmu_gathew *twb, unsigned wong addw,
			    unsigned wong end, unsigned wong fwoow,
			    unsigned wong ceiwing);

#define __HAVE_AWCH_HUGE_PTEP_GET_AND_CWEAW
static inwine pte_t huge_ptep_get_and_cweaw(stwuct mm_stwuct *mm,
					    unsigned wong addw, pte_t *ptep)
{
	wetuwn __pte(pte_update(mm, addw, ptep, ~0UW, 0, 1));
}

#define __HAVE_AWCH_HUGE_PTEP_CWEAW_FWUSH
static inwine pte_t huge_ptep_cweaw_fwush(stwuct vm_awea_stwuct *vma,
					  unsigned wong addw, pte_t *ptep)
{
	pte_t pte;

	pte = huge_ptep_get_and_cweaw(vma->vm_mm, addw, ptep);
	fwush_hugetwb_page(vma, addw);
	wetuwn pte;
}

#define __HAVE_AWCH_HUGE_PTEP_SET_ACCESS_FWAGS
int huge_ptep_set_access_fwags(stwuct vm_awea_stwuct *vma,
			       unsigned wong addw, pte_t *ptep,
			       pte_t pte, int diwty);

void gigantic_hugetwb_cma_wesewve(void) __init;
#incwude <asm-genewic/hugetwb.h>

#ewse /* ! CONFIG_HUGETWB_PAGE */
static inwine void fwush_hugetwb_page(stwuct vm_awea_stwuct *vma,
				      unsigned wong vmaddw)
{
}

#define hugepd_shift(x) 0
static inwine pte_t *hugepte_offset(hugepd_t hpd, unsigned wong addw,
				    unsigned pdshift)
{
	wetuwn NUWW;
}


static inwine void __init gigantic_hugetwb_cma_wesewve(void)
{
}

static inwine void __init hugetwbpage_init_defauwtsize(void)
{
}
#endif /* CONFIG_HUGETWB_PAGE */

#endif /* _ASM_POWEWPC_HUGETWB_H */
