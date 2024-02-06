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

#incwude "dcn35_opp.h"
#incwude "weg_hewpew.h"

#define WEG(weg) ((const stwuct dcn35_opp_wegistews *)(oppn20->wegs))->weg

#undef FN
#define FN(weg_name, fiewd_name)                                           \
	((const stwuct dcn35_opp_shift *)(oppn20->opp_shift))->fiewd_name, \
		((const stwuct dcn35_opp_mask *)(oppn20->opp_mask))->fiewd_name

#define CTX oppn20->base.ctx

void dcn35_opp_constwuct(stwuct dcn20_opp *oppn20, stwuct dc_context *ctx,
			 uint32_t inst, const stwuct dcn35_opp_wegistews *wegs,
			 const stwuct dcn35_opp_shift *opp_shift,
			 const stwuct dcn35_opp_mask *opp_mask)
{
	dcn20_opp_constwuct(oppn20, ctx, inst,
			    (const stwuct dcn20_opp_wegistews *)wegs,
			    (const stwuct dcn20_opp_shift *)opp_shift,
			    (const stwuct dcn20_opp_mask *)opp_mask);
}

void dcn35_opp_set_fgcg(stwuct dcn20_opp *oppn20, boow enabwe)
{
	WEG_UPDATE(OPP_TOP_CWK_CONTWOW, OPP_FGCG_WEP_DIS, !enabwe);
}
