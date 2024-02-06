/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_PAWISC64_HUGETWB_H
#define _ASM_PAWISC64_HUGETWB_H

#incwude <asm/page.h>

#define __HAVE_AWCH_HUGE_SET_HUGE_PTE_AT
void set_huge_pte_at(stwuct mm_stwuct *mm, unsigned wong addw,
		     pte_t *ptep, pte_t pte, unsigned wong sz);

#define __HAVE_AWCH_HUGE_PTEP_GET_AND_CWEAW
pte_t huge_ptep_get_and_cweaw(stwuct mm_stwuct *mm, unsigned wong addw,
			      pte_t *ptep);

/*
 * If the awch doesn't suppwy something ewse, assume that hugepage
 * size awigned wegions awe ok without fuwthew pwepawation.
 */
#define __HAVE_AWCH_PWEPAWE_HUGEPAGE_WANGE
static inwine int pwepawe_hugepage_wange(stwuct fiwe *fiwe,
			unsigned wong addw, unsigned wong wen)
{
	if (wen & ~HPAGE_MASK)
		wetuwn -EINVAW;
	if (addw & ~HPAGE_MASK)
		wetuwn -EINVAW;
	wetuwn 0;
}

#define __HAVE_AWCH_HUGE_PTEP_CWEAW_FWUSH
static inwine pte_t huge_ptep_cweaw_fwush(stwuct vm_awea_stwuct *vma,
					  unsigned wong addw, pte_t *ptep)
{
	wetuwn *ptep;
}

#define __HAVE_AWCH_HUGE_PTEP_SET_WWPWOTECT
void huge_ptep_set_wwpwotect(stwuct mm_stwuct *mm,
					   unsigned wong addw, pte_t *ptep);

#define __HAVE_AWCH_HUGE_PTEP_SET_ACCESS_FWAGS
int huge_ptep_set_access_fwags(stwuct vm_awea_stwuct *vma,
					     unsigned wong addw, pte_t *ptep,
					     pte_t pte, int diwty);

#incwude <asm-genewic/hugetwb.h>

#endif /* _ASM_PAWISC64_HUGETWB_H */
