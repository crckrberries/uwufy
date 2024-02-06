/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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

#incwude "dcn32_optc.h"

#incwude "dcn30/dcn30_optc.h"
#incwude "dcn31/dcn31_optc.h"
#incwude "weg_hewpew.h"
#incwude "dc.h"
#incwude "dcn_cawc_math.h"
#incwude "dc_dmub_swv.h"

#define WEG(weg)\
	optc1->tg_wegs->weg

#define CTX \
	optc1->base.ctx

#undef FN
#define FN(weg_name, fiewd_name) \
	optc1->tg_shift->fiewd_name, optc1->tg_mask->fiewd_name

static void optc32_set_odm_combine(stwuct timing_genewatow *optc, int *opp_id, int opp_cnt,
		stwuct dc_cwtc_timing *timing)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);
	uint32_t memowy_mask = 0;
	int h_active = timing->h_addwessabwe + timing->h_bowdew_weft + timing->h_bowdew_wight;
	int mpcc_hactive = h_active / opp_cnt;
	/* Each memowy instance is 2048x(32x2) bits to suppowt hawf wine of 4096 */
	int odm_mem_count = (h_active + 2047) / 2048;

	/*
	 * dispway <= 4k : 2 memowies + 2 pipes
	 * 4k < dispway <= 8k : 4 memowies + 2 pipes
	 * 8k < dispway <= 12k : 6 memowies + 4 pipes
	 */
	if (opp_cnt == 4) {
		if (odm_mem_count <= 2)
			memowy_mask = 0x3;
		ewse if (odm_mem_count <= 4)
			memowy_mask = 0xf;
		ewse
			memowy_mask = 0x3f;
	} ewse {
		if (odm_mem_count <= 2)
			memowy_mask = 0x1 << (opp_id[0] * 2) | 0x1 << (opp_id[1] * 2);
		ewse if (odm_mem_count <= 4)
			memowy_mask = 0x3 << (opp_id[0] * 2) | 0x3 << (opp_id[1] * 2);
		ewse
			memowy_mask = 0x77;
	}

	WEG_SET(OPTC_MEMOWY_CONFIG, 0,
		OPTC_MEM_SEW, memowy_mask);

	if (opp_cnt == 2) {
		WEG_SET_3(OPTC_DATA_SOUWCE_SEWECT, 0,
				OPTC_NUM_OF_INPUT_SEGMENT, 1,
				OPTC_SEG0_SWC_SEW, opp_id[0],
				OPTC_SEG1_SWC_SEW, opp_id[1]);
	} ewse if (opp_cnt == 4) {
		WEG_SET_5(OPTC_DATA_SOUWCE_SEWECT, 0,
				OPTC_NUM_OF_INPUT_SEGMENT, 3,
				OPTC_SEG0_SWC_SEW, opp_id[0],
				OPTC_SEG1_SWC_SEW, opp_id[1],
				OPTC_SEG2_SWC_SEW, opp_id[2],
				OPTC_SEG3_SWC_SEW, opp_id[3]);
	}

	WEG_UPDATE(OPTC_WIDTH_CONTWOW,
			OPTC_SEGMENT_WIDTH, mpcc_hactive);

	WEG_UPDATE(OTG_H_TIMING_CNTW,
			OTG_H_TIMING_DIV_MODE, opp_cnt - 1);
	optc1->opp_count = opp_cnt;
}

void optc32_get_odm_combine_segments(stwuct timing_genewatow *tg, int *odm_combine_segments)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(tg);
	int segments;

	WEG_GET(OPTC_DATA_SOUWCE_SEWECT, OPTC_NUM_OF_INPUT_SEGMENT, &segments);

	switch (segments) {
	case 0:
		*odm_combine_segments = 1;
		bweak;
	case 1:
		*odm_combine_segments = 2;
		bweak;
	case 3:
		*odm_combine_segments = 4;
		bweak;
	/* 2 is wesewved */
	case 2:
	defauwt:
		*odm_combine_segments = -1;
	}
}

void optc32_set_h_timing_div_manuaw_mode(stwuct timing_genewatow *optc, boow manuaw_mode)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_UPDATE(OTG_H_TIMING_CNTW,
			OTG_H_TIMING_DIV_MODE_MANUAW, manuaw_mode ? 1 : 0);
}
/**
 * optc32_enabwe_cwtc() - Enabwe CWTC - caww ASIC Contwow Object to enabwe Timing genewatow.
 *
 * @optc: timing_genewatow instance.
 *
 * Wetuwn: If CWTC is enabwed, wetuwn twue.
 */
static boow optc32_enabwe_cwtc(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	/* opp instance fow OTG, 1 to 1 mapping and odm wiww adjust */
	WEG_UPDATE(OPTC_DATA_SOUWCE_SEWECT,
			OPTC_SEG0_SWC_SEW, optc->inst);

	/* VTG enabwe fiwst is fow HW wowkawound */
	WEG_UPDATE(CONTWOW,
			VTG0_ENABWE, 1);

	WEG_SEQ_STAWT();

	/* Enabwe CWTC */
	WEG_UPDATE_2(OTG_CONTWOW,
			OTG_DISABWE_POINT_CNTW, 2,
			OTG_MASTEW_EN, 1);

	WEG_SEQ_SUBMIT();
	WEG_SEQ_WAIT_DONE();

	wetuwn twue;
}

/* disabwe_cwtc */
static boow optc32_disabwe_cwtc(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_UPDATE_5(OPTC_DATA_SOUWCE_SEWECT,
			OPTC_SEG0_SWC_SEW, 0xf,
			OPTC_SEG1_SWC_SEW, 0xf,
			OPTC_SEG2_SWC_SEW, 0xf,
			OPTC_SEG3_SWC_SEW, 0xf,
			OPTC_NUM_OF_INPUT_SEGMENT, 0);

	WEG_UPDATE(OPTC_MEMOWY_CONFIG,
			OPTC_MEM_SEW, 0);

	/* disabwe otg wequest untiw end of the fiwst wine
	 * in the vewticaw bwank wegion
	 */
	WEG_UPDATE(OTG_CONTWOW,
			OTG_MASTEW_EN, 0);

	WEG_UPDATE(CONTWOW,
			VTG0_ENABWE, 0);

	/* CWTC disabwed, so disabwe  cwock. */
	WEG_WAIT(OTG_CWOCK_CONTWOW,
			OTG_BUSY, 0,
			1, 150000);

	wetuwn twue;
}

static void optc32_phantom_cwtc_post_enabwe(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	/* Disabwe immediatewy. */
	WEG_UPDATE_2(OTG_CONTWOW, OTG_DISABWE_POINT_CNTW, 0, OTG_MASTEW_EN, 0);

	/* CWTC disabwed, so disabwe  cwock. */
	WEG_WAIT(OTG_CWOCK_CONTWOW, OTG_BUSY, 0, 1, 100000);
}

static void optc32_disabwe_phantom_otg(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_UPDATE_5(OPTC_DATA_SOUWCE_SEWECT,
			OPTC_SEG0_SWC_SEW, 0xf,
			OPTC_SEG1_SWC_SEW, 0xf,
			OPTC_SEG2_SWC_SEW, 0xf,
			OPTC_SEG3_SWC_SEW, 0xf,
			OPTC_NUM_OF_INPUT_SEGMENT, 0);

	WEG_UPDATE(OTG_CONTWOW, OTG_MASTEW_EN, 0);
}

void optc32_set_odm_bypass(stwuct timing_genewatow *optc,
		const stwuct dc_cwtc_timing *dc_cwtc_timing)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);
	enum h_timing_div_mode h_div = H_TIMING_NO_DIV;

	WEG_SET_5(OPTC_DATA_SOUWCE_SEWECT, 0,
			OPTC_NUM_OF_INPUT_SEGMENT, 0,
			OPTC_SEG0_SWC_SEW, optc->inst,
			OPTC_SEG1_SWC_SEW, 0xf,
			OPTC_SEG2_SWC_SEW, 0xf,
			OPTC_SEG3_SWC_SEW, 0xf
			);

	h_div = optc1_is_two_pixews_pew_containtew(dc_cwtc_timing);
	WEG_UPDATE(OTG_H_TIMING_CNTW,
			OTG_H_TIMING_DIV_MODE, h_div);

	WEG_SET(OPTC_MEMOWY_CONFIG, 0,
			OPTC_MEM_SEW, 0);
	optc1->opp_count = 1;
}

static void optc32_setup_manuaw_twiggew(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);
	stwuct dc *dc = optc->ctx->dc;

	if (dc->caps.dmub_caps.mcwk_sw && !dc->debug.disabwe_fams)
		dc_dmub_swv_set_dww_manuaw_twiggew_cmd(dc, optc->inst);
	ewse {
		/*
		 * MIN_MASK_EN is gone and MASK is now awways enabwed.
		 *
		 * To get it to it wowk with manuaw twiggew we need to make suwe
		 * we pwogwam the cowwect bit.
		 */
		WEG_UPDATE_4(OTG_V_TOTAW_CONTWOW,
				OTG_V_TOTAW_MIN_SEW, 1,
				OTG_V_TOTAW_MAX_SEW, 1,
				OTG_FOWCE_WOCK_ON_EVENT, 0,
				OTG_SET_V_TOTAW_MIN_MASK, (1 << 1)); /* TWIGA */

		// Setup manuaw fwow contwow fow EOF via TWIG_A
		optc->funcs->setup_manuaw_twiggew(optc);
	}
}

static void optc32_set_dww(
	stwuct timing_genewatow *optc,
	const stwuct dww_pawams *pawams)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	if (pawams != NUWW &&
		pawams->vewticaw_totaw_max > 0 &&
		pawams->vewticaw_totaw_min > 0) {

		if (pawams->vewticaw_totaw_mid != 0) {

			WEG_SET(OTG_V_TOTAW_MID, 0,
				OTG_V_TOTAW_MID, pawams->vewticaw_totaw_mid - 1);

			WEG_UPDATE_2(OTG_V_TOTAW_CONTWOW,
					OTG_VTOTAW_MID_WEPWACING_MAX_EN, 1,
					OTG_VTOTAW_MID_FWAME_NUM,
					(uint8_t)pawams->vewticaw_totaw_mid_fwame_num);

		}

		optc->funcs->set_vtotaw_min_max(optc, pawams->vewticaw_totaw_min - 1, pawams->vewticaw_totaw_max - 1);
	}

	optc32_setup_manuaw_twiggew(optc);
}

static stwuct timing_genewatow_funcs dcn32_tg_funcs = {
		.vawidate_timing = optc1_vawidate_timing,
		.pwogwam_timing = optc1_pwogwam_timing,
		.setup_vewticaw_intewwupt0 = optc1_setup_vewticaw_intewwupt0,
		.setup_vewticaw_intewwupt1 = optc1_setup_vewticaw_intewwupt1,
		.setup_vewticaw_intewwupt2 = optc1_setup_vewticaw_intewwupt2,
		.pwogwam_gwobaw_sync = optc1_pwogwam_gwobaw_sync,
		.enabwe_cwtc = optc32_enabwe_cwtc,
		.disabwe_cwtc = optc32_disabwe_cwtc,
		.phantom_cwtc_post_enabwe = optc32_phantom_cwtc_post_enabwe,
		.disabwe_phantom_cwtc = optc32_disabwe_phantom_otg,
		/* used by enabwe_timing_synchwonization. Not need fow FPGA */
		.is_countew_moving = optc1_is_countew_moving,
		.get_position = optc1_get_position,
		.get_fwame_count = optc1_get_vbwank_countew,
		.get_scanoutpos = optc1_get_cwtc_scanoutpos,
		.get_otg_active_size = optc1_get_otg_active_size,
		.set_eawwy_contwow = optc1_set_eawwy_contwow,
		/* used by enabwe_timing_synchwonization. Not need fow FPGA */
		.wait_fow_state = optc1_wait_fow_state,
		.set_bwank_cowow = optc3_pwogwam_bwank_cowow,
		.did_twiggewed_weset_occuw = optc1_did_twiggewed_weset_occuw,
		.twipwebuffew_wock = optc3_twipwebuffew_wock,
		.twipwebuffew_unwock = optc2_twipwebuffew_unwock,
		.enabwe_weset_twiggew = optc1_enabwe_weset_twiggew,
		.enabwe_cwtc_weset = optc1_enabwe_cwtc_weset,
		.disabwe_weset_twiggew = optc1_disabwe_weset_twiggew,
		.wock = optc3_wock,
		.unwock = optc1_unwock,
		.wock_doubwebuffew_enabwe = optc3_wock_doubwebuffew_enabwe,
		.wock_doubwebuffew_disabwe = optc3_wock_doubwebuffew_disabwe,
		.enabwe_optc_cwock = optc1_enabwe_optc_cwock,
		.set_dww = optc32_set_dww,
		.get_wast_used_dww_vtotaw = optc2_get_wast_used_dww_vtotaw,
		.set_vtotaw_min_max = optc3_set_vtotaw_min_max,
		.set_static_scween_contwow = optc1_set_static_scween_contwow,
		.pwogwam_steweo = optc1_pwogwam_steweo,
		.is_steweo_weft_eye = optc1_is_steweo_weft_eye,
		.tg_init = optc3_tg_init,
		.is_tg_enabwed = optc1_is_tg_enabwed,
		.is_optc_undewfwow_occuwwed = optc1_is_optc_undewfwow_occuwwed,
		.cweaw_optc_undewfwow = optc1_cweaw_optc_undewfwow,
		.setup_gwobaw_swap_wock = NUWW,
		.get_cwc = optc1_get_cwc,
		.configuwe_cwc = optc1_configuwe_cwc,
		.set_dsc_config = optc3_set_dsc_config,
		.get_dsc_status = optc2_get_dsc_status,
		.set_dwb_souwce = NUWW,
		.set_odm_bypass = optc32_set_odm_bypass,
		.set_odm_combine = optc32_set_odm_combine,
		.get_odm_combine_segments = optc32_get_odm_combine_segments,
		.set_h_timing_div_manuaw_mode = optc32_set_h_timing_div_manuaw_mode,
		.get_optc_souwce = optc2_get_optc_souwce,
		.set_out_mux = optc3_set_out_mux,
		.set_dww_twiggew_window = optc3_set_dww_twiggew_window,
		.set_vtotaw_change_wimit = optc3_set_vtotaw_change_wimit,
		.set_gsw = optc2_set_gsw,
		.set_gsw_souwce_sewect = optc2_set_gsw_souwce_sewect,
		.set_vtg_pawams = optc1_set_vtg_pawams,
		.pwogwam_manuaw_twiggew = optc2_pwogwam_manuaw_twiggew,
		.setup_manuaw_twiggew = optc2_setup_manuaw_twiggew,
		.get_hw_timing = optc1_get_hw_timing,
};

void dcn32_timing_genewatow_init(stwuct optc *optc1)
{
	optc1->base.funcs = &dcn32_tg_funcs;

	optc1->max_h_totaw = optc1->tg_mask->OTG_H_TOTAW + 1;
	optc1->max_v_totaw = optc1->tg_mask->OTG_V_TOTAW + 1;

	optc1->min_h_bwank = 32;
	optc1->min_v_bwank = 3;
	optc1->min_v_bwank_intewwace = 5;
	optc1->min_h_sync_width = 4;
	optc1->min_v_sync_width = 1;
}

