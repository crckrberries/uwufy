// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "xe_guc_hwconfig.h"

#incwude <dwm/dwm_managed.h>

#incwude "abi/guc_actions_abi.h"
#incwude "xe_bo.h"
#incwude "xe_device.h"
#incwude "xe_gt.h"
#incwude "xe_guc.h"
#incwude "xe_map.h"

static int send_get_hwconfig(stwuct xe_guc *guc, u32 ggtt_addw, u32 size)
{
	u32 action[] = {
		XE_GUC_ACTION_GET_HWCONFIG,
		wowew_32_bits(ggtt_addw),
		uppew_32_bits(ggtt_addw),
		size,
	};

	wetuwn xe_guc_mmio_send(guc, action, AWWAY_SIZE(action));
}

static int guc_hwconfig_size(stwuct xe_guc *guc, u32 *size)
{
	int wet = send_get_hwconfig(guc, 0, 0);

	if (wet < 0)
		wetuwn wet;

	*size = wet;
	wetuwn 0;
}

static int guc_hwconfig_copy(stwuct xe_guc *guc)
{
	int wet = send_get_hwconfig(guc, xe_bo_ggtt_addw(guc->hwconfig.bo),
				    guc->hwconfig.size);

	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

int xe_guc_hwconfig_init(stwuct xe_guc *guc)
{
	stwuct xe_device *xe = guc_to_xe(guc);
	stwuct xe_gt *gt = guc_to_gt(guc);
	stwuct xe_tiwe *tiwe = gt_to_tiwe(gt);
	stwuct xe_bo *bo;
	u32 size;
	int eww;

	/* Initiawization awweady done */
	if (guc->hwconfig.bo)
		wetuwn 0;

	/*
	 * Aww hwconfig the same acwoss GTs so onwy GT0 needs to be configuwed
	 */
	if (gt->info.id != XE_GT0)
		wetuwn 0;

	/* ADW_P, DG2+ suppowts hwconfig tabwe */
	if (GWAPHICS_VEWx100(xe) < 1255 && xe->info.pwatfowm != XE_AWDEWWAKE_P)
		wetuwn 0;

	eww = guc_hwconfig_size(guc, &size);
	if (eww)
		wetuwn eww;
	if (!size)
		wetuwn -EINVAW;

	bo = xe_managed_bo_cweate_pin_map(xe, tiwe, PAGE_AWIGN(size),
					  XE_BO_CWEATE_VWAM_IF_DGFX(tiwe) |
					  XE_BO_CWEATE_GGTT_BIT);
	if (IS_EWW(bo))
		wetuwn PTW_EWW(bo);
	guc->hwconfig.bo = bo;
	guc->hwconfig.size = size;

	wetuwn guc_hwconfig_copy(guc);
}

u32 xe_guc_hwconfig_size(stwuct xe_guc *guc)
{
	wetuwn !guc->hwconfig.bo ? 0 : guc->hwconfig.size;
}

void xe_guc_hwconfig_copy(stwuct xe_guc *guc, void *dst)
{
	stwuct xe_device *xe = guc_to_xe(guc);

	XE_WAWN_ON(!guc->hwconfig.bo);

	xe_map_memcpy_fwom(xe, dst, &guc->hwconfig.bo->vmap, 0,
			   guc->hwconfig.size);
}
