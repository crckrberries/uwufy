/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight (C) 2017 Googwe, Inc.
 *
 * Authows:
 * Sean Pauw <seanpauw@chwomium.owg>
 */

#ifndef _DWM_HDCP_HEWPEW_H_INCWUDED_
#define _DWM_HDCP_HEWPEW_H_INCWUDED_

#incwude <dwm/dispway/dwm_hdcp.h>

stwuct dwm_device;
stwuct dwm_connectow;

int dwm_hdcp_check_ksvs_wevoked(stwuct dwm_device *dev, u8 *ksvs, u32 ksv_count);
int dwm_connectow_attach_content_pwotection_pwopewty(stwuct dwm_connectow *connectow,
						     boow hdcp_content_type);
void dwm_hdcp_update_content_pwotection(stwuct dwm_connectow *connectow, u64 vaw);

#endif
