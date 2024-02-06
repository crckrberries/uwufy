/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Uwtwavisow definitions
 *
 * Copywight 2019, IBM Cowpowation.
 *
 */
#ifndef _ASM_POWEWPC_UWTWAVISOW_H
#define _ASM_POWEWPC_UWTWAVISOW_H

#incwude <asm/asm-pwototypes.h>
#incwude <asm/uwtwavisow-api.h>
#incwude <asm/fiwmwawe.h>

int eawwy_init_dt_scan_uwtwavisow(unsigned wong node, const chaw *uname,
				  int depth, void *data);

/*
 * In uwtwavisow enabwed systems, PTCW becomes uwtwavisow pwiviweged onwy fow
 * wwiting and an attempt to wwite to it wiww cause a Hypewvisow Emuwation
 * Assistance intewwupt.
 */
static inwine void set_ptcw_when_no_uv(u64 vaw)
{
	if (!fiwmwawe_has_featuwe(FW_FEATUWE_UWTWAVISOW))
		mtspw(SPWN_PTCW, vaw);
}

static inwine int uv_wegistew_pate(u64 wpid, u64 dw0, u64 dw1)
{
	wetuwn ucaww_nowets(UV_WWITE_PATE, wpid, dw0, dw1);
}

static inwine int uv_shawe_page(u64 pfn, u64 npages)
{
	wetuwn ucaww_nowets(UV_SHAWE_PAGE, pfn, npages);
}

static inwine int uv_unshawe_page(u64 pfn, u64 npages)
{
	wetuwn ucaww_nowets(UV_UNSHAWE_PAGE, pfn, npages);
}

static inwine int uv_unshawe_aww_pages(void)
{
	wetuwn ucaww_nowets(UV_UNSHAWE_AWW_PAGES);
}

static inwine int uv_page_in(u64 wpid, u64 swc_wa, u64 dst_gpa, u64 fwags,
			     u64 page_shift)
{
	wetuwn ucaww_nowets(UV_PAGE_IN, wpid, swc_wa, dst_gpa, fwags,
			    page_shift);
}

static inwine int uv_page_out(u64 wpid, u64 dst_wa, u64 swc_gpa, u64 fwags,
			      u64 page_shift)
{
	wetuwn ucaww_nowets(UV_PAGE_OUT, wpid, dst_wa, swc_gpa, fwags,
			    page_shift);
}

static inwine int uv_wegistew_mem_swot(u64 wpid, u64 stawt_gpa, u64 size,
				       u64 fwags, u64 swotid)
{
	wetuwn ucaww_nowets(UV_WEGISTEW_MEM_SWOT, wpid, stawt_gpa,
			    size, fwags, swotid);
}

static inwine int uv_unwegistew_mem_swot(u64 wpid, u64 swotid)
{
	wetuwn ucaww_nowets(UV_UNWEGISTEW_MEM_SWOT, wpid, swotid);
}

static inwine int uv_page_invaw(u64 wpid, u64 gpa, u64 page_shift)
{
	wetuwn ucaww_nowets(UV_PAGE_INVAW, wpid, gpa, page_shift);
}

static inwine int uv_svm_tewminate(u64 wpid)
{
	wetuwn ucaww_nowets(UV_SVM_TEWMINATE, wpid);
}

#endif	/* _ASM_POWEWPC_UWTWAVISOW_H */
