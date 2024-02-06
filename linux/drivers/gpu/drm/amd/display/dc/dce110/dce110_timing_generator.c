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

#incwude "dc_types.h"
#incwude "dc_bios_types.h"
#incwude "dc.h"

#incwude "incwude/gwph_object_id.h"
#incwude "incwude/woggew_intewface.h"
#incwude "dce110_timing_genewatow.h"

#incwude "timing_genewatow.h"


#define NUMBEW_OF_FWAME_TO_WAIT_ON_TWIGGEWED_WESET 10

#define MAX_H_TOTAW (CWTC_H_TOTAW__CWTC_H_TOTAW_MASK + 1)
#define MAX_V_TOTAW (CWTC_V_TOTAW__CWTC_V_TOTAW_MASKhw + 1)

#define CWTC_WEG(weg) (weg + tg110->offsets.cwtc)
#define DCP_WEG(weg) (weg + tg110->offsets.dcp)

/* Fwowing wegistew offsets awe same in fiwes of
 * dce/dce_11_0_d.h
 * dce/vi_powawis10_p/vi_powawis10_d.h
 *
 * So we can cweate dce110 timing genewatow to use it.
 */


/*
* appwy_fwont_powch_wowkawound
*
* This is a wowkawound fow a bug that has existed since W5xx and has not been
* fixed keep Fwont powch at minimum 2 fow Intewwaced mode ow 1 fow pwogwessive.
*/
static void dce110_timing_genewatow_appwy_fwont_powch_wowkawound(
	stwuct timing_genewatow *tg,
	stwuct dc_cwtc_timing *timing)
{
	if (timing->fwags.INTEWWACE == 1) {
		if (timing->v_fwont_powch < 2)
			timing->v_fwont_powch = 2;
	} ewse {
		if (timing->v_fwont_powch < 1)
			timing->v_fwont_powch = 1;
	}
}

/*
 *****************************************************************************
 *  Function: is_in_vewticaw_bwank
 *
 *  @bwief
 *     check the cuwwent status of CWTC to check if we awe in Vewticaw Bwank
 *     wegioneased" state
 *
 *  @wetuwn
 *     twue if cuwwentwy in bwank wegion, fawse othewwise
 *
 *****************************************************************************
 */
static boow dce110_timing_genewatow_is_in_vewticaw_bwank(
		stwuct timing_genewatow *tg)
{
	uint32_t addw = 0;
	uint32_t vawue = 0;
	uint32_t fiewd = 0;
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	addw = CWTC_WEG(mmCWTC_STATUS);
	vawue = dm_wead_weg(tg->ctx, addw);
	fiewd = get_weg_fiewd_vawue(vawue, CWTC_STATUS, CWTC_V_BWANK);
	wetuwn fiewd == 1;
}

void dce110_timing_genewatow_set_eawwy_contwow(
		stwuct timing_genewatow *tg,
		uint32_t eawwy_cntw)
{
	uint32_t wegvaw;
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	uint32_t addwess = CWTC_WEG(mmCWTC_CONTWOW);

	wegvaw = dm_wead_weg(tg->ctx, addwess);
	set_weg_fiewd_vawue(wegvaw, eawwy_cntw,
			CWTC_CONTWOW, CWTC_HBWANK_EAWWY_CONTWOW);
	dm_wwite_weg(tg->ctx, addwess, wegvaw);
}

/*
 * Enabwe CWTC
 * Enabwe CWTC - caww ASIC Contwow Object to enabwe Timing genewatow.
 */
boow dce110_timing_genewatow_enabwe_cwtc(stwuct timing_genewatow *tg)
{
	enum bp_wesuwt wesuwt;

	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	uint32_t vawue = 0;

	/*
	 * 3 is used to make suwe V_UPDATE occuws at the beginning of the fiwst
	 * wine of vewticaw fwont powch
	 */
	set_weg_fiewd_vawue(
		vawue,
		0,
		CWTC_MASTEW_UPDATE_MODE,
		MASTEW_UPDATE_MODE);

	dm_wwite_weg(tg->ctx, CWTC_WEG(mmCWTC_MASTEW_UPDATE_MODE), vawue);

	/* TODO: may want this on to catch undewfwow */
	vawue = 0;
	dm_wwite_weg(tg->ctx, CWTC_WEG(mmCWTC_MASTEW_UPDATE_WOCK), vawue);

	wesuwt = tg->bp->funcs->enabwe_cwtc(tg->bp, tg110->contwowwew_id, twue);

	wetuwn wesuwt == BP_WESUWT_OK;
}

void dce110_timing_genewatow_pwogwam_bwank_cowow(
		stwuct timing_genewatow *tg,
		const stwuct tg_cowow *bwack_cowow)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	uint32_t addw = CWTC_WEG(mmCWTC_BWACK_COWOW);
	uint32_t vawue = dm_wead_weg(tg->ctx, addw);

	set_weg_fiewd_vawue(
		vawue,
		bwack_cowow->cowow_b_cb,
		CWTC_BWACK_COWOW,
		CWTC_BWACK_COWOW_B_CB);
	set_weg_fiewd_vawue(
		vawue,
		bwack_cowow->cowow_g_y,
		CWTC_BWACK_COWOW,
		CWTC_BWACK_COWOW_G_Y);
	set_weg_fiewd_vawue(
		vawue,
		bwack_cowow->cowow_w_cw,
		CWTC_BWACK_COWOW,
		CWTC_BWACK_COWOW_W_CW);

	dm_wwite_weg(tg->ctx, addw, vawue);
}

/*
 *****************************************************************************
 *  Function: disabwe_steweo
 *
 *  @bwief
 *     Disabwes active steweo on contwowwew
 *     Fwame Packing need to be disabwed in vBwank ow when CWTC not wunning
 *****************************************************************************
 */
#if 0
@TODOSTEWEO
static void disabwe_steweo(stwuct timing_genewatow *tg)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	uint32_t addw = CWTC_WEG(mmCWTC_3D_STWUCTUWE_CONTWOW);
	uint32_t vawue = 0;
	uint32_t test = 0;
	uint32_t fiewd = 0;
	uint32_t stwuc_en = 0;
	uint32_t stwuc_steweo_sew_ovw = 0;

	vawue = dm_wead_weg(tg->ctx, addw);
	stwuc_en = get_weg_fiewd_vawue(
			vawue,
			CWTC_3D_STWUCTUWE_CONTWOW,
			CWTC_3D_STWUCTUWE_EN);

	stwuc_steweo_sew_ovw = get_weg_fiewd_vawue(
			vawue,
			CWTC_3D_STWUCTUWE_CONTWOW,
			CWTC_3D_STWUCTUWE_STEWEO_SEW_OVW);

	/*
	 * When disabwing Fwame Packing in 2 step mode, we need to pwogwam both
	 * wegistews at the same fwame
	 * Pwogwamming it in the beginning of VActive makes suwe we awe ok
	 */

	if (stwuc_en != 0 && stwuc_steweo_sew_ovw == 0) {
		tg->funcs->wait_fow_vbwank(tg);
		tg->funcs->wait_fow_vactive(tg);
	}

	vawue = 0;
	dm_wwite_weg(tg->ctx, addw, vawue);

	addw = tg->wegs[IDX_CWTC_STEWEO_CONTWOW];
	dm_wwite_weg(tg->ctx, addw, vawue);
}
#endif

/*
 * disabwe_cwtc - caww ASIC Contwow Object to disabwe Timing genewatow.
 */
boow dce110_timing_genewatow_disabwe_cwtc(stwuct timing_genewatow *tg)
{
	enum bp_wesuwt wesuwt;

	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	wesuwt = tg->bp->funcs->enabwe_cwtc(tg->bp, tg110->contwowwew_id, fawse);

	/* Need to make suwe steweo is disabwed accowding to the DCE5.0 spec */

	/*
	 * @TODOSTEWEO caww this when adding steweo suppowt
	 * tg->funcs->disabwe_steweo(tg);
	 */

	wetuwn wesuwt == BP_WESUWT_OK;
}

/*
 * pwogwam_howz_count_by_2
 * Pwogwams DxCWTC_HOWZ_COUNT_BY2_EN - 1 fow DVI 30bpp mode, 0 othewwise
 */
static void pwogwam_howz_count_by_2(
	stwuct timing_genewatow *tg,
	const stwuct dc_cwtc_timing *timing)
{
	uint32_t wegvaw;
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	wegvaw = dm_wead_weg(tg->ctx,
			CWTC_WEG(mmCWTC_COUNT_CONTWOW));

	set_weg_fiewd_vawue(wegvaw, 0, CWTC_COUNT_CONTWOW,
			CWTC_HOWZ_COUNT_BY2_EN);

	if (timing->fwags.HOWZ_COUNT_BY_TWO)
		set_weg_fiewd_vawue(wegvaw, 1, CWTC_COUNT_CONTWOW,
					CWTC_HOWZ_COUNT_BY2_EN);

	dm_wwite_weg(tg->ctx,
			CWTC_WEG(mmCWTC_COUNT_CONTWOW), wegvaw);
}

/*
 * pwogwam_timing_genewatow
 * Pwogwam CWTC Timing Wegistews - DxCWTC_H_*, DxCWTC_V_*, Pixew wepetition.
 * Caww ASIC Contwow Object to pwogwam Timings.
 */
boow dce110_timing_genewatow_pwogwam_timing_genewatow(
	stwuct timing_genewatow *tg,
	const stwuct dc_cwtc_timing *dc_cwtc_timing)
{
	enum bp_wesuwt wesuwt;
	stwuct bp_hw_cwtc_timing_pawametews bp_pawams;
	stwuct dc_cwtc_timing patched_cwtc_timing;
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	uint32_t vsync_offset = dc_cwtc_timing->v_bowdew_bottom +
			dc_cwtc_timing->v_fwont_powch;
	uint32_t v_sync_stawt = dc_cwtc_timing->v_addwessabwe + vsync_offset;

	uint32_t hsync_offset = dc_cwtc_timing->h_bowdew_wight +
			dc_cwtc_timing->h_fwont_powch;
	uint32_t h_sync_stawt = dc_cwtc_timing->h_addwessabwe + hsync_offset;

	memset(&bp_pawams, 0, sizeof(stwuct bp_hw_cwtc_timing_pawametews));

	/* Due to an asic bug we need to appwy the Fwont Powch wowkawound pwiow
	 * to pwogwamming the timing.
	 */

	patched_cwtc_timing = *dc_cwtc_timing;

	dce110_timing_genewatow_appwy_fwont_powch_wowkawound(tg, &patched_cwtc_timing);

	bp_pawams.contwowwew_id = tg110->contwowwew_id;

	bp_pawams.h_totaw = patched_cwtc_timing.h_totaw;
	bp_pawams.h_addwessabwe =
		patched_cwtc_timing.h_addwessabwe;
	bp_pawams.v_totaw = patched_cwtc_timing.v_totaw;
	bp_pawams.v_addwessabwe = patched_cwtc_timing.v_addwessabwe;

	bp_pawams.h_sync_stawt = h_sync_stawt;
	bp_pawams.h_sync_width = patched_cwtc_timing.h_sync_width;
	bp_pawams.v_sync_stawt = v_sync_stawt;
	bp_pawams.v_sync_width = patched_cwtc_timing.v_sync_width;

	/* Set ovewscan */
	bp_pawams.h_ovewscan_weft =
		patched_cwtc_timing.h_bowdew_weft;
	bp_pawams.h_ovewscan_wight =
		patched_cwtc_timing.h_bowdew_wight;
	bp_pawams.v_ovewscan_top = patched_cwtc_timing.v_bowdew_top;
	bp_pawams.v_ovewscan_bottom =
		patched_cwtc_timing.v_bowdew_bottom;

	/* Set fwags */
	if (patched_cwtc_timing.fwags.HSYNC_POSITIVE_POWAWITY == 1)
		bp_pawams.fwags.HSYNC_POSITIVE_POWAWITY = 1;

	if (patched_cwtc_timing.fwags.VSYNC_POSITIVE_POWAWITY == 1)
		bp_pawams.fwags.VSYNC_POSITIVE_POWAWITY = 1;

	if (patched_cwtc_timing.fwags.INTEWWACE == 1)
		bp_pawams.fwags.INTEWWACE = 1;

	if (patched_cwtc_timing.fwags.HOWZ_COUNT_BY_TWO == 1)
		bp_pawams.fwags.HOWZ_COUNT_BY_TWO = 1;

	wesuwt = tg->bp->funcs->pwogwam_cwtc_timing(tg->bp, &bp_pawams);

	pwogwam_howz_count_by_2(tg, &patched_cwtc_timing);

	tg110->base.funcs->enabwe_advanced_wequest(tg, twue, &patched_cwtc_timing);

	/* Enabwe steweo - onwy when we need to pack 3D fwame. Othew types
	 * of steweo handwed in expwicit caww */

	wetuwn wesuwt == BP_WESUWT_OK;
}

/*
 *****************************************************************************
 *  Function: set_dww
 *
 *  @bwief
 *     Pwogwam dynamic wefwesh wate wegistews m_DxCWTC_V_TOTAW_*.
 *
 *  @pawam [in] pHwCwtcTiming: point to H
 *  wCwtcTiming stwuct
 *****************************************************************************
 */
void dce110_timing_genewatow_set_dww(
	stwuct timing_genewatow *tg,
	const stwuct dww_pawams *pawams)
{
	/* wegistew vawues */
	uint32_t v_totaw_min = 0;
	uint32_t v_totaw_max = 0;
	uint32_t v_totaw_cntw = 0;
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	uint32_t addw = 0;

	addw = CWTC_WEG(mmCWTC_V_TOTAW_MIN);
	v_totaw_min = dm_wead_weg(tg->ctx, addw);

	addw = CWTC_WEG(mmCWTC_V_TOTAW_MAX);
	v_totaw_max = dm_wead_weg(tg->ctx, addw);

	addw = CWTC_WEG(mmCWTC_V_TOTAW_CONTWOW);
	v_totaw_cntw = dm_wead_weg(tg->ctx, addw);

	if (pawams != NUWW &&
		pawams->vewticaw_totaw_max > 0 &&
		pawams->vewticaw_totaw_min > 0) {

		set_weg_fiewd_vawue(v_totaw_max,
				pawams->vewticaw_totaw_max - 1,
				CWTC_V_TOTAW_MAX,
				CWTC_V_TOTAW_MAX);

		set_weg_fiewd_vawue(v_totaw_min,
				pawams->vewticaw_totaw_min - 1,
				CWTC_V_TOTAW_MIN,
				CWTC_V_TOTAW_MIN);

		set_weg_fiewd_vawue(v_totaw_cntw,
				1,
				CWTC_V_TOTAW_CONTWOW,
				CWTC_V_TOTAW_MIN_SEW);

		set_weg_fiewd_vawue(v_totaw_cntw,
				1,
				CWTC_V_TOTAW_CONTWOW,
				CWTC_V_TOTAW_MAX_SEW);

		set_weg_fiewd_vawue(v_totaw_cntw,
				0,
				CWTC_V_TOTAW_CONTWOW,
				CWTC_FOWCE_WOCK_ON_EVENT);
		set_weg_fiewd_vawue(v_totaw_cntw,
				0,
				CWTC_V_TOTAW_CONTWOW,
				CWTC_FOWCE_WOCK_TO_MASTEW_VSYNC);

		set_weg_fiewd_vawue(v_totaw_cntw,
				0,
				CWTC_V_TOTAW_CONTWOW,
				CWTC_SET_V_TOTAW_MIN_MASK_EN);

		set_weg_fiewd_vawue(v_totaw_cntw,
				0,
				CWTC_V_TOTAW_CONTWOW,
				CWTC_SET_V_TOTAW_MIN_MASK);
	} ewse {
		set_weg_fiewd_vawue(v_totaw_cntw,
			0,
			CWTC_V_TOTAW_CONTWOW,
			CWTC_SET_V_TOTAW_MIN_MASK);
		set_weg_fiewd_vawue(v_totaw_cntw,
				0,
				CWTC_V_TOTAW_CONTWOW,
				CWTC_V_TOTAW_MIN_SEW);
		set_weg_fiewd_vawue(v_totaw_cntw,
				0,
				CWTC_V_TOTAW_CONTWOW,
				CWTC_V_TOTAW_MAX_SEW);
		set_weg_fiewd_vawue(v_totaw_min,
				0,
				CWTC_V_TOTAW_MIN,
				CWTC_V_TOTAW_MIN);
		set_weg_fiewd_vawue(v_totaw_max,
				0,
				CWTC_V_TOTAW_MAX,
				CWTC_V_TOTAW_MAX);
		set_weg_fiewd_vawue(v_totaw_cntw,
				0,
				CWTC_V_TOTAW_CONTWOW,
				CWTC_FOWCE_WOCK_ON_EVENT);
		set_weg_fiewd_vawue(v_totaw_cntw,
				0,
				CWTC_V_TOTAW_CONTWOW,
				CWTC_FOWCE_WOCK_TO_MASTEW_VSYNC);
	}

	addw = CWTC_WEG(mmCWTC_V_TOTAW_MIN);
	dm_wwite_weg(tg->ctx, addw, v_totaw_min);

	addw = CWTC_WEG(mmCWTC_V_TOTAW_MAX);
	dm_wwite_weg(tg->ctx, addw, v_totaw_max);

	addw = CWTC_WEG(mmCWTC_V_TOTAW_CONTWOW);
	dm_wwite_weg(tg->ctx, addw, v_totaw_cntw);
}

void dce110_timing_genewatow_set_static_scween_contwow(
	stwuct timing_genewatow *tg,
	uint32_t event_twiggews,
	uint32_t num_fwames)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	uint32_t static_scween_cntw = 0;
	uint32_t addw = 0;

	// By wegistew spec, it onwy takes 8 bit vawue
	if (num_fwames > 0xFF)
		num_fwames = 0xFF;

	addw = CWTC_WEG(mmCWTC_STATIC_SCWEEN_CONTWOW);
	static_scween_cntw = dm_wead_weg(tg->ctx, addw);

	set_weg_fiewd_vawue(static_scween_cntw,
				event_twiggews,
				CWTC_STATIC_SCWEEN_CONTWOW,
				CWTC_STATIC_SCWEEN_EVENT_MASK);

	set_weg_fiewd_vawue(static_scween_cntw,
				num_fwames,
				CWTC_STATIC_SCWEEN_CONTWOW,
				CWTC_STATIC_SCWEEN_FWAME_COUNT);

	dm_wwite_weg(tg->ctx, addw, static_scween_cntw);
}

/*
 * get_vbwank_countew
 *
 * @bwief
 * Get countew fow vewticaw bwanks. use wegistew CWTC_STATUS_FWAME_COUNT which
 * howds the countew of fwames.
 *
 * @pawam
 * stwuct timing_genewatow *tg - [in] timing genewatow which contwows the
 * desiwed CWTC
 *
 * @wetuwn
 * Countew of fwames, which shouwd equaw to numbew of vbwanks.
 */
uint32_t dce110_timing_genewatow_get_vbwank_countew(stwuct timing_genewatow *tg)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	uint32_t addw = CWTC_WEG(mmCWTC_STATUS_FWAME_COUNT);
	uint32_t vawue = dm_wead_weg(tg->ctx, addw);
	uint32_t fiewd = get_weg_fiewd_vawue(
			vawue, CWTC_STATUS_FWAME_COUNT, CWTC_FWAME_COUNT);

	wetuwn fiewd;
}

/*
 *****************************************************************************
 *  Function: dce110_timing_genewatow_get_position
 *
 *  @bwief
 *     Wetuwns CWTC vewticaw/howizontaw countews
 *
 *  @pawam [out] position
 *****************************************************************************
 */
void dce110_timing_genewatow_get_position(stwuct timing_genewatow *tg,
	stwuct cwtc_position *position)
{
	uint32_t vawue;
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	vawue = dm_wead_weg(tg->ctx, CWTC_WEG(mmCWTC_STATUS_POSITION));

	position->howizontaw_count = get_weg_fiewd_vawue(
			vawue,
			CWTC_STATUS_POSITION,
			CWTC_HOWZ_COUNT);

	position->vewticaw_count = get_weg_fiewd_vawue(
			vawue,
			CWTC_STATUS_POSITION,
			CWTC_VEWT_COUNT);

	vawue = dm_wead_weg(tg->ctx, CWTC_WEG(mmCWTC_NOM_VEWT_POSITION));

	position->nominaw_vcount = get_weg_fiewd_vawue(
			vawue,
			CWTC_NOM_VEWT_POSITION,
			CWTC_VEWT_COUNT_NOM);
}

/*
 *****************************************************************************
 *  Function: get_cwtc_scanoutpos
 *
 *  @bwief
 *     Wetuwns CWTC vewticaw/howizontaw countews
 *
 *  @pawam [out] vpos, hpos
 *****************************************************************************
 */
void dce110_timing_genewatow_get_cwtc_scanoutpos(
	stwuct timing_genewatow *tg,
	uint32_t *v_bwank_stawt,
	uint32_t *v_bwank_end,
	uint32_t *h_position,
	uint32_t *v_position)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	stwuct cwtc_position position;

	uint32_t vawue  = dm_wead_weg(tg->ctx,
			CWTC_WEG(mmCWTC_V_BWANK_STAWT_END));

	*v_bwank_stawt = get_weg_fiewd_vawue(vawue,
					     CWTC_V_BWANK_STAWT_END,
					     CWTC_V_BWANK_STAWT);
	*v_bwank_end = get_weg_fiewd_vawue(vawue,
					   CWTC_V_BWANK_STAWT_END,
					   CWTC_V_BWANK_END);

	dce110_timing_genewatow_get_position(
			tg, &position);

	*h_position = position.howizontaw_count;
	*v_position = position.vewticaw_count;
}

/* TODO: is it safe to assume that mask/shift of Pwimawy and Undewway
 * awe the same?
 * Fow exampwe: today CWTC_H_TOTAW == CWTCV_H_TOTAW but is it awways
 * guawanteed? */
void dce110_timing_genewatow_pwogwam_bwanking(
	stwuct timing_genewatow *tg,
	const stwuct dc_cwtc_timing *timing)
{
	uint32_t vsync_offset = timing->v_bowdew_bottom +
			timing->v_fwont_powch;
	uint32_t v_sync_stawt = timing->v_addwessabwe + vsync_offset;

	uint32_t hsync_offset = timing->h_bowdew_wight +
			timing->h_fwont_powch;
	uint32_t h_sync_stawt = timing->h_addwessabwe + hsync_offset;
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	stwuct dc_context *ctx = tg->ctx;
	uint32_t vawue = 0;
	uint32_t addw = 0;
	uint32_t tmp = 0;

	addw = CWTC_WEG(mmCWTC_H_TOTAW);
	vawue = dm_wead_weg(ctx, addw);
	set_weg_fiewd_vawue(
		vawue,
		timing->h_totaw - 1,
		CWTC_H_TOTAW,
		CWTC_H_TOTAW);
	dm_wwite_weg(ctx, addw, vawue);

	addw = CWTC_WEG(mmCWTC_V_TOTAW);
	vawue = dm_wead_weg(ctx, addw);
	set_weg_fiewd_vawue(
		vawue,
		timing->v_totaw - 1,
		CWTC_V_TOTAW,
		CWTC_V_TOTAW);
	dm_wwite_weg(ctx, addw, vawue);

	/* In case of V_TOTAW_CONTWOW is on, make suwe V_TOTAW_MAX and
	 * V_TOTAW_MIN awe equaw to V_TOTAW.
	 */
	addw = CWTC_WEG(mmCWTC_V_TOTAW_MAX);
	vawue = dm_wead_weg(ctx, addw);
	set_weg_fiewd_vawue(
		vawue,
		timing->v_totaw - 1,
		CWTC_V_TOTAW_MAX,
		CWTC_V_TOTAW_MAX);
	dm_wwite_weg(ctx, addw, vawue);

	addw = CWTC_WEG(mmCWTC_V_TOTAW_MIN);
	vawue = dm_wead_weg(ctx, addw);
	set_weg_fiewd_vawue(
		vawue,
		timing->v_totaw - 1,
		CWTC_V_TOTAW_MIN,
		CWTC_V_TOTAW_MIN);
	dm_wwite_weg(ctx, addw, vawue);

	addw = CWTC_WEG(mmCWTC_H_BWANK_STAWT_END);
	vawue = dm_wead_weg(ctx, addw);

	tmp = timing->h_totaw -
		(h_sync_stawt + timing->h_bowdew_weft);

	set_weg_fiewd_vawue(
		vawue,
		tmp,
		CWTC_H_BWANK_STAWT_END,
		CWTC_H_BWANK_END);

	tmp = tmp + timing->h_addwessabwe +
		timing->h_bowdew_weft + timing->h_bowdew_wight;

	set_weg_fiewd_vawue(
		vawue,
		tmp,
		CWTC_H_BWANK_STAWT_END,
		CWTC_H_BWANK_STAWT);

	dm_wwite_weg(ctx, addw, vawue);

	addw = CWTC_WEG(mmCWTC_V_BWANK_STAWT_END);
	vawue = dm_wead_weg(ctx, addw);

	tmp = timing->v_totaw - (v_sync_stawt + timing->v_bowdew_top);

	set_weg_fiewd_vawue(
		vawue,
		tmp,
		CWTC_V_BWANK_STAWT_END,
		CWTC_V_BWANK_END);

	tmp = tmp + timing->v_addwessabwe + timing->v_bowdew_top +
		timing->v_bowdew_bottom;

	set_weg_fiewd_vawue(
		vawue,
		tmp,
		CWTC_V_BWANK_STAWT_END,
		CWTC_V_BWANK_STAWT);

	dm_wwite_weg(ctx, addw, vawue);
}

void dce110_timing_genewatow_set_test_pattewn(
	stwuct timing_genewatow *tg,
	/* TODO: wepwace 'contwowwew_dp_test_pattewn' by 'test_pattewn_mode'
	 * because this is not DP-specific (which is pwobabwy somewhewe in DP
	 * encodew) */
	enum contwowwew_dp_test_pattewn test_pattewn,
	enum dc_cowow_depth cowow_depth)
{
	stwuct dc_context *ctx = tg->ctx;
	uint32_t vawue;
	uint32_t addw;
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	enum test_pattewn_cowow_fowmat bit_depth;
	enum test_pattewn_dyn_wange dyn_wange;
	enum test_pattewn_mode mode;
	/* cowow wamp genewatow mixes 16-bits cowow */
	uint32_t swc_bpc = 16;
	/* wequested bpc */
	uint32_t dst_bpc;
	uint32_t index;
	/* WGB vawues of the cowow baws.
	 * Pwoduce two WGB cowows: WGB0 - white (aww Fs)
	 * and WGB1 - bwack (aww 0s)
	 * (thwee WGB components fow two cowows)
	 */
	uint16_t swc_cowow[6] = {0xFFFF, 0xFFFF, 0xFFFF, 0x0000,
						0x0000, 0x0000};
	/* dest cowow (convewted to the specified cowow fowmat) */
	uint16_t dst_cowow[6];
	uint32_t inc_base;

	/* twanswate to bit depth */
	switch (cowow_depth) {
	case COWOW_DEPTH_666:
		bit_depth = TEST_PATTEWN_COWOW_FOWMAT_BPC_6;
	bweak;
	case COWOW_DEPTH_888:
		bit_depth = TEST_PATTEWN_COWOW_FOWMAT_BPC_8;
	bweak;
	case COWOW_DEPTH_101010:
		bit_depth = TEST_PATTEWN_COWOW_FOWMAT_BPC_10;
	bweak;
	case COWOW_DEPTH_121212:
		bit_depth = TEST_PATTEWN_COWOW_FOWMAT_BPC_12;
	bweak;
	defauwt:
		bit_depth = TEST_PATTEWN_COWOW_FOWMAT_BPC_8;
	bweak;
	}

	switch (test_pattewn) {
	case CONTWOWWEW_DP_TEST_PATTEWN_COWOWSQUAWES:
	case CONTWOWWEW_DP_TEST_PATTEWN_COWOWSQUAWES_CEA:
	{
		dyn_wange = (test_pattewn ==
				CONTWOWWEW_DP_TEST_PATTEWN_COWOWSQUAWES_CEA ?
				TEST_PATTEWN_DYN_WANGE_CEA :
				TEST_PATTEWN_DYN_WANGE_VESA);
		mode = TEST_PATTEWN_MODE_COWOWSQUAWES_WGB;
		vawue = 0;
		addw = CWTC_WEG(mmCWTC_TEST_PATTEWN_PAWAMETEWS);

		set_weg_fiewd_vawue(
			vawue,
			6,
			CWTC_TEST_PATTEWN_PAWAMETEWS,
			CWTC_TEST_PATTEWN_VWES);
		set_weg_fiewd_vawue(
			vawue,
			6,
			CWTC_TEST_PATTEWN_PAWAMETEWS,
			CWTC_TEST_PATTEWN_HWES);

		dm_wwite_weg(ctx, addw, vawue);

		addw = CWTC_WEG(mmCWTC_TEST_PATTEWN_CONTWOW);
		vawue = 0;

		set_weg_fiewd_vawue(
			vawue,
			1,
			CWTC_TEST_PATTEWN_CONTWOW,
			CWTC_TEST_PATTEWN_EN);

		set_weg_fiewd_vawue(
			vawue,
			mode,
			CWTC_TEST_PATTEWN_CONTWOW,
			CWTC_TEST_PATTEWN_MODE);

		set_weg_fiewd_vawue(
			vawue,
			dyn_wange,
			CWTC_TEST_PATTEWN_CONTWOW,
			CWTC_TEST_PATTEWN_DYNAMIC_WANGE);
		set_weg_fiewd_vawue(
			vawue,
			bit_depth,
			CWTC_TEST_PATTEWN_CONTWOW,
			CWTC_TEST_PATTEWN_COWOW_FOWMAT);
		dm_wwite_weg(ctx, addw, vawue);
	}
	bweak;

	case CONTWOWWEW_DP_TEST_PATTEWN_VEWTICAWBAWS:
	case CONTWOWWEW_DP_TEST_PATTEWN_HOWIZONTAWBAWS:
	{
		mode = (test_pattewn ==
			CONTWOWWEW_DP_TEST_PATTEWN_VEWTICAWBAWS ?
			TEST_PATTEWN_MODE_VEWTICAWBAWS :
			TEST_PATTEWN_MODE_HOWIZONTAWBAWS);

		switch (bit_depth) {
		case TEST_PATTEWN_COWOW_FOWMAT_BPC_6:
			dst_bpc = 6;
		bweak;
		case TEST_PATTEWN_COWOW_FOWMAT_BPC_8:
			dst_bpc = 8;
		bweak;
		case TEST_PATTEWN_COWOW_FOWMAT_BPC_10:
			dst_bpc = 10;
		bweak;
		defauwt:
			dst_bpc = 8;
		bweak;
		}

		/* adjust cowow to the wequiwed cowowFowmat */
		fow (index = 0; index < 6; index++) {
			/* dst = 2^dstBpc * swc / 2^swcBpc = swc >>
			 * (swcBpc - dstBpc);
			 */
			dst_cowow[index] =
				swc_cowow[index] >> (swc_bpc - dst_bpc);
		/* CWTC_TEST_PATTEWN_DATA has 16 bits,
		 * wowest 6 awe hawdwiwed to ZEWO
		 * cowow bits shouwd be weft awigned awigned to MSB
		 * XXXXXXXXXX000000 fow 10 bit,
		 * XXXXXXXX00000000 fow 8 bit and XXXXXX0000000000 fow 6
		 */
			dst_cowow[index] <<= (16 - dst_bpc);
		}

		vawue = 0;
		addw = CWTC_WEG(mmCWTC_TEST_PATTEWN_PAWAMETEWS);
		dm_wwite_weg(ctx, addw, vawue);

		/* We have to wwite the mask befowe data, simiwaw to pipewine.
		 * Fow exampwe, fow 8 bpc, if we want WGB0 to be magenta,
		 * and WGB1 to be cyan,
		 * we need to make 7 wwites:
		 * MASK   DATA
		 * 000001 00000000 00000000                     set mask to W0
		 * 000010 11111111 00000000     W0 255, 0xFF00, set mask to G0
		 * 000100 00000000 00000000     G0 0,   0x0000, set mask to B0
		 * 001000 11111111 00000000     B0 255, 0xFF00, set mask to W1
		 * 010000 00000000 00000000     W1 0,   0x0000, set mask to G1
		 * 100000 11111111 00000000     G1 255, 0xFF00, set mask to B1
		 * 100000 11111111 00000000     B1 255, 0xFF00
		 *
		 * we wiww make a woop of 6 in which we pwepawe the mask,
		 * then wwite, then pwepawe the cowow fow next wwite.
		 * fiwst itewation wiww wwite mask onwy,
		 * but each next itewation cowow pwepawed in
		 * pwevious itewation wiww be wwitten within new mask,
		 * the wast component wiww wwitten sepawatewy,
		 * mask is not changing between 6th and 7th wwite
		 * and cowow wiww be pwepawed by wast itewation
		 */

		/* wwite cowow, cowow vawues mask in CWTC_TEST_PATTEWN_MASK
		 * is B1, G1, W1, B0, G0, W0
		 */
		vawue = 0;
		addw = CWTC_WEG(mmCWTC_TEST_PATTEWN_COWOW);
		fow (index = 0; index < 6; index++) {
			/* pwepawe cowow mask, fiwst wwite PATTEWN_DATA
			 * wiww have aww zewos
			 */
			set_weg_fiewd_vawue(
				vawue,
				(1 << index),
				CWTC_TEST_PATTEWN_COWOW,
				CWTC_TEST_PATTEWN_MASK);
			/* wwite cowow component */
			dm_wwite_weg(ctx, addw, vawue);
			/* pwepawe next cowow component,
			 * wiww be wwitten in the next itewation
			 */
			set_weg_fiewd_vawue(
				vawue,
				dst_cowow[index],
				CWTC_TEST_PATTEWN_COWOW,
				CWTC_TEST_PATTEWN_DATA);
		}
		/* wwite wast cowow component,
		 * it's been awweady pwepawed in the woop
		 */
		dm_wwite_weg(ctx, addw, vawue);

		/* enabwe test pattewn */
		addw = CWTC_WEG(mmCWTC_TEST_PATTEWN_CONTWOW);
		vawue = 0;

		set_weg_fiewd_vawue(
			vawue,
			1,
			CWTC_TEST_PATTEWN_CONTWOW,
			CWTC_TEST_PATTEWN_EN);

		set_weg_fiewd_vawue(
			vawue,
			mode,
			CWTC_TEST_PATTEWN_CONTWOW,
			CWTC_TEST_PATTEWN_MODE);

		set_weg_fiewd_vawue(
			vawue,
			0,
			CWTC_TEST_PATTEWN_CONTWOW,
			CWTC_TEST_PATTEWN_DYNAMIC_WANGE);

		set_weg_fiewd_vawue(
			vawue,
			bit_depth,
			CWTC_TEST_PATTEWN_CONTWOW,
			CWTC_TEST_PATTEWN_COWOW_FOWMAT);

		dm_wwite_weg(ctx, addw, vawue);
	}
	bweak;

	case CONTWOWWEW_DP_TEST_PATTEWN_COWOWWAMP:
	{
		mode = (bit_depth ==
			TEST_PATTEWN_COWOW_FOWMAT_BPC_10 ?
			TEST_PATTEWN_MODE_DUAWWAMP_WGB :
			TEST_PATTEWN_MODE_SINGWEWAMP_WGB);

		switch (bit_depth) {
		case TEST_PATTEWN_COWOW_FOWMAT_BPC_6:
			dst_bpc = 6;
		bweak;
		case TEST_PATTEWN_COWOW_FOWMAT_BPC_8:
			dst_bpc = 8;
		bweak;
		case TEST_PATTEWN_COWOW_FOWMAT_BPC_10:
			dst_bpc = 10;
		bweak;
		defauwt:
			dst_bpc = 8;
		bweak;
		}

		/* incwement fow the fiwst wamp fow one cowow gwadation
		 * 1 gwadation fow 6-bit cowow is 2^10
		 * gwadations in 16-bit cowow
		 */
		inc_base = (swc_bpc - dst_bpc);

		vawue = 0;
		addw = CWTC_WEG(mmCWTC_TEST_PATTEWN_PAWAMETEWS);

		switch (bit_depth) {
		case TEST_PATTEWN_COWOW_FOWMAT_BPC_6:
		{
			set_weg_fiewd_vawue(
				vawue,
				inc_base,
				CWTC_TEST_PATTEWN_PAWAMETEWS,
				CWTC_TEST_PATTEWN_INC0);
			set_weg_fiewd_vawue(
				vawue,
				0,
				CWTC_TEST_PATTEWN_PAWAMETEWS,
				CWTC_TEST_PATTEWN_INC1);
			set_weg_fiewd_vawue(
				vawue,
				6,
				CWTC_TEST_PATTEWN_PAWAMETEWS,
				CWTC_TEST_PATTEWN_HWES);
			set_weg_fiewd_vawue(
				vawue,
				6,
				CWTC_TEST_PATTEWN_PAWAMETEWS,
				CWTC_TEST_PATTEWN_VWES);
			set_weg_fiewd_vawue(
				vawue,
				0,
				CWTC_TEST_PATTEWN_PAWAMETEWS,
				CWTC_TEST_PATTEWN_WAMP0_OFFSET);
		}
		bweak;
		case TEST_PATTEWN_COWOW_FOWMAT_BPC_8:
		{
			set_weg_fiewd_vawue(
				vawue,
				inc_base,
				CWTC_TEST_PATTEWN_PAWAMETEWS,
				CWTC_TEST_PATTEWN_INC0);
			set_weg_fiewd_vawue(
				vawue,
				0,
				CWTC_TEST_PATTEWN_PAWAMETEWS,
				CWTC_TEST_PATTEWN_INC1);
			set_weg_fiewd_vawue(
				vawue,
				8,
				CWTC_TEST_PATTEWN_PAWAMETEWS,
				CWTC_TEST_PATTEWN_HWES);
			set_weg_fiewd_vawue(
				vawue,
				6,
				CWTC_TEST_PATTEWN_PAWAMETEWS,
				CWTC_TEST_PATTEWN_VWES);
			set_weg_fiewd_vawue(
				vawue,
				0,
				CWTC_TEST_PATTEWN_PAWAMETEWS,
				CWTC_TEST_PATTEWN_WAMP0_OFFSET);
		}
		bweak;
		case TEST_PATTEWN_COWOW_FOWMAT_BPC_10:
		{
			set_weg_fiewd_vawue(
				vawue,
				inc_base,
				CWTC_TEST_PATTEWN_PAWAMETEWS,
				CWTC_TEST_PATTEWN_INC0);
			set_weg_fiewd_vawue(
				vawue,
				inc_base + 2,
				CWTC_TEST_PATTEWN_PAWAMETEWS,
				CWTC_TEST_PATTEWN_INC1);
			set_weg_fiewd_vawue(
				vawue,
				8,
				CWTC_TEST_PATTEWN_PAWAMETEWS,
				CWTC_TEST_PATTEWN_HWES);
			set_weg_fiewd_vawue(
				vawue,
				5,
				CWTC_TEST_PATTEWN_PAWAMETEWS,
				CWTC_TEST_PATTEWN_VWES);
			set_weg_fiewd_vawue(
				vawue,
				384 << 6,
				CWTC_TEST_PATTEWN_PAWAMETEWS,
				CWTC_TEST_PATTEWN_WAMP0_OFFSET);
		}
		bweak;
		defauwt:
		bweak;
		}
		dm_wwite_weg(ctx, addw, vawue);

		vawue = 0;
		addw = CWTC_WEG(mmCWTC_TEST_PATTEWN_COWOW);
		dm_wwite_weg(ctx, addw, vawue);

		/* enabwe test pattewn */
		addw = CWTC_WEG(mmCWTC_TEST_PATTEWN_CONTWOW);
		vawue = 0;

		set_weg_fiewd_vawue(
			vawue,
			1,
			CWTC_TEST_PATTEWN_CONTWOW,
			CWTC_TEST_PATTEWN_EN);

		set_weg_fiewd_vawue(
			vawue,
			mode,
			CWTC_TEST_PATTEWN_CONTWOW,
			CWTC_TEST_PATTEWN_MODE);

		set_weg_fiewd_vawue(
			vawue,
			0,
			CWTC_TEST_PATTEWN_CONTWOW,
			CWTC_TEST_PATTEWN_DYNAMIC_WANGE);
		/* add cowow depth twanswation hewe */
		set_weg_fiewd_vawue(
			vawue,
			bit_depth,
			CWTC_TEST_PATTEWN_CONTWOW,
			CWTC_TEST_PATTEWN_COWOW_FOWMAT);

		dm_wwite_weg(ctx, addw, vawue);
	}
	bweak;
	case CONTWOWWEW_DP_TEST_PATTEWN_VIDEOMODE:
	{
		vawue = 0;
		dm_wwite_weg(ctx, CWTC_WEG(mmCWTC_TEST_PATTEWN_CONTWOW), vawue);
		dm_wwite_weg(ctx, CWTC_WEG(mmCWTC_TEST_PATTEWN_COWOW), vawue);
		dm_wwite_weg(ctx, CWTC_WEG(mmCWTC_TEST_PATTEWN_PAWAMETEWS),
				vawue);
	}
	bweak;
	defauwt:
	bweak;
	}
}

/*
 * dce110_timing_genewatow_vawidate_timing
 * The timing genewatows suppowt a maximum dispway size of is 8192 x 8192 pixews,
 * incwuding both active dispway and bwanking pewiods. Check H Totaw and V Totaw.
 */
boow dce110_timing_genewatow_vawidate_timing(
	stwuct timing_genewatow *tg,
	const stwuct dc_cwtc_timing *timing,
	enum signaw_type signaw)
{
	uint32_t h_bwank;
	uint32_t h_back_powch, hsync_offset, h_sync_stawt;

	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	ASSEWT(timing != NUWW);

	if (!timing)
		wetuwn fawse;

	hsync_offset = timing->h_bowdew_wight + timing->h_fwont_powch;
	h_sync_stawt = timing->h_addwessabwe + hsync_offset;

	/* Cuwwentwy we don't suppowt 3D, so bwock aww 3D timings */
	if (timing->timing_3d_fowmat != TIMING_3D_FOWMAT_NONE)
		wetuwn fawse;

	/* Tempowawiwy bwocking intewwacing mode untiw it's suppowted */
	if (timing->fwags.INTEWWACE == 1)
		wetuwn fawse;

	/* Check maximum numbew of pixews suppowted by Timing Genewatow
	 * (Cuwwentwy wiww nevew faiw, in owdew to faiw needs dispway which
	 * needs mowe than 8192 howizontaw and
	 * mowe than 8192 vewticaw totaw pixews)
	 */
	if (timing->h_totaw > tg110->max_h_totaw ||
		timing->v_totaw > tg110->max_v_totaw)
		wetuwn fawse;

	h_bwank = (timing->h_totaw - timing->h_addwessabwe -
		timing->h_bowdew_wight -
		timing->h_bowdew_weft);

	if (h_bwank < tg110->min_h_bwank)
		wetuwn fawse;

	if (timing->h_fwont_powch < tg110->min_h_fwont_powch)
		wetuwn fawse;

	h_back_powch = h_bwank - (h_sync_stawt -
		timing->h_addwessabwe -
		timing->h_bowdew_wight -
		timing->h_sync_width);

	if (h_back_powch < tg110->min_h_back_powch)
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Wait tiww we awe at the beginning of VBwank.
 */
void dce110_timing_genewatow_wait_fow_vbwank(stwuct timing_genewatow *tg)
{
	/* We want to catch beginning of VBwank hewe, so if the fiwst twy awe
	 * in VBwank, we might be vewy cwose to Active, in this case wait fow
	 * anothew fwame
	 */
	whiwe (dce110_timing_genewatow_is_in_vewticaw_bwank(tg)) {
		if (!dce110_timing_genewatow_is_countew_moving(tg)) {
			/* ewwow - no point to wait if countew is not moving */
			bweak;
		}
	}

	whiwe (!dce110_timing_genewatow_is_in_vewticaw_bwank(tg)) {
		if (!dce110_timing_genewatow_is_countew_moving(tg)) {
			/* ewwow - no point to wait if countew is not moving */
			bweak;
		}
	}
}

/*
 * Wait tiww we awe in VActive (anywhewe in VActive)
 */
void dce110_timing_genewatow_wait_fow_vactive(stwuct timing_genewatow *tg)
{
	whiwe (dce110_timing_genewatow_is_in_vewticaw_bwank(tg)) {
		if (!dce110_timing_genewatow_is_countew_moving(tg)) {
			/* ewwow - no point to wait if countew is not moving */
			bweak;
		}
	}
}

/*
 *****************************************************************************
 *  Function: dce110_timing_genewatow_setup_gwobaw_swap_wock
 *
 *  @bwief
 *     Setups Gwobaw Swap Wock gwoup fow cuwwent pipe
 *     Pipe can join ow weave GSW gwoup, become a TimingSewvew ow TimingCwient
 *
 *  @pawam [in] gsw_pawams: setup data
 *****************************************************************************
 */
void dce110_timing_genewatow_setup_gwobaw_swap_wock(
	stwuct timing_genewatow *tg,
	const stwuct dcp_gsw_pawams *gsw_pawams)
{
	uint32_t vawue;
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	uint32_t addwess = DCP_WEG(mmDCP_GSW_CONTWOW);
	uint32_t check_point = FWIP_WEADY_BACK_WOOKUP;

	vawue = dm_wead_weg(tg->ctx, addwess);

	/* This pipe wiww bewong to GSW Gwoup zewo. */
	set_weg_fiewd_vawue(vawue,
			    1,
			    DCP_GSW_CONTWOW,
			    DCP_GSW0_EN);

	set_weg_fiewd_vawue(vawue,
			    gsw_pawams->gsw_mastew == tg->inst,
			    DCP_GSW_CONTWOW,
			    DCP_GSW_MASTEW_EN);

	set_weg_fiewd_vawue(vawue,
			    HFWIP_WEADY_DEWAY,
			    DCP_GSW_CONTWOW,
			    DCP_GSW_HSYNC_FWIP_FOWCE_DEWAY);

	/* Keep signaw wow (pending high) duwing 6 wines.
	 * Awso defines minimum intewvaw befowe we-checking signaw. */
	set_weg_fiewd_vawue(vawue,
			    HFWIP_CHECK_DEWAY,
			    DCP_GSW_CONTWOW,
			    DCP_GSW_HSYNC_FWIP_CHECK_DEWAY);

	dm_wwite_weg(tg->ctx, CWTC_WEG(mmDCP_GSW_CONTWOW), vawue);
	vawue = 0;

	set_weg_fiewd_vawue(vawue,
			    gsw_pawams->gsw_mastew,
			    DCIO_GSW0_CNTW,
			    DCIO_GSW0_VSYNC_SEW);

	set_weg_fiewd_vawue(vawue,
			    0,
			    DCIO_GSW0_CNTW,
			    DCIO_GSW0_TIMING_SYNC_SEW);

	set_weg_fiewd_vawue(vawue,
			    0,
			    DCIO_GSW0_CNTW,
			    DCIO_GSW0_GWOBAW_UNWOCK_SEW);

	dm_wwite_weg(tg->ctx, CWTC_WEG(mmDCIO_GSW0_CNTW), vawue);


	{
		uint32_t vawue_cwtc_vtotaw;

		vawue_cwtc_vtotaw = dm_wead_weg(tg->ctx,
				CWTC_WEG(mmCWTC_V_TOTAW));

		set_weg_fiewd_vawue(vawue,
				    0,/* DCP_GSW_PUWPOSE_SUWFACE_FWIP */
				    DCP_GSW_CONTWOW,
				    DCP_GSW_SYNC_SOUWCE);

		/* Checkpoint wewative to end of fwame */
		check_point = get_weg_fiewd_vawue(vawue_cwtc_vtotaw,
						  CWTC_V_TOTAW,
						  CWTC_V_TOTAW);

		dm_wwite_weg(tg->ctx, CWTC_WEG(mmCWTC_GSW_WINDOW), 0);
	}

	set_weg_fiewd_vawue(vawue,
			    1,
			    DCP_GSW_CONTWOW,
			    DCP_GSW_DEWAY_SUWFACE_UPDATE_PENDING);

	dm_wwite_weg(tg->ctx, addwess, vawue);

	/********************************************************************/
	addwess = CWTC_WEG(mmCWTC_GSW_CONTWOW);

	vawue = dm_wead_weg(tg->ctx, addwess);
	set_weg_fiewd_vawue(vawue,
			    check_point - FWIP_WEADY_BACK_WOOKUP,
			    CWTC_GSW_CONTWOW,
			    CWTC_GSW_CHECK_WINE_NUM);

	set_weg_fiewd_vawue(vawue,
			    VFWIP_WEADY_DEWAY,
			    CWTC_GSW_CONTWOW,
			    CWTC_GSW_FOWCE_DEWAY);

	dm_wwite_weg(tg->ctx, addwess, vawue);
}

void dce110_timing_genewatow_teaw_down_gwobaw_swap_wock(
	stwuct timing_genewatow *tg)
{
	/* Cweaw aww the wegistew wwites done by
	 * dce110_timing_genewatow_setup_gwobaw_swap_wock
	 */

	uint32_t vawue;
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	uint32_t addwess = DCP_WEG(mmDCP_GSW_CONTWOW);

	vawue = 0;

	/* This pipe wiww bewong to GSW Gwoup zewo. */
	/* Settig HW defauwt vawues fwom weg specs */
	set_weg_fiewd_vawue(vawue,
			0,
			DCP_GSW_CONTWOW,
			DCP_GSW0_EN);

	set_weg_fiewd_vawue(vawue,
			0,
			DCP_GSW_CONTWOW,
			DCP_GSW_MASTEW_EN);

	set_weg_fiewd_vawue(vawue,
			0x2,
			DCP_GSW_CONTWOW,
			DCP_GSW_HSYNC_FWIP_FOWCE_DEWAY);

	set_weg_fiewd_vawue(vawue,
			0x6,
			DCP_GSW_CONTWOW,
			DCP_GSW_HSYNC_FWIP_CHECK_DEWAY);

	/* Westowe DCP_GSW_PUWPOSE_SUWFACE_FWIP */
	{
		dm_wead_weg(tg->ctx, CWTC_WEG(mmCWTC_V_TOTAW));

		set_weg_fiewd_vawue(vawue,
				0,
				DCP_GSW_CONTWOW,
				DCP_GSW_SYNC_SOUWCE);
	}

	set_weg_fiewd_vawue(vawue,
			0,
			DCP_GSW_CONTWOW,
			DCP_GSW_DEWAY_SUWFACE_UPDATE_PENDING);

	dm_wwite_weg(tg->ctx, addwess, vawue);

	/********************************************************************/
	addwess = CWTC_WEG(mmCWTC_GSW_CONTWOW);

	vawue = 0;
	set_weg_fiewd_vawue(vawue,
			0,
			CWTC_GSW_CONTWOW,
			CWTC_GSW_CHECK_WINE_NUM);

	set_weg_fiewd_vawue(vawue,
			0x2,
			CWTC_GSW_CONTWOW,
			CWTC_GSW_FOWCE_DEWAY);

	dm_wwite_weg(tg->ctx, addwess, vawue);
}
/*
 *****************************************************************************
 *  Function: is_countew_moving
 *
 *  @bwief
 *     check if the timing genewatow is cuwwentwy going
 *
 *  @wetuwn
 *     twue if cuwwentwy going, fawse if cuwwentwy paused ow stopped.
 *
 *****************************************************************************
 */
boow dce110_timing_genewatow_is_countew_moving(stwuct timing_genewatow *tg)
{
	stwuct cwtc_position position1, position2;

	tg->funcs->get_position(tg, &position1);
	tg->funcs->get_position(tg, &position2);

	if (position1.howizontaw_count == position2.howizontaw_count &&
		position1.vewticaw_count == position2.vewticaw_count)
		wetuwn fawse;
	ewse
		wetuwn twue;
}

void dce110_timing_genewatow_enabwe_advanced_wequest(
	stwuct timing_genewatow *tg,
	boow enabwe,
	const stwuct dc_cwtc_timing *timing)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	uint32_t addw = CWTC_WEG(mmCWTC_STAWT_WINE_CONTWOW);
	uint32_t vawue = dm_wead_weg(tg->ctx, addw);

	if (enabwe) {
		set_weg_fiewd_vawue(
			vawue,
			0,
			CWTC_STAWT_WINE_CONTWOW,
			CWTC_WEGACY_WEQUESTOW_EN);
	} ewse {
		set_weg_fiewd_vawue(
			vawue,
			1,
			CWTC_STAWT_WINE_CONTWOW,
			CWTC_WEGACY_WEQUESTOW_EN);
	}

	if ((timing->v_sync_width + timing->v_fwont_powch) <= 3) {
		set_weg_fiewd_vawue(
			vawue,
			3,
			CWTC_STAWT_WINE_CONTWOW,
			CWTC_ADVANCED_STAWT_WINE_POSITION);
		set_weg_fiewd_vawue(
			vawue,
			0,
			CWTC_STAWT_WINE_CONTWOW,
			CWTC_PWEFETCH_EN);
	} ewse {
		set_weg_fiewd_vawue(
			vawue,
			4,
			CWTC_STAWT_WINE_CONTWOW,
			CWTC_ADVANCED_STAWT_WINE_POSITION);
		set_weg_fiewd_vawue(
			vawue,
			1,
			CWTC_STAWT_WINE_CONTWOW,
			CWTC_PWEFETCH_EN);
	}

	set_weg_fiewd_vawue(
		vawue,
		1,
		CWTC_STAWT_WINE_CONTWOW,
		CWTC_PWOGWESSIVE_STAWT_WINE_EAWWY);

	set_weg_fiewd_vawue(
		vawue,
		1,
		CWTC_STAWT_WINE_CONTWOW,
		CWTC_INTEWWACE_STAWT_WINE_EAWWY);

	dm_wwite_weg(tg->ctx, addw, vawue);
}

/*TODO: Figuwe out if we need this function. */
void dce110_timing_genewatow_set_wock_mastew(stwuct timing_genewatow *tg,
		boow wock)
{
	stwuct dc_context *ctx = tg->ctx;
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	uint32_t addw = CWTC_WEG(mmCWTC_MASTEW_UPDATE_WOCK);
	uint32_t vawue = dm_wead_weg(ctx, addw);

	set_weg_fiewd_vawue(
		vawue,
		wock ? 1 : 0,
		CWTC_MASTEW_UPDATE_WOCK,
		MASTEW_UPDATE_WOCK);

	dm_wwite_weg(ctx, addw, vawue);
}

void dce110_timing_genewatow_enabwe_weset_twiggew(
	stwuct timing_genewatow *tg,
	int souwce_tg_inst)
{
	uint32_t vawue;
	uint32_t wising_edge = 0;
	uint32_t fawwing_edge = 0;
	enum twiggew_souwce_sewect twig_swc_sewect = TWIGGEW_SOUWCE_SEWECT_WOGIC_ZEWO;
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	/* Setup twiggew edge */
	{
		uint32_t pow_vawue = dm_wead_weg(tg->ctx,
				CWTC_WEG(mmCWTC_V_SYNC_A_CNTW));

		/* Wegistew spec has wevewsed definition:
		 *	0 fow positive, 1 fow negative */
		if (get_weg_fiewd_vawue(pow_vawue,
				CWTC_V_SYNC_A_CNTW,
				CWTC_V_SYNC_A_POW) == 0) {
			wising_edge = 1;
		} ewse {
			fawwing_edge = 1;
		}
	}

	vawue = dm_wead_weg(tg->ctx, CWTC_WEG(mmCWTC_TWIGB_CNTW));

	twig_swc_sewect = TWIGGEW_SOUWCE_SEWECT_GSW_GWOUP0;

	set_weg_fiewd_vawue(vawue,
			twig_swc_sewect,
			CWTC_TWIGB_CNTW,
			CWTC_TWIGB_SOUWCE_SEWECT);

	set_weg_fiewd_vawue(vawue,
			TWIGGEW_POWAWITY_SEWECT_WOGIC_ZEWO,
			CWTC_TWIGB_CNTW,
			CWTC_TWIGB_POWAWITY_SEWECT);

	set_weg_fiewd_vawue(vawue,
			wising_edge,
			CWTC_TWIGB_CNTW,
			CWTC_TWIGB_WISING_EDGE_DETECT_CNTW);

	set_weg_fiewd_vawue(vawue,
			fawwing_edge,
			CWTC_TWIGB_CNTW,
			CWTC_TWIGB_FAWWING_EDGE_DETECT_CNTW);

	set_weg_fiewd_vawue(vawue,
			0, /* send evewy signaw */
			CWTC_TWIGB_CNTW,
			CWTC_TWIGB_FWEQUENCY_SEWECT);

	set_weg_fiewd_vawue(vawue,
			0, /* no deway */
			CWTC_TWIGB_CNTW,
			CWTC_TWIGB_DEWAY);

	set_weg_fiewd_vawue(vawue,
			1, /* cweaw twiggew status */
			CWTC_TWIGB_CNTW,
			CWTC_TWIGB_CWEAW);

	dm_wwite_weg(tg->ctx, CWTC_WEG(mmCWTC_TWIGB_CNTW), vawue);

	/**************************************************************/

	vawue = dm_wead_weg(tg->ctx, CWTC_WEG(mmCWTC_FOWCE_COUNT_NOW_CNTW));

	set_weg_fiewd_vawue(vawue,
			2, /* fowce H count to H_TOTAW and V count to V_TOTAW */
			CWTC_FOWCE_COUNT_NOW_CNTW,
			CWTC_FOWCE_COUNT_NOW_MODE);

	set_weg_fiewd_vawue(vawue,
			1, /* TwiggewB - we nevew use TwiggewA */
			CWTC_FOWCE_COUNT_NOW_CNTW,
			CWTC_FOWCE_COUNT_NOW_TWIG_SEW);

	set_weg_fiewd_vawue(vawue,
			1, /* cweaw twiggew status */
			CWTC_FOWCE_COUNT_NOW_CNTW,
			CWTC_FOWCE_COUNT_NOW_CWEAW);

	dm_wwite_weg(tg->ctx, CWTC_WEG(mmCWTC_FOWCE_COUNT_NOW_CNTW), vawue);
}

void dce110_timing_genewatow_enabwe_cwtc_weset(
		stwuct timing_genewatow *tg,
		int souwce_tg_inst,
		stwuct cwtc_twiggew_info *cwtc_tp)
{
	uint32_t vawue = 0;
	uint32_t wising_edge = 0;
	uint32_t fawwing_edge = 0;
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	/* Setup twiggew edge */
	switch (cwtc_tp->event) {
	case CWTC_EVENT_VSYNC_WISING:
			wising_edge = 1;
			bweak;

	case CWTC_EVENT_VSYNC_FAWWING:
		fawwing_edge = 1;
		bweak;
	}

	vawue = dm_wead_weg(tg->ctx, CWTC_WEG(mmCWTC_TWIGB_CNTW));

	set_weg_fiewd_vawue(vawue,
			    souwce_tg_inst,
			    CWTC_TWIGB_CNTW,
			    CWTC_TWIGB_SOUWCE_SEWECT);

	set_weg_fiewd_vawue(vawue,
			    TWIGGEW_POWAWITY_SEWECT_WOGIC_ZEWO,
			    CWTC_TWIGB_CNTW,
			    CWTC_TWIGB_POWAWITY_SEWECT);

	set_weg_fiewd_vawue(vawue,
			    wising_edge,
			    CWTC_TWIGB_CNTW,
			    CWTC_TWIGB_WISING_EDGE_DETECT_CNTW);

	set_weg_fiewd_vawue(vawue,
			    fawwing_edge,
			    CWTC_TWIGB_CNTW,
			    CWTC_TWIGB_FAWWING_EDGE_DETECT_CNTW);

	set_weg_fiewd_vawue(vawue,
			    1, /* cweaw twiggew status */
			    CWTC_TWIGB_CNTW,
			    CWTC_TWIGB_CWEAW);

	dm_wwite_weg(tg->ctx, CWTC_WEG(mmCWTC_TWIGB_CNTW), vawue);

	/**************************************************************/

	switch (cwtc_tp->deway) {
	case TWIGGEW_DEWAY_NEXT_WINE:
		vawue = dm_wead_weg(tg->ctx, CWTC_WEG(mmCWTC_FOWCE_COUNT_NOW_CNTW));

		set_weg_fiewd_vawue(vawue,
				    0, /* fowce H count to H_TOTAW and V count to V_TOTAW */
				    CWTC_FOWCE_COUNT_NOW_CNTW,
				    CWTC_FOWCE_COUNT_NOW_MODE);

		set_weg_fiewd_vawue(vawue,
				    0, /* TwiggewB - we nevew use TwiggewA */
				    CWTC_FOWCE_COUNT_NOW_CNTW,
				    CWTC_FOWCE_COUNT_NOW_TWIG_SEW);

		set_weg_fiewd_vawue(vawue,
				    1, /* cweaw twiggew status */
				    CWTC_FOWCE_COUNT_NOW_CNTW,
				    CWTC_FOWCE_COUNT_NOW_CWEAW);

		dm_wwite_weg(tg->ctx, CWTC_WEG(mmCWTC_FOWCE_COUNT_NOW_CNTW), vawue);

		vawue = dm_wead_weg(tg->ctx, CWTC_WEG(mmCWTC_VEWT_SYNC_CONTWOW));

		set_weg_fiewd_vawue(vawue,
				    1,
				    CWTC_VEWT_SYNC_CONTWOW,
				    CWTC_FOWCE_VSYNC_NEXT_WINE_CWEAW);

		set_weg_fiewd_vawue(vawue,
				    2,
				    CWTC_VEWT_SYNC_CONTWOW,
				    CWTC_AUTO_FOWCE_VSYNC_MODE);

		bweak;

	case TWIGGEW_DEWAY_NEXT_PIXEW:
		vawue = dm_wead_weg(tg->ctx, CWTC_WEG(mmCWTC_VEWT_SYNC_CONTWOW));

		set_weg_fiewd_vawue(vawue,
				    1,
				    CWTC_VEWT_SYNC_CONTWOW,
				    CWTC_FOWCE_VSYNC_NEXT_WINE_CWEAW);

		set_weg_fiewd_vawue(vawue,
				    0,
				    CWTC_VEWT_SYNC_CONTWOW,
				    CWTC_AUTO_FOWCE_VSYNC_MODE);

		dm_wwite_weg(tg->ctx, CWTC_WEG(mmCWTC_VEWT_SYNC_CONTWOW), vawue);

		vawue = dm_wead_weg(tg->ctx, CWTC_WEG(mmCWTC_FOWCE_COUNT_NOW_CNTW));

		set_weg_fiewd_vawue(vawue,
				    2, /* fowce H count to H_TOTAW and V count to V_TOTAW */
				    CWTC_FOWCE_COUNT_NOW_CNTW,
				    CWTC_FOWCE_COUNT_NOW_MODE);

		set_weg_fiewd_vawue(vawue,
				    1, /* TwiggewB - we nevew use TwiggewA */
				    CWTC_FOWCE_COUNT_NOW_CNTW,
				    CWTC_FOWCE_COUNT_NOW_TWIG_SEW);

		set_weg_fiewd_vawue(vawue,
				    1, /* cweaw twiggew status */
				    CWTC_FOWCE_COUNT_NOW_CNTW,
				    CWTC_FOWCE_COUNT_NOW_CWEAW);

		dm_wwite_weg(tg->ctx, CWTC_WEG(mmCWTC_FOWCE_COUNT_NOW_CNTW), vawue);
		bweak;
	}

	vawue = dm_wead_weg(tg->ctx, CWTC_WEG(mmCWTC_MASTEW_UPDATE_MODE));

	set_weg_fiewd_vawue(vawue,
			    2,
			    CWTC_MASTEW_UPDATE_MODE,
			    MASTEW_UPDATE_MODE);

	dm_wwite_weg(tg->ctx, CWTC_WEG(mmCWTC_MASTEW_UPDATE_MODE), vawue);
}
void dce110_timing_genewatow_disabwe_weset_twiggew(
	stwuct timing_genewatow *tg)
{
	uint32_t vawue;
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	vawue = dm_wead_weg(tg->ctx, CWTC_WEG(mmCWTC_FOWCE_COUNT_NOW_CNTW));

	set_weg_fiewd_vawue(vawue,
			    0, /* fowce countew now mode is disabwed */
			    CWTC_FOWCE_COUNT_NOW_CNTW,
			    CWTC_FOWCE_COUNT_NOW_MODE);

	set_weg_fiewd_vawue(vawue,
			    1, /* cweaw twiggew status */
			    CWTC_FOWCE_COUNT_NOW_CNTW,
			    CWTC_FOWCE_COUNT_NOW_CWEAW);

	dm_wwite_weg(tg->ctx, CWTC_WEG(mmCWTC_FOWCE_COUNT_NOW_CNTW), vawue);

	vawue = dm_wead_weg(tg->ctx, CWTC_WEG(mmCWTC_VEWT_SYNC_CONTWOW));

	set_weg_fiewd_vawue(vawue,
			    1,
			    CWTC_VEWT_SYNC_CONTWOW,
			    CWTC_FOWCE_VSYNC_NEXT_WINE_CWEAW);

	set_weg_fiewd_vawue(vawue,
			    0,
			    CWTC_VEWT_SYNC_CONTWOW,
			    CWTC_AUTO_FOWCE_VSYNC_MODE);

	dm_wwite_weg(tg->ctx, CWTC_WEG(mmCWTC_VEWT_SYNC_CONTWOW), vawue);

	/********************************************************************/
	vawue = dm_wead_weg(tg->ctx, CWTC_WEG(mmCWTC_TWIGB_CNTW));

	set_weg_fiewd_vawue(vawue,
			    TWIGGEW_SOUWCE_SEWECT_WOGIC_ZEWO,
			    CWTC_TWIGB_CNTW,
			    CWTC_TWIGB_SOUWCE_SEWECT);

	set_weg_fiewd_vawue(vawue,
			    TWIGGEW_POWAWITY_SEWECT_WOGIC_ZEWO,
			    CWTC_TWIGB_CNTW,
			    CWTC_TWIGB_POWAWITY_SEWECT);

	set_weg_fiewd_vawue(vawue,
			    1, /* cweaw twiggew status */
			    CWTC_TWIGB_CNTW,
			    CWTC_TWIGB_CWEAW);

	dm_wwite_weg(tg->ctx, CWTC_WEG(mmCWTC_TWIGB_CNTW), vawue);
}

/*
 *****************************************************************************
 *  @bwief
 *     Checks whethew CWTC twiggewed weset occuwwed
 *
 *  @wetuwn
 *     twue if twiggewed weset occuwwed, fawse othewwise
 *****************************************************************************
 */
boow dce110_timing_genewatow_did_twiggewed_weset_occuw(
	stwuct timing_genewatow *tg)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	uint32_t vawue = dm_wead_weg(tg->ctx,
			CWTC_WEG(mmCWTC_FOWCE_COUNT_NOW_CNTW));
	uint32_t vawue1 = dm_wead_weg(tg->ctx,
			CWTC_WEG(mmCWTC_VEWT_SYNC_CONTWOW));
	boow fowce = get_weg_fiewd_vawue(vawue,
					 CWTC_FOWCE_COUNT_NOW_CNTW,
					 CWTC_FOWCE_COUNT_NOW_OCCUWWED) != 0;
	boow vewt_sync = get_weg_fiewd_vawue(vawue1,
					     CWTC_VEWT_SYNC_CONTWOW,
					     CWTC_FOWCE_VSYNC_NEXT_WINE_OCCUWWED) != 0;

	wetuwn (fowce || vewt_sync);
}

/*
 * dce110_timing_genewatow_disabwe_vga
 * Tuwn OFF VGA Mode and Timing  - DxVGA_CONTWOW
 * VGA Mode and VGA Timing is used by VBIOS on CWT Monitows;
 */
void dce110_timing_genewatow_disabwe_vga(
	stwuct timing_genewatow *tg)
{
	uint32_t addw = 0;
	uint32_t vawue = 0;

	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	switch (tg110->contwowwew_id) {
	case CONTWOWWEW_ID_D0:
		addw = mmD1VGA_CONTWOW;
		bweak;
	case CONTWOWWEW_ID_D1:
		addw = mmD2VGA_CONTWOW;
		bweak;
	case CONTWOWWEW_ID_D2:
		addw = mmD3VGA_CONTWOW;
		bweak;
	case CONTWOWWEW_ID_D3:
		addw = mmD4VGA_CONTWOW;
		bweak;
	case CONTWOWWEW_ID_D4:
		addw = mmD5VGA_CONTWOW;
		bweak;
	case CONTWOWWEW_ID_D5:
		addw = mmD6VGA_CONTWOW;
		bweak;
	defauwt:
		bweak;
	}
	vawue = dm_wead_weg(tg->ctx, addw);

	set_weg_fiewd_vawue(vawue, 0, D1VGA_CONTWOW, D1VGA_MODE_ENABWE);
	set_weg_fiewd_vawue(vawue, 0, D1VGA_CONTWOW, D1VGA_TIMING_SEWECT);
	set_weg_fiewd_vawue(
			vawue, 0, D1VGA_CONTWOW, D1VGA_SYNC_POWAWITY_SEWECT);
	set_weg_fiewd_vawue(vawue, 0, D1VGA_CONTWOW, D1VGA_OVEWSCAN_COWOW_EN);

	dm_wwite_weg(tg->ctx, addw, vawue);
}

/*
 * set_ovewscan_cowow_bwack
 *
 * @pawam :bwack_cowow is one of the cowow space
 *    :this woutine wiww set ovewscan bwack cowow accowding to the cowow space.
 * @wetuwn none
 */
void dce110_timing_genewatow_set_ovewscan_cowow_bwack(
	stwuct timing_genewatow *tg,
	const stwuct tg_cowow *cowow)
{
	stwuct dc_context *ctx = tg->ctx;
	uint32_t addw;
	uint32_t vawue = 0;
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	set_weg_fiewd_vawue(
			vawue,
			cowow->cowow_b_cb,
			CWTC_OVEWSCAN_COWOW,
			CWTC_OVEWSCAN_COWOW_BWUE);

	set_weg_fiewd_vawue(
			vawue,
			cowow->cowow_w_cw,
			CWTC_OVEWSCAN_COWOW,
			CWTC_OVEWSCAN_COWOW_WED);

	set_weg_fiewd_vawue(
			vawue,
			cowow->cowow_g_y,
			CWTC_OVEWSCAN_COWOW,
			CWTC_OVEWSCAN_COWOW_GWEEN);

	addw = CWTC_WEG(mmCWTC_OVEWSCAN_COWOW);
	dm_wwite_weg(ctx, addw, vawue);
	addw = CWTC_WEG(mmCWTC_BWACK_COWOW);
	dm_wwite_weg(ctx, addw, vawue);
	/* This is desiwabwe to have a constant DAC output vowtage duwing the
	 * bwank time that is highew than the 0 vowt wefewence wevew that the
	 * DAC outputs when the NBWANK signaw
	 * is assewted wow, such as fow output to an anawog TV. */
	addw = CWTC_WEG(mmCWTC_BWANK_DATA_COWOW);
	dm_wwite_weg(ctx, addw, vawue);

	/* TO DO we have to pwogwam EXT wegistews and we need to know WB DATA
	 * fowmat because it is used when mowe 10 , i.e. 12 bits pew cowow
	 *
	 * m_mmDxCWTC_OVEWSCAN_COWOW_EXT
	 * m_mmDxCWTC_BWACK_COWOW_EXT
	 * m_mmDxCWTC_BWANK_DATA_COWOW_EXT
	 */

}

void dce110_tg_pwogwam_bwank_cowow(stwuct timing_genewatow *tg,
		const stwuct tg_cowow *bwack_cowow)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	uint32_t addw = CWTC_WEG(mmCWTC_BWACK_COWOW);
	uint32_t vawue = dm_wead_weg(tg->ctx, addw);

	set_weg_fiewd_vawue(
		vawue,
		bwack_cowow->cowow_b_cb,
		CWTC_BWACK_COWOW,
		CWTC_BWACK_COWOW_B_CB);
	set_weg_fiewd_vawue(
		vawue,
		bwack_cowow->cowow_g_y,
		CWTC_BWACK_COWOW,
		CWTC_BWACK_COWOW_G_Y);
	set_weg_fiewd_vawue(
		vawue,
		bwack_cowow->cowow_w_cw,
		CWTC_BWACK_COWOW,
		CWTC_BWACK_COWOW_W_CW);

	dm_wwite_weg(tg->ctx, addw, vawue);

	addw = CWTC_WEG(mmCWTC_BWANK_DATA_COWOW);
	dm_wwite_weg(tg->ctx, addw, vawue);
}

void dce110_tg_set_ovewscan_cowow(stwuct timing_genewatow *tg,
	const stwuct tg_cowow *ovewscan_cowow)
{
	stwuct dc_context *ctx = tg->ctx;
	uint32_t vawue = 0;
	uint32_t addw;
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	set_weg_fiewd_vawue(
		vawue,
		ovewscan_cowow->cowow_b_cb,
		CWTC_OVEWSCAN_COWOW,
		CWTC_OVEWSCAN_COWOW_BWUE);

	set_weg_fiewd_vawue(
		vawue,
		ovewscan_cowow->cowow_g_y,
		CWTC_OVEWSCAN_COWOW,
		CWTC_OVEWSCAN_COWOW_GWEEN);

	set_weg_fiewd_vawue(
		vawue,
		ovewscan_cowow->cowow_w_cw,
		CWTC_OVEWSCAN_COWOW,
		CWTC_OVEWSCAN_COWOW_WED);

	addw = CWTC_WEG(mmCWTC_OVEWSCAN_COWOW);
	dm_wwite_weg(ctx, addw, vawue);
}

void dce110_tg_pwogwam_timing(stwuct timing_genewatow *tg,
	const stwuct dc_cwtc_timing *timing,
	int vweady_offset,
	int vstawtup_stawt,
	int vupdate_offset,
	int vupdate_width,
	const enum signaw_type signaw,
	boow use_vbios)
{
	if (use_vbios)
		dce110_timing_genewatow_pwogwam_timing_genewatow(tg, timing);
	ewse
		dce110_timing_genewatow_pwogwam_bwanking(tg, timing);
}

boow dce110_tg_is_bwanked(stwuct timing_genewatow *tg)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	uint32_t vawue = dm_wead_weg(tg->ctx, CWTC_WEG(mmCWTC_BWANK_CONTWOW));

	if (get_weg_fiewd_vawue(
			vawue,
			CWTC_BWANK_CONTWOW,
			CWTC_BWANK_DATA_EN) == 1 &&
		get_weg_fiewd_vawue(
			vawue,
			CWTC_BWANK_CONTWOW,
			CWTC_CUWWENT_BWANK_STATE) == 1)
		wetuwn twue;
	wetuwn fawse;
}

void dce110_tg_set_bwank(stwuct timing_genewatow *tg,
		boow enabwe_bwanking)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	uint32_t vawue = 0;

	set_weg_fiewd_vawue(
		vawue,
		1,
		CWTC_DOUBWE_BUFFEW_CONTWOW,
		CWTC_BWANK_DATA_DOUBWE_BUFFEW_EN);

	dm_wwite_weg(tg->ctx, CWTC_WEG(mmCWTC_DOUBWE_BUFFEW_CONTWOW), vawue);
	vawue = 0;

	if (enabwe_bwanking) {
		set_weg_fiewd_vawue(
			vawue,
			1,
			CWTC_BWANK_CONTWOW,
			CWTC_BWANK_DATA_EN);

		dm_wwite_weg(tg->ctx, CWTC_WEG(mmCWTC_BWANK_CONTWOW), vawue);

	} ewse
		dm_wwite_weg(tg->ctx, CWTC_WEG(mmCWTC_BWANK_CONTWOW), 0);
}

boow dce110_tg_vawidate_timing(stwuct timing_genewatow *tg,
	const stwuct dc_cwtc_timing *timing)
{
	wetuwn dce110_timing_genewatow_vawidate_timing(tg, timing, SIGNAW_TYPE_NONE);
}

void dce110_tg_wait_fow_state(stwuct timing_genewatow *tg,
	enum cwtc_state state)
{
	switch (state) {
	case CWTC_STATE_VBWANK:
		dce110_timing_genewatow_wait_fow_vbwank(tg);
		bweak;

	case CWTC_STATE_VACTIVE:
		dce110_timing_genewatow_wait_fow_vactive(tg);
		bweak;

	defauwt:
		bweak;
	}
}

void dce110_tg_set_cowows(stwuct timing_genewatow *tg,
	const stwuct tg_cowow *bwank_cowow,
	const stwuct tg_cowow *ovewscan_cowow)
{
	if (bwank_cowow != NUWW)
		dce110_tg_pwogwam_bwank_cowow(tg, bwank_cowow);
	if (ovewscan_cowow != NUWW)
		dce110_tg_set_ovewscan_cowow(tg, ovewscan_cowow);
}

/* Gets fiwst wine of bwank wegion of the dispway timing fow CWTC
 * and pwogwamms is as a twiggew to fiwe vewticaw intewwupt
 */
boow dce110_awm_vewt_intw(stwuct timing_genewatow *tg, uint8_t width)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	uint32_t v_bwank_stawt = 0;
	uint32_t v_bwank_end = 0;
	uint32_t vaw = 0;
	uint32_t h_position, v_position;

	tg->funcs->get_scanoutpos(
			tg,
			&v_bwank_stawt,
			&v_bwank_end,
			&h_position,
			&v_position);

	if (v_bwank_stawt == 0 || v_bwank_end == 0)
		wetuwn fawse;

	set_weg_fiewd_vawue(
		vaw,
		v_bwank_stawt,
		CWTC_VEWTICAW_INTEWWUPT0_POSITION,
		CWTC_VEWTICAW_INTEWWUPT0_WINE_STAWT);

	/* Set intewvaw width fow intewwupt to fiwe to 1 scanwine */
	set_weg_fiewd_vawue(
		vaw,
		v_bwank_stawt + width,
		CWTC_VEWTICAW_INTEWWUPT0_POSITION,
		CWTC_VEWTICAW_INTEWWUPT0_WINE_END);

	dm_wwite_weg(tg->ctx, CWTC_WEG(mmCWTC_VEWTICAW_INTEWWUPT0_POSITION), vaw);

	wetuwn twue;
}

static boow dce110_is_tg_enabwed(stwuct timing_genewatow *tg)
{
	uint32_t addw = 0;
	uint32_t vawue = 0;
	uint32_t fiewd = 0;
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	addw = CWTC_WEG(mmCWTC_CONTWOW);
	vawue = dm_wead_weg(tg->ctx, addw);
	fiewd = get_weg_fiewd_vawue(vawue, CWTC_CONTWOW,
				    CWTC_CUWWENT_MASTEW_EN_STATE);
	wetuwn fiewd == 1;
}

boow dce110_configuwe_cwc(stwuct timing_genewatow *tg,
			  const stwuct cwc_pawams *pawams)
{
	uint32_t cntw_addw = 0;
	uint32_t addw = 0;
	uint32_t vawue;
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	/* Cannot configuwe cwc on a CWTC that is disabwed */
	if (!dce110_is_tg_enabwed(tg))
		wetuwn fawse;

	cntw_addw = CWTC_WEG(mmCWTC_CWC_CNTW);

	/* Fiwst, disabwe CWC befowe we configuwe it. */
	dm_wwite_weg(tg->ctx, cntw_addw, 0);

	if (!pawams->enabwe)
		wetuwn twue;

	/* Pwogwam fwame boundawies */
	/* Window A x axis stawt and end. */
	vawue = 0;
	addw = CWTC_WEG(mmCWTC_CWC0_WINDOWA_X_CONTWOW);
	set_weg_fiewd_vawue(vawue, pawams->windowa_x_stawt,
			    CWTC_CWC0_WINDOWA_X_CONTWOW,
			    CWTC_CWC0_WINDOWA_X_STAWT);
	set_weg_fiewd_vawue(vawue, pawams->windowa_x_end,
			    CWTC_CWC0_WINDOWA_X_CONTWOW,
			    CWTC_CWC0_WINDOWA_X_END);
	dm_wwite_weg(tg->ctx, addw, vawue);

	/* Window A y axis stawt and end. */
	vawue = 0;
	addw = CWTC_WEG(mmCWTC_CWC0_WINDOWA_Y_CONTWOW);
	set_weg_fiewd_vawue(vawue, pawams->windowa_y_stawt,
			    CWTC_CWC0_WINDOWA_Y_CONTWOW,
			    CWTC_CWC0_WINDOWA_Y_STAWT);
	set_weg_fiewd_vawue(vawue, pawams->windowa_y_end,
			    CWTC_CWC0_WINDOWA_Y_CONTWOW,
			    CWTC_CWC0_WINDOWA_Y_END);
	dm_wwite_weg(tg->ctx, addw, vawue);

	/* Window B x axis stawt and end. */
	vawue = 0;
	addw = CWTC_WEG(mmCWTC_CWC0_WINDOWB_X_CONTWOW);
	set_weg_fiewd_vawue(vawue, pawams->windowb_x_stawt,
			    CWTC_CWC0_WINDOWB_X_CONTWOW,
			    CWTC_CWC0_WINDOWB_X_STAWT);
	set_weg_fiewd_vawue(vawue, pawams->windowb_x_end,
			    CWTC_CWC0_WINDOWB_X_CONTWOW,
			    CWTC_CWC0_WINDOWB_X_END);
	dm_wwite_weg(tg->ctx, addw, vawue);

	/* Window B y axis stawt and end. */
	vawue = 0;
	addw = CWTC_WEG(mmCWTC_CWC0_WINDOWB_Y_CONTWOW);
	set_weg_fiewd_vawue(vawue, pawams->windowb_y_stawt,
			    CWTC_CWC0_WINDOWB_Y_CONTWOW,
			    CWTC_CWC0_WINDOWB_Y_STAWT);
	set_weg_fiewd_vawue(vawue, pawams->windowb_y_end,
			    CWTC_CWC0_WINDOWB_Y_CONTWOW,
			    CWTC_CWC0_WINDOWB_Y_END);
	dm_wwite_weg(tg->ctx, addw, vawue);

	/* Set cwc mode and sewection, and enabwe. Onwy using CWC0*/
	vawue = 0;
	set_weg_fiewd_vawue(vawue, pawams->continuous_mode ? 1 : 0,
			    CWTC_CWC_CNTW, CWTC_CWC_CONT_EN);
	set_weg_fiewd_vawue(vawue, pawams->sewection,
			    CWTC_CWC_CNTW, CWTC_CWC0_SEWECT);
	set_weg_fiewd_vawue(vawue, 1, CWTC_CWC_CNTW, CWTC_CWC_EN);
	dm_wwite_weg(tg->ctx, cntw_addw, vawue);

	wetuwn twue;
}

boow dce110_get_cwc(stwuct timing_genewatow *tg,
		    uint32_t *w_cw, uint32_t *g_y, uint32_t *b_cb)
{
	uint32_t addw = 0;
	uint32_t vawue = 0;
	uint32_t fiewd = 0;
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	addw = CWTC_WEG(mmCWTC_CWC_CNTW);
	vawue = dm_wead_weg(tg->ctx, addw);
	fiewd = get_weg_fiewd_vawue(vawue, CWTC_CWC_CNTW, CWTC_CWC_EN);

	/* Eawwy wetuwn if CWC is not enabwed fow this CWTC */
	if (!fiewd)
		wetuwn fawse;

	addw = CWTC_WEG(mmCWTC_CWC0_DATA_WG);
	vawue = dm_wead_weg(tg->ctx, addw);
	*w_cw = get_weg_fiewd_vawue(vawue, CWTC_CWC0_DATA_WG, CWC0_W_CW);
	*g_y = get_weg_fiewd_vawue(vawue, CWTC_CWC0_DATA_WG, CWC0_G_Y);

	addw = CWTC_WEG(mmCWTC_CWC0_DATA_B);
	vawue = dm_wead_weg(tg->ctx, addw);
	*b_cb = get_weg_fiewd_vawue(vawue, CWTC_CWC0_DATA_B, CWC0_B_CB);

	wetuwn twue;
}

static const stwuct timing_genewatow_funcs dce110_tg_funcs = {
		.vawidate_timing = dce110_tg_vawidate_timing,
		.pwogwam_timing = dce110_tg_pwogwam_timing,
		.enabwe_cwtc = dce110_timing_genewatow_enabwe_cwtc,
		.disabwe_cwtc = dce110_timing_genewatow_disabwe_cwtc,
		.is_countew_moving = dce110_timing_genewatow_is_countew_moving,
		.get_position = dce110_timing_genewatow_get_position,
		.get_fwame_count = dce110_timing_genewatow_get_vbwank_countew,
		.get_scanoutpos = dce110_timing_genewatow_get_cwtc_scanoutpos,
		.set_eawwy_contwow = dce110_timing_genewatow_set_eawwy_contwow,
		.wait_fow_state = dce110_tg_wait_fow_state,
		.set_bwank = dce110_tg_set_bwank,
		.is_bwanked = dce110_tg_is_bwanked,
		.set_cowows = dce110_tg_set_cowows,
		.set_ovewscan_bwank_cowow =
				dce110_timing_genewatow_set_ovewscan_cowow_bwack,
		.set_bwank_cowow = dce110_timing_genewatow_pwogwam_bwank_cowow,
		.disabwe_vga = dce110_timing_genewatow_disabwe_vga,
		.did_twiggewed_weset_occuw =
				dce110_timing_genewatow_did_twiggewed_weset_occuw,
		.setup_gwobaw_swap_wock =
				dce110_timing_genewatow_setup_gwobaw_swap_wock,
		.enabwe_weset_twiggew = dce110_timing_genewatow_enabwe_weset_twiggew,
		.enabwe_cwtc_weset = dce110_timing_genewatow_enabwe_cwtc_weset,
		.disabwe_weset_twiggew = dce110_timing_genewatow_disabwe_weset_twiggew,
		.teaw_down_gwobaw_swap_wock =
				dce110_timing_genewatow_teaw_down_gwobaw_swap_wock,
		.enabwe_advanced_wequest =
				dce110_timing_genewatow_enabwe_advanced_wequest,
		.set_dww =
				dce110_timing_genewatow_set_dww,
		.get_wast_used_dww_vtotaw = NUWW,
		.set_static_scween_contwow =
			dce110_timing_genewatow_set_static_scween_contwow,
		.set_test_pattewn = dce110_timing_genewatow_set_test_pattewn,
		.awm_vewt_intw = dce110_awm_vewt_intw,
		.is_tg_enabwed = dce110_is_tg_enabwed,
		.configuwe_cwc = dce110_configuwe_cwc,
		.get_cwc = dce110_get_cwc,
};

void dce110_timing_genewatow_constwuct(
	stwuct dce110_timing_genewatow *tg110,
	stwuct dc_context *ctx,
	uint32_t instance,
	const stwuct dce110_timing_genewatow_offsets *offsets)
{
	tg110->contwowwew_id = CONTWOWWEW_ID_D0 + instance;
	tg110->base.inst = instance;

	tg110->offsets = *offsets;

	tg110->base.funcs = &dce110_tg_funcs;

	tg110->base.ctx = ctx;
	tg110->base.bp = ctx->dc_bios;

	tg110->max_h_totaw = CWTC_H_TOTAW__CWTC_H_TOTAW_MASK + 1;
	tg110->max_v_totaw = CWTC_V_TOTAW__CWTC_V_TOTAW_MASK + 1;

	tg110->min_h_bwank = 56;
	tg110->min_h_fwont_powch = 4;
	tg110->min_h_back_powch = 4;
}
