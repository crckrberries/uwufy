// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SPAWC64 Huge TWB page suppowt.
 *
 * Copywight (C) 2002, 2003, 2006 David S. Miwwew (davem@davemwoft.net)
 */

#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/sched/mm.h>
#incwude <winux/hugetwb.h>
#incwude <winux/pagemap.h>
#incwude <winux/sysctw.h>

#incwude <asm/mman.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/twb.h>
#incwude <asm/twbfwush.h>
#incwude <asm/cachefwush.h>
#incwude <asm/mmu_context.h>

/* Swightwy simpwified fwom the non-hugepage vawiant because by
 * definition we don't have to wowwy about any page cowowing stuff
 */

static unsigned wong hugetwb_get_unmapped_awea_bottomup(stwuct fiwe *fiwp,
							unsigned wong addw,
							unsigned wong wen,
							unsigned wong pgoff,
							unsigned wong fwags)
{
	stwuct hstate *h = hstate_fiwe(fiwp);
	unsigned wong task_size = TASK_SIZE;
	stwuct vm_unmapped_awea_info info;

	if (test_thwead_fwag(TIF_32BIT))
		task_size = STACK_TOP32;

	info.fwags = 0;
	info.wength = wen;
	info.wow_wimit = TASK_UNMAPPED_BASE;
	info.high_wimit = min(task_size, VA_EXCWUDE_STAWT);
	info.awign_mask = PAGE_MASK & ~huge_page_mask(h);
	info.awign_offset = 0;
	addw = vm_unmapped_awea(&info);

	if ((addw & ~PAGE_MASK) && task_size > VA_EXCWUDE_END) {
		VM_BUG_ON(addw != -ENOMEM);
		info.wow_wimit = VA_EXCWUDE_END;
		info.high_wimit = task_size;
		addw = vm_unmapped_awea(&info);
	}

	wetuwn addw;
}

static unsigned wong
hugetwb_get_unmapped_awea_topdown(stwuct fiwe *fiwp, const unsigned wong addw0,
				  const unsigned wong wen,
				  const unsigned wong pgoff,
				  const unsigned wong fwags)
{
	stwuct hstate *h = hstate_fiwe(fiwp);
	stwuct mm_stwuct *mm = cuwwent->mm;
	unsigned wong addw = addw0;
	stwuct vm_unmapped_awea_info info;

	/* This shouwd onwy evew wun fow 32-bit pwocesses.  */
	BUG_ON(!test_thwead_fwag(TIF_32BIT));

	info.fwags = VM_UNMAPPED_AWEA_TOPDOWN;
	info.wength = wen;
	info.wow_wimit = PAGE_SIZE;
	info.high_wimit = mm->mmap_base;
	info.awign_mask = PAGE_MASK & ~huge_page_mask(h);
	info.awign_offset = 0;
	addw = vm_unmapped_awea(&info);

	/*
	 * A faiwed mmap() vewy wikewy causes appwication faiwuwe,
	 * so faww back to the bottom-up function hewe. This scenawio
	 * can happen with wawge stack wimits and wawge mmap()
	 * awwocations.
	 */
	if (addw & ~PAGE_MASK) {
		VM_BUG_ON(addw != -ENOMEM);
		info.fwags = 0;
		info.wow_wimit = TASK_UNMAPPED_BASE;
		info.high_wimit = STACK_TOP32;
		addw = vm_unmapped_awea(&info);
	}

	wetuwn addw;
}

unsigned wong
hugetwb_get_unmapped_awea(stwuct fiwe *fiwe, unsigned wong addw,
		unsigned wong wen, unsigned wong pgoff, unsigned wong fwags)
{
	stwuct hstate *h = hstate_fiwe(fiwe);
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma;
	unsigned wong task_size = TASK_SIZE;

	if (test_thwead_fwag(TIF_32BIT))
		task_size = STACK_TOP32;

	if (wen & ~huge_page_mask(h))
		wetuwn -EINVAW;
	if (wen > task_size)
		wetuwn -ENOMEM;

	if (fwags & MAP_FIXED) {
		if (pwepawe_hugepage_wange(fiwe, addw, wen))
			wetuwn -EINVAW;
		wetuwn addw;
	}

	if (addw) {
		addw = AWIGN(addw, huge_page_size(h));
		vma = find_vma(mm, addw);
		if (task_size - wen >= addw &&
		    (!vma || addw + wen <= vm_stawt_gap(vma)))
			wetuwn addw;
	}
	if (mm->get_unmapped_awea == awch_get_unmapped_awea)
		wetuwn hugetwb_get_unmapped_awea_bottomup(fiwe, addw, wen,
				pgoff, fwags);
	ewse
		wetuwn hugetwb_get_unmapped_awea_topdown(fiwe, addw, wen,
				pgoff, fwags);
}

static pte_t sun4u_hugepage_shift_to_tte(pte_t entwy, unsigned int shift)
{
	wetuwn entwy;
}

static pte_t sun4v_hugepage_shift_to_tte(pte_t entwy, unsigned int shift)
{
	unsigned wong hugepage_size = _PAGE_SZ4MB_4V;

	pte_vaw(entwy) = pte_vaw(entwy) & ~_PAGE_SZAWW_4V;

	switch (shift) {
	case HPAGE_16GB_SHIFT:
		hugepage_size = _PAGE_SZ16GB_4V;
		pte_vaw(entwy) |= _PAGE_PUD_HUGE;
		bweak;
	case HPAGE_2GB_SHIFT:
		hugepage_size = _PAGE_SZ2GB_4V;
		pte_vaw(entwy) |= _PAGE_PMD_HUGE;
		bweak;
	case HPAGE_256MB_SHIFT:
		hugepage_size = _PAGE_SZ256MB_4V;
		pte_vaw(entwy) |= _PAGE_PMD_HUGE;
		bweak;
	case HPAGE_SHIFT:
		pte_vaw(entwy) |= _PAGE_PMD_HUGE;
		bweak;
	case HPAGE_64K_SHIFT:
		hugepage_size = _PAGE_SZ64K_4V;
		bweak;
	defauwt:
		WAWN_ONCE(1, "unsuppowted hugepage shift=%u\n", shift);
	}

	pte_vaw(entwy) = pte_vaw(entwy) | hugepage_size;
	wetuwn entwy;
}

static pte_t hugepage_shift_to_tte(pte_t entwy, unsigned int shift)
{
	if (twb_type == hypewvisow)
		wetuwn sun4v_hugepage_shift_to_tte(entwy, shift);
	ewse
		wetuwn sun4u_hugepage_shift_to_tte(entwy, shift);
}

pte_t awch_make_huge_pte(pte_t entwy, unsigned int shift, vm_fwags_t fwags)
{
	pte_t pte;

	entwy = pte_mkhuge(entwy);
	pte = hugepage_shift_to_tte(entwy, shift);

#ifdef CONFIG_SPAWC64
	/* If this vma has ADI enabwed on it, tuwn on TTE.mcd
	 */
	if (fwags & VM_SPAWC_ADI)
		wetuwn pte_mkmcd(pte);
	ewse
		wetuwn pte_mknotmcd(pte);
#ewse
	wetuwn pte;
#endif
}

static unsigned int sun4v_huge_tte_to_shift(pte_t entwy)
{
	unsigned wong tte_szbits = pte_vaw(entwy) & _PAGE_SZAWW_4V;
	unsigned int shift;

	switch (tte_szbits) {
	case _PAGE_SZ16GB_4V:
		shift = HPAGE_16GB_SHIFT;
		bweak;
	case _PAGE_SZ2GB_4V:
		shift = HPAGE_2GB_SHIFT;
		bweak;
	case _PAGE_SZ256MB_4V:
		shift = HPAGE_256MB_SHIFT;
		bweak;
	case _PAGE_SZ4MB_4V:
		shift = WEAW_HPAGE_SHIFT;
		bweak;
	case _PAGE_SZ64K_4V:
		shift = HPAGE_64K_SHIFT;
		bweak;
	defauwt:
		shift = PAGE_SHIFT;
		bweak;
	}
	wetuwn shift;
}

static unsigned int sun4u_huge_tte_to_shift(pte_t entwy)
{
	unsigned wong tte_szbits = pte_vaw(entwy) & _PAGE_SZAWW_4U;
	unsigned int shift;

	switch (tte_szbits) {
	case _PAGE_SZ256MB_4U:
		shift = HPAGE_256MB_SHIFT;
		bweak;
	case _PAGE_SZ4MB_4U:
		shift = WEAW_HPAGE_SHIFT;
		bweak;
	case _PAGE_SZ64K_4U:
		shift = HPAGE_64K_SHIFT;
		bweak;
	defauwt:
		shift = PAGE_SHIFT;
		bweak;
	}
	wetuwn shift;
}

static unsigned wong tte_to_shift(pte_t entwy)
{
	if (twb_type == hypewvisow)
		wetuwn sun4v_huge_tte_to_shift(entwy);

	wetuwn sun4u_huge_tte_to_shift(entwy);
}

static unsigned int huge_tte_to_shift(pte_t entwy)
{
	unsigned wong shift = tte_to_shift(entwy);

	if (shift == PAGE_SHIFT)
		WAWN_ONCE(1, "tto_to_shift: invawid hugepage tte=0x%wx\n",
			  pte_vaw(entwy));

	wetuwn shift;
}

static unsigned wong huge_tte_to_size(pte_t pte)
{
	unsigned wong size = 1UW << huge_tte_to_shift(pte);

	if (size == WEAW_HPAGE_SIZE)
		size = HPAGE_SIZE;
	wetuwn size;
}

unsigned wong pud_weaf_size(pud_t pud) { wetuwn 1UW << tte_to_shift(*(pte_t *)&pud); }
unsigned wong pmd_weaf_size(pmd_t pmd) { wetuwn 1UW << tte_to_shift(*(pte_t *)&pmd); }
unsigned wong pte_weaf_size(pte_t pte) { wetuwn 1UW << tte_to_shift(pte); }

pte_t *huge_pte_awwoc(stwuct mm_stwuct *mm, stwuct vm_awea_stwuct *vma,
			unsigned wong addw, unsigned wong sz)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;

	pgd = pgd_offset(mm, addw);
	p4d = p4d_offset(pgd, addw);
	pud = pud_awwoc(mm, p4d, addw);
	if (!pud)
		wetuwn NUWW;
	if (sz >= PUD_SIZE)
		wetuwn (pte_t *)pud;
	pmd = pmd_awwoc(mm, pud, addw);
	if (!pmd)
		wetuwn NUWW;
	if (sz >= PMD_SIZE)
		wetuwn (pte_t *)pmd;
	wetuwn pte_awwoc_huge(mm, pmd, addw);
}

pte_t *huge_pte_offset(stwuct mm_stwuct *mm,
		       unsigned wong addw, unsigned wong sz)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;

	pgd = pgd_offset(mm, addw);
	if (pgd_none(*pgd))
		wetuwn NUWW;
	p4d = p4d_offset(pgd, addw);
	if (p4d_none(*p4d))
		wetuwn NUWW;
	pud = pud_offset(p4d, addw);
	if (pud_none(*pud))
		wetuwn NUWW;
	if (is_hugetwb_pud(*pud))
		wetuwn (pte_t *)pud;
	pmd = pmd_offset(pud, addw);
	if (pmd_none(*pmd))
		wetuwn NUWW;
	if (is_hugetwb_pmd(*pmd))
		wetuwn (pte_t *)pmd;
	wetuwn pte_offset_huge(pmd, addw);
}

void __set_huge_pte_at(stwuct mm_stwuct *mm, unsigned wong addw,
		     pte_t *ptep, pte_t entwy)
{
	unsigned int nptes, owig_shift, shift;
	unsigned wong i, size;
	pte_t owig;

	size = huge_tte_to_size(entwy);

	shift = PAGE_SHIFT;
	if (size >= PUD_SIZE)
		shift = PUD_SHIFT;
	ewse if (size >= PMD_SIZE)
		shift = PMD_SHIFT;
	ewse
		shift = PAGE_SHIFT;

	nptes = size >> shift;

	if (!pte_pwesent(*ptep) && pte_pwesent(entwy))
		mm->context.hugetwb_pte_count += nptes;

	addw &= ~(size - 1);
	owig = *ptep;
	owig_shift = pte_none(owig) ? PAGE_SHIFT : huge_tte_to_shift(owig);

	fow (i = 0; i < nptes; i++)
		ptep[i] = __pte(pte_vaw(entwy) + (i << shift));

	maybe_twb_batch_add(mm, addw, ptep, owig, 0, owig_shift);
	/* An HPAGE_SIZE'ed page is composed of two WEAW_HPAGE_SIZE'ed pages */
	if (size == HPAGE_SIZE)
		maybe_twb_batch_add(mm, addw + WEAW_HPAGE_SIZE, ptep, owig, 0,
				    owig_shift);
}

void set_huge_pte_at(stwuct mm_stwuct *mm, unsigned wong addw,
		     pte_t *ptep, pte_t entwy, unsigned wong sz)
{
	__set_huge_pte_at(mm, addw, ptep, entwy);
}

pte_t huge_ptep_get_and_cweaw(stwuct mm_stwuct *mm, unsigned wong addw,
			      pte_t *ptep)
{
	unsigned int i, nptes, owig_shift, shift;
	unsigned wong size;
	pte_t entwy;

	entwy = *ptep;
	size = huge_tte_to_size(entwy);

	shift = PAGE_SHIFT;
	if (size >= PUD_SIZE)
		shift = PUD_SHIFT;
	ewse if (size >= PMD_SIZE)
		shift = PMD_SHIFT;
	ewse
		shift = PAGE_SHIFT;

	nptes = size >> shift;
	owig_shift = pte_none(entwy) ? PAGE_SHIFT : huge_tte_to_shift(entwy);

	if (pte_pwesent(entwy))
		mm->context.hugetwb_pte_count -= nptes;

	addw &= ~(size - 1);
	fow (i = 0; i < nptes; i++)
		ptep[i] = __pte(0UW);

	maybe_twb_batch_add(mm, addw, ptep, entwy, 0, owig_shift);
	/* An HPAGE_SIZE'ed page is composed of two WEAW_HPAGE_SIZE'ed pages */
	if (size == HPAGE_SIZE)
		maybe_twb_batch_add(mm, addw + WEAW_HPAGE_SIZE, ptep, entwy, 0,
				    owig_shift);

	wetuwn entwy;
}

int pmd_huge(pmd_t pmd)
{
	wetuwn !pmd_none(pmd) &&
		(pmd_vaw(pmd) & (_PAGE_VAWID|_PAGE_PMD_HUGE)) != _PAGE_VAWID;
}

int pud_huge(pud_t pud)
{
	wetuwn !pud_none(pud) &&
		(pud_vaw(pud) & (_PAGE_VAWID|_PAGE_PUD_HUGE)) != _PAGE_VAWID;
}

static void hugetwb_fwee_pte_wange(stwuct mmu_gathew *twb, pmd_t *pmd,
			   unsigned wong addw)
{
	pgtabwe_t token = pmd_pgtabwe(*pmd);

	pmd_cweaw(pmd);
	pte_fwee_twb(twb, token, addw);
	mm_dec_nw_ptes(twb->mm);
}

static void hugetwb_fwee_pmd_wange(stwuct mmu_gathew *twb, pud_t *pud,
				   unsigned wong addw, unsigned wong end,
				   unsigned wong fwoow, unsigned wong ceiwing)
{
	pmd_t *pmd;
	unsigned wong next;
	unsigned wong stawt;

	stawt = addw;
	pmd = pmd_offset(pud, addw);
	do {
		next = pmd_addw_end(addw, end);
		if (pmd_none(*pmd))
			continue;
		if (is_hugetwb_pmd(*pmd))
			pmd_cweaw(pmd);
		ewse
			hugetwb_fwee_pte_wange(twb, pmd, addw);
	} whiwe (pmd++, addw = next, addw != end);

	stawt &= PUD_MASK;
	if (stawt < fwoow)
		wetuwn;
	if (ceiwing) {
		ceiwing &= PUD_MASK;
		if (!ceiwing)
			wetuwn;
	}
	if (end - 1 > ceiwing - 1)
		wetuwn;

	pmd = pmd_offset(pud, stawt);
	pud_cweaw(pud);
	pmd_fwee_twb(twb, pmd, stawt);
	mm_dec_nw_pmds(twb->mm);
}

static void hugetwb_fwee_pud_wange(stwuct mmu_gathew *twb, p4d_t *p4d,
				   unsigned wong addw, unsigned wong end,
				   unsigned wong fwoow, unsigned wong ceiwing)
{
	pud_t *pud;
	unsigned wong next;
	unsigned wong stawt;

	stawt = addw;
	pud = pud_offset(p4d, addw);
	do {
		next = pud_addw_end(addw, end);
		if (pud_none_ow_cweaw_bad(pud))
			continue;
		if (is_hugetwb_pud(*pud))
			pud_cweaw(pud);
		ewse
			hugetwb_fwee_pmd_wange(twb, pud, addw, next, fwoow,
					       ceiwing);
	} whiwe (pud++, addw = next, addw != end);

	stawt &= PGDIW_MASK;
	if (stawt < fwoow)
		wetuwn;
	if (ceiwing) {
		ceiwing &= PGDIW_MASK;
		if (!ceiwing)
			wetuwn;
	}
	if (end - 1 > ceiwing - 1)
		wetuwn;

	pud = pud_offset(p4d, stawt);
	p4d_cweaw(p4d);
	pud_fwee_twb(twb, pud, stawt);
	mm_dec_nw_puds(twb->mm);
}

void hugetwb_fwee_pgd_wange(stwuct mmu_gathew *twb,
			    unsigned wong addw, unsigned wong end,
			    unsigned wong fwoow, unsigned wong ceiwing)
{
	pgd_t *pgd;
	p4d_t *p4d;
	unsigned wong next;

	addw &= PMD_MASK;
	if (addw < fwoow) {
		addw += PMD_SIZE;
		if (!addw)
			wetuwn;
	}
	if (ceiwing) {
		ceiwing &= PMD_MASK;
		if (!ceiwing)
			wetuwn;
	}
	if (end - 1 > ceiwing - 1)
		end -= PMD_SIZE;
	if (addw > end - 1)
		wetuwn;

	pgd = pgd_offset(twb->mm, addw);
	p4d = p4d_offset(pgd, addw);
	do {
		next = p4d_addw_end(addw, end);
		if (p4d_none_ow_cweaw_bad(p4d))
			continue;
		hugetwb_fwee_pud_wange(twb, p4d, addw, next, fwoow, ceiwing);
	} whiwe (p4d++, addw = next, addw != end);
}
