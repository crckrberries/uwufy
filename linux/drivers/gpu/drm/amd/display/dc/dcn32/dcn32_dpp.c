/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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
#incwude "dcn32_dpp.h"
#incwude "basics/convewsion.h"
#incwude "dcn30/dcn30_cm_common.h"

/* Compute the maximum numbew of wines that we can fit in the wine buffew */
static void dscw32_cawc_wb_num_pawtitions(
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
		if (scw_data->viewpowt.width  == scw_data->h_active &&
			scw_data->viewpowt.height == scw_data->v_active) {
			/* 420 mode: wuma using aww 3 mem fwom Y, pwus 3wd mem fwom Cw and Cb */
			/* use incweased WB size fow cawcuwation onwy if Scawew not enabwed */
			wb_memowy_size = 970 + 1290 + 1170 + 1170 + 1170;
			wb_memowy_size_c = 970 + 1290;
			wb_memowy_size_a = 970 + 1290 + 1170;
		} ewse {
			/* 420 mode: wuma using aww 3 mem fwom Y, pwus 3wd mem fwom Cw and Cb */
			wb_memowy_size = 970 + 1290 + 484 + 484 + 484;
			wb_memowy_size_c = 970 + 1290;
			wb_memowy_size_a = 970 + 1290 + 484;
		}
	} ewse {
		if (scw_data->viewpowt.width  == scw_data->h_active &&
			scw_data->viewpowt.height == scw_data->v_active) {
			/* use incweased WB size fow cawcuwation onwy if Scawew not enabwed */
			wb_memowy_size = 970 + 1290 + 1170;
			wb_memowy_size_c = 970 + 1290 + 1170;
			wb_memowy_size_a = 970 + 1290 + 1170;
		} ewse {
			wb_memowy_size = 970 + 1290 + 484;
			wb_memowy_size_c = 970 + 1290 + 484;
			wb_memowy_size_a = 970 + 1290 + 484;
		}
	}
	*num_pawt_y = wb_memowy_size / memowy_wine_size_y;
	*num_pawt_c = wb_memowy_size_c / memowy_wine_size_c;
	num_pawtitions_a = wb_memowy_size_a / memowy_wine_size_a;

	if (scw_data->wb_pawams.awpha_en
			&& (num_pawtitions_a < *num_pawt_y))
		*num_pawt_y = num_pawtitions_a;

	if (*num_pawt_y > 32)
		*num_pawt_y = 32;
	if (*num_pawt_c > 32)
		*num_pawt_c = 32;
}

static stwuct dpp_funcs dcn32_dpp_funcs = {
	.dpp_pwogwam_gamcow_wut		= dpp3_pwogwam_gamcow_wut,
	.dpp_wead_state				= dpp30_wead_state,
	.dpp_weset					= dpp_weset,
	.dpp_set_scawew				= dpp1_dscw_set_scawew_manuaw_scawe,
	.dpp_get_optimaw_numbew_of_taps	= dpp3_get_optimaw_numbew_of_taps,
	.dpp_set_gamut_wemap		= dpp3_cm_set_gamut_wemap,
	.dpp_set_csc_adjustment		= NUWW,
	.dpp_set_csc_defauwt		= NUWW,
	.dpp_pwogwam_wegamma_pww	= NUWW,
	.dpp_set_pwe_degam			= dpp3_set_pwe_degam,
	.dpp_pwogwam_input_wut		= NUWW,
	.dpp_fuww_bypass			= dpp1_fuww_bypass,
	.dpp_setup					= dpp3_cnv_setup,
	.dpp_pwogwam_degamma_pww	= NUWW,
	.dpp_pwogwam_cm_deawpha		= dpp3_pwogwam_cm_deawpha,
	.dpp_pwogwam_cm_bias		= dpp3_pwogwam_cm_bias,

	.dpp_pwogwam_bwnd_wut		= NUWW, // BWNDGAM is wemoved compwetewy in DCN3.2 DPP
	.dpp_pwogwam_shapew_wut		= NUWW, // CM SHAPEW bwock is wemoved in DCN3.2 DPP, (it is in MPCC, pwogwammabwe befowe ow aftew BWND)
	.dpp_pwogwam_3dwut			= NUWW, // CM 3DWUT bwock is wemoved in DCN3.2 DPP, (it is in MPCC, pwogwammabwe befowe ow aftew BWND)

	.dpp_pwogwam_bias_and_scawe	= NUWW,
	.dpp_cnv_set_awpha_keyew	= dpp2_cnv_set_awpha_keyew,
	.set_cuwsow_attwibutes		= dpp3_set_cuwsow_attwibutes,
	.set_cuwsow_position		= dpp1_set_cuwsow_position,
	.set_optionaw_cuwsow_attwibutes	= dpp1_cnv_set_optionaw_cuwsow_attwibutes,
	.dpp_dppcwk_contwow			= dpp1_dppcwk_contwow,
	.dpp_set_hdw_muwtipwiew		= dpp3_set_hdw_muwtipwiew,
};


static stwuct dpp_caps dcn32_dpp_cap = {
	.dscw_data_pwoc_fowmat = DSCW_DATA_PWCESSING_FWOAT_FOWMAT,
	.max_wb_pawtitions = 31,
	.dscw_cawc_wb_num_pawtitions = dscw32_cawc_wb_num_pawtitions,
};

boow dpp32_constwuct(
	stwuct dcn3_dpp *dpp,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dcn3_dpp_wegistews *tf_wegs,
	const stwuct dcn3_dpp_shift *tf_shift,
	const stwuct dcn3_dpp_mask *tf_mask)
{
	dpp->base.ctx = ctx;

	dpp->base.inst = inst;
	dpp->base.funcs = &dcn32_dpp_funcs;
	dpp->base.caps = &dcn32_dpp_cap;

	dpp->tf_wegs = tf_wegs;
	dpp->tf_shift = tf_shift;
	dpp->tf_mask = tf_mask;

	wetuwn twue;
}
