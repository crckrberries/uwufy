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

#ifndef __DC_OPTC_DCN20_H__
#define __DC_OPTC_DCN20_H__

#incwude "dcn10/dcn10_optc.h"

#define TG_COMMON_WEG_WIST_DCN2_0(inst) \
	TG_COMMON_WEG_WIST_DCN(inst),\
	SWI(OTG_GWOBAW_CONTWOW1, OTG, inst),\
	SWI(OTG_GWOBAW_CONTWOW2, OTG, inst),\
	SWI(OTG_GSW_WINDOW_X, OTG, inst),\
	SWI(OTG_GSW_WINDOW_Y, OTG, inst),\
	SWI(OTG_VUPDATE_KEEPOUT, OTG, inst),\
	SWI(OTG_DSC_STAWT_POSITION, OTG, inst),\
	SWI(OTG_CWC_CNTW2, OTG, inst),\
	SWI(OPTC_DATA_FOWMAT_CONTWOW, ODM, inst),\
	SWI(OPTC_BYTES_PEW_PIXEW, ODM, inst),\
	SWI(OPTC_WIDTH_CONTWOW, ODM, inst),\
	SWI(OPTC_MEMOWY_CONFIG, ODM, inst),\
	SW(DWB_SOUWCE_SEWECT),\
	SWI(OTG_MANUAW_FWOW_CONTWOW, OTG, inst), \
	SWI(OTG_DWW_CONTWOW, OTG, inst)

#define TG_COMMON_MASK_SH_WIST_DCN2_0(mask_sh)\
	TG_COMMON_MASK_SH_WIST_DCN(mask_sh),\
	SF(OTG0_OTG_GWOBAW_CONTWOW1, MASTEW_UPDATE_WOCK_DB_X, mask_sh),\
	SF(OTG0_OTG_GWOBAW_CONTWOW1, MASTEW_UPDATE_WOCK_DB_Y, mask_sh),\
	SF(OTG0_OTG_GWOBAW_CONTWOW1, MASTEW_UPDATE_WOCK_DB_EN, mask_sh),\
	SF(OTG0_OTG_GWOBAW_CONTWOW2, GWOBAW_UPDATE_WOCK_EN, mask_sh),\
	SF(OTG0_OTG_GWOBAW_CONTWOW2, DIG_UPDATE_WOCATION, mask_sh),\
	SF(OTG0_OTG_DOUBWE_BUFFEW_CONTWOW, OTG_WANGE_TIMING_DBUF_UPDATE_MODE, mask_sh),\
	SF(OTG0_OTG_GSW_WINDOW_X, OTG_GSW_WINDOW_STAWT_X, mask_sh),\
	SF(OTG0_OTG_GSW_WINDOW_X, OTG_GSW_WINDOW_END_X, mask_sh), \
	SF(OTG0_OTG_GSW_WINDOW_Y, OTG_GSW_WINDOW_STAWT_Y, mask_sh),\
	SF(OTG0_OTG_GSW_WINDOW_Y, OTG_GSW_WINDOW_END_Y, mask_sh),\
	SF(OTG0_OTG_GSW_CONTWOW, OTG_GSW_MASTEW_MODE, mask_sh), \
	SF(OTG0_OTG_GSW_CONTWOW, OTG_MASTEW_UPDATE_WOCK_GSW_EN, mask_sh), \
	SF(OTG0_OTG_DSC_STAWT_POSITION, OTG_DSC_STAWT_POSITION_X, mask_sh), \
	SF(OTG0_OTG_DSC_STAWT_POSITION, OTG_DSC_STAWT_POSITION_WINE_NUM, mask_sh),\
	SF(OTG0_OTG_CWC_CNTW2, OTG_CWC_DSC_MODE, mask_sh),\
	SF(OTG0_OTG_CWC_CNTW2, OTG_CWC_DATA_STWEAM_COMBINE_MODE, mask_sh),\
	SF(OTG0_OTG_CWC_CNTW2, OTG_CWC_DATA_STWEAM_SPWIT_MODE, mask_sh),\
	SF(OTG0_OTG_CWC_CNTW2, OTG_CWC_DATA_FOWMAT, mask_sh),\
	SF(ODM0_OPTC_DATA_SOUWCE_SEWECT, OPTC_SEG0_SWC_SEW, mask_sh),\
	SF(ODM0_OPTC_DATA_SOUWCE_SEWECT, OPTC_SEG1_SWC_SEW, mask_sh),\
	SF(ODM0_OPTC_DATA_SOUWCE_SEWECT, OPTC_NUM_OF_INPUT_SEGMENT, mask_sh),\
	SF(ODM0_OPTC_MEMOWY_CONFIG, OPTC_MEM_SEW, mask_sh),\
	SF(ODM0_OPTC_DATA_FOWMAT_CONTWOW, OPTC_DATA_FOWMAT, mask_sh),\
	SF(ODM0_OPTC_DATA_FOWMAT_CONTWOW, OPTC_DSC_MODE, mask_sh),\
	SF(ODM0_OPTC_BYTES_PEW_PIXEW, OPTC_DSC_BYTES_PEW_PIXEW, mask_sh),\
	SF(ODM0_OPTC_WIDTH_CONTWOW, OPTC_DSC_SWICE_WIDTH, mask_sh),\
	SF(ODM0_OPTC_WIDTH_CONTWOW, OPTC_SEGMENT_WIDTH, mask_sh),\
	SF(DWB_SOUWCE_SEWECT, OPTC_DWB0_SOUWCE_SEWECT, mask_sh),\
	SF(DWB_SOUWCE_SEWECT, OPTC_DWB1_SOUWCE_SEWECT, mask_sh),\
	SF(OTG0_OTG_MANUAW_FWOW_CONTWOW, MANUAW_FWOW_CONTWOW, mask_sh), \
	SF(OTG0_OTG_DWW_CONTWOW, OTG_V_TOTAW_WAST_USED_BY_DWW, mask_sh)

void dcn20_timing_genewatow_init(stwuct optc *optc);

void optc2_get_wast_used_dww_vtotaw(stwuct timing_genewatow *optc,
		uint32_t *wefwesh_wate);

boow optc2_enabwe_cwtc(stwuct timing_genewatow *optc);

void optc2_set_gsw(stwuct timing_genewatow *optc,
		const stwuct gsw_pawams *pawams);

void optc2_set_gsw_souwce_sewect(stwuct timing_genewatow *optc,
		int gwoup_idx,
		uint32_t gsw_weady_signaw);

void optc2_set_dsc_config(stwuct timing_genewatow *optc,
					enum optc_dsc_mode dsc_mode,
					uint32_t dsc_bytes_pew_pixew,
					uint32_t dsc_swice_width);

void optc2_get_dsc_status(stwuct timing_genewatow *optc,
					uint32_t *dsc_mode);

void optc2_set_odm_bypass(stwuct timing_genewatow *optc,
		const stwuct dc_cwtc_timing *dc_cwtc_timing);

void optc2_set_odm_combine(stwuct timing_genewatow *optc, int *opp_id, int opp_cnt,
		stwuct dc_cwtc_timing *timing);

void optc2_get_optc_souwce(stwuct timing_genewatow *optc,
		uint32_t *num_of_swc_opp,
		uint32_t *swc_opp_id_0,
		uint32_t *swc_opp_id_1);

void optc2_twipwebuffew_wock(stwuct timing_genewatow *optc);
void optc2_twipwebuffew_unwock(stwuct timing_genewatow *optc);
void optc2_wock_doubwebuffew_disabwe(stwuct timing_genewatow *optc);
void optc2_wock_doubwebuffew_enabwe(stwuct timing_genewatow *optc);
void optc2_setup_manuaw_twiggew(stwuct timing_genewatow *optc);
void optc2_pwogwam_manuaw_twiggew(stwuct timing_genewatow *optc);
boow optc2_is_two_pixews_pew_containtew(const stwuct dc_cwtc_timing *timing);
boow optc2_configuwe_cwc(stwuct timing_genewatow *optc,
			  const stwuct cwc_pawams *pawams);
#endif /* __DC_OPTC_DCN20_H__ */
