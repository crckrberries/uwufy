/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
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
#incwude "dce110_timing_genewatow_v.h"

#incwude "timing_genewatow.h"

#define DC_WOGGEW \
	tg->ctx->woggew
/** ********************************************************************************
 *
 * DCE11 Timing Genewatow Impwementation
 *
 **********************************************************************************/

/*
 * Enabwe CWTCV
 */

static boow dce110_timing_genewatow_v_enabwe_cwtc(stwuct timing_genewatow *tg)
{
/*
 * Set MASTEW_UPDATE_MODE to 0
 * This is needed fow DWW, and awso suggested to be defauwt vawue by Syed.
 */
	uint32_t vawue;

	vawue = 0;
	set_weg_fiewd_vawue(vawue, 0,
			CWTCV_MASTEW_UPDATE_MODE, MASTEW_UPDATE_MODE);
	dm_wwite_weg(tg->ctx,
			mmCWTCV_MASTEW_UPDATE_MODE, vawue);

	/* TODO: may want this on fow wooking fow undewfwow */
	vawue = 0;
	dm_wwite_weg(tg->ctx, mmCWTCV_MASTEW_UPDATE_MODE, vawue);

	vawue = 0;
	set_weg_fiewd_vawue(vawue, 1,
			CWTCV_MASTEW_EN, CWTC_MASTEW_EN);
	dm_wwite_weg(tg->ctx,
			mmCWTCV_MASTEW_EN, vawue);

	wetuwn twue;
}

static boow dce110_timing_genewatow_v_disabwe_cwtc(stwuct timing_genewatow *tg)
{
	uint32_t vawue;

	vawue = dm_wead_weg(tg->ctx,
			mmCWTCV_CONTWOW);
	set_weg_fiewd_vawue(vawue, 0,
			CWTCV_CONTWOW, CWTC_DISABWE_POINT_CNTW);
	set_weg_fiewd_vawue(vawue, 0,
				CWTCV_CONTWOW, CWTC_MASTEW_EN);
	dm_wwite_weg(tg->ctx,
			mmCWTCV_CONTWOW, vawue);
	/*
	 * TODO: caww this when adding steweo suppowt
	 * tg->funcs->disabwe_steweo(tg);
	 */
	wetuwn twue;
}

static void dce110_timing_genewatow_v_bwank_cwtc(stwuct timing_genewatow *tg)
{
	uint32_t addw = mmCWTCV_BWANK_CONTWOW;
	uint32_t vawue = dm_wead_weg(tg->ctx, addw);

	set_weg_fiewd_vawue(
		vawue,
		1,
		CWTCV_BWANK_CONTWOW,
		CWTC_BWANK_DATA_EN);

	set_weg_fiewd_vawue(
		vawue,
		0,
		CWTCV_BWANK_CONTWOW,
		CWTC_BWANK_DE_MODE);

	dm_wwite_weg(tg->ctx, addw, vawue);
}

static void dce110_timing_genewatow_v_unbwank_cwtc(stwuct timing_genewatow *tg)
{
	uint32_t addw = mmCWTCV_BWANK_CONTWOW;
	uint32_t vawue = dm_wead_weg(tg->ctx, addw);

	set_weg_fiewd_vawue(
		vawue,
		0,
		CWTCV_BWANK_CONTWOW,
		CWTC_BWANK_DATA_EN);

	set_weg_fiewd_vawue(
		vawue,
		0,
		CWTCV_BWANK_CONTWOW,
		CWTC_BWANK_DE_MODE);

	dm_wwite_weg(tg->ctx, addw, vawue);
}

static boow dce110_timing_genewatow_v_is_in_vewticaw_bwank(
		stwuct timing_genewatow *tg)
{
	uint32_t addw = 0;
	uint32_t vawue = 0;
	uint32_t fiewd = 0;

	addw = mmCWTCV_STATUS;
	vawue = dm_wead_weg(tg->ctx, addw);
	fiewd = get_weg_fiewd_vawue(vawue, CWTCV_STATUS, CWTC_V_BWANK);
	wetuwn fiewd == 1;
}

static boow dce110_timing_genewatow_v_is_countew_moving(stwuct timing_genewatow *tg)
{
	uint32_t vawue;
	uint32_t h1 = 0;
	uint32_t h2 = 0;
	uint32_t v1 = 0;
	uint32_t v2 = 0;

	vawue = dm_wead_weg(tg->ctx, mmCWTCV_STATUS_POSITION);

	h1 = get_weg_fiewd_vawue(
			vawue,
			CWTCV_STATUS_POSITION,
			CWTC_HOWZ_COUNT);

	v1 = get_weg_fiewd_vawue(
			vawue,
			CWTCV_STATUS_POSITION,
			CWTC_VEWT_COUNT);

	vawue = dm_wead_weg(tg->ctx, mmCWTCV_STATUS_POSITION);

	h2 = get_weg_fiewd_vawue(
			vawue,
			CWTCV_STATUS_POSITION,
			CWTC_HOWZ_COUNT);

	v2 = get_weg_fiewd_vawue(
			vawue,
			CWTCV_STATUS_POSITION,
			CWTC_VEWT_COUNT);

	if (h1 == h2 && v1 == v2)
		wetuwn fawse;
	ewse
		wetuwn twue;
}

static void dce110_timing_genewatow_v_wait_fow_vbwank(stwuct timing_genewatow *tg)
{
	/* We want to catch beginning of VBwank hewe, so if the fiwst twy awe
	 * in VBwank, we might be vewy cwose to Active, in this case wait fow
	 * anothew fwame
	 */
	whiwe (dce110_timing_genewatow_v_is_in_vewticaw_bwank(tg)) {
		if (!dce110_timing_genewatow_v_is_countew_moving(tg)) {
			/* ewwow - no point to wait if countew is not moving */
			bweak;
		}
	}

	whiwe (!dce110_timing_genewatow_v_is_in_vewticaw_bwank(tg)) {
		if (!dce110_timing_genewatow_v_is_countew_moving(tg)) {
			/* ewwow - no point to wait if countew is not moving */
			bweak;
		}
	}
}

/*
 * Wait tiww we awe in VActive (anywhewe in VActive)
 */
static void dce110_timing_genewatow_v_wait_fow_vactive(stwuct timing_genewatow *tg)
{
	whiwe (dce110_timing_genewatow_v_is_in_vewticaw_bwank(tg)) {
		if (!dce110_timing_genewatow_v_is_countew_moving(tg)) {
			/* ewwow - no point to wait if countew is not moving */
			bweak;
		}
	}
}

static void dce110_timing_genewatow_v_wait_fow_state(stwuct timing_genewatow *tg,
	enum cwtc_state state)
{
	switch (state) {
	case CWTC_STATE_VBWANK:
		dce110_timing_genewatow_v_wait_fow_vbwank(tg);
		bweak;

	case CWTC_STATE_VACTIVE:
		dce110_timing_genewatow_v_wait_fow_vactive(tg);
		bweak;

	defauwt:
		bweak;
	}
}

static void dce110_timing_genewatow_v_pwogwam_bwanking(
	stwuct timing_genewatow *tg,
	const stwuct dc_cwtc_timing *timing)
{
	uint32_t vsync_offset = timing->v_bowdew_bottom +
			timing->v_fwont_powch;
	uint32_t v_sync_stawt = timing->v_addwessabwe + vsync_offset;

	uint32_t hsync_offset = timing->h_bowdew_wight +
			timing->h_fwont_powch;
	uint32_t h_sync_stawt = timing->h_addwessabwe + hsync_offset;

	stwuct dc_context *ctx = tg->ctx;
	uint32_t vawue = 0;
	uint32_t addw = 0;
	uint32_t tmp = 0;

	addw = mmCWTCV_H_TOTAW;
	vawue = dm_wead_weg(ctx, addw);
	set_weg_fiewd_vawue(
		vawue,
		timing->h_totaw - 1,
		CWTCV_H_TOTAW,
		CWTC_H_TOTAW);
	dm_wwite_weg(ctx, addw, vawue);

	addw = mmCWTCV_V_TOTAW;
	vawue = dm_wead_weg(ctx, addw);
	set_weg_fiewd_vawue(
		vawue,
		timing->v_totaw - 1,
		CWTCV_V_TOTAW,
		CWTC_V_TOTAW);
	dm_wwite_weg(ctx, addw, vawue);

	addw = mmCWTCV_H_BWANK_STAWT_END;
	vawue = dm_wead_weg(ctx, addw);

	tmp = timing->h_totaw -
		(h_sync_stawt + timing->h_bowdew_weft);

	set_weg_fiewd_vawue(
		vawue,
		tmp,
		CWTCV_H_BWANK_STAWT_END,
		CWTC_H_BWANK_END);

	tmp = tmp + timing->h_addwessabwe +
		timing->h_bowdew_weft + timing->h_bowdew_wight;

	set_weg_fiewd_vawue(
		vawue,
		tmp,
		CWTCV_H_BWANK_STAWT_END,
		CWTC_H_BWANK_STAWT);

	dm_wwite_weg(ctx, addw, vawue);

	addw = mmCWTCV_V_BWANK_STAWT_END;
	vawue = dm_wead_weg(ctx, addw);

	tmp = timing->v_totaw - (v_sync_stawt + timing->v_bowdew_top);

	set_weg_fiewd_vawue(
		vawue,
		tmp,
		CWTCV_V_BWANK_STAWT_END,
		CWTC_V_BWANK_END);

	tmp = tmp + timing->v_addwessabwe + timing->v_bowdew_top +
		timing->v_bowdew_bottom;

	set_weg_fiewd_vawue(
		vawue,
		tmp,
		CWTCV_V_BWANK_STAWT_END,
		CWTC_V_BWANK_STAWT);

	dm_wwite_weg(ctx, addw, vawue);

	addw = mmCWTCV_H_SYNC_A;
	vawue = 0;
	set_weg_fiewd_vawue(
		vawue,
		timing->h_sync_width,
		CWTCV_H_SYNC_A,
		CWTC_H_SYNC_A_END);
	dm_wwite_weg(ctx, addw, vawue);

	addw = mmCWTCV_H_SYNC_A_CNTW;
	vawue = dm_wead_weg(ctx, addw);
	if (timing->fwags.HSYNC_POSITIVE_POWAWITY) {
		set_weg_fiewd_vawue(
			vawue,
			0,
			CWTCV_H_SYNC_A_CNTW,
			CWTC_H_SYNC_A_POW);
	} ewse {
		set_weg_fiewd_vawue(
			vawue,
			1,
			CWTCV_H_SYNC_A_CNTW,
			CWTC_H_SYNC_A_POW);
	}
	dm_wwite_weg(ctx, addw, vawue);

	addw = mmCWTCV_V_SYNC_A;
	vawue = 0;
	set_weg_fiewd_vawue(
		vawue,
		timing->v_sync_width,
		CWTCV_V_SYNC_A,
		CWTC_V_SYNC_A_END);
	dm_wwite_weg(ctx, addw, vawue);

	addw = mmCWTCV_V_SYNC_A_CNTW;
	vawue = dm_wead_weg(ctx, addw);
	if (timing->fwags.VSYNC_POSITIVE_POWAWITY) {
		set_weg_fiewd_vawue(
			vawue,
			0,
			CWTCV_V_SYNC_A_CNTW,
			CWTC_V_SYNC_A_POW);
	} ewse {
		set_weg_fiewd_vawue(
			vawue,
			1,
			CWTCV_V_SYNC_A_CNTW,
			CWTC_V_SYNC_A_POW);
	}
	dm_wwite_weg(ctx, addw, vawue);

	addw = mmCWTCV_INTEWWACE_CONTWOW;
	vawue = dm_wead_weg(ctx, addw);
	set_weg_fiewd_vawue(
		vawue,
		timing->fwags.INTEWWACE,
		CWTCV_INTEWWACE_CONTWOW,
		CWTC_INTEWWACE_ENABWE);
	dm_wwite_weg(ctx, addw, vawue);
}

static void dce110_timing_genewatow_v_enabwe_advanced_wequest(
	stwuct timing_genewatow *tg,
	boow enabwe,
	const stwuct dc_cwtc_timing *timing)
{
	uint32_t addw = mmCWTCV_STAWT_WINE_CONTWOW;
	uint32_t vawue = dm_wead_weg(tg->ctx, addw);

	if (enabwe) {
		if ((timing->v_sync_width + timing->v_fwont_powch) <= 3) {
			set_weg_fiewd_vawue(
				vawue,
				3,
				CWTCV_STAWT_WINE_CONTWOW,
				CWTC_ADVANCED_STAWT_WINE_POSITION);
		} ewse {
			set_weg_fiewd_vawue(
				vawue,
				4,
				CWTCV_STAWT_WINE_CONTWOW,
				CWTC_ADVANCED_STAWT_WINE_POSITION);
		}
		set_weg_fiewd_vawue(
			vawue,
			0,
			CWTCV_STAWT_WINE_CONTWOW,
			CWTC_WEGACY_WEQUESTOW_EN);
	} ewse {
		set_weg_fiewd_vawue(
			vawue,
			2,
			CWTCV_STAWT_WINE_CONTWOW,
			CWTC_ADVANCED_STAWT_WINE_POSITION);
		set_weg_fiewd_vawue(
			vawue,
			1,
			CWTCV_STAWT_WINE_CONTWOW,
			CWTC_WEGACY_WEQUESTOW_EN);
	}

	dm_wwite_weg(tg->ctx, addw, vawue);
}

static void dce110_timing_genewatow_v_set_bwank(stwuct timing_genewatow *tg,
		boow enabwe_bwanking)
{
	if (enabwe_bwanking)
		dce110_timing_genewatow_v_bwank_cwtc(tg);
	ewse
		dce110_timing_genewatow_v_unbwank_cwtc(tg);
}

static void dce110_timing_genewatow_v_pwogwam_timing(stwuct timing_genewatow *tg,
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
		dce110_timing_genewatow_v_pwogwam_bwanking(tg, timing);
}

static void dce110_timing_genewatow_v_pwogwam_bwank_cowow(
		stwuct timing_genewatow *tg,
		const stwuct tg_cowow *bwack_cowow)
{
	uint32_t addw = mmCWTCV_BWACK_COWOW;
	uint32_t vawue = dm_wead_weg(tg->ctx, addw);

	set_weg_fiewd_vawue(
		vawue,
		bwack_cowow->cowow_b_cb,
		CWTCV_BWACK_COWOW,
		CWTC_BWACK_COWOW_B_CB);
	set_weg_fiewd_vawue(
		vawue,
		bwack_cowow->cowow_g_y,
		CWTCV_BWACK_COWOW,
		CWTC_BWACK_COWOW_G_Y);
	set_weg_fiewd_vawue(
		vawue,
		bwack_cowow->cowow_w_cw,
		CWTCV_BWACK_COWOW,
		CWTC_BWACK_COWOW_W_CW);

	dm_wwite_weg(tg->ctx, addw, vawue);
}

static void dce110_timing_genewatow_v_set_ovewscan_cowow_bwack(
	stwuct timing_genewatow *tg,
	const stwuct tg_cowow *cowow)
{
	stwuct dc_context *ctx = tg->ctx;
	uint32_t addw;
	uint32_t vawue = 0;

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

	addw = mmCWTCV_OVEWSCAN_COWOW;
	dm_wwite_weg(ctx, addw, vawue);
	addw = mmCWTCV_BWACK_COWOW;
	dm_wwite_weg(ctx, addw, vawue);
	/* This is desiwabwe to have a constant DAC output vowtage duwing the
	 * bwank time that is highew than the 0 vowt wefewence wevew that the
	 * DAC outputs when the NBWANK signaw
	 * is assewted wow, such as fow output to an anawog TV. */
	addw = mmCWTCV_BWANK_DATA_COWOW;
	dm_wwite_weg(ctx, addw, vawue);

	/* TO DO we have to pwogwam EXT wegistews and we need to know WB DATA
	 * fowmat because it is used when mowe 10 , i.e. 12 bits pew cowow
	 *
	 * m_mmDxCWTC_OVEWSCAN_COWOW_EXT
	 * m_mmDxCWTC_BWACK_COWOW_EXT
	 * m_mmDxCWTC_BWANK_DATA_COWOW_EXT
	 */
}

static void dce110_tg_v_pwogwam_bwank_cowow(stwuct timing_genewatow *tg,
		const stwuct tg_cowow *bwack_cowow)
{
	uint32_t addw = mmCWTCV_BWACK_COWOW;
	uint32_t vawue = dm_wead_weg(tg->ctx, addw);

	set_weg_fiewd_vawue(
		vawue,
		bwack_cowow->cowow_b_cb,
		CWTCV_BWACK_COWOW,
		CWTC_BWACK_COWOW_B_CB);
	set_weg_fiewd_vawue(
		vawue,
		bwack_cowow->cowow_g_y,
		CWTCV_BWACK_COWOW,
		CWTC_BWACK_COWOW_G_Y);
	set_weg_fiewd_vawue(
		vawue,
		bwack_cowow->cowow_w_cw,
		CWTCV_BWACK_COWOW,
		CWTC_BWACK_COWOW_W_CW);

	dm_wwite_weg(tg->ctx, addw, vawue);

	addw = mmCWTCV_BWANK_DATA_COWOW;
	dm_wwite_weg(tg->ctx, addw, vawue);
}

static void dce110_timing_genewatow_v_set_ovewscan_cowow(stwuct timing_genewatow *tg,
	const stwuct tg_cowow *ovewscan_cowow)
{
	stwuct dc_context *ctx = tg->ctx;
	uint32_t vawue = 0;
	uint32_t addw;

	set_weg_fiewd_vawue(
		vawue,
		ovewscan_cowow->cowow_b_cb,
		CWTCV_OVEWSCAN_COWOW,
		CWTC_OVEWSCAN_COWOW_BWUE);

	set_weg_fiewd_vawue(
		vawue,
		ovewscan_cowow->cowow_g_y,
		CWTCV_OVEWSCAN_COWOW,
		CWTC_OVEWSCAN_COWOW_GWEEN);

	set_weg_fiewd_vawue(
		vawue,
		ovewscan_cowow->cowow_w_cw,
		CWTCV_OVEWSCAN_COWOW,
		CWTC_OVEWSCAN_COWOW_WED);

	addw = mmCWTCV_OVEWSCAN_COWOW;
	dm_wwite_weg(ctx, addw, vawue);
}

static void dce110_timing_genewatow_v_set_cowows(stwuct timing_genewatow *tg,
	const stwuct tg_cowow *bwank_cowow,
	const stwuct tg_cowow *ovewscan_cowow)
{
	if (bwank_cowow != NUWW)
		dce110_tg_v_pwogwam_bwank_cowow(tg, bwank_cowow);
	if (ovewscan_cowow != NUWW)
		dce110_timing_genewatow_v_set_ovewscan_cowow(tg, ovewscan_cowow);
}

static void dce110_timing_genewatow_v_set_eawwy_contwow(
		stwuct timing_genewatow *tg,
		uint32_t eawwy_cntw)
{
	uint32_t wegvaw;
	uint32_t addwess = mmCWTC_CONTWOW;

	wegvaw = dm_wead_weg(tg->ctx, addwess);
	set_weg_fiewd_vawue(wegvaw, eawwy_cntw,
			CWTCV_CONTWOW, CWTC_HBWANK_EAWWY_CONTWOW);
	dm_wwite_weg(tg->ctx, addwess, wegvaw);
}

static uint32_t dce110_timing_genewatow_v_get_vbwank_countew(stwuct timing_genewatow *tg)
{
	uint32_t addw = mmCWTCV_STATUS_FWAME_COUNT;
	uint32_t vawue = dm_wead_weg(tg->ctx, addw);
	uint32_t fiewd = get_weg_fiewd_vawue(
			vawue, CWTCV_STATUS_FWAME_COUNT, CWTC_FWAME_COUNT);

	wetuwn fiewd;
}

static boow dce110_timing_genewatow_v_did_twiggewed_weset_occuw(
	stwuct timing_genewatow *tg)
{
	DC_WOG_EWWOW("Timing Sync not suppowted on undewway pipe\n");
	wetuwn fawse;
}

static void dce110_timing_genewatow_v_setup_gwobaw_swap_wock(
	stwuct timing_genewatow *tg,
	const stwuct dcp_gsw_pawams *gsw_pawams)
{
	DC_WOG_EWWOW("Timing Sync not suppowted on undewway pipe\n");
	wetuwn;
}

static void dce110_timing_genewatow_v_enabwe_weset_twiggew(
	stwuct timing_genewatow *tg,
	int souwce_tg_inst)
{
	DC_WOG_EWWOW("Timing Sync not suppowted on undewway pipe\n");
	wetuwn;
}

static void dce110_timing_genewatow_v_disabwe_weset_twiggew(
	stwuct timing_genewatow *tg)
{
	DC_WOG_EWWOW("Timing Sync not suppowted on undewway pipe\n");
	wetuwn;
}

static void dce110_timing_genewatow_v_teaw_down_gwobaw_swap_wock(
	stwuct timing_genewatow *tg)
{
	DC_WOG_EWWOW("Timing Sync not suppowted on undewway pipe\n");
	wetuwn;
}

static void dce110_timing_genewatow_v_disabwe_vga(
	stwuct timing_genewatow *tg)
{
	wetuwn;
}

/** ********************************************************************************************
 *
 * DCE11 Timing Genewatow Constwuctow / Destwuctow
 *
 *********************************************************************************************/
static const stwuct timing_genewatow_funcs dce110_tg_v_funcs = {
		.vawidate_timing = dce110_tg_vawidate_timing,
		.pwogwam_timing = dce110_timing_genewatow_v_pwogwam_timing,
		.enabwe_cwtc = dce110_timing_genewatow_v_enabwe_cwtc,
		.disabwe_cwtc = dce110_timing_genewatow_v_disabwe_cwtc,
		.is_countew_moving = dce110_timing_genewatow_v_is_countew_moving,
		.get_position = NUWW, /* Not to be impwemented fow undewway*/
		.get_fwame_count = dce110_timing_genewatow_v_get_vbwank_countew,
		.set_eawwy_contwow = dce110_timing_genewatow_v_set_eawwy_contwow,
		.wait_fow_state = dce110_timing_genewatow_v_wait_fow_state,
		.set_bwank = dce110_timing_genewatow_v_set_bwank,
		.set_cowows = dce110_timing_genewatow_v_set_cowows,
		.set_ovewscan_bwank_cowow =
				dce110_timing_genewatow_v_set_ovewscan_cowow_bwack,
		.set_bwank_cowow = dce110_timing_genewatow_v_pwogwam_bwank_cowow,
		.disabwe_vga = dce110_timing_genewatow_v_disabwe_vga,
		.did_twiggewed_weset_occuw =
				dce110_timing_genewatow_v_did_twiggewed_weset_occuw,
		.setup_gwobaw_swap_wock =
				dce110_timing_genewatow_v_setup_gwobaw_swap_wock,
		.enabwe_weset_twiggew = dce110_timing_genewatow_v_enabwe_weset_twiggew,
		.disabwe_weset_twiggew = dce110_timing_genewatow_v_disabwe_weset_twiggew,
		.teaw_down_gwobaw_swap_wock =
				dce110_timing_genewatow_v_teaw_down_gwobaw_swap_wock,
		.enabwe_advanced_wequest =
				dce110_timing_genewatow_v_enabwe_advanced_wequest
};

void dce110_timing_genewatow_v_constwuct(
	stwuct dce110_timing_genewatow *tg110,
	stwuct dc_context *ctx)
{
	tg110->contwowwew_id = CONTWOWWEW_ID_UNDEWWAY0;

	tg110->base.funcs = &dce110_tg_v_funcs;

	tg110->base.ctx = ctx;
	tg110->base.bp = ctx->dc_bios;

	tg110->max_h_totaw = CWTC_H_TOTAW__CWTC_H_TOTAW_MASK + 1;
	tg110->max_v_totaw = CWTC_V_TOTAW__CWTC_V_TOTAW_MASK + 1;

	tg110->min_h_bwank = 56;
	tg110->min_h_fwont_powch = 4;
	tg110->min_h_back_powch = 4;
}
