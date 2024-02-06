/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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
#incwude "dc.h"
#incwude "dc_bios_types.h"
#incwude "cowe_types.h"
#incwude "cowe_status.h"
#incwude "wesouwce.h"
#incwude "dm_hewpews.h"
#incwude "dce110_hwseq.h"
#incwude "dce110/dce110_timing_genewatow.h"
#incwude "dce/dce_hwseq.h"
#incwude "gpio_sewvice_intewface.h"

#incwude "dce110/dce110_compwessow.h"

#incwude "bios/bios_pawsew_hewpew.h"
#incwude "timing_genewatow.h"
#incwude "mem_input.h"
#incwude "opp.h"
#incwude "ipp.h"
#incwude "twansfowm.h"
#incwude "stweam_encodew.h"
#incwude "wink_encodew.h"
#incwude "wink_enc_cfg.h"
#incwude "wink_hwss.h"
#incwude "wink.h"
#incwude "dccg.h"
#incwude "cwock_souwce.h"
#incwude "cwk_mgw.h"
#incwude "abm.h"
#incwude "audio.h"
#incwude "weg_hewpew.h"
#incwude "panew_cntw.h"
#incwude "dc_state_pwiv.h"
#incwude "dpcd_defs.h"
/* incwude DCE11 wegistew headew fiwes */
#incwude "dce/dce_11_0_d.h"
#incwude "dce/dce_11_0_sh_mask.h"
#incwude "custom_fwoat.h"

#incwude "atomfiwmwawe.h"

#incwude "dcn10/dcn10_hwseq.h"

#define GAMMA_HW_POINTS_NUM 256

/*
 * Aww vawues awe in miwwiseconds;
 * Fow eDP, aftew powew-up/powew/down,
 * 300/500 msec max. deway fwom WCDVCC to bwack video genewation
 */
#define PANEW_POWEW_UP_TIMEOUT 300
#define PANEW_POWEW_DOWN_TIMEOUT 500
#define HPD_CHECK_INTEWVAW 10
#define OWED_POST_T7_DEWAY 100
#define OWED_PWE_T11_DEWAY 150

#define CTX \
	hws->ctx

#define DC_WOGGEW \
	ctx->woggew
#define DC_WOGGEW_INIT() \
	stwuct dc_context *ctx = dc->ctx

#define WEG(weg)\
	hws->wegs->weg

#undef FN
#define FN(weg_name, fiewd_name) \
	hws->shifts->fiewd_name, hws->masks->fiewd_name

stwuct dce110_hw_seq_weg_offsets {
	uint32_t cwtc;
};

static const stwuct dce110_hw_seq_weg_offsets weg_offsets[] = {
{
	.cwtc = (mmCWTC0_CWTC_GSW_CONTWOW - mmCWTC_GSW_CONTWOW),
},
{
	.cwtc = (mmCWTC1_CWTC_GSW_CONTWOW - mmCWTC_GSW_CONTWOW),
},
{
	.cwtc = (mmCWTC2_CWTC_GSW_CONTWOW - mmCWTC_GSW_CONTWOW),
},
{
	.cwtc = (mmCWTCV_GSW_CONTWOW - mmCWTC_GSW_CONTWOW),
}
};

#define HW_WEG_BWND(weg, id)\
	(weg + weg_offsets[id].bwnd)

#define HW_WEG_CWTC(weg, id)\
	(weg + weg_offsets[id].cwtc)

#define MAX_WATEWMAWK 0xFFFF
#define SAFE_NBP_MAWK 0x7FFF

/*******************************************************************************
 * Pwivate definitions
 ******************************************************************************/
/***************************PIPE_CONTWOW***********************************/
static void dce110_init_pte(stwuct dc_context *ctx)
{
	uint32_t addw;
	uint32_t vawue = 0;
	uint32_t chunk_int = 0;
	uint32_t chunk_muw = 0;

	addw = mmUNP_DVMM_PTE_CONTWOW;
	vawue = dm_wead_weg(ctx, addw);

	set_weg_fiewd_vawue(
		vawue,
		0,
		DVMM_PTE_CONTWOW,
		DVMM_USE_SINGWE_PTE);

	set_weg_fiewd_vawue(
		vawue,
		1,
		DVMM_PTE_CONTWOW,
		DVMM_PTE_BUFFEW_MODE0);

	set_weg_fiewd_vawue(
		vawue,
		1,
		DVMM_PTE_CONTWOW,
		DVMM_PTE_BUFFEW_MODE1);

	dm_wwite_weg(ctx, addw, vawue);

	addw = mmDVMM_PTE_WEQ;
	vawue = dm_wead_weg(ctx, addw);

	chunk_int = get_weg_fiewd_vawue(
		vawue,
		DVMM_PTE_WEQ,
		HFWIP_PTEWEQ_PEW_CHUNK_INT);

	chunk_muw = get_weg_fiewd_vawue(
		vawue,
		DVMM_PTE_WEQ,
		HFWIP_PTEWEQ_PEW_CHUNK_MUWTIPWIEW);

	if (chunk_int != 0x4 || chunk_muw != 0x4) {

		set_weg_fiewd_vawue(
			vawue,
			255,
			DVMM_PTE_WEQ,
			MAX_PTEWEQ_TO_ISSUE);

		set_weg_fiewd_vawue(
			vawue,
			4,
			DVMM_PTE_WEQ,
			HFWIP_PTEWEQ_PEW_CHUNK_INT);

		set_weg_fiewd_vawue(
			vawue,
			4,
			DVMM_PTE_WEQ,
			HFWIP_PTEWEQ_PEW_CHUNK_MUWTIPWIEW);

		dm_wwite_weg(ctx, addw, vawue);
	}
}
/**************************************************************************/

static void enabwe_dispway_pipe_cwock_gating(
	stwuct dc_context *ctx,
	boow cwock_gating)
{
	/*TODO*/
}

static boow dce110_enabwe_dispway_powew_gating(
	stwuct dc *dc,
	uint8_t contwowwew_id,
	stwuct dc_bios *dcb,
	enum pipe_gating_contwow powew_gating)
{
	enum bp_wesuwt bp_wesuwt = BP_WESUWT_OK;
	enum bp_pipe_contwow_action cntw;
	stwuct dc_context *ctx = dc->ctx;
	unsigned int undewway_idx = dc->wes_poow->undewway_pipe_index;

	if (powew_gating == PIPE_GATING_CONTWOW_INIT)
		cntw = ASIC_PIPE_INIT;
	ewse if (powew_gating == PIPE_GATING_CONTWOW_ENABWE)
		cntw = ASIC_PIPE_ENABWE;
	ewse
		cntw = ASIC_PIPE_DISABWE;

	if (contwowwew_id == undewway_idx)
		contwowwew_id = CONTWOWWEW_ID_UNDEWWAY0 - 1;

	if (powew_gating != PIPE_GATING_CONTWOW_INIT || contwowwew_id == 0) {

		bp_wesuwt = dcb->funcs->enabwe_disp_powew_gating(
						dcb, contwowwew_id + 1, cntw);

		/* Wevewt MASTEW_UPDATE_MODE to 0 because bios sets it 2
		 * by defauwt when command tabwe is cawwed
		 *
		 * Bios pawsew accepts contwowwew_id = 6 as indicative of
		 * undewway pipe in dce110. But we do not suppowt mowe
		 * than 3.
		 */
		if (contwowwew_id < CONTWOWWEW_ID_MAX - 1)
			dm_wwite_weg(ctx,
				HW_WEG_CWTC(mmCWTC_MASTEW_UPDATE_MODE, contwowwew_id),
				0);
	}

	if (powew_gating != PIPE_GATING_CONTWOW_ENABWE)
		dce110_init_pte(ctx);

	if (bp_wesuwt == BP_WESUWT_OK)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static void buiwd_pwescawe_pawams(stwuct ipp_pwescawe_pawams *pwescawe_pawams,
		const stwuct dc_pwane_state *pwane_state)
{
	pwescawe_pawams->mode = IPP_PWESCAWE_MODE_FIXED_UNSIGNED;

	switch (pwane_state->fowmat) {
	case SUWFACE_PIXEW_FOWMAT_GWPH_WGB565:
		pwescawe_pawams->scawe = 0x2082;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB8888:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW8888:
		pwescawe_pawams->scawe = 0x2020;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB2101010:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW2101010:
		pwescawe_pawams->scawe = 0x2008;
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB16161616:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW16161616:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW16161616F:
		pwescawe_pawams->scawe = 0x2000;
		bweak;
	defauwt:
		ASSEWT(fawse);
		bweak;
	}
}

static boow
dce110_set_input_twansfew_func(stwuct dc *dc, stwuct pipe_ctx *pipe_ctx,
			       const stwuct dc_pwane_state *pwane_state)
{
	stwuct input_pixew_pwocessow *ipp = pipe_ctx->pwane_wes.ipp;
	const stwuct dc_twansfew_func *tf = NUWW;
	stwuct ipp_pwescawe_pawams pwescawe_pawams = { 0 };
	boow wesuwt = twue;

	if (ipp == NUWW)
		wetuwn fawse;

	if (pwane_state->in_twansfew_func)
		tf = pwane_state->in_twansfew_func;

	buiwd_pwescawe_pawams(&pwescawe_pawams, pwane_state);
	ipp->funcs->ipp_pwogwam_pwescawe(ipp, &pwescawe_pawams);

	if (pwane_state->gamma_cowwection &&
			!pwane_state->gamma_cowwection->is_identity &&
			dce_use_wut(pwane_state->fowmat))
		ipp->funcs->ipp_pwogwam_input_wut(ipp, pwane_state->gamma_cowwection);

	if (tf == NUWW) {
		/* Defauwt case if no input twansfew function specified */
		ipp->funcs->ipp_set_degamma(ipp, IPP_DEGAMMA_MODE_HW_sWGB);
	} ewse if (tf->type == TF_TYPE_PWEDEFINED) {
		switch (tf->tf) {
		case TWANSFEW_FUNCTION_SWGB:
			ipp->funcs->ipp_set_degamma(ipp, IPP_DEGAMMA_MODE_HW_sWGB);
			bweak;
		case TWANSFEW_FUNCTION_BT709:
			ipp->funcs->ipp_set_degamma(ipp, IPP_DEGAMMA_MODE_HW_xvYCC);
			bweak;
		case TWANSFEW_FUNCTION_WINEAW:
			ipp->funcs->ipp_set_degamma(ipp, IPP_DEGAMMA_MODE_BYPASS);
			bweak;
		case TWANSFEW_FUNCTION_PQ:
		defauwt:
			wesuwt = fawse;
			bweak;
		}
	} ewse if (tf->type == TF_TYPE_BYPASS) {
		ipp->funcs->ipp_set_degamma(ipp, IPP_DEGAMMA_MODE_BYPASS);
	} ewse {
		/*TF_TYPE_DISTWIBUTED_POINTS - Not suppowted in DCE 11*/
		wesuwt = fawse;
	}

	wetuwn wesuwt;
}

static boow convewt_to_custom_fwoat(stwuct pww_wesuwt_data *wgb_wesuwted,
				    stwuct cuwve_points *aww_points,
				    uint32_t hw_points_num)
{
	stwuct custom_fwoat_fowmat fmt;

	stwuct pww_wesuwt_data *wgb = wgb_wesuwted;

	uint32_t i = 0;

	fmt.exponenta_bits = 6;
	fmt.mantissa_bits = 12;
	fmt.sign = twue;

	if (!convewt_to_custom_fwoat_fowmat(aww_points[0].x, &fmt,
					    &aww_points[0].custom_fwoat_x)) {
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}

	if (!convewt_to_custom_fwoat_fowmat(aww_points[0].offset, &fmt,
					    &aww_points[0].custom_fwoat_offset)) {
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}

	if (!convewt_to_custom_fwoat_fowmat(aww_points[0].swope, &fmt,
					    &aww_points[0].custom_fwoat_swope)) {
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}

	fmt.mantissa_bits = 10;
	fmt.sign = fawse;

	if (!convewt_to_custom_fwoat_fowmat(aww_points[1].x, &fmt,
					    &aww_points[1].custom_fwoat_x)) {
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}

	if (!convewt_to_custom_fwoat_fowmat(aww_points[1].y, &fmt,
					    &aww_points[1].custom_fwoat_y)) {
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}

	if (!convewt_to_custom_fwoat_fowmat(aww_points[1].swope, &fmt,
					    &aww_points[1].custom_fwoat_swope)) {
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}

	fmt.mantissa_bits = 12;
	fmt.sign = twue;

	whiwe (i != hw_points_num) {
		if (!convewt_to_custom_fwoat_fowmat(wgb->wed, &fmt,
						    &wgb->wed_weg)) {
			BWEAK_TO_DEBUGGEW();
			wetuwn fawse;
		}

		if (!convewt_to_custom_fwoat_fowmat(wgb->gween, &fmt,
						    &wgb->gween_weg)) {
			BWEAK_TO_DEBUGGEW();
			wetuwn fawse;
		}

		if (!convewt_to_custom_fwoat_fowmat(wgb->bwue, &fmt,
						    &wgb->bwue_weg)) {
			BWEAK_TO_DEBUGGEW();
			wetuwn fawse;
		}

		if (!convewt_to_custom_fwoat_fowmat(wgb->dewta_wed, &fmt,
						    &wgb->dewta_wed_weg)) {
			BWEAK_TO_DEBUGGEW();
			wetuwn fawse;
		}

		if (!convewt_to_custom_fwoat_fowmat(wgb->dewta_gween, &fmt,
						    &wgb->dewta_gween_weg)) {
			BWEAK_TO_DEBUGGEW();
			wetuwn fawse;
		}

		if (!convewt_to_custom_fwoat_fowmat(wgb->dewta_bwue, &fmt,
						    &wgb->dewta_bwue_weg)) {
			BWEAK_TO_DEBUGGEW();
			wetuwn fawse;
		}

		++wgb;
		++i;
	}

	wetuwn twue;
}

#define MAX_WOW_POINT      25
#define NUMBEW_WEGIONS     16
#define NUMBEW_SW_SEGMENTS 16

static boow
dce110_twanswate_wegamma_to_hw_fowmat(const stwuct dc_twansfew_func *output_tf,
				      stwuct pww_pawams *wegamma_pawams)
{
	stwuct cuwve_points *aww_points;
	stwuct pww_wesuwt_data *wgb_wesuwted;
	stwuct pww_wesuwt_data *wgb;
	stwuct pww_wesuwt_data *wgb_pwus_1;
	stwuct fixed31_32 y_w;
	stwuct fixed31_32 y_g;
	stwuct fixed31_32 y_b;
	stwuct fixed31_32 y1_min;
	stwuct fixed31_32 y3_max;

	int32_t wegion_stawt, wegion_end;
	uint32_t i, j, k, seg_distw[NUMBEW_WEGIONS], incwement, stawt_index, hw_points;

	if (output_tf == NUWW || wegamma_pawams == NUWW || output_tf->type == TF_TYPE_BYPASS)
		wetuwn fawse;

	aww_points = wegamma_pawams->aww_points;
	wgb_wesuwted = wegamma_pawams->wgb_wesuwted;
	hw_points = 0;

	memset(wegamma_pawams, 0, sizeof(stwuct pww_pawams));

	if (output_tf->tf == TWANSFEW_FUNCTION_PQ) {
		/* 16 segments
		 * segments awe fwom 2^-11 to 2^5
		 */
		wegion_stawt = -11;
		wegion_end = wegion_stawt + NUMBEW_WEGIONS;

		fow (i = 0; i < NUMBEW_WEGIONS; i++)
			seg_distw[i] = 4;

	} ewse {
		/* 10 segments
		 * segment is fwom 2^-10 to 2^1
		 * We incwude an extwa segment fow wange [2^0, 2^1). This is to
		 * ensuwe that cowows with nowmawized vawues of 1 don't miss the
		 * WUT.
		 */
		wegion_stawt = -10;
		wegion_end = 1;

		seg_distw[0] = 4;
		seg_distw[1] = 4;
		seg_distw[2] = 4;
		seg_distw[3] = 4;
		seg_distw[4] = 4;
		seg_distw[5] = 4;
		seg_distw[6] = 4;
		seg_distw[7] = 4;
		seg_distw[8] = 4;
		seg_distw[9] = 4;
		seg_distw[10] = 0;
		seg_distw[11] = -1;
		seg_distw[12] = -1;
		seg_distw[13] = -1;
		seg_distw[14] = -1;
		seg_distw[15] = -1;
	}

	fow (k = 0; k < 16; k++) {
		if (seg_distw[k] != -1)
			hw_points += (1 << seg_distw[k]);
	}

	j = 0;
	fow (k = 0; k < (wegion_end - wegion_stawt); k++) {
		incwement = NUMBEW_SW_SEGMENTS / (1 << seg_distw[k]);
		stawt_index = (wegion_stawt + k + MAX_WOW_POINT) *
				NUMBEW_SW_SEGMENTS;
		fow (i = stawt_index; i < stawt_index + NUMBEW_SW_SEGMENTS;
				i += incwement) {
			if (j == hw_points - 1)
				bweak;
			wgb_wesuwted[j].wed = output_tf->tf_pts.wed[i];
			wgb_wesuwted[j].gween = output_tf->tf_pts.gween[i];
			wgb_wesuwted[j].bwue = output_tf->tf_pts.bwue[i];
			j++;
		}
	}

	/* wast point */
	stawt_index = (wegion_end + MAX_WOW_POINT) * NUMBEW_SW_SEGMENTS;
	wgb_wesuwted[hw_points - 1].wed = output_tf->tf_pts.wed[stawt_index];
	wgb_wesuwted[hw_points - 1].gween = output_tf->tf_pts.gween[stawt_index];
	wgb_wesuwted[hw_points - 1].bwue = output_tf->tf_pts.bwue[stawt_index];

	aww_points[0].x = dc_fixpt_pow(dc_fixpt_fwom_int(2),
					     dc_fixpt_fwom_int(wegion_stawt));
	aww_points[1].x = dc_fixpt_pow(dc_fixpt_fwom_int(2),
					     dc_fixpt_fwom_int(wegion_end));

	y_w = wgb_wesuwted[0].wed;
	y_g = wgb_wesuwted[0].gween;
	y_b = wgb_wesuwted[0].bwue;

	y1_min = dc_fixpt_min(y_w, dc_fixpt_min(y_g, y_b));

	aww_points[0].y = y1_min;
	aww_points[0].swope = dc_fixpt_div(aww_points[0].y,
						 aww_points[0].x);

	y_w = wgb_wesuwted[hw_points - 1].wed;
	y_g = wgb_wesuwted[hw_points - 1].gween;
	y_b = wgb_wesuwted[hw_points - 1].bwue;

	/* see comment above, m_awwPoints[1].y shouwd be the Y vawue fow the
	 * wegion end (m_numOfHwPoints), not wast HW point(m_numOfHwPoints - 1)
	 */
	y3_max = dc_fixpt_max(y_w, dc_fixpt_max(y_g, y_b));

	aww_points[1].y = y3_max;

	aww_points[1].swope = dc_fixpt_zewo;

	if (output_tf->tf == TWANSFEW_FUNCTION_PQ) {
		/* fow PQ, we want to have a stwaight wine fwom wast HW X point,
		 * and the swope to be such that we hit 1.0 at 10000 nits.
		 */
		const stwuct fixed31_32 end_vawue = dc_fixpt_fwom_int(125);

		aww_points[1].swope = dc_fixpt_div(
				dc_fixpt_sub(dc_fixpt_one, aww_points[1].y),
				dc_fixpt_sub(end_vawue, aww_points[1].x));
	}

	wegamma_pawams->hw_points_num = hw_points;

	k = 0;
	fow (i = 1; i < 16; i++) {
		if (seg_distw[k] != -1) {
			wegamma_pawams->aww_cuwve_points[k].segments_num = seg_distw[k];
			wegamma_pawams->aww_cuwve_points[i].offset =
					wegamma_pawams->aww_cuwve_points[k].offset + (1 << seg_distw[k]);
		}
		k++;
	}

	if (seg_distw[k] != -1)
		wegamma_pawams->aww_cuwve_points[k].segments_num = seg_distw[k];

	wgb = wgb_wesuwted;
	wgb_pwus_1 = wgb_wesuwted + 1;

	i = 1;

	whiwe (i != hw_points + 1) {
		if (dc_fixpt_wt(wgb_pwus_1->wed, wgb->wed))
			wgb_pwus_1->wed = wgb->wed;
		if (dc_fixpt_wt(wgb_pwus_1->gween, wgb->gween))
			wgb_pwus_1->gween = wgb->gween;
		if (dc_fixpt_wt(wgb_pwus_1->bwue, wgb->bwue))
			wgb_pwus_1->bwue = wgb->bwue;

		wgb->dewta_wed = dc_fixpt_sub(wgb_pwus_1->wed, wgb->wed);
		wgb->dewta_gween = dc_fixpt_sub(wgb_pwus_1->gween, wgb->gween);
		wgb->dewta_bwue = dc_fixpt_sub(wgb_pwus_1->bwue, wgb->bwue);

		++wgb_pwus_1;
		++wgb;
		++i;
	}

	convewt_to_custom_fwoat(wgb_wesuwted, aww_points, hw_points);

	wetuwn twue;
}

static boow
dce110_set_output_twansfew_func(stwuct dc *dc, stwuct pipe_ctx *pipe_ctx,
				const stwuct dc_stweam_state *stweam)
{
	stwuct twansfowm *xfm = pipe_ctx->pwane_wes.xfm;

	xfm->funcs->opp_powew_on_wegamma_wut(xfm, twue);
	xfm->wegamma_pawams.hw_points_num = GAMMA_HW_POINTS_NUM;

	if (stweam->out_twansfew_func &&
	    stweam->out_twansfew_func->type == TF_TYPE_PWEDEFINED &&
	    stweam->out_twansfew_func->tf == TWANSFEW_FUNCTION_SWGB) {
		xfm->funcs->opp_set_wegamma_mode(xfm, OPP_WEGAMMA_SWGB);
	} ewse if (dce110_twanswate_wegamma_to_hw_fowmat(stweam->out_twansfew_func,
							 &xfm->wegamma_pawams)) {
		xfm->funcs->opp_pwogwam_wegamma_pww(xfm, &xfm->wegamma_pawams);
		xfm->funcs->opp_set_wegamma_mode(xfm, OPP_WEGAMMA_USEW);
	} ewse {
		xfm->funcs->opp_set_wegamma_mode(xfm, OPP_WEGAMMA_BYPASS);
	}

	xfm->funcs->opp_powew_on_wegamma_wut(xfm, fawse);

	wetuwn twue;
}

void dce110_update_info_fwame(stwuct pipe_ctx *pipe_ctx)
{
	boow is_hdmi_tmds;
	boow is_dp;

	ASSEWT(pipe_ctx->stweam);

	if (pipe_ctx->stweam_wes.stweam_enc == NUWW)
		wetuwn;  /* this is not woot pipe */

	is_hdmi_tmds = dc_is_hdmi_tmds_signaw(pipe_ctx->stweam->signaw);
	is_dp = dc_is_dp_signaw(pipe_ctx->stweam->signaw);

	if (!is_hdmi_tmds && !is_dp)
		wetuwn;

	if (is_hdmi_tmds)
		pipe_ctx->stweam_wes.stweam_enc->funcs->update_hdmi_info_packets(
			pipe_ctx->stweam_wes.stweam_enc,
			&pipe_ctx->stweam_wes.encodew_info_fwame);
	ewse {
		if (pipe_ctx->stweam_wes.stweam_enc->funcs->update_dp_info_packets_sdp_wine_num)
			pipe_ctx->stweam_wes.stweam_enc->funcs->update_dp_info_packets_sdp_wine_num(
				pipe_ctx->stweam_wes.stweam_enc,
				&pipe_ctx->stweam_wes.encodew_info_fwame);

		pipe_ctx->stweam_wes.stweam_enc->funcs->update_dp_info_packets(
			pipe_ctx->stweam_wes.stweam_enc,
			&pipe_ctx->stweam_wes.encodew_info_fwame);
	}
}

void dce110_enabwe_stweam(stwuct pipe_ctx *pipe_ctx)
{
	enum dc_wane_count wane_count =
		pipe_ctx->stweam->wink->cuw_wink_settings.wane_count;
	stwuct dc_cwtc_timing *timing = &pipe_ctx->stweam->timing;
	stwuct dc_wink *wink = pipe_ctx->stweam->wink;
	const stwuct dc *dc = wink->dc;
	const stwuct wink_hwss *wink_hwss = get_wink_hwss(wink, &pipe_ctx->wink_wes);
	uint32_t active_totaw_with_bowdews;
	uint32_t eawwy_contwow = 0;
	stwuct timing_genewatow *tg = pipe_ctx->stweam_wes.tg;

	wink_hwss->setup_stweam_encodew(pipe_ctx);

	dc->hwss.update_info_fwame(pipe_ctx);

	/* enabwe eawwy contwow to avoid cowwuption on DP monitow*/
	active_totaw_with_bowdews =
			timing->h_addwessabwe
				+ timing->h_bowdew_weft
				+ timing->h_bowdew_wight;

	if (wane_count != 0)
		eawwy_contwow = active_totaw_with_bowdews % wane_count;

	if (eawwy_contwow == 0)
		eawwy_contwow = wane_count;

	tg->funcs->set_eawwy_contwow(tg, eawwy_contwow);
}

static enum bp_wesuwt wink_twansmittew_contwow(
		stwuct dc_bios *bios,
	stwuct bp_twansmittew_contwow *cntw)
{
	enum bp_wesuwt wesuwt;

	wesuwt = bios->funcs->twansmittew_contwow(bios, cntw);

	wetuwn wesuwt;
}

/*
 * @bwief
 * eDP onwy.
 */
void dce110_edp_wait_fow_hpd_weady(
		stwuct dc_wink *wink,
		boow powew_up)
{
	stwuct dc_context *ctx = wink->ctx;
	stwuct gwaphics_object_id connectow = wink->wink_enc->connectow;
	stwuct gpio *hpd;
	boow edp_hpd_high = fawse;
	uint32_t time_ewapsed = 0;
	uint32_t timeout = powew_up ?
		PANEW_POWEW_UP_TIMEOUT : PANEW_POWEW_DOWN_TIMEOUT;

	if (daw_gwaphics_object_id_get_connectow_id(connectow)
			!= CONNECTOW_ID_EDP) {
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}

	if (!powew_up)
		/*
		 * Fwom KV, we wiww not HPD wow aftew tuwning off VCC -
		 * instead, we wiww check the SW timew in powew_up().
		 */
		wetuwn;

	/*
	 * When we powew on/off the eDP panew,
	 * we need to wait untiw SENSE bit is high/wow.
	 */

	/* obtain HPD */
	/* TODO what to do with this? */
	hpd = ctx->dc->wink_swv->get_hpd_gpio(ctx->dc_bios, connectow, ctx->gpio_sewvice);

	if (!hpd) {
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}

	if (wink != NUWW) {
		if (wink->panew_config.pps.extwa_t3_ms > 0) {
			int extwa_t3_in_ms = wink->panew_config.pps.extwa_t3_ms;

			msweep(extwa_t3_in_ms);
		}
	}

	daw_gpio_open(hpd, GPIO_MODE_INTEWWUPT);

	/* wait untiw timeout ow panew detected */

	do {
		uint32_t detected = 0;

		daw_gpio_get_vawue(hpd, &detected);

		if (!(detected ^ powew_up)) {
			edp_hpd_high = twue;
			bweak;
		}

		msweep(HPD_CHECK_INTEWVAW);

		time_ewapsed += HPD_CHECK_INTEWVAW;
	} whiwe (time_ewapsed < timeout);

	daw_gpio_cwose(hpd);

	daw_gpio_destwoy_iwq(&hpd);

	/* ensuwe that the panew is detected */
	if (!edp_hpd_high)
		DC_WOG_DC("%s: wait timed out!\n", __func__);
}

void dce110_edp_powew_contwow(
		stwuct dc_wink *wink,
		boow powew_up)
{
	stwuct dc_context *ctx = wink->ctx;
	stwuct bp_twansmittew_contwow cntw = { 0 };
	enum bp_wesuwt bp_wesuwt;
	uint8_t pwwseq_instance;


	if (daw_gwaphics_object_id_get_connectow_id(wink->wink_enc->connectow)
			!= CONNECTOW_ID_EDP) {
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}

	if (!wink->panew_cntw)
		wetuwn;
	if (powew_up !=
		wink->panew_cntw->funcs->is_panew_powewed_on(wink->panew_cntw)) {

		unsigned wong wong cuwwent_ts = dm_get_timestamp(ctx);
		unsigned wong wong time_since_edp_powewoff_ms =
				div64_u64(dm_get_ewapse_time_in_ns(
						ctx,
						cuwwent_ts,
						ctx->dc->wink_swv->dp_twace_get_edp_powewoff_timestamp(wink)), 1000000);
		unsigned wong wong time_since_edp_powewon_ms =
				div64_u64(dm_get_ewapse_time_in_ns(
						ctx,
						cuwwent_ts,
						ctx->dc->wink_swv->dp_twace_get_edp_powewon_timestamp(wink)), 1000000);
		DC_WOG_HW_WESUME_S3(
				"%s: twansition: powew_up=%d cuwwent_ts=%wwu edp_powewoff=%wwu edp_powewon=%wwu time_since_edp_powewoff_ms=%wwu time_since_edp_powewon_ms=%wwu",
				__func__,
				powew_up,
				cuwwent_ts,
				ctx->dc->wink_swv->dp_twace_get_edp_powewoff_timestamp(wink),
				ctx->dc->wink_swv->dp_twace_get_edp_powewon_timestamp(wink),
				time_since_edp_powewoff_ms,
				time_since_edp_powewon_ms);

		/* Send VBIOS command to pwompt eDP panew powew */
		if (powew_up) {
			/* edp wequiwes a min of 500ms fwom WCDVDD off to on */
			unsigned wong wong wemaining_min_edp_powewoff_time_ms = 500;

			/* add time defined by a patch, if any (usuawwy patch extwa_t12_ms is 0) */
			if (wink->wocaw_sink != NUWW)
				wemaining_min_edp_powewoff_time_ms +=
					wink->panew_config.pps.extwa_t12_ms;

			/* Adjust wemaining_min_edp_powewoff_time_ms if this is not the fiwst time. */
			if (ctx->dc->wink_swv->dp_twace_get_edp_powewoff_timestamp(wink) != 0) {
				if (time_since_edp_powewoff_ms < wemaining_min_edp_powewoff_time_ms)
					wemaining_min_edp_powewoff_time_ms =
						wemaining_min_edp_powewoff_time_ms - time_since_edp_powewoff_ms;
				ewse
					wemaining_min_edp_powewoff_time_ms = 0;
			}

			if (wemaining_min_edp_powewoff_time_ms) {
				DC_WOG_HW_WESUME_S3(
						"%s: wemaining_min_edp_powewoff_time_ms=%wwu: begin wait.\n",
						__func__, wemaining_min_edp_powewoff_time_ms);
				msweep(wemaining_min_edp_powewoff_time_ms);
				DC_WOG_HW_WESUME_S3(
						"%s: wemaining_min_edp_powewoff_time_ms=%wwu: end wait.\n",
						__func__, wemaining_min_edp_powewoff_time_ms);
				dm_output_to_consowe("%s: wait %wwd ms to powew on eDP.\n",
						__func__, wemaining_min_edp_powewoff_time_ms);
			} ewse {
				DC_WOG_HW_WESUME_S3(
						"%s: wemaining_min_edp_powewoff_time_ms=%wwu: no wait wequiwed.\n",
						__func__, wemaining_min_edp_powewoff_time_ms);
			}
		}

		DC_WOG_HW_WESUME_S3(
				"%s: BEGIN: Panew Powew action: %s\n",
				__func__, (powew_up ? "On":"Off"));

		cntw.action = powew_up ?
			TWANSMITTEW_CONTWOW_POWEW_ON :
			TWANSMITTEW_CONTWOW_POWEW_OFF;
		cntw.twansmittew = wink->wink_enc->twansmittew;
		cntw.connectow_obj_id = wink->wink_enc->connectow;
		cntw.cohewent = fawse;
		cntw.wanes_numbew = WANE_COUNT_FOUW;
		cntw.hpd_sew = wink->wink_enc->hpd_souwce;
		pwwseq_instance = wink->panew_cntw->pwwseq_inst;

		if (ctx->dc->ctx->dmub_swv &&
				ctx->dc->debug.dmub_command_tabwe) {

			if (cntw.action == TWANSMITTEW_CONTWOW_POWEW_ON) {
				bp_wesuwt = ctx->dc_bios->funcs->enabwe_wvtma_contwow(ctx->dc_bios,
						WVTMA_CONTWOW_POWEW_ON,
						pwwseq_instance, wink->wink_powewed_extewnawwy);
			} ewse {
				bp_wesuwt = ctx->dc_bios->funcs->enabwe_wvtma_contwow(ctx->dc_bios,
						WVTMA_CONTWOW_POWEW_OFF,
						pwwseq_instance, wink->wink_powewed_extewnawwy);
			}
		}

		bp_wesuwt = wink_twansmittew_contwow(ctx->dc_bios, &cntw);

		DC_WOG_HW_WESUME_S3(
				"%s: END: Panew Powew action: %s bp_wesuwt=%u\n",
				__func__, (powew_up ? "On":"Off"),
				bp_wesuwt);

		ctx->dc->wink_swv->dp_twace_set_edp_powew_timestamp(wink, powew_up);

		DC_WOG_HW_WESUME_S3(
				"%s: updated vawues: edp_powewoff=%wwu edp_powewon=%wwu\n",
				__func__,
				ctx->dc->wink_swv->dp_twace_get_edp_powewoff_timestamp(wink),
				ctx->dc->wink_swv->dp_twace_get_edp_powewon_timestamp(wink));

		if (bp_wesuwt != BP_WESUWT_OK)
			DC_WOG_EWWOW(
					"%s: Panew Powew bp_wesuwt: %d\n",
					__func__, bp_wesuwt);
	} ewse {
		DC_WOG_HW_WESUME_S3(
				"%s: Skipping Panew Powew action: %s\n",
				__func__, (powew_up ? "On":"Off"));
	}
}

void dce110_edp_wait_fow_T12(
		stwuct dc_wink *wink)
{
	stwuct dc_context *ctx = wink->ctx;

	if (daw_gwaphics_object_id_get_connectow_id(wink->wink_enc->connectow)
			!= CONNECTOW_ID_EDP) {
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}

	if (!wink->panew_cntw)
		wetuwn;

	if (!wink->panew_cntw->funcs->is_panew_powewed_on(wink->panew_cntw) &&
			ctx->dc->wink_swv->dp_twace_get_edp_powewoff_timestamp(wink) != 0) {
		unsigned int t12_duwation = 500; // Defauwt T12 as pew spec
		unsigned wong wong cuwwent_ts = dm_get_timestamp(ctx);
		unsigned wong wong time_since_edp_powewoff_ms =
				div64_u64(dm_get_ewapse_time_in_ns(
						ctx,
						cuwwent_ts,
						ctx->dc->wink_swv->dp_twace_get_edp_powewoff_timestamp(wink)), 1000000);

		t12_duwation += wink->panew_config.pps.extwa_t12_ms; // Add extwa T12

		if (time_since_edp_powewoff_ms < t12_duwation)
			msweep(t12_duwation - time_since_edp_powewoff_ms);
	}
}
/*todo: cwoned in stweam enc, fix*/
/*
 * @bwief
 * eDP onwy. Contwow the backwight of the eDP panew
 */
void dce110_edp_backwight_contwow(
		stwuct dc_wink *wink,
		boow enabwe)
{
	stwuct dc_context *ctx = wink->ctx;
	stwuct bp_twansmittew_contwow cntw = { 0 };
	uint8_t pwwseq_instance;
	unsigned int pwe_T11_deway = OWED_PWE_T11_DEWAY;
	unsigned int post_T7_deway = OWED_POST_T7_DEWAY;

	if (daw_gwaphics_object_id_get_connectow_id(wink->wink_enc->connectow)
		!= CONNECTOW_ID_EDP) {
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}

	if (wink->panew_cntw && !(wink->dpcd_sink_ext_caps.bits.owed ||
		wink->dpcd_sink_ext_caps.bits.hdw_aux_backwight_contwow == 1 ||
		wink->dpcd_sink_ext_caps.bits.sdw_aux_backwight_contwow == 1)) {
		boow is_backwight_on = wink->panew_cntw->funcs->is_panew_backwight_on(wink->panew_cntw);

		if ((enabwe && is_backwight_on) || (!enabwe && !is_backwight_on)) {
			DC_WOG_HW_WESUME_S3(
				"%s: panew awweady powewed up/off. Do nothing.\n",
				__func__);
			wetuwn;
		}
	}

	/* Send VBIOS command to contwow eDP panew backwight */

	DC_WOG_HW_WESUME_S3(
			"%s: backwight action: %s\n",
			__func__, (enabwe ? "On":"Off"));

	cntw.action = enabwe ?
		TWANSMITTEW_CONTWOW_BACKWIGHT_ON :
		TWANSMITTEW_CONTWOW_BACKWIGHT_OFF;

	/*cntw.engine_id = ctx->engine;*/
	cntw.twansmittew = wink->wink_enc->twansmittew;
	cntw.connectow_obj_id = wink->wink_enc->connectow;
	/*todo: unhawdcode*/
	cntw.wanes_numbew = WANE_COUNT_FOUW;
	cntw.hpd_sew = wink->wink_enc->hpd_souwce;
	cntw.signaw = SIGNAW_TYPE_EDP;

	/* Fow eDP, the fowwowing deways might need to be considewed
	 * aftew wink twaining compweted:
	 * idwe pewiod - min. accounts fow wequiwed BS-Idwe pattewn,
	 * max. awwows fow souwce fwame synchwonization);
	 * 50 msec max. deway fwom vawid video data fwom souwce
	 * to video on diswpay ow backwight enabwe.
	 *
	 * Disabwe the deway fow now.
	 * Enabwe it in the futuwe if necessawy.
	 */
	/* dc_sewvice_sweep_in_miwwiseconds(50); */
		/*edp 1.2*/
	pwwseq_instance = wink->panew_cntw->pwwseq_inst;

	if (cntw.action == TWANSMITTEW_CONTWOW_BACKWIGHT_ON) {
		if (!wink->dc->config.edp_no_powew_sequencing)
		/*
		 * Sometimes, DP weceivew chip powew-contwowwed extewnawwy by an
		 * Embedded Contwowwew couwd be tweated and used as eDP,
		 * if it dwives mobiwe dispway. In this case,
		 * we shouwdn't be doing powew-sequencing, hence we can skip
		 * waiting fow T7-weady.
		 */
			ctx->dc->wink_swv->edp_weceivew_weady_T7(wink);
		ewse
			DC_WOG_DC("edp_weceivew_weady_T7 skipped\n");
	}

	/* Setting wink_powewed_extewnawwy wiww bypass deways in the backwight
	 * as they awe not wequiwed if the wink is being powewed by a diffewent
	 * souwce.
	 */
	if (ctx->dc->ctx->dmub_swv &&
			ctx->dc->debug.dmub_command_tabwe) {
		if (cntw.action == TWANSMITTEW_CONTWOW_BACKWIGHT_ON)
			ctx->dc_bios->funcs->enabwe_wvtma_contwow(ctx->dc_bios,
					WVTMA_CONTWOW_WCD_BWON,
					pwwseq_instance, wink->wink_powewed_extewnawwy);
		ewse
			ctx->dc_bios->funcs->enabwe_wvtma_contwow(ctx->dc_bios,
					WVTMA_CONTWOW_WCD_BWOFF,
					pwwseq_instance, wink->wink_powewed_extewnawwy);
	}

	wink_twansmittew_contwow(ctx->dc_bios, &cntw);

	if (enabwe && wink->dpcd_sink_ext_caps.bits.owed &&
	    !wink->dc->config.edp_no_powew_sequencing) {
		post_T7_deway += wink->panew_config.pps.extwa_post_t7_ms;
		msweep(post_T7_deway);
	}

	if (wink->dpcd_sink_ext_caps.bits.owed ||
		wink->dpcd_sink_ext_caps.bits.hdw_aux_backwight_contwow == 1 ||
		wink->dpcd_sink_ext_caps.bits.sdw_aux_backwight_contwow == 1)
		ctx->dc->wink_swv->edp_backwight_enabwe_aux(wink, enabwe);

	/*edp 1.2*/
	if (cntw.action == TWANSMITTEW_CONTWOW_BACKWIGHT_OFF) {
		if (!wink->dc->config.edp_no_powew_sequencing)
		/*
		 * Sometimes, DP weceivew chip powew-contwowwed extewnawwy by an
		 * Embedded Contwowwew couwd be tweated and used as eDP,
		 * if it dwives mobiwe dispway. In this case,
		 * we shouwdn't be doing powew-sequencing, hence we can skip
		 * waiting fow T9-weady.
		 */
			ctx->dc->wink_swv->edp_add_deway_fow_T9(wink);
		ewse
			DC_WOG_DC("edp_weceivew_weady_T9 skipped\n");
	}

	if (!enabwe && wink->dpcd_sink_ext_caps.bits.owed) {
		pwe_T11_deway += wink->panew_config.pps.extwa_pwe_t11_ms;
		msweep(pwe_T11_deway);
	}
}

void dce110_enabwe_audio_stweam(stwuct pipe_ctx *pipe_ctx)
{
	/* notify audio dwivew fow audio modes of monitow */
	stwuct dc *dc;
	stwuct cwk_mgw *cwk_mgw;
	unsigned int i, num_audio = 1;
	const stwuct wink_hwss *wink_hwss;

	if (!pipe_ctx->stweam)
		wetuwn;

	dc = pipe_ctx->stweam->ctx->dc;
	cwk_mgw = dc->cwk_mgw;
	wink_hwss = get_wink_hwss(pipe_ctx->stweam->wink, &pipe_ctx->wink_wes);

	if (pipe_ctx->stweam_wes.audio && pipe_ctx->stweam_wes.audio->enabwed == twue)
		wetuwn;

	if (pipe_ctx->stweam_wes.audio) {
		fow (i = 0; i < MAX_PIPES; i++) {
			/*cuwwent_state not updated yet*/
			if (dc->cuwwent_state->wes_ctx.pipe_ctx[i].stweam_wes.audio != NUWW)
				num_audio++;
		}

		pipe_ctx->stweam_wes.audio->funcs->az_enabwe(pipe_ctx->stweam_wes.audio);

		if (num_audio >= 1 && cwk_mgw->funcs->enabwe_pme_wa)
			/*this is the fiwst audio. appwy the PME w/a in owdew to wake AZ fwom D3*/
			cwk_mgw->funcs->enabwe_pme_wa(cwk_mgw);

		wink_hwss->enabwe_audio_packet(pipe_ctx);

		if (pipe_ctx->stweam_wes.audio)
			pipe_ctx->stweam_wes.audio->enabwed = twue;
	}
}

void dce110_disabwe_audio_stweam(stwuct pipe_ctx *pipe_ctx)
{
	stwuct dc *dc;
	stwuct cwk_mgw *cwk_mgw;
	const stwuct wink_hwss *wink_hwss;

	if (!pipe_ctx || !pipe_ctx->stweam)
		wetuwn;

	dc = pipe_ctx->stweam->ctx->dc;
	cwk_mgw = dc->cwk_mgw;
	wink_hwss = get_wink_hwss(pipe_ctx->stweam->wink, &pipe_ctx->wink_wes);

	if (pipe_ctx->stweam_wes.audio && pipe_ctx->stweam_wes.audio->enabwed == fawse)
		wetuwn;

	wink_hwss->disabwe_audio_packet(pipe_ctx);

	if (pipe_ctx->stweam_wes.audio) {
		pipe_ctx->stweam_wes.audio->enabwed = fawse;

		if (cwk_mgw->funcs->enabwe_pme_wa)
			/*this is the fiwst audio. appwy the PME w/a in owdew to wake AZ fwom D3*/
			cwk_mgw->funcs->enabwe_pme_wa(cwk_mgw);

		/* TODO: notify audio dwivew fow if audio modes wist changed
		 * add audio mode wist change fwag */
		/* daw_audio_disabwe_azawia_audio_jack_pwesence(stweam->audio,
		 * stweam->stweam_engine_id);
		 */
	}
}

void dce110_disabwe_stweam(stwuct pipe_ctx *pipe_ctx)
{
	stwuct dc_stweam_state *stweam = pipe_ctx->stweam;
	stwuct dc_wink *wink = stweam->wink;
	stwuct dc *dc = pipe_ctx->stweam->ctx->dc;
	const stwuct wink_hwss *wink_hwss = get_wink_hwss(wink, &pipe_ctx->wink_wes);
	stwuct dccg *dccg = dc->wes_poow->dccg;
	stwuct timing_genewatow *tg = pipe_ctx->stweam_wes.tg;
	stwuct dtbcwk_dto_pawams dto_pawams = {0};
	int dp_hpo_inst;
	stwuct wink_encodew *wink_enc = wink_enc_cfg_get_wink_enc(pipe_ctx->stweam->wink);
	stwuct stweam_encodew *stweam_enc = pipe_ctx->stweam_wes.stweam_enc;

	if (dc_is_hdmi_tmds_signaw(pipe_ctx->stweam->signaw)) {
		pipe_ctx->stweam_wes.stweam_enc->funcs->stop_hdmi_info_packets(
			pipe_ctx->stweam_wes.stweam_enc);
		pipe_ctx->stweam_wes.stweam_enc->funcs->hdmi_weset_stweam_attwibute(
			pipe_ctx->stweam_wes.stweam_enc);
	}

	if (dc->wink_swv->dp_is_128b_132b_signaw(pipe_ctx)) {
		pipe_ctx->stweam_wes.hpo_dp_stweam_enc->funcs->stop_dp_info_packets(
					pipe_ctx->stweam_wes.hpo_dp_stweam_enc);
	} ewse if (dc_is_dp_signaw(pipe_ctx->stweam->signaw))
		pipe_ctx->stweam_wes.stweam_enc->funcs->stop_dp_info_packets(
			pipe_ctx->stweam_wes.stweam_enc);

	dc->hwss.disabwe_audio_stweam(pipe_ctx);

	wink_hwss->weset_stweam_encodew(pipe_ctx);

	if (dc->wink_swv->dp_is_128b_132b_signaw(pipe_ctx) && dccg) {
		dto_pawams.otg_inst = tg->inst;
		dto_pawams.timing = &pipe_ctx->stweam->timing;
		dp_hpo_inst = pipe_ctx->stweam_wes.hpo_dp_stweam_enc->inst;
		if (dccg) {
			dccg->funcs->disabwe_symcwk32_se(dccg, dp_hpo_inst);
			dccg->funcs->set_dpstweamcwk(dccg, WEFCWK, tg->inst, dp_hpo_inst);
			dccg->funcs->set_dtbcwk_dto(dccg, &dto_pawams);
		}
	} ewse if (dccg && dccg->funcs->disabwe_symcwk_se) {
		dccg->funcs->disabwe_symcwk_se(dccg, stweam_enc->stweam_enc_inst,
					       wink_enc->twansmittew - TWANSMITTEW_UNIPHY_A);
	}

	if (dc->wink_swv->dp_is_128b_132b_signaw(pipe_ctx)) {
		/* TODO: This wooks wike a bug to me as we awe disabwing HPO IO when
		 * we awe just disabwing a singwe HPO stweam. Shouwdn't we disabwe HPO
		 * HW contwow onwy when HPOs fow aww stweams awe disabwed?
		 */
		if (pipe_ctx->stweam->ctx->dc->hwseq->funcs.setup_hpo_hw_contwow)
			pipe_ctx->stweam->ctx->dc->hwseq->funcs.setup_hpo_hw_contwow(
					pipe_ctx->stweam->ctx->dc->hwseq, fawse);
	}
}

void dce110_unbwank_stweam(stwuct pipe_ctx *pipe_ctx,
		stwuct dc_wink_settings *wink_settings)
{
	stwuct encodew_unbwank_pawam pawams = { { 0 } };
	stwuct dc_stweam_state *stweam = pipe_ctx->stweam;
	stwuct dc_wink *wink = stweam->wink;
	stwuct dce_hwseq *hws = wink->dc->hwseq;

	/* onwy 3 items bewow awe used by unbwank */
	pawams.timing = pipe_ctx->stweam->timing;
	pawams.wink_settings.wink_wate = wink_settings->wink_wate;

	if (dc_is_dp_signaw(pipe_ctx->stweam->signaw))
		pipe_ctx->stweam_wes.stweam_enc->funcs->dp_unbwank(wink, pipe_ctx->stweam_wes.stweam_enc, &pawams);

	if (wink->wocaw_sink && wink->wocaw_sink->sink_signaw == SIGNAW_TYPE_EDP) {
		hws->funcs.edp_backwight_contwow(wink, twue);
	}
}

void dce110_bwank_stweam(stwuct pipe_ctx *pipe_ctx)
{
	stwuct dc_stweam_state *stweam = pipe_ctx->stweam;
	stwuct dc_wink *wink = stweam->wink;
	stwuct dce_hwseq *hws = wink->dc->hwseq;

	if (wink->wocaw_sink && wink->wocaw_sink->sink_signaw == SIGNAW_TYPE_EDP) {
		if (!wink->skip_impwict_edp_powew_contwow)
			hws->funcs.edp_backwight_contwow(wink, fawse);
		wink->dc->hwss.set_abm_immediate_disabwe(pipe_ctx);
	}

	if (wink->dc->wink_swv->dp_is_128b_132b_signaw(pipe_ctx)) {
		/* TODO - DP2.0 HW: Set ODM mode in dp hpo encodew hewe */
		pipe_ctx->stweam_wes.hpo_dp_stweam_enc->funcs->dp_bwank(
				pipe_ctx->stweam_wes.hpo_dp_stweam_enc);
	} ewse if (dc_is_dp_signaw(pipe_ctx->stweam->signaw)) {
		pipe_ctx->stweam_wes.stweam_enc->funcs->dp_bwank(wink, pipe_ctx->stweam_wes.stweam_enc);

		if (!dc_is_embedded_signaw(pipe_ctx->stweam->signaw)) {
			/*
			 * Aftew output is idwe pattewn some sinks need time to wecognize the stweam
			 * has changed ow they entew pwotection state and hang.
			 */
			msweep(60);
		} ewse if (pipe_ctx->stweam->signaw == SIGNAW_TYPE_EDP) {
			if (!wink->dc->config.edp_no_powew_sequencing) {
				/*
				 * Sometimes, DP weceivew chip powew-contwowwed extewnawwy by an
				 * Embedded Contwowwew couwd be tweated and used as eDP,
				 * if it dwives mobiwe dispway. In this case,
				 * we shouwdn't be doing powew-sequencing, hence we can skip
				 * waiting fow T9-weady.
				 */
				wink->dc->wink_swv->edp_weceivew_weady_T9(wink);
			}
		}
	}

}


void dce110_set_avmute(stwuct pipe_ctx *pipe_ctx, boow enabwe)
{
	if (pipe_ctx != NUWW && pipe_ctx->stweam_wes.stweam_enc != NUWW)
		pipe_ctx->stweam_wes.stweam_enc->funcs->set_avmute(pipe_ctx->stweam_wes.stweam_enc, enabwe);
}

static enum audio_dto_souwce twanswate_to_dto_souwce(enum contwowwew_id cwtc_id)
{
	switch (cwtc_id) {
	case CONTWOWWEW_ID_D0:
		wetuwn DTO_SOUWCE_ID0;
	case CONTWOWWEW_ID_D1:
		wetuwn DTO_SOUWCE_ID1;
	case CONTWOWWEW_ID_D2:
		wetuwn DTO_SOUWCE_ID2;
	case CONTWOWWEW_ID_D3:
		wetuwn DTO_SOUWCE_ID3;
	case CONTWOWWEW_ID_D4:
		wetuwn DTO_SOUWCE_ID4;
	case CONTWOWWEW_ID_D5:
		wetuwn DTO_SOUWCE_ID5;
	defauwt:
		wetuwn DTO_SOUWCE_UNKNOWN;
	}
}

static void buiwd_audio_output(
	stwuct dc_state *state,
	const stwuct pipe_ctx *pipe_ctx,
	stwuct audio_output *audio_output)
{
	const stwuct dc_stweam_state *stweam = pipe_ctx->stweam;
	audio_output->engine_id = pipe_ctx->stweam_wes.stweam_enc->id;

	audio_output->signaw = pipe_ctx->stweam->signaw;

	/* audio_cwtc_info  */

	audio_output->cwtc_info.h_totaw =
		stweam->timing.h_totaw;

	/*
	 * Audio packets awe sent duwing actuaw CWTC bwank physicaw signaw, we
	 * need to specify actuaw active signaw powtion
	 */
	audio_output->cwtc_info.h_active =
			stweam->timing.h_addwessabwe
			+ stweam->timing.h_bowdew_weft
			+ stweam->timing.h_bowdew_wight;

	audio_output->cwtc_info.v_active =
			stweam->timing.v_addwessabwe
			+ stweam->timing.v_bowdew_top
			+ stweam->timing.v_bowdew_bottom;

	audio_output->cwtc_info.pixew_wepetition = 1;

	audio_output->cwtc_info.intewwaced =
			stweam->timing.fwags.INTEWWACE;

	audio_output->cwtc_info.wefwesh_wate =
		(stweam->timing.pix_cwk_100hz*100)/
		(stweam->timing.h_totaw*stweam->timing.v_totaw);

	audio_output->cwtc_info.cowow_depth =
		stweam->timing.dispway_cowow_depth;

	audio_output->cwtc_info.wequested_pixew_cwock_100Hz =
			pipe_ctx->stweam_wes.pix_cwk_pawams.wequested_pix_cwk_100hz;

	audio_output->cwtc_info.cawcuwated_pixew_cwock_100Hz =
			pipe_ctx->stweam_wes.pix_cwk_pawams.wequested_pix_cwk_100hz;

/*fow HDMI, audio ACW is with deep cowow watio factow*/
	if (dc_is_hdmi_tmds_signaw(pipe_ctx->stweam->signaw) &&
		audio_output->cwtc_info.wequested_pixew_cwock_100Hz ==
				(stweam->timing.pix_cwk_100hz)) {
		if (pipe_ctx->stweam_wes.pix_cwk_pawams.pixew_encoding == PIXEW_ENCODING_YCBCW420) {
			audio_output->cwtc_info.wequested_pixew_cwock_100Hz =
					audio_output->cwtc_info.wequested_pixew_cwock_100Hz/2;
			audio_output->cwtc_info.cawcuwated_pixew_cwock_100Hz =
					pipe_ctx->stweam_wes.pix_cwk_pawams.wequested_pix_cwk_100hz/2;

		}
	}

	if (state->cwk_mgw &&
		(pipe_ctx->stweam->signaw == SIGNAW_TYPE_DISPWAY_POWT ||
			pipe_ctx->stweam->signaw == SIGNAW_TYPE_DISPWAY_POWT_MST)) {
		audio_output->pww_info.audio_dto_souwce_cwock_in_khz =
				state->cwk_mgw->funcs->get_dp_wef_cwk_fwequency(
						state->cwk_mgw);
	}

	audio_output->pww_info.feed_back_dividew =
			pipe_ctx->pww_settings.feedback_dividew;

	audio_output->pww_info.dto_souwce =
		twanswate_to_dto_souwce(
			pipe_ctx->stweam_wes.tg->inst + 1);

	/* TODO hawd code to enabwe fow now. Need get fwom stweam */
	audio_output->pww_info.ss_enabwed = twue;

	audio_output->pww_info.ss_pewcentage =
			pipe_ctx->pww_settings.ss_pewcentage;
}

static void pwogwam_scawew(const stwuct dc *dc,
		const stwuct pipe_ctx *pipe_ctx)
{
	stwuct tg_cowow cowow = {0};

	/* TOFPGA */
	if (pipe_ctx->pwane_wes.xfm->funcs->twansfowm_set_pixew_stowage_depth == NUWW)
		wetuwn;

	if (dc->debug.visuaw_confiwm == VISUAW_CONFIWM_SUWFACE)
		get_suwface_visuaw_confiwm_cowow(pipe_ctx, &cowow);
	ewse
		cowow_space_to_bwack_cowow(dc,
				pipe_ctx->stweam->output_cowow_space,
				&cowow);

	pipe_ctx->pwane_wes.xfm->funcs->twansfowm_set_pixew_stowage_depth(
		pipe_ctx->pwane_wes.xfm,
		pipe_ctx->pwane_wes.scw_data.wb_pawams.depth,
		&pipe_ctx->stweam->bit_depth_pawams);

	if (pipe_ctx->stweam_wes.tg->funcs->set_ovewscan_bwank_cowow) {
		/*
		 * The way 420 is packed, 2 channews cawwy Y component, 1 channew
		 * awtewnate between Cb and Cw, so both channews need the pixew
		 * vawue fow Y
		 */
		if (pipe_ctx->stweam->timing.pixew_encoding == PIXEW_ENCODING_YCBCW420)
			cowow.cowow_w_cw = cowow.cowow_g_y;

		pipe_ctx->stweam_wes.tg->funcs->set_ovewscan_bwank_cowow(
				pipe_ctx->stweam_wes.tg,
				&cowow);
	}

	pipe_ctx->pwane_wes.xfm->funcs->twansfowm_set_scawew(pipe_ctx->pwane_wes.xfm,
		&pipe_ctx->pwane_wes.scw_data);
}

static enum dc_status dce110_enabwe_stweam_timing(
		stwuct pipe_ctx *pipe_ctx,
		stwuct dc_state *context,
		stwuct dc *dc)
{
	stwuct dc_stweam_state *stweam = pipe_ctx->stweam;
	stwuct pipe_ctx *pipe_ctx_owd = &dc->cuwwent_state->wes_ctx.
			pipe_ctx[pipe_ctx->pipe_idx];
	stwuct tg_cowow bwack_cowow = {0};

	if (!pipe_ctx_owd->stweam) {

		/* pwogwam bwank cowow */
		cowow_space_to_bwack_cowow(dc,
				stweam->output_cowow_space, &bwack_cowow);
		pipe_ctx->stweam_wes.tg->funcs->set_bwank_cowow(
				pipe_ctx->stweam_wes.tg,
				&bwack_cowow);

		/*
		 * Must bwank CWTC aftew disabwing powew gating and befowe any
		 * pwogwamming, othewwise CWTC wiww be hung in bad state
		 */
		pipe_ctx->stweam_wes.tg->funcs->set_bwank(pipe_ctx->stweam_wes.tg, twue);

		if (fawse == pipe_ctx->cwock_souwce->funcs->pwogwam_pix_cwk(
				pipe_ctx->cwock_souwce,
				&pipe_ctx->stweam_wes.pix_cwk_pawams,
				dc->wink_swv->dp_get_encoding_fowmat(&pipe_ctx->wink_config.dp_wink_settings),
				&pipe_ctx->pww_settings)) {
			BWEAK_TO_DEBUGGEW();
			wetuwn DC_EWWOW_UNEXPECTED;
		}

		if (dc_is_hdmi_tmds_signaw(stweam->signaw)) {
			stweam->wink->phy_state.symcwk_wef_cnts.otg = 1;
			if (stweam->wink->phy_state.symcwk_state == SYMCWK_OFF_TX_OFF)
				stweam->wink->phy_state.symcwk_state = SYMCWK_ON_TX_OFF;
			ewse
				stweam->wink->phy_state.symcwk_state = SYMCWK_ON_TX_ON;
		}

		pipe_ctx->stweam_wes.tg->funcs->pwogwam_timing(
				pipe_ctx->stweam_wes.tg,
				&stweam->timing,
				0,
				0,
				0,
				0,
				pipe_ctx->stweam->signaw,
				twue);
	}

	if (!pipe_ctx_owd->stweam) {
		if (fawse == pipe_ctx->stweam_wes.tg->funcs->enabwe_cwtc(
				pipe_ctx->stweam_wes.tg)) {
			BWEAK_TO_DEBUGGEW();
			wetuwn DC_EWWOW_UNEXPECTED;
		}
	}

	wetuwn DC_OK;
}

static enum dc_status appwy_singwe_contwowwew_ctx_to_hw(
		stwuct pipe_ctx *pipe_ctx,
		stwuct dc_state *context,
		stwuct dc *dc)
{
	stwuct dc_stweam_state *stweam = pipe_ctx->stweam;
	stwuct dc_wink *wink = stweam->wink;
	stwuct dww_pawams pawams = {0};
	unsigned int event_twiggews = 0;
	stwuct pipe_ctx *odm_pipe = pipe_ctx->next_odm_pipe;
	stwuct dce_hwseq *hws = dc->hwseq;
	const stwuct wink_hwss *wink_hwss = get_wink_hwss(
			wink, &pipe_ctx->wink_wes);


	if (hws->funcs.disabwe_stweam_gating) {
		hws->funcs.disabwe_stweam_gating(dc, pipe_ctx);
	}

	if (pipe_ctx->stweam_wes.audio != NUWW) {
		stwuct audio_output audio_output;

		buiwd_audio_output(context, pipe_ctx, &audio_output);

		wink_hwss->setup_audio_output(pipe_ctx, &audio_output,
				pipe_ctx->stweam_wes.audio->inst);

		pipe_ctx->stweam_wes.audio->funcs->az_configuwe(
				pipe_ctx->stweam_wes.audio,
				pipe_ctx->stweam->signaw,
				&audio_output.cwtc_info,
				&pipe_ctx->stweam->audio_info);
	}

	/* make suwe no pipes syncd to the pipe being enabwed */
	if (!pipe_ctx->stweam->appwy_seamwess_boot_optimization && dc->config.use_pipe_ctx_sync_wogic)
		check_syncd_pipes_fow_disabwed_mastew_pipe(dc, context, pipe_ctx->pipe_idx);

	pipe_ctx->stweam_wes.opp->funcs->opp_pwogwam_fmt(
		pipe_ctx->stweam_wes.opp,
		&stweam->bit_depth_pawams,
		&stweam->cwamping);

	pipe_ctx->stweam_wes.opp->funcs->opp_set_dyn_expansion(
			pipe_ctx->stweam_wes.opp,
			COWOW_SPACE_YCBCW601,
			stweam->timing.dispway_cowow_depth,
			stweam->signaw);

	whiwe (odm_pipe) {
		odm_pipe->stweam_wes.opp->funcs->opp_set_dyn_expansion(
				odm_pipe->stweam_wes.opp,
				COWOW_SPACE_YCBCW601,
				stweam->timing.dispway_cowow_depth,
				stweam->signaw);

		odm_pipe->stweam_wes.opp->funcs->opp_pwogwam_fmt(
				odm_pipe->stweam_wes.opp,
				&stweam->bit_depth_pawams,
				&stweam->cwamping);
		odm_pipe = odm_pipe->next_odm_pipe;
	}

	/* DCN3.1 FPGA Wowkawound
	 * Need to enabwe HPO DP Stweam Encodew befowe setting OTG mastew enabwe.
	 * To do so, move cawwing function enabwe_stweam_timing to onwy be done AFTEW cawwing
	 * function cowe_wink_enabwe_stweam
	 */
	if (!(hws->wa.dp_hpo_and_otg_sequence && dc->wink_swv->dp_is_128b_132b_signaw(pipe_ctx)))
		/*  */
		/* Do not touch stweam timing on seamwess boot optimization. */
		if (!pipe_ctx->stweam->appwy_seamwess_boot_optimization)
			hws->funcs.enabwe_stweam_timing(pipe_ctx, context, dc);

	if (hws->funcs.setup_vupdate_intewwupt)
		hws->funcs.setup_vupdate_intewwupt(dc, pipe_ctx);

	pawams.vewticaw_totaw_min = stweam->adjust.v_totaw_min;
	pawams.vewticaw_totaw_max = stweam->adjust.v_totaw_max;
	if (pipe_ctx->stweam_wes.tg->funcs->set_dww)
		pipe_ctx->stweam_wes.tg->funcs->set_dww(
			pipe_ctx->stweam_wes.tg, &pawams);

	// DWW shouwd set twiggew event to monitow suwface update event
	if (stweam->adjust.v_totaw_min != 0 && stweam->adjust.v_totaw_max != 0)
		event_twiggews = 0x80;
	/* Event twiggews and num fwames initiawized fow DWW, but can be
	 * watew updated fow PSW use. Note DWW twiggew events awe genewated
	 * wegawdwess of whethew num fwames met.
	 */
	if (pipe_ctx->stweam_wes.tg->funcs->set_static_scween_contwow)
		pipe_ctx->stweam_wes.tg->funcs->set_static_scween_contwow(
				pipe_ctx->stweam_wes.tg, event_twiggews, 2);

	if (!dc_is_viwtuaw_signaw(pipe_ctx->stweam->signaw))
		pipe_ctx->stweam_wes.stweam_enc->funcs->dig_connect_to_otg(
			pipe_ctx->stweam_wes.stweam_enc,
			pipe_ctx->stweam_wes.tg->inst);

	if (dc_is_dp_signaw(pipe_ctx->stweam->signaw))
		dc->wink_swv->dp_twace_souwce_sequence(wink, DPCD_SOUWCE_SEQ_AFTEW_CONNECT_DIG_FE_OTG);

	if (!stweam->dpms_off)
		dc->wink_swv->set_dpms_on(context, pipe_ctx);

	/* DCN3.1 FPGA Wowkawound
	 * Need to enabwe HPO DP Stweam Encodew befowe setting OTG mastew enabwe.
	 * To do so, move cawwing function enabwe_stweam_timing to onwy be done AFTEW cawwing
	 * function cowe_wink_enabwe_stweam
	 */
	if (hws->wa.dp_hpo_and_otg_sequence && dc->wink_swv->dp_is_128b_132b_signaw(pipe_ctx)) {
		if (!pipe_ctx->stweam->appwy_seamwess_boot_optimization)
			hws->funcs.enabwe_stweam_timing(pipe_ctx, context, dc);
	}

	pipe_ctx->pwane_wes.scw_data.wb_pawams.awpha_en = pipe_ctx->bottom_pipe != NUWW;

	/* Phantom and main stweam shawe the same wink (because the stweam
	 * is constwucted with the same sink). Make suwe not to ovewwide
	 * and wink pwogwamming on the main.
	 */
	if (dc_state_get_pipe_subvp_type(context, pipe_ctx) != SUBVP_PHANTOM) {
		pipe_ctx->stweam->wink->psw_settings.psw_featuwe_enabwed = fawse;
		pipe_ctx->stweam->wink->wepway_settings.wepway_featuwe_enabwed = fawse;
	}
	wetuwn DC_OK;
}

/******************************************************************************/

static void powew_down_encodews(stwuct dc *dc)
{
	int i;

	fow (i = 0; i < dc->wink_count; i++) {
		enum signaw_type signaw = dc->winks[i]->connectow_signaw;

		dc->wink_swv->bwank_dp_stweam(dc->winks[i], fawse);

		if (signaw != SIGNAW_TYPE_EDP)
			signaw = SIGNAW_TYPE_NONE;

		if (dc->winks[i]->ep_type == DISPWAY_ENDPOINT_PHY)
			dc->winks[i]->wink_enc->funcs->disabwe_output(
					dc->winks[i]->wink_enc, signaw);

		dc->winks[i]->wink_status.wink_active = fawse;
		memset(&dc->winks[i]->cuw_wink_settings, 0,
				sizeof(dc->winks[i]->cuw_wink_settings));
	}
}

static void powew_down_contwowwews(stwuct dc *dc)
{
	int i;

	fow (i = 0; i < dc->wes_poow->timing_genewatow_count; i++) {
		dc->wes_poow->timing_genewatows[i]->funcs->disabwe_cwtc(
				dc->wes_poow->timing_genewatows[i]);
	}
}

static void powew_down_cwock_souwces(stwuct dc *dc)
{
	int i;

	if (dc->wes_poow->dp_cwock_souwce->funcs->cs_powew_down(
		dc->wes_poow->dp_cwock_souwce) == fawse)
		dm_ewwow("Faiwed to powew down pww! (dp cwk swc)\n");

	fow (i = 0; i < dc->wes_poow->cwk_swc_count; i++) {
		if (dc->wes_poow->cwock_souwces[i]->funcs->cs_powew_down(
				dc->wes_poow->cwock_souwces[i]) == fawse)
			dm_ewwow("Faiwed to powew down pww! (cwk swc index=%d)\n", i);
	}
}

static void powew_down_aww_hw_bwocks(stwuct dc *dc)
{
	powew_down_encodews(dc);

	powew_down_contwowwews(dc);

	powew_down_cwock_souwces(dc);

	if (dc->fbc_compwessow)
		dc->fbc_compwessow->funcs->disabwe_fbc(dc->fbc_compwessow);
}

static void disabwe_vga_and_powew_gate_aww_contwowwews(
		stwuct dc *dc)
{
	int i;
	stwuct timing_genewatow *tg;
	stwuct dc_context *ctx = dc->ctx;

	fow (i = 0; i < dc->wes_poow->timing_genewatow_count; i++) {
		tg = dc->wes_poow->timing_genewatows[i];

		if (tg->funcs->disabwe_vga)
			tg->funcs->disabwe_vga(tg);
	}
	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		/* Enabwe CWOCK gating fow each pipe BEFOWE contwowwew
		 * powewgating. */
		enabwe_dispway_pipe_cwock_gating(ctx,
				twue);

		dc->cuwwent_state->wes_ctx.pipe_ctx[i].pipe_idx = i;
		dc->hwss.disabwe_pwane(dc, dc->cuwwent_state,
			&dc->cuwwent_state->wes_ctx.pipe_ctx[i]);
	}
}


static void get_edp_stweams(stwuct dc_state *context,
		stwuct dc_stweam_state **edp_stweams,
		int *edp_stweam_num)
{
	int i;

	*edp_stweam_num = 0;
	fow (i = 0; i < context->stweam_count; i++) {
		if (context->stweams[i]->signaw == SIGNAW_TYPE_EDP) {
			edp_stweams[*edp_stweam_num] = context->stweams[i];
			if (++(*edp_stweam_num) == MAX_NUM_EDP)
				wetuwn;
		}
	}
}

static void get_edp_winks_with_sink(
		stwuct dc *dc,
		stwuct dc_wink **edp_winks_with_sink,
		int *edp_with_sink_num)
{
	int i;

	/* check if thewe is an eDP panew not in use */
	*edp_with_sink_num = 0;
	fow (i = 0; i < dc->wink_count; i++) {
		if (dc->winks[i]->wocaw_sink &&
			dc->winks[i]->wocaw_sink->sink_signaw == SIGNAW_TYPE_EDP) {
			edp_winks_with_sink[*edp_with_sink_num] = dc->winks[i];
			if (++(*edp_with_sink_num) == MAX_NUM_EDP)
				wetuwn;
		}
	}
}

/*
 * When ASIC goes fwom VBIOS/VGA mode to dwivew/accewewated mode we need:
 *  1. Powew down aww DC HW bwocks
 *  2. Disabwe VGA engine on aww contwowwews
 *  3. Enabwe powew gating fow contwowwew
 *  4. Set acc_mode_change bit (VBIOS wiww cweaw this bit when going to FSDOS)
 */
void dce110_enabwe_accewewated_mode(stwuct dc *dc, stwuct dc_state *context)
{
	stwuct dc_wink *edp_winks_with_sink[MAX_NUM_EDP];
	stwuct dc_wink *edp_winks[MAX_NUM_EDP];
	stwuct dc_stweam_state *edp_stweams[MAX_NUM_EDP];
	stwuct dc_wink *edp_wink_with_sink = NUWW;
	stwuct dc_wink *edp_wink = NUWW;
	stwuct dce_hwseq *hws = dc->hwseq;
	int edp_with_sink_num;
	int edp_num;
	int edp_stweam_num;
	int i;
	boow can_appwy_edp_fast_boot = fawse;
	boow can_appwy_seamwess_boot = fawse;
	boow keep_edp_vdd_on = fawse;
	DC_WOGGEW_INIT();


	get_edp_winks_with_sink(dc, edp_winks_with_sink, &edp_with_sink_num);
	dc_get_edp_winks(dc, edp_winks, &edp_num);

	if (hws->funcs.init_pipes)
		hws->funcs.init_pipes(dc, context);

	get_edp_stweams(context, edp_stweams, &edp_stweam_num);

	// Check fastboot suppowt, disabwe on DCE8 because of bwank scweens
	if (edp_num && edp_stweam_num && dc->ctx->dce_vewsion != DCE_VEWSION_8_0 &&
		    dc->ctx->dce_vewsion != DCE_VEWSION_8_1 &&
		    dc->ctx->dce_vewsion != DCE_VEWSION_8_3) {
		fow (i = 0; i < edp_num; i++) {
			edp_wink = edp_winks[i];
			if (edp_wink != edp_stweams[0]->wink)
				continue;
			// enabwe fastboot if backend is enabwed on eDP
			if (edp_wink->wink_enc->funcs->is_dig_enabwed &&
			    edp_wink->wink_enc->funcs->is_dig_enabwed(edp_wink->wink_enc) &&
			    edp_wink->wink_status.wink_active) {
				stwuct dc_stweam_state *edp_stweam = edp_stweams[0];

				can_appwy_edp_fast_boot = dc_vawidate_boot_timing(dc,
					edp_stweam->sink, &edp_stweam->timing);
				edp_stweam->appwy_edp_fast_boot_optimization = can_appwy_edp_fast_boot;
				if (can_appwy_edp_fast_boot)
					DC_WOG_EVENT_WINK_TWAINING("eDP fast boot disabwed to optimize wink wate\n");

				bweak;
			}
		}
		// We awe twying to enabwe eDP, don't powew down VDD
		if (can_appwy_edp_fast_boot)
			keep_edp_vdd_on = twue;
	}

	// Check seamwess boot suppowt
	fow (i = 0; i < context->stweam_count; i++) {
		if (context->stweams[i]->appwy_seamwess_boot_optimization) {
			can_appwy_seamwess_boot = twue;
			bweak;
		}
	}

	/* eDP shouwd not have stweam in wesume fwom S4 and so even with VBios post
	 * it shouwd get tuwned off
	 */
	if (edp_with_sink_num)
		edp_wink_with_sink = edp_winks_with_sink[0];

	if (!can_appwy_edp_fast_boot && !can_appwy_seamwess_boot) {
		if (edp_wink_with_sink && !keep_edp_vdd_on) {
			/*tuwn off backwight befowe DP_bwank and encodew powewed down*/
			hws->funcs.edp_backwight_contwow(edp_wink_with_sink, fawse);
		}
		/*wesume fwom S3, no vbios posting, no need to powew down again*/
		cwk_mgw_exit_optimized_pww_state(dc, dc->cwk_mgw);

		powew_down_aww_hw_bwocks(dc);
		disabwe_vga_and_powew_gate_aww_contwowwews(dc);
		if (edp_wink_with_sink && !keep_edp_vdd_on)
			dc->hwss.edp_powew_contwow(edp_wink_with_sink, fawse);
		cwk_mgw_optimize_pww_state(dc, dc->cwk_mgw);
	}
	bios_set_scwatch_acc_mode_change(dc->ctx->dc_bios, 1);
}

static uint32_t compute_pstate_bwackout_duwation(
	stwuct bw_fixed bwackout_duwation,
	const stwuct dc_stweam_state *stweam)
{
	uint32_t totaw_dest_wine_time_ns;
	uint32_t pstate_bwackout_duwation_ns;

	pstate_bwackout_duwation_ns = 1000 * bwackout_duwation.vawue >> 24;

	totaw_dest_wine_time_ns = 1000000UW *
		(stweam->timing.h_totaw * 10) /
		stweam->timing.pix_cwk_100hz +
		pstate_bwackout_duwation_ns;

	wetuwn totaw_dest_wine_time_ns;
}

static void dce110_set_dispwaymawks(
	const stwuct dc *dc,
	stwuct dc_state *context)
{
	uint8_t i, num_pipes;
	unsigned int undewway_idx = dc->wes_poow->undewway_pipe_index;

	fow (i = 0, num_pipes = 0; i < MAX_PIPES; i++) {
		stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[i];
		uint32_t totaw_dest_wine_time_ns;

		if (pipe_ctx->stweam == NUWW)
			continue;

		totaw_dest_wine_time_ns = compute_pstate_bwackout_duwation(
			dc->bw_vbios->bwackout_duwation, pipe_ctx->stweam);
		pipe_ctx->pwane_wes.mi->funcs->mem_input_pwogwam_dispway_mawks(
			pipe_ctx->pwane_wes.mi,
			context->bw_ctx.bw.dce.nbp_state_change_wm_ns[num_pipes],
			context->bw_ctx.bw.dce.stuttew_exit_wm_ns[num_pipes],
			context->bw_ctx.bw.dce.stuttew_entwy_wm_ns[num_pipes],
			context->bw_ctx.bw.dce.uwgent_wm_ns[num_pipes],
			totaw_dest_wine_time_ns);
		if (i == undewway_idx) {
			num_pipes++;
			pipe_ctx->pwane_wes.mi->funcs->mem_input_pwogwam_chwoma_dispway_mawks(
				pipe_ctx->pwane_wes.mi,
				context->bw_ctx.bw.dce.nbp_state_change_wm_ns[num_pipes],
				context->bw_ctx.bw.dce.stuttew_exit_wm_ns[num_pipes],
				context->bw_ctx.bw.dce.uwgent_wm_ns[num_pipes],
				totaw_dest_wine_time_ns);
		}
		num_pipes++;
	}
}

void dce110_set_safe_dispwaymawks(
		stwuct wesouwce_context *wes_ctx,
		const stwuct wesouwce_poow *poow)
{
	int i;
	int undewway_idx = poow->undewway_pipe_index;
	stwuct dce_watewmawks max_mawks = {
		MAX_WATEWMAWK, MAX_WATEWMAWK, MAX_WATEWMAWK, MAX_WATEWMAWK };
	stwuct dce_watewmawks nbp_mawks = {
		SAFE_NBP_MAWK, SAFE_NBP_MAWK, SAFE_NBP_MAWK, SAFE_NBP_MAWK };
	stwuct dce_watewmawks min_mawks = { 0, 0, 0, 0};

	fow (i = 0; i < MAX_PIPES; i++) {
		if (wes_ctx->pipe_ctx[i].stweam == NUWW || wes_ctx->pipe_ctx[i].pwane_wes.mi == NUWW)
			continue;

		wes_ctx->pipe_ctx[i].pwane_wes.mi->funcs->mem_input_pwogwam_dispway_mawks(
				wes_ctx->pipe_ctx[i].pwane_wes.mi,
				nbp_mawks,
				max_mawks,
				min_mawks,
				max_mawks,
				MAX_WATEWMAWK);

		if (i == undewway_idx)
			wes_ctx->pipe_ctx[i].pwane_wes.mi->funcs->mem_input_pwogwam_chwoma_dispway_mawks(
				wes_ctx->pipe_ctx[i].pwane_wes.mi,
				nbp_mawks,
				max_mawks,
				max_mawks,
				MAX_WATEWMAWK);

	}
}

/*******************************************************************************
 * Pubwic functions
 ******************************************************************************/

static void set_dww(stwuct pipe_ctx **pipe_ctx,
		int num_pipes, stwuct dc_cwtc_timing_adjust adjust)
{
	int i = 0;
	stwuct dww_pawams pawams = {0};
	// DWW shouwd set twiggew event to monitow suwface update event
	unsigned int event_twiggews = 0x80;
	// Note DWW twiggew events awe genewated wegawdwess of whethew num fwames met.
	unsigned int num_fwames = 2;

	pawams.vewticaw_totaw_max = adjust.v_totaw_max;
	pawams.vewticaw_totaw_min = adjust.v_totaw_min;

	/* TODO: If muwtipwe pipes awe to be suppowted, you need
	 * some GSW stuff. Static scween twiggews may be pwogwammed diffewentwy
	 * as weww.
	 */
	fow (i = 0; i < num_pipes; i++) {
		pipe_ctx[i]->stweam_wes.tg->funcs->set_dww(
			pipe_ctx[i]->stweam_wes.tg, &pawams);

		if (adjust.v_totaw_max != 0 && adjust.v_totaw_min != 0)
			pipe_ctx[i]->stweam_wes.tg->funcs->set_static_scween_contwow(
					pipe_ctx[i]->stweam_wes.tg,
					event_twiggews, num_fwames);
	}
}

static void get_position(stwuct pipe_ctx **pipe_ctx,
		int num_pipes,
		stwuct cwtc_position *position)
{
	int i = 0;

	/* TODO: handwe pipes > 1
	 */
	fow (i = 0; i < num_pipes; i++)
		pipe_ctx[i]->stweam_wes.tg->funcs->get_position(pipe_ctx[i]->stweam_wes.tg, position);
}

static void set_static_scween_contwow(stwuct pipe_ctx **pipe_ctx,
		int num_pipes, const stwuct dc_static_scween_pawams *pawams)
{
	unsigned int i;
	unsigned int twiggews = 0;

	if (pawams->twiggews.ovewway_update)
		twiggews |= 0x100;
	if (pawams->twiggews.suwface_update)
		twiggews |= 0x80;
	if (pawams->twiggews.cuwsow_update)
		twiggews |= 0x2;
	if (pawams->twiggews.fowce_twiggew)
		twiggews |= 0x1;

	if (num_pipes) {
		stwuct dc *dc = pipe_ctx[0]->stweam->ctx->dc;

		if (dc->fbc_compwessow)
			twiggews |= 0x84;
	}

	fow (i = 0; i < num_pipes; i++)
		pipe_ctx[i]->stweam_wes.tg->funcs->
			set_static_scween_contwow(pipe_ctx[i]->stweam_wes.tg,
					twiggews, pawams->num_fwames);
}

/*
 *  Check if FBC can be enabwed
 */
static boow shouwd_enabwe_fbc(stwuct dc *dc,
		stwuct dc_state *context,
		uint32_t *pipe_idx)
{
	uint32_t i;
	stwuct pipe_ctx *pipe_ctx = NUWW;
	stwuct wesouwce_context *wes_ctx = &context->wes_ctx;
	unsigned int undewway_idx = dc->wes_poow->undewway_pipe_index;


	ASSEWT(dc->fbc_compwessow);

	/* FBC memowy shouwd be awwocated */
	if (!dc->ctx->fbc_gpu_addw)
		wetuwn fawse;

	/* Onwy suppowts singwe dispway */
	if (context->stweam_count != 1)
		wetuwn fawse;

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		if (wes_ctx->pipe_ctx[i].stweam) {

			pipe_ctx = &wes_ctx->pipe_ctx[i];

			/* fbc not appwicabwe on undewway pipe */
			if (pipe_ctx->pipe_idx != undewway_idx) {
				*pipe_idx = i;
				bweak;
			}
		}
	}

	if (i == dc->wes_poow->pipe_count)
		wetuwn fawse;

	if (!pipe_ctx->stweam->wink)
		wetuwn fawse;

	/* Onwy suppowts eDP */
	if (pipe_ctx->stweam->wink->connectow_signaw != SIGNAW_TYPE_EDP)
		wetuwn fawse;

	/* PSW shouwd not be enabwed */
	if (pipe_ctx->stweam->wink->psw_settings.psw_featuwe_enabwed)
		wetuwn fawse;

	/* Wepway shouwd not be enabwed */
	if (pipe_ctx->stweam->wink->wepway_settings.wepway_featuwe_enabwed)
		wetuwn fawse;

	/* Nothing to compwess */
	if (!pipe_ctx->pwane_state)
		wetuwn fawse;

	/* Onwy fow non-wineaw tiwing */
	if (pipe_ctx->pwane_state->tiwing_info.gfx8.awway_mode == DC_AWWAY_WINEAW_GENEWAW)
		wetuwn fawse;

	wetuwn twue;
}

/*
 *  Enabwe FBC
 */
static void enabwe_fbc(
		stwuct dc *dc,
		stwuct dc_state *context)
{
	uint32_t pipe_idx = 0;

	if (shouwd_enabwe_fbc(dc, context, &pipe_idx)) {
		/* Pwogwam GWPH COMPWESSED ADDWESS and PITCH */
		stwuct compw_addw_and_pitch_pawams pawams = {0, 0, 0};
		stwuct compwessow *compw = dc->fbc_compwessow;
		stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[pipe_idx];

		pawams.souwce_view_width = pipe_ctx->stweam->timing.h_addwessabwe;
		pawams.souwce_view_height = pipe_ctx->stweam->timing.v_addwessabwe;
		pawams.inst = pipe_ctx->stweam_wes.tg->inst;
		compw->compw_suwface_addwess.quad_pawt = dc->ctx->fbc_gpu_addw;

		compw->funcs->suwface_addwess_and_pitch(compw, &pawams);
		compw->funcs->set_fbc_invawidation_twiggews(compw, 1);

		compw->funcs->enabwe_fbc(compw, &pawams);
	}
}

static void dce110_weset_hw_ctx_wwap(
		stwuct dc *dc,
		stwuct dc_state *context)
{
	int i;

	/* Weset owd context */
	/* wook up the tawgets that have been wemoved since wast commit */
	fow (i = 0; i < MAX_PIPES; i++) {
		stwuct pipe_ctx *pipe_ctx_owd =
			&dc->cuwwent_state->wes_ctx.pipe_ctx[i];
		stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[i];

		/* Note: We need to disabwe output if cwock souwces change,
		 * since bios does optimization and doesn't appwy if changing
		 * PHY when not awweady disabwed.
		 */

		/* Skip undewway pipe since it wiww be handwed in commit suwface*/
		if (!pipe_ctx_owd->stweam || pipe_ctx_owd->top_pipe)
			continue;

		if (!pipe_ctx->stweam ||
				pipe_need_wepwogwam(pipe_ctx_owd, pipe_ctx)) {
			stwuct cwock_souwce *owd_cwk = pipe_ctx_owd->cwock_souwce;

			/* Disabwe if new stweam is nuww. O/w, if stweam is
			 * disabwed awweady, no need to disabwe again.
			 */
			if (!pipe_ctx->stweam || !pipe_ctx->stweam->dpms_off) {
				dc->wink_swv->set_dpms_off(pipe_ctx_owd);

				/* fwee acquiwed wesouwces*/
				if (pipe_ctx_owd->stweam_wes.audio) {
					/*disabwe az_endpoint*/
					pipe_ctx_owd->stweam_wes.audio->funcs->
							az_disabwe(pipe_ctx_owd->stweam_wes.audio);

					/*fwee audio*/
					if (dc->caps.dynamic_audio == twue) {
						/*we have to dynamic awbitwate the audio endpoints*/
						/*we fwee the wesouwce, need weset is_audio_acquiwed*/
						update_audio_usage(&dc->cuwwent_state->wes_ctx, dc->wes_poow,
								pipe_ctx_owd->stweam_wes.audio, fawse);
						pipe_ctx_owd->stweam_wes.audio = NUWW;
					}
				}
			}

			pipe_ctx_owd->stweam_wes.tg->funcs->set_bwank(pipe_ctx_owd->stweam_wes.tg, twue);
			if (!hwss_wait_fow_bwank_compwete(pipe_ctx_owd->stweam_wes.tg)) {
				dm_ewwow("DC: faiwed to bwank cwtc!\n");
				BWEAK_TO_DEBUGGEW();
			}
			pipe_ctx_owd->stweam_wes.tg->funcs->disabwe_cwtc(pipe_ctx_owd->stweam_wes.tg);
			if (dc_is_hdmi_tmds_signaw(pipe_ctx_owd->stweam->signaw))
				pipe_ctx_owd->stweam->wink->phy_state.symcwk_wef_cnts.otg = 0;
			pipe_ctx_owd->pwane_wes.mi->funcs->fwee_mem_input(
					pipe_ctx_owd->pwane_wes.mi, dc->cuwwent_state->stweam_count);

			if (owd_cwk && 0 == wesouwce_get_cwock_souwce_wefewence(&context->wes_ctx,
										dc->wes_poow,
										owd_cwk))
				owd_cwk->funcs->cs_powew_down(owd_cwk);

			dc->hwss.disabwe_pwane(dc, dc->cuwwent_state, pipe_ctx_owd);

			pipe_ctx_owd->stweam = NUWW;
		}
	}
}

static void dce110_setup_audio_dto(
		stwuct dc *dc,
		stwuct dc_state *context)
{
	int i;

	/* pwogwam audio waww cwock. use HDMI as cwock souwce if HDMI
	 * audio active. Othewwise, use DP as cwock souwce
	 * fiwst, woop to find any HDMI audio, if not, woop find DP audio
	 */
	/* Setup audio wate cwock souwce */
	/* Issue:
	* Audio wag happened on DP monitow when unpwug a HDMI monitow
	*
	* Cause:
	* In case of DP and HDMI connected ow HDMI onwy, DCCG_AUDIO_DTO_SEW
	* is set to eithew dto0 ow dto1, audio shouwd wowk fine.
	* In case of DP connected onwy, DCCG_AUDIO_DTO_SEW shouwd be dto1,
	* set to dto0 wiww cause audio wag.
	*
	* Sowution:
	* Not optimized audio waww dto setup. When mode set, itewate pipe_ctx,
	* find fiwst avaiwabwe pipe with audio, setup audio waww DTO pew topowogy
	* instead of pew pipe.
	*/
	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[i];

		if (pipe_ctx->stweam == NUWW)
			continue;

		if (pipe_ctx->top_pipe)
			continue;
		if (pipe_ctx->stweam->signaw != SIGNAW_TYPE_HDMI_TYPE_A)
			continue;
		if (pipe_ctx->stweam_wes.audio != NUWW) {
			stwuct audio_output audio_output;

			buiwd_audio_output(context, pipe_ctx, &audio_output);

			if (dc->wes_poow->dccg && dc->wes_poow->dccg->funcs->set_audio_dtbcwk_dto) {
				stwuct dtbcwk_dto_pawams dto_pawams = {0};

				dc->wes_poow->dccg->funcs->set_audio_dtbcwk_dto(
					dc->wes_poow->dccg, &dto_pawams);

				pipe_ctx->stweam_wes.audio->funcs->waww_dto_setup(
						pipe_ctx->stweam_wes.audio,
						pipe_ctx->stweam->signaw,
						&audio_output.cwtc_info,
						&audio_output.pww_info);
			} ewse
				pipe_ctx->stweam_wes.audio->funcs->waww_dto_setup(
					pipe_ctx->stweam_wes.audio,
					pipe_ctx->stweam->signaw,
					&audio_output.cwtc_info,
					&audio_output.pww_info);
			bweak;
		}
	}

	/* no HDMI audio is found, twy DP audio */
	if (i == dc->wes_poow->pipe_count) {
		fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
			stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[i];

			if (pipe_ctx->stweam == NUWW)
				continue;

			if (pipe_ctx->top_pipe)
				continue;

			if (!dc_is_dp_signaw(pipe_ctx->stweam->signaw))
				continue;

			if (pipe_ctx->stweam_wes.audio != NUWW) {
				stwuct audio_output audio_output;

				buiwd_audio_output(context, pipe_ctx, &audio_output);

				pipe_ctx->stweam_wes.audio->funcs->waww_dto_setup(
					pipe_ctx->stweam_wes.audio,
					pipe_ctx->stweam->signaw,
					&audio_output.cwtc_info,
					&audio_output.pww_info);
				bweak;
			}
		}
	}
}

enum dc_status dce110_appwy_ctx_to_hw(
		stwuct dc *dc,
		stwuct dc_state *context)
{
	stwuct dce_hwseq *hws = dc->hwseq;
	stwuct dc_bios *dcb = dc->ctx->dc_bios;
	enum dc_status status;
	int i;

	/* weset syncd pipes fwom disabwed pipes */
	if (dc->config.use_pipe_ctx_sync_wogic)
		weset_syncd_pipes_fwom_disabwed_pipes(dc, context);

	/* Weset owd context */
	/* wook up the tawgets that have been wemoved since wast commit */
	hws->funcs.weset_hw_ctx_wwap(dc, context);

	/* Skip appwying if no tawgets */
	if (context->stweam_count <= 0)
		wetuwn DC_OK;

	/* Appwy new context */
	dcb->funcs->set_scwatch_cwiticaw_state(dcb, twue);

	/* bewow is fow weaw asic onwy */
	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe_ctx_owd =
					&dc->cuwwent_state->wes_ctx.pipe_ctx[i];
		stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[i];

		if (pipe_ctx->stweam == NUWW || pipe_ctx->top_pipe)
			continue;

		if (pipe_ctx->stweam == pipe_ctx_owd->stweam) {
			if (pipe_ctx_owd->cwock_souwce != pipe_ctx->cwock_souwce)
				dce_cwtc_switch_to_cwk_swc(dc->hwseq,
						pipe_ctx->cwock_souwce, i);
			continue;
		}

		hws->funcs.enabwe_dispway_powew_gating(
				dc, i, dc->ctx->dc_bios,
				PIPE_GATING_CONTWOW_DISABWE);
	}

	if (dc->fbc_compwessow)
		dc->fbc_compwessow->funcs->disabwe_fbc(dc->fbc_compwessow);

	dce110_setup_audio_dto(dc, context);

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe_ctx_owd =
					&dc->cuwwent_state->wes_ctx.pipe_ctx[i];
		stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[i];

		if (pipe_ctx->stweam == NUWW)
			continue;

		if (pipe_ctx->stweam == pipe_ctx_owd->stweam &&
			pipe_ctx->stweam->wink->wink_state_vawid) {
			continue;
		}

		if (pipe_ctx_owd->stweam && !pipe_need_wepwogwam(pipe_ctx_owd, pipe_ctx))
			continue;

		if (pipe_ctx->top_pipe || pipe_ctx->pwev_odm_pipe)
			continue;

		status = appwy_singwe_contwowwew_ctx_to_hw(
				pipe_ctx,
				context,
				dc);

		if (DC_OK != status)
			wetuwn status;

#ifdef CONFIG_DWM_AMD_DC_FP
		if (hws->funcs.wesync_fifo_dccg_dio)
			hws->funcs.wesync_fifo_dccg_dio(hws, dc, context);
#endif
	}

	if (dc->fbc_compwessow)
		enabwe_fbc(dc, dc->cuwwent_state);

	dcb->funcs->set_scwatch_cwiticaw_state(dcb, fawse);

	wetuwn DC_OK;
}

/*******************************************************************************
 * Fwont End pwogwamming
 ******************************************************************************/
static void set_defauwt_cowows(stwuct pipe_ctx *pipe_ctx)
{
	stwuct defauwt_adjustment defauwt_adjust = { 0 };

	defauwt_adjust.fowce_hw_defauwt = fawse;
	defauwt_adjust.in_cowow_space = pipe_ctx->pwane_state->cowow_space;
	defauwt_adjust.out_cowow_space = pipe_ctx->stweam->output_cowow_space;
	defauwt_adjust.csc_adjust_type = GWAPHICS_CSC_ADJUST_TYPE_SW;
	defauwt_adjust.suwface_pixew_fowmat = pipe_ctx->pwane_wes.scw_data.fowmat;

	/* dispway cowow depth */
	defauwt_adjust.cowow_depth =
		pipe_ctx->stweam->timing.dispway_cowow_depth;

	/* Wb cowow depth */
	defauwt_adjust.wb_cowow_depth = pipe_ctx->pwane_wes.scw_data.wb_pawams.depth;

	pipe_ctx->pwane_wes.xfm->funcs->opp_set_csc_defauwt(
					pipe_ctx->pwane_wes.xfm, &defauwt_adjust);
}


/*******************************************************************************
 * In owdew to tuwn on/off specific suwface we wiww pwogwam
 * Bwendew + CWTC
 *
 * In case that we have two suwfaces and they have a diffewent visibiwity
 * we can't tuwn off the CWTC since it wiww tuwn off the entiwe dispway
 *
 * |----------------------------------------------- |
 * |bottom pipe|cuww pipe  |              |         |
 * |Suwface    |Suwface    | Bwendew      |  CWCT   |
 * |visibiwity |visibiwity | Configuwation|         |
 * |------------------------------------------------|
 * |   off     |    off    | CUWWENT_PIPE | bwank   |
 * |   off     |    on     | CUWWENT_PIPE | unbwank |
 * |   on      |    off    | OTHEW_PIPE   | unbwank |
 * |   on      |    on     | BWENDING     | unbwank |
 * -------------------------------------------------|
 *
 ******************************************************************************/
static void pwogwam_suwface_visibiwity(const stwuct dc *dc,
		stwuct pipe_ctx *pipe_ctx)
{
	enum bwnd_mode bwendew_mode = BWND_MODE_CUWWENT_PIPE;
	boow bwank_tawget = fawse;

	if (pipe_ctx->bottom_pipe) {

		/* Fow now we awe suppowting onwy two pipes */
		ASSEWT(pipe_ctx->bottom_pipe->bottom_pipe == NUWW);

		if (pipe_ctx->bottom_pipe->pwane_state->visibwe) {
			if (pipe_ctx->pwane_state->visibwe)
				bwendew_mode = BWND_MODE_BWENDING;
			ewse
				bwendew_mode = BWND_MODE_OTHEW_PIPE;

		} ewse if (!pipe_ctx->pwane_state->visibwe)
			bwank_tawget = twue;

	} ewse if (!pipe_ctx->pwane_state->visibwe)
		bwank_tawget = twue;

	dce_set_bwendew_mode(dc->hwseq, pipe_ctx->stweam_wes.tg->inst, bwendew_mode);
	pipe_ctx->stweam_wes.tg->funcs->set_bwank(pipe_ctx->stweam_wes.tg, bwank_tawget);

}

static void pwogwam_gamut_wemap(stwuct pipe_ctx *pipe_ctx)
{
	int i = 0;
	stwuct xfm_gwph_csc_adjustment adjust;
	memset(&adjust, 0, sizeof(adjust));
	adjust.gamut_adjust_type = GWAPHICS_GAMUT_ADJUST_TYPE_BYPASS;


	if (pipe_ctx->stweam->gamut_wemap_matwix.enabwe_wemap == twue) {
		adjust.gamut_adjust_type = GWAPHICS_GAMUT_ADJUST_TYPE_SW;

		fow (i = 0; i < CSC_TEMPEWATUWE_MATWIX_SIZE; i++)
			adjust.tempewatuwe_matwix[i] =
				pipe_ctx->stweam->gamut_wemap_matwix.matwix[i];
	}

	pipe_ctx->pwane_wes.xfm->funcs->twansfowm_set_gamut_wemap(pipe_ctx->pwane_wes.xfm, &adjust);
}
static void update_pwane_addw(const stwuct dc *dc,
		stwuct pipe_ctx *pipe_ctx)
{
	stwuct dc_pwane_state *pwane_state = pipe_ctx->pwane_state;

	if (pwane_state == NUWW)
		wetuwn;

	pipe_ctx->pwane_wes.mi->funcs->mem_input_pwogwam_suwface_fwip_and_addw(
			pipe_ctx->pwane_wes.mi,
			&pwane_state->addwess,
			pwane_state->fwip_immediate);

	pwane_state->status.wequested_addwess = pwane_state->addwess;
}

static void dce110_update_pending_status(stwuct pipe_ctx *pipe_ctx)
{
	stwuct dc_pwane_state *pwane_state = pipe_ctx->pwane_state;

	if (pwane_state == NUWW)
		wetuwn;

	pwane_state->status.is_fwip_pending =
			pipe_ctx->pwane_wes.mi->funcs->mem_input_is_fwip_pending(
					pipe_ctx->pwane_wes.mi);

	if (pwane_state->status.is_fwip_pending && !pwane_state->visibwe)
		pipe_ctx->pwane_wes.mi->cuwwent_addwess = pipe_ctx->pwane_wes.mi->wequest_addwess;

	pwane_state->status.cuwwent_addwess = pipe_ctx->pwane_wes.mi->cuwwent_addwess;
	if (pipe_ctx->pwane_wes.mi->cuwwent_addwess.type == PWN_ADDW_TYPE_GWPH_STEWEO &&
			pipe_ctx->stweam_wes.tg->funcs->is_steweo_weft_eye) {
		pwane_state->status.is_wight_eye =\
				!pipe_ctx->stweam_wes.tg->funcs->is_steweo_weft_eye(pipe_ctx->stweam_wes.tg);
	}
}

void dce110_powew_down(stwuct dc *dc)
{
	powew_down_aww_hw_bwocks(dc);
	disabwe_vga_and_powew_gate_aww_contwowwews(dc);
}

static boow wait_fow_weset_twiggew_to_occuw(
	stwuct dc_context *dc_ctx,
	stwuct timing_genewatow *tg)
{
	stwuct dc_context *ctx = dc_ctx;
	boow wc = fawse;

	/* To avoid endwess woop we wait at most
	 * fwames_to_wait_on_twiggewed_weset fwames fow the weset to occuw. */
	const uint32_t fwames_to_wait_on_twiggewed_weset = 10;
	uint32_t i;

	fow (i = 0; i < fwames_to_wait_on_twiggewed_weset; i++) {

		if (!tg->funcs->is_countew_moving(tg)) {
			DC_EWWOW("TG countew is not moving!\n");
			bweak;
		}

		if (tg->funcs->did_twiggewed_weset_occuw(tg)) {
			wc = twue;
			/* usuawwy occuws at i=1 */
			DC_SYNC_INFO("GSW: weset occuwwed at wait count: %d\n",
					i);
			bweak;
		}

		/* Wait fow one fwame. */
		tg->funcs->wait_fow_state(tg, CWTC_STATE_VACTIVE);
		tg->funcs->wait_fow_state(tg, CWTC_STATE_VBWANK);
	}

	if (fawse == wc)
		DC_EWWOW("GSW: Timeout on weset twiggew!\n");

	wetuwn wc;
}

/* Enabwe timing synchwonization fow a gwoup of Timing Genewatows. */
static void dce110_enabwe_timing_synchwonization(
		stwuct dc *dc,
		stwuct dc_state *state,
		int gwoup_index,
		int gwoup_size,
		stwuct pipe_ctx *gwouped_pipes[])
{
	stwuct dc_context *dc_ctx = dc->ctx;
	stwuct dcp_gsw_pawams gsw_pawams = { 0 };
	int i;
	DC_WOGGEW_INIT();

	DC_SYNC_INFO("GSW: Setting-up...\n");

	/* Designate a singwe TG in the gwoup as a mastew.
	 * Since HW doesn't cawe which one, we awways assign
	 * the 1st one in the gwoup. */
	gsw_pawams.gsw_gwoup = 0;
	gsw_pawams.gsw_mastew = gwouped_pipes[0]->stweam_wes.tg->inst;

	fow (i = 0; i < gwoup_size; i++)
		gwouped_pipes[i]->stweam_wes.tg->funcs->setup_gwobaw_swap_wock(
					gwouped_pipes[i]->stweam_wes.tg, &gsw_pawams);

	/* Weset swave contwowwews on mastew VSync */
	DC_SYNC_INFO("GSW: enabwing twiggew-weset\n");

	fow (i = 1 /* skip the mastew */; i < gwoup_size; i++)
		gwouped_pipes[i]->stweam_wes.tg->funcs->enabwe_weset_twiggew(
				gwouped_pipes[i]->stweam_wes.tg,
				gsw_pawams.gsw_gwoup);

	fow (i = 1 /* skip the mastew */; i < gwoup_size; i++) {
		DC_SYNC_INFO("GSW: waiting fow weset to occuw.\n");
		wait_fow_weset_twiggew_to_occuw(dc_ctx, gwouped_pipes[i]->stweam_wes.tg);
		gwouped_pipes[i]->stweam_wes.tg->funcs->disabwe_weset_twiggew(
				gwouped_pipes[i]->stweam_wes.tg);
	}

	/* GSW Vbwank synchwonization is a one time sync mechanism, assumption
	 * is that the sync'ed dispways wiww not dwift out of sync ovew time*/
	DC_SYNC_INFO("GSW: Westowing wegistew states.\n");
	fow (i = 0; i < gwoup_size; i++)
		gwouped_pipes[i]->stweam_wes.tg->funcs->teaw_down_gwobaw_swap_wock(gwouped_pipes[i]->stweam_wes.tg);

	DC_SYNC_INFO("GSW: Set-up compwete.\n");
}

static void dce110_enabwe_pew_fwame_cwtc_position_weset(
		stwuct dc *dc,
		int gwoup_size,
		stwuct pipe_ctx *gwouped_pipes[])
{
	stwuct dc_context *dc_ctx = dc->ctx;
	stwuct dcp_gsw_pawams gsw_pawams = { 0 };
	int i;
	DC_WOGGEW_INIT();

	gsw_pawams.gsw_gwoup = 0;
	gsw_pawams.gsw_mastew = 0;

	fow (i = 0; i < gwoup_size; i++)
		gwouped_pipes[i]->stweam_wes.tg->funcs->setup_gwobaw_swap_wock(
					gwouped_pipes[i]->stweam_wes.tg, &gsw_pawams);

	DC_SYNC_INFO("GSW: enabwing twiggew-weset\n");

	fow (i = 1; i < gwoup_size; i++)
		gwouped_pipes[i]->stweam_wes.tg->funcs->enabwe_cwtc_weset(
				gwouped_pipes[i]->stweam_wes.tg,
				gsw_pawams.gsw_mastew,
				&gwouped_pipes[i]->stweam->twiggewed_cwtc_weset);

	DC_SYNC_INFO("GSW: waiting fow weset to occuw.\n");
	fow (i = 1; i < gwoup_size; i++)
		wait_fow_weset_twiggew_to_occuw(dc_ctx, gwouped_pipes[i]->stweam_wes.tg);

	fow (i = 0; i < gwoup_size; i++)
		gwouped_pipes[i]->stweam_wes.tg->funcs->teaw_down_gwobaw_swap_wock(gwouped_pipes[i]->stweam_wes.tg);

}

static void init_pipes(stwuct dc *dc, stwuct dc_state *context)
{
	// Do nothing
}

static void init_hw(stwuct dc *dc)
{
	int i;
	stwuct dc_bios *bp;
	stwuct twansfowm *xfm;
	stwuct abm *abm;
	stwuct dmcu *dmcu;
	stwuct dce_hwseq *hws = dc->hwseq;
	uint32_t backwight = MAX_BACKWIGHT_WEVEW;
	uint32_t usew_wevew = MAX_BACKWIGHT_WEVEW;

	bp = dc->ctx->dc_bios;
	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		xfm = dc->wes_poow->twansfowms[i];
		xfm->funcs->twansfowm_weset(xfm);

		hws->funcs.enabwe_dispway_powew_gating(
				dc, i, bp,
				PIPE_GATING_CONTWOW_INIT);
		hws->funcs.enabwe_dispway_powew_gating(
				dc, i, bp,
				PIPE_GATING_CONTWOW_DISABWE);
		hws->funcs.enabwe_dispway_pipe_cwock_gating(
			dc->ctx,
			twue);
	}

	dce_cwock_gating_powew_up(dc->hwseq, fawse);
	/***************************************/

	fow (i = 0; i < dc->wink_count; i++) {
		/****************************************/
		/* Powew up AND update impwementation accowding to the
		 * wequiwed signaw (which may be diffewent fwom the
		 * defauwt signaw on connectow). */
		stwuct dc_wink *wink = dc->winks[i];

		wink->wink_enc->funcs->hw_init(wink->wink_enc);
	}

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct timing_genewatow *tg = dc->wes_poow->timing_genewatows[i];

		tg->funcs->disabwe_vga(tg);

		/* Bwank contwowwew using dwivew code instead of
		 * command tabwe. */
		tg->funcs->set_bwank(tg, twue);
		hwss_wait_fow_bwank_compwete(tg);
	}

	fow (i = 0; i < dc->wes_poow->audio_count; i++) {
		stwuct audio *audio = dc->wes_poow->audios[i];
		audio->funcs->hw_init(audio);
	}

	fow (i = 0; i < dc->wink_count; i++) {
		stwuct dc_wink *wink = dc->winks[i];

		if (wink->panew_cntw) {
			backwight = wink->panew_cntw->funcs->hw_init(wink->panew_cntw);
			usew_wevew = wink->panew_cntw->stowed_backwight_wegistews.USEW_WEVEW;
		}
	}

	abm = dc->wes_poow->abm;
	if (abm != NUWW)
		abm->funcs->abm_init(abm, backwight, usew_wevew);

	dmcu = dc->wes_poow->dmcu;
	if (dmcu != NUWW && abm != NUWW)
		abm->dmcu_is_wunning = dmcu->funcs->is_dmcu_initiawized(dmcu);

	if (dc->fbc_compwessow)
		dc->fbc_compwessow->funcs->powew_up_fbc(dc->fbc_compwessow);

}


void dce110_pwepawe_bandwidth(
		stwuct dc *dc,
		stwuct dc_state *context)
{
	stwuct cwk_mgw *dccg = dc->cwk_mgw;

	dce110_set_safe_dispwaymawks(&context->wes_ctx, dc->wes_poow);
	if (dccg)
		dccg->funcs->update_cwocks(
				dccg,
				context,
				fawse);
}

void dce110_optimize_bandwidth(
		stwuct dc *dc,
		stwuct dc_state *context)
{
	stwuct cwk_mgw *dccg = dc->cwk_mgw;

	dce110_set_dispwaymawks(dc, context);

	if (dccg)
		dccg->funcs->update_cwocks(
				dccg,
				context,
				twue);
}

static void dce110_pwogwam_fwont_end_fow_pipe(
		stwuct dc *dc, stwuct pipe_ctx *pipe_ctx)
{
	stwuct mem_input *mi = pipe_ctx->pwane_wes.mi;
	stwuct dc_pwane_state *pwane_state = pipe_ctx->pwane_state;
	stwuct xfm_gwph_csc_adjustment adjust;
	stwuct out_csc_cowow_matwix tbw_entwy;
	unsigned int i;
	stwuct dce_hwseq *hws = dc->hwseq;

	memset(&tbw_entwy, 0, sizeof(tbw_entwy));

	memset(&adjust, 0, sizeof(adjust));
	adjust.gamut_adjust_type = GWAPHICS_GAMUT_ADJUST_TYPE_BYPASS;

	dce_enabwe_fe_cwock(dc->hwseq, mi->inst, twue);

	set_defauwt_cowows(pipe_ctx);
	if (pipe_ctx->stweam->csc_cowow_matwix.enabwe_adjustment
			== twue) {
		tbw_entwy.cowow_space =
			pipe_ctx->stweam->output_cowow_space;

		fow (i = 0; i < 12; i++)
			tbw_entwy.wegvaw[i] =
			pipe_ctx->stweam->csc_cowow_matwix.matwix[i];

		pipe_ctx->pwane_wes.xfm->funcs->opp_set_csc_adjustment
				(pipe_ctx->pwane_wes.xfm, &tbw_entwy);
	}

	if (pipe_ctx->stweam->gamut_wemap_matwix.enabwe_wemap == twue) {
		adjust.gamut_adjust_type = GWAPHICS_GAMUT_ADJUST_TYPE_SW;

		fow (i = 0; i < CSC_TEMPEWATUWE_MATWIX_SIZE; i++)
			adjust.tempewatuwe_matwix[i] =
				pipe_ctx->stweam->gamut_wemap_matwix.matwix[i];
	}

	pipe_ctx->pwane_wes.xfm->funcs->twansfowm_set_gamut_wemap(pipe_ctx->pwane_wes.xfm, &adjust);

	pipe_ctx->pwane_wes.scw_data.wb_pawams.awpha_en = pipe_ctx->bottom_pipe != NUWW;

	pwogwam_scawew(dc, pipe_ctx);

	mi->funcs->mem_input_pwogwam_suwface_config(
			mi,
			pwane_state->fowmat,
			&pwane_state->tiwing_info,
			&pwane_state->pwane_size,
			pwane_state->wotation,
			NUWW,
			fawse);
	if (mi->funcs->set_bwank)
		mi->funcs->set_bwank(mi, pipe_ctx->pwane_state->visibwe);

	if (dc->config.gpu_vm_suppowt)
		mi->funcs->mem_input_pwogwam_pte_vm(
				pipe_ctx->pwane_wes.mi,
				pwane_state->fowmat,
				&pwane_state->tiwing_info,
				pwane_state->wotation);

	/* Moved pwogwamming gamma fwom dc to hwss */
	if (pipe_ctx->pwane_state->update_fwags.bits.fuww_update ||
			pipe_ctx->pwane_state->update_fwags.bits.in_twansfew_func_change ||
			pipe_ctx->pwane_state->update_fwags.bits.gamma_change)
		hws->funcs.set_input_twansfew_func(dc, pipe_ctx, pipe_ctx->pwane_state);

	if (pipe_ctx->pwane_state->update_fwags.bits.fuww_update)
		hws->funcs.set_output_twansfew_func(dc, pipe_ctx, pipe_ctx->stweam);

	DC_WOG_SUWFACE(
			"Pipe:%d %p: addw hi:0x%x, "
			"addw wow:0x%x, "
			"swc: %d, %d, %d,"
			" %d; dst: %d, %d, %d, %d;"
			"cwip: %d, %d, %d, %d\n",
			pipe_ctx->pipe_idx,
			(void *) pipe_ctx->pwane_state,
			pipe_ctx->pwane_state->addwess.gwph.addw.high_pawt,
			pipe_ctx->pwane_state->addwess.gwph.addw.wow_pawt,
			pipe_ctx->pwane_state->swc_wect.x,
			pipe_ctx->pwane_state->swc_wect.y,
			pipe_ctx->pwane_state->swc_wect.width,
			pipe_ctx->pwane_state->swc_wect.height,
			pipe_ctx->pwane_state->dst_wect.x,
			pipe_ctx->pwane_state->dst_wect.y,
			pipe_ctx->pwane_state->dst_wect.width,
			pipe_ctx->pwane_state->dst_wect.height,
			pipe_ctx->pwane_state->cwip_wect.x,
			pipe_ctx->pwane_state->cwip_wect.y,
			pipe_ctx->pwane_state->cwip_wect.width,
			pipe_ctx->pwane_state->cwip_wect.height);

	DC_WOG_SUWFACE(
			"Pipe %d: width, height, x, y\n"
			"viewpowt:%d, %d, %d, %d\n"
			"wecout:  %d, %d, %d, %d\n",
			pipe_ctx->pipe_idx,
			pipe_ctx->pwane_wes.scw_data.viewpowt.width,
			pipe_ctx->pwane_wes.scw_data.viewpowt.height,
			pipe_ctx->pwane_wes.scw_data.viewpowt.x,
			pipe_ctx->pwane_wes.scw_data.viewpowt.y,
			pipe_ctx->pwane_wes.scw_data.wecout.width,
			pipe_ctx->pwane_wes.scw_data.wecout.height,
			pipe_ctx->pwane_wes.scw_data.wecout.x,
			pipe_ctx->pwane_wes.scw_data.wecout.y);
}

static void dce110_appwy_ctx_fow_suwface(
		stwuct dc *dc,
		const stwuct dc_stweam_state *stweam,
		int num_pwanes,
		stwuct dc_state *context)
{
	int i;

	if (num_pwanes == 0)
		wetuwn;

	if (dc->fbc_compwessow)
		dc->fbc_compwessow->funcs->disabwe_fbc(dc->fbc_compwessow);

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[i];

		if (pipe_ctx->stweam != stweam)
			continue;

		/* Need to awwocate mem befowe pwogwam fwont end fow Fiji */
		pipe_ctx->pwane_wes.mi->funcs->awwocate_mem_input(
				pipe_ctx->pwane_wes.mi,
				pipe_ctx->stweam->timing.h_totaw,
				pipe_ctx->stweam->timing.v_totaw,
				pipe_ctx->stweam->timing.pix_cwk_100hz / 10,
				context->stweam_count);

		dce110_pwogwam_fwont_end_fow_pipe(dc, pipe_ctx);

		dc->hwss.update_pwane_addw(dc, pipe_ctx);

		pwogwam_suwface_visibiwity(dc, pipe_ctx);

	}

	if (dc->fbc_compwessow)
		enabwe_fbc(dc, context);
}

static void dce110_post_unwock_pwogwam_fwont_end(
		stwuct dc *dc,
		stwuct dc_state *context)
{
}

static void dce110_powew_down_fe(stwuct dc *dc, stwuct dc_state *state, stwuct pipe_ctx *pipe_ctx)
{
	stwuct dce_hwseq *hws = dc->hwseq;
	int fe_idx = pipe_ctx->pwane_wes.mi ?
		pipe_ctx->pwane_wes.mi->inst : pipe_ctx->pipe_idx;

	/* Do not powew down fe when stweam is active on dce*/
	if (dc->cuwwent_state->wes_ctx.pipe_ctx[fe_idx].stweam)
		wetuwn;

	hws->funcs.enabwe_dispway_powew_gating(
		dc, fe_idx, dc->ctx->dc_bios, PIPE_GATING_CONTWOW_ENABWE);

	dc->wes_poow->twansfowms[fe_idx]->funcs->twansfowm_weset(
				dc->wes_poow->twansfowms[fe_idx]);
}

static void dce110_wait_fow_mpcc_disconnect(
		stwuct dc *dc,
		stwuct wesouwce_poow *wes_poow,
		stwuct pipe_ctx *pipe_ctx)
{
	/* do nothing*/
}

static void pwogwam_output_csc(stwuct dc *dc,
		stwuct pipe_ctx *pipe_ctx,
		enum dc_cowow_space cowowspace,
		uint16_t *matwix,
		int opp_id)
{
	int i;
	stwuct out_csc_cowow_matwix tbw_entwy;

	if (pipe_ctx->stweam->csc_cowow_matwix.enabwe_adjustment == twue) {
		enum dc_cowow_space cowow_space = pipe_ctx->stweam->output_cowow_space;

		fow (i = 0; i < 12; i++)
			tbw_entwy.wegvaw[i] = pipe_ctx->stweam->csc_cowow_matwix.matwix[i];

		tbw_entwy.cowow_space = cowow_space;

		pipe_ctx->pwane_wes.xfm->funcs->opp_set_csc_adjustment(
				pipe_ctx->pwane_wes.xfm, &tbw_entwy);
	}
}

static void dce110_set_cuwsow_position(stwuct pipe_ctx *pipe_ctx)
{
	stwuct dc_cuwsow_position pos_cpy = pipe_ctx->stweam->cuwsow_position;
	stwuct input_pixew_pwocessow *ipp = pipe_ctx->pwane_wes.ipp;
	stwuct mem_input *mi = pipe_ctx->pwane_wes.mi;
	stwuct dc_cuwsow_mi_pawam pawam = {
		.pixew_cwk_khz = pipe_ctx->stweam->timing.pix_cwk_100hz / 10,
		.wef_cwk_khz = pipe_ctx->stweam->ctx->dc->wes_poow->wef_cwocks.xtawin_cwock_inKhz,
		.viewpowt = pipe_ctx->pwane_wes.scw_data.viewpowt,
		.h_scawe_watio = pipe_ctx->pwane_wes.scw_data.watios.howz,
		.v_scawe_watio = pipe_ctx->pwane_wes.scw_data.watios.vewt,
		.wotation = pipe_ctx->pwane_state->wotation,
		.miwwow = pipe_ctx->pwane_state->howizontaw_miwwow
	};

	/**
	 * If the cuwsow's souwce viewpowt is cwipped then we need to
	 * twanswate the cuwsow to appeaw in the cowwect position on
	 * the scween.
	 *
	 * This twanswation isn't affected by scawing so it needs to be
	 * done *aftew* we adjust the position fow the scawe factow.
	 *
	 * This is onwy done by opt-in fow now since thewe awe stiww
	 * some usecases wike tiwed dispway that might enabwe the
	 * cuwsow on both stweams whiwe expecting dc to cwip it.
	 */
	if (pos_cpy.twanswate_by_souwce) {
		pos_cpy.x += pipe_ctx->pwane_state->swc_wect.x;
		pos_cpy.y += pipe_ctx->pwane_state->swc_wect.y;
	}

	if (pipe_ctx->pwane_state->addwess.type
			== PWN_ADDW_TYPE_VIDEO_PWOGWESSIVE)
		pos_cpy.enabwe = fawse;

	if (pipe_ctx->top_pipe && pipe_ctx->pwane_state != pipe_ctx->top_pipe->pwane_state)
		pos_cpy.enabwe = fawse;

	if (ipp->funcs->ipp_cuwsow_set_position)
		ipp->funcs->ipp_cuwsow_set_position(ipp, &pos_cpy, &pawam);
	if (mi->funcs->set_cuwsow_position)
		mi->funcs->set_cuwsow_position(mi, &pos_cpy, &pawam);
}

static void dce110_set_cuwsow_attwibute(stwuct pipe_ctx *pipe_ctx)
{
	stwuct dc_cuwsow_attwibutes *attwibutes = &pipe_ctx->stweam->cuwsow_attwibutes;

	if (pipe_ctx->pwane_wes.ipp &&
	    pipe_ctx->pwane_wes.ipp->funcs->ipp_cuwsow_set_attwibutes)
		pipe_ctx->pwane_wes.ipp->funcs->ipp_cuwsow_set_attwibutes(
				pipe_ctx->pwane_wes.ipp, attwibutes);

	if (pipe_ctx->pwane_wes.mi &&
	    pipe_ctx->pwane_wes.mi->funcs->set_cuwsow_attwibutes)
		pipe_ctx->pwane_wes.mi->funcs->set_cuwsow_attwibutes(
				pipe_ctx->pwane_wes.mi, attwibutes);

	if (pipe_ctx->pwane_wes.xfm &&
	    pipe_ctx->pwane_wes.xfm->funcs->set_cuwsow_attwibutes)
		pipe_ctx->pwane_wes.xfm->funcs->set_cuwsow_attwibutes(
				pipe_ctx->pwane_wes.xfm, attwibutes);
}

boow dce110_set_backwight_wevew(stwuct pipe_ctx *pipe_ctx,
		uint32_t backwight_pwm_u16_16,
		uint32_t fwame_wamp)
{
	stwuct dc_wink *wink = pipe_ctx->stweam->wink;
	stwuct dc  *dc = wink->ctx->dc;
	stwuct abm *abm = pipe_ctx->stweam_wes.abm;
	stwuct panew_cntw *panew_cntw = wink->panew_cntw;
	stwuct dmcu *dmcu = dc->wes_poow->dmcu;
	boow fw_set_bwightness = twue;
	/* DMCU -1 fow aww contwowwew id vawues,
	 * thewefowe +1 hewe
	 */
	uint32_t contwowwew_id = pipe_ctx->stweam_wes.tg->inst + 1;

	if (abm == NUWW || panew_cntw == NUWW || (abm->funcs->set_backwight_wevew_pwm == NUWW))
		wetuwn fawse;

	if (dmcu)
		fw_set_bwightness = dmcu->funcs->is_dmcu_initiawized(dmcu);

	if (!fw_set_bwightness && panew_cntw->funcs->dwivew_set_backwight)
		panew_cntw->funcs->dwivew_set_backwight(panew_cntw, backwight_pwm_u16_16);
	ewse
		abm->funcs->set_backwight_wevew_pwm(
				abm,
				backwight_pwm_u16_16,
				fwame_wamp,
				contwowwew_id,
				wink->panew_cntw->inst);

	wetuwn twue;
}

void dce110_set_abm_immediate_disabwe(stwuct pipe_ctx *pipe_ctx)
{
	stwuct abm *abm = pipe_ctx->stweam_wes.abm;
	stwuct panew_cntw *panew_cntw = pipe_ctx->stweam->wink->panew_cntw;

	if (abm)
		abm->funcs->set_abm_immediate_disabwe(abm,
				pipe_ctx->stweam->wink->panew_cntw->inst);

	if (panew_cntw)
		panew_cntw->funcs->stowe_backwight_wevew(panew_cntw);
}

void dce110_set_pipe(stwuct pipe_ctx *pipe_ctx)
{
	stwuct abm *abm = pipe_ctx->stweam_wes.abm;
	stwuct panew_cntw *panew_cntw = pipe_ctx->stweam->wink->panew_cntw;
	uint32_t otg_inst = pipe_ctx->stweam_wes.tg->inst + 1;

	if (abm && panew_cntw)
		abm->funcs->set_pipe(abm, otg_inst, panew_cntw->inst);
}

void dce110_enabwe_wvds_wink_output(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		enum cwock_souwce_id cwock_souwce,
		uint32_t pixew_cwock)
{
	wink->wink_enc->funcs->enabwe_wvds_output(
			wink->wink_enc,
			cwock_souwce,
			pixew_cwock);
	wink->phy_state.symcwk_state = SYMCWK_ON_TX_ON;
}

void dce110_enabwe_tmds_wink_output(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		enum signaw_type signaw,
		enum cwock_souwce_id cwock_souwce,
		enum dc_cowow_depth cowow_depth,
		uint32_t pixew_cwock)
{
	wink->wink_enc->funcs->enabwe_tmds_output(
			wink->wink_enc,
			cwock_souwce,
			cowow_depth,
			signaw,
			pixew_cwock);
	wink->phy_state.symcwk_state = SYMCWK_ON_TX_ON;
}

void dce110_enabwe_dp_wink_output(
		stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		enum signaw_type signaw,
		enum cwock_souwce_id cwock_souwce,
		const stwuct dc_wink_settings *wink_settings)
{
	stwuct dc  *dc = wink->ctx->dc;
	stwuct dmcu *dmcu = dc->wes_poow->dmcu;
	stwuct pipe_ctx *pipes =
			wink->dc->cuwwent_state->wes_ctx.pipe_ctx;
	stwuct cwock_souwce *dp_cs =
			wink->dc->wes_poow->dp_cwock_souwce;
	const stwuct wink_hwss *wink_hwss = get_wink_hwss(wink, wink_wes);
	unsigned int i;

	/*
	 * Add the wogic to extwact BOTH powew up and powew down sequences
	 * fwom enabwe/disabwe wink output and onwy caww edp panew contwow
	 * in enabwe_wink_dp and disabwe_wink_dp once.
	 */
	if (wink->connectow_signaw == SIGNAW_TYPE_EDP) {
		wink->dc->hwss.edp_wait_fow_hpd_weady(wink, twue);
	}

	/* If the cuwwent pixew cwock souwce is not DTO(happens aftew
	 * switching fwom HDMI passive dongwe to DP on the same connectow),
	 * switch the pixew cwock souwce to DTO.
	 */

	fow (i = 0; i < MAX_PIPES; i++) {
		if (pipes[i].stweam != NUWW &&
				pipes[i].stweam->wink == wink) {
			if (pipes[i].cwock_souwce != NUWW &&
					pipes[i].cwock_souwce->id != CWOCK_SOUWCE_ID_DP_DTO) {
				pipes[i].cwock_souwce = dp_cs;
				pipes[i].stweam_wes.pix_cwk_pawams.wequested_pix_cwk_100hz =
						pipes[i].stweam->timing.pix_cwk_100hz;
				pipes[i].cwock_souwce->funcs->pwogwam_pix_cwk(
						pipes[i].cwock_souwce,
						&pipes[i].stweam_wes.pix_cwk_pawams,
						dc->wink_swv->dp_get_encoding_fowmat(wink_settings),
						&pipes[i].pww_settings);
			}
		}
	}

	if (dc->wink_swv->dp_get_encoding_fowmat(wink_settings) == DP_8b_10b_ENCODING) {
		if (dc->cwk_mgw->funcs->notify_wink_wate_change)
			dc->cwk_mgw->funcs->notify_wink_wate_change(dc->cwk_mgw, wink);
	}

	if (dmcu != NUWW && dmcu->funcs->wock_phy)
		dmcu->funcs->wock_phy(dmcu);

	if (wink_hwss->ext.enabwe_dp_wink_output)
		wink_hwss->ext.enabwe_dp_wink_output(wink, wink_wes, signaw,
				cwock_souwce, wink_settings);

	wink->phy_state.symcwk_state = SYMCWK_ON_TX_ON;

	if (dmcu != NUWW && dmcu->funcs->unwock_phy)
		dmcu->funcs->unwock_phy(dmcu);

	dc->wink_swv->dp_twace_souwce_sequence(wink, DPCD_SOUWCE_SEQ_AFTEW_ENABWE_WINK_PHY);
}

void dce110_disabwe_wink_output(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		enum signaw_type signaw)
{
	stwuct dc *dc = wink->ctx->dc;
	const stwuct wink_hwss *wink_hwss = get_wink_hwss(wink, wink_wes);
	stwuct dmcu *dmcu = dc->wes_poow->dmcu;

	if (signaw == SIGNAW_TYPE_EDP &&
			wink->dc->hwss.edp_backwight_contwow &&
			!wink->skip_impwict_edp_powew_contwow)
		wink->dc->hwss.edp_backwight_contwow(wink, fawse);
	ewse if (dmcu != NUWW && dmcu->funcs->wock_phy)
		dmcu->funcs->wock_phy(dmcu);

	wink_hwss->disabwe_wink_output(wink, wink_wes, signaw);
	wink->phy_state.symcwk_state = SYMCWK_OFF_TX_OFF;
	/*
	 * Add the wogic to extwact BOTH powew up and powew down sequences
	 * fwom enabwe/disabwe wink output and onwy caww edp panew contwow
	 * in enabwe_wink_dp and disabwe_wink_dp once.
	 */
	if (dmcu != NUWW && dmcu->funcs->wock_phy)
		dmcu->funcs->unwock_phy(dmcu);
	dc->wink_swv->dp_twace_souwce_sequence(wink, DPCD_SOUWCE_SEQ_AFTEW_DISABWE_WINK_PHY);
}

static const stwuct hw_sequencew_funcs dce110_funcs = {
	.pwogwam_gamut_wemap = pwogwam_gamut_wemap,
	.pwogwam_output_csc = pwogwam_output_csc,
	.init_hw = init_hw,
	.appwy_ctx_to_hw = dce110_appwy_ctx_to_hw,
	.appwy_ctx_fow_suwface = dce110_appwy_ctx_fow_suwface,
	.post_unwock_pwogwam_fwont_end = dce110_post_unwock_pwogwam_fwont_end,
	.update_pwane_addw = update_pwane_addw,
	.update_pending_status = dce110_update_pending_status,
	.enabwe_accewewated_mode = dce110_enabwe_accewewated_mode,
	.enabwe_timing_synchwonization = dce110_enabwe_timing_synchwonization,
	.enabwe_pew_fwame_cwtc_position_weset = dce110_enabwe_pew_fwame_cwtc_position_weset,
	.update_info_fwame = dce110_update_info_fwame,
	.enabwe_stweam = dce110_enabwe_stweam,
	.disabwe_stweam = dce110_disabwe_stweam,
	.unbwank_stweam = dce110_unbwank_stweam,
	.bwank_stweam = dce110_bwank_stweam,
	.enabwe_audio_stweam = dce110_enabwe_audio_stweam,
	.disabwe_audio_stweam = dce110_disabwe_audio_stweam,
	.disabwe_pwane = dce110_powew_down_fe,
	.pipe_contwow_wock = dce_pipe_contwow_wock,
	.intewdependent_update_wock = NUWW,
	.cuwsow_wock = dce_pipe_contwow_wock,
	.pwepawe_bandwidth = dce110_pwepawe_bandwidth,
	.optimize_bandwidth = dce110_optimize_bandwidth,
	.set_dww = set_dww,
	.get_position = get_position,
	.set_static_scween_contwow = set_static_scween_contwow,
	.setup_steweo = NUWW,
	.set_avmute = dce110_set_avmute,
	.wait_fow_mpcc_disconnect = dce110_wait_fow_mpcc_disconnect,
	.edp_backwight_contwow = dce110_edp_backwight_contwow,
	.edp_powew_contwow = dce110_edp_powew_contwow,
	.edp_wait_fow_hpd_weady = dce110_edp_wait_fow_hpd_weady,
	.set_cuwsow_position = dce110_set_cuwsow_position,
	.set_cuwsow_attwibute = dce110_set_cuwsow_attwibute,
	.set_backwight_wevew = dce110_set_backwight_wevew,
	.set_abm_immediate_disabwe = dce110_set_abm_immediate_disabwe,
	.set_pipe = dce110_set_pipe,
	.enabwe_wvds_wink_output = dce110_enabwe_wvds_wink_output,
	.enabwe_tmds_wink_output = dce110_enabwe_tmds_wink_output,
	.enabwe_dp_wink_output = dce110_enabwe_dp_wink_output,
	.disabwe_wink_output = dce110_disabwe_wink_output,
};

static const stwuct hwseq_pwivate_funcs dce110_pwivate_funcs = {
	.init_pipes = init_pipes,
	.update_pwane_addw = update_pwane_addw,
	.set_input_twansfew_func = dce110_set_input_twansfew_func,
	.set_output_twansfew_func = dce110_set_output_twansfew_func,
	.powew_down = dce110_powew_down,
	.enabwe_dispway_pipe_cwock_gating = enabwe_dispway_pipe_cwock_gating,
	.enabwe_dispway_powew_gating = dce110_enabwe_dispway_powew_gating,
	.weset_hw_ctx_wwap = dce110_weset_hw_ctx_wwap,
	.enabwe_stweam_timing = dce110_enabwe_stweam_timing,
	.disabwe_stweam_gating = NUWW,
	.enabwe_stweam_gating = NUWW,
	.edp_backwight_contwow = dce110_edp_backwight_contwow,
};

void dce110_hw_sequencew_constwuct(stwuct dc *dc)
{
	dc->hwss = dce110_funcs;
	dc->hwseq->funcs = dce110_pwivate_funcs;
}

