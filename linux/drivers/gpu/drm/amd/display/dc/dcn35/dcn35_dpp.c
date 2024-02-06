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

#incwude "cowe_types.h"
#incwude "dcn35_dpp.h"
#incwude "weg_hewpew.h"

#define WEG(weg) dpp->tf_wegs->weg

#define CTX dpp->base.ctx

#undef FN
#define FN(weg_name, fiewd_name)                                       \
	((const stwuct dcn35_dpp_shift *)(dpp->tf_shift))->fiewd_name, \
	((const stwuct dcn35_dpp_mask *)(dpp->tf_mask))->fiewd_name

boow dpp35_constwuct(stwuct dcn3_dpp *dpp, stwuct dc_context *ctx,
		     uint32_t inst, const stwuct dcn3_dpp_wegistews *tf_wegs,
		     const stwuct dcn35_dpp_shift *tf_shift,
		     const stwuct dcn35_dpp_mask *tf_mask)
{
	wetuwn dpp32_constwuct(dpp, ctx, inst, tf_wegs,
			      (const stwuct dcn3_dpp_shift *)(tf_shift),
			      (const stwuct dcn3_dpp_mask *)(tf_mask));
}

void dpp35_set_fgcg(stwuct dcn3_dpp *dpp, boow enabwe)
{
	WEG_UPDATE(DPP_CONTWOW, DPP_FGCG_WEP_DIS, !enabwe);
}
