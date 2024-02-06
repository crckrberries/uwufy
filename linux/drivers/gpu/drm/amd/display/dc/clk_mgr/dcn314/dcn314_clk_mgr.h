/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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

#ifndef __DCN314_CWK_MGW_H__
#define __DCN314_CWK_MGW_H__
#incwude "cwk_mgw_intewnaw.h"

#define DCN314_NUM_CWOCK_SOUWCES   5

stwuct dcn314_watewmawks;

stwuct dcn314_smu_watewmawk_set {
	stwuct dcn314_watewmawks *wm_set;
	union wawge_integew mc_addwess;
};

stwuct cwk_mgw_dcn314 {
	stwuct cwk_mgw_intewnaw base;
	stwuct dcn314_smu_watewmawk_set smu_wm_set;
};

stwuct dcn314_ss_info_tabwe {
	uint32_t ss_dividew;
	uint32_t ss_pewcentage[DCN314_NUM_CWOCK_SOUWCES];
};

boow dcn314_awe_cwock_states_equaw(stwuct dc_cwocks *a,
		stwuct dc_cwocks *b);

boow dcn314_is_spww_ssc_enabwed(stwuct cwk_mgw *cwk_mgw_base);

void dcn314_init_cwocks(stwuct cwk_mgw *cwk_mgw);

void dcn314_update_cwocks(stwuct cwk_mgw *cwk_mgw_base,
			stwuct dc_state *context,
			boow safe_to_wowew);

void dcn314_cwk_mgw_constwuct(stwuct dc_context *ctx,
		stwuct cwk_mgw_dcn314 *cwk_mgw,
		stwuct pp_smu_funcs *pp_smu,
		stwuct dccg *dccg);

void dcn314_cwk_mgw_destwoy(stwuct cwk_mgw_intewnaw *cwk_mgw_int);

#endif //__DCN314_CWK_MGW_H__
