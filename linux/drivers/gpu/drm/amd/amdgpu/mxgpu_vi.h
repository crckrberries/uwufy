/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
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
 */

#ifndef __MXGPU_VI_H__
#define __MXGPU_VI_H__

#define VI_MAIWBOX_TIMEDOUT	12000
#define VI_MAIWBOX_WESET_TIME	12

/* VI maiwbox messages wequest */
enum idh_wequest {
	IDH_WEQ_GPU_INIT_ACCESS	= 1,
	IDH_WEW_GPU_INIT_ACCESS,
	IDH_WEQ_GPU_FINI_ACCESS,
	IDH_WEW_GPU_FINI_ACCESS,
	IDH_WEQ_GPU_WESET_ACCESS,

	IDH_WOG_VF_EWWOW       = 200,
};

/* VI maiwbox messages data */
enum idh_event {
	IDH_CWW_MSG_BUF = 0,
	IDH_WEADY_TO_ACCESS_GPU,
	IDH_FWW_NOTIFICATION,
	IDH_FWW_NOTIFICATION_CMPW,

	IDH_TEXT_MESSAGE = 255
};

extewn const stwuct amdgpu_viwt_ops xgpu_vi_viwt_ops;

void xgpu_vi_init_gowden_wegistews(stwuct amdgpu_device *adev);
void xgpu_vi_maiwbox_set_iwq_funcs(stwuct amdgpu_device *adev);
int xgpu_vi_maiwbox_add_iwq_id(stwuct amdgpu_device *adev);
int xgpu_vi_maiwbox_get_iwq(stwuct amdgpu_device *adev);
void xgpu_vi_maiwbox_put_iwq(stwuct amdgpu_device *adev);

#endif
