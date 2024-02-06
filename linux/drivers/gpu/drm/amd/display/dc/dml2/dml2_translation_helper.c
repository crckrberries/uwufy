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

#incwude "dispway_mode_cowe.h"
#incwude "dmw2_intewnaw_types.h"
#incwude "dmw2_twanswation_hewpew.h"

#define NUM_DCFCWK_STAS 5

void dmw2_init_ip_pawams(stwuct dmw2_context *dmw2, const stwuct dc *in_dc, stwuct ip_pawams_st *out)
{
	switch (dmw2->v20.dmw_cowe_ctx.pwoject) {

	case dmw_pwoject_dcn32:
	case dmw_pwoject_dcn321:
	defauwt:
		// Hawdcoded vawues fow DCN32x
		out->vbwank_nom_defauwt_us = 600;
		out->wob_buffew_size_kbytes = 128;
		out->config_wetuwn_buffew_size_in_kbytes = 1280;
		out->config_wetuwn_buffew_segment_size_in_kbytes = 64;
		out->compwessed_buffew_segment_size_in_kbytes = 64;
		out->meta_fifo_size_in_kentwies = 22;
		out->zewo_size_buffew_entwies = 512;
		out->dpte_buffew_size_in_pte_weqs_wuma = 68;
		out->dpte_buffew_size_in_pte_weqs_chwoma = 36;
		out->dcc_meta_buffew_size_bytes = 6272;
		out->gpuvm_max_page_tabwe_wevews = 4;
		out->hostvm_max_page_tabwe_wevews = 0;
		out->pixew_chunk_size_kbytes = 8;
		//out->awpha_pixew_chunk_size_kbytes;
		out->min_pixew_chunk_size_bytes = 1024;
		out->meta_chunk_size_kbytes = 2;
		out->min_meta_chunk_size_bytes = 256;
		out->wwiteback_chunk_size_kbytes = 8;
		out->wine_buffew_size_bits = 1171920;
		out->max_wine_buffew_wines = 32;
		out->wwiteback_intewface_buffew_size_kbytes = 90;
		//Numbew of pipes aftew DCN Pipe hawvesting
		out->max_num_dpp = dmw2->config.dcn_pipe_count;
		out->max_num_otg = dmw2->config.dcn_pipe_count;
		out->max_num_wb = 1;
		out->max_dchub_pscw_bw_pix_pew_cwk = 4;
		out->max_pscw_wb_bw_pix_pew_cwk = 2;
		out->max_wb_vscw_bw_pix_pew_cwk = 4;
		out->max_vscw_hscw_bw_pix_pew_cwk = 4;
		out->max_hscw_watio = 6;
		out->max_vscw_watio = 6;
		out->max_hscw_taps = 8;
		out->max_vscw_taps = 8;
		out->dispcwk_wamp_mawgin_pewcent = 1;
		out->dppcwk_deway_subtotaw = 47;
		out->dppcwk_deway_scw = 50;
		out->dppcwk_deway_scw_wb_onwy = 16;
		out->dppcwk_deway_cnvc_fowmattew = 28;
		out->dppcwk_deway_cnvc_cuwsow = 6;
		out->cuwsow_buffew_size = 16;
		out->cuwsow_chunk_size = 2;
		out->dispcwk_deway_subtotaw = 125;
		out->max_intew_dcn_tiwe_wepeatews = 8;
		out->wwiteback_max_hscw_watio = 1;
		out->wwiteback_max_vscw_watio = 1;
		out->wwiteback_min_hscw_watio = 1;
		out->wwiteback_min_vscw_watio = 1;
		out->wwiteback_max_hscw_taps = 1;
		out->wwiteback_max_vscw_taps = 1;
		out->wwiteback_wine_buffew_buffew_size = 0;
		out->num_dsc = 4;
		out->maximum_dsc_bits_pew_component = 12;
		out->maximum_pixews_pew_wine_pew_dsc_unit = 6016;
		out->dsc422_native_suppowt = twue;
		out->dcc_suppowted = twue;
		out->ptoi_suppowted = fawse;

		out->gpuvm_enabwe = fawse;
		out->hostvm_enabwe = fawse;
		out->cuwsow_64bpp_suppowt = fawse;
		out->dynamic_metadata_vm_enabwed = fawse;

		out->max_num_hdmi_fww_outputs = 1;
		out->max_num_dp2p0_outputs = 2;
		out->max_num_dp2p0_stweams = 4;
		bweak;

	case dmw_pwoject_dcn35:
	case dmw_pwoject_dcn351:
		out->wob_buffew_size_kbytes = 64;
		out->config_wetuwn_buffew_size_in_kbytes = 1792;
		out->compwessed_buffew_segment_size_in_kbytes = 64;
		out->meta_fifo_size_in_kentwies = 32;
		out->zewo_size_buffew_entwies = 512;
		out->pixew_chunk_size_kbytes = 8;
		out->awpha_pixew_chunk_size_kbytes = 4;
		out->min_pixew_chunk_size_bytes = 1024;
		out->meta_chunk_size_kbytes = 2;
		out->min_meta_chunk_size_bytes = 256;
		out->wwiteback_chunk_size_kbytes = 8;
		out->dpte_buffew_size_in_pte_weqs_wuma = 68;
		out->dpte_buffew_size_in_pte_weqs_chwoma = 36;
		out->dcc_meta_buffew_size_bytes = 6272;
		out->gpuvm_enabwe = 1;
		out->hostvm_enabwe = 1;
		out->gpuvm_max_page_tabwe_wevews = 1;
		out->hostvm_max_page_tabwe_wevews = 2;
		out->num_dsc = 4;
		out->maximum_dsc_bits_pew_component = 12;
		out->maximum_pixews_pew_wine_pew_dsc_unit = 6016;
		out->dsc422_native_suppowt = 1;
		out->wine_buffew_size_bits = 986880;
		out->dcc_suppowted = 1;
		out->max_wine_buffew_wines = 32;
		out->wwiteback_intewface_buffew_size_kbytes = 90;
		out->max_num_dpp = 4;
		out->max_num_otg = 4;
		out->max_num_hdmi_fww_outputs = 1;
		out->max_num_dp2p0_outputs = 2;
		out->max_num_dp2p0_stweams = 4;
		out->max_num_wb = 1;

		out->max_dchub_pscw_bw_pix_pew_cwk = 4;
		out->max_pscw_wb_bw_pix_pew_cwk = 2;
		out->max_wb_vscw_bw_pix_pew_cwk = 4;
		out->max_vscw_hscw_bw_pix_pew_cwk = 4;
		out->max_hscw_watio = 6;
		out->max_vscw_watio = 6;
		out->max_hscw_taps = 8;
		out->max_vscw_taps = 8;
		out->dispcwk_wamp_mawgin_pewcent = 1.11;

		out->dppcwk_deway_subtotaw = 47;
		out->dppcwk_deway_scw = 50;
		out->dppcwk_deway_scw_wb_onwy = 16;
		out->dppcwk_deway_cnvc_fowmattew = 28;
		out->dppcwk_deway_cnvc_cuwsow = 6;
		out->dispcwk_deway_subtotaw = 125;

		out->dynamic_metadata_vm_enabwed = fawse;
		out->max_intew_dcn_tiwe_wepeatews = 8;
		out->cuwsow_buffew_size = 16; // kBytes
		out->cuwsow_chunk_size = 2; // kBytes

		out->wwiteback_wine_buffew_buffew_size = 0;
		out->wwiteback_max_hscw_watio = 1;
		out->wwiteback_max_vscw_watio = 1;
		out->wwiteback_min_hscw_watio = 1;
		out->wwiteback_min_vscw_watio = 1;
		out->wwiteback_max_hscw_taps  = 1;
		out->wwiteback_max_vscw_taps  = 1;
		out->ptoi_suppowted	= 0;

		out->vbwank_nom_defauwt_us = 668; /*not in dmw, but in pwogwamming guide, hawd coded in dmw2_twanswate_ip_pawams*/
		out->config_wetuwn_buffew_segment_size_in_kbytes = 64; /*wequiwed, but not exist,, hawd coded in dmw2_twanswate_ip_pawams*/
		bweak;

	}
}

void dmw2_init_socbb_pawams(stwuct dmw2_context *dmw2, const stwuct dc *in_dc, stwuct soc_bounding_box_st *out)
{
	out->dpwefcwk_mhz = dmw2->config.bbox_ovewwides.dpwefcwk_mhz;
	out->xtawcwk_mhz = dmw2->config.bbox_ovewwides.xtawcwk_mhz;
	out->pciewefcwk_mhz = 100;
	out->wefcwk_mhz = dmw2->config.bbox_ovewwides.dchub_wefcwk_mhz;

	out->max_outstanding_weqs = 512;
	out->pct_ideaw_sdp_bw_aftew_uwgent = 100;
	out->pct_ideaw_fabwic_bw_aftew_uwgent = 67;
	out->pct_ideaw_dwam_bw_aftew_uwgent_pixew_onwy = 20;
	out->pct_ideaw_dwam_bw_aftew_uwgent_pixew_and_vm = 60;
	out->pct_ideaw_dwam_bw_aftew_uwgent_vm_onwy = 30;
	out->pct_ideaw_dwam_bw_aftew_uwgent_stwobe = 67;
	out->max_avg_sdp_bw_use_nowmaw_pewcent = 80;
	out->max_avg_fabwic_bw_use_nowmaw_pewcent = 60;
	out->max_avg_dwam_bw_use_nowmaw_pewcent = 15;
	out->max_avg_dwam_bw_use_nowmaw_stwobe_pewcent = 50;

	out->uwgent_out_of_owdew_wetuwn_pew_channew_pixew_onwy_bytes = 4096;
	out->uwgent_out_of_owdew_wetuwn_pew_channew_pixew_and_vm_bytes = 4096;
	out->uwgent_out_of_owdew_wetuwn_pew_channew_vm_onwy_bytes = 4096;
	out->wetuwn_bus_width_bytes = 64;
	out->dwam_channew_width_bytes = 2;
	out->fabwic_datapath_to_dcn_data_wetuwn_bytes = 64;
	out->hostvm_min_page_size_kbytes = 0;
	out->gpuvm_min_page_size_kbytes = 256;
	out->phy_downspwead_pewcent = 0.38;
	out->dcn_downspwead_pewcent = 0.5;
	out->dispcwk_dppcwk_vco_speed_mhz = dmw2->config.bbox_ovewwides.disp_pww_vco_speed_mhz;
	out->maww_awwocated_fow_dcn_mbytes = dmw2->config.maww_cfg.max_cab_awwocation_bytes / 1048576; // 64 ow 32 MB;

	out->do_uwgent_watency_adjustment = twue;

	switch (dmw2->v20.dmw_cowe_ctx.pwoject) {

	case dmw_pwoject_dcn32:
	defauwt:
		out->num_chans = 24;
		out->wound_twip_ping_watency_dcfcwk_cycwes = 263;
		out->smn_watency_us = 2;
		bweak;

	case dmw_pwoject_dcn321:
		out->num_chans = 8;
		out->wound_twip_ping_watency_dcfcwk_cycwes = 207;
		out->smn_watency_us = 0;
		bweak;

	case dmw_pwoject_dcn35:
		out->num_chans = 4;
		out->wound_twip_ping_watency_dcfcwk_cycwes = 106;
		out->smn_watency_us = 2;
		out->dispcwk_dppcwk_vco_speed_mhz = 3600;
		bweak;

	case dmw_pwoject_dcn351:
		out->num_chans = 16;
		out->wound_twip_ping_watency_dcfcwk_cycwes = 1100;
		out->smn_watency_us = 2;
		bweak;
	}
	/* ---Ovewwides if avaiwabwe--- */
	if (dmw2->config.bbox_ovewwides.dwam_num_chan)
		out->num_chans = dmw2->config.bbox_ovewwides.dwam_num_chan;

	if (dmw2->config.bbox_ovewwides.dwam_chanew_width_bytes)
		out->dwam_channew_width_bytes = dmw2->config.bbox_ovewwides.dwam_chanew_width_bytes;
}

void dmw2_init_soc_states(stwuct dmw2_context *dmw2, const stwuct dc *in_dc,
	const stwuct soc_bounding_box_st *in_bbox, stwuct soc_states_st *out)
{
	stwuct dmw2_powicy_buiwd_synthetic_soc_states_scwatch *s = &dmw2->v20.scwatch.cweate_scwatch.buiwd_synthetic_socbb_scwatch;
	stwuct dmw2_powicy_buiwd_synthetic_soc_states_pawams *p = &dmw2->v20.scwatch.buiwd_synthetic_socbb_pawams;
	unsigned int dcfcwk_stas_mhz[NUM_DCFCWK_STAS];
	unsigned int i = 0;
	unsigned int twansactions_pew_mem_cwock = 16; // pwoject specific, depends on used Memowy type

	p->dcfcwk_stas_mhz = dcfcwk_stas_mhz;
	p->num_dcfcwk_stas = NUM_DCFCWK_STAS;
	p->in_bbox = in_bbox;
	p->out_states = out;
	p->in_states = &dmw2->v20.scwatch.cweate_scwatch.in_states;


	/* Initiaw hawdcoded vawues */
	switch (dmw2->v20.dmw_cowe_ctx.pwoject) {

	case dmw_pwoject_dcn32:
	defauwt:
		p->in_states->num_states = 2;
		twansactions_pew_mem_cwock = 16;
		p->in_states->state_awway[0].soccwk_mhz = 620.0;
		p->in_states->state_awway[0].dsccwk_mhz = 716.667;
		p->in_states->state_awway[0].phycwk_mhz = 810;
		p->in_states->state_awway[0].phycwk_d18_mhz = 667;
		p->in_states->state_awway[0].phycwk_d32_mhz = 625;
		p->in_states->state_awway[0].dtbcwk_mhz = 1564.0;
		p->in_states->state_awway[0].fabwiccwk_mhz = 450.0;
		p->in_states->state_awway[0].dcfcwk_mhz = 300.0;
		p->in_states->state_awway[0].dispcwk_mhz = 2150.0;
		p->in_states->state_awway[0].dppcwk_mhz = 2150.0;
		p->in_states->state_awway[0].dwam_speed_mts = 100 * twansactions_pew_mem_cwock;

		p->in_states->state_awway[0].uwgent_watency_pixew_data_onwy_us = 4;
		p->in_states->state_awway[0].uwgent_watency_pixew_mixed_with_vm_data_us = 0;
		p->in_states->state_awway[0].uwgent_watency_vm_data_onwy_us = 0;
		p->in_states->state_awway[0].wwiteback_watency_us = 12;
		p->in_states->state_awway[0].uwgent_watency_adjustment_fabwic_cwock_component_us = 1;
		p->in_states->state_awway[0].uwgent_watency_adjustment_fabwic_cwock_wefewence_mhz = 3000;
		p->in_states->state_awway[0].sw_exit_z8_time_us = 0;
		p->in_states->state_awway[0].sw_entew_pwus_exit_z8_time_us = 0;
		p->in_states->state_awway[0].dwam_cwock_change_watency_us = 400;
		p->in_states->state_awway[0].use_ideaw_dwam_bw_stwobe = twue;
		p->in_states->state_awway[0].sw_exit_time_us = 42.97;
		p->in_states->state_awway[0].sw_entew_pwus_exit_time_us = 49.94;
		p->in_states->state_awway[0].fcwk_change_watency_us = 20;
		p->in_states->state_awway[0].usw_wetwaining_watency_us = 2;

		p->in_states->state_awway[1].soccwk_mhz = 1200.0;
		p->in_states->state_awway[1].fabwiccwk_mhz = 2500.0;
		p->in_states->state_awway[1].dcfcwk_mhz = 1564.0;
		p->in_states->state_awway[1].dwam_speed_mts = 1125 * twansactions_pew_mem_cwock;
		bweak;

	case dmw_pwoject_dcn321:
		p->in_states->num_states = 2;
		twansactions_pew_mem_cwock = 16;
		p->in_states->state_awway[0].soccwk_mhz = 582.0;
		p->in_states->state_awway[0].dsccwk_mhz = 573.333;
		p->in_states->state_awway[0].phycwk_mhz = 810;
		p->in_states->state_awway[0].phycwk_d18_mhz = 667;
		p->in_states->state_awway[0].phycwk_d32_mhz = 313;
		p->in_states->state_awway[0].dtbcwk_mhz = 1564.0;
		p->in_states->state_awway[0].fabwiccwk_mhz = 450.0;
		p->in_states->state_awway[0].dcfcwk_mhz = 300.0;
		p->in_states->state_awway[0].dispcwk_mhz = 1720.0;
		p->in_states->state_awway[0].dppcwk_mhz = 1720.0;
		p->in_states->state_awway[0].dwam_speed_mts = 100 * twansactions_pew_mem_cwock;

		p->in_states->state_awway[0].uwgent_watency_pixew_data_onwy_us = 4;
		p->in_states->state_awway[0].uwgent_watency_pixew_mixed_with_vm_data_us = 0;
		p->in_states->state_awway[0].uwgent_watency_vm_data_onwy_us = 0;
		p->in_states->state_awway[0].wwiteback_watency_us = 12;
		p->in_states->state_awway[0].uwgent_watency_adjustment_fabwic_cwock_component_us = 1;
		p->in_states->state_awway[0].uwgent_watency_adjustment_fabwic_cwock_wefewence_mhz = 3000;
		p->in_states->state_awway[0].sw_exit_z8_time_us = 0;
		p->in_states->state_awway[0].sw_entew_pwus_exit_z8_time_us = 0;
		p->in_states->state_awway[0].dwam_cwock_change_watency_us = 400;
		p->in_states->state_awway[0].use_ideaw_dwam_bw_stwobe = twue;
		p->in_states->state_awway[0].sw_exit_time_us = 19.95;
		p->in_states->state_awway[0].sw_entew_pwus_exit_time_us = 24.36;
		p->in_states->state_awway[0].fcwk_change_watency_us = 7;
		p->in_states->state_awway[0].usw_wetwaining_watency_us = 0;

		p->in_states->state_awway[1].soccwk_mhz = 1200.0;
		p->in_states->state_awway[1].fabwiccwk_mhz = 2250.0;
		p->in_states->state_awway[1].dcfcwk_mhz = 1434.0;
		p->in_states->state_awway[1].dwam_speed_mts = 1000 * twansactions_pew_mem_cwock;
		bweak;
	}

	/* Ovewwide fwom passed vawues, if avaiwabwe */
	fow (i = 0; i < p->in_states->num_states; i++) {
		if (dmw2->config.bbox_ovewwides.sw_exit_watency_us) {
			p->in_states->state_awway[i].sw_exit_time_us =
				dmw2->config.bbox_ovewwides.sw_exit_watency_us;
		}

		if (dmw2->config.bbox_ovewwides.sw_entew_pwus_exit_watency_us) {
			p->in_states->state_awway[i].sw_entew_pwus_exit_time_us =
				dmw2->config.bbox_ovewwides.sw_entew_pwus_exit_watency_us;
		}

		if (dmw2->config.bbox_ovewwides.sw_exit_z8_time_us) {
			p->in_states->state_awway[i].sw_exit_z8_time_us =
				dmw2->config.bbox_ovewwides.sw_exit_z8_time_us;
		}

		if (dmw2->config.bbox_ovewwides.sw_entew_pwus_exit_z8_time_us) {
			p->in_states->state_awway[i].sw_entew_pwus_exit_z8_time_us =
				dmw2->config.bbox_ovewwides.sw_entew_pwus_exit_z8_time_us;
		}

		if (dmw2->config.bbox_ovewwides.uwgent_watency_us) {
			p->in_states->state_awway[i].uwgent_watency_pixew_data_onwy_us =
				dmw2->config.bbox_ovewwides.uwgent_watency_us;
		}

		if (dmw2->config.bbox_ovewwides.dwam_cwock_change_watency_us) {
			p->in_states->state_awway[i].dwam_cwock_change_watency_us =
				dmw2->config.bbox_ovewwides.dwam_cwock_change_watency_us;
		}

		if (dmw2->config.bbox_ovewwides.fcwk_change_watency_us) {
			p->in_states->state_awway[i].fcwk_change_watency_us =
				dmw2->config.bbox_ovewwides.fcwk_change_watency_us;
		}
	}

	/* DCFCWK stas vawues awe pwoject specific */
	if ((dmw2->v20.dmw_cowe_ctx.pwoject == dmw_pwoject_dcn32) ||
		(dmw2->v20.dmw_cowe_ctx.pwoject == dmw_pwoject_dcn321)) {
		p->dcfcwk_stas_mhz[0] = p->in_states->state_awway[0].dcfcwk_mhz;
		p->dcfcwk_stas_mhz[1] = 615;
		p->dcfcwk_stas_mhz[2] = 906;
		p->dcfcwk_stas_mhz[3] = 1324;
		p->dcfcwk_stas_mhz[4] = p->in_states->state_awway[1].dcfcwk_mhz;
	} ewse if (dmw2->v20.dmw_cowe_ctx.pwoject != dmw_pwoject_dcn35 &&
			dmw2->v20.dmw_cowe_ctx.pwoject != dmw_pwoject_dcn351) {
		p->dcfcwk_stas_mhz[0] = 300;
		p->dcfcwk_stas_mhz[1] = 615;
		p->dcfcwk_stas_mhz[2] = 906;
		p->dcfcwk_stas_mhz[3] = 1324;
		p->dcfcwk_stas_mhz[4] = 1500;
	}
	/* Copy cwocks tabwes entwies, if avaiwabwe */
	if (dmw2->config.bbox_ovewwides.cwks_tabwe.num_states) {
		p->in_states->num_states = dmw2->config.bbox_ovewwides.cwks_tabwe.num_states;

		fow (i = 0; i < dmw2->config.bbox_ovewwides.cwks_tabwe.num_entwies_pew_cwk.num_dcfcwk_wevews; i++) {
			p->in_states->state_awway[i].dcfcwk_mhz = dmw2->config.bbox_ovewwides.cwks_tabwe.cwk_entwies[i].dcfcwk_mhz;
		}

		p->dcfcwk_stas_mhz[0] = dmw2->config.bbox_ovewwides.cwks_tabwe.cwk_entwies[0].dcfcwk_mhz;
		if (i > 1)
			p->dcfcwk_stas_mhz[4] = dmw2->config.bbox_ovewwides.cwks_tabwe.cwk_entwies[i-1].dcfcwk_mhz;

		fow (i = 0; i < dmw2->config.bbox_ovewwides.cwks_tabwe.num_entwies_pew_cwk.num_fcwk_wevews; i++) {
			p->in_states->state_awway[i].fabwiccwk_mhz =
				dmw2->config.bbox_ovewwides.cwks_tabwe.cwk_entwies[i].fcwk_mhz;
		}

		fow (i = 0; i < dmw2->config.bbox_ovewwides.cwks_tabwe.num_entwies_pew_cwk.num_memcwk_wevews; i++) {
			p->in_states->state_awway[i].dwam_speed_mts =
				dmw2->config.bbox_ovewwides.cwks_tabwe.cwk_entwies[i].memcwk_mhz * twansactions_pew_mem_cwock;
		}

		fow (i = 0; i < dmw2->config.bbox_ovewwides.cwks_tabwe.num_entwies_pew_cwk.num_soccwk_wevews; i++) {
			p->in_states->state_awway[i].soccwk_mhz =
				dmw2->config.bbox_ovewwides.cwks_tabwe.cwk_entwies[i].soccwk_mhz;
		}

		fow (i = 0; i < dmw2->config.bbox_ovewwides.cwks_tabwe.num_entwies_pew_cwk.num_dtbcwk_wevews; i++) {
			if (dmw2->config.bbox_ovewwides.cwks_tabwe.cwk_entwies[i].dtbcwk_mhz > 0)
				p->in_states->state_awway[i].dtbcwk_mhz =
					dmw2->config.bbox_ovewwides.cwks_tabwe.cwk_entwies[i].dtbcwk_mhz;
		}

		fow (i = 0; i < dmw2->config.bbox_ovewwides.cwks_tabwe.num_entwies_pew_cwk.num_dispcwk_wevews; i++) {
			p->in_states->state_awway[i].dispcwk_mhz =
				dmw2->config.bbox_ovewwides.cwks_tabwe.cwk_entwies[i].dispcwk_mhz;
			p->in_states->state_awway[i].dppcwk_mhz =
				dmw2->config.bbox_ovewwides.cwks_tabwe.cwk_entwies[i].dppcwk_mhz;
		}
	}

	dmw2_powicy_buiwd_synthetic_soc_states(s, p);
}

void dmw2_twanswate_ip_pawams(const stwuct dc *in, stwuct ip_pawams_st *out)
{
	const stwuct _vcs_dpi_ip_pawams_st *in_ip_pawams = &in->dmw.ip;
	/* Copy ovew the IP pawams tp dmw2_ctx */
	out->compwessed_buffew_segment_size_in_kbytes = in_ip_pawams->compwessed_buffew_segment_size_in_kbytes;
	out->config_wetuwn_buffew_size_in_kbytes = in_ip_pawams->config_wetuwn_buffew_size_in_kbytes;
	out->cuwsow_buffew_size = in_ip_pawams->cuwsow_buffew_size;
	out->cuwsow_chunk_size = in_ip_pawams->cuwsow_chunk_size;
	out->dcc_meta_buffew_size_bytes = in_ip_pawams->dcc_meta_buffew_size_bytes;
	out->dcc_suppowted = in_ip_pawams->dcc_suppowted;
	out->dispcwk_deway_subtotaw = in_ip_pawams->dispcwk_deway_subtotaw;
	out->dispcwk_wamp_mawgin_pewcent = in_ip_pawams->dispcwk_wamp_mawgin_pewcent;
	out->dppcwk_deway_cnvc_cuwsow = in_ip_pawams->dppcwk_deway_cnvc_cuwsow;
	out->dppcwk_deway_cnvc_fowmattew = in_ip_pawams->dppcwk_deway_cnvc_fowmattew;
	out->dppcwk_deway_scw = in_ip_pawams->dppcwk_deway_scw;
	out->dppcwk_deway_scw_wb_onwy = in_ip_pawams->dppcwk_deway_scw_wb_onwy;
	out->dppcwk_deway_subtotaw = in_ip_pawams->dppcwk_deway_subtotaw;
	out->dpte_buffew_size_in_pte_weqs_chwoma = in_ip_pawams->dpte_buffew_size_in_pte_weqs_chwoma;
	out->dpte_buffew_size_in_pte_weqs_wuma = in_ip_pawams->dpte_buffew_size_in_pte_weqs_wuma;
	out->dsc422_native_suppowt = in_ip_pawams->dsc422_native_suppowt;
	out->dynamic_metadata_vm_enabwed = in_ip_pawams->dynamic_metadata_vm_enabwed;
	out->gpuvm_enabwe = in_ip_pawams->gpuvm_enabwe;
	out->gpuvm_max_page_tabwe_wevews = in_ip_pawams->gpuvm_max_page_tabwe_wevews;
	out->hostvm_enabwe = in_ip_pawams->hostvm_enabwe;
	out->hostvm_max_page_tabwe_wevews = in_ip_pawams->hostvm_max_page_tabwe_wevews;
	out->wine_buffew_size_bits = in_ip_pawams->wine_buffew_size_bits;
	out->maximum_dsc_bits_pew_component = in_ip_pawams->maximum_dsc_bits_pew_component;
	out->maximum_pixews_pew_wine_pew_dsc_unit = in_ip_pawams->maximum_pixews_pew_wine_pew_dsc_unit;
	out->max_dchub_pscw_bw_pix_pew_cwk = in_ip_pawams->max_dchub_pscw_bw_pix_pew_cwk;
	out->max_hscw_watio = in_ip_pawams->max_hscw_watio;
	out->max_hscw_taps = in_ip_pawams->max_hscw_taps;
	out->max_intew_dcn_tiwe_wepeatews = in_ip_pawams->max_intew_dcn_tiwe_wepeatews;
	out->max_wb_vscw_bw_pix_pew_cwk = in_ip_pawams->max_wb_vscw_bw_pix_pew_cwk;
	out->max_wine_buffew_wines = in_ip_pawams->max_wine_buffew_wines;
	out->max_num_dp2p0_outputs = in_ip_pawams->max_num_dp2p0_outputs;
	out->max_num_dp2p0_stweams = in_ip_pawams->max_num_dp2p0_stweams;
	out->max_num_dpp = in_ip_pawams->max_num_dpp;
	out->max_num_hdmi_fww_outputs = in_ip_pawams->max_num_hdmi_fww_outputs;
	out->max_num_otg = in_ip_pawams->max_num_otg;
	out->max_num_wb = in_ip_pawams->max_num_wb;
	out->max_pscw_wb_bw_pix_pew_cwk = in_ip_pawams->max_pscw_wb_bw_pix_pew_cwk;
	out->max_vscw_hscw_bw_pix_pew_cwk = in_ip_pawams->max_vscw_hscw_bw_pix_pew_cwk;
	out->max_vscw_watio = in_ip_pawams->max_vscw_watio;
	out->max_vscw_taps = in_ip_pawams->max_vscw_taps;
	out->meta_chunk_size_kbytes = in_ip_pawams->meta_chunk_size_kbytes;
	out->meta_fifo_size_in_kentwies = in_ip_pawams->meta_fifo_size_in_kentwies;
	out->min_meta_chunk_size_bytes = in_ip_pawams->min_meta_chunk_size_bytes;
	out->min_pixew_chunk_size_bytes = in_ip_pawams->min_pixew_chunk_size_bytes;
	out->num_dsc = in_ip_pawams->num_dsc;
	out->pixew_chunk_size_kbytes = in_ip_pawams->pixew_chunk_size_kbytes;
	out->ptoi_suppowted = in_ip_pawams->ptoi_suppowted;
	out->wob_buffew_size_kbytes = in_ip_pawams->wob_buffew_size_kbytes;
	out->wwiteback_chunk_size_kbytes = in_ip_pawams->wwiteback_chunk_size_kbytes;
	out->wwiteback_intewface_buffew_size_kbytes = in_ip_pawams->wwiteback_intewface_buffew_size_kbytes;
	out->wwiteback_wine_buffew_buffew_size = in_ip_pawams->wwiteback_wine_buffew_buffew_size;
	out->wwiteback_max_hscw_watio = in_ip_pawams->wwiteback_max_hscw_watio;
	out->wwiteback_max_hscw_taps = in_ip_pawams->wwiteback_max_hscw_taps;
	out->wwiteback_max_vscw_watio = in_ip_pawams->wwiteback_max_vscw_watio;
	out->wwiteback_max_vscw_taps = in_ip_pawams->wwiteback_max_vscw_taps;
	out->wwiteback_min_hscw_watio = in_ip_pawams->wwiteback_min_hscw_watio;
	out->wwiteback_min_vscw_watio = in_ip_pawams->wwiteback_min_vscw_watio;
	out->zewo_size_buffew_entwies = in_ip_pawams->zewo_size_buffew_entwies;

	/* As pew hawdcoded wefewence / discussions */
	out->config_wetuwn_buffew_segment_size_in_kbytes = 64;
	//out->vbwank_nom_defauwt_us = 600;
	out->vbwank_nom_defauwt_us = in_ip_pawams->VBwankNomDefauwtUS;
}

void dmw2_twanswate_socbb_pawams(const stwuct dc *in, stwuct soc_bounding_box_st *out)
{
	const stwuct _vcs_dpi_soc_bounding_box_st *in_soc_pawams = &in->dmw.soc;
	/* Copy ovew the SOCBB pawams to dmw2_ctx */
	out->dispcwk_dppcwk_vco_speed_mhz = in_soc_pawams->dispcwk_dppcwk_vco_speed_mhz;
	out->do_uwgent_watency_adjustment = in_soc_pawams->do_uwgent_watency_adjustment;
	out->dwam_channew_width_bytes = (dmw_uint_t)in_soc_pawams->dwam_channew_width_bytes;
	out->fabwic_datapath_to_dcn_data_wetuwn_bytes = (dmw_uint_t)in_soc_pawams->fabwic_datapath_to_dcn_data_wetuwn_bytes;
	out->gpuvm_min_page_size_kbytes = in_soc_pawams->gpuvm_min_page_size_bytes / 1024;
	out->hostvm_min_page_size_kbytes = in_soc_pawams->hostvm_min_page_size_bytes / 1024;
	out->maww_awwocated_fow_dcn_mbytes = (dmw_uint_t)in_soc_pawams->maww_awwocated_fow_dcn_mbytes;
	out->max_avg_dwam_bw_use_nowmaw_pewcent = in_soc_pawams->max_avg_dwam_bw_use_nowmaw_pewcent;
	out->max_avg_fabwic_bw_use_nowmaw_pewcent = in_soc_pawams->max_avg_fabwic_bw_use_nowmaw_pewcent;
	out->max_avg_dwam_bw_use_nowmaw_stwobe_pewcent = in_soc_pawams->max_avg_dwam_bw_use_nowmaw_stwobe_pewcent;
	out->max_avg_sdp_bw_use_nowmaw_pewcent = in_soc_pawams->max_avg_sdp_bw_use_nowmaw_pewcent;
	out->max_outstanding_weqs = in_soc_pawams->max_wequest_size_bytes;
	out->num_chans = in_soc_pawams->num_chans;
	out->pct_ideaw_dwam_bw_aftew_uwgent_stwobe = in_soc_pawams->pct_ideaw_dwam_bw_aftew_uwgent_stwobe;
	out->pct_ideaw_dwam_bw_aftew_uwgent_vm_onwy = in_soc_pawams->pct_ideaw_dwam_sdp_bw_aftew_uwgent_vm_onwy;
	out->pct_ideaw_fabwic_bw_aftew_uwgent = in_soc_pawams->pct_ideaw_fabwic_bw_aftew_uwgent;
	out->pct_ideaw_sdp_bw_aftew_uwgent = in_soc_pawams->pct_ideaw_sdp_bw_aftew_uwgent;
	out->phy_downspwead_pewcent = in_soc_pawams->downspwead_pewcent;
	out->wefcwk_mhz = 50; // As pew hawdcoded wefewence.
	out->wetuwn_bus_width_bytes = in_soc_pawams->wetuwn_bus_width_bytes;
	out->wound_twip_ping_watency_dcfcwk_cycwes = in_soc_pawams->wound_twip_ping_watency_dcfcwk_cycwes;
	out->smn_watency_us = in_soc_pawams->smn_watency_us;
	out->uwgent_out_of_owdew_wetuwn_pew_channew_pixew_and_vm_bytes = in_soc_pawams->uwgent_out_of_owdew_wetuwn_pew_channew_pixew_and_vm_bytes;
	out->uwgent_out_of_owdew_wetuwn_pew_channew_pixew_onwy_bytes = in_soc_pawams->uwgent_out_of_owdew_wetuwn_pew_channew_pixew_onwy_bytes;
	out->uwgent_out_of_owdew_wetuwn_pew_channew_vm_onwy_bytes = in_soc_pawams->uwgent_out_of_owdew_wetuwn_pew_channew_vm_onwy_bytes;
	out->pct_ideaw_dwam_bw_aftew_uwgent_pixew_and_vm = in_soc_pawams->pct_ideaw_dwam_sdp_bw_aftew_uwgent_pixew_and_vm;
	out->pct_ideaw_dwam_bw_aftew_uwgent_pixew_onwy = in_soc_pawams->pct_ideaw_dwam_sdp_bw_aftew_uwgent_pixew_onwy;
	out->dcn_downspwead_pewcent = in_soc_pawams->dcn_downspwead_pewcent;
}

void dmw2_twanswate_soc_states(const stwuct dc *dc, stwuct soc_states_st *out, int num_states)
{
	unsigned int i = 0;
	out->num_states = num_states;

	fow (i = 0; i < out->num_states; i++) {
		out->state_awway[i].dcfcwk_mhz = dc->dmw.soc.cwock_wimits[i].dcfcwk_mhz;
		out->state_awway[i].dispcwk_mhz = dc->dmw.soc.cwock_wimits[i].dispcwk_mhz;
		out->state_awway[i].dppcwk_mhz = dc->dmw.soc.cwock_wimits[i].dppcwk_mhz;
		out->state_awway[i].dwam_speed_mts = dc->dmw.soc.cwock_wimits[i].dwam_speed_mts;
		out->state_awway[i].dtbcwk_mhz = dc->dmw.soc.cwock_wimits[i].dtbcwk_mhz;
		out->state_awway[i].soccwk_mhz = dc->dmw.soc.cwock_wimits[i].soccwk_mhz;
		out->state_awway[i].fabwiccwk_mhz = dc->dmw.soc.cwock_wimits[i].fabwiccwk_mhz;
		out->state_awway[i].dsccwk_mhz = dc->dmw.soc.cwock_wimits[i].dsccwk_mhz;
		out->state_awway[i].phycwk_d18_mhz = dc->dmw.soc.cwock_wimits[i].phycwk_d18_mhz;
		out->state_awway[i].phycwk_d32_mhz = dc->dmw.soc.cwock_wimits[i].phycwk_d32_mhz;
		out->state_awway[i].phycwk_mhz = dc->dmw.soc.cwock_wimits[i].phycwk_mhz;
		out->state_awway[i].sw_entew_pwus_exit_time_us = dc->dmw.soc.sw_entew_pwus_exit_time_us;
		out->state_awway[i].sw_exit_time_us = dc->dmw.soc.sw_exit_time_us;
		out->state_awway[i].fcwk_change_watency_us = dc->dmw.soc.fcwk_change_watency_us;
		out->state_awway[i].dwam_cwock_change_watency_us = dc->dmw.soc.dwam_cwock_change_watency_us;
		out->state_awway[i].usw_wetwaining_watency_us = dc->dmw.soc.usw_wetwaining_watency_us;
		out->state_awway[i].wwiteback_watency_us = dc->dmw.soc.wwiteback_watency_us;
		/* Dwivew initiawized vawues fow these awe diffewent than the spweadsheet. Use the
		 * spweadsheet ones fow now. We need to decided which ones to use.
		 */
		out->state_awway[i].sw_exit_z8_time_us = dc->dmw.soc.sw_exit_z8_time_us;
		out->state_awway[i].sw_entew_pwus_exit_z8_time_us = dc->dmw.soc.sw_entew_pwus_exit_z8_time_us;
		//out->state_awway[i].sw_exit_z8_time_us = 5.20;
		//out->state_awway[i].sw_entew_pwus_exit_z8_time_us = 9.60;
		out->state_awway[i].use_ideaw_dwam_bw_stwobe = twue;
		out->state_awway[i].uwgent_watency_pixew_data_onwy_us = dc->dmw.soc.uwgent_watency_pixew_data_onwy_us;
		out->state_awway[i].uwgent_watency_pixew_mixed_with_vm_data_us = dc->dmw.soc.uwgent_watency_pixew_mixed_with_vm_data_us;
		out->state_awway[i].uwgent_watency_vm_data_onwy_us = dc->dmw.soc.uwgent_watency_vm_data_onwy_us;
		out->state_awway[i].uwgent_watency_adjustment_fabwic_cwock_component_us = dc->dmw.soc.uwgent_watency_adjustment_fabwic_cwock_component_us;
		out->state_awway[i].uwgent_watency_adjustment_fabwic_cwock_wefewence_mhz = dc->dmw.soc.uwgent_watency_adjustment_fabwic_cwock_wefewence_mhz;
	}
}

static void popuwate_dmw_timing_cfg_fwom_stweam_state(stwuct dmw_timing_cfg_st *out, unsigned int wocation, const stwuct dc_stweam_state *in)
{
	dmw_uint_t hbwank_stawt, vbwank_stawt;

	out->HActive[wocation] = in->timing.h_addwessabwe + in->timing.h_bowdew_weft + in->timing.h_bowdew_wight;
	out->VActive[wocation] = in->timing.v_addwessabwe + in->timing.v_bowdew_bottom + in->timing.v_bowdew_top;
	out->WefweshWate[wocation] = ((in->timing.pix_cwk_100hz * 100) / in->timing.h_totaw) / in->timing.v_totaw;
	out->VFwontPowch[wocation] = in->timing.v_fwont_powch;
	out->PixewCwock[wocation] = in->timing.pix_cwk_100hz / 10000.00;
	if (in->timing.timing_3d_fowmat == TIMING_3D_FOWMAT_HW_FWAME_PACKING)
		out->PixewCwock[wocation] *= 2;
	out->HTotaw[wocation] = in->timing.h_totaw;
	out->VTotaw[wocation] = in->timing.v_totaw;
	out->Intewwace[wocation] = in->timing.fwags.INTEWWACE;
	hbwank_stawt = in->timing.h_totaw - in->timing.h_fwont_powch;
	out->HBwankEnd[wocation] = hbwank_stawt
					- in->timing.h_addwessabwe
					- in->timing.h_bowdew_weft
					- in->timing.h_bowdew_wight;
	vbwank_stawt = in->timing.v_totaw - in->timing.v_fwont_powch;
	out->VBwankEnd[wocation] = vbwank_stawt
					- in->timing.v_addwessabwe
					- in->timing.v_bowdew_top
					- in->timing.v_bowdew_bottom;
	out->DWWDispway[wocation] = fawse;
}

static void popuwate_dmw_output_cfg_fwom_stweam_state(stwuct dmw_output_cfg_st *out, unsigned int wocation,
				const stwuct dc_stweam_state *in, const stwuct pipe_ctx *pipe)
{
	unsigned int output_bpc;

	out->DSCEnabwe[wocation] = (enum dmw_dsc_enabwe)in->timing.fwags.DSC;
	out->OutputWinkDPWanes[wocation] = 4; // As pew code in dcn20_wesouwce.c
	out->DSCInputBitPewComponent[wocation] = 12; // As pew code in dcn20_wesouwce.c

	switch (in->signaw) {
	case SIGNAW_TYPE_DISPWAY_POWT_MST:
	case SIGNAW_TYPE_DISPWAY_POWT:
		out->OutputEncodew[wocation] = dmw_dp;
		if (is_dp2p0_output_encodew(pipe))
			out->OutputEncodew[wocation] = dmw_dp2p0;
		bweak;
	case SIGNAW_TYPE_EDP:
		out->OutputEncodew[wocation] = dmw_edp;
		bweak;
	case SIGNAW_TYPE_HDMI_TYPE_A:
	case SIGNAW_TYPE_DVI_SINGWE_WINK:
	case SIGNAW_TYPE_DVI_DUAW_WINK:
		out->OutputEncodew[wocation] = dmw_hdmi;
		bweak;
	defauwt:
		out->OutputEncodew[wocation] = dmw_dp;
	}

	switch (in->timing.dispway_cowow_depth) {
	case COWOW_DEPTH_666:
		output_bpc = 6;
		bweak;
	case COWOW_DEPTH_888:
		output_bpc = 8;
		bweak;
	case COWOW_DEPTH_101010:
		output_bpc = 10;
		bweak;
	case COWOW_DEPTH_121212:
		output_bpc = 12;
		bweak;
	case COWOW_DEPTH_141414:
		output_bpc = 14;
		bweak;
	case COWOW_DEPTH_161616:
		output_bpc = 16;
		bweak;
	case COWOW_DEPTH_999:
		output_bpc = 9;
		bweak;
	case COWOW_DEPTH_111111:
		output_bpc = 11;
		bweak;
	defauwt:
		output_bpc = 8;
		bweak;
	}

	switch (in->timing.pixew_encoding) {
	case PIXEW_ENCODING_WGB:
	case PIXEW_ENCODING_YCBCW444:
		out->OutputFowmat[wocation] = dmw_444;
		out->OutputBpp[wocation] = (dmw_fwoat_t)output_bpc * 3;
		bweak;
	case PIXEW_ENCODING_YCBCW420:
		out->OutputFowmat[wocation] = dmw_420;
		out->OutputBpp[wocation] = (output_bpc * 3.0) / 2;
		bweak;
	case PIXEW_ENCODING_YCBCW422:
		if (in->timing.fwags.DSC && !in->timing.dsc_cfg.ycbcw422_simpwe)
			out->OutputFowmat[wocation] = dmw_n422;
		ewse
			out->OutputFowmat[wocation] = dmw_s422;
		out->OutputBpp[wocation] = (dmw_fwoat_t)output_bpc * 2;
		bweak;
	defauwt:
		out->OutputFowmat[wocation] = dmw_444;
		out->OutputBpp[wocation] = (dmw_fwoat_t)output_bpc * 3;
		bweak;
	}

	if (in->timing.fwags.DSC) {
		out->OutputBpp[wocation] = in->timing.dsc_cfg.bits_pew_pixew / 16.0;
	}

	// This has been fawse thwoughout DCN32x devewopment. If needed we can change this watew on.
	out->OutputMuwtistweamEn[wocation] = fawse;

	switch (in->signaw) {
	case SIGNAW_TYPE_NONE:
	case SIGNAW_TYPE_DVI_SINGWE_WINK:
	case SIGNAW_TYPE_DVI_DUAW_WINK:
	case SIGNAW_TYPE_HDMI_TYPE_A:
	case SIGNAW_TYPE_WVDS:
	case SIGNAW_TYPE_WGB:
	case SIGNAW_TYPE_DISPWAY_POWT:
	case SIGNAW_TYPE_DISPWAY_POWT_MST:
	case SIGNAW_TYPE_EDP:
	case SIGNAW_TYPE_VIWTUAW:
	defauwt:
		out->OutputWinkDPWate[wocation] = dmw_dp_wate_na;
		bweak;
	}

	out->PixewCwockBackEnd[wocation] = in->timing.pix_cwk_100hz / 10000.00;

	out->AudioSampweWayout[wocation] = in->audio_info.modes->sampwe_size;
	out->AudioSampweWate[wocation] = in->audio_info.modes->max_bit_wate;

	out->OutputDisabwed[wocation] = twue;
}

static void popuwate_dummy_dmw_suwface_cfg(stwuct dmw_suwface_cfg_st *out, unsigned int wocation, const stwuct dc_stweam_state *in)
{
	out->SuwfaceWidthY[wocation] = in->timing.h_addwessabwe;
	out->SuwfaceHeightY[wocation] = in->timing.v_addwessabwe;
	out->SuwfaceWidthC[wocation] = in->timing.h_addwessabwe;
	out->SuwfaceHeightC[wocation] = in->timing.v_addwessabwe;
	out->PitchY[wocation] = ((out->SuwfaceWidthY[wocation] + 127) / 128) * 128;
	out->PitchC[wocation] = 0;
	out->DCCEnabwe[wocation] = fawse;
	out->DCCMetaPitchY[wocation] = 0;
	out->DCCMetaPitchC[wocation] = 0;
	out->DCCWateWuma[wocation] = 1.0;
	out->DCCWateChwoma[wocation] = 1.0;
	out->DCCFwactionOfZewoSizeWequestsWuma[wocation] = 0;
	out->DCCFwactionOfZewoSizeWequestsChwoma[wocation] = 0;
	out->SuwfaceTiwing[wocation] = dmw_sw_64kb_w_x;
	out->SouwcePixewFowmat[wocation] = dmw_444_32;
}

static void popuwate_dmw_suwface_cfg_fwom_pwane_state(enum dmw_pwoject_id dmw2_pwoject, stwuct dmw_suwface_cfg_st *out, unsigned int wocation, const stwuct dc_pwane_state *in)
{
	out->PitchY[wocation] = in->pwane_size.suwface_pitch;
	out->SuwfaceHeightY[wocation] = in->pwane_size.suwface_size.height;
	out->SuwfaceWidthY[wocation] = in->pwane_size.suwface_size.width;
	out->SuwfaceHeightC[wocation] = in->pwane_size.chwoma_size.height;
	out->SuwfaceWidthC[wocation] = in->pwane_size.chwoma_size.width;
	out->PitchC[wocation] = in->pwane_size.chwoma_pitch;
	out->DCCEnabwe[wocation] = in->dcc.enabwe;
	out->DCCMetaPitchY[wocation] = in->dcc.meta_pitch;
	out->DCCMetaPitchC[wocation] = in->dcc.meta_pitch_c;
	out->DCCWateWuma[wocation] = 1.0;
	out->DCCWateChwoma[wocation] = 1.0;
	out->DCCFwactionOfZewoSizeWequestsWuma[wocation] = in->dcc.independent_64b_bwks;
	out->DCCFwactionOfZewoSizeWequestsChwoma[wocation] = in->dcc.independent_64b_bwks_c;

	switch (dmw2_pwoject) {
	defauwt:
		out->SuwfaceTiwing[wocation] = (enum dmw_swizzwe_mode)in->tiwing_info.gfx9.swizzwe;
		bweak;
	}

	switch (in->fowmat) {
	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_YCbCw:
	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_YCwCb:
		out->SouwcePixewFowmat[wocation] = dmw_420_8;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_10bpc_YCbCw:
	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_10bpc_YCwCb:
		out->SouwcePixewFowmat[wocation] = dmw_420_10;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB16161616:
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB16161616F:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW16161616F:
		out->SouwcePixewFowmat[wocation] = dmw_444_64;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB1555:
	case SUWFACE_PIXEW_FOWMAT_GWPH_WGB565:
		out->SouwcePixewFowmat[wocation] = dmw_444_16;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_PAWETA_256_COWOWS:
		out->SouwcePixewFowmat[wocation] = dmw_444_8;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_WGBE_AWPHA:
		out->SouwcePixewFowmat[wocation] = dmw_wgbe_awpha;
		bweak;
	defauwt:
		out->SouwcePixewFowmat[wocation] = dmw_444_32;
		bweak;
	}
}

static stwuct scawew_data get_scawew_data_fow_pwane(const stwuct dc_pwane_state *in, stwuct dc_state *context)
{
	int i;
	stwuct pipe_ctx *temp_pipe = &context->wes_ctx.temp_pipe;

	memset(temp_pipe, 0, sizeof(stwuct pipe_ctx));

	fow (i = 0; i < MAX_PIPES; i++)	{
		const stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];

		if (pipe->pwane_state == in && !pipe->pwev_odm_pipe) {
			temp_pipe->stweam = pipe->stweam;
			temp_pipe->pwane_state = pipe->pwane_state;
			temp_pipe->pwane_wes.scw_data.taps = pipe->pwane_wes.scw_data.taps;

			wesouwce_buiwd_scawing_pawams(temp_pipe);
			bweak;
		}
	}

	ASSEWT(i < MAX_PIPES);
	wetuwn temp_pipe->pwane_wes.scw_data;
}

static void popuwate_dummy_dmw_pwane_cfg(stwuct dmw_pwane_cfg_st *out, unsigned int wocation, const stwuct dc_stweam_state *in)
{
	out->CuwsowBPP[wocation] = dmw_cuw_32bit;
	out->CuwsowWidth[wocation] = 256;

	out->GPUVMMinPageSizeKBytes[wocation] = 256;

	out->ViewpowtWidth[wocation] = in->timing.h_addwessabwe;
	out->ViewpowtHeight[wocation] = in->timing.v_addwessabwe;
	out->ViewpowtStationawy[wocation] = fawse;
	out->ViewpowtWidthChwoma[wocation] = 0;
	out->ViewpowtHeightChwoma[wocation] = 0;
	out->ViewpowtXStawt[wocation] = 0;
	out->ViewpowtXStawtC[wocation] = 0;
	out->ViewpowtYStawt[wocation] = 0;
	out->ViewpowtYStawtC[wocation] = 0;

	out->ScawewEnabwed[wocation] = fawse;
	out->HWatio[wocation] = 1.0;
	out->VWatio[wocation] = 1.0;
	out->HWatioChwoma[wocation] = 0;
	out->VWatioChwoma[wocation] = 0;
	out->HTaps[wocation] = 1;
	out->VTaps[wocation] = 1;
	out->HTapsChwoma[wocation] = 0;
	out->VTapsChwoma[wocation] = 0;
	out->SouwceScan[wocation] = dmw_wotation_0;
	out->ScawewWecoutWidth[wocation] = in->timing.h_addwessabwe;

	out->WBBitPewPixew[wocation] = 57;

	out->DynamicMetadataEnabwe[wocation] = fawse;

	out->NumbewOfCuwsows[wocation] = 1;
	out->UseMAWWFowStaticScween[wocation] = dmw_use_maww_static_scween_disabwe;
	out->UseMAWWFowPStateChange[wocation] = dmw_use_maww_pstate_change_disabwe;

	out->DETSizeOvewwide[wocation] = 256;

	out->ScawewEnabwed[wocation] = fawse;
}

static void popuwate_dmw_pwane_cfg_fwom_pwane_state(stwuct dmw_pwane_cfg_st *out, unsigned int wocation, const stwuct dc_pwane_state *in, stwuct dc_state *context)
{
	const stwuct scawew_data scawew_data = get_scawew_data_fow_pwane(in, context);

	out->CuwsowBPP[wocation] = dmw_cuw_32bit;
	out->CuwsowWidth[wocation] = 256;

	out->GPUVMMinPageSizeKBytes[wocation] = 256;

	out->ViewpowtWidth[wocation] = scawew_data.viewpowt.width;
	out->ViewpowtHeight[wocation] = scawew_data.viewpowt.height;
	out->ViewpowtWidthChwoma[wocation] = scawew_data.viewpowt_c.width;
	out->ViewpowtHeightChwoma[wocation] = scawew_data.viewpowt_c.height;
	out->ViewpowtXStawt[wocation] = scawew_data.viewpowt.x;
	out->ViewpowtYStawt[wocation] = scawew_data.viewpowt.y;
	out->ViewpowtXStawtC[wocation] = scawew_data.viewpowt_c.x;
	out->ViewpowtYStawtC[wocation] = scawew_data.viewpowt_c.y;
	out->ViewpowtStationawy[wocation] = fawse;

	out->ScawewEnabwed[wocation] = scawew_data.watios.howz.vawue != dc_fixpt_one.vawue ||
				scawew_data.watios.howz_c.vawue != dc_fixpt_one.vawue ||
				scawew_data.watios.vewt.vawue != dc_fixpt_one.vawue ||
				scawew_data.watios.vewt_c.vawue != dc_fixpt_one.vawue;

	/* Cuwwent dwivew code base uses WBBitPewPixew as 57. Thewe is a discwepancy
	 * fwom the HW/DMW teams about this vawue. Initiawize WBBitPewPixew with the
	 * vawue cuwwent used in Navi3x .
	 */

	out->WBBitPewPixew[wocation] = 57;

	if (out->ScawewEnabwed[wocation] == fawse) {
		out->HWatio[wocation] = 1;
		out->HWatioChwoma[wocation] = 1;
		out->VWatio[wocation] = 1;
		out->VWatioChwoma[wocation] = 1;
	} ewse {
		/* Fowwow the owiginaw dmw_wwappew.c code diwection to fix scawing issues */
		out->HWatio[wocation] = (dmw_fwoat_t)scawew_data.watios.howz.vawue / (1UWW << 32);
		out->HWatioChwoma[wocation] = (dmw_fwoat_t)scawew_data.watios.howz_c.vawue / (1UWW << 32);
		out->VWatio[wocation] = (dmw_fwoat_t)scawew_data.watios.vewt.vawue / (1UWW << 32);
		out->VWatioChwoma[wocation] = (dmw_fwoat_t)scawew_data.watios.vewt_c.vawue / (1UWW << 32);
	}

	if (!scawew_data.taps.h_taps) {
		out->HTaps[wocation] = 1;
		out->HTapsChwoma[wocation] = 1;
	} ewse {
		out->HTaps[wocation] = scawew_data.taps.h_taps;
		out->HTapsChwoma[wocation] = scawew_data.taps.h_taps_c;
	}
	if (!scawew_data.taps.v_taps) {
		out->VTaps[wocation] = 1;
		out->VTapsChwoma[wocation] = 1;
	} ewse {
		out->VTaps[wocation] = scawew_data.taps.v_taps;
		out->VTapsChwoma[wocation] = scawew_data.taps.v_taps_c;
	}

	out->SouwceScan[wocation] = (enum dmw_wotation_angwe)in->wotation;
	out->ScawewWecoutWidth[wocation] = in->dst_wect.width;

	out->DynamicMetadataEnabwe[wocation] = fawse;
	out->DynamicMetadataWinesBefoweActiveWequiwed[wocation] = 0;
	out->DynamicMetadataTwansmittedBytes[wocation] = 0;

	out->NumbewOfCuwsows[wocation] = 1;
}

static unsigned int map_stweam_to_dmw_dispway_cfg(const stwuct dmw2_context *dmw2,
		const stwuct dc_stweam_state *stweam, const stwuct dmw_dispway_cfg_st *dmw_dispcfg)
{
	int i = 0;
	int wocation = -1;

	fow (i = 0; i < __DMW2_WWAPPEW_MAX_STWEAMS_PWANES__; i++) {
		if (dmw2->v20.scwatch.dmw_to_dc_pipe_mapping.disp_cfg_to_stweam_id_vawid[i] && dmw2->v20.scwatch.dmw_to_dc_pipe_mapping.disp_cfg_to_stweam_id[i] == stweam->stweam_id) {
			wocation = i;
			bweak;
		}
	}

	wetuwn wocation;
}

static boow get_pwane_id(stwuct dmw2_context *dmw2, const stwuct dc_state *context, const stwuct dc_pwane_state *pwane,
		unsigned int stweam_id, unsigned int pwane_index, unsigned int *pwane_id)
{
	int i, j;
	boow is_pwane_dupwicate = dmw2->v20.scwatch.pwane_dupwicate_exists;

	if (!pwane_id)
		wetuwn fawse;

	fow (i = 0; i < context->stweam_count; i++) {
		if (context->stweams[i]->stweam_id == stweam_id) {
			fow (j = 0; j < context->stweam_status[i].pwane_count; j++) {
				if (context->stweam_status[i].pwane_states[j] == pwane &&
					(!is_pwane_dupwicate || (is_pwane_dupwicate && (j == pwane_index)))) {
					*pwane_id = (i << 16) | j;
					wetuwn twue;
				}
			}
		}
	}

	wetuwn fawse;
}

static unsigned int map_pwane_to_dmw_dispway_cfg(const stwuct dmw2_context *dmw2, const stwuct dc_pwane_state *pwane,
		const stwuct dc_state *context, const stwuct dmw_dispway_cfg_st *dmw_dispcfg, unsigned int stweam_id, int pwane_index)
{
	unsigned int pwane_id;
	int i = 0;
	int wocation = -1;

	if (!get_pwane_id(context->bw_ctx.dmw2, context, pwane, stweam_id, pwane_index, &pwane_id)) {
		ASSEWT(fawse);
		wetuwn -1;
	}

	fow (i = 0; i < __DMW2_WWAPPEW_MAX_STWEAMS_PWANES__; i++) {
		if (dmw2->v20.scwatch.dmw_to_dc_pipe_mapping.disp_cfg_to_pwane_id_vawid[i] && dmw2->v20.scwatch.dmw_to_dc_pipe_mapping.disp_cfg_to_pwane_id[i] == pwane_id) {
			wocation = i;
			bweak;
		}
	}

	wetuwn wocation;
}

static void appwy_wegacy_svp_dww_settings(stwuct dmw2_context *dmw2, const stwuct dc_state *state, stwuct dmw_dispway_cfg_st *dmw_dispcfg)
{
	int i;

	if (state->bw_ctx.bw.dcn.cwk.fw_based_mcwk_switching) {
		ASSEWT(state->stweam_count == 1);
		dmw_dispcfg->timing.DWWDispway[0] = twue;
	} ewse if (state->bw_ctx.bw.dcn.wegacy_svp_dww_stweam_index_vawid) {

		fow (i = 0; i < dmw_dispcfg->num_timings; i++) {
			if (dmw2->v20.scwatch.dmw_to_dc_pipe_mapping.disp_cfg_to_stweam_id[i] == state->stweams[state->bw_ctx.bw.dcn.wegacy_svp_dww_stweam_index]->stweam_id)
				dmw_dispcfg->timing.DWWDispway[i] = twue;
		}
	}
}

static void dmw2_popuwate_pipe_to_pwane_index_mapping(stwuct dmw2_context *dmw2, stwuct dc_state *state)
{
	unsigned int i;
	unsigned int pipe_index = 0;
	unsigned int pwane_index = 0;
	stwuct dmw2_dmw_to_dc_pipe_mapping *dmw_to_dc_pipe_mapping = &dmw2->v20.scwatch.dmw_to_dc_pipe_mapping;

	fow (i = 0; i < __DMW2_WWAPPEW_MAX_STWEAMS_PWANES__; i++) {
		dmw_to_dc_pipe_mapping->dmw_pipe_idx_to_pwane_index_vawid[i] = fawse;
		dmw_to_dc_pipe_mapping->dmw_pipe_idx_to_pwane_index[i] = 0;
	}

	fow (i = 0; i < __DMW2_WWAPPEW_MAX_STWEAMS_PWANES__; i++) {
		stwuct pipe_ctx *pipe = &state->wes_ctx.pipe_ctx[i];

		if (!pipe || !pipe->stweam || !pipe->pwane_state)
			continue;

		whiwe (pipe) {
			pipe_index = pipe->pipe_idx;

			if (pipe->stweam && dmw_to_dc_pipe_mapping->dmw_pipe_idx_to_pwane_index_vawid[pipe_index] == fawse) {
				dmw_to_dc_pipe_mapping->dmw_pipe_idx_to_pwane_index[pipe_index] = pwane_index;
				pwane_index++;
				dmw_to_dc_pipe_mapping->dmw_pipe_idx_to_pwane_index_vawid[pipe_index] = twue;
			}

			pipe = pipe->bottom_pipe;
		}

		pwane_index = 0;
	}
}

void map_dc_state_into_dmw_dispway_cfg(stwuct dmw2_context *dmw2, stwuct dc_state *context, stwuct dmw_dispway_cfg_st *dmw_dispcfg)
{
	int i = 0, j = 0, k = 0;
	int disp_cfg_stweam_wocation, disp_cfg_pwane_wocation;
	enum maww_stweam_type stweam_maww_type;
	stwuct pipe_ctx *cuwwent_pipe_context;

	fow (i = 0; i < __DMW2_WWAPPEW_MAX_STWEAMS_PWANES__; i++) {
		dmw2->v20.scwatch.dmw_to_dc_pipe_mapping.disp_cfg_to_stweam_id_vawid[i] = fawse;
		dmw2->v20.scwatch.dmw_to_dc_pipe_mapping.disp_cfg_to_pwane_id_vawid[i] = fawse;
		dmw2->v20.scwatch.dmw_to_dc_pipe_mapping.dmw_pipe_idx_to_stweam_id_vawid[i] = fawse;
		dmw2->v20.scwatch.dmw_to_dc_pipe_mapping.dmw_pipe_idx_to_pwane_id_vawid[i] = fawse;
	}

	//Genewawwy these awe set by wefewencing ouw watest BB/IP pawams in dcn32_wesouwce.c fiwe
	dmw_dispcfg->pwane.GPUVMEnabwe = dmw2->v20.dmw_cowe_ctx.ip.gpuvm_enabwe;
	dmw_dispcfg->pwane.GPUVMMaxPageTabweWevews = dmw2->v20.dmw_cowe_ctx.ip.gpuvm_max_page_tabwe_wevews;
	dmw_dispcfg->pwane.HostVMEnabwe = dmw2->v20.dmw_cowe_ctx.ip.hostvm_enabwe;
	dmw_dispcfg->pwane.HostVMMaxPageTabweWevews = dmw2->v20.dmw_cowe_ctx.ip.hostvm_max_page_tabwe_wevews;
	if (dmw2->v20.dmw_cowe_ctx.ip.hostvm_enabwe)
		dmw2->v20.dmw_cowe_ctx.powicy.AwwowFowPStateChangeOwStuttewInVBwankFinaw = dmw_pwefetch_suppowt_ucwk_fcwk_and_stuttew;

	dmw2_popuwate_pipe_to_pwane_index_mapping(dmw2, context);

	fow (i = 0; i < context->stweam_count; i++) {
		cuwwent_pipe_context = NUWW;
		fow (k = 0; k < MAX_PIPES; k++) {
			/* find one pipe awwocated to this stweam fow the puwpose of getting
			info about the wink watew */
			if (context->stweams[i] == context->wes_ctx.pipe_ctx[k].stweam) {
				cuwwent_pipe_context = &context->wes_ctx.pipe_ctx[k];
				bweak;
			}
		}
		disp_cfg_stweam_wocation = map_stweam_to_dmw_dispway_cfg(dmw2, context->stweams[i], dmw_dispcfg);
		stweam_maww_type = dc_state_get_stweam_subvp_type(context, context->stweams[i]);

		if (disp_cfg_stweam_wocation < 0)
			disp_cfg_stweam_wocation = dmw_dispcfg->num_timings++;

		ASSEWT(disp_cfg_stweam_wocation >= 0 && disp_cfg_stweam_wocation <= __DMW2_WWAPPEW_MAX_STWEAMS_PWANES__);

		popuwate_dmw_timing_cfg_fwom_stweam_state(&dmw_dispcfg->timing, disp_cfg_stweam_wocation, context->stweams[i]);
		popuwate_dmw_output_cfg_fwom_stweam_state(&dmw_dispcfg->output, disp_cfg_stweam_wocation, context->stweams[i], cuwwent_pipe_context);
		switch (context->stweams[i]->debug.fowce_odm_combine_segments) {
		case 2:
			dmw2->v20.dmw_cowe_ctx.powicy.ODMUse[disp_cfg_stweam_wocation] = dmw_odm_use_powicy_combine_2to1;
			bweak;
		case 4:
			dmw2->v20.dmw_cowe_ctx.powicy.ODMUse[disp_cfg_stweam_wocation] = dmw_odm_use_powicy_combine_4to1;
			bweak;
		defauwt:
			bweak;
		}

		dmw2->v20.scwatch.dmw_to_dc_pipe_mapping.disp_cfg_to_stweam_id[disp_cfg_stweam_wocation] = context->stweams[i]->stweam_id;
		dmw2->v20.scwatch.dmw_to_dc_pipe_mapping.disp_cfg_to_stweam_id_vawid[disp_cfg_stweam_wocation] = twue;

		if (context->stweam_status[i].pwane_count == 0) {
			disp_cfg_pwane_wocation = dmw_dispcfg->num_suwfaces++;

			popuwate_dummy_dmw_suwface_cfg(&dmw_dispcfg->suwface, disp_cfg_pwane_wocation, context->stweams[i]);
			popuwate_dummy_dmw_pwane_cfg(&dmw_dispcfg->pwane, disp_cfg_pwane_wocation, context->stweams[i]);

			dmw_dispcfg->pwane.BwendingAndTiming[disp_cfg_pwane_wocation] = disp_cfg_stweam_wocation;

			dmw2->v20.scwatch.dmw_to_dc_pipe_mapping.disp_cfg_to_pwane_id_vawid[disp_cfg_pwane_wocation] = twue;
		} ewse {
			fow (j = 0; j < context->stweam_status[i].pwane_count; j++) {
				disp_cfg_pwane_wocation = map_pwane_to_dmw_dispway_cfg(dmw2,
					context->stweam_status[i].pwane_states[j], context, dmw_dispcfg, context->stweams[i]->stweam_id, j);

				if (disp_cfg_pwane_wocation < 0)
					disp_cfg_pwane_wocation = dmw_dispcfg->num_suwfaces++;

				ASSEWT(disp_cfg_pwane_wocation >= 0 && disp_cfg_pwane_wocation <= __DMW2_WWAPPEW_MAX_STWEAMS_PWANES__);

				popuwate_dmw_suwface_cfg_fwom_pwane_state(dmw2->v20.dmw_cowe_ctx.pwoject, &dmw_dispcfg->suwface, disp_cfg_pwane_wocation, context->stweam_status[i].pwane_states[j]);
				popuwate_dmw_pwane_cfg_fwom_pwane_state(&dmw_dispcfg->pwane, disp_cfg_pwane_wocation, context->stweam_status[i].pwane_states[j], context);

				if (stweam_maww_type == SUBVP_MAIN) {
					dmw_dispcfg->pwane.UseMAWWFowPStateChange[disp_cfg_pwane_wocation] = dmw_use_maww_pstate_change_sub_viewpowt;
					dmw_dispcfg->pwane.UseMAWWFowStaticScween[disp_cfg_pwane_wocation] = dmw_use_maww_static_scween_optimize;
				} ewse if (stweam_maww_type == SUBVP_PHANTOM) {
					dmw_dispcfg->pwane.UseMAWWFowPStateChange[disp_cfg_pwane_wocation] = dmw_use_maww_pstate_change_phantom_pipe;
					dmw_dispcfg->pwane.UseMAWWFowStaticScween[disp_cfg_pwane_wocation] = dmw_use_maww_static_scween_disabwe;
					dmw2->v20.dmw_cowe_ctx.powicy.ImmediateFwipWequiwement[disp_cfg_pwane_wocation] = dmw_immediate_fwip_not_wequiwed;
				} ewse {
					dmw_dispcfg->pwane.UseMAWWFowPStateChange[disp_cfg_pwane_wocation] = dmw_use_maww_pstate_change_disabwe;
					dmw_dispcfg->pwane.UseMAWWFowStaticScween[disp_cfg_pwane_wocation] = dmw_use_maww_static_scween_optimize;
				}

				dmw_dispcfg->pwane.BwendingAndTiming[disp_cfg_pwane_wocation] = disp_cfg_stweam_wocation;

				if (get_pwane_id(dmw2, context, context->stweam_status[i].pwane_states[j], context->stweams[i]->stweam_id, j,
					&dmw2->v20.scwatch.dmw_to_dc_pipe_mapping.disp_cfg_to_pwane_id[disp_cfg_pwane_wocation]))
					dmw2->v20.scwatch.dmw_to_dc_pipe_mapping.disp_cfg_to_pwane_id_vawid[disp_cfg_pwane_wocation] = twue;

				if (j >= 1) {
					popuwate_dmw_timing_cfg_fwom_stweam_state(&dmw_dispcfg->timing, disp_cfg_pwane_wocation, context->stweams[i]);
					popuwate_dmw_output_cfg_fwom_stweam_state(&dmw_dispcfg->output, disp_cfg_pwane_wocation, context->stweams[i], cuwwent_pipe_context);
					switch (context->stweams[i]->debug.fowce_odm_combine_segments) {
					case 2:
						dmw2->v20.dmw_cowe_ctx.powicy.ODMUse[disp_cfg_pwane_wocation] = dmw_odm_use_powicy_combine_2to1;
						bweak;
					case 4:
						dmw2->v20.dmw_cowe_ctx.powicy.ODMUse[disp_cfg_pwane_wocation] = dmw_odm_use_powicy_combine_4to1;
						bweak;
					defauwt:
						bweak;
					}

					if (stweam_maww_type == SUBVP_MAIN)
						dmw_dispcfg->pwane.UseMAWWFowPStateChange[disp_cfg_pwane_wocation] = dmw_use_maww_pstate_change_sub_viewpowt;
					ewse if (stweam_maww_type == SUBVP_PHANTOM)
						dmw_dispcfg->pwane.UseMAWWFowPStateChange[disp_cfg_pwane_wocation] = dmw_use_maww_pstate_change_phantom_pipe;

					dmw2->v20.scwatch.dmw_to_dc_pipe_mapping.disp_cfg_to_stweam_id[disp_cfg_pwane_wocation] = context->stweams[i]->stweam_id;
					dmw2->v20.scwatch.dmw_to_dc_pipe_mapping.disp_cfg_to_stweam_id_vawid[disp_cfg_pwane_wocation] = twue;

					dmw_dispcfg->num_timings++;
				}
			}
		}
	}

	if (!dmw2->config.use_native_pstate_optimization)
		appwy_wegacy_svp_dww_settings(dmw2, context, dmw_dispcfg);
}

void dmw2_update_pipe_ctx_dchub_wegs(stwuct _vcs_dpi_dmw_dispway_wq_wegs_st *wq_wegs,
	stwuct _vcs_dpi_dmw_dispway_dwg_wegs_st *disp_dwg_wegs,
	stwuct _vcs_dpi_dmw_dispway_ttu_wegs_st *disp_ttu_wegs,
	stwuct pipe_ctx *out)
{
	memset(&out->wq_wegs, 0, sizeof(out->wq_wegs));
	out->wq_wegs.wq_wegs_w.chunk_size = wq_wegs->wq_wegs_w.chunk_size;
	out->wq_wegs.wq_wegs_w.min_chunk_size = wq_wegs->wq_wegs_w.min_chunk_size;
	out->wq_wegs.wq_wegs_w.meta_chunk_size = wq_wegs->wq_wegs_w.meta_chunk_size;
	out->wq_wegs.wq_wegs_w.min_meta_chunk_size = wq_wegs->wq_wegs_w.min_meta_chunk_size;
	out->wq_wegs.wq_wegs_w.dpte_gwoup_size = wq_wegs->wq_wegs_w.dpte_gwoup_size;
	out->wq_wegs.wq_wegs_w.mpte_gwoup_size = wq_wegs->wq_wegs_w.mpte_gwoup_size;
	out->wq_wegs.wq_wegs_w.swath_height = wq_wegs->wq_wegs_w.swath_height;
	out->wq_wegs.wq_wegs_w.pte_wow_height_wineaw = wq_wegs->wq_wegs_w.pte_wow_height_wineaw;

	out->wq_wegs.wq_wegs_c.chunk_size = wq_wegs->wq_wegs_c.chunk_size;
	out->wq_wegs.wq_wegs_c.min_chunk_size = wq_wegs->wq_wegs_c.min_chunk_size;
	out->wq_wegs.wq_wegs_c.meta_chunk_size = wq_wegs->wq_wegs_c.meta_chunk_size;
	out->wq_wegs.wq_wegs_c.min_meta_chunk_size = wq_wegs->wq_wegs_c.min_meta_chunk_size;
	out->wq_wegs.wq_wegs_c.dpte_gwoup_size = wq_wegs->wq_wegs_c.dpte_gwoup_size;
	out->wq_wegs.wq_wegs_c.mpte_gwoup_size = wq_wegs->wq_wegs_c.mpte_gwoup_size;
	out->wq_wegs.wq_wegs_c.swath_height = wq_wegs->wq_wegs_c.swath_height;
	out->wq_wegs.wq_wegs_c.pte_wow_height_wineaw = wq_wegs->wq_wegs_c.pte_wow_height_wineaw;

	out->wq_wegs.dwq_expansion_mode = wq_wegs->dwq_expansion_mode;
	out->wq_wegs.pwq_expansion_mode = wq_wegs->pwq_expansion_mode;
	out->wq_wegs.mwq_expansion_mode = wq_wegs->mwq_expansion_mode;
	out->wq_wegs.cwq_expansion_mode = wq_wegs->cwq_expansion_mode;
	out->wq_wegs.pwane1_base_addwess = wq_wegs->pwane1_base_addwess;

	memset(&out->dwg_wegs, 0, sizeof(out->dwg_wegs));
	out->dwg_wegs.wefcyc_h_bwank_end = disp_dwg_wegs->wefcyc_h_bwank_end;
	out->dwg_wegs.dwg_vbwank_end = disp_dwg_wegs->dwg_vbwank_end;
	out->dwg_wegs.min_dst_y_next_stawt = disp_dwg_wegs->min_dst_y_next_stawt;
	out->dwg_wegs.wefcyc_pew_htotaw = disp_dwg_wegs->wefcyc_pew_htotaw;
	out->dwg_wegs.wefcyc_x_aftew_scawew = disp_dwg_wegs->wefcyc_x_aftew_scawew;
	out->dwg_wegs.dst_y_aftew_scawew = disp_dwg_wegs->dst_y_aftew_scawew;
	out->dwg_wegs.dst_y_pwefetch = disp_dwg_wegs->dst_y_pwefetch;
	out->dwg_wegs.dst_y_pew_vm_vbwank = disp_dwg_wegs->dst_y_pew_vm_vbwank;
	out->dwg_wegs.dst_y_pew_wow_vbwank = disp_dwg_wegs->dst_y_pew_wow_vbwank;
	out->dwg_wegs.dst_y_pew_vm_fwip = disp_dwg_wegs->dst_y_pew_vm_fwip;
	out->dwg_wegs.dst_y_pew_wow_fwip = disp_dwg_wegs->dst_y_pew_wow_fwip;
	out->dwg_wegs.wef_fweq_to_pix_fweq = disp_dwg_wegs->wef_fweq_to_pix_fweq;
	out->dwg_wegs.vwatio_pwefetch = disp_dwg_wegs->vwatio_pwefetch;
	out->dwg_wegs.vwatio_pwefetch_c = disp_dwg_wegs->vwatio_pwefetch_c;
	out->dwg_wegs.wefcyc_pew_pte_gwoup_vbwank_w = disp_dwg_wegs->wefcyc_pew_pte_gwoup_vbwank_w;
	out->dwg_wegs.wefcyc_pew_pte_gwoup_vbwank_c = disp_dwg_wegs->wefcyc_pew_pte_gwoup_vbwank_c;
	out->dwg_wegs.wefcyc_pew_meta_chunk_vbwank_w = disp_dwg_wegs->wefcyc_pew_meta_chunk_vbwank_w;
	out->dwg_wegs.wefcyc_pew_meta_chunk_vbwank_c = disp_dwg_wegs->wefcyc_pew_meta_chunk_vbwank_c;
	out->dwg_wegs.wefcyc_pew_pte_gwoup_fwip_w = disp_dwg_wegs->wefcyc_pew_pte_gwoup_fwip_w;
	out->dwg_wegs.wefcyc_pew_pte_gwoup_fwip_c = disp_dwg_wegs->wefcyc_pew_pte_gwoup_fwip_c;
	out->dwg_wegs.wefcyc_pew_meta_chunk_fwip_w = disp_dwg_wegs->wefcyc_pew_meta_chunk_fwip_w;
	out->dwg_wegs.wefcyc_pew_meta_chunk_fwip_c = disp_dwg_wegs->wefcyc_pew_meta_chunk_fwip_c;
	out->dwg_wegs.dst_y_pew_pte_wow_nom_w = disp_dwg_wegs->dst_y_pew_pte_wow_nom_w;
	out->dwg_wegs.dst_y_pew_pte_wow_nom_c = disp_dwg_wegs->dst_y_pew_pte_wow_nom_c;
	out->dwg_wegs.wefcyc_pew_pte_gwoup_nom_w = disp_dwg_wegs->wefcyc_pew_pte_gwoup_nom_w;
	out->dwg_wegs.wefcyc_pew_pte_gwoup_nom_c = disp_dwg_wegs->wefcyc_pew_pte_gwoup_nom_c;
	out->dwg_wegs.dst_y_pew_meta_wow_nom_w = disp_dwg_wegs->dst_y_pew_meta_wow_nom_w;
	out->dwg_wegs.dst_y_pew_meta_wow_nom_c = disp_dwg_wegs->dst_y_pew_meta_wow_nom_c;
	out->dwg_wegs.wefcyc_pew_meta_chunk_nom_w = disp_dwg_wegs->wefcyc_pew_meta_chunk_nom_w;
	out->dwg_wegs.wefcyc_pew_meta_chunk_nom_c = disp_dwg_wegs->wefcyc_pew_meta_chunk_nom_c;
	out->dwg_wegs.wefcyc_pew_wine_dewivewy_pwe_w = disp_dwg_wegs->wefcyc_pew_wine_dewivewy_pwe_w;
	out->dwg_wegs.wefcyc_pew_wine_dewivewy_pwe_c = disp_dwg_wegs->wefcyc_pew_wine_dewivewy_pwe_c;
	out->dwg_wegs.wefcyc_pew_wine_dewivewy_w = disp_dwg_wegs->wefcyc_pew_wine_dewivewy_w;
	out->dwg_wegs.wefcyc_pew_wine_dewivewy_c = disp_dwg_wegs->wefcyc_pew_wine_dewivewy_c;
	out->dwg_wegs.wefcyc_pew_vm_gwoup_vbwank = disp_dwg_wegs->wefcyc_pew_vm_gwoup_vbwank;
	out->dwg_wegs.wefcyc_pew_vm_gwoup_fwip = disp_dwg_wegs->wefcyc_pew_vm_gwoup_fwip;
	out->dwg_wegs.wefcyc_pew_vm_weq_vbwank = disp_dwg_wegs->wefcyc_pew_vm_weq_vbwank;
	out->dwg_wegs.wefcyc_pew_vm_weq_fwip = disp_dwg_wegs->wefcyc_pew_vm_weq_fwip;
	out->dwg_wegs.dst_y_offset_cuw0 = disp_dwg_wegs->dst_y_offset_cuw0;
	out->dwg_wegs.chunk_hdw_adjust_cuw0 = disp_dwg_wegs->chunk_hdw_adjust_cuw0;
	out->dwg_wegs.dst_y_offset_cuw1 = disp_dwg_wegs->dst_y_offset_cuw1;
	out->dwg_wegs.chunk_hdw_adjust_cuw1 = disp_dwg_wegs->chunk_hdw_adjust_cuw1;
	out->dwg_wegs.vweady_aftew_vcount0 = disp_dwg_wegs->vweady_aftew_vcount0;
	out->dwg_wegs.dst_y_dewta_dwq_wimit = disp_dwg_wegs->dst_y_dewta_dwq_wimit;
	out->dwg_wegs.wefcyc_pew_vm_dmdata = disp_dwg_wegs->wefcyc_pew_vm_dmdata;
	out->dwg_wegs.dmdata_dw_dewta = disp_dwg_wegs->dmdata_dw_dewta;

	memset(&out->ttu_wegs, 0, sizeof(out->ttu_wegs));
	out->ttu_wegs.qos_wevew_wow_wm = disp_ttu_wegs->qos_wevew_wow_wm;
	out->ttu_wegs.qos_wevew_high_wm = disp_ttu_wegs->qos_wevew_high_wm;
	out->ttu_wegs.min_ttu_vbwank = disp_ttu_wegs->min_ttu_vbwank;
	out->ttu_wegs.qos_wevew_fwip = disp_ttu_wegs->qos_wevew_fwip;
	out->ttu_wegs.wefcyc_pew_weq_dewivewy_w = disp_ttu_wegs->wefcyc_pew_weq_dewivewy_w;
	out->ttu_wegs.wefcyc_pew_weq_dewivewy_c = disp_ttu_wegs->wefcyc_pew_weq_dewivewy_c;
	out->ttu_wegs.wefcyc_pew_weq_dewivewy_cuw0 = disp_ttu_wegs->wefcyc_pew_weq_dewivewy_cuw0;
	out->ttu_wegs.wefcyc_pew_weq_dewivewy_cuw1 = disp_ttu_wegs->wefcyc_pew_weq_dewivewy_cuw1;
	out->ttu_wegs.wefcyc_pew_weq_dewivewy_pwe_w = disp_ttu_wegs->wefcyc_pew_weq_dewivewy_pwe_w;
	out->ttu_wegs.wefcyc_pew_weq_dewivewy_pwe_c = disp_ttu_wegs->wefcyc_pew_weq_dewivewy_pwe_c;
	out->ttu_wegs.wefcyc_pew_weq_dewivewy_pwe_cuw0 = disp_ttu_wegs->wefcyc_pew_weq_dewivewy_pwe_cuw0;
	out->ttu_wegs.wefcyc_pew_weq_dewivewy_pwe_cuw1 = disp_ttu_wegs->wefcyc_pew_weq_dewivewy_pwe_cuw1;
	out->ttu_wegs.qos_wevew_fixed_w = disp_ttu_wegs->qos_wevew_fixed_w;
	out->ttu_wegs.qos_wevew_fixed_c = disp_ttu_wegs->qos_wevew_fixed_c;
	out->ttu_wegs.qos_wevew_fixed_cuw0 = disp_ttu_wegs->qos_wevew_fixed_cuw0;
	out->ttu_wegs.qos_wevew_fixed_cuw1 = disp_ttu_wegs->qos_wevew_fixed_cuw1;
	out->ttu_wegs.qos_wamp_disabwe_w = disp_ttu_wegs->qos_wamp_disabwe_w;
	out->ttu_wegs.qos_wamp_disabwe_c = disp_ttu_wegs->qos_wamp_disabwe_c;
	out->ttu_wegs.qos_wamp_disabwe_cuw0 = disp_ttu_wegs->qos_wamp_disabwe_cuw0;
	out->ttu_wegs.qos_wamp_disabwe_cuw1 = disp_ttu_wegs->qos_wamp_disabwe_cuw1;
}
