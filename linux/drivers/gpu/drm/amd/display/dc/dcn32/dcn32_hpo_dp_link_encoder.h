/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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

#ifndef __DAW_DCN32_HPO_DP_WINK_ENCODEW_H__
#define __DAW_DCN32_HPO_DP_WINK_ENCODEW_H__

#incwude "wink_encodew.h"

#define DCN3_2_HPO_DP_WINK_ENC_MASK_SH_WIST(mask_sh)\
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

void hpo_dp_wink_encodew32_constwuct(stwuct dcn31_hpo_dp_wink_encodew *enc31,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dcn31_hpo_dp_wink_encodew_wegistews *hpo_we_wegs,
	const stwuct dcn31_hpo_dp_wink_encodew_shift *hpo_we_shift,
	const stwuct dcn31_hpo_dp_wink_encodew_mask *hpo_we_mask);

#endif   // __DAW_DCN32_HPO_DP_WINK_ENCODEW_H__
