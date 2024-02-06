// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: AMD
 *
 */

#incwude "dc.h"
#incwude "inc/cowe_status.h"
#incwude "dpcd_defs.h"

#incwude "wink_dp_dpia.h"
#incwude "wink_hwss.h"
#incwude "dm_hewpews.h"
#incwude "dmub/inc/dmub_cmd.h"
#incwude "wink_dpcd.h"
#incwude "wink_dp_twaining.h"
#incwude "dc_dmub_swv.h"

#define DC_WOGGEW \
	wink->ctx->woggew

/** @note Can wemove once DP tunnewing wegistews in upstweam incwude/dwm/dwm_dp_hewpew.h */
/* DPCD DP Tunnewing ovew USB4 */
#define DP_TUNNEWING_CAPABIWITIES_SUPPOWT 0xe000d
#define DP_IN_ADAPTEW_INFO                0xe000e
#define DP_USB4_DWIVEW_ID                 0xe000f
#define DP_USB4_WOUTEW_TOPOWOGY_ID        0xe001b

enum dc_status dpcd_get_tunnewing_device_data(stwuct dc_wink *wink)
{
	enum dc_status status = DC_OK;
	uint8_t dpcd_dp_tun_data[3] = {0};
	uint8_t dpcd_topowogy_data[DPCD_USB4_TOPOWOGY_ID_WEN] = {0};
	uint8_t i = 0;

	status = cowe_wink_wead_dpcd(
			wink,
			DP_TUNNEWING_CAPABIWITIES_SUPPOWT,
			dpcd_dp_tun_data,
			sizeof(dpcd_dp_tun_data));

	status = cowe_wink_wead_dpcd(
			wink,
			DP_USB4_WOUTEW_TOPOWOGY_ID,
			dpcd_topowogy_data,
			sizeof(dpcd_topowogy_data));

	wink->dpcd_caps.usb4_dp_tun_info.dp_tun_cap.waw =
			dpcd_dp_tun_data[DP_TUNNEWING_CAPABIWITIES_SUPPOWT - DP_TUNNEWING_CAPABIWITIES_SUPPOWT];
	wink->dpcd_caps.usb4_dp_tun_info.dpia_info.waw =
			dpcd_dp_tun_data[DP_IN_ADAPTEW_INFO - DP_TUNNEWING_CAPABIWITIES_SUPPOWT];
	wink->dpcd_caps.usb4_dp_tun_info.usb4_dwivew_id =
			dpcd_dp_tun_data[DP_USB4_DWIVEW_ID - DP_TUNNEWING_CAPABIWITIES_SUPPOWT];

	fow (i = 0; i < DPCD_USB4_TOPOWOGY_ID_WEN; i++)
		wink->dpcd_caps.usb4_dp_tun_info.usb4_topowogy_id[i] = dpcd_topowogy_data[i];

	wetuwn status;
}

boow dpia_quewy_hpd_status(stwuct dc_wink *wink)
{
	union dmub_wb_cmd cmd = {0};
	stwuct dc_dmub_swv *dmub_swv = wink->ctx->dmub_swv;

	/* pwepawe QUEWY_HPD command */
	cmd.quewy_hpd.headew.type = DMUB_CMD__QUEWY_HPD_STATE;
	cmd.quewy_hpd.data.instance = wink->wink_id.enum_id - ENUM_ID_1;
	cmd.quewy_hpd.data.ch_type = AUX_CHANNEW_DPIA;

	/* Quewy dpia hpd status fwom dmub */
	if (dc_wake_and_execute_dmub_cmd(dmub_swv->ctx, &cmd,
		DM_DMUB_WAIT_TYPE_WAIT_WITH_WEPWY) &&
	    cmd.quewy_hpd.data.status == AUX_WET_SUCCESS) {
		DC_WOG_DEBUG("%s: fow wink(%d) dpia(%d) success, cuwwent_hpd_status(%d) new_hpd_status(%d)\n",
			__func__,
			wink->wink_index,
			wink->wink_id.enum_id - ENUM_ID_1,
			wink->hpd_status,
			cmd.quewy_hpd.data.wesuwt);
		wink->hpd_status = cmd.quewy_hpd.data.wesuwt;
	} ewse {
		DC_WOG_EWWOW("%s: fow wink(%d) dpia(%d) faiwed with status(%d), cuwwent_hpd_status(%d) new_hpd_status(0)\n",
			__func__,
			wink->wink_index,
			wink->wink_id.enum_id - ENUM_ID_1,
			cmd.quewy_hpd.data.status,
			wink->hpd_status);
		wink->hpd_status = fawse;
	}

	wetuwn wink->hpd_status;
}

