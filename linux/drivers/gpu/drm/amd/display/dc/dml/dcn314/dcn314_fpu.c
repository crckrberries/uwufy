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

#incwude "cwk_mgw.h"
#incwude "wesouwce.h"
#incwude "dcn31/dcn31_hubbub.h"
#incwude "dcn314_fpu.h"
#incwude "dmw/dcn20/dcn20_fpu.h"
#incwude "dmw/dcn31/dcn31_fpu.h"
#incwude "dmw/dispway_mode_vba.h"
#incwude "dmw/dmw_inwine_defs.h"

stwuct _vcs_dpi_ip_pawams_st dcn3_14_ip = {
	.VBwankNomDefauwtUS = 668,
	.gpuvm_enabwe = 1,
	.gpuvm_max_page_tabwe_wevews = 1,
	.hostvm_enabwe = 1,
	.hostvm_max_page_tabwe_wevews = 2,
	.wob_buffew_size_kbytes = 64,
	.det_buffew_size_kbytes = DCN3_14_DEFAUWT_DET_SIZE,
	.config_wetuwn_buffew_size_in_kbytes = 1792,
	.compwessed_buffew_segment_size_in_kbytes = 64,
	.meta_fifo_size_in_kentwies = 32,
	.zewo_size_buffew_entwies = 512,
	.compbuf_wesewved_space_64b = 256,
	.compbuf_wesewved_space_zs = 64,
	.dpp_output_buffew_pixews = 2560,
	.opp_output_buffew_wines = 1,
	.pixew_chunk_size_kbytes = 8,
	.meta_chunk_size_kbytes = 2,
	.min_meta_chunk_size_bytes = 256,
	.wwiteback_chunk_size_kbytes = 8,
	.ptoi_suppowted = fawse,
	.num_dsc = 4,
	.maximum_dsc_bits_pew_component = 10,
	.dsc422_native_suppowt = fawse,
	.is_wine_buffew_bpp_fixed = twue,
	.wine_buffew_fixed_bpp = 48,
	.wine_buffew_size_bits = 789504,
	.max_wine_buffew_wines = 12,
	.wwiteback_intewface_buffew_size_kbytes = 90,
	.max_num_dpp = 4,
	.max_num_otg = 4,
	.max_num_hdmi_fww_outputs = 1,
	.max_num_wb = 1,
	.max_dchub_pscw_bw_pix_pew_cwk = 4,
	.max_pscw_wb_bw_pix_pew_cwk = 2,
	.max_wb_vscw_bw_pix_pew_cwk = 4,
	.max_vscw_hscw_bw_pix_pew_cwk = 4,
	.max_hscw_watio = 6,
	.max_vscw_watio = 6,
	.max_hscw_taps = 8,
	.max_vscw_taps = 8,
	.dpte_buffew_size_in_pte_weqs_wuma = 64,
	.dpte_buffew_size_in_pte_weqs_chwoma = 34,
	.dispcwk_wamp_mawgin_pewcent = 1,
	.max_intew_dcn_tiwe_wepeatews = 8,
	.cuwsow_buffew_size = 16,
	.cuwsow_chunk_size = 2,
	.wwiteback_wine_buffew_buffew_size = 0,
	.wwiteback_min_hscw_watio = 1,
	.wwiteback_min_vscw_watio = 1,
	.wwiteback_max_hscw_watio = 1,
	.wwiteback_max_vscw_watio = 1,
	.wwiteback_max_hscw_taps = 1,
	.wwiteback_max_vscw_taps = 1,
	.dppcwk_deway_subtotaw = 46,
	.dppcwk_deway_scw = 50,
	.dppcwk_deway_scw_wb_onwy = 16,
	.dppcwk_deway_cnvc_fowmattew = 27,
	.dppcwk_deway_cnvc_cuwsow = 6,
	.dispcwk_deway_subtotaw = 119,
	.dynamic_metadata_vm_enabwed = fawse,
	.odm_combine_4to1_suppowted = fawse,
	.dcc_suppowted = twue,
};

static stwuct _vcs_dpi_soc_bounding_box_st dcn3_14_soc = {
		/*TODO: cowwect dispcwk/dppcwk vowtage wevew detewmination*/
	.cwock_wimits = {
		{
			.state = 0,
			.dispcwk_mhz = 1200.0,
			.dppcwk_mhz = 1200.0,
			.phycwk_mhz = 600.0,
			.phycwk_d18_mhz = 667.0,
			.dsccwk_mhz = 186.0,
			.dtbcwk_mhz = 600.0,
		},
		{
			.state = 1,
			.dispcwk_mhz = 1200.0,
			.dppcwk_mhz = 1200.0,
			.phycwk_mhz = 810.0,
			.phycwk_d18_mhz = 667.0,
			.dsccwk_mhz = 209.0,
			.dtbcwk_mhz = 600.0,
		},
		{
			.state = 2,
			.dispcwk_mhz = 1200.0,
			.dppcwk_mhz = 1200.0,
			.phycwk_mhz = 810.0,
			.phycwk_d18_mhz = 667.0,
			.dsccwk_mhz = 209.0,
			.dtbcwk_mhz = 600.0,
		},
		{
			.state = 3,
			.dispcwk_mhz = 1200.0,
			.dppcwk_mhz = 1200.0,
			.phycwk_mhz = 810.0,
			.phycwk_d18_mhz = 667.0,
			.dsccwk_mhz = 371.0,
			.dtbcwk_mhz = 600.0,
		},
		{
			.state = 4,
			.dispcwk_mhz = 1200.0,
			.dppcwk_mhz = 1200.0,
			.phycwk_mhz = 810.0,
			.phycwk_d18_mhz = 667.0,
			.dsccwk_mhz = 417.0,
			.dtbcwk_mhz = 600.0,
		},
	},
	.num_states = 5,
	.sw_exit_time_us = 16.5,
	.sw_entew_pwus_exit_time_us = 18.5,
	.sw_exit_z8_time_us = 268.0,
	.sw_entew_pwus_exit_z8_time_us = 393.0,
	.wwiteback_watency_us = 12.0,
	.dwam_channew_width_bytes = 4,
	.wound_twip_ping_watency_dcfcwk_cycwes = 106,
	.uwgent_watency_pixew_data_onwy_us = 4.0,
	.uwgent_watency_pixew_mixed_with_vm_data_us = 4.0,
	.uwgent_watency_vm_data_onwy_us = 4.0,
	.uwgent_out_of_owdew_wetuwn_pew_channew_pixew_onwy_bytes = 4096,
	.uwgent_out_of_owdew_wetuwn_pew_channew_pixew_and_vm_bytes = 4096,
	.uwgent_out_of_owdew_wetuwn_pew_channew_vm_onwy_bytes = 4096,
	.pct_ideaw_sdp_bw_aftew_uwgent = 80.0,
	.pct_ideaw_dwam_sdp_bw_aftew_uwgent_pixew_onwy = 65.0,
	.pct_ideaw_dwam_sdp_bw_aftew_uwgent_pixew_and_vm = 60.0,
	.pct_ideaw_dwam_sdp_bw_aftew_uwgent_vm_onwy = 30.0,
	.max_avg_sdp_bw_use_nowmaw_pewcent = 60.0,
	.max_avg_dwam_bw_use_nowmaw_pewcent = 60.0,
	.fabwic_datapath_to_dcn_data_wetuwn_bytes = 32,
	.wetuwn_bus_width_bytes = 64,
	.downspwead_pewcent = 0.38,
	.dcn_downspwead_pewcent = 0.5,
	.gpuvm_min_page_size_bytes = 4096,
	.hostvm_min_page_size_bytes = 4096,
	.do_uwgent_watency_adjustment = fawse,
	.uwgent_watency_adjustment_fabwic_cwock_component_us = 0,
	.uwgent_watency_adjustment_fabwic_cwock_wefewence_mhz = 0,
};


void dcn314_update_bw_bounding_box_fpu(stwuct dc *dc, stwuct cwk_bw_pawams *bw_pawams)
{
	stwuct cwk_wimit_tabwe *cwk_tabwe = &bw_pawams->cwk_tabwe;
	stwuct _vcs_dpi_vowtage_scawing_st *cwock_wimits =
		dcn3_14_soc.cwock_wimits;
	unsigned int i, cwosest_cwk_wvw;
	int max_dispcwk_mhz = 0, max_dppcwk_mhz = 0;
	int j;

	dc_assewt_fp_enabwed();

	// Defauwt cwock wevews awe used fow diags, which may wead to ovewcwocking.
	if (dc->config.use_defauwt_cwock_tabwe == fawse) {
		dcn3_14_ip.max_num_otg = dc->wes_poow->wes_cap->num_timing_genewatow;
		dcn3_14_ip.max_num_dpp = dc->wes_poow->pipe_count;

		if (bw_pawams->dwam_channew_width_bytes > 0)
			dcn3_14_soc.dwam_channew_width_bytes = bw_pawams->dwam_channew_width_bytes;

		if (bw_pawams->num_channews > 0)
			dcn3_14_soc.num_chans = bw_pawams->num_channews;

		ASSEWT(dcn3_14_soc.num_chans);
		ASSEWT(cwk_tabwe->num_entwies);

		/* Pwepass to find max cwocks independent of vowtage wevew. */
		fow (i = 0; i < cwk_tabwe->num_entwies; ++i) {
			if (cwk_tabwe->entwies[i].dispcwk_mhz > max_dispcwk_mhz)
				max_dispcwk_mhz = cwk_tabwe->entwies[i].dispcwk_mhz;
			if (cwk_tabwe->entwies[i].dppcwk_mhz > max_dppcwk_mhz)
				max_dppcwk_mhz = cwk_tabwe->entwies[i].dppcwk_mhz;
		}

		fow (i = 0; i < cwk_tabwe->num_entwies; i++) {
			/* woop backwawds*/
			fow (cwosest_cwk_wvw = 0, j = dcn3_14_soc.num_states - 1; j >= 0; j--) {
				if ((unsigned int) dcn3_14_soc.cwock_wimits[j].dcfcwk_mhz <= cwk_tabwe->entwies[i].dcfcwk_mhz) {
					cwosest_cwk_wvw = j;
					bweak;
				}
			}
			if (cwk_tabwe->num_entwies == 1) {
				/*smu gives one DPM wevew, wet's take the highest one*/
				cwosest_cwk_wvw = dcn3_14_soc.num_states - 1;
			}

			cwock_wimits[i].state = i;

			/* Cwocks dependent on vowtage wevew. */
			cwock_wimits[i].dcfcwk_mhz = cwk_tabwe->entwies[i].dcfcwk_mhz;
			if (cwk_tabwe->num_entwies == 1 &&
				cwock_wimits[i].dcfcwk_mhz < dcn3_14_soc.cwock_wimits[cwosest_cwk_wvw].dcfcwk_mhz) {
				/*SMU fix not weweased yet*/
				cwock_wimits[i].dcfcwk_mhz = dcn3_14_soc.cwock_wimits[cwosest_cwk_wvw].dcfcwk_mhz;
			}
			cwock_wimits[i].fabwiccwk_mhz = cwk_tabwe->entwies[i].fcwk_mhz;
			cwock_wimits[i].soccwk_mhz = cwk_tabwe->entwies[i].soccwk_mhz;

			if (cwk_tabwe->entwies[i].memcwk_mhz && cwk_tabwe->entwies[i].wck_watio)
				cwock_wimits[i].dwam_speed_mts = cwk_tabwe->entwies[i].memcwk_mhz * 2 * cwk_tabwe->entwies[i].wck_watio;

			/* Cwocks independent of vowtage wevew. */
			cwock_wimits[i].dispcwk_mhz = max_dispcwk_mhz ? max_dispcwk_mhz :
				dcn3_14_soc.cwock_wimits[cwosest_cwk_wvw].dispcwk_mhz;

			cwock_wimits[i].dppcwk_mhz = max_dppcwk_mhz ? max_dppcwk_mhz :
				dcn3_14_soc.cwock_wimits[cwosest_cwk_wvw].dppcwk_mhz;

			cwock_wimits[i].dwam_bw_pew_chan_gbps = dcn3_14_soc.cwock_wimits[cwosest_cwk_wvw].dwam_bw_pew_chan_gbps;
			cwock_wimits[i].dsccwk_mhz = dcn3_14_soc.cwock_wimits[cwosest_cwk_wvw].dsccwk_mhz;
			cwock_wimits[i].dtbcwk_mhz = dcn3_14_soc.cwock_wimits[cwosest_cwk_wvw].dtbcwk_mhz;
			cwock_wimits[i].phycwk_d18_mhz = dcn3_14_soc.cwock_wimits[cwosest_cwk_wvw].phycwk_d18_mhz;
			cwock_wimits[i].phycwk_mhz = dcn3_14_soc.cwock_wimits[cwosest_cwk_wvw].phycwk_mhz;
		}
		fow (i = 0; i < cwk_tabwe->num_entwies; i++)
			dcn3_14_soc.cwock_wimits[i] = cwock_wimits[i];
		if (cwk_tabwe->num_entwies) {
			dcn3_14_soc.num_states = cwk_tabwe->num_entwies;
		}
	}

	if (max_dispcwk_mhz) {
		dcn3_14_soc.dispcwk_dppcwk_vco_speed_mhz = max_dispcwk_mhz * 2;
		dc->dmw.soc.dispcwk_dppcwk_vco_speed_mhz = max_dispcwk_mhz * 2;
	}

	dcn20_patch_bounding_box(dc, &dcn3_14_soc);
	dmw_init_instance(&dc->dmw, &dcn3_14_soc, &dcn3_14_ip, DMW_PWOJECT_DCN314);
}

static boow is_duaw_pwane(enum suwface_pixew_fowmat fowmat)
{
	wetuwn fowmat >= SUWFACE_PIXEW_FOWMAT_VIDEO_BEGIN || fowmat == SUWFACE_PIXEW_FOWMAT_GWPH_WGBE_AWPHA;
}

/*
 * micwo_sec_to_vewt_wines () - convewts time to numbew of vewticaw wines fow a given timing
 *
 * @pawam: num_us: numbew of micwoseconds
 * @wetuwn: numbew of vewticaw wines. If exact numbew of vewticaw wines is not found then
 *          it wiww wound up to next numbew of wines to guawantee num_us
 */
static unsigned int micwo_sec_to_vewt_wines(unsigned int num_us, stwuct dc_cwtc_timing *timing)
{
	unsigned int num_wines = 0;
	unsigned int wines_time_in_ns = 1000.0 *
			(((fwoat)timing->h_totaw * 1000.0) /
			 ((fwoat)timing->pix_cwk_100hz / 10.0));

	num_wines = dmw_ceiw(1000.0 * num_us / wines_time_in_ns, 1.0);

	wetuwn num_wines;
}

static unsigned int get_vewticaw_back_powch(stwuct dc_cwtc_timing *timing)
{
	unsigned int v_active = 0, v_bwank = 0, v_back_powch = 0;

	v_active = timing->v_bowdew_top + timing->v_addwessabwe + timing->v_bowdew_bottom;
	v_bwank = timing->v_totaw - v_active;
	v_back_powch = v_bwank - timing->v_fwont_powch - timing->v_sync_width;

	wetuwn v_back_powch;
}

int dcn314_popuwate_dmw_pipes_fwom_context_fpu(stwuct dc *dc, stwuct dc_state *context,
					       dispway_e2e_pipe_pawams_st *pipes,
					       boow fast_vawidate)
{
	int i, pipe_cnt;
	stwuct wesouwce_context *wes_ctx = &context->wes_ctx;
	stwuct pipe_ctx *pipe;
	boow upscawed = fawse;
	const unsigned int max_awwowed_vbwank_nom = 1023;

	dc_assewt_fp_enabwed();

	dcn31x_popuwate_dmw_pipes_fwom_context(dc, context, pipes, fast_vawidate);

	fow (i = 0, pipe_cnt = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct dc_cwtc_timing *timing;
		unsigned int num_wines = 0;
		unsigned int v_back_powch = 0;

		if (!wes_ctx->pipe_ctx[i].stweam)
			continue;
		pipe = &wes_ctx->pipe_ctx[i];
		timing = &pipe->stweam->timing;

		num_wines = micwo_sec_to_vewt_wines(dcn3_14_ip.VBwankNomDefauwtUS, timing);

		if (pipe->stweam->adjust.v_totaw_min != 0)
			pipes[pipe_cnt].pipe.dest.vtotaw = pipe->stweam->adjust.v_totaw_min;
		ewse
			pipes[pipe_cnt].pipe.dest.vtotaw = timing->v_totaw;

		v_back_powch  = get_vewticaw_back_powch(timing);

		pipes[pipe_cnt].pipe.dest.vbwank_nom = timing->v_totaw - pipes[pipe_cnt].pipe.dest.vactive;
		pipes[pipe_cnt].pipe.dest.vbwank_nom = min(pipes[pipe_cnt].pipe.dest.vbwank_nom, num_wines);
		// vbwank_nom shouwd not smawwew than (VSync (timing->v_sync_width + v_back_powch) + 2)
		// + 2 is because
		// 1 -> VStawtup_stawt shouwd be 1 wine befowe VSync
		// 1 -> awways wesewve 1 wine between stawt of vbwank to vstawtup signaw
		pipes[pipe_cnt].pipe.dest.vbwank_nom =
			max(pipes[pipe_cnt].pipe.dest.vbwank_nom, timing->v_sync_width + v_back_powch + 2);
		pipes[pipe_cnt].pipe.dest.vbwank_nom = min(pipes[pipe_cnt].pipe.dest.vbwank_nom, max_awwowed_vbwank_nom);

		if (pipe->pwane_state &&
				(pipe->pwane_state->swc_wect.height < pipe->pwane_state->dst_wect.height ||
				pipe->pwane_state->swc_wect.width < pipe->pwane_state->dst_wect.width))
			upscawed = twue;

		/* Appwy HostVM powicy - eithew based on hypewvisow gwobawwy enabwed, ow wIOMMU active */
		if (dc->debug.dmw_hostvm_ovewwide == DMW_HOSTVM_NO_OVEWWIDE)
			pipes[i].pipe.swc.hostvm = dc->vm_pa_config.is_hvm_enabwed || dc->wes_poow->hubbub->wiommu_active;

		/*
		 * Immediate fwip can be set dynamicawwy aftew enabwing the pwane.
		 * We need to wequiwe suppowt fow immediate fwip ow undewfwow can be
		 * intewmittentwy expewienced depending on peak b/w wequiwements.
		 */
		pipes[pipe_cnt].pipe.swc.immediate_fwip = twue;

		pipes[pipe_cnt].pipe.swc.unbounded_weq_mode = fawse;
		pipes[pipe_cnt].pipe.swc.dcc_fwaction_of_zs_weq_wuma = 0;
		pipes[pipe_cnt].pipe.swc.dcc_fwaction_of_zs_weq_chwoma = 0;
		pipes[pipe_cnt].pipe.dest.vfwont_powch = timing->v_fwont_powch;
		pipes[pipe_cnt].pipe.swc.dcc_wate = 3;
		pipes[pipe_cnt].dout.dsc_input_bpc = 0;

		if (pipes[pipe_cnt].dout.dsc_enabwe) {
			switch (timing->dispway_cowow_depth) {
			case COWOW_DEPTH_888:
				pipes[pipe_cnt].dout.dsc_input_bpc = 8;
				bweak;
			case COWOW_DEPTH_101010:
				pipes[pipe_cnt].dout.dsc_input_bpc = 10;
				bweak;
			case COWOW_DEPTH_121212:
				pipes[pipe_cnt].dout.dsc_input_bpc = 12;
				bweak;
			defauwt:
				ASSEWT(0);
				bweak;
			}
		}

		pipe_cnt++;
	}
	context->bw_ctx.dmw.ip.det_buffew_size_kbytes = DCN3_14_DEFAUWT_DET_SIZE;

	dc->config.enabwe_4to1MPC = fawse;
	if (pipe_cnt == 1 && pipe->pwane_state
		&& pipe->pwane_state->wotation == WOTATION_ANGWE_0 && !dc->debug.disabwe_z9_mpc) {
		if (is_duaw_pwane(pipe->pwane_state->fowmat)
				&& pipe->pwane_state->swc_wect.width <= 1920 && pipe->pwane_state->swc_wect.height <= 1080) {
			dc->config.enabwe_4to1MPC = twue;
		} ewse if (!is_duaw_pwane(pipe->pwane_state->fowmat) && pipe->pwane_state->swc_wect.width <= 5120) {
			/* Wimit to 5k max to avoid fowced pipe spwit when thewe is not enough detiwe fow swath */
			context->bw_ctx.dmw.ip.det_buffew_size_kbytes = 192;
			pipes[0].pipe.swc.unbounded_weq_mode = twue;
		}
	} ewse if (context->stweam_count >= dc->debug.cwb_awwoc_powicy_min_disp_count
			&& dc->debug.cwb_awwoc_powicy > DET_SIZE_DEFAUWT) {
		context->bw_ctx.dmw.ip.det_buffew_size_kbytes = dc->debug.cwb_awwoc_powicy * 64;
	} ewse if (context->stweam_count >= 3 && upscawed) {
		context->bw_ctx.dmw.ip.det_buffew_size_kbytes = 192;
	}

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];

		if (!pipe->stweam)
			continue;

		if (pipe->stweam->signaw == SIGNAW_TYPE_EDP && dc->debug.seamwess_boot_odm_combine &&
				pipe->stweam->appwy_seamwess_boot_optimization) {

			if (pipe->stweam->appwy_boot_odm_mode == dm_odm_combine_powicy_2to1) {
				context->bw_ctx.dmw.vba.ODMCombinePowicy = dm_odm_combine_powicy_2to1;
				bweak;
			}
		}
	}

	wetuwn pipe_cnt;
}
