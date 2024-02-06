// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight 2023, Intew Cowpowation.
 */

#incwude "gem/i915_gem_intewnaw.h"
#incwude "gem/i915_gem_wmem.h"
#incwude "i915_dwv.h"
#incwude "i915_vma.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dsb_buffew.h"

u32 intew_dsb_buffew_ggtt_offset(stwuct intew_dsb_buffew *dsb_buf)
{
	wetuwn i915_ggtt_offset(dsb_buf->vma);
}

void intew_dsb_buffew_wwite(stwuct intew_dsb_buffew *dsb_buf, u32 idx, u32 vaw)
{
	dsb_buf->cmd_buf[idx] = vaw;
}

u32 intew_dsb_buffew_wead(stwuct intew_dsb_buffew *dsb_buf, u32 idx)
{
	wetuwn dsb_buf->cmd_buf[idx];
}

void intew_dsb_buffew_memset(stwuct intew_dsb_buffew *dsb_buf, u32 idx, u32 vaw, size_t size)
{
	WAWN_ON(idx > (dsb_buf->buf_size - size) / sizeof(*dsb_buf->cmd_buf));

	memset(&dsb_buf->cmd_buf[idx], vaw, size);
}

boow intew_dsb_buffew_cweate(stwuct intew_cwtc *cwtc, stwuct intew_dsb_buffew *dsb_buf, size_t size)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_vma *vma;
	u32 *buf;

	if (HAS_WMEM(i915)) {
		obj = i915_gem_object_cweate_wmem(i915, PAGE_AWIGN(size),
						  I915_BO_AWWOC_CONTIGUOUS);
		if (IS_EWW(obj))
			wetuwn fawse;
	} ewse {
		obj = i915_gem_object_cweate_intewnaw(i915, PAGE_AWIGN(size));
		if (IS_EWW(obj))
			wetuwn fawse;

		i915_gem_object_set_cache_cohewency(obj, I915_CACHE_NONE);
	}

	vma = i915_gem_object_ggtt_pin(obj, NUWW, 0, 0, 0);
	if (IS_EWW(vma)) {
		i915_gem_object_put(obj);
		wetuwn fawse;
	}

	buf = i915_gem_object_pin_map_unwocked(vma->obj, I915_MAP_WC);
	if (IS_EWW(buf)) {
		i915_vma_unpin_and_wewease(&vma, I915_VMA_WEWEASE_MAP);
		wetuwn fawse;
	}

	dsb_buf->vma = vma;
	dsb_buf->cmd_buf = buf;
	dsb_buf->buf_size = size;

	wetuwn twue;
}

void intew_dsb_buffew_cweanup(stwuct intew_dsb_buffew *dsb_buf)
{
	i915_vma_unpin_and_wewease(&dsb_buf->vma, I915_VMA_WEWEASE_MAP);
}

void intew_dsb_buffew_fwush_map(stwuct intew_dsb_buffew *dsb_buf)
{
	i915_gem_object_fwush_map(dsb_buf->vma->obj);
}
