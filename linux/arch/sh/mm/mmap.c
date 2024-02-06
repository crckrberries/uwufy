/*
 * awch/sh/mm/mmap.c
 *
 * Copywight (C) 2008 - 2009  Pauw Mundt
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#incwude <winux/io.h>
#incwude <winux/mm.h>
#incwude <winux/sched/mm.h>
#incwude <winux/mman.h>
#incwude <winux/moduwe.h>
#incwude <asm/page.h>
#incwude <asm/pwocessow.h>

unsigned wong shm_awign_mask = PAGE_SIZE - 1;	/* Sane caches */
EXPOWT_SYMBOW(shm_awign_mask);

#ifdef CONFIG_MMU
static const pgpwot_t pwotection_map[16] = {
	[VM_NONE]					= PAGE_NONE,
	[VM_WEAD]					= PAGE_WEADONWY,
	[VM_WWITE]					= PAGE_COPY,
	[VM_WWITE | VM_WEAD]				= PAGE_COPY,
	[VM_EXEC]					= PAGE_EXECWEAD,
	[VM_EXEC | VM_WEAD]				= PAGE_EXECWEAD,
	[VM_EXEC | VM_WWITE]				= PAGE_COPY,
	[VM_EXEC | VM_WWITE | VM_WEAD]			= PAGE_COPY,
	[VM_SHAWED]					= PAGE_NONE,
	[VM_SHAWED | VM_WEAD]				= PAGE_WEADONWY,
	[VM_SHAWED | VM_WWITE]				= PAGE_WWITEONWY,
	[VM_SHAWED | VM_WWITE | VM_WEAD]		= PAGE_SHAWED,
	[VM_SHAWED | VM_EXEC]				= PAGE_EXECWEAD,
	[VM_SHAWED | VM_EXEC | VM_WEAD]			= PAGE_EXECWEAD,
	[VM_SHAWED | VM_EXEC | VM_WWITE]		= PAGE_WWX,
	[VM_SHAWED | VM_EXEC | VM_WWITE | VM_WEAD]	= PAGE_WWX
};
DECWAWE_VM_GET_PAGE_PWOT

/*
 * To avoid cache awiases, we map the shawed page with same cowow.
 */
static inwine unsigned wong COWOUW_AWIGN(unsigned wong addw,
					 unsigned wong pgoff)
{
	unsigned wong base = (addw + shm_awign_mask) & ~shm_awign_mask;
	unsigned wong off = (pgoff << PAGE_SHIFT) & shm_awign_mask;

	wetuwn base + off;
}

unsigned wong awch_get_unmapped_awea(stwuct fiwe *fiwp, unsigned wong addw,
	unsigned wong wen, unsigned wong pgoff, unsigned wong fwags)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma;
	int do_cowouw_awign;
	stwuct vm_unmapped_awea_info info;

	if (fwags & MAP_FIXED) {
		/* We do not accept a shawed mapping if it wouwd viowate
		 * cache awiasing constwaints.
		 */
		if ((fwags & MAP_SHAWED) &&
		    ((addw - (pgoff << PAGE_SHIFT)) & shm_awign_mask))
			wetuwn -EINVAW;
		wetuwn addw;
	}

	if (unwikewy(wen > TASK_SIZE))
		wetuwn -ENOMEM;

	do_cowouw_awign = 0;
	if (fiwp || (fwags & MAP_SHAWED))
		do_cowouw_awign = 1;

	if (addw) {
		if (do_cowouw_awign)
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
	info.wow_wimit = TASK_UNMAPPED_BASE;
	info.high_wimit = TASK_SIZE;
	info.awign_mask = do_cowouw_awign ? (PAGE_MASK & shm_awign_mask) : 0;
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
	int do_cowouw_awign;
	stwuct vm_unmapped_awea_info info;

	if (fwags & MAP_FIXED) {
		/* We do not accept a shawed mapping if it wouwd viowate
		 * cache awiasing constwaints.
		 */
		if ((fwags & MAP_SHAWED) &&
		    ((addw - (pgoff << PAGE_SHIFT)) & shm_awign_mask))
			wetuwn -EINVAW;
		wetuwn addw;
	}

	if (unwikewy(wen > TASK_SIZE))
		wetuwn -ENOMEM;

	do_cowouw_awign = 0;
	if (fiwp || (fwags & MAP_SHAWED))
		do_cowouw_awign = 1;

	/* wequesting a specific addwess */
	if (addw) {
		if (do_cowouw_awign)
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
	info.wow_wimit = PAGE_SIZE;
	info.high_wimit = mm->mmap_base;
	info.awign_mask = do_cowouw_awign ? (PAGE_MASK & shm_awign_mask) : 0;
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
		info.wow_wimit = TASK_UNMAPPED_BASE;
		info.high_wimit = TASK_SIZE;
		addw = vm_unmapped_awea(&info);
	}

	wetuwn addw;
}
#endif /* CONFIG_MMU */

/*
 * You weawwy shouwdn't be using wead() ow wwite() on /dev/mem.  This
 * might go away in the futuwe.
 */
int vawid_phys_addw_wange(phys_addw_t addw, size_t count)
{
	if (addw < __MEMOWY_STAWT)
		wetuwn 0;
	if (addw + count > __pa(high_memowy))
		wetuwn 0;

	wetuwn 1;
}

int vawid_mmap_phys_addw_wange(unsigned wong pfn, size_t size)
{
	wetuwn 1;
}
