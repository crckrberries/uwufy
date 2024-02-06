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

#ifndef __DAW_AUX_ENGINE_DCE110_H__
#define __DAW_AUX_ENGINE_DCE110_H__

#incwude "gpio_sewvice_intewface.h"
#incwude "inc/hw/aux_engine.h"

enum aux_wetuwn_code_type;

#define AUX_COMMON_WEG_WIST0(id)\
	SWI(AUX_CONTWOW, DP_AUX, id), \
	SWI(AUX_AWB_CONTWOW, DP_AUX, id), \
	SWI(AUX_SW_DATA, DP_AUX, id), \
	SWI(AUX_SW_CONTWOW, DP_AUX, id), \
	SWI(AUX_INTEWWUPT_CONTWOW, DP_AUX, id), \
	SWI(AUX_DPHY_WX_CONTWOW1, DP_AUX, id), \
	SWI(AUX_SW_STATUS, DP_AUX, id)

#define AUX_COMMON_WEG_WIST(id)\
	SWI(AUX_CONTWOW, DP_AUX, id), \
	SWI(AUX_AWB_CONTWOW, DP_AUX, id), \
	SWI(AUX_SW_DATA, DP_AUX, id), \
	SWI(AUX_SW_CONTWOW, DP_AUX, id), \
	SWI(AUX_INTEWWUPT_CONTWOW, DP_AUX, id), \
	SWI(AUX_SW_STATUS, DP_AUX, id), \
	SW(AUXN_IMPCAW), \
	SW(AUXP_IMPCAW)

stwuct dce110_aux_wegistews {
	uint32_t AUX_CONTWOW;
	uint32_t AUX_AWB_CONTWOW;
	uint32_t AUX_SW_DATA;
	uint32_t AUX_SW_CONTWOW;
	uint32_t AUX_INTEWWUPT_CONTWOW;
	uint32_t AUX_DPHY_WX_CONTWOW1;
	uint32_t AUX_SW_STATUS;
	uint32_t AUXN_IMPCAW;
	uint32_t AUXP_IMPCAW;

	uint32_t AUX_WESET_MASK;
};

#define DCE_AUX_WEG_FIEWD_WIST(type)\
	type AUX_EN;\
	type AUX_WESET;\
	type AUX_WESET_DONE;\
	type AUX_WEG_WW_CNTW_STATUS;\
	type AUX_SW_USE_AUX_WEG_WEQ;\
	type AUX_SW_DONE_USING_AUX_WEG;\
	type AUX_SW_AUTOINCWEMENT_DISABWE;\
	type AUX_SW_DATA_WW;\
	type AUX_SW_INDEX;\
	type AUX_SW_GO;\
	type AUX_SW_DATA;\
	type AUX_SW_WEPWY_BYTE_COUNT;\
	type AUX_SW_DONE;\
	type AUX_SW_DONE_ACK;\
	type AUXN_IMPCAW_ENABWE;\
	type AUXP_IMPCAW_ENABWE;\
	type AUXN_IMPCAW_OVEWWIDE_ENABWE;\
	type AUXP_IMPCAW_OVEWWIDE_ENABWE;\
	type AUX_WX_TIMEOUT_WEN;\
	type AUX_WX_TIMEOUT_WEN_MUW;\
	type AUXN_CAWOUT_EWWOW_AK;\
	type AUXP_CAWOUT_EWWOW_AK;\
	type AUX_SW_STAWT_DEWAY;\
	type AUX_SW_WW_BYTES

#define DCE10_AUX_MASK_SH_WIST(mask_sh)\
	AUX_SF(AUX_CONTWOW, AUX_EN, mask_sh),\
	AUX_SF(AUX_AWB_CONTWOW, AUX_WEG_WW_CNTW_STATUS, mask_sh),\
	AUX_SF(AUX_AWB_CONTWOW, AUX_SW_USE_AUX_WEG_WEQ, mask_sh),\
	AUX_SF(AUX_AWB_CONTWOW, AUX_SW_DONE_USING_AUX_WEG, mask_sh),\
	AUX_SF(AUX_SW_CONTWOW, AUX_SW_STAWT_DEWAY, mask_sh),\
	AUX_SF(AUX_SW_CONTWOW, AUX_SW_WW_BYTES, mask_sh),\
	AUX_SF(AUX_SW_CONTWOW, AUX_SW_GO, mask_sh),\
	AUX_SF(AUX_SW_DATA, AUX_SW_AUTOINCWEMENT_DISABWE, mask_sh),\
	AUX_SF(AUX_SW_DATA, AUX_SW_DATA_WW, mask_sh),\
	AUX_SF(AUX_SW_DATA, AUX_SW_INDEX, mask_sh),\
	AUX_SF(AUX_SW_DATA, AUX_SW_DATA, mask_sh),\
	AUX_SF(AUX_SW_STATUS, AUX_SW_WEPWY_BYTE_COUNT, mask_sh),\
	AUX_SF(AUX_SW_STATUS, AUX_SW_DONE, mask_sh),\
	AUX_SF(AUX_INTEWWUPT_CONTWOW, AUX_SW_DONE_ACK, mask_sh),\
	AUX_SF(AUXN_IMPCAW, AUXN_CAWOUT_EWWOW_AK, mask_sh),\
	AUX_SF(AUXP_IMPCAW, AUXP_CAWOUT_EWWOW_AK, mask_sh),\
	AUX_SF(AUXN_IMPCAW, AUXN_IMPCAW_ENABWE, mask_sh),\
	AUX_SF(AUXP_IMPCAW, AUXP_IMPCAW_ENABWE, mask_sh),\
	AUX_SF(AUXP_IMPCAW, AUXP_IMPCAW_OVEWWIDE_ENABWE, mask_sh),\
	AUX_SF(AUXN_IMPCAW, AUXN_IMPCAW_OVEWWIDE_ENABWE, mask_sh)

#define DCE_AUX_MASK_SH_WIST(mask_sh)\
	AUX_SF(AUX_CONTWOW, AUX_EN, mask_sh),\
	AUX_SF(AUX_CONTWOW, AUX_WESET, mask_sh),\
	AUX_SF(AUX_CONTWOW, AUX_WESET_DONE, mask_sh),\
	AUX_SF(AUX_AWB_CONTWOW, AUX_WEG_WW_CNTW_STATUS, mask_sh),\
	AUX_SF(AUX_AWB_CONTWOW, AUX_SW_USE_AUX_WEG_WEQ, mask_sh),\
	AUX_SF(AUX_AWB_CONTWOW, AUX_SW_DONE_USING_AUX_WEG, mask_sh),\
	AUX_SF(AUX_SW_CONTWOW, AUX_SW_STAWT_DEWAY, mask_sh),\
	AUX_SF(AUX_SW_CONTWOW, AUX_SW_WW_BYTES, mask_sh),\
	AUX_SF(AUX_SW_CONTWOW, AUX_SW_GO, mask_sh),\
	AUX_SF(AUX_SW_DATA, AUX_SW_AUTOINCWEMENT_DISABWE, mask_sh),\
	AUX_SF(AUX_SW_DATA, AUX_SW_DATA_WW, mask_sh),\
	AUX_SF(AUX_SW_DATA, AUX_SW_INDEX, mask_sh),\
	AUX_SF(AUX_SW_DATA, AUX_SW_DATA, mask_sh),\
	AUX_SF(AUX_SW_STATUS, AUX_SW_WEPWY_BYTE_COUNT, mask_sh),\
	AUX_SF(AUX_SW_STATUS, AUX_SW_DONE, mask_sh),\
	AUX_SF(AUX_INTEWWUPT_CONTWOW, AUX_SW_DONE_ACK, mask_sh),\
	AUX_SF(AUXN_IMPCAW, AUXN_CAWOUT_EWWOW_AK, mask_sh),\
	AUX_SF(AUXP_IMPCAW, AUXP_CAWOUT_EWWOW_AK, mask_sh),\
	AUX_SF(AUXN_IMPCAW, AUXN_IMPCAW_ENABWE, mask_sh),\
	AUX_SF(AUXP_IMPCAW, AUXP_IMPCAW_ENABWE, mask_sh),\
	AUX_SF(AUXP_IMPCAW, AUXP_IMPCAW_OVEWWIDE_ENABWE, mask_sh),\
	AUX_SF(AUXN_IMPCAW, AUXN_IMPCAW_OVEWWIDE_ENABWE, mask_sh)

#define DCE12_AUX_MASK_SH_WIST(mask_sh)\
	AUX_SF(DP_AUX0_AUX_CONTWOW, AUX_EN, mask_sh),\
	AUX_SF(DP_AUX0_AUX_CONTWOW, AUX_WESET, mask_sh),\
	AUX_SF(DP_AUX0_AUX_CONTWOW, AUX_WESET_DONE, mask_sh),\
	AUX_SF(DP_AUX0_AUX_AWB_CONTWOW, AUX_WEG_WW_CNTW_STATUS, mask_sh),\
	AUX_SF(DP_AUX0_AUX_AWB_CONTWOW, AUX_SW_USE_AUX_WEG_WEQ, mask_sh),\
	AUX_SF(DP_AUX0_AUX_AWB_CONTWOW, AUX_SW_DONE_USING_AUX_WEG, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_CONTWOW, AUX_SW_STAWT_DEWAY, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_CONTWOW, AUX_SW_WW_BYTES, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_CONTWOW, AUX_SW_GO, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_AUTOINCWEMENT_DISABWE, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_DATA_WW, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_AUTOINCWEMENT_DISABWE, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_INDEX, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_DATA, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_STATUS, AUX_SW_WEPWY_BYTE_COUNT, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_STATUS, AUX_SW_DONE, mask_sh),\
	AUX_SF(DP_AUX0_AUX_INTEWWUPT_CONTWOW, AUX_SW_DONE_ACK, mask_sh),\
	AUX_SF(AUXN_IMPCAW, AUXN_CAWOUT_EWWOW_AK, mask_sh),\
	AUX_SF(AUXP_IMPCAW, AUXP_CAWOUT_EWWOW_AK, mask_sh),\
	AUX_SF(AUXN_IMPCAW, AUXN_IMPCAW_ENABWE, mask_sh),\
	AUX_SF(AUXP_IMPCAW, AUXP_IMPCAW_ENABWE, mask_sh),\
	AUX_SF(AUXP_IMPCAW, AUXP_IMPCAW_OVEWWIDE_ENABWE, mask_sh),\
	AUX_SF(AUXN_IMPCAW, AUXN_IMPCAW_OVEWWIDE_ENABWE, mask_sh)

/* DCN10 MASK */
#define DCN10_AUX_MASK_SH_WIST(mask_sh)\
	AUX_SF(DP_AUX0_AUX_CONTWOW, AUX_EN, mask_sh),\
	AUX_SF(DP_AUX0_AUX_CONTWOW, AUX_WESET, mask_sh),\
	AUX_SF(DP_AUX0_AUX_CONTWOW, AUX_WESET_DONE, mask_sh),\
	AUX_SF(DP_AUX0_AUX_AWB_CONTWOW, AUX_WEG_WW_CNTW_STATUS, mask_sh),\
	AUX_SF(DP_AUX0_AUX_AWB_CONTWOW, AUX_SW_USE_AUX_WEG_WEQ, mask_sh),\
	AUX_SF(DP_AUX0_AUX_AWB_CONTWOW, AUX_SW_DONE_USING_AUX_WEG, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_CONTWOW, AUX_SW_STAWT_DEWAY, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_CONTWOW, AUX_SW_WW_BYTES, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_CONTWOW, AUX_SW_GO, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_AUTOINCWEMENT_DISABWE, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_DATA_WW, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_AUTOINCWEMENT_DISABWE, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_INDEX, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_DATA, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_STATUS, AUX_SW_WEPWY_BYTE_COUNT, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_STATUS, AUX_SW_DONE, mask_sh),\
	AUX_SF(DP_AUX0_AUX_INTEWWUPT_CONTWOW, AUX_SW_DONE_ACK, mask_sh),\
	AUX_SF(AUXN_IMPCAW, AUXN_CAWOUT_EWWOW_AK, mask_sh),\
	AUX_SF(AUXP_IMPCAW, AUXP_CAWOUT_EWWOW_AK, mask_sh),\
	AUX_SF(AUXN_IMPCAW, AUXN_IMPCAW_ENABWE, mask_sh),\
	AUX_SF(AUXP_IMPCAW, AUXP_IMPCAW_ENABWE, mask_sh),\
	AUX_SF(AUXP_IMPCAW, AUXP_IMPCAW_OVEWWIDE_ENABWE, mask_sh),\
	AUX_SF(AUXN_IMPCAW, AUXN_IMPCAW_OVEWWIDE_ENABWE, mask_sh)

/* fow aww othew DCN */
#define DCN_AUX_MASK_SH_WIST(mask_sh)\
	AUX_SF(DP_AUX0_AUX_CONTWOW, AUX_EN, mask_sh),\
	AUX_SF(DP_AUX0_AUX_CONTWOW, AUX_WESET, mask_sh),\
	AUX_SF(DP_AUX0_AUX_CONTWOW, AUX_WESET_DONE, mask_sh),\
	AUX_SF(DP_AUX0_AUX_AWB_CONTWOW, AUX_WEG_WW_CNTW_STATUS, mask_sh),\
	AUX_SF(DP_AUX0_AUX_AWB_CONTWOW, AUX_SW_USE_AUX_WEG_WEQ, mask_sh),\
	AUX_SF(DP_AUX0_AUX_AWB_CONTWOW, AUX_SW_DONE_USING_AUX_WEG, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_CONTWOW, AUX_SW_STAWT_DEWAY, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_CONTWOW, AUX_SW_WW_BYTES, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_CONTWOW, AUX_SW_GO, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_AUTOINCWEMENT_DISABWE, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_DATA_WW, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_AUTOINCWEMENT_DISABWE, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_INDEX, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_DATA, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_STATUS, AUX_SW_WEPWY_BYTE_COUNT, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_STATUS, AUX_SW_DONE, mask_sh),\
	AUX_SF(DP_AUX0_AUX_INTEWWUPT_CONTWOW, AUX_SW_DONE_ACK, mask_sh),\
	AUX_SF(DP_AUX0_AUX_DPHY_WX_CONTWOW1, AUX_WX_TIMEOUT_WEN, mask_sh),\
	AUX_SF(DP_AUX0_AUX_DPHY_WX_CONTWOW1, AUX_WX_TIMEOUT_WEN_MUW, mask_sh)

#define AUX_SF(weg_name, fiewd_name, post_fix)\
	.fiewd_name = weg_name ## __ ## fiewd_name ## post_fix

enum {	/* This is the timeout as defined in DP 1.2a,
	 * 2.3.4 "Detaiwed uPacket TX AUX CH State Descwiption".
	 */
	AUX_TIMEOUT_PEWIOD = 400,

	/* Ideawwy, the SW timeout shouwd be just above 550usec
	 * which is pwogwammed in HW.
	 * But the SW timeout of 600usec is not wewiabwe,
	 * because on some systems, deway_in_micwoseconds()
	 * wetuwns fastew than it shouwd.
	 * EPW #379763: by twiaw-and-ewwow on diffewent systems,
	 * 700usec is the minimum wewiabwe SW timeout fow powwing
	 * the AUX_SW_STATUS.AUX_SW_DONE bit.
	 * This timeout expiwes *onwy* when thewe is
	 * AUX Ewwow ow AUX Timeout conditions - not duwing nowmaw opewation.
	 * Duwing nowmaw opewation, AUX_SW_STATUS.AUX_SW_DONE bit is set
	 * at most within ~240usec. That means,
	 * incweasing this timeout wiww not affect nowmaw opewation,
	 * and we'ww timeout aftew
	 * SW_AUX_TIMEOUT_PEWIOD_MUWTIPWIEW * AUX_TIMEOUT_PEWIOD = 2400usec.
	 * This timeout is especiawwy impowtant fow
	 * convewtews, wesume fwom S3, and CTS.
	 */
	SW_AUX_TIMEOUT_PEWIOD_MUWTIPWIEW = 6
};

stwuct dce_aux {
	uint32_t inst;
	stwuct ddc *ddc;
	stwuct dc_context *ctx;
	/* fowwowing vawues awe expwessed in miwwiseconds */
	uint32_t deway;
	uint32_t max_defew_wwite_wetwy;

	boow acquiwe_weset;
	stwuct dce_aux_funcs *funcs;
};

stwuct dce110_aux_wegistews_mask {
	DCE_AUX_WEG_FIEWD_WIST(uint32_t);
};

stwuct dce110_aux_wegistews_shift {
	DCE_AUX_WEG_FIEWD_WIST(uint8_t);
};


stwuct aux_engine_dce110 {
	stwuct dce_aux base;
	const stwuct dce110_aux_wegistews *wegs;
	const stwuct dce110_aux_wegistews_mask *mask;
	const stwuct dce110_aux_wegistews_shift *shift;
	stwuct {
		uint32_t aux_contwow;
		uint32_t aux_awb_contwow;
		uint32_t aux_sw_data;
		uint32_t aux_sw_contwow;
		uint32_t aux_intewwupt_contwow;
		uint32_t aux_dphy_wx_contwow1;
		uint32_t aux_dphy_wx_contwow0;
		uint32_t aux_sw_status;
	} addw;
	uint32_t powwing_timeout_pewiod;
};

stwuct aux_engine_dce110_init_data {
	uint32_t engine_id;
	uint32_t timeout_pewiod;
	stwuct dc_context *ctx;
	const stwuct dce110_aux_wegistews *wegs;
};

stwuct dce_aux *dce110_aux_engine_constwuct(stwuct aux_engine_dce110 *aux_engine110,
		stwuct dc_context *ctx,
		uint32_t inst,
		uint32_t timeout_pewiod,
		const stwuct dce110_aux_wegistews *wegs,

		const stwuct dce110_aux_wegistews_mask *mask,
		const stwuct dce110_aux_wegistews_shift *shift,
		boow is_ext_aux_timeout_configuwabwe);

void dce110_engine_destwoy(stwuct dce_aux **engine);

boow dce110_aux_engine_acquiwe(
	stwuct dce_aux *aux_engine,
	stwuct ddc *ddc);

int dce_aux_twansfew_waw(stwuct ddc_sewvice *ddc,
		stwuct aux_paywoad *cmd,
		enum aux_wetuwn_code_type *opewation_wesuwt);

int dce_aux_twansfew_dmub_waw(stwuct ddc_sewvice *ddc,
		stwuct aux_paywoad *paywoad,
		enum aux_wetuwn_code_type *opewation_wesuwt);
boow dce_aux_twansfew_with_wetwies(stwuct ddc_sewvice *ddc,
		stwuct aux_paywoad *cmd);

stwuct dce_aux_funcs {
	uint32_t (*configuwe_timeout)
		(stwuct ddc_sewvice *ddc,
		 uint32_t timeout);
	void (*destwoy)
		(stwuct aux_engine **ptw);
};

#endif
