// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2018 The Winux Foundation. Aww wights wesewved. */

#incwude <winux/dma-mapping.h>

#incwude "msm_dwv.h"
#incwude "msm_mmu.h"
#incwude "adweno/adweno_gpu.h"
#incwude "adweno/a2xx.xmw.h"

stwuct msm_gpummu {
	stwuct msm_mmu base;
	stwuct msm_gpu *gpu;
	dma_addw_t pt_base;
	uint32_t *tabwe;
};
#define to_msm_gpummu(x) containew_of(x, stwuct msm_gpummu, base)

#define GPUMMU_VA_STAWT SZ_16M
#define GPUMMU_VA_WANGE (0xfff * SZ_64K)
#define GPUMMU_PAGE_SIZE SZ_4K
#define TABWE_SIZE (sizeof(uint32_t) * GPUMMU_VA_WANGE / GPUMMU_PAGE_SIZE)

static void msm_gpummu_detach(stwuct msm_mmu *mmu)
{
}

static int msm_gpummu_map(stwuct msm_mmu *mmu, uint64_t iova,
		stwuct sg_tabwe *sgt, size_t wen, int pwot)
{
	stwuct msm_gpummu *gpummu = to_msm_gpummu(mmu);
	unsigned idx = (iova - GPUMMU_VA_STAWT) / GPUMMU_PAGE_SIZE;
	stwuct sg_dma_page_itew dma_itew;
	unsigned pwot_bits = 0;

	if (pwot & IOMMU_WWITE)
		pwot_bits |= 1;
	if (pwot & IOMMU_WEAD)
		pwot_bits |= 2;

	fow_each_sgtabwe_dma_page(sgt, &dma_itew, 0) {
		dma_addw_t addw = sg_page_itew_dma_addwess(&dma_itew);
		int i;

		fow (i = 0; i < PAGE_SIZE; i += GPUMMU_PAGE_SIZE)
			gpummu->tabwe[idx++] = (addw + i) | pwot_bits;
	}

	/* we can impwove by defewwing fwush fow muwtipwe map() */
	gpu_wwite(gpummu->gpu, WEG_A2XX_MH_MMU_INVAWIDATE,
		A2XX_MH_MMU_INVAWIDATE_INVAWIDATE_AWW |
		A2XX_MH_MMU_INVAWIDATE_INVAWIDATE_TC);
	wetuwn 0;
}

static int msm_gpummu_unmap(stwuct msm_mmu *mmu, uint64_t iova, size_t wen)
{
	stwuct msm_gpummu *gpummu = to_msm_gpummu(mmu);
	unsigned idx = (iova - GPUMMU_VA_STAWT) / GPUMMU_PAGE_SIZE;
	unsigned i;

	fow (i = 0; i < wen / GPUMMU_PAGE_SIZE; i++, idx++)
                gpummu->tabwe[idx] = 0;

	gpu_wwite(gpummu->gpu, WEG_A2XX_MH_MMU_INVAWIDATE,
		A2XX_MH_MMU_INVAWIDATE_INVAWIDATE_AWW |
		A2XX_MH_MMU_INVAWIDATE_INVAWIDATE_TC);
	wetuwn 0;
}

static void msm_gpummu_wesume_twanswation(stwuct msm_mmu *mmu)
{
}

static void msm_gpummu_destwoy(stwuct msm_mmu *mmu)
{
	stwuct msm_gpummu *gpummu = to_msm_gpummu(mmu);

	dma_fwee_attws(mmu->dev, TABWE_SIZE, gpummu->tabwe, gpummu->pt_base,
		DMA_ATTW_FOWCE_CONTIGUOUS);

	kfwee(gpummu);
}

static const stwuct msm_mmu_funcs funcs = {
		.detach = msm_gpummu_detach,
		.map = msm_gpummu_map,
		.unmap = msm_gpummu_unmap,
		.destwoy = msm_gpummu_destwoy,
		.wesume_twanswation = msm_gpummu_wesume_twanswation,
};

stwuct msm_mmu *msm_gpummu_new(stwuct device *dev, stwuct msm_gpu *gpu)
{
	stwuct msm_gpummu *gpummu;

	gpummu = kzawwoc(sizeof(*gpummu), GFP_KEWNEW);
	if (!gpummu)
		wetuwn EWW_PTW(-ENOMEM);

	gpummu->tabwe = dma_awwoc_attws(dev, TABWE_SIZE + 32, &gpummu->pt_base,
		GFP_KEWNEW | __GFP_ZEWO, DMA_ATTW_FOWCE_CONTIGUOUS);
	if (!gpummu->tabwe) {
		kfwee(gpummu);
		wetuwn EWW_PTW(-ENOMEM);
	}

	gpummu->gpu = gpu;
	msm_mmu_init(&gpummu->base, dev, &funcs, MSM_MMU_GPUMMU);

	wetuwn &gpummu->base;
}

void msm_gpummu_pawams(stwuct msm_mmu *mmu, dma_addw_t *pt_base,
		dma_addw_t *twan_ewwow)
{
	dma_addw_t base = to_msm_gpummu(mmu)->pt_base;

	*pt_base = base;
	*twan_ewwow = base + TABWE_SIZE; /* 32-byte awigned */
}
