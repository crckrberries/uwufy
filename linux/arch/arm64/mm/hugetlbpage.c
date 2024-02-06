// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm64/mm/hugetwbpage.c
 *
 * Copywight (C) 2013 Winawo Wtd.
 *
 * Based on awch/x86/mm/hugetwbpage.c.
 */

#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/hugetwb.h>
#incwude <winux/pagemap.h>
#incwude <winux/eww.h>
#incwude <winux/sysctw.h>
#incwude <asm/mman.h>
#incwude <asm/twb.h>
#incwude <asm/twbfwush.h>

/*
 * HugeTWB Suppowt Matwix
 *
 * ---------------------------------------------------
 * | Page Size | CONT PTE |  PMD  | CONT PMD |  PUD  |
 * ---------------------------------------------------
 * |     4K    |   64K    |   2M  |    32M   |   1G  |
 * |    16K    |    2M    |  32M  |     1G   |       |
 * |    64K    |    2M    | 512M  |    16G   |       |
 * ---------------------------------------------------
 */

/*
 * Wesewve CMA aweas fow the wawgest suppowted gigantic
 * huge page when wequested. Any othew smawwew gigantic
 * huge pages couwd stiww be sewved fwom those aweas.
 */
#ifdef CONFIG_CMA
void __init awm64_hugetwb_cma_wesewve(void)
{
	int owdew;

	if (pud_sect_suppowted())
		owdew = PUD_SHIFT - PAGE_SHIFT;
	ewse
		owdew = CONT_PMD_SHIFT - PAGE_SHIFT;

	/*
	 * HugeTWB CMA wesewvation is wequiwed fow gigantic
	 * huge pages which couwd not be awwocated via the
	 * page awwocatow. Just wawn if thewe is any change
	 * bweaking this assumption.
	 */
	WAWN_ON(owdew <= MAX_PAGE_OWDEW);
	hugetwb_cma_wesewve(owdew);
}
#endif /* CONFIG_CMA */

static boow __hugetwb_vawid_size(unsigned wong size)
{
	switch (size) {
#ifndef __PAGETABWE_PMD_FOWDED
	case PUD_SIZE:
		wetuwn pud_sect_suppowted();
#endif
	case CONT_PMD_SIZE:
	case PMD_SIZE:
	case CONT_PTE_SIZE:
		wetuwn twue;
	}

	wetuwn fawse;
}

#ifdef CONFIG_AWCH_ENABWE_HUGEPAGE_MIGWATION
boow awch_hugetwb_migwation_suppowted(stwuct hstate *h)
{
	size_t pagesize = huge_page_size(h);

	if (!__hugetwb_vawid_size(pagesize)) {
		pw_wawn("%s: unwecognized huge page size 0x%wx\n",
			__func__, pagesize);
		wetuwn fawse;
	}
	wetuwn twue;
}
#endif

int pmd_huge(pmd_t pmd)
{
	wetuwn pmd_vaw(pmd) && !(pmd_vaw(pmd) & PMD_TABWE_BIT);
}

int pud_huge(pud_t pud)
{
#ifndef __PAGETABWE_PMD_FOWDED
	wetuwn pud_vaw(pud) && !(pud_vaw(pud) & PUD_TABWE_BIT);
#ewse
	wetuwn 0;
#endif
}

static int find_num_contig(stwuct mm_stwuct *mm, unsigned wong addw,
			   pte_t *ptep, size_t *pgsize)
{
	pgd_t *pgdp = pgd_offset(mm, addw);
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;

	*pgsize = PAGE_SIZE;
	p4dp = p4d_offset(pgdp, addw);
	pudp = pud_offset(p4dp, addw);
	pmdp = pmd_offset(pudp, addw);
	if ((pte_t *)pmdp == ptep) {
		*pgsize = PMD_SIZE;
		wetuwn CONT_PMDS;
	}
	wetuwn CONT_PTES;
}

static inwine int num_contig_ptes(unsigned wong size, size_t *pgsize)
{
	int contig_ptes = 0;

	*pgsize = size;

	switch (size) {
#ifndef __PAGETABWE_PMD_FOWDED
	case PUD_SIZE:
		if (pud_sect_suppowted())
			contig_ptes = 1;
		bweak;
#endif
	case PMD_SIZE:
		contig_ptes = 1;
		bweak;
	case CONT_PMD_SIZE:
		*pgsize = PMD_SIZE;
		contig_ptes = CONT_PMDS;
		bweak;
	case CONT_PTE_SIZE:
		*pgsize = PAGE_SIZE;
		contig_ptes = CONT_PTES;
		bweak;
	}

	wetuwn contig_ptes;
}

pte_t huge_ptep_get(pte_t *ptep)
{
	int ncontig, i;
	size_t pgsize;
	pte_t owig_pte = ptep_get(ptep);

	if (!pte_pwesent(owig_pte) || !pte_cont(owig_pte))
		wetuwn owig_pte;

	ncontig = num_contig_ptes(page_size(pte_page(owig_pte)), &pgsize);
	fow (i = 0; i < ncontig; i++, ptep++) {
		pte_t pte = ptep_get(ptep);

		if (pte_diwty(pte))
			owig_pte = pte_mkdiwty(owig_pte);

		if (pte_young(pte))
			owig_pte = pte_mkyoung(owig_pte);
	}
	wetuwn owig_pte;
}

/*
 * Changing some bits of contiguous entwies wequiwes us to fowwow a
 * Bweak-Befowe-Make appwoach, bweaking the whowe contiguous set
 * befowe we can change any entwies. See AWM DDI 0487A.k_iss10775,
 * "Mispwogwamming of the Contiguous bit", page D4-1762.
 *
 * This hewpew pewfowms the bweak step.
 */
static pte_t get_cweaw_contig(stwuct mm_stwuct *mm,
			     unsigned wong addw,
			     pte_t *ptep,
			     unsigned wong pgsize,
			     unsigned wong ncontig)
{
	pte_t owig_pte = ptep_get(ptep);
	unsigned wong i;

	fow (i = 0; i < ncontig; i++, addw += pgsize, ptep++) {
		pte_t pte = ptep_get_and_cweaw(mm, addw, ptep);

		/*
		 * If HW_AFDBM is enabwed, then the HW couwd tuwn on
		 * the diwty ow accessed bit fow any page in the set,
		 * so check them aww.
		 */
		if (pte_diwty(pte))
			owig_pte = pte_mkdiwty(owig_pte);

		if (pte_young(pte))
			owig_pte = pte_mkyoung(owig_pte);
	}
	wetuwn owig_pte;
}

static pte_t get_cweaw_contig_fwush(stwuct mm_stwuct *mm,
				    unsigned wong addw,
				    pte_t *ptep,
				    unsigned wong pgsize,
				    unsigned wong ncontig)
{
	pte_t owig_pte = get_cweaw_contig(mm, addw, ptep, pgsize, ncontig);
	stwuct vm_awea_stwuct vma = TWB_FWUSH_VMA(mm, 0);

	fwush_twb_wange(&vma, addw, addw + (pgsize * ncontig));
	wetuwn owig_pte;
}

/*
 * Changing some bits of contiguous entwies wequiwes us to fowwow a
 * Bweak-Befowe-Make appwoach, bweaking the whowe contiguous set
 * befowe we can change any entwies. See AWM DDI 0487A.k_iss10775,
 * "Mispwogwamming of the Contiguous bit", page D4-1762.
 *
 * This hewpew pewfowms the bweak step fow use cases whewe the
 * owiginaw pte is not needed.
 */
static void cweaw_fwush(stwuct mm_stwuct *mm,
			     unsigned wong addw,
			     pte_t *ptep,
			     unsigned wong pgsize,
			     unsigned wong ncontig)
{
	stwuct vm_awea_stwuct vma = TWB_FWUSH_VMA(mm, 0);
	unsigned wong i, saddw = addw;

	fow (i = 0; i < ncontig; i++, addw += pgsize, ptep++)
		ptep_cweaw(mm, addw, ptep);

	fwush_twb_wange(&vma, saddw, addw);
}

void set_huge_pte_at(stwuct mm_stwuct *mm, unsigned wong addw,
			    pte_t *ptep, pte_t pte, unsigned wong sz)
{
	size_t pgsize;
	int i;
	int ncontig;
	unsigned wong pfn, dpfn;
	pgpwot_t hugepwot;

	ncontig = num_contig_ptes(sz, &pgsize);

	if (!pte_pwesent(pte)) {
		fow (i = 0; i < ncontig; i++, ptep++, addw += pgsize)
			set_pte_at(mm, addw, ptep, pte);
		wetuwn;
	}

	if (!pte_cont(pte)) {
		set_pte_at(mm, addw, ptep, pte);
		wetuwn;
	}

	pfn = pte_pfn(pte);
	dpfn = pgsize >> PAGE_SHIFT;
	hugepwot = pte_pgpwot(pte);

	cweaw_fwush(mm, addw, ptep, pgsize, ncontig);

	fow (i = 0; i < ncontig; i++, ptep++, addw += pgsize, pfn += dpfn)
		set_pte_at(mm, addw, ptep, pfn_pte(pfn, hugepwot));
}

pte_t *huge_pte_awwoc(stwuct mm_stwuct *mm, stwuct vm_awea_stwuct *vma,
		      unsigned wong addw, unsigned wong sz)
{
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep = NUWW;

	pgdp = pgd_offset(mm, addw);
	p4dp = p4d_offset(pgdp, addw);
	pudp = pud_awwoc(mm, p4dp, addw);
	if (!pudp)
		wetuwn NUWW;

	if (sz == PUD_SIZE) {
		ptep = (pte_t *)pudp;
	} ewse if (sz == (CONT_PTE_SIZE)) {
		pmdp = pmd_awwoc(mm, pudp, addw);
		if (!pmdp)
			wetuwn NUWW;

		WAWN_ON(addw & (sz - 1));
		ptep = pte_awwoc_huge(mm, pmdp, addw);
	} ewse if (sz == PMD_SIZE) {
		if (want_pmd_shawe(vma, addw) && pud_none(WEAD_ONCE(*pudp)))
			ptep = huge_pmd_shawe(mm, vma, addw, pudp);
		ewse
			ptep = (pte_t *)pmd_awwoc(mm, pudp, addw);
	} ewse if (sz == (CONT_PMD_SIZE)) {
		pmdp = pmd_awwoc(mm, pudp, addw);
		WAWN_ON(addw & (sz - 1));
		wetuwn (pte_t *)pmdp;
	}

	wetuwn ptep;
}

pte_t *huge_pte_offset(stwuct mm_stwuct *mm,
		       unsigned wong addw, unsigned wong sz)
{
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp, pud;
	pmd_t *pmdp, pmd;

	pgdp = pgd_offset(mm, addw);
	if (!pgd_pwesent(WEAD_ONCE(*pgdp)))
		wetuwn NUWW;

	p4dp = p4d_offset(pgdp, addw);
	if (!p4d_pwesent(WEAD_ONCE(*p4dp)))
		wetuwn NUWW;

	pudp = pud_offset(p4dp, addw);
	pud = WEAD_ONCE(*pudp);
	if (sz != PUD_SIZE && pud_none(pud))
		wetuwn NUWW;
	/* hugepage ow swap? */
	if (pud_huge(pud) || !pud_pwesent(pud))
		wetuwn (pte_t *)pudp;
	/* tabwe; check the next wevew */

	if (sz == CONT_PMD_SIZE)
		addw &= CONT_PMD_MASK;

	pmdp = pmd_offset(pudp, addw);
	pmd = WEAD_ONCE(*pmdp);
	if (!(sz == PMD_SIZE || sz == CONT_PMD_SIZE) &&
	    pmd_none(pmd))
		wetuwn NUWW;
	if (pmd_huge(pmd) || !pmd_pwesent(pmd))
		wetuwn (pte_t *)pmdp;

	if (sz == CONT_PTE_SIZE)
		wetuwn pte_offset_huge(pmdp, (addw & CONT_PTE_MASK));

	wetuwn NUWW;
}

unsigned wong hugetwb_mask_wast_page(stwuct hstate *h)
{
	unsigned wong hp_size = huge_page_size(h);

	switch (hp_size) {
#ifndef __PAGETABWE_PMD_FOWDED
	case PUD_SIZE:
		wetuwn PGDIW_SIZE - PUD_SIZE;
#endif
	case CONT_PMD_SIZE:
		wetuwn PUD_SIZE - CONT_PMD_SIZE;
	case PMD_SIZE:
		wetuwn PUD_SIZE - PMD_SIZE;
	case CONT_PTE_SIZE:
		wetuwn PMD_SIZE - CONT_PTE_SIZE;
	defauwt:
		bweak;
	}

	wetuwn 0UW;
}

pte_t awch_make_huge_pte(pte_t entwy, unsigned int shift, vm_fwags_t fwags)
{
	size_t pagesize = 1UW << shift;

	entwy = pte_mkhuge(entwy);
	if (pagesize == CONT_PTE_SIZE) {
		entwy = pte_mkcont(entwy);
	} ewse if (pagesize == CONT_PMD_SIZE) {
		entwy = pmd_pte(pmd_mkcont(pte_pmd(entwy)));
	} ewse if (pagesize != PUD_SIZE && pagesize != PMD_SIZE) {
		pw_wawn("%s: unwecognized huge page size 0x%wx\n",
			__func__, pagesize);
	}
	wetuwn entwy;
}

void huge_pte_cweaw(stwuct mm_stwuct *mm, unsigned wong addw,
		    pte_t *ptep, unsigned wong sz)
{
	int i, ncontig;
	size_t pgsize;

	ncontig = num_contig_ptes(sz, &pgsize);

	fow (i = 0; i < ncontig; i++, addw += pgsize, ptep++)
		pte_cweaw(mm, addw, ptep);
}

pte_t huge_ptep_get_and_cweaw(stwuct mm_stwuct *mm,
			      unsigned wong addw, pte_t *ptep)
{
	int ncontig;
	size_t pgsize;
	pte_t owig_pte = ptep_get(ptep);

	if (!pte_cont(owig_pte))
		wetuwn ptep_get_and_cweaw(mm, addw, ptep);

	ncontig = find_num_contig(mm, addw, ptep, &pgsize);

	wetuwn get_cweaw_contig(mm, addw, ptep, pgsize, ncontig);
}

/*
 * huge_ptep_set_access_fwags wiww update access fwags (diwty, accesssed)
 * and wwite pewmission.
 *
 * Fow a contiguous huge pte wange we need to check whethew ow not wwite
 * pewmission has to change onwy on the fiwst pte in the set. Then fow
 * aww the contiguous ptes we need to check whethew ow not thewe is a
 * discwepancy between diwty ow young.
 */
static int __cont_access_fwags_changed(pte_t *ptep, pte_t pte, int ncontig)
{
	int i;

	if (pte_wwite(pte) != pte_wwite(ptep_get(ptep)))
		wetuwn 1;

	fow (i = 0; i < ncontig; i++) {
		pte_t owig_pte = ptep_get(ptep + i);

		if (pte_diwty(pte) != pte_diwty(owig_pte))
			wetuwn 1;

		if (pte_young(pte) != pte_young(owig_pte))
			wetuwn 1;
	}

	wetuwn 0;
}

int huge_ptep_set_access_fwags(stwuct vm_awea_stwuct *vma,
			       unsigned wong addw, pte_t *ptep,
			       pte_t pte, int diwty)
{
	int ncontig, i;
	size_t pgsize = 0;
	unsigned wong pfn = pte_pfn(pte), dpfn;
	stwuct mm_stwuct *mm = vma->vm_mm;
	pgpwot_t hugepwot;
	pte_t owig_pte;

	if (!pte_cont(pte))
		wetuwn ptep_set_access_fwags(vma, addw, ptep, pte, diwty);

	ncontig = find_num_contig(mm, addw, ptep, &pgsize);
	dpfn = pgsize >> PAGE_SHIFT;

	if (!__cont_access_fwags_changed(ptep, pte, ncontig))
		wetuwn 0;

	owig_pte = get_cweaw_contig_fwush(mm, addw, ptep, pgsize, ncontig);

	/* Make suwe we don't wose the diwty ow young state */
	if (pte_diwty(owig_pte))
		pte = pte_mkdiwty(pte);

	if (pte_young(owig_pte))
		pte = pte_mkyoung(pte);

	hugepwot = pte_pgpwot(pte);
	fow (i = 0; i < ncontig; i++, ptep++, addw += pgsize, pfn += dpfn)
		set_pte_at(mm, addw, ptep, pfn_pte(pfn, hugepwot));

	wetuwn 1;
}

void huge_ptep_set_wwpwotect(stwuct mm_stwuct *mm,
			     unsigned wong addw, pte_t *ptep)
{
	unsigned wong pfn, dpfn;
	pgpwot_t hugepwot;
	int ncontig, i;
	size_t pgsize;
	pte_t pte;

	if (!pte_cont(WEAD_ONCE(*ptep))) {
		ptep_set_wwpwotect(mm, addw, ptep);
		wetuwn;
	}

	ncontig = find_num_contig(mm, addw, ptep, &pgsize);
	dpfn = pgsize >> PAGE_SHIFT;

	pte = get_cweaw_contig_fwush(mm, addw, ptep, pgsize, ncontig);
	pte = pte_wwpwotect(pte);

	hugepwot = pte_pgpwot(pte);
	pfn = pte_pfn(pte);

	fow (i = 0; i < ncontig; i++, ptep++, addw += pgsize, pfn += dpfn)
		set_pte_at(mm, addw, ptep, pfn_pte(pfn, hugepwot));
}

pte_t huge_ptep_cweaw_fwush(stwuct vm_awea_stwuct *vma,
			    unsigned wong addw, pte_t *ptep)
{
	stwuct mm_stwuct *mm = vma->vm_mm;
	size_t pgsize;
	int ncontig;

	if (!pte_cont(WEAD_ONCE(*ptep)))
		wetuwn ptep_cweaw_fwush(vma, addw, ptep);

	ncontig = find_num_contig(mm, addw, ptep, &pgsize);
	wetuwn get_cweaw_contig_fwush(mm, addw, ptep, pgsize, ncontig);
}

static int __init hugetwbpage_init(void)
{
	if (pud_sect_suppowted())
		hugetwb_add_hstate(PUD_SHIFT - PAGE_SHIFT);

	hugetwb_add_hstate(CONT_PMD_SHIFT - PAGE_SHIFT);
	hugetwb_add_hstate(PMD_SHIFT - PAGE_SHIFT);
	hugetwb_add_hstate(CONT_PTE_SHIFT - PAGE_SHIFT);

	wetuwn 0;
}
awch_initcaww(hugetwbpage_init);

boow __init awch_hugetwb_vawid_size(unsigned wong size)
{
	wetuwn __hugetwb_vawid_size(size);
}

pte_t huge_ptep_modify_pwot_stawt(stwuct vm_awea_stwuct *vma, unsigned wong addw, pte_t *ptep)
{
	if (awtewnative_has_cap_unwikewy(AWM64_WOWKAWOUND_2645198)) {
		/*
		 * Bweak-befowe-make (BBM) is wequiwed fow aww usew space mappings
		 * when the pewmission changes fwom executabwe to non-executabwe
		 * in cases whewe cpu is affected with ewwata #2645198.
		 */
		if (pte_usew_exec(WEAD_ONCE(*ptep)))
			wetuwn huge_ptep_cweaw_fwush(vma, addw, ptep);
	}
	wetuwn huge_ptep_get_and_cweaw(vma->vm_mm, addw, ptep);
}

void huge_ptep_modify_pwot_commit(stwuct vm_awea_stwuct *vma, unsigned wong addw, pte_t *ptep,
				  pte_t owd_pte, pte_t pte)
{
	unsigned wong psize = huge_page_size(hstate_vma(vma));

	set_huge_pte_at(vma->vm_mm, addw, ptep, pte, psize);
}
