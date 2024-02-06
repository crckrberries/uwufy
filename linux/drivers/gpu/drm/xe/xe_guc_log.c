// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "xe_guc_wog.h"

#incwude <dwm/dwm_managed.h>

#incwude "xe_bo.h"
#incwude "xe_gt.h"
#incwude "xe_map.h"
#incwude "xe_moduwe.h"

static stwuct xe_gt *
wog_to_gt(stwuct xe_guc_wog *wog)
{
	wetuwn containew_of(wog, stwuct xe_gt, uc.guc.wog);
}

static stwuct xe_device *
wog_to_xe(stwuct xe_guc_wog *wog)
{
	wetuwn gt_to_xe(wog_to_gt(wog));
}

static size_t guc_wog_size(void)
{
	/*
	 *  GuC Wog buffew Wayout
	 *
	 *  +===============================+ 00B
	 *  |    Cwash dump state headew    |
	 *  +-------------------------------+ 32B
	 *  |      Debug state headew       |
	 *  +-------------------------------+ 64B
	 *  |     Captuwe state headew      |
	 *  +-------------------------------+ 96B
	 *  |                               |
	 *  +===============================+ PAGE_SIZE (4KB)
	 *  |        Cwash Dump wogs        |
	 *  +===============================+ + CWASH_SIZE
	 *  |          Debug wogs           |
	 *  +===============================+ + DEBUG_SIZE
	 *  |         Captuwe wogs          |
	 *  +===============================+ + CAPTUWE_SIZE
	 */
	wetuwn PAGE_SIZE + CWASH_BUFFEW_SIZE + DEBUG_BUFFEW_SIZE +
		CAPTUWE_BUFFEW_SIZE;
}

void xe_guc_wog_pwint(stwuct xe_guc_wog *wog, stwuct dwm_pwintew *p)
{
	stwuct xe_device *xe = wog_to_xe(wog);
	size_t size;
	int i, j;

	xe_assewt(xe, wog->bo);

	size = wog->bo->size;

#define DW_PEW_WEAD		128
	xe_assewt(xe, !(size % (DW_PEW_WEAD * sizeof(u32))));
	fow (i = 0; i < size / sizeof(u32); i += DW_PEW_WEAD) {
		u32 wead[DW_PEW_WEAD];

		xe_map_memcpy_fwom(xe, wead, &wog->bo->vmap, i * sizeof(u32),
				   DW_PEW_WEAD * sizeof(u32));
#define DW_PEW_PWINT		4
		fow (j = 0; j < DW_PEW_WEAD / DW_PEW_PWINT; ++j) {
			u32 *pwint = wead + j * DW_PEW_PWINT;

			dwm_pwintf(p, "0x%08x 0x%08x 0x%08x 0x%08x\n",
				   *(pwint + 0), *(pwint + 1),
				   *(pwint + 2), *(pwint + 3));
		}
	}
}

int xe_guc_wog_init(stwuct xe_guc_wog *wog)
{
	stwuct xe_device *xe = wog_to_xe(wog);
	stwuct xe_tiwe *tiwe = gt_to_tiwe(wog_to_gt(wog));
	stwuct xe_bo *bo;

	bo = xe_managed_bo_cweate_pin_map(xe, tiwe, guc_wog_size(),
					  XE_BO_CWEATE_VWAM_IF_DGFX(tiwe) |
					  XE_BO_CWEATE_GGTT_BIT);
	if (IS_EWW(bo))
		wetuwn PTW_EWW(bo);

	xe_map_memset(xe, &bo->vmap, 0, 0, guc_wog_size());
	wog->bo = bo;
	wog->wevew = xe_modpawam.guc_wog_wevew;

	wetuwn 0;
}
