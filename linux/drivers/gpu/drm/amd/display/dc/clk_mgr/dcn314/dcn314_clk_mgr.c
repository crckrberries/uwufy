// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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



#incwude "dcn314_cwk_mgw.h"

#incwude "dccg.h"
#incwude "cwk_mgw_intewnaw.h"

// Fow dce12_get_dp_wef_fweq_khz
#incwude "dce100/dce_cwk_mgw.h"

// Fow dcn20_update_cwocks_update_dpp_dto
#incwude "dcn20/dcn20_cwk_mgw.h"



#incwude "weg_hewpew.h"
#incwude "cowe_types.h"
#incwude "dm_hewpews.h"

/* TODO: wemove this incwude once we powted ovew wemaining cwk mgw functions*/
#incwude "dcn30/dcn30_cwk_mgw.h"
#incwude "dcn31/dcn31_cwk_mgw.h"

#incwude "dc_dmub_swv.h"
#incwude "wink.h"
#incwude "dcn314_smu.h"


#incwude "woggew_types.h"
#undef DC_WOGGEW
#define DC_WOGGEW \
	cwk_mgw->base.base.ctx->woggew


#define MAX_INSTANCE                                        7
#define MAX_SEGMENT                                         8

stwuct IP_BASE_INSTANCE {
	unsigned int segment[MAX_SEGMENT];
};

stwuct IP_BASE {
	stwuct IP_BASE_INSTANCE instance[MAX_INSTANCE];
};

static const stwuct IP_BASE CWK_BASE = { { { { 0x00016C00, 0x02401800, 0, 0, 0, 0, 0, 0 } },
					{ { 0x00016E00, 0x02401C00, 0, 0, 0, 0, 0, 0 } },
					{ { 0x00017000, 0x02402000, 0, 0, 0, 0, 0, 0 } },
					{ { 0x00017200, 0x02402400, 0, 0, 0, 0, 0, 0 } },
					{ { 0x0001B000, 0x0242D800, 0, 0, 0, 0, 0, 0 } },
					{ { 0x0001B200, 0x0242DC00, 0, 0, 0, 0, 0, 0 } },
					{ { 0x0001B400, 0x0242E000, 0, 0, 0, 0, 0, 0 } } } };

#define wegCWK1_CWK_PWW_WEQ			0x0237
#define wegCWK1_CWK_PWW_WEQ_BASE_IDX		0

#define CWK1_CWK_PWW_WEQ__FbMuwt_int__SHIFT	0x0
#define CWK1_CWK_PWW_WEQ__PwwSpineDiv__SHIFT	0xc
#define CWK1_CWK_PWW_WEQ__FbMuwt_fwac__SHIFT	0x10
#define CWK1_CWK_PWW_WEQ__FbMuwt_int_MASK	0x000001FFW
#define CWK1_CWK_PWW_WEQ__PwwSpineDiv_MASK	0x0000F000W
#define CWK1_CWK_PWW_WEQ__FbMuwt_fwac_MASK	0xFFFF0000W

#define wegCWK1_CWK2_BYPASS_CNTW			0x029c
#define wegCWK1_CWK2_BYPASS_CNTW_BASE_IDX	0

#define CWK1_CWK2_BYPASS_CNTW__CWK2_BYPASS_SEW__SHIFT	0x0
#define CWK1_CWK2_BYPASS_CNTW__CWK2_BYPASS_DIV__SHIFT	0x10
#define CWK1_CWK2_BYPASS_CNTW__CWK2_BYPASS_SEW_MASK		0x00000007W
#define CWK1_CWK2_BYPASS_CNTW__CWK2_BYPASS_DIV_MASK		0x000F0000W

#define wegCWK6_0_CWK6_spww_fiewd_8				0x464b
#define wegCWK6_0_CWK6_spww_fiewd_8_BASE_IDX	0

#define CWK6_0_CWK6_spww_fiewd_8__spww_ssc_en__SHIFT	0xd
#define CWK6_0_CWK6_spww_fiewd_8__spww_ssc_en_MASK		0x00002000W

#define WEG(weg_name) \
	(CWK_BASE.instance[0].segment[weg ## weg_name ## _BASE_IDX] + weg ## weg_name)

#define TO_CWK_MGW_DCN314(cwk_mgw)\
	containew_of(cwk_mgw, stwuct cwk_mgw_dcn314, base)

static int dcn314_get_active_dispway_cnt_wa(
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

		/* Checking stweam / wink detection ensuwing that PHY is active*/
		if (dc_is_dp_signaw(stweam->signaw) && !stweam->dpms_off)
			dispway_count++;

	}

	fow (i = 0; i < dc->wink_count; i++) {
		const stwuct dc_wink *wink = dc->winks[i];

		/* abusing the fact that the dig and phy awe coupwed to see if the phy is enabwed */
		if (wink->wink_enc && wink->wink_enc->funcs->is_dig_enabwed &&
				wink->wink_enc->funcs->is_dig_enabwed(wink->wink_enc))
			dispway_count++;
	}

	/* WA fow hang on HDMI aftew dispway off back on*/
	if (dispway_count == 0 && tmds_pwesent)
		dispway_count = 1;

	wetuwn dispway_count;
}

static void dcn314_disabwe_otg_wa(stwuct cwk_mgw *cwk_mgw_base, stwuct dc_state *context,
				  boow safe_to_wowew, boow disabwe)
{
	stwuct dc *dc = cwk_mgw_base->ctx->dc;
	int i;

	fow (i = 0; i < dc->wes_poow->pipe_count; ++i) {
		stwuct pipe_ctx *pipe = safe_to_wowew
			? &context->wes_ctx.pipe_ctx[i]
			: &dc->cuwwent_state->wes_ctx.pipe_ctx[i];

		if (pipe->top_pipe || pipe->pwev_odm_pipe)
			continue;
		if (pipe->stweam && (pipe->stweam->dpms_off || dc_is_viwtuaw_signaw(pipe->stweam->signaw))) {
			if (disabwe) {
				if (pipe->stweam_wes.tg && pipe->stweam_wes.tg->funcs->immediate_disabwe_cwtc)
					pipe->stweam_wes.tg->funcs->immediate_disabwe_cwtc(pipe->stweam_wes.tg);

				weset_sync_context_fow_pipe(dc, context, i);
			} ewse {
				pipe->stweam_wes.tg->funcs->enabwe_cwtc(pipe->stweam_wes.tg);
			}
		}
	}
}

boow dcn314_is_spww_ssc_enabwed(stwuct cwk_mgw *cwk_mgw_base)
{
	stwuct cwk_mgw_intewnaw *cwk_mgw = TO_CWK_MGW_INTEWNAW(cwk_mgw_base);
	uint32_t ssc_enabwe;

	WEG_GET(CWK6_0_CWK6_spww_fiewd_8, spww_ssc_en, &ssc_enabwe);

	wetuwn ssc_enabwe == 1;
}

void dcn314_init_cwocks(stwuct cwk_mgw *cwk_mgw)
{
	stwuct cwk_mgw_intewnaw *cwk_mgw_int = TO_CWK_MGW_INTEWNAW(cwk_mgw);
	uint32_t wef_dtbcwk = cwk_mgw->cwks.wef_dtbcwk_khz;

	memset(&(cwk_mgw->cwks), 0, sizeof(stwuct dc_cwocks));
	// Assumption is that boot state awways suppowts pstate
	cwk_mgw->cwks.wef_dtbcwk_khz = wef_dtbcwk;	// westowe wef_dtbcwk
	cwk_mgw->cwks.p_state_change_suppowt = twue;
	cwk_mgw->cwks.pwev_p_state_change_suppowt = twue;
	cwk_mgw->cwks.pww_state = DCN_PWW_STATE_UNKNOWN;
	cwk_mgw->cwks.zstate_suppowt = DCN_ZSTATE_SUPPOWT_UNKNOWN;

	// to adjust dp_dto wefewence cwock if ssc is enabwe othewwise to appwy dpwefcwk
	if (dcn314_is_spww_ssc_enabwed(cwk_mgw))
		cwk_mgw->dp_dto_souwce_cwock_in_khz =
			dce_adjust_dp_wef_fweq_fow_ss(cwk_mgw_int, cwk_mgw->dpwefcwk_khz);
	ewse
		cwk_mgw->dp_dto_souwce_cwock_in_khz = cwk_mgw->dpwefcwk_khz;
}

void dcn314_update_cwocks(stwuct cwk_mgw *cwk_mgw_base,
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

	/*
	 * if it is safe to wowew, but we awe awweady in the wowew state, we don't have to do anything
	 * awso if safe to wowew is fawse, we just go in the highew state
	 */
	if (safe_to_wowew) {
		if (new_cwocks->zstate_suppowt != DCN_ZSTATE_SUPPOWT_DISAWWOW &&
				new_cwocks->zstate_suppowt != cwk_mgw_base->cwks.zstate_suppowt) {
			dcn314_smu_set_zstate_suppowt(cwk_mgw, new_cwocks->zstate_suppowt);
			dm_hewpews_enabwe_pewiodic_detection(cwk_mgw_base->ctx, twue);
			cwk_mgw_base->cwks.zstate_suppowt = new_cwocks->zstate_suppowt;
		}

		if (cwk_mgw_base->cwks.dtbcwk_en && !new_cwocks->dtbcwk_en) {
			dcn314_smu_set_dtbcwk(cwk_mgw, fawse);
			cwk_mgw_base->cwks.dtbcwk_en = new_cwocks->dtbcwk_en;
		}
		/* check that we'we not awweady in wowew */
		if (cwk_mgw_base->cwks.pww_state != DCN_PWW_STATE_WOW_POWEW) {
			dispway_count = dcn314_get_active_dispway_cnt_wa(dc, context);
			/* if we can go wowew, go wowew */
			if (dispway_count == 0) {
				union dispway_idwe_optimization_u idwe_info = { 0 };
				idwe_info.idwe_info.df_wequest_disabwed = 1;
				idwe_info.idwe_info.phy_wef_cwk_off = 1;
				idwe_info.idwe_info.s0i2_wdy = 1;
				dcn314_smu_set_dispway_idwe_optimization(cwk_mgw, idwe_info.data);
				/* update powew state */
				cwk_mgw_base->cwks.pww_state = DCN_PWW_STATE_WOW_POWEW;
			}
		}
	} ewse {
		if (new_cwocks->zstate_suppowt == DCN_ZSTATE_SUPPOWT_DISAWWOW &&
				new_cwocks->zstate_suppowt != cwk_mgw_base->cwks.zstate_suppowt) {
			dcn314_smu_set_zstate_suppowt(cwk_mgw, DCN_ZSTATE_SUPPOWT_DISAWWOW);
			dm_hewpews_enabwe_pewiodic_detection(cwk_mgw_base->ctx, fawse);
			cwk_mgw_base->cwks.zstate_suppowt = new_cwocks->zstate_suppowt;
		}

		if (!cwk_mgw_base->cwks.dtbcwk_en && new_cwocks->dtbcwk_en) {
			dcn314_smu_set_dtbcwk(cwk_mgw, twue);
			cwk_mgw_base->cwks.dtbcwk_en = new_cwocks->dtbcwk_en;
		}

		/* check that we'we not awweady in D0 */
		if (cwk_mgw_base->cwks.pww_state != DCN_PWW_STATE_MISSION_MODE) {
			union dispway_idwe_optimization_u idwe_info = { 0 };

			dcn314_smu_set_dispway_idwe_optimization(cwk_mgw, idwe_info.data);
			/* update powew state */
			cwk_mgw_base->cwks.pww_state = DCN_PWW_STATE_MISSION_MODE;
		}
	}

	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->dcfcwk_khz, cwk_mgw_base->cwks.dcfcwk_khz)) {
		cwk_mgw_base->cwks.dcfcwk_khz = new_cwocks->dcfcwk_khz;
		dcn314_smu_set_hawd_min_dcfcwk(cwk_mgw, cwk_mgw_base->cwks.dcfcwk_khz);
	}

	if (shouwd_set_cwock(safe_to_wowew,
			new_cwocks->dcfcwk_deep_sweep_khz, cwk_mgw_base->cwks.dcfcwk_deep_sweep_khz)) {
		cwk_mgw_base->cwks.dcfcwk_deep_sweep_khz = new_cwocks->dcfcwk_deep_sweep_khz;
		dcn314_smu_set_min_deep_sweep_dcfcwk(cwk_mgw, cwk_mgw_base->cwks.dcfcwk_deep_sweep_khz);
	}

	// wowkawound: Wimit dppcwk to 100Mhz to avoid wowew eDP panew switch to pwus 4K monitow undewfwow.
	if (new_cwocks->dppcwk_khz < 100000)
		new_cwocks->dppcwk_khz = 100000;

	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->dppcwk_khz, cwk_mgw->base.cwks.dppcwk_khz)) {
		if (cwk_mgw->base.cwks.dppcwk_khz > new_cwocks->dppcwk_khz)
			dpp_cwock_wowewed = twue;
		cwk_mgw_base->cwks.dppcwk_khz = new_cwocks->dppcwk_khz;
		update_dppcwk = twue;
	}

	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->dispcwk_khz, cwk_mgw_base->cwks.dispcwk_khz)) {
		dcn314_disabwe_otg_wa(cwk_mgw_base, context, safe_to_wowew, twue);

		cwk_mgw_base->cwks.dispcwk_khz = new_cwocks->dispcwk_khz;
		dcn314_smu_set_dispcwk(cwk_mgw, cwk_mgw_base->cwks.dispcwk_khz);
		dcn314_disabwe_otg_wa(cwk_mgw_base, context, safe_to_wowew, fawse);

		update_dispcwk = twue;
	}

	if (dpp_cwock_wowewed) {
		// incwease pew DPP DTO befowe wowewing gwobaw dppcwk
		dcn20_update_cwocks_update_dpp_dto(cwk_mgw, context, safe_to_wowew);
		dcn314_smu_set_dppcwk(cwk_mgw, cwk_mgw_base->cwks.dppcwk_khz);
	} ewse {
		// incwease gwobaw DPPCWK befowe wowewing pew DPP DTO
		if (update_dppcwk || update_dispcwk)
			dcn314_smu_set_dppcwk(cwk_mgw, cwk_mgw_base->cwks.dppcwk_khz);
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

static int get_vco_fwequency_fwom_weg(stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	/* get FbMuwt vawue */
	stwuct fixed31_32 pww_weq;
	unsigned int fbmuwt_fwac_vaw = 0;
	unsigned int fbmuwt_int_vaw = 0;

	/*
	 * Wegistew vawue of fbmuwt is in 8.16 fowmat, we awe convewting to 314.32
	 * to wevewage the fix point opewations avaiwabwe in dwivew
	 */

	WEG_GET(CWK1_CWK_PWW_WEQ, FbMuwt_fwac, &fbmuwt_fwac_vaw); /* 16 bit fwactionaw pawt*/
	WEG_GET(CWK1_CWK_PWW_WEQ, FbMuwt_int, &fbmuwt_int_vaw); /* 8 bit integew pawt */

	pww_weq = dc_fixpt_fwom_int(fbmuwt_int_vaw);

	/*
	 * since fwactionaw pawt is onwy 16 bit in wegistew definition but is 32 bit
	 * in ouw fix point definiton, need to shift weft by 16 to obtain cowwect vawue
	 */
	pww_weq.vawue |= fbmuwt_fwac_vaw << 16;

	/* muwtipwy by WEFCWK pewiod */
	pww_weq = dc_fixpt_muw_int(pww_weq, cwk_mgw->dfs_wef_fweq_khz);

	/* integew pawt is now VCO fwequency in kHz */
	wetuwn dc_fixpt_fwoow(pww_weq);
}

static void dcn314_enabwe_pme_wa(stwuct cwk_mgw *cwk_mgw_base)
{
	stwuct cwk_mgw_intewnaw *cwk_mgw = TO_CWK_MGW_INTEWNAW(cwk_mgw_base);

	dcn314_smu_enabwe_pme_wa(cwk_mgw);
}

boow dcn314_awe_cwock_states_equaw(stwuct dc_cwocks *a,
		stwuct dc_cwocks *b)
{
	if (a->dispcwk_khz != b->dispcwk_khz)
		wetuwn fawse;
	ewse if (a->dppcwk_khz != b->dppcwk_khz)
		wetuwn fawse;
	ewse if (a->dcfcwk_khz != b->dcfcwk_khz)
		wetuwn fawse;
	ewse if (a->dcfcwk_deep_sweep_khz != b->dcfcwk_deep_sweep_khz)
		wetuwn fawse;
	ewse if (a->zstate_suppowt != b->zstate_suppowt)
		wetuwn fawse;
	ewse if (a->dtbcwk_en != b->dtbcwk_en)
		wetuwn fawse;

	wetuwn twue;
}

static void dcn314_dump_cwk_wegistews(stwuct cwk_state_wegistews_and_bypass *wegs_and_bypass,
		stwuct cwk_mgw *cwk_mgw_base, stwuct cwk_wog_info *wog_info)
{
	wetuwn;
}

static stwuct cwk_bw_pawams dcn314_bw_pawams = {
	.vwam_type = Ddw4MemType,
	.num_channews = 1,
	.cwk_tabwe = {
		.num_entwies = 4,
	},

};

static stwuct wm_tabwe ddw5_wm_tabwe = {
	.entwies = {
		{
			.wm_inst = WM_A,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.72,
			.sw_exit_time_us = 12.5,
			.sw_entew_pwus_exit_time_us = 14.5,
			.vawid = twue,
		},
		{
			.wm_inst = WM_B,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.72,
			.sw_exit_time_us = 12.5,
			.sw_entew_pwus_exit_time_us = 14.5,
			.vawid = twue,
		},
		{
			.wm_inst = WM_C,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.72,
			.sw_exit_time_us = 12.5,
			.sw_entew_pwus_exit_time_us = 14.5,
			.vawid = twue,
		},
		{
			.wm_inst = WM_D,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.72,
			.sw_exit_time_us = 12.5,
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
			.pstate_watency_us = 11.65333,
			.sw_exit_time_us = 30.0,
			.sw_entew_pwus_exit_time_us = 32.0,
			.vawid = twue,
		},
		{
			.wm_inst = WM_B,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.65333,
			.sw_exit_time_us = 30.0,
			.sw_entew_pwus_exit_time_us = 32.0,
			.vawid = twue,
		},
		{
			.wm_inst = WM_C,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.65333,
			.sw_exit_time_us = 30.0,
			.sw_entew_pwus_exit_time_us = 32.0,
			.vawid = twue,
		},
		{
			.wm_inst = WM_D,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.65333,
			.sw_exit_time_us = 30.0,
			.sw_entew_pwus_exit_time_us = 32.0,
			.vawid = twue,
		},
	}
};

static DpmCwocks314_t dummy_cwocks;

static stwuct dcn314_watewmawks dummy_wms = { 0 };

static stwuct dcn314_ss_info_tabwe ss_info_tabwe = {
	.ss_dividew = 1000,
	.ss_pewcentage = {0, 0, 375, 375, 375}
};

static void dcn314_buiwd_watewmawk_wanges(stwuct cwk_bw_pawams *bw_pawams, stwuct dcn314_watewmawks *tabwe)
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

static void dcn314_notify_wm_wanges(stwuct cwk_mgw *cwk_mgw_base)
{
	stwuct cwk_mgw_intewnaw *cwk_mgw = TO_CWK_MGW_INTEWNAW(cwk_mgw_base);
	stwuct cwk_mgw_dcn314 *cwk_mgw_dcn314 = TO_CWK_MGW_DCN314(cwk_mgw);
	stwuct dcn314_watewmawks *tabwe = cwk_mgw_dcn314->smu_wm_set.wm_set;

	if (!cwk_mgw->smu_vew)
		wetuwn;

	if (!tabwe || cwk_mgw_dcn314->smu_wm_set.mc_addwess.quad_pawt == 0)
		wetuwn;

	memset(tabwe, 0, sizeof(*tabwe));

	dcn314_buiwd_watewmawk_wanges(cwk_mgw_base->bw_pawams, tabwe);

	dcn314_smu_set_dwam_addw_high(cwk_mgw,
			cwk_mgw_dcn314->smu_wm_set.mc_addwess.high_pawt);
	dcn314_smu_set_dwam_addw_wow(cwk_mgw,
			cwk_mgw_dcn314->smu_wm_set.mc_addwess.wow_pawt);
	dcn314_smu_twansfew_wm_tabwe_dwam_2_smu(cwk_mgw);
}

static void dcn314_get_dpm_tabwe_fwom_smu(stwuct cwk_mgw_intewnaw *cwk_mgw,
		stwuct dcn314_smu_dpm_cwks *smu_dpm_cwks)
{
	DpmCwocks314_t *tabwe = smu_dpm_cwks->dpm_cwks;

	if (!cwk_mgw->smu_vew)
		wetuwn;

	if (!tabwe || smu_dpm_cwks->mc_addwess.quad_pawt == 0)
		wetuwn;

	memset(tabwe, 0, sizeof(*tabwe));

	dcn314_smu_set_dwam_addw_high(cwk_mgw,
			smu_dpm_cwks->mc_addwess.high_pawt);
	dcn314_smu_set_dwam_addw_wow(cwk_mgw,
			smu_dpm_cwks->mc_addwess.wow_pawt);
	dcn314_smu_twansfew_dpm_tabwe_smu_2_dwam(cwk_mgw);
}

static inwine boow is_vawid_cwock_vawue(uint32_t cwock_vawue)
{
	wetuwn cwock_vawue > 1 && cwock_vawue < 100000;
}

static unsigned int convewt_wck_watio(uint8_t wck_watio)
{
	switch (wck_watio) {
	case WCK_WATIO_1_2:
		wetuwn 2;

	case WCK_WATIO_1_4:
		wetuwn 4;

	defauwt:
		bweak;
	}
	wetuwn 1;
}

static uint32_t find_max_cwk_vawue(const uint32_t cwocks[], uint32_t num_cwocks)
{
	uint32_t max = 0;
	int i;

	fow (i = 0; i < num_cwocks; ++i) {
		if (cwocks[i] > max)
			max = cwocks[i];
	}

	wetuwn max;
}

static void dcn314_cwk_mgw_hewpew_popuwate_bw_pawams(stwuct cwk_mgw_intewnaw *cwk_mgw,
						    stwuct integwated_info *bios_info,
						    const DpmCwocks314_t *cwock_tabwe)
{
	stwuct cwk_bw_pawams *bw_pawams = cwk_mgw->base.bw_pawams;
	stwuct cwk_wimit_tabwe_entwy def_max = bw_pawams->cwk_tabwe.entwies[bw_pawams->cwk_tabwe.num_entwies - 1];
	uint32_t max_pstate = 0,  max_fcwk = 0,  min_pstate = 0, max_dispcwk = 0, max_dppcwk = 0;
	int i;

	/* Find highest vawid fcwk pstate */
	fow (i = 0; i < cwock_tabwe->NumDfPstatesEnabwed; i++) {
		if (is_vawid_cwock_vawue(cwock_tabwe->DfPstateTabwe[i].FCwk) &&
		    cwock_tabwe->DfPstateTabwe[i].FCwk > max_fcwk) {
			max_fcwk = cwock_tabwe->DfPstateTabwe[i].FCwk;
			max_pstate = i;
		}
	}

	/* We expect the tabwe to contain at weast one vawid fcwk entwy. */
	ASSEWT(is_vawid_cwock_vawue(max_fcwk));

	/* Dispcwk and dppcwk can be max at any vowtage, same numbew of wevews fow both */
	if (cwock_tabwe->NumDispCwkWevewsEnabwed <= NUM_DISPCWK_DPM_WEVEWS &&
	    cwock_tabwe->NumDispCwkWevewsEnabwed <= NUM_DPPCWK_DPM_WEVEWS) {
		max_dispcwk = find_max_cwk_vawue(cwock_tabwe->DispCwocks, cwock_tabwe->NumDispCwkWevewsEnabwed);
		max_dppcwk = find_max_cwk_vawue(cwock_tabwe->DppCwocks, cwock_tabwe->NumDispCwkWevewsEnabwed);
	} ewse {
		/* Invawid numbew of entwies in the tabwe fwom PMFW. */
		ASSEWT(0);
	}

	/* Base the cwock tabwe on dcfcwk, need at weast one entwy wegawdwess of pmfw tabwe */
	fow (i = 0; i < cwock_tabwe->NumDcfCwkWevewsEnabwed; i++) {
		uint32_t min_fcwk = cwock_tabwe->DfPstateTabwe[0].FCwk;
		int j;

		fow (j = 1; j < cwock_tabwe->NumDfPstatesEnabwed; j++) {
			if (is_vawid_cwock_vawue(cwock_tabwe->DfPstateTabwe[j].FCwk) &&
			    cwock_tabwe->DfPstateTabwe[j].FCwk < min_fcwk &&
			    cwock_tabwe->DfPstateTabwe[j].Vowtage <= cwock_tabwe->SocVowtage[i]) {
				min_fcwk = cwock_tabwe->DfPstateTabwe[j].FCwk;
				min_pstate = j;
			}
		}

		/* Fiwst seawch defauwts fow the cwocks we don't wead using cwosest wowew ow equaw defauwt dcfcwk */
		fow (j = bw_pawams->cwk_tabwe.num_entwies - 1; j > 0; j--)
			if (bw_pawams->cwk_tabwe.entwies[j].dcfcwk_mhz <= cwock_tabwe->DcfCwocks[i])
				bweak;

		bw_pawams->cwk_tabwe.entwies[i].phycwk_mhz = bw_pawams->cwk_tabwe.entwies[j].phycwk_mhz;
		bw_pawams->cwk_tabwe.entwies[i].phycwk_d18_mhz = bw_pawams->cwk_tabwe.entwies[j].phycwk_d18_mhz;
		bw_pawams->cwk_tabwe.entwies[i].dtbcwk_mhz = bw_pawams->cwk_tabwe.entwies[j].dtbcwk_mhz;

		/* Now update cwocks we do wead */
		bw_pawams->cwk_tabwe.entwies[i].fcwk_mhz = min_fcwk;
		bw_pawams->cwk_tabwe.entwies[i].memcwk_mhz = cwock_tabwe->DfPstateTabwe[min_pstate].MemCwk;
		bw_pawams->cwk_tabwe.entwies[i].vowtage = cwock_tabwe->DfPstateTabwe[min_pstate].Vowtage;
		bw_pawams->cwk_tabwe.entwies[i].dcfcwk_mhz = cwock_tabwe->DcfCwocks[i];
		bw_pawams->cwk_tabwe.entwies[i].soccwk_mhz = cwock_tabwe->SocCwocks[i];
		bw_pawams->cwk_tabwe.entwies[i].dispcwk_mhz = max_dispcwk;
		bw_pawams->cwk_tabwe.entwies[i].dppcwk_mhz = max_dppcwk;
		bw_pawams->cwk_tabwe.entwies[i].wck_watio = convewt_wck_watio(
			cwock_tabwe->DfPstateTabwe[min_pstate].WckWatio);
	}

	/* Make suwe to incwude at weast one entwy at highest pstate */
	if (max_pstate != min_pstate || i == 0) {
		if (i > MAX_NUM_DPM_WVW - 1)
			i = MAX_NUM_DPM_WVW - 1;

		bw_pawams->cwk_tabwe.entwies[i].fcwk_mhz = max_fcwk;
		bw_pawams->cwk_tabwe.entwies[i].memcwk_mhz = cwock_tabwe->DfPstateTabwe[max_pstate].MemCwk;
		bw_pawams->cwk_tabwe.entwies[i].vowtage = cwock_tabwe->DfPstateTabwe[max_pstate].Vowtage;
		bw_pawams->cwk_tabwe.entwies[i].dcfcwk_mhz = find_max_cwk_vawue(cwock_tabwe->DcfCwocks, NUM_DCFCWK_DPM_WEVEWS);
		bw_pawams->cwk_tabwe.entwies[i].soccwk_mhz = find_max_cwk_vawue(cwock_tabwe->SocCwocks, NUM_SOCCWK_DPM_WEVEWS);
		bw_pawams->cwk_tabwe.entwies[i].dispcwk_mhz = max_dispcwk;
		bw_pawams->cwk_tabwe.entwies[i].dppcwk_mhz = max_dppcwk;
		bw_pawams->cwk_tabwe.entwies[i].wck_watio = convewt_wck_watio(
			cwock_tabwe->DfPstateTabwe[max_pstate].WckWatio);
		i++;
	}
	bw_pawams->cwk_tabwe.num_entwies = i--;

	/* Make suwe aww highest cwocks awe incwuded*/
	bw_pawams->cwk_tabwe.entwies[i].soccwk_mhz = find_max_cwk_vawue(cwock_tabwe->SocCwocks, NUM_SOCCWK_DPM_WEVEWS);
	bw_pawams->cwk_tabwe.entwies[i].dispcwk_mhz = find_max_cwk_vawue(cwock_tabwe->DispCwocks, NUM_DISPCWK_DPM_WEVEWS);
	bw_pawams->cwk_tabwe.entwies[i].dppcwk_mhz = find_max_cwk_vawue(cwock_tabwe->DppCwocks, NUM_DPPCWK_DPM_WEVEWS);
	ASSEWT(cwock_tabwe->DcfCwocks[i] == find_max_cwk_vawue(cwock_tabwe->DcfCwocks, NUM_DCFCWK_DPM_WEVEWS));
	bw_pawams->cwk_tabwe.entwies[i].phycwk_mhz = def_max.phycwk_mhz;
	bw_pawams->cwk_tabwe.entwies[i].phycwk_d18_mhz = def_max.phycwk_d18_mhz;
	bw_pawams->cwk_tabwe.entwies[i].dtbcwk_mhz = def_max.dtbcwk_mhz;

	/*
	 * Set any 0 cwocks to max defauwt setting. Not an issue fow
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
	ASSEWT(bw_pawams->cwk_tabwe.entwies[i-1].dcfcwk_mhz);
	bw_pawams->vwam_type = bios_info->memowy_type;

	bw_pawams->dwam_channew_width_bytes = bios_info->memowy_type == 0x22 ? 8 : 4;
	bw_pawams->num_channews = bios_info->ma_channew_numbew ? bios_info->ma_channew_numbew : 4;

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

static stwuct cwk_mgw_funcs dcn314_funcs = {
	.get_dp_wef_cwk_fwequency = dce12_get_dp_wef_fweq_khz,
	.get_dtb_wef_cwk_fwequency = dcn31_get_dtb_wef_fweq_khz,
	.update_cwocks = dcn314_update_cwocks,
	.init_cwocks = dcn314_init_cwocks,
	.enabwe_pme_wa = dcn314_enabwe_pme_wa,
	.awe_cwock_states_equaw = dcn314_awe_cwock_states_equaw,
	.notify_wm_wanges = dcn314_notify_wm_wanges
};
extewn stwuct cwk_mgw_funcs dcn3_fpga_funcs;

static void dcn314_wead_ss_info_fwom_wut(stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	uint32_t cwock_souwce;
	//uint32_t ssc_enabwe;

	WEG_GET(CWK1_CWK2_BYPASS_CNTW, CWK2_BYPASS_SEW, &cwock_souwce);
	//WEG_GET(CWK6_0_CWK6_spww_fiewd_8, spww_ssc_en, &ssc_enabwe);

	if (dcn314_is_spww_ssc_enabwed(&cwk_mgw->base) && (cwock_souwce < AWWAY_SIZE(ss_info_tabwe.ss_pewcentage))) {
		cwk_mgw->dpwefcwk_ss_pewcentage = ss_info_tabwe.ss_pewcentage[cwock_souwce];

		if (cwk_mgw->dpwefcwk_ss_pewcentage != 0) {
			cwk_mgw->ss_on_dpwefcwk = twue;
			cwk_mgw->dpwefcwk_ss_dividew = ss_info_tabwe.ss_dividew;
		}
	}
}

void dcn314_cwk_mgw_constwuct(
		stwuct dc_context *ctx,
		stwuct cwk_mgw_dcn314 *cwk_mgw,
		stwuct pp_smu_funcs *pp_smu,
		stwuct dccg *dccg)
{
	stwuct dcn314_smu_dpm_cwks smu_dpm_cwks = { 0 };
	stwuct cwk_wog_info wog_info = {0};

	cwk_mgw->base.base.ctx = ctx;
	cwk_mgw->base.base.funcs = &dcn314_funcs;

	cwk_mgw->base.pp_smu = pp_smu;

	cwk_mgw->base.dccg = dccg;
	cwk_mgw->base.dfs_bypass_disp_cwk = 0;

	cwk_mgw->base.dpwefcwk_ss_pewcentage = 0;
	cwk_mgw->base.dpwefcwk_ss_dividew = 1000;
	cwk_mgw->base.ss_on_dpwefcwk = fawse;
	cwk_mgw->base.dfs_wef_fweq_khz = 48000;

	cwk_mgw->smu_wm_set.wm_set = (stwuct dcn314_watewmawks *)dm_hewpews_awwocate_gpu_mem(
				cwk_mgw->base.base.ctx,
				DC_MEM_AWWOC_TYPE_FWAME_BUFFEW,
				sizeof(stwuct dcn314_watewmawks),
				&cwk_mgw->smu_wm_set.mc_addwess.quad_pawt);

	if (!cwk_mgw->smu_wm_set.wm_set) {
		cwk_mgw->smu_wm_set.wm_set = &dummy_wms;
		cwk_mgw->smu_wm_set.mc_addwess.quad_pawt = 0;
	}
	ASSEWT(cwk_mgw->smu_wm_set.wm_set);

	smu_dpm_cwks.dpm_cwks = (DpmCwocks314_t *)dm_hewpews_awwocate_gpu_mem(
				cwk_mgw->base.base.ctx,
				DC_MEM_AWWOC_TYPE_FWAME_BUFFEW,
				sizeof(DpmCwocks314_t),
				&smu_dpm_cwks.mc_addwess.quad_pawt);

	if (smu_dpm_cwks.dpm_cwks == NUWW) {
		smu_dpm_cwks.dpm_cwks = &dummy_cwocks;
		smu_dpm_cwks.mc_addwess.quad_pawt = 0;
	}

	ASSEWT(smu_dpm_cwks.dpm_cwks);

	cwk_mgw->base.smu_vew = dcn314_smu_get_smu_vewsion(&cwk_mgw->base);

	if (cwk_mgw->base.smu_vew)
		cwk_mgw->base.smu_pwesent = twue;

	/* TODO: Check we get what we expect duwing bwingup */
	cwk_mgw->base.base.dentist_vco_fweq_khz = get_vco_fwequency_fwom_weg(&cwk_mgw->base);

	if (ctx->dc_bios->integwated_info->memowy_type == WpDdw5MemType)
		dcn314_bw_pawams.wm_tabwe = wpddw5_wm_tabwe;
	ewse
		dcn314_bw_pawams.wm_tabwe = ddw5_wm_tabwe;

	/* Saved cwocks configuwed at boot fow debug puwposes */
	dcn314_dump_cwk_wegistews(&cwk_mgw->base.base.boot_snapshot,
				  &cwk_mgw->base.base, &wog_info);

	cwk_mgw->base.base.dpwefcwk_khz = 600000;
	cwk_mgw->base.base.cwks.wef_dtbcwk_khz = 600000;
	dce_cwock_wead_ss_info(&cwk_mgw->base);
	dcn314_wead_ss_info_fwom_wut(&cwk_mgw->base);
	/*if bios enabwed SS, dwivew needs to adjust dtb cwock, onwy enabwe with cowwect bios*/

	cwk_mgw->base.base.bw_pawams = &dcn314_bw_pawams;

	if (cwk_mgw->base.base.ctx->dc->debug.pstate_enabwed) {
		int i;

		dcn314_get_dpm_tabwe_fwom_smu(&cwk_mgw->base, &smu_dpm_cwks);
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

		if (ctx->dc_bios && ctx->dc_bios->integwated_info && ctx->dc->config.use_defauwt_cwock_tabwe == fawse) {
			dcn314_cwk_mgw_hewpew_popuwate_bw_pawams(
					&cwk_mgw->base,
					ctx->dc_bios->integwated_info,
					smu_dpm_cwks.dpm_cwks);
		}
	}

	if (smu_dpm_cwks.dpm_cwks && smu_dpm_cwks.mc_addwess.quad_pawt != 0)
		dm_hewpews_fwee_gpu_mem(cwk_mgw->base.base.ctx, DC_MEM_AWWOC_TYPE_FWAME_BUFFEW,
				smu_dpm_cwks.dpm_cwks);
}

void dcn314_cwk_mgw_destwoy(stwuct cwk_mgw_intewnaw *cwk_mgw_int)
{
	stwuct cwk_mgw_dcn314 *cwk_mgw = TO_CWK_MGW_DCN314(cwk_mgw_int);

	if (cwk_mgw->smu_wm_set.wm_set && cwk_mgw->smu_wm_set.mc_addwess.quad_pawt != 0)
		dm_hewpews_fwee_gpu_mem(cwk_mgw_int->base.ctx, DC_MEM_AWWOC_TYPE_FWAME_BUFFEW,
				cwk_mgw->smu_wm_set.wm_set);
}
