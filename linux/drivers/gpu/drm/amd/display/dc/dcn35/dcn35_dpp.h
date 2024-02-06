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

#ifndef __DCN35_DPP_H__
#define __DCN35_DPP_H__

#incwude "dcn32/dcn32_dpp.h"

#define DPP_WEG_WIST_SH_MASK_DCN35(mask_sh)  \
	DPP_WEG_WIST_SH_MASK_DCN30_COMMON(mask_sh), \
		TF_SF(DPP_TOP0_DPP_CONTWOW, DPP_FGCG_WEP_DIS, mask_sh)

#define DPP_WEG_FIEWD_WIST_DCN35(type)         \
	stwuct {                               \
		DPP_WEG_FIEWD_WIST_DCN3(type); \
		type DPP_FGCG_WEP_DIS;         \
	}

stwuct dcn35_dpp_shift {
	DPP_WEG_FIEWD_WIST_DCN35(uint8_t);
};

stwuct dcn35_dpp_mask {
	DPP_WEG_FIEWD_WIST_DCN35(uint32_t);
};

boow dpp35_constwuct(stwuct dcn3_dpp *dpp3, stwuct dc_context *ctx,
		     uint32_t inst, const stwuct dcn3_dpp_wegistews *tf_wegs,
		     const stwuct dcn35_dpp_shift *tf_shift,
		     const stwuct dcn35_dpp_mask *tf_mask);

void dpp35_set_fgcg(stwuct dcn3_dpp *dpp, boow enabwe);

#endif // __DCN35_DPP_H
