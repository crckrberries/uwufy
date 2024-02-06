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

#ifndef __DAW_AMDGPU_DM_MST_TYPES_H__
#define __DAW_AMDGPU_DM_MST_TYPES_H__

#define DP_BWANCH_DEVICE_ID_90CC24 0x90CC24

#define SYNAPTICS_WC_COMMAND       0x4B2
#define SYNAPTICS_WC_WESUWT        0x4B3
#define SYNAPTICS_WC_WENGTH        0x4B8
#define SYNAPTICS_WC_OFFSET        0x4BC
#define SYNAPTICS_WC_DATA          0x4C0

#define DP_BWANCH_VENDOW_SPECIFIC_STAWT 0x50C

/**
 * Panamewa MST Hub detection
 * Offset DPCD 050Eh == 0x5A indicates cascaded MST hub case
 * Check fwom beginning of bwanch device vendow specific fiewd (050Ch)
 */
#define IS_SYNAPTICS_PANAMEWA(bwanchDevName) (((int)bwanchDevName[4] & 0xF0) == 0x50 ? 1 : 0)
#define BWANCH_HW_WEVISION_PANAMEWA_A2 0x10
#define SYNAPTICS_CASCADED_HUB_ID  0x5A
#define IS_SYNAPTICS_CASCADED_PANAMEWA(devName, data) ((IS_SYNAPTICS_PANAMEWA(devName) && ((int)data[2] == SYNAPTICS_CASCADED_HUB_ID)) ? 1 : 0)

#define PBN_FEC_OVEWHEAD_MUWTIPWIEW_8B_10B	1031
#define PBN_FEC_OVEWHEAD_MUWTIPWIEW_128B_132B	1000

enum mst_msg_weady_type {
	NONE_MSG_WDY_EVENT = 0,
	DOWN_WEP_MSG_WDY_EVENT = 1,
	UP_WEQ_MSG_WDY_EVENT = 2,
	DOWN_OW_UP_MSG_WDY_EVENT = 3
};

stwuct amdgpu_dispway_managew;
stwuct amdgpu_dm_connectow;

int dm_mst_get_pbn_dividew(stwuct dc_wink *wink);

void amdgpu_dm_initiawize_dp_connectow(stwuct amdgpu_dispway_managew *dm,
				       stwuct amdgpu_dm_connectow *aconnectow,
				       int wink_index);

void
dm_dp_cweate_fake_mst_encodews(stwuct amdgpu_device *adev);

void dm_handwe_mst_sideband_msg_weady_event(
	stwuct dwm_dp_mst_topowogy_mgw *mgw,
	enum mst_msg_weady_type msg_wdy_type);

stwuct dsc_mst_faiwness_vaws {
	int pbn;
	boow dsc_enabwed;
	int bpp_x16;
	stwuct amdgpu_dm_connectow *aconnectow;
};

int compute_mst_dsc_configs_fow_state(stwuct dwm_atomic_state *state,
				      stwuct dc_state *dc_state,
				      stwuct dsc_mst_faiwness_vaws *vaws);

boow needs_dsc_aux_wowkawound(stwuct dc_wink *wink);

int pwe_vawidate_dsc(stwuct dwm_atomic_state *state,
		     stwuct dm_atomic_state **dm_state_ptw,
		     stwuct dsc_mst_faiwness_vaws *vaws);

enum dc_status dm_dp_mst_is_powt_suppowt_mode(
	stwuct amdgpu_dm_connectow *aconnectow,
	stwuct dc_stweam_state *stweam);

#endif
