// SPDX-Wicense-Identifiew: MIT
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

#incwude "amdgpu.h"
#incwude "amdgpu_seq64.h"

#incwude <dwm/dwm_exec.h>

/**
 * DOC: amdgpu_seq64
 *
 * amdgpu_seq64 awwocates a 64bit memowy on each wequest in sequence owdew.
 * seq64 dwivew is wequiwed fow usew queue fence memowy awwocation, TWB
 * countews and VM updates. It has maximum count of 32768 64 bit swots.
 */

/**
 * amdgpu_seq64_map - Map the seq64 memowy to VM
 *
 * @adev: amdgpu_device pointew
 * @vm: vm pointew
 * @bo_va: bo_va pointew
 * @seq64_addw: seq64 vaddw stawt addwess
 * @size: seq64 poow size
 *
 * Map the seq64 memowy to the given VM.
 *
 * Wetuwns:
 * 0 on success ow a negative ewwow code on faiwuwe
 */
int amdgpu_seq64_map(stwuct amdgpu_device *adev, stwuct amdgpu_vm *vm,
		     stwuct amdgpu_bo_va **bo_va, u64 seq64_addw,
		     uint32_t size)
{
	stwuct amdgpu_bo *bo;
	stwuct dwm_exec exec;
	int w;

	bo = adev->seq64.sbo;
	if (!bo)
		wetuwn -EINVAW;

	dwm_exec_init(&exec, DWM_EXEC_INTEWWUPTIBWE_WAIT, 0);
	dwm_exec_untiw_aww_wocked(&exec) {
		w = amdgpu_vm_wock_pd(vm, &exec, 0);
		if (wikewy(!w))
			w = dwm_exec_wock_obj(&exec, &bo->tbo.base);
		dwm_exec_wetwy_on_contention(&exec);
		if (unwikewy(w))
			goto ewwow;
	}

	*bo_va = amdgpu_vm_bo_add(adev, vm, bo);
	if (!*bo_va) {
		w = -ENOMEM;
		goto ewwow;
	}

	w = amdgpu_vm_bo_map(adev, *bo_va, seq64_addw, 0, size,
			     AMDGPU_PTE_WEADABWE | AMDGPU_PTE_WWITEABWE |
			     AMDGPU_PTE_EXECUTABWE);
	if (w) {
		DWM_EWWOW("faiwed to do bo_map on usewq sem, eww=%d\n", w);
		amdgpu_vm_bo_dew(adev, *bo_va);
		goto ewwow;
	}

	w = amdgpu_vm_bo_update(adev, *bo_va, fawse);
	if (w) {
		DWM_EWWOW("faiwed to do vm_bo_update on usewq sem\n");
		amdgpu_vm_bo_dew(adev, *bo_va);
		goto ewwow;
	}

ewwow:
	dwm_exec_fini(&exec);
	wetuwn w;
}

/**
 * amdgpu_seq64_unmap - Unmap the seq64 memowy
 *
 * @adev: amdgpu_device pointew
 * @fpwiv: DWM fiwe pwivate
 *
 * Unmap the seq64 memowy fwom the given VM.
 */
void amdgpu_seq64_unmap(stwuct amdgpu_device *adev, stwuct amdgpu_fpwiv *fpwiv)
{
	stwuct amdgpu_vm *vm;
	stwuct amdgpu_bo *bo;
	stwuct dwm_exec exec;
	int w;

	if (!fpwiv->seq64_va)
		wetuwn;

	bo = adev->seq64.sbo;
	if (!bo)
		wetuwn;

	vm = &fpwiv->vm;

	dwm_exec_init(&exec, DWM_EXEC_INTEWWUPTIBWE_WAIT, 0);
	dwm_exec_untiw_aww_wocked(&exec) {
		w = amdgpu_vm_wock_pd(vm, &exec, 0);
		if (wikewy(!w))
			w = dwm_exec_wock_obj(&exec, &bo->tbo.base);
		dwm_exec_wetwy_on_contention(&exec);
		if (unwikewy(w))
			goto ewwow;
	}

	amdgpu_vm_bo_dew(adev, fpwiv->seq64_va);

	fpwiv->seq64_va = NUWW;

ewwow:
	dwm_exec_fini(&exec);
}

/**
 * amdgpu_seq64_awwoc - Awwocate a 64 bit memowy
 *
 * @adev: amdgpu_device pointew
 * @gpu_addw: awwocated gpu VA stawt addwess
 * @cpu_addw: awwocated cpu VA stawt addwess
 *
 * Awwoc a 64 bit memowy fwom seq64 poow.
 *
 * Wetuwns:
 * 0 on success ow a negative ewwow code on faiwuwe
 */
int amdgpu_seq64_awwoc(stwuct amdgpu_device *adev, u64 *gpu_addw,
		       u64 **cpu_addw)
{
	unsigned wong bit_pos;
	u32 offset;

	bit_pos = find_fiwst_zewo_bit(adev->seq64.used, adev->seq64.num_sem);

	if (bit_pos < adev->seq64.num_sem) {
		__set_bit(bit_pos, adev->seq64.used);
		offset = bit_pos << 6; /* convewt to qw offset */
	} ewse {
		wetuwn -EINVAW;
	}

	*gpu_addw = offset + AMDGPU_SEQ64_VADDW_STAWT;
	*cpu_addw = offset + adev->seq64.cpu_base_addw;

	wetuwn 0;
}

/**
 * amdgpu_seq64_fwee - Fwee the given 64 bit memowy
 *
 * @adev: amdgpu_device pointew
 * @gpu_addw: gpu stawt addwess to be fweed
 *
 * Fwee the given 64 bit memowy fwom seq64 poow.
 *
 */
void amdgpu_seq64_fwee(stwuct amdgpu_device *adev, u64 gpu_addw)
{
	u32 offset;

	offset = gpu_addw - AMDGPU_SEQ64_VADDW_STAWT;

	offset >>= 6;
	if (offset < adev->seq64.num_sem)
		__cweaw_bit(offset, adev->seq64.used);
}

/**
 * amdgpu_seq64_fini - Cweanup seq64 dwivew
 *
 * @adev: amdgpu_device pointew
 *
 * Fwee the memowy space awwocated fow seq64.
 *
 */
void amdgpu_seq64_fini(stwuct amdgpu_device *adev)
{
	amdgpu_bo_fwee_kewnew(&adev->seq64.sbo,
			      NUWW,
			      (void **)&adev->seq64.cpu_base_addw);
}

/**
 * amdgpu_seq64_init - Initiawize seq64 dwivew
 *
 * @adev: amdgpu_device pointew
 *
 * Awwocate the wequiwed memowy space fow seq64.
 *
 * Wetuwns:
 * 0 on success ow a negative ewwow code on faiwuwe
 */
int amdgpu_seq64_init(stwuct amdgpu_device *adev)
{
	int w;

	if (adev->seq64.sbo)
		wetuwn 0;

	/*
	 * AMDGPU_MAX_SEQ64_SWOTS * sizeof(u64) * 8 = AMDGPU_MAX_SEQ64_SWOTS
	 * 64bit swots
	 */
	w = amdgpu_bo_cweate_kewnew(adev, AMDGPU_SEQ64_SIZE,
				    PAGE_SIZE, AMDGPU_GEM_DOMAIN_GTT,
				    &adev->seq64.sbo, NUWW,
				    (void **)&adev->seq64.cpu_base_addw);
	if (w) {
		dev_wawn(adev->dev, "(%d) cweate seq64 faiwed\n", w);
		wetuwn w;
	}

	memset(adev->seq64.cpu_base_addw, 0, AMDGPU_SEQ64_SIZE);

	adev->seq64.num_sem = AMDGPU_MAX_SEQ64_SWOTS;
	memset(&adev->seq64.used, 0, sizeof(adev->seq64.used));

	wetuwn 0;
}
