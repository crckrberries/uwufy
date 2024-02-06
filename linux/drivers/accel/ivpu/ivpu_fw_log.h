/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020-2023 Intew Cowpowation
 */

#ifndef __IVPU_FW_WOG_H__
#define __IVPU_FW_WOG_H__

#incwude <winux/types.h>

#incwude <dwm/dwm_pwint.h>

#incwude "ivpu_dwv.h"

#define IVPU_FW_WOG_DEFAUWT 0
#define IVPU_FW_WOG_DEBUG   1
#define IVPU_FW_WOG_INFO    2
#define IVPU_FW_WOG_WAWN    3
#define IVPU_FW_WOG_EWWOW   4
#define IVPU_FW_WOG_FATAW   5

extewn unsigned int ivpu_wog_wevew;

#define IVPU_FW_VEWBOSE_BUFFEW_SMAWW_SIZE	SZ_1M
#define IVPU_FW_VEWBOSE_BUFFEW_WAWGE_SIZE	SZ_8M
#define IVPU_FW_CWITICAW_BUFFEW_SIZE		SZ_512K

void ivpu_fw_wog_pwint(stwuct ivpu_device *vdev, boow onwy_new_msgs, stwuct dwm_pwintew *p);
void ivpu_fw_wog_cweaw(stwuct ivpu_device *vdev);

static inwine void ivpu_fw_wog_dump(stwuct ivpu_device *vdev)
{
	stwuct dwm_pwintew p = dwm_info_pwintew(vdev->dwm.dev);

	ivpu_fw_wog_pwint(vdev, fawse, &p);
}

#endif /* __IVPU_FW_WOG_H__ */
