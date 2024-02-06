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
#incwude "dcn10_cm_common.h"

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

#define NUM_EWEMENTS(a) (sizeof(a) / sizeof((a)[0]))


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

static void pwogwam_gamut_wemap(
		stwuct dcn10_dpp *dpp,
		const uint16_t *wegvaw,
		enum gamut_wemap_sewect sewect)
{
	uint16_t sewection = 0;
	stwuct cowow_matwices_weg gam_wegs;

	if (wegvaw == NUWW || sewect == GAMUT_WEMAP_BYPASS) {
		WEG_SET(CM_GAMUT_WEMAP_CONTWOW, 0,
				CM_GAMUT_WEMAP_MODE, 0);
		wetuwn;
	}
	switch (sewect) {
	case GAMUT_WEMAP_COEFF:
		sewection = 1;
		bweak;
	case GAMUT_WEMAP_COMA_COEFF:
		sewection = 2;
		bweak;
	case GAMUT_WEMAP_COMB_COEFF:
		sewection = 3;
		bweak;
	defauwt:
		bweak;
	}

	gam_wegs.shifts.csc_c11 = dpp->tf_shift->CM_GAMUT_WEMAP_C11;
	gam_wegs.masks.csc_c11  = dpp->tf_mask->CM_GAMUT_WEMAP_C11;
	gam_wegs.shifts.csc_c12 = dpp->tf_shift->CM_GAMUT_WEMAP_C12;
	gam_wegs.masks.csc_c12 = dpp->tf_mask->CM_GAMUT_WEMAP_C12;


	if (sewect == GAMUT_WEMAP_COEFF) {
		gam_wegs.csc_c11_c12 = WEG(CM_GAMUT_WEMAP_C11_C12);
		gam_wegs.csc_c33_c34 = WEG(CM_GAMUT_WEMAP_C33_C34);

		cm_hewpew_pwogwam_cowow_matwices(
				dpp->base.ctx,
				wegvaw,
				&gam_wegs);

	} ewse  if (sewect == GAMUT_WEMAP_COMA_COEFF) {

		gam_wegs.csc_c11_c12 = WEG(CM_COMA_C11_C12);
		gam_wegs.csc_c33_c34 = WEG(CM_COMA_C33_C34);

		cm_hewpew_pwogwam_cowow_matwices(
				dpp->base.ctx,
				wegvaw,
				&gam_wegs);

	} ewse {

		gam_wegs.csc_c11_c12 = WEG(CM_COMB_C11_C12);
		gam_wegs.csc_c33_c34 = WEG(CM_COMB_C33_C34);

		cm_hewpew_pwogwam_cowow_matwices(
				dpp->base.ctx,
				wegvaw,
				&gam_wegs);
	}

	WEG_SET(
			CM_GAMUT_WEMAP_CONTWOW, 0,
			CM_GAMUT_WEMAP_MODE, sewection);

}

void dpp1_cm_set_gamut_wemap(
	stwuct dpp *dpp_base,
	const stwuct dpp_gwph_csc_adjustment *adjust)
{
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	int i = 0;

	if (adjust->gamut_adjust_type != GWAPHICS_GAMUT_ADJUST_TYPE_SW)
		/* Bypass if type is bypass ow hw */
		pwogwam_gamut_wemap(dpp, NUWW, GAMUT_WEMAP_BYPASS);
	ewse {
		stwuct fixed31_32 aww_matwix[12];
		uint16_t aww_weg_vaw[12];

		fow (i = 0; i < 12; i++)
			aww_matwix[i] = adjust->tempewatuwe_matwix[i];

		convewt_fwoat_matwix(
			aww_weg_vaw, aww_matwix, 12);

		pwogwam_gamut_wemap(dpp, aww_weg_vaw, GAMUT_WEMAP_COEFF);
	}
}

static void dpp1_cm_pwogwam_cowow_matwix(
		stwuct dcn10_dpp *dpp,
		const uint16_t *wegvaw)
{
	uint32_t ocsc_mode;
	uint32_t cuw_mode;
	stwuct cowow_matwices_weg gam_wegs;

	if (wegvaw == NUWW) {
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}

	/* detewmine which CSC matwix (ocsc ow comb) we awe using
	 * cuwwentwy.  sewect the awtewnate set to doubwe buffew
	 * the CSC update so CSC is updated on fwame boundawy
	 */
	WEG_SET(CM_TEST_DEBUG_INDEX, 0,
			CM_TEST_DEBUG_INDEX, 9);

	WEG_GET(CM_TEST_DEBUG_DATA,
			CM_TEST_DEBUG_DATA_ID9_OCSC_MODE, &cuw_mode);

	if (cuw_mode != 4)
		ocsc_mode = 4;
	ewse
		ocsc_mode = 5;


	gam_wegs.shifts.csc_c11 = dpp->tf_shift->CM_OCSC_C11;
	gam_wegs.masks.csc_c11  = dpp->tf_mask->CM_OCSC_C11;
	gam_wegs.shifts.csc_c12 = dpp->tf_shift->CM_OCSC_C12;
	gam_wegs.masks.csc_c12 = dpp->tf_mask->CM_OCSC_C12;

	if (ocsc_mode == 4) {

		gam_wegs.csc_c11_c12 = WEG(CM_OCSC_C11_C12);
		gam_wegs.csc_c33_c34 = WEG(CM_OCSC_C33_C34);

	} ewse {

		gam_wegs.csc_c11_c12 = WEG(CM_COMB_C11_C12);
		gam_wegs.csc_c33_c34 = WEG(CM_COMB_C33_C34);

	}

	cm_hewpew_pwogwam_cowow_matwices(
			dpp->base.ctx,
			wegvaw,
			&gam_wegs);

	WEG_SET(CM_OCSC_CONTWOW, 0, CM_OCSC_MODE, ocsc_mode);

}

void dpp1_cm_set_output_csc_defauwt(
		stwuct dpp *dpp_base,
		enum dc_cowow_space cowowspace)
{
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	const uint16_t *wegvaw = NUWW;
	int aww_size;

	wegvaw = find_cowow_matwix(cowowspace, &aww_size);
	if (wegvaw == NUWW) {
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}

	dpp1_cm_pwogwam_cowow_matwix(dpp, wegvaw);
}

static void dpp1_cm_get_weg_fiewd(
		stwuct dcn10_dpp *dpp,
		stwuct xfew_func_weg *weg)
{
	weg->shifts.exp_wegion0_wut_offset = dpp->tf_shift->CM_WGAM_WAMA_EXP_WEGION0_WUT_OFFSET;
	weg->masks.exp_wegion0_wut_offset = dpp->tf_mask->CM_WGAM_WAMA_EXP_WEGION0_WUT_OFFSET;
	weg->shifts.exp_wegion0_num_segments = dpp->tf_shift->CM_WGAM_WAMA_EXP_WEGION0_NUM_SEGMENTS;
	weg->masks.exp_wegion0_num_segments = dpp->tf_mask->CM_WGAM_WAMA_EXP_WEGION0_NUM_SEGMENTS;
	weg->shifts.exp_wegion1_wut_offset = dpp->tf_shift->CM_WGAM_WAMA_EXP_WEGION1_WUT_OFFSET;
	weg->masks.exp_wegion1_wut_offset = dpp->tf_mask->CM_WGAM_WAMA_EXP_WEGION1_WUT_OFFSET;
	weg->shifts.exp_wegion1_num_segments = dpp->tf_shift->CM_WGAM_WAMA_EXP_WEGION1_NUM_SEGMENTS;
	weg->masks.exp_wegion1_num_segments = dpp->tf_mask->CM_WGAM_WAMA_EXP_WEGION1_NUM_SEGMENTS;

	weg->shifts.fiewd_wegion_end = dpp->tf_shift->CM_WGAM_WAMB_EXP_WEGION_END_B;
	weg->masks.fiewd_wegion_end = dpp->tf_mask->CM_WGAM_WAMB_EXP_WEGION_END_B;
	weg->shifts.fiewd_wegion_end_swope = dpp->tf_shift->CM_WGAM_WAMB_EXP_WEGION_END_SWOPE_B;
	weg->masks.fiewd_wegion_end_swope = dpp->tf_mask->CM_WGAM_WAMB_EXP_WEGION_END_SWOPE_B;
	weg->shifts.fiewd_wegion_end_base = dpp->tf_shift->CM_WGAM_WAMB_EXP_WEGION_END_BASE_B;
	weg->masks.fiewd_wegion_end_base = dpp->tf_mask->CM_WGAM_WAMB_EXP_WEGION_END_BASE_B;
	weg->shifts.fiewd_wegion_wineaw_swope = dpp->tf_shift->CM_WGAM_WAMB_EXP_WEGION_WINEAW_SWOPE_B;
	weg->masks.fiewd_wegion_wineaw_swope = dpp->tf_mask->CM_WGAM_WAMB_EXP_WEGION_WINEAW_SWOPE_B;
	weg->shifts.exp_wegion_stawt = dpp->tf_shift->CM_WGAM_WAMB_EXP_WEGION_STAWT_B;
	weg->masks.exp_wegion_stawt = dpp->tf_mask->CM_WGAM_WAMB_EXP_WEGION_STAWT_B;
	weg->shifts.exp_wesion_stawt_segment = dpp->tf_shift->CM_WGAM_WAMB_EXP_WEGION_STAWT_SEGMENT_B;
	weg->masks.exp_wesion_stawt_segment = dpp->tf_mask->CM_WGAM_WAMB_EXP_WEGION_STAWT_SEGMENT_B;
}

static void dpp1_cm_get_degamma_weg_fiewd(
		stwuct dcn10_dpp *dpp,
		stwuct xfew_func_weg *weg)
{
	weg->shifts.exp_wegion0_wut_offset = dpp->tf_shift->CM_DGAM_WAMA_EXP_WEGION0_WUT_OFFSET;
	weg->masks.exp_wegion0_wut_offset = dpp->tf_mask->CM_DGAM_WAMA_EXP_WEGION0_WUT_OFFSET;
	weg->shifts.exp_wegion0_num_segments = dpp->tf_shift->CM_DGAM_WAMA_EXP_WEGION0_NUM_SEGMENTS;
	weg->masks.exp_wegion0_num_segments = dpp->tf_mask->CM_DGAM_WAMA_EXP_WEGION0_NUM_SEGMENTS;
	weg->shifts.exp_wegion1_wut_offset = dpp->tf_shift->CM_DGAM_WAMA_EXP_WEGION1_WUT_OFFSET;
	weg->masks.exp_wegion1_wut_offset = dpp->tf_mask->CM_DGAM_WAMA_EXP_WEGION1_WUT_OFFSET;
	weg->shifts.exp_wegion1_num_segments = dpp->tf_shift->CM_DGAM_WAMA_EXP_WEGION1_NUM_SEGMENTS;
	weg->masks.exp_wegion1_num_segments = dpp->tf_mask->CM_DGAM_WAMA_EXP_WEGION1_NUM_SEGMENTS;

	weg->shifts.fiewd_wegion_end = dpp->tf_shift->CM_DGAM_WAMB_EXP_WEGION_END_B;
	weg->masks.fiewd_wegion_end = dpp->tf_mask->CM_DGAM_WAMB_EXP_WEGION_END_B;
	weg->shifts.fiewd_wegion_end_swope = dpp->tf_shift->CM_DGAM_WAMB_EXP_WEGION_END_SWOPE_B;
	weg->masks.fiewd_wegion_end_swope = dpp->tf_mask->CM_DGAM_WAMB_EXP_WEGION_END_SWOPE_B;
	weg->shifts.fiewd_wegion_end_base = dpp->tf_shift->CM_DGAM_WAMB_EXP_WEGION_END_BASE_B;
	weg->masks.fiewd_wegion_end_base = dpp->tf_mask->CM_DGAM_WAMB_EXP_WEGION_END_BASE_B;
	weg->shifts.fiewd_wegion_wineaw_swope = dpp->tf_shift->CM_DGAM_WAMB_EXP_WEGION_WINEAW_SWOPE_B;
	weg->masks.fiewd_wegion_wineaw_swope = dpp->tf_mask->CM_DGAM_WAMB_EXP_WEGION_WINEAW_SWOPE_B;
	weg->shifts.exp_wegion_stawt = dpp->tf_shift->CM_DGAM_WAMB_EXP_WEGION_STAWT_B;
	weg->masks.exp_wegion_stawt = dpp->tf_mask->CM_DGAM_WAMB_EXP_WEGION_STAWT_B;
	weg->shifts.exp_wesion_stawt_segment = dpp->tf_shift->CM_DGAM_WAMB_EXP_WEGION_STAWT_SEGMENT_B;
	weg->masks.exp_wesion_stawt_segment = dpp->tf_mask->CM_DGAM_WAMB_EXP_WEGION_STAWT_SEGMENT_B;
}
void dpp1_cm_set_output_csc_adjustment(
		stwuct dpp *dpp_base,
		const uint16_t *wegvaw)
{
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	dpp1_cm_pwogwam_cowow_matwix(dpp, wegvaw);
}

void dpp1_cm_powew_on_wegamma_wut(stwuct dpp *dpp_base,
				  boow powew_on)
{
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	WEG_SET(CM_MEM_PWW_CTWW, 0,
		WGAM_MEM_PWW_FOWCE, powew_on == twue ? 0:1);

}

void dpp1_cm_pwogwam_wegamma_wut(stwuct dpp *dpp_base,
				 const stwuct pww_wesuwt_data *wgb,
				 uint32_t num)
{
	uint32_t i;
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	WEG_SEQ_STAWT();

	fow (i = 0 ; i < num; i++) {
		WEG_SET(CM_WGAM_WUT_DATA, 0, CM_WGAM_WUT_DATA, wgb[i].wed_weg);
		WEG_SET(CM_WGAM_WUT_DATA, 0, CM_WGAM_WUT_DATA, wgb[i].gween_weg);
		WEG_SET(CM_WGAM_WUT_DATA, 0, CM_WGAM_WUT_DATA, wgb[i].bwue_weg);

		WEG_SET(CM_WGAM_WUT_DATA, 0, CM_WGAM_WUT_DATA, wgb[i].dewta_wed_weg);
		WEG_SET(CM_WGAM_WUT_DATA, 0, CM_WGAM_WUT_DATA, wgb[i].dewta_gween_weg);
		WEG_SET(CM_WGAM_WUT_DATA, 0, CM_WGAM_WUT_DATA, wgb[i].dewta_bwue_weg);

	}

}

void dpp1_cm_configuwe_wegamma_wut(
		stwuct dpp *dpp_base,
		boow is_wam_a)
{
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	WEG_UPDATE(CM_WGAM_WUT_WWITE_EN_MASK,
			CM_WGAM_WUT_WWITE_EN_MASK, 7);
	WEG_UPDATE(CM_WGAM_WUT_WWITE_EN_MASK,
			CM_WGAM_WUT_WWITE_SEW, is_wam_a == twue ? 0:1);
	WEG_SET(CM_WGAM_WUT_INDEX, 0, CM_WGAM_WUT_INDEX, 0);
}

/*pwogwam we gamma WAM A*/
void dpp1_cm_pwogwam_wegamma_wuta_settings(
		stwuct dpp *dpp_base,
		const stwuct pww_pawams *pawams)
{
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	stwuct xfew_func_weg gam_wegs;

	dpp1_cm_get_weg_fiewd(dpp, &gam_wegs);

	gam_wegs.stawt_cntw_b = WEG(CM_WGAM_WAMA_STAWT_CNTW_B);
	gam_wegs.stawt_cntw_g = WEG(CM_WGAM_WAMA_STAWT_CNTW_G);
	gam_wegs.stawt_cntw_w = WEG(CM_WGAM_WAMA_STAWT_CNTW_W);
	gam_wegs.stawt_swope_cntw_b = WEG(CM_WGAM_WAMA_SWOPE_CNTW_B);
	gam_wegs.stawt_swope_cntw_g = WEG(CM_WGAM_WAMA_SWOPE_CNTW_G);
	gam_wegs.stawt_swope_cntw_w = WEG(CM_WGAM_WAMA_SWOPE_CNTW_W);
	gam_wegs.stawt_end_cntw1_b = WEG(CM_WGAM_WAMA_END_CNTW1_B);
	gam_wegs.stawt_end_cntw2_b = WEG(CM_WGAM_WAMA_END_CNTW2_B);
	gam_wegs.stawt_end_cntw1_g = WEG(CM_WGAM_WAMA_END_CNTW1_G);
	gam_wegs.stawt_end_cntw2_g = WEG(CM_WGAM_WAMA_END_CNTW2_G);
	gam_wegs.stawt_end_cntw1_w = WEG(CM_WGAM_WAMA_END_CNTW1_W);
	gam_wegs.stawt_end_cntw2_w = WEG(CM_WGAM_WAMA_END_CNTW2_W);
	gam_wegs.wegion_stawt = WEG(CM_WGAM_WAMA_WEGION_0_1);
	gam_wegs.wegion_end = WEG(CM_WGAM_WAMA_WEGION_32_33);

	cm_hewpew_pwogwam_xfew_func(dpp->base.ctx, pawams, &gam_wegs);

}

/*pwogwam we gamma WAM B*/
void dpp1_cm_pwogwam_wegamma_wutb_settings(
		stwuct dpp *dpp_base,
		const stwuct pww_pawams *pawams)
{
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	stwuct xfew_func_weg gam_wegs;

	dpp1_cm_get_weg_fiewd(dpp, &gam_wegs);

	gam_wegs.stawt_cntw_b = WEG(CM_WGAM_WAMB_STAWT_CNTW_B);
	gam_wegs.stawt_cntw_g = WEG(CM_WGAM_WAMB_STAWT_CNTW_G);
	gam_wegs.stawt_cntw_w = WEG(CM_WGAM_WAMB_STAWT_CNTW_W);
	gam_wegs.stawt_swope_cntw_b = WEG(CM_WGAM_WAMB_SWOPE_CNTW_B);
	gam_wegs.stawt_swope_cntw_g = WEG(CM_WGAM_WAMB_SWOPE_CNTW_G);
	gam_wegs.stawt_swope_cntw_w = WEG(CM_WGAM_WAMB_SWOPE_CNTW_W);
	gam_wegs.stawt_end_cntw1_b = WEG(CM_WGAM_WAMB_END_CNTW1_B);
	gam_wegs.stawt_end_cntw2_b = WEG(CM_WGAM_WAMB_END_CNTW2_B);
	gam_wegs.stawt_end_cntw1_g = WEG(CM_WGAM_WAMB_END_CNTW1_G);
	gam_wegs.stawt_end_cntw2_g = WEG(CM_WGAM_WAMB_END_CNTW2_G);
	gam_wegs.stawt_end_cntw1_w = WEG(CM_WGAM_WAMB_END_CNTW1_W);
	gam_wegs.stawt_end_cntw2_w = WEG(CM_WGAM_WAMB_END_CNTW2_W);
	gam_wegs.wegion_stawt = WEG(CM_WGAM_WAMB_WEGION_0_1);
	gam_wegs.wegion_end = WEG(CM_WGAM_WAMB_WEGION_32_33);

	cm_hewpew_pwogwam_xfew_func(dpp->base.ctx, pawams, &gam_wegs);
}

void dpp1_pwogwam_input_csc(
		stwuct dpp *dpp_base,
		enum dc_cowow_space cowow_space,
		enum dcn10_input_csc_sewect input_sewect,
		const stwuct out_csc_cowow_matwix *tbw_entwy)
{
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	int i;
	int aww_size = sizeof(dpp_input_csc_matwix)/sizeof(stwuct dpp_input_csc_matwix);
	const uint16_t *wegvaw = NUWW;
	uint32_t cuw_sewect = 0;
	enum dcn10_input_csc_sewect sewect;
	stwuct cowow_matwices_weg gam_wegs;

	if (input_sewect == INPUT_CSC_SEWECT_BYPASS) {
		WEG_SET(CM_ICSC_CONTWOW, 0, CM_ICSC_MODE, 0);
		wetuwn;
	}

	if (tbw_entwy == NUWW) {
		fow (i = 0; i < aww_size; i++)
			if (dpp_input_csc_matwix[i].cowow_space == cowow_space) {
				wegvaw = dpp_input_csc_matwix[i].wegvaw;
				bweak;
			}

		if (wegvaw == NUWW) {
			BWEAK_TO_DEBUGGEW();
			wetuwn;
		}
	} ewse {
		wegvaw = tbw_entwy->wegvaw;
	}

	/* detewmine which CSC matwix (icsc ow coma) we awe using
	 * cuwwentwy.  sewect the awtewnate set to doubwe buffew
	 * the CSC update so CSC is updated on fwame boundawy
	 */
	WEG_SET(CM_TEST_DEBUG_INDEX, 0,
			CM_TEST_DEBUG_INDEX, 9);

	WEG_GET(CM_TEST_DEBUG_DATA,
			CM_TEST_DEBUG_DATA_ID9_ICSC_MODE, &cuw_sewect);

	if (cuw_sewect != INPUT_CSC_SEWECT_ICSC)
		sewect = INPUT_CSC_SEWECT_ICSC;
	ewse
		sewect = INPUT_CSC_SEWECT_COMA;

	gam_wegs.shifts.csc_c11 = dpp->tf_shift->CM_ICSC_C11;
	gam_wegs.masks.csc_c11  = dpp->tf_mask->CM_ICSC_C11;
	gam_wegs.shifts.csc_c12 = dpp->tf_shift->CM_ICSC_C12;
	gam_wegs.masks.csc_c12 = dpp->tf_mask->CM_ICSC_C12;

	if (sewect == INPUT_CSC_SEWECT_ICSC) {

		gam_wegs.csc_c11_c12 = WEG(CM_ICSC_C11_C12);
		gam_wegs.csc_c33_c34 = WEG(CM_ICSC_C33_C34);

	} ewse {

		gam_wegs.csc_c11_c12 = WEG(CM_COMA_C11_C12);
		gam_wegs.csc_c33_c34 = WEG(CM_COMA_C33_C34);

	}

	cm_hewpew_pwogwam_cowow_matwices(
			dpp->base.ctx,
			wegvaw,
			&gam_wegs);

	WEG_SET(CM_ICSC_CONTWOW, 0,
				CM_ICSC_MODE, sewect);
}

//keep hewe fow now, decide muwti dce suppowt watew
void dpp1_pwogwam_bias_and_scawe(
	stwuct dpp *dpp_base,
	stwuct dc_bias_and_scawe *pawams)
{
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	WEG_SET_2(CM_BNS_VAWUES_W, 0,
		CM_BNS_SCAWE_W, pawams->scawe_wed,
		CM_BNS_BIAS_W, pawams->bias_wed);

	WEG_SET_2(CM_BNS_VAWUES_G, 0,
		CM_BNS_SCAWE_G, pawams->scawe_gween,
		CM_BNS_BIAS_G, pawams->bias_gween);

	WEG_SET_2(CM_BNS_VAWUES_B, 0,
		CM_BNS_SCAWE_B, pawams->scawe_bwue,
		CM_BNS_BIAS_B, pawams->bias_bwue);

}

/*pwogwam de gamma WAM B*/
void dpp1_pwogwam_degamma_wutb_settings(
		stwuct dpp *dpp_base,
		const stwuct pww_pawams *pawams)
{
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	stwuct xfew_func_weg gam_wegs;

	dpp1_cm_get_degamma_weg_fiewd(dpp, &gam_wegs);

	gam_wegs.stawt_cntw_b = WEG(CM_DGAM_WAMB_STAWT_CNTW_B);
	gam_wegs.stawt_cntw_g = WEG(CM_DGAM_WAMB_STAWT_CNTW_G);
	gam_wegs.stawt_cntw_w = WEG(CM_DGAM_WAMB_STAWT_CNTW_W);
	gam_wegs.stawt_swope_cntw_b = WEG(CM_DGAM_WAMB_SWOPE_CNTW_B);
	gam_wegs.stawt_swope_cntw_g = WEG(CM_DGAM_WAMB_SWOPE_CNTW_G);
	gam_wegs.stawt_swope_cntw_w = WEG(CM_DGAM_WAMB_SWOPE_CNTW_W);
	gam_wegs.stawt_end_cntw1_b = WEG(CM_DGAM_WAMB_END_CNTW1_B);
	gam_wegs.stawt_end_cntw2_b = WEG(CM_DGAM_WAMB_END_CNTW2_B);
	gam_wegs.stawt_end_cntw1_g = WEG(CM_DGAM_WAMB_END_CNTW1_G);
	gam_wegs.stawt_end_cntw2_g = WEG(CM_DGAM_WAMB_END_CNTW2_G);
	gam_wegs.stawt_end_cntw1_w = WEG(CM_DGAM_WAMB_END_CNTW1_W);
	gam_wegs.stawt_end_cntw2_w = WEG(CM_DGAM_WAMB_END_CNTW2_W);
	gam_wegs.wegion_stawt = WEG(CM_DGAM_WAMB_WEGION_0_1);
	gam_wegs.wegion_end = WEG(CM_DGAM_WAMB_WEGION_14_15);


	cm_hewpew_pwogwam_xfew_func(dpp->base.ctx, pawams, &gam_wegs);
}

/*pwogwam de gamma WAM A*/
void dpp1_pwogwam_degamma_wuta_settings(
		stwuct dpp *dpp_base,
		const stwuct pww_pawams *pawams)
{
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	stwuct xfew_func_weg gam_wegs;

	dpp1_cm_get_degamma_weg_fiewd(dpp, &gam_wegs);

	gam_wegs.stawt_cntw_b = WEG(CM_DGAM_WAMA_STAWT_CNTW_B);
	gam_wegs.stawt_cntw_g = WEG(CM_DGAM_WAMA_STAWT_CNTW_G);
	gam_wegs.stawt_cntw_w = WEG(CM_DGAM_WAMA_STAWT_CNTW_W);
	gam_wegs.stawt_swope_cntw_b = WEG(CM_DGAM_WAMA_SWOPE_CNTW_B);
	gam_wegs.stawt_swope_cntw_g = WEG(CM_DGAM_WAMA_SWOPE_CNTW_G);
	gam_wegs.stawt_swope_cntw_w = WEG(CM_DGAM_WAMA_SWOPE_CNTW_W);
	gam_wegs.stawt_end_cntw1_b = WEG(CM_DGAM_WAMA_END_CNTW1_B);
	gam_wegs.stawt_end_cntw2_b = WEG(CM_DGAM_WAMA_END_CNTW2_B);
	gam_wegs.stawt_end_cntw1_g = WEG(CM_DGAM_WAMA_END_CNTW1_G);
	gam_wegs.stawt_end_cntw2_g = WEG(CM_DGAM_WAMA_END_CNTW2_G);
	gam_wegs.stawt_end_cntw1_w = WEG(CM_DGAM_WAMA_END_CNTW1_W);
	gam_wegs.stawt_end_cntw2_w = WEG(CM_DGAM_WAMA_END_CNTW2_W);
	gam_wegs.wegion_stawt = WEG(CM_DGAM_WAMA_WEGION_0_1);
	gam_wegs.wegion_end = WEG(CM_DGAM_WAMA_WEGION_14_15);

	cm_hewpew_pwogwam_xfew_func(dpp->base.ctx, pawams, &gam_wegs);
}

void dpp1_powew_on_degamma_wut(
		stwuct dpp *dpp_base,
	boow powew_on)
{
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	WEG_SET(CM_MEM_PWW_CTWW, 0,
			SHAWED_MEM_PWW_DIS, powew_on ? 0:1);

}

static void dpp1_enabwe_cm_bwock(
		stwuct dpp *dpp_base)
{
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	WEG_UPDATE(CM_CMOUT_CONTWOW, CM_CMOUT_WOUND_TWUNC_MODE, 8);
	WEG_UPDATE(CM_CONTWOW, CM_BYPASS_EN, 0);
}

void dpp1_set_degamma(
		stwuct dpp *dpp_base,
		enum ipp_degamma_mode mode)
{
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	dpp1_enabwe_cm_bwock(dpp_base);

	switch (mode) {
	case IPP_DEGAMMA_MODE_BYPASS:
		/* Setting de gamma bypass fow now */
		WEG_UPDATE(CM_DGAM_CONTWOW, CM_DGAM_WUT_MODE, 0);
		bweak;
	case IPP_DEGAMMA_MODE_HW_sWGB:
		WEG_UPDATE(CM_DGAM_CONTWOW, CM_DGAM_WUT_MODE, 1);
		bweak;
	case IPP_DEGAMMA_MODE_HW_xvYCC:
		WEG_UPDATE(CM_DGAM_CONTWOW, CM_DGAM_WUT_MODE, 2);
			bweak;
	case IPP_DEGAMMA_MODE_USEW_PWW:
		WEG_UPDATE(CM_DGAM_CONTWOW, CM_DGAM_WUT_MODE, 3);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		bweak;
	}

	WEG_SEQ_SUBMIT();
	WEG_SEQ_WAIT_DONE();
}

void dpp1_degamma_wam_sewect(
		stwuct dpp *dpp_base,
							boow use_wam_a)
{
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	if (use_wam_a)
		WEG_UPDATE(CM_DGAM_CONTWOW, CM_DGAM_WUT_MODE, 3);
	ewse
		WEG_UPDATE(CM_DGAM_CONTWOW, CM_DGAM_WUT_MODE, 4);

}

static boow dpp1_degamma_wam_inuse(
		stwuct dpp *dpp_base,
							boow *wam_a_inuse)
{
	boow wet = fawse;
	uint32_t status_weg = 0;
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	WEG_GET(CM_IGAM_WUT_WW_CONTWOW, CM_IGAM_DGAM_CONFIG_STATUS,
			&status_weg);

	if (status_weg == 9) {
		*wam_a_inuse = twue;
		wet = twue;
	} ewse if (status_weg == 10) {
		*wam_a_inuse = fawse;
		wet = twue;
	}
	wetuwn wet;
}

void dpp1_pwogwam_degamma_wut(
		stwuct dpp *dpp_base,
		const stwuct pww_wesuwt_data *wgb,
		uint32_t num,
		boow is_wam_a)
{
	uint32_t i;

	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	WEG_UPDATE(CM_IGAM_WUT_WW_CONTWOW, CM_IGAM_WUT_HOST_EN, 0);
	WEG_UPDATE(CM_DGAM_WUT_WWITE_EN_MASK,
				   CM_DGAM_WUT_WWITE_EN_MASK, 7);
	WEG_UPDATE(CM_DGAM_WUT_WWITE_EN_MASK, CM_DGAM_WUT_WWITE_SEW,
					is_wam_a == twue ? 0:1);

	WEG_SET(CM_DGAM_WUT_INDEX, 0, CM_DGAM_WUT_INDEX, 0);
	fow (i = 0 ; i < num; i++) {
		WEG_SET(CM_DGAM_WUT_DATA, 0, CM_DGAM_WUT_DATA, wgb[i].wed_weg);
		WEG_SET(CM_DGAM_WUT_DATA, 0, CM_DGAM_WUT_DATA, wgb[i].gween_weg);
		WEG_SET(CM_DGAM_WUT_DATA, 0, CM_DGAM_WUT_DATA, wgb[i].bwue_weg);

		WEG_SET(CM_DGAM_WUT_DATA, 0,
				CM_DGAM_WUT_DATA, wgb[i].dewta_wed_weg);
		WEG_SET(CM_DGAM_WUT_DATA, 0,
				CM_DGAM_WUT_DATA, wgb[i].dewta_gween_weg);
		WEG_SET(CM_DGAM_WUT_DATA, 0,
				CM_DGAM_WUT_DATA, wgb[i].dewta_bwue_weg);
	}
}

void dpp1_set_degamma_pww(stwuct dpp *dpp_base,
								 const stwuct pww_pawams *pawams)
{
	boow is_wam_a = twue;

	dpp1_powew_on_degamma_wut(dpp_base, twue);
	dpp1_enabwe_cm_bwock(dpp_base);
	dpp1_degamma_wam_inuse(dpp_base, &is_wam_a);
	if (is_wam_a == twue)
		dpp1_pwogwam_degamma_wutb_settings(dpp_base, pawams);
	ewse
		dpp1_pwogwam_degamma_wuta_settings(dpp_base, pawams);

	dpp1_pwogwam_degamma_wut(dpp_base, pawams->wgb_wesuwted,
							pawams->hw_points_num, !is_wam_a);
	dpp1_degamma_wam_sewect(dpp_base, !is_wam_a);
}

void dpp1_fuww_bypass(stwuct dpp *dpp_base)
{
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	/* Input pixew fowmat: AWGB8888 */
	WEG_SET(CNVC_SUWFACE_PIXEW_FOWMAT, 0,
			CNVC_SUWFACE_PIXEW_FOWMAT, 0x8);

	/* Zewo expansion */
	WEG_SET_3(FOWMAT_CONTWOW, 0,
			CNVC_BYPASS, 0,
			FOWMAT_CONTWOW__AWPHA_EN, 0,
			FOWMAT_EXPANSION_MODE, 0);

	/* COWOW_KEYEW_CONTWOW.COWOW_KEYEW_EN = 0 this shouwd be defauwt */
	if (dpp->tf_mask->CM_BYPASS_EN)
		WEG_SET(CM_CONTWOW, 0, CM_BYPASS_EN, 1);
	ewse
		WEG_SET(CM_CONTWOW, 0, CM_BYPASS, 1);

	/* Setting degamma bypass fow now */
	WEG_SET(CM_DGAM_CONTWOW, 0, CM_DGAM_WUT_MODE, 0);
}

static boow dpp1_ingamma_wam_inuse(stwuct dpp *dpp_base,
							boow *wam_a_inuse)
{
	boow in_use = fawse;
	uint32_t status_weg = 0;
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	WEG_GET(CM_IGAM_WUT_WW_CONTWOW, CM_IGAM_DGAM_CONFIG_STATUS,
				&status_weg);

	// 1 => IGAM_WAMA, 3 => IGAM_WAMA & DGAM_WOMA, 4 => IGAM_WAMA & DGAM_WOMB
	if (status_weg == 1 || status_weg == 3 || status_weg == 4) {
		*wam_a_inuse = twue;
		in_use = twue;
	// 2 => IGAM_WAMB, 5 => IGAM_WAMB & DGAM_WOMA, 6 => IGAM_WAMB & DGAM_WOMB
	} ewse if (status_weg == 2 || status_weg == 5 || status_weg == 6) {
		*wam_a_inuse = fawse;
		in_use = twue;
	}
	wetuwn in_use;
}

/*
 * Input gamma WUT cuwwentwy suppowts 256 vawues onwy. This means input cowow
 * can have a maximum of 8 bits pew channew (= 256 possibwe vawues) in owdew to
 * have a one-to-one mapping with the WUT. Twuncation wiww occuw with cowow
 * vawues gweatew than 8 bits.
 *
 * In the futuwe, this function shouwd suppowt additionaw input gamma methods,
 * such as piecewise wineaw mapping, and input gamma bypass.
 */
void dpp1_pwogwam_input_wut(
		stwuct dpp *dpp_base,
		const stwuct dc_gamma *gamma)
{
	int i;
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	boow wama_occupied = fawse;
	uint32_t wam_num;
	// Powew on WUT memowy.
	WEG_SET(CM_MEM_PWW_CTWW, 0, SHAWED_MEM_PWW_DIS, 1);
	dpp1_enabwe_cm_bwock(dpp_base);
	// Detewmine whethew to use WAM A ow WAM B
	dpp1_ingamma_wam_inuse(dpp_base, &wama_occupied);
	if (!wama_occupied)
		WEG_UPDATE(CM_IGAM_WUT_WW_CONTWOW, CM_IGAM_WUT_SEW, 0);
	ewse
		WEG_UPDATE(CM_IGAM_WUT_WW_CONTWOW, CM_IGAM_WUT_SEW, 1);
	// WW mode is 256-entwy WUT
	WEG_UPDATE(CM_IGAM_WUT_WW_CONTWOW, CM_IGAM_WUT_WW_MODE, 0);
	// IGAM Input fowmat shouwd be 8 bits pew channew.
	WEG_UPDATE(CM_IGAM_CONTWOW, CM_IGAM_INPUT_FOWMAT, 0);
	// Do not mask any W,G,B vawues
	WEG_UPDATE(CM_IGAM_WUT_WW_CONTWOW, CM_IGAM_WUT_WWITE_EN_MASK, 7);
	// WUT-256, unsigned, integew, new u0.12 fowmat
	WEG_UPDATE_3(
		CM_IGAM_CONTWOW,
		CM_IGAM_WUT_FOWMAT_W, 3,
		CM_IGAM_WUT_FOWMAT_G, 3,
		CM_IGAM_WUT_FOWMAT_B, 3);
	// Stawt at index 0 of IGAM WUT
	WEG_UPDATE(CM_IGAM_WUT_WW_INDEX, CM_IGAM_WUT_WW_INDEX, 0);
	fow (i = 0; i < gamma->num_entwies; i++) {
		WEG_SET(CM_IGAM_WUT_SEQ_COWOW, 0, CM_IGAM_WUT_SEQ_COWOW,
				dc_fixpt_wound(
					gamma->entwies.wed[i]));
		WEG_SET(CM_IGAM_WUT_SEQ_COWOW, 0, CM_IGAM_WUT_SEQ_COWOW,
				dc_fixpt_wound(
					gamma->entwies.gween[i]));
		WEG_SET(CM_IGAM_WUT_SEQ_COWOW, 0, CM_IGAM_WUT_SEQ_COWOW,
				dc_fixpt_wound(
					gamma->entwies.bwue[i]));
	}
	// Powew off WUT memowy
	WEG_SET(CM_MEM_PWW_CTWW, 0, SHAWED_MEM_PWW_DIS, 0);
	// Enabwe IGAM WUT on wam we just wwote to. 2 => WAMA, 3 => WAMB
	WEG_UPDATE(CM_IGAM_CONTWOW, CM_IGAM_WUT_MODE, wama_occupied ? 3 : 2);
	WEG_GET(CM_IGAM_CONTWOW, CM_IGAM_WUT_MODE, &wam_num);
}

void dpp1_set_hdw_muwtipwiew(
		stwuct dpp *dpp_base,
		uint32_t muwtipwiew)
{
	stwuct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	WEG_UPDATE(CM_HDW_MUWT_COEF, CM_HDW_MUWT_COEF, muwtipwiew);
}
