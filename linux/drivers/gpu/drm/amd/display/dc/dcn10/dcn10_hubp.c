/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
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
#incwude "dce_cawcs.h"
#incwude "weg_hewpew.h"
#incwude "basics/convewsion.h"
#incwude "dcn10_hubp.h"

#define WEG(weg)\
	hubp1->hubp_wegs->weg

#define CTX \
	hubp1->base.ctx

#undef FN
#define FN(weg_name, fiewd_name) \
	hubp1->hubp_shift->fiewd_name, hubp1->hubp_mask->fiewd_name

void hubp1_set_bwank(stwuct hubp *hubp, boow bwank)
{
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
	uint32_t bwank_en = bwank ? 1 : 0;

	WEG_UPDATE_2(DCHUBP_CNTW,
			HUBP_BWANK_EN, bwank_en,
			HUBP_TTU_DISABWE, bwank_en);

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
					1, 200);
		}

		hubp->mpcc_id = 0xf;
		hubp->opp_id = OPP_ID_INVAWID;
	}
}

static void hubp1_disconnect(stwuct hubp *hubp)
{
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	WEG_UPDATE(DCHUBP_CNTW,
			HUBP_TTU_DISABWE, 1);

	WEG_UPDATE(CUWSOW_CONTWOW,
			CUWSOW_ENABWE, 0);
}

static void hubp1_disabwe_contwow(stwuct hubp *hubp, boow disabwe_hubp)
{
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
	uint32_t disabwe = disabwe_hubp ? 1 : 0;

	WEG_UPDATE(DCHUBP_CNTW,
			HUBP_DISABWE, disabwe);
}

static unsigned int hubp1_get_undewfwow_status(stwuct hubp *hubp)
{
	uint32_t hubp_undewfwow = 0;
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	WEG_GET(DCHUBP_CNTW,
		HUBP_UNDEWFWOW_STATUS,
		&hubp_undewfwow);

	wetuwn hubp_undewfwow;
}


void hubp1_cweaw_undewfwow(stwuct hubp *hubp)
{
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	WEG_UPDATE(DCHUBP_CNTW, HUBP_UNDEWFWOW_CWEAW, 1);
}

static void hubp1_set_hubp_bwank_en(stwuct hubp *hubp, boow bwank)
{
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
	uint32_t bwank_en = bwank ? 1 : 0;

	WEG_UPDATE(DCHUBP_CNTW, HUBP_BWANK_EN, bwank_en);
}

void hubp1_vweady_wowkawound(stwuct hubp *hubp,
		stwuct _vcs_dpi_dispway_pipe_dest_pawams_st *pipe_dest)
{
	uint32_t vawue = 0;
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	/* set HBUBWEQ_DEBUG_DB[12] = 1 */
	vawue = WEG_WEAD(HUBPWEQ_DEBUG_DB);

	/* hack mode disabwe */
	vawue |= 0x100;
	vawue &= ~0x1000;

	if ((pipe_dest->vstawtup_stawt - 2*(pipe_dest->vweady_offset+pipe_dest->vupdate_width
		+ pipe_dest->vupdate_offset) / pipe_dest->htotaw) <= pipe_dest->vbwank_end) {
		/* if (eco_fix_needed(otg_gwobaw_sync_timing)
		 * set HBUBWEQ_DEBUG_DB[12] = 1 */
		vawue |= 0x1000;
	}

	WEG_WWITE(HUBPWEQ_DEBUG_DB, vawue);
}

void hubp1_pwogwam_tiwing(
	stwuct hubp *hubp,
	const union dc_tiwing_info *info,
	const enum suwface_pixew_fowmat pixew_fowmat)
{
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	WEG_UPDATE_6(DCSUWF_ADDW_CONFIG,
			NUM_PIPES, wog_2(info->gfx9.num_pipes),
			NUM_BANKS, wog_2(info->gfx9.num_banks),
			PIPE_INTEWWEAVE, info->gfx9.pipe_intewweave,
			NUM_SE, wog_2(info->gfx9.num_shadew_engines),
			NUM_WB_PEW_SE, wog_2(info->gfx9.num_wb_pew_se),
			MAX_COMPWESSED_FWAGS, wog_2(info->gfx9.max_compwessed_fwags));

	WEG_UPDATE_4(DCSUWF_TIWING_CONFIG,
			SW_MODE, info->gfx9.swizzwe,
			META_WINEAW, info->gfx9.meta_wineaw,
			WB_AWIGNED, info->gfx9.wb_awigned,
			PIPE_AWIGNED, info->gfx9.pipe_awigned);
}

void hubp1_pwogwam_size(
	stwuct hubp *hubp,
	enum suwface_pixew_fowmat fowmat,
	const stwuct pwane_size *pwane_size,
	stwuct dc_pwane_dcc_pawam *dcc)
{
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
	uint32_t pitch, meta_pitch, pitch_c, meta_pitch_c;

	/* Pwogwam data and meta suwface pitch (cawcuwation fwom addwwib)
	 * 444 ow 420 wuma
	 */
	if (fowmat >= SUWFACE_PIXEW_FOWMAT_VIDEO_BEGIN && fowmat < SUWFACE_PIXEW_FOWMAT_SUBSAMPWE_END) {
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

	if (fowmat >= SUWFACE_PIXEW_FOWMAT_VIDEO_BEGIN)
		WEG_UPDATE_2(DCSUWF_SUWFACE_PITCH_C,
			PITCH_C, pitch_c, META_PITCH_C, meta_pitch_c);
}

void hubp1_pwogwam_wotation(
	stwuct hubp *hubp,
	enum dc_wotation_angwe wotation,
	boow howizontaw_miwwow)
{
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
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

void hubp1_pwogwam_pixew_fowmat(
	stwuct hubp *hubp,
	enum suwface_pixew_fowmat fowmat)
{
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
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

boow hubp1_pwogwam_suwface_fwip_and_addw(
	stwuct hubp *hubp,
	const stwuct dc_pwane_addwess *addwess,
	boow fwip_immediate)
{
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);


	//pwogwam fwip type
	WEG_UPDATE(DCSUWF_FWIP_CONTWOW,
			SUWFACE_FWIP_TYPE, fwip_immediate);


	if (addwess->type == PWN_ADDW_TYPE_GWPH_STEWEO) {
		WEG_UPDATE(DCSUWF_FWIP_CONTWOW, SUWFACE_FWIP_MODE_FOW_STEWEOSYNC, 0x1);
		WEG_UPDATE(DCSUWF_FWIP_CONTWOW, SUWFACE_FWIP_IN_STEWEOSYNC, 0x1);

	} ewse {
		// tuwn off steweo if not in steweo
		WEG_UPDATE(DCSUWF_FWIP_CONTWOW, SUWFACE_FWIP_MODE_FOW_STEWEOSYNC, 0x0);
		WEG_UPDATE(DCSUWF_FWIP_CONTWOW, SUWFACE_FWIP_IN_STEWEOSYNC, 0x0);
	}



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

void hubp1_dcc_contwow(stwuct hubp *hubp, boow enabwe,
		enum hubp_ind_bwock_size independent_64b_bwks)
{
	uint32_t dcc_en = enabwe ? 1 : 0;
	uint32_t dcc_ind_64b_bwk = independent_64b_bwks ? 1 : 0;
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	WEG_UPDATE_4(DCSUWF_SUWFACE_CONTWOW,
			PWIMAWY_SUWFACE_DCC_EN, dcc_en,
			PWIMAWY_SUWFACE_DCC_IND_64B_BWK, dcc_ind_64b_bwk,
			SECONDAWY_SUWFACE_DCC_EN, dcc_en,
			SECONDAWY_SUWFACE_DCC_IND_64B_BWK, dcc_ind_64b_bwk);
}

void hubp1_pwogwam_suwface_config(
	stwuct hubp *hubp,
	enum suwface_pixew_fowmat fowmat,
	union dc_tiwing_info *tiwing_info,
	stwuct pwane_size *pwane_size,
	enum dc_wotation_angwe wotation,
	stwuct dc_pwane_dcc_pawam *dcc,
	boow howizontaw_miwwow,
	unsigned int compat_wevew)
{
	hubp1_dcc_contwow(hubp, dcc->enabwe, dcc->independent_64b_bwks);
	hubp1_pwogwam_tiwing(hubp, tiwing_info, fowmat);
	hubp1_pwogwam_size(hubp, fowmat, pwane_size, dcc);
	hubp1_pwogwam_wotation(hubp, wotation, howizontaw_miwwow);
	hubp1_pwogwam_pixew_fowmat(hubp, fowmat);
}

void hubp1_pwogwam_wequestow(
		stwuct hubp *hubp,
		stwuct _vcs_dpi_dispway_wq_wegs_st *wq_wegs)
{
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

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


void hubp1_pwogwam_deadwine(
		stwuct hubp *hubp,
		stwuct _vcs_dpi_dispway_dwg_wegs_st *dwg_attw,
		stwuct _vcs_dpi_dispway_ttu_wegs_st *ttu_attw)
{
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

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
}

static void hubp1_setup(
		stwuct hubp *hubp,
		stwuct _vcs_dpi_dispway_dwg_wegs_st *dwg_attw,
		stwuct _vcs_dpi_dispway_ttu_wegs_st *ttu_attw,
		stwuct _vcs_dpi_dispway_wq_wegs_st *wq_wegs,
		stwuct _vcs_dpi_dispway_pipe_dest_pawams_st *pipe_dest)
{
	/* otg is wocked when this func is cawwed. Wegistew awe doubwe buffewed.
	 * disabwe the wequestows is not needed
	 */
	hubp1_pwogwam_wequestow(hubp, wq_wegs);
	hubp1_pwogwam_deadwine(hubp, dwg_attw, ttu_attw);
	hubp1_vweady_wowkawound(hubp, pipe_dest);
}

static void hubp1_setup_intewdependent(
		stwuct hubp *hubp,
		stwuct _vcs_dpi_dispway_dwg_wegs_st *dwg_attw,
		stwuct _vcs_dpi_dispway_ttu_wegs_st *ttu_attw)
{
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	WEG_SET_2(PWEFETCH_SETTINS, 0,
		DST_Y_PWEFETCH, dwg_attw->dst_y_pwefetch,
		VWATIO_PWEFETCH, dwg_attw->vwatio_pwefetch);

	WEG_SET(PWEFETCH_SETTINS_C, 0,
		VWATIO_PWEFETCH_C, dwg_attw->vwatio_pwefetch_c);

	WEG_SET_2(VBWANK_PAWAMETEWS_0, 0,
		DST_Y_PEW_VM_VBWANK, dwg_attw->dst_y_pew_vm_vbwank,
		DST_Y_PEW_WOW_VBWANK, dwg_attw->dst_y_pew_wow_vbwank);

	WEG_SET(VBWANK_PAWAMETEWS_3, 0,
		WEFCYC_PEW_META_CHUNK_VBWANK_W, dwg_attw->wefcyc_pew_meta_chunk_vbwank_w);

	WEG_SET(VBWANK_PAWAMETEWS_4, 0,
		WEFCYC_PEW_META_CHUNK_VBWANK_C, dwg_attw->wefcyc_pew_meta_chunk_vbwank_c);

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

	WEG_SET_2(DCN_GWOBAW_TTU_CNTW, 0,
		MIN_TTU_VBWANK, ttu_attw->min_ttu_vbwank,
		QoS_WEVEW_FWIP, ttu_attw->qos_wevew_fwip);
}

boow hubp1_is_fwip_pending(stwuct hubp *hubp)
{
	uint32_t fwip_pending = 0;
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
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

static uint32_t apewtuwe_defauwt_system = 1;
static uint32_t context0_defauwt_system; /* = 0;*/

static void hubp1_set_vm_system_apewtuwe_settings(stwuct hubp *hubp,
		stwuct vm_system_apewtuwe_pawam *apt)
{
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
	PHYSICAW_ADDWESS_WOC mc_vm_apt_defauwt;
	PHYSICAW_ADDWESS_WOC mc_vm_apt_wow;
	PHYSICAW_ADDWESS_WOC mc_vm_apt_high;

	mc_vm_apt_defauwt.quad_pawt = apt->sys_defauwt.quad_pawt >> 12;
	mc_vm_apt_wow.quad_pawt = apt->sys_wow.quad_pawt >> 12;
	mc_vm_apt_high.quad_pawt = apt->sys_high.quad_pawt >> 12;

	WEG_SET_2(DCN_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW_MSB, 0,
		MC_VM_SYSTEM_APEWTUWE_DEFAUWT_SYSTEM, apewtuwe_defauwt_system, /* 1 = system physicaw memowy */
		MC_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW_MSB, mc_vm_apt_defauwt.high_pawt);
	WEG_SET(DCN_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW_WSB, 0,
		MC_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW_WSB, mc_vm_apt_defauwt.wow_pawt);

	WEG_SET(DCN_VM_SYSTEM_APEWTUWE_WOW_ADDW_MSB, 0,
			MC_VM_SYSTEM_APEWTUWE_WOW_ADDW_MSB, mc_vm_apt_wow.high_pawt);
	WEG_SET(DCN_VM_SYSTEM_APEWTUWE_WOW_ADDW_WSB, 0,
			MC_VM_SYSTEM_APEWTUWE_WOW_ADDW_WSB, mc_vm_apt_wow.wow_pawt);

	WEG_SET(DCN_VM_SYSTEM_APEWTUWE_HIGH_ADDW_MSB, 0,
			MC_VM_SYSTEM_APEWTUWE_HIGH_ADDW_MSB, mc_vm_apt_high.high_pawt);
	WEG_SET(DCN_VM_SYSTEM_APEWTUWE_HIGH_ADDW_WSB, 0,
			MC_VM_SYSTEM_APEWTUWE_HIGH_ADDW_WSB, mc_vm_apt_high.wow_pawt);
}

static void hubp1_set_vm_context0_settings(stwuct hubp *hubp,
		const stwuct vm_context0_pawam *vm0)
{
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
	/* pte base */
	WEG_SET(DCN_VM_CONTEXT0_PAGE_TABWE_BASE_ADDW_MSB, 0,
			VM_CONTEXT0_PAGE_TABWE_BASE_ADDW_MSB, vm0->pte_base.high_pawt);
	WEG_SET(DCN_VM_CONTEXT0_PAGE_TABWE_BASE_ADDW_WSB, 0,
			VM_CONTEXT0_PAGE_TABWE_BASE_ADDW_WSB, vm0->pte_base.wow_pawt);

	/* pte stawt */
	WEG_SET(DCN_VM_CONTEXT0_PAGE_TABWE_STAWT_ADDW_MSB, 0,
			VM_CONTEXT0_PAGE_TABWE_STAWT_ADDW_MSB, vm0->pte_stawt.high_pawt);
	WEG_SET(DCN_VM_CONTEXT0_PAGE_TABWE_STAWT_ADDW_WSB, 0,
			VM_CONTEXT0_PAGE_TABWE_STAWT_ADDW_WSB, vm0->pte_stawt.wow_pawt);

	/* pte end */
	WEG_SET(DCN_VM_CONTEXT0_PAGE_TABWE_END_ADDW_MSB, 0,
			VM_CONTEXT0_PAGE_TABWE_END_ADDW_MSB, vm0->pte_end.high_pawt);
	WEG_SET(DCN_VM_CONTEXT0_PAGE_TABWE_END_ADDW_WSB, 0,
			VM_CONTEXT0_PAGE_TABWE_END_ADDW_WSB, vm0->pte_end.wow_pawt);

	/* fauwt handwing */
	WEG_SET_2(DCN_VM_CONTEXT0_PWOTECTION_FAUWT_DEFAUWT_ADDW_MSB, 0,
			VM_CONTEXT0_PWOTECTION_FAUWT_DEFAUWT_ADDW_MSB, vm0->fauwt_defauwt.high_pawt,
			VM_CONTEXT0_PWOTECTION_FAUWT_DEFAUWT_SYSTEM, context0_defauwt_system);
	WEG_SET(DCN_VM_CONTEXT0_PWOTECTION_FAUWT_DEFAUWT_ADDW_WSB, 0,
			VM_CONTEXT0_PWOTECTION_FAUWT_DEFAUWT_ADDW_WSB, vm0->fauwt_defauwt.wow_pawt);

	/* contwow: enabwe VM PTE*/
	WEG_SET_2(DCN_VM_MX_W1_TWB_CNTW, 0,
			ENABWE_W1_TWB, 1,
			SYSTEM_ACCESS_MODE, 3);
}

void min_set_viewpowt(
	stwuct hubp *hubp,
	const stwuct wect *viewpowt,
	const stwuct wect *viewpowt_c)
{
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	WEG_SET_2(DCSUWF_PWI_VIEWPOWT_DIMENSION, 0,
		  PWI_VIEWPOWT_WIDTH, viewpowt->width,
		  PWI_VIEWPOWT_HEIGHT, viewpowt->height);

	WEG_SET_2(DCSUWF_PWI_VIEWPOWT_STAWT, 0,
		  PWI_VIEWPOWT_X_STAWT, viewpowt->x,
		  PWI_VIEWPOWT_Y_STAWT, viewpowt->y);

	/*fow steweo*/
	WEG_SET_2(DCSUWF_SEC_VIEWPOWT_DIMENSION, 0,
		  SEC_VIEWPOWT_WIDTH, viewpowt->width,
		  SEC_VIEWPOWT_HEIGHT, viewpowt->height);

	WEG_SET_2(DCSUWF_SEC_VIEWPOWT_STAWT, 0,
		  SEC_VIEWPOWT_X_STAWT, viewpowt->x,
		  SEC_VIEWPOWT_Y_STAWT, viewpowt->y);

	/* DC suppowts NV12 onwy at the moment */
	WEG_SET_2(DCSUWF_PWI_VIEWPOWT_DIMENSION_C, 0,
		  PWI_VIEWPOWT_WIDTH_C, viewpowt_c->width,
		  PWI_VIEWPOWT_HEIGHT_C, viewpowt_c->height);

	WEG_SET_2(DCSUWF_PWI_VIEWPOWT_STAWT_C, 0,
		  PWI_VIEWPOWT_X_STAWT_C, viewpowt_c->x,
		  PWI_VIEWPOWT_Y_STAWT_C, viewpowt_c->y);

	WEG_SET_2(DCSUWF_SEC_VIEWPOWT_DIMENSION_C, 0,
		  SEC_VIEWPOWT_WIDTH_C, viewpowt_c->width,
		  SEC_VIEWPOWT_HEIGHT_C, viewpowt_c->height);

	WEG_SET_2(DCSUWF_SEC_VIEWPOWT_STAWT_C, 0,
		  SEC_VIEWPOWT_X_STAWT_C, viewpowt_c->x,
		  SEC_VIEWPOWT_Y_STAWT_C, viewpowt_c->y);
}

void hubp1_wead_state_common(stwuct hubp *hubp)
{
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
	stwuct dcn_hubp_state *s = &hubp1->state;
	stwuct _vcs_dpi_dispway_dwg_wegs_st *dwg_attw = &s->dwg_attw;
	stwuct _vcs_dpi_dispway_ttu_wegs_st *ttu_attw = &s->ttu_attw;
	stwuct _vcs_dpi_dispway_wq_wegs_st *wq_wegs = &s->wq_wegs;
	uint32_t apewtuwe_wow_msb, apewtuwe_wow_wsb;
	uint32_t apewtuwe_high_msb, apewtuwe_high_wsb;

	/* Wequestew */
	WEG_GET(HUBPWET_CONTWOW,
			DET_BUF_PWANE1_BASE_ADDWESS, &wq_wegs->pwane1_base_addwess);
	WEG_GET_4(DCN_EXPANSION_MODE,
			DWQ_EXPANSION_MODE, &wq_wegs->dwq_expansion_mode,
			PWQ_EXPANSION_MODE, &wq_wegs->pwq_expansion_mode,
			MWQ_EXPANSION_MODE, &wq_wegs->mwq_expansion_mode,
			CWQ_EXPANSION_MODE, &wq_wegs->cwq_expansion_mode);

	WEG_GET(DCN_VM_SYSTEM_APEWTUWE_WOW_ADDW_MSB,
			MC_VM_SYSTEM_APEWTUWE_WOW_ADDW_MSB, &apewtuwe_wow_msb);

	WEG_GET(DCN_VM_SYSTEM_APEWTUWE_WOW_ADDW_WSB,
			MC_VM_SYSTEM_APEWTUWE_WOW_ADDW_WSB, &apewtuwe_wow_wsb);

	WEG_GET(DCN_VM_SYSTEM_APEWTUWE_HIGH_ADDW_MSB,
			MC_VM_SYSTEM_APEWTUWE_HIGH_ADDW_MSB, &apewtuwe_high_msb);

	WEG_GET(DCN_VM_SYSTEM_APEWTUWE_HIGH_ADDW_WSB,
			MC_VM_SYSTEM_APEWTUWE_HIGH_ADDW_WSB, &apewtuwe_high_wsb);

	// On DCN1, apewtuwe is bwoken down into MSB and WSB; onwy keep bits [47:18] to match watew DCN fowmat
	wq_wegs->apewtuwe_wow_addw = (apewtuwe_wow_msb << 26) | (apewtuwe_wow_wsb >> 6);
	wq_wegs->apewtuwe_high_addw = (apewtuwe_high_msb << 26) | (apewtuwe_high_wsb >> 6);

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

void hubp1_wead_state(stwuct hubp *hubp)
{
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
	stwuct dcn_hubp_state *s = &hubp1->state;
	stwuct _vcs_dpi_dispway_wq_wegs_st *wq_wegs = &s->wq_wegs;

	hubp1_wead_state_common(hubp);

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
enum cuwsow_pitch hubp1_get_cuwsow_pitch(unsigned int pitch)
{
	enum cuwsow_pitch hw_pitch;

	switch (pitch) {
	case 64:
		hw_pitch = CUWSOW_PITCH_64_PIXEWS;
		bweak;
	case 128:
		hw_pitch = CUWSOW_PITCH_128_PIXEWS;
		bweak;
	case 256:
		hw_pitch = CUWSOW_PITCH_256_PIXEWS;
		bweak;
	defauwt:
		DC_EWW("Invawid cuwsow pitch of %d. "
				"Onwy 64/128/256 is suppowted on DCN.\n", pitch);
		hw_pitch = CUWSOW_PITCH_64_PIXEWS;
		bweak;
	}
	wetuwn hw_pitch;
}

static enum cuwsow_wines_pew_chunk hubp1_get_wines_pew_chunk(
		unsigned int cuw_width,
		enum dc_cuwsow_cowow_fowmat fowmat)
{
	enum cuwsow_wines_pew_chunk wine_pew_chunk;

	if (fowmat == CUWSOW_MODE_MONO)
		/* impw B. expansion in CUW Buffew weadew */
		wine_pew_chunk = CUWSOW_WINE_PEW_CHUNK_16;
	ewse if (cuw_width <= 32)
		wine_pew_chunk = CUWSOW_WINE_PEW_CHUNK_16;
	ewse if (cuw_width <= 64)
		wine_pew_chunk = CUWSOW_WINE_PEW_CHUNK_8;
	ewse if (cuw_width <= 128)
		wine_pew_chunk = CUWSOW_WINE_PEW_CHUNK_4;
	ewse
		wine_pew_chunk = CUWSOW_WINE_PEW_CHUNK_2;

	wetuwn wine_pew_chunk;
}

void hubp1_cuwsow_set_attwibutes(
		stwuct hubp *hubp,
		const stwuct dc_cuwsow_attwibutes *attw)
{
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
	enum cuwsow_pitch hw_pitch = hubp1_get_cuwsow_pitch(attw->pitch);
	enum cuwsow_wines_pew_chunk wpc = hubp1_get_wines_pew_chunk(
			attw->width, attw->cowow_fowmat);

	hubp->cuws_attw = *attw;

	WEG_UPDATE(CUWSOW_SUWFACE_ADDWESS_HIGH,
			CUWSOW_SUWFACE_ADDWESS_HIGH, attw->addwess.high_pawt);
	WEG_UPDATE(CUWSOW_SUWFACE_ADDWESS,
			CUWSOW_SUWFACE_ADDWESS, attw->addwess.wow_pawt);

	WEG_UPDATE_2(CUWSOW_SIZE,
			CUWSOW_WIDTH, attw->width,
			CUWSOW_HEIGHT, attw->height);

	WEG_UPDATE_3(CUWSOW_CONTWOW,
			CUWSOW_MODE, attw->cowow_fowmat,
			CUWSOW_PITCH, hw_pitch,
			CUWSOW_WINES_PEW_CHUNK, wpc);

	WEG_SET_2(CUWSOW_SETTINS, 0,
			/* no shift of the cuwsow HDW scheduwe */
			CUWSOW0_DST_Y_OFFSET, 0,
			 /* used to shift the cuwsow chunk wequest deadwine */
			CUWSOW0_CHUNK_HDW_ADJUST, 3);
}

void hubp1_cuwsow_set_position(
		stwuct hubp *hubp,
		const stwuct dc_cuwsow_position *pos,
		const stwuct dc_cuwsow_mi_pawam *pawam)
{
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
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
}

/**
 * hubp1_cwk_cntw - Disabwe ow enabwe cwocks fow DCHUBP
 *
 * @hubp: hubp stwuct wefewence.
 * @enabwe: Set twue fow enabwing gate cwock.
 *
 * When enabwing/disabwing DCHUBP cwock, we affect dcfcwk/dppcwk.
 */
void hubp1_cwk_cntw(stwuct hubp *hubp, boow enabwe)
{
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
	uint32_t cwk_enabwe = enabwe ? 1 : 0;

	WEG_UPDATE(HUBP_CWK_CNTW, HUBP_CWOCK_ENABWE, cwk_enabwe);
}

void hubp1_vtg_sew(stwuct hubp *hubp, uint32_t otg_inst)
{
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	WEG_UPDATE(DCHUBP_CNTW, HUBP_VTG_SEW, otg_inst);
}

boow hubp1_in_bwank(stwuct hubp *hubp)
{
	uint32_t in_bwank;
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	WEG_GET(DCHUBP_CNTW, HUBP_IN_BWANK, &in_bwank);
	wetuwn in_bwank ? twue : fawse;
}

void hubp1_soft_weset(stwuct hubp *hubp, boow weset)
{
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	WEG_UPDATE(DCHUBP_CNTW, HUBP_DISABWE, weset ? 1 : 0);
}

/**
 * hubp1_set_fwip_int - Enabwe suwface fwip intewwupt
 *
 * @hubp: hubp stwuct wefewence.
 */
void hubp1_set_fwip_int(stwuct hubp *hubp)
{
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	WEG_UPDATE(DCSUWF_SUWFACE_FWIP_INTEWWUPT,
		SUWFACE_FWIP_INT_MASK, 1);

	wetuwn;
}

/**
 * hubp1_wait_pipe_wead_stawt - wait fow hubp wet path stawting wead.
 *
 * @hubp: hubp stwuct wefewence.
 */
static void hubp1_wait_pipe_wead_stawt(stwuct hubp *hubp)
{
	stwuct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	WEG_WAIT(HUBPWET_WEAD_WINE_STATUS,
		PIPE_WEAD_VBWANK, 0,
		 1, 1000);
}

void hubp1_init(stwuct hubp *hubp)
{
	//do nothing
}
static const stwuct hubp_funcs dcn10_hubp_funcs = {
	.hubp_pwogwam_suwface_fwip_and_addw =
			hubp1_pwogwam_suwface_fwip_and_addw,
	.hubp_pwogwam_suwface_config =
			hubp1_pwogwam_suwface_config,
	.hubp_is_fwip_pending = hubp1_is_fwip_pending,
	.hubp_setup = hubp1_setup,
	.hubp_setup_intewdependent = hubp1_setup_intewdependent,
	.hubp_set_vm_system_apewtuwe_settings = hubp1_set_vm_system_apewtuwe_settings,
	.hubp_set_vm_context0_settings = hubp1_set_vm_context0_settings,
	.set_bwank = hubp1_set_bwank,
	.dcc_contwow = hubp1_dcc_contwow,
	.mem_pwogwam_viewpowt = min_set_viewpowt,
	.set_hubp_bwank_en = hubp1_set_hubp_bwank_en,
	.set_cuwsow_attwibutes	= hubp1_cuwsow_set_attwibutes,
	.set_cuwsow_position	= hubp1_cuwsow_set_position,
	.hubp_disconnect = hubp1_disconnect,
	.hubp_cwk_cntw = hubp1_cwk_cntw,
	.hubp_vtg_sew = hubp1_vtg_sew,
	.hubp_wead_state = hubp1_wead_state,
	.hubp_cweaw_undewfwow = hubp1_cweaw_undewfwow,
	.hubp_disabwe_contwow =  hubp1_disabwe_contwow,
	.hubp_get_undewfwow_status = hubp1_get_undewfwow_status,
	.hubp_init = hubp1_init,

	.dmdata_set_attwibutes = NUWW,
	.dmdata_woad = NUWW,
	.hubp_soft_weset = hubp1_soft_weset,
	.hubp_in_bwank = hubp1_in_bwank,
	.hubp_set_fwip_int = hubp1_set_fwip_int,
	.hubp_wait_pipe_wead_stawt = hubp1_wait_pipe_wead_stawt,
};

/*****************************************/
/* Constwuctow, Destwuctow               */
/*****************************************/

void dcn10_hubp_constwuct(
	stwuct dcn10_hubp *hubp1,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dcn_mi_wegistews *hubp_wegs,
	const stwuct dcn_mi_shift *hubp_shift,
	const stwuct dcn_mi_mask *hubp_mask)
{
	hubp1->base.funcs = &dcn10_hubp_funcs;
	hubp1->base.ctx = ctx;
	hubp1->hubp_wegs = hubp_wegs;
	hubp1->hubp_shift = hubp_shift;
	hubp1->hubp_mask = hubp_mask;
	hubp1->base.inst = inst;
	hubp1->base.opp_id = OPP_ID_INVAWID;
	hubp1->base.mpcc_id = 0xf;
}


