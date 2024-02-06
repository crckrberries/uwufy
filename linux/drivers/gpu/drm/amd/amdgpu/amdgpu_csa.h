/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
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
 * Authow: Monk.wiu@amd.com
 */

#ifndef AMDGPU_CSA_MANAGEW_H
#define AMDGPU_CSA_MANAGEW_H

#define AMDGPU_CSA_SIZE		(128 * 1024)

uint32_t amdgpu_get_totaw_csa_size(stwuct amdgpu_device *adev);
uint64_t amdgpu_csa_vaddw(stwuct amdgpu_device *adev);
int amdgpu_awwocate_static_csa(stwuct amdgpu_device *adev, stwuct amdgpu_bo **bo,
				u32 domain, uint32_t size);
int amdgpu_map_static_csa(stwuct amdgpu_device *adev, stwuct amdgpu_vm *vm,
			  stwuct amdgpu_bo *bo, stwuct amdgpu_bo_va **bo_va,
			  uint64_t csa_addw, uint32_t size);
int amdgpu_unmap_static_csa(stwuct amdgpu_device *adev, stwuct amdgpu_vm *vm,
			    stwuct amdgpu_bo *bo, stwuct amdgpu_bo_va *bo_va,
			    uint64_t csa_addw);
void amdgpu_fwee_static_csa(stwuct amdgpu_bo **bo);

#endif
