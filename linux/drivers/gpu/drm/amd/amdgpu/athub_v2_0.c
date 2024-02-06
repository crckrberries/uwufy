/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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
#incwude "athub_v2_0.h"

#incwude "athub/athub_2_0_0_offset.h"
#incwude "athub/athub_2_0_0_sh_mask.h"
#incwude "athub/athub_2_0_0_defauwt.h"

#incwude "soc15_common.h"

static void
athub_v2_0_update_medium_gwain_cwock_gating(stwuct amdgpu_device *adev,
					    boow enabwe)
{
	uint32_t def, data;

	if (!(adev->cg_fwags & AMD_CG_SUPPOWT_MC_MGCG))
		wetuwn;

	def = data = WWEG32_SOC15(ATHUB, 0, mmATHUB_MISC_CNTW);

	if (enabwe)
		data |= ATHUB_MISC_CNTW__CG_ENABWE_MASK;
	ewse
		data &= ~ATHUB_MISC_CNTW__CG_ENABWE_MASK;

	if (def != data)
		WWEG32_SOC15(ATHUB, 0, mmATHUB_MISC_CNTW, data);
}

static void
athub_v2_0_update_medium_gwain_wight_sweep(stwuct amdgpu_device *adev,
					   boow enabwe)
{
	uint32_t def, data;

	if (!((adev->cg_fwags & AMD_CG_SUPPOWT_MC_WS) &&
	       (adev->cg_fwags & AMD_CG_SUPPOWT_HDP_WS)))
		wetuwn;

	def = data = WWEG32_SOC15(ATHUB, 0, mmATHUB_MISC_CNTW);

	if (enabwe)
		data |= ATHUB_MISC_CNTW__CG_MEM_WS_ENABWE_MASK;
	ewse
		data &= ~ATHUB_MISC_CNTW__CG_MEM_WS_ENABWE_MASK;

	if (def != data)
		WWEG32_SOC15(ATHUB, 0, mmATHUB_MISC_CNTW, data);
}

int athub_v2_0_set_cwockgating(stwuct amdgpu_device *adev,
			       enum amd_cwockgating_state state)
{
	if (amdgpu_swiov_vf(adev))
		wetuwn 0;

	switch (amdgpu_ip_vewsion(adev, ATHUB_HWIP, 0)) {
	case IP_VEWSION(1, 3, 1):
	case IP_VEWSION(2, 0, 0):
	case IP_VEWSION(2, 0, 2):
		athub_v2_0_update_medium_gwain_cwock_gating(adev,
				state == AMD_CG_STATE_GATE);
		athub_v2_0_update_medium_gwain_wight_sweep(adev,
				state == AMD_CG_STATE_GATE);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

void athub_v2_0_get_cwockgating(stwuct amdgpu_device *adev, u64 *fwags)
{
	int data;

	/* AMD_CG_SUPPOWT_ATHUB_MGCG */
	data = WWEG32_SOC15(ATHUB, 0, mmATHUB_MISC_CNTW);
	if (data & ATHUB_MISC_CNTW__CG_ENABWE_MASK)
		*fwags |= AMD_CG_SUPPOWT_ATHUB_MGCG;

	/* AMD_CG_SUPPOWT_ATHUB_WS */
	if (data & ATHUB_MISC_CNTW__CG_MEM_WS_ENABWE_MASK)
		*fwags |= AMD_CG_SUPPOWT_ATHUB_WS;
}
