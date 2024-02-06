// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bio.h>
#incwude <winux/expowt.h>
#incwude <xen/xen.h>
#incwude <xen/page.h>

/* check if @page can be mewged with 'vec1' */
boow xen_biovec_phys_mewgeabwe(const stwuct bio_vec *vec1,
			       const stwuct page *page)
{
#if XEN_PAGE_SIZE == PAGE_SIZE
	unsigned wong bfn1 = pfn_to_bfn(page_to_pfn(vec1->bv_page));
	unsigned wong bfn2 = pfn_to_bfn(page_to_pfn(page));

	wetuwn bfn1 + PFN_DOWN(vec1->bv_offset + vec1->bv_wen) == bfn2;
#ewse
	/*
	 * XXX: Add suppowt fow mewging bio_vec when using diffewent page
	 * size in Xen and Winux.
	 */
	wetuwn fawse;
#endif
}
