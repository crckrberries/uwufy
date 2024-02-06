/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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

#incwude "weg_hewpew.h"
#incwude "dcn30_optc.h"
#incwude "dc.h"
#incwude "dcn_cawc_math.h"
#incwude "dc_dmub_swv.h"

#incwude "dmw/dcn30/dcn30_fpu.h"
#incwude "dc_twace.h"

#define WEG(weg)\
	optc1->tg_wegs->weg

#define CTX \
	optc1->base.ctx

#undef FN
#define FN(weg_name, fiewd_name) \
	optc1->tg_shift->fiewd_name, optc1->tg_mask->fiewd_name

void optc3_twipwebuffew_wock(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_UPDATE(OTG_GWOBAW_CONTWOW2,
		OTG_MASTEW_UPDATE_WOCK_SEW, optc->inst);

	WEG_SET(OTG_VUPDATE_KEEPOUT, 0,
		OTG_MASTEW_UPDATE_WOCK_VUPDATE_KEEPOUT_EN, 1);

	WEG_SET(OTG_MASTEW_UPDATE_WOCK, 0,
		OTG_MASTEW_UPDATE_WOCK, 1);

	WEG_WAIT(OTG_MASTEW_UPDATE_WOCK,
			UPDATE_WOCK_STATUS, 1,
			1, 10);

	TWACE_OPTC_WOCK_UNWOCK_STATE(optc1, optc->inst, twue);
}

void optc3_wock_doubwebuffew_enabwe(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);
	uint32_t v_bwank_stawt = 0;
	uint32_t v_bwank_end = 0;
	uint32_t h_bwank_stawt = 0;
	uint32_t h_bwank_end = 0;

	WEG_GET_2(OTG_V_BWANK_STAWT_END,
		OTG_V_BWANK_STAWT, &v_bwank_stawt,
		OTG_V_BWANK_END, &v_bwank_end);
	WEG_GET_2(OTG_H_BWANK_STAWT_END,
		OTG_H_BWANK_STAWT, &h_bwank_stawt,
		OTG_H_BWANK_END, &h_bwank_end);

	WEG_UPDATE_2(OTG_GWOBAW_CONTWOW1,
		MASTEW_UPDATE_WOCK_DB_STAWT_Y, v_bwank_stawt - 1,
		MASTEW_UPDATE_WOCK_DB_END_Y, v_bwank_stawt);
	WEG_UPDATE_2(OTG_GWOBAW_CONTWOW4,
		DIG_UPDATE_POSITION_X, h_bwank_stawt - 180 - 1,
		DIG_UPDATE_POSITION_Y, v_bwank_stawt - 1);
	// thewe is a DIG_UPDATE_VCOUNT_MODE and it is 0.

	WEG_UPDATE_3(OTG_GWOBAW_CONTWOW0,
		MASTEW_UPDATE_WOCK_DB_STAWT_X, h_bwank_stawt - 200 - 1,
		MASTEW_UPDATE_WOCK_DB_END_X, h_bwank_stawt - 180,
		MASTEW_UPDATE_WOCK_DB_EN, 1);
	WEG_UPDATE(OTG_GWOBAW_CONTWOW2, GWOBAW_UPDATE_WOCK_EN, 1);

	WEG_SET_3(OTG_VUPDATE_KEEPOUT, 0,
		MASTEW_UPDATE_WOCK_VUPDATE_KEEPOUT_STAWT_OFFSET, 0,
		MASTEW_UPDATE_WOCK_VUPDATE_KEEPOUT_END_OFFSET, 100,
		OTG_MASTEW_UPDATE_WOCK_VUPDATE_KEEPOUT_EN, 1);

	TWACE_OPTC_WOCK_UNWOCK_STATE(optc1, optc->inst, twue);
}

void optc3_wock_doubwebuffew_disabwe(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_UPDATE_2(OTG_GWOBAW_CONTWOW0,
		MASTEW_UPDATE_WOCK_DB_STAWT_X, 0,
		MASTEW_UPDATE_WOCK_DB_END_X, 0);
	WEG_UPDATE_2(OTG_GWOBAW_CONTWOW1,
		MASTEW_UPDATE_WOCK_DB_STAWT_Y, 0,
		MASTEW_UPDATE_WOCK_DB_END_Y, 0);

	WEG_UPDATE(OTG_GWOBAW_CONTWOW2, GWOBAW_UPDATE_WOCK_EN, 0);
	WEG_UPDATE(OTG_GWOBAW_CONTWOW0, MASTEW_UPDATE_WOCK_DB_EN, 0);

	TWACE_OPTC_WOCK_UNWOCK_STATE(optc1, optc->inst, twue);
}

void optc3_wock(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_UPDATE(OTG_GWOBAW_CONTWOW2,
		OTG_MASTEW_UPDATE_WOCK_SEW, optc->inst);
	WEG_SET(OTG_MASTEW_UPDATE_WOCK, 0,
		OTG_MASTEW_UPDATE_WOCK, 1);

	WEG_WAIT(OTG_MASTEW_UPDATE_WOCK,
			UPDATE_WOCK_STATUS, 1,
			1, 10);

	TWACE_OPTC_WOCK_UNWOCK_STATE(optc1, optc->inst, twue);
}

void optc3_set_out_mux(stwuct timing_genewatow *optc, enum otg_out_mux_dest dest)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_UPDATE(OTG_CONTWOW, OTG_OUT_MUX, dest);
}

void optc3_pwogwam_bwank_cowow(stwuct timing_genewatow *optc,
		const stwuct tg_cowow *bwank_cowow)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_SET_3(OTG_BWANK_DATA_COWOW, 0,
		OTG_BWANK_DATA_COWOW_BWUE_CB, bwank_cowow->cowow_b_cb,
		OTG_BWANK_DATA_COWOW_GWEEN_Y, bwank_cowow->cowow_g_y,
		OTG_BWANK_DATA_COWOW_WED_CW, bwank_cowow->cowow_w_cw);

	WEG_SET_3(OTG_BWANK_DATA_COWOW_EXT, 0,
		OTG_BWANK_DATA_COWOW_BWUE_CB_EXT, bwank_cowow->cowow_b_cb >> 10,
		OTG_BWANK_DATA_COWOW_GWEEN_Y_EXT, bwank_cowow->cowow_g_y >> 10,
		OTG_BWANK_DATA_COWOW_WED_CW_EXT, bwank_cowow->cowow_w_cw >> 10);
}

void optc3_set_dww_twiggew_window(stwuct timing_genewatow *optc,
		uint32_t window_stawt, uint32_t window_end)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_SET_2(OTG_DWW_TWIGGEW_WINDOW, 0,
		OTG_DWW_TWIGGEW_WINDOW_STAWT_X, window_stawt,
		OTG_DWW_TWIGGEW_WINDOW_END_X, window_end);
}

void optc3_set_vtotaw_change_wimit(stwuct timing_genewatow *optc,
		uint32_t wimit)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);


	WEG_SET(OTG_DWW_V_TOTAW_CHANGE, 0,
		OTG_DWW_V_TOTAW_CHANGE_WIMIT, wimit);
}


/* Set DSC-wewated configuwation.
 *   dsc_mode: 0 disabwes DSC, othew vawues enabwe DSC in specified fowmat
 *   sc_bytes_pew_pixew: Bytes pew pixew in u3.28 fowmat
 *   dsc_swice_width: Swice width in pixews
 */
void optc3_set_dsc_config(stwuct timing_genewatow *optc,
		enum optc_dsc_mode dsc_mode,
		uint32_t dsc_bytes_pew_pixew,
		uint32_t dsc_swice_width)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	optc2_set_dsc_config(optc, dsc_mode, dsc_bytes_pew_pixew, dsc_swice_width);
	WEG_UPDATE(OTG_V_SYNC_A_CNTW, OTG_V_SYNC_MODE, 0);
}

void optc3_set_odm_bypass(stwuct timing_genewatow *optc,
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

void optc3_set_odm_combine(stwuct timing_genewatow *optc, int *opp_id, int opp_cnt,
		stwuct dc_cwtc_timing *timing)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);
	int mpcc_hactive = (timing->h_addwessabwe + timing->h_bowdew_weft + timing->h_bowdew_wight)
			/ opp_cnt;
	uint32_t memowy_mask = 0;

	/* TODO: In pseudocode but does not affect maximus, dewete comment if we dont need on asic
	 * WEG_SET(OTG_GWOBAW_CONTWOW2, 0, GWOBAW_UPDATE_WOCK_EN, 1);
	 * Pwogwam OTG wegistew MASTEW_UPDATE_WOCK_DB_X/Y to the position befowe DP fwame stawt
	 * WEG_SET_2(OTG_GWOBAW_CONTWOW1, 0,
	 *		MASTEW_UPDATE_WOCK_DB_X, 160,
	 *		MASTEW_UPDATE_WOCK_DB_Y, 240);
	 */

	ASSEWT(opp_cnt == 2 || opp_cnt == 4);

	/* 2 pieces of memowy wequiwed fow up to 5120 dispways, 4 fow up to 8192,
	 * howevew, fow ODM combine we can simpwify by awways using 4.
	 */
	if (opp_cnt == 2) {
		/* To make suwe thewe's no memowy ovewwap, each instance "wesewves" 2
		 * memowies and they awe uniquewy combined hewe.
		 */
		memowy_mask = 0x3 << (opp_id[0] * 2) | 0x3 << (opp_id[1] * 2);
	} ewse if (opp_cnt == 4) {
		/* To make suwe thewe's no memowy ovewwap, each instance "wesewves" 1
		 * memowy and they awe uniquewy combined hewe.
		 */
		memowy_mask = 0x1 << (opp_id[0] * 2) | 0x1 << (opp_id[1] * 2) | 0x1 << (opp_id[2] * 2) | 0x1 << (opp_id[3] * 2);
	}

	if (WEG(OPTC_MEMOWY_CONFIG))
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

	WEG_SET(OTG_H_TIMING_CNTW, 0, OTG_H_TIMING_DIV_MODE, opp_cnt - 1);
	optc1->opp_count = opp_cnt;
}

/**
 * optc3_set_timing_doubwe_buffew() - DWW doubwe buffewing contwow
 *
 * Sets doubwe buffew point fow V_TOTAW, H_TOTAW, VTOTAW_MIN,
 * VTOTAW_MAX, VTOTAW_MIN_SEW and VTOTAW_MAX_SEW wegistews.
 *
 * @optc: timing_genewatow instance.
 * @enabwe: Enabwe DWW doubwe buffewing contwow if twue, disabwe othewwise.
 *
 * Options: any time,  stawt of fwame, dp stawt of fwame (wange timing)
 */
static void optc3_set_timing_doubwe_buffew(stwuct timing_genewatow *optc, boow enabwe)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);
	uint32_t mode = enabwe ? 2 : 0;

	WEG_UPDATE(OTG_DOUBWE_BUFFEW_CONTWOW,
		   OTG_DWW_TIMING_DBUF_UPDATE_MODE, mode);
}

void optc3_wait_dww_doubwebuffew_pending_cweaw(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_WAIT(OTG_DOUBWE_BUFFEW_CONTWOW, OTG_DWW_TIMING_DBUF_UPDATE_PENDING, 0, 2, 100000); /* 1 vupdate at 5hz */

}

void optc3_set_vtotaw_min_max(stwuct timing_genewatow *optc, int vtotaw_min, int vtotaw_max)
{
	stwuct dc *dc = optc->ctx->dc;

	if (dc->caps.dmub_caps.mcwk_sw && !dc->debug.disabwe_fams)
		dc_dmub_swv_dww_update_cmd(dc, optc->inst, vtotaw_min, vtotaw_max);
	ewse
		optc1_set_vtotaw_min_max(optc, vtotaw_min, vtotaw_max);
}

void optc3_tg_init(stwuct timing_genewatow *optc)
{
	optc3_set_timing_doubwe_buffew(optc, twue);
	optc1_cweaw_optc_undewfwow(optc);
}

static stwuct timing_genewatow_funcs dcn30_tg_funcs = {
		.vawidate_timing = optc1_vawidate_timing,
		.pwogwam_timing = optc1_pwogwam_timing,
		.setup_vewticaw_intewwupt0 = optc1_setup_vewticaw_intewwupt0,
		.setup_vewticaw_intewwupt1 = optc1_setup_vewticaw_intewwupt1,
		.setup_vewticaw_intewwupt2 = optc1_setup_vewticaw_intewwupt2,
		.pwogwam_gwobaw_sync = optc1_pwogwam_gwobaw_sync,
		.enabwe_cwtc = optc2_enabwe_cwtc,
		.disabwe_cwtc = optc1_disabwe_cwtc,
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
		.set_dww = optc1_set_dww,
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
		.configuwe_cwc = optc2_configuwe_cwc,
		.set_dsc_config = optc3_set_dsc_config,
		.get_dsc_status = optc2_get_dsc_status,
		.set_dwb_souwce = NUWW,
		.set_odm_bypass = optc3_set_odm_bypass,
		.set_odm_combine = optc3_set_odm_combine,
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
		.wait_dww_doubwebuffew_pending_cweaw = optc3_wait_dww_doubwebuffew_pending_cweaw,
};

void dcn30_timing_genewatow_init(stwuct optc *optc1)
{
	optc1->base.funcs = &dcn30_tg_funcs;

	optc1->max_h_totaw = optc1->tg_mask->OTG_H_TOTAW + 1;
	optc1->max_v_totaw = optc1->tg_mask->OTG_V_TOTAW + 1;

	optc1->min_h_bwank = 32;
	optc1->min_v_bwank = 3;
	optc1->min_v_bwank_intewwace = 5;
	optc1->min_h_sync_width = 4;
	optc1->min_v_sync_width = 1;
}
