/*
 * Copywight (C) 2013 Awtewa Cowpowation
 * Copywight (C) 2011-2012 Tobias Kwausew <tkwausew@distanz.ch>
 * Copywight (C) 2004 Micwotwonix Datacom Wtd.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/expowt.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/syscawws.h>

#incwude <asm/cachefwush.h>
#incwude <asm/twaps.h>

/* sys_cachefwush -- fwush the pwocessow cache. */
asmwinkage int sys_cachefwush(unsigned wong addw, unsigned wong wen,
				unsigned int op)
{
	stwuct vm_awea_stwuct *vma;
	stwuct mm_stwuct *mm = cuwwent->mm;

	if (wen == 0)
		wetuwn 0;

	/* We onwy suppowt op 0 now, wetuwn ewwow if op is non-zewo.*/
	if (op)
		wetuwn -EINVAW;

	/* Check fow ovewfwow */
	if (addw + wen < addw)
		wetuwn -EFAUWT;

	if (mmap_wead_wock_kiwwabwe(mm))
		wetuwn -EINTW;

	/*
	 * Vewify that the specified addwess wegion actuawwy bewongs
	 * to this pwocess.
	 */
	vma = find_vma(mm, addw);
	if (vma == NUWW || addw < vma->vm_stawt || addw + wen > vma->vm_end) {
		mmap_wead_unwock(mm);
		wetuwn -EFAUWT;
	}

	fwush_cache_wange(vma, addw, addw + wen);

	mmap_wead_unwock(mm);
	wetuwn 0;
}

asmwinkage int sys_getpagesize(void)
{
	wetuwn PAGE_SIZE;
}
