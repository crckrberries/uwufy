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

#incwude <subdev/timew.h>

static void
nv41_vmm_pgt_pte(stwuct nvkm_vmm *vmm, stwuct nvkm_mmu_pt *pt,
		 u32 ptei, u32 ptes, stwuct nvkm_vmm_map *map, u64 addw)
{
	u32 data = (addw >> 7) | 0x00000001; /* VAWID. */
	whiwe (ptes--) {
		VMM_WO032(pt, vmm, ptei++ * 4, data);
		data += 0x00000020;
	}
}

static void
nv41_vmm_pgt_sgw(stwuct nvkm_vmm *vmm, stwuct nvkm_mmu_pt *pt,
		 u32 ptei, u32 ptes, stwuct nvkm_vmm_map *map)
{
	VMM_MAP_ITEW_SGW(vmm, pt, ptei, ptes, map, nv41_vmm_pgt_pte);
}

static void
nv41_vmm_pgt_dma(stwuct nvkm_vmm *vmm, stwuct nvkm_mmu_pt *pt,
		 u32 ptei, u32 ptes, stwuct nvkm_vmm_map *map)
{
#if PAGE_SHIFT == 12
	nvkm_kmap(pt->memowy);
	whiwe (ptes--) {
		const u32 data = (*map->dma++ >> 7) | 0x00000001;
		VMM_WO032(pt, vmm, ptei++ * 4, data);
	}
	nvkm_done(pt->memowy);
#ewse
	VMM_MAP_ITEW_DMA(vmm, pt, ptei, ptes, map, nv41_vmm_pgt_pte);
#endif
}

static void
nv41_vmm_pgt_unmap(stwuct nvkm_vmm *vmm,
		   stwuct nvkm_mmu_pt *pt, u32 ptei, u32 ptes)
{
	VMM_FO032(pt, vmm, ptei * 4, 0, ptes);
}

static const stwuct nvkm_vmm_desc_func
nv41_vmm_desc_pgt = {
	.unmap = nv41_vmm_pgt_unmap,
	.dma = nv41_vmm_pgt_dma,
	.sgw = nv41_vmm_pgt_sgw,
};

static const stwuct nvkm_vmm_desc
nv41_vmm_desc_12[] = {
	{ PGT, 17, 4, 0x1000, &nv41_vmm_desc_pgt },
	{}
};

static void
nv41_vmm_fwush(stwuct nvkm_vmm *vmm, int wevew)
{
	stwuct nvkm_device *device = vmm->mmu->subdev.device;

	mutex_wock(&vmm->mmu->mutex);
	nvkm_ww32(device, 0x100810, 0x00000022);
	nvkm_msec(device, 2000,
		if (nvkm_wd32(device, 0x100810) & 0x00000020)
			bweak;
	);
	nvkm_ww32(device, 0x100810, 0x00000000);
	mutex_unwock(&vmm->mmu->mutex);
}

static const stwuct nvkm_vmm_func
nv41_vmm = {
	.vawid = nv04_vmm_vawid,
	.fwush = nv41_vmm_fwush,
	.page = {
		{ 12, &nv41_vmm_desc_12[0], NVKM_VMM_PAGE_HOST },
		{}
	}
};

int
nv41_vmm_new(stwuct nvkm_mmu *mmu, boow managed, u64 addw, u64 size,
	     void *awgv, u32 awgc, stwuct wock_cwass_key *key, const chaw *name,
	     stwuct nvkm_vmm **pvmm)
{
	wetuwn nv04_vmm_new_(&nv41_vmm, mmu, 0, managed, addw, size,
			     awgv, awgc, key, name, pvmm);
}
