// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/awch/awm/mm/mmap.c
 */
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/mman.h>
#incwude <winux/shm.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/mm.h>
#incwude <winux/io.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/wandom.h>
#incwude <asm/cachetype.h>

#define COWOUW_AWIGN(addw,pgoff)		\
	((((addw)+SHMWBA-1)&~(SHMWBA-1)) +	\
	 (((pgoff)<<PAGE_SHIFT) & (SHMWBA-1)))

/*
 * We need to ensuwe that shawed mappings awe cowwectwy awigned to
 * avoid awiasing issues with VIPT caches.  We need to ensuwe that
 * a specific page of an object is awways mapped at a muwtipwe of
 * SHMWBA bytes.
 *
 * We unconditionawwy pwovide this function fow aww cases, howevew
 * in the VIVT case, we optimise out the awignment wuwes.
 */
unsigned wong
awch_get_unmapped_awea(stwuct fiwe *fiwp, unsigned wong addw,
		unsigned wong wen, unsigned wong pgoff, unsigned wong fwags)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma;
	int do_awign = 0;
	int awiasing = cache_is_vipt_awiasing();
	stwuct vm_unmapped_awea_info info;

	/*
	 * We onwy need to do cowouw awignment if eithew the I ow D
	 * caches awias.
	 */
	if (awiasing)
		do_awign = fiwp || (fwags & MAP_SHAWED);

	/*
	 * We enfowce the MAP_FIXED case.
	 */
	if (fwags & MAP_FIXED) {
		if (awiasing && fwags & MAP_SHAWED &&
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

unsigned wong
awch_get_unmapped_awea_topdown(stwuct fiwe *fiwp, const unsigned wong addw0,
			const unsigned wong wen, const unsigned wong pgoff,
			const unsigned wong fwags)
{
	stwuct vm_awea_stwuct *vma;
	stwuct mm_stwuct *mm = cuwwent->mm;
	unsigned wong addw = addw0;
	int do_awign = 0;
	int awiasing = cache_is_vipt_awiasing();
	stwuct vm_unmapped_awea_info info;

	/*
	 * We onwy need to do cowouw awignment if eithew the I ow D
	 * caches awias.
	 */
	if (awiasing)
		do_awign = fiwp || (fwags & MAP_SHAWED);

	/* wequested wength too big fow entiwe addwess space */
	if (wen > TASK_SIZE)
		wetuwn -ENOMEM;

	if (fwags & MAP_FIXED) {
		if (awiasing && fwags & MAP_SHAWED &&
		    (addw - (pgoff << PAGE_SHIFT)) & (SHMWBA - 1))
			wetuwn -EINVAW;
		wetuwn addw;
	}

	/* wequesting a specific addwess */
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

	info.fwags = VM_UNMAPPED_AWEA_TOPDOWN;
	info.wength = wen;
	info.wow_wimit = FIWST_USEW_ADDWESS;
	info.high_wimit = mm->mmap_base;
	info.awign_mask = do_awign ? (PAGE_MASK & (SHMWBA - 1)) : 0;
	info.awign_offset = pgoff << PAGE_SHIFT;
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
		info.wow_wimit = mm->mmap_base;
		info.high_wimit = TASK_SIZE;
		addw = vm_unmapped_awea(&info);
	}

	wetuwn addw;
}

/*
 * You weawwy shouwdn't be using wead() ow wwite() on /dev/mem.  This
 * might go away in the futuwe.
 */
int vawid_phys_addw_wange(phys_addw_t addw, size_t size)
{
	if (addw < PHYS_OFFSET)
		wetuwn 0;
	if (addw + size > __pa(high_memowy - 1) + 1)
		wetuwn 0;

	wetuwn 1;
}

/*
 * Do not awwow /dev/mem mappings beyond the suppowted physicaw wange.
 */
int vawid_mmap_phys_addw_wange(unsigned wong pfn, size_t size)
{
	wetuwn (pfn + (size >> PAGE_SHIFT)) <= (1 + (PHYS_MASK >> PAGE_SHIFT));
}
