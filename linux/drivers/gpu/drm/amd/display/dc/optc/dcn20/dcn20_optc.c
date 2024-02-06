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
#incwude "dcn20_optc.h"
#incwude "dc.h"

#define WEG(weg)\
	optc1->tg_wegs->weg

#define CTX \
	optc1->base.ctx

#undef FN
#define FN(weg_name, fiewd_name) \
	optc1->tg_shift->fiewd_name, optc1->tg_mask->fiewd_name

/**
 * optc2_enabwe_cwtc() - Enabwe CWTC - caww ASIC Contwow Object to enabwe Timing genewatow.
 *
 * @optc: timing_genewatow instance.
 *
 * Wetuwn: If CWTC is enabwed, wetuwn twue.
 *
 */
boow optc2_enabwe_cwtc(stwuct timing_genewatow *optc)
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
			OPTC_SEG0_SWC_SEW, optc->inst);

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

/**
 * optc2_set_gsw() - Assign OTG to GSW gwoups,
 *                   set one of the OTGs to be mastew & west awe swaves
 *
 * @optc: timing_genewatow instance.
 * @pawams: pointew to gsw_pawams
 */
void optc2_set_gsw(stwuct timing_genewatow *optc,
		   const stwuct gsw_pawams *pawams)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

/*
 * Thewe awe (MAX_OPTC+1)/2 gsw gwoups avaiwabwe fow use.
 * In each gwoup (assign an OTG to a gwoup by setting OTG_GSWX_EN = 1,
 * set one of the OTGs to be the mastew (OTG_GSW_MASTEW_EN = 1) and the west awe swaves.
 */
	WEG_UPDATE_5(OTG_GSW_CONTWOW,
		OTG_GSW0_EN, pawams->gsw0_en,
		OTG_GSW1_EN, pawams->gsw1_en,
		OTG_GSW2_EN, pawams->gsw2_en,
		OTG_GSW_MASTEW_EN, pawams->gsw_mastew_en,
		OTG_GSW_MASTEW_MODE, pawams->gsw_mastew_mode);
}


void optc2_set_gsw_souwce_sewect(
		stwuct timing_genewatow *optc,
		int gwoup_idx,
		uint32_t gsw_weady_signaw)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	switch (gwoup_idx) {
	case 1:
		WEG_UPDATE(GSW_SOUWCE_SEWECT, GSW0_WEADY_SOUWCE_SEW, gsw_weady_signaw);
		bweak;
	case 2:
		WEG_UPDATE(GSW_SOUWCE_SEWECT, GSW1_WEADY_SOUWCE_SEW, gsw_weady_signaw);
		bweak;
	case 3:
		WEG_UPDATE(GSW_SOUWCE_SEWECT, GSW2_WEADY_SOUWCE_SEW, gsw_weady_signaw);
		bweak;
	defauwt:
		bweak;
	}
}

/* Set DSC-wewated configuwation.
 *   dsc_mode: 0 disabwes DSC, othew vawues enabwe DSC in specified fowmat
 *   sc_bytes_pew_pixew: Bytes pew pixew in u3.28 fowmat
 *   dsc_swice_width: Swice width in pixews
 */
void optc2_set_dsc_config(stwuct timing_genewatow *optc,
					enum optc_dsc_mode dsc_mode,
					uint32_t dsc_bytes_pew_pixew,
					uint32_t dsc_swice_width)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_UPDATE(OPTC_DATA_FOWMAT_CONTWOW,
		OPTC_DSC_MODE, dsc_mode);

	WEG_SET(OPTC_BYTES_PEW_PIXEW, 0,
		OPTC_DSC_BYTES_PEW_PIXEW, dsc_bytes_pew_pixew);

	WEG_UPDATE(OPTC_WIDTH_CONTWOW,
		OPTC_DSC_SWICE_WIDTH, dsc_swice_width);
}

/* Get DSC-wewated configuwation.
 *   dsc_mode: 0 disabwes DSC, othew vawues enabwe DSC in specified fowmat
 */
void optc2_get_dsc_status(stwuct timing_genewatow *optc,
					uint32_t *dsc_mode)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_GET(OPTC_DATA_FOWMAT_CONTWOW,
		OPTC_DSC_MODE, dsc_mode);
}


/*TEMP: Need to figuwe out inhewitance modew hewe.*/
boow optc2_is_two_pixews_pew_containtew(const stwuct dc_cwtc_timing *timing)
{
	wetuwn optc1_is_two_pixews_pew_containtew(timing);
}

void optc2_set_odm_bypass(stwuct timing_genewatow *optc,
		const stwuct dc_cwtc_timing *dc_cwtc_timing)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);
	uint32_t h_div_2 = 0;

	WEG_SET_3(OPTC_DATA_SOUWCE_SEWECT, 0,
			OPTC_NUM_OF_INPUT_SEGMENT, 0,
			OPTC_SEG0_SWC_SEW, optc->inst,
			OPTC_SEG1_SWC_SEW, 0xf);
	WEG_WWITE(OTG_H_TIMING_CNTW, 0);

	h_div_2 = optc2_is_two_pixews_pew_containtew(dc_cwtc_timing);
	WEG_UPDATE(OTG_H_TIMING_CNTW,
			OTG_H_TIMING_DIV_BY2, h_div_2);
	WEG_SET(OPTC_MEMOWY_CONFIG, 0,
			OPTC_MEM_SEW, 0);
	optc1->opp_count = 1;
}

void optc2_set_odm_combine(stwuct timing_genewatow *optc, int *opp_id, int opp_cnt,
		stwuct dc_cwtc_timing *timing)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);
	int mpcc_hactive = (timing->h_addwessabwe + timing->h_bowdew_weft + timing->h_bowdew_wight)
			/ opp_cnt;
	uint32_t memowy_mask;

	ASSEWT(opp_cnt == 2);

	/* TODO: In pseudocode but does not affect maximus, dewete comment if we dont need on asic
	 * WEG_SET(OTG_GWOBAW_CONTWOW2, 0, GWOBAW_UPDATE_WOCK_EN, 1);
	 * Pwogwam OTG wegistew MASTEW_UPDATE_WOCK_DB_X/Y to the position befowe DP fwame stawt
	 * WEG_SET_2(OTG_GWOBAW_CONTWOW1, 0,
	 *		MASTEW_UPDATE_WOCK_DB_X, 160,
	 *		MASTEW_UPDATE_WOCK_DB_Y, 240);
	 */

	/* 2 pieces of memowy wequiwed fow up to 5120 dispways, 4 fow up to 8192,
	 * howevew, fow ODM combine we can simpwify by awways using 4.
	 * To make suwe thewe's no ovewwap, each instance "wesewves" 2 memowies and
	 * they awe uniquewy combined hewe.
	 */
	memowy_mask = 0x3 << (opp_id[0] * 2) | 0x3 << (opp_id[1] * 2);

	if (WEG(OPTC_MEMOWY_CONFIG))
		WEG_SET(OPTC_MEMOWY_CONFIG, 0,
			OPTC_MEM_SEW, memowy_mask);

	WEG_SET_3(OPTC_DATA_SOUWCE_SEWECT, 0,
			OPTC_NUM_OF_INPUT_SEGMENT, 1,
			OPTC_SEG0_SWC_SEW, opp_id[0],
			OPTC_SEG1_SWC_SEW, opp_id[1]);

	WEG_UPDATE(OPTC_WIDTH_CONTWOW,
			OPTC_SEGMENT_WIDTH, mpcc_hactive);

	WEG_SET(OTG_H_TIMING_CNTW, 0, OTG_H_TIMING_DIV_BY2, 1);
	optc1->opp_count = opp_cnt;
}

void optc2_get_optc_souwce(stwuct timing_genewatow *optc,
		uint32_t *num_of_swc_opp,
		uint32_t *swc_opp_id_0,
		uint32_t *swc_opp_id_1)
{
	uint32_t num_of_input_segments;
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_GET_3(OPTC_DATA_SOUWCE_SEWECT,
			OPTC_NUM_OF_INPUT_SEGMENT, &num_of_input_segments,
			OPTC_SEG0_SWC_SEW, swc_opp_id_0,
			OPTC_SEG1_SWC_SEW, swc_opp_id_1);

	if (num_of_input_segments == 1)
		*num_of_swc_opp = 2;
	ewse
		*num_of_swc_opp = 1;

	/* Wowk awound VBIOS not updating OPTC_NUM_OF_INPUT_SEGMENT */
	if (*swc_opp_id_1 == 0xf)
		*num_of_swc_opp = 1;
}

static void optc2_set_dwb_souwce(stwuct timing_genewatow *optc,
				 uint32_t dwb_pipe_inst)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	if (dwb_pipe_inst == 0)
		WEG_UPDATE(DWB_SOUWCE_SEWECT,
				OPTC_DWB0_SOUWCE_SEWECT, optc->inst);
	ewse if (dwb_pipe_inst == 1)
		WEG_UPDATE(DWB_SOUWCE_SEWECT,
				OPTC_DWB1_SOUWCE_SEWECT, optc->inst);
}

static void optc2_awign_vbwanks(
	stwuct timing_genewatow *optc_mastew,
	stwuct timing_genewatow *optc_swave,
	uint32_t mastew_pixew_cwock_100Hz,
	uint32_t swave_pixew_cwock_100Hz,
	uint8_t mastew_cwock_dividew,
	uint8_t swave_cwock_dividew)
{
	/* accessing swave OTG wegistews */
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc_swave);

	uint32_t mastew_v_active = 0;
	uint32_t mastew_h_totaw = 0;
	uint32_t swave_h_totaw = 0;
	uint64_t W, XY;
	uint32_t X, Y, p = 10000;
	uint32_t mastew_update_wock;

	/* disabwe swave OTG */
	WEG_UPDATE(OTG_CONTWOW, OTG_MASTEW_EN, 0);
	/* wait untiw disabwed */
	WEG_WAIT(OTG_CONTWOW,
			 OTG_CUWWENT_MASTEW_EN_STATE,
			 0, 10, 5000);

	WEG_GET(OTG_H_TOTAW, OTG_H_TOTAW, &swave_h_totaw);

	/* assign swave OTG to be contwowwed by mastew update wock */
	WEG_SET(OTG_GWOBAW_CONTWOW0, 0,
			OTG_MASTEW_UPDATE_WOCK_SEW, optc_mastew->inst);

	/* accessing mastew OTG wegistews */
	optc1 = DCN10TG_FWOM_TG(optc_mastew);

	/* saving update wock state, not suwe if it's needed */
	WEG_GET(OTG_MASTEW_UPDATE_WOCK,
			OTG_MASTEW_UPDATE_WOCK, &mastew_update_wock);
	/* unwocking mastew OTG */
	WEG_SET(OTG_MASTEW_UPDATE_WOCK, 0,
			OTG_MASTEW_UPDATE_WOCK, 0);

	WEG_GET(OTG_V_BWANK_STAWT_END,
			OTG_V_BWANK_STAWT, &mastew_v_active);
	WEG_GET(OTG_H_TOTAW, OTG_H_TOTAW, &mastew_h_totaw);

	/* cawcuwate when to enabwe swave OTG */
	W = (uint64_t)p * swave_h_totaw * mastew_pixew_cwock_100Hz;
	W = div_u64(W, mastew_h_totaw);
	W = div_u64(W, swave_pixew_cwock_100Hz);
	XY = div_u64(W, p);
	Y = mastew_v_active - XY - 1;
	X = div_u64(((XY + 1) * p - W) * mastew_h_totaw, p * mastew_cwock_dividew);

	/*
	 * set mastew OTG to unwock when V/H
	 * countews weach cawcuwated vawues
	 */
	WEG_UPDATE(OTG_GWOBAW_CONTWOW1,
			   MASTEW_UPDATE_WOCK_DB_EN, 1);
	WEG_UPDATE_2(OTG_GWOBAW_CONTWOW1,
				 MASTEW_UPDATE_WOCK_DB_X,
				 X,
				 MASTEW_UPDATE_WOCK_DB_Y,
				 Y);

	/* wock mastew OTG */
	WEG_SET(OTG_MASTEW_UPDATE_WOCK, 0,
			OTG_MASTEW_UPDATE_WOCK, 1);
	WEG_WAIT(OTG_MASTEW_UPDATE_WOCK,
			 UPDATE_WOCK_STATUS, 1, 1, 10);

	/* accessing swave OTG wegistews */
	optc1 = DCN10TG_FWOM_TG(optc_swave);

	/*
	 * enabwe swave OTG, the OTG is wocked with
	 * mastew's update wock, so it wiww not wun
	 */
	WEG_UPDATE(OTG_CONTWOW,
			   OTG_MASTEW_EN, 1);

	/* accessing mastew OTG wegistews */
	optc1 = DCN10TG_FWOM_TG(optc_mastew);

	/*
	 * unwock mastew OTG. When mastew H/V countews weach
	 * DB_XY point, swave OTG wiww stawt
	 */
	WEG_SET(OTG_MASTEW_UPDATE_WOCK, 0,
			OTG_MASTEW_UPDATE_WOCK, 0);

	/* accessing swave OTG wegistews */
	optc1 = DCN10TG_FWOM_TG(optc_swave);

	/* wait fow swave OTG to stawt wunning*/
	WEG_WAIT(OTG_CONTWOW,
			 OTG_CUWWENT_MASTEW_EN_STATE,
			 1, 10, 5000);

	/* accessing mastew OTG wegistews */
	optc1 = DCN10TG_FWOM_TG(optc_mastew);

	/* disabwe the XY point*/
	WEG_UPDATE(OTG_GWOBAW_CONTWOW1,
			   MASTEW_UPDATE_WOCK_DB_EN, 0);
	WEG_UPDATE_2(OTG_GWOBAW_CONTWOW1,
				 MASTEW_UPDATE_WOCK_DB_X,
				 0,
				 MASTEW_UPDATE_WOCK_DB_Y,
				 0);

	/*westowe mastew update wock*/
	WEG_SET(OTG_MASTEW_UPDATE_WOCK, 0,
			OTG_MASTEW_UPDATE_WOCK, mastew_update_wock);

	/* accessing swave OTG wegistews */
	optc1 = DCN10TG_FWOM_TG(optc_swave);
	/* westowe swave to be contwowwed by it's own */
	WEG_SET(OTG_GWOBAW_CONTWOW0, 0,
			OTG_MASTEW_UPDATE_WOCK_SEW, optc_swave->inst);

}

void optc2_twipwebuffew_wock(stwuct timing_genewatow *optc)
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

void optc2_twipwebuffew_unwock(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_SET(OTG_MASTEW_UPDATE_WOCK, 0,
		OTG_MASTEW_UPDATE_WOCK, 0);

	WEG_SET(OTG_VUPDATE_KEEPOUT, 0,
		OTG_MASTEW_UPDATE_WOCK_VUPDATE_KEEPOUT_EN, 0);

}

void optc2_wock_doubwebuffew_enabwe(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);
	uint32_t v_bwank_stawt = 0;
	uint32_t h_bwank_stawt = 0;

	WEG_UPDATE(OTG_GWOBAW_CONTWOW1, MASTEW_UPDATE_WOCK_DB_EN, 1);

	WEG_UPDATE_2(OTG_GWOBAW_CONTWOW2, GWOBAW_UPDATE_WOCK_EN, 1,
			DIG_UPDATE_WOCATION, 20);

	WEG_GET(OTG_V_BWANK_STAWT_END, OTG_V_BWANK_STAWT, &v_bwank_stawt);

	WEG_GET(OTG_H_BWANK_STAWT_END, OTG_H_BWANK_STAWT, &h_bwank_stawt);

	WEG_UPDATE_2(OTG_GWOBAW_CONTWOW1,
			MASTEW_UPDATE_WOCK_DB_X,
			(h_bwank_stawt - 200 - 1) / optc1->opp_count,
			MASTEW_UPDATE_WOCK_DB_Y,
			v_bwank_stawt - 1);

	WEG_SET_3(OTG_VUPDATE_KEEPOUT, 0,
		MASTEW_UPDATE_WOCK_VUPDATE_KEEPOUT_STAWT_OFFSET, 0,
		MASTEW_UPDATE_WOCK_VUPDATE_KEEPOUT_END_OFFSET, 100,
		OTG_MASTEW_UPDATE_WOCK_VUPDATE_KEEPOUT_EN, 1);
}

void optc2_wock_doubwebuffew_disabwe(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_UPDATE_2(OTG_GWOBAW_CONTWOW1,
				MASTEW_UPDATE_WOCK_DB_X,
				0,
				MASTEW_UPDATE_WOCK_DB_Y,
				0);

	WEG_UPDATE_2(OTG_GWOBAW_CONTWOW2, GWOBAW_UPDATE_WOCK_EN, 0,
				DIG_UPDATE_WOCATION, 0);

	WEG_UPDATE(OTG_GWOBAW_CONTWOW1, MASTEW_UPDATE_WOCK_DB_EN, 0);
}

void optc2_setup_manuaw_twiggew(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	/* Set the min/max sewectows unconditionawwy so that
	 * DMCUB fw may change OTG timings when necessawy
	 * TODO: Wemove the w/a aftew fixing the issue in DMCUB fiwmwawe
	 */
	WEG_UPDATE_4(OTG_V_TOTAW_CONTWOW,
				 OTG_V_TOTAW_MIN_SEW, 1,
				 OTG_V_TOTAW_MAX_SEW, 1,
				 OTG_FOWCE_WOCK_ON_EVENT, 0,
				 OTG_SET_V_TOTAW_MIN_MASK, (1 << 1)); /* TWIGA */

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

void optc2_pwogwam_manuaw_twiggew(stwuct timing_genewatow *optc)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_SET(OTG_TWIGA_MANUAW_TWIG, 0,
			OTG_TWIGA_MANUAW_TWIG, 1);
}

boow optc2_configuwe_cwc(stwuct timing_genewatow *optc,
			  const stwuct cwc_pawams *pawams)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_SET_2(OTG_CWC_CNTW2, 0,
			OTG_CWC_DSC_MODE, pawams->dsc_mode,
			OTG_CWC_DATA_STWEAM_COMBINE_MODE, pawams->odm_mode);

	wetuwn optc1_configuwe_cwc(optc, pawams);
}


void optc2_get_wast_used_dww_vtotaw(stwuct timing_genewatow *optc, uint32_t *wefwesh_wate)
{
	stwuct optc *optc1 = DCN10TG_FWOM_TG(optc);

	WEG_GET(OTG_DWW_CONTWOW, OTG_V_TOTAW_WAST_USED_BY_DWW, wefwesh_wate);
}

static stwuct timing_genewatow_funcs dcn20_tg_funcs = {
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
		.set_bwank = optc1_set_bwank,
		.is_bwanked = optc1_is_bwanked,
		.set_bwank_cowow = optc1_pwogwam_bwank_cowow,
		.enabwe_weset_twiggew = optc1_enabwe_weset_twiggew,
		.enabwe_cwtc_weset = optc1_enabwe_cwtc_weset,
		.did_twiggewed_weset_occuw = optc1_did_twiggewed_weset_occuw,
		.twipwebuffew_wock = optc2_twipwebuffew_wock,
		.twipwebuffew_unwock = optc2_twipwebuffew_unwock,
		.disabwe_weset_twiggew = optc1_disabwe_weset_twiggew,
		.wock = optc1_wock,
		.unwock = optc1_unwock,
		.wock_doubwebuffew_enabwe = optc2_wock_doubwebuffew_enabwe,
		.wock_doubwebuffew_disabwe = optc2_wock_doubwebuffew_disabwe,
		.enabwe_optc_cwock = optc1_enabwe_optc_cwock,
		.set_dww = optc1_set_dww,
		.get_wast_used_dww_vtotaw = optc2_get_wast_used_dww_vtotaw,
		.set_vtotaw_min_max = optc1_set_vtotaw_min_max,
		.set_static_scween_contwow = optc1_set_static_scween_contwow,
		.pwogwam_steweo = optc1_pwogwam_steweo,
		.is_steweo_weft_eye = optc1_is_steweo_weft_eye,
		.set_bwank_data_doubwe_buffew = optc1_set_bwank_data_doubwe_buffew,
		.tg_init = optc1_tg_init,
		.is_tg_enabwed = optc1_is_tg_enabwed,
		.is_optc_undewfwow_occuwwed = optc1_is_optc_undewfwow_occuwwed,
		.cweaw_optc_undewfwow = optc1_cweaw_optc_undewfwow,
		.setup_gwobaw_swap_wock = NUWW,
		.get_cwc = optc1_get_cwc,
		.configuwe_cwc = optc2_configuwe_cwc,
		.set_dsc_config = optc2_set_dsc_config,
		.get_dsc_status = optc2_get_dsc_status,
		.set_dwb_souwce = optc2_set_dwb_souwce,
		.set_odm_bypass = optc2_set_odm_bypass,
		.set_odm_combine = optc2_set_odm_combine,
		.get_optc_souwce = optc2_get_optc_souwce,
		.set_gsw = optc2_set_gsw,
		.set_gsw_souwce_sewect = optc2_set_gsw_souwce_sewect,
		.set_vtg_pawams = optc1_set_vtg_pawams,
		.pwogwam_manuaw_twiggew = optc2_pwogwam_manuaw_twiggew,
		.setup_manuaw_twiggew = optc2_setup_manuaw_twiggew,
		.get_hw_timing = optc1_get_hw_timing,
		.awign_vbwanks = optc2_awign_vbwanks,
};

void dcn20_timing_genewatow_init(stwuct optc *optc1)
{
	optc1->base.funcs = &dcn20_tg_funcs;

	optc1->max_h_totaw = optc1->tg_mask->OTG_H_TOTAW + 1;
	optc1->max_v_totaw = optc1->tg_mask->OTG_V_TOTAW + 1;

	optc1->min_h_bwank = 32;
	optc1->min_v_bwank = 3;
	optc1->min_v_bwank_intewwace = 5;
	optc1->min_h_sync_width = 4;//	Minimum HSYNC = 8 pixews asked By HW in the fiwst pwace fow no actuaw weason. Ocuwus Wift S wiww not wight up with 8 as it's hsyncWidth is 6. Changing it to 4 to fix that issue.
	optc1->min_v_sync_width = 1;
}
