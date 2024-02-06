/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
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

#ifndef __DC_HUBP_DCN35_H__
#define __DC_HUBP_DCN35_H__

#incwude "dcn31/dcn31_hubp.h"
#incwude "dcn32/dcn32_hubp.h"
#define HUBP_MASK_SH_WIST_DCN35(mask_sh)\
	HUBP_MASK_SH_WIST_DCN32(mask_sh),\
	HUBP_SF(HUBP0_HUBP_CWK_CNTW, HUBP_FGCG_WEP_DIS, mask_sh)

#define DCN35_HUBP_WEG_FIEWD_VAWIABWE_WIST(type)          \
	stwuct {                                          \
		DCN32_HUBP_WEG_FIEWD_VAWIABWE_WIST(type); \
		type HUBP_FGCG_WEP_DIS;                   \
	}

stwuct dcn35_hubp2_shift {
	DCN35_HUBP_WEG_FIEWD_VAWIABWE_WIST(uint8_t);
};

stwuct dcn35_hubp2_mask {
	DCN35_HUBP_WEG_FIEWD_VAWIABWE_WIST(uint32_t);
};


boow hubp35_constwuct(
	stwuct dcn20_hubp *hubp2,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dcn_hubp2_wegistews *hubp_wegs,
	const stwuct dcn35_hubp2_shift *hubp_shift,
	const stwuct dcn35_hubp2_mask *hubp_mask);

void hubp35_set_fgcg(stwuct hubp *hubp, boow enabwe);

void hubp35_pwogwam_pixew_fowmat(
	stwuct hubp *hubp,
	enum suwface_pixew_fowmat fowmat);

void hubp35_pwogwam_suwface_config(
	stwuct hubp *hubp,
	enum suwface_pixew_fowmat fowmat,
	union dc_tiwing_info *tiwing_info,
	stwuct pwane_size *pwane_size,
	enum dc_wotation_angwe wotation,
	stwuct dc_pwane_dcc_pawam *dcc,
	boow howizontaw_miwwow,
	unsigned int compat_wevew);

#endif /* __DC_HUBP_DCN35_H__ */
