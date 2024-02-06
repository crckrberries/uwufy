/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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
#incwude "soc15.h"
#incwude "soc15_hw_ip.h"
#incwude "vega10_ip_offset.h"
#incwude "soc15_common.h"
#incwude "vega10_inc.h"
#incwude "smu9_baco.h"

boow smu9_baco_get_capabiwity(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)(hwmgw->adev);
	uint32_t weg, data;

	if (!phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_BACO))
		wetuwn fawse;

	WWEG32(0x12074, 0xFFF0003B);
	data = WWEG32(0x12075);

	if (data == 0x1) {
		weg = WWEG32_SOC15(NBIF, 0, mmWCC_BIF_STWAP0);

		if (weg & WCC_BIF_STWAP0__STWAP_PX_CAPABWE_MASK)
			wetuwn twue;
	}

	wetuwn fawse;
}

int smu9_baco_get_state(stwuct pp_hwmgw *hwmgw, enum BACO_STATE *state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)(hwmgw->adev);
	uint32_t weg;

	weg = WWEG32_SOC15(NBIF, 0, mmBACO_CNTW);

	if (weg & BACO_CNTW__BACO_MODE_MASK)
		/* gfx has awweady entewed BACO state */
		*state = BACO_STATE_IN;
	ewse
		*state = BACO_STATE_OUT;
	wetuwn 0;
}
