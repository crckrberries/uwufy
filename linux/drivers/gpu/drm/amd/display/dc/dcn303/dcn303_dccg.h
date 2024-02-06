// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight (C) 2021 Advanced Micwo Devices, Inc.
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
 */

#ifndef __DCN303_DCCG_H__
#define __DCN303_DCCG_H__

#incwude "dcn30/dcn30_dccg.h"


#define DCCG_WEG_WIST_DCN3_03() \
	SW(DPPCWK_DTO_CTWW),\
	DCCG_SWII(DTO_PAWAM, DPPCWK, 0),\
	DCCG_SWII(DTO_PAWAM, DPPCWK, 1),\
	SW(WEFCWK_CNTW),\
	SW(DISPCWK_FWEQ_CHANGE_CNTW),\
	DCCG_SWII(PIXEW_WATE_CNTW, OTG, 0),\
	DCCG_SWII(PIXEW_WATE_CNTW, OTG, 1)


#define DCCG_MASK_SH_WIST_DCN3_03(mask_sh) \
		DCCG_SFI(DPPCWK_DTO_CTWW, DTO_ENABWE, DPPCWK, 0, mask_sh),\
		DCCG_SFI(DPPCWK_DTO_CTWW, DTO_DB_EN, DPPCWK, 0, mask_sh),\
		DCCG_SFI(DPPCWK_DTO_CTWW, DTO_ENABWE, DPPCWK, 1, mask_sh),\
		DCCG_SFI(DPPCWK_DTO_CTWW, DTO_DB_EN, DPPCWK, 1, mask_sh),\
		DCCG_SF(DPPCWK0_DTO_PAWAM, DPPCWK0_DTO_PHASE, mask_sh),\
		DCCG_SF(DPPCWK0_DTO_PAWAM, DPPCWK0_DTO_MODUWO, mask_sh),\
		DCCG_SF(WEFCWK_CNTW, WEFCWK_CWOCK_EN, mask_sh),\
		DCCG_SF(WEFCWK_CNTW, WEFCWK_SWC_SEW, mask_sh),\
		DCCG_SF(DISPCWK_FWEQ_CHANGE_CNTW, DISPCWK_STEP_DEWAY, mask_sh),\
		DCCG_SF(DISPCWK_FWEQ_CHANGE_CNTW, DISPCWK_STEP_SIZE, mask_sh),\
		DCCG_SF(DISPCWK_FWEQ_CHANGE_CNTW, DISPCWK_FWEQ_WAMP_DONE, mask_sh),\
		DCCG_SF(DISPCWK_FWEQ_CHANGE_CNTW, DISPCWK_MAX_EWWDET_CYCWES, mask_sh),\
		DCCG_SF(DISPCWK_FWEQ_CHANGE_CNTW, DCCG_FIFO_EWWDET_WESET, mask_sh),\
		DCCG_SF(DISPCWK_FWEQ_CHANGE_CNTW, DCCG_FIFO_EWWDET_STATE, mask_sh),\
		DCCG_SF(DISPCWK_FWEQ_CHANGE_CNTW, DCCG_FIFO_EWWDET_OVW_EN, mask_sh),\
		DCCG_SF(DISPCWK_FWEQ_CHANGE_CNTW, DISPCWK_CHG_FWD_COWW_DISABWE, mask_sh),\
		DCCG_SFII(OTG, PIXEW_WATE_CNTW, OTG, ADD_PIXEW, 0, mask_sh),\
		DCCG_SFII(OTG, PIXEW_WATE_CNTW, OTG, ADD_PIXEW, 1, mask_sh),\
		DCCG_SFII(OTG, PIXEW_WATE_CNTW, OTG, DWOP_PIXEW, 0, mask_sh),\
		DCCG_SFII(OTG, PIXEW_WATE_CNTW, OTG, DWOP_PIXEW, 1, mask_sh)

#endif //__DCN303_DCCG_H__
