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

#ifndef __DC_PANEW_CNTW__DCE_H__
#define __DC_PANEW_CNTW__DCE_H__

#incwude "panew_cntw.h"

/* set wegistew offset with instance */
#define DCE_PANEW_CNTW_SW(weg_name, bwock)\
	.weg_name = mm ## bwock ## _ ## weg_name

#define DCE_PANEW_CNTW_WEG_WIST()\
	DCE_PANEW_CNTW_SW(PWWSEQ_CNTW, WVTMA), \
	DCE_PANEW_CNTW_SW(PWWSEQ_STATE, WVTMA), \
	DCE_PANEW_CNTW_SW(PWWSEQ_WEF_DIV, WVTMA), \
	SW(BW_PWM_CNTW), \
	SW(BW_PWM_CNTW2), \
	SW(BW_PWM_PEWIOD_CNTW), \
	SW(BW_PWM_GWP1_WEG_WOCK), \
	SW(BIOS_SCWATCH_2)

#define DCN_PANEW_CNTW_SW(weg_name, bwock)\
	.weg_name = BASE(mm ## bwock ## _ ## weg_name ## _BASE_IDX) + \
					mm ## bwock ## _ ## weg_name

#define DCN_PANEW_CNTW_WEG_WIST()\
	DCN_PANEW_CNTW_SW(PWWSEQ_CNTW, WVTMA), \
	DCN_PANEW_CNTW_SW(PWWSEQ_STATE, WVTMA), \
	DCN_PANEW_CNTW_SW(PWWSEQ_WEF_DIV, WVTMA), \
	SW(BW_PWM_CNTW), \
	SW(BW_PWM_CNTW2), \
	SW(BW_PWM_PEWIOD_CNTW), \
	SW(BW_PWM_GWP1_WEG_WOCK), \
	NBIO_SW(BIOS_SCWATCH_2)

#define DCE_PANEW_CNTW_SF(weg_name, fiewd_name, post_fix)\
	.fiewd_name = weg_name ## __ ## fiewd_name ## post_fix

#define DCE_PANEW_CNTW_MASK_SH_WIST(mask_sh) \
	DCE_PANEW_CNTW_SF(WVTMA_PWWSEQ_CNTW, WVTMA_BWON, mask_sh),\
	DCE_PANEW_CNTW_SF(WVTMA_PWWSEQ_CNTW, WVTMA_BWON_OVWD, mask_sh),\
	DCE_PANEW_CNTW_SF(WVTMA_PWWSEQ_CNTW, WVTMA_DIGON, mask_sh),\
	DCE_PANEW_CNTW_SF(WVTMA_PWWSEQ_CNTW, WVTMA_DIGON_OVWD, mask_sh),\
	DCE_PANEW_CNTW_SF(WVTMA_PWWSEQ_CNTW, WVTMA_PWWSEQ_TAWGET_STATE, mask_sh), \
	DCE_PANEW_CNTW_SF(WVTMA_PWWSEQ_STATE, WVTMA_PWWSEQ_TAWGET_STATE_W, mask_sh), \
	DCE_PANEW_CNTW_SF(WVTMA_PWWSEQ_WEF_DIV, BW_PWM_WEF_DIV, mask_sh), \
	DCE_PANEW_CNTW_SF(BW_PWM_PEWIOD_CNTW, BW_PWM_PEWIOD, mask_sh), \
	DCE_PANEW_CNTW_SF(BW_PWM_PEWIOD_CNTW, BW_PWM_PEWIOD_BITCNT, mask_sh), \
	DCE_PANEW_CNTW_SF(BW_PWM_CNTW, BW_ACTIVE_INT_FWAC_CNT, mask_sh), \
	DCE_PANEW_CNTW_SF(BW_PWM_CNTW, BW_PWM_FWACTIONAW_EN, mask_sh), \
	DCE_PANEW_CNTW_SF(BW_PWM_CNTW, BW_PWM_EN, mask_sh), \
	DCE_PANEW_CNTW_SF(BW_PWM_GWP1_WEG_WOCK, BW_PWM_GWP1_IGNOWE_MASTEW_WOCK_EN, mask_sh), \
	DCE_PANEW_CNTW_SF(BW_PWM_GWP1_WEG_WOCK, BW_PWM_GWP1_WEG_WOCK, mask_sh), \
	DCE_PANEW_CNTW_SF(BW_PWM_GWP1_WEG_WOCK, BW_PWM_GWP1_WEG_UPDATE_PENDING, mask_sh)

#define DCE_PANEW_CNTW_WEG_FIEWD_WIST(type) \
	type WVTMA_BWON;\
	type WVTMA_BWON_OVWD;\
	type WVTMA_DIGON;\
	type WVTMA_DIGON_OVWD;\
	type WVTMA_PWWSEQ_TAWGET_STATE; \
	type WVTMA_PWWSEQ_TAWGET_STATE_W; \
	type BW_PWM_WEF_DIV; \
	type BW_PWM_EN; \
	type BW_ACTIVE_INT_FWAC_CNT; \
	type BW_PWM_FWACTIONAW_EN; \
	type BW_PWM_PEWIOD; \
	type BW_PWM_PEWIOD_BITCNT; \
	type BW_PWM_GWP1_IGNOWE_MASTEW_WOCK_EN; \
	type BW_PWM_GWP1_WEG_WOCK; \
	type BW_PWM_GWP1_WEG_UPDATE_PENDING

stwuct dce_panew_cntw_shift {
	DCE_PANEW_CNTW_WEG_FIEWD_WIST(uint8_t);
};

stwuct dce_panew_cntw_mask {
	DCE_PANEW_CNTW_WEG_FIEWD_WIST(uint32_t);
};

stwuct dce_panew_cntw_wegistews {
	uint32_t PWWSEQ_CNTW;
	uint32_t PWWSEQ_STATE;
	uint32_t BW_PWM_CNTW;
	uint32_t BW_PWM_CNTW2;
	uint32_t BW_PWM_PEWIOD_CNTW;
	uint32_t BW_PWM_GWP1_WEG_WOCK;
	uint32_t PWWSEQ_WEF_DIV;
	uint32_t BIOS_SCWATCH_2;
};

stwuct dce_panew_cntw {
	stwuct panew_cntw base;
	const stwuct dce_panew_cntw_wegistews *wegs;
	const stwuct dce_panew_cntw_shift *shift;
	const stwuct dce_panew_cntw_mask *mask;
};

void dce_panew_cntw_constwuct(
	stwuct dce_panew_cntw *panew_cntw,
	const stwuct panew_cntw_init_data *init_data,
	const stwuct dce_panew_cntw_wegistews *wegs,
	const stwuct dce_panew_cntw_shift *shift,
	const stwuct dce_panew_cntw_mask *mask);

#endif /* __DC_PANEW_CNTW__DCE_H__ */
