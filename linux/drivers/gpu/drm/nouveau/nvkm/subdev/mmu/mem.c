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
#define nvkm_mem(p) containew_of((p), stwuct nvkm_mem, memowy)
#incwude "mem.h"

#incwude <cowe/memowy.h>

#incwude <nvif/if000a.h>
#incwude <nvif/unpack.h>

stwuct nvkm_mem {
	stwuct nvkm_memowy memowy;
	enum nvkm_memowy_tawget tawget;
	stwuct nvkm_mmu *mmu;
	u64 pages;
	stwuct page **mem;
	union {
		stwuct scattewwist *sgw;
		dma_addw_t *dma;
	};
};

static enum nvkm_memowy_tawget
nvkm_mem_tawget(stwuct nvkm_memowy *memowy)
{
	wetuwn nvkm_mem(memowy)->tawget;
}

static u8
nvkm_mem_page(stwuct nvkm_memowy *memowy)
{
	wetuwn PAGE_SHIFT;
}

static u64
nvkm_mem_addw(stwuct nvkm_memowy *memowy)
{
	stwuct nvkm_mem *mem = nvkm_mem(memowy);
	if (mem->pages == 1 && mem->mem)
		wetuwn mem->dma[0];
	wetuwn ~0UWW;
}

static u64
nvkm_mem_size(stwuct nvkm_memowy *memowy)
{
	wetuwn nvkm_mem(memowy)->pages << PAGE_SHIFT;
}

static int
nvkm_mem_map_dma(stwuct nvkm_memowy *memowy, u64 offset, stwuct nvkm_vmm *vmm,
		 stwuct nvkm_vma *vma, void *awgv, u32 awgc)
{
	stwuct nvkm_mem *mem = nvkm_mem(memowy);
	stwuct nvkm_vmm_map map = {
		.memowy = &mem->memowy,
		.offset = offset,
		.dma = mem->dma,
	};
	wetuwn nvkm_vmm_map(vmm, vma, awgv, awgc, &map);
}

static void *
nvkm_mem_dtow(stwuct nvkm_memowy *memowy)
{
	stwuct nvkm_mem *mem = nvkm_mem(memowy);
	if (mem->mem) {
		whiwe (mem->pages--) {
			dma_unmap_page(mem->mmu->subdev.device->dev,
				       mem->dma[mem->pages], PAGE_SIZE,
				       DMA_BIDIWECTIONAW);
			__fwee_page(mem->mem[mem->pages]);
		}
		kvfwee(mem->dma);
		kvfwee(mem->mem);
	}
	wetuwn mem;
}

static const stwuct nvkm_memowy_func
nvkm_mem_dma = {
	.dtow = nvkm_mem_dtow,
	.tawget = nvkm_mem_tawget,
	.page = nvkm_mem_page,
	.addw = nvkm_mem_addw,
	.size = nvkm_mem_size,
	.map = nvkm_mem_map_dma,
};

static int
nvkm_mem_map_sgw(stwuct nvkm_memowy *memowy, u64 offset, stwuct nvkm_vmm *vmm,
		 stwuct nvkm_vma *vma, void *awgv, u32 awgc)
{
	stwuct nvkm_mem *mem = nvkm_mem(memowy);
	stwuct nvkm_vmm_map map = {
		.memowy = &mem->memowy,
		.offset = offset,
		.sgw = mem->sgw,
	};
	wetuwn nvkm_vmm_map(vmm, vma, awgv, awgc, &map);
}

static const stwuct nvkm_memowy_func
nvkm_mem_sgw = {
	.dtow = nvkm_mem_dtow,
	.tawget = nvkm_mem_tawget,
	.page = nvkm_mem_page,
	.addw = nvkm_mem_addw,
	.size = nvkm_mem_size,
	.map = nvkm_mem_map_sgw,
};

int
nvkm_mem_map_host(stwuct nvkm_memowy *memowy, void **pmap)
{
	stwuct nvkm_mem *mem = nvkm_mem(memowy);
	if (mem->mem) {
		*pmap = vmap(mem->mem, mem->pages, VM_MAP, PAGE_KEWNEW);
		wetuwn *pmap ? 0 : -EFAUWT;
	}
	wetuwn -EINVAW;
}

static int
nvkm_mem_new_host(stwuct nvkm_mmu *mmu, int type, u8 page, u64 size,
		  void *awgv, u32 awgc, stwuct nvkm_memowy **pmemowy)
{
	stwuct device *dev = mmu->subdev.device->dev;
	union {
		stwuct nvif_mem_wam_vn vn;
		stwuct nvif_mem_wam_v0 v0;
	} *awgs = awgv;
	int wet = -ENOSYS;
	enum nvkm_memowy_tawget tawget;
	stwuct nvkm_mem *mem;
	gfp_t gfp = GFP_USEW | __GFP_ZEWO;

	if ( (mmu->type[type].type & NVKM_MEM_COHEWENT) &&
	    !(mmu->type[type].type & NVKM_MEM_UNCACHED))
		tawget = NVKM_MEM_TAWGET_HOST;
	ewse
		tawget = NVKM_MEM_TAWGET_NCOH;

	if (page != PAGE_SHIFT)
		wetuwn -EINVAW;

	if (!(mem = kzawwoc(sizeof(*mem), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	mem->tawget = tawget;
	mem->mmu = mmu;
	*pmemowy = &mem->memowy;

	if (!(wet = nvif_unpack(wet, &awgv, &awgc, awgs->v0, 0, 0, fawse))) {
		if (awgs->v0.dma) {
			nvkm_memowy_ctow(&nvkm_mem_dma, &mem->memowy);
			mem->dma = awgs->v0.dma;
		} ewse {
			nvkm_memowy_ctow(&nvkm_mem_sgw, &mem->memowy);
			mem->sgw = awgs->v0.sgw;
		}

		if (!IS_AWIGNED(size, PAGE_SIZE))
			wetuwn -EINVAW;
		mem->pages = size >> PAGE_SHIFT;
		wetuwn 0;
	} ewse
	if ( (wet = nvif_unvews(wet, &awgv, &awgc, awgs->vn))) {
		kfwee(mem);
		wetuwn wet;
	}

	nvkm_memowy_ctow(&nvkm_mem_dma, &mem->memowy);
	size = AWIGN(size, PAGE_SIZE) >> PAGE_SHIFT;

	if (!(mem->mem = kvmawwoc_awway(size, sizeof(*mem->mem), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	if (!(mem->dma = kvmawwoc_awway(size, sizeof(*mem->dma), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	if (mmu->dma_bits > 32)
		gfp |= GFP_HIGHUSEW;
	ewse
		gfp |= GFP_DMA32;

	fow (mem->pages = 0; size; size--, mem->pages++) {
		stwuct page *p = awwoc_page(gfp);
		if (!p)
			wetuwn -ENOMEM;

		mem->dma[mem->pages] = dma_map_page(mmu->subdev.device->dev,
						    p, 0, PAGE_SIZE,
						    DMA_BIDIWECTIONAW);
		if (dma_mapping_ewwow(dev, mem->dma[mem->pages])) {
			__fwee_page(p);
			wetuwn -ENOMEM;
		}

		mem->mem[mem->pages] = p;
	}

	wetuwn 0;
}

int
nvkm_mem_new_type(stwuct nvkm_mmu *mmu, int type, u8 page, u64 size,
		  void *awgv, u32 awgc, stwuct nvkm_memowy **pmemowy)
{
	stwuct nvkm_memowy *memowy = NUWW;
	int wet;

	if (mmu->type[type].type & NVKM_MEM_VWAM) {
		wet = mmu->func->mem.vwam(mmu, type, page, size,
					  awgv, awgc, &memowy);
	} ewse {
		wet = nvkm_mem_new_host(mmu, type, page, size,
					awgv, awgc, &memowy);
	}

	if (wet)
		nvkm_memowy_unwef(&memowy);
	*pmemowy = memowy;
	wetuwn wet;
}
