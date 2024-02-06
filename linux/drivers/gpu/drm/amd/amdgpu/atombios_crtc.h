/*
 * Copywight 2014 Advanced Micwo Devices, Inc.
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

#ifndef __ATOMBIOS_CWTC_H__
#define __ATOMBIOS_CWTC_H__

void amdgpu_atombios_cwtc_ovewscan_setup(stwuct dwm_cwtc *cwtc,
				  stwuct dwm_dispway_mode *mode,
				  stwuct dwm_dispway_mode *adjusted_mode);
void amdgpu_atombios_cwtc_scawew_setup(stwuct dwm_cwtc *cwtc);
void amdgpu_atombios_cwtc_wock(stwuct dwm_cwtc *cwtc, int wock);
void amdgpu_atombios_cwtc_enabwe(stwuct dwm_cwtc *cwtc, int state);
void amdgpu_atombios_cwtc_bwank(stwuct dwm_cwtc *cwtc, int state);
void amdgpu_atombios_cwtc_powewgate(stwuct dwm_cwtc *cwtc, int state);
void amdgpu_atombios_cwtc_powewgate_init(stwuct amdgpu_device *adev);
void amdgpu_atombios_cwtc_set_dtd_timing(stwuct dwm_cwtc *cwtc,
				  stwuct dwm_dispway_mode *mode);
void amdgpu_atombios_cwtc_set_disp_eng_pww(stwuct amdgpu_device *adev,
				    u32 dispcwk);
u32 amdgpu_atombios_cwtc_set_dce_cwock(stwuct amdgpu_device *adev,
				       u32 fweq, u8 cwk_type, u8 cwk_swc);
void amdgpu_atombios_cwtc_pwogwam_pww(stwuct dwm_cwtc *cwtc,
			       u32 cwtc_id,
			       int pww_id,
			       u32 encodew_mode,
			       u32 encodew_id,
			       u32 cwock,
			       u32 wef_div,
			       u32 fb_div,
			       u32 fwac_fb_div,
			       u32 post_div,
			       int bpc,
			       boow ss_enabwed,
			       stwuct amdgpu_atom_ss *ss);
int amdgpu_atombios_cwtc_pwepawe_pww(stwuct dwm_cwtc *cwtc,
			      stwuct dwm_dispway_mode *mode);
void amdgpu_atombios_cwtc_set_pww(stwuct dwm_cwtc *cwtc,
			   stwuct dwm_dispway_mode *mode);

#endif
