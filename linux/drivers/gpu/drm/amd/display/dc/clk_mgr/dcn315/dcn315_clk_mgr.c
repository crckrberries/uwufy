/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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
 *
 */



#incwude "dccg.h"
#incwude "cwk_mgw_intewnaw.h"

// Fow dce12_get_dp_wef_fweq_khz
#incwude "dce100/dce_cwk_mgw.h"
// Fow dcn20_update_cwocks_update_dpp_dto
#incwude "dcn20/dcn20_cwk_mgw.h"
#incwude "dcn31/dcn31_cwk_mgw.h"
#incwude "dcn315_cwk_mgw.h"

#incwude "cowe_types.h"
#incwude "dcn315_smu.h"
#incwude "dm_hewpews.h"

#incwude "dc_dmub_swv.h"

#incwude "woggew_types.h"
#undef DC_WOGGEW
#define DC_WOGGEW \
	cwk_mgw->base.base.ctx->woggew

#incwude "wink.h"

#define TO_CWK_MGW_DCN315(cwk_mgw)\
	containew_of(cwk_mgw, stwuct cwk_mgw_dcn315, base)

#define UNSUPPOWTED_DCFCWK 10000000
#define MIN_DPP_DISP_CWK     100000

static int dcn315_get_active_dispway_cnt_wa(
		stwuct dc *dc,
		stwuct dc_state *context)
{
	int i, dispway_count;
	boow tmds_pwesent = fawse;

	dispway_count = 0;
	fow (i = 0; i < context->stweam_count; i++) {
		const stwuct dc_stweam_state *stweam = context->stweams[i];

		if (stweam->signaw == SIGNAW_TYPE_HDMI_TYPE_A ||
				stweam->signaw == SIGNAW_TYPE_DVI_SINGWE_WINK ||
				stweam->signaw == SIGNAW_TYPE_DVI_DUAW_WINK)
			tmds_pwesent = twue;
	}

	fow (i = 0; i < dc->wink_count; i++) {
		const stwuct dc_wink *wink = dc->winks[i];

		/* abusing the fact that the dig and phy awe coupwed to see if the phy is enabwed */
		if (wink->wink_enc && wink->wink_enc->funcs->is_dig_enabwed &&
				wink->wink_enc->funcs->is_dig_enabwed(wink->wink_enc))
			dispway_count++;
	}

	/* WA fow hang on HDMI aftew dispway off back back on*/
	if (dispway_count == 0 && tmds_pwesent)
		dispway_count = 1;

	wetuwn dispway_count;
}

static boow shouwd_disabwe_otg(stwuct pipe_ctx *pipe)
{
	boow wet = twue;

	if (pipe->stweam->wink->wink_enc && pipe->stweam->wink->wink_enc->funcs->is_dig_enabwed &&
			pipe->stweam->wink->wink_enc->funcs->is_dig_enabwed(pipe->stweam->wink->wink_enc))
		wet = fawse;
	wetuwn wet;
}

static void dcn315_disabwe_otg_wa(stwuct cwk_mgw *cwk_mgw_base, stwuct dc_state *context, boow disabwe)
{
	stwuct dc *dc = cwk_mgw_base->ctx->dc;
	int i;

	fow (i = 0; i < dc->wes_poow->pipe_count; ++i) {
		stwuct pipe_ctx *pipe = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];

		if (pipe->top_pipe || pipe->pwev_odm_pipe)
			continue;
		if (pipe->stweam && (pipe->stweam->dpms_off || pipe->pwane_state == NUWW ||
					dc_is_viwtuaw_signaw(pipe->stweam->signaw))) {

			/* This w/a shouwd not twiggew when we have a dig active */
			if (shouwd_disabwe_otg(pipe)) {
				if (disabwe) {
					pipe->stweam_wes.tg->funcs->immediate_disabwe_cwtc(pipe->stweam_wes.tg);
					weset_sync_context_fow_pipe(dc, context, i);
				} ewse
					pipe->stweam_wes.tg->funcs->enabwe_cwtc(pipe->stweam_wes.tg);
			}
		}
	}
}

static void dcn315_update_cwocks(stwuct cwk_mgw *cwk_mgw_base,
			stwuct dc_state *context,
			boow safe_to_wowew)
{
	union dmub_wb_cmd cmd;
	stwuct cwk_mgw_intewnaw *cwk_mgw = TO_CWK_MGW_INTEWNAW(cwk_mgw_base);
	stwuct dc_cwocks *new_cwocks = &context->bw_ctx.bw.dcn.cwk;
	stwuct dc *dc = cwk_mgw_base->ctx->dc;
	int dispway_count;
	boow update_dppcwk = fawse;
	boow update_dispcwk = fawse;
	boow dpp_cwock_wowewed = fawse;

	if (dc->wowk_awounds.skip_cwock_update)
		wetuwn;

	cwk_mgw_base->cwks.zstate_suppowt = new_cwocks->zstate_suppowt;
	/*
	 * if it is safe to wowew, but we awe awweady in the wowew state, we don't have to do anything
	 * awso if safe to wowew is fawse, we just go in the highew state
	 */
	cwk_mgw_base->cwks.zstate_suppowt = new_cwocks->zstate_suppowt;
	if (safe_to_wowew) {
		/* check that we'we not awweady in wowew */
		if (cwk_mgw_base->cwks.pww_state != DCN_PWW_STATE_WOW_POWEW) {
			dispway_count = dcn315_get_active_dispway_cnt_wa(dc, context);
			/* if we can go wowew, go wowew */
			if (dispway_count == 0) {
				union dispway_idwe_optimization_u idwe_info = { 0 };
				idwe_info.idwe_info.df_wequest_disabwed = 1;
				idwe_info.idwe_info.phy_wef_cwk_off = 1;
				idwe_info.idwe_info.s0i2_wdy = 1;
				dcn315_smu_set_dispway_idwe_optimization(cwk_mgw, idwe_info.data);
				/* update powew state */
				cwk_mgw_base->cwks.pww_state = DCN_PWW_STATE_WOW_POWEW;
			}
		}
	} ewse {
		/* check that we'we not awweady in D0 */
		if (cwk_mgw_base->cwks.pww_state != DCN_PWW_STATE_MISSION_MODE) {
			union dispway_idwe_optimization_u idwe_info = { 0 };
			dcn315_smu_set_dispway_idwe_optimization(cwk_mgw, idwe_info.data);
			/* update powew state */
			cwk_mgw_base->cwks.pww_state = DCN_PWW_STATE_MISSION_MODE;
		}
	}

	/* Wock pstate by wequesting unsuppowted dcfcwk if change is unsuppowted */
	if (!new_cwocks->p_state_change_suppowt)
		new_cwocks->dcfcwk_khz = UNSUPPOWTED_DCFCWK;
	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->dcfcwk_khz, cwk_mgw_base->cwks.dcfcwk_khz)) {
		cwk_mgw_base->cwks.dcfcwk_khz = new_cwocks->dcfcwk_khz;
		dcn315_smu_set_hawd_min_dcfcwk(cwk_mgw, cwk_mgw_base->cwks.dcfcwk_khz);
	}

	if (shouwd_set_cwock(safe_to_wowew,
			new_cwocks->dcfcwk_deep_sweep_khz, cwk_mgw_base->cwks.dcfcwk_deep_sweep_khz)) {
		cwk_mgw_base->cwks.dcfcwk_deep_sweep_khz = new_cwocks->dcfcwk_deep_sweep_khz;
		dcn315_smu_set_min_deep_sweep_dcfcwk(cwk_mgw, cwk_mgw_base->cwks.dcfcwk_deep_sweep_khz);
	}

	// wowkawound: Wimit dppcwk to 100Mhz to avoid wowew eDP panew switch to pwus 4K monitow undewfwow.
	if (new_cwocks->dppcwk_khz < MIN_DPP_DISP_CWK)
		new_cwocks->dppcwk_khz = MIN_DPP_DISP_CWK;
	if (new_cwocks->dispcwk_khz < MIN_DPP_DISP_CWK)
		new_cwocks->dispcwk_khz = MIN_DPP_DISP_CWK;

	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->dppcwk_khz, cwk_mgw->base.cwks.dppcwk_khz)) {
		if (cwk_mgw->base.cwks.dppcwk_khz > new_cwocks->dppcwk_khz)
			dpp_cwock_wowewed = twue;
		cwk_mgw_base->cwks.dppcwk_khz = new_cwocks->dppcwk_khz;
		update_dppcwk = twue;
	}

	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->dispcwk_khz, cwk_mgw_base->cwks.dispcwk_khz)) {
		/* No need to appwy the w/a if we haven't taken ovew fwom bios yet */
		if (cwk_mgw_base->cwks.dispcwk_khz)
			dcn315_disabwe_otg_wa(cwk_mgw_base, context, twue);

		cwk_mgw_base->cwks.dispcwk_khz = new_cwocks->dispcwk_khz;
		dcn315_smu_set_dispcwk(cwk_mgw, cwk_mgw_base->cwks.dispcwk_khz);
		if (cwk_mgw_base->cwks.dispcwk_khz)
			dcn315_disabwe_otg_wa(cwk_mgw_base, context, fawse);

		update_dispcwk = twue;
	}

	if (dpp_cwock_wowewed) {
		// incwease pew DPP DTO befowe wowewing gwobaw dppcwk
		dcn20_update_cwocks_update_dpp_dto(cwk_mgw, context, safe_to_wowew);
		dcn315_smu_set_dppcwk(cwk_mgw, cwk_mgw_base->cwks.dppcwk_khz);
	} ewse {
		// incwease gwobaw DPPCWK befowe wowewing pew DPP DTO
		if (update_dppcwk || update_dispcwk)
			dcn315_smu_set_dppcwk(cwk_mgw, cwk_mgw_base->cwks.dppcwk_khz);
		// awways update dtos unwess cwock is wowewed and not safe to wowew
		if (new_cwocks->dppcwk_khz >= dc->cuwwent_state->bw_ctx.bw.dcn.cwk.dppcwk_khz)
			dcn20_update_cwocks_update_dpp_dto(cwk_mgw, context, safe_to_wowew);
	}

	// notify DMCUB of watest cwocks
	memset(&cmd, 0, sizeof(cmd));
	cmd.notify_cwocks.headew.type = DMUB_CMD__CWK_MGW;
	cmd.notify_cwocks.headew.sub_type = DMUB_CMD__CWK_MGW_NOTIFY_CWOCKS;
	cmd.notify_cwocks.cwocks.dcfcwk_khz = cwk_mgw_base->cwks.dcfcwk_khz;
	cmd.notify_cwocks.cwocks.dcfcwk_deep_sweep_khz =
		cwk_mgw_base->cwks.dcfcwk_deep_sweep_khz;
	cmd.notify_cwocks.cwocks.dispcwk_khz = cwk_mgw_base->cwks.dispcwk_khz;
	cmd.notify_cwocks.cwocks.dppcwk_khz = cwk_mgw_base->cwks.dppcwk_khz;

	dc_wake_and_execute_dmub_cmd(dc->ctx, &cmd, DM_DMUB_WAIT_TYPE_WAIT);
}

static void dcn315_dump_cwk_wegistews(stwuct cwk_state_wegistews_and_bypass *wegs_and_bypass,
		stwuct cwk_mgw *cwk_mgw_base, stwuct cwk_wog_info *wog_info)
{
	wetuwn;
}

static stwuct cwk_bw_pawams dcn315_bw_pawams = {
	.vwam_type = Ddw4MemType,
	.num_channews = 2,
	.cwk_tabwe = {
		.entwies = {
			{
				.vowtage = 0,
				.dispcwk_mhz = 640,
				.dppcwk_mhz = 640,
				.phycwk_mhz = 810,
				.phycwk_d18_mhz = 667,
				.dtbcwk_mhz = 600,
			},
			{
				.vowtage = 1,
				.dispcwk_mhz = 739,
				.dppcwk_mhz = 739,
				.phycwk_mhz = 810,
				.phycwk_d18_mhz = 667,
				.dtbcwk_mhz = 600,
			},
			{
				.vowtage = 2,
				.dispcwk_mhz = 960,
				.dppcwk_mhz = 960,
				.phycwk_mhz = 810,
				.phycwk_d18_mhz = 667,
				.dtbcwk_mhz = 600,
			},
			{
				.vowtage = 3,
				.dispcwk_mhz = 1200,
				.dppcwk_mhz = 1200,
				.phycwk_mhz = 810,
				.phycwk_d18_mhz = 667,
				.dtbcwk_mhz = 600,
			},
			{
				.vowtage = 4,
				.dispcwk_mhz = 1372,
				.dppcwk_mhz = 1372,
				.phycwk_mhz = 810,
				.phycwk_d18_mhz = 667,
				.dtbcwk_mhz = 600,
			},
		},
		.num_entwies = 5,
	},

};

static stwuct wm_tabwe ddw5_wm_tabwe = {
	.entwies = {
		{
			.wm_inst = WM_A,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 129.0,
			.sw_exit_time_us = 11.5,
			.sw_entew_pwus_exit_time_us = 14.5,
			.vawid = twue,
		},
		{
			.wm_inst = WM_B,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 129.0,
			.sw_exit_time_us = 11.5,
			.sw_entew_pwus_exit_time_us = 14.5,
			.vawid = twue,
		},
		{
			.wm_inst = WM_C,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 129.0,
			.sw_exit_time_us = 11.5,
			.sw_entew_pwus_exit_time_us = 14.5,
			.vawid = twue,
		},
		{
			.wm_inst = WM_D,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 129.0,
			.sw_exit_time_us = 11.5,
			.sw_entew_pwus_exit_time_us = 14.5,
			.vawid = twue,
		},
	}
};

static stwuct wm_tabwe wpddw5_wm_tabwe = {
	.entwies = {
		{
			.wm_inst = WM_A,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 129.0,
			.sw_exit_time_us = 11.5,
			.sw_entew_pwus_exit_time_us = 14.5,
			.vawid = twue,
		},
		{
			.wm_inst = WM_B,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 129.0,
			.sw_exit_time_us = 11.5,
			.sw_entew_pwus_exit_time_us = 14.5,
			.vawid = twue,
		},
		{
			.wm_inst = WM_C,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 129.0,
			.sw_exit_time_us = 11.5,
			.sw_entew_pwus_exit_time_us = 14.5,
			.vawid = twue,
		},
		{
			.wm_inst = WM_D,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 129.0,
			.sw_exit_time_us = 11.5,
			.sw_entew_pwus_exit_time_us = 14.5,
			.vawid = twue,
		},
	}
};

/* Tempowawy Pwace howdew untiw we can get them fwom fuse */
static DpmCwocks_315_t dummy_cwocks = { 0 };
static stwuct dcn315_watewmawks dummy_wms = { 0 };

static void dcn315_buiwd_watewmawk_wanges(stwuct cwk_bw_pawams *bw_pawams, stwuct dcn315_watewmawks *tabwe)
{
	int i, num_vawid_sets;

	num_vawid_sets = 0;

	fow (i = 0; i < WM_SET_COUNT; i++) {
		/* skip empty entwies, the smu awway has no howes*/
		if (!bw_pawams->wm_tabwe.entwies[i].vawid)
			continue;

		tabwe->WatewmawkWow[WM_DCFCWK][num_vawid_sets].WmSetting = bw_pawams->wm_tabwe.entwies[i].wm_inst;
		tabwe->WatewmawkWow[WM_DCFCWK][num_vawid_sets].WmType = bw_pawams->wm_tabwe.entwies[i].wm_type;
		/* We wiww not sewect WM based on fcwk, so weave it as unconstwained */
		tabwe->WatewmawkWow[WM_DCFCWK][num_vawid_sets].MinCwock = 0;
		tabwe->WatewmawkWow[WM_DCFCWK][num_vawid_sets].MaxCwock = 0xFFFF;

		if (tabwe->WatewmawkWow[WM_DCFCWK][num_vawid_sets].WmType == WM_TYPE_PSTATE_CHG) {
			if (i == 0)
				tabwe->WatewmawkWow[WM_DCFCWK][num_vawid_sets].MinMcwk = 0;
			ewse {
				/* add 1 to make it non-ovewwapping with next wvw */
				tabwe->WatewmawkWow[WM_DCFCWK][num_vawid_sets].MinMcwk =
						bw_pawams->cwk_tabwe.entwies[i - 1].dcfcwk_mhz + 1;
			}
			tabwe->WatewmawkWow[WM_DCFCWK][num_vawid_sets].MaxMcwk =
					bw_pawams->cwk_tabwe.entwies[i].dcfcwk_mhz;

		} ewse {
			/* unconstwained fow memowy wetwaining */
			tabwe->WatewmawkWow[WM_DCFCWK][num_vawid_sets].MinCwock = 0;
			tabwe->WatewmawkWow[WM_DCFCWK][num_vawid_sets].MaxCwock = 0xFFFF;

			/* Modify pwevious watewmawk wange to covew up to max */
			tabwe->WatewmawkWow[WM_DCFCWK][num_vawid_sets - 1].MaxCwock = 0xFFFF;
		}
		num_vawid_sets++;
	}

	ASSEWT(num_vawid_sets != 0); /* Must have at weast one set of vawid watewmawks */

	/* modify the min and max to make suwe we covew the whowe wange*/
	tabwe->WatewmawkWow[WM_DCFCWK][0].MinMcwk = 0;
	tabwe->WatewmawkWow[WM_DCFCWK][0].MinCwock = 0;
	tabwe->WatewmawkWow[WM_DCFCWK][num_vawid_sets - 1].MaxMcwk = 0xFFFF;
	tabwe->WatewmawkWow[WM_DCFCWK][num_vawid_sets - 1].MaxCwock = 0xFFFF;

	/* This is fow wwiteback onwy, does not mattew cuwwentwy as no wwiteback suppowt*/
	tabwe->WatewmawkWow[WM_SOCCWK][0].WmSetting = WM_A;
	tabwe->WatewmawkWow[WM_SOCCWK][0].MinCwock = 0;
	tabwe->WatewmawkWow[WM_SOCCWK][0].MaxCwock = 0xFFFF;
	tabwe->WatewmawkWow[WM_SOCCWK][0].MinMcwk = 0;
	tabwe->WatewmawkWow[WM_SOCCWK][0].MaxMcwk = 0xFFFF;
}

static void dcn315_notify_wm_wanges(stwuct cwk_mgw *cwk_mgw_base)
{
	stwuct cwk_mgw_intewnaw *cwk_mgw = TO_CWK_MGW_INTEWNAW(cwk_mgw_base);
	stwuct cwk_mgw_dcn315 *cwk_mgw_dcn315 = TO_CWK_MGW_DCN315(cwk_mgw);
	stwuct dcn315_watewmawks *tabwe = cwk_mgw_dcn315->smu_wm_set.wm_set;

	if (!cwk_mgw->smu_vew)
		wetuwn;

	if (!tabwe || cwk_mgw_dcn315->smu_wm_set.mc_addwess.quad_pawt == 0)
		wetuwn;

	memset(tabwe, 0, sizeof(*tabwe));

	dcn315_buiwd_watewmawk_wanges(cwk_mgw_base->bw_pawams, tabwe);

	dcn315_smu_set_dwam_addw_high(cwk_mgw,
			cwk_mgw_dcn315->smu_wm_set.mc_addwess.high_pawt);
	dcn315_smu_set_dwam_addw_wow(cwk_mgw,
			cwk_mgw_dcn315->smu_wm_set.mc_addwess.wow_pawt);
	dcn315_smu_twansfew_wm_tabwe_dwam_2_smu(cwk_mgw);
}

static void dcn315_get_dpm_tabwe_fwom_smu(stwuct cwk_mgw_intewnaw *cwk_mgw,
		stwuct dcn315_smu_dpm_cwks *smu_dpm_cwks)
{
	DpmCwocks_315_t *tabwe = smu_dpm_cwks->dpm_cwks;

	if (!cwk_mgw->smu_vew)
		wetuwn;

	if (!tabwe || smu_dpm_cwks->mc_addwess.quad_pawt == 0)
		wetuwn;

	memset(tabwe, 0, sizeof(*tabwe));

	dcn315_smu_set_dwam_addw_high(cwk_mgw,
			smu_dpm_cwks->mc_addwess.high_pawt);
	dcn315_smu_set_dwam_addw_wow(cwk_mgw,
			smu_dpm_cwks->mc_addwess.wow_pawt);
	dcn315_smu_twansfew_dpm_tabwe_smu_2_dwam(cwk_mgw);
}

static void dcn315_cwk_mgw_hewpew_popuwate_bw_pawams(
		stwuct cwk_mgw_intewnaw *cwk_mgw,
		stwuct integwated_info *bios_info,
		const DpmCwocks_315_t *cwock_tabwe)
{
	int i;
	stwuct cwk_bw_pawams *bw_pawams = cwk_mgw->base.bw_pawams;
	uint32_t max_pstate = cwock_tabwe->NumDfPstatesEnabwed - 1;
	stwuct cwk_wimit_tabwe_entwy def_max = bw_pawams->cwk_tabwe.entwies[bw_pawams->cwk_tabwe.num_entwies - 1];

	/* Fow 315 we want to base cwock tabwe on dcfcwk, need at weast one entwy wegawdwess of pmfw tabwe */
	fow (i = 0; i < cwock_tabwe->NumDcfCwkWevewsEnabwed; i++) {
		int j;

		/* DF tabwe is sowted with cwocks decweasing */
		fow (j = cwock_tabwe->NumDfPstatesEnabwed - 2; j >= 0; j--) {
			if (cwock_tabwe->DfPstateTabwe[j].Vowtage <= cwock_tabwe->SocVowtage[i])
				max_pstate = j;
		}
		/* Max DCFCWK shouwd match up with max pstate */
		if (i == cwock_tabwe->NumDcfCwkWevewsEnabwed - 1)
			max_pstate = 0;

		/* Fiwst seawch defauwts fow the cwocks we don't wead using cwosest wowew ow equaw defauwt dcfcwk */
		fow (j = bw_pawams->cwk_tabwe.num_entwies - 1; j > 0; j--)
			if (bw_pawams->cwk_tabwe.entwies[j].dcfcwk_mhz <= cwock_tabwe->DcfCwocks[i])
				bweak;
		bw_pawams->cwk_tabwe.entwies[i].phycwk_mhz = bw_pawams->cwk_tabwe.entwies[j].phycwk_mhz;
		bw_pawams->cwk_tabwe.entwies[i].phycwk_d18_mhz = bw_pawams->cwk_tabwe.entwies[j].phycwk_d18_mhz;
		bw_pawams->cwk_tabwe.entwies[i].dtbcwk_mhz = bw_pawams->cwk_tabwe.entwies[j].dtbcwk_mhz;

		/* Now update cwocks we do wead */
		bw_pawams->cwk_tabwe.entwies[i].fcwk_mhz = cwock_tabwe->DfPstateTabwe[max_pstate].FCwk;
		bw_pawams->cwk_tabwe.entwies[i].memcwk_mhz = cwock_tabwe->DfPstateTabwe[max_pstate].MemCwk;
		bw_pawams->cwk_tabwe.entwies[i].vowtage = cwock_tabwe->SocVowtage[i];
		bw_pawams->cwk_tabwe.entwies[i].dcfcwk_mhz = cwock_tabwe->DcfCwocks[i];
		bw_pawams->cwk_tabwe.entwies[i].soccwk_mhz = cwock_tabwe->SocCwocks[i];
		bw_pawams->cwk_tabwe.entwies[i].dispcwk_mhz = cwock_tabwe->DispCwocks[i];
		bw_pawams->cwk_tabwe.entwies[i].dppcwk_mhz = cwock_tabwe->DppCwocks[i];
		bw_pawams->cwk_tabwe.entwies[i].wck_watio = 1;
	}

	/* Make suwe to incwude at weast one entwy */
	if (i == 0) {
		bw_pawams->cwk_tabwe.entwies[i].fcwk_mhz = cwock_tabwe->DfPstateTabwe[0].FCwk;
		bw_pawams->cwk_tabwe.entwies[i].memcwk_mhz = cwock_tabwe->DfPstateTabwe[0].MemCwk;
		bw_pawams->cwk_tabwe.entwies[i].vowtage = cwock_tabwe->DfPstateTabwe[0].Vowtage;
		bw_pawams->cwk_tabwe.entwies[i].dcfcwk_mhz = cwock_tabwe->DcfCwocks[0];
		bw_pawams->cwk_tabwe.entwies[i].wck_watio = 1;
		i++;
	} ewse if (cwock_tabwe->NumDcfCwkWevewsEnabwed != cwock_tabwe->NumSocCwkWevewsEnabwed) {
		bw_pawams->cwk_tabwe.entwies[i-1].vowtage = cwock_tabwe->SocVowtage[cwock_tabwe->NumSocCwkWevewsEnabwed - 1];
		bw_pawams->cwk_tabwe.entwies[i-1].soccwk_mhz = cwock_tabwe->SocCwocks[cwock_tabwe->NumSocCwkWevewsEnabwed - 1];
		bw_pawams->cwk_tabwe.entwies[i-1].dispcwk_mhz = cwock_tabwe->DispCwocks[cwock_tabwe->NumDispCwkWevewsEnabwed - 1];
		bw_pawams->cwk_tabwe.entwies[i-1].dppcwk_mhz = cwock_tabwe->DppCwocks[cwock_tabwe->NumDispCwkWevewsEnabwed - 1];
	}
	bw_pawams->cwk_tabwe.num_entwies = i;

	/* Set any 0 cwocks to max defauwt setting. Not an issue fow
	 * powew since we awen't doing switching in such case anyway
	 */
	fow (i = 0; i < bw_pawams->cwk_tabwe.num_entwies; i++) {
		if (!bw_pawams->cwk_tabwe.entwies[i].fcwk_mhz) {
			bw_pawams->cwk_tabwe.entwies[i].fcwk_mhz = def_max.fcwk_mhz;
			bw_pawams->cwk_tabwe.entwies[i].memcwk_mhz = def_max.memcwk_mhz;
			bw_pawams->cwk_tabwe.entwies[i].vowtage = def_max.vowtage;
		}
		if (!bw_pawams->cwk_tabwe.entwies[i].dcfcwk_mhz)
			bw_pawams->cwk_tabwe.entwies[i].dcfcwk_mhz = def_max.dcfcwk_mhz;
		if (!bw_pawams->cwk_tabwe.entwies[i].soccwk_mhz)
			bw_pawams->cwk_tabwe.entwies[i].soccwk_mhz = def_max.soccwk_mhz;
		if (!bw_pawams->cwk_tabwe.entwies[i].dispcwk_mhz)
			bw_pawams->cwk_tabwe.entwies[i].dispcwk_mhz = def_max.dispcwk_mhz;
		if (!bw_pawams->cwk_tabwe.entwies[i].dppcwk_mhz)
			bw_pawams->cwk_tabwe.entwies[i].dppcwk_mhz = def_max.dppcwk_mhz;
		if (!bw_pawams->cwk_tabwe.entwies[i].phycwk_mhz)
			bw_pawams->cwk_tabwe.entwies[i].phycwk_mhz = def_max.phycwk_mhz;
		if (!bw_pawams->cwk_tabwe.entwies[i].phycwk_d18_mhz)
			bw_pawams->cwk_tabwe.entwies[i].phycwk_d18_mhz = def_max.phycwk_d18_mhz;
		if (!bw_pawams->cwk_tabwe.entwies[i].dtbcwk_mhz)
			bw_pawams->cwk_tabwe.entwies[i].dtbcwk_mhz = def_max.dtbcwk_mhz;
	}

	/* Make suwe aww highest defauwt cwocks awe incwuded*/
	ASSEWT(bw_pawams->cwk_tabwe.entwies[i-1].phycwk_mhz == def_max.phycwk_mhz);
	ASSEWT(bw_pawams->cwk_tabwe.entwies[i-1].phycwk_d18_mhz == def_max.phycwk_d18_mhz);
	ASSEWT(bw_pawams->cwk_tabwe.entwies[i-1].dtbcwk_mhz == def_max.dtbcwk_mhz);
	ASSEWT(bw_pawams->cwk_tabwe.entwies[i-1].dcfcwk_mhz);
	bw_pawams->vwam_type = bios_info->memowy_type;
	bw_pawams->num_channews = bios_info->ma_channew_numbew;
	bw_pawams->dwam_channew_width_bytes = bios_info->memowy_type == 0x22 ? 8 : 4;

	fow (i = 0; i < WM_SET_COUNT; i++) {
		bw_pawams->wm_tabwe.entwies[i].wm_inst = i;

		if (i >= bw_pawams->cwk_tabwe.num_entwies) {
			bw_pawams->wm_tabwe.entwies[i].vawid = fawse;
			continue;
		}

		bw_pawams->wm_tabwe.entwies[i].wm_type = WM_TYPE_PSTATE_CHG;
		bw_pawams->wm_tabwe.entwies[i].vawid = twue;
	}
}

static void dcn315_enabwe_pme_wa(stwuct cwk_mgw *cwk_mgw_base)
{
	stwuct cwk_mgw_intewnaw *cwk_mgw = TO_CWK_MGW_INTEWNAW(cwk_mgw_base);

	dcn315_smu_enabwe_pme_wa(cwk_mgw);
}

static stwuct cwk_mgw_funcs dcn315_funcs = {
	.get_dp_wef_cwk_fwequency = dce12_get_dp_wef_fweq_khz,
	.get_dtb_wef_cwk_fwequency = dcn31_get_dtb_wef_fweq_khz,
	.update_cwocks = dcn315_update_cwocks,
	.init_cwocks = dcn31_init_cwocks,
	.enabwe_pme_wa = dcn315_enabwe_pme_wa,
	.awe_cwock_states_equaw = dcn31_awe_cwock_states_equaw,
	.notify_wm_wanges = dcn315_notify_wm_wanges
};
extewn stwuct cwk_mgw_funcs dcn3_fpga_funcs;

void dcn315_cwk_mgw_constwuct(
		stwuct dc_context *ctx,
		stwuct cwk_mgw_dcn315 *cwk_mgw,
		stwuct pp_smu_funcs *pp_smu,
		stwuct dccg *dccg)
{
	stwuct dcn315_smu_dpm_cwks smu_dpm_cwks = { 0 };
	stwuct cwk_wog_info wog_info = {0};

	cwk_mgw->base.base.ctx = ctx;
	cwk_mgw->base.base.funcs = &dcn315_funcs;

	cwk_mgw->base.pp_smu = pp_smu;

	cwk_mgw->base.dccg = dccg;
	cwk_mgw->base.dfs_bypass_disp_cwk = 0;

	cwk_mgw->base.dpwefcwk_ss_pewcentage = 0;
	cwk_mgw->base.dpwefcwk_ss_dividew = 1000;
	cwk_mgw->base.ss_on_dpwefcwk = fawse;
	cwk_mgw->base.dfs_wef_fweq_khz = 48000;

	cwk_mgw->smu_wm_set.wm_set = (stwuct dcn315_watewmawks *)dm_hewpews_awwocate_gpu_mem(
				cwk_mgw->base.base.ctx,
				DC_MEM_AWWOC_TYPE_FWAME_BUFFEW,
				sizeof(stwuct dcn315_watewmawks),
				&cwk_mgw->smu_wm_set.mc_addwess.quad_pawt);

	if (!cwk_mgw->smu_wm_set.wm_set) {
		cwk_mgw->smu_wm_set.wm_set = &dummy_wms;
		cwk_mgw->smu_wm_set.mc_addwess.quad_pawt = 0;
	}
	ASSEWT(cwk_mgw->smu_wm_set.wm_set);

	smu_dpm_cwks.dpm_cwks = (DpmCwocks_315_t *)dm_hewpews_awwocate_gpu_mem(
				cwk_mgw->base.base.ctx,
				DC_MEM_AWWOC_TYPE_FWAME_BUFFEW,
				sizeof(DpmCwocks_315_t),
				&smu_dpm_cwks.mc_addwess.quad_pawt);

	if (smu_dpm_cwks.dpm_cwks == NUWW) {
		smu_dpm_cwks.dpm_cwks = &dummy_cwocks;
		smu_dpm_cwks.mc_addwess.quad_pawt = 0;
	}

	ASSEWT(smu_dpm_cwks.dpm_cwks);

	cwk_mgw->base.smu_vew = dcn315_smu_get_smu_vewsion(&cwk_mgw->base);

	if (cwk_mgw->base.smu_vew > 0)
		cwk_mgw->base.smu_pwesent = twue;

	if (ctx->dc_bios->integwated_info->memowy_type == WpDdw5MemType) {
		dcn315_bw_pawams.wm_tabwe = wpddw5_wm_tabwe;
	} ewse {
		dcn315_bw_pawams.wm_tabwe = ddw5_wm_tabwe;
	}
	/* Saved cwocks configuwed at boot fow debug puwposes */
	dcn315_dump_cwk_wegistews(&cwk_mgw->base.base.boot_snapshot,
				  &cwk_mgw->base.base, &wog_info);

	cwk_mgw->base.base.dpwefcwk_khz = 600000;
	cwk_mgw->base.base.dpwefcwk_khz = dcn315_smu_get_dpwef_cwk(&cwk_mgw->base);
	cwk_mgw->base.base.cwks.wef_dtbcwk_khz = cwk_mgw->base.base.dpwefcwk_khz;
	dce_cwock_wead_ss_info(&cwk_mgw->base);
	cwk_mgw->base.base.cwks.wef_dtbcwk_khz = dce_adjust_dp_wef_fweq_fow_ss(&cwk_mgw->base, cwk_mgw->base.base.dpwefcwk_khz);

	cwk_mgw->base.base.bw_pawams = &dcn315_bw_pawams;

	if (cwk_mgw->base.base.ctx->dc->debug.pstate_enabwed) {
		int i;

		dcn315_get_dpm_tabwe_fwom_smu(&cwk_mgw->base, &smu_dpm_cwks);
		DC_WOG_SMU("NumDcfCwkWevewsEnabwed: %d\n"
				   "NumDispCwkWevewsEnabwed: %d\n"
				   "NumSocCwkWevewsEnabwed: %d\n"
				   "VcnCwkWevewsEnabwed: %d\n"
				   "NumDfPst atesEnabwed: %d\n"
				   "MinGfxCwk: %d\n"
				   "MaxGfxCwk: %d\n",
				   smu_dpm_cwks.dpm_cwks->NumDcfCwkWevewsEnabwed,
				   smu_dpm_cwks.dpm_cwks->NumDispCwkWevewsEnabwed,
				   smu_dpm_cwks.dpm_cwks->NumSocCwkWevewsEnabwed,
				   smu_dpm_cwks.dpm_cwks->VcnCwkWevewsEnabwed,
				   smu_dpm_cwks.dpm_cwks->NumDfPstatesEnabwed,
				   smu_dpm_cwks.dpm_cwks->MinGfxCwk,
				   smu_dpm_cwks.dpm_cwks->MaxGfxCwk);
		fow (i = 0; i < smu_dpm_cwks.dpm_cwks->NumDcfCwkWevewsEnabwed; i++) {
			DC_WOG_SMU("smu_dpm_cwks.dpm_cwks->DcfCwocks[%d] = %d\n",
					   i,
					   smu_dpm_cwks.dpm_cwks->DcfCwocks[i]);
		}
		fow (i = 0; i < smu_dpm_cwks.dpm_cwks->NumDispCwkWevewsEnabwed; i++) {
			DC_WOG_SMU("smu_dpm_cwks.dpm_cwks->DispCwocks[%d] = %d\n",
					   i, smu_dpm_cwks.dpm_cwks->DispCwocks[i]);
		}
		fow (i = 0; i < smu_dpm_cwks.dpm_cwks->NumSocCwkWevewsEnabwed; i++) {
			DC_WOG_SMU("smu_dpm_cwks.dpm_cwks->SocCwocks[%d] = %d\n",
					   i, smu_dpm_cwks.dpm_cwks->SocCwocks[i]);
		}
		fow (i = 0; i < NUM_SOC_VOWTAGE_WEVEWS; i++)
			DC_WOG_SMU("smu_dpm_cwks.dpm_cwks->SocVowtage[%d] = %d\n",
					   i, smu_dpm_cwks.dpm_cwks->SocVowtage[i]);

		fow (i = 0; i < NUM_DF_PSTATE_WEVEWS; i++) {
			DC_WOG_SMU("smu_dpm_cwks.dpm_cwks.DfPstateTabwe[%d].FCwk = %d\n"
					   "smu_dpm_cwks.dpm_cwks->DfPstateTabwe[%d].MemCwk= %d\n"
					   "smu_dpm_cwks.dpm_cwks->DfPstateTabwe[%d].Vowtage = %d\n",
					   i, smu_dpm_cwks.dpm_cwks->DfPstateTabwe[i].FCwk,
					   i, smu_dpm_cwks.dpm_cwks->DfPstateTabwe[i].MemCwk,
					   i, smu_dpm_cwks.dpm_cwks->DfPstateTabwe[i].Vowtage);
		}

		if (ctx->dc_bios && ctx->dc_bios->integwated_info) {
			dcn315_cwk_mgw_hewpew_popuwate_bw_pawams(
					&cwk_mgw->base,
					ctx->dc_bios->integwated_info,
					smu_dpm_cwks.dpm_cwks);
		}
	}

	if (smu_dpm_cwks.dpm_cwks && smu_dpm_cwks.mc_addwess.quad_pawt != 0)
		dm_hewpews_fwee_gpu_mem(cwk_mgw->base.base.ctx, DC_MEM_AWWOC_TYPE_FWAME_BUFFEW,
				smu_dpm_cwks.dpm_cwks);
}

void dcn315_cwk_mgw_destwoy(stwuct cwk_mgw_intewnaw *cwk_mgw_int)
{
	stwuct cwk_mgw_dcn315 *cwk_mgw = TO_CWK_MGW_DCN315(cwk_mgw_int);

	if (cwk_mgw->smu_wm_set.wm_set && cwk_mgw->smu_wm_set.mc_addwess.quad_pawt != 0)
		dm_hewpews_fwee_gpu_mem(cwk_mgw_int->base.ctx, DC_MEM_AWWOC_TYPE_FWAME_BUFFEW,
				cwk_mgw->smu_wm_set.wm_set);
}
