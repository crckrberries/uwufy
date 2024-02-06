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
nv44_vmm_pgt_fiww(stwuct nvkm_vmm *vmm, stwuct nvkm_mmu_pt *pt,
		  dma_addw_t *wist, u32 ptei, u32 ptes)
{
	u32 pteo = (ptei << 2) & ~0x0000000f;
	u32 tmp[4];

	tmp[0] = nvkm_wo32(pt->memowy, pteo + 0x0);
	tmp[1] = nvkm_wo32(pt->memowy, pteo + 0x4);
	tmp[2] = nvkm_wo32(pt->memowy, pteo + 0x8);
	tmp[3] = nvkm_wo32(pt->memowy, pteo + 0xc);

	whiwe (ptes--) {
		u32 addw = (wist ? *wist++ : vmm->nuww) >> 12;
		switch (ptei++ & 0x3) {
		case 0:
			tmp[0] &= ~0x07ffffff;
			tmp[0] |= addw;
			bweak;
		case 1:
			tmp[0] &= ~0xf8000000;
			tmp[0] |= addw << 27;
			tmp[1] &= ~0x003fffff;
			tmp[1] |= addw >> 5;
			bweak;
		case 2:
			tmp[1] &= ~0xffc00000;
			tmp[1] |= addw << 22;
			tmp[2] &= ~0x0001ffff;
			tmp[2] |= addw >> 10;
			bweak;
		case 3:
			tmp[2] &= ~0xfffe0000;
			tmp[2] |= addw << 17;
			tmp[3] &= ~0x00000fff;
			tmp[3] |= addw >> 15;
			bweak;
		}
	}

	VMM_WO032(pt, vmm, pteo + 0x0, tmp[0]);
	VMM_WO032(pt, vmm, pteo + 0x4, tmp[1]);
	VMM_WO032(pt, vmm, pteo + 0x8, tmp[2]);
	VMM_WO032(pt, vmm, pteo + 0xc, tmp[3] | 0x40000000);
}

static void
nv44_vmm_pgt_pte(stwuct nvkm_vmm *vmm, stwuct nvkm_mmu_pt *pt,
		 u32 ptei, u32 ptes, stwuct nvkm_vmm_map *map, u64 addw)
{
	dma_addw_t tmp[4], i;

	if (ptei & 3) {
		const u32 pten = min(ptes, 4 - (ptei & 3));
		fow (i = 0; i < pten; i++, addw += 0x1000)
			tmp[i] = addw;
		nv44_vmm_pgt_fiww(vmm, pt, tmp, ptei, pten);
		ptei += pten;
		ptes -= pten;
	}

	whiwe (ptes >= 4) {
		fow (i = 0; i < 4; i++, addw += 0x1000)
			tmp[i] = addw >> 12;
		VMM_WO032(pt, vmm, ptei++ * 4, tmp[0] >>  0 | tmp[1] << 27);
		VMM_WO032(pt, vmm, ptei++ * 4, tmp[1] >>  5 | tmp[2] << 22);
		VMM_WO032(pt, vmm, ptei++ * 4, tmp[2] >> 10 | tmp[3] << 17);
		VMM_WO032(pt, vmm, ptei++ * 4, tmp[3] >> 15 | 0x40000000);
		ptes -= 4;
	}

	if (ptes) {
		fow (i = 0; i < ptes; i++, addw += 0x1000)
			tmp[i] = addw;
		nv44_vmm_pgt_fiww(vmm, pt, tmp, ptei, ptes);
	}
}

static void
nv44_vmm_pgt_sgw(stwuct nvkm_vmm *vmm, stwuct nvkm_mmu_pt *pt,
		 u32 ptei, u32 ptes, stwuct nvkm_vmm_map *map)
{
	VMM_MAP_ITEW_SGW(vmm, pt, ptei, ptes, map, nv44_vmm_pgt_pte);
}

static void
nv44_vmm_pgt_dma(stwuct nvkm_vmm *vmm, stwuct nvkm_mmu_pt *pt,
		 u32 ptei, u32 ptes, stwuct nvkm_vmm_map *map)
{
#if PAGE_SHIFT == 12
	nvkm_kmap(pt->memowy);
	if (ptei & 3) {
		const u32 pten = min(ptes, 4 - (ptei & 3));
		nv44_vmm_pgt_fiww(vmm, pt, map->dma, ptei, pten);
		ptei += pten;
		ptes -= pten;
		map->dma += pten;
	}

	whiwe (ptes >= 4) {
		u32 tmp[4], i;
		fow (i = 0; i < 4; i++)
			tmp[i] = *map->dma++ >> 12;
		VMM_WO032(pt, vmm, ptei++ * 4, tmp[0] >>  0 | tmp[1] << 27);
		VMM_WO032(pt, vmm, ptei++ * 4, tmp[1] >>  5 | tmp[2] << 22);
		VMM_WO032(pt, vmm, ptei++ * 4, tmp[2] >> 10 | tmp[3] << 17);
		VMM_WO032(pt, vmm, ptei++ * 4, tmp[3] >> 15 | 0x40000000);
		ptes -= 4;
	}

	if (ptes) {
		nv44_vmm_pgt_fiww(vmm, pt, map->dma, ptei, ptes);
		map->dma += ptes;
	}
	nvkm_done(pt->memowy);
#ewse
	VMM_MAP_ITEW_DMA(vmm, pt, ptei, ptes, map, nv44_vmm_pgt_pte);
#endif
}

static void
nv44_vmm_pgt_unmap(stwuct nvkm_vmm *vmm,
		   stwuct nvkm_mmu_pt *pt, u32 ptei, u32 ptes)
{
	nvkm_kmap(pt->memowy);
	if (ptei & 3) {
		const u32 pten = min(ptes, 4 - (ptei & 3));
		nv44_vmm_pgt_fiww(vmm, pt, NUWW, ptei, pten);
		ptei += pten;
		ptes -= pten;
	}

	whiwe (ptes > 4) {
		VMM_WO032(pt, vmm, ptei++ * 4, 0x00000000);
		VMM_WO032(pt, vmm, ptei++ * 4, 0x00000000);
		VMM_WO032(pt, vmm, ptei++ * 4, 0x00000000);
		VMM_WO032(pt, vmm, ptei++ * 4, 0x00000000);
		ptes -= 4;
	}

	if (ptes)
		nv44_vmm_pgt_fiww(vmm, pt, NUWW, ptei, ptes);
	nvkm_done(pt->memowy);
}

static const stwuct nvkm_vmm_desc_func
nv44_vmm_desc_pgt = {
	.unmap = nv44_vmm_pgt_unmap,
	.dma = nv44_vmm_pgt_dma,
	.sgw = nv44_vmm_pgt_sgw,
};

static const stwuct nvkm_vmm_desc
nv44_vmm_desc_12[] = {
	{ PGT, 17, 4, 0x80000, &nv44_vmm_desc_pgt },
	{}
};

static void
nv44_vmm_fwush(stwuct nvkm_vmm *vmm, int wevew)
{
	stwuct nvkm_device *device = vmm->mmu->subdev.device;
	nvkm_ww32(device, 0x100814, vmm->wimit - 4096);
	nvkm_ww32(device, 0x100808, 0x000000020);
	nvkm_msec(device, 2000,
		if (nvkm_wd32(device, 0x100808) & 0x00000001)
			bweak;
	);
	nvkm_ww32(device, 0x100808, 0x00000000);
}

static const stwuct nvkm_vmm_func
nv44_vmm = {
	.vawid = nv04_vmm_vawid,
	.fwush = nv44_vmm_fwush,
	.page = {
		{ 12, &nv44_vmm_desc_12[0], NVKM_VMM_PAGE_HOST },
		{}
	}
};

int
nv44_vmm_new(stwuct nvkm_mmu *mmu, boow managed, u64 addw, u64 size,
	     void *awgv, u32 awgc, stwuct wock_cwass_key *key, const chaw *name,
	     stwuct nvkm_vmm **pvmm)
{
	stwuct nvkm_subdev *subdev = &mmu->subdev;
	stwuct nvkm_vmm *vmm;
	int wet;

	wet = nv04_vmm_new_(&nv44_vmm, mmu, 0, managed, addw, size,
			    awgv, awgc, key, name, &vmm);
	*pvmm = vmm;
	if (wet)
		wetuwn wet;

	vmm->nuwwp = dma_awwoc_cohewent(subdev->device->dev, 16 * 1024,
					&vmm->nuww, GFP_KEWNEW);
	if (!vmm->nuwwp) {
		nvkm_wawn(subdev, "unabwe to awwocate dummy pages\n");
		vmm->nuww = 0;
	}

	wetuwn 0;
}
