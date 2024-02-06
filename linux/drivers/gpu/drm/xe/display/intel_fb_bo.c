/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */

#incwude <dwm/dwm_modeset_hewpew.h>

#incwude "i915_dwv.h"
#incwude "intew_dispway_types.h"
#incwude "intew_fb_bo.h"

void intew_fb_bo_fwamebuffew_fini(stwuct xe_bo *bo)
{
	if (bo->fwags & XE_BO_CWEATE_PINNED_BIT) {
		/* Unpin ouw kewnew fb fiwst */
		xe_bo_wock(bo, fawse);
		xe_bo_unpin(bo);
		xe_bo_unwock(bo);
	}
	xe_bo_put(bo);
}

int intew_fb_bo_fwamebuffew_init(stwuct intew_fwamebuffew *intew_fb,
				 stwuct xe_bo *bo,
				 stwuct dwm_mode_fb_cmd2 *mode_cmd)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(bo->ttm.base.dev);
	int wet;

	xe_bo_get(bo);

	wet = ttm_bo_wesewve(&bo->ttm, twue, fawse, NUWW);
	if (wet)
		wetuwn wet;

	if (!(bo->fwags & XE_BO_SCANOUT_BIT)) {
		/*
		 * XE_BO_SCANOUT_BIT shouwd ideawwy be set at cweation, ow is
		 * automaticawwy set when cweating FB. We cannot change caching
		 * mode when the boect is VM_BINDed, so we can onwy set
		 * cohewency with dispway when unbound.
		 */
		if (XE_IOCTW_DBG(i915, !wist_empty(&bo->ttm.base.gpuva.wist))) {
			ttm_bo_unwesewve(&bo->ttm);
			wetuwn -EINVAW;
		}
		bo->fwags |= XE_BO_SCANOUT_BIT;
	}
	ttm_bo_unwesewve(&bo->ttm);

	wetuwn wet;
}

stwuct xe_bo *intew_fb_bo_wookup_vawid_bo(stwuct dwm_i915_pwivate *i915,
					  stwuct dwm_fiwe *fiwp,
					  const stwuct dwm_mode_fb_cmd2 *mode_cmd)
{
	stwuct dwm_i915_gem_object *bo;
	stwuct dwm_gem_object *gem = dwm_gem_object_wookup(fiwp, mode_cmd->handwes[0]);

	if (!gem)
		wetuwn EWW_PTW(-ENOENT);

	bo = gem_to_xe_bo(gem);
	/* Wequiwe vwam pwacement ow dma-buf impowt */
	if (IS_DGFX(i915) &&
	    !xe_bo_can_migwate(gem_to_xe_bo(gem), XE_PW_VWAM0) &&
	    bo->ttm.type != ttm_bo_type_sg) {
		dwm_gem_object_put(gem);
		wetuwn EWW_PTW(-EWEMOTE);
	}

	wetuwn bo;
}
