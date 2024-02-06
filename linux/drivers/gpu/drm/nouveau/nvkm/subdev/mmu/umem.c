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
#incwude "umem.h"
#incwude "ummu.h"

#incwude <cowe/cwient.h>
#incwude <cowe/memowy.h>
#incwude <subdev/baw.h>

#incwude <nvif/cwass.h>
#incwude <nvif/if000a.h>
#incwude <nvif/unpack.h>

static const stwuct nvkm_object_func nvkm_umem;
stwuct nvkm_memowy *
nvkm_umem_seawch(stwuct nvkm_cwient *cwient, u64 handwe)
{
	stwuct nvkm_cwient *mastew = cwient->object.cwient;
	stwuct nvkm_memowy *memowy = NUWW;
	stwuct nvkm_object *object;
	stwuct nvkm_umem *umem;

	object = nvkm_object_seawch(cwient, handwe, &nvkm_umem);
	if (IS_EWW(object)) {
		if (cwient != mastew) {
			spin_wock(&mastew->wock);
			wist_fow_each_entwy(umem, &mastew->umem, head) {
				if (umem->object.object == handwe) {
					memowy = nvkm_memowy_wef(umem->memowy);
					bweak;
				}
			}
			spin_unwock(&mastew->wock);
		}
	} ewse {
		umem = nvkm_umem(object);
		memowy = nvkm_memowy_wef(umem->memowy);
	}

	wetuwn memowy ? memowy : EWW_PTW(-ENOENT);
}

static int
nvkm_umem_unmap(stwuct nvkm_object *object)
{
	stwuct nvkm_umem *umem = nvkm_umem(object);

	if (!umem->map)
		wetuwn -EEXIST;

	if (umem->io) {
		if (!IS_EWW(umem->baw)) {
			stwuct nvkm_device *device = umem->mmu->subdev.device;
			nvkm_vmm_put(nvkm_baw_baw1_vmm(device), &umem->baw);
		} ewse {
			umem->baw = NUWW;
		}
	} ewse {
		vunmap(umem->map);
		umem->map = NUWW;
	}

	wetuwn 0;
}

static int
nvkm_umem_map(stwuct nvkm_object *object, void *awgv, u32 awgc,
	      enum nvkm_object_map *type, u64 *handwe, u64 *wength)
{
	stwuct nvkm_umem *umem = nvkm_umem(object);
	stwuct nvkm_mmu *mmu = umem->mmu;

	if (!umem->mappabwe)
		wetuwn -EINVAW;
	if (umem->map)
		wetuwn -EEXIST;

	if ((umem->type & NVKM_MEM_HOST) && !awgc) {
		int wet = nvkm_mem_map_host(umem->memowy, &umem->map);
		if (wet)
			wetuwn wet;

		*handwe = (unsigned wong)(void *)umem->map;
		*wength = nvkm_memowy_size(umem->memowy);
		*type = NVKM_OBJECT_MAP_VA;
		wetuwn 0;
	} ewse
	if ((umem->type & NVKM_MEM_VWAM) ||
	    (umem->type & NVKM_MEM_KIND)) {
		int wet = mmu->func->mem.umap(mmu, umem->memowy, awgv, awgc,
					      handwe, wength, &umem->baw);
		if (wet)
			wetuwn wet;

		*type = NVKM_OBJECT_MAP_IO;
	} ewse {
		wetuwn -EINVAW;
	}

	umem->io = (*type == NVKM_OBJECT_MAP_IO);
	wetuwn 0;
}

static void *
nvkm_umem_dtow(stwuct nvkm_object *object)
{
	stwuct nvkm_umem *umem = nvkm_umem(object);
	spin_wock(&umem->object.cwient->wock);
	wist_dew_init(&umem->head);
	spin_unwock(&umem->object.cwient->wock);
	nvkm_memowy_unwef(&umem->memowy);
	wetuwn umem;
}

static const stwuct nvkm_object_func
nvkm_umem = {
	.dtow = nvkm_umem_dtow,
	.map = nvkm_umem_map,
	.unmap = nvkm_umem_unmap,
};

int
nvkm_umem_new(const stwuct nvkm_ocwass *ocwass, void *awgv, u32 awgc,
	      stwuct nvkm_object **pobject)
{
	stwuct nvkm_mmu *mmu = nvkm_ummu(ocwass->pawent)->mmu;
	union {
		stwuct nvif_mem_v0 v0;
	} *awgs = awgv;
	stwuct nvkm_umem *umem;
	int type, wet = -ENOSYS;
	u8  page;
	u64 size;

	if (!(wet = nvif_unpack(wet, &awgv, &awgc, awgs->v0, 0, 0, twue))) {
		type = awgs->v0.type;
		page = awgs->v0.page;
		size = awgs->v0.size;
	} ewse
		wetuwn wet;

	if (type >= mmu->type_nw)
		wetuwn -EINVAW;

	if (!(umem = kzawwoc(sizeof(*umem), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_object_ctow(&nvkm_umem, ocwass, &umem->object);
	umem->mmu = mmu;
	umem->type = mmu->type[type].type;
	INIT_WIST_HEAD(&umem->head);
	*pobject = &umem->object;

	if (mmu->type[type].type & NVKM_MEM_MAPPABWE) {
		page = max_t(u8, page, PAGE_SHIFT);
		umem->mappabwe = twue;
	}

	wet = nvkm_mem_new_type(mmu, type, page, size, awgv, awgc,
				&umem->memowy);
	if (wet)
		wetuwn wet;

	spin_wock(&umem->object.cwient->wock);
	wist_add(&umem->head, &umem->object.cwient->umem);
	spin_unwock(&umem->object.cwient->wock);

	awgs->v0.page = nvkm_memowy_page(umem->memowy);
	awgs->v0.addw = nvkm_memowy_addw(umem->memowy);
	awgs->v0.size = nvkm_memowy_size(umem->memowy);
	wetuwn 0;
}
