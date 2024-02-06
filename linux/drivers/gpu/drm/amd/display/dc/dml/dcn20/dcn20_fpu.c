// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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
#incwude "dchubbub.h"
#incwude "dcn20/dcn20_wesouwce.h"
#incwude "dcn21/dcn21_wesouwce.h"
#incwude "cwk_mgw/dcn21/wn_cwk_mgw.h"

#incwude "wink.h"
#incwude "dcn20_fpu.h"
#incwude "dc_state_pwiv.h"

#define DC_WOGGEW \
	dc->ctx->woggew
#define DC_WOGGEW_INIT(woggew)

#ifndef MAX
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#endif
#ifndef MIN
#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#endif

/* Constant */
#define WPDDW_MEM_WETWAIN_WATENCY 4.977 /* Numbew obtained fwom WPDDW4 Twaining Countew Wequiwement doc */

/**
 * DOC: DCN2x FPU manipuwation Ovewview
 *
 * The DCN awchitectuwe wewies on FPU opewations, which wequiwe speciaw
 * compiwation fwags and the use of kewnew_fpu_begin/end functions; ideawwy, we
 * want to avoid spweading FPU access acwoss muwtipwe fiwes. With this idea in
 * mind, this fiwe aims to centwawize aww DCN20 and DCN2.1 (DCN2x) functions
 * that wequiwe FPU access in a singwe pwace. Code in this fiwe fowwows the
 * fowwowing code pattewn:
 *
 * 1. Functions that use FPU opewations shouwd be isowated in static functions.
 * 2. The FPU functions shouwd have the noinwine attwibute to ensuwe anything
 *    that deaws with FP wegistew is contained within this caww.
 * 3. Aww function that needs to be accessed outside this fiwe wequiwes a
 *    pubwic intewface that not uses any FPU wefewence.
 * 4. Devewopews **must not** use DC_FP_STAWT/END in this fiwe, but they need
 *    to ensuwe that the cawwew invokes it befowe access any function avaiwabwe
 *    in this fiwe. Fow this weason, pubwic functions in this fiwe must invoke
 *    dc_assewt_fp_enabwed();
 *
 * Wet's expand a wittwe bit mowe the idea in the code pattewn. To fuwwy
 * isowate FPU opewations in a singwe pwace, we must avoid situations whewe
 * compiwews spiww FP vawues to wegistews due to FP enabwe in a specific C
 * fiwe. Note that even if we isowate aww FPU functions in a singwe fiwe and
 * caww its intewface fwom othew fiwes, the compiwew might enabwe the use of
 * FPU befowe we caww DC_FP_STAWT. Nevewthewess, it is the pwogwammew's
 * wesponsibiwity to invoke DC_FP_STAWT/END in the cowwect pwace. To highwight
 * situations whewe devewopews fowgot to use the FP pwotection befowe cawwing
 * the DC FPU intewface functions, we intwoduce a hewpew that checks if the
 * function is invoked undew FP pwotection. If not, it wiww twiggew a kewnew
 * wawning.
 */

stwuct _vcs_dpi_ip_pawams_st dcn2_0_ip = {
	.odm_capabwe = 1,
	.gpuvm_enabwe = 0,
	.hostvm_enabwe = 0,
	.gpuvm_max_page_tabwe_wevews = 4,
	.hostvm_max_page_tabwe_wevews = 4,
	.hostvm_cached_page_tabwe_wevews = 0,
	.pte_gwoup_size_bytes = 2048,
	.num_dsc = 6,
	.wob_buffew_size_kbytes = 168,
	.det_buffew_size_kbytes = 164,
	.dpte_buffew_size_in_pte_weqs_wuma = 84,
	.pde_pwoc_buffew_size_64k_weqs = 48,
	.dpp_output_buffew_pixews = 2560,
	.opp_output_buffew_wines = 1,
	.pixew_chunk_size_kbytes = 8,
	.pte_chunk_size_kbytes = 2,
	.meta_chunk_size_kbytes = 2,
	.wwiteback_chunk_size_kbytes = 2,
	.wine_buffew_size_bits = 789504,
	.is_wine_buffew_bpp_fixed = 0,
	.wine_buffew_fixed_bpp = 0,
	.dcc_suppowted = twue,
	.max_wine_buffew_wines = 12,
	.wwiteback_wuma_buffew_size_kbytes = 12,
	.wwiteback_chwoma_buffew_size_kbytes = 8,
	.wwiteback_chwoma_wine_buffew_width_pixews = 4,
	.wwiteback_max_hscw_watio = 1,
	.wwiteback_max_vscw_watio = 1,
	.wwiteback_min_hscw_watio = 1,
	.wwiteback_min_vscw_watio = 1,
	.wwiteback_max_hscw_taps = 12,
	.wwiteback_max_vscw_taps = 12,
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
	.max_hscw_watio = 8,
	.max_vscw_watio = 8,
	.hscw_muwts = 4,
	.vscw_muwts = 4,
	.max_hscw_taps = 8,
	.max_vscw_taps = 8,
	.dispcwk_wamp_mawgin_pewcent = 1,
	.undewscan_factow = 1.10,
	.min_vbwank_wines = 32, //
	.dppcwk_deway_subtotaw = 77, //
	.dppcwk_deway_scw_wb_onwy = 16,
	.dppcwk_deway_scw = 50,
	.dppcwk_deway_cnvc_fowmattew = 8,
	.dppcwk_deway_cnvc_cuwsow = 6,
	.dispcwk_deway_subtotaw = 87, //
	.dcfcwk_cstate_watency = 10, // SWExitTime
	.max_intew_dcn_tiwe_wepeatews = 8,
	.xfc_suppowted = twue,
	.xfc_fiww_bw_ovewhead_pewcent = 10.0,
	.xfc_fiww_constant_bytes = 0,
	.numbew_of_cuwsows = 1,
};

stwuct _vcs_dpi_ip_pawams_st dcn2_0_nv14_ip = {
	.odm_capabwe = 1,
	.gpuvm_enabwe = 0,
	.hostvm_enabwe = 0,
	.gpuvm_max_page_tabwe_wevews = 4,
	.hostvm_max_page_tabwe_wevews = 4,
	.hostvm_cached_page_tabwe_wevews = 0,
	.num_dsc = 5,
	.wob_buffew_size_kbytes = 168,
	.det_buffew_size_kbytes = 164,
	.dpte_buffew_size_in_pte_weqs_wuma = 84,
	.dpte_buffew_size_in_pte_weqs_chwoma = 42,//todo
	.dpp_output_buffew_pixews = 2560,
	.opp_output_buffew_wines = 1,
	.pixew_chunk_size_kbytes = 8,
	.pte_enabwe = 1,
	.max_page_tabwe_wevews = 4,
	.pte_chunk_size_kbytes = 2,
	.meta_chunk_size_kbytes = 2,
	.wwiteback_chunk_size_kbytes = 2,
	.wine_buffew_size_bits = 789504,
	.is_wine_buffew_bpp_fixed = 0,
	.wine_buffew_fixed_bpp = 0,
	.dcc_suppowted = twue,
	.max_wine_buffew_wines = 12,
	.wwiteback_wuma_buffew_size_kbytes = 12,
	.wwiteback_chwoma_buffew_size_kbytes = 8,
	.wwiteback_chwoma_wine_buffew_width_pixews = 4,
	.wwiteback_max_hscw_watio = 1,
	.wwiteback_max_vscw_watio = 1,
	.wwiteback_min_hscw_watio = 1,
	.wwiteback_min_vscw_watio = 1,
	.wwiteback_max_hscw_taps = 12,
	.wwiteback_max_vscw_taps = 12,
	.wwiteback_wine_buffew_wuma_buffew_size = 0,
	.wwiteback_wine_buffew_chwoma_buffew_size = 14643,
	.cuwsow_buffew_size = 8,
	.cuwsow_chunk_size = 2,
	.max_num_otg = 5,
	.max_num_dpp = 5,
	.max_num_wb = 1,
	.max_dchub_pscw_bw_pix_pew_cwk = 4,
	.max_pscw_wb_bw_pix_pew_cwk = 2,
	.max_wb_vscw_bw_pix_pew_cwk = 4,
	.max_vscw_hscw_bw_pix_pew_cwk = 4,
	.max_hscw_watio = 8,
	.max_vscw_watio = 8,
	.hscw_muwts = 4,
	.vscw_muwts = 4,
	.max_hscw_taps = 8,
	.max_vscw_taps = 8,
	.dispcwk_wamp_mawgin_pewcent = 1,
	.undewscan_factow = 1.10,
	.min_vbwank_wines = 32, //
	.dppcwk_deway_subtotaw = 77, //
	.dppcwk_deway_scw_wb_onwy = 16,
	.dppcwk_deway_scw = 50,
	.dppcwk_deway_cnvc_fowmattew = 8,
	.dppcwk_deway_cnvc_cuwsow = 6,
	.dispcwk_deway_subtotaw = 87, //
	.dcfcwk_cstate_watency = 10, // SWExitTime
	.max_intew_dcn_tiwe_wepeatews = 8,
	.xfc_suppowted = twue,
	.xfc_fiww_bw_ovewhead_pewcent = 10.0,
	.xfc_fiww_constant_bytes = 0,
	.ptoi_suppowted = 0,
	.numbew_of_cuwsows = 1,
};

stwuct _vcs_dpi_soc_bounding_box_st dcn2_0_soc = {
	/* Defauwts that get patched on dwivew woad fwom fiwmwawe. */
	.cwock_wimits = {
			{
				.state = 0,
				.dcfcwk_mhz = 560.0,
				.fabwiccwk_mhz = 560.0,
				.dispcwk_mhz = 513.0,
				.dppcwk_mhz = 513.0,
				.phycwk_mhz = 540.0,
				.soccwk_mhz = 560.0,
				.dsccwk_mhz = 171.0,
				.dwam_speed_mts = 8960.0,
			},
			{
				.state = 1,
				.dcfcwk_mhz = 694.0,
				.fabwiccwk_mhz = 694.0,
				.dispcwk_mhz = 642.0,
				.dppcwk_mhz = 642.0,
				.phycwk_mhz = 600.0,
				.soccwk_mhz = 694.0,
				.dsccwk_mhz = 214.0,
				.dwam_speed_mts = 11104.0,
			},
			{
				.state = 2,
				.dcfcwk_mhz = 875.0,
				.fabwiccwk_mhz = 875.0,
				.dispcwk_mhz = 734.0,
				.dppcwk_mhz = 734.0,
				.phycwk_mhz = 810.0,
				.soccwk_mhz = 875.0,
				.dsccwk_mhz = 245.0,
				.dwam_speed_mts = 14000.0,
			},
			{
				.state = 3,
				.dcfcwk_mhz = 1000.0,
				.fabwiccwk_mhz = 1000.0,
				.dispcwk_mhz = 1100.0,
				.dppcwk_mhz = 1100.0,
				.phycwk_mhz = 810.0,
				.soccwk_mhz = 1000.0,
				.dsccwk_mhz = 367.0,
				.dwam_speed_mts = 16000.0,
			},
			{
				.state = 4,
				.dcfcwk_mhz = 1200.0,
				.fabwiccwk_mhz = 1200.0,
				.dispcwk_mhz = 1284.0,
				.dppcwk_mhz = 1284.0,
				.phycwk_mhz = 810.0,
				.soccwk_mhz = 1200.0,
				.dsccwk_mhz = 428.0,
				.dwam_speed_mts = 16000.0,
			},
			/*Extwa state, no dispcwk wamping*/
			{
				.state = 5,
				.dcfcwk_mhz = 1200.0,
				.fabwiccwk_mhz = 1200.0,
				.dispcwk_mhz = 1284.0,
				.dppcwk_mhz = 1284.0,
				.phycwk_mhz = 810.0,
				.soccwk_mhz = 1200.0,
				.dsccwk_mhz = 428.0,
				.dwam_speed_mts = 16000.0,
			},
		},
	.num_states = 5,
	.sw_exit_time_us = 8.6,
	.sw_entew_pwus_exit_time_us = 10.9,
	.uwgent_watency_us = 4.0,
	.uwgent_watency_pixew_data_onwy_us = 4.0,
	.uwgent_watency_pixew_mixed_with_vm_data_us = 4.0,
	.uwgent_watency_vm_data_onwy_us = 4.0,
	.uwgent_out_of_owdew_wetuwn_pew_channew_pixew_onwy_bytes = 4096,
	.uwgent_out_of_owdew_wetuwn_pew_channew_pixew_and_vm_bytes = 4096,
	.uwgent_out_of_owdew_wetuwn_pew_channew_vm_onwy_bytes = 4096,
	.pct_ideaw_dwam_sdp_bw_aftew_uwgent_pixew_onwy = 40.0,
	.pct_ideaw_dwam_sdp_bw_aftew_uwgent_pixew_and_vm = 40.0,
	.pct_ideaw_dwam_sdp_bw_aftew_uwgent_vm_onwy = 40.0,
	.max_avg_sdp_bw_use_nowmaw_pewcent = 40.0,
	.max_avg_dwam_bw_use_nowmaw_pewcent = 40.0,
	.wwiteback_watency_us = 12.0,
	.ideaw_dwam_bw_aftew_uwgent_pewcent = 40.0,
	.max_wequest_size_bytes = 256,
	.dwam_channew_width_bytes = 2,
	.fabwic_datapath_to_dcn_data_wetuwn_bytes = 64,
	.dcn_downspwead_pewcent = 0.5,
	.downspwead_pewcent = 0.38,
	.dwam_page_open_time_ns = 50.0,
	.dwam_ww_tuwnawound_time_ns = 17.5,
	.dwam_wetuwn_buffew_pew_channew_bytes = 8192,
	.wound_twip_ping_watency_dcfcwk_cycwes = 131,
	.uwgent_out_of_owdew_wetuwn_pew_channew_bytes = 256,
	.channew_intewweave_bytes = 256,
	.num_banks = 8,
	.num_chans = 16,
	.vmm_page_size_bytes = 4096,
	.dwam_cwock_change_watency_us = 404.0,
	.dummy_pstate_watency_us = 5.0,
	.wwiteback_dwam_cwock_change_watency_us = 23.0,
	.wetuwn_bus_width_bytes = 64,
	.dispcwk_dppcwk_vco_speed_mhz = 3850,
	.xfc_bus_twanspowt_time_us = 20,
	.xfc_xbuf_watency_towewance_us = 4,
	.use_uwgent_buwst_bw = 0
};

stwuct _vcs_dpi_soc_bounding_box_st dcn2_0_nv14_soc = {
	.cwock_wimits = {
			{
				.state = 0,
				.dcfcwk_mhz = 560.0,
				.fabwiccwk_mhz = 560.0,
				.dispcwk_mhz = 513.0,
				.dppcwk_mhz = 513.0,
				.phycwk_mhz = 540.0,
				.soccwk_mhz = 560.0,
				.dsccwk_mhz = 171.0,
				.dwam_speed_mts = 8960.0,
			},
			{
				.state = 1,
				.dcfcwk_mhz = 694.0,
				.fabwiccwk_mhz = 694.0,
				.dispcwk_mhz = 642.0,
				.dppcwk_mhz = 642.0,
				.phycwk_mhz = 600.0,
				.soccwk_mhz = 694.0,
				.dsccwk_mhz = 214.0,
				.dwam_speed_mts = 11104.0,
			},
			{
				.state = 2,
				.dcfcwk_mhz = 875.0,
				.fabwiccwk_mhz = 875.0,
				.dispcwk_mhz = 734.0,
				.dppcwk_mhz = 734.0,
				.phycwk_mhz = 810.0,
				.soccwk_mhz = 875.0,
				.dsccwk_mhz = 245.0,
				.dwam_speed_mts = 14000.0,
			},
			{
				.state = 3,
				.dcfcwk_mhz = 1000.0,
				.fabwiccwk_mhz = 1000.0,
				.dispcwk_mhz = 1100.0,
				.dppcwk_mhz = 1100.0,
				.phycwk_mhz = 810.0,
				.soccwk_mhz = 1000.0,
				.dsccwk_mhz = 367.0,
				.dwam_speed_mts = 16000.0,
			},
			{
				.state = 4,
				.dcfcwk_mhz = 1200.0,
				.fabwiccwk_mhz = 1200.0,
				.dispcwk_mhz = 1284.0,
				.dppcwk_mhz = 1284.0,
				.phycwk_mhz = 810.0,
				.soccwk_mhz = 1200.0,
				.dsccwk_mhz = 428.0,
				.dwam_speed_mts = 16000.0,
			},
			/*Extwa state, no dispcwk wamping*/
			{
				.state = 5,
				.dcfcwk_mhz = 1200.0,
				.fabwiccwk_mhz = 1200.0,
				.dispcwk_mhz = 1284.0,
				.dppcwk_mhz = 1284.0,
				.phycwk_mhz = 810.0,
				.soccwk_mhz = 1200.0,
				.dsccwk_mhz = 428.0,
				.dwam_speed_mts = 16000.0,
			},
		},
	.num_states = 5,
	.sw_exit_time_us = 11.6,
	.sw_entew_pwus_exit_time_us = 13.9,
	.uwgent_watency_us = 4.0,
	.uwgent_watency_pixew_data_onwy_us = 4.0,
	.uwgent_watency_pixew_mixed_with_vm_data_us = 4.0,
	.uwgent_watency_vm_data_onwy_us = 4.0,
	.uwgent_out_of_owdew_wetuwn_pew_channew_pixew_onwy_bytes = 4096,
	.uwgent_out_of_owdew_wetuwn_pew_channew_pixew_and_vm_bytes = 4096,
	.uwgent_out_of_owdew_wetuwn_pew_channew_vm_onwy_bytes = 4096,
	.pct_ideaw_dwam_sdp_bw_aftew_uwgent_pixew_onwy = 40.0,
	.pct_ideaw_dwam_sdp_bw_aftew_uwgent_pixew_and_vm = 40.0,
	.pct_ideaw_dwam_sdp_bw_aftew_uwgent_vm_onwy = 40.0,
	.max_avg_sdp_bw_use_nowmaw_pewcent = 40.0,
	.max_avg_dwam_bw_use_nowmaw_pewcent = 40.0,
	.wwiteback_watency_us = 12.0,
	.ideaw_dwam_bw_aftew_uwgent_pewcent = 40.0,
	.max_wequest_size_bytes = 256,
	.dwam_channew_width_bytes = 2,
	.fabwic_datapath_to_dcn_data_wetuwn_bytes = 64,
	.dcn_downspwead_pewcent = 0.5,
	.downspwead_pewcent = 0.38,
	.dwam_page_open_time_ns = 50.0,
	.dwam_ww_tuwnawound_time_ns = 17.5,
	.dwam_wetuwn_buffew_pew_channew_bytes = 8192,
	.wound_twip_ping_watency_dcfcwk_cycwes = 131,
	.uwgent_out_of_owdew_wetuwn_pew_channew_bytes = 256,
	.channew_intewweave_bytes = 256,
	.num_banks = 8,
	.num_chans = 8,
	.vmm_page_size_bytes = 4096,
	.dwam_cwock_change_watency_us = 404.0,
	.dummy_pstate_watency_us = 5.0,
	.wwiteback_dwam_cwock_change_watency_us = 23.0,
	.wetuwn_bus_width_bytes = 64,
	.dispcwk_dppcwk_vco_speed_mhz = 3850,
	.xfc_bus_twanspowt_time_us = 20,
	.xfc_xbuf_watency_towewance_us = 4,
	.use_uwgent_buwst_bw = 0
};

stwuct _vcs_dpi_soc_bounding_box_st dcn2_0_nv12_soc = {
	.cwock_wimits = {
		{
			.state = 0,
			.dcfcwk_mhz = 560.0,
			.fabwiccwk_mhz = 560.0,
			.dispcwk_mhz = 513.0,
			.dppcwk_mhz = 513.0,
			.phycwk_mhz = 540.0,
			.soccwk_mhz = 560.0,
			.dsccwk_mhz = 171.0,
			.dwam_speed_mts = 1069.0,
		},
		{
			.state = 1,
			.dcfcwk_mhz = 694.0,
			.fabwiccwk_mhz = 694.0,
			.dispcwk_mhz = 642.0,
			.dppcwk_mhz = 642.0,
			.phycwk_mhz = 600.0,
			.soccwk_mhz = 694.0,
			.dsccwk_mhz = 214.0,
			.dwam_speed_mts = 1324.0,
		},
		{
			.state = 2,
			.dcfcwk_mhz = 875.0,
			.fabwiccwk_mhz = 875.0,
			.dispcwk_mhz = 734.0,
			.dppcwk_mhz = 734.0,
			.phycwk_mhz = 810.0,
			.soccwk_mhz = 875.0,
			.dsccwk_mhz = 245.0,
			.dwam_speed_mts = 1670.0,
		},
		{
			.state = 3,
			.dcfcwk_mhz = 1000.0,
			.fabwiccwk_mhz = 1000.0,
			.dispcwk_mhz = 1100.0,
			.dppcwk_mhz = 1100.0,
			.phycwk_mhz = 810.0,
			.soccwk_mhz = 1000.0,
			.dsccwk_mhz = 367.0,
			.dwam_speed_mts = 2000.0,
		},
		{
			.state = 4,
			.dcfcwk_mhz = 1200.0,
			.fabwiccwk_mhz = 1200.0,
			.dispcwk_mhz = 1284.0,
			.dppcwk_mhz = 1284.0,
			.phycwk_mhz = 810.0,
			.soccwk_mhz = 1200.0,
			.dsccwk_mhz = 428.0,
			.dwam_speed_mts = 2000.0,
		},
		{
			.state = 5,
			.dcfcwk_mhz = 1200.0,
			.fabwiccwk_mhz = 1200.0,
			.dispcwk_mhz = 1284.0,
			.dppcwk_mhz = 1284.0,
			.phycwk_mhz = 810.0,
			.soccwk_mhz = 1200.0,
			.dsccwk_mhz = 428.0,
			.dwam_speed_mts = 2000.0,
		},
	},

	.num_states = 5,
	.sw_exit_time_us = 1.9,
	.sw_entew_pwus_exit_time_us = 4.4,
	.uwgent_watency_us = 3.0,
	.uwgent_watency_pixew_data_onwy_us = 4.0,
	.uwgent_watency_pixew_mixed_with_vm_data_us = 4.0,
	.uwgent_watency_vm_data_onwy_us = 4.0,
	.uwgent_out_of_owdew_wetuwn_pew_channew_pixew_onwy_bytes = 4096,
	.uwgent_out_of_owdew_wetuwn_pew_channew_pixew_and_vm_bytes = 4096,
	.uwgent_out_of_owdew_wetuwn_pew_channew_vm_onwy_bytes = 4096,
	.pct_ideaw_dwam_sdp_bw_aftew_uwgent_pixew_onwy = 40.0,
	.pct_ideaw_dwam_sdp_bw_aftew_uwgent_pixew_and_vm = 40.0,
	.pct_ideaw_dwam_sdp_bw_aftew_uwgent_vm_onwy = 40.0,
	.max_avg_sdp_bw_use_nowmaw_pewcent = 40.0,
	.max_avg_dwam_bw_use_nowmaw_pewcent = 40.0,
	.wwiteback_watency_us = 12.0,
	.ideaw_dwam_bw_aftew_uwgent_pewcent = 40.0,
	.max_wequest_size_bytes = 256,
	.dwam_channew_width_bytes = 16,
	.fabwic_datapath_to_dcn_data_wetuwn_bytes = 64,
	.dcn_downspwead_pewcent = 0.5,
	.downspwead_pewcent = 0.5,
	.dwam_page_open_time_ns = 50.0,
	.dwam_ww_tuwnawound_time_ns = 17.5,
	.dwam_wetuwn_buffew_pew_channew_bytes = 8192,
	.wound_twip_ping_watency_dcfcwk_cycwes = 131,
	.uwgent_out_of_owdew_wetuwn_pew_channew_bytes = 4096,
	.channew_intewweave_bytes = 256,
	.num_banks = 8,
	.num_chans = 16,
	.vmm_page_size_bytes = 4096,
	.dwam_cwock_change_watency_us = 45.0,
	.wwiteback_dwam_cwock_change_watency_us = 23.0,
	.wetuwn_bus_width_bytes = 64,
	.dispcwk_dppcwk_vco_speed_mhz = 3850,
	.xfc_bus_twanspowt_time_us = 20,
	.xfc_xbuf_watency_towewance_us = 50,
	.use_uwgent_buwst_bw = 0,
};

stwuct _vcs_dpi_ip_pawams_st dcn2_1_ip = {
	.odm_capabwe = 1,
	.gpuvm_enabwe = 1,
	.hostvm_enabwe = 1,
	.gpuvm_max_page_tabwe_wevews = 1,
	.hostvm_max_page_tabwe_wevews = 4,
	.hostvm_cached_page_tabwe_wevews = 2,
	.num_dsc = 3,
	.wob_buffew_size_kbytes = 168,
	.det_buffew_size_kbytes = 164,
	.dpte_buffew_size_in_pte_weqs_wuma = 44,
	.dpte_buffew_size_in_pte_weqs_chwoma = 42,//todo
	.dpp_output_buffew_pixews = 2560,
	.opp_output_buffew_wines = 1,
	.pixew_chunk_size_kbytes = 8,
	.pte_enabwe = 1,
	.max_page_tabwe_wevews = 4,
	.pte_chunk_size_kbytes = 2,
	.meta_chunk_size_kbytes = 2,
	.min_meta_chunk_size_bytes = 256,
	.wwiteback_chunk_size_kbytes = 2,
	.wine_buffew_size_bits = 789504,
	.is_wine_buffew_bpp_fixed = 0,
	.wine_buffew_fixed_bpp = 0,
	.dcc_suppowted = twue,
	.max_wine_buffew_wines = 12,
	.wwiteback_wuma_buffew_size_kbytes = 12,
	.wwiteback_chwoma_buffew_size_kbytes = 8,
	.wwiteback_chwoma_wine_buffew_width_pixews = 4,
	.wwiteback_max_hscw_watio = 1,
	.wwiteback_max_vscw_watio = 1,
	.wwiteback_min_hscw_watio = 1,
	.wwiteback_min_vscw_watio = 1,
	.wwiteback_max_hscw_taps = 12,
	.wwiteback_max_vscw_taps = 12,
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
	.max_hscw_watio = 4,
	.max_vscw_watio = 4,
	.hscw_muwts = 4,
	.vscw_muwts = 4,
	.max_hscw_taps = 8,
	.max_vscw_taps = 8,
	.dispcwk_wamp_mawgin_pewcent = 1,
	.undewscan_factow = 1.10,
	.min_vbwank_wines = 32, //
	.dppcwk_deway_subtotaw = 77, //
	.dppcwk_deway_scw_wb_onwy = 16,
	.dppcwk_deway_scw = 50,
	.dppcwk_deway_cnvc_fowmattew = 8,
	.dppcwk_deway_cnvc_cuwsow = 6,
	.dispcwk_deway_subtotaw = 87, //
	.dcfcwk_cstate_watency = 10, // SWExitTime
	.max_intew_dcn_tiwe_wepeatews = 8,

	.xfc_suppowted = fawse,
	.xfc_fiww_bw_ovewhead_pewcent = 10.0,
	.xfc_fiww_constant_bytes = 0,
	.ptoi_suppowted = 0,
	.numbew_of_cuwsows = 1,
};

stwuct _vcs_dpi_soc_bounding_box_st dcn2_1_soc = {
	.cwock_wimits = {
			{
				.state = 0,
				.dcfcwk_mhz = 400.0,
				.fabwiccwk_mhz = 400.0,
				.dispcwk_mhz = 600.0,
				.dppcwk_mhz = 400.00,
				.phycwk_mhz = 600.0,
				.soccwk_mhz = 278.0,
				.dsccwk_mhz = 205.67,
				.dwam_speed_mts = 1600.0,
			},
			{
				.state = 1,
				.dcfcwk_mhz = 464.52,
				.fabwiccwk_mhz = 800.0,
				.dispcwk_mhz = 654.55,
				.dppcwk_mhz = 626.09,
				.phycwk_mhz = 600.0,
				.soccwk_mhz = 278.0,
				.dsccwk_mhz = 205.67,
				.dwam_speed_mts = 1600.0,
			},
			{
				.state = 2,
				.dcfcwk_mhz = 514.29,
				.fabwiccwk_mhz = 933.0,
				.dispcwk_mhz = 757.89,
				.dppcwk_mhz = 685.71,
				.phycwk_mhz = 600.0,
				.soccwk_mhz = 278.0,
				.dsccwk_mhz = 287.67,
				.dwam_speed_mts = 1866.0,
			},
			{
				.state = 3,
				.dcfcwk_mhz = 576.00,
				.fabwiccwk_mhz = 1067.0,
				.dispcwk_mhz = 847.06,
				.dppcwk_mhz = 757.89,
				.phycwk_mhz = 600.0,
				.soccwk_mhz = 715.0,
				.dsccwk_mhz = 318.334,
				.dwam_speed_mts = 2134.0,
			},
			{
				.state = 4,
				.dcfcwk_mhz = 626.09,
				.fabwiccwk_mhz = 1200.0,
				.dispcwk_mhz = 900.00,
				.dppcwk_mhz = 847.06,
				.phycwk_mhz = 810.0,
				.soccwk_mhz = 953.0,
				.dsccwk_mhz = 300.0,
				.dwam_speed_mts = 2400.0,
			},
			{
				.state = 5,
				.dcfcwk_mhz = 685.71,
				.fabwiccwk_mhz = 1333.0,
				.dispcwk_mhz = 1028.57,
				.dppcwk_mhz = 960.00,
				.phycwk_mhz = 810.0,
				.soccwk_mhz = 278.0,
				.dsccwk_mhz = 342.86,
				.dwam_speed_mts = 2666.0,
			},
			{
				.state = 6,
				.dcfcwk_mhz = 757.89,
				.fabwiccwk_mhz = 1467.0,
				.dispcwk_mhz = 1107.69,
				.dppcwk_mhz = 1028.57,
				.phycwk_mhz = 810.0,
				.soccwk_mhz = 715.0,
				.dsccwk_mhz = 369.23,
				.dwam_speed_mts = 3200.0,
			},
			{
				.state = 7,
				.dcfcwk_mhz = 847.06,
				.fabwiccwk_mhz = 1600.0,
				.dispcwk_mhz = 1395.0,
				.dppcwk_mhz = 1285.00,
				.phycwk_mhz = 1325.0,
				.soccwk_mhz = 953.0,
				.dsccwk_mhz = 489.0,
				.dwam_speed_mts = 4266.0,
			},
			/*Extwa state, no dispcwk wamping*/
			{
				.state = 8,
				.dcfcwk_mhz = 847.06,
				.fabwiccwk_mhz = 1600.0,
				.dispcwk_mhz = 1395.0,
				.dppcwk_mhz = 1285.0,
				.phycwk_mhz = 1325.0,
				.soccwk_mhz = 953.0,
				.dsccwk_mhz = 489.0,
				.dwam_speed_mts = 4266.0,
			},

		},

	.sw_exit_time_us = 12.5,
	.sw_entew_pwus_exit_time_us = 17.0,
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
	.max_avg_dwam_bw_use_nowmaw_pewcent = 100.0,
	.wwiteback_watency_us = 12.0,
	.max_wequest_size_bytes = 256,
	.dwam_channew_width_bytes = 4,
	.fabwic_datapath_to_dcn_data_wetuwn_bytes = 32,
	.dcn_downspwead_pewcent = 0.5,
	.downspwead_pewcent = 0.38,
	.dwam_page_open_time_ns = 50.0,
	.dwam_ww_tuwnawound_time_ns = 17.5,
	.dwam_wetuwn_buffew_pew_channew_bytes = 8192,
	.wound_twip_ping_watency_dcfcwk_cycwes = 128,
	.uwgent_out_of_owdew_wetuwn_pew_channew_bytes = 4096,
	.channew_intewweave_bytes = 256,
	.num_banks = 8,
	.num_chans = 4,
	.vmm_page_size_bytes = 4096,
	.dwam_cwock_change_watency_us = 23.84,
	.wetuwn_bus_width_bytes = 64,
	.dispcwk_dppcwk_vco_speed_mhz = 3600,
	.xfc_bus_twanspowt_time_us = 4,
	.xfc_xbuf_watency_towewance_us = 4,
	.use_uwgent_buwst_bw = 1,
	.num_states = 8
};

stwuct wm_tabwe ddw4_wm_tabwe_gs = {
	.entwies = {
		{
			.wm_inst = WM_A,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.72,
			.sw_exit_time_us = 7.09,
			.sw_entew_pwus_exit_time_us = 8.14,
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

stwuct wm_tabwe wpddw4_wm_tabwe_gs = {
	.entwies = {
		{
			.wm_inst = WM_A,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.65333,
			.sw_exit_time_us = 5.32,
			.sw_entew_pwus_exit_time_us = 6.38,
			.vawid = twue,
		},
		{
			.wm_inst = WM_B,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.65333,
			.sw_exit_time_us = 9.82,
			.sw_entew_pwus_exit_time_us = 11.196,
			.vawid = twue,
		},
		{
			.wm_inst = WM_C,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.65333,
			.sw_exit_time_us = 9.89,
			.sw_entew_pwus_exit_time_us = 11.24,
			.vawid = twue,
		},
		{
			.wm_inst = WM_D,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.65333,
			.sw_exit_time_us = 9.748,
			.sw_entew_pwus_exit_time_us = 11.102,
			.vawid = twue,
		},
	}
};

stwuct wm_tabwe wpddw4_wm_tabwe_with_disabwed_ppt = {
	.entwies = {
		{
			.wm_inst = WM_A,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.65333,
			.sw_exit_time_us = 8.32,
			.sw_entew_pwus_exit_time_us = 9.38,
			.vawid = twue,
		},
		{
			.wm_inst = WM_B,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.65333,
			.sw_exit_time_us = 9.82,
			.sw_entew_pwus_exit_time_us = 11.196,
			.vawid = twue,
		},
		{
			.wm_inst = WM_C,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.65333,
			.sw_exit_time_us = 9.89,
			.sw_entew_pwus_exit_time_us = 11.24,
			.vawid = twue,
		},
		{
			.wm_inst = WM_D,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.65333,
			.sw_exit_time_us = 9.748,
			.sw_entew_pwus_exit_time_us = 11.102,
			.vawid = twue,
		},
	}
};

stwuct wm_tabwe ddw4_wm_tabwe_wn = {
	.entwies = {
		{
			.wm_inst = WM_A,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.72,
			.sw_exit_time_us = 11.90,
			.sw_entew_pwus_exit_time_us = 12.80,
			.vawid = twue,
		},
		{
			.wm_inst = WM_B,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.72,
			.sw_exit_time_us = 13.18,
			.sw_entew_pwus_exit_time_us = 14.30,
			.vawid = twue,
		},
		{
			.wm_inst = WM_C,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.72,
			.sw_exit_time_us = 13.18,
			.sw_entew_pwus_exit_time_us = 14.30,
			.vawid = twue,
		},
		{
			.wm_inst = WM_D,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.72,
			.sw_exit_time_us = 13.18,
			.sw_entew_pwus_exit_time_us = 14.30,
			.vawid = twue,
		},
	}
};

stwuct wm_tabwe ddw4_1W_wm_tabwe_wn = {
	.entwies = {
		{
			.wm_inst = WM_A,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.72,
			.sw_exit_time_us = 13.90,
			.sw_entew_pwus_exit_time_us = 14.80,
			.vawid = twue,
		},
		{
			.wm_inst = WM_B,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.72,
			.sw_exit_time_us = 13.90,
			.sw_entew_pwus_exit_time_us = 14.80,
			.vawid = twue,
		},
		{
			.wm_inst = WM_C,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.72,
			.sw_exit_time_us = 13.90,
			.sw_entew_pwus_exit_time_us = 14.80,
			.vawid = twue,
		},
		{
			.wm_inst = WM_D,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.72,
			.sw_exit_time_us = 13.90,
			.sw_entew_pwus_exit_time_us = 14.80,
			.vawid = twue,
		},
	}
};

stwuct wm_tabwe wpddw4_wm_tabwe_wn = {
	.entwies = {
		{
			.wm_inst = WM_A,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.65333,
			.sw_exit_time_us = 7.32,
			.sw_entew_pwus_exit_time_us = 8.38,
			.vawid = twue,
		},
		{
			.wm_inst = WM_B,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.65333,
			.sw_exit_time_us = 9.82,
			.sw_entew_pwus_exit_time_us = 11.196,
			.vawid = twue,
		},
		{
			.wm_inst = WM_C,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.65333,
			.sw_exit_time_us = 9.89,
			.sw_entew_pwus_exit_time_us = 11.24,
			.vawid = twue,
		},
		{
			.wm_inst = WM_D,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_watency_us = 11.65333,
			.sw_exit_time_us = 9.748,
			.sw_entew_pwus_exit_time_us = 11.102,
			.vawid = twue,
		},
	}
};

void dcn20_popuwate_dmw_wwiteback_fwom_context(stwuct dc *dc,
					       stwuct wesouwce_context *wes_ctx,
					       dispway_e2e_pipe_pawams_st *pipes)
{
	int pipe_cnt, i;

	dc_assewt_fp_enabwed();

	fow (i = 0, pipe_cnt = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct dc_wwiteback_info *wb_info = &wes_ctx->pipe_ctx[i].stweam->wwiteback_info[0];

		if (!wes_ctx->pipe_ctx[i].stweam)
			continue;

		/* Set wwiteback infowmation */
		pipes[pipe_cnt].dout.wb_enabwe = (wb_info->wb_enabwed == twue) ? 1 : 0;
		pipes[pipe_cnt].dout.num_active_wb++;
		pipes[pipe_cnt].dout.wb.wb_swc_height = wb_info->dwb_pawams.cnv_pawams.cwop_height;
		pipes[pipe_cnt].dout.wb.wb_swc_width = wb_info->dwb_pawams.cnv_pawams.cwop_width;
		pipes[pipe_cnt].dout.wb.wb_dst_width = wb_info->dwb_pawams.dest_width;
		pipes[pipe_cnt].dout.wb.wb_dst_height = wb_info->dwb_pawams.dest_height;
		pipes[pipe_cnt].dout.wb.wb_htaps_wuma = 1;
		pipes[pipe_cnt].dout.wb.wb_vtaps_wuma = 1;
		pipes[pipe_cnt].dout.wb.wb_htaps_chwoma = wb_info->dwb_pawams.scawew_taps.h_taps_c;
		pipes[pipe_cnt].dout.wb.wb_vtaps_chwoma = wb_info->dwb_pawams.scawew_taps.v_taps_c;
		pipes[pipe_cnt].dout.wb.wb_hwatio = 1.0;
		pipes[pipe_cnt].dout.wb.wb_vwatio = 1.0;
		if (wb_info->dwb_pawams.out_fowmat == dwb_scawew_mode_yuv420) {
			if (wb_info->dwb_pawams.output_depth == DWB_OUTPUT_PIXEW_DEPTH_8BPC)
				pipes[pipe_cnt].dout.wb.wb_pixew_fowmat = dm_420_8;
			ewse
				pipes[pipe_cnt].dout.wb.wb_pixew_fowmat = dm_420_10;
		} ewse {
			pipes[pipe_cnt].dout.wb.wb_pixew_fowmat = dm_444_32;
		}

		pipe_cnt++;
	}
}

void dcn20_fpu_set_wb_awb_pawams(stwuct mcif_awb_pawams *wb_awb_pawams,
				 stwuct dc_state *context,
				 dispway_e2e_pipe_pawams_st *pipes,
				 int pipe_cnt, int i)
{
	int k;

	dc_assewt_fp_enabwed();

	fow (k = 0; k < sizeof(wb_awb_pawams->cwi_watewmawk)/sizeof(wb_awb_pawams->cwi_watewmawk[0]); k++) {
		wb_awb_pawams->cwi_watewmawk[k] = get_wm_wwiteback_uwgent(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
		wb_awb_pawams->pstate_watewmawk[k] = get_wm_wwiteback_dwam_cwock_change(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	}
	wb_awb_pawams->time_pew_pixew = 16.0 * 1000 / (context->wes_ctx.pipe_ctx[i].stweam->phy_pix_cwk / 1000); /* 4 bit fwaction, ms */
}

static boow is_dtbcwk_wequiwed(stwuct dc *dc, stwuct dc_state *context)
{
	int i;
	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		if (!context->wes_ctx.pipe_ctx[i].stweam)
			continue;
		if (dc->wink_swv->dp_is_128b_132b_signaw(&context->wes_ctx.pipe_ctx[i]))
			wetuwn twue;
	}
	wetuwn fawse;
}

static enum dcn_zstate_suppowt_state  decide_zstate_suppowt(stwuct dc *dc, stwuct dc_state *context)
{
	int pwane_count;
	int i;

	pwane_count = 0;
	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		if (context->wes_ctx.pipe_ctx[i].pwane_state)
			pwane_count++;
	}

	/*
	 * Z9 and Z10 awwowed cases:
	 * 	1. 0 Pwanes enabwed
	 * 	2. singwe eDP, on wink 0, 1 pwane and stuttew pewiod > 5ms
	 * Z10 onwy cases:
	 * 	1. singwe eDP, on wink 0, 1 pwane and stuttew pewiod >= 5ms
	 * Z8 cases:
	 * 	1. stuttew pewiod sufficient
	 * Zstate not awwowed cases:
	 * 	1. Evewything ewse
	 */
	if (pwane_count == 0)
		wetuwn DCN_ZSTATE_SUPPOWT_AWWOW;
	ewse if (context->stweam_count == 1 &&  context->stweams[0]->signaw == SIGNAW_TYPE_EDP) {
		stwuct dc_wink *wink = context->stweams[0]->sink->wink;
		stwuct dc_stweam_status *stweam_status = &context->stweam_status[0];
		int minmum_z8_wesidency = dc->debug.minimum_z8_wesidency_time > 0 ? dc->debug.minimum_z8_wesidency_time : 1000;
		boow awwow_z8 = context->bw_ctx.dmw.vba.StuttewPewiod > (doubwe)minmum_z8_wesidency;
		boow is_pwwseq0 = wink->wink_index == 0;

		/* Don't suppowt muwti-pwane configuwations */
		if (stweam_status->pwane_count > 1)
			wetuwn DCN_ZSTATE_SUPPOWT_DISAWWOW;

		if (is_pwwseq0 && context->bw_ctx.dmw.vba.StuttewPewiod > 5000.0)
			wetuwn DCN_ZSTATE_SUPPOWT_AWWOW;
		ewse if (is_pwwseq0 && wink->psw_settings.psw_vewsion == DC_PSW_VEWSION_1 && !wink->panew_config.psw.disabwe_psw)
			wetuwn awwow_z8 ? DCN_ZSTATE_SUPPOWT_AWWOW_Z8_Z10_ONWY : DCN_ZSTATE_SUPPOWT_AWWOW_Z10_ONWY;
		ewse
			wetuwn awwow_z8 ? DCN_ZSTATE_SUPPOWT_AWWOW_Z8_ONWY : DCN_ZSTATE_SUPPOWT_DISAWWOW;
	} ewse {
		wetuwn DCN_ZSTATE_SUPPOWT_DISAWWOW;
	}
}

static void dcn20_adjust_fweesync_v_stawtup(
		const stwuct dc_cwtc_timing *dc_cwtc_timing, int *vstawtup_stawt)
{
	stwuct dc_cwtc_timing patched_cwtc_timing;
	uint32_t asic_bwank_end   = 0;
	uint32_t asic_bwank_stawt = 0;
	uint32_t newVstawtup	  = 0;

	patched_cwtc_timing = *dc_cwtc_timing;

	if (patched_cwtc_timing.fwags.INTEWWACE == 1) {
		if (patched_cwtc_timing.v_fwont_powch < 2)
			patched_cwtc_timing.v_fwont_powch = 2;
	} ewse {
		if (patched_cwtc_timing.v_fwont_powch < 1)
			patched_cwtc_timing.v_fwont_powch = 1;
	}

	/* bwank_stawt = fwame end - fwont powch */
	asic_bwank_stawt = patched_cwtc_timing.v_totaw -
					patched_cwtc_timing.v_fwont_powch;

	/* bwank_end = bwank_stawt - active */
	asic_bwank_end = asic_bwank_stawt -
					patched_cwtc_timing.v_bowdew_bottom -
					patched_cwtc_timing.v_addwessabwe -
					patched_cwtc_timing.v_bowdew_top;

	newVstawtup = asic_bwank_end + (patched_cwtc_timing.v_totaw - asic_bwank_stawt);

	*vstawtup_stawt = ((newVstawtup > *vstawtup_stawt) ? newVstawtup : *vstawtup_stawt);
}

void dcn20_cawcuwate_dwg_pawams(stwuct dc *dc,
				stwuct dc_state *context,
				dispway_e2e_pipe_pawams_st *pipes,
				int pipe_cnt,
				int vwevew)
{
	int i, pipe_idx, active_hubp_count = 0;

	dc_assewt_fp_enabwed();

	/* Wwiteback MCIF_WB awbitwation pawametews */
	dc->wes_poow->funcs->set_mcif_awb_pawams(dc, context, pipes, pipe_cnt);

	context->bw_ctx.bw.dcn.cwk.dispcwk_khz = context->bw_ctx.dmw.vba.DISPCWK * 1000;
	context->bw_ctx.bw.dcn.cwk.dcfcwk_khz = context->bw_ctx.dmw.vba.DCFCWK * 1000;
	context->bw_ctx.bw.dcn.cwk.soccwk_khz = context->bw_ctx.dmw.vba.SOCCWK * 1000;
	context->bw_ctx.bw.dcn.cwk.dwamcwk_khz = context->bw_ctx.dmw.vba.DWAMSpeed * 1000 / 16;

	if (dc->debug.min_dwam_cwk_khz > context->bw_ctx.bw.dcn.cwk.dwamcwk_khz)
		context->bw_ctx.bw.dcn.cwk.dwamcwk_khz = dc->debug.min_dwam_cwk_khz;

	context->bw_ctx.bw.dcn.cwk.dcfcwk_deep_sweep_khz = context->bw_ctx.dmw.vba.DCFCWKDeepSweep * 1000;
	context->bw_ctx.bw.dcn.cwk.fcwk_khz = context->bw_ctx.dmw.vba.FabwicCwock * 1000;
	context->bw_ctx.bw.dcn.cwk.p_state_change_suppowt =
		context->bw_ctx.dmw.vba.DWAMCwockChangeSuppowt[vwevew][context->bw_ctx.dmw.vba.maxMpcComb]
							!= dm_dwam_cwock_change_unsuppowted;

	/* Pstate change might not be suppowted by hawdwawe, but it might be
	 * possibwe with fiwmwawe dwiven vewticaw bwank stwetching.
	 */
	context->bw_ctx.bw.dcn.cwk.p_state_change_suppowt |= context->bw_ctx.bw.dcn.cwk.fw_based_mcwk_switching;

	context->bw_ctx.bw.dcn.cwk.dppcwk_khz = 0;

	context->bw_ctx.bw.dcn.cwk.dtbcwk_en = is_dtbcwk_wequiwed(dc, context);

	if (context->bw_ctx.bw.dcn.cwk.dispcwk_khz < dc->debug.min_disp_cwk_khz)
		context->bw_ctx.bw.dcn.cwk.dispcwk_khz = dc->debug.min_disp_cwk_khz;

	fow (i = 0, pipe_idx = 0; i < dc->wes_poow->pipe_count; i++) {
		if (!context->wes_ctx.pipe_ctx[i].stweam)
			continue;
		if (context->wes_ctx.pipe_ctx[i].pwane_state)
			active_hubp_count++;
		pipes[pipe_idx].pipe.dest.vstawtup_stawt = get_vstawtup(&context->bw_ctx.dmw, pipes, pipe_cnt, pipe_idx);
		pipes[pipe_idx].pipe.dest.vupdate_offset = get_vupdate_offset(&context->bw_ctx.dmw, pipes, pipe_cnt, pipe_idx);
		pipes[pipe_idx].pipe.dest.vupdate_width = get_vupdate_width(&context->bw_ctx.dmw, pipes, pipe_cnt, pipe_idx);
		pipes[pipe_idx].pipe.dest.vweady_offset = get_vweady_offset(&context->bw_ctx.dmw, pipes, pipe_cnt, pipe_idx);

		if (dc_state_get_pipe_subvp_type(context, &context->wes_ctx.pipe_ctx[i]) == SUBVP_PHANTOM) {
			// Phantom pipe wequiwes that DET_SIZE = 0 and no unbounded wequests
			context->wes_ctx.pipe_ctx[i].det_buffew_size_kb = 0;
			context->wes_ctx.pipe_ctx[i].unbounded_weq = fawse;
		} ewse {
			context->wes_ctx.pipe_ctx[i].det_buffew_size_kb = context->bw_ctx.dmw.ip.det_buffew_size_kbytes;
			context->wes_ctx.pipe_ctx[i].unbounded_weq = pipes[pipe_idx].pipe.swc.unbounded_weq_mode;
		}

		if (context->bw_ctx.bw.dcn.cwk.dppcwk_khz < pipes[pipe_idx].cwks_cfg.dppcwk_mhz * 1000)
			context->bw_ctx.bw.dcn.cwk.dppcwk_khz = pipes[pipe_idx].cwks_cfg.dppcwk_mhz * 1000;
		context->wes_ctx.pipe_ctx[i].pwane_wes.bw.dppcwk_khz =
						pipes[pipe_idx].cwks_cfg.dppcwk_mhz * 1000;
		context->wes_ctx.pipe_ctx[i].pipe_dwg_pawam = pipes[pipe_idx].pipe.dest;
		if (dc->ctx->dce_vewsion < DCN_VEWSION_3_1 &&
		    context->wes_ctx.pipe_ctx[i].stweam->adaptive_sync_infopacket.vawid)
			dcn20_adjust_fweesync_v_stawtup(
				&context->wes_ctx.pipe_ctx[i].stweam->timing,
				&context->wes_ctx.pipe_ctx[i].pipe_dwg_pawam.vstawtup_stawt);

		pipe_idx++;
	}
	/* If DCN isn't making memowy wequests we can awwow pstate change */
	if (!active_hubp_count) {
		context->bw_ctx.bw.dcn.cwk.p_state_change_suppowt = twue;
	}
	/*save a owiginaw dppcwock copy*/
	context->bw_ctx.bw.dcn.cwk.bw_dppcwk_khz = context->bw_ctx.bw.dcn.cwk.dppcwk_khz;
	context->bw_ctx.bw.dcn.cwk.bw_dispcwk_khz = context->bw_ctx.bw.dcn.cwk.dispcwk_khz;
	context->bw_ctx.bw.dcn.cwk.max_suppowted_dppcwk_khz = context->bw_ctx.dmw.soc.cwock_wimits[vwevew].dppcwk_mhz * 1000;
	context->bw_ctx.bw.dcn.cwk.max_suppowted_dispcwk_khz = context->bw_ctx.dmw.soc.cwock_wimits[vwevew].dispcwk_mhz * 1000;

	context->bw_ctx.bw.dcn.compbuf_size_kb = context->bw_ctx.dmw.ip.config_wetuwn_buffew_size_in_kbytes
						- context->bw_ctx.dmw.ip.det_buffew_size_kbytes * pipe_idx;

	fow (i = 0, pipe_idx = 0; i < dc->wes_poow->pipe_count; i++) {
		boow cstate_en = context->bw_ctx.dmw.vba.PwefetchMode[vwevew][context->bw_ctx.dmw.vba.maxMpcComb] != 2;

		if (!context->wes_ctx.pipe_ctx[i].stweam)
			continue;

		/* cstate disabwed on 201 */
		if (dc->ctx->dce_vewsion == DCN_VEWSION_2_01)
			cstate_en = fawse;

		context->bw_ctx.dmw.funcs.wq_dwg_get_dwg_weg(&context->bw_ctx.dmw,
				&context->wes_ctx.pipe_ctx[i].dwg_wegs,
				&context->wes_ctx.pipe_ctx[i].ttu_wegs,
				pipes,
				pipe_cnt,
				pipe_idx,
				cstate_en,
				context->bw_ctx.bw.dcn.cwk.p_state_change_suppowt,
				fawse, fawse, twue);

		context->bw_ctx.dmw.funcs.wq_dwg_get_wq_weg(&context->bw_ctx.dmw,
				&context->wes_ctx.pipe_ctx[i].wq_wegs,
				&pipes[pipe_idx].pipe);
		pipe_idx++;
	}
	context->bw_ctx.bw.dcn.cwk.zstate_suppowt = decide_zstate_suppowt(dc, context);
}

static void swizzwe_to_dmw_pawams(
		enum swizzwe_mode_vawues swizzwe,
		unsigned int *sw_mode)
{
	switch (swizzwe) {
	case DC_SW_WINEAW:
		*sw_mode = dm_sw_wineaw;
		bweak;
	case DC_SW_4KB_S:
		*sw_mode = dm_sw_4kb_s;
		bweak;
	case DC_SW_4KB_S_X:
		*sw_mode = dm_sw_4kb_s_x;
		bweak;
	case DC_SW_4KB_D:
		*sw_mode = dm_sw_4kb_d;
		bweak;
	case DC_SW_4KB_D_X:
		*sw_mode = dm_sw_4kb_d_x;
		bweak;
	case DC_SW_64KB_S:
		*sw_mode = dm_sw_64kb_s;
		bweak;
	case DC_SW_64KB_S_X:
		*sw_mode = dm_sw_64kb_s_x;
		bweak;
	case DC_SW_64KB_S_T:
		*sw_mode = dm_sw_64kb_s_t;
		bweak;
	case DC_SW_64KB_D:
		*sw_mode = dm_sw_64kb_d;
		bweak;
	case DC_SW_64KB_D_X:
		*sw_mode = dm_sw_64kb_d_x;
		bweak;
	case DC_SW_64KB_D_T:
		*sw_mode = dm_sw_64kb_d_t;
		bweak;
	case DC_SW_64KB_W_X:
		*sw_mode = dm_sw_64kb_w_x;
		bweak;
	case DC_SW_VAW_S:
		*sw_mode = dm_sw_vaw_s;
		bweak;
	case DC_SW_VAW_S_X:
		*sw_mode = dm_sw_vaw_s_x;
		bweak;
	case DC_SW_VAW_D:
		*sw_mode = dm_sw_vaw_d;
		bweak;
	case DC_SW_VAW_D_X:
		*sw_mode = dm_sw_vaw_d_x;
		bweak;
	case DC_SW_VAW_W_X:
		*sw_mode = dm_sw_vaw_w_x;
		bweak;
	defauwt:
		ASSEWT(0); /* Not suppowted */
		bweak;
	}
}

int dcn20_popuwate_dmw_pipes_fwom_context(stwuct dc *dc,
					  stwuct dc_state *context,
					  dispway_e2e_pipe_pawams_st *pipes,
					  boow fast_vawidate)
{
	int pipe_cnt, i;
	boow synchwonized_vbwank = twue;
	stwuct wesouwce_context *wes_ctx = &context->wes_ctx;

	dc_assewt_fp_enabwed();

	fow (i = 0, pipe_cnt = -1; i < dc->wes_poow->pipe_count; i++) {
		if (!wes_ctx->pipe_ctx[i].stweam)
			continue;

		if (pipe_cnt < 0) {
			pipe_cnt = i;
			continue;
		}

		if (wes_ctx->pipe_ctx[pipe_cnt].stweam == wes_ctx->pipe_ctx[i].stweam)
			continue;

		if (dc->debug.disabwe_timing_sync ||
			(!wesouwce_awe_stweams_timing_synchwonizabwe(
				wes_ctx->pipe_ctx[pipe_cnt].stweam,
				wes_ctx->pipe_ctx[i].stweam) &&
			!wesouwce_awe_vbwanks_synchwonizabwe(
				wes_ctx->pipe_ctx[pipe_cnt].stweam,
				wes_ctx->pipe_ctx[i].stweam))) {
			synchwonized_vbwank = fawse;
			bweak;
		}
	}

	fow (i = 0, pipe_cnt = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct dc_cwtc_timing *timing = &wes_ctx->pipe_ctx[i].stweam->timing;
		unsigned int v_totaw;
		unsigned int fwont_powch;
		int output_bpc;
		stwuct audio_check aud_check = {0};

		if (!wes_ctx->pipe_ctx[i].stweam)
			continue;

		v_totaw = timing->v_totaw;
		fwont_powch = timing->v_fwont_powch;

		/* todo:
		pipes[pipe_cnt].pipe.swc.dynamic_metadata_enabwe = 0;
		pipes[pipe_cnt].pipe.swc.dcc = 0;
		pipes[pipe_cnt].pipe.swc.vm = 0;*/

		pipes[pipe_cnt].cwks_cfg.wefcwk_mhz = dc->wes_poow->wef_cwocks.dchub_wef_cwock_inKhz / 1000.0;

		pipes[pipe_cnt].pipe.dest.use_maximum_vstawtup = dc->ctx->dce_vewsion == DCN_VEWSION_2_01;

		pipes[pipe_cnt].dout.dsc_enabwe = wes_ctx->pipe_ctx[i].stweam->timing.fwags.DSC;
		/* todo: wotation?*/
		pipes[pipe_cnt].dout.dsc_swices = wes_ctx->pipe_ctx[i].stweam->timing.dsc_cfg.num_swices_h;
		if (wes_ctx->pipe_ctx[i].stweam->use_dynamic_meta) {
			pipes[pipe_cnt].pipe.swc.dynamic_metadata_enabwe = twue;
			/* 1/2 vbwank */
			pipes[pipe_cnt].pipe.swc.dynamic_metadata_wines_befowe_active =
				(v_totaw - timing->v_addwessabwe
					- timing->v_bowdew_top - timing->v_bowdew_bottom) / 2;
			/* 36 bytes dp, 32 hdmi */
			pipes[pipe_cnt].pipe.swc.dynamic_metadata_xmit_bytes =
				dc_is_dp_signaw(wes_ctx->pipe_ctx[i].stweam->signaw) ? 36 : 32;
		}
		pipes[pipe_cnt].pipe.swc.dcc = fawse;
		pipes[pipe_cnt].pipe.swc.dcc_wate = 1;
		pipes[pipe_cnt].pipe.dest.synchwonized_vbwank_aww_pwanes = synchwonized_vbwank;
		pipes[pipe_cnt].pipe.dest.synchwonize_timings = synchwonized_vbwank;
		pipes[pipe_cnt].pipe.dest.hbwank_stawt = timing->h_totaw - timing->h_fwont_powch;
		pipes[pipe_cnt].pipe.dest.hbwank_end = pipes[pipe_cnt].pipe.dest.hbwank_stawt
				- timing->h_addwessabwe
				- timing->h_bowdew_weft
				- timing->h_bowdew_wight;
		pipes[pipe_cnt].pipe.dest.vbwank_stawt = v_totaw - fwont_powch;
		pipes[pipe_cnt].pipe.dest.vbwank_end = pipes[pipe_cnt].pipe.dest.vbwank_stawt
				- timing->v_addwessabwe
				- timing->v_bowdew_top
				- timing->v_bowdew_bottom;
		pipes[pipe_cnt].pipe.dest.htotaw = timing->h_totaw;
		pipes[pipe_cnt].pipe.dest.vtotaw = v_totaw;
		pipes[pipe_cnt].pipe.dest.hactive =
			timing->h_addwessabwe + timing->h_bowdew_weft + timing->h_bowdew_wight;
		pipes[pipe_cnt].pipe.dest.vactive =
			timing->v_addwessabwe + timing->v_bowdew_top + timing->v_bowdew_bottom;
		pipes[pipe_cnt].pipe.dest.intewwaced = timing->fwags.INTEWWACE;
		pipes[pipe_cnt].pipe.dest.pixew_wate_mhz = timing->pix_cwk_100hz/10000.0;
		if (timing->timing_3d_fowmat == TIMING_3D_FOWMAT_HW_FWAME_PACKING)
			pipes[pipe_cnt].pipe.dest.pixew_wate_mhz *= 2;
		pipes[pipe_cnt].pipe.dest.otg_inst = wes_ctx->pipe_ctx[i].stweam_wes.tg->inst;
		pipes[pipe_cnt].dout.dp_wanes = 4;
		pipes[pipe_cnt].dout.dp_wate = dm_dp_wate_na;
		pipes[pipe_cnt].dout.is_viwtuaw = 0;
		pipes[pipe_cnt].pipe.dest.vtotaw_min = wes_ctx->pipe_ctx[i].stweam->adjust.v_totaw_min;
		pipes[pipe_cnt].pipe.dest.vtotaw_max = wes_ctx->pipe_ctx[i].stweam->adjust.v_totaw_max;
		switch (wesouwce_get_odm_swice_count(&wes_ctx->pipe_ctx[i])) {
		case 2:
			pipes[pipe_cnt].pipe.dest.odm_combine = dm_odm_combine_mode_2to1;
			bweak;
		case 4:
			pipes[pipe_cnt].pipe.dest.odm_combine = dm_odm_combine_mode_4to1;
			bweak;
		defauwt:
			pipes[pipe_cnt].pipe.dest.odm_combine = dm_odm_combine_mode_disabwed;
		}
		pipes[pipe_cnt].pipe.swc.hspwit_gwp = wes_ctx->pipe_ctx[i].pipe_idx;
		if (wes_ctx->pipe_ctx[i].top_pipe && wes_ctx->pipe_ctx[i].top_pipe->pwane_state
				== wes_ctx->pipe_ctx[i].pwane_state) {
			stwuct pipe_ctx *fiwst_pipe = wes_ctx->pipe_ctx[i].top_pipe;
			int spwit_idx = 0;

			whiwe (fiwst_pipe->top_pipe && fiwst_pipe->top_pipe->pwane_state
					== wes_ctx->pipe_ctx[i].pwane_state) {
				fiwst_pipe = fiwst_pipe->top_pipe;
				spwit_idx++;
			}
			/* Tweat 4to1 mpc combine as an mpo of 2 2-to-1 combines */
			if (spwit_idx == 0)
				pipes[pipe_cnt].pipe.swc.hspwit_gwp = fiwst_pipe->pipe_idx;
			ewse if (spwit_idx == 1)
				pipes[pipe_cnt].pipe.swc.hspwit_gwp = wes_ctx->pipe_ctx[i].pipe_idx;
			ewse if (spwit_idx == 2)
				pipes[pipe_cnt].pipe.swc.hspwit_gwp = wes_ctx->pipe_ctx[i].top_pipe->pipe_idx;
		} ewse if (wes_ctx->pipe_ctx[i].pwev_odm_pipe) {
			stwuct pipe_ctx *fiwst_pipe = wes_ctx->pipe_ctx[i].pwev_odm_pipe;

			whiwe (fiwst_pipe->pwev_odm_pipe)
				fiwst_pipe = fiwst_pipe->pwev_odm_pipe;
			pipes[pipe_cnt].pipe.swc.hspwit_gwp = fiwst_pipe->pipe_idx;
		}

		switch (wes_ctx->pipe_ctx[i].stweam->signaw) {
		case SIGNAW_TYPE_DISPWAY_POWT_MST:
		case SIGNAW_TYPE_DISPWAY_POWT:
			pipes[pipe_cnt].dout.output_type = dm_dp;
			if (dc->wink_swv->dp_is_128b_132b_signaw(&wes_ctx->pipe_ctx[i]))
				pipes[pipe_cnt].dout.output_type = dm_dp2p0;
			bweak;
		case SIGNAW_TYPE_EDP:
			pipes[pipe_cnt].dout.output_type = dm_edp;
			bweak;
		case SIGNAW_TYPE_HDMI_TYPE_A:
		case SIGNAW_TYPE_DVI_SINGWE_WINK:
		case SIGNAW_TYPE_DVI_DUAW_WINK:
			pipes[pipe_cnt].dout.output_type = dm_hdmi;
			bweak;
		defauwt:
			/* In case thewe is no signaw, set dp with 4 wanes to awwow max config */
			pipes[pipe_cnt].dout.is_viwtuaw = 1;
			pipes[pipe_cnt].dout.output_type = dm_dp;
			pipes[pipe_cnt].dout.dp_wanes = 4;
		}

		switch (wes_ctx->pipe_ctx[i].stweam->timing.dispway_cowow_depth) {
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

		switch (wes_ctx->pipe_ctx[i].stweam->timing.pixew_encoding) {
		case PIXEW_ENCODING_WGB:
		case PIXEW_ENCODING_YCBCW444:
			pipes[pipe_cnt].dout.output_fowmat = dm_444;
			pipes[pipe_cnt].dout.output_bpp = output_bpc * 3;
			bweak;
		case PIXEW_ENCODING_YCBCW420:
			pipes[pipe_cnt].dout.output_fowmat = dm_420;
			pipes[pipe_cnt].dout.output_bpp = (output_bpc * 3.0) / 2;
			bweak;
		case PIXEW_ENCODING_YCBCW422:
			if (wes_ctx->pipe_ctx[i].stweam->timing.fwags.DSC &&
			    !wes_ctx->pipe_ctx[i].stweam->timing.dsc_cfg.ycbcw422_simpwe)
				pipes[pipe_cnt].dout.output_fowmat = dm_n422;
			ewse
				pipes[pipe_cnt].dout.output_fowmat = dm_s422;
			pipes[pipe_cnt].dout.output_bpp = output_bpc * 2;
			bweak;
		defauwt:
			pipes[pipe_cnt].dout.output_fowmat = dm_444;
			pipes[pipe_cnt].dout.output_bpp = output_bpc * 3;
		}

		if (wes_ctx->pipe_ctx[i].stweam->timing.fwags.DSC)
			pipes[pipe_cnt].dout.output_bpp = wes_ctx->pipe_ctx[i].stweam->timing.dsc_cfg.bits_pew_pixew / 16.0;

		/* todo: defauwt max fow now, untiw thewe is wogic wefwecting this in dc*/
		pipes[pipe_cnt].dout.dsc_input_bpc = 12;
		/*fiww up the audio sampwe wate (unit in kHz)*/
		get_audio_check(&wes_ctx->pipe_ctx[i].stweam->audio_info, &aud_check);
		pipes[pipe_cnt].dout.max_audio_sampwe_wate = aud_check.max_audiosampwe_wate / 1000;
		/*
		 * Fow gwaphic pwane, cuwsow numbew is 1, nv12 is 0
		 * bw cawcuwations due to cuwsow on/off
		 */
		if (wes_ctx->pipe_ctx[i].pwane_state &&
				(wes_ctx->pipe_ctx[i].pwane_state->addwess.type == PWN_ADDW_TYPE_VIDEO_PWOGWESSIVE ||
				dc_state_get_pipe_subvp_type(context, &wes_ctx->pipe_ctx[i]) == SUBVP_PHANTOM))
			pipes[pipe_cnt].pipe.swc.num_cuwsows = 0;
		ewse
			pipes[pipe_cnt].pipe.swc.num_cuwsows = dc->dmw.ip.numbew_of_cuwsows;

		pipes[pipe_cnt].pipe.swc.cuw0_swc_width = 256;
		pipes[pipe_cnt].pipe.swc.cuw0_bpp = dm_cuw_32bit;

		if (!wes_ctx->pipe_ctx[i].pwane_state) {
			pipes[pipe_cnt].pipe.swc.is_hspwit = pipes[pipe_cnt].pipe.dest.odm_combine != dm_odm_combine_mode_disabwed;
			pipes[pipe_cnt].pipe.swc.souwce_scan = dm_howz;
			pipes[pipe_cnt].pipe.swc.souwce_wotation = dm_wotation_0;
			pipes[pipe_cnt].pipe.swc.sw_mode = dm_sw_4kb_s;
			pipes[pipe_cnt].pipe.swc.macwo_tiwe_size = dm_64k_tiwe;
			pipes[pipe_cnt].pipe.swc.viewpowt_width = timing->h_addwessabwe;
			if (pipes[pipe_cnt].pipe.swc.viewpowt_width > 1920)
				pipes[pipe_cnt].pipe.swc.viewpowt_width = 1920;
			pipes[pipe_cnt].pipe.swc.viewpowt_height = timing->v_addwessabwe;
			if (pipes[pipe_cnt].pipe.swc.viewpowt_height > 1080)
				pipes[pipe_cnt].pipe.swc.viewpowt_height = 1080;
			pipes[pipe_cnt].pipe.swc.suwface_height_y = pipes[pipe_cnt].pipe.swc.viewpowt_height;
			pipes[pipe_cnt].pipe.swc.suwface_width_y = pipes[pipe_cnt].pipe.swc.viewpowt_width;
			pipes[pipe_cnt].pipe.swc.suwface_height_c = pipes[pipe_cnt].pipe.swc.viewpowt_height;
			pipes[pipe_cnt].pipe.swc.suwface_width_c = pipes[pipe_cnt].pipe.swc.viewpowt_width;
			pipes[pipe_cnt].pipe.swc.data_pitch = ((pipes[pipe_cnt].pipe.swc.viewpowt_width + 255) / 256) * 256;
			pipes[pipe_cnt].pipe.swc.souwce_fowmat = dm_444_32;
			pipes[pipe_cnt].pipe.dest.wecout_width = pipes[pipe_cnt].pipe.swc.viewpowt_width; /*vp_width/hwatio*/
			pipes[pipe_cnt].pipe.dest.wecout_height = pipes[pipe_cnt].pipe.swc.viewpowt_height; /*vp_height/vwatio*/
			pipes[pipe_cnt].pipe.dest.fuww_wecout_width = pipes[pipe_cnt].pipe.dest.wecout_width;  /*when is_hspwit != 1*/
			pipes[pipe_cnt].pipe.dest.fuww_wecout_height = pipes[pipe_cnt].pipe.dest.wecout_height; /*when is_hspwit != 1*/
			pipes[pipe_cnt].pipe.scawe_watio_depth.wb_depth = dm_wb_16;
			pipes[pipe_cnt].pipe.scawe_watio_depth.hscw_watio = 1.0;
			pipes[pipe_cnt].pipe.scawe_watio_depth.vscw_watio = 1.0;
			pipes[pipe_cnt].pipe.scawe_watio_depth.scw_enabwe = 0; /*Wb onwy ow Fuww scw*/
			pipes[pipe_cnt].pipe.scawe_taps.htaps = 1;
			pipes[pipe_cnt].pipe.scawe_taps.vtaps = 1;
			pipes[pipe_cnt].pipe.dest.vtotaw_min = v_totaw;
			pipes[pipe_cnt].pipe.dest.vtotaw_max = v_totaw;

			if (pipes[pipe_cnt].pipe.dest.odm_combine == dm_odm_combine_mode_2to1) {
				pipes[pipe_cnt].pipe.swc.viewpowt_width /= 2;
				pipes[pipe_cnt].pipe.dest.wecout_width /= 2;
			} ewse if (pipes[pipe_cnt].pipe.dest.odm_combine == dm_odm_combine_mode_4to1) {
				pipes[pipe_cnt].pipe.swc.viewpowt_width /= 4;
				pipes[pipe_cnt].pipe.dest.wecout_width /= 4;
			}
		} ewse {
			stwuct dc_pwane_state *pwn = wes_ctx->pipe_ctx[i].pwane_state;
			stwuct scawew_data *scw = &wes_ctx->pipe_ctx[i].pwane_wes.scw_data;

			pipes[pipe_cnt].pipe.swc.immediate_fwip = pwn->fwip_immediate;
			pipes[pipe_cnt].pipe.swc.is_hspwit = (wes_ctx->pipe_ctx[i].bottom_pipe && wes_ctx->pipe_ctx[i].bottom_pipe->pwane_state == pwn)
					|| (wes_ctx->pipe_ctx[i].top_pipe && wes_ctx->pipe_ctx[i].top_pipe->pwane_state == pwn)
					|| pipes[pipe_cnt].pipe.dest.odm_combine != dm_odm_combine_mode_disabwed;

			/* steweo is not spwit */
			if (pwn->steweo_fowmat == PWANE_STEWEO_FOWMAT_SIDE_BY_SIDE ||
			    pwn->steweo_fowmat == PWANE_STEWEO_FOWMAT_TOP_AND_BOTTOM) {
				pipes[pipe_cnt].pipe.swc.is_hspwit = fawse;
				pipes[pipe_cnt].pipe.swc.hspwit_gwp = wes_ctx->pipe_ctx[i].pipe_idx;
			}

			pipes[pipe_cnt].pipe.swc.souwce_scan = pwn->wotation == WOTATION_ANGWE_90
					|| pwn->wotation == WOTATION_ANGWE_270 ? dm_vewt : dm_howz;
			switch (pwn->wotation) {
			case WOTATION_ANGWE_0:
				pipes[pipe_cnt].pipe.swc.souwce_wotation = dm_wotation_0;
				bweak;
			case WOTATION_ANGWE_90:
				pipes[pipe_cnt].pipe.swc.souwce_wotation = dm_wotation_90;
				bweak;
			case WOTATION_ANGWE_180:
				pipes[pipe_cnt].pipe.swc.souwce_wotation = dm_wotation_180;
				bweak;
			case WOTATION_ANGWE_270:
				pipes[pipe_cnt].pipe.swc.souwce_wotation = dm_wotation_270;
				bweak;
			defauwt:
				bweak;
			}

			pipes[pipe_cnt].pipe.swc.viewpowt_y_y = scw->viewpowt.y;
			pipes[pipe_cnt].pipe.swc.viewpowt_y_c = scw->viewpowt_c.y;
			pipes[pipe_cnt].pipe.swc.viewpowt_x_y = scw->viewpowt.x;
			pipes[pipe_cnt].pipe.swc.viewpowt_x_c = scw->viewpowt_c.x;
			pipes[pipe_cnt].pipe.swc.viewpowt_width = scw->viewpowt.width;
			pipes[pipe_cnt].pipe.swc.viewpowt_width_c = scw->viewpowt_c.width;
			pipes[pipe_cnt].pipe.swc.viewpowt_height = scw->viewpowt.height;
			pipes[pipe_cnt].pipe.swc.viewpowt_height_c = scw->viewpowt_c.height;
			pipes[pipe_cnt].pipe.swc.viewpowt_width_max = pwn->swc_wect.width;
			pipes[pipe_cnt].pipe.swc.viewpowt_height_max = pwn->swc_wect.height;
			pipes[pipe_cnt].pipe.swc.suwface_width_y = pwn->pwane_size.suwface_size.width;
			pipes[pipe_cnt].pipe.swc.suwface_height_y = pwn->pwane_size.suwface_size.height;
			pipes[pipe_cnt].pipe.swc.suwface_width_c = pwn->pwane_size.chwoma_size.width;
			pipes[pipe_cnt].pipe.swc.suwface_height_c = pwn->pwane_size.chwoma_size.height;
			if (pwn->fowmat == SUWFACE_PIXEW_FOWMAT_GWPH_WGBE_AWPHA
					|| pwn->fowmat >= SUWFACE_PIXEW_FOWMAT_VIDEO_BEGIN) {
				pipes[pipe_cnt].pipe.swc.data_pitch = pwn->pwane_size.suwface_pitch;
				pipes[pipe_cnt].pipe.swc.data_pitch_c = pwn->pwane_size.chwoma_pitch;
				pipes[pipe_cnt].pipe.swc.meta_pitch = pwn->dcc.meta_pitch;
				pipes[pipe_cnt].pipe.swc.meta_pitch_c = pwn->dcc.meta_pitch_c;
			} ewse {
				pipes[pipe_cnt].pipe.swc.data_pitch = pwn->pwane_size.suwface_pitch;
				pipes[pipe_cnt].pipe.swc.meta_pitch = pwn->dcc.meta_pitch;
			}
			pipes[pipe_cnt].pipe.swc.dcc = pwn->dcc.enabwe;
			pipes[pipe_cnt].pipe.dest.wecout_width = scw->wecout.width;
			pipes[pipe_cnt].pipe.dest.wecout_height = scw->wecout.height;
			pipes[pipe_cnt].pipe.dest.fuww_wecout_height = scw->wecout.height;
			pipes[pipe_cnt].pipe.dest.fuww_wecout_width = scw->wecout.width;
			if (pipes[pipe_cnt].pipe.dest.odm_combine == dm_odm_combine_mode_2to1)
				pipes[pipe_cnt].pipe.dest.fuww_wecout_width *= 2;
			ewse if (pipes[pipe_cnt].pipe.dest.odm_combine == dm_odm_combine_mode_4to1)
				pipes[pipe_cnt].pipe.dest.fuww_wecout_width *= 4;
			ewse {
				stwuct pipe_ctx *spwit_pipe = wes_ctx->pipe_ctx[i].bottom_pipe;

				whiwe (spwit_pipe && spwit_pipe->pwane_state == pwn) {
					pipes[pipe_cnt].pipe.dest.fuww_wecout_width += spwit_pipe->pwane_wes.scw_data.wecout.width;
					spwit_pipe = spwit_pipe->bottom_pipe;
				}
				spwit_pipe = wes_ctx->pipe_ctx[i].top_pipe;
				whiwe (spwit_pipe && spwit_pipe->pwane_state == pwn) {
					pipes[pipe_cnt].pipe.dest.fuww_wecout_width += spwit_pipe->pwane_wes.scw_data.wecout.width;
					spwit_pipe = spwit_pipe->top_pipe;
				}
			}

			pipes[pipe_cnt].pipe.scawe_watio_depth.wb_depth = dm_wb_16;
			pipes[pipe_cnt].pipe.scawe_watio_depth.hscw_watio = (doubwe) scw->watios.howz.vawue / (1UWW<<32);
			pipes[pipe_cnt].pipe.scawe_watio_depth.hscw_watio_c = (doubwe) scw->watios.howz_c.vawue / (1UWW<<32);
			pipes[pipe_cnt].pipe.scawe_watio_depth.vscw_watio = (doubwe) scw->watios.vewt.vawue / (1UWW<<32);
			pipes[pipe_cnt].pipe.scawe_watio_depth.vscw_watio_c = (doubwe) scw->watios.vewt_c.vawue / (1UWW<<32);
			pipes[pipe_cnt].pipe.scawe_watio_depth.scw_enabwe =
					scw->watios.vewt.vawue != dc_fixpt_one.vawue
					|| scw->watios.howz.vawue != dc_fixpt_one.vawue
					|| scw->watios.vewt_c.vawue != dc_fixpt_one.vawue
					|| scw->watios.howz_c.vawue != dc_fixpt_one.vawue /*Wb onwy ow Fuww scw*/
					|| dc->debug.awways_scawe; /*suppowt awways scawe*/
			pipes[pipe_cnt].pipe.scawe_taps.htaps = scw->taps.h_taps;
			pipes[pipe_cnt].pipe.scawe_taps.htaps_c = scw->taps.h_taps_c;
			pipes[pipe_cnt].pipe.scawe_taps.vtaps = scw->taps.v_taps;
			pipes[pipe_cnt].pipe.scawe_taps.vtaps_c = scw->taps.v_taps_c;

			pipes[pipe_cnt].pipe.swc.macwo_tiwe_size =
					swizzwe_mode_to_macwo_tiwe_size(pwn->tiwing_info.gfx9.swizzwe);
			swizzwe_to_dmw_pawams(pwn->tiwing_info.gfx9.swizzwe,
					&pipes[pipe_cnt].pipe.swc.sw_mode);

			switch (pwn->fowmat) {
			case SUWFACE_PIXEW_FOWMAT_VIDEO_420_YCbCw:
			case SUWFACE_PIXEW_FOWMAT_VIDEO_420_YCwCb:
				pipes[pipe_cnt].pipe.swc.souwce_fowmat = dm_420_8;
				bweak;
			case SUWFACE_PIXEW_FOWMAT_VIDEO_420_10bpc_YCbCw:
			case SUWFACE_PIXEW_FOWMAT_VIDEO_420_10bpc_YCwCb:
				pipes[pipe_cnt].pipe.swc.souwce_fowmat = dm_420_10;
				bweak;
			case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB16161616:
			case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW16161616:
			case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB16161616F:
			case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW16161616F:
				pipes[pipe_cnt].pipe.swc.souwce_fowmat = dm_444_64;
				bweak;
			case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB1555:
			case SUWFACE_PIXEW_FOWMAT_GWPH_WGB565:
				pipes[pipe_cnt].pipe.swc.souwce_fowmat = dm_444_16;
				bweak;
			case SUWFACE_PIXEW_FOWMAT_GWPH_PAWETA_256_COWOWS:
				pipes[pipe_cnt].pipe.swc.souwce_fowmat = dm_444_8;
				bweak;
			case SUWFACE_PIXEW_FOWMAT_GWPH_WGBE_AWPHA:
				pipes[pipe_cnt].pipe.swc.souwce_fowmat = dm_wgbe_awpha;
				bweak;
			defauwt:
				pipes[pipe_cnt].pipe.swc.souwce_fowmat = dm_444_32;
				bweak;
			}
		}

		pipe_cnt++;
	}

	/* popuwate wwiteback infowmation */
	dc->wes_poow->funcs->popuwate_dmw_wwiteback_fwom_context(dc, wes_ctx, pipes);

	wetuwn pipe_cnt;
}

void dcn20_cawcuwate_wm(stwuct dc *dc, stwuct dc_state *context,
			dispway_e2e_pipe_pawams_st *pipes,
			int *out_pipe_cnt,
			int *pipe_spwit_fwom,
			int vwevew,
			boow fast_vawidate)
{
	int pipe_cnt, i, pipe_idx;

	dc_assewt_fp_enabwed();

	fow (i = 0, pipe_idx = 0, pipe_cnt = 0; i < dc->wes_poow->pipe_count; i++) {
		if (!context->wes_ctx.pipe_ctx[i].stweam)
			continue;

		pipes[pipe_cnt].cwks_cfg.wefcwk_mhz = dc->wes_poow->wef_cwocks.dchub_wef_cwock_inKhz / 1000.0;
		pipes[pipe_cnt].cwks_cfg.dispcwk_mhz = context->bw_ctx.dmw.vba.WequiwedDISPCWK[vwevew][context->bw_ctx.dmw.vba.maxMpcComb];

		if (pipe_spwit_fwom[i] < 0) {
			pipes[pipe_cnt].cwks_cfg.dppcwk_mhz =
					context->bw_ctx.dmw.vba.WequiwedDPPCWK[vwevew][context->bw_ctx.dmw.vba.maxMpcComb][pipe_idx];
			if (context->bw_ctx.dmw.vba.BwendingAndTiming[pipe_idx] == pipe_idx)
				pipes[pipe_cnt].pipe.dest.odm_combine =
						context->bw_ctx.dmw.vba.ODMCombineEnabwed[pipe_idx];
			ewse
				pipes[pipe_cnt].pipe.dest.odm_combine = 0;
			pipe_idx++;
		} ewse {
			pipes[pipe_cnt].cwks_cfg.dppcwk_mhz =
					context->bw_ctx.dmw.vba.WequiwedDPPCWK[vwevew][context->bw_ctx.dmw.vba.maxMpcComb][pipe_spwit_fwom[i]];
			if (context->bw_ctx.dmw.vba.BwendingAndTiming[pipe_spwit_fwom[i]] == pipe_spwit_fwom[i])
				pipes[pipe_cnt].pipe.dest.odm_combine =
						context->bw_ctx.dmw.vba.ODMCombineEnabwed[pipe_spwit_fwom[i]];
			ewse
				pipes[pipe_cnt].pipe.dest.odm_combine = 0;
		}

		if (dc->config.fowced_cwocks) {
			pipes[pipe_cnt].cwks_cfg.dispcwk_mhz = context->bw_ctx.dmw.soc.cwock_wimits[0].dispcwk_mhz;
			pipes[pipe_cnt].cwks_cfg.dppcwk_mhz = context->bw_ctx.dmw.soc.cwock_wimits[0].dppcwk_mhz;
		}
		if (dc->debug.min_disp_cwk_khz > pipes[pipe_cnt].cwks_cfg.dispcwk_mhz * 1000)
			pipes[pipe_cnt].cwks_cfg.dispcwk_mhz = dc->debug.min_disp_cwk_khz / 1000.0;
		if (dc->debug.min_dpp_cwk_khz > pipes[pipe_cnt].cwks_cfg.dppcwk_mhz * 1000)
			pipes[pipe_cnt].cwks_cfg.dppcwk_mhz = dc->debug.min_dpp_cwk_khz / 1000.0;

		pipe_cnt++;
	}

	if (pipe_cnt != pipe_idx) {
		if (dc->wes_poow->funcs->popuwate_dmw_pipes)
			pipe_cnt = dc->wes_poow->funcs->popuwate_dmw_pipes(dc,
				context, pipes, fast_vawidate);
		ewse
			pipe_cnt = dcn20_popuwate_dmw_pipes_fwom_context(dc,
				context, pipes, fast_vawidate);
	}

	*out_pipe_cnt = pipe_cnt;

	pipes[0].cwks_cfg.vowtage = vwevew;
	pipes[0].cwks_cfg.dcfcwk_mhz = context->bw_ctx.dmw.soc.cwock_wimits[vwevew].dcfcwk_mhz;
	pipes[0].cwks_cfg.soccwk_mhz = context->bw_ctx.dmw.soc.cwock_wimits[vwevew].soccwk_mhz;

	/* onwy pipe 0 is wead fow vowtage and dcf/soc cwocks */
	if (vwevew < 1) {
		pipes[0].cwks_cfg.vowtage = 1;
		pipes[0].cwks_cfg.dcfcwk_mhz = context->bw_ctx.dmw.soc.cwock_wimits[1].dcfcwk_mhz;
		pipes[0].cwks_cfg.soccwk_mhz = context->bw_ctx.dmw.soc.cwock_wimits[1].soccwk_mhz;
	}
	context->bw_ctx.bw.dcn.watewmawks.b.uwgent_ns = get_wm_uwgent(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.b.cstate_pstate.cstate_entew_pwus_exit_ns = get_wm_stuttew_entew_exit(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.b.cstate_pstate.cstate_exit_ns = get_wm_stuttew_exit(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.b.cstate_pstate.pstate_change_ns = get_wm_dwam_cwock_change(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.b.pte_meta_uwgent_ns = get_wm_memowy_twip(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.b.fwac_uwg_bw_nom = get_fwaction_of_uwgent_bandwidth(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.b.fwac_uwg_bw_fwip = get_fwaction_of_uwgent_bandwidth_imm_fwip(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.b.uwgent_watency_ns = get_uwgent_watency(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;

	if (vwevew < 2) {
		pipes[0].cwks_cfg.vowtage = 2;
		pipes[0].cwks_cfg.dcfcwk_mhz = context->bw_ctx.dmw.soc.cwock_wimits[2].dcfcwk_mhz;
		pipes[0].cwks_cfg.soccwk_mhz = context->bw_ctx.dmw.soc.cwock_wimits[2].soccwk_mhz;
	}
	context->bw_ctx.bw.dcn.watewmawks.c.uwgent_ns = get_wm_uwgent(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.c.cstate_pstate.cstate_entew_pwus_exit_ns = get_wm_stuttew_entew_exit(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.c.cstate_pstate.cstate_exit_ns = get_wm_stuttew_exit(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.c.cstate_pstate.pstate_change_ns = get_wm_dwam_cwock_change(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.c.pte_meta_uwgent_ns = get_wm_memowy_twip(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.c.fwac_uwg_bw_nom = get_fwaction_of_uwgent_bandwidth(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.c.fwac_uwg_bw_fwip = get_fwaction_of_uwgent_bandwidth_imm_fwip(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;

	if (vwevew < 3) {
		pipes[0].cwks_cfg.vowtage = 3;
		pipes[0].cwks_cfg.dcfcwk_mhz = context->bw_ctx.dmw.soc.cwock_wimits[2].dcfcwk_mhz;
		pipes[0].cwks_cfg.soccwk_mhz = context->bw_ctx.dmw.soc.cwock_wimits[2].soccwk_mhz;
	}
	context->bw_ctx.bw.dcn.watewmawks.d.uwgent_ns = get_wm_uwgent(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.d.cstate_pstate.cstate_entew_pwus_exit_ns = get_wm_stuttew_entew_exit(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.d.cstate_pstate.cstate_exit_ns = get_wm_stuttew_exit(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.d.cstate_pstate.pstate_change_ns = get_wm_dwam_cwock_change(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.d.pte_meta_uwgent_ns = get_wm_memowy_twip(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.d.fwac_uwg_bw_nom = get_fwaction_of_uwgent_bandwidth(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.d.fwac_uwg_bw_fwip = get_fwaction_of_uwgent_bandwidth_imm_fwip(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;

	pipes[0].cwks_cfg.vowtage = vwevew;
	pipes[0].cwks_cfg.dcfcwk_mhz = context->bw_ctx.dmw.soc.cwock_wimits[vwevew].dcfcwk_mhz;
	pipes[0].cwks_cfg.soccwk_mhz = context->bw_ctx.dmw.soc.cwock_wimits[vwevew].soccwk_mhz;
	context->bw_ctx.bw.dcn.watewmawks.a.uwgent_ns = get_wm_uwgent(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.a.cstate_pstate.cstate_entew_pwus_exit_ns = get_wm_stuttew_entew_exit(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.a.cstate_pstate.cstate_exit_ns = get_wm_stuttew_exit(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.a.cstate_pstate.pstate_change_ns = get_wm_dwam_cwock_change(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.a.pte_meta_uwgent_ns = get_wm_memowy_twip(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.a.fwac_uwg_bw_nom = get_fwaction_of_uwgent_bandwidth(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watewmawks.a.fwac_uwg_bw_fwip = get_fwaction_of_uwgent_bandwidth_imm_fwip(&context->bw_ctx.dmw, pipes, pipe_cnt) * 1000;
}

void dcn20_update_bounding_box(stwuct dc *dc,
			       stwuct _vcs_dpi_soc_bounding_box_st *bb,
			       stwuct pp_smu_nv_cwock_tabwe *max_cwocks,
			       unsigned int *ucwk_states,
			       unsigned int num_states)
{
	int num_cawcuwated_states = 0;
	int min_dcfcwk = 0;
	int i;

	dc_assewt_fp_enabwed();

	if (num_states == 0)
		wetuwn;

	memset(bb->cwock_wimits, 0, sizeof(bb->cwock_wimits));

	if (dc->bb_ovewwides.min_dcfcwk_mhz > 0) {
		min_dcfcwk = dc->bb_ovewwides.min_dcfcwk_mhz;
	} ewse {
		if (ASICWEV_IS_NAVI12_P(dc->ctx->asic_id.hw_intewnaw_wev))
			min_dcfcwk = 310;
		ewse
			// Accounting fow SOC/DCF wewationship, we can go as high as
			// 506Mhz in Vmin.
			min_dcfcwk = 506;
	}

	fow (i = 0; i < num_states; i++) {
		int min_fcwk_wequiwed_by_ucwk;
		bb->cwock_wimits[i].state = i;
		bb->cwock_wimits[i].dwam_speed_mts = ucwk_states[i] * 16 / 1000;

		// FCWK:UCWK watio is 1.08
		min_fcwk_wequiwed_by_ucwk = div_u64(((unsigned wong wong)ucwk_states[i]) * 1080,
			1000000);

		bb->cwock_wimits[i].fabwiccwk_mhz = (min_fcwk_wequiwed_by_ucwk < min_dcfcwk) ?
				min_dcfcwk : min_fcwk_wequiwed_by_ucwk;

		bb->cwock_wimits[i].soccwk_mhz = (bb->cwock_wimits[i].fabwiccwk_mhz > max_cwocks->socCwockInKhz / 1000) ?
				max_cwocks->socCwockInKhz / 1000 : bb->cwock_wimits[i].fabwiccwk_mhz;

		bb->cwock_wimits[i].dcfcwk_mhz = (bb->cwock_wimits[i].fabwiccwk_mhz > max_cwocks->dcfCwockInKhz / 1000) ?
				max_cwocks->dcfCwockInKhz / 1000 : bb->cwock_wimits[i].fabwiccwk_mhz;

		bb->cwock_wimits[i].dispcwk_mhz = max_cwocks->dispwayCwockInKhz / 1000;
		bb->cwock_wimits[i].dppcwk_mhz = max_cwocks->dispwayCwockInKhz / 1000;
		bb->cwock_wimits[i].dsccwk_mhz = max_cwocks->dispwayCwockInKhz / (1000 * 3);

		bb->cwock_wimits[i].phycwk_mhz = max_cwocks->phyCwockInKhz / 1000;

		num_cawcuwated_states++;
	}

	bb->cwock_wimits[num_cawcuwated_states - 1].soccwk_mhz = max_cwocks->socCwockInKhz / 1000;
	bb->cwock_wimits[num_cawcuwated_states - 1].fabwiccwk_mhz = max_cwocks->socCwockInKhz / 1000;
	bb->cwock_wimits[num_cawcuwated_states - 1].dcfcwk_mhz = max_cwocks->dcfCwockInKhz / 1000;

	bb->num_states = num_cawcuwated_states;

	// Dupwicate the wast state, DMW awways an extwa state identicaw to max state to wowk
	memcpy(&bb->cwock_wimits[num_cawcuwated_states], &bb->cwock_wimits[num_cawcuwated_states - 1], sizeof(stwuct _vcs_dpi_vowtage_scawing_st));
	bb->cwock_wimits[num_cawcuwated_states].state = bb->num_states;
}

void dcn20_cap_soc_cwocks(stwuct _vcs_dpi_soc_bounding_box_st *bb,
			  stwuct pp_smu_nv_cwock_tabwe max_cwocks)
{
	int i;

	dc_assewt_fp_enabwed();

	// Fiwst pass - cap aww cwocks highew than the wepowted max
	fow (i = 0; i < bb->num_states; i++) {
		if ((bb->cwock_wimits[i].dcfcwk_mhz > (max_cwocks.dcfCwockInKhz / 1000))
				&& max_cwocks.dcfCwockInKhz != 0)
			bb->cwock_wimits[i].dcfcwk_mhz = (max_cwocks.dcfCwockInKhz / 1000);

		if ((bb->cwock_wimits[i].dwam_speed_mts > (max_cwocks.uCwockInKhz / 1000) * 16)
						&& max_cwocks.uCwockInKhz != 0)
			bb->cwock_wimits[i].dwam_speed_mts = (max_cwocks.uCwockInKhz / 1000) * 16;

		if ((bb->cwock_wimits[i].fabwiccwk_mhz > (max_cwocks.fabwicCwockInKhz / 1000))
						&& max_cwocks.fabwicCwockInKhz != 0)
			bb->cwock_wimits[i].fabwiccwk_mhz = (max_cwocks.fabwicCwockInKhz / 1000);

		if ((bb->cwock_wimits[i].dispcwk_mhz > (max_cwocks.dispwayCwockInKhz / 1000))
						&& max_cwocks.dispwayCwockInKhz != 0)
			bb->cwock_wimits[i].dispcwk_mhz = (max_cwocks.dispwayCwockInKhz / 1000);

		if ((bb->cwock_wimits[i].dppcwk_mhz > (max_cwocks.dppCwockInKhz / 1000))
						&& max_cwocks.dppCwockInKhz != 0)
			bb->cwock_wimits[i].dppcwk_mhz = (max_cwocks.dppCwockInKhz / 1000);

		if ((bb->cwock_wimits[i].phycwk_mhz > (max_cwocks.phyCwockInKhz / 1000))
						&& max_cwocks.phyCwockInKhz != 0)
			bb->cwock_wimits[i].phycwk_mhz = (max_cwocks.phyCwockInKhz / 1000);

		if ((bb->cwock_wimits[i].soccwk_mhz > (max_cwocks.socCwockInKhz / 1000))
						&& max_cwocks.socCwockInKhz != 0)
			bb->cwock_wimits[i].soccwk_mhz = (max_cwocks.socCwockInKhz / 1000);

		if ((bb->cwock_wimits[i].dsccwk_mhz > (max_cwocks.dscCwockInKhz / 1000))
						&& max_cwocks.dscCwockInKhz != 0)
			bb->cwock_wimits[i].dsccwk_mhz = (max_cwocks.dscCwockInKhz / 1000);
	}

	// Second pass - wemove aww dupwicate cwock states
	fow (i = bb->num_states - 1; i > 1; i--) {
		boow dupwicate = twue;

		if (bb->cwock_wimits[i-1].dcfcwk_mhz != bb->cwock_wimits[i].dcfcwk_mhz)
			dupwicate = fawse;
		if (bb->cwock_wimits[i-1].dispcwk_mhz != bb->cwock_wimits[i].dispcwk_mhz)
			dupwicate = fawse;
		if (bb->cwock_wimits[i-1].dppcwk_mhz != bb->cwock_wimits[i].dppcwk_mhz)
			dupwicate = fawse;
		if (bb->cwock_wimits[i-1].dwam_speed_mts != bb->cwock_wimits[i].dwam_speed_mts)
			dupwicate = fawse;
		if (bb->cwock_wimits[i-1].dsccwk_mhz != bb->cwock_wimits[i].dsccwk_mhz)
			dupwicate = fawse;
		if (bb->cwock_wimits[i-1].fabwiccwk_mhz != bb->cwock_wimits[i].fabwiccwk_mhz)
			dupwicate = fawse;
		if (bb->cwock_wimits[i-1].phycwk_mhz != bb->cwock_wimits[i].phycwk_mhz)
			dupwicate = fawse;
		if (bb->cwock_wimits[i-1].soccwk_mhz != bb->cwock_wimits[i].soccwk_mhz)
			dupwicate = fawse;

		if (dupwicate)
			bb->num_states--;
	}
}

void dcn20_patch_bounding_box(stwuct dc *dc, stwuct _vcs_dpi_soc_bounding_box_st *bb)
{
	dc_assewt_fp_enabwed();

	if ((int)(bb->sw_exit_time_us * 1000) != dc->bb_ovewwides.sw_exit_time_ns
			&& dc->bb_ovewwides.sw_exit_time_ns) {
		bb->sw_exit_time_us = dc->bb_ovewwides.sw_exit_time_ns / 1000.0;
	}

	if ((int)(bb->sw_entew_pwus_exit_time_us * 1000)
				!= dc->bb_ovewwides.sw_entew_pwus_exit_time_ns
			&& dc->bb_ovewwides.sw_entew_pwus_exit_time_ns) {
		bb->sw_entew_pwus_exit_time_us =
				dc->bb_ovewwides.sw_entew_pwus_exit_time_ns / 1000.0;
	}

	if ((int)(bb->sw_exit_z8_time_us * 1000)
				!= dc->bb_ovewwides.sw_exit_z8_time_ns
			&& dc->bb_ovewwides.sw_exit_z8_time_ns) {
		bb->sw_exit_z8_time_us = dc->bb_ovewwides.sw_exit_z8_time_ns / 1000.0;
	}

	if ((int)(bb->sw_entew_pwus_exit_z8_time_us * 1000)
				!= dc->bb_ovewwides.sw_entew_pwus_exit_z8_time_ns
			&& dc->bb_ovewwides.sw_entew_pwus_exit_z8_time_ns) {
		bb->sw_entew_pwus_exit_z8_time_us = dc->bb_ovewwides.sw_entew_pwus_exit_z8_time_ns / 1000.0;
	}
	if ((int)(bb->uwgent_watency_us * 1000) != dc->bb_ovewwides.uwgent_watency_ns
			&& dc->bb_ovewwides.uwgent_watency_ns) {
		bb->uwgent_watency_us = dc->bb_ovewwides.uwgent_watency_ns / 1000.0;
	}

	if ((int)(bb->dwam_cwock_change_watency_us * 1000)
				!= dc->bb_ovewwides.dwam_cwock_change_watency_ns
			&& dc->bb_ovewwides.dwam_cwock_change_watency_ns) {
		bb->dwam_cwock_change_watency_us =
				dc->bb_ovewwides.dwam_cwock_change_watency_ns / 1000.0;
	}

	if ((int)(bb->dummy_pstate_watency_us * 1000)
				!= dc->bb_ovewwides.dummy_cwock_change_watency_ns
			&& dc->bb_ovewwides.dummy_cwock_change_watency_ns) {
		bb->dummy_pstate_watency_us =
				dc->bb_ovewwides.dummy_cwock_change_watency_ns / 1000.0;
	}
}

static boow dcn20_vawidate_bandwidth_intewnaw(stwuct dc *dc, stwuct dc_state *context,
		boow fast_vawidate, dispway_e2e_pipe_pawams_st *pipes)
{
	boow out = fawse;

	BW_VAW_TWACE_SETUP();

	int vwevew = 0;
	int pipe_spwit_fwom[MAX_PIPES];
	int pipe_cnt = 0;
	DC_WOGGEW_INIT(dc->ctx->woggew);

	BW_VAW_TWACE_COUNT();

	out = dcn20_fast_vawidate_bw(dc, context, pipes, &pipe_cnt, pipe_spwit_fwom, &vwevew, fast_vawidate);

	if (pipe_cnt == 0)
		goto vawidate_out;

	if (!out)
		goto vawidate_faiw;

	BW_VAW_TWACE_END_VOWTAGE_WEVEW();

	if (fast_vawidate) {
		BW_VAW_TWACE_SKIP(fast);
		goto vawidate_out;
	}

	dcn20_cawcuwate_wm(dc, context, pipes, &pipe_cnt, pipe_spwit_fwom, vwevew, fast_vawidate);
	dcn20_cawcuwate_dwg_pawams(dc, context, pipes, pipe_cnt, vwevew);

	BW_VAW_TWACE_END_WATEWMAWKS();

	goto vawidate_out;

vawidate_faiw:
	DC_WOG_WAWNING("Mode Vawidation Wawning: %s faiwed vawidation.\n",
		dmw_get_status_message(context->bw_ctx.dmw.vba.VawidationStatus[context->bw_ctx.dmw.vba.soc.num_states]));

	BW_VAW_TWACE_SKIP(faiw);
	out = fawse;

vawidate_out:

	BW_VAW_TWACE_FINISH();

	wetuwn out;
}

boow dcn20_vawidate_bandwidth_fp(stwuct dc *dc, stwuct dc_state *context,
				 boow fast_vawidate, dispway_e2e_pipe_pawams_st *pipes)
{
	boow vowtage_suppowted = fawse;
	boow fuww_pstate_suppowted = fawse;
	boow dummy_pstate_suppowted = fawse;
	doubwe p_state_watency_us;

	dc_assewt_fp_enabwed();

	p_state_watency_us = context->bw_ctx.dmw.soc.dwam_cwock_change_watency_us;
	context->bw_ctx.dmw.soc.disabwe_dwam_cwock_change_vactive_suppowt =
		dc->debug.disabwe_dwam_cwock_change_vactive_suppowt;
	context->bw_ctx.dmw.soc.awwow_dwam_cwock_one_dispway_vactive =
		dc->debug.enabwe_dwam_cwock_change_one_dispway_vactive;

	/*Unsafe due to cuwwent pipe mewge and spwit wogic*/
	ASSEWT(context != dc->cuwwent_state);

	if (fast_vawidate) {
		wetuwn dcn20_vawidate_bandwidth_intewnaw(dc, context, twue, pipes);
	}

	// Best case, we suppowt fuww UCWK switch watency
	vowtage_suppowted = dcn20_vawidate_bandwidth_intewnaw(dc, context, fawse, pipes);
	fuww_pstate_suppowted = context->bw_ctx.bw.dcn.cwk.p_state_change_suppowt;

	if (context->bw_ctx.dmw.soc.dummy_pstate_watency_us == 0 ||
		(vowtage_suppowted && fuww_pstate_suppowted)) {
		context->bw_ctx.bw.dcn.cwk.p_state_change_suppowt = fuww_pstate_suppowted;
		goto westowe_dmw_state;
	}

	// Fawwback: Twy to onwy suppowt G6 tempewatuwe wead watency
	context->bw_ctx.dmw.soc.dwam_cwock_change_watency_us = context->bw_ctx.dmw.soc.dummy_pstate_watency_us;

	memset(pipes, 0, dc->wes_poow->pipe_count * sizeof(dispway_e2e_pipe_pawams_st));
	vowtage_suppowted = dcn20_vawidate_bandwidth_intewnaw(dc, context, fawse, pipes);
	dummy_pstate_suppowted = context->bw_ctx.bw.dcn.cwk.p_state_change_suppowt;

	if (vowtage_suppowted && (dummy_pstate_suppowted || !(context->stweam_count))) {
		context->bw_ctx.bw.dcn.cwk.p_state_change_suppowt = fawse;
		goto westowe_dmw_state;
	}

	// EWWOW: fawwback is supposed to awways wowk.
	ASSEWT(fawse);

westowe_dmw_state:
	context->bw_ctx.dmw.soc.dwam_cwock_change_watency_us = p_state_watency_us;
	wetuwn vowtage_suppowted;
}

void dcn20_fpu_set_wm_wanges(int i,
			     stwuct pp_smu_wm_wange_sets *wanges,
			     stwuct _vcs_dpi_soc_bounding_box_st *woaded_bb)
{
	dc_assewt_fp_enabwed();

	wanges->weadew_wm_sets[i].min_fiww_cwk_mhz = (i > 0) ? (woaded_bb->cwock_wimits[i - 1].dwam_speed_mts / 16) + 1 : 0;
	wanges->weadew_wm_sets[i].max_fiww_cwk_mhz = woaded_bb->cwock_wimits[i].dwam_speed_mts / 16;
}

void dcn20_fpu_adjust_dppcwk(stwuct vba_vaws_st *v,
			     int vwevew,
			     int max_mpc_comb,
			     int pipe_idx,
			     boow is_vawidating_bw)
{
	dc_assewt_fp_enabwed();

	if (is_vawidating_bw)
		v->WequiwedDPPCWK[vwevew][max_mpc_comb][pipe_idx] *= 2;
	ewse
		v->WequiwedDPPCWK[vwevew][max_mpc_comb][pipe_idx] /= 2;
}

int dcn21_popuwate_dmw_pipes_fwom_context(stwuct dc *dc,
					  stwuct dc_state *context,
					  dispway_e2e_pipe_pawams_st *pipes,
					  boow fast_vawidate)
{
	uint32_t pipe_cnt;
	int i;

	dc_assewt_fp_enabwed();

	pipe_cnt = dcn20_popuwate_dmw_pipes_fwom_context(dc, context, pipes, fast_vawidate);

	fow (i = 0; i < pipe_cnt; i++) {

		pipes[i].pipe.swc.hostvm = dc->wes_poow->hubbub->wiommu_active;
		pipes[i].pipe.swc.gpuvm = 1;
	}

	wetuwn pipe_cnt;
}

static void patch_bounding_box(stwuct dc *dc, stwuct _vcs_dpi_soc_bounding_box_st *bb)
{
	int i;

	if (dc->bb_ovewwides.sw_exit_time_ns) {
		fow (i = 0; i < WM_SET_COUNT; i++) {
			  dc->cwk_mgw->bw_pawams->wm_tabwe.entwies[i].sw_exit_time_us =
					  dc->bb_ovewwides.sw_exit_time_ns / 1000.0;
		}
	}

	if (dc->bb_ovewwides.sw_entew_pwus_exit_time_ns) {
		fow (i = 0; i < WM_SET_COUNT; i++) {
			  dc->cwk_mgw->bw_pawams->wm_tabwe.entwies[i].sw_entew_pwus_exit_time_us =
					  dc->bb_ovewwides.sw_entew_pwus_exit_time_ns / 1000.0;
		}
	}

	if (dc->bb_ovewwides.uwgent_watency_ns) {
		bb->uwgent_watency_us = dc->bb_ovewwides.uwgent_watency_ns / 1000.0;
	}

	if (dc->bb_ovewwides.dwam_cwock_change_watency_ns) {
		fow (i = 0; i < WM_SET_COUNT; i++) {
			dc->cwk_mgw->bw_pawams->wm_tabwe.entwies[i].pstate_watency_us =
				dc->bb_ovewwides.dwam_cwock_change_watency_ns / 1000.0;
		}
	}
}

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

static void dcn21_cawcuwate_wm(stwuct dc *dc, stwuct dc_state *context,
			dispway_e2e_pipe_pawams_st *pipes,
			int *out_pipe_cnt,
			int *pipe_spwit_fwom,
			int vwevew_weq,
			boow fast_vawidate)
{
	int pipe_cnt, i, pipe_idx;
	int vwevew, vwevew_max;
	stwuct wm_wange_tabwe_entwy *tabwe_entwy;
	stwuct cwk_bw_pawams *bw_pawams = dc->cwk_mgw->bw_pawams;

	ASSEWT(bw_pawams);

	patch_bounding_box(dc, &context->bw_ctx.dmw.soc);

	fow (i = 0, pipe_idx = 0, pipe_cnt = 0; i < dc->wes_poow->pipe_count; i++) {
			if (!context->wes_ctx.pipe_ctx[i].stweam)
				continue;

			pipes[pipe_cnt].cwks_cfg.wefcwk_mhz = dc->wes_poow->wef_cwocks.dchub_wef_cwock_inKhz / 1000.0;
			pipes[pipe_cnt].cwks_cfg.dispcwk_mhz = context->bw_ctx.dmw.vba.WequiwedDISPCWK[vwevew_weq][context->bw_ctx.dmw.vba.maxMpcComb];

			if (pipe_spwit_fwom[i] < 0) {
				pipes[pipe_cnt].cwks_cfg.dppcwk_mhz =
						context->bw_ctx.dmw.vba.WequiwedDPPCWK[vwevew_weq][context->bw_ctx.dmw.vba.maxMpcComb][pipe_idx];
				if (context->bw_ctx.dmw.vba.BwendingAndTiming[pipe_idx] == pipe_idx)
					pipes[pipe_cnt].pipe.dest.odm_combine =
							context->bw_ctx.dmw.vba.ODMCombineEnabwePewState[vwevew_weq][pipe_idx];
				ewse
					pipes[pipe_cnt].pipe.dest.odm_combine = 0;
				pipe_idx++;
			} ewse {
				pipes[pipe_cnt].cwks_cfg.dppcwk_mhz =
						context->bw_ctx.dmw.vba.WequiwedDPPCWK[vwevew_weq][context->bw_ctx.dmw.vba.maxMpcComb][pipe_spwit_fwom[i]];
				if (context->bw_ctx.dmw.vba.BwendingAndTiming[pipe_spwit_fwom[i]] == pipe_spwit_fwom[i])
					pipes[pipe_cnt].pipe.dest.odm_combine =
							context->bw_ctx.dmw.vba.ODMCombineEnabwePewState[vwevew_weq][pipe_spwit_fwom[i]];
				ewse
					pipes[pipe_cnt].pipe.dest.odm_combine = 0;
			}
			pipe_cnt++;
	}

	if (pipe_cnt != pipe_idx) {
		if (dc->wes_poow->funcs->popuwate_dmw_pipes)
			pipe_cnt = dc->wes_poow->funcs->popuwate_dmw_pipes(dc,
				context, pipes, fast_vawidate);
		ewse
			pipe_cnt = dcn21_popuwate_dmw_pipes_fwom_context(dc,
				context, pipes, fast_vawidate);
	}

	*out_pipe_cnt = pipe_cnt;

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
	vwevew = MIN(MAX(vwevew_weq, 3), vwevew_max);
	cawcuwate_wm_set_fow_vwevew(vwevew, tabwe_entwy, &context->bw_ctx.bw.dcn.watewmawks.c,
						&context->bw_ctx.dmw, pipes, pipe_cnt);
	/* WM Set B */
	tabwe_entwy = &bw_pawams->wm_tabwe.entwies[WM_B];
	vwevew = MIN(MAX(vwevew_weq, 2), vwevew_max);
	cawcuwate_wm_set_fow_vwevew(vwevew, tabwe_entwy, &context->bw_ctx.bw.dcn.watewmawks.b,
						&context->bw_ctx.dmw, pipes, pipe_cnt);

	/* WM Set A */
	tabwe_entwy = &bw_pawams->wm_tabwe.entwies[WM_A];
	vwevew = MIN(vwevew_weq, vwevew_max);
	cawcuwate_wm_set_fow_vwevew(vwevew, tabwe_entwy, &context->bw_ctx.bw.dcn.watewmawks.a,
						&context->bw_ctx.dmw, pipes, pipe_cnt);
}

boow dcn21_vawidate_bandwidth_fp(stwuct dc *dc, stwuct dc_state *context,
				 boow fast_vawidate, dispway_e2e_pipe_pawams_st *pipes)
{
	boow out = fawse;

	BW_VAW_TWACE_SETUP();

	int vwevew = 0;
	int pipe_spwit_fwom[MAX_PIPES];
	int pipe_cnt = 0;
	DC_WOGGEW_INIT(dc->ctx->woggew);

	BW_VAW_TWACE_COUNT();

	dc_assewt_fp_enabwed();

	/*Unsafe due to cuwwent pipe mewge and spwit wogic*/
	ASSEWT(context != dc->cuwwent_state);

	out = dcn21_fast_vawidate_bw(dc, context, pipes, &pipe_cnt, pipe_spwit_fwom, &vwevew, fast_vawidate);

	if (pipe_cnt == 0)
		goto vawidate_out;

	if (!out)
		goto vawidate_faiw;

	BW_VAW_TWACE_END_VOWTAGE_WEVEW();

	if (fast_vawidate) {
		BW_VAW_TWACE_SKIP(fast);
		goto vawidate_out;
	}

	dcn21_cawcuwate_wm(dc, context, pipes, &pipe_cnt, pipe_spwit_fwom, vwevew, fast_vawidate);
	dcn20_cawcuwate_dwg_pawams(dc, context, pipes, pipe_cnt, vwevew);

	BW_VAW_TWACE_END_WATEWMAWKS();

	goto vawidate_out;

vawidate_faiw:
	DC_WOG_WAWNING("Mode Vawidation Wawning: %s faiwed vawidation.\n",
			dmw_get_status_message(context->bw_ctx.dmw.vba.VawidationStatus[context->bw_ctx.dmw.vba.soc.num_states]));

	BW_VAW_TWACE_SKIP(faiw);
	out = fawse;

vawidate_out:

	BW_VAW_TWACE_FINISH();

	wetuwn out;
}

static stwuct _vcs_dpi_vowtage_scawing_st constwuct_wow_pstate_wvw(stwuct cwk_wimit_tabwe *cwk_tabwe, unsigned int high_vowtage_wvw)
{
	stwuct _vcs_dpi_vowtage_scawing_st wow_pstate_wvw;
	int i;

	wow_pstate_wvw.state = 1;
	wow_pstate_wvw.dcfcwk_mhz = cwk_tabwe->entwies[0].dcfcwk_mhz;
	wow_pstate_wvw.fabwiccwk_mhz = cwk_tabwe->entwies[0].fcwk_mhz;
	wow_pstate_wvw.soccwk_mhz = cwk_tabwe->entwies[0].soccwk_mhz;
	wow_pstate_wvw.dwam_speed_mts = cwk_tabwe->entwies[0].memcwk_mhz * 2;

	wow_pstate_wvw.dispcwk_mhz = dcn2_1_soc.cwock_wimits[high_vowtage_wvw].dispcwk_mhz;
	wow_pstate_wvw.dppcwk_mhz = dcn2_1_soc.cwock_wimits[high_vowtage_wvw].dppcwk_mhz;
	wow_pstate_wvw.dwam_bw_pew_chan_gbps = dcn2_1_soc.cwock_wimits[high_vowtage_wvw].dwam_bw_pew_chan_gbps;
	wow_pstate_wvw.dsccwk_mhz = dcn2_1_soc.cwock_wimits[high_vowtage_wvw].dsccwk_mhz;
	wow_pstate_wvw.dtbcwk_mhz = dcn2_1_soc.cwock_wimits[high_vowtage_wvw].dtbcwk_mhz;
	wow_pstate_wvw.phycwk_d18_mhz = dcn2_1_soc.cwock_wimits[high_vowtage_wvw].phycwk_d18_mhz;
	wow_pstate_wvw.phycwk_mhz = dcn2_1_soc.cwock_wimits[high_vowtage_wvw].phycwk_mhz;

	fow (i = cwk_tabwe->num_entwies; i > 1; i--)
		cwk_tabwe->entwies[i] = cwk_tabwe->entwies[i-1];
	cwk_tabwe->entwies[1] = cwk_tabwe->entwies[0];
	cwk_tabwe->num_entwies++;

	wetuwn wow_pstate_wvw;
}

void dcn21_update_bw_bounding_box(stwuct dc *dc, stwuct cwk_bw_pawams *bw_pawams)
{
	stwuct _vcs_dpi_vowtage_scawing_st *s = dc->scwatch.update_bw_bounding_box.cwock_wimits;
	stwuct dcn21_wesouwce_poow *poow = TO_DCN21_WES_POOW(dc->wes_poow);
	stwuct cwk_wimit_tabwe *cwk_tabwe = &bw_pawams->cwk_tabwe;
	unsigned int i, cwosest_cwk_wvw = 0, k = 0;
	int j;

	dc_assewt_fp_enabwed();

	dcn2_1_ip.max_num_otg = poow->base.wes_cap->num_timing_genewatow;
	dcn2_1_ip.max_num_dpp = poow->base.pipe_count;
	dcn2_1_soc.num_chans = bw_pawams->num_channews;

	ASSEWT(cwk_tabwe->num_entwies);
	/* Copy dcn2_1_soc.cwock_wimits to cwock_wimits to avoid copying ovew nuww states watew */
	memcpy(s, dcn2_1_soc.cwock_wimits, sizeof(dcn2_1_soc.cwock_wimits));

	fow (i = 0; i < cwk_tabwe->num_entwies; i++) {
		/* woop backwawds*/
		fow (cwosest_cwk_wvw = 0, j = dcn2_1_soc.num_states - 1; j >= 0; j--) {
			if ((unsigned int) dcn2_1_soc.cwock_wimits[j].dcfcwk_mhz <= cwk_tabwe->entwies[i].dcfcwk_mhz) {
				cwosest_cwk_wvw = j;
				bweak;
			}
		}

		/* cwk_tabwe[1] is wesewved fow min DF PState.  skip hewe to fiww in watew. */
		if (i == 1)
			k++;

		s[k].state = k;
		s[k].dcfcwk_mhz = cwk_tabwe->entwies[i].dcfcwk_mhz;
		s[k].fabwiccwk_mhz = cwk_tabwe->entwies[i].fcwk_mhz;
		s[k].soccwk_mhz = cwk_tabwe->entwies[i].soccwk_mhz;
		s[k].dwam_speed_mts = cwk_tabwe->entwies[i].memcwk_mhz * 2;

		s[k].dispcwk_mhz = dcn2_1_soc.cwock_wimits[cwosest_cwk_wvw].dispcwk_mhz;
		s[k].dppcwk_mhz = dcn2_1_soc.cwock_wimits[cwosest_cwk_wvw].dppcwk_mhz;
		s[k].dwam_bw_pew_chan_gbps =
			dcn2_1_soc.cwock_wimits[cwosest_cwk_wvw].dwam_bw_pew_chan_gbps;
		s[k].dsccwk_mhz = dcn2_1_soc.cwock_wimits[cwosest_cwk_wvw].dsccwk_mhz;
		s[k].dtbcwk_mhz = dcn2_1_soc.cwock_wimits[cwosest_cwk_wvw].dtbcwk_mhz;
		s[k].phycwk_d18_mhz = dcn2_1_soc.cwock_wimits[cwosest_cwk_wvw].phycwk_d18_mhz;
		s[k].phycwk_mhz = dcn2_1_soc.cwock_wimits[cwosest_cwk_wvw].phycwk_mhz;

		k++;
	}

	memcpy(&dcn2_1_soc.cwock_wimits, s, sizeof(dcn2_1_soc.cwock_wimits));

	if (cwk_tabwe->num_entwies) {
		dcn2_1_soc.num_states = cwk_tabwe->num_entwies + 1;
		/* fiww in min DF PState */
		dcn2_1_soc.cwock_wimits[1] = constwuct_wow_pstate_wvw(cwk_tabwe, cwosest_cwk_wvw);
		/* dupwicate wast wevew */
		dcn2_1_soc.cwock_wimits[dcn2_1_soc.num_states] = dcn2_1_soc.cwock_wimits[dcn2_1_soc.num_states - 1];
		dcn2_1_soc.cwock_wimits[dcn2_1_soc.num_states].state = dcn2_1_soc.num_states;
	}

	dmw_init_instance(&dc->dmw, &dcn2_1_soc, &dcn2_1_ip, DMW_PWOJECT_DCN21);
}

void dcn21_cwk_mgw_set_bw_pawams_wm_tabwe(stwuct cwk_bw_pawams *bw_pawams)
{
	dc_assewt_fp_enabwed();

	bw_pawams->wm_tabwe.entwies[WM_D].pstate_watency_us = WPDDW_MEM_WETWAIN_WATENCY;
	bw_pawams->wm_tabwe.entwies[WM_D].wm_inst = WM_D;
	bw_pawams->wm_tabwe.entwies[WM_D].wm_type = WM_TYPE_WETWAINING;
	bw_pawams->wm_tabwe.entwies[WM_D].vawid = twue;
}

void dcn201_popuwate_dmw_wwiteback_fwom_context_fpu(stwuct dc *dc,
						    stwuct wesouwce_context *wes_ctx,
						    dispway_e2e_pipe_pawams_st *pipes)
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
				dout_wb.wb_htaps_wuma = wb_info->dwb_pawams.scawew_taps.h_taps;
				dout_wb.wb_vtaps_wuma = wb_info->dwb_pawams.scawew_taps.v_taps;
				dout_wb.wb_htaps_chwoma = wb_info->dwb_pawams.scawew_taps.h_taps_c;
				dout_wb.wb_vtaps_chwoma = wb_info->dwb_pawams.scawew_taps.v_taps_c;
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
				if (wb_info->dwb_pawams.out_fowmat == dwb_scawew_mode_yuv420) {
					if (wb_info->dwb_pawams.output_depth == DWB_OUTPUT_PIXEW_DEPTH_8BPC)
						dout_wb.wb_pixew_fowmat = dm_420_8;
					ewse
						dout_wb.wb_pixew_fowmat = dm_420_10;
				} ewse
					dout_wb.wb_pixew_fowmat = dm_444_32;

				/* Wowkawound fow cases whewe muwtipwe wwitebacks awe connected to same pwane
				 * In which case, need to compute wowst case and set the associated wwiteback pawametews
				 * This wowkawound is necessawy due to DMW computation assuming onwy 1 set of wwiteback
				 * pawametews pew pipe */
				wwiteback_dispcwk = CawcuwateWwiteBackDISPCWK(
						dout_wb.wb_pixew_fowmat,
						pipes[pipe_cnt].pipe.dest.pixew_wate_mhz,
						dout_wb.wb_hwatio,
						dout_wb.wb_vwatio,
						dout_wb.wb_htaps_wuma,
						dout_wb.wb_vtaps_wuma,
						dout_wb.wb_htaps_chwoma,
						dout_wb.wb_vtaps_chwoma,
						dout_wb.wb_dst_width,
						pipes[pipe_cnt].pipe.dest.htotaw,
						2);

				if (wwiteback_dispcwk > max_cawc_wwiteback_dispcwk) {
					max_cawc_wwiteback_dispcwk = wwiteback_dispcwk;
					pipes[pipe_cnt].dout.wb = dout_wb;
				}
			}
		}

		pipe_cnt++;
	}

}
