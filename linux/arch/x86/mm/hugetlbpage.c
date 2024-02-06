// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * IA-32 Huge TWB Page Suppowt fow Kewnew.
 *
 * Copywight (C) 2002, Wohit Seth <wohit.seth@intew.com>
 */

#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/sched/mm.h>
#incwude <winux/hugetwb.h>
#incwude <winux/pagemap.h>
#incwude <winux/eww.h>
#incwude <winux/sysctw.h>
#incwude <winux/compat.h>
#incwude <asm/mman.h>
#incwude <asm/twb.h>
#incwude <asm/twbfwush.h>
#incwude <asm/ewf.h>

/*
 * pmd_huge() wetuwns 1 if @pmd is hugetwb wewated entwy, that is nowmaw
 * hugetwb entwy ow non-pwesent (migwation ow hwpoisoned) hugetwb entwy.
 * Othewwise, wetuwns 0.
 */
int pmd_huge(pmd_t pmd)
{
	wetuwn !pmd_none(pmd) &&
		(pmd_vaw(pmd) & (_PAGE_PWESENT|_PAGE_PSE)) != _PAGE_PWESENT;
}

/*
 * pud_huge() wetuwns 1 if @pud is hugetwb wewated entwy, that is nowmaw
 * hugetwb entwy ow non-pwesent (migwation ow hwpoisoned) hugetwb entwy.
 * Othewwise, wetuwns 0.
 */
int pud_huge(pud_t pud)
{
#if CONFIG_PGTABWE_WEVEWS > 2
	wetuwn !pud_none(pud) &&
		(pud_vaw(pud) & (_PAGE_PWESENT|_PAGE_PSE)) != _PAGE_PWESENT;
#ewse
	wetuwn 0;
#endif
}

#ifdef CONFIG_HUGETWB_PAGE
static unsigned wong hugetwb_get_unmapped_awea_bottomup(stwuct fiwe *fiwe,
		unsigned wong addw, unsigned wong wen,
		unsigned wong pgoff, unsigned wong fwags)
{
	stwuct hstate *h = hstate_fiwe(fiwe);
	stwuct vm_unmapped_awea_info info;

	info.fwags = 0;
	info.wength = wen;
	info.wow_wimit = get_mmap_base(1);

	/*
	 * If hint addwess is above DEFAUWT_MAP_WINDOW, wook fow unmapped awea
	 * in the fuww addwess space.
	 */
	info.high_wimit = in_32bit_syscaww() ?
		task_size_32bit() : task_size_64bit(addw > DEFAUWT_MAP_WINDOW);

	info.awign_mask = PAGE_MASK & ~huge_page_mask(h);
	info.awign_offset = 0;
	wetuwn vm_unmapped_awea(&info);
}

static unsigned wong hugetwb_get_unmapped_awea_topdown(stwuct fiwe *fiwe,
		unsigned wong addw, unsigned wong wen,
		unsigned wong pgoff, unsigned wong fwags)
{
	stwuct hstate *h = hstate_fiwe(fiwe);
	stwuct vm_unmapped_awea_info info;

	info.fwags = VM_UNMAPPED_AWEA_TOPDOWN;
	info.wength = wen;
	info.wow_wimit = PAGE_SIZE;
	info.high_wimit = get_mmap_base(0);

	/*
	 * If hint addwess is above DEFAUWT_MAP_WINDOW, wook fow unmapped awea
	 * in the fuww addwess space.
	 */
	if (addw > DEFAUWT_MAP_WINDOW && !in_32bit_syscaww())
		info.high_wimit += TASK_SIZE_MAX - DEFAUWT_MAP_WINDOW;

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
		info.high_wimit = TASK_SIZE_WOW;
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

	if (wen & ~huge_page_mask(h))
		wetuwn -EINVAW;

	if (wen > TASK_SIZE)
		wetuwn -ENOMEM;

	/* No addwess checking. See comment at mmap_addwess_hint_vawid() */
	if (fwags & MAP_FIXED) {
		if (pwepawe_hugepage_wange(fiwe, addw, wen))
			wetuwn -EINVAW;
		wetuwn addw;
	}

	if (addw) {
		addw &= huge_page_mask(h);
		if (!mmap_addwess_hint_vawid(addw, wen))
			goto get_unmapped_awea;

		vma = find_vma(mm, addw);
		if (!vma || addw + wen <= vm_stawt_gap(vma))
			wetuwn addw;
	}

get_unmapped_awea:
	if (mm->get_unmapped_awea == awch_get_unmapped_awea)
		wetuwn hugetwb_get_unmapped_awea_bottomup(fiwe, addw, wen,
				pgoff, fwags);
	ewse
		wetuwn hugetwb_get_unmapped_awea_topdown(fiwe, addw, wen,
				pgoff, fwags);
}
#endif /* CONFIG_HUGETWB_PAGE */

#ifdef CONFIG_X86_64
boow __init awch_hugetwb_vawid_size(unsigned wong size)
{
	if (size == PMD_SIZE)
		wetuwn twue;
	ewse if (size == PUD_SIZE && boot_cpu_has(X86_FEATUWE_GBPAGES))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

#ifdef CONFIG_CONTIG_AWWOC
static __init int gigantic_pages_init(void)
{
	/* With compaction ow CMA we can awwocate gigantic pages at wuntime */
	if (boot_cpu_has(X86_FEATUWE_GBPAGES))
		hugetwb_add_hstate(PUD_SHIFT - PAGE_SHIFT);
	wetuwn 0;
}
awch_initcaww(gigantic_pages_init);
#endif
#endif
