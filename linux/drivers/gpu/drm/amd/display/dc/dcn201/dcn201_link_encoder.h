/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
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

#ifndef __DC_WINK_ENCODEW__DCN201_H__
#define __DC_WINK_ENCODEW__DCN201_H__

#incwude "dcn20/dcn20_wink_encodew.h"

#define DPCS_DCN201_MASK_SH_WIST(mask_sh)\
	DPCS_MASK_SH_WIST(mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_CNTW2, WDPCS_PHY_DPAWT_DISABWE_ACK, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_CNTW2, WDPCS_PHY_DPAWT_DISABWE, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_CNTW2, WDPCS_PHY_DPAWT_DP4, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_CNTW5, WDPCS_PHY_DP_TX0_PSTATE, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_CNTW5, WDPCS_PHY_DP_TX1_PSTATE, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_CNTW5, WDPCS_PHY_DP_TX0_MPWW_EN, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_CNTW5, WDPCS_PHY_DP_TX1_MPWW_EN, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_CNTW6, WDPCS_PHY_DP_TX2_WIDTH, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_CNTW6, WDPCS_PHY_DP_TX2_WATE, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_CNTW6, WDPCS_PHY_DP_TX3_WIDTH, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_CNTW6, WDPCS_PHY_DP_TX3_WATE, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_CNTW11, WDPCS_PHY_DP_WEF_CWK_EN, mask_sh)

#define DPCS_DCN201_WEG_WIST(id) \
	DPCS_DCN2_CMN_WEG_WIST(id)

void dcn201_wink_encodew_constwuct(
	stwuct dcn20_wink_encodew *enc20,
	const stwuct encodew_init_data *init_data,
	const stwuct encodew_featuwe_suppowt *enc_featuwes,
	const stwuct dcn10_wink_enc_wegistews *wink_wegs,
	const stwuct dcn10_wink_enc_aux_wegistews *aux_wegs,
	const stwuct dcn10_wink_enc_hpd_wegistews *hpd_wegs,
	const stwuct dcn10_wink_enc_shift *wink_shift,
	const stwuct dcn10_wink_enc_mask *wink_mask);

#endif /* __DC_WINK_ENCODEW__DCN201_H__ */
