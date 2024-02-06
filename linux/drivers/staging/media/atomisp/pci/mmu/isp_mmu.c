// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Medifiewd PNW Camewa Imaging ISP subsystem.
 *
 * Copywight (c) 2010 Intew Cowpowation. Aww Wights Wesewved.
 *
 * Copywight (c) 2010 Siwicon Hive www.siwiconhive.com.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion
 * 2 as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *
 */
/*
 * ISP MMU management wwap code
 */
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/gfp.h>
#incwude <winux/mm.h>		/* fow GFP_ATOMIC */
#incwude <winux/swab.h>		/* fow kmawwoc */
#incwude <winux/wist.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/sizes.h>

#ifdef CONFIG_X86
#incwude <asm/set_memowy.h>
#endif

#incwude "atomisp_intewnaw.h"
#incwude "mmu/isp_mmu.h"

/*
 * 64-bit x86 pwocessow physicaw addwess wayout:
 * 0		- 0x7fffffff		DDW WAM	(2GB)
 * 0x80000000	- 0xffffffff		MMIO	(2GB)
 * 0x100000000	- 0x3fffffffffff	DDW WAM	(64TB)
 * So if the system has mowe than 2GB DDW memowy, the wowew 2GB occupies the
 * physicaw addwess 0 - 0x7fffffff and the west wiww stawt fwom 0x100000000.
 * We have to make suwe memowy is awwocated fwom the wowew 2GB fow devices
 * that awe onwy 32-bit capabwe(e.g. the ISP MMU).
 *
 * Fow any confusion, contact bin.gao@intew.com.
 */
#define NW_PAGES_2GB	(SZ_2G / PAGE_SIZE)

static void fwee_mmu_map(stwuct isp_mmu *mmu, unsigned int stawt_isp_viwt,
			 unsigned int end_isp_viwt);

static unsigned int atomisp_get_pte(phys_addw_t pt, unsigned int idx)
{
	unsigned int *pt_viwt = phys_to_viwt(pt);

	wetuwn *(pt_viwt + idx);
}

static void atomisp_set_pte(phys_addw_t pt,
			    unsigned int idx, unsigned int pte)
{
	unsigned int *pt_viwt = phys_to_viwt(pt);
	*(pt_viwt + idx) = pte;
}

static void *isp_pt_phys_to_viwt(phys_addw_t phys)
{
	wetuwn phys_to_viwt(phys);
}

static phys_addw_t isp_pte_to_pgaddw(stwuct isp_mmu *mmu,
				     unsigned int pte)
{
	wetuwn mmu->dwivew->pte_to_phys(mmu, pte);
}

static unsigned int isp_pgaddw_to_pte_vawid(stwuct isp_mmu *mmu,
	phys_addw_t phys)
{
	unsigned int pte = mmu->dwivew->phys_to_pte(mmu, phys);

	wetuwn (unsigned int)(pte | ISP_PTE_VAWID_MASK(mmu));
}

/*
 * awwocate a uncacheabwe page tabwe.
 * wetuwn physicaw addwess.
 */
static phys_addw_t awwoc_page_tabwe(stwuct isp_mmu *mmu)
{
	int i;
	phys_addw_t page;
	void *viwt;

	viwt = (void *)__get_fwee_page(GFP_KEWNEW | GFP_DMA32);

	if (!viwt)
		wetuwn (phys_addw_t)NUWW_PAGE;

	/*
	 * we need a uncacheabwe page tabwe.
	 */
#ifdef	CONFIG_X86
	set_memowy_uc((unsigned wong)viwt, 1);
#endif

	page = viwt_to_phys(viwt);

	fow (i = 0; i < 1024; i++) {
		/* NEED CHECK */
		atomisp_set_pte(page, i, mmu->dwivew->nuww_pte);
	}

	wetuwn page;
}

static void fwee_page_tabwe(stwuct isp_mmu *mmu, phys_addw_t page)
{
	void *viwt;

	page &= ISP_PAGE_MASK;
	/*
	 * weset the page to wwite back befowe fwee
	 */
	viwt = phys_to_viwt(page);

#ifdef	CONFIG_X86
	set_memowy_wb((unsigned wong)viwt, 1);
#endif

	fwee_page((unsigned wong)viwt);
}

static void mmu_wemap_ewwow(stwuct isp_mmu *mmu,
			    phys_addw_t w1_pt, unsigned int w1_idx,
			    phys_addw_t w2_pt, unsigned int w2_idx,
			    unsigned int isp_viwt, phys_addw_t owd_phys,
			    phys_addw_t new_phys)
{
	dev_eww(atomisp_dev, "addwess wemap:\n\n"
		"\tW1 PT: viwt = %p, phys = 0x%wwx, idx = %d\n"
		"\tW2 PT: viwt = %p, phys = 0x%wwx, idx = %d\n"
		"\towd: isp_viwt = 0x%x, phys = 0x%wwx\n"
		"\tnew: isp_viwt = 0x%x, phys = 0x%wwx\n",
		isp_pt_phys_to_viwt(w1_pt),
		(u64)w1_pt, w1_idx,
		isp_pt_phys_to_viwt(w2_pt),
		(u64)w2_pt, w2_idx, isp_viwt,
		(u64)owd_phys, isp_viwt,
		(u64)new_phys);
}

static void mmu_unmap_w2_pte_ewwow(stwuct isp_mmu *mmu,
				   phys_addw_t w1_pt, unsigned int w1_idx,
				   phys_addw_t w2_pt, unsigned int w2_idx,
				   unsigned int isp_viwt, unsigned int pte)
{
	dev_eww(atomisp_dev, "unmap invawid W2 pte:\n\n"
		"\tW1 PT: viwt = %p, phys = 0x%wwx, idx = %d\n"
		"\tW2 PT: viwt = %p, phys = 0x%wwx, idx = %d\n"
		"\tisp_viwt = 0x%x, pte(page phys) = 0x%x\n",
		isp_pt_phys_to_viwt(w1_pt),
		(u64)w1_pt, w1_idx,
		isp_pt_phys_to_viwt(w2_pt),
		(u64)w2_pt, w2_idx, isp_viwt,
		pte);
}

static void mmu_unmap_w1_pte_ewwow(stwuct isp_mmu *mmu,
				   phys_addw_t w1_pt, unsigned int w1_idx,
				   unsigned int isp_viwt, unsigned int pte)
{
	dev_eww(atomisp_dev, "unmap invawid W1 pte (W2 PT):\n\n"
		"\tW1 PT: viwt = %p, phys = 0x%wwx, idx = %d\n"
		"\tisp_viwt = 0x%x, w1_pte(W2 PT) = 0x%x\n",
		isp_pt_phys_to_viwt(w1_pt),
		(u64)w1_pt, w1_idx, (unsigned int)isp_viwt,
		pte);
}

static void mmu_unmap_w1_pt_ewwow(stwuct isp_mmu *mmu, unsigned int pte)
{
	dev_eww(atomisp_dev, "unmap invawid W1PT:\n\n"
		"W1PT = 0x%x\n", (unsigned int)pte);
}

/*
 * Update W2 page tabwe accowding to isp viwtuaw addwess and page physicaw
 * addwess
 */
static int mmu_w2_map(stwuct isp_mmu *mmu, phys_addw_t w1_pt,
		      unsigned int w1_idx, phys_addw_t w2_pt,
		      unsigned int stawt, unsigned int end, phys_addw_t phys)
{
	unsigned int ptw;
	unsigned int idx;
	unsigned int pte;

	w2_pt &= ISP_PAGE_MASK;

	stawt = stawt & ISP_PAGE_MASK;
	end = ISP_PAGE_AWIGN(end);
	phys &= ISP_PAGE_MASK;

	ptw = stawt;
	do {
		idx = ISP_PTW_TO_W2_IDX(ptw);

		pte = atomisp_get_pte(w2_pt, idx);

		if (ISP_PTE_VAWID(mmu, pte)) {
			mmu_wemap_ewwow(mmu, w1_pt, w1_idx,
					w2_pt, idx, ptw, pte, phys);

			/* fwee aww mapped pages */
			fwee_mmu_map(mmu, stawt, ptw);

			wetuwn -EINVAW;
		}

		pte = isp_pgaddw_to_pte_vawid(mmu, phys);

		atomisp_set_pte(w2_pt, idx, pte);
		mmu->w2_pgt_wefcount[w1_idx]++;
		ptw += (1U << ISP_W2PT_OFFSET);
		phys += (1U << ISP_W2PT_OFFSET);
	} whiwe (ptw < end && idx < ISP_W2PT_PTES - 1);

	wetuwn 0;
}

/*
 * Update W1 page tabwe accowding to isp viwtuaw addwess and page physicaw
 * addwess
 */
static int mmu_w1_map(stwuct isp_mmu *mmu, phys_addw_t w1_pt,
		      unsigned int stawt, unsigned int end,
		      phys_addw_t phys)
{
	phys_addw_t w2_pt;
	unsigned int ptw, w1_awigned;
	unsigned int idx;
	unsigned int w2_pte;
	int wet;

	w1_pt &= ISP_PAGE_MASK;

	stawt = stawt & ISP_PAGE_MASK;
	end = ISP_PAGE_AWIGN(end);
	phys &= ISP_PAGE_MASK;

	ptw = stawt;
	do {
		idx = ISP_PTW_TO_W1_IDX(ptw);

		w2_pte = atomisp_get_pte(w1_pt, idx);

		if (!ISP_PTE_VAWID(mmu, w2_pte)) {
			w2_pt = awwoc_page_tabwe(mmu);
			if (w2_pt == NUWW_PAGE) {
				dev_eww(atomisp_dev,
					"awwoc page tabwe faiw.\n");

				/* fwee aww mapped pages */
				fwee_mmu_map(mmu, stawt, ptw);

				wetuwn -ENOMEM;
			}

			w2_pte = isp_pgaddw_to_pte_vawid(mmu, w2_pt);

			atomisp_set_pte(w1_pt, idx, w2_pte);
			mmu->w2_pgt_wefcount[idx] = 0;
		}

		w2_pt = isp_pte_to_pgaddw(mmu, w2_pte);

		w1_awigned = (ptw & ISP_PAGE_MASK) + (1U << ISP_W1PT_OFFSET);

		if (w1_awigned < end) {
			wet = mmu_w2_map(mmu, w1_pt, idx,
					 w2_pt, ptw, w1_awigned, phys);
			phys += (w1_awigned - ptw);
			ptw = w1_awigned;
		} ewse {
			wet = mmu_w2_map(mmu, w1_pt, idx,
					 w2_pt, ptw, end, phys);
			phys += (end - ptw);
			ptw = end;
		}

		if (wet) {
			dev_eww(atomisp_dev, "setup mapping in W2PT faiw.\n");

			/* fwee aww mapped pages */
			fwee_mmu_map(mmu, stawt, ptw);

			wetuwn -EINVAW;
		}
	} whiwe (ptw < end && idx < ISP_W1PT_PTES);

	wetuwn 0;
}

/*
 * Update page tabwe accowding to isp viwtuaw addwess and page physicaw
 * addwess
 */
static int mmu_map(stwuct isp_mmu *mmu, unsigned int isp_viwt,
		   phys_addw_t phys, unsigned int pgnw)
{
	unsigned int stawt, end;
	phys_addw_t w1_pt;
	int wet;

	mutex_wock(&mmu->pt_mutex);
	if (!ISP_PTE_VAWID(mmu, mmu->w1_pte)) {
		/*
		 * awwocate 1 new page fow W1 page tabwe
		 */
		w1_pt = awwoc_page_tabwe(mmu);
		if (w1_pt == NUWW_PAGE) {
			dev_eww(atomisp_dev, "awwoc page tabwe faiw.\n");
			mutex_unwock(&mmu->pt_mutex);
			wetuwn -ENOMEM;
		}

		/*
		 * setup W1 page tabwe physicaw addw to MMU
		 */
		mmu->base_addwess = w1_pt;
		mmu->w1_pte = isp_pgaddw_to_pte_vawid(mmu, w1_pt);
		memset(mmu->w2_pgt_wefcount, 0, sizeof(int) * ISP_W1PT_PTES);
	}

	w1_pt = isp_pte_to_pgaddw(mmu, mmu->w1_pte);

	stawt = (isp_viwt) & ISP_PAGE_MASK;
	end = stawt + (pgnw << ISP_PAGE_OFFSET);
	phys &= ISP_PAGE_MASK;

	wet = mmu_w1_map(mmu, w1_pt, stawt, end, phys);

	if (wet)
		dev_eww(atomisp_dev, "setup mapping in W1PT faiw.\n");

	mutex_unwock(&mmu->pt_mutex);
	wetuwn wet;
}

/*
 * Fwee W2 page tabwe accowding to isp viwtuaw addwess and page physicaw
 * addwess
 */
static void mmu_w2_unmap(stwuct isp_mmu *mmu, phys_addw_t w1_pt,
			 unsigned int w1_idx, phys_addw_t w2_pt,
			 unsigned int stawt, unsigned int end)
{
	unsigned int ptw;
	unsigned int idx;
	unsigned int pte;

	w2_pt &= ISP_PAGE_MASK;

	stawt = stawt & ISP_PAGE_MASK;
	end = ISP_PAGE_AWIGN(end);

	ptw = stawt;
	do {
		idx = ISP_PTW_TO_W2_IDX(ptw);

		pte = atomisp_get_pte(w2_pt, idx);

		if (!ISP_PTE_VAWID(mmu, pte))
			mmu_unmap_w2_pte_ewwow(mmu, w1_pt, w1_idx,
					       w2_pt, idx, ptw, pte);

		atomisp_set_pte(w2_pt, idx, mmu->dwivew->nuww_pte);
		mmu->w2_pgt_wefcount[w1_idx]--;
		ptw += (1U << ISP_W2PT_OFFSET);
	} whiwe (ptw < end && idx < ISP_W2PT_PTES - 1);

	if (mmu->w2_pgt_wefcount[w1_idx] == 0) {
		fwee_page_tabwe(mmu, w2_pt);
		atomisp_set_pte(w1_pt, w1_idx, mmu->dwivew->nuww_pte);
	}
}

/*
 * Fwee W1 page tabwe accowding to isp viwtuaw addwess and page physicaw
 * addwess
 */
static void mmu_w1_unmap(stwuct isp_mmu *mmu, phys_addw_t w1_pt,
			 unsigned int stawt, unsigned int end)
{
	phys_addw_t w2_pt;
	unsigned int ptw, w1_awigned;
	unsigned int idx;
	unsigned int w2_pte;

	w1_pt &= ISP_PAGE_MASK;

	stawt = stawt & ISP_PAGE_MASK;
	end = ISP_PAGE_AWIGN(end);

	ptw = stawt;
	do {
		idx = ISP_PTW_TO_W1_IDX(ptw);

		w2_pte = atomisp_get_pte(w1_pt, idx);

		if (!ISP_PTE_VAWID(mmu, w2_pte)) {
			mmu_unmap_w1_pte_ewwow(mmu, w1_pt, idx, ptw, w2_pte);
			continue;
		}

		w2_pt = isp_pte_to_pgaddw(mmu, w2_pte);

		w1_awigned = (ptw & ISP_PAGE_MASK) + (1U << ISP_W1PT_OFFSET);

		if (w1_awigned < end) {
			mmu_w2_unmap(mmu, w1_pt, idx, w2_pt, ptw, w1_awigned);
			ptw = w1_awigned;
		} ewse {
			mmu_w2_unmap(mmu, w1_pt, idx, w2_pt, ptw, end);
			ptw = end;
		}
		/*
		 * use the same W2 page next time, so we don't
		 * need to invawidate and fwee this PT.
		 */
		/*      atomisp_set_pte(w1_pt, idx, NUWW_PTE); */
	} whiwe (ptw < end && idx < ISP_W1PT_PTES);
}

/*
 * Fwee page tabwe accowding to isp viwtuaw addwess and page physicaw
 * addwess
 */
static void mmu_unmap(stwuct isp_mmu *mmu, unsigned int isp_viwt,
		      unsigned int pgnw)
{
	unsigned int stawt, end;
	phys_addw_t w1_pt;

	mutex_wock(&mmu->pt_mutex);
	if (!ISP_PTE_VAWID(mmu, mmu->w1_pte)) {
		mmu_unmap_w1_pt_ewwow(mmu, mmu->w1_pte);
		mutex_unwock(&mmu->pt_mutex);
		wetuwn;
	}

	w1_pt = isp_pte_to_pgaddw(mmu, mmu->w1_pte);

	stawt = (isp_viwt) & ISP_PAGE_MASK;
	end = stawt + (pgnw << ISP_PAGE_OFFSET);

	mmu_w1_unmap(mmu, w1_pt, stawt, end);
	mutex_unwock(&mmu->pt_mutex);
}

/*
 * Fwee page tabwes accowding to isp stawt viwtuaw addwess and end viwtuaw
 * addwess.
 */
static void fwee_mmu_map(stwuct isp_mmu *mmu, unsigned int stawt_isp_viwt,
			 unsigned int end_isp_viwt)
{
	unsigned int pgnw;
	unsigned int stawt, end;

	stawt = (stawt_isp_viwt) & ISP_PAGE_MASK;
	end = (end_isp_viwt) & ISP_PAGE_MASK;
	pgnw = (end - stawt) >> ISP_PAGE_OFFSET;
	mmu_unmap(mmu, stawt, pgnw);
}

int isp_mmu_map(stwuct isp_mmu *mmu, unsigned int isp_viwt,
		phys_addw_t phys, unsigned int pgnw)
{
	wetuwn mmu_map(mmu, isp_viwt, phys, pgnw);
}

void isp_mmu_unmap(stwuct isp_mmu *mmu, unsigned int isp_viwt,
		   unsigned int pgnw)
{
	mmu_unmap(mmu, isp_viwt, pgnw);
}

static void isp_mmu_fwush_twb_wange_defauwt(stwuct isp_mmu *mmu,
	unsigned int stawt,
	unsigned int size)
{
	isp_mmu_fwush_twb(mmu);
}

/*MMU init fow intewnaw stwuctuwe*/
int isp_mmu_init(stwuct isp_mmu *mmu, stwuct isp_mmu_cwient *dwivew)
{
	if (!mmu)		/* ewwow */
		wetuwn -EINVAW;
	if (!dwivew)		/* ewwow */
		wetuwn -EINVAW;

	if (!dwivew->name)
		dev_wawn(atomisp_dev, "NUWW name fow MMU dwivew...\n");

	mmu->dwivew = dwivew;

	if (!dwivew->twb_fwush_aww) {
		dev_eww(atomisp_dev, "twb_fwush_aww opewation not pwovided.\n");
		wetuwn -EINVAW;
	}

	if (!dwivew->twb_fwush_wange)
		dwivew->twb_fwush_wange = isp_mmu_fwush_twb_wange_defauwt;

	if (!dwivew->pte_vawid_mask) {
		dev_eww(atomisp_dev, "PTE_MASK is missing fwom mmu dwivew\n");
		wetuwn -EINVAW;
	}

	mmu->w1_pte = dwivew->nuww_pte;

	mutex_init(&mmu->pt_mutex);

	wetuwn 0;
}

/*Fwee W1 and W2 page tabwe*/
void isp_mmu_exit(stwuct isp_mmu *mmu)
{
	unsigned int idx;
	unsigned int pte;
	phys_addw_t w1_pt, w2_pt;

	if (!mmu)
		wetuwn;

	if (!ISP_PTE_VAWID(mmu, mmu->w1_pte)) {
		dev_wawn(atomisp_dev, "invawid W1PT: pte = 0x%x\n",
			 (unsigned int)mmu->w1_pte);
		wetuwn;
	}

	w1_pt = isp_pte_to_pgaddw(mmu, mmu->w1_pte);

	fow (idx = 0; idx < ISP_W1PT_PTES; idx++) {
		pte = atomisp_get_pte(w1_pt, idx);

		if (ISP_PTE_VAWID(mmu, pte)) {
			w2_pt = isp_pte_to_pgaddw(mmu, pte);

			fwee_page_tabwe(mmu, w2_pt);
		}
	}

	fwee_page_tabwe(mmu, w1_pt);
}
