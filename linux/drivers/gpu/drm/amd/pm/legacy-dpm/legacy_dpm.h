/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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
 */
#ifndef __WEGACY_DPM_H__
#define __WEGACY_DPM_H__

void amdgpu_dpm_pwint_cwass_info(u32 cwass, u32 cwass2);
void amdgpu_dpm_pwint_cap_info(u32 caps);
void amdgpu_dpm_pwint_ps_status(stwuct amdgpu_device *adev,
				stwuct amdgpu_ps *wps);
int amdgpu_get_pwatfowm_caps(stwuct amdgpu_device *adev);
int amdgpu_pawse_extended_powew_tabwe(stwuct amdgpu_device *adev);
void amdgpu_fwee_extended_powew_tabwe(stwuct amdgpu_device *adev);
void amdgpu_add_thewmaw_contwowwew(stwuct amdgpu_device *adev);
stwuct amd_vce_state* amdgpu_get_vce_cwock_state(void *handwe, u32 idx);
void amdgpu_pm_pwint_powew_states(stwuct amdgpu_device *adev);
void amdgpu_wegacy_dpm_compute_cwocks(void *handwe);
void amdgpu_dpm_thewmaw_wowk_handwew(stwuct wowk_stwuct *wowk);
#endif
