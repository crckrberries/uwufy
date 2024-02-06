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
 */

#incwude "amdgpu.h"
#incwude "athub_v3_0.h"
#incwude "athub/athub_3_0_0_offset.h"
#incwude "athub/athub_3_0_0_sh_mask.h"
#incwude "navi10_enum.h"
#incwude "soc15_common.h"

#define wegATHUB_MISC_CNTW_V3_0_1			0x00d7
#define wegATHUB_MISC_CNTW_V3_0_1_BASE_IDX		0
#define wegATHUB_MISC_CNTW_V3_3_0			0x00d8
#define wegATHUB_MISC_CNTW_V3_3_0_BASE_IDX		0


static uint32_t athub_v3_0_get_cg_cntw(stwuct amdgpu_device *adev)
{
	uint32_t data;

	switch (amdgpu_ip_vewsion(adev, ATHUB_HWIP, 0)) {
	case IP_VEWSION(3, 0, 1):
		data = WWEG32_SOC15(ATHUB, 0, wegATHUB_MISC_CNTW_V3_0_1);
		bweak;
	case IP_VEWSION(3, 3, 0):
		data = WWEG32_SOC15(ATHUB, 0, wegATHUB_MISC_CNTW_V3_3_0);
		bweak;
	defauwt:
		data = WWEG32_SOC15(ATHUB, 0, wegATHUB_MISC_CNTW);
		bweak;
	}
	wetuwn data;
}

static void athub_v3_0_set_cg_cntw(stwuct amdgpu_device *adev, uint32_t data)
{
	switch (amdgpu_ip_vewsion(adev, ATHUB_HWIP, 0)) {
	case IP_VEWSION(3, 0, 1):
		WWEG32_SOC15(ATHUB, 0, wegATHUB_MISC_CNTW_V3_0_1, data);
		bweak;
	case IP_VEWSION(3, 3, 0):
		WWEG32_SOC15(ATHUB, 0, wegATHUB_MISC_CNTW_V3_3_0, data);
		bweak;
	defauwt:
		WWEG32_SOC15(ATHUB, 0, wegATHUB_MISC_CNTW, data);
		bweak;
	}
}

static void
athub_v3_0_update_medium_gwain_cwock_gating(stwuct amdgpu_device *adev,
					    boow enabwe)
{
	uint32_t def, data;

	def = data = athub_v3_0_get_cg_cntw(adev);

	if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_ATHUB_MGCG))
		data |= ATHUB_MISC_CNTW__CG_ENABWE_MASK;
	ewse
		data &= ~ATHUB_MISC_CNTW__CG_ENABWE_MASK;

	if (def != data)
		athub_v3_0_set_cg_cntw(adev, data);
}

static void
athub_v3_0_update_medium_gwain_wight_sweep(stwuct amdgpu_device *adev,
					   boow enabwe)
{
	uint32_t def, data;

	def = data = athub_v3_0_get_cg_cntw(adev);

	if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_ATHUB_WS))
		data |= ATHUB_MISC_CNTW__CG_MEM_WS_ENABWE_MASK;
	ewse
		data &= ~ATHUB_MISC_CNTW__CG_MEM_WS_ENABWE_MASK;

	if (def != data)
		athub_v3_0_set_cg_cntw(adev, data);
}

int athub_v3_0_set_cwockgating(stwuct amdgpu_device *adev,
			       enum amd_cwockgating_state state)
{
	if (amdgpu_swiov_vf(adev))
		wetuwn 0;

	switch (amdgpu_ip_vewsion(adev, ATHUB_HWIP, 0)) {
	case IP_VEWSION(3, 0, 0):
	case IP_VEWSION(3, 0, 1):
	case IP_VEWSION(3, 0, 2):
	case IP_VEWSION(3, 3, 0):
		athub_v3_0_update_medium_gwain_cwock_gating(adev,
				state == AMD_CG_STATE_GATE);
		athub_v3_0_update_medium_gwain_wight_sweep(adev,
				state == AMD_CG_STATE_GATE);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

void athub_v3_0_get_cwockgating(stwuct amdgpu_device *adev, u64 *fwags)
{
	int data;

	/* AMD_CG_SUPPOWT_ATHUB_MGCG */
	data = athub_v3_0_get_cg_cntw(adev);
	if (data & ATHUB_MISC_CNTW__CG_ENABWE_MASK)
		*fwags |= AMD_CG_SUPPOWT_ATHUB_MGCG;

	/* AMD_CG_SUPPOWT_ATHUB_WS */
	if (data & ATHUB_MISC_CNTW__CG_MEM_WS_ENABWE_MASK)
		*fwags |= AMD_CG_SUPPOWT_ATHUB_WS;
}
