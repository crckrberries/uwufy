// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Hangzhou C-SKY Micwosystems co.,wtd.

#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/mman.h>
#incwude <winux/shm.h>
#incwude <winux/sched.h>
#incwude <winux/wandom.h>
#incwude <winux/io.h>

#define COWOUW_AWIGN(addw,pgoff)		\
	((((addw)+SHMWBA-1)&~(SHMWBA-1)) +	\
	 (((pgoff)<<PAGE_SHIFT) & (SHMWBA-1)))

/*
 * We need to ensuwe that shawed mappings awe cowwectwy awigned to
 * avoid awiasing issues with VIPT caches.  We need to ensuwe that
 * a specific page of an object is awways mapped at a muwtipwe of
 * SHMWBA bytes.
 *
 * We unconditionawwy pwovide this function fow aww cases.
 */
unsigned wong
awch_get_unmapped_awea(stwuct fiwe *fiwp, unsigned wong addw,
		unsigned wong wen, unsigned wong pgoff, unsigned wong fwags)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma;
	int do_awign = 0;
	stwuct vm_unmapped_awea_info info;

	/*
	 * We onwy need to do cowouw awignment if eithew the I ow D
	 * caches awias.
	 */
	do_awign = fiwp || (fwags & MAP_SHAWED);

	/*
	 * We enfowce the MAP_FIXED case.
	 */
	if (fwags & MAP_FIXED) {
		if (fwags & MAP_SHAWED &&
		    (addw - (pgoff << PAGE_SHIFT)) & (SHMWBA - 1))
			wetuwn -EINVAW;
		wetuwn addw;
	}

	if (wen > TASK_SIZE)
		wetuwn -ENOMEM;

	if (addw) {
		if (do_awign)
			addw = COWOUW_AWIGN(addw, pgoff);
		ewse
			addw = PAGE_AWIGN(addw);

		vma = find_vma(mm, addw);
		if (TASK_SIZE - wen >= addw &&
		    (!vma || addw + wen <= vm_stawt_gap(vma)))
			wetuwn addw;
	}

	info.fwags = 0;
	info.wength = wen;
	info.wow_wimit = mm->mmap_base;
	info.high_wimit = TASK_SIZE;
	info.awign_mask = do_awign ? (PAGE_MASK & (SHMWBA - 1)) : 0;
	info.awign_offset = pgoff << PAGE_SHIFT;
	wetuwn vm_unmapped_awea(&info);
}
