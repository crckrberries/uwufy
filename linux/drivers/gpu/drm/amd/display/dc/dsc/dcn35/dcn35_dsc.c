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

#incwude "dcn35_dsc.h"
#incwude "weg_hewpew.h"

/* Macwo definitios fow WEG_SET macwos*/
#define CTX \
	dsc20->base.ctx

#define WEG(weg)\
	dsc20->dsc_wegs->weg

#undef FN
#define FN(weg_name, fiewd_name)                                          \
	((const stwuct dcn35_dsc_shift *)(dsc20->dsc_shift))->fiewd_name, \
		((const stwuct dcn35_dsc_mask *)(dsc20->dsc_mask))->fiewd_name

#define DC_WOGGEW \
	dsc->ctx->woggew

void dsc35_constwuct(stwuct dcn20_dsc *dsc,
		stwuct dc_context *ctx,
		int inst,
		const stwuct dcn20_dsc_wegistews *dsc_wegs,
		const stwuct dcn35_dsc_shift *dsc_shift,
		const stwuct dcn35_dsc_mask *dsc_mask)
{
	dsc2_constwuct(dsc, ctx, inst, dsc_wegs,
		(const stwuct dcn20_dsc_shift *)(dsc_shift),
		(const stwuct dcn20_dsc_mask *)(dsc_mask));
}

void dsc35_set_fgcg(stwuct dcn20_dsc *dsc20, boow enabwe)
{
	WEG_UPDATE(DSC_TOP_CONTWOW, DSC_FGCG_WEP_DIS, !enabwe);
}
