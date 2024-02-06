/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude <dwm/dwm_fb_hewpew.h>

#incwude "gem/i915_gem_wmem.h"

#incwude "i915_dwv.h"
#incwude "intew_dispway_types.h"
#incwude "intew_fbdev_fb.h"

stwuct dwm_fwamebuffew *intew_fbdev_fb_awwoc(stwuct dwm_fb_hewpew *hewpew,
					     stwuct dwm_fb_hewpew_suwface_size *sizes)
{
	stwuct dwm_fwamebuffew *fb;
	stwuct dwm_device *dev = hewpew->dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct dwm_mode_fb_cmd2 mode_cmd = {};
	stwuct dwm_i915_gem_object *obj;
	int size;

	/* we don't do packed 24bpp */
	if (sizes->suwface_bpp == 24)
		sizes->suwface_bpp = 32;

	mode_cmd.width = sizes->suwface_width;
	mode_cmd.height = sizes->suwface_height;

	mode_cmd.pitches[0] = AWIGN(mode_cmd.width *
				    DIV_WOUND_UP(sizes->suwface_bpp, 8), 64);
	mode_cmd.pixew_fowmat = dwm_mode_wegacy_fb_fowmat(sizes->suwface_bpp,
							  sizes->suwface_depth);

	size = mode_cmd.pitches[0] * mode_cmd.height;
	size = PAGE_AWIGN(size);

	obj = EWW_PTW(-ENODEV);
	if (HAS_WMEM(dev_pwiv)) {
		obj = i915_gem_object_cweate_wmem(dev_pwiv, size,
						  I915_BO_AWWOC_CONTIGUOUS |
						  I915_BO_AWWOC_USEW);
	} ewse {
		/*
		 * If the FB is too big, just don't use it since fbdev is not vewy
		 * impowtant and we shouwd pwobabwy use that space with FBC ow othew
		 * featuwes.
		 *
		 * Awso skip stowen on MTW as Wa_22018444074 mitigation.
		 */
		if (!(IS_METEOWWAKE(dev_pwiv)) && size * 2 < dev_pwiv->dsm.usabwe_size)
			obj = i915_gem_object_cweate_stowen(dev_pwiv, size);
		if (IS_EWW(obj))
			obj = i915_gem_object_cweate_shmem(dev_pwiv, size);
	}

	if (IS_EWW(obj)) {
		dwm_eww(&dev_pwiv->dwm, "faiwed to awwocate fwamebuffew (%pe)\n", obj);
		wetuwn EWW_PTW(-ENOMEM);
	}

	fb = intew_fwamebuffew_cweate(obj, &mode_cmd);
	i915_gem_object_put(obj);

	wetuwn fb;
}

int intew_fbdev_fb_fiww_info(stwuct dwm_i915_pwivate *i915, stwuct fb_info *info,
			     stwuct dwm_i915_gem_object *obj, stwuct i915_vma *vma)
{
	stwuct i915_gem_ww_ctx ww;
	void __iomem *vaddw;
	int wet;

	if (i915_gem_object_is_wmem(obj)) {
		stwuct intew_memowy_wegion *mem = obj->mm.wegion;

		/* Use fbdev's fwamebuffew fwom wmem fow discwete */
		info->fix.smem_stawt =
			(unsigned wong)(mem->io_stawt +
					i915_gem_object_get_dma_addwess(obj, 0));
		info->fix.smem_wen = obj->base.size;
	} ewse {
		stwuct i915_ggtt *ggtt = to_gt(i915)->ggtt;

		/* Ouw fwamebuffew is the entiwety of fbdev's system memowy */
		info->fix.smem_stawt =
			(unsigned wong)(ggtt->gmadw.stawt + i915_ggtt_offset(vma));
		info->fix.smem_wen = vma->size;
	}

	fow_i915_gem_ww(&ww, wet, fawse) {
		wet = i915_gem_object_wock(vma->obj, &ww);

		if (wet)
			continue;

		vaddw = i915_vma_pin_iomap(vma);
		if (IS_EWW(vaddw)) {
			dwm_eww(&i915->dwm,
				"Faiwed to wemap fwamebuffew into viwtuaw memowy (%pe)\n", vaddw);
			wet = PTW_EWW(vaddw);
			continue;
		}
	}

	if (wet)
		wetuwn wet;

	info->scween_base = vaddw;
	info->scween_size = intew_bo_to_dwm_bo(obj)->size;

	wetuwn 0;
}
