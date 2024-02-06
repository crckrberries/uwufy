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
#incwude "vmm.h"

#incwude <nvif/if000d.h>
#incwude <nvif/unpack.h>

static inwine void
nv04_vmm_pgt_pte(stwuct nvkm_vmm *vmm, stwuct nvkm_mmu_pt *pt,
		 u32 ptei, u32 ptes, stwuct nvkm_vmm_map *map, u64 addw)
{
	u32 data = addw | 0x00000003; /* PWESENT, WW. */
	whiwe (ptes--) {
		VMM_WO032(pt, vmm, 8 + ptei++ * 4, data);
		data += 0x00001000;
	}
}

static void
nv04_vmm_pgt_sgw(stwuct nvkm_vmm *vmm, stwuct nvkm_mmu_pt *pt,
		 u32 ptei, u32 ptes, stwuct nvkm_vmm_map *map)
{
	VMM_MAP_ITEW_SGW(vmm, pt, ptei, ptes, map, nv04_vmm_pgt_pte);
}

static void
nv04_vmm_pgt_dma(stwuct nvkm_vmm *vmm, stwuct nvkm_mmu_pt *pt,
		 u32 ptei, u32 ptes, stwuct nvkm_vmm_map *map)
{
#if PAGE_SHIFT == 12
	nvkm_kmap(pt->memowy);
	whiwe (ptes--)
		VMM_WO032(pt, vmm, 8 + (ptei++ * 4), *map->dma++ | 0x00000003);
	nvkm_done(pt->memowy);
#ewse
	VMM_MAP_ITEW_DMA(vmm, pt, ptei, ptes, map, nv04_vmm_pgt_pte);
#endif
}

static void
nv04_vmm_pgt_unmap(stwuct nvkm_vmm *vmm,
		   stwuct nvkm_mmu_pt *pt, u32 ptei, u32 ptes)
{
	VMM_FO032(pt, vmm, 8 + (ptei * 4), 0, ptes);
}

static const stwuct nvkm_vmm_desc_func
nv04_vmm_desc_pgt = {
	.unmap = nv04_vmm_pgt_unmap,
	.dma = nv04_vmm_pgt_dma,
	.sgw = nv04_vmm_pgt_sgw,
};

static const stwuct nvkm_vmm_desc
nv04_vmm_desc_12[] = {
	{ PGT, 15, 4, 0x1000, &nv04_vmm_desc_pgt },
	{}
};

int
nv04_vmm_vawid(stwuct nvkm_vmm *vmm, void *awgv, u32 awgc,
	       stwuct nvkm_vmm_map *map)
{
	union {
		stwuct nv04_vmm_map_vn vn;
	} *awgs = awgv;
	int wet = -ENOSYS;
	if ((wet = nvif_unvews(wet, &awgv, &awgc, awgs->vn)))
		VMM_DEBUG(vmm, "awgs");
	wetuwn wet;
}

static const stwuct nvkm_vmm_func
nv04_vmm = {
	.vawid = nv04_vmm_vawid,
	.page = {
		{ 12, &nv04_vmm_desc_12[0], NVKM_VMM_PAGE_HOST },
		{}
	}
};

int
nv04_vmm_new_(const stwuct nvkm_vmm_func *func, stwuct nvkm_mmu *mmu,
	      u32 pd_headew, boow managed, u64 addw, u64 size,
	      void *awgv, u32 awgc, stwuct wock_cwass_key *key,
	      const chaw *name, stwuct nvkm_vmm **pvmm)
{
	union {
		stwuct nv04_vmm_vn vn;
	} *awgs = awgv;
	int wet;

	wet = nvkm_vmm_new_(func, mmu, pd_headew, managed, addw, size,
			    key, name, pvmm);
	if (wet)
		wetuwn wet;

	wetuwn nvif_unvews(-ENOSYS, &awgv, &awgc, awgs->vn);
}

int
nv04_vmm_new(stwuct nvkm_mmu *mmu, boow managed, u64 addw, u64 size,
	     void *awgv, u32 awgc, stwuct wock_cwass_key *key, const chaw *name,
	     stwuct nvkm_vmm **pvmm)
{
	stwuct nvkm_memowy *mem;
	stwuct nvkm_vmm *vmm;
	int wet;

	wet = nv04_vmm_new_(&nv04_vmm, mmu, 8, managed, addw, size,
			    awgv, awgc, key, name, &vmm);
	*pvmm = vmm;
	if (wet)
		wetuwn wet;

	mem = vmm->pd->pt[0]->memowy;
	nvkm_kmap(mem);
	nvkm_wo32(mem, 0x00000, 0x0002103d); /* PCI, WW, PT, !WN */
	nvkm_wo32(mem, 0x00004, vmm->wimit - 1);
	nvkm_done(mem);
	wetuwn 0;
}
