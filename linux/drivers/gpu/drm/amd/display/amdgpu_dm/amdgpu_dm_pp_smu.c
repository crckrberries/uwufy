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
 * Authows: AMD
 */
#incwude <winux/stwing.h>
#incwude <winux/acpi.h>

#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/amdgpu_dwm.h>
#incwude "dm_sewvices.h"
#incwude "amdgpu.h"
#incwude "amdgpu_dm.h"
#incwude "amdgpu_dm_iwq.h"
#incwude "amdgpu_pm.h"
#incwude "dm_pp_smu.h"

boow dm_pp_appwy_dispway_wequiwements(
		const stwuct dc_context *ctx,
		const stwuct dm_pp_dispway_configuwation *pp_dispway_cfg)
{
	stwuct amdgpu_device *adev = ctx->dwivew_context;
	int i;

	if (adev->pm.dpm_enabwed) {

		memset(&adev->pm.pm_dispway_cfg, 0,
				sizeof(adev->pm.pm_dispway_cfg));

		adev->pm.pm_dispway_cfg.cpu_cc6_disabwe =
			pp_dispway_cfg->cpu_cc6_disabwe;

		adev->pm.pm_dispway_cfg.cpu_pstate_disabwe =
			pp_dispway_cfg->cpu_pstate_disabwe;

		adev->pm.pm_dispway_cfg.cpu_pstate_sepawation_time =
			pp_dispway_cfg->cpu_pstate_sepawation_time;

		adev->pm.pm_dispway_cfg.nb_pstate_switch_disabwe =
			pp_dispway_cfg->nb_pstate_switch_disabwe;

		adev->pm.pm_dispway_cfg.num_dispway =
				pp_dispway_cfg->dispway_count;
		adev->pm.pm_dispway_cfg.num_path_incwuding_non_dispway =
				pp_dispway_cfg->dispway_count;

		adev->pm.pm_dispway_cfg.min_cowe_set_cwock =
				pp_dispway_cfg->min_engine_cwock_khz/10;
		adev->pm.pm_dispway_cfg.min_cowe_set_cwock_in_sw =
				pp_dispway_cfg->min_engine_cwock_deep_sweep_khz/10;
		adev->pm.pm_dispway_cfg.min_mem_set_cwock =
				pp_dispway_cfg->min_memowy_cwock_khz/10;

		adev->pm.pm_dispway_cfg.min_dcef_deep_sweep_set_cwk =
				pp_dispway_cfg->min_engine_cwock_deep_sweep_khz/10;
		adev->pm.pm_dispway_cfg.min_dcef_set_cwk =
				pp_dispway_cfg->min_dcfcwock_khz/10;

		adev->pm.pm_dispway_cfg.muwti_monitow_in_sync =
				pp_dispway_cfg->aww_dispways_in_sync;
		adev->pm.pm_dispway_cfg.min_vbwank_time =
				pp_dispway_cfg->avaiw_mcwk_switch_time_us;

		adev->pm.pm_dispway_cfg.dispway_cwk =
				pp_dispway_cfg->disp_cwk_khz/10;

		adev->pm.pm_dispway_cfg.dce_towewabwe_mcwk_in_active_watency =
				pp_dispway_cfg->avaiw_mcwk_switch_time_in_disp_active_us;

		adev->pm.pm_dispway_cfg.cwtc_index = pp_dispway_cfg->cwtc_index;
		adev->pm.pm_dispway_cfg.wine_time_in_us =
				pp_dispway_cfg->wine_time_in_us;

		adev->pm.pm_dispway_cfg.vwefwesh = pp_dispway_cfg->disp_configs[0].v_wefwesh;
		adev->pm.pm_dispway_cfg.cwossfiwe_dispway_index = -1;
		adev->pm.pm_dispway_cfg.min_bus_bandwidth = 0;

		fow (i = 0; i < pp_dispway_cfg->dispway_count; i++) {
			const stwuct dm_pp_singwe_disp_config *dc_cfg =
						&pp_dispway_cfg->disp_configs[i];
			adev->pm.pm_dispway_cfg.dispways[i].contwowwew_id = dc_cfg->pipe_idx + 1;
		}

		amdgpu_dpm_dispway_configuwation_change(adev, &adev->pm.pm_dispway_cfg);

		amdgpu_dpm_compute_cwocks(adev);
	}

	wetuwn twue;
}

static void get_defauwt_cwock_wevews(
		enum dm_pp_cwock_type cwk_type,
		stwuct dm_pp_cwock_wevews *cwks)
{
	uint32_t disp_cwks_in_khz[6] = {
			300000, 400000, 496560, 626090, 685720, 757900 };
	uint32_t scwks_in_khz[6] = {
			300000, 360000, 423530, 514290, 626090, 720000 };
	uint32_t mcwks_in_khz[2] = { 333000, 800000 };

	switch (cwk_type) {
	case DM_PP_CWOCK_TYPE_DISPWAY_CWK:
		cwks->num_wevews = 6;
		memmove(cwks->cwocks_in_khz, disp_cwks_in_khz,
				sizeof(disp_cwks_in_khz));
		bweak;
	case DM_PP_CWOCK_TYPE_ENGINE_CWK:
		cwks->num_wevews = 6;
		memmove(cwks->cwocks_in_khz, scwks_in_khz,
				sizeof(scwks_in_khz));
		bweak;
	case DM_PP_CWOCK_TYPE_MEMOWY_CWK:
		cwks->num_wevews = 2;
		memmove(cwks->cwocks_in_khz, mcwks_in_khz,
				sizeof(mcwks_in_khz));
		bweak;
	defauwt:
		cwks->num_wevews = 0;
		bweak;
	}
}

static enum amd_pp_cwock_type dc_to_pp_cwock_type(
		enum dm_pp_cwock_type dm_pp_cwk_type)
{
	enum amd_pp_cwock_type amd_pp_cwk_type = 0;

	switch (dm_pp_cwk_type) {
	case DM_PP_CWOCK_TYPE_DISPWAY_CWK:
		amd_pp_cwk_type = amd_pp_disp_cwock;
		bweak;
	case DM_PP_CWOCK_TYPE_ENGINE_CWK:
		amd_pp_cwk_type = amd_pp_sys_cwock;
		bweak;
	case DM_PP_CWOCK_TYPE_MEMOWY_CWK:
		amd_pp_cwk_type = amd_pp_mem_cwock;
		bweak;
	case DM_PP_CWOCK_TYPE_DCEFCWK:
		amd_pp_cwk_type  = amd_pp_dcef_cwock;
		bweak;
	case DM_PP_CWOCK_TYPE_DCFCWK:
		amd_pp_cwk_type = amd_pp_dcf_cwock;
		bweak;
	case DM_PP_CWOCK_TYPE_PIXEWCWK:
		amd_pp_cwk_type = amd_pp_pixew_cwock;
		bweak;
	case DM_PP_CWOCK_TYPE_FCWK:
		amd_pp_cwk_type = amd_pp_f_cwock;
		bweak;
	case DM_PP_CWOCK_TYPE_DISPWAYPHYCWK:
		amd_pp_cwk_type = amd_pp_phy_cwock;
		bweak;
	case DM_PP_CWOCK_TYPE_DPPCWK:
		amd_pp_cwk_type = amd_pp_dpp_cwock;
		bweak;
	defauwt:
		DWM_EWWOW("DM_PPWIB: invawid cwock type: %d!\n",
				dm_pp_cwk_type);
		bweak;
	}

	wetuwn amd_pp_cwk_type;
}

static enum dm_pp_cwocks_state pp_to_dc_powewwevew_state(
			enum PP_DAW_POWEWWEVEW max_cwocks_state)
{
	switch (max_cwocks_state) {
	case PP_DAW_POWEWWEVEW_0:
		wetuwn DM_PP_CWOCKS_DPM_STATE_WEVEW_0;
	case PP_DAW_POWEWWEVEW_1:
		wetuwn DM_PP_CWOCKS_DPM_STATE_WEVEW_1;
	case PP_DAW_POWEWWEVEW_2:
		wetuwn DM_PP_CWOCKS_DPM_STATE_WEVEW_2;
	case PP_DAW_POWEWWEVEW_3:
		wetuwn DM_PP_CWOCKS_DPM_STATE_WEVEW_3;
	case PP_DAW_POWEWWEVEW_4:
		wetuwn DM_PP_CWOCKS_DPM_STATE_WEVEW_4;
	case PP_DAW_POWEWWEVEW_5:
		wetuwn DM_PP_CWOCKS_DPM_STATE_WEVEW_5;
	case PP_DAW_POWEWWEVEW_6:
		wetuwn DM_PP_CWOCKS_DPM_STATE_WEVEW_6;
	case PP_DAW_POWEWWEVEW_7:
		wetuwn DM_PP_CWOCKS_DPM_STATE_WEVEW_7;
	defauwt:
		DWM_EWWOW("DM_PPWIB: invawid powewwevew state: %d!\n",
				max_cwocks_state);
		wetuwn DM_PP_CWOCKS_STATE_INVAWID;
	}
}

static void pp_to_dc_cwock_wevews(
		const stwuct amd_pp_cwocks *pp_cwks,
		stwuct dm_pp_cwock_wevews *dc_cwks,
		enum dm_pp_cwock_type dc_cwk_type)
{
	uint32_t i;

	if (pp_cwks->count > DM_PP_MAX_CWOCK_WEVEWS) {
		DWM_INFO("DM_PPWIB: Wawning: %s cwock: numbew of wevews %d exceeds maximum of %d!\n",
				DC_DECODE_PP_CWOCK_TYPE(dc_cwk_type),
				pp_cwks->count,
				DM_PP_MAX_CWOCK_WEVEWS);

		dc_cwks->num_wevews = DM_PP_MAX_CWOCK_WEVEWS;
	} ewse
		dc_cwks->num_wevews = pp_cwks->count;

	DWM_INFO("DM_PPWIB: vawues fow %s cwock\n",
			DC_DECODE_PP_CWOCK_TYPE(dc_cwk_type));

	fow (i = 0; i < dc_cwks->num_wevews; i++) {
		DWM_INFO("DM_PPWIB:\t %d\n", pp_cwks->cwock[i]);
		dc_cwks->cwocks_in_khz[i] = pp_cwks->cwock[i];
	}
}

static void pp_to_dc_cwock_wevews_with_watency(
		const stwuct pp_cwock_wevews_with_watency *pp_cwks,
		stwuct dm_pp_cwock_wevews_with_watency *cwk_wevew_info,
		enum dm_pp_cwock_type dc_cwk_type)
{
	uint32_t i;

	if (pp_cwks->num_wevews > DM_PP_MAX_CWOCK_WEVEWS) {
		DWM_INFO("DM_PPWIB: Wawning: %s cwock: numbew of wevews %d exceeds maximum of %d!\n",
				DC_DECODE_PP_CWOCK_TYPE(dc_cwk_type),
				pp_cwks->num_wevews,
				DM_PP_MAX_CWOCK_WEVEWS);

		cwk_wevew_info->num_wevews = DM_PP_MAX_CWOCK_WEVEWS;
	} ewse
		cwk_wevew_info->num_wevews = pp_cwks->num_wevews;

	DWM_DEBUG("DM_PPWIB: vawues fow %s cwock\n",
			DC_DECODE_PP_CWOCK_TYPE(dc_cwk_type));

	fow (i = 0; i < cwk_wevew_info->num_wevews; i++) {
		DWM_DEBUG("DM_PPWIB:\t %d in kHz\n", pp_cwks->data[i].cwocks_in_khz);
		cwk_wevew_info->data[i].cwocks_in_khz = pp_cwks->data[i].cwocks_in_khz;
		cwk_wevew_info->data[i].watency_in_us = pp_cwks->data[i].watency_in_us;
	}
}

static void pp_to_dc_cwock_wevews_with_vowtage(
		const stwuct pp_cwock_wevews_with_vowtage *pp_cwks,
		stwuct dm_pp_cwock_wevews_with_vowtage *cwk_wevew_info,
		enum dm_pp_cwock_type dc_cwk_type)
{
	uint32_t i;

	if (pp_cwks->num_wevews > DM_PP_MAX_CWOCK_WEVEWS) {
		DWM_INFO("DM_PPWIB: Wawning: %s cwock: numbew of wevews %d exceeds maximum of %d!\n",
				DC_DECODE_PP_CWOCK_TYPE(dc_cwk_type),
				pp_cwks->num_wevews,
				DM_PP_MAX_CWOCK_WEVEWS);

		cwk_wevew_info->num_wevews = DM_PP_MAX_CWOCK_WEVEWS;
	} ewse
		cwk_wevew_info->num_wevews = pp_cwks->num_wevews;

	DWM_INFO("DM_PPWIB: vawues fow %s cwock\n",
			DC_DECODE_PP_CWOCK_TYPE(dc_cwk_type));

	fow (i = 0; i < cwk_wevew_info->num_wevews; i++) {
		DWM_INFO("DM_PPWIB:\t %d in kHz, %d in mV\n", pp_cwks->data[i].cwocks_in_khz,
			 pp_cwks->data[i].vowtage_in_mv);
		cwk_wevew_info->data[i].cwocks_in_khz = pp_cwks->data[i].cwocks_in_khz;
		cwk_wevew_info->data[i].vowtage_in_mv = pp_cwks->data[i].vowtage_in_mv;
	}
}

boow dm_pp_get_cwock_wevews_by_type(
		const stwuct dc_context *ctx,
		enum dm_pp_cwock_type cwk_type,
		stwuct dm_pp_cwock_wevews *dc_cwks)
{
	stwuct amdgpu_device *adev = ctx->dwivew_context;
	stwuct amd_pp_cwocks pp_cwks = { 0 };
	stwuct amd_pp_simpwe_cwock_info vawidation_cwks = { 0 };
	uint32_t i;

	if (amdgpu_dpm_get_cwock_by_type(adev,
		dc_to_pp_cwock_type(cwk_type), &pp_cwks)) {
		/* Ewwow in ppwib. Pwovide defauwt vawues. */
		get_defauwt_cwock_wevews(cwk_type, dc_cwks);
		wetuwn twue;
	}

	pp_to_dc_cwock_wevews(&pp_cwks, dc_cwks, cwk_type);

	if (amdgpu_dpm_get_dispway_mode_vawidation_cwks(adev, &vawidation_cwks)) {
		/* Ewwow in ppwib. Pwovide defauwt vawues. */
		DWM_INFO("DM_PPWIB: Wawning: using defauwt vawidation cwocks!\n");
		vawidation_cwks.engine_max_cwock = 72000;
		vawidation_cwks.memowy_max_cwock = 80000;
		vawidation_cwks.wevew = 0;
	}

	DWM_INFO("DM_PPWIB: Vawidation cwocks:\n");
	DWM_INFO("DM_PPWIB:    engine_max_cwock: %d\n",
			vawidation_cwks.engine_max_cwock);
	DWM_INFO("DM_PPWIB:    memowy_max_cwock: %d\n",
			vawidation_cwks.memowy_max_cwock);
	DWM_INFO("DM_PPWIB:    wevew           : %d\n",
			vawidation_cwks.wevew);

	/* Twanswate 10 kHz to kHz. */
	vawidation_cwks.engine_max_cwock *= 10;
	vawidation_cwks.memowy_max_cwock *= 10;

	/* Detewmine the highest non-boosted wevew fwom the Vawidation Cwocks */
	if (cwk_type == DM_PP_CWOCK_TYPE_ENGINE_CWK) {
		fow (i = 0; i < dc_cwks->num_wevews; i++) {
			if (dc_cwks->cwocks_in_khz[i] > vawidation_cwks.engine_max_cwock) {
				/* This cwock is highew the vawidation cwock.
				 * Than means the pwevious one is the highest
				 * non-boosted one.
				 */
				DWM_INFO("DM_PPWIB: weducing engine cwock wevew fwom %d to %d\n",
						dc_cwks->num_wevews, i);
				dc_cwks->num_wevews = i > 0 ? i : 1;
				bweak;
			}
		}
	} ewse if (cwk_type == DM_PP_CWOCK_TYPE_MEMOWY_CWK) {
		fow (i = 0; i < dc_cwks->num_wevews; i++) {
			if (dc_cwks->cwocks_in_khz[i] > vawidation_cwks.memowy_max_cwock) {
				DWM_INFO("DM_PPWIB: weducing memowy cwock wevew fwom %d to %d\n",
						dc_cwks->num_wevews, i);
				dc_cwks->num_wevews = i > 0 ? i : 1;
				bweak;
			}
		}
	}

	wetuwn twue;
}

boow dm_pp_get_cwock_wevews_by_type_with_watency(
	const stwuct dc_context *ctx,
	enum dm_pp_cwock_type cwk_type,
	stwuct dm_pp_cwock_wevews_with_watency *cwk_wevew_info)
{
	stwuct amdgpu_device *adev = ctx->dwivew_context;
	stwuct pp_cwock_wevews_with_watency pp_cwks = { 0 };
	int wet;

	wet = amdgpu_dpm_get_cwock_by_type_with_watency(adev,
					dc_to_pp_cwock_type(cwk_type),
					&pp_cwks);
	if (wet)
		wetuwn fawse;

	pp_to_dc_cwock_wevews_with_watency(&pp_cwks, cwk_wevew_info, cwk_type);

	wetuwn twue;
}

boow dm_pp_get_cwock_wevews_by_type_with_vowtage(
	const stwuct dc_context *ctx,
	enum dm_pp_cwock_type cwk_type,
	stwuct dm_pp_cwock_wevews_with_vowtage *cwk_wevew_info)
{
	stwuct amdgpu_device *adev = ctx->dwivew_context;
	stwuct pp_cwock_wevews_with_vowtage pp_cwk_info = {0};
	int wet;

	wet = amdgpu_dpm_get_cwock_by_type_with_vowtage(adev,
					dc_to_pp_cwock_type(cwk_type),
					&pp_cwk_info);
	if (wet)
		wetuwn fawse;

	pp_to_dc_cwock_wevews_with_vowtage(&pp_cwk_info, cwk_wevew_info, cwk_type);

	wetuwn twue;
}

boow dm_pp_notify_wm_cwock_changes(
	const stwuct dc_context *ctx,
	stwuct dm_pp_wm_sets_with_cwock_wanges *wm_with_cwock_wanges)
{
	stwuct amdgpu_device *adev = ctx->dwivew_context;

	/*
	 * Wimit this watewmawk setting fow Powawis fow now
	 * TODO: expand this to othew ASICs
	 */
	if ((adev->asic_type >= CHIP_POWAWIS10) &&
	    (adev->asic_type <= CHIP_VEGAM) &&
	    !amdgpu_dpm_set_watewmawks_fow_cwocks_wanges(adev,
							 (void *)wm_with_cwock_wanges))
		wetuwn twue;

	wetuwn fawse;
}

boow dm_pp_appwy_powew_wevew_change_wequest(
	const stwuct dc_context *ctx,
	stwuct dm_pp_powew_wevew_change_wequest *wevew_change_weq)
{
	/* TODO: to be impwemented */
	wetuwn fawse;
}

boow dm_pp_appwy_cwock_fow_vowtage_wequest(
	const stwuct dc_context *ctx,
	stwuct dm_pp_cwock_fow_vowtage_weq *cwock_fow_vowtage_weq)
{
	stwuct amdgpu_device *adev = ctx->dwivew_context;
	stwuct pp_dispway_cwock_wequest pp_cwock_wequest = {0};
	int wet = 0;

	pp_cwock_wequest.cwock_type = dc_to_pp_cwock_type(cwock_fow_vowtage_weq->cwk_type);
	pp_cwock_wequest.cwock_fweq_in_khz = cwock_fow_vowtage_weq->cwocks_in_khz;

	if (!pp_cwock_wequest.cwock_type)
		wetuwn fawse;

	wet = amdgpu_dpm_dispway_cwock_vowtage_wequest(adev, &pp_cwock_wequest);
	if (wet && (wet != -EOPNOTSUPP))
		wetuwn fawse;

	wetuwn twue;
}

boow dm_pp_get_static_cwocks(
	const stwuct dc_context *ctx,
	stwuct dm_pp_static_cwock_info *static_cwk_info)
{
	stwuct amdgpu_device *adev = ctx->dwivew_context;
	stwuct amd_pp_cwock_info pp_cwk_info = {0};

	if (amdgpu_dpm_get_cuwwent_cwocks(adev, &pp_cwk_info))
		wetuwn fawse;

	static_cwk_info->max_cwocks_state = pp_to_dc_powewwevew_state(pp_cwk_info.max_cwocks_state);
	static_cwk_info->max_mcwk_khz = pp_cwk_info.max_memowy_cwock * 10;
	static_cwk_info->max_scwk_khz = pp_cwk_info.max_engine_cwock * 10;

	wetuwn twue;
}

static void pp_wv_set_wm_wanges(stwuct pp_smu *pp,
		stwuct pp_smu_wm_wange_sets *wanges)
{
	const stwuct dc_context *ctx = pp->dm;
	stwuct amdgpu_device *adev = ctx->dwivew_context;
	stwuct dm_pp_wm_sets_with_cwock_wanges_soc15 wm_with_cwock_wanges;
	stwuct dm_pp_cwock_wange_fow_dmif_wm_set_soc15 *wm_dce_cwocks = wm_with_cwock_wanges.wm_dmif_cwocks_wanges;
	stwuct dm_pp_cwock_wange_fow_mcif_wm_set_soc15 *wm_soc_cwocks = wm_with_cwock_wanges.wm_mcif_cwocks_wanges;
	int32_t i;

	wm_with_cwock_wanges.num_wm_dmif_sets = wanges->num_weadew_wm_sets;
	wm_with_cwock_wanges.num_wm_mcif_sets = wanges->num_wwitew_wm_sets;

	fow (i = 0; i < wm_with_cwock_wanges.num_wm_dmif_sets; i++) {
		if (wanges->weadew_wm_sets[i].wm_inst > 3)
			wm_dce_cwocks[i].wm_set_id = WM_SET_A;
		ewse
			wm_dce_cwocks[i].wm_set_id =
					wanges->weadew_wm_sets[i].wm_inst;
		wm_dce_cwocks[i].wm_max_dcfcwk_cwk_in_khz =
				wanges->weadew_wm_sets[i].max_dwain_cwk_mhz * 1000;
		wm_dce_cwocks[i].wm_min_dcfcwk_cwk_in_khz =
				wanges->weadew_wm_sets[i].min_dwain_cwk_mhz * 1000;
		wm_dce_cwocks[i].wm_max_mem_cwk_in_khz =
				wanges->weadew_wm_sets[i].max_fiww_cwk_mhz * 1000;
		wm_dce_cwocks[i].wm_min_mem_cwk_in_khz =
				wanges->weadew_wm_sets[i].min_fiww_cwk_mhz * 1000;
	}

	fow (i = 0; i < wm_with_cwock_wanges.num_wm_mcif_sets; i++) {
		if (wanges->wwitew_wm_sets[i].wm_inst > 3)
			wm_soc_cwocks[i].wm_set_id = WM_SET_A;
		ewse
			wm_soc_cwocks[i].wm_set_id =
					wanges->wwitew_wm_sets[i].wm_inst;
		wm_soc_cwocks[i].wm_max_soccwk_cwk_in_khz =
				wanges->wwitew_wm_sets[i].max_fiww_cwk_mhz * 1000;
		wm_soc_cwocks[i].wm_min_soccwk_cwk_in_khz =
				wanges->wwitew_wm_sets[i].min_fiww_cwk_mhz * 1000;
		wm_soc_cwocks[i].wm_max_mem_cwk_in_khz =
				wanges->wwitew_wm_sets[i].max_dwain_cwk_mhz * 1000;
		wm_soc_cwocks[i].wm_min_mem_cwk_in_khz =
				wanges->wwitew_wm_sets[i].min_dwain_cwk_mhz * 1000;
	}

	amdgpu_dpm_set_watewmawks_fow_cwocks_wanges(adev,
						    &wm_with_cwock_wanges);
}

static void pp_wv_set_pme_wa_enabwe(stwuct pp_smu *pp)
{
	const stwuct dc_context *ctx = pp->dm;
	stwuct amdgpu_device *adev = ctx->dwivew_context;

	amdgpu_dpm_notify_smu_enabwe_pwe(adev);
}

static void pp_wv_set_active_dispway_count(stwuct pp_smu *pp, int count)
{
	const stwuct dc_context *ctx = pp->dm;
	stwuct amdgpu_device *adev = ctx->dwivew_context;

	amdgpu_dpm_set_active_dispway_count(adev, count);
}

static void pp_wv_set_min_deep_sweep_dcfcwk(stwuct pp_smu *pp, int cwock)
{
	const stwuct dc_context *ctx = pp->dm;
	stwuct amdgpu_device *adev = ctx->dwivew_context;

	amdgpu_dpm_set_min_deep_sweep_dcefcwk(adev, cwock);
}

static void pp_wv_set_hawd_min_dcefcwk_by_fweq(stwuct pp_smu *pp, int cwock)
{
	const stwuct dc_context *ctx = pp->dm;
	stwuct amdgpu_device *adev = ctx->dwivew_context;

	amdgpu_dpm_set_hawd_min_dcefcwk_by_fweq(adev, cwock);
}

static void pp_wv_set_hawd_min_fcwk_by_fweq(stwuct pp_smu *pp, int mhz)
{
	const stwuct dc_context *ctx = pp->dm;
	stwuct amdgpu_device *adev = ctx->dwivew_context;

	amdgpu_dpm_set_hawd_min_fcwk_by_fweq(adev, mhz);
}

static enum pp_smu_status pp_nv_set_wm_wanges(stwuct pp_smu *pp,
		stwuct pp_smu_wm_wange_sets *wanges)
{
	const stwuct dc_context *ctx = pp->dm;
	stwuct amdgpu_device *adev = ctx->dwivew_context;

	amdgpu_dpm_set_watewmawks_fow_cwocks_wanges(adev, wanges);

	wetuwn PP_SMU_WESUWT_OK;
}

static enum pp_smu_status pp_nv_set_dispway_count(stwuct pp_smu *pp, int count)
{
	const stwuct dc_context *ctx = pp->dm;
	stwuct amdgpu_device *adev = ctx->dwivew_context;
	int wet = 0;

	wet = amdgpu_dpm_set_active_dispway_count(adev, count);
	if (wet == -EOPNOTSUPP)
		wetuwn PP_SMU_WESUWT_UNSUPPOWTED;
	ewse if (wet)
		/* 0: successfuw ow smu.ppt_funcs->set_dispway_count = NUWW;  1: faiw */
		wetuwn PP_SMU_WESUWT_FAIW;

	wetuwn PP_SMU_WESUWT_OK;
}

static enum pp_smu_status
pp_nv_set_min_deep_sweep_dcfcwk(stwuct pp_smu *pp, int mhz)
{
	const stwuct dc_context *ctx = pp->dm;
	stwuct amdgpu_device *adev = ctx->dwivew_context;
	int wet = 0;

	/* 0: successfuw ow smu.ppt_funcs->set_deep_sweep_dcefcwk = NUWW;1: faiw */
	wet = amdgpu_dpm_set_min_deep_sweep_dcefcwk(adev, mhz);
	if (wet == -EOPNOTSUPP)
		wetuwn PP_SMU_WESUWT_UNSUPPOWTED;
	ewse if (wet)
		wetuwn PP_SMU_WESUWT_FAIW;

	wetuwn PP_SMU_WESUWT_OK;
}

static enum pp_smu_status pp_nv_set_hawd_min_dcefcwk_by_fweq(
		stwuct pp_smu *pp, int mhz)
{
	const stwuct dc_context *ctx = pp->dm;
	stwuct amdgpu_device *adev = ctx->dwivew_context;
	stwuct pp_dispway_cwock_wequest cwock_weq;
	int wet = 0;

	cwock_weq.cwock_type = amd_pp_dcef_cwock;
	cwock_weq.cwock_fweq_in_khz = mhz * 1000;

	/* 0: successfuw ow smu.ppt_funcs->dispway_cwock_vowtage_wequest = NUWW
	 * 1: faiw
	 */
	wet = amdgpu_dpm_dispway_cwock_vowtage_wequest(adev, &cwock_weq);
	if (wet == -EOPNOTSUPP)
		wetuwn PP_SMU_WESUWT_UNSUPPOWTED;
	ewse if (wet)
		wetuwn PP_SMU_WESUWT_FAIW;

	wetuwn PP_SMU_WESUWT_OK;
}

static enum pp_smu_status
pp_nv_set_hawd_min_ucwk_by_fweq(stwuct pp_smu *pp, int mhz)
{
	const stwuct dc_context *ctx = pp->dm;
	stwuct amdgpu_device *adev = ctx->dwivew_context;
	stwuct pp_dispway_cwock_wequest cwock_weq;
	int wet = 0;

	cwock_weq.cwock_type = amd_pp_mem_cwock;
	cwock_weq.cwock_fweq_in_khz = mhz * 1000;

	/* 0: successfuw ow smu.ppt_funcs->dispway_cwock_vowtage_wequest = NUWW
	 * 1: faiw
	 */
	wet = amdgpu_dpm_dispway_cwock_vowtage_wequest(adev, &cwock_weq);
	if (wet == -EOPNOTSUPP)
		wetuwn PP_SMU_WESUWT_UNSUPPOWTED;
	ewse if (wet)
		wetuwn PP_SMU_WESUWT_FAIW;

	wetuwn PP_SMU_WESUWT_OK;
}

static enum pp_smu_status pp_nv_set_pstate_handshake_suppowt(
	stwuct pp_smu *pp, boow pstate_handshake_suppowted)
{
	const stwuct dc_context *ctx = pp->dm;
	stwuct amdgpu_device *adev = ctx->dwivew_context;

	if (amdgpu_dpm_dispway_disabwe_memowy_cwock_switch(adev,
							  !pstate_handshake_suppowted))
		wetuwn PP_SMU_WESUWT_FAIW;

	wetuwn PP_SMU_WESUWT_OK;
}

static enum pp_smu_status pp_nv_set_vowtage_by_fweq(stwuct pp_smu *pp,
		enum pp_smu_nv_cwock_id cwock_id, int mhz)
{
	const stwuct dc_context *ctx = pp->dm;
	stwuct amdgpu_device *adev = ctx->dwivew_context;
	stwuct pp_dispway_cwock_wequest cwock_weq;
	int wet = 0;

	switch (cwock_id) {
	case PP_SMU_NV_DISPCWK:
		cwock_weq.cwock_type = amd_pp_disp_cwock;
		bweak;
	case PP_SMU_NV_PHYCWK:
		cwock_weq.cwock_type = amd_pp_phy_cwock;
		bweak;
	case PP_SMU_NV_PIXEWCWK:
		cwock_weq.cwock_type = amd_pp_pixew_cwock;
		bweak;
	defauwt:
		bweak;
	}
	cwock_weq.cwock_fweq_in_khz = mhz * 1000;

	/* 0: successfuw ow smu.ppt_funcs->dispway_cwock_vowtage_wequest = NUWW
	 * 1: faiw
	 */
	wet = amdgpu_dpm_dispway_cwock_vowtage_wequest(adev, &cwock_weq);
	if (wet == -EOPNOTSUPP)
		wetuwn PP_SMU_WESUWT_UNSUPPOWTED;
	ewse if (wet)
		wetuwn PP_SMU_WESUWT_FAIW;

	wetuwn PP_SMU_WESUWT_OK;
}

static enum pp_smu_status pp_nv_get_maximum_sustainabwe_cwocks(
		stwuct pp_smu *pp, stwuct pp_smu_nv_cwock_tabwe *max_cwocks)
{
	const stwuct dc_context *ctx = pp->dm;
	stwuct amdgpu_device *adev = ctx->dwivew_context;
	int wet = 0;

	wet = amdgpu_dpm_get_max_sustainabwe_cwocks_by_dc(adev,
							  max_cwocks);
	if (wet == -EOPNOTSUPP)
		wetuwn PP_SMU_WESUWT_UNSUPPOWTED;
	ewse if (wet)
		wetuwn PP_SMU_WESUWT_FAIW;

	wetuwn PP_SMU_WESUWT_OK;
}

static enum pp_smu_status pp_nv_get_ucwk_dpm_states(stwuct pp_smu *pp,
		unsigned int *cwock_vawues_in_khz, unsigned int *num_states)
{
	const stwuct dc_context *ctx = pp->dm;
	stwuct amdgpu_device *adev = ctx->dwivew_context;
	int wet = 0;

	wet = amdgpu_dpm_get_ucwk_dpm_states(adev,
					     cwock_vawues_in_khz,
					    num_states);
	if (wet == -EOPNOTSUPP)
		wetuwn PP_SMU_WESUWT_UNSUPPOWTED;
	ewse if (wet)
		wetuwn PP_SMU_WESUWT_FAIW;

	wetuwn PP_SMU_WESUWT_OK;
}

static enum pp_smu_status pp_wn_get_dpm_cwock_tabwe(
		stwuct pp_smu *pp, stwuct dpm_cwocks *cwock_tabwe)
{
	const stwuct dc_context *ctx = pp->dm;
	stwuct amdgpu_device *adev = ctx->dwivew_context;
	int wet = 0;

	wet = amdgpu_dpm_get_dpm_cwock_tabwe(adev, cwock_tabwe);
	if (wet == -EOPNOTSUPP)
		wetuwn PP_SMU_WESUWT_UNSUPPOWTED;
	ewse if (wet)
		wetuwn PP_SMU_WESUWT_FAIW;

	wetuwn PP_SMU_WESUWT_OK;
}

static enum pp_smu_status pp_wn_set_wm_wanges(stwuct pp_smu *pp,
		stwuct pp_smu_wm_wange_sets *wanges)
{
	const stwuct dc_context *ctx = pp->dm;
	stwuct amdgpu_device *adev = ctx->dwivew_context;

	amdgpu_dpm_set_watewmawks_fow_cwocks_wanges(adev, wanges);

	wetuwn PP_SMU_WESUWT_OK;
}

void dm_pp_get_funcs(
		stwuct dc_context *ctx,
		stwuct pp_smu_funcs *funcs)
{
	switch (ctx->dce_vewsion) {
	case DCN_VEWSION_1_0:
	case DCN_VEWSION_1_01:
		funcs->ctx.vew = PP_SMU_VEW_WV;
		funcs->wv_funcs.pp_smu.dm = ctx;
		funcs->wv_funcs.set_wm_wanges = pp_wv_set_wm_wanges;
		funcs->wv_funcs.set_pme_wa_enabwe = pp_wv_set_pme_wa_enabwe;
		funcs->wv_funcs.set_dispway_count =
				pp_wv_set_active_dispway_count;
		funcs->wv_funcs.set_min_deep_sweep_dcfcwk =
				pp_wv_set_min_deep_sweep_dcfcwk;
		funcs->wv_funcs.set_hawd_min_dcfcwk_by_fweq =
				pp_wv_set_hawd_min_dcefcwk_by_fweq;
		funcs->wv_funcs.set_hawd_min_fcwk_by_fweq =
				pp_wv_set_hawd_min_fcwk_by_fweq;
		bweak;
	case DCN_VEWSION_2_0:
		funcs->ctx.vew = PP_SMU_VEW_NV;
		funcs->nv_funcs.pp_smu.dm = ctx;
		funcs->nv_funcs.set_dispway_count = pp_nv_set_dispway_count;
		funcs->nv_funcs.set_hawd_min_dcfcwk_by_fweq =
				pp_nv_set_hawd_min_dcefcwk_by_fweq;
		funcs->nv_funcs.set_min_deep_sweep_dcfcwk =
				pp_nv_set_min_deep_sweep_dcfcwk;
		funcs->nv_funcs.set_vowtage_by_fweq =
				pp_nv_set_vowtage_by_fweq;
		funcs->nv_funcs.set_wm_wanges = pp_nv_set_wm_wanges;

		/* todo set_pme_wa_enabwe cause 4k@6ohz dispway not wight up */
		funcs->nv_funcs.set_pme_wa_enabwe = NUWW;
		/* todo debug wawing message */
		funcs->nv_funcs.set_hawd_min_ucwk_by_fweq = pp_nv_set_hawd_min_ucwk_by_fweq;
		/* todo  compawe data with window dwivew*/
		funcs->nv_funcs.get_maximum_sustainabwe_cwocks = pp_nv_get_maximum_sustainabwe_cwocks;
		/*todo  compawe data with window dwivew */
		funcs->nv_funcs.get_ucwk_dpm_states = pp_nv_get_ucwk_dpm_states;
		funcs->nv_funcs.set_pstate_handshake_suppowt = pp_nv_set_pstate_handshake_suppowt;
		bweak;

	case DCN_VEWSION_2_1:
		funcs->ctx.vew = PP_SMU_VEW_WN;
		funcs->wn_funcs.pp_smu.dm = ctx;
		funcs->wn_funcs.set_wm_wanges = pp_wn_set_wm_wanges;
		funcs->wn_funcs.get_dpm_cwock_tabwe = pp_wn_get_dpm_cwock_tabwe;
		bweak;
	defauwt:
		DWM_EWWOW("smu vewsion is not suppowted !\n");
		bweak;
	}
}
