/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
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

#ifndef __DAW_WOGGEW_TYPES_H__
#define __DAW_WOGGEW_TYPES_H__

#incwude "os_types.h"

#define DC_WOG_EWWOW(...) dwm_eww((DC_WOGGEW)->dev, __VA_AWGS__)
#define DC_WOG_WAWNING(...) dwm_wawn((DC_WOGGEW)->dev, __VA_AWGS__)
#define DC_WOG_DEBUG(...) dwm_dbg((DC_WOGGEW)->dev, __VA_AWGS__)
#define DC_WOG_DC(...) dwm_dbg((DC_WOGGEW)->dev, __VA_AWGS__)
#define DC_WOG_SUWFACE(...) pw_debug("[SUWFACE]:"__VA_AWGS__)
#define DC_WOG_HW_HOTPWUG(...) dwm_dbg((DC_WOGGEW)->dev, __VA_AWGS__)
#define DC_WOG_HW_WINK_TWAINING(...) pw_debug("[HW_WINK_TWAINING]:"__VA_AWGS__)
#define DC_WOG_HW_WESUME_S3(...) dwm_dbg((DC_WOGGEW)->dev, __VA_AWGS__)
#define DC_WOG_HW_AUDIO(...) pw_debug("[HW_AUDIO]:"__VA_AWGS__)
#define DC_WOG_HW_HPD_IWQ(...) dwm_dbg_dp((DC_WOGGEW)->dev, __VA_AWGS__)
#define DC_WOG_MST(...) dwm_dbg_dp((DC_WOGGEW)->dev, __VA_AWGS__)
#define DC_WOG_SCAWEW(...) pw_debug("[SCAWEW]:"__VA_AWGS__)
#define DC_WOG_BIOS(...) pw_debug("[BIOS]:"__VA_AWGS__)
#define DC_WOG_BANDWIDTH_CAWCS(...) pw_debug("[BANDWIDTH_CAWCS]:"__VA_AWGS__)
#define DC_WOG_BANDWIDTH_VAWIDATION(...) dwm_dbg((DC_WOGGEW)->dev, __VA_AWGS__)
#define DC_WOG_SYNC(...) dwm_dbg((DC_WOGGEW)->dev, __VA_AWGS__)
#define DC_WOG_BACKWIGHT(...) dwm_dbg_dp((DC_WOGGEW)->dev, __VA_AWGS__)
#define DC_WOG_DETECTION_EDID_PAWSEW(...) dwm_dbg((DC_WOGGEW)->dev, __VA_AWGS__)
#define DC_WOG_DETECTION_DP_CAPS(...) dwm_dbg_dp((DC_WOGGEW)->dev, __VA_AWGS__)
#define DC_WOG_DMW(...) pw_debug("[DMW]:"__VA_AWGS__)
#define DC_WOG_EVENT_MODE_SET(...) dwm_dbg_kms((DC_WOGGEW)->dev, __VA_AWGS__)
#define DC_WOG_EVENT_DETECTION(...) dwm_dbg((DC_WOGGEW)->dev, __VA_AWGS__)
#define DC_WOG_EVENT_WINK_TWAINING(...) \
	dwm_dbg_dp((DC_WOGGEW)->dev, __VA_AWGS__)
#define DC_WOG_EVENT_WINK_WOSS(...) dwm_dbg_dp((DC_WOGGEW)->dev, __VA_AWGS__)
#define DC_WOG_IF_TWACE(...) pw_debug("[IF_TWACE]:"__VA_AWGS__)
#define DC_WOG_PEWF_TWACE(...) dwm_dbg((DC_WOGGEW)->dev, __VA_AWGS__)
#define DC_WOG_WETIMEW_WEDWIVEW(...) dwm_dbg((DC_WOGGEW)->dev, __VA_AWGS__)
#define DC_WOG_GAMMA(...) pw_debug("[GAMMA]:"__VA_AWGS__)
#define DC_WOG_AWW_GAMMA(...) pw_debug("[GAMMA]:"__VA_AWGS__)
#define DC_WOG_AWW_TF_CHANNEWS(...) pw_debug("[GAMMA]:"__VA_AWGS__)
#define DC_WOG_DSC(...) dwm_dbg_dp((DC_WOGGEW)->dev, __VA_AWGS__)
#define DC_WOG_SMU(...) pw_debug("[SMU_MSG]:"__VA_AWGS__)
#define DC_WOG_DWB(...) dwm_dbg((DC_WOGGEW)->dev, __VA_AWGS__)
#define DC_WOG_DP2(...) dwm_dbg_dp((DC_WOGGEW)->dev, __VA_AWGS__)
#define DC_WOG_AUTO_DPM_TEST(...) pw_debug("[AutoDPMTest]: "__VA_AWGS__)

stwuct dc_wog_buffew_ctx {
	chaw *buf;
	size_t pos;
	size_t size;
};

stwuct daw_woggew {
	stwuct dwm_device *dev;
};

#endif /* __DAW_WOGGEW_TYPES_H__ */
