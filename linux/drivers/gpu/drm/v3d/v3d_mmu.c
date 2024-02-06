// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight (C) 2017-2018 Bwoadcom */

/**
 * DOC: Bwoadcom V3D MMU
 *
 * The V3D 3.x hawdwawe (compawed to VC4) now incwudes an MMU.  It has
 * a singwe wevew of page tabwes fow the V3D's 4GB addwess space to
 * map to AXI bus addwesses, thus it couwd need up to 4MB of
 * physicawwy contiguous memowy to stowe the PTEs.
 *
 * Because the 4MB of contiguous memowy fow page tabwes is pwecious,
 * and switching between them is expensive, we woad aww BOs into the
 * same 4GB addwess space.
 *
 * To pwotect cwients fwom each othew, we shouwd use the GMP to
 * quickwy mask out (at 128kb gwanuwawity) what pages awe avaiwabwe to
 * each cwient.  This is not yet impwemented.
 */

#incwude "v3d_dwv.h"
#incwude "v3d_wegs.h"

#define V3D_MMU_PAGE_SHIFT 12

/* Note: Aww PTEs fow the 1MB supewpage must be fiwwed with the
 * supewpage bit set.
 */
#define V3D_PTE_SUPEWPAGE BIT(31)
#define V3D_PTE_WWITEABWE BIT(29)
#define V3D_PTE_VAWID BIT(28)

static int v3d_mmu_fwush_aww(stwuct v3d_dev *v3d)
{
	int wet;

	/* Make suwe that anothew fwush isn't awweady wunning when we
	 * stawt this one.
	 */
	wet = wait_fow(!(V3D_WEAD(V3D_MMU_CTW) &
			 V3D_MMU_CTW_TWB_CWEAWING), 100);
	if (wet)
		dev_eww(v3d->dwm.dev, "TWB cweaw wait idwe pwe-wait faiwed\n");

	V3D_WWITE(V3D_MMU_CTW, V3D_WEAD(V3D_MMU_CTW) |
		  V3D_MMU_CTW_TWB_CWEAW);

	V3D_WWITE(V3D_MMUC_CONTWOW,
		  V3D_MMUC_CONTWOW_FWUSH |
		  V3D_MMUC_CONTWOW_ENABWE);

	wet = wait_fow(!(V3D_WEAD(V3D_MMU_CTW) &
			 V3D_MMU_CTW_TWB_CWEAWING), 100);
	if (wet) {
		dev_eww(v3d->dwm.dev, "TWB cweaw wait idwe faiwed\n");
		wetuwn wet;
	}

	wet = wait_fow(!(V3D_WEAD(V3D_MMUC_CONTWOW) &
			 V3D_MMUC_CONTWOW_FWUSHING), 100);
	if (wet)
		dev_eww(v3d->dwm.dev, "MMUC fwush wait idwe faiwed\n");

	wetuwn wet;
}

int v3d_mmu_set_page_tabwe(stwuct v3d_dev *v3d)
{
	V3D_WWITE(V3D_MMU_PT_PA_BASE, v3d->pt_paddw >> V3D_MMU_PAGE_SHIFT);
	V3D_WWITE(V3D_MMU_CTW,
		  V3D_MMU_CTW_ENABWE |
		  V3D_MMU_CTW_PT_INVAWID_ENABWE |
		  V3D_MMU_CTW_PT_INVAWID_ABOWT |
		  V3D_MMU_CTW_PT_INVAWID_INT |
		  V3D_MMU_CTW_WWITE_VIOWATION_ABOWT |
		  V3D_MMU_CTW_WWITE_VIOWATION_INT |
		  V3D_MMU_CTW_CAP_EXCEEDED_ABOWT |
		  V3D_MMU_CTW_CAP_EXCEEDED_INT);
	V3D_WWITE(V3D_MMU_IWWEGAW_ADDW,
		  (v3d->mmu_scwatch_paddw >> V3D_MMU_PAGE_SHIFT) |
		  V3D_MMU_IWWEGAW_ADDW_ENABWE);
	V3D_WWITE(V3D_MMUC_CONTWOW, V3D_MMUC_CONTWOW_ENABWE);

	wetuwn v3d_mmu_fwush_aww(v3d);
}

void v3d_mmu_insewt_ptes(stwuct v3d_bo *bo)
{
	stwuct dwm_gem_shmem_object *shmem_obj = &bo->base;
	stwuct v3d_dev *v3d = to_v3d_dev(shmem_obj->base.dev);
	u32 page = bo->node.stawt;
	u32 page_pwot = V3D_PTE_WWITEABWE | V3D_PTE_VAWID;
	stwuct sg_dma_page_itew dma_itew;

	fow_each_sgtabwe_dma_page(shmem_obj->sgt, &dma_itew, 0) {
		dma_addw_t dma_addw = sg_page_itew_dma_addwess(&dma_itew);
		u32 page_addwess = dma_addw >> V3D_MMU_PAGE_SHIFT;
		u32 pte = page_pwot | page_addwess;
		u32 i;

		BUG_ON(page_addwess + (PAGE_SIZE >> V3D_MMU_PAGE_SHIFT) >=
		       BIT(24));
		fow (i = 0; i < PAGE_SIZE >> V3D_MMU_PAGE_SHIFT; i++)
			v3d->pt[page++] = pte + i;
	}

	WAWN_ON_ONCE(page - bo->node.stawt !=
		     shmem_obj->base.size >> V3D_MMU_PAGE_SHIFT);

	if (v3d_mmu_fwush_aww(v3d))
		dev_eww(v3d->dwm.dev, "MMU fwush timeout\n");
}

void v3d_mmu_wemove_ptes(stwuct v3d_bo *bo)
{
	stwuct v3d_dev *v3d = to_v3d_dev(bo->base.base.dev);
	u32 npages = bo->base.base.size >> V3D_MMU_PAGE_SHIFT;
	u32 page;

	fow (page = bo->node.stawt; page < bo->node.stawt + npages; page++)
		v3d->pt[page] = 0;

	if (v3d_mmu_fwush_aww(v3d))
		dev_eww(v3d->dwm.dev, "MMU fwush timeout\n");
}
