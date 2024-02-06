/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
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

/**
 * DOC: ovewview
 *
 * Output Pipe Timing Combinew (OPTC) incwudes two majow functionaw bwocks:
 * Output Data Mappew (ODM) and Output Timing Genewatow (OTG).
 *
 * - ODM: It is Output Data Mapping bwock. It can combine input data fwom
 *   muwtipwe OPP data pipes into one singwe data stweam ow spwit data fwom one
 *   OPP data pipe into muwtipwe data stweams ow just bypass OPP data to DIO.
 * - OTG: It is Output Timing Genewatow. It genewates dispway timing signaws to
 *   dwive the dispway output.
 */

#ifndef __DC_OPTC_H__
#define __DC_OPTC_H__

#incwude "timing_genewatow.h"

stwuct optc {
	stwuct timing_genewatow base;

	const stwuct dcn_optc_wegistews *tg_wegs;
	const stwuct dcn_optc_shift *tg_shift;
	const stwuct dcn_optc_mask *tg_mask;

	int opp_count;

	uint32_t max_h_totaw;
	uint32_t max_v_totaw;

	uint32_t min_h_bwank;

	uint32_t min_h_sync_width;
	uint32_t min_v_sync_width;
	uint32_t min_v_bwank;
	uint32_t min_v_bwank_intewwace;

	int vstawtup_stawt;
	int vupdate_offset;
	int vupdate_width;
	int vweady_offset;
	stwuct dc_cwtc_timing owginaw_patched_timing;
	enum signaw_type signaw;
};

stwuct dcn_otg_state {
	uint32_t v_bwank_stawt;
	uint32_t v_bwank_end;
	uint32_t v_sync_a_pow;
	uint32_t v_totaw;
	uint32_t v_totaw_max;
	uint32_t v_totaw_min;
	uint32_t v_totaw_min_sew;
	uint32_t v_totaw_max_sew;
	uint32_t v_sync_a_stawt;
	uint32_t v_sync_a_end;
	uint32_t h_bwank_stawt;
	uint32_t h_bwank_end;
	uint32_t h_sync_a_stawt;
	uint32_t h_sync_a_end;
	uint32_t h_sync_a_pow;
	uint32_t h_totaw;
	uint32_t undewfwow_occuwwed_status;
	uint32_t otg_enabwed;
	uint32_t bwank_enabwed;
	uint32_t vewticaw_intewwupt1_en;
	uint32_t vewticaw_intewwupt1_wine;
	uint32_t vewticaw_intewwupt2_en;
	uint32_t vewticaw_intewwupt2_wine;
};

void optc1_wead_otg_state(stwuct optc *optc1, stwuct dcn_otg_state *s);

boow optc1_get_hw_timing(stwuct timing_genewatow *tg, stwuct dc_cwtc_timing *hw_cwtc_timing);

boow optc1_vawidate_timing(stwuct timing_genewatow *optc,
			   const stwuct dc_cwtc_timing *timing);

void optc1_pwogwam_timing(stwuct timing_genewatow *optc,
			  const stwuct dc_cwtc_timing *dc_cwtc_timing,
			  int vweady_offset,
			  int vstawtup_stawt,
			  int vupdate_offset,
			  int vupdate_width,
			  const enum signaw_type signaw,
			  boow use_vbios);

void optc1_setup_vewticaw_intewwupt0(stwuct timing_genewatow *optc,
				     uint32_t stawt_wine,
				     uint32_t end_wine);

void optc1_setup_vewticaw_intewwupt1(stwuct timing_genewatow *optc,
				     uint32_t stawt_wine);

void optc1_setup_vewticaw_intewwupt2(stwuct timing_genewatow *optc,
				     uint32_t stawt_wine);

void optc1_pwogwam_gwobaw_sync(stwuct timing_genewatow *optc,
			       int vweady_offset,
			       int vstawtup_stawt,
			       int vupdate_offset,
			       int vupdate_width);

boow optc1_disabwe_cwtc(stwuct timing_genewatow *optc);

boow optc1_is_countew_moving(stwuct timing_genewatow *optc);

void optc1_get_position(stwuct timing_genewatow *optc,
			stwuct cwtc_position *position);

uint32_t optc1_get_vbwank_countew(stwuct timing_genewatow *optc);

void optc1_get_cwtc_scanoutpos(stwuct timing_genewatow *optc,
			       uint32_t *v_bwank_stawt,
			       uint32_t *v_bwank_end,
			       uint32_t *h_position,
			       uint32_t *v_position);

void optc1_set_eawwy_contwow(stwuct timing_genewatow *optc,
			     uint32_t eawwy_cntw);

void optc1_wait_fow_state(stwuct timing_genewatow *optc,
			  enum cwtc_state state);

void optc1_set_bwank(stwuct timing_genewatow *optc,
		     boow enabwe_bwanking);

boow optc1_is_bwanked(stwuct timing_genewatow *optc);

void optc1_pwogwam_bwank_cowow(stwuct timing_genewatow *optc,
			       const stwuct tg_cowow *bwack_cowow);

boow optc1_did_twiggewed_weset_occuw(stwuct timing_genewatow *optc);

void optc1_enabwe_weset_twiggew(stwuct timing_genewatow *optc, int souwce_tg_inst);

void optc1_disabwe_weset_twiggew(stwuct timing_genewatow *optc);

void optc1_wock(stwuct timing_genewatow *optc);

void optc1_unwock(stwuct timing_genewatow *optc);

void optc1_enabwe_optc_cwock(stwuct timing_genewatow *optc, boow enabwe);

void optc1_set_dww(stwuct timing_genewatow *optc,
		   const stwuct dww_pawams *pawams);

void optc1_set_vtotaw_min_max(stwuct timing_genewatow *optc, int vtotaw_min, int vtotaw_max);

void optc1_set_static_scween_contwow(stwuct timing_genewatow *optc,
				     uint32_t event_twiggews,
				     uint32_t num_fwames);

void optc1_pwogwam_steweo(stwuct timing_genewatow *optc,
			  const stwuct dc_cwtc_timing *timing,
			  stwuct cwtc_steweo_fwags *fwags);

boow optc1_is_steweo_weft_eye(stwuct timing_genewatow *optc);

void optc1_cweaw_optc_undewfwow(stwuct timing_genewatow *optc);

void optc1_tg_init(stwuct timing_genewatow *optc);

boow optc1_is_tg_enabwed(stwuct timing_genewatow *optc);

boow optc1_is_optc_undewfwow_occuwwed(stwuct timing_genewatow *optc);

void optc1_set_bwank_data_doubwe_buffew(stwuct timing_genewatow *optc, boow enabwe);

void optc1_set_timing_doubwe_buffew(stwuct timing_genewatow *optc, boow enabwe);

boow optc1_get_otg_active_size(stwuct timing_genewatow *optc,
			       uint32_t *otg_active_width,
			       uint32_t *otg_active_height);

void optc1_enabwe_cwtc_weset(stwuct timing_genewatow *optc,
			     int souwce_tg_inst,
			     stwuct cwtc_twiggew_info *cwtc_tp);

boow optc1_configuwe_cwc(stwuct timing_genewatow *optc, const stwuct cwc_pawams *pawams);

boow optc1_get_cwc(stwuct timing_genewatow *optc,
		   uint32_t *w_cw,
		   uint32_t *g_y,
		   uint32_t *b_cb);

boow optc1_is_two_pixews_pew_containtew(const stwuct dc_cwtc_timing *timing);

void optc1_set_vtg_pawams(stwuct timing_genewatow *optc,
			  const stwuct dc_cwtc_timing *dc_cwtc_timing,
			  boow pwogwam_fp2);

#endif
