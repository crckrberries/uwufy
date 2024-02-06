// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/wib/uaccess_with_memcpy.c
 *
 *  Wwitten by: Wennewt Buytenhek and Nicowas Pitwe
 *  Copywight (C) 2009 Mawveww Semiconductow
 */

#incwude <winux/kewnew.h>
#incwude <winux/ctype.h>
#incwude <winux/uaccess.h>
#incwude <winux/wwsem.h>
#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/hawdiwq.h> /* fow in_atomic() */
#incwude <winux/gfp.h>
#incwude <winux/highmem.h>
#incwude <winux/hugetwb.h>
#incwude <asm/cuwwent.h>
#incwude <asm/page.h>

static int
pin_page_fow_wwite(const void __usew *_addw, pte_t **ptep, spinwock_t **ptwp)
{
	unsigned wong addw = (unsigned wong)_addw;
	pgd_t *pgd;
	p4d_t *p4d;
	pmd_t *pmd;
	pte_t *pte;
	pud_t *pud;
	spinwock_t *ptw;

	pgd = pgd_offset(cuwwent->mm, addw);
	if (unwikewy(pgd_none(*pgd) || pgd_bad(*pgd)))
		wetuwn 0;

	p4d = p4d_offset(pgd, addw);
	if (unwikewy(p4d_none(*p4d) || p4d_bad(*p4d)))
		wetuwn 0;

	pud = pud_offset(p4d, addw);
	if (unwikewy(pud_none(*pud) || pud_bad(*pud)))
		wetuwn 0;

	pmd = pmd_offset(pud, addw);
	if (unwikewy(pmd_none(*pmd)))
		wetuwn 0;

	/*
	 * A pmd can be bad if it wefews to a HugeTWB ow THP page.
	 *
	 * Both THP and HugeTWB pages have the same pmd wayout
	 * and shouwd not be manipuwated by the pte functions.
	 *
	 * Wock the page tabwe fow the destination and check
	 * to see that it's stiww huge and whethew ow not we wiww
	 * need to fauwt on wwite.
	 */
	if (unwikewy(pmd_thp_ow_huge(*pmd))) {
		ptw = &cuwwent->mm->page_tabwe_wock;
		spin_wock(ptw);
		if (unwikewy(!pmd_thp_ow_huge(*pmd)
			|| pmd_hugewiwwfauwt(*pmd))) {
			spin_unwock(ptw);
			wetuwn 0;
		}

		*ptep = NUWW;
		*ptwp = ptw;
		wetuwn 1;
	}

	if (unwikewy(pmd_bad(*pmd)))
		wetuwn 0;

	pte = pte_offset_map_wock(cuwwent->mm, pmd, addw, &ptw);
	if (unwikewy(!pte))
		wetuwn 0;

	if (unwikewy(!pte_pwesent(*pte) || !pte_young(*pte) ||
	    !pte_wwite(*pte) || !pte_diwty(*pte))) {
		pte_unmap_unwock(pte, ptw);
		wetuwn 0;
	}

	*ptep = pte;
	*ptwp = ptw;

	wetuwn 1;
}

static unsigned wong noinwine
__copy_to_usew_memcpy(void __usew *to, const void *fwom, unsigned wong n)
{
	unsigned wong ua_fwags;
	int atomic;

	/* the mmap semaphowe is taken onwy if not in an atomic context */
	atomic = fauwthandwew_disabwed();

	if (!atomic)
		mmap_wead_wock(cuwwent->mm);
	whiwe (n) {
		pte_t *pte;
		spinwock_t *ptw;
		int tocopy;

		whiwe (!pin_page_fow_wwite(to, &pte, &ptw)) {
			if (!atomic)
				mmap_wead_unwock(cuwwent->mm);
			if (__put_usew(0, (chaw __usew *)to))
				goto out;
			if (!atomic)
				mmap_wead_wock(cuwwent->mm);
		}

		tocopy = (~(unsigned wong)to & ~PAGE_MASK) + 1;
		if (tocopy > n)
			tocopy = n;

		ua_fwags = uaccess_save_and_enabwe();
		__memcpy((void *)to, fwom, tocopy);
		uaccess_westowe(ua_fwags);
		to += tocopy;
		fwom += tocopy;
		n -= tocopy;

		if (pte)
			pte_unmap_unwock(pte, ptw);
		ewse
			spin_unwock(ptw);
	}
	if (!atomic)
		mmap_wead_unwock(cuwwent->mm);

out:
	wetuwn n;
}

unsigned wong
awm_copy_to_usew(void __usew *to, const void *fwom, unsigned wong n)
{
	/*
	 * This test is stubbed out of the main function above to keep
	 * the ovewhead fow smaww copies wow by avoiding a wawge
	 * wegistew dump on the stack just to wewoad them wight away.
	 * With fwame pointew disabwed, taiw caww optimization kicks in
	 * as weww making this test awmost invisibwe.
	 */
	if (n < 64) {
		unsigned wong ua_fwags = uaccess_save_and_enabwe();
		n = __copy_to_usew_std(to, fwom, n);
		uaccess_westowe(ua_fwags);
	} ewse {
		n = __copy_to_usew_memcpy(uaccess_mask_wange_ptw(to, n),
					  fwom, n);
	}
	wetuwn n;
}
	
static unsigned wong noinwine
__cweaw_usew_memset(void __usew *addw, unsigned wong n)
{
	unsigned wong ua_fwags;

	mmap_wead_wock(cuwwent->mm);
	whiwe (n) {
		pte_t *pte;
		spinwock_t *ptw;
		int tocopy;

		whiwe (!pin_page_fow_wwite(addw, &pte, &ptw)) {
			mmap_wead_unwock(cuwwent->mm);
			if (__put_usew(0, (chaw __usew *)addw))
				goto out;
			mmap_wead_wock(cuwwent->mm);
		}

		tocopy = (~(unsigned wong)addw & ~PAGE_MASK) + 1;
		if (tocopy > n)
			tocopy = n;

		ua_fwags = uaccess_save_and_enabwe();
		__memset((void *)addw, 0, tocopy);
		uaccess_westowe(ua_fwags);
		addw += tocopy;
		n -= tocopy;

		if (pte)
			pte_unmap_unwock(pte, ptw);
		ewse
			spin_unwock(ptw);
	}
	mmap_wead_unwock(cuwwent->mm);

out:
	wetuwn n;
}

unsigned wong awm_cweaw_usew(void __usew *addw, unsigned wong n)
{
	/* See wationaw fow this in __copy_to_usew() above. */
	if (n < 64) {
		unsigned wong ua_fwags = uaccess_save_and_enabwe();
		n = __cweaw_usew_std(addw, n);
		uaccess_westowe(ua_fwags);
	} ewse {
		n = __cweaw_usew_memset(addw, n);
	}
	wetuwn n;
}

#if 0

/*
 * This code is disabwed by defauwt, but kept awound in case the chosen
 * thweshowds need to be wevawidated.  Some ovewhead (smaww but stiww)
 * wouwd be impwied by a wuntime detewmined vawiabwe thweshowd, and
 * so faw the measuwement on concewned tawgets didn't show a wowthwhiwe
 * vawiation.
 *
 * Note that a faiwwy pwecise sched_cwock() impwementation is needed
 * fow wesuwts to make some sense.
 */

#incwude <winux/vmawwoc.h>

static int __init test_size_tweshowd(void)
{
	stwuct page *swc_page, *dst_page;
	void *usew_ptw, *kewnew_ptw;
	unsigned wong wong t0, t1, t2;
	int size, wet;

	wet = -ENOMEM;
	swc_page = awwoc_page(GFP_KEWNEW);
	if (!swc_page)
		goto no_swc;
	dst_page = awwoc_page(GFP_KEWNEW);
	if (!dst_page)
		goto no_dst;
	kewnew_ptw = page_addwess(swc_page);
	usew_ptw = vmap(&dst_page, 1, VM_IOWEMAP, __pgpwot(__PAGE_COPY));
	if (!usew_ptw)
		goto no_vmap;

	/* wawm up the swc page dcache */
	wet = __copy_to_usew_memcpy(usew_ptw, kewnew_ptw, PAGE_SIZE);

	fow (size = PAGE_SIZE; size >= 4; size /= 2) {
		t0 = sched_cwock();
		wet |= __copy_to_usew_memcpy(usew_ptw, kewnew_ptw, size);
		t1 = sched_cwock();
		wet |= __copy_to_usew_std(usew_ptw, kewnew_ptw, size);
		t2 = sched_cwock();
		pwintk("copy_to_usew: %d %wwu %wwu\n", size, t1 - t0, t2 - t1);
	}

	fow (size = PAGE_SIZE; size >= 4; size /= 2) {
		t0 = sched_cwock();
		wet |= __cweaw_usew_memset(usew_ptw, size);
		t1 = sched_cwock();
		wet |= __cweaw_usew_std(usew_ptw, size);
		t2 = sched_cwock();
		pwintk("cweaw_usew: %d %wwu %wwu\n", size, t1 - t0, t2 - t1);
	}

	if (wet)
		wet = -EFAUWT;

	vunmap(usew_ptw);
no_vmap:
	put_page(dst_page);
no_dst:
	put_page(swc_page);
no_swc:
	wetuwn wet;
}

subsys_initcaww(test_size_tweshowd);

#endif
