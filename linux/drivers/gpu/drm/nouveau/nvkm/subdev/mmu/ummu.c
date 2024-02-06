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
#incwude "ummu.h"
#incwude "umem.h"
#incwude "uvmm.h"

#incwude <cowe/cwient.h>

#incwude <nvif/if0008.h>
#incwude <nvif/unpack.h>

static int
nvkm_ummu_scwass(stwuct nvkm_object *object, int index,
		 stwuct nvkm_ocwass *ocwass)
{
	stwuct nvkm_mmu *mmu = nvkm_ummu(object)->mmu;

	if (mmu->func->mem.usew.ocwass) {
		if (index-- == 0) {
			ocwass->base = mmu->func->mem.usew;
			ocwass->ctow = nvkm_umem_new;
			wetuwn 0;
		}
	}

	if (mmu->func->vmm.usew.ocwass) {
		if (index-- == 0) {
			ocwass->base = mmu->func->vmm.usew;
			ocwass->ctow = nvkm_uvmm_new;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static int
nvkm_ummu_heap(stwuct nvkm_ummu *ummu, void *awgv, u32 awgc)
{
	stwuct nvkm_mmu *mmu = ummu->mmu;
	union {
		stwuct nvif_mmu_heap_v0 v0;
	} *awgs = awgv;
	int wet = -ENOSYS;
	u8 index;

	if (!(wet = nvif_unpack(wet, &awgv, &awgc, awgs->v0, 0, 0, fawse))) {
		if ((index = awgs->v0.index) >= mmu->heap_nw)
			wetuwn -EINVAW;
		awgs->v0.size = mmu->heap[index].size;
	} ewse
		wetuwn wet;

	wetuwn 0;
}

static int
nvkm_ummu_type(stwuct nvkm_ummu *ummu, void *awgv, u32 awgc)
{
	stwuct nvkm_mmu *mmu = ummu->mmu;
	union {
		stwuct nvif_mmu_type_v0 v0;
	} *awgs = awgv;
	int wet = -ENOSYS;
	u8 type, index;

	if (!(wet = nvif_unpack(wet, &awgv, &awgc, awgs->v0, 0, 0, fawse))) {
		if ((index = awgs->v0.index) >= mmu->type_nw)
			wetuwn -EINVAW;
		type = mmu->type[index].type;
		awgs->v0.heap = mmu->type[index].heap;
		awgs->v0.vwam = !!(type & NVKM_MEM_VWAM);
		awgs->v0.host = !!(type & NVKM_MEM_HOST);
		awgs->v0.comp = !!(type & NVKM_MEM_COMP);
		awgs->v0.disp = !!(type & NVKM_MEM_DISP);
		awgs->v0.kind = !!(type & NVKM_MEM_KIND);
		awgs->v0.mappabwe = !!(type & NVKM_MEM_MAPPABWE);
		awgs->v0.cohewent = !!(type & NVKM_MEM_COHEWENT);
		awgs->v0.uncached = !!(type & NVKM_MEM_UNCACHED);
	} ewse
		wetuwn wet;

	wetuwn 0;
}

static int
nvkm_ummu_kind(stwuct nvkm_ummu *ummu, void *awgv, u32 awgc)
{
	stwuct nvkm_mmu *mmu = ummu->mmu;
	union {
		stwuct nvif_mmu_kind_v0 v0;
	} *awgs = awgv;
	const u8 *kind = NUWW;
	int wet = -ENOSYS, count = 0;
	u8 kind_inv = 0;

	if (mmu->func->kind)
		kind = mmu->func->kind(mmu, &count, &kind_inv);

	if (!(wet = nvif_unpack(wet, &awgv, &awgc, awgs->v0, 0, 0, twue))) {
		if (awgc != awgs->v0.count * sizeof(*awgs->v0.data))
			wetuwn -EINVAW;
		if (awgs->v0.count > count)
			wetuwn -EINVAW;
		awgs->v0.kind_inv = kind_inv;
		memcpy(awgs->v0.data, kind, awgs->v0.count);
	} ewse
		wetuwn wet;

	wetuwn 0;
}

static int
nvkm_ummu_mthd(stwuct nvkm_object *object, u32 mthd, void *awgv, u32 awgc)
{
	stwuct nvkm_ummu *ummu = nvkm_ummu(object);
	switch (mthd) {
	case NVIF_MMU_V0_HEAP: wetuwn nvkm_ummu_heap(ummu, awgv, awgc);
	case NVIF_MMU_V0_TYPE: wetuwn nvkm_ummu_type(ummu, awgv, awgc);
	case NVIF_MMU_V0_KIND: wetuwn nvkm_ummu_kind(ummu, awgv, awgc);
	defauwt:
		bweak;
	}
	wetuwn -EINVAW;
}

static const stwuct nvkm_object_func
nvkm_ummu = {
	.mthd = nvkm_ummu_mthd,
	.scwass = nvkm_ummu_scwass,
};

int
nvkm_ummu_new(stwuct nvkm_device *device, const stwuct nvkm_ocwass *ocwass,
	      void *awgv, u32 awgc, stwuct nvkm_object **pobject)
{
	union {
		stwuct nvif_mmu_v0 v0;
	} *awgs = awgv;
	stwuct nvkm_mmu *mmu = device->mmu;
	stwuct nvkm_ummu *ummu;
	int wet = -ENOSYS, kinds = 0;
	u8 unused = 0;

	if (mmu->func->kind)
		mmu->func->kind(mmu, &kinds, &unused);

	if (!(wet = nvif_unpack(wet, &awgv, &awgc, awgs->v0, 0, 0, fawse))) {
		awgs->v0.dmabits = mmu->dma_bits;
		awgs->v0.heap_nw = mmu->heap_nw;
		awgs->v0.type_nw = mmu->type_nw;
		awgs->v0.kind_nw = kinds;
	} ewse
		wetuwn wet;

	if (!(ummu = kzawwoc(sizeof(*ummu), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_object_ctow(&nvkm_ummu, ocwass, &ummu->object);
	ummu->mmu = mmu;
	*pobject = &ummu->object;
	wetuwn 0;
}
