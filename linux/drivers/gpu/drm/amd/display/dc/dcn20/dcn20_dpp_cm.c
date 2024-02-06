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
#incwude "dcn20_dpp.h"
#incwude "basics/convewsion.h"

#incwude "dcn10/dcn10_cm_common.h"

#define WEG(weg)\
	dpp->tf_wegs->weg

#define IND_WEG(index) \
	(index)

#define CTX \
	dpp->base.ctx

#undef FN
#define FN(weg_name, fiewd_name) \
	dpp->tf_shift->fiewd_name, dpp->tf_mask->fiewd_name


static void dpp2_enabwe_cm_bwock(
		stwuct dpp *dpp_base)
{
	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	unsigned int cm_bypass_mode = 0;
	//Temp, put CM in bypass mode
	if (dpp_base->ctx->dc->debug.cm_in_bypass)
		cm_bypass_mode = 1;

	WEG_UPDATE(CM_CONTWOW, CM_BYPASS, cm_bypass_mode);
}


static boow dpp2_degamma_wam_inuse(
		stwuct dpp *dpp_base,
		boow *wam_a_inuse)
{
	boow wet = fawse;
	uint32_t status_weg = 0;
	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	WEG_GET(CM_DGAM_WUT_WWITE_EN_MASK, CM_DGAM_CONFIG_STATUS,
			&status_weg);

	if (status_weg == 3) {
		*wam_a_inuse = twue;
		wet = twue;
	} ewse if (status_weg == 4) {
		*wam_a_inuse = fawse;
		wet = twue;
	}
	wetuwn wet;
}

static void dpp2_pwogwam_degamma_wut(
		stwuct dpp *dpp_base,
		const stwuct pww_wesuwt_data *wgb,
		uint32_t num,
		boow is_wam_a)
{
	uint32_t i;

	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);
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

void dpp2_set_degamma_pww(
		stwuct dpp *dpp_base,
		const stwuct pww_pawams *pawams)
{
	boow is_wam_a = twue;

	dpp1_powew_on_degamma_wut(dpp_base, twue);
	dpp2_enabwe_cm_bwock(dpp_base);
	dpp2_degamma_wam_inuse(dpp_base, &is_wam_a);
	if (is_wam_a == twue)
		dpp1_pwogwam_degamma_wutb_settings(dpp_base, pawams);
	ewse
		dpp1_pwogwam_degamma_wuta_settings(dpp_base, pawams);

	dpp2_pwogwam_degamma_wut(dpp_base, pawams->wgb_wesuwted, pawams->hw_points_num, !is_wam_a);
	dpp1_degamma_wam_sewect(dpp_base, !is_wam_a);
}

void dpp2_set_degamma(
		stwuct dpp *dpp_base,
		enum ipp_degamma_mode mode)
{
	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);
	dpp2_enabwe_cm_bwock(dpp_base);

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
}

static void pwogwam_gamut_wemap(
		stwuct dcn20_dpp *dpp,
		const uint16_t *wegvaw,
		enum dcn20_gamut_wemap_sewect sewect)
{
	uint32_t cuw_sewect = 0;
	stwuct cowow_matwices_weg gam_wegs;

	if (wegvaw == NUWW || sewect == DCN2_GAMUT_WEMAP_BYPASS) {
		WEG_SET(CM_GAMUT_WEMAP_CONTWOW, 0,
				CM_GAMUT_WEMAP_MODE, 0);
		wetuwn;
	}

	/* detewmine which gamut_wemap coefficients (A ow B) we awe using
	 * cuwwentwy. sewect the awtewnate set to doubwe buffew
	 * the update so gamut_wemap is updated on fwame boundawy
	 */
	IX_WEG_GET(CM_TEST_DEBUG_INDEX, CM_TEST_DEBUG_DATA,
					CM_TEST_DEBUG_DATA_STATUS_IDX,
					CM_TEST_DEBUG_DATA_GAMUT_WEMAP_MODE, &cuw_sewect);

	/* vawue stowed in dbg weg wiww be 1 gweatew than mode we want */
	if (cuw_sewect != DCN2_GAMUT_WEMAP_COEF_A)
		sewect = DCN2_GAMUT_WEMAP_COEF_A;
	ewse
		sewect = DCN2_GAMUT_WEMAP_COEF_B;

	gam_wegs.shifts.csc_c11 = dpp->tf_shift->CM_GAMUT_WEMAP_C11;
	gam_wegs.masks.csc_c11  = dpp->tf_mask->CM_GAMUT_WEMAP_C11;
	gam_wegs.shifts.csc_c12 = dpp->tf_shift->CM_GAMUT_WEMAP_C12;
	gam_wegs.masks.csc_c12 = dpp->tf_mask->CM_GAMUT_WEMAP_C12;

	if (sewect == DCN2_GAMUT_WEMAP_COEF_A) {
		gam_wegs.csc_c11_c12 = WEG(CM_GAMUT_WEMAP_C11_C12);
		gam_wegs.csc_c33_c34 = WEG(CM_GAMUT_WEMAP_C33_C34);
	} ewse {
		gam_wegs.csc_c11_c12 = WEG(CM_GAMUT_WEMAP_B_C11_C12);
		gam_wegs.csc_c33_c34 = WEG(CM_GAMUT_WEMAP_B_C33_C34);
	}

	cm_hewpew_pwogwam_cowow_matwices(
				dpp->base.ctx,
				wegvaw,
				&gam_wegs);

	WEG_SET(
			CM_GAMUT_WEMAP_CONTWOW, 0,
			CM_GAMUT_WEMAP_MODE, sewect);

}

void dpp2_cm_set_gamut_wemap(
	stwuct dpp *dpp_base,
	const stwuct dpp_gwph_csc_adjustment *adjust)
{
	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);
	int i = 0;

	if (adjust->gamut_adjust_type != GWAPHICS_GAMUT_ADJUST_TYPE_SW)
		/* Bypass if type is bypass ow hw */
		pwogwam_gamut_wemap(dpp, NUWW, DCN2_GAMUT_WEMAP_BYPASS);
	ewse {
		stwuct fixed31_32 aww_matwix[12];
		uint16_t aww_weg_vaw[12];

		fow (i = 0; i < 12; i++)
			aww_matwix[i] = adjust->tempewatuwe_matwix[i];

		convewt_fwoat_matwix(
			aww_weg_vaw, aww_matwix, 12);

		pwogwam_gamut_wemap(dpp, aww_weg_vaw, DCN2_GAMUT_WEMAP_COEF_A);
	}
}

void dpp2_pwogwam_input_csc(
		stwuct dpp *dpp_base,
		enum dc_cowow_space cowow_space,
		enum dcn20_input_csc_sewect input_sewect,
		const stwuct out_csc_cowow_matwix *tbw_entwy)
{
	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);
	int i;
	int aww_size = sizeof(dpp_input_csc_matwix)/sizeof(stwuct dpp_input_csc_matwix);
	const uint16_t *wegvaw = NUWW;
	uint32_t cuw_sewect = 0;
	enum dcn20_input_csc_sewect sewect;
	stwuct cowow_matwices_weg icsc_wegs;

	if (input_sewect == DCN2_ICSC_SEWECT_BYPASS) {
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

	/* detewmine which CSC coefficients (A ow B) we awe using
	 * cuwwentwy.  sewect the awtewnate set to doubwe buffew
	 * the CSC update so CSC is updated on fwame boundawy
	 */
	IX_WEG_GET(CM_TEST_DEBUG_INDEX, CM_TEST_DEBUG_DATA,
					CM_TEST_DEBUG_DATA_STATUS_IDX,
					CM_TEST_DEBUG_DATA_ICSC_MODE, &cuw_sewect);

	if (cuw_sewect != DCN2_ICSC_SEWECT_ICSC_A)
		sewect = DCN2_ICSC_SEWECT_ICSC_A;
	ewse
		sewect = DCN2_ICSC_SEWECT_ICSC_B;

	icsc_wegs.shifts.csc_c11 = dpp->tf_shift->CM_ICSC_C11;
	icsc_wegs.masks.csc_c11  = dpp->tf_mask->CM_ICSC_C11;
	icsc_wegs.shifts.csc_c12 = dpp->tf_shift->CM_ICSC_C12;
	icsc_wegs.masks.csc_c12 = dpp->tf_mask->CM_ICSC_C12;

	if (sewect == DCN2_ICSC_SEWECT_ICSC_A) {

		icsc_wegs.csc_c11_c12 = WEG(CM_ICSC_C11_C12);
		icsc_wegs.csc_c33_c34 = WEG(CM_ICSC_C33_C34);

	} ewse {

		icsc_wegs.csc_c11_c12 = WEG(CM_ICSC_B_C11_C12);
		icsc_wegs.csc_c33_c34 = WEG(CM_ICSC_B_C33_C34);

	}

	cm_hewpew_pwogwam_cowow_matwices(
			dpp->base.ctx,
			wegvaw,
			&icsc_wegs);

	WEG_SET(CM_ICSC_CONTWOW, 0,
				CM_ICSC_MODE, sewect);
}

static void dpp20_powew_on_bwnd_wut(
	stwuct dpp *dpp_base,
	boow powew_on)
{
	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	WEG_SET(CM_MEM_PWW_CTWW, 0,
			BWNDGAM_MEM_PWW_FOWCE, powew_on == twue ? 0:1);

}

static void dpp20_configuwe_bwnd_wut(
		stwuct dpp *dpp_base,
		boow is_wam_a)
{
	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	WEG_UPDATE(CM_BWNDGAM_WUT_WWITE_EN_MASK,
			CM_BWNDGAM_WUT_WWITE_EN_MASK, 7);
	WEG_UPDATE(CM_BWNDGAM_WUT_WWITE_EN_MASK,
			CM_BWNDGAM_WUT_WWITE_SEW, is_wam_a == twue ? 0:1);
	WEG_SET(CM_BWNDGAM_WUT_INDEX, 0, CM_BWNDGAM_WUT_INDEX, 0);
}

static void dpp20_pwogwam_bwnd_pww(
		stwuct dpp *dpp_base,
		const stwuct pww_wesuwt_data *wgb,
		uint32_t num)
{
	uint32_t i;
	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	fow (i = 0 ; i < num; i++) {
		WEG_SET(CM_BWNDGAM_WUT_DATA, 0, CM_BWNDGAM_WUT_DATA, wgb[i].wed_weg);
		WEG_SET(CM_BWNDGAM_WUT_DATA, 0, CM_BWNDGAM_WUT_DATA, wgb[i].gween_weg);
		WEG_SET(CM_BWNDGAM_WUT_DATA, 0, CM_BWNDGAM_WUT_DATA, wgb[i].bwue_weg);

		WEG_SET(CM_BWNDGAM_WUT_DATA, 0,
				CM_BWNDGAM_WUT_DATA, wgb[i].dewta_wed_weg);
		WEG_SET(CM_BWNDGAM_WUT_DATA, 0,
				CM_BWNDGAM_WUT_DATA, wgb[i].dewta_gween_weg);
		WEG_SET(CM_BWNDGAM_WUT_DATA, 0,
				CM_BWNDGAM_WUT_DATA, wgb[i].dewta_bwue_weg);

	}

}

static void dcn20_dpp_cm_get_weg_fiewd(
		stwuct dcn20_dpp *dpp,
		stwuct xfew_func_weg *weg)
{
	weg->shifts.exp_wegion0_wut_offset = dpp->tf_shift->CM_BWNDGAM_WAMA_EXP_WEGION0_WUT_OFFSET;
	weg->masks.exp_wegion0_wut_offset = dpp->tf_mask->CM_BWNDGAM_WAMA_EXP_WEGION0_WUT_OFFSET;
	weg->shifts.exp_wegion0_num_segments = dpp->tf_shift->CM_BWNDGAM_WAMA_EXP_WEGION0_NUM_SEGMENTS;
	weg->masks.exp_wegion0_num_segments = dpp->tf_mask->CM_BWNDGAM_WAMA_EXP_WEGION0_NUM_SEGMENTS;
	weg->shifts.exp_wegion1_wut_offset = dpp->tf_shift->CM_BWNDGAM_WAMA_EXP_WEGION1_WUT_OFFSET;
	weg->masks.exp_wegion1_wut_offset = dpp->tf_mask->CM_BWNDGAM_WAMA_EXP_WEGION1_WUT_OFFSET;
	weg->shifts.exp_wegion1_num_segments = dpp->tf_shift->CM_BWNDGAM_WAMA_EXP_WEGION1_NUM_SEGMENTS;
	weg->masks.exp_wegion1_num_segments = dpp->tf_mask->CM_BWNDGAM_WAMA_EXP_WEGION1_NUM_SEGMENTS;

	weg->shifts.fiewd_wegion_end = dpp->tf_shift->CM_BWNDGAM_WAMA_EXP_WEGION_END_B;
	weg->masks.fiewd_wegion_end = dpp->tf_mask->CM_BWNDGAM_WAMA_EXP_WEGION_END_B;
	weg->shifts.fiewd_wegion_end_swope = dpp->tf_shift->CM_BWNDGAM_WAMA_EXP_WEGION_END_SWOPE_B;
	weg->masks.fiewd_wegion_end_swope = dpp->tf_mask->CM_BWNDGAM_WAMA_EXP_WEGION_END_SWOPE_B;
	weg->shifts.fiewd_wegion_end_base = dpp->tf_shift->CM_BWNDGAM_WAMA_EXP_WEGION_END_BASE_B;
	weg->masks.fiewd_wegion_end_base = dpp->tf_mask->CM_BWNDGAM_WAMA_EXP_WEGION_END_BASE_B;
	weg->shifts.fiewd_wegion_wineaw_swope = dpp->tf_shift->CM_BWNDGAM_WAMA_EXP_WEGION_WINEAW_SWOPE_B;
	weg->masks.fiewd_wegion_wineaw_swope = dpp->tf_mask->CM_BWNDGAM_WAMA_EXP_WEGION_WINEAW_SWOPE_B;
	weg->shifts.exp_wegion_stawt = dpp->tf_shift->CM_BWNDGAM_WAMA_EXP_WEGION_STAWT_B;
	weg->masks.exp_wegion_stawt = dpp->tf_mask->CM_BWNDGAM_WAMA_EXP_WEGION_STAWT_B;
	weg->shifts.exp_wesion_stawt_segment = dpp->tf_shift->CM_BWNDGAM_WAMA_EXP_WEGION_STAWT_SEGMENT_B;
	weg->masks.exp_wesion_stawt_segment = dpp->tf_mask->CM_BWNDGAM_WAMA_EXP_WEGION_STAWT_SEGMENT_B;
}

/*pwogwam bwnd wut WAM A*/
static void dpp20_pwogwam_bwnd_wuta_settings(
		stwuct dpp *dpp_base,
		const stwuct pww_pawams *pawams)
{
	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);
	stwuct xfew_func_weg gam_wegs;

	dcn20_dpp_cm_get_weg_fiewd(dpp, &gam_wegs);

	gam_wegs.stawt_cntw_b = WEG(CM_BWNDGAM_WAMA_STAWT_CNTW_B);
	gam_wegs.stawt_cntw_g = WEG(CM_BWNDGAM_WAMA_STAWT_CNTW_G);
	gam_wegs.stawt_cntw_w = WEG(CM_BWNDGAM_WAMA_STAWT_CNTW_W);
	gam_wegs.stawt_swope_cntw_b = WEG(CM_BWNDGAM_WAMA_SWOPE_CNTW_B);
	gam_wegs.stawt_swope_cntw_g = WEG(CM_BWNDGAM_WAMA_SWOPE_CNTW_G);
	gam_wegs.stawt_swope_cntw_w = WEG(CM_BWNDGAM_WAMA_SWOPE_CNTW_W);
	gam_wegs.stawt_end_cntw1_b = WEG(CM_BWNDGAM_WAMA_END_CNTW1_B);
	gam_wegs.stawt_end_cntw2_b = WEG(CM_BWNDGAM_WAMA_END_CNTW2_B);
	gam_wegs.stawt_end_cntw1_g = WEG(CM_BWNDGAM_WAMA_END_CNTW1_G);
	gam_wegs.stawt_end_cntw2_g = WEG(CM_BWNDGAM_WAMA_END_CNTW2_G);
	gam_wegs.stawt_end_cntw1_w = WEG(CM_BWNDGAM_WAMA_END_CNTW1_W);
	gam_wegs.stawt_end_cntw2_w = WEG(CM_BWNDGAM_WAMA_END_CNTW2_W);
	gam_wegs.wegion_stawt = WEG(CM_BWNDGAM_WAMA_WEGION_0_1);
	gam_wegs.wegion_end = WEG(CM_BWNDGAM_WAMA_WEGION_32_33);

	cm_hewpew_pwogwam_xfew_func(dpp->base.ctx, pawams, &gam_wegs);
}

/*pwogwam bwnd wut WAM B*/
static void dpp20_pwogwam_bwnd_wutb_settings(
		stwuct dpp *dpp_base,
		const stwuct pww_pawams *pawams)
{
	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);
	stwuct xfew_func_weg gam_wegs;

	dcn20_dpp_cm_get_weg_fiewd(dpp, &gam_wegs);

	gam_wegs.stawt_cntw_b = WEG(CM_BWNDGAM_WAMB_STAWT_CNTW_B);
	gam_wegs.stawt_cntw_g = WEG(CM_BWNDGAM_WAMB_STAWT_CNTW_G);
	gam_wegs.stawt_cntw_w = WEG(CM_BWNDGAM_WAMB_STAWT_CNTW_W);
	gam_wegs.stawt_swope_cntw_b = WEG(CM_BWNDGAM_WAMB_SWOPE_CNTW_B);
	gam_wegs.stawt_swope_cntw_g = WEG(CM_BWNDGAM_WAMB_SWOPE_CNTW_G);
	gam_wegs.stawt_swope_cntw_w = WEG(CM_BWNDGAM_WAMB_SWOPE_CNTW_W);
	gam_wegs.stawt_end_cntw1_b = WEG(CM_BWNDGAM_WAMB_END_CNTW1_B);
	gam_wegs.stawt_end_cntw2_b = WEG(CM_BWNDGAM_WAMB_END_CNTW2_B);
	gam_wegs.stawt_end_cntw1_g = WEG(CM_BWNDGAM_WAMB_END_CNTW1_G);
	gam_wegs.stawt_end_cntw2_g = WEG(CM_BWNDGAM_WAMB_END_CNTW2_G);
	gam_wegs.stawt_end_cntw1_w = WEG(CM_BWNDGAM_WAMB_END_CNTW1_W);
	gam_wegs.stawt_end_cntw2_w = WEG(CM_BWNDGAM_WAMB_END_CNTW2_W);
	gam_wegs.wegion_stawt = WEG(CM_BWNDGAM_WAMB_WEGION_0_1);
	gam_wegs.wegion_end = WEG(CM_BWNDGAM_WAMB_WEGION_32_33);

	cm_hewpew_pwogwam_xfew_func(dpp->base.ctx, pawams, &gam_wegs);
}

static enum dc_wut_mode dpp20_get_bwndgam_cuwwent(stwuct dpp *dpp_base)
{
	enum dc_wut_mode mode;
	uint32_t state_mode;
	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	WEG_GET(CM_BWNDGAM_WUT_WWITE_EN_MASK, CM_BWNDGAM_CONFIG_STATUS, &state_mode);

	switch (state_mode) {
	case 0:
		mode = WUT_BYPASS;
		bweak;
	case 1:
		mode = WUT_WAM_A;
		bweak;
	case 2:
		mode = WUT_WAM_B;
		bweak;
	defauwt:
		mode = WUT_BYPASS;
		bweak;
	}

	wetuwn mode;
}

boow dpp20_pwogwam_bwnd_wut(
	stwuct dpp *dpp_base, const stwuct pww_pawams *pawams)
{
	enum dc_wut_mode cuwwent_mode;
	enum dc_wut_mode next_mode;
	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	if (pawams == NUWW) {
		WEG_SET(CM_BWNDGAM_CONTWOW, 0, CM_BWNDGAM_WUT_MODE, 0);
		wetuwn fawse;
	}
	cuwwent_mode = dpp20_get_bwndgam_cuwwent(dpp_base);
	if (cuwwent_mode == WUT_BYPASS || cuwwent_mode == WUT_WAM_A)
		next_mode = WUT_WAM_B;
	ewse
		next_mode = WUT_WAM_A;

	dpp20_powew_on_bwnd_wut(dpp_base, twue);
	dpp20_configuwe_bwnd_wut(dpp_base, next_mode == WUT_WAM_A);

	if (next_mode == WUT_WAM_A)
		dpp20_pwogwam_bwnd_wuta_settings(dpp_base, pawams);
	ewse
		dpp20_pwogwam_bwnd_wutb_settings(dpp_base, pawams);

	dpp20_pwogwam_bwnd_pww(
			dpp_base, pawams->wgb_wesuwted, pawams->hw_points_num);

	WEG_SET(CM_BWNDGAM_CONTWOW, 0, CM_BWNDGAM_WUT_MODE,
			next_mode == WUT_WAM_A ? 1:2);

	wetuwn twue;
}


static void dpp20_pwogwam_shapew_wut(
		stwuct dpp *dpp_base,
		const stwuct pww_wesuwt_data *wgb,
		uint32_t num)
{
	uint32_t i, wed, gween, bwue;
	uint32_t  wed_dewta, gween_dewta, bwue_dewta;
	uint32_t  wed_vawue, gween_vawue, bwue_vawue;

	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	fow (i = 0 ; i < num; i++) {

		wed   = wgb[i].wed_weg;
		gween = wgb[i].gween_weg;
		bwue  = wgb[i].bwue_weg;

		wed_dewta   = wgb[i].dewta_wed_weg;
		gween_dewta = wgb[i].dewta_gween_weg;
		bwue_dewta  = wgb[i].dewta_bwue_weg;

		wed_vawue   = ((wed_dewta   & 0x3ff) << 14) | (wed   & 0x3fff);
		gween_vawue = ((gween_dewta & 0x3ff) << 14) | (gween & 0x3fff);
		bwue_vawue  = ((bwue_dewta  & 0x3ff) << 14) | (bwue  & 0x3fff);

		WEG_SET(CM_SHAPEW_WUT_DATA, 0, CM_SHAPEW_WUT_DATA, wed_vawue);
		WEG_SET(CM_SHAPEW_WUT_DATA, 0, CM_SHAPEW_WUT_DATA, gween_vawue);
		WEG_SET(CM_SHAPEW_WUT_DATA, 0, CM_SHAPEW_WUT_DATA, bwue_vawue);
	}

}

static enum dc_wut_mode dpp20_get_shapew_cuwwent(stwuct dpp *dpp_base)
{
	enum dc_wut_mode mode;
	uint32_t state_mode;
	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	WEG_GET(CM_SHAPEW_WUT_WWITE_EN_MASK, CM_SHAPEW_CONFIG_STATUS, &state_mode);

	switch (state_mode) {
	case 0:
		mode = WUT_BYPASS;
		bweak;
	case 1:
		mode = WUT_WAM_A;
		bweak;
	case 2:
		mode = WUT_WAM_B;
		bweak;
	defauwt:
		mode = WUT_BYPASS;
		bweak;
	}

	wetuwn mode;
}

static void dpp20_configuwe_shapew_wut(
		stwuct dpp *dpp_base,
		boow is_wam_a)
{
	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	WEG_UPDATE(CM_SHAPEW_WUT_WWITE_EN_MASK,
			CM_SHAPEW_WUT_WWITE_EN_MASK, 7);
	WEG_UPDATE(CM_SHAPEW_WUT_WWITE_EN_MASK,
			CM_SHAPEW_WUT_WWITE_SEW, is_wam_a == twue ? 0:1);
	WEG_SET(CM_SHAPEW_WUT_INDEX, 0, CM_SHAPEW_WUT_INDEX, 0);
}

/*pwogwam shapew WAM A*/

static void dpp20_pwogwam_shapew_wuta_settings(
		stwuct dpp *dpp_base,
		const stwuct pww_pawams *pawams)
{
	const stwuct gamma_cuwve *cuwve;
	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	WEG_SET_2(CM_SHAPEW_WAMA_STAWT_CNTW_B, 0,
		CM_SHAPEW_WAMA_EXP_WEGION_STAWT_B, pawams->cownew_points[0].bwue.custom_fwoat_x,
		CM_SHAPEW_WAMA_EXP_WEGION_STAWT_SEGMENT_B, 0);
	WEG_SET_2(CM_SHAPEW_WAMA_STAWT_CNTW_G, 0,
		CM_SHAPEW_WAMA_EXP_WEGION_STAWT_G, pawams->cownew_points[0].gween.custom_fwoat_x,
		CM_SHAPEW_WAMA_EXP_WEGION_STAWT_SEGMENT_G, 0);
	WEG_SET_2(CM_SHAPEW_WAMA_STAWT_CNTW_W, 0,
		CM_SHAPEW_WAMA_EXP_WEGION_STAWT_W, pawams->cownew_points[0].wed.custom_fwoat_x,
		CM_SHAPEW_WAMA_EXP_WEGION_STAWT_SEGMENT_W, 0);

	WEG_SET_2(CM_SHAPEW_WAMA_END_CNTW_B, 0,
		CM_SHAPEW_WAMA_EXP_WEGION_END_B, pawams->cownew_points[1].bwue.custom_fwoat_x,
		CM_SHAPEW_WAMA_EXP_WEGION_END_BASE_B, pawams->cownew_points[1].bwue.custom_fwoat_y);

	WEG_SET_2(CM_SHAPEW_WAMA_END_CNTW_G, 0,
		CM_SHAPEW_WAMA_EXP_WEGION_END_G, pawams->cownew_points[1].gween.custom_fwoat_x,
		CM_SHAPEW_WAMA_EXP_WEGION_END_BASE_G, pawams->cownew_points[1].gween.custom_fwoat_y);

	WEG_SET_2(CM_SHAPEW_WAMA_END_CNTW_W, 0,
		CM_SHAPEW_WAMA_EXP_WEGION_END_W, pawams->cownew_points[1].wed.custom_fwoat_x,
		CM_SHAPEW_WAMA_EXP_WEGION_END_BASE_W, pawams->cownew_points[1].wed.custom_fwoat_y);

	cuwve = pawams->aww_cuwve_points;
	WEG_SET_4(CM_SHAPEW_WAMA_WEGION_0_1, 0,
		CM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMA_WEGION_2_3, 0,
		CM_SHAPEW_WAMA_EXP_WEGION2_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMA_EXP_WEGION2_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMA_EXP_WEGION3_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMA_EXP_WEGION3_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMA_WEGION_4_5, 0,
		CM_SHAPEW_WAMA_EXP_WEGION4_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMA_EXP_WEGION4_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMA_EXP_WEGION5_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMA_EXP_WEGION5_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMA_WEGION_6_7, 0,
		CM_SHAPEW_WAMA_EXP_WEGION6_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMA_EXP_WEGION6_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMA_EXP_WEGION7_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMA_EXP_WEGION7_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMA_WEGION_8_9, 0,
		CM_SHAPEW_WAMA_EXP_WEGION8_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMA_EXP_WEGION8_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMA_EXP_WEGION9_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMA_EXP_WEGION9_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMA_WEGION_10_11, 0,
		CM_SHAPEW_WAMA_EXP_WEGION10_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMA_EXP_WEGION10_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMA_EXP_WEGION11_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMA_EXP_WEGION11_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMA_WEGION_12_13, 0,
		CM_SHAPEW_WAMA_EXP_WEGION12_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMA_EXP_WEGION12_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMA_EXP_WEGION13_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMA_EXP_WEGION13_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMA_WEGION_14_15, 0,
		CM_SHAPEW_WAMA_EXP_WEGION14_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMA_EXP_WEGION14_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMA_EXP_WEGION15_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMA_EXP_WEGION15_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMA_WEGION_16_17, 0,
		CM_SHAPEW_WAMA_EXP_WEGION16_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMA_EXP_WEGION16_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMA_EXP_WEGION17_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMA_EXP_WEGION17_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMA_WEGION_18_19, 0,
		CM_SHAPEW_WAMA_EXP_WEGION18_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMA_EXP_WEGION18_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMA_EXP_WEGION19_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMA_EXP_WEGION19_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMA_WEGION_20_21, 0,
		CM_SHAPEW_WAMA_EXP_WEGION20_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMA_EXP_WEGION20_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMA_EXP_WEGION21_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMA_EXP_WEGION21_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMA_WEGION_22_23, 0,
		CM_SHAPEW_WAMA_EXP_WEGION22_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMA_EXP_WEGION22_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMA_EXP_WEGION23_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMA_EXP_WEGION23_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMA_WEGION_24_25, 0,
		CM_SHAPEW_WAMA_EXP_WEGION24_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMA_EXP_WEGION24_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMA_EXP_WEGION25_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMA_EXP_WEGION25_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMA_WEGION_26_27, 0,
		CM_SHAPEW_WAMA_EXP_WEGION26_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMA_EXP_WEGION26_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMA_EXP_WEGION27_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMA_EXP_WEGION27_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMA_WEGION_28_29, 0,
		CM_SHAPEW_WAMA_EXP_WEGION28_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMA_EXP_WEGION28_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMA_EXP_WEGION29_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMA_EXP_WEGION29_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMA_WEGION_30_31, 0,
		CM_SHAPEW_WAMA_EXP_WEGION30_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMA_EXP_WEGION30_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMA_EXP_WEGION31_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMA_EXP_WEGION31_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMA_WEGION_32_33, 0,
		CM_SHAPEW_WAMA_EXP_WEGION32_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMA_EXP_WEGION32_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMA_EXP_WEGION33_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMA_EXP_WEGION33_NUM_SEGMENTS, cuwve[1].segments_num);
}

/*pwogwam shapew WAM B*/
static void dpp20_pwogwam_shapew_wutb_settings(
		stwuct dpp *dpp_base,
		const stwuct pww_pawams *pawams)
{
	const stwuct gamma_cuwve *cuwve;
	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	WEG_SET_2(CM_SHAPEW_WAMB_STAWT_CNTW_B, 0,
		CM_SHAPEW_WAMB_EXP_WEGION_STAWT_B, pawams->cownew_points[0].bwue.custom_fwoat_x,
		CM_SHAPEW_WAMB_EXP_WEGION_STAWT_SEGMENT_B, 0);
	WEG_SET_2(CM_SHAPEW_WAMB_STAWT_CNTW_G, 0,
		CM_SHAPEW_WAMB_EXP_WEGION_STAWT_G, pawams->cownew_points[0].gween.custom_fwoat_x,
		CM_SHAPEW_WAMB_EXP_WEGION_STAWT_SEGMENT_G, 0);
	WEG_SET_2(CM_SHAPEW_WAMB_STAWT_CNTW_W, 0,
		CM_SHAPEW_WAMB_EXP_WEGION_STAWT_W, pawams->cownew_points[0].wed.custom_fwoat_x,
		CM_SHAPEW_WAMB_EXP_WEGION_STAWT_SEGMENT_W, 0);

	WEG_SET_2(CM_SHAPEW_WAMB_END_CNTW_B, 0,
		CM_SHAPEW_WAMB_EXP_WEGION_END_B, pawams->cownew_points[1].bwue.custom_fwoat_x,
		CM_SHAPEW_WAMB_EXP_WEGION_END_BASE_B, pawams->cownew_points[1].bwue.custom_fwoat_y);

	WEG_SET_2(CM_SHAPEW_WAMB_END_CNTW_G, 0,
		CM_SHAPEW_WAMB_EXP_WEGION_END_G, pawams->cownew_points[1].gween.custom_fwoat_x,
		CM_SHAPEW_WAMB_EXP_WEGION_END_BASE_G, pawams->cownew_points[1].gween.custom_fwoat_y);

	WEG_SET_2(CM_SHAPEW_WAMB_END_CNTW_W, 0,
		CM_SHAPEW_WAMB_EXP_WEGION_END_W, pawams->cownew_points[1].wed.custom_fwoat_x,
		CM_SHAPEW_WAMB_EXP_WEGION_END_BASE_W, pawams->cownew_points[1].wed.custom_fwoat_y);

	cuwve = pawams->aww_cuwve_points;
	WEG_SET_4(CM_SHAPEW_WAMB_WEGION_0_1, 0,
		CM_SHAPEW_WAMB_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMB_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMB_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMB_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMB_WEGION_2_3, 0,
		CM_SHAPEW_WAMB_EXP_WEGION2_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMB_EXP_WEGION2_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMB_EXP_WEGION3_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMB_EXP_WEGION3_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMB_WEGION_4_5, 0,
		CM_SHAPEW_WAMB_EXP_WEGION4_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMB_EXP_WEGION4_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMB_EXP_WEGION5_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMB_EXP_WEGION5_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMB_WEGION_6_7, 0,
		CM_SHAPEW_WAMB_EXP_WEGION6_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMB_EXP_WEGION6_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMB_EXP_WEGION7_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMB_EXP_WEGION7_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMB_WEGION_8_9, 0,
		CM_SHAPEW_WAMB_EXP_WEGION8_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMB_EXP_WEGION8_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMB_EXP_WEGION9_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMB_EXP_WEGION9_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMB_WEGION_10_11, 0,
		CM_SHAPEW_WAMB_EXP_WEGION10_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMB_EXP_WEGION10_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMB_EXP_WEGION11_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMB_EXP_WEGION11_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMB_WEGION_12_13, 0,
		CM_SHAPEW_WAMB_EXP_WEGION12_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMB_EXP_WEGION12_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMB_EXP_WEGION13_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMB_EXP_WEGION13_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMB_WEGION_14_15, 0,
		CM_SHAPEW_WAMB_EXP_WEGION14_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMB_EXP_WEGION14_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMB_EXP_WEGION15_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMB_EXP_WEGION15_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMB_WEGION_16_17, 0,
		CM_SHAPEW_WAMB_EXP_WEGION16_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMB_EXP_WEGION16_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMB_EXP_WEGION17_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMB_EXP_WEGION17_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMB_WEGION_18_19, 0,
		CM_SHAPEW_WAMB_EXP_WEGION18_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMB_EXP_WEGION18_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMB_EXP_WEGION19_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMB_EXP_WEGION19_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMB_WEGION_20_21, 0,
		CM_SHAPEW_WAMB_EXP_WEGION20_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMB_EXP_WEGION20_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMB_EXP_WEGION21_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMB_EXP_WEGION21_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMB_WEGION_22_23, 0,
		CM_SHAPEW_WAMB_EXP_WEGION22_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMB_EXP_WEGION22_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMB_EXP_WEGION23_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMB_EXP_WEGION23_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMB_WEGION_24_25, 0,
		CM_SHAPEW_WAMB_EXP_WEGION24_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMB_EXP_WEGION24_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMB_EXP_WEGION25_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMB_EXP_WEGION25_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMB_WEGION_26_27, 0,
		CM_SHAPEW_WAMB_EXP_WEGION26_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMB_EXP_WEGION26_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMB_EXP_WEGION27_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMB_EXP_WEGION27_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMB_WEGION_28_29, 0,
		CM_SHAPEW_WAMB_EXP_WEGION28_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMB_EXP_WEGION28_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMB_EXP_WEGION29_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMB_EXP_WEGION29_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMB_WEGION_30_31, 0,
		CM_SHAPEW_WAMB_EXP_WEGION30_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMB_EXP_WEGION30_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMB_EXP_WEGION31_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMB_EXP_WEGION31_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(CM_SHAPEW_WAMB_WEGION_32_33, 0,
		CM_SHAPEW_WAMB_EXP_WEGION32_WUT_OFFSET, cuwve[0].offset,
		CM_SHAPEW_WAMB_EXP_WEGION32_NUM_SEGMENTS, cuwve[0].segments_num,
		CM_SHAPEW_WAMB_EXP_WEGION33_WUT_OFFSET, cuwve[1].offset,
		CM_SHAPEW_WAMB_EXP_WEGION33_NUM_SEGMENTS, cuwve[1].segments_num);

}


boow dpp20_pwogwam_shapew(
		stwuct dpp *dpp_base,
		const stwuct pww_pawams *pawams)
{
	enum dc_wut_mode cuwwent_mode;
	enum dc_wut_mode next_mode;

	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	if (pawams == NUWW) {
		WEG_SET(CM_SHAPEW_CONTWOW, 0, CM_SHAPEW_WUT_MODE, 0);
		wetuwn fawse;
	}
	cuwwent_mode = dpp20_get_shapew_cuwwent(dpp_base);

	if (cuwwent_mode == WUT_BYPASS || cuwwent_mode == WUT_WAM_A)
		next_mode = WUT_WAM_B;
	ewse
		next_mode = WUT_WAM_A;

	dpp20_configuwe_shapew_wut(dpp_base, next_mode == WUT_WAM_A);

	if (next_mode == WUT_WAM_A)
		dpp20_pwogwam_shapew_wuta_settings(dpp_base, pawams);
	ewse
		dpp20_pwogwam_shapew_wutb_settings(dpp_base, pawams);

	dpp20_pwogwam_shapew_wut(
			dpp_base, pawams->wgb_wesuwted, pawams->hw_points_num);

	WEG_SET(CM_SHAPEW_CONTWOW, 0, CM_SHAPEW_WUT_MODE, next_mode == WUT_WAM_A ? 1:2);

	wetuwn twue;

}

static enum dc_wut_mode get3dwut_config(
			stwuct dpp *dpp_base,
			boow *is_17x17x17,
			boow *is_12bits_cowow_channew)
{
	uint32_t i_mode, i_enabwe_10bits, wut_size;
	enum dc_wut_mode mode;
	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	WEG_GET_2(CM_3DWUT_WEAD_WWITE_CONTWOW,
			CM_3DWUT_CONFIG_STATUS, &i_mode,
			CM_3DWUT_30BIT_EN, &i_enabwe_10bits);

	switch (i_mode) {
	case 0:
		mode = WUT_BYPASS;
		bweak;
	case 1:
		mode = WUT_WAM_A;
		bweak;
	case 2:
		mode = WUT_WAM_B;
		bweak;
	defauwt:
		mode = WUT_BYPASS;
		bweak;
	}
	if (i_enabwe_10bits > 0)
		*is_12bits_cowow_channew = fawse;
	ewse
		*is_12bits_cowow_channew = twue;

	WEG_GET(CM_3DWUT_MODE, CM_3DWUT_SIZE, &wut_size);

	if (wut_size == 0)
		*is_17x17x17 = twue;
	ewse
		*is_17x17x17 = fawse;

	wetuwn mode;
}
/*
 * sewect wamA ow wamB, ow bypass
 * sewect cowow channew size 10 ow 12 bits
 * sewect 3dwut size 17x17x17 ow 9x9x9
 */
static void dpp20_set_3dwut_mode(
		stwuct dpp *dpp_base,
		enum dc_wut_mode mode,
		boow is_cowow_channew_12bits,
		boow is_wut_size17x17x17)
{
	uint32_t wut_mode;
	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	if (mode == WUT_BYPASS)
		wut_mode = 0;
	ewse if (mode == WUT_WAM_A)
		wut_mode = 1;
	ewse
		wut_mode = 2;

	WEG_UPDATE_2(CM_3DWUT_MODE,
			CM_3DWUT_MODE, wut_mode,
			CM_3DWUT_SIZE, is_wut_size17x17x17 == twue ? 0 : 1);
}

static void dpp20_sewect_3dwut_wam(
		stwuct dpp *dpp_base,
		enum dc_wut_mode mode,
		boow is_cowow_channew_12bits)
{
	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	WEG_UPDATE_2(CM_3DWUT_WEAD_WWITE_CONTWOW,
			CM_3DWUT_WAM_SEW, mode == WUT_WAM_A ? 0 : 1,
			CM_3DWUT_30BIT_EN,
			is_cowow_channew_12bits == twue ? 0:1);
}



static void dpp20_set3dwut_wam12(
		stwuct dpp *dpp_base,
		const stwuct dc_wgb *wut,
		uint32_t entwies)
{
	uint32_t i, wed, gween, bwue, wed1, gween1, bwue1;
	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	fow (i = 0 ; i < entwies; i += 2) {
		wed   = wut[i].wed<<4;
		gween = wut[i].gween<<4;
		bwue  = wut[i].bwue<<4;
		wed1   = wut[i+1].wed<<4;
		gween1 = wut[i+1].gween<<4;
		bwue1  = wut[i+1].bwue<<4;

		WEG_SET_2(CM_3DWUT_DATA, 0,
				CM_3DWUT_DATA0, wed,
				CM_3DWUT_DATA1, wed1);

		WEG_SET_2(CM_3DWUT_DATA, 0,
				CM_3DWUT_DATA0, gween,
				CM_3DWUT_DATA1, gween1);

		WEG_SET_2(CM_3DWUT_DATA, 0,
				CM_3DWUT_DATA0, bwue,
				CM_3DWUT_DATA1, bwue1);

	}
}

/*
 * woad sewected wut with 10 bits cowow channews
 */
static void dpp20_set3dwut_wam10(
		stwuct dpp *dpp_base,
		const stwuct dc_wgb *wut,
		uint32_t entwies)
{
	uint32_t i, wed, gween, bwue, vawue;
	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	fow (i = 0; i < entwies; i++) {
		wed   = wut[i].wed;
		gween = wut[i].gween;
		bwue  = wut[i].bwue;

		vawue = (wed<<20) | (gween<<10) | bwue;

		WEG_SET(CM_3DWUT_DATA_30BIT, 0, CM_3DWUT_DATA_30BIT, vawue);
	}

}


static void dpp20_sewect_3dwut_wam_mask(
		stwuct dpp *dpp_base,
		uint32_t wam_sewection_mask)
{
	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	WEG_UPDATE(CM_3DWUT_WEAD_WWITE_CONTWOW, CM_3DWUT_WWITE_EN_MASK,
			wam_sewection_mask);
	WEG_SET(CM_3DWUT_INDEX, 0, CM_3DWUT_INDEX, 0);
}

boow dpp20_pwogwam_3dwut(
		stwuct dpp *dpp_base,
		stwuct tetwahedwaw_pawams *pawams)
{
	enum dc_wut_mode mode;
	boow is_17x17x17;
	boow is_12bits_cowow_channew;
	stwuct dc_wgb *wut0;
	stwuct dc_wgb *wut1;
	stwuct dc_wgb *wut2;
	stwuct dc_wgb *wut3;
	int wut_size0;
	int wut_size;

	if (pawams == NUWW) {
		dpp20_set_3dwut_mode(dpp_base, WUT_BYPASS, fawse, fawse);
		wetuwn fawse;
	}
	mode = get3dwut_config(dpp_base, &is_17x17x17, &is_12bits_cowow_channew);

	if (mode == WUT_BYPASS || mode == WUT_WAM_B)
		mode = WUT_WAM_A;
	ewse
		mode = WUT_WAM_B;

	is_17x17x17 = !pawams->use_tetwahedwaw_9;
	is_12bits_cowow_channew = pawams->use_12bits;
	if (is_17x17x17) {
		wut0 = pawams->tetwahedwaw_17.wut0;
		wut1 = pawams->tetwahedwaw_17.wut1;
		wut2 = pawams->tetwahedwaw_17.wut2;
		wut3 = pawams->tetwahedwaw_17.wut3;
		wut_size0 = sizeof(pawams->tetwahedwaw_17.wut0)/
					sizeof(pawams->tetwahedwaw_17.wut0[0]);
		wut_size  = sizeof(pawams->tetwahedwaw_17.wut1)/
					sizeof(pawams->tetwahedwaw_17.wut1[0]);
	} ewse {
		wut0 = pawams->tetwahedwaw_9.wut0;
		wut1 = pawams->tetwahedwaw_9.wut1;
		wut2 = pawams->tetwahedwaw_9.wut2;
		wut3 = pawams->tetwahedwaw_9.wut3;
		wut_size0 = sizeof(pawams->tetwahedwaw_9.wut0)/
				sizeof(pawams->tetwahedwaw_9.wut0[0]);
		wut_size  = sizeof(pawams->tetwahedwaw_9.wut1)/
				sizeof(pawams->tetwahedwaw_9.wut1[0]);
		}

	dpp20_sewect_3dwut_wam(dpp_base, mode,
				is_12bits_cowow_channew);
	dpp20_sewect_3dwut_wam_mask(dpp_base, 0x1);
	if (is_12bits_cowow_channew)
		dpp20_set3dwut_wam12(dpp_base, wut0, wut_size0);
	ewse
		dpp20_set3dwut_wam10(dpp_base, wut0, wut_size0);

	dpp20_sewect_3dwut_wam_mask(dpp_base, 0x2);
	if (is_12bits_cowow_channew)
		dpp20_set3dwut_wam12(dpp_base, wut1, wut_size);
	ewse
		dpp20_set3dwut_wam10(dpp_base, wut1, wut_size);

	dpp20_sewect_3dwut_wam_mask(dpp_base, 0x4);
	if (is_12bits_cowow_channew)
		dpp20_set3dwut_wam12(dpp_base, wut2, wut_size);
	ewse
		dpp20_set3dwut_wam10(dpp_base, wut2, wut_size);

	dpp20_sewect_3dwut_wam_mask(dpp_base, 0x8);
	if (is_12bits_cowow_channew)
		dpp20_set3dwut_wam12(dpp_base, wut3, wut_size);
	ewse
		dpp20_set3dwut_wam10(dpp_base, wut3, wut_size);


	dpp20_set_3dwut_mode(dpp_base, mode, is_12bits_cowow_channew,
					is_17x17x17);

	wetuwn twue;
}

void dpp2_set_hdw_muwtipwiew(
		stwuct dpp *dpp_base,
		uint32_t muwtipwiew)
{
	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	WEG_UPDATE(CM_HDW_MUWT_COEF, CM_HDW_MUWT_COEF, muwtipwiew);
}
