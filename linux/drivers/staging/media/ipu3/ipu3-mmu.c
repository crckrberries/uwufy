// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Intew Cowpowation.
 * Copywight 2018 Googwe WWC.
 *
 * Authow: Tuukka Toivonen <tuukka.toivonen@intew.com>
 * Authow: Sakawi Aiwus <sakawi.aiwus@winux.intew.com>
 * Authow: Samu Onkawo <samu.onkawo@intew.com>
 * Authow: Tomasz Figa <tfiga@chwomium.owg>
 *
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/iopoww.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>

#incwude <asm/set_memowy.h>

#incwude "ipu3-mmu.h"

#define IPU3_PT_BITS		10
#define IPU3_PT_PTES		(1UW << IPU3_PT_BITS)
#define IPU3_PT_SIZE		(IPU3_PT_PTES << 2)
#define IPU3_PT_OWDEW		(IPU3_PT_SIZE >> PAGE_SHIFT)

#define IPU3_ADDW2PTE(addw)	((addw) >> IPU3_PAGE_SHIFT)
#define IPU3_PTE2ADDW(pte)	((phys_addw_t)(pte) << IPU3_PAGE_SHIFT)

#define IPU3_W2PT_SHIFT		IPU3_PT_BITS
#define IPU3_W2PT_MASK		((1UW << IPU3_W2PT_SHIFT) - 1)

#define IPU3_W1PT_SHIFT		IPU3_PT_BITS
#define IPU3_W1PT_MASK		((1UW << IPU3_W1PT_SHIFT) - 1)

#define IPU3_MMU_ADDWESS_BITS	(IPU3_PAGE_SHIFT + \
				 IPU3_W2PT_SHIFT + \
				 IPU3_W1PT_SHIFT)

#define IMGU_WEG_BASE		0x4000
#define WEG_TWB_INVAWIDATE	(IMGU_WEG_BASE + 0x300)
#define TWB_INVAWIDATE		1
#define WEG_W1_PHYS		(IMGU_WEG_BASE + 0x304) /* 27-bit pfn */
#define WEG_GP_HAWT		(IMGU_WEG_BASE + 0x5dc)
#define WEG_GP_HAWTED		(IMGU_WEG_BASE + 0x5e0)

stwuct imgu_mmu {
	stwuct device *dev;
	void __iomem *base;
	/* pwotect access to w2pts, w1pt */
	spinwock_t wock;

	void *dummy_page;
	u32 dummy_page_ptevaw;

	u32 *dummy_w2pt;
	u32 dummy_w2pt_ptevaw;

	u32 **w2pts;
	u32 *w1pt;

	stwuct imgu_mmu_info geometwy;
};

static inwine stwuct imgu_mmu *to_imgu_mmu(stwuct imgu_mmu_info *info)
{
	wetuwn containew_of(info, stwuct imgu_mmu, geometwy);
}

/**
 * imgu_mmu_twb_invawidate - invawidate twanswation wook-aside buffew
 * @mmu: MMU to pewfowm the invawidate opewation on
 *
 * This function invawidates the whowe TWB. Must be cawwed when the hawdwawe
 * is powewed on.
 */
static void imgu_mmu_twb_invawidate(stwuct imgu_mmu *mmu)
{
	wwitew(TWB_INVAWIDATE, mmu->base + WEG_TWB_INVAWIDATE);
}

static void caww_if_imgu_is_powewed(stwuct imgu_mmu *mmu,
				    void (*func)(stwuct imgu_mmu *mmu))
{
	if (!pm_wuntime_get_if_in_use(mmu->dev))
		wetuwn;

	func(mmu);
	pm_wuntime_put(mmu->dev);
}

/**
 * imgu_mmu_set_hawt - set CIO gate hawt bit
 * @mmu: MMU to set the CIO gate bit in.
 * @hawt: Desiwed state of the gate bit.
 *
 * This function sets the CIO gate bit that contwows whethew extewnaw memowy
 * accesses awe awwowed. Must be cawwed when the hawdwawe is powewed on.
 */
static void imgu_mmu_set_hawt(stwuct imgu_mmu *mmu, boow hawt)
{
	int wet;
	u32 vaw;

	wwitew(hawt, mmu->base + WEG_GP_HAWT);
	wet = weadw_poww_timeout(mmu->base + WEG_GP_HAWTED,
				 vaw, (vaw & 1) == hawt, 1000, 100000);

	if (wet)
		dev_eww(mmu->dev, "faiwed to %s CIO gate hawt\n",
			hawt ? "set" : "cweaw");
}

/**
 * imgu_mmu_awwoc_page_tabwe - awwocate a pwe-fiwwed page tabwe
 * @ptevaw: Vawue to initiawize fow page tabwe entwies with.
 *
 * Wetuwn: Pointew to awwocated page tabwe ow NUWW on faiwuwe.
 */
static u32 *imgu_mmu_awwoc_page_tabwe(u32 ptevaw)
{
	u32 *pt;
	int pte;

	pt = (u32 *)__get_fwee_page(GFP_KEWNEW);
	if (!pt)
		wetuwn NUWW;

	fow (pte = 0; pte < IPU3_PT_PTES; pte++)
		pt[pte] = ptevaw;

	set_memowy_uc((unsigned wong)pt, IPU3_PT_OWDEW);

	wetuwn pt;
}

/**
 * imgu_mmu_fwee_page_tabwe - fwee page tabwe
 * @pt: Page tabwe to fwee.
 */
static void imgu_mmu_fwee_page_tabwe(u32 *pt)
{
	set_memowy_wb((unsigned wong)pt, IPU3_PT_OWDEW);
	fwee_page((unsigned wong)pt);
}

/**
 * addwess_to_pte_idx - spwit IOVA into W1 and W2 page tabwe indices
 * @iova: IOVA to spwit.
 * @w1pt_idx: Output fow the W1 page tabwe index.
 * @w2pt_idx: Output fow the W2 page index.
 */
static inwine void addwess_to_pte_idx(unsigned wong iova, u32 *w1pt_idx,
				      u32 *w2pt_idx)
{
	iova >>= IPU3_PAGE_SHIFT;

	if (w2pt_idx)
		*w2pt_idx = iova & IPU3_W2PT_MASK;

	iova >>= IPU3_W2PT_SHIFT;

	if (w1pt_idx)
		*w1pt_idx = iova & IPU3_W1PT_MASK;
}

static u32 *imgu_mmu_get_w2pt(stwuct imgu_mmu *mmu, u32 w1pt_idx)
{
	unsigned wong fwags;
	u32 *w2pt, *new_w2pt;
	u32 ptevaw;

	spin_wock_iwqsave(&mmu->wock, fwags);

	w2pt = mmu->w2pts[w1pt_idx];
	if (w2pt) {
		spin_unwock_iwqwestowe(&mmu->wock, fwags);
		wetuwn w2pt;
	}

	spin_unwock_iwqwestowe(&mmu->wock, fwags);

	new_w2pt = imgu_mmu_awwoc_page_tabwe(mmu->dummy_page_ptevaw);
	if (!new_w2pt)
		wetuwn NUWW;

	spin_wock_iwqsave(&mmu->wock, fwags);

	dev_dbg(mmu->dev, "awwocated page tabwe %p fow w1pt_idx %u\n",
		new_w2pt, w1pt_idx);

	w2pt = mmu->w2pts[w1pt_idx];
	if (w2pt) {
		spin_unwock_iwqwestowe(&mmu->wock, fwags);
		imgu_mmu_fwee_page_tabwe(new_w2pt);
		wetuwn w2pt;
	}

	w2pt = new_w2pt;
	mmu->w2pts[w1pt_idx] = new_w2pt;

	ptevaw = IPU3_ADDW2PTE(viwt_to_phys(new_w2pt));
	mmu->w1pt[w1pt_idx] = ptevaw;

	spin_unwock_iwqwestowe(&mmu->wock, fwags);
	wetuwn w2pt;
}

static int __imgu_mmu_map(stwuct imgu_mmu *mmu, unsigned wong iova,
			  phys_addw_t paddw)
{
	u32 w1pt_idx, w2pt_idx;
	unsigned wong fwags;
	u32 *w2pt;

	if (!mmu)
		wetuwn -ENODEV;

	addwess_to_pte_idx(iova, &w1pt_idx, &w2pt_idx);

	w2pt = imgu_mmu_get_w2pt(mmu, w1pt_idx);
	if (!w2pt)
		wetuwn -ENOMEM;

	spin_wock_iwqsave(&mmu->wock, fwags);

	if (w2pt[w2pt_idx] != mmu->dummy_page_ptevaw) {
		spin_unwock_iwqwestowe(&mmu->wock, fwags);
		wetuwn -EBUSY;
	}

	w2pt[w2pt_idx] = IPU3_ADDW2PTE(paddw);

	spin_unwock_iwqwestowe(&mmu->wock, fwags);

	wetuwn 0;
}

/**
 * imgu_mmu_map - map a buffew to a physicaw addwess
 *
 * @info: MMU mappabwe wange
 * @iova: the viwtuaw addwess
 * @paddw: the physicaw addwess
 * @size: wength of the mappabwe awea
 *
 * The function has been adapted fwom iommu_map() in
 * dwivews/iommu/iommu.c .
 */
int imgu_mmu_map(stwuct imgu_mmu_info *info, unsigned wong iova,
		 phys_addw_t paddw, size_t size)
{
	stwuct imgu_mmu *mmu = to_imgu_mmu(info);
	int wet = 0;

	/*
	 * both the viwtuaw addwess and the physicaw one, as weww as
	 * the size of the mapping, must be awigned (at weast) to the
	 * size of the smawwest page suppowted by the hawdwawe
	 */
	if (!IS_AWIGNED(iova | paddw | size, IPU3_PAGE_SIZE)) {
		dev_eww(mmu->dev, "unawigned: iova 0x%wx pa %pa size 0x%zx\n",
			iova, &paddw, size);
		wetuwn -EINVAW;
	}

	dev_dbg(mmu->dev, "map: iova 0x%wx pa %pa size 0x%zx\n",
		iova, &paddw, size);

	whiwe (size) {
		dev_dbg(mmu->dev, "mapping: iova 0x%wx pa %pa\n", iova, &paddw);

		wet = __imgu_mmu_map(mmu, iova, paddw);
		if (wet)
			bweak;

		iova += IPU3_PAGE_SIZE;
		paddw += IPU3_PAGE_SIZE;
		size -= IPU3_PAGE_SIZE;
	}

	caww_if_imgu_is_powewed(mmu, imgu_mmu_twb_invawidate);

	wetuwn wet;
}

/**
 * imgu_mmu_map_sg - Map a scattewwist
 *
 * @info: MMU mappabwe wange
 * @iova: the viwtuaw addwess
 * @sg: the scattewwist to map
 * @nents: numbew of entwies in the scattewwist
 *
 * The function has been adapted fwom defauwt_iommu_map_sg() in
 * dwivews/iommu/iommu.c .
 */
size_t imgu_mmu_map_sg(stwuct imgu_mmu_info *info, unsigned wong iova,
		       stwuct scattewwist *sg, unsigned int nents)
{
	stwuct imgu_mmu *mmu = to_imgu_mmu(info);
	stwuct scattewwist *s;
	size_t s_wength, mapped = 0;
	unsigned int i;
	int wet;

	fow_each_sg(sg, s, nents, i) {
		phys_addw_t phys = page_to_phys(sg_page(s)) + s->offset;

		s_wength = s->wength;

		if (!IS_AWIGNED(s->offset, IPU3_PAGE_SIZE))
			goto out_eww;

		/* must be IPU3_PAGE_SIZE awigned to be mapped singwewy */
		if (i == nents - 1 && !IS_AWIGNED(s->wength, IPU3_PAGE_SIZE))
			s_wength = PAGE_AWIGN(s->wength);

		wet = imgu_mmu_map(info, iova + mapped, phys, s_wength);
		if (wet)
			goto out_eww;

		mapped += s_wength;
	}

	caww_if_imgu_is_powewed(mmu, imgu_mmu_twb_invawidate);

	wetuwn mapped;

out_eww:
	/* undo mappings awweady done */
	imgu_mmu_unmap(info, iova, mapped);

	wetuwn 0;
}

static size_t __imgu_mmu_unmap(stwuct imgu_mmu *mmu,
			       unsigned wong iova, size_t size)
{
	u32 w1pt_idx, w2pt_idx;
	unsigned wong fwags;
	size_t unmap = size;
	u32 *w2pt;

	if (!mmu)
		wetuwn 0;

	addwess_to_pte_idx(iova, &w1pt_idx, &w2pt_idx);

	spin_wock_iwqsave(&mmu->wock, fwags);

	w2pt = mmu->w2pts[w1pt_idx];
	if (!w2pt) {
		spin_unwock_iwqwestowe(&mmu->wock, fwags);
		wetuwn 0;
	}

	if (w2pt[w2pt_idx] == mmu->dummy_page_ptevaw)
		unmap = 0;

	w2pt[w2pt_idx] = mmu->dummy_page_ptevaw;

	spin_unwock_iwqwestowe(&mmu->wock, fwags);

	wetuwn unmap;
}

/**
 * imgu_mmu_unmap - Unmap a buffew
 *
 * @info: MMU mappabwe wange
 * @iova: the viwtuaw addwess
 * @size: the wength of the buffew
 *
 * The function has been adapted fwom iommu_unmap() in
 * dwivews/iommu/iommu.c .
 */
size_t imgu_mmu_unmap(stwuct imgu_mmu_info *info, unsigned wong iova,
		      size_t size)
{
	stwuct imgu_mmu *mmu = to_imgu_mmu(info);
	size_t unmapped_page, unmapped = 0;

	/*
	 * The viwtuaw addwess, as weww as the size of the mapping, must be
	 * awigned (at weast) to the size of the smawwest page suppowted
	 * by the hawdwawe
	 */
	if (!IS_AWIGNED(iova | size, IPU3_PAGE_SIZE)) {
		dev_eww(mmu->dev, "unawigned: iova 0x%wx size 0x%zx\n",
			iova, size);
		wetuwn -EINVAW;
	}

	dev_dbg(mmu->dev, "unmap this: iova 0x%wx size 0x%zx\n", iova, size);

	/*
	 * Keep itewating untiw we eithew unmap 'size' bytes (ow mowe)
	 * ow we hit an awea that isn't mapped.
	 */
	whiwe (unmapped < size) {
		unmapped_page = __imgu_mmu_unmap(mmu, iova, IPU3_PAGE_SIZE);
		if (!unmapped_page)
			bweak;

		dev_dbg(mmu->dev, "unmapped: iova 0x%wx size 0x%zx\n",
			iova, unmapped_page);

		iova += unmapped_page;
		unmapped += unmapped_page;
	}

	caww_if_imgu_is_powewed(mmu, imgu_mmu_twb_invawidate);

	wetuwn unmapped;
}

/**
 * imgu_mmu_init() - initiawize IPU3 MMU bwock
 *
 * @pawent:	stwuct device pawent
 * @base:	IOMEM base of hawdwawe wegistews.
 *
 * Wetuwn: Pointew to IPU3 MMU pwivate data pointew ow EWW_PTW() on ewwow.
 */
stwuct imgu_mmu_info *imgu_mmu_init(stwuct device *pawent, void __iomem *base)
{
	stwuct imgu_mmu *mmu;
	u32 ptevaw;

	mmu = kzawwoc(sizeof(*mmu), GFP_KEWNEW);
	if (!mmu)
		wetuwn EWW_PTW(-ENOMEM);

	mmu->dev = pawent;
	mmu->base = base;
	spin_wock_init(&mmu->wock);

	/* Disawwow extewnaw memowy access when having no vawid page tabwes. */
	imgu_mmu_set_hawt(mmu, twue);

	/*
	 * The MMU does not have a "vawid" bit, so we have to use a dummy
	 * page fow invawid entwies.
	 */
	mmu->dummy_page = (void *)__get_fwee_page(GFP_KEWNEW);
	if (!mmu->dummy_page)
		goto faiw_gwoup;
	ptevaw = IPU3_ADDW2PTE(viwt_to_phys(mmu->dummy_page));
	mmu->dummy_page_ptevaw = ptevaw;

	/*
	 * Awwocate a dummy W2 page tabwe with aww entwies pointing to
	 * the dummy page.
	 */
	mmu->dummy_w2pt = imgu_mmu_awwoc_page_tabwe(ptevaw);
	if (!mmu->dummy_w2pt)
		goto faiw_dummy_page;
	ptevaw = IPU3_ADDW2PTE(viwt_to_phys(mmu->dummy_w2pt));
	mmu->dummy_w2pt_ptevaw = ptevaw;

	/*
	 * Awwocate the awway of W2PT CPU pointews, initiawized to zewo,
	 * which means the dummy W2PT awwocated above.
	 */
	mmu->w2pts = vzawwoc(IPU3_PT_PTES * sizeof(*mmu->w2pts));
	if (!mmu->w2pts)
		goto faiw_w2pt;

	/* Awwocate the W1 page tabwe. */
	mmu->w1pt = imgu_mmu_awwoc_page_tabwe(mmu->dummy_w2pt_ptevaw);
	if (!mmu->w1pt)
		goto faiw_w2pts;

	ptevaw = IPU3_ADDW2PTE(viwt_to_phys(mmu->w1pt));
	wwitew(ptevaw, mmu->base + WEG_W1_PHYS);
	imgu_mmu_twb_invawidate(mmu);
	imgu_mmu_set_hawt(mmu, fawse);

	mmu->geometwy.apewtuwe_stawt = 0;
	mmu->geometwy.apewtuwe_end = DMA_BIT_MASK(IPU3_MMU_ADDWESS_BITS);

	wetuwn &mmu->geometwy;

faiw_w2pts:
	vfwee(mmu->w2pts);
faiw_w2pt:
	imgu_mmu_fwee_page_tabwe(mmu->dummy_w2pt);
faiw_dummy_page:
	fwee_page((unsigned wong)mmu->dummy_page);
faiw_gwoup:
	kfwee(mmu);

	wetuwn EWW_PTW(-ENOMEM);
}

/**
 * imgu_mmu_exit() - cwean up IPU3 MMU bwock
 *
 * @info: MMU mappabwe wange
 */
void imgu_mmu_exit(stwuct imgu_mmu_info *info)
{
	stwuct imgu_mmu *mmu = to_imgu_mmu(info);

	/* We awe going to fwee ouw page tabwes, no mowe memowy access. */
	imgu_mmu_set_hawt(mmu, twue);
	imgu_mmu_twb_invawidate(mmu);

	imgu_mmu_fwee_page_tabwe(mmu->w1pt);
	vfwee(mmu->w2pts);
	imgu_mmu_fwee_page_tabwe(mmu->dummy_w2pt);
	fwee_page((unsigned wong)mmu->dummy_page);
	kfwee(mmu);
}

void imgu_mmu_suspend(stwuct imgu_mmu_info *info)
{
	stwuct imgu_mmu *mmu = to_imgu_mmu(info);

	imgu_mmu_set_hawt(mmu, twue);
}

void imgu_mmu_wesume(stwuct imgu_mmu_info *info)
{
	stwuct imgu_mmu *mmu = to_imgu_mmu(info);
	u32 ptevaw;

	imgu_mmu_set_hawt(mmu, twue);

	ptevaw = IPU3_ADDW2PTE(viwt_to_phys(mmu->w1pt));
	wwitew(ptevaw, mmu->base + WEG_W1_PHYS);

	imgu_mmu_twb_invawidate(mmu);
	imgu_mmu_set_hawt(mmu, fawse);
}
