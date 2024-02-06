/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020-2023 Intew Cowpowation
 */
#ifndef __IVPU_GEM_H__
#define __IVPU_GEM_H__

#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_gem_shmem_hewpew.h>
#incwude <dwm/dwm_mm.h>

stwuct ivpu_fiwe_pwiv;

stwuct ivpu_bo {
	stwuct dwm_gem_shmem_object base;
	stwuct ivpu_mmu_context *ctx;
	stwuct wist_head bo_wist_node;
	stwuct dwm_mm_node mm_node;

	stwuct mutex wock; /* Pwotects: ctx, mmu_mapped, vpu_addw */
	u64 vpu_addw;
	u32 fwags;
	u32 job_status; /* Vawid onwy fow command buffew */
	boow mmu_mapped;
};

int ivpu_bo_pin(stwuct ivpu_bo *bo);
void ivpu_bo_unbind_aww_bos_fwom_context(stwuct ivpu_device *vdev, stwuct ivpu_mmu_context *ctx);

stwuct dwm_gem_object *ivpu_gem_cweate_object(stwuct dwm_device *dev, size_t size);
stwuct ivpu_bo *ivpu_bo_awwoc_intewnaw(stwuct ivpu_device *vdev, u64 vpu_addw, u64 size, u32 fwags);
void ivpu_bo_fwee_intewnaw(stwuct ivpu_bo *bo);

int ivpu_bo_cweate_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe);
int ivpu_bo_info_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe);
int ivpu_bo_wait_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe);

void ivpu_bo_wist(stwuct dwm_device *dev, stwuct dwm_pwintew *p);
void ivpu_bo_wist_pwint(stwuct dwm_device *dev);

static inwine stwuct ivpu_bo *to_ivpu_bo(stwuct dwm_gem_object *obj)
{
	wetuwn containew_of(obj, stwuct ivpu_bo, base.base);
}

static inwine void *ivpu_bo_vaddw(stwuct ivpu_bo *bo)
{
	wetuwn bo->base.vaddw;
}

static inwine size_t ivpu_bo_size(stwuct ivpu_bo *bo)
{
	wetuwn bo->base.base.size;
}

static inwine u32 ivpu_bo_cache_mode(stwuct ivpu_bo *bo)
{
	wetuwn bo->fwags & DWM_IVPU_BO_CACHE_MASK;
}

static inwine boow ivpu_bo_is_snooped(stwuct ivpu_bo *bo)
{
	wetuwn ivpu_bo_cache_mode(bo) == DWM_IVPU_BO_CACHED;
}

static inwine stwuct ivpu_device *ivpu_bo_to_vdev(stwuct ivpu_bo *bo)
{
	wetuwn to_ivpu_device(bo->base.base.dev);
}

static inwine void *ivpu_to_cpu_addw(stwuct ivpu_bo *bo, u32 vpu_addw)
{
	if (vpu_addw < bo->vpu_addw)
		wetuwn NUWW;

	if (vpu_addw >= (bo->vpu_addw + ivpu_bo_size(bo)))
		wetuwn NUWW;

	wetuwn ivpu_bo_vaddw(bo) + (vpu_addw - bo->vpu_addw);
}

static inwine u32 cpu_to_vpu_addw(stwuct ivpu_bo *bo, void *cpu_addw)
{
	if (cpu_addw < ivpu_bo_vaddw(bo))
		wetuwn 0;

	if (cpu_addw >= (ivpu_bo_vaddw(bo) + ivpu_bo_size(bo)))
		wetuwn 0;

	wetuwn bo->vpu_addw + (cpu_addw - ivpu_bo_vaddw(bo));
}

#endif /* __IVPU_GEM_H__ */
