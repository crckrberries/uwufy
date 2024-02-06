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

void dpp20_wead_state(stwuct dpp *dpp_base,
		stwuct dcn_dpp_state *s)
{
	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	WEG_GET(DPP_CONTWOW,
			DPP_CWOCK_ENABWE, &s->is_enabwed);
	WEG_GET(CM_DGAM_CONTWOW,
			CM_DGAM_WUT_MODE, &s->dgam_wut_mode);
	// BGAM has no WOM, and definition is diffewent, can't weuse same dump
	//WEG_GET(CM_BWNDGAM_CONTWOW,
	//		CM_BWNDGAM_WUT_MODE, &s->wgam_wut_mode);
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

void dpp2_powew_on_obuf(
		stwuct dpp *dpp_base,
	boow powew_on)
{
	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	WEG_UPDATE(CM_MEM_PWW_CTWW, SHAWED_MEM_PWW_DIS, powew_on == twue ? 1:0);

	WEG_UPDATE(OBUF_MEM_PWW_CTWW,
			OBUF_MEM_PWW_FOWCE, powew_on == twue ? 0:1);

	WEG_UPDATE(DSCW_MEM_PWW_CTWW,
			WUT_MEM_PWW_FOWCE, powew_on == twue ? 0:1);
}

void dpp2_dummy_pwogwam_input_wut(
		stwuct dpp *dpp_base,
		const stwuct dc_gamma *gamma)
{}

static void dpp2_cnv_setup (
		stwuct dpp *dpp_base,
		enum suwface_pixew_fowmat fowmat,
		enum expansion_mode mode,
		stwuct dc_csc_twansfowm input_csc_cowow_matwix,
		enum dc_cowow_space input_cowow_space,
		stwuct cnv_awpha_2bit_wut *awpha_2bit_wut)
{
	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);
	uint32_t pixew_fowmat = 0;
	uint32_t awpha_en = 1;
	enum dc_cowow_space cowow_space = COWOW_SPACE_SWGB;
	enum dcn20_input_csc_sewect sewect = DCN2_ICSC_SEWECT_BYPASS;
	boow fowce_disabwe_cuwsow = fawse;
	stwuct out_csc_cowow_matwix tbw_entwy;
	uint32_t is_2bit = 0;
	int i = 0;

	WEG_SET_2(FOWMAT_CONTWOW, 0,
		CNVC_BYPASS, 0,
		FOWMAT_EXPANSION_MODE, mode);

	//hawdcode defauwt
    //FOWMAT_CONTWOW. FOWMAT_CNV16                                 	defauwt 0: U0.16/S.1.15;         1: U1.15/ S.1.14
    //FOWMAT_CONTWOW. CNVC_BYPASS_MSB_AWIGN          				defauwt 0: disabwed              1: enabwed
    //FOWMAT_CONTWOW. CWAMP_POSITIVE                               	defauwt 0: disabwed              1: enabwed
    //FOWMAT_CONTWOW. CWAMP_POSITIVE_C                          	defauwt 0: disabwed              1: enabwed
	WEG_UPDATE(FOWMAT_CONTWOW, FOWMAT_CNV16, 0);
	WEG_UPDATE(FOWMAT_CONTWOW, CNVC_BYPASS_MSB_AWIGN, 0);
	WEG_UPDATE(FOWMAT_CONTWOW, CWAMP_POSITIVE, 0);
	WEG_UPDATE(FOWMAT_CONTWOW, CWAMP_POSITIVE_C, 0);

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
		is_2bit = 1;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_YCbCw:
		fowce_disabwe_cuwsow = fawse;
		pixew_fowmat = 65;
		cowow_space = COWOW_SPACE_YCBCW709;
		sewect = DCN2_ICSC_SEWECT_ICSC_A;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_YCwCb:
		fowce_disabwe_cuwsow = twue;
		pixew_fowmat = 64;
		cowow_space = COWOW_SPACE_YCBCW709;
		sewect = DCN2_ICSC_SEWECT_ICSC_A;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_10bpc_YCbCw:
		fowce_disabwe_cuwsow = twue;
		pixew_fowmat = 67;
		cowow_space = COWOW_SPACE_YCBCW709;
		sewect = DCN2_ICSC_SEWECT_ICSC_A;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_10bpc_YCwCb:
		fowce_disabwe_cuwsow = twue;
		pixew_fowmat = 66;
		cowow_space = COWOW_SPACE_YCBCW709;
		sewect = DCN2_ICSC_SEWECT_ICSC_A;
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
	case SUWFACE_PIXEW_FOWMAT_VIDEO_AYCwCb8888:
		pixew_fowmat = 12;
		cowow_space = COWOW_SPACE_YCBCW709;
		sewect = DCN2_ICSC_SEWECT_ICSC_A;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_WGB111110_FIX:
		pixew_fowmat = 112;
		awpha_en = 0;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_BGW101111_FIX:
		pixew_fowmat = 113;
		awpha_en = 0;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_VIDEO_ACwYCb2101010:
		pixew_fowmat = 114;
		cowow_space = COWOW_SPACE_YCBCW709;
		sewect = DCN2_ICSC_SEWECT_ICSC_A;
		is_2bit = 1;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_VIDEO_CwYCbA1010102:
		pixew_fowmat = 115;
		cowow_space = COWOW_SPACE_YCBCW709;
		sewect = DCN2_ICSC_SEWECT_ICSC_A;
		is_2bit = 1;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_WGB111110_FWOAT:
		pixew_fowmat = 118;
		awpha_en = 0;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_BGW101111_FWOAT:
		pixew_fowmat = 119;
		awpha_en = 0;
		bweak;
	defauwt:
		bweak;
	}

	/* Set defauwt cowow space based on fowmat if none is given. */
	cowow_space = input_cowow_space ? input_cowow_space : cowow_space;

	if (is_2bit == 1 && awpha_2bit_wut != NUWW) {
		WEG_UPDATE(AWPHA_2BIT_WUT, AWPHA_2BIT_WUT0, awpha_2bit_wut->wut0);
		WEG_UPDATE(AWPHA_2BIT_WUT, AWPHA_2BIT_WUT1, awpha_2bit_wut->wut1);
		WEG_UPDATE(AWPHA_2BIT_WUT, AWPHA_2BIT_WUT2, awpha_2bit_wut->wut2);
		WEG_UPDATE(AWPHA_2BIT_WUT, AWPHA_2BIT_WUT3, awpha_2bit_wut->wut3);
	}

	WEG_SET(CNVC_SUWFACE_PIXEW_FOWMAT, 0,
			CNVC_SUWFACE_PIXEW_FOWMAT, pixew_fowmat);
	WEG_UPDATE(FOWMAT_CONTWOW, FOWMAT_CONTWOW__AWPHA_EN, awpha_en);

	// if input adjustments exist, pwogwam icsc with those vawues
	if (input_csc_cowow_matwix.enabwe_adjustment
				== twue) {
		fow (i = 0; i < 12; i++)
			tbw_entwy.wegvaw[i] = input_csc_cowow_matwix.matwix[i];

		tbw_entwy.cowow_space = input_cowow_space;

		if (cowow_space >= COWOW_SPACE_YCBCW601)
			sewect = DCN2_ICSC_SEWECT_ICSC_A;
		ewse
			sewect = DCN2_ICSC_SEWECT_BYPASS;

		dpp2_pwogwam_input_csc(dpp_base, cowow_space, sewect, &tbw_entwy);
	} ewse
	dpp2_pwogwam_input_csc(dpp_base, cowow_space, sewect, NUWW);

	if (fowce_disabwe_cuwsow) {
		WEG_UPDATE(CUWSOW_CONTWOW,
				CUWSOW_ENABWE, 0);
		WEG_UPDATE(CUWSOW0_CONTWOW,
				CUW0_ENABWE, 0);

	}
	dpp2_powew_on_obuf(dpp_base, twue);

}

/*compute the maximum numbew of wines that we can fit in the wine buffew*/
void dscw2_cawc_wb_num_pawtitions(
		const stwuct scawew_data *scw_data,
		enum wb_memowy_config wb_config,
		int *num_pawt_y,
		int *num_pawt_c)
{
	int memowy_wine_size_y, memowy_wine_size_c, memowy_wine_size_a,
	wb_memowy_size, wb_memowy_size_c, wb_memowy_size_a, num_pawtitions_a;

	int wine_size = scw_data->viewpowt.width < scw_data->wecout.width ?
			scw_data->viewpowt.width : scw_data->wecout.width;
	int wine_size_c = scw_data->viewpowt_c.width < scw_data->wecout.width ?
			scw_data->viewpowt_c.width : scw_data->wecout.width;

	if (wine_size == 0)
		wine_size = 1;

	if (wine_size_c == 0)
		wine_size_c = 1;

	memowy_wine_size_y = (wine_size + 5) / 6; /* +5 to ceiw */
	memowy_wine_size_c = (wine_size_c + 5) / 6; /* +5 to ceiw */
	memowy_wine_size_a = (wine_size + 5) / 6; /* +5 to ceiw */

	if (wb_config == WB_MEMOWY_CONFIG_1) {
		wb_memowy_size = 970;
		wb_memowy_size_c = 970;
		wb_memowy_size_a = 970;
	} ewse if (wb_config == WB_MEMOWY_CONFIG_2) {
		wb_memowy_size = 1290;
		wb_memowy_size_c = 1290;
		wb_memowy_size_a = 1290;
	} ewse if (wb_config == WB_MEMOWY_CONFIG_3) {
		/* 420 mode: using 3wd mem fwom Y, Cw and Cb */
		wb_memowy_size = 970 + 1290 + 484 + 484 + 484;
		wb_memowy_size_c = 970 + 1290;
		wb_memowy_size_a = 970 + 1290 + 484;
	} ewse {
		wb_memowy_size = 970 + 1290 + 484;
		wb_memowy_size_c = 970 + 1290 + 484;
		wb_memowy_size_a = 970 + 1290 + 484;
	}
	*num_pawt_y = wb_memowy_size / memowy_wine_size_y;
	*num_pawt_c = wb_memowy_size_c / memowy_wine_size_c;
	num_pawtitions_a = wb_memowy_size_a / memowy_wine_size_a;

	if (scw_data->wb_pawams.awpha_en
			&& (num_pawtitions_a < *num_pawt_y))
		*num_pawt_y = num_pawtitions_a;

	if (*num_pawt_y > 64)
		*num_pawt_y = 64;
	if (*num_pawt_c > 64)
		*num_pawt_c = 64;
}

void dpp2_cnv_set_awpha_keyew(
		stwuct dpp *dpp_base,
		stwuct cnv_cowow_keyew_pawams *cowow_keyew)
{
	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	WEG_UPDATE(COWOW_KEYEW_CONTWOW, COWOW_KEYEW_EN, cowow_keyew->cowow_keyew_en);

	WEG_UPDATE(COWOW_KEYEW_CONTWOW, COWOW_KEYEW_MODE, cowow_keyew->cowow_keyew_mode);

	WEG_UPDATE(COWOW_KEYEW_AWPHA, COWOW_KEYEW_AWPHA_WOW, cowow_keyew->cowow_keyew_awpha_wow);
	WEG_UPDATE(COWOW_KEYEW_AWPHA, COWOW_KEYEW_AWPHA_HIGH, cowow_keyew->cowow_keyew_awpha_high);

	WEG_UPDATE(COWOW_KEYEW_WED, COWOW_KEYEW_WED_WOW, cowow_keyew->cowow_keyew_wed_wow);
	WEG_UPDATE(COWOW_KEYEW_WED, COWOW_KEYEW_WED_HIGH, cowow_keyew->cowow_keyew_wed_high);

	WEG_UPDATE(COWOW_KEYEW_GWEEN, COWOW_KEYEW_GWEEN_WOW, cowow_keyew->cowow_keyew_gween_wow);
	WEG_UPDATE(COWOW_KEYEW_GWEEN, COWOW_KEYEW_GWEEN_HIGH, cowow_keyew->cowow_keyew_gween_high);

	WEG_UPDATE(COWOW_KEYEW_BWUE, COWOW_KEYEW_BWUE_WOW, cowow_keyew->cowow_keyew_bwue_wow);
	WEG_UPDATE(COWOW_KEYEW_BWUE, COWOW_KEYEW_BWUE_HIGH, cowow_keyew->cowow_keyew_bwue_high);
}

void dpp2_set_cuwsow_attwibutes(
		stwuct dpp *dpp_base,
		stwuct dc_cuwsow_attwibutes *cuwsow_attwibutes)
{
	enum dc_cuwsow_cowow_fowmat cowow_fowmat = cuwsow_attwibutes->cowow_fowmat;
	stwuct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);
	int cuw_wom_en = 0;

	if (cowow_fowmat == CUWSOW_MODE_COWOW_PWE_MUWTIPWIED_AWPHA ||
		cowow_fowmat == CUWSOW_MODE_COWOW_UN_PWE_MUWTIPWIED_AWPHA) {
		if (cuwsow_attwibutes->attwibute_fwags.bits.ENABWE_CUWSOW_DEGAMMA) {
			cuw_wom_en = 1;
		}
	}

	WEG_UPDATE_3(CUWSOW0_CONTWOW,
			CUW0_MODE, cowow_fowmat,
			CUW0_EXPANSION_MODE, 0,
			CUW0_WOM_EN, cuw_wom_en);

	if (cowow_fowmat == CUWSOW_MODE_MONO) {
		/* todo: cwawify what to pwogwam these to */
		WEG_UPDATE(CUWSOW0_COWOW0,
				CUW0_COWOW0, 0x00000000);
		WEG_UPDATE(CUWSOW0_COWOW1,
				CUW0_COWOW1, 0xFFFFFFFF);
	}
}

void oppn20_dummy_pwogwam_wegamma_pww(
		stwuct dpp *dpp,
		const stwuct pww_pawams *pawams,
		enum opp_wegamma mode)
{}

static stwuct dpp_funcs dcn20_dpp_funcs = {
	.dpp_wead_state = dpp20_wead_state,
	.dpp_weset = dpp_weset,
	.dpp_set_scawew = dpp1_dscw_set_scawew_manuaw_scawe,
	.dpp_get_optimaw_numbew_of_taps = dpp1_get_optimaw_numbew_of_taps,
	.dpp_set_gamut_wemap = dpp2_cm_set_gamut_wemap,
	.dpp_set_csc_adjustment = NUWW,
	.dpp_set_csc_defauwt = NUWW,
	.dpp_pwogwam_wegamma_pww = oppn20_dummy_pwogwam_wegamma_pww,
	.dpp_set_degamma		= dpp2_set_degamma,
	.dpp_pwogwam_input_wut		= dpp2_dummy_pwogwam_input_wut,
	.dpp_fuww_bypass		= dpp1_fuww_bypass,
	.dpp_setup			= dpp2_cnv_setup,
	.dpp_pwogwam_degamma_pww	= dpp2_set_degamma_pww,
	.dpp_pwogwam_bwnd_wut = dpp20_pwogwam_bwnd_wut,
	.dpp_pwogwam_shapew_wut = dpp20_pwogwam_shapew,
	.dpp_pwogwam_3dwut = dpp20_pwogwam_3dwut,
	.dpp_pwogwam_bias_and_scawe = NUWW,
	.dpp_cnv_set_awpha_keyew = dpp2_cnv_set_awpha_keyew,
	.set_cuwsow_attwibutes = dpp2_set_cuwsow_attwibutes,
	.set_cuwsow_position = dpp1_set_cuwsow_position,
	.set_optionaw_cuwsow_attwibutes = dpp1_cnv_set_optionaw_cuwsow_attwibutes,
	.dpp_dppcwk_contwow = dpp1_dppcwk_contwow,
	.dpp_set_hdw_muwtipwiew = dpp2_set_hdw_muwtipwiew,
};

static stwuct dpp_caps dcn20_dpp_cap = {
	.dscw_data_pwoc_fowmat = DSCW_DATA_PWCESSING_FWOAT_FOWMAT,
	.dscw_cawc_wb_num_pawtitions = dscw2_cawc_wb_num_pawtitions,
};

boow dpp2_constwuct(
	stwuct dcn20_dpp *dpp,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dcn2_dpp_wegistews *tf_wegs,
	const stwuct dcn2_dpp_shift *tf_shift,
	const stwuct dcn2_dpp_mask *tf_mask)
{
	dpp->base.ctx = ctx;

	dpp->base.inst = inst;
	dpp->base.funcs = &dcn20_dpp_funcs;
	dpp->base.caps = &dcn20_dpp_cap;

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

	wetuwn twue;
}

