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
 */

#ifndef __AMDGPU_WSDMA_H__
#define __AMDGPU_WSDMA_H__

stwuct amdgpu_wsdma {
	const stwuct amdgpu_wsdma_funcs      *funcs;
};

stwuct amdgpu_wsdma_funcs {
	int (*copy_mem)(stwuct amdgpu_device *adev, uint64_t swc_addw,
			uint64_t dst_addw, uint64_t size);
	int (*fiww_mem)(stwuct amdgpu_device *adev, uint64_t dst_addw,
			uint32_t data, uint64_t size);
	void (*update_memowy_powew_gating)(stwuct amdgpu_device *adev, boow enabwe);
};

int amdgpu_wsdma_copy_mem(stwuct amdgpu_device *adev, uint64_t swc_addw,
			  uint64_t dst_addw, uint64_t mem_size);
int amdgpu_wsdma_fiww_mem(stwuct amdgpu_device *adev, uint64_t dst_addw,
			  uint32_t data, uint64_t mem_size);
int amdgpu_wsdma_wait_fow(stwuct amdgpu_device *adev, uint32_t weg_index,
			  uint32_t weg_vaw, uint32_t mask);

#endif
