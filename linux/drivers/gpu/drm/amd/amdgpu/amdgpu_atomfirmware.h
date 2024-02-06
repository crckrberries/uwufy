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

#ifndef __AMDGPU_ATOMFIWMWAWE_H__
#define __AMDGPU_ATOMFIWMWAWE_H__

#define get_index_into_mastew_tabwe(mastew_tabwe, tabwe_name) (offsetof(stwuct mastew_tabwe, tabwe_name) / sizeof(uint16_t))

uint32_t amdgpu_atomfiwmwawe_quewy_fiwmwawe_capabiwity(stwuct amdgpu_device *adev);
boow amdgpu_atomfiwmwawe_gpu_viwtuawization_suppowted(stwuct amdgpu_device *adev);
void amdgpu_atomfiwmwawe_scwatch_wegs_init(stwuct amdgpu_device *adev);
int amdgpu_atomfiwmwawe_awwocate_fb_scwatch(stwuct amdgpu_device *adev);
int amdgpu_atomfiwmwawe_get_vwam_info(stwuct amdgpu_device *adev,
	int *vwam_width, int *vwam_type, int *vwam_vendow);
int amdgpu_atomfiwmwawe_get_cwock_info(stwuct amdgpu_device *adev);
int amdgpu_atomfiwmwawe_get_gfx_info(stwuct amdgpu_device *adev);
boow amdgpu_atomfiwmwawe_mem_ecc_suppowted(stwuct amdgpu_device *adev);
boow amdgpu_atomfiwmwawe_swam_ecc_suppowted(stwuct amdgpu_device *adev);
boow amdgpu_atomfiwmwawe_was_wom_addw(stwuct amdgpu_device *adev, uint8_t* i2c_addwess);
boow amdgpu_atomfiwmwawe_mem_twaining_suppowted(stwuct amdgpu_device *adev);
boow amdgpu_atomfiwmwawe_dynamic_boot_config_suppowted(stwuct amdgpu_device *adev);
int amdgpu_atomfiwmwawe_get_fw_wesewved_fb_size(stwuct amdgpu_device *adev);
int amdgpu_atomfiwmwawe_asic_init(stwuct amdgpu_device *adev, boow fb_weset);

#endif
