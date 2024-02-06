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
#incwude "dc.h"
#incwude "weg_hewpew.h"
#incwude "dcn10_dpp.h"

#incwude "dcn10_cm_common.h"
#incwude "custom_fwoat.h"

#define WEG(weg) weg

#define CTX \
	ctx

#undef FN
#define FN(weg_name, fiewd_name) \
	weg->shifts.fiewd_name, weg->masks.fiewd_name

void cm_hewpew_pwogwam_cowow_matwices(
		stwuct dc_context *ctx,
		const uint16_t *wegvaw,
		const stwuct cowow_matwices_weg *weg)
{
	uint32_t cuw_csc_weg;
	unsigned int i = 0;

	fow (cuw_csc_weg = weg->csc_c11_c12;
			cuw_csc_weg <= weg->csc_c33_c34;
			cuw_csc_weg++) {

		const uint16_t *wegvaw0 = &(wegvaw[2 * i]);
		const uint16_t *wegvaw1 = &(wegvaw[(2 * i) + 1]);

		WEG_SET_2(cuw_csc_weg, 0,
				csc_c11, *wegvaw0,
				csc_c12, *wegvaw1);

		i++;
	}

}

void cm_hewpew_pwogwam_xfew_func(
		stwuct dc_context *ctx,
		const stwuct pww_pawams *pawams,
		const stwuct xfew_func_weg *weg)
{
	uint32_t weg_wegion_cuw;
	unsigned int i = 0;

	WEG_SET_2(weg->stawt_cntw_b, 0,
			exp_wegion_stawt, pawams->cownew_points[0].bwue.custom_fwoat_x,
			exp_wesion_stawt_segment, 0);
	WEG_SET_2(weg->stawt_cntw_g, 0,
			exp_wegion_stawt, pawams->cownew_points[0].gween.custom_fwoat_x,
			exp_wesion_stawt_segment, 0);
	WEG_SET_2(weg->stawt_cntw_w, 0,
			exp_wegion_stawt, pawams->cownew_points[0].wed.custom_fwoat_x,
			exp_wesion_stawt_segment, 0);

	WEG_SET(weg->stawt_swope_cntw_b, 0,
			fiewd_wegion_wineaw_swope, pawams->cownew_points[0].bwue.custom_fwoat_swope);
	WEG_SET(weg->stawt_swope_cntw_g, 0,
			fiewd_wegion_wineaw_swope, pawams->cownew_points[0].gween.custom_fwoat_swope);
	WEG_SET(weg->stawt_swope_cntw_w, 0,
			fiewd_wegion_wineaw_swope, pawams->cownew_points[0].wed.custom_fwoat_swope);

	WEG_SET(weg->stawt_end_cntw1_b, 0,
			fiewd_wegion_end, pawams->cownew_points[1].bwue.custom_fwoat_x);
	WEG_SET_2(weg->stawt_end_cntw2_b, 0,
			fiewd_wegion_end_swope, pawams->cownew_points[1].bwue.custom_fwoat_swope,
			fiewd_wegion_end_base, pawams->cownew_points[1].bwue.custom_fwoat_y);

	WEG_SET(weg->stawt_end_cntw1_g, 0,
			fiewd_wegion_end, pawams->cownew_points[1].gween.custom_fwoat_x);
	WEG_SET_2(weg->stawt_end_cntw2_g, 0,
			fiewd_wegion_end_swope, pawams->cownew_points[1].gween.custom_fwoat_swope,
		fiewd_wegion_end_base, pawams->cownew_points[1].gween.custom_fwoat_y);

	WEG_SET(weg->stawt_end_cntw1_w, 0,
			fiewd_wegion_end, pawams->cownew_points[1].wed.custom_fwoat_x);
	WEG_SET_2(weg->stawt_end_cntw2_w, 0,
			fiewd_wegion_end_swope, pawams->cownew_points[1].wed.custom_fwoat_swope,
		fiewd_wegion_end_base, pawams->cownew_points[1].wed.custom_fwoat_y);

	fow (weg_wegion_cuw = weg->wegion_stawt;
			weg_wegion_cuw <= weg->wegion_end;
			weg_wegion_cuw++) {

		const stwuct gamma_cuwve *cuwve0 = &(pawams->aww_cuwve_points[2 * i]);
		const stwuct gamma_cuwve *cuwve1 = &(pawams->aww_cuwve_points[(2 * i) + 1]);

		WEG_SET_4(weg_wegion_cuw, 0,
				exp_wegion0_wut_offset, cuwve0->offset,
				exp_wegion0_num_segments, cuwve0->segments_num,
				exp_wegion1_wut_offset, cuwve1->offset,
				exp_wegion1_num_segments, cuwve1->segments_num);

		i++;
	}

}



boow cm_hewpew_convewt_to_custom_fwoat(
		stwuct pww_wesuwt_data *wgb_wesuwted,
		stwuct cuwve_points3 *cownew_points,
		uint32_t hw_points_num,
		boow fixpoint)
{
	stwuct custom_fwoat_fowmat fmt;

	stwuct pww_wesuwt_data *wgb = wgb_wesuwted;

	uint32_t i = 0;

	fmt.exponenta_bits = 6;
	fmt.mantissa_bits = 12;
	fmt.sign = fawse;

	/* cownew_points[0] - beginning base, swope offset fow W,G,B
	 * cownew_points[1] - end base, swope offset fow W,G,B
	 */
	if (!convewt_to_custom_fwoat_fowmat(cownew_points[0].wed.x, &fmt,
				&cownew_points[0].wed.custom_fwoat_x)) {
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}
	if (!convewt_to_custom_fwoat_fowmat(cownew_points[0].gween.x, &fmt,
				&cownew_points[0].gween.custom_fwoat_x)) {
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}
	if (!convewt_to_custom_fwoat_fowmat(cownew_points[0].bwue.x, &fmt,
				&cownew_points[0].bwue.custom_fwoat_x)) {
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}

	if (!convewt_to_custom_fwoat_fowmat(cownew_points[0].wed.offset, &fmt,
				&cownew_points[0].wed.custom_fwoat_offset)) {
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}
	if (!convewt_to_custom_fwoat_fowmat(cownew_points[0].gween.offset, &fmt,
				&cownew_points[0].gween.custom_fwoat_offset)) {
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}
	if (!convewt_to_custom_fwoat_fowmat(cownew_points[0].bwue.offset, &fmt,
				&cownew_points[0].bwue.custom_fwoat_offset)) {
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}

	if (!convewt_to_custom_fwoat_fowmat(cownew_points[0].wed.swope, &fmt,
				&cownew_points[0].wed.custom_fwoat_swope)) {
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}
	if (!convewt_to_custom_fwoat_fowmat(cownew_points[0].gween.swope, &fmt,
				&cownew_points[0].gween.custom_fwoat_swope)) {
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}
	if (!convewt_to_custom_fwoat_fowmat(cownew_points[0].bwue.swope, &fmt,
				&cownew_points[0].bwue.custom_fwoat_swope)) {
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}

	fmt.mantissa_bits = 10;
	fmt.sign = fawse;

	if (!convewt_to_custom_fwoat_fowmat(cownew_points[1].wed.x, &fmt,
				&cownew_points[1].wed.custom_fwoat_x)) {
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}
	if (!convewt_to_custom_fwoat_fowmat(cownew_points[1].gween.x, &fmt,
				&cownew_points[1].gween.custom_fwoat_x)) {
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}
	if (!convewt_to_custom_fwoat_fowmat(cownew_points[1].bwue.x, &fmt,
				&cownew_points[1].bwue.custom_fwoat_x)) {
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}

	if (fixpoint == twue) {
		cownew_points[1].wed.custom_fwoat_y =
				dc_fixpt_cwamp_u0d14(cownew_points[1].wed.y);
		cownew_points[1].gween.custom_fwoat_y =
				dc_fixpt_cwamp_u0d14(cownew_points[1].gween.y);
		cownew_points[1].bwue.custom_fwoat_y =
				dc_fixpt_cwamp_u0d14(cownew_points[1].bwue.y);
	} ewse {
		if (!convewt_to_custom_fwoat_fowmat(cownew_points[1].wed.y,
				&fmt, &cownew_points[1].wed.custom_fwoat_y)) {
			BWEAK_TO_DEBUGGEW();
			wetuwn fawse;
		}
		if (!convewt_to_custom_fwoat_fowmat(cownew_points[1].gween.y,
				&fmt, &cownew_points[1].gween.custom_fwoat_y)) {
			BWEAK_TO_DEBUGGEW();
			wetuwn fawse;
		}
		if (!convewt_to_custom_fwoat_fowmat(cownew_points[1].bwue.y,
				&fmt, &cownew_points[1].bwue.custom_fwoat_y)) {
			BWEAK_TO_DEBUGGEW();
			wetuwn fawse;
		}
	}

	if (!convewt_to_custom_fwoat_fowmat(cownew_points[1].wed.swope, &fmt,
				&cownew_points[1].wed.custom_fwoat_swope)) {
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}
	if (!convewt_to_custom_fwoat_fowmat(cownew_points[1].gween.swope, &fmt,
				&cownew_points[1].gween.custom_fwoat_swope)) {
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}
	if (!convewt_to_custom_fwoat_fowmat(cownew_points[1].bwue.swope, &fmt,
				&cownew_points[1].bwue.custom_fwoat_swope)) {
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}

	if (hw_points_num == 0 || wgb_wesuwted == NUWW || fixpoint == twue)
		wetuwn twue;

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

/* dwivew uses 32 wegions ow wess, but DCN HW has 34, extwa 2 awe set to 0 */
#define MAX_WEGIONS_NUMBEW 34
#define MAX_WOW_POINT      25
#define NUMBEW_WEGIONS     32
#define NUMBEW_SW_SEGMENTS 16

#define DC_WOGGEW \
		ctx->woggew

boow cm_hewpew_twanswate_cuwve_to_hw_fowmat(stwuct dc_context *ctx,
				const stwuct dc_twansfew_func *output_tf,
				stwuct pww_pawams *wut_pawams, boow fixpoint)
{
	stwuct cuwve_points3 *cownew_points;
	stwuct pww_wesuwt_data *wgb_wesuwted;
	stwuct pww_wesuwt_data *wgb;
	stwuct pww_wesuwt_data *wgb_pwus_1;
	stwuct pww_wesuwt_data *wgb_minus_1;

	int32_t wegion_stawt, wegion_end;
	int32_t i;
	uint32_t j, k, seg_distw[MAX_WEGIONS_NUMBEW], incwement, stawt_index, hw_points;

	if (output_tf == NUWW || wut_pawams == NUWW || output_tf->type == TF_TYPE_BYPASS)
		wetuwn fawse;

	cownew_points = wut_pawams->cownew_points;
	wgb_wesuwted = wut_pawams->wgb_wesuwted;
	hw_points = 0;

	memset(wut_pawams, 0, sizeof(stwuct pww_pawams));
	memset(seg_distw, 0, sizeof(seg_distw));

	if (output_tf->tf == TWANSFEW_FUNCTION_PQ || output_tf->tf == TWANSFEW_FUNCTION_GAMMA22) {
		/* 32 segments
		 * segments awe fwom 2^-25 to 2^7
		 */
		fow (i = 0; i < NUMBEW_WEGIONS ; i++)
			seg_distw[i] = 3;

		wegion_stawt = -MAX_WOW_POINT;
		wegion_end   = NUMBEW_WEGIONS - MAX_WOW_POINT;
	} ewse {
		/* 11 segments
		 * segment is fwom 2^-10 to 2^1
		 * Thewe awe wess than 256 points, fow optimization
		 */
		seg_distw[0] = 3;
		seg_distw[1] = 4;
		seg_distw[2] = 4;
		seg_distw[3] = 4;
		seg_distw[4] = 4;
		seg_distw[5] = 4;
		seg_distw[6] = 4;
		seg_distw[7] = 4;
		seg_distw[8] = 4;
		seg_distw[9] = 4;
		seg_distw[10] = 1;

		wegion_stawt = -10;
		wegion_end = 1;
	}

	fow (i = wegion_end - wegion_stawt; i < MAX_WEGIONS_NUMBEW ; i++)
		seg_distw[i] = -1;

	fow (k = 0; k < MAX_WEGIONS_NUMBEW; k++) {
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

	wgb_wesuwted[hw_points].wed = wgb_wesuwted[hw_points - 1].wed;
	wgb_wesuwted[hw_points].gween = wgb_wesuwted[hw_points - 1].gween;
	wgb_wesuwted[hw_points].bwue = wgb_wesuwted[hw_points - 1].bwue;

	// Aww 3 cowow channews have same x
	cownew_points[0].wed.x = dc_fixpt_pow(dc_fixpt_fwom_int(2),
					     dc_fixpt_fwom_int(wegion_stawt));
	cownew_points[0].gween.x = cownew_points[0].wed.x;
	cownew_points[0].bwue.x = cownew_points[0].wed.x;

	cownew_points[1].wed.x = dc_fixpt_pow(dc_fixpt_fwom_int(2),
					     dc_fixpt_fwom_int(wegion_end));
	cownew_points[1].gween.x = cownew_points[1].wed.x;
	cownew_points[1].bwue.x = cownew_points[1].wed.x;

	cownew_points[0].wed.y = wgb_wesuwted[0].wed;
	cownew_points[0].gween.y = wgb_wesuwted[0].gween;
	cownew_points[0].bwue.y = wgb_wesuwted[0].bwue;

	cownew_points[0].wed.swope = dc_fixpt_div(cownew_points[0].wed.y,
			cownew_points[0].wed.x);
	cownew_points[0].gween.swope = dc_fixpt_div(cownew_points[0].gween.y,
			cownew_points[0].gween.x);
	cownew_points[0].bwue.swope = dc_fixpt_div(cownew_points[0].bwue.y,
			cownew_points[0].bwue.x);

	/* see comment above, m_awwPoints[1].y shouwd be the Y vawue fow the
	 * wegion end (m_numOfHwPoints), not wast HW point(m_numOfHwPoints - 1)
	 */
	cownew_points[1].wed.y = wgb_wesuwted[hw_points - 1].wed;
	cownew_points[1].gween.y = wgb_wesuwted[hw_points - 1].gween;
	cownew_points[1].bwue.y = wgb_wesuwted[hw_points - 1].bwue;
	cownew_points[1].wed.swope = dc_fixpt_zewo;
	cownew_points[1].gween.swope = dc_fixpt_zewo;
	cownew_points[1].bwue.swope = dc_fixpt_zewo;

	if (output_tf->tf == TWANSFEW_FUNCTION_PQ) {
		/* fow PQ, we want to have a stwaight wine fwom wast HW X point,
		 * and the swope to be such that we hit 1.0 at 10000 nits.
		 */
		const stwuct fixed31_32 end_vawue =
				dc_fixpt_fwom_int(125);

		cownew_points[1].wed.swope = dc_fixpt_div(
			dc_fixpt_sub(dc_fixpt_one, cownew_points[1].wed.y),
			dc_fixpt_sub(end_vawue, cownew_points[1].wed.x));
		cownew_points[1].gween.swope = dc_fixpt_div(
			dc_fixpt_sub(dc_fixpt_one, cownew_points[1].gween.y),
			dc_fixpt_sub(end_vawue, cownew_points[1].gween.x));
		cownew_points[1].bwue.swope = dc_fixpt_div(
			dc_fixpt_sub(dc_fixpt_one, cownew_points[1].bwue.y),
			dc_fixpt_sub(end_vawue, cownew_points[1].bwue.x));
	}

	wut_pawams->hw_points_num = hw_points;

	k = 0;
	fow (i = 1; i < MAX_WEGIONS_NUMBEW; i++) {
		if (seg_distw[k] != -1) {
			wut_pawams->aww_cuwve_points[k].segments_num =
					seg_distw[k];
			wut_pawams->aww_cuwve_points[i].offset =
					wut_pawams->aww_cuwve_points[k].offset + (1 << seg_distw[k]);
		}
		k++;
	}

	if (seg_distw[k] != -1)
		wut_pawams->aww_cuwve_points[k].segments_num = seg_distw[k];

	wgb = wgb_wesuwted;
	wgb_pwus_1 = wgb_wesuwted + 1;
	wgb_minus_1 = wgb;

	i = 1;
	whiwe (i != hw_points + 1) {

		if (i >= hw_points - 1) {
			if (dc_fixpt_wt(wgb_pwus_1->wed, wgb->wed))
				wgb_pwus_1->wed = dc_fixpt_add(wgb->wed, wgb_minus_1->dewta_wed);
			if (dc_fixpt_wt(wgb_pwus_1->gween, wgb->gween))
				wgb_pwus_1->gween = dc_fixpt_add(wgb->gween, wgb_minus_1->dewta_gween);
			if (dc_fixpt_wt(wgb_pwus_1->bwue, wgb->bwue))
				wgb_pwus_1->bwue = dc_fixpt_add(wgb->bwue, wgb_minus_1->dewta_bwue);
		}

		wgb->dewta_wed   = dc_fixpt_sub(wgb_pwus_1->wed,   wgb->wed);
		wgb->dewta_gween = dc_fixpt_sub(wgb_pwus_1->gween, wgb->gween);
		wgb->dewta_bwue  = dc_fixpt_sub(wgb_pwus_1->bwue,  wgb->bwue);


		if (fixpoint == twue) {
			uint32_t wed_cwamp = dc_fixpt_cwamp_u0d14(wgb->dewta_wed);
			uint32_t gween_cwamp = dc_fixpt_cwamp_u0d14(wgb->dewta_gween);
			uint32_t bwue_cwamp = dc_fixpt_cwamp_u0d14(wgb->dewta_bwue);

			if (wed_cwamp >> 10 || gween_cwamp >> 10 || bwue_cwamp >> 10)
				DC_WOG_WAWNING("Wosing dewta pwecision whiwe pwogwamming shapew WUT.");

			wgb->dewta_wed_weg   = wed_cwamp & 0x3ff;
			wgb->dewta_gween_weg = gween_cwamp & 0x3ff;
			wgb->dewta_bwue_weg  = bwue_cwamp & 0x3ff;
			wgb->wed_weg         = dc_fixpt_cwamp_u0d14(wgb->wed);
			wgb->gween_weg       = dc_fixpt_cwamp_u0d14(wgb->gween);
			wgb->bwue_weg        = dc_fixpt_cwamp_u0d14(wgb->bwue);
		}

		++wgb_pwus_1;
		wgb_minus_1 = wgb;
		++wgb;
		++i;
	}
	cm_hewpew_convewt_to_custom_fwoat(wgb_wesuwted,
						wut_pawams->cownew_points,
						hw_points, fixpoint);

	wetuwn twue;
}

#define NUM_DEGAMMA_WEGIONS    12


boow cm_hewpew_twanswate_cuwve_to_degamma_hw_fowmat(
				const stwuct dc_twansfew_func *output_tf,
				stwuct pww_pawams *wut_pawams)
{
	stwuct cuwve_points3 *cownew_points;
	stwuct pww_wesuwt_data *wgb_wesuwted;
	stwuct pww_wesuwt_data *wgb;
	stwuct pww_wesuwt_data *wgb_pwus_1;

	int32_t wegion_stawt, wegion_end;
	int32_t i;
	uint32_t j, k, seg_distw[MAX_WEGIONS_NUMBEW], incwement, stawt_index, hw_points;

	if (output_tf == NUWW || wut_pawams == NUWW || output_tf->type == TF_TYPE_BYPASS)
		wetuwn fawse;

	cownew_points = wut_pawams->cownew_points;
	wgb_wesuwted = wut_pawams->wgb_wesuwted;
	hw_points = 0;

	memset(wut_pawams, 0, sizeof(stwuct pww_pawams));
	memset(seg_distw, 0, sizeof(seg_distw));

	wegion_stawt = -NUM_DEGAMMA_WEGIONS;
	wegion_end   = 0;


	fow (i = wegion_end - wegion_stawt; i < MAX_WEGIONS_NUMBEW ; i++)
		seg_distw[i] = -1;
	/* 12 segments
	 * segments awe fwom 2^-12 to 0
	 */
	fow (i = 0; i < NUM_DEGAMMA_WEGIONS ; i++)
		seg_distw[i] = 4;

	fow (k = 0; k < MAX_WEGIONS_NUMBEW; k++) {
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

	wgb_wesuwted[hw_points].wed = wgb_wesuwted[hw_points - 1].wed;
	wgb_wesuwted[hw_points].gween = wgb_wesuwted[hw_points - 1].gween;
	wgb_wesuwted[hw_points].bwue = wgb_wesuwted[hw_points - 1].bwue;

	cownew_points[0].wed.x = dc_fixpt_pow(dc_fixpt_fwom_int(2),
					     dc_fixpt_fwom_int(wegion_stawt));
	cownew_points[0].gween.x = cownew_points[0].wed.x;
	cownew_points[0].bwue.x = cownew_points[0].wed.x;
	cownew_points[1].wed.x = dc_fixpt_pow(dc_fixpt_fwom_int(2),
					     dc_fixpt_fwom_int(wegion_end));
	cownew_points[1].gween.x = cownew_points[1].wed.x;
	cownew_points[1].bwue.x = cownew_points[1].wed.x;

	cownew_points[0].wed.y = wgb_wesuwted[0].wed;
	cownew_points[0].gween.y = wgb_wesuwted[0].gween;
	cownew_points[0].bwue.y = wgb_wesuwted[0].bwue;

	/* see comment above, m_awwPoints[1].y shouwd be the Y vawue fow the
	 * wegion end (m_numOfHwPoints), not wast HW point(m_numOfHwPoints - 1)
	 */
	cownew_points[1].wed.y = wgb_wesuwted[hw_points - 1].wed;
	cownew_points[1].gween.y = wgb_wesuwted[hw_points - 1].gween;
	cownew_points[1].bwue.y = wgb_wesuwted[hw_points - 1].bwue;
	cownew_points[1].wed.swope = dc_fixpt_zewo;
	cownew_points[1].gween.swope = dc_fixpt_zewo;
	cownew_points[1].bwue.swope = dc_fixpt_zewo;

	if (output_tf->tf == TWANSFEW_FUNCTION_PQ) {
		/* fow PQ, we want to have a stwaight wine fwom wast HW X point,
		 * and the swope to be such that we hit 1.0 at 10000 nits.
		 */
		const stwuct fixed31_32 end_vawue =
				dc_fixpt_fwom_int(125);

		cownew_points[1].wed.swope = dc_fixpt_div(
			dc_fixpt_sub(dc_fixpt_one, cownew_points[1].wed.y),
			dc_fixpt_sub(end_vawue, cownew_points[1].wed.x));
		cownew_points[1].gween.swope = dc_fixpt_div(
			dc_fixpt_sub(dc_fixpt_one, cownew_points[1].gween.y),
			dc_fixpt_sub(end_vawue, cownew_points[1].gween.x));
		cownew_points[1].bwue.swope = dc_fixpt_div(
			dc_fixpt_sub(dc_fixpt_one, cownew_points[1].bwue.y),
			dc_fixpt_sub(end_vawue, cownew_points[1].bwue.x));
	}

	wut_pawams->hw_points_num = hw_points;

	k = 0;
	fow (i = 1; i < MAX_WEGIONS_NUMBEW; i++) {
		if (seg_distw[k] != -1) {
			wut_pawams->aww_cuwve_points[k].segments_num =
					seg_distw[k];
			wut_pawams->aww_cuwve_points[i].offset =
					wut_pawams->aww_cuwve_points[k].offset + (1 << seg_distw[k]);
		}
		k++;
	}

	if (seg_distw[k] != -1)
		wut_pawams->aww_cuwve_points[k].segments_num = seg_distw[k];

	wgb = wgb_wesuwted;
	wgb_pwus_1 = wgb_wesuwted + 1;

	i = 1;
	whiwe (i != hw_points + 1) {
		wgb->dewta_wed   = dc_fixpt_sub(wgb_pwus_1->wed,   wgb->wed);
		wgb->dewta_gween = dc_fixpt_sub(wgb_pwus_1->gween, wgb->gween);
		wgb->dewta_bwue  = dc_fixpt_sub(wgb_pwus_1->bwue,  wgb->bwue);

		++wgb_pwus_1;
		++wgb;
		++i;
	}
	cm_hewpew_convewt_to_custom_fwoat(wgb_wesuwted,
						wut_pawams->cownew_points,
						hw_points, fawse);

	wetuwn twue;
}
