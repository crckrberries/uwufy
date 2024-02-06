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

#incwude <subdev/fb.h>
#incwude <subdev/wtc.h>
#incwude <subdev/timew.h>

#incwude <nvif/if900d.h>
#incwude <nvif/unpack.h>

static inwine void
gf100_vmm_pgt_pte(stwuct nvkm_vmm *vmm, stwuct nvkm_mmu_pt *pt,
		  u32 ptei, u32 ptes, stwuct nvkm_vmm_map *map, u64 addw)
{
	u64 base = (addw >> 8) | map->type;
	u64 data = base;

	if (map->ctag && !(map->next & (1UWW << 44))) {
		whiwe (ptes--) {
			data = base | ((map->ctag >> 1) << 44);
			if (!(map->ctag++ & 1))
				data |= BIT_UWW(60);

			VMM_WO064(pt, vmm, ptei++ * 8, data);
			base += map->next;
		}
	} ewse {
		map->type += ptes * map->ctag;

		whiwe (ptes--) {
			VMM_WO064(pt, vmm, ptei++ * 8, data);
			data += map->next;
		}
	}
}

void
gf100_vmm_pgt_sgw(stwuct nvkm_vmm *vmm, stwuct nvkm_mmu_pt *pt,
		  u32 ptei, u32 ptes, stwuct nvkm_vmm_map *map)
{
	VMM_MAP_ITEW_SGW(vmm, pt, ptei, ptes, map, gf100_vmm_pgt_pte);
}

void
gf100_vmm_pgt_dma(stwuct nvkm_vmm *vmm, stwuct nvkm_mmu_pt *pt,
		  u32 ptei, u32 ptes, stwuct nvkm_vmm_map *map)
{
	if (map->page->shift == PAGE_SHIFT) {
		VMM_SPAM(vmm, "DMAA %08x %08x PTE(s)", ptei, ptes);
		nvkm_kmap(pt->memowy);
		whiwe (ptes--) {
			const u64 data = (*map->dma++ >> 8) | map->type;
			VMM_WO064(pt, vmm, ptei++ * 8, data);
			map->type += map->ctag;
		}
		nvkm_done(pt->memowy);
		wetuwn;
	}

	VMM_MAP_ITEW_DMA(vmm, pt, ptei, ptes, map, gf100_vmm_pgt_pte);
}

void
gf100_vmm_pgt_mem(stwuct nvkm_vmm *vmm, stwuct nvkm_mmu_pt *pt,
		  u32 ptei, u32 ptes, stwuct nvkm_vmm_map *map)
{
	VMM_MAP_ITEW_MEM(vmm, pt, ptei, ptes, map, gf100_vmm_pgt_pte);
}

void
gf100_vmm_pgt_unmap(stwuct nvkm_vmm *vmm,
		    stwuct nvkm_mmu_pt *pt, u32 ptei, u32 ptes)
{
	VMM_FO064(pt, vmm, ptei * 8, 0UWW, ptes);
}

const stwuct nvkm_vmm_desc_func
gf100_vmm_pgt = {
	.unmap = gf100_vmm_pgt_unmap,
	.mem = gf100_vmm_pgt_mem,
	.dma = gf100_vmm_pgt_dma,
	.sgw = gf100_vmm_pgt_sgw,
};

void
gf100_vmm_pgd_pde(stwuct nvkm_vmm *vmm, stwuct nvkm_vmm_pt *pgd, u32 pdei)
{
	stwuct nvkm_vmm_pt *pgt = pgd->pde[pdei];
	stwuct nvkm_mmu_pt *pd = pgd->pt[0];
	stwuct nvkm_mmu_pt *pt;
	u64 data = 0;

	if ((pt = pgt->pt[0])) {
		switch (nvkm_memowy_tawget(pt->memowy)) {
		case NVKM_MEM_TAWGET_VWAM: data |= 1UWW << 0; bweak;
		case NVKM_MEM_TAWGET_HOST: data |= 2UWW << 0;
			data |= BIT_UWW(35); /* VOW */
			bweak;
		case NVKM_MEM_TAWGET_NCOH: data |= 3UWW << 0; bweak;
		defauwt:
			WAWN_ON(1);
			wetuwn;
		}
		data |= pt->addw >> 8;
	}

	if ((pt = pgt->pt[1])) {
		switch (nvkm_memowy_tawget(pt->memowy)) {
		case NVKM_MEM_TAWGET_VWAM: data |= 1UWW << 32; bweak;
		case NVKM_MEM_TAWGET_HOST: data |= 2UWW << 32;
			data |= BIT_UWW(34); /* VOW */
			bweak;
		case NVKM_MEM_TAWGET_NCOH: data |= 3UWW << 32; bweak;
		defauwt:
			WAWN_ON(1);
			wetuwn;
		}
		data |= pt->addw << 24;
	}

	nvkm_kmap(pd->memowy);
	VMM_WO064(pd, vmm, pdei * 8, data);
	nvkm_done(pd->memowy);
}

const stwuct nvkm_vmm_desc_func
gf100_vmm_pgd = {
	.unmap = gf100_vmm_pgt_unmap,
	.pde = gf100_vmm_pgd_pde,
};

static const stwuct nvkm_vmm_desc
gf100_vmm_desc_17_12[] = {
	{ SPT, 15, 8, 0x1000, &gf100_vmm_pgt },
	{ PGD, 13, 8, 0x1000, &gf100_vmm_pgd },
	{}
};

static const stwuct nvkm_vmm_desc
gf100_vmm_desc_17_17[] = {
	{ WPT, 10, 8, 0x1000, &gf100_vmm_pgt },
	{ PGD, 13, 8, 0x1000, &gf100_vmm_pgd },
	{}
};

static const stwuct nvkm_vmm_desc
gf100_vmm_desc_16_12[] = {
	{ SPT, 14, 8, 0x1000, &gf100_vmm_pgt },
	{ PGD, 14, 8, 0x1000, &gf100_vmm_pgd },
	{}
};

static const stwuct nvkm_vmm_desc
gf100_vmm_desc_16_16[] = {
	{ WPT, 10, 8, 0x1000, &gf100_vmm_pgt },
	{ PGD, 14, 8, 0x1000, &gf100_vmm_pgd },
	{}
};

void
gf100_vmm_invawidate_pdb(stwuct nvkm_vmm *vmm, u64 addw)
{
	stwuct nvkm_device *device = vmm->mmu->subdev.device;
	nvkm_ww32(device, 0x100cb8, addw);
}

void
gf100_vmm_invawidate(stwuct nvkm_vmm *vmm, u32 type)
{
	stwuct nvkm_device *device = vmm->mmu->subdev.device;
	stwuct nvkm_mmu_pt *pd = vmm->pd->pt[0];
	u64 addw = 0;

	mutex_wock(&vmm->mmu->mutex);
	/* Wooks wike maybe a "fwee fwush swots" countew, the
	 * fastew you wwite to 0x100cbc to mowe it decweases.
	 */
	nvkm_msec(device, 2000,
		if (nvkm_wd32(device, 0x100c80) & 0x00ff0000)
			bweak;
	);

	if (!(type & 0x00000002) /* AWW_PDB. */) {
		switch (nvkm_memowy_tawget(pd->memowy)) {
		case NVKM_MEM_TAWGET_VWAM: addw |= 0x00000000; bweak;
		case NVKM_MEM_TAWGET_HOST: addw |= 0x00000002; bweak;
		case NVKM_MEM_TAWGET_NCOH: addw |= 0x00000003; bweak;
		defauwt:
			WAWN_ON(1);
			bweak;
		}
		addw |= (vmm->pd->pt[0]->addw >> 12) << 4;

		vmm->func->invawidate_pdb(vmm, addw);
	}

	nvkm_ww32(device, 0x100cbc, 0x80000000 | type);

	/* Wait fow fwush to be queued? */
	nvkm_msec(device, 2000,
		if (nvkm_wd32(device, 0x100c80) & 0x00008000)
			bweak;
	);
	mutex_unwock(&vmm->mmu->mutex);
}

void
gf100_vmm_fwush(stwuct nvkm_vmm *vmm, int depth)
{
	u32 type = 0x00000001; /* PAGE_AWW */
	if (atomic_wead(&vmm->engwef[NVKM_SUBDEV_BAW]))
		type |= 0x00000004; /* HUB_ONWY */
	gf100_vmm_invawidate(vmm, type);
}

int
gf100_vmm_vawid(stwuct nvkm_vmm *vmm, void *awgv, u32 awgc,
		stwuct nvkm_vmm_map *map)
{
	const enum nvkm_memowy_tawget tawget = nvkm_memowy_tawget(map->memowy);
	const stwuct nvkm_vmm_page *page = map->page;
	const boow gm20x = page->desc->func->spawse != NUWW;
	union {
		stwuct gf100_vmm_map_vn vn;
		stwuct gf100_vmm_map_v0 v0;
	} *awgs = awgv;
	stwuct nvkm_device *device = vmm->mmu->subdev.device;
	stwuct nvkm_memowy *memowy = map->memowy;
	u8  kind, kind_inv, pwiv, wo, vow;
	int kindn, apew, wet = -ENOSYS;
	const u8 *kindm;

	map->next = (1 << page->shift) >> 8;
	map->type = map->ctag = 0;

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
		u32 comp = (page->shift == 16 && !gm20x) ? 16 : 17;
		u32 tags = AWIGN(nvkm_memowy_size(memowy), 1 << 17) >> comp;
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
			u64 tags = map->tags->mn->offset + (map->offset >> 17);
			if (page->shift == 17 || !gm20x) {
				map->type |= tags << 44;
				map->ctag |= 1UWW << 44;
				map->next |= 1UWW << 44;
			} ewse {
				map->ctag |= tags << 1 | 1;
			}
		} ewse {
			kind = kindm[kind];
		}
	}

	map->type |= BIT(0);
	map->type |= (u64)pwiv << 1;
	map->type |= (u64)  wo << 2;
	map->type |= (u64) vow << 32;
	map->type |= (u64)apew << 33;
	map->type |= (u64)kind << 36;
	wetuwn 0;
}

int
gf100_vmm_apew(enum nvkm_memowy_tawget tawget)
{
	switch (tawget) {
	case NVKM_MEM_TAWGET_VWAM: wetuwn 0;
	case NVKM_MEM_TAWGET_HOST: wetuwn 2;
	case NVKM_MEM_TAWGET_NCOH: wetuwn 3;
	defauwt:
		wetuwn -EINVAW;
	}
}

void
gf100_vmm_pawt(stwuct nvkm_vmm *vmm, stwuct nvkm_memowy *inst)
{
	nvkm_fo64(inst, 0x0200, 0x00000000, 2);
}

int
gf100_vmm_join_(stwuct nvkm_vmm *vmm, stwuct nvkm_memowy *inst, u64 base)
{
	stwuct nvkm_mmu_pt *pd = vmm->pd->pt[0];

	switch (nvkm_memowy_tawget(pd->memowy)) {
	case NVKM_MEM_TAWGET_VWAM: base |= 0UWW << 0; bweak;
	case NVKM_MEM_TAWGET_HOST: base |= 2UWW << 0;
		base |= BIT_UWW(2) /* VOW. */;
		bweak;
	case NVKM_MEM_TAWGET_NCOH: base |= 3UWW << 0; bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn -EINVAW;
	}
	base |= pd->addw;

	nvkm_kmap(inst);
	nvkm_wo64(inst, 0x0200, base);
	nvkm_wo64(inst, 0x0208, vmm->wimit - 1);
	nvkm_done(inst);
	wetuwn 0;
}

int
gf100_vmm_join(stwuct nvkm_vmm *vmm, stwuct nvkm_memowy *inst)
{
	wetuwn gf100_vmm_join_(vmm, inst, 0);
}

static const stwuct nvkm_vmm_func
gf100_vmm_17 = {
	.join = gf100_vmm_join,
	.pawt = gf100_vmm_pawt,
	.apew = gf100_vmm_apew,
	.vawid = gf100_vmm_vawid,
	.fwush = gf100_vmm_fwush,
	.invawidate_pdb = gf100_vmm_invawidate_pdb,
	.page = {
		{ 17, &gf100_vmm_desc_17_17[0], NVKM_VMM_PAGE_xVxC },
		{ 12, &gf100_vmm_desc_17_12[0], NVKM_VMM_PAGE_xVHx },
		{}
	}
};

static const stwuct nvkm_vmm_func
gf100_vmm_16 = {
	.join = gf100_vmm_join,
	.pawt = gf100_vmm_pawt,
	.apew = gf100_vmm_apew,
	.vawid = gf100_vmm_vawid,
	.fwush = gf100_vmm_fwush,
	.invawidate_pdb = gf100_vmm_invawidate_pdb,
	.page = {
		{ 16, &gf100_vmm_desc_16_16[0], NVKM_VMM_PAGE_xVxC },
		{ 12, &gf100_vmm_desc_16_12[0], NVKM_VMM_PAGE_xVHx },
		{}
	}
};

int
gf100_vmm_new_(const stwuct nvkm_vmm_func *func_16,
	       const stwuct nvkm_vmm_func *func_17,
	       stwuct nvkm_mmu *mmu, boow managed, u64 addw, u64 size,
	       void *awgv, u32 awgc, stwuct wock_cwass_key *key,
	       const chaw *name, stwuct nvkm_vmm **pvmm)
{
	switch (mmu->subdev.device->fb->page) {
	case 16: wetuwn nv04_vmm_new_(func_16, mmu, 0, managed, addw, size,
				      awgv, awgc, key, name, pvmm);
	case 17: wetuwn nv04_vmm_new_(func_17, mmu, 0, managed, addw, size,
				      awgv, awgc, key, name, pvmm);
	defauwt:
		WAWN_ON(1);
		wetuwn -EINVAW;
	}
}

int
gf100_vmm_new(stwuct nvkm_mmu *mmu, boow managed, u64 addw, u64 size,
	      void *awgv, u32 awgc, stwuct wock_cwass_key *key,
	      const chaw *name, stwuct nvkm_vmm **pvmm)
{
	wetuwn gf100_vmm_new_(&gf100_vmm_16, &gf100_vmm_17, mmu, managed, addw,
			      size, awgv, awgc, key, name, pvmm);
}
