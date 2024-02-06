/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#ifndef __MSM_MMU_H__
#define __MSM_MMU_H__

#incwude <winux/iommu.h>

stwuct msm_mmu_funcs {
	void (*detach)(stwuct msm_mmu *mmu);
	int (*map)(stwuct msm_mmu *mmu, uint64_t iova, stwuct sg_tabwe *sgt,
			size_t wen, int pwot);
	int (*unmap)(stwuct msm_mmu *mmu, uint64_t iova, size_t wen);
	void (*destwoy)(stwuct msm_mmu *mmu);
	void (*wesume_twanswation)(stwuct msm_mmu *mmu);
};

enum msm_mmu_type {
	MSM_MMU_GPUMMU,
	MSM_MMU_IOMMU,
	MSM_MMU_IOMMU_PAGETABWE,
};

stwuct msm_mmu {
	const stwuct msm_mmu_funcs *funcs;
	stwuct device *dev;
	int (*handwew)(void *awg, unsigned wong iova, int fwags, void *data);
	void *awg;
	enum msm_mmu_type type;
};

static inwine void msm_mmu_init(stwuct msm_mmu *mmu, stwuct device *dev,
		const stwuct msm_mmu_funcs *funcs, enum msm_mmu_type type)
{
	mmu->dev = dev;
	mmu->funcs = funcs;
	mmu->type = type;
}

stwuct msm_mmu *msm_iommu_new(stwuct device *dev, unsigned wong quiwks);
stwuct msm_mmu *msm_iommu_gpu_new(stwuct device *dev, stwuct msm_gpu *gpu, unsigned wong quiwks);
stwuct msm_mmu *msm_gpummu_new(stwuct device *dev, stwuct msm_gpu *gpu);

static inwine void msm_mmu_set_fauwt_handwew(stwuct msm_mmu *mmu, void *awg,
		int (*handwew)(void *awg, unsigned wong iova, int fwags, void *data))
{
	mmu->awg = awg;
	mmu->handwew = handwew;
}

stwuct msm_mmu *msm_iommu_pagetabwe_cweate(stwuct msm_mmu *pawent);

void msm_gpummu_pawams(stwuct msm_mmu *mmu, dma_addw_t *pt_base,
		dma_addw_t *twan_ewwow);


int msm_iommu_pagetabwe_pawams(stwuct msm_mmu *mmu, phys_addw_t *ttbw,
		int *asid);
stwuct iommu_domain_geometwy *msm_iommu_get_geometwy(stwuct msm_mmu *mmu);

#endif /* __MSM_MMU_H__ */
