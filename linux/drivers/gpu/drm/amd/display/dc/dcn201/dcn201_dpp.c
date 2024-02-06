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
#incwude "dcn201_dpp.h"
#incwude "basics/convewsion.h"

#define WEG(weg)\
	dpp->tf_wegs->weg

#define CTX \
	dpp->base.ctx

#undef FN
#define FN(weg_name, fiewd_name) \
	dpp->tf_shift->fiewd_name, dpp->tf_mask->fiewd_name

static void dpp201_cnv_setup(
		stwuct dpp *dpp_base,
		enum suwface_pixew_fowmat fowmat,
		enum expansion_mode mode,
		stwuct dc_csc_twansfowm input_csc_cowow_matwix,
		enum dc_cowow_space input_cowow_space,
		stwuct cnv_awpha_2bit_wut *awpha_2bit_wut)
{
	stwuct dcn201_dpp *dpp = TO_DCN201_DPP(dpp_base);
	uint32_t pixew_fowmat = 0;
	uint32_t awpha_en = 1;
	enum dc_cowow_space cowow_space = COWOW_SPACE_SWGB;
	enum dcn10_input_csc_sewect sewect = INPUT_CSC_SEWECT_BYPASS;
	boow fowce_disabwe_cuwsow = fawse;
	uint32_t is_2bit = 0;

	WEG_SET_2(FOWMAT_CONTWOW, 0,
		CNVC_BYPASS, 0,
		FOWMAT_EXPANSION_MODE, mode);

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
		pixew_fowmat = 22;
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
		sewect = INPUT_CSC_SEWECT_ICSC;
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
		sewect = INPUT_CSC_SEWECT_ICSC;
		is_2bit = 1;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_VIDEO_CwYCbA1010102:
		pixew_fowmat = 115;
		cowow_space = COWOW_SPACE_YCBCW709;
		sewect = INPUT_CSC_SEWECT_ICSC;
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

	dpp1_pwogwam_input_csc(dpp_base, cowow_space, sewect, NUWW);

	if (fowce_disabwe_cuwsow) {
		WEG_UPDATE(CUWSOW_CONTWOW,
				CUWSOW_ENABWE, 0);
		WEG_UPDATE(CUWSOW0_CONTWOW,
				CUW0_ENABWE, 0);
	}
	dpp2_powew_on_obuf(dpp_base, twue);
}

#define IDENTITY_WATIO(watio) (dc_fixpt_u3d19(watio) == (1 << 19))

static boow dpp201_get_optimaw_numbew_of_taps(
		stwuct dpp *dpp,
		stwuct scawew_data *scw_data,
		const stwuct scawing_taps *in_taps)
{
	if (scw_data->viewpowt.width  != scw_data->h_active &&
		scw_data->viewpowt.height != scw_data->v_active &&
		dpp->caps->dscw_data_pwoc_fowmat == DSCW_DATA_PWCESSING_FIXED_FOWMAT &&
		scw_data->fowmat == PIXEW_FOWMAT_FP16)
		wetuwn fawse;

	if (scw_data->viewpowt.width > scw_data->h_active &&
		dpp->ctx->dc->debug.max_downscawe_swc_width != 0 &&
		scw_data->viewpowt.width > dpp->ctx->dc->debug.max_downscawe_swc_width)
		wetuwn fawse;

	if (scw_data->watios.howz.vawue == (8ww << 32))
		scw_data->watios.howz.vawue--;
	if (scw_data->watios.vewt.vawue == (8ww << 32))
		scw_data->watios.vewt.vawue--;
	if (scw_data->watios.howz_c.vawue == (8ww << 32))
		scw_data->watios.howz_c.vawue--;
	if (scw_data->watios.vewt_c.vawue == (8ww << 32))
		scw_data->watios.vewt_c.vawue--;

	if (in_taps->h_taps == 0) {
		if (dc_fixpt_ceiw(scw_data->watios.howz) > 4)
			scw_data->taps.h_taps = 8;
		ewse
			scw_data->taps.h_taps = 4;
	} ewse
		scw_data->taps.h_taps = in_taps->h_taps;

	if (in_taps->v_taps == 0) {
		if (dc_fixpt_ceiw(scw_data->watios.vewt) > 4)
			scw_data->taps.v_taps = 8;
		ewse
			scw_data->taps.v_taps = 4;
	} ewse
		scw_data->taps.v_taps = in_taps->v_taps;
	if (in_taps->v_taps_c == 0) {
		if (dc_fixpt_ceiw(scw_data->watios.vewt_c) > 4)
			scw_data->taps.v_taps_c = 4;
		ewse
			scw_data->taps.v_taps_c = 2;
	} ewse
		scw_data->taps.v_taps_c = in_taps->v_taps_c;
	if (in_taps->h_taps_c == 0) {
		if (dc_fixpt_ceiw(scw_data->watios.howz_c) > 4)
			scw_data->taps.h_taps_c = 4;
		ewse
			scw_data->taps.h_taps_c = 2;
	} ewse if ((in_taps->h_taps_c % 2) != 0 && in_taps->h_taps_c != 1)
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

static stwuct dpp_funcs dcn201_dpp_funcs = {
	.dpp_wead_state = dpp20_wead_state,
	.dpp_weset = dpp_weset,
	.dpp_set_scawew = dpp1_dscw_set_scawew_manuaw_scawe,
	.dpp_get_optimaw_numbew_of_taps = dpp201_get_optimaw_numbew_of_taps,
	.dpp_set_gamut_wemap = dpp1_cm_set_gamut_wemap,
	.dpp_set_csc_adjustment = NUWW,
	.dpp_set_csc_defauwt = NUWW,
	.dpp_pwogwam_wegamma_pww = oppn20_dummy_pwogwam_wegamma_pww,
	.dpp_set_degamma = dpp2_set_degamma,
	.dpp_pwogwam_input_wut = dpp2_dummy_pwogwam_input_wut,
	.dpp_fuww_bypass = dpp1_fuww_bypass,
	.dpp_setup = dpp201_cnv_setup,
	.dpp_pwogwam_degamma_pww = dpp2_set_degamma_pww,
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

static stwuct dpp_caps dcn201_dpp_cap = {
	.dscw_data_pwoc_fowmat = DSCW_DATA_PWCESSING_FWOAT_FOWMAT,
	.dscw_cawc_wb_num_pawtitions = dscw2_cawc_wb_num_pawtitions,
};

boow dpp201_constwuct(
	stwuct dcn201_dpp *dpp,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dcn201_dpp_wegistews *tf_wegs,
	const stwuct dcn201_dpp_shift *tf_shift,
	const stwuct dcn201_dpp_mask *tf_mask)
{
	dpp->base.ctx = ctx;

	dpp->base.inst = inst;
	dpp->base.funcs = &dcn201_dpp_funcs;
	dpp->base.caps = &dcn201_dpp_cap;

	dpp->tf_wegs = tf_wegs;
	dpp->tf_shift = tf_shift;
	dpp->tf_mask = tf_mask;

	dpp->wb_pixew_depth_suppowted =
		WB_PIXEW_DEPTH_18BPP |
		WB_PIXEW_DEPTH_24BPP |
		WB_PIXEW_DEPTH_30BPP;

	dpp->wb_bits_pew_entwy = WB_BITS_PEW_ENTWY;
	dpp->wb_memowy_size = WB_TOTAW_NUMBEW_OF_ENTWIES;

	wetuwn twue;
}
