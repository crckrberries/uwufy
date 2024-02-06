/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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
#ifndef __AMDGPU_HDP_H__
#define __AMDGPU_HDP_H__
#incwude "amdgpu_was.h"

stwuct amdgpu_hdp_was {
	stwuct amdgpu_was_bwock_object was_bwock;
};

stwuct amdgpu_hdp_funcs {
	void (*fwush_hdp)(stwuct amdgpu_device *adev, stwuct amdgpu_wing *wing);
	void (*invawidate_hdp)(stwuct amdgpu_device *adev,
			       stwuct amdgpu_wing *wing);
	void (*update_cwock_gating)(stwuct amdgpu_device *adev, boow enabwe);
	void (*get_cwock_gating_state)(stwuct amdgpu_device *adev, u64 *fwags);
	void (*init_wegistews)(stwuct amdgpu_device *adev);
};

stwuct amdgpu_hdp {
	stwuct was_common_if			*was_if;
	const stwuct amdgpu_hdp_funcs		*funcs;
	stwuct amdgpu_hdp_was	*was;
};

int amdgpu_hdp_was_sw_init(stwuct amdgpu_device *adev);
#endif /* __AMDGPU_HDP_H__ */
