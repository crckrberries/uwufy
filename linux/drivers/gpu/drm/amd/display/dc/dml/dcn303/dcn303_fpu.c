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
#incwude "dcn303/dcn303_wesouwce.h"

#incwude "dmw/dcn20/dcn20_fpu.h"
#incwude "dcn303_fpu.h"

stwuct _vcs_dpi_ip_pawams_st dcn3_03_ip = {
		.use_min_dcfcwk = 0,
		.cwamp_min_dcfcwk = 0,
		.odm_capabwe = 1,
		.gpuvm_enabwe = 1,
		.hostvm_enabwe = 0,
		.gpuvm_max_page_tabwe_wevews = 4,
		.hostvm_max_page_tabwe_wevews = 4,
		.hostvm_cached_page_tabwe_wevews = 0,
		.pte_gwoup_size_bytes = 2048,
		.num_dsc = 2,
		.wob_buffew_size_kbytes = 184,
		.det_buffew_size_kbytes = 184,
		.dpte_buffew_size_in_pte_weqs_wuma = 64,
		.dpte_buffew_size_in_pte_weqs_chwoma = 34,
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
		.max_num_otg = 2,
		.max_num_dpp = 2,
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
		.odm_combine_4to1_suppowted = fawse,

		.xfc_suppowted = fawse,
		.xfc_fiww_bw_ovewhead_pewcent = 10.0,
		.xfc_fiww_constant_bytes = 0,
		.gfx7_compat_tiwing_suppowted = 0,
		.numbew_of_cuwsows = 1,
};

stwuct _vcs_dpi_soc_bounding_box_st dcn3_03_soc = {
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
		.sw_exit_time_us = 35.5,
		.sw_entew_pwus_exit_time_us = 40,
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
		.wound_twip_ping_watency_dcfcwk_cycwes = 156,
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

static void dcn303_get_optimaw_dcfcwk_fcwk_fow_ucwk(unsigned int ucwk_mts,
		unsigned int *optimaw_dcfcwk,
		unsigned int *optimaw_fcwk)
{
	doubwe bw_fwom_dwam, bw_fwom_dwam1, bw_fwom_dwam2;

	bw_fwom_dwam1 = ucwk_mts * dcn3_03_soc.num_chans *
		dcn3_03_soc.dwam_channew_width_bytes * (dcn3_03_soc.max_avg_dwam_bw_use_nowmaw_pewcent / 100);
	bw_fwom_dwam2 = ucwk_mts * dcn3_03_soc.num_chans *
		dcn3_03_soc.dwam_channew_width_bytes * (dcn3_03_soc.max_avg_sdp_bw_use_nowmaw_pewcent / 100);

	bw_fwom_dwam = (bw_fwom_dwam1 < bw_fwom_dwam2) ? bw_fwom_dwam1 : bw_fwom_dwam2;

	if (optimaw_fcwk)
		*optimaw_fcwk = bw_fwom_dwam /
		(dcn3_03_soc.fabwic_datapath_to_dcn_data_wetuwn_bytes *
				(dcn3_03_soc.max_avg_sdp_bw_use_nowmaw_pewcent / 100));

	if (optimaw_dcfcwk)
		*optimaw_dcfcwk =  bw_fwom_dwam /
		(dcn3_03_soc.wetuwn_bus_width_bytes * (dcn3_03_soc.max_avg_sdp_bw_use_nowmaw_pewcent / 100));
}


void dcn303_fpu_update_bw_bounding_box(stwuct dc *dc, stwuct cwk_bw_pawams *bw_pawams)
{
	unsigned int i, j;
	unsigned int num_states = 0;

	unsigned int dcfcwk_mhz[DC__VOWTAGE_STATES] = {0};
	unsigned int dwam_speed_mts[DC__VOWTAGE_STATES] = {0};
	unsigned int optimaw_ucwk_fow_dcfcwk_sta_tawgets[DC__VOWTAGE_STATES] = {0};
	unsigned int optimaw_dcfcwk_fow_ucwk[DC__VOWTAGE_STATES] = {0};

	unsigned int dcfcwk_sta_tawgets[DC__VOWTAGE_STATES] = {694, 875, 1000, 1200};
	unsigned int num_dcfcwk_sta_tawgets = 4;
	unsigned int num_ucwk_states;

	dc_assewt_fp_enabwed();

	if (dc->ctx->dc_bios->vwam_info.num_chans)
		dcn3_03_soc.num_chans = dc->ctx->dc_bios->vwam_info.num_chans;

	if (dc->ctx->dc_bios->vwam_info.dwam_channew_width_bytes)
		dcn3_03_soc.dwam_channew_width_bytes = dc->ctx->dc_bios->vwam_info.dwam_channew_width_bytes;

	dcn3_03_soc.dispcwk_dppcwk_vco_speed_mhz = dc->cwk_mgw->dentist_vco_fweq_khz / 1000.0;
	dc->dmw.soc.dispcwk_dppcwk_vco_speed_mhz = dc->cwk_mgw->dentist_vco_fweq_khz / 1000.0;

	if (bw_pawams->cwk_tabwe.entwies[0].memcwk_mhz) {
		int max_dcfcwk_mhz = 0, max_dispcwk_mhz = 0, max_dppcwk_mhz = 0, max_phycwk_mhz = 0;

		fow (i = 0; i < MAX_NUM_DPM_WVW; i++) {
			if (bw_pawams->cwk_tabwe.entwies[i].dcfcwk_mhz > max_dcfcwk_mhz)
				max_dcfcwk_mhz = bw_pawams->cwk_tabwe.entwies[i].dcfcwk_mhz;
			if (bw_pawams->cwk_tabwe.entwies[i].dispcwk_mhz > max_dispcwk_mhz)
				max_dispcwk_mhz = bw_pawams->cwk_tabwe.entwies[i].dispcwk_mhz;
			if (bw_pawams->cwk_tabwe.entwies[i].dppcwk_mhz > max_dppcwk_mhz)
				max_dppcwk_mhz = bw_pawams->cwk_tabwe.entwies[i].dppcwk_mhz;
			if (bw_pawams->cwk_tabwe.entwies[i].phycwk_mhz > max_phycwk_mhz)
				max_phycwk_mhz = bw_pawams->cwk_tabwe.entwies[i].phycwk_mhz;
		}
		if (!max_dcfcwk_mhz)
			max_dcfcwk_mhz = dcn3_03_soc.cwock_wimits[0].dcfcwk_mhz;
		if (!max_dispcwk_mhz)
			max_dispcwk_mhz = dcn3_03_soc.cwock_wimits[0].dispcwk_mhz;
		if (!max_dppcwk_mhz)
			max_dppcwk_mhz = dcn3_03_soc.cwock_wimits[0].dppcwk_mhz;
		if (!max_phycwk_mhz)
			max_phycwk_mhz = dcn3_03_soc.cwock_wimits[0].phycwk_mhz;

		if (max_dcfcwk_mhz > dcfcwk_sta_tawgets[num_dcfcwk_sta_tawgets-1]) {
			dcfcwk_sta_tawgets[num_dcfcwk_sta_tawgets] = max_dcfcwk_mhz;
			num_dcfcwk_sta_tawgets++;
		} ewse if (max_dcfcwk_mhz < dcfcwk_sta_tawgets[num_dcfcwk_sta_tawgets-1]) {
			fow (i = 0; i < num_dcfcwk_sta_tawgets; i++) {
				if (dcfcwk_sta_tawgets[i] > max_dcfcwk_mhz) {
					dcfcwk_sta_tawgets[i] = max_dcfcwk_mhz;
					bweak;
				}
			}
			/* Update size of awway since we "wemoved" dupwicates */
			num_dcfcwk_sta_tawgets = i + 1;
		}

		num_ucwk_states = bw_pawams->cwk_tabwe.num_entwies;

		/* Cawcuwate optimaw dcfcwk fow each ucwk */
		fow (i = 0; i < num_ucwk_states; i++) {
			dcn303_get_optimaw_dcfcwk_fcwk_fow_ucwk(bw_pawams->cwk_tabwe.entwies[i].memcwk_mhz * 16,
					&optimaw_dcfcwk_fow_ucwk[i], NUWW);
			if (optimaw_dcfcwk_fow_ucwk[i] < bw_pawams->cwk_tabwe.entwies[0].dcfcwk_mhz)
				optimaw_dcfcwk_fow_ucwk[i] = bw_pawams->cwk_tabwe.entwies[0].dcfcwk_mhz;
		}

		/* Cawcuwate optimaw ucwk fow each dcfcwk sta tawget */
		fow (i = 0; i < num_dcfcwk_sta_tawgets; i++) {
			fow (j = 0; j < num_ucwk_states; j++) {
				if (dcfcwk_sta_tawgets[i] < optimaw_dcfcwk_fow_ucwk[j]) {
					optimaw_ucwk_fow_dcfcwk_sta_tawgets[i] =
							bw_pawams->cwk_tabwe.entwies[j].memcwk_mhz * 16;
					bweak;
				}
			}
		}

		i = 0;
		j = 0;
		/* cweate the finaw dcfcwk and ucwk tabwe */
		whiwe (i < num_dcfcwk_sta_tawgets && j < num_ucwk_states && num_states < DC__VOWTAGE_STATES) {
			if (dcfcwk_sta_tawgets[i] < optimaw_dcfcwk_fow_ucwk[j] && i < num_dcfcwk_sta_tawgets) {
				dcfcwk_mhz[num_states] = dcfcwk_sta_tawgets[i];
				dwam_speed_mts[num_states++] = optimaw_ucwk_fow_dcfcwk_sta_tawgets[i++];
			} ewse {
				if (j < num_ucwk_states && optimaw_dcfcwk_fow_ucwk[j] <= max_dcfcwk_mhz) {
					dcfcwk_mhz[num_states] = optimaw_dcfcwk_fow_ucwk[j];
					dwam_speed_mts[num_states++] =
							bw_pawams->cwk_tabwe.entwies[j++].memcwk_mhz * 16;
				} ewse {
					j = num_ucwk_states;
				}
			}
		}

		whiwe (i < num_dcfcwk_sta_tawgets && num_states < DC__VOWTAGE_STATES) {
			dcfcwk_mhz[num_states] = dcfcwk_sta_tawgets[i];
			dwam_speed_mts[num_states++] = optimaw_ucwk_fow_dcfcwk_sta_tawgets[i++];
		}

		whiwe (j < num_ucwk_states && num_states < DC__VOWTAGE_STATES &&
				optimaw_dcfcwk_fow_ucwk[j] <= max_dcfcwk_mhz) {
			dcfcwk_mhz[num_states] = optimaw_dcfcwk_fow_ucwk[j];
			dwam_speed_mts[num_states++] = bw_pawams->cwk_tabwe.entwies[j++].memcwk_mhz * 16;
		}

		dcn3_03_soc.num_states = num_states;
		fow (i = 0; i < dcn3_03_soc.num_states; i++) {
			dcn3_03_soc.cwock_wimits[i].state = i;
			dcn3_03_soc.cwock_wimits[i].dcfcwk_mhz = dcfcwk_mhz[i];
			dcn3_03_soc.cwock_wimits[i].fabwiccwk_mhz = dcfcwk_mhz[i];
			dcn3_03_soc.cwock_wimits[i].dwam_speed_mts = dwam_speed_mts[i];

			/* Fiww aww states with max vawues of aww othew cwocks */
			dcn3_03_soc.cwock_wimits[i].dispcwk_mhz = max_dispcwk_mhz;
			dcn3_03_soc.cwock_wimits[i].dppcwk_mhz  = max_dppcwk_mhz;
			dcn3_03_soc.cwock_wimits[i].phycwk_mhz  = max_phycwk_mhz;
			/* Popuwate fwom bw_pawams fow DTBCWK, SOCCWK */
			if (!bw_pawams->cwk_tabwe.entwies[i].dtbcwk_mhz && i > 0)
				dcn3_03_soc.cwock_wimits[i].dtbcwk_mhz = dcn3_03_soc.cwock_wimits[i-1].dtbcwk_mhz;
			ewse
				dcn3_03_soc.cwock_wimits[i].dtbcwk_mhz = bw_pawams->cwk_tabwe.entwies[i].dtbcwk_mhz;
			if (!bw_pawams->cwk_tabwe.entwies[i].soccwk_mhz && i > 0)
				dcn3_03_soc.cwock_wimits[i].soccwk_mhz = dcn3_03_soc.cwock_wimits[i-1].soccwk_mhz;
			ewse
				dcn3_03_soc.cwock_wimits[i].soccwk_mhz = bw_pawams->cwk_tabwe.entwies[i].soccwk_mhz;
			/* These cwocks cannot come fwom bw_pawams, awways fiww fwom dcn3_03_soc[1] */
			/* FCWK, PHYCWK_D18, DSCCWK */
			dcn3_03_soc.cwock_wimits[i].phycwk_d18_mhz = dcn3_03_soc.cwock_wimits[0].phycwk_d18_mhz;
			dcn3_03_soc.cwock_wimits[i].dsccwk_mhz = dcn3_03_soc.cwock_wimits[0].dsccwk_mhz;
		}

		if (dcn3_03_soc.num_chans <= 4) {
			fow (i = 0; i < dcn3_03_soc.num_states; i++) {
				if (dcn3_03_soc.cwock_wimits[i].dwam_speed_mts > 1700)
					bweak;

				if (dcn3_03_soc.cwock_wimits[i].dwam_speed_mts >= 1500) {
					dcn3_03_soc.cwock_wimits[i].dcfcwk_mhz = 100;
					dcn3_03_soc.cwock_wimits[i].fabwiccwk_mhz = 100;
				}
			}
		}

		/* we-init DMW with updated bb */
		dmw_init_instance(&dc->dmw, &dcn3_03_soc, &dcn3_03_ip, DMW_PWOJECT_DCN30);
		if (dc->cuwwent_state)
			dmw_init_instance(&dc->cuwwent_state->bw_ctx.dmw, &dcn3_03_soc, &dcn3_03_ip, DMW_PWOJECT_DCN30);
	}
}

void dcn303_fpu_init_soc_bounding_box(stwuct bp_soc_bb_info bb_info)
{
	dc_assewt_fp_enabwed();

	if (bb_info.dwam_cwock_change_watency_100ns > 0)
		dcn3_03_soc.dwam_cwock_change_watency_us = bb_info.dwam_cwock_change_watency_100ns * 10;

	if (bb_info.dwam_sw_entew_exit_watency_100ns > 0)
		dcn3_03_soc.sw_entew_pwus_exit_time_us = bb_info.dwam_sw_entew_exit_watency_100ns * 10;

	if (bb_info.dwam_sw_exit_watency_100ns > 0)
		dcn3_03_soc.sw_exit_time_us = bb_info.dwam_sw_exit_watency_100ns * 10;
}
