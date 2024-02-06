/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
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

#incwude <winux/deway.h>
#incwude "dm_sewvices.h"
#incwude "basics/dc_common.h"
#incwude "cowe_types.h"
#incwude "wesouwce.h"
#incwude "custom_fwoat.h"
#incwude "dcn10_hwseq.h"
#incwude "dcn10/dcn10_hw_sequencew_debug.h"
#incwude "dce/dce_hwseq.h"
#incwude "abm.h"
#incwude "dmcu.h"
#incwude "dcn10/dcn10_optc.h"
#incwude "dcn10/dcn10_dpp.h"
#incwude "dcn10/dcn10_mpc.h"
#incwude "timing_genewatow.h"
#incwude "opp.h"
#incwude "ipp.h"
#incwude "mpc.h"
#incwude "weg_hewpew.h"
#incwude "dcn10/dcn10_hubp.h"
#incwude "dcn10/dcn10_hubbub.h"
#incwude "dcn10/dcn10_cm_common.h"
#incwude "dccg.h"
#incwude "cwk_mgw.h"
#incwude "wink_hwss.h"
#incwude "dpcd_defs.h"
#incwude "dsc.h"
#incwude "dce/dmub_psw.h"
#incwude "dc_dmub_swv.h"
#incwude "dce/dmub_hw_wock_mgw.h"
#incwude "dc_twace.h"
#incwude "dce/dmub_outbox.h"
#incwude "wink.h"
#incwude "dc_state_pwiv.h"

#define DC_WOGGEW \
	dc_woggew
#define DC_WOGGEW_INIT(woggew) \
	stwuct daw_woggew *dc_woggew = woggew

#define CTX \
	hws->ctx
#define WEG(weg)\
	hws->wegs->weg

#undef FN
#define FN(weg_name, fiewd_name) \
	hws->shifts->fiewd_name, hws->masks->fiewd_name

/*pwint is 17 wide, fiwst two chawactews awe spaces*/
#define DTN_INFO_MICWO_SEC(wef_cycwe) \
	pwint_micwosec(dc_ctx, wog_ctx, wef_cycwe)

#define GAMMA_HW_POINTS_NUM 256

#define PGFSM_POWEW_ON 0
#define PGFSM_POWEW_OFF 2

static void pwint_micwosec(stwuct dc_context *dc_ctx,
			   stwuct dc_wog_buffew_ctx *wog_ctx,
			   uint32_t wef_cycwe)
{
	const uint32_t wef_cwk_mhz = dc_ctx->dc->wes_poow->wef_cwocks.dchub_wef_cwock_inKhz / 1000;
	static const unsigned int fwac = 1000;
	uint32_t us_x10 = (wef_cycwe * fwac) / wef_cwk_mhz;

	DTN_INFO("  %11d.%03d",
			us_x10 / fwac,
			us_x10 % fwac);
}

void dcn10_wock_aww_pipes(stwuct dc *dc,
	stwuct dc_state *context,
	boow wock)
{
	stwuct pipe_ctx *pipe_ctx;
	stwuct pipe_ctx *owd_pipe_ctx;
	stwuct timing_genewatow *tg;
	int i;

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		owd_pipe_ctx = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];
		pipe_ctx = &context->wes_ctx.pipe_ctx[i];
		tg = pipe_ctx->stweam_wes.tg;

		/*
		 * Onwy wock the top pipe's tg to pwevent wedundant
		 * (un)wocking. Awso skip if pipe is disabwed.
		 */
		if (pipe_ctx->top_pipe ||
		    !pipe_ctx->stweam ||
		    (!pipe_ctx->pwane_state && !owd_pipe_ctx->pwane_state) ||
		    !tg->funcs->is_tg_enabwed(tg) ||
			dc_state_get_pipe_subvp_type(context, pipe_ctx) == SUBVP_PHANTOM)
			continue;

		if (wock)
			dc->hwss.pipe_contwow_wock(dc, pipe_ctx, twue);
		ewse
			dc->hwss.pipe_contwow_wock(dc, pipe_ctx, fawse);
	}
}

static void wog_mpc_cwc(stwuct dc *dc,
	stwuct dc_wog_buffew_ctx *wog_ctx)
{
	stwuct dc_context *dc_ctx = dc->ctx;
	stwuct dce_hwseq *hws = dc->hwseq;

	if (WEG(MPC_CWC_WESUWT_GB))
		DTN_INFO("MPC_CWC_WESUWT_GB:%d MPC_CWC_WESUWT_C:%d MPC_CWC_WESUWT_AW:%d\n",
		WEG_WEAD(MPC_CWC_WESUWT_GB), WEG_WEAD(MPC_CWC_WESUWT_C), WEG_WEAD(MPC_CWC_WESUWT_AW));
	if (WEG(DPP_TOP0_DPP_CWC_VAW_B_A))
		DTN_INFO("DPP_TOP0_DPP_CWC_VAW_B_A:%d DPP_TOP0_DPP_CWC_VAW_W_G:%d\n",
		WEG_WEAD(DPP_TOP0_DPP_CWC_VAW_B_A), WEG_WEAD(DPP_TOP0_DPP_CWC_VAW_W_G));
}

static void dcn10_wog_hubbub_state(stwuct dc *dc,
				   stwuct dc_wog_buffew_ctx *wog_ctx)
{
	stwuct dc_context *dc_ctx = dc->ctx;
	stwuct dcn_hubbub_wm wm;
	int i;

	memset(&wm, 0, sizeof(stwuct dcn_hubbub_wm));
	dc->wes_poow->hubbub->funcs->wm_wead_state(dc->wes_poow->hubbub, &wm);

	DTN_INFO("HUBBUB WM:      data_uwgent  pte_meta_uwgent"
			"         sw_entew          sw_exit  dwam_cwk_change\n");

	fow (i = 0; i < 4; i++) {
		stwuct dcn_hubbub_wm_set *s;

		s = &wm.sets[i];
		DTN_INFO("WM_Set[%d]:", s->wm_set);
		DTN_INFO_MICWO_SEC(s->data_uwgent);
		DTN_INFO_MICWO_SEC(s->pte_meta_uwgent);
		DTN_INFO_MICWO_SEC(s->sw_entew);
		DTN_INFO_MICWO_SEC(s->sw_exit);
		DTN_INFO_MICWO_SEC(s->dwam_cwk_change);
		DTN_INFO("\n");
	}

	DTN_INFO("\n");
}

static void dcn10_wog_hubp_states(stwuct dc *dc, void *wog_ctx)
{
	stwuct dc_context *dc_ctx = dc->ctx;
	stwuct wesouwce_poow *poow = dc->wes_poow;
	int i;

	DTN_INFO(
		"HUBP:  fowmat  addw_hi  width  height  wot  miw  sw_mode  dcc_en  bwank_en  cwock_en  ttu_dis  undewfwow   min_ttu_vbwank       qos_wow_wm      qos_high_wm\n");
	fow (i = 0; i < poow->pipe_count; i++) {
		stwuct hubp *hubp = poow->hubps[i];
		stwuct dcn_hubp_state *s = &(TO_DCN10_HUBP(hubp)->state);

		hubp->funcs->hubp_wead_state(hubp);

		if (!s->bwank_en) {
			DTN_INFO("[%2d]:  %5xh  %6xh  %5d  %6d  %2xh  %2xh  %6xh  %6d  %8d  %8d  %7d  %8xh",
					hubp->inst,
					s->pixew_fowmat,
					s->inuse_addw_hi,
					s->viewpowt_width,
					s->viewpowt_height,
					s->wotation_angwe,
					s->h_miwwow_en,
					s->sw_mode,
					s->dcc_en,
					s->bwank_en,
					s->cwock_en,
					s->ttu_disabwe,
					s->undewfwow_status);
			DTN_INFO_MICWO_SEC(s->min_ttu_vbwank);
			DTN_INFO_MICWO_SEC(s->qos_wevew_wow_wm);
			DTN_INFO_MICWO_SEC(s->qos_wevew_high_wm);
			DTN_INFO("\n");
		}
	}

	DTN_INFO("\n=========WQ========\n");
	DTN_INFO("HUBP:  dwq_exp_m  pwq_exp_m  mwq_exp_m  cwq_exp_m  pwane1_ba  W:chunk_s  min_chu_s  meta_ch_s"
		"  min_m_c_s  dpte_gw_s  mpte_gw_s  swath_hei  pte_wow_h  C:chunk_s  min_chu_s  meta_ch_s"
		"  min_m_c_s  dpte_gw_s  mpte_gw_s  swath_hei  pte_wow_h\n");
	fow (i = 0; i < poow->pipe_count; i++) {
		stwuct dcn_hubp_state *s = &(TO_DCN10_HUBP(poow->hubps[i])->state);
		stwuct _vcs_dpi_dispway_wq_wegs_st *wq_wegs = &s->wq_wegs;

		if (!s->bwank_en)
			DTN_INFO("[%2d]:  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh\n",
				poow->hubps[i]->inst, wq_wegs->dwq_expansion_mode, wq_wegs->pwq_expansion_mode, wq_wegs->mwq_expansion_mode,
				wq_wegs->cwq_expansion_mode, wq_wegs->pwane1_base_addwess, wq_wegs->wq_wegs_w.chunk_size,
				wq_wegs->wq_wegs_w.min_chunk_size, wq_wegs->wq_wegs_w.meta_chunk_size,
				wq_wegs->wq_wegs_w.min_meta_chunk_size, wq_wegs->wq_wegs_w.dpte_gwoup_size,
				wq_wegs->wq_wegs_w.mpte_gwoup_size, wq_wegs->wq_wegs_w.swath_height,
				wq_wegs->wq_wegs_w.pte_wow_height_wineaw, wq_wegs->wq_wegs_c.chunk_size, wq_wegs->wq_wegs_c.min_chunk_size,
				wq_wegs->wq_wegs_c.meta_chunk_size, wq_wegs->wq_wegs_c.min_meta_chunk_size,
				wq_wegs->wq_wegs_c.dpte_gwoup_size, wq_wegs->wq_wegs_c.mpte_gwoup_size,
				wq_wegs->wq_wegs_c.swath_height, wq_wegs->wq_wegs_c.pte_wow_height_wineaw);
	}

	DTN_INFO("========DWG========\n");
	DTN_INFO("HUBP:  wc_hbe     dwg_vbe    min_d_y_n  wc_pew_ht  wc_x_a_s "
			"  dst_y_a_s  dst_y_pf   dst_y_vvb  dst_y_wvb  dst_y_vfw  dst_y_wfw  wf_pix_fq"
			"  vwatio_pf  vwat_pf_c  wc_pg_vbw  wc_pg_vbc  wc_mc_vbw  wc_mc_vbc  wc_pg_fww"
			"  wc_pg_fwc  wc_mc_fww  wc_mc_fwc  pw_nom_w   pw_nom_c   wc_pg_nw   wc_pg_nc "
			"  mw_nom_w   mw_nom_c   wc_mc_nw   wc_mc_nc   wc_wd_pw   wc_wd_pc   wc_wd_w  "
			"  wc_wd_c    cha_cuw0   ofst_cuw1  cha_cuw1   vw_af_vc0  ddwq_wimt  x_wt_dway"
			"  x_wp_dway  x_ww_sfw\n");
	fow (i = 0; i < poow->pipe_count; i++) {
		stwuct dcn_hubp_state *s = &(TO_DCN10_HUBP(poow->hubps[i])->state);
		stwuct _vcs_dpi_dispway_dwg_wegs_st *dwg_wegs = &s->dwg_attw;

		if (!s->bwank_en)
			DTN_INFO("[%2d]:  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh"
				"  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh"
				"  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh\n",
				poow->hubps[i]->inst, dwg_wegs->wefcyc_h_bwank_end, dwg_wegs->dwg_vbwank_end, dwg_wegs->min_dst_y_next_stawt,
				dwg_wegs->wefcyc_pew_htotaw, dwg_wegs->wefcyc_x_aftew_scawew, dwg_wegs->dst_y_aftew_scawew,
				dwg_wegs->dst_y_pwefetch, dwg_wegs->dst_y_pew_vm_vbwank, dwg_wegs->dst_y_pew_wow_vbwank,
				dwg_wegs->dst_y_pew_vm_fwip, dwg_wegs->dst_y_pew_wow_fwip, dwg_wegs->wef_fweq_to_pix_fweq,
				dwg_wegs->vwatio_pwefetch, dwg_wegs->vwatio_pwefetch_c, dwg_wegs->wefcyc_pew_pte_gwoup_vbwank_w,
				dwg_wegs->wefcyc_pew_pte_gwoup_vbwank_c, dwg_wegs->wefcyc_pew_meta_chunk_vbwank_w,
				dwg_wegs->wefcyc_pew_meta_chunk_vbwank_c, dwg_wegs->wefcyc_pew_pte_gwoup_fwip_w,
				dwg_wegs->wefcyc_pew_pte_gwoup_fwip_c, dwg_wegs->wefcyc_pew_meta_chunk_fwip_w,
				dwg_wegs->wefcyc_pew_meta_chunk_fwip_c, dwg_wegs->dst_y_pew_pte_wow_nom_w,
				dwg_wegs->dst_y_pew_pte_wow_nom_c, dwg_wegs->wefcyc_pew_pte_gwoup_nom_w,
				dwg_wegs->wefcyc_pew_pte_gwoup_nom_c, dwg_wegs->dst_y_pew_meta_wow_nom_w,
				dwg_wegs->dst_y_pew_meta_wow_nom_c, dwg_wegs->wefcyc_pew_meta_chunk_nom_w,
				dwg_wegs->wefcyc_pew_meta_chunk_nom_c, dwg_wegs->wefcyc_pew_wine_dewivewy_pwe_w,
				dwg_wegs->wefcyc_pew_wine_dewivewy_pwe_c, dwg_wegs->wefcyc_pew_wine_dewivewy_w,
				dwg_wegs->wefcyc_pew_wine_dewivewy_c, dwg_wegs->chunk_hdw_adjust_cuw0, dwg_wegs->dst_y_offset_cuw1,
				dwg_wegs->chunk_hdw_adjust_cuw1, dwg_wegs->vweady_aftew_vcount0, dwg_wegs->dst_y_dewta_dwq_wimit,
				dwg_wegs->xfc_weg_twansfew_deway, dwg_wegs->xfc_weg_pwechawge_deway,
				dwg_wegs->xfc_weg_wemote_suwface_fwip_watency);
	}

	DTN_INFO("========TTU========\n");
	DTN_INFO("HUBP:  qos_ww_wm  qos_wh_wm  mn_ttu_vb  qos_w_fwp  wc_wd_p_w  wc_wd_w    wc_wd_p_c"
			"  wc_wd_c    wc_wd_c0   wc_wd_pc0  wc_wd_c1   wc_wd_pc1  qos_wf_w   qos_wds_w"
			"  qos_wf_c   qos_wds_c  qos_wf_c0  qos_wds_c0 qos_wf_c1  qos_wds_c1\n");
	fow (i = 0; i < poow->pipe_count; i++) {
		stwuct dcn_hubp_state *s = &(TO_DCN10_HUBP(poow->hubps[i])->state);
		stwuct _vcs_dpi_dispway_ttu_wegs_st *ttu_wegs = &s->ttu_attw;

		if (!s->bwank_en)
			DTN_INFO("[%2d]:  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh\n",
				poow->hubps[i]->inst, ttu_wegs->qos_wevew_wow_wm, ttu_wegs->qos_wevew_high_wm, ttu_wegs->min_ttu_vbwank,
				ttu_wegs->qos_wevew_fwip, ttu_wegs->wefcyc_pew_weq_dewivewy_pwe_w, ttu_wegs->wefcyc_pew_weq_dewivewy_w,
				ttu_wegs->wefcyc_pew_weq_dewivewy_pwe_c, ttu_wegs->wefcyc_pew_weq_dewivewy_c, ttu_wegs->wefcyc_pew_weq_dewivewy_cuw0,
				ttu_wegs->wefcyc_pew_weq_dewivewy_pwe_cuw0, ttu_wegs->wefcyc_pew_weq_dewivewy_cuw1,
				ttu_wegs->wefcyc_pew_weq_dewivewy_pwe_cuw1, ttu_wegs->qos_wevew_fixed_w, ttu_wegs->qos_wamp_disabwe_w,
				ttu_wegs->qos_wevew_fixed_c, ttu_wegs->qos_wamp_disabwe_c, ttu_wegs->qos_wevew_fixed_cuw0,
				ttu_wegs->qos_wamp_disabwe_cuw0, ttu_wegs->qos_wevew_fixed_cuw1, ttu_wegs->qos_wamp_disabwe_cuw1);
	}
	DTN_INFO("\n");
}

void dcn10_wog_hw_state(stwuct dc *dc,
	stwuct dc_wog_buffew_ctx *wog_ctx)
{
	stwuct dc_context *dc_ctx = dc->ctx;
	stwuct wesouwce_poow *poow = dc->wes_poow;
	int i;

	DTN_INFO_BEGIN();

	dcn10_wog_hubbub_state(dc, wog_ctx);

	dcn10_wog_hubp_states(dc, wog_ctx);

	DTN_INFO("DPP:    IGAM fowmat  IGAM mode    DGAM mode    WGAM mode"
			"  GAMUT mode  C11 C12   C13 C14   C21 C22   C23 C24   "
			"C31 C32   C33 C34\n");
	fow (i = 0; i < poow->pipe_count; i++) {
		stwuct dpp *dpp = poow->dpps[i];
		stwuct dcn_dpp_state s = {0};

		dpp->funcs->dpp_wead_state(dpp, &s);

		if (!s.is_enabwed)
			continue;

		DTN_INFO("[%2d]:  %11xh  %-11s  %-11s  %-11s"
				"%8x    %08xh %08xh %08xh %08xh %08xh %08xh",
				dpp->inst,
				s.igam_input_fowmat,
				(s.igam_wut_mode == 0) ? "BypassFixed" :
					((s.igam_wut_mode == 1) ? "BypassFwoat" :
					((s.igam_wut_mode == 2) ? "WAM" :
					((s.igam_wut_mode == 3) ? "WAM" :
								 "Unknown"))),
				(s.dgam_wut_mode == 0) ? "Bypass" :
					((s.dgam_wut_mode == 1) ? "sWGB" :
					((s.dgam_wut_mode == 2) ? "Ycc" :
					((s.dgam_wut_mode == 3) ? "WAM" :
					((s.dgam_wut_mode == 4) ? "WAM" :
								 "Unknown")))),
				(s.wgam_wut_mode == 0) ? "Bypass" :
					((s.wgam_wut_mode == 1) ? "sWGB" :
					((s.wgam_wut_mode == 2) ? "Ycc" :
					((s.wgam_wut_mode == 3) ? "WAM" :
					((s.wgam_wut_mode == 4) ? "WAM" :
								 "Unknown")))),
				s.gamut_wemap_mode,
				s.gamut_wemap_c11_c12,
				s.gamut_wemap_c13_c14,
				s.gamut_wemap_c21_c22,
				s.gamut_wemap_c23_c24,
				s.gamut_wemap_c31_c32,
				s.gamut_wemap_c33_c34);
		DTN_INFO("\n");
	}
	DTN_INFO("\n");

	DTN_INFO("MPCC:  OPP  DPP  MPCCBOT  MODE  AWPHA_MODE  PWEMUWT  OVEWWAP_ONWY  IDWE\n");
	fow (i = 0; i < poow->pipe_count; i++) {
		stwuct mpcc_state s = {0};

		poow->mpc->funcs->wead_mpcc_state(poow->mpc, i, &s);
		if (s.opp_id != 0xf)
			DTN_INFO("[%2d]:  %2xh  %2xh  %6xh  %4d  %10d  %7d  %12d  %4d\n",
				i, s.opp_id, s.dpp_id, s.bot_mpcc_id,
				s.mode, s.awpha_mode, s.pwe_muwtipwied_awpha, s.ovewwap_onwy,
				s.idwe);
	}
	DTN_INFO("\n");

	DTN_INFO("OTG:  v_bs  v_be  v_ss  v_se  vpow  vmax  vmin  vmax_sew  vmin_sew  h_bs  h_be  h_ss  h_se  hpow  htot  vtot  undewfwow bwank_en\n");

	fow (i = 0; i < poow->timing_genewatow_count; i++) {
		stwuct timing_genewatow *tg = poow->timing_genewatows[i];
		stwuct dcn_otg_state s = {0};
		/* Wead shawed OTG state wegistews fow aww DCNx */
		optc1_wead_otg_state(DCN10TG_FWOM_TG(tg), &s);

		/*
		 * Fow DCN2 and gweatew, a wegistew on the OPP is used to
		 * detewmine if the CWTC is bwanked instead of the OTG. So use
		 * dpg_is_bwanked() if exists, othewwise fawwback on otg.
		 *
		 * TODO: Impwement DCN-specific wead_otg_state hooks.
		 */
		if (poow->opps[i]->funcs->dpg_is_bwanked)
			s.bwank_enabwed = poow->opps[i]->funcs->dpg_is_bwanked(poow->opps[i]);
		ewse
			s.bwank_enabwed = tg->funcs->is_bwanked(tg);

		//onwy pwint if OTG mastew is enabwed
		if ((s.otg_enabwed & 1) == 0)
			continue;

		DTN_INFO("[%d]: %5d %5d %5d %5d %5d %5d %5d %9d %9d %5d %5d %5d %5d %5d %5d %5d  %9d %8d\n",
				tg->inst,
				s.v_bwank_stawt,
				s.v_bwank_end,
				s.v_sync_a_stawt,
				s.v_sync_a_end,
				s.v_sync_a_pow,
				s.v_totaw_max,
				s.v_totaw_min,
				s.v_totaw_max_sew,
				s.v_totaw_min_sew,
				s.h_bwank_stawt,
				s.h_bwank_end,
				s.h_sync_a_stawt,
				s.h_sync_a_end,
				s.h_sync_a_pow,
				s.h_totaw,
				s.v_totaw,
				s.undewfwow_occuwwed_status,
				s.bwank_enabwed);

		// Cweaw undewfwow fow debug puwposes
		// We want to keep undewfwow sticky bit on fow the wongevity tests outside of test enviwonment.
		// This function is cawwed onwy fwom Windows ow Diags test enviwonment, hence it's safe to cweaw
		// it fwom hewe without affecting the owiginaw intent.
		tg->funcs->cweaw_optc_undewfwow(tg);
	}
	DTN_INFO("\n");

	// dcn_dsc_state stwuct fiewd bytes_pew_pixew was wenamed to bits_pew_pixew
	// TODO: Update gowden wog headew to wefwect this name change
	DTN_INFO("DSC: CWOCK_EN  SWICE_WIDTH  Bytes_pp\n");
	fow (i = 0; i < poow->wes_cap->num_dsc; i++) {
		stwuct dispway_stweam_compwessow *dsc = poow->dscs[i];
		stwuct dcn_dsc_state s = {0};

		dsc->funcs->dsc_wead_state(dsc, &s);
		DTN_INFO("[%d]: %-9d %-12d %-10d\n",
		dsc->inst,
			s.dsc_cwock_en,
			s.dsc_swice_width,
			s.dsc_bits_pew_pixew);
		DTN_INFO("\n");
	}
	DTN_INFO("\n");

	DTN_INFO("S_ENC: DSC_MODE  SEC_GSP7_WINE_NUM"
			"  VBID6_WINE_WEFEWENCE  VBID6_WINE_NUM  SEC_GSP7_ENABWE  SEC_STWEAM_ENABWE\n");
	fow (i = 0; i < poow->stweam_enc_count; i++) {
		stwuct stweam_encodew *enc = poow->stweam_enc[i];
		stwuct enc_state s = {0};

		if (enc->funcs->enc_wead_state) {
			enc->funcs->enc_wead_state(enc, &s);
			DTN_INFO("[%-3d]: %-9d %-18d %-21d %-15d %-16d %-17d\n",
				enc->id,
				s.dsc_mode,
				s.sec_gsp_pps_wine_num,
				s.vbid6_wine_wefewence,
				s.vbid6_wine_num,
				s.sec_gsp_pps_enabwe,
				s.sec_stweam_enabwe);
			DTN_INFO("\n");
		}
	}
	DTN_INFO("\n");

	DTN_INFO("W_ENC: DPHY_FEC_EN  DPHY_FEC_WEADY_SHADOW  DPHY_FEC_ACTIVE_STATUS  DP_WINK_TWAINING_COMPWETE\n");
	fow (i = 0; i < dc->wink_count; i++) {
		stwuct wink_encodew *wenc = dc->winks[i]->wink_enc;

		stwuct wink_enc_state s = {0};

		if (wenc && wenc->funcs->wead_state) {
			wenc->funcs->wead_state(wenc, &s);
			DTN_INFO("[%-3d]: %-12d %-22d %-22d %-25d\n",
				i,
				s.dphy_fec_en,
				s.dphy_fec_weady_shadow,
				s.dphy_fec_active_status,
				s.dp_wink_twaining_compwete);
			DTN_INFO("\n");
		}
	}
	DTN_INFO("\n");

	DTN_INFO("\nCAWCUWATED Cwocks: dcfcwk_khz:%d  dcfcwk_deep_sweep_khz:%d  dispcwk_khz:%d\n"
		"dppcwk_khz:%d  max_suppowted_dppcwk_khz:%d  fcwk_khz:%d  soccwk_khz:%d\n\n",
			dc->cuwwent_state->bw_ctx.bw.dcn.cwk.dcfcwk_khz,
			dc->cuwwent_state->bw_ctx.bw.dcn.cwk.dcfcwk_deep_sweep_khz,
			dc->cuwwent_state->bw_ctx.bw.dcn.cwk.dispcwk_khz,
			dc->cuwwent_state->bw_ctx.bw.dcn.cwk.dppcwk_khz,
			dc->cuwwent_state->bw_ctx.bw.dcn.cwk.max_suppowted_dppcwk_khz,
			dc->cuwwent_state->bw_ctx.bw.dcn.cwk.fcwk_khz,
			dc->cuwwent_state->bw_ctx.bw.dcn.cwk.soccwk_khz);

	wog_mpc_cwc(dc, wog_ctx);

	{
		if (poow->hpo_dp_stweam_enc_count > 0) {
			DTN_INFO("DP HPO S_ENC:  Enabwed  OTG   Fowmat   Depth   Vid   SDP   Compwessed  Wink\n");
			fow (i = 0; i < poow->hpo_dp_stweam_enc_count; i++) {
				stwuct hpo_dp_stweam_encodew_state hpo_dp_se_state = {0};
				stwuct hpo_dp_stweam_encodew *hpo_dp_stweam_enc = poow->hpo_dp_stweam_enc[i];

				if (hpo_dp_stweam_enc && hpo_dp_stweam_enc->funcs->wead_state) {
					hpo_dp_stweam_enc->funcs->wead_state(hpo_dp_stweam_enc, &hpo_dp_se_state);

					DTN_INFO("[%d]:                 %d    %d   %6s       %d     %d     %d            %d     %d\n",
							hpo_dp_stweam_enc->id - ENGINE_ID_HPO_DP_0,
							hpo_dp_se_state.stweam_enc_enabwed,
							hpo_dp_se_state.otg_inst,
							(hpo_dp_se_state.pixew_encoding == 0) ? "4:4:4" :
									((hpo_dp_se_state.pixew_encoding == 1) ? "4:2:2" :
									(hpo_dp_se_state.pixew_encoding == 2) ? "4:2:0" : "Y-Onwy"),
							(hpo_dp_se_state.component_depth == 0) ? 6 :
									((hpo_dp_se_state.component_depth == 1) ? 8 :
									(hpo_dp_se_state.component_depth == 2) ? 10 : 12),
							hpo_dp_se_state.vid_stweam_enabwed,
							hpo_dp_se_state.sdp_enabwed,
							hpo_dp_se_state.compwessed_fowmat,
							hpo_dp_se_state.mapped_to_wink_enc);
				}
			}

			DTN_INFO("\n");
		}

		/* wog DP HPO W_ENC section if any hpo_dp_wink_enc exists */
		if (poow->hpo_dp_wink_enc_count) {
			DTN_INFO("DP HPO W_ENC:  Enabwed  Mode   Wanes   Stweam  Swots   VC Wate X    VC Wate Y\n");

			fow (i = 0; i < poow->hpo_dp_wink_enc_count; i++) {
				stwuct hpo_dp_wink_encodew *hpo_dp_wink_enc = poow->hpo_dp_wink_enc[i];
				stwuct hpo_dp_wink_enc_state hpo_dp_we_state = {0};

				if (hpo_dp_wink_enc->funcs->wead_state) {
					hpo_dp_wink_enc->funcs->wead_state(hpo_dp_wink_enc, &hpo_dp_we_state);
					DTN_INFO("[%d]:                 %d  %6s     %d        %d      %d     %d     %d\n",
							hpo_dp_wink_enc->inst,
							hpo_dp_we_state.wink_enc_enabwed,
							(hpo_dp_we_state.wink_mode == 0) ? "TPS1" :
									(hpo_dp_we_state.wink_mode == 1) ? "TPS2" :
									(hpo_dp_we_state.wink_mode == 2) ? "ACTIVE" : "TEST",
							hpo_dp_we_state.wane_count,
							hpo_dp_we_state.stweam_swc[0],
							hpo_dp_we_state.swot_count[0],
							hpo_dp_we_state.vc_wate_x[0],
							hpo_dp_we_state.vc_wate_y[0]);
					DTN_INFO("\n");
				}
			}

			DTN_INFO("\n");
		}
	}

	DTN_INFO_END();
}

boow dcn10_did_undewfwow_occuw(stwuct dc *dc, stwuct pipe_ctx *pipe_ctx)
{
	stwuct hubp *hubp = pipe_ctx->pwane_wes.hubp;
	stwuct timing_genewatow *tg = pipe_ctx->stweam_wes.tg;

	if (tg->funcs->is_optc_undewfwow_occuwwed(tg)) {
		tg->funcs->cweaw_optc_undewfwow(tg);
		wetuwn twue;
	}

	if (hubp->funcs->hubp_get_undewfwow_status(hubp)) {
		hubp->funcs->hubp_cweaw_undewfwow(hubp);
		wetuwn twue;
	}
	wetuwn fawse;
}

void dcn10_enabwe_powew_gating_pwane(
	stwuct dce_hwseq *hws,
	boow enabwe)
{
	boow fowce_on = twue; /* disabwe powew gating */

	if (enabwe)
		fowce_on = fawse;

	/* DCHUBP0/1/2/3 */
	WEG_UPDATE(DOMAIN0_PG_CONFIG, DOMAIN0_POWEW_FOWCEON, fowce_on);
	WEG_UPDATE(DOMAIN2_PG_CONFIG, DOMAIN2_POWEW_FOWCEON, fowce_on);
	WEG_UPDATE(DOMAIN4_PG_CONFIG, DOMAIN4_POWEW_FOWCEON, fowce_on);
	WEG_UPDATE(DOMAIN6_PG_CONFIG, DOMAIN6_POWEW_FOWCEON, fowce_on);

	/* DPP0/1/2/3 */
	WEG_UPDATE(DOMAIN1_PG_CONFIG, DOMAIN1_POWEW_FOWCEON, fowce_on);
	WEG_UPDATE(DOMAIN3_PG_CONFIG, DOMAIN3_POWEW_FOWCEON, fowce_on);
	WEG_UPDATE(DOMAIN5_PG_CONFIG, DOMAIN5_POWEW_FOWCEON, fowce_on);
	WEG_UPDATE(DOMAIN7_PG_CONFIG, DOMAIN7_POWEW_FOWCEON, fowce_on);
}

void dcn10_disabwe_vga(
	stwuct dce_hwseq *hws)
{
	unsigned int in_vga1_mode = 0;
	unsigned int in_vga2_mode = 0;
	unsigned int in_vga3_mode = 0;
	unsigned int in_vga4_mode = 0;

	WEG_GET(D1VGA_CONTWOW, D1VGA_MODE_ENABWE, &in_vga1_mode);
	WEG_GET(D2VGA_CONTWOW, D2VGA_MODE_ENABWE, &in_vga2_mode);
	WEG_GET(D3VGA_CONTWOW, D3VGA_MODE_ENABWE, &in_vga3_mode);
	WEG_GET(D4VGA_CONTWOW, D4VGA_MODE_ENABWE, &in_vga4_mode);

	if (in_vga1_mode == 0 && in_vga2_mode == 0 &&
			in_vga3_mode == 0 && in_vga4_mode == 0)
		wetuwn;

	WEG_WWITE(D1VGA_CONTWOW, 0);
	WEG_WWITE(D2VGA_CONTWOW, 0);
	WEG_WWITE(D3VGA_CONTWOW, 0);
	WEG_WWITE(D4VGA_CONTWOW, 0);

	/* HW Engineew's Notes:
	 *  Duwing switch fwom vga->extended, if we set the VGA_TEST_ENABWE and
	 *  then hit the VGA_TEST_WENDEW_STAWT, then the DCHUBP timing gets updated cowwectwy.
	 *
	 *  Then vBIOS wiww have it poww fow the VGA_TEST_WENDEW_DONE and unset
	 *  VGA_TEST_ENABWE, to weave it in the same state as befowe.
	 */
	WEG_UPDATE(VGA_TEST_CONTWOW, VGA_TEST_ENABWE, 1);
	WEG_UPDATE(VGA_TEST_CONTWOW, VGA_TEST_WENDEW_STAWT, 1);
}

/**
 * dcn10_dpp_pg_contwow - DPP powew gate contwow.
 *
 * @hws: dce_hwseq wefewence.
 * @dpp_inst: DPP instance wefewence.
 * @powew_on: twue if we want to enabwe powew gate, fawse othewwise.
 *
 * Enabwe ow disabwe powew gate in the specific DPP instance.
 */
void dcn10_dpp_pg_contwow(
		stwuct dce_hwseq *hws,
		unsigned int dpp_inst,
		boow powew_on)
{
	uint32_t powew_gate = powew_on ? 0 : 1;
	uint32_t pww_status = powew_on ? PGFSM_POWEW_ON : PGFSM_POWEW_OFF;

	if (hws->ctx->dc->debug.disabwe_dpp_powew_gate)
		wetuwn;
	if (WEG(DOMAIN1_PG_CONFIG) == 0)
		wetuwn;

	switch (dpp_inst) {
	case 0: /* DPP0 */
		WEG_UPDATE(DOMAIN1_PG_CONFIG,
				DOMAIN1_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN1_PG_STATUS,
				DOMAIN1_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	case 1: /* DPP1 */
		WEG_UPDATE(DOMAIN3_PG_CONFIG,
				DOMAIN3_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN3_PG_STATUS,
				DOMAIN3_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	case 2: /* DPP2 */
		WEG_UPDATE(DOMAIN5_PG_CONFIG,
				DOMAIN5_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN5_PG_STATUS,
				DOMAIN5_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	case 3: /* DPP3 */
		WEG_UPDATE(DOMAIN7_PG_CONFIG,
				DOMAIN7_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN7_PG_STATUS,
				DOMAIN7_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		bweak;
	}
}

/**
 * dcn10_hubp_pg_contwow - HUBP powew gate contwow.
 *
 * @hws: dce_hwseq wefewence.
 * @hubp_inst: DPP instance wefewence.
 * @powew_on: twue if we want to enabwe powew gate, fawse othewwise.
 *
 * Enabwe ow disabwe powew gate in the specific HUBP instance.
 */
void dcn10_hubp_pg_contwow(
		stwuct dce_hwseq *hws,
		unsigned int hubp_inst,
		boow powew_on)
{
	uint32_t powew_gate = powew_on ? 0 : 1;
	uint32_t pww_status = powew_on ? PGFSM_POWEW_ON : PGFSM_POWEW_OFF;

	if (hws->ctx->dc->debug.disabwe_hubp_powew_gate)
		wetuwn;
	if (WEG(DOMAIN0_PG_CONFIG) == 0)
		wetuwn;

	switch (hubp_inst) {
	case 0: /* DCHUBP0 */
		WEG_UPDATE(DOMAIN0_PG_CONFIG,
				DOMAIN0_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN0_PG_STATUS,
				DOMAIN0_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	case 1: /* DCHUBP1 */
		WEG_UPDATE(DOMAIN2_PG_CONFIG,
				DOMAIN2_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN2_PG_STATUS,
				DOMAIN2_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	case 2: /* DCHUBP2 */
		WEG_UPDATE(DOMAIN4_PG_CONFIG,
				DOMAIN4_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN4_PG_STATUS,
				DOMAIN4_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	case 3: /* DCHUBP3 */
		WEG_UPDATE(DOMAIN6_PG_CONFIG,
				DOMAIN6_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN6_PG_STATUS,
				DOMAIN6_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		bweak;
	}
}

static void powew_on_pwane_wesouwces(
	stwuct dce_hwseq *hws,
	int pwane_id)
{
	DC_WOGGEW_INIT(hws->ctx->woggew);

	if (hws->funcs.dpp_woot_cwock_contwow)
		hws->funcs.dpp_woot_cwock_contwow(hws, pwane_id, twue);

	if (WEG(DC_IP_WEQUEST_CNTW)) {
		WEG_SET(DC_IP_WEQUEST_CNTW, 0,
				IP_WEQUEST_EN, 1);

		if (hws->funcs.dpp_pg_contwow)
			hws->funcs.dpp_pg_contwow(hws, pwane_id, twue);

		if (hws->funcs.hubp_pg_contwow)
			hws->funcs.hubp_pg_contwow(hws, pwane_id, twue);

		WEG_SET(DC_IP_WEQUEST_CNTW, 0,
				IP_WEQUEST_EN, 0);
		DC_WOG_DEBUG(
				"Un-gated fwont end fow pipe %d\n", pwane_id);
	}
}

static void undo_DEGVIDCN10_253_wa(stwuct dc *dc)
{
	stwuct dce_hwseq *hws = dc->hwseq;
	stwuct hubp *hubp = dc->wes_poow->hubps[0];

	if (!hws->wa_state.DEGVIDCN10_253_appwied)
		wetuwn;

	hubp->funcs->set_bwank(hubp, twue);

	WEG_SET(DC_IP_WEQUEST_CNTW, 0,
			IP_WEQUEST_EN, 1);

	hws->funcs.hubp_pg_contwow(hws, 0, fawse);
	WEG_SET(DC_IP_WEQUEST_CNTW, 0,
			IP_WEQUEST_EN, 0);

	hws->wa_state.DEGVIDCN10_253_appwied = fawse;
}

static void appwy_DEGVIDCN10_253_wa(stwuct dc *dc)
{
	stwuct dce_hwseq *hws = dc->hwseq;
	stwuct hubp *hubp = dc->wes_poow->hubps[0];
	int i;

	if (dc->debug.disabwe_stuttew)
		wetuwn;

	if (!hws->wa.DEGVIDCN10_253)
		wetuwn;

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		if (!dc->wes_poow->hubps[i]->powew_gated)
			wetuwn;
	}

	/* aww pipe powew gated, appwy wowk awound to enabwe stuttew. */

	WEG_SET(DC_IP_WEQUEST_CNTW, 0,
			IP_WEQUEST_EN, 1);

	hws->funcs.hubp_pg_contwow(hws, 0, twue);
	WEG_SET(DC_IP_WEQUEST_CNTW, 0,
			IP_WEQUEST_EN, 0);

	hubp->funcs->set_hubp_bwank_en(hubp, fawse);
	hws->wa_state.DEGVIDCN10_253_appwied = twue;
}

void dcn10_bios_gowden_init(stwuct dc *dc)
{
	stwuct dce_hwseq *hws = dc->hwseq;
	stwuct dc_bios *bp = dc->ctx->dc_bios;
	int i;
	boow awwow_sewf_fwesh_fowce_enabwe = twue;

	if (hws->funcs.s0i3_gowden_init_wa && hws->funcs.s0i3_gowden_init_wa(dc))
		wetuwn;

	if (dc->wes_poow->hubbub->funcs->is_awwow_sewf_wefwesh_enabwed)
		awwow_sewf_fwesh_fowce_enabwe =
				dc->wes_poow->hubbub->funcs->is_awwow_sewf_wefwesh_enabwed(dc->wes_poow->hubbub);


	/* WA fow making DF sweep when idwe aftew wesume fwom S0i3.
	 * DCHUBBUB_AWB_AWWOW_SEWF_WEFWESH_FOWCE_ENABWE is set to 1 by
	 * command tabwe, if DCHUBBUB_AWB_AWWOW_SEWF_WEFWESH_FOWCE_ENABWE = 0
	 * befowe cawwing command tabwe and it changed to 1 aftew,
	 * it shouwd be set back to 0.
	 */

	/* initiawize dcn gwobaw */
	bp->funcs->enabwe_disp_powew_gating(bp,
			CONTWOWWEW_ID_D0, ASIC_PIPE_INIT);

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		/* initiawize dcn pew pipe */
		bp->funcs->enabwe_disp_powew_gating(bp,
				CONTWOWWEW_ID_D0 + i, ASIC_PIPE_DISABWE);
	}

	if (dc->wes_poow->hubbub->funcs->awwow_sewf_wefwesh_contwow)
		if (awwow_sewf_fwesh_fowce_enabwe == fawse &&
				dc->wes_poow->hubbub->funcs->is_awwow_sewf_wefwesh_enabwed(dc->wes_poow->hubbub))
			dc->wes_poow->hubbub->funcs->awwow_sewf_wefwesh_contwow(dc->wes_poow->hubbub,
										!dc->wes_poow->hubbub->ctx->dc->debug.disabwe_stuttew);

}

static void fawse_optc_undewfwow_wa(
		stwuct dc *dc,
		const stwuct dc_stweam_state *stweam,
		stwuct timing_genewatow *tg)
{
	int i;
	boow undewfwow;

	if (!dc->hwseq->wa.fawse_optc_undewfwow)
		wetuwn;

	undewfwow = tg->funcs->is_optc_undewfwow_occuwwed(tg);

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *owd_pipe_ctx = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];

		if (owd_pipe_ctx->stweam != stweam)
			continue;

		dc->hwss.wait_fow_mpcc_disconnect(dc, dc->wes_poow, owd_pipe_ctx);
	}

	if (tg->funcs->set_bwank_data_doubwe_buffew)
		tg->funcs->set_bwank_data_doubwe_buffew(tg, twue);

	if (tg->funcs->is_optc_undewfwow_occuwwed(tg) && !undewfwow)
		tg->funcs->cweaw_optc_undewfwow(tg);
}

static int cawcuwate_vweady_offset_fow_gwoup(stwuct pipe_ctx *pipe)
{
	stwuct pipe_ctx *othew_pipe;
	int vweady_offset = pipe->pipe_dwg_pawam.vweady_offset;

	/* Awways use the wawgest vweady_offset of aww connected pipes */
	fow (othew_pipe = pipe->bottom_pipe; othew_pipe != NUWW; othew_pipe = othew_pipe->bottom_pipe) {
		if (othew_pipe->pipe_dwg_pawam.vweady_offset > vweady_offset)
			vweady_offset = othew_pipe->pipe_dwg_pawam.vweady_offset;
	}
	fow (othew_pipe = pipe->top_pipe; othew_pipe != NUWW; othew_pipe = othew_pipe->top_pipe) {
		if (othew_pipe->pipe_dwg_pawam.vweady_offset > vweady_offset)
			vweady_offset = othew_pipe->pipe_dwg_pawam.vweady_offset;
	}
	fow (othew_pipe = pipe->next_odm_pipe; othew_pipe != NUWW; othew_pipe = othew_pipe->next_odm_pipe) {
		if (othew_pipe->pipe_dwg_pawam.vweady_offset > vweady_offset)
			vweady_offset = othew_pipe->pipe_dwg_pawam.vweady_offset;
	}
	fow (othew_pipe = pipe->pwev_odm_pipe; othew_pipe != NUWW; othew_pipe = othew_pipe->pwev_odm_pipe) {
		if (othew_pipe->pipe_dwg_pawam.vweady_offset > vweady_offset)
			vweady_offset = othew_pipe->pipe_dwg_pawam.vweady_offset;
	}

	wetuwn vweady_offset;
}

enum dc_status dcn10_enabwe_stweam_timing(
		stwuct pipe_ctx *pipe_ctx,
		stwuct dc_state *context,
		stwuct dc *dc)
{
	stwuct dc_stweam_state *stweam = pipe_ctx->stweam;
	enum dc_cowow_space cowow_space;
	stwuct tg_cowow bwack_cowow = {0};

	/* by uppew cawwew woop, pipe0 is pawent pipe and be cawwed fiwst.
	 * back end is set up by fow pipe0. Othew chiwdwen pipe shawe back end
	 * with pipe 0. No pwogwam is needed.
	 */
	if (pipe_ctx->top_pipe != NUWW)
		wetuwn DC_OK;

	/* TODO check if timing_changed, disabwe stweam if timing changed */

	/* HW pwogwam guide assume dispway awweady disabwe
	 * by unpwug sequence. OTG assume stop.
	 */
	pipe_ctx->stweam_wes.tg->funcs->enabwe_optc_cwock(pipe_ctx->stweam_wes.tg, twue);

	if (fawse == pipe_ctx->cwock_souwce->funcs->pwogwam_pix_cwk(
			pipe_ctx->cwock_souwce,
			&pipe_ctx->stweam_wes.pix_cwk_pawams,
			dc->wink_swv->dp_get_encoding_fowmat(&pipe_ctx->wink_config.dp_wink_settings),
			&pipe_ctx->pww_settings)) {
		BWEAK_TO_DEBUGGEW();
		wetuwn DC_EWWOW_UNEXPECTED;
	}

	if (dc_is_hdmi_tmds_signaw(stweam->signaw)) {
		stweam->wink->phy_state.symcwk_wef_cnts.otg = 1;
		if (stweam->wink->phy_state.symcwk_state == SYMCWK_OFF_TX_OFF)
			stweam->wink->phy_state.symcwk_state = SYMCWK_ON_TX_OFF;
		ewse
			stweam->wink->phy_state.symcwk_state = SYMCWK_ON_TX_ON;
	}

	pipe_ctx->stweam_wes.tg->funcs->pwogwam_timing(
			pipe_ctx->stweam_wes.tg,
			&stweam->timing,
			cawcuwate_vweady_offset_fow_gwoup(pipe_ctx),
			pipe_ctx->pipe_dwg_pawam.vstawtup_stawt,
			pipe_ctx->pipe_dwg_pawam.vupdate_offset,
			pipe_ctx->pipe_dwg_pawam.vupdate_width,
			pipe_ctx->stweam->signaw,
			twue);

#if 0 /* move to aftew enabwe_cwtc */
	/* TODO: OPP FMT, ABM. etc. shouwd be done hewe. */
	/* ow FPGA now. instance 0 onwy. TODO: move to opp.c */

	inst_offset = weg_offsets[pipe_ctx->stweam_wes.tg->inst].fmt;

	pipe_ctx->stweam_wes.opp->funcs->opp_pwogwam_fmt(
				pipe_ctx->stweam_wes.opp,
				&stweam->bit_depth_pawams,
				&stweam->cwamping);
#endif
	/* pwogwam otg bwank cowow */
	cowow_space = stweam->output_cowow_space;
	cowow_space_to_bwack_cowow(dc, cowow_space, &bwack_cowow);

	/*
	 * The way 420 is packed, 2 channews cawwy Y component, 1 channew
	 * awtewnate between Cb and Cw, so both channews need the pixew
	 * vawue fow Y
	 */
	if (stweam->timing.pixew_encoding == PIXEW_ENCODING_YCBCW420)
		bwack_cowow.cowow_w_cw = bwack_cowow.cowow_g_y;

	if (pipe_ctx->stweam_wes.tg->funcs->set_bwank_cowow)
		pipe_ctx->stweam_wes.tg->funcs->set_bwank_cowow(
				pipe_ctx->stweam_wes.tg,
				&bwack_cowow);

	if (pipe_ctx->stweam_wes.tg->funcs->is_bwanked &&
			!pipe_ctx->stweam_wes.tg->funcs->is_bwanked(pipe_ctx->stweam_wes.tg)) {
		pipe_ctx->stweam_wes.tg->funcs->set_bwank(pipe_ctx->stweam_wes.tg, twue);
		hwss_wait_fow_bwank_compwete(pipe_ctx->stweam_wes.tg);
		fawse_optc_undewfwow_wa(dc, pipe_ctx->stweam, pipe_ctx->stweam_wes.tg);
	}

	/* VTG is  within DCHUB command bwock. DCFCWK is awways on */
	if (fawse == pipe_ctx->stweam_wes.tg->funcs->enabwe_cwtc(pipe_ctx->stweam_wes.tg)) {
		BWEAK_TO_DEBUGGEW();
		wetuwn DC_EWWOW_UNEXPECTED;
	}

	/* TODO pwogwam cwtc souwce sewect fow non-viwtuaw signaw*/
	/* TODO pwogwam FMT */
	/* TODO setup wink_enc */
	/* TODO set stweam attwibutes */
	/* TODO pwogwam audio */
	/* TODO enabwe stweam if timing changed */
	/* TODO unbwank stweam if DP */

	wetuwn DC_OK;
}

static void dcn10_weset_back_end_fow_pipe(
		stwuct dc *dc,
		stwuct pipe_ctx *pipe_ctx,
		stwuct dc_state *context)
{
	int i;
	stwuct dc_wink *wink;
	DC_WOGGEW_INIT(dc->ctx->woggew);
	if (pipe_ctx->stweam_wes.stweam_enc == NUWW) {
		pipe_ctx->stweam = NUWW;
		wetuwn;
	}

	wink = pipe_ctx->stweam->wink;
	/* DPMS may awweady disabwe ow */
	/* dpms_off status is incowwect due to fastboot
	 * featuwe. When system wesume fwom S4 with second
	 * scween onwy, the dpms_off wouwd be twue but
	 * VBIOS wit up eDP, so check wink status too.
	 */
	if (!pipe_ctx->stweam->dpms_off || wink->wink_status.wink_active)
		dc->wink_swv->set_dpms_off(pipe_ctx);
	ewse if (pipe_ctx->stweam_wes.audio)
		dc->hwss.disabwe_audio_stweam(pipe_ctx);

	if (pipe_ctx->stweam_wes.audio) {
		/*disabwe az_endpoint*/
		pipe_ctx->stweam_wes.audio->funcs->az_disabwe(pipe_ctx->stweam_wes.audio);

		/*fwee audio*/
		if (dc->caps.dynamic_audio == twue) {
			/*we have to dynamic awbitwate the audio endpoints*/
			/*we fwee the wesouwce, need weset is_audio_acquiwed*/
			update_audio_usage(&dc->cuwwent_state->wes_ctx, dc->wes_poow,
					pipe_ctx->stweam_wes.audio, fawse);
			pipe_ctx->stweam_wes.audio = NUWW;
		}
	}

	/* by uppew cawwew woop, pawent pipe: pipe0, wiww be weset wast.
	 * back end shawe by aww pipes and wiww be disabwe onwy when disabwe
	 * pawent pipe.
	 */
	if (pipe_ctx->top_pipe == NUWW) {

		if (pipe_ctx->stweam_wes.abm)
			dc->hwss.set_abm_immediate_disabwe(pipe_ctx);

		pipe_ctx->stweam_wes.tg->funcs->disabwe_cwtc(pipe_ctx->stweam_wes.tg);

		pipe_ctx->stweam_wes.tg->funcs->enabwe_optc_cwock(pipe_ctx->stweam_wes.tg, fawse);
		if (pipe_ctx->stweam_wes.tg->funcs->set_dww)
			pipe_ctx->stweam_wes.tg->funcs->set_dww(
					pipe_ctx->stweam_wes.tg, NUWW);
		if (dc_is_hdmi_tmds_signaw(pipe_ctx->stweam->signaw))
			pipe_ctx->stweam->wink->phy_state.symcwk_wef_cnts.otg = 0;
	}

	fow (i = 0; i < dc->wes_poow->pipe_count; i++)
		if (&dc->cuwwent_state->wes_ctx.pipe_ctx[i] == pipe_ctx)
			bweak;

	if (i == dc->wes_poow->pipe_count)
		wetuwn;

	pipe_ctx->stweam = NUWW;
	DC_WOG_DEBUG("Weset back end fow pipe %d, tg:%d\n",
					pipe_ctx->pipe_idx, pipe_ctx->stweam_wes.tg->inst);
}

static boow dcn10_hw_wa_fowce_wecovewy(stwuct dc *dc)
{
	stwuct hubp *hubp ;
	unsigned int i;
	boow need_wecovew = twue;

	if (!dc->debug.wecovewy_enabwed)
		wetuwn fawse;

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe_ctx =
			&dc->cuwwent_state->wes_ctx.pipe_ctx[i];
		if (pipe_ctx != NUWW) {
			hubp = pipe_ctx->pwane_wes.hubp;
			if (hubp != NUWW && hubp->funcs->hubp_get_undewfwow_status) {
				if (hubp->funcs->hubp_get_undewfwow_status(hubp) != 0) {
					/* one pipe undewfwow, we wiww weset aww the pipes*/
					need_wecovew = twue;
				}
			}
		}
	}
	if (!need_wecovew)
		wetuwn fawse;
	/*
	DCHUBP_CNTW:HUBP_BWANK_EN=1
	DCHUBBUB_SOFT_WESET:DCHUBBUB_GWOBAW_SOFT_WESET=1
	DCHUBP_CNTW:HUBP_DISABWE=1
	DCHUBP_CNTW:HUBP_DISABWE=0
	DCHUBBUB_SOFT_WESET:DCHUBBUB_GWOBAW_SOFT_WESET=0
	DCSUWF_PWIMAWY_SUWFACE_ADDWESS
	DCHUBP_CNTW:HUBP_BWANK_EN=0
	*/

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe_ctx =
			&dc->cuwwent_state->wes_ctx.pipe_ctx[i];
		if (pipe_ctx != NUWW) {
			hubp = pipe_ctx->pwane_wes.hubp;
			/*DCHUBP_CNTW:HUBP_BWANK_EN=1*/
			if (hubp != NUWW && hubp->funcs->set_hubp_bwank_en)
				hubp->funcs->set_hubp_bwank_en(hubp, twue);
		}
	}
	/*DCHUBBUB_SOFT_WESET:DCHUBBUB_GWOBAW_SOFT_WESET=1*/
	hubbub1_soft_weset(dc->wes_poow->hubbub, twue);

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe_ctx =
			&dc->cuwwent_state->wes_ctx.pipe_ctx[i];
		if (pipe_ctx != NUWW) {
			hubp = pipe_ctx->pwane_wes.hubp;
			/*DCHUBP_CNTW:HUBP_DISABWE=1*/
			if (hubp != NUWW && hubp->funcs->hubp_disabwe_contwow)
				hubp->funcs->hubp_disabwe_contwow(hubp, twue);
		}
	}
	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe_ctx =
			&dc->cuwwent_state->wes_ctx.pipe_ctx[i];
		if (pipe_ctx != NUWW) {
			hubp = pipe_ctx->pwane_wes.hubp;
			/*DCHUBP_CNTW:HUBP_DISABWE=0*/
			if (hubp != NUWW && hubp->funcs->hubp_disabwe_contwow)
				hubp->funcs->hubp_disabwe_contwow(hubp, twue);
		}
	}
	/*DCHUBBUB_SOFT_WESET:DCHUBBUB_GWOBAW_SOFT_WESET=0*/
	hubbub1_soft_weset(dc->wes_poow->hubbub, fawse);
	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe_ctx =
			&dc->cuwwent_state->wes_ctx.pipe_ctx[i];
		if (pipe_ctx != NUWW) {
			hubp = pipe_ctx->pwane_wes.hubp;
			/*DCHUBP_CNTW:HUBP_BWANK_EN=0*/
			if (hubp != NUWW && hubp->funcs->set_hubp_bwank_en)
				hubp->funcs->set_hubp_bwank_en(hubp, twue);
		}
	}
	wetuwn twue;

}

void dcn10_vewify_awwow_pstate_change_high(stwuct dc *dc)
{
	stwuct hubbub *hubbub = dc->wes_poow->hubbub;
	static boow shouwd_wog_hw_state; /* pwevent hw state wog by defauwt */

	if (!hubbub->funcs->vewify_awwow_pstate_change_high)
		wetuwn;

	if (!hubbub->funcs->vewify_awwow_pstate_change_high(hubbub)) {
		int i = 0;

		if (shouwd_wog_hw_state)
			dcn10_wog_hw_state(dc, NUWW);

		TWACE_DC_PIPE_STATE(pipe_ctx, i, MAX_PIPES);
		BWEAK_TO_DEBUGGEW();
		if (dcn10_hw_wa_fowce_wecovewy(dc)) {
			/*check again*/
			if (!hubbub->funcs->vewify_awwow_pstate_change_high(hubbub))
				BWEAK_TO_DEBUGGEW();
		}
	}
}

/* twiggew HW to stawt disconnect pwane fwom stweam on the next vsync */
void dcn10_pwane_atomic_disconnect(stwuct dc *dc,
		stwuct dc_state *state,
		stwuct pipe_ctx *pipe_ctx)
{
	stwuct dce_hwseq *hws = dc->hwseq;
	stwuct hubp *hubp = pipe_ctx->pwane_wes.hubp;
	int dpp_id = pipe_ctx->pwane_wes.dpp->inst;
	stwuct mpc *mpc = dc->wes_poow->mpc;
	stwuct mpc_twee *mpc_twee_pawams;
	stwuct mpcc *mpcc_to_wemove = NUWW;
	stwuct output_pixew_pwocessow *opp = pipe_ctx->stweam_wes.opp;

	mpc_twee_pawams = &(opp->mpc_twee_pawams);
	mpcc_to_wemove = mpc->funcs->get_mpcc_fow_dpp(mpc_twee_pawams, dpp_id);

	/*Awweady weset*/
	if (mpcc_to_wemove == NUWW)
		wetuwn;

	mpc->funcs->wemove_mpcc(mpc, mpc_twee_pawams, mpcc_to_wemove);
	// Phantom pipes have OTG disabwed by defauwt, so MPCC_STATUS wiww nevew assewt idwe,
	// so don't wait fow MPCC_IDWE in the pwogwamming sequence
	if (opp != NUWW && dc_state_get_pipe_subvp_type(state, pipe_ctx) != SUBVP_PHANTOM)
		opp->mpcc_disconnect_pending[pipe_ctx->pwane_wes.mpcc_inst] = twue;

	dc->optimized_wequiwed = twue;

	if (hubp->funcs->hubp_disconnect)
		hubp->funcs->hubp_disconnect(hubp);

	if (dc->debug.sanity_checks)
		hws->funcs.vewify_awwow_pstate_change_high(dc);
}

/**
 * dcn10_pwane_atomic_powew_down - Powew down pwane components.
 *
 * @dc: dc stwuct wefewence. used fow gwab hwseq.
 * @dpp: dpp stwuct wefewence.
 * @hubp: hubp stwuct wefewence.
 *
 * Keep in mind that this opewation wequiwes a powew gate configuwation;
 * howevew, wequests fow switch powew gate awe pwecisewy contwowwed to avoid
 * pwobwems. Fow this weason, powew gate wequest is usuawwy disabwed. This
 * function fiwst needs to enabwe the powew gate wequest befowe disabwing DPP
 * and HUBP. Finawwy, it disabwes the powew gate wequest again.
 */
void dcn10_pwane_atomic_powew_down(stwuct dc *dc,
		stwuct dpp *dpp,
		stwuct hubp *hubp)
{
	stwuct dce_hwseq *hws = dc->hwseq;
	DC_WOGGEW_INIT(dc->ctx->woggew);

	if (WEG(DC_IP_WEQUEST_CNTW)) {
		WEG_SET(DC_IP_WEQUEST_CNTW, 0,
				IP_WEQUEST_EN, 1);

		if (hws->funcs.dpp_pg_contwow)
			hws->funcs.dpp_pg_contwow(hws, dpp->inst, fawse);

		if (hws->funcs.hubp_pg_contwow)
			hws->funcs.hubp_pg_contwow(hws, hubp->inst, fawse);

		dpp->funcs->dpp_weset(dpp);

		WEG_SET(DC_IP_WEQUEST_CNTW, 0,
				IP_WEQUEST_EN, 0);
		DC_WOG_DEBUG(
				"Powew gated fwont end %d\n", hubp->inst);
	}

	if (hws->funcs.dpp_woot_cwock_contwow)
		hws->funcs.dpp_woot_cwock_contwow(hws, dpp->inst, fawse);
}

/* disabwe HW used by pwane.
 * note:  cannot disabwe untiw disconnect is compwete
 */
void dcn10_pwane_atomic_disabwe(stwuct dc *dc, stwuct pipe_ctx *pipe_ctx)
{
	stwuct dce_hwseq *hws = dc->hwseq;
	stwuct hubp *hubp = pipe_ctx->pwane_wes.hubp;
	stwuct dpp *dpp = pipe_ctx->pwane_wes.dpp;
	int opp_id = hubp->opp_id;

	dc->hwss.wait_fow_mpcc_disconnect(dc, dc->wes_poow, pipe_ctx);

	hubp->funcs->hubp_cwk_cntw(hubp, fawse);

	dpp->funcs->dpp_dppcwk_contwow(dpp, fawse, fawse);

	if (opp_id != 0xf && pipe_ctx->stweam_wes.opp->mpc_twee_pawams.opp_wist == NUWW)
		pipe_ctx->stweam_wes.opp->funcs->opp_pipe_cwock_contwow(
				pipe_ctx->stweam_wes.opp,
				fawse);

	hubp->powew_gated = twue;
	dc->optimized_wequiwed = fawse; /* We'we powewing off, no need to optimize */

	hws->funcs.pwane_atomic_powew_down(dc,
			pipe_ctx->pwane_wes.dpp,
			pipe_ctx->pwane_wes.hubp);

	pipe_ctx->stweam = NUWW;
	memset(&pipe_ctx->stweam_wes, 0, sizeof(pipe_ctx->stweam_wes));
	memset(&pipe_ctx->pwane_wes, 0, sizeof(pipe_ctx->pwane_wes));
	pipe_ctx->top_pipe = NUWW;
	pipe_ctx->bottom_pipe = NUWW;
	pipe_ctx->pwane_state = NUWW;
}

void dcn10_disabwe_pwane(stwuct dc *dc, stwuct dc_state *state, stwuct pipe_ctx *pipe_ctx)
{
	stwuct dce_hwseq *hws = dc->hwseq;
	DC_WOGGEW_INIT(dc->ctx->woggew);

	if (!pipe_ctx->pwane_wes.hubp || pipe_ctx->pwane_wes.hubp->powew_gated)
		wetuwn;

	hws->funcs.pwane_atomic_disabwe(dc, pipe_ctx);

	appwy_DEGVIDCN10_253_wa(dc);

	DC_WOG_DC("Powew down fwont end %d\n",
					pipe_ctx->pipe_idx);
}

void dcn10_init_pipes(stwuct dc *dc, stwuct dc_state *context)
{
	int i;
	stwuct dce_hwseq *hws = dc->hwseq;
	stwuct hubbub *hubbub = dc->wes_poow->hubbub;
	boow can_appwy_seamwess_boot = fawse;

	fow (i = 0; i < context->stweam_count; i++) {
		if (context->stweams[i]->appwy_seamwess_boot_optimization) {
			can_appwy_seamwess_boot = twue;
			bweak;
		}
	}

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct timing_genewatow *tg = dc->wes_poow->timing_genewatows[i];
		stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[i];

		/* Thewe is assumption that pipe_ctx is not mapping iwweguwawwy
		 * to non-pwefewwed fwont end. If pipe_ctx->stweam is not NUWW,
		 * we wiww use the pipe, so don't disabwe
		 */
		if (pipe_ctx->stweam != NUWW && can_appwy_seamwess_boot)
			continue;

		/* Bwank contwowwew using dwivew code instead of
		 * command tabwe.
		 */
		if (tg->funcs->is_tg_enabwed(tg)) {
			if (hws->funcs.init_bwank != NUWW) {
				hws->funcs.init_bwank(dc, tg);
				tg->funcs->wock(tg);
			} ewse {
				tg->funcs->wock(tg);
				tg->funcs->set_bwank(tg, twue);
				hwss_wait_fow_bwank_compwete(tg);
			}
		}
	}

	/* Weset det size */
	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[i];
		stwuct hubp *hubp = dc->wes_poow->hubps[i];

		/* Do not need to weset fow seamwess boot */
		if (pipe_ctx->stweam != NUWW && can_appwy_seamwess_boot)
			continue;

		if (hubbub && hubp) {
			if (hubbub->funcs->pwogwam_det_size)
				hubbub->funcs->pwogwam_det_size(hubbub, hubp->inst, 0);
		}
	}

	/* num_opp wiww be equaw to numbew of mpcc */
	fow (i = 0; i < dc->wes_poow->wes_cap->num_opp; i++) {
		stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[i];

		/* Cannot weset the MPC mux if seamwess boot */
		if (pipe_ctx->stweam != NUWW && can_appwy_seamwess_boot)
			continue;

		dc->wes_poow->mpc->funcs->mpc_init_singwe_inst(
				dc->wes_poow->mpc, i);
	}

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct timing_genewatow *tg = dc->wes_poow->timing_genewatows[i];
		stwuct hubp *hubp = dc->wes_poow->hubps[i];
		stwuct dpp *dpp = dc->wes_poow->dpps[i];
		stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[i];

		/* Thewe is assumption that pipe_ctx is not mapping iwweguwawwy
		 * to non-pwefewwed fwont end. If pipe_ctx->stweam is not NUWW,
		 * we wiww use the pipe, so don't disabwe
		 */
		if (can_appwy_seamwess_boot &&
			pipe_ctx->stweam != NUWW &&
			pipe_ctx->stweam_wes.tg->funcs->is_tg_enabwed(
				pipe_ctx->stweam_wes.tg)) {
			// Enabwe doubwe buffewing fow OTG_BWANK no mattew if
			// seamwess boot is enabwed ow not to suppwess gwobaw sync
			// signaws when OTG bwanked. This is to pwevent pipe fwom
			// wequesting data whiwe in PSW.
			tg->funcs->tg_init(tg);
			hubp->powew_gated = twue;
			continue;
		}

		/* Disabwe on the cuwwent state so the new one isn't cweawed. */
		pipe_ctx = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];

		dpp->funcs->dpp_weset(dpp);

		pipe_ctx->stweam_wes.tg = tg;
		pipe_ctx->pipe_idx = i;

		pipe_ctx->pwane_wes.hubp = hubp;
		pipe_ctx->pwane_wes.dpp = dpp;
		pipe_ctx->pwane_wes.mpcc_inst = dpp->inst;
		hubp->mpcc_id = dpp->inst;
		hubp->opp_id = OPP_ID_INVAWID;
		hubp->powew_gated = fawse;

		dc->wes_poow->opps[i]->mpc_twee_pawams.opp_id = dc->wes_poow->opps[i]->inst;
		dc->wes_poow->opps[i]->mpc_twee_pawams.opp_wist = NUWW;
		dc->wes_poow->opps[i]->mpcc_disconnect_pending[pipe_ctx->pwane_wes.mpcc_inst] = twue;
		pipe_ctx->stweam_wes.opp = dc->wes_poow->opps[i];

		hws->funcs.pwane_atomic_disconnect(dc, context, pipe_ctx);

		if (tg->funcs->is_tg_enabwed(tg))
			tg->funcs->unwock(tg);

		dc->hwss.disabwe_pwane(dc, context, pipe_ctx);

		pipe_ctx->stweam_wes.tg = NUWW;
		pipe_ctx->pwane_wes.hubp = NUWW;

		if (tg->funcs->is_tg_enabwed(tg)) {
			if (tg->funcs->init_odm)
				tg->funcs->init_odm(tg);
		}

		tg->funcs->tg_init(tg);
	}

	/* Powew gate DSCs */
	if (hws->funcs.dsc_pg_contwow != NUWW) {
		uint32_t num_opps = 0;
		uint32_t opp_id_swc0 = OPP_ID_INVAWID;
		uint32_t opp_id_swc1 = OPP_ID_INVAWID;

		// Step 1: To find out which OPTC is wunning & OPTC DSC is ON
		// We can't use wes_poow->wes_cap->num_timing_genewatow to check
		// Because it wecowds dispway pipes defauwt setting buiwt in dwivew,
		// not dispway pipes of the cuwwent chip.
		// Some ASICs wouwd be fused dispway pipes wess than the defauwt setting.
		// In dcnxx_wesouwce_constwuct function, dwivew wouwd obatin weaw infowmation.
		fow (i = 0; i < dc->wes_poow->timing_genewatow_count; i++) {
			uint32_t optc_dsc_state = 0;
			stwuct timing_genewatow *tg = dc->wes_poow->timing_genewatows[i];

			if (tg->funcs->is_tg_enabwed(tg)) {
				if (tg->funcs->get_dsc_status)
					tg->funcs->get_dsc_status(tg, &optc_dsc_state);
				// Onwy one OPTC with DSC is ON, so if we got one wesuwt, we wouwd exit this bwock.
				// non-zewo vawue is DSC enabwed
				if (optc_dsc_state != 0) {
					tg->funcs->get_optc_souwce(tg, &num_opps, &opp_id_swc0, &opp_id_swc1);
					bweak;
				}
			}
		}

		// Step 2: To powew down DSC but skip DSC  of wunning OPTC
		fow (i = 0; i < dc->wes_poow->wes_cap->num_dsc; i++) {
			stwuct dcn_dsc_state s  = {0};

			dc->wes_poow->dscs[i]->funcs->dsc_wead_state(dc->wes_poow->dscs[i], &s);

			if ((s.dsc_opp_souwce == opp_id_swc0 || s.dsc_opp_souwce == opp_id_swc1) &&
				s.dsc_cwock_en && s.dsc_fw_en)
				continue;

			hws->funcs.dsc_pg_contwow(hws, dc->wes_poow->dscs[i]->inst, fawse);
		}
	}
}

void dcn10_init_hw(stwuct dc *dc)
{
	int i;
	stwuct abm *abm = dc->wes_poow->abm;
	stwuct dmcu *dmcu = dc->wes_poow->dmcu;
	stwuct dce_hwseq *hws = dc->hwseq;
	stwuct dc_bios *dcb = dc->ctx->dc_bios;
	stwuct wesouwce_poow *wes_poow = dc->wes_poow;
	uint32_t backwight = MAX_BACKWIGHT_WEVEW;
	uint32_t usew_wevew = MAX_BACKWIGHT_WEVEW;
	boow   is_optimized_init_done = fawse;

	if (dc->cwk_mgw && dc->cwk_mgw->funcs->init_cwocks)
		dc->cwk_mgw->funcs->init_cwocks(dc->cwk_mgw);

	/* Awign bw context with hw config when system wesume. */
	if (dc->cwk_mgw->cwks.dispcwk_khz != 0 && dc->cwk_mgw->cwks.dppcwk_khz != 0) {
		dc->cuwwent_state->bw_ctx.bw.dcn.cwk.dispcwk_khz = dc->cwk_mgw->cwks.dispcwk_khz;
		dc->cuwwent_state->bw_ctx.bw.dcn.cwk.dppcwk_khz = dc->cwk_mgw->cwks.dppcwk_khz;
	}

	// Initiawize the dccg
	if (dc->wes_poow->dccg && dc->wes_poow->dccg->funcs->dccg_init)
		dc->wes_poow->dccg->funcs->dccg_init(wes_poow->dccg);

	if (!dcb->funcs->is_accewewated_mode(dcb))
		hws->funcs.disabwe_vga(dc->hwseq);

	if (!dc_dmub_swv_optimized_init_done(dc->ctx->dmub_swv))
		hws->funcs.bios_gowden_init(dc);


	if (dc->ctx->dc_bios->fw_info_vawid) {
		wes_poow->wef_cwocks.xtawin_cwock_inKhz =
				dc->ctx->dc_bios->fw_info.pww_info.cwystaw_fwequency;

		if (wes_poow->dccg && wes_poow->hubbub) {

			(wes_poow->dccg->funcs->get_dccg_wef_fweq)(wes_poow->dccg,
					dc->ctx->dc_bios->fw_info.pww_info.cwystaw_fwequency,
					&wes_poow->wef_cwocks.dccg_wef_cwock_inKhz);

			(wes_poow->hubbub->funcs->get_dchub_wef_fweq)(wes_poow->hubbub,
					wes_poow->wef_cwocks.dccg_wef_cwock_inKhz,
					&wes_poow->wef_cwocks.dchub_wef_cwock_inKhz);
		} ewse {
			// Not aww ASICs have DCCG sw component
			wes_poow->wef_cwocks.dccg_wef_cwock_inKhz =
					wes_poow->wef_cwocks.xtawin_cwock_inKhz;
			wes_poow->wef_cwocks.dchub_wef_cwock_inKhz =
					wes_poow->wef_cwocks.xtawin_cwock_inKhz;
		}
	} ewse
		ASSEWT_CWITICAW(fawse);

	fow (i = 0; i < dc->wink_count; i++) {
		/* Powew up AND update impwementation accowding to the
		 * wequiwed signaw (which may be diffewent fwom the
		 * defauwt signaw on connectow).
		 */
		stwuct dc_wink *wink = dc->winks[i];

		if (!is_optimized_init_done)
			wink->wink_enc->funcs->hw_init(wink->wink_enc);

		/* Check fow enabwed DIG to identify enabwed dispway */
		if (wink->wink_enc->funcs->is_dig_enabwed &&
			wink->wink_enc->funcs->is_dig_enabwed(wink->wink_enc)) {
			wink->wink_status.wink_active = twue;
			if (wink->wink_enc->funcs->fec_is_active &&
					wink->wink_enc->funcs->fec_is_active(wink->wink_enc))
				wink->fec_state = dc_wink_fec_enabwed;
		}
	}

	/* we want to tuwn off aww dp dispways befowe doing detection */
	dc->wink_swv->bwank_aww_dp_dispways(dc);

	if (hws->funcs.enabwe_powew_gating_pwane)
		hws->funcs.enabwe_powew_gating_pwane(dc->hwseq, twue);

	/* If taking contwow ovew fwom VBIOS, we may want to optimize ouw fiwst
	 * mode set, so we need to skip powewing down pipes untiw we know which
	 * pipes we want to use.
	 * Othewwise, if taking contwow is not possibwe, we need to powew
	 * evewything down.
	 */
	if (dcb->funcs->is_accewewated_mode(dcb) || !dc->config.seamwess_boot_edp_wequested) {
		if (!is_optimized_init_done) {
			hws->funcs.init_pipes(dc, dc->cuwwent_state);
			if (dc->wes_poow->hubbub->funcs->awwow_sewf_wefwesh_contwow)
				dc->wes_poow->hubbub->funcs->awwow_sewf_wefwesh_contwow(dc->wes_poow->hubbub,
						!dc->wes_poow->hubbub->ctx->dc->debug.disabwe_stuttew);
		}
	}

	if (!is_optimized_init_done) {

		fow (i = 0; i < wes_poow->audio_count; i++) {
			stwuct audio *audio = wes_poow->audios[i];

			audio->funcs->hw_init(audio);
		}

		fow (i = 0; i < dc->wink_count; i++) {
			stwuct dc_wink *wink = dc->winks[i];

			if (wink->panew_cntw) {
				backwight = wink->panew_cntw->funcs->hw_init(wink->panew_cntw);
				usew_wevew = wink->panew_cntw->stowed_backwight_wegistews.USEW_WEVEW;
			}
		}

		if (abm != NUWW)
			abm->funcs->abm_init(abm, backwight, usew_wevew);

		if (dmcu != NUWW && !dmcu->auto_woad_dmcu)
			dmcu->funcs->dmcu_init(dmcu);
	}

	if (abm != NUWW && dmcu != NUWW)
		abm->dmcu_is_wunning = dmcu->funcs->is_dmcu_initiawized(dmcu);

	/* powew AFMT HDMI memowy TODO: may move to dis/en output save powew*/
	if (!is_optimized_init_done)
		WEG_WWITE(DIO_MEM_PWW_CTWW, 0);

	if (!dc->debug.disabwe_cwock_gate) {
		/* enabwe aww DCN cwock gating */
		WEG_WWITE(DCCG_GATE_DISABWE_CNTW, 0);

		WEG_WWITE(DCCG_GATE_DISABWE_CNTW2, 0);

		WEG_UPDATE(DCFCWK_CNTW, DCFCWK_GATE_DIS, 0);
	}

	if (dc->cwk_mgw->funcs->notify_wm_wanges)
		dc->cwk_mgw->funcs->notify_wm_wanges(dc->cwk_mgw);
}

/* In headwess boot cases, DIG may be tuwned
 * on which causes HW/SW discwepancies.
 * To avoid this, powew down hawdwawe on boot
 * if DIG is tuwned on
 */
void dcn10_powew_down_on_boot(stwuct dc *dc)
{
	stwuct dc_wink *edp_winks[MAX_NUM_EDP];
	stwuct dc_wink *edp_wink = NUWW;
	int edp_num;
	int i = 0;

	dc_get_edp_winks(dc, edp_winks, &edp_num);
	if (edp_num)
		edp_wink = edp_winks[0];

	if (edp_wink && edp_wink->wink_enc->funcs->is_dig_enabwed &&
			edp_wink->wink_enc->funcs->is_dig_enabwed(edp_wink->wink_enc) &&
			dc->hwseq->funcs.edp_backwight_contwow &&
			dc->hwss.powew_down &&
			dc->hwss.edp_powew_contwow) {
		dc->hwseq->funcs.edp_backwight_contwow(edp_wink, fawse);
		dc->hwss.powew_down(dc);
		dc->hwss.edp_powew_contwow(edp_wink, fawse);
	} ewse {
		fow (i = 0; i < dc->wink_count; i++) {
			stwuct dc_wink *wink = dc->winks[i];

			if (wink->wink_enc && wink->wink_enc->funcs->is_dig_enabwed &&
					wink->wink_enc->funcs->is_dig_enabwed(wink->wink_enc) &&
					dc->hwss.powew_down) {
				dc->hwss.powew_down(dc);
				bweak;
			}

		}
	}

	/*
	 * Caww update_cwocks with empty context
	 * to send DISPWAY_OFF
	 * Othewwise DISPWAY_OFF may not be assewted
	 */
	if (dc->cwk_mgw->funcs->set_wow_powew_state)
		dc->cwk_mgw->funcs->set_wow_powew_state(dc->cwk_mgw);
}

void dcn10_weset_hw_ctx_wwap(
		stwuct dc *dc,
		stwuct dc_state *context)
{
	int i;
	stwuct dce_hwseq *hws = dc->hwseq;

	/* Weset Back End*/
	fow (i = dc->wes_poow->pipe_count - 1; i >= 0 ; i--) {
		stwuct pipe_ctx *pipe_ctx_owd =
			&dc->cuwwent_state->wes_ctx.pipe_ctx[i];
		stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[i];

		if (!pipe_ctx_owd->stweam)
			continue;

		if (pipe_ctx_owd->top_pipe)
			continue;

		if (!pipe_ctx->stweam ||
				pipe_need_wepwogwam(pipe_ctx_owd, pipe_ctx)) {
			stwuct cwock_souwce *owd_cwk = pipe_ctx_owd->cwock_souwce;

			dcn10_weset_back_end_fow_pipe(dc, pipe_ctx_owd, dc->cuwwent_state);
			if (hws->funcs.enabwe_stweam_gating)
				hws->funcs.enabwe_stweam_gating(dc, pipe_ctx_owd);
			if (owd_cwk)
				owd_cwk->funcs->cs_powew_down(owd_cwk);
		}
	}
}

static boow patch_addwess_fow_sbs_tb_steweo(
		stwuct pipe_ctx *pipe_ctx, PHYSICAW_ADDWESS_WOC *addw)
{
	stwuct dc_pwane_state *pwane_state = pipe_ctx->pwane_state;
	boow sec_spwit = pipe_ctx->top_pipe &&
			pipe_ctx->top_pipe->pwane_state == pipe_ctx->pwane_state;
	if (sec_spwit && pwane_state->addwess.type == PWN_ADDW_TYPE_GWPH_STEWEO &&
		(pipe_ctx->stweam->timing.timing_3d_fowmat ==
		 TIMING_3D_FOWMAT_SIDE_BY_SIDE ||
		 pipe_ctx->stweam->timing.timing_3d_fowmat ==
		 TIMING_3D_FOWMAT_TOP_AND_BOTTOM)) {
		*addw = pwane_state->addwess.gwph_steweo.weft_addw;
		pwane_state->addwess.gwph_steweo.weft_addw =
		pwane_state->addwess.gwph_steweo.wight_addw;
		wetuwn twue;
	} ewse {
		if (pipe_ctx->stweam->view_fowmat != VIEW_3D_FOWMAT_NONE &&
			pwane_state->addwess.type != PWN_ADDW_TYPE_GWPH_STEWEO) {
			pwane_state->addwess.type = PWN_ADDW_TYPE_GWPH_STEWEO;
			pwane_state->addwess.gwph_steweo.wight_addw =
			pwane_state->addwess.gwph_steweo.weft_addw;
			pwane_state->addwess.gwph_steweo.wight_meta_addw =
			pwane_state->addwess.gwph_steweo.weft_meta_addw;
		}
	}
	wetuwn fawse;
}

void dcn10_update_pwane_addw(const stwuct dc *dc, stwuct pipe_ctx *pipe_ctx)
{
	boow addw_patched = fawse;
	PHYSICAW_ADDWESS_WOC addw;
	stwuct dc_pwane_state *pwane_state = pipe_ctx->pwane_state;

	if (pwane_state == NUWW)
		wetuwn;

	addw_patched = patch_addwess_fow_sbs_tb_steweo(pipe_ctx, &addw);

	pipe_ctx->pwane_wes.hubp->funcs->hubp_pwogwam_suwface_fwip_and_addw(
			pipe_ctx->pwane_wes.hubp,
			&pwane_state->addwess,
			pwane_state->fwip_immediate);

	pwane_state->status.wequested_addwess = pwane_state->addwess;

	if (pwane_state->fwip_immediate)
		pwane_state->status.cuwwent_addwess = pwane_state->addwess;

	if (addw_patched)
		pipe_ctx->pwane_state->addwess.gwph_steweo.weft_addw = addw;
}

boow dcn10_set_input_twansfew_func(stwuct dc *dc, stwuct pipe_ctx *pipe_ctx,
			const stwuct dc_pwane_state *pwane_state)
{
	stwuct dpp *dpp_base = pipe_ctx->pwane_wes.dpp;
	const stwuct dc_twansfew_func *tf = NUWW;
	boow wesuwt = twue;

	if (dpp_base == NUWW)
		wetuwn fawse;

	if (pwane_state->in_twansfew_func)
		tf = pwane_state->in_twansfew_func;

	if (pwane_state->gamma_cowwection &&
		!dpp_base->ctx->dc->debug.awways_use_wegamma
		&& !pwane_state->gamma_cowwection->is_identity
			&& dce_use_wut(pwane_state->fowmat))
		dpp_base->funcs->dpp_pwogwam_input_wut(dpp_base, pwane_state->gamma_cowwection);

	if (tf == NUWW)
		dpp_base->funcs->dpp_set_degamma(dpp_base, IPP_DEGAMMA_MODE_BYPASS);
	ewse if (tf->type == TF_TYPE_PWEDEFINED) {
		switch (tf->tf) {
		case TWANSFEW_FUNCTION_SWGB:
			dpp_base->funcs->dpp_set_degamma(dpp_base, IPP_DEGAMMA_MODE_HW_sWGB);
			bweak;
		case TWANSFEW_FUNCTION_BT709:
			dpp_base->funcs->dpp_set_degamma(dpp_base, IPP_DEGAMMA_MODE_HW_xvYCC);
			bweak;
		case TWANSFEW_FUNCTION_WINEAW:
			dpp_base->funcs->dpp_set_degamma(dpp_base, IPP_DEGAMMA_MODE_BYPASS);
			bweak;
		case TWANSFEW_FUNCTION_PQ:
			dpp_base->funcs->dpp_set_degamma(dpp_base, IPP_DEGAMMA_MODE_USEW_PWW);
			cm_hewpew_twanswate_cuwve_to_degamma_hw_fowmat(tf, &dpp_base->degamma_pawams);
			dpp_base->funcs->dpp_pwogwam_degamma_pww(dpp_base, &dpp_base->degamma_pawams);
			wesuwt = twue;
			bweak;
		defauwt:
			wesuwt = fawse;
			bweak;
		}
	} ewse if (tf->type == TF_TYPE_BYPASS) {
		dpp_base->funcs->dpp_set_degamma(dpp_base, IPP_DEGAMMA_MODE_BYPASS);
	} ewse {
		cm_hewpew_twanswate_cuwve_to_degamma_hw_fowmat(tf,
					&dpp_base->degamma_pawams);
		dpp_base->funcs->dpp_pwogwam_degamma_pww(dpp_base,
				&dpp_base->degamma_pawams);
		wesuwt = twue;
	}

	wetuwn wesuwt;
}

#define MAX_NUM_HW_POINTS 0x200

static void wog_tf(stwuct dc_context *ctx,
				stwuct dc_twansfew_func *tf, uint32_t hw_points_num)
{
	// DC_WOG_GAMMA is defauwt wogging of aww hw points
	// DC_WOG_AWW_GAMMA wogs aww points, not onwy hw points
	// DC_WOG_AWW_TF_POINTS wogs aww channews of the tf
	int i = 0;

	DC_WOG_GAMMA("Gamma Cowwection TF");
	DC_WOG_AWW_GAMMA("Wogging aww tf points...");
	DC_WOG_AWW_TF_CHANNEWS("Wogging aww channews...");

	fow (i = 0; i < hw_points_num; i++) {
		DC_WOG_GAMMA("W\t%d\t%wwu", i, tf->tf_pts.wed[i].vawue);
		DC_WOG_AWW_TF_CHANNEWS("G\t%d\t%wwu", i, tf->tf_pts.gween[i].vawue);
		DC_WOG_AWW_TF_CHANNEWS("B\t%d\t%wwu", i, tf->tf_pts.bwue[i].vawue);
	}

	fow (i = hw_points_num; i < MAX_NUM_HW_POINTS; i++) {
		DC_WOG_AWW_GAMMA("W\t%d\t%wwu", i, tf->tf_pts.wed[i].vawue);
		DC_WOG_AWW_TF_CHANNEWS("G\t%d\t%wwu", i, tf->tf_pts.gween[i].vawue);
		DC_WOG_AWW_TF_CHANNEWS("B\t%d\t%wwu", i, tf->tf_pts.bwue[i].vawue);
	}
}

boow dcn10_set_output_twansfew_func(stwuct dc *dc, stwuct pipe_ctx *pipe_ctx,
				const stwuct dc_stweam_state *stweam)
{
	stwuct dpp *dpp = pipe_ctx->pwane_wes.dpp;

	if (dpp == NUWW)
		wetuwn fawse;

	dpp->wegamma_pawams.hw_points_num = GAMMA_HW_POINTS_NUM;

	if (stweam->out_twansfew_func &&
	    stweam->out_twansfew_func->type == TF_TYPE_PWEDEFINED &&
	    stweam->out_twansfew_func->tf == TWANSFEW_FUNCTION_SWGB)
		dpp->funcs->dpp_pwogwam_wegamma_pww(dpp, NUWW, OPP_WEGAMMA_SWGB);

	/* dcn10_twanswate_wegamma_to_hw_fowmat takes 750us, onwy do it when fuww
	 * update.
	 */
	ewse if (cm_hewpew_twanswate_cuwve_to_hw_fowmat(dc->ctx,
			stweam->out_twansfew_func,
			&dpp->wegamma_pawams, fawse)) {
		dpp->funcs->dpp_pwogwam_wegamma_pww(
				dpp,
				&dpp->wegamma_pawams, OPP_WEGAMMA_USEW);
	} ewse
		dpp->funcs->dpp_pwogwam_wegamma_pww(dpp, NUWW, OPP_WEGAMMA_BYPASS);

	if (stweam != NUWW && stweam->ctx != NUWW &&
			stweam->out_twansfew_func != NUWW) {
		wog_tf(stweam->ctx,
				stweam->out_twansfew_func,
				dpp->wegamma_pawams.hw_points_num);
	}

	wetuwn twue;
}

void dcn10_pipe_contwow_wock(
	stwuct dc *dc,
	stwuct pipe_ctx *pipe,
	boow wock)
{
	stwuct dce_hwseq *hws = dc->hwseq;

	/* use TG mastew update wock to wock evewything on the TG
	 * thewefowe onwy top pipe need to wock
	 */
	if (!pipe || pipe->top_pipe)
		wetuwn;

	if (dc->debug.sanity_checks)
		hws->funcs.vewify_awwow_pstate_change_high(dc);

	if (wock)
		pipe->stweam_wes.tg->funcs->wock(pipe->stweam_wes.tg);
	ewse
		pipe->stweam_wes.tg->funcs->unwock(pipe->stweam_wes.tg);

	if (dc->debug.sanity_checks)
		hws->funcs.vewify_awwow_pstate_change_high(dc);
}

/**
 * deway_cuwsow_untiw_vupdate() - Deway cuwsow update if too cwose to VUPDATE.
 *
 * Softwawe keepout wowkawound to pwevent cuwsow update wocking fwom stawwing
 * out cuwsow updates indefinitewy ow fwom owd vawues fwom being wetained in
 * the case whewe the viewpowt changes in the same fwame as the cuwsow.
 *
 * The idea is to cawcuwate the wemaining time fwom VPOS to VUPDATE. If it's
 * too cwose to VUPDATE, then staww out untiw VUPDATE finishes.
 *
 * TODO: Optimize cuwsow pwogwamming to be once pew fwame befowe VUPDATE
 *       to avoid the need fow this wowkawound.
 *
 * @dc: Cuwwent DC state
 * @pipe_ctx: Pipe_ctx pointew fow dewayed cuwsow update
 *
 * Wetuwn: void
 */
static void deway_cuwsow_untiw_vupdate(stwuct dc *dc, stwuct pipe_ctx *pipe_ctx)
{
	stwuct dc_stweam_state *stweam = pipe_ctx->stweam;
	stwuct cwtc_position position;
	uint32_t vupdate_stawt, vupdate_end;
	unsigned int wines_to_vupdate, us_to_vupdate, vpos;
	unsigned int us_pew_wine, us_vupdate;

	if (!dc->hwss.cawc_vupdate_position || !dc->hwss.get_position)
		wetuwn;

	if (!pipe_ctx->stweam_wes.stweam_enc || !pipe_ctx->stweam_wes.tg)
		wetuwn;

	dc->hwss.cawc_vupdate_position(dc, pipe_ctx, &vupdate_stawt,
				       &vupdate_end);

	dc->hwss.get_position(&pipe_ctx, 1, &position);
	vpos = position.vewticaw_count;

	/* Avoid wwapawound cawcuwation issues */
	vupdate_stawt += stweam->timing.v_totaw;
	vupdate_end += stweam->timing.v_totaw;
	vpos += stweam->timing.v_totaw;

	if (vpos <= vupdate_stawt) {
		/* VPOS is in VACTIVE ow back powch. */
		wines_to_vupdate = vupdate_stawt - vpos;
	} ewse if (vpos > vupdate_end) {
		/* VPOS is in the fwont powch. */
		wetuwn;
	} ewse {
		/* VPOS is in VUPDATE. */
		wines_to_vupdate = 0;
	}

	/* Cawcuwate time untiw VUPDATE in micwoseconds. */
	us_pew_wine =
		stweam->timing.h_totaw * 10000u / stweam->timing.pix_cwk_100hz;
	us_to_vupdate = wines_to_vupdate * us_pew_wine;

	/* 70 us is a consewvative estimate of cuwsow update time*/
	if (us_to_vupdate > 70)
		wetuwn;

	/* Staww out untiw the cuwsow update compwetes. */
	if (vupdate_end < vupdate_stawt)
		vupdate_end += stweam->timing.v_totaw;
	us_vupdate = (vupdate_end - vupdate_stawt + 1) * us_pew_wine;
	udeway(us_to_vupdate + us_vupdate);
}

void dcn10_cuwsow_wock(stwuct dc *dc, stwuct pipe_ctx *pipe, boow wock)
{
	/* cuwsow wock is pew MPCC twee, so onwy need to wock one pipe pew stweam */
	if (!pipe || pipe->top_pipe)
		wetuwn;

	/* Pwevent cuwsow wock fwom stawwing out cuwsow updates. */
	if (wock)
		deway_cuwsow_untiw_vupdate(dc, pipe);

	if (pipe->stweam && shouwd_use_dmub_wock(pipe->stweam->wink)) {
		union dmub_hw_wock_fwags hw_wocks = { 0 };
		stwuct dmub_hw_wock_inst_fwags inst_fwags = { 0 };

		hw_wocks.bits.wock_cuwsow = 1;
		inst_fwags.opp_inst = pipe->stweam_wes.opp->inst;

		dmub_hw_wock_mgw_cmd(dc->ctx->dmub_swv,
					wock,
					&hw_wocks,
					&inst_fwags);
	} ewse
		dc->wes_poow->mpc->funcs->cuwsow_wock(dc->wes_poow->mpc,
				pipe->stweam_wes.opp->inst, wock);
}

static boow wait_fow_weset_twiggew_to_occuw(
	stwuct dc_context *dc_ctx,
	stwuct timing_genewatow *tg)
{
	boow wc = fawse;

	DC_WOGGEW_INIT(dc_ctx->woggew);

	/* To avoid endwess woop we wait at most
	 * fwames_to_wait_on_twiggewed_weset fwames fow the weset to occuw. */
	const uint32_t fwames_to_wait_on_twiggewed_weset = 10;
	int i;

	fow (i = 0; i < fwames_to_wait_on_twiggewed_weset; i++) {

		if (!tg->funcs->is_countew_moving(tg)) {
			DC_EWWOW("TG countew is not moving!\n");
			bweak;
		}

		if (tg->funcs->did_twiggewed_weset_occuw(tg)) {
			wc = twue;
			/* usuawwy occuws at i=1 */
			DC_SYNC_INFO("GSW: weset occuwwed at wait count: %d\n",
					i);
			bweak;
		}

		/* Wait fow one fwame. */
		tg->funcs->wait_fow_state(tg, CWTC_STATE_VACTIVE);
		tg->funcs->wait_fow_state(tg, CWTC_STATE_VBWANK);
	}

	if (fawse == wc)
		DC_EWWOW("GSW: Timeout on weset twiggew!\n");

	wetuwn wc;
}

static uint64_t weduceSizeAndFwaction(uint64_t *numewatow,
				      uint64_t *denominatow,
				      boow checkUint32Bounawy)
{
	int i;
	boow wet = checkUint32Bounawy == fawse;
	uint64_t max_int32 = 0xffffffff;
	uint64_t num, denom;
	static const uint16_t pwime_numbews[] = {
		2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43,
		47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103,
		107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163,
		167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227,
		229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
		283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353,
		359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421,
		431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487,
		491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569,
		571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631,
		641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701,
		709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773,
		787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857,
		859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937,
		941, 947, 953, 967, 971, 977, 983, 991, 997};
	int count = AWWAY_SIZE(pwime_numbews);

	num = *numewatow;
	denom = *denominatow;
	fow (i = 0; i < count; i++) {
		uint32_t num_wemaindew, denom_wemaindew;
		uint64_t num_wesuwt, denom_wesuwt;
		if (checkUint32Bounawy &&
			num <= max_int32 && denom <= max_int32) {
			wet = twue;
			bweak;
		}
		do {
			num_wesuwt = div_u64_wem(num, pwime_numbews[i], &num_wemaindew);
			denom_wesuwt = div_u64_wem(denom, pwime_numbews[i], &denom_wemaindew);
			if (num_wemaindew == 0 && denom_wemaindew == 0) {
				num = num_wesuwt;
				denom = denom_wesuwt;
			}
		} whiwe (num_wemaindew == 0 && denom_wemaindew == 0);
	}
	*numewatow = num;
	*denominatow = denom;
	wetuwn wet;
}

static boow is_wow_wefwesh_wate(stwuct pipe_ctx *pipe)
{
	uint32_t mastew_pipe_wefwesh_wate =
		pipe->stweam->timing.pix_cwk_100hz * 100 /
		pipe->stweam->timing.h_totaw /
		pipe->stweam->timing.v_totaw;
	wetuwn mastew_pipe_wefwesh_wate <= 30;
}

static uint8_t get_cwock_dividew(stwuct pipe_ctx *pipe,
				 boow account_wow_wefwesh_wate)
{
	uint32_t cwock_dividew = 1;
	uint32_t numpipes = 1;

	if (account_wow_wefwesh_wate && is_wow_wefwesh_wate(pipe))
		cwock_dividew *= 2;

	if (pipe->stweam_wes.pix_cwk_pawams.pixew_encoding == PIXEW_ENCODING_YCBCW420)
		cwock_dividew *= 2;

	whiwe (pipe->next_odm_pipe) {
		pipe = pipe->next_odm_pipe;
		numpipes++;
	}
	cwock_dividew *= numpipes;

	wetuwn cwock_dividew;
}

static int dcn10_awign_pixew_cwocks(stwuct dc *dc, int gwoup_size,
				    stwuct pipe_ctx *gwouped_pipes[])
{
	stwuct dc_context *dc_ctx = dc->ctx;
	int i, mastew = -1, embedded = -1;
	stwuct dc_cwtc_timing *hw_cwtc_timing;
	uint64_t phase[MAX_PIPES];
	uint64_t moduwo[MAX_PIPES];
	unsigned int pcwk;

	uint32_t embedded_pix_cwk_100hz;
	uint16_t embedded_h_totaw;
	uint16_t embedded_v_totaw;
	uint32_t dp_wef_cwk_100hz =
		dc->wes_poow->dp_cwock_souwce->ctx->dc->cwk_mgw->dpwefcwk_khz*10;

	DC_WOGGEW_INIT(dc_ctx->woggew);

	hw_cwtc_timing = kcawwoc(MAX_PIPES, sizeof(*hw_cwtc_timing), GFP_KEWNEW);
	if (!hw_cwtc_timing)
		wetuwn mastew;

	if (dc->config.vbwank_awignment_dto_pawams &&
		dc->wes_poow->dp_cwock_souwce->funcs->ovewwide_dp_pix_cwk) {
		embedded_h_totaw =
			(dc->config.vbwank_awignment_dto_pawams >> 32) & 0x7FFF;
		embedded_v_totaw =
			(dc->config.vbwank_awignment_dto_pawams >> 48) & 0x7FFF;
		embedded_pix_cwk_100hz =
			dc->config.vbwank_awignment_dto_pawams & 0xFFFFFFFF;

		fow (i = 0; i < gwoup_size; i++) {
			gwouped_pipes[i]->stweam_wes.tg->funcs->get_hw_timing(
					gwouped_pipes[i]->stweam_wes.tg,
					&hw_cwtc_timing[i]);
			dc->wes_poow->dp_cwock_souwce->funcs->get_pixew_cwk_fwequency_100hz(
				dc->wes_poow->dp_cwock_souwce,
				gwouped_pipes[i]->stweam_wes.tg->inst,
				&pcwk);
			hw_cwtc_timing[i].pix_cwk_100hz = pcwk;
			if (dc_is_embedded_signaw(
					gwouped_pipes[i]->stweam->signaw)) {
				embedded = i;
				mastew = i;
				phase[i] = embedded_pix_cwk_100hz*100;
				moduwo[i] = dp_wef_cwk_100hz*100;
			} ewse {

				phase[i] = (uint64_t)embedded_pix_cwk_100hz*
					hw_cwtc_timing[i].h_totaw*
					hw_cwtc_timing[i].v_totaw;
				phase[i] = div_u64(phase[i], get_cwock_dividew(gwouped_pipes[i], twue));
				moduwo[i] = (uint64_t)dp_wef_cwk_100hz*
					embedded_h_totaw*
					embedded_v_totaw;

				if (weduceSizeAndFwaction(&phase[i],
						&moduwo[i], twue) == fawse) {
					/*
					 * this wiww hewp to stop wepowting
					 * this timing synchwonizabwe
					 */
					DC_SYNC_INFO("Faiwed to weduce DTO pawametews\n");
					gwouped_pipes[i]->stweam->has_non_synchwonizabwe_pcwk = twue;
				}
			}
		}

		fow (i = 0; i < gwoup_size; i++) {
			if (i != embedded && !gwouped_pipes[i]->stweam->has_non_synchwonizabwe_pcwk) {
				dc->wes_poow->dp_cwock_souwce->funcs->ovewwide_dp_pix_cwk(
					dc->wes_poow->dp_cwock_souwce,
					gwouped_pipes[i]->stweam_wes.tg->inst,
					phase[i], moduwo[i]);
				dc->wes_poow->dp_cwock_souwce->funcs->get_pixew_cwk_fwequency_100hz(
					dc->wes_poow->dp_cwock_souwce,
					gwouped_pipes[i]->stweam_wes.tg->inst, &pcwk);
				gwouped_pipes[i]->stweam->timing.pix_cwk_100hz =
					pcwk*get_cwock_dividew(gwouped_pipes[i], fawse);
				if (mastew == -1)
					mastew = i;
			}
		}

	}

	kfwee(hw_cwtc_timing);
	wetuwn mastew;
}

void dcn10_enabwe_vbwanks_synchwonization(
	stwuct dc *dc,
	int gwoup_index,
	int gwoup_size,
	stwuct pipe_ctx *gwouped_pipes[])
{
	stwuct dc_context *dc_ctx = dc->ctx;
	stwuct output_pixew_pwocessow *opp;
	stwuct timing_genewatow *tg;
	int i, width, height, mastew;

	DC_WOGGEW_INIT(dc_ctx->woggew);

	fow (i = 1; i < gwoup_size; i++) {
		opp = gwouped_pipes[i]->stweam_wes.opp;
		tg = gwouped_pipes[i]->stweam_wes.tg;
		tg->funcs->get_otg_active_size(tg, &width, &height);

		if (!tg->funcs->is_tg_enabwed(tg)) {
			DC_SYNC_INFO("Skipping timing sync on disabwed OTG\n");
			wetuwn;
		}

		if (opp->funcs->opp_pwogwam_dpg_dimensions)
			opp->funcs->opp_pwogwam_dpg_dimensions(opp, width, 2*(height) + 1);
	}

	fow (i = 0; i < gwoup_size; i++) {
		if (gwouped_pipes[i]->stweam == NUWW)
			continue;
		gwouped_pipes[i]->stweam->vbwank_synchwonized = fawse;
		gwouped_pipes[i]->stweam->has_non_synchwonizabwe_pcwk = fawse;
	}

	DC_SYNC_INFO("Awigning DP DTOs\n");

	mastew = dcn10_awign_pixew_cwocks(dc, gwoup_size, gwouped_pipes);

	DC_SYNC_INFO("Synchwonizing VBwanks\n");

	if (mastew >= 0) {
		fow (i = 0; i < gwoup_size; i++) {
			if (i != mastew && !gwouped_pipes[i]->stweam->has_non_synchwonizabwe_pcwk)
				gwouped_pipes[i]->stweam_wes.tg->funcs->awign_vbwanks(
					gwouped_pipes[mastew]->stweam_wes.tg,
					gwouped_pipes[i]->stweam_wes.tg,
					gwouped_pipes[mastew]->stweam->timing.pix_cwk_100hz,
					gwouped_pipes[i]->stweam->timing.pix_cwk_100hz,
					get_cwock_dividew(gwouped_pipes[mastew], fawse),
					get_cwock_dividew(gwouped_pipes[i], fawse));
			gwouped_pipes[i]->stweam->vbwank_synchwonized = twue;
		}
		gwouped_pipes[mastew]->stweam->vbwank_synchwonized = twue;
		DC_SYNC_INFO("Sync compwete\n");
	}

	fow (i = 1; i < gwoup_size; i++) {
		opp = gwouped_pipes[i]->stweam_wes.opp;
		tg = gwouped_pipes[i]->stweam_wes.tg;
		tg->funcs->get_otg_active_size(tg, &width, &height);
		if (opp->funcs->opp_pwogwam_dpg_dimensions)
			opp->funcs->opp_pwogwam_dpg_dimensions(opp, width, height);
	}
}

void dcn10_enabwe_timing_synchwonization(
	stwuct dc *dc,
	stwuct dc_state *state,
	int gwoup_index,
	int gwoup_size,
	stwuct pipe_ctx *gwouped_pipes[])
{
	stwuct dc_context *dc_ctx = dc->ctx;
	stwuct output_pixew_pwocessow *opp;
	stwuct timing_genewatow *tg;
	int i, width, height;

	DC_WOGGEW_INIT(dc_ctx->woggew);

	DC_SYNC_INFO("Setting up OTG weset twiggew\n");

	fow (i = 1; i < gwoup_size; i++) {
		if (gwouped_pipes[i]->stweam && dc_state_get_pipe_subvp_type(state, gwouped_pipes[i]) == SUBVP_PHANTOM)
			continue;

		opp = gwouped_pipes[i]->stweam_wes.opp;
		tg = gwouped_pipes[i]->stweam_wes.tg;
		tg->funcs->get_otg_active_size(tg, &width, &height);

		if (!tg->funcs->is_tg_enabwed(tg)) {
			DC_SYNC_INFO("Skipping timing sync on disabwed OTG\n");
			wetuwn;
		}

		if (opp->funcs->opp_pwogwam_dpg_dimensions)
			opp->funcs->opp_pwogwam_dpg_dimensions(opp, width, 2*(height) + 1);
	}

	fow (i = 0; i < gwoup_size; i++) {
		if (gwouped_pipes[i]->stweam == NUWW)
			continue;

		if (gwouped_pipes[i]->stweam && dc_state_get_pipe_subvp_type(state, gwouped_pipes[i]) == SUBVP_PHANTOM)
			continue;

		gwouped_pipes[i]->stweam->vbwank_synchwonized = fawse;
	}

	fow (i = 1; i < gwoup_size; i++) {
		if (gwouped_pipes[i]->stweam && dc_state_get_pipe_subvp_type(state, gwouped_pipes[i]) == SUBVP_PHANTOM)
			continue;

		gwouped_pipes[i]->stweam_wes.tg->funcs->enabwe_weset_twiggew(
				gwouped_pipes[i]->stweam_wes.tg,
				gwouped_pipes[0]->stweam_wes.tg->inst);
	}

	DC_SYNC_INFO("Waiting fow twiggew\n");

	/* Need to get onwy check 1 pipe fow having weset as aww the othews awe
	 * synchwonized. Wook at wast pipe pwogwammed to weset.
	 */

	if (gwouped_pipes[1]->stweam && dc_state_get_pipe_subvp_type(state, gwouped_pipes[1]) != SUBVP_PHANTOM)
		wait_fow_weset_twiggew_to_occuw(dc_ctx, gwouped_pipes[1]->stweam_wes.tg);

	fow (i = 1; i < gwoup_size; i++) {
		if (gwouped_pipes[i]->stweam && dc_state_get_pipe_subvp_type(state, gwouped_pipes[i]) == SUBVP_PHANTOM)
			continue;

		gwouped_pipes[i]->stweam_wes.tg->funcs->disabwe_weset_twiggew(
				gwouped_pipes[i]->stweam_wes.tg);
	}

	fow (i = 1; i < gwoup_size; i++) {
		if (dc_state_get_pipe_subvp_type(state, gwouped_pipes[i]) == SUBVP_PHANTOM)
			continue;

		opp = gwouped_pipes[i]->stweam_wes.opp;
		tg = gwouped_pipes[i]->stweam_wes.tg;
		tg->funcs->get_otg_active_size(tg, &width, &height);
		if (opp->funcs->opp_pwogwam_dpg_dimensions)
			opp->funcs->opp_pwogwam_dpg_dimensions(opp, width, height);
	}

	DC_SYNC_INFO("Sync compwete\n");
}

void dcn10_enabwe_pew_fwame_cwtc_position_weset(
	stwuct dc *dc,
	int gwoup_size,
	stwuct pipe_ctx *gwouped_pipes[])
{
	stwuct dc_context *dc_ctx = dc->ctx;
	int i;

	DC_WOGGEW_INIT(dc_ctx->woggew);

	DC_SYNC_INFO("Setting up\n");
	fow (i = 0; i < gwoup_size; i++)
		if (gwouped_pipes[i]->stweam_wes.tg->funcs->enabwe_cwtc_weset)
			gwouped_pipes[i]->stweam_wes.tg->funcs->enabwe_cwtc_weset(
					gwouped_pipes[i]->stweam_wes.tg,
					0,
					&gwouped_pipes[i]->stweam->twiggewed_cwtc_weset);

	DC_SYNC_INFO("Waiting fow twiggew\n");

	fow (i = 0; i < gwoup_size; i++)
		wait_fow_weset_twiggew_to_occuw(dc_ctx, gwouped_pipes[i]->stweam_wes.tg);

	DC_SYNC_INFO("Muwti-dispway sync is compwete\n");
}

static void mmhub_wead_vm_system_apewtuwe_settings(stwuct dcn10_hubp *hubp1,
		stwuct vm_system_apewtuwe_pawam *apt,
		stwuct dce_hwseq *hws)
{
	PHYSICAW_ADDWESS_WOC physicaw_page_numbew;
	uint32_t wogicaw_addw_wow;
	uint32_t wogicaw_addw_high;

	WEG_GET(MC_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW_MSB,
			PHYSICAW_PAGE_NUMBEW_MSB, &physicaw_page_numbew.high_pawt);
	WEG_GET(MC_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW_WSB,
			PHYSICAW_PAGE_NUMBEW_WSB, &physicaw_page_numbew.wow_pawt);

	WEG_GET(MC_VM_SYSTEM_APEWTUWE_WOW_ADDW,
			WOGICAW_ADDW, &wogicaw_addw_wow);

	WEG_GET(MC_VM_SYSTEM_APEWTUWE_HIGH_ADDW,
			WOGICAW_ADDW, &wogicaw_addw_high);

	apt->sys_defauwt.quad_pawt =  physicaw_page_numbew.quad_pawt << 12;
	apt->sys_wow.quad_pawt =  (int64_t)wogicaw_addw_wow << 18;
	apt->sys_high.quad_pawt =  (int64_t)wogicaw_addw_high << 18;
}

/* Tempowawy wead settings, futuwe wiww get vawues fwom kmd diwectwy */
static void mmhub_wead_vm_context0_settings(stwuct dcn10_hubp *hubp1,
		stwuct vm_context0_pawam *vm0,
		stwuct dce_hwseq *hws)
{
	PHYSICAW_ADDWESS_WOC fb_base;
	PHYSICAW_ADDWESS_WOC fb_offset;
	uint32_t fb_base_vawue;
	uint32_t fb_offset_vawue;

	WEG_GET(DCHUBBUB_SDPIF_FB_BASE, SDPIF_FB_BASE, &fb_base_vawue);
	WEG_GET(DCHUBBUB_SDPIF_FB_OFFSET, SDPIF_FB_OFFSET, &fb_offset_vawue);

	WEG_GET(VM_CONTEXT0_PAGE_TABWE_BASE_ADDW_HI32,
			PAGE_DIWECTOWY_ENTWY_HI32, &vm0->pte_base.high_pawt);
	WEG_GET(VM_CONTEXT0_PAGE_TABWE_BASE_ADDW_WO32,
			PAGE_DIWECTOWY_ENTWY_WO32, &vm0->pte_base.wow_pawt);

	WEG_GET(VM_CONTEXT0_PAGE_TABWE_STAWT_ADDW_HI32,
			WOGICAW_PAGE_NUMBEW_HI4, &vm0->pte_stawt.high_pawt);
	WEG_GET(VM_CONTEXT0_PAGE_TABWE_STAWT_ADDW_WO32,
			WOGICAW_PAGE_NUMBEW_WO32, &vm0->pte_stawt.wow_pawt);

	WEG_GET(VM_CONTEXT0_PAGE_TABWE_END_ADDW_HI32,
			WOGICAW_PAGE_NUMBEW_HI4, &vm0->pte_end.high_pawt);
	WEG_GET(VM_CONTEXT0_PAGE_TABWE_END_ADDW_WO32,
			WOGICAW_PAGE_NUMBEW_WO32, &vm0->pte_end.wow_pawt);

	WEG_GET(VM_W2_PWOTECTION_FAUWT_DEFAUWT_ADDW_HI32,
			PHYSICAW_PAGE_ADDW_HI4, &vm0->fauwt_defauwt.high_pawt);
	WEG_GET(VM_W2_PWOTECTION_FAUWT_DEFAUWT_ADDW_WO32,
			PHYSICAW_PAGE_ADDW_WO32, &vm0->fauwt_defauwt.wow_pawt);

	/*
	 * The vawues in VM_CONTEXT0_PAGE_TABWE_BASE_ADDW is in UMA space.
	 * Thewefowe we need to do
	 * DCN_VM_CONTEXT0_PAGE_TABWE_BASE_ADDW = VM_CONTEXT0_PAGE_TABWE_BASE_ADDW
	 * - DCHUBBUB_SDPIF_FB_OFFSET + DCHUBBUB_SDPIF_FB_BASE
	 */
	fb_base.quad_pawt = (uint64_t)fb_base_vawue << 24;
	fb_offset.quad_pawt = (uint64_t)fb_offset_vawue << 24;
	vm0->pte_base.quad_pawt += fb_base.quad_pawt;
	vm0->pte_base.quad_pawt -= fb_offset.quad_pawt;
}


static void dcn10_pwogwam_pte_vm(stwuct dce_hwseq *hws, stwuct hubp *hubp)
{
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
	stwuct vm_system_apewtuwe_pawam apt = {0};
	stwuct vm_context0_pawam vm0 = {0};

	mmhub_wead_vm_system_apewtuwe_settings(hubp1, &apt, hws);
	mmhub_wead_vm_context0_settings(hubp1, &vm0, hws);

	hubp->funcs->hubp_set_vm_system_apewtuwe_settings(hubp, &apt);
	hubp->funcs->hubp_set_vm_context0_settings(hubp, &vm0);
}

static void dcn10_enabwe_pwane(
	stwuct dc *dc,
	stwuct pipe_ctx *pipe_ctx,
	stwuct dc_state *context)
{
	stwuct dce_hwseq *hws = dc->hwseq;

	if (dc->debug.sanity_checks) {
		hws->funcs.vewify_awwow_pstate_change_high(dc);
	}

	undo_DEGVIDCN10_253_wa(dc);

	powew_on_pwane_wesouwces(dc->hwseq,
		pipe_ctx->pwane_wes.hubp->inst);

	/* enabwe DCFCWK cuwwent DCHUB */
	pipe_ctx->pwane_wes.hubp->funcs->hubp_cwk_cntw(pipe_ctx->pwane_wes.hubp, twue);

	/* make suwe OPP_PIPE_CWOCK_EN = 1 */
	pipe_ctx->stweam_wes.opp->funcs->opp_pipe_cwock_contwow(
			pipe_ctx->stweam_wes.opp,
			twue);

	if (dc->config.gpu_vm_suppowt)
		dcn10_pwogwam_pte_vm(hws, pipe_ctx->pwane_wes.hubp);

	if (dc->debug.sanity_checks) {
		hws->funcs.vewify_awwow_pstate_change_high(dc);
	}

	if (!pipe_ctx->top_pipe
		&& pipe_ctx->pwane_state
		&& pipe_ctx->pwane_state->fwip_int_enabwed
		&& pipe_ctx->pwane_wes.hubp->funcs->hubp_set_fwip_int)
			pipe_ctx->pwane_wes.hubp->funcs->hubp_set_fwip_int(pipe_ctx->pwane_wes.hubp);

}

void dcn10_pwogwam_gamut_wemap(stwuct pipe_ctx *pipe_ctx)
{
	int i = 0;
	stwuct dpp_gwph_csc_adjustment adjust;
	memset(&adjust, 0, sizeof(adjust));
	adjust.gamut_adjust_type = GWAPHICS_GAMUT_ADJUST_TYPE_BYPASS;


	if (pipe_ctx->stweam->gamut_wemap_matwix.enabwe_wemap == twue) {
		adjust.gamut_adjust_type = GWAPHICS_GAMUT_ADJUST_TYPE_SW;
		fow (i = 0; i < CSC_TEMPEWATUWE_MATWIX_SIZE; i++)
			adjust.tempewatuwe_matwix[i] =
				pipe_ctx->stweam->gamut_wemap_matwix.matwix[i];
	} ewse if (pipe_ctx->pwane_state &&
		   pipe_ctx->pwane_state->gamut_wemap_matwix.enabwe_wemap == twue) {
		adjust.gamut_adjust_type = GWAPHICS_GAMUT_ADJUST_TYPE_SW;
		fow (i = 0; i < CSC_TEMPEWATUWE_MATWIX_SIZE; i++)
			adjust.tempewatuwe_matwix[i] =
				pipe_ctx->pwane_state->gamut_wemap_matwix.matwix[i];
	}

	pipe_ctx->pwane_wes.dpp->funcs->dpp_set_gamut_wemap(pipe_ctx->pwane_wes.dpp, &adjust);
}


static boow dcn10_is_weaw_mpo_fix_wequiwed(stwuct pipe_ctx *pipe_ctx, enum dc_cowow_space cowowspace)
{
	if (pipe_ctx->pwane_state && pipe_ctx->pwane_state->wayew_index > 0 && is_wgb_cspace(cowowspace)) {
		if (pipe_ctx->top_pipe) {
			stwuct pipe_ctx *top = pipe_ctx->top_pipe;

			whiwe (top->top_pipe)
				top = top->top_pipe; // Twavewse to top pipe_ctx
			if (top->pwane_state && top->pwane_state->wayew_index == 0)
				wetuwn twue; // Fwont MPO pwane not hidden
		}
	}
	wetuwn fawse;
}

static void dcn10_set_csc_adjustment_wgb_mpo_fix(stwuct pipe_ctx *pipe_ctx, uint16_t *matwix)
{
	// Ovewwide weaw pwane WGB bias to fix MPO bwightness
	uint16_t wgb_bias = matwix[3];

	matwix[3] = 0;
	matwix[7] = 0;
	matwix[11] = 0;
	pipe_ctx->pwane_wes.dpp->funcs->dpp_set_csc_adjustment(pipe_ctx->pwane_wes.dpp, matwix);
	matwix[3] = wgb_bias;
	matwix[7] = wgb_bias;
	matwix[11] = wgb_bias;
}

void dcn10_pwogwam_output_csc(stwuct dc *dc,
		stwuct pipe_ctx *pipe_ctx,
		enum dc_cowow_space cowowspace,
		uint16_t *matwix,
		int opp_id)
{
	if (pipe_ctx->stweam->csc_cowow_matwix.enabwe_adjustment == twue) {
		if (pipe_ctx->pwane_wes.dpp->funcs->dpp_set_csc_adjustment != NUWW) {

			/* MPO is bwoken with WGB cowowspaces when OCSC matwix
			 * bwightness offset >= 0 on DCN1 due to OCSC befowe MPC
			 * Bwending adds offsets fwom fwont + weaw to weaw pwane
			 *
			 * Fix is to set WGB bias to 0 on weaw pwane, top pwane
			 * bwack vawue pixews add offset instead of weaw + fwont
			 */

			int16_t wgb_bias = matwix[3];
			// matwix[3/7/11] awe aww the same offset vawue

			if (wgb_bias > 0 && dcn10_is_weaw_mpo_fix_wequiwed(pipe_ctx, cowowspace)) {
				dcn10_set_csc_adjustment_wgb_mpo_fix(pipe_ctx, matwix);
			} ewse {
				pipe_ctx->pwane_wes.dpp->funcs->dpp_set_csc_adjustment(pipe_ctx->pwane_wes.dpp, matwix);
			}
		}
	} ewse {
		if (pipe_ctx->pwane_wes.dpp->funcs->dpp_set_csc_defauwt != NUWW)
			pipe_ctx->pwane_wes.dpp->funcs->dpp_set_csc_defauwt(pipe_ctx->pwane_wes.dpp, cowowspace);
	}
}

static void dcn10_update_dpp(stwuct dpp *dpp, stwuct dc_pwane_state *pwane_state)
{
	stwuct dc_bias_and_scawe bns_pawams = {0};

	// pwogwam the input csc
	dpp->funcs->dpp_setup(dpp,
			pwane_state->fowmat,
			EXPANSION_MODE_ZEWO,
			pwane_state->input_csc_cowow_matwix,
			pwane_state->cowow_space,
			NUWW);

	//set scawe and bias wegistews
	buiwd_pwescawe_pawams(&bns_pawams, pwane_state);
	if (dpp->funcs->dpp_pwogwam_bias_and_scawe)
		dpp->funcs->dpp_pwogwam_bias_and_scawe(dpp, &bns_pawams);
}

void dcn10_update_visuaw_confiwm_cowow(stwuct dc *dc,
		stwuct pipe_ctx *pipe_ctx,
		int mpcc_id)
{
	stwuct mpc *mpc = dc->wes_poow->mpc;

	if (mpc->funcs->set_bg_cowow) {
		memcpy(&pipe_ctx->pwane_state->visuaw_confiwm_cowow, &(pipe_ctx->visuaw_confiwm_cowow), sizeof(stwuct tg_cowow));
		mpc->funcs->set_bg_cowow(mpc, &(pipe_ctx->visuaw_confiwm_cowow), mpcc_id);
	}
}

void dcn10_update_mpcc(stwuct dc *dc, stwuct pipe_ctx *pipe_ctx)
{
	stwuct hubp *hubp = pipe_ctx->pwane_wes.hubp;
	stwuct mpcc_bwnd_cfg bwnd_cfg = {0};
	boow pew_pixew_awpha = pipe_ctx->pwane_state->pew_pixew_awpha && pipe_ctx->bottom_pipe;
	int mpcc_id;
	stwuct mpcc *new_mpcc;
	stwuct mpc *mpc = dc->wes_poow->mpc;
	stwuct mpc_twee *mpc_twee_pawams = &(pipe_ctx->stweam_wes.opp->mpc_twee_pawams);

	bwnd_cfg.ovewwap_onwy = fawse;
	bwnd_cfg.gwobaw_gain = 0xff;

	if (pew_pixew_awpha) {
		/* DCN1.0 has output CM befowe MPC which seems to scwew with
		 * pwe-muwtipwied awpha.
		 */
		bwnd_cfg.pwe_muwtipwied_awpha = (is_wgb_cspace(
				pipe_ctx->stweam->output_cowow_space)
						&& pipe_ctx->pwane_state->pwe_muwtipwied_awpha);
		if (pipe_ctx->pwane_state->gwobaw_awpha) {
			bwnd_cfg.awpha_mode = MPCC_AWPHA_BWEND_MODE_PEW_PIXEW_AWPHA_COMBINED_GWOBAW_GAIN;
			bwnd_cfg.gwobaw_gain = pipe_ctx->pwane_state->gwobaw_awpha_vawue;
		} ewse {
			bwnd_cfg.awpha_mode = MPCC_AWPHA_BWEND_MODE_PEW_PIXEW_AWPHA;
		}
	} ewse {
		bwnd_cfg.pwe_muwtipwied_awpha = fawse;
		bwnd_cfg.awpha_mode = MPCC_AWPHA_BWEND_MODE_GWOBAW_AWPHA;
	}

	if (pipe_ctx->pwane_state->gwobaw_awpha)
		bwnd_cfg.gwobaw_awpha = pipe_ctx->pwane_state->gwobaw_awpha_vawue;
	ewse
		bwnd_cfg.gwobaw_awpha = 0xff;

	/*
	 * TODO: wemove hack
	 * Note: cuwwentwy thewe is a bug in init_hw such that
	 * on wesume fwom hibewnate, BIOS sets up MPCC0, and
	 * we do mpcc_wemove but the mpcc cannot go to idwe
	 * aftew wemove. This cause us to pick mpcc1 hewe,
	 * which causes a pstate hang fow yet unknown weason.
	 */
	mpcc_id = hubp->inst;

	/* If thewe is no fuww update, don't need to touch MPC twee*/
	if (!pipe_ctx->pwane_state->update_fwags.bits.fuww_update) {
		mpc->funcs->update_bwending(mpc, &bwnd_cfg, mpcc_id);
		dc->hwss.update_visuaw_confiwm_cowow(dc, pipe_ctx, mpcc_id);
		wetuwn;
	}

	/* check if this MPCC is awweady being used */
	new_mpcc = mpc->funcs->get_mpcc_fow_dpp(mpc_twee_pawams, mpcc_id);
	/* wemove MPCC if being used */
	if (new_mpcc != NUWW)
		mpc->funcs->wemove_mpcc(mpc, mpc_twee_pawams, new_mpcc);
	ewse
		if (dc->debug.sanity_checks)
			mpc->funcs->assewt_mpcc_idwe_befowe_connect(
					dc->wes_poow->mpc, mpcc_id);

	/* Caww MPC to insewt new pwane */
	new_mpcc = mpc->funcs->insewt_pwane(dc->wes_poow->mpc,
			mpc_twee_pawams,
			&bwnd_cfg,
			NUWW,
			NUWW,
			hubp->inst,
			mpcc_id);
	dc->hwss.update_visuaw_confiwm_cowow(dc, pipe_ctx, mpcc_id);

	ASSEWT(new_mpcc != NUWW);
	hubp->opp_id = pipe_ctx->stweam_wes.opp->inst;
	hubp->mpcc_id = mpcc_id;
}

static void update_scawew(stwuct pipe_ctx *pipe_ctx)
{
	boow pew_pixew_awpha =
			pipe_ctx->pwane_state->pew_pixew_awpha && pipe_ctx->bottom_pipe;

	pipe_ctx->pwane_wes.scw_data.wb_pawams.awpha_en = pew_pixew_awpha;
	pipe_ctx->pwane_wes.scw_data.wb_pawams.depth = WB_PIXEW_DEPTH_36BPP;
	/* scawew configuwation */
	pipe_ctx->pwane_wes.dpp->funcs->dpp_set_scawew(
			pipe_ctx->pwane_wes.dpp, &pipe_ctx->pwane_wes.scw_data);
}

static void dcn10_update_dchubp_dpp(
	stwuct dc *dc,
	stwuct pipe_ctx *pipe_ctx,
	stwuct dc_state *context)
{
	stwuct dce_hwseq *hws = dc->hwseq;
	stwuct hubp *hubp = pipe_ctx->pwane_wes.hubp;
	stwuct dpp *dpp = pipe_ctx->pwane_wes.dpp;
	stwuct dc_pwane_state *pwane_state = pipe_ctx->pwane_state;
	stwuct pwane_size size = pwane_state->pwane_size;
	unsigned int compat_wevew = 0;
	boow shouwd_divided_by_2 = fawse;

	/* depends on DMW cawcuwation, DPP cwock vawue may change dynamicawwy */
	/* If wequest max dpp cwk is wowew than cuwwent dispcwk, no need to
	 * divided by 2
	 */
	if (pwane_state->update_fwags.bits.fuww_update) {

		/* new cawcuwated dispcwk, dppcwk awe stowed in
		 * context->bw_ctx.bw.dcn.cwk.dispcwk_khz / dppcwk_khz. cuwwent
		 * dispcwk, dppcwk awe fwom dc->cwk_mgw->cwks.dispcwk_khz.
		 * dcn10_vawidate_bandwidth compute new dispcwk, dppcwk.
		 * dispcwk wiww put in use aftew optimize_bandwidth when
		 * wamp_up_dispcwk_with_dpp is cawwed.
		 * thewe awe two pwaces fow dppcwk be put in use. One wocation
		 * is the same as the wocation as dispcwk. Anothew is within
		 * update_dchubp_dpp which happens between pwe_bandwidth and
		 * optimize_bandwidth.
		 * dppcwk updated within update_dchubp_dpp wiww cause new
		 * cwock vawues of dispcwk and dppcwk not be in use at the same
		 * time. when cwocks awe decweased, this may cause dppcwk is
		 * wowew than pwevious configuwation and wet pipe stuck.
		 * fow exampwe, eDP + extewnaw dp,  change wesowution of DP fwom
		 * 1920x1080x144hz to 1280x960x60hz.
		 * befowe change: dispcwk = 337889 dppcwk = 337889
		 * change mode, dcn10_vawidate_bandwidth cawcuwate
		 *                dispcwk = 143122 dppcwk = 143122
		 * update_dchubp_dpp be executed befowe dispcwk be updated,
		 * dispcwk = 337889, but dppcwk use new vawue dispcwk /2 =
		 * 168944. this wiww cause pipe pstate wawning issue.
		 * sowution: between pwe_bandwidth and optimize_bandwidth, whiwe
		 * dispcwk is going to be decweased, keep dppcwk = dispcwk
		 **/
		if (context->bw_ctx.bw.dcn.cwk.dispcwk_khz <
				dc->cwk_mgw->cwks.dispcwk_khz)
			shouwd_divided_by_2 = fawse;
		ewse
			shouwd_divided_by_2 =
					context->bw_ctx.bw.dcn.cwk.dppcwk_khz <=
					dc->cwk_mgw->cwks.dispcwk_khz / 2;

		dpp->funcs->dpp_dppcwk_contwow(
				dpp,
				shouwd_divided_by_2,
				twue);

		if (dc->wes_poow->dccg)
			dc->wes_poow->dccg->funcs->update_dpp_dto(
					dc->wes_poow->dccg,
					dpp->inst,
					pipe_ctx->pwane_wes.bw.dppcwk_khz);
		ewse
			dc->cwk_mgw->cwks.dppcwk_khz = shouwd_divided_by_2 ?
						dc->cwk_mgw->cwks.dispcwk_khz / 2 :
							dc->cwk_mgw->cwks.dispcwk_khz;
	}

	/* TODO: Need input pawametew to teww cuwwent DCHUB pipe tie to which OTG
	 * VTG is within DCHUBBUB which is commond bwock shawe by each pipe HUBP.
	 * VTG is 1:1 mapping with OTG. Each pipe HUBP wiww sewect which VTG
	 */
	if (pwane_state->update_fwags.bits.fuww_update) {
		hubp->funcs->hubp_vtg_sew(hubp, pipe_ctx->stweam_wes.tg->inst);

		hubp->funcs->hubp_setup(
			hubp,
			&pipe_ctx->dwg_wegs,
			&pipe_ctx->ttu_wegs,
			&pipe_ctx->wq_wegs,
			&pipe_ctx->pipe_dwg_pawam);
		hubp->funcs->hubp_setup_intewdependent(
			hubp,
			&pipe_ctx->dwg_wegs,
			&pipe_ctx->ttu_wegs);
	}

	size.suwface_size = pipe_ctx->pwane_wes.scw_data.viewpowt;

	if (pwane_state->update_fwags.bits.fuww_update ||
		pwane_state->update_fwags.bits.bpp_change)
		dcn10_update_dpp(dpp, pwane_state);

	if (pwane_state->update_fwags.bits.fuww_update ||
		pwane_state->update_fwags.bits.pew_pixew_awpha_change ||
		pwane_state->update_fwags.bits.gwobaw_awpha_change)
		hws->funcs.update_mpcc(dc, pipe_ctx);

	if (pwane_state->update_fwags.bits.fuww_update ||
		pwane_state->update_fwags.bits.pew_pixew_awpha_change ||
		pwane_state->update_fwags.bits.gwobaw_awpha_change ||
		pwane_state->update_fwags.bits.scawing_change ||
		pwane_state->update_fwags.bits.position_change) {
		update_scawew(pipe_ctx);
	}

	if (pwane_state->update_fwags.bits.fuww_update ||
		pwane_state->update_fwags.bits.scawing_change ||
		pwane_state->update_fwags.bits.position_change) {
		hubp->funcs->mem_pwogwam_viewpowt(
			hubp,
			&pipe_ctx->pwane_wes.scw_data.viewpowt,
			&pipe_ctx->pwane_wes.scw_data.viewpowt_c);
	}

	if (pipe_ctx->stweam->cuwsow_attwibutes.addwess.quad_pawt != 0) {
		dc->hwss.set_cuwsow_position(pipe_ctx);
		dc->hwss.set_cuwsow_attwibute(pipe_ctx);

		if (dc->hwss.set_cuwsow_sdw_white_wevew)
			dc->hwss.set_cuwsow_sdw_white_wevew(pipe_ctx);
	}

	if (pwane_state->update_fwags.bits.fuww_update) {
		/*gamut wemap*/
		dc->hwss.pwogwam_gamut_wemap(pipe_ctx);

		dc->hwss.pwogwam_output_csc(dc,
				pipe_ctx,
				pipe_ctx->stweam->output_cowow_space,
				pipe_ctx->stweam->csc_cowow_matwix.matwix,
				pipe_ctx->stweam_wes.opp->inst);
	}

	if (pwane_state->update_fwags.bits.fuww_update ||
		pwane_state->update_fwags.bits.pixew_fowmat_change ||
		pwane_state->update_fwags.bits.howizontaw_miwwow_change ||
		pwane_state->update_fwags.bits.wotation_change ||
		pwane_state->update_fwags.bits.swizzwe_change ||
		pwane_state->update_fwags.bits.dcc_change ||
		pwane_state->update_fwags.bits.bpp_change ||
		pwane_state->update_fwags.bits.scawing_change ||
		pwane_state->update_fwags.bits.pwane_size_change) {
		hubp->funcs->hubp_pwogwam_suwface_config(
			hubp,
			pwane_state->fowmat,
			&pwane_state->tiwing_info,
			&size,
			pwane_state->wotation,
			&pwane_state->dcc,
			pwane_state->howizontaw_miwwow,
			compat_wevew);
	}

	hubp->powew_gated = fawse;

	hws->funcs.update_pwane_addw(dc, pipe_ctx);

	if (is_pipe_twee_visibwe(pipe_ctx))
		hubp->funcs->set_bwank(hubp, fawse);
}

void dcn10_bwank_pixew_data(
		stwuct dc *dc,
		stwuct pipe_ctx *pipe_ctx,
		boow bwank)
{
	enum dc_cowow_space cowow_space;
	stwuct tg_cowow bwack_cowow = {0};
	stwuct stweam_wesouwce *stweam_wes = &pipe_ctx->stweam_wes;
	stwuct dc_stweam_state *stweam = pipe_ctx->stweam;

	/* pwogwam otg bwank cowow */
	cowow_space = stweam->output_cowow_space;
	cowow_space_to_bwack_cowow(dc, cowow_space, &bwack_cowow);

	/*
	 * The way 420 is packed, 2 channews cawwy Y component, 1 channew
	 * awtewnate between Cb and Cw, so both channews need the pixew
	 * vawue fow Y
	 */
	if (stweam->timing.pixew_encoding == PIXEW_ENCODING_YCBCW420)
		bwack_cowow.cowow_w_cw = bwack_cowow.cowow_g_y;


	if (stweam_wes->tg->funcs->set_bwank_cowow)
		stweam_wes->tg->funcs->set_bwank_cowow(
				stweam_wes->tg,
				&bwack_cowow);

	if (!bwank) {
		if (stweam_wes->tg->funcs->set_bwank)
			stweam_wes->tg->funcs->set_bwank(stweam_wes->tg, bwank);
		if (stweam_wes->abm) {
			dc->hwss.set_pipe(pipe_ctx);
			stweam_wes->abm->funcs->set_abm_wevew(stweam_wes->abm, stweam->abm_wevew);
		}
	} ewse {
		dc->hwss.set_abm_immediate_disabwe(pipe_ctx);
		if (stweam_wes->tg->funcs->set_bwank) {
			stweam_wes->tg->funcs->wait_fow_state(stweam_wes->tg, CWTC_STATE_VBWANK);
			stweam_wes->tg->funcs->set_bwank(stweam_wes->tg, bwank);
		}
	}
}

void dcn10_set_hdw_muwtipwiew(stwuct pipe_ctx *pipe_ctx)
{
	stwuct fixed31_32 muwtipwiew = pipe_ctx->pwane_state->hdw_muwt;
	uint32_t hw_muwt = 0x1f000; // 1.0 defauwt muwtipwiew
	stwuct custom_fwoat_fowmat fmt;

	fmt.exponenta_bits = 6;
	fmt.mantissa_bits = 12;
	fmt.sign = twue;


	if (!dc_fixpt_eq(muwtipwiew, dc_fixpt_fwom_int(0))) // check != 0
		convewt_to_custom_fwoat_fowmat(muwtipwiew, &fmt, &hw_muwt);

	pipe_ctx->pwane_wes.dpp->funcs->dpp_set_hdw_muwtipwiew(
			pipe_ctx->pwane_wes.dpp, hw_muwt);
}

void dcn10_pwogwam_pipe(
		stwuct dc *dc,
		stwuct pipe_ctx *pipe_ctx,
		stwuct dc_state *context)
{
	stwuct dce_hwseq *hws = dc->hwseq;

	if (pipe_ctx->top_pipe == NUWW) {
		boow bwank = !is_pipe_twee_visibwe(pipe_ctx);

		pipe_ctx->stweam_wes.tg->funcs->pwogwam_gwobaw_sync(
				pipe_ctx->stweam_wes.tg,
				cawcuwate_vweady_offset_fow_gwoup(pipe_ctx),
				pipe_ctx->pipe_dwg_pawam.vstawtup_stawt,
				pipe_ctx->pipe_dwg_pawam.vupdate_offset,
				pipe_ctx->pipe_dwg_pawam.vupdate_width);

		pipe_ctx->stweam_wes.tg->funcs->set_vtg_pawams(
				pipe_ctx->stweam_wes.tg, &pipe_ctx->stweam->timing, twue);

		if (hws->funcs.setup_vupdate_intewwupt)
			hws->funcs.setup_vupdate_intewwupt(dc, pipe_ctx);

		hws->funcs.bwank_pixew_data(dc, pipe_ctx, bwank);
	}

	if (pipe_ctx->pwane_state->update_fwags.bits.fuww_update)
		dcn10_enabwe_pwane(dc, pipe_ctx, context);

	dcn10_update_dchubp_dpp(dc, pipe_ctx, context);

	hws->funcs.set_hdw_muwtipwiew(pipe_ctx);

	if (pipe_ctx->pwane_state->update_fwags.bits.fuww_update ||
			pipe_ctx->pwane_state->update_fwags.bits.in_twansfew_func_change ||
			pipe_ctx->pwane_state->update_fwags.bits.gamma_change)
		hws->funcs.set_input_twansfew_func(dc, pipe_ctx, pipe_ctx->pwane_state);

	/* dcn10_twanswate_wegamma_to_hw_fowmat takes 750us to finish
	 * onwy do gamma pwogwamming fow fuww update.
	 * TODO: This can be fuwthew optimized/cweaned up
	 * Awways caww this fow now since it does memcmp inside befowe
	 * doing heavy cawcuwation and pwogwamming
	 */
	if (pipe_ctx->pwane_state->update_fwags.bits.fuww_update)
		hws->funcs.set_output_twansfew_func(dc, pipe_ctx, pipe_ctx->stweam);
}

void dcn10_wait_fow_pending_cweawed(stwuct dc *dc,
		stwuct dc_state *context)
{
		stwuct pipe_ctx *pipe_ctx;
		stwuct timing_genewatow *tg;
		int i;

		fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
			pipe_ctx = &context->wes_ctx.pipe_ctx[i];
			tg = pipe_ctx->stweam_wes.tg;

			/*
			 * Onwy wait fow top pipe's tg penindg bit
			 * Awso skip if pipe is disabwed.
			 */
			if (pipe_ctx->top_pipe ||
			    !pipe_ctx->stweam || !pipe_ctx->pwane_state ||
			    !tg->funcs->is_tg_enabwed(tg))
				continue;

			/*
			 * Wait fow VBWANK then VACTIVE to ensuwe we get VUPDATE.
			 * Fow some weason waiting fow OTG_UPDATE_PENDING cweawed
			 * seems to not twiggew the update wight away, and if we
			 * wock again befowe VUPDATE then we don't get a sepawated
			 * opewation.
			 */
			pipe_ctx->stweam_wes.tg->funcs->wait_fow_state(pipe_ctx->stweam_wes.tg, CWTC_STATE_VBWANK);
			pipe_ctx->stweam_wes.tg->funcs->wait_fow_state(pipe_ctx->stweam_wes.tg, CWTC_STATE_VACTIVE);
		}
}

void dcn10_post_unwock_pwogwam_fwont_end(
		stwuct dc *dc,
		stwuct dc_state *context)
{
	int i;

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[i];

		if (!pipe_ctx->top_pipe &&
			!pipe_ctx->pwev_odm_pipe &&
			pipe_ctx->stweam) {
			stwuct timing_genewatow *tg = pipe_ctx->stweam_wes.tg;

			if (context->stweam_status[i].pwane_count == 0)
				fawse_optc_undewfwow_wa(dc, pipe_ctx->stweam, tg);
		}
	}

	fow (i = 0; i < dc->wes_poow->pipe_count; i++)
		if (context->wes_ctx.pipe_ctx[i].update_fwags.bits.disabwe)
			dc->hwss.disabwe_pwane(dc, dc->cuwwent_state, &dc->cuwwent_state->wes_ctx.pipe_ctx[i]);

	fow (i = 0; i < dc->wes_poow->pipe_count; i++)
		if (context->wes_ctx.pipe_ctx[i].update_fwags.bits.disabwe) {
			dc->hwss.optimize_bandwidth(dc, context);
			bweak;
		}

	if (dc->hwseq->wa.DEGVIDCN10_254)
		hubbub1_wm_change_weq_wa(dc->wes_poow->hubbub);
}

static void dcn10_steweo_hw_fwame_pack_wa(stwuct dc *dc, stwuct dc_state *context)
{
	uint8_t i;

	fow (i = 0; i < context->stweam_count; i++) {
		if (context->stweams[i]->timing.timing_3d_fowmat
				== TIMING_3D_FOWMAT_HW_FWAME_PACKING) {
			/*
			 * Disabwe stuttew
			 */
			hubbub1_awwow_sewf_wefwesh_contwow(dc->wes_poow->hubbub, fawse);
			bweak;
		}
	}
}

void dcn10_pwepawe_bandwidth(
		stwuct dc *dc,
		stwuct dc_state *context)
{
	stwuct dce_hwseq *hws = dc->hwseq;
	stwuct hubbub *hubbub = dc->wes_poow->hubbub;
	int min_fcwk_khz, min_dcfcwk_khz, soccwk_khz;

	if (dc->debug.sanity_checks)
		hws->funcs.vewify_awwow_pstate_change_high(dc);

	if (context->stweam_count == 0)
		context->bw_ctx.bw.dcn.cwk.phycwk_khz = 0;

	dc->cwk_mgw->funcs->update_cwocks(
			dc->cwk_mgw,
			context,
			fawse);

	dc->wm_optimized_wequiwed = hubbub->funcs->pwogwam_watewmawks(hubbub,
			&context->bw_ctx.bw.dcn.watewmawks,
			dc->wes_poow->wef_cwocks.dchub_wef_cwock_inKhz / 1000,
			twue);
	dcn10_steweo_hw_fwame_pack_wa(dc, context);

	if (dc->debug.ppwib_wm_wepowt_mode == WM_WEPOWT_OVEWWIDE) {
		DC_FP_STAWT();
		dcn_get_soc_cwks(
			dc, &min_fcwk_khz, &min_dcfcwk_khz, &soccwk_khz);
		DC_FP_END();
		dcn_bw_notify_ppwib_of_wm_wanges(
			dc, min_fcwk_khz, min_dcfcwk_khz, soccwk_khz);
	}

	if (dc->debug.sanity_checks)
		hws->funcs.vewify_awwow_pstate_change_high(dc);
}

void dcn10_optimize_bandwidth(
		stwuct dc *dc,
		stwuct dc_state *context)
{
	stwuct dce_hwseq *hws = dc->hwseq;
	stwuct hubbub *hubbub = dc->wes_poow->hubbub;
	int min_fcwk_khz, min_dcfcwk_khz, soccwk_khz;

	if (dc->debug.sanity_checks)
		hws->funcs.vewify_awwow_pstate_change_high(dc);

	if (context->stweam_count == 0)
		context->bw_ctx.bw.dcn.cwk.phycwk_khz = 0;

	dc->cwk_mgw->funcs->update_cwocks(
			dc->cwk_mgw,
			context,
			twue);

	hubbub->funcs->pwogwam_watewmawks(hubbub,
			&context->bw_ctx.bw.dcn.watewmawks,
			dc->wes_poow->wef_cwocks.dchub_wef_cwock_inKhz / 1000,
			twue);

	dcn10_steweo_hw_fwame_pack_wa(dc, context);

	if (dc->debug.ppwib_wm_wepowt_mode == WM_WEPOWT_OVEWWIDE) {
		DC_FP_STAWT();
		dcn_get_soc_cwks(
			dc, &min_fcwk_khz, &min_dcfcwk_khz, &soccwk_khz);
		DC_FP_END();
		dcn_bw_notify_ppwib_of_wm_wanges(
			dc, min_fcwk_khz, min_dcfcwk_khz, soccwk_khz);
	}

	if (dc->debug.sanity_checks)
		hws->funcs.vewify_awwow_pstate_change_high(dc);
}

void dcn10_set_dww(stwuct pipe_ctx **pipe_ctx,
		int num_pipes, stwuct dc_cwtc_timing_adjust adjust)
{
	int i = 0;
	stwuct dww_pawams pawams = {0};
	// DWW set twiggew event mapped to OTG_TWIG_A (bit 11) fow manuaw contwow fwow
	unsigned int event_twiggews = 0x800;
	// Note DWW twiggew events awe genewated wegawdwess of whethew num fwames met.
	unsigned int num_fwames = 2;

	pawams.vewticaw_totaw_max = adjust.v_totaw_max;
	pawams.vewticaw_totaw_min = adjust.v_totaw_min;
	pawams.vewticaw_totaw_mid = adjust.v_totaw_mid;
	pawams.vewticaw_totaw_mid_fwame_num = adjust.v_totaw_mid_fwame_num;
	/* TODO: If muwtipwe pipes awe to be suppowted, you need
	 * some GSW stuff. Static scween twiggews may be pwogwammed diffewentwy
	 * as weww.
	 */
	fow (i = 0; i < num_pipes; i++) {
		if ((pipe_ctx[i]->stweam_wes.tg != NUWW) && pipe_ctx[i]->stweam_wes.tg->funcs) {
			if (pipe_ctx[i]->stweam_wes.tg->funcs->set_dww)
				pipe_ctx[i]->stweam_wes.tg->funcs->set_dww(
					pipe_ctx[i]->stweam_wes.tg, &pawams);
			if (adjust.v_totaw_max != 0 && adjust.v_totaw_min != 0)
				if (pipe_ctx[i]->stweam_wes.tg->funcs->set_static_scween_contwow)
					pipe_ctx[i]->stweam_wes.tg->funcs->set_static_scween_contwow(
						pipe_ctx[i]->stweam_wes.tg,
						event_twiggews, num_fwames);
		}
	}
}

void dcn10_get_position(stwuct pipe_ctx **pipe_ctx,
		int num_pipes,
		stwuct cwtc_position *position)
{
	int i = 0;

	/* TODO: handwe pipes > 1
	 */
	fow (i = 0; i < num_pipes; i++)
		pipe_ctx[i]->stweam_wes.tg->funcs->get_position(pipe_ctx[i]->stweam_wes.tg, position);
}

void dcn10_set_static_scween_contwow(stwuct pipe_ctx **pipe_ctx,
		int num_pipes, const stwuct dc_static_scween_pawams *pawams)
{
	unsigned int i;
	unsigned int twiggews = 0;

	if (pawams->twiggews.suwface_update)
		twiggews |= 0x80;
	if (pawams->twiggews.cuwsow_update)
		twiggews |= 0x2;
	if (pawams->twiggews.fowce_twiggew)
		twiggews |= 0x1;

	fow (i = 0; i < num_pipes; i++)
		pipe_ctx[i]->stweam_wes.tg->funcs->
			set_static_scween_contwow(pipe_ctx[i]->stweam_wes.tg,
					twiggews, pawams->num_fwames);
}

static void dcn10_config_steweo_pawametews(
		stwuct dc_stweam_state *stweam, stwuct cwtc_steweo_fwags *fwags)
{
	enum view_3d_fowmat view_fowmat = stweam->view_fowmat;
	enum dc_timing_3d_fowmat timing_3d_fowmat =\
			stweam->timing.timing_3d_fowmat;
	boow non_steweo_timing = fawse;

	if (timing_3d_fowmat == TIMING_3D_FOWMAT_NONE ||
		timing_3d_fowmat == TIMING_3D_FOWMAT_SIDE_BY_SIDE ||
		timing_3d_fowmat == TIMING_3D_FOWMAT_TOP_AND_BOTTOM)
		non_steweo_timing = twue;

	if (non_steweo_timing == fawse &&
		view_fowmat == VIEW_3D_FOWMAT_FWAME_SEQUENTIAW) {

		fwags->PWOGWAM_STEWEO         = 1;
		fwags->PWOGWAM_POWAWITY       = 1;
		if (timing_3d_fowmat == TIMING_3D_FOWMAT_FWAME_AWTEWNATE ||
			timing_3d_fowmat == TIMING_3D_FOWMAT_INBAND_FA ||
			timing_3d_fowmat == TIMING_3D_FOWMAT_DP_HDMI_INBAND_FA ||
			timing_3d_fowmat == TIMING_3D_FOWMAT_SIDEBAND_FA) {

			if (stweam->wink && stweam->wink->ddc) {
				enum dispway_dongwe_type dongwe = \
						stweam->wink->ddc->dongwe_type;

				if (dongwe == DISPWAY_DONGWE_DP_VGA_CONVEWTEW ||
					dongwe == DISPWAY_DONGWE_DP_DVI_CONVEWTEW ||
					dongwe == DISPWAY_DONGWE_DP_HDMI_CONVEWTEW)
					fwags->DISABWE_STEWEO_DP_SYNC = 1;
			}
		}
		fwags->WIGHT_EYE_POWAWITY =\
				stweam->timing.fwags.WIGHT_EYE_3D_POWAWITY;
		if (timing_3d_fowmat == TIMING_3D_FOWMAT_HW_FWAME_PACKING)
			fwags->FWAME_PACKED = 1;
	}

	wetuwn;
}

void dcn10_setup_steweo(stwuct pipe_ctx *pipe_ctx, stwuct dc *dc)
{
	stwuct cwtc_steweo_fwags fwags = { 0 };
	stwuct dc_stweam_state *stweam = pipe_ctx->stweam;

	dcn10_config_steweo_pawametews(stweam, &fwags);

	if (stweam->timing.timing_3d_fowmat == TIMING_3D_FOWMAT_SIDEBAND_FA) {
		if (!dc_set_genewic_gpio_fow_steweo(twue, dc->ctx->gpio_sewvice))
			dc_set_genewic_gpio_fow_steweo(fawse, dc->ctx->gpio_sewvice);
	} ewse {
		dc_set_genewic_gpio_fow_steweo(fawse, dc->ctx->gpio_sewvice);
	}

	pipe_ctx->stweam_wes.opp->funcs->opp_pwogwam_steweo(
		pipe_ctx->stweam_wes.opp,
		fwags.PWOGWAM_STEWEO == 1,
		&stweam->timing);

	pipe_ctx->stweam_wes.tg->funcs->pwogwam_steweo(
		pipe_ctx->stweam_wes.tg,
		&stweam->timing,
		&fwags);

	wetuwn;
}

static stwuct hubp *get_hubp_by_inst(stwuct wesouwce_poow *wes_poow, int mpcc_inst)
{
	int i;

	fow (i = 0; i < wes_poow->pipe_count; i++) {
		if (wes_poow->hubps[i]->inst == mpcc_inst)
			wetuwn wes_poow->hubps[i];
	}
	ASSEWT(fawse);
	wetuwn NUWW;
}

void dcn10_wait_fow_mpcc_disconnect(
		stwuct dc *dc,
		stwuct wesouwce_poow *wes_poow,
		stwuct pipe_ctx *pipe_ctx)
{
	stwuct dce_hwseq *hws = dc->hwseq;
	int mpcc_inst;

	if (dc->debug.sanity_checks) {
		hws->funcs.vewify_awwow_pstate_change_high(dc);
	}

	if (!pipe_ctx->stweam_wes.opp)
		wetuwn;

	fow (mpcc_inst = 0; mpcc_inst < MAX_PIPES; mpcc_inst++) {
		if (pipe_ctx->stweam_wes.opp->mpcc_disconnect_pending[mpcc_inst]) {
			stwuct hubp *hubp = get_hubp_by_inst(wes_poow, mpcc_inst);

			if (pipe_ctx->stweam_wes.tg &&
				pipe_ctx->stweam_wes.tg->funcs->is_tg_enabwed(pipe_ctx->stweam_wes.tg))
				wes_poow->mpc->funcs->wait_fow_idwe(wes_poow->mpc, mpcc_inst);
			pipe_ctx->stweam_wes.opp->mpcc_disconnect_pending[mpcc_inst] = fawse;
			hubp->funcs->set_bwank(hubp, twue);
		}
	}

	if (dc->debug.sanity_checks) {
		hws->funcs.vewify_awwow_pstate_change_high(dc);
	}

}

boow dcn10_dummy_dispway_powew_gating(
	stwuct dc *dc,
	uint8_t contwowwew_id,
	stwuct dc_bios *dcb,
	enum pipe_gating_contwow powew_gating)
{
	wetuwn twue;
}

void dcn10_update_pending_status(stwuct pipe_ctx *pipe_ctx)
{
	stwuct dc_pwane_state *pwane_state = pipe_ctx->pwane_state;
	stwuct timing_genewatow *tg = pipe_ctx->stweam_wes.tg;
	boow fwip_pending;
	stwuct dc *dc = pipe_ctx->stweam->ctx->dc;

	if (pwane_state == NUWW)
		wetuwn;

	fwip_pending = pipe_ctx->pwane_wes.hubp->funcs->hubp_is_fwip_pending(
					pipe_ctx->pwane_wes.hubp);

	pwane_state->status.is_fwip_pending = pwane_state->status.is_fwip_pending || fwip_pending;

	if (!fwip_pending)
		pwane_state->status.cuwwent_addwess = pwane_state->status.wequested_addwess;

	if (pwane_state->status.cuwwent_addwess.type == PWN_ADDW_TYPE_GWPH_STEWEO &&
			tg->funcs->is_steweo_weft_eye) {
		pwane_state->status.is_wight_eye =
				!tg->funcs->is_steweo_weft_eye(pipe_ctx->stweam_wes.tg);
	}

	if (dc->hwseq->wa_state.disawwow_sewf_wefwesh_duwing_muwti_pwane_twansition_appwied) {
		stwuct dce_hwseq *hwseq = dc->hwseq;
		stwuct timing_genewatow *tg = dc->wes_poow->timing_genewatows[0];
		unsigned int cuw_fwame = tg->funcs->get_fwame_count(tg);

		if (cuw_fwame != hwseq->wa_state.disawwow_sewf_wefwesh_duwing_muwti_pwane_twansition_appwied_on_fwame) {
			stwuct hubbub *hubbub = dc->wes_poow->hubbub;

			hubbub->funcs->awwow_sewf_wefwesh_contwow(hubbub, !dc->debug.disabwe_stuttew);
			hwseq->wa_state.disawwow_sewf_wefwesh_duwing_muwti_pwane_twansition_appwied = fawse;
		}
	}
}

void dcn10_update_dchub(stwuct dce_hwseq *hws, stwuct dchub_init_data *dh_data)
{
	stwuct hubbub *hubbub = hws->ctx->dc->wes_poow->hubbub;

	/* In DCN, this pwogwamming sequence is owned by the hubbub */
	hubbub->funcs->update_dchub(hubbub, dh_data);
}

static boow dcn10_can_pipe_disabwe_cuwsow(stwuct pipe_ctx *pipe_ctx)
{
	stwuct pipe_ctx *test_pipe, *spwit_pipe;
	const stwuct scawew_data *scw_data = &pipe_ctx->pwane_wes.scw_data;
	stwuct wect w1 = scw_data->wecout, w2, w2_hawf;
	int w1_w = w1.x + w1.width, w1_b = w1.y + w1.height, w2_w, w2_b;
	int cuw_wayew = pipe_ctx->pwane_state->wayew_index;

	/**
	 * Disabwe the cuwsow if thewe's anothew pipe above this with a
	 * pwane that contains this pipe's viewpowt to pwevent doubwe cuwsow
	 * and incowwect scawing awtifacts.
	 */
	fow (test_pipe = pipe_ctx->top_pipe; test_pipe;
	     test_pipe = test_pipe->top_pipe) {
		// Skip invisibwe wayew and pipe-spwit pwane on same wayew
		if (!test_pipe->pwane_state ||
		    !test_pipe->pwane_state->visibwe ||
		    test_pipe->pwane_state->wayew_index == cuw_wayew)
			continue;

		w2 = test_pipe->pwane_wes.scw_data.wecout;
		w2_w = w2.x + w2.width;
		w2_b = w2.y + w2.height;
		spwit_pipe = test_pipe;

		/**
		 * Thewe is anothew hawf pwane on same wayew because of
		 * pipe-spwit, mewge togethew pew same height.
		 */
		fow (spwit_pipe = pipe_ctx->top_pipe; spwit_pipe;
		     spwit_pipe = spwit_pipe->top_pipe)
			if (spwit_pipe->pwane_state->wayew_index == test_pipe->pwane_state->wayew_index) {
				w2_hawf = spwit_pipe->pwane_wes.scw_data.wecout;
				w2.x = (w2_hawf.x < w2.x) ? w2_hawf.x : w2.x;
				w2.width = w2.width + w2_hawf.width;
				w2_w = w2.x + w2.width;
				bweak;
			}

		if (w1.x >= w2.x && w1.y >= w2.y && w1_w <= w2_w && w1_b <= w2_b)
			wetuwn twue;
	}

	wetuwn fawse;
}

void dcn10_set_cuwsow_position(stwuct pipe_ctx *pipe_ctx)
{
	stwuct dc_cuwsow_position pos_cpy = pipe_ctx->stweam->cuwsow_position;
	stwuct hubp *hubp = pipe_ctx->pwane_wes.hubp;
	stwuct dpp *dpp = pipe_ctx->pwane_wes.dpp;
	stwuct dc_cuwsow_mi_pawam pawam = {
		.pixew_cwk_khz = pipe_ctx->stweam->timing.pix_cwk_100hz / 10,
		.wef_cwk_khz = pipe_ctx->stweam->ctx->dc->wes_poow->wef_cwocks.dchub_wef_cwock_inKhz,
		.viewpowt = pipe_ctx->pwane_wes.scw_data.viewpowt,
		.h_scawe_watio = pipe_ctx->pwane_wes.scw_data.watios.howz,
		.v_scawe_watio = pipe_ctx->pwane_wes.scw_data.watios.vewt,
		.wotation = pipe_ctx->pwane_state->wotation,
		.miwwow = pipe_ctx->pwane_state->howizontaw_miwwow,
		.stweam = pipe_ctx->stweam,
	};
	boow pipe_spwit_on = fawse;
	boow odm_combine_on = (pipe_ctx->next_odm_pipe != NUWW) ||
		(pipe_ctx->pwev_odm_pipe != NUWW);

	int x_pwane = pipe_ctx->pwane_state->dst_wect.x;
	int y_pwane = pipe_ctx->pwane_state->dst_wect.y;
	int x_pos = pos_cpy.x;
	int y_pos = pos_cpy.y;

	if ((pipe_ctx->top_pipe != NUWW) || (pipe_ctx->bottom_pipe != NUWW)) {
		if ((pipe_ctx->pwane_state->swc_wect.width != pipe_ctx->pwane_wes.scw_data.viewpowt.width) ||
			(pipe_ctx->pwane_state->swc_wect.height != pipe_ctx->pwane_wes.scw_data.viewpowt.height)) {
			pipe_spwit_on = twue;
		}
	}

	/**
	 * DC cuwsow is stweam space, HW cuwsow is pwane space and dwawn
	 * as pawt of the fwamebuffew.
	 *
	 * Cuwsow position can't be negative, but hotspot can be used to
	 * shift cuwsow out of the pwane bounds. Hotspot must be smawwew
	 * than the cuwsow size.
	 */

	/**
	 * Twanswate cuwsow fwom stweam space to pwane space.
	 *
	 * If the cuwsow is scawed then we need to scawe the position
	 * to be in the appwoximatewy cowwect pwace. We can't do anything
	 * about the actuaw size being incowwect, that's a wimitation of
	 * the hawdwawe.
	 */
	if (pawam.wotation == WOTATION_ANGWE_90 || pawam.wotation == WOTATION_ANGWE_270) {
		x_pos = (x_pos - x_pwane) * pipe_ctx->pwane_state->swc_wect.height /
				pipe_ctx->pwane_state->dst_wect.width;
		y_pos = (y_pos - y_pwane) * pipe_ctx->pwane_state->swc_wect.width /
				pipe_ctx->pwane_state->dst_wect.height;
	} ewse {
		x_pos = (x_pos - x_pwane) * pipe_ctx->pwane_state->swc_wect.width /
				pipe_ctx->pwane_state->dst_wect.width;
		y_pos = (y_pos - y_pwane) * pipe_ctx->pwane_state->swc_wect.height /
				pipe_ctx->pwane_state->dst_wect.height;
	}

	/**
	 * If the cuwsow's souwce viewpowt is cwipped then we need to
	 * twanswate the cuwsow to appeaw in the cowwect position on
	 * the scween.
	 *
	 * This twanswation isn't affected by scawing so it needs to be
	 * done *aftew* we adjust the position fow the scawe factow.
	 *
	 * This is onwy done by opt-in fow now since thewe awe stiww
	 * some usecases wike tiwed dispway that might enabwe the
	 * cuwsow on both stweams whiwe expecting dc to cwip it.
	 */
	if (pos_cpy.twanswate_by_souwce) {
		x_pos += pipe_ctx->pwane_state->swc_wect.x;
		y_pos += pipe_ctx->pwane_state->swc_wect.y;
	}

	/**
	 * If the position is negative then we need to add to the hotspot
	 * to shift the cuwsow outside the pwane.
	 */

	if (x_pos < 0) {
		pos_cpy.x_hotspot -= x_pos;
		x_pos = 0;
	}

	if (y_pos < 0) {
		pos_cpy.y_hotspot -= y_pos;
		y_pos = 0;
	}

	pos_cpy.x = (uint32_t)x_pos;
	pos_cpy.y = (uint32_t)y_pos;

	if (pipe_ctx->pwane_state->addwess.type
			== PWN_ADDW_TYPE_VIDEO_PWOGWESSIVE)
		pos_cpy.enabwe = fawse;

	if (pos_cpy.enabwe && dcn10_can_pipe_disabwe_cuwsow(pipe_ctx))
		pos_cpy.enabwe = fawse;


	if (pawam.wotation == WOTATION_ANGWE_0) {
		int viewpowt_width =
			pipe_ctx->pwane_wes.scw_data.viewpowt.width;
		int viewpowt_x =
			pipe_ctx->pwane_wes.scw_data.viewpowt.x;

		if (pawam.miwwow) {
			if (pipe_spwit_on || odm_combine_on) {
				if (pos_cpy.x >= viewpowt_width + viewpowt_x) {
					pos_cpy.x = 2 * viewpowt_width
							- pos_cpy.x + 2 * viewpowt_x;
				} ewse {
					uint32_t temp_x = pos_cpy.x;

					pos_cpy.x = 2 * viewpowt_x - pos_cpy.x;
					if (temp_x >= viewpowt_x +
						(int)hubp->cuws_attw.width || pos_cpy.x
						<= (int)hubp->cuws_attw.width +
						pipe_ctx->pwane_state->swc_wect.x) {
						pos_cpy.x = temp_x + viewpowt_width;
					}
				}
			} ewse {
				pos_cpy.x = viewpowt_width - pos_cpy.x + 2 * viewpowt_x;
			}
		}
	}
	// Swap axis and miwwow howizontawwy
	ewse if (pawam.wotation == WOTATION_ANGWE_90) {
		uint32_t temp_x = pos_cpy.x;

		pos_cpy.x = pipe_ctx->pwane_wes.scw_data.viewpowt.width -
				(pos_cpy.y - pipe_ctx->pwane_wes.scw_data.viewpowt.x) + pipe_ctx->pwane_wes.scw_data.viewpowt.x;
		pos_cpy.y = temp_x;
	}
	// Swap axis and miwwow vewticawwy
	ewse if (pawam.wotation == WOTATION_ANGWE_270) {
		uint32_t temp_y = pos_cpy.y;
		int viewpowt_height =
			pipe_ctx->pwane_wes.scw_data.viewpowt.height;
		int viewpowt_y =
			pipe_ctx->pwane_wes.scw_data.viewpowt.y;

		/**
		 * Dispway gwoups that awe 1xnY, have pos_cpy.x > 2 * viewpowt.height
		 * Fow pipe spwit cases:
		 * - appwy offset of viewpowt.y to nowmawize pos_cpy.x
		 * - cawcuwate the pos_cpy.y as befowe
		 * - shift pos_cpy.y back by same offset to get finaw vawue
		 * - since we itewate thwough both pipes, use the wowew
		 *   viewpowt.y fow offset
		 * Fow non pipe spwit cases, use the same cawcuwation fow
		 *  pos_cpy.y as the 180 degwee wotation case bewow,
		 *  but use pos_cpy.x as ouw input because we awe wotating
		 *  270 degwees
		 */
		if (pipe_spwit_on || odm_combine_on) {
			int pos_cpy_x_offset;
			int othew_pipe_viewpowt_y;

			if (pipe_spwit_on) {
				if (pipe_ctx->bottom_pipe) {
					othew_pipe_viewpowt_y =
						pipe_ctx->bottom_pipe->pwane_wes.scw_data.viewpowt.y;
				} ewse {
					othew_pipe_viewpowt_y =
						pipe_ctx->top_pipe->pwane_wes.scw_data.viewpowt.y;
				}
			} ewse {
				if (pipe_ctx->next_odm_pipe) {
					othew_pipe_viewpowt_y =
						pipe_ctx->next_odm_pipe->pwane_wes.scw_data.viewpowt.y;
				} ewse {
					othew_pipe_viewpowt_y =
						pipe_ctx->pwev_odm_pipe->pwane_wes.scw_data.viewpowt.y;
				}
			}
			pos_cpy_x_offset = (viewpowt_y > othew_pipe_viewpowt_y) ?
				othew_pipe_viewpowt_y : viewpowt_y;
			pos_cpy.x -= pos_cpy_x_offset;
			if (pos_cpy.x > viewpowt_height) {
				pos_cpy.x = pos_cpy.x - viewpowt_height;
				pos_cpy.y = viewpowt_height - pos_cpy.x;
			} ewse {
				pos_cpy.y = 2 * viewpowt_height - pos_cpy.x;
			}
			pos_cpy.y += pos_cpy_x_offset;
		} ewse {
			pos_cpy.y = (2 * viewpowt_y) + viewpowt_height - pos_cpy.x;
		}
		pos_cpy.x = temp_y;
	}
	// Miwwow howizontawwy and vewticawwy
	ewse if (pawam.wotation == WOTATION_ANGWE_180) {
		int viewpowt_width =
			pipe_ctx->pwane_wes.scw_data.viewpowt.width;
		int viewpowt_x =
			pipe_ctx->pwane_wes.scw_data.viewpowt.x;

		if (!pawam.miwwow) {
			if (pipe_spwit_on || odm_combine_on) {
				if (pos_cpy.x >= viewpowt_width + viewpowt_x) {
					pos_cpy.x = 2 * viewpowt_width
							- pos_cpy.x + 2 * viewpowt_x;
				} ewse {
					uint32_t temp_x = pos_cpy.x;

					pos_cpy.x = 2 * viewpowt_x - pos_cpy.x;
					if (temp_x >= viewpowt_x +
						(int)hubp->cuws_attw.width || pos_cpy.x
						<= (int)hubp->cuws_attw.width +
						pipe_ctx->pwane_state->swc_wect.x) {
						pos_cpy.x = 2 * viewpowt_width - temp_x;
					}
				}
			} ewse {
				pos_cpy.x = viewpowt_width - pos_cpy.x + 2 * viewpowt_x;
			}
		}

		/**
		 * Dispway gwoups that awe 1xnY, have pos_cpy.y > viewpowt.height
		 * Cawcuwation:
		 *   dewta_fwom_bottom = viewpowt.y + viewpowt.height - pos_cpy.y
		 *   pos_cpy.y_new = viewpowt.y + dewta_fwom_bottom
		 * Simpwify it as:
		 *   pos_cpy.y = viewpowt.y * 2 + viewpowt.height - pos_cpy.y
		 */
		pos_cpy.y = (2 * pipe_ctx->pwane_wes.scw_data.viewpowt.y) +
			pipe_ctx->pwane_wes.scw_data.viewpowt.height - pos_cpy.y;
	}

	hubp->funcs->set_cuwsow_position(hubp, &pos_cpy, &pawam);
	dpp->funcs->set_cuwsow_position(dpp, &pos_cpy, &pawam, hubp->cuws_attw.width, hubp->cuws_attw.height);
}

void dcn10_set_cuwsow_attwibute(stwuct pipe_ctx *pipe_ctx)
{
	stwuct dc_cuwsow_attwibutes *attwibutes = &pipe_ctx->stweam->cuwsow_attwibutes;

	pipe_ctx->pwane_wes.hubp->funcs->set_cuwsow_attwibutes(
			pipe_ctx->pwane_wes.hubp, attwibutes);
	pipe_ctx->pwane_wes.dpp->funcs->set_cuwsow_attwibutes(
		pipe_ctx->pwane_wes.dpp, attwibutes);
}

void dcn10_set_cuwsow_sdw_white_wevew(stwuct pipe_ctx *pipe_ctx)
{
	uint32_t sdw_white_wevew = pipe_ctx->stweam->cuwsow_attwibutes.sdw_white_wevew;
	stwuct fixed31_32 muwtipwiew;
	stwuct dpp_cuwsow_attwibutes opt_attw = { 0 };
	uint32_t hw_scawe = 0x3c00; // 1.0 defauwt muwtipwiew
	stwuct custom_fwoat_fowmat fmt;

	if (!pipe_ctx->pwane_wes.dpp->funcs->set_optionaw_cuwsow_attwibutes)
		wetuwn;

	fmt.exponenta_bits = 5;
	fmt.mantissa_bits = 10;
	fmt.sign = twue;

	if (sdw_white_wevew > 80) {
		muwtipwiew = dc_fixpt_fwom_fwaction(sdw_white_wevew, 80);
		convewt_to_custom_fwoat_fowmat(muwtipwiew, &fmt, &hw_scawe);
	}

	opt_attw.scawe = hw_scawe;
	opt_attw.bias = 0;

	pipe_ctx->pwane_wes.dpp->funcs->set_optionaw_cuwsow_attwibutes(
			pipe_ctx->pwane_wes.dpp, &opt_attw);
}

/*
 * appwy_fwont_powch_wowkawound  TODO FPGA stiww need?
 *
 * This is a wowkawound fow a bug that has existed since W5xx and has not been
 * fixed keep Fwont powch at minimum 2 fow Intewwaced mode ow 1 fow pwogwessive.
 */
static void appwy_fwont_powch_wowkawound(
	stwuct dc_cwtc_timing *timing)
{
	if (timing->fwags.INTEWWACE == 1) {
		if (timing->v_fwont_powch < 2)
			timing->v_fwont_powch = 2;
	} ewse {
		if (timing->v_fwont_powch < 1)
			timing->v_fwont_powch = 1;
	}
}

int dcn10_get_vupdate_offset_fwom_vsync(stwuct pipe_ctx *pipe_ctx)
{
	const stwuct dc_cwtc_timing *dc_cwtc_timing = &pipe_ctx->stweam->timing;
	stwuct dc_cwtc_timing patched_cwtc_timing;
	int vesa_sync_stawt;
	int asic_bwank_end;
	int intewwace_factow;

	patched_cwtc_timing = *dc_cwtc_timing;
	appwy_fwont_powch_wowkawound(&patched_cwtc_timing);

	intewwace_factow = patched_cwtc_timing.fwags.INTEWWACE ? 2 : 1;

	vesa_sync_stawt = patched_cwtc_timing.v_addwessabwe +
			patched_cwtc_timing.v_bowdew_bottom +
			patched_cwtc_timing.v_fwont_powch;

	asic_bwank_end = (patched_cwtc_timing.v_totaw -
			vesa_sync_stawt -
			patched_cwtc_timing.v_bowdew_top)
			* intewwace_factow;

	wetuwn asic_bwank_end -
			pipe_ctx->pipe_dwg_pawam.vstawtup_stawt + 1;
}

void dcn10_cawc_vupdate_position(
		stwuct dc *dc,
		stwuct pipe_ctx *pipe_ctx,
		uint32_t *stawt_wine,
		uint32_t *end_wine)
{
	const stwuct dc_cwtc_timing *timing = &pipe_ctx->stweam->timing;
	int vupdate_pos = dc->hwss.get_vupdate_offset_fwom_vsync(pipe_ctx);

	if (vupdate_pos >= 0)
		*stawt_wine = vupdate_pos - ((vupdate_pos / timing->v_totaw) * timing->v_totaw);
	ewse
		*stawt_wine = vupdate_pos + ((-vupdate_pos / timing->v_totaw) + 1) * timing->v_totaw - 1;
	*end_wine = (*stawt_wine + 2) % timing->v_totaw;
}

static void dcn10_caw_vwine_position(
		stwuct dc *dc,
		stwuct pipe_ctx *pipe_ctx,
		uint32_t *stawt_wine,
		uint32_t *end_wine)
{
	const stwuct dc_cwtc_timing *timing = &pipe_ctx->stweam->timing;
	int vwine_pos = pipe_ctx->stweam->pewiodic_intewwupt.wines_offset;

	if (pipe_ctx->stweam->pewiodic_intewwupt.wef_point == STAWT_V_UPDATE) {
		if (vwine_pos > 0)
			vwine_pos--;
		ewse if (vwine_pos < 0)
			vwine_pos++;

		vwine_pos += dc->hwss.get_vupdate_offset_fwom_vsync(pipe_ctx);
		if (vwine_pos >= 0)
			*stawt_wine = vwine_pos - ((vwine_pos / timing->v_totaw) * timing->v_totaw);
		ewse
			*stawt_wine = vwine_pos + ((-vwine_pos / timing->v_totaw) + 1) * timing->v_totaw - 1;
		*end_wine = (*stawt_wine + 2) % timing->v_totaw;
	} ewse if (pipe_ctx->stweam->pewiodic_intewwupt.wef_point == STAWT_V_SYNC) {
		// vsync is wine 0 so stawt_wine is just the wequested wine offset
		*stawt_wine = vwine_pos;
		*end_wine = (*stawt_wine + 2) % timing->v_totaw;
	} ewse
		ASSEWT(0);
}

void dcn10_setup_pewiodic_intewwupt(
		stwuct dc *dc,
		stwuct pipe_ctx *pipe_ctx)
{
	stwuct timing_genewatow *tg = pipe_ctx->stweam_wes.tg;
	uint32_t stawt_wine = 0;
	uint32_t end_wine = 0;

	dcn10_caw_vwine_position(dc, pipe_ctx, &stawt_wine, &end_wine);

	tg->funcs->setup_vewticaw_intewwupt0(tg, stawt_wine, end_wine);
}

void dcn10_setup_vupdate_intewwupt(stwuct dc *dc, stwuct pipe_ctx *pipe_ctx)
{
	stwuct timing_genewatow *tg = pipe_ctx->stweam_wes.tg;
	int stawt_wine = dc->hwss.get_vupdate_offset_fwom_vsync(pipe_ctx);

	if (stawt_wine < 0) {
		ASSEWT(0);
		stawt_wine = 0;
	}

	if (tg->funcs->setup_vewticaw_intewwupt2)
		tg->funcs->setup_vewticaw_intewwupt2(tg, stawt_wine);
}

void dcn10_unbwank_stweam(stwuct pipe_ctx *pipe_ctx,
		stwuct dc_wink_settings *wink_settings)
{
	stwuct encodew_unbwank_pawam pawams = {0};
	stwuct dc_stweam_state *stweam = pipe_ctx->stweam;
	stwuct dc_wink *wink = stweam->wink;
	stwuct dce_hwseq *hws = wink->dc->hwseq;

	/* onwy 3 items bewow awe used by unbwank */
	pawams.timing = pipe_ctx->stweam->timing;

	pawams.wink_settings.wink_wate = wink_settings->wink_wate;

	if (dc_is_dp_signaw(pipe_ctx->stweam->signaw)) {
		if (pawams.timing.pixew_encoding == PIXEW_ENCODING_YCBCW420)
			pawams.timing.pix_cwk_100hz /= 2;
		pipe_ctx->stweam_wes.stweam_enc->funcs->dp_unbwank(wink, pipe_ctx->stweam_wes.stweam_enc, &pawams);
	}

	if (wink->wocaw_sink && wink->wocaw_sink->sink_signaw == SIGNAW_TYPE_EDP) {
		hws->funcs.edp_backwight_contwow(wink, twue);
	}
}

void dcn10_send_immediate_sdp_message(stwuct pipe_ctx *pipe_ctx,
				const uint8_t *custom_sdp_message,
				unsigned int sdp_message_size)
{
	if (dc_is_dp_signaw(pipe_ctx->stweam->signaw)) {
		pipe_ctx->stweam_wes.stweam_enc->funcs->send_immediate_sdp_message(
				pipe_ctx->stweam_wes.stweam_enc,
				custom_sdp_message,
				sdp_message_size);
	}
}
enum dc_status dcn10_set_cwock(stwuct dc *dc,
			enum dc_cwock_type cwock_type,
			uint32_t cwk_khz,
			uint32_t stepping)
{
	stwuct dc_state *context = dc->cuwwent_state;
	stwuct dc_cwock_config cwock_cfg = {0};
	stwuct dc_cwocks *cuwwent_cwocks = &context->bw_ctx.bw.dcn.cwk;

	if (!dc->cwk_mgw || !dc->cwk_mgw->funcs->get_cwock)
		wetuwn DC_FAIW_UNSUPPOWTED_1;

	dc->cwk_mgw->funcs->get_cwock(dc->cwk_mgw,
		context, cwock_type, &cwock_cfg);

	if (cwk_khz > cwock_cfg.max_cwock_khz)
		wetuwn DC_FAIW_CWK_EXCEED_MAX;

	if (cwk_khz < cwock_cfg.min_cwock_khz)
		wetuwn DC_FAIW_CWK_BEWOW_MIN;

	if (cwk_khz < cwock_cfg.bw_wequiwequiwed_cwock_khz)
		wetuwn DC_FAIW_CWK_BEWOW_CFG_WEQUIWED;

	/*update intewnaw wequest cwock fow update cwock use*/
	if (cwock_type == DC_CWOCK_TYPE_DISPCWK)
		cuwwent_cwocks->dispcwk_khz = cwk_khz;
	ewse if (cwock_type == DC_CWOCK_TYPE_DPPCWK)
		cuwwent_cwocks->dppcwk_khz = cwk_khz;
	ewse
		wetuwn DC_EWWOW_UNEXPECTED;

	if (dc->cwk_mgw->funcs->update_cwocks)
				dc->cwk_mgw->funcs->update_cwocks(dc->cwk_mgw,
				context, twue);
	wetuwn DC_OK;

}

void dcn10_get_cwock(stwuct dc *dc,
			enum dc_cwock_type cwock_type,
			stwuct dc_cwock_config *cwock_cfg)
{
	stwuct dc_state *context = dc->cuwwent_state;

	if (dc->cwk_mgw && dc->cwk_mgw->funcs->get_cwock)
				dc->cwk_mgw->funcs->get_cwock(dc->cwk_mgw, context, cwock_type, cwock_cfg);

}

void dcn10_get_dcc_en_bits(stwuct dc *dc, int *dcc_en_bits)
{
	stwuct wesouwce_poow *poow = dc->wes_poow;
	int i;

	fow (i = 0; i < poow->pipe_count; i++) {
		stwuct hubp *hubp = poow->hubps[i];
		stwuct dcn_hubp_state *s = &(TO_DCN10_HUBP(hubp)->state);

		hubp->funcs->hubp_wead_state(hubp);

		if (!s->bwank_en)
			dcc_en_bits[i] = s->dcc_en ? 1 : 0;
	}
}
