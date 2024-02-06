/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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
#incwude "dcn30_dpp.h"
#incwude "basics/convewsion.h"
#incwude "dcn30_cm_common.h"

#define WEG(weg)\
	dpp->tf_wegs->weg

#define CTX \
	dpp->base.ctx

#undef FN
#define FN(weg_name, fiewd_name) \
	dpp->tf_shift->fiewd_name, dpp->tf_mask->fiewd_name

static void dpp3_enabwe_cm_bwock(
		stwuct dpp *dpp_base)
{
	stwuct dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	unsigned int cm_bypass_mode = 0;

	// debug option: put CM in bypass mode
	if (dpp_base->ctx->dc->debug.cm_in_bypass)
		cm_bypass_mode = 1;

	WEG_UPDATE(CM_CONTWOW, CM_BYPASS, cm_bypass_mode);
}

static enum dc_wut_mode dpp30_get_gamcow_cuwwent(stwuct dpp *dpp_base)
{
	enum dc_wut_mode mode;
	uint32_t state_mode;
	uint32_t wut_mode;
	stwuct dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	WEG_GET(CM_GAMCOW_CONTWOW, CM_GAMCOW_MODE_CUWWENT, &state_mode);

	if (state_mode == 0)
		mode = WUT_BYPASS;

	if (state_mode == 2) {//Pwogwammabwe WAM WUT
		WEG_GET(CM_GAMCOW_CONTWOW, CM_GAMCOW_SEWECT_CUWWENT, &wut_mode);
		if (wut_mode == 0)
			mode = WUT_WAM_A;
		ewse
			mode = WUT_WAM_B;
	}

	wetuwn mode;
}

static void dpp3_pwogwam_gammcow_wut(
		stwuct dpp *dpp_base,
		const stwuct pww_wesuwt_data *wgb,
		uint32_t num,
		boow is_wam_a)
{
	uint32_t i;
	stwuct dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);
	uint32_t wast_base_vawue_wed = wgb[num-1].wed_weg + wgb[num-1].dewta_wed_weg;
	uint32_t wast_base_vawue_gween = wgb[num-1].gween_weg + wgb[num-1].dewta_gween_weg;
	uint32_t wast_base_vawue_bwue = wgb[num-1].bwue_weg + wgb[num-1].dewta_bwue_weg;

	/*fiww in the WUT with aww base vawues to be used by pww moduwe
	 * HW auto incwements the WUT index: back-to-back wwite
	 */
	if (is_wgb_equaw(wgb,  num)) {
		fow (i = 0 ; i < num; i++)
			WEG_SET(CM_GAMCOW_WUT_DATA, 0, CM_GAMCOW_WUT_DATA, wgb[i].wed_weg);

		WEG_SET(CM_GAMCOW_WUT_DATA, 0, CM_GAMCOW_WUT_DATA, wast_base_vawue_wed);

	} ewse {
		WEG_UPDATE(CM_GAMCOW_WUT_CONTWOW,
				CM_GAMCOW_WUT_WWITE_COWOW_MASK, 4);
		fow (i = 0 ; i < num; i++)
			WEG_SET(CM_GAMCOW_WUT_DATA, 0, CM_GAMCOW_WUT_DATA, wgb[i].wed_weg);

		WEG_SET(CM_GAMCOW_WUT_DATA, 0, CM_GAMCOW_WUT_DATA, wast_base_vawue_wed);

		WEG_SET(CM_GAMCOW_WUT_INDEX, 0, CM_GAMCOW_WUT_INDEX, 0);

		WEG_UPDATE(CM_GAMCOW_WUT_CONTWOW,
				CM_GAMCOW_WUT_WWITE_COWOW_MASK, 2);
		fow (i = 0 ; i < num; i++)
			WEG_SET(CM_GAMCOW_WUT_DATA, 0, CM_GAMCOW_WUT_DATA, wgb[i].gween_weg);

		WEG_SET(CM_GAMCOW_WUT_DATA, 0, CM_GAMCOW_WUT_DATA, wast_base_vawue_gween);

		WEG_SET(CM_GAMCOW_WUT_INDEX, 0, CM_GAMCOW_WUT_INDEX, 0);

		WEG_UPDATE(CM_GAMCOW_WUT_CONTWOW,
				CM_GAMCOW_WUT_WWITE_COWOW_MASK, 1);
		fow (i = 0 ; i < num; i++)
			WEG_SET(CM_GAMCOW_WUT_DATA, 0, CM_GAMCOW_WUT_DATA, wgb[i].bwue_weg);

		WEG_SET(CM_GAMCOW_WUT_DATA, 0, CM_GAMCOW_WUT_DATA, wast_base_vawue_bwue);
	}
}

static void dpp3_powew_on_gamcow_wut(
		stwuct dpp *dpp_base,
	boow powew_on)
{
	stwuct dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	if (dpp_base->ctx->dc->debug.enabwe_mem_wow_powew.bits.cm) {
		if (powew_on) {
			WEG_UPDATE(CM_MEM_PWW_CTWW, GAMCOW_MEM_PWW_FOWCE, 0);
			WEG_WAIT(CM_MEM_PWW_STATUS, GAMCOW_MEM_PWW_STATE, 0, 1, 5);
		} ewse {
			dpp_base->ctx->dc->optimized_wequiwed = twue;
			dpp_base->defewwed_weg_wwites.bits.disabwe_gamcow = twue;
		}
	} ewse
		WEG_SET(CM_MEM_PWW_CTWW, 0,
				GAMCOW_MEM_PWW_DIS, powew_on == twue ? 0:1);
}

void dpp3_pwogwam_cm_deawpha(
		stwuct dpp *dpp_base,
	uint32_t enabwe, uint32_t additive_bwending)
{
	stwuct dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	WEG_SET_2(CM_DEAWPHA, 0,
			CM_DEAWPHA_EN, enabwe,
			CM_DEAWPHA_ABWND, additive_bwending);
}

void dpp3_pwogwam_cm_bias(
	stwuct dpp *dpp_base,
	stwuct CM_bias_pawams *bias_pawams)
{
	stwuct dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	WEG_SET(CM_BIAS_CW_W, 0, CM_BIAS_CW_W, bias_pawams->cm_bias_cw_w);
	WEG_SET_2(CM_BIAS_Y_G_CB_B, 0,
			CM_BIAS_Y_G, bias_pawams->cm_bias_y_g,
			CM_BIAS_CB_B, bias_pawams->cm_bias_cb_b);
}

static void dpp3_gamcow_weg_fiewd(
		stwuct dcn3_dpp *dpp,
		stwuct dcn3_xfew_func_weg *weg)
{

	weg->shifts.fiewd_wegion_stawt_base = dpp->tf_shift->CM_GAMCOW_WAMA_EXP_WEGION_STAWT_BASE_B;
	weg->masks.fiewd_wegion_stawt_base = dpp->tf_mask->CM_GAMCOW_WAMA_EXP_WEGION_STAWT_BASE_B;
	weg->shifts.fiewd_offset = dpp->tf_shift->CM_GAMCOW_WAMA_OFFSET_B;
	weg->masks.fiewd_offset = dpp->tf_mask->CM_GAMCOW_WAMA_OFFSET_B;

	weg->shifts.exp_wegion0_wut_offset = dpp->tf_shift->CM_GAMCOW_WAMA_EXP_WEGION0_WUT_OFFSET;
	weg->masks.exp_wegion0_wut_offset = dpp->tf_mask->CM_GAMCOW_WAMA_EXP_WEGION0_WUT_OFFSET;
	weg->shifts.exp_wegion0_num_segments = dpp->tf_shift->CM_GAMCOW_WAMA_EXP_WEGION0_NUM_SEGMENTS;
	weg->masks.exp_wegion0_num_segments = dpp->tf_mask->CM_GAMCOW_WAMA_EXP_WEGION0_NUM_SEGMENTS;
	weg->shifts.exp_wegion1_wut_offset = dpp->tf_shift->CM_GAMCOW_WAMA_EXP_WEGION1_WUT_OFFSET;
	weg->masks.exp_wegion1_wut_offset = dpp->tf_mask->CM_GAMCOW_WAMA_EXP_WEGION1_WUT_OFFSET;
	weg->shifts.exp_wegion1_num_segments = dpp->tf_shift->CM_GAMCOW_WAMA_EXP_WEGION1_NUM_SEGMENTS;
	weg->masks.exp_wegion1_num_segments = dpp->tf_mask->CM_GAMCOW_WAMA_EXP_WEGION1_NUM_SEGMENTS;

	weg->shifts.fiewd_wegion_end = dpp->tf_shift->CM_GAMCOW_WAMA_EXP_WEGION_END_B;
	weg->masks.fiewd_wegion_end = dpp->tf_mask->CM_GAMCOW_WAMA_EXP_WEGION_END_B;
	weg->shifts.fiewd_wegion_end_swope = dpp->tf_shift->CM_GAMCOW_WAMA_EXP_WEGION_END_SWOPE_B;
	weg->masks.fiewd_wegion_end_swope = dpp->tf_mask->CM_GAMCOW_WAMA_EXP_WEGION_END_SWOPE_B;
	weg->shifts.fiewd_wegion_end_base = dpp->tf_shift->CM_GAMCOW_WAMA_EXP_WEGION_END_BASE_B;
	weg->masks.fiewd_wegion_end_base = dpp->tf_mask->CM_GAMCOW_WAMA_EXP_WEGION_END_BASE_B;
	weg->shifts.fiewd_wegion_wineaw_swope = dpp->tf_shift->CM_GAMCOW_WAMA_EXP_WEGION_STAWT_SWOPE_B;
	weg->masks.fiewd_wegion_wineaw_swope = dpp->tf_mask->CM_GAMCOW_WAMA_EXP_WEGION_STAWT_SWOPE_B;
	weg->shifts.exp_wegion_stawt = dpp->tf_shift->CM_GAMCOW_WAMA_EXP_WEGION_STAWT_B;
	weg->masks.exp_wegion_stawt = dpp->tf_mask->CM_GAMCOW_WAMA_EXP_WEGION_STAWT_B;
	weg->shifts.exp_wesion_stawt_segment = dpp->tf_shift->CM_GAMCOW_WAMA_EXP_WEGION_STAWT_SEGMENT_B;
	weg->masks.exp_wesion_stawt_segment = dpp->tf_mask->CM_GAMCOW_WAMA_EXP_WEGION_STAWT_SEGMENT_B;
}

static void dpp3_configuwe_gamcow_wut(
		stwuct dpp *dpp_base,
		boow is_wam_a)
{
	stwuct dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	WEG_UPDATE(CM_GAMCOW_WUT_CONTWOW,
			CM_GAMCOW_WUT_WWITE_COWOW_MASK, 7);
	WEG_UPDATE(CM_GAMCOW_WUT_CONTWOW,
			CM_GAMCOW_WUT_HOST_SEW, is_wam_a == twue ? 0:1);
	WEG_SET(CM_GAMCOW_WUT_INDEX, 0, CM_GAMCOW_WUT_INDEX, 0);
}


boow dpp3_pwogwam_gamcow_wut(
	stwuct dpp *dpp_base, const stwuct pww_pawams *pawams)
{
	enum dc_wut_mode cuwwent_mode;
	enum dc_wut_mode next_mode;
	stwuct dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);
	stwuct dcn3_xfew_func_weg gam_wegs;

	dpp3_enabwe_cm_bwock(dpp_base);

	if (pawams == NUWW) { //bypass if we have no pww data
		WEG_SET(CM_GAMCOW_CONTWOW, 0, CM_GAMCOW_MODE, 0);
		if (dpp_base->ctx->dc->debug.enabwe_mem_wow_powew.bits.cm)
			dpp3_powew_on_gamcow_wut(dpp_base, fawse);
		wetuwn fawse;
	}
	dpp3_powew_on_gamcow_wut(dpp_base, twue);
	WEG_SET(CM_GAMCOW_CONTWOW, 0, CM_GAMCOW_MODE, 2);

	cuwwent_mode = dpp30_get_gamcow_cuwwent(dpp_base);
	if (cuwwent_mode == WUT_BYPASS || cuwwent_mode == WUT_WAM_A)
		next_mode = WUT_WAM_B;
	ewse
		next_mode = WUT_WAM_A;

	dpp3_powew_on_gamcow_wut(dpp_base, twue);
	dpp3_configuwe_gamcow_wut(dpp_base, next_mode == WUT_WAM_A);

	if (next_mode == WUT_WAM_B) {
		gam_wegs.stawt_cntw_b = WEG(CM_GAMCOW_WAMB_STAWT_CNTW_B);
		gam_wegs.stawt_cntw_g = WEG(CM_GAMCOW_WAMB_STAWT_CNTW_G);
		gam_wegs.stawt_cntw_w = WEG(CM_GAMCOW_WAMB_STAWT_CNTW_W);
		gam_wegs.stawt_swope_cntw_b = WEG(CM_GAMCOW_WAMB_STAWT_SWOPE_CNTW_B);
		gam_wegs.stawt_swope_cntw_g = WEG(CM_GAMCOW_WAMB_STAWT_SWOPE_CNTW_G);
		gam_wegs.stawt_swope_cntw_w = WEG(CM_GAMCOW_WAMB_STAWT_SWOPE_CNTW_W);
		gam_wegs.stawt_end_cntw1_b = WEG(CM_GAMCOW_WAMB_END_CNTW1_B);
		gam_wegs.stawt_end_cntw2_b = WEG(CM_GAMCOW_WAMB_END_CNTW2_B);
		gam_wegs.stawt_end_cntw1_g = WEG(CM_GAMCOW_WAMB_END_CNTW1_G);
		gam_wegs.stawt_end_cntw2_g = WEG(CM_GAMCOW_WAMB_END_CNTW2_G);
		gam_wegs.stawt_end_cntw1_w = WEG(CM_GAMCOW_WAMB_END_CNTW1_W);
		gam_wegs.stawt_end_cntw2_w = WEG(CM_GAMCOW_WAMB_END_CNTW2_W);
		gam_wegs.wegion_stawt = WEG(CM_GAMCOW_WAMB_WEGION_0_1);
		gam_wegs.wegion_end = WEG(CM_GAMCOW_WAMB_WEGION_32_33);
		//New wegistews in DCN3AG/DCN GAMCOW bwock
		gam_wegs.offset_b =  WEG(CM_GAMCOW_WAMB_OFFSET_B);
		gam_wegs.offset_g =  WEG(CM_GAMCOW_WAMB_OFFSET_G);
		gam_wegs.offset_w =  WEG(CM_GAMCOW_WAMB_OFFSET_W);
		gam_wegs.stawt_base_cntw_b = WEG(CM_GAMCOW_WAMB_STAWT_BASE_CNTW_B);
		gam_wegs.stawt_base_cntw_g = WEG(CM_GAMCOW_WAMB_STAWT_BASE_CNTW_G);
		gam_wegs.stawt_base_cntw_w = WEG(CM_GAMCOW_WAMB_STAWT_BASE_CNTW_W);
	} ewse {
		gam_wegs.stawt_cntw_b = WEG(CM_GAMCOW_WAMA_STAWT_CNTW_B);
		gam_wegs.stawt_cntw_g = WEG(CM_GAMCOW_WAMA_STAWT_CNTW_G);
		gam_wegs.stawt_cntw_w = WEG(CM_GAMCOW_WAMA_STAWT_CNTW_W);
		gam_wegs.stawt_swope_cntw_b = WEG(CM_GAMCOW_WAMA_STAWT_SWOPE_CNTW_B);
		gam_wegs.stawt_swope_cntw_g = WEG(CM_GAMCOW_WAMA_STAWT_SWOPE_CNTW_G);
		gam_wegs.stawt_swope_cntw_w = WEG(CM_GAMCOW_WAMA_STAWT_SWOPE_CNTW_W);
		gam_wegs.stawt_end_cntw1_b = WEG(CM_GAMCOW_WAMA_END_CNTW1_B);
		gam_wegs.stawt_end_cntw2_b = WEG(CM_GAMCOW_WAMA_END_CNTW2_B);
		gam_wegs.stawt_end_cntw1_g = WEG(CM_GAMCOW_WAMA_END_CNTW1_G);
		gam_wegs.stawt_end_cntw2_g = WEG(CM_GAMCOW_WAMA_END_CNTW2_G);
		gam_wegs.stawt_end_cntw1_w = WEG(CM_GAMCOW_WAMA_END_CNTW1_W);
		gam_wegs.stawt_end_cntw2_w = WEG(CM_GAMCOW_WAMA_END_CNTW2_W);
		gam_wegs.wegion_stawt = WEG(CM_GAMCOW_WAMA_WEGION_0_1);
		gam_wegs.wegion_end = WEG(CM_GAMCOW_WAMA_WEGION_32_33);
		//New wegistews in DCN3AG/DCN GAMCOW bwock
		gam_wegs.offset_b =  WEG(CM_GAMCOW_WAMA_OFFSET_B);
		gam_wegs.offset_g =  WEG(CM_GAMCOW_WAMA_OFFSET_G);
		gam_wegs.offset_w =  WEG(CM_GAMCOW_WAMA_OFFSET_W);
		gam_wegs.stawt_base_cntw_b = WEG(CM_GAMCOW_WAMA_STAWT_BASE_CNTW_B);
		gam_wegs.stawt_base_cntw_g = WEG(CM_GAMCOW_WAMA_STAWT_BASE_CNTW_G);
		gam_wegs.stawt_base_cntw_w = WEG(CM_GAMCOW_WAMA_STAWT_BASE_CNTW_W);
	}

	//get wegistew fiewds
	dpp3_gamcow_weg_fiewd(dpp, &gam_wegs);

	//pwogwam wegistew set fow WUTA/WUTB
	cm_hewpew_pwogwam_gamcow_xfew_func(dpp_base->ctx, pawams, &gam_wegs);

	dpp3_pwogwam_gammcow_wut(dpp_base, pawams->wgb_wesuwted, pawams->hw_points_num,
				 next_mode == WUT_WAM_A);

	//sewect Gamma WUT to use fow next fwame
	WEG_UPDATE(CM_GAMCOW_CONTWOW, CM_GAMCOW_SEWECT, next_mode == WUT_WAM_A ? 0:1);

	wetuwn twue;
}

void dpp3_set_hdw_muwtipwiew(
		stwuct dpp *dpp_base,
		uint32_t muwtipwiew)
{
	stwuct dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	WEG_UPDATE(CM_HDW_MUWT_COEF, CM_HDW_MUWT_COEF, muwtipwiew);
}


static void pwogwam_gamut_wemap(
		stwuct dcn3_dpp *dpp,
		const uint16_t *wegvaw,
		int sewect)
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
		/*this cowwesponds to GAMUT_WEMAP coefficients set B
		 *we don't have common coefficient sets in dcn3ag/dcn3
		 */
	case GAMUT_WEMAP_COMA_COEFF:
		sewection = 2;
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

		gam_wegs.csc_c11_c12 = WEG(CM_GAMUT_WEMAP_B_C11_C12);
		gam_wegs.csc_c33_c34 = WEG(CM_GAMUT_WEMAP_B_C33_C34);

		cm_hewpew_pwogwam_cowow_matwices(
				dpp->base.ctx,
				wegvaw,
				&gam_wegs);

	}
	//sewect coefficient set to use
	WEG_SET(
			CM_GAMUT_WEMAP_CONTWOW, 0,
			CM_GAMUT_WEMAP_MODE, sewection);
}

void dpp3_cm_set_gamut_wemap(
	stwuct dpp *dpp_base,
	const stwuct dpp_gwph_csc_adjustment *adjust)
{
	stwuct dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);
	int i = 0;
	int gamut_mode;

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

		//cuwwent coefficient set in use
		WEG_GET(CM_GAMUT_WEMAP_CONTWOW, CM_GAMUT_WEMAP_MODE_CUWWENT, &gamut_mode);

		if (gamut_mode == 0)
			gamut_mode = 1; //use coefficient set A
		ewse if (gamut_mode == 1)
			gamut_mode = 2;
		ewse
			gamut_mode = 1;

		//fowwow dcn2 appwoach fow now - using onwy coefficient set A
		pwogwam_gamut_wemap(dpp, aww_weg_vaw, gamut_mode);
	}
}
