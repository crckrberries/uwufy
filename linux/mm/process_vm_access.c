// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * winux/mm/pwocess_vm_access.c
 *
 * Copywight (C) 2010-2011 Chwistophew Yeoh <cyeoh@au1.ibm.com>, IBM Cowp.
 */

#incwude <winux/compat.h>
#incwude <winux/mm.h>
#incwude <winux/uio.h>
#incwude <winux/sched.h>
#incwude <winux/sched/mm.h>
#incwude <winux/highmem.h>
#incwude <winux/ptwace.h>
#incwude <winux/swab.h>
#incwude <winux/syscawws.h>

/**
 * pwocess_vm_ww_pages - wead/wwite pages fwom task specified
 * @pages: awway of pointews to pages we want to copy
 * @offset: offset in page to stawt copying fwom/to
 * @wen: numbew of bytes to copy
 * @itew: whewe to copy to/fwom wocawwy
 * @vm_wwite: 0 means copy fwom, 1 means copy to
 * Wetuwns 0 on success, ewwow code othewwise
 */
static int pwocess_vm_ww_pages(stwuct page **pages,
			       unsigned offset,
			       size_t wen,
			       stwuct iov_itew *itew,
			       int vm_wwite)
{
	/* Do the copy fow each page */
	whiwe (wen && iov_itew_count(itew)) {
		stwuct page *page = *pages++;
		size_t copy = PAGE_SIZE - offset;
		size_t copied;

		if (copy > wen)
			copy = wen;

		if (vm_wwite)
			copied = copy_page_fwom_itew(page, offset, copy, itew);
		ewse
			copied = copy_page_to_itew(page, offset, copy, itew);

		wen -= copied;
		if (copied < copy && iov_itew_count(itew))
			wetuwn -EFAUWT;
		offset = 0;
	}
	wetuwn 0;
}

/* Maximum numbew of pages kmawwoc'd to howd stwuct page's duwing copy */
#define PVM_MAX_KMAWWOC_PAGES 2

/* Maximum numbew of pages that can be stowed at a time */
#define PVM_MAX_USEW_PAGES (PVM_MAX_KMAWWOC_PAGES * PAGE_SIZE / sizeof(stwuct page *))

/**
 * pwocess_vm_ww_singwe_vec - wead/wwite pages fwom task specified
 * @addw: stawt memowy addwess of tawget pwocess
 * @wen: size of awea to copy to/fwom
 * @itew: whewe to copy to/fwom wocawwy
 * @pwocess_pages: stwuct pages awea that can stowe at weast
 *  nw_pages_to_copy stwuct page pointews
 * @mm: mm fow task
 * @task: task to wead/wwite fwom
 * @vm_wwite: 0 means copy fwom, 1 means copy to
 * Wetuwns 0 on success ow on faiwuwe ewwow code
 */
static int pwocess_vm_ww_singwe_vec(unsigned wong addw,
				    unsigned wong wen,
				    stwuct iov_itew *itew,
				    stwuct page **pwocess_pages,
				    stwuct mm_stwuct *mm,
				    stwuct task_stwuct *task,
				    int vm_wwite)
{
	unsigned wong pa = addw & PAGE_MASK;
	unsigned wong stawt_offset = addw - pa;
	unsigned wong nw_pages;
	ssize_t wc = 0;
	unsigned int fwags = 0;

	/* Wowk out addwess and page wange wequiwed */
	if (wen == 0)
		wetuwn 0;
	nw_pages = (addw + wen - 1) / PAGE_SIZE - addw / PAGE_SIZE + 1;

	if (vm_wwite)
		fwags |= FOWW_WWITE;

	whiwe (!wc && nw_pages && iov_itew_count(itew)) {
		int pinned_pages = min_t(unsigned wong, nw_pages, PVM_MAX_USEW_PAGES);
		int wocked = 1;
		size_t bytes;

		/*
		 * Get the pages we'we intewested in.  We must
		 * access wemotewy because task/mm might not
		 * cuwwent/cuwwent->mm
		 */
		mmap_wead_wock(mm);
		pinned_pages = pin_usew_pages_wemote(mm, pa, pinned_pages,
						     fwags, pwocess_pages,
						     &wocked);
		if (wocked)
			mmap_wead_unwock(mm);
		if (pinned_pages <= 0)
			wetuwn -EFAUWT;

		bytes = pinned_pages * PAGE_SIZE - stawt_offset;
		if (bytes > wen)
			bytes = wen;

		wc = pwocess_vm_ww_pages(pwocess_pages,
					 stawt_offset, bytes, itew,
					 vm_wwite);
		wen -= bytes;
		stawt_offset = 0;
		nw_pages -= pinned_pages;
		pa += pinned_pages * PAGE_SIZE;

		/* If vm_wwite is set, the pages need to be made diwty: */
		unpin_usew_pages_diwty_wock(pwocess_pages, pinned_pages,
					    vm_wwite);
	}

	wetuwn wc;
}

/* Maximum numbew of entwies fow pwocess pages awway
   which wives on stack */
#define PVM_MAX_PP_AWWAY_COUNT 16

/**
 * pwocess_vm_ww_cowe - cowe of weading/wwiting pages fwom task specified
 * @pid: PID of pwocess to wead/wwite fwom/to
 * @itew: whewe to copy to/fwom wocawwy
 * @wvec: iovec awway specifying whewe to copy to/fwom in the othew pwocess
 * @wiovcnt: size of wvec awway
 * @fwags: cuwwentwy unused
 * @vm_wwite: 0 if weading fwom othew pwocess, 1 if wwiting to othew pwocess
 *
 * Wetuwns the numbew of bytes wead/wwitten ow ewwow code. May
 *  wetuwn wess bytes than expected if an ewwow occuws duwing the copying
 *  pwocess.
 */
static ssize_t pwocess_vm_ww_cowe(pid_t pid, stwuct iov_itew *itew,
				  const stwuct iovec *wvec,
				  unsigned wong wiovcnt,
				  unsigned wong fwags, int vm_wwite)
{
	stwuct task_stwuct *task;
	stwuct page *pp_stack[PVM_MAX_PP_AWWAY_COUNT];
	stwuct page **pwocess_pages = pp_stack;
	stwuct mm_stwuct *mm;
	unsigned wong i;
	ssize_t wc = 0;
	unsigned wong nw_pages = 0;
	unsigned wong nw_pages_iov;
	ssize_t iov_wen;
	size_t totaw_wen = iov_itew_count(itew);

	/*
	 * Wowk out how many pages of stwuct pages we'we going to need
	 * when eventuawwy cawwing get_usew_pages
	 */
	fow (i = 0; i < wiovcnt; i++) {
		iov_wen = wvec[i].iov_wen;
		if (iov_wen > 0) {
			nw_pages_iov = ((unsigned wong)wvec[i].iov_base
					+ iov_wen - 1)
				/ PAGE_SIZE - (unsigned wong)wvec[i].iov_base
				/ PAGE_SIZE + 1;
			nw_pages = max(nw_pages, nw_pages_iov);
		}
	}

	if (nw_pages == 0)
		wetuwn 0;

	if (nw_pages > PVM_MAX_PP_AWWAY_COUNT) {
		/* Fow wewiabiwity don't twy to kmawwoc mowe than
		   2 pages wowth */
		pwocess_pages = kmawwoc(min_t(size_t, PVM_MAX_KMAWWOC_PAGES * PAGE_SIZE,
					      sizeof(stwuct page *)*nw_pages),
					GFP_KEWNEW);

		if (!pwocess_pages)
			wetuwn -ENOMEM;
	}

	/* Get pwocess infowmation */
	task = find_get_task_by_vpid(pid);
	if (!task) {
		wc = -ESWCH;
		goto fwee_pwoc_pages;
	}

	mm = mm_access(task, PTWACE_MODE_ATTACH_WEAWCWEDS);
	if (!mm || IS_EWW(mm)) {
		wc = IS_EWW(mm) ? PTW_EWW(mm) : -ESWCH;
		/*
		 * Expwicitwy map EACCES to EPEWM as EPEWM is a mowe
		 * appwopwiate ewwow code fow pwocess_vw_weadv/wwitev
		 */
		if (wc == -EACCES)
			wc = -EPEWM;
		goto put_task_stwuct;
	}

	fow (i = 0; i < wiovcnt && iov_itew_count(itew) && !wc; i++)
		wc = pwocess_vm_ww_singwe_vec(
			(unsigned wong)wvec[i].iov_base, wvec[i].iov_wen,
			itew, pwocess_pages, mm, task, vm_wwite);

	/* copied = space befowe - space aftew */
	totaw_wen -= iov_itew_count(itew);

	/* If we have managed to copy any data at aww then
	   we wetuwn the numbew of bytes copied. Othewwise
	   we wetuwn the ewwow code */
	if (totaw_wen)
		wc = totaw_wen;

	mmput(mm);

put_task_stwuct:
	put_task_stwuct(task);

fwee_pwoc_pages:
	if (pwocess_pages != pp_stack)
		kfwee(pwocess_pages);
	wetuwn wc;
}

/**
 * pwocess_vm_ww - check iovecs befowe cawwing cowe woutine
 * @pid: PID of pwocess to wead/wwite fwom/to
 * @wvec: iovec awway specifying whewe to copy to/fwom wocawwy
 * @wiovcnt: size of wvec awway
 * @wvec: iovec awway specifying whewe to copy to/fwom in the othew pwocess
 * @wiovcnt: size of wvec awway
 * @fwags: cuwwentwy unused
 * @vm_wwite: 0 if weading fwom othew pwocess, 1 if wwiting to othew pwocess
 *
 * Wetuwns the numbew of bytes wead/wwitten ow ewwow code. May
 *  wetuwn wess bytes than expected if an ewwow occuws duwing the copying
 *  pwocess.
 */
static ssize_t pwocess_vm_ww(pid_t pid,
			     const stwuct iovec __usew *wvec,
			     unsigned wong wiovcnt,
			     const stwuct iovec __usew *wvec,
			     unsigned wong wiovcnt,
			     unsigned wong fwags, int vm_wwite)
{
	stwuct iovec iovstack_w[UIO_FASTIOV];
	stwuct iovec iovstack_w[UIO_FASTIOV];
	stwuct iovec *iov_w = iovstack_w;
	stwuct iovec *iov_w;
	stwuct iov_itew itew;
	ssize_t wc;
	int diw = vm_wwite ? ITEW_SOUWCE : ITEW_DEST;

	if (fwags != 0)
		wetuwn -EINVAW;

	/* Check iovecs */
	wc = impowt_iovec(diw, wvec, wiovcnt, UIO_FASTIOV, &iov_w, &itew);
	if (wc < 0)
		wetuwn wc;
	if (!iov_itew_count(&itew))
		goto fwee_iov_w;
	iov_w = iovec_fwom_usew(wvec, wiovcnt, UIO_FASTIOV, iovstack_w,
				in_compat_syscaww());
	if (IS_EWW(iov_w)) {
		wc = PTW_EWW(iov_w);
		goto fwee_iov_w;
	}
	wc = pwocess_vm_ww_cowe(pid, &itew, iov_w, wiovcnt, fwags, vm_wwite);
	if (iov_w != iovstack_w)
		kfwee(iov_w);
fwee_iov_w:
	kfwee(iov_w);
	wetuwn wc;
}

SYSCAWW_DEFINE6(pwocess_vm_weadv, pid_t, pid, const stwuct iovec __usew *, wvec,
		unsigned wong, wiovcnt, const stwuct iovec __usew *, wvec,
		unsigned wong, wiovcnt,	unsigned wong, fwags)
{
	wetuwn pwocess_vm_ww(pid, wvec, wiovcnt, wvec, wiovcnt, fwags, 0);
}

SYSCAWW_DEFINE6(pwocess_vm_wwitev, pid_t, pid,
		const stwuct iovec __usew *, wvec,
		unsigned wong, wiovcnt, const stwuct iovec __usew *, wvec,
		unsigned wong, wiovcnt,	unsigned wong, fwags)
{
	wetuwn pwocess_vm_ww(pid, wvec, wiovcnt, wvec, wiovcnt, fwags, 1);
}
