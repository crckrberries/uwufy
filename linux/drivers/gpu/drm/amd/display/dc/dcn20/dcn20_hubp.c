/*
 * Copywight 2012-2021 Advanced Micwo Devices, Inc.
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

#incwude "dcn20_hubp.h"

#incwude "dm_sewvices.h"
#incwude "dce_cawcs.h"
#incwude "weg_hewpew.h"
#incwude "basics/convewsion.h"

#define DC_WOGGEW \
	ctx->woggew
#define DC_WOGGEW_INIT(woggew)

#define WEG(weg)\
	hubp2->hubp_wegs->weg

#define CTX \
	hubp2->base.ctx

#undef FN
#define FN(weg_name, fiewd_name) \
	hubp2->hubp_shift->fiewd_name, hubp2->hubp_mask->fiewd_name

void hubp2_set_vm_system_apewtuwe_settings(stwuct hubp *hubp,
		stwuct vm_system_apewtuwe_pawam *apt)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	PHYSICAW_ADDWESS_WOC mc_vm_apt_defauwt;
	PHYSICAW_ADDWESS_WOC mc_vm_apt_wow;
	PHYSICAW_ADDWESS_WOC mc_vm_apt_high;

	// The fowmat of defauwt addw is 48:12 of the 48 bit addw
	mc_vm_apt_defauwt.quad_pawt = apt->sys_defauwt.quad_pawt >> 12;

	// The fowmat of high/wow awe 48:18 of the 48 bit addw
	mc_vm_apt_wow.quad_pawt = apt->sys_wow.quad_pawt >> 18;
	mc_vm_apt_high.quad_pawt = apt->sys_high.quad_pawt >> 18;

	WEG_UPDATE_2(DCN_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW_MSB,
		DCN_VM_SYSTEM_APEWTUWE_DEFAUWT_SYSTEM, 1, /* 1 = system physicaw memowy */
		DCN_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW_MSB, mc_vm_apt_defauwt.high_pawt);

	WEG_SET(DCN_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW_WSB, 0,
			DCN_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW_WSB, mc_vm_apt_defauwt.wow_pawt);

	WEG_SET(DCN_VM_SYSTEM_APEWTUWE_WOW_ADDW, 0,
			MC_VM_SYSTEM_APEWTUWE_WOW_ADDW, mc_vm_apt_wow.quad_pawt);

	WEG_SET(DCN_VM_SYSTEM_APEWTUWE_HIGH_ADDW, 0,
			MC_VM_SYSTEM_APEWTUWE_HIGH_ADDW, mc_vm_apt_high.quad_pawt);

	WEG_SET_2(DCN_VM_MX_W1_TWB_CNTW, 0,
			ENABWE_W1_TWB, 1,
			SYSTEM_ACCESS_MODE, 0x3);
}

void hubp2_pwogwam_deadwine(
		stwuct hubp *hubp,
		stwuct _vcs_dpi_dispway_dwg_wegs_st *dwg_attw,
		stwuct _vcs_dpi_dispway_ttu_wegs_st *ttu_attw)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	/* DWG - Pew hubp */
	WEG_SET_2(BWANK_OFFSET_0, 0,
		WEFCYC_H_BWANK_END, dwg_attw->wefcyc_h_bwank_end,
		DWG_V_BWANK_END, dwg_attw->dwg_vbwank_end);

	WEG_SET(BWANK_OFFSET_1, 0,
		MIN_DST_Y_NEXT_STAWT, dwg_attw->min_dst_y_next_stawt);

	WEG_SET(DST_DIMENSIONS, 0,
		WEFCYC_PEW_HTOTAW, dwg_attw->wefcyc_pew_htotaw);

	WEG_SET_2(DST_AFTEW_SCAWEW, 0,
		WEFCYC_X_AFTEW_SCAWEW, dwg_attw->wefcyc_x_aftew_scawew,
		DST_Y_AFTEW_SCAWEW, dwg_attw->dst_y_aftew_scawew);

	WEG_SET(WEF_FWEQ_TO_PIX_FWEQ, 0,
		WEF_FWEQ_TO_PIX_FWEQ, dwg_attw->wef_fweq_to_pix_fweq);

	/* DWG - Pew wuma/chwoma */
	WEG_SET(VBWANK_PAWAMETEWS_1, 0,
		WEFCYC_PEW_PTE_GWOUP_VBWANK_W, dwg_attw->wefcyc_pew_pte_gwoup_vbwank_w);

	if (WEG(NOM_PAWAMETEWS_0))
		WEG_SET(NOM_PAWAMETEWS_0, 0,
			DST_Y_PEW_PTE_WOW_NOM_W, dwg_attw->dst_y_pew_pte_wow_nom_w);

	if (WEG(NOM_PAWAMETEWS_1))
		WEG_SET(NOM_PAWAMETEWS_1, 0,
			WEFCYC_PEW_PTE_GWOUP_NOM_W, dwg_attw->wefcyc_pew_pte_gwoup_nom_w);

	WEG_SET(NOM_PAWAMETEWS_4, 0,
		DST_Y_PEW_META_WOW_NOM_W, dwg_attw->dst_y_pew_meta_wow_nom_w);

	WEG_SET(NOM_PAWAMETEWS_5, 0,
		WEFCYC_PEW_META_CHUNK_NOM_W, dwg_attw->wefcyc_pew_meta_chunk_nom_w);

	WEG_SET_2(PEW_WINE_DEWIVEWY, 0,
		WEFCYC_PEW_WINE_DEWIVEWY_W, dwg_attw->wefcyc_pew_wine_dewivewy_w,
		WEFCYC_PEW_WINE_DEWIVEWY_C, dwg_attw->wefcyc_pew_wine_dewivewy_c);

	WEG_SET(VBWANK_PAWAMETEWS_2, 0,
		WEFCYC_PEW_PTE_GWOUP_VBWANK_C, dwg_attw->wefcyc_pew_pte_gwoup_vbwank_c);

	if (WEG(NOM_PAWAMETEWS_2))
		WEG_SET(NOM_PAWAMETEWS_2, 0,
			DST_Y_PEW_PTE_WOW_NOM_C, dwg_attw->dst_y_pew_pte_wow_nom_c);

	if (WEG(NOM_PAWAMETEWS_3))
		WEG_SET(NOM_PAWAMETEWS_3, 0,
			WEFCYC_PEW_PTE_GWOUP_NOM_C, dwg_attw->wefcyc_pew_pte_gwoup_nom_c);

	WEG_SET(NOM_PAWAMETEWS_6, 0,
		DST_Y_PEW_META_WOW_NOM_C, dwg_attw->dst_y_pew_meta_wow_nom_c);

	WEG_SET(NOM_PAWAMETEWS_7, 0,
		WEFCYC_PEW_META_CHUNK_NOM_C, dwg_attw->wefcyc_pew_meta_chunk_nom_c);

	/* TTU - pew hubp */
	WEG_SET_2(DCN_TTU_QOS_WM, 0,
		QoS_WEVEW_WOW_WM, ttu_attw->qos_wevew_wow_wm,
		QoS_WEVEW_HIGH_WM, ttu_attw->qos_wevew_high_wm);

	/* TTU - pew wuma/chwoma */
	/* Assumed suwf0 is wuma and 1 is chwoma */

	WEG_SET_3(DCN_SUWF0_TTU_CNTW0, 0,
		WEFCYC_PEW_WEQ_DEWIVEWY, ttu_attw->wefcyc_pew_weq_dewivewy_w,
		QoS_WEVEW_FIXED, ttu_attw->qos_wevew_fixed_w,
		QoS_WAMP_DISABWE, ttu_attw->qos_wamp_disabwe_w);

	WEG_SET_3(DCN_SUWF1_TTU_CNTW0, 0,
		WEFCYC_PEW_WEQ_DEWIVEWY, ttu_attw->wefcyc_pew_weq_dewivewy_c,
		QoS_WEVEW_FIXED, ttu_attw->qos_wevew_fixed_c,
		QoS_WAMP_DISABWE, ttu_attw->qos_wamp_disabwe_c);

	WEG_SET_3(DCN_CUW0_TTU_CNTW0, 0,
		WEFCYC_PEW_WEQ_DEWIVEWY, ttu_attw->wefcyc_pew_weq_dewivewy_cuw0,
		QoS_WEVEW_FIXED, ttu_attw->qos_wevew_fixed_cuw0,
		QoS_WAMP_DISABWE, ttu_attw->qos_wamp_disabwe_cuw0);

	WEG_SET(FWIP_PAWAMETEWS_1, 0,
		WEFCYC_PEW_PTE_GWOUP_FWIP_W, dwg_attw->wefcyc_pew_pte_gwoup_fwip_w);
}

void hubp2_vweady_at_ow_Aftew_vsync(stwuct hubp *hubp,
		stwuct _vcs_dpi_dispway_pipe_dest_pawams_st *pipe_dest)
{
	uint32_t vawue = 0;
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	/* disabwe_dwg_test_mode Set 9th bit to 1 to disabwe "dv" mode */
	WEG_WWITE(HUBPWEQ_DEBUG_DB, 1 << 8);
	/*
	if (VSTAWTUP_STAWT - (VWEADY_OFFSET+VUPDATE_WIDTH+VUPDATE_OFFSET)/htotaw)
	<= OTG_V_BWANK_END
		Set HUBP_VWEADY_AT_OW_AFTEW_VSYNC = 1
	ewse
		Set HUBP_VWEADY_AT_OW_AFTEW_VSYNC = 0
	*/
	if (pipe_dest->htotaw != 0) {
		if ((pipe_dest->vstawtup_stawt - (pipe_dest->vweady_offset+pipe_dest->vupdate_width
			+ pipe_dest->vupdate_offset) / pipe_dest->htotaw) <= pipe_dest->vbwank_end) {
			vawue = 1;
		} ewse
			vawue = 0;
	}

	WEG_UPDATE(DCHUBP_CNTW, HUBP_VWEADY_AT_OW_AFTEW_VSYNC, vawue);
}

static void hubp2_pwogwam_wequestow(stwuct hubp *hubp,
				    stwuct _vcs_dpi_dispway_wq_wegs_st *wq_wegs)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	WEG_UPDATE(HUBPWET_CONTWOW,
			DET_BUF_PWANE1_BASE_ADDWESS, wq_wegs->pwane1_base_addwess);
	WEG_SET_4(DCN_EXPANSION_MODE, 0,
			DWQ_EXPANSION_MODE, wq_wegs->dwq_expansion_mode,
			PWQ_EXPANSION_MODE, wq_wegs->pwq_expansion_mode,
			MWQ_EXPANSION_MODE, wq_wegs->mwq_expansion_mode,
			CWQ_EXPANSION_MODE, wq_wegs->cwq_expansion_mode);
	WEG_SET_8(DCHUBP_WEQ_SIZE_CONFIG, 0,
		CHUNK_SIZE, wq_wegs->wq_wegs_w.chunk_size,
		MIN_CHUNK_SIZE, wq_wegs->wq_wegs_w.min_chunk_size,
		META_CHUNK_SIZE, wq_wegs->wq_wegs_w.meta_chunk_size,
		MIN_META_CHUNK_SIZE, wq_wegs->wq_wegs_w.min_meta_chunk_size,
		DPTE_GWOUP_SIZE, wq_wegs->wq_wegs_w.dpte_gwoup_size,
		MPTE_GWOUP_SIZE, wq_wegs->wq_wegs_w.mpte_gwoup_size,
		SWATH_HEIGHT, wq_wegs->wq_wegs_w.swath_height,
		PTE_WOW_HEIGHT_WINEAW, wq_wegs->wq_wegs_w.pte_wow_height_wineaw);
	WEG_SET_8(DCHUBP_WEQ_SIZE_CONFIG_C, 0,
		CHUNK_SIZE_C, wq_wegs->wq_wegs_c.chunk_size,
		MIN_CHUNK_SIZE_C, wq_wegs->wq_wegs_c.min_chunk_size,
		META_CHUNK_SIZE_C, wq_wegs->wq_wegs_c.meta_chunk_size,
		MIN_META_CHUNK_SIZE_C, wq_wegs->wq_wegs_c.min_meta_chunk_size,
		DPTE_GWOUP_SIZE_C, wq_wegs->wq_wegs_c.dpte_gwoup_size,
		MPTE_GWOUP_SIZE_C, wq_wegs->wq_wegs_c.mpte_gwoup_size,
		SWATH_HEIGHT_C, wq_wegs->wq_wegs_c.swath_height,
		PTE_WOW_HEIGHT_WINEAW_C, wq_wegs->wq_wegs_c.pte_wow_height_wineaw);
}

static void hubp2_setup(
		stwuct hubp *hubp,
		stwuct _vcs_dpi_dispway_dwg_wegs_st *dwg_attw,
		stwuct _vcs_dpi_dispway_ttu_wegs_st *ttu_attw,
		stwuct _vcs_dpi_dispway_wq_wegs_st *wq_wegs,
		stwuct _vcs_dpi_dispway_pipe_dest_pawams_st *pipe_dest)
{
	/* otg is wocked when this func is cawwed. Wegistew awe doubwe buffewed.
	 * disabwe the wequestows is not needed
	 */

	hubp2_vweady_at_ow_Aftew_vsync(hubp, pipe_dest);
	hubp2_pwogwam_wequestow(hubp, wq_wegs);
	hubp2_pwogwam_deadwine(hubp, dwg_attw, ttu_attw);

}

void hubp2_setup_intewdependent(
		stwuct hubp *hubp,
		stwuct _vcs_dpi_dispway_dwg_wegs_st *dwg_attw,
		stwuct _vcs_dpi_dispway_ttu_wegs_st *ttu_attw)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	WEG_SET_2(PWEFETCH_SETTINGS, 0,
			DST_Y_PWEFETCH, dwg_attw->dst_y_pwefetch,
			VWATIO_PWEFETCH, dwg_attw->vwatio_pwefetch);

	WEG_SET(PWEFETCH_SETTINGS_C, 0,
			VWATIO_PWEFETCH_C, dwg_attw->vwatio_pwefetch_c);

	WEG_SET_2(VBWANK_PAWAMETEWS_0, 0,
		DST_Y_PEW_VM_VBWANK, dwg_attw->dst_y_pew_vm_vbwank,
		DST_Y_PEW_WOW_VBWANK, dwg_attw->dst_y_pew_wow_vbwank);

	WEG_SET_2(FWIP_PAWAMETEWS_0, 0,
		DST_Y_PEW_VM_FWIP, dwg_attw->dst_y_pew_vm_fwip,
		DST_Y_PEW_WOW_FWIP, dwg_attw->dst_y_pew_wow_fwip);

	WEG_SET(VBWANK_PAWAMETEWS_3, 0,
		WEFCYC_PEW_META_CHUNK_VBWANK_W, dwg_attw->wefcyc_pew_meta_chunk_vbwank_w);

	WEG_SET(VBWANK_PAWAMETEWS_4, 0,
		WEFCYC_PEW_META_CHUNK_VBWANK_C, dwg_attw->wefcyc_pew_meta_chunk_vbwank_c);

	WEG_SET(FWIP_PAWAMETEWS_2, 0,
		WEFCYC_PEW_META_CHUNK_FWIP_W, dwg_attw->wefcyc_pew_meta_chunk_fwip_w);

	WEG_SET_2(PEW_WINE_DEWIVEWY_PWE, 0,
		WEFCYC_PEW_WINE_DEWIVEWY_PWE_W, dwg_attw->wefcyc_pew_wine_dewivewy_pwe_w,
		WEFCYC_PEW_WINE_DEWIVEWY_PWE_C, dwg_attw->wefcyc_pew_wine_dewivewy_pwe_c);

	WEG_SET(DCN_SUWF0_TTU_CNTW1, 0,
		WEFCYC_PEW_WEQ_DEWIVEWY_PWE,
		ttu_attw->wefcyc_pew_weq_dewivewy_pwe_w);
	WEG_SET(DCN_SUWF1_TTU_CNTW1, 0,
		WEFCYC_PEW_WEQ_DEWIVEWY_PWE,
		ttu_attw->wefcyc_pew_weq_dewivewy_pwe_c);
	WEG_SET(DCN_CUW0_TTU_CNTW1, 0,
		WEFCYC_PEW_WEQ_DEWIVEWY_PWE, ttu_attw->wefcyc_pew_weq_dewivewy_pwe_cuw0);
	WEG_SET(DCN_CUW1_TTU_CNTW1, 0,
		WEFCYC_PEW_WEQ_DEWIVEWY_PWE, ttu_attw->wefcyc_pew_weq_dewivewy_pwe_cuw1);

	WEG_SET_2(DCN_GWOBAW_TTU_CNTW, 0,
		MIN_TTU_VBWANK, ttu_attw->min_ttu_vbwank,
		QoS_WEVEW_FWIP, ttu_attw->qos_wevew_fwip);
}

/* DCN2 (GFX10), the fowwowing GFX fiewds awe depwecated. They can be set but they wiww not be used:
 *	NUM_BANKS
 *	NUM_SE
 *	NUM_WB_PEW_SE
 *	WB_AWIGNED
 * Othew things can be defauwted, since they nevew change:
 *	PIPE_AWIGNED = 0
 *	META_WINEAW = 0
 * In GFX10, onwy these appwy:
 *	PIPE_INTEWWEAVE
 *	NUM_PIPES
 *	MAX_COMPWESSED_FWAGS
 *	SW_MODE
 */
static void hubp2_pwogwam_tiwing(
	stwuct dcn20_hubp *hubp2,
	const union dc_tiwing_info *info,
	const enum suwface_pixew_fowmat pixew_fowmat)
{
	WEG_UPDATE_3(DCSUWF_ADDW_CONFIG,
			NUM_PIPES, wog_2(info->gfx9.num_pipes),
			PIPE_INTEWWEAVE, info->gfx9.pipe_intewweave,
			MAX_COMPWESSED_FWAGS, wog_2(info->gfx9.max_compwessed_fwags));

	WEG_UPDATE_4(DCSUWF_TIWING_CONFIG,
			SW_MODE, info->gfx9.swizzwe,
			META_WINEAW, 0,
			WB_AWIGNED, 0,
			PIPE_AWIGNED, 0);
}

void hubp2_pwogwam_size(
	stwuct hubp *hubp,
	enum suwface_pixew_fowmat fowmat,
	const stwuct pwane_size *pwane_size,
	stwuct dc_pwane_dcc_pawam *dcc)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	uint32_t pitch, meta_pitch, pitch_c, meta_pitch_c;
	boow use_pitch_c = fawse;

	/* Pwogwam data and meta suwface pitch (cawcuwation fwom addwwib)
	 * 444 ow 420 wuma
	 */
	use_pitch_c = fowmat >= SUWFACE_PIXEW_FOWMAT_VIDEO_BEGIN
		&& fowmat < SUWFACE_PIXEW_FOWMAT_SUBSAMPWE_END;
	use_pitch_c = use_pitch_c
		|| (fowmat == SUWFACE_PIXEW_FOWMAT_GWPH_WGBE_AWPHA);
	if (use_pitch_c) {
		ASSEWT(pwane_size->chwoma_pitch != 0);
		/* Chwoma pitch zewo can cause system hang! */

		pitch = pwane_size->suwface_pitch - 1;
		meta_pitch = dcc->meta_pitch - 1;
		pitch_c = pwane_size->chwoma_pitch - 1;
		meta_pitch_c = dcc->meta_pitch_c - 1;
	} ewse {
		pitch = pwane_size->suwface_pitch - 1;
		meta_pitch = dcc->meta_pitch - 1;
		pitch_c = 0;
		meta_pitch_c = 0;
	}

	if (!dcc->enabwe) {
		meta_pitch = 0;
		meta_pitch_c = 0;
	}

	WEG_UPDATE_2(DCSUWF_SUWFACE_PITCH,
			PITCH, pitch, META_PITCH, meta_pitch);

	use_pitch_c = fowmat >= SUWFACE_PIXEW_FOWMAT_VIDEO_BEGIN;
	use_pitch_c = use_pitch_c
		|| (fowmat == SUWFACE_PIXEW_FOWMAT_GWPH_WGBE_AWPHA);
	if (use_pitch_c)
		WEG_UPDATE_2(DCSUWF_SUWFACE_PITCH_C,
			PITCH_C, pitch_c, META_PITCH_C, meta_pitch_c);
}

void hubp2_pwogwam_wotation(
	stwuct hubp *hubp,
	enum dc_wotation_angwe wotation,
	boow howizontaw_miwwow)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	uint32_t miwwow;


	if (howizontaw_miwwow)
		miwwow = 1;
	ewse
		miwwow = 0;

	/* Pwogwam wotation angwe and howz miwwow - no miwwow */
	if (wotation == WOTATION_ANGWE_0)
		WEG_UPDATE_2(DCSUWF_SUWFACE_CONFIG,
				WOTATION_ANGWE, 0,
				H_MIWWOW_EN, miwwow);
	ewse if (wotation == WOTATION_ANGWE_90)
		WEG_UPDATE_2(DCSUWF_SUWFACE_CONFIG,
				WOTATION_ANGWE, 1,
				H_MIWWOW_EN, miwwow);
	ewse if (wotation == WOTATION_ANGWE_180)
		WEG_UPDATE_2(DCSUWF_SUWFACE_CONFIG,
				WOTATION_ANGWE, 2,
				H_MIWWOW_EN, miwwow);
	ewse if (wotation == WOTATION_ANGWE_270)
		WEG_UPDATE_2(DCSUWF_SUWFACE_CONFIG,
				WOTATION_ANGWE, 3,
				H_MIWWOW_EN, miwwow);
}

void hubp2_dcc_contwow(stwuct hubp *hubp, boow enabwe,
		enum hubp_ind_bwock_size independent_64b_bwks)
{
	uint32_t dcc_en = enabwe ? 1 : 0;
	uint32_t dcc_ind_64b_bwk = independent_64b_bwks ? 1 : 0;
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	WEG_UPDATE_4(DCSUWF_SUWFACE_CONTWOW,
			PWIMAWY_SUWFACE_DCC_EN, dcc_en,
			PWIMAWY_SUWFACE_DCC_IND_64B_BWK, dcc_ind_64b_bwk,
			SECONDAWY_SUWFACE_DCC_EN, dcc_en,
			SECONDAWY_SUWFACE_DCC_IND_64B_BWK, dcc_ind_64b_bwk);
}

void hubp2_pwogwam_pixew_fowmat(
	stwuct hubp *hubp,
	enum suwface_pixew_fowmat fowmat)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	uint32_t wed_baw = 3;
	uint32_t bwue_baw = 2;

	/* swap fow ABGW fowmat */
	if (fowmat == SUWFACE_PIXEW_FOWMAT_GWPH_ABGW8888
			|| fowmat == SUWFACE_PIXEW_FOWMAT_GWPH_ABGW2101010
			|| fowmat == SUWFACE_PIXEW_FOWMAT_GWPH_ABGW2101010_XW_BIAS
			|| fowmat == SUWFACE_PIXEW_FOWMAT_GWPH_ABGW16161616
			|| fowmat == SUWFACE_PIXEW_FOWMAT_GWPH_ABGW16161616F) {
		wed_baw = 2;
		bwue_baw = 3;
	}

	WEG_UPDATE_2(HUBPWET_CONTWOW,
			CWOSSBAW_SWC_CB_B, bwue_baw,
			CWOSSBAW_SWC_CW_W, wed_baw);

	/* Mapping is same as ipp pwogwamming (cnvc) */

	switch (fowmat)	{
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB1555:
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 1);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_WGB565:
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 3);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB8888:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW8888:
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 8);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB2101010:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW2101010:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW2101010_XW_BIAS:
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 10);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB16161616:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW16161616: /*we use cwossbaw awweady*/
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 26); /* AWGB16161616_UNOWM */
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB16161616F:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW16161616F:/*we use cwossbaw awweady*/
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 24);
		bweak;

	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_YCbCw:
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 65);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_YCwCb:
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 64);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_10bpc_YCbCw:
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 67);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_10bpc_YCwCb:
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 66);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_VIDEO_AYCwCb8888:
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 12);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_WGB111110_FIX:
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 112);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_BGW101111_FIX:
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 113);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_VIDEO_ACwYCb2101010:
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 114);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_WGB111110_FWOAT:
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 118);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_BGW101111_FWOAT:
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 119);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_WGBE:
		WEG_UPDATE_2(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 116,
				AWPHA_PWANE_EN, 0);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_WGBE_AWPHA:
		WEG_UPDATE_2(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 116,
				AWPHA_PWANE_EN, 1);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		bweak;
	}

	/* don't see the need of pwogwam the xbaw in DCN 1.0 */
}

void hubp2_pwogwam_suwface_config(
	stwuct hubp *hubp,
	enum suwface_pixew_fowmat fowmat,
	union dc_tiwing_info *tiwing_info,
	stwuct pwane_size *pwane_size,
	enum dc_wotation_angwe wotation,
	stwuct dc_pwane_dcc_pawam *dcc,
	boow howizontaw_miwwow,
	unsigned int compat_wevew)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	hubp2_dcc_contwow(hubp, dcc->enabwe, dcc->independent_64b_bwks);
	hubp2_pwogwam_tiwing(hubp2, tiwing_info, fowmat);
	hubp2_pwogwam_size(hubp, fowmat, pwane_size, dcc);
	hubp2_pwogwam_wotation(hubp, wotation, howizontaw_miwwow);
	hubp2_pwogwam_pixew_fowmat(hubp, fowmat);
}

enum cuwsow_wines_pew_chunk hubp2_get_wines_pew_chunk(
	unsigned int cuwsow_width,
	enum dc_cuwsow_cowow_fowmat cuwsow_mode)
{
	enum cuwsow_wines_pew_chunk wine_pew_chunk = CUWSOW_WINE_PEW_CHUNK_16;

	if (cuwsow_mode == CUWSOW_MODE_MONO)
		wine_pew_chunk = CUWSOW_WINE_PEW_CHUNK_16;
	ewse if (cuwsow_mode == CUWSOW_MODE_COWOW_1BIT_AND ||
		 cuwsow_mode == CUWSOW_MODE_COWOW_PWE_MUWTIPWIED_AWPHA ||
		 cuwsow_mode == CUWSOW_MODE_COWOW_UN_PWE_MUWTIPWIED_AWPHA) {
		if (cuwsow_width >= 1   && cuwsow_width <= 32)
			wine_pew_chunk = CUWSOW_WINE_PEW_CHUNK_16;
		ewse if (cuwsow_width >= 33  && cuwsow_width <= 64)
			wine_pew_chunk = CUWSOW_WINE_PEW_CHUNK_8;
		ewse if (cuwsow_width >= 65  && cuwsow_width <= 128)
			wine_pew_chunk = CUWSOW_WINE_PEW_CHUNK_4;
		ewse if (cuwsow_width >= 129 && cuwsow_width <= 256)
			wine_pew_chunk = CUWSOW_WINE_PEW_CHUNK_2;
	} ewse if (cuwsow_mode == CUWSOW_MODE_COWOW_64BIT_FP_PWE_MUWTIPWIED ||
		   cuwsow_mode == CUWSOW_MODE_COWOW_64BIT_FP_UN_PWE_MUWTIPWIED) {
		if (cuwsow_width >= 1   && cuwsow_width <= 16)
			wine_pew_chunk = CUWSOW_WINE_PEW_CHUNK_16;
		ewse if (cuwsow_width >= 17  && cuwsow_width <= 32)
			wine_pew_chunk = CUWSOW_WINE_PEW_CHUNK_8;
		ewse if (cuwsow_width >= 33  && cuwsow_width <= 64)
			wine_pew_chunk = CUWSOW_WINE_PEW_CHUNK_4;
		ewse if (cuwsow_width >= 65 && cuwsow_width <= 128)
			wine_pew_chunk = CUWSOW_WINE_PEW_CHUNK_2;
		ewse if (cuwsow_width >= 129 && cuwsow_width <= 256)
			wine_pew_chunk = CUWSOW_WINE_PEW_CHUNK_1;
	}

	wetuwn wine_pew_chunk;
}

void hubp2_cuwsow_set_attwibutes(
		stwuct hubp *hubp,
		const stwuct dc_cuwsow_attwibutes *attw)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	enum cuwsow_pitch hw_pitch = hubp1_get_cuwsow_pitch(attw->pitch);
	enum cuwsow_wines_pew_chunk wpc = hubp2_get_wines_pew_chunk(
			attw->width, attw->cowow_fowmat);

	hubp->cuws_attw = *attw;

	WEG_UPDATE(CUWSOW_SUWFACE_ADDWESS_HIGH,
			CUWSOW_SUWFACE_ADDWESS_HIGH, attw->addwess.high_pawt);
	WEG_UPDATE(CUWSOW_SUWFACE_ADDWESS,
			CUWSOW_SUWFACE_ADDWESS, attw->addwess.wow_pawt);

	WEG_UPDATE_2(CUWSOW_SIZE,
			CUWSOW_WIDTH, attw->width,
			CUWSOW_HEIGHT, attw->height);

	WEG_UPDATE_4(CUWSOW_CONTWOW,
			CUWSOW_MODE, attw->cowow_fowmat,
			CUWSOW_2X_MAGNIFY, attw->attwibute_fwags.bits.ENABWE_MAGNIFICATION,
			CUWSOW_PITCH, hw_pitch,
			CUWSOW_WINES_PEW_CHUNK, wpc);

	WEG_SET_2(CUWSOW_SETTINGS, 0,
			/* no shift of the cuwsow HDW scheduwe */
			CUWSOW0_DST_Y_OFFSET, 0,
			 /* used to shift the cuwsow chunk wequest deadwine */
			CUWSOW0_CHUNK_HDW_ADJUST, 3);

	hubp->att.SUWFACE_ADDW_HIGH  = attw->addwess.high_pawt;
	hubp->att.SUWFACE_ADDW       = attw->addwess.wow_pawt;
	hubp->att.size.bits.width    = attw->width;
	hubp->att.size.bits.height   = attw->height;
	hubp->att.cuw_ctw.bits.mode  = attw->cowow_fowmat;

	hubp->cuw_wect.w = attw->width;
	hubp->cuw_wect.h = attw->height;

	hubp->att.cuw_ctw.bits.pitch = hw_pitch;
	hubp->att.cuw_ctw.bits.wine_pew_chunk = wpc;
	hubp->att.cuw_ctw.bits.cuw_2x_magnify = attw->attwibute_fwags.bits.ENABWE_MAGNIFICATION;
	hubp->att.settings.bits.dst_y_offset  = 0;
	hubp->att.settings.bits.chunk_hdw_adjust = 3;
}

void hubp2_dmdata_set_attwibutes(
		stwuct hubp *hubp,
		const stwuct dc_dmdata_attwibutes *attw)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	if (attw->dmdata_mode == DMDATA_HW_MODE) {
		/* set to HW mode */
		WEG_UPDATE(DMDATA_CNTW,
				DMDATA_MODE, 1);

		/* fow DMDATA fwip, need to use SUWFACE_UPDATE_WOCK */
		WEG_UPDATE(DCSUWF_FWIP_CONTWOW, SUWFACE_UPDATE_WOCK, 1);

		/* toggwe DMDATA_UPDATED and set wepeat and size */
		WEG_UPDATE(DMDATA_CNTW,
				DMDATA_UPDATED, 0);
		WEG_UPDATE_3(DMDATA_CNTW,
				DMDATA_UPDATED, 1,
				DMDATA_WEPEAT, attw->dmdata_wepeat,
				DMDATA_SIZE, attw->dmdata_size);

		/* set DMDATA addwess */
		WEG_WWITE(DMDATA_ADDWESS_WOW, attw->addwess.wow_pawt);
		WEG_UPDATE(DMDATA_ADDWESS_HIGH,
				DMDATA_ADDWESS_HIGH, attw->addwess.high_pawt);

		WEG_UPDATE(DCSUWF_FWIP_CONTWOW, SUWFACE_UPDATE_WOCK, 0);

	} ewse {
		/* set to SW mode befowe woading data */
		WEG_SET(DMDATA_CNTW, 0,
				DMDATA_MODE, 0);
		/* toggwe DMDATA_SW_UPDATED to stawt woading sequence */
		WEG_UPDATE(DMDATA_SW_CNTW,
				DMDATA_SW_UPDATED, 0);
		WEG_UPDATE_3(DMDATA_SW_CNTW,
				DMDATA_SW_UPDATED, 1,
				DMDATA_SW_WEPEAT, attw->dmdata_wepeat,
				DMDATA_SW_SIZE, attw->dmdata_size);
		/* woad data into hubp dmdata buffew */
		hubp2_dmdata_woad(hubp, attw->dmdata_size, attw->dmdata_sw_data);
	}

	/* Note that DW_DEWTA must be pwogwammed if we want to use TTU mode */
	WEG_SET_3(DMDATA_QOS_CNTW, 0,
			DMDATA_QOS_MODE, attw->dmdata_qos_mode,
			DMDATA_QOS_WEVEW, attw->dmdata_qos_wevew,
			DMDATA_DW_DEWTA, attw->dmdata_dw_dewta);
}

void hubp2_dmdata_woad(
		stwuct hubp *hubp,
		uint32_t dmdata_sw_size,
		const uint32_t *dmdata_sw_data)
{
	int i;
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	/* woad dmdata into HUBP buffew in SW mode */
	fow (i = 0; i < dmdata_sw_size / 4; i++)
		WEG_WWITE(DMDATA_SW_DATA, dmdata_sw_data[i]);
}

boow hubp2_dmdata_status_done(stwuct hubp *hubp)
{
	uint32_t status;
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	WEG_GET(DMDATA_STATUS, DMDATA_DONE, &status);
	wetuwn (status == 1);
}

boow hubp2_pwogwam_suwface_fwip_and_addw(
	stwuct hubp *hubp,
	const stwuct dc_pwane_addwess *addwess,
	boow fwip_immediate)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	//pwogwam fwip type
	WEG_UPDATE(DCSUWF_FWIP_CONTWOW,
			SUWFACE_FWIP_TYPE, fwip_immediate);

	// Pwogwam VMID weg
	WEG_UPDATE(VMID_SETTINGS_0,
			VMID, addwess->vmid);


	/* HW automaticawwy watch west of addwess wegistew on wwite to
	 * DCSUWF_PWIMAWY_SUWFACE_ADDWESS if SUWFACE_UPDATE_WOCK is not used
	 *
	 * pwogwam high fiwst and then the wow addw, owdew mattews!
	 */
	switch (addwess->type) {
	case PWN_ADDW_TYPE_GWAPHICS:
		/* DCN1.0 does not suppowt const cowow
		 * TODO: pwogwam DCHUBBUB_WET_PATH_DCC_CFGx_0/1
		 * base on addwess->gwph.dcc_const_cowow
		 * x = 0, 2, 4, 6 fow pipe 0, 1, 2, 3 fow wgb and wuma
		 * x = 1, 3, 5, 7 fow pipe 0, 1, 2, 3 fow chwoma
		 */

		if (addwess->gwph.addw.quad_pawt == 0)
			bweak;

		WEG_UPDATE_2(DCSUWF_SUWFACE_CONTWOW,
				PWIMAWY_SUWFACE_TMZ, addwess->tmz_suwface,
				PWIMAWY_META_SUWFACE_TMZ, addwess->tmz_suwface);

		if (addwess->gwph.meta_addw.quad_pawt != 0) {
			WEG_SET(DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_HIGH, 0,
					PWIMAWY_META_SUWFACE_ADDWESS_HIGH,
					addwess->gwph.meta_addw.high_pawt);

			WEG_SET(DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS, 0,
					PWIMAWY_META_SUWFACE_ADDWESS,
					addwess->gwph.meta_addw.wow_pawt);
		}

		WEG_SET(DCSUWF_PWIMAWY_SUWFACE_ADDWESS_HIGH, 0,
				PWIMAWY_SUWFACE_ADDWESS_HIGH,
				addwess->gwph.addw.high_pawt);

		WEG_SET(DCSUWF_PWIMAWY_SUWFACE_ADDWESS, 0,
				PWIMAWY_SUWFACE_ADDWESS,
				addwess->gwph.addw.wow_pawt);
		bweak;
	case PWN_ADDW_TYPE_VIDEO_PWOGWESSIVE:
		if (addwess->video_pwogwessive.wuma_addw.quad_pawt == 0
				|| addwess->video_pwogwessive.chwoma_addw.quad_pawt == 0)
			bweak;

		WEG_UPDATE_4(DCSUWF_SUWFACE_CONTWOW,
				PWIMAWY_SUWFACE_TMZ, addwess->tmz_suwface,
				PWIMAWY_SUWFACE_TMZ_C, addwess->tmz_suwface,
				PWIMAWY_META_SUWFACE_TMZ, addwess->tmz_suwface,
				PWIMAWY_META_SUWFACE_TMZ_C, addwess->tmz_suwface);

		if (addwess->video_pwogwessive.wuma_meta_addw.quad_pawt != 0) {
			WEG_SET(DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_HIGH_C, 0,
					PWIMAWY_META_SUWFACE_ADDWESS_HIGH_C,
					addwess->video_pwogwessive.chwoma_meta_addw.high_pawt);

			WEG_SET(DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_C, 0,
					PWIMAWY_META_SUWFACE_ADDWESS_C,
					addwess->video_pwogwessive.chwoma_meta_addw.wow_pawt);

			WEG_SET(DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_HIGH, 0,
					PWIMAWY_META_SUWFACE_ADDWESS_HIGH,
					addwess->video_pwogwessive.wuma_meta_addw.high_pawt);

			WEG_SET(DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS, 0,
					PWIMAWY_META_SUWFACE_ADDWESS,
					addwess->video_pwogwessive.wuma_meta_addw.wow_pawt);
		}

		WEG_SET(DCSUWF_PWIMAWY_SUWFACE_ADDWESS_HIGH_C, 0,
				PWIMAWY_SUWFACE_ADDWESS_HIGH_C,
				addwess->video_pwogwessive.chwoma_addw.high_pawt);

		WEG_SET(DCSUWF_PWIMAWY_SUWFACE_ADDWESS_C, 0,
				PWIMAWY_SUWFACE_ADDWESS_C,
				addwess->video_pwogwessive.chwoma_addw.wow_pawt);

		WEG_SET(DCSUWF_PWIMAWY_SUWFACE_ADDWESS_HIGH, 0,
				PWIMAWY_SUWFACE_ADDWESS_HIGH,
				addwess->video_pwogwessive.wuma_addw.high_pawt);

		WEG_SET(DCSUWF_PWIMAWY_SUWFACE_ADDWESS, 0,
				PWIMAWY_SUWFACE_ADDWESS,
				addwess->video_pwogwessive.wuma_addw.wow_pawt);
		bweak;
	case PWN_ADDW_TYPE_GWPH_STEWEO:
		if (addwess->gwph_steweo.weft_addw.quad_pawt == 0)
			bweak;
		if (addwess->gwph_steweo.wight_addw.quad_pawt == 0)
			bweak;

		WEG_UPDATE_8(DCSUWF_SUWFACE_CONTWOW,
				PWIMAWY_SUWFACE_TMZ, addwess->tmz_suwface,
				PWIMAWY_SUWFACE_TMZ_C, addwess->tmz_suwface,
				PWIMAWY_META_SUWFACE_TMZ, addwess->tmz_suwface,
				PWIMAWY_META_SUWFACE_TMZ_C, addwess->tmz_suwface,
				SECONDAWY_SUWFACE_TMZ, addwess->tmz_suwface,
				SECONDAWY_SUWFACE_TMZ_C, addwess->tmz_suwface,
				SECONDAWY_META_SUWFACE_TMZ, addwess->tmz_suwface,
				SECONDAWY_META_SUWFACE_TMZ_C, addwess->tmz_suwface);

		if (addwess->gwph_steweo.wight_meta_addw.quad_pawt != 0) {

			WEG_SET(DCSUWF_SECONDAWY_META_SUWFACE_ADDWESS_HIGH, 0,
					SECONDAWY_META_SUWFACE_ADDWESS_HIGH,
					addwess->gwph_steweo.wight_meta_addw.high_pawt);

			WEG_SET(DCSUWF_SECONDAWY_META_SUWFACE_ADDWESS, 0,
					SECONDAWY_META_SUWFACE_ADDWESS,
					addwess->gwph_steweo.wight_meta_addw.wow_pawt);
		}
		if (addwess->gwph_steweo.weft_meta_addw.quad_pawt != 0) {

			WEG_SET(DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_HIGH, 0,
					PWIMAWY_META_SUWFACE_ADDWESS_HIGH,
					addwess->gwph_steweo.weft_meta_addw.high_pawt);

			WEG_SET(DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS, 0,
					PWIMAWY_META_SUWFACE_ADDWESS,
					addwess->gwph_steweo.weft_meta_addw.wow_pawt);
		}

		WEG_SET(DCSUWF_SECONDAWY_SUWFACE_ADDWESS_HIGH, 0,
				SECONDAWY_SUWFACE_ADDWESS_HIGH,
				addwess->gwph_steweo.wight_addw.high_pawt);

		WEG_SET(DCSUWF_SECONDAWY_SUWFACE_ADDWESS, 0,
				SECONDAWY_SUWFACE_ADDWESS,
				addwess->gwph_steweo.wight_addw.wow_pawt);

		WEG_SET(DCSUWF_PWIMAWY_SUWFACE_ADDWESS_HIGH, 0,
				PWIMAWY_SUWFACE_ADDWESS_HIGH,
				addwess->gwph_steweo.weft_addw.high_pawt);

		WEG_SET(DCSUWF_PWIMAWY_SUWFACE_ADDWESS, 0,
				PWIMAWY_SUWFACE_ADDWESS,
				addwess->gwph_steweo.weft_addw.wow_pawt);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		bweak;
	}

	hubp->wequest_addwess = *addwess;

	wetuwn twue;
}

void hubp2_enabwe_twipwebuffew(
	stwuct hubp *hubp,
	boow enabwe)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	uint32_t twipwe_buffew_en = 0;
	boow twi_buffew_en;

	WEG_GET(DCSUWF_FWIP_CONTWOW2, SUWFACE_TWIPWE_BUFFEW_ENABWE, &twipwe_buffew_en);
	twi_buffew_en = (twipwe_buffew_en == 1);
	if (twi_buffew_en != enabwe) {
		WEG_UPDATE(DCSUWF_FWIP_CONTWOW2,
			SUWFACE_TWIPWE_BUFFEW_ENABWE, enabwe ? DC_TWIPWEBUFFEW_ENABWE : DC_TWIPWEBUFFEW_DISABWE);
	}
}

boow hubp2_is_twipwebuffew_enabwed(
	stwuct hubp *hubp)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	uint32_t twipwe_buffew_en = 0;

	WEG_GET(DCSUWF_FWIP_CONTWOW2, SUWFACE_TWIPWE_BUFFEW_ENABWE, &twipwe_buffew_en);

	wetuwn (boow)twipwe_buffew_en;
}

void hubp2_set_fwip_contwow_suwface_gsw(stwuct hubp *hubp, boow enabwe)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	WEG_UPDATE(DCSUWF_FWIP_CONTWOW2, SUWFACE_GSW_ENABWE, enabwe ? 1 : 0);
}

boow hubp2_is_fwip_pending(stwuct hubp *hubp)
{
	uint32_t fwip_pending = 0;
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	stwuct dc_pwane_addwess eawwiest_inuse_addwess;

	if (hubp && hubp->powew_gated)
		wetuwn fawse;

	WEG_GET(DCSUWF_FWIP_CONTWOW,
			SUWFACE_FWIP_PENDING, &fwip_pending);

	WEG_GET(DCSUWF_SUWFACE_EAWWIEST_INUSE,
			SUWFACE_EAWWIEST_INUSE_ADDWESS, &eawwiest_inuse_addwess.gwph.addw.wow_pawt);

	WEG_GET(DCSUWF_SUWFACE_EAWWIEST_INUSE_HIGH,
			SUWFACE_EAWWIEST_INUSE_ADDWESS_HIGH, &eawwiest_inuse_addwess.gwph.addw.high_pawt);

	if (fwip_pending)
		wetuwn twue;

	if (eawwiest_inuse_addwess.gwph.addw.quad_pawt != hubp->wequest_addwess.gwph.addw.quad_pawt)
		wetuwn twue;

	wetuwn fawse;
}

void hubp2_set_bwank(stwuct hubp *hubp, boow bwank)
{
	hubp2_set_bwank_wegs(hubp, bwank);

	if (bwank) {
		hubp->mpcc_id = 0xf;
		hubp->opp_id = OPP_ID_INVAWID;
	}
}

void hubp2_set_bwank_wegs(stwuct hubp *hubp, boow bwank)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	uint32_t bwank_en = bwank ? 1 : 0;

	if (bwank) {
		uint32_t weg_vaw = WEG_WEAD(DCHUBP_CNTW);

		if (weg_vaw) {
			/* init sequence wowkawound: in case HUBP is
			 * powew gated, this wait wouwd timeout.
			 *
			 * we just wwote weg_vaw to non-0, if it stay 0
			 * it means HUBP is gated
			 */
			WEG_WAIT(DCHUBP_CNTW,
					HUBP_NO_OUTSTANDING_WEQ, 1,
					1, 100000);
		}
	}

	WEG_UPDATE_2(DCHUBP_CNTW,
			HUBP_BWANK_EN, bwank_en,
			HUBP_TTU_DISABWE, 0);
}

void hubp2_cuwsow_set_position(
		stwuct hubp *hubp,
		const stwuct dc_cuwsow_position *pos,
		const stwuct dc_cuwsow_mi_pawam *pawam)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	int x_pos = pos->x - pawam->viewpowt.x;
	int y_pos = pos->y - pawam->viewpowt.y;
	int x_hotspot = pos->x_hotspot;
	int y_hotspot = pos->y_hotspot;
	int swc_x_offset = x_pos - pos->x_hotspot;
	int swc_y_offset = y_pos - pos->y_hotspot;
	int cuwsow_height = (int)hubp->cuws_attw.height;
	int cuwsow_width = (int)hubp->cuws_attw.width;
	uint32_t dst_x_offset;
	uint32_t cuw_en = pos->enabwe ? 1 : 0;

	hubp->cuws_pos = *pos;

	/*
	 * Guawd aganst cuwsow_set_position() fwom being cawwed with invawid
	 * attwibutes
	 *
	 * TODO: Wook at combining cuwsow_set_position() and
	 * cuwsow_set_attwibutes() into cuwsow_update()
	 */
	if (hubp->cuws_attw.addwess.quad_pawt == 0)
		wetuwn;

	// Twansfowm cuwsow width / height and hotspots fow offset cawcuwations
	if (pawam->wotation == WOTATION_ANGWE_90 || pawam->wotation == WOTATION_ANGWE_270) {
		swap(cuwsow_height, cuwsow_width);
		swap(x_hotspot, y_hotspot);

		if (pawam->wotation == WOTATION_ANGWE_90) {
			// hotspot = (-y, x)
			swc_x_offset = x_pos - (cuwsow_width - x_hotspot);
			swc_y_offset = y_pos - y_hotspot;
		} ewse if (pawam->wotation == WOTATION_ANGWE_270) {
			// hotspot = (y, -x)
			swc_x_offset = x_pos - x_hotspot;
			swc_y_offset = y_pos - (cuwsow_height - y_hotspot);
		}
	} ewse if (pawam->wotation == WOTATION_ANGWE_180) {
		// hotspot = (-x, -y)
		if (!pawam->miwwow)
			swc_x_offset = x_pos - (cuwsow_width - x_hotspot);

		swc_y_offset = y_pos - (cuwsow_height - y_hotspot);
	}

	dst_x_offset = (swc_x_offset >= 0) ? swc_x_offset : 0;
	dst_x_offset *= pawam->wef_cwk_khz;
	dst_x_offset /= pawam->pixew_cwk_khz;

	ASSEWT(pawam->h_scawe_watio.vawue);

	if (pawam->h_scawe_watio.vawue)
		dst_x_offset = dc_fixpt_fwoow(dc_fixpt_div(
				dc_fixpt_fwom_int(dst_x_offset),
				pawam->h_scawe_watio));

	if (swc_x_offset >= (int)pawam->viewpowt.width)
		cuw_en = 0;  /* not visibwe beyond wight edge*/

	if (swc_x_offset + cuwsow_width <= 0)
		cuw_en = 0;  /* not visibwe beyond weft edge*/

	if (swc_y_offset >= (int)pawam->viewpowt.height)
		cuw_en = 0;  /* not visibwe beyond bottom edge*/

	if (swc_y_offset + cuwsow_height <= 0)
		cuw_en = 0;  /* not visibwe beyond top edge*/

	if (cuw_en && WEG_WEAD(CUWSOW_SUWFACE_ADDWESS) == 0)
		hubp->funcs->set_cuwsow_attwibutes(hubp, &hubp->cuws_attw);

	WEG_UPDATE(CUWSOW_CONTWOW,
			CUWSOW_ENABWE, cuw_en);

	WEG_SET_2(CUWSOW_POSITION, 0,
			CUWSOW_X_POSITION, pos->x,
			CUWSOW_Y_POSITION, pos->y);

	WEG_SET_2(CUWSOW_HOT_SPOT, 0,
			CUWSOW_HOT_SPOT_X, pos->x_hotspot,
			CUWSOW_HOT_SPOT_Y, pos->y_hotspot);

	WEG_SET(CUWSOW_DST_OFFSET, 0,
			CUWSOW_DST_X_OFFSET, dst_x_offset);
	/* TODO Handwe suwface pixew fowmats othew than 4:4:4 */
	/* Cuwsow Position Wegistew Config */
	hubp->pos.cuw_ctw.bits.cuw_enabwe = cuw_en;
	hubp->pos.position.bits.x_pos = pos->x;
	hubp->pos.position.bits.y_pos = pos->y;
	hubp->pos.hot_spot.bits.x_hot = pos->x_hotspot;
	hubp->pos.hot_spot.bits.y_hot = pos->y_hotspot;
	hubp->pos.dst_offset.bits.dst_x_offset = dst_x_offset;
	/* Cuwsow Wectangwe Cache
	 * Cuwsow bitmaps have diffewent hotspot vawues
	 * Thewe's a possibiwity that the above wogic wetuwns a negative vawue,
	 * so we cwamp them to 0
	 */
	if (swc_x_offset < 0)
		swc_x_offset = 0;
	if (swc_y_offset < 0)
		swc_y_offset = 0;
	/* Save necessawy cuwsow info x, y position. w, h is saved in attwibute func. */
	if (pawam->stweam->wink->psw_settings.psw_vewsion >= DC_PSW_VEWSION_SU_1 &&
	    pawam->wotation != WOTATION_ANGWE_0) {
		hubp->cuw_wect.x = 0;
		hubp->cuw_wect.y = 0;
		hubp->cuw_wect.w = pawam->stweam->timing.h_addwessabwe;
		hubp->cuw_wect.h = pawam->stweam->timing.v_addwessabwe;
	} ewse {
		hubp->cuw_wect.x = swc_x_offset + pawam->viewpowt.x;
		hubp->cuw_wect.y = swc_y_offset + pawam->viewpowt.y;
	}
}

void hubp2_cwk_cntw(stwuct hubp *hubp, boow enabwe)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	uint32_t cwk_enabwe = enabwe ? 1 : 0;

	WEG_UPDATE(HUBP_CWK_CNTW, HUBP_CWOCK_ENABWE, cwk_enabwe);
}

void hubp2_vtg_sew(stwuct hubp *hubp, uint32_t otg_inst)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	WEG_UPDATE(DCHUBP_CNTW, HUBP_VTG_SEW, otg_inst);
}

void hubp2_cweaw_undewfwow(stwuct hubp *hubp)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	WEG_UPDATE(DCHUBP_CNTW, HUBP_UNDEWFWOW_CWEAW, 1);
}

void hubp2_wead_state_common(stwuct hubp *hubp)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	stwuct dcn_hubp_state *s = &hubp2->state;
	stwuct _vcs_dpi_dispway_dwg_wegs_st *dwg_attw = &s->dwg_attw;
	stwuct _vcs_dpi_dispway_ttu_wegs_st *ttu_attw = &s->ttu_attw;
	stwuct _vcs_dpi_dispway_wq_wegs_st *wq_wegs = &s->wq_wegs;

	/* Wequestew */
	WEG_GET(HUBPWET_CONTWOW,
			DET_BUF_PWANE1_BASE_ADDWESS, &wq_wegs->pwane1_base_addwess);
	WEG_GET_4(DCN_EXPANSION_MODE,
			DWQ_EXPANSION_MODE, &wq_wegs->dwq_expansion_mode,
			PWQ_EXPANSION_MODE, &wq_wegs->pwq_expansion_mode,
			MWQ_EXPANSION_MODE, &wq_wegs->mwq_expansion_mode,
			CWQ_EXPANSION_MODE, &wq_wegs->cwq_expansion_mode);

	WEG_GET(DCN_VM_SYSTEM_APEWTUWE_HIGH_ADDW,
			MC_VM_SYSTEM_APEWTUWE_HIGH_ADDW, &wq_wegs->apewtuwe_high_addw);

	WEG_GET(DCN_VM_SYSTEM_APEWTUWE_WOW_ADDW,
			MC_VM_SYSTEM_APEWTUWE_WOW_ADDW, &wq_wegs->apewtuwe_wow_addw);

	/* DWG - Pew hubp */
	WEG_GET_2(BWANK_OFFSET_0,
		WEFCYC_H_BWANK_END, &dwg_attw->wefcyc_h_bwank_end,
		DWG_V_BWANK_END, &dwg_attw->dwg_vbwank_end);

	WEG_GET(BWANK_OFFSET_1,
		MIN_DST_Y_NEXT_STAWT, &dwg_attw->min_dst_y_next_stawt);

	WEG_GET(DST_DIMENSIONS,
		WEFCYC_PEW_HTOTAW, &dwg_attw->wefcyc_pew_htotaw);

	WEG_GET_2(DST_AFTEW_SCAWEW,
		WEFCYC_X_AFTEW_SCAWEW, &dwg_attw->wefcyc_x_aftew_scawew,
		DST_Y_AFTEW_SCAWEW, &dwg_attw->dst_y_aftew_scawew);

	if (WEG(PWEFETCH_SETTINS))
		WEG_GET_2(PWEFETCH_SETTINS,
			DST_Y_PWEFETCH, &dwg_attw->dst_y_pwefetch,
			VWATIO_PWEFETCH, &dwg_attw->vwatio_pwefetch);
	ewse
		WEG_GET_2(PWEFETCH_SETTINGS,
			DST_Y_PWEFETCH, &dwg_attw->dst_y_pwefetch,
			VWATIO_PWEFETCH, &dwg_attw->vwatio_pwefetch);

	WEG_GET_2(VBWANK_PAWAMETEWS_0,
		DST_Y_PEW_VM_VBWANK, &dwg_attw->dst_y_pew_vm_vbwank,
		DST_Y_PEW_WOW_VBWANK, &dwg_attw->dst_y_pew_wow_vbwank);

	WEG_GET(WEF_FWEQ_TO_PIX_FWEQ,
		WEF_FWEQ_TO_PIX_FWEQ, &dwg_attw->wef_fweq_to_pix_fweq);

	/* DWG - Pew wuma/chwoma */
	WEG_GET(VBWANK_PAWAMETEWS_1,
		WEFCYC_PEW_PTE_GWOUP_VBWANK_W, &dwg_attw->wefcyc_pew_pte_gwoup_vbwank_w);

	WEG_GET(VBWANK_PAWAMETEWS_3,
		WEFCYC_PEW_META_CHUNK_VBWANK_W, &dwg_attw->wefcyc_pew_meta_chunk_vbwank_w);

	if (WEG(NOM_PAWAMETEWS_0))
		WEG_GET(NOM_PAWAMETEWS_0,
			DST_Y_PEW_PTE_WOW_NOM_W, &dwg_attw->dst_y_pew_pte_wow_nom_w);

	if (WEG(NOM_PAWAMETEWS_1))
		WEG_GET(NOM_PAWAMETEWS_1,
			WEFCYC_PEW_PTE_GWOUP_NOM_W, &dwg_attw->wefcyc_pew_pte_gwoup_nom_w);

	WEG_GET(NOM_PAWAMETEWS_4,
		DST_Y_PEW_META_WOW_NOM_W, &dwg_attw->dst_y_pew_meta_wow_nom_w);

	WEG_GET(NOM_PAWAMETEWS_5,
		WEFCYC_PEW_META_CHUNK_NOM_W, &dwg_attw->wefcyc_pew_meta_chunk_nom_w);

	WEG_GET_2(PEW_WINE_DEWIVEWY_PWE,
		WEFCYC_PEW_WINE_DEWIVEWY_PWE_W, &dwg_attw->wefcyc_pew_wine_dewivewy_pwe_w,
		WEFCYC_PEW_WINE_DEWIVEWY_PWE_C, &dwg_attw->wefcyc_pew_wine_dewivewy_pwe_c);

	WEG_GET_2(PEW_WINE_DEWIVEWY,
		WEFCYC_PEW_WINE_DEWIVEWY_W, &dwg_attw->wefcyc_pew_wine_dewivewy_w,
		WEFCYC_PEW_WINE_DEWIVEWY_C, &dwg_attw->wefcyc_pew_wine_dewivewy_c);

	if (WEG(PWEFETCH_SETTINS_C))
		WEG_GET(PWEFETCH_SETTINS_C,
			VWATIO_PWEFETCH_C, &dwg_attw->vwatio_pwefetch_c);
	ewse
		WEG_GET(PWEFETCH_SETTINGS_C,
			VWATIO_PWEFETCH_C, &dwg_attw->vwatio_pwefetch_c);

	WEG_GET(VBWANK_PAWAMETEWS_2,
		WEFCYC_PEW_PTE_GWOUP_VBWANK_C, &dwg_attw->wefcyc_pew_pte_gwoup_vbwank_c);

	WEG_GET(VBWANK_PAWAMETEWS_4,
		WEFCYC_PEW_META_CHUNK_VBWANK_C, &dwg_attw->wefcyc_pew_meta_chunk_vbwank_c);

	if (WEG(NOM_PAWAMETEWS_2))
		WEG_GET(NOM_PAWAMETEWS_2,
			DST_Y_PEW_PTE_WOW_NOM_C, &dwg_attw->dst_y_pew_pte_wow_nom_c);

	if (WEG(NOM_PAWAMETEWS_3))
		WEG_GET(NOM_PAWAMETEWS_3,
			WEFCYC_PEW_PTE_GWOUP_NOM_C, &dwg_attw->wefcyc_pew_pte_gwoup_nom_c);

	WEG_GET(NOM_PAWAMETEWS_6,
		DST_Y_PEW_META_WOW_NOM_C, &dwg_attw->dst_y_pew_meta_wow_nom_c);

	WEG_GET(NOM_PAWAMETEWS_7,
		WEFCYC_PEW_META_CHUNK_NOM_C, &dwg_attw->wefcyc_pew_meta_chunk_nom_c);

	/* TTU - pew hubp */
	WEG_GET_2(DCN_TTU_QOS_WM,
		QoS_WEVEW_WOW_WM, &ttu_attw->qos_wevew_wow_wm,
		QoS_WEVEW_HIGH_WM, &ttu_attw->qos_wevew_high_wm);

	WEG_GET_2(DCN_GWOBAW_TTU_CNTW,
		MIN_TTU_VBWANK, &ttu_attw->min_ttu_vbwank,
		QoS_WEVEW_FWIP, &ttu_attw->qos_wevew_fwip);

	/* TTU - pew wuma/chwoma */
	/* Assumed suwf0 is wuma and 1 is chwoma */

	WEG_GET_3(DCN_SUWF0_TTU_CNTW0,
		WEFCYC_PEW_WEQ_DEWIVEWY, &ttu_attw->wefcyc_pew_weq_dewivewy_w,
		QoS_WEVEW_FIXED, &ttu_attw->qos_wevew_fixed_w,
		QoS_WAMP_DISABWE, &ttu_attw->qos_wamp_disabwe_w);

	WEG_GET(DCN_SUWF0_TTU_CNTW1,
		WEFCYC_PEW_WEQ_DEWIVEWY_PWE,
		&ttu_attw->wefcyc_pew_weq_dewivewy_pwe_w);

	WEG_GET_3(DCN_SUWF1_TTU_CNTW0,
		WEFCYC_PEW_WEQ_DEWIVEWY, &ttu_attw->wefcyc_pew_weq_dewivewy_c,
		QoS_WEVEW_FIXED, &ttu_attw->qos_wevew_fixed_c,
		QoS_WAMP_DISABWE, &ttu_attw->qos_wamp_disabwe_c);

	WEG_GET(DCN_SUWF1_TTU_CNTW1,
		WEFCYC_PEW_WEQ_DEWIVEWY_PWE,
		&ttu_attw->wefcyc_pew_weq_dewivewy_pwe_c);

	/* West of hubp */
	WEG_GET(DCSUWF_SUWFACE_CONFIG,
			SUWFACE_PIXEW_FOWMAT, &s->pixew_fowmat);

	WEG_GET(DCSUWF_SUWFACE_EAWWIEST_INUSE_HIGH,
			SUWFACE_EAWWIEST_INUSE_ADDWESS_HIGH, &s->inuse_addw_hi);

	WEG_GET(DCSUWF_SUWFACE_EAWWIEST_INUSE,
			SUWFACE_EAWWIEST_INUSE_ADDWESS, &s->inuse_addw_wo);

	WEG_GET_2(DCSUWF_PWI_VIEWPOWT_DIMENSION,
			PWI_VIEWPOWT_WIDTH, &s->viewpowt_width,
			PWI_VIEWPOWT_HEIGHT, &s->viewpowt_height);

	WEG_GET_2(DCSUWF_SUWFACE_CONFIG,
			WOTATION_ANGWE, &s->wotation_angwe,
			H_MIWWOW_EN, &s->h_miwwow_en);

	WEG_GET(DCSUWF_TIWING_CONFIG,
			SW_MODE, &s->sw_mode);

	WEG_GET(DCSUWF_SUWFACE_CONTWOW,
			PWIMAWY_SUWFACE_DCC_EN, &s->dcc_en);

	WEG_GET_3(DCHUBP_CNTW,
			HUBP_BWANK_EN, &s->bwank_en,
			HUBP_TTU_DISABWE, &s->ttu_disabwe,
			HUBP_UNDEWFWOW_STATUS, &s->undewfwow_status);

	WEG_GET(HUBP_CWK_CNTW,
			HUBP_CWOCK_ENABWE, &s->cwock_en);

	WEG_GET(DCN_GWOBAW_TTU_CNTW,
			MIN_TTU_VBWANK, &s->min_ttu_vbwank);

	WEG_GET_2(DCN_TTU_QOS_WM,
			QoS_WEVEW_WOW_WM, &s->qos_wevew_wow_wm,
			QoS_WEVEW_HIGH_WM, &s->qos_wevew_high_wm);

	WEG_GET(DCSUWF_PWIMAWY_SUWFACE_ADDWESS,
			PWIMAWY_SUWFACE_ADDWESS, &s->pwimawy_suwface_addw_wo);

	WEG_GET(DCSUWF_PWIMAWY_SUWFACE_ADDWESS_HIGH,
			PWIMAWY_SUWFACE_ADDWESS, &s->pwimawy_suwface_addw_hi);

	WEG_GET(DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS,
			PWIMAWY_META_SUWFACE_ADDWESS, &s->pwimawy_meta_addw_wo);

	WEG_GET(DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_HIGH,
			PWIMAWY_META_SUWFACE_ADDWESS, &s->pwimawy_meta_addw_hi);
}

void hubp2_wead_state(stwuct hubp *hubp)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	stwuct dcn_hubp_state *s = &hubp2->state;
	stwuct _vcs_dpi_dispway_wq_wegs_st *wq_wegs = &s->wq_wegs;

	hubp2_wead_state_common(hubp);

	WEG_GET_8(DCHUBP_WEQ_SIZE_CONFIG,
		CHUNK_SIZE, &wq_wegs->wq_wegs_w.chunk_size,
		MIN_CHUNK_SIZE, &wq_wegs->wq_wegs_w.min_chunk_size,
		META_CHUNK_SIZE, &wq_wegs->wq_wegs_w.meta_chunk_size,
		MIN_META_CHUNK_SIZE, &wq_wegs->wq_wegs_w.min_meta_chunk_size,
		DPTE_GWOUP_SIZE, &wq_wegs->wq_wegs_w.dpte_gwoup_size,
		MPTE_GWOUP_SIZE, &wq_wegs->wq_wegs_w.mpte_gwoup_size,
		SWATH_HEIGHT, &wq_wegs->wq_wegs_w.swath_height,
		PTE_WOW_HEIGHT_WINEAW, &wq_wegs->wq_wegs_w.pte_wow_height_wineaw);

	WEG_GET_8(DCHUBP_WEQ_SIZE_CONFIG_C,
		CHUNK_SIZE_C, &wq_wegs->wq_wegs_c.chunk_size,
		MIN_CHUNK_SIZE_C, &wq_wegs->wq_wegs_c.min_chunk_size,
		META_CHUNK_SIZE_C, &wq_wegs->wq_wegs_c.meta_chunk_size,
		MIN_META_CHUNK_SIZE_C, &wq_wegs->wq_wegs_c.min_meta_chunk_size,
		DPTE_GWOUP_SIZE_C, &wq_wegs->wq_wegs_c.dpte_gwoup_size,
		MPTE_GWOUP_SIZE_C, &wq_wegs->wq_wegs_c.mpte_gwoup_size,
		SWATH_HEIGHT_C, &wq_wegs->wq_wegs_c.swath_height,
		PTE_WOW_HEIGHT_WINEAW_C, &wq_wegs->wq_wegs_c.pte_wow_height_wineaw);

}

static void hubp2_vawidate_dmw_output(stwuct hubp *hubp,
		stwuct dc_context *ctx,
		stwuct _vcs_dpi_dispway_wq_wegs_st *dmw_wq_wegs,
		stwuct _vcs_dpi_dispway_dwg_wegs_st *dmw_dwg_attw,
		stwuct _vcs_dpi_dispway_ttu_wegs_st *dmw_ttu_attw)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	stwuct _vcs_dpi_dispway_wq_wegs_st wq_wegs = {0};
	stwuct _vcs_dpi_dispway_dwg_wegs_st dwg_attw = {0};
	stwuct _vcs_dpi_dispway_ttu_wegs_st ttu_attw = {0};
	DC_WOGGEW_INIT(ctx->woggew);
	DC_WOG_DEBUG("DMW Vawidation | Wunning Vawidation");

	/* Wequestow Wegs */
	WEG_GET(HUBPWET_CONTWOW,
		DET_BUF_PWANE1_BASE_ADDWESS, &wq_wegs.pwane1_base_addwess);
	WEG_GET_4(DCN_EXPANSION_MODE,
		DWQ_EXPANSION_MODE, &wq_wegs.dwq_expansion_mode,
		PWQ_EXPANSION_MODE, &wq_wegs.pwq_expansion_mode,
		MWQ_EXPANSION_MODE, &wq_wegs.mwq_expansion_mode,
		CWQ_EXPANSION_MODE, &wq_wegs.cwq_expansion_mode);
	WEG_GET_8(DCHUBP_WEQ_SIZE_CONFIG,
		CHUNK_SIZE, &wq_wegs.wq_wegs_w.chunk_size,
		MIN_CHUNK_SIZE, &wq_wegs.wq_wegs_w.min_chunk_size,
		META_CHUNK_SIZE, &wq_wegs.wq_wegs_w.meta_chunk_size,
		MIN_META_CHUNK_SIZE, &wq_wegs.wq_wegs_w.min_meta_chunk_size,
		DPTE_GWOUP_SIZE, &wq_wegs.wq_wegs_w.dpte_gwoup_size,
		MPTE_GWOUP_SIZE, &wq_wegs.wq_wegs_w.mpte_gwoup_size,
		SWATH_HEIGHT, &wq_wegs.wq_wegs_w.swath_height,
		PTE_WOW_HEIGHT_WINEAW, &wq_wegs.wq_wegs_w.pte_wow_height_wineaw);
	WEG_GET_8(DCHUBP_WEQ_SIZE_CONFIG_C,
		CHUNK_SIZE_C, &wq_wegs.wq_wegs_c.chunk_size,
		MIN_CHUNK_SIZE_C, &wq_wegs.wq_wegs_c.min_chunk_size,
		META_CHUNK_SIZE_C, &wq_wegs.wq_wegs_c.meta_chunk_size,
		MIN_META_CHUNK_SIZE_C, &wq_wegs.wq_wegs_c.min_meta_chunk_size,
		DPTE_GWOUP_SIZE_C, &wq_wegs.wq_wegs_c.dpte_gwoup_size,
		MPTE_GWOUP_SIZE_C, &wq_wegs.wq_wegs_c.mpte_gwoup_size,
		SWATH_HEIGHT_C, &wq_wegs.wq_wegs_c.swath_height,
		PTE_WOW_HEIGHT_WINEAW_C, &wq_wegs.wq_wegs_c.pte_wow_height_wineaw);

	if (wq_wegs.pwane1_base_addwess != dmw_wq_wegs->pwane1_base_addwess)
		DC_WOG_DEBUG("DMW Vawidation | HUBPWET_CONTWOW:DET_BUF_PWANE1_BASE_ADDWESS - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->pwane1_base_addwess, wq_wegs.pwane1_base_addwess);
	if (wq_wegs.dwq_expansion_mode != dmw_wq_wegs->dwq_expansion_mode)
		DC_WOG_DEBUG("DMW Vawidation | DCN_EXPANSION_MODE:DWQ_EXPANSION_MODE - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->dwq_expansion_mode, wq_wegs.dwq_expansion_mode);
	if (wq_wegs.pwq_expansion_mode != dmw_wq_wegs->pwq_expansion_mode)
		DC_WOG_DEBUG("DMW Vawidation | DCN_EXPANSION_MODE:MWQ_EXPANSION_MODE - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->pwq_expansion_mode, wq_wegs.pwq_expansion_mode);
	if (wq_wegs.mwq_expansion_mode != dmw_wq_wegs->mwq_expansion_mode)
		DC_WOG_DEBUG("DMW Vawidation | DCN_EXPANSION_MODE:DET_BUF_PWANE1_BASE_ADDWESS - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->mwq_expansion_mode, wq_wegs.mwq_expansion_mode);
	if (wq_wegs.cwq_expansion_mode != dmw_wq_wegs->cwq_expansion_mode)
		DC_WOG_DEBUG("DMW Vawidation | DCN_EXPANSION_MODE:CWQ_EXPANSION_MODE - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->cwq_expansion_mode, wq_wegs.cwq_expansion_mode);

	if (wq_wegs.wq_wegs_w.chunk_size != dmw_wq_wegs->wq_wegs_w.chunk_size)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG_C:CHUNK_SIZE - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_w.chunk_size, wq_wegs.wq_wegs_w.chunk_size);
	if (wq_wegs.wq_wegs_w.min_chunk_size != dmw_wq_wegs->wq_wegs_w.min_chunk_size)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG_C:MIN_CHUNK_SIZE - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_w.min_chunk_size, wq_wegs.wq_wegs_w.min_chunk_size);
	if (wq_wegs.wq_wegs_w.meta_chunk_size != dmw_wq_wegs->wq_wegs_w.meta_chunk_size)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG_C:META_CHUNK_SIZE - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_w.meta_chunk_size, wq_wegs.wq_wegs_w.meta_chunk_size);
	if (wq_wegs.wq_wegs_w.min_meta_chunk_size != dmw_wq_wegs->wq_wegs_w.min_meta_chunk_size)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG_C:MIN_META_CHUNK_SIZE - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_w.min_meta_chunk_size, wq_wegs.wq_wegs_w.min_meta_chunk_size);
	if (wq_wegs.wq_wegs_w.dpte_gwoup_size != dmw_wq_wegs->wq_wegs_w.dpte_gwoup_size)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG_C:DPTE_GWOUP_SIZE - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_w.dpte_gwoup_size, wq_wegs.wq_wegs_w.dpte_gwoup_size);
	if (wq_wegs.wq_wegs_w.mpte_gwoup_size != dmw_wq_wegs->wq_wegs_w.mpte_gwoup_size)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG_C:MPTE_GWOUP_SIZE - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_w.mpte_gwoup_size, wq_wegs.wq_wegs_w.mpte_gwoup_size);
	if (wq_wegs.wq_wegs_w.swath_height != dmw_wq_wegs->wq_wegs_w.swath_height)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG_C:SWATH_HEIGHT - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_w.swath_height, wq_wegs.wq_wegs_w.swath_height);
	if (wq_wegs.wq_wegs_w.pte_wow_height_wineaw != dmw_wq_wegs->wq_wegs_w.pte_wow_height_wineaw)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG_C:PTE_WOW_HEIGHT_WINEAW - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_w.pte_wow_height_wineaw, wq_wegs.wq_wegs_w.pte_wow_height_wineaw);

	if (wq_wegs.wq_wegs_c.chunk_size != dmw_wq_wegs->wq_wegs_c.chunk_size)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG:CHUNK_SIZE_C - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_c.chunk_size, wq_wegs.wq_wegs_c.chunk_size);
	if (wq_wegs.wq_wegs_c.min_chunk_size != dmw_wq_wegs->wq_wegs_c.min_chunk_size)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG:MIN_CHUNK_SIZE_C - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_c.min_chunk_size, wq_wegs.wq_wegs_c.min_chunk_size);
	if (wq_wegs.wq_wegs_c.meta_chunk_size != dmw_wq_wegs->wq_wegs_c.meta_chunk_size)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG:META_CHUNK_SIZE_C - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_c.meta_chunk_size, wq_wegs.wq_wegs_c.meta_chunk_size);
	if (wq_wegs.wq_wegs_c.min_meta_chunk_size != dmw_wq_wegs->wq_wegs_c.min_meta_chunk_size)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG:MIN_META_CHUNK_SIZE_C - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_c.min_meta_chunk_size, wq_wegs.wq_wegs_c.min_meta_chunk_size);
	if (wq_wegs.wq_wegs_c.dpte_gwoup_size != dmw_wq_wegs->wq_wegs_c.dpte_gwoup_size)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG:DPTE_GWOUP_SIZE_C - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_c.dpte_gwoup_size, wq_wegs.wq_wegs_c.dpte_gwoup_size);
	if (wq_wegs.wq_wegs_c.mpte_gwoup_size != dmw_wq_wegs->wq_wegs_c.mpte_gwoup_size)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG:MPTE_GWOUP_SIZE_C - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_c.mpte_gwoup_size, wq_wegs.wq_wegs_c.mpte_gwoup_size);
	if (wq_wegs.wq_wegs_c.swath_height != dmw_wq_wegs->wq_wegs_c.swath_height)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG:SWATH_HEIGHT_C - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_c.swath_height, wq_wegs.wq_wegs_c.swath_height);
	if (wq_wegs.wq_wegs_c.pte_wow_height_wineaw != dmw_wq_wegs->wq_wegs_c.pte_wow_height_wineaw)
		DC_WOG_DEBUG("DMW Vawidation | DCHUBP_WEQ_SIZE_CONFIG:PTE_WOW_HEIGHT_WINEAW_C - Expected: %u  Actuaw: %u\n",
				dmw_wq_wegs->wq_wegs_c.pte_wow_height_wineaw, wq_wegs.wq_wegs_c.pte_wow_height_wineaw);

	/* DWG - Pew hubp */
	WEG_GET_2(BWANK_OFFSET_0,
		WEFCYC_H_BWANK_END, &dwg_attw.wefcyc_h_bwank_end,
		DWG_V_BWANK_END, &dwg_attw.dwg_vbwank_end);
	WEG_GET(BWANK_OFFSET_1,
		MIN_DST_Y_NEXT_STAWT, &dwg_attw.min_dst_y_next_stawt);
	WEG_GET(DST_DIMENSIONS,
		WEFCYC_PEW_HTOTAW, &dwg_attw.wefcyc_pew_htotaw);
	WEG_GET_2(DST_AFTEW_SCAWEW,
		WEFCYC_X_AFTEW_SCAWEW, &dwg_attw.wefcyc_x_aftew_scawew,
		DST_Y_AFTEW_SCAWEW, &dwg_attw.dst_y_aftew_scawew);
	WEG_GET(WEF_FWEQ_TO_PIX_FWEQ,
		WEF_FWEQ_TO_PIX_FWEQ, &dwg_attw.wef_fweq_to_pix_fweq);

	if (dwg_attw.wefcyc_h_bwank_end != dmw_dwg_attw->wefcyc_h_bwank_end)
		DC_WOG_DEBUG("DMW Vawidation | BWANK_OFFSET_0:WEFCYC_H_BWANK_END - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_h_bwank_end, dwg_attw.wefcyc_h_bwank_end);
	if (dwg_attw.dwg_vbwank_end != dmw_dwg_attw->dwg_vbwank_end)
		DC_WOG_DEBUG("DMW Vawidation | BWANK_OFFSET_0:DWG_V_BWANK_END - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->dwg_vbwank_end, dwg_attw.dwg_vbwank_end);
	if (dwg_attw.min_dst_y_next_stawt != dmw_dwg_attw->min_dst_y_next_stawt)
		DC_WOG_DEBUG("DMW Vawidation | BWANK_OFFSET_1:MIN_DST_Y_NEXT_STAWT - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->min_dst_y_next_stawt, dwg_attw.min_dst_y_next_stawt);
	if (dwg_attw.wefcyc_pew_htotaw != dmw_dwg_attw->wefcyc_pew_htotaw)
		DC_WOG_DEBUG("DMW Vawidation | DST_DIMENSIONS:WEFCYC_PEW_HTOTAW - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_htotaw, dwg_attw.wefcyc_pew_htotaw);
	if (dwg_attw.wefcyc_x_aftew_scawew != dmw_dwg_attw->wefcyc_x_aftew_scawew)
		DC_WOG_DEBUG("DMW Vawidation | DST_AFTEW_SCAWEW:WEFCYC_X_AFTEW_SCAWEW - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_x_aftew_scawew, dwg_attw.wefcyc_x_aftew_scawew);
	if (dwg_attw.dst_y_aftew_scawew != dmw_dwg_attw->dst_y_aftew_scawew)
		DC_WOG_DEBUG("DMW Vawidation | DST_AFTEW_SCAWEW:DST_Y_AFTEW_SCAWEW - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->dst_y_aftew_scawew, dwg_attw.dst_y_aftew_scawew);
	if (dwg_attw.wef_fweq_to_pix_fweq != dmw_dwg_attw->wef_fweq_to_pix_fweq)
		DC_WOG_DEBUG("DMW Vawidation | WEF_FWEQ_TO_PIX_FWEQ:WEF_FWEQ_TO_PIX_FWEQ - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wef_fweq_to_pix_fweq, dwg_attw.wef_fweq_to_pix_fweq);

	/* DWG - Pew wuma/chwoma */
	WEG_GET(VBWANK_PAWAMETEWS_1,
		WEFCYC_PEW_PTE_GWOUP_VBWANK_W, &dwg_attw.wefcyc_pew_pte_gwoup_vbwank_w);
	if (WEG(NOM_PAWAMETEWS_0))
		WEG_GET(NOM_PAWAMETEWS_0,
			DST_Y_PEW_PTE_WOW_NOM_W, &dwg_attw.dst_y_pew_pte_wow_nom_w);
	if (WEG(NOM_PAWAMETEWS_1))
		WEG_GET(NOM_PAWAMETEWS_1,
			WEFCYC_PEW_PTE_GWOUP_NOM_W, &dwg_attw.wefcyc_pew_pte_gwoup_nom_w);
	WEG_GET(NOM_PAWAMETEWS_4,
		DST_Y_PEW_META_WOW_NOM_W, &dwg_attw.dst_y_pew_meta_wow_nom_w);
	WEG_GET(NOM_PAWAMETEWS_5,
		WEFCYC_PEW_META_CHUNK_NOM_W, &dwg_attw.wefcyc_pew_meta_chunk_nom_w);
	WEG_GET_2(PEW_WINE_DEWIVEWY,
		WEFCYC_PEW_WINE_DEWIVEWY_W, &dwg_attw.wefcyc_pew_wine_dewivewy_w,
		WEFCYC_PEW_WINE_DEWIVEWY_C, &dwg_attw.wefcyc_pew_wine_dewivewy_c);
	WEG_GET_2(PEW_WINE_DEWIVEWY_PWE,
		WEFCYC_PEW_WINE_DEWIVEWY_PWE_W, &dwg_attw.wefcyc_pew_wine_dewivewy_pwe_w,
		WEFCYC_PEW_WINE_DEWIVEWY_PWE_C, &dwg_attw.wefcyc_pew_wine_dewivewy_pwe_c);
	WEG_GET(VBWANK_PAWAMETEWS_2,
		WEFCYC_PEW_PTE_GWOUP_VBWANK_C, &dwg_attw.wefcyc_pew_pte_gwoup_vbwank_c);
	if (WEG(NOM_PAWAMETEWS_2))
		WEG_GET(NOM_PAWAMETEWS_2,
			DST_Y_PEW_PTE_WOW_NOM_C, &dwg_attw.dst_y_pew_pte_wow_nom_c);
	if (WEG(NOM_PAWAMETEWS_3))
		WEG_GET(NOM_PAWAMETEWS_3,
			WEFCYC_PEW_PTE_GWOUP_NOM_C, &dwg_attw.wefcyc_pew_pte_gwoup_nom_c);
	WEG_GET(NOM_PAWAMETEWS_6,
		DST_Y_PEW_META_WOW_NOM_C, &dwg_attw.dst_y_pew_meta_wow_nom_c);
	WEG_GET(NOM_PAWAMETEWS_7,
		WEFCYC_PEW_META_CHUNK_NOM_C, &dwg_attw.wefcyc_pew_meta_chunk_nom_c);
	WEG_GET(VBWANK_PAWAMETEWS_3,
			WEFCYC_PEW_META_CHUNK_VBWANK_W, &dwg_attw.wefcyc_pew_meta_chunk_vbwank_w);
	WEG_GET(VBWANK_PAWAMETEWS_4,
			WEFCYC_PEW_META_CHUNK_VBWANK_C, &dwg_attw.wefcyc_pew_meta_chunk_vbwank_c);

	if (dwg_attw.wefcyc_pew_pte_gwoup_vbwank_w != dmw_dwg_attw->wefcyc_pew_pte_gwoup_vbwank_w)
		DC_WOG_DEBUG("DMW Vawidation | VBWANK_PAWAMETEWS_1:WEFCYC_PEW_PTE_GWOUP_VBWANK_W - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_pte_gwoup_vbwank_w, dwg_attw.wefcyc_pew_pte_gwoup_vbwank_w);
	if (dwg_attw.dst_y_pew_pte_wow_nom_w != dmw_dwg_attw->dst_y_pew_pte_wow_nom_w)
		DC_WOG_DEBUG("DMW Vawidation | NOM_PAWAMETEWS_0:DST_Y_PEW_PTE_WOW_NOM_W - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->dst_y_pew_pte_wow_nom_w, dwg_attw.dst_y_pew_pte_wow_nom_w);
	if (dwg_attw.wefcyc_pew_pte_gwoup_nom_w != dmw_dwg_attw->wefcyc_pew_pte_gwoup_nom_w)
		DC_WOG_DEBUG("DMW Vawidation | NOM_PAWAMETEWS_1:WEFCYC_PEW_PTE_GWOUP_NOM_W - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_pte_gwoup_nom_w, dwg_attw.wefcyc_pew_pte_gwoup_nom_w);
	if (dwg_attw.dst_y_pew_meta_wow_nom_w != dmw_dwg_attw->dst_y_pew_meta_wow_nom_w)
		DC_WOG_DEBUG("DMW Vawidation | NOM_PAWAMETEWS_4:DST_Y_PEW_META_WOW_NOM_W - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->dst_y_pew_meta_wow_nom_w, dwg_attw.dst_y_pew_meta_wow_nom_w);
	if (dwg_attw.wefcyc_pew_meta_chunk_nom_w != dmw_dwg_attw->wefcyc_pew_meta_chunk_nom_w)
		DC_WOG_DEBUG("DMW Vawidation | NOM_PAWAMETEWS_5:WEFCYC_PEW_META_CHUNK_NOM_W - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_meta_chunk_nom_w, dwg_attw.wefcyc_pew_meta_chunk_nom_w);
	if (dwg_attw.wefcyc_pew_wine_dewivewy_w != dmw_dwg_attw->wefcyc_pew_wine_dewivewy_w)
		DC_WOG_DEBUG("DMW Vawidation | PEW_WINE_DEWIVEWY:WEFCYC_PEW_WINE_DEWIVEWY_W - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_wine_dewivewy_w, dwg_attw.wefcyc_pew_wine_dewivewy_w);
	if (dwg_attw.wefcyc_pew_wine_dewivewy_c != dmw_dwg_attw->wefcyc_pew_wine_dewivewy_c)
		DC_WOG_DEBUG("DMW Vawidation | PEW_WINE_DEWIVEWY:WEFCYC_PEW_WINE_DEWIVEWY_C - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_wine_dewivewy_c, dwg_attw.wefcyc_pew_wine_dewivewy_c);
	if (dwg_attw.wefcyc_pew_pte_gwoup_vbwank_c != dmw_dwg_attw->wefcyc_pew_pte_gwoup_vbwank_c)
		DC_WOG_DEBUG("DMW Vawidation | VBWANK_PAWAMETEWS_2:WEFCYC_PEW_PTE_GWOUP_VBWANK_C - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_pte_gwoup_vbwank_c, dwg_attw.wefcyc_pew_pte_gwoup_vbwank_c);
	if (dwg_attw.dst_y_pew_pte_wow_nom_c != dmw_dwg_attw->dst_y_pew_pte_wow_nom_c)
		DC_WOG_DEBUG("DMW Vawidation | NOM_PAWAMETEWS_2:DST_Y_PEW_PTE_WOW_NOM_C - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->dst_y_pew_pte_wow_nom_c, dwg_attw.dst_y_pew_pte_wow_nom_c);
	if (dwg_attw.wefcyc_pew_pte_gwoup_nom_c != dmw_dwg_attw->wefcyc_pew_pte_gwoup_nom_c)
		DC_WOG_DEBUG("DMW Vawidation | NOM_PAWAMETEWS_3:WEFCYC_PEW_PTE_GWOUP_NOM_C - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_pte_gwoup_nom_c, dwg_attw.wefcyc_pew_pte_gwoup_nom_c);
	if (dwg_attw.dst_y_pew_meta_wow_nom_c != dmw_dwg_attw->dst_y_pew_meta_wow_nom_c)
		DC_WOG_DEBUG("DMW Vawidation | NOM_PAWAMETEWS_6:DST_Y_PEW_META_WOW_NOM_C - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->dst_y_pew_meta_wow_nom_c, dwg_attw.dst_y_pew_meta_wow_nom_c);
	if (dwg_attw.wefcyc_pew_meta_chunk_nom_c != dmw_dwg_attw->wefcyc_pew_meta_chunk_nom_c)
		DC_WOG_DEBUG("DMW Vawidation | NOM_PAWAMETEWS_7:WEFCYC_PEW_META_CHUNK_NOM_C - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_meta_chunk_nom_c, dwg_attw.wefcyc_pew_meta_chunk_nom_c);
	if (dwg_attw.wefcyc_pew_wine_dewivewy_pwe_w != dmw_dwg_attw->wefcyc_pew_wine_dewivewy_pwe_w)
		DC_WOG_DEBUG("DMW Vawidation | PEW_WINE_DEWIVEWY_PWE:WEFCYC_PEW_WINE_DEWIVEWY_PWE_W - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_wine_dewivewy_pwe_w, dwg_attw.wefcyc_pew_wine_dewivewy_pwe_w);
	if (dwg_attw.wefcyc_pew_wine_dewivewy_pwe_c != dmw_dwg_attw->wefcyc_pew_wine_dewivewy_pwe_c)
		DC_WOG_DEBUG("DMW Vawidation | PEW_WINE_DEWIVEWY_PWE:WEFCYC_PEW_WINE_DEWIVEWY_PWE_C - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_wine_dewivewy_pwe_c, dwg_attw.wefcyc_pew_wine_dewivewy_pwe_c);
	if (dwg_attw.wefcyc_pew_meta_chunk_vbwank_w != dmw_dwg_attw->wefcyc_pew_meta_chunk_vbwank_w)
		DC_WOG_DEBUG("DMW Vawidation | VBWANK_PAWAMETEWS_3:WEFCYC_PEW_META_CHUNK_VBWANK_W - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_meta_chunk_vbwank_w, dwg_attw.wefcyc_pew_meta_chunk_vbwank_w);
	if (dwg_attw.wefcyc_pew_meta_chunk_vbwank_c != dmw_dwg_attw->wefcyc_pew_meta_chunk_vbwank_c)
		DC_WOG_DEBUG("DMW Vawidation | VBWANK_PAWAMETEWS_4:WEFCYC_PEW_META_CHUNK_VBWANK_C - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_meta_chunk_vbwank_c, dwg_attw.wefcyc_pew_meta_chunk_vbwank_c);

	/* TTU - pew hubp */
	WEG_GET_2(DCN_TTU_QOS_WM,
		QoS_WEVEW_WOW_WM, &ttu_attw.qos_wevew_wow_wm,
		QoS_WEVEW_HIGH_WM, &ttu_attw.qos_wevew_high_wm);

	if (ttu_attw.qos_wevew_wow_wm != dmw_ttu_attw->qos_wevew_wow_wm)
		DC_WOG_DEBUG("DMW Vawidation | DCN_TTU_QOS_WM:QoS_WEVEW_WOW_WM - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->qos_wevew_wow_wm, ttu_attw.qos_wevew_wow_wm);
	if (ttu_attw.qos_wevew_high_wm != dmw_ttu_attw->qos_wevew_high_wm)
		DC_WOG_DEBUG("DMW Vawidation | DCN_TTU_QOS_WM:QoS_WEVEW_HIGH_WM - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->qos_wevew_high_wm, ttu_attw.qos_wevew_high_wm);

	/* TTU - pew wuma/chwoma */
	/* Assumed suwf0 is wuma and 1 is chwoma */
	WEG_GET_3(DCN_SUWF0_TTU_CNTW0,
		WEFCYC_PEW_WEQ_DEWIVEWY, &ttu_attw.wefcyc_pew_weq_dewivewy_w,
		QoS_WEVEW_FIXED, &ttu_attw.qos_wevew_fixed_w,
		QoS_WAMP_DISABWE, &ttu_attw.qos_wamp_disabwe_w);
	WEG_GET_3(DCN_SUWF1_TTU_CNTW0,
		WEFCYC_PEW_WEQ_DEWIVEWY, &ttu_attw.wefcyc_pew_weq_dewivewy_c,
		QoS_WEVEW_FIXED, &ttu_attw.qos_wevew_fixed_c,
		QoS_WAMP_DISABWE, &ttu_attw.qos_wamp_disabwe_c);
	WEG_GET_3(DCN_CUW0_TTU_CNTW0,
		WEFCYC_PEW_WEQ_DEWIVEWY, &ttu_attw.wefcyc_pew_weq_dewivewy_cuw0,
		QoS_WEVEW_FIXED, &ttu_attw.qos_wevew_fixed_cuw0,
		QoS_WAMP_DISABWE, &ttu_attw.qos_wamp_disabwe_cuw0);
	WEG_GET(FWIP_PAWAMETEWS_1,
		WEFCYC_PEW_PTE_GWOUP_FWIP_W, &dwg_attw.wefcyc_pew_pte_gwoup_fwip_w);
	WEG_GET(DCN_CUW0_TTU_CNTW1,
			WEFCYC_PEW_WEQ_DEWIVEWY_PWE, &ttu_attw.wefcyc_pew_weq_dewivewy_pwe_cuw0);
	WEG_GET(DCN_CUW1_TTU_CNTW1,
			WEFCYC_PEW_WEQ_DEWIVEWY_PWE, &ttu_attw.wefcyc_pew_weq_dewivewy_pwe_cuw1);
	WEG_GET(DCN_SUWF0_TTU_CNTW1,
			WEFCYC_PEW_WEQ_DEWIVEWY_PWE, &ttu_attw.wefcyc_pew_weq_dewivewy_pwe_w);
	WEG_GET(DCN_SUWF1_TTU_CNTW1,
			WEFCYC_PEW_WEQ_DEWIVEWY_PWE, &ttu_attw.wefcyc_pew_weq_dewivewy_pwe_c);

	if (ttu_attw.wefcyc_pew_weq_dewivewy_w != dmw_ttu_attw->wefcyc_pew_weq_dewivewy_w)
		DC_WOG_DEBUG("DMW Vawidation | DCN_SUWF0_TTU_CNTW0:WEFCYC_PEW_WEQ_DEWIVEWY - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->wefcyc_pew_weq_dewivewy_w, ttu_attw.wefcyc_pew_weq_dewivewy_w);
	if (ttu_attw.qos_wevew_fixed_w != dmw_ttu_attw->qos_wevew_fixed_w)
		DC_WOG_DEBUG("DMW Vawidation | DCN_SUWF0_TTU_CNTW0:QoS_WEVEW_FIXED - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->qos_wevew_fixed_w, ttu_attw.qos_wevew_fixed_w);
	if (ttu_attw.qos_wamp_disabwe_w != dmw_ttu_attw->qos_wamp_disabwe_w)
		DC_WOG_DEBUG("DMW Vawidation | DCN_SUWF0_TTU_CNTW0:QoS_WAMP_DISABWE - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->qos_wamp_disabwe_w, ttu_attw.qos_wamp_disabwe_w);
	if (ttu_attw.wefcyc_pew_weq_dewivewy_c != dmw_ttu_attw->wefcyc_pew_weq_dewivewy_c)
		DC_WOG_DEBUG("DMW Vawidation | DCN_SUWF1_TTU_CNTW0:WEFCYC_PEW_WEQ_DEWIVEWY - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->wefcyc_pew_weq_dewivewy_c, ttu_attw.wefcyc_pew_weq_dewivewy_c);
	if (ttu_attw.qos_wevew_fixed_c != dmw_ttu_attw->qos_wevew_fixed_c)
		DC_WOG_DEBUG("DMW Vawidation | DCN_SUWF1_TTU_CNTW0:QoS_WEVEW_FIXED - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->qos_wevew_fixed_c, ttu_attw.qos_wevew_fixed_c);
	if (ttu_attw.qos_wamp_disabwe_c != dmw_ttu_attw->qos_wamp_disabwe_c)
		DC_WOG_DEBUG("DMW Vawidation | DCN_SUWF1_TTU_CNTW0:QoS_WAMP_DISABWE - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->qos_wamp_disabwe_c, ttu_attw.qos_wamp_disabwe_c);
	if (ttu_attw.wefcyc_pew_weq_dewivewy_cuw0 != dmw_ttu_attw->wefcyc_pew_weq_dewivewy_cuw0)
		DC_WOG_DEBUG("DMW Vawidation | DCN_CUW0_TTU_CNTW0:WEFCYC_PEW_WEQ_DEWIVEWY - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->wefcyc_pew_weq_dewivewy_cuw0, ttu_attw.wefcyc_pew_weq_dewivewy_cuw0);
	if (ttu_attw.qos_wevew_fixed_cuw0 != dmw_ttu_attw->qos_wevew_fixed_cuw0)
		DC_WOG_DEBUG("DMW Vawidation | DCN_CUW0_TTU_CNTW0:QoS_WEVEW_FIXED - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->qos_wevew_fixed_cuw0, ttu_attw.qos_wevew_fixed_cuw0);
	if (ttu_attw.qos_wamp_disabwe_cuw0 != dmw_ttu_attw->qos_wamp_disabwe_cuw0)
		DC_WOG_DEBUG("DMW Vawidation | DCN_CUW0_TTU_CNTW0:QoS_WAMP_DISABWE - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->qos_wamp_disabwe_cuw0, ttu_attw.qos_wamp_disabwe_cuw0);
	if (dwg_attw.wefcyc_pew_pte_gwoup_fwip_w != dmw_dwg_attw->wefcyc_pew_pte_gwoup_fwip_w)
		DC_WOG_DEBUG("DMW Vawidation | FWIP_PAWAMETEWS_1:WEFCYC_PEW_PTE_GWOUP_FWIP_W - Expected: %u  Actuaw: %u\n",
				dmw_dwg_attw->wefcyc_pew_pte_gwoup_fwip_w, dwg_attw.wefcyc_pew_pte_gwoup_fwip_w);
	if (ttu_attw.wefcyc_pew_weq_dewivewy_pwe_cuw0 != dmw_ttu_attw->wefcyc_pew_weq_dewivewy_pwe_cuw0)
		DC_WOG_DEBUG("DMW Vawidation | DCN_CUW0_TTU_CNTW1:WEFCYC_PEW_WEQ_DEWIVEWY_PWE - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->wefcyc_pew_weq_dewivewy_pwe_cuw0, ttu_attw.wefcyc_pew_weq_dewivewy_pwe_cuw0);
	if (ttu_attw.wefcyc_pew_weq_dewivewy_pwe_cuw1 != dmw_ttu_attw->wefcyc_pew_weq_dewivewy_pwe_cuw1)
		DC_WOG_DEBUG("DMW Vawidation | DCN_CUW1_TTU_CNTW1:WEFCYC_PEW_WEQ_DEWIVEWY_PWE - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->wefcyc_pew_weq_dewivewy_pwe_cuw1, ttu_attw.wefcyc_pew_weq_dewivewy_pwe_cuw1);
	if (ttu_attw.wefcyc_pew_weq_dewivewy_pwe_w != dmw_ttu_attw->wefcyc_pew_weq_dewivewy_pwe_w)
		DC_WOG_DEBUG("DMW Vawidation | DCN_SUWF0_TTU_CNTW1:WEFCYC_PEW_WEQ_DEWIVEWY_PWE - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->wefcyc_pew_weq_dewivewy_pwe_w, ttu_attw.wefcyc_pew_weq_dewivewy_pwe_w);
	if (ttu_attw.wefcyc_pew_weq_dewivewy_pwe_c != dmw_ttu_attw->wefcyc_pew_weq_dewivewy_pwe_c)
		DC_WOG_DEBUG("DMW Vawidation | DCN_SUWF1_TTU_CNTW1:WEFCYC_PEW_WEQ_DEWIVEWY_PWE - Expected: %u  Actuaw: %u\n",
				dmw_ttu_attw->wefcyc_pew_weq_dewivewy_pwe_c, ttu_attw.wefcyc_pew_weq_dewivewy_pwe_c);
}

static stwuct hubp_funcs dcn20_hubp_funcs = {
	.hubp_enabwe_twipweBuffew = hubp2_enabwe_twipwebuffew,
	.hubp_is_twipwebuffew_enabwed = hubp2_is_twipwebuffew_enabwed,
	.hubp_pwogwam_suwface_fwip_and_addw = hubp2_pwogwam_suwface_fwip_and_addw,
	.hubp_pwogwam_suwface_config = hubp2_pwogwam_suwface_config,
	.hubp_is_fwip_pending = hubp2_is_fwip_pending,
	.hubp_setup = hubp2_setup,
	.hubp_setup_intewdependent = hubp2_setup_intewdependent,
	.hubp_set_vm_system_apewtuwe_settings = hubp2_set_vm_system_apewtuwe_settings,
	.set_bwank = hubp2_set_bwank,
	.set_bwank_wegs = hubp2_set_bwank_wegs,
	.dcc_contwow = hubp2_dcc_contwow,
	.mem_pwogwam_viewpowt = min_set_viewpowt,
	.set_cuwsow_attwibutes	= hubp2_cuwsow_set_attwibutes,
	.set_cuwsow_position	= hubp2_cuwsow_set_position,
	.hubp_cwk_cntw = hubp2_cwk_cntw,
	.hubp_vtg_sew = hubp2_vtg_sew,
	.dmdata_set_attwibutes = hubp2_dmdata_set_attwibutes,
	.dmdata_woad = hubp2_dmdata_woad,
	.dmdata_status_done = hubp2_dmdata_status_done,
	.hubp_wead_state = hubp2_wead_state,
	.hubp_cweaw_undewfwow = hubp2_cweaw_undewfwow,
	.hubp_set_fwip_contwow_suwface_gsw = hubp2_set_fwip_contwow_suwface_gsw,
	.hubp_init = hubp1_init,
	.vawidate_dmw_output = hubp2_vawidate_dmw_output,
	.hubp_in_bwank = hubp1_in_bwank,
	.hubp_soft_weset = hubp1_soft_weset,
	.hubp_set_fwip_int = hubp1_set_fwip_int,
};


boow hubp2_constwuct(
	stwuct dcn20_hubp *hubp2,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dcn_hubp2_wegistews *hubp_wegs,
	const stwuct dcn_hubp2_shift *hubp_shift,
	const stwuct dcn_hubp2_mask *hubp_mask)
{
	hubp2->base.funcs = &dcn20_hubp_funcs;
	hubp2->base.ctx = ctx;
	hubp2->hubp_wegs = hubp_wegs;
	hubp2->hubp_shift = hubp_shift;
	hubp2->hubp_mask = hubp_mask;
	hubp2->base.inst = inst;
	hubp2->base.opp_id = OPP_ID_INVAWID;
	hubp2->base.mpcc_id = 0xf;

	wetuwn twue;
}
