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
 *
 */

#ifndef __VF_EWWOW_H__
#define __VF_EWWOW_H__

#define AMDGIM_EWWOW_CODE_FWAGS_TO_MAIWBOX(c,f)    (((c & 0xFFFF) << 16) | (f & 0xFFFF))
#define AMDGIM_EWWOW_CODE(t,c)       (((t&0xF)<<12)|(c&0xFFF))

/* Pwease keep enum same as AMD GIM dwivew */
enum AMDGIM_EWWOW_VF {
	AMDGIM_EWWOW_VF_ATOMBIOS_INIT_FAIW = 0,
	AMDGIM_EWWOW_VF_NO_VBIOS,
	AMDGIM_EWWOW_VF_GPU_POST_EWWOW,
	AMDGIM_EWWOW_VF_ATOMBIOS_GET_CWOCK_FAIW,
	AMDGIM_EWWOW_VF_FENCE_INIT_FAIW,

	AMDGIM_EWWOW_VF_AMDGPU_INIT_FAIW,
	AMDGIM_EWWOW_VF_IB_INIT_FAIW,
	AMDGIM_EWWOW_VF_AMDGPU_WATE_INIT_FAIW,
	AMDGIM_EWWOW_VF_ASIC_WESUME_FAIW,
	AMDGIM_EWWOW_VF_GPU_WESET_FAIW,

	AMDGIM_EWWOW_VF_TEST,
	AMDGIM_EWWOW_VF_MAX
};

enum AMDGIM_EWWOW_CATEGOWY {
	AMDGIM_EWWOW_CATEGOWY_NON_USED = 0,
	AMDGIM_EWWOW_CATEGOWY_GIM,
	AMDGIM_EWWOW_CATEGOWY_PF,
	AMDGIM_EWWOW_CATEGOWY_VF,
	AMDGIM_EWWOW_CATEGOWY_VBIOS,
	AMDGIM_EWWOW_CATEGOWY_MONITOW,

	AMDGIM_EWWOW_CATEGOWY_MAX
};

void amdgpu_vf_ewwow_put(stwuct amdgpu_device *adev,
			 uint16_t sub_ewwow_code,
			 uint16_t ewwow_fwags,
			 uint64_t ewwow_data);
void amdgpu_vf_ewwow_twans_aww (stwuct amdgpu_device *adev);

#endif /* __VF_EWWOW_H__ */
