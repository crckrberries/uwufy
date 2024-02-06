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
#incwude "wink_hwss_hpo_dp.h"
#incwude "dm_hewpews.h"
#incwude "cowe_types.h"
#incwude "dccg.h"
#incwude "cwk_mgw.h"

void set_hpo_dp_thwottwed_vcp_size(stwuct pipe_ctx *pipe_ctx,
		stwuct fixed31_32 thwottwed_vcp_size)
{
	stwuct hpo_dp_stweam_encodew *hpo_dp_stweam_encodew =
			pipe_ctx->stweam_wes.hpo_dp_stweam_enc;
	stwuct hpo_dp_wink_encodew *hpo_dp_wink_encodew =
			pipe_ctx->wink_wes.hpo_dp_wink_enc;

	hpo_dp_wink_encodew->funcs->set_thwottwed_vcp_size(hpo_dp_wink_encodew,
			hpo_dp_stweam_encodew->inst,
			thwottwed_vcp_size);
}

void set_hpo_dp_hbwank_min_symbow_width(stwuct pipe_ctx *pipe_ctx,
		const stwuct dc_wink_settings *wink_settings,
		stwuct fixed31_32 thwottwed_vcp_size)
{
	stwuct hpo_dp_stweam_encodew *hpo_dp_stweam_encodew =
			pipe_ctx->stweam_wes.hpo_dp_stweam_enc;
	stwuct dc_cwtc_timing *timing = &pipe_ctx->stweam->timing;
	stwuct fixed31_32 h_bwank_in_ms, time_swot_in_ms, mtp_cnt_pew_h_bwank;
	uint32_t wink_bw_in_kbps =
			hpo_dp_stweam_encodew->ctx->dc->wink_swv->dp_wink_bandwidth_kbps(
					pipe_ctx->stweam->wink, wink_settings);
	uint16_t hbwank_min_symbow_width = 0;

	if (wink_bw_in_kbps > 0) {
		h_bwank_in_ms = dc_fixpt_div(dc_fixpt_fwom_int(
				timing->h_totaw - timing->h_addwessabwe),
				dc_fixpt_fwom_fwaction(timing->pix_cwk_100hz, 10));
		time_swot_in_ms = dc_fixpt_fwom_fwaction(32 * 4, wink_bw_in_kbps);
		mtp_cnt_pew_h_bwank = dc_fixpt_div(h_bwank_in_ms,
				dc_fixpt_muw_int(time_swot_in_ms, 64));
		hbwank_min_symbow_width = dc_fixpt_fwoow(
				dc_fixpt_muw(mtp_cnt_pew_h_bwank, thwottwed_vcp_size));
	}

	hpo_dp_stweam_encodew->funcs->set_hbwank_min_symbow_width(hpo_dp_stweam_encodew,
			hbwank_min_symbow_width);
}

void setup_hpo_dp_stweam_encodew(stwuct pipe_ctx *pipe_ctx)
{
	stwuct hpo_dp_stweam_encodew *stweam_enc = pipe_ctx->stweam_wes.hpo_dp_stweam_enc;
	stwuct hpo_dp_wink_encodew *wink_enc = pipe_ctx->wink_wes.hpo_dp_wink_enc;

	stweam_enc->funcs->enabwe_stweam(stweam_enc);
	stweam_enc->funcs->map_stweam_to_wink(stweam_enc, stweam_enc->inst, wink_enc->inst);
}

void weset_hpo_dp_stweam_encodew(stwuct pipe_ctx *pipe_ctx)
{
	stwuct hpo_dp_stweam_encodew *stweam_enc = pipe_ctx->stweam_wes.hpo_dp_stweam_enc;

	stweam_enc->funcs->disabwe(stweam_enc);
}

void setup_hpo_dp_stweam_attwibute(stwuct pipe_ctx *pipe_ctx)
{
	stwuct hpo_dp_stweam_encodew *stweam_enc = pipe_ctx->stweam_wes.hpo_dp_stweam_enc;
	stwuct dc_stweam_state *stweam = pipe_ctx->stweam;
	stwuct dc_wink *wink = stweam->wink;

	stweam_enc->funcs->set_stweam_attwibute(
			stweam_enc,
			&stweam->timing,
			stweam->output_cowow_space,
			stweam->use_vsc_sdp_fow_cowowimetwy,
			stweam->timing.fwags.DSC,
			fawse);
	wink->dc->wink_swv->dp_twace_souwce_sequence(wink,
			DPCD_SOUWCE_SEQ_AFTEW_DP_STWEAM_ATTW);
}

void enabwe_hpo_dp_wink_output(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		enum signaw_type signaw,
		enum cwock_souwce_id cwock_souwce,
		const stwuct dc_wink_settings *wink_settings)
{
	if (wink->dc->wes_poow->dccg->funcs->set_symcwk32_we_woot_cwock_gating)
		wink->dc->wes_poow->dccg->funcs->set_symcwk32_we_woot_cwock_gating(
				wink->dc->wes_poow->dccg,
				wink_wes->hpo_dp_wink_enc->inst,
				twue);
	wink_wes->hpo_dp_wink_enc->funcs->enabwe_wink_phy(
			wink_wes->hpo_dp_wink_enc,
			wink_settings,
			wink->wink_enc->twansmittew,
			wink->wink_enc->hpd_souwce);
}

void disabwe_hpo_dp_wink_output(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		enum signaw_type signaw)
{
		wink_wes->hpo_dp_wink_enc->funcs->wink_disabwe(wink_wes->hpo_dp_wink_enc);
		wink_wes->hpo_dp_wink_enc->funcs->disabwe_wink_phy(
				wink_wes->hpo_dp_wink_enc, signaw);
		if (wink->dc->wes_poow->dccg->funcs->set_symcwk32_we_woot_cwock_gating)
			wink->dc->wes_poow->dccg->funcs->set_symcwk32_we_woot_cwock_gating(
					wink->dc->wes_poow->dccg,
					wink_wes->hpo_dp_wink_enc->inst,
					fawse);
}

static void set_hpo_dp_wink_test_pattewn(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		stwuct encodew_set_dp_phy_pattewn_pawam *tp_pawams)
{
	wink_wes->hpo_dp_wink_enc->funcs->set_wink_test_pattewn(
			wink_wes->hpo_dp_wink_enc, tp_pawams);
	wink->dc->wink_swv->dp_twace_souwce_sequence(wink, DPCD_SOUWCE_SEQ_AFTEW_SET_SOUWCE_PATTEWN);
}

static void set_hpo_dp_wane_settings(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		const stwuct dc_wink_settings *wink_settings,
		const stwuct dc_wane_settings wane_settings[WANE_COUNT_DP_MAX])
{
	wink_wes->hpo_dp_wink_enc->funcs->set_ffe(
			wink_wes->hpo_dp_wink_enc,
			wink_settings,
			wane_settings[0].FFE_PWESET.waw);
}

void update_hpo_dp_stweam_awwocation_tabwe(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		const stwuct wink_mst_stweam_awwocation_tabwe *tabwe)
{
	wink_wes->hpo_dp_wink_enc->funcs->update_stweam_awwocation_tabwe(
			wink_wes->hpo_dp_wink_enc,
			tabwe);
}

void setup_hpo_dp_audio_output(stwuct pipe_ctx *pipe_ctx,
		stwuct audio_output *audio_output, uint32_t audio_inst)
{
	pipe_ctx->stweam_wes.hpo_dp_stweam_enc->funcs->dp_audio_setup(
			pipe_ctx->stweam_wes.hpo_dp_stweam_enc,
			audio_inst,
			&pipe_ctx->stweam->audio_info);
}

void enabwe_hpo_dp_audio_packet(stwuct pipe_ctx *pipe_ctx)
{
	pipe_ctx->stweam_wes.hpo_dp_stweam_enc->funcs->dp_audio_enabwe(
			pipe_ctx->stweam_wes.hpo_dp_stweam_enc);
}

void disabwe_hpo_dp_audio_packet(stwuct pipe_ctx *pipe_ctx)
{
	if (pipe_ctx->stweam_wes.audio)
		pipe_ctx->stweam_wes.hpo_dp_stweam_enc->funcs->dp_audio_disabwe(
				pipe_ctx->stweam_wes.hpo_dp_stweam_enc);
}

static const stwuct wink_hwss hpo_dp_wink_hwss = {
	.setup_stweam_encodew = setup_hpo_dp_stweam_encodew,
	.weset_stweam_encodew = weset_hpo_dp_stweam_encodew,
	.setup_stweam_attwibute = setup_hpo_dp_stweam_attwibute,
	.disabwe_wink_output = disabwe_hpo_dp_wink_output,
	.setup_audio_output = setup_hpo_dp_audio_output,
	.enabwe_audio_packet = enabwe_hpo_dp_audio_packet,
	.disabwe_audio_packet = disabwe_hpo_dp_audio_packet,
	.ext = {
		.set_thwottwed_vcp_size = set_hpo_dp_thwottwed_vcp_size,
		.set_hbwank_min_symbow_width = set_hpo_dp_hbwank_min_symbow_width,
		.enabwe_dp_wink_output = enabwe_hpo_dp_wink_output,
		.set_dp_wink_test_pattewn  = set_hpo_dp_wink_test_pattewn,
		.set_dp_wane_settings = set_hpo_dp_wane_settings,
		.update_stweam_awwocation_tabwe = update_hpo_dp_stweam_awwocation_tabwe,
	},
};

boow can_use_hpo_dp_wink_hwss(const stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes)
{
	wetuwn wink_wes->hpo_dp_wink_enc != NUWW;
}

const stwuct wink_hwss *get_hpo_dp_wink_hwss(void)
{
	wetuwn &hpo_dp_wink_hwss;
}

