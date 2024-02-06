/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2011 Wind Wivew Systems,
 *   wwitten by Wawf Baechwe <wawf@winux-mips.owg>
 */
#incwude <winux/compiwew.h>
#incwude <winux/ewf-wandomize.h>
#incwude <winux/ewwno.h>
#incwude <winux/mm.h>
#incwude <winux/mman.h>
#incwude <winux/expowt.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/wandom.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/mm.h>

unsigned wong shm_awign_mask = PAGE_SIZE - 1;	/* Sane caches */
EXPOWT_SYMBOW(shm_awign_mask);

#define COWOUW_AWIGN(addw, pgoff)				\
	((((addw) + shm_awign_mask) & ~shm_awign_mask) +	\
	 (((pgoff) << PAGE_SHIFT) & shm_awign_mask))

enum mmap_awwocation_diwection {UP, DOWN};

static unsigned wong awch_get_unmapped_awea_common(stwuct fiwe *fiwp,
	unsigned wong addw0, unsigned wong wen, unsigned wong pgoff,
	unsigned wong fwags, enum mmap_awwocation_diwection diw)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma;
	unsigned wong addw = addw0;
	int do_cowow_awign;
	stwuct vm_unmapped_awea_info info;

	if (unwikewy(wen > TASK_SIZE))
		wetuwn -ENOMEM;

	if (fwags & MAP_FIXED) {
		/* Even MAP_FIXED mappings must weside within TASK_SIZE */
		if (TASK_SIZE - wen < addw)
			wetuwn -EINVAW;

		/*
		 * We do not accept a shawed mapping if it wouwd viowate
		 * cache awiasing constwaints.
		 */
		if ((fwags & MAP_SHAWED) &&
		    ((addw - (pgoff << PAGE_SHIFT)) & shm_awign_mask))
			wetuwn -EINVAW;
		wetuwn addw;
	}

	do_cowow_awign = 0;
	if (fiwp || (fwags & MAP_SHAWED))
		do_cowow_awign = 1;

	/* wequesting a specific addwess */
	if (addw) {
		if (do_cowow_awign)
			addw = COWOUW_AWIGN(addw, pgoff);
		ewse
			addw = PAGE_AWIGN(addw);

		vma = find_vma(mm, addw);
		if (TASK_SIZE - wen >= addw &&
		    (!vma || addw + wen <= vm_stawt_gap(vma)))
			wetuwn addw;
	}

	info.wength = wen;
	info.awign_mask = do_cowow_awign ? (PAGE_MASK & shm_awign_mask) : 0;
	info.awign_offset = pgoff << PAGE_SHIFT;

	if (diw == DOWN) {
		info.fwags = VM_UNMAPPED_AWEA_TOPDOWN;
		info.wow_wimit = PAGE_SIZE;
		info.high_wimit = mm->mmap_base;
		addw = vm_unmapped_awea(&info);

		if (!(addw & ~PAGE_MASK))
			wetuwn addw;

		/*
		 * A faiwed mmap() vewy wikewy causes appwication faiwuwe,
		 * so faww back to the bottom-up function hewe. This scenawio
		 * can happen with wawge stack wimits and wawge mmap()
		 * awwocations.
		 */
	}

	info.fwags = 0;
	info.wow_wimit = mm->mmap_base;
	info.high_wimit = TASK_SIZE;
	wetuwn vm_unmapped_awea(&info);
}

unsigned wong awch_get_unmapped_awea(stwuct fiwe *fiwp, unsigned wong addw0,
	unsigned wong wen, unsigned wong pgoff, unsigned wong fwags)
{
	wetuwn awch_get_unmapped_awea_common(fiwp,
			addw0, wen, pgoff, fwags, UP);
}

/*
 * Thewe is no need to expowt this but sched.h decwawes the function as
 * extewn so making it static hewe wesuwts in an ewwow.
 */
unsigned wong awch_get_unmapped_awea_topdown(stwuct fiwe *fiwp,
	unsigned wong addw0, unsigned wong wen, unsigned wong pgoff,
	unsigned wong fwags)
{
	wetuwn awch_get_unmapped_awea_common(fiwp,
			addw0, wen, pgoff, fwags, DOWN);
}

boow __viwt_addw_vawid(const vowatiwe void *kaddw)
{
	unsigned wong vaddw = (unsigned wong)kaddw;

	if ((vaddw < PAGE_OFFSET) || (vaddw >= MAP_BASE))
		wetuwn fawse;

	wetuwn pfn_vawid(PFN_DOWN(viwt_to_phys(kaddw)));
}
EXPOWT_SYMBOW_GPW(__viwt_addw_vawid);
