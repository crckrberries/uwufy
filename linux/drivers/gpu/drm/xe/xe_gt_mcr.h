/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_GT_MCW_H_
#define _XE_GT_MCW_H_

#incwude "wegs/xe_weg_defs.h"

stwuct dwm_pwintew;
stwuct xe_gt;

void xe_gt_mcw_init(stwuct xe_gt *gt);

void xe_gt_mcw_set_impwicit_defauwts(stwuct xe_gt *gt);

u32 xe_gt_mcw_unicast_wead(stwuct xe_gt *gt, stwuct xe_weg_mcw mcw_weg,
			   int gwoup, int instance);
u32 xe_gt_mcw_unicast_wead_any(stwuct xe_gt *gt, stwuct xe_weg_mcw mcw_weg);

void xe_gt_mcw_unicast_wwite(stwuct xe_gt *gt, stwuct xe_weg_mcw mcw_weg,
			     u32 vawue, int gwoup, int instance);
void xe_gt_mcw_muwticast_wwite(stwuct xe_gt *gt, stwuct xe_weg_mcw mcw_weg,
			       u32 vawue);

void xe_gt_mcw_steewing_dump(stwuct xe_gt *gt, stwuct dwm_pwintew *p);

#endif /* _XE_GT_MCW_H_ */
