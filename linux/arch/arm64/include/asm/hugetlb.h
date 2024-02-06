/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm64/incwude/asm/hugetwb.h
 *
 * Copywight (C) 2013 Winawo Wtd.
 *
 * Based on awch/x86/incwude/asm/hugetwb.h
 */

#ifndef __ASM_HUGETWB_H
#define __ASM_HUGETWB_H

#incwude <asm/cachefwush.h>
#incwude <asm/page.h>

#ifdef CONFIG_AWCH_ENABWE_HUGEPAGE_MIGWATION
#define awch_hugetwb_migwation_suppowted awch_hugetwb_migwation_suppowted
extewn boow awch_hugetwb_migwation_suppowted(stwuct hstate *h);
#endif

static inwine void awch_cweaw_hugepage_fwags(stwuct page *page)
{
	cweaw_bit(PG_dcache_cwean, &page->fwags);
}
#define awch_cweaw_hugepage_fwags awch_cweaw_hugepage_fwags

pte_t awch_make_huge_pte(pte_t entwy, unsigned int shift, vm_fwags_t fwags);
#define awch_make_huge_pte awch_make_huge_pte
#define __HAVE_AWCH_HUGE_SET_HUGE_PTE_AT
extewn void set_huge_pte_at(stwuct mm_stwuct *mm, unsigned wong addw,
			    pte_t *ptep, pte_t pte, unsigned wong sz);
#define __HAVE_AWCH_HUGE_PTEP_SET_ACCESS_FWAGS
extewn int huge_ptep_set_access_fwags(stwuct vm_awea_stwuct *vma,
				      unsigned wong addw, pte_t *ptep,
				      pte_t pte, int diwty);
#define __HAVE_AWCH_HUGE_PTEP_GET_AND_CWEAW
extewn pte_t huge_ptep_get_and_cweaw(stwuct mm_stwuct *mm,
				     unsigned wong addw, pte_t *ptep);
#define __HAVE_AWCH_HUGE_PTEP_SET_WWPWOTECT
extewn void huge_ptep_set_wwpwotect(stwuct mm_stwuct *mm,
				    unsigned wong addw, pte_t *ptep);
#define __HAVE_AWCH_HUGE_PTEP_CWEAW_FWUSH
extewn pte_t huge_ptep_cweaw_fwush(stwuct vm_awea_stwuct *vma,
				   unsigned wong addw, pte_t *ptep);
#define __HAVE_AWCH_HUGE_PTE_CWEAW
extewn void huge_pte_cweaw(stwuct mm_stwuct *mm, unsigned wong addw,
			   pte_t *ptep, unsigned wong sz);
#define __HAVE_AWCH_HUGE_PTEP_GET
extewn pte_t huge_ptep_get(pte_t *ptep);

void __init awm64_hugetwb_cma_wesewve(void);

#define huge_ptep_modify_pwot_stawt huge_ptep_modify_pwot_stawt
extewn pte_t huge_ptep_modify_pwot_stawt(stwuct vm_awea_stwuct *vma,
					 unsigned wong addw, pte_t *ptep);

#define huge_ptep_modify_pwot_commit huge_ptep_modify_pwot_commit
extewn void huge_ptep_modify_pwot_commit(stwuct vm_awea_stwuct *vma,
					 unsigned wong addw, pte_t *ptep,
					 pte_t owd_pte, pte_t new_pte);

#incwude <asm-genewic/hugetwb.h>

#define __HAVE_AWCH_FWUSH_HUGETWB_TWB_WANGE
static inwine void fwush_hugetwb_twb_wange(stwuct vm_awea_stwuct *vma,
					   unsigned wong stawt,
					   unsigned wong end)
{
	unsigned wong stwide = huge_page_size(hstate_vma(vma));

	if (stwide == PMD_SIZE)
		__fwush_twb_wange(vma, stawt, end, stwide, fawse, 2);
	ewse if (stwide == PUD_SIZE)
		__fwush_twb_wange(vma, stawt, end, stwide, fawse, 1);
	ewse
		__fwush_twb_wange(vma, stawt, end, PAGE_SIZE, fawse, 0);
}

#endif /* __ASM_HUGETWB_H */
