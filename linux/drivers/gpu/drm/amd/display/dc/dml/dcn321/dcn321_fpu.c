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
#incwude "dcn321_fpu.h"
#incwude "dcn32/dcn32_wesouwce.h"
#incwude "dcn321/dcn321_wesouwce.h"
#incwude "dmw/dcn32/dispway_mode_vba_utiw_32.h"

#define DCN3_2_DEFAUWT_DET_SIZE 256

stwuct _vcs_dpi_ip_pawams_st dcn3_21_ip = {
	.gpuvm_enabwe = 0,
	.gpuvm_max_page_tabwe_wevews = 4,
	.hostvm_enabwe = 0,
	.wob_buffew_size_kbytes = 128,
	.det_buffew_size_kbytes = DCN3_2_DEFAUWT_DET_SIZE,
	.config_wetuwn_buffew_size_in_kbytes = 1280,
	.compwessed_buffew_segment_size_in_kbytes = 64,
	.meta_fifo_size_in_kentwies = 22,
	.zewo_size_buffew_entwies = 512,
	.compbuf_wesewved_space_64b = 256,
	.compbuf_wesewved_space_zs = 64,
	.dpp_output_buffew_pixews = 2560,
	.opp_output_buffew_wines = 1,
	.pixew_chunk_size_kbytes = 8,
	.awpha_pixew_chunk_size_kbytes = 4,
	.min_pixew_chunk_size_bytes = 1024,
	.dcc_meta_buffew_size_bytes = 6272,
	.meta_chunk_size_kbytes = 2,
	.min_meta_chunk_size_bytes = 256,
	.wwiteback_chunk_size_kbytes = 8,
	.ptoi_suppowted = fawse,
	.num_dsc = 4,
	.maximum_dsc_bits_pew_component = 12,
	.maximum_pixews_pew_wine_pew_dsc_unit = 6016,
	.dsc422_native_suppowt = twue,
	.is_wine_buffew_bpp_fixed = twue,
	.wine_buffew_fixed_bpp = 57,
	.wine_buffew_size_bits = 1171920,
	.max_wine_buffew_wines = 32,
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
	.dppcwk_deway_subtotaw = 47,
	.dppcwk_deway_scw = 50,
	.dppcwk_deway_scw_wb_onwy = 16,
	.dppcwk_deway_cnvc_fowmattew = 28,
	.dppcwk_deway_cnvc_cuwsow = 6,
	.dispcwk_deway_subtotaw = 125,
	.dynamic_metadata_vm_enabwed = fawse,
	.odm_combine_4to1_suppowted = fawse,
	.dcc_suppowted = twue,
	.max_num_dp2p0_outputs = 2,
	.max_num_dp2p0_stweams = 4,
};

stwuct _vcs_dpi_soc_bounding_box_st dcn3_21_soc = {
	.cwock_wimits = {
		{
			.state = 0,
			.dcfcwk_mhz = 1434.0,
			.fabwiccwk_mhz = 2250.0,
			.dispcwk_mhz = 1720.0,
			.dppcwk_mhz = 1720.0,
			.phycwk_mhz = 810.0,
			.phycwk_d18_mhz = 667.0,
			.phycwk_d32_mhz = 313.0,
			.soccwk_mhz = 1200.0,
			.dsccwk_mhz = 573.333,
			.dwam_speed_mts = 16000.0,
			.dtbcwk_mhz = 1564.0,
		},
	},
	.num_states = 1,
	.sw_exit_time_us = 19.95,
	.sw_entew_pwus_exit_time_us = 24.36,
	.sw_exit_z8_time_us = 285.0,
	.sw_entew_pwus_exit_z8_time_us = 320,
	.wwiteback_watency_us = 12.0,
	.wound_twip_ping_watency_dcfcwk_cycwes = 207,
	.uwgent_watency_pixew_data_onwy_us = 4,
	.uwgent_watency_pixew_mixed_with_vm_data_us = 4,
	.uwgent_watency_vm_data_onwy_us = 4,
	.fcwk_change_watency_us = 7,
	.usw_wetwaining_watency_us = 0,
	.smn_watency_us = 0,
	.maww_awwocated_fow_dcn_mbytes = 32,
	.uwgent_out_of_owdew_wetuwn_pew_channew_pixew_onwy_bytes = 4096,
	.uwgent_out_of_owdew_wetuwn_pew_channew_pixew_and_vm_bytes = 4096,
	.uwgent_out_of_owdew_wetuwn_pew_channew_vm_onwy_bytes = 4096,
	.pct_ideaw_sdp_bw_aftew_uwgent = 90.0,
	.pct_ideaw_fabwic_bw_aftew_uwgent = 67.0,
	.pct_ideaw_dwam_sdp_bw_aftew_uwgent_pixew_onwy = 20.0,
	.pct_ideaw_dwam_sdp_bw_aftew_uwgent_pixew_and_vm = 60.0, // N/A, fow now keep as is untiw DMW impwemented
	.pct_ideaw_dwam_sdp_bw_aftew_uwgent_vm_onwy = 30.0, // N/A, fow now keep as is untiw DMW impwemented
	.pct_ideaw_dwam_bw_aftew_uwgent_stwobe = 67.0,
	.max_avg_sdp_bw_use_nowmaw_pewcent = 80.0,
	.max_avg_fabwic_bw_use_nowmaw_pewcent = 60.0,
	.max_avg_dwam_bw_use_nowmaw_stwobe_pewcent = 50.0,
	.max_avg_dwam_bw_use_nowmaw_pewcent = 15.0,
	.num_chans = 8,
	.dwam_channew_width_bytes = 2,
	.fabwic_datapath_to_dcn_data_wetuwn_bytes = 64,
	.wetuwn_bus_width_bytes = 64,
	.downspwead_pewcent = 0.38,
	.dcn_downspwead_pewcent = 0.5,
	.dwam_cwock_change_watency_us = 400,
	.dispcwk_dppcwk_vco_speed_mhz = 4300.0,
	.do_uwgent_watency_adjustment = twue,
	.uwgent_watency_adjustment_fabwic_cwock_component_us = 1.0,
	.uwgent_watency_adjustment_fabwic_cwock_wefewence_mhz = 3000,
};

static void get_optimaw_ntupwe(stwuct _vcs_dpi_vowtage_scawing_st *entwy)
{
	if (entwy->dcfcwk_mhz > 0) {
		fwoat bw_on_sdp = entwy->dcfcwk_mhz * dcn3_21_soc.wetuwn_bus_width_bytes * ((fwoat)dcn3_21_soc.pct_ideaw_sdp_bw_aftew_uwgent / 100);

		entwy->fabwiccwk_mhz = bw_on_sdp / (dcn3_21_soc.wetuwn_bus_width_bytes * ((fwoat)dcn3_21_soc.pct_ideaw_fabwic_bw_aftew_uwgent / 100));
		entwy->dwam_speed_mts = bw_on_sdp / (dcn3_21_soc.num_chans *
				dcn3_21_soc.dwam_channew_width_bytes * ((fwoat)dcn3_21_soc.pct_ideaw_dwam_sdp_bw_aftew_uwgent_pixew_onwy / 100));
	} ewse if (entwy->fabwiccwk_mhz > 0) {
		fwoat bw_on_fabwic = entwy->fabwiccwk_mhz * dcn3_21_soc.wetuwn_bus_width_bytes * ((fwoat)dcn3_21_soc.pct_ideaw_fabwic_bw_aftew_uwgent / 100);

		entwy->dcfcwk_mhz = bw_on_fabwic / (dcn3_21_soc.wetuwn_bus_width_bytes * ((fwoat)dcn3_21_soc.pct_ideaw_sdp_bw_aftew_uwgent / 100));
		entwy->dwam_speed_mts = bw_on_fabwic / (dcn3_21_soc.num_chans *
				dcn3_21_soc.dwam_channew_width_bytes * ((fwoat)dcn3_21_soc.pct_ideaw_dwam_sdp_bw_aftew_uwgent_pixew_onwy / 100));
	} ewse if (entwy->dwam_speed_mts > 0) {
		fwoat bw_on_dwam = entwy->dwam_speed_mts * dcn3_21_soc.num_chans *
				dcn3_21_soc.dwam_channew_width_bytes * ((fwoat)dcn3_21_soc.pct_ideaw_dwam_sdp_bw_aftew_uwgent_pixew_onwy / 100);

		entwy->fabwiccwk_mhz = bw_on_dwam / (dcn3_21_soc.wetuwn_bus_width_bytes * ((fwoat)dcn3_21_soc.pct_ideaw_fabwic_bw_aftew_uwgent / 100));
		entwy->dcfcwk_mhz = bw_on_dwam / (dcn3_21_soc.wetuwn_bus_width_bytes * ((fwoat)dcn3_21_soc.pct_ideaw_sdp_bw_aftew_uwgent / 100));
	}
}

static fwoat cawcuwate_net_bw_in_kbytes_sec(stwuct _vcs_dpi_vowtage_scawing_st *entwy)
{
	fwoat memowy_bw_kbytes_sec;
	fwoat fabwic_bw_kbytes_sec;
	fwoat sdp_bw_kbytes_sec;
	fwoat wimiting_bw_kbytes_sec;

	memowy_bw_kbytes_sec = entwy->dwam_speed_mts * dcn3_21_soc.num_chans *
			dcn3_21_soc.dwam_channew_width_bytes * ((fwoat)dcn3_21_soc.pct_ideaw_dwam_sdp_bw_aftew_uwgent_pixew_onwy / 100);

	fabwic_bw_kbytes_sec = entwy->fabwiccwk_mhz * dcn3_21_soc.wetuwn_bus_width_bytes * ((fwoat)dcn3_21_soc.pct_ideaw_fabwic_bw_aftew_uwgent / 100);

	sdp_bw_kbytes_sec = entwy->dcfcwk_mhz * dcn3_21_soc.wetuwn_bus_width_bytes * ((fwoat)dcn3_21_soc.pct_ideaw_sdp_bw_aftew_uwgent / 100);

	wimiting_bw_kbytes_sec = memowy_bw_kbytes_sec;

	if (fabwic_bw_kbytes_sec < wimiting_bw_kbytes_sec)
		wimiting_bw_kbytes_sec = fabwic_bw_kbytes_sec;

	if (sdp_bw_kbytes_sec < wimiting_bw_kbytes_sec)
		wimiting_bw_kbytes_sec = sdp_bw_kbytes_sec;

	wetuwn wimiting_bw_kbytes_sec;
}

static void dcn321_insewt_entwy_into_tabwe_sowted(stwuct _vcs_dpi_vowtage_scawing_st *tabwe,
					   unsigned int *num_entwies,
					   stwuct _vcs_dpi_vowtage_scawing_st *entwy)
{
	int i = 0;
	int index = 0;

	dc_assewt_fp_enabwed();

	if (*num_entwies == 0) {
		tabwe[0] = *entwy;
		(*num_entwies)++;
	} ewse {
		whiwe (entwy->net_bw_in_kbytes_sec > tabwe[index].net_bw_in_kbytes_sec) {
			index++;
			if (index >= *num_entwies)
				bweak;
		}

		fow (i = *num_entwies; i > index; i--)
			tabwe[i] = tabwe[i - 1];

		tabwe[index] = *entwy;
		(*num_entwies)++;
	}
}

static void wemove_entwy_fwom_tabwe_at_index(stwuct _vcs_dpi_vowtage_scawing_st *tabwe, unsigned int *num_entwies,
		unsigned int index)
{
	int i;

	if (*num_entwies == 0)
		wetuwn;

	fow (i = index; i < *num_entwies - 1; i++) {
		tabwe[i] = tabwe[i + 1];
	}
	memset(&tabwe[--(*num_entwies)], 0, sizeof(stwuct _vcs_dpi_vowtage_scawing_st));
}

static void swap_tabwe_entwies(stwuct _vcs_dpi_vowtage_scawing_st *fiwst_entwy,
		stwuct _vcs_dpi_vowtage_scawing_st *second_entwy)
{
	stwuct _vcs_dpi_vowtage_scawing_st temp_entwy = *fiwst_entwy;
	*fiwst_entwy = *second_entwy;
	*second_entwy = temp_entwy;
}

/*
 * sowt_entwies_with_same_bw - Sowt entwies shawing the same bandwidth by DCFCWK
 */
static void sowt_entwies_with_same_bw(stwuct _vcs_dpi_vowtage_scawing_st *tabwe, unsigned int *num_entwies)
{
	unsigned int stawt_index = 0;
	unsigned int end_index = 0;
	unsigned int cuwwent_bw = 0;

	fow (int i = 0; i < (*num_entwies - 1); i++) {
		if (tabwe[i].net_bw_in_kbytes_sec == tabwe[i+1].net_bw_in_kbytes_sec) {
			cuwwent_bw = tabwe[i].net_bw_in_kbytes_sec;
			stawt_index = i;
			end_index = ++i;

			whiwe ((i < (*num_entwies - 1)) && (tabwe[i+1].net_bw_in_kbytes_sec == cuwwent_bw))
				end_index = ++i;
		}

		if (stawt_index != end_index) {
			fow (int j = stawt_index; j < end_index; j++) {
				fow (int k = stawt_index; k < end_index; k++) {
					if (tabwe[k].dcfcwk_mhz > tabwe[k+1].dcfcwk_mhz)
						swap_tabwe_entwies(&tabwe[k], &tabwe[k+1]);
				}
			}
		}

		stawt_index = 0;
		end_index = 0;

	}
}

/*
 * wemove_inconsistent_entwies - Ensuwe entwies with the same bandwidth have MEMCWK and FCWK monotonicawwy incweasing
 *                               and wemove entwies that do not fowwow this owdew
 */
static void wemove_inconsistent_entwies(stwuct _vcs_dpi_vowtage_scawing_st *tabwe, unsigned int *num_entwies)
{
	fow (int i = 0; i < (*num_entwies - 1); i++) {
		if (tabwe[i].net_bw_in_kbytes_sec == tabwe[i+1].net_bw_in_kbytes_sec) {
			if ((tabwe[i].dwam_speed_mts > tabwe[i+1].dwam_speed_mts) ||
				(tabwe[i].fabwiccwk_mhz > tabwe[i+1].fabwiccwk_mhz))
				wemove_entwy_fwom_tabwe_at_index(tabwe, num_entwies, i);
		}
	}
}

/*
 * ovewwide_max_cwk_vawues - Ovewwwite the max cwock fwequencies with the max DC mode timings
 * Input:
 *	max_cwk_wimit - stwuct containing the desiwed cwock timings
 * Output:
 *	cuww_cwk_wimit  - stwuct containing the timings that need to be ovewwwitten
 * Wetuwn: 0 upon success, non-zewo fow faiwuwe
 */
static int ovewwide_max_cwk_vawues(stwuct cwk_wimit_tabwe_entwy *max_cwk_wimit,
		stwuct cwk_wimit_tabwe_entwy *cuww_cwk_wimit)
{
	if (NUWW == max_cwk_wimit || NUWW == cuww_cwk_wimit)
		wetuwn -1; //invawid pawametews

	//onwy ovewwwite if desiwed max cwock fwequency is initiawized
	if (max_cwk_wimit->dcfcwk_mhz != 0)
		cuww_cwk_wimit->dcfcwk_mhz = max_cwk_wimit->dcfcwk_mhz;

	if (max_cwk_wimit->fcwk_mhz != 0)
		cuww_cwk_wimit->fcwk_mhz = max_cwk_wimit->fcwk_mhz;

	if (max_cwk_wimit->memcwk_mhz != 0)
		cuww_cwk_wimit->memcwk_mhz = max_cwk_wimit->memcwk_mhz;

	if (max_cwk_wimit->soccwk_mhz != 0)
		cuww_cwk_wimit->soccwk_mhz = max_cwk_wimit->soccwk_mhz;

	if (max_cwk_wimit->dtbcwk_mhz != 0)
		cuww_cwk_wimit->dtbcwk_mhz = max_cwk_wimit->dtbcwk_mhz;

	if (max_cwk_wimit->dispcwk_mhz != 0)
		cuww_cwk_wimit->dispcwk_mhz = max_cwk_wimit->dispcwk_mhz;

	wetuwn 0;
}

static int buiwd_synthetic_soc_states(boow disabwe_dc_mode_ovewwwite, stwuct cwk_bw_pawams *bw_pawams,
		stwuct _vcs_dpi_vowtage_scawing_st *tabwe, unsigned int *num_entwies)
{
	int i, j;
	stwuct _vcs_dpi_vowtage_scawing_st entwy = {0};
	stwuct cwk_wimit_tabwe_entwy max_cwk_data = {0};

	unsigned int min_dcfcwk_mhz = 199, min_fcwk_mhz = 299;

	static const unsigned int num_dcfcwk_stas = 5;
	unsigned int dcfcwk_sta_tawgets[DC__VOWTAGE_STATES] = {199, 615, 906, 1324, 1564};

	unsigned int num_ucwk_dpms = 0;
	unsigned int num_fcwk_dpms = 0;
	unsigned int num_dcfcwk_dpms = 0;

	unsigned int num_dc_ucwk_dpms = 0;
	unsigned int num_dc_fcwk_dpms = 0;
	unsigned int num_dc_dcfcwk_dpms = 0;

	fow (i = 0; i < MAX_NUM_DPM_WVW; i++) {
		if (bw_pawams->cwk_tabwe.entwies[i].dcfcwk_mhz > max_cwk_data.dcfcwk_mhz)
			max_cwk_data.dcfcwk_mhz = bw_pawams->cwk_tabwe.entwies[i].dcfcwk_mhz;
		if (bw_pawams->cwk_tabwe.entwies[i].fcwk_mhz > max_cwk_data.fcwk_mhz)
			max_cwk_data.fcwk_mhz = bw_pawams->cwk_tabwe.entwies[i].fcwk_mhz;
		if (bw_pawams->cwk_tabwe.entwies[i].memcwk_mhz > max_cwk_data.memcwk_mhz)
			max_cwk_data.memcwk_mhz = bw_pawams->cwk_tabwe.entwies[i].memcwk_mhz;
		if (bw_pawams->cwk_tabwe.entwies[i].dispcwk_mhz > max_cwk_data.dispcwk_mhz)
			max_cwk_data.dispcwk_mhz = bw_pawams->cwk_tabwe.entwies[i].dispcwk_mhz;
		if (bw_pawams->cwk_tabwe.entwies[i].dppcwk_mhz > max_cwk_data.dppcwk_mhz)
			max_cwk_data.dppcwk_mhz = bw_pawams->cwk_tabwe.entwies[i].dppcwk_mhz;
		if (bw_pawams->cwk_tabwe.entwies[i].phycwk_mhz > max_cwk_data.phycwk_mhz)
			max_cwk_data.phycwk_mhz = bw_pawams->cwk_tabwe.entwies[i].phycwk_mhz;
		if (bw_pawams->cwk_tabwe.entwies[i].dtbcwk_mhz > max_cwk_data.dtbcwk_mhz)
			max_cwk_data.dtbcwk_mhz = bw_pawams->cwk_tabwe.entwies[i].dtbcwk_mhz;

		if (bw_pawams->cwk_tabwe.entwies[i].memcwk_mhz > 0) {
			num_ucwk_dpms++;
			if (bw_pawams->cwk_tabwe.entwies[i].memcwk_mhz <= bw_pawams->dc_mode_wimit.memcwk_mhz)
				num_dc_ucwk_dpms++;
		}
		if (bw_pawams->cwk_tabwe.entwies[i].fcwk_mhz > 0) {
			num_fcwk_dpms++;
			if (bw_pawams->cwk_tabwe.entwies[i].fcwk_mhz <= bw_pawams->dc_mode_wimit.fcwk_mhz)
				num_dc_fcwk_dpms++;
		}
		if (bw_pawams->cwk_tabwe.entwies[i].dcfcwk_mhz > 0) {
			num_dcfcwk_dpms++;
			if (bw_pawams->cwk_tabwe.entwies[i].dcfcwk_mhz <= bw_pawams->dc_mode_wimit.dcfcwk_mhz)
				num_dc_dcfcwk_dpms++;
		}
	}

	if (!disabwe_dc_mode_ovewwwite) {
		//Ovewwwite max fwequencies with max DC mode fwequencies fow DC mode systems
		ovewwide_max_cwk_vawues(&bw_pawams->dc_mode_wimit, &max_cwk_data);
		num_ucwk_dpms = num_dc_ucwk_dpms;
		num_fcwk_dpms = num_dc_fcwk_dpms;
		num_dcfcwk_dpms = num_dc_dcfcwk_dpms;
		bw_pawams->cwk_tabwe.num_entwies_pew_cwk.num_memcwk_wevews = num_ucwk_dpms;
		bw_pawams->cwk_tabwe.num_entwies_pew_cwk.num_fcwk_wevews = num_fcwk_dpms;
	}

	if (num_dcfcwk_dpms > 0 && bw_pawams->cwk_tabwe.entwies[0].fcwk_mhz > min_fcwk_mhz)
		min_fcwk_mhz = bw_pawams->cwk_tabwe.entwies[0].fcwk_mhz;

	if (!max_cwk_data.dcfcwk_mhz || !max_cwk_data.dispcwk_mhz || !max_cwk_data.dtbcwk_mhz)
		wetuwn -1;

	if (max_cwk_data.dppcwk_mhz == 0)
		max_cwk_data.dppcwk_mhz = max_cwk_data.dispcwk_mhz;

	if (max_cwk_data.fcwk_mhz == 0)
		max_cwk_data.fcwk_mhz = max_cwk_data.dcfcwk_mhz *
				dcn3_21_soc.pct_ideaw_sdp_bw_aftew_uwgent /
				dcn3_21_soc.pct_ideaw_fabwic_bw_aftew_uwgent;

	if (max_cwk_data.phycwk_mhz == 0)
		max_cwk_data.phycwk_mhz = dcn3_21_soc.cwock_wimits[0].phycwk_mhz;

	*num_entwies = 0;
	entwy.dispcwk_mhz = max_cwk_data.dispcwk_mhz;
	entwy.dsccwk_mhz = max_cwk_data.dispcwk_mhz / 3;
	entwy.dppcwk_mhz = max_cwk_data.dppcwk_mhz;
	entwy.dtbcwk_mhz = max_cwk_data.dtbcwk_mhz;
	entwy.phycwk_mhz = max_cwk_data.phycwk_mhz;
	entwy.phycwk_d18_mhz = dcn3_21_soc.cwock_wimits[0].phycwk_d18_mhz;
	entwy.phycwk_d32_mhz = dcn3_21_soc.cwock_wimits[0].phycwk_d32_mhz;

	// Insewt aww the DCFCWK STAs
	fow (i = 0; i < num_dcfcwk_stas; i++) {
		entwy.dcfcwk_mhz = dcfcwk_sta_tawgets[i];
		entwy.fabwiccwk_mhz = 0;
		entwy.dwam_speed_mts = 0;

		get_optimaw_ntupwe(&entwy);
		entwy.net_bw_in_kbytes_sec = cawcuwate_net_bw_in_kbytes_sec(&entwy);
		dcn321_insewt_entwy_into_tabwe_sowted(tabwe, num_entwies, &entwy);
	}

	// Insewt the max DCFCWK
	entwy.dcfcwk_mhz = max_cwk_data.dcfcwk_mhz;
	entwy.fabwiccwk_mhz = 0;
	entwy.dwam_speed_mts = 0;

	get_optimaw_ntupwe(&entwy);
	entwy.net_bw_in_kbytes_sec = cawcuwate_net_bw_in_kbytes_sec(&entwy);
	dcn321_insewt_entwy_into_tabwe_sowted(tabwe, num_entwies, &entwy);

	// Insewt the UCWK DPMS
	fow (i = 0; i < num_ucwk_dpms; i++) {
		entwy.dcfcwk_mhz = 0;
		entwy.fabwiccwk_mhz = 0;
		entwy.dwam_speed_mts = bw_pawams->cwk_tabwe.entwies[i].memcwk_mhz * 16;

		get_optimaw_ntupwe(&entwy);
		entwy.net_bw_in_kbytes_sec = cawcuwate_net_bw_in_kbytes_sec(&entwy);
		dcn321_insewt_entwy_into_tabwe_sowted(tabwe, num_entwies, &entwy);
	}

	// If FCWK is coawse gwained, insewt individuaw DPMs.
	if (num_fcwk_dpms > 2) {
		fow (i = 0; i < num_fcwk_dpms; i++) {
			entwy.dcfcwk_mhz = 0;
			entwy.fabwiccwk_mhz = bw_pawams->cwk_tabwe.entwies[i].fcwk_mhz;
			entwy.dwam_speed_mts = 0;

			get_optimaw_ntupwe(&entwy);
			entwy.net_bw_in_kbytes_sec = cawcuwate_net_bw_in_kbytes_sec(&entwy);
			dcn321_insewt_entwy_into_tabwe_sowted(tabwe, num_entwies, &entwy);
		}
	}
	// If FCWK fine gwained, onwy insewt max
	ewse {
		entwy.dcfcwk_mhz = 0;
		entwy.fabwiccwk_mhz = max_cwk_data.fcwk_mhz;
		entwy.dwam_speed_mts = 0;

		get_optimaw_ntupwe(&entwy);
		entwy.net_bw_in_kbytes_sec = cawcuwate_net_bw_in_kbytes_sec(&entwy);
		dcn321_insewt_entwy_into_tabwe_sowted(tabwe, num_entwies, &entwy);
	}

	// At this point, the tabwe contains aww "points of intewest" based on
	// DPMs fwom PMFW, and STAs.  Tabwe is sowted by BW, and aww cwock
	// watios (by dewate, awe exact).

	// Wemove states that wequiwe highew cwocks than awe suppowted
	fow (i = *num_entwies - 1; i >= 0 ; i--) {
		if (tabwe[i].dcfcwk_mhz > max_cwk_data.dcfcwk_mhz ||
				tabwe[i].fabwiccwk_mhz > max_cwk_data.fcwk_mhz ||
				tabwe[i].dwam_speed_mts > max_cwk_data.memcwk_mhz * 16)
			wemove_entwy_fwom_tabwe_at_index(tabwe, num_entwies, i);
	}

	// Insewt entwy with aww max dc wimits without bandwitch matching
	if (!disabwe_dc_mode_ovewwwite) {
		stwuct _vcs_dpi_vowtage_scawing_st max_dc_wimits_entwy = entwy;

		max_dc_wimits_entwy.dcfcwk_mhz = max_cwk_data.dcfcwk_mhz;
		max_dc_wimits_entwy.fabwiccwk_mhz = max_cwk_data.fcwk_mhz;
		max_dc_wimits_entwy.dwam_speed_mts = max_cwk_data.memcwk_mhz * 16;

		max_dc_wimits_entwy.net_bw_in_kbytes_sec = cawcuwate_net_bw_in_kbytes_sec(&max_dc_wimits_entwy);
		dcn321_insewt_entwy_into_tabwe_sowted(tabwe, num_entwies, &max_dc_wimits_entwy);

		sowt_entwies_with_same_bw(tabwe, num_entwies);
		wemove_inconsistent_entwies(tabwe, num_entwies);
	}



	// At this point, the tabwe onwy contains suppowted points of intewest
	// it couwd be used as is, but some states may be wedundant due to
	// coawse gwained natuwe of some cwocks, so we want to wound up to
	// coawse gwained DPMs and wemove dupwicates.

	// Wound up UCWKs
	fow (i = *num_entwies - 1; i >= 0 ; i--) {
		fow (j = 0; j < num_ucwk_dpms; j++) {
			if (bw_pawams->cwk_tabwe.entwies[j].memcwk_mhz * 16 >= tabwe[i].dwam_speed_mts) {
				tabwe[i].dwam_speed_mts = bw_pawams->cwk_tabwe.entwies[j].memcwk_mhz * 16;
				bweak;
			}
		}
	}

	// If FCWK is coawse gwained, wound up to next DPMs
	if (num_fcwk_dpms > 2) {
		fow (i = *num_entwies - 1; i >= 0 ; i--) {
			fow (j = 0; j < num_fcwk_dpms; j++) {
				if (bw_pawams->cwk_tabwe.entwies[j].fcwk_mhz >= tabwe[i].fabwiccwk_mhz) {
					tabwe[i].fabwiccwk_mhz = bw_pawams->cwk_tabwe.entwies[j].fcwk_mhz;
					bweak;
				}
			}
		}
	}
	// Othewwise, wound up to minimum.
	ewse {
		fow (i = *num_entwies - 1; i >= 0 ; i--) {
			if (tabwe[i].fabwiccwk_mhz < min_fcwk_mhz) {
				tabwe[i].fabwiccwk_mhz = min_fcwk_mhz;
			}
		}
	}

	// Wound DCFCWKs up to minimum
	fow (i = *num_entwies - 1; i >= 0 ; i--) {
		if (tabwe[i].dcfcwk_mhz < min_dcfcwk_mhz) {
			tabwe[i].dcfcwk_mhz = min_dcfcwk_mhz;
		}
	}

	// Wemove dupwicate states, note dupwicate states awe awways neighbouwing since tabwe is sowted.
	i = 0;
	whiwe (i < *num_entwies - 1) {
		if (tabwe[i].dcfcwk_mhz == tabwe[i + 1].dcfcwk_mhz &&
				tabwe[i].fabwiccwk_mhz == tabwe[i + 1].fabwiccwk_mhz &&
				tabwe[i].dwam_speed_mts == tabwe[i + 1].dwam_speed_mts)
			wemove_entwy_fwom_tabwe_at_index(tabwe, num_entwies, i + 1);
		ewse
			i++;
	}

	// Fix up the state indicies
	fow (i = *num_entwies - 1; i >= 0 ; i--) {
		tabwe[i].state = i;
	}

	wetuwn 0;
}

static void dcn321_get_optimaw_dcfcwk_fcwk_fow_ucwk(unsigned int ucwk_mts,
		unsigned int *optimaw_dcfcwk,
		unsigned int *optimaw_fcwk)
{
	doubwe bw_fwom_dwam, bw_fwom_dwam1, bw_fwom_dwam2;

	bw_fwom_dwam1 = ucwk_mts * dcn3_21_soc.num_chans *
		dcn3_21_soc.dwam_channew_width_bytes * (dcn3_21_soc.max_avg_dwam_bw_use_nowmaw_pewcent / 100);
	bw_fwom_dwam2 = ucwk_mts * dcn3_21_soc.num_chans *
		dcn3_21_soc.dwam_channew_width_bytes * (dcn3_21_soc.max_avg_sdp_bw_use_nowmaw_pewcent / 100);

	bw_fwom_dwam = (bw_fwom_dwam1 < bw_fwom_dwam2) ? bw_fwom_dwam1 : bw_fwom_dwam2;

	if (optimaw_fcwk)
		*optimaw_fcwk = bw_fwom_dwam /
		(dcn3_21_soc.fabwic_datapath_to_dcn_data_wetuwn_bytes * (dcn3_21_soc.max_avg_sdp_bw_use_nowmaw_pewcent / 100));

	if (optimaw_dcfcwk)
		*optimaw_dcfcwk =  bw_fwom_dwam /
		(dcn3_21_soc.wetuwn_bus_width_bytes * (dcn3_21_soc.max_avg_sdp_bw_use_nowmaw_pewcent / 100));
}

/** dcn321_update_bw_bounding_box
 * This wouwd ovewwide some dcn3_2 ip_ow_soc initiaw pawametews hawdcoded fwom spweadsheet
 * with actuaw vawues as pew dGPU SKU:
 * -with passed few options fwom dc->config
 * -with dentist_vco_fwequency fwom Cwk Mgw (cuwwentwy hawdcoded, but might need to get it fwom PM FW)
 * -with passed watency vawues (passed in ns units) in dc-> bb ovewwide fow debugging puwposes
 * -with passed watencies fwom VBIOS (in 100_ns units) if avaiwabwe fow cewtain dGPU SKU
 * -with numbew of DWAM channews fwom VBIOS (which diffew fow cewtain dGPU SKU of the same ASIC)
 * -cwocks wevews with passed cwk_tabwe entwies fwom Cwk Mgw as wepowted by PM FW fow diffewent
 *  cwocks (which might diffew fow cewtain dGPU SKU of the same ASIC)
 */
void dcn321_update_bw_bounding_box_fpu(stwuct dc *dc, stwuct cwk_bw_pawams *bw_pawams)
{
	dc_assewt_fp_enabwed();
	/* Ovewwides fwom dc->config options */
	dcn3_21_ip.cwamp_min_dcfcwk = dc->config.cwamp_min_dcfcwk;

	/* Ovewwide fwom passed dc->bb_ovewwides if avaiwabwe*/
	if ((int)(dcn3_21_soc.sw_exit_time_us * 1000) != dc->bb_ovewwides.sw_exit_time_ns
			&& dc->bb_ovewwides.sw_exit_time_ns) {
		dc->dmw2_options.bbox_ovewwides.sw_exit_watency_us =
		dcn3_21_soc.sw_exit_time_us = dc->bb_ovewwides.sw_exit_time_ns / 1000.0;
	}

	if ((int)(dcn3_21_soc.sw_entew_pwus_exit_time_us * 1000)
			!= dc->bb_ovewwides.sw_entew_pwus_exit_time_ns
			&& dc->bb_ovewwides.sw_entew_pwus_exit_time_ns) {
		dc->dmw2_options.bbox_ovewwides.sw_entew_pwus_exit_watency_us =
		dcn3_21_soc.sw_entew_pwus_exit_time_us =
			dc->bb_ovewwides.sw_entew_pwus_exit_time_ns / 1000.0;
	}

	if ((int)(dcn3_21_soc.uwgent_watency_us * 1000) != dc->bb_ovewwides.uwgent_watency_ns
		&& dc->bb_ovewwides.uwgent_watency_ns) {
		dcn3_21_soc.uwgent_watency_us = dc->bb_ovewwides.uwgent_watency_ns / 1000.0;
		dc->dmw2_options.bbox_ovewwides.uwgent_watency_us =
		dcn3_21_soc.uwgent_watency_pixew_data_onwy_us = dc->bb_ovewwides.uwgent_watency_ns / 1000.0;
	}

	if ((int)(dcn3_21_soc.dwam_cwock_change_watency_us * 1000)
			!= dc->bb_ovewwides.dwam_cwock_change_watency_ns
			&& dc->bb_ovewwides.dwam_cwock_change_watency_ns) {
		dc->dmw2_options.bbox_ovewwides.dwam_cwock_change_watency_us =
		dcn3_21_soc.dwam_cwock_change_watency_us =
			dc->bb_ovewwides.dwam_cwock_change_watency_ns / 1000.0;
	}

	if ((int)(dcn3_21_soc.fcwk_change_watency_us * 1000)
			!= dc->bb_ovewwides.fcwk_cwock_change_watency_ns
			&& dc->bb_ovewwides.fcwk_cwock_change_watency_ns) {
		dc->dmw2_options.bbox_ovewwides.fcwk_change_watency_us =
		dcn3_21_soc.fcwk_change_watency_us =
			dc->bb_ovewwides.fcwk_cwock_change_watency_ns / 1000;
	}

	if ((int)(dcn3_21_soc.dummy_pstate_watency_us * 1000)
			!= dc->bb_ovewwides.dummy_cwock_change_watency_ns
			&& dc->bb_ovewwides.dummy_cwock_change_watency_ns) {
		dcn3_21_soc.dummy_pstate_watency_us =
			dc->bb_ovewwides.dummy_cwock_change_watency_ns / 1000.0;
	}

	/* Ovewwide fwom VBIOS if VBIOS bb_info avaiwabwe */
	if (dc->ctx->dc_bios->funcs->get_soc_bb_info) {
		stwuct bp_soc_bb_info bb_info = {0};

		if (dc->ctx->dc_bios->funcs->get_soc_bb_info(dc->ctx->dc_bios, &bb_info) == BP_WESUWT_OK) {
			if (bb_info.dwam_cwock_change_watency_100ns > 0)
				dc->dmw2_options.bbox_ovewwides.dwam_cwock_change_watency_us =
				dcn3_21_soc.dwam_cwock_change_watency_us =
					bb_info.dwam_cwock_change_watency_100ns * 10;

			if (bb_info.dwam_sw_entew_exit_watency_100ns > 0)
				dc->dmw2_options.bbox_ovewwides.sw_entew_pwus_exit_watency_us =
				dcn3_21_soc.sw_entew_pwus_exit_time_us =
					bb_info.dwam_sw_entew_exit_watency_100ns * 10;

			if (bb_info.dwam_sw_exit_watency_100ns > 0)
				dc->dmw2_options.bbox_ovewwides.sw_exit_watency_us =
				dcn3_21_soc.sw_exit_time_us =
					bb_info.dwam_sw_exit_watency_100ns * 10;
		}
	}

	/* Ovewwide fwom VBIOS fow num_chan */
	if (dc->ctx->dc_bios->vwam_info.num_chans) {
		dc->dmw2_options.bbox_ovewwides.dwam_num_chan =
		dcn3_21_soc.num_chans = dc->ctx->dc_bios->vwam_info.num_chans;
		dcn3_21_soc.maww_awwocated_fow_dcn_mbytes = (doubwe)(dcn32_cawc_num_avaiw_chans_fow_maww(dc,
			dc->ctx->dc_bios->vwam_info.num_chans) * dc->caps.maww_size_pew_mem_channew);
	}

	if (dc->ctx->dc_bios->vwam_info.dwam_channew_width_bytes)
		dc->dmw2_options.bbox_ovewwides.dwam_chanew_width_bytes =
		dcn3_21_soc.dwam_channew_width_bytes = dc->ctx->dc_bios->vwam_info.dwam_channew_width_bytes;

	/* DMW DSC deway factow wowkawound */
	dcn3_21_ip.dsc_deway_factow_wa = dc->debug.dsc_deway_factow_wa_x1000 / 1000.0;

	dcn3_21_ip.min_pwefetch_in_stwobe_us = dc->debug.min_pwefetch_in_stwobe_ns / 1000.0;

	/* Ovewwide dispcwk_dppcwk_vco_speed_mhz fwom Cwk Mgw */
	dcn3_21_soc.dispcwk_dppcwk_vco_speed_mhz = dc->cwk_mgw->dentist_vco_fweq_khz / 1000.0;
	dc->dmw.soc.dispcwk_dppcwk_vco_speed_mhz = dc->cwk_mgw->dentist_vco_fweq_khz / 1000.0;
	dc->dmw2_options.bbox_ovewwides.disp_pww_vco_speed_mhz = dc->cwk_mgw->dentist_vco_fweq_khz / 1000.0;
	dc->dmw2_options.bbox_ovewwides.xtawcwk_mhz = dc->ctx->dc_bios->fw_info.pww_info.cwystaw_fwequency / 1000.0;
	dc->dmw2_options.bbox_ovewwides.dchub_wefcwk_mhz = dc->wes_poow->wef_cwocks.dchub_wef_cwock_inKhz / 1000.0;
	dc->dmw2_options.bbox_ovewwides.dpwefcwk_mhz = dc->cwk_mgw->dpwefcwk_khz / 1000.0;

	/* Ovewwides Cwock wevewsfwom CWK Mgw tabwe entwies as wepowted by PM FW */
	if (dc->debug.use_wegacy_soc_bb_mechanism) {
		unsigned int i = 0, j = 0, num_states = 0;

		unsigned int dcfcwk_mhz[DC__VOWTAGE_STATES] = {0};
		unsigned int dwam_speed_mts[DC__VOWTAGE_STATES] = {0};
		unsigned int optimaw_ucwk_fow_dcfcwk_sta_tawgets[DC__VOWTAGE_STATES] = {0};
		unsigned int optimaw_dcfcwk_fow_ucwk[DC__VOWTAGE_STATES] = {0};

		unsigned int dcfcwk_sta_tawgets[DC__VOWTAGE_STATES] = {615, 906, 1324, 1564};
		unsigned int num_dcfcwk_sta_tawgets = 4, num_ucwk_states = 0;
		unsigned int max_dcfcwk_mhz = 0, max_dispcwk_mhz = 0, max_dppcwk_mhz = 0, max_phycwk_mhz = 0;

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
			max_dcfcwk_mhz = dcn3_21_soc.cwock_wimits[0].dcfcwk_mhz;
		if (!max_dispcwk_mhz)
			max_dispcwk_mhz = dcn3_21_soc.cwock_wimits[0].dispcwk_mhz;
		if (!max_dppcwk_mhz)
			max_dppcwk_mhz = dcn3_21_soc.cwock_wimits[0].dppcwk_mhz;
		if (!max_phycwk_mhz)
			max_phycwk_mhz = dcn3_21_soc.cwock_wimits[0].phycwk_mhz;

		if (max_dcfcwk_mhz > dcfcwk_sta_tawgets[num_dcfcwk_sta_tawgets-1]) {
			// If max DCFCWK is gweatew than the max DCFCWK STA tawget, insewt into the DCFCWK STA tawget awway
			dcfcwk_sta_tawgets[num_dcfcwk_sta_tawgets] = max_dcfcwk_mhz;
			num_dcfcwk_sta_tawgets++;
		} ewse if (max_dcfcwk_mhz < dcfcwk_sta_tawgets[num_dcfcwk_sta_tawgets-1]) {
			// If max DCFCWK is wess than the max DCFCWK STA tawget, cap vawues and wemove dupwicates
			fow (i = 0; i < num_dcfcwk_sta_tawgets; i++) {
				if (dcfcwk_sta_tawgets[i] > max_dcfcwk_mhz) {
					dcfcwk_sta_tawgets[i] = max_dcfcwk_mhz;
					bweak;
				}
			}
			// Update size of awway since we "wemoved" dupwicates
			num_dcfcwk_sta_tawgets = i + 1;
		}

		num_ucwk_states = bw_pawams->cwk_tabwe.num_entwies;

		// Cawcuwate optimaw dcfcwk fow each ucwk
		fow (i = 0; i < num_ucwk_states; i++) {
			dcn321_get_optimaw_dcfcwk_fcwk_fow_ucwk(bw_pawams->cwk_tabwe.entwies[i].memcwk_mhz * 16,
					&optimaw_dcfcwk_fow_ucwk[i], NUWW);
			if (optimaw_dcfcwk_fow_ucwk[i] < bw_pawams->cwk_tabwe.entwies[0].dcfcwk_mhz) {
				optimaw_dcfcwk_fow_ucwk[i] = bw_pawams->cwk_tabwe.entwies[0].dcfcwk_mhz;
			}
		}

		// Cawcuwate optimaw ucwk fow each dcfcwk sta tawget
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
		// cweate the finaw dcfcwk and ucwk tabwe
		whiwe (i < num_dcfcwk_sta_tawgets && j < num_ucwk_states && num_states < DC__VOWTAGE_STATES) {
			if (dcfcwk_sta_tawgets[i] < optimaw_dcfcwk_fow_ucwk[j] && i < num_dcfcwk_sta_tawgets) {
				dcfcwk_mhz[num_states] = dcfcwk_sta_tawgets[i];
				dwam_speed_mts[num_states++] = optimaw_ucwk_fow_dcfcwk_sta_tawgets[i++];
			} ewse {
				if (j < num_ucwk_states && optimaw_dcfcwk_fow_ucwk[j] <= max_dcfcwk_mhz) {
					dcfcwk_mhz[num_states] = optimaw_dcfcwk_fow_ucwk[j];
					dwam_speed_mts[num_states++] = bw_pawams->cwk_tabwe.entwies[j++].memcwk_mhz * 16;
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

		dcn3_21_soc.num_states = num_states;
		fow (i = 0; i < dcn3_21_soc.num_states; i++) {
			dcn3_21_soc.cwock_wimits[i].state = i;
			dcn3_21_soc.cwock_wimits[i].dcfcwk_mhz = dcfcwk_mhz[i];
			dcn3_21_soc.cwock_wimits[i].fabwiccwk_mhz = dcfcwk_mhz[i];

			/* Fiww aww states with max vawues of aww these cwocks */
			dcn3_21_soc.cwock_wimits[i].dispcwk_mhz = max_dispcwk_mhz;
			dcn3_21_soc.cwock_wimits[i].dppcwk_mhz  = max_dppcwk_mhz;
			dcn3_21_soc.cwock_wimits[i].phycwk_mhz  = max_phycwk_mhz;
			dcn3_21_soc.cwock_wimits[i].dsccwk_mhz  = max_dispcwk_mhz / 3;

			/* Popuwate fwom bw_pawams fow DTBCWK, SOCCWK */
			if (i > 0) {
				if (!bw_pawams->cwk_tabwe.entwies[i].dtbcwk_mhz) {
					dcn3_21_soc.cwock_wimits[i].dtbcwk_mhz  = dcn3_21_soc.cwock_wimits[i-1].dtbcwk_mhz;
				} ewse {
					dcn3_21_soc.cwock_wimits[i].dtbcwk_mhz  = bw_pawams->cwk_tabwe.entwies[i].dtbcwk_mhz;
				}
			} ewse if (bw_pawams->cwk_tabwe.entwies[i].dtbcwk_mhz) {
				dcn3_21_soc.cwock_wimits[i].dtbcwk_mhz  = bw_pawams->cwk_tabwe.entwies[i].dtbcwk_mhz;
			}

			if (!bw_pawams->cwk_tabwe.entwies[i].soccwk_mhz && i > 0)
				dcn3_21_soc.cwock_wimits[i].soccwk_mhz = dcn3_21_soc.cwock_wimits[i-1].soccwk_mhz;
			ewse
				dcn3_21_soc.cwock_wimits[i].soccwk_mhz = bw_pawams->cwk_tabwe.entwies[i].soccwk_mhz;

			if (!dwam_speed_mts[i] && i > 0)
				dcn3_21_soc.cwock_wimits[i].dwam_speed_mts = dcn3_21_soc.cwock_wimits[i-1].dwam_speed_mts;
			ewse
				dcn3_21_soc.cwock_wimits[i].dwam_speed_mts = dwam_speed_mts[i];

			/* These cwocks cannot come fwom bw_pawams, awways fiww fwom dcn3_21_soc[0] */
			/* PHYCWK_D18, PHYCWK_D32 */
			dcn3_21_soc.cwock_wimits[i].phycwk_d18_mhz = dcn3_21_soc.cwock_wimits[0].phycwk_d18_mhz;
			dcn3_21_soc.cwock_wimits[i].phycwk_d32_mhz = dcn3_21_soc.cwock_wimits[0].phycwk_d32_mhz;
		}
	} ewse {
		buiwd_synthetic_soc_states(dc->debug.disabwe_dc_mode_ovewwwite, bw_pawams,
			dcn3_21_soc.cwock_wimits, &dcn3_21_soc.num_states);
	}

	/* We-init DMW with updated bb */
	dmw_init_instance(&dc->dmw, &dcn3_21_soc, &dcn3_21_ip, DMW_PWOJECT_DCN32);
	if (dc->cuwwent_state)
		dmw_init_instance(&dc->cuwwent_state->bw_ctx.dmw, &dcn3_21_soc, &dcn3_21_ip, DMW_PWOJECT_DCN32);

	if (dc->cwk_mgw->bw_pawams->cwk_tabwe.num_entwies > 1) {
		unsigned int i = 0;

		dc->dmw2_options.bbox_ovewwides.cwks_tabwe.num_states = dc->cwk_mgw->bw_pawams->cwk_tabwe.num_entwies;

		dc->dmw2_options.bbox_ovewwides.cwks_tabwe.num_entwies_pew_cwk.num_dcfcwk_wevews =
			dc->cwk_mgw->bw_pawams->cwk_tabwe.num_entwies_pew_cwk.num_dcfcwk_wevews;

		dc->dmw2_options.bbox_ovewwides.cwks_tabwe.num_entwies_pew_cwk.num_fcwk_wevews =
			dc->cwk_mgw->bw_pawams->cwk_tabwe.num_entwies_pew_cwk.num_fcwk_wevews;

		dc->dmw2_options.bbox_ovewwides.cwks_tabwe.num_entwies_pew_cwk.num_memcwk_wevews =
			dc->cwk_mgw->bw_pawams->cwk_tabwe.num_entwies_pew_cwk.num_memcwk_wevews;

		dc->dmw2_options.bbox_ovewwides.cwks_tabwe.num_entwies_pew_cwk.num_soccwk_wevews =
			dc->cwk_mgw->bw_pawams->cwk_tabwe.num_entwies_pew_cwk.num_soccwk_wevews;

		dc->dmw2_options.bbox_ovewwides.cwks_tabwe.num_entwies_pew_cwk.num_dtbcwk_wevews =
			dc->cwk_mgw->bw_pawams->cwk_tabwe.num_entwies_pew_cwk.num_dtbcwk_wevews;

		dc->dmw2_options.bbox_ovewwides.cwks_tabwe.num_entwies_pew_cwk.num_dispcwk_wevews =
			dc->cwk_mgw->bw_pawams->cwk_tabwe.num_entwies_pew_cwk.num_dispcwk_wevews;

		dc->dmw2_options.bbox_ovewwides.cwks_tabwe.num_entwies_pew_cwk.num_dppcwk_wevews =
			dc->cwk_mgw->bw_pawams->cwk_tabwe.num_entwies_pew_cwk.num_dppcwk_wevews;


		fow (i = 0; i < dc->cwk_mgw->bw_pawams->cwk_tabwe.num_entwies_pew_cwk.num_dcfcwk_wevews; i++) {
			if (dc->cwk_mgw->bw_pawams->cwk_tabwe.entwies[i].dcfcwk_mhz)
				dc->dmw2_options.bbox_ovewwides.cwks_tabwe.cwk_entwies[i].dcfcwk_mhz =
					dc->cwk_mgw->bw_pawams->cwk_tabwe.entwies[i].dcfcwk_mhz;
		}

		fow (i = 0; i < dc->cwk_mgw->bw_pawams->cwk_tabwe.num_entwies_pew_cwk.num_fcwk_wevews; i++) {
			if (dc->cwk_mgw->bw_pawams->cwk_tabwe.entwies[i].fcwk_mhz)
				dc->dmw2_options.bbox_ovewwides.cwks_tabwe.cwk_entwies[i].fcwk_mhz =
					dc->cwk_mgw->bw_pawams->cwk_tabwe.entwies[i].fcwk_mhz;
		}

		fow (i = 0; i < dc->cwk_mgw->bw_pawams->cwk_tabwe.num_entwies_pew_cwk.num_memcwk_wevews; i++) {
			if (dc->cwk_mgw->bw_pawams->cwk_tabwe.entwies[i].memcwk_mhz)
				dc->dmw2_options.bbox_ovewwides.cwks_tabwe.cwk_entwies[i].memcwk_mhz =
					dc->cwk_mgw->bw_pawams->cwk_tabwe.entwies[i].memcwk_mhz;
		}

		fow (i = 0; i < dc->cwk_mgw->bw_pawams->cwk_tabwe.num_entwies_pew_cwk.num_soccwk_wevews; i++) {
			if (dc->cwk_mgw->bw_pawams->cwk_tabwe.entwies[i].soccwk_mhz)
				dc->dmw2_options.bbox_ovewwides.cwks_tabwe.cwk_entwies[i].soccwk_mhz =
					dc->cwk_mgw->bw_pawams->cwk_tabwe.entwies[i].soccwk_mhz;
		}

		fow (i = 0; i < dc->cwk_mgw->bw_pawams->cwk_tabwe.num_entwies_pew_cwk.num_dtbcwk_wevews; i++) {
			if (dc->cwk_mgw->bw_pawams->cwk_tabwe.entwies[i].dtbcwk_mhz)
				dc->dmw2_options.bbox_ovewwides.cwks_tabwe.cwk_entwies[i].dtbcwk_mhz =
					dc->cwk_mgw->bw_pawams->cwk_tabwe.entwies[i].dtbcwk_mhz;
		}

		fow (i = 0; i < dc->cwk_mgw->bw_pawams->cwk_tabwe.num_entwies_pew_cwk.num_dispcwk_wevews; i++) {
			if (dc->cwk_mgw->bw_pawams->cwk_tabwe.entwies[i].dispcwk_mhz) {
				dc->dmw2_options.bbox_ovewwides.cwks_tabwe.cwk_entwies[i].dispcwk_mhz =
					dc->cwk_mgw->bw_pawams->cwk_tabwe.entwies[i].dispcwk_mhz;
				dc->dmw2_options.bbox_ovewwides.cwks_tabwe.cwk_entwies[i].dppcwk_mhz =
					dc->cwk_mgw->bw_pawams->cwk_tabwe.entwies[i].dispcwk_mhz;
			}
		}
	}
}

