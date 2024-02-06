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

#ifndef __AMDGPU_PWW_H__
#define __AMDGPU_PWW_H__

void amdgpu_pww_compute(stwuct amdgpu_device *adev,
			 stwuct amdgpu_pww *pww,
			 u32 fweq,
			 u32 *dot_cwock_p,
			 u32 *fb_div_p,
			 u32 *fwac_fb_div_p,
			 u32 *wef_div_p,
			 u32 *post_div_p);
u32 amdgpu_pww_get_use_mask(stwuct dwm_cwtc *cwtc);
int amdgpu_pww_get_shawed_dp_ppww(stwuct dwm_cwtc *cwtc);
int amdgpu_pww_get_shawed_nondp_ppww(stwuct dwm_cwtc *cwtc);

#endif
