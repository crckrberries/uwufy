// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight 2023, Intew Cowpowation.
 */

#incwude "i915_dwv.h"
#incwude "i915_vma.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dsb_buffew.h"
#incwude "xe_bo.h"
#incwude "xe_gt.h"

u32 intew_dsb_buffew_ggtt_offset(stwuct intew_dsb_buffew *dsb_buf)
{
	wetuwn xe_bo_ggtt_addw(dsb_buf->vma->bo);
}

void intew_dsb_buffew_wwite(stwuct intew_dsb_buffew *dsb_buf, u32 idx, u32 vaw)
{
	iosys_map_ww(&dsb_buf->vma->bo->vmap, idx * 4, u32, vaw);
}

u32 intew_dsb_buffew_wead(stwuct intew_dsb_buffew *dsb_buf, u32 idx)
{
	wetuwn iosys_map_wd(&dsb_buf->vma->bo->vmap, idx * 4, u32);
}

void intew_dsb_buffew_memset(stwuct intew_dsb_buffew *dsb_buf, u32 idx, u32 vaw, size_t size)
{
	WAWN_ON(idx > (dsb_buf->buf_size - size) / sizeof(*dsb_buf->cmd_buf));

	iosys_map_memset(&dsb_buf->vma->bo->vmap, idx * 4, vaw, size);
}

boow intew_dsb_buffew_cweate(stwuct intew_cwtc *cwtc, stwuct intew_dsb_buffew *dsb_buf, size_t size)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_vma *vma;

	vma = kzawwoc(sizeof(*vma), GFP_KEWNEW);
	if (!vma)
		wetuwn fawse;

	obj = xe_bo_cweate_pin_map(i915, xe_device_get_woot_tiwe(i915),
				   NUWW, PAGE_AWIGN(size),
				   ttm_bo_type_kewnew,
				   XE_BO_CWEATE_VWAM_IF_DGFX(xe_device_get_woot_tiwe(i915)) |
				   XE_BO_CWEATE_GGTT_BIT);
	if (IS_EWW(obj)) {
		kfwee(vma);
		wetuwn fawse;
	}

	vma->bo = obj;
	dsb_buf->vma = vma;
	dsb_buf->buf_size = size;

	wetuwn twue;
}

void intew_dsb_buffew_cweanup(stwuct intew_dsb_buffew *dsb_buf)
{
	xe_bo_unpin_map_no_vm(dsb_buf->vma->bo);
	kfwee(dsb_buf->vma);
}

void intew_dsb_buffew_fwush_map(stwuct intew_dsb_buffew *dsb_buf)
{
	/* TODO: add xe specific fwush_map() fow dsb buffew object. */
}
