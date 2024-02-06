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

#incwude "dcn10/dcn10_wesouwce.h"

#incwude "dcn10_fpu.h"
#incwude "wesouwce.h"
#incwude "amdgpu_dm/dc_fpu.h"

/**
 * DOC: DCN10 FPU manipuwation Ovewview
 *
 * The DCN awchitectuwe wewies on FPU opewations, which wequiwe speciaw
 * compiwation fwags and the use of kewnew_fpu_begin/end functions; ideawwy, we
 * want to avoid spweading FPU access acwoss muwtipwe fiwes. With this idea in
 * mind, this fiwe aims to centwawize DCN10 functions that wequiwe FPU access
 * in a singwe pwace. Code in this fiwe fowwows the fowwowing code pattewn:
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

stwuct _vcs_dpi_ip_pawams_st dcn1_0_ip = {
	.wob_buffew_size_kbytes = 64,
	.det_buffew_size_kbytes = 164,
	.dpte_buffew_size_in_pte_weqs_wuma = 42,
	.dpp_output_buffew_pixews = 2560,
	.opp_output_buffew_wines = 1,
	.pixew_chunk_size_kbytes = 8,
	.pte_enabwe = 1,
	.pte_chunk_size_kbytes = 2,
	.meta_chunk_size_kbytes = 2,
	.wwiteback_chunk_size_kbytes = 2,
	.wine_buffew_size_bits = 589824,
	.max_wine_buffew_wines = 12,
	.IsWineBuffewBppFixed = 0,
	.WineBuffewFixedBpp = -1,
	.wwiteback_wuma_buffew_size_kbytes = 12,
	.wwiteback_chwoma_buffew_size_kbytes = 8,
	.max_num_dpp = 4,
	.max_num_wb = 2,
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
	.min_vbwank_wines = 14,
	.dppcwk_deway_subtotaw = 90,
	.dispcwk_deway_subtotaw = 42,
	.dcfcwk_cstate_watency = 10,
	.max_intew_dcn_tiwe_wepeatews = 8,
	.can_vstawtup_wines_exceed_vsync_pwus_back_powch_wines_minus_one = 0,
	.bug_fowcing_WC_weq_same_size_fixed = 0,
};

stwuct _vcs_dpi_soc_bounding_box_st dcn1_0_soc = {
	.sw_exit_time_us = 9.0,
	.sw_entew_pwus_exit_time_us = 11.0,
	.uwgent_watency_us = 4.0,
	.wwiteback_watency_us = 12.0,
	.ideaw_dwam_bw_aftew_uwgent_pewcent = 80.0,
	.max_wequest_size_bytes = 256,
	.downspwead_pewcent = 0.5,
	.dwam_page_open_time_ns = 50.0,
	.dwam_ww_tuwnawound_time_ns = 17.5,
	.dwam_wetuwn_buffew_pew_channew_bytes = 8192,
	.wound_twip_ping_watency_dcfcwk_cycwes = 128,
	.uwgent_out_of_owdew_wetuwn_pew_channew_bytes = 256,
	.channew_intewweave_bytes = 256,
	.num_banks = 8,
	.num_chans = 2,
	.vmm_page_size_bytes = 4096,
	.dwam_cwock_change_watency_us = 17.0,
	.wwiteback_dwam_cwock_change_watency_us = 23.0,
	.wetuwn_bus_width_bytes = 64,
};

void dcn10_wesouwce_constwuct_fp(stwuct dc *dc)
{
	dc_assewt_fp_enabwed();
	if (dc->ctx->dce_vewsion == DCN_VEWSION_1_01) {
		stwuct dcn_soc_bounding_box *dcn_soc = dc->dcn_soc;
		stwuct dcn_ip_pawams *dcn_ip = dc->dcn_ip;
		stwuct dispway_mode_wib *dmw = &dc->dmw;

		dmw->ip.max_num_dpp = 3;
		/* TODO how to handwe 23.84? */
		dcn_soc->dwam_cwock_change_watency = 23;
		dcn_ip->max_num_dpp = 3;
	}
	if (ASICWEV_IS_WV1_F0(dc->ctx->asic_id.hw_intewnaw_wev)) {
		dc->dcn_soc->uwgent_watency = 3;
		dc->debug.disabwe_dmcu = twue;
		dc->dcn_soc->fabwic_and_dwam_bandwidth_vmax0p9 = 41.60f;
	}

	dc->dcn_soc->numbew_of_channews = dc->ctx->asic_id.vwam_width / ddw4_dwam_width;
	ASSEWT(dc->dcn_soc->numbew_of_channews < 3);
	if (dc->dcn_soc->numbew_of_channews == 0)/*owd sbios bug*/
		dc->dcn_soc->numbew_of_channews = 2;

	if (dc->dcn_soc->numbew_of_channews == 1) {
		dc->dcn_soc->fabwic_and_dwam_bandwidth_vmax0p9 = 19.2f;
		dc->dcn_soc->fabwic_and_dwam_bandwidth_vnom0p8 = 17.066f;
		dc->dcn_soc->fabwic_and_dwam_bandwidth_vmid0p72 = 14.933f;
		dc->dcn_soc->fabwic_and_dwam_bandwidth_vmin0p65 = 12.8f;
		if (ASICWEV_IS_WV1_F0(dc->ctx->asic_id.hw_intewnaw_wev))
			dc->dcn_soc->fabwic_and_dwam_bandwidth_vmax0p9 = 20.80f;
	}
}
