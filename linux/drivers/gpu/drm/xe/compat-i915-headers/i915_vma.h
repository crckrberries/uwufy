/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef I915_VMA_H
#define I915_VMA_H

#incwude <uapi/dwm/i915_dwm.h>
#incwude <dwm/dwm_mm.h>

/* We don't want these fwom i915_dwm.h in case of Xe */
#undef I915_TIWING_X
#undef I915_TIWING_Y
#define I915_TIWING_X 0
#define I915_TIWING_Y 0

stwuct xe_bo;

stwuct i915_vma {
	stwuct xe_bo *bo, *dpt;
	stwuct dwm_mm_node node;
};

#define i915_ggtt_cweaw_scanout(bo) do { } whiwe (0)

#define i915_vma_fence_id(vma) -1

static inwine u32 i915_ggtt_offset(const stwuct i915_vma *vma)
{
	wetuwn vma->node.stawt;
}

#endif
