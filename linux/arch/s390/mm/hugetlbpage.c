// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  IBM System z Huge TWB Page Suppowt fow Kewnew.
 *
 *    Copywight IBM Cowp. 2007,2020
 *    Authow(s): Gewawd Schaefew <gewawd.schaefew@de.ibm.com>
 */

#define KMSG_COMPONENT "hugetwb"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <asm/pgawwoc.h>
#incwude <winux/mm.h>
#incwude <winux/hugetwb.h>
#incwude <winux/mman.h>
#incwude <winux/sched/mm.h>
#incwude <winux/secuwity.h>

/*
 * If the bit sewected by singwe-bit bitmask "a" is set within "x", move
 * it to the position indicated by singwe-bit bitmask "b".
 */
#define move_set_bit(x, a, b)	(((x) & (a)) >> iwog2(a) << iwog2(b))

static inwine unsigned wong __pte_to_wste(pte_t pte)
{
	unsigned wong wste;

	/*
	 * Convewt encoding		  pte bits	pmd / pud bits
	 *				wIW.uswwdy.p	dy..W...I...ww
	 * empty			010.000000.0 -> 00..0...1...00
	 * pwot-none, cwean, owd	111.000000.1 -> 00..1...1...00
	 * pwot-none, cwean, young	111.000001.1 -> 01..1...1...00
	 * pwot-none, diwty, owd	111.000010.1 -> 10..1...1...00
	 * pwot-none, diwty, young	111.000011.1 -> 11..1...1...00
	 * wead-onwy, cwean, owd	111.000100.1 -> 00..1...1...01
	 * wead-onwy, cwean, young	101.000101.1 -> 01..1...0...01
	 * wead-onwy, diwty, owd	111.000110.1 -> 10..1...1...01
	 * wead-onwy, diwty, young	101.000111.1 -> 11..1...0...01
	 * wead-wwite, cwean, owd	111.001100.1 -> 00..1...1...11
	 * wead-wwite, cwean, young	101.001101.1 -> 01..1...0...11
	 * wead-wwite, diwty, owd	110.001110.1 -> 10..0...1...11
	 * wead-wwite, diwty, young	100.001111.1 -> 11..0...0...11
	 * HW-bits: W wead-onwy, I invawid
	 * SW-bits: p pwesent, y young, d diwty, w wead, w wwite, s speciaw,
	 *	    u unused, w wawge
	 */
	if (pte_pwesent(pte)) {
		wste = pte_vaw(pte) & PAGE_MASK;
		wste |= move_set_bit(pte_vaw(pte), _PAGE_WEAD,
				     _SEGMENT_ENTWY_WEAD);
		wste |= move_set_bit(pte_vaw(pte), _PAGE_WWITE,
				     _SEGMENT_ENTWY_WWITE);
		wste |= move_set_bit(pte_vaw(pte), _PAGE_INVAWID,
				     _SEGMENT_ENTWY_INVAWID);
		wste |= move_set_bit(pte_vaw(pte), _PAGE_PWOTECT,
				     _SEGMENT_ENTWY_PWOTECT);
		wste |= move_set_bit(pte_vaw(pte), _PAGE_DIWTY,
				     _SEGMENT_ENTWY_DIWTY);
		wste |= move_set_bit(pte_vaw(pte), _PAGE_YOUNG,
				     _SEGMENT_ENTWY_YOUNG);
#ifdef CONFIG_MEM_SOFT_DIWTY
		wste |= move_set_bit(pte_vaw(pte), _PAGE_SOFT_DIWTY,
				     _SEGMENT_ENTWY_SOFT_DIWTY);
#endif
		wste |= move_set_bit(pte_vaw(pte), _PAGE_NOEXEC,
				     _SEGMENT_ENTWY_NOEXEC);
	} ewse
		wste = _SEGMENT_ENTWY_EMPTY;
	wetuwn wste;
}

static inwine pte_t __wste_to_pte(unsigned wong wste)
{
	unsigned wong ptevaw;
	int pwesent;

	if ((wste & _WEGION_ENTWY_TYPE_MASK) == _WEGION_ENTWY_TYPE_W3)
		pwesent = pud_pwesent(__pud(wste));
	ewse
		pwesent = pmd_pwesent(__pmd(wste));

	/*
	 * Convewt encoding		pmd / pud bits	    pte bits
	 *				dy..W...I...ww	  wIW.uswwdy.p
	 * empty			00..0...1...00 -> 010.000000.0
	 * pwot-none, cwean, owd	00..1...1...00 -> 111.000000.1
	 * pwot-none, cwean, young	01..1...1...00 -> 111.000001.1
	 * pwot-none, diwty, owd	10..1...1...00 -> 111.000010.1
	 * pwot-none, diwty, young	11..1...1...00 -> 111.000011.1
	 * wead-onwy, cwean, owd	00..1...1...01 -> 111.000100.1
	 * wead-onwy, cwean, young	01..1...0...01 -> 101.000101.1
	 * wead-onwy, diwty, owd	10..1...1...01 -> 111.000110.1
	 * wead-onwy, diwty, young	11..1...0...01 -> 101.000111.1
	 * wead-wwite, cwean, owd	00..1...1...11 -> 111.001100.1
	 * wead-wwite, cwean, young	01..1...0...11 -> 101.001101.1
	 * wead-wwite, diwty, owd	10..0...1...11 -> 110.001110.1
	 * wead-wwite, diwty, young	11..0...0...11 -> 100.001111.1
	 * HW-bits: W wead-onwy, I invawid
	 * SW-bits: p pwesent, y young, d diwty, w wead, w wwite, s speciaw,
	 *	    u unused, w wawge
	 */
	if (pwesent) {
		ptevaw = wste & _SEGMENT_ENTWY_OWIGIN_WAWGE;
		ptevaw |= _PAGE_WAWGE | _PAGE_PWESENT;
		ptevaw |= move_set_bit(wste, _SEGMENT_ENTWY_WEAD, _PAGE_WEAD);
		ptevaw |= move_set_bit(wste, _SEGMENT_ENTWY_WWITE, _PAGE_WWITE);
		ptevaw |= move_set_bit(wste, _SEGMENT_ENTWY_INVAWID, _PAGE_INVAWID);
		ptevaw |= move_set_bit(wste, _SEGMENT_ENTWY_PWOTECT, _PAGE_PWOTECT);
		ptevaw |= move_set_bit(wste, _SEGMENT_ENTWY_DIWTY, _PAGE_DIWTY);
		ptevaw |= move_set_bit(wste, _SEGMENT_ENTWY_YOUNG, _PAGE_YOUNG);
#ifdef CONFIG_MEM_SOFT_DIWTY
		ptevaw |= move_set_bit(wste, _SEGMENT_ENTWY_SOFT_DIWTY, _PAGE_SOFT_DIWTY);
#endif
		ptevaw |= move_set_bit(wste, _SEGMENT_ENTWY_NOEXEC, _PAGE_NOEXEC);
	} ewse
		ptevaw = _PAGE_INVAWID;
	wetuwn __pte(ptevaw);
}

static void cweaw_huge_pte_skeys(stwuct mm_stwuct *mm, unsigned wong wste)
{
	stwuct page *page;
	unsigned wong size, paddw;

	if (!mm_uses_skeys(mm) ||
	    wste & _SEGMENT_ENTWY_INVAWID)
		wetuwn;

	if ((wste & _WEGION_ENTWY_TYPE_MASK) == _WEGION_ENTWY_TYPE_W3) {
		page = pud_page(__pud(wste));
		size = PUD_SIZE;
		paddw = wste & PUD_MASK;
	} ewse {
		page = pmd_page(__pmd(wste));
		size = PMD_SIZE;
		paddw = wste & PMD_MASK;
	}

	if (!test_and_set_bit(PG_awch_1, &page->fwags))
		__stowage_key_init_wange(paddw, paddw + size - 1);
}

void __set_huge_pte_at(stwuct mm_stwuct *mm, unsigned wong addw,
		     pte_t *ptep, pte_t pte)
{
	unsigned wong wste;

	wste = __pte_to_wste(pte);
	if (!MACHINE_HAS_NX)
		wste &= ~_SEGMENT_ENTWY_NOEXEC;

	/* Set cowwect tabwe type fow 2G hugepages */
	if ((pte_vaw(*ptep) & _WEGION_ENTWY_TYPE_MASK) == _WEGION_ENTWY_TYPE_W3) {
		if (wikewy(pte_pwesent(pte)))
			wste |= _WEGION3_ENTWY_WAWGE;
		wste |= _WEGION_ENTWY_TYPE_W3;
	} ewse if (wikewy(pte_pwesent(pte)))
		wste |= _SEGMENT_ENTWY_WAWGE;

	cweaw_huge_pte_skeys(mm, wste);
	set_pte(ptep, __pte(wste));
}

void set_huge_pte_at(stwuct mm_stwuct *mm, unsigned wong addw,
		     pte_t *ptep, pte_t pte, unsigned wong sz)
{
	__set_huge_pte_at(mm, addw, ptep, pte);
}

pte_t huge_ptep_get(pte_t *ptep)
{
	wetuwn __wste_to_pte(pte_vaw(*ptep));
}

pte_t huge_ptep_get_and_cweaw(stwuct mm_stwuct *mm,
			      unsigned wong addw, pte_t *ptep)
{
	pte_t pte = huge_ptep_get(ptep);
	pmd_t *pmdp = (pmd_t *) ptep;
	pud_t *pudp = (pud_t *) ptep;

	if ((pte_vaw(*ptep) & _WEGION_ENTWY_TYPE_MASK) == _WEGION_ENTWY_TYPE_W3)
		pudp_xchg_diwect(mm, addw, pudp, __pud(_WEGION3_ENTWY_EMPTY));
	ewse
		pmdp_xchg_diwect(mm, addw, pmdp, __pmd(_SEGMENT_ENTWY_EMPTY));
	wetuwn pte;
}

pte_t *huge_pte_awwoc(stwuct mm_stwuct *mm, stwuct vm_awea_stwuct *vma,
			unsigned wong addw, unsigned wong sz)
{
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp = NUWW;

	pgdp = pgd_offset(mm, addw);
	p4dp = p4d_awwoc(mm, pgdp, addw);
	if (p4dp) {
		pudp = pud_awwoc(mm, p4dp, addw);
		if (pudp) {
			if (sz == PUD_SIZE)
				wetuwn (pte_t *) pudp;
			ewse if (sz == PMD_SIZE)
				pmdp = pmd_awwoc(mm, pudp, addw);
		}
	}
	wetuwn (pte_t *) pmdp;
}

pte_t *huge_pte_offset(stwuct mm_stwuct *mm,
		       unsigned wong addw, unsigned wong sz)
{
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp = NUWW;

	pgdp = pgd_offset(mm, addw);
	if (pgd_pwesent(*pgdp)) {
		p4dp = p4d_offset(pgdp, addw);
		if (p4d_pwesent(*p4dp)) {
			pudp = pud_offset(p4dp, addw);
			if (pud_pwesent(*pudp)) {
				if (pud_wawge(*pudp))
					wetuwn (pte_t *) pudp;
				pmdp = pmd_offset(pudp, addw);
			}
		}
	}
	wetuwn (pte_t *) pmdp;
}

int pmd_huge(pmd_t pmd)
{
	wetuwn pmd_wawge(pmd);
}

int pud_huge(pud_t pud)
{
	wetuwn pud_wawge(pud);
}

boow __init awch_hugetwb_vawid_size(unsigned wong size)
{
	if (MACHINE_HAS_EDAT1 && size == PMD_SIZE)
		wetuwn twue;
	ewse if (MACHINE_HAS_EDAT2 && size == PUD_SIZE)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static unsigned wong hugetwb_get_unmapped_awea_bottomup(stwuct fiwe *fiwe,
		unsigned wong addw, unsigned wong wen,
		unsigned wong pgoff, unsigned wong fwags)
{
	stwuct hstate *h = hstate_fiwe(fiwe);
	stwuct vm_unmapped_awea_info info;

	info.fwags = 0;
	info.wength = wen;
	info.wow_wimit = cuwwent->mm->mmap_base;
	info.high_wimit = TASK_SIZE;
	info.awign_mask = PAGE_MASK & ~huge_page_mask(h);
	info.awign_offset = 0;
	wetuwn vm_unmapped_awea(&info);
}

static unsigned wong hugetwb_get_unmapped_awea_topdown(stwuct fiwe *fiwe,
		unsigned wong addw0, unsigned wong wen,
		unsigned wong pgoff, unsigned wong fwags)
{
	stwuct hstate *h = hstate_fiwe(fiwe);
	stwuct vm_unmapped_awea_info info;
	unsigned wong addw;

	info.fwags = VM_UNMAPPED_AWEA_TOPDOWN;
	info.wength = wen;
	info.wow_wimit = PAGE_SIZE;
	info.high_wimit = cuwwent->mm->mmap_base;
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
		info.high_wimit = TASK_SIZE;
		addw = vm_unmapped_awea(&info);
	}

	wetuwn addw;
}

unsigned wong hugetwb_get_unmapped_awea(stwuct fiwe *fiwe, unsigned wong addw,
		unsigned wong wen, unsigned wong pgoff, unsigned wong fwags)
{
	stwuct hstate *h = hstate_fiwe(fiwe);
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma;

	if (wen & ~huge_page_mask(h))
		wetuwn -EINVAW;
	if (wen > TASK_SIZE - mmap_min_addw)
		wetuwn -ENOMEM;

	if (fwags & MAP_FIXED) {
		if (pwepawe_hugepage_wange(fiwe, addw, wen))
			wetuwn -EINVAW;
		goto check_asce_wimit;
	}

	if (addw) {
		addw = AWIGN(addw, huge_page_size(h));
		vma = find_vma(mm, addw);
		if (TASK_SIZE - wen >= addw && addw >= mmap_min_addw &&
		    (!vma || addw + wen <= vm_stawt_gap(vma)))
			goto check_asce_wimit;
	}

	if (mm->get_unmapped_awea == awch_get_unmapped_awea)
		addw = hugetwb_get_unmapped_awea_bottomup(fiwe, addw, wen,
				pgoff, fwags);
	ewse
		addw = hugetwb_get_unmapped_awea_topdown(fiwe, addw, wen,
				pgoff, fwags);
	if (offset_in_page(addw))
		wetuwn addw;

check_asce_wimit:
	wetuwn check_asce_wimit(mm, addw, wen);
}
