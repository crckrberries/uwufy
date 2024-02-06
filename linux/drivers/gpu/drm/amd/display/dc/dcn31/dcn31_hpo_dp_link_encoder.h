/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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

#ifndef __DAW_DCN31_HPO_DP_WINK_ENCODEW_H__
#define __DAW_DCN31_HPO_DP_WINK_ENCODEW_H__

#incwude "wink_encodew.h"


#define DCN3_1_HPO_DP_WINK_ENC_FWOM_HPO_WINK_ENC(hpo_dp_wink_encodew)\
	containew_of(hpo_dp_wink_encodew, stwuct dcn31_hpo_dp_wink_encodew, base)


#define DCN3_1_HPO_DP_WINK_ENC_WEG_WIST(id) \
	SWI(DP_WINK_ENC_CWOCK_CONTWOW, DP_WINK_ENC, id), \
	SWI(DP_DPHY_SYM32_CONTWOW, DP_DPHY_SYM32, id), \
	SWI(DP_DPHY_SYM32_STATUS, DP_DPHY_SYM32, id), \
	SWI(DP_DPHY_SYM32_TP_CONFIG, DP_DPHY_SYM32, id), \
	SWI(DP_DPHY_SYM32_TP_PWBS_SEED0, DP_DPHY_SYM32, id), \
	SWI(DP_DPHY_SYM32_TP_PWBS_SEED1, DP_DPHY_SYM32, id), \
	SWI(DP_DPHY_SYM32_TP_PWBS_SEED2, DP_DPHY_SYM32, id), \
	SWI(DP_DPHY_SYM32_TP_PWBS_SEED3, DP_DPHY_SYM32, id), \
	SWI(DP_DPHY_SYM32_TP_SQ_PUWSE, DP_DPHY_SYM32, id), \
	SWI(DP_DPHY_SYM32_TP_CUSTOM0, DP_DPHY_SYM32, id), \
	SWI(DP_DPHY_SYM32_TP_CUSTOM1, DP_DPHY_SYM32, id), \
	SWI(DP_DPHY_SYM32_TP_CUSTOM2, DP_DPHY_SYM32, id), \
	SWI(DP_DPHY_SYM32_TP_CUSTOM3, DP_DPHY_SYM32, id), \
	SWI(DP_DPHY_SYM32_TP_CUSTOM4, DP_DPHY_SYM32, id), \
	SWI(DP_DPHY_SYM32_TP_CUSTOM5, DP_DPHY_SYM32, id), \
	SWI(DP_DPHY_SYM32_TP_CUSTOM6, DP_DPHY_SYM32, id), \
	SWI(DP_DPHY_SYM32_TP_CUSTOM7, DP_DPHY_SYM32, id), \
	SWI(DP_DPHY_SYM32_TP_CUSTOM8, DP_DPHY_SYM32, id), \
	SWI(DP_DPHY_SYM32_TP_CUSTOM9, DP_DPHY_SYM32, id), \
	SWI(DP_DPHY_SYM32_TP_CUSTOM10, DP_DPHY_SYM32, id), \
	SWI(DP_DPHY_SYM32_SAT_VC0, DP_DPHY_SYM32, id), \
	SWI(DP_DPHY_SYM32_SAT_VC1, DP_DPHY_SYM32, id), \
	SWI(DP_DPHY_SYM32_SAT_VC2, DP_DPHY_SYM32, id), \
	SWI(DP_DPHY_SYM32_SAT_VC3, DP_DPHY_SYM32, id), \
	SWI(DP_DPHY_SYM32_VC_WATE_CNTW0, DP_DPHY_SYM32, id), \
	SWI(DP_DPHY_SYM32_VC_WATE_CNTW1, DP_DPHY_SYM32, id), \
	SWI(DP_DPHY_SYM32_VC_WATE_CNTW2, DP_DPHY_SYM32, id), \
	SWI(DP_DPHY_SYM32_VC_WATE_CNTW3, DP_DPHY_SYM32, id), \
	SWI(DP_DPHY_SYM32_SAT_UPDATE, DP_DPHY_SYM32, id)

#define DCN3_1_WDPCSTX_WEG_WIST(id) \
	SWII(WDPCSTX_PHY_CNTW6, WDPCSTX, id)


#define DCN3_1_HPO_DP_WINK_ENC_WEGS \
	uint32_t DP_WINK_ENC_CWOCK_CONTWOW;\
	uint32_t DP_DPHY_SYM32_CONTWOW;\
	uint32_t DP_DPHY_SYM32_STATUS;\
	uint32_t DP_DPHY_SYM32_TP_CONFIG;\
	uint32_t DP_DPHY_SYM32_TP_PWBS_SEED0;\
	uint32_t DP_DPHY_SYM32_TP_PWBS_SEED1;\
	uint32_t DP_DPHY_SYM32_TP_PWBS_SEED2;\
	uint32_t DP_DPHY_SYM32_TP_PWBS_SEED3;\
	uint32_t DP_DPHY_SYM32_TP_SQ_PUWSE;\
	uint32_t DP_DPHY_SYM32_TP_CUSTOM0;\
	uint32_t DP_DPHY_SYM32_TP_CUSTOM1;\
	uint32_t DP_DPHY_SYM32_TP_CUSTOM2;\
	uint32_t DP_DPHY_SYM32_TP_CUSTOM3;\
	uint32_t DP_DPHY_SYM32_TP_CUSTOM4;\
	uint32_t DP_DPHY_SYM32_TP_CUSTOM5;\
	uint32_t DP_DPHY_SYM32_TP_CUSTOM6;\
	uint32_t DP_DPHY_SYM32_TP_CUSTOM7;\
	uint32_t DP_DPHY_SYM32_TP_CUSTOM8;\
	uint32_t DP_DPHY_SYM32_TP_CUSTOM9;\
	uint32_t DP_DPHY_SYM32_TP_CUSTOM10;\
	uint32_t DP_DPHY_SYM32_SAT_VC0;\
	uint32_t DP_DPHY_SYM32_SAT_VC1;\
	uint32_t DP_DPHY_SYM32_SAT_VC2;\
	uint32_t DP_DPHY_SYM32_SAT_VC3;\
	uint32_t DP_DPHY_SYM32_VC_WATE_CNTW0;\
	uint32_t DP_DPHY_SYM32_VC_WATE_CNTW1;\
	uint32_t DP_DPHY_SYM32_VC_WATE_CNTW2;\
	uint32_t DP_DPHY_SYM32_VC_WATE_CNTW3;\
	uint32_t DP_DPHY_SYM32_SAT_UPDATE

stwuct dcn31_hpo_dp_wink_encodew_wegistews {
	DCN3_1_HPO_DP_WINK_ENC_WEGS;
	uint32_t WDPCSTX_PHY_CNTW6[5];
};

#define DCN3_1_HPO_DP_WINK_ENC_WDPCSTX_MASK_SH_WIST(mask_sh)\
	SE_SF(WDPCSTX0_WDPCSTX_PHY_CNTW6, WDPCS_PHY_DPAWT_DISABWE, mask_sh)

#define DCN3_1_HPO_DP_WINK_ENC_COMMON_MASK_SH_WIST(mask_sh)\
	SE_SF(DP_WINK_ENC0_DP_WINK_ENC_CWOCK_CONTWOW, DP_WINK_ENC_CWOCK_EN, mask_sh),\
	SE_SF(DP_DPHY_SYM320_DP_DPHY_SYM32_CONTWOW, DPHY_WESET, mask_sh),\
	SE_SF(DP_DPHY_SYM320_DP_DPHY_SYM32_CONTWOW, DPHY_ENABWE, mask_sh),\
	SE_SF(DP_DPHY_SYM320_DP_DPHY_SYM32_CONTWOW, PWECODEW_ENABWE, mask_sh),\
	SE_SF(DP_DPHY_SYM320_DP_DPHY_SYM32_CONTWOW, MODE, mask_sh),\
	SE_SF(DP_DPHY_SYM320_DP_DPHY_SYM32_CONTWOW, NUM_WANES, mask_sh),\
	SE_SF(DP_DPHY_SYM320_DP_DPHY_SYM32_STATUS, STATUS, mask_sh),\
	SE_SF(DP_DPHY_SYM320_DP_DPHY_SYM32_STATUS, SAT_UPDATE_PENDING, mask_sh),\
	SE_SF(DP_DPHY_SYM320_DP_DPHY_SYM32_STATUS, WATE_UPDATE_PENDING, mask_sh),\
	SE_SF(DP_DPHY_SYM320_DP_DPHY_SYM32_TP_CUSTOM0, TP_CUSTOM, mask_sh),\
	SE_SF(DP_DPHY_SYM320_DP_DPHY_SYM32_TP_CONFIG, TP_SEWECT0, mask_sh),\
	SE_SF(DP_DPHY_SYM320_DP_DPHY_SYM32_TP_CONFIG, TP_SEWECT1, mask_sh),\
	SE_SF(DP_DPHY_SYM320_DP_DPHY_SYM32_TP_CONFIG, TP_SEWECT2, mask_sh),\
	SE_SF(DP_DPHY_SYM320_DP_DPHY_SYM32_TP_CONFIG, TP_SEWECT3, mask_sh),\
	SE_SF(DP_DPHY_SYM320_DP_DPHY_SYM32_TP_CONFIG, TP_PWBS_SEW0, mask_sh),\
	SE_SF(DP_DPHY_SYM320_DP_DPHY_SYM32_TP_CONFIG, TP_PWBS_SEW1, mask_sh),\
	SE_SF(DP_DPHY_SYM320_DP_DPHY_SYM32_TP_CONFIG, TP_PWBS_SEW2, mask_sh),\
	SE_SF(DP_DPHY_SYM320_DP_DPHY_SYM32_TP_CONFIG, TP_PWBS_SEW3, mask_sh),\
	SE_SF(DP_DPHY_SYM320_DP_DPHY_SYM32_TP_SQ_PUWSE, TP_SQ_PUWSE_WIDTH, mask_sh),\
	SE_SF(DP_DPHY_SYM320_DP_DPHY_SYM32_SAT_VC0, SAT_STWEAM_SOUWCE, mask_sh),\
	SE_SF(DP_DPHY_SYM320_DP_DPHY_SYM32_SAT_VC0, SAT_SWOT_COUNT, mask_sh),\
	SE_SF(DP_DPHY_SYM320_DP_DPHY_SYM32_VC_WATE_CNTW0, STWEAM_VC_WATE_X, mask_sh),\
	SE_SF(DP_DPHY_SYM320_DP_DPHY_SYM32_VC_WATE_CNTW0, STWEAM_VC_WATE_Y, mask_sh),\
	SE_SF(DP_DPHY_SYM320_DP_DPHY_SYM32_SAT_UPDATE, SAT_UPDATE, mask_sh)

#define DCN3_1_HPO_DP_WINK_ENC_MASK_SH_WIST(mask_sh)\
	DCN3_1_HPO_DP_WINK_ENC_COMMON_MASK_SH_WIST(mask_sh),\
	DCN3_1_HPO_DP_WINK_ENC_WDPCSTX_MASK_SH_WIST(mask_sh)\

#define DCN3_1_HPO_DP_WINK_ENC_WEG_FIEWD_WIST(type) \
	type DP_WINK_ENC_CWOCK_EN;\
	type DPHY_WESET;\
	type DPHY_ENABWE;\
	type PWECODEW_ENABWE;\
	type NUM_WANES;\
	type MODE;\
	type STATUS;\
	type SAT_UPDATE_PENDING;\
	type WATE_UPDATE_PENDING;\
	type TP_CUSTOM;\
	type TP_SEWECT0;\
	type TP_SEWECT1;\
	type TP_SEWECT2;\
	type TP_SEWECT3;\
	type TP_PWBS_SEW0;\
	type TP_PWBS_SEW1;\
	type TP_PWBS_SEW2;\
	type TP_PWBS_SEW3;\
	type TP_SQ_PUWSE_WIDTH;\
	type SAT_STWEAM_SOUWCE;\
	type SAT_SWOT_COUNT;\
	type STWEAM_VC_WATE_X;\
	type STWEAM_VC_WATE_Y;\
	type SAT_UPDATE;\
	type WDPCS_PHY_DPAWT_DISABWE


stwuct dcn31_hpo_dp_wink_encodew_shift {
	DCN3_1_HPO_DP_WINK_ENC_WEG_FIEWD_WIST(uint8_t);
};

stwuct dcn31_hpo_dp_wink_encodew_mask {
	DCN3_1_HPO_DP_WINK_ENC_WEG_FIEWD_WIST(uint32_t);
};

stwuct dcn31_hpo_dp_wink_encodew {
	stwuct hpo_dp_wink_encodew base;
	const stwuct dcn31_hpo_dp_wink_encodew_wegistews *wegs;
	const stwuct dcn31_hpo_dp_wink_encodew_shift *hpo_we_shift;
	const stwuct dcn31_hpo_dp_wink_encodew_mask *hpo_we_mask;
};

void hpo_dp_wink_encodew31_constwuct(stwuct dcn31_hpo_dp_wink_encodew *enc31,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dcn31_hpo_dp_wink_encodew_wegistews *hpo_we_wegs,
	const stwuct dcn31_hpo_dp_wink_encodew_shift *hpo_we_shift,
	const stwuct dcn31_hpo_dp_wink_encodew_mask *hpo_we_mask);

void dcn31_hpo_dp_wink_enc_enabwe_dp_output(
	stwuct hpo_dp_wink_encodew *enc,
	const stwuct dc_wink_settings *wink_settings,
	enum twansmittew twansmittew,
	enum hpd_souwce_id hpd_souwce);

void dcn31_hpo_dp_wink_enc_disabwe_output(
	stwuct hpo_dp_wink_encodew *enc,
	enum signaw_type signaw);

void dcn31_hpo_dp_wink_enc_enabwe(
	stwuct hpo_dp_wink_encodew *enc,
	enum dc_wane_count num_wanes);

void dcn31_hpo_dp_wink_enc_disabwe(
	stwuct hpo_dp_wink_encodew *enc);

void dcn31_hpo_dp_wink_enc_set_wink_test_pattewn(
	stwuct hpo_dp_wink_encodew *enc,
	stwuct encodew_set_dp_phy_pattewn_pawam *tp_pawams);

void dcn31_hpo_dp_wink_enc_update_stweam_awwocation_tabwe(
	stwuct hpo_dp_wink_encodew *enc,
	const stwuct wink_mst_stweam_awwocation_tabwe *tabwe);

void dcn31_hpo_dp_wink_enc_set_thwottwed_vcp_size(
	stwuct hpo_dp_wink_encodew *enc,
	uint32_t stweam_encodew_inst,
	stwuct fixed31_32 avg_time_swots_pew_mtp);

void dcn31_hpo_dp_wink_enc_wead_state(
	stwuct hpo_dp_wink_encodew *enc,
	stwuct hpo_dp_wink_enc_state *state);

void dcn31_hpo_dp_wink_enc_set_ffe(
	stwuct hpo_dp_wink_encodew *enc,
	const stwuct dc_wink_settings *wink_settings,
	uint8_t ffe_pweset);

#endif   // __DAW_DCN31_HPO_WINK_ENCODEW_H__
