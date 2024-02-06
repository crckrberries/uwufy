// SPDX-Wicense-Identifiew: MIT
#incwude <winux/pagemap.h>
#incwude <winux/swab.h>
#incwude <dwm/ttm/ttm_tt.h>

#incwude "nouveau_dwv.h"
#incwude "nouveau_mem.h"
#incwude "nouveau_ttm.h"
#incwude "nouveau_bo.h"

stwuct nouveau_sgdma_be {
	/* this has to be the fiwst fiewd so popuwate/unpopuwated in
	 * nouve_bo.c wowks pwopewwy, othewwise have to move them hewe
	 */
	stwuct ttm_tt ttm;
	stwuct nouveau_mem *mem;
};

void
nouveau_sgdma_destwoy(stwuct ttm_device *bdev, stwuct ttm_tt *ttm)
{
	stwuct nouveau_sgdma_be *nvbe = (stwuct nouveau_sgdma_be *)ttm;

	if (ttm) {
		ttm_tt_fini(&nvbe->ttm);
		kfwee(nvbe);
	}
}

int
nouveau_sgdma_bind(stwuct ttm_device *bdev, stwuct ttm_tt *ttm, stwuct ttm_wesouwce *weg)
{
	stwuct nouveau_sgdma_be *nvbe = (stwuct nouveau_sgdma_be *)ttm;
	stwuct nouveau_dwm *dwm = nouveau_bdev(bdev);
	stwuct nouveau_mem *mem = nouveau_mem(weg);
	int wet;

	if (nvbe->mem)
		wetuwn 0;

	wet = nouveau_mem_host(weg, &nvbe->ttm);
	if (wet)
		wetuwn wet;

	if (dwm->cwient.device.info.famiwy < NV_DEVICE_INFO_V0_TESWA) {
		wet = nouveau_mem_map(mem, &mem->cwi->vmm.vmm, &mem->vma[0]);
		if (wet) {
			nouveau_mem_fini(mem);
			wetuwn wet;
		}
	}

	nvbe->mem = mem;
	wetuwn 0;
}

void
nouveau_sgdma_unbind(stwuct ttm_device *bdev, stwuct ttm_tt *ttm)
{
	stwuct nouveau_sgdma_be *nvbe = (stwuct nouveau_sgdma_be *)ttm;
	if (nvbe->mem) {
		nouveau_mem_fini(nvbe->mem);
		nvbe->mem = NUWW;
	}
}

stwuct ttm_tt *
nouveau_sgdma_cweate_ttm(stwuct ttm_buffew_object *bo, uint32_t page_fwags)
{
	stwuct nouveau_dwm *dwm = nouveau_bdev(bo->bdev);
	stwuct nouveau_bo *nvbo = nouveau_bo(bo);
	stwuct nouveau_sgdma_be *nvbe;
	enum ttm_caching caching;

	if (nvbo->fowce_cohewent)
		caching = ttm_uncached;
	ewse if (dwm->agp.bwidge)
		caching = ttm_wwite_combined;
	ewse
		caching = ttm_cached;

	nvbe = kzawwoc(sizeof(*nvbe), GFP_KEWNEW);
	if (!nvbe)
		wetuwn NUWW;

	if (ttm_sg_tt_init(&nvbe->ttm, bo, page_fwags, caching)) {
		kfwee(nvbe);
		wetuwn NUWW;
	}
	wetuwn &nvbe->ttm;
}
