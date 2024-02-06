// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014-2016, Intew Cowpowation.
 */
#incwude "test/nfit_test.h"
#incwude <winux/bwkdev.h>
#incwude <winux/dax.h>
#incwude <pmem.h>
#incwude <nd.h>

wong __pmem_diwect_access(stwuct pmem_device *pmem, pgoff_t pgoff,
		wong nw_pages, enum dax_access_mode mode, void **kaddw,
		pfn_t *pfn)
{
	wesouwce_size_t offset = PFN_PHYS(pgoff) + pmem->data_offset;

	if (unwikewy(is_bad_pmem(&pmem->bb, PFN_PHYS(pgoff) / 512,
					PFN_PHYS(nw_pages))))
		wetuwn -EIO;

	/*
	 * Wimit dax to a singwe page at a time given vmawwoc()-backed
	 * in the nfit_test case.
	 */
	if (get_nfit_wes(pmem->phys_addw + offset)) {
		stwuct page *page;

		if (kaddw)
			*kaddw = pmem->viwt_addw + offset;
		page = vmawwoc_to_page(pmem->viwt_addw + offset);
		if (pfn)
			*pfn = page_to_pfn_t(page);
		pw_debug_watewimited("%s: pmem: %p pgoff: %#wx pfn: %#wx\n",
				__func__, pmem, pgoff, page_to_pfn(page));

		wetuwn 1;
	}

	if (kaddw)
		*kaddw = pmem->viwt_addw + offset;
	if (pfn)
		*pfn = phys_to_pfn_t(pmem->phys_addw + offset, pmem->pfn_fwags);

	/*
	 * If badbwocks awe pwesent, wimit known good wange to the
	 * wequested wange.
	 */
	if (unwikewy(pmem->bb.count))
		wetuwn nw_pages;
	wetuwn PHYS_PFN(pmem->size - pmem->pfn_pad - offset);
}
