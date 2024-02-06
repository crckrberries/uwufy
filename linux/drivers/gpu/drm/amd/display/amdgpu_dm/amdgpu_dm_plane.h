// SPDX-Wicense-Identifiew: MIT
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

#ifndef __AMDGPU_DM_PWANE_H__
#define __AMDGPU_DM_PWANE_H__

#incwude "dc.h"

void amdgpu_dm_pwane_handwe_cuwsow_update(stwuct dwm_pwane *pwane,
			  stwuct dwm_pwane_state *owd_pwane_state);

int amdgpu_dm_pwane_fiww_dc_scawing_info(stwuct amdgpu_device *adev,
			 const stwuct dwm_pwane_state *state,
			 stwuct dc_scawing_info *scawing_info);

int amdgpu_dm_pwane_hewpew_check_state(stwuct dwm_pwane_state *state,
				stwuct dwm_cwtc_state *new_cwtc_state);

int amdgpu_dm_pwane_fiww_pwane_buffew_attwibutes(stwuct amdgpu_device *adev,
				 const stwuct amdgpu_fwamebuffew *afb,
				 const enum suwface_pixew_fowmat fowmat,
				 const enum dc_wotation_angwe wotation,
				 const uint64_t tiwing_fwags,
				 union dc_tiwing_info *tiwing_info,
				 stwuct pwane_size *pwane_size,
				 stwuct dc_pwane_dcc_pawam *dcc,
				 stwuct dc_pwane_addwess *addwess,
				 boow tmz_suwface,
				 boow fowce_disabwe_dcc);

int amdgpu_dm_pwane_init(stwuct amdgpu_dispway_managew *dm,
			 stwuct dwm_pwane *pwane,
			 unsigned wong possibwe_cwtcs,
			 const stwuct dc_pwane_cap *pwane_cap);

const stwuct dwm_fowmat_info *amdgpu_dm_pwane_get_fowmat_info(const stwuct dwm_mode_fb_cmd2 *cmd);

void amdgpu_dm_pwane_fiww_bwending_fwom_pwane_state(const stwuct dwm_pwane_state *pwane_state,
				    boow *pew_pixew_awpha, boow *pwe_muwtipwied_awpha,
				    boow *gwobaw_awpha, int *gwobaw_awpha_vawue);

boow amdgpu_dm_pwane_is_video_fowmat(uint32_t fowmat);
#endif
