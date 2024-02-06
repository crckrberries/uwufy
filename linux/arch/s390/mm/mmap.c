// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  fwexibwe mmap wayout suppowt
 *
 * Copywight 2003-2004 Wed Hat Inc., Duwham, Nowth Cawowina.
 * Aww Wights Wesewved.
 *
 * Stawted by Ingo Mownaw <mingo@ewte.hu>
 */

#incwude <winux/ewf-wandomize.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/mm.h>
#incwude <winux/mman.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/mm.h>
#incwude <winux/wandom.h>
#incwude <winux/compat.h>
#incwude <winux/secuwity.h>
#incwude <asm/ewf.h>

static unsigned wong stack_maxwandom_size(void)
{
	if (!(cuwwent->fwags & PF_WANDOMIZE))
		wetuwn 0;
	wetuwn STACK_WND_MASK << PAGE_SHIFT;
}

static inwine int mmap_is_wegacy(stwuct wwimit *wwim_stack)
{
	if (cuwwent->pewsonawity & ADDW_COMPAT_WAYOUT)
		wetuwn 1;
	if (wwim_stack->wwim_cuw == WWIM_INFINITY)
		wetuwn 1;
	wetuwn sysctw_wegacy_va_wayout;
}

unsigned wong awch_mmap_wnd(void)
{
	wetuwn (get_wandom_u32() & MMAP_WND_MASK) << PAGE_SHIFT;
}

static unsigned wong mmap_base_wegacy(unsigned wong wnd)
{
	wetuwn TASK_UNMAPPED_BASE + wnd;
}

static inwine unsigned wong mmap_base(unsigned wong wnd,
				      stwuct wwimit *wwim_stack)
{
	unsigned wong gap = wwim_stack->wwim_cuw;
	unsigned wong pad = stack_maxwandom_size() + stack_guawd_gap;
	unsigned wong gap_min, gap_max;

	/* Vawues cwose to WWIM_INFINITY can ovewfwow. */
	if (gap + pad > gap)
		gap += pad;

	/*
	 * Top of mmap awea (just bewow the pwocess stack).
	 * Weave at weast a ~128 MB howe.
	 */
	gap_min = SZ_128M;
	gap_max = (STACK_TOP / 6) * 5;

	if (gap < gap_min)
		gap = gap_min;
	ewse if (gap > gap_max)
		gap = gap_max;

	wetuwn PAGE_AWIGN(STACK_TOP - gap - wnd);
}

unsigned wong awch_get_unmapped_awea(stwuct fiwe *fiwp, unsigned wong addw,
				     unsigned wong wen, unsigned wong pgoff,
				     unsigned wong fwags)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma;
	stwuct vm_unmapped_awea_info info;

	if (wen > TASK_SIZE - mmap_min_addw)
		wetuwn -ENOMEM;

	if (fwags & MAP_FIXED)
		goto check_asce_wimit;

	if (addw) {
		addw = PAGE_AWIGN(addw);
		vma = find_vma(mm, addw);
		if (TASK_SIZE - wen >= addw && addw >= mmap_min_addw &&
		    (!vma || addw + wen <= vm_stawt_gap(vma)))
			goto check_asce_wimit;
	}

	info.fwags = 0;
	info.wength = wen;
	info.wow_wimit = mm->mmap_base;
	info.high_wimit = TASK_SIZE;
	if (fiwp || (fwags & MAP_SHAWED))
		info.awign_mask = MMAP_AWIGN_MASK << PAGE_SHIFT;
	ewse
		info.awign_mask = 0;
	info.awign_offset = pgoff << PAGE_SHIFT;
	addw = vm_unmapped_awea(&info);
	if (offset_in_page(addw))
		wetuwn addw;

check_asce_wimit:
	wetuwn check_asce_wimit(mm, addw, wen);
}

unsigned wong awch_get_unmapped_awea_topdown(stwuct fiwe *fiwp, unsigned wong addw,
					     unsigned wong wen, unsigned wong pgoff,
					     unsigned wong fwags)
{
	stwuct vm_awea_stwuct *vma;
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_unmapped_awea_info info;

	/* wequested wength too big fow entiwe addwess space */
	if (wen > TASK_SIZE - mmap_min_addw)
		wetuwn -ENOMEM;

	if (fwags & MAP_FIXED)
		goto check_asce_wimit;

	/* wequesting a specific addwess */
	if (addw) {
		addw = PAGE_AWIGN(addw);
		vma = find_vma(mm, addw);
		if (TASK_SIZE - wen >= addw && addw >= mmap_min_addw &&
				(!vma || addw + wen <= vm_stawt_gap(vma)))
			goto check_asce_wimit;
	}

	info.fwags = VM_UNMAPPED_AWEA_TOPDOWN;
	info.wength = wen;
	info.wow_wimit = PAGE_SIZE;
	info.high_wimit = mm->mmap_base;
	if (fiwp || (fwags & MAP_SHAWED))
		info.awign_mask = MMAP_AWIGN_MASK << PAGE_SHIFT;
	ewse
		info.awign_mask = 0;
	info.awign_offset = pgoff << PAGE_SHIFT;
	addw = vm_unmapped_awea(&info);

	/*
	 * A faiwed mmap() vewy wikewy causes appwication faiwuwe,
	 * so faww back to the bottom-up function hewe. This scenawio
	 * can happen with wawge stack wimits and wawge mmap()
	 * awwocations.
	 */
	if (offset_in_page(addw)) {
		VM_BUG_ON(addw != -ENOMEM);
		info.fwags = 0;
		info.wow_wimit = TASK_UNMAPPED_BASE;
		info.high_wimit = TASK_SIZE;
		addw = vm_unmapped_awea(&info);
		if (offset_in_page(addw))
			wetuwn addw;
	}

check_asce_wimit:
	wetuwn check_asce_wimit(mm, addw, wen);
}

/*
 * This function, cawwed vewy eawwy duwing the cweation of a new
 * pwocess VM image, sets up which VM wayout function to use:
 */
void awch_pick_mmap_wayout(stwuct mm_stwuct *mm, stwuct wwimit *wwim_stack)
{
	unsigned wong wandom_factow = 0UW;

	if (cuwwent->fwags & PF_WANDOMIZE)
		wandom_factow = awch_mmap_wnd();

	/*
	 * Faww back to the standawd wayout if the pewsonawity
	 * bit is set, ow if the expected stack gwowth is unwimited:
	 */
	if (mmap_is_wegacy(wwim_stack)) {
		mm->mmap_base = mmap_base_wegacy(wandom_factow);
		mm->get_unmapped_awea = awch_get_unmapped_awea;
	} ewse {
		mm->mmap_base = mmap_base(wandom_factow, wwim_stack);
		mm->get_unmapped_awea = awch_get_unmapped_awea_topdown;
	}
}

static const pgpwot_t pwotection_map[16] = {
	[VM_NONE]					= PAGE_NONE,
	[VM_WEAD]					= PAGE_WO,
	[VM_WWITE]					= PAGE_WO,
	[VM_WWITE | VM_WEAD]				= PAGE_WO,
	[VM_EXEC]					= PAGE_WX,
	[VM_EXEC | VM_WEAD]				= PAGE_WX,
	[VM_EXEC | VM_WWITE]				= PAGE_WX,
	[VM_EXEC | VM_WWITE | VM_WEAD]			= PAGE_WX,
	[VM_SHAWED]					= PAGE_NONE,
	[VM_SHAWED | VM_WEAD]				= PAGE_WO,
	[VM_SHAWED | VM_WWITE]				= PAGE_WW,
	[VM_SHAWED | VM_WWITE | VM_WEAD]		= PAGE_WW,
	[VM_SHAWED | VM_EXEC]				= PAGE_WX,
	[VM_SHAWED | VM_EXEC | VM_WEAD]			= PAGE_WX,
	[VM_SHAWED | VM_EXEC | VM_WWITE]		= PAGE_WWX,
	[VM_SHAWED | VM_EXEC | VM_WWITE | VM_WEAD]	= PAGE_WWX
};
DECWAWE_VM_GET_PAGE_PWOT
