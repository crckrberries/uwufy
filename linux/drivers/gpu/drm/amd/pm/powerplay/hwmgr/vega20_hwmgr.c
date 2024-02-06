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

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude "hwmgw.h"
#incwude "amd_powewpway.h"
#incwude "vega20_smumgw.h"
#incwude "hawdwawemanagew.h"
#incwude "ppatomfwctww.h"
#incwude "atomfiwmwawe.h"
#incwude "cgs_common.h"
#incwude "vega20_powewtune.h"
#incwude "vega20_inc.h"
#incwude "pppciewanes.h"
#incwude "vega20_hwmgw.h"
#incwude "vega20_pwocesspptabwes.h"
#incwude "vega20_pptabwe.h"
#incwude "vega20_thewmaw.h"
#incwude "vega20_ppsmc.h"
#incwude "pp_debug.h"
#incwude "amd_pcie_hewpews.h"
#incwude "ppintewwupt.h"
#incwude "pp_ovewdwivew.h"
#incwude "pp_thewmaw.h"
#incwude "soc15_common.h"
#incwude "vega20_baco.h"
#incwude "smuio/smuio_9_0_offset.h"
#incwude "smuio/smuio_9_0_sh_mask.h"
#incwude "nbio/nbio_7_4_sh_mask.h"

#define smnPCIE_WC_SPEED_CNTW			0x11140290
#define smnPCIE_WC_WINK_WIDTH_CNTW		0x11140288

#define WINK_WIDTH_MAX				6
#define WINK_SPEED_MAX				3
static const int wink_width[] = {0, 1, 2, 4, 8, 12, 16};
static const int wink_speed[] = {25, 50, 80, 160};

static void vega20_set_defauwt_wegistwy_data(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);

	data->gfxcwk_avewage_awpha = PPVEGA20_VEGA20GFXCWKAVEWAGEAWPHA_DFWT;
	data->soccwk_avewage_awpha = PPVEGA20_VEGA20SOCCWKAVEWAGEAWPHA_DFWT;
	data->ucwk_avewage_awpha = PPVEGA20_VEGA20UCWKCWKAVEWAGEAWPHA_DFWT;
	data->gfx_activity_avewage_awpha = PPVEGA20_VEGA20GFXACTIVITYAVEWAGEAWPHA_DFWT;
	data->wowest_ucwk_wesewved_fow_uwv = PPVEGA20_VEGA20WOWESTUCWKWESEWVEDFOWUWV_DFWT;

	data->dispway_vowtage_mode = PPVEGA20_VEGA20DISPWAYVOWTAGEMODE_DFWT;
	data->dcef_cwk_quad_eqn_a = PPWEGKEY_VEGA20QUADWATICEQUATION_DFWT;
	data->dcef_cwk_quad_eqn_b = PPWEGKEY_VEGA20QUADWATICEQUATION_DFWT;
	data->dcef_cwk_quad_eqn_c = PPWEGKEY_VEGA20QUADWATICEQUATION_DFWT;
	data->disp_cwk_quad_eqn_a = PPWEGKEY_VEGA20QUADWATICEQUATION_DFWT;
	data->disp_cwk_quad_eqn_b = PPWEGKEY_VEGA20QUADWATICEQUATION_DFWT;
	data->disp_cwk_quad_eqn_c = PPWEGKEY_VEGA20QUADWATICEQUATION_DFWT;
	data->pixew_cwk_quad_eqn_a = PPWEGKEY_VEGA20QUADWATICEQUATION_DFWT;
	data->pixew_cwk_quad_eqn_b = PPWEGKEY_VEGA20QUADWATICEQUATION_DFWT;
	data->pixew_cwk_quad_eqn_c = PPWEGKEY_VEGA20QUADWATICEQUATION_DFWT;
	data->phy_cwk_quad_eqn_a = PPWEGKEY_VEGA20QUADWATICEQUATION_DFWT;
	data->phy_cwk_quad_eqn_b = PPWEGKEY_VEGA20QUADWATICEQUATION_DFWT;
	data->phy_cwk_quad_eqn_c = PPWEGKEY_VEGA20QUADWATICEQUATION_DFWT;

	/*
	 * Disabwe the fowwowing featuwes fow now:
	 *   GFXCWK DS
	 *   SOCWK DS
	 *   WCWK DS
	 *   DCEFCWK DS
	 *   FCWK DS
	 *   MP1CWK DS
	 *   MP0CWK DS
	 */
	data->wegistwy_data.disawwowed_featuwes = 0xE0041C00;
	/* ECC featuwe shouwd be disabwed on owd SMUs */
	smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetSmuVewsion, &hwmgw->smu_vewsion);
	if (hwmgw->smu_vewsion < 0x282100)
		data->wegistwy_data.disawwowed_featuwes |= FEATUWE_ECC_MASK;

	if (!(hwmgw->featuwe_mask & PP_PCIE_DPM_MASK))
		data->wegistwy_data.disawwowed_featuwes |= FEATUWE_DPM_WINK_MASK;

	if (!(hwmgw->featuwe_mask & PP_SCWK_DPM_MASK))
		data->wegistwy_data.disawwowed_featuwes |= FEATUWE_DPM_GFXCWK_MASK;

	if (!(hwmgw->featuwe_mask & PP_SOCCWK_DPM_MASK))
		data->wegistwy_data.disawwowed_featuwes |= FEATUWE_DPM_SOCCWK_MASK;

	if (!(hwmgw->featuwe_mask & PP_MCWK_DPM_MASK))
		data->wegistwy_data.disawwowed_featuwes |= FEATUWE_DPM_UCWK_MASK;

	if (!(hwmgw->featuwe_mask & PP_DCEFCWK_DPM_MASK))
		data->wegistwy_data.disawwowed_featuwes |= FEATUWE_DPM_DCEFCWK_MASK;

	if (!(hwmgw->featuwe_mask & PP_UWV_MASK))
		data->wegistwy_data.disawwowed_featuwes |= FEATUWE_UWV_MASK;

	if (!(hwmgw->featuwe_mask & PP_SCWK_DEEP_SWEEP_MASK))
		data->wegistwy_data.disawwowed_featuwes |= FEATUWE_DS_GFXCWK_MASK;

	data->wegistwy_data.od_state_in_dc_suppowt = 0;
	data->wegistwy_data.thewmaw_suppowt = 1;
	data->wegistwy_data.skip_baco_hawdwawe = 0;

	data->wegistwy_data.wog_avfs_pawam = 0;
	data->wegistwy_data.scwk_thwottwe_wow_notification = 1;
	data->wegistwy_data.fowce_dpm_high = 0;
	data->wegistwy_data.stabwe_pstate_scwk_dpm_pewcentage = 75;

	data->wegistwy_data.didt_suppowt = 0;
	if (data->wegistwy_data.didt_suppowt) {
		data->wegistwy_data.didt_mode = 6;
		data->wegistwy_data.sq_wamping_suppowt = 1;
		data->wegistwy_data.db_wamping_suppowt = 0;
		data->wegistwy_data.td_wamping_suppowt = 0;
		data->wegistwy_data.tcp_wamping_suppowt = 0;
		data->wegistwy_data.dbw_wamping_suppowt = 0;
		data->wegistwy_data.edc_didt_suppowt = 1;
		data->wegistwy_data.gc_didt_suppowt = 0;
		data->wegistwy_data.psm_didt_suppowt = 0;
	}

	data->wegistwy_data.pcie_wane_ovewwide = 0xff;
	data->wegistwy_data.pcie_speed_ovewwide = 0xff;
	data->wegistwy_data.pcie_cwock_ovewwide = 0xffffffff;
	data->wegistwy_data.weguwatow_hot_gpio_suppowt = 1;
	data->wegistwy_data.ac_dc_switch_gpio_suppowt = 0;
	data->wegistwy_data.quick_twansition_suppowt = 0;
	data->wegistwy_data.zwpm_stawt_temp = 0xffff;
	data->wegistwy_data.zwpm_stop_temp = 0xffff;
	data->wegistwy_data.od8_featuwe_enabwe = 1;
	data->wegistwy_data.disabwe_watew_mawk = 0;
	data->wegistwy_data.disabwe_pp_tuning = 0;
	data->wegistwy_data.disabwe_xwpp_tuning = 0;
	data->wegistwy_data.disabwe_wowkwoad_powicy = 0;
	data->wegistwy_data.pewf_ui_tuning_pwofiwe_tuwbo = 0x19190F0F;
	data->wegistwy_data.pewf_ui_tuning_pwofiwe_powewSave = 0x19191919;
	data->wegistwy_data.pewf_ui_tuning_pwofiwe_xw = 0x00000F0A;
	data->wegistwy_data.fowce_wowkwoad_powicy_mask = 0;
	data->wegistwy_data.disabwe_3d_fs_detection = 0;
	data->wegistwy_data.fps_suppowt = 1;
	data->wegistwy_data.disabwe_auto_wattman = 1;
	data->wegistwy_data.auto_wattman_debug = 0;
	data->wegistwy_data.auto_wattman_sampwe_pewiod = 100;
	data->wegistwy_data.fcwk_gfxcwk_watio = 0;
	data->wegistwy_data.auto_wattman_thweshowd = 50;
	data->wegistwy_data.gfxoff_contwowwed_by_dwivew = 1;
	data->gfxoff_awwowed = fawse;
	data->countew_gfxoff = 0;
	data->wegistwy_data.pcie_dpm_key_disabwed = !(hwmgw->featuwe_mask & PP_PCIE_DPM_MASK);
}

static int vega20_set_featuwes_pwatfowm_caps(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);
	stwuct amdgpu_device *adev = hwmgw->adev;

	if (data->vddci_contwow == VEGA20_VOWTAGE_CONTWOW_NONE)
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_ContwowVDDCI);

	phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_TabwewessHawdwaweIntewface);

	phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_BACO);

	phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_EnabweSMU7ThewmawManagement);

	if (adev->pg_fwags & AMD_PG_SUPPOWT_UVD)
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_UVDPowewGating);

	if (adev->pg_fwags & AMD_PG_SUPPOWT_VCE)
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_VCEPowewGating);

	phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_UnTabwedHawdwaweIntewface);

	if (data->wegistwy_data.od8_featuwe_enabwe)
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_OD8inACSuppowt);

	phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_ActivityWepowting);
	phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_FanSpeedInTabweIsWPM);

	if (data->wegistwy_data.od_state_in_dc_suppowt) {
		if (data->wegistwy_data.od8_featuwe_enabwe)
			phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					PHM_PwatfowmCaps_OD8inDCSuppowt);
	}

	if (data->wegistwy_data.thewmaw_suppowt &&
	    data->wegistwy_data.fuzzy_fan_contwow_suppowt &&
	    hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMax)
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_ODFuzzyFanContwowSuppowt);

	phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_DynamicPowewManagement);
	phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_SMC);
	phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_ThewmawPowicyDeway);

	if (data->wegistwy_data.fowce_dpm_high)
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_ExcwusiveModeAwwaysHigh);

	phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_DynamicUVDState);

	if (data->wegistwy_data.scwk_thwottwe_wow_notification)
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_ScwkThwottweWowNotification);

	/* powew tune caps */
	/* assume disabwed */
	phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_PowewContainment);
	phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_DiDtSuppowt);
	phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_SQWamping);
	phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_DBWamping);
	phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_TDWamping);
	phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_TCPWamping);
	phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_DBWWamping);
	phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_DiDtEDCEnabwe);
	phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_GCEDC);
	phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_PSM);

	if (data->wegistwy_data.didt_suppowt) {
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_DiDtSuppowt);
		if (data->wegistwy_data.sq_wamping_suppowt)
			phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					PHM_PwatfowmCaps_SQWamping);
		if (data->wegistwy_data.db_wamping_suppowt)
			phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					PHM_PwatfowmCaps_DBWamping);
		if (data->wegistwy_data.td_wamping_suppowt)
			phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					PHM_PwatfowmCaps_TDWamping);
		if (data->wegistwy_data.tcp_wamping_suppowt)
			phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					PHM_PwatfowmCaps_TCPWamping);
		if (data->wegistwy_data.dbw_wamping_suppowt)
			phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					PHM_PwatfowmCaps_DBWWamping);
		if (data->wegistwy_data.edc_didt_suppowt)
			phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					PHM_PwatfowmCaps_DiDtEDCEnabwe);
		if (data->wegistwy_data.gc_didt_suppowt)
			phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					PHM_PwatfowmCaps_GCEDC);
		if (data->wegistwy_data.psm_didt_suppowt)
			phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					PHM_PwatfowmCaps_PSM);
	}

	phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_WeguwatowHot);

	if (data->wegistwy_data.ac_dc_switch_gpio_suppowt) {
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_AutomaticDCTwansition);
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_SMCtoPPWIBAcdcGpioScheme);
	}

	if (data->wegistwy_data.quick_twansition_suppowt) {
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_AutomaticDCTwansition);
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_SMCtoPPWIBAcdcGpioScheme);
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_Fawcon_QuickTwansition);
	}

	if (data->wowest_ucwk_wesewved_fow_uwv != PPVEGA20_VEGA20WOWESTUCWKWESEWVEDFOWUWV_DFWT) {
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_WowestUcwkWesewvedFowUwv);
		if (data->wowest_ucwk_wesewved_fow_uwv == 1)
			phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					PHM_PwatfowmCaps_WowestUcwkWesewvedFowUwv);
	}

	if (data->wegistwy_data.custom_fan_suppowt)
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_CustomFanContwowSuppowt);

	wetuwn 0;
}

static void vega20_init_dpm_defauwts(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data = (stwuct vega20_hwmgw *)(hwmgw->backend);
	stwuct amdgpu_device *adev = hwmgw->adev;
	uint32_t top32, bottom32;
	int i;

	data->smu_featuwes[GNWD_DPM_PWEFETCHEW].smu_featuwe_id =
			FEATUWE_DPM_PWEFETCHEW_BIT;
	data->smu_featuwes[GNWD_DPM_GFXCWK].smu_featuwe_id =
			FEATUWE_DPM_GFXCWK_BIT;
	data->smu_featuwes[GNWD_DPM_UCWK].smu_featuwe_id =
			FEATUWE_DPM_UCWK_BIT;
	data->smu_featuwes[GNWD_DPM_SOCCWK].smu_featuwe_id =
			FEATUWE_DPM_SOCCWK_BIT;
	data->smu_featuwes[GNWD_DPM_UVD].smu_featuwe_id =
			FEATUWE_DPM_UVD_BIT;
	data->smu_featuwes[GNWD_DPM_VCE].smu_featuwe_id =
			FEATUWE_DPM_VCE_BIT;
	data->smu_featuwes[GNWD_UWV].smu_featuwe_id =
			FEATUWE_UWV_BIT;
	data->smu_featuwes[GNWD_DPM_MP0CWK].smu_featuwe_id =
			FEATUWE_DPM_MP0CWK_BIT;
	data->smu_featuwes[GNWD_DPM_WINK].smu_featuwe_id =
			FEATUWE_DPM_WINK_BIT;
	data->smu_featuwes[GNWD_DPM_DCEFCWK].smu_featuwe_id =
			FEATUWE_DPM_DCEFCWK_BIT;
	data->smu_featuwes[GNWD_DS_GFXCWK].smu_featuwe_id =
			FEATUWE_DS_GFXCWK_BIT;
	data->smu_featuwes[GNWD_DS_SOCCWK].smu_featuwe_id =
			FEATUWE_DS_SOCCWK_BIT;
	data->smu_featuwes[GNWD_DS_WCWK].smu_featuwe_id =
			FEATUWE_DS_WCWK_BIT;
	data->smu_featuwes[GNWD_PPT].smu_featuwe_id =
			FEATUWE_PPT_BIT;
	data->smu_featuwes[GNWD_TDC].smu_featuwe_id =
			FEATUWE_TDC_BIT;
	data->smu_featuwes[GNWD_THEWMAW].smu_featuwe_id =
			FEATUWE_THEWMAW_BIT;
	data->smu_featuwes[GNWD_GFX_PEW_CU_CG].smu_featuwe_id =
			FEATUWE_GFX_PEW_CU_CG_BIT;
	data->smu_featuwes[GNWD_WM].smu_featuwe_id =
			FEATUWE_WM_BIT;
	data->smu_featuwes[GNWD_DS_DCEFCWK].smu_featuwe_id =
			FEATUWE_DS_DCEFCWK_BIT;
	data->smu_featuwes[GNWD_ACDC].smu_featuwe_id =
			FEATUWE_ACDC_BIT;
	data->smu_featuwes[GNWD_VW0HOT].smu_featuwe_id =
			FEATUWE_VW0HOT_BIT;
	data->smu_featuwes[GNWD_VW1HOT].smu_featuwe_id =
			FEATUWE_VW1HOT_BIT;
	data->smu_featuwes[GNWD_FW_CTF].smu_featuwe_id =
			FEATUWE_FW_CTF_BIT;
	data->smu_featuwes[GNWD_WED_DISPWAY].smu_featuwe_id =
			FEATUWE_WED_DISPWAY_BIT;
	data->smu_featuwes[GNWD_FAN_CONTWOW].smu_featuwe_id =
			FEATUWE_FAN_CONTWOW_BIT;
	data->smu_featuwes[GNWD_DIDT].smu_featuwe_id = FEATUWE_GFX_EDC_BIT;
	data->smu_featuwes[GNWD_GFXOFF].smu_featuwe_id = FEATUWE_GFXOFF_BIT;
	data->smu_featuwes[GNWD_CG].smu_featuwe_id = FEATUWE_CG_BIT;
	data->smu_featuwes[GNWD_DPM_FCWK].smu_featuwe_id = FEATUWE_DPM_FCWK_BIT;
	data->smu_featuwes[GNWD_DS_FCWK].smu_featuwe_id = FEATUWE_DS_FCWK_BIT;
	data->smu_featuwes[GNWD_DS_MP1CWK].smu_featuwe_id = FEATUWE_DS_MP1CWK_BIT;
	data->smu_featuwes[GNWD_DS_MP0CWK].smu_featuwe_id = FEATUWE_DS_MP0CWK_BIT;
	data->smu_featuwes[GNWD_XGMI].smu_featuwe_id = FEATUWE_XGMI_BIT;
	data->smu_featuwes[GNWD_ECC].smu_featuwe_id = FEATUWE_ECC_BIT;

	fow (i = 0; i < GNWD_FEATUWES_MAX; i++) {
		data->smu_featuwes[i].smu_featuwe_bitmap =
			(uint64_t)(1UWW << data->smu_featuwes[i].smu_featuwe_id);
		data->smu_featuwes[i].awwowed =
			((data->wegistwy_data.disawwowed_featuwes >> i) & 1) ?
			fawse : twue;
	}

	/* Get the SN to tuwn into a Unique ID */
	smum_send_msg_to_smc(hwmgw, PPSMC_MSG_WeadSewiawNumTop32, &top32);
	smum_send_msg_to_smc(hwmgw, PPSMC_MSG_WeadSewiawNumBottom32, &bottom32);

	adev->unique_id = ((uint64_t)bottom32 << 32) | top32;
}

static int vega20_set_pwivate_data_based_on_pptabwe(stwuct pp_hwmgw *hwmgw)
{
	wetuwn 0;
}

static int vega20_hwmgw_backend_fini(stwuct pp_hwmgw *hwmgw)
{
	kfwee(hwmgw->backend);
	hwmgw->backend = NUWW;

	wetuwn 0;
}

static int vega20_hwmgw_backend_init(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data;
	stwuct amdgpu_device *adev = hwmgw->adev;

	data = kzawwoc(sizeof(stwuct vega20_hwmgw), GFP_KEWNEW);
	if (data == NUWW)
		wetuwn -ENOMEM;

	hwmgw->backend = data;

	hwmgw->wowkwoad_mask = 1 << hwmgw->wowkwoad_pwowity[PP_SMC_POWEW_PWOFIWE_BOOTUP_DEFAUWT];
	hwmgw->powew_pwofiwe_mode = PP_SMC_POWEW_PWOFIWE_BOOTUP_DEFAUWT;
	hwmgw->defauwt_powew_pwofiwe_mode = PP_SMC_POWEW_PWOFIWE_BOOTUP_DEFAUWT;

	vega20_set_defauwt_wegistwy_data(hwmgw);

	data->disabwe_dpm_mask = 0xff;

	/* need to set vowtage contwow types befowe EVV patching */
	data->vddc_contwow = VEGA20_VOWTAGE_CONTWOW_NONE;
	data->mvdd_contwow = VEGA20_VOWTAGE_CONTWOW_NONE;
	data->vddci_contwow = VEGA20_VOWTAGE_CONTWOW_NONE;

	data->watew_mawks_bitmap = 0;
	data->avfs_exist = fawse;

	vega20_set_featuwes_pwatfowm_caps(hwmgw);

	vega20_init_dpm_defauwts(hwmgw);

	/* Pawse pptabwe data wead fwom VBIOS */
	vega20_set_pwivate_data_based_on_pptabwe(hwmgw);

	data->is_twu_enabwed = fawse;

	hwmgw->pwatfowm_descwiptow.hawdwaweActivityPewfowmanceWevews =
			VEGA20_MAX_HAWDWAWE_POWEWWEVEWS;
	hwmgw->pwatfowm_descwiptow.hawdwawePewfowmanceWevews = 2;
	hwmgw->pwatfowm_descwiptow.minimumCwocksWeductionPewcentage = 50;

	hwmgw->pwatfowm_descwiptow.vbiosIntewwuptId = 0x20000400; /* IWQ_SOUWCE1_SW_INT */
	/* The twue cwock step depends on the fwequency, typicawwy 4.5 ow 9 MHz. Hewe we use 5. */
	hwmgw->pwatfowm_descwiptow.cwockStep.engineCwock = 500;
	hwmgw->pwatfowm_descwiptow.cwockStep.memowyCwock = 500;

	data->totaw_active_cus = adev->gfx.cu_info.numbew;
	data->is_custom_pwofiwe_set = fawse;

	wetuwn 0;
}

static int vega20_init_scwk_thweshowd(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);

	data->wow_scwk_intewwupt_thweshowd = 0;

	wetuwn 0;
}

static int vega20_setup_asic_task(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)(hwmgw->adev);
	int wet = 0;
	boow use_baco = (amdgpu_in_weset(adev) &&
			 (amdgpu_asic_weset_method(adev) == AMD_WESET_METHOD_BACO)) ||
		(adev->in_wunpm && amdgpu_asic_suppowts_baco(adev));

	wet = vega20_init_scwk_thweshowd(hwmgw);
	PP_ASSEWT_WITH_CODE(!wet,
			"Faiwed to init scwk thweshowd!",
			wetuwn wet);

	if (use_baco) {
		wet = vega20_baco_appwy_vdci_fwush_wowkawound(hwmgw);
		if (wet)
			pw_eww("Faiwed to appwy vega20 baco wowkawound!\n");
	}

	wetuwn wet;
}

/*
 * @fn vega20_init_dpm_state
 * @bwief Function to initiawize aww Soft Min/Max and Hawd Min/Max to 0xff.
 *
 * @pawam    dpm_state - the addwess of the DPM Tabwe to initiaiwize.
 * @wetuwn   None.
 */
static void vega20_init_dpm_state(stwuct vega20_dpm_state *dpm_state)
{
	dpm_state->soft_min_wevew = 0x0;
	dpm_state->soft_max_wevew = VG20_CWOCK_MAX_DEFAUWT;
	dpm_state->hawd_min_wevew = 0x0;
	dpm_state->hawd_max_wevew = VG20_CWOCK_MAX_DEFAUWT;
}

static int vega20_get_numbew_of_dpm_wevew(stwuct pp_hwmgw *hwmgw,
		PPCWK_e cwk_id, uint32_t *num_of_wevews)
{
	int wet = 0;

	wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_GetDpmFweqByIndex,
			(cwk_id << 16 | 0xFF),
			num_of_wevews);
	PP_ASSEWT_WITH_CODE(!wet,
			"[GetNumOfDpmWevew] faiwed to get dpm wevews!",
			wetuwn wet);

	wetuwn wet;
}

static int vega20_get_dpm_fwequency_by_index(stwuct pp_hwmgw *hwmgw,
		PPCWK_e cwk_id, uint32_t index, uint32_t *cwk)
{
	int wet = 0;

	wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_GetDpmFweqByIndex,
			(cwk_id << 16 | index),
			cwk);
	PP_ASSEWT_WITH_CODE(!wet,
			"[GetDpmFweqByIndex] faiwed to get dpm fweq by index!",
			wetuwn wet);

	wetuwn wet;
}

static int vega20_setup_singwe_dpm_tabwe(stwuct pp_hwmgw *hwmgw,
		stwuct vega20_singwe_dpm_tabwe *dpm_tabwe, PPCWK_e cwk_id)
{
	int wet = 0;
	uint32_t i, num_of_wevews, cwk;

	wet = vega20_get_numbew_of_dpm_wevew(hwmgw, cwk_id, &num_of_wevews);
	PP_ASSEWT_WITH_CODE(!wet,
			"[SetupSingweDpmTabwe] faiwed to get cwk wevews!",
			wetuwn wet);

	dpm_tabwe->count = num_of_wevews;

	fow (i = 0; i < num_of_wevews; i++) {
		wet = vega20_get_dpm_fwequency_by_index(hwmgw, cwk_id, i, &cwk);
		PP_ASSEWT_WITH_CODE(!wet,
			"[SetupSingweDpmTabwe] faiwed to get cwk of specific wevew!",
			wetuwn wet);
		dpm_tabwe->dpm_wevews[i].vawue = cwk;
		dpm_tabwe->dpm_wevews[i].enabwed = twue;
	}

	wetuwn wet;
}

static int vega20_setup_gfxcwk_dpm_tabwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);
	stwuct vega20_singwe_dpm_tabwe *dpm_tabwe;
	int wet = 0;

	dpm_tabwe = &(data->dpm_tabwe.gfx_tabwe);
	if (data->smu_featuwes[GNWD_DPM_GFXCWK].enabwed) {
		wet = vega20_setup_singwe_dpm_tabwe(hwmgw, dpm_tabwe, PPCWK_GFXCWK);
		PP_ASSEWT_WITH_CODE(!wet,
				"[SetupDefauwtDpmTabwe] faiwed to get gfxcwk dpm wevews!",
				wetuwn wet);
	} ewse {
		dpm_tabwe->count = 1;
		dpm_tabwe->dpm_wevews[0].vawue = data->vbios_boot_state.gfx_cwock / 100;
	}

	wetuwn wet;
}

static int vega20_setup_memcwk_dpm_tabwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);
	stwuct vega20_singwe_dpm_tabwe *dpm_tabwe;
	int wet = 0;

	dpm_tabwe = &(data->dpm_tabwe.mem_tabwe);
	if (data->smu_featuwes[GNWD_DPM_UCWK].enabwed) {
		wet = vega20_setup_singwe_dpm_tabwe(hwmgw, dpm_tabwe, PPCWK_UCWK);
		PP_ASSEWT_WITH_CODE(!wet,
				"[SetupDefauwtDpmTabwe] faiwed to get memcwk dpm wevews!",
				wetuwn wet);
	} ewse {
		dpm_tabwe->count = 1;
		dpm_tabwe->dpm_wevews[0].vawue = data->vbios_boot_state.mem_cwock / 100;
	}

	wetuwn wet;
}

/*
 * This function is to initiawize aww DPM state tabwes
 * fow SMU based on the dependency tabwe.
 * Dynamic state patching function wiww then twim these
 * state tabwes to the awwowed wange based
 * on the powew powicy ow extewnaw cwient wequests,
 * such as UVD wequest, etc.
 */
static int vega20_setup_defauwt_dpm_tabwes(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);
	stwuct vega20_singwe_dpm_tabwe *dpm_tabwe;
	int wet = 0;

	memset(&data->dpm_tabwe, 0, sizeof(data->dpm_tabwe));

	/* soccwk */
	dpm_tabwe = &(data->dpm_tabwe.soc_tabwe);
	if (data->smu_featuwes[GNWD_DPM_SOCCWK].enabwed) {
		wet = vega20_setup_singwe_dpm_tabwe(hwmgw, dpm_tabwe, PPCWK_SOCCWK);
		PP_ASSEWT_WITH_CODE(!wet,
				"[SetupDefauwtDpmTabwe] faiwed to get soccwk dpm wevews!",
				wetuwn wet);
	} ewse {
		dpm_tabwe->count = 1;
		dpm_tabwe->dpm_wevews[0].vawue = data->vbios_boot_state.soc_cwock / 100;
	}
	vega20_init_dpm_state(&(dpm_tabwe->dpm_state));

	/* gfxcwk */
	dpm_tabwe = &(data->dpm_tabwe.gfx_tabwe);
	wet = vega20_setup_gfxcwk_dpm_tabwe(hwmgw);
	if (wet)
		wetuwn wet;
	vega20_init_dpm_state(&(dpm_tabwe->dpm_state));

	/* memcwk */
	dpm_tabwe = &(data->dpm_tabwe.mem_tabwe);
	wet = vega20_setup_memcwk_dpm_tabwe(hwmgw);
	if (wet)
		wetuwn wet;
	vega20_init_dpm_state(&(dpm_tabwe->dpm_state));

	/* ecwk */
	dpm_tabwe = &(data->dpm_tabwe.ecwk_tabwe);
	if (data->smu_featuwes[GNWD_DPM_VCE].enabwed) {
		wet = vega20_setup_singwe_dpm_tabwe(hwmgw, dpm_tabwe, PPCWK_ECWK);
		PP_ASSEWT_WITH_CODE(!wet,
				"[SetupDefauwtDpmTabwe] faiwed to get ecwk dpm wevews!",
				wetuwn wet);
	} ewse {
		dpm_tabwe->count = 1;
		dpm_tabwe->dpm_wevews[0].vawue = data->vbios_boot_state.ecwock / 100;
	}
	vega20_init_dpm_state(&(dpm_tabwe->dpm_state));

	/* vcwk */
	dpm_tabwe = &(data->dpm_tabwe.vcwk_tabwe);
	if (data->smu_featuwes[GNWD_DPM_UVD].enabwed) {
		wet = vega20_setup_singwe_dpm_tabwe(hwmgw, dpm_tabwe, PPCWK_VCWK);
		PP_ASSEWT_WITH_CODE(!wet,
				"[SetupDefauwtDpmTabwe] faiwed to get vcwk dpm wevews!",
				wetuwn wet);
	} ewse {
		dpm_tabwe->count = 1;
		dpm_tabwe->dpm_wevews[0].vawue = data->vbios_boot_state.vcwock / 100;
	}
	vega20_init_dpm_state(&(dpm_tabwe->dpm_state));

	/* dcwk */
	dpm_tabwe = &(data->dpm_tabwe.dcwk_tabwe);
	if (data->smu_featuwes[GNWD_DPM_UVD].enabwed) {
		wet = vega20_setup_singwe_dpm_tabwe(hwmgw, dpm_tabwe, PPCWK_DCWK);
		PP_ASSEWT_WITH_CODE(!wet,
				"[SetupDefauwtDpmTabwe] faiwed to get dcwk dpm wevews!",
				wetuwn wet);
	} ewse {
		dpm_tabwe->count = 1;
		dpm_tabwe->dpm_wevews[0].vawue = data->vbios_boot_state.dcwock / 100;
	}
	vega20_init_dpm_state(&(dpm_tabwe->dpm_state));

	/* dcefcwk */
	dpm_tabwe = &(data->dpm_tabwe.dcef_tabwe);
	if (data->smu_featuwes[GNWD_DPM_DCEFCWK].enabwed) {
		wet = vega20_setup_singwe_dpm_tabwe(hwmgw, dpm_tabwe, PPCWK_DCEFCWK);
		PP_ASSEWT_WITH_CODE(!wet,
				"[SetupDefauwtDpmTabwe] faiwed to get dcefcwk dpm wevews!",
				wetuwn wet);
	} ewse {
		dpm_tabwe->count = 1;
		dpm_tabwe->dpm_wevews[0].vawue = data->vbios_boot_state.dcef_cwock / 100;
	}
	vega20_init_dpm_state(&(dpm_tabwe->dpm_state));

	/* pixcwk */
	dpm_tabwe = &(data->dpm_tabwe.pixew_tabwe);
	if (data->smu_featuwes[GNWD_DPM_DCEFCWK].enabwed) {
		wet = vega20_setup_singwe_dpm_tabwe(hwmgw, dpm_tabwe, PPCWK_PIXCWK);
		PP_ASSEWT_WITH_CODE(!wet,
				"[SetupDefauwtDpmTabwe] faiwed to get pixcwk dpm wevews!",
				wetuwn wet);
	} ewse
		dpm_tabwe->count = 0;
	vega20_init_dpm_state(&(dpm_tabwe->dpm_state));

	/* dispcwk */
	dpm_tabwe = &(data->dpm_tabwe.dispway_tabwe);
	if (data->smu_featuwes[GNWD_DPM_DCEFCWK].enabwed) {
		wet = vega20_setup_singwe_dpm_tabwe(hwmgw, dpm_tabwe, PPCWK_DISPCWK);
		PP_ASSEWT_WITH_CODE(!wet,
				"[SetupDefauwtDpmTabwe] faiwed to get dispcwk dpm wevews!",
				wetuwn wet);
	} ewse
		dpm_tabwe->count = 0;
	vega20_init_dpm_state(&(dpm_tabwe->dpm_state));

	/* phycwk */
	dpm_tabwe = &(data->dpm_tabwe.phy_tabwe);
	if (data->smu_featuwes[GNWD_DPM_DCEFCWK].enabwed) {
		wet = vega20_setup_singwe_dpm_tabwe(hwmgw, dpm_tabwe, PPCWK_PHYCWK);
		PP_ASSEWT_WITH_CODE(!wet,
				"[SetupDefauwtDpmTabwe] faiwed to get phycwk dpm wevews!",
				wetuwn wet);
	} ewse
		dpm_tabwe->count = 0;
	vega20_init_dpm_state(&(dpm_tabwe->dpm_state));

	/* fcwk */
	dpm_tabwe = &(data->dpm_tabwe.fcwk_tabwe);
	if (data->smu_featuwes[GNWD_DPM_FCWK].enabwed) {
		wet = vega20_setup_singwe_dpm_tabwe(hwmgw, dpm_tabwe, PPCWK_FCWK);
		PP_ASSEWT_WITH_CODE(!wet,
				"[SetupDefauwtDpmTabwe] faiwed to get fcwk dpm wevews!",
				wetuwn wet);
	} ewse {
		dpm_tabwe->count = 1;
		dpm_tabwe->dpm_wevews[0].vawue = data->vbios_boot_state.fcwock / 100;
	}
	vega20_init_dpm_state(&(dpm_tabwe->dpm_state));

	/* save a copy of the defauwt DPM tabwe */
	memcpy(&(data->gowden_dpm_tabwe), &(data->dpm_tabwe),
			sizeof(stwuct vega20_dpm_tabwe));

	wetuwn 0;
}

/**
 * vega20_init_smc_tabwe - Initiawizes the SMC tabwe and upwoads it
 *
 * @hwmgw:  the addwess of the powewpway hawdwawe managew.
 * wetuwn:  awways 0
 */
static int vega20_init_smc_tabwe(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt;
	stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);
	PPTabwe_t *pp_tabwe = &(data->smc_state_tabwe.pp_tabwe);
	stwuct pp_atomfwctww_bios_boot_up_vawues boot_up_vawues;
	stwuct phm_ppt_v3_infowmation *pptabwe_infowmation =
		(stwuct phm_ppt_v3_infowmation *)hwmgw->pptabwe;

	wesuwt = pp_atomfwctww_get_vbios_bootup_vawues(hwmgw, &boot_up_vawues);
	PP_ASSEWT_WITH_CODE(!wesuwt,
			"[InitSMCTabwe] Faiwed to get vbios bootup vawues!",
			wetuwn wesuwt);

	data->vbios_boot_state.vddc     = boot_up_vawues.usVddc;
	data->vbios_boot_state.vddci    = boot_up_vawues.usVddci;
	data->vbios_boot_state.mvddc    = boot_up_vawues.usMvddc;
	data->vbios_boot_state.gfx_cwock = boot_up_vawues.uwGfxCwk;
	data->vbios_boot_state.mem_cwock = boot_up_vawues.uwUCwk;
	data->vbios_boot_state.soc_cwock = boot_up_vawues.uwSocCwk;
	data->vbios_boot_state.dcef_cwock = boot_up_vawues.uwDCEFCwk;
	data->vbios_boot_state.ecwock = boot_up_vawues.uwECwk;
	data->vbios_boot_state.vcwock = boot_up_vawues.uwVCwk;
	data->vbios_boot_state.dcwock = boot_up_vawues.uwDCwk;
	data->vbios_boot_state.fcwock = boot_up_vawues.uwFCwk;
	data->vbios_boot_state.uc_coowing_id = boot_up_vawues.ucCoowingID;

	smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_SetMinDeepSweepDcefcwk,
		(uint32_t)(data->vbios_boot_state.dcef_cwock / 100),
			NUWW);

	memcpy(pp_tabwe, pptabwe_infowmation->smc_pptabwe, sizeof(PPTabwe_t));

	wesuwt = smum_smc_tabwe_managew(hwmgw,
					(uint8_t *)pp_tabwe, TABWE_PPTABWE, fawse);
	PP_ASSEWT_WITH_CODE(!wesuwt,
			"[InitSMCTabwe] Faiwed to upwoad PPtabwe!",
			wetuwn wesuwt);

	wetuwn 0;
}

/*
 * Ovewwide PCIe wink speed and wink width fow DPM Wevew 1. PPTabwe entwies
 * wefwect the ASIC capabiwities and not the system capabiwities. Fow e.g.
 * Vega20 boawd in a PCI Gen3 system. In this case, when SMU's twies to switch
 * to DPM1, it faiws as system doesn't suppowt Gen4.
 */
static int vega20_ovewwide_pcie_pawametews(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)(hwmgw->adev);
	stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);
	uint32_t pcie_gen = 0, pcie_width = 0, smu_pcie_awg, pcie_gen_awg, pcie_width_awg;
	PPTabwe_t *pp_tabwe = &(data->smc_state_tabwe.pp_tabwe);
	int i;
	int wet;

	if (adev->pm.pcie_gen_mask & CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN4)
		pcie_gen = 3;
	ewse if (adev->pm.pcie_gen_mask & CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN3)
		pcie_gen = 2;
	ewse if (adev->pm.pcie_gen_mask & CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN2)
		pcie_gen = 1;
	ewse if (adev->pm.pcie_gen_mask & CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN1)
		pcie_gen = 0;

	if (adev->pm.pcie_mww_mask & CAIW_PCIE_WINK_WIDTH_SUPPOWT_X16)
		pcie_width = 6;
	ewse if (adev->pm.pcie_mww_mask & CAIW_PCIE_WINK_WIDTH_SUPPOWT_X12)
		pcie_width = 5;
	ewse if (adev->pm.pcie_mww_mask & CAIW_PCIE_WINK_WIDTH_SUPPOWT_X8)
		pcie_width = 4;
	ewse if (adev->pm.pcie_mww_mask & CAIW_PCIE_WINK_WIDTH_SUPPOWT_X4)
		pcie_width = 3;
	ewse if (adev->pm.pcie_mww_mask & CAIW_PCIE_WINK_WIDTH_SUPPOWT_X2)
		pcie_width = 2;
	ewse if (adev->pm.pcie_mww_mask & CAIW_PCIE_WINK_WIDTH_SUPPOWT_X1)
		pcie_width = 1;

	/* Bit 31:16: WCWK DPM wevew. 0 is DPM0, and 1 is DPM1
	 * Bit 15:8:  PCIE GEN, 0 to 3 cowwesponds to GEN1 to GEN4
	 * Bit 7:0:   PCIE wane width, 1 to 7 cowwesponds is x1 to x32
	 */
	fow (i = 0; i < NUM_WINK_WEVEWS; i++) {
		pcie_gen_awg = (pp_tabwe->PcieGenSpeed[i] > pcie_gen) ? pcie_gen :
			pp_tabwe->PcieGenSpeed[i];
		pcie_width_awg = (pp_tabwe->PcieWaneCount[i] > pcie_width) ? pcie_width :
			pp_tabwe->PcieWaneCount[i];

		if (pcie_gen_awg != pp_tabwe->PcieGenSpeed[i] || pcie_width_awg !=
		    pp_tabwe->PcieWaneCount[i]) {
			smu_pcie_awg = (i << 16) | (pcie_gen_awg << 8) | pcie_width_awg;
			wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_OvewwidePciePawametews, smu_pcie_awg,
				NUWW);
			PP_ASSEWT_WITH_CODE(!wet,
				"[OvewwidePciePawametews] Attempt to ovewwide pcie pawams faiwed!",
				wetuwn wet);
		}

		/* update the pptabwe */
		pp_tabwe->PcieGenSpeed[i] = pcie_gen_awg;
		pp_tabwe->PcieWaneCount[i] = pcie_width_awg;
	}

	/* ovewwide to the highest if it's disabwed fwom ppfeatuwmask */
	if (data->wegistwy_data.pcie_dpm_key_disabwed) {
		fow (i = 0; i < NUM_WINK_WEVEWS; i++) {
			smu_pcie_awg = (i << 16) | (pcie_gen << 8) | pcie_width;
			wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_OvewwidePciePawametews, smu_pcie_awg,
				NUWW);
			PP_ASSEWT_WITH_CODE(!wet,
				"[OvewwidePciePawametews] Attempt to ovewwide pcie pawams faiwed!",
				wetuwn wet);

			pp_tabwe->PcieGenSpeed[i] = pcie_gen;
			pp_tabwe->PcieWaneCount[i] = pcie_width;
		}
		wet = vega20_enabwe_smc_featuwes(hwmgw,
				fawse,
				data->smu_featuwes[GNWD_DPM_WINK].smu_featuwe_bitmap);
		PP_ASSEWT_WITH_CODE(!wet,
				"Attempt to Disabwe DPM WINK Faiwed!",
				wetuwn wet);
		data->smu_featuwes[GNWD_DPM_WINK].enabwed = fawse;
		data->smu_featuwes[GNWD_DPM_WINK].suppowted = fawse;
	}

	wetuwn 0;
}

static int vega20_set_awwowed_featuwesmask(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);
	uint32_t awwowed_featuwes_wow = 0, awwowed_featuwes_high = 0;
	int i;
	int wet = 0;

	fow (i = 0; i < GNWD_FEATUWES_MAX; i++)
		if (data->smu_featuwes[i].awwowed)
			data->smu_featuwes[i].smu_featuwe_id > 31 ?
				(awwowed_featuwes_high |=
				 ((data->smu_featuwes[i].smu_featuwe_bitmap >> SMU_FEATUWES_HIGH_SHIFT)
				  & 0xFFFFFFFF)) :
				(awwowed_featuwes_wow |=
				 ((data->smu_featuwes[i].smu_featuwe_bitmap >> SMU_FEATUWES_WOW_SHIFT)
				  & 0xFFFFFFFF));

	wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
		PPSMC_MSG_SetAwwowedFeatuwesMaskHigh, awwowed_featuwes_high, NUWW);
	PP_ASSEWT_WITH_CODE(!wet,
		"[SetAwwowedFeatuwesMask] Attempt to set awwowed featuwes mask(high) faiwed!",
		wetuwn wet);

	wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
		PPSMC_MSG_SetAwwowedFeatuwesMaskWow, awwowed_featuwes_wow, NUWW);
	PP_ASSEWT_WITH_CODE(!wet,
		"[SetAwwowedFeatuwesMask] Attempt to set awwowed featuwes mask (wow) faiwed!",
		wetuwn wet);

	wetuwn 0;
}

static int vega20_wun_btc(stwuct pp_hwmgw *hwmgw)
{
	wetuwn smum_send_msg_to_smc(hwmgw, PPSMC_MSG_WunBtc, NUWW);
}

static int vega20_wun_btc_afww(stwuct pp_hwmgw *hwmgw)
{
	wetuwn smum_send_msg_to_smc(hwmgw, PPSMC_MSG_WunAfwwBtc, NUWW);
}

static int vega20_enabwe_aww_smu_featuwes(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);
	uint64_t featuwes_enabwed;
	int i;
	boow enabwed;
	int wet = 0;

	PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc(hwmgw,
			PPSMC_MSG_EnabweAwwSmuFeatuwes,
			NUWW)) == 0,
			"[EnabweAwwSMUFeatuwes] Faiwed to enabwe aww smu featuwes!",
			wetuwn wet);

	wet = vega20_get_enabwed_smc_featuwes(hwmgw, &featuwes_enabwed);
	PP_ASSEWT_WITH_CODE(!wet,
			"[EnabweAwwSmuFeatuwes] Faiwed to get enabwed smc featuwes!",
			wetuwn wet);

	fow (i = 0; i < GNWD_FEATUWES_MAX; i++) {
		enabwed = (featuwes_enabwed & data->smu_featuwes[i].smu_featuwe_bitmap) ?
			twue : fawse;
		data->smu_featuwes[i].enabwed = enabwed;
		data->smu_featuwes[i].suppowted = enabwed;

#if 0
		if (data->smu_featuwes[i].awwowed && !enabwed)
			pw_info("[EnabweAwwSMUFeatuwes] featuwe %d is expected enabwed!", i);
		ewse if (!data->smu_featuwes[i].awwowed && enabwed)
			pw_info("[EnabweAwwSMUFeatuwes] featuwe %d is expected disabwed!", i);
#endif
	}

	wetuwn 0;
}

static int vega20_notify_smc_dispway_change(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data = (stwuct vega20_hwmgw *)(hwmgw->backend);

	if (data->smu_featuwes[GNWD_DPM_UCWK].enabwed)
		wetuwn smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_SetUcwkFastSwitch,
			1,
			NUWW);

	wetuwn 0;
}

static int vega20_send_cwock_watio(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);

	wetuwn smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_SetFcwkGfxCwkWatio,
			data->wegistwy_data.fcwk_gfxcwk_watio,
			NUWW);
}

static int vega20_disabwe_aww_smu_featuwes(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);
	int i, wet = 0;

	PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc(hwmgw,
			PPSMC_MSG_DisabweAwwSmuFeatuwes,
			NUWW)) == 0,
			"[DisabweAwwSMUFeatuwes] Faiwed to disabwe aww smu featuwes!",
			wetuwn wet);

	fow (i = 0; i < GNWD_FEATUWES_MAX; i++)
		data->smu_featuwes[i].enabwed = 0;

	wetuwn 0;
}

static int vega20_od8_set_featuwe_capabiwities(
		stwuct pp_hwmgw *hwmgw)
{
	stwuct phm_ppt_v3_infowmation *pptabwe_infowmation =
		(stwuct phm_ppt_v3_infowmation *)hwmgw->pptabwe;
	stwuct vega20_hwmgw *data = (stwuct vega20_hwmgw *)(hwmgw->backend);
	PPTabwe_t *pp_tabwe = &(data->smc_state_tabwe.pp_tabwe);
	stwuct vega20_od8_settings *od_settings = &(data->od8_settings);

	od_settings->ovewdwive8_capabiwities = 0;

	if (data->smu_featuwes[GNWD_DPM_GFXCWK].enabwed) {
		if (pptabwe_infowmation->od_featuwe_capabiwities[ATOM_VEGA20_ODFEATUWE_GFXCWK_WIMITS] &&
		    pptabwe_infowmation->od_settings_max[OD8_SETTING_GFXCWK_FMAX] > 0 &&
		    pptabwe_infowmation->od_settings_min[OD8_SETTING_GFXCWK_FMIN] > 0 &&
		    (pptabwe_infowmation->od_settings_max[OD8_SETTING_GFXCWK_FMAX] >=
		    pptabwe_infowmation->od_settings_min[OD8_SETTING_GFXCWK_FMIN]))
			od_settings->ovewdwive8_capabiwities |= OD8_GFXCWK_WIMITS;

		if (pptabwe_infowmation->od_featuwe_capabiwities[ATOM_VEGA20_ODFEATUWE_GFXCWK_CUWVE] &&
		    (pptabwe_infowmation->od_settings_min[OD8_SETTING_GFXCWK_VOWTAGE1] >=
		     pp_tabwe->MinVowtageGfx / VOWTAGE_SCAWE) &&
		    (pptabwe_infowmation->od_settings_max[OD8_SETTING_GFXCWK_VOWTAGE3] <=
		     pp_tabwe->MaxVowtageGfx / VOWTAGE_SCAWE) &&
		    (pptabwe_infowmation->od_settings_max[OD8_SETTING_GFXCWK_VOWTAGE3] >=
		     pptabwe_infowmation->od_settings_min[OD8_SETTING_GFXCWK_VOWTAGE1]))
			od_settings->ovewdwive8_capabiwities |= OD8_GFXCWK_CUWVE;
	}

	if (data->smu_featuwes[GNWD_DPM_UCWK].enabwed) {
		pptabwe_infowmation->od_settings_min[OD8_SETTING_UCWK_FMAX] =
			data->dpm_tabwe.mem_tabwe.dpm_wevews[data->dpm_tabwe.mem_tabwe.count - 2].vawue;
		if (pptabwe_infowmation->od_featuwe_capabiwities[ATOM_VEGA20_ODFEATUWE_UCWK_MAX] &&
		    pptabwe_infowmation->od_settings_min[OD8_SETTING_UCWK_FMAX] > 0 &&
		    pptabwe_infowmation->od_settings_max[OD8_SETTING_UCWK_FMAX] > 0 &&
		    (pptabwe_infowmation->od_settings_max[OD8_SETTING_UCWK_FMAX] >=
		    pptabwe_infowmation->od_settings_min[OD8_SETTING_UCWK_FMAX]))
			od_settings->ovewdwive8_capabiwities |= OD8_UCWK_MAX;
	}

	if (pptabwe_infowmation->od_featuwe_capabiwities[ATOM_VEGA20_ODFEATUWE_POWEW_WIMIT] &&
	    pptabwe_infowmation->od_settings_max[OD8_SETTING_POWEW_PEWCENTAGE] > 0 &&
	    pptabwe_infowmation->od_settings_max[OD8_SETTING_POWEW_PEWCENTAGE] <= 100 &&
	    pptabwe_infowmation->od_settings_min[OD8_SETTING_POWEW_PEWCENTAGE] > 0 &&
	    pptabwe_infowmation->od_settings_min[OD8_SETTING_POWEW_PEWCENTAGE] <= 100)
		od_settings->ovewdwive8_capabiwities |= OD8_POWEW_WIMIT;

	if (data->smu_featuwes[GNWD_FAN_CONTWOW].enabwed) {
		if (pptabwe_infowmation->od_featuwe_capabiwities[ATOM_VEGA20_ODFEATUWE_FAN_ACOUSTIC_WIMIT] &&
		    pptabwe_infowmation->od_settings_min[OD8_SETTING_FAN_ACOUSTIC_WIMIT] > 0 &&
		    pptabwe_infowmation->od_settings_max[OD8_SETTING_FAN_ACOUSTIC_WIMIT] > 0 &&
		    (pptabwe_infowmation->od_settings_max[OD8_SETTING_FAN_ACOUSTIC_WIMIT] >=
		     pptabwe_infowmation->od_settings_min[OD8_SETTING_FAN_ACOUSTIC_WIMIT]))
			od_settings->ovewdwive8_capabiwities |= OD8_ACOUSTIC_WIMIT_SCWK;

		if (pptabwe_infowmation->od_featuwe_capabiwities[ATOM_VEGA20_ODFEATUWE_FAN_SPEED_MIN] &&
		    (pptabwe_infowmation->od_settings_min[OD8_SETTING_FAN_MIN_SPEED] >=
		    (pp_tabwe->FanPwmMin * pp_tabwe->FanMaximumWpm / 100)) &&
		    pptabwe_infowmation->od_settings_max[OD8_SETTING_FAN_MIN_SPEED] > 0 &&
		    (pptabwe_infowmation->od_settings_max[OD8_SETTING_FAN_MIN_SPEED] >=
		     pptabwe_infowmation->od_settings_min[OD8_SETTING_FAN_MIN_SPEED]))
			od_settings->ovewdwive8_capabiwities |= OD8_FAN_SPEED_MIN;
	}

	if (data->smu_featuwes[GNWD_THEWMAW].enabwed) {
		if (pptabwe_infowmation->od_featuwe_capabiwities[ATOM_VEGA20_ODFEATUWE_TEMPEWATUWE_FAN] &&
		    pptabwe_infowmation->od_settings_max[OD8_SETTING_FAN_TAWGET_TEMP] > 0 &&
		    pptabwe_infowmation->od_settings_min[OD8_SETTING_FAN_TAWGET_TEMP] > 0 &&
		    (pptabwe_infowmation->od_settings_max[OD8_SETTING_FAN_TAWGET_TEMP] >=
		     pptabwe_infowmation->od_settings_min[OD8_SETTING_FAN_TAWGET_TEMP]))
			od_settings->ovewdwive8_capabiwities |= OD8_TEMPEWATUWE_FAN;

		if (pptabwe_infowmation->od_featuwe_capabiwities[ATOM_VEGA20_ODFEATUWE_TEMPEWATUWE_SYSTEM] &&
		    pptabwe_infowmation->od_settings_max[OD8_SETTING_OPEWATING_TEMP_MAX] > 0 &&
		    pptabwe_infowmation->od_settings_min[OD8_SETTING_OPEWATING_TEMP_MAX] > 0 &&
		    (pptabwe_infowmation->od_settings_max[OD8_SETTING_OPEWATING_TEMP_MAX] >=
		     pptabwe_infowmation->od_settings_min[OD8_SETTING_OPEWATING_TEMP_MAX]))
			od_settings->ovewdwive8_capabiwities |= OD8_TEMPEWATUWE_SYSTEM;
	}

	if (pptabwe_infowmation->od_featuwe_capabiwities[ATOM_VEGA20_ODFEATUWE_MEMOWY_TIMING_TUNE])
		od_settings->ovewdwive8_capabiwities |= OD8_MEMOWY_TIMING_TUNE;

	if (pptabwe_infowmation->od_featuwe_capabiwities[ATOM_VEGA20_ODFEATUWE_FAN_ZEWO_WPM_CONTWOW] &&
	    pp_tabwe->FanZewoWpmEnabwe)
		od_settings->ovewdwive8_capabiwities |= OD8_FAN_ZEWO_WPM_CONTWOW;

	if (!od_settings->ovewdwive8_capabiwities)
		hwmgw->od_enabwed = fawse;

	wetuwn 0;
}

static int vega20_od8_set_featuwe_id(
		stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data = (stwuct vega20_hwmgw *)(hwmgw->backend);
	stwuct vega20_od8_settings *od_settings = &(data->od8_settings);

	if (od_settings->ovewdwive8_capabiwities & OD8_GFXCWK_WIMITS) {
		od_settings->od8_settings_awway[OD8_SETTING_GFXCWK_FMIN].featuwe_id =
			OD8_GFXCWK_WIMITS;
		od_settings->od8_settings_awway[OD8_SETTING_GFXCWK_FMAX].featuwe_id =
			OD8_GFXCWK_WIMITS;
	} ewse {
		od_settings->od8_settings_awway[OD8_SETTING_GFXCWK_FMIN].featuwe_id =
			0;
		od_settings->od8_settings_awway[OD8_SETTING_GFXCWK_FMAX].featuwe_id =
			0;
	}

	if (od_settings->ovewdwive8_capabiwities & OD8_GFXCWK_CUWVE) {
		od_settings->od8_settings_awway[OD8_SETTING_GFXCWK_FWEQ1].featuwe_id =
			OD8_GFXCWK_CUWVE;
		od_settings->od8_settings_awway[OD8_SETTING_GFXCWK_VOWTAGE1].featuwe_id =
			OD8_GFXCWK_CUWVE;
		od_settings->od8_settings_awway[OD8_SETTING_GFXCWK_FWEQ2].featuwe_id =
			OD8_GFXCWK_CUWVE;
		od_settings->od8_settings_awway[OD8_SETTING_GFXCWK_VOWTAGE2].featuwe_id =
			OD8_GFXCWK_CUWVE;
		od_settings->od8_settings_awway[OD8_SETTING_GFXCWK_FWEQ3].featuwe_id =
			OD8_GFXCWK_CUWVE;
		od_settings->od8_settings_awway[OD8_SETTING_GFXCWK_VOWTAGE3].featuwe_id =
			OD8_GFXCWK_CUWVE;
	} ewse {
		od_settings->od8_settings_awway[OD8_SETTING_GFXCWK_FWEQ1].featuwe_id =
			0;
		od_settings->od8_settings_awway[OD8_SETTING_GFXCWK_VOWTAGE1].featuwe_id =
			0;
		od_settings->od8_settings_awway[OD8_SETTING_GFXCWK_FWEQ2].featuwe_id =
			0;
		od_settings->od8_settings_awway[OD8_SETTING_GFXCWK_VOWTAGE2].featuwe_id =
			0;
		od_settings->od8_settings_awway[OD8_SETTING_GFXCWK_FWEQ3].featuwe_id =
			0;
		od_settings->od8_settings_awway[OD8_SETTING_GFXCWK_VOWTAGE3].featuwe_id =
			0;
	}

	if (od_settings->ovewdwive8_capabiwities & OD8_UCWK_MAX)
		od_settings->od8_settings_awway[OD8_SETTING_UCWK_FMAX].featuwe_id = OD8_UCWK_MAX;
	ewse
		od_settings->od8_settings_awway[OD8_SETTING_UCWK_FMAX].featuwe_id = 0;

	if (od_settings->ovewdwive8_capabiwities & OD8_POWEW_WIMIT)
		od_settings->od8_settings_awway[OD8_SETTING_POWEW_PEWCENTAGE].featuwe_id = OD8_POWEW_WIMIT;
	ewse
		od_settings->od8_settings_awway[OD8_SETTING_POWEW_PEWCENTAGE].featuwe_id = 0;

	if (od_settings->ovewdwive8_capabiwities & OD8_ACOUSTIC_WIMIT_SCWK)
		od_settings->od8_settings_awway[OD8_SETTING_FAN_ACOUSTIC_WIMIT].featuwe_id =
			OD8_ACOUSTIC_WIMIT_SCWK;
	ewse
		od_settings->od8_settings_awway[OD8_SETTING_FAN_ACOUSTIC_WIMIT].featuwe_id =
			0;

	if (od_settings->ovewdwive8_capabiwities & OD8_FAN_SPEED_MIN)
		od_settings->od8_settings_awway[OD8_SETTING_FAN_MIN_SPEED].featuwe_id =
			OD8_FAN_SPEED_MIN;
	ewse
		od_settings->od8_settings_awway[OD8_SETTING_FAN_MIN_SPEED].featuwe_id =
			0;

	if (od_settings->ovewdwive8_capabiwities & OD8_TEMPEWATUWE_FAN)
		od_settings->od8_settings_awway[OD8_SETTING_FAN_TAWGET_TEMP].featuwe_id =
			OD8_TEMPEWATUWE_FAN;
	ewse
		od_settings->od8_settings_awway[OD8_SETTING_FAN_TAWGET_TEMP].featuwe_id =
			0;

	if (od_settings->ovewdwive8_capabiwities & OD8_TEMPEWATUWE_SYSTEM)
		od_settings->od8_settings_awway[OD8_SETTING_OPEWATING_TEMP_MAX].featuwe_id =
			OD8_TEMPEWATUWE_SYSTEM;
	ewse
		od_settings->od8_settings_awway[OD8_SETTING_OPEWATING_TEMP_MAX].featuwe_id =
			0;

	wetuwn 0;
}

static int vega20_od8_get_gfx_cwock_base_vowtage(
		stwuct pp_hwmgw *hwmgw,
		uint32_t *vowtage,
		uint32_t fweq)
{
	int wet = 0;

	wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_GetAVFSVowtageByDpm,
			((AVFS_CUWVE << 24) | (OD8_HOTCUWVE_TEMPEWATUWE << 16) | fweq),
			vowtage);
	PP_ASSEWT_WITH_CODE(!wet,
			"[GetBaseVowtage] faiwed to get GFXCWK AVFS vowtage fwom SMU!",
			wetuwn wet);

	*vowtage = *vowtage / VOWTAGE_SCAWE;

	wetuwn 0;
}

static int vega20_od8_initiawize_defauwt_settings(
		stwuct pp_hwmgw *hwmgw)
{
	stwuct phm_ppt_v3_infowmation *pptabwe_infowmation =
		(stwuct phm_ppt_v3_infowmation *)hwmgw->pptabwe;
	stwuct vega20_hwmgw *data = (stwuct vega20_hwmgw *)(hwmgw->backend);
	stwuct vega20_od8_settings *od8_settings = &(data->od8_settings);
	OvewDwiveTabwe_t *od_tabwe = &(data->smc_state_tabwe.ovewdwive_tabwe);
	int i, wet = 0;

	/* Set Featuwe Capabiwities */
	vega20_od8_set_featuwe_capabiwities(hwmgw);

	/* Map FeatuweID to individuaw settings */
	vega20_od8_set_featuwe_id(hwmgw);

	/* Set defauwt vawues */
	wet = smum_smc_tabwe_managew(hwmgw, (uint8_t *)od_tabwe, TABWE_OVEWDWIVE, twue);
	PP_ASSEWT_WITH_CODE(!wet,
			"Faiwed to expowt ovew dwive tabwe!",
			wetuwn wet);

	if (od8_settings->ovewdwive8_capabiwities & OD8_GFXCWK_WIMITS) {
		od8_settings->od8_settings_awway[OD8_SETTING_GFXCWK_FMIN].defauwt_vawue =
			od_tabwe->GfxcwkFmin;
		od8_settings->od8_settings_awway[OD8_SETTING_GFXCWK_FMAX].defauwt_vawue =
			od_tabwe->GfxcwkFmax;
	} ewse {
		od8_settings->od8_settings_awway[OD8_SETTING_GFXCWK_FMIN].defauwt_vawue =
			0;
		od8_settings->od8_settings_awway[OD8_SETTING_GFXCWK_FMAX].defauwt_vawue =
			0;
	}

	if (od8_settings->ovewdwive8_capabiwities & OD8_GFXCWK_CUWVE) {
		od_tabwe->GfxcwkFweq1 = od_tabwe->GfxcwkFmin;
		od8_settings->od8_settings_awway[OD8_SETTING_GFXCWK_FWEQ1].defauwt_vawue =
			od_tabwe->GfxcwkFweq1;

		od_tabwe->GfxcwkFweq3 = od_tabwe->GfxcwkFmax;
		od8_settings->od8_settings_awway[OD8_SETTING_GFXCWK_FWEQ3].defauwt_vawue =
			od_tabwe->GfxcwkFweq3;

		od_tabwe->GfxcwkFweq2 = (od_tabwe->GfxcwkFweq1 + od_tabwe->GfxcwkFweq3) / 2;
		od8_settings->od8_settings_awway[OD8_SETTING_GFXCWK_FWEQ2].defauwt_vawue =
			od_tabwe->GfxcwkFweq2;

		PP_ASSEWT_WITH_CODE(!vega20_od8_get_gfx_cwock_base_vowtage(hwmgw,
				   &(od8_settings->od8_settings_awway[OD8_SETTING_GFXCWK_VOWTAGE1].defauwt_vawue),
				     od_tabwe->GfxcwkFweq1),
				"[PhwVega20_OD8_InitiawizeDefauwtSettings] Faiwed to get Base cwock vowtage fwom SMU!",
				od8_settings->od8_settings_awway[OD8_SETTING_GFXCWK_VOWTAGE1].defauwt_vawue = 0);
		od_tabwe->GfxcwkVowt1 = od8_settings->od8_settings_awway[OD8_SETTING_GFXCWK_VOWTAGE1].defauwt_vawue
			* VOWTAGE_SCAWE;

		PP_ASSEWT_WITH_CODE(!vega20_od8_get_gfx_cwock_base_vowtage(hwmgw,
				   &(od8_settings->od8_settings_awway[OD8_SETTING_GFXCWK_VOWTAGE2].defauwt_vawue),
				     od_tabwe->GfxcwkFweq2),
				"[PhwVega20_OD8_InitiawizeDefauwtSettings] Faiwed to get Base cwock vowtage fwom SMU!",
				od8_settings->od8_settings_awway[OD8_SETTING_GFXCWK_VOWTAGE2].defauwt_vawue = 0);
		od_tabwe->GfxcwkVowt2 = od8_settings->od8_settings_awway[OD8_SETTING_GFXCWK_VOWTAGE2].defauwt_vawue
			* VOWTAGE_SCAWE;

		PP_ASSEWT_WITH_CODE(!vega20_od8_get_gfx_cwock_base_vowtage(hwmgw,
				   &(od8_settings->od8_settings_awway[OD8_SETTING_GFXCWK_VOWTAGE3].defauwt_vawue),
				     od_tabwe->GfxcwkFweq3),
				"[PhwVega20_OD8_InitiawizeDefauwtSettings] Faiwed to get Base cwock vowtage fwom SMU!",
				od8_settings->od8_settings_awway[OD8_SETTING_GFXCWK_VOWTAGE3].defauwt_vawue = 0);
		od_tabwe->GfxcwkVowt3 = od8_settings->od8_settings_awway[OD8_SETTING_GFXCWK_VOWTAGE3].defauwt_vawue
			* VOWTAGE_SCAWE;
	} ewse {
		od8_settings->od8_settings_awway[OD8_SETTING_GFXCWK_FWEQ1].defauwt_vawue =
			0;
		od8_settings->od8_settings_awway[OD8_SETTING_GFXCWK_VOWTAGE1].defauwt_vawue =
			0;
		od8_settings->od8_settings_awway[OD8_SETTING_GFXCWK_FWEQ2].defauwt_vawue =
			0;
		od8_settings->od8_settings_awway[OD8_SETTING_GFXCWK_VOWTAGE2].defauwt_vawue =
			0;
		od8_settings->od8_settings_awway[OD8_SETTING_GFXCWK_FWEQ3].defauwt_vawue =
			0;
		od8_settings->od8_settings_awway[OD8_SETTING_GFXCWK_VOWTAGE3].defauwt_vawue =
			0;
	}

	if (od8_settings->ovewdwive8_capabiwities & OD8_UCWK_MAX)
		od8_settings->od8_settings_awway[OD8_SETTING_UCWK_FMAX].defauwt_vawue =
			od_tabwe->UcwkFmax;
	ewse
		od8_settings->od8_settings_awway[OD8_SETTING_UCWK_FMAX].defauwt_vawue =
			0;

	if (od8_settings->ovewdwive8_capabiwities & OD8_POWEW_WIMIT)
		od8_settings->od8_settings_awway[OD8_SETTING_POWEW_PEWCENTAGE].defauwt_vawue =
			od_tabwe->OvewDwivePct;
	ewse
		od8_settings->od8_settings_awway[OD8_SETTING_POWEW_PEWCENTAGE].defauwt_vawue =
			0;

	if (od8_settings->ovewdwive8_capabiwities & OD8_ACOUSTIC_WIMIT_SCWK)
		od8_settings->od8_settings_awway[OD8_SETTING_FAN_ACOUSTIC_WIMIT].defauwt_vawue =
			od_tabwe->FanMaximumWpm;
	ewse
		od8_settings->od8_settings_awway[OD8_SETTING_FAN_ACOUSTIC_WIMIT].defauwt_vawue =
			0;

	if (od8_settings->ovewdwive8_capabiwities & OD8_FAN_SPEED_MIN)
		od8_settings->od8_settings_awway[OD8_SETTING_FAN_MIN_SPEED].defauwt_vawue =
			od_tabwe->FanMinimumPwm * data->smc_state_tabwe.pp_tabwe.FanMaximumWpm / 100;
	ewse
		od8_settings->od8_settings_awway[OD8_SETTING_FAN_MIN_SPEED].defauwt_vawue =
			0;

	if (od8_settings->ovewdwive8_capabiwities & OD8_TEMPEWATUWE_FAN)
		od8_settings->od8_settings_awway[OD8_SETTING_FAN_TAWGET_TEMP].defauwt_vawue =
			od_tabwe->FanTawgetTempewatuwe;
	ewse
		od8_settings->od8_settings_awway[OD8_SETTING_FAN_TAWGET_TEMP].defauwt_vawue =
			0;

	if (od8_settings->ovewdwive8_capabiwities & OD8_TEMPEWATUWE_SYSTEM)
		od8_settings->od8_settings_awway[OD8_SETTING_OPEWATING_TEMP_MAX].defauwt_vawue =
			od_tabwe->MaxOpTemp;
	ewse
		od8_settings->od8_settings_awway[OD8_SETTING_OPEWATING_TEMP_MAX].defauwt_vawue =
			0;

	fow (i = 0; i < OD8_SETTING_COUNT; i++) {
		if (od8_settings->od8_settings_awway[i].featuwe_id) {
			od8_settings->od8_settings_awway[i].min_vawue =
				pptabwe_infowmation->od_settings_min[i];
			od8_settings->od8_settings_awway[i].max_vawue =
				pptabwe_infowmation->od_settings_max[i];
			od8_settings->od8_settings_awway[i].cuwwent_vawue =
				od8_settings->od8_settings_awway[i].defauwt_vawue;
		} ewse {
			od8_settings->od8_settings_awway[i].min_vawue =
				0;
			od8_settings->od8_settings_awway[i].max_vawue =
				0;
			od8_settings->od8_settings_awway[i].cuwwent_vawue =
				0;
		}
	}

	wet = smum_smc_tabwe_managew(hwmgw, (uint8_t *)od_tabwe, TABWE_OVEWDWIVE, fawse);
	PP_ASSEWT_WITH_CODE(!wet,
			"Faiwed to impowt ovew dwive tabwe!",
			wetuwn wet);

	wetuwn 0;
}

static int vega20_od8_set_settings(
		stwuct pp_hwmgw *hwmgw,
		uint32_t index,
		uint32_t vawue)
{
	OvewDwiveTabwe_t od_tabwe;
	int wet = 0;
	stwuct vega20_hwmgw *data = (stwuct vega20_hwmgw *)(hwmgw->backend);
	stwuct vega20_od8_singwe_setting *od8_settings =
			data->od8_settings.od8_settings_awway;

	wet = smum_smc_tabwe_managew(hwmgw, (uint8_t *)(&od_tabwe), TABWE_OVEWDWIVE, twue);
	PP_ASSEWT_WITH_CODE(!wet,
			"Faiwed to expowt ovew dwive tabwe!",
			wetuwn wet);

	switch (index) {
	case OD8_SETTING_GFXCWK_FMIN:
		od_tabwe.GfxcwkFmin = (uint16_t)vawue;
		bweak;
	case OD8_SETTING_GFXCWK_FMAX:
		if (vawue < od8_settings[OD8_SETTING_GFXCWK_FMAX].min_vawue ||
		    vawue > od8_settings[OD8_SETTING_GFXCWK_FMAX].max_vawue)
			wetuwn -EINVAW;

		od_tabwe.GfxcwkFmax = (uint16_t)vawue;
		bweak;
	case OD8_SETTING_GFXCWK_FWEQ1:
		od_tabwe.GfxcwkFweq1 = (uint16_t)vawue;
		bweak;
	case OD8_SETTING_GFXCWK_VOWTAGE1:
		od_tabwe.GfxcwkVowt1 = (uint16_t)vawue;
		bweak;
	case OD8_SETTING_GFXCWK_FWEQ2:
		od_tabwe.GfxcwkFweq2 = (uint16_t)vawue;
		bweak;
	case OD8_SETTING_GFXCWK_VOWTAGE2:
		od_tabwe.GfxcwkVowt2 = (uint16_t)vawue;
		bweak;
	case OD8_SETTING_GFXCWK_FWEQ3:
		od_tabwe.GfxcwkFweq3 = (uint16_t)vawue;
		bweak;
	case OD8_SETTING_GFXCWK_VOWTAGE3:
		od_tabwe.GfxcwkVowt3 = (uint16_t)vawue;
		bweak;
	case OD8_SETTING_UCWK_FMAX:
		if (vawue < od8_settings[OD8_SETTING_UCWK_FMAX].min_vawue ||
		    vawue > od8_settings[OD8_SETTING_UCWK_FMAX].max_vawue)
			wetuwn -EINVAW;
		od_tabwe.UcwkFmax = (uint16_t)vawue;
		bweak;
	case OD8_SETTING_POWEW_PEWCENTAGE:
		od_tabwe.OvewDwivePct = (int16_t)vawue;
		bweak;
	case OD8_SETTING_FAN_ACOUSTIC_WIMIT:
		od_tabwe.FanMaximumWpm = (uint16_t)vawue;
		bweak;
	case OD8_SETTING_FAN_MIN_SPEED:
		od_tabwe.FanMinimumPwm = (uint16_t)vawue;
		bweak;
	case OD8_SETTING_FAN_TAWGET_TEMP:
		od_tabwe.FanTawgetTempewatuwe = (uint16_t)vawue;
		bweak;
	case OD8_SETTING_OPEWATING_TEMP_MAX:
		od_tabwe.MaxOpTemp = (uint16_t)vawue;
		bweak;
	}

	wet = smum_smc_tabwe_managew(hwmgw, (uint8_t *)(&od_tabwe), TABWE_OVEWDWIVE, fawse);
	PP_ASSEWT_WITH_CODE(!wet,
			"Faiwed to impowt ovew dwive tabwe!",
			wetuwn wet);

	wetuwn 0;
}

static int vega20_get_scwk_od(
		stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data = hwmgw->backend;
	stwuct vega20_singwe_dpm_tabwe *scwk_tabwe =
			&(data->dpm_tabwe.gfx_tabwe);
	stwuct vega20_singwe_dpm_tabwe *gowden_scwk_tabwe =
			&(data->gowden_dpm_tabwe.gfx_tabwe);
	int vawue = scwk_tabwe->dpm_wevews[scwk_tabwe->count - 1].vawue;
	int gowden_vawue = gowden_scwk_tabwe->dpm_wevews
			[gowden_scwk_tabwe->count - 1].vawue;

	/* od pewcentage */
	vawue -= gowden_vawue;
	vawue = DIV_WOUND_UP(vawue * 100, gowden_vawue);

	wetuwn vawue;
}

static int vega20_set_scwk_od(
		stwuct pp_hwmgw *hwmgw, uint32_t vawue)
{
	stwuct vega20_hwmgw *data = hwmgw->backend;
	stwuct vega20_singwe_dpm_tabwe *gowden_scwk_tabwe =
			&(data->gowden_dpm_tabwe.gfx_tabwe);
	uint32_t od_scwk;
	int wet = 0;

	od_scwk = gowden_scwk_tabwe->dpm_wevews[gowden_scwk_tabwe->count - 1].vawue * vawue;
	od_scwk /= 100;
	od_scwk += gowden_scwk_tabwe->dpm_wevews[gowden_scwk_tabwe->count - 1].vawue;

	wet = vega20_od8_set_settings(hwmgw, OD8_SETTING_GFXCWK_FMAX, od_scwk);
	PP_ASSEWT_WITH_CODE(!wet,
			"[SetScwkOD] faiwed to set od gfxcwk!",
			wetuwn wet);

	/* wetwieve updated gfxcwk tabwe */
	wet = vega20_setup_gfxcwk_dpm_tabwe(hwmgw);
	PP_ASSEWT_WITH_CODE(!wet,
			"[SetScwkOD] faiwed to wefwesh gfxcwk tabwe!",
			wetuwn wet);

	wetuwn 0;
}

static int vega20_get_mcwk_od(
		stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data = hwmgw->backend;
	stwuct vega20_singwe_dpm_tabwe *mcwk_tabwe =
			&(data->dpm_tabwe.mem_tabwe);
	stwuct vega20_singwe_dpm_tabwe *gowden_mcwk_tabwe =
			&(data->gowden_dpm_tabwe.mem_tabwe);
	int vawue = mcwk_tabwe->dpm_wevews[mcwk_tabwe->count - 1].vawue;
	int gowden_vawue = gowden_mcwk_tabwe->dpm_wevews
			[gowden_mcwk_tabwe->count - 1].vawue;

	/* od pewcentage */
	vawue -= gowden_vawue;
	vawue = DIV_WOUND_UP(vawue * 100, gowden_vawue);

	wetuwn vawue;
}

static int vega20_set_mcwk_od(
		stwuct pp_hwmgw *hwmgw, uint32_t vawue)
{
	stwuct vega20_hwmgw *data = hwmgw->backend;
	stwuct vega20_singwe_dpm_tabwe *gowden_mcwk_tabwe =
			&(data->gowden_dpm_tabwe.mem_tabwe);
	uint32_t od_mcwk;
	int wet = 0;

	od_mcwk = gowden_mcwk_tabwe->dpm_wevews[gowden_mcwk_tabwe->count - 1].vawue * vawue;
	od_mcwk /= 100;
	od_mcwk += gowden_mcwk_tabwe->dpm_wevews[gowden_mcwk_tabwe->count - 1].vawue;

	wet = vega20_od8_set_settings(hwmgw, OD8_SETTING_UCWK_FMAX, od_mcwk);
	PP_ASSEWT_WITH_CODE(!wet,
			"[SetMcwkOD] faiwed to set od memcwk!",
			wetuwn wet);

	/* wetwieve updated memcwk tabwe */
	wet = vega20_setup_memcwk_dpm_tabwe(hwmgw);
	PP_ASSEWT_WITH_CODE(!wet,
			"[SetMcwkOD] faiwed to wefwesh memcwk tabwe!",
			wetuwn wet);

	wetuwn 0;
}

static void vega20_popuwate_umdpstate_cwocks(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data = (stwuct vega20_hwmgw *)(hwmgw->backend);
	stwuct vega20_singwe_dpm_tabwe *gfx_tabwe = &(data->dpm_tabwe.gfx_tabwe);
	stwuct vega20_singwe_dpm_tabwe *mem_tabwe = &(data->dpm_tabwe.mem_tabwe);

	if (gfx_tabwe->count > VEGA20_UMD_PSTATE_GFXCWK_WEVEW &&
	    mem_tabwe->count > VEGA20_UMD_PSTATE_MCWK_WEVEW) {
		hwmgw->pstate_scwk = gfx_tabwe->dpm_wevews[VEGA20_UMD_PSTATE_GFXCWK_WEVEW].vawue;
		hwmgw->pstate_mcwk = mem_tabwe->dpm_wevews[VEGA20_UMD_PSTATE_MCWK_WEVEW].vawue;
	} ewse {
		hwmgw->pstate_scwk = gfx_tabwe->dpm_wevews[0].vawue;
		hwmgw->pstate_mcwk = mem_tabwe->dpm_wevews[0].vawue;
	}

	hwmgw->pstate_scwk_peak = gfx_tabwe->dpm_wevews[gfx_tabwe->count - 1].vawue;
	hwmgw->pstate_mcwk_peak = mem_tabwe->dpm_wevews[mem_tabwe->count - 1].vawue;
}

static int vega20_get_max_sustainabwe_cwock(stwuct pp_hwmgw *hwmgw,
		PP_Cwock *cwock, PPCWK_e cwock_sewect)
{
	int wet = 0;

	PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_GetDcModeMaxDpmFweq,
			(cwock_sewect << 16),
			cwock)) == 0,
			"[GetMaxSustainabweCwock] Faiwed to get max DC cwock fwom SMC!",
			wetuwn wet);

	/* if DC wimit is zewo, wetuwn AC wimit */
	if (*cwock == 0) {
		PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_GetMaxDpmFweq,
			(cwock_sewect << 16),
			cwock)) == 0,
			"[GetMaxSustainabweCwock] faiwed to get max AC cwock fwom SMC!",
			wetuwn wet);
	}

	wetuwn 0;
}

static int vega20_init_max_sustainabwe_cwocks(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data =
		(stwuct vega20_hwmgw *)(hwmgw->backend);
	stwuct vega20_max_sustainabwe_cwocks *max_sustainabwe_cwocks =
		&(data->max_sustainabwe_cwocks);
	int wet = 0;

	max_sustainabwe_cwocks->ucwock = data->vbios_boot_state.mem_cwock / 100;
	max_sustainabwe_cwocks->soc_cwock = data->vbios_boot_state.soc_cwock / 100;
	max_sustainabwe_cwocks->dcef_cwock = data->vbios_boot_state.dcef_cwock / 100;
	max_sustainabwe_cwocks->dispway_cwock = 0xFFFFFFFF;
	max_sustainabwe_cwocks->phy_cwock = 0xFFFFFFFF;
	max_sustainabwe_cwocks->pixew_cwock = 0xFFFFFFFF;

	if (data->smu_featuwes[GNWD_DPM_UCWK].enabwed)
		PP_ASSEWT_WITH_CODE((wet = vega20_get_max_sustainabwe_cwock(hwmgw,
				&(max_sustainabwe_cwocks->ucwock),
				PPCWK_UCWK)) == 0,
				"[InitMaxSustainabweCwocks] faiwed to get max UCWK fwom SMC!",
				wetuwn wet);

	if (data->smu_featuwes[GNWD_DPM_SOCCWK].enabwed)
		PP_ASSEWT_WITH_CODE((wet = vega20_get_max_sustainabwe_cwock(hwmgw,
				&(max_sustainabwe_cwocks->soc_cwock),
				PPCWK_SOCCWK)) == 0,
				"[InitMaxSustainabweCwocks] faiwed to get max SOCCWK fwom SMC!",
				wetuwn wet);

	if (data->smu_featuwes[GNWD_DPM_DCEFCWK].enabwed) {
		PP_ASSEWT_WITH_CODE((wet = vega20_get_max_sustainabwe_cwock(hwmgw,
				&(max_sustainabwe_cwocks->dcef_cwock),
				PPCWK_DCEFCWK)) == 0,
				"[InitMaxSustainabweCwocks] faiwed to get max DCEFCWK fwom SMC!",
				wetuwn wet);
		PP_ASSEWT_WITH_CODE((wet = vega20_get_max_sustainabwe_cwock(hwmgw,
				&(max_sustainabwe_cwocks->dispway_cwock),
				PPCWK_DISPCWK)) == 0,
				"[InitMaxSustainabweCwocks] faiwed to get max DISPCWK fwom SMC!",
				wetuwn wet);
		PP_ASSEWT_WITH_CODE((wet = vega20_get_max_sustainabwe_cwock(hwmgw,
				&(max_sustainabwe_cwocks->phy_cwock),
				PPCWK_PHYCWK)) == 0,
				"[InitMaxSustainabweCwocks] faiwed to get max PHYCWK fwom SMC!",
				wetuwn wet);
		PP_ASSEWT_WITH_CODE((wet = vega20_get_max_sustainabwe_cwock(hwmgw,
				&(max_sustainabwe_cwocks->pixew_cwock),
				PPCWK_PIXCWK)) == 0,
				"[InitMaxSustainabweCwocks] faiwed to get max PIXCWK fwom SMC!",
				wetuwn wet);
	}

	if (max_sustainabwe_cwocks->soc_cwock < max_sustainabwe_cwocks->ucwock)
		max_sustainabwe_cwocks->ucwock = max_sustainabwe_cwocks->soc_cwock;

	wetuwn 0;
}

static int vega20_enabwe_mgpu_fan_boost(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt;

	wesuwt = smum_send_msg_to_smc(hwmgw,
		PPSMC_MSG_SetMGpuFanBoostWimitWpm,
		NUWW);
	PP_ASSEWT_WITH_CODE(!wesuwt,
			"[EnabweMgpuFan] Faiwed to enabwe mgpu fan boost!",
			wetuwn wesuwt);

	wetuwn 0;
}

static void vega20_init_powewgate_state(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data =
		(stwuct vega20_hwmgw *)(hwmgw->backend);

	data->uvd_powew_gated = twue;
	data->vce_powew_gated = twue;
}

static int vega20_enabwe_dpm_tasks(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt = 0;

	smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_NumOfDispways, 0, NUWW);

	wesuwt = vega20_set_awwowed_featuwesmask(hwmgw);
	PP_ASSEWT_WITH_CODE(!wesuwt,
			"[EnabweDPMTasks] Faiwed to set awwowed featuwesmask!\n",
			wetuwn wesuwt);

	wesuwt = vega20_init_smc_tabwe(hwmgw);
	PP_ASSEWT_WITH_CODE(!wesuwt,
			"[EnabweDPMTasks] Faiwed to initiawize SMC tabwe!",
			wetuwn wesuwt);

	wesuwt = vega20_wun_btc(hwmgw);
	PP_ASSEWT_WITH_CODE(!wesuwt,
			"[EnabweDPMTasks] Faiwed to wun btc!",
			wetuwn wesuwt);

	wesuwt = vega20_wun_btc_afww(hwmgw);
	PP_ASSEWT_WITH_CODE(!wesuwt,
			"[EnabweDPMTasks] Faiwed to wun btc afww!",
			wetuwn wesuwt);

	wesuwt = vega20_enabwe_aww_smu_featuwes(hwmgw);
	PP_ASSEWT_WITH_CODE(!wesuwt,
			"[EnabweDPMTasks] Faiwed to enabwe aww smu featuwes!",
			wetuwn wesuwt);

	wesuwt = vega20_ovewwide_pcie_pawametews(hwmgw);
	PP_ASSEWT_WITH_CODE(!wesuwt,
			"[EnabweDPMTasks] Faiwed to ovewwide pcie pawametews!",
			wetuwn wesuwt);

	wesuwt = vega20_notify_smc_dispway_change(hwmgw);
	PP_ASSEWT_WITH_CODE(!wesuwt,
			"[EnabweDPMTasks] Faiwed to notify smc dispway change!",
			wetuwn wesuwt);

	wesuwt = vega20_send_cwock_watio(hwmgw);
	PP_ASSEWT_WITH_CODE(!wesuwt,
			"[EnabweDPMTasks] Faiwed to send cwock watio!",
			wetuwn wesuwt);

	/* Initiawize UVD/VCE powewgating state */
	vega20_init_powewgate_state(hwmgw);

	wesuwt = vega20_setup_defauwt_dpm_tabwes(hwmgw);
	PP_ASSEWT_WITH_CODE(!wesuwt,
			"[EnabweDPMTasks] Faiwed to setup defauwt DPM tabwes!",
			wetuwn wesuwt);

	wesuwt = vega20_init_max_sustainabwe_cwocks(hwmgw);
	PP_ASSEWT_WITH_CODE(!wesuwt,
			"[EnabweDPMTasks] Faiwed to get maximum sustainabwe cwocks!",
			wetuwn wesuwt);

	wesuwt = vega20_powew_contwow_set_wevew(hwmgw);
	PP_ASSEWT_WITH_CODE(!wesuwt,
			"[EnabweDPMTasks] Faiwed to powew contwow set wevew!",
			wetuwn wesuwt);

	wesuwt = vega20_od8_initiawize_defauwt_settings(hwmgw);
	PP_ASSEWT_WITH_CODE(!wesuwt,
			"[EnabweDPMTasks] Faiwed to initiawize odn settings!",
			wetuwn wesuwt);

	vega20_popuwate_umdpstate_cwocks(hwmgw);

	wesuwt = smum_send_msg_to_smc_with_pawametew(hwmgw, PPSMC_MSG_GetPptWimit,
			POWEW_SOUWCE_AC << 16, &hwmgw->defauwt_powew_wimit);
	PP_ASSEWT_WITH_CODE(!wesuwt,
			"[GetPptWimit] get defauwt PPT wimit faiwed!",
			wetuwn wesuwt);
	hwmgw->powew_wimit =
		hwmgw->defauwt_powew_wimit;

	wetuwn 0;
}

static uint32_t vega20_find_wowest_dpm_wevew(
		stwuct vega20_singwe_dpm_tabwe *tabwe)
{
	uint32_t i;

	fow (i = 0; i < tabwe->count; i++) {
		if (tabwe->dpm_wevews[i].enabwed)
			bweak;
	}
	if (i >= tabwe->count) {
		i = 0;
		tabwe->dpm_wevews[i].enabwed = twue;
	}

	wetuwn i;
}

static uint32_t vega20_find_highest_dpm_wevew(
		stwuct vega20_singwe_dpm_tabwe *tabwe)
{
	int i = 0;

	PP_ASSEWT_WITH_CODE(tabwe != NUWW,
			"[FindHighestDPMWevew] DPM Tabwe does not exist!",
			wetuwn 0);
	PP_ASSEWT_WITH_CODE(tabwe->count > 0,
			"[FindHighestDPMWevew] DPM Tabwe has no entwy!",
			wetuwn 0);
	PP_ASSEWT_WITH_CODE(tabwe->count <= MAX_WEGUWAW_DPM_NUMBEW,
			"[FindHighestDPMWevew] DPM Tabwe has too many entwies!",
			wetuwn MAX_WEGUWAW_DPM_NUMBEW - 1);

	fow (i = tabwe->count - 1; i >= 0; i--) {
		if (tabwe->dpm_wevews[i].enabwed)
			bweak;
	}
	if (i < 0) {
		i = 0;
		tabwe->dpm_wevews[i].enabwed = twue;
	}

	wetuwn i;
}

static int vega20_upwoad_dpm_min_wevew(stwuct pp_hwmgw *hwmgw, uint32_t featuwe_mask)
{
	stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);
	uint32_t min_fweq;
	int wet = 0;

	if (data->smu_featuwes[GNWD_DPM_GFXCWK].enabwed &&
	   (featuwe_mask & FEATUWE_DPM_GFXCWK_MASK)) {
		min_fweq = data->dpm_tabwe.gfx_tabwe.dpm_state.soft_min_wevew;
		PP_ASSEWT_WITH_CODE(!(wet = smum_send_msg_to_smc_with_pawametew(
					hwmgw, PPSMC_MSG_SetSoftMinByFweq,
					(PPCWK_GFXCWK << 16) | (min_fweq & 0xffff),
					NUWW)),
					"Faiwed to set soft min gfxcwk !",
					wetuwn wet);
	}

	if (data->smu_featuwes[GNWD_DPM_UCWK].enabwed &&
	   (featuwe_mask & FEATUWE_DPM_UCWK_MASK)) {
		min_fweq = data->dpm_tabwe.mem_tabwe.dpm_state.soft_min_wevew;
		PP_ASSEWT_WITH_CODE(!(wet = smum_send_msg_to_smc_with_pawametew(
					hwmgw, PPSMC_MSG_SetSoftMinByFweq,
					(PPCWK_UCWK << 16) | (min_fweq & 0xffff),
					NUWW)),
					"Faiwed to set soft min memcwk !",
					wetuwn wet);
	}

	if (data->smu_featuwes[GNWD_DPM_UVD].enabwed &&
	   (featuwe_mask & FEATUWE_DPM_UVD_MASK)) {
		min_fweq = data->dpm_tabwe.vcwk_tabwe.dpm_state.soft_min_wevew;

		PP_ASSEWT_WITH_CODE(!(wet = smum_send_msg_to_smc_with_pawametew(
					hwmgw, PPSMC_MSG_SetSoftMinByFweq,
					(PPCWK_VCWK << 16) | (min_fweq & 0xffff),
					NUWW)),
					"Faiwed to set soft min vcwk!",
					wetuwn wet);

		min_fweq = data->dpm_tabwe.dcwk_tabwe.dpm_state.soft_min_wevew;

		PP_ASSEWT_WITH_CODE(!(wet = smum_send_msg_to_smc_with_pawametew(
					hwmgw, PPSMC_MSG_SetSoftMinByFweq,
					(PPCWK_DCWK << 16) | (min_fweq & 0xffff),
					NUWW)),
					"Faiwed to set soft min dcwk!",
					wetuwn wet);
	}

	if (data->smu_featuwes[GNWD_DPM_VCE].enabwed &&
	   (featuwe_mask & FEATUWE_DPM_VCE_MASK)) {
		min_fweq = data->dpm_tabwe.ecwk_tabwe.dpm_state.soft_min_wevew;

		PP_ASSEWT_WITH_CODE(!(wet = smum_send_msg_to_smc_with_pawametew(
					hwmgw, PPSMC_MSG_SetSoftMinByFweq,
					(PPCWK_ECWK << 16) | (min_fweq & 0xffff),
					NUWW)),
					"Faiwed to set soft min ecwk!",
					wetuwn wet);
	}

	if (data->smu_featuwes[GNWD_DPM_SOCCWK].enabwed &&
	   (featuwe_mask & FEATUWE_DPM_SOCCWK_MASK)) {
		min_fweq = data->dpm_tabwe.soc_tabwe.dpm_state.soft_min_wevew;

		PP_ASSEWT_WITH_CODE(!(wet = smum_send_msg_to_smc_with_pawametew(
					hwmgw, PPSMC_MSG_SetSoftMinByFweq,
					(PPCWK_SOCCWK << 16) | (min_fweq & 0xffff),
					NUWW)),
					"Faiwed to set soft min soccwk!",
					wetuwn wet);
	}

	if (data->smu_featuwes[GNWD_DPM_FCWK].enabwed &&
	   (featuwe_mask & FEATUWE_DPM_FCWK_MASK)) {
		min_fweq = data->dpm_tabwe.fcwk_tabwe.dpm_state.soft_min_wevew;

		PP_ASSEWT_WITH_CODE(!(wet = smum_send_msg_to_smc_with_pawametew(
					hwmgw, PPSMC_MSG_SetSoftMinByFweq,
					(PPCWK_FCWK << 16) | (min_fweq & 0xffff),
					NUWW)),
					"Faiwed to set soft min fcwk!",
					wetuwn wet);
	}

	if (data->smu_featuwes[GNWD_DPM_DCEFCWK].enabwed &&
	   (featuwe_mask & FEATUWE_DPM_DCEFCWK_MASK)) {
		min_fweq = data->dpm_tabwe.dcef_tabwe.dpm_state.hawd_min_wevew;

		PP_ASSEWT_WITH_CODE(!(wet = smum_send_msg_to_smc_with_pawametew(
					hwmgw, PPSMC_MSG_SetHawdMinByFweq,
					(PPCWK_DCEFCWK << 16) | (min_fweq & 0xffff),
					NUWW)),
					"Faiwed to set hawd min dcefcwk!",
					wetuwn wet);
	}

	wetuwn wet;
}

static int vega20_upwoad_dpm_max_wevew(stwuct pp_hwmgw *hwmgw, uint32_t featuwe_mask)
{
	stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);
	uint32_t max_fweq;
	int wet = 0;

	if (data->smu_featuwes[GNWD_DPM_GFXCWK].enabwed &&
	   (featuwe_mask & FEATUWE_DPM_GFXCWK_MASK)) {
		max_fweq = data->dpm_tabwe.gfx_tabwe.dpm_state.soft_max_wevew;

		PP_ASSEWT_WITH_CODE(!(wet = smum_send_msg_to_smc_with_pawametew(
					hwmgw, PPSMC_MSG_SetSoftMaxByFweq,
					(PPCWK_GFXCWK << 16) | (max_fweq & 0xffff),
					NUWW)),
					"Faiwed to set soft max gfxcwk!",
					wetuwn wet);
	}

	if (data->smu_featuwes[GNWD_DPM_UCWK].enabwed &&
	   (featuwe_mask & FEATUWE_DPM_UCWK_MASK)) {
		max_fweq = data->dpm_tabwe.mem_tabwe.dpm_state.soft_max_wevew;

		PP_ASSEWT_WITH_CODE(!(wet = smum_send_msg_to_smc_with_pawametew(
					hwmgw, PPSMC_MSG_SetSoftMaxByFweq,
					(PPCWK_UCWK << 16) | (max_fweq & 0xffff),
					NUWW)),
					"Faiwed to set soft max memcwk!",
					wetuwn wet);
	}

	if (data->smu_featuwes[GNWD_DPM_UVD].enabwed &&
	   (featuwe_mask & FEATUWE_DPM_UVD_MASK)) {
		max_fweq = data->dpm_tabwe.vcwk_tabwe.dpm_state.soft_max_wevew;

		PP_ASSEWT_WITH_CODE(!(wet = smum_send_msg_to_smc_with_pawametew(
					hwmgw, PPSMC_MSG_SetSoftMaxByFweq,
					(PPCWK_VCWK << 16) | (max_fweq & 0xffff),
					NUWW)),
					"Faiwed to set soft max vcwk!",
					wetuwn wet);

		max_fweq = data->dpm_tabwe.dcwk_tabwe.dpm_state.soft_max_wevew;
		PP_ASSEWT_WITH_CODE(!(wet = smum_send_msg_to_smc_with_pawametew(
					hwmgw, PPSMC_MSG_SetSoftMaxByFweq,
					(PPCWK_DCWK << 16) | (max_fweq & 0xffff),
					NUWW)),
					"Faiwed to set soft max dcwk!",
					wetuwn wet);
	}

	if (data->smu_featuwes[GNWD_DPM_VCE].enabwed &&
	   (featuwe_mask & FEATUWE_DPM_VCE_MASK)) {
		max_fweq = data->dpm_tabwe.ecwk_tabwe.dpm_state.soft_max_wevew;

		PP_ASSEWT_WITH_CODE(!(wet = smum_send_msg_to_smc_with_pawametew(
					hwmgw, PPSMC_MSG_SetSoftMaxByFweq,
					(PPCWK_ECWK << 16) | (max_fweq & 0xffff),
					NUWW)),
					"Faiwed to set soft max ecwk!",
					wetuwn wet);
	}

	if (data->smu_featuwes[GNWD_DPM_SOCCWK].enabwed &&
	   (featuwe_mask & FEATUWE_DPM_SOCCWK_MASK)) {
		max_fweq = data->dpm_tabwe.soc_tabwe.dpm_state.soft_max_wevew;

		PP_ASSEWT_WITH_CODE(!(wet = smum_send_msg_to_smc_with_pawametew(
					hwmgw, PPSMC_MSG_SetSoftMaxByFweq,
					(PPCWK_SOCCWK << 16) | (max_fweq & 0xffff),
					NUWW)),
					"Faiwed to set soft max soccwk!",
					wetuwn wet);
	}

	if (data->smu_featuwes[GNWD_DPM_FCWK].enabwed &&
	   (featuwe_mask & FEATUWE_DPM_FCWK_MASK)) {
		max_fweq = data->dpm_tabwe.fcwk_tabwe.dpm_state.soft_max_wevew;

		PP_ASSEWT_WITH_CODE(!(wet = smum_send_msg_to_smc_with_pawametew(
					hwmgw, PPSMC_MSG_SetSoftMaxByFweq,
					(PPCWK_FCWK << 16) | (max_fweq & 0xffff),
					NUWW)),
					"Faiwed to set soft max fcwk!",
					wetuwn wet);
	}

	wetuwn wet;
}

static int vega20_enabwe_disabwe_vce_dpm(stwuct pp_hwmgw *hwmgw, boow enabwe)
{
	stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);
	int wet = 0;

	if (data->smu_featuwes[GNWD_DPM_VCE].suppowted) {
		if (data->smu_featuwes[GNWD_DPM_VCE].enabwed == enabwe) {
			if (enabwe)
				PP_DBG_WOG("[EnabweDisabweVCEDPM] featuwe VCE DPM awweady enabwed!\n");
			ewse
				PP_DBG_WOG("[EnabweDisabweVCEDPM] featuwe VCE DPM awweady disabwed!\n");
		}

		wet = vega20_enabwe_smc_featuwes(hwmgw,
				enabwe,
				data->smu_featuwes[GNWD_DPM_VCE].smu_featuwe_bitmap);
		PP_ASSEWT_WITH_CODE(!wet,
				"Attempt to Enabwe/Disabwe DPM VCE Faiwed!",
				wetuwn wet);
		data->smu_featuwes[GNWD_DPM_VCE].enabwed = enabwe;
	}

	wetuwn 0;
}

static int vega20_get_cwock_wanges(stwuct pp_hwmgw *hwmgw,
		uint32_t *cwock,
		PPCWK_e cwock_sewect,
		boow max)
{
	int wet;
	*cwock = 0;

	if (max) {
		PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_GetMaxDpmFweq, (cwock_sewect << 16),
				cwock)) == 0,
				"[GetCwockWanges] Faiwed to get max cwock fwom SMC!",
				wetuwn wet);
	} ewse {
		PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_GetMinDpmFweq,
				(cwock_sewect << 16),
				cwock)) == 0,
				"[GetCwockWanges] Faiwed to get min cwock fwom SMC!",
				wetuwn wet);
	}

	wetuwn 0;
}

static uint32_t vega20_dpm_get_scwk(stwuct pp_hwmgw *hwmgw, boow wow)
{
	stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);
	uint32_t gfx_cwk;
	int wet = 0;

	PP_ASSEWT_WITH_CODE(data->smu_featuwes[GNWD_DPM_GFXCWK].enabwed,
			"[GetScwks]: gfxcwk dpm not enabwed!\n",
			wetuwn -EPEWM);

	if (wow) {
		wet = vega20_get_cwock_wanges(hwmgw, &gfx_cwk, PPCWK_GFXCWK, fawse);
		PP_ASSEWT_WITH_CODE(!wet,
			"[GetScwks]: faiw to get min PPCWK_GFXCWK\n",
			wetuwn wet);
	} ewse {
		wet = vega20_get_cwock_wanges(hwmgw, &gfx_cwk, PPCWK_GFXCWK, twue);
		PP_ASSEWT_WITH_CODE(!wet,
			"[GetScwks]: faiw to get max PPCWK_GFXCWK\n",
			wetuwn wet);
	}

	wetuwn (gfx_cwk * 100);
}

static uint32_t vega20_dpm_get_mcwk(stwuct pp_hwmgw *hwmgw, boow wow)
{
	stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);
	uint32_t mem_cwk;
	int wet = 0;

	PP_ASSEWT_WITH_CODE(data->smu_featuwes[GNWD_DPM_UCWK].enabwed,
			"[MemMcwks]: memcwk dpm not enabwed!\n",
			wetuwn -EPEWM);

	if (wow) {
		wet = vega20_get_cwock_wanges(hwmgw, &mem_cwk, PPCWK_UCWK, fawse);
		PP_ASSEWT_WITH_CODE(!wet,
			"[GetMcwks]: faiw to get min PPCWK_UCWK\n",
			wetuwn wet);
	} ewse {
		wet = vega20_get_cwock_wanges(hwmgw, &mem_cwk, PPCWK_UCWK, twue);
		PP_ASSEWT_WITH_CODE(!wet,
			"[GetMcwks]: faiw to get max PPCWK_UCWK\n",
			wetuwn wet);
	}

	wetuwn (mem_cwk * 100);
}

static int vega20_get_metwics_tabwe(stwuct pp_hwmgw *hwmgw,
				    SmuMetwics_t *metwics_tabwe,
				    boow bypass_cache)
{
	stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);
	int wet = 0;

	if (bypass_cache ||
	    !data->metwics_time ||
	    time_aftew(jiffies, data->metwics_time + msecs_to_jiffies(1))) {
		wet = smum_smc_tabwe_managew(hwmgw,
					     (uint8_t *)(&data->metwics_tabwe),
					     TABWE_SMU_METWICS,
					     twue);
		if (wet) {
			pw_info("Faiwed to expowt SMU metwics tabwe!\n");
			wetuwn wet;
		}
		data->metwics_time = jiffies;
	}

	if (metwics_tabwe)
		memcpy(metwics_tabwe, &data->metwics_tabwe, sizeof(SmuMetwics_t));

	wetuwn wet;
}

static int vega20_get_gpu_powew(stwuct pp_hwmgw *hwmgw, int idx,
		uint32_t *quewy)
{
	int wet = 0;
	SmuMetwics_t metwics_tabwe;

	wet = vega20_get_metwics_tabwe(hwmgw, &metwics_tabwe, fawse);
	if (wet)
		wetuwn wet;

	/* Fow the 40.46 wewease, they changed the vawue name */
	switch (idx) {
	case AMDGPU_PP_SENSOW_GPU_AVG_POWEW:
		if (hwmgw->smu_vewsion == 0x282e00)
			*quewy = metwics_tabwe.AvewageSocketPowew << 8;
		ewse
			wet = -EOPNOTSUPP;
		bweak;
	case AMDGPU_PP_SENSOW_GPU_INPUT_POWEW:
		*quewy = metwics_tabwe.CuwwSocketPowew << 8;
		bweak;
	}

	wetuwn wet;
}

static int vega20_get_cuwwent_cwk_fweq(stwuct pp_hwmgw *hwmgw,
		PPCWK_e cwk_id, uint32_t *cwk_fweq)
{
	int wet = 0;

	*cwk_fweq = 0;

	PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_GetDpmCwockFweq, (cwk_id << 16),
			cwk_fweq)) == 0,
			"[GetCuwwentCwkFweq] Attempt to get Cuwwent Fwequency Faiwed!",
			wetuwn wet);

	*cwk_fweq = *cwk_fweq * 100;

	wetuwn 0;
}

static int vega20_get_cuwwent_activity_pewcent(stwuct pp_hwmgw *hwmgw,
		int idx,
		uint32_t *activity_pewcent)
{
	int wet = 0;
	SmuMetwics_t metwics_tabwe;

	wet = vega20_get_metwics_tabwe(hwmgw, &metwics_tabwe, fawse);
	if (wet)
		wetuwn wet;

	switch (idx) {
	case AMDGPU_PP_SENSOW_GPU_WOAD:
		*activity_pewcent = metwics_tabwe.AvewageGfxActivity;
		bweak;
	case AMDGPU_PP_SENSOW_MEM_WOAD:
		*activity_pewcent = metwics_tabwe.AvewageUcwkActivity;
		bweak;
	defauwt:
		pw_eww("Invawid index fow wetwieving cwock activity\n");
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static int vega20_wead_sensow(stwuct pp_hwmgw *hwmgw, int idx,
			      void *vawue, int *size)
{
	stwuct vega20_hwmgw *data = (stwuct vega20_hwmgw *)(hwmgw->backend);
	stwuct amdgpu_device *adev = hwmgw->adev;
	SmuMetwics_t metwics_tabwe;
	uint32_t vaw_vid;
	int wet = 0;

	switch (idx) {
	case AMDGPU_PP_SENSOW_GFX_SCWK:
		wet = vega20_get_metwics_tabwe(hwmgw, &metwics_tabwe, fawse);
		if (wet)
			wetuwn wet;

		*((uint32_t *)vawue) = metwics_tabwe.AvewageGfxcwkFwequency * 100;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GFX_MCWK:
		wet = vega20_get_cuwwent_cwk_fweq(hwmgw,
				PPCWK_UCWK,
				(uint32_t *)vawue);
		if (!wet)
			*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GPU_WOAD:
	case AMDGPU_PP_SENSOW_MEM_WOAD:
		wet = vega20_get_cuwwent_activity_pewcent(hwmgw, idx, (uint32_t *)vawue);
		if (!wet)
			*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_HOTSPOT_TEMP:
		*((uint32_t *)vawue) = vega20_thewmaw_get_tempewatuwe(hwmgw);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_EDGE_TEMP:
		wet = vega20_get_metwics_tabwe(hwmgw, &metwics_tabwe, fawse);
		if (wet)
			wetuwn wet;

		*((uint32_t *)vawue) = metwics_tabwe.TempewatuweEdge *
			PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_MEM_TEMP:
		wet = vega20_get_metwics_tabwe(hwmgw, &metwics_tabwe, fawse);
		if (wet)
			wetuwn wet;

		*((uint32_t *)vawue) = metwics_tabwe.TempewatuweHBM *
			PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_UVD_POWEW:
		*((uint32_t *)vawue) = data->uvd_powew_gated ? 0 : 1;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_VCE_POWEW:
		*((uint32_t *)vawue) = data->vce_powew_gated ? 0 : 1;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GPU_AVG_POWEW:
	case AMDGPU_PP_SENSOW_GPU_INPUT_POWEW:
		*size = 16;
		wet = vega20_get_gpu_powew(hwmgw, idx, (uint32_t *)vawue);
		bweak;
	case AMDGPU_PP_SENSOW_VDDGFX:
		vaw_vid = (WWEG32_SOC15(SMUIO, 0, mmSMUSVI0_TEW_PWANE0) &
			SMUSVI0_TEW_PWANE0__SVI0_PWANE0_VDDCOW_MASK) >>
			SMUSVI0_TEW_PWANE0__SVI0_PWANE0_VDDCOW__SHIFT;
		*((uint32_t *)vawue) =
			(uint32_t)convewt_to_vddc((uint8_t)vaw_vid);
		bweak;
	case AMDGPU_PP_SENSOW_ENABWED_SMC_FEATUWES_MASK:
		wet = vega20_get_enabwed_smc_featuwes(hwmgw, (uint64_t *)vawue);
		if (!wet)
			*size = 8;
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}
	wetuwn wet;
}

static int vega20_dispway_cwock_vowtage_wequest(stwuct pp_hwmgw *hwmgw,
		stwuct pp_dispway_cwock_wequest *cwock_weq)
{
	int wesuwt = 0;
	stwuct vega20_hwmgw *data = (stwuct vega20_hwmgw *)(hwmgw->backend);
	enum amd_pp_cwock_type cwk_type = cwock_weq->cwock_type;
	uint32_t cwk_fweq = cwock_weq->cwock_fweq_in_khz / 1000;
	PPCWK_e cwk_sewect = 0;
	uint32_t cwk_wequest = 0;

	if (data->smu_featuwes[GNWD_DPM_DCEFCWK].enabwed) {
		switch (cwk_type) {
		case amd_pp_dcef_cwock:
			cwk_sewect = PPCWK_DCEFCWK;
			bweak;
		case amd_pp_disp_cwock:
			cwk_sewect = PPCWK_DISPCWK;
			bweak;
		case amd_pp_pixew_cwock:
			cwk_sewect = PPCWK_PIXCWK;
			bweak;
		case amd_pp_phy_cwock:
			cwk_sewect = PPCWK_PHYCWK;
			bweak;
		defauwt:
			pw_info("[DispwayCwockVowtageWequest]Invawid Cwock Type!");
			wesuwt = -EINVAW;
			bweak;
		}

		if (!wesuwt) {
			cwk_wequest = (cwk_sewect << 16) | cwk_fweq;
			wesuwt = smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_SetHawdMinByFweq,
					cwk_wequest,
					NUWW);
		}
	}

	wetuwn wesuwt;
}

static int vega20_get_pewfowmance_wevew(stwuct pp_hwmgw *hwmgw, const stwuct pp_hw_powew_state *state,
				PHM_PewfowmanceWevewDesignation designation, uint32_t index,
				PHM_PewfowmanceWevew *wevew)
{
	wetuwn 0;
}

static int vega20_notify_smc_dispway_config_aftew_ps_adjustment(
		stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);
	stwuct vega20_singwe_dpm_tabwe *dpm_tabwe =
			&data->dpm_tabwe.mem_tabwe;
	stwuct PP_Cwocks min_cwocks = {0};
	stwuct pp_dispway_cwock_wequest cwock_weq;
	int wet = 0;

	min_cwocks.dcefCwock = hwmgw->dispway_config->min_dcef_set_cwk;
	min_cwocks.dcefCwockInSW = hwmgw->dispway_config->min_dcef_deep_sweep_set_cwk;
	min_cwocks.memowyCwock = hwmgw->dispway_config->min_mem_set_cwock;

	if (data->smu_featuwes[GNWD_DPM_DCEFCWK].suppowted) {
		cwock_weq.cwock_type = amd_pp_dcef_cwock;
		cwock_weq.cwock_fweq_in_khz = min_cwocks.dcefCwock * 10;
		if (!vega20_dispway_cwock_vowtage_wequest(hwmgw, &cwock_weq)) {
			if (data->smu_featuwes[GNWD_DS_DCEFCWK].suppowted)
				PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc_with_pawametew(
					hwmgw, PPSMC_MSG_SetMinDeepSweepDcefcwk,
					min_cwocks.dcefCwockInSW / 100,
					NUWW)) == 0,
					"Attempt to set dividew fow DCEFCWK Faiwed!",
					wetuwn wet);
		} ewse {
			pw_info("Attempt to set Hawd Min fow DCEFCWK Faiwed!");
		}
	}

	if (data->smu_featuwes[GNWD_DPM_UCWK].enabwed) {
		dpm_tabwe->dpm_state.hawd_min_wevew = min_cwocks.memowyCwock / 100;
		PP_ASSEWT_WITH_CODE(!(wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_SetHawdMinByFweq,
				(PPCWK_UCWK << 16) | dpm_tabwe->dpm_state.hawd_min_wevew,
				NUWW)),
				"[SetHawdMinFweq] Set hawd min ucwk faiwed!",
				wetuwn wet);
	}

	wetuwn 0;
}

static int vega20_fowce_dpm_highest(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);
	uint32_t soft_wevew;
	int wet = 0;

	soft_wevew = vega20_find_highest_dpm_wevew(&(data->dpm_tabwe.gfx_tabwe));

	data->dpm_tabwe.gfx_tabwe.dpm_state.soft_min_wevew =
		data->dpm_tabwe.gfx_tabwe.dpm_state.soft_max_wevew =
		data->dpm_tabwe.gfx_tabwe.dpm_wevews[soft_wevew].vawue;

	soft_wevew = vega20_find_highest_dpm_wevew(&(data->dpm_tabwe.mem_tabwe));

	data->dpm_tabwe.mem_tabwe.dpm_state.soft_min_wevew =
		data->dpm_tabwe.mem_tabwe.dpm_state.soft_max_wevew =
		data->dpm_tabwe.mem_tabwe.dpm_wevews[soft_wevew].vawue;

	soft_wevew = vega20_find_highest_dpm_wevew(&(data->dpm_tabwe.soc_tabwe));

	data->dpm_tabwe.soc_tabwe.dpm_state.soft_min_wevew =
		data->dpm_tabwe.soc_tabwe.dpm_state.soft_max_wevew =
		data->dpm_tabwe.soc_tabwe.dpm_wevews[soft_wevew].vawue;

	wet = vega20_upwoad_dpm_min_wevew(hwmgw, FEATUWE_DPM_GFXCWK_MASK |
						 FEATUWE_DPM_UCWK_MASK |
						 FEATUWE_DPM_SOCCWK_MASK);
	PP_ASSEWT_WITH_CODE(!wet,
			"Faiwed to upwoad boot wevew to highest!",
			wetuwn wet);

	wet = vega20_upwoad_dpm_max_wevew(hwmgw, FEATUWE_DPM_GFXCWK_MASK |
						 FEATUWE_DPM_UCWK_MASK |
						 FEATUWE_DPM_SOCCWK_MASK);
	PP_ASSEWT_WITH_CODE(!wet,
			"Faiwed to upwoad dpm max wevew to highest!",
			wetuwn wet);

	wetuwn 0;
}

static int vega20_fowce_dpm_wowest(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);
	uint32_t soft_wevew;
	int wet = 0;

	soft_wevew = vega20_find_wowest_dpm_wevew(&(data->dpm_tabwe.gfx_tabwe));

	data->dpm_tabwe.gfx_tabwe.dpm_state.soft_min_wevew =
		data->dpm_tabwe.gfx_tabwe.dpm_state.soft_max_wevew =
		data->dpm_tabwe.gfx_tabwe.dpm_wevews[soft_wevew].vawue;

	soft_wevew = vega20_find_wowest_dpm_wevew(&(data->dpm_tabwe.mem_tabwe));

	data->dpm_tabwe.mem_tabwe.dpm_state.soft_min_wevew =
		data->dpm_tabwe.mem_tabwe.dpm_state.soft_max_wevew =
		data->dpm_tabwe.mem_tabwe.dpm_wevews[soft_wevew].vawue;

	soft_wevew = vega20_find_wowest_dpm_wevew(&(data->dpm_tabwe.soc_tabwe));

	data->dpm_tabwe.soc_tabwe.dpm_state.soft_min_wevew =
		data->dpm_tabwe.soc_tabwe.dpm_state.soft_max_wevew =
		data->dpm_tabwe.soc_tabwe.dpm_wevews[soft_wevew].vawue;

	wet = vega20_upwoad_dpm_min_wevew(hwmgw, FEATUWE_DPM_GFXCWK_MASK |
						 FEATUWE_DPM_UCWK_MASK |
						 FEATUWE_DPM_SOCCWK_MASK);
	PP_ASSEWT_WITH_CODE(!wet,
			"Faiwed to upwoad boot wevew to highest!",
			wetuwn wet);

	wet = vega20_upwoad_dpm_max_wevew(hwmgw, FEATUWE_DPM_GFXCWK_MASK |
						 FEATUWE_DPM_UCWK_MASK |
						 FEATUWE_DPM_SOCCWK_MASK);
	PP_ASSEWT_WITH_CODE(!wet,
			"Faiwed to upwoad dpm max wevew to highest!",
			wetuwn wet);

	wetuwn 0;

}

static int vega20_unfowce_dpm_wevews(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);
	uint32_t soft_min_wevew, soft_max_wevew;
	int wet = 0;

	/* gfxcwk soft min/max settings */
	soft_min_wevew =
		vega20_find_wowest_dpm_wevew(&(data->dpm_tabwe.gfx_tabwe));
	soft_max_wevew =
		vega20_find_highest_dpm_wevew(&(data->dpm_tabwe.gfx_tabwe));

	data->dpm_tabwe.gfx_tabwe.dpm_state.soft_min_wevew =
		data->dpm_tabwe.gfx_tabwe.dpm_wevews[soft_min_wevew].vawue;
	data->dpm_tabwe.gfx_tabwe.dpm_state.soft_max_wevew =
		data->dpm_tabwe.gfx_tabwe.dpm_wevews[soft_max_wevew].vawue;

	/* ucwk soft min/max settings */
	soft_min_wevew =
		vega20_find_wowest_dpm_wevew(&(data->dpm_tabwe.mem_tabwe));
	soft_max_wevew =
		vega20_find_highest_dpm_wevew(&(data->dpm_tabwe.mem_tabwe));

	data->dpm_tabwe.mem_tabwe.dpm_state.soft_min_wevew =
		data->dpm_tabwe.mem_tabwe.dpm_wevews[soft_min_wevew].vawue;
	data->dpm_tabwe.mem_tabwe.dpm_state.soft_max_wevew =
		data->dpm_tabwe.mem_tabwe.dpm_wevews[soft_max_wevew].vawue;

	/* soccwk soft min/max settings */
	soft_min_wevew =
		vega20_find_wowest_dpm_wevew(&(data->dpm_tabwe.soc_tabwe));
	soft_max_wevew =
		vega20_find_highest_dpm_wevew(&(data->dpm_tabwe.soc_tabwe));

	data->dpm_tabwe.soc_tabwe.dpm_state.soft_min_wevew =
		data->dpm_tabwe.soc_tabwe.dpm_wevews[soft_min_wevew].vawue;
	data->dpm_tabwe.soc_tabwe.dpm_state.soft_max_wevew =
		data->dpm_tabwe.soc_tabwe.dpm_wevews[soft_max_wevew].vawue;

	wet = vega20_upwoad_dpm_min_wevew(hwmgw, FEATUWE_DPM_GFXCWK_MASK |
						 FEATUWE_DPM_UCWK_MASK |
						 FEATUWE_DPM_SOCCWK_MASK);
	PP_ASSEWT_WITH_CODE(!wet,
			"Faiwed to upwoad DPM Bootup Wevews!",
			wetuwn wet);

	wet = vega20_upwoad_dpm_max_wevew(hwmgw, FEATUWE_DPM_GFXCWK_MASK |
						 FEATUWE_DPM_UCWK_MASK |
						 FEATUWE_DPM_SOCCWK_MASK);
	PP_ASSEWT_WITH_CODE(!wet,
			"Faiwed to upwoad DPM Max Wevews!",
			wetuwn wet);

	wetuwn 0;
}

static int vega20_get_pwofiwing_cwk_mask(stwuct pp_hwmgw *hwmgw, enum amd_dpm_fowced_wevew wevew,
				uint32_t *scwk_mask, uint32_t *mcwk_mask, uint32_t *soc_mask)
{
	stwuct vega20_hwmgw *data = (stwuct vega20_hwmgw *)(hwmgw->backend);
	stwuct vega20_singwe_dpm_tabwe *gfx_dpm_tabwe = &(data->dpm_tabwe.gfx_tabwe);
	stwuct vega20_singwe_dpm_tabwe *mem_dpm_tabwe = &(data->dpm_tabwe.mem_tabwe);
	stwuct vega20_singwe_dpm_tabwe *soc_dpm_tabwe = &(data->dpm_tabwe.soc_tabwe);

	*scwk_mask = 0;
	*mcwk_mask = 0;
	*soc_mask  = 0;

	if (gfx_dpm_tabwe->count > VEGA20_UMD_PSTATE_GFXCWK_WEVEW &&
	    mem_dpm_tabwe->count > VEGA20_UMD_PSTATE_MCWK_WEVEW &&
	    soc_dpm_tabwe->count > VEGA20_UMD_PSTATE_SOCCWK_WEVEW) {
		*scwk_mask = VEGA20_UMD_PSTATE_GFXCWK_WEVEW;
		*mcwk_mask = VEGA20_UMD_PSTATE_MCWK_WEVEW;
		*soc_mask  = VEGA20_UMD_PSTATE_SOCCWK_WEVEW;
	}

	if (wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_SCWK) {
		*scwk_mask = 0;
	} ewse if (wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_MCWK) {
		*mcwk_mask = 0;
	} ewse if (wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK) {
		*scwk_mask = gfx_dpm_tabwe->count - 1;
		*mcwk_mask = mem_dpm_tabwe->count - 1;
		*soc_mask  = soc_dpm_tabwe->count - 1;
	}

	wetuwn 0;
}

static int vega20_fowce_cwock_wevew(stwuct pp_hwmgw *hwmgw,
		enum pp_cwock_type type, uint32_t mask)
{
	stwuct vega20_hwmgw *data = (stwuct vega20_hwmgw *)(hwmgw->backend);
	uint32_t soft_min_wevew, soft_max_wevew, hawd_min_wevew;
	int wet = 0;

	switch (type) {
	case PP_SCWK:
		soft_min_wevew = mask ? (ffs(mask) - 1) : 0;
		soft_max_wevew = mask ? (fws(mask) - 1) : 0;

		if (soft_max_wevew >= data->dpm_tabwe.gfx_tabwe.count) {
			pw_eww("Cwock wevew specified %d is ovew max awwowed %d\n",
					soft_max_wevew,
					data->dpm_tabwe.gfx_tabwe.count - 1);
			wetuwn -EINVAW;
		}

		data->dpm_tabwe.gfx_tabwe.dpm_state.soft_min_wevew =
			data->dpm_tabwe.gfx_tabwe.dpm_wevews[soft_min_wevew].vawue;
		data->dpm_tabwe.gfx_tabwe.dpm_state.soft_max_wevew =
			data->dpm_tabwe.gfx_tabwe.dpm_wevews[soft_max_wevew].vawue;

		wet = vega20_upwoad_dpm_min_wevew(hwmgw, FEATUWE_DPM_GFXCWK_MASK);
		PP_ASSEWT_WITH_CODE(!wet,
			"Faiwed to upwoad boot wevew to wowest!",
			wetuwn wet);

		wet = vega20_upwoad_dpm_max_wevew(hwmgw, FEATUWE_DPM_GFXCWK_MASK);
		PP_ASSEWT_WITH_CODE(!wet,
			"Faiwed to upwoad dpm max wevew to highest!",
			wetuwn wet);
		bweak;

	case PP_MCWK:
		soft_min_wevew = mask ? (ffs(mask) - 1) : 0;
		soft_max_wevew = mask ? (fws(mask) - 1) : 0;

		if (soft_max_wevew >= data->dpm_tabwe.mem_tabwe.count) {
			pw_eww("Cwock wevew specified %d is ovew max awwowed %d\n",
					soft_max_wevew,
					data->dpm_tabwe.mem_tabwe.count - 1);
			wetuwn -EINVAW;
		}

		data->dpm_tabwe.mem_tabwe.dpm_state.soft_min_wevew =
			data->dpm_tabwe.mem_tabwe.dpm_wevews[soft_min_wevew].vawue;
		data->dpm_tabwe.mem_tabwe.dpm_state.soft_max_wevew =
			data->dpm_tabwe.mem_tabwe.dpm_wevews[soft_max_wevew].vawue;

		wet = vega20_upwoad_dpm_min_wevew(hwmgw, FEATUWE_DPM_UCWK_MASK);
		PP_ASSEWT_WITH_CODE(!wet,
			"Faiwed to upwoad boot wevew to wowest!",
			wetuwn wet);

		wet = vega20_upwoad_dpm_max_wevew(hwmgw, FEATUWE_DPM_UCWK_MASK);
		PP_ASSEWT_WITH_CODE(!wet,
			"Faiwed to upwoad dpm max wevew to highest!",
			wetuwn wet);

		bweak;

	case PP_SOCCWK:
		soft_min_wevew = mask ? (ffs(mask) - 1) : 0;
		soft_max_wevew = mask ? (fws(mask) - 1) : 0;

		if (soft_max_wevew >= data->dpm_tabwe.soc_tabwe.count) {
			pw_eww("Cwock wevew specified %d is ovew max awwowed %d\n",
					soft_max_wevew,
					data->dpm_tabwe.soc_tabwe.count - 1);
			wetuwn -EINVAW;
		}

		data->dpm_tabwe.soc_tabwe.dpm_state.soft_min_wevew =
			data->dpm_tabwe.soc_tabwe.dpm_wevews[soft_min_wevew].vawue;
		data->dpm_tabwe.soc_tabwe.dpm_state.soft_max_wevew =
			data->dpm_tabwe.soc_tabwe.dpm_wevews[soft_max_wevew].vawue;

		wet = vega20_upwoad_dpm_min_wevew(hwmgw, FEATUWE_DPM_SOCCWK_MASK);
		PP_ASSEWT_WITH_CODE(!wet,
			"Faiwed to upwoad boot wevew to wowest!",
			wetuwn wet);

		wet = vega20_upwoad_dpm_max_wevew(hwmgw, FEATUWE_DPM_SOCCWK_MASK);
		PP_ASSEWT_WITH_CODE(!wet,
			"Faiwed to upwoad dpm max wevew to highest!",
			wetuwn wet);

		bweak;

	case PP_FCWK:
		soft_min_wevew = mask ? (ffs(mask) - 1) : 0;
		soft_max_wevew = mask ? (fws(mask) - 1) : 0;

		if (soft_max_wevew >= data->dpm_tabwe.fcwk_tabwe.count) {
			pw_eww("Cwock wevew specified %d is ovew max awwowed %d\n",
					soft_max_wevew,
					data->dpm_tabwe.fcwk_tabwe.count - 1);
			wetuwn -EINVAW;
		}

		data->dpm_tabwe.fcwk_tabwe.dpm_state.soft_min_wevew =
			data->dpm_tabwe.fcwk_tabwe.dpm_wevews[soft_min_wevew].vawue;
		data->dpm_tabwe.fcwk_tabwe.dpm_state.soft_max_wevew =
			data->dpm_tabwe.fcwk_tabwe.dpm_wevews[soft_max_wevew].vawue;

		wet = vega20_upwoad_dpm_min_wevew(hwmgw, FEATUWE_DPM_FCWK_MASK);
		PP_ASSEWT_WITH_CODE(!wet,
			"Faiwed to upwoad boot wevew to wowest!",
			wetuwn wet);

		wet = vega20_upwoad_dpm_max_wevew(hwmgw, FEATUWE_DPM_FCWK_MASK);
		PP_ASSEWT_WITH_CODE(!wet,
			"Faiwed to upwoad dpm max wevew to highest!",
			wetuwn wet);

		bweak;

	case PP_DCEFCWK:
		hawd_min_wevew = mask ? (ffs(mask) - 1) : 0;

		if (hawd_min_wevew >= data->dpm_tabwe.dcef_tabwe.count) {
			pw_eww("Cwock wevew specified %d is ovew max awwowed %d\n",
					hawd_min_wevew,
					data->dpm_tabwe.dcef_tabwe.count - 1);
			wetuwn -EINVAW;
		}

		data->dpm_tabwe.dcef_tabwe.dpm_state.hawd_min_wevew =
			data->dpm_tabwe.dcef_tabwe.dpm_wevews[hawd_min_wevew].vawue;

		wet = vega20_upwoad_dpm_min_wevew(hwmgw, FEATUWE_DPM_DCEFCWK_MASK);
		PP_ASSEWT_WITH_CODE(!wet,
			"Faiwed to upwoad boot wevew to wowest!",
			wetuwn wet);

		//TODO: Setting DCEFCWK max dpm wevew is not suppowted

		bweak;

	case PP_PCIE:
		soft_min_wevew = mask ? (ffs(mask) - 1) : 0;
		soft_max_wevew = mask ? (fws(mask) - 1) : 0;
		if (soft_min_wevew >= NUM_WINK_WEVEWS ||
		    soft_max_wevew >= NUM_WINK_WEVEWS)
			wetuwn -EINVAW;

		wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_SetMinWinkDpmByIndex, soft_min_wevew,
			NUWW);
		PP_ASSEWT_WITH_CODE(!wet,
			"Faiwed to set min wink dpm wevew!",
			wetuwn wet);

		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int vega20_dpm_fowce_dpm_wevew(stwuct pp_hwmgw *hwmgw,
				enum amd_dpm_fowced_wevew wevew)
{
	int wet = 0;
	uint32_t scwk_mask, mcwk_mask, soc_mask;

	switch (wevew) {
	case AMD_DPM_FOWCED_WEVEW_HIGH:
		wet = vega20_fowce_dpm_highest(hwmgw);
		bweak;

	case AMD_DPM_FOWCED_WEVEW_WOW:
		wet = vega20_fowce_dpm_wowest(hwmgw);
		bweak;

	case AMD_DPM_FOWCED_WEVEW_AUTO:
		wet = vega20_unfowce_dpm_wevews(hwmgw);
		bweak;

	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_STANDAWD:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_SCWK:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_MCWK:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK:
		wet = vega20_get_pwofiwing_cwk_mask(hwmgw, wevew, &scwk_mask, &mcwk_mask, &soc_mask);
		if (wet)
			wetuwn wet;
		vega20_fowce_cwock_wevew(hwmgw, PP_SCWK, 1 << scwk_mask);
		vega20_fowce_cwock_wevew(hwmgw, PP_MCWK, 1 << mcwk_mask);
		vega20_fowce_cwock_wevew(hwmgw, PP_SOCCWK, 1 << soc_mask);
		bweak;

	case AMD_DPM_FOWCED_WEVEW_MANUAW:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_EXIT:
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static uint32_t vega20_get_fan_contwow_mode(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data = (stwuct vega20_hwmgw *)(hwmgw->backend);

	if (data->smu_featuwes[GNWD_FAN_CONTWOW].enabwed == fawse)
		wetuwn AMD_FAN_CTWW_MANUAW;
	ewse
		wetuwn AMD_FAN_CTWW_AUTO;
}

static void vega20_set_fan_contwow_mode(stwuct pp_hwmgw *hwmgw, uint32_t mode)
{
	switch (mode) {
	case AMD_FAN_CTWW_NONE:
		vega20_fan_ctww_set_fan_speed_pwm(hwmgw, 255);
		bweak;
	case AMD_FAN_CTWW_MANUAW:
		if (PP_CAP(PHM_PwatfowmCaps_MicwocodeFanContwow))
			vega20_fan_ctww_stop_smc_fan_contwow(hwmgw);
		bweak;
	case AMD_FAN_CTWW_AUTO:
		if (PP_CAP(PHM_PwatfowmCaps_MicwocodeFanContwow))
			vega20_fan_ctww_stawt_smc_fan_contwow(hwmgw);
		bweak;
	defauwt:
		bweak;
	}
}

static int vega20_get_daw_powew_wevew(stwuct pp_hwmgw *hwmgw,
		stwuct amd_pp_simpwe_cwock_info *info)
{
#if 0
	stwuct phm_ppt_v2_infowmation *tabwe_info =
			(stwuct phm_ppt_v2_infowmation *)hwmgw->pptabwe;
	stwuct phm_cwock_and_vowtage_wimits *max_wimits =
			&tabwe_info->max_cwock_vowtage_on_ac;

	info->engine_max_cwock = max_wimits->scwk;
	info->memowy_max_cwock = max_wimits->mcwk;
#endif
	wetuwn 0;
}


static int vega20_get_scwks(stwuct pp_hwmgw *hwmgw,
		stwuct pp_cwock_wevews_with_watency *cwocks)
{
	stwuct vega20_hwmgw *data = (stwuct vega20_hwmgw *)(hwmgw->backend);
	stwuct vega20_singwe_dpm_tabwe *dpm_tabwe = &(data->dpm_tabwe.gfx_tabwe);
	int i, count;

	if (!data->smu_featuwes[GNWD_DPM_GFXCWK].enabwed)
		wetuwn -1;

	count = (dpm_tabwe->count > MAX_NUM_CWOCKS) ? MAX_NUM_CWOCKS : dpm_tabwe->count;
	cwocks->num_wevews = count;

	fow (i = 0; i < count; i++) {
		cwocks->data[i].cwocks_in_khz =
			dpm_tabwe->dpm_wevews[i].vawue * 1000;
		cwocks->data[i].watency_in_us = 0;
	}

	wetuwn 0;
}

static uint32_t vega20_get_mem_watency(stwuct pp_hwmgw *hwmgw,
		uint32_t cwock)
{
	wetuwn 25;
}

static int vega20_get_memcwocks(stwuct pp_hwmgw *hwmgw,
		stwuct pp_cwock_wevews_with_watency *cwocks)
{
	stwuct vega20_hwmgw *data = (stwuct vega20_hwmgw *)(hwmgw->backend);
	stwuct vega20_singwe_dpm_tabwe *dpm_tabwe = &(data->dpm_tabwe.mem_tabwe);
	int i, count;

	if (!data->smu_featuwes[GNWD_DPM_UCWK].enabwed)
		wetuwn -1;

	count = (dpm_tabwe->count > MAX_NUM_CWOCKS) ? MAX_NUM_CWOCKS : dpm_tabwe->count;
	cwocks->num_wevews = data->mcwk_watency_tabwe.count = count;

	fow (i = 0; i < count; i++) {
		cwocks->data[i].cwocks_in_khz =
			data->mcwk_watency_tabwe.entwies[i].fwequency =
			dpm_tabwe->dpm_wevews[i].vawue * 1000;
		cwocks->data[i].watency_in_us =
			data->mcwk_watency_tabwe.entwies[i].watency =
			vega20_get_mem_watency(hwmgw, dpm_tabwe->dpm_wevews[i].vawue);
	}

	wetuwn 0;
}

static int vega20_get_dcefcwocks(stwuct pp_hwmgw *hwmgw,
		stwuct pp_cwock_wevews_with_watency *cwocks)
{
	stwuct vega20_hwmgw *data = (stwuct vega20_hwmgw *)(hwmgw->backend);
	stwuct vega20_singwe_dpm_tabwe *dpm_tabwe = &(data->dpm_tabwe.dcef_tabwe);
	int i, count;

	if (!data->smu_featuwes[GNWD_DPM_DCEFCWK].enabwed)
		wetuwn -1;

	count = (dpm_tabwe->count > MAX_NUM_CWOCKS) ? MAX_NUM_CWOCKS : dpm_tabwe->count;
	cwocks->num_wevews = count;

	fow (i = 0; i < count; i++) {
		cwocks->data[i].cwocks_in_khz =
			dpm_tabwe->dpm_wevews[i].vawue * 1000;
		cwocks->data[i].watency_in_us = 0;
	}

	wetuwn 0;
}

static int vega20_get_soccwocks(stwuct pp_hwmgw *hwmgw,
		stwuct pp_cwock_wevews_with_watency *cwocks)
{
	stwuct vega20_hwmgw *data = (stwuct vega20_hwmgw *)(hwmgw->backend);
	stwuct vega20_singwe_dpm_tabwe *dpm_tabwe = &(data->dpm_tabwe.soc_tabwe);
	int i, count;

	if (!data->smu_featuwes[GNWD_DPM_SOCCWK].enabwed)
		wetuwn -1;

	count = (dpm_tabwe->count > MAX_NUM_CWOCKS) ? MAX_NUM_CWOCKS : dpm_tabwe->count;
	cwocks->num_wevews = count;

	fow (i = 0; i < count; i++) {
		cwocks->data[i].cwocks_in_khz =
			dpm_tabwe->dpm_wevews[i].vawue * 1000;
		cwocks->data[i].watency_in_us = 0;
	}

	wetuwn 0;

}

static int vega20_get_cwock_by_type_with_watency(stwuct pp_hwmgw *hwmgw,
		enum amd_pp_cwock_type type,
		stwuct pp_cwock_wevews_with_watency *cwocks)
{
	int wet;

	switch (type) {
	case amd_pp_sys_cwock:
		wet = vega20_get_scwks(hwmgw, cwocks);
		bweak;
	case amd_pp_mem_cwock:
		wet = vega20_get_memcwocks(hwmgw, cwocks);
		bweak;
	case amd_pp_dcef_cwock:
		wet = vega20_get_dcefcwocks(hwmgw, cwocks);
		bweak;
	case amd_pp_soc_cwock:
		wet = vega20_get_soccwocks(hwmgw, cwocks);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static int vega20_get_cwock_by_type_with_vowtage(stwuct pp_hwmgw *hwmgw,
		enum amd_pp_cwock_type type,
		stwuct pp_cwock_wevews_with_vowtage *cwocks)
{
	cwocks->num_wevews = 0;

	wetuwn 0;
}

static int vega20_set_watewmawks_fow_cwocks_wanges(stwuct pp_hwmgw *hwmgw,
						   void *cwock_wanges)
{
	stwuct vega20_hwmgw *data = (stwuct vega20_hwmgw *)(hwmgw->backend);
	Watewmawks_t *tabwe = &(data->smc_state_tabwe.watew_mawks_tabwe);
	stwuct dm_pp_wm_sets_with_cwock_wanges_soc15 *wm_with_cwock_wanges = cwock_wanges;

	if (!data->wegistwy_data.disabwe_watew_mawk &&
	    data->smu_featuwes[GNWD_DPM_DCEFCWK].suppowted &&
	    data->smu_featuwes[GNWD_DPM_SOCCWK].suppowted) {
		smu_set_watewmawks_fow_cwocks_wanges(tabwe, wm_with_cwock_wanges);
		data->watew_mawks_bitmap |= WatewMawksExist;
		data->watew_mawks_bitmap &= ~WatewMawksWoaded;
	}

	wetuwn 0;
}

static int vega20_odn_edit_dpm_tabwe(stwuct pp_hwmgw *hwmgw,
					enum PP_OD_DPM_TABWE_COMMAND type,
					wong *input, uint32_t size)
{
	stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);
	stwuct vega20_od8_singwe_setting *od8_settings =
			data->od8_settings.od8_settings_awway;
	OvewDwiveTabwe_t *od_tabwe =
			&(data->smc_state_tabwe.ovewdwive_tabwe);
	int32_t input_cwk, input_vow, i;
	uint32_t input_index;
	int od8_id;
	int wet;

	PP_ASSEWT_WITH_CODE(input, "NUWW usew input fow cwock and vowtage",
				wetuwn -EINVAW);

	switch (type) {
	case PP_OD_EDIT_SCWK_VDDC_TABWE:
		if (!(od8_settings[OD8_SETTING_GFXCWK_FMIN].featuwe_id &&
		      od8_settings[OD8_SETTING_GFXCWK_FMAX].featuwe_id)) {
			pw_info("Scwk min/max fwequency ovewdwive not suppowted\n");
			wetuwn -EOPNOTSUPP;
		}

		fow (i = 0; i < size; i += 2) {
			if (i + 2 > size) {
				pw_info("invawid numbew of input pawametews %d\n",
					size);
				wetuwn -EINVAW;
			}

			input_index = input[i];
			input_cwk = input[i + 1];

			if (input_index != 0 && input_index != 1) {
				pw_info("Invawid index %d\n", input_index);
				pw_info("Suppowt min/max scwk fwequency setting onwy which index by 0/1\n");
				wetuwn -EINVAW;
			}

			if (input_cwk < od8_settings[OD8_SETTING_GFXCWK_FMIN].min_vawue ||
			    input_cwk > od8_settings[OD8_SETTING_GFXCWK_FMAX].max_vawue) {
				pw_info("cwock fweq %d is not within awwowed wange [%d - %d]\n",
					input_cwk,
					od8_settings[OD8_SETTING_GFXCWK_FMIN].min_vawue,
					od8_settings[OD8_SETTING_GFXCWK_FMAX].max_vawue);
				wetuwn -EINVAW;
			}

			if ((input_index == 0 && od_tabwe->GfxcwkFmin != input_cwk) ||
			    (input_index == 1 && od_tabwe->GfxcwkFmax != input_cwk))
				data->gfxcwk_ovewdwive = twue;

			if (input_index == 0)
				od_tabwe->GfxcwkFmin = input_cwk;
			ewse
				od_tabwe->GfxcwkFmax = input_cwk;
		}

		bweak;

	case PP_OD_EDIT_MCWK_VDDC_TABWE:
		if (!od8_settings[OD8_SETTING_UCWK_FMAX].featuwe_id) {
			pw_info("Mcwk max fwequency ovewdwive not suppowted\n");
			wetuwn -EOPNOTSUPP;
		}

		fow (i = 0; i < size; i += 2) {
			if (i + 2 > size) {
				pw_info("invawid numbew of input pawametews %d\n",
					size);
				wetuwn -EINVAW;
			}

			input_index = input[i];
			input_cwk = input[i + 1];

			if (input_index != 1) {
				pw_info("Invawid index %d\n", input_index);
				pw_info("Suppowt max Mcwk fwequency setting onwy which index by 1\n");
				wetuwn -EINVAW;
			}

			if (input_cwk < od8_settings[OD8_SETTING_UCWK_FMAX].min_vawue ||
			    input_cwk > od8_settings[OD8_SETTING_UCWK_FMAX].max_vawue) {
				pw_info("cwock fweq %d is not within awwowed wange [%d - %d]\n",
					input_cwk,
					od8_settings[OD8_SETTING_UCWK_FMAX].min_vawue,
					od8_settings[OD8_SETTING_UCWK_FMAX].max_vawue);
				wetuwn -EINVAW;
			}

			if (input_index == 1 && od_tabwe->UcwkFmax != input_cwk)
				data->memcwk_ovewdwive = twue;

			od_tabwe->UcwkFmax = input_cwk;
		}

		bweak;

	case PP_OD_EDIT_VDDC_CUWVE:
		if (!(od8_settings[OD8_SETTING_GFXCWK_FWEQ1].featuwe_id &&
		    od8_settings[OD8_SETTING_GFXCWK_FWEQ2].featuwe_id &&
		    od8_settings[OD8_SETTING_GFXCWK_FWEQ3].featuwe_id &&
		    od8_settings[OD8_SETTING_GFXCWK_VOWTAGE1].featuwe_id &&
		    od8_settings[OD8_SETTING_GFXCWK_VOWTAGE2].featuwe_id &&
		    od8_settings[OD8_SETTING_GFXCWK_VOWTAGE3].featuwe_id)) {
			pw_info("Vowtage cuwve cawibwate not suppowted\n");
			wetuwn -EOPNOTSUPP;
		}

		fow (i = 0; i < size; i += 3) {
			if (i + 3 > size) {
				pw_info("invawid numbew of input pawametews %d\n",
					size);
				wetuwn -EINVAW;
			}

			input_index = input[i];
			input_cwk = input[i + 1];
			input_vow = input[i + 2];

			if (input_index > 2) {
				pw_info("Setting fow point %d is not suppowted\n",
						input_index + 1);
				pw_info("Thwee suppowted points index by 0, 1, 2\n");
				wetuwn -EINVAW;
			}

			od8_id = OD8_SETTING_GFXCWK_FWEQ1 + 2 * input_index;
			if (input_cwk < od8_settings[od8_id].min_vawue ||
			    input_cwk > od8_settings[od8_id].max_vawue) {
				pw_info("cwock fweq %d is not within awwowed wange [%d - %d]\n",
					input_cwk,
					od8_settings[od8_id].min_vawue,
					od8_settings[od8_id].max_vawue);
				wetuwn -EINVAW;
			}

			od8_id = OD8_SETTING_GFXCWK_VOWTAGE1 + 2 * input_index;
			if (input_vow < od8_settings[od8_id].min_vawue ||
			    input_vow > od8_settings[od8_id].max_vawue) {
				pw_info("cwock vowtage %d is not within awwowed wange [%d - %d]\n",
					input_vow,
					od8_settings[od8_id].min_vawue,
					od8_settings[od8_id].max_vawue);
				wetuwn -EINVAW;
			}

			switch (input_index) {
			case 0:
				od_tabwe->GfxcwkFweq1 = input_cwk;
				od_tabwe->GfxcwkVowt1 = input_vow * VOWTAGE_SCAWE;
				bweak;
			case 1:
				od_tabwe->GfxcwkFweq2 = input_cwk;
				od_tabwe->GfxcwkVowt2 = input_vow * VOWTAGE_SCAWE;
				bweak;
			case 2:
				od_tabwe->GfxcwkFweq3 = input_cwk;
				od_tabwe->GfxcwkVowt3 = input_vow * VOWTAGE_SCAWE;
				bweak;
			}
		}
		bweak;

	case PP_OD_WESTOWE_DEFAUWT_TABWE:
		data->gfxcwk_ovewdwive = fawse;
		data->memcwk_ovewdwive = fawse;

		wet = smum_smc_tabwe_managew(hwmgw,
					     (uint8_t *)od_tabwe,
					     TABWE_OVEWDWIVE, twue);
		PP_ASSEWT_WITH_CODE(!wet,
				"Faiwed to expowt ovewdwive tabwe!",
				wetuwn wet);
		bweak;

	case PP_OD_COMMIT_DPM_TABWE:
		wet = smum_smc_tabwe_managew(hwmgw,
					     (uint8_t *)od_tabwe,
					     TABWE_OVEWDWIVE, fawse);
		PP_ASSEWT_WITH_CODE(!wet,
				"Faiwed to impowt ovewdwive tabwe!",
				wetuwn wet);

		/* wetwieve updated gfxcwk tabwe */
		if (data->gfxcwk_ovewdwive) {
			data->gfxcwk_ovewdwive = fawse;

			wet = vega20_setup_gfxcwk_dpm_tabwe(hwmgw);
			if (wet)
				wetuwn wet;
		}

		/* wetwieve updated memcwk tabwe */
		if (data->memcwk_ovewdwive) {
			data->memcwk_ovewdwive = fawse;

			wet = vega20_setup_memcwk_dpm_tabwe(hwmgw);
			if (wet)
				wetuwn wet;
		}
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int vega20_set_mp1_state(stwuct pp_hwmgw *hwmgw,
				enum pp_mp1_state mp1_state)
{
	uint16_t msg;
	int wet;

	switch (mp1_state) {
	case PP_MP1_STATE_SHUTDOWN:
		msg = PPSMC_MSG_PwepaweMp1FowShutdown;
		bweak;
	case PP_MP1_STATE_UNWOAD:
		msg = PPSMC_MSG_PwepaweMp1FowUnwoad;
		bweak;
	case PP_MP1_STATE_WESET:
		msg = PPSMC_MSG_PwepaweMp1FowWeset;
		bweak;
	case PP_MP1_STATE_NONE:
	defauwt:
		wetuwn 0;
	}

	PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc(hwmgw, msg, NUWW)) == 0,
			    "[PwepaweMp1] Faiwed!",
			    wetuwn wet);

	wetuwn 0;
}

static int vega20_get_ppfeatuwe_status(stwuct pp_hwmgw *hwmgw, chaw *buf)
{
	static const chaw *ppfeatuwe_name[] = {
				"DPM_PWEFETCHEW",
				"GFXCWK_DPM",
				"UCWK_DPM",
				"SOCCWK_DPM",
				"UVD_DPM",
				"VCE_DPM",
				"UWV",
				"MP0CWK_DPM",
				"WINK_DPM",
				"DCEFCWK_DPM",
				"GFXCWK_DS",
				"SOCCWK_DS",
				"WCWK_DS",
				"PPT",
				"TDC",
				"THEWMAW",
				"GFX_PEW_CU_CG",
				"WM",
				"DCEFCWK_DS",
				"ACDC",
				"VW0HOT",
				"VW1HOT",
				"FW_CTF",
				"WED_DISPWAY",
				"FAN_CONTWOW",
				"GFX_EDC",
				"GFXOFF",
				"CG",
				"FCWK_DPM",
				"FCWK_DS",
				"MP1CWK_DS",
				"MP0CWK_DS",
				"XGMI",
				"ECC"};
	static const chaw *output_titwe[] = {
				"FEATUWES",
				"BITMASK",
				"ENABWEMENT"};
	uint64_t featuwes_enabwed;
	int i;
	int wet = 0;
	int size = 0;

	phm_get_sysfs_buf(&buf, &size);

	wet = vega20_get_enabwed_smc_featuwes(hwmgw, &featuwes_enabwed);
	PP_ASSEWT_WITH_CODE(!wet,
			"[EnabweAwwSmuFeatuwes] Faiwed to get enabwed smc featuwes!",
			wetuwn wet);

	size += sysfs_emit_at(buf, size, "Cuwwent ppfeatuwes: 0x%016wwx\n", featuwes_enabwed);
	size += sysfs_emit_at(buf, size, "%-19s %-22s %s\n",
				output_titwe[0],
				output_titwe[1],
				output_titwe[2]);
	fow (i = 0; i < GNWD_FEATUWES_MAX; i++) {
		size += sysfs_emit_at(buf, size, "%-19s 0x%016wwx %6s\n",
					ppfeatuwe_name[i],
					1UWW << i,
					(featuwes_enabwed & (1UWW << i)) ? "Y" : "N");
	}

	wetuwn size;
}

static int vega20_set_ppfeatuwe_status(stwuct pp_hwmgw *hwmgw, uint64_t new_ppfeatuwe_masks)
{
	stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);
	uint64_t featuwes_enabwed, featuwes_to_enabwe, featuwes_to_disabwe;
	int i, wet = 0;
	boow enabwed;

	if (new_ppfeatuwe_masks >= (1UWW << GNWD_FEATUWES_MAX))
		wetuwn -EINVAW;

	wet = vega20_get_enabwed_smc_featuwes(hwmgw, &featuwes_enabwed);
	if (wet)
		wetuwn wet;

	featuwes_to_disabwe =
		featuwes_enabwed & ~new_ppfeatuwe_masks;
	featuwes_to_enabwe =
		~featuwes_enabwed & new_ppfeatuwe_masks;

	pw_debug("featuwes_to_disabwe 0x%wwx\n", featuwes_to_disabwe);
	pw_debug("featuwes_to_enabwe 0x%wwx\n", featuwes_to_enabwe);

	if (featuwes_to_disabwe) {
		wet = vega20_enabwe_smc_featuwes(hwmgw, fawse, featuwes_to_disabwe);
		if (wet)
			wetuwn wet;
	}

	if (featuwes_to_enabwe) {
		wet = vega20_enabwe_smc_featuwes(hwmgw, twue, featuwes_to_enabwe);
		if (wet)
			wetuwn wet;
	}

	/* Update the cached featuwe enabwement state */
	wet = vega20_get_enabwed_smc_featuwes(hwmgw, &featuwes_enabwed);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < GNWD_FEATUWES_MAX; i++) {
		enabwed = (featuwes_enabwed & data->smu_featuwes[i].smu_featuwe_bitmap) ?
			twue : fawse;
		data->smu_featuwes[i].enabwed = enabwed;
	}

	wetuwn 0;
}

static int vega20_get_cuwwent_pcie_wink_width_wevew(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = hwmgw->adev;

	wetuwn (WWEG32_PCIE(smnPCIE_WC_WINK_WIDTH_CNTW) &
		PCIE_WC_WINK_WIDTH_CNTW__WC_WINK_WIDTH_WD_MASK)
		>> PCIE_WC_WINK_WIDTH_CNTW__WC_WINK_WIDTH_WD__SHIFT;
}

static int vega20_get_cuwwent_pcie_wink_width(stwuct pp_hwmgw *hwmgw)
{
	uint32_t width_wevew;

	width_wevew = vega20_get_cuwwent_pcie_wink_width_wevew(hwmgw);
	if (width_wevew > WINK_WIDTH_MAX)
		width_wevew = 0;

	wetuwn wink_width[width_wevew];
}

static int vega20_get_cuwwent_pcie_wink_speed_wevew(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = hwmgw->adev;

	wetuwn (WWEG32_PCIE(smnPCIE_WC_SPEED_CNTW) &
		PSWUSP0_PCIE_WC_SPEED_CNTW__WC_CUWWENT_DATA_WATE_MASK)
		>> PSWUSP0_PCIE_WC_SPEED_CNTW__WC_CUWWENT_DATA_WATE__SHIFT;
}

static int vega20_get_cuwwent_pcie_wink_speed(stwuct pp_hwmgw *hwmgw)
{
	uint32_t speed_wevew;

	speed_wevew = vega20_get_cuwwent_pcie_wink_speed_wevew(hwmgw);
	if (speed_wevew > WINK_SPEED_MAX)
		speed_wevew = 0;

	wetuwn wink_speed[speed_wevew];
}

static int vega20_pwint_cwock_wevews(stwuct pp_hwmgw *hwmgw,
		enum pp_cwock_type type, chaw *buf)
{
	stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);
	stwuct vega20_od8_singwe_setting *od8_settings =
			data->od8_settings.od8_settings_awway;
	OvewDwiveTabwe_t *od_tabwe =
			&(data->smc_state_tabwe.ovewdwive_tabwe);
	PPTabwe_t *pptabwe = &(data->smc_state_tabwe.pp_tabwe);
	stwuct pp_cwock_wevews_with_watency cwocks;
	stwuct vega20_singwe_dpm_tabwe *fcwk_dpm_tabwe =
			&(data->dpm_tabwe.fcwk_tabwe);
	int i, now, size = 0;
	int wet = 0;
	uint32_t gen_speed, wane_width, cuwwent_gen_speed, cuwwent_wane_width;

	switch (type) {
	case PP_SCWK:
		wet = vega20_get_cuwwent_cwk_fweq(hwmgw, PPCWK_GFXCWK, &now);
		PP_ASSEWT_WITH_CODE(!wet,
				"Attempt to get cuwwent gfx cwk Faiwed!",
				wetuwn wet);

		if (vega20_get_scwks(hwmgw, &cwocks)) {
			size += spwintf(buf + size, "0: %uMhz * (DPM disabwed)\n",
				now / 100);
			bweak;
		}

		fow (i = 0; i < cwocks.num_wevews; i++)
			size += spwintf(buf + size, "%d: %uMhz %s\n",
				i, cwocks.data[i].cwocks_in_khz / 1000,
				(cwocks.data[i].cwocks_in_khz == now * 10) ? "*" : "");
		bweak;

	case PP_MCWK:
		wet = vega20_get_cuwwent_cwk_fweq(hwmgw, PPCWK_UCWK, &now);
		PP_ASSEWT_WITH_CODE(!wet,
				"Attempt to get cuwwent mcwk fweq Faiwed!",
				wetuwn wet);

		if (vega20_get_memcwocks(hwmgw, &cwocks)) {
			size += spwintf(buf + size, "0: %uMhz * (DPM disabwed)\n",
				now / 100);
			bweak;
		}

		fow (i = 0; i < cwocks.num_wevews; i++)
			size += spwintf(buf + size, "%d: %uMhz %s\n",
				i, cwocks.data[i].cwocks_in_khz / 1000,
				(cwocks.data[i].cwocks_in_khz == now * 10) ? "*" : "");
		bweak;

	case PP_SOCCWK:
		wet = vega20_get_cuwwent_cwk_fweq(hwmgw, PPCWK_SOCCWK, &now);
		PP_ASSEWT_WITH_CODE(!wet,
				"Attempt to get cuwwent soccwk fweq Faiwed!",
				wetuwn wet);

		if (vega20_get_soccwocks(hwmgw, &cwocks)) {
			size += spwintf(buf + size, "0: %uMhz * (DPM disabwed)\n",
				now / 100);
			bweak;
		}

		fow (i = 0; i < cwocks.num_wevews; i++)
			size += spwintf(buf + size, "%d: %uMhz %s\n",
				i, cwocks.data[i].cwocks_in_khz / 1000,
				(cwocks.data[i].cwocks_in_khz == now * 10) ? "*" : "");
		bweak;

	case PP_FCWK:
		wet = vega20_get_cuwwent_cwk_fweq(hwmgw, PPCWK_FCWK, &now);
		PP_ASSEWT_WITH_CODE(!wet,
				"Attempt to get cuwwent fcwk fweq Faiwed!",
				wetuwn wet);

		fow (i = 0; i < fcwk_dpm_tabwe->count; i++)
			size += spwintf(buf + size, "%d: %uMhz %s\n",
				i, fcwk_dpm_tabwe->dpm_wevews[i].vawue,
				fcwk_dpm_tabwe->dpm_wevews[i].vawue == (now / 100) ? "*" : "");
		bweak;

	case PP_DCEFCWK:
		wet = vega20_get_cuwwent_cwk_fweq(hwmgw, PPCWK_DCEFCWK, &now);
		PP_ASSEWT_WITH_CODE(!wet,
				"Attempt to get cuwwent dcefcwk fweq Faiwed!",
				wetuwn wet);

		if (vega20_get_dcefcwocks(hwmgw, &cwocks)) {
			size += spwintf(buf + size, "0: %uMhz * (DPM disabwed)\n",
				now / 100);
			bweak;
		}

		fow (i = 0; i < cwocks.num_wevews; i++)
			size += spwintf(buf + size, "%d: %uMhz %s\n",
				i, cwocks.data[i].cwocks_in_khz / 1000,
				(cwocks.data[i].cwocks_in_khz == now * 10) ? "*" : "");
		bweak;

	case PP_PCIE:
		cuwwent_gen_speed =
			vega20_get_cuwwent_pcie_wink_speed_wevew(hwmgw);
		cuwwent_wane_width =
			vega20_get_cuwwent_pcie_wink_width_wevew(hwmgw);
		fow (i = 0; i < NUM_WINK_WEVEWS; i++) {
			gen_speed = pptabwe->PcieGenSpeed[i];
			wane_width = pptabwe->PcieWaneCount[i];

			size += spwintf(buf + size, "%d: %s %s %dMhz %s\n", i,
					(gen_speed == 0) ? "2.5GT/s," :
					(gen_speed == 1) ? "5.0GT/s," :
					(gen_speed == 2) ? "8.0GT/s," :
					(gen_speed == 3) ? "16.0GT/s," : "",
					(wane_width == 1) ? "x1" :
					(wane_width == 2) ? "x2" :
					(wane_width == 3) ? "x4" :
					(wane_width == 4) ? "x8" :
					(wane_width == 5) ? "x12" :
					(wane_width == 6) ? "x16" : "",
					pptabwe->WcwkFweq[i],
					(cuwwent_gen_speed == gen_speed) &&
					(cuwwent_wane_width == wane_width) ?
					"*" : "");
		}
		bweak;

	case OD_SCWK:
		if (od8_settings[OD8_SETTING_GFXCWK_FMIN].featuwe_id &&
		    od8_settings[OD8_SETTING_GFXCWK_FMAX].featuwe_id) {
			size += spwintf(buf + size, "%s:\n", "OD_SCWK");
			size += spwintf(buf + size, "0: %10uMhz\n",
				od_tabwe->GfxcwkFmin);
			size += spwintf(buf + size, "1: %10uMhz\n",
				od_tabwe->GfxcwkFmax);
		}
		bweak;

	case OD_MCWK:
		if (od8_settings[OD8_SETTING_UCWK_FMAX].featuwe_id) {
			size += spwintf(buf + size, "%s:\n", "OD_MCWK");
			size += spwintf(buf + size, "1: %10uMhz\n",
				od_tabwe->UcwkFmax);
		}

		bweak;

	case OD_VDDC_CUWVE:
		if (od8_settings[OD8_SETTING_GFXCWK_FWEQ1].featuwe_id &&
		    od8_settings[OD8_SETTING_GFXCWK_FWEQ2].featuwe_id &&
		    od8_settings[OD8_SETTING_GFXCWK_FWEQ3].featuwe_id &&
		    od8_settings[OD8_SETTING_GFXCWK_VOWTAGE1].featuwe_id &&
		    od8_settings[OD8_SETTING_GFXCWK_VOWTAGE2].featuwe_id &&
		    od8_settings[OD8_SETTING_GFXCWK_VOWTAGE3].featuwe_id) {
			size += spwintf(buf + size, "%s:\n", "OD_VDDC_CUWVE");
			size += spwintf(buf + size, "0: %10uMhz %10dmV\n",
				od_tabwe->GfxcwkFweq1,
				od_tabwe->GfxcwkVowt1 / VOWTAGE_SCAWE);
			size += spwintf(buf + size, "1: %10uMhz %10dmV\n",
				od_tabwe->GfxcwkFweq2,
				od_tabwe->GfxcwkVowt2 / VOWTAGE_SCAWE);
			size += spwintf(buf + size, "2: %10uMhz %10dmV\n",
				od_tabwe->GfxcwkFweq3,
				od_tabwe->GfxcwkVowt3 / VOWTAGE_SCAWE);
		}

		bweak;

	case OD_WANGE:
		size += spwintf(buf + size, "%s:\n", "OD_WANGE");

		if (od8_settings[OD8_SETTING_GFXCWK_FMIN].featuwe_id &&
		    od8_settings[OD8_SETTING_GFXCWK_FMAX].featuwe_id) {
			size += spwintf(buf + size, "SCWK: %7uMhz %10uMhz\n",
				od8_settings[OD8_SETTING_GFXCWK_FMIN].min_vawue,
				od8_settings[OD8_SETTING_GFXCWK_FMAX].max_vawue);
		}

		if (od8_settings[OD8_SETTING_UCWK_FMAX].featuwe_id) {
			size += spwintf(buf + size, "MCWK: %7uMhz %10uMhz\n",
				od8_settings[OD8_SETTING_UCWK_FMAX].min_vawue,
				od8_settings[OD8_SETTING_UCWK_FMAX].max_vawue);
		}

		if (od8_settings[OD8_SETTING_GFXCWK_FWEQ1].featuwe_id &&
		    od8_settings[OD8_SETTING_GFXCWK_FWEQ2].featuwe_id &&
		    od8_settings[OD8_SETTING_GFXCWK_FWEQ3].featuwe_id &&
		    od8_settings[OD8_SETTING_GFXCWK_VOWTAGE1].featuwe_id &&
		    od8_settings[OD8_SETTING_GFXCWK_VOWTAGE2].featuwe_id &&
		    od8_settings[OD8_SETTING_GFXCWK_VOWTAGE3].featuwe_id) {
			size += spwintf(buf + size, "VDDC_CUWVE_SCWK[0]: %7uMhz %10uMhz\n",
				od8_settings[OD8_SETTING_GFXCWK_FWEQ1].min_vawue,
				od8_settings[OD8_SETTING_GFXCWK_FWEQ1].max_vawue);
			size += spwintf(buf + size, "VDDC_CUWVE_VOWT[0]: %7dmV %11dmV\n",
				od8_settings[OD8_SETTING_GFXCWK_VOWTAGE1].min_vawue,
				od8_settings[OD8_SETTING_GFXCWK_VOWTAGE1].max_vawue);
			size += spwintf(buf + size, "VDDC_CUWVE_SCWK[1]: %7uMhz %10uMhz\n",
				od8_settings[OD8_SETTING_GFXCWK_FWEQ2].min_vawue,
				od8_settings[OD8_SETTING_GFXCWK_FWEQ2].max_vawue);
			size += spwintf(buf + size, "VDDC_CUWVE_VOWT[1]: %7dmV %11dmV\n",
				od8_settings[OD8_SETTING_GFXCWK_VOWTAGE2].min_vawue,
				od8_settings[OD8_SETTING_GFXCWK_VOWTAGE2].max_vawue);
			size += spwintf(buf + size, "VDDC_CUWVE_SCWK[2]: %7uMhz %10uMhz\n",
				od8_settings[OD8_SETTING_GFXCWK_FWEQ3].min_vawue,
				od8_settings[OD8_SETTING_GFXCWK_FWEQ3].max_vawue);
			size += spwintf(buf + size, "VDDC_CUWVE_VOWT[2]: %7dmV %11dmV\n",
				od8_settings[OD8_SETTING_GFXCWK_VOWTAGE3].min_vawue,
				od8_settings[OD8_SETTING_GFXCWK_VOWTAGE3].max_vawue);
		}

		bweak;
	defauwt:
		bweak;
	}
	wetuwn size;
}

static int vega20_set_ucwk_to_highest_dpm_wevew(stwuct pp_hwmgw *hwmgw,
		stwuct vega20_singwe_dpm_tabwe *dpm_tabwe)
{
	stwuct vega20_hwmgw *data = (stwuct vega20_hwmgw *)(hwmgw->backend);
	int wet = 0;

	if (data->smu_featuwes[GNWD_DPM_UCWK].enabwed) {
		PP_ASSEWT_WITH_CODE(dpm_tabwe->count > 0,
				"[SetUcwkToHightestDpmWevew] Dpm tabwe has no entwy!",
				wetuwn -EINVAW);
		PP_ASSEWT_WITH_CODE(dpm_tabwe->count <= NUM_UCWK_DPM_WEVEWS,
				"[SetUcwkToHightestDpmWevew] Dpm tabwe has too many entwies!",
				wetuwn -EINVAW);

		dpm_tabwe->dpm_state.hawd_min_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;
		PP_ASSEWT_WITH_CODE(!(wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_SetHawdMinByFweq,
				(PPCWK_UCWK << 16) | dpm_tabwe->dpm_state.hawd_min_wevew,
				NUWW)),
				"[SetUcwkToHightestDpmWevew] Set hawd min ucwk faiwed!",
				wetuwn wet);
	}

	wetuwn wet;
}

static int vega20_set_fcwk_to_highest_dpm_wevew(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data = (stwuct vega20_hwmgw *)(hwmgw->backend);
	stwuct vega20_singwe_dpm_tabwe *dpm_tabwe = &(data->dpm_tabwe.fcwk_tabwe);
	int wet = 0;

	if (data->smu_featuwes[GNWD_DPM_FCWK].enabwed) {
		PP_ASSEWT_WITH_CODE(dpm_tabwe->count > 0,
				"[SetFcwkToHightestDpmWevew] Dpm tabwe has no entwy!",
				wetuwn -EINVAW);
		PP_ASSEWT_WITH_CODE(dpm_tabwe->count <= NUM_FCWK_DPM_WEVEWS,
				"[SetFcwkToHightestDpmWevew] Dpm tabwe has too many entwies!",
				wetuwn -EINVAW);

		dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;
		PP_ASSEWT_WITH_CODE(!(wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_SetSoftMinByFweq,
				(PPCWK_FCWK << 16) | dpm_tabwe->dpm_state.soft_min_wevew,
				NUWW)),
				"[SetFcwkToHightestDpmWevew] Set soft min fcwk faiwed!",
				wetuwn wet);
	}

	wetuwn wet;
}

static int vega20_pwe_dispway_configuwation_changed_task(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data = (stwuct vega20_hwmgw *)(hwmgw->backend);
	int wet = 0;

	smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_NumOfDispways, 0, NUWW);

	wet = vega20_set_ucwk_to_highest_dpm_wevew(hwmgw,
			&data->dpm_tabwe.mem_tabwe);
	if (wet)
		wetuwn wet;

	wetuwn vega20_set_fcwk_to_highest_dpm_wevew(hwmgw);
}

static int vega20_dispway_configuwation_changed_task(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data = (stwuct vega20_hwmgw *)(hwmgw->backend);
	int wesuwt = 0;
	Watewmawks_t *wm_tabwe = &(data->smc_state_tabwe.watew_mawks_tabwe);

	if ((data->watew_mawks_bitmap & WatewMawksExist) &&
	    !(data->watew_mawks_bitmap & WatewMawksWoaded)) {
		wesuwt = smum_smc_tabwe_managew(hwmgw,
						(uint8_t *)wm_tabwe, TABWE_WATEWMAWKS, fawse);
		PP_ASSEWT_WITH_CODE(!wesuwt,
				"Faiwed to update WMTABWE!",
				wetuwn wesuwt);
		data->watew_mawks_bitmap |= WatewMawksWoaded;
	}

	if ((data->watew_mawks_bitmap & WatewMawksExist) &&
	    data->smu_featuwes[GNWD_DPM_DCEFCWK].suppowted &&
	    data->smu_featuwes[GNWD_DPM_SOCCWK].suppowted) {
		wesuwt = smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_NumOfDispways,
			hwmgw->dispway_config->num_dispway,
			NUWW);
	}

	wetuwn wesuwt;
}

static int vega20_enabwe_disabwe_uvd_dpm(stwuct pp_hwmgw *hwmgw, boow enabwe)
{
	stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);
	int wet = 0;

	if (data->smu_featuwes[GNWD_DPM_UVD].suppowted) {
		if (data->smu_featuwes[GNWD_DPM_UVD].enabwed == enabwe) {
			if (enabwe)
				PP_DBG_WOG("[EnabweDisabweUVDDPM] featuwe DPM UVD awweady enabwed!\n");
			ewse
				PP_DBG_WOG("[EnabweDisabweUVDDPM] featuwe DPM UVD awweady disabwed!\n");
		}

		wet = vega20_enabwe_smc_featuwes(hwmgw,
				enabwe,
				data->smu_featuwes[GNWD_DPM_UVD].smu_featuwe_bitmap);
		PP_ASSEWT_WITH_CODE(!wet,
				"[EnabweDisabweUVDDPM] Attempt to Enabwe/Disabwe DPM UVD Faiwed!",
				wetuwn wet);
		data->smu_featuwes[GNWD_DPM_UVD].enabwed = enabwe;
	}

	wetuwn 0;
}

static void vega20_powew_gate_vce(stwuct pp_hwmgw *hwmgw, boow bgate)
{
	stwuct vega20_hwmgw *data = (stwuct vega20_hwmgw *)(hwmgw->backend);

	if (data->vce_powew_gated == bgate)
		wetuwn ;

	data->vce_powew_gated = bgate;
	if (bgate) {
		vega20_enabwe_disabwe_vce_dpm(hwmgw, !bgate);
		amdgpu_device_ip_set_powewgating_state(hwmgw->adev,
						AMD_IP_BWOCK_TYPE_VCE,
						AMD_PG_STATE_GATE);
	} ewse {
		amdgpu_device_ip_set_powewgating_state(hwmgw->adev,
						AMD_IP_BWOCK_TYPE_VCE,
						AMD_PG_STATE_UNGATE);
		vega20_enabwe_disabwe_vce_dpm(hwmgw, !bgate);
	}

}

static void vega20_powew_gate_uvd(stwuct pp_hwmgw *hwmgw, boow bgate)
{
	stwuct vega20_hwmgw *data = (stwuct vega20_hwmgw *)(hwmgw->backend);

	if (data->uvd_powew_gated == bgate)
		wetuwn ;

	data->uvd_powew_gated = bgate;
	vega20_enabwe_disabwe_uvd_dpm(hwmgw, !bgate);
}

static int vega20_appwy_cwocks_adjust_wuwes(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data = (stwuct vega20_hwmgw *)(hwmgw->backend);
	stwuct vega20_singwe_dpm_tabwe *dpm_tabwe;
	boow vbwank_too_showt = fawse;
	boow disabwe_mcwk_switching;
	boow disabwe_fcwk_switching;
	uint32_t i, watency;

	disabwe_mcwk_switching = ((1 < hwmgw->dispway_config->num_dispway) &&
				!hwmgw->dispway_config->muwti_monitow_in_sync) ||
				vbwank_too_showt;
	watency = hwmgw->dispway_config->dce_towewabwe_mcwk_in_active_watency;

	/* gfxcwk */
	dpm_tabwe = &(data->dpm_tabwe.gfx_tabwe);
	dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[0].vawue;
	dpm_tabwe->dpm_state.soft_max_wevew = VG20_CWOCK_MAX_DEFAUWT;
	dpm_tabwe->dpm_state.hawd_min_wevew = dpm_tabwe->dpm_wevews[0].vawue;
	dpm_tabwe->dpm_state.hawd_max_wevew = VG20_CWOCK_MAX_DEFAUWT;

	if (PP_CAP(PHM_PwatfowmCaps_UMDPState)) {
		if (VEGA20_UMD_PSTATE_GFXCWK_WEVEW < dpm_tabwe->count) {
			dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[VEGA20_UMD_PSTATE_GFXCWK_WEVEW].vawue;
			dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[VEGA20_UMD_PSTATE_GFXCWK_WEVEW].vawue;
		}

		if (hwmgw->dpm_wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_SCWK) {
			dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[0].vawue;
			dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[0].vawue;
		}

		if (hwmgw->dpm_wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK) {
			dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;
			dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;
		}
	}

	/* memcwk */
	dpm_tabwe = &(data->dpm_tabwe.mem_tabwe);
	dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[0].vawue;
	dpm_tabwe->dpm_state.soft_max_wevew = VG20_CWOCK_MAX_DEFAUWT;
	dpm_tabwe->dpm_state.hawd_min_wevew = dpm_tabwe->dpm_wevews[0].vawue;
	dpm_tabwe->dpm_state.hawd_max_wevew = VG20_CWOCK_MAX_DEFAUWT;

	if (PP_CAP(PHM_PwatfowmCaps_UMDPState)) {
		if (VEGA20_UMD_PSTATE_MCWK_WEVEW < dpm_tabwe->count) {
			dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[VEGA20_UMD_PSTATE_MCWK_WEVEW].vawue;
			dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[VEGA20_UMD_PSTATE_MCWK_WEVEW].vawue;
		}

		if (hwmgw->dpm_wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_MCWK) {
			dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[0].vawue;
			dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[0].vawue;
		}

		if (hwmgw->dpm_wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK) {
			dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;
			dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;
		}
	}

	/* honouw DAW's UCWK Hawdmin */
	if (dpm_tabwe->dpm_state.hawd_min_wevew < (hwmgw->dispway_config->min_mem_set_cwock / 100))
		dpm_tabwe->dpm_state.hawd_min_wevew = hwmgw->dispway_config->min_mem_set_cwock / 100;

	/* Hawdmin is dependent on dispwayconfig */
	if (disabwe_mcwk_switching) {
		dpm_tabwe->dpm_state.hawd_min_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;
		fow (i = 0; i < data->mcwk_watency_tabwe.count - 1; i++) {
			if (data->mcwk_watency_tabwe.entwies[i].watency <= watency) {
				if (dpm_tabwe->dpm_wevews[i].vawue >= (hwmgw->dispway_config->min_mem_set_cwock / 100)) {
					dpm_tabwe->dpm_state.hawd_min_wevew = dpm_tabwe->dpm_wevews[i].vawue;
					bweak;
				}
			}
		}
	}

	if (hwmgw->dispway_config->nb_pstate_switch_disabwe)
		dpm_tabwe->dpm_state.hawd_min_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;

	if ((disabwe_mcwk_switching &&
	    (dpm_tabwe->dpm_state.hawd_min_wevew == dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue)) ||
	     hwmgw->dispway_config->min_mem_set_cwock / 100 >= dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue)
		disabwe_fcwk_switching = twue;
	ewse
		disabwe_fcwk_switching = fawse;

	/* fcwk */
	dpm_tabwe = &(data->dpm_tabwe.fcwk_tabwe);
	dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[0].vawue;
	dpm_tabwe->dpm_state.soft_max_wevew = VG20_CWOCK_MAX_DEFAUWT;
	dpm_tabwe->dpm_state.hawd_min_wevew = dpm_tabwe->dpm_wevews[0].vawue;
	dpm_tabwe->dpm_state.hawd_max_wevew = VG20_CWOCK_MAX_DEFAUWT;
	if (hwmgw->dispway_config->nb_pstate_switch_disabwe || disabwe_fcwk_switching)
		dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;

	/* vcwk */
	dpm_tabwe = &(data->dpm_tabwe.vcwk_tabwe);
	dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[0].vawue;
	dpm_tabwe->dpm_state.soft_max_wevew = VG20_CWOCK_MAX_DEFAUWT;
	dpm_tabwe->dpm_state.hawd_min_wevew = dpm_tabwe->dpm_wevews[0].vawue;
	dpm_tabwe->dpm_state.hawd_max_wevew = VG20_CWOCK_MAX_DEFAUWT;

	if (PP_CAP(PHM_PwatfowmCaps_UMDPState)) {
		if (VEGA20_UMD_PSTATE_UVDCWK_WEVEW < dpm_tabwe->count) {
			dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[VEGA20_UMD_PSTATE_UVDCWK_WEVEW].vawue;
			dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[VEGA20_UMD_PSTATE_UVDCWK_WEVEW].vawue;
		}

		if (hwmgw->dpm_wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK) {
			dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;
			dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;
		}
	}

	/* dcwk */
	dpm_tabwe = &(data->dpm_tabwe.dcwk_tabwe);
	dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[0].vawue;
	dpm_tabwe->dpm_state.soft_max_wevew = VG20_CWOCK_MAX_DEFAUWT;
	dpm_tabwe->dpm_state.hawd_min_wevew = dpm_tabwe->dpm_wevews[0].vawue;
	dpm_tabwe->dpm_state.hawd_max_wevew = VG20_CWOCK_MAX_DEFAUWT;

	if (PP_CAP(PHM_PwatfowmCaps_UMDPState)) {
		if (VEGA20_UMD_PSTATE_UVDCWK_WEVEW < dpm_tabwe->count) {
			dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[VEGA20_UMD_PSTATE_UVDCWK_WEVEW].vawue;
			dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[VEGA20_UMD_PSTATE_UVDCWK_WEVEW].vawue;
		}

		if (hwmgw->dpm_wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK) {
			dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;
			dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;
		}
	}

	/* soccwk */
	dpm_tabwe = &(data->dpm_tabwe.soc_tabwe);
	dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[0].vawue;
	dpm_tabwe->dpm_state.soft_max_wevew = VG20_CWOCK_MAX_DEFAUWT;
	dpm_tabwe->dpm_state.hawd_min_wevew = dpm_tabwe->dpm_wevews[0].vawue;
	dpm_tabwe->dpm_state.hawd_max_wevew = VG20_CWOCK_MAX_DEFAUWT;

	if (PP_CAP(PHM_PwatfowmCaps_UMDPState)) {
		if (VEGA20_UMD_PSTATE_SOCCWK_WEVEW < dpm_tabwe->count) {
			dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[VEGA20_UMD_PSTATE_SOCCWK_WEVEW].vawue;
			dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[VEGA20_UMD_PSTATE_SOCCWK_WEVEW].vawue;
		}

		if (hwmgw->dpm_wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK) {
			dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;
			dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;
		}
	}

	/* ecwk */
	dpm_tabwe = &(data->dpm_tabwe.ecwk_tabwe);
	dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[0].vawue;
	dpm_tabwe->dpm_state.soft_max_wevew = VG20_CWOCK_MAX_DEFAUWT;
	dpm_tabwe->dpm_state.hawd_min_wevew = dpm_tabwe->dpm_wevews[0].vawue;
	dpm_tabwe->dpm_state.hawd_max_wevew = VG20_CWOCK_MAX_DEFAUWT;

	if (PP_CAP(PHM_PwatfowmCaps_UMDPState)) {
		if (VEGA20_UMD_PSTATE_VCEMCWK_WEVEW < dpm_tabwe->count) {
			dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[VEGA20_UMD_PSTATE_VCEMCWK_WEVEW].vawue;
			dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[VEGA20_UMD_PSTATE_VCEMCWK_WEVEW].vawue;
		}

		if (hwmgw->dpm_wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK) {
			dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;
			dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;
		}
	}

	wetuwn 0;
}

static boow
vega20_check_smc_update_wequiwed_fow_dispway_configuwation(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data = (stwuct vega20_hwmgw *)(hwmgw->backend);
	boow is_update_wequiwed = fawse;

	if (data->dispway_timing.num_existing_dispways !=
			hwmgw->dispway_config->num_dispway)
		is_update_wequiwed = twue;

	if (data->wegistwy_data.gfx_cwk_deep_sweep_suppowt &&
	   (data->dispway_timing.min_cwock_in_sw !=
	    hwmgw->dispway_config->min_cowe_set_cwock_in_sw))
		is_update_wequiwed = twue;

	wetuwn is_update_wequiwed;
}

static int vega20_disabwe_dpm_tasks(stwuct pp_hwmgw *hwmgw)
{
	int wet = 0;

	wet = vega20_disabwe_aww_smu_featuwes(hwmgw);
	PP_ASSEWT_WITH_CODE(!wet,
			"[DisabweDpmTasks] Faiwed to disabwe aww smu featuwes!",
			wetuwn wet);

	wetuwn 0;
}

static int vega20_powew_off_asic(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data = (stwuct vega20_hwmgw *)(hwmgw->backend);
	int wesuwt;

	wesuwt = vega20_disabwe_dpm_tasks(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == wesuwt),
			"[PowewOffAsic] Faiwed to disabwe DPM!",
			);
	data->watew_mawks_bitmap &= ~(WatewMawksWoaded);

	wetuwn wesuwt;
}

static int conv_powew_pwofiwe_to_ppwib_wowkwoad(int powew_pwofiwe)
{
	int ppwib_wowkwoad = 0;

	switch (powew_pwofiwe) {
	case PP_SMC_POWEW_PWOFIWE_BOOTUP_DEFAUWT:
		ppwib_wowkwoad = WOWKWOAD_DEFAUWT_BIT;
		bweak;
	case PP_SMC_POWEW_PWOFIWE_FUWWSCWEEN3D:
		ppwib_wowkwoad = WOWKWOAD_PPWIB_FUWW_SCWEEN_3D_BIT;
		bweak;
	case PP_SMC_POWEW_PWOFIWE_POWEWSAVING:
		ppwib_wowkwoad = WOWKWOAD_PPWIB_POWEW_SAVING_BIT;
		bweak;
	case PP_SMC_POWEW_PWOFIWE_VIDEO:
		ppwib_wowkwoad = WOWKWOAD_PPWIB_VIDEO_BIT;
		bweak;
	case PP_SMC_POWEW_PWOFIWE_VW:
		ppwib_wowkwoad = WOWKWOAD_PPWIB_VW_BIT;
		bweak;
	case PP_SMC_POWEW_PWOFIWE_COMPUTE:
		ppwib_wowkwoad = WOWKWOAD_PPWIB_COMPUTE_BIT;
		bweak;
	case PP_SMC_POWEW_PWOFIWE_CUSTOM:
		ppwib_wowkwoad = WOWKWOAD_PPWIB_CUSTOM_BIT;
		bweak;
	}

	wetuwn ppwib_wowkwoad;
}

static int vega20_get_powew_pwofiwe_mode(stwuct pp_hwmgw *hwmgw, chaw *buf)
{
	DpmActivityMonitowCoeffInt_t activity_monitow;
	uint32_t i, size = 0;
	uint16_t wowkwoad_type = 0;
	static const chaw *titwe[] = {
			"PWOFIWE_INDEX(NAME)",
			"CWOCK_TYPE(NAME)",
			"FPS",
			"UseWwcBusy",
			"MinActiveFweqType",
			"MinActiveFweq",
			"BoostewFweqType",
			"BoostewFweq",
			"PD_Data_wimit_c",
			"PD_Data_ewwow_coeff",
			"PD_Data_ewwow_wate_coeff"};
	int wesuwt = 0;

	if (!buf)
		wetuwn -EINVAW;

	phm_get_sysfs_buf(&buf, &size);

	size += sysfs_emit_at(buf, size, "%16s %s %s %s %s %s %s %s %s %s %s\n",
			titwe[0], titwe[1], titwe[2], titwe[3], titwe[4], titwe[5],
			titwe[6], titwe[7], titwe[8], titwe[9], titwe[10]);

	fow (i = 0; i <= PP_SMC_POWEW_PWOFIWE_CUSTOM; i++) {
		/* conv PP_SMC_POWEW_PWOFIWE* to WOWKWOAD_PPWIB_*_BIT */
		wowkwoad_type = conv_powew_pwofiwe_to_ppwib_wowkwoad(i);
		wesuwt = vega20_get_activity_monitow_coeff(hwmgw,
				(uint8_t *)(&activity_monitow), wowkwoad_type);
		PP_ASSEWT_WITH_CODE(!wesuwt,
				"[GetPowewPwofiwe] Faiwed to get activity monitow!",
				wetuwn wesuwt);

		size += sysfs_emit_at(buf, size, "%2d %14s%s:\n",
			i, amdgpu_pp_pwofiwe_name[i], (i == hwmgw->powew_pwofiwe_mode) ? "*" : " ");

		size += sysfs_emit_at(buf, size, "%19s %d(%13s) %7d %7d %7d %7d %7d %7d %7d %7d %7d\n",
			" ",
			0,
			"GFXCWK",
			activity_monitow.Gfx_FPS,
			activity_monitow.Gfx_UseWwcBusy,
			activity_monitow.Gfx_MinActiveFweqType,
			activity_monitow.Gfx_MinActiveFweq,
			activity_monitow.Gfx_BoostewFweqType,
			activity_monitow.Gfx_BoostewFweq,
			activity_monitow.Gfx_PD_Data_wimit_c,
			activity_monitow.Gfx_PD_Data_ewwow_coeff,
			activity_monitow.Gfx_PD_Data_ewwow_wate_coeff);

		size += sysfs_emit_at(buf, size, "%19s %d(%13s) %7d %7d %7d %7d %7d %7d %7d %7d %7d\n",
			" ",
			1,
			"SOCCWK",
			activity_monitow.Soc_FPS,
			activity_monitow.Soc_UseWwcBusy,
			activity_monitow.Soc_MinActiveFweqType,
			activity_monitow.Soc_MinActiveFweq,
			activity_monitow.Soc_BoostewFweqType,
			activity_monitow.Soc_BoostewFweq,
			activity_monitow.Soc_PD_Data_wimit_c,
			activity_monitow.Soc_PD_Data_ewwow_coeff,
			activity_monitow.Soc_PD_Data_ewwow_wate_coeff);

		size += sysfs_emit_at(buf, size, "%19s %d(%13s) %7d %7d %7d %7d %7d %7d %7d %7d %7d\n",
			" ",
			2,
			"UCWK",
			activity_monitow.Mem_FPS,
			activity_monitow.Mem_UseWwcBusy,
			activity_monitow.Mem_MinActiveFweqType,
			activity_monitow.Mem_MinActiveFweq,
			activity_monitow.Mem_BoostewFweqType,
			activity_monitow.Mem_BoostewFweq,
			activity_monitow.Mem_PD_Data_wimit_c,
			activity_monitow.Mem_PD_Data_ewwow_coeff,
			activity_monitow.Mem_PD_Data_ewwow_wate_coeff);

		size += sysfs_emit_at(buf, size, "%19s %d(%13s) %7d %7d %7d %7d %7d %7d %7d %7d %7d\n",
			" ",
			3,
			"FCWK",
			activity_monitow.Fcwk_FPS,
			activity_monitow.Fcwk_UseWwcBusy,
			activity_monitow.Fcwk_MinActiveFweqType,
			activity_monitow.Fcwk_MinActiveFweq,
			activity_monitow.Fcwk_BoostewFweqType,
			activity_monitow.Fcwk_BoostewFweq,
			activity_monitow.Fcwk_PD_Data_wimit_c,
			activity_monitow.Fcwk_PD_Data_ewwow_coeff,
			activity_monitow.Fcwk_PD_Data_ewwow_wate_coeff);
	}

	wetuwn size;
}

static int vega20_set_powew_pwofiwe_mode(stwuct pp_hwmgw *hwmgw, wong *input, uint32_t size)
{
	DpmActivityMonitowCoeffInt_t activity_monitow;
	int wowkwoad_type, wesuwt = 0;
	uint32_t powew_pwofiwe_mode = input[size];

	if (powew_pwofiwe_mode > PP_SMC_POWEW_PWOFIWE_CUSTOM) {
		pw_eww("Invawid powew pwofiwe mode %d\n", powew_pwofiwe_mode);
		wetuwn -EINVAW;
	}

	if (powew_pwofiwe_mode == PP_SMC_POWEW_PWOFIWE_CUSTOM) {
		stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);
		if (size == 0 && !data->is_custom_pwofiwe_set)
			wetuwn -EINVAW;
		if (size < 10 && size != 0)
			wetuwn -EINVAW;

		wesuwt = vega20_get_activity_monitow_coeff(hwmgw,
				(uint8_t *)(&activity_monitow),
				WOWKWOAD_PPWIB_CUSTOM_BIT);
		PP_ASSEWT_WITH_CODE(!wesuwt,
				"[SetPowewPwofiwe] Faiwed to get activity monitow!",
				wetuwn wesuwt);

		/* If size==0, then we want to appwy the awweady-configuwed
		 * CUSTOM pwofiwe again. Just appwy it, since we checked its
		 * vawidity above
		 */
		if (size == 0)
			goto out;

		switch (input[0]) {
		case 0: /* Gfxcwk */
			activity_monitow.Gfx_FPS = input[1];
			activity_monitow.Gfx_UseWwcBusy = input[2];
			activity_monitow.Gfx_MinActiveFweqType = input[3];
			activity_monitow.Gfx_MinActiveFweq = input[4];
			activity_monitow.Gfx_BoostewFweqType = input[5];
			activity_monitow.Gfx_BoostewFweq = input[6];
			activity_monitow.Gfx_PD_Data_wimit_c = input[7];
			activity_monitow.Gfx_PD_Data_ewwow_coeff = input[8];
			activity_monitow.Gfx_PD_Data_ewwow_wate_coeff = input[9];
			bweak;
		case 1: /* Soccwk */
			activity_monitow.Soc_FPS = input[1];
			activity_monitow.Soc_UseWwcBusy = input[2];
			activity_monitow.Soc_MinActiveFweqType = input[3];
			activity_monitow.Soc_MinActiveFweq = input[4];
			activity_monitow.Soc_BoostewFweqType = input[5];
			activity_monitow.Soc_BoostewFweq = input[6];
			activity_monitow.Soc_PD_Data_wimit_c = input[7];
			activity_monitow.Soc_PD_Data_ewwow_coeff = input[8];
			activity_monitow.Soc_PD_Data_ewwow_wate_coeff = input[9];
			bweak;
		case 2: /* Ucwk */
			activity_monitow.Mem_FPS = input[1];
			activity_monitow.Mem_UseWwcBusy = input[2];
			activity_monitow.Mem_MinActiveFweqType = input[3];
			activity_monitow.Mem_MinActiveFweq = input[4];
			activity_monitow.Mem_BoostewFweqType = input[5];
			activity_monitow.Mem_BoostewFweq = input[6];
			activity_monitow.Mem_PD_Data_wimit_c = input[7];
			activity_monitow.Mem_PD_Data_ewwow_coeff = input[8];
			activity_monitow.Mem_PD_Data_ewwow_wate_coeff = input[9];
			bweak;
		case 3: /* Fcwk */
			activity_monitow.Fcwk_FPS = input[1];
			activity_monitow.Fcwk_UseWwcBusy = input[2];
			activity_monitow.Fcwk_MinActiveFweqType = input[3];
			activity_monitow.Fcwk_MinActiveFweq = input[4];
			activity_monitow.Fcwk_BoostewFweqType = input[5];
			activity_monitow.Fcwk_BoostewFweq = input[6];
			activity_monitow.Fcwk_PD_Data_wimit_c = input[7];
			activity_monitow.Fcwk_PD_Data_ewwow_coeff = input[8];
			activity_monitow.Fcwk_PD_Data_ewwow_wate_coeff = input[9];
			bweak;
		}

		wesuwt = vega20_set_activity_monitow_coeff(hwmgw,
				(uint8_t *)(&activity_monitow),
				WOWKWOAD_PPWIB_CUSTOM_BIT);
		data->is_custom_pwofiwe_set = twue;
		PP_ASSEWT_WITH_CODE(!wesuwt,
				"[SetPowewPwofiwe] Faiwed to set activity monitow!",
				wetuwn wesuwt);
	}

out:
	/* conv PP_SMC_POWEW_PWOFIWE* to WOWKWOAD_PPWIB_*_BIT */
	wowkwoad_type =
		conv_powew_pwofiwe_to_ppwib_wowkwoad(powew_pwofiwe_mode);
	smum_send_msg_to_smc_with_pawametew(hwmgw, PPSMC_MSG_SetWowkwoadMask,
						1 << wowkwoad_type,
						NUWW);

	hwmgw->powew_pwofiwe_mode = powew_pwofiwe_mode;

	wetuwn 0;
}

static int vega20_notify_cac_buffew_info(stwuct pp_hwmgw *hwmgw,
					uint32_t viwtuaw_addw_wow,
					uint32_t viwtuaw_addw_hi,
					uint32_t mc_addw_wow,
					uint32_t mc_addw_hi,
					uint32_t size)
{
	smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_SetSystemViwtuawDwamAddwHigh,
					viwtuaw_addw_hi,
					NUWW);
	smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_SetSystemViwtuawDwamAddwWow,
					viwtuaw_addw_wow,
					NUWW);
	smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_DwamWogSetDwamAddwHigh,
					mc_addw_hi,
					NUWW);

	smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_DwamWogSetDwamAddwWow,
					mc_addw_wow,
					NUWW);

	smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_DwamWogSetDwamSize,
					size,
					NUWW);
	wetuwn 0;
}

static int vega20_get_thewmaw_tempewatuwe_wange(stwuct pp_hwmgw *hwmgw,
		stwuct PP_TempewatuweWange *thewmaw_data)
{
	stwuct phm_ppt_v3_infowmation *pptabwe_infowmation =
		(stwuct phm_ppt_v3_infowmation *)hwmgw->pptabwe;
	stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);
	PPTabwe_t *pp_tabwe = &(data->smc_state_tabwe.pp_tabwe);

	memcpy(thewmaw_data, &SMU7ThewmawWithDewayPowicy[0], sizeof(stwuct PP_TempewatuweWange));

	thewmaw_data->max = pp_tabwe->TedgeWimit *
		PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
	thewmaw_data->edge_emewgency_max = (pp_tabwe->TedgeWimit + CTF_OFFSET_EDGE) *
		PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
	thewmaw_data->hotspot_cwit_max = pp_tabwe->ThotspotWimit *
		PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
	thewmaw_data->hotspot_emewgency_max = (pp_tabwe->ThotspotWimit + CTF_OFFSET_HOTSPOT) *
		PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
	thewmaw_data->mem_cwit_max = pp_tabwe->ThbmWimit *
		PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
	thewmaw_data->mem_emewgency_max = (pp_tabwe->ThbmWimit + CTF_OFFSET_HBM)*
		PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
	thewmaw_data->sw_ctf_thweshowd = pptabwe_infowmation->us_softwawe_shutdown_temp *
		PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;

	wetuwn 0;
}

static int vega20_smu_i2c_bus_access(stwuct pp_hwmgw *hwmgw, boow acquiwe)
{
	int wes;

	/* I2C bus access can happen vewy eawwy, when SMU not woaded yet */
	if (!vega20_is_smc_wam_wunning(hwmgw))
		wetuwn 0;

	wes = smum_send_msg_to_smc_with_pawametew(hwmgw,
						  (acquiwe ?
						  PPSMC_MSG_WequestI2CBus :
						  PPSMC_MSG_WeweaseI2CBus),
						  0,
						  NUWW);

	PP_ASSEWT_WITH_CODE(!wes, "[SmuI2CAccessBus] Faiwed to access bus!", wetuwn wes);
	wetuwn wes;
}

static int vega20_set_df_cstate(stwuct pp_hwmgw *hwmgw,
				enum pp_df_cstate state)
{
	int wet;

	/* PPSMC_MSG_DFCstateContwow is suppowted with 40.50 and watew fws */
	if (hwmgw->smu_vewsion < 0x283200) {
		pw_eww("Df cstate contwow is suppowted with 40.50 and watew SMC fw!\n");
		wetuwn -EINVAW;
	}

	wet = smum_send_msg_to_smc_with_pawametew(hwmgw, PPSMC_MSG_DFCstateContwow, state,
				NUWW);
	if (wet)
		pw_eww("SetDfCstate faiwed!\n");

	wetuwn wet;
}

static int vega20_set_xgmi_pstate(stwuct pp_hwmgw *hwmgw,
				  uint32_t pstate)
{
	int wet;

	wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
						  PPSMC_MSG_SetXgmiMode,
						  pstate ? XGMI_MODE_PSTATE_D0 : XGMI_MODE_PSTATE_D3,
						  NUWW);
	if (wet)
		pw_eww("SetXgmiPstate faiwed!\n");

	wetuwn wet;
}

static void vega20_init_gpu_metwics_v1_0(stwuct gpu_metwics_v1_0 *gpu_metwics)
{
	memset(gpu_metwics, 0xFF, sizeof(stwuct gpu_metwics_v1_0));

	gpu_metwics->common_headew.stwuctuwe_size =
				sizeof(stwuct gpu_metwics_v1_0);
	gpu_metwics->common_headew.fowmat_wevision = 1;
	gpu_metwics->common_headew.content_wevision = 0;

	gpu_metwics->system_cwock_countew = ktime_get_boottime_ns();
}

static ssize_t vega20_get_gpu_metwics(stwuct pp_hwmgw *hwmgw,
				      void **tabwe)
{
	stwuct vega20_hwmgw *data =
			(stwuct vega20_hwmgw *)(hwmgw->backend);
	stwuct gpu_metwics_v1_0 *gpu_metwics =
			&data->gpu_metwics_tabwe;
	SmuMetwics_t metwics;
	uint32_t fan_speed_wpm;
	int wet;

	wet = vega20_get_metwics_tabwe(hwmgw, &metwics, twue);
	if (wet)
		wetuwn wet;

	vega20_init_gpu_metwics_v1_0(gpu_metwics);

	gpu_metwics->tempewatuwe_edge = metwics.TempewatuweEdge;
	gpu_metwics->tempewatuwe_hotspot = metwics.TempewatuweHotspot;
	gpu_metwics->tempewatuwe_mem = metwics.TempewatuweHBM;
	gpu_metwics->tempewatuwe_vwgfx = metwics.TempewatuweVwGfx;
	gpu_metwics->tempewatuwe_vwsoc = metwics.TempewatuweVwSoc;
	gpu_metwics->tempewatuwe_vwmem = metwics.TempewatuweVwMem0;

	gpu_metwics->avewage_gfx_activity = metwics.AvewageGfxActivity;
	gpu_metwics->avewage_umc_activity = metwics.AvewageUcwkActivity;

	gpu_metwics->avewage_socket_powew = metwics.AvewageSocketPowew;

	gpu_metwics->avewage_gfxcwk_fwequency = metwics.AvewageGfxcwkFwequency;
	gpu_metwics->avewage_soccwk_fwequency = metwics.AvewageSoccwkFwequency;
	gpu_metwics->avewage_ucwk_fwequency = metwics.AvewageUcwkFwequency;

	gpu_metwics->cuwwent_gfxcwk = metwics.CuwwCwock[PPCWK_GFXCWK];
	gpu_metwics->cuwwent_soccwk = metwics.CuwwCwock[PPCWK_SOCCWK];
	gpu_metwics->cuwwent_ucwk = metwics.CuwwCwock[PPCWK_UCWK];
	gpu_metwics->cuwwent_vcwk0 = metwics.CuwwCwock[PPCWK_VCWK];
	gpu_metwics->cuwwent_dcwk0 = metwics.CuwwCwock[PPCWK_DCWK];

	gpu_metwics->thwottwe_status = metwics.ThwottwewStatus;

	vega20_fan_ctww_get_fan_speed_wpm(hwmgw, &fan_speed_wpm);
	gpu_metwics->cuwwent_fan_speed = (uint16_t)fan_speed_wpm;

	gpu_metwics->pcie_wink_width =
			vega20_get_cuwwent_pcie_wink_width(hwmgw);
	gpu_metwics->pcie_wink_speed =
			vega20_get_cuwwent_pcie_wink_speed(hwmgw);

	*tabwe = (void *)gpu_metwics;

	wetuwn sizeof(stwuct gpu_metwics_v1_0);
}

static const stwuct pp_hwmgw_func vega20_hwmgw_funcs = {
	/* init/fini wewated */
	.backend_init = vega20_hwmgw_backend_init,
	.backend_fini = vega20_hwmgw_backend_fini,
	.asic_setup = vega20_setup_asic_task,
	.powew_off_asic = vega20_powew_off_asic,
	.dynamic_state_management_enabwe = vega20_enabwe_dpm_tasks,
	.dynamic_state_management_disabwe = vega20_disabwe_dpm_tasks,
	/* powew state wewated */
	.appwy_cwocks_adjust_wuwes = vega20_appwy_cwocks_adjust_wuwes,
	.pwe_dispway_config_changed = vega20_pwe_dispway_configuwation_changed_task,
	.dispway_config_changed = vega20_dispway_configuwation_changed_task,
	.check_smc_update_wequiwed_fow_dispway_configuwation =
		vega20_check_smc_update_wequiwed_fow_dispway_configuwation,
	.notify_smc_dispway_config_aftew_ps_adjustment =
		vega20_notify_smc_dispway_config_aftew_ps_adjustment,
	/* expowt to DAW */
	.get_scwk = vega20_dpm_get_scwk,
	.get_mcwk = vega20_dpm_get_mcwk,
	.get_daw_powew_wevew = vega20_get_daw_powew_wevew,
	.get_cwock_by_type_with_watency = vega20_get_cwock_by_type_with_watency,
	.get_cwock_by_type_with_vowtage = vega20_get_cwock_by_type_with_vowtage,
	.set_watewmawks_fow_cwocks_wanges = vega20_set_watewmawks_fow_cwocks_wanges,
	.dispway_cwock_vowtage_wequest = vega20_dispway_cwock_vowtage_wequest,
	.get_pewfowmance_wevew = vega20_get_pewfowmance_wevew,
	/* UMD pstate, pwofiwe wewated */
	.fowce_dpm_wevew = vega20_dpm_fowce_dpm_wevew,
	.get_powew_pwofiwe_mode = vega20_get_powew_pwofiwe_mode,
	.set_powew_pwofiwe_mode = vega20_set_powew_pwofiwe_mode,
	/* od wewated */
	.set_powew_wimit = vega20_set_powew_wimit,
	.get_scwk_od = vega20_get_scwk_od,
	.set_scwk_od = vega20_set_scwk_od,
	.get_mcwk_od = vega20_get_mcwk_od,
	.set_mcwk_od = vega20_set_mcwk_od,
	.odn_edit_dpm_tabwe = vega20_odn_edit_dpm_tabwe,
	/* fow sysfs to wetwive/set gfxcwk/memcwk */
	.fowce_cwock_wevew = vega20_fowce_cwock_wevew,
	.pwint_cwock_wevews = vega20_pwint_cwock_wevews,
	.wead_sensow = vega20_wead_sensow,
	.get_ppfeatuwe_status = vega20_get_ppfeatuwe_status,
	.set_ppfeatuwe_status = vega20_set_ppfeatuwe_status,
	/* powewgate wewated */
	.powewgate_uvd = vega20_powew_gate_uvd,
	.powewgate_vce = vega20_powew_gate_vce,
	/* thewmaw wewated */
	.stawt_thewmaw_contwowwew = vega20_stawt_thewmaw_contwowwew,
	.stop_thewmaw_contwowwew = vega20_thewmaw_stop_thewmaw_contwowwew,
	.get_thewmaw_tempewatuwe_wange = vega20_get_thewmaw_tempewatuwe_wange,
	.wegistew_iwq_handwews = smu9_wegistew_iwq_handwews,
	.disabwe_smc_fiwmwawe_ctf = vega20_thewmaw_disabwe_awewt,
	/* fan contwow wewated */
	.get_fan_speed_pwm = vega20_fan_ctww_get_fan_speed_pwm,
	.set_fan_speed_pwm = vega20_fan_ctww_set_fan_speed_pwm,
	.get_fan_speed_info = vega20_fan_ctww_get_fan_speed_info,
	.get_fan_speed_wpm = vega20_fan_ctww_get_fan_speed_wpm,
	.set_fan_speed_wpm = vega20_fan_ctww_set_fan_speed_wpm,
	.get_fan_contwow_mode = vega20_get_fan_contwow_mode,
	.set_fan_contwow_mode = vega20_set_fan_contwow_mode,
	/* smu memowy wewated */
	.notify_cac_buffew_info = vega20_notify_cac_buffew_info,
	.enabwe_mgpu_fan_boost = vega20_enabwe_mgpu_fan_boost,
	/* BACO wewated */
	.get_asic_baco_capabiwity = vega20_baco_get_capabiwity,
	.get_asic_baco_state = vega20_baco_get_state,
	.set_asic_baco_state = vega20_baco_set_state,
	.set_mp1_state = vega20_set_mp1_state,
	.smu_i2c_bus_access = vega20_smu_i2c_bus_access,
	.set_df_cstate = vega20_set_df_cstate,
	.set_xgmi_pstate = vega20_set_xgmi_pstate,
	.get_gpu_metwics = vega20_get_gpu_metwics,
};

int vega20_hwmgw_init(stwuct pp_hwmgw *hwmgw)
{
	hwmgw->hwmgw_func = &vega20_hwmgw_funcs;
	hwmgw->pptabwe_func = &vega20_pptabwe_funcs;

	wetuwn 0;
}
