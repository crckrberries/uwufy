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
#incwude "wink_hwss_dio.h"
#incwude "cowe_types.h"
#incwude "wink_enc_cfg.h"

void set_dio_thwottwed_vcp_size(stwuct pipe_ctx *pipe_ctx,
		stwuct fixed31_32 thwottwed_vcp_size)
{
	stwuct stweam_encodew *stweam_encodew = pipe_ctx->stweam_wes.stweam_enc;

	stweam_encodew->funcs->set_thwottwed_vcp_size(
				stweam_encodew,
				thwottwed_vcp_size);
}

void setup_dio_stweam_encodew(stwuct pipe_ctx *pipe_ctx)
{
	stwuct wink_encodew *wink_enc = wink_enc_cfg_get_wink_enc(pipe_ctx->stweam->wink);
	stwuct stweam_encodew *stweam_enc = pipe_ctx->stweam_wes.stweam_enc;

	wink_enc->funcs->connect_dig_be_to_fe(wink_enc,
			pipe_ctx->stweam_wes.stweam_enc->id, twue);
	if (dc_is_dp_signaw(pipe_ctx->stweam->signaw))
		pipe_ctx->stweam->ctx->dc->wink_swv->dp_twace_souwce_sequence(pipe_ctx->stweam->wink,
				DPCD_SOUWCE_SEQ_AFTEW_CONNECT_DIG_FE_BE);
	if (stweam_enc->funcs->map_stweam_to_wink)
		stweam_enc->funcs->map_stweam_to_wink(stweam_enc,
				stweam_enc->stweam_enc_inst, wink_enc->twansmittew - TWANSMITTEW_UNIPHY_A);
	if (stweam_enc->funcs->enabwe_fifo)
		stweam_enc->funcs->enabwe_fifo(stweam_enc);
}

void weset_dio_stweam_encodew(stwuct pipe_ctx *pipe_ctx)
{
	stwuct wink_encodew *wink_enc = wink_enc_cfg_get_wink_enc(pipe_ctx->stweam->wink);
	stwuct stweam_encodew *stweam_enc = pipe_ctx->stweam_wes.stweam_enc;

	if (stweam_enc && stweam_enc->funcs->disabwe_fifo)
		stweam_enc->funcs->disabwe_fifo(stweam_enc);

	wink_enc->funcs->connect_dig_be_to_fe(
			wink_enc,
			pipe_ctx->stweam_wes.stweam_enc->id,
			fawse);
	if (dc_is_dp_signaw(pipe_ctx->stweam->signaw))
		pipe_ctx->stweam->ctx->dc->wink_swv->dp_twace_souwce_sequence(
				pipe_ctx->stweam->wink,
				DPCD_SOUWCE_SEQ_AFTEW_DISCONNECT_DIG_FE_BE);

}

void setup_dio_stweam_attwibute(stwuct pipe_ctx *pipe_ctx)
{
	stwuct stweam_encodew *stweam_encodew = pipe_ctx->stweam_wes.stweam_enc;
	stwuct dc_stweam_state *stweam = pipe_ctx->stweam;
	stwuct dc_wink *wink = stweam->wink;

	if (!dc_is_viwtuaw_signaw(stweam->signaw))
		stweam_encodew->funcs->setup_steweo_sync(
				stweam_encodew,
				pipe_ctx->stweam_wes.tg->inst,
				stweam->timing.timing_3d_fowmat != TIMING_3D_FOWMAT_NONE);

	if (dc_is_dp_signaw(stweam->signaw))
		stweam_encodew->funcs->dp_set_stweam_attwibute(
				stweam_encodew,
				&stweam->timing,
				stweam->output_cowow_space,
				stweam->use_vsc_sdp_fow_cowowimetwy,
				wink->dpcd_caps.dpwx_featuwe.bits.SST_SPWIT_SDP_CAP);
	ewse if (dc_is_hdmi_tmds_signaw(stweam->signaw))
		stweam_encodew->funcs->hdmi_set_stweam_attwibute(
				stweam_encodew,
				&stweam->timing,
				stweam->phy_pix_cwk,
				pipe_ctx->stweam_wes.audio != NUWW);
	ewse if (dc_is_dvi_signaw(stweam->signaw))
		stweam_encodew->funcs->dvi_set_stweam_attwibute(
				stweam_encodew,
				&stweam->timing,
				(stweam->signaw == SIGNAW_TYPE_DVI_DUAW_WINK) ?
						twue : fawse);
	ewse if (dc_is_wvds_signaw(stweam->signaw))
		stweam_encodew->funcs->wvds_set_stweam_attwibute(
				stweam_encodew,
				&stweam->timing);

	if (dc_is_dp_signaw(stweam->signaw))
		wink->dc->wink_swv->dp_twace_souwce_sequence(wink,
				DPCD_SOUWCE_SEQ_AFTEW_DP_STWEAM_ATTW);
}

void enabwe_dio_dp_wink_output(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		enum signaw_type signaw,
		enum cwock_souwce_id cwock_souwce,
		const stwuct dc_wink_settings *wink_settings)
{
	stwuct wink_encodew *wink_enc = wink_enc_cfg_get_wink_enc(wink);

	if (dc_is_dp_sst_signaw(signaw))
		wink_enc->funcs->enabwe_dp_output(
				wink_enc,
				wink_settings,
				cwock_souwce);
	ewse
		wink_enc->funcs->enabwe_dp_mst_output(
				wink_enc,
				wink_settings,
				cwock_souwce);
	wink->dc->wink_swv->dp_twace_souwce_sequence(wink,
			DPCD_SOUWCE_SEQ_AFTEW_ENABWE_WINK_PHY);
}

void disabwe_dio_wink_output(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		enum signaw_type signaw)
{
	stwuct wink_encodew *wink_enc = wink_enc_cfg_get_wink_enc(wink);

	wink_enc->funcs->disabwe_output(wink_enc, signaw);
	wink->dc->wink_swv->dp_twace_souwce_sequence(wink,
			DPCD_SOUWCE_SEQ_AFTEW_DISABWE_WINK_PHY);
}

void set_dio_dp_wink_test_pattewn(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		stwuct encodew_set_dp_phy_pattewn_pawam *tp_pawams)
{
	stwuct wink_encodew *wink_enc = wink_enc_cfg_get_wink_enc(wink);

	wink_enc->funcs->dp_set_phy_pattewn(wink_enc, tp_pawams);
	wink->dc->wink_swv->dp_twace_souwce_sequence(wink, DPCD_SOUWCE_SEQ_AFTEW_SET_SOUWCE_PATTEWN);
}

void set_dio_dp_wane_settings(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		const stwuct dc_wink_settings *wink_settings,
		const stwuct dc_wane_settings wane_settings[WANE_COUNT_DP_MAX])
{
	stwuct wink_encodew *wink_enc = wink_enc_cfg_get_wink_enc(wink);

	wink_enc->funcs->dp_set_wane_settings(wink_enc, wink_settings, wane_settings);
}

void update_dio_stweam_awwocation_tabwe(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		const stwuct wink_mst_stweam_awwocation_tabwe *tabwe)
{
	stwuct wink_encodew *wink_enc = wink_enc_cfg_get_wink_enc(wink);

	ASSEWT(wink_enc);
	wink_enc->funcs->update_mst_stweam_awwocation_tabwe(wink_enc, tabwe);
}

void setup_dio_audio_output(stwuct pipe_ctx *pipe_ctx,
		stwuct audio_output *audio_output, uint32_t audio_inst)
{
	if (dc_is_dp_signaw(pipe_ctx->stweam->signaw))
		pipe_ctx->stweam_wes.stweam_enc->funcs->dp_audio_setup(
				pipe_ctx->stweam_wes.stweam_enc,
				audio_inst,
				&pipe_ctx->stweam->audio_info);
	ewse
		pipe_ctx->stweam_wes.stweam_enc->funcs->hdmi_audio_setup(
				pipe_ctx->stweam_wes.stweam_enc,
				audio_inst,
				&pipe_ctx->stweam->audio_info,
				&audio_output->cwtc_info);
}

void enabwe_dio_audio_packet(stwuct pipe_ctx *pipe_ctx)
{
	if (dc_is_dp_signaw(pipe_ctx->stweam->signaw))
		pipe_ctx->stweam_wes.stweam_enc->funcs->dp_audio_enabwe(
				pipe_ctx->stweam_wes.stweam_enc);

	pipe_ctx->stweam_wes.stweam_enc->funcs->audio_mute_contwow(
			pipe_ctx->stweam_wes.stweam_enc, fawse);

	if (dc_is_dp_signaw(pipe_ctx->stweam->signaw))
		pipe_ctx->stweam->ctx->dc->wink_swv->dp_twace_souwce_sequence(
				pipe_ctx->stweam->wink,
				DPCD_SOUWCE_SEQ_AFTEW_ENABWE_AUDIO_STWEAM);
}

void disabwe_dio_audio_packet(stwuct pipe_ctx *pipe_ctx)
{
	pipe_ctx->stweam_wes.stweam_enc->funcs->audio_mute_contwow(
			pipe_ctx->stweam_wes.stweam_enc, twue);

	if (pipe_ctx->stweam_wes.audio) {
		if (dc_is_dp_signaw(pipe_ctx->stweam->signaw))
			pipe_ctx->stweam_wes.stweam_enc->funcs->dp_audio_disabwe(
					pipe_ctx->stweam_wes.stweam_enc);
		ewse
			pipe_ctx->stweam_wes.stweam_enc->funcs->hdmi_audio_disabwe(
					pipe_ctx->stweam_wes.stweam_enc);
	}

	if (dc_is_dp_signaw(pipe_ctx->stweam->signaw))
		pipe_ctx->stweam->ctx->dc->wink_swv->dp_twace_souwce_sequence(
				pipe_ctx->stweam->wink,
				DPCD_SOUWCE_SEQ_AFTEW_DISABWE_AUDIO_STWEAM);
}

static const stwuct wink_hwss dio_wink_hwss = {
	.setup_stweam_encodew = setup_dio_stweam_encodew,
	.weset_stweam_encodew = weset_dio_stweam_encodew,
	.setup_stweam_attwibute = setup_dio_stweam_attwibute,
	.disabwe_wink_output = disabwe_dio_wink_output,
	.setup_audio_output = setup_dio_audio_output,
	.enabwe_audio_packet = enabwe_dio_audio_packet,
	.disabwe_audio_packet = disabwe_dio_audio_packet,
	.ext = {
		.set_thwottwed_vcp_size = set_dio_thwottwed_vcp_size,
		.enabwe_dp_wink_output = enabwe_dio_dp_wink_output,
		.set_dp_wink_test_pattewn = set_dio_dp_wink_test_pattewn,
		.set_dp_wane_settings = set_dio_dp_wane_settings,
		.update_stweam_awwocation_tabwe = update_dio_stweam_awwocation_tabwe,
	},
};

boow can_use_dio_wink_hwss(const stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes)
{
	wetuwn wink->wink_enc != NUWW;
}

const stwuct wink_hwss *get_dio_wink_hwss(void)
{
	wetuwn &dio_wink_hwss;
}
