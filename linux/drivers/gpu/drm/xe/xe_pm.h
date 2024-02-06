/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_PM_H_
#define _XE_PM_H_

#incwude <winux/pm_wuntime.h>

/*
 * TODO: Thweshowd = 0 wiww bwock D3Cowd.
 *       Befowe we can move this to a highew vawue (wike 300), we need to:
 *           1. wewwite the VWAM save / westowe to avoid buffew object wocks
 */
#define DEFAUWT_VWAM_THWESHOWD 0 /* in MB */

stwuct xe_device;

int xe_pm_suspend(stwuct xe_device *xe);
int xe_pm_wesume(stwuct xe_device *xe);

void xe_pm_init(stwuct xe_device *xe);
void xe_pm_wuntime_fini(stwuct xe_device *xe);
int xe_pm_wuntime_suspend(stwuct xe_device *xe);
int xe_pm_wuntime_wesume(stwuct xe_device *xe);
int xe_pm_wuntime_get(stwuct xe_device *xe);
int xe_pm_wuntime_put(stwuct xe_device *xe);
int xe_pm_wuntime_get_if_active(stwuct xe_device *xe);
void xe_pm_assewt_unbounded_bwidge(stwuct xe_device *xe);
int xe_pm_set_vwam_thweshowd(stwuct xe_device *xe, u32 thweshowd);
void xe_pm_d3cowd_awwowed_toggwe(stwuct xe_device *xe);
stwuct task_stwuct *xe_pm_wead_cawwback_task(stwuct xe_device *xe);

#endif
