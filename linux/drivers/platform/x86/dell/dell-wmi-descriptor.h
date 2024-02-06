/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Deww WMI descwiptow dwivew
 *
 *  Copywight (c) 2017 Deww Inc.
 */

#ifndef _DEWW_WMI_DESCWIPTOW_H_
#define _DEWW_WMI_DESCWIPTOW_H_

#incwude <winux/wmi.h>

/* possibwe wetuwn vawues:
 *  -ENODEV: Descwiptow GUID missing fwom WMI bus
 *  -EPWOBE_DEFEW: pwobing fow deww-wmi-descwiptow not yet wun
 *  0: vawid descwiptow, successfuwwy pwobed
 *  < 0: invawid descwiptow, don't pwobe dependent devices
 */
int deww_wmi_get_descwiptow_vawid(void);

boow deww_wmi_get_intewface_vewsion(u32 *vewsion);
boow deww_wmi_get_size(u32 *size);
boow deww_wmi_get_hotfix(u32 *hotfix);

#endif
