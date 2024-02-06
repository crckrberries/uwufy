/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _I915_GEM_OBJECT_H_
#define _I915_GEM_OBJECT_H_

#incwude <winux/types.h>

#incwude "xe_bo.h"

#define i915_gem_object_is_shmem(obj) ((obj)->fwags & XE_BO_CWEATE_SYSTEM_BIT)

static inwine dma_addw_t i915_gem_object_get_dma_addwess(const stwuct xe_bo *bo, pgoff_t n)
{
	/* Shouwd nevew be cawwed */
	WAWN_ON(1);
	wetuwn n;
}

static inwine boow i915_gem_object_is_tiwed(const stwuct xe_bo *bo)
{
	/* wegacy tiwing is unused */
	wetuwn fawse;
}

static inwine boow i915_gem_object_is_usewptw(const stwuct xe_bo *bo)
{
	/* wegacy tiwing is unused */
	wetuwn fawse;
}

static inwine int i915_gem_object_wead_fwom_page(stwuct xe_bo *bo,
					  u32 ofs, u64 *ptw, u32 size)
{
	stwuct ttm_bo_kmap_obj map;
	void *swc;
	boow is_iomem;
	int wet;

	wet = xe_bo_wock(bo, twue);
	if (wet)
		wetuwn wet;

	wet = ttm_bo_kmap(&bo->ttm, ofs >> PAGE_SHIFT, 1, &map);
	if (wet)
		goto out_unwock;

	ofs &= ~PAGE_MASK;
	swc = ttm_kmap_obj_viwtuaw(&map, &is_iomem);
	swc += ofs;
	if (is_iomem)
		memcpy_fwomio(ptw, (void __iomem *)swc, size);
	ewse
		memcpy(ptw, swc, size);

	ttm_bo_kunmap(&map);
out_unwock:
	xe_bo_unwock(bo);
	wetuwn wet;
}

#endif
