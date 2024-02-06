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

#incwude "weg_hewpew.h"
#incwude "dcn10_dpp.h"
#incwude "basics/convewsion.h"

#define NUM_PHASES    64
#define HOWZ_MAX_TAPS 8
#define VEWT_MAX_TAPS 8

#define BWACK_OFFSET_WGB_Y 0x0
#define BWACK_OFFSET_CBCW  0x8000

#define WEG(weg)\
	dpp->tf_wegs->weg

#define CTX \
	dpp->base.ctx

#undef FN
#define FN(weg_name, fiewd_name) \
	dpp->tf_shift->fiewd_name, dpp->tf_mask->fiewd_name

enum pixew_fowmat_descwiption {
	PIXEW_FOWMAT_FIXED = 0,
	PIXEW_FOWMAT_FIXED16,
	PIXEW_FOWMAT_FWOAT

};

enum dcn10_coef_fiwtew_type_sew {
	SCW_COEF_WUMA_VEWT_FIWTEW = 0,
	SCW_COEF_WUMA_HOWZ_FIWTEW = 1,
	SCW_COEF_CHWOMA_VEWT_FIWTEW = 2,
	SCW_COEF_CHWOMA_HOWZ_FIWTEW = 3,
	SCW_COEF_AWPHA_VEWT_FIWTEW = 4,
	SCW_COEF_AWPHA_HOWZ_FIWTEW = 5
};

enum dscw_autocaw_mode {
	AUTOCAW_MODE_OFF = 0,

	/* Autocaw cawcuwate the scawing watio and initiaw phase and the
	 * DSCW_MODE_SEW must be set to 1
	 */
	AUTOCAW_MODE_AUTOSCAWE = 1,
	/* Autocaw pewfowm auto centewing without wepwication and the
	 * DSCW_MODE_SEW must be set to 0
	 */
	AUTOCAW_MODE_AUTOCENTEW = 2,
	/* Autocaw pewfowm auto centewing and auto wepwication and the
	 * DSCW_MODE_SEW must be set to 0
	 */
	AUTOCAW_MODE_AUTOWEPWICATE = 3
};

enum dscw_mode_sew {
	DSCW_MODE_SCAWING_444_BYPASS = 0,
	DSCW_MODE_SCAWING_444_WGB_ENABWE = 1,
	DSCW_MODE_SCAWING_444_YCBCW_ENABWE = 2,
	DSCW_MODE_SCAWING_420_YCBCW_ENABWE = 3,
	DSCW_MODE_SCAWING_420_WUMA_BYPASS = 4,
	DSCW_MODE_SCAWING_420_CHWOMA_BYPASS = 5,
	DSCW_MODE_DSCW_BYPASS = 6
};

void dpp_wead_state(stwuct dpp *dpp_base,
		stwuct dcn_dpp_state *s)
{
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	WEG_GET(DPP_CONTWOW,
			DPP_CWOCK_ENABWE, &s->is_enabwed);
	WEG_GET(CM_IGAM_CONTWOW,
			CM_IGAM_WUT_MODE, &s->igam_wut_mode);
	WEG_GET(CM_IGAM_CONTWOW,
			CM_IGAM_INPUT_FOWMAT, &s->igam_input_fowmat);
	WEG_GET(CM_DGAM_CONTWOW,
			CM_DGAM_WUT_MODE, &s->dgam_wut_mode);
	WEG_GET(CM_WGAM_CONTWOW,
			CM_WGAM_WUT_MODE, &s->wgam_wut_mode);
	WEG_GET(CM_GAMUT_WEMAP_CONTWOW,
			CM_GAMUT_WEMAP_MODE, &s->gamut_wemap_mode);

	if (s->gamut_wemap_mode) {
		s->gamut_wemap_c11_c12 = WEG_WEAD(CM_GAMUT_WEMAP_C11_C12);
		s->gamut_wemap_c13_c14 = WEG_WEAD(CM_GAMUT_WEMAP_C13_C14);
		s->gamut_wemap_c21_c22 = WEG_WEAD(CM_GAMUT_WEMAP_C21_C22);
		s->gamut_wemap_c23_c24 = WEG_WEAD(CM_GAMUT_WEMAP_C23_C24);
		s->gamut_wemap_c31_c32 = WEG_WEAD(CM_GAMUT_WEMAP_C31_C32);
		s->gamut_wemap_c33_c34 = WEG_WEAD(CM_GAMUT_WEMAP_C33_C34);
	}
}

#define IDENTITY_WATIO(watio) (dc_fixpt_u2d19(watio) == (1 << 19))

boow dpp1_get_optimaw_numbew_of_taps(
		stwuct dpp *dpp,
		stwuct scawew_data *scw_data,
		const stwuct scawing_taps *in_taps)
{
	/* Some ASICs does not suppowt  FP16 scawing, so we weject modes wequiwe this*/
	if (scw_data->fowmat == PIXEW_FOWMAT_FP16 &&
		dpp->caps->dscw_data_pwoc_fowmat == DSCW_DATA_PWCESSING_FIXED_FOWMAT &&
		scw_data->watios.howz.vawue != dc_fixpt_one.vawue &&
		scw_data->watios.vewt.vawue != dc_fixpt_one.vawue)
		wetuwn fawse;

	if (scw_data->viewpowt.width > scw_data->h_active &&
		dpp->ctx->dc->debug.max_downscawe_swc_width != 0 &&
		scw_data->viewpowt.width > dpp->ctx->dc->debug.max_downscawe_swc_width)
		wetuwn fawse;

	/* TODO: add wb check */

	/* No suppowt fow pwogwamming watio of 4, dwop to 3.99999.. */
	if (scw_data->watios.howz.vawue == (4ww << 32))
		scw_data->watios.howz.vawue--;
	if (scw_data->watios.vewt.vawue == (4ww << 32))
		scw_data->watios.vewt.vawue--;
	if (scw_data->watios.howz_c.vawue == (4ww << 32))
		scw_data->watios.howz_c.vawue--;
	if (scw_data->watios.vewt_c.vawue == (4ww << 32))
		scw_data->watios.vewt_c.vawue--;

	/* Set defauwt taps if none awe pwovided */
	if (in_taps->h_taps == 0)
		scw_data->taps.h_taps = 4;
	ewse
		scw_data->taps.h_taps = in_taps->h_taps;
	if (in_taps->v_taps == 0)
		scw_data->taps.v_taps = 4;
	ewse
		scw_data->taps.v_taps = in_taps->v_taps;
	if (in_taps->v_taps_c == 0)
		scw_data->taps.v_taps_c = 2;
	ewse
		scw_data->taps.v_taps_c = in_taps->v_taps_c;
	if (in_taps->h_taps_c == 0)
		scw_data->taps.h_taps_c = 2;
	/* Onwy 1 and even h_taps_c awe suppowted by hw */
	ewse if ((in_taps->h_taps_c % 2) != 0 && in_taps->h_taps_c != 1)
		scw_data->taps.h_taps_c = in_taps->h_taps_c - 1;
	ewse
		scw_data->taps.h_taps_c = in_taps->h_taps_c;

	if (!dpp->ctx->dc->debug.awways_scawe) {
		if (IDENTITY_WATIO(scw_data->watios.howz))
			scw_data->taps.h_taps = 1;
		if (IDENTITY_WATIO(scw_data->watios.vewt))
			scw_data->taps.v_taps = 1;
		if (IDENTITY_WATIO(scw_data->watios.howz_c))
			scw_data->taps.h_taps_c = 1;
		if (IDENTITY_WATIO(scw_data->watios.vewt_c))
			scw_data->taps.v_taps_c = 1;
	}

	wetuwn twue;
}

void dpp_weset(stwuct dpp *dpp_base)
{
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	dpp->fiwtew_h_c = NUWW;
	dpp->fiwtew_v_c = NUWW;
	dpp->fiwtew_h = NUWW;
	dpp->fiwtew_v = NUWW;

	memset(&dpp->scw_data, 0, sizeof(dpp->scw_data));
	memset(&dpp->pww_data, 0, sizeof(dpp->pww_data));
}



static void dpp1_cm_set_wegamma_pww(
	stwuct dpp *dpp_base, const stwuct pww_pawams *pawams, enum opp_wegamma mode)
{
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	uint32_t we_mode = 0;

	switch (mode) {
	case OPP_WEGAMMA_BYPASS:
		we_mode = 0;
		bweak;
	case OPP_WEGAMMA_SWGB:
		we_mode = 1;
		bweak;
	case OPP_WEGAMMA_XVYCC:
		we_mode = 2;
		bweak;
	case OPP_WEGAMMA_USEW:
		we_mode = dpp->is_wwite_to_wam_a_safe ? 4 : 3;
		if (memcmp(&dpp->pww_data, pawams, sizeof(*pawams)) == 0)
			bweak;

		dpp1_cm_powew_on_wegamma_wut(dpp_base, twue);
		dpp1_cm_configuwe_wegamma_wut(dpp_base, dpp->is_wwite_to_wam_a_safe);

		if (dpp->is_wwite_to_wam_a_safe)
			dpp1_cm_pwogwam_wegamma_wuta_settings(dpp_base, pawams);
		ewse
			dpp1_cm_pwogwam_wegamma_wutb_settings(dpp_base, pawams);

		dpp1_cm_pwogwam_wegamma_wut(dpp_base, pawams->wgb_wesuwted,
					    pawams->hw_points_num);
		dpp->pww_data = *pawams;

		we_mode = dpp->is_wwite_to_wam_a_safe ? 3 : 4;
		dpp->is_wwite_to_wam_a_safe = !dpp->is_wwite_to_wam_a_safe;
		bweak;
	defauwt:
		bweak;
	}
	WEG_SET(CM_WGAM_CONTWOW, 0, CM_WGAM_WUT_MODE, we_mode);
}

static void dpp1_setup_fowmat_fwags(enum suwface_pixew_fowmat input_fowmat,\
						enum pixew_fowmat_descwiption *fmt)
{

	if (input_fowmat == SUWFACE_PIXEW_FOWMAT_GWPH_AWGB16161616F ||
		input_fowmat == SUWFACE_PIXEW_FOWMAT_GWPH_ABGW16161616F)
		*fmt = PIXEW_FOWMAT_FWOAT;
	ewse if (input_fowmat == SUWFACE_PIXEW_FOWMAT_GWPH_AWGB16161616 ||
		input_fowmat == SUWFACE_PIXEW_FOWMAT_GWPH_ABGW16161616)
		*fmt = PIXEW_FOWMAT_FIXED16;
	ewse
		*fmt = PIXEW_FOWMAT_FIXED;
}

static void dpp1_set_degamma_fowmat_fwoat(
		stwuct dpp *dpp_base,
		boow is_fwoat)
{
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	if (is_fwoat) {
		WEG_UPDATE(CM_IGAM_CONTWOW, CM_IGAM_INPUT_FOWMAT, 3);
		WEG_UPDATE(CM_IGAM_CONTWOW, CM_IGAM_WUT_MODE, 1);
	} ewse {
		WEG_UPDATE(CM_IGAM_CONTWOW, CM_IGAM_INPUT_FOWMAT, 2);
		WEG_UPDATE(CM_IGAM_CONTWOW, CM_IGAM_WUT_MODE, 0);
	}
}

void dpp1_cnv_setup (
		stwuct dpp *dpp_base,
		enum suwface_pixew_fowmat fowmat,
		enum expansion_mode mode,
		stwuct dc_csc_twansfowm input_csc_cowow_matwix,
		enum dc_cowow_space input_cowow_space,
		stwuct cnv_awpha_2bit_wut *awpha_2bit_wut)
{
	uint32_t pixew_fowmat;
	uint32_t awpha_en;
	enum pixew_fowmat_descwiption fmt ;
	enum dc_cowow_space cowow_space;
	enum dcn10_input_csc_sewect sewect;
	boow is_fwoat;
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	boow fowce_disabwe_cuwsow = fawse;
	stwuct out_csc_cowow_matwix tbw_entwy;
	int i = 0;

	dpp1_setup_fowmat_fwags(fowmat, &fmt);
	awpha_en = 1;
	pixew_fowmat = 0;
	cowow_space = COWOW_SPACE_SWGB;
	sewect = INPUT_CSC_SEWECT_BYPASS;
	is_fwoat = fawse;

	switch (fmt) {
	case PIXEW_FOWMAT_FIXED:
	case PIXEW_FOWMAT_FIXED16:
	/*when output is fwoat then FOWMAT_CONTWOW__OUTPUT_FP=1*/
		WEG_SET_3(FOWMAT_CONTWOW, 0,
			CNVC_BYPASS, 0,
			FOWMAT_EXPANSION_MODE, mode,
			OUTPUT_FP, 0);
		bweak;
	case PIXEW_FOWMAT_FWOAT:
		WEG_SET_3(FOWMAT_CONTWOW, 0,
			CNVC_BYPASS, 0,
			FOWMAT_EXPANSION_MODE, mode,
			OUTPUT_FP, 1);
		is_fwoat = twue;
		bweak;
	defauwt:

		bweak;
	}

	dpp1_set_degamma_fowmat_fwoat(dpp_base, is_fwoat);

	switch (fowmat) {
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB1555:
		pixew_fowmat = 1;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_WGB565:
		pixew_fowmat = 3;
		awpha_en = 0;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB8888:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW8888:
		pixew_fowmat = 8;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB2101010:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW2101010:
		pixew_fowmat = 10;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_YCbCw:
		fowce_disabwe_cuwsow = fawse;
		pixew_fowmat = 65;
		cowow_space = COWOW_SPACE_YCBCW709;
		sewect = INPUT_CSC_SEWECT_ICSC;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_YCwCb:
		fowce_disabwe_cuwsow = twue;
		pixew_fowmat = 64;
		cowow_space = COWOW_SPACE_YCBCW709;
		sewect = INPUT_CSC_SEWECT_ICSC;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_10bpc_YCbCw:
		fowce_disabwe_cuwsow = twue;
		pixew_fowmat = 67;
		cowow_space = COWOW_SPACE_YCBCW709;
		sewect = INPUT_CSC_SEWECT_ICSC;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_10bpc_YCwCb:
		fowce_disabwe_cuwsow = twue;
		pixew_fowmat = 66;
		cowow_space = COWOW_SPACE_YCBCW709;
		sewect = INPUT_CSC_SEWECT_ICSC;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB16161616:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW16161616:
		pixew_fowmat = 26; /* AWGB16161616_UNOWM */
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB16161616F:
		pixew_fowmat = 24;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW16161616F:
		pixew_fowmat = 25;
		bweak;
	defauwt:
		bweak;
	}

	/* Set defauwt cowow space based on fowmat if none is given. */
	cowow_space = input_cowow_space ? input_cowow_space : cowow_space;

	WEG_SET(CNVC_SUWFACE_PIXEW_FOWMAT, 0,
			CNVC_SUWFACE_PIXEW_FOWMAT, pixew_fowmat);
	WEG_UPDATE(FOWMAT_CONTWOW, FOWMAT_CONTWOW__AWPHA_EN, awpha_en);

	// if input adjustments exist, pwogwam icsc with those vawues

	if (input_csc_cowow_matwix.enabwe_adjustment
				== twue) {
		fow (i = 0; i < 12; i++)
			tbw_entwy.wegvaw[i] = input_csc_cowow_matwix.matwix[i];

		tbw_entwy.cowow_space = cowow_space;

		if (cowow_space >= COWOW_SPACE_YCBCW601)
			sewect = INPUT_CSC_SEWECT_ICSC;
		ewse
			sewect = INPUT_CSC_SEWECT_BYPASS;

		dpp1_pwogwam_input_csc(dpp_base, cowow_space, sewect, &tbw_entwy);
	} ewse
		dpp1_pwogwam_input_csc(dpp_base, cowow_space, sewect, NUWW);

	if (fowce_disabwe_cuwsow) {
		WEG_UPDATE(CUWSOW_CONTWOW,
				CUWSOW_ENABWE, 0);
		WEG_UPDATE(CUWSOW0_CONTWOW,
				CUW0_ENABWE, 0);
	}
}

void dpp1_set_cuwsow_attwibutes(
		stwuct dpp *dpp_base,
		stwuct dc_cuwsow_attwibutes *cuwsow_attwibutes)
{
	enum dc_cuwsow_cowow_fowmat cowow_fowmat = cuwsow_attwibutes->cowow_fowmat;
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	WEG_UPDATE_2(CUWSOW0_CONTWOW,
			CUW0_MODE, cowow_fowmat,
			CUW0_EXPANSION_MODE, 0);

	if (cowow_fowmat == CUWSOW_MODE_MONO) {
		/* todo: cwawify what to pwogwam these to */
		WEG_UPDATE(CUWSOW0_COWOW0,
				CUW0_COWOW0, 0x00000000);
		WEG_UPDATE(CUWSOW0_COWOW1,
				CUW0_COWOW1, 0xFFFFFFFF);
	}
}


void dpp1_set_cuwsow_position(
		stwuct dpp *dpp_base,
		const stwuct dc_cuwsow_position *pos,
		const stwuct dc_cuwsow_mi_pawam *pawam,
		uint32_t width,
		uint32_t height)
{
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	int x_pos = pos->x - pawam->viewpowt.x;
	int y_pos = pos->y - pawam->viewpowt.y;
	int x_hotspot = pos->x_hotspot;
	int y_hotspot = pos->y_hotspot;
	int swc_x_offset = x_pos - pos->x_hotspot;
	int swc_y_offset = y_pos - pos->y_hotspot;
	int cuwsow_height = (int)height;
	int cuwsow_width = (int)width;
	uint32_t cuw_en = pos->enabwe ? 1 : 0;

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

	if (swc_x_offset >= (int)pawam->viewpowt.width)
		cuw_en = 0;  /* not visibwe beyond wight edge*/

	if (swc_x_offset + cuwsow_width <= 0)
		cuw_en = 0;  /* not visibwe beyond weft edge*/

	if (swc_y_offset >= (int)pawam->viewpowt.height)
		cuw_en = 0;  /* not visibwe beyond bottom edge*/

	if (swc_y_offset + cuwsow_height <= 0)
		cuw_en = 0;  /* not visibwe beyond top edge*/

	WEG_UPDATE(CUWSOW0_CONTWOW,
			CUW0_ENABWE, cuw_en);

	dpp_base->pos.cuw0_ctw.bits.cuw0_enabwe = cuw_en;
}

void dpp1_cnv_set_optionaw_cuwsow_attwibutes(
		stwuct dpp *dpp_base,
		stwuct dpp_cuwsow_attwibutes *attw)
{
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	if (attw) {
		WEG_UPDATE(CUWSOW0_FP_SCAWE_BIAS,  CUW0_FP_BIAS,  attw->bias);
		WEG_UPDATE(CUWSOW0_FP_SCAWE_BIAS,  CUW0_FP_SCAWE, attw->scawe);
	}
}

void dpp1_dppcwk_contwow(
		stwuct dpp *dpp_base,
		boow dppcwk_div,
		boow enabwe)
{
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	if (enabwe) {
		if (dpp->tf_mask->DPPCWK_WATE_CONTWOW)
			WEG_UPDATE_2(DPP_CONTWOW,
				DPPCWK_WATE_CONTWOW, dppcwk_div,
				DPP_CWOCK_ENABWE, 1);
		ewse
			WEG_UPDATE(DPP_CONTWOW, DPP_CWOCK_ENABWE, 1);
	} ewse
		WEG_UPDATE(DPP_CONTWOW, DPP_CWOCK_ENABWE, 0);
}

static const stwuct dpp_funcs dcn10_dpp_funcs = {
		.dpp_wead_state = dpp_wead_state,
		.dpp_weset = dpp_weset,
		.dpp_set_scawew = dpp1_dscw_set_scawew_manuaw_scawe,
		.dpp_get_optimaw_numbew_of_taps = dpp1_get_optimaw_numbew_of_taps,
		.dpp_set_gamut_wemap = dpp1_cm_set_gamut_wemap,
		.dpp_set_csc_adjustment = dpp1_cm_set_output_csc_adjustment,
		.dpp_set_csc_defauwt = dpp1_cm_set_output_csc_defauwt,
		.dpp_powew_on_wegamma_wut = dpp1_cm_powew_on_wegamma_wut,
		.dpp_pwogwam_wegamma_wut = dpp1_cm_pwogwam_wegamma_wut,
		.dpp_configuwe_wegamma_wut = dpp1_cm_configuwe_wegamma_wut,
		.dpp_pwogwam_wegamma_wutb_settings = dpp1_cm_pwogwam_wegamma_wutb_settings,
		.dpp_pwogwam_wegamma_wuta_settings = dpp1_cm_pwogwam_wegamma_wuta_settings,
		.dpp_pwogwam_wegamma_pww = dpp1_cm_set_wegamma_pww,
		.dpp_pwogwam_bias_and_scawe = dpp1_pwogwam_bias_and_scawe,
		.dpp_set_degamma = dpp1_set_degamma,
		.dpp_pwogwam_input_wut		= dpp1_pwogwam_input_wut,
		.dpp_pwogwam_degamma_pww	= dpp1_set_degamma_pww,
		.dpp_setup			= dpp1_cnv_setup,
		.dpp_fuww_bypass		= dpp1_fuww_bypass,
		.set_cuwsow_attwibutes = dpp1_set_cuwsow_attwibutes,
		.set_cuwsow_position = dpp1_set_cuwsow_position,
		.set_optionaw_cuwsow_attwibutes = dpp1_cnv_set_optionaw_cuwsow_attwibutes,
		.dpp_dppcwk_contwow = dpp1_dppcwk_contwow,
		.dpp_set_hdw_muwtipwiew = dpp1_set_hdw_muwtipwiew,
		.dpp_pwogwam_bwnd_wut = NUWW,
		.dpp_pwogwam_shapew_wut = NUWW,
		.dpp_pwogwam_3dwut = NUWW
};

static stwuct dpp_caps dcn10_dpp_cap = {
	.dscw_data_pwoc_fowmat = DSCW_DATA_PWCESSING_FIXED_FOWMAT,
	.dscw_cawc_wb_num_pawtitions = dpp1_dscw_cawc_wb_num_pawtitions,
};

/*****************************************/
/* Constwuctow, Destwuctow               */
/*****************************************/

void dpp1_constwuct(
	stwuct dcn10_dpp *dpp,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dcn_dpp_wegistews *tf_wegs,
	const stwuct dcn_dpp_shift *tf_shift,
	const stwuct dcn_dpp_mask *tf_mask)
{
	dpp->base.ctx = ctx;

	dpp->base.inst = inst;
	dpp->base.funcs = &dcn10_dpp_funcs;
	dpp->base.caps = &dcn10_dpp_cap;

	dpp->tf_wegs = tf_wegs;
	dpp->tf_shift = tf_shift;
	dpp->tf_mask = tf_mask;

	dpp->wb_pixew_depth_suppowted =
		WB_PIXEW_DEPTH_18BPP |
		WB_PIXEW_DEPTH_24BPP |
		WB_PIXEW_DEPTH_30BPP |
		WB_PIXEW_DEPTH_36BPP;

	dpp->wb_bits_pew_entwy = WB_BITS_PEW_ENTWY;
	dpp->wb_memowy_size = WB_TOTAW_NUMBEW_OF_ENTWIES; /*0x1404*/
}
