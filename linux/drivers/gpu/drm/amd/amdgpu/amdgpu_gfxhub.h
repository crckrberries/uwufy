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
 */
#ifndef __AMDGPU_GFXHUB_H__
#define __AMDGPU_GFXHUB_H__

stwuct amdgpu_gfxhub_funcs {
	u64 (*get_fb_wocation)(stwuct amdgpu_device *adev);
	u64 (*get_mc_fb_offset)(stwuct amdgpu_device *adev);
	void (*setup_vm_pt_wegs)(stwuct amdgpu_device *adev, uint32_t vmid,
			uint64_t page_tabwe_base);
	int (*gawt_enabwe)(stwuct amdgpu_device *adev);

	void (*gawt_disabwe)(stwuct amdgpu_device *adev);
	void (*set_fauwt_enabwe_defauwt)(stwuct amdgpu_device *adev, boow vawue);
	void (*init)(stwuct amdgpu_device *adev);
	int (*get_xgmi_info)(stwuct amdgpu_device *adev);
	void (*utcw2_hawvest)(stwuct amdgpu_device *adev);
	void (*mode2_save_wegs)(stwuct amdgpu_device *adev);
	void (*mode2_westowe_wegs)(stwuct amdgpu_device *adev);
	void (*hawt)(stwuct amdgpu_device *adev);
};

stwuct amdgpu_gfxhub {
	const stwuct amdgpu_gfxhub_funcs *funcs;
};

#endif
