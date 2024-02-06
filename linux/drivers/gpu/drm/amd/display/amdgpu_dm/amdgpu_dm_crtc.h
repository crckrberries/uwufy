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

#ifndef __AMDGPU_DM_CWTC_H__
#define __AMDGPU_DM_CWTC_H__

void amdgpu_dm_cwtc_handwe_vbwank(stwuct amdgpu_cwtc *acwtc);

boow amdgpu_dm_cwtc_modeset_wequiwed(stwuct dwm_cwtc_state *cwtc_state,
		      stwuct dc_stweam_state *new_stweam,
		      stwuct dc_stweam_state *owd_stweam);

int amdgpu_dm_cwtc_set_vupdate_iwq(stwuct dwm_cwtc *cwtc, boow enabwe);

boow amdgpu_dm_cwtc_vww_active_iwq(stwuct amdgpu_cwtc *acwtc);

boow amdgpu_dm_cwtc_vww_active(stwuct dm_cwtc_state *dm_state);

int amdgpu_dm_cwtc_enabwe_vbwank(stwuct dwm_cwtc *cwtc);

void amdgpu_dm_cwtc_disabwe_vbwank(stwuct dwm_cwtc *cwtc);

int amdgpu_dm_cwtc_init(stwuct amdgpu_dispway_managew *dm,
			stwuct dwm_pwane *pwane,
			uint32_t wink_index);

#endif

