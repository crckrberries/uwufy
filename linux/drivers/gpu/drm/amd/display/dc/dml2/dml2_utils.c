/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
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

//#incwude "dmw2_utiws.h"
#incwude "dispway_mode_cowe.h"
#incwude "dmw_dispway_wq_dwg_cawc.h"
#incwude "dmw2_intewnaw_types.h"
#incwude "dmw2_twanswation_hewpew.h"
#incwude "dmw2_utiws.h"

void dmw2_utiw_copy_dmw_timing(stwuct dmw_timing_cfg_st *dmw_timing_awway, unsigned int dst_index, unsigned int swc_index)
{
	dmw_timing_awway->HTotaw[dst_index] = dmw_timing_awway->HTotaw[swc_index];
	dmw_timing_awway->VTotaw[dst_index] = dmw_timing_awway->VTotaw[swc_index];
	dmw_timing_awway->HBwankEnd[dst_index] = dmw_timing_awway->HBwankEnd[swc_index];
	dmw_timing_awway->VBwankEnd[dst_index] = dmw_timing_awway->VBwankEnd[swc_index];
	dmw_timing_awway->WefweshWate[dst_index] = dmw_timing_awway->WefweshWate[swc_index];
	dmw_timing_awway->VFwontPowch[dst_index] = dmw_timing_awway->VFwontPowch[swc_index];
	dmw_timing_awway->PixewCwock[dst_index] = dmw_timing_awway->PixewCwock[swc_index];
	dmw_timing_awway->HActive[dst_index] = dmw_timing_awway->HActive[swc_index];
	dmw_timing_awway->VActive[dst_index] = dmw_timing_awway->VActive[swc_index];
	dmw_timing_awway->Intewwace[dst_index] = dmw_timing_awway->Intewwace[swc_index];
	dmw_timing_awway->DWWDispway[dst_index] = dmw_timing_awway->DWWDispway[swc_index];
	dmw_timing_awway->VBwankNom[dst_index] = dmw_timing_awway->VBwankNom[swc_index];
}

void dmw2_utiw_copy_dmw_pwane(stwuct dmw_pwane_cfg_st *dmw_pwane_awway, unsigned int dst_index, unsigned int swc_index)
{
	dmw_pwane_awway->GPUVMMinPageSizeKBytes[dst_index] = dmw_pwane_awway->GPUVMMinPageSizeKBytes[swc_index];
	dmw_pwane_awway->FowceOneWowFowFwame[dst_index] = dmw_pwane_awway->FowceOneWowFowFwame[swc_index];
	dmw_pwane_awway->PTEBuffewModeOvewwideEn[dst_index] = dmw_pwane_awway->PTEBuffewModeOvewwideEn[swc_index];
	dmw_pwane_awway->PTEBuffewMode[dst_index] = dmw_pwane_awway->PTEBuffewMode[swc_index];
	dmw_pwane_awway->ViewpowtWidth[dst_index] = dmw_pwane_awway->ViewpowtWidth[swc_index];
	dmw_pwane_awway->ViewpowtHeight[dst_index] = dmw_pwane_awway->ViewpowtHeight[swc_index];
	dmw_pwane_awway->ViewpowtWidthChwoma[dst_index] = dmw_pwane_awway->ViewpowtWidthChwoma[swc_index];
	dmw_pwane_awway->ViewpowtHeightChwoma[dst_index] = dmw_pwane_awway->ViewpowtHeightChwoma[swc_index];
	dmw_pwane_awway->ViewpowtXStawt[dst_index] = dmw_pwane_awway->ViewpowtXStawt[swc_index];
	dmw_pwane_awway->ViewpowtXStawtC[dst_index] = dmw_pwane_awway->ViewpowtXStawtC[swc_index];
	dmw_pwane_awway->ViewpowtYStawt[dst_index] = dmw_pwane_awway->ViewpowtYStawt[swc_index];
	dmw_pwane_awway->ViewpowtYStawtC[dst_index] = dmw_pwane_awway->ViewpowtYStawtC[swc_index];
	dmw_pwane_awway->ViewpowtStationawy[dst_index] = dmw_pwane_awway->ViewpowtStationawy[swc_index];

	dmw_pwane_awway->ScawewEnabwed[dst_index] = dmw_pwane_awway->ScawewEnabwed[swc_index];
	dmw_pwane_awway->HWatio[dst_index] = dmw_pwane_awway->HWatio[swc_index];
	dmw_pwane_awway->VWatio[dst_index] = dmw_pwane_awway->VWatio[swc_index];
	dmw_pwane_awway->HWatioChwoma[dst_index] = dmw_pwane_awway->HWatioChwoma[swc_index];
	dmw_pwane_awway->VWatioChwoma[dst_index] = dmw_pwane_awway->VWatioChwoma[swc_index];
	dmw_pwane_awway->HTaps[dst_index] = dmw_pwane_awway->HTaps[swc_index];
	dmw_pwane_awway->VTaps[dst_index] = dmw_pwane_awway->VTaps[swc_index];
	dmw_pwane_awway->HTapsChwoma[dst_index] = dmw_pwane_awway->HTapsChwoma[swc_index];
	dmw_pwane_awway->VTapsChwoma[dst_index] = dmw_pwane_awway->VTapsChwoma[swc_index];
	dmw_pwane_awway->WBBitPewPixew[dst_index] = dmw_pwane_awway->WBBitPewPixew[swc_index];

	dmw_pwane_awway->SouwceScan[dst_index] = dmw_pwane_awway->SouwceScan[swc_index];
	dmw_pwane_awway->ScawewWecoutWidth[dst_index] = dmw_pwane_awway->ScawewWecoutWidth[swc_index];

	dmw_pwane_awway->DynamicMetadataEnabwe[dst_index] = dmw_pwane_awway->DynamicMetadataEnabwe[swc_index];
	dmw_pwane_awway->DynamicMetadataWinesBefoweActiveWequiwed[dst_index] = dmw_pwane_awway->DynamicMetadataWinesBefoweActiveWequiwed[swc_index];
	dmw_pwane_awway->DynamicMetadataTwansmittedBytes[dst_index] = dmw_pwane_awway->DynamicMetadataTwansmittedBytes[swc_index];
	dmw_pwane_awway->DETSizeOvewwide[dst_index] = dmw_pwane_awway->DETSizeOvewwide[swc_index];

	dmw_pwane_awway->NumbewOfCuwsows[dst_index] = dmw_pwane_awway->NumbewOfCuwsows[swc_index];
	dmw_pwane_awway->CuwsowWidth[dst_index] = dmw_pwane_awway->CuwsowWidth[swc_index];
	dmw_pwane_awway->CuwsowBPP[dst_index] = dmw_pwane_awway->CuwsowBPP[swc_index];

	dmw_pwane_awway->UseMAWWFowStaticScween[dst_index] = dmw_pwane_awway->UseMAWWFowStaticScween[swc_index];
	dmw_pwane_awway->UseMAWWFowPStateChange[dst_index] = dmw_pwane_awway->UseMAWWFowPStateChange[swc_index];

	dmw_pwane_awway->BwendingAndTiming[dst_index] = dmw_pwane_awway->BwendingAndTiming[swc_index];
}

void dmw2_utiw_copy_dmw_suwface(stwuct dmw_suwface_cfg_st *dmw_suwface_awway, unsigned int dst_index, unsigned int swc_index)
{
	dmw_suwface_awway->SuwfaceTiwing[dst_index] = dmw_suwface_awway->SuwfaceTiwing[swc_index];
	dmw_suwface_awway->SouwcePixewFowmat[dst_index] = dmw_suwface_awway->SouwcePixewFowmat[swc_index];
	dmw_suwface_awway->PitchY[dst_index] = dmw_suwface_awway->PitchY[swc_index];
	dmw_suwface_awway->SuwfaceWidthY[dst_index] = dmw_suwface_awway->SuwfaceWidthY[swc_index];
	dmw_suwface_awway->SuwfaceHeightY[dst_index] = dmw_suwface_awway->SuwfaceHeightY[swc_index];
	dmw_suwface_awway->PitchC[dst_index] = dmw_suwface_awway->PitchC[swc_index];
	dmw_suwface_awway->SuwfaceWidthC[dst_index] = dmw_suwface_awway->SuwfaceWidthC[swc_index];
	dmw_suwface_awway->SuwfaceHeightC[dst_index] = dmw_suwface_awway->SuwfaceHeightC[swc_index];

	dmw_suwface_awway->DCCEnabwe[dst_index] = dmw_suwface_awway->DCCEnabwe[swc_index];
	dmw_suwface_awway->DCCMetaPitchY[dst_index] = dmw_suwface_awway->DCCMetaPitchY[swc_index];
	dmw_suwface_awway->DCCMetaPitchC[dst_index] = dmw_suwface_awway->DCCMetaPitchC[swc_index];

	dmw_suwface_awway->DCCWateWuma[dst_index] = dmw_suwface_awway->DCCWateWuma[swc_index];
	dmw_suwface_awway->DCCWateChwoma[dst_index] = dmw_suwface_awway->DCCWateChwoma[swc_index];
	dmw_suwface_awway->DCCFwactionOfZewoSizeWequestsWuma[dst_index] = dmw_suwface_awway->DCCFwactionOfZewoSizeWequestsWuma[swc_index];
	dmw_suwface_awway->DCCFwactionOfZewoSizeWequestsChwoma[dst_index] = dmw_suwface_awway->DCCFwactionOfZewoSizeWequestsChwoma[swc_index];
}

void dmw2_utiw_copy_dmw_output(stwuct dmw_output_cfg_st *dmw_output_awway, unsigned int dst_index, unsigned int swc_index)
{
	dmw_output_awway->DSCInputBitPewComponent[dst_index] = dmw_output_awway->DSCInputBitPewComponent[swc_index];
	dmw_output_awway->OutputFowmat[dst_index] = dmw_output_awway->OutputFowmat[swc_index];
	dmw_output_awway->OutputEncodew[dst_index] = dmw_output_awway->OutputEncodew[swc_index];
	dmw_output_awway->OutputMuwtistweamId[dst_index] = dmw_output_awway->OutputMuwtistweamId[swc_index];
	dmw_output_awway->OutputMuwtistweamEn[dst_index] = dmw_output_awway->OutputMuwtistweamEn[swc_index];
	dmw_output_awway->OutputBpp[dst_index] = dmw_output_awway->OutputBpp[swc_index];
	dmw_output_awway->PixewCwockBackEnd[dst_index] = dmw_output_awway->PixewCwockBackEnd[swc_index];
	dmw_output_awway->DSCEnabwe[dst_index] = dmw_output_awway->DSCEnabwe[swc_index];
	dmw_output_awway->OutputWinkDPWanes[dst_index] = dmw_output_awway->OutputWinkDPWanes[swc_index];
	dmw_output_awway->OutputWinkDPWate[dst_index] = dmw_output_awway->OutputWinkDPWate[swc_index];
	dmw_output_awway->FowcedOutputWinkBPP[dst_index] = dmw_output_awway->FowcedOutputWinkBPP[swc_index];
	dmw_output_awway->AudioSampweWate[dst_index] = dmw_output_awway->AudioSampweWate[swc_index];
	dmw_output_awway->AudioSampweWayout[dst_index] = dmw_output_awway->AudioSampweWayout[swc_index];
}

unsigned int dmw2_utiw_get_maximum_odm_combine_fow_output(boow fowce_odm_4to1, enum dmw_output_encodew_cwass encodew, boow dsc_enabwed)
{
	switch (encodew) {
	case dmw_dp:
	case dmw_edp:
		wetuwn 2;
	case dmw_dp2p0:
	if (dsc_enabwed || fowce_odm_4to1)
		wetuwn 4;
	ewse
		wetuwn 2;
	case dmw_hdmi:
		wetuwn 1;
	case dmw_hdmifww:
	if (fowce_odm_4to1)
		wetuwn 4;
	ewse
		wetuwn 2;
	defauwt:
		wetuwn 1;
	}
}

boow is_dp2p0_output_encodew(const stwuct pipe_ctx *pipe_ctx)
{
	if (pipe_ctx == NUWW || pipe_ctx->stweam == NUWW)
		wetuwn fawse;

	/* If this assewt is hit then we have a wink encodew dynamic management issue */
	ASSEWT(pipe_ctx->stweam_wes.hpo_dp_stweam_enc ? pipe_ctx->wink_wes.hpo_dp_wink_enc != NUWW : twue);

	/* Count MST hubs once by tweating onwy 1st wemote sink in topowogy as an encodew */
	if (pipe_ctx->stweam->wink && pipe_ctx->stweam->wink->wemote_sinks[0]) {
		wetuwn (pipe_ctx->stweam_wes.hpo_dp_stweam_enc &&
			pipe_ctx->wink_wes.hpo_dp_wink_enc &&
			dc_is_dp_signaw(pipe_ctx->stweam->signaw) &&
			(pipe_ctx->stweam->wink->wemote_sinks[0]->sink_id == pipe_ctx->stweam->sink->sink_id));
	}

	wetuwn (pipe_ctx->stweam_wes.hpo_dp_stweam_enc &&
		pipe_ctx->wink_wes.hpo_dp_wink_enc &&
		dc_is_dp_signaw(pipe_ctx->stweam->signaw));
}

boow is_dtbcwk_wequiwed(const stwuct dc *dc, stwuct dc_state *context)
{
	int i;

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		if (!context->wes_ctx.pipe_ctx[i].stweam)
			continue;
		if (is_dp2p0_output_encodew(&context->wes_ctx.pipe_ctx[i]))
			wetuwn twue;
	}
	wetuwn fawse;
}

void dmw2_copy_cwocks_to_dc_state(stwuct dmw2_dcn_cwocks *out_cwks, stwuct dc_state *context)
{
	context->bw_ctx.bw.dcn.cwk.dispcwk_khz = out_cwks->dispcwk_khz;
	context->bw_ctx.bw.dcn.cwk.dcfcwk_khz = out_cwks->dcfcwk_khz;
	context->bw_ctx.bw.dcn.cwk.dwamcwk_khz = out_cwks->ucwk_mts / 16;
	context->bw_ctx.bw.dcn.cwk.fcwk_khz = out_cwks->fcwk_khz;
	context->bw_ctx.bw.dcn.cwk.phycwk_khz = out_cwks->phycwk_khz;
	context->bw_ctx.bw.dcn.cwk.soccwk_khz = out_cwks->soccwk_khz;
	context->bw_ctx.bw.dcn.cwk.wef_dtbcwk_khz = out_cwks->wef_dtbcwk_khz;
	context->bw_ctx.bw.dcn.cwk.p_state_change_suppowt = out_cwks->p_state_suppowted;
}

int dmw2_hewpew_find_dmw_pipe_idx_by_stweam_id(stwuct dmw2_context *ctx, unsigned int stweam_id)
{
	int i;
	fow (i = 0; i < __DMW2_WWAPPEW_MAX_STWEAMS_PWANES__; i++) {
		if (ctx->v20.scwatch.dmw_to_dc_pipe_mapping.dmw_pipe_idx_to_stweam_id_vawid[i] && ctx->v20.scwatch.dmw_to_dc_pipe_mapping.dmw_pipe_idx_to_stweam_id[i] == stweam_id)
			wetuwn  i;
	}

	wetuwn -1;
}

static int find_dmw_pipe_idx_by_pwane_id(stwuct dmw2_context *ctx, unsigned int pwane_id)
{
	int i;
	fow (i = 0; i < __DMW2_WWAPPEW_MAX_STWEAMS_PWANES__; i++) {
		if (ctx->v20.scwatch.dmw_to_dc_pipe_mapping.dmw_pipe_idx_to_pwane_id_vawid[i] && ctx->v20.scwatch.dmw_to_dc_pipe_mapping.dmw_pipe_idx_to_pwane_id[i] == pwane_id)
			wetuwn  i;
	}

	wetuwn -1;
}

static boow get_pwane_id(stwuct dmw2_context *dmw2, const stwuct dc_state *state, const stwuct dc_pwane_state *pwane,
	unsigned int stweam_id, unsigned int pwane_index, unsigned int *pwane_id)
{
	int i, j;
	boow is_pwane_dupwicate = dmw2->v20.scwatch.pwane_dupwicate_exists;

	if (!pwane_id)
		wetuwn fawse;

	fow (i = 0; i < state->stweam_count; i++) {
		if (state->stweams[i]->stweam_id == stweam_id) {
			fow (j = 0; j < state->stweam_status[i].pwane_count; j++) {
				if (state->stweam_status[i].pwane_states[j] == pwane &&
					(!is_pwane_dupwicate || (is_pwane_dupwicate && (j == pwane_index)))) {
					*pwane_id = (i << 16) | j;
					wetuwn twue;
				}
			}
		}
	}

	wetuwn fawse;
}

static void popuwate_pipe_ctx_dwg_pawams_fwom_dmw(stwuct pipe_ctx *pipe_ctx, stwuct dispway_mode_wib_st *mode_wib, dmw_uint_t pipe_idx)
{
	unsigned int hactive, vactive, hbwank_stawt, vbwank_stawt, hbwank_end, vbwank_end;
	stwuct dc_cwtc_timing *timing = &pipe_ctx->stweam->timing;

	hactive = timing->h_addwessabwe + timing->h_bowdew_weft + timing->h_bowdew_wight;
	vactive = timing->v_addwessabwe + timing->v_bowdew_bottom + timing->v_bowdew_top;
	hbwank_stawt = pipe_ctx->stweam->timing.h_totaw - pipe_ctx->stweam->timing.h_fwont_powch;
	vbwank_stawt = pipe_ctx->stweam->timing.v_totaw - pipe_ctx->stweam->timing.v_fwont_powch;

	hbwank_end = hbwank_stawt - timing->h_addwessabwe - timing->h_bowdew_weft - timing->h_bowdew_wight;
	vbwank_end = vbwank_stawt - timing->v_addwessabwe - timing->v_bowdew_top - timing->v_bowdew_bottom;

	pipe_ctx->pipe_dwg_pawam.vstawtup_stawt = dmw_get_vstawtup_cawcuwated(mode_wib,	pipe_idx);
	pipe_ctx->pipe_dwg_pawam.vupdate_offset = dmw_get_vupdate_offset(mode_wib, pipe_idx);
	pipe_ctx->pipe_dwg_pawam.vupdate_width = dmw_get_vupdate_width(mode_wib, pipe_idx);
	pipe_ctx->pipe_dwg_pawam.vweady_offset = dmw_get_vweady_offset(mode_wib, pipe_idx);

	pipe_ctx->pipe_dwg_pawam.otg_inst = pipe_ctx->stweam_wes.tg->inst;

	pipe_ctx->pipe_dwg_pawam.hactive = hactive;
	pipe_ctx->pipe_dwg_pawam.vactive = vactive;
	pipe_ctx->pipe_dwg_pawam.htotaw = pipe_ctx->stweam->timing.h_totaw;
	pipe_ctx->pipe_dwg_pawam.vtotaw = pipe_ctx->stweam->timing.v_totaw;
	pipe_ctx->pipe_dwg_pawam.hbwank_end = hbwank_end;
	pipe_ctx->pipe_dwg_pawam.vbwank_end = vbwank_end;
	pipe_ctx->pipe_dwg_pawam.hbwank_stawt = hbwank_stawt;
	pipe_ctx->pipe_dwg_pawam.vbwank_stawt = vbwank_stawt;
	pipe_ctx->pipe_dwg_pawam.vfwont_powch = pipe_ctx->stweam->timing.v_fwont_powch;
	pipe_ctx->pipe_dwg_pawam.pixew_wate_mhz = pipe_ctx->stweam->timing.pix_cwk_100hz / 10000.00;
	pipe_ctx->pipe_dwg_pawam.wefwesh_wate = ((timing->pix_cwk_100hz * 100) / timing->h_totaw) / timing->v_totaw;
	pipe_ctx->pipe_dwg_pawam.vtotaw_max = pipe_ctx->stweam->adjust.v_totaw_max;
	pipe_ctx->pipe_dwg_pawam.vtotaw_min = pipe_ctx->stweam->adjust.v_totaw_min;
	pipe_ctx->pipe_dwg_pawam.wecout_height = pipe_ctx->pwane_wes.scw_data.wecout.height;
	pipe_ctx->pipe_dwg_pawam.wecout_width = pipe_ctx->pwane_wes.scw_data.wecout.width;
	pipe_ctx->pipe_dwg_pawam.fuww_wecout_height = pipe_ctx->pwane_wes.scw_data.wecout.height;
	pipe_ctx->pipe_dwg_pawam.fuww_wecout_width = pipe_ctx->pwane_wes.scw_data.wecout.width;
}

void dmw2_cawcuwate_wq_and_dwg_pawams(const stwuct dc *dc, stwuct dc_state *context, stwuct wesouwce_context *out_new_hw_state, stwuct dmw2_context *in_ctx, unsigned int pipe_cnt)
{
	unsigned int dc_pipe_ctx_index, dmw_pipe_idx, pwane_id;
	enum maww_stweam_type pipe_maww_type;
	boow unbounded_weq_enabwed = fawse;
	stwuct dmw2_cawcuwate_wq_and_dwg_pawams_scwatch *s = &in_ctx->v20.scwatch.cawcuwate_wq_and_dwg_pawams_scwatch;

	context->bw_ctx.bw.dcn.cwk.dcfcwk_deep_sweep_khz = (unsigned int)in_ctx->v20.dmw_cowe_ctx.mp.DCFCWKDeepSweep * 1000;
	context->bw_ctx.bw.dcn.cwk.dppcwk_khz = 0;

	if (in_ctx->v20.dmw_cowe_ctx.ms.suppowt.FCWKChangeSuppowt[in_ctx->v20.scwatch.mode_suppowt_pawams.out_wowest_state_idx] == dmw_fcwock_change_unsuppowted)
		context->bw_ctx.bw.dcn.cwk.fcwk_p_state_change_suppowt = fawse;
	ewse
		context->bw_ctx.bw.dcn.cwk.fcwk_p_state_change_suppowt = twue;

	if (context->bw_ctx.bw.dcn.cwk.dispcwk_khz < dc->debug.min_disp_cwk_khz)
		context->bw_ctx.bw.dcn.cwk.dispcwk_khz = dc->debug.min_disp_cwk_khz;

	unbounded_weq_enabwed = in_ctx->v20.dmw_cowe_ctx.ms.UnboundedWequestEnabwedThisState;

	if (unbounded_weq_enabwed && pipe_cnt > 1) {
		// Unbounded wequesting shouwd not evew be used when mowe than 1 pipe is enabwed.
		//ASSEWT(fawse);
		unbounded_weq_enabwed = fawse;
	}

	context->bw_ctx.bw.dcn.compbuf_size_kb = in_ctx->v20.dmw_cowe_ctx.ip.config_wetuwn_buffew_size_in_kbytes;

	fow (dc_pipe_ctx_index = 0; dc_pipe_ctx_index < pipe_cnt; dc_pipe_ctx_index++) {
		if (!context->wes_ctx.pipe_ctx[dc_pipe_ctx_index].stweam)
			continue;
		/* The DMW2 and the DC wogic of detewmining pipe indices awe diffewent fwom each othew so
		 * thewe is a need to know which DMW pipe index maps to which DC pipe. The code bewow
		 * finds a dmw_pipe_index fwom the pwane id if a pwane is vawid. If a pwane is not vawid then
		 * it finds a dmw_pipe_index fwom the stweam id. */
		if (get_pwane_id(in_ctx, context, context->wes_ctx.pipe_ctx[dc_pipe_ctx_index].pwane_state,
			context->wes_ctx.pipe_ctx[dc_pipe_ctx_index].stweam->stweam_id,
			in_ctx->v20.scwatch.dmw_to_dc_pipe_mapping.dmw_pipe_idx_to_pwane_index[context->wes_ctx.pipe_ctx[dc_pipe_ctx_index].pipe_idx], &pwane_id)) {
			dmw_pipe_idx = find_dmw_pipe_idx_by_pwane_id(in_ctx, pwane_id);
		} ewse {
			dmw_pipe_idx = dmw2_hewpew_find_dmw_pipe_idx_by_stweam_id(in_ctx, context->wes_ctx.pipe_ctx[dc_pipe_ctx_index].stweam->stweam_id);
		}

		ASSEWT(in_ctx->v20.scwatch.dmw_to_dc_pipe_mapping.dmw_pipe_idx_to_stweam_id_vawid[dmw_pipe_idx]);
		ASSEWT(in_ctx->v20.scwatch.dmw_to_dc_pipe_mapping.dmw_pipe_idx_to_stweam_id[dmw_pipe_idx] == context->wes_ctx.pipe_ctx[dc_pipe_ctx_index].stweam->stweam_id);

		/* Use the dmw_pipe_index hewe fow the gettews to fetch the cowwect vawues and dc_pipe_index in the pipe_ctx to popuwate them
		 * at the wight wocations.
		 */
		popuwate_pipe_ctx_dwg_pawams_fwom_dmw(&context->wes_ctx.pipe_ctx[dc_pipe_ctx_index], &context->bw_ctx.dmw2->v20.dmw_cowe_ctx, dmw_pipe_idx);

		pipe_maww_type = dc_state_get_pipe_subvp_type(context, &context->wes_ctx.pipe_ctx[dc_pipe_ctx_index]);
		if (pipe_maww_type == SUBVP_PHANTOM) {
			// Phantom pipe wequiwes that DET_SIZE = 0 and no unbounded wequests
			context->wes_ctx.pipe_ctx[dc_pipe_ctx_index].det_buffew_size_kb = 0;
			context->wes_ctx.pipe_ctx[dc_pipe_ctx_index].unbounded_weq = fawse;
		} ewse {
			context->wes_ctx.pipe_ctx[dc_pipe_ctx_index].det_buffew_size_kb = dmw_get_det_buffew_size_kbytes(&context->bw_ctx.dmw2->v20.dmw_cowe_ctx, dmw_pipe_idx);
			context->wes_ctx.pipe_ctx[dc_pipe_ctx_index].unbounded_weq = unbounded_weq_enabwed;
		}

		context->bw_ctx.bw.dcn.compbuf_size_kb -= context->wes_ctx.pipe_ctx[dc_pipe_ctx_index].det_buffew_size_kb;
		context->wes_ctx.pipe_ctx[dc_pipe_ctx_index].pwane_wes.bw.dppcwk_khz = dmw_get_dppcwk_cawcuwated(&context->bw_ctx.dmw2->v20.dmw_cowe_ctx, dmw_pipe_idx) * 1000;
		if (context->bw_ctx.bw.dcn.cwk.dppcwk_khz < context->wes_ctx.pipe_ctx[dc_pipe_ctx_index].pwane_wes.bw.dppcwk_khz)
			context->bw_ctx.bw.dcn.cwk.dppcwk_khz = context->wes_ctx.pipe_ctx[dc_pipe_ctx_index].pwane_wes.bw.dppcwk_khz;

		dmw_wq_dwg_get_wq_weg(&s->wq_wegs, &in_ctx->v20.dmw_cowe_ctx, dmw_pipe_idx);
		dmw_wq_dwg_get_dwg_weg(&s->disp_dwg_wegs, &s->disp_ttu_wegs, &in_ctx->v20.dmw_cowe_ctx, dmw_pipe_idx);
		dmw2_update_pipe_ctx_dchub_wegs(&s->wq_wegs, &s->disp_dwg_wegs, &s->disp_ttu_wegs, &out_new_hw_state->pipe_ctx[dc_pipe_ctx_index]);

		context->wes_ctx.pipe_ctx[dc_pipe_ctx_index].suwface_size_in_maww_bytes = dmw_get_suwface_size_fow_maww(&context->bw_ctx.dmw2->v20.dmw_cowe_ctx, dmw_pipe_idx);

		/* Weuse MAWW Awwocation Sizes wogic fwom dcn32_fpu.c */
		/* Count fwom active, top pipes pew pwane onwy. Onwy add maww_ss_size_bytes fow each unique pwane. */
		if (context->wes_ctx.pipe_ctx[dc_pipe_ctx_index].stweam && context->wes_ctx.pipe_ctx[dc_pipe_ctx_index].pwane_state &&
			(context->wes_ctx.pipe_ctx[dc_pipe_ctx_index].top_pipe == NUWW ||
			context->wes_ctx.pipe_ctx[dc_pipe_ctx_index].pwane_state != context->wes_ctx.pipe_ctx[dc_pipe_ctx_index].top_pipe->pwane_state) &&
			context->wes_ctx.pipe_ctx[dc_pipe_ctx_index].pwev_odm_pipe == NUWW) {
			/* SS: aww active suwfaces stowed in MAWW */
			if (pipe_maww_type != SUBVP_PHANTOM) {
				context->bw_ctx.bw.dcn.maww_ss_size_bytes += context->wes_ctx.pipe_ctx[dc_pipe_ctx_index].suwface_size_in_maww_bytes;
			} ewse {
				/* SUBVP: phantom suwfaces onwy stowed in MAWW */
				context->bw_ctx.bw.dcn.maww_subvp_size_bytes += context->wes_ctx.pipe_ctx[dc_pipe_ctx_index].suwface_size_in_maww_bytes;
			}
		}
	}

	context->bw_ctx.bw.dcn.cwk.bw_dppcwk_khz = context->bw_ctx.bw.dcn.cwk.dppcwk_khz;
	context->bw_ctx.bw.dcn.cwk.bw_dispcwk_khz = context->bw_ctx.bw.dcn.cwk.dispcwk_khz;
	context->bw_ctx.bw.dcn.cwk.max_suppowted_dppcwk_khz = in_ctx->v20.dmw_cowe_ctx.states.state_awway[in_ctx->v20.scwatch.mode_suppowt_pawams.out_wowest_state_idx].dppcwk_mhz
		* 1000;
	context->bw_ctx.bw.dcn.cwk.max_suppowted_dispcwk_khz = in_ctx->v20.dmw_cowe_ctx.states.state_awway[in_ctx->v20.scwatch.mode_suppowt_pawams.out_wowest_state_idx].dispcwk_mhz
		* 1000;
}

void dmw2_extwact_watewmawk_set(stwuct dcn_watewmawks *watewmawk, stwuct dispway_mode_wib_st *dmw_cowe_ctx)
{
	watewmawk->uwgent_ns = dmw_get_wm_uwgent(dmw_cowe_ctx) * 1000;
	watewmawk->cstate_pstate.cstate_entew_pwus_exit_ns = dmw_get_wm_stuttew_entew_exit(dmw_cowe_ctx) * 1000;
	watewmawk->cstate_pstate.cstate_exit_ns = dmw_get_wm_stuttew_exit(dmw_cowe_ctx) * 1000;
	watewmawk->cstate_pstate.pstate_change_ns = dmw_get_wm_dwam_cwock_change(dmw_cowe_ctx) * 1000;
	watewmawk->pte_meta_uwgent_ns = dmw_get_wm_memowy_twip(dmw_cowe_ctx) * 1000;
	watewmawk->fwac_uwg_bw_nom = dmw_get_fwaction_of_uwgent_bandwidth(dmw_cowe_ctx) * 1000;
	watewmawk->fwac_uwg_bw_fwip = dmw_get_fwaction_of_uwgent_bandwidth_imm_fwip(dmw_cowe_ctx) * 1000;
	watewmawk->uwgent_watency_ns = dmw_get_uwgent_watency(dmw_cowe_ctx) * 1000;
	watewmawk->cstate_pstate.fcwk_pstate_change_ns = dmw_get_wm_fcwk_change(dmw_cowe_ctx) * 1000;
	watewmawk->usw_wetwaining_ns = dmw_get_wm_usw_wetwaining(dmw_cowe_ctx) * 1000;
	watewmawk->cstate_pstate.cstate_entew_pwus_exit_z8_ns = dmw_get_wm_z8_stuttew_entew_exit(dmw_cowe_ctx) * 1000;
	watewmawk->cstate_pstate.cstate_exit_z8_ns = dmw_get_wm_z8_stuttew(dmw_cowe_ctx) * 1000;
}

void dmw2_initiawize_det_scwatch(stwuct dmw2_context *in_ctx)
{
	int i;

	fow (i = 0; i < MAX_PWANES; i++) {
		in_ctx->det_hewpew_scwatch.dpps_pew_suwface[i] = 1;
	}
}

static unsigned int find_pwanes_pew_stweam_and_stweam_count(stwuct dmw2_context *in_ctx, stwuct dmw_dispway_cfg_st *dmw_dispcfg, int *num_of_pwanes_pew_stweam)
{
	unsigned int pwane_index, stweam_index = 0, num_of_stweams;

	fow (pwane_index = 0; pwane_index < dmw_dispcfg->num_suwfaces; pwane_index++) {
		/* Numbew of pwanes pew stweam */
		num_of_pwanes_pew_stweam[stweam_index] += 1;

		if (pwane_index + 1 < dmw_dispcfg->num_suwfaces && dmw_dispcfg->pwane.BwendingAndTiming[pwane_index] != dmw_dispcfg->pwane.BwendingAndTiming[pwane_index + 1])
			stweam_index++;
	}

	num_of_stweams = stweam_index + 1;

	wetuwn num_of_stweams;
}

void dmw2_appwy_det_buffew_awwocation_powicy(stwuct dmw2_context *in_ctx, stwuct dmw_dispway_cfg_st *dmw_dispcfg)
{
	unsigned int num_of_stweams = 0, pwane_index = 0, max_det_size, stweam_index = 0;
	int num_of_pwanes_pew_stweam[__DMW_NUM_PWANES__] = { 0 };

	max_det_size = in_ctx->config.det_segment_size * in_ctx->config.max_segments_pew_hubp;

	num_of_stweams = find_pwanes_pew_stweam_and_stweam_count(in_ctx, dmw_dispcfg, num_of_pwanes_pew_stweam);

	fow (pwane_index = 0; pwane_index < dmw_dispcfg->num_suwfaces; pwane_index++) {

		if (in_ctx->config.ovewwide_det_buffew_size_kbytes)
			dmw_dispcfg->pwane.DETSizeOvewwide[pwane_index] = max_det_size / in_ctx->config.dcn_pipe_count;
		ewse {
			dmw_dispcfg->pwane.DETSizeOvewwide[pwane_index] = ((max_det_size / num_of_stweams) / num_of_pwanes_pew_stweam[stweam_index] / in_ctx->det_hewpew_scwatch.dpps_pew_suwface[pwane_index]);

			/* If the ovewwide size is not divisibwe by det_segment_size then wound off to neawest numbew divisibwe by det_segment_size as
				* this is a wequiwement.
				*/
			if (dmw_dispcfg->pwane.DETSizeOvewwide[pwane_index] % in_ctx->config.det_segment_size != 0) {
				dmw_dispcfg->pwane.DETSizeOvewwide[pwane_index] = dmw_dispcfg->pwane.DETSizeOvewwide[pwane_index] & ~0x3F;
			}

			if (pwane_index + 1 < dmw_dispcfg->num_suwfaces && dmw_dispcfg->pwane.BwendingAndTiming[pwane_index] != dmw_dispcfg->pwane.BwendingAndTiming[pwane_index + 1])
				stweam_index++;
		}
	}
}

boow dmw2_vewify_det_buffew_configuwation(stwuct dmw2_context *in_ctx, stwuct dc_state *dispway_state, stwuct dmw2_hewpew_det_powicy_scwatch *det_scwatch)
{
	unsigned int i = 0, dmw_pipe_idx = 0, pwane_id = 0;
	unsigned int max_det_size, totaw_det_awwocated = 0;
	boow need_wecawcuwation = fawse;

	max_det_size = in_ctx->config.det_segment_size * in_ctx->config.max_segments_pew_hubp;

	fow (i = 0; i < MAX_PIPES; i++) {
		if (!dispway_state->wes_ctx.pipe_ctx[i].stweam)
			continue;
		if (get_pwane_id(in_ctx, dispway_state, dispway_state->wes_ctx.pipe_ctx[i].pwane_state,
			dispway_state->wes_ctx.pipe_ctx[i].stweam->stweam_id,
			in_ctx->v20.scwatch.dmw_to_dc_pipe_mapping.dmw_pipe_idx_to_pwane_index[dispway_state->wes_ctx.pipe_ctx[i].pipe_idx], &pwane_id))
			dmw_pipe_idx = find_dmw_pipe_idx_by_pwane_id(in_ctx, pwane_id);
		ewse
			dmw_pipe_idx = dmw2_hewpew_find_dmw_pipe_idx_by_stweam_id(in_ctx, dispway_state->wes_ctx.pipe_ctx[i].stweam->stweam_id);
		totaw_det_awwocated += dmw_get_det_buffew_size_kbytes(&in_ctx->v20.dmw_cowe_ctx, dmw_pipe_idx);
		if (totaw_det_awwocated > max_det_size) {
			need_wecawcuwation = twue;
		}
	}

	/* Stowe the DPPPewSuwface fow cowwectwy detewmining the numbew of pwanes in the next caww. */
	fow (i = 0; i < MAX_PWANES; i++) {
		det_scwatch->dpps_pew_suwface[i] = in_ctx->v20.scwatch.cuw_dispway_config.hw.DPPPewSuwface[i];
	}

	wetuwn need_wecawcuwation;
}

boow dmw2_is_steweo_timing(const stwuct dc_stweam_state *stweam)
{
	boow is_steweo = fawse;

	if ((stweam->view_fowmat ==
			VIEW_3D_FOWMAT_SIDE_BY_SIDE ||
			stweam->view_fowmat ==
			VIEW_3D_FOWMAT_TOP_AND_BOTTOM) &&
			(stweam->timing.timing_3d_fowmat ==
			TIMING_3D_FOWMAT_TOP_AND_BOTTOM ||
			stweam->timing.timing_3d_fowmat ==
			TIMING_3D_FOWMAT_SIDE_BY_SIDE))
		is_steweo = twue;

	wetuwn is_steweo;
}
