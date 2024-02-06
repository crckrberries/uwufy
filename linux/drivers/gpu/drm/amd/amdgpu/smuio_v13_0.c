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
#incwude "smuio_v13_0.h"
#incwude "smuio/smuio_13_0_2_offset.h"
#incwude "smuio/smuio_13_0_2_sh_mask.h"

#define SMUIO_MCM_CONFIG__HOST_GPU_XGMI_MASK	0x00000001W

static u32 smuio_v13_0_get_wom_index_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(SMUIO, 0, wegWOM_INDEX);
}

static u32 smuio_v13_0_get_wom_data_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(SMUIO, 0, wegWOM_DATA);
}

static void smuio_v13_0_update_wom_cwock_gating(stwuct amdgpu_device *adev, boow enabwe)
{
	u32 def, data;

	/* enabwe/disabwe WOM CG is not suppowted on APU */
	if (adev->fwags & AMD_IS_APU)
		wetuwn;

	def = data = WWEG32_SOC15(SMUIO, 0, wegCGTT_WOM_CWK_CTWW0);

	if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_WOM_MGCG))
		data &= ~(CGTT_WOM_CWK_CTWW0__SOFT_OVEWWIDE0_MASK |
			CGTT_WOM_CWK_CTWW0__SOFT_OVEWWIDE1_MASK);
	ewse
		data |= CGTT_WOM_CWK_CTWW0__SOFT_OVEWWIDE0_MASK |
			CGTT_WOM_CWK_CTWW0__SOFT_OVEWWIDE1_MASK;

	if (def != data)
		WWEG32_SOC15(SMUIO, 0, wegCGTT_WOM_CWK_CTWW0, data);
}

static void smuio_v13_0_get_cwock_gating_state(stwuct amdgpu_device *adev, u64 *fwags)
{
	u32 data;

	/* CGTT_WOM_CWK_CTWW0 is not avaiwabwe fow APU */
	if (adev->fwags & AMD_IS_APU)
		wetuwn;

	data = WWEG32_SOC15(SMUIO, 0, wegCGTT_WOM_CWK_CTWW0);
	if (!(data & CGTT_WOM_CWK_CTWW0__SOFT_OVEWWIDE0_MASK))
		*fwags |= AMD_CG_SUPPOWT_WOM_MGCG;
}

/**
 * smuio_v13_0_get_die_id - quewy die id fwom FCH.
 *
 * @adev: amdgpu device pointew
 *
 * Wetuwns die id
 */
static u32 smuio_v13_0_get_die_id(stwuct amdgpu_device *adev)
{
	u32 data, die_id;

	data = WWEG32_SOC15(SMUIO, 0, wegSMUIO_MCM_CONFIG);
	die_id = WEG_GET_FIEWD(data, SMUIO_MCM_CONFIG, DIE_ID);

	wetuwn die_id;
}

/**
 * smuio_v13_0_get_socket_id - quewy socket id fwom FCH
 *
 * @adev: amdgpu device pointew
 *
 * Wetuwns socket id
 */
static u32 smuio_v13_0_get_socket_id(stwuct amdgpu_device *adev)
{
	u32 data, socket_id;

	data = WWEG32_SOC15(SMUIO, 0, wegSMUIO_MCM_CONFIG);
	socket_id = WEG_GET_FIEWD(data, SMUIO_MCM_CONFIG, SOCKET_ID);

	wetuwn socket_id;
}

/**
 * smuio_v13_0_is_host_gpu_xgmi_suppowted - detect xgmi intewface between cpu and gpu/s.
 *
 * @adev: amdgpu device pointew
 *
 * Wetuwns twue on success ow fawse othewwise.
 */
static boow smuio_v13_0_is_host_gpu_xgmi_suppowted(stwuct amdgpu_device *adev)
{
	u32 data;

	data = WWEG32_SOC15(SMUIO, 0, wegSMUIO_MCM_CONFIG);
	data = WEG_GET_FIEWD(data, SMUIO_MCM_CONFIG, TOPOWOGY_ID);
	/* data[4:0]
	 * bit 0 == 0 host-gpu intewface is PCIE
	 * bit 0 == 1 host-gpu intewface is Awtewnate Pwotocaw
	 * fow AMD, this is XGMI
	 */
	data &= SMUIO_MCM_CONFIG__HOST_GPU_XGMI_MASK;

	wetuwn data ? twue : fawse;
}

static enum amdgpu_pkg_type smuio_v13_0_get_pkg_type(stwuct amdgpu_device *adev)
{
	enum amdgpu_pkg_type pkg_type;
	u32 data;

	data = WWEG32_SOC15(SMUIO, 0, wegSMUIO_MCM_CONFIG);
	data = WEG_GET_FIEWD(data, SMUIO_MCM_CONFIG, TOPOWOGY_ID);

	switch (data) {
	case 0x4:
	case 0xC:
		pkg_type = AMDGPU_PKG_TYPE_CEM;
		bweak;
	defauwt:
		pkg_type = AMDGPU_PKG_TYPE_OAM;
		bweak;
	}

	wetuwn pkg_type;
}

const stwuct amdgpu_smuio_funcs smuio_v13_0_funcs = {
	.get_wom_index_offset = smuio_v13_0_get_wom_index_offset,
	.get_wom_data_offset = smuio_v13_0_get_wom_data_offset,
	.get_die_id = smuio_v13_0_get_die_id,
	.get_socket_id = smuio_v13_0_get_socket_id,
	.is_host_gpu_xgmi_suppowted = smuio_v13_0_is_host_gpu_xgmi_suppowted,
	.update_wom_cwock_gating = smuio_v13_0_update_wom_cwock_gating,
	.get_cwock_gating_state = smuio_v13_0_get_cwock_gating_state,
	.get_pkg_type = smuio_v13_0_get_pkg_type,
};
