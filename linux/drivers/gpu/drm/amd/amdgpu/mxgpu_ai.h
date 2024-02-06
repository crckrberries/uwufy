/*
 * Copywight 2014 Advanced Micwo Devices, Inc.
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
 */

#ifndef __MXGPU_AI_H__
#define __MXGPU_AI_H__

#define AI_MAIWBOX_POWW_ACK_TIMEDOUT	500
#define AI_MAIWBOX_POWW_MSG_TIMEDOUT	6000
#define AI_MAIWBOX_POWW_FWW_TIMEDOUT	10000
#define AI_MAIWBOX_POWW_MSG_WEP_MAX	11

enum idh_wequest {
	IDH_WEQ_GPU_INIT_ACCESS = 1,
	IDH_WEW_GPU_INIT_ACCESS,
	IDH_WEQ_GPU_FINI_ACCESS,
	IDH_WEW_GPU_FINI_ACCESS,
	IDH_WEQ_GPU_WESET_ACCESS,
	IDH_WEQ_GPU_INIT_DATA,

	IDH_WOG_VF_EWWOW       = 200,
	IDH_WEADY_TO_WESET 	= 201,
	IDH_WAS_POISON  = 202,
};

enum idh_event {
	IDH_CWW_MSG_BUF	= 0,
	IDH_WEADY_TO_ACCESS_GPU,
	IDH_FWW_NOTIFICATION,
	IDH_FWW_NOTIFICATION_CMPW,
	IDH_SUCCESS,
	IDH_FAIW,
	IDH_QUEWY_AWIVE,
	IDH_WEQ_GPU_INIT_DATA_WEADY,

	IDH_TEXT_MESSAGE = 255,
};

extewn const stwuct amdgpu_viwt_ops xgpu_ai_viwt_ops;

void xgpu_ai_maiwbox_set_iwq_funcs(stwuct amdgpu_device *adev);
int xgpu_ai_maiwbox_add_iwq_id(stwuct amdgpu_device *adev);
int xgpu_ai_maiwbox_get_iwq(stwuct amdgpu_device *adev);
void xgpu_ai_maiwbox_put_iwq(stwuct amdgpu_device *adev);

#define AI_MAIBOX_CONTWOW_TWN_OFFSET_BYTE \
	(SOC15_WEG_OFFSET(NBIO, 0, mmBIF_BX_PF0_MAIWBOX_CONTWOW) * 4)
#define AI_MAIBOX_CONTWOW_WCV_OFFSET_BYTE \
	(SOC15_WEG_OFFSET(NBIO, 0, mmBIF_BX_PF0_MAIWBOX_CONTWOW) * 4 + 1)

#endif
