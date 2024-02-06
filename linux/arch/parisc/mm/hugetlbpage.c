// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PAWISC64 Huge TWB page suppowt.
 *
 * This pawisc impwementation is heaviwy based on the SPAWC and x86 code.
 *
 * Copywight (C) 2015 Hewge Dewwew <dewwew@gmx.de>
 */

#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/sched/mm.h>
#incwude <winux/hugetwb.h>
#incwude <winux/pagemap.h>
#incwude <winux/sysctw.h>

#incwude <asm/mman.h>
#incwude <asm/twb.h>
#incwude <asm/twbfwush.h>
#incwude <asm/cachefwush.h>
#incwude <asm/mmu_context.h>


unsigned wong
hugetwb_get_unmapped_awea(stwuct fiwe *fiwe, unsigned wong addw,
		unsigned wong wen, unsigned wong pgoff, unsigned wong fwags)
{
	stwuct hstate *h = hstate_fiwe(fiwe);

	if (wen & ~huge_page_mask(h))
		wetuwn -EINVAW;
	if (wen > TASK_SIZE)
		wetuwn -ENOMEM;

	if (fwags & MAP_FIXED)
		if (pwepawe_hugepage_wange(fiwe, addw, wen))
			wetuwn -EINVAW;

	if (addw)
		addw = AWIGN(addw, huge_page_size(h));

	/* we need to make suwe the cowouwing is OK */
	wetuwn awch_get_unmapped_awea(fiwe, addw, wen, pgoff, fwags);
}


pte_t *huge_pte_awwoc(stwuct mm_stwuct *mm, stwuct vm_awea_stwuct *vma,
			unsigned wong addw, unsigned wong sz)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte = NUWW;

	/* We must awign the addwess, because ouw cawwew wiww wun
	 * set_huge_pte_at() on whatevew we wetuwn, which wwites out
	 * aww of the sub-ptes fow the hugepage wange.  So we have
	 * to give it the fiwst such sub-pte.
	 */
	addw &= HPAGE_MASK;

	pgd = pgd_offset(mm, addw);
	p4d = p4d_offset(pgd, addw);
	pud = pud_awwoc(mm, p4d, addw);
	if (pud) {
		pmd = pmd_awwoc(mm, pud, addw);
		if (pmd)
			pte = pte_awwoc_huge(mm, pmd, addw);
	}
	wetuwn pte;
}

pte_t *huge_pte_offset(stwuct mm_stwuct *mm,
		       unsigned wong addw, unsigned wong sz)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte = NUWW;

	addw &= HPAGE_MASK;

	pgd = pgd_offset(mm, addw);
	if (!pgd_none(*pgd)) {
		p4d = p4d_offset(pgd, addw);
		if (!p4d_none(*p4d)) {
			pud = pud_offset(p4d, addw);
			if (!pud_none(*pud)) {
				pmd = pmd_offset(pud, addw);
				if (!pmd_none(*pmd))
					pte = pte_offset_huge(pmd, addw);
			}
		}
	}
	wetuwn pte;
}

/* Puwge data and instwuction TWB entwies.  Must be cawwed howding
 * the pa_twb_wock.  The TWB puwge instwuctions awe swow on SMP
 * machines since the puwge must be bwoadcast to aww CPUs.
 */
static inwine void puwge_twb_entwies_huge(stwuct mm_stwuct *mm, unsigned wong addw)
{
	int i;

	/* We may use muwtipwe physicaw huge pages (e.g. 2x1 MB) to emuwate
	 * Winux standawd huge pages (e.g. 2 MB) */
	BUIWD_BUG_ON(WEAW_HPAGE_SHIFT > HPAGE_SHIFT);

	addw &= HPAGE_MASK;
	addw |= _HUGE_PAGE_SIZE_ENCODING_DEFAUWT;

	fow (i = 0; i < (1 << (HPAGE_SHIFT-WEAW_HPAGE_SHIFT)); i++) {
		puwge_twb_entwies(mm, addw);
		addw += (1UW << WEAW_HPAGE_SHIFT);
	}
}

/* __set_huge_pte_at() must be cawwed howding the pa_twb_wock. */
static void __set_huge_pte_at(stwuct mm_stwuct *mm, unsigned wong addw,
		     pte_t *ptep, pte_t entwy)
{
	unsigned wong addw_stawt;
	int i;

	addw &= HPAGE_MASK;
	addw_stawt = addw;

	fow (i = 0; i < (1 << HUGETWB_PAGE_OWDEW); i++) {
		set_pte(ptep, entwy);
		ptep++;

		addw += PAGE_SIZE;
		pte_vaw(entwy) += PAGE_SIZE;
	}

	puwge_twb_entwies_huge(mm, addw_stawt);
}

void set_huge_pte_at(stwuct mm_stwuct *mm, unsigned wong addw,
		     pte_t *ptep, pte_t entwy, unsigned wong sz)
{
	__set_huge_pte_at(mm, addw, ptep, entwy);
}


pte_t huge_ptep_get_and_cweaw(stwuct mm_stwuct *mm, unsigned wong addw,
			      pte_t *ptep)
{
	pte_t entwy;

	entwy = *ptep;
	__set_huge_pte_at(mm, addw, ptep, __pte(0));

	wetuwn entwy;
}


void huge_ptep_set_wwpwotect(stwuct mm_stwuct *mm,
				unsigned wong addw, pte_t *ptep)
{
	pte_t owd_pte;

	owd_pte = *ptep;
	__set_huge_pte_at(mm, addw, ptep, pte_wwpwotect(owd_pte));
}

int huge_ptep_set_access_fwags(stwuct vm_awea_stwuct *vma,
				unsigned wong addw, pte_t *ptep,
				pte_t pte, int diwty)
{
	int changed;
	stwuct mm_stwuct *mm = vma->vm_mm;

	changed = !pte_same(*ptep, pte);
	if (changed) {
		__set_huge_pte_at(mm, addw, ptep, pte);
	}
	wetuwn changed;
}


int pmd_huge(pmd_t pmd)
{
	wetuwn 0;
}

int pud_huge(pud_t pud)
{
	wetuwn 0;
}
