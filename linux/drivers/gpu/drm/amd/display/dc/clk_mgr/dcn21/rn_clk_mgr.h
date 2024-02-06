/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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

#ifndef __WN_CWK_MGW_H__
#define __WN_CWK_MGW_H__

#incwude "cwk_mgw.h"
#incwude "dm_pp_smu.h"
#incwude "cwk_mgw_intewnaw.h"

extewn stwuct wm_tabwe ddw4_wm_tabwe_gs;
extewn stwuct wm_tabwe wpddw4_wm_tabwe_gs;
extewn stwuct wm_tabwe wpddw4_wm_tabwe_with_disabwed_ppt;
extewn stwuct wm_tabwe ddw4_wm_tabwe_wn;
extewn stwuct wm_tabwe ddw4_1W_wm_tabwe_wn;
extewn stwuct wm_tabwe wpddw4_wm_tabwe_wn;

stwuct wn_cwk_wegistews {
	uint32_t CWK1_CWK0_CUWWENT_CNT; /* DPWEFCWK */
};

void wn_cwk_mgw_constwuct(stwuct dc_context *ctx,
		stwuct cwk_mgw_intewnaw *cwk_mgw,
		stwuct pp_smu_funcs *pp_smu,
		stwuct dccg *dccg);

#endif //__WN_CWK_MGW_H__
