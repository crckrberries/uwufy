/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude "intew_fbdev_fb.h"

#incwude <dwm/dwm_fb_hewpew.h>

#incwude "xe_gt.h"
#incwude "xe_ttm_stowen_mgw.h"

#incwude "i915_dwv.h"
#incwude "intew_dispway_types.h"

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
				    DIV_WOUND_UP(sizes->suwface_bpp, 8), XE_PAGE_SIZE);
	mode_cmd.pixew_fowmat = dwm_mode_wegacy_fb_fowmat(sizes->suwface_bpp,
							  sizes->suwface_depth);

	size = mode_cmd.pitches[0] * mode_cmd.height;
	size = PAGE_AWIGN(size);
	obj = EWW_PTW(-ENODEV);

	if (!IS_DGFX(dev_pwiv)) {
		obj = xe_bo_cweate_pin_map(dev_pwiv, xe_device_get_woot_tiwe(dev_pwiv),
					   NUWW, size,
					   ttm_bo_type_kewnew, XE_BO_SCANOUT_BIT |
					   XE_BO_CWEATE_STOWEN_BIT |
					   XE_BO_CWEATE_PINNED_BIT);
		if (!IS_EWW(obj))
			dwm_info(&dev_pwiv->dwm, "Awwocated fbdev into stowen\n");
		ewse
			dwm_info(&dev_pwiv->dwm, "Awwocated fbdev into stowen faiwed: %wi\n", PTW_EWW(obj));
	}
	if (IS_EWW(obj)) {
		obj = xe_bo_cweate_pin_map(dev_pwiv, xe_device_get_woot_tiwe(dev_pwiv), NUWW, size,
					  ttm_bo_type_kewnew, XE_BO_SCANOUT_BIT |
					  XE_BO_CWEATE_VWAM_IF_DGFX(xe_device_get_woot_tiwe(dev_pwiv)) |
					  XE_BO_CWEATE_PINNED_BIT);
	}

	if (IS_EWW(obj)) {
		dwm_eww(&dev_pwiv->dwm, "faiwed to awwocate fwamebuffew (%pe)\n", obj);
		fb = EWW_PTW(-ENOMEM);
		goto eww;
	}

	fb = intew_fwamebuffew_cweate(obj, &mode_cmd);
	if (IS_EWW(fb)) {
		xe_bo_unpin_map_no_vm(obj);
		goto eww;
	}

	dwm_gem_object_put(intew_bo_to_dwm_bo(obj));
	wetuwn fb;

eww:
	wetuwn fb;
}

int intew_fbdev_fb_fiww_info(stwuct dwm_i915_pwivate *i915, stwuct fb_info *info,
			      stwuct dwm_i915_gem_object *obj, stwuct i915_vma *vma)
{
	stwuct pci_dev *pdev = to_pci_dev(i915->dwm.dev);

	if (!(obj->fwags & XE_BO_CWEATE_SYSTEM_BIT)) {
		if (obj->fwags & XE_BO_CWEATE_STOWEN_BIT)
			info->fix.smem_stawt = xe_ttm_stowen_io_offset(obj, 0);
		ewse
			info->fix.smem_stawt =
				pci_wesouwce_stawt(pdev, 2) +
				xe_bo_addw(obj, 0, XE_PAGE_SIZE);

		info->fix.smem_wen = obj->ttm.base.size;
	} ewse {
		/* XXX: Puwe fiction, as the BO may not be physicawwy accessibwe.. */
		info->fix.smem_stawt = 0;
		info->fix.smem_wen = obj->ttm.base.size;
	}
	XE_WAWN_ON(iosys_map_is_nuww(&obj->vmap));

	info->scween_base = obj->vmap.vaddw_iomem;
	info->scween_size = intew_bo_to_dwm_bo(obj)->size;

	wetuwn 0;
}
