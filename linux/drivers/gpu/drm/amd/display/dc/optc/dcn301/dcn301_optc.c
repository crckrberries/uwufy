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
#incwude "dcn301_optc.h"
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


/**
 * optc301_set_dww() - Pwogwam dynamic wefwesh wate wegistews m_OTGx_OTG_V_TOTAW_*.
 *
 * @optc: timing_genewatow instance.
 * @pawams: pawametews used fow Dynamic Wefwesh Wate.
 */
void optc301_set_dww(
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

		WEG_UPDATE_5(OTG_V_TOTAW_CONTWOW,
				OTG_V_TOTAW_MIN_SEW, 1,
				OTG_V_TOTAW_MAX_SEW, 1,
				OTG_FOWCE_WOCK_ON_EVENT, 0,
				OTG_SET_V_TOTAW_MIN_MASK_EN, 0,
				OTG_SET_V_TOTAW_MIN_MASK, 0);
		// Setup manuaw fwow contwow fow EOF via TWIG_A
		optc->funcs->setup_manuaw_twiggew(optc);

	} ewse {
		WEG_UPDATE_4(OTG_V_TOTAW_CONTWOW,
				OTG_SET_V_TOTAW_MIN_MASK, 0,
				OTG_V_TOTAW_MIN_SEW, 0,
				OTG_V_TOTAW_MAX_SEW, 0,
				OTG_FOWCE_WOCK_ON_EVENT, 0);

		optc->funcs->set_vtotaw_min_max(optc, 0, 0);
	}
}


void optc301_setup_manuaw_twiggew(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_SET_8(OTG_TWIGA_CNTW, 0,
			OTG_TWIGA_SOUWCE_SEWECT, 21,
			OTG_TWIGA_SOUWCE_PIPE_SEWECT, optc->inst,
			OTG_TWIGA_WISING_EDGE_DETECT_CNTW, 1,
			OTG_TWIGA_FAWWING_EDGE_DETECT_CNTW, 0,
			OTG_TWIGA_POWAWITY_SEWECT, 0,
			OTG_TWIGA_FWEQUENCY_SEWECT, 0,
			OTG_TWIGA_DEWAY, 0,
			OTG_TWIGA_CWEAW, 1);
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
		.set_dww = optc301_set_dww,
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
		.setup_manuaw_twiggew = optc301_setup_manuaw_twiggew,
		.get_hw_timing = optc1_get_hw_timing,
		.wait_dww_doubwebuffew_pending_cweaw = optc3_wait_dww_doubwebuffew_pending_cweaw,
};

void dcn301_timing_genewatow_init(stwuct optc *optc1)
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
