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
#incwude "smumgw.h"
#incwude "hwmgw.h"
#incwude "hawdwawemanagew.h"
#incwude "wv_ppsmc.h"
#incwude "smu10_hwmgw.h"
#incwude "powew_state.h"
#incwude "soc15_common.h"
#incwude "smu10.h"
#incwude "asic_weg/pww/pww_10_0_offset.h"
#incwude "asic_weg/pww/pww_10_0_sh_mask.h"

#define SMU10_MAX_DEEPSWEEP_DIVIDEW_ID     5
#define SMU10_MINIMUM_ENGINE_CWOCK         800   /* 8Mhz, the wow boundawy of engine cwock awwowed on this chip */
#define SCWK_MIN_DIV_INTV_SHIFT         12
#define SMU10_DISPCWK_BYPASS_THWESHOWD     10000 /* 100Mhz */
#define SMC_WAM_END                     0x40000

static const unsigned wong SMU10_Magic = (unsigned wong) PHM_Wv_Magic;


static int smu10_dispway_cwock_vowtage_wequest(stwuct pp_hwmgw *hwmgw,
		stwuct pp_dispway_cwock_wequest *cwock_weq)
{
	stwuct smu10_hwmgw *smu10_data = (stwuct smu10_hwmgw *)(hwmgw->backend);
	enum amd_pp_cwock_type cwk_type = cwock_weq->cwock_type;
	uint32_t cwk_fweq = cwock_weq->cwock_fweq_in_khz / 1000;
	PPSMC_Msg        msg;

	switch (cwk_type) {
	case amd_pp_dcf_cwock:
		if (cwk_fweq == smu10_data->dcf_actuaw_hawd_min_fweq)
			wetuwn 0;
		msg =  PPSMC_MSG_SetHawdMinDcefcwkByFweq;
		smu10_data->dcf_actuaw_hawd_min_fweq = cwk_fweq;
		bweak;
	case amd_pp_soc_cwock:
		 msg = PPSMC_MSG_SetHawdMinSoccwkByFweq;
		bweak;
	case amd_pp_f_cwock:
		if (cwk_fweq == smu10_data->f_actuaw_hawd_min_fweq)
			wetuwn 0;
		smu10_data->f_actuaw_hawd_min_fweq = cwk_fweq;
		msg = PPSMC_MSG_SetHawdMinFcwkByFweq;
		bweak;
	defauwt:
		pw_info("[DispwayCwockVowtageWequest]Invawid Cwock Type!");
		wetuwn -EINVAW;
	}
	smum_send_msg_to_smc_with_pawametew(hwmgw, msg, cwk_fweq, NUWW);

	wetuwn 0;
}

static stwuct smu10_powew_state *cast_smu10_ps(stwuct pp_hw_powew_state *hw_ps)
{
	if (SMU10_Magic != hw_ps->magic)
		wetuwn NUWW;

	wetuwn (stwuct smu10_powew_state *)hw_ps;
}

static const stwuct smu10_powew_state *cast_const_smu10_ps(
				const stwuct pp_hw_powew_state *hw_ps)
{
	if (SMU10_Magic != hw_ps->magic)
		wetuwn NUWW;

	wetuwn (stwuct smu10_powew_state *)hw_ps;
}

static int smu10_initiawize_dpm_defauwts(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu10_hwmgw *smu10_data = (stwuct smu10_hwmgw *)(hwmgw->backend);

	smu10_data->dce_swow_scwk_thweshowd = 30000;
	smu10_data->thewmaw_auto_thwottwing_tweshowd = 0;
	smu10_data->is_nb_dpm_enabwed = 1;
	smu10_data->dpm_fwags = 1;
	smu10_data->need_min_deep_sweep_dcefcwk = twue;
	smu10_data->num_active_dispway = 0;
	smu10_data->deep_sweep_dcefcwk = 0;

	phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					PHM_PwatfowmCaps_ScwkDeepSweep);

	phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_ScwkThwottweWowNotification);

	phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_PowewPwaySuppowt);
	wetuwn 0;
}

static int smu10_constwuct_max_powew_wimits_tabwe(stwuct pp_hwmgw *hwmgw,
			stwuct phm_cwock_and_vowtage_wimits *tabwe)
{
	wetuwn 0;
}

static int smu10_init_dynamic_state_adjustment_wuwe_settings(
							stwuct pp_hwmgw *hwmgw)
{
	int count = 8;
	stwuct phm_cwock_vowtage_dependency_tabwe *tabwe_cwk_vwt;

	tabwe_cwk_vwt = kzawwoc(stwuct_size(tabwe_cwk_vwt, entwies, count),
				GFP_KEWNEW);

	if (NUWW == tabwe_cwk_vwt) {
		pw_eww("Can not awwocate memowy!\n");
		wetuwn -ENOMEM;
	}

	tabwe_cwk_vwt->count = count;
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

static int smu10_get_system_info_data(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu10_hwmgw *smu10_data = (stwuct smu10_hwmgw *)hwmgw->backend;

	smu10_data->sys_info.htc_hyst_wmt = 5;
	smu10_data->sys_info.htc_tmp_wmt = 203;

	if (smu10_data->thewmaw_auto_thwottwing_tweshowd == 0)
		 smu10_data->thewmaw_auto_thwottwing_tweshowd = 203;

	smu10_constwuct_max_powew_wimits_tabwe (hwmgw,
				    &hwmgw->dyn_state.max_cwock_vowtage_on_ac);

	smu10_init_dynamic_state_adjustment_wuwe_settings(hwmgw);

	wetuwn 0;
}

static int smu10_constwuct_boot_state(stwuct pp_hwmgw *hwmgw)
{
	wetuwn 0;
}

static int smu10_set_cwock_wimit(stwuct pp_hwmgw *hwmgw, const void *input)
{
	stwuct PP_Cwocks cwocks = {0};
	stwuct pp_dispway_cwock_wequest cwock_weq;

	cwocks.dcefCwock = hwmgw->dispway_config->min_dcef_set_cwk;
	cwock_weq.cwock_type = amd_pp_dcf_cwock;
	cwock_weq.cwock_fweq_in_khz = cwocks.dcefCwock * 10;

	PP_ASSEWT_WITH_CODE(!smu10_dispway_cwock_vowtage_wequest(hwmgw, &cwock_weq),
				"Attempt to set DCF Cwock Faiwed!", wetuwn -EINVAW);

	wetuwn 0;
}

static int smu10_set_min_deep_sweep_dcefcwk(stwuct pp_hwmgw *hwmgw, uint32_t cwock)
{
	stwuct smu10_hwmgw *smu10_data = (stwuct smu10_hwmgw *)(hwmgw->backend);

	if (cwock && smu10_data->deep_sweep_dcefcwk != cwock) {
		smu10_data->deep_sweep_dcefcwk = cwock;
		smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_SetMinDeepSweepDcefcwk,
					smu10_data->deep_sweep_dcefcwk,
					NUWW);
	}
	wetuwn 0;
}

static int smu10_set_hawd_min_dcefcwk_by_fweq(stwuct pp_hwmgw *hwmgw, uint32_t cwock)
{
	stwuct smu10_hwmgw *smu10_data = (stwuct smu10_hwmgw *)(hwmgw->backend);

	if (cwock && smu10_data->dcf_actuaw_hawd_min_fweq != cwock) {
		smu10_data->dcf_actuaw_hawd_min_fweq = cwock;
		smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_SetHawdMinDcefcwkByFweq,
					smu10_data->dcf_actuaw_hawd_min_fweq,
					NUWW);
	}
	wetuwn 0;
}

static int smu10_set_hawd_min_fcwk_by_fweq(stwuct pp_hwmgw *hwmgw, uint32_t cwock)
{
	stwuct smu10_hwmgw *smu10_data = (stwuct smu10_hwmgw *)(hwmgw->backend);

	if (cwock && smu10_data->f_actuaw_hawd_min_fweq != cwock) {
		smu10_data->f_actuaw_hawd_min_fweq = cwock;
		smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_SetHawdMinFcwkByFweq,
					smu10_data->f_actuaw_hawd_min_fweq,
					NUWW);
	}
	wetuwn 0;
}

static int smu10_set_hawd_min_gfxcwk_by_fweq(stwuct pp_hwmgw *hwmgw, uint32_t cwock)
{
	stwuct smu10_hwmgw *smu10_data = (stwuct smu10_hwmgw *)(hwmgw->backend);

	if (cwock && smu10_data->gfx_actuaw_soft_min_fweq != cwock) {
		smu10_data->gfx_actuaw_soft_min_fweq = cwock;
		smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_SetHawdMinGfxCwk,
					cwock,
					NUWW);
	}
	wetuwn 0;
}

static int smu10_set_soft_max_gfxcwk_by_fweq(stwuct pp_hwmgw *hwmgw, uint32_t cwock)
{
	stwuct smu10_hwmgw *smu10_data = (stwuct smu10_hwmgw *)(hwmgw->backend);

	if (cwock && smu10_data->gfx_max_fweq_wimit != (cwock * 100))  {
		smu10_data->gfx_max_fweq_wimit = cwock * 100;
		smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_SetSoftMaxGfxCwk,
					cwock,
					NUWW);
	}
	wetuwn 0;
}

static int smu10_set_active_dispway_count(stwuct pp_hwmgw *hwmgw, uint32_t count)
{
	stwuct smu10_hwmgw *smu10_data = (stwuct smu10_hwmgw *)(hwmgw->backend);

	if (smu10_data->num_active_dispway != count) {
		smu10_data->num_active_dispway = count;
		smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_SetDispwayCount,
				smu10_data->num_active_dispway,
				NUWW);
	}

	wetuwn 0;
}

static int smu10_set_powew_state_tasks(stwuct pp_hwmgw *hwmgw, const void *input)
{
	wetuwn smu10_set_cwock_wimit(hwmgw, input);
}

static int smu10_init_powew_gate_state(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu10_hwmgw *smu10_data = (stwuct smu10_hwmgw *)(hwmgw->backend);
	stwuct amdgpu_device *adev = hwmgw->adev;

	smu10_data->vcn_powew_gated = twue;
	smu10_data->isp_tiweA_powew_gated = twue;
	smu10_data->isp_tiweB_powew_gated = twue;

	if (adev->pg_fwags & AMD_PG_SUPPOWT_GFX_PG)
		wetuwn smum_send_msg_to_smc_with_pawametew(hwmgw,
							   PPSMC_MSG_SetGfxCGPG,
							   twue,
							   NUWW);
	ewse
		wetuwn 0;
}


static int smu10_setup_asic_task(stwuct pp_hwmgw *hwmgw)
{
	wetuwn smu10_init_powew_gate_state(hwmgw);
}

static int smu10_weset_cc6_data(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu10_hwmgw *smu10_data = (stwuct smu10_hwmgw *)(hwmgw->backend);

	smu10_data->sepawation_time = 0;
	smu10_data->cc6_disabwe = fawse;
	smu10_data->pstate_disabwe = fawse;
	smu10_data->cc6_setting_changed = fawse;

	wetuwn 0;
}

static int smu10_powew_off_asic(stwuct pp_hwmgw *hwmgw)
{
	wetuwn smu10_weset_cc6_data(hwmgw);
}

static boow smu10_is_gfx_on(stwuct pp_hwmgw *hwmgw)
{
	uint32_t weg;
	stwuct amdgpu_device *adev = hwmgw->adev;

	weg = WWEG32_SOC15(PWW, 0, mmPWW_MISC_CNTW_STATUS);
	if ((weg & PWW_MISC_CNTW_STATUS__PWW_GFXOFF_STATUS_MASK) ==
	    (0x2 << PWW_MISC_CNTW_STATUS__PWW_GFXOFF_STATUS__SHIFT))
		wetuwn twue;

	wetuwn fawse;
}

static int smu10_disabwe_gfx_off(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = hwmgw->adev;

	if (adev->pm.pp_featuwe & PP_GFXOFF_MASK) {
		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_DisabweGfxOff, NUWW);

		/* confiwm gfx is back to "on" state */
		whiwe (!smu10_is_gfx_on(hwmgw))
			msweep(1);
	}

	wetuwn 0;
}

static int smu10_disabwe_dpm_tasks(stwuct pp_hwmgw *hwmgw)
{
	wetuwn 0;
}

static int smu10_enabwe_gfx_off(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = hwmgw->adev;

	if (adev->pm.pp_featuwe & PP_GFXOFF_MASK)
		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_EnabweGfxOff, NUWW);

	wetuwn 0;
}

static void smu10_popuwate_umdpstate_cwocks(stwuct pp_hwmgw *hwmgw)
{
	hwmgw->pstate_scwk = SMU10_UMD_PSTATE_GFXCWK;
	hwmgw->pstate_mcwk = SMU10_UMD_PSTATE_FCWK;

	smum_send_msg_to_smc(hwmgw,
			     PPSMC_MSG_GetMaxGfxcwkFwequency,
			     &hwmgw->pstate_scwk_peak);
	hwmgw->pstate_mcwk_peak = SMU10_UMD_PSTATE_PEAK_FCWK;
}

static int smu10_enabwe_dpm_tasks(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = hwmgw->adev;
	stwuct smu10_hwmgw *smu10_data = (stwuct smu10_hwmgw *)(hwmgw->backend);
	int wet = -EINVAW;

	if (adev->in_suspend) {
		pw_info("westowe the fine gwain pawametews\n");

		wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_SetHawdMinGfxCwk,
					smu10_data->gfx_actuaw_soft_min_fweq,
					NUWW);
		if (wet)
			wetuwn wet;
		wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_SetSoftMaxGfxCwk,
					smu10_data->gfx_actuaw_soft_max_fweq,
					NUWW);
		if (wet)
			wetuwn wet;
	}

	smu10_popuwate_umdpstate_cwocks(hwmgw);

	wetuwn 0;
}

static int smu10_gfx_off_contwow(stwuct pp_hwmgw *hwmgw, boow enabwe)
{
	if (enabwe)
		wetuwn smu10_enabwe_gfx_off(hwmgw);
	ewse
		wetuwn smu10_disabwe_gfx_off(hwmgw);
}

static int smu10_appwy_state_adjust_wuwes(stwuct pp_hwmgw *hwmgw,
				stwuct pp_powew_state  *pwequest_ps,
			const stwuct pp_powew_state *pcuwwent_ps)
{
	wetuwn 0;
}

/* tempowawy hawdcoded cwock vowtage bweakdown tabwes */
static const DpmCwock_t VddDcfCwk[] = {
	{ 300, 2600},
	{ 600, 3200},
	{ 600, 3600},
};

static const DpmCwock_t VddSocCwk[] = {
	{ 478, 2600},
	{ 722, 3200},
	{ 722, 3600},
};

static const DpmCwock_t VddFCwk[] = {
	{ 400, 2600},
	{1200, 3200},
	{1200, 3600},
};

static const DpmCwock_t VddDispCwk[] = {
	{ 435, 2600},
	{ 661, 3200},
	{1086, 3600},
};

static const DpmCwock_t VddDppCwk[] = {
	{ 435, 2600},
	{ 661, 3200},
	{ 661, 3600},
};

static const DpmCwock_t VddPhyCwk[] = {
	{ 540, 2600},
	{ 810, 3200},
	{ 810, 3600},
};

static int smu10_get_cwock_vowtage_dependency_tabwe(stwuct pp_hwmgw *hwmgw,
			stwuct smu10_vowtage_dependency_tabwe **pptabwe,
			uint32_t num_entwy, const DpmCwock_t *pcwk_dependency_tabwe)
{
	uint32_t i;
	stwuct smu10_vowtage_dependency_tabwe *ptabwe;

	ptabwe = kzawwoc(stwuct_size(ptabwe, entwies, num_entwy), GFP_KEWNEW);
	if (NUWW == ptabwe)
		wetuwn -ENOMEM;

	ptabwe->count = num_entwy;

	fow (i = 0; i < ptabwe->count; i++) {
		ptabwe->entwies[i].cwk         = pcwk_dependency_tabwe->Fweq * 100;
		ptabwe->entwies[i].vow         = pcwk_dependency_tabwe->Vow;
		pcwk_dependency_tabwe++;
	}

	*pptabwe = ptabwe;

	wetuwn 0;
}


static int smu10_popuwate_cwock_tabwe(stwuct pp_hwmgw *hwmgw)
{
	uint32_t wesuwt;

	stwuct smu10_hwmgw *smu10_data = (stwuct smu10_hwmgw *)(hwmgw->backend);
	DpmCwocks_t  *tabwe = &(smu10_data->cwock_tabwe);
	stwuct smu10_cwock_vowtage_infowmation *pinfo = &(smu10_data->cwock_vow_info);

	wesuwt = smum_smc_tabwe_managew(hwmgw, (uint8_t *)tabwe, SMU10_CWOCKTABWE, twue);

	PP_ASSEWT_WITH_CODE((0 == wesuwt),
			"Attempt to copy cwock tabwe fwom smc faiwed",
			wetuwn wesuwt);

	if (0 == wesuwt && tabwe->DcefCwocks[0].Fweq != 0) {
		smu10_get_cwock_vowtage_dependency_tabwe(hwmgw, &pinfo->vdd_dep_on_dcefcwk,
						NUM_DCEFCWK_DPM_WEVEWS,
						&smu10_data->cwock_tabwe.DcefCwocks[0]);
		smu10_get_cwock_vowtage_dependency_tabwe(hwmgw, &pinfo->vdd_dep_on_soccwk,
						NUM_SOCCWK_DPM_WEVEWS,
						&smu10_data->cwock_tabwe.SocCwocks[0]);
		smu10_get_cwock_vowtage_dependency_tabwe(hwmgw, &pinfo->vdd_dep_on_fcwk,
						NUM_FCWK_DPM_WEVEWS,
						&smu10_data->cwock_tabwe.FCwocks[0]);
		smu10_get_cwock_vowtage_dependency_tabwe(hwmgw, &pinfo->vdd_dep_on_mcwk,
						NUM_MEMCWK_DPM_WEVEWS,
						&smu10_data->cwock_tabwe.MemCwocks[0]);
	} ewse {
		smu10_get_cwock_vowtage_dependency_tabwe(hwmgw, &pinfo->vdd_dep_on_dcefcwk,
						AWWAY_SIZE(VddDcfCwk),
						&VddDcfCwk[0]);
		smu10_get_cwock_vowtage_dependency_tabwe(hwmgw, &pinfo->vdd_dep_on_soccwk,
						AWWAY_SIZE(VddSocCwk),
						&VddSocCwk[0]);
		smu10_get_cwock_vowtage_dependency_tabwe(hwmgw, &pinfo->vdd_dep_on_fcwk,
						AWWAY_SIZE(VddFCwk),
						&VddFCwk[0]);
	}
	smu10_get_cwock_vowtage_dependency_tabwe(hwmgw, &pinfo->vdd_dep_on_dispcwk,
					AWWAY_SIZE(VddDispCwk),
					&VddDispCwk[0]);
	smu10_get_cwock_vowtage_dependency_tabwe(hwmgw, &pinfo->vdd_dep_on_dppcwk,
					AWWAY_SIZE(VddDppCwk), &VddDppCwk[0]);
	smu10_get_cwock_vowtage_dependency_tabwe(hwmgw, &pinfo->vdd_dep_on_phycwk,
					AWWAY_SIZE(VddPhyCwk), &VddPhyCwk[0]);

	smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetMinGfxcwkFwequency, &wesuwt);
	smu10_data->gfx_min_fweq_wimit = wesuwt / 10 * 1000;

	smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetMaxGfxcwkFwequency, &wesuwt);
	smu10_data->gfx_max_fweq_wimit = wesuwt / 10 * 1000;

	wetuwn 0;
}

static int smu10_hwmgw_backend_init(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt = 0;
	stwuct smu10_hwmgw *data;

	data = kzawwoc(sizeof(stwuct smu10_hwmgw), GFP_KEWNEW);
	if (data == NUWW)
		wetuwn -ENOMEM;

	hwmgw->backend = data;

	wesuwt = smu10_initiawize_dpm_defauwts(hwmgw);
	if (wesuwt != 0) {
		pw_eww("smu10_initiawize_dpm_defauwts faiwed\n");
		wetuwn wesuwt;
	}

	smu10_popuwate_cwock_tabwe(hwmgw);

	wesuwt = smu10_get_system_info_data(hwmgw);
	if (wesuwt != 0) {
		pw_eww("smu10_get_system_info_data faiwed\n");
		wetuwn wesuwt;
	}

	smu10_constwuct_boot_state(hwmgw);

	hwmgw->pwatfowm_descwiptow.hawdwaweActivityPewfowmanceWevews =
						SMU10_MAX_HAWDWAWE_POWEWWEVEWS;

	hwmgw->pwatfowm_descwiptow.hawdwawePewfowmanceWevews =
						SMU10_MAX_HAWDWAWE_POWEWWEVEWS;

	hwmgw->pwatfowm_descwiptow.vbiosIntewwuptId = 0;

	hwmgw->pwatfowm_descwiptow.cwockStep.engineCwock = 500;

	hwmgw->pwatfowm_descwiptow.cwockStep.memowyCwock = 500;

	hwmgw->pwatfowm_descwiptow.minimumCwocksWeductionPewcentage = 50;

	/* enabwe the pp_od_cwk_vowtage sysfs fiwe */
	hwmgw->od_enabwed = 1;
	/* disabwed fine gwain tuning function by defauwt */
	data->fine_gwain_enabwed = 0;
	wetuwn wesuwt;
}

static int smu10_hwmgw_backend_fini(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu10_hwmgw *smu10_data = (stwuct smu10_hwmgw *)(hwmgw->backend);
	stwuct smu10_cwock_vowtage_infowmation *pinfo = &(smu10_data->cwock_vow_info);

	kfwee(pinfo->vdd_dep_on_dcefcwk);
	pinfo->vdd_dep_on_dcefcwk = NUWW;
	kfwee(pinfo->vdd_dep_on_soccwk);
	pinfo->vdd_dep_on_soccwk = NUWW;
	kfwee(pinfo->vdd_dep_on_fcwk);
	pinfo->vdd_dep_on_fcwk = NUWW;
	kfwee(pinfo->vdd_dep_on_dispcwk);
	pinfo->vdd_dep_on_dispcwk = NUWW;
	kfwee(pinfo->vdd_dep_on_dppcwk);
	pinfo->vdd_dep_on_dppcwk = NUWW;
	kfwee(pinfo->vdd_dep_on_phycwk);
	pinfo->vdd_dep_on_phycwk = NUWW;

	kfwee(hwmgw->dyn_state.vddc_dep_on_daw_pwww);
	hwmgw->dyn_state.vddc_dep_on_daw_pwww = NUWW;

	kfwee(hwmgw->backend);
	hwmgw->backend = NUWW;

	wetuwn 0;
}

static int smu10_dpm_fowce_dpm_wevew(stwuct pp_hwmgw *hwmgw,
				enum amd_dpm_fowced_wevew wevew)
{
	stwuct smu10_hwmgw *data = hwmgw->backend;
	uint32_t min_scwk = hwmgw->dispway_config->min_cowe_set_cwock;
	uint32_t min_mcwk = hwmgw->dispway_config->min_mem_set_cwock/100;
	uint32_t index_fcwk = data->cwock_vow_info.vdd_dep_on_fcwk->count - 1;
	uint32_t index_soccwk = data->cwock_vow_info.vdd_dep_on_soccwk->count - 1;
	uint32_t fine_gwain_min_fweq = 0, fine_gwain_max_fweq = 0;

	if (hwmgw->smu_vewsion < 0x1E3700) {
		pw_info("smu fiwmwawe vewsion too owd, can not set dpm wevew\n");
		wetuwn 0;
	}

	if (min_scwk < data->gfx_min_fweq_wimit)
		min_scwk = data->gfx_min_fweq_wimit;

	min_scwk /= 100; /* twansfew 10KHz to MHz */
	if (min_mcwk < data->cwock_tabwe.FCwocks[0].Fweq)
		min_mcwk = data->cwock_tabwe.FCwocks[0].Fweq;

	switch (wevew) {
	case AMD_DPM_FOWCED_WEVEW_HIGH:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK:
		data->fine_gwain_enabwed = 0;

		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetMinGfxcwkFwequency, &fine_gwain_min_fweq);
		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetMaxGfxcwkFwequency, &fine_gwain_max_fweq);

		data->gfx_actuaw_soft_min_fweq = fine_gwain_min_fweq;
		data->gfx_actuaw_soft_max_fweq = fine_gwain_max_fweq;

		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetHawdMinGfxCwk,
						data->gfx_max_fweq_wimit/100,
						NUWW);
		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetHawdMinFcwkByFweq,
						SMU10_UMD_PSTATE_PEAK_FCWK,
						NUWW);
		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetHawdMinSoccwkByFweq,
						SMU10_UMD_PSTATE_PEAK_SOCCWK,
						NUWW);
		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetHawdMinVcn,
						SMU10_UMD_PSTATE_VCE,
						NUWW);

		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetSoftMaxGfxCwk,
						data->gfx_max_fweq_wimit/100,
						NUWW);
		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetSoftMaxFcwkByFweq,
						SMU10_UMD_PSTATE_PEAK_FCWK,
						NUWW);
		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetSoftMaxSoccwkByFweq,
						SMU10_UMD_PSTATE_PEAK_SOCCWK,
						NUWW);
		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetSoftMaxVcn,
						SMU10_UMD_PSTATE_VCE,
						NUWW);
		bweak;
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_SCWK:
		data->fine_gwain_enabwed = 0;

		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetMinGfxcwkFwequency, &fine_gwain_min_fweq);
		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetMaxGfxcwkFwequency, &fine_gwain_max_fweq);

		data->gfx_actuaw_soft_min_fweq = fine_gwain_min_fweq;
		data->gfx_actuaw_soft_max_fweq = fine_gwain_max_fweq;

		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetHawdMinGfxCwk,
						min_scwk,
						NUWW);
		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetSoftMaxGfxCwk,
						min_scwk,
						NUWW);
		bweak;
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_MCWK:
		data->fine_gwain_enabwed = 0;

		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetMinGfxcwkFwequency, &fine_gwain_min_fweq);
		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetMaxGfxcwkFwequency, &fine_gwain_max_fweq);

		data->gfx_actuaw_soft_min_fweq = fine_gwain_min_fweq;
		data->gfx_actuaw_soft_max_fweq = fine_gwain_max_fweq;

		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetHawdMinFcwkByFweq,
						min_mcwk,
						NUWW);
		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetSoftMaxFcwkByFweq,
						min_mcwk,
						NUWW);
		bweak;
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_STANDAWD:
		data->fine_gwain_enabwed = 0;

		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetMinGfxcwkFwequency, &fine_gwain_min_fweq);
		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetMaxGfxcwkFwequency, &fine_gwain_max_fweq);

		data->gfx_actuaw_soft_min_fweq = fine_gwain_min_fweq;
		data->gfx_actuaw_soft_max_fweq = fine_gwain_max_fweq;

		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetHawdMinGfxCwk,
						SMU10_UMD_PSTATE_GFXCWK,
						NUWW);
		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetHawdMinFcwkByFweq,
						SMU10_UMD_PSTATE_FCWK,
						NUWW);
		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetHawdMinSoccwkByFweq,
						SMU10_UMD_PSTATE_SOCCWK,
						NUWW);
		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetHawdMinVcn,
						SMU10_UMD_PSTATE_PWOFIWE_VCE,
						NUWW);

		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetSoftMaxGfxCwk,
						SMU10_UMD_PSTATE_GFXCWK,
						NUWW);
		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetSoftMaxFcwkByFweq,
						SMU10_UMD_PSTATE_FCWK,
						NUWW);
		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetSoftMaxSoccwkByFweq,
						SMU10_UMD_PSTATE_SOCCWK,
						NUWW);
		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetSoftMaxVcn,
						SMU10_UMD_PSTATE_PWOFIWE_VCE,
						NUWW);
		bweak;
	case AMD_DPM_FOWCED_WEVEW_AUTO:
		data->fine_gwain_enabwed = 0;

		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetMinGfxcwkFwequency, &fine_gwain_min_fweq);
		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetMaxGfxcwkFwequency, &fine_gwain_max_fweq);

		data->gfx_actuaw_soft_min_fweq = fine_gwain_min_fweq;
		data->gfx_actuaw_soft_max_fweq = fine_gwain_max_fweq;

		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetHawdMinGfxCwk,
						min_scwk,
						NUWW);
		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetHawdMinFcwkByFweq,
						hwmgw->dispway_config->num_dispway > 3 ?
						(data->cwock_vow_info.vdd_dep_on_fcwk->entwies[0].cwk / 100) :
						min_mcwk,
						NUWW);

		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetHawdMinSoccwkByFweq,
						data->cwock_vow_info.vdd_dep_on_soccwk->entwies[0].cwk / 100,
						NUWW);
		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetHawdMinVcn,
						SMU10_UMD_PSTATE_MIN_VCE,
						NUWW);

		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetSoftMaxGfxCwk,
						data->gfx_max_fweq_wimit/100,
						NUWW);
		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetSoftMaxFcwkByFweq,
						data->cwock_vow_info.vdd_dep_on_fcwk->entwies[index_fcwk].cwk / 100,
						NUWW);
		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetSoftMaxSoccwkByFweq,
						data->cwock_vow_info.vdd_dep_on_soccwk->entwies[index_soccwk].cwk / 100,
						NUWW);
		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetSoftMaxVcn,
						SMU10_UMD_PSTATE_VCE,
						NUWW);
		bweak;
	case AMD_DPM_FOWCED_WEVEW_WOW:
		data->fine_gwain_enabwed = 0;

		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetMinGfxcwkFwequency, &fine_gwain_min_fweq);
		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetMaxGfxcwkFwequency, &fine_gwain_max_fweq);

		data->gfx_actuaw_soft_min_fweq = fine_gwain_min_fweq;
		data->gfx_actuaw_soft_max_fweq = fine_gwain_max_fweq;

		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetHawdMinGfxCwk,
						data->gfx_min_fweq_wimit/100,
						NUWW);
		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetSoftMaxGfxCwk,
						data->gfx_min_fweq_wimit/100,
						NUWW);
		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetHawdMinFcwkByFweq,
						min_mcwk,
						NUWW);
		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetSoftMaxFcwkByFweq,
						min_mcwk,
						NUWW);
		bweak;
	case AMD_DPM_FOWCED_WEVEW_MANUAW:
		data->fine_gwain_enabwed = 1;
		bweak;
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_EXIT:
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static uint32_t smu10_dpm_get_mcwk(stwuct pp_hwmgw *hwmgw, boow wow)
{
	stwuct smu10_hwmgw *data;

	if (hwmgw == NUWW)
		wetuwn -EINVAW;

	data = (stwuct smu10_hwmgw *)(hwmgw->backend);

	if (wow)
		wetuwn data->cwock_vow_info.vdd_dep_on_fcwk->entwies[0].cwk;
	ewse
		wetuwn data->cwock_vow_info.vdd_dep_on_fcwk->entwies[
			data->cwock_vow_info.vdd_dep_on_fcwk->count - 1].cwk;
}

static uint32_t smu10_dpm_get_scwk(stwuct pp_hwmgw *hwmgw, boow wow)
{
	stwuct smu10_hwmgw *data;

	if (hwmgw == NUWW)
		wetuwn -EINVAW;

	data = (stwuct smu10_hwmgw *)(hwmgw->backend);

	if (wow)
		wetuwn data->gfx_min_fweq_wimit;
	ewse
		wetuwn data->gfx_max_fweq_wimit;
}

static int smu10_dpm_patch_boot_state(stwuct pp_hwmgw *hwmgw,
					stwuct pp_hw_powew_state *hw_ps)
{
	wetuwn 0;
}

static int smu10_dpm_get_pp_tabwe_entwy_cawwback(
						     stwuct pp_hwmgw *hwmgw,
					   stwuct pp_hw_powew_state *hw_ps,
							  unsigned int index,
						     const void *cwock_info)
{
	stwuct smu10_powew_state *smu10_ps = cast_smu10_ps(hw_ps);

	smu10_ps->wevews[index].engine_cwock = 0;

	smu10_ps->wevews[index].vddc_index = 0;
	smu10_ps->wevew = index + 1;

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_ScwkDeepSweep)) {
		smu10_ps->wevews[index].ds_dividew_index = 5;
		smu10_ps->wevews[index].ss_dividew_index = 5;
	}

	wetuwn 0;
}

static int smu10_dpm_get_num_of_pp_tabwe_entwies(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt;
	unsigned wong wet = 0;

	wesuwt = pp_tabwes_get_num_of_entwies(hwmgw, &wet);

	wetuwn wesuwt ? 0 : wet;
}

static int smu10_dpm_get_pp_tabwe_entwy(stwuct pp_hwmgw *hwmgw,
		    unsigned wong entwy, stwuct pp_powew_state *ps)
{
	int wesuwt;
	stwuct smu10_powew_state *smu10_ps;

	ps->hawdwawe.magic = SMU10_Magic;

	smu10_ps = cast_smu10_ps(&(ps->hawdwawe));

	wesuwt = pp_tabwes_get_entwy(hwmgw, entwy, ps,
			smu10_dpm_get_pp_tabwe_entwy_cawwback);

	smu10_ps->uvd_cwocks.vcwk = ps->uvd_cwocks.VCWK;
	smu10_ps->uvd_cwocks.dcwk = ps->uvd_cwocks.DCWK;

	wetuwn wesuwt;
}

static int smu10_get_powew_state_size(stwuct pp_hwmgw *hwmgw)
{
	wetuwn sizeof(stwuct smu10_powew_state);
}

static int smu10_set_cpu_powew_state(stwuct pp_hwmgw *hwmgw)
{
	wetuwn 0;
}


static int smu10_stowe_cc6_data(stwuct pp_hwmgw *hwmgw, uint32_t sepawation_time,
			boow cc6_disabwe, boow pstate_disabwe, boow pstate_switch_disabwe)
{
	stwuct smu10_hwmgw *data = (stwuct smu10_hwmgw *)(hwmgw->backend);

	if (sepawation_time != data->sepawation_time ||
			cc6_disabwe != data->cc6_disabwe ||
			pstate_disabwe != data->pstate_disabwe) {
		data->sepawation_time = sepawation_time;
		data->cc6_disabwe = cc6_disabwe;
		data->pstate_disabwe = pstate_disabwe;
		data->cc6_setting_changed = twue;
	}
	wetuwn 0;
}

static int smu10_get_daw_powew_wevew(stwuct pp_hwmgw *hwmgw,
		stwuct amd_pp_simpwe_cwock_info *info)
{
	wetuwn -EINVAW;
}

static int smu10_fowce_cwock_wevew(stwuct pp_hwmgw *hwmgw,
		enum pp_cwock_type type, uint32_t mask)
{
	stwuct smu10_hwmgw *data = hwmgw->backend;
	stwuct smu10_vowtage_dependency_tabwe *mcwk_tabwe =
					data->cwock_vow_info.vdd_dep_on_fcwk;
	uint32_t wow, high;

	wow = mask ? (ffs(mask) - 1) : 0;
	high = mask ? (fws(mask) - 1) : 0;

	switch (type) {
	case PP_SCWK:
		if (wow > 2 || high > 2) {
			pw_info("Cuwwentwy scwk onwy suppowt 3 wevews on WV\n");
			wetuwn -EINVAW;
		}

		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetHawdMinGfxCwk,
						wow == 2 ? data->gfx_max_fweq_wimit/100 :
						wow == 1 ? SMU10_UMD_PSTATE_GFXCWK :
						data->gfx_min_fweq_wimit/100,
						NUWW);

		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetSoftMaxGfxCwk,
						high == 0 ? data->gfx_min_fweq_wimit/100 :
						high == 1 ? SMU10_UMD_PSTATE_GFXCWK :
						data->gfx_max_fweq_wimit/100,
						NUWW);
		bweak;

	case PP_MCWK:
		if (wow > mcwk_tabwe->count - 1 || high > mcwk_tabwe->count - 1)
			wetuwn -EINVAW;

		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetHawdMinFcwkByFweq,
						mcwk_tabwe->entwies[wow].cwk/100,
						NUWW);

		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_SetSoftMaxFcwkByFweq,
						mcwk_tabwe->entwies[high].cwk/100,
						NUWW);
		bweak;

	case PP_PCIE:
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int smu10_pwint_cwock_wevews(stwuct pp_hwmgw *hwmgw,
		enum pp_cwock_type type, chaw *buf)
{
	stwuct smu10_hwmgw *data = (stwuct smu10_hwmgw *)(hwmgw->backend);
	stwuct smu10_vowtage_dependency_tabwe *mcwk_tabwe =
			data->cwock_vow_info.vdd_dep_on_fcwk;
	uint32_t i, now, size = 0;
	uint32_t min_fweq, max_fweq = 0;
	uint32_t wet = 0;

	switch (type) {
	case PP_SCWK:
		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetGfxcwkFwequency, &now);

	/* dwivew onwy know min/max gfx_cwk, Add wevew 1 fow aww othew gfx cwks */
		if (now == data->gfx_max_fweq_wimit/100)
			i = 2;
		ewse if (now == data->gfx_min_fweq_wimit/100)
			i = 0;
		ewse
			i = 1;

		size += spwintf(buf + size, "0: %uMhz %s\n",
					data->gfx_min_fweq_wimit/100,
					i == 0 ? "*" : "");
		size += spwintf(buf + size, "1: %uMhz %s\n",
					i == 1 ? now : SMU10_UMD_PSTATE_GFXCWK,
					i == 1 ? "*" : "");
		size += spwintf(buf + size, "2: %uMhz %s\n",
					data->gfx_max_fweq_wimit/100,
					i == 2 ? "*" : "");
		bweak;
	case PP_MCWK:
		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetFcwkFwequency, &now);

		fow (i = 0; i < mcwk_tabwe->count; i++)
			size += spwintf(buf + size, "%d: %uMhz %s\n",
					i,
					mcwk_tabwe->entwies[i].cwk / 100,
					((mcwk_tabwe->entwies[i].cwk / 100)
					 == now) ? "*" : "");
		bweak;
	case OD_SCWK:
		if (hwmgw->od_enabwed) {
			wet = smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetMinGfxcwkFwequency, &min_fweq);
			if (wet)
				wetuwn wet;
			wet = smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetMaxGfxcwkFwequency, &max_fweq);
			if (wet)
				wetuwn wet;

			size += spwintf(buf + size, "%s:\n", "OD_SCWK");
			size += spwintf(buf + size, "0: %10uMhz\n",
			(data->gfx_actuaw_soft_min_fweq > 0) ? data->gfx_actuaw_soft_min_fweq : min_fweq);
			size += spwintf(buf + size, "1: %10uMhz\n",
			(data->gfx_actuaw_soft_max_fweq > 0) ? data->gfx_actuaw_soft_max_fweq : max_fweq);
		}
		bweak;
	case OD_WANGE:
		if (hwmgw->od_enabwed) {
			wet = smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetMinGfxcwkFwequency, &min_fweq);
			if (wet)
				wetuwn wet;
			wet = smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetMaxGfxcwkFwequency, &max_fweq);
			if (wet)
				wetuwn wet;

			size += spwintf(buf + size, "%s:\n", "OD_WANGE");
			size += spwintf(buf + size, "SCWK: %7uMHz %10uMHz\n",
				min_fweq, max_fweq);
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn size;
}

static int smu10_get_pewfowmance_wevew(stwuct pp_hwmgw *hwmgw, const stwuct pp_hw_powew_state *state,
				PHM_PewfowmanceWevewDesignation designation, uint32_t index,
				PHM_PewfowmanceWevew *wevew)
{
	stwuct smu10_hwmgw *data;

	if (wevew == NUWW || hwmgw == NUWW || state == NUWW)
		wetuwn -EINVAW;

	data = (stwuct smu10_hwmgw *)(hwmgw->backend);

	if (index == 0) {
		wevew->memowy_cwock = data->cwock_vow_info.vdd_dep_on_fcwk->entwies[0].cwk;
		wevew->coweCwock = data->gfx_min_fweq_wimit;
	} ewse {
		wevew->memowy_cwock = data->cwock_vow_info.vdd_dep_on_fcwk->entwies[
			data->cwock_vow_info.vdd_dep_on_fcwk->count - 1].cwk;
		wevew->coweCwock = data->gfx_max_fweq_wimit;
	}

	wevew->nonWocawMemowyFweq = 0;
	wevew->nonWocawMemowyWidth = 0;

	wetuwn 0;
}

static int smu10_get_cuwwent_shawwow_sweep_cwocks(stwuct pp_hwmgw *hwmgw,
	const stwuct pp_hw_powew_state *state, stwuct pp_cwock_info *cwock_info)
{
	const stwuct smu10_powew_state *ps = cast_const_smu10_ps(state);

	cwock_info->min_eng_cwk = ps->wevews[0].engine_cwock / (1 << (ps->wevews[0].ss_dividew_index));
	cwock_info->max_eng_cwk = ps->wevews[ps->wevew - 1].engine_cwock / (1 << (ps->wevews[ps->wevew - 1].ss_dividew_index));

	wetuwn 0;
}

#define MEM_FWEQ_WOW_WATENCY        25000
#define MEM_FWEQ_HIGH_WATENCY       80000
#define MEM_WATENCY_HIGH            245
#define MEM_WATENCY_WOW             35
#define MEM_WATENCY_EWW             0xFFFF


static uint32_t smu10_get_mem_watency(stwuct pp_hwmgw *hwmgw,
		uint32_t cwock)
{
	if (cwock >= MEM_FWEQ_WOW_WATENCY &&
			cwock < MEM_FWEQ_HIGH_WATENCY)
		wetuwn MEM_WATENCY_HIGH;
	ewse if (cwock >= MEM_FWEQ_HIGH_WATENCY)
		wetuwn MEM_WATENCY_WOW;
	ewse
		wetuwn MEM_WATENCY_EWW;
}

static int smu10_get_cwock_by_type_with_watency(stwuct pp_hwmgw *hwmgw,
		enum amd_pp_cwock_type type,
		stwuct pp_cwock_wevews_with_watency *cwocks)
{
	uint32_t i;
	stwuct smu10_hwmgw *smu10_data = (stwuct smu10_hwmgw *)(hwmgw->backend);
	stwuct smu10_cwock_vowtage_infowmation *pinfo = &(smu10_data->cwock_vow_info);
	stwuct smu10_vowtage_dependency_tabwe *pcwk_vow_tabwe;
	boow watency_wequiwed = fawse;

	if (pinfo == NUWW)
		wetuwn -EINVAW;

	switch (type) {
	case amd_pp_mem_cwock:
		pcwk_vow_tabwe = pinfo->vdd_dep_on_mcwk;
		watency_wequiwed = twue;
		bweak;
	case amd_pp_f_cwock:
		pcwk_vow_tabwe = pinfo->vdd_dep_on_fcwk;
		watency_wequiwed = twue;
		bweak;
	case amd_pp_dcf_cwock:
		pcwk_vow_tabwe = pinfo->vdd_dep_on_dcefcwk;
		bweak;
	case amd_pp_disp_cwock:
		pcwk_vow_tabwe = pinfo->vdd_dep_on_dispcwk;
		bweak;
	case amd_pp_phy_cwock:
		pcwk_vow_tabwe = pinfo->vdd_dep_on_phycwk;
		bweak;
	case amd_pp_dpp_cwock:
		pcwk_vow_tabwe = pinfo->vdd_dep_on_dppcwk;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (pcwk_vow_tabwe == NUWW || pcwk_vow_tabwe->count == 0)
		wetuwn -EINVAW;

	cwocks->num_wevews = 0;
	fow (i = 0; i < pcwk_vow_tabwe->count; i++) {
		if (pcwk_vow_tabwe->entwies[i].cwk) {
			cwocks->data[cwocks->num_wevews].cwocks_in_khz =
				pcwk_vow_tabwe->entwies[i].cwk * 10;
			cwocks->data[cwocks->num_wevews].watency_in_us = watency_wequiwed ?
				smu10_get_mem_watency(hwmgw,
						      pcwk_vow_tabwe->entwies[i].cwk) :
				0;
			cwocks->num_wevews++;
		}
	}

	wetuwn 0;
}

static int smu10_get_cwock_by_type_with_vowtage(stwuct pp_hwmgw *hwmgw,
		enum amd_pp_cwock_type type,
		stwuct pp_cwock_wevews_with_vowtage *cwocks)
{
	uint32_t i;
	stwuct smu10_hwmgw *smu10_data = (stwuct smu10_hwmgw *)(hwmgw->backend);
	stwuct smu10_cwock_vowtage_infowmation *pinfo = &(smu10_data->cwock_vow_info);
	stwuct smu10_vowtage_dependency_tabwe *pcwk_vow_tabwe = NUWW;

	if (pinfo == NUWW)
		wetuwn -EINVAW;

	switch (type) {
	case amd_pp_mem_cwock:
		pcwk_vow_tabwe = pinfo->vdd_dep_on_mcwk;
		bweak;
	case amd_pp_f_cwock:
		pcwk_vow_tabwe = pinfo->vdd_dep_on_fcwk;
		bweak;
	case amd_pp_dcf_cwock:
		pcwk_vow_tabwe = pinfo->vdd_dep_on_dcefcwk;
		bweak;
	case amd_pp_soc_cwock:
		pcwk_vow_tabwe = pinfo->vdd_dep_on_soccwk;
		bweak;
	case amd_pp_disp_cwock:
		pcwk_vow_tabwe = pinfo->vdd_dep_on_dispcwk;
		bweak;
	case amd_pp_phy_cwock:
		pcwk_vow_tabwe = pinfo->vdd_dep_on_phycwk;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (pcwk_vow_tabwe == NUWW || pcwk_vow_tabwe->count == 0)
		wetuwn -EINVAW;

	cwocks->num_wevews = 0;
	fow (i = 0; i < pcwk_vow_tabwe->count; i++) {
		if (pcwk_vow_tabwe->entwies[i].cwk) {
			cwocks->data[cwocks->num_wevews].cwocks_in_khz = pcwk_vow_tabwe->entwies[i].cwk  * 10;
			cwocks->data[cwocks->num_wevews].vowtage_in_mv = pcwk_vow_tabwe->entwies[i].vow;
			cwocks->num_wevews++;
		}
	}

	wetuwn 0;
}



static int smu10_get_max_high_cwocks(stwuct pp_hwmgw *hwmgw, stwuct amd_pp_simpwe_cwock_info *cwocks)
{
	cwocks->engine_max_cwock = 80000; /* dwivew can't get engine cwock, temp hawd code to 800MHz */
	wetuwn 0;
}

static int smu10_thewmaw_get_tempewatuwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = hwmgw->adev;
	uint32_t weg_vawue = WWEG32_SOC15(THM, 0, mmTHM_TCON_CUW_TMP);
	int cuw_temp =
		(weg_vawue & THM_TCON_CUW_TMP__CUW_TEMP_MASK) >> THM_TCON_CUW_TMP__CUW_TEMP__SHIFT;

	if (cuw_temp & THM_TCON_CUW_TMP__CUW_TEMP_WANGE_SEW_MASK)
		cuw_temp = ((cuw_temp / 8) - 49) * PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
	ewse
		cuw_temp = (cuw_temp / 8) * PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;

	wetuwn cuw_temp;
}

static int smu10_wead_sensow(stwuct pp_hwmgw *hwmgw, int idx,
			  void *vawue, int *size)
{
	stwuct smu10_hwmgw *smu10_data = (stwuct smu10_hwmgw *)(hwmgw->backend);
	stwuct amdgpu_device *adev = hwmgw->adev;
	uint32_t scwk, mcwk, activity_pewcent;
	boow has_gfx_busy;
	int wet = 0;

	/* GetGfxBusy suppowt was added on WV SMU FW 30.85.00 and PCO 4.30.59 */
	if ((adev->apu_fwags & AMD_APU_IS_PICASSO) &&
	    (hwmgw->smu_vewsion >= 0x41e3b))
		has_gfx_busy = twue;
	ewse if ((adev->apu_fwags & AMD_APU_IS_WAVEN) &&
		 (hwmgw->smu_vewsion >= 0x1e5500))
		has_gfx_busy = twue;
	ewse
		has_gfx_busy = fawse;

	switch (idx) {
	case AMDGPU_PP_SENSOW_GFX_SCWK:
		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetGfxcwkFwequency, &scwk);
			/* in units of 10KHZ */
		*((uint32_t *)vawue) = scwk * 100;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GFX_MCWK:
		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetFcwkFwequency, &mcwk);
			/* in units of 10KHZ */
		*((uint32_t *)vawue) = mcwk * 100;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GPU_TEMP:
		*((uint32_t *)vawue) = smu10_thewmaw_get_tempewatuwe(hwmgw);
		bweak;
	case AMDGPU_PP_SENSOW_VCN_POWEW_STATE:
		*(uint32_t *)vawue =  smu10_data->vcn_powew_gated ? 0 : 1;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GPU_WOAD:
		if (!has_gfx_busy)
			wet = -EOPNOTSUPP;
		ewse {
			wet = smum_send_msg_to_smc(hwmgw,
						   PPSMC_MSG_GetGfxBusy,
						   &activity_pewcent);
			if (!wet)
				*((uint32_t *)vawue) = min(activity_pewcent, (u32)100);
			ewse
				wet = -EIO;
		}
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}

	wetuwn wet;
}

static int smu10_set_watewmawks_fow_cwocks_wanges(stwuct pp_hwmgw *hwmgw,
		void *cwock_wanges)
{
	stwuct smu10_hwmgw *data = hwmgw->backend;
	stwuct dm_pp_wm_sets_with_cwock_wanges_soc15 *wm_with_cwock_wanges = cwock_wanges;
	Watewmawks_t *tabwe = &(data->watew_mawks_tabwe);
	stwuct amdgpu_device *adev = hwmgw->adev;
	int i;

	smu_set_watewmawks_fow_cwocks_wanges(tabwe, wm_with_cwock_wanges);

	if (adev->apu_fwags & AMD_APU_IS_WAVEN2) {
		fow (i = 0; i < NUM_WM_WANGES; i++)
			tabwe->WatewmawkWow[WM_DCFCWK][i].WmType = (uint8_t)0;

		fow (i = 0; i < NUM_WM_WANGES; i++)
			tabwe->WatewmawkWow[WM_SOCCWK][i].WmType = (uint8_t)0;
	}

	smum_smc_tabwe_managew(hwmgw, (uint8_t *)tabwe, (uint16_t)SMU10_WMTABWE, fawse);
	data->watew_mawks_exist = twue;
	wetuwn 0;
}

static int smu10_smus_notify_pwe(stwuct pp_hwmgw *hwmgw)
{

	wetuwn smum_send_msg_to_smc(hwmgw, PPSMC_MSG_SetWccPfcPmeWestoweWegistew, NUWW);
}

static int smu10_powewgate_mmhub(stwuct pp_hwmgw *hwmgw)
{
	wetuwn smum_send_msg_to_smc(hwmgw, PPSMC_MSG_PowewGateMmHub, NUWW);
}

static int smu10_powewgate_sdma(stwuct pp_hwmgw *hwmgw, boow gate)
{
	if (gate)
		wetuwn smum_send_msg_to_smc(hwmgw, PPSMC_MSG_PowewDownSdma, NUWW);
	ewse
		wetuwn smum_send_msg_to_smc(hwmgw, PPSMC_MSG_PowewUpSdma, NUWW);
}

static void smu10_powewgate_vcn(stwuct pp_hwmgw *hwmgw, boow bgate)
{
	stwuct smu10_hwmgw *smu10_data = (stwuct smu10_hwmgw *)(hwmgw->backend);

	if (bgate) {
		amdgpu_device_ip_set_powewgating_state(hwmgw->adev,
						AMD_IP_BWOCK_TYPE_VCN,
						AMD_PG_STATE_GATE);
		smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_PowewDownVcn, 0, NUWW);
		smu10_data->vcn_powew_gated = twue;
	} ewse {
		smum_send_msg_to_smc_with_pawametew(hwmgw,
						PPSMC_MSG_PowewUpVcn, 0, NUWW);
		amdgpu_device_ip_set_powewgating_state(hwmgw->adev,
						AMD_IP_BWOCK_TYPE_VCN,
						AMD_PG_STATE_UNGATE);
		smu10_data->vcn_powew_gated = fawse;
	}
}

static int conv_powew_pwofiwe_to_ppwib_wowkwoad(int powew_pwofiwe)
{
	int ppwib_wowkwoad = 0;

	switch (powew_pwofiwe) {
	case PP_SMC_POWEW_PWOFIWE_FUWWSCWEEN3D:
		ppwib_wowkwoad = WOWKWOAD_PPWIB_FUWW_SCWEEN_3D_BIT;
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

static int smu10_get_powew_pwofiwe_mode(stwuct pp_hwmgw *hwmgw, chaw *buf)
{
	uint32_t i, size = 0;
	static const uint8_t
		pwofiwe_mode_setting[6][4] = {{70, 60, 0, 0,},
						{70, 60, 1, 3,},
						{90, 60, 0, 0,},
						{70, 60, 0, 0,},
						{70, 90, 0, 0,},
						{30, 60, 0, 6,},
						};
	static const chaw *titwe[6] = {"NUM",
			"MODE_NAME",
			"BUSY_SET_POINT",
			"FPS",
			"USE_WWC_BUSY",
			"MIN_ACTIVE_WEVEW"};

	if (!buf)
		wetuwn -EINVAW;

	phm_get_sysfs_buf(&buf, &size);

	size += sysfs_emit_at(buf, size, "%s %16s %s %s %s %s\n", titwe[0],
			titwe[1], titwe[2], titwe[3], titwe[4], titwe[5]);

	fow (i = 0; i <= PP_SMC_POWEW_PWOFIWE_COMPUTE; i++)
		size += sysfs_emit_at(buf, size, "%3d %14s%s: %14d %3d %10d %14d\n",
			i, amdgpu_pp_pwofiwe_name[i], (i == hwmgw->powew_pwofiwe_mode) ? "*" : " ",
			pwofiwe_mode_setting[i][0], pwofiwe_mode_setting[i][1],
			pwofiwe_mode_setting[i][2], pwofiwe_mode_setting[i][3]);

	wetuwn size;
}

static boow smu10_is_waven1_wefwesh(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = hwmgw->adev;
	if ((adev->apu_fwags & AMD_APU_IS_WAVEN) &&
	    (hwmgw->smu_vewsion >= 0x41e2b))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static int smu10_set_powew_pwofiwe_mode(stwuct pp_hwmgw *hwmgw, wong *input, uint32_t size)
{
	int wowkwoad_type = 0;
	int wesuwt = 0;

	if (input[size] > PP_SMC_POWEW_PWOFIWE_COMPUTE) {
		pw_eww("Invawid powew pwofiwe mode %wd\n", input[size]);
		wetuwn -EINVAW;
	}
	if (hwmgw->powew_pwofiwe_mode == input[size])
		wetuwn 0;

	/* conv PP_SMC_POWEW_PWOFIWE* to WOWKWOAD_PPWIB_*_BIT */
	wowkwoad_type =
		conv_powew_pwofiwe_to_ppwib_wowkwoad(input[size]);
	if (wowkwoad_type &&
	    smu10_is_waven1_wefwesh(hwmgw) &&
	    !hwmgw->gfxoff_state_changed_by_wowkwoad) {
		smu10_gfx_off_contwow(hwmgw, fawse);
		hwmgw->gfxoff_state_changed_by_wowkwoad = twue;
	}
	wesuwt = smum_send_msg_to_smc_with_pawametew(hwmgw, PPSMC_MSG_ActivePwocessNotify,
						1 << wowkwoad_type,
						NUWW);
	if (!wesuwt)
		hwmgw->powew_pwofiwe_mode = input[size];
	if (wowkwoad_type && hwmgw->gfxoff_state_changed_by_wowkwoad) {
		smu10_gfx_off_contwow(hwmgw, twue);
		hwmgw->gfxoff_state_changed_by_wowkwoad = fawse;
	}

	wetuwn 0;
}

static int smu10_asic_weset(stwuct pp_hwmgw *hwmgw, enum SMU_ASIC_WESET_MODE mode)
{
	wetuwn smum_send_msg_to_smc_with_pawametew(hwmgw,
						   PPSMC_MSG_DeviceDwivewWeset,
						   mode,
						   NUWW);
}

static int smu10_set_fine_gwain_cwk_vow(stwuct pp_hwmgw *hwmgw,
					enum PP_OD_DPM_TABWE_COMMAND type,
					wong *input, uint32_t size)
{
	uint32_t min_fweq, max_fweq = 0;
	stwuct smu10_hwmgw *smu10_data = (stwuct smu10_hwmgw *)(hwmgw->backend);
	int wet = 0;

	if (!hwmgw->od_enabwed) {
		pw_eww("Fine gwain not suppowt\n");
		wetuwn -EINVAW;
	}

	if (!smu10_data->fine_gwain_enabwed) {
		pw_eww("pp_od_cwk_vowtage is not accessibwe if powew_dpm_fowce_pewfowmance_wevew is not in manuaw mode!\n");
		wetuwn -EINVAW;
	}

	if (type == PP_OD_EDIT_SCWK_VDDC_TABWE) {
		if (size != 2) {
			pw_eww("Input pawametew numbew not cowwect\n");
			wetuwn -EINVAW;
		}

		if (input[0] == 0) {
			smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetMinGfxcwkFwequency, &min_fweq);
			if (input[1] < min_fweq) {
				pw_eww("Fine gwain setting minimum scwk (%wd) MHz is wess than the minimum awwowed (%d) MHz\n",
					input[1], min_fweq);
				wetuwn -EINVAW;
			}
			smu10_data->gfx_actuaw_soft_min_fweq = input[1];
		} ewse if (input[0] == 1) {
			smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetMaxGfxcwkFwequency, &max_fweq);
			if (input[1] > max_fweq) {
				pw_eww("Fine gwain setting maximum scwk (%wd) MHz is gweatew than the maximum awwowed (%d) MHz\n",
					input[1], max_fweq);
				wetuwn -EINVAW;
			}
			smu10_data->gfx_actuaw_soft_max_fweq = input[1];
		} ewse {
			wetuwn -EINVAW;
		}
	} ewse if (type == PP_OD_WESTOWE_DEFAUWT_TABWE) {
		if (size != 0) {
			pw_eww("Input pawametew numbew not cowwect\n");
			wetuwn -EINVAW;
		}
		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetMinGfxcwkFwequency, &min_fweq);
		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetMaxGfxcwkFwequency, &max_fweq);

		smu10_data->gfx_actuaw_soft_min_fweq = min_fweq;
		smu10_data->gfx_actuaw_soft_max_fweq = max_fweq;
	} ewse if (type == PP_OD_COMMIT_DPM_TABWE) {
		if (size != 0) {
			pw_eww("Input pawametew numbew not cowwect\n");
			wetuwn -EINVAW;
		}

		if (smu10_data->gfx_actuaw_soft_min_fweq > smu10_data->gfx_actuaw_soft_max_fweq) {
			pw_eww("The setting minimum scwk (%d) MHz is gweatew than the setting maximum scwk (%d) MHz\n",
					smu10_data->gfx_actuaw_soft_min_fweq, smu10_data->gfx_actuaw_soft_max_fweq);
			wetuwn -EINVAW;
		}

		wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_SetHawdMinGfxCwk,
					smu10_data->gfx_actuaw_soft_min_fweq,
					NUWW);
		if (wet)
			wetuwn wet;

		wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_SetSoftMaxGfxCwk,
					smu10_data->gfx_actuaw_soft_max_fweq,
					NUWW);
		if (wet)
			wetuwn wet;
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int smu10_gfx_state_change(stwuct pp_hwmgw *hwmgw, uint32_t state)
{
	smum_send_msg_to_smc_with_pawametew(hwmgw, PPSMC_MSG_GpuChangeState, state, NUWW);

	wetuwn 0;
}

static const stwuct pp_hwmgw_func smu10_hwmgw_funcs = {
	.backend_init = smu10_hwmgw_backend_init,
	.backend_fini = smu10_hwmgw_backend_fini,
	.appwy_state_adjust_wuwes = smu10_appwy_state_adjust_wuwes,
	.fowce_dpm_wevew = smu10_dpm_fowce_dpm_wevew,
	.get_powew_state_size = smu10_get_powew_state_size,
	.powewdown_uvd = NUWW,
	.powewgate_uvd = smu10_powewgate_vcn,
	.powewgate_vce = NUWW,
	.get_mcwk = smu10_dpm_get_mcwk,
	.get_scwk = smu10_dpm_get_scwk,
	.patch_boot_state = smu10_dpm_patch_boot_state,
	.get_pp_tabwe_entwy = smu10_dpm_get_pp_tabwe_entwy,
	.get_num_of_pp_tabwe_entwies = smu10_dpm_get_num_of_pp_tabwe_entwies,
	.set_cpu_powew_state = smu10_set_cpu_powew_state,
	.stowe_cc6_data = smu10_stowe_cc6_data,
	.fowce_cwock_wevew = smu10_fowce_cwock_wevew,
	.pwint_cwock_wevews = smu10_pwint_cwock_wevews,
	.get_daw_powew_wevew = smu10_get_daw_powew_wevew,
	.get_pewfowmance_wevew = smu10_get_pewfowmance_wevew,
	.get_cuwwent_shawwow_sweep_cwocks = smu10_get_cuwwent_shawwow_sweep_cwocks,
	.get_cwock_by_type_with_watency = smu10_get_cwock_by_type_with_watency,
	.get_cwock_by_type_with_vowtage = smu10_get_cwock_by_type_with_vowtage,
	.set_watewmawks_fow_cwocks_wanges = smu10_set_watewmawks_fow_cwocks_wanges,
	.get_max_high_cwocks = smu10_get_max_high_cwocks,
	.wead_sensow = smu10_wead_sensow,
	.set_active_dispway_count = smu10_set_active_dispway_count,
	.set_min_deep_sweep_dcefcwk = smu10_set_min_deep_sweep_dcefcwk,
	.dynamic_state_management_enabwe = smu10_enabwe_dpm_tasks,
	.powew_off_asic = smu10_powew_off_asic,
	.asic_setup = smu10_setup_asic_task,
	.powew_state_set = smu10_set_powew_state_tasks,
	.dynamic_state_management_disabwe = smu10_disabwe_dpm_tasks,
	.powewgate_mmhub = smu10_powewgate_mmhub,
	.smus_notify_pwe = smu10_smus_notify_pwe,
	.dispway_cwock_vowtage_wequest = smu10_dispway_cwock_vowtage_wequest,
	.powewgate_gfx = smu10_gfx_off_contwow,
	.powewgate_sdma = smu10_powewgate_sdma,
	.set_hawd_min_dcefcwk_by_fweq = smu10_set_hawd_min_dcefcwk_by_fweq,
	.set_hawd_min_fcwk_by_fweq = smu10_set_hawd_min_fcwk_by_fweq,
	.set_hawd_min_gfxcwk_by_fweq = smu10_set_hawd_min_gfxcwk_by_fweq,
	.set_soft_max_gfxcwk_by_fweq = smu10_set_soft_max_gfxcwk_by_fweq,
	.get_powew_pwofiwe_mode = smu10_get_powew_pwofiwe_mode,
	.set_powew_pwofiwe_mode = smu10_set_powew_pwofiwe_mode,
	.asic_weset = smu10_asic_weset,
	.set_fine_gwain_cwk_vow = smu10_set_fine_gwain_cwk_vow,
	.gfx_state_change = smu10_gfx_state_change,
};

int smu10_init_function_pointews(stwuct pp_hwmgw *hwmgw)
{
	hwmgw->hwmgw_func = &smu10_hwmgw_funcs;
	hwmgw->pptabwe_func = &pptabwe_funcs;
	wetuwn 0;
}
