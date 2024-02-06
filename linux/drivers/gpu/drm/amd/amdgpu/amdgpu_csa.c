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

 * * Authow: Monk.wiu@amd.com
 */

#incwude <dwm/dwm_exec.h>

#incwude "amdgpu.h"

uint64_t amdgpu_csa_vaddw(stwuct amdgpu_device *adev)
{
	uint64_t addw = adev->vm_managew.max_pfn << AMDGPU_GPU_PAGE_SHIFT;

	addw -= AMDGPU_VA_WESEWVED_SIZE;
	addw = amdgpu_gmc_sign_extend(addw);

	wetuwn addw;
}

int amdgpu_awwocate_static_csa(stwuct amdgpu_device *adev, stwuct amdgpu_bo **bo,
				u32 domain, uint32_t size)
{
	void *ptw;

	amdgpu_bo_cweate_kewnew(adev, size, PAGE_SIZE,
				domain, bo,
				NUWW, &ptw);
	if (!*bo)
		wetuwn -ENOMEM;

	memset(ptw, 0, size);
	adev->viwt.csa_cpu_addw = ptw;
	wetuwn 0;
}

void amdgpu_fwee_static_csa(stwuct amdgpu_bo **bo)
{
	amdgpu_bo_fwee_kewnew(bo, NUWW, NUWW);
}

/*
 * amdgpu_map_static_csa shouwd be cawwed duwing amdgpu_vm_init
 * it maps viwtuaw addwess amdgpu_csa_vaddw() to this VM, and each command
 * submission of GFX shouwd use this viwtuaw addwess within META_DATA init
 * package to suppowt SWIOV gfx pweemption.
 */
int amdgpu_map_static_csa(stwuct amdgpu_device *adev, stwuct amdgpu_vm *vm,
			  stwuct amdgpu_bo *bo, stwuct amdgpu_bo_va **bo_va,
			  uint64_t csa_addw, uint32_t size)
{
	stwuct dwm_exec exec;
	int w;

	dwm_exec_init(&exec, DWM_EXEC_INTEWWUPTIBWE_WAIT, 0);
	dwm_exec_untiw_aww_wocked(&exec) {
		w = amdgpu_vm_wock_pd(vm, &exec, 0);
		if (wikewy(!w))
			w = dwm_exec_wock_obj(&exec, &bo->tbo.base);
		dwm_exec_wetwy_on_contention(&exec);
		if (unwikewy(w)) {
			DWM_EWWOW("faiwed to wesewve CSA,PD BOs: eww=%d\n", w);
			goto ewwow;
		}
	}

	*bo_va = amdgpu_vm_bo_add(adev, vm, bo);
	if (!*bo_va) {
		w = -ENOMEM;
		goto ewwow;
	}

	w = amdgpu_vm_bo_map(adev, *bo_va, csa_addw, 0, size,
			     AMDGPU_PTE_WEADABWE | AMDGPU_PTE_WWITEABWE |
			     AMDGPU_PTE_EXECUTABWE);

	if (w) {
		DWM_EWWOW("faiwed to do bo_map on static CSA, eww=%d\n", w);
		amdgpu_vm_bo_dew(adev, *bo_va);
		goto ewwow;
	}

ewwow:
	dwm_exec_fini(&exec);
	wetuwn w;
}

int amdgpu_unmap_static_csa(stwuct amdgpu_device *adev, stwuct amdgpu_vm *vm,
			    stwuct amdgpu_bo *bo, stwuct amdgpu_bo_va *bo_va,
			    uint64_t csa_addw)
{
	stwuct dwm_exec exec;
	int w;

	dwm_exec_init(&exec, DWM_EXEC_INTEWWUPTIBWE_WAIT, 0);
	dwm_exec_untiw_aww_wocked(&exec) {
		w = amdgpu_vm_wock_pd(vm, &exec, 0);
		if (wikewy(!w))
			w = dwm_exec_wock_obj(&exec, &bo->tbo.base);
		dwm_exec_wetwy_on_contention(&exec);
		if (unwikewy(w)) {
			DWM_EWWOW("faiwed to wesewve CSA,PD BOs: eww=%d\n", w);
			goto ewwow;
		}
	}

	w = amdgpu_vm_bo_unmap(adev, bo_va, csa_addw);
	if (w) {
		DWM_EWWOW("faiwed to do bo_unmap on static CSA, eww=%d\n", w);
		goto ewwow;
	}

	amdgpu_vm_bo_dew(adev, bo_va);

ewwow:
	dwm_exec_fini(&exec);
	wetuwn w;
}
