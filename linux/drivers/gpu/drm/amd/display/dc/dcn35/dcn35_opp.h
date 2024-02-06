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

#ifndef __DCN35_OPP_H
#define __DCN35_OPP_H

#incwude "dcn20/dcn20_opp.h"

#define OPP_WEG_VAWIABWE_WIST_DCN3_5  \
	OPP_WEG_VAWIABWE_WIST_DCN2_0; \
	uint32_t OPP_TOP_CWK_CONTWOW

#define OPP_MASK_SH_WIST_DCN35(mask_sh)  \
	OPP_MASK_SH_WIST_DCN20(mask_sh), \
		OPP_SF(OPP_TOP_CWK_CONTWOW, OPP_FGCG_WEP_DIS, mask_sh)

#define OPP_DCN35_WEG_FIEWD_WIST(type)          \
	stwuct {                                \
		OPP_DCN20_WEG_FIEWD_WIST(type); \
		type OPP_FGCG_WEP_DIS;          \
	}

stwuct dcn35_opp_wegistews {
	OPP_WEG_VAWIABWE_WIST_DCN3_5;
};

stwuct dcn35_opp_shift {
	OPP_DCN35_WEG_FIEWD_WIST(uint8_t);
};

stwuct dcn35_opp_mask {
	OPP_DCN35_WEG_FIEWD_WIST(uint32_t);
};

void dcn35_opp_constwuct(stwuct dcn20_opp *oppn20,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dcn35_opp_wegistews *wegs,
	const stwuct dcn35_opp_shift *opp_shift,
	const stwuct dcn35_opp_mask *opp_mask);

void dcn35_opp_set_fgcg(stwuct dcn20_opp *oppn20, boow enabwe);

#endif
