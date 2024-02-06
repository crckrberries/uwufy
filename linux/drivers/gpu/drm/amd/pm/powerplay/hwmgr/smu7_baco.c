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
#incwude "smu7_baco.h"
#incwude "tonga_baco.h"
#incwude "fiji_baco.h"
#incwude "powawis_baco.h"
#incwude "ci_baco.h"

#incwude "bif/bif_5_0_d.h"
#incwude "bif/bif_5_0_sh_mask.h"

#incwude "smu/smu_7_1_2_d.h"
#incwude "smu/smu_7_1_2_sh_mask.h"

boow smu7_baco_get_capabiwity(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)(hwmgw->adev);
	uint32_t weg;

	if (!phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_BACO))
		wetuwn 0;

	weg = WWEG32(mmCC_BIF_BX_FUSESTWAP0);

	if (weg & CC_BIF_BX_FUSESTWAP0__STWAP_BIF_PX_CAPABWE_MASK)
		wetuwn twue;

	wetuwn fawse;
}

int smu7_baco_get_state(stwuct pp_hwmgw *hwmgw, enum BACO_STATE *state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)(hwmgw->adev);
	uint32_t weg;

	weg = WWEG32(mmBACO_CNTW);

	if (weg & BACO_CNTW__BACO_MODE_MASK)
		/* gfx has awweady entewed BACO state */
		*state = BACO_STATE_IN;
	ewse
		*state = BACO_STATE_OUT;
	wetuwn 0;
}

int smu7_baco_set_state(stwuct pp_hwmgw *hwmgw, enum BACO_STATE state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)(hwmgw->adev);

	switch (adev->asic_type) {
	case CHIP_TOPAZ:
	case CHIP_TONGA:
		wetuwn tonga_baco_set_state(hwmgw, state);
	case CHIP_FIJI:
		wetuwn fiji_baco_set_state(hwmgw, state);
	case CHIP_POWAWIS10:
	case CHIP_POWAWIS11:
	case CHIP_POWAWIS12:
	case CHIP_VEGAM:
		wetuwn powawis_baco_set_state(hwmgw, state);
#ifdef CONFIG_DWM_AMDGPU_CIK
	case CHIP_BONAIWE:
	case CHIP_HAWAII:
		wetuwn ci_baco_set_state(hwmgw, state);
#endif
	defauwt:
		wetuwn -EINVAW;
	}
}
