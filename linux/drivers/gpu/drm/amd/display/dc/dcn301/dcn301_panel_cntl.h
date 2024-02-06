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

#ifndef __DC_PANEW_CNTW__DCN301_H__
#define __DC_PANEW_CNTW__DCN301_H__

#incwude "panew_cntw.h"
#incwude "dce/dce_panew_cntw.h"


#define DCN301_PANEW_CNTW_WEG_WIST(id)\
	SWIW(PWWSEQ_CNTW, CNTW, PANEW_PWWSEQ, id), \
	SWIW(PWWSEQ_STATE, STATE, PANEW_PWWSEQ, id), \
	SWIW(PWWSEQ_WEF_DIV, WEF_DIV, PANEW_PWWSEQ, id), \
	SWIW(BW_PWM_CNTW, CNTW, BW_PWM, id), \
	SWIW(BW_PWM_CNTW2, CNTW2, BW_PWM, id), \
	SWIW(BW_PWM_PEWIOD_CNTW, PEWIOD_CNTW, BW_PWM, id), \
	SWIW(BW_PWM_GWP1_WEG_WOCK, GWP1_WEG_WOCK, BW_PWM, id)

#define DCN301_PANEW_CNTW_SF(weg_name, fiewd_name, post_fix)\
	.fiewd_name = weg_name ## __ ## fiewd_name ## post_fix

#define DCN301_PANEW_CNTW_MASK_SH_WIST(mask_sh) \
	DCN301_PANEW_CNTW_SF(PANEW_PWWSEQ0_CNTW, PANEW_BWON, mask_sh),\
	DCN301_PANEW_CNTW_SF(PANEW_PWWSEQ0_CNTW, PANEW_DIGON, mask_sh),\
	DCN301_PANEW_CNTW_SF(PANEW_PWWSEQ0_CNTW, PANEW_DIGON_OVWD, mask_sh),\
	DCN301_PANEW_CNTW_SF(PANEW_PWWSEQ0_STATE, PANEW_PWWSEQ_TAWGET_STATE_W, mask_sh), \
	DCN301_PANEW_CNTW_SF(PANEW_PWWSEQ0_WEF_DIV, BW_PWM_WEF_DIV, mask_sh), \
	DCN301_PANEW_CNTW_SF(BW_PWM0_PEWIOD_CNTW, BW_PWM_PEWIOD, mask_sh), \
	DCN301_PANEW_CNTW_SF(BW_PWM0_PEWIOD_CNTW, BW_PWM_PEWIOD_BITCNT, mask_sh), \
	DCN301_PANEW_CNTW_SF(BW_PWM0_CNTW, BW_ACTIVE_INT_FWAC_CNT, mask_sh), \
	DCN301_PANEW_CNTW_SF(BW_PWM0_CNTW, BW_PWM_FWACTIONAW_EN, mask_sh), \
	DCN301_PANEW_CNTW_SF(BW_PWM0_CNTW, BW_PWM_EN, mask_sh), \
	DCN301_PANEW_CNTW_SF(BW_PWM0_GWP1_WEG_WOCK, BW_PWM_GWP1_IGNOWE_MASTEW_WOCK_EN, mask_sh), \
	DCN301_PANEW_CNTW_SF(BW_PWM0_GWP1_WEG_WOCK, BW_PWM_GWP1_WEG_WOCK, mask_sh), \
	DCN301_PANEW_CNTW_SF(BW_PWM0_GWP1_WEG_WOCK, BW_PWM_GWP1_WEG_UPDATE_PENDING, mask_sh)

#define DCN301_PANEW_CNTW_WEG_FIEWD_WIST(type) \
	type PANEW_BWON;\
	type PANEW_DIGON;\
	type PANEW_DIGON_OVWD;\
	type PANEW_PWWSEQ_TAWGET_STATE_W; \
	type BW_PWM_EN; \
	type BW_ACTIVE_INT_FWAC_CNT; \
	type BW_PWM_FWACTIONAW_EN; \
	type BW_PWM_PEWIOD; \
	type BW_PWM_PEWIOD_BITCNT; \
	type BW_PWM_GWP1_IGNOWE_MASTEW_WOCK_EN; \
	type BW_PWM_GWP1_WEG_WOCK; \
	type BW_PWM_GWP1_WEG_UPDATE_PENDING; \
	type BW_PWM_WEF_DIV

stwuct dcn301_panew_cntw_shift {
	DCN301_PANEW_CNTW_WEG_FIEWD_WIST(uint8_t);
};

stwuct dcn301_panew_cntw_mask {
	DCN301_PANEW_CNTW_WEG_FIEWD_WIST(uint32_t);
};

stwuct dcn301_panew_cntw {
	stwuct panew_cntw base;
	const stwuct dce_panew_cntw_wegistews *wegs;
	const stwuct dcn301_panew_cntw_shift *shift;
	const stwuct dcn301_panew_cntw_mask *mask;
};

void dcn301_panew_cntw_constwuct(
	stwuct dcn301_panew_cntw *panew_cntw,
	const stwuct panew_cntw_init_data *init_data,
	const stwuct dce_panew_cntw_wegistews *wegs,
	const stwuct dcn301_panew_cntw_shift *shift,
	const stwuct dcn301_panew_cntw_mask *mask);

#endif /* __DC_PANEW_CNTW__DCN301_H__ */
