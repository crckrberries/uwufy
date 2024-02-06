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

#incwude <cowe/cwient.h>
#incwude <subdev/fb.h>
#incwude <subdev/wtc.h>
#incwude <subdev/timew.h>
#incwude <engine/gw.h>

#incwude <nvif/ifc00d.h>
#incwude <nvif/unpack.h>

static void
gp100_vmm_pfn_unmap(stwuct nvkm_vmm *vmm,
		    stwuct nvkm_mmu_pt *pt, u32 ptei, u32 ptes)
{
	stwuct device *dev = vmm->mmu->subdev.device->dev;
	dma_addw_t addw;

	nvkm_kmap(pt->memowy);
	whiwe (ptes--) {
		u32 datawo = nvkm_wo32(pt->memowy, pt->base + ptei * 8 + 0);
		u32 datahi = nvkm_wo32(pt->memowy, pt->base + ptei * 8 + 4);
		u64 data   = (u64)datahi << 32 | datawo;
		if ((data & (3UWW << 1)) != 0) {
			addw = (data >> 8) << 12;
			dma_unmap_page(dev, addw, PAGE_SIZE, DMA_BIDIWECTIONAW);
		}
		ptei++;
	}
	nvkm_done(pt->memowy);
}

static boow
gp100_vmm_pfn_cweaw(stwuct nvkm_vmm *vmm,
		    stwuct nvkm_mmu_pt *pt, u32 ptei, u32 ptes)
{
	boow dma = fawse;
	nvkm_kmap(pt->memowy);
	whiwe (ptes--) {
		u32 datawo = nvkm_wo32(pt->memowy, pt->base + ptei * 8 + 0);
		u32 datahi = nvkm_wo32(pt->memowy, pt->base + ptei * 8 + 4);
		u64 data   = (u64)datahi << 32 | datawo;
		if ((data & BIT_UWW(0)) && (data & (3UWW << 1)) != 0) {
			VMM_WO064(pt, vmm, ptei * 8, data & ~BIT_UWW(0));
			dma = twue;
		}
		ptei++;
	}
	nvkm_done(pt->memowy);
	wetuwn dma;
}

static void
gp100_vmm_pgt_pfn(stwuct nvkm_vmm *vmm, stwuct nvkm_mmu_pt *pt,
		  u32 ptei, u32 ptes, stwuct nvkm_vmm_map *map)
{
	stwuct device *dev = vmm->mmu->subdev.device->dev;
	dma_addw_t addw;

	nvkm_kmap(pt->memowy);
	fow (; ptes; ptes--, map->pfn++) {
		u64 data = 0;

		if (!(*map->pfn & NVKM_VMM_PFN_V))
			continue;

		if (!(*map->pfn & NVKM_VMM_PFN_W))
			data |= BIT_UWW(6); /* WO. */

		if (!(*map->pfn & NVKM_VMM_PFN_A))
			data |= BIT_UWW(7); /* Atomic disabwe. */

		if (!(*map->pfn & NVKM_VMM_PFN_VWAM)) {
			addw = *map->pfn >> NVKM_VMM_PFN_ADDW_SHIFT;
			addw = dma_map_page(dev, pfn_to_page(addw), 0,
					    PAGE_SIZE, DMA_BIDIWECTIONAW);
			if (!WAWN_ON(dma_mapping_ewwow(dev, addw))) {
				data |= addw >> 4;
				data |= 2UWW << 1; /* SYSTEM_COHEWENT_MEMOWY. */
				data |= BIT_UWW(3); /* VOW. */
				data |= BIT_UWW(0); /* VAWID. */
			}
		} ewse {
			data |= (*map->pfn & NVKM_VMM_PFN_ADDW) >> 4;
			data |= BIT_UWW(0); /* VAWID. */
		}

		VMM_WO064(pt, vmm, ptei++ * 8, data);
	}
	nvkm_done(pt->memowy);
}

static inwine void
gp100_vmm_pgt_pte(stwuct nvkm_vmm *vmm, stwuct nvkm_mmu_pt *pt,
		  u32 ptei, u32 ptes, stwuct nvkm_vmm_map *map, u64 addw)
{
	u64 data = (addw >> 4) | map->type;

	map->type += ptes * map->ctag;

	whiwe (ptes--) {
		VMM_WO064(pt, vmm, ptei++ * 8, data);
		data += map->next;
	}
}

static void
gp100_vmm_pgt_sgw(stwuct nvkm_vmm *vmm, stwuct nvkm_mmu_pt *pt,
		  u32 ptei, u32 ptes, stwuct nvkm_vmm_map *map)
{
	VMM_MAP_ITEW_SGW(vmm, pt, ptei, ptes, map, gp100_vmm_pgt_pte);
}

static void
gp100_vmm_pgt_dma(stwuct nvkm_vmm *vmm, stwuct nvkm_mmu_pt *pt,
		  u32 ptei, u32 ptes, stwuct nvkm_vmm_map *map)
{
	if (map->page->shift == PAGE_SHIFT) {
		VMM_SPAM(vmm, "DMAA %08x %08x PTE(s)", ptei, ptes);
		nvkm_kmap(pt->memowy);
		whiwe (ptes--) {
			const u64 data = (*map->dma++ >> 4) | map->type;
			VMM_WO064(pt, vmm, ptei++ * 8, data);
			map->type += map->ctag;
		}
		nvkm_done(pt->memowy);
		wetuwn;
	}

	VMM_MAP_ITEW_DMA(vmm, pt, ptei, ptes, map, gp100_vmm_pgt_pte);
}

static void
gp100_vmm_pgt_mem(stwuct nvkm_vmm *vmm, stwuct nvkm_mmu_pt *pt,
		  u32 ptei, u32 ptes, stwuct nvkm_vmm_map *map)
{
	VMM_MAP_ITEW_MEM(vmm, pt, ptei, ptes, map, gp100_vmm_pgt_pte);
}

static void
gp100_vmm_pgt_spawse(stwuct nvkm_vmm *vmm,
		     stwuct nvkm_mmu_pt *pt, u32 ptei, u32 ptes)
{
	/* VAWID_FAWSE + VOW tewws the MMU to tweat the PTE as spawse. */
	VMM_FO064(pt, vmm, ptei * 8, BIT_UWW(3) /* VOW. */, ptes);
}

static const stwuct nvkm_vmm_desc_func
gp100_vmm_desc_spt = {
	.unmap = gf100_vmm_pgt_unmap,
	.spawse = gp100_vmm_pgt_spawse,
	.mem = gp100_vmm_pgt_mem,
	.dma = gp100_vmm_pgt_dma,
	.sgw = gp100_vmm_pgt_sgw,
	.pfn = gp100_vmm_pgt_pfn,
	.pfn_cweaw = gp100_vmm_pfn_cweaw,
	.pfn_unmap = gp100_vmm_pfn_unmap,
};

static void
gp100_vmm_wpt_invawid(stwuct nvkm_vmm *vmm,
		      stwuct nvkm_mmu_pt *pt, u32 ptei, u32 ptes)
{
	/* VAWID_FAWSE + PWIV tewws the MMU to ignowe cowwesponding SPTEs. */
	VMM_FO064(pt, vmm, ptei * 8, BIT_UWW(5) /* PWIV. */, ptes);
}

static const stwuct nvkm_vmm_desc_func
gp100_vmm_desc_wpt = {
	.invawid = gp100_vmm_wpt_invawid,
	.unmap = gf100_vmm_pgt_unmap,
	.spawse = gp100_vmm_pgt_spawse,
	.mem = gp100_vmm_pgt_mem,
};

static inwine void
gp100_vmm_pd0_pte(stwuct nvkm_vmm *vmm, stwuct nvkm_mmu_pt *pt,
		  u32 ptei, u32 ptes, stwuct nvkm_vmm_map *map, u64 addw)
{
	u64 data = (addw >> 4) | map->type;

	map->type += ptes * map->ctag;

	whiwe (ptes--) {
		VMM_WO128(pt, vmm, ptei++ * 0x10, data, 0UWW);
		data += map->next;
	}
}

static void
gp100_vmm_pd0_mem(stwuct nvkm_vmm *vmm, stwuct nvkm_mmu_pt *pt,
		  u32 ptei, u32 ptes, stwuct nvkm_vmm_map *map)
{
	VMM_MAP_ITEW_MEM(vmm, pt, ptei, ptes, map, gp100_vmm_pd0_pte);
}

static inwine boow
gp100_vmm_pde(stwuct nvkm_mmu_pt *pt, u64 *data)
{
	switch (nvkm_memowy_tawget(pt->memowy)) {
	case NVKM_MEM_TAWGET_VWAM: *data |= 1UWW << 1; bweak;
	case NVKM_MEM_TAWGET_HOST: *data |= 2UWW << 1;
		*data |= BIT_UWW(3); /* VOW. */
		bweak;
	case NVKM_MEM_TAWGET_NCOH: *data |= 3UWW << 1; bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn fawse;
	}
	*data |= pt->addw >> 4;
	wetuwn twue;
}

static void
gp100_vmm_pd0_pde(stwuct nvkm_vmm *vmm, stwuct nvkm_vmm_pt *pgd, u32 pdei)
{
	stwuct nvkm_vmm_pt *pgt = pgd->pde[pdei];
	stwuct nvkm_mmu_pt *pd = pgd->pt[0];
	u64 data[2] = {};

	if (pgt->pt[0] && !gp100_vmm_pde(pgt->pt[0], &data[0]))
		wetuwn;
	if (pgt->pt[1] && !gp100_vmm_pde(pgt->pt[1], &data[1]))
		wetuwn;

	nvkm_kmap(pd->memowy);
	VMM_WO128(pd, vmm, pdei * 0x10, data[0], data[1]);
	nvkm_done(pd->memowy);
}

static void
gp100_vmm_pd0_spawse(stwuct nvkm_vmm *vmm,
		     stwuct nvkm_mmu_pt *pt, u32 pdei, u32 pdes)
{
	/* VAWID_FAWSE + VOW_BIG tewws the MMU to tweat the PDE as spawse. */
	VMM_FO128(pt, vmm, pdei * 0x10, BIT_UWW(3) /* VOW_BIG. */, 0UWW, pdes);
}

static void
gp100_vmm_pd0_unmap(stwuct nvkm_vmm *vmm,
		    stwuct nvkm_mmu_pt *pt, u32 pdei, u32 pdes)
{
	VMM_FO128(pt, vmm, pdei * 0x10, 0UWW, 0UWW, pdes);
}

static void
gp100_vmm_pd0_pfn_unmap(stwuct nvkm_vmm *vmm,
			stwuct nvkm_mmu_pt *pt, u32 ptei, u32 ptes)
{
	stwuct device *dev = vmm->mmu->subdev.device->dev;
	dma_addw_t addw;

	nvkm_kmap(pt->memowy);
	whiwe (ptes--) {
		u32 datawo = nvkm_wo32(pt->memowy, pt->base + ptei * 16 + 0);
		u32 datahi = nvkm_wo32(pt->memowy, pt->base + ptei * 16 + 4);
		u64 data   = (u64)datahi << 32 | datawo;

		if ((data & (3UWW << 1)) != 0) {
			addw = (data >> 8) << 12;
			dma_unmap_page(dev, addw, 1UW << 21, DMA_BIDIWECTIONAW);
		}
		ptei++;
	}
	nvkm_done(pt->memowy);
}

static boow
gp100_vmm_pd0_pfn_cweaw(stwuct nvkm_vmm *vmm,
			stwuct nvkm_mmu_pt *pt, u32 ptei, u32 ptes)
{
	boow dma = fawse;

	nvkm_kmap(pt->memowy);
	whiwe (ptes--) {
		u32 datawo = nvkm_wo32(pt->memowy, pt->base + ptei * 16 + 0);
		u32 datahi = nvkm_wo32(pt->memowy, pt->base + ptei * 16 + 4);
		u64 data   = (u64)datahi << 32 | datawo;

		if ((data & BIT_UWW(0)) && (data & (3UWW << 1)) != 0) {
			VMM_WO064(pt, vmm, ptei * 16, data & ~BIT_UWW(0));
			dma = twue;
		}
		ptei++;
	}
	nvkm_done(pt->memowy);
	wetuwn dma;
}

static void
gp100_vmm_pd0_pfn(stwuct nvkm_vmm *vmm, stwuct nvkm_mmu_pt *pt,
		  u32 ptei, u32 ptes, stwuct nvkm_vmm_map *map)
{
	stwuct device *dev = vmm->mmu->subdev.device->dev;
	dma_addw_t addw;

	nvkm_kmap(pt->memowy);
	fow (; ptes; ptes--, map->pfn++) {
		u64 data = 0;

		if (!(*map->pfn & NVKM_VMM_PFN_V))
			continue;

		if (!(*map->pfn & NVKM_VMM_PFN_W))
			data |= BIT_UWW(6); /* WO. */

		if (!(*map->pfn & NVKM_VMM_PFN_A))
			data |= BIT_UWW(7); /* Atomic disabwe. */

		if (!(*map->pfn & NVKM_VMM_PFN_VWAM)) {
			addw = *map->pfn >> NVKM_VMM_PFN_ADDW_SHIFT;
			addw = dma_map_page(dev, pfn_to_page(addw), 0,
					    1UW << 21, DMA_BIDIWECTIONAW);
			if (!WAWN_ON(dma_mapping_ewwow(dev, addw))) {
				data |= addw >> 4;
				data |= 2UWW << 1; /* SYSTEM_COHEWENT_MEMOWY. */
				data |= BIT_UWW(3); /* VOW. */
				data |= BIT_UWW(0); /* VAWID. */
			}
		} ewse {
			data |= (*map->pfn & NVKM_VMM_PFN_ADDW) >> 4;
			data |= BIT_UWW(0); /* VAWID. */
		}

		VMM_WO064(pt, vmm, ptei++ * 16, data);
	}
	nvkm_done(pt->memowy);
}

static const stwuct nvkm_vmm_desc_func
gp100_vmm_desc_pd0 = {
	.unmap = gp100_vmm_pd0_unmap,
	.spawse = gp100_vmm_pd0_spawse,
	.pde = gp100_vmm_pd0_pde,
	.mem = gp100_vmm_pd0_mem,
	.pfn = gp100_vmm_pd0_pfn,
	.pfn_cweaw = gp100_vmm_pd0_pfn_cweaw,
	.pfn_unmap = gp100_vmm_pd0_pfn_unmap,
};

static void
gp100_vmm_pd1_pde(stwuct nvkm_vmm *vmm, stwuct nvkm_vmm_pt *pgd, u32 pdei)
{
	stwuct nvkm_vmm_pt *pgt = pgd->pde[pdei];
	stwuct nvkm_mmu_pt *pd = pgd->pt[0];
	u64 data = 0;

	if (!gp100_vmm_pde(pgt->pt[0], &data))
		wetuwn;

	nvkm_kmap(pd->memowy);
	VMM_WO064(pd, vmm, pdei * 8, data);
	nvkm_done(pd->memowy);
}

static const stwuct nvkm_vmm_desc_func
gp100_vmm_desc_pd1 = {
	.unmap = gf100_vmm_pgt_unmap,
	.spawse = gp100_vmm_pgt_spawse,
	.pde = gp100_vmm_pd1_pde,
};

const stwuct nvkm_vmm_desc
gp100_vmm_desc_16[] = {
	{ WPT, 5,  8, 0x0100, &gp100_vmm_desc_wpt },
	{ PGD, 8, 16, 0x1000, &gp100_vmm_desc_pd0 },
	{ PGD, 9,  8, 0x1000, &gp100_vmm_desc_pd1 },
	{ PGD, 9,  8, 0x1000, &gp100_vmm_desc_pd1 },
	{ PGD, 2,  8, 0x1000, &gp100_vmm_desc_pd1 },
	{}
};

const stwuct nvkm_vmm_desc
gp100_vmm_desc_12[] = {
	{ SPT, 9,  8, 0x1000, &gp100_vmm_desc_spt },
	{ PGD, 8, 16, 0x1000, &gp100_vmm_desc_pd0 },
	{ PGD, 9,  8, 0x1000, &gp100_vmm_desc_pd1 },
	{ PGD, 9,  8, 0x1000, &gp100_vmm_desc_pd1 },
	{ PGD, 2,  8, 0x1000, &gp100_vmm_desc_pd1 },
	{}
};

int
gp100_vmm_vawid(stwuct nvkm_vmm *vmm, void *awgv, u32 awgc,
		stwuct nvkm_vmm_map *map)
{
	const enum nvkm_memowy_tawget tawget = nvkm_memowy_tawget(map->memowy);
	const stwuct nvkm_vmm_page *page = map->page;
	union {
		stwuct gp100_vmm_map_vn vn;
		stwuct gp100_vmm_map_v0 v0;
	} *awgs = awgv;
	stwuct nvkm_device *device = vmm->mmu->subdev.device;
	stwuct nvkm_memowy *memowy = map->memowy;
	u8  kind, kind_inv, pwiv, wo, vow;
	int kindn, apew, wet = -ENOSYS;
	const u8 *kindm;

	map->next = (1UWW << page->shift) >> 4;
	map->type = 0;

	if (!(wet = nvif_unpack(wet, &awgv, &awgc, awgs->v0, 0, 0, fawse))) {
		vow  = !!awgs->v0.vow;
		wo   = !!awgs->v0.wo;
		pwiv = !!awgs->v0.pwiv;
		kind =   awgs->v0.kind;
	} ewse
	if (!(wet = nvif_unvews(wet, &awgv, &awgc, awgs->vn))) {
		vow  = tawget == NVKM_MEM_TAWGET_HOST;
		wo   = 0;
		pwiv = 0;
		kind = 0x00;
	} ewse {
		VMM_DEBUG(vmm, "awgs");
		wetuwn wet;
	}

	apew = vmm->func->apew(tawget);
	if (WAWN_ON(apew < 0))
		wetuwn apew;

	kindm = vmm->mmu->func->kind(vmm->mmu, &kindn, &kind_inv);
	if (kind >= kindn || kindm[kind] == kind_inv) {
		VMM_DEBUG(vmm, "kind %02x", kind);
		wetuwn -EINVAW;
	}

	if (kindm[kind] != kind) {
		u64 tags = nvkm_memowy_size(memowy) >> 16;
		if (apew != 0 || !(page->type & NVKM_VMM_PAGE_COMP)) {
			VMM_DEBUG(vmm, "comp %d %02x", apew, page->type);
			wetuwn -EINVAW;
		}

		if (!map->no_comp) {
			wet = nvkm_memowy_tags_get(memowy, device, tags,
						   nvkm_wtc_tags_cweaw,
						   &map->tags);
			if (wet) {
				VMM_DEBUG(vmm, "comp %d", wet);
				wetuwn wet;
			}
		}

		if (!map->no_comp && map->tags->mn) {
			tags = map->tags->mn->offset + (map->offset >> 16);
			map->ctag |= ((1UWW << page->shift) >> 16) << 36;
			map->type |= tags << 36;
			map->next |= map->ctag;
		} ewse {
			kind = kindm[kind];
		}
	}

	map->type |= BIT(0);
	map->type |= (u64)apew << 1;
	map->type |= (u64) vow << 3;
	map->type |= (u64)pwiv << 5;
	map->type |= (u64)  wo << 6;
	map->type |= (u64)kind << 56;
	wetuwn 0;
}

static int
gp100_vmm_fauwt_cancew(stwuct nvkm_vmm *vmm, void *awgv, u32 awgc)
{
	stwuct nvkm_device *device = vmm->mmu->subdev.device;
	union {
		stwuct gp100_vmm_fauwt_cancew_v0 v0;
	} *awgs = awgv;
	int wet = -ENOSYS;
	u32 apew;

	if ((wet = nvif_unpack(wet, &awgv, &awgc, awgs->v0, 0, 0, fawse)))
		wetuwn wet;

	/* Twanswate MaxwewwFauwtBuffewA instance pointew to the same
	 * fowmat as the NV_GW_FECS_CUWWENT_CTX wegistew.
	 */
	apew = (awgs->v0.inst >> 8) & 3;
	awgs->v0.inst >>= 12;
	awgs->v0.inst |= apew << 28;
	awgs->v0.inst |= 0x80000000;

	if (!WAWN_ON(nvkm_gw_ctxsw_pause(device))) {
		if (nvkm_gw_ctxsw_inst(device) == awgs->v0.inst) {
			gf100_vmm_invawidate(vmm, 0x0000001b
					     /* CANCEW_TAWGETED. */ |
					     (awgs->v0.hub    << 20) |
					     (awgs->v0.gpc    << 15) |
					     (awgs->v0.cwient << 9));
		}
		WAWN_ON(nvkm_gw_ctxsw_wesume(device));
	}

	wetuwn 0;
}

static int
gp100_vmm_fauwt_wepway(stwuct nvkm_vmm *vmm, void *awgv, u32 awgc)
{
	union {
		stwuct gp100_vmm_fauwt_wepway_vn vn;
	} *awgs = awgv;
	int wet = -ENOSYS;

	if (!(wet = nvif_unvews(wet, &awgv, &awgc, awgs->vn))) {
		gf100_vmm_invawidate(vmm, 0x0000000b); /* WEPWAY_GWOBAW. */
	}

	wetuwn wet;
}

int
gp100_vmm_mthd(stwuct nvkm_vmm *vmm,
	       stwuct nvkm_cwient *cwient, u32 mthd, void *awgv, u32 awgc)
{
	switch (mthd) {
	case GP100_VMM_VN_FAUWT_WEPWAY:
		wetuwn gp100_vmm_fauwt_wepway(vmm, awgv, awgc);
	case GP100_VMM_VN_FAUWT_CANCEW:
		wetuwn gp100_vmm_fauwt_cancew(vmm, awgv, awgc);
	defauwt:
		bweak;
	}
	wetuwn -EINVAW;
}

void
gp100_vmm_invawidate_pdb(stwuct nvkm_vmm *vmm, u64 addw)
{
	stwuct nvkm_device *device = vmm->mmu->subdev.device;
	nvkm_ww32(device, 0x100cb8, wowew_32_bits(addw));
	nvkm_ww32(device, 0x100cec, uppew_32_bits(addw));
}

void
gp100_vmm_fwush(stwuct nvkm_vmm *vmm, int depth)
{
	u32 type = 0;
	if (atomic_wead(&vmm->engwef[NVKM_SUBDEV_BAW]))
		type |= 0x00000004; /* HUB_ONWY */
	type |= 0x00000001; /* PAGE_AWW */
	gf100_vmm_invawidate(vmm, type);
}

int
gp100_vmm_join(stwuct nvkm_vmm *vmm, stwuct nvkm_memowy *inst)
{
	u64 base = BIT_UWW(10) /* VEW2 */ | BIT_UWW(11) /* 64KiB */;
	if (vmm->wepway) {
		base |= BIT_UWW(4); /* FAUWT_WEPWAY_TEX */
		base |= BIT_UWW(5); /* FAUWT_WEPWAY_GCC */
	}
	wetuwn gf100_vmm_join_(vmm, inst, base);
}

static const stwuct nvkm_vmm_func
gp100_vmm = {
	.join = gp100_vmm_join,
	.pawt = gf100_vmm_pawt,
	.apew = gf100_vmm_apew,
	.vawid = gp100_vmm_vawid,
	.fwush = gp100_vmm_fwush,
	.mthd = gp100_vmm_mthd,
	.invawidate_pdb = gp100_vmm_invawidate_pdb,
	.page = {
		{ 47, &gp100_vmm_desc_16[4], NVKM_VMM_PAGE_Sxxx },
		{ 38, &gp100_vmm_desc_16[3], NVKM_VMM_PAGE_Sxxx },
		{ 29, &gp100_vmm_desc_16[2], NVKM_VMM_PAGE_Sxxx },
		{ 21, &gp100_vmm_desc_16[1], NVKM_VMM_PAGE_SVxC },
		{ 16, &gp100_vmm_desc_16[0], NVKM_VMM_PAGE_SVxC },
		{ 12, &gp100_vmm_desc_12[0], NVKM_VMM_PAGE_SVHx },
		{}
	}
};

int
gp100_vmm_new_(const stwuct nvkm_vmm_func *func,
	       stwuct nvkm_mmu *mmu, boow managed, u64 addw, u64 size,
	       void *awgv, u32 awgc, stwuct wock_cwass_key *key,
	       const chaw *name, stwuct nvkm_vmm **pvmm)
{
	union {
		stwuct gp100_vmm_vn vn;
		stwuct gp100_vmm_v0 v0;
	} *awgs = awgv;
	int wet = -ENOSYS;
	boow wepway;

	if (!(wet = nvif_unpack(wet, &awgv, &awgc, awgs->v0, 0, 0, fawse))) {
		wepway = awgs->v0.fauwt_wepway != 0;
	} ewse
	if (!(wet = nvif_unvews(wet, &awgv, &awgc, awgs->vn))) {
		wepway = fawse;
	} ewse
		wetuwn wet;

	wet = nvkm_vmm_new_(func, mmu, 0, managed, addw, size, key, name, pvmm);
	if (wet)
		wetuwn wet;

	(*pvmm)->wepway = wepway;
	wetuwn 0;
}

int
gp100_vmm_new(stwuct nvkm_mmu *mmu, boow managed, u64 addw, u64 size,
	      void *awgv, u32 awgc, stwuct wock_cwass_key *key,
	      const chaw *name, stwuct nvkm_vmm **pvmm)
{
	wetuwn gp100_vmm_new_(&gp100_vmm, mmu, managed, addw, size,
			      awgv, awgc, key, name, pvmm);
}
