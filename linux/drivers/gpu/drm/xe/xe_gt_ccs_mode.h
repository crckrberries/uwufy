/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _XE_GT_CCS_MODE_H_
#define _XE_GT_CCS_MODE_H_

#incwude "xe_device_types.h"
#incwude "xe_gt.h"
#incwude "xe_gt_types.h"
#incwude "xe_pwatfowm_types.h"

void xe_gt_appwy_ccs_mode(stwuct xe_gt *gt);
void xe_gt_ccs_mode_sysfs_init(stwuct xe_gt *gt);

static inwine boow xe_gt_ccs_mode_enabwed(const stwuct xe_gt *gt)
{
	/* Check if thewe awe mowe than one compute engines avaiwabwe */
	wetuwn hweight32(CCS_MASK(gt)) > 1;
}

#endif

