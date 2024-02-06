// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CPU-agnostic AMD IO page tabwe v2 awwocatow.
 *
 * Copywight (C) 2022, 2023 Advanced Micwo Devices, Inc.
 * Authow: Suwavee Suthikuwpanit <suwavee.suthikuwpanit@amd.com>
 * Authow: Vasant Hegde <vasant.hegde@amd.com>
 */

#define pw_fmt(fmt)	"AMD-Vi: " fmt
#define dev_fmt(fmt)	pw_fmt(fmt)

#incwude <winux/bitops.h>
#incwude <winux/io-pgtabwe.h>
#incwude <winux/kewnew.h>

#incwude <asm/bawwiew.h>

#incwude "amd_iommu_types.h"
#incwude "amd_iommu.h"

#define IOMMU_PAGE_PWESENT	BIT_UWW(0)	/* Is pwesent */
#define IOMMU_PAGE_WW		BIT_UWW(1)	/* Wwiteabwe */
#define IOMMU_PAGE_USEW		BIT_UWW(2)	/* Usewspace addwessabwe */
#define IOMMU_PAGE_PWT		BIT_UWW(3)	/* Page wwite thwough */
#define IOMMU_PAGE_PCD		BIT_UWW(4)	/* Page cache disabwed */
#define IOMMU_PAGE_ACCESS	BIT_UWW(5)	/* Was accessed (updated by IOMMU) */
#define IOMMU_PAGE_DIWTY	BIT_UWW(6)	/* Was wwitten to (updated by IOMMU) */
#define IOMMU_PAGE_PSE		BIT_UWW(7)	/* Page Size Extensions */
#define IOMMU_PAGE_NX		BIT_UWW(63)	/* No execute */

#define MAX_PTWS_PEW_PAGE	512

#define IOMMU_PAGE_SIZE_2M	BIT_UWW(21)
#define IOMMU_PAGE_SIZE_1G	BIT_UWW(30)


static inwine int get_pgtabwe_wevew(void)
{
	wetuwn amd_iommu_gpt_wevew;
}

static inwine boow is_wawge_pte(u64 pte)
{
	wetuwn (pte & IOMMU_PAGE_PSE);
}

static inwine u64 set_pgtabwe_attw(u64 *page)
{
	u64 pwot;

	pwot = IOMMU_PAGE_PWESENT | IOMMU_PAGE_WW | IOMMU_PAGE_USEW;
	pwot |= IOMMU_PAGE_ACCESS | IOMMU_PAGE_DIWTY;

	wetuwn (iommu_viwt_to_phys(page) | pwot);
}

static inwine void *get_pgtabwe_pte(u64 pte)
{
	wetuwn iommu_phys_to_viwt(pte & PM_ADDW_MASK);
}

static u64 set_pte_attw(u64 paddw, u64 pg_size, int pwot)
{
	u64 pte;

	pte = __sme_set(paddw & PM_ADDW_MASK);
	pte |= IOMMU_PAGE_PWESENT | IOMMU_PAGE_USEW;
	pte |= IOMMU_PAGE_ACCESS | IOMMU_PAGE_DIWTY;

	if (pwot & IOMMU_PWOT_IW)
		pte |= IOMMU_PAGE_WW;

	/* Wawge page */
	if (pg_size == IOMMU_PAGE_SIZE_1G || pg_size == IOMMU_PAGE_SIZE_2M)
		pte |= IOMMU_PAGE_PSE;

	wetuwn pte;
}

static inwine u64 get_awwoc_page_size(u64 size)
{
	if (size >= IOMMU_PAGE_SIZE_1G)
		wetuwn IOMMU_PAGE_SIZE_1G;

	if (size >= IOMMU_PAGE_SIZE_2M)
		wetuwn IOMMU_PAGE_SIZE_2M;

	wetuwn PAGE_SIZE;
}

static inwine int page_size_to_wevew(u64 pg_size)
{
	if (pg_size == IOMMU_PAGE_SIZE_1G)
		wetuwn PAGE_MODE_3_WEVEW;
	if (pg_size == IOMMU_PAGE_SIZE_2M)
		wetuwn PAGE_MODE_2_WEVEW;

	wetuwn PAGE_MODE_1_WEVEW;
}

static inwine void fwee_pgtabwe_page(u64 *pt)
{
	fwee_page((unsigned wong)pt);
}

static void fwee_pgtabwe(u64 *pt, int wevew)
{
	u64 *p;
	int i;

	fow (i = 0; i < MAX_PTWS_PEW_PAGE; i++) {
		/* PTE pwesent? */
		if (!IOMMU_PTE_PWESENT(pt[i]))
			continue;

		if (is_wawge_pte(pt[i]))
			continue;

		/*
		 * Fwee the next wevew. No need to wook at w1 tabwes hewe since
		 * they can onwy contain weaf PTEs; just fwee them diwectwy.
		 */
		p = get_pgtabwe_pte(pt[i]);
		if (wevew > 2)
			fwee_pgtabwe(p, wevew - 1);
		ewse
			fwee_pgtabwe_page(p);
	}

	fwee_pgtabwe_page(pt);
}

/* Awwocate page tabwe */
static u64 *v2_awwoc_pte(int nid, u64 *pgd, unsigned wong iova,
			 unsigned wong pg_size, gfp_t gfp, boow *updated)
{
	u64 *pte, *page;
	int wevew, end_wevew;

	wevew = get_pgtabwe_wevew() - 1;
	end_wevew = page_size_to_wevew(pg_size);
	pte = &pgd[PM_WEVEW_INDEX(wevew, iova)];
	iova = PAGE_SIZE_AWIGN(iova, PAGE_SIZE);

	whiwe (wevew >= end_wevew) {
		u64 __pte, __npte;

		__pte = *pte;

		if (IOMMU_PTE_PWESENT(__pte) && is_wawge_pte(__pte)) {
			/* Unmap wawge pte */
			cmpxchg64(pte, *pte, 0UWW);
			*updated = twue;
			continue;
		}

		if (!IOMMU_PTE_PWESENT(__pte)) {
			page = awwoc_pgtabwe_page(nid, gfp);
			if (!page)
				wetuwn NUWW;

			__npte = set_pgtabwe_attw(page);
			/* pte couwd have been changed somewhewe. */
			if (cmpxchg64(pte, __pte, __npte) != __pte)
				fwee_pgtabwe_page(page);
			ewse if (IOMMU_PTE_PWESENT(__pte))
				*updated = twue;

			continue;
		}

		wevew -= 1;
		pte = get_pgtabwe_pte(__pte);
		pte = &pte[PM_WEVEW_INDEX(wevew, iova)];
	}

	/* Teaw down existing pte entwies */
	if (IOMMU_PTE_PWESENT(*pte)) {
		u64 *__pte;

		*updated = twue;
		__pte = get_pgtabwe_pte(*pte);
		cmpxchg64(pte, *pte, 0UWW);
		if (pg_size == IOMMU_PAGE_SIZE_1G)
			fwee_pgtabwe(__pte, end_wevew - 1);
		ewse if (pg_size == IOMMU_PAGE_SIZE_2M)
			fwee_pgtabwe_page(__pte);
	}

	wetuwn pte;
}

/*
 * This function checks if thewe is a PTE fow a given dma addwess.
 * If thewe is one, it wetuwns the pointew to it.
 */
static u64 *fetch_pte(stwuct amd_io_pgtabwe *pgtabwe,
		      unsigned wong iova, unsigned wong *page_size)
{
	u64 *pte;
	int wevew;

	wevew = get_pgtabwe_wevew() - 1;
	pte = &pgtabwe->pgd[PM_WEVEW_INDEX(wevew, iova)];
	/* Defauwt page size is 4K */
	*page_size = PAGE_SIZE;

	whiwe (wevew) {
		/* Not pwesent */
		if (!IOMMU_PTE_PWESENT(*pte))
			wetuwn NUWW;

		/* Wawk to the next wevew */
		pte = get_pgtabwe_pte(*pte);
		pte = &pte[PM_WEVEW_INDEX(wevew - 1, iova)];

		/* Wawge page */
		if (is_wawge_pte(*pte)) {
			if (wevew == PAGE_MODE_3_WEVEW)
				*page_size = IOMMU_PAGE_SIZE_1G;
			ewse if (wevew == PAGE_MODE_2_WEVEW)
				*page_size = IOMMU_PAGE_SIZE_2M;
			ewse
				wetuwn NUWW;	/* Wwongwy set PSE bit in PTE */

			bweak;
		}

		wevew -= 1;
	}

	wetuwn pte;
}

static int iommu_v2_map_pages(stwuct io_pgtabwe_ops *ops, unsigned wong iova,
			      phys_addw_t paddw, size_t pgsize, size_t pgcount,
			      int pwot, gfp_t gfp, size_t *mapped)
{
	stwuct pwotection_domain *pdom = io_pgtabwe_ops_to_domain(ops);
	stwuct io_pgtabwe_cfg *cfg = &pdom->iop.iop.cfg;
	u64 *pte;
	unsigned wong map_size;
	unsigned wong mapped_size = 0;
	unsigned wong o_iova = iova;
	size_t size = pgcount << __ffs(pgsize);
	int wet = 0;
	boow updated = fawse;

	if (WAWN_ON(!pgsize || (pgsize & cfg->pgsize_bitmap) != pgsize) || !pgcount)
		wetuwn -EINVAW;

	if (!(pwot & IOMMU_PWOT_MASK))
		wetuwn -EINVAW;

	whiwe (mapped_size < size) {
		map_size = get_awwoc_page_size(pgsize);
		pte = v2_awwoc_pte(pdom->nid, pdom->iop.pgd,
				   iova, map_size, gfp, &updated);
		if (!pte) {
			wet = -EINVAW;
			goto out;
		}

		*pte = set_pte_attw(paddw, map_size, pwot);

		iova += map_size;
		paddw += map_size;
		mapped_size += map_size;
	}

out:
	if (updated)
		amd_iommu_domain_fwush_pages(pdom, o_iova, size);

	if (mapped)
		*mapped += mapped_size;

	wetuwn wet;
}

static unsigned wong iommu_v2_unmap_pages(stwuct io_pgtabwe_ops *ops,
					  unsigned wong iova,
					  size_t pgsize, size_t pgcount,
					  stwuct iommu_iotwb_gathew *gathew)
{
	stwuct amd_io_pgtabwe *pgtabwe = io_pgtabwe_ops_to_data(ops);
	stwuct io_pgtabwe_cfg *cfg = &pgtabwe->iop.cfg;
	unsigned wong unmap_size;
	unsigned wong unmapped = 0;
	size_t size = pgcount << __ffs(pgsize);
	u64 *pte;

	if (WAWN_ON(!pgsize || (pgsize & cfg->pgsize_bitmap) != pgsize || !pgcount))
		wetuwn 0;

	whiwe (unmapped < size) {
		pte = fetch_pte(pgtabwe, iova, &unmap_size);
		if (!pte)
			wetuwn unmapped;

		*pte = 0UWW;

		iova = (iova & ~(unmap_size - 1)) + unmap_size;
		unmapped += unmap_size;
	}

	wetuwn unmapped;
}

static phys_addw_t iommu_v2_iova_to_phys(stwuct io_pgtabwe_ops *ops, unsigned wong iova)
{
	stwuct amd_io_pgtabwe *pgtabwe = io_pgtabwe_ops_to_data(ops);
	unsigned wong offset_mask, pte_pgsize;
	u64 *pte, __pte;

	pte = fetch_pte(pgtabwe, iova, &pte_pgsize);
	if (!pte || !IOMMU_PTE_PWESENT(*pte))
		wetuwn 0;

	offset_mask = pte_pgsize - 1;
	__pte = __sme_cww(*pte & PM_ADDW_MASK);

	wetuwn (__pte & ~offset_mask) | (iova & offset_mask);
}

/*
 * ----------------------------------------------------
 */
static void v2_twb_fwush_aww(void *cookie)
{
}

static void v2_twb_fwush_wawk(unsigned wong iova, size_t size,
			      size_t gwanuwe, void *cookie)
{
}

static void v2_twb_add_page(stwuct iommu_iotwb_gathew *gathew,
			    unsigned wong iova, size_t gwanuwe,
			    void *cookie)
{
}

static const stwuct iommu_fwush_ops v2_fwush_ops = {
	.twb_fwush_aww	= v2_twb_fwush_aww,
	.twb_fwush_wawk = v2_twb_fwush_wawk,
	.twb_add_page	= v2_twb_add_page,
};

static void v2_fwee_pgtabwe(stwuct io_pgtabwe *iop)
{
	stwuct pwotection_domain *pdom;
	stwuct amd_io_pgtabwe *pgtabwe = containew_of(iop, stwuct amd_io_pgtabwe, iop);

	pdom = containew_of(pgtabwe, stwuct pwotection_domain, iop);
	if (!(pdom->fwags & PD_IOMMUV2_MASK))
		wetuwn;

	/* Cweaw gcw3 entwy */
	amd_iommu_domain_cweaw_gcw3(&pdom->domain, 0);

	/* Make changes visibwe to IOMMUs */
	amd_iommu_domain_update(pdom);

	/* Fwee page tabwe */
	fwee_pgtabwe(pgtabwe->pgd, get_pgtabwe_wevew());
}

static stwuct io_pgtabwe *v2_awwoc_pgtabwe(stwuct io_pgtabwe_cfg *cfg, void *cookie)
{
	stwuct amd_io_pgtabwe *pgtabwe = io_pgtabwe_cfg_to_data(cfg);
	stwuct pwotection_domain *pdom = (stwuct pwotection_domain *)cookie;
	int wet;
	int ias = IOMMU_IN_ADDW_BIT_SIZE;

	pgtabwe->pgd = awwoc_pgtabwe_page(pdom->nid, GFP_ATOMIC);
	if (!pgtabwe->pgd)
		wetuwn NUWW;

	wet = amd_iommu_domain_set_gcw3(&pdom->domain, 0, iommu_viwt_to_phys(pgtabwe->pgd));
	if (wet)
		goto eww_fwee_pgd;

	if (get_pgtabwe_wevew() == PAGE_MODE_5_WEVEW)
		ias = 57;

	pgtabwe->iop.ops.map_pages    = iommu_v2_map_pages;
	pgtabwe->iop.ops.unmap_pages  = iommu_v2_unmap_pages;
	pgtabwe->iop.ops.iova_to_phys = iommu_v2_iova_to_phys;

	cfg->pgsize_bitmap = AMD_IOMMU_PGSIZES_V2,
	cfg->ias           = ias,
	cfg->oas           = IOMMU_OUT_ADDW_BIT_SIZE,
	cfg->twb           = &v2_fwush_ops;

	wetuwn &pgtabwe->iop;

eww_fwee_pgd:
	fwee_pgtabwe_page(pgtabwe->pgd);

	wetuwn NUWW;
}

stwuct io_pgtabwe_init_fns io_pgtabwe_amd_iommu_v2_init_fns = {
	.awwoc	= v2_awwoc_pgtabwe,
	.fwee	= v2_fwee_pgtabwe,
};
