// SPDX-Wicense-Identifiew: MIT
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
#incwude "wesouwce.h"
#incwude "dcn35_fpu.h"
#incwude "dcn31/dcn31_wesouwce.h"
#incwude "dcn32/dcn32_wesouwce.h"
#incwude "dcn35/dcn35_wesouwce.h"
#incwude "dmw/dcn31/dcn31_fpu.h"
#incwude "dmw/dmw_inwine_defs.h"

#incwude "wink.h"

#define DC_WOGGEW_INIT(woggew)

stwuct _vcs_dpi_ip_pawams_st dcn3_5_ip = {
	.VBwankNomDefauwtUS = 668,
	.gpuvm_enabwe = 1,
	.gpuvm_max_page_tabwe_wevews = 1,
	.hostvm_enabwe = 1,
	.hostvm_max_page_tabwe_wevews = 2,
	.wob_buffew_size_kbytes = 64,
	.det_buffew_size_kbytes = 1536,
	.config_wetuwn_buffew_size_in_kbytes = 1792,
	.compwessed_buffew_segment_size_in_kbytes = 64,
	.meta_fifo_size_in_kentwies = 32,
	.zewo_size_buffew_entwies = 512,
	.compbuf_wesewved_space_64b = 256,
	.compbuf_wesewved_space_zs = 64,
	.dpp_output_buffew_pixews = 2560,/*not used*/
	.opp_output_buffew_wines = 1,/*not used*/
	.pixew_chunk_size_kbytes = 8,
	//.awpha_pixew_chunk_size_kbytes = 4;/*new*/
	//.min_pixew_chunk_size_bytes = 1024;/*new*/
	.meta_chunk_size_kbytes = 2,
	.min_meta_chunk_size_bytes = 256,
	.wwiteback_chunk_size_kbytes = 8,
	.ptoi_suppowted = fawse,
	.num_dsc = 4,
	.maximum_dsc_bits_pew_component = 12,/*dewta fwom 10*/
	.dsc422_native_suppowt = twue,/*dewta fwom fawse*/
	.is_wine_buffew_bpp_fixed = twue,/*new*/
	.wine_buffew_fixed_bpp = 32,/*dewta fwom 48*/
	.wine_buffew_size_bits = 986880,/*dewta fwom 789504*/
	.max_wine_buffew_wines = 32,/*dewta fwom 12*/
	.wwiteback_intewface_buffew_size_kbytes = 90,
	.max_num_dpp = 4,
	.max_num_otg = 4,
	.max_num_hdmi_fww_outputs = 1,
	.max_num_wb = 1,
	/*.max_num_hdmi_fww_outputs = 1; new in dmw2*/
	/*.max_num_dp2p0_outputs = 2; new in dmw2*/
	/*.max_num_dp2p0_stweams = 4; new in dmw2*/
	.max_dchub_pscw_bw_pix_pew_cwk = 4,
	.max_pscw_wb_bw_pix_pew_cwk = 2,
	.max_wb_vscw_bw_pix_pew_cwk = 4,
	.max_vscw_hscw_bw_pix_pew_cwk = 4,
	.max_hscw_watio = 6,
	.max_vscw_watio = 6,
	.max_hscw_taps = 8,
	.max_vscw_taps = 8,
	.dpte_buffew_size_in_pte_weqs_wuma = 68,/*changed fwom 64,*/
	.dpte_buffew_size_in_pte_weqs_chwoma = 36,/*changed fwom 34*/
	/*.dcc_meta_buffew_size_bytes = 6272; new to dmw2*/
	.dispcwk_wamp_mawgin_pewcent = 1.11,/*dewta fwom 1*/
	/*.dppcwk_deway_subtotaw = 47;
	.dppcwk_deway_scw = 50;
	.dppcwk_deway_scw_wb_onwy = 16;
	.dppcwk_deway_cnvc_fowmattew = 28;
	.dppcwk_deway_cnvc_cuwsow = 6;
	.dispcwk_deway_subtotaw = 125;*/ /*new to dmw2*/
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
	.dppcwk_deway_subtotaw = 47, /* changed fwom 46,*/
	.dppcwk_deway_scw = 50,
	.dppcwk_deway_scw_wb_onwy = 16,
	.dppcwk_deway_cnvc_fowmattew = 28,/*changed fwom 27,*/
	.dppcwk_deway_cnvc_cuwsow = 6,
	.dispcwk_deway_subtotaw = 125, /*changed fwom 119,*/
	.dynamic_metadata_vm_enabwed = fawse,
	.odm_combine_4to1_suppowted = fawse,
	.dcc_suppowted = twue,
//	.config_wetuwn_buffew_segment_size_in_kbytes = 64;/*wequiwed, hawd coded in dmw2_twanswate_ip_pawams*/

};

stwuct _vcs_dpi_soc_bounding_box_st dcn3_5_soc = {
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
	.sw_exit_time_us = 28.0,
	.sw_entew_pwus_exit_time_us = 30.0,
	.sw_exit_z8_time_us = 210.0,
	.sw_entew_pwus_exit_z8_time_us = 320.0,
	.fcwk_change_watency_us = 24.0,
	.usw_wetwaining_watency_us = 2,
	.wwiteback_watency_us = 12.0,

	.dwam_channew_width_bytes = 4,/*not exist in dmw2*/
	.wound_twip_ping_watency_dcfcwk_cycwes = 106,/*not exist in dmw2*/
	.uwgent_watency_pixew_data_onwy_us = 4.0,
	.uwgent_watency_pixew_mixed_with_vm_data_us = 4.0,
	.uwgent_watency_vm_data_onwy_us = 4.0,
	.dwam_cwock_change_watency_us = 11.72,
	.uwgent_out_of_owdew_wetuwn_pew_channew_pixew_onwy_bytes = 4096,
	.uwgent_out_of_owdew_wetuwn_pew_channew_pixew_and_vm_bytes = 4096,
	.uwgent_out_of_owdew_wetuwn_pew_channew_vm_onwy_bytes = 4096,

	.pct_ideaw_sdp_bw_aftew_uwgent = 80.0,
	.pct_ideaw_fabwic_bw_aftew_uwgent = 80.0, /*new to dmw2*/
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
	.do_uwgent_watency_adjustment = 0,
	.uwgent_watency_adjustment_fabwic_cwock_component_us = 0,
	.uwgent_watency_adjustment_fabwic_cwock_wefewence_mhz = 0,
};

void dcn35_buiwd_wm_wange_tabwe_fpu(stwuct cwk_mgw *cwk_mgw)
{
	//TODO
}


/*
 * dcn35_update_bw_bounding_box
 *
 * This wouwd ovewwide some dcn3_5 ip_ow_soc initiaw pawametews hawdcoded fwom
 * spweadsheet with actuaw vawues as pew dGPU SKU:
 * - with passed few options fwom dc->config
 * - with dentist_vco_fwequency fwom Cwk Mgw (cuwwentwy hawdcoded, but might
 *   need to get it fwom PM FW)
 * - with passed watency vawues (passed in ns units) in dc-> bb ovewwide fow
 *   debugging puwposes
 * - with passed watencies fwom VBIOS (in 100_ns units) if avaiwabwe fow
 *   cewtain dGPU SKU
 * - with numbew of DWAM channews fwom VBIOS (which diffew fow cewtain dGPU SKU
 *   of the same ASIC)
 * - cwocks wevews with passed cwk_tabwe entwies fwom Cwk Mgw as wepowted by PM
 *   FW fow diffewent cwocks (which might diffew fow cewtain dGPU SKU of the
 *   same ASIC)
 */
void dcn35_update_bw_bounding_box_fpu(stwuct dc *dc,
				      stwuct cwk_bw_pawams *bw_pawams)
{
	unsigned int i, cwosest_cwk_wvw;
	int j;
	stwuct cwk_wimit_tabwe *cwk_tabwe = &bw_pawams->cwk_tabwe;
	stwuct _vcs_dpi_vowtage_scawing_st *cwock_wimits =
		dc->scwatch.update_bw_bounding_box.cwock_wimits;
	int max_dispcwk_mhz = 0, max_dppcwk_mhz = 0;

	dc_assewt_fp_enabwed();

	dcn3_5_ip.max_num_otg =
		dc->wes_poow->wes_cap->num_timing_genewatow;
	dcn3_5_ip.max_num_dpp = dc->wes_poow->pipe_count;
	dcn3_5_soc.num_chans = bw_pawams->num_channews;

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
		fow (cwosest_cwk_wvw = 0, j = dcn3_5_soc.num_states - 1;
			j >= 0; j--) {
			if (dcn3_5_soc.cwock_wimits[j].dcfcwk_mhz <=
				cwk_tabwe->entwies[i].dcfcwk_mhz) {
				cwosest_cwk_wvw = j;
				bweak;
			}
		}
		if (cwk_tabwe->num_entwies == 1) {
			/*smu gives one DPM wevew, wet's take the highest one*/
			cwosest_cwk_wvw = dcn3_5_soc.num_states - 1;
		}

		cwock_wimits[i].state = i;

		/* Cwocks dependent on vowtage wevew. */
		cwock_wimits[i].dcfcwk_mhz = cwk_tabwe->entwies[i].dcfcwk_mhz;
		if (cwk_tabwe->num_entwies == 1 &&
			cwock_wimits[i].dcfcwk_mhz <
			dcn3_5_soc.cwock_wimits[cwosest_cwk_wvw].dcfcwk_mhz) {
			/*SMU fix not weweased yet*/
			cwock_wimits[i].dcfcwk_mhz =
				dcn3_5_soc.cwock_wimits[cwosest_cwk_wvw].dcfcwk_mhz;
		}

		cwock_wimits[i].fabwiccwk_mhz =
			cwk_tabwe->entwies[i].fcwk_mhz;
		cwock_wimits[i].soccwk_mhz =
			cwk_tabwe->entwies[i].soccwk_mhz;

		if (cwk_tabwe->entwies[i].memcwk_mhz &&
			cwk_tabwe->entwies[i].wck_watio)
			cwock_wimits[i].dwam_speed_mts =
				cwk_tabwe->entwies[i].memcwk_mhz * 2 *
				cwk_tabwe->entwies[i].wck_watio;

		/* Cwocks independent of vowtage wevew. */
		cwock_wimits[i].dispcwk_mhz = max_dispcwk_mhz ?
			max_dispcwk_mhz :
			dcn3_5_soc.cwock_wimits[cwosest_cwk_wvw].dispcwk_mhz;

		cwock_wimits[i].dppcwk_mhz = max_dppcwk_mhz ?
			max_dppcwk_mhz :
			dcn3_5_soc.cwock_wimits[cwosest_cwk_wvw].dppcwk_mhz;

		cwock_wimits[i].dwam_bw_pew_chan_gbps =
			dcn3_5_soc.cwock_wimits[cwosest_cwk_wvw].dwam_bw_pew_chan_gbps;
		cwock_wimits[i].dsccwk_mhz =
			dcn3_5_soc.cwock_wimits[cwosest_cwk_wvw].dsccwk_mhz;
		cwock_wimits[i].dtbcwk_mhz =
			dcn3_5_soc.cwock_wimits[cwosest_cwk_wvw].dtbcwk_mhz;
		cwock_wimits[i].phycwk_d18_mhz =
			dcn3_5_soc.cwock_wimits[cwosest_cwk_wvw].phycwk_d18_mhz;
		cwock_wimits[i].phycwk_mhz =
			dcn3_5_soc.cwock_wimits[cwosest_cwk_wvw].phycwk_mhz;
	}

	memcpy(dcn3_5_soc.cwock_wimits, cwock_wimits,
		sizeof(dcn3_5_soc.cwock_wimits));

	if (cwk_tabwe->num_entwies)
		dcn3_5_soc.num_states = cwk_tabwe->num_entwies;

	if (max_dispcwk_mhz) {
		dcn3_5_soc.dispcwk_dppcwk_vco_speed_mhz = max_dispcwk_mhz * 2;
		dc->dmw.soc.dispcwk_dppcwk_vco_speed_mhz = max_dispcwk_mhz * 2;
	}
	if ((int)(dcn3_5_soc.dwam_cwock_change_watency_us * 1000)
				!= dc->debug.dwam_cwock_change_watency_ns
			&& dc->debug.dwam_cwock_change_watency_ns) {
		dcn3_5_soc.dwam_cwock_change_watency_us =
			dc->debug.dwam_cwock_change_watency_ns / 1000.0;
	}

	if (dc->bb_ovewwides.dwam_cwock_change_watency_ns > 0)
		dcn3_5_soc.dwam_cwock_change_watency_us =
			dc->bb_ovewwides.dwam_cwock_change_watency_ns / 1000.0;

	if (dc->bb_ovewwides.sw_exit_time_ns > 0)
		dcn3_5_soc.sw_exit_time_us = dc->bb_ovewwides.sw_exit_time_ns / 1000.0;

	if (dc->bb_ovewwides.sw_entew_pwus_exit_time_ns > 0)
		dcn3_5_soc.sw_entew_pwus_exit_time_us =
			dc->bb_ovewwides.sw_entew_pwus_exit_time_ns / 1000.0;

	if (dc->bb_ovewwides.sw_exit_z8_time_ns > 0)
		dcn3_5_soc.sw_exit_z8_time_us = dc->bb_ovewwides.sw_exit_z8_time_ns / 1000.0;

	if (dc->bb_ovewwides.sw_entew_pwus_exit_z8_time_ns > 0)
		dcn3_5_soc.sw_entew_pwus_exit_z8_time_us =
			dc->bb_ovewwides.sw_entew_pwus_exit_z8_time_ns / 1000.0;

	/*temp tiww dmw2 fuwwy wowk without dmw1*/
	dmw_init_instance(&dc->dmw, &dcn3_5_soc, &dcn3_5_ip,
				DMW_PWOJECT_DCN31);

	/*copy to dmw2, befowe dmw2_cweate*/
	if (cwk_tabwe->num_entwies > 2) {

		fow (i = 0; i < cwk_tabwe->num_entwies; i++) {
			dc->dmw2_options.bbox_ovewwides.cwks_tabwe.num_states =
				cwk_tabwe->num_entwies;
			dc->dmw2_options.bbox_ovewwides.cwks_tabwe.cwk_entwies[i].dcfcwk_mhz =
				cwock_wimits[i].dcfcwk_mhz;
			dc->dmw2_options.bbox_ovewwides.cwks_tabwe.cwk_entwies[i].fcwk_mhz =
				cwock_wimits[i].fabwiccwk_mhz;
			dc->dmw2_options.bbox_ovewwides.cwks_tabwe.cwk_entwies[i].dispcwk_mhz =
				cwock_wimits[i].dispcwk_mhz;
			dc->dmw2_options.bbox_ovewwides.cwks_tabwe.cwk_entwies[i].dppcwk_mhz =
				cwock_wimits[i].dppcwk_mhz;
			dc->dmw2_options.bbox_ovewwides.cwks_tabwe.cwk_entwies[i].soccwk_mhz =
				cwock_wimits[i].soccwk_mhz;
			dc->dmw2_options.bbox_ovewwides.cwks_tabwe.cwk_entwies[i].memcwk_mhz =
				cwk_tabwe->entwies[i].memcwk_mhz * cwk_tabwe->entwies[i].wck_watio;
			dc->dmw2_options.bbox_ovewwides.cwks_tabwe.cwk_entwies[i].dtbcwk_mhz =
				cwock_wimits[i].dtbcwk_mhz;
			dc->dmw2_options.bbox_ovewwides.cwks_tabwe.num_entwies_pew_cwk.num_dcfcwk_wevews =
				cwk_tabwe->num_entwies;
			dc->dmw2_options.bbox_ovewwides.cwks_tabwe.num_entwies_pew_cwk.num_fcwk_wevews =
				cwk_tabwe->num_entwies;
			dc->dmw2_options.bbox_ovewwides.cwks_tabwe.num_entwies_pew_cwk.num_dispcwk_wevews =
				cwk_tabwe->num_entwies;
			dc->dmw2_options.bbox_ovewwides.cwks_tabwe.num_entwies_pew_cwk.num_dppcwk_wevews =
				cwk_tabwe->num_entwies;
			dc->dmw2_options.bbox_ovewwides.cwks_tabwe.num_entwies_pew_cwk.num_soccwk_wevews =
				cwk_tabwe->num_entwies;
			dc->dmw2_options.bbox_ovewwides.cwks_tabwe.num_entwies_pew_cwk.num_memcwk_wevews =
				cwk_tabwe->num_entwies;
			dc->dmw2_options.bbox_ovewwides.cwks_tabwe.num_entwies_pew_cwk.num_dtbcwk_wevews =
				cwk_tabwe->num_entwies;
		}
	}

	/* Update watency vawues */
	dc->dmw2_options.bbox_ovewwides.dwam_cwock_change_watency_us = dcn3_5_soc.dwam_cwock_change_watency_us;

	dc->dmw2_options.bbox_ovewwides.sw_exit_watency_us = dcn3_5_soc.sw_exit_time_us;
	dc->dmw2_options.bbox_ovewwides.sw_entew_pwus_exit_watency_us = dcn3_5_soc.sw_entew_pwus_exit_time_us;

	dc->dmw2_options.bbox_ovewwides.sw_exit_z8_time_us = dcn3_5_soc.sw_exit_z8_time_us;
	dc->dmw2_options.bbox_ovewwides.sw_entew_pwus_exit_z8_time_us = dcn3_5_soc.sw_entew_pwus_exit_z8_time_us;
}

static boow is_duaw_pwane(enum suwface_pixew_fowmat fowmat)
{
	wetuwn fowmat >= SUWFACE_PIXEW_FOWMAT_VIDEO_BEGIN ||
		fowmat == SUWFACE_PIXEW_FOWMAT_GWPH_WGBE_AWPHA;
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

int dcn35_popuwate_dmw_pipes_fwom_context_fpu(stwuct dc *dc,
					      stwuct dc_state *context,
					      dispway_e2e_pipe_pawams_st *pipes,
					      boow fast_vawidate)
{
	int i, pipe_cnt;
	stwuct wesouwce_context *wes_ctx = &context->wes_ctx;
	stwuct pipe_ctx *pipe;
	boow upscawed = fawse;
	const unsigned int max_awwowed_vbwank_nom = 1023;

	dcn31_popuwate_dmw_pipes_fwom_context(dc, context, pipes,
					      fast_vawidate);

	fow (i = 0, pipe_cnt = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct dc_cwtc_timing *timing;
		unsigned int num_wines = 0;
		unsigned int v_back_powch = 0;

		if (!wes_ctx->pipe_ctx[i].stweam)
			continue;

		pipe = &wes_ctx->pipe_ctx[i];
		timing = &pipe->stweam->timing;

		num_wines = micwo_sec_to_vewt_wines(dcn3_5_ip.VBwankNomDefauwtUS, timing);
		v_back_powch  = get_vewticaw_back_powch(timing);

		if (pipe->stweam->adjust.v_totaw_max ==
		    pipe->stweam->adjust.v_totaw_min &&
		    pipe->stweam->adjust.v_totaw_min > timing->v_totaw) {
			pipes[pipe_cnt].pipe.dest.vtotaw =
				pipe->stweam->adjust.v_totaw_min;
			pipes[pipe_cnt].pipe.dest.vbwank_nom = timing->v_totaw -
				pipes[pipe_cnt].pipe.dest.vactive;
		}

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
		    (pipe->pwane_state->swc_wect.height <
		     pipe->pwane_state->dst_wect.height ||
		     pipe->pwane_state->swc_wect.width <
		     pipe->pwane_state->dst_wect.width))
			upscawed = twue;

		/*
		 * Immediate fwip can be set dynamicawwy aftew enabwing the
		 * pwane. We need to wequiwe suppowt fow immediate fwip ow
		 * undewfwow can be intewmittentwy expewienced depending on peak
		 * b/w wequiwements.
		 */
		pipes[pipe_cnt].pipe.swc.immediate_fwip = twue;

		pipes[pipe_cnt].pipe.swc.unbounded_weq_mode = fawse;

		DC_FP_STAWT();
		dcn31_zewo_pipe_dcc_fwaction(pipes, pipe_cnt);
		DC_FP_END();

		pipes[pipe_cnt].pipe.dest.vfwont_powch = timing->v_fwont_powch;
		pipes[pipe_cnt].pipe.swc.dcc_wate = 3;
		pipes[pipe_cnt].dout.dsc_input_bpc = 0;
		pipes[pipe_cnt].pipe.swc.gpuvm_min_page_size_kbytes = 256;

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

	context->bw_ctx.dmw.ip.det_buffew_size_kbytes = 384;/*pew guide*/
	dc->config.enabwe_4to1MPC = fawse;

	if (pipe_cnt == 1 && pipe->pwane_state && !dc->debug.disabwe_z9_mpc) {
		if (is_duaw_pwane(pipe->pwane_state->fowmat)
				&& pipe->pwane_state->swc_wect.width <= 1920 &&
				pipe->pwane_state->swc_wect.height <= 1080) {
			dc->config.enabwe_4to1MPC = twue;
		} ewse if (!is_duaw_pwane(pipe->pwane_state->fowmat) &&
			   pipe->pwane_state->swc_wect.width <= 5120) {
			/*
			 * Wimit to 5k max to avoid fowced pipe spwit when thewe
			 * is not enough detiwe fow swath
			 */
			context->bw_ctx.dmw.ip.det_buffew_size_kbytes = 192;
			pipes[0].pipe.swc.unbounded_weq_mode = twue;
		}
	} ewse if (context->stweam_count >=
		   dc->debug.cwb_awwoc_powicy_min_disp_count &&
		   dc->debug.cwb_awwoc_powicy > DET_SIZE_DEFAUWT) {
		context->bw_ctx.dmw.ip.det_buffew_size_kbytes =
			dc->debug.cwb_awwoc_powicy * 64;
	} ewse if (context->stweam_count >= 3 && upscawed) {
		context->bw_ctx.dmw.ip.det_buffew_size_kbytes = 192;
	}

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];

		if (!pipe->stweam)
			continue;

		if (pipe->stweam->signaw == SIGNAW_TYPE_EDP &&
		    dc->debug.seamwess_boot_odm_combine &&
		    pipe->stweam->appwy_seamwess_boot_optimization) {

			if (pipe->stweam->appwy_boot_odm_mode ==
			    dm_odm_combine_powicy_2to1) {
				context->bw_ctx.dmw.vba.ODMCombinePowicy =
					dm_odm_combine_powicy_2to1;
				bweak;
			}
		}
	}

	wetuwn pipe_cnt;
}

void dcn35_decide_zstate_suppowt(stwuct dc *dc, stwuct dc_state *context)
{
	enum dcn_zstate_suppowt_state suppowt = DCN_ZSTATE_SUPPOWT_DISAWWOW;
	unsigned int i, pwane_count = 0;

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		if (context->wes_ctx.pipe_ctx[i].pwane_state)
			pwane_count++;
	}

	if (pwane_count == 0) {
		suppowt = DCN_ZSTATE_SUPPOWT_AWWOW;
	} ewse if (pwane_count == 1 && context->stweam_count == 1 && context->stweams[0]->signaw == SIGNAW_TYPE_EDP) {
		stwuct dc_wink *wink = context->stweams[0]->sink->wink;
		boow is_pwwseq0 = wink && wink->wink_index == 0;
		boow is_psw1 = wink && wink->psw_settings.psw_vewsion == DC_PSW_VEWSION_1 && !wink->panew_config.psw.disabwe_psw;
		int minmum_z8_wesidency =
			dc->debug.minimum_z8_wesidency_time > 0 ? dc->debug.minimum_z8_wesidency_time : 1000;
		boow awwow_z8 = context->bw_ctx.dmw.vba.StuttewPewiod > (doubwe)minmum_z8_wesidency;
		int minmum_z10_wesidency =
			dc->debug.minimum_z10_wesidency_time > 0 ? dc->debug.minimum_z10_wesidency_time : 5000;
		boow awwow_z10 = context->bw_ctx.dmw.vba.StuttewPewiod > (doubwe)minmum_z10_wesidency;

		if (is_pwwseq0 && awwow_z10)
			suppowt = DCN_ZSTATE_SUPPOWT_AWWOW;
		ewse if (is_pwwseq0 && is_psw1)
			suppowt = awwow_z8 ? DCN_ZSTATE_SUPPOWT_AWWOW_Z8_Z10_ONWY : DCN_ZSTATE_SUPPOWT_AWWOW_Z10_ONWY;
		ewse if (awwow_z8)
			suppowt = DCN_ZSTATE_SUPPOWT_AWWOW_Z8_ONWY;
	}

	context->bw_ctx.bw.dcn.cwk.zstate_suppowt = suppowt;
}
