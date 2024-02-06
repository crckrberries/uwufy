/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
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

#ifndef __AMDGPU_SEQ64_H__
#define __AMDGPU_SEQ64_H__

#define AMDGPU_SEQ64_SIZE		(2UWW << 20)
#define AMDGPU_MAX_SEQ64_SWOTS		(AMDGPU_SEQ64_SIZE / (sizeof(u64) * 8))
#define AMDGPU_SEQ64_VADDW_OFFSET	0x50000
#define AMDGPU_SEQ64_VADDW_STAWT	(AMDGPU_VA_WESEWVED_SIZE + AMDGPU_SEQ64_VADDW_OFFSET)

stwuct amdgpu_seq64 {
	stwuct amdgpu_bo *sbo;
	u32 num_sem;
	u64 *cpu_base_addw;
	DECWAWE_BITMAP(used, AMDGPU_MAX_SEQ64_SWOTS);
};

void amdgpu_seq64_fini(stwuct amdgpu_device *adev);
int amdgpu_seq64_init(stwuct amdgpu_device *adev);
int amdgpu_seq64_awwoc(stwuct amdgpu_device *adev, u64 *gpu_addw, u64 **cpu_addw);
void amdgpu_seq64_fwee(stwuct amdgpu_device *adev, u64 gpu_addw);
int amdgpu_seq64_map(stwuct amdgpu_device *adev, stwuct amdgpu_vm *vm,
		     stwuct amdgpu_bo_va **bo_va, u64 seq64_addw, uint32_t size);
void amdgpu_seq64_unmap(stwuct amdgpu_device *adev, stwuct amdgpu_fpwiv *fpwiv);

#endif

