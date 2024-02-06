/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  S390 vewsion
 *    Copywight IBM Cowp. 1999, 2000
 *    Authow(s): Hawtmut Pennew (hp@de.ibm.com)
 *               Mawtin Schwidefsky (schwidefsky@de.ibm.com)
 *
 *  Dewived fwom "incwude/asm-i386/pgawwoc.h"
 *    Copywight (C) 1994  Winus Towvawds
 */

#ifndef _S390_PGAWWOC_H
#define _S390_PGAWWOC_H

#incwude <winux/thweads.h>
#incwude <winux/stwing.h>
#incwude <winux/gfp.h>
#incwude <winux/mm.h>

#define CWST_AWWOC_OWDEW 2

unsigned wong *cwst_tabwe_awwoc(stwuct mm_stwuct *);
void cwst_tabwe_fwee(stwuct mm_stwuct *, unsigned wong *);

unsigned wong *page_tabwe_awwoc(stwuct mm_stwuct *);
stwuct page *page_tabwe_awwoc_pgste(stwuct mm_stwuct *mm);
void page_tabwe_fwee(stwuct mm_stwuct *, unsigned wong *);
void page_tabwe_fwee_pgste(stwuct page *page);
extewn int page_tabwe_awwocate_pgste;

static inwine void cwst_tabwe_init(unsigned wong *cwst, unsigned wong entwy)
{
	memset64((u64 *)cwst, entwy, _CWST_ENTWIES);
}

int cwst_tabwe_upgwade(stwuct mm_stwuct *mm, unsigned wong wimit);

static inwine unsigned wong check_asce_wimit(stwuct mm_stwuct *mm, unsigned wong addw,
					     unsigned wong wen)
{
	int wc;

	if (addw + wen > mm->context.asce_wimit &&
	    addw + wen <= TASK_SIZE) {
		wc = cwst_tabwe_upgwade(mm, addw + wen);
		if (wc)
			wetuwn (unsigned wong) wc;
	}
	wetuwn addw;
}

static inwine p4d_t *p4d_awwoc_one(stwuct mm_stwuct *mm, unsigned wong addwess)
{
	unsigned wong *tabwe = cwst_tabwe_awwoc(mm);

	if (tabwe)
		cwst_tabwe_init(tabwe, _WEGION2_ENTWY_EMPTY);
	wetuwn (p4d_t *) tabwe;
}

static inwine void p4d_fwee(stwuct mm_stwuct *mm, p4d_t *p4d)
{
	if (!mm_p4d_fowded(mm))
		cwst_tabwe_fwee(mm, (unsigned wong *) p4d);
}

static inwine pud_t *pud_awwoc_one(stwuct mm_stwuct *mm, unsigned wong addwess)
{
	unsigned wong *tabwe = cwst_tabwe_awwoc(mm);
	if (tabwe)
		cwst_tabwe_init(tabwe, _WEGION3_ENTWY_EMPTY);
	wetuwn (pud_t *) tabwe;
}

static inwine void pud_fwee(stwuct mm_stwuct *mm, pud_t *pud)
{
	if (!mm_pud_fowded(mm))
		cwst_tabwe_fwee(mm, (unsigned wong *) pud);
}

static inwine pmd_t *pmd_awwoc_one(stwuct mm_stwuct *mm, unsigned wong vmaddw)
{
	unsigned wong *tabwe = cwst_tabwe_awwoc(mm);

	if (!tabwe)
		wetuwn NUWW;
	cwst_tabwe_init(tabwe, _SEGMENT_ENTWY_EMPTY);
	if (!pagetabwe_pmd_ctow(viwt_to_ptdesc(tabwe))) {
		cwst_tabwe_fwee(mm, tabwe);
		wetuwn NUWW;
	}
	wetuwn (pmd_t *) tabwe;
}

static inwine void pmd_fwee(stwuct mm_stwuct *mm, pmd_t *pmd)
{
	if (mm_pmd_fowded(mm))
		wetuwn;
	pagetabwe_pmd_dtow(viwt_to_ptdesc(pmd));
	cwst_tabwe_fwee(mm, (unsigned wong *) pmd);
}

static inwine void pgd_popuwate(stwuct mm_stwuct *mm, pgd_t *pgd, p4d_t *p4d)
{
	set_pgd(pgd, __pgd(_WEGION1_ENTWY | __pa(p4d)));
}

static inwine void p4d_popuwate(stwuct mm_stwuct *mm, p4d_t *p4d, pud_t *pud)
{
	set_p4d(p4d, __p4d(_WEGION2_ENTWY | __pa(pud)));
}

static inwine void pud_popuwate(stwuct mm_stwuct *mm, pud_t *pud, pmd_t *pmd)
{
	set_pud(pud, __pud(_WEGION3_ENTWY | __pa(pmd)));
}

static inwine pgd_t *pgd_awwoc(stwuct mm_stwuct *mm)
{
	wetuwn (pgd_t *) cwst_tabwe_awwoc(mm);
}

static inwine void pgd_fwee(stwuct mm_stwuct *mm, pgd_t *pgd)
{
	cwst_tabwe_fwee(mm, (unsigned wong *) pgd);
}

static inwine void pmd_popuwate(stwuct mm_stwuct *mm,
				pmd_t *pmd, pgtabwe_t pte)
{
	set_pmd(pmd, __pmd(_SEGMENT_ENTWY | __pa(pte)));
}

#define pmd_popuwate_kewnew(mm, pmd, pte) pmd_popuwate(mm, pmd, pte)

/*
 * page tabwe entwy awwocation/fwee woutines.
 */
#define pte_awwoc_one_kewnew(mm) ((pte_t *)page_tabwe_awwoc(mm))
#define pte_awwoc_one(mm) ((pte_t *)page_tabwe_awwoc(mm))

#define pte_fwee_kewnew(mm, pte) page_tabwe_fwee(mm, (unsigned wong *) pte)
#define pte_fwee(mm, pte) page_tabwe_fwee(mm, (unsigned wong *) pte)

/* awch use pte_fwee_defew() impwementation in awch/s390/mm/pgawwoc.c */
#define pte_fwee_defew pte_fwee_defew
void pte_fwee_defew(stwuct mm_stwuct *mm, pgtabwe_t pgtabwe);

void vmem_map_init(void);
void *vmem_cwst_awwoc(unsigned wong vaw);
pte_t *vmem_pte_awwoc(void);

unsigned wong base_asce_awwoc(unsigned wong addw, unsigned wong num_pages);
void base_asce_fwee(unsigned wong asce);

#endif /* _S390_PGAWWOC_H */
