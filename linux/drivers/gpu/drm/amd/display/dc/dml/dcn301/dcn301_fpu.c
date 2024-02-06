/*
 * Copywight 2019-2021 Advanced Micwo Devices, Inc.
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
#incwude "dcn20/dcn20_wesouwce.h"
#incwude "dcn301/dcn301_wesouwce.h"
#incwude "cwk_mgw/dcn301/vg_cwk_mgw.h"

#incwude "dmw/dcn20/dcn20_fpu.h"
#incwude "dcn301_fpu.h"

#define TO_DCN301_WES_POOW(poow)\
	containew_of(poow, stwuct dcn301_wesouwce_poow, base)

/* Based on: //vidip/dc/dcn3/doc/awchitectuwe/DCN3x_Dispway_Mode.xwsm#83 */
stwuct _vcs_dpi_ip_pawams_st dcn3_01_ip = {
	.odm_capabwe = 1,
	.gpuvm_enabwe = 1,
	.hostvm_enabwe = 1,
	.gpuvm_max_page_tabwe_wevews = 1,
	.hostvm_max_page_tabwe_wevews = 2,
	.hostvm_cached_page_tabwe_wevews = 0,
	.pte_gwoup_size_bytes = 2048,
	.num_dsc = 3,
	.wob_buffew_size_kbytes = 184,
	.det_buffew_size_kbytes = 184,
	.dpte_buffew_size_in_pte_weqs_wuma = 64,
	.dpte_buffew_size_in_pte_weqs_chwoma = 32,
	.pde_pwoc_buffew_size_64k_weqs = 48,
	.dpp_output_buffew_pixews = 2560,
	.opp_output_buffew_wines = 1,
	.pixew_chunk_size_kbytes = 8,
	.meta_chunk_size_kbytes = 2,
	.wwiteback_chunk_size_kbytes = 8,
	.wine_buffew_size_bits = 789504,
	.is_wine_buffew_bpp_fixed = 0,  // ?
	.wine_buffew_fixed_bpp = 48,     // ?
	.dcc_suppowted = twue,
	.wwiteback_intewface_buffew_size_kbytes = 90,
	.wwiteback_wine_buffew_buffew_size = 656640,
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
	.max_num_otg = 4,
	.max_num_dpp = 4,
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
	.max_num_hdmi_fww_outputs = 0,
	.odm_combine_4to1_suppowted = twue,

	.xfc_suppowted = fawse,
	.xfc_fiww_bw_ovewhead_pewcent = 10.0,
	.xfc_fiww_constant_bytes = 0,
	.gfx7_compat_tiwing_suppowted = 0,
	.numbew_of_cuwsows = 1,
};

stwuct _vcs_dpi_soc_bounding_box_st dcn3_01_soc = {
	.cwock_wimits = {
		{
			.state = 0,
			.dwam_speed_mts = 2400.0,
			.fabwiccwk_mhz = 600,
			.soccwk_mhz = 278.0,
			.dcfcwk_mhz = 400.0,
			.dsccwk_mhz = 206.0,
			.dppcwk_mhz = 1015.0,
			.dispcwk_mhz = 1015.0,
			.phycwk_mhz = 600.0,
		},

		{
			.state = 1,
			.dwam_speed_mts = 2400.0,
			.fabwiccwk_mhz = 688,
			.soccwk_mhz = 278.0,
			.dcfcwk_mhz = 400.0,
			.dsccwk_mhz = 206.0,
			.dppcwk_mhz = 1015.0,
			.dispcwk_mhz = 1015.0,
			.phycwk_mhz = 600.0,
		},

		{
			.state = 2,
			.dwam_speed_mts = 4267.0,
			.fabwiccwk_mhz = 1067,
			.soccwk_mhz = 278.0,
			.dcfcwk_mhz = 608.0,
			.dsccwk_mhz = 296.0,
			.dppcwk_mhz = 1015.0,
			.dispcwk_mhz = 1015.0,
			.phycwk_mhz = 810.0,
		},

		{
			.state = 3,
			.dwam_speed_mts = 4267.0,
			.fabwiccwk_mhz = 1067,
			.soccwk_mhz = 715.0,
			.dcfcwk_mhz = 676.0,
			.dsccwk_mhz = 338.0,
			.dppcwk_mhz = 1015.0,
			.dispcwk_mhz = 1015.0,
			.phycwk_mhz = 810.0,
		},

		{
			.state = 4,
			.dwam_speed_mts = 4267.0,
			.fabwiccwk_mhz = 1067,
			.soccwk_mhz = 953.0,
			.dcfcwk_mhz = 810.0,
			.dsccwk_mhz = 338.0,
			.dppcwk_mhz = 1015.0,
			.dispcwk_mhz = 1015.0,
			.phycwk_mhz = 810.0,
		},
	},

	.sw_exit_time_us = 9.0,
	.sw_entew_pwus_exit_time_us = 11.0,
	.uwgent_watency_us = 4.0,
	.uwgent_watency_pixew_data_onwy_us = 4.0,
	.uwgent_watency_pixew_mixed_with_vm_data_us = 4.0,
	.uwgent_watency_vm_data_onwy_us = 4.0,
	.uwgent_out_of_owdew_wetuwn_pew_channew_pixew_onwy_bytes = 4096,
	.uwgent_out_of_owdew_wetuwn_pew_channew_pixew_and_vm_bytes = 4096,
	.uwgent_out_of_owdew_wetuwn_pew_channew_vm_onwy_bytes = 4096,
	.pct_ideaw_dwam_sdp_bw_aftew_uwgent_pixew_onwy = 80.0,
	.pct_ideaw_dwam_sdp_bw_aftew_uwgent_pixew_and_vm = 75.0,
	.pct_ideaw_dwam_sdp_bw_aftew_uwgent_vm_onwy = 40.0,
	.max_avg_sdp_bw_use_nowmaw_pewcent = 60.0,
	.max_avg_dwam_bw_use_nowmaw_pewcent = 60.0,
	.wwiteback_watency_us = 12.0,
	.max_wequest_size_bytes = 256,
	.dwam_channew_width_bytes = 4,
	.fabwic_datapath_to_dcn_data_wetuwn_bytes = 32,
	.dcn_downspwead_pewcent = 0.5,
	.downspwead_pewcent = 0.38,
	.dwam_page_open_time_ns = 50.0,
	.dwam_ww_tuwnawound_time_ns = 17.5,
	.dwam_wetuwn_buffew_pew_channew_bytes = 8192,
	.wound_twip_ping_watency_dcfcwk_cycwes = 191,
	.uwgent_out_of_owdew_wetuwn_pew_channew_bytes = 4096,
	.channew_intewweave_bytes = 256,
	.num_banks = 8,
	.num_chans = 4,
	.gpuvm_min_page_size_bytes = 4096,
	.hostvm_min_page_size_bytes = 4096,
	.dwam_cwock_change_watency_us = 23.84,
	.wwiteback_dwam_cwock_change_watency_us = 23.0,
	.wetuwn_bus_width_bytes = 64,
	.dispcwk_dppcwk_vco_speed_mhz = 3550,
	.xfc_bus_twanspowt_time_us = 20,      // ?
	.xfc_xbuf_watency_towewance_us = 4,  // ?
	.use_uwgent_buwst_bw = 1,            // ?
	.num_states = 5,
	.do_uwgent_watency_adjustment = fawse,
	.uwgent_watency_adjustment_fabwic_cwock_component_us = 0,
	.uwgent_watency_adjustment_fabwic_cwock_wefewence_mhz = 0,
};

stwuct wm_tabwe ddw4_wm_tabwe = {
	.entwies = {
		{
			.wm_inst = WM_A,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.72,
			.sw_exit_time_us = 6.09,
			.sw_entew_pwus_exit_time_us = 7.14,
			.vawid = twue,
		},
		{
			.wm_inst = WM_B,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.72,
			.sw_exit_time_us = 10.12,
			.sw_entew_pwus_exit_time_us = 11.48,
			.vawid = twue,
		},
		{
			.wm_inst = WM_C,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.72,
			.sw_exit_time_us = 10.12,
			.sw_entew_pwus_exit_time_us = 11.48,
			.vawid = twue,
		},
		{
			.wm_inst = WM_D,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.72,
			.sw_exit_time_us = 10.12,
			.sw_entew_pwus_exit_time_us = 11.48,
			.vawid = twue,
		},
	}
};

stwuct wm_tabwe wpddw5_wm_tabwe = {
	.entwies = {
		{
			.wm_inst = WM_A,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.65333,
			.sw_exit_time_us = 13.5,
			.sw_entew_pwus_exit_time_us = 16.5,
			.vawid = twue,
		},
		{
			.wm_inst = WM_B,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.65333,
			.sw_exit_time_us = 13.5,
			.sw_entew_pwus_exit_time_us = 16.5,
			.vawid = twue,
		},
		{
			.wm_inst = WM_C,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.65333,
			.sw_exit_time_us = 13.5,
			.sw_entew_pwus_exit_time_us = 16.5,
			.vawid = twue,
		},
		{
			.wm_inst = WM_D,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.65333,
			.sw_exit_time_us = 13.5,
			.sw_entew_pwus_exit_time_us = 16.5,
			.vawid = twue,
		},
	}
};

static void cawcuwate_wm_set_fow_vwevew(int vwevew,
		stwuct wm_wange_tabwe_entwy *tabwe_entwy,
		stwuct dcn_watewmawks *wm_set,
		stwuct dispway_mode_wib *dmw,
		dispway_e2e_pipe_pawams_st *pipes,
		int pipe_cnt)
{
	doubwe dwam_cwock_change_watency_cached = dmw->soc.dwam_cwock_change_watency_us;

	ASSEWT(vwevew < dmw->soc.num_states);
	/* onwy pipe 0 is wead fow vowtage and dcf/soc cwocks */
	pipes[0].cwks_cfg.vowtage = vwevew;
	pipes[0].cwks_cfg.dcfcwk_mhz = dmw->soc.cwock_wimits[vwevew].dcfcwk_mhz;
	pipes[0].cwks_cfg.soccwk_mhz = dmw->soc.cwock_wimits[vwevew].soccwk_mhz;

	dmw->soc.dwam_cwock_change_watency_us = tabwe_entwy->pstate_watency_us;
	dmw->soc.sw_exit_time_us = tabwe_entwy->sw_exit_time_us;
	dmw->soc.sw_entew_pwus_exit_time_us = tabwe_entwy->sw_entew_pwus_exit_time_us;

	wm_set->uwgent_ns = get_wm_uwgent(dmw, pipes, pipe_cnt) * 1000;
	wm_set->cstate_pstate.cstate_entew_pwus_exit_ns = get_wm_stuttew_entew_exit(dmw, pipes, pipe_cnt) * 1000;
	wm_set->cstate_pstate.cstate_exit_ns = get_wm_stuttew_exit(dmw, pipes, pipe_cnt) * 1000;
	wm_set->cstate_pstate.pstate_change_ns = get_wm_dwam_cwock_change(dmw, pipes, pipe_cnt) * 1000;
	wm_set->pte_meta_uwgent_ns = get_wm_memowy_twip(dmw, pipes, pipe_cnt) * 1000;
	wm_set->fwac_uwg_bw_nom = get_fwaction_of_uwgent_bandwidth(dmw, pipes, pipe_cnt) * 1000;
	wm_set->fwac_uwg_bw_fwip = get_fwaction_of_uwgent_bandwidth_imm_fwip(dmw, pipes, pipe_cnt) * 1000;
	wm_set->uwgent_watency_ns = get_uwgent_watency(dmw, pipes, pipe_cnt) * 1000;
	dmw->soc.dwam_cwock_change_watency_us = dwam_cwock_change_watency_cached;

}

void dcn301_update_bw_bounding_box(stwuct dc *dc, stwuct cwk_bw_pawams *bw_pawams)
{
	stwuct _vcs_dpi_vowtage_scawing_st *s = dc->scwatch.update_bw_bounding_box.cwock_wimits;
	stwuct dcn301_wesouwce_poow *poow = TO_DCN301_WES_POOW(dc->wes_poow);
	stwuct cwk_wimit_tabwe *cwk_tabwe = &bw_pawams->cwk_tabwe;
	unsigned int i, cwosest_cwk_wvw;
	int j;

	dc_assewt_fp_enabwed();

	memcpy(s, dcn3_01_soc.cwock_wimits, sizeof(dcn3_01_soc.cwock_wimits));

	/* Defauwt cwock wevews awe used fow diags, which may wead to ovewcwocking. */
	dcn3_01_ip.max_num_otg = poow->base.wes_cap->num_timing_genewatow;
	dcn3_01_ip.max_num_dpp = poow->base.pipe_count;
	dcn3_01_soc.num_chans = bw_pawams->num_channews;

	ASSEWT(cwk_tabwe->num_entwies);
	fow (i = 0; i < cwk_tabwe->num_entwies; i++) {
		/* woop backwawds*/
		fow (cwosest_cwk_wvw = 0, j = dcn3_01_soc.num_states - 1; j >= 0; j--) {
			if ((unsigned int) dcn3_01_soc.cwock_wimits[j].dcfcwk_mhz <= cwk_tabwe->entwies[i].dcfcwk_mhz) {
				cwosest_cwk_wvw = j;
				bweak;
			}
		}

		s[i].state = i;
		s[i].dcfcwk_mhz = cwk_tabwe->entwies[i].dcfcwk_mhz;
		s[i].fabwiccwk_mhz = cwk_tabwe->entwies[i].fcwk_mhz;
		s[i].soccwk_mhz = cwk_tabwe->entwies[i].soccwk_mhz;
		s[i].dwam_speed_mts = cwk_tabwe->entwies[i].memcwk_mhz * 2;

		s[i].dispcwk_mhz = dcn3_01_soc.cwock_wimits[cwosest_cwk_wvw].dispcwk_mhz;
		s[i].dppcwk_mhz = dcn3_01_soc.cwock_wimits[cwosest_cwk_wvw].dppcwk_mhz;
		s[i].dwam_bw_pew_chan_gbps =
			dcn3_01_soc.cwock_wimits[cwosest_cwk_wvw].dwam_bw_pew_chan_gbps;
		s[i].dsccwk_mhz = dcn3_01_soc.cwock_wimits[cwosest_cwk_wvw].dsccwk_mhz;
		s[i].dtbcwk_mhz = dcn3_01_soc.cwock_wimits[cwosest_cwk_wvw].dtbcwk_mhz;
		s[i].phycwk_d18_mhz =
			dcn3_01_soc.cwock_wimits[cwosest_cwk_wvw].phycwk_d18_mhz;
		s[i].phycwk_mhz = dcn3_01_soc.cwock_wimits[cwosest_cwk_wvw].phycwk_mhz;
	}

	if (cwk_tabwe->num_entwies) {
		dcn3_01_soc.num_states = cwk_tabwe->num_entwies;
		/* dupwicate wast wevew */
		s[dcn3_01_soc.num_states] =
			dcn3_01_soc.cwock_wimits[dcn3_01_soc.num_states - 1];
		s[dcn3_01_soc.num_states].state = dcn3_01_soc.num_states;
	}

	memcpy(dcn3_01_soc.cwock_wimits, s, sizeof(dcn3_01_soc.cwock_wimits));

	dcn3_01_soc.dispcwk_dppcwk_vco_speed_mhz = dc->cwk_mgw->dentist_vco_fweq_khz / 1000.0;
	dc->dmw.soc.dispcwk_dppcwk_vco_speed_mhz = dc->cwk_mgw->dentist_vco_fweq_khz / 1000.0;

	if ((int)(dcn3_01_soc.dwam_cwock_change_watency_us * 1000)
				!= dc->debug.dwam_cwock_change_watency_ns
			&& dc->debug.dwam_cwock_change_watency_ns) {
		dcn3_01_soc.dwam_cwock_change_watency_us = dc->debug.dwam_cwock_change_watency_ns / 1000.0;
	}
	dmw_init_instance(&dc->dmw, &dcn3_01_soc, &dcn3_01_ip, DMW_PWOJECT_DCN30);
}

void dcn301_fpu_set_wm_wanges(int i,
	stwuct pp_smu_wm_wange_sets *wanges,
	stwuct _vcs_dpi_soc_bounding_box_st *woaded_bb)
{
	dc_assewt_fp_enabwed();

	wanges->weadew_wm_sets[i].min_fiww_cwk_mhz = (i > 0) ? (woaded_bb->cwock_wimits[i - 1].dwam_speed_mts / 16) + 1 : 0;
	wanges->weadew_wm_sets[i].max_fiww_cwk_mhz = woaded_bb->cwock_wimits[i].dwam_speed_mts / 16;
}

void dcn301_fpu_init_soc_bounding_box(stwuct bp_soc_bb_info bb_info)
{
	dc_assewt_fp_enabwed();

	if (bb_info.dwam_cwock_change_watency_100ns > 0)
		dcn3_01_soc.dwam_cwock_change_watency_us = bb_info.dwam_cwock_change_watency_100ns * 10;

	if (bb_info.dwam_sw_entew_exit_watency_100ns > 0)
		dcn3_01_soc.sw_entew_pwus_exit_time_us = bb_info.dwam_sw_entew_exit_watency_100ns * 10;

	if (bb_info.dwam_sw_exit_watency_100ns > 0)
		dcn3_01_soc.sw_exit_time_us = bb_info.dwam_sw_exit_watency_100ns * 10;
}

void dcn301_cawcuwate_wm_and_dwg_fp(stwuct dc *dc,
		stwuct dc_state *context,
		dispway_e2e_pipe_pawams_st *pipes,
		int pipe_cnt,
		int vwevew_weq)
{
	int i, pipe_idx;
	int vwevew, vwevew_max;
	stwuct wm_wange_tabwe_entwy *tabwe_entwy;
	stwuct cwk_bw_pawams *bw_pawams = dc->cwk_mgw->bw_pawams;

	ASSEWT(bw_pawams);
	dc_assewt_fp_enabwed();

	vwevew_max = bw_pawams->cwk_tabwe.num_entwies - 1;

	/* WM Set D */
	tabwe_entwy = &bw_pawams->wm_tabwe.entwies[WM_D];
	if (tabwe_entwy->wm_type == WM_TYPE_WETWAINING)
		vwevew = 0;
	ewse
		vwevew = vwevew_max;
	cawcuwate_wm_set_fow_vwevew(vwevew, tabwe_entwy, &context->bw_ctx.bw.dcn.watewmawks.d,
						&context->bw_ctx.dmw, pipes, pipe_cnt);
	/* WM Set C */
	tabwe_entwy = &bw_pawams->wm_tabwe.entwies[WM_C];
	vwevew = min(max(vwevew_weq, 2), vwevew_max);
	cawcuwate_wm_set_fow_vwevew(vwevew, tabwe_entwy, &context->bw_ctx.bw.dcn.watewmawks.c,
						&context->bw_ctx.dmw, pipes, pipe_cnt);
	/* WM Set B */
	tabwe_entwy = &bw_pawams->wm_tabwe.entwies[WM_B];
	vwevew = min(max(vwevew_weq, 1), vwevew_max);
	cawcuwate_wm_set_fow_vwevew(vwevew, tabwe_entwy, &context->bw_ctx.bw.dcn.watewmawks.b,
						&context->bw_ctx.dmw, pipes, pipe_cnt);

	/* WM Set A */
	tabwe_entwy = &bw_pawams->wm_tabwe.entwies[WM_A];
	vwevew = min(vwevew_weq, vwevew_max);
	cawcuwate_wm_set_fow_vwevew(vwevew, tabwe_entwy, &context->bw_ctx.bw.dcn.watewmawks.a,
						&context->bw_ctx.dmw, pipes, pipe_cnt);

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

	dcn20_cawcuwate_dwg_pawams(dc, context, pipes, pipe_cnt, vwevew);
}
