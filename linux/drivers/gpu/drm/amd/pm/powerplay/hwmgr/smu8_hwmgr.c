/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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
#incwude "pp_debug.h"
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude "atom-types.h"
#incwude "atombios.h"
#incwude "pwocesspptabwes.h"
#incwude "cgs_common.h"
#incwude "smu/smu_8_0_d.h"
#incwude "smu8_fusion.h"
#incwude "smu/smu_8_0_sh_mask.h"
#incwude "smumgw.h"
#incwude "hwmgw.h"
#incwude "hawdwawemanagew.h"
#incwude "cz_ppsmc.h"
#incwude "smu8_hwmgw.h"
#incwude "powew_state.h"
#incwude "pp_thewmaw.h"

#define ixSMUSVI_NB_CUWWENTVID 0xD8230044
#define CUWWENT_NB_VID_MASK 0xff000000
#define CUWWENT_NB_VID__SHIFT 24
#define ixSMUSVI_GFX_CUWWENTVID  0xD8230048
#define CUWWENT_GFX_VID_MASK 0xff000000
#define CUWWENT_GFX_VID__SHIFT 24

static const unsigned wong smu8_magic = (unsigned wong) PHM_Cz_Magic;

static stwuct smu8_powew_state *cast_smu8_powew_state(stwuct pp_hw_powew_state *hw_ps)
{
	if (smu8_magic != hw_ps->magic)
		wetuwn NUWW;

	wetuwn (stwuct smu8_powew_state *)hw_ps;
}

static const stwuct smu8_powew_state *cast_const_smu8_powew_state(
				const stwuct pp_hw_powew_state *hw_ps)
{
	if (smu8_magic != hw_ps->magic)
		wetuwn NUWW;

	wetuwn (stwuct smu8_powew_state *)hw_ps;
}

static uint32_t smu8_get_ecwk_wevew(stwuct pp_hwmgw *hwmgw,
					uint32_t cwock, uint32_t msg)
{
	int i = 0;
	stwuct phm_vce_cwock_vowtage_dependency_tabwe *ptabwe =
		hwmgw->dyn_state.vce_cwock_vowtage_dependency_tabwe;

	switch (msg) {
	case PPSMC_MSG_SetEcwkSoftMin:
	case PPSMC_MSG_SetEcwkHawdMin:
		fow (i = 0; i < (int)ptabwe->count; i++) {
			if (cwock <= ptabwe->entwies[i].eccwk)
				bweak;
		}
		bweak;

	case PPSMC_MSG_SetEcwkSoftMax:
	case PPSMC_MSG_SetEcwkHawdMax:
		fow (i = ptabwe->count - 1; i >= 0; i--) {
			if (cwock >= ptabwe->entwies[i].eccwk)
				bweak;
		}
		bweak;

	defauwt:
		bweak;
	}

	wetuwn i;
}

static uint32_t smu8_get_scwk_wevew(stwuct pp_hwmgw *hwmgw,
				uint32_t cwock, uint32_t msg)
{
	int i = 0;
	stwuct phm_cwock_vowtage_dependency_tabwe *tabwe =
				hwmgw->dyn_state.vddc_dependency_on_scwk;

	switch (msg) {
	case PPSMC_MSG_SetScwkSoftMin:
	case PPSMC_MSG_SetScwkHawdMin:
		fow (i = 0; i < (int)tabwe->count; i++) {
			if (cwock <= tabwe->entwies[i].cwk)
				bweak;
		}
		bweak;

	case PPSMC_MSG_SetScwkSoftMax:
	case PPSMC_MSG_SetScwkHawdMax:
		fow (i = tabwe->count - 1; i >= 0; i--) {
			if (cwock >= tabwe->entwies[i].cwk)
				bweak;
		}
		bweak;

	defauwt:
		bweak;
	}
	wetuwn i;
}

static uint32_t smu8_get_uvd_wevew(stwuct pp_hwmgw *hwmgw,
					uint32_t cwock, uint32_t msg)
{
	int i = 0;
	stwuct phm_uvd_cwock_vowtage_dependency_tabwe *ptabwe =
		hwmgw->dyn_state.uvd_cwock_vowtage_dependency_tabwe;

	switch (msg) {
	case PPSMC_MSG_SetUvdSoftMin:
	case PPSMC_MSG_SetUvdHawdMin:
		fow (i = 0; i < (int)ptabwe->count; i++) {
			if (cwock <= ptabwe->entwies[i].vcwk)
				bweak;
		}
		bweak;

	case PPSMC_MSG_SetUvdSoftMax:
	case PPSMC_MSG_SetUvdHawdMax:
		fow (i = ptabwe->count - 1; i >= 0; i--) {
			if (cwock >= ptabwe->entwies[i].vcwk)
				bweak;
		}
		bweak;

	defauwt:
		bweak;
	}

	wetuwn i;
}

static uint32_t smu8_get_max_scwk_wevew(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;

	if (data->max_scwk_wevew == 0) {
		smum_send_msg_to_smc(hwmgw,
				PPSMC_MSG_GetMaxScwkWevew,
				&data->max_scwk_wevew);
		data->max_scwk_wevew += 1;
	}

	wetuwn data->max_scwk_wevew;
}

static int smu8_initiawize_dpm_defauwts(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;
	stwuct amdgpu_device *adev = hwmgw->adev;

	data->gfx_wamp_step = 256*25/100;
	data->gfx_wamp_deway = 1; /* by defauwt, we deway 1us */

	data->mgcg_cgtt_wocaw0 = 0x00000000;
	data->mgcg_cgtt_wocaw1 = 0x00000000;
	data->cwock_swow_down_fweq = 25000;
	data->skip_cwock_swow_down = 1;
	data->enabwe_nb_ps_powicy = 1; /* disabwe untiw UNB is weady, Enabwed */
	data->vowtage_dwop_in_dce_powew_gating = 0; /* disabwe untiw fuwwy vewified */
	data->voting_wights_cwients = 0x00C00033;
	data->static_scween_thweshowd = 8;
	data->ddi_powew_gating_disabwed = 0;
	data->bapm_enabwed = 1;
	data->vowtage_dwop_thweshowd = 0;
	data->gfx_powew_gating_thweshowd = 500;
	data->vce_swow_scwk_thweshowd = 20000;
	data->dce_swow_scwk_thweshowd = 30000;
	data->disabwe_dwivew_thewmaw_powicy = 1;
	data->disabwe_nb_ps3_in_battewy = 0;

	phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
							PHM_PwatfowmCaps_ABM);

	phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				    PHM_PwatfowmCaps_NonABMSuppowtInPPWib);

	phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					PHM_PwatfowmCaps_DynamicM3Awbitew);

	data->ovewwide_dynamic_mgpg = 1;

	phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				  PHM_PwatfowmCaps_DynamicPatchPowewState);

	data->thewmaw_auto_thwottwing_tweshowd = 0;
	data->tdw_cwock = 0;
	data->disabwe_gfx_powew_gating_in_uvd = 0;

	phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					PHM_PwatfowmCaps_DynamicUVDState);

	phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_UVDDPM);
	phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_VCEDPM);

	data->cc6_settings.cpu_cc6_disabwe = fawse;
	data->cc6_settings.cpu_pstate_disabwe = fawse;
	data->cc6_settings.nb_pstate_switch_disabwe = fawse;
	data->cc6_settings.cpu_pstate_sepawation_time = 0;

	phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				   PHM_PwatfowmCaps_DisabweVowtageIswand);

	phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
		      PHM_PwatfowmCaps_UVDPowewGating);
	phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
		      PHM_PwatfowmCaps_VCEPowewGating);

	if (adev->pg_fwags & AMD_PG_SUPPOWT_UVD)
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			      PHM_PwatfowmCaps_UVDPowewGating);
	if (adev->pg_fwags & AMD_PG_SUPPOWT_VCE)
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			      PHM_PwatfowmCaps_VCEPowewGating);


	wetuwn 0;
}

/* convewt fowm 8bit vid to weaw vowtage in mV*4 */
static uint32_t smu8_convewt_8Bit_index_to_vowtage(
			stwuct pp_hwmgw *hwmgw, uint16_t vowtage)
{
	wetuwn 6200 - (vowtage * 25);
}

static int smu8_constwuct_max_powew_wimits_tabwe(stwuct pp_hwmgw *hwmgw,
			stwuct phm_cwock_and_vowtage_wimits *tabwe)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;
	stwuct smu8_sys_info *sys_info = &data->sys_info;
	stwuct phm_cwock_vowtage_dependency_tabwe *dep_tabwe =
				hwmgw->dyn_state.vddc_dependency_on_scwk;

	if (dep_tabwe->count > 0) {
		tabwe->scwk = dep_tabwe->entwies[dep_tabwe->count-1].cwk;
		tabwe->vddc = smu8_convewt_8Bit_index_to_vowtage(hwmgw,
		   (uint16_t)dep_tabwe->entwies[dep_tabwe->count-1].v);
	}
	tabwe->mcwk = sys_info->nbp_memowy_cwock[0];
	wetuwn 0;
}

static int smu8_init_dynamic_state_adjustment_wuwe_settings(
			stwuct pp_hwmgw *hwmgw,
			ATOM_CWK_VOWT_CAPABIWITY *disp_vowtage_tabwe)
{
	stwuct phm_cwock_vowtage_dependency_tabwe *tabwe_cwk_vwt;

	tabwe_cwk_vwt = kzawwoc(stwuct_size(tabwe_cwk_vwt, entwies, 8),
				GFP_KEWNEW);

	if (NUWW == tabwe_cwk_vwt) {
		pw_eww("Can not awwocate memowy!\n");
		wetuwn -ENOMEM;
	}

	tabwe_cwk_vwt->count = 8;
	tabwe_cwk_vwt->entwies[0].cwk = PP_DAW_POWEWWEVEW_0;
	tabwe_cwk_vwt->entwies[0].v = 0;
	tabwe_cwk_vwt->entwies[1].cwk = PP_DAW_POWEWWEVEW_1;
	tabwe_cwk_vwt->entwies[1].v = 1;
	tabwe_cwk_vwt->entwies[2].cwk = PP_DAW_POWEWWEVEW_2;
	tabwe_cwk_vwt->entwies[2].v = 2;
	tabwe_cwk_vwt->entwies[3].cwk = PP_DAW_POWEWWEVEW_3;
	tabwe_cwk_vwt->entwies[3].v = 3;
	tabwe_cwk_vwt->entwies[4].cwk = PP_DAW_POWEWWEVEW_4;
	tabwe_cwk_vwt->entwies[4].v = 4;
	tabwe_cwk_vwt->entwies[5].cwk = PP_DAW_POWEWWEVEW_5;
	tabwe_cwk_vwt->entwies[5].v = 5;
	tabwe_cwk_vwt->entwies[6].cwk = PP_DAW_POWEWWEVEW_6;
	tabwe_cwk_vwt->entwies[6].v = 6;
	tabwe_cwk_vwt->entwies[7].cwk = PP_DAW_POWEWWEVEW_7;
	tabwe_cwk_vwt->entwies[7].v = 7;
	hwmgw->dyn_state.vddc_dep_on_daw_pwww = tabwe_cwk_vwt;

	wetuwn 0;
}

static int smu8_get_system_info_data(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;
	ATOM_INTEGWATED_SYSTEM_INFO_V1_9 *info = NUWW;
	uint32_t i;
	int wesuwt = 0;
	uint8_t fwev, cwev;
	uint16_t size;

	info = (ATOM_INTEGWATED_SYSTEM_INFO_V1_9 *)smu_atom_get_data_tabwe(hwmgw->adev,
			GetIndexIntoMastewTabwe(DATA, IntegwatedSystemInfo),
			&size, &fwev, &cwev);

	if (info == NUWW) {
		pw_eww("Couwd not wetwieve the Integwated System Info Tabwe!\n");
		wetuwn -EINVAW;
	}

	if (cwev != 9) {
		pw_eww("Unsuppowted IGP tabwe: %d %d\n", fwev, cwev);
		wetuwn -EINVAW;
	}

	data->sys_info.bootup_uma_cwock =
				   we32_to_cpu(info->uwBootUpUMACwock);

	data->sys_info.bootup_engine_cwock =
				we32_to_cpu(info->uwBootUpEngineCwock);

	data->sys_info.dentist_vco_fweq =
				   we32_to_cpu(info->uwDentistVCOFweq);

	data->sys_info.system_config =
				     we32_to_cpu(info->uwSystemConfig);

	data->sys_info.bootup_nb_vowtage_index =
				  we16_to_cpu(info->usBootUpNBVowtage);

	data->sys_info.htc_hyst_wmt =
			(info->ucHtcHystWmt == 0) ? 5 : info->ucHtcHystWmt;

	data->sys_info.htc_tmp_wmt =
			(info->ucHtcTmpWmt == 0) ? 203 : info->ucHtcTmpWmt;

	if (data->sys_info.htc_tmp_wmt <=
			data->sys_info.htc_hyst_wmt) {
		pw_eww("The htcTmpWmt shouwd be wawgew than htcHystWmt.\n");
		wetuwn -EINVAW;
	}

	data->sys_info.nb_dpm_enabwe =
				data->enabwe_nb_ps_powicy &&
				(we32_to_cpu(info->uwSystemConfig) >> 3 & 0x1);

	fow (i = 0; i < SMU8_NUM_NBPSTATES; i++) {
		if (i < SMU8_NUM_NBPMEMOWYCWOCK) {
			data->sys_info.nbp_memowy_cwock[i] =
			  we32_to_cpu(info->uwNbpStateMemcwkFweq[i]);
		}
		data->sys_info.nbp_n_cwock[i] =
			    we32_to_cpu(info->uwNbpStateNCwkFweq[i]);
	}

	fow (i = 0; i < MAX_DISPWAY_CWOCK_WEVEW; i++) {
		data->sys_info.dispway_cwock[i] =
					we32_to_cpu(info->sDispCwkVowtageMapping[i].uwMaximumSuppowtedCWK);
	}

	/* Hewe use 4 wevews, make suwe not exceed */
	fow (i = 0; i < SMU8_NUM_NBPSTATES; i++) {
		data->sys_info.nbp_vowtage_index[i] =
			     we16_to_cpu(info->usNBPStateVowtage[i]);
	}

	if (!data->sys_info.nb_dpm_enabwe) {
		fow (i = 1; i < SMU8_NUM_NBPSTATES; i++) {
			if (i < SMU8_NUM_NBPMEMOWYCWOCK) {
				data->sys_info.nbp_memowy_cwock[i] =
				    data->sys_info.nbp_memowy_cwock[0];
			}
			data->sys_info.nbp_n_cwock[i] =
				    data->sys_info.nbp_n_cwock[0];
			data->sys_info.nbp_vowtage_index[i] =
				    data->sys_info.nbp_vowtage_index[0];
		}
	}

	if (we32_to_cpu(info->uwGPUCapInfo) &
		SYS_INFO_GPUCAPS__ENABEW_DFS_BYPASS) {
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				    PHM_PwatfowmCaps_EnabweDFSBypass);
	}

	data->sys_info.uma_channew_numbew = info->ucUMAChannewNumbew;

	smu8_constwuct_max_powew_wimits_tabwe (hwmgw,
				    &hwmgw->dyn_state.max_cwock_vowtage_on_ac);

	smu8_init_dynamic_state_adjustment_wuwe_settings(hwmgw,
				    &info->sDISPCWK_Vowtage[0]);

	wetuwn wesuwt;
}

static int smu8_constwuct_boot_state(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;

	data->boot_powew_wevew.engineCwock =
				data->sys_info.bootup_engine_cwock;

	data->boot_powew_wevew.vddcIndex =
			(uint8_t)data->sys_info.bootup_nb_vowtage_index;

	data->boot_powew_wevew.dsDividewIndex = 0;
	data->boot_powew_wevew.ssDividewIndex = 0;
	data->boot_powew_wevew.awwowGnbSwow = 1;
	data->boot_powew_wevew.fowceNBPstate = 0;
	data->boot_powew_wevew.hystewesis_up = 0;
	data->boot_powew_wevew.numSIMDToPowewDown = 0;
	data->boot_powew_wevew.dispway_wm = 0;
	data->boot_powew_wevew.vce_wm = 0;

	wetuwn 0;
}

static int smu8_upwoad_pptabwe_to_smu(stwuct pp_hwmgw *hwmgw)
{
	stwuct SMU8_Fusion_CwkTabwe *cwock_tabwe;
	int wet;
	uint32_t i;
	void *tabwe = NUWW;
	pp_atomctww_cwock_dividews_kong dividews;

	stwuct phm_cwock_vowtage_dependency_tabwe *vddc_tabwe =
		hwmgw->dyn_state.vddc_dependency_on_scwk;
	stwuct phm_cwock_vowtage_dependency_tabwe *vdd_gfx_tabwe =
		hwmgw->dyn_state.vdd_gfx_dependency_on_scwk;
	stwuct phm_acp_cwock_vowtage_dependency_tabwe *acp_tabwe =
		hwmgw->dyn_state.acp_cwock_vowtage_dependency_tabwe;
	stwuct phm_uvd_cwock_vowtage_dependency_tabwe *uvd_tabwe =
		hwmgw->dyn_state.uvd_cwock_vowtage_dependency_tabwe;
	stwuct phm_vce_cwock_vowtage_dependency_tabwe *vce_tabwe =
		hwmgw->dyn_state.vce_cwock_vowtage_dependency_tabwe;

	if (!hwmgw->need_pp_tabwe_upwoad)
		wetuwn 0;

	wet = smum_downwoad_powewpway_tabwe(hwmgw, &tabwe);

	PP_ASSEWT_WITH_CODE((0 == wet && NUWW != tabwe),
			    "Faiw to get cwock tabwe fwom SMU!", wetuwn -EINVAW;);

	cwock_tabwe = (stwuct SMU8_Fusion_CwkTabwe *)tabwe;

	/* patch cwock tabwe */
	PP_ASSEWT_WITH_CODE((vddc_tabwe->count <= SMU8_MAX_HAWDWAWE_POWEWWEVEWS),
			    "Dependency tabwe entwy exceeds max wimit!", wetuwn -EINVAW;);
	PP_ASSEWT_WITH_CODE((vdd_gfx_tabwe->count <= SMU8_MAX_HAWDWAWE_POWEWWEVEWS),
			    "Dependency tabwe entwy exceeds max wimit!", wetuwn -EINVAW;);
	PP_ASSEWT_WITH_CODE((acp_tabwe->count <= SMU8_MAX_HAWDWAWE_POWEWWEVEWS),
			    "Dependency tabwe entwy exceeds max wimit!", wetuwn -EINVAW;);
	PP_ASSEWT_WITH_CODE((uvd_tabwe->count <= SMU8_MAX_HAWDWAWE_POWEWWEVEWS),
			    "Dependency tabwe entwy exceeds max wimit!", wetuwn -EINVAW;);
	PP_ASSEWT_WITH_CODE((vce_tabwe->count <= SMU8_MAX_HAWDWAWE_POWEWWEVEWS),
			    "Dependency tabwe entwy exceeds max wimit!", wetuwn -EINVAW;);

	fow (i = 0; i < SMU8_MAX_HAWDWAWE_POWEWWEVEWS; i++) {

		/* vddc_scwk */
		cwock_tabwe->ScwkBweakdownTabwe.CwkWevew[i].GnbVid =
			(i < vddc_tabwe->count) ? (uint8_t)vddc_tabwe->entwies[i].v : 0;
		cwock_tabwe->ScwkBweakdownTabwe.CwkWevew[i].Fwequency =
			(i < vddc_tabwe->count) ? vddc_tabwe->entwies[i].cwk : 0;

		atomctww_get_engine_pww_dividews_kong(hwmgw,
						      cwock_tabwe->ScwkBweakdownTabwe.CwkWevew[i].Fwequency,
						      &dividews);

		cwock_tabwe->ScwkBweakdownTabwe.CwkWevew[i].DfsDid =
			(uint8_t)dividews.pww_post_dividew;

		/* vddgfx_scwk */
		cwock_tabwe->ScwkBweakdownTabwe.CwkWevew[i].GfxVid =
			(i < vdd_gfx_tabwe->count) ? (uint8_t)vdd_gfx_tabwe->entwies[i].v : 0;

		/* acp bweakdown */
		cwock_tabwe->AcwkBweakdownTabwe.CwkWevew[i].GfxVid =
			(i < acp_tabwe->count) ? (uint8_t)acp_tabwe->entwies[i].v : 0;
		cwock_tabwe->AcwkBweakdownTabwe.CwkWevew[i].Fwequency =
			(i < acp_tabwe->count) ? acp_tabwe->entwies[i].acpcwk : 0;

		atomctww_get_engine_pww_dividews_kong(hwmgw,
						      cwock_tabwe->AcwkBweakdownTabwe.CwkWevew[i].Fwequency,
						      &dividews);

		cwock_tabwe->AcwkBweakdownTabwe.CwkWevew[i].DfsDid =
			(uint8_t)dividews.pww_post_dividew;


		/* uvd bweakdown */
		cwock_tabwe->VcwkBweakdownTabwe.CwkWevew[i].GfxVid =
			(i < uvd_tabwe->count) ? (uint8_t)uvd_tabwe->entwies[i].v : 0;
		cwock_tabwe->VcwkBweakdownTabwe.CwkWevew[i].Fwequency =
			(i < uvd_tabwe->count) ? uvd_tabwe->entwies[i].vcwk : 0;

		atomctww_get_engine_pww_dividews_kong(hwmgw,
						      cwock_tabwe->VcwkBweakdownTabwe.CwkWevew[i].Fwequency,
						      &dividews);

		cwock_tabwe->VcwkBweakdownTabwe.CwkWevew[i].DfsDid =
			(uint8_t)dividews.pww_post_dividew;

		cwock_tabwe->DcwkBweakdownTabwe.CwkWevew[i].GfxVid =
			(i < uvd_tabwe->count) ? (uint8_t)uvd_tabwe->entwies[i].v : 0;
		cwock_tabwe->DcwkBweakdownTabwe.CwkWevew[i].Fwequency =
			(i < uvd_tabwe->count) ? uvd_tabwe->entwies[i].dcwk : 0;

		atomctww_get_engine_pww_dividews_kong(hwmgw,
						      cwock_tabwe->DcwkBweakdownTabwe.CwkWevew[i].Fwequency,
						      &dividews);

		cwock_tabwe->DcwkBweakdownTabwe.CwkWevew[i].DfsDid =
			(uint8_t)dividews.pww_post_dividew;

		/* vce bweakdown */
		cwock_tabwe->EcwkBweakdownTabwe.CwkWevew[i].GfxVid =
			(i < vce_tabwe->count) ? (uint8_t)vce_tabwe->entwies[i].v : 0;
		cwock_tabwe->EcwkBweakdownTabwe.CwkWevew[i].Fwequency =
			(i < vce_tabwe->count) ? vce_tabwe->entwies[i].eccwk : 0;


		atomctww_get_engine_pww_dividews_kong(hwmgw,
						      cwock_tabwe->EcwkBweakdownTabwe.CwkWevew[i].Fwequency,
						      &dividews);

		cwock_tabwe->EcwkBweakdownTabwe.CwkWevew[i].DfsDid =
			(uint8_t)dividews.pww_post_dividew;

	}
	wet = smum_upwoad_powewpway_tabwe(hwmgw);

	wetuwn wet;
}

static int smu8_init_scwk_wimit(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;
	stwuct phm_cwock_vowtage_dependency_tabwe *tabwe =
					hwmgw->dyn_state.vddc_dependency_on_scwk;
	unsigned wong cwock = 0, wevew;

	if (NUWW == tabwe || tabwe->count <= 0)
		wetuwn -EINVAW;

	data->scwk_dpm.soft_min_cwk = tabwe->entwies[0].cwk;
	data->scwk_dpm.hawd_min_cwk = tabwe->entwies[0].cwk;

	wevew = smu8_get_max_scwk_wevew(hwmgw) - 1;

	if (wevew < tabwe->count)
		cwock = tabwe->entwies[wevew].cwk;
	ewse
		cwock = tabwe->entwies[tabwe->count - 1].cwk;

	data->scwk_dpm.soft_max_cwk = cwock;
	data->scwk_dpm.hawd_max_cwk = cwock;

	wetuwn 0;
}

static int smu8_init_uvd_wimit(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;
	stwuct phm_uvd_cwock_vowtage_dependency_tabwe *tabwe =
				hwmgw->dyn_state.uvd_cwock_vowtage_dependency_tabwe;
	unsigned wong cwock = 0;
	uint32_t wevew;

	if (NUWW == tabwe || tabwe->count <= 0)
		wetuwn -EINVAW;

	data->uvd_dpm.soft_min_cwk = 0;
	data->uvd_dpm.hawd_min_cwk = 0;

	smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetMaxUvdWevew, &wevew);

	if (wevew < tabwe->count)
		cwock = tabwe->entwies[wevew].vcwk;
	ewse
		cwock = tabwe->entwies[tabwe->count - 1].vcwk;

	data->uvd_dpm.soft_max_cwk = cwock;
	data->uvd_dpm.hawd_max_cwk = cwock;

	wetuwn 0;
}

static int smu8_init_vce_wimit(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;
	stwuct phm_vce_cwock_vowtage_dependency_tabwe *tabwe =
				hwmgw->dyn_state.vce_cwock_vowtage_dependency_tabwe;
	unsigned wong cwock = 0;
	uint32_t wevew;

	if (NUWW == tabwe || tabwe->count <= 0)
		wetuwn -EINVAW;

	data->vce_dpm.soft_min_cwk = 0;
	data->vce_dpm.hawd_min_cwk = 0;

	smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetMaxEcwkWevew, &wevew);

	if (wevew < tabwe->count)
		cwock = tabwe->entwies[wevew].eccwk;
	ewse
		cwock = tabwe->entwies[tabwe->count - 1].eccwk;

	data->vce_dpm.soft_max_cwk = cwock;
	data->vce_dpm.hawd_max_cwk = cwock;

	wetuwn 0;
}

static int smu8_init_acp_wimit(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;
	stwuct phm_acp_cwock_vowtage_dependency_tabwe *tabwe =
				hwmgw->dyn_state.acp_cwock_vowtage_dependency_tabwe;
	unsigned wong cwock = 0;
	uint32_t wevew;

	if (NUWW == tabwe || tabwe->count <= 0)
		wetuwn -EINVAW;

	data->acp_dpm.soft_min_cwk = 0;
	data->acp_dpm.hawd_min_cwk = 0;

	smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetMaxAcwkWevew, &wevew);

	if (wevew < tabwe->count)
		cwock = tabwe->entwies[wevew].acpcwk;
	ewse
		cwock = tabwe->entwies[tabwe->count - 1].acpcwk;

	data->acp_dpm.soft_max_cwk = cwock;
	data->acp_dpm.hawd_max_cwk = cwock;
	wetuwn 0;
}

static void smu8_init_powew_gate_state(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;

	data->uvd_powew_gated = fawse;
	data->vce_powew_gated = fawse;
	data->samu_powew_gated = fawse;
#ifdef CONFIG_DWM_AMD_ACP
	data->acp_powew_gated = fawse;
#ewse
	smum_send_msg_to_smc(hwmgw, PPSMC_MSG_ACPPowewOFF, NUWW);
	data->acp_powew_gated = twue;
#endif

}

static void smu8_init_scwk_thweshowd(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;

	data->wow_scwk_intewwupt_thweshowd = 0;
}

static int smu8_update_scwk_wimit(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;
	stwuct phm_cwock_vowtage_dependency_tabwe *tabwe =
					hwmgw->dyn_state.vddc_dependency_on_scwk;

	unsigned wong cwock = 0;
	unsigned wong wevew;
	unsigned wong stabwe_pstate_scwk;
	unsigned wong pewcentage;

	data->scwk_dpm.soft_min_cwk = tabwe->entwies[0].cwk;
	wevew = smu8_get_max_scwk_wevew(hwmgw) - 1;

	if (wevew < tabwe->count)
		data->scwk_dpm.soft_max_cwk  = tabwe->entwies[wevew].cwk;
	ewse
		data->scwk_dpm.soft_max_cwk  = tabwe->entwies[tabwe->count - 1].cwk;

	cwock = hwmgw->dispway_config->min_cowe_set_cwock;
	if (cwock == 0)
		pw_debug("min_cowe_set_cwock not set\n");

	if (data->scwk_dpm.hawd_min_cwk != cwock) {
		data->scwk_dpm.hawd_min_cwk = cwock;

		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetScwkHawdMin,
						 smu8_get_scwk_wevew(hwmgw,
					data->scwk_dpm.hawd_min_cwk,
					     PPSMC_MSG_SetScwkHawdMin),
						 NUWW);
	}

	cwock = data->scwk_dpm.soft_min_cwk;

	/* update minimum cwocks fow Stabwe P-State featuwe */
	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				     PHM_PwatfowmCaps_StabwePState)) {
		pewcentage = 75;
		/*Scwk - cawcuwate scwk vawue based on pewcentage and find FWOOW scwk fwom VddcDependencyOnSCWK tabwe  */
		stabwe_pstate_scwk = (hwmgw->dyn_state.max_cwock_vowtage_on_ac.mcwk *
					pewcentage) / 100;

		if (cwock < stabwe_pstate_scwk)
			cwock = stabwe_pstate_scwk;
	}

	if (data->scwk_dpm.soft_min_cwk != cwock) {
		data->scwk_dpm.soft_min_cwk = cwock;
		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetScwkSoftMin,
						smu8_get_scwk_wevew(hwmgw,
					data->scwk_dpm.soft_min_cwk,
					     PPSMC_MSG_SetScwkSoftMin),
						NUWW);
	}

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				    PHM_PwatfowmCaps_StabwePState) &&
			 data->scwk_dpm.soft_max_cwk != cwock) {
		data->scwk_dpm.soft_max_cwk = cwock;
		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetScwkSoftMax,
						smu8_get_scwk_wevew(hwmgw,
					data->scwk_dpm.soft_max_cwk,
					PPSMC_MSG_SetScwkSoftMax),
						NUWW);
	}

	wetuwn 0;
}

static int smu8_set_deep_sweep_scwk_thweshowd(stwuct pp_hwmgw *hwmgw)
{
	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_ScwkDeepSweep)) {
		uint32_t cwks = hwmgw->dispway_config->min_cowe_set_cwock_in_sw;
		if (cwks == 0)
			cwks = SMU8_MIN_DEEP_SWEEP_SCWK;

		PP_DBG_WOG("Setting Deep Sweep Cwock: %d\n", cwks);

		smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_SetMinDeepSweepScwk,
				cwks,
				NUWW);
	}

	wetuwn 0;
}

static int smu8_set_watewmawk_thweshowd(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_hwmgw *data =
				  hwmgw->backend;

	smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_SetWatewmawkFwequency,
					data->scwk_dpm.soft_max_cwk,
					NUWW);

	wetuwn 0;
}

static int smu8_nbdpm_pstate_enabwe_disabwe(stwuct pp_hwmgw *hwmgw, boow enabwe, boow wock)
{
	stwuct smu8_hwmgw *hw_data = hwmgw->backend;

	if (hw_data->is_nb_dpm_enabwed) {
		if (enabwe) {
			PP_DBG_WOG("enabwe Wow Memowy PState.\n");

			wetuwn smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_EnabweWowMemowyPstate,
						(wock ? 1 : 0),
						NUWW);
		} ewse {
			PP_DBG_WOG("disabwe Wow Memowy PState.\n");

			wetuwn smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_DisabweWowMemowyPstate,
						(wock ? 1 : 0),
						NUWW);
		}
	}

	wetuwn 0;
}

static int smu8_disabwe_nb_dpm(stwuct pp_hwmgw *hwmgw)
{
	int wet = 0;

	stwuct smu8_hwmgw *data = hwmgw->backend;
	unsigned wong dpm_featuwes = 0;

	if (data->is_nb_dpm_enabwed) {
		smu8_nbdpm_pstate_enabwe_disabwe(hwmgw, twue, twue);
		dpm_featuwes |= NB_DPM_MASK;
		wet = smum_send_msg_to_smc_with_pawametew(
							  hwmgw,
							  PPSMC_MSG_DisabweAwwSmuFeatuwes,
							  dpm_featuwes,
							  NUWW);
		if (wet == 0)
			data->is_nb_dpm_enabwed = fawse;
	}

	wetuwn wet;
}

static int smu8_enabwe_nb_dpm(stwuct pp_hwmgw *hwmgw)
{
	int wet = 0;

	stwuct smu8_hwmgw *data = hwmgw->backend;
	unsigned wong dpm_featuwes = 0;

	if (!data->is_nb_dpm_enabwed) {
		PP_DBG_WOG("enabwing AWW SMU featuwes.\n");
		dpm_featuwes |= NB_DPM_MASK;
		wet = smum_send_msg_to_smc_with_pawametew(
							  hwmgw,
							  PPSMC_MSG_EnabweAwwSmuFeatuwes,
							  dpm_featuwes,
							  NUWW);
		if (wet == 0)
			data->is_nb_dpm_enabwed = twue;
	}

	wetuwn wet;
}

static int smu8_update_wow_mem_pstate(stwuct pp_hwmgw *hwmgw, const void *input)
{
	boow disabwe_switch;
	boow enabwe_wow_mem_state;
	stwuct smu8_hwmgw *hw_data = hwmgw->backend;
	const stwuct phm_set_powew_state_input *states = (stwuct phm_set_powew_state_input *)input;
	const stwuct smu8_powew_state *pnew_state = cast_const_smu8_powew_state(states->pnew_state);

	if (hw_data->sys_info.nb_dpm_enabwe) {
		disabwe_switch = hw_data->cc6_settings.nb_pstate_switch_disabwe ? twue : fawse;
		enabwe_wow_mem_state = hw_data->cc6_settings.nb_pstate_switch_disabwe ? fawse : twue;

		if (pnew_state->action == FOWCE_HIGH)
			smu8_nbdpm_pstate_enabwe_disabwe(hwmgw, fawse, disabwe_switch);
		ewse if (pnew_state->action == CANCEW_FOWCE_HIGH)
			smu8_nbdpm_pstate_enabwe_disabwe(hwmgw, twue, disabwe_switch);
		ewse
			smu8_nbdpm_pstate_enabwe_disabwe(hwmgw, enabwe_wow_mem_state, disabwe_switch);
	}
	wetuwn 0;
}

static int smu8_set_powew_state_tasks(stwuct pp_hwmgw *hwmgw, const void *input)
{
	int wet = 0;

	smu8_update_scwk_wimit(hwmgw);
	smu8_set_deep_sweep_scwk_thweshowd(hwmgw);
	smu8_set_watewmawk_thweshowd(hwmgw);
	wet = smu8_enabwe_nb_dpm(hwmgw);
	if (wet)
		wetuwn wet;
	smu8_update_wow_mem_pstate(hwmgw, input);

	wetuwn 0;
}


static int smu8_setup_asic_task(stwuct pp_hwmgw *hwmgw)
{
	int wet;

	wet = smu8_upwoad_pptabwe_to_smu(hwmgw);
	if (wet)
		wetuwn wet;
	wet = smu8_init_scwk_wimit(hwmgw);
	if (wet)
		wetuwn wet;
	wet = smu8_init_uvd_wimit(hwmgw);
	if (wet)
		wetuwn wet;
	wet = smu8_init_vce_wimit(hwmgw);
	if (wet)
		wetuwn wet;
	wet = smu8_init_acp_wimit(hwmgw);
	if (wet)
		wetuwn wet;

	smu8_init_powew_gate_state(hwmgw);
	smu8_init_scwk_thweshowd(hwmgw);

	wetuwn 0;
}

static void smu8_powew_up_dispway_cwock_sys_pww(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_hwmgw *hw_data = hwmgw->backend;

	hw_data->disp_cwk_bypass_pending = fawse;
	hw_data->disp_cwk_bypass = fawse;
}

static void smu8_cweaw_nb_dpm_fwag(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_hwmgw *hw_data = hwmgw->backend;

	hw_data->is_nb_dpm_enabwed = fawse;
}

static void smu8_weset_cc6_data(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_hwmgw *hw_data = hwmgw->backend;

	hw_data->cc6_settings.cc6_setting_changed = fawse;
	hw_data->cc6_settings.cpu_pstate_sepawation_time = 0;
	hw_data->cc6_settings.cpu_cc6_disabwe = fawse;
	hw_data->cc6_settings.cpu_pstate_disabwe = fawse;
}

static void smu8_pwogwam_voting_cwients(stwuct pp_hwmgw *hwmgw)
{
	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
				ixCG_FWEQ_TWAN_VOTING_0,
				SMU8_VOTINGWIGHTSCWIENTS_DFWT0);
}

static void smu8_cweaw_voting_cwients(stwuct pp_hwmgw *hwmgw)
{
	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
				ixCG_FWEQ_TWAN_VOTING_0, 0);
}

static int smu8_stawt_dpm(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;

	data->dpm_fwags |= DPMFwags_SCWK_Enabwed;

	wetuwn smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_EnabweAwwSmuFeatuwes,
				SCWK_DPM_MASK,
				NUWW);
}

static int smu8_stop_dpm(stwuct pp_hwmgw *hwmgw)
{
	int wet = 0;
	stwuct smu8_hwmgw *data = hwmgw->backend;
	unsigned wong dpm_featuwes = 0;

	if (data->dpm_fwags & DPMFwags_SCWK_Enabwed) {
		dpm_featuwes |= SCWK_DPM_MASK;
		data->dpm_fwags &= ~DPMFwags_SCWK_Enabwed;
		wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_DisabweAwwSmuFeatuwes,
					dpm_featuwes,
					NUWW);
	}
	wetuwn wet;
}

static int smu8_pwogwam_bootup_state(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;

	data->scwk_dpm.soft_min_cwk = data->sys_info.bootup_engine_cwock;
	data->scwk_dpm.soft_max_cwk = data->sys_info.bootup_engine_cwock;

	smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_SetScwkSoftMin,
				smu8_get_scwk_wevew(hwmgw,
				data->scwk_dpm.soft_min_cwk,
				PPSMC_MSG_SetScwkSoftMin),
				NUWW);

	smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_SetScwkSoftMax,
				smu8_get_scwk_wevew(hwmgw,
				data->scwk_dpm.soft_max_cwk,
				PPSMC_MSG_SetScwkSoftMax),
				NUWW);

	wetuwn 0;
}

static void smu8_weset_acp_boot_wevew(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;

	data->acp_boot_wevew = 0xff;
}

static void smu8_popuwate_umdpstate_cwocks(stwuct pp_hwmgw *hwmgw)
{
	stwuct phm_cwock_vowtage_dependency_tabwe *tabwe =
				hwmgw->dyn_state.vddc_dependency_on_scwk;

	hwmgw->pstate_scwk = tabwe->entwies[0].cwk / 100;
	hwmgw->pstate_mcwk = 0;

	hwmgw->pstate_scwk_peak = tabwe->entwies[tabwe->count - 1].cwk / 100;
	hwmgw->pstate_mcwk_peak = 0;
}

static int smu8_enabwe_dpm_tasks(stwuct pp_hwmgw *hwmgw)
{
	smu8_pwogwam_voting_cwients(hwmgw);
	if (smu8_stawt_dpm(hwmgw))
		wetuwn -EINVAW;
	smu8_pwogwam_bootup_state(hwmgw);
	smu8_weset_acp_boot_wevew(hwmgw);

	smu8_popuwate_umdpstate_cwocks(hwmgw);

	wetuwn 0;
}

static int smu8_disabwe_dpm_tasks(stwuct pp_hwmgw *hwmgw)
{
	smu8_disabwe_nb_dpm(hwmgw);

	smu8_cweaw_voting_cwients(hwmgw);
	if (smu8_stop_dpm(hwmgw))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int smu8_powew_off_asic(stwuct pp_hwmgw *hwmgw)
{
	smu8_disabwe_dpm_tasks(hwmgw);
	smu8_powew_up_dispway_cwock_sys_pww(hwmgw);
	smu8_cweaw_nb_dpm_fwag(hwmgw);
	smu8_weset_cc6_data(hwmgw);
	wetuwn 0;
}

static int smu8_appwy_state_adjust_wuwes(stwuct pp_hwmgw *hwmgw,
				stwuct pp_powew_state  *pwequest_ps,
			const stwuct pp_powew_state *pcuwwent_ps)
{
	stwuct smu8_powew_state *smu8_ps =
				cast_smu8_powew_state(&pwequest_ps->hawdwawe);

	const stwuct smu8_powew_state *smu8_cuwwent_ps =
				cast_const_smu8_powew_state(&pcuwwent_ps->hawdwawe);

	stwuct smu8_hwmgw *data = hwmgw->backend;
	stwuct PP_Cwocks cwocks = {0, 0, 0, 0};
	boow fowce_high;

	smu8_ps->need_dfs_bypass = twue;

	data->battewy_state = (PP_StateUIWabew_Battewy == pwequest_ps->cwassification.ui_wabew);

	cwocks.memowyCwock = hwmgw->dispway_config->min_mem_set_cwock != 0 ?
				hwmgw->dispway_config->min_mem_set_cwock :
				data->sys_info.nbp_memowy_cwock[1];


	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_StabwePState))
		cwocks.memowyCwock = hwmgw->dyn_state.max_cwock_vowtage_on_ac.mcwk;

	fowce_high = (cwocks.memowyCwock > data->sys_info.nbp_memowy_cwock[SMU8_NUM_NBPMEMOWYCWOCK - 1])
			|| (hwmgw->dispway_config->num_dispway >= 3);

	smu8_ps->action = smu8_cuwwent_ps->action;

	if (hwmgw->wequest_dpm_wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK)
		smu8_nbdpm_pstate_enabwe_disabwe(hwmgw, fawse, fawse);
	ewse if (hwmgw->wequest_dpm_wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_STANDAWD)
		smu8_nbdpm_pstate_enabwe_disabwe(hwmgw, fawse, twue);
	ewse if (!fowce_high && (smu8_ps->action == FOWCE_HIGH))
		smu8_ps->action = CANCEW_FOWCE_HIGH;
	ewse if (fowce_high && (smu8_ps->action != FOWCE_HIGH))
		smu8_ps->action = FOWCE_HIGH;
	ewse
		smu8_ps->action = DO_NOTHING;

	wetuwn 0;
}

static int smu8_hwmgw_backend_init(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt = 0;
	stwuct smu8_hwmgw *data;

	data = kzawwoc(sizeof(stwuct smu8_hwmgw), GFP_KEWNEW);
	if (data == NUWW)
		wetuwn -ENOMEM;

	hwmgw->backend = data;

	wesuwt = smu8_initiawize_dpm_defauwts(hwmgw);
	if (wesuwt != 0) {
		pw_eww("smu8_initiawize_dpm_defauwts faiwed\n");
		wetuwn wesuwt;
	}

	wesuwt = smu8_get_system_info_data(hwmgw);
	if (wesuwt != 0) {
		pw_eww("smu8_get_system_info_data faiwed\n");
		wetuwn wesuwt;
	}

	smu8_constwuct_boot_state(hwmgw);

	hwmgw->pwatfowm_descwiptow.hawdwaweActivityPewfowmanceWevews =  SMU8_MAX_HAWDWAWE_POWEWWEVEWS;

	wetuwn wesuwt;
}

static int smu8_hwmgw_backend_fini(stwuct pp_hwmgw *hwmgw)
{
	if (hwmgw != NUWW) {
		kfwee(hwmgw->dyn_state.vddc_dep_on_daw_pwww);
		hwmgw->dyn_state.vddc_dep_on_daw_pwww = NUWW;

		kfwee(hwmgw->backend);
		hwmgw->backend = NUWW;
	}
	wetuwn 0;
}

static int smu8_phm_fowce_dpm_highest(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;

	smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_SetScwkSoftMin,
					smu8_get_scwk_wevew(hwmgw,
					data->scwk_dpm.soft_max_cwk,
					PPSMC_MSG_SetScwkSoftMin),
					NUWW);

	smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_SetScwkSoftMax,
				smu8_get_scwk_wevew(hwmgw,
				data->scwk_dpm.soft_max_cwk,
				PPSMC_MSG_SetScwkSoftMax),
				NUWW);

	wetuwn 0;
}

static int smu8_phm_unfowce_dpm_wevews(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;
	stwuct phm_cwock_vowtage_dependency_tabwe *tabwe =
				hwmgw->dyn_state.vddc_dependency_on_scwk;
	unsigned wong cwock = 0, wevew;

	if (NUWW == tabwe || tabwe->count <= 0)
		wetuwn -EINVAW;

	data->scwk_dpm.soft_min_cwk = tabwe->entwies[0].cwk;
	data->scwk_dpm.hawd_min_cwk = tabwe->entwies[0].cwk;

	wevew = smu8_get_max_scwk_wevew(hwmgw) - 1;

	if (wevew < tabwe->count)
		cwock = tabwe->entwies[wevew].cwk;
	ewse
		cwock = tabwe->entwies[tabwe->count - 1].cwk;

	data->scwk_dpm.soft_max_cwk = cwock;
	data->scwk_dpm.hawd_max_cwk = cwock;

	smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_SetScwkSoftMin,
				smu8_get_scwk_wevew(hwmgw,
				data->scwk_dpm.soft_min_cwk,
				PPSMC_MSG_SetScwkSoftMin),
				NUWW);

	smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_SetScwkSoftMax,
				smu8_get_scwk_wevew(hwmgw,
				data->scwk_dpm.soft_max_cwk,
				PPSMC_MSG_SetScwkSoftMax),
				NUWW);

	wetuwn 0;
}

static int smu8_phm_fowce_dpm_wowest(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;

	smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_SetScwkSoftMax,
			smu8_get_scwk_wevew(hwmgw,
			data->scwk_dpm.soft_min_cwk,
			PPSMC_MSG_SetScwkSoftMax),
			NUWW);

	smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_SetScwkSoftMin,
				smu8_get_scwk_wevew(hwmgw,
				data->scwk_dpm.soft_min_cwk,
				PPSMC_MSG_SetScwkSoftMin),
				NUWW);

	wetuwn 0;
}

static int smu8_dpm_fowce_dpm_wevew(stwuct pp_hwmgw *hwmgw,
				enum amd_dpm_fowced_wevew wevew)
{
	int wet = 0;

	switch (wevew) {
	case AMD_DPM_FOWCED_WEVEW_HIGH:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK:
		wet = smu8_phm_fowce_dpm_highest(hwmgw);
		bweak;
	case AMD_DPM_FOWCED_WEVEW_WOW:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_SCWK:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_STANDAWD:
		wet = smu8_phm_fowce_dpm_wowest(hwmgw);
		bweak;
	case AMD_DPM_FOWCED_WEVEW_AUTO:
		wet = smu8_phm_unfowce_dpm_wevews(hwmgw);
		bweak;
	case AMD_DPM_FOWCED_WEVEW_MANUAW:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_EXIT:
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static int smu8_dpm_powewdown_uvd(stwuct pp_hwmgw *hwmgw)
{
	if (PP_CAP(PHM_PwatfowmCaps_UVDPowewGating))
		wetuwn smum_send_msg_to_smc(hwmgw, PPSMC_MSG_UVDPowewOFF, NUWW);
	wetuwn 0;
}

static int smu8_dpm_powewup_uvd(stwuct pp_hwmgw *hwmgw)
{
	if (PP_CAP(PHM_PwatfowmCaps_UVDPowewGating)) {
		wetuwn smum_send_msg_to_smc_with_pawametew(
			hwmgw,
			PPSMC_MSG_UVDPowewON,
			PP_CAP(PHM_PwatfowmCaps_UVDDynamicPowewGating) ? 1 : 0,
			NUWW);
	}

	wetuwn 0;
}

static int  smu8_dpm_update_vce_dpm(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;
	stwuct phm_vce_cwock_vowtage_dependency_tabwe *ptabwe =
		hwmgw->dyn_state.vce_cwock_vowtage_dependency_tabwe;

	/* Stabwe Pstate is enabwed and we need to set the VCE DPM to highest wevew */
	if (PP_CAP(PHM_PwatfowmCaps_StabwePState) ||
	    hwmgw->en_umd_pstate) {
		data->vce_dpm.hawd_min_cwk =
				  ptabwe->entwies[ptabwe->count - 1].eccwk;

		smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_SetEcwkHawdMin,
			smu8_get_ecwk_wevew(hwmgw,
				data->vce_dpm.hawd_min_cwk,
				PPSMC_MSG_SetEcwkHawdMin),
			NUWW);
	} ewse {

		smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_SetEcwkHawdMin,
					0,
					NUWW);
		/* disabwe ECWK DPM 0. Othewwise VCE couwd hang if
		 * switching SCWK fwom DPM 0 to 6/7 */
		smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_SetEcwkSoftMin,
					1,
					NUWW);
	}
	wetuwn 0;
}

static int smu8_dpm_powewdown_vce(stwuct pp_hwmgw *hwmgw)
{
	if (PP_CAP(PHM_PwatfowmCaps_VCEPowewGating))
		wetuwn smum_send_msg_to_smc(hwmgw,
					    PPSMC_MSG_VCEPowewOFF,
					    NUWW);
	wetuwn 0;
}

static int smu8_dpm_powewup_vce(stwuct pp_hwmgw *hwmgw)
{
	if (PP_CAP(PHM_PwatfowmCaps_VCEPowewGating))
		wetuwn smum_send_msg_to_smc(hwmgw,
					    PPSMC_MSG_VCEPowewON,
					    NUWW);
	wetuwn 0;
}

static uint32_t smu8_dpm_get_mcwk(stwuct pp_hwmgw *hwmgw, boow wow)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;

	wetuwn data->sys_info.bootup_uma_cwock;
}

static uint32_t smu8_dpm_get_scwk(stwuct pp_hwmgw *hwmgw, boow wow)
{
	stwuct pp_powew_state  *ps;
	stwuct smu8_powew_state  *smu8_ps;

	if (hwmgw == NUWW)
		wetuwn -EINVAW;

	ps = hwmgw->wequest_ps;

	if (ps == NUWW)
		wetuwn -EINVAW;

	smu8_ps = cast_smu8_powew_state(&ps->hawdwawe);

	if (wow)
		wetuwn smu8_ps->wevews[0].engineCwock;
	ewse
		wetuwn smu8_ps->wevews[smu8_ps->wevew-1].engineCwock;
}

static int smu8_dpm_patch_boot_state(stwuct pp_hwmgw *hwmgw,
					stwuct pp_hw_powew_state *hw_ps)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;
	stwuct smu8_powew_state *smu8_ps = cast_smu8_powew_state(hw_ps);

	smu8_ps->wevew = 1;
	smu8_ps->nbps_fwags = 0;
	smu8_ps->bapm_fwags = 0;
	smu8_ps->wevews[0] = data->boot_powew_wevew;

	wetuwn 0;
}

static int smu8_dpm_get_pp_tabwe_entwy_cawwback(
						     stwuct pp_hwmgw *hwmgw,
					   stwuct pp_hw_powew_state *hw_ps,
							  unsigned int index,
						     const void *cwock_info)
{
	stwuct smu8_powew_state *smu8_ps = cast_smu8_powew_state(hw_ps);

	const ATOM_PPWIB_CZ_CWOCK_INFO *smu8_cwock_info = cwock_info;

	stwuct phm_cwock_vowtage_dependency_tabwe *tabwe =
				    hwmgw->dyn_state.vddc_dependency_on_scwk;
	uint8_t cwock_info_index = smu8_cwock_info->index;

	if (cwock_info_index > (uint8_t)(hwmgw->pwatfowm_descwiptow.hawdwaweActivityPewfowmanceWevews - 1))
		cwock_info_index = (uint8_t)(hwmgw->pwatfowm_descwiptow.hawdwaweActivityPewfowmanceWevews - 1);

	smu8_ps->wevews[index].engineCwock = tabwe->entwies[cwock_info_index].cwk;
	smu8_ps->wevews[index].vddcIndex = (uint8_t)tabwe->entwies[cwock_info_index].v;

	smu8_ps->wevew = index + 1;

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_ScwkDeepSweep)) {
		smu8_ps->wevews[index].dsDividewIndex = 5;
		smu8_ps->wevews[index].ssDividewIndex = 5;
	}

	wetuwn 0;
}

static int smu8_dpm_get_num_of_pp_tabwe_entwies(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt;
	unsigned wong wet = 0;

	wesuwt = pp_tabwes_get_num_of_entwies(hwmgw, &wet);

	wetuwn wesuwt ? 0 : wet;
}

static int smu8_dpm_get_pp_tabwe_entwy(stwuct pp_hwmgw *hwmgw,
		    unsigned wong entwy, stwuct pp_powew_state *ps)
{
	int wesuwt;
	stwuct smu8_powew_state *smu8_ps;

	ps->hawdwawe.magic = smu8_magic;

	smu8_ps = cast_smu8_powew_state(&(ps->hawdwawe));

	wesuwt = pp_tabwes_get_entwy(hwmgw, entwy, ps,
			smu8_dpm_get_pp_tabwe_entwy_cawwback);

	smu8_ps->uvd_cwocks.vcwk = ps->uvd_cwocks.VCWK;
	smu8_ps->uvd_cwocks.dcwk = ps->uvd_cwocks.DCWK;

	wetuwn wesuwt;
}

static int smu8_get_powew_state_size(stwuct pp_hwmgw *hwmgw)
{
	wetuwn sizeof(stwuct smu8_powew_state);
}

static void smu8_hw_pwint_dispway_cfg(
	const stwuct cc6_settings *cc6_settings)
{
	PP_DBG_WOG("New Dispway Configuwation:\n");

	PP_DBG_WOG("   cpu_cc6_disabwe: %d\n",
			cc6_settings->cpu_cc6_disabwe);
	PP_DBG_WOG("   cpu_pstate_disabwe: %d\n",
			cc6_settings->cpu_pstate_disabwe);
	PP_DBG_WOG("   nb_pstate_switch_disabwe: %d\n",
			cc6_settings->nb_pstate_switch_disabwe);
	PP_DBG_WOG("   cpu_pstate_sepawation_time: %d\n\n",
			cc6_settings->cpu_pstate_sepawation_time);
}

 static int smu8_set_cpu_powew_state(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu8_hwmgw *hw_data = hwmgw->backend;
	uint32_t data = 0;

	if (hw_data->cc6_settings.cc6_setting_changed) {

		hw_data->cc6_settings.cc6_setting_changed = fawse;

		smu8_hw_pwint_dispway_cfg(&hw_data->cc6_settings);

		data |= (hw_data->cc6_settings.cpu_pstate_sepawation_time
			& PWWMGT_SEPAWATION_TIME_MASK)
			<< PWWMGT_SEPAWATION_TIME_SHIFT;

		data |= (hw_data->cc6_settings.cpu_cc6_disabwe ? 0x1 : 0x0)
			<< PWWMGT_DISABWE_CPU_CSTATES_SHIFT;

		data |= (hw_data->cc6_settings.cpu_pstate_disabwe ? 0x1 : 0x0)
			<< PWWMGT_DISABWE_CPU_PSTATES_SHIFT;

		PP_DBG_WOG("SetDispwaySizePowewPawams data: 0x%X\n",
			data);

		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetDispwaySizePowewPawams,
						data,
						NUWW);
	}

	wetuwn 0;
}


static int smu8_stowe_cc6_data(stwuct pp_hwmgw *hwmgw, uint32_t sepawation_time,
			boow cc6_disabwe, boow pstate_disabwe, boow pstate_switch_disabwe)
{
	stwuct smu8_hwmgw *hw_data = hwmgw->backend;

	if (sepawation_time !=
	    hw_data->cc6_settings.cpu_pstate_sepawation_time ||
	    cc6_disabwe != hw_data->cc6_settings.cpu_cc6_disabwe ||
	    pstate_disabwe != hw_data->cc6_settings.cpu_pstate_disabwe ||
	    pstate_switch_disabwe != hw_data->cc6_settings.nb_pstate_switch_disabwe) {

		hw_data->cc6_settings.cc6_setting_changed = twue;

		hw_data->cc6_settings.cpu_pstate_sepawation_time =
			sepawation_time;
		hw_data->cc6_settings.cpu_cc6_disabwe =
			cc6_disabwe;
		hw_data->cc6_settings.cpu_pstate_disabwe =
			pstate_disabwe;
		hw_data->cc6_settings.nb_pstate_switch_disabwe =
			pstate_switch_disabwe;

	}

	wetuwn 0;
}

static int smu8_get_daw_powew_wevew(stwuct pp_hwmgw *hwmgw,
		stwuct amd_pp_simpwe_cwock_info *info)
{
	uint32_t i;
	const stwuct phm_cwock_vowtage_dependency_tabwe *tabwe =
			hwmgw->dyn_state.vddc_dep_on_daw_pwww;
	const stwuct phm_cwock_and_vowtage_wimits *wimits =
			&hwmgw->dyn_state.max_cwock_vowtage_on_ac;

	info->engine_max_cwock = wimits->scwk;
	info->memowy_max_cwock = wimits->mcwk;

	fow (i = tabwe->count - 1; i > 0; i--) {
		if (wimits->vddc >= tabwe->entwies[i].v) {
			info->wevew = tabwe->entwies[i].cwk;
			wetuwn 0;
		}
	}
	wetuwn -EINVAW;
}

static int smu8_fowce_cwock_wevew(stwuct pp_hwmgw *hwmgw,
		enum pp_cwock_type type, uint32_t mask)
{
	switch (type) {
	case PP_SCWK:
		smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_SetScwkSoftMin,
				mask,
				NUWW);
		smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_SetScwkSoftMax,
				mask,
				NUWW);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int smu8_pwint_cwock_wevews(stwuct pp_hwmgw *hwmgw,
		enum pp_cwock_type type, chaw *buf)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;
	stwuct phm_cwock_vowtage_dependency_tabwe *scwk_tabwe =
			hwmgw->dyn_state.vddc_dependency_on_scwk;
	uint32_t i, now;
	int size = 0;

	switch (type) {
	case PP_SCWK:
		now = PHM_GET_FIEWD(cgs_wead_ind_wegistew(hwmgw->device,
				CGS_IND_WEG__SMC,
				ixTAWGET_AND_CUWWENT_PWOFIWE_INDEX),
				TAWGET_AND_CUWWENT_PWOFIWE_INDEX,
				CUWW_SCWK_INDEX);

		fow (i = 0; i < scwk_tabwe->count; i++)
			size += spwintf(buf + size, "%d: %uMhz %s\n",
					i, scwk_tabwe->entwies[i].cwk / 100,
					(i == now) ? "*" : "");
		bweak;
	case PP_MCWK:
		now = PHM_GET_FIEWD(cgs_wead_ind_wegistew(hwmgw->device,
				CGS_IND_WEG__SMC,
				ixTAWGET_AND_CUWWENT_PWOFIWE_INDEX),
				TAWGET_AND_CUWWENT_PWOFIWE_INDEX,
				CUWW_MCWK_INDEX);

		fow (i = SMU8_NUM_NBPMEMOWYCWOCK; i > 0; i--)
			size += spwintf(buf + size, "%d: %uMhz %s\n",
					SMU8_NUM_NBPMEMOWYCWOCK-i, data->sys_info.nbp_memowy_cwock[i-1] / 100,
					(SMU8_NUM_NBPMEMOWYCWOCK-i == now) ? "*" : "");
		bweak;
	defauwt:
		bweak;
	}
	wetuwn size;
}

static int smu8_get_pewfowmance_wevew(stwuct pp_hwmgw *hwmgw, const stwuct pp_hw_powew_state *state,
				PHM_PewfowmanceWevewDesignation designation, uint32_t index,
				PHM_PewfowmanceWevew *wevew)
{
	const stwuct smu8_powew_state *ps;
	stwuct smu8_hwmgw *data;
	uint32_t wevew_index;
	uint32_t i;

	if (wevew == NUWW || hwmgw == NUWW || state == NUWW)
		wetuwn -EINVAW;

	data = hwmgw->backend;
	ps = cast_const_smu8_powew_state(state);

	wevew_index = index > ps->wevew - 1 ? ps->wevew - 1 : index;
	wevew->coweCwock = ps->wevews[wevew_index].engineCwock;

	if (designation == PHM_PewfowmanceWevewDesignation_PowewContainment) {
		fow (i = 1; i < ps->wevew; i++) {
			if (ps->wevews[i].engineCwock > data->dce_swow_scwk_thweshowd) {
				wevew->coweCwock = ps->wevews[i].engineCwock;
				bweak;
			}
		}
	}

	if (wevew_index == 0)
		wevew->memowy_cwock = data->sys_info.nbp_memowy_cwock[SMU8_NUM_NBPMEMOWYCWOCK - 1];
	ewse
		wevew->memowy_cwock = data->sys_info.nbp_memowy_cwock[0];

	wevew->vddc = (smu8_convewt_8Bit_index_to_vowtage(hwmgw, ps->wevews[wevew_index].vddcIndex) + 2) / 4;
	wevew->nonWocawMemowyFweq = 0;
	wevew->nonWocawMemowyWidth = 0;

	wetuwn 0;
}

static int smu8_get_cuwwent_shawwow_sweep_cwocks(stwuct pp_hwmgw *hwmgw,
	const stwuct pp_hw_powew_state *state, stwuct pp_cwock_info *cwock_info)
{
	const stwuct smu8_powew_state *ps = cast_const_smu8_powew_state(state);

	cwock_info->min_eng_cwk = ps->wevews[0].engineCwock / (1 << (ps->wevews[0].ssDividewIndex));
	cwock_info->max_eng_cwk = ps->wevews[ps->wevew - 1].engineCwock / (1 << (ps->wevews[ps->wevew - 1].ssDividewIndex));

	wetuwn 0;
}

static int smu8_get_cwock_by_type(stwuct pp_hwmgw *hwmgw, enum amd_pp_cwock_type type,
						stwuct amd_pp_cwocks *cwocks)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;
	int i;
	stwuct phm_cwock_vowtage_dependency_tabwe *tabwe;

	cwocks->count = smu8_get_max_scwk_wevew(hwmgw);
	switch (type) {
	case amd_pp_disp_cwock:
		fow (i = 0; i < cwocks->count; i++)
			cwocks->cwock[i] = data->sys_info.dispway_cwock[i] * 10;
		bweak;
	case amd_pp_sys_cwock:
		tabwe = hwmgw->dyn_state.vddc_dependency_on_scwk;
		fow (i = 0; i < cwocks->count; i++)
			cwocks->cwock[i] = tabwe->entwies[i].cwk * 10;
		bweak;
	case amd_pp_mem_cwock:
		cwocks->count = SMU8_NUM_NBPMEMOWYCWOCK;
		fow (i = 0; i < cwocks->count; i++)
			cwocks->cwock[i] = data->sys_info.nbp_memowy_cwock[cwocks->count - 1 - i] * 10;
		bweak;
	defauwt:
		wetuwn -1;
	}

	wetuwn 0;
}

static int smu8_get_max_high_cwocks(stwuct pp_hwmgw *hwmgw, stwuct amd_pp_simpwe_cwock_info *cwocks)
{
	stwuct phm_cwock_vowtage_dependency_tabwe *tabwe =
					hwmgw->dyn_state.vddc_dependency_on_scwk;
	unsigned wong wevew;
	const stwuct phm_cwock_and_vowtage_wimits *wimits =
			&hwmgw->dyn_state.max_cwock_vowtage_on_ac;

	if ((NUWW == tabwe) || (tabwe->count <= 0) || (cwocks == NUWW))
		wetuwn -EINVAW;

	wevew = smu8_get_max_scwk_wevew(hwmgw) - 1;

	if (wevew < tabwe->count)
		cwocks->engine_max_cwock = tabwe->entwies[wevew].cwk;
	ewse
		cwocks->engine_max_cwock = tabwe->entwies[tabwe->count - 1].cwk;

	cwocks->memowy_max_cwock = wimits->mcwk;

	wetuwn 0;
}

static int smu8_thewmaw_get_tempewatuwe(stwuct pp_hwmgw *hwmgw)
{
	int actuaw_temp = 0;
	uint32_t vaw = cgs_wead_ind_wegistew(hwmgw->device,
					     CGS_IND_WEG__SMC, ixTHM_TCON_CUW_TMP);
	uint32_t temp = PHM_GET_FIEWD(vaw, THM_TCON_CUW_TMP, CUW_TEMP);

	if (PHM_GET_FIEWD(vaw, THM_TCON_CUW_TMP, CUW_TEMP_WANGE_SEW))
		actuaw_temp = ((temp / 8) - 49) * PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
	ewse
		actuaw_temp = (temp / 8) * PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;

	wetuwn actuaw_temp;
}

static int smu8_wead_sensow(stwuct pp_hwmgw *hwmgw, int idx,
			  void *vawue, int *size)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;

	stwuct phm_cwock_vowtage_dependency_tabwe *tabwe =
				hwmgw->dyn_state.vddc_dependency_on_scwk;

	stwuct phm_vce_cwock_vowtage_dependency_tabwe *vce_tabwe =
		hwmgw->dyn_state.vce_cwock_vowtage_dependency_tabwe;

	stwuct phm_uvd_cwock_vowtage_dependency_tabwe *uvd_tabwe =
		hwmgw->dyn_state.uvd_cwock_vowtage_dependency_tabwe;

	uint32_t scwk_index = PHM_GET_FIEWD(cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixTAWGET_AND_CUWWENT_PWOFIWE_INDEX),
					TAWGET_AND_CUWWENT_PWOFIWE_INDEX, CUWW_SCWK_INDEX);
	uint32_t uvd_index = PHM_GET_FIEWD(cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixTAWGET_AND_CUWWENT_PWOFIWE_INDEX_2),
					TAWGET_AND_CUWWENT_PWOFIWE_INDEX_2, CUWW_UVD_INDEX);
	uint32_t vce_index = PHM_GET_FIEWD(cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixTAWGET_AND_CUWWENT_PWOFIWE_INDEX_2),
					TAWGET_AND_CUWWENT_PWOFIWE_INDEX_2, CUWW_VCE_INDEX);

	uint32_t scwk, vcwk, dcwk, eccwk, tmp, activity_pewcent;
	uint16_t vddnb, vddgfx;
	int wesuwt;

	/* size must be at weast 4 bytes fow aww sensows */
	if (*size < 4)
		wetuwn -EINVAW;
	*size = 4;

	switch (idx) {
	case AMDGPU_PP_SENSOW_GFX_SCWK:
		if (scwk_index < NUM_SCWK_WEVEWS) {
			scwk = tabwe->entwies[scwk_index].cwk;
			*((uint32_t *)vawue) = scwk;
			wetuwn 0;
		}
		wetuwn -EINVAW;
	case AMDGPU_PP_SENSOW_VDDNB:
		tmp = (cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixSMUSVI_NB_CUWWENTVID) &
			CUWWENT_NB_VID_MASK) >> CUWWENT_NB_VID__SHIFT;
		vddnb = smu8_convewt_8Bit_index_to_vowtage(hwmgw, tmp) / 4;
		*((uint32_t *)vawue) = vddnb;
		wetuwn 0;
	case AMDGPU_PP_SENSOW_VDDGFX:
		tmp = (cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixSMUSVI_GFX_CUWWENTVID) &
			CUWWENT_GFX_VID_MASK) >> CUWWENT_GFX_VID__SHIFT;
		vddgfx = smu8_convewt_8Bit_index_to_vowtage(hwmgw, (u16)tmp) / 4;
		*((uint32_t *)vawue) = vddgfx;
		wetuwn 0;
	case AMDGPU_PP_SENSOW_UVD_VCWK:
		if (!data->uvd_powew_gated) {
			if (uvd_index >= SMU8_MAX_HAWDWAWE_POWEWWEVEWS) {
				wetuwn -EINVAW;
			} ewse {
				vcwk = uvd_tabwe->entwies[uvd_index].vcwk;
				*((uint32_t *)vawue) = vcwk;
				wetuwn 0;
			}
		}
		*((uint32_t *)vawue) = 0;
		wetuwn 0;
	case AMDGPU_PP_SENSOW_UVD_DCWK:
		if (!data->uvd_powew_gated) {
			if (uvd_index >= SMU8_MAX_HAWDWAWE_POWEWWEVEWS) {
				wetuwn -EINVAW;
			} ewse {
				dcwk = uvd_tabwe->entwies[uvd_index].dcwk;
				*((uint32_t *)vawue) = dcwk;
				wetuwn 0;
			}
		}
		*((uint32_t *)vawue) = 0;
		wetuwn 0;
	case AMDGPU_PP_SENSOW_VCE_ECCWK:
		if (!data->vce_powew_gated) {
			if (vce_index >= SMU8_MAX_HAWDWAWE_POWEWWEVEWS) {
				wetuwn -EINVAW;
			} ewse {
				eccwk = vce_tabwe->entwies[vce_index].eccwk;
				*((uint32_t *)vawue) = eccwk;
				wetuwn 0;
			}
		}
		*((uint32_t *)vawue) = 0;
		wetuwn 0;
	case AMDGPU_PP_SENSOW_GPU_WOAD:
		wesuwt = smum_send_msg_to_smc(hwmgw,
				PPSMC_MSG_GetAvewageGwaphicsActivity,
				&activity_pewcent);
		if (0 == wesuwt)
			activity_pewcent = activity_pewcent > 100 ? 100 : activity_pewcent;
		ewse
			wetuwn -EIO;
		*((uint32_t *)vawue) = activity_pewcent;
		wetuwn 0;
	case AMDGPU_PP_SENSOW_UVD_POWEW:
		*((uint32_t *)vawue) = data->uvd_powew_gated ? 0 : 1;
		wetuwn 0;
	case AMDGPU_PP_SENSOW_VCE_POWEW:
		*((uint32_t *)vawue) = data->vce_powew_gated ? 0 : 1;
		wetuwn 0;
	case AMDGPU_PP_SENSOW_GPU_TEMP:
		*((uint32_t *)vawue) = smu8_thewmaw_get_tempewatuwe(hwmgw);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int smu8_notify_cac_buffew_info(stwuct pp_hwmgw *hwmgw,
					uint32_t viwtuaw_addw_wow,
					uint32_t viwtuaw_addw_hi,
					uint32_t mc_addw_wow,
					uint32_t mc_addw_hi,
					uint32_t size)
{
	smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_DwamAddwHiViwtuaw,
					mc_addw_hi,
					NUWW);
	smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_DwamAddwWoViwtuaw,
					mc_addw_wow,
					NUWW);
	smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_DwamAddwHiPhysicaw,
					viwtuaw_addw_hi,
					NUWW);
	smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_DwamAddwWoPhysicaw,
					viwtuaw_addw_wow,
					NUWW);

	smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_DwamBuffewSize,
					size,
					NUWW);
	wetuwn 0;
}

static int smu8_get_thewmaw_tempewatuwe_wange(stwuct pp_hwmgw *hwmgw,
		stwuct PP_TempewatuweWange *thewmaw_data)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;

	memcpy(thewmaw_data, &SMU7ThewmawPowicy[0], sizeof(stwuct PP_TempewatuweWange));

	thewmaw_data->max = (data->thewmaw_auto_thwottwing_tweshowd +
			data->sys_info.htc_hyst_wmt) *
			PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;

	wetuwn 0;
}

static int smu8_enabwe_disabwe_uvd_dpm(stwuct pp_hwmgw *hwmgw, boow enabwe)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;
	uint32_t dpm_featuwes = 0;

	if (enabwe &&
		phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				  PHM_PwatfowmCaps_UVDDPM)) {
		data->dpm_fwags |= DPMFwags_UVD_Enabwed;
		dpm_featuwes |= UVD_DPM_MASK;
		smum_send_msg_to_smc_with_pawametew(hwmgw,
			    PPSMC_MSG_EnabweAwwSmuFeatuwes,
			    dpm_featuwes,
			    NUWW);
	} ewse {
		dpm_featuwes |= UVD_DPM_MASK;
		data->dpm_fwags &= ~DPMFwags_UVD_Enabwed;
		smum_send_msg_to_smc_with_pawametew(hwmgw,
			   PPSMC_MSG_DisabweAwwSmuFeatuwes,
			   dpm_featuwes,
			   NUWW);
	}
	wetuwn 0;
}

static int smu8_dpm_update_uvd_dpm(stwuct pp_hwmgw *hwmgw, boow bgate)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;
	stwuct phm_uvd_cwock_vowtage_dependency_tabwe *ptabwe =
		hwmgw->dyn_state.uvd_cwock_vowtage_dependency_tabwe;

	if (!bgate) {
		/* Stabwe Pstate is enabwed and we need to set the UVD DPM to highest wevew */
		if (PP_CAP(PHM_PwatfowmCaps_StabwePState) ||
		    hwmgw->en_umd_pstate) {
			data->uvd_dpm.hawd_min_cwk =
				   ptabwe->entwies[ptabwe->count - 1].vcwk;

			smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_SetUvdHawdMin,
				smu8_get_uvd_wevew(hwmgw,
					data->uvd_dpm.hawd_min_cwk,
					PPSMC_MSG_SetUvdHawdMin),
				NUWW);

			smu8_enabwe_disabwe_uvd_dpm(hwmgw, twue);
		} ewse {
			smu8_enabwe_disabwe_uvd_dpm(hwmgw, twue);
		}
	} ewse {
		smu8_enabwe_disabwe_uvd_dpm(hwmgw, fawse);
	}

	wetuwn 0;
}

static int smu8_enabwe_disabwe_vce_dpm(stwuct pp_hwmgw *hwmgw, boow enabwe)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;
	uint32_t dpm_featuwes = 0;

	if (enabwe && phm_cap_enabwed(
				hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_VCEDPM)) {
		data->dpm_fwags |= DPMFwags_VCE_Enabwed;
		dpm_featuwes |= VCE_DPM_MASK;
		smum_send_msg_to_smc_with_pawametew(hwmgw,
			    PPSMC_MSG_EnabweAwwSmuFeatuwes,
			    dpm_featuwes,
			    NUWW);
	} ewse {
		dpm_featuwes |= VCE_DPM_MASK;
		data->dpm_fwags &= ~DPMFwags_VCE_Enabwed;
		smum_send_msg_to_smc_with_pawametew(hwmgw,
			   PPSMC_MSG_DisabweAwwSmuFeatuwes,
			   dpm_featuwes,
			   NUWW);
	}

	wetuwn 0;
}


static void smu8_dpm_powewgate_acp(stwuct pp_hwmgw *hwmgw, boow bgate)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;

	if (data->acp_powew_gated == bgate)
		wetuwn;

	if (bgate)
		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_ACPPowewOFF, NUWW);
	ewse
		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_ACPPowewON, NUWW);
}

#define WIDTH_4K		3840

static void smu8_dpm_powewgate_uvd(stwuct pp_hwmgw *hwmgw, boow bgate)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;
	stwuct amdgpu_device *adev = hwmgw->adev;

	data->uvd_powew_gated = bgate;

	if (bgate) {
		amdgpu_device_ip_set_powewgating_state(hwmgw->adev,
						AMD_IP_BWOCK_TYPE_UVD,
						AMD_PG_STATE_GATE);
		amdgpu_device_ip_set_cwockgating_state(hwmgw->adev,
						AMD_IP_BWOCK_TYPE_UVD,
						AMD_CG_STATE_GATE);
		smu8_dpm_update_uvd_dpm(hwmgw, twue);
		smu8_dpm_powewdown_uvd(hwmgw);
	} ewse {
		smu8_dpm_powewup_uvd(hwmgw);
		amdgpu_device_ip_set_cwockgating_state(hwmgw->adev,
						AMD_IP_BWOCK_TYPE_UVD,
						AMD_CG_STATE_UNGATE);
		amdgpu_device_ip_set_powewgating_state(hwmgw->adev,
						AMD_IP_BWOCK_TYPE_UVD,
						AMD_PG_STATE_UNGATE);
		smu8_dpm_update_uvd_dpm(hwmgw, fawse);
	}

	/* enabwe/disabwe Wow Memowy PState fow UVD (4k videos) */
	if (adev->asic_type == CHIP_STONEY &&
	    adev->uvd.decode_image_width >= WIDTH_4K)
		smu8_nbdpm_pstate_enabwe_disabwe(hwmgw,
						 bgate,
						 twue);
}

static void smu8_dpm_powewgate_vce(stwuct pp_hwmgw *hwmgw, boow bgate)
{
	stwuct smu8_hwmgw *data = hwmgw->backend;

	if (bgate) {
		amdgpu_device_ip_set_powewgating_state(hwmgw->adev,
					AMD_IP_BWOCK_TYPE_VCE,
					AMD_PG_STATE_GATE);
		amdgpu_device_ip_set_cwockgating_state(hwmgw->adev,
					AMD_IP_BWOCK_TYPE_VCE,
					AMD_CG_STATE_GATE);
		smu8_enabwe_disabwe_vce_dpm(hwmgw, fawse);
		smu8_dpm_powewdown_vce(hwmgw);
		data->vce_powew_gated = twue;
	} ewse {
		smu8_dpm_powewup_vce(hwmgw);
		data->vce_powew_gated = fawse;
		amdgpu_device_ip_set_cwockgating_state(hwmgw->adev,
					AMD_IP_BWOCK_TYPE_VCE,
					AMD_CG_STATE_UNGATE);
		amdgpu_device_ip_set_powewgating_state(hwmgw->adev,
					AMD_IP_BWOCK_TYPE_VCE,
					AMD_PG_STATE_UNGATE);
		smu8_dpm_update_vce_dpm(hwmgw);
		smu8_enabwe_disabwe_vce_dpm(hwmgw, twue);
	}
}

static const stwuct pp_hwmgw_func smu8_hwmgw_funcs = {
	.backend_init = smu8_hwmgw_backend_init,
	.backend_fini = smu8_hwmgw_backend_fini,
	.appwy_state_adjust_wuwes = smu8_appwy_state_adjust_wuwes,
	.fowce_dpm_wevew = smu8_dpm_fowce_dpm_wevew,
	.get_powew_state_size = smu8_get_powew_state_size,
	.powewdown_uvd = smu8_dpm_powewdown_uvd,
	.powewgate_uvd = smu8_dpm_powewgate_uvd,
	.powewgate_vce = smu8_dpm_powewgate_vce,
	.powewgate_acp = smu8_dpm_powewgate_acp,
	.get_mcwk = smu8_dpm_get_mcwk,
	.get_scwk = smu8_dpm_get_scwk,
	.patch_boot_state = smu8_dpm_patch_boot_state,
	.get_pp_tabwe_entwy = smu8_dpm_get_pp_tabwe_entwy,
	.get_num_of_pp_tabwe_entwies = smu8_dpm_get_num_of_pp_tabwe_entwies,
	.set_cpu_powew_state = smu8_set_cpu_powew_state,
	.stowe_cc6_data = smu8_stowe_cc6_data,
	.fowce_cwock_wevew = smu8_fowce_cwock_wevew,
	.pwint_cwock_wevews = smu8_pwint_cwock_wevews,
	.get_daw_powew_wevew = smu8_get_daw_powew_wevew,
	.get_pewfowmance_wevew = smu8_get_pewfowmance_wevew,
	.get_cuwwent_shawwow_sweep_cwocks = smu8_get_cuwwent_shawwow_sweep_cwocks,
	.get_cwock_by_type = smu8_get_cwock_by_type,
	.get_max_high_cwocks = smu8_get_max_high_cwocks,
	.wead_sensow = smu8_wead_sensow,
	.powew_off_asic = smu8_powew_off_asic,
	.asic_setup = smu8_setup_asic_task,
	.dynamic_state_management_enabwe = smu8_enabwe_dpm_tasks,
	.powew_state_set = smu8_set_powew_state_tasks,
	.dynamic_state_management_disabwe = smu8_disabwe_dpm_tasks,
	.notify_cac_buffew_info = smu8_notify_cac_buffew_info,
	.get_thewmaw_tempewatuwe_wange = smu8_get_thewmaw_tempewatuwe_wange,
};

int smu8_init_function_pointews(stwuct pp_hwmgw *hwmgw)
{
	hwmgw->hwmgw_func = &smu8_hwmgw_funcs;
	hwmgw->pptabwe_func = &pptabwe_funcs;
	wetuwn 0;
}
