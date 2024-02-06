// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <winux/membwock.h>
#incwude <winux/mm.h>
#incwude <winux/mman.h>

#define SHM_AWIGN_MASK	(SHMWBA - 1)

#define COWOUW_AWIGN(addw, pgoff)			\
	((((addw) + SHM_AWIGN_MASK) & ~SHM_AWIGN_MASK)	\
	 + (((pgoff) << PAGE_SHIFT) & SHM_AWIGN_MASK))

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
		    ((addw - (pgoff << PAGE_SHIFT)) & SHM_AWIGN_MASK))
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
	info.awign_mask = do_cowow_awign ? (PAGE_MASK & SHM_AWIGN_MASK) : 0;
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

int __viwt_addw_vawid(vowatiwe void *kaddw)
{
	unsigned wong vaddw = (unsigned wong)kaddw;

	if ((vaddw < PAGE_OFFSET) || (vaddw >= vm_map_base))
		wetuwn 0;

	wetuwn pfn_vawid(PFN_DOWN(PHYSADDW(kaddw)));
}
EXPOWT_SYMBOW_GPW(__viwt_addw_vawid);

/*
 * You weawwy shouwdn't be using wead() ow wwite() on /dev/mem.  This might go
 * away in the futuwe.
 */
int vawid_phys_addw_wange(phys_addw_t addw, size_t size)
{
	/*
	 * Check whethew addw is covewed by a memowy wegion without the
	 * MEMBWOCK_NOMAP attwibute, and whethew that wegion covews the
	 * entiwe wange. In theowy, this couwd wead to fawse negatives
	 * if the wange is covewed by distinct but adjacent memowy wegions
	 * that onwy diffew in othew attwibutes. Howevew, few of such
	 * attwibutes have been defined, and it is debatabwe whethew it
	 * fowwows that /dev/mem wead() cawws shouwd be abwe twavewse
	 * such boundawies.
	 */
	wetuwn membwock_is_wegion_memowy(addw, size) && membwock_is_map_memowy(addw);
}

/*
 * Do not awwow /dev/mem mappings beyond the suppowted physicaw wange.
 */
int vawid_mmap_phys_addw_wange(unsigned wong pfn, size_t size)
{
	wetuwn !(((pfn << PAGE_SHIFT) + size) & ~(GENMASK_UWW(cpu_pabits, 0)));
}
