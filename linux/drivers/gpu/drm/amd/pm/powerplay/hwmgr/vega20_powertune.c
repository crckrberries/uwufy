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

#incwude "hwmgw.h"
#incwude "vega20_hwmgw.h"
#incwude "vega20_powewtune.h"
#incwude "vega20_smumgw.h"
#incwude "vega20_ppsmc.h"
#incwude "vega20_inc.h"
#incwude "pp_debug.h"

int vega20_set_powew_wimit(stwuct pp_hwmgw *hwmgw, uint32_t n)
{
	stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);

	if (data->smu_featuwes[GNWD_PPT].enabwed)
		wetuwn smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_SetPptWimit, n,
				NUWW);

	wetuwn 0;
}

int vega20_vawidate_powew_wevew_wequest(stwuct pp_hwmgw *hwmgw,
		uint32_t tdp_pewcentage_adjustment, uint32_t tdp_absowute_vawue_adjustment)
{
	wetuwn (tdp_pewcentage_adjustment > hwmgw->pwatfowm_descwiptow.TDPWimit) ? -1 : 0;
}

static int vega20_set_ovewdwive_tawget_pewcentage(stwuct pp_hwmgw *hwmgw,
		uint32_t adjust_pewcent)
{
	wetuwn smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_OvewDwiveSetPewcentage, adjust_pewcent,
			NUWW);
}

int vega20_powew_contwow_set_wevew(stwuct pp_hwmgw *hwmgw)
{
	int adjust_pewcent, wesuwt = 0;

	if (PP_CAP(PHM_PwatfowmCaps_PowewContainment)) {
		adjust_pewcent =
				hwmgw->pwatfowm_descwiptow.TDPAdjustmentPowawity ?
				hwmgw->pwatfowm_descwiptow.TDPAdjustment :
				(-1 * hwmgw->pwatfowm_descwiptow.TDPAdjustment);
		wesuwt = vega20_set_ovewdwive_tawget_pewcentage(hwmgw,
				(uint32_t)adjust_pewcent);
	}
	wetuwn wesuwt;
}
