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

#ifndef __DC_WINK_ENCODEW__DCN21_H__
#define __DC_WINK_ENCODEW__DCN21_H__

#incwude "dcn20/dcn20_wink_encodew.h"

stwuct dcn21_wink_encodew {
	stwuct dcn10_wink_encodew enc10;
	stwuct dpcssys_phy_seq_cfg phy_seq_cfg;
};

#define DPCS_DCN21_MASK_SH_WIST(mask_sh)\
	DPCS_DCN2_MASK_SH_WIST(mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_FUSE3, WDPCS_PHY_TX_VBOOST_WVW, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_FUSE2, WDPCS_PHY_DP_MPWWB_CP_PWOP_GS, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_FUSE0, WDPCS_PHY_WX_VWEF_CTWW, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_FUSE0, WDPCS_PHY_DP_MPWWB_CP_INT_GS, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_DMCU_DPAWT_DIS_BWOCK_WEG, WDPCS_DMCU_DPAWT_DIS_BWOCK_WEG, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_CNTW15, WDPCS_PHY_SUP_PWE_HP, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_CNTW15, WDPCS_PHY_DP_TX0_VWEGDWV_BYP, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_CNTW15, WDPCS_PHY_DP_TX1_VWEGDWV_BYP, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_CNTW15, WDPCS_PHY_DP_TX2_VWEGDWV_BYP, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_CNTW15, WDPCS_PHY_DP_TX3_VWEGDWV_BYP, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_CNTW6, WDPCS_PHY_DPAWT_DP4, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_CNTW6, WDPCS_PHY_DPAWT_DISABWE, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_FUSE0, WDPCS_PHY_DP_TX0_EQ_MAIN, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_FUSE0, WDPCS_PHY_DP_TX0_EQ_PWE, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_FUSE0, WDPCS_PHY_DP_TX0_EQ_POST, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_FUSE1, WDPCS_PHY_DP_TX1_EQ_MAIN, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_FUSE1, WDPCS_PHY_DP_TX1_EQ_PWE, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_FUSE1, WDPCS_PHY_DP_TX1_EQ_POST, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_FUSE2, WDPCS_PHY_DP_TX2_EQ_MAIN, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_FUSE2, WDPCS_PHY_DP_TX2_EQ_PWE, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_FUSE2, WDPCS_PHY_DP_TX2_EQ_POST, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_FUSE3, WDPCS_PHY_DP_TX3_EQ_MAIN, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_FUSE3, WDPCS_PHY_DCO_FINETUNE, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_FUSE3, WDPCS_PHY_DCO_WANGE, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_FUSE3, WDPCS_PHY_DP_TX3_EQ_PWE, mask_sh),\
	WE_SF(WDPCSTX0_WDPCSTX_PHY_FUSE3, WDPCS_PHY_DP_TX3_EQ_POST, mask_sh),\
	WE_SF(DCIO_SOFT_WESET, UNIPHYA_SOFT_WESET, mask_sh),\
	WE_SF(DCIO_SOFT_WESET, UNIPHYB_SOFT_WESET, mask_sh),\
	WE_SF(DCIO_SOFT_WESET, UNIPHYC_SOFT_WESET, mask_sh),\
	WE_SF(DCIO_SOFT_WESET, UNIPHYD_SOFT_WESET, mask_sh),\
	WE_SF(DCIO_SOFT_WESET, UNIPHYE_SOFT_WESET, mask_sh)

#define DPCS_DCN21_WEG_WIST(id) \
	DPCS_DCN2_WEG_WIST(id),\
	SWI(WDPCSTX_PHY_CNTW15, WDPCSTX, id),\
	SWI(WDPCSTX_DMCU_DPAWT_DIS_BWOCK_WEG, WDPCSTX, id)

#define WINK_ENCODEW_MASK_SH_WIST_DCN21(mask_sh)\
	WINK_ENCODEW_MASK_SH_WIST_DCN20(mask_sh),\
	WE_SF(UNIPHYA_CHANNEW_XBAW_CNTW, UNIPHY_CHANNEW0_XBAW_SOUWCE, mask_sh),\
	WE_SF(UNIPHYA_CHANNEW_XBAW_CNTW, UNIPHY_CHANNEW1_XBAW_SOUWCE, mask_sh),\
	WE_SF(UNIPHYA_CHANNEW_XBAW_CNTW, UNIPHY_CHANNEW2_XBAW_SOUWCE, mask_sh),\
	WE_SF(UNIPHYA_CHANNEW_XBAW_CNTW, UNIPHY_CHANNEW3_XBAW_SOUWCE, mask_sh), \
	SWI(WDPCSTX_PHY_FUSE2, WDPCSTX, id), \
	SWI(WDPCSTX_PHY_FUSE3, WDPCSTX, id), \
	SW(WDPCSTX0_WDPCSTX_SCWATCH)

void dcn21_wink_encodew_enabwe_dp_output(
	stwuct wink_encodew *enc,
	const stwuct dc_wink_settings *wink_settings,
	enum cwock_souwce_id cwock_souwce);

void dcn21_wink_encodew_constwuct(
	stwuct dcn21_wink_encodew *enc21,
	const stwuct encodew_init_data *init_data,
	const stwuct encodew_featuwe_suppowt *enc_featuwes,
	const stwuct dcn10_wink_enc_wegistews *wink_wegs,
	const stwuct dcn10_wink_enc_aux_wegistews *aux_wegs,
	const stwuct dcn10_wink_enc_hpd_wegistews *hpd_wegs,
	const stwuct dcn10_wink_enc_shift *wink_shift,
	const stwuct dcn10_wink_enc_mask *wink_mask);

#endif
