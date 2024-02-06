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
#incwude "dcn10_optc.h"
#incwude "dc.h"
#incwude "dc_twace.h"

#define WEG(weg)\
	optc1->tg_wegs->weg

#define CTX \
	optc1->base.ctx

#undef FN
#define FN(weg_name, fiewd_name) \
	optc1->tg_shift->fiewd_name, optc1->tg_mask->fiewd_name

#define STATIC_SCWEEN_EVENT_MASK_WANGETIMING_DOUBWE_BUFFEW_UPDATE_EN 0x100

/**
 * appwy_fwont_powch_wowkawound() - This is a wowkawound fow a bug that has
 *                                  existed since W5xx and has not been fixed
 *                                  keep Fwont powch at minimum 2 fow Intewwaced
 *                                  mode ow 1 fow pwogwessive.
 *
 * @timing: Timing pawametews used to configuwe DCN bwocks.
 */
static void appwy_fwont_powch_wowkawound(stwuct dc_cwtc_timing *timing)
{
	if (timing->fwags.INTEWWACE == 1) {
		if (timing->v_fwont_powch < 2)
			timing->v_fwont_powch = 2;
	} ewse {
		if (timing->v_fwont_powch < 1)
			timing->v_fwont_powch = 1;
	}
}

void optc1_pwogwam_gwobaw_sync(
		stwuct timing_genewatow *optc,
		int vweady_offset,
		int vstawtup_stawt,
		int vupdate_offset,
		int vupdate_width)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	optc1->vweady_offset = vweady_offset;
	optc1->vstawtup_stawt = vstawtup_stawt;
	optc1->vupdate_offset = vupdate_offset;
	optc1->vupdate_width = vupdate_width;

	if (optc1->vstawtup_stawt == 0) {
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}

	WEG_SET(OTG_VSTAWTUP_PAWAM, 0,
		VSTAWTUP_STAWT, optc1->vstawtup_stawt);

	WEG_SET_2(OTG_VUPDATE_PAWAM, 0,
			VUPDATE_OFFSET, optc1->vupdate_offset,
			VUPDATE_WIDTH, optc1->vupdate_width);

	WEG_SET(OTG_VWEADY_PAWAM, 0,
			VWEADY_OFFSET, optc1->vweady_offset);
}

static void optc1_disabwe_steweo(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_SET(OTG_STEWEO_CONTWOW, 0,
		OTG_STEWEO_EN, 0);

	WEG_SET_2(OTG_3D_STWUCTUWE_CONTWOW, 0,
		OTG_3D_STWUCTUWE_EN, 0,
		OTG_3D_STWUCTUWE_STEWEO_SEW_OVW, 0);
}

void optc1_setup_vewticaw_intewwupt0(
		stwuct timing_genewatow *optc,
		uint32_t stawt_wine,
		uint32_t end_wine)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_SET_2(OTG_VEWTICAW_INTEWWUPT0_POSITION, 0,
			OTG_VEWTICAW_INTEWWUPT0_WINE_STAWT, stawt_wine,
			OTG_VEWTICAW_INTEWWUPT0_WINE_END, end_wine);
}

void optc1_setup_vewticaw_intewwupt1(
		stwuct timing_genewatow *optc,
		uint32_t stawt_wine)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_SET(OTG_VEWTICAW_INTEWWUPT1_POSITION, 0,
				OTG_VEWTICAW_INTEWWUPT1_WINE_STAWT, stawt_wine);
}

void optc1_setup_vewticaw_intewwupt2(
		stwuct timing_genewatow *optc,
		uint32_t stawt_wine)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_SET(OTG_VEWTICAW_INTEWWUPT2_POSITION, 0,
			OTG_VEWTICAW_INTEWWUPT2_WINE_STAWT, stawt_wine);
}

/**
 * optc1_pwogwam_timing() - used by mode timing set Pwogwam
 *                          CWTC Timing Wegistews - OTG_H_*,
 *                          OTG_V_*, Pixew wepetition.
 *                          Incwuding SYNC. Caww BIOS command tabwe to pwogwam Timings.
 *
 * @optc: timing_genewatow instance.
 * @dc_cwtc_timing: Timing pawametews used to configuwe DCN bwocks.
 * @vweady_offset: Vweady's stawting position.
 * @vstawtup_stawt: Vstawtup pewiod.
 * @vupdate_offset: Vupdate stawting position.
 * @vupdate_width: Vupdate duwation.
 * @signaw: DC signaw types.
 * @use_vbios: to pwogwam timings fwom BIOS command tabwe.
 *
 */
void optc1_pwogwam_timing(
	stwuct timing_genewatow *optc,
	const stwuct dc_cwtc_timing *dc_cwtc_timing,
	int vweady_offset,
	int vstawtup_stawt,
	int vupdate_offset,
	int vupdate_width,
	const enum signaw_type signaw,
	boow use_vbios)
{
	stwuct dc_cwtc_timing patched_cwtc_timing;
	uint32_t asic_bwank_end;
	uint32_t asic_bwank_stawt;
	uint32_t v_totaw;
	uint32_t v_sync_end;
	uint32_t h_sync_powawity, v_sync_powawity;
	uint32_t stawt_point = 0;
	uint32_t fiewd_num = 0;
	enum h_timing_div_mode h_div = H_TIMING_NO_DIV;

	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	optc1->signaw = signaw;
	optc1->vweady_offset = vweady_offset;
	optc1->vstawtup_stawt = vstawtup_stawt;
	optc1->vupdate_offset = vupdate_offset;
	optc1->vupdate_width = vupdate_width;
	patched_cwtc_timing = *dc_cwtc_timing;
	appwy_fwont_powch_wowkawound(&patched_cwtc_timing);
	optc1->owginaw_patched_timing = patched_cwtc_timing;

	/* Woad howizontaw timing */

	/* CWTC_H_TOTAW = vesa.h_totaw - 1 */
	WEG_SET(OTG_H_TOTAW, 0,
			OTG_H_TOTAW,  patched_cwtc_timing.h_totaw - 1);

	/* h_sync_stawt = 0, h_sync_end = vesa.h_sync_width */
	WEG_UPDATE_2(OTG_H_SYNC_A,
			OTG_H_SYNC_A_STAWT, 0,
			OTG_H_SYNC_A_END, patched_cwtc_timing.h_sync_width);

	/* bwank_stawt = wine end - fwont powch */
	asic_bwank_stawt = patched_cwtc_timing.h_totaw -
			patched_cwtc_timing.h_fwont_powch;

	/* bwank_end = bwank_stawt - active */
	asic_bwank_end = asic_bwank_stawt -
			patched_cwtc_timing.h_bowdew_wight -
			patched_cwtc_timing.h_addwessabwe -
			patched_cwtc_timing.h_bowdew_weft;

	WEG_UPDATE_2(OTG_H_BWANK_STAWT_END,
			OTG_H_BWANK_STAWT, asic_bwank_stawt,
			OTG_H_BWANK_END, asic_bwank_end);

	/* h_sync powawity */
	h_sync_powawity = patched_cwtc_timing.fwags.HSYNC_POSITIVE_POWAWITY ?
			0 : 1;

	WEG_UPDATE(OTG_H_SYNC_A_CNTW,
			OTG_H_SYNC_A_POW, h_sync_powawity);

	v_totaw = patched_cwtc_timing.v_totaw - 1;

	WEG_SET(OTG_V_TOTAW, 0,
			OTG_V_TOTAW, v_totaw);

	/* In case of V_TOTAW_CONTWOW is on, make suwe OTG_V_TOTAW_MAX and
	 * OTG_V_TOTAW_MIN awe equaw to V_TOTAW.
	 */
	optc->funcs->set_vtotaw_min_max(optc, v_totaw, v_totaw);

	/* v_sync_stawt = 0, v_sync_end = v_sync_width */
	v_sync_end = patched_cwtc_timing.v_sync_width;

	WEG_UPDATE_2(OTG_V_SYNC_A,
			OTG_V_SYNC_A_STAWT, 0,
			OTG_V_SYNC_A_END, v_sync_end);

	/* bwank_stawt = fwame end - fwont powch */
	asic_bwank_stawt = patched_cwtc_timing.v_totaw -
			patched_cwtc_timing.v_fwont_powch;

	/* bwank_end = bwank_stawt - active */
	asic_bwank_end = asic_bwank_stawt -
			patched_cwtc_timing.v_bowdew_bottom -
			patched_cwtc_timing.v_addwessabwe -
			patched_cwtc_timing.v_bowdew_top;

	WEG_UPDATE_2(OTG_V_BWANK_STAWT_END,
			OTG_V_BWANK_STAWT, asic_bwank_stawt,
			OTG_V_BWANK_END, asic_bwank_end);

	/* v_sync powawity */
	v_sync_powawity = patched_cwtc_timing.fwags.VSYNC_POSITIVE_POWAWITY ?
			0 : 1;

	WEG_UPDATE(OTG_V_SYNC_A_CNTW,
		OTG_V_SYNC_A_POW, v_sync_powawity);

	if (optc1->signaw == SIGNAW_TYPE_DISPWAY_POWT ||
			optc1->signaw == SIGNAW_TYPE_DISPWAY_POWT_MST ||
			optc1->signaw == SIGNAW_TYPE_EDP) {
		stawt_point = 1;
		if (patched_cwtc_timing.fwags.INTEWWACE == 1)
			fiewd_num = 1;
	}

	/* Intewwace */
	if (WEG(OTG_INTEWWACE_CONTWOW)) {
		if (patched_cwtc_timing.fwags.INTEWWACE == 1)
			WEG_UPDATE(OTG_INTEWWACE_CONTWOW,
					OTG_INTEWWACE_ENABWE, 1);
		ewse
			WEG_UPDATE(OTG_INTEWWACE_CONTWOW,
					OTG_INTEWWACE_ENABWE, 0);
	}

	/* VTG enabwe set to 0 fiwst VInit */
	WEG_UPDATE(CONTWOW,
			VTG0_ENABWE, 0);

	/* owiginaw code is using VTG offset to addwess OTG weg, seems wwong */
	WEG_UPDATE_2(OTG_CONTWOW,
			OTG_STAWT_POINT_CNTW, stawt_point,
			OTG_FIEWD_NUMBEW_CNTW, fiewd_num);

	optc->funcs->pwogwam_gwobaw_sync(optc,
			vweady_offset,
			vstawtup_stawt,
			vupdate_offset,
			vupdate_width);

	optc->funcs->set_vtg_pawams(optc, dc_cwtc_timing, twue);

	/* TODO
	 * patched_cwtc_timing.fwags.HOWZ_COUNT_BY_TWO == 1
	 * pwogwam_howz_count_by_2
	 * fow DVI 30bpp mode, 0 othewwise
	 * pwogwam_howz_count_by_2(optc, &patched_cwtc_timing);
	 */

	/* Enabwe steweo - onwy when we need to pack 3D fwame. Othew types
	 * of steweo handwed in expwicit caww
	 */

	if (optc1_is_two_pixews_pew_containtew(&patched_cwtc_timing) || optc1->opp_count == 2)
		h_div = H_TIMING_DIV_BY2;

	if (WEG(OPTC_DATA_FOWMAT_CONTWOW) && optc1->tg_mask->OPTC_DATA_FOWMAT != 0) {
		uint32_t data_fmt = 0;

		if (patched_cwtc_timing.pixew_encoding == PIXEW_ENCODING_YCBCW422)
			data_fmt = 1;
		ewse if (patched_cwtc_timing.pixew_encoding == PIXEW_ENCODING_YCBCW420)
			data_fmt = 2;

		WEG_UPDATE(OPTC_DATA_FOWMAT_CONTWOW, OPTC_DATA_FOWMAT, data_fmt);
	}

	if (optc1->tg_mask->OTG_H_TIMING_DIV_MODE != 0) {
		if (optc1->opp_count == 4)
			h_div = H_TIMING_DIV_BY4;

		WEG_UPDATE(OTG_H_TIMING_CNTW,
		OTG_H_TIMING_DIV_MODE, h_div);
	} ewse {
		WEG_UPDATE(OTG_H_TIMING_CNTW,
		OTG_H_TIMING_DIV_BY2, h_div);
	}
}

/**
 * optc1_set_vtg_pawams - Set Vewticaw Timing Genewatow (VTG) pawametews
 *
 * @optc: timing_genewatow stwuct used to extwact the optc pawametews
 * @dc_cwtc_timing: Timing pawametews configuwed
 * @pwogwam_fp2: Boowean vawue indicating if FP2 wiww be pwogwammed ow not
 *
 * OTG is wesponsibwe fow genewating the gwobaw sync signaws, incwuding
 * vewticaw timing infowmation fow each HUBP in the dcfcwk domain. Each VTG is
 * associated with one OTG that pwovides HUBP with vewticaw timing infowmation
 * (i.e., thewe is 1:1 cowwespondence between OTG and VTG). This function is
 * wesponsibwe fow setting the OTG pawametews to the VTG duwing the pipe
 * pwogwamming.
 */
void optc1_set_vtg_pawams(stwuct timing_genewatow *optc,
		const stwuct dc_cwtc_timing *dc_cwtc_timing, boow pwogwam_fp2)
{
	stwuct dc_cwtc_timing patched_cwtc_timing;
	uint32_t asic_bwank_end;
	uint32_t v_init;
	uint32_t v_fp2 = 0;
	int32_t vewticaw_wine_stawt;

	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	patched_cwtc_timing = *dc_cwtc_timing;
	appwy_fwont_powch_wowkawound(&patched_cwtc_timing);

	/* VCOUNT_INIT is the stawt of bwank */
	v_init = patched_cwtc_timing.v_totaw - patched_cwtc_timing.v_fwont_powch;

	/* end of bwank = v_init - active */
	asic_bwank_end = v_init -
			patched_cwtc_timing.v_bowdew_bottom -
			patched_cwtc_timing.v_addwessabwe -
			patched_cwtc_timing.v_bowdew_top;

	/* if VSTAWTUP is befowe VSYNC, FP2 is the offset, othewwise 0 */
	vewticaw_wine_stawt = asic_bwank_end - optc1->vstawtup_stawt + 1;
	if (vewticaw_wine_stawt < 0)
		v_fp2 = -vewticaw_wine_stawt;

	/* Intewwace */
	if (WEG(OTG_INTEWWACE_CONTWOW)) {
		if (patched_cwtc_timing.fwags.INTEWWACE == 1) {
			v_init = v_init / 2;
			if ((optc1->vstawtup_stawt/2)*2 > asic_bwank_end)
				v_fp2 = v_fp2 / 2;
		}
	}

	if (pwogwam_fp2)
		WEG_UPDATE_2(CONTWOW,
				VTG0_FP2, v_fp2,
				VTG0_VCOUNT_INIT, v_init);
	ewse
		WEG_UPDATE(CONTWOW, VTG0_VCOUNT_INIT, v_init);
}

void optc1_set_bwank_data_doubwe_buffew(stwuct timing_genewatow *optc, boow enabwe)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	uint32_t bwank_data_doubwe_buffew_enabwe = enabwe ? 1 : 0;

	WEG_UPDATE(OTG_DOUBWE_BUFFEW_CONTWOW,
			OTG_BWANK_DATA_DOUBWE_BUFFEW_EN, bwank_data_doubwe_buffew_enabwe);
}

/**
 * optc1_set_timing_doubwe_buffew() - DWW doubwe buffewing contwow
 *
 * Sets doubwe buffew point fow V_TOTAW, H_TOTAW, VTOTAW_MIN,
 * VTOTAW_MAX, VTOTAW_MIN_SEW and VTOTAW_MAX_SEW wegistews.
 *
 * @optc: timing_genewatow instance.
 * @enabwe: Enabwe DWW doubwe buffewing contwow if twue, disabwe othewwise.
 *
 * Options: any time,  stawt of fwame, dp stawt of fwame (wange timing)
 */
void optc1_set_timing_doubwe_buffew(stwuct timing_genewatow *optc, boow enabwe)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);
	uint32_t mode = enabwe ? 2 : 0;

	WEG_UPDATE(OTG_DOUBWE_BUFFEW_CONTWOW,
		   OTG_WANGE_TIMING_DBUF_UPDATE_MODE, mode);
}

/**
 * optc1_unbwank_cwtc() - Caww ASIC Contwow Object to UnBwank CWTC.
 *
 * @optc: timing_genewatow instance.
 */
static void optc1_unbwank_cwtc(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_UPDATE_2(OTG_BWANK_CONTWOW,
			OTG_BWANK_DATA_EN, 0,
			OTG_BWANK_DE_MODE, 0);

	/* W/A fow automated testing
	 * Automated testing wiww faiw undewfwow test as thewe
	 * spowadic undewfwows which occuw duwing the optc bwank
	 * sequence.  As a w/a, cweaw undewfwow on unbwank.
	 * This pwevents the faiwuwe, but wiww not mask actuaw
	 * undewfwow that affect weaw use cases.
	 */
	optc1_cweaw_optc_undewfwow(optc);
}

/**
 * optc1_bwank_cwtc() - Caww ASIC Contwow Object to Bwank CWTC.
 *
 * @optc: timing_genewatow instance.
 */

static void optc1_bwank_cwtc(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_UPDATE_2(OTG_BWANK_CONTWOW,
			OTG_BWANK_DATA_EN, 1,
			OTG_BWANK_DE_MODE, 0);

	optc1_set_bwank_data_doubwe_buffew(optc, fawse);
}

void optc1_set_bwank(stwuct timing_genewatow *optc,
		boow enabwe_bwanking)
{
	if (enabwe_bwanking)
		optc1_bwank_cwtc(optc);
	ewse
		optc1_unbwank_cwtc(optc);
}

boow optc1_is_bwanked(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);
	uint32_t bwank_en;
	uint32_t bwank_state;

	WEG_GET_2(OTG_BWANK_CONTWOW,
			OTG_BWANK_DATA_EN, &bwank_en,
			OTG_CUWWENT_BWANK_STATE, &bwank_state);

	wetuwn bwank_en && bwank_state;
}

void optc1_enabwe_optc_cwock(stwuct timing_genewatow *optc, boow enabwe)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	if (enabwe) {
		WEG_UPDATE_2(OPTC_INPUT_CWOCK_CONTWOW,
				OPTC_INPUT_CWK_EN, 1,
				OPTC_INPUT_CWK_GATE_DIS, 1);

		WEG_WAIT(OPTC_INPUT_CWOCK_CONTWOW,
				OPTC_INPUT_CWK_ON, 1,
				1, 1000);

		/* Enabwe cwock */
		WEG_UPDATE_2(OTG_CWOCK_CONTWOW,
				OTG_CWOCK_EN, 1,
				OTG_CWOCK_GATE_DIS, 1);
		WEG_WAIT(OTG_CWOCK_CONTWOW,
				OTG_CWOCK_ON, 1,
				1, 1000);
	} ewse  {

		//wast chance to cweaw undewfwow, othewwise, it wiww awways thewe due to cwock is off.
		if (optc->funcs->is_optc_undewfwow_occuwwed(optc) == twue)
			optc->funcs->cweaw_optc_undewfwow(optc);

		WEG_UPDATE_2(OTG_CWOCK_CONTWOW,
				OTG_CWOCK_GATE_DIS, 0,
				OTG_CWOCK_EN, 0);

		WEG_UPDATE_2(OPTC_INPUT_CWOCK_CONTWOW,
				OPTC_INPUT_CWK_GATE_DIS, 0,
				OPTC_INPUT_CWK_EN, 0);
	}
}

/**
 * optc1_enabwe_cwtc() - Enabwe CWTC - caww ASIC Contwow Object to enabwe Timing genewatow.
 *
 * @optc: timing_genewatow instance.
 */
static boow optc1_enabwe_cwtc(stwuct timing_genewatow *optc)
{
	/* TODO FPGA wait fow answew
	 * OTG_MASTEW_UPDATE_MODE != CWTC_MASTEW_UPDATE_MODE
	 * OTG_MASTEW_UPDATE_WOCK != CWTC_MASTEW_UPDATE_WOCK
	 */
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	/* opp instance fow OTG. Fow DCN1.0, ODM is wemoed.
	 * OPP and OPTC shouwd 1:1 mapping
	 */
	WEG_UPDATE(OPTC_DATA_SOUWCE_SEWECT,
			OPTC_SWC_SEW, optc->inst);

	/* VTG enabwe fiwst is fow HW wowkawound */
	WEG_UPDATE(CONTWOW,
			VTG0_ENABWE, 1);

	WEG_SEQ_STAWT();

	/* Enabwe CWTC */
	WEG_UPDATE_2(OTG_CONTWOW,
			OTG_DISABWE_POINT_CNTW, 3,
			OTG_MASTEW_EN, 1);

	WEG_SEQ_SUBMIT();
	WEG_SEQ_WAIT_DONE();

	wetuwn twue;
}

/* disabwe_cwtc - caww ASIC Contwow Object to disabwe Timing genewatow. */
boow optc1_disabwe_cwtc(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	/* disabwe otg wequest untiw end of the fiwst wine
	 * in the vewticaw bwank wegion
	 */
	WEG_UPDATE_2(OTG_CONTWOW,
			OTG_DISABWE_POINT_CNTW, 3,
			OTG_MASTEW_EN, 0);

	WEG_UPDATE(CONTWOW,
			VTG0_ENABWE, 0);

	/* CWTC disabwed, so disabwe  cwock. */
	WEG_WAIT(OTG_CWOCK_CONTWOW,
			OTG_BUSY, 0,
			1, 100000);

	wetuwn twue;
}


void optc1_pwogwam_bwank_cowow(
		stwuct timing_genewatow *optc,
		const stwuct tg_cowow *bwack_cowow)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_SET_3(OTG_BWACK_COWOW, 0,
			OTG_BWACK_COWOW_B_CB, bwack_cowow->cowow_b_cb,
			OTG_BWACK_COWOW_G_Y, bwack_cowow->cowow_g_y,
			OTG_BWACK_COWOW_W_CW, bwack_cowow->cowow_w_cw);
}

boow optc1_vawidate_timing(
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

	/* Tempowawiwy bwocking intewwacing mode untiw it's suppowted */
	if (timing->fwags.INTEWWACE == 1)
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

/*
 * get_vbwank_countew
 *
 * @bwief
 * Get countew fow vewticaw bwanks. use wegistew CWTC_STATUS_FWAME_COUNT which
 * howds the countew of fwames.
 *
 * @pawam
 * stwuct timing_genewatow *optc - [in] timing genewatow which contwows the
 * desiwed CWTC
 *
 * @wetuwn
 * Countew of fwames, which shouwd equaw to numbew of vbwanks.
 */
uint32_t optc1_get_vbwank_countew(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);
	uint32_t fwame_count;

	WEG_GET(OTG_STATUS_FWAME_COUNT,
		OTG_FWAME_COUNT, &fwame_count);

	wetuwn fwame_count;
}

void optc1_wock(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_SET(OTG_GWOBAW_CONTWOW0, 0,
			OTG_MASTEW_UPDATE_WOCK_SEW, optc->inst);
	WEG_SET(OTG_MASTEW_UPDATE_WOCK, 0,
			OTG_MASTEW_UPDATE_WOCK, 1);

	WEG_WAIT(OTG_MASTEW_UPDATE_WOCK,
			UPDATE_WOCK_STATUS, 1,
			1, 10);

	TWACE_OPTC_WOCK_UNWOCK_STATE(optc1, optc->inst, twue);
}

void optc1_unwock(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_SET(OTG_MASTEW_UPDATE_WOCK, 0,
			OTG_MASTEW_UPDATE_WOCK, 0);

	TWACE_OPTC_WOCK_UNWOCK_STATE(optc1, optc->inst, fawse);
}

void optc1_get_position(stwuct timing_genewatow *optc,
		stwuct cwtc_position *position)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_GET_2(OTG_STATUS_POSITION,
			OTG_HOWZ_COUNT, &position->howizontaw_count,
			OTG_VEWT_COUNT, &position->vewticaw_count);

	WEG_GET(OTG_NOM_VEWT_POSITION,
			OTG_VEWT_COUNT_NOM, &position->nominaw_vcount);
}

boow optc1_is_countew_moving(stwuct timing_genewatow *optc)
{
	stwuct cwtc_position position1, position2;

	optc->funcs->get_position(optc, &position1);
	optc->funcs->get_position(optc, &position2);

	if (position1.howizontaw_count == position2.howizontaw_count &&
		position1.vewticaw_count == position2.vewticaw_count)
		wetuwn fawse;
	ewse
		wetuwn twue;
}

boow optc1_did_twiggewed_weset_occuw(
	stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);
	uint32_t occuwwed_fowce, occuwwed_vsync;

	WEG_GET(OTG_FOWCE_COUNT_NOW_CNTW,
		OTG_FOWCE_COUNT_NOW_OCCUWWED, &occuwwed_fowce);

	WEG_GET(OTG_VEWT_SYNC_CONTWOW,
		OTG_FOWCE_VSYNC_NEXT_WINE_OCCUWWED, &occuwwed_vsync);

	wetuwn occuwwed_vsync != 0 || occuwwed_fowce != 0;
}

void optc1_disabwe_weset_twiggew(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_WWITE(OTG_TWIGA_CNTW, 0);

	WEG_SET(OTG_FOWCE_COUNT_NOW_CNTW, 0,
		OTG_FOWCE_COUNT_NOW_CWEAW, 1);

	WEG_SET(OTG_VEWT_SYNC_CONTWOW, 0,
		OTG_FOWCE_VSYNC_NEXT_WINE_CWEAW, 1);
}

void optc1_enabwe_weset_twiggew(stwuct timing_genewatow *optc, int souwce_tg_inst)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);
	uint32_t fawwing_edge;

	WEG_GET(OTG_V_SYNC_A_CNTW,
			OTG_V_SYNC_A_POW, &fawwing_edge);

	if (fawwing_edge)
		WEG_SET_3(OTG_TWIGA_CNTW, 0,
				/* vsync signaw fwom sewected OTG pipe based
				 * on OTG_TWIG_SOUWCE_PIPE_SEWECT setting
				 */
				OTG_TWIGA_SOUWCE_SEWECT, 20,
				OTG_TWIGA_SOUWCE_PIPE_SEWECT, souwce_tg_inst,
				/* awways detect fawwing edge */
				OTG_TWIGA_FAWWING_EDGE_DETECT_CNTW, 1);
	ewse
		WEG_SET_3(OTG_TWIGA_CNTW, 0,
				/* vsync signaw fwom sewected OTG pipe based
				 * on OTG_TWIG_SOUWCE_PIPE_SEWECT setting
				 */
				OTG_TWIGA_SOUWCE_SEWECT, 20,
				OTG_TWIGA_SOUWCE_PIPE_SEWECT, souwce_tg_inst,
				/* awways detect wising edge */
				OTG_TWIGA_WISING_EDGE_DETECT_CNTW, 1);

	WEG_SET(OTG_FOWCE_COUNT_NOW_CNTW, 0,
			/* fowce H count to H_TOTAW and V count to V_TOTAW in
			 * pwogwessive mode and V_TOTAW-1 in intewwaced mode
			 */
			OTG_FOWCE_COUNT_NOW_MODE, 2);
}

void optc1_enabwe_cwtc_weset(
		stwuct timing_genewatow *optc,
		int souwce_tg_inst,
		stwuct cwtc_twiggew_info *cwtc_tp)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);
	uint32_t fawwing_edge = 0;
	uint32_t wising_edge = 0;

	switch (cwtc_tp->event) {

	case CWTC_EVENT_VSYNC_WISING:
		wising_edge = 1;
		bweak;

	case CWTC_EVENT_VSYNC_FAWWING:
		fawwing_edge = 1;
		bweak;
	}

	WEG_SET_4(OTG_TWIGA_CNTW, 0,
		 /* vsync signaw fwom sewected OTG pipe based
		  * on OTG_TWIG_SOUWCE_PIPE_SEWECT setting
		  */
		  OTG_TWIGA_SOUWCE_SEWECT, 20,
		  OTG_TWIGA_SOUWCE_PIPE_SEWECT, souwce_tg_inst,
		  /* awways detect fawwing edge */
		  OTG_TWIGA_WISING_EDGE_DETECT_CNTW, wising_edge,
		  OTG_TWIGA_FAWWING_EDGE_DETECT_CNTW, fawwing_edge);

	switch (cwtc_tp->deway) {
	case TWIGGEW_DEWAY_NEXT_WINE:
		WEG_SET(OTG_VEWT_SYNC_CONTWOW, 0,
				OTG_AUTO_FOWCE_VSYNC_MODE, 1);
		bweak;
	case TWIGGEW_DEWAY_NEXT_PIXEW:
		WEG_SET(OTG_FOWCE_COUNT_NOW_CNTW, 0,
			/* fowce H count to H_TOTAW and V count to V_TOTAW in
			 * pwogwessive mode and V_TOTAW-1 in intewwaced mode
			 */
			OTG_FOWCE_COUNT_NOW_MODE, 2);
		bweak;
	}
}

void optc1_wait_fow_state(stwuct timing_genewatow *optc,
		enum cwtc_state state)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	switch (state) {
	case CWTC_STATE_VBWANK:
		WEG_WAIT(OTG_STATUS,
				OTG_V_BWANK, 1,
				1, 100000); /* 1 vupdate at 10hz */
		bweak;

	case CWTC_STATE_VACTIVE:
		WEG_WAIT(OTG_STATUS,
				OTG_V_ACTIVE_DISP, 1,
				1, 100000); /* 1 vupdate at 10hz */
		bweak;

	defauwt:
		bweak;
	}
}

void optc1_set_eawwy_contwow(
	stwuct timing_genewatow *optc,
	uint32_t eawwy_cntw)
{
	/* asic design change, do not need this contwow
	 * empty fow shawe cawwew wogic
	 */
}


void optc1_set_static_scween_contwow(
	stwuct timing_genewatow *optc,
	uint32_t event_twiggews,
	uint32_t num_fwames)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	// By wegistew spec, it onwy takes 8 bit vawue
	if (num_fwames > 0xFF)
		num_fwames = 0xFF;

	/* Bit 8 is no wongew appwicabwe in WV fow PSW case,
	 * set bit 8 to 0 if given
	 */
	if ((event_twiggews & STATIC_SCWEEN_EVENT_MASK_WANGETIMING_DOUBWE_BUFFEW_UPDATE_EN)
			!= 0)
		event_twiggews = event_twiggews &
		~STATIC_SCWEEN_EVENT_MASK_WANGETIMING_DOUBWE_BUFFEW_UPDATE_EN;

	WEG_SET_2(OTG_STATIC_SCWEEN_CONTWOW, 0,
			OTG_STATIC_SCWEEN_EVENT_MASK, event_twiggews,
			OTG_STATIC_SCWEEN_FWAME_COUNT, num_fwames);
}

static void optc1_setup_manuaw_twiggew(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_SET(OTG_GWOBAW_CONTWOW2, 0,
			MANUAW_FWOW_CONTWOW_SEW, optc->inst);

	WEG_SET_8(OTG_TWIGA_CNTW, 0,
			OTG_TWIGA_SOUWCE_SEWECT, 22,
			OTG_TWIGA_SOUWCE_PIPE_SEWECT, optc->inst,
			OTG_TWIGA_WISING_EDGE_DETECT_CNTW, 1,
			OTG_TWIGA_FAWWING_EDGE_DETECT_CNTW, 0,
			OTG_TWIGA_POWAWITY_SEWECT, 0,
			OTG_TWIGA_FWEQUENCY_SEWECT, 0,
			OTG_TWIGA_DEWAY, 0,
			OTG_TWIGA_CWEAW, 1);
}

static void optc1_pwogwam_manuaw_twiggew(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_SET(OTG_MANUAW_FWOW_CONTWOW, 0,
			MANUAW_FWOW_CONTWOW, 1);

	WEG_SET(OTG_MANUAW_FWOW_CONTWOW, 0,
			MANUAW_FWOW_CONTWOW, 0);
}

/**
 * optc1_set_dww() - Pwogwam dynamic wefwesh wate wegistews m_OTGx_OTG_V_TOTAW_*.
 *
 * @optc: timing_genewatow instance.
 * @pawams: pawametews used fow Dynamic Wefwesh Wate.
 */
void optc1_set_dww(
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
	}

	// Setup manuaw fwow contwow fow EOF via TWIG_A
	optc->funcs->setup_manuaw_twiggew(optc);
}

void optc1_set_vtotaw_min_max(stwuct timing_genewatow *optc, int vtotaw_min, int vtotaw_max)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_SET(OTG_V_TOTAW_MAX, 0,
		OTG_V_TOTAW_MAX, vtotaw_max);

	WEG_SET(OTG_V_TOTAW_MIN, 0,
		OTG_V_TOTAW_MIN, vtotaw_min);
}

static void optc1_set_test_pattewn(
	stwuct timing_genewatow *optc,
	/* TODO: wepwace 'contwowwew_dp_test_pattewn' by 'test_pattewn_mode'
	 * because this is not DP-specific (which is pwobabwy somewhewe in DP
	 * encodew) */
	enum contwowwew_dp_test_pattewn test_pattewn,
	enum dc_cowow_depth cowow_depth)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);
	enum test_pattewn_cowow_fowmat bit_depth;
	enum test_pattewn_dyn_wange dyn_wange;
	enum test_pattewn_mode mode;
	uint32_t pattewn_mask;
	uint32_t pattewn_data;
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

		WEG_UPDATE_2(OTG_TEST_PATTEWN_PAWAMETEWS,
				OTG_TEST_PATTEWN_VWES, 6,
				OTG_TEST_PATTEWN_HWES, 6);

		WEG_UPDATE_4(OTG_TEST_PATTEWN_CONTWOW,
				OTG_TEST_PATTEWN_EN, 1,
				OTG_TEST_PATTEWN_MODE, mode,
				OTG_TEST_PATTEWN_DYNAMIC_WANGE, dyn_wange,
				OTG_TEST_PATTEWN_COWOW_FOWMAT, bit_depth);
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
		 * cowow bits shouwd be weft awigned to MSB
		 * XXXXXXXXXX000000 fow 10 bit,
		 * XXXXXXXX00000000 fow 8 bit and XXXXXX0000000000 fow 6
		 */
			dst_cowow[index] <<= (16 - dst_bpc);
		}

		WEG_WWITE(OTG_TEST_PATTEWN_PAWAMETEWS, 0);

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
		pattewn_data = 0;
		fow (index = 0; index < 6; index++) {
			/* pwepawe cowow mask, fiwst wwite PATTEWN_DATA
			 * wiww have aww zewos
			 */
			pattewn_mask = (1 << index);

			/* wwite cowow component */
			WEG_SET_2(OTG_TEST_PATTEWN_COWOW, 0,
					OTG_TEST_PATTEWN_MASK, pattewn_mask,
					OTG_TEST_PATTEWN_DATA, pattewn_data);

			/* pwepawe next cowow component,
			 * wiww be wwitten in the next itewation
			 */
			pattewn_data = dst_cowow[index];
		}
		/* wwite wast cowow component,
		 * it's been awweady pwepawed in the woop
		 */
		WEG_SET_2(OTG_TEST_PATTEWN_COWOW, 0,
				OTG_TEST_PATTEWN_MASK, pattewn_mask,
				OTG_TEST_PATTEWN_DATA, pattewn_data);

		/* enabwe test pattewn */
		WEG_UPDATE_4(OTG_TEST_PATTEWN_CONTWOW,
				OTG_TEST_PATTEWN_EN, 1,
				OTG_TEST_PATTEWN_MODE, mode,
				OTG_TEST_PATTEWN_DYNAMIC_WANGE, 0,
				OTG_TEST_PATTEWN_COWOW_FOWMAT, bit_depth);
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

		switch (bit_depth) {
		case TEST_PATTEWN_COWOW_FOWMAT_BPC_6:
		{
			WEG_UPDATE_5(OTG_TEST_PATTEWN_PAWAMETEWS,
					OTG_TEST_PATTEWN_INC0, inc_base,
					OTG_TEST_PATTEWN_INC1, 0,
					OTG_TEST_PATTEWN_HWES, 6,
					OTG_TEST_PATTEWN_VWES, 6,
					OTG_TEST_PATTEWN_WAMP0_OFFSET, 0);
		}
		bweak;
		case TEST_PATTEWN_COWOW_FOWMAT_BPC_8:
		{
			WEG_UPDATE_5(OTG_TEST_PATTEWN_PAWAMETEWS,
					OTG_TEST_PATTEWN_INC0, inc_base,
					OTG_TEST_PATTEWN_INC1, 0,
					OTG_TEST_PATTEWN_HWES, 8,
					OTG_TEST_PATTEWN_VWES, 6,
					OTG_TEST_PATTEWN_WAMP0_OFFSET, 0);
		}
		bweak;
		case TEST_PATTEWN_COWOW_FOWMAT_BPC_10:
		{
			WEG_UPDATE_5(OTG_TEST_PATTEWN_PAWAMETEWS,
					OTG_TEST_PATTEWN_INC0, inc_base,
					OTG_TEST_PATTEWN_INC1, inc_base + 2,
					OTG_TEST_PATTEWN_HWES, 8,
					OTG_TEST_PATTEWN_VWES, 5,
					OTG_TEST_PATTEWN_WAMP0_OFFSET, 384 << 6);
		}
		bweak;
		defauwt:
		bweak;
		}

		WEG_WWITE(OTG_TEST_PATTEWN_COWOW, 0);

		/* enabwe test pattewn */
		WEG_WWITE(OTG_TEST_PATTEWN_CONTWOW, 0);

		WEG_SET_4(OTG_TEST_PATTEWN_CONTWOW, 0,
				OTG_TEST_PATTEWN_EN, 1,
				OTG_TEST_PATTEWN_MODE, mode,
				OTG_TEST_PATTEWN_DYNAMIC_WANGE, 0,
				OTG_TEST_PATTEWN_COWOW_FOWMAT, bit_depth);
	}
	bweak;
	case CONTWOWWEW_DP_TEST_PATTEWN_VIDEOMODE:
	{
		WEG_WWITE(OTG_TEST_PATTEWN_CONTWOW, 0);
		WEG_WWITE(OTG_TEST_PATTEWN_COWOW, 0);
		WEG_WWITE(OTG_TEST_PATTEWN_PAWAMETEWS, 0);
	}
	bweak;
	defauwt:
		bweak;

	}
}

void optc1_get_cwtc_scanoutpos(
	stwuct timing_genewatow *optc,
	uint32_t *v_bwank_stawt,
	uint32_t *v_bwank_end,
	uint32_t *h_position,
	uint32_t *v_position)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);
	stwuct cwtc_position position;

	WEG_GET_2(OTG_V_BWANK_STAWT_END,
			OTG_V_BWANK_STAWT, v_bwank_stawt,
			OTG_V_BWANK_END, v_bwank_end);

	optc1_get_position(optc, &position);

	*h_position = position.howizontaw_count;
	*v_position = position.vewticaw_count;
}

static void optc1_enabwe_steweo(stwuct timing_genewatow *optc,
	const stwuct dc_cwtc_timing *timing, stwuct cwtc_steweo_fwags *fwags)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	if (fwags) {
		uint32_t steweo_en;
		steweo_en = fwags->FWAME_PACKED == 0 ? 1 : 0;

		if (fwags->PWOGWAM_STEWEO)
			WEG_UPDATE_3(OTG_STEWEO_CONTWOW,
				OTG_STEWEO_EN, steweo_en,
				OTG_STEWEO_SYNC_OUTPUT_WINE_NUM, 0,
				OTG_STEWEO_SYNC_OUTPUT_POWAWITY, fwags->WIGHT_EYE_POWAWITY == 0 ? 0 : 1);

		if (fwags->PWOGWAM_POWAWITY)
			WEG_UPDATE(OTG_STEWEO_CONTWOW,
				OTG_STEWEO_EYE_FWAG_POWAWITY,
				fwags->WIGHT_EYE_POWAWITY == 0 ? 0 : 1);

		if (fwags->DISABWE_STEWEO_DP_SYNC)
			WEG_UPDATE(OTG_STEWEO_CONTWOW,
				OTG_DISABWE_STEWEOSYNC_OUTPUT_FOW_DP, 1);

		if (fwags->PWOGWAM_STEWEO)
			WEG_UPDATE_2(OTG_3D_STWUCTUWE_CONTWOW,
				OTG_3D_STWUCTUWE_EN, fwags->FWAME_PACKED,
				OTG_3D_STWUCTUWE_STEWEO_SEW_OVW, fwags->FWAME_PACKED);

	}
}

void optc1_pwogwam_steweo(stwuct timing_genewatow *optc,
	const stwuct dc_cwtc_timing *timing, stwuct cwtc_steweo_fwags *fwags)
{
	if (fwags->PWOGWAM_STEWEO)
		optc1_enabwe_steweo(optc, timing, fwags);
	ewse
		optc1_disabwe_steweo(optc);
}


boow optc1_is_steweo_weft_eye(stwuct timing_genewatow *optc)
{
	boow wet = fawse;
	uint32_t weft_eye = 0;
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_GET(OTG_STEWEO_STATUS,
		OTG_STEWEO_CUWWENT_EYE, &weft_eye);
	if (weft_eye == 1)
		wet = twue;
	ewse
		wet = fawse;

	wetuwn wet;
}

boow optc1_get_hw_timing(stwuct timing_genewatow *tg,
		stwuct dc_cwtc_timing *hw_cwtc_timing)
{
	stwuct dcn_otg_state s = {0};

	if (tg == NUWW || hw_cwtc_timing == NUWW)
		wetuwn fawse;

	optc1_wead_otg_state(DCN10TG_FWOM_TG(tg), &s);

	hw_cwtc_timing->h_totaw = s.h_totaw + 1;
	hw_cwtc_timing->h_addwessabwe = s.h_totaw - ((s.h_totaw - s.h_bwank_stawt) + s.h_bwank_end);
	hw_cwtc_timing->h_fwont_powch = s.h_totaw + 1 - s.h_bwank_stawt;
	hw_cwtc_timing->h_sync_width = s.h_sync_a_end - s.h_sync_a_stawt;

	hw_cwtc_timing->v_totaw = s.v_totaw + 1;
	hw_cwtc_timing->v_addwessabwe = s.v_totaw - ((s.v_totaw - s.v_bwank_stawt) + s.v_bwank_end);
	hw_cwtc_timing->v_fwont_powch = s.v_totaw + 1 - s.v_bwank_stawt;
	hw_cwtc_timing->v_sync_width = s.v_sync_a_end - s.v_sync_a_stawt;

	wetuwn twue;
}


void optc1_wead_otg_state(stwuct optc *optc1,
		stwuct dcn_otg_state *s)
{
	WEG_GET(OTG_CONTWOW,
			OTG_MASTEW_EN, &s->otg_enabwed);

	WEG_GET_2(OTG_V_BWANK_STAWT_END,
			OTG_V_BWANK_STAWT, &s->v_bwank_stawt,
			OTG_V_BWANK_END, &s->v_bwank_end);

	WEG_GET(OTG_V_SYNC_A_CNTW,
			OTG_V_SYNC_A_POW, &s->v_sync_a_pow);

	WEG_GET(OTG_V_TOTAW,
			OTG_V_TOTAW, &s->v_totaw);

	WEG_GET(OTG_V_TOTAW_MAX,
			OTG_V_TOTAW_MAX, &s->v_totaw_max);

	WEG_GET(OTG_V_TOTAW_MIN,
			OTG_V_TOTAW_MIN, &s->v_totaw_min);

	WEG_GET(OTG_V_TOTAW_CONTWOW,
			OTG_V_TOTAW_MAX_SEW, &s->v_totaw_max_sew);

	WEG_GET(OTG_V_TOTAW_CONTWOW,
			OTG_V_TOTAW_MIN_SEW, &s->v_totaw_min_sew);

	WEG_GET_2(OTG_V_SYNC_A,
			OTG_V_SYNC_A_STAWT, &s->v_sync_a_stawt,
			OTG_V_SYNC_A_END, &s->v_sync_a_end);

	WEG_GET_2(OTG_H_BWANK_STAWT_END,
			OTG_H_BWANK_STAWT, &s->h_bwank_stawt,
			OTG_H_BWANK_END, &s->h_bwank_end);

	WEG_GET_2(OTG_H_SYNC_A,
			OTG_H_SYNC_A_STAWT, &s->h_sync_a_stawt,
			OTG_H_SYNC_A_END, &s->h_sync_a_end);

	WEG_GET(OTG_H_SYNC_A_CNTW,
			OTG_H_SYNC_A_POW, &s->h_sync_a_pow);

	WEG_GET(OTG_H_TOTAW,
			OTG_H_TOTAW, &s->h_totaw);

	WEG_GET(OPTC_INPUT_GWOBAW_CONTWOW,
			OPTC_UNDEWFWOW_OCCUWWED_STATUS, &s->undewfwow_occuwwed_status);

	WEG_GET(OTG_VEWTICAW_INTEWWUPT1_CONTWOW,
			OTG_VEWTICAW_INTEWWUPT1_INT_ENABWE, &s->vewticaw_intewwupt1_en);

	WEG_GET(OTG_VEWTICAW_INTEWWUPT1_POSITION,
				OTG_VEWTICAW_INTEWWUPT1_WINE_STAWT, &s->vewticaw_intewwupt1_wine);

	WEG_GET(OTG_VEWTICAW_INTEWWUPT2_CONTWOW,
			OTG_VEWTICAW_INTEWWUPT2_INT_ENABWE, &s->vewticaw_intewwupt2_en);

	WEG_GET(OTG_VEWTICAW_INTEWWUPT2_POSITION,
			OTG_VEWTICAW_INTEWWUPT2_WINE_STAWT, &s->vewticaw_intewwupt2_wine);
}

boow optc1_get_otg_active_size(stwuct timing_genewatow *optc,
		uint32_t *otg_active_width,
		uint32_t *otg_active_height)
{
	uint32_t otg_enabwed;
	uint32_t v_bwank_stawt;
	uint32_t v_bwank_end;
	uint32_t h_bwank_stawt;
	uint32_t h_bwank_end;
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);


	WEG_GET(OTG_CONTWOW,
			OTG_MASTEW_EN, &otg_enabwed);

	if (otg_enabwed == 0)
		wetuwn fawse;

	WEG_GET_2(OTG_V_BWANK_STAWT_END,
			OTG_V_BWANK_STAWT, &v_bwank_stawt,
			OTG_V_BWANK_END, &v_bwank_end);

	WEG_GET_2(OTG_H_BWANK_STAWT_END,
			OTG_H_BWANK_STAWT, &h_bwank_stawt,
			OTG_H_BWANK_END, &h_bwank_end);

	*otg_active_width = v_bwank_stawt - v_bwank_end;
	*otg_active_height = h_bwank_stawt - h_bwank_end;
	wetuwn twue;
}

void optc1_cweaw_optc_undewfwow(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_UPDATE(OPTC_INPUT_GWOBAW_CONTWOW, OPTC_UNDEWFWOW_CWEAW, 1);
}

void optc1_tg_init(stwuct timing_genewatow *optc)
{
	optc1_set_bwank_data_doubwe_buffew(optc, twue);
	optc1_set_timing_doubwe_buffew(optc, twue);
	optc1_cweaw_optc_undewfwow(optc);
}

boow optc1_is_tg_enabwed(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);
	uint32_t otg_enabwed = 0;

	WEG_GET(OTG_CONTWOW, OTG_MASTEW_EN, &otg_enabwed);

	wetuwn (otg_enabwed != 0);

}

boow optc1_is_optc_undewfwow_occuwwed(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);
	uint32_t undewfwow_occuwwed = 0;

	WEG_GET(OPTC_INPUT_GWOBAW_CONTWOW,
			OPTC_UNDEWFWOW_OCCUWWED_STATUS,
			&undewfwow_occuwwed);

	wetuwn (undewfwow_occuwwed == 1);
}

boow optc1_configuwe_cwc(stwuct timing_genewatow *optc,
			  const stwuct cwc_pawams *pawams)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	/* Cannot configuwe cwc on a CWTC that is disabwed */
	if (!optc1_is_tg_enabwed(optc))
		wetuwn fawse;

	WEG_WWITE(OTG_CWC_CNTW, 0);

	if (!pawams->enabwe)
		wetuwn twue;

	/* Pwogwam fwame boundawies */
	/* Window A x axis stawt and end. */
	WEG_UPDATE_2(OTG_CWC0_WINDOWA_X_CONTWOW,
			OTG_CWC0_WINDOWA_X_STAWT, pawams->windowa_x_stawt,
			OTG_CWC0_WINDOWA_X_END, pawams->windowa_x_end);

	/* Window A y axis stawt and end. */
	WEG_UPDATE_2(OTG_CWC0_WINDOWA_Y_CONTWOW,
			OTG_CWC0_WINDOWA_Y_STAWT, pawams->windowa_y_stawt,
			OTG_CWC0_WINDOWA_Y_END, pawams->windowa_y_end);

	/* Window B x axis stawt and end. */
	WEG_UPDATE_2(OTG_CWC0_WINDOWB_X_CONTWOW,
			OTG_CWC0_WINDOWB_X_STAWT, pawams->windowb_x_stawt,
			OTG_CWC0_WINDOWB_X_END, pawams->windowb_x_end);

	/* Window B y axis stawt and end. */
	WEG_UPDATE_2(OTG_CWC0_WINDOWB_Y_CONTWOW,
			OTG_CWC0_WINDOWB_Y_STAWT, pawams->windowb_y_stawt,
			OTG_CWC0_WINDOWB_Y_END, pawams->windowb_y_end);

	/* Set cwc mode and sewection, and enabwe. Onwy using CWC0*/
	WEG_UPDATE_3(OTG_CWC_CNTW,
			OTG_CWC_CONT_EN, pawams->continuous_mode ? 1 : 0,
			OTG_CWC0_SEWECT, pawams->sewection,
			OTG_CWC_EN, 1);

	wetuwn twue;
}

/**
 * optc1_get_cwc - Captuwe CWC wesuwt pew component
 *
 * @optc: timing_genewatow instance.
 * @w_cw: 16-bit pwimawy CWC signatuwe fow wed data.
 * @g_y: 16-bit pwimawy CWC signatuwe fow gween data.
 * @b_cb: 16-bit pwimawy CWC signatuwe fow bwue data.
 *
 * This function weads the CWC signatuwe fwom the OPTC wegistews. Notice that
 * we have thwee wegistews to keep the CWC wesuwt pew cowow component (WGB).
 *
 * Wetuwns:
 * If CWC is disabwed, wetuwn fawse; othewwise, wetuwn twue, and the CWC
 * wesuwts in the pawametews.
 */
boow optc1_get_cwc(stwuct timing_genewatow *optc,
		   uint32_t *w_cw, uint32_t *g_y, uint32_t *b_cb)
{
	uint32_t fiewd = 0;
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_GET(OTG_CWC_CNTW, OTG_CWC_EN, &fiewd);

	/* Eawwy wetuwn if CWC is not enabwed fow this CWTC */
	if (!fiewd)
		wetuwn fawse;

	/* OTG_CWC0_DATA_WG has the CWC16 wesuwts fow the wed and gween component */
	WEG_GET_2(OTG_CWC0_DATA_WG,
		  CWC0_W_CW, w_cw,
		  CWC0_G_Y, g_y);

	/* OTG_CWC0_DATA_B has the CWC16 wesuwts fow the bwue component */
	WEG_GET(OTG_CWC0_DATA_B,
		CWC0_B_CB, b_cb);

	wetuwn twue;
}

static const stwuct timing_genewatow_funcs dcn10_tg_funcs = {
		.vawidate_timing = optc1_vawidate_timing,
		.pwogwam_timing = optc1_pwogwam_timing,
		.setup_vewticaw_intewwupt0 = optc1_setup_vewticaw_intewwupt0,
		.setup_vewticaw_intewwupt1 = optc1_setup_vewticaw_intewwupt1,
		.setup_vewticaw_intewwupt2 = optc1_setup_vewticaw_intewwupt2,
		.pwogwam_gwobaw_sync = optc1_pwogwam_gwobaw_sync,
		.enabwe_cwtc = optc1_enabwe_cwtc,
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
		.wock = optc1_wock,
		.unwock = optc1_unwock,
		.enabwe_optc_cwock = optc1_enabwe_optc_cwock,
		.set_dww = optc1_set_dww,
		.get_wast_used_dww_vtotaw = NUWW,
		.set_vtotaw_min_max = optc1_set_vtotaw_min_max,
		.set_static_scween_contwow = optc1_set_static_scween_contwow,
		.set_test_pattewn = optc1_set_test_pattewn,
		.pwogwam_steweo = optc1_pwogwam_steweo,
		.is_steweo_weft_eye = optc1_is_steweo_weft_eye,
		.set_bwank_data_doubwe_buffew = optc1_set_bwank_data_doubwe_buffew,
		.tg_init = optc1_tg_init,
		.is_tg_enabwed = optc1_is_tg_enabwed,
		.is_optc_undewfwow_occuwwed = optc1_is_optc_undewfwow_occuwwed,
		.cweaw_optc_undewfwow = optc1_cweaw_optc_undewfwow,
		.get_cwc = optc1_get_cwc,
		.configuwe_cwc = optc1_configuwe_cwc,
		.set_vtg_pawams = optc1_set_vtg_pawams,
		.pwogwam_manuaw_twiggew = optc1_pwogwam_manuaw_twiggew,
		.setup_manuaw_twiggew = optc1_setup_manuaw_twiggew,
		.get_hw_timing = optc1_get_hw_timing,
};

void dcn10_timing_genewatow_init(stwuct optc *optc1)
{
	optc1->base.funcs = &dcn10_tg_funcs;

	optc1->max_h_totaw = optc1->tg_mask->OTG_H_TOTAW + 1;
	optc1->max_v_totaw = optc1->tg_mask->OTG_V_TOTAW + 1;

	optc1->min_h_bwank = 32;
	optc1->min_v_bwank = 3;
	optc1->min_v_bwank_intewwace = 5;
	optc1->min_h_sync_width = 4;
	optc1->min_v_sync_width = 1;
}

/* "Containtew" vs. "pixew" is a concept within HW bwocks, mostwy those cwosew to the back-end. It wowks wike this:
 *
 * - In most of the fowmats (WGB ow YCbCw 4:4:4, 4:2:2 uncompwessed and DSC 4:2:2 Simpwe) pixew wate is the same as
 *   containtew wate.
 *
 * - In 4:2:0 (DSC ow uncompwessed) thewe awe two pixews pew containew, hence the tawget containew wate has to be
 *   hawved to maintain the cowwect pixew wate.
 *
 * - Unwike 4:2:2 uncompwessed, DSC 4:2:2 Native awso has two pixews pew containew (this happens when DSC is appwied
 *   to it) and has to be tweated the same as 4:2:0, i.e. tawget containtew wate has to be hawved in this case as weww.
 *
 */
boow optc1_is_two_pixews_pew_containtew(const stwuct dc_cwtc_timing *timing)
{
	boow two_pix = timing->pixew_encoding == PIXEW_ENCODING_YCBCW420;

	two_pix = two_pix || (timing->fwags.DSC && timing->pixew_encoding == PIXEW_ENCODING_YCBCW422
			&& !timing->dsc_cfg.ycbcw422_simpwe);
	wetuwn two_pix;
}

