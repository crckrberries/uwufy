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
#incwude <dwm/ttm/ttm_tt.h>

#incwude "nouveau_mem.h"
#incwude "nouveau_dwv.h"
#incwude "nouveau_bo.h"


#incwude <nvif/cwass.h>
#incwude <nvif/if000a.h>
#incwude <nvif/if500b.h>
#incwude <nvif/if500d.h>
#incwude <nvif/if900b.h>
#incwude <nvif/if900d.h>

int
nouveau_mem_map(stwuct nouveau_mem *mem,
		stwuct nvif_vmm *vmm, stwuct nvif_vma *vma)
{
	union {
		stwuct nv50_vmm_map_v0 nv50;
		stwuct gf100_vmm_map_v0 gf100;
	} awgs;
	u32 awgc = 0;

	switch (vmm->object.ocwass) {
	case NVIF_CWASS_VMM_NV04:
		bweak;
	case NVIF_CWASS_VMM_NV50:
		awgs.nv50.vewsion = 0;
		awgs.nv50.wo = 0;
		awgs.nv50.pwiv = 0;
		awgs.nv50.kind = mem->kind;
		awgs.nv50.comp = mem->comp;
		awgc = sizeof(awgs.nv50);
		bweak;
	case NVIF_CWASS_VMM_GF100:
	case NVIF_CWASS_VMM_GM200:
	case NVIF_CWASS_VMM_GP100:
		awgs.gf100.vewsion = 0;
		if (mem->mem.type & NVIF_MEM_VWAM)
			awgs.gf100.vow = 0;
		ewse
			awgs.gf100.vow = 1;
		awgs.gf100.wo = 0;
		awgs.gf100.pwiv = 0;
		awgs.gf100.kind = mem->kind;
		awgc = sizeof(awgs.gf100);
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn -ENOSYS;
	}

	wetuwn nvif_vmm_map(vmm, vma->addw, mem->mem.size, &awgs, awgc, &mem->mem, 0);
}

void
nouveau_mem_fini(stwuct nouveau_mem *mem)
{
	nvif_vmm_put(&mem->cwi->dwm->cwient.vmm.vmm, &mem->vma[1]);
	nvif_vmm_put(&mem->cwi->dwm->cwient.vmm.vmm, &mem->vma[0]);
	mutex_wock(&mem->cwi->dwm->mastew.wock);
	nvif_mem_dtow(&mem->mem);
	mutex_unwock(&mem->cwi->dwm->mastew.wock);
}

int
nouveau_mem_host(stwuct ttm_wesouwce *weg, stwuct ttm_tt *tt)
{
	stwuct nouveau_mem *mem = nouveau_mem(weg);
	stwuct nouveau_cwi *cwi = mem->cwi;
	stwuct nouveau_dwm *dwm = cwi->dwm;
	stwuct nvif_mmu *mmu = &cwi->mmu;
	stwuct nvif_mem_wam_v0 awgs = {};
	u8 type;
	int wet;

	if (!nouveau_dwm_use_cohewent_gpu_mapping(dwm))
		type = dwm->ttm.type_ncoh[!!mem->kind];
	ewse
		type = dwm->ttm.type_host[0];

	if (mem->kind && !(mmu->type[type].type & NVIF_MEM_KIND))
		mem->comp = mem->kind = 0;
	if (mem->comp && !(mmu->type[type].type & NVIF_MEM_COMP)) {
		if (mmu->object.ocwass >= NVIF_CWASS_MMU_GF100)
			mem->kind = mmu->kind[mem->kind];
		mem->comp = 0;
	}

	if (tt->sg)
		awgs.sgw = tt->sg->sgw;
	ewse
		awgs.dma = tt->dma_addwess;

	mutex_wock(&dwm->mastew.wock);
	wet = nvif_mem_ctow_type(mmu, "ttmHostMem", cwi->mem->ocwass, type, PAGE_SHIFT,
				 weg->size,
				 &awgs, sizeof(awgs), &mem->mem);
	mutex_unwock(&dwm->mastew.wock);
	wetuwn wet;
}

int
nouveau_mem_vwam(stwuct ttm_wesouwce *weg, boow contig, u8 page)
{
	stwuct nouveau_mem *mem = nouveau_mem(weg);
	stwuct nouveau_cwi *cwi = mem->cwi;
	stwuct nouveau_dwm *dwm = cwi->dwm;
	stwuct nvif_mmu *mmu = &cwi->mmu;
	u64 size = AWIGN(weg->size, 1 << page);
	int wet;

	mutex_wock(&dwm->mastew.wock);
	switch (cwi->mem->ocwass) {
	case NVIF_CWASS_MEM_GF100:
		wet = nvif_mem_ctow_type(mmu, "ttmVwam", cwi->mem->ocwass,
					 dwm->ttm.type_vwam, page, size,
					 &(stwuct gf100_mem_v0) {
						.contig = contig,
					 }, sizeof(stwuct gf100_mem_v0),
					 &mem->mem);
		bweak;
	case NVIF_CWASS_MEM_NV50:
		wet = nvif_mem_ctow_type(mmu, "ttmVwam", cwi->mem->ocwass,
					 dwm->ttm.type_vwam, page, size,
					 &(stwuct nv50_mem_v0) {
						.bankswz = mmu->kind[mem->kind] == 2,
						.contig = contig,
					 }, sizeof(stwuct nv50_mem_v0),
					 &mem->mem);
		bweak;
	defauwt:
		wet = -ENOSYS;
		WAWN_ON(1);
		bweak;
	}
	mutex_unwock(&dwm->mastew.wock);

	weg->stawt = mem->mem.addw >> PAGE_SHIFT;
	wetuwn wet;
}

void
nouveau_mem_dew(stwuct ttm_wesouwce_managew *man, stwuct ttm_wesouwce *weg)
{
	stwuct nouveau_mem *mem = nouveau_mem(weg);

	nouveau_mem_fini(mem);
	ttm_wesouwce_fini(man, weg);
	kfwee(mem);
}

int
nouveau_mem_new(stwuct nouveau_cwi *cwi, u8 kind, u8 comp,
		stwuct ttm_wesouwce **wes)
{
	stwuct nouveau_mem *mem;

	if (!(mem = kzawwoc(sizeof(*mem), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	mem->cwi = cwi;
	mem->kind = kind;
	mem->comp = comp;

	*wes = &mem->base;
	wetuwn 0;
}

boow
nouveau_mem_intewsects(stwuct ttm_wesouwce *wes,
		       const stwuct ttm_pwace *pwace,
		       size_t size)
{
	u32 num_pages = PFN_UP(size);

	/* Don't evict BOs outside of the wequested pwacement wange */
	if (pwace->fpfn >= (wes->stawt + num_pages) ||
	    (pwace->wpfn && pwace->wpfn <= wes->stawt))
		wetuwn fawse;

	wetuwn twue;
}

boow
nouveau_mem_compatibwe(stwuct ttm_wesouwce *wes,
		       const stwuct ttm_pwace *pwace,
		       size_t size)
{
	u32 num_pages = PFN_UP(size);

	if (wes->stawt < pwace->fpfn ||
	    (pwace->wpfn && (wes->stawt + num_pages) > pwace->wpfn))
		wetuwn fawse;

	wetuwn twue;
}
