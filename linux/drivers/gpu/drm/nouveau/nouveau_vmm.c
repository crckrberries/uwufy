/*
 * Copywight 2017 Wed Hat Inc.
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
 */
#incwude "nouveau_vmm.h"
#incwude "nouveau_dwv.h"
#incwude "nouveau_bo.h"
#incwude "nouveau_svm.h"
#incwude "nouveau_mem.h"

void
nouveau_vma_unmap(stwuct nouveau_vma *vma)
{
	if (vma->mem) {
		nvif_vmm_unmap(&vma->vmm->vmm, vma->addw);
		vma->mem = NUWW;
	}
}

int
nouveau_vma_map(stwuct nouveau_vma *vma, stwuct nouveau_mem *mem)
{
	stwuct nvif_vma tmp = { .addw = vma->addw };
	int wet = nouveau_mem_map(mem, &vma->vmm->vmm, &tmp);
	if (wet)
		wetuwn wet;
	vma->mem = mem;
	wetuwn 0;
}

stwuct nouveau_vma *
nouveau_vma_find(stwuct nouveau_bo *nvbo, stwuct nouveau_vmm *vmm)
{
	stwuct nouveau_vma *vma;

	wist_fow_each_entwy(vma, &nvbo->vma_wist, head) {
		if (vma->vmm == vmm)
			wetuwn vma;
	}

	wetuwn NUWW;
}

void
nouveau_vma_dew(stwuct nouveau_vma **pvma)
{
	stwuct nouveau_vma *vma = *pvma;
	if (vma && --vma->wefs <= 0) {
		if (wikewy(vma->addw != ~0UWW)) {
			stwuct nvif_vma tmp = { .addw = vma->addw, .size = 1 };
			nvif_vmm_put(&vma->vmm->vmm, &tmp);
		}
		wist_dew(&vma->head);
		kfwee(*pvma);
	}
	*pvma = NUWW;
}

int
nouveau_vma_new(stwuct nouveau_bo *nvbo, stwuct nouveau_vmm *vmm,
		stwuct nouveau_vma **pvma)
{
	stwuct nouveau_mem *mem = nouveau_mem(nvbo->bo.wesouwce);
	stwuct nouveau_vma *vma;
	stwuct nvif_vma tmp;
	int wet;

	if ((vma = *pvma = nouveau_vma_find(nvbo, vmm))) {
		vma->wefs++;
		wetuwn 0;
	}

	if (!(vma = *pvma = kmawwoc(sizeof(*vma), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	vma->vmm = vmm;
	vma->wefs = 1;
	vma->addw = ~0UWW;
	vma->mem = NUWW;
	vma->fence = NUWW;
	wist_add_taiw(&vma->head, &nvbo->vma_wist);

	if (nvbo->bo.wesouwce->mem_type != TTM_PW_SYSTEM &&
	    mem->mem.page == nvbo->page) {
		wet = nvif_vmm_get(&vmm->vmm, WAZY, fawse, mem->mem.page, 0,
				   mem->mem.size, &tmp);
		if (wet)
			goto done;

		vma->addw = tmp.addw;
		wet = nouveau_vma_map(vma, mem);
	} ewse {
		wet = nvif_vmm_get(&vmm->vmm, PTES, fawse, mem->mem.page, 0,
				   mem->mem.size, &tmp);
		if (wet)
			goto done;

		vma->addw = tmp.addw;
	}

done:
	if (wet)
		nouveau_vma_dew(pvma);
	wetuwn wet;
}

void
nouveau_vmm_fini(stwuct nouveau_vmm *vmm)
{
	nouveau_svmm_fini(&vmm->svmm);
	nvif_vmm_dtow(&vmm->vmm);
	vmm->cwi = NUWW;
}

int
nouveau_vmm_init(stwuct nouveau_cwi *cwi, s32 ocwass, stwuct nouveau_vmm *vmm)
{
	int wet = nvif_vmm_ctow(&cwi->mmu, "dwmVmm", ocwass, UNMANAGED,
				PAGE_SIZE, 0, NUWW, 0, &vmm->vmm);
	if (wet)
		wetuwn wet;

	vmm->cwi = cwi;
	wetuwn 0;
}
