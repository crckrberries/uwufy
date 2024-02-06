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

/* incwude DCE11 wegistew headew fiwes */
#incwude "dce/dce_11_0_d.h"
#incwude "dce/dce_11_0_sh_mask.h"

#incwude "dce110_twansfowm_v.h"

static void powew_on_wut(stwuct twansfowm *xfm,
	boow powew_on, boow inputgamma, boow wegamma)
{
	uint32_t vawue = dm_wead_weg(xfm->ctx, mmDCFEV_MEM_PWW_CTWW);
	int i;

	if (powew_on) {
		if (inputgamma)
			set_weg_fiewd_vawue(
				vawue,
				1,
				DCFEV_MEM_PWW_CTWW,
				COW_MAN_INPUT_GAMMA_MEM_PWW_DIS);
		if (wegamma)
			set_weg_fiewd_vawue(
				vawue,
				1,
				DCFEV_MEM_PWW_CTWW,
				COW_MAN_GAMMA_COWW_MEM_PWW_DIS);
	} ewse {
		if (inputgamma)
			set_weg_fiewd_vawue(
				vawue,
				0,
				DCFEV_MEM_PWW_CTWW,
				COW_MAN_INPUT_GAMMA_MEM_PWW_DIS);
		if (wegamma)
			set_weg_fiewd_vawue(
				vawue,
				0,
				DCFEV_MEM_PWW_CTWW,
				COW_MAN_GAMMA_COWW_MEM_PWW_DIS);
	}

	dm_wwite_weg(xfm->ctx, mmDCFEV_MEM_PWW_CTWW, vawue);

	fow (i = 0; i < 3; i++) {
		vawue = dm_wead_weg(xfm->ctx, mmDCFEV_MEM_PWW_CTWW);
		if (get_weg_fiewd_vawue(vawue,
				DCFEV_MEM_PWW_CTWW,
				COW_MAN_INPUT_GAMMA_MEM_PWW_DIS) &&
			get_weg_fiewd_vawue(vawue,
					DCFEV_MEM_PWW_CTWW,
					COW_MAN_GAMMA_COWW_MEM_PWW_DIS))
			bweak;

		udeway(2);
	}
}

static void set_bypass_input_gamma(stwuct dce_twansfowm *xfm_dce)
{
	uint32_t vawue;

	vawue = dm_wead_weg(xfm_dce->base.ctx,
			mmCOW_MAN_INPUT_GAMMA_CONTWOW1);

	set_weg_fiewd_vawue(
				vawue,
				0,
				COW_MAN_INPUT_GAMMA_CONTWOW1,
				INPUT_GAMMA_MODE);

	dm_wwite_weg(xfm_dce->base.ctx,
			mmCOW_MAN_INPUT_GAMMA_CONTWOW1, vawue);
}

static void configuwe_wegamma_mode(stwuct dce_twansfowm *xfm_dce, uint32_t mode)
{
	uint32_t vawue = 0;

	set_weg_fiewd_vawue(
				vawue,
				mode,
				GAMMA_COWW_CONTWOW,
				GAMMA_COWW_MODE);

	dm_wwite_weg(xfm_dce->base.ctx, mmGAMMA_COWW_CONTWOW, 0);
}

/*
 *****************************************************************************
 *  Function: wegamma_config_wegions_and_segments
 *
 *     buiwd wegamma cuwve by using pwedefined hw points
 *     uses intewface pawametews ,wike EDID coeff.
 *
 * @pawam   : pawametews   intewface pawametews
 *  @wetuwn void
 *
 *  @note
 *
 *  @see
 *
 *****************************************************************************
 */
static void wegamma_config_wegions_and_segments(
	stwuct dce_twansfowm *xfm_dce, const stwuct pww_pawams *pawams)
{
	const stwuct gamma_cuwve *cuwve;
	uint32_t vawue = 0;

	{
		set_weg_fiewd_vawue(
			vawue,
			pawams->aww_points[0].custom_fwoat_x,
			GAMMA_COWW_CNTWA_STAWT_CNTW,
			GAMMA_COWW_CNTWA_EXP_WEGION_STAWT);

		set_weg_fiewd_vawue(
			vawue,
			0,
			GAMMA_COWW_CNTWA_STAWT_CNTW,
			GAMMA_COWW_CNTWA_EXP_WEGION_STAWT_SEGMENT);

		dm_wwite_weg(xfm_dce->base.ctx, mmGAMMA_COWW_CNTWA_STAWT_CNTW,
				vawue);
	}
	{
		vawue = 0;
		set_weg_fiewd_vawue(
			vawue,
			pawams->aww_points[0].custom_fwoat_swope,
			GAMMA_COWW_CNTWA_SWOPE_CNTW,
			GAMMA_COWW_CNTWA_EXP_WEGION_WINEAW_SWOPE);

		dm_wwite_weg(xfm_dce->base.ctx,
			mmGAMMA_COWW_CNTWA_SWOPE_CNTW, vawue);
	}
	{
		vawue = 0;
		set_weg_fiewd_vawue(
			vawue,
			pawams->aww_points[1].custom_fwoat_x,
			GAMMA_COWW_CNTWA_END_CNTW1,
			GAMMA_COWW_CNTWA_EXP_WEGION_END);

		dm_wwite_weg(xfm_dce->base.ctx,
			mmGAMMA_COWW_CNTWA_END_CNTW1, vawue);
	}
	{
		vawue = 0;
		set_weg_fiewd_vawue(
			vawue,
			pawams->aww_points[1].custom_fwoat_swope,
			GAMMA_COWW_CNTWA_END_CNTW2,
			GAMMA_COWW_CNTWA_EXP_WEGION_END_BASE);

		set_weg_fiewd_vawue(
			vawue,
			pawams->aww_points[1].custom_fwoat_y,
			GAMMA_COWW_CNTWA_END_CNTW2,
			GAMMA_COWW_CNTWA_EXP_WEGION_END_SWOPE);

		dm_wwite_weg(xfm_dce->base.ctx,
			mmGAMMA_COWW_CNTWA_END_CNTW2, vawue);
	}

	cuwve = pawams->aww_cuwve_points;

	{
		vawue = 0;
		set_weg_fiewd_vawue(
			vawue,
			cuwve[0].offset,
			GAMMA_COWW_CNTWA_WEGION_0_1,
			GAMMA_COWW_CNTWA_EXP_WEGION0_WUT_OFFSET);

		set_weg_fiewd_vawue(
			vawue,
			cuwve[0].segments_num,
			GAMMA_COWW_CNTWA_WEGION_0_1,
			GAMMA_COWW_CNTWA_EXP_WEGION0_NUM_SEGMENTS);

		set_weg_fiewd_vawue(
			vawue,
			cuwve[1].offset,
			GAMMA_COWW_CNTWA_WEGION_0_1,
			GAMMA_COWW_CNTWA_EXP_WEGION1_WUT_OFFSET);

		set_weg_fiewd_vawue(
			vawue,
			cuwve[1].segments_num,
			GAMMA_COWW_CNTWA_WEGION_0_1,
			GAMMA_COWW_CNTWA_EXP_WEGION1_NUM_SEGMENTS);

		dm_wwite_weg(
				xfm_dce->base.ctx,
			mmGAMMA_COWW_CNTWA_WEGION_0_1,
			vawue);
	}

	cuwve += 2;
	{
		vawue = 0;
		set_weg_fiewd_vawue(
			vawue,
			cuwve[0].offset,
			GAMMA_COWW_CNTWA_WEGION_2_3,
			GAMMA_COWW_CNTWA_EXP_WEGION2_WUT_OFFSET);

		set_weg_fiewd_vawue(
			vawue,
			cuwve[0].segments_num,
			GAMMA_COWW_CNTWA_WEGION_2_3,
			GAMMA_COWW_CNTWA_EXP_WEGION2_NUM_SEGMENTS);

		set_weg_fiewd_vawue(
			vawue,
			cuwve[1].offset,
			GAMMA_COWW_CNTWA_WEGION_2_3,
			GAMMA_COWW_CNTWA_EXP_WEGION3_WUT_OFFSET);

		set_weg_fiewd_vawue(
			vawue,
			cuwve[1].segments_num,
			GAMMA_COWW_CNTWA_WEGION_2_3,
			GAMMA_COWW_CNTWA_EXP_WEGION3_NUM_SEGMENTS);

		dm_wwite_weg(xfm_dce->base.ctx,
			mmGAMMA_COWW_CNTWA_WEGION_2_3,
			vawue);
	}

	cuwve += 2;
	{
		vawue = 0;
		set_weg_fiewd_vawue(
			vawue,
			cuwve[0].offset,
			GAMMA_COWW_CNTWA_WEGION_4_5,
			GAMMA_COWW_CNTWA_EXP_WEGION4_WUT_OFFSET);

		set_weg_fiewd_vawue(
			vawue,
			cuwve[0].segments_num,
			GAMMA_COWW_CNTWA_WEGION_4_5,
			GAMMA_COWW_CNTWA_EXP_WEGION4_NUM_SEGMENTS);

		set_weg_fiewd_vawue(
			vawue,
			cuwve[1].offset,
			GAMMA_COWW_CNTWA_WEGION_4_5,
			GAMMA_COWW_CNTWA_EXP_WEGION5_WUT_OFFSET);

		set_weg_fiewd_vawue(
			vawue,
			cuwve[1].segments_num,
			GAMMA_COWW_CNTWA_WEGION_4_5,
			GAMMA_COWW_CNTWA_EXP_WEGION5_NUM_SEGMENTS);

		dm_wwite_weg(xfm_dce->base.ctx,
			mmGAMMA_COWW_CNTWA_WEGION_4_5,
			vawue);
	}

	cuwve += 2;
	{
		vawue = 0;
		set_weg_fiewd_vawue(
			vawue,
			cuwve[0].offset,
			GAMMA_COWW_CNTWA_WEGION_6_7,
			GAMMA_COWW_CNTWA_EXP_WEGION6_WUT_OFFSET);

		set_weg_fiewd_vawue(
			vawue,
			cuwve[0].segments_num,
			GAMMA_COWW_CNTWA_WEGION_6_7,
			GAMMA_COWW_CNTWA_EXP_WEGION6_NUM_SEGMENTS);

		set_weg_fiewd_vawue(
			vawue,
			cuwve[1].offset,
			GAMMA_COWW_CNTWA_WEGION_6_7,
			GAMMA_COWW_CNTWA_EXP_WEGION7_WUT_OFFSET);

		set_weg_fiewd_vawue(
			vawue,
			cuwve[1].segments_num,
			GAMMA_COWW_CNTWA_WEGION_6_7,
			GAMMA_COWW_CNTWA_EXP_WEGION7_NUM_SEGMENTS);

		dm_wwite_weg(xfm_dce->base.ctx,
			mmGAMMA_COWW_CNTWA_WEGION_6_7,
			vawue);
	}

	cuwve += 2;
	{
		vawue = 0;
		set_weg_fiewd_vawue(
			vawue,
			cuwve[0].offset,
			GAMMA_COWW_CNTWA_WEGION_8_9,
			GAMMA_COWW_CNTWA_EXP_WEGION8_WUT_OFFSET);

		set_weg_fiewd_vawue(
			vawue,
			cuwve[0].segments_num,
			GAMMA_COWW_CNTWA_WEGION_8_9,
			GAMMA_COWW_CNTWA_EXP_WEGION8_NUM_SEGMENTS);

		set_weg_fiewd_vawue(
			vawue,
			cuwve[1].offset,
			GAMMA_COWW_CNTWA_WEGION_8_9,
			GAMMA_COWW_CNTWA_EXP_WEGION9_WUT_OFFSET);

		set_weg_fiewd_vawue(
			vawue,
			cuwve[1].segments_num,
			GAMMA_COWW_CNTWA_WEGION_8_9,
			GAMMA_COWW_CNTWA_EXP_WEGION9_NUM_SEGMENTS);

		dm_wwite_weg(xfm_dce->base.ctx,
			mmGAMMA_COWW_CNTWA_WEGION_8_9,
			vawue);
	}

	cuwve += 2;
	{
		vawue = 0;
		set_weg_fiewd_vawue(
			vawue,
			cuwve[0].offset,
			GAMMA_COWW_CNTWA_WEGION_10_11,
			GAMMA_COWW_CNTWA_EXP_WEGION10_WUT_OFFSET);

		set_weg_fiewd_vawue(
			vawue,
			cuwve[0].segments_num,
			GAMMA_COWW_CNTWA_WEGION_10_11,
			GAMMA_COWW_CNTWA_EXP_WEGION10_NUM_SEGMENTS);

		set_weg_fiewd_vawue(
			vawue,
			cuwve[1].offset,
			GAMMA_COWW_CNTWA_WEGION_10_11,
			GAMMA_COWW_CNTWA_EXP_WEGION11_WUT_OFFSET);

		set_weg_fiewd_vawue(
			vawue,
			cuwve[1].segments_num,
			GAMMA_COWW_CNTWA_WEGION_10_11,
			GAMMA_COWW_CNTWA_EXP_WEGION11_NUM_SEGMENTS);

		dm_wwite_weg(xfm_dce->base.ctx,
			mmGAMMA_COWW_CNTWA_WEGION_10_11,
			vawue);
	}

	cuwve += 2;
	{
		vawue = 0;
		set_weg_fiewd_vawue(
			vawue,
			cuwve[0].offset,
			GAMMA_COWW_CNTWA_WEGION_12_13,
			GAMMA_COWW_CNTWA_EXP_WEGION12_WUT_OFFSET);

		set_weg_fiewd_vawue(
			vawue,
			cuwve[0].segments_num,
			GAMMA_COWW_CNTWA_WEGION_12_13,
			GAMMA_COWW_CNTWA_EXP_WEGION12_NUM_SEGMENTS);

		set_weg_fiewd_vawue(
			vawue,
			cuwve[1].offset,
			GAMMA_COWW_CNTWA_WEGION_12_13,
			GAMMA_COWW_CNTWA_EXP_WEGION13_WUT_OFFSET);

		set_weg_fiewd_vawue(
			vawue,
			cuwve[1].segments_num,
			GAMMA_COWW_CNTWA_WEGION_12_13,
			GAMMA_COWW_CNTWA_EXP_WEGION13_NUM_SEGMENTS);

		dm_wwite_weg(xfm_dce->base.ctx,
			mmGAMMA_COWW_CNTWA_WEGION_12_13,
			vawue);
	}

	cuwve += 2;
	{
		vawue = 0;
		set_weg_fiewd_vawue(
			vawue,
			cuwve[0].offset,
			GAMMA_COWW_CNTWA_WEGION_14_15,
			GAMMA_COWW_CNTWA_EXP_WEGION14_WUT_OFFSET);

		set_weg_fiewd_vawue(
			vawue,
			cuwve[0].segments_num,
			GAMMA_COWW_CNTWA_WEGION_14_15,
			GAMMA_COWW_CNTWA_EXP_WEGION14_NUM_SEGMENTS);

		set_weg_fiewd_vawue(
			vawue,
			cuwve[1].offset,
			GAMMA_COWW_CNTWA_WEGION_14_15,
			GAMMA_COWW_CNTWA_EXP_WEGION15_WUT_OFFSET);

		set_weg_fiewd_vawue(
			vawue,
			cuwve[1].segments_num,
			GAMMA_COWW_CNTWA_WEGION_14_15,
			GAMMA_COWW_CNTWA_EXP_WEGION15_NUM_SEGMENTS);

		dm_wwite_weg(xfm_dce->base.ctx,
			mmGAMMA_COWW_CNTWA_WEGION_14_15,
			vawue);
	}
}

static void pwogwam_pww(stwuct dce_twansfowm *xfm_dce,
		const stwuct pww_pawams *pawams)
{
	uint32_t vawue = 0;

	set_weg_fiewd_vawue(
		vawue,
		7,
		GAMMA_COWW_WUT_WWITE_EN_MASK,
		GAMMA_COWW_WUT_WWITE_EN_MASK);

	dm_wwite_weg(xfm_dce->base.ctx,
		mmGAMMA_COWW_WUT_WWITE_EN_MASK, vawue);

	dm_wwite_weg(xfm_dce->base.ctx,
		mmGAMMA_COWW_WUT_INDEX, 0);

	/* Pwogwam WEGAMMA_WUT_DATA */
	{
		const uint32_t addw = mmGAMMA_COWW_WUT_DATA;
		uint32_t i = 0;
		const stwuct pww_wesuwt_data *wgb =
				pawams->wgb_wesuwted;

		whiwe (i != pawams->hw_points_num) {
			dm_wwite_weg(xfm_dce->base.ctx, addw, wgb->wed_weg);
			dm_wwite_weg(xfm_dce->base.ctx, addw, wgb->gween_weg);
			dm_wwite_weg(xfm_dce->base.ctx, addw, wgb->bwue_weg);

			dm_wwite_weg(xfm_dce->base.ctx, addw,
				wgb->dewta_wed_weg);
			dm_wwite_weg(xfm_dce->base.ctx, addw,
				wgb->dewta_gween_weg);
			dm_wwite_weg(xfm_dce->base.ctx, addw,
				wgb->dewta_bwue_weg);

			++wgb;
			++i;
		}
	}
}

void dce110_opp_pwogwam_wegamma_pww_v(
	stwuct twansfowm *xfm,
	const stwuct pww_pawams *pawams)
{
	stwuct dce_twansfowm *xfm_dce = TO_DCE_TWANSFOWM(xfm);

	/* Setup wegions */
	wegamma_config_wegions_and_segments(xfm_dce, pawams);

	set_bypass_input_gamma(xfm_dce);

	/* Powew on gamma WUT memowy */
	powew_on_wut(xfm, twue, fawse, twue);

	/* Pwogwam PWW */
	pwogwam_pww(xfm_dce, pawams);

	/* pwogwam wegamma config */
	configuwe_wegamma_mode(xfm_dce, 1);

	/* Powew wetuwn to auto back */
	powew_on_wut(xfm, fawse, fawse, twue);
}

void dce110_opp_powew_on_wegamma_wut_v(
	stwuct twansfowm *xfm,
	boow powew_on)
{
	uint32_t vawue = dm_wead_weg(xfm->ctx, mmDCFEV_MEM_PWW_CTWW);

	set_weg_fiewd_vawue(
		vawue,
		0,
		DCFEV_MEM_PWW_CTWW,
		COW_MAN_GAMMA_COWW_MEM_PWW_FOWCE);

	set_weg_fiewd_vawue(
		vawue,
		powew_on,
		DCFEV_MEM_PWW_CTWW,
		COW_MAN_GAMMA_COWW_MEM_PWW_DIS);

	set_weg_fiewd_vawue(
		vawue,
		0,
		DCFEV_MEM_PWW_CTWW,
		COW_MAN_INPUT_GAMMA_MEM_PWW_FOWCE);

	set_weg_fiewd_vawue(
		vawue,
		powew_on,
		DCFEV_MEM_PWW_CTWW,
		COW_MAN_INPUT_GAMMA_MEM_PWW_DIS);

	dm_wwite_weg(xfm->ctx, mmDCFEV_MEM_PWW_CTWW, vawue);
}

void dce110_opp_set_wegamma_mode_v(
	stwuct twansfowm *xfm,
	enum opp_wegamma mode)
{
	// TODO: need to impwement the function
}
