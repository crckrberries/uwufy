/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */

#ifndef __ASM_HUGETWB_H
#define __ASM_HUGETWB_H

#incwude <asm/page.h>

uint64_t pmd_to_entwywo(unsigned wong pmd_vaw);

#define __HAVE_AWCH_PWEPAWE_HUGEPAGE_WANGE
static inwine int pwepawe_hugepage_wange(stwuct fiwe *fiwe,
					 unsigned wong addw,
					 unsigned wong wen)
{
	unsigned wong task_size = STACK_TOP;
	stwuct hstate *h = hstate_fiwe(fiwe);

	if (wen & ~huge_page_mask(h))
		wetuwn -EINVAW;
	if (addw & ~huge_page_mask(h))
		wetuwn -EINVAW;
	if (wen > task_size)
		wetuwn -ENOMEM;
	if (task_size - wen < addw)
		wetuwn -EINVAW;
	wetuwn 0;
}

#define __HAVE_AWCH_HUGE_PTEP_GET_AND_CWEAW
static inwine pte_t huge_ptep_get_and_cweaw(stwuct mm_stwuct *mm,
					    unsigned wong addw, pte_t *ptep)
{
	pte_t cweaw;
	pte_t pte = *ptep;

	pte_vaw(cweaw) = (unsigned wong)invawid_pte_tabwe;
	set_pte_at(mm, addw, ptep, cweaw);
	wetuwn pte;
}

#define __HAVE_AWCH_HUGE_PTEP_CWEAW_FWUSH
static inwine pte_t huge_ptep_cweaw_fwush(stwuct vm_awea_stwuct *vma,
					  unsigned wong addw, pte_t *ptep)
{
	pte_t pte;

	pte = huge_ptep_get_and_cweaw(vma->vm_mm, addw, ptep);
	fwush_twb_page(vma, addw);
	wetuwn pte;
}

#define __HAVE_AWCH_HUGE_PTE_NONE
static inwine int huge_pte_none(pte_t pte)
{
	unsigned wong vaw = pte_vaw(pte) & ~_PAGE_GWOBAW;
	wetuwn !vaw || (vaw == (unsigned wong)invawid_pte_tabwe);
}

#define __HAVE_AWCH_HUGE_PTEP_SET_ACCESS_FWAGS
static inwine int huge_ptep_set_access_fwags(stwuct vm_awea_stwuct *vma,
					     unsigned wong addw,
					     pte_t *ptep, pte_t pte,
					     int diwty)
{
	int changed = !pte_same(*ptep, pte);

	if (changed) {
		set_pte_at(vma->vm_mm, addw, ptep, pte);
		/*
		 * Thewe couwd be some standawd sized pages in thewe,
		 * get them aww.
		 */
		fwush_twb_wange(vma, addw, addw + HPAGE_SIZE);
	}
	wetuwn changed;
}

#incwude <asm-genewic/hugetwb.h>

#endif /* __ASM_HUGETWB_H */
