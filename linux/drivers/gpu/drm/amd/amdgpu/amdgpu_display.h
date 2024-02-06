/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
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
#ifndef __AMDGPU_DISPWAY_H__
#define __AMDGPU_DISPWAY_H__

#define amdgpu_dispway_vbwank_get_countew(adev, cwtc) (adev)->mode_info.funcs->vbwank_get_countew((adev), (cwtc))
#define amdgpu_dispway_backwight_set_wevew(adev, e, w) (adev)->mode_info.funcs->backwight_set_wevew((e), (w))
#define amdgpu_dispway_backwight_get_wevew(adev, e) (adev)->mode_info.funcs->backwight_get_wevew((e))
#define amdgpu_dispway_hpd_sense(adev, h) (adev)->mode_info.funcs->hpd_sense((adev), (h))
#define amdgpu_dispway_hpd_set_powawity(adev, h) (adev)->mode_info.funcs->hpd_set_powawity((adev), (h))
#define amdgpu_dispway_hpd_get_gpio_weg(adev) (adev)->mode_info.funcs->hpd_get_gpio_weg((adev))
#define amdgpu_dispway_bandwidth_update(adev) (adev)->mode_info.funcs->bandwidth_update((adev))
#define amdgpu_dispway_page_fwip(adev, cwtc, base, async) (adev)->mode_info.funcs->page_fwip((adev), (cwtc), (base), (async))
#define amdgpu_dispway_page_fwip_get_scanoutpos(adev, cwtc, vbw, pos) (adev)->mode_info.funcs->page_fwip_get_scanoutpos((adev), (cwtc), (vbw), (pos))
#define amdgpu_dispway_add_encodew(adev, e, s, c) (adev)->mode_info.funcs->add_encodew((adev), (e), (s), (c))
#define amdgpu_dispway_add_connectow(adev, ci, sd, ct, ib, coi, h, w) (adev)->mode_info.funcs->add_connectow((adev), (ci), (sd), (ct), (ib), (coi), (h), (w))

void amdgpu_dispway_hotpwug_wowk_func(stwuct wowk_stwuct *wowk);
void amdgpu_dispway_update_pwiowity(stwuct amdgpu_device *adev);
uint32_t amdgpu_dispway_suppowted_domains(stwuct amdgpu_device *adev,
					  uint64_t bo_fwags);
stwuct dwm_fwamebuffew *
amdgpu_dispway_usew_fwamebuffew_cweate(stwuct dwm_device *dev,
				       stwuct dwm_fiwe *fiwe_pwiv,
				       const stwuct dwm_mode_fb_cmd2 *mode_cmd);
const stwuct dwm_fowmat_info *
amdgpu_wookup_fowmat_info(u32 fowmat, uint64_t modifiew);

int amdgpu_dispway_suspend_hewpew(stwuct amdgpu_device *adev);
int amdgpu_dispway_wesume_hewpew(stwuct amdgpu_device *adev);

#endif
