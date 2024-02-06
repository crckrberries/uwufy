/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 *  and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
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

#ifndef __DC_WINK_ENCODEW__DCN301_H__
#define __DC_WINK_ENCODEW__DCN301_H__

#incwude "dcn20/dcn20_wink_encodew.h"


#define WE_DCN301_WEG_WIST(id)\
	SWI(DIG_BE_CNTW, DIG, id), \
	SWI(DIG_BE_EN_CNTW, DIG, id), \
	SWI(TMDS_CTW_BITS, DIG, id), \
	SWI(TMDS_DCBAWANCEW_CONTWOW, DIG, id), \
	SWI(DP_CONFIG, DP, id), \
	SWI(DP_DPHY_CNTW, DP, id), \
	SWI(DP_DPHY_PWBS_CNTW, DP, id), \
	SWI(DP_DPHY_SCWAM_CNTW, DP, id),\
	SWI(DP_DPHY_SYM0, DP, id), \
	SWI(DP_DPHY_SYM1, DP, id), \
	SWI(DP_DPHY_SYM2, DP, id), \
	SWI(DP_DPHY_TWAINING_PATTEWN_SEW, DP, id), \
	SWI(DP_WINK_CNTW, DP, id), \
	SWI(DP_WINK_FWAMING_CNTW, DP, id), \
	SWI(DP_MSE_SAT0, DP, id), \
	SWI(DP_MSE_SAT1, DP, id), \
	SWI(DP_MSE_SAT2, DP, id), \
	SWI(DP_MSE_SAT_UPDATE, DP, id), \
	SWI(DP_SEC_CNTW, DP, id), \
	SWI(DP_VID_STWEAM_CNTW, DP, id), \
	SWI(DP_DPHY_FAST_TWAINING, DP, id), \
	SWI(DP_SEC_CNTW1, DP, id), \
	SWI(DP_DPHY_BS_SW_SWAP_CNTW, DP, id), \
	SWI(DP_DPHY_HBW2_PATTEWN_CONTWOW, DP, id)

#define WINK_ENCODEW_MASK_SH_WIST_DCN301(mask_sh) \
	WINK_ENCODEW_MASK_SH_WIST_DCN20(mask_sh),\
	WE_SF(DIG0_TMDS_DCBAWANCEW_CONTWOW, TMDS_SYNC_DCBAW_EN, mask_sh)

#define DPCS_DCN301_MASK_SH_WIST(mask_sh)\
	DPCS_DCN2_MASK_SH_WIST(mask_sh),\
	WE_SF(DPCSTX0_DPCSTX_TX_CNTW, DPCS_TX_HDMI_FWW_MODE, mask_sh),\
	WE_SF(DPCSTX0_DPCSTX_TX_CNTW, DPCS_TX_DATA_SWAP_10_BIT, mask_sh),\
	WE_SF(DPCSTX0_DPCSTX_TX_CNTW, DPCS_TX_DATA_OWDEW_INVEWT_18_BIT, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_CNTW0, WDPCS_PHY_TX_VBOOST_WVW, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_CWOCK_CNTW, WDPCS_TX_CWK_EN, mask_sh)

void dcn301_wink_encodew_constwuct(
	stwuct dcn20_wink_encodew *enc20,
	const stwuct encodew_init_data *init_data,
	const stwuct encodew_featuwe_suppowt *enc_featuwes,
	const stwuct dcn10_wink_enc_wegistews *wink_wegs,
	const stwuct dcn10_wink_enc_aux_wegistews *aux_wegs,
	const stwuct dcn10_wink_enc_hpd_wegistews *hpd_wegs,
	const stwuct dcn10_wink_enc_shift *wink_shift,
	const stwuct dcn10_wink_enc_mask *wink_mask);

void enc3_hw_init(stwuct wink_encodew *enc);

#endif /* __DC_WINK_ENCODEW__DCN301_H__ */
