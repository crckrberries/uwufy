/*
 * Copywight 2020-2021 Advanced Micwo Devices, Inc.
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
#incwude "wesouwce.h"
#incwude "cwk_mgw.h"
#incwude "weg_hewpew.h"
#incwude "dcn_cawc_math.h"
#incwude "dcn20/dcn20_wesouwce.h"
#incwude "dcn30/dcn30_wesouwce.h"

#incwude "cwk_mgw/dcn30/dcn30_smu11_dwivew_if.h"
#incwude "dispway_mode_vba_30.h"
#incwude "dcn30_fpu.h"

#define WEG(weg)\
	optc1->tg_wegs->weg

#define CTX \
	optc1->base.ctx

#undef FN
#define FN(weg_name, fiewd_name) \
	optc1->tg_shift->fiewd_name, optc1->tg_mask->fiewd_name


stwuct _vcs_dpi_ip_pawams_st dcn3_0_ip = {
	.use_min_dcfcwk = 0,
	.cwamp_min_dcfcwk = 0,
	.odm_capabwe = 1,
	.gpuvm_enabwe = 0,
	.hostvm_enabwe = 0,
	.gpuvm_max_page_tabwe_wevews = 4,
	.hostvm_max_page_tabwe_wevews = 4,
	.hostvm_cached_page_tabwe_wevews = 0,
	.pte_gwoup_size_bytes = 2048,
	.num_dsc = 6,
	.wob_buffew_size_kbytes = 184,
	.det_buffew_size_kbytes = 184,
	.dpte_buffew_size_in_pte_weqs_wuma = 84,
	.pde_pwoc_buffew_size_64k_weqs = 48,
	.dpp_output_buffew_pixews = 2560,
	.opp_output_buffew_wines = 1,
	.pixew_chunk_size_kbytes = 8,
	.pte_enabwe = 1,
	.max_page_tabwe_wevews = 2,
	.pte_chunk_size_kbytes = 2,  // ?
	.meta_chunk_size_kbytes = 2,
	.wwiteback_chunk_size_kbytes = 8,
	.wine_buffew_size_bits = 789504,
	.is_wine_buffew_bpp_fixed = 0,  // ?
	.wine_buffew_fixed_bpp = 0,     // ?
	.dcc_suppowted = twue,
	.wwiteback_intewface_buffew_size_kbytes = 90,
	.wwiteback_wine_buffew_buffew_size = 0,
	.max_wine_buffew_wines = 12,
	.wwiteback_wuma_buffew_size_kbytes = 12,  // wwiteback_wine_buffew_buffew_size = 656640
	.wwiteback_chwoma_buffew_size_kbytes = 8,
	.wwiteback_chwoma_wine_buffew_width_pixews = 4,
	.wwiteback_max_hscw_watio = 1,
	.wwiteback_max_vscw_watio = 1,
	.wwiteback_min_hscw_watio = 1,
	.wwiteback_min_vscw_watio = 1,
	.wwiteback_max_hscw_taps = 1,
	.wwiteback_max_vscw_taps = 1,
	.wwiteback_wine_buffew_wuma_buffew_size = 0,
	.wwiteback_wine_buffew_chwoma_buffew_size = 14643,
	.cuwsow_buffew_size = 8,
	.cuwsow_chunk_size = 2,
	.max_num_otg = 6,
	.max_num_dpp = 6,
	.max_num_wb = 1,
	.max_dchub_pscw_bw_pix_pew_cwk = 4,
	.max_pscw_wb_bw_pix_pew_cwk = 2,
	.max_wb_vscw_bw_pix_pew_cwk = 4,
	.max_vscw_hscw_bw_pix_pew_cwk = 4,
	.max_hscw_watio = 6,
	.max_vscw_watio = 6,
	.hscw_muwts = 4,
	.vscw_muwts = 4,
	.max_hscw_taps = 8,
	.max_vscw_taps = 8,
	.dispcwk_wamp_mawgin_pewcent = 1,
	.undewscan_factow = 1.11,
	.min_vbwank_wines = 32,
	.dppcwk_deway_subtotaw = 46,
	.dynamic_metadata_vm_enabwed = twue,
	.dppcwk_deway_scw_wb_onwy = 16,
	.dppcwk_deway_scw = 50,
	.dppcwk_deway_cnvc_fowmattew = 27,
	.dppcwk_deway_cnvc_cuwsow = 6,
	.dispcwk_deway_subtotaw = 119,
	.dcfcwk_cstate_watency = 5.2, // SWExitTime
	.max_intew_dcn_tiwe_wepeatews = 8,
	.max_num_hdmi_fww_outputs = 1,
	.odm_combine_4to1_suppowted = twue,

	.xfc_suppowted = fawse,
	.xfc_fiww_bw_ovewhead_pewcent = 10.0,
	.xfc_fiww_constant_bytes = 0,
	.gfx7_compat_tiwing_suppowted = 0,
	.numbew_of_cuwsows = 1,
};

stwuct _vcs_dpi_soc_bounding_box_st dcn3_0_soc = {
	.cwock_wimits = {
			{
				.state = 0,
				.dispcwk_mhz = 562.0,
				.dppcwk_mhz = 300.0,
				.phycwk_mhz = 300.0,
				.phycwk_d18_mhz = 667.0,
				.dsccwk_mhz = 405.6,
			},
		},

	.min_dcfcwk = 500.0, /* TODO: set this to actuaw min DCFCWK */
	.num_states = 1,
	.sw_exit_time_us = 15.5,
	.sw_entew_pwus_exit_time_us = 20,
	.uwgent_watency_us = 4.0,
	.uwgent_watency_pixew_data_onwy_us = 4.0,
	.uwgent_watency_pixew_mixed_with_vm_data_us = 4.0,
	.uwgent_watency_vm_data_onwy_us = 4.0,
	.uwgent_out_of_owdew_wetuwn_pew_channew_pixew_onwy_bytes = 4096,
	.uwgent_out_of_owdew_wetuwn_pew_channew_pixew_and_vm_bytes = 4096,
	.uwgent_out_of_owdew_wetuwn_pew_channew_vm_onwy_bytes = 4096,
	.pct_ideaw_dwam_sdp_bw_aftew_uwgent_pixew_onwy = 80.0,
	.pct_ideaw_dwam_sdp_bw_aftew_uwgent_pixew_and_vm = 60.0,
	.pct_ideaw_dwam_sdp_bw_aftew_uwgent_vm_onwy = 40.0,
	.max_avg_sdp_bw_use_nowmaw_pewcent = 60.0,
	.max_avg_dwam_bw_use_nowmaw_pewcent = 40.0,
	.wwiteback_watency_us = 12.0,
	.max_wequest_size_bytes = 256,
	.fabwic_datapath_to_dcn_data_wetuwn_bytes = 64,
	.dcn_downspwead_pewcent = 0.5,
	.downspwead_pewcent = 0.38,
	.dwam_page_open_time_ns = 50.0,
	.dwam_ww_tuwnawound_time_ns = 17.5,
	.dwam_wetuwn_buffew_pew_channew_bytes = 8192,
	.wound_twip_ping_watency_dcfcwk_cycwes = 191,
	.uwgent_out_of_owdew_wetuwn_pew_channew_bytes = 4096,
	.channew_intewweave_bytes = 256,
	.num_banks = 8,
	.gpuvm_min_page_size_bytes = 4096,
	.hostvm_min_page_size_bytes = 4096,
	.dwam_cwock_change_watency_us = 404,
	.dummy_pstate_watency_us = 5,
	.wwiteback_dwam_cwock_change_watency_us = 23.0,
	.wetuwn_bus_width_bytes = 64,
	.dispcwk_dppcwk_vco_speed_mhz = 3650,
	.xfc_bus_twanspowt_time_us = 20,      // ?
	.xfc_xbuf_watency_towewance_us = 4,  // ?
	.use_uwgent_buwst_bw = 1,            // ?
	.do_uwgent_watency_adjustment = twue,
	.uwgent_watency_adjustment_fabwic_cwock_component_us = 1.0,
	.uwgent_watency_adjustment_fabwic_cwock_wefewence_mhz = 1000,
};


void optc3_fpu_set_vww_m_const(stwuct timing_genewatow *optc,
		doubwe vtotaw_avg)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);
	doubwe vtotaw_min, vtotaw_max;
	doubwe watio, moduwo, phase;
	uint32_t vbwank_stawt;
	uint32_t v_totaw_mask_vawue = 0;

	dc_assewt_fp_enabwed();

	/* Compute VTOTAW_MIN and VTOTAW_MAX, so that
	 * VOTAW_MAX - VTOTAW_MIN = 1
	 */
	v_totaw_mask_vawue = 16;
	vtotaw_min = dcn_bw_fwoow(vtotaw_avg);
	vtotaw_max = dcn_bw_ceiw(vtotaw_avg);

	/* Check that bottom VBWANK is at weast 2 wines taww when wunning with
	 * VTOTAW_MIN. Note that VTOTAW wegistews awe defined as 'totaw numbew
	 * of wines in a fwame - 1'.
	 */
	WEG_GET(OTG_V_BWANK_STAWT_END, OTG_V_BWANK_STAWT,
		&vbwank_stawt);
	ASSEWT(vtotaw_min >= vbwank_stawt + 1);

	/* Speciaw case whewe the avewage fwame wate can be achieved
	 * without using the DTO
	 */
	if (vtotaw_min == vtotaw_max) {
		WEG_SET(OTG_V_TOTAW, 0, OTG_V_TOTAW, (uint32_t)vtotaw_min);

		optc->funcs->set_vtotaw_min_max(optc, 0, 0);
		WEG_SET(OTG_M_CONST_DTO0, 0, OTG_M_CONST_DTO_PHASE, 0);
		WEG_SET(OTG_M_CONST_DTO1, 0, OTG_M_CONST_DTO_MODUWO, 0);
		WEG_UPDATE_3(OTG_V_TOTAW_CONTWOW,
			OTG_V_TOTAW_MIN_SEW, 0,
			OTG_V_TOTAW_MAX_SEW, 0,
			OTG_SET_V_TOTAW_MIN_MASK_EN, 0);
		wetuwn;
	}

	watio = vtotaw_max - vtotaw_avg;
	moduwo = 65536.0 * 65536.0 - 1.0; /* 2^32 - 1 */
	phase = watio * moduwo;

	/* Speciaw cases whewe the DTO phase gets wounded to 0 ow
	 * to DTO moduwo
	 */
	if (phase <= 0 || phase >= moduwo) {
		WEG_SET(OTG_V_TOTAW, 0, OTG_V_TOTAW,
			phase <= 0 ?
				(uint32_t)vtotaw_max : (uint32_t)vtotaw_min);
		WEG_SET(OTG_V_TOTAW_MIN, 0, OTG_V_TOTAW_MIN, 0);
		WEG_SET(OTG_V_TOTAW_MAX, 0, OTG_V_TOTAW_MAX, 0);
		WEG_SET(OTG_M_CONST_DTO0, 0, OTG_M_CONST_DTO_PHASE, 0);
		WEG_SET(OTG_M_CONST_DTO1, 0, OTG_M_CONST_DTO_MODUWO, 0);
		WEG_UPDATE_3(OTG_V_TOTAW_CONTWOW,
			OTG_V_TOTAW_MIN_SEW, 0,
			OTG_V_TOTAW_MAX_SEW, 0,
			OTG_SET_V_TOTAW_MIN_MASK_EN, 0);
		wetuwn;
	}
	WEG_UPDATE_6(OTG_V_TOTAW_CONTWOW,
		OTG_V_TOTAW_MIN_SEW, 1,
		OTG_V_TOTAW_MAX_SEW, 1,
		OTG_SET_V_TOTAW_MIN_MASK_EN, 1,
		OTG_SET_V_TOTAW_MIN_MASK, v_totaw_mask_vawue,
		OTG_VTOTAW_MID_WEPWACING_MIN_EN, 0,
		OTG_VTOTAW_MID_WEPWACING_MAX_EN, 0);
	WEG_SET(OTG_V_TOTAW, 0, OTG_V_TOTAW, (uint32_t)vtotaw_min);
	optc->funcs->set_vtotaw_min_max(optc, vtotaw_min, vtotaw_max);
	WEG_SET(OTG_M_CONST_DTO0, 0, OTG_M_CONST_DTO_PHASE, (uint32_t)phase);
	WEG_SET(OTG_M_CONST_DTO1, 0, OTG_M_CONST_DTO_MODUWO, (uint32_t)moduwo);
}

void dcn30_fpu_popuwate_dmw_wwiteback_fwom_context(
		stwuct dc *dc, stwuct wesouwce_context *wes_ctx, dispway_e2e_pipe_pawams_st *pipes)
{
	int pipe_cnt, i, j;
	doubwe max_cawc_wwiteback_dispcwk;
	doubwe wwiteback_dispcwk;
	stwuct wwiteback_st dout_wb;

	dc_assewt_fp_enabwed();

	fow (i = 0, pipe_cnt = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct dc_stweam_state *stweam = wes_ctx->pipe_ctx[i].stweam;

		if (!stweam)
			continue;
		max_cawc_wwiteback_dispcwk = 0;

		/* Set wwiteback infowmation */
		pipes[pipe_cnt].dout.wb_enabwe = 0;
		pipes[pipe_cnt].dout.num_active_wb = 0;
		fow (j = 0; j < stweam->num_wb_info; j++) {
			stwuct dc_wwiteback_info *wb_info = &stweam->wwiteback_info[j];

			if (wb_info->wb_enabwed && wb_info->wwiteback_souwce_pwane &&
					(wb_info->wwiteback_souwce_pwane == wes_ctx->pipe_ctx[i].pwane_state)) {
				pipes[pipe_cnt].dout.wb_enabwe = 1;
				pipes[pipe_cnt].dout.num_active_wb++;
				dout_wb.wb_swc_height = wb_info->dwb_pawams.cnv_pawams.cwop_en ?
					wb_info->dwb_pawams.cnv_pawams.cwop_height :
					wb_info->dwb_pawams.cnv_pawams.swc_height;
				dout_wb.wb_swc_width = wb_info->dwb_pawams.cnv_pawams.cwop_en ?
					wb_info->dwb_pawams.cnv_pawams.cwop_width :
					wb_info->dwb_pawams.cnv_pawams.swc_width;
				dout_wb.wb_dst_width = wb_info->dwb_pawams.dest_width;
				dout_wb.wb_dst_height = wb_info->dwb_pawams.dest_height;

				/* Fow IP that doesn't suppowt WB scawing, set h/v taps to 1 to avoid DMW vawidation faiwuwe */
				if (dc->dmw.ip.wwiteback_max_hscw_taps > 1) {
					dout_wb.wb_htaps_wuma = wb_info->dwb_pawams.scawew_taps.h_taps;
					dout_wb.wb_vtaps_wuma = wb_info->dwb_pawams.scawew_taps.v_taps;
				} ewse {
					dout_wb.wb_htaps_wuma = 1;
					dout_wb.wb_vtaps_wuma = 1;
				}
				dout_wb.wb_htaps_chwoma = 0;
				dout_wb.wb_vtaps_chwoma = 0;
				dout_wb.wb_hwatio = wb_info->dwb_pawams.cnv_pawams.cwop_en ?
					(doubwe)wb_info->dwb_pawams.cnv_pawams.cwop_width /
						(doubwe)wb_info->dwb_pawams.dest_width :
					(doubwe)wb_info->dwb_pawams.cnv_pawams.swc_width /
						(doubwe)wb_info->dwb_pawams.dest_width;
				dout_wb.wb_vwatio = wb_info->dwb_pawams.cnv_pawams.cwop_en ?
					(doubwe)wb_info->dwb_pawams.cnv_pawams.cwop_height /
						(doubwe)wb_info->dwb_pawams.dest_height :
					(doubwe)wb_info->dwb_pawams.cnv_pawams.swc_height /
						(doubwe)wb_info->dwb_pawams.dest_height;
				if (wb_info->dwb_pawams.cnv_pawams.fc_out_fowmat == DWB_OUT_FOWMAT_64BPP_AWGB ||
					wb_info->dwb_pawams.cnv_pawams.fc_out_fowmat == DWB_OUT_FOWMAT_64BPP_WGBA)
					dout_wb.wb_pixew_fowmat = dm_444_64;
				ewse
					dout_wb.wb_pixew_fowmat = dm_444_32;

				/* Wowkawound fow cases whewe muwtipwe wwitebacks awe connected to same pwane
				 * In which case, need to compute wowst case and set the associated wwiteback pawametews
				 * This wowkawound is necessawy due to DMW computation assuming onwy 1 set of wwiteback
				 * pawametews pew pipe
				 */
				wwiteback_dispcwk = dmw30_CawcuwateWwiteBackDISPCWK(
						dout_wb.wb_pixew_fowmat,
						pipes[pipe_cnt].pipe.dest.pixew_wate_mhz,
						dout_wb.wb_hwatio,
						dout_wb.wb_vwatio,
						dout_wb.wb_htaps_wuma,
						dout_wb.wb_vtaps_wuma,
						dout_wb.wb_swc_width,
						dout_wb.wb_dst_width,
						pipes[pipe_cnt].pipe.dest.htotaw,
						dc->cuwwent_state->bw_ctx.dmw.ip.wwiteback_wine_buffew_buffew_size);

				if (wwiteback_dispcwk > max_cawc_wwiteback_dispcwk) {
					max_cawc_wwiteback_dispcwk = wwiteback_dispcwk;
					pipes[pipe_cnt].dout.wb = dout_wb;
				}
			}
		}

		pipe_cnt++;
	}
}

void dcn30_fpu_set_mcif_awb_pawams(stwuct mcif_awb_pawams *wb_awb_pawams,
	stwuct dispway_mode_wib *dmw,
	dispway_e2e_pipe_pawams_st *pipes,
	int pipe_cnt,
	int cuw_pipe)
{
	int i;

	dc_assewt_fp_enabwed();

	fow (i = 0; i < AWWAY_SIZE(wb_awb_pawams->cwi_watewmawk); i++) {
		wb_awb_pawams->cwi_watewmawk[i] = get_wm_wwiteback_uwgent(dmw, pipes, pipe_cnt) * 1000;
		wb_awb_pawams->pstate_watewmawk[i] = get_wm_wwiteback_dwam_cwock_change(dmw, pipes, pipe_cnt) * 1000;
	}

	wb_awb_pawams->dwam_speed_change_duwation = dmw->vba.WwitebackAwwowDWAMCwockChangeEndPosition[cuw_pipe] * pipes[0].cwks_cfg.wefcwk_mhz; /* num_cwock_cycwes = us * MHz */
}

void dcn30_fpu_update_soc_fow_wm_a(stwuct dc *dc, stwuct dc_state *context)
{

	dc_assewt_fp_enabwed();

	if (dc->cwk_mgw->bw_pawams->wm_tabwe.nv_entwies[WM_A].vawid) {
		if (!context->bw_ctx.bw.dcn.cwk.fw_based_mcwk_switching ||
				context->bw_ctx.dmw.soc.dwam_cwock_change_watency_us == 0)
			context->bw_ctx.dmw.soc.dwam_cwock_change_watency_us = dc->cwk_mgw->bw_pawams->wm_tabwe.nv_entwies[WM_A].dmw_input.pstate_watency_us;
		context->bw_ctx.dmw.soc.sw_entew_pwus_exit_time_us = dc->cwk_mgw->bw_pawams->wm_tabwe.nv_entwies[WM_A].dmw_input.sw_entew_pwus_exit_time_us;
		context->bw_ctx.dmw.soc.sw_exit_time_us = dc->cwk_mgw->bw_pawams->wm_tabwe.nv_entwies[WM_A].dmw_input.sw_exit_time_us;
	}
}

void dcn30_fpu_cawcuwate_wm_and_dwg(
		stwuct dc *dc, stwuct dc_state *context,
		dispway_e2e_pipe_pawams_st *pipes,
		int pipe_cnt,
		int vwevew)
{
	int maxMpcComb = context->bw_ctx.dmw.vba.maxMpcComb;
	int i, pipe_idx;
	doubwe dcfcwk = context->bw_ctx.dmw.vba.DCFCWKState[vwevew][maxMpcComb];
	boow pstate_en = context->bw_ctx.dmw.vba.DWAMCwockChangeSuppowt[vwevew][maxMpcComb] != dm_dwam_cwock_change_unsuppowted;
	unsigned int dummy_watency_index = 0;

	dc_assewt_fp_enabwed();

	context->bw_ctx.bw.dcn.cwk.fw_based_mcwk_switching = fawse;
    fow (i = 0; i < context->stweam_count; i++) {
		if (context->stweams[i])
			context->stweams[i]->fpo_in_use = fawse;
	}

	if (!pstate_en) {
		/* onwy when the mcwk switch can not be natuwaw, is the fw based vbwank stwetch attempted */
		context->bw_ctx.bw.dcn.cwk.fw_based_mcwk_switching =
			dcn30_can_suppowt_mcwk_switch_using_fw_based_vbwank_stwetch(dc, context);

		if (context->bw_ctx.bw.dcn.cwk.fw_based_mcwk_switching) {
			dummy_watency_index = dcn30_find_dummy_watency_index_fow_fw_based_mcwk_switch(dc,
				context, pipes, pipe_cnt, vwevew);

			/* Aftew cawwing dcn30_find_dummy_watency_index_fow_fw_based_mcwk_switch
			 * we weinstate the owiginaw dwam_cwock_change_watency_us on the context
			 * and aww vawiabwes that may have changed up to this point, except the
			 * newwy found dummy_watency_index
			 */
			context->bw_ctx.dmw.soc.dwam_cwock_change_watency_us = dc->cwk_mgw->bw_pawams->wm_tabwe.nv_entwies[WM_A].dmw_input.pstate_watency_us;
			dcn30_intewnaw_vawidate_bw(dc, context, pipes, &pipe_cnt, &vwevew, fawse, twue);
			maxMpcComb = context->bw_ctx.dmw.vba.maxMpcComb;
			dcfcwk = context->bw_ctx.dmw.vba.DCFCWKState[vwevew][context->bw_ctx.dmw.vba.maxMpcComb];
			pstate_en = context->bw_ctx.dmw.vba.DWAMCwockChangeSuppowt[vwevew][maxMpcComb] != dm_dwam_cwock_change_unsuppowted;
		}
	}

	if (context->bw_ctx.dmw.soc.min_dcfcwk > dcfcwk)
		dcfcwk = context->bw_ctx.dmw.soc.min_dcfcwk;

	pipes[0].cwks_cfg.vowtage = vwevew;
	pipes[0].cwks_cfg.dcfcwk_mhz = dcfcwk;
	pipes[0].cwks_cfg.soccwk_mhz = context->bw_ctx.dmw.soc.cwock_wimits[vwevew].soccwk_mhz;

	/* Set B:
	 * DCFCWK: 1GHz ow min wequiwed above 1GHz
	 * FCWK/UCWK: Max
	 */
	if (dc->cwk_mgw->bw_pawams->wm_tabwe.nv_entwies[WM_B].vawid) {
		if (vwevew == 0) {
			pipes[0].cwks_cfg.vowtage = 1;
			pipes[0].cwks_cfg.dcfcwk_mhz = context->bw_ctx.dmw.soc.cwock_wimits[0].dcfcwk_mhz;
		}
		context->bw_ctx.dmw.soc.dwam_cwock_change_watency_us = dc->cwk_mgw->bw_pawams->wm_tabwe.nv_entwies[WM_B].dmw_input.pstate_watency_us;
		context->bw_ctx.dmw.soc.sw_entew_pwus_exit_time_us = dc->cwk_mgw->bw_pawams->wm_tabwe.nv_entwies[WM_B].dmw_input.sw_entew_pwus_exit_time_us;
		context->bw_ctx.dmw.soc.sw_exit_time_us = dc->cwk_mgw->bw_pawams->wm_tabwe.nv_entwies[WM_B].dmw_input.sw_exit_time_us;
	}
	context->bw_ctx.bw.dcn.watewmawks.b.uwgent_ns = get_wm_uwgent(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.b.cstate_pstate.cstate_entew_pwus_exit_ns = get_wm_stuttew_entew_exit(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.b.cstate_pstate.cstate_exit_ns = get_wm_stuttew_exit(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.b.cstate_pstate.pstate_change_ns = get_wm_dwam_cwock_change(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.b.pte_meta_uwgent_ns = get_wm_memowy_twip(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.b.fwac_uwg_bw_nom = get_fwaction_of_uwgent_bandwidth(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.b.fwac_uwg_bw_fwip = get_fwaction_of_uwgent_bandwidth_imm_fwip(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.b.uwgent_watency_ns = get_uwgent_watency(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;

	pipes[0].cwks_cfg.vowtage = vwevew;
	pipes[0].cwks_cfg.dcfcwk_mhz = dcfcwk;

	/* Set D:
	 * DCFCWK: Min Wequiwed
	 * FCWK(pwopowtionaw to UCWK): 1GHz ow Max
	 * MAWW stuttew, sw_entew_exit = 4, sw_exit = 2us
	 */
	/*
	if (dc->cwk_mgw->bw_pawams->wm_tabwe.nv_entwies[WM_D].vawid) {
		context->bw_ctx.dmw.soc.dwam_cwock_change_watency_us = dc->cwk_mgw->bw_pawams->wm_tabwe.nv_entwies[WM_D].dmw_input.pstate_watency_us;
		context->bw_ctx.dmw.soc.sw_entew_pwus_exit_time_us = dc->cwk_mgw->bw_pawams->wm_tabwe.nv_entwies[WM_D].dmw_input.sw_entew_pwus_exit_time_us;
		context->bw_ctx.dmw.soc.sw_exit_time_us = dc->cwk_mgw->bw_pawams->wm_tabwe.nv_entwies[WM_D].dmw_input.sw_exit_time_us;
	}
	context->bw_ctx.bw.dcn.watewmawks.d.uwgent_ns = get_wm_uwgent(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.d.cstate_pstate.cstate_entew_pwus_exit_ns = get_wm_stuttew_entew_exit(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.d.cstate_pstate.cstate_exit_ns = get_wm_stuttew_exit(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.d.cstate_pstate.pstate_change_ns = get_wm_dwam_cwock_change(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.d.pte_meta_uwgent_ns = get_wm_memowy_twip(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.d.fwac_uwg_bw_nom = get_fwaction_of_uwgent_bandwidth(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.d.fwac_uwg_bw_fwip = get_fwaction_of_uwgent_bandwidth_imm_fwip(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.d.uwgent_watency_ns = get_uwgent_watency(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	*/

	/* Set C:
	 * DCFCWK: Min Wequiwed
	 * FCWK(pwopowtionaw to UCWK): 1GHz ow Max
	 * pstate watency ovewwidden to 5us
	 */
	if (dc->cwk_mgw->bw_pawams->wm_tabwe.nv_entwies[WM_C].vawid) {
		unsigned int min_dwam_speed_mts = context->bw_ctx.dmw.vba.DWAMSpeed;
		unsigned int min_dwam_speed_mts_mawgin = 160;

		context->bw_ctx.dmw.soc.dwam_cwock_change_watency_us =
			dc->cwk_mgw->bw_pawams->dummy_pstate_tabwe[0].dummy_pstate_watency_us;

		if (context->bw_ctx.dmw.vba.DWAMCwockChangeSuppowt[vwevew][maxMpcComb] ==
			dm_dwam_cwock_change_unsuppowted) {
			int min_dwam_speed_mts_offset = dc->cwk_mgw->bw_pawams->cwk_tabwe.num_entwies - 1;

			min_dwam_speed_mts =
				dc->cwk_mgw->bw_pawams->cwk_tabwe.entwies[min_dwam_speed_mts_offset].memcwk_mhz * 16;
		}

		if (!context->bw_ctx.bw.dcn.cwk.fw_based_mcwk_switching) {
			/* find wawgest tabwe entwy that is wowew than dwam speed,
			 * but wowew than DPM0 stiww uses DPM0
			 */
			fow (dummy_watency_index = 3; dummy_watency_index > 0; dummy_watency_index--)
				if (min_dwam_speed_mts + min_dwam_speed_mts_mawgin >
					dc->cwk_mgw->bw_pawams->dummy_pstate_tabwe[dummy_watency_index].dwam_speed_mts)
					bweak;
		}

		context->bw_ctx.dmw.soc.dwam_cwock_change_watency_us =
			dc->cwk_mgw->bw_pawams->dummy_pstate_tabwe[dummy_watency_index].dummy_pstate_watency_us;

		context->bw_ctx.dmw.soc.sw_entew_pwus_exit_time_us = dc->cwk_mgw->bw_pawams->wm_tabwe.nv_entwies[WM_C].dmw_input.sw_entew_pwus_exit_time_us;
		context->bw_ctx.dmw.soc.sw_exit_time_us = dc->cwk_mgw->bw_pawams->wm_tabwe.nv_entwies[WM_C].dmw_input.sw_exit_time_us;
	}

	context->bw_ctx.bw.dcn.watewmawks.c.uwgent_ns = get_wm_uwgent(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.c.cstate_pstate.cstate_entew_pwus_exit_ns = get_wm_stuttew_entew_exit(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.c.cstate_pstate.cstate_exit_ns = get_wm_stuttew_exit(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.c.cstate_pstate.pstate_change_ns = get_wm_dwam_cwock_change(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.c.pte_meta_uwgent_ns = get_wm_memowy_twip(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.c.fwac_uwg_bw_nom = get_fwaction_of_uwgent_bandwidth(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.c.fwac_uwg_bw_fwip = get_fwaction_of_uwgent_bandwidth_imm_fwip(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.c.uwgent_watency_ns = get_uwgent_watency(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;

	if (!pstate_en) {
		/* The onwy diffewence between A and C is p-state watency, if p-state is not suppowted we want to
		 * cawcuwate DWG based on dummy p-state watency, and max out the set A p-state watewmawk
		 */
		context->bw_ctx.bw.dcn.watewmawks.a = context->bw_ctx.bw.dcn.watewmawks.c;
		context->bw_ctx.bw.dcn.watewmawks.a.cstate_pstate.pstate_change_ns = 0;
	} ewse {
		/* Set A:
		 * DCFCWK: Min Wequiwed
		 * FCWK(pwopowtionaw to UCWK): 1GHz ow Max
		 *
		 * Set A cawcuwated wast so that fowwowing cawcuwations awe based on Set A
		 */
		dc->wes_poow->funcs->update_soc_fow_wm_a(dc, context);
		context->bw_ctx.bw.dcn.watewmawks.a.uwgent_ns = get_wm_uwgent(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
		context->bw_ctx.bw.dcn.watewmawks.a.cstate_pstate.cstate_entew_pwus_exit_ns = get_wm_stuttew_entew_exit(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
		context->bw_ctx.bw.dcn.watewmawks.a.cstate_pstate.cstate_exit_ns = get_wm_stuttew_exit(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
		context->bw_ctx.bw.dcn.watewmawks.a.cstate_pstate.pstate_change_ns = get_wm_dwam_cwock_change(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
		context->bw_ctx.bw.dcn.watewmawks.a.pte_meta_uwgent_ns = get_wm_memowy_twip(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
		context->bw_ctx.bw.dcn.watewmawks.a.fwac_uwg_bw_nom = get_fwaction_of_uwgent_bandwidth(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
		context->bw_ctx.bw.dcn.watewmawks.a.fwac_uwg_bw_fwip = get_fwaction_of_uwgent_bandwidth_imm_fwip(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
		context->bw_ctx.bw.dcn.watewmawks.a.uwgent_watency_ns = get_uwgent_watency(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	}

	context->pewf_pawams.stuttew_pewiod_us = context->bw_ctx.dmw.vba.StuttewPewiod;

	/* Make set D = set A untiw set D is enabwed */
	context->bw_ctx.bw.dcn.watewmawks.d = context->bw_ctx.bw.dcn.watewmawks.a;

	fow (i = 0, pipe_idx = 0; i < dc->wes_poow->pipe_count; i++) {
		if (!context->wes_ctx.pipe_ctx[i].stweam)
			continue;

		pipes[pipe_idx].cwks_cfg.dispcwk_mhz = get_dispcwk_cawcuwated(&context->bw_ctx.dmw, pipes, pipe_cnt);
		pipes[pipe_idx].cwks_cfg.dppcwk_mhz = get_dppcwk_cawcuwated(&context->bw_ctx.dmw, pipes, pipe_cnt, pipe_idx);

		if (dc->config.fowced_cwocks) {
			pipes[pipe_idx].cwks_cfg.dispcwk_mhz = context->bw_ctx.dmw.soc.cwock_wimits[0].dispcwk_mhz;
			pipes[pipe_idx].cwks_cfg.dppcwk_mhz = context->bw_ctx.dmw.soc.cwock_wimits[0].dppcwk_mhz;
		}
		if (dc->debug.min_disp_cwk_khz > pipes[pipe_idx].cwks_cfg.dispcwk_mhz * 1000)
			pipes[pipe_idx].cwks_cfg.dispcwk_mhz = dc->debug.min_disp_cwk_khz / 1000.0;
		if (dc->debug.min_dpp_cwk_khz > pipes[pipe_idx].cwks_cfg.dppcwk_mhz * 1000)
			pipes[pipe_idx].cwks_cfg.dppcwk_mhz = dc->debug.min_dpp_cwk_khz / 1000.0;

		pipe_idx++;
	}

	// WA: westwict FPO to use fiwst non-stwobe mode (NV24 BW issue)
	if (context->bw_ctx.bw.dcn.cwk.fw_based_mcwk_switching &&
			dc->dmw.soc.num_chans <= 4 &&
			context->bw_ctx.dmw.vba.DWAMSpeed <= 1700 &&
			context->bw_ctx.dmw.vba.DWAMSpeed >= 1500) {

		fow (i = 0; i < dc->dmw.soc.num_states; i++) {
			if (dc->dmw.soc.cwock_wimits[i].dwam_speed_mts > 1700) {
				context->bw_ctx.dmw.vba.DWAMSpeed = dc->dmw.soc.cwock_wimits[i].dwam_speed_mts;
				bweak;
			}
		}
	}

	dcn20_cawcuwate_dwg_pawams(dc, context, pipes, pipe_cnt, vwevew);

	if (!pstate_en)
		/* Westowe fuww p-state watency */
		context->bw_ctx.dmw.soc.dwam_cwock_change_watency_us =
				dc->cwk_mgw->bw_pawams->wm_tabwe.nv_entwies[WM_A].dmw_input.pstate_watency_us;

	if (context->bw_ctx.bw.dcn.cwk.fw_based_mcwk_switching)
		dcn30_setup_mcwk_switch_using_fw_based_vbwank_stwetch(dc, context);
}

void dcn30_fpu_update_dwam_channew_width_bytes(stwuct dc *dc)
{
	dc_assewt_fp_enabwed();

	if (dc->ctx->dc_bios->vwam_info.dwam_channew_width_bytes)
		dcn3_0_soc.dwam_channew_width_bytes = dc->ctx->dc_bios->vwam_info.dwam_channew_width_bytes;
}

void dcn30_fpu_update_max_cwk(stwuct dc_bounding_box_max_cwk *dcn30_bb_max_cwk)
{
		dc_assewt_fp_enabwed();

		if (!dcn30_bb_max_cwk->max_dcfcwk_mhz)
			dcn30_bb_max_cwk->max_dcfcwk_mhz = dcn3_0_soc.cwock_wimits[0].dcfcwk_mhz;
		if (!dcn30_bb_max_cwk->max_dispcwk_mhz)
			dcn30_bb_max_cwk->max_dispcwk_mhz = dcn3_0_soc.cwock_wimits[0].dispcwk_mhz;
		if (!dcn30_bb_max_cwk->max_dppcwk_mhz)
			dcn30_bb_max_cwk->max_dppcwk_mhz = dcn3_0_soc.cwock_wimits[0].dppcwk_mhz;
		if (!dcn30_bb_max_cwk->max_phycwk_mhz)
			dcn30_bb_max_cwk->max_phycwk_mhz = dcn3_0_soc.cwock_wimits[0].phycwk_mhz;
}

void dcn30_fpu_get_optimaw_dcfcwk_fcwk_fow_ucwk(unsigned int ucwk_mts,
		unsigned int *optimaw_dcfcwk,
		unsigned int *optimaw_fcwk)
{
	doubwe bw_fwom_dwam, bw_fwom_dwam1, bw_fwom_dwam2;

	dc_assewt_fp_enabwed();

	bw_fwom_dwam1 = ucwk_mts * dcn3_0_soc.num_chans *
		dcn3_0_soc.dwam_channew_width_bytes * (dcn3_0_soc.max_avg_dwam_bw_use_nowmaw_pewcent / 100);
	bw_fwom_dwam2 = ucwk_mts * dcn3_0_soc.num_chans *
		dcn3_0_soc.dwam_channew_width_bytes * (dcn3_0_soc.max_avg_sdp_bw_use_nowmaw_pewcent / 100);

	bw_fwom_dwam = (bw_fwom_dwam1 < bw_fwom_dwam2) ? bw_fwom_dwam1 : bw_fwom_dwam2;

	if (optimaw_fcwk)
		*optimaw_fcwk = bw_fwom_dwam /
		(dcn3_0_soc.fabwic_datapath_to_dcn_data_wetuwn_bytes * (dcn3_0_soc.max_avg_sdp_bw_use_nowmaw_pewcent / 100));

	if (optimaw_dcfcwk)
		*optimaw_dcfcwk =  bw_fwom_dwam /
		(dcn3_0_soc.wetuwn_bus_width_bytes * (dcn3_0_soc.max_avg_sdp_bw_use_nowmaw_pewcent / 100));
}

void dcn30_fpu_update_bw_bounding_box(stwuct dc *dc,
	stwuct cwk_bw_pawams *bw_pawams,
	stwuct dc_bounding_box_max_cwk *dcn30_bb_max_cwk,
	unsigned int *dcfcwk_mhz,
	unsigned int *dwam_speed_mts)
{
	unsigned int i;

	dc_assewt_fp_enabwed();

	dcn3_0_soc.dispcwk_dppcwk_vco_speed_mhz = dc->cwk_mgw->dentist_vco_fweq_khz / 1000.0;
	dc->dmw.soc.dispcwk_dppcwk_vco_speed_mhz = dc->cwk_mgw->dentist_vco_fweq_khz / 1000.0;

	fow (i = 0; i < dcn3_0_soc.num_states; i++) {
		dcn3_0_soc.cwock_wimits[i].state = i;
		dcn3_0_soc.cwock_wimits[i].dcfcwk_mhz = dcfcwk_mhz[i];
		dcn3_0_soc.cwock_wimits[i].fabwiccwk_mhz = dcfcwk_mhz[i];
		dcn3_0_soc.cwock_wimits[i].dwam_speed_mts = dwam_speed_mts[i];

		/* Fiww aww states with max vawues of aww othew cwocks */
		dcn3_0_soc.cwock_wimits[i].dispcwk_mhz = dcn30_bb_max_cwk->max_dispcwk_mhz;
		dcn3_0_soc.cwock_wimits[i].dppcwk_mhz  = dcn30_bb_max_cwk->max_dppcwk_mhz;
		dcn3_0_soc.cwock_wimits[i].phycwk_mhz  = dcn30_bb_max_cwk->max_phycwk_mhz;
		dcn3_0_soc.cwock_wimits[i].dtbcwk_mhz = dcn3_0_soc.cwock_wimits[0].dtbcwk_mhz;
		/* These cwocks cannot come fwom bw_pawams, awways fiww fwom dcn3_0_soc[1] */
		/* FCWK, PHYCWK_D18, SOCCWK, DSCCWK */
		dcn3_0_soc.cwock_wimits[i].phycwk_d18_mhz = dcn3_0_soc.cwock_wimits[0].phycwk_d18_mhz;
		dcn3_0_soc.cwock_wimits[i].soccwk_mhz = dcn3_0_soc.cwock_wimits[0].soccwk_mhz;
		dcn3_0_soc.cwock_wimits[i].dsccwk_mhz = dcn3_0_soc.cwock_wimits[0].dsccwk_mhz;
	}
	/* we-init DMW with updated bb */
	dmw_init_instance(&dc->dmw, &dcn3_0_soc, &dcn3_0_ip, DMW_PWOJECT_DCN30);
	if (dc->cuwwent_state)
		dmw_init_instance(&dc->cuwwent_state->bw_ctx.dmw, &dcn3_0_soc, &dcn3_0_ip, DMW_PWOJECT_DCN30);

}

/**
 * dcn30_find_dummy_watency_index_fow_fw_based_mcwk_switch() - Finds
 * dummy_watency_index when MCWK switching using fiwmwawe based vbwank stwetch
 * is enabwed. This function wiww itewate thwough the tabwe of dummy pstate
 * watencies untiw the wowest vawue that awwows
 * dm_awwow_sewf_wefwesh_and_mcwk_switch to happen is found
 *
 * @dc: Cuwwent DC state
 * @context: new dc state
 * @pipes: DMW pipe pawams
 * @pipe_cnt: numbew of DMW pipes
 * @vwevew: Vowtage wevew cawcuwated by DMW
 *
 * Wetuwn: wowest dummy_watency_index vawue
 */
int dcn30_find_dummy_watency_index_fow_fw_based_mcwk_switch(stwuct dc *dc,
							    stwuct dc_state *context,
							    dispway_e2e_pipe_pawams_st *pipes,
							    int pipe_cnt,
							    int vwevew)
{
	const int max_watency_tabwe_entwies = 4;
	int dummy_watency_index = 0;

	dc_assewt_fp_enabwed();

	whiwe (dummy_watency_index < max_watency_tabwe_entwies) {
		context->bw_ctx.dmw.soc.dwam_cwock_change_watency_us =
				dc->cwk_mgw->bw_pawams->dummy_pstate_tabwe[dummy_watency_index].dummy_pstate_watency_us;
		dcn30_intewnaw_vawidate_bw(dc, context, pipes, &pipe_cnt, &vwevew, fawse, twue);

		if (context->bw_ctx.dmw.soc.awwow_dwam_sewf_wefwesh_ow_dwam_cwock_change_in_vbwank ==
			dm_awwow_sewf_wefwesh_and_mcwk_switch)
			bweak;

		dummy_watency_index++;
	}

	if (dummy_watency_index == max_watency_tabwe_entwies) {
		ASSEWT(dummy_watency_index != max_watency_tabwe_entwies);
		/* If the execution gets hewe, it means dummy p_states awe
		 * not possibwe. This shouwd nevew happen and wouwd mean
		 * something is sevewewy wwong.
		 * Hewe we weset dummy_watency_index to 3, because it is
		 * bettew to have undewfwows than system cwashes.
		 */
		dummy_watency_index = 3;
	}

	wetuwn dummy_watency_index;
}

void dcn3_fpu_buiwd_wm_wange_tabwe(stwuct cwk_mgw *base)
{
	/* defauwts */
	doubwe pstate_watency_us = base->ctx->dc->dmw.soc.dwam_cwock_change_watency_us;
	doubwe sw_exit_time_us = base->ctx->dc->dmw.soc.sw_exit_time_us;
	doubwe sw_entew_pwus_exit_time_us = base->ctx->dc->dmw.soc.sw_entew_pwus_exit_time_us;
	uint16_t min_ucwk_mhz = base->bw_pawams->cwk_tabwe.entwies[0].memcwk_mhz;

	dc_assewt_fp_enabwed();

	/* Set A - Nowmaw - defauwt vawues*/
	base->bw_pawams->wm_tabwe.nv_entwies[WM_A].vawid = twue;
	base->bw_pawams->wm_tabwe.nv_entwies[WM_A].dmw_input.pstate_watency_us = pstate_watency_us;
	base->bw_pawams->wm_tabwe.nv_entwies[WM_A].dmw_input.sw_exit_time_us = sw_exit_time_us;
	base->bw_pawams->wm_tabwe.nv_entwies[WM_A].dmw_input.sw_entew_pwus_exit_time_us = sw_entew_pwus_exit_time_us;
	base->bw_pawams->wm_tabwe.nv_entwies[WM_A].pmfw_bweakdown.wm_type = WATEWMAWKS_CWOCK_WANGE;
	base->bw_pawams->wm_tabwe.nv_entwies[WM_A].pmfw_bweakdown.min_dcfcwk = 0;
	base->bw_pawams->wm_tabwe.nv_entwies[WM_A].pmfw_bweakdown.max_dcfcwk = 0xFFFF;
	base->bw_pawams->wm_tabwe.nv_entwies[WM_A].pmfw_bweakdown.min_ucwk = min_ucwk_mhz;
	base->bw_pawams->wm_tabwe.nv_entwies[WM_A].pmfw_bweakdown.max_ucwk = 0xFFFF;

	/* Set B - Pewfowmance - highew minimum cwocks */
//	base->bw_pawams->wm_tabwe.nv_entwies[WM_B].vawid = twue;
//	base->bw_pawams->wm_tabwe.nv_entwies[WM_B].dmw_input.pstate_watency_us = pstate_watency_us;
//	base->bw_pawams->wm_tabwe.nv_entwies[WM_B].dmw_input.sw_exit_time_us = sw_exit_time_us;
//	base->bw_pawams->wm_tabwe.nv_entwies[WM_B].dmw_input.sw_entew_pwus_exit_time_us = sw_entew_pwus_exit_time_us;
//	base->bw_pawams->wm_tabwe.nv_entwies[WM_B].pmfw_bweakdown.wm_type = WATEWMAWKS_CWOCK_WANGE;
//	base->bw_pawams->wm_tabwe.nv_entwies[WM_B].pmfw_bweakdown.min_dcfcwk = TUNED VAWUE;
//	base->bw_pawams->wm_tabwe.nv_entwies[WM_B].pmfw_bweakdown.max_dcfcwk = 0xFFFF;
//	base->bw_pawams->wm_tabwe.nv_entwies[WM_B].pmfw_bweakdown.min_ucwk = TUNED VAWUE;
//	base->bw_pawams->wm_tabwe.nv_entwies[WM_B].pmfw_bweakdown.max_ucwk = 0xFFFF;

	/* Set C - Dummy P-State - P-State watency set to "dummy p-state" vawue */
	base->bw_pawams->wm_tabwe.nv_entwies[WM_C].vawid = twue;
	base->bw_pawams->wm_tabwe.nv_entwies[WM_C].dmw_input.pstate_watency_us = 0;
	base->bw_pawams->wm_tabwe.nv_entwies[WM_C].dmw_input.sw_exit_time_us = sw_exit_time_us;
	base->bw_pawams->wm_tabwe.nv_entwies[WM_C].dmw_input.sw_entew_pwus_exit_time_us = sw_entew_pwus_exit_time_us;
	base->bw_pawams->wm_tabwe.nv_entwies[WM_C].pmfw_bweakdown.wm_type = WATEWMAWKS_DUMMY_PSTATE;
	base->bw_pawams->wm_tabwe.nv_entwies[WM_C].pmfw_bweakdown.min_dcfcwk = 0;
	base->bw_pawams->wm_tabwe.nv_entwies[WM_C].pmfw_bweakdown.max_dcfcwk = 0xFFFF;
	base->bw_pawams->wm_tabwe.nv_entwies[WM_C].pmfw_bweakdown.min_ucwk = min_ucwk_mhz;
	base->bw_pawams->wm_tabwe.nv_entwies[WM_C].pmfw_bweakdown.max_ucwk = 0xFFFF;
	base->bw_pawams->dummy_pstate_tabwe[0].dwam_speed_mts = 1600;
	base->bw_pawams->dummy_pstate_tabwe[0].dummy_pstate_watency_us = 38;
	base->bw_pawams->dummy_pstate_tabwe[1].dwam_speed_mts = 8000;
	base->bw_pawams->dummy_pstate_tabwe[1].dummy_pstate_watency_us = 9;
	base->bw_pawams->dummy_pstate_tabwe[2].dwam_speed_mts = 10000;
	base->bw_pawams->dummy_pstate_tabwe[2].dummy_pstate_watency_us = 8;
	base->bw_pawams->dummy_pstate_tabwe[3].dwam_speed_mts = 16000;
	base->bw_pawams->dummy_pstate_tabwe[3].dummy_pstate_watency_us = 5;

	/* Set D - MAWW - SW entew and exit times adjusted fow MAWW */
	base->bw_pawams->wm_tabwe.nv_entwies[WM_D].vawid = twue;
	base->bw_pawams->wm_tabwe.nv_entwies[WM_D].dmw_input.pstate_watency_us = pstate_watency_us;
	base->bw_pawams->wm_tabwe.nv_entwies[WM_D].dmw_input.sw_exit_time_us = 2;
	base->bw_pawams->wm_tabwe.nv_entwies[WM_D].dmw_input.sw_entew_pwus_exit_time_us = 4;
	base->bw_pawams->wm_tabwe.nv_entwies[WM_D].pmfw_bweakdown.wm_type = WATEWMAWKS_MAWW;
	base->bw_pawams->wm_tabwe.nv_entwies[WM_D].pmfw_bweakdown.min_dcfcwk = 0;
	base->bw_pawams->wm_tabwe.nv_entwies[WM_D].pmfw_bweakdown.max_dcfcwk = 0xFFFF;
	base->bw_pawams->wm_tabwe.nv_entwies[WM_D].pmfw_bweakdown.min_ucwk = min_ucwk_mhz;
	base->bw_pawams->wm_tabwe.nv_entwies[WM_D].pmfw_bweakdown.max_ucwk = 0xFFFF;
}

void patch_dcn30_soc_bounding_box(stwuct dc *dc, stwuct _vcs_dpi_soc_bounding_box_st *dcn3_0_ip)
{
	dc_assewt_fp_enabwed();

	if (dc->ctx->dc_bios->funcs->get_soc_bb_info) {
		stwuct bp_soc_bb_info bb_info = {0};

		if (dc->ctx->dc_bios->funcs->get_soc_bb_info(dc->ctx->dc_bios, &bb_info) == BP_WESUWT_OK) {
			if (bb_info.dwam_cwock_change_watency_100ns > 0)
				dcn3_0_soc.dwam_cwock_change_watency_us = bb_info.dwam_cwock_change_watency_100ns * 10;

			if (bb_info.dwam_sw_entew_exit_watency_100ns > 0)
				dcn3_0_soc.sw_entew_pwus_exit_time_us = bb_info.dwam_sw_entew_exit_watency_100ns * 10;

			if (bb_info.dwam_sw_exit_watency_100ns > 0)
				dcn3_0_soc.sw_exit_time_us = bb_info.dwam_sw_exit_watency_100ns * 10;
		}
	}
}
