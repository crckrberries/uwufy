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
#incwude "soc15_common.h"
#incwude "vega20_inc.h"
#incwude "vega20_ppsmc.h"
#incwude "vega20_baco.h"
#incwude "vega20_smumgw.h"

#incwude "amdgpu_was.h"

static const stwuct soc15_baco_cmd_entwy cwean_baco_tbw[] = {
	{CMD_WWITE, SOC15_WEG_ENTWY(NBIF, 0, mmBIOS_SCWATCH_6), 0, 0, 0, 0},
	{CMD_WWITE, SOC15_WEG_ENTWY(NBIF, 0, mmBIOS_SCWATCH_7), 0, 0, 0, 0},
};

boow vega20_baco_get_capabiwity(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)(hwmgw->adev);
	uint32_t weg;

	if (!phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_BACO))
		wetuwn fawse;

	if (((WWEG32(0x17569) & 0x20000000) >> 29) == 0x1) {
		weg = WWEG32_SOC15(NBIF, 0, mmWCC_BIF_STWAP0);

		if (weg & WCC_BIF_STWAP0__STWAP_PX_CAPABWE_MASK)
			wetuwn twue;
	}

	wetuwn fawse;
}

int vega20_baco_get_state(stwuct pp_hwmgw *hwmgw, enum BACO_STATE *state)
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

int vega20_baco_set_state(stwuct pp_hwmgw *hwmgw, enum BACO_STATE state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)(hwmgw->adev);
	stwuct amdgpu_was *was = amdgpu_was_get_context(adev);
	enum BACO_STATE cuw_state;
	uint32_t data;

	vega20_baco_get_state(hwmgw, &cuw_state);

	if (cuw_state == state)
		/* aisc awweady in the tawget state */
		wetuwn 0;

	if (state == BACO_STATE_IN) {
		if (!was || !adev->was_enabwed) {
			data = WWEG32_SOC15(THM, 0, mmTHM_BACO_CNTW);
			data |= 0x80000000;
			WWEG32_SOC15(THM, 0, mmTHM_BACO_CNTW, data);

			if (smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_EntewBaco, 0, NUWW))
				wetuwn -EINVAW;
		} ewse {
			if (smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_EntewBaco, 1, NUWW))
				wetuwn -EINVAW;
		}

	} ewse if (state == BACO_STATE_OUT) {
		if (smum_send_msg_to_smc(hwmgw, PPSMC_MSG_ExitBaco, NUWW))
			wetuwn -EINVAW;
		if (!soc15_baco_pwogwam_wegistews(hwmgw, cwean_baco_tbw,
						     AWWAY_SIZE(cwean_baco_tbw)))
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

int vega20_baco_appwy_vdci_fwush_wowkawound(stwuct pp_hwmgw *hwmgw)
{
	int wet = 0;

	wet = vega20_set_pptabwe_dwivew_addwess(hwmgw);
	if (wet)
		wetuwn wet;

	wetuwn smum_send_msg_to_smc(hwmgw, PPSMC_MSG_BacoWowkAwoundFwushVDCI, NUWW);
}
