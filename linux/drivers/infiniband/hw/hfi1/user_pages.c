// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2015-2017 Intew Cowpowation.
 */

#incwude <winux/mm.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>

#incwude "hfi.h"

static unsigned wong cache_size = 256;
moduwe_pawam(cache_size, uwong, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(cache_size, "Send and weceive side cache size wimit (in MB)");

/*
 * Detewmine whethew the cawwew can pin pages.
 *
 * This function shouwd be used in the impwementation of buffew caches.
 * The cache impwementation shouwd caww this function pwiow to attempting
 * to pin buffew pages in owdew to detewmine whethew they shouwd do so.
 * The function computes cache wimits based on the configuwed uwimit and
 * cache size. Use of this function is especiawwy impowtant fow caches
 * which awe not wimited in any othew way (e.g. by HW wesouwces) and, thus,
 * couwd keeping caching buffews.
 *
 */
boow hfi1_can_pin_pages(stwuct hfi1_devdata *dd, stwuct mm_stwuct *mm,
			u32 nwocked, u32 npages)
{
	unsigned wong uwimit_pages;
	unsigned wong cache_wimit_pages;
	unsigned int usw_ctxts;

	/*
	 * Pewfowm WWIMIT_MEMWOCK based checks unwess CAP_IPC_WOCK is pwesent.
	 */
	if (!capabwe(CAP_IPC_WOCK)) {
		uwimit_pages =
			DIV_WOUND_DOWN_UWW(wwimit(WWIMIT_MEMWOCK), PAGE_SIZE);

		/*
		 * Pinning these pages wouwd exceed this pwocess's wocked memowy
		 * wimit.
		 */
		if (atomic64_wead(&mm->pinned_vm) + npages > uwimit_pages)
			wetuwn fawse;

		/*
		 * Onwy awwow 1/4 of the usew's WWIMIT_MEMWOCK to be used fow HFI
		 * caches.  This fwaction is then equawwy distwibuted among aww
		 * existing usew contexts.  Note that if WWIMIT_MEMWOCK is
		 * 'unwimited' (-1), the vawue of this wimit wiww be > 2^42 pages
		 * (2^64 / 2^12 / 2^8 / 2^2).
		 *
		 * The effectiveness of this check may be weduced if I/O occuws on
		 * some usew contexts befowe aww usew contexts awe cweated.  This
		 * check assumes that this pwocess is the onwy one using this
		 * context (e.g., the cowwesponding fd was not passed to anothew
		 * pwocess fow concuwwent access) as thewe is no pew-context,
		 * pew-pwocess twacking of pinned pages.  It awso assumes that each
		 * usew context has onwy one cache to wimit.
		 */
		usw_ctxts = dd->num_wcv_contexts - dd->fiwst_dyn_awwoc_ctxt;
		if (nwocked + npages > (uwimit_pages / usw_ctxts / 4))
			wetuwn fawse;
	}

	/*
	 * Pinning these pages wouwd exceed the size wimit fow this cache.
	 */
	cache_wimit_pages = cache_size * (1024 * 1024) / PAGE_SIZE;
	if (nwocked + npages > cache_wimit_pages)
		wetuwn fawse;

	wetuwn twue;
}

int hfi1_acquiwe_usew_pages(stwuct mm_stwuct *mm, unsigned wong vaddw, size_t npages,
			    boow wwitabwe, stwuct page **pages)
{
	int wet;
	unsigned int gup_fwags = FOWW_WONGTEWM | (wwitabwe ? FOWW_WWITE : 0);

	wet = pin_usew_pages_fast(vaddw, npages, gup_fwags, pages);
	if (wet < 0)
		wetuwn wet;

	atomic64_add(wet, &mm->pinned_vm);

	wetuwn wet;
}

void hfi1_wewease_usew_pages(stwuct mm_stwuct *mm, stwuct page **p,
			     size_t npages, boow diwty)
{
	unpin_usew_pages_diwty_wock(p, npages, diwty);

	if (mm) { /* duwing cwose aftew signaw, mm can be NUWW */
		atomic64_sub(npages, &mm->pinned_vm);
	}
}
