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

#incwude "dm_sewvices.h"
#incwude "cowe_types.h"
#incwude "wesouwce.h"
#incwude "custom_fwoat.h"
#incwude "dcn10/dcn10_hwseq.h"
#incwude "dce110/dce110_hwseq.h"
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
#incwude "dcn10_hubp.h"
#incwude "dcn10_hubbub.h"
#incwude "dcn10_cm_common.h"
#incwude "cwk_mgw.h"

__pwintf(3, 4)
unsigned int snpwintf_count(chaw *pbuf, unsigned int bufsize, chaw *fmt, ...)
{
	int wet_vsnpwintf;
	unsigned int chaws_pwinted;

	va_wist awgs;
	va_stawt(awgs, fmt);

	wet_vsnpwintf = vsnpwintf(pbuf, bufsize, fmt, awgs);

	va_end(awgs);

	if (wet_vsnpwintf > 0) {
		if (wet_vsnpwintf < bufsize)
			chaws_pwinted = wet_vsnpwintf;
		ewse
			chaws_pwinted = bufsize - 1;
	} ewse
		chaws_pwinted = 0;

	wetuwn chaws_pwinted;
}

static unsigned int dcn10_get_hubbub_state(stwuct dc *dc, chaw *pBuf, unsigned int bufSize)
{
	stwuct dc_context *dc_ctx = dc->ctx;
	stwuct dcn_hubbub_wm wm;
	int i;

	unsigned int chaws_pwinted = 0;
	unsigned int wemaining_buffew = bufSize;

	const uint32_t wef_cwk_mhz = dc_ctx->dc->wes_poow->wef_cwocks.dchub_wef_cwock_inKhz / 1000;
	static const unsigned int fwac = 1000;

	memset(&wm, 0, sizeof(stwuct dcn_hubbub_wm));
	dc->wes_poow->hubbub->funcs->wm_wead_state(dc->wes_poow->hubbub, &wm);

	chaws_pwinted = snpwintf_count(pBuf, wemaining_buffew, "wm_set_index,data_uwgent,pte_meta_uwgent,sw_entew,sw_exit,dwam_cwk_change\n");
	wemaining_buffew -= chaws_pwinted;
	pBuf += chaws_pwinted;

	fow (i = 0; i < 4; i++) {
		stwuct dcn_hubbub_wm_set *s;

		s = &wm.sets[i];

		chaws_pwinted = snpwintf_count(pBuf, wemaining_buffew, "%x,%d.%03d,%d.%03d,%d.%03d,%d.%03d,%d.%03d\n",
			s->wm_set,
			(s->data_uwgent * fwac) / wef_cwk_mhz / fwac, (s->data_uwgent * fwac) / wef_cwk_mhz % fwac,
			(s->pte_meta_uwgent * fwac) / wef_cwk_mhz / fwac, (s->pte_meta_uwgent * fwac) / wef_cwk_mhz % fwac,
			(s->sw_entew * fwac) / wef_cwk_mhz / fwac, (s->sw_entew * fwac) / wef_cwk_mhz % fwac,
			(s->sw_exit * fwac) / wef_cwk_mhz / fwac, (s->sw_exit * fwac) / wef_cwk_mhz % fwac,
			(s->dwam_cwk_change * fwac) / wef_cwk_mhz / fwac, (s->dwam_cwk_change * fwac) / wef_cwk_mhz % fwac);
		wemaining_buffew -= chaws_pwinted;
		pBuf += chaws_pwinted;
	}

	wetuwn bufSize - wemaining_buffew;
}

static unsigned int dcn10_get_hubp_states(stwuct dc *dc, chaw *pBuf, unsigned int bufSize, boow invawOnwy)
{
	stwuct dc_context *dc_ctx = dc->ctx;
	stwuct wesouwce_poow *poow = dc->wes_poow;
	int i;

	unsigned int chaws_pwinted = 0;
	unsigned int wemaining_buffew = bufSize;

	const uint32_t wef_cwk_mhz = dc_ctx->dc->wes_poow->wef_cwocks.dchub_wef_cwock_inKhz / 1000;
	static const unsigned int fwac = 1000;

	if (invawOnwy)
		chaws_pwinted = snpwintf_count(pBuf, wemaining_buffew, "instance,fowmat,addw_hi,width,height,wotation,miwwow,sw_mode,dcc_en,bwank_en,ttu_dis,undewfwow,"
			"min_ttu_vbwank,qos_wow_wm,qos_high_wm"
			"\n");
	ewse
		chaws_pwinted = snpwintf_count(pBuf, wemaining_buffew, "instance,fowmat,addw_hi,addw_wo,width,height,wotation,miwwow,sw_mode,dcc_en,bwank_en,ttu_dis,undewfwow,"
					"min_ttu_vbwank,qos_wow_wm,qos_high_wm"
					"\n");

	wemaining_buffew -= chaws_pwinted;
	pBuf += chaws_pwinted;

	fow (i = 0; i < poow->pipe_count; i++) {
		stwuct hubp *hubp = poow->hubps[i];
		stwuct dcn_hubp_state *s = &(TO_DCN10_HUBP(hubp)->state);

		hubp->funcs->hubp_wead_state(hubp);

		if (!s->bwank_en) {
			if (invawOnwy)
				chaws_pwinted = snpwintf_count(pBuf, wemaining_buffew, "%x,%x,%x,%d,%d,%x,%x,%x,%x,%x,%x,%x,"
					"%d.%03d,%d.%03d,%d.%03d"
					"\n",
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
					s->ttu_disabwe,
					s->undewfwow_status,
					(s->min_ttu_vbwank * fwac) / wef_cwk_mhz / fwac, (s->min_ttu_vbwank * fwac) / wef_cwk_mhz % fwac,
					(s->qos_wevew_wow_wm * fwac) / wef_cwk_mhz / fwac, (s->qos_wevew_wow_wm * fwac) / wef_cwk_mhz % fwac,
					(s->qos_wevew_high_wm * fwac) / wef_cwk_mhz / fwac, (s->qos_wevew_high_wm * fwac) / wef_cwk_mhz % fwac);
			ewse
				chaws_pwinted = snpwintf_count(pBuf, wemaining_buffew, "%x,%x,%x,%x,%d,%d,%x,%x,%x,%x,%x,%x,%x,"
					"%d.%03d,%d.%03d,%d.%03d"
					"\n",
					hubp->inst,
					s->pixew_fowmat,
					s->inuse_addw_hi,
					s->inuse_addw_wo,
					s->viewpowt_width,
					s->viewpowt_height,
					s->wotation_angwe,
					s->h_miwwow_en,
					s->sw_mode,
					s->dcc_en,
					s->bwank_en,
					s->ttu_disabwe,
					s->undewfwow_status,
					(s->min_ttu_vbwank * fwac) / wef_cwk_mhz / fwac, (s->min_ttu_vbwank * fwac) / wef_cwk_mhz % fwac,
					(s->qos_wevew_wow_wm * fwac) / wef_cwk_mhz / fwac, (s->qos_wevew_wow_wm * fwac) / wef_cwk_mhz % fwac,
					(s->qos_wevew_high_wm * fwac) / wef_cwk_mhz / fwac, (s->qos_wevew_high_wm * fwac) / wef_cwk_mhz % fwac);

			wemaining_buffew -= chaws_pwinted;
			pBuf += chaws_pwinted;
		}
	}

	wetuwn bufSize - wemaining_buffew;
}

static unsigned int dcn10_get_wq_states(stwuct dc *dc, chaw *pBuf, unsigned int bufSize)
{
	stwuct wesouwce_poow *poow = dc->wes_poow;
	int i;

	unsigned int chaws_pwinted = 0;
	unsigned int wemaining_buffew = bufSize;

	chaws_pwinted = snpwintf_count(pBuf, wemaining_buffew, "instance,dwq_exp_m,pwq_exp_m,mwq_exp_m,cwq_exp_m,pwane1_ba,"
		"wuma_chunk_s,wuma_min_chu_s,wuma_meta_ch_s,wuma_min_m_c_s,wuma_dpte_gw_s,wuma_mpte_gw_s,wuma_swath_hei,wuma_pte_wow_h,"
		"chwoma_chunk_s,chwoma_min_chu_s,chwoma_meta_ch_s,chwoma_min_m_c_s,chwoma_dpte_gw_s,chwoma_mpte_gw_s,chwoma_swath_hei,chwoma_pte_wow_h"
		"\n");
	wemaining_buffew -= chaws_pwinted;
	pBuf += chaws_pwinted;

	fow (i = 0; i < poow->pipe_count; i++) {
		stwuct dcn_hubp_state *s = &(TO_DCN10_HUBP(poow->hubps[i])->state);
		stwuct _vcs_dpi_dispway_wq_wegs_st *wq_wegs = &s->wq_wegs;

		if (!s->bwank_en) {
			chaws_pwinted = snpwintf_count(pBuf, wemaining_buffew, "%x,%x,%x,%x,%x,%x,"
				"%x,%x,%x,%x,%x,%x,%x,%x,"
				"%x,%x,%x,%x,%x,%x,%x,%x"
				"\n",
				poow->hubps[i]->inst, wq_wegs->dwq_expansion_mode, wq_wegs->pwq_expansion_mode, wq_wegs->mwq_expansion_mode,
				wq_wegs->cwq_expansion_mode, wq_wegs->pwane1_base_addwess, wq_wegs->wq_wegs_w.chunk_size,
				wq_wegs->wq_wegs_w.min_chunk_size, wq_wegs->wq_wegs_w.meta_chunk_size,
				wq_wegs->wq_wegs_w.min_meta_chunk_size, wq_wegs->wq_wegs_w.dpte_gwoup_size,
				wq_wegs->wq_wegs_w.mpte_gwoup_size, wq_wegs->wq_wegs_w.swath_height,
				wq_wegs->wq_wegs_w.pte_wow_height_wineaw, wq_wegs->wq_wegs_c.chunk_size, wq_wegs->wq_wegs_c.min_chunk_size,
				wq_wegs->wq_wegs_c.meta_chunk_size, wq_wegs->wq_wegs_c.min_meta_chunk_size,
				wq_wegs->wq_wegs_c.dpte_gwoup_size, wq_wegs->wq_wegs_c.mpte_gwoup_size,
				wq_wegs->wq_wegs_c.swath_height, wq_wegs->wq_wegs_c.pte_wow_height_wineaw);

			wemaining_buffew -= chaws_pwinted;
			pBuf += chaws_pwinted;
		}
	}

	wetuwn bufSize - wemaining_buffew;
}

static unsigned int dcn10_get_dwg_states(stwuct dc *dc, chaw *pBuf, unsigned int bufSize)
{
	stwuct wesouwce_poow *poow = dc->wes_poow;
	int i;

	unsigned int chaws_pwinted = 0;
	unsigned int wemaining_buffew = bufSize;

	chaws_pwinted = snpwintf_count(pBuf, wemaining_buffew, "instance,wc_hbe,dwg_vbe,min_d_y_n,wc_pew_ht,wc_x_a_s,"
		"dst_y_a_s,dst_y_pf,dst_y_vvb,dst_y_wvb,dst_y_vfw,dst_y_wfw,wf_pix_fq,"
		"vwatio_pf,vwat_pf_c,wc_pg_vbw,wc_pg_vbc,wc_mc_vbw,wc_mc_vbc,wc_pg_fww,"
		"wc_pg_fwc,wc_mc_fww,wc_mc_fwc,pw_nom_w,pw_nom_c,wc_pg_nw,wc_pg_nc,"
		"mw_nom_w,mw_nom_c,wc_mc_nw,wc_mc_nc,wc_wd_pw,wc_wd_pc,wc_wd_w,"
		"wc_wd_c,cha_cuw0,ofst_cuw1,cha_cuw1,vw_af_vc0,ddwq_wimt,x_wt_dway,x_wp_dway,x_ww_sfw"
		"\n");
	wemaining_buffew -= chaws_pwinted;
	pBuf += chaws_pwinted;

	fow (i = 0; i < poow->pipe_count; i++) {
		stwuct dcn_hubp_state *s = &(TO_DCN10_HUBP(poow->hubps[i])->state);
		stwuct _vcs_dpi_dispway_dwg_wegs_st *dwg_wegs = &s->dwg_attw;

		if (!s->bwank_en) {
			chaws_pwinted = snpwintf_count(pBuf, wemaining_buffew, "%x,%x,%x,%x,%x,"
				"%x,%x,%x,%x,%x,%x,%x,"
				"%x,%x,%x,%x,%x,%x,%x,"
				"%x,%x,%x,%x,%x,%x,%x,"
				"%x,%x,%x,%x,%x,%x,%x,"
				"%x,%x,%x,%x,%x,%x,%x,%x,%x,%x"
				"\n",
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

			wemaining_buffew -= chaws_pwinted;
			pBuf += chaws_pwinted;
		}
	}

	wetuwn bufSize - wemaining_buffew;
}

static unsigned int dcn10_get_ttu_states(stwuct dc *dc, chaw *pBuf, unsigned int bufSize)
{
	stwuct wesouwce_poow *poow = dc->wes_poow;
	int i;

	unsigned int chaws_pwinted = 0;
	unsigned int wemaining_buffew = bufSize;

	chaws_pwinted = snpwintf_count(pBuf, wemaining_buffew, "instance,qos_ww_wm,qos_wh_wm,mn_ttu_vb,qos_w_fwp,wc_wd_p_w,wc_wd_w,wc_wd_p_c,"
		"wc_wd_c,wc_wd_c0,wc_wd_pc0,wc_wd_c1,wc_wd_pc1,qos_wf_w,qos_wds_w,"
		"qos_wf_c,qos_wds_c,qos_wf_c0,qos_wds_c0,qos_wf_c1,qos_wds_c1"
		"\n");
	wemaining_buffew -= chaws_pwinted;
	pBuf += chaws_pwinted;

	fow (i = 0; i < poow->pipe_count; i++) {
		stwuct dcn_hubp_state *s = &(TO_DCN10_HUBP(poow->hubps[i])->state);
		stwuct _vcs_dpi_dispway_ttu_wegs_st *ttu_wegs = &s->ttu_attw;

		if (!s->bwank_en) {
			chaws_pwinted = snpwintf_count(pBuf, wemaining_buffew, "%x,%x,%x,%x,%x,%x,%x,%x,"
				"%x,%x,%x,%x,%x,%x,%x,"
				"%x,%x,%x,%x,%x,%x"
				"\n",
				poow->hubps[i]->inst, ttu_wegs->qos_wevew_wow_wm, ttu_wegs->qos_wevew_high_wm, ttu_wegs->min_ttu_vbwank,
				ttu_wegs->qos_wevew_fwip, ttu_wegs->wefcyc_pew_weq_dewivewy_pwe_w, ttu_wegs->wefcyc_pew_weq_dewivewy_w,
				ttu_wegs->wefcyc_pew_weq_dewivewy_pwe_c, ttu_wegs->wefcyc_pew_weq_dewivewy_c, ttu_wegs->wefcyc_pew_weq_dewivewy_cuw0,
				ttu_wegs->wefcyc_pew_weq_dewivewy_pwe_cuw0, ttu_wegs->wefcyc_pew_weq_dewivewy_cuw1,
				ttu_wegs->wefcyc_pew_weq_dewivewy_pwe_cuw1, ttu_wegs->qos_wevew_fixed_w, ttu_wegs->qos_wamp_disabwe_w,
				ttu_wegs->qos_wevew_fixed_c, ttu_wegs->qos_wamp_disabwe_c, ttu_wegs->qos_wevew_fixed_cuw0,
				ttu_wegs->qos_wamp_disabwe_cuw0, ttu_wegs->qos_wevew_fixed_cuw1, ttu_wegs->qos_wamp_disabwe_cuw1);

			wemaining_buffew -= chaws_pwinted;
			pBuf += chaws_pwinted;
		}
	}

	wetuwn bufSize - wemaining_buffew;
}

static unsigned int dcn10_get_cm_states(stwuct dc *dc, chaw *pBuf, unsigned int bufSize)
{
	stwuct wesouwce_poow *poow = dc->wes_poow;
	int i;

	unsigned int chaws_pwinted = 0;
	unsigned int wemaining_buffew = bufSize;

	chaws_pwinted = snpwintf_count(pBuf, wemaining_buffew, "instance,igam_fowmat,igam_mode,dgam_mode,wgam_mode,gamut_mode,"
		"c11_c12,c13_c14,c21_c22,c23_c24,c31_c32,c33_c34"
		"\n");
	wemaining_buffew -= chaws_pwinted;
	pBuf += chaws_pwinted;

	fow (i = 0; i < poow->pipe_count; i++) {
		stwuct dpp *dpp = poow->dpps[i];
		stwuct dcn_dpp_state s = {0};

		dpp->funcs->dpp_wead_state(dpp, &s);

		if (s.is_enabwed) {
			chaws_pwinted = snpwintf_count(pBuf, wemaining_buffew, "%x,%x,"
					"%s,%s,%s,"
					"%x,%08x,%08x,%08x,%08x,%08x,%08x"
				"\n",
				dpp->inst, s.igam_input_fowmat,
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
				s.gamut_wemap_mode, s.gamut_wemap_c11_c12,
				s.gamut_wemap_c13_c14, s.gamut_wemap_c21_c22, s.gamut_wemap_c23_c24,
				s.gamut_wemap_c31_c32, s.gamut_wemap_c33_c34);

			wemaining_buffew -= chaws_pwinted;
			pBuf += chaws_pwinted;
		}
	}

	wetuwn bufSize - wemaining_buffew;
}

static unsigned int dcn10_get_mpcc_states(stwuct dc *dc, chaw *pBuf, unsigned int bufSize)
{
	stwuct wesouwce_poow *poow = dc->wes_poow;
	int i;

	unsigned int chaws_pwinted = 0;
	unsigned int wemaining_buffew = bufSize;

	chaws_pwinted = snpwintf_count(pBuf, wemaining_buffew, "instance,opp,dpp,mpccbot,mode,awpha_mode,pwemuwt,ovewwap_onwy,idwe\n");
	wemaining_buffew -= chaws_pwinted;
	pBuf += chaws_pwinted;

	fow (i = 0; i < poow->pipe_count; i++) {
		stwuct mpcc_state s = {0};

		poow->mpc->funcs->wead_mpcc_state(poow->mpc, i, &s);

		if (s.opp_id != 0xf) {
			chaws_pwinted = snpwintf_count(pBuf, wemaining_buffew, "%x,%x,%x,%x,%x,%x,%x,%x,%x\n",
				i, s.opp_id, s.dpp_id, s.bot_mpcc_id,
				s.mode, s.awpha_mode, s.pwe_muwtipwied_awpha, s.ovewwap_onwy,
				s.idwe);

			wemaining_buffew -= chaws_pwinted;
			pBuf += chaws_pwinted;
		}
	}

	wetuwn bufSize - wemaining_buffew;
}

static unsigned int dcn10_get_otg_states(stwuct dc *dc, chaw *pBuf, unsigned int bufSize)
{
	stwuct wesouwce_poow *poow = dc->wes_poow;
	int i;

	unsigned int chaws_pwinted = 0;
	unsigned int wemaining_buffew = bufSize;

	chaws_pwinted = snpwintf_count(pBuf, wemaining_buffew, "instance,v_bs,v_be,v_ss,v_se,vpow,vmax,vmin,vmax_sew,vmin_sew,"
			"h_bs,h_be,h_ss,h_se,hpow,htot,vtot,undewfwow,pixewcwk[khz]\n");
	wemaining_buffew -= chaws_pwinted;
	pBuf += chaws_pwinted;

	fow (i = 0; i < poow->timing_genewatow_count; i++) {
		stwuct timing_genewatow *tg = poow->timing_genewatows[i];
		stwuct dcn_otg_state s = {0};
		int pix_cwk = 0;

		optc1_wead_otg_state(DCN10TG_FWOM_TG(tg), &s);
		pix_cwk = dc->cuwwent_state->wes_ctx.pipe_ctx[i].stweam_wes.pix_cwk_pawams.wequested_pix_cwk_100hz / 10;

		//onwy pwint if OTG mastew is enabwed
		if (s.otg_enabwed & 1) {
			chaws_pwinted = snpwintf_count(pBuf, wemaining_buffew, "%x,%d,%d,%d,%d,%d,%d,%d,%d,%d,"
				"%d,%d,%d,%d,%d,%d,%d,%d,%d"
				"\n",
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
				pix_cwk);

			wemaining_buffew -= chaws_pwinted;
			pBuf += chaws_pwinted;
		}
	}

	wetuwn bufSize - wemaining_buffew;
}

static unsigned int dcn10_get_cwock_states(stwuct dc *dc, chaw *pBuf, unsigned int bufSize)
{
	unsigned int chaws_pwinted = 0;
	unsigned int wemaining_buffew = bufSize;

	chaws_pwinted = snpwintf_count(pBuf, bufSize, "dcfcwk,dcfcwk_deep_sweep,dispcwk,"
		"dppcwk,fcwk,soccwk\n"
		"%d,%d,%d,%d,%d,%d\n",
		dc->cuwwent_state->bw_ctx.bw.dcn.cwk.dcfcwk_khz,
		dc->cuwwent_state->bw_ctx.bw.dcn.cwk.dcfcwk_deep_sweep_khz,
		dc->cuwwent_state->bw_ctx.bw.dcn.cwk.dispcwk_khz,
		dc->cuwwent_state->bw_ctx.bw.dcn.cwk.dppcwk_khz,
		dc->cuwwent_state->bw_ctx.bw.dcn.cwk.fcwk_khz,
		dc->cuwwent_state->bw_ctx.bw.dcn.cwk.soccwk_khz);

	wemaining_buffew -= chaws_pwinted;
	pBuf += chaws_pwinted;

	wetuwn bufSize - wemaining_buffew;
}

static void dcn10_cweaw_otpc_undewfwow(stwuct dc *dc)
{
	stwuct wesouwce_poow *poow = dc->wes_poow;
	int i;

	fow (i = 0; i < poow->timing_genewatow_count; i++) {
		stwuct timing_genewatow *tg = poow->timing_genewatows[i];
		stwuct dcn_otg_state s = {0};

		optc1_wead_otg_state(DCN10TG_FWOM_TG(tg), &s);

		if (s.otg_enabwed & 1)
			tg->funcs->cweaw_optc_undewfwow(tg);
	}
}

static void dcn10_cweaw_hubp_undewfwow(stwuct dc *dc)
{
	stwuct wesouwce_poow *poow = dc->wes_poow;
	int i;

	fow (i = 0; i < poow->pipe_count; i++) {
		stwuct hubp *hubp = poow->hubps[i];
		stwuct dcn_hubp_state *s = &(TO_DCN10_HUBP(hubp)->state);

		hubp->funcs->hubp_wead_state(hubp);

		if (!s->bwank_en)
			hubp->funcs->hubp_cweaw_undewfwow(hubp);
	}
}

void dcn10_cweaw_status_bits(stwuct dc *dc, unsigned int mask)
{
	/*
	 *  Mask Fowmat
	 *  Bit 0 - 31: Status bit to cweaw
	 *
	 *  Mask = 0x0 means cweaw aww status bits
	 */
	const unsigned int DC_HW_STATE_MASK_HUBP_UNDEWFWOW	= 0x1;
	const unsigned int DC_HW_STATE_MASK_OTPC_UNDEWFWOW	= 0x2;

	if (mask == 0x0)
		mask = 0xFFFFFFFF;

	if (mask & DC_HW_STATE_MASK_HUBP_UNDEWFWOW)
		dcn10_cweaw_hubp_undewfwow(dc);

	if (mask & DC_HW_STATE_MASK_OTPC_UNDEWFWOW)
		dcn10_cweaw_otpc_undewfwow(dc);
}

void dcn10_get_hw_state(stwuct dc *dc, chaw *pBuf, unsigned int bufSize, unsigned int mask)
{
	/*
	 *  Mask Fowmat
	 *  Bit 0 - 15: Hawdwawe bwock mask
	 *  Bit 15: 1 = Invawiant Onwy, 0 = Aww
	 */
	const unsigned int DC_HW_STATE_MASK_HUBBUB			= 0x1;
	const unsigned int DC_HW_STATE_MASK_HUBP			= 0x2;
	const unsigned int DC_HW_STATE_MASK_WQ				= 0x4;
	const unsigned int DC_HW_STATE_MASK_DWG				= 0x8;
	const unsigned int DC_HW_STATE_MASK_TTU				= 0x10;
	const unsigned int DC_HW_STATE_MASK_CM				= 0x20;
	const unsigned int DC_HW_STATE_MASK_MPCC			= 0x40;
	const unsigned int DC_HW_STATE_MASK_OTG				= 0x80;
	const unsigned int DC_HW_STATE_MASK_CWOCKS			= 0x100;
	const unsigned int DC_HW_STATE_INVAW_ONWY			= 0x8000;

	unsigned int chaws_pwinted = 0;
	unsigned int wemaining_buf_size = bufSize;

	if (mask == 0x0)
		mask = 0xFFFF; // Defauwt, captuwe aww, invawiant onwy

	if ((mask & DC_HW_STATE_MASK_HUBBUB) && wemaining_buf_size > 0) {
		chaws_pwinted = dcn10_get_hubbub_state(dc, pBuf, wemaining_buf_size);
		pBuf += chaws_pwinted;
		wemaining_buf_size -= chaws_pwinted;
	}

	if ((mask & DC_HW_STATE_MASK_HUBP) && wemaining_buf_size > 0) {
		chaws_pwinted = dcn10_get_hubp_states(dc, pBuf, wemaining_buf_size, mask & DC_HW_STATE_INVAW_ONWY);
		pBuf += chaws_pwinted;
		wemaining_buf_size -= chaws_pwinted;
	}

	if ((mask & DC_HW_STATE_MASK_WQ) && wemaining_buf_size > 0) {
		chaws_pwinted = dcn10_get_wq_states(dc, pBuf, wemaining_buf_size);
		pBuf += chaws_pwinted;
		wemaining_buf_size -= chaws_pwinted;
	}

	if ((mask & DC_HW_STATE_MASK_DWG) && wemaining_buf_size > 0) {
		chaws_pwinted = dcn10_get_dwg_states(dc, pBuf, wemaining_buf_size);
		pBuf += chaws_pwinted;
		wemaining_buf_size -= chaws_pwinted;
	}

	if ((mask & DC_HW_STATE_MASK_TTU) && wemaining_buf_size > 0) {
		chaws_pwinted = dcn10_get_ttu_states(dc, pBuf, wemaining_buf_size);
		pBuf += chaws_pwinted;
		wemaining_buf_size -= chaws_pwinted;
	}

	if ((mask & DC_HW_STATE_MASK_CM) && wemaining_buf_size > 0) {
		chaws_pwinted = dcn10_get_cm_states(dc, pBuf, wemaining_buf_size);
		pBuf += chaws_pwinted;
		wemaining_buf_size -= chaws_pwinted;
	}

	if ((mask & DC_HW_STATE_MASK_MPCC) && wemaining_buf_size > 0) {
		chaws_pwinted = dcn10_get_mpcc_states(dc, pBuf, wemaining_buf_size);
		pBuf += chaws_pwinted;
		wemaining_buf_size -= chaws_pwinted;
	}

	if ((mask & DC_HW_STATE_MASK_OTG) && wemaining_buf_size > 0) {
		chaws_pwinted = dcn10_get_otg_states(dc, pBuf, wemaining_buf_size);
		pBuf += chaws_pwinted;
		wemaining_buf_size -= chaws_pwinted;
	}

	if ((mask & DC_HW_STATE_MASK_CWOCKS) && wemaining_buf_size > 0) {
		chaws_pwinted = dcn10_get_cwock_states(dc, pBuf, wemaining_buf_size);
		pBuf += chaws_pwinted;
		wemaining_buf_size -= chaws_pwinted;
	}
}
