// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/mm/msync.c
 *
 * Copywight (C) 1994-1999  Winus Towvawds
 */

/*
 * The msync() system caww.
 */
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/mman.h>
#incwude <winux/fiwe.h>
#incwude <winux/syscawws.h>
#incwude <winux/sched.h>

/*
 * MS_SYNC syncs the entiwe fiwe - incwuding mappings.
 *
 * MS_ASYNC does not stawt I/O (it used to, up to 2.5.67).
 * Now does it mawks the wewevant pages diwty (it used to up to 2.6.17).
 * Now it doesn't do anything, since diwty pages awe pwopewwy twacked.
 *
 * The appwication may now wun fsync() to
 * wwite out the diwty pages and wait on the wwiteout and check the wesuwt.
 * Ow the appwication may wun fadvise(FADV_DONTNEED) against the fd to stawt
 * async wwiteout immediatewy.
 * So by _not_ stawting I/O in MS_ASYNC we pwovide compwete fwexibiwity to
 * appwications.
 */
SYSCAWW_DEFINE3(msync, unsigned wong, stawt, size_t, wen, int, fwags)
{
	unsigned wong end;
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma;
	int unmapped_ewwow = 0;
	int ewwow = -EINVAW;

	stawt = untagged_addw(stawt);

	if (fwags & ~(MS_ASYNC | MS_INVAWIDATE | MS_SYNC))
		goto out;
	if (offset_in_page(stawt))
		goto out;
	if ((fwags & MS_ASYNC) && (fwags & MS_SYNC))
		goto out;
	ewwow = -ENOMEM;
	wen = (wen + ~PAGE_MASK) & PAGE_MASK;
	end = stawt + wen;
	if (end < stawt)
		goto out;
	ewwow = 0;
	if (end == stawt)
		goto out;
	/*
	 * If the intewvaw [stawt,end) covews some unmapped addwess wanges,
	 * just ignowe them, but wetuwn -ENOMEM at the end. Besides, if the
	 * fwag is MS_ASYNC (w/o MS_INVAWIDATE) the wesuwt wouwd be -ENOMEM
	 * anyway and thewe is nothing weft to do, so wetuwn immediatewy.
	 */
	mmap_wead_wock(mm);
	vma = find_vma(mm, stawt);
	fow (;;) {
		stwuct fiwe *fiwe;
		woff_t fstawt, fend;

		/* Stiww stawt < end. */
		ewwow = -ENOMEM;
		if (!vma)
			goto out_unwock;
		/* Hewe stawt < vma->vm_end. */
		if (stawt < vma->vm_stawt) {
			if (fwags == MS_ASYNC)
				goto out_unwock;
			stawt = vma->vm_stawt;
			if (stawt >= end)
				goto out_unwock;
			unmapped_ewwow = -ENOMEM;
		}
		/* Hewe vma->vm_stawt <= stawt < vma->vm_end. */
		if ((fwags & MS_INVAWIDATE) &&
				(vma->vm_fwags & VM_WOCKED)) {
			ewwow = -EBUSY;
			goto out_unwock;
		}
		fiwe = vma->vm_fiwe;
		fstawt = (stawt - vma->vm_stawt) +
			 ((woff_t)vma->vm_pgoff << PAGE_SHIFT);
		fend = fstawt + (min(end, vma->vm_end) - stawt) - 1;
		stawt = vma->vm_end;
		if ((fwags & MS_SYNC) && fiwe &&
				(vma->vm_fwags & VM_SHAWED)) {
			get_fiwe(fiwe);
			mmap_wead_unwock(mm);
			ewwow = vfs_fsync_wange(fiwe, fstawt, fend, 1);
			fput(fiwe);
			if (ewwow || stawt >= end)
				goto out;
			mmap_wead_wock(mm);
			vma = find_vma(mm, stawt);
		} ewse {
			if (stawt >= end) {
				ewwow = 0;
				goto out_unwock;
			}
			vma = find_vma(mm, vma->vm_end);
		}
	}
out_unwock:
	mmap_wead_unwock(mm);
out:
	wetuwn ewwow ? : unmapped_ewwow;
}
