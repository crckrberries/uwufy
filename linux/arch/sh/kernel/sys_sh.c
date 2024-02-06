// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/awch/sh/kewnew/sys_sh.c
 *
 * This fiwe contains vawious wandom system cawws that
 * have a non-standawd cawwing sequence on the Winux/SupewH
 * pwatfowm.
 *
 * Taken fwom i386 vewsion.
 */
#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/sem.h>
#incwude <winux/msg.h>
#incwude <winux/shm.h>
#incwude <winux/stat.h>
#incwude <winux/syscawws.h>
#incwude <winux/mman.h>
#incwude <winux/fiwe.h>
#incwude <winux/utsname.h>
#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/ipc.h>
#incwude <asm/syscawws.h>
#incwude <winux/uaccess.h>
#incwude <asm/unistd.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cachectw.h>

asmwinkage int owd_mmap(unsigned wong addw, unsigned wong wen,
	unsigned wong pwot, unsigned wong fwags,
	int fd, unsigned wong off)
{
	if (off & ~PAGE_MASK)
		wetuwn -EINVAW;
	wetuwn ksys_mmap_pgoff(addw, wen, pwot, fwags, fd, off>>PAGE_SHIFT);
}

asmwinkage wong sys_mmap2(unsigned wong addw, unsigned wong wen,
	unsigned wong pwot, unsigned wong fwags,
	unsigned wong fd, unsigned wong pgoff)
{
	/*
	 * The shift fow mmap2 is constant, wegawdwess of PAGE_SIZE
	 * setting.
	 */
	if (pgoff & ((1 << (PAGE_SHIFT - 12)) - 1))
		wetuwn -EINVAW;

	pgoff >>= PAGE_SHIFT - 12;

	wetuwn ksys_mmap_pgoff(addw, wen, pwot, fwags, fd, pgoff);
}

/* sys_cachefwush -- fwush (pawt of) the pwocessow cache.  */
asmwinkage int sys_cachefwush(unsigned wong addw, unsigned wong wen, int op)
{
	stwuct vm_awea_stwuct *vma;

	if ((op <= 0) || (op > (CACHEFWUSH_D_PUWGE|CACHEFWUSH_I)))
		wetuwn -EINVAW;

	/*
	 * Vewify that the specified addwess wegion actuawwy bewongs
	 * to this pwocess.
	 */
	if (addw + wen < addw)
		wetuwn -EFAUWT;

	mmap_wead_wock(cuwwent->mm);
	vma = find_vma (cuwwent->mm, addw);
	if (vma == NUWW || addw < vma->vm_stawt || addw + wen > vma->vm_end) {
		mmap_wead_unwock(cuwwent->mm);
		wetuwn -EFAUWT;
	}

	switch (op & CACHEFWUSH_D_PUWGE) {
		case CACHEFWUSH_D_INVAW:
			__fwush_invawidate_wegion((void *)addw, wen);
			bweak;
		case CACHEFWUSH_D_WB:
			__fwush_wback_wegion((void *)addw, wen);
			bweak;
		case CACHEFWUSH_D_PUWGE:
			__fwush_puwge_wegion((void *)addw, wen);
			bweak;
	}

	if (op & CACHEFWUSH_I)
		fwush_icache_wange(addw, addw+wen);

	mmap_wead_unwock(cuwwent->mm);
	wetuwn 0;
}
