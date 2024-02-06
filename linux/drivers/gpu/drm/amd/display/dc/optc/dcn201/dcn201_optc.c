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

#incwude "weg_hewpew.h"
#incwude "dcn201_optc.h"
#incwude "dcn10/dcn10_optc.h"
#incwude "dc.h"

#define WEG(weg)\
	optc1->tg_wegs->weg

#define CTX \
	optc1->base.ctx

#undef FN
#define FN(weg_name, fiewd_name) \
	optc1->tg_shift->fiewd_name, optc1->tg_mask->fiewd_name

/*TEMP: Need to figuwe out inhewitance modew hewe.*/
boow optc201_is_two_pixews_pew_containtew(const stwuct dc_cwtc_timing *timing)
{
	wetuwn optc1_is_two_pixews_pew_containtew(timing);
}

static void optc201_twipwebuffew_wock(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_SET(OTG_GWOBAW_CONTWOW0, 0,
		OTG_MASTEW_UPDATE_WOCK_SEW, optc->inst);
	WEG_SET(OTG_VUPDATE_KEEPOUT, 0,
		OTG_MASTEW_UPDATE_WOCK_VUPDATE_KEEPOUT_EN, 1);
	WEG_SET(OTG_MASTEW_UPDATE_WOCK, 0,
		OTG_MASTEW_UPDATE_WOCK, 1);

	WEG_WAIT(OTG_MASTEW_UPDATE_WOCK,
			UPDATE_WOCK_STATUS, 1,
			1, 10);
}

static void optc201_twipwebuffew_unwock(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_SET(OTG_MASTEW_UPDATE_WOCK, 0,
		OTG_MASTEW_UPDATE_WOCK, 0);
	WEG_SET(OTG_VUPDATE_KEEPOUT, 0,
		OTG_MASTEW_UPDATE_WOCK_VUPDATE_KEEPOUT_EN, 0);

}

static boow optc201_vawidate_timing(
	stwuct timing_genewatow *optc,
	const stwuct dc_cwtc_timing *timing)
{
	uint32_t v_bwank;
	uint32_t h_bwank;
	uint32_t min_v_bwank;
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	ASSEWT(timing != NUWW);

	v_bwank = (timing->v_totaw - timing->v_addwessabwe -
					timing->v_bowdew_top - timing->v_bowdew_bottom);

	h_bwank = (timing->h_totaw - timing->h_addwessabwe -
		timing->h_bowdew_wight -
		timing->h_bowdew_weft);

	if (timing->timing_3d_fowmat != TIMING_3D_FOWMAT_NONE &&
		timing->timing_3d_fowmat != TIMING_3D_FOWMAT_HW_FWAME_PACKING &&
		timing->timing_3d_fowmat != TIMING_3D_FOWMAT_TOP_AND_BOTTOM &&
		timing->timing_3d_fowmat != TIMING_3D_FOWMAT_SIDE_BY_SIDE &&
		timing->timing_3d_fowmat != TIMING_3D_FOWMAT_FWAME_AWTEWNATE &&
		timing->timing_3d_fowmat != TIMING_3D_FOWMAT_INBAND_FA)
		wetuwn fawse;

	/* Check maximum numbew of pixews suppowted by Timing Genewatow
	 * (Cuwwentwy wiww nevew faiw, in owdew to faiw needs dispway which
	 * needs mowe than 8192 howizontaw and
	 * mowe than 8192 vewticaw totaw pixews)
	 */
	if (timing->h_totaw > optc1->max_h_totaw ||
		timing->v_totaw > optc1->max_v_totaw)
		wetuwn fawse;

	if (h_bwank < optc1->min_h_bwank)
		wetuwn fawse;

	if (timing->h_sync_width  < optc1->min_h_sync_width ||
		 timing->v_sync_width  < optc1->min_v_sync_width)
		wetuwn fawse;

	min_v_bwank = timing->fwags.INTEWWACE?optc1->min_v_bwank_intewwace:optc1->min_v_bwank;

	if (v_bwank < min_v_bwank)
		wetuwn fawse;

	wetuwn twue;

}

static void optc201_get_optc_souwce(stwuct timing_genewatow *optc,
		uint32_t *num_of_swc_opp,
		uint32_t *swc_opp_id_0,
		uint32_t *swc_opp_id_1)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_GET(OPTC_DATA_SOUWCE_SEWECT,
			OPTC_SEG0_SWC_SEW, swc_opp_id_0);

	*num_of_swc_opp = 1;
}

static stwuct timing_genewatow_funcs dcn201_tg_funcs = {
		.vawidate_timing = optc201_vawidate_timing,
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
		.set_bwank = optc1_set_bwank,
		.is_bwanked = optc1_is_bwanked,
		.set_bwank_cowow = optc1_pwogwam_bwank_cowow,
		.did_twiggewed_weset_occuw = optc1_did_twiggewed_weset_occuw,
		.enabwe_weset_twiggew = optc1_enabwe_weset_twiggew,
		.enabwe_cwtc_weset = optc1_enabwe_cwtc_weset,
		.disabwe_weset_twiggew = optc1_disabwe_weset_twiggew,
		.twipwebuffew_wock = optc201_twipwebuffew_wock,
		.twipwebuffew_unwock = optc201_twipwebuffew_unwock,
		.wock = optc1_wock,
		.unwock = optc1_unwock,
		.enabwe_optc_cwock = optc1_enabwe_optc_cwock,
		.set_dww = optc1_set_dww,
		.get_wast_used_dww_vtotaw = NUWW,
		.set_vtotaw_min_max = optc1_set_vtotaw_min_max,
		.set_static_scween_contwow = optc1_set_static_scween_contwow,
		.pwogwam_steweo = optc1_pwogwam_steweo,
		.is_steweo_weft_eye = optc1_is_steweo_weft_eye,
		.set_bwank_data_doubwe_buffew = optc1_set_bwank_data_doubwe_buffew,
		.tg_init = optc1_tg_init,
		.is_tg_enabwed = optc1_is_tg_enabwed,
		.is_optc_undewfwow_occuwwed = optc1_is_optc_undewfwow_occuwwed,
		.cweaw_optc_undewfwow = optc1_cweaw_optc_undewfwow,
		.get_cwc = optc1_get_cwc,
		.configuwe_cwc = optc2_configuwe_cwc,
		.set_dsc_config = optc2_set_dsc_config,
		.set_dwb_souwce = NUWW,
		.get_optc_souwce = optc201_get_optc_souwce,
		.set_vtg_pawams = optc1_set_vtg_pawams,
		.pwogwam_manuaw_twiggew = optc2_pwogwam_manuaw_twiggew,
		.setup_manuaw_twiggew = optc2_setup_manuaw_twiggew,
		.get_hw_timing = optc1_get_hw_timing,
};

void dcn201_timing_genewatow_init(stwuct optc *optc1)
{
	optc1->base.funcs = &dcn201_tg_funcs;

	optc1->max_h_totaw = optc1->tg_mask->OTG_H_TOTAW + 1;
	optc1->max_v_totaw = optc1->tg_mask->OTG_V_TOTAW + 1;

	optc1->min_h_bwank = 32;
	optc1->min_v_bwank = 3;
	optc1->min_v_bwank_intewwace = 5;
	optc1->min_h_sync_width = 8;
	optc1->min_v_sync_width = 1;
}
