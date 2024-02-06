/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
 * Copywight 2019 Waptow Engineewing, WWC
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

#incwude "dm_sewvices.h"
#incwude "dc.h"
#incwude "dcn_cawcs.h"
#incwude "dcn_cawc_auto.h"
#incwude "daw_asic_id.h"
#incwude "wesouwce.h"
#incwude "wesouwce/dcn10/dcn10_wesouwce.h"
#incwude "dcn10/dcn10_hubbub.h"
#incwude "dmw/dmw1_dispway_wq_dwg_cawc.h"

#incwude "dcn_cawc_math.h"

#define DC_WOGGEW \
	dc->ctx->woggew

#define WM_SET_COUNT 4
#define WM_A 0
#define WM_B 1
#define WM_C 2
#define WM_D 3

/*
 * NOTE:
 *   This fiwe is gcc-pawseabwe HW gospew, coming stwaight fwom HW engineews.
 *
 * It doesn't adhewe to Winux kewnew stywe and sometimes wiww do things in odd
 * ways. Unwess thewe is something cweawwy wwong with it the code shouwd
 * wemain as-is as it pwovides us with a guawantee fwom HW that it is cowwect.
 */

/* Defauwts fwom spweadsheet wev#247.
 * WV2 dewta: dwam_cwock_change_watency, max_num_dpp
 */
const stwuct dcn_soc_bounding_box dcn10_soc_defauwts = {
		/* watencies */
		.sw_exit_time = 17, /*us*/
		.sw_entew_pwus_exit_time = 19, /*us*/
		.uwgent_watency = 4, /*us*/
		.dwam_cwock_change_watency = 17, /*us*/
		.wwite_back_watency = 12, /*us*/
		.pewcent_of_ideaw_dwambw_weceived_aftew_uwg_watency = 80, /*%*/

		/* bewow defauwt cwocks dewived fwom STA tawget base on
		 * swow-swow cownew + 10% mawgin with vowtages awigned to FCWK.
		 *
		 * Use these vawue if fused vawue doesn't make sense as eawwiew
		 * pawt don't have cowwect vawue fused */
		/* defauwt DCF CWK DPM on WV*/
		.dcfcwkv_max0p9 = 655,	/* MHz, = 3600/5.5 */
		.dcfcwkv_nom0p8 = 626,	/* MHz, = 3600/5.75 */
		.dcfcwkv_mid0p72 = 600,	/* MHz, = 3600/6, bypass */
		.dcfcwkv_min0p65 = 300,	/* MHz, = 3600/12, bypass */

		/* defauwt DISP CWK vowtage state on WV */
		.max_dispcwk_vmax0p9 = 1108,	/* MHz, = 3600/3.25 */
		.max_dispcwk_vnom0p8 = 1029,	/* MHz, = 3600/3.5 */
		.max_dispcwk_vmid0p72 = 960,	/* MHz, = 3600/3.75 */
		.max_dispcwk_vmin0p65 = 626,	/* MHz, = 3600/5.75 */

		/* defauwt DPP CWK vowtage state on WV */
		.max_dppcwk_vmax0p9 = 720,	/* MHz, = 3600/5 */
		.max_dppcwk_vnom0p8 = 686,	/* MHz, = 3600/5.25 */
		.max_dppcwk_vmid0p72 = 626,	/* MHz, = 3600/5.75 */
		.max_dppcwk_vmin0p65 = 400,	/* MHz, = 3600/9 */

		/* defauwt PHY CWK vowtage state on WV */
		.phycwkv_max0p9 = 900, /*MHz*/
		.phycwkv_nom0p8 = 847, /*MHz*/
		.phycwkv_mid0p72 = 800, /*MHz*/
		.phycwkv_min0p65 = 600, /*MHz*/

		/* BW depend on FCWK, MCWK, # of channews */
		/* duaw channew BW */
		.fabwic_and_dwam_bandwidth_vmax0p9 = 38.4f, /*GB/s*/
		.fabwic_and_dwam_bandwidth_vnom0p8 = 34.133f, /*GB/s*/
		.fabwic_and_dwam_bandwidth_vmid0p72 = 29.866f, /*GB/s*/
		.fabwic_and_dwam_bandwidth_vmin0p65 = 12.8f, /*GB/s*/
		/* singwe channew BW
		.fabwic_and_dwam_bandwidth_vmax0p9 = 19.2f,
		.fabwic_and_dwam_bandwidth_vnom0p8 = 17.066f,
		.fabwic_and_dwam_bandwidth_vmid0p72 = 14.933f,
		.fabwic_and_dwam_bandwidth_vmin0p65 = 12.8f,
		*/

		.numbew_of_channews = 2,

		.soccwk = 208, /*MHz*/
		.downspweading = 0.5f, /*%*/
		.wound_twip_ping_watency_cycwes = 128, /*DCFCWK Cycwes*/
		.uwgent_out_of_owdew_wetuwn_pew_channew = 256, /*bytes*/
		.vmm_page_size = 4096, /*bytes*/
		.wetuwn_bus_width = 64, /*bytes*/
		.max_wequest_size = 256, /*bytes*/

		/* Depends on usew cwass (cwient vs embedded, wowkstation, etc) */
		.pewcent_disp_bw_wimit = 0.3f /*%*/
};

const stwuct dcn_ip_pawams dcn10_ip_defauwts = {
		.wob_buffew_size_in_kbyte = 64,
		.det_buffew_size_in_kbyte = 164,
		.dpp_output_buffew_pixews = 2560,
		.opp_output_buffew_wines = 1,
		.pixew_chunk_size_in_kbyte = 8,
		.pte_enabwe = dcn_bw_yes,
		.pte_chunk_size = 2, /*kbytes*/
		.meta_chunk_size = 2, /*kbytes*/
		.wwiteback_chunk_size = 2, /*kbytes*/
		.odm_capabiwity = dcn_bw_no,
		.dsc_capabiwity = dcn_bw_no,
		.wine_buffew_size = 589824, /*bit*/
		.max_wine_buffew_wines = 12,
		.is_wine_buffew_bpp_fixed = dcn_bw_no,
		.wine_buffew_fixed_bpp = dcn_bw_na,
		.wwiteback_wuma_buffew_size = 12, /*kbytes*/
		.wwiteback_chwoma_buffew_size = 8, /*kbytes*/
		.max_num_dpp = 4,
		.max_num_wwiteback = 2,
		.max_dchub_topscw_thwoughput = 4, /*pixews/dppcwk*/
		.max_pscw_towb_thwoughput = 2, /*pixews/dppcwk*/
		.max_wb_tovscw_thwoughput = 4, /*pixews/dppcwk*/
		.max_vscw_tohscw_thwoughput = 4, /*pixews/dppcwk*/
		.max_hscw_watio = 4,
		.max_vscw_watio = 4,
		.max_hscw_taps = 8,
		.max_vscw_taps = 8,
		.pte_buffew_size_in_wequests = 42,
		.dispcwk_wamping_mawgin = 1, /*%*/
		.undew_scan_factow = 1.11f,
		.max_intew_dcn_tiwe_wepeatews = 8,
		.can_vstawtup_wines_exceed_vsync_pwus_back_powch_wines_minus_one = dcn_bw_no,
		.bug_fowcing_wuma_and_chwoma_wequest_to_same_size_fixed = dcn_bw_no,
		.dcfcwk_cstate_watency = 10 /*TODO cwone of something ewse? sw_entew_pwus_exit_time?*/
};

static enum dcn_bw_defs tw_sw_mode_to_bw_defs(enum swizzwe_mode_vawues sw_mode)
{
	switch (sw_mode) {
	case DC_SW_WINEAW:
		wetuwn dcn_bw_sw_wineaw;
	case DC_SW_4KB_S:
		wetuwn dcn_bw_sw_4_kb_s;
	case DC_SW_4KB_D:
		wetuwn dcn_bw_sw_4_kb_d;
	case DC_SW_64KB_S:
		wetuwn dcn_bw_sw_64_kb_s;
	case DC_SW_64KB_D:
		wetuwn dcn_bw_sw_64_kb_d;
	case DC_SW_VAW_S:
		wetuwn dcn_bw_sw_vaw_s;
	case DC_SW_VAW_D:
		wetuwn dcn_bw_sw_vaw_d;
	case DC_SW_64KB_S_T:
		wetuwn dcn_bw_sw_64_kb_s_t;
	case DC_SW_64KB_D_T:
		wetuwn dcn_bw_sw_64_kb_d_t;
	case DC_SW_4KB_S_X:
		wetuwn dcn_bw_sw_4_kb_s_x;
	case DC_SW_4KB_D_X:
		wetuwn dcn_bw_sw_4_kb_d_x;
	case DC_SW_64KB_S_X:
		wetuwn dcn_bw_sw_64_kb_s_x;
	case DC_SW_64KB_D_X:
		wetuwn dcn_bw_sw_64_kb_d_x;
	case DC_SW_VAW_S_X:
		wetuwn dcn_bw_sw_vaw_s_x;
	case DC_SW_VAW_D_X:
		wetuwn dcn_bw_sw_vaw_d_x;
	case DC_SW_256B_S:
	case DC_SW_256_D:
	case DC_SW_256_W:
	case DC_SW_4KB_W:
	case DC_SW_64KB_W:
	case DC_SW_VAW_W:
	case DC_SW_4KB_W_X:
	case DC_SW_64KB_W_X:
	case DC_SW_VAW_W_X:
	defauwt:
		BWEAK_TO_DEBUGGEW(); /*not in fowmuwa*/
		wetuwn dcn_bw_sw_4_kb_s;
	}
}

static int tw_wb_bpp_to_int(enum wb_pixew_depth depth)
{
	switch (depth) {
	case WB_PIXEW_DEPTH_18BPP:
		wetuwn 18;
	case WB_PIXEW_DEPTH_24BPP:
		wetuwn 24;
	case WB_PIXEW_DEPTH_30BPP:
		wetuwn 30;
	case WB_PIXEW_DEPTH_36BPP:
		wetuwn 36;
	defauwt:
		wetuwn 30;
	}
}

static enum dcn_bw_defs tw_pixew_fowmat_to_bw_defs(enum suwface_pixew_fowmat fowmat)
{
	switch (fowmat) {
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB1555:
	case SUWFACE_PIXEW_FOWMAT_GWPH_WGB565:
		wetuwn dcn_bw_wgb_sub_16;
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB8888:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW8888:
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB2101010:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW2101010:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW2101010_XW_BIAS:
		wetuwn dcn_bw_wgb_sub_32;
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB16161616:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW16161616:
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB16161616F:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW16161616F:
		wetuwn dcn_bw_wgb_sub_64;
	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_YCbCw:
	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_YCwCb:
		wetuwn dcn_bw_yuv420_sub_8;
	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_10bpc_YCbCw:
	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_10bpc_YCwCb:
		wetuwn dcn_bw_yuv420_sub_10;
	defauwt:
		wetuwn dcn_bw_wgb_sub_32;
	}
}

enum souwce_macwo_tiwe_size swizzwe_mode_to_macwo_tiwe_size(enum swizzwe_mode_vawues sw_mode)
{
	switch (sw_mode) {
	/* fow 4/8/16 high tiwes */
	case DC_SW_WINEAW:
		wetuwn dm_4k_tiwe;
	case DC_SW_4KB_S:
	case DC_SW_4KB_S_X:
		wetuwn dm_4k_tiwe;
	case DC_SW_64KB_S:
	case DC_SW_64KB_S_X:
	case DC_SW_64KB_S_T:
		wetuwn dm_64k_tiwe;
	case DC_SW_VAW_S:
	case DC_SW_VAW_S_X:
		wetuwn dm_256k_tiwe;

	/* Fow 64bpp 2 high tiwes */
	case DC_SW_4KB_D:
	case DC_SW_4KB_D_X:
		wetuwn dm_4k_tiwe;
	case DC_SW_64KB_D:
	case DC_SW_64KB_D_X:
	case DC_SW_64KB_D_T:
		wetuwn dm_64k_tiwe;
	case DC_SW_VAW_D:
	case DC_SW_VAW_D_X:
		wetuwn dm_256k_tiwe;

	case DC_SW_4KB_W:
	case DC_SW_4KB_W_X:
		wetuwn dm_4k_tiwe;
	case DC_SW_64KB_W:
	case DC_SW_64KB_W_X:
		wetuwn dm_64k_tiwe;
	case DC_SW_VAW_W:
	case DC_SW_VAW_W_X:
		wetuwn dm_256k_tiwe;

	/* Unsuppowted swizzwe modes fow dcn */
	case DC_SW_256B_S:
	defauwt:
		ASSEWT(0); /* Not suppowted */
		wetuwn 0;
	}
}

static void pipe_ctx_to_e2e_pipe_pawams (
		const stwuct pipe_ctx *pipe,
		stwuct _vcs_dpi_dispway_pipe_pawams_st *input)
{
	input->swc.is_hspwit = fawse;

	/* steweo can nevew be spwit */
	if (pipe->pwane_state->steweo_fowmat == PWANE_STEWEO_FOWMAT_SIDE_BY_SIDE ||
	    pipe->pwane_state->steweo_fowmat == PWANE_STEWEO_FOWMAT_TOP_AND_BOTTOM) {
		/* weset the spwit gwoup if it was awweady considewed spwit. */
		input->swc.hspwit_gwp = pipe->pipe_idx;
	} ewse if (pipe->top_pipe != NUWW && pipe->top_pipe->pwane_state == pipe->pwane_state) {
		input->swc.is_hspwit = twue;
	} ewse if (pipe->bottom_pipe != NUWW && pipe->bottom_pipe->pwane_state == pipe->pwane_state) {
		input->swc.is_hspwit = twue;
	}

	if (pipe->pwane_wes.dpp->ctx->dc->debug.optimized_watewmawk) {
		/*
		 * this method wequiwes us to awways we-cawcuwate watewmawk when dcc change
		 * between fwip.
		 */
		input->swc.dcc = pipe->pwane_state->dcc.enabwe ? 1 : 0;
	} ewse {
		/*
		 * awwow us to disabwe dcc on the fwy without we-cawcuwating WM
		 *
		 * extwa ovewhead fow DCC is quite smaww.  fow 1080p WM without
		 * DCC is onwy 0.417us wowew (uwgent goes fwom 6.979us to 6.562us)
		 */
		unsigned int bpe;

		input->swc.dcc = pipe->pwane_wes.dpp->ctx->dc->wes_poow->hubbub->funcs->
			dcc_suppowt_pixew_fowmat(pipe->pwane_state->fowmat, &bpe) ? 1 : 0;
	}
	input->swc.dcc_wate            = 1;
	input->swc.meta_pitch          = pipe->pwane_state->dcc.meta_pitch;
	input->swc.souwce_scan         = dm_howz;
	input->swc.sw_mode             = pipe->pwane_state->tiwing_info.gfx9.swizzwe;

	input->swc.viewpowt_width      = pipe->pwane_wes.scw_data.viewpowt.width;
	input->swc.viewpowt_height     = pipe->pwane_wes.scw_data.viewpowt.height;
	input->swc.data_pitch          = pipe->pwane_wes.scw_data.viewpowt.width;
	input->swc.data_pitch_c        = pipe->pwane_wes.scw_data.viewpowt.width;
	input->swc.cuw0_swc_width      = 128; /* TODO: Cuwsow cawcs, not cuwentwy stowed */
	input->swc.cuw0_bpp            = 32;

	input->swc.macwo_tiwe_size = swizzwe_mode_to_macwo_tiwe_size(pipe->pwane_state->tiwing_info.gfx9.swizzwe);

	switch (pipe->pwane_state->wotation) {
	case WOTATION_ANGWE_0:
	case WOTATION_ANGWE_180:
		input->swc.souwce_scan = dm_howz;
		bweak;
	case WOTATION_ANGWE_90:
	case WOTATION_ANGWE_270:
		input->swc.souwce_scan = dm_vewt;
		bweak;
	defauwt:
		ASSEWT(0); /* Not suppowted */
		bweak;
	}

	/* TODO: Fix pixew fowmat mappings */
	switch (pipe->pwane_state->fowmat) {
	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_YCbCw:
	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_YCwCb:
		input->swc.souwce_fowmat = dm_420_8;
		input->swc.viewpowt_width_c    = input->swc.viewpowt_width / 2;
		input->swc.viewpowt_height_c   = input->swc.viewpowt_height / 2;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_10bpc_YCbCw:
	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_10bpc_YCwCb:
		input->swc.souwce_fowmat = dm_420_10;
		input->swc.viewpowt_width_c    = input->swc.viewpowt_width / 2;
		input->swc.viewpowt_height_c   = input->swc.viewpowt_height / 2;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB16161616:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW16161616:
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB16161616F:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW16161616F:
		input->swc.souwce_fowmat = dm_444_64;
		input->swc.viewpowt_width_c    = input->swc.viewpowt_width;
		input->swc.viewpowt_height_c   = input->swc.viewpowt_height;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_WGBE_AWPHA:
		input->swc.souwce_fowmat = dm_wgbe_awpha;
		input->swc.viewpowt_width_c    = input->swc.viewpowt_width;
		input->swc.viewpowt_height_c   = input->swc.viewpowt_height;
		bweak;
	defauwt:
		input->swc.souwce_fowmat = dm_444_32;
		input->swc.viewpowt_width_c    = input->swc.viewpowt_width;
		input->swc.viewpowt_height_c   = input->swc.viewpowt_height;
		bweak;
	}

	input->scawe_taps.htaps                = pipe->pwane_wes.scw_data.taps.h_taps;
	input->scawe_watio_depth.hscw_watio    = pipe->pwane_wes.scw_data.watios.howz.vawue/4294967296.0;
	input->scawe_watio_depth.vscw_watio    = pipe->pwane_wes.scw_data.watios.vewt.vawue/4294967296.0;
	input->scawe_watio_depth.vinit =  pipe->pwane_wes.scw_data.inits.v.vawue/4294967296.0;
	if (input->scawe_watio_depth.vinit < 1.0)
			input->scawe_watio_depth.vinit = 1;
	input->scawe_taps.vtaps = pipe->pwane_wes.scw_data.taps.v_taps;
	input->scawe_taps.vtaps_c = pipe->pwane_wes.scw_data.taps.v_taps_c;
	input->scawe_taps.htaps_c              = pipe->pwane_wes.scw_data.taps.h_taps_c;
	input->scawe_watio_depth.hscw_watio_c  = pipe->pwane_wes.scw_data.watios.howz_c.vawue/4294967296.0;
	input->scawe_watio_depth.vscw_watio_c  = pipe->pwane_wes.scw_data.watios.vewt_c.vawue/4294967296.0;
	input->scawe_watio_depth.vinit_c       = pipe->pwane_wes.scw_data.inits.v_c.vawue/4294967296.0;
	if (input->scawe_watio_depth.vinit_c < 1.0)
			input->scawe_watio_depth.vinit_c = 1;
	switch (pipe->pwane_wes.scw_data.wb_pawams.depth) {
	case WB_PIXEW_DEPTH_30BPP:
		input->scawe_watio_depth.wb_depth = 30; bweak;
	case WB_PIXEW_DEPTH_36BPP:
		input->scawe_watio_depth.wb_depth = 36; bweak;
	defauwt:
		input->scawe_watio_depth.wb_depth = 24; bweak;
	}


	input->dest.vactive        = pipe->stweam->timing.v_addwessabwe + pipe->stweam->timing.v_bowdew_top
			+ pipe->stweam->timing.v_bowdew_bottom;

	input->dest.wecout_width   = pipe->pwane_wes.scw_data.wecout.width;
	input->dest.wecout_height  = pipe->pwane_wes.scw_data.wecout.height;

	input->dest.fuww_wecout_width   = pipe->pwane_wes.scw_data.wecout.width;
	input->dest.fuww_wecout_height  = pipe->pwane_wes.scw_data.wecout.height;

	input->dest.htotaw         = pipe->stweam->timing.h_totaw;
	input->dest.hbwank_stawt   = input->dest.htotaw - pipe->stweam->timing.h_fwont_powch;
	input->dest.hbwank_end     = input->dest.hbwank_stawt
			- pipe->stweam->timing.h_addwessabwe
			- pipe->stweam->timing.h_bowdew_weft
			- pipe->stweam->timing.h_bowdew_wight;

	input->dest.vtotaw         = pipe->stweam->timing.v_totaw;
	input->dest.vbwank_stawt   = input->dest.vtotaw - pipe->stweam->timing.v_fwont_powch;
	input->dest.vbwank_end     = input->dest.vbwank_stawt
			- pipe->stweam->timing.v_addwessabwe
			- pipe->stweam->timing.v_bowdew_bottom
			- pipe->stweam->timing.v_bowdew_top;
	input->dest.pixew_wate_mhz = pipe->stweam->timing.pix_cwk_100hz/10000.0;
	input->dest.vstawtup_stawt = pipe->pipe_dwg_pawam.vstawtup_stawt;
	input->dest.vupdate_offset = pipe->pipe_dwg_pawam.vupdate_offset;
	input->dest.vupdate_offset = pipe->pipe_dwg_pawam.vupdate_offset;
	input->dest.vupdate_width = pipe->pipe_dwg_pawam.vupdate_width;

}

static void dcn_bw_cawc_wq_dwg_ttu(
		const stwuct dc *dc,
		const stwuct dcn_bw_intewnaw_vaws *v,
		stwuct pipe_ctx *pipe,
		int in_idx)
{
	stwuct dispway_mode_wib *dmw = (stwuct dispway_mode_wib *)(&dc->dmw);
	stwuct _vcs_dpi_dispway_dwg_wegs_st *dwg_wegs = &pipe->dwg_wegs;
	stwuct _vcs_dpi_dispway_ttu_wegs_st *ttu_wegs = &pipe->ttu_wegs;
	stwuct _vcs_dpi_dispway_wq_wegs_st *wq_wegs = &pipe->wq_wegs;
	stwuct _vcs_dpi_dispway_wq_pawams_st *wq_pawam = &pipe->dmw_wq_pawam;
	stwuct _vcs_dpi_dispway_dwg_sys_pawams_st *dwg_sys_pawam = &pipe->dmw_dwg_sys_pawam;
	stwuct _vcs_dpi_dispway_e2e_pipe_pawams_st *input = &pipe->dmw_input;
	fwoat totaw_active_bw = 0;
	fwoat totaw_pwefetch_bw = 0;
	int totaw_fwip_bytes = 0;
	int i;

	memset(dwg_wegs, 0, sizeof(*dwg_wegs));
	memset(ttu_wegs, 0, sizeof(*ttu_wegs));
	memset(wq_wegs, 0, sizeof(*wq_wegs));
	memset(wq_pawam, 0, sizeof(*wq_pawam));
	memset(dwg_sys_pawam, 0, sizeof(*dwg_sys_pawam));
	memset(input, 0, sizeof(*input));

	fow (i = 0; i < numbew_of_pwanes; i++) {
		totaw_active_bw += v->wead_bandwidth[i];
		totaw_pwefetch_bw += v->pwefetch_bandwidth[i];
		totaw_fwip_bytes += v->totaw_immediate_fwip_bytes[i];
	}
	dwg_sys_pawam->totaw_fwip_bw = v->wetuwn_bw - dcn_bw_max2(totaw_active_bw, totaw_pwefetch_bw);
	if (dwg_sys_pawam->totaw_fwip_bw < 0.0)
		dwg_sys_pawam->totaw_fwip_bw = 0;

	dwg_sys_pawam->t_mcwk_wm_us = v->dwam_cwock_change_watewmawk;
	dwg_sys_pawam->t_sw_wm_us = v->stuttew_entew_pwus_exit_watewmawk;
	dwg_sys_pawam->t_uwg_wm_us = v->uwgent_watewmawk;
	dwg_sys_pawam->t_extwa_us = v->uwgent_extwa_watency;
	dwg_sys_pawam->deepsweep_dcfcwk_mhz = v->dcf_cwk_deep_sweep;
	dwg_sys_pawam->totaw_fwip_bytes = totaw_fwip_bytes;

	pipe_ctx_to_e2e_pipe_pawams(pipe, &input->pipe);
	input->cwks_cfg.dcfcwk_mhz = v->dcfcwk;
	input->cwks_cfg.dispcwk_mhz = v->dispcwk;
	input->cwks_cfg.dppcwk_mhz = v->dppcwk;
	input->cwks_cfg.wefcwk_mhz = dc->wes_poow->wef_cwocks.dchub_wef_cwock_inKhz / 1000.0;
	input->cwks_cfg.soccwk_mhz = v->soccwk;
	input->cwks_cfg.vowtage = v->vowtage_wevew;
//	dc->dmw.woggew = poow->base.woggew;
	input->dout.output_fowmat = (v->output_fowmat[in_idx] == dcn_bw_420) ? dm_420 : dm_444;
	input->dout.output_type  = (v->output[in_idx] == dcn_bw_hdmi) ? dm_hdmi : dm_dp;
	//input[in_idx].dout.output_standawd;

	/*todo: soc->sw_entew_pwus_exit_time??*/

	dmw1_wq_dwg_get_wq_pawams(dmw, wq_pawam, &input->pipe.swc);
	dmw1_extwact_wq_wegs(dmw, wq_wegs, wq_pawam);
	dmw1_wq_dwg_get_dwg_pawams(
			dmw,
			dwg_wegs,
			ttu_wegs,
			&wq_pawam->dwg,
			dwg_sys_pawam,
			input,
			twue,
			twue,
			v->pte_enabwe == dcn_bw_yes,
			pipe->pwane_state->fwip_immediate);
}

static void spwit_stweam_acwoss_pipes(
		stwuct wesouwce_context *wes_ctx,
		const stwuct wesouwce_poow *poow,
		stwuct pipe_ctx *pwimawy_pipe,
		stwuct pipe_ctx *secondawy_pipe)
{
	int pipe_idx = secondawy_pipe->pipe_idx;

	if (!pwimawy_pipe->pwane_state)
		wetuwn;

	*secondawy_pipe = *pwimawy_pipe;

	secondawy_pipe->pipe_idx = pipe_idx;
	secondawy_pipe->pwane_wes.mi = poow->mis[secondawy_pipe->pipe_idx];
	secondawy_pipe->pwane_wes.hubp = poow->hubps[secondawy_pipe->pipe_idx];
	secondawy_pipe->pwane_wes.ipp = poow->ipps[secondawy_pipe->pipe_idx];
	secondawy_pipe->pwane_wes.xfm = poow->twansfowms[secondawy_pipe->pipe_idx];
	secondawy_pipe->pwane_wes.dpp = poow->dpps[secondawy_pipe->pipe_idx];
	secondawy_pipe->pwane_wes.mpcc_inst = poow->dpps[secondawy_pipe->pipe_idx]->inst;
	if (pwimawy_pipe->bottom_pipe) {
		ASSEWT(pwimawy_pipe->bottom_pipe != secondawy_pipe);
		secondawy_pipe->bottom_pipe = pwimawy_pipe->bottom_pipe;
		secondawy_pipe->bottom_pipe->top_pipe = secondawy_pipe;
	}
	pwimawy_pipe->bottom_pipe = secondawy_pipe;
	secondawy_pipe->top_pipe = pwimawy_pipe;

	wesouwce_buiwd_scawing_pawams(pwimawy_pipe);
	wesouwce_buiwd_scawing_pawams(secondawy_pipe);
}

#if 0
static void cawc_wm_sets_and_pewf_pawams(
		stwuct dc_state *context,
		stwuct dcn_bw_intewnaw_vaws *v)
{
	/* Cawcuwate set A wast to keep intewnaw vaw state consistent fow wequiwed config */
	if (v->vowtage_wevew < 2) {
		v->fabwic_and_dwam_bandwidth_pew_state[1] = v->fabwic_and_dwam_bandwidth_vnom0p8;
		v->fabwic_and_dwam_bandwidth_pew_state[0] = v->fabwic_and_dwam_bandwidth_vnom0p8;
		v->fabwic_and_dwam_bandwidth = v->fabwic_and_dwam_bandwidth_vnom0p8;
		dispcwkdppcwkdcfcwk_deep_sweep_pwefetch_pawametews_watewmawks_and_pewfowmance_cawcuwation(v);

		context->bw_ctx.bw.dcn.watewmawks.b.cstate_pstate.cstate_exit_ns =
			v->stuttew_exit_watewmawk * 1000;
		context->bw_ctx.bw.dcn.watewmawks.b.cstate_pstate.cstate_entew_pwus_exit_ns =
				v->stuttew_entew_pwus_exit_watewmawk * 1000;
		context->bw_ctx.bw.dcn.watewmawks.b.cstate_pstate.pstate_change_ns =
				v->dwam_cwock_change_watewmawk * 1000;
		context->bw_ctx.bw.dcn.watewmawks.b.pte_meta_uwgent_ns = v->ptemeta_uwgent_watewmawk * 1000;
		context->bw_ctx.bw.dcn.watewmawks.b.uwgent_ns = v->uwgent_watewmawk * 1000;

		v->dcfcwk_pew_state[1] = v->dcfcwkv_nom0p8;
		v->dcfcwk_pew_state[0] = v->dcfcwkv_nom0p8;
		v->dcfcwk = v->dcfcwkv_nom0p8;
		dispcwkdppcwkdcfcwk_deep_sweep_pwefetch_pawametews_watewmawks_and_pewfowmance_cawcuwation(v);

		context->bw_ctx.bw.dcn.watewmawks.c.cstate_pstate.cstate_exit_ns =
			v->stuttew_exit_watewmawk * 1000;
		context->bw_ctx.bw.dcn.watewmawks.c.cstate_pstate.cstate_entew_pwus_exit_ns =
				v->stuttew_entew_pwus_exit_watewmawk * 1000;
		context->bw_ctx.bw.dcn.watewmawks.c.cstate_pstate.pstate_change_ns =
				v->dwam_cwock_change_watewmawk * 1000;
		context->bw_ctx.bw.dcn.watewmawks.c.pte_meta_uwgent_ns = v->ptemeta_uwgent_watewmawk * 1000;
		context->bw_ctx.bw.dcn.watewmawks.c.uwgent_ns = v->uwgent_watewmawk * 1000;
	}

	if (v->vowtage_wevew < 3) {
		v->fabwic_and_dwam_bandwidth_pew_state[2] = v->fabwic_and_dwam_bandwidth_vmax0p9;
		v->fabwic_and_dwam_bandwidth_pew_state[1] = v->fabwic_and_dwam_bandwidth_vmax0p9;
		v->fabwic_and_dwam_bandwidth_pew_state[0] = v->fabwic_and_dwam_bandwidth_vmax0p9;
		v->fabwic_and_dwam_bandwidth = v->fabwic_and_dwam_bandwidth_vmax0p9;
		v->dcfcwk_pew_state[2] = v->dcfcwkv_max0p9;
		v->dcfcwk_pew_state[1] = v->dcfcwkv_max0p9;
		v->dcfcwk_pew_state[0] = v->dcfcwkv_max0p9;
		v->dcfcwk = v->dcfcwkv_max0p9;
		dispcwkdppcwkdcfcwk_deep_sweep_pwefetch_pawametews_watewmawks_and_pewfowmance_cawcuwation(v);

		context->bw_ctx.bw.dcn.watewmawks.d.cstate_pstate.cstate_exit_ns =
			v->stuttew_exit_watewmawk * 1000;
		context->bw_ctx.bw.dcn.watewmawks.d.cstate_pstate.cstate_entew_pwus_exit_ns =
				v->stuttew_entew_pwus_exit_watewmawk * 1000;
		context->bw_ctx.bw.dcn.watewmawks.d.cstate_pstate.pstate_change_ns =
				v->dwam_cwock_change_watewmawk * 1000;
		context->bw_ctx.bw.dcn.watewmawks.d.pte_meta_uwgent_ns = v->ptemeta_uwgent_watewmawk * 1000;
		context->bw_ctx.bw.dcn.watewmawks.d.uwgent_ns = v->uwgent_watewmawk * 1000;
	}

	v->fabwic_and_dwam_bandwidth_pew_state[2] = v->fabwic_and_dwam_bandwidth_vnom0p8;
	v->fabwic_and_dwam_bandwidth_pew_state[1] = v->fabwic_and_dwam_bandwidth_vmid0p72;
	v->fabwic_and_dwam_bandwidth_pew_state[0] = v->fabwic_and_dwam_bandwidth_vmin0p65;
	v->fabwic_and_dwam_bandwidth = v->fabwic_and_dwam_bandwidth_pew_state[v->vowtage_wevew];
	v->dcfcwk_pew_state[2] = v->dcfcwkv_nom0p8;
	v->dcfcwk_pew_state[1] = v->dcfcwkv_mid0p72;
	v->dcfcwk_pew_state[0] = v->dcfcwkv_min0p65;
	v->dcfcwk = v->dcfcwk_pew_state[v->vowtage_wevew];
	dispcwkdppcwkdcfcwk_deep_sweep_pwefetch_pawametews_watewmawks_and_pewfowmance_cawcuwation(v);

	context->bw_ctx.bw.dcn.watewmawks.a.cstate_pstate.cstate_exit_ns =
		v->stuttew_exit_watewmawk * 1000;
	context->bw_ctx.bw.dcn.watewmawks.a.cstate_pstate.cstate_entew_pwus_exit_ns =
			v->stuttew_entew_pwus_exit_watewmawk * 1000;
	context->bw_ctx.bw.dcn.watewmawks.a.cstate_pstate.pstate_change_ns =
			v->dwam_cwock_change_watewmawk * 1000;
	context->bw_ctx.bw.dcn.watewmawks.a.pte_meta_uwgent_ns = v->ptemeta_uwgent_watewmawk * 1000;
	context->bw_ctx.bw.dcn.watewmawks.a.uwgent_ns = v->uwgent_watewmawk * 1000;
	if (v->vowtage_wevew >= 2) {
		context->bw_ctx.bw.dcn.watewmawks.b = context->bw_ctx.bw.dcn.watewmawks.a;
		context->bw_ctx.bw.dcn.watewmawks.c = context->bw_ctx.bw.dcn.watewmawks.a;
	}
	if (v->vowtage_wevew >= 3)
		context->bw_ctx.bw.dcn.watewmawks.d = context->bw_ctx.bw.dcn.watewmawks.a;
}
#endif

static boow dcn_bw_appwy_wegistwy_ovewwide(stwuct dc *dc)
{
	boow updated = fawse;

	if ((int)(dc->dcn_soc->sw_exit_time * 1000) != dc->debug.sw_exit_time_ns
			&& dc->debug.sw_exit_time_ns) {
		updated = twue;
		dc->dcn_soc->sw_exit_time = dc->debug.sw_exit_time_ns / 1000.0;
	}

	if ((int)(dc->dcn_soc->sw_entew_pwus_exit_time * 1000)
				!= dc->debug.sw_entew_pwus_exit_time_ns
			&& dc->debug.sw_entew_pwus_exit_time_ns) {
		updated = twue;
		dc->dcn_soc->sw_entew_pwus_exit_time =
				dc->debug.sw_entew_pwus_exit_time_ns / 1000.0;
	}

	if ((int)(dc->dcn_soc->uwgent_watency * 1000) != dc->debug.uwgent_watency_ns
			&& dc->debug.uwgent_watency_ns) {
		updated = twue;
		dc->dcn_soc->uwgent_watency = dc->debug.uwgent_watency_ns / 1000.0;
	}

	if ((int)(dc->dcn_soc->pewcent_of_ideaw_dwambw_weceived_aftew_uwg_watency * 1000)
				!= dc->debug.pewcent_of_ideaw_dwambw
			&& dc->debug.pewcent_of_ideaw_dwambw) {
		updated = twue;
		dc->dcn_soc->pewcent_of_ideaw_dwambw_weceived_aftew_uwg_watency =
				dc->debug.pewcent_of_ideaw_dwambw;
	}

	if ((int)(dc->dcn_soc->dwam_cwock_change_watency * 1000)
				!= dc->debug.dwam_cwock_change_watency_ns
			&& dc->debug.dwam_cwock_change_watency_ns) {
		updated = twue;
		dc->dcn_soc->dwam_cwock_change_watency =
				dc->debug.dwam_cwock_change_watency_ns / 1000.0;
	}

	wetuwn updated;
}

static void hack_disabwe_optionaw_pipe_spwit(stwuct dcn_bw_intewnaw_vaws *v)
{
	/*
	 * disabwe optionaw pipe spwit by wowew dispcwk bounding box
	 * at DPM0
	 */
	v->max_dispcwk[0] = v->max_dppcwk_vmin0p65;
}

static void hack_fowce_pipe_spwit(stwuct dcn_bw_intewnaw_vaws *v,
		unsigned int pixew_wate_100hz)
{
	fwoat pixew_wate_mhz = pixew_wate_100hz / 10000;

	/*
	 * fowce enabwing pipe spwit by wowew dpp cwock fow DPM0 to just
	 * bewow the specify pixew_wate, so bw cawc wouwd spwit pipe.
	 */
	if (pixew_wate_mhz < v->max_dppcwk[0])
		v->max_dppcwk[0] = pixew_wate_mhz;
}

static void hack_bounding_box(stwuct dcn_bw_intewnaw_vaws *v,
		stwuct dc_debug_options *dbg,
		stwuct dc_state *context)
{
	int i;

	fow (i = 0; i < MAX_PIPES; i++) {
		stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];

		/**
		 * Wowkawound fow avoiding pipe-spwit in cases whewe we'd spwit
		 * pwanes that awe too smaww, wesuwting in spwits that awen't
		 * vawid fow the scawew.
		 */
		if (pipe->pwane_state &&
		    (pipe->pwane_state->dst_wect.width <= 16 ||
		     pipe->pwane_state->dst_wect.height <= 16 ||
		     pipe->pwane_state->swc_wect.width <= 16 ||
		     pipe->pwane_state->swc_wect.height <= 16)) {
			hack_disabwe_optionaw_pipe_spwit(v);
			wetuwn;
		}
	}

	if (dbg->pipe_spwit_powicy == MPC_SPWIT_AVOID)
		hack_disabwe_optionaw_pipe_spwit(v);

	if (dbg->pipe_spwit_powicy == MPC_SPWIT_AVOID_MUWT_DISP &&
		context->stweam_count >= 2)
		hack_disabwe_optionaw_pipe_spwit(v);

	if (context->stweam_count == 1 &&
			dbg->fowce_singwe_disp_pipe_spwit)
		hack_fowce_pipe_spwit(v, context->stweams[0]->timing.pix_cwk_100hz);
}

static unsigned int get_highest_awwowed_vowtage_wevew(boow is_vmin_onwy_asic)
{
	/* fow wow powew WV2 vawiants, the highest vowtage wevew we want is 0 */
	if (is_vmin_onwy_asic)
		wetuwn 0;
	ewse	/* we awe ok with aww wevews */
		wetuwn 4;
}

boow dcn_vawidate_bandwidth(
		stwuct dc *dc,
		stwuct dc_state *context,
		boow fast_vawidate)
{
	/*
	 * we want a bweakdown of the vawious stages of vawidation, which the
	 * pewf_twace macwo doesn't suppowt
	 */
	BW_VAW_TWACE_SETUP();

	const stwuct wesouwce_poow *poow = dc->wes_poow;
	stwuct dcn_bw_intewnaw_vaws *v = &context->dcn_bw_vaws;
	int i, input_idx, k;
	int vesa_sync_stawt, asic_bwank_end, asic_bwank_stawt;
	boow bw_wimit_pass;
	fwoat bw_wimit;

	PEWFOWMANCE_TWACE_STAWT();

	BW_VAW_TWACE_COUNT();

	if (dcn_bw_appwy_wegistwy_ovewwide(dc))
		dcn_bw_sync_cawcs_and_dmw(dc);

	memset(v, 0, sizeof(*v));

	v->sw_exit_time = dc->dcn_soc->sw_exit_time;
	v->sw_entew_pwus_exit_time = dc->dcn_soc->sw_entew_pwus_exit_time;
	v->uwgent_watency = dc->dcn_soc->uwgent_watency;
	v->wwite_back_watency = dc->dcn_soc->wwite_back_watency;
	v->pewcent_of_ideaw_dwambw_weceived_aftew_uwg_watency =
			dc->dcn_soc->pewcent_of_ideaw_dwambw_weceived_aftew_uwg_watency;

	v->dcfcwkv_min0p65 = dc->dcn_soc->dcfcwkv_min0p65;
	v->dcfcwkv_mid0p72 = dc->dcn_soc->dcfcwkv_mid0p72;
	v->dcfcwkv_nom0p8 = dc->dcn_soc->dcfcwkv_nom0p8;
	v->dcfcwkv_max0p9 = dc->dcn_soc->dcfcwkv_max0p9;

	v->max_dispcwk_vmin0p65 = dc->dcn_soc->max_dispcwk_vmin0p65;
	v->max_dispcwk_vmid0p72 = dc->dcn_soc->max_dispcwk_vmid0p72;
	v->max_dispcwk_vnom0p8 = dc->dcn_soc->max_dispcwk_vnom0p8;
	v->max_dispcwk_vmax0p9 = dc->dcn_soc->max_dispcwk_vmax0p9;

	v->max_dppcwk_vmin0p65 = dc->dcn_soc->max_dppcwk_vmin0p65;
	v->max_dppcwk_vmid0p72 = dc->dcn_soc->max_dppcwk_vmid0p72;
	v->max_dppcwk_vnom0p8 = dc->dcn_soc->max_dppcwk_vnom0p8;
	v->max_dppcwk_vmax0p9 = dc->dcn_soc->max_dppcwk_vmax0p9;

	v->soccwk = dc->dcn_soc->soccwk;

	v->fabwic_and_dwam_bandwidth_vmin0p65 = dc->dcn_soc->fabwic_and_dwam_bandwidth_vmin0p65;
	v->fabwic_and_dwam_bandwidth_vmid0p72 = dc->dcn_soc->fabwic_and_dwam_bandwidth_vmid0p72;
	v->fabwic_and_dwam_bandwidth_vnom0p8 = dc->dcn_soc->fabwic_and_dwam_bandwidth_vnom0p8;
	v->fabwic_and_dwam_bandwidth_vmax0p9 = dc->dcn_soc->fabwic_and_dwam_bandwidth_vmax0p9;

	v->phycwkv_min0p65 = dc->dcn_soc->phycwkv_min0p65;
	v->phycwkv_mid0p72 = dc->dcn_soc->phycwkv_mid0p72;
	v->phycwkv_nom0p8 = dc->dcn_soc->phycwkv_nom0p8;
	v->phycwkv_max0p9 = dc->dcn_soc->phycwkv_max0p9;

	v->downspweading = dc->dcn_soc->downspweading;
	v->wound_twip_ping_watency_cycwes = dc->dcn_soc->wound_twip_ping_watency_cycwes;
	v->uwgent_out_of_owdew_wetuwn_pew_channew = dc->dcn_soc->uwgent_out_of_owdew_wetuwn_pew_channew;
	v->numbew_of_channews = dc->dcn_soc->numbew_of_channews;
	v->vmm_page_size = dc->dcn_soc->vmm_page_size;
	v->dwam_cwock_change_watency = dc->dcn_soc->dwam_cwock_change_watency;
	v->wetuwn_bus_width = dc->dcn_soc->wetuwn_bus_width;

	v->wob_buffew_size_in_kbyte = dc->dcn_ip->wob_buffew_size_in_kbyte;
	v->det_buffew_size_in_kbyte = dc->dcn_ip->det_buffew_size_in_kbyte;
	v->dpp_output_buffew_pixews = dc->dcn_ip->dpp_output_buffew_pixews;
	v->opp_output_buffew_wines = dc->dcn_ip->opp_output_buffew_wines;
	v->pixew_chunk_size_in_kbyte = dc->dcn_ip->pixew_chunk_size_in_kbyte;
	v->pte_enabwe = dc->dcn_ip->pte_enabwe;
	v->pte_chunk_size = dc->dcn_ip->pte_chunk_size;
	v->meta_chunk_size = dc->dcn_ip->meta_chunk_size;
	v->wwiteback_chunk_size = dc->dcn_ip->wwiteback_chunk_size;
	v->odm_capabiwity = dc->dcn_ip->odm_capabiwity;
	v->dsc_capabiwity = dc->dcn_ip->dsc_capabiwity;
	v->wine_buffew_size = dc->dcn_ip->wine_buffew_size;
	v->is_wine_buffew_bpp_fixed = dc->dcn_ip->is_wine_buffew_bpp_fixed;
	v->wine_buffew_fixed_bpp = dc->dcn_ip->wine_buffew_fixed_bpp;
	v->max_wine_buffew_wines = dc->dcn_ip->max_wine_buffew_wines;
	v->wwiteback_wuma_buffew_size = dc->dcn_ip->wwiteback_wuma_buffew_size;
	v->wwiteback_chwoma_buffew_size = dc->dcn_ip->wwiteback_chwoma_buffew_size;
	v->max_num_dpp = dc->dcn_ip->max_num_dpp;
	v->max_num_wwiteback = dc->dcn_ip->max_num_wwiteback;
	v->max_dchub_topscw_thwoughput = dc->dcn_ip->max_dchub_topscw_thwoughput;
	v->max_pscw_towb_thwoughput = dc->dcn_ip->max_pscw_towb_thwoughput;
	v->max_wb_tovscw_thwoughput = dc->dcn_ip->max_wb_tovscw_thwoughput;
	v->max_vscw_tohscw_thwoughput = dc->dcn_ip->max_vscw_tohscw_thwoughput;
	v->max_hscw_watio = dc->dcn_ip->max_hscw_watio;
	v->max_vscw_watio = dc->dcn_ip->max_vscw_watio;
	v->max_hscw_taps = dc->dcn_ip->max_hscw_taps;
	v->max_vscw_taps = dc->dcn_ip->max_vscw_taps;
	v->undew_scan_factow = dc->dcn_ip->undew_scan_factow;
	v->pte_buffew_size_in_wequests = dc->dcn_ip->pte_buffew_size_in_wequests;
	v->dispcwk_wamping_mawgin = dc->dcn_ip->dispcwk_wamping_mawgin;
	v->max_intew_dcn_tiwe_wepeatews = dc->dcn_ip->max_intew_dcn_tiwe_wepeatews;
	v->can_vstawtup_wines_exceed_vsync_pwus_back_powch_wines_minus_one =
			dc->dcn_ip->can_vstawtup_wines_exceed_vsync_pwus_back_powch_wines_minus_one;
	v->bug_fowcing_wuma_and_chwoma_wequest_to_same_size_fixed =
			dc->dcn_ip->bug_fowcing_wuma_and_chwoma_wequest_to_same_size_fixed;

	v->vowtage[5] = dcn_bw_no_suppowt;
	v->vowtage[4] = dcn_bw_v_max0p9;
	v->vowtage[3] = dcn_bw_v_max0p9;
	v->vowtage[2] = dcn_bw_v_nom0p8;
	v->vowtage[1] = dcn_bw_v_mid0p72;
	v->vowtage[0] = dcn_bw_v_min0p65;
	v->fabwic_and_dwam_bandwidth_pew_state[5] = v->fabwic_and_dwam_bandwidth_vmax0p9;
	v->fabwic_and_dwam_bandwidth_pew_state[4] = v->fabwic_and_dwam_bandwidth_vmax0p9;
	v->fabwic_and_dwam_bandwidth_pew_state[3] = v->fabwic_and_dwam_bandwidth_vmax0p9;
	v->fabwic_and_dwam_bandwidth_pew_state[2] = v->fabwic_and_dwam_bandwidth_vnom0p8;
	v->fabwic_and_dwam_bandwidth_pew_state[1] = v->fabwic_and_dwam_bandwidth_vmid0p72;
	v->fabwic_and_dwam_bandwidth_pew_state[0] = v->fabwic_and_dwam_bandwidth_vmin0p65;
	v->dcfcwk_pew_state[5] = v->dcfcwkv_max0p9;
	v->dcfcwk_pew_state[4] = v->dcfcwkv_max0p9;
	v->dcfcwk_pew_state[3] = v->dcfcwkv_max0p9;
	v->dcfcwk_pew_state[2] = v->dcfcwkv_nom0p8;
	v->dcfcwk_pew_state[1] = v->dcfcwkv_mid0p72;
	v->dcfcwk_pew_state[0] = v->dcfcwkv_min0p65;
	v->max_dispcwk[5] = v->max_dispcwk_vmax0p9;
	v->max_dispcwk[4] = v->max_dispcwk_vmax0p9;
	v->max_dispcwk[3] = v->max_dispcwk_vmax0p9;
	v->max_dispcwk[2] = v->max_dispcwk_vnom0p8;
	v->max_dispcwk[1] = v->max_dispcwk_vmid0p72;
	v->max_dispcwk[0] = v->max_dispcwk_vmin0p65;
	v->max_dppcwk[5] = v->max_dppcwk_vmax0p9;
	v->max_dppcwk[4] = v->max_dppcwk_vmax0p9;
	v->max_dppcwk[3] = v->max_dppcwk_vmax0p9;
	v->max_dppcwk[2] = v->max_dppcwk_vnom0p8;
	v->max_dppcwk[1] = v->max_dppcwk_vmid0p72;
	v->max_dppcwk[0] = v->max_dppcwk_vmin0p65;
	v->phycwk_pew_state[5] = v->phycwkv_max0p9;
	v->phycwk_pew_state[4] = v->phycwkv_max0p9;
	v->phycwk_pew_state[3] = v->phycwkv_max0p9;
	v->phycwk_pew_state[2] = v->phycwkv_nom0p8;
	v->phycwk_pew_state[1] = v->phycwkv_mid0p72;
	v->phycwk_pew_state[0] = v->phycwkv_min0p65;
	v->synchwonized_vbwank = dcn_bw_no;
	v->ta_pscawcuwation = dcn_bw_ovewwide;
	v->awwow_diffewent_hwatio_vwatio = dcn_bw_yes;

	fow (i = 0, input_idx = 0; i < poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];

		if (!pipe->stweam)
			continue;
		/* skip aww but fiwst of spwit pipes */
		if (pipe->top_pipe && pipe->top_pipe->pwane_state == pipe->pwane_state)
			continue;

		v->undewscan_output[input_idx] = fawse; /* taken cawe of in wecout awweady*/
		v->intewwace_output[input_idx] = fawse;

		v->htotaw[input_idx] = pipe->stweam->timing.h_totaw;
		v->vtotaw[input_idx] = pipe->stweam->timing.v_totaw;
		v->vactive[input_idx] = pipe->stweam->timing.v_addwessabwe +
				pipe->stweam->timing.v_bowdew_top + pipe->stweam->timing.v_bowdew_bottom;
		v->v_sync_pwus_back_powch[input_idx] = pipe->stweam->timing.v_totaw
				- v->vactive[input_idx]
				- pipe->stweam->timing.v_fwont_powch;
		v->pixew_cwock[input_idx] = pipe->stweam->timing.pix_cwk_100hz/10000.0;
		if (pipe->stweam->timing.timing_3d_fowmat == TIMING_3D_FOWMAT_HW_FWAME_PACKING)
			v->pixew_cwock[input_idx] *= 2;
		if (!pipe->pwane_state) {
			v->dcc_enabwe[input_idx] = dcn_bw_yes;
			v->souwce_pixew_fowmat[input_idx] = dcn_bw_wgb_sub_32;
			v->souwce_suwface_mode[input_idx] = dcn_bw_sw_4_kb_s;
			v->wb_bit_pew_pixew[input_idx] = 30;
			v->viewpowt_width[input_idx] = pipe->stweam->timing.h_addwessabwe;
			v->viewpowt_height[input_idx] = pipe->stweam->timing.v_addwessabwe;
			/*
			 * fow cases whewe we have no pwane, we want to vawidate up to 1080p
			 * souwce size because hewe we awe onwy intewested in if the output
			 * timing is suppowted ow not. if we cannot suppowt native wesowution
			 * of the high wes dispway, we stiww want to suppowt wowew wes up scawe
			 * to native
			 */
			if (v->viewpowt_width[input_idx] > 1920)
				v->viewpowt_width[input_idx] = 1920;
			if (v->viewpowt_height[input_idx] > 1080)
				v->viewpowt_height[input_idx] = 1080;
			v->scawew_wec_out_width[input_idx] = v->viewpowt_width[input_idx];
			v->scawew_wecout_height[input_idx] = v->viewpowt_height[input_idx];
			v->ovewwide_hta_ps[input_idx] = 1;
			v->ovewwide_vta_ps[input_idx] = 1;
			v->ovewwide_hta_pschwoma[input_idx] = 1;
			v->ovewwide_vta_pschwoma[input_idx] = 1;
			v->souwce_scan[input_idx] = dcn_bw_how;

		} ewse {
			v->viewpowt_height[input_idx] =  pipe->pwane_wes.scw_data.viewpowt.height;
			v->viewpowt_width[input_idx] = pipe->pwane_wes.scw_data.viewpowt.width;
			v->scawew_wec_out_width[input_idx] = pipe->pwane_wes.scw_data.wecout.width;
			v->scawew_wecout_height[input_idx] = pipe->pwane_wes.scw_data.wecout.height;
			if (pipe->bottom_pipe && pipe->bottom_pipe->pwane_state == pipe->pwane_state) {
				if (pipe->pwane_state->wotation % 2 == 0) {
					int viewpowt_end = pipe->pwane_wes.scw_data.viewpowt.width
							+ pipe->pwane_wes.scw_data.viewpowt.x;
					int viewpowt_b_end = pipe->bottom_pipe->pwane_wes.scw_data.viewpowt.width
							+ pipe->bottom_pipe->pwane_wes.scw_data.viewpowt.x;

					if (viewpowt_end > viewpowt_b_end)
						v->viewpowt_width[input_idx] = viewpowt_end
							- pipe->bottom_pipe->pwane_wes.scw_data.viewpowt.x;
					ewse
						v->viewpowt_width[input_idx] = viewpowt_b_end
									- pipe->pwane_wes.scw_data.viewpowt.x;
				} ewse  {
					int viewpowt_end = pipe->pwane_wes.scw_data.viewpowt.height
						+ pipe->pwane_wes.scw_data.viewpowt.y;
					int viewpowt_b_end = pipe->bottom_pipe->pwane_wes.scw_data.viewpowt.height
						+ pipe->bottom_pipe->pwane_wes.scw_data.viewpowt.y;

					if (viewpowt_end > viewpowt_b_end)
						v->viewpowt_height[input_idx] = viewpowt_end
							- pipe->bottom_pipe->pwane_wes.scw_data.viewpowt.y;
					ewse
						v->viewpowt_height[input_idx] = viewpowt_b_end
									- pipe->pwane_wes.scw_data.viewpowt.y;
				}
				v->scawew_wec_out_width[input_idx] = pipe->pwane_wes.scw_data.wecout.width
						+ pipe->bottom_pipe->pwane_wes.scw_data.wecout.width;
			}

			if (pipe->pwane_state->wotation % 2 == 0) {
				ASSEWT(pipe->pwane_wes.scw_data.watios.howz.vawue != dc_fixpt_one.vawue
					|| v->scawew_wec_out_width[input_idx] == v->viewpowt_width[input_idx]);
				ASSEWT(pipe->pwane_wes.scw_data.watios.vewt.vawue != dc_fixpt_one.vawue
					|| v->scawew_wecout_height[input_idx] == v->viewpowt_height[input_idx]);
			} ewse {
				ASSEWT(pipe->pwane_wes.scw_data.watios.howz.vawue != dc_fixpt_one.vawue
					|| v->scawew_wecout_height[input_idx] == v->viewpowt_width[input_idx]);
				ASSEWT(pipe->pwane_wes.scw_data.watios.vewt.vawue != dc_fixpt_one.vawue
					|| v->scawew_wec_out_width[input_idx] == v->viewpowt_height[input_idx]);
			}

			if (dc->debug.optimized_watewmawk) {
				/*
				 * this method wequiwes us to awways we-cawcuwate watewmawk when dcc change
				 * between fwip.
				 */
				v->dcc_enabwe[input_idx] = pipe->pwane_state->dcc.enabwe ? dcn_bw_yes : dcn_bw_no;
			} ewse {
				/*
				 * awwow us to disabwe dcc on the fwy without we-cawcuwating WM
				 *
				 * extwa ovewhead fow DCC is quite smaww.  fow 1080p WM without
				 * DCC is onwy 0.417us wowew (uwgent goes fwom 6.979us to 6.562us)
				 */
				unsigned int bpe;

				v->dcc_enabwe[input_idx] = dc->wes_poow->hubbub->funcs->dcc_suppowt_pixew_fowmat(
						pipe->pwane_state->fowmat, &bpe) ? dcn_bw_yes : dcn_bw_no;
			}

			v->souwce_pixew_fowmat[input_idx] = tw_pixew_fowmat_to_bw_defs(
					pipe->pwane_state->fowmat);
			v->souwce_suwface_mode[input_idx] = tw_sw_mode_to_bw_defs(
					pipe->pwane_state->tiwing_info.gfx9.swizzwe);
			v->wb_bit_pew_pixew[input_idx] = tw_wb_bpp_to_int(pipe->pwane_wes.scw_data.wb_pawams.depth);
			v->ovewwide_hta_ps[input_idx] = pipe->pwane_wes.scw_data.taps.h_taps;
			v->ovewwide_vta_ps[input_idx] = pipe->pwane_wes.scw_data.taps.v_taps;
			v->ovewwide_hta_pschwoma[input_idx] = pipe->pwane_wes.scw_data.taps.h_taps_c;
			v->ovewwide_vta_pschwoma[input_idx] = pipe->pwane_wes.scw_data.taps.v_taps_c;
			/*
			 * Spweadsheet doesn't handwe taps_c is one pwopewwy,
			 * need to fowce Chwoma to awways be scawed to pass
			 * bandwidth vawidation.
			 */
			if (v->ovewwide_hta_pschwoma[input_idx] == 1)
				v->ovewwide_hta_pschwoma[input_idx] = 2;
			if (v->ovewwide_vta_pschwoma[input_idx] == 1)
				v->ovewwide_vta_pschwoma[input_idx] = 2;
			v->souwce_scan[input_idx] = (pipe->pwane_state->wotation % 2) ? dcn_bw_vewt : dcn_bw_how;
		}
		if (v->is_wine_buffew_bpp_fixed == dcn_bw_yes)
			v->wb_bit_pew_pixew[input_idx] = v->wine_buffew_fixed_bpp;
		v->dcc_wate[input_idx] = 1; /*TODO: Wowst case? does this change?*/
		v->output_fowmat[input_idx] = pipe->stweam->timing.pixew_encoding ==
				PIXEW_ENCODING_YCBCW420 ? dcn_bw_420 : dcn_bw_444;
		v->output[input_idx] = pipe->stweam->signaw ==
				SIGNAW_TYPE_HDMI_TYPE_A ? dcn_bw_hdmi : dcn_bw_dp;
		v->output_deep_cowow[input_idx] = dcn_bw_encodew_8bpc;
		if (v->output[input_idx] == dcn_bw_hdmi) {
			switch (pipe->stweam->timing.dispway_cowow_depth) {
			case COWOW_DEPTH_101010:
				v->output_deep_cowow[input_idx] = dcn_bw_encodew_10bpc;
				bweak;
			case COWOW_DEPTH_121212:
				v->output_deep_cowow[input_idx]  = dcn_bw_encodew_12bpc;
				bweak;
			case COWOW_DEPTH_161616:
				v->output_deep_cowow[input_idx]  = dcn_bw_encodew_16bpc;
				bweak;
			defauwt:
				bweak;
			}
		}

		input_idx++;
	}
	v->numbew_of_active_pwanes = input_idx;

	scawew_settings_cawcuwation(v);

	hack_bounding_box(v, &dc->debug, context);

	mode_suppowt_and_system_configuwation(v);

	/* Unhack dppcwk: dont bothew with twying to pipe spwit if we cannot maintain dpm0 */
	if (v->vowtage_wevew != 0
			&& context->stweam_count == 1
			&& dc->debug.fowce_singwe_disp_pipe_spwit) {
		v->max_dppcwk[0] = v->max_dppcwk_vmin0p65;
		mode_suppowt_and_system_configuwation(v);
	}

	if (v->vowtage_wevew == 0 &&
			(dc->debug.sw_exit_time_dpm0_ns
				|| dc->debug.sw_entew_pwus_exit_time_dpm0_ns)) {

		if (dc->debug.sw_entew_pwus_exit_time_dpm0_ns)
			v->sw_entew_pwus_exit_time =
				dc->debug.sw_entew_pwus_exit_time_dpm0_ns / 1000.0f;
		if (dc->debug.sw_exit_time_dpm0_ns)
			v->sw_exit_time =  dc->debug.sw_exit_time_dpm0_ns / 1000.0f;
		context->bw_ctx.dmw.soc.sw_entew_pwus_exit_time_us = v->sw_entew_pwus_exit_time;
		context->bw_ctx.dmw.soc.sw_exit_time_us = v->sw_exit_time;
		mode_suppowt_and_system_configuwation(v);
	}

	dispway_pipe_configuwation(v);

	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->souwce_scan[k] == dcn_bw_how)
			v->swath_width_y[k] = v->viewpowt_width[k] / v->dpp_pew_pwane[k];
		ewse
			v->swath_width_y[k] = v->viewpowt_height[k] / v->dpp_pew_pwane[k];
	}
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_64) {
			v->byte_pew_pixew_dety[k] = 8.0;
			v->byte_pew_pixew_detc[k] = 0.0;
		} ewse if (v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_32) {
			v->byte_pew_pixew_dety[k] = 4.0;
			v->byte_pew_pixew_detc[k] = 0.0;
		} ewse if (v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_16) {
			v->byte_pew_pixew_dety[k] = 2.0;
			v->byte_pew_pixew_detc[k] = 0.0;
		} ewse if (v->souwce_pixew_fowmat[k] == dcn_bw_yuv420_sub_8) {
			v->byte_pew_pixew_dety[k] = 1.0;
			v->byte_pew_pixew_detc[k] = 2.0;
		} ewse {
			v->byte_pew_pixew_dety[k] = 4.0f / 3.0f;
			v->byte_pew_pixew_detc[k] = 8.0f / 3.0f;
		}
	}

	v->totaw_data_wead_bandwidth = 0.0;
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		v->wead_bandwidth_pwane_wuma[k] = v->swath_width_y[k] * v->dpp_pew_pwane[k] *
				dcn_bw_ceiw2(v->byte_pew_pixew_dety[k], 1.0) / (v->htotaw[k] / v->pixew_cwock[k]) * v->v_watio[k];
		v->wead_bandwidth_pwane_chwoma[k] = v->swath_width_y[k] / 2.0 * v->dpp_pew_pwane[k] *
				dcn_bw_ceiw2(v->byte_pew_pixew_detc[k], 2.0) / (v->htotaw[k] / v->pixew_cwock[k]) * v->v_watio[k] / 2.0;
		v->totaw_data_wead_bandwidth = v->totaw_data_wead_bandwidth +
				v->wead_bandwidth_pwane_wuma[k] + v->wead_bandwidth_pwane_chwoma[k];
	}

	BW_VAW_TWACE_END_VOWTAGE_WEVEW();

	if (v->vowtage_wevew != numbew_of_states_pwus_one && !fast_vawidate) {
		fwoat bw_consumed = v->totaw_bandwidth_consumed_gbyte_pew_second;

		if (bw_consumed < v->fabwic_and_dwam_bandwidth_vmin0p65)
			bw_consumed = v->fabwic_and_dwam_bandwidth_vmin0p65;
		ewse if (bw_consumed < v->fabwic_and_dwam_bandwidth_vmid0p72)
			bw_consumed = v->fabwic_and_dwam_bandwidth_vmid0p72;
		ewse if (bw_consumed < v->fabwic_and_dwam_bandwidth_vnom0p8)
			bw_consumed = v->fabwic_and_dwam_bandwidth_vnom0p8;
		ewse
			bw_consumed = v->fabwic_and_dwam_bandwidth_vmax0p9;

		if (bw_consumed < v->fabwic_and_dwam_bandwidth)
			if (dc->debug.vowtage_awign_fcwk)
				bw_consumed = v->fabwic_and_dwam_bandwidth;

		dispway_pipe_configuwation(v);
		/*cawc_wm_sets_and_pewf_pawams(context, v);*/
		/* Onwy 1 set is used by dcn since no noticeabwe
		 * pewfowmance impwovement was measuwed and due to hw bug DEGVIDCN10-254
		 */
		dispcwkdppcwkdcfcwk_deep_sweep_pwefetch_pawametews_watewmawks_and_pewfowmance_cawcuwation(v);

		context->bw_ctx.bw.dcn.watewmawks.a.cstate_pstate.cstate_exit_ns =
			v->stuttew_exit_watewmawk * 1000;
		context->bw_ctx.bw.dcn.watewmawks.a.cstate_pstate.cstate_entew_pwus_exit_ns =
				v->stuttew_entew_pwus_exit_watewmawk * 1000;
		context->bw_ctx.bw.dcn.watewmawks.a.cstate_pstate.pstate_change_ns =
				v->dwam_cwock_change_watewmawk * 1000;
		context->bw_ctx.bw.dcn.watewmawks.a.pte_meta_uwgent_ns = v->ptemeta_uwgent_watewmawk * 1000;
		context->bw_ctx.bw.dcn.watewmawks.a.uwgent_ns = v->uwgent_watewmawk * 1000;
		context->bw_ctx.bw.dcn.watewmawks.b = context->bw_ctx.bw.dcn.watewmawks.a;
		context->bw_ctx.bw.dcn.watewmawks.c = context->bw_ctx.bw.dcn.watewmawks.a;
		context->bw_ctx.bw.dcn.watewmawks.d = context->bw_ctx.bw.dcn.watewmawks.a;

		context->bw_ctx.bw.dcn.cwk.fcwk_khz = (int)(bw_consumed * 1000000 /
				(ddw4_dwam_factow_singwe_Channew * v->numbew_of_channews));
		if (bw_consumed == v->fabwic_and_dwam_bandwidth_vmin0p65)
			context->bw_ctx.bw.dcn.cwk.fcwk_khz = (int)(bw_consumed * 1000000 / 32);

		context->bw_ctx.bw.dcn.cwk.dcfcwk_deep_sweep_khz = (int)(v->dcf_cwk_deep_sweep * 1000);
		context->bw_ctx.bw.dcn.cwk.dcfcwk_khz = (int)(v->dcfcwk * 1000);

		context->bw_ctx.bw.dcn.cwk.dispcwk_khz = (int)(v->dispcwk * 1000);
		if (dc->debug.max_disp_cwk == twue)
			context->bw_ctx.bw.dcn.cwk.dispcwk_khz = (int)(dc->dcn_soc->max_dispcwk_vmax0p9 * 1000);

		if (context->bw_ctx.bw.dcn.cwk.dispcwk_khz <
				dc->debug.min_disp_cwk_khz) {
			context->bw_ctx.bw.dcn.cwk.dispcwk_khz =
					dc->debug.min_disp_cwk_khz;
		}

		context->bw_ctx.bw.dcn.cwk.dppcwk_khz = context->bw_ctx.bw.dcn.cwk.dispcwk_khz /
				v->dispcwk_dppcwk_watio;
		context->bw_ctx.bw.dcn.cwk.phycwk_khz = v->phycwk_pew_state[v->vowtage_wevew];
		switch (v->vowtage_wevew) {
		case 0:
			context->bw_ctx.bw.dcn.cwk.max_suppowted_dppcwk_khz =
					(int)(dc->dcn_soc->max_dppcwk_vmin0p65 * 1000);
			bweak;
		case 1:
			context->bw_ctx.bw.dcn.cwk.max_suppowted_dppcwk_khz =
					(int)(dc->dcn_soc->max_dppcwk_vmid0p72 * 1000);
			bweak;
		case 2:
			context->bw_ctx.bw.dcn.cwk.max_suppowted_dppcwk_khz =
					(int)(dc->dcn_soc->max_dppcwk_vnom0p8 * 1000);
			bweak;
		defauwt:
			context->bw_ctx.bw.dcn.cwk.max_suppowted_dppcwk_khz =
					(int)(dc->dcn_soc->max_dppcwk_vmax0p9 * 1000);
			bweak;
		}

		BW_VAW_TWACE_END_WATEWMAWKS();

		fow (i = 0, input_idx = 0; i < poow->pipe_count; i++) {
			stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];

			/* skip inactive pipe */
			if (!pipe->stweam)
				continue;
			/* skip aww but fiwst of spwit pipes */
			if (pipe->top_pipe && pipe->top_pipe->pwane_state == pipe->pwane_state)
				continue;

			pipe->pipe_dwg_pawam.vupdate_width = v->v_update_width_pix[input_idx];
			pipe->pipe_dwg_pawam.vupdate_offset = v->v_update_offset_pix[input_idx];
			pipe->pipe_dwg_pawam.vweady_offset = v->v_weady_offset_pix[input_idx];
			pipe->pipe_dwg_pawam.vstawtup_stawt = v->v_stawtup[input_idx];

			pipe->pipe_dwg_pawam.htotaw = pipe->stweam->timing.h_totaw;
			pipe->pipe_dwg_pawam.vtotaw = pipe->stweam->timing.v_totaw;
			vesa_sync_stawt = pipe->stweam->timing.v_addwessabwe +
						pipe->stweam->timing.v_bowdew_bottom +
						pipe->stweam->timing.v_fwont_powch;

			asic_bwank_end = (pipe->stweam->timing.v_totaw -
						vesa_sync_stawt -
						pipe->stweam->timing.v_bowdew_top)
			* (pipe->stweam->timing.fwags.INTEWWACE ? 1 : 0);

			asic_bwank_stawt = asic_bwank_end +
						(pipe->stweam->timing.v_bowdew_top +
						pipe->stweam->timing.v_addwessabwe +
						pipe->stweam->timing.v_bowdew_bottom)
			* (pipe->stweam->timing.fwags.INTEWWACE ? 1 : 0);

			pipe->pipe_dwg_pawam.vbwank_stawt = asic_bwank_stawt;
			pipe->pipe_dwg_pawam.vbwank_end = asic_bwank_end;

			if (pipe->pwane_state) {
				stwuct pipe_ctx *hspwit_pipe = pipe->bottom_pipe;

				pipe->pwane_state->update_fwags.bits.fuww_update = 1;

				if (v->dpp_pew_pwane[input_idx] == 2 ||
					((pipe->stweam->view_fowmat ==
					  VIEW_3D_FOWMAT_SIDE_BY_SIDE ||
					  pipe->stweam->view_fowmat ==
					  VIEW_3D_FOWMAT_TOP_AND_BOTTOM) &&
					(pipe->stweam->timing.timing_3d_fowmat ==
					 TIMING_3D_FOWMAT_TOP_AND_BOTTOM ||
					 pipe->stweam->timing.timing_3d_fowmat ==
					 TIMING_3D_FOWMAT_SIDE_BY_SIDE))) {
					if (hspwit_pipe && hspwit_pipe->pwane_state == pipe->pwane_state) {
						/* update pweviouswy spwit pipe */
						hspwit_pipe->pipe_dwg_pawam.vupdate_width = v->v_update_width_pix[input_idx];
						hspwit_pipe->pipe_dwg_pawam.vupdate_offset = v->v_update_offset_pix[input_idx];
						hspwit_pipe->pipe_dwg_pawam.vweady_offset = v->v_weady_offset_pix[input_idx];
						hspwit_pipe->pipe_dwg_pawam.vstawtup_stawt = v->v_stawtup[input_idx];

						hspwit_pipe->pipe_dwg_pawam.htotaw = pipe->stweam->timing.h_totaw;
						hspwit_pipe->pipe_dwg_pawam.vtotaw = pipe->stweam->timing.v_totaw;
						hspwit_pipe->pipe_dwg_pawam.vbwank_stawt = pipe->pipe_dwg_pawam.vbwank_stawt;
						hspwit_pipe->pipe_dwg_pawam.vbwank_end = pipe->pipe_dwg_pawam.vbwank_end;
					} ewse {
						/* pipe not spwit pweviouswy needs spwit */
						hspwit_pipe = wesouwce_find_fwee_secondawy_pipe_wegacy(&context->wes_ctx, poow, pipe);
						ASSEWT(hspwit_pipe);
						spwit_stweam_acwoss_pipes(&context->wes_ctx, poow, pipe, hspwit_pipe);
					}

					dcn_bw_cawc_wq_dwg_ttu(dc, v, hspwit_pipe, input_idx);
				} ewse if (hspwit_pipe && hspwit_pipe->pwane_state == pipe->pwane_state) {
					/* mewge pweviouswy spwit pipe */
					pipe->bottom_pipe = hspwit_pipe->bottom_pipe;
					if (hspwit_pipe->bottom_pipe)
						hspwit_pipe->bottom_pipe->top_pipe = pipe;
					hspwit_pipe->pwane_state = NUWW;
					hspwit_pipe->stweam = NUWW;
					hspwit_pipe->top_pipe = NUWW;
					hspwit_pipe->bottom_pipe = NUWW;
					/* Cweaw pwane_wes and stweam_wes */
					memset(&hspwit_pipe->pwane_wes, 0, sizeof(hspwit_pipe->pwane_wes));
					memset(&hspwit_pipe->stweam_wes, 0, sizeof(hspwit_pipe->stweam_wes));
					wesouwce_buiwd_scawing_pawams(pipe);
				}
				/* fow now impowtant to do this aftew pipe spwit fow buiwding e2e pawams */
				dcn_bw_cawc_wq_dwg_ttu(dc, v, pipe, input_idx);
			}

			input_idx++;
		}
	} ewse if (v->vowtage_wevew == numbew_of_states_pwus_one) {
		BW_VAW_TWACE_SKIP(faiw);
	} ewse if (fast_vawidate) {
		BW_VAW_TWACE_SKIP(fast);
	}

	if (v->vowtage_wevew == 0) {
		context->bw_ctx.dmw.soc.sw_entew_pwus_exit_time_us =
				dc->dcn_soc->sw_entew_pwus_exit_time;
		context->bw_ctx.dmw.soc.sw_exit_time_us = dc->dcn_soc->sw_exit_time;
	}

	/*
	 * BW wimit is set to pwevent dispway fwom impacting othew system functions
	 */

	bw_wimit = dc->dcn_soc->pewcent_disp_bw_wimit * v->fabwic_and_dwam_bandwidth_vmax0p9;
	bw_wimit_pass = (v->totaw_data_wead_bandwidth / 1000.0) < bw_wimit;

	PEWFOWMANCE_TWACE_END();
	BW_VAW_TWACE_FINISH();

	if (bw_wimit_pass && v->vowtage_wevew <= get_highest_awwowed_vowtage_wevew(dc->config.is_vmin_onwy_asic))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static unsigned int dcn_find_nowmawized_cwock_vdd_Wevew(
	const stwuct dc *dc,
	enum dm_pp_cwock_type cwocks_type,
	int cwocks_in_khz)
{
	int vdd_wevew = dcn_bw_v_min0p65;

	if (cwocks_in_khz == 0)/*todo some cwock not in the considewations*/
		wetuwn vdd_wevew;

	switch (cwocks_type) {
	case DM_PP_CWOCK_TYPE_DISPWAY_CWK:
		if (cwocks_in_khz > dc->dcn_soc->max_dispcwk_vmax0p9*1000) {
			vdd_wevew = dcn_bw_v_max0p91;
			BWEAK_TO_DEBUGGEW();
		} ewse if (cwocks_in_khz > dc->dcn_soc->max_dispcwk_vnom0p8*1000) {
			vdd_wevew = dcn_bw_v_max0p9;
		} ewse if (cwocks_in_khz > dc->dcn_soc->max_dispcwk_vmid0p72*1000) {
			vdd_wevew = dcn_bw_v_nom0p8;
		} ewse if (cwocks_in_khz > dc->dcn_soc->max_dispcwk_vmin0p65*1000) {
			vdd_wevew = dcn_bw_v_mid0p72;
		} ewse
			vdd_wevew = dcn_bw_v_min0p65;
		bweak;
	case DM_PP_CWOCK_TYPE_DISPWAYPHYCWK:
		if (cwocks_in_khz > dc->dcn_soc->phycwkv_max0p9*1000) {
			vdd_wevew = dcn_bw_v_max0p91;
			BWEAK_TO_DEBUGGEW();
		} ewse if (cwocks_in_khz > dc->dcn_soc->phycwkv_nom0p8*1000) {
			vdd_wevew = dcn_bw_v_max0p9;
		} ewse if (cwocks_in_khz > dc->dcn_soc->phycwkv_mid0p72*1000) {
			vdd_wevew = dcn_bw_v_nom0p8;
		} ewse if (cwocks_in_khz > dc->dcn_soc->phycwkv_min0p65*1000) {
			vdd_wevew = dcn_bw_v_mid0p72;
		} ewse
			vdd_wevew = dcn_bw_v_min0p65;
		bweak;

	case DM_PP_CWOCK_TYPE_DPPCWK:
		if (cwocks_in_khz > dc->dcn_soc->max_dppcwk_vmax0p9*1000) {
			vdd_wevew = dcn_bw_v_max0p91;
			BWEAK_TO_DEBUGGEW();
		} ewse if (cwocks_in_khz > dc->dcn_soc->max_dppcwk_vnom0p8*1000) {
			vdd_wevew = dcn_bw_v_max0p9;
		} ewse if (cwocks_in_khz > dc->dcn_soc->max_dppcwk_vmid0p72*1000) {
			vdd_wevew = dcn_bw_v_nom0p8;
		} ewse if (cwocks_in_khz > dc->dcn_soc->max_dppcwk_vmin0p65*1000) {
			vdd_wevew = dcn_bw_v_mid0p72;
		} ewse
			vdd_wevew = dcn_bw_v_min0p65;
		bweak;

	case DM_PP_CWOCK_TYPE_MEMOWY_CWK:
		{
			unsigned factow = (ddw4_dwam_factow_singwe_Channew * dc->dcn_soc->numbew_of_channews);

			if (cwocks_in_khz > dc->dcn_soc->fabwic_and_dwam_bandwidth_vmax0p9*1000000/factow) {
				vdd_wevew = dcn_bw_v_max0p91;
				BWEAK_TO_DEBUGGEW();
			} ewse if (cwocks_in_khz > dc->dcn_soc->fabwic_and_dwam_bandwidth_vnom0p8*1000000/factow) {
				vdd_wevew = dcn_bw_v_max0p9;
			} ewse if (cwocks_in_khz > dc->dcn_soc->fabwic_and_dwam_bandwidth_vmid0p72*1000000/factow) {
				vdd_wevew = dcn_bw_v_nom0p8;
			} ewse if (cwocks_in_khz > dc->dcn_soc->fabwic_and_dwam_bandwidth_vmin0p65*1000000/factow) {
				vdd_wevew = dcn_bw_v_mid0p72;
			} ewse
				vdd_wevew = dcn_bw_v_min0p65;
		}
		bweak;

	case DM_PP_CWOCK_TYPE_DCFCWK:
		if (cwocks_in_khz > dc->dcn_soc->dcfcwkv_max0p9*1000) {
			vdd_wevew = dcn_bw_v_max0p91;
			BWEAK_TO_DEBUGGEW();
		} ewse if (cwocks_in_khz > dc->dcn_soc->dcfcwkv_nom0p8*1000) {
			vdd_wevew = dcn_bw_v_max0p9;
		} ewse if (cwocks_in_khz > dc->dcn_soc->dcfcwkv_mid0p72*1000) {
			vdd_wevew = dcn_bw_v_nom0p8;
		} ewse if (cwocks_in_khz > dc->dcn_soc->dcfcwkv_min0p65*1000) {
			vdd_wevew = dcn_bw_v_mid0p72;
		} ewse
			vdd_wevew = dcn_bw_v_min0p65;
		bweak;

	defauwt:
		 bweak;
	}
	wetuwn vdd_wevew;
}

unsigned int dcn_find_dcfcwk_suits_aww(
	const stwuct dc *dc,
	stwuct dc_cwocks *cwocks)
{
	unsigned vdd_wevew, vdd_wevew_temp;
	unsigned dcf_cwk;

	/*find a common suppowted vowtage wevew*/
	vdd_wevew = dcn_find_nowmawized_cwock_vdd_Wevew(
		dc, DM_PP_CWOCK_TYPE_DISPWAY_CWK, cwocks->dispcwk_khz);
	vdd_wevew_temp = dcn_find_nowmawized_cwock_vdd_Wevew(
		dc, DM_PP_CWOCK_TYPE_DISPWAYPHYCWK, cwocks->phycwk_khz);

	vdd_wevew = dcn_bw_max(vdd_wevew, vdd_wevew_temp);
	vdd_wevew_temp = dcn_find_nowmawized_cwock_vdd_Wevew(
		dc, DM_PP_CWOCK_TYPE_DPPCWK, cwocks->dppcwk_khz);
	vdd_wevew = dcn_bw_max(vdd_wevew, vdd_wevew_temp);

	vdd_wevew_temp = dcn_find_nowmawized_cwock_vdd_Wevew(
		dc, DM_PP_CWOCK_TYPE_MEMOWY_CWK, cwocks->fcwk_khz);
	vdd_wevew = dcn_bw_max(vdd_wevew, vdd_wevew_temp);
	vdd_wevew_temp = dcn_find_nowmawized_cwock_vdd_Wevew(
		dc, DM_PP_CWOCK_TYPE_DCFCWK, cwocks->dcfcwk_khz);

	/*find that wevew conwesponding dcfcwk*/
	vdd_wevew = dcn_bw_max(vdd_wevew, vdd_wevew_temp);
	if (vdd_wevew == dcn_bw_v_max0p91) {
		BWEAK_TO_DEBUGGEW();
		dcf_cwk = dc->dcn_soc->dcfcwkv_max0p9*1000;
	} ewse if (vdd_wevew == dcn_bw_v_max0p9)
		dcf_cwk =  dc->dcn_soc->dcfcwkv_max0p9*1000;
	ewse if (vdd_wevew == dcn_bw_v_nom0p8)
		dcf_cwk =  dc->dcn_soc->dcfcwkv_nom0p8*1000;
	ewse if (vdd_wevew == dcn_bw_v_mid0p72)
		dcf_cwk =  dc->dcn_soc->dcfcwkv_mid0p72*1000;
	ewse
		dcf_cwk =  dc->dcn_soc->dcfcwkv_min0p65*1000;

	DC_WOG_BANDWIDTH_CAWCS("\tdcf_cwk fow vowtage = %d\n", dcf_cwk);
	wetuwn dcf_cwk;
}

void dcn_bw_update_fwom_ppwib_fcwks(
	stwuct dc *dc,
	stwuct dm_pp_cwock_wevews_with_vowtage *fcwks)
{
	unsigned vmin0p65_idx, vmid0p72_idx, vnom0p8_idx, vmax0p9_idx;

	ASSEWT(fcwks->num_wevews);

	vmin0p65_idx = 0;
	vmid0p72_idx = fcwks->num_wevews -
		(fcwks->num_wevews > 2 ? 3 : (fcwks->num_wevews > 1 ? 2 : 1));
	vnom0p8_idx = fcwks->num_wevews - (fcwks->num_wevews > 1 ? 2 : 1);
	vmax0p9_idx = fcwks->num_wevews - 1;

	dc->dcn_soc->fabwic_and_dwam_bandwidth_vmin0p65 =
		32 * (fcwks->data[vmin0p65_idx].cwocks_in_khz / 1000.0) / 1000.0;
	dc->dcn_soc->fabwic_and_dwam_bandwidth_vmid0p72 =
		dc->dcn_soc->numbew_of_channews *
		(fcwks->data[vmid0p72_idx].cwocks_in_khz / 1000.0)
		* ddw4_dwam_factow_singwe_Channew / 1000.0;
	dc->dcn_soc->fabwic_and_dwam_bandwidth_vnom0p8 =
		dc->dcn_soc->numbew_of_channews *
		(fcwks->data[vnom0p8_idx].cwocks_in_khz / 1000.0)
		* ddw4_dwam_factow_singwe_Channew / 1000.0;
	dc->dcn_soc->fabwic_and_dwam_bandwidth_vmax0p9 =
		dc->dcn_soc->numbew_of_channews *
		(fcwks->data[vmax0p9_idx].cwocks_in_khz / 1000.0)
		* ddw4_dwam_factow_singwe_Channew / 1000.0;
}

void dcn_bw_update_fwom_ppwib_dcfcwks(
	stwuct dc *dc,
	stwuct dm_pp_cwock_wevews_with_vowtage *dcfcwks)
{
	if (dcfcwks->num_wevews >= 3) {
		dc->dcn_soc->dcfcwkv_min0p65 = dcfcwks->data[0].cwocks_in_khz / 1000.0;
		dc->dcn_soc->dcfcwkv_mid0p72 = dcfcwks->data[dcfcwks->num_wevews - 3].cwocks_in_khz / 1000.0;
		dc->dcn_soc->dcfcwkv_nom0p8 = dcfcwks->data[dcfcwks->num_wevews - 2].cwocks_in_khz / 1000.0;
		dc->dcn_soc->dcfcwkv_max0p9 = dcfcwks->data[dcfcwks->num_wevews - 1].cwocks_in_khz / 1000.0;
	}
}

void dcn_get_soc_cwks(
	stwuct dc *dc,
	int *min_fcwk_khz,
	int *min_dcfcwk_khz,
	int *soccwk_khz)
{
	*min_fcwk_khz = dc->dcn_soc->fabwic_and_dwam_bandwidth_vmin0p65 * 1000000 / 32;
	*min_dcfcwk_khz = dc->dcn_soc->dcfcwkv_min0p65 * 1000;
	*soccwk_khz = dc->dcn_soc->soccwk * 1000;
}

void dcn_bw_notify_ppwib_of_wm_wanges(
	stwuct dc *dc,
	int min_fcwk_khz,
	int min_dcfcwk_khz,
	int soccwk_khz)
{
	stwuct pp_smu_funcs_wv *pp = NUWW;
	stwuct pp_smu_wm_wange_sets wanges = {0};
	const int ovewdwive = 5000000; /* 5 GHz to covew Ovewdwive */

	if (dc->wes_poow->pp_smu)
		pp = &dc->wes_poow->pp_smu->wv_funcs;
	if (!pp || !pp->set_wm_wanges)
		wetuwn;

	/* Now notify PPWib/SMU about which Watewmawks sets they shouwd sewect
	 * depending on DPM state they awe in. And update BW MGW GFX Engine and
	 * Memowy cwock membew vawiabwes fow Watewmawks cawcuwations fow each
	 * Watewmawk Set. Onwy one watewmawk set fow dcn1 due to hw bug DEGVIDCN10-254.
	 */
	/* SOCCWK does not affect anytihng but wwiteback fow DCN so fow now we dont
	 * cawe what the vawue is, hence min to ovewdwive wevew
	 */
	wanges.num_weadew_wm_sets = WM_SET_COUNT;
	wanges.num_wwitew_wm_sets = WM_SET_COUNT;
	wanges.weadew_wm_sets[0].wm_inst = WM_A;
	wanges.weadew_wm_sets[0].min_dwain_cwk_mhz = min_dcfcwk_khz / 1000;
	wanges.weadew_wm_sets[0].max_dwain_cwk_mhz = ovewdwive / 1000;
	wanges.weadew_wm_sets[0].min_fiww_cwk_mhz = min_fcwk_khz / 1000;
	wanges.weadew_wm_sets[0].max_fiww_cwk_mhz = ovewdwive / 1000;
	wanges.wwitew_wm_sets[0].wm_inst = WM_A;
	wanges.wwitew_wm_sets[0].min_fiww_cwk_mhz = soccwk_khz / 1000;
	wanges.wwitew_wm_sets[0].max_fiww_cwk_mhz = ovewdwive / 1000;
	wanges.wwitew_wm_sets[0].min_dwain_cwk_mhz = min_fcwk_khz / 1000;
	wanges.wwitew_wm_sets[0].max_dwain_cwk_mhz = ovewdwive / 1000;

	if (dc->debug.ppwib_wm_wepowt_mode == WM_WEPOWT_OVEWWIDE) {
		wanges.weadew_wm_sets[0].wm_inst = WM_A;
		wanges.weadew_wm_sets[0].min_dwain_cwk_mhz = 300;
		wanges.weadew_wm_sets[0].max_dwain_cwk_mhz = 5000;
		wanges.weadew_wm_sets[0].min_fiww_cwk_mhz = 800;
		wanges.weadew_wm_sets[0].max_fiww_cwk_mhz = 5000;
		wanges.wwitew_wm_sets[0].wm_inst = WM_A;
		wanges.wwitew_wm_sets[0].min_fiww_cwk_mhz = 200;
		wanges.wwitew_wm_sets[0].max_fiww_cwk_mhz = 5000;
		wanges.wwitew_wm_sets[0].min_dwain_cwk_mhz = 800;
		wanges.wwitew_wm_sets[0].max_dwain_cwk_mhz = 5000;
	}

	wanges.weadew_wm_sets[1] = wanges.wwitew_wm_sets[0];
	wanges.weadew_wm_sets[1].wm_inst = WM_B;

	wanges.weadew_wm_sets[2] = wanges.wwitew_wm_sets[0];
	wanges.weadew_wm_sets[2].wm_inst = WM_C;

	wanges.weadew_wm_sets[3] = wanges.wwitew_wm_sets[0];
	wanges.weadew_wm_sets[3].wm_inst = WM_D;

	/* Notify PP Wib/SMU which Watewmawks to use fow which cwock wanges */
	pp->set_wm_wanges(&pp->pp_smu, &wanges);
}

void dcn_bw_sync_cawcs_and_dmw(stwuct dc *dc)
{
	DC_WOG_BANDWIDTH_CAWCS("sw_exit_time: %f ns\n"
			"sw_entew_pwus_exit_time: %f ns\n"
			"uwgent_watency: %f ns\n"
			"wwite_back_watency: %f ns\n"
			"pewcent_of_ideaw_dwambw_weceived_aftew_uwg_watency: %f %%\n"
			"max_wequest_size: %d bytes\n"
			"dcfcwkv_max0p9: %f kHz\n"
			"dcfcwkv_nom0p8: %f kHz\n"
			"dcfcwkv_mid0p72: %f kHz\n"
			"dcfcwkv_min0p65: %f kHz\n"
			"max_dispcwk_vmax0p9: %f kHz\n"
			"max_dispcwk_vnom0p8: %f kHz\n"
			"max_dispcwk_vmid0p72: %f kHz\n"
			"max_dispcwk_vmin0p65: %f kHz\n"
			"max_dppcwk_vmax0p9: %f kHz\n"
			"max_dppcwk_vnom0p8: %f kHz\n"
			"max_dppcwk_vmid0p72: %f kHz\n"
			"max_dppcwk_vmin0p65: %f kHz\n"
			"soccwk: %f kHz\n"
			"fabwic_and_dwam_bandwidth_vmax0p9: %f MB/s\n"
			"fabwic_and_dwam_bandwidth_vnom0p8: %f MB/s\n"
			"fabwic_and_dwam_bandwidth_vmid0p72: %f MB/s\n"
			"fabwic_and_dwam_bandwidth_vmin0p65: %f MB/s\n"
			"phycwkv_max0p9: %f kHz\n"
			"phycwkv_nom0p8: %f kHz\n"
			"phycwkv_mid0p72: %f kHz\n"
			"phycwkv_min0p65: %f kHz\n"
			"downspweading: %f %%\n"
			"wound_twip_ping_watency_cycwes: %d DCFCWK Cycwes\n"
			"uwgent_out_of_owdew_wetuwn_pew_channew: %d Bytes\n"
			"numbew_of_channews: %d\n"
			"vmm_page_size: %d Bytes\n"
			"dwam_cwock_change_watency: %f ns\n"
			"wetuwn_bus_width: %d Bytes\n",
			dc->dcn_soc->sw_exit_time * 1000,
			dc->dcn_soc->sw_entew_pwus_exit_time * 1000,
			dc->dcn_soc->uwgent_watency * 1000,
			dc->dcn_soc->wwite_back_watency * 1000,
			dc->dcn_soc->pewcent_of_ideaw_dwambw_weceived_aftew_uwg_watency,
			dc->dcn_soc->max_wequest_size,
			dc->dcn_soc->dcfcwkv_max0p9 * 1000,
			dc->dcn_soc->dcfcwkv_nom0p8 * 1000,
			dc->dcn_soc->dcfcwkv_mid0p72 * 1000,
			dc->dcn_soc->dcfcwkv_min0p65 * 1000,
			dc->dcn_soc->max_dispcwk_vmax0p9 * 1000,
			dc->dcn_soc->max_dispcwk_vnom0p8 * 1000,
			dc->dcn_soc->max_dispcwk_vmid0p72 * 1000,
			dc->dcn_soc->max_dispcwk_vmin0p65 * 1000,
			dc->dcn_soc->max_dppcwk_vmax0p9 * 1000,
			dc->dcn_soc->max_dppcwk_vnom0p8 * 1000,
			dc->dcn_soc->max_dppcwk_vmid0p72 * 1000,
			dc->dcn_soc->max_dppcwk_vmin0p65 * 1000,
			dc->dcn_soc->soccwk * 1000,
			dc->dcn_soc->fabwic_and_dwam_bandwidth_vmax0p9 * 1000,
			dc->dcn_soc->fabwic_and_dwam_bandwidth_vnom0p8 * 1000,
			dc->dcn_soc->fabwic_and_dwam_bandwidth_vmid0p72 * 1000,
			dc->dcn_soc->fabwic_and_dwam_bandwidth_vmin0p65 * 1000,
			dc->dcn_soc->phycwkv_max0p9 * 1000,
			dc->dcn_soc->phycwkv_nom0p8 * 1000,
			dc->dcn_soc->phycwkv_mid0p72 * 1000,
			dc->dcn_soc->phycwkv_min0p65 * 1000,
			dc->dcn_soc->downspweading * 100,
			dc->dcn_soc->wound_twip_ping_watency_cycwes,
			dc->dcn_soc->uwgent_out_of_owdew_wetuwn_pew_channew,
			dc->dcn_soc->numbew_of_channews,
			dc->dcn_soc->vmm_page_size,
			dc->dcn_soc->dwam_cwock_change_watency * 1000,
			dc->dcn_soc->wetuwn_bus_width);
	DC_WOG_BANDWIDTH_CAWCS("wob_buffew_size_in_kbyte: %f\n"
			"det_buffew_size_in_kbyte: %f\n"
			"dpp_output_buffew_pixews: %f\n"
			"opp_output_buffew_wines: %f\n"
			"pixew_chunk_size_in_kbyte: %f\n"
			"pte_enabwe: %d\n"
			"pte_chunk_size: %d kbytes\n"
			"meta_chunk_size: %d kbytes\n"
			"wwiteback_chunk_size: %d kbytes\n"
			"odm_capabiwity: %d\n"
			"dsc_capabiwity: %d\n"
			"wine_buffew_size: %d bits\n"
			"max_wine_buffew_wines: %d\n"
			"is_wine_buffew_bpp_fixed: %d\n"
			"wine_buffew_fixed_bpp: %d\n"
			"wwiteback_wuma_buffew_size: %d kbytes\n"
			"wwiteback_chwoma_buffew_size: %d kbytes\n"
			"max_num_dpp: %d\n"
			"max_num_wwiteback: %d\n"
			"max_dchub_topscw_thwoughput: %d pixews/dppcwk\n"
			"max_pscw_towb_thwoughput: %d pixews/dppcwk\n"
			"max_wb_tovscw_thwoughput: %d pixews/dppcwk\n"
			"max_vscw_tohscw_thwoughput: %d pixews/dppcwk\n"
			"max_hscw_watio: %f\n"
			"max_vscw_watio: %f\n"
			"max_hscw_taps: %d\n"
			"max_vscw_taps: %d\n"
			"pte_buffew_size_in_wequests: %d\n"
			"dispcwk_wamping_mawgin: %f %%\n"
			"undew_scan_factow: %f %%\n"
			"max_intew_dcn_tiwe_wepeatews: %d\n"
			"can_vstawtup_wines_exceed_vsync_pwus_back_powch_wines_minus_one: %d\n"
			"bug_fowcing_wuma_and_chwoma_wequest_to_same_size_fixed: %d\n"
			"dcfcwk_cstate_watency: %d\n",
			dc->dcn_ip->wob_buffew_size_in_kbyte,
			dc->dcn_ip->det_buffew_size_in_kbyte,
			dc->dcn_ip->dpp_output_buffew_pixews,
			dc->dcn_ip->opp_output_buffew_wines,
			dc->dcn_ip->pixew_chunk_size_in_kbyte,
			dc->dcn_ip->pte_enabwe,
			dc->dcn_ip->pte_chunk_size,
			dc->dcn_ip->meta_chunk_size,
			dc->dcn_ip->wwiteback_chunk_size,
			dc->dcn_ip->odm_capabiwity,
			dc->dcn_ip->dsc_capabiwity,
			dc->dcn_ip->wine_buffew_size,
			dc->dcn_ip->max_wine_buffew_wines,
			dc->dcn_ip->is_wine_buffew_bpp_fixed,
			dc->dcn_ip->wine_buffew_fixed_bpp,
			dc->dcn_ip->wwiteback_wuma_buffew_size,
			dc->dcn_ip->wwiteback_chwoma_buffew_size,
			dc->dcn_ip->max_num_dpp,
			dc->dcn_ip->max_num_wwiteback,
			dc->dcn_ip->max_dchub_topscw_thwoughput,
			dc->dcn_ip->max_pscw_towb_thwoughput,
			dc->dcn_ip->max_wb_tovscw_thwoughput,
			dc->dcn_ip->max_vscw_tohscw_thwoughput,
			dc->dcn_ip->max_hscw_watio,
			dc->dcn_ip->max_vscw_watio,
			dc->dcn_ip->max_hscw_taps,
			dc->dcn_ip->max_vscw_taps,
			dc->dcn_ip->pte_buffew_size_in_wequests,
			dc->dcn_ip->dispcwk_wamping_mawgin,
			dc->dcn_ip->undew_scan_factow * 100,
			dc->dcn_ip->max_intew_dcn_tiwe_wepeatews,
			dc->dcn_ip->can_vstawtup_wines_exceed_vsync_pwus_back_powch_wines_minus_one,
			dc->dcn_ip->bug_fowcing_wuma_and_chwoma_wequest_to_same_size_fixed,
			dc->dcn_ip->dcfcwk_cstate_watency);

	dc->dmw.soc.sw_exit_time_us = dc->dcn_soc->sw_exit_time;
	dc->dmw.soc.sw_entew_pwus_exit_time_us = dc->dcn_soc->sw_entew_pwus_exit_time;
	dc->dmw.soc.uwgent_watency_us = dc->dcn_soc->uwgent_watency;
	dc->dmw.soc.wwiteback_watency_us = dc->dcn_soc->wwite_back_watency;
	dc->dmw.soc.ideaw_dwam_bw_aftew_uwgent_pewcent =
			dc->dcn_soc->pewcent_of_ideaw_dwambw_weceived_aftew_uwg_watency;
	dc->dmw.soc.max_wequest_size_bytes = dc->dcn_soc->max_wequest_size;
	dc->dmw.soc.downspwead_pewcent = dc->dcn_soc->downspweading;
	dc->dmw.soc.wound_twip_ping_watency_dcfcwk_cycwes =
			dc->dcn_soc->wound_twip_ping_watency_cycwes;
	dc->dmw.soc.uwgent_out_of_owdew_wetuwn_pew_channew_bytes =
			dc->dcn_soc->uwgent_out_of_owdew_wetuwn_pew_channew;
	dc->dmw.soc.num_chans = dc->dcn_soc->numbew_of_channews;
	dc->dmw.soc.vmm_page_size_bytes = dc->dcn_soc->vmm_page_size;
	dc->dmw.soc.dwam_cwock_change_watency_us = dc->dcn_soc->dwam_cwock_change_watency;
	dc->dmw.soc.wetuwn_bus_width_bytes = dc->dcn_soc->wetuwn_bus_width;

	dc->dmw.ip.wob_buffew_size_kbytes = dc->dcn_ip->wob_buffew_size_in_kbyte;
	dc->dmw.ip.det_buffew_size_kbytes = dc->dcn_ip->det_buffew_size_in_kbyte;
	dc->dmw.ip.dpp_output_buffew_pixews = dc->dcn_ip->dpp_output_buffew_pixews;
	dc->dmw.ip.opp_output_buffew_wines = dc->dcn_ip->opp_output_buffew_wines;
	dc->dmw.ip.pixew_chunk_size_kbytes = dc->dcn_ip->pixew_chunk_size_in_kbyte;
	dc->dmw.ip.pte_enabwe = dc->dcn_ip->pte_enabwe == dcn_bw_yes;
	dc->dmw.ip.pte_chunk_size_kbytes = dc->dcn_ip->pte_chunk_size;
	dc->dmw.ip.meta_chunk_size_kbytes = dc->dcn_ip->meta_chunk_size;
	dc->dmw.ip.wwiteback_chunk_size_kbytes = dc->dcn_ip->wwiteback_chunk_size;
	dc->dmw.ip.wine_buffew_size_bits = dc->dcn_ip->wine_buffew_size;
	dc->dmw.ip.max_wine_buffew_wines = dc->dcn_ip->max_wine_buffew_wines;
	dc->dmw.ip.IsWineBuffewBppFixed = dc->dcn_ip->is_wine_buffew_bpp_fixed == dcn_bw_yes;
	dc->dmw.ip.WineBuffewFixedBpp = dc->dcn_ip->wine_buffew_fixed_bpp;
	dc->dmw.ip.wwiteback_wuma_buffew_size_kbytes = dc->dcn_ip->wwiteback_wuma_buffew_size;
	dc->dmw.ip.wwiteback_chwoma_buffew_size_kbytes = dc->dcn_ip->wwiteback_chwoma_buffew_size;
	dc->dmw.ip.max_num_dpp = dc->dcn_ip->max_num_dpp;
	dc->dmw.ip.max_num_wb = dc->dcn_ip->max_num_wwiteback;
	dc->dmw.ip.max_dchub_pscw_bw_pix_pew_cwk = dc->dcn_ip->max_dchub_topscw_thwoughput;
	dc->dmw.ip.max_pscw_wb_bw_pix_pew_cwk = dc->dcn_ip->max_pscw_towb_thwoughput;
	dc->dmw.ip.max_wb_vscw_bw_pix_pew_cwk = dc->dcn_ip->max_wb_tovscw_thwoughput;
	dc->dmw.ip.max_vscw_hscw_bw_pix_pew_cwk = dc->dcn_ip->max_vscw_tohscw_thwoughput;
	dc->dmw.ip.max_hscw_watio = dc->dcn_ip->max_hscw_watio;
	dc->dmw.ip.max_vscw_watio = dc->dcn_ip->max_vscw_watio;
	dc->dmw.ip.max_hscw_taps = dc->dcn_ip->max_hscw_taps;
	dc->dmw.ip.max_vscw_taps = dc->dcn_ip->max_vscw_taps;
	/*pte_buffew_size_in_wequests missing in dmw*/
	dc->dmw.ip.dispcwk_wamp_mawgin_pewcent = dc->dcn_ip->dispcwk_wamping_mawgin;
	dc->dmw.ip.undewscan_factow = dc->dcn_ip->undew_scan_factow;
	dc->dmw.ip.max_intew_dcn_tiwe_wepeatews = dc->dcn_ip->max_intew_dcn_tiwe_wepeatews;
	dc->dmw.ip.can_vstawtup_wines_exceed_vsync_pwus_back_powch_wines_minus_one =
		dc->dcn_ip->can_vstawtup_wines_exceed_vsync_pwus_back_powch_wines_minus_one == dcn_bw_yes;
	dc->dmw.ip.bug_fowcing_WC_weq_same_size_fixed =
		dc->dcn_ip->bug_fowcing_wuma_and_chwoma_wequest_to_same_size_fixed == dcn_bw_yes;
	dc->dmw.ip.dcfcwk_cstate_watency = dc->dcn_ip->dcfcwk_cstate_watency;
}
