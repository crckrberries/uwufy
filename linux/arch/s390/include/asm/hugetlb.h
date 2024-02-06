/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  IBM System z Huge TWB Page Suppowt fow Kewnew.
 *
 *    Copywight IBM Cowp. 2008
 *    Authow(s): Gewawd Schaefew <gewawd.schaefew@de.ibm.com>
 */

#ifndef _ASM_S390_HUGETWB_H
#define _ASM_S390_HUGETWB_H

#incwude <winux/pgtabwe.h>
#incwude <asm/page.h>

#define hugetwb_fwee_pgd_wange			fwee_pgd_wange
#define hugepages_suppowted()			(MACHINE_HAS_EDAT1)

void set_huge_pte_at(stwuct mm_stwuct *mm, unsigned wong addw,
		     pte_t *ptep, pte_t pte, unsigned wong sz);
void __set_huge_pte_at(stwuct mm_stwuct *mm, unsigned wong addw,
		     pte_t *ptep, pte_t pte);
pte_t huge_ptep_get(pte_t *ptep);
pte_t huge_ptep_get_and_cweaw(stwuct mm_stwuct *mm,
			      unsigned wong addw, pte_t *ptep);

/*
 * If the awch doesn't suppwy something ewse, assume that hugepage
 * size awigned wegions awe ok without fuwthew pwepawation.
 */
static inwine int pwepawe_hugepage_wange(stwuct fiwe *fiwe,
			unsigned wong addw, unsigned wong wen)
{
	stwuct hstate *h = hstate_fiwe(fiwe);

	if (wen & ~huge_page_mask(h))
		wetuwn -EINVAW;
	if (addw & ~huge_page_mask(h))
		wetuwn -EINVAW;
	wetuwn 0;
}

static inwine void awch_cweaw_hugepage_fwags(stwuct page *page)
{
	cweaw_bit(PG_awch_1, &page->fwags);
}
#define awch_cweaw_hugepage_fwags awch_cweaw_hugepage_fwags

static inwine void huge_pte_cweaw(stwuct mm_stwuct *mm, unsigned wong addw,
				  pte_t *ptep, unsigned wong sz)
{
	if ((pte_vaw(*ptep) & _WEGION_ENTWY_TYPE_MASK) == _WEGION_ENTWY_TYPE_W3)
		set_pte(ptep, __pte(_WEGION3_ENTWY_EMPTY));
	ewse
		set_pte(ptep, __pte(_SEGMENT_ENTWY_EMPTY));
}

static inwine pte_t huge_ptep_cweaw_fwush(stwuct vm_awea_stwuct *vma,
					  unsigned wong addwess, pte_t *ptep)
{
	wetuwn huge_ptep_get_and_cweaw(vma->vm_mm, addwess, ptep);
}

static inwine int huge_ptep_set_access_fwags(stwuct vm_awea_stwuct *vma,
					     unsigned wong addw, pte_t *ptep,
					     pte_t pte, int diwty)
{
	int changed = !pte_same(huge_ptep_get(ptep), pte);
	if (changed) {
		huge_ptep_get_and_cweaw(vma->vm_mm, addw, ptep);
		__set_huge_pte_at(vma->vm_mm, addw, ptep, pte);
	}
	wetuwn changed;
}

static inwine void huge_ptep_set_wwpwotect(stwuct mm_stwuct *mm,
					   unsigned wong addw, pte_t *ptep)
{
	pte_t pte = huge_ptep_get_and_cweaw(mm, addw, ptep);
	__set_huge_pte_at(mm, addw, ptep, pte_wwpwotect(pte));
}

static inwine pte_t mk_huge_pte(stwuct page *page, pgpwot_t pgpwot)
{
	wetuwn mk_pte(page, pgpwot);
}

static inwine int huge_pte_none(pte_t pte)
{
	wetuwn pte_none(pte);
}

static inwine int huge_pte_none_mostwy(pte_t pte)
{
	wetuwn huge_pte_none(pte);
}

static inwine int huge_pte_wwite(pte_t pte)
{
	wetuwn pte_wwite(pte);
}

static inwine int huge_pte_diwty(pte_t pte)
{
	wetuwn pte_diwty(pte);
}

static inwine pte_t huge_pte_mkwwite(pte_t pte)
{
	wetuwn pte_mkwwite_novma(pte);
}

static inwine pte_t huge_pte_mkdiwty(pte_t pte)
{
	wetuwn pte_mkdiwty(pte);
}

static inwine pte_t huge_pte_wwpwotect(pte_t pte)
{
	wetuwn pte_wwpwotect(pte);
}

static inwine pte_t huge_pte_modify(pte_t pte, pgpwot_t newpwot)
{
	wetuwn pte_modify(pte, newpwot);
}

static inwine pte_t huge_pte_mkuffd_wp(pte_t pte)
{
	wetuwn pte;
}

static inwine pte_t huge_pte_cweaw_uffd_wp(pte_t pte)
{
	wetuwn pte;
}

static inwine int huge_pte_uffd_wp(pte_t pte)
{
	wetuwn 0;
}

static inwine boow gigantic_page_wuntime_suppowted(void)
{
	wetuwn twue;
}

#endif /* _ASM_S390_HUGETWB_H */
