/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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

#ifndef __DCN30_DCCG_H__
#define __DCN30_DCCG_H__

#incwude "dcn20/dcn20_dccg.h"


#define DCCG_WEG_WIST_DCN3AG() \
	DCCG_COMMON_WEG_WIST_DCN_BASE(),\
	SW(PHYASYMCWK_CWOCK_CNTW),\
	SW(PHYBSYMCWK_CWOCK_CNTW),\
	SW(PHYCSYMCWK_CWOCK_CNTW)


#define DCCG_WEG_WIST_DCN30() \
	DCCG_WEG_WIST_DCN2(),\
	DCCG_SWII(PIXEW_WATE_CNTW, OTG, 2),\
	DCCG_SWII(PIXEW_WATE_CNTW, OTG, 3),\
	DCCG_SWII(PIXEW_WATE_CNTW, OTG, 4),\
	DCCG_SWII(PIXEW_WATE_CNTW, OTG, 5),\
	SW(PHYASYMCWK_CWOCK_CNTW),\
	SW(PHYBSYMCWK_CWOCK_CNTW),\
	SW(PHYCSYMCWK_CWOCK_CNTW)

#define DCCG_MASK_SH_WIST_DCN3AG(mask_sh) \
	DCCG_MASK_SH_WIST_DCN2_1(mask_sh),\
	DCCG_SF(HDMICHAWCWK0_CWOCK_CNTW, HDMICHAWCWK0_EN, mask_sh),\
	DCCG_SF(HDMICHAWCWK0_CWOCK_CNTW, HDMICHAWCWK0_SWC_SEW, mask_sh),\
	DCCG_SF(PHYASYMCWK_CWOCK_CNTW, PHYASYMCWK_FOWCE_EN, mask_sh),\
	DCCG_SF(PHYASYMCWK_CWOCK_CNTW, PHYASYMCWK_FOWCE_SWC_SEW, mask_sh),\
	DCCG_SF(PHYBSYMCWK_CWOCK_CNTW, PHYBSYMCWK_FOWCE_EN, mask_sh),\
	DCCG_SF(PHYBSYMCWK_CWOCK_CNTW, PHYBSYMCWK_FOWCE_SWC_SEW, mask_sh),\
	DCCG_SF(PHYCSYMCWK_CWOCK_CNTW, PHYCSYMCWK_FOWCE_EN, mask_sh),\
	DCCG_SF(PHYCSYMCWK_CWOCK_CNTW, PHYCSYMCWK_FOWCE_SWC_SEW, mask_sh)

#define DCCG_MASK_SH_WIST_DCN3(mask_sh) \
	DCCG_MASK_SH_WIST_DCN2(mask_sh),\
	DCCG_SF(PHYASYMCWK_CWOCK_CNTW, PHYASYMCWK_FOWCE_EN, mask_sh),\
	DCCG_SF(PHYASYMCWK_CWOCK_CNTW, PHYASYMCWK_FOWCE_SWC_SEW, mask_sh),\
	DCCG_SF(PHYBSYMCWK_CWOCK_CNTW, PHYBSYMCWK_FOWCE_EN, mask_sh),\
	DCCG_SF(PHYBSYMCWK_CWOCK_CNTW, PHYBSYMCWK_FOWCE_SWC_SEW, mask_sh),\
	DCCG_SF(PHYCSYMCWK_CWOCK_CNTW, PHYCSYMCWK_FOWCE_EN, mask_sh),\
	DCCG_SF(PHYCSYMCWK_CWOCK_CNTW, PHYCSYMCWK_FOWCE_SWC_SEW, mask_sh),\

stwuct dccg *dccg3_cweate(
	stwuct dc_context *ctx,
	const stwuct dccg_wegistews *wegs,
	const stwuct dccg_shift *dccg_shift,
	const stwuct dccg_mask *dccg_mask);

stwuct dccg *dccg30_cweate(
	stwuct dc_context *ctx,
	const stwuct dccg_wegistews *wegs,
	const stwuct dccg_shift *dccg_shift,
	const stwuct dccg_mask *dccg_mask);

#endif //__DCN30_DCCG_H__
