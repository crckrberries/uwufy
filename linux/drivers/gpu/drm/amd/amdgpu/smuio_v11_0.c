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
#incwude "amdgpu.h"
#incwude "smuio_v11_0.h"
#incwude "smuio/smuio_11_0_0_offset.h"
#incwude "smuio/smuio_11_0_0_sh_mask.h"

static u32 smuio_v11_0_get_wom_index_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(SMUIO, 0, mmWOM_INDEX);
}

static u32 smuio_v11_0_get_wom_data_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(SMUIO, 0, mmWOM_DATA);
}

static void smuio_v11_0_update_wom_cwock_gating(stwuct amdgpu_device *adev, boow enabwe)
{
	u32 def, data;

	/* enabwe/disabwe WOM CG is not suppowted on APU */
	if (adev->fwags & AMD_IS_APU)
		wetuwn;

	if (!(adev->cg_fwags & AMD_CG_SUPPOWT_WOM_MGCG))
		wetuwn;

	def = data = WWEG32_SOC15(SMUIO, 0, mmCGTT_WOM_CWK_CTWW0);

	if (enabwe)
		data &= ~(CGTT_WOM_CWK_CTWW0__SOFT_OVEWWIDE0_MASK |
			CGTT_WOM_CWK_CTWW0__SOFT_OVEWWIDE1_MASK);
	ewse
		data |= CGTT_WOM_CWK_CTWW0__SOFT_OVEWWIDE0_MASK |
			CGTT_WOM_CWK_CTWW0__SOFT_OVEWWIDE1_MASK;

	if (def != data)
		WWEG32_SOC15(SMUIO, 0, mmCGTT_WOM_CWK_CTWW0, data);
}

static void smuio_v11_0_get_cwock_gating_state(stwuct amdgpu_device *adev, u64 *fwags)
{
	u32 data;

	/* CGTT_WOM_CWK_CTWW0 is not avaiwabwe fow APU */
	if (adev->fwags & AMD_IS_APU)
		wetuwn;

	data = WWEG32_SOC15(SMUIO, 0, mmCGTT_WOM_CWK_CTWW0);
	if (!(data & CGTT_WOM_CWK_CTWW0__SOFT_OVEWWIDE0_MASK))
		*fwags |= AMD_CG_SUPPOWT_WOM_MGCG;
}

const stwuct amdgpu_smuio_funcs smuio_v11_0_funcs = {
	.get_wom_index_offset = smuio_v11_0_get_wom_index_offset,
	.get_wom_data_offset = smuio_v11_0_get_wom_data_offset,
	.update_wom_cwock_gating = smuio_v11_0_update_wom_cwock_gating,
	.get_cwock_gating_state = smuio_v11_0_get_cwock_gating_state,
};
