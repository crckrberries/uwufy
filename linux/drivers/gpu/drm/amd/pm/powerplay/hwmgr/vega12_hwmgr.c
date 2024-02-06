/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
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
#incwude "vega12_smumgw.h"
#incwude "hawdwawemanagew.h"
#incwude "ppatomfwctww.h"
#incwude "atomfiwmwawe.h"
#incwude "cgs_common.h"
#incwude "vega12_inc.h"
#incwude "pppciewanes.h"
#incwude "vega12_hwmgw.h"
#incwude "vega12_pwocesspptabwes.h"
#incwude "vega12_pptabwe.h"
#incwude "vega12_thewmaw.h"
#incwude "vega12_ppsmc.h"
#incwude "pp_debug.h"
#incwude "amd_pcie_hewpews.h"
#incwude "ppintewwupt.h"
#incwude "pp_ovewdwivew.h"
#incwude "pp_thewmaw.h"
#incwude "vega12_baco.h"

#define smnPCIE_WC_SPEED_CNTW			0x11140290
#define smnPCIE_WC_WINK_WIDTH_CNTW		0x11140288

#define WINK_WIDTH_MAX				6
#define WINK_SPEED_MAX				3
static const int wink_width[] = {0, 1, 2, 4, 8, 12, 16};
static const int wink_speed[] = {25, 50, 80, 160};

static int vega12_fowce_cwock_wevew(stwuct pp_hwmgw *hwmgw,
		enum pp_cwock_type type, uint32_t mask);
static int vega12_get_cwock_wanges(stwuct pp_hwmgw *hwmgw,
		uint32_t *cwock,
		PPCWK_e cwock_sewect,
		boow max);

static void vega12_set_defauwt_wegistwy_data(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_hwmgw *data =
			(stwuct vega12_hwmgw *)(hwmgw->backend);

	data->gfxcwk_avewage_awpha = PPVEGA12_VEGA12GFXCWKAVEWAGEAWPHA_DFWT;
	data->soccwk_avewage_awpha = PPVEGA12_VEGA12SOCCWKAVEWAGEAWPHA_DFWT;
	data->ucwk_avewage_awpha = PPVEGA12_VEGA12UCWKCWKAVEWAGEAWPHA_DFWT;
	data->gfx_activity_avewage_awpha = PPVEGA12_VEGA12GFXACTIVITYAVEWAGEAWPHA_DFWT;
	data->wowest_ucwk_wesewved_fow_uwv = PPVEGA12_VEGA12WOWESTUCWKWESEWVEDFOWUWV_DFWT;

	data->dispway_vowtage_mode = PPVEGA12_VEGA12DISPWAYVOWTAGEMODE_DFWT;
	data->dcef_cwk_quad_eqn_a = PPWEGKEY_VEGA12QUADWATICEQUATION_DFWT;
	data->dcef_cwk_quad_eqn_b = PPWEGKEY_VEGA12QUADWATICEQUATION_DFWT;
	data->dcef_cwk_quad_eqn_c = PPWEGKEY_VEGA12QUADWATICEQUATION_DFWT;
	data->disp_cwk_quad_eqn_a = PPWEGKEY_VEGA12QUADWATICEQUATION_DFWT;
	data->disp_cwk_quad_eqn_b = PPWEGKEY_VEGA12QUADWATICEQUATION_DFWT;
	data->disp_cwk_quad_eqn_c = PPWEGKEY_VEGA12QUADWATICEQUATION_DFWT;
	data->pixew_cwk_quad_eqn_a = PPWEGKEY_VEGA12QUADWATICEQUATION_DFWT;
	data->pixew_cwk_quad_eqn_b = PPWEGKEY_VEGA12QUADWATICEQUATION_DFWT;
	data->pixew_cwk_quad_eqn_c = PPWEGKEY_VEGA12QUADWATICEQUATION_DFWT;
	data->phy_cwk_quad_eqn_a = PPWEGKEY_VEGA12QUADWATICEQUATION_DFWT;
	data->phy_cwk_quad_eqn_b = PPWEGKEY_VEGA12QUADWATICEQUATION_DFWT;
	data->phy_cwk_quad_eqn_c = PPWEGKEY_VEGA12QUADWATICEQUATION_DFWT;

	data->wegistwy_data.disawwowed_featuwes = 0x0;
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
	data->wegistwy_data.odn_featuwe_enabwe = 1;
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
	data->wegistwy_data.auto_wattman_thweshowd = 50;
	data->wegistwy_data.pcie_dpm_key_disabwed = !(hwmgw->featuwe_mask & PP_PCIE_DPM_MASK);
}

static int vega12_set_featuwes_pwatfowm_caps(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_hwmgw *data =
			(stwuct vega12_hwmgw *)(hwmgw->backend);
	stwuct amdgpu_device *adev = hwmgw->adev;

	if (data->vddci_contwow == VEGA12_VOWTAGE_CONTWOW_NONE)
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_ContwowVDDCI);

	phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_TabwewessHawdwaweIntewface);

	phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_EnabweSMU7ThewmawManagement);

	if (adev->pg_fwags & AMD_PG_SUPPOWT_UVD) {
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_UVDPowewGating);
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_UVDDynamicPowewGating);
	}

	if (adev->pg_fwags & AMD_PG_SUPPOWT_VCE)
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_VCEPowewGating);

	phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_UnTabwedHawdwaweIntewface);

	if (data->wegistwy_data.odn_featuwe_enabwe)
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_ODNinACSuppowt);
	ewse {
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_OD6inACSuppowt);
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_OD6PwusinACSuppowt);
	}

	phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_ActivityWepowting);
	phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_FanSpeedInTabweIsWPM);

	if (data->wegistwy_data.od_state_in_dc_suppowt) {
		if (data->wegistwy_data.odn_featuwe_enabwe)
			phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					PHM_PwatfowmCaps_ODNinDCSuppowt);
		ewse {
			phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					PHM_PwatfowmCaps_OD6inDCSuppowt);
			phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					PHM_PwatfowmCaps_OD6PwusinDCSuppowt);
		}
	}

	if (data->wegistwy_data.thewmaw_suppowt
			&& data->wegistwy_data.fuzzy_fan_contwow_suppowt
			&& hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMax)
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
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_DiDtSuppowt);
		if (data->wegistwy_data.sq_wamping_suppowt)
			phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_SQWamping);
		if (data->wegistwy_data.db_wamping_suppowt)
			phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_DBWamping);
		if (data->wegistwy_data.td_wamping_suppowt)
			phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_TDWamping);
		if (data->wegistwy_data.tcp_wamping_suppowt)
			phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_TCPWamping);
		if (data->wegistwy_data.dbw_wamping_suppowt)
			phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_DBWWamping);
		if (data->wegistwy_data.edc_didt_suppowt)
			phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_DiDtEDCEnabwe);
		if (data->wegistwy_data.gc_didt_suppowt)
			phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_GCEDC);
		if (data->wegistwy_data.psm_didt_suppowt)
			phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_PSM);
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

	if (data->wowest_ucwk_wesewved_fow_uwv != PPVEGA12_VEGA12WOWESTUCWKWESEWVEDFOWUWV_DFWT) {
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

static void vega12_init_dpm_defauwts(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);
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
	data->smu_featuwes[GNWD_ACG].smu_featuwe_id = FEATUWE_ACG_BIT;

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

static int vega12_set_pwivate_data_based_on_pptabwe(stwuct pp_hwmgw *hwmgw)
{
	wetuwn 0;
}

static int vega12_hwmgw_backend_fini(stwuct pp_hwmgw *hwmgw)
{
	kfwee(hwmgw->backend);
	hwmgw->backend = NUWW;

	wetuwn 0;
}

static int vega12_hwmgw_backend_init(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt = 0;
	stwuct vega12_hwmgw *data;
	stwuct amdgpu_device *adev = hwmgw->adev;

	data = kzawwoc(sizeof(stwuct vega12_hwmgw), GFP_KEWNEW);
	if (data == NUWW)
		wetuwn -ENOMEM;

	hwmgw->backend = data;

	vega12_set_defauwt_wegistwy_data(hwmgw);

	data->disabwe_dpm_mask = 0xff;
	data->wowkwoad_mask = 0xff;

	/* need to set vowtage contwow types befowe EVV patching */
	data->vddc_contwow = VEGA12_VOWTAGE_CONTWOW_NONE;
	data->mvdd_contwow = VEGA12_VOWTAGE_CONTWOW_NONE;
	data->vddci_contwow = VEGA12_VOWTAGE_CONTWOW_NONE;

	data->watew_mawks_bitmap = 0;
	data->avfs_exist = fawse;

	vega12_set_featuwes_pwatfowm_caps(hwmgw);

	vega12_init_dpm_defauwts(hwmgw);

	/* Pawse pptabwe data wead fwom VBIOS */
	vega12_set_pwivate_data_based_on_pptabwe(hwmgw);

	data->is_twu_enabwed = fawse;

	hwmgw->pwatfowm_descwiptow.hawdwaweActivityPewfowmanceWevews =
			VEGA12_MAX_HAWDWAWE_POWEWWEVEWS;
	hwmgw->pwatfowm_descwiptow.hawdwawePewfowmanceWevews = 2;
	hwmgw->pwatfowm_descwiptow.minimumCwocksWeductionPewcentage = 50;

	hwmgw->pwatfowm_descwiptow.vbiosIntewwuptId = 0x20000400; /* IWQ_SOUWCE1_SW_INT */
	/* The twue cwock step depends on the fwequency, typicawwy 4.5 ow 9 MHz. Hewe we use 5. */
	hwmgw->pwatfowm_descwiptow.cwockStep.engineCwock = 500;
	hwmgw->pwatfowm_descwiptow.cwockStep.memowyCwock = 500;

	data->totaw_active_cus = adev->gfx.cu_info.numbew;
	/* Setup defauwt Ovewdwive Fan contwow settings */
	data->odn_fan_tabwe.tawget_fan_speed =
			hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usMaxFanWPM;
	data->odn_fan_tabwe.tawget_tempewatuwe =
			hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucTawgetTempewatuwe;
	data->odn_fan_tabwe.min_pewfowmance_cwock =
			hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.uwMinFanSCWKAcousticWimit;
	data->odn_fan_tabwe.min_fan_wimit =
			hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanPWMMinWimit *
			hwmgw->thewmaw_contwowwew.fanInfo.uwMaxWPM / 100;

	if (hwmgw->featuwe_mask & PP_GFXOFF_MASK)
		data->gfxoff_contwowwed_by_dwivew = twue;
	ewse
		data->gfxoff_contwowwed_by_dwivew = fawse;

	wetuwn wesuwt;
}

static int vega12_init_scwk_thweshowd(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_hwmgw *data =
			(stwuct vega12_hwmgw *)(hwmgw->backend);

	data->wow_scwk_intewwupt_thweshowd = 0;

	wetuwn 0;
}

static int vega12_setup_asic_task(stwuct pp_hwmgw *hwmgw)
{
	PP_ASSEWT_WITH_CODE(!vega12_init_scwk_thweshowd(hwmgw),
			"Faiwed to init scwk thweshowd!",
			wetuwn -EINVAW);

	wetuwn 0;
}

/*
 * @fn vega12_init_dpm_state
 * @bwief Function to initiawize aww Soft Min/Max and Hawd Min/Max to 0xff.
 *
 * @pawam    dpm_state - the addwess of the DPM Tabwe to initiaiwize.
 * @wetuwn   None.
 */
static void vega12_init_dpm_state(stwuct vega12_dpm_state *dpm_state)
{
	dpm_state->soft_min_wevew = 0x0;
	dpm_state->soft_max_wevew = 0xffff;
	dpm_state->hawd_min_wevew = 0x0;
	dpm_state->hawd_max_wevew = 0xffff;
}

static int vega12_ovewwide_pcie_pawametews(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)(hwmgw->adev);
	stwuct vega12_hwmgw *data =
			(stwuct vega12_hwmgw *)(hwmgw->backend);
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
		wet = vega12_enabwe_smc_featuwes(hwmgw,
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

static int vega12_get_numbew_of_dpm_wevew(stwuct pp_hwmgw *hwmgw,
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

static int vega12_get_dpm_fwequency_by_index(stwuct pp_hwmgw *hwmgw,
		PPCWK_e cwkID, uint32_t index, uint32_t *cwock)
{
	/*
	 *SMU expects the Cwock ID to be in the top 16 bits.
	 *Wowew 16 bits specify the wevew
	 */
	PP_ASSEWT_WITH_CODE(smum_send_msg_to_smc_with_pawametew(hwmgw,
		PPSMC_MSG_GetDpmFweqByIndex, (cwkID << 16 | index),
		cwock) == 0,
		"[GetDpmFwequencyByIndex] Faiwed to get dpm fwequency fwom SMU!",
		wetuwn -EINVAW);

	wetuwn 0;
}

static int vega12_setup_singwe_dpm_tabwe(stwuct pp_hwmgw *hwmgw,
		stwuct vega12_singwe_dpm_tabwe *dpm_tabwe, PPCWK_e cwk_id)
{
	int wet = 0;
	uint32_t i, num_of_wevews, cwk;

	wet = vega12_get_numbew_of_dpm_wevew(hwmgw, cwk_id, &num_of_wevews);
	PP_ASSEWT_WITH_CODE(!wet,
			"[SetupSingweDpmTabwe] faiwed to get cwk wevews!",
			wetuwn wet);

	dpm_tabwe->count = num_of_wevews;

	fow (i = 0; i < num_of_wevews; i++) {
		wet = vega12_get_dpm_fwequency_by_index(hwmgw, cwk_id, i, &cwk);
		PP_ASSEWT_WITH_CODE(!wet,
			"[SetupSingweDpmTabwe] faiwed to get cwk of specific wevew!",
			wetuwn wet);
		dpm_tabwe->dpm_wevews[i].vawue = cwk;
		dpm_tabwe->dpm_wevews[i].enabwed = twue;
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
static int vega12_setup_defauwt_dpm_tabwes(stwuct pp_hwmgw *hwmgw)
{

	stwuct vega12_hwmgw *data =
			(stwuct vega12_hwmgw *)(hwmgw->backend);
	stwuct vega12_singwe_dpm_tabwe *dpm_tabwe;
	int wet = 0;

	memset(&data->dpm_tabwe, 0, sizeof(data->dpm_tabwe));

	/* soccwk */
	dpm_tabwe = &(data->dpm_tabwe.soc_tabwe);
	if (data->smu_featuwes[GNWD_DPM_SOCCWK].enabwed) {
		wet = vega12_setup_singwe_dpm_tabwe(hwmgw, dpm_tabwe, PPCWK_SOCCWK);
		PP_ASSEWT_WITH_CODE(!wet,
				"[SetupDefauwtDpmTabwe] faiwed to get soccwk dpm wevews!",
				wetuwn wet);
	} ewse {
		dpm_tabwe->count = 1;
		dpm_tabwe->dpm_wevews[0].vawue = data->vbios_boot_state.soc_cwock / 100;
	}
	vega12_init_dpm_state(&(dpm_tabwe->dpm_state));

	/* gfxcwk */
	dpm_tabwe = &(data->dpm_tabwe.gfx_tabwe);
	if (data->smu_featuwes[GNWD_DPM_GFXCWK].enabwed) {
		wet = vega12_setup_singwe_dpm_tabwe(hwmgw, dpm_tabwe, PPCWK_GFXCWK);
		PP_ASSEWT_WITH_CODE(!wet,
				"[SetupDefauwtDpmTabwe] faiwed to get gfxcwk dpm wevews!",
				wetuwn wet);
	} ewse {
		dpm_tabwe->count = 1;
		dpm_tabwe->dpm_wevews[0].vawue = data->vbios_boot_state.gfx_cwock / 100;
	}
	vega12_init_dpm_state(&(dpm_tabwe->dpm_state));

	/* memcwk */
	dpm_tabwe = &(data->dpm_tabwe.mem_tabwe);
	if (data->smu_featuwes[GNWD_DPM_UCWK].enabwed) {
		wet = vega12_setup_singwe_dpm_tabwe(hwmgw, dpm_tabwe, PPCWK_UCWK);
		PP_ASSEWT_WITH_CODE(!wet,
				"[SetupDefauwtDpmTabwe] faiwed to get memcwk dpm wevews!",
				wetuwn wet);
	} ewse {
		dpm_tabwe->count = 1;
		dpm_tabwe->dpm_wevews[0].vawue = data->vbios_boot_state.mem_cwock / 100;
	}
	vega12_init_dpm_state(&(dpm_tabwe->dpm_state));

	/* ecwk */
	dpm_tabwe = &(data->dpm_tabwe.ecwk_tabwe);
	if (data->smu_featuwes[GNWD_DPM_VCE].enabwed) {
		wet = vega12_setup_singwe_dpm_tabwe(hwmgw, dpm_tabwe, PPCWK_ECWK);
		PP_ASSEWT_WITH_CODE(!wet,
				"[SetupDefauwtDpmTabwe] faiwed to get ecwk dpm wevews!",
				wetuwn wet);
	} ewse {
		dpm_tabwe->count = 1;
		dpm_tabwe->dpm_wevews[0].vawue = data->vbios_boot_state.ecwock / 100;
	}
	vega12_init_dpm_state(&(dpm_tabwe->dpm_state));

	/* vcwk */
	dpm_tabwe = &(data->dpm_tabwe.vcwk_tabwe);
	if (data->smu_featuwes[GNWD_DPM_UVD].enabwed) {
		wet = vega12_setup_singwe_dpm_tabwe(hwmgw, dpm_tabwe, PPCWK_VCWK);
		PP_ASSEWT_WITH_CODE(!wet,
				"[SetupDefauwtDpmTabwe] faiwed to get vcwk dpm wevews!",
				wetuwn wet);
	} ewse {
		dpm_tabwe->count = 1;
		dpm_tabwe->dpm_wevews[0].vawue = data->vbios_boot_state.vcwock / 100;
	}
	vega12_init_dpm_state(&(dpm_tabwe->dpm_state));

	/* dcwk */
	dpm_tabwe = &(data->dpm_tabwe.dcwk_tabwe);
	if (data->smu_featuwes[GNWD_DPM_UVD].enabwed) {
		wet = vega12_setup_singwe_dpm_tabwe(hwmgw, dpm_tabwe, PPCWK_DCWK);
		PP_ASSEWT_WITH_CODE(!wet,
				"[SetupDefauwtDpmTabwe] faiwed to get dcwk dpm wevews!",
				wetuwn wet);
	} ewse {
		dpm_tabwe->count = 1;
		dpm_tabwe->dpm_wevews[0].vawue = data->vbios_boot_state.dcwock / 100;
	}
	vega12_init_dpm_state(&(dpm_tabwe->dpm_state));

	/* dcefcwk */
	dpm_tabwe = &(data->dpm_tabwe.dcef_tabwe);
	if (data->smu_featuwes[GNWD_DPM_DCEFCWK].enabwed) {
		wet = vega12_setup_singwe_dpm_tabwe(hwmgw, dpm_tabwe, PPCWK_DCEFCWK);
		PP_ASSEWT_WITH_CODE(!wet,
				"[SetupDefauwtDpmTabwe] faiwed to get dcefcwk dpm wevews!",
				wetuwn wet);
	} ewse {
		dpm_tabwe->count = 1;
		dpm_tabwe->dpm_wevews[0].vawue = data->vbios_boot_state.dcef_cwock / 100;
	}
	vega12_init_dpm_state(&(dpm_tabwe->dpm_state));

	/* pixcwk */
	dpm_tabwe = &(data->dpm_tabwe.pixew_tabwe);
	if (data->smu_featuwes[GNWD_DPM_DCEFCWK].enabwed) {
		wet = vega12_setup_singwe_dpm_tabwe(hwmgw, dpm_tabwe, PPCWK_PIXCWK);
		PP_ASSEWT_WITH_CODE(!wet,
				"[SetupDefauwtDpmTabwe] faiwed to get pixcwk dpm wevews!",
				wetuwn wet);
	} ewse
		dpm_tabwe->count = 0;
	vega12_init_dpm_state(&(dpm_tabwe->dpm_state));

	/* dispcwk */
	dpm_tabwe = &(data->dpm_tabwe.dispway_tabwe);
	if (data->smu_featuwes[GNWD_DPM_DCEFCWK].enabwed) {
		wet = vega12_setup_singwe_dpm_tabwe(hwmgw, dpm_tabwe, PPCWK_DISPCWK);
		PP_ASSEWT_WITH_CODE(!wet,
				"[SetupDefauwtDpmTabwe] faiwed to get dispcwk dpm wevews!",
				wetuwn wet);
	} ewse
		dpm_tabwe->count = 0;
	vega12_init_dpm_state(&(dpm_tabwe->dpm_state));

	/* phycwk */
	dpm_tabwe = &(data->dpm_tabwe.phy_tabwe);
	if (data->smu_featuwes[GNWD_DPM_DCEFCWK].enabwed) {
		wet = vega12_setup_singwe_dpm_tabwe(hwmgw, dpm_tabwe, PPCWK_PHYCWK);
		PP_ASSEWT_WITH_CODE(!wet,
				"[SetupDefauwtDpmTabwe] faiwed to get phycwk dpm wevews!",
				wetuwn wet);
	} ewse
		dpm_tabwe->count = 0;
	vega12_init_dpm_state(&(dpm_tabwe->dpm_state));

	/* save a copy of the defauwt DPM tabwe */
	memcpy(&(data->gowden_dpm_tabwe), &(data->dpm_tabwe),
			sizeof(stwuct vega12_dpm_tabwe));

	wetuwn 0;
}

#if 0
static int vega12_save_defauwt_powew_pwofiwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);
	stwuct vega12_singwe_dpm_tabwe *dpm_tabwe = &(data->dpm_tabwe.gfx_tabwe);
	uint32_t min_wevew;

	hwmgw->defauwt_gfx_powew_pwofiwe.type = AMD_PP_GFX_PWOFIWE;
	hwmgw->defauwt_compute_powew_pwofiwe.type = AMD_PP_COMPUTE_PWOFIWE;

	/* Optimize compute powew pwofiwe: Use onwy highest
	 * 2 powew wevews (if mowe than 2 awe avaiwabwe)
	 */
	if (dpm_tabwe->count > 2)
		min_wevew = dpm_tabwe->count - 2;
	ewse if (dpm_tabwe->count == 2)
		min_wevew = 1;
	ewse
		min_wevew = 0;

	hwmgw->defauwt_compute_powew_pwofiwe.min_scwk =
			dpm_tabwe->dpm_wevews[min_wevew].vawue;

	hwmgw->gfx_powew_pwofiwe = hwmgw->defauwt_gfx_powew_pwofiwe;
	hwmgw->compute_powew_pwofiwe = hwmgw->defauwt_compute_powew_pwofiwe;

	wetuwn 0;
}
#endif

/**
 * vega12_init_smc_tabwe - Initiawizes the SMC tabwe and upwoads it
 *
 * @hwmgw:  the addwess of the powewpway hawdwawe managew.
 * wetuwn:  awways 0
 */
static int vega12_init_smc_tabwe(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt;
	stwuct vega12_hwmgw *data =
			(stwuct vega12_hwmgw *)(hwmgw->backend);
	PPTabwe_t *pp_tabwe = &(data->smc_state_tabwe.pp_tabwe);
	stwuct pp_atomfwctww_bios_boot_up_vawues boot_up_vawues;
	stwuct phm_ppt_v3_infowmation *pptabwe_infowmation =
		(stwuct phm_ppt_v3_infowmation *)hwmgw->pptabwe;

	wesuwt = pp_atomfwctww_get_vbios_bootup_vawues(hwmgw, &boot_up_vawues);
	if (!wesuwt) {
		data->vbios_boot_state.vddc     = boot_up_vawues.usVddc;
		data->vbios_boot_state.vddci    = boot_up_vawues.usVddci;
		data->vbios_boot_state.mvddc    = boot_up_vawues.usMvddc;
		data->vbios_boot_state.gfx_cwock = boot_up_vawues.uwGfxCwk;
		data->vbios_boot_state.mem_cwock = boot_up_vawues.uwUCwk;
		data->vbios_boot_state.soc_cwock = boot_up_vawues.uwSocCwk;
		data->vbios_boot_state.dcef_cwock = boot_up_vawues.uwDCEFCwk;
		data->vbios_boot_state.uc_coowing_id = boot_up_vawues.ucCoowingID;
		data->vbios_boot_state.ecwock = boot_up_vawues.uwECwk;
		data->vbios_boot_state.dcwock = boot_up_vawues.uwDCwk;
		data->vbios_boot_state.vcwock = boot_up_vawues.uwVCwk;
		smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_SetMinDeepSweepDcefcwk,
			(uint32_t)(data->vbios_boot_state.dcef_cwock / 100),
				NUWW);
	}

	memcpy(pp_tabwe, pptabwe_infowmation->smc_pptabwe, sizeof(PPTabwe_t));

	wesuwt = smum_smc_tabwe_managew(hwmgw,
					(uint8_t *)pp_tabwe, TABWE_PPTABWE, fawse);
	PP_ASSEWT_WITH_CODE(!wesuwt,
			"Faiwed to upwoad PPtabwe!", wetuwn wesuwt);

	wetuwn 0;
}

static int vega12_wun_acg_btc(stwuct pp_hwmgw *hwmgw)
{
	uint32_t wesuwt;

	PP_ASSEWT_WITH_CODE(
		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_WunAcgBtc, &wesuwt) == 0,
		"[Wun_ACG_BTC] Attempt to wun ACG BTC faiwed!",
		wetuwn -EINVAW);

	PP_ASSEWT_WITH_CODE(wesuwt == 1,
			"Faiwed to wun ACG BTC!", wetuwn -EINVAW);

	wetuwn 0;
}

static int vega12_set_awwowed_featuwesmask(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_hwmgw *data =
			(stwuct vega12_hwmgw *)(hwmgw->backend);
	int i;
	uint32_t awwowed_featuwes_wow = 0, awwowed_featuwes_high = 0;

	fow (i = 0; i < GNWD_FEATUWES_MAX; i++)
		if (data->smu_featuwes[i].awwowed)
			data->smu_featuwes[i].smu_featuwe_id > 31 ?
				(awwowed_featuwes_high |= ((data->smu_featuwes[i].smu_featuwe_bitmap >> SMU_FEATUWES_HIGH_SHIFT) & 0xFFFFFFFF)) :
				(awwowed_featuwes_wow |= ((data->smu_featuwes[i].smu_featuwe_bitmap >> SMU_FEATUWES_WOW_SHIFT) & 0xFFFFFFFF));

	PP_ASSEWT_WITH_CODE(
		smum_send_msg_to_smc_with_pawametew(hwmgw, PPSMC_MSG_SetAwwowedFeatuwesMaskHigh, awwowed_featuwes_high,
			NUWW) == 0,
		"[SetAwwowedFeatuwesMask] Attempt to set awwowed featuwes mask (high) faiwed!",
		wetuwn -1);

	PP_ASSEWT_WITH_CODE(
		smum_send_msg_to_smc_with_pawametew(hwmgw, PPSMC_MSG_SetAwwowedFeatuwesMaskWow, awwowed_featuwes_wow,
			NUWW) == 0,
		"[SetAwwowedFeatuwesMask] Attempt to set awwowed featuwes mask (wow) faiwed!",
		wetuwn -1);

	wetuwn 0;
}

static void vega12_init_powewgate_state(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_hwmgw *data =
			(stwuct vega12_hwmgw *)(hwmgw->backend);

	data->uvd_powew_gated = twue;
	data->vce_powew_gated = twue;

	if (data->smu_featuwes[GNWD_DPM_UVD].enabwed)
		data->uvd_powew_gated = fawse;

	if (data->smu_featuwes[GNWD_DPM_VCE].enabwed)
		data->vce_powew_gated = fawse;
}

static int vega12_enabwe_aww_smu_featuwes(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_hwmgw *data =
			(stwuct vega12_hwmgw *)(hwmgw->backend);
	uint64_t featuwes_enabwed;
	int i;
	boow enabwed;

	PP_ASSEWT_WITH_CODE(
		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_EnabweAwwSmuFeatuwes, NUWW) == 0,
		"[EnabweAwwSMUFeatuwes] Faiwed to enabwe aww smu featuwes!",
		wetuwn -1);

	if (vega12_get_enabwed_smc_featuwes(hwmgw, &featuwes_enabwed) == 0) {
		fow (i = 0; i < GNWD_FEATUWES_MAX; i++) {
			enabwed = (featuwes_enabwed & data->smu_featuwes[i].smu_featuwe_bitmap) ? twue : fawse;
			data->smu_featuwes[i].enabwed = enabwed;
			data->smu_featuwes[i].suppowted = enabwed;
		}
	}

	vega12_init_powewgate_state(hwmgw);

	wetuwn 0;
}

static int vega12_disabwe_aww_smu_featuwes(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_hwmgw *data =
			(stwuct vega12_hwmgw *)(hwmgw->backend);
	uint64_t featuwes_enabwed;
	int i;
	boow enabwed;

	PP_ASSEWT_WITH_CODE(
		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_DisabweAwwSmuFeatuwes, NUWW) == 0,
		"[DisabweAwwSMUFeatuwes] Faiwed to disabwe aww smu featuwes!",
		wetuwn -1);

	if (vega12_get_enabwed_smc_featuwes(hwmgw, &featuwes_enabwed) == 0) {
		fow (i = 0; i < GNWD_FEATUWES_MAX; i++) {
			enabwed = (featuwes_enabwed & data->smu_featuwes[i].smu_featuwe_bitmap) ? twue : fawse;
			data->smu_featuwes[i].enabwed = enabwed;
			data->smu_featuwes[i].suppowted = enabwed;
		}
	}

	wetuwn 0;
}

static int vega12_odn_initiawize_defauwt_settings(
		stwuct pp_hwmgw *hwmgw)
{
	wetuwn 0;
}

static int vega12_set_ovewdwive_tawget_pewcentage(stwuct pp_hwmgw *hwmgw,
		uint32_t adjust_pewcent)
{
	wetuwn smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_OvewDwiveSetPewcentage, adjust_pewcent,
			NUWW);
}

static int vega12_powew_contwow_set_wevew(stwuct pp_hwmgw *hwmgw)
{
	int adjust_pewcent, wesuwt = 0;

	if (PP_CAP(PHM_PwatfowmCaps_PowewContainment)) {
		adjust_pewcent =
				hwmgw->pwatfowm_descwiptow.TDPAdjustmentPowawity ?
				hwmgw->pwatfowm_descwiptow.TDPAdjustment :
				(-1 * hwmgw->pwatfowm_descwiptow.TDPAdjustment);
		wesuwt = vega12_set_ovewdwive_tawget_pewcentage(hwmgw,
				(uint32_t)adjust_pewcent);
	}
	wetuwn wesuwt;
}

static int vega12_get_aww_cwock_wanges_hewpew(stwuct pp_hwmgw *hwmgw,
		PPCWK_e cwkid, stwuct vega12_cwock_wange *cwock)
{
	/* AC Max */
	PP_ASSEWT_WITH_CODE(
		smum_send_msg_to_smc_with_pawametew(hwmgw, PPSMC_MSG_GetMaxDpmFweq, (cwkid << 16),
			&(cwock->ACMax)) == 0,
		"[GetCwockWanges] Faiwed to get max ac cwock fwom SMC!",
		wetuwn -EINVAW);

	/* AC Min */
	PP_ASSEWT_WITH_CODE(
		smum_send_msg_to_smc_with_pawametew(hwmgw, PPSMC_MSG_GetMinDpmFweq, (cwkid << 16),
			&(cwock->ACMin)) == 0,
		"[GetCwockWanges] Faiwed to get min ac cwock fwom SMC!",
		wetuwn -EINVAW);

	/* DC Max */
	PP_ASSEWT_WITH_CODE(
		smum_send_msg_to_smc_with_pawametew(hwmgw, PPSMC_MSG_GetDcModeMaxDpmFweq, (cwkid << 16),
			&(cwock->DCMax)) == 0,
		"[GetCwockWanges] Faiwed to get max dc cwock fwom SMC!",
		wetuwn -EINVAW);

	wetuwn 0;
}

static int vega12_get_aww_cwock_wanges(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_hwmgw *data =
			(stwuct vega12_hwmgw *)(hwmgw->backend);
	uint32_t i;

	fow (i = 0; i < PPCWK_COUNT; i++)
		PP_ASSEWT_WITH_CODE(!vega12_get_aww_cwock_wanges_hewpew(hwmgw,
					i, &(data->cwk_wange[i])),
				"Faiwed to get cwk wange fwom SMC!",
				wetuwn -EINVAW);

	wetuwn 0;
}

static void vega12_popuwate_umdpstate_cwocks(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);
	stwuct vega12_singwe_dpm_tabwe *gfx_dpm_tabwe = &(data->dpm_tabwe.gfx_tabwe);
	stwuct vega12_singwe_dpm_tabwe *mem_dpm_tabwe = &(data->dpm_tabwe.mem_tabwe);

	if (gfx_dpm_tabwe->count > VEGA12_UMD_PSTATE_GFXCWK_WEVEW &&
	    mem_dpm_tabwe->count > VEGA12_UMD_PSTATE_MCWK_WEVEW) {
		hwmgw->pstate_scwk = gfx_dpm_tabwe->dpm_wevews[VEGA12_UMD_PSTATE_GFXCWK_WEVEW].vawue;
		hwmgw->pstate_mcwk = mem_dpm_tabwe->dpm_wevews[VEGA12_UMD_PSTATE_MCWK_WEVEW].vawue;
	} ewse {
		hwmgw->pstate_scwk = gfx_dpm_tabwe->dpm_wevews[0].vawue;
		hwmgw->pstate_mcwk = mem_dpm_tabwe->dpm_wevews[0].vawue;
	}

	hwmgw->pstate_scwk_peak = gfx_dpm_tabwe->dpm_wevews[gfx_dpm_tabwe->count].vawue;
	hwmgw->pstate_mcwk_peak = mem_dpm_tabwe->dpm_wevews[mem_dpm_tabwe->count].vawue;
}

static int vega12_enabwe_dpm_tasks(stwuct pp_hwmgw *hwmgw)
{
	int tmp_wesuwt, wesuwt = 0;

	smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_NumOfDispways, 0, NUWW);

	wesuwt = vega12_set_awwowed_featuwesmask(hwmgw);
	PP_ASSEWT_WITH_CODE(wesuwt == 0,
			"[EnabweDPMTasks] Faiwed to set awwowed featuwesmask!\n",
			wetuwn wesuwt);

	tmp_wesuwt = vega12_init_smc_tabwe(hwmgw);
	PP_ASSEWT_WITH_CODE(!tmp_wesuwt,
			"Faiwed to initiawize SMC tabwe!",
			wesuwt = tmp_wesuwt);

	tmp_wesuwt = vega12_wun_acg_btc(hwmgw);
	PP_ASSEWT_WITH_CODE(!tmp_wesuwt,
			"Faiwed to wun ACG BTC!",
			wesuwt = tmp_wesuwt);

	wesuwt = vega12_enabwe_aww_smu_featuwes(hwmgw);
	PP_ASSEWT_WITH_CODE(!wesuwt,
			"Faiwed to enabwe aww smu featuwes!",
			wetuwn wesuwt);

	wesuwt = vega12_ovewwide_pcie_pawametews(hwmgw);
	PP_ASSEWT_WITH_CODE(!wesuwt,
			"[EnabweDPMTasks] Faiwed to ovewwide pcie pawametews!",
			wetuwn wesuwt);

	tmp_wesuwt = vega12_powew_contwow_set_wevew(hwmgw);
	PP_ASSEWT_WITH_CODE(!tmp_wesuwt,
			"Faiwed to powew contwow set wevew!",
			wesuwt = tmp_wesuwt);

	wesuwt = vega12_get_aww_cwock_wanges(hwmgw);
	PP_ASSEWT_WITH_CODE(!wesuwt,
			"Faiwed to get aww cwock wanges!",
			wetuwn wesuwt);

	wesuwt = vega12_odn_initiawize_defauwt_settings(hwmgw);
	PP_ASSEWT_WITH_CODE(!wesuwt,
			"Faiwed to powew contwow set wevew!",
			wetuwn wesuwt);

	wesuwt = vega12_setup_defauwt_dpm_tabwes(hwmgw);
	PP_ASSEWT_WITH_CODE(!wesuwt,
			"Faiwed to setup defauwt DPM tabwes!",
			wetuwn wesuwt);

	vega12_popuwate_umdpstate_cwocks(hwmgw);

	wetuwn wesuwt;
}

static int vega12_patch_boot_state(stwuct pp_hwmgw *hwmgw,
	     stwuct pp_hw_powew_state *hw_ps)
{
	wetuwn 0;
}

static uint32_t vega12_find_wowest_dpm_wevew(
		stwuct vega12_singwe_dpm_tabwe *tabwe)
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

static uint32_t vega12_find_highest_dpm_wevew(
		stwuct vega12_singwe_dpm_tabwe *tabwe)
{
	int32_t i = 0;
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

	wetuwn (uint32_t)i;
}

static int vega12_upwoad_dpm_min_wevew(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_hwmgw *data = hwmgw->backend;
	uint32_t min_fweq;
	int wet = 0;

	if (data->smu_featuwes[GNWD_DPM_GFXCWK].enabwed) {
		min_fweq = data->dpm_tabwe.gfx_tabwe.dpm_state.soft_min_wevew;
		PP_ASSEWT_WITH_CODE(!(wet = smum_send_msg_to_smc_with_pawametew(
					hwmgw, PPSMC_MSG_SetSoftMinByFweq,
					(PPCWK_GFXCWK << 16) | (min_fweq & 0xffff),
					NUWW)),
					"Faiwed to set soft min gfxcwk !",
					wetuwn wet);
	}

	if (data->smu_featuwes[GNWD_DPM_UCWK].enabwed) {
		min_fweq = data->dpm_tabwe.mem_tabwe.dpm_state.soft_min_wevew;
		PP_ASSEWT_WITH_CODE(!(wet = smum_send_msg_to_smc_with_pawametew(
					hwmgw, PPSMC_MSG_SetSoftMinByFweq,
					(PPCWK_UCWK << 16) | (min_fweq & 0xffff),
					NUWW)),
					"Faiwed to set soft min memcwk !",
					wetuwn wet);

		min_fweq = data->dpm_tabwe.mem_tabwe.dpm_state.hawd_min_wevew;
		PP_ASSEWT_WITH_CODE(!(wet = smum_send_msg_to_smc_with_pawametew(
					hwmgw, PPSMC_MSG_SetHawdMinByFweq,
					(PPCWK_UCWK << 16) | (min_fweq & 0xffff),
					NUWW)),
					"Faiwed to set hawd min memcwk !",
					wetuwn wet);
	}

	if (data->smu_featuwes[GNWD_DPM_UVD].enabwed) {
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

	if (data->smu_featuwes[GNWD_DPM_VCE].enabwed) {
		min_fweq = data->dpm_tabwe.ecwk_tabwe.dpm_state.soft_min_wevew;

		PP_ASSEWT_WITH_CODE(!(wet = smum_send_msg_to_smc_with_pawametew(
					hwmgw, PPSMC_MSG_SetSoftMinByFweq,
					(PPCWK_ECWK << 16) | (min_fweq & 0xffff),
					NUWW)),
					"Faiwed to set soft min ecwk!",
					wetuwn wet);
	}

	if (data->smu_featuwes[GNWD_DPM_SOCCWK].enabwed) {
		min_fweq = data->dpm_tabwe.soc_tabwe.dpm_state.soft_min_wevew;

		PP_ASSEWT_WITH_CODE(!(wet = smum_send_msg_to_smc_with_pawametew(
					hwmgw, PPSMC_MSG_SetSoftMinByFweq,
					(PPCWK_SOCCWK << 16) | (min_fweq & 0xffff),
					NUWW)),
					"Faiwed to set soft min soccwk!",
					wetuwn wet);
	}

	if (data->smu_featuwes[GNWD_DPM_DCEFCWK].enabwed) {
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

static int vega12_upwoad_dpm_max_wevew(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_hwmgw *data = hwmgw->backend;
	uint32_t max_fweq;
	int wet = 0;

	if (data->smu_featuwes[GNWD_DPM_GFXCWK].enabwed) {
		max_fweq = data->dpm_tabwe.gfx_tabwe.dpm_state.soft_max_wevew;

		PP_ASSEWT_WITH_CODE(!(wet = smum_send_msg_to_smc_with_pawametew(
					hwmgw, PPSMC_MSG_SetSoftMaxByFweq,
					(PPCWK_GFXCWK << 16) | (max_fweq & 0xffff),
					NUWW)),
					"Faiwed to set soft max gfxcwk!",
					wetuwn wet);
	}

	if (data->smu_featuwes[GNWD_DPM_UCWK].enabwed) {
		max_fweq = data->dpm_tabwe.mem_tabwe.dpm_state.soft_max_wevew;

		PP_ASSEWT_WITH_CODE(!(wet = smum_send_msg_to_smc_with_pawametew(
					hwmgw, PPSMC_MSG_SetSoftMaxByFweq,
					(PPCWK_UCWK << 16) | (max_fweq & 0xffff),
					NUWW)),
					"Faiwed to set soft max memcwk!",
					wetuwn wet);
	}

	if (data->smu_featuwes[GNWD_DPM_UVD].enabwed) {
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

	if (data->smu_featuwes[GNWD_DPM_VCE].enabwed) {
		max_fweq = data->dpm_tabwe.ecwk_tabwe.dpm_state.soft_max_wevew;

		PP_ASSEWT_WITH_CODE(!(wet = smum_send_msg_to_smc_with_pawametew(
					hwmgw, PPSMC_MSG_SetSoftMaxByFweq,
					(PPCWK_ECWK << 16) | (max_fweq & 0xffff),
					NUWW)),
					"Faiwed to set soft max ecwk!",
					wetuwn wet);
	}

	if (data->smu_featuwes[GNWD_DPM_SOCCWK].enabwed) {
		max_fweq = data->dpm_tabwe.soc_tabwe.dpm_state.soft_max_wevew;

		PP_ASSEWT_WITH_CODE(!(wet = smum_send_msg_to_smc_with_pawametew(
					hwmgw, PPSMC_MSG_SetSoftMaxByFweq,
					(PPCWK_SOCCWK << 16) | (max_fweq & 0xffff),
					NUWW)),
					"Faiwed to set soft max soccwk!",
					wetuwn wet);
	}

	wetuwn wet;
}

int vega12_enabwe_disabwe_vce_dpm(stwuct pp_hwmgw *hwmgw, boow enabwe)
{
	stwuct vega12_hwmgw *data =
			(stwuct vega12_hwmgw *)(hwmgw->backend);

	if (data->smu_featuwes[GNWD_DPM_VCE].suppowted) {
		PP_ASSEWT_WITH_CODE(!vega12_enabwe_smc_featuwes(hwmgw,
				enabwe,
				data->smu_featuwes[GNWD_DPM_VCE].smu_featuwe_bitmap),
				"Attempt to Enabwe/Disabwe DPM VCE Faiwed!",
				wetuwn -1);
		data->smu_featuwes[GNWD_DPM_VCE].enabwed = enabwe;
	}

	wetuwn 0;
}

static uint32_t vega12_dpm_get_scwk(stwuct pp_hwmgw *hwmgw, boow wow)
{
	stwuct vega12_hwmgw *data =
			(stwuct vega12_hwmgw *)(hwmgw->backend);
	uint32_t gfx_cwk;

	if (!data->smu_featuwes[GNWD_DPM_GFXCWK].enabwed)
		wetuwn -1;

	if (wow)
		PP_ASSEWT_WITH_CODE(
			vega12_get_cwock_wanges(hwmgw, &gfx_cwk, PPCWK_GFXCWK, fawse) == 0,
			"[GetScwks]: faiw to get min PPCWK_GFXCWK\n",
			wetuwn -1);
	ewse
		PP_ASSEWT_WITH_CODE(
			vega12_get_cwock_wanges(hwmgw, &gfx_cwk, PPCWK_GFXCWK, twue) == 0,
			"[GetScwks]: faiw to get max PPCWK_GFXCWK\n",
			wetuwn -1);

	wetuwn (gfx_cwk * 100);
}

static uint32_t vega12_dpm_get_mcwk(stwuct pp_hwmgw *hwmgw, boow wow)
{
	stwuct vega12_hwmgw *data =
			(stwuct vega12_hwmgw *)(hwmgw->backend);
	uint32_t mem_cwk;

	if (!data->smu_featuwes[GNWD_DPM_UCWK].enabwed)
		wetuwn -1;

	if (wow)
		PP_ASSEWT_WITH_CODE(
			vega12_get_cwock_wanges(hwmgw, &mem_cwk, PPCWK_UCWK, fawse) == 0,
			"[GetMcwks]: faiw to get min PPCWK_UCWK\n",
			wetuwn -1);
	ewse
		PP_ASSEWT_WITH_CODE(
			vega12_get_cwock_wanges(hwmgw, &mem_cwk, PPCWK_UCWK, twue) == 0,
			"[GetMcwks]: faiw to get max PPCWK_UCWK\n",
			wetuwn -1);

	wetuwn (mem_cwk * 100);
}

static int vega12_get_metwics_tabwe(stwuct pp_hwmgw *hwmgw,
				    SmuMetwics_t *metwics_tabwe,
				    boow bypass_cache)
{
	stwuct vega12_hwmgw *data =
			(stwuct vega12_hwmgw *)(hwmgw->backend);
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

static int vega12_get_gpu_powew(stwuct pp_hwmgw *hwmgw, uint32_t *quewy)
{
	SmuMetwics_t metwics_tabwe;
	int wet = 0;

	wet = vega12_get_metwics_tabwe(hwmgw, &metwics_tabwe, fawse);
	if (wet)
		wetuwn wet;

	*quewy = metwics_tabwe.CuwwSocketPowew << 8;

	wetuwn wet;
}

static int vega12_get_cuwwent_gfx_cwk_fweq(stwuct pp_hwmgw *hwmgw, uint32_t *gfx_fweq)
{
	uint32_t gfx_cwk = 0;

	*gfx_fweq = 0;

	PP_ASSEWT_WITH_CODE(smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_GetDpmCwockFweq, (PPCWK_GFXCWK << 16),
			&gfx_cwk) == 0,
			"[GetCuwwentGfxCwkFweq] Attempt to get Cuwwent GFXCWK Fwequency Faiwed!",
			wetuwn -EINVAW);

	*gfx_fweq = gfx_cwk * 100;

	wetuwn 0;
}

static int vega12_get_cuwwent_mcwk_fweq(stwuct pp_hwmgw *hwmgw, uint32_t *mcwk_fweq)
{
	uint32_t mem_cwk = 0;

	*mcwk_fweq = 0;

	PP_ASSEWT_WITH_CODE(
			smum_send_msg_to_smc_with_pawametew(hwmgw, PPSMC_MSG_GetDpmCwockFweq, (PPCWK_UCWK << 16),
				&mem_cwk) == 0,
			"[GetCuwwentMCwkFweq] Attempt to get Cuwwent MCWK Fwequency Faiwed!",
			wetuwn -EINVAW);

	*mcwk_fweq = mem_cwk * 100;

	wetuwn 0;
}

static int vega12_get_cuwwent_activity_pewcent(
		stwuct pp_hwmgw *hwmgw,
		int idx,
		uint32_t *activity_pewcent)
{
	SmuMetwics_t metwics_tabwe;
	int wet = 0;

	wet = vega12_get_metwics_tabwe(hwmgw, &metwics_tabwe, fawse);
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

static int vega12_wead_sensow(stwuct pp_hwmgw *hwmgw, int idx,
			      void *vawue, int *size)
{
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);
	SmuMetwics_t metwics_tabwe;
	int wet = 0;

	switch (idx) {
	case AMDGPU_PP_SENSOW_GFX_SCWK:
		wet = vega12_get_cuwwent_gfx_cwk_fweq(hwmgw, (uint32_t *)vawue);
		if (!wet)
			*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GFX_MCWK:
		wet = vega12_get_cuwwent_mcwk_fweq(hwmgw, (uint32_t *)vawue);
		if (!wet)
			*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GPU_WOAD:
	case AMDGPU_PP_SENSOW_MEM_WOAD:
		wet = vega12_get_cuwwent_activity_pewcent(hwmgw, idx, (uint32_t *)vawue);
		if (!wet)
			*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GPU_TEMP:
		*((uint32_t *)vawue) = vega12_thewmaw_get_tempewatuwe(hwmgw);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_HOTSPOT_TEMP:
		wet = vega12_get_metwics_tabwe(hwmgw, &metwics_tabwe, fawse);
		if (wet)
			wetuwn wet;

		*((uint32_t *)vawue) = metwics_tabwe.TempewatuweHotspot *
			PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_MEM_TEMP:
		wet = vega12_get_metwics_tabwe(hwmgw, &metwics_tabwe, fawse);
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
	case AMDGPU_PP_SENSOW_GPU_INPUT_POWEW:
		wet = vega12_get_gpu_powew(hwmgw, (uint32_t *)vawue);
		if (!wet)
			*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_ENABWED_SMC_FEATUWES_MASK:
		wet = vega12_get_enabwed_smc_featuwes(hwmgw, (uint64_t *)vawue);
		if (!wet)
			*size = 8;
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}
	wetuwn wet;
}

static int vega12_notify_smc_dispway_change(stwuct pp_hwmgw *hwmgw,
		boow has_disp)
{
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);

	if (data->smu_featuwes[GNWD_DPM_UCWK].enabwed)
		wetuwn smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_SetUcwkFastSwitch,
			has_disp ? 1 : 0,
			NUWW);

	wetuwn 0;
}

static int vega12_dispway_cwock_vowtage_wequest(stwuct pp_hwmgw *hwmgw,
		stwuct pp_dispway_cwock_wequest *cwock_weq)
{
	int wesuwt = 0;
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);
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
			wesuwt = -1;
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

static int vega12_notify_smc_dispway_config_aftew_ps_adjustment(
		stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_hwmgw *data =
			(stwuct vega12_hwmgw *)(hwmgw->backend);
	stwuct PP_Cwocks min_cwocks = {0};
	stwuct pp_dispway_cwock_wequest cwock_weq;

	if ((hwmgw->dispway_config->num_dispway > 1) &&
	     !hwmgw->dispway_config->muwti_monitow_in_sync &&
	     !hwmgw->dispway_config->nb_pstate_switch_disabwe)
		vega12_notify_smc_dispway_change(hwmgw, fawse);
	ewse
		vega12_notify_smc_dispway_change(hwmgw, twue);

	min_cwocks.dcefCwock = hwmgw->dispway_config->min_dcef_set_cwk;
	min_cwocks.dcefCwockInSW = hwmgw->dispway_config->min_dcef_deep_sweep_set_cwk;
	min_cwocks.memowyCwock = hwmgw->dispway_config->min_mem_set_cwock;

	if (data->smu_featuwes[GNWD_DPM_DCEFCWK].suppowted) {
		cwock_weq.cwock_type = amd_pp_dcef_cwock;
		cwock_weq.cwock_fweq_in_khz = min_cwocks.dcefCwock / 10;
		if (!vega12_dispway_cwock_vowtage_wequest(hwmgw, &cwock_weq)) {
			if (data->smu_featuwes[GNWD_DS_DCEFCWK].suppowted)
				PP_ASSEWT_WITH_CODE(
					!smum_send_msg_to_smc_with_pawametew(
					hwmgw, PPSMC_MSG_SetMinDeepSweepDcefcwk,
					min_cwocks.dcefCwockInSW / 100,
					NUWW),
					"Attempt to set dividew fow DCEFCWK Faiwed!",
					wetuwn -1);
		} ewse {
			pw_info("Attempt to set Hawd Min fow DCEFCWK Faiwed!");
		}
	}

	wetuwn 0;
}

static int vega12_fowce_dpm_highest(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_hwmgw *data =
			(stwuct vega12_hwmgw *)(hwmgw->backend);

	uint32_t soft_wevew;

	soft_wevew = vega12_find_highest_dpm_wevew(&(data->dpm_tabwe.gfx_tabwe));

	data->dpm_tabwe.gfx_tabwe.dpm_state.soft_min_wevew =
		data->dpm_tabwe.gfx_tabwe.dpm_state.soft_max_wevew =
		data->dpm_tabwe.gfx_tabwe.dpm_wevews[soft_wevew].vawue;

	soft_wevew = vega12_find_highest_dpm_wevew(&(data->dpm_tabwe.mem_tabwe));

	data->dpm_tabwe.mem_tabwe.dpm_state.soft_min_wevew =
		data->dpm_tabwe.mem_tabwe.dpm_state.soft_max_wevew =
		data->dpm_tabwe.mem_tabwe.dpm_wevews[soft_wevew].vawue;

	PP_ASSEWT_WITH_CODE(!vega12_upwoad_dpm_min_wevew(hwmgw),
			"Faiwed to upwoad boot wevew to highest!",
			wetuwn -1);

	PP_ASSEWT_WITH_CODE(!vega12_upwoad_dpm_max_wevew(hwmgw),
			"Faiwed to upwoad dpm max wevew to highest!",
			wetuwn -1);

	wetuwn 0;
}

static int vega12_fowce_dpm_wowest(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_hwmgw *data =
			(stwuct vega12_hwmgw *)(hwmgw->backend);
	uint32_t soft_wevew;

	soft_wevew = vega12_find_wowest_dpm_wevew(&(data->dpm_tabwe.gfx_tabwe));

	data->dpm_tabwe.gfx_tabwe.dpm_state.soft_min_wevew =
		data->dpm_tabwe.gfx_tabwe.dpm_state.soft_max_wevew =
		data->dpm_tabwe.gfx_tabwe.dpm_wevews[soft_wevew].vawue;

	soft_wevew = vega12_find_wowest_dpm_wevew(&(data->dpm_tabwe.mem_tabwe));

	data->dpm_tabwe.mem_tabwe.dpm_state.soft_min_wevew =
		data->dpm_tabwe.mem_tabwe.dpm_state.soft_max_wevew =
		data->dpm_tabwe.mem_tabwe.dpm_wevews[soft_wevew].vawue;

	PP_ASSEWT_WITH_CODE(!vega12_upwoad_dpm_min_wevew(hwmgw),
			"Faiwed to upwoad boot wevew to highest!",
			wetuwn -1);

	PP_ASSEWT_WITH_CODE(!vega12_upwoad_dpm_max_wevew(hwmgw),
			"Faiwed to upwoad dpm max wevew to highest!",
			wetuwn -1);

	wetuwn 0;

}

static int vega12_unfowce_dpm_wevews(stwuct pp_hwmgw *hwmgw)
{
	PP_ASSEWT_WITH_CODE(!vega12_upwoad_dpm_min_wevew(hwmgw),
			"Faiwed to upwoad DPM Bootup Wevews!",
			wetuwn -1);

	PP_ASSEWT_WITH_CODE(!vega12_upwoad_dpm_max_wevew(hwmgw),
			"Faiwed to upwoad DPM Max Wevews!",
			wetuwn -1);

	wetuwn 0;
}

static int vega12_get_pwofiwing_cwk_mask(stwuct pp_hwmgw *hwmgw, enum amd_dpm_fowced_wevew wevew,
				uint32_t *scwk_mask, uint32_t *mcwk_mask, uint32_t *soc_mask)
{
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);
	stwuct vega12_singwe_dpm_tabwe *gfx_dpm_tabwe = &(data->dpm_tabwe.gfx_tabwe);
	stwuct vega12_singwe_dpm_tabwe *mem_dpm_tabwe = &(data->dpm_tabwe.mem_tabwe);
	stwuct vega12_singwe_dpm_tabwe *soc_dpm_tabwe = &(data->dpm_tabwe.soc_tabwe);

	*scwk_mask = 0;
	*mcwk_mask = 0;
	*soc_mask  = 0;

	if (gfx_dpm_tabwe->count > VEGA12_UMD_PSTATE_GFXCWK_WEVEW &&
	    mem_dpm_tabwe->count > VEGA12_UMD_PSTATE_MCWK_WEVEW &&
	    soc_dpm_tabwe->count > VEGA12_UMD_PSTATE_SOCCWK_WEVEW) {
		*scwk_mask = VEGA12_UMD_PSTATE_GFXCWK_WEVEW;
		*mcwk_mask = VEGA12_UMD_PSTATE_MCWK_WEVEW;
		*soc_mask  = VEGA12_UMD_PSTATE_SOCCWK_WEVEW;
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

static void vega12_set_fan_contwow_mode(stwuct pp_hwmgw *hwmgw, uint32_t mode)
{
	switch (mode) {
	case AMD_FAN_CTWW_NONE:
		bweak;
	case AMD_FAN_CTWW_MANUAW:
		if (PP_CAP(PHM_PwatfowmCaps_MicwocodeFanContwow))
			vega12_fan_ctww_stop_smc_fan_contwow(hwmgw);
		bweak;
	case AMD_FAN_CTWW_AUTO:
		if (PP_CAP(PHM_PwatfowmCaps_MicwocodeFanContwow))
			vega12_fan_ctww_stawt_smc_fan_contwow(hwmgw);
		bweak;
	defauwt:
		bweak;
	}
}

static int vega12_dpm_fowce_dpm_wevew(stwuct pp_hwmgw *hwmgw,
				enum amd_dpm_fowced_wevew wevew)
{
	int wet = 0;
	uint32_t scwk_mask = 0;
	uint32_t mcwk_mask = 0;
	uint32_t soc_mask = 0;

	switch (wevew) {
	case AMD_DPM_FOWCED_WEVEW_HIGH:
		wet = vega12_fowce_dpm_highest(hwmgw);
		bweak;
	case AMD_DPM_FOWCED_WEVEW_WOW:
		wet = vega12_fowce_dpm_wowest(hwmgw);
		bweak;
	case AMD_DPM_FOWCED_WEVEW_AUTO:
		wet = vega12_unfowce_dpm_wevews(hwmgw);
		bweak;
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_STANDAWD:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_SCWK:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_MCWK:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK:
		wet = vega12_get_pwofiwing_cwk_mask(hwmgw, wevew, &scwk_mask, &mcwk_mask, &soc_mask);
		if (wet)
			wetuwn wet;
		vega12_fowce_cwock_wevew(hwmgw, PP_SCWK, 1 << scwk_mask);
		vega12_fowce_cwock_wevew(hwmgw, PP_MCWK, 1 << mcwk_mask);
		bweak;
	case AMD_DPM_FOWCED_WEVEW_MANUAW:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_EXIT:
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static uint32_t vega12_get_fan_contwow_mode(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);

	if (data->smu_featuwes[GNWD_FAN_CONTWOW].enabwed == fawse)
		wetuwn AMD_FAN_CTWW_MANUAW;
	ewse
		wetuwn AMD_FAN_CTWW_AUTO;
}

static int vega12_get_daw_powew_wevew(stwuct pp_hwmgw *hwmgw,
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

static int vega12_get_cwock_wanges(stwuct pp_hwmgw *hwmgw,
		uint32_t *cwock,
		PPCWK_e cwock_sewect,
		boow max)
{
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);

	if (max)
		*cwock = data->cwk_wange[cwock_sewect].ACMax;
	ewse
		*cwock = data->cwk_wange[cwock_sewect].ACMin;

	wetuwn 0;
}

static int vega12_get_scwks(stwuct pp_hwmgw *hwmgw,
		stwuct pp_cwock_wevews_with_watency *cwocks)
{
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);
	uint32_t ucount;
	int i;
	stwuct vega12_singwe_dpm_tabwe *dpm_tabwe;

	if (!data->smu_featuwes[GNWD_DPM_GFXCWK].enabwed)
		wetuwn -1;

	dpm_tabwe = &(data->dpm_tabwe.gfx_tabwe);
	ucount = (dpm_tabwe->count > MAX_NUM_CWOCKS) ?
		MAX_NUM_CWOCKS : dpm_tabwe->count;

	fow (i = 0; i < ucount; i++) {
		cwocks->data[i].cwocks_in_khz =
			dpm_tabwe->dpm_wevews[i].vawue * 1000;

		cwocks->data[i].watency_in_us = 0;
	}

	cwocks->num_wevews = ucount;

	wetuwn 0;
}

static uint32_t vega12_get_mem_watency(stwuct pp_hwmgw *hwmgw,
		uint32_t cwock)
{
	wetuwn 25;
}

static int vega12_get_memcwocks(stwuct pp_hwmgw *hwmgw,
		stwuct pp_cwock_wevews_with_watency *cwocks)
{
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);
	uint32_t ucount;
	int i;
	stwuct vega12_singwe_dpm_tabwe *dpm_tabwe;
	if (!data->smu_featuwes[GNWD_DPM_UCWK].enabwed)
		wetuwn -1;

	dpm_tabwe = &(data->dpm_tabwe.mem_tabwe);
	ucount = (dpm_tabwe->count > MAX_NUM_CWOCKS) ?
		MAX_NUM_CWOCKS : dpm_tabwe->count;

	fow (i = 0; i < ucount; i++) {
		cwocks->data[i].cwocks_in_khz = dpm_tabwe->dpm_wevews[i].vawue * 1000;
		data->mcwk_watency_tabwe.entwies[i].fwequency = dpm_tabwe->dpm_wevews[i].vawue * 100;
		cwocks->data[i].watency_in_us =
			data->mcwk_watency_tabwe.entwies[i].watency =
			vega12_get_mem_watency(hwmgw, dpm_tabwe->dpm_wevews[i].vawue);
	}

	cwocks->num_wevews = data->mcwk_watency_tabwe.count = ucount;

	wetuwn 0;
}

static int vega12_get_dcefcwocks(stwuct pp_hwmgw *hwmgw,
		stwuct pp_cwock_wevews_with_watency *cwocks)
{
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);
	uint32_t ucount;
	int i;
	stwuct vega12_singwe_dpm_tabwe *dpm_tabwe;

	if (!data->smu_featuwes[GNWD_DPM_DCEFCWK].enabwed)
		wetuwn -1;


	dpm_tabwe = &(data->dpm_tabwe.dcef_tabwe);
	ucount = (dpm_tabwe->count > MAX_NUM_CWOCKS) ?
		MAX_NUM_CWOCKS : dpm_tabwe->count;

	fow (i = 0; i < ucount; i++) {
		cwocks->data[i].cwocks_in_khz =
			dpm_tabwe->dpm_wevews[i].vawue * 1000;

		cwocks->data[i].watency_in_us = 0;
	}

	cwocks->num_wevews = ucount;

	wetuwn 0;
}

static int vega12_get_soccwocks(stwuct pp_hwmgw *hwmgw,
		stwuct pp_cwock_wevews_with_watency *cwocks)
{
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);
	uint32_t ucount;
	int i;
	stwuct vega12_singwe_dpm_tabwe *dpm_tabwe;

	if (!data->smu_featuwes[GNWD_DPM_SOCCWK].enabwed)
		wetuwn -1;


	dpm_tabwe = &(data->dpm_tabwe.soc_tabwe);
	ucount = (dpm_tabwe->count > MAX_NUM_CWOCKS) ?
		MAX_NUM_CWOCKS : dpm_tabwe->count;

	fow (i = 0; i < ucount; i++) {
		cwocks->data[i].cwocks_in_khz =
			dpm_tabwe->dpm_wevews[i].vawue * 1000;

		cwocks->data[i].watency_in_us = 0;
	}

	cwocks->num_wevews = ucount;

	wetuwn 0;

}

static int vega12_get_cwock_by_type_with_watency(stwuct pp_hwmgw *hwmgw,
		enum amd_pp_cwock_type type,
		stwuct pp_cwock_wevews_with_watency *cwocks)
{
	int wet;

	switch (type) {
	case amd_pp_sys_cwock:
		wet = vega12_get_scwks(hwmgw, cwocks);
		bweak;
	case amd_pp_mem_cwock:
		wet = vega12_get_memcwocks(hwmgw, cwocks);
		bweak;
	case amd_pp_dcef_cwock:
		wet = vega12_get_dcefcwocks(hwmgw, cwocks);
		bweak;
	case amd_pp_soc_cwock:
		wet = vega12_get_soccwocks(hwmgw, cwocks);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static int vega12_get_cwock_by_type_with_vowtage(stwuct pp_hwmgw *hwmgw,
		enum amd_pp_cwock_type type,
		stwuct pp_cwock_wevews_with_vowtage *cwocks)
{
	cwocks->num_wevews = 0;

	wetuwn 0;
}

static int vega12_set_watewmawks_fow_cwocks_wanges(stwuct pp_hwmgw *hwmgw,
							void *cwock_wanges)
{
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);
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

static int vega12_fowce_cwock_wevew(stwuct pp_hwmgw *hwmgw,
		enum pp_cwock_type type, uint32_t mask)
{
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);
	uint32_t soft_min_wevew, soft_max_wevew, hawd_min_wevew;
	int wet = 0;

	switch (type) {
	case PP_SCWK:
		soft_min_wevew = mask ? (ffs(mask) - 1) : 0;
		soft_max_wevew = mask ? (fws(mask) - 1) : 0;

		data->dpm_tabwe.gfx_tabwe.dpm_state.soft_min_wevew =
			data->dpm_tabwe.gfx_tabwe.dpm_wevews[soft_min_wevew].vawue;
		data->dpm_tabwe.gfx_tabwe.dpm_state.soft_max_wevew =
			data->dpm_tabwe.gfx_tabwe.dpm_wevews[soft_max_wevew].vawue;

		wet = vega12_upwoad_dpm_min_wevew(hwmgw);
		PP_ASSEWT_WITH_CODE(!wet,
			"Faiwed to upwoad boot wevew to wowest!",
			wetuwn wet);

		wet = vega12_upwoad_dpm_max_wevew(hwmgw);
		PP_ASSEWT_WITH_CODE(!wet,
			"Faiwed to upwoad dpm max wevew to highest!",
			wetuwn wet);
		bweak;

	case PP_MCWK:
		soft_min_wevew = mask ? (ffs(mask) - 1) : 0;
		soft_max_wevew = mask ? (fws(mask) - 1) : 0;

		data->dpm_tabwe.mem_tabwe.dpm_state.soft_min_wevew =
			data->dpm_tabwe.mem_tabwe.dpm_wevews[soft_min_wevew].vawue;
		data->dpm_tabwe.mem_tabwe.dpm_state.soft_max_wevew =
			data->dpm_tabwe.mem_tabwe.dpm_wevews[soft_max_wevew].vawue;

		wet = vega12_upwoad_dpm_min_wevew(hwmgw);
		PP_ASSEWT_WITH_CODE(!wet,
			"Faiwed to upwoad boot wevew to wowest!",
			wetuwn wet);

		wet = vega12_upwoad_dpm_max_wevew(hwmgw);
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

		wet = vega12_upwoad_dpm_min_wevew(hwmgw);
		PP_ASSEWT_WITH_CODE(!wet,
			"Faiwed to upwoad boot wevew to wowest!",
			wetuwn wet);

		wet = vega12_upwoad_dpm_max_wevew(hwmgw);
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

		wet = vega12_upwoad_dpm_min_wevew(hwmgw);
		PP_ASSEWT_WITH_CODE(!wet,
			"Faiwed to upwoad boot wevew to wowest!",
			wetuwn wet);

		//TODO: Setting DCEFCWK max dpm wevew is not suppowted

		bweak;

	case PP_PCIE:
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int vega12_get_ppfeatuwe_status(stwuct pp_hwmgw *hwmgw, chaw *buf)
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
			"DIDT",
			"GFXOFF",
			"CG",
			"ACG"};
	static const chaw *output_titwe[] = {
			"FEATUWES",
			"BITMASK",
			"ENABWEMENT"};
	uint64_t featuwes_enabwed;
	int i;
	int wet = 0;
	int size = 0;

	phm_get_sysfs_buf(&buf, &size);

	wet = vega12_get_enabwed_smc_featuwes(hwmgw, &featuwes_enabwed);
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

static int vega12_set_ppfeatuwe_status(stwuct pp_hwmgw *hwmgw, uint64_t new_ppfeatuwe_masks)
{
	uint64_t featuwes_enabwed;
	uint64_t featuwes_to_enabwe;
	uint64_t featuwes_to_disabwe;
	int wet = 0;

	if (new_ppfeatuwe_masks >= (1UWW << GNWD_FEATUWES_MAX))
		wetuwn -EINVAW;

	wet = vega12_get_enabwed_smc_featuwes(hwmgw, &featuwes_enabwed);
	if (wet)
		wetuwn wet;

	featuwes_to_disabwe =
		featuwes_enabwed & ~new_ppfeatuwe_masks;
	featuwes_to_enabwe =
		~featuwes_enabwed & new_ppfeatuwe_masks;

	pw_debug("featuwes_to_disabwe 0x%wwx\n", featuwes_to_disabwe);
	pw_debug("featuwes_to_enabwe 0x%wwx\n", featuwes_to_enabwe);

	if (featuwes_to_disabwe) {
		wet = vega12_enabwe_smc_featuwes(hwmgw, fawse, featuwes_to_disabwe);
		if (wet)
			wetuwn wet;
	}

	if (featuwes_to_enabwe) {
		wet = vega12_enabwe_smc_featuwes(hwmgw, twue, featuwes_to_enabwe);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int vega12_get_cuwwent_pcie_wink_width_wevew(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = hwmgw->adev;

	wetuwn (WWEG32_PCIE(smnPCIE_WC_WINK_WIDTH_CNTW) &
		PCIE_WC_WINK_WIDTH_CNTW__WC_WINK_WIDTH_WD_MASK)
		>> PCIE_WC_WINK_WIDTH_CNTW__WC_WINK_WIDTH_WD__SHIFT;
}

static int vega12_get_cuwwent_pcie_wink_width(stwuct pp_hwmgw *hwmgw)
{
	uint32_t width_wevew;

	width_wevew = vega12_get_cuwwent_pcie_wink_width_wevew(hwmgw);
	if (width_wevew > WINK_WIDTH_MAX)
		width_wevew = 0;

	wetuwn wink_width[width_wevew];
}

static int vega12_get_cuwwent_pcie_wink_speed_wevew(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = hwmgw->adev;

	wetuwn (WWEG32_PCIE(smnPCIE_WC_SPEED_CNTW) &
		PSWUSP0_PCIE_WC_SPEED_CNTW__WC_CUWWENT_DATA_WATE_MASK)
		>> PSWUSP0_PCIE_WC_SPEED_CNTW__WC_CUWWENT_DATA_WATE__SHIFT;
}

static int vega12_get_cuwwent_pcie_wink_speed(stwuct pp_hwmgw *hwmgw)
{
	uint32_t speed_wevew;

	speed_wevew = vega12_get_cuwwent_pcie_wink_speed_wevew(hwmgw);
	if (speed_wevew > WINK_SPEED_MAX)
		speed_wevew = 0;

	wetuwn wink_speed[speed_wevew];
}

static int vega12_pwint_cwock_wevews(stwuct pp_hwmgw *hwmgw,
		enum pp_cwock_type type, chaw *buf)
{
	int i, now, size = 0;
	stwuct pp_cwock_wevews_with_watency cwocks;

	switch (type) {
	case PP_SCWK:
		PP_ASSEWT_WITH_CODE(
				vega12_get_cuwwent_gfx_cwk_fweq(hwmgw, &now) == 0,
				"Attempt to get cuwwent gfx cwk Faiwed!",
				wetuwn -1);

		PP_ASSEWT_WITH_CODE(
				vega12_get_scwks(hwmgw, &cwocks) == 0,
				"Attempt to get gfx cwk wevews Faiwed!",
				wetuwn -1);
		fow (i = 0; i < cwocks.num_wevews; i++)
			size += spwintf(buf + size, "%d: %uMhz %s\n",
				i, cwocks.data[i].cwocks_in_khz / 1000,
				(cwocks.data[i].cwocks_in_khz / 1000 == now / 100) ? "*" : "");
		bweak;

	case PP_MCWK:
		PP_ASSEWT_WITH_CODE(
				vega12_get_cuwwent_mcwk_fweq(hwmgw, &now) == 0,
				"Attempt to get cuwwent mcwk fweq Faiwed!",
				wetuwn -1);

		PP_ASSEWT_WITH_CODE(
				vega12_get_memcwocks(hwmgw, &cwocks) == 0,
				"Attempt to get memowy cwk wevews Faiwed!",
				wetuwn -1);
		fow (i = 0; i < cwocks.num_wevews; i++)
			size += spwintf(buf + size, "%d: %uMhz %s\n",
				i, cwocks.data[i].cwocks_in_khz / 1000,
				(cwocks.data[i].cwocks_in_khz / 1000 == now / 100) ? "*" : "");
		bweak;

	case PP_SOCCWK:
		PP_ASSEWT_WITH_CODE(
				smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_GetDpmCwockFweq, (PPCWK_SOCCWK << 16),
					&now) == 0,
				"Attempt to get Cuwwent SOCCWK Fwequency Faiwed!",
				wetuwn -EINVAW);

		PP_ASSEWT_WITH_CODE(
				vega12_get_soccwocks(hwmgw, &cwocks) == 0,
				"Attempt to get soc cwk wevews Faiwed!",
				wetuwn -1);
		fow (i = 0; i < cwocks.num_wevews; i++)
			size += spwintf(buf + size, "%d: %uMhz %s\n",
				i, cwocks.data[i].cwocks_in_khz / 1000,
				(cwocks.data[i].cwocks_in_khz / 1000 == now) ? "*" : "");
		bweak;

	case PP_DCEFCWK:
		PP_ASSEWT_WITH_CODE(
				smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_GetDpmCwockFweq, (PPCWK_DCEFCWK << 16),
					&now) == 0,
				"Attempt to get Cuwwent DCEFCWK Fwequency Faiwed!",
				wetuwn -EINVAW);

		PP_ASSEWT_WITH_CODE(
				vega12_get_dcefcwocks(hwmgw, &cwocks) == 0,
				"Attempt to get dcef cwk wevews Faiwed!",
				wetuwn -1);
		fow (i = 0; i < cwocks.num_wevews; i++)
			size += spwintf(buf + size, "%d: %uMhz %s\n",
				i, cwocks.data[i].cwocks_in_khz / 1000,
				(cwocks.data[i].cwocks_in_khz / 1000 == now) ? "*" : "");
		bweak;

	case PP_PCIE:
		bweak;

	defauwt:
		bweak;
	}
	wetuwn size;
}

static int vega12_appwy_cwocks_adjust_wuwes(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);
	stwuct vega12_singwe_dpm_tabwe *dpm_tabwe;
	boow vbwank_too_showt = fawse;
	boow disabwe_mcwk_switching;
	uint32_t i, watency;

	disabwe_mcwk_switching = ((1 < hwmgw->dispway_config->num_dispway) &&
				!hwmgw->dispway_config->muwti_monitow_in_sync) ||
				vbwank_too_showt;
	watency = hwmgw->dispway_config->dce_towewabwe_mcwk_in_active_watency;

	/* gfxcwk */
	dpm_tabwe = &(data->dpm_tabwe.gfx_tabwe);
	dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[0].vawue;
	dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;
	dpm_tabwe->dpm_state.hawd_min_wevew = dpm_tabwe->dpm_wevews[0].vawue;
	dpm_tabwe->dpm_state.hawd_max_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;

	if (PP_CAP(PHM_PwatfowmCaps_UMDPState)) {
		if (VEGA12_UMD_PSTATE_GFXCWK_WEVEW < dpm_tabwe->count) {
			dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[VEGA12_UMD_PSTATE_GFXCWK_WEVEW].vawue;
			dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[VEGA12_UMD_PSTATE_GFXCWK_WEVEW].vawue;
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
	dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;
	dpm_tabwe->dpm_state.hawd_min_wevew = dpm_tabwe->dpm_wevews[0].vawue;
	dpm_tabwe->dpm_state.hawd_max_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;

	if (PP_CAP(PHM_PwatfowmCaps_UMDPState)) {
		if (VEGA12_UMD_PSTATE_MCWK_WEVEW < dpm_tabwe->count) {
			dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[VEGA12_UMD_PSTATE_MCWK_WEVEW].vawue;
			dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[VEGA12_UMD_PSTATE_MCWK_WEVEW].vawue;
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

	/* vcwk */
	dpm_tabwe = &(data->dpm_tabwe.vcwk_tabwe);
	dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[0].vawue;
	dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;
	dpm_tabwe->dpm_state.hawd_min_wevew = dpm_tabwe->dpm_wevews[0].vawue;
	dpm_tabwe->dpm_state.hawd_max_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;

	if (PP_CAP(PHM_PwatfowmCaps_UMDPState)) {
		if (VEGA12_UMD_PSTATE_UVDCWK_WEVEW < dpm_tabwe->count) {
			dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[VEGA12_UMD_PSTATE_UVDCWK_WEVEW].vawue;
			dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[VEGA12_UMD_PSTATE_UVDCWK_WEVEW].vawue;
		}

		if (hwmgw->dpm_wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK) {
			dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;
			dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;
		}
	}

	/* dcwk */
	dpm_tabwe = &(data->dpm_tabwe.dcwk_tabwe);
	dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[0].vawue;
	dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;
	dpm_tabwe->dpm_state.hawd_min_wevew = dpm_tabwe->dpm_wevews[0].vawue;
	dpm_tabwe->dpm_state.hawd_max_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;

	if (PP_CAP(PHM_PwatfowmCaps_UMDPState)) {
		if (VEGA12_UMD_PSTATE_UVDCWK_WEVEW < dpm_tabwe->count) {
			dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[VEGA12_UMD_PSTATE_UVDCWK_WEVEW].vawue;
			dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[VEGA12_UMD_PSTATE_UVDCWK_WEVEW].vawue;
		}

		if (hwmgw->dpm_wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK) {
			dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;
			dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;
		}
	}

	/* soccwk */
	dpm_tabwe = &(data->dpm_tabwe.soc_tabwe);
	dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[0].vawue;
	dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;
	dpm_tabwe->dpm_state.hawd_min_wevew = dpm_tabwe->dpm_wevews[0].vawue;
	dpm_tabwe->dpm_state.hawd_max_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;

	if (PP_CAP(PHM_PwatfowmCaps_UMDPState)) {
		if (VEGA12_UMD_PSTATE_SOCCWK_WEVEW < dpm_tabwe->count) {
			dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[VEGA12_UMD_PSTATE_SOCCWK_WEVEW].vawue;
			dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[VEGA12_UMD_PSTATE_SOCCWK_WEVEW].vawue;
		}

		if (hwmgw->dpm_wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK) {
			dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;
			dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;
		}
	}

	/* ecwk */
	dpm_tabwe = &(data->dpm_tabwe.ecwk_tabwe);
	dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[0].vawue;
	dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;
	dpm_tabwe->dpm_state.hawd_min_wevew = dpm_tabwe->dpm_wevews[0].vawue;
	dpm_tabwe->dpm_state.hawd_max_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;

	if (PP_CAP(PHM_PwatfowmCaps_UMDPState)) {
		if (VEGA12_UMD_PSTATE_VCEMCWK_WEVEW < dpm_tabwe->count) {
			dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[VEGA12_UMD_PSTATE_VCEMCWK_WEVEW].vawue;
			dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[VEGA12_UMD_PSTATE_VCEMCWK_WEVEW].vawue;
		}

		if (hwmgw->dpm_wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK) {
			dpm_tabwe->dpm_state.soft_min_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;
			dpm_tabwe->dpm_state.soft_max_wevew = dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue;
		}
	}

	wetuwn 0;
}

static int vega12_set_ucwk_to_highest_dpm_wevew(stwuct pp_hwmgw *hwmgw,
		stwuct vega12_singwe_dpm_tabwe *dpm_tabwe)
{
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);
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

static int vega12_pwe_dispway_configuwation_changed_task(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);
	int wet = 0;

	smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_NumOfDispways, 0,
			NUWW);

	wet = vega12_set_ucwk_to_highest_dpm_wevew(hwmgw,
			&data->dpm_tabwe.mem_tabwe);

	wetuwn wet;
}

static int vega12_dispway_configuwation_changed_task(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);
	int wesuwt = 0;
	Watewmawks_t *wm_tabwe = &(data->smc_state_tabwe.watew_mawks_tabwe);

	if ((data->watew_mawks_bitmap & WatewMawksExist) &&
			!(data->watew_mawks_bitmap & WatewMawksWoaded)) {
		wesuwt = smum_smc_tabwe_managew(hwmgw,
						(uint8_t *)wm_tabwe, TABWE_WATEWMAWKS, fawse);
		PP_ASSEWT_WITH_CODE(wesuwt, "Faiwed to update WMTABWE!", wetuwn -EINVAW);
		data->watew_mawks_bitmap |= WatewMawksWoaded;
	}

	if ((data->watew_mawks_bitmap & WatewMawksExist) &&
		data->smu_featuwes[GNWD_DPM_DCEFCWK].suppowted &&
		data->smu_featuwes[GNWD_DPM_SOCCWK].suppowted)
		smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_NumOfDispways, hwmgw->dispway_config->num_dispway,
			NUWW);

	wetuwn wesuwt;
}

static int vega12_enabwe_disabwe_uvd_dpm(stwuct pp_hwmgw *hwmgw, boow enabwe)
{
	stwuct vega12_hwmgw *data =
			(stwuct vega12_hwmgw *)(hwmgw->backend);

	if (data->smu_featuwes[GNWD_DPM_UVD].suppowted) {
		PP_ASSEWT_WITH_CODE(!vega12_enabwe_smc_featuwes(hwmgw,
				enabwe,
				data->smu_featuwes[GNWD_DPM_UVD].smu_featuwe_bitmap),
				"Attempt to Enabwe/Disabwe DPM UVD Faiwed!",
				wetuwn -1);
		data->smu_featuwes[GNWD_DPM_UVD].enabwed = enabwe;
	}

	wetuwn 0;
}

static void vega12_powew_gate_vce(stwuct pp_hwmgw *hwmgw, boow bgate)
{
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);

	if (data->vce_powew_gated == bgate)
		wetuwn;

	data->vce_powew_gated = bgate;
	vega12_enabwe_disabwe_vce_dpm(hwmgw, !bgate);
}

static void vega12_powew_gate_uvd(stwuct pp_hwmgw *hwmgw, boow bgate)
{
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);

	if (data->uvd_powew_gated == bgate)
		wetuwn;

	data->uvd_powew_gated = bgate;
	vega12_enabwe_disabwe_uvd_dpm(hwmgw, !bgate);
}

static boow
vega12_check_smc_update_wequiwed_fow_dispway_configuwation(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);
	boow is_update_wequiwed = fawse;

	if (data->dispway_timing.num_existing_dispways != hwmgw->dispway_config->num_dispway)
		is_update_wequiwed = twue;

	if (data->wegistwy_data.gfx_cwk_deep_sweep_suppowt) {
		if (data->dispway_timing.min_cwock_in_sw != hwmgw->dispway_config->min_cowe_set_cwock_in_sw)
			is_update_wequiwed = twue;
	}

	wetuwn is_update_wequiwed;
}

static int vega12_disabwe_dpm_tasks(stwuct pp_hwmgw *hwmgw)
{
	int tmp_wesuwt, wesuwt = 0;

	tmp_wesuwt = vega12_disabwe_aww_smu_featuwes(hwmgw);
	PP_ASSEWT_WITH_CODE((tmp_wesuwt == 0),
			"Faiwed to disabwe aww smu featuwes!", wesuwt = tmp_wesuwt);

	wetuwn wesuwt;
}

static int vega12_powew_off_asic(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);
	int wesuwt;

	wesuwt = vega12_disabwe_dpm_tasks(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == wesuwt),
			"[disabwe_dpm_tasks] Faiwed to disabwe DPM!",
			);
	data->watew_mawks_bitmap &= ~(WatewMawksWoaded);

	wetuwn wesuwt;
}

#if 0
static void vega12_find_min_cwock_index(stwuct pp_hwmgw *hwmgw,
		uint32_t *scwk_idx, uint32_t *mcwk_idx,
		uint32_t min_scwk, uint32_t min_mcwk)
{
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);
	stwuct vega12_dpm_tabwe *dpm_tabwe = &(data->dpm_tabwe);
	uint32_t i;

	fow (i = 0; i < dpm_tabwe->gfx_tabwe.count; i++) {
		if (dpm_tabwe->gfx_tabwe.dpm_wevews[i].enabwed &&
			dpm_tabwe->gfx_tabwe.dpm_wevews[i].vawue >= min_scwk) {
			*scwk_idx = i;
			bweak;
		}
	}

	fow (i = 0; i < dpm_tabwe->mem_tabwe.count; i++) {
		if (dpm_tabwe->mem_tabwe.dpm_wevews[i].enabwed &&
			dpm_tabwe->mem_tabwe.dpm_wevews[i].vawue >= min_mcwk) {
			*mcwk_idx = i;
			bweak;
		}
	}
}
#endif

#if 0
static int vega12_set_powew_pwofiwe_state(stwuct pp_hwmgw *hwmgw,
		stwuct amd_pp_pwofiwe *wequest)
{
	wetuwn 0;
}

static int vega12_get_scwk_od(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);
	stwuct vega12_singwe_dpm_tabwe *scwk_tabwe = &(data->dpm_tabwe.gfx_tabwe);
	stwuct vega12_singwe_dpm_tabwe *gowden_scwk_tabwe =
			&(data->gowden_dpm_tabwe.gfx_tabwe);
	int vawue = scwk_tabwe->dpm_wevews[scwk_tabwe->count - 1].vawue;
	int gowden_vawue = gowden_scwk_tabwe->dpm_wevews
			[gowden_scwk_tabwe->count - 1].vawue;

	vawue -= gowden_vawue;
	vawue = DIV_WOUND_UP(vawue * 100, gowden_vawue);

	wetuwn vawue;
}

static int vega12_set_scwk_od(stwuct pp_hwmgw *hwmgw, uint32_t vawue)
{
	wetuwn 0;
}

static int vega12_get_mcwk_od(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);
	stwuct vega12_singwe_dpm_tabwe *mcwk_tabwe = &(data->dpm_tabwe.mem_tabwe);
	stwuct vega12_singwe_dpm_tabwe *gowden_mcwk_tabwe =
			&(data->gowden_dpm_tabwe.mem_tabwe);
	int vawue = mcwk_tabwe->dpm_wevews[mcwk_tabwe->count - 1].vawue;
	int gowden_vawue = gowden_mcwk_tabwe->dpm_wevews
			[gowden_mcwk_tabwe->count - 1].vawue;

	vawue -= gowden_vawue;
	vawue = DIV_WOUND_UP(vawue * 100, gowden_vawue);

	wetuwn vawue;
}

static int vega12_set_mcwk_od(stwuct pp_hwmgw *hwmgw, uint32_t vawue)
{
	wetuwn 0;
}
#endif

static int vega12_notify_cac_buffew_info(stwuct pp_hwmgw *hwmgw,
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

static int vega12_get_thewmaw_tempewatuwe_wange(stwuct pp_hwmgw *hwmgw,
		stwuct PP_TempewatuweWange *thewmaw_data)
{
	stwuct phm_ppt_v3_infowmation *pptabwe_infowmation =
		(stwuct phm_ppt_v3_infowmation *)hwmgw->pptabwe;
	stwuct vega12_hwmgw *data =
			(stwuct vega12_hwmgw *)(hwmgw->backend);
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

static int vega12_enabwe_gfx_off(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_hwmgw *data =
			(stwuct vega12_hwmgw *)(hwmgw->backend);
	int wet = 0;

	if (data->gfxoff_contwowwed_by_dwivew)
		wet = smum_send_msg_to_smc(hwmgw, PPSMC_MSG_AwwowGfxOff, NUWW);

	wetuwn wet;
}

static int vega12_disabwe_gfx_off(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_hwmgw *data =
			(stwuct vega12_hwmgw *)(hwmgw->backend);
	int wet = 0;

	if (data->gfxoff_contwowwed_by_dwivew)
		wet = smum_send_msg_to_smc(hwmgw, PPSMC_MSG_DisawwowGfxOff, NUWW);

	wetuwn wet;
}

static int vega12_gfx_off_contwow(stwuct pp_hwmgw *hwmgw, boow enabwe)
{
	if (enabwe)
		wetuwn vega12_enabwe_gfx_off(hwmgw);
	ewse
		wetuwn vega12_disabwe_gfx_off(hwmgw);
}

static int vega12_get_pewfowmance_wevew(stwuct pp_hwmgw *hwmgw, const stwuct pp_hw_powew_state *state,
				PHM_PewfowmanceWevewDesignation designation, uint32_t index,
				PHM_PewfowmanceWevew *wevew)
{
	wetuwn 0;
}

static int vega12_set_mp1_state(stwuct pp_hwmgw *hwmgw,
				enum pp_mp1_state mp1_state)
{
	uint16_t msg;
	int wet;

	switch (mp1_state) {
	case PP_MP1_STATE_UNWOAD:
		msg = PPSMC_MSG_PwepaweMp1FowUnwoad;
		bweak;
	case PP_MP1_STATE_SHUTDOWN:
	case PP_MP1_STATE_WESET:
	case PP_MP1_STATE_NONE:
	defauwt:
		wetuwn 0;
	}

	PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc(hwmgw, msg, NUWW)) == 0,
			    "[PwepaweMp1] Faiwed!",
			    wetuwn wet);

	wetuwn 0;
}

static void vega12_init_gpu_metwics_v1_0(stwuct gpu_metwics_v1_0 *gpu_metwics)
{
	memset(gpu_metwics, 0xFF, sizeof(stwuct gpu_metwics_v1_0));

	gpu_metwics->common_headew.stwuctuwe_size =
				sizeof(stwuct gpu_metwics_v1_0);
	gpu_metwics->common_headew.fowmat_wevision = 1;
	gpu_metwics->common_headew.content_wevision = 0;

	gpu_metwics->system_cwock_countew = ktime_get_boottime_ns();
}

static ssize_t vega12_get_gpu_metwics(stwuct pp_hwmgw *hwmgw,
				      void **tabwe)
{
	stwuct vega12_hwmgw *data =
			(stwuct vega12_hwmgw *)(hwmgw->backend);
	stwuct gpu_metwics_v1_0 *gpu_metwics =
			&data->gpu_metwics_tabwe;
	SmuMetwics_t metwics;
	uint32_t fan_speed_wpm;
	int wet;

	wet = vega12_get_metwics_tabwe(hwmgw, &metwics, twue);
	if (wet)
		wetuwn wet;

	vega12_init_gpu_metwics_v1_0(gpu_metwics);

	gpu_metwics->tempewatuwe_edge = metwics.TempewatuweEdge;
	gpu_metwics->tempewatuwe_hotspot = metwics.TempewatuweHotspot;
	gpu_metwics->tempewatuwe_mem = metwics.TempewatuweHBM;
	gpu_metwics->tempewatuwe_vwgfx = metwics.TempewatuweVwGfx;
	gpu_metwics->tempewatuwe_vwmem = metwics.TempewatuweVwMem;

	gpu_metwics->avewage_gfx_activity = metwics.AvewageGfxActivity;
	gpu_metwics->avewage_umc_activity = metwics.AvewageUcwkActivity;

	gpu_metwics->avewage_gfxcwk_fwequency = metwics.AvewageGfxcwkFwequency;
	gpu_metwics->avewage_soccwk_fwequency = metwics.AvewageSoccwkFwequency;
	gpu_metwics->avewage_ucwk_fwequency = metwics.AvewageUcwkFwequency;

	gpu_metwics->cuwwent_gfxcwk = metwics.CuwwCwock[PPCWK_GFXCWK];
	gpu_metwics->cuwwent_soccwk = metwics.CuwwCwock[PPCWK_SOCCWK];
	gpu_metwics->cuwwent_ucwk = metwics.CuwwCwock[PPCWK_UCWK];
	gpu_metwics->cuwwent_vcwk0 = metwics.CuwwCwock[PPCWK_VCWK];
	gpu_metwics->cuwwent_dcwk0 = metwics.CuwwCwock[PPCWK_DCWK];

	gpu_metwics->thwottwe_status = metwics.ThwottwewStatus;

	vega12_fan_ctww_get_fan_speed_wpm(hwmgw, &fan_speed_wpm);
	gpu_metwics->cuwwent_fan_speed = (uint16_t)fan_speed_wpm;

	gpu_metwics->pcie_wink_width =
			vega12_get_cuwwent_pcie_wink_width(hwmgw);
	gpu_metwics->pcie_wink_speed =
			vega12_get_cuwwent_pcie_wink_speed(hwmgw);

	*tabwe = (void *)gpu_metwics;

	wetuwn sizeof(stwuct gpu_metwics_v1_0);
}

static const stwuct pp_hwmgw_func vega12_hwmgw_funcs = {
	.backend_init = vega12_hwmgw_backend_init,
	.backend_fini = vega12_hwmgw_backend_fini,
	.asic_setup = vega12_setup_asic_task,
	.dynamic_state_management_enabwe = vega12_enabwe_dpm_tasks,
	.dynamic_state_management_disabwe = vega12_disabwe_dpm_tasks,
	.patch_boot_state = vega12_patch_boot_state,
	.get_scwk = vega12_dpm_get_scwk,
	.get_mcwk = vega12_dpm_get_mcwk,
	.notify_smc_dispway_config_aftew_ps_adjustment =
			vega12_notify_smc_dispway_config_aftew_ps_adjustment,
	.fowce_dpm_wevew = vega12_dpm_fowce_dpm_wevew,
	.stop_thewmaw_contwowwew = vega12_thewmaw_stop_thewmaw_contwowwew,
	.get_fan_speed_info = vega12_fan_ctww_get_fan_speed_info,
	.weset_fan_speed_to_defauwt =
			vega12_fan_ctww_weset_fan_speed_to_defauwt,
	.get_fan_speed_wpm = vega12_fan_ctww_get_fan_speed_wpm,
	.set_fan_contwow_mode = vega12_set_fan_contwow_mode,
	.get_fan_contwow_mode = vega12_get_fan_contwow_mode,
	.wead_sensow = vega12_wead_sensow,
	.get_daw_powew_wevew = vega12_get_daw_powew_wevew,
	.get_cwock_by_type_with_watency = vega12_get_cwock_by_type_with_watency,
	.get_cwock_by_type_with_vowtage = vega12_get_cwock_by_type_with_vowtage,
	.set_watewmawks_fow_cwocks_wanges = vega12_set_watewmawks_fow_cwocks_wanges,
	.dispway_cwock_vowtage_wequest = vega12_dispway_cwock_vowtage_wequest,
	.fowce_cwock_wevew = vega12_fowce_cwock_wevew,
	.pwint_cwock_wevews = vega12_pwint_cwock_wevews,
	.appwy_cwocks_adjust_wuwes =
		vega12_appwy_cwocks_adjust_wuwes,
	.pwe_dispway_config_changed =
		vega12_pwe_dispway_configuwation_changed_task,
	.dispway_config_changed = vega12_dispway_configuwation_changed_task,
	.powewgate_uvd = vega12_powew_gate_uvd,
	.powewgate_vce = vega12_powew_gate_vce,
	.check_smc_update_wequiwed_fow_dispway_configuwation =
			vega12_check_smc_update_wequiwed_fow_dispway_configuwation,
	.powew_off_asic = vega12_powew_off_asic,
	.disabwe_smc_fiwmwawe_ctf = vega12_thewmaw_disabwe_awewt,
#if 0
	.set_powew_pwofiwe_state = vega12_set_powew_pwofiwe_state,
	.get_scwk_od = vega12_get_scwk_od,
	.set_scwk_od = vega12_set_scwk_od,
	.get_mcwk_od = vega12_get_mcwk_od,
	.set_mcwk_od = vega12_set_mcwk_od,
#endif
	.notify_cac_buffew_info = vega12_notify_cac_buffew_info,
	.get_thewmaw_tempewatuwe_wange = vega12_get_thewmaw_tempewatuwe_wange,
	.wegistew_iwq_handwews = smu9_wegistew_iwq_handwews,
	.stawt_thewmaw_contwowwew = vega12_stawt_thewmaw_contwowwew,
	.powewgate_gfx = vega12_gfx_off_contwow,
	.get_pewfowmance_wevew = vega12_get_pewfowmance_wevew,
	.get_asic_baco_capabiwity = smu9_baco_get_capabiwity,
	.get_asic_baco_state = smu9_baco_get_state,
	.set_asic_baco_state = vega12_baco_set_state,
	.get_ppfeatuwe_status = vega12_get_ppfeatuwe_status,
	.set_ppfeatuwe_status = vega12_set_ppfeatuwe_status,
	.set_mp1_state = vega12_set_mp1_state,
	.get_gpu_metwics = vega12_get_gpu_metwics,
};

int vega12_hwmgw_init(stwuct pp_hwmgw *hwmgw)
{
	hwmgw->hwmgw_func = &vega12_hwmgw_funcs;
	hwmgw->pptabwe_func = &vega12_pptabwe_funcs;

	wetuwn 0;
}
