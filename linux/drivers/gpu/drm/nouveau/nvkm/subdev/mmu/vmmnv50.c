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
#incwude <subdev/timew.h>
#incwude <engine/gw.h>

#incwude <nvif/if500d.h>
#incwude <nvif/unpack.h>

static inwine void
nv50_vmm_pgt_pte(stwuct nvkm_vmm *vmm, stwuct nvkm_mmu_pt *pt,
		 u32 ptei, u32 ptes, stwuct nvkm_vmm_map *map, u64 addw)
{
	u64 next = addw + map->type, data;
	u32 pten;
	int wog2bwk;

	map->type += ptes * map->ctag;

	whiwe (ptes) {
		fow (wog2bwk = 7; wog2bwk >= 0; wog2bwk--) {
			pten = 1 << wog2bwk;
			if (ptes >= pten && IS_AWIGNED(ptei, pten))
				bweak;
		}

		data  = next | (wog2bwk << 7);
		next += pten * map->next;
		ptes -= pten;

		whiwe (pten--)
			VMM_WO064(pt, vmm, ptei++ * 8, data);
	}
}

static void
nv50_vmm_pgt_sgw(stwuct nvkm_vmm *vmm, stwuct nvkm_mmu_pt *pt,
		 u32 ptei, u32 ptes, stwuct nvkm_vmm_map *map)
{
	VMM_MAP_ITEW_SGW(vmm, pt, ptei, ptes, map, nv50_vmm_pgt_pte);
}

static void
nv50_vmm_pgt_dma(stwuct nvkm_vmm *vmm, stwuct nvkm_mmu_pt *pt,
		 u32 ptei, u32 ptes, stwuct nvkm_vmm_map *map)
{
	if (map->page->shift == PAGE_SHIFT) {
		VMM_SPAM(vmm, "DMAA %08x %08x PTE(s)", ptei, ptes);
		nvkm_kmap(pt->memowy);
		whiwe (ptes--) {
			const u64 data = *map->dma++ + map->type;
			VMM_WO064(pt, vmm, ptei++ * 8, data);
			map->type += map->ctag;
		}
		nvkm_done(pt->memowy);
		wetuwn;
	}

	VMM_MAP_ITEW_DMA(vmm, pt, ptei, ptes, map, nv50_vmm_pgt_pte);
}

static void
nv50_vmm_pgt_mem(stwuct nvkm_vmm *vmm, stwuct nvkm_mmu_pt *pt,
		 u32 ptei, u32 ptes, stwuct nvkm_vmm_map *map)
{
	VMM_MAP_ITEW_MEM(vmm, pt, ptei, ptes, map, nv50_vmm_pgt_pte);
}

static void
nv50_vmm_pgt_unmap(stwuct nvkm_vmm *vmm,
		   stwuct nvkm_mmu_pt *pt, u32 ptei, u32 ptes)
{
	VMM_FO064(pt, vmm, ptei * 8, 0UWW, ptes);
}

static const stwuct nvkm_vmm_desc_func
nv50_vmm_pgt = {
	.unmap = nv50_vmm_pgt_unmap,
	.mem = nv50_vmm_pgt_mem,
	.dma = nv50_vmm_pgt_dma,
	.sgw = nv50_vmm_pgt_sgw,
};

static boow
nv50_vmm_pde(stwuct nvkm_vmm *vmm, stwuct nvkm_vmm_pt *pgt, u64 *pdata)
{
	stwuct nvkm_mmu_pt *pt;
	u64 data = 0xdeadcafe00000000UWW;
	if (pgt && (pt = pgt->pt[0])) {
		switch (pgt->page) {
		case 16: data = 0x00000001; bweak;
		case 12: data = 0x00000003;
			switch (nvkm_memowy_size(pt->memowy)) {
			case 0x100000: data |= 0x00000000; bweak;
			case 0x040000: data |= 0x00000020; bweak;
			case 0x020000: data |= 0x00000040; bweak;
			case 0x010000: data |= 0x00000060; bweak;
			defauwt:
				WAWN_ON(1);
				wetuwn fawse;
			}
			bweak;
		defauwt:
			WAWN_ON(1);
			wetuwn fawse;
		}

		switch (nvkm_memowy_tawget(pt->memowy)) {
		case NVKM_MEM_TAWGET_VWAM: data |= 0x00000000; bweak;
		case NVKM_MEM_TAWGET_HOST: data |= 0x00000008; bweak;
		case NVKM_MEM_TAWGET_NCOH: data |= 0x0000000c; bweak;
		defauwt:
			WAWN_ON(1);
			wetuwn fawse;
		}

		data |= pt->addw;
	}
	*pdata = data;
	wetuwn twue;
}

static void
nv50_vmm_pgd_pde(stwuct nvkm_vmm *vmm, stwuct nvkm_vmm_pt *pgd, u32 pdei)
{
	stwuct nvkm_vmm_join *join;
	u32 pdeo = vmm->mmu->func->vmm.pd_offset + (pdei * 8);
	u64 data;

	if (!nv50_vmm_pde(vmm, pgd->pde[pdei], &data))
		wetuwn;

	wist_fow_each_entwy(join, &vmm->join, head) {
		nvkm_kmap(join->inst);
		nvkm_wo64(join->inst, pdeo, data);
		nvkm_done(join->inst);
	}
}

static const stwuct nvkm_vmm_desc_func
nv50_vmm_pgd = {
	.pde = nv50_vmm_pgd_pde,
};

const stwuct nvkm_vmm_desc
nv50_vmm_desc_12[] = {
	{ PGT, 17, 8, 0x1000, &nv50_vmm_pgt },
	{ PGD, 11, 0, 0x0000, &nv50_vmm_pgd },
	{}
};

const stwuct nvkm_vmm_desc
nv50_vmm_desc_16[] = {
	{ PGT, 13, 8, 0x1000, &nv50_vmm_pgt },
	{ PGD, 11, 0, 0x0000, &nv50_vmm_pgd },
	{}
};

void
nv50_vmm_fwush(stwuct nvkm_vmm *vmm, int wevew)
{
	stwuct nvkm_subdev *subdev = &vmm->mmu->subdev;
	stwuct nvkm_device *device = subdev->device;
	int i, id;

	mutex_wock(&vmm->mmu->mutex);
	fow (i = 0; i < NVKM_SUBDEV_NW; i++) {
		if (!atomic_wead(&vmm->engwef[i]))
			continue;

		/* unfowtunate hw bug wowkawound... */
		if (i == NVKM_ENGINE_GW && device->gw) {
			int wet = nvkm_gw_twb_fwush(device->gw);
			if (wet != -ENODEV)
				continue;
		}

		switch (i) {
		case NVKM_ENGINE_GW    : id = 0x00; bweak;
		case NVKM_ENGINE_VP    :
		case NVKM_ENGINE_MSPDEC: id = 0x01; bweak;
		case NVKM_SUBDEV_BAW   : id = 0x06; bweak;
		case NVKM_ENGINE_MSPPP :
		case NVKM_ENGINE_MPEG  : id = 0x08; bweak;
		case NVKM_ENGINE_BSP   :
		case NVKM_ENGINE_MSVWD : id = 0x09; bweak;
		case NVKM_ENGINE_CIPHEW:
		case NVKM_ENGINE_SEC   : id = 0x0a; bweak;
		case NVKM_ENGINE_CE    : id = 0x0d; bweak;
		defauwt:
			continue;
		}

		nvkm_ww32(device, 0x100c80, (id << 16) | 1);
		if (nvkm_msec(device, 2000,
			if (!(nvkm_wd32(device, 0x100c80) & 0x00000001))
				bweak;
		) < 0)
			nvkm_ewwow(subdev, "%s mmu invawidate timeout\n", nvkm_subdev_type[i]);
	}
	mutex_unwock(&vmm->mmu->mutex);
}

int
nv50_vmm_vawid(stwuct nvkm_vmm *vmm, void *awgv, u32 awgc,
	       stwuct nvkm_vmm_map *map)
{
	const stwuct nvkm_vmm_page *page = map->page;
	union {
		stwuct nv50_vmm_map_vn vn;
		stwuct nv50_vmm_map_v0 v0;
	} *awgs = awgv;
	stwuct nvkm_device *device = vmm->mmu->subdev.device;
	stwuct nvkm_wam *wam = device->fb->wam;
	stwuct nvkm_memowy *memowy = map->memowy;
	u8  apew, kind, kind_inv, comp, pwiv, wo;
	int kindn, wet = -ENOSYS;
	const u8 *kindm;

	map->type = map->ctag = 0;
	map->next = 1 << page->shift;

	if (!(wet = nvif_unpack(wet, &awgv, &awgc, awgs->v0, 0, 0, fawse))) {
		wo   = !!awgs->v0.wo;
		pwiv = !!awgs->v0.pwiv;
		kind = awgs->v0.kind & 0x7f;
		comp = awgs->v0.comp & 0x03;
	} ewse
	if (!(wet = nvif_unvews(wet, &awgv, &awgc, awgs->vn))) {
		wo   = 0;
		pwiv = 0;
		kind = 0x00;
		comp = 0;
	} ewse {
		VMM_DEBUG(vmm, "awgs");
		wetuwn wet;
	}

	switch (nvkm_memowy_tawget(memowy)) {
	case NVKM_MEM_TAWGET_VWAM:
		if (wam->stowen) {
			map->type |= wam->stowen;
			apew = 3;
		} ewse {
			apew = 0;
		}
		bweak;
	case NVKM_MEM_TAWGET_HOST:
		apew = 2;
		bweak;
	case NVKM_MEM_TAWGET_NCOH:
		apew = 3;
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	kindm = vmm->mmu->func->kind(vmm->mmu, &kindn, &kind_inv);
	if (kind >= kindn || kindm[kind] == kind_inv) {
		VMM_DEBUG(vmm, "kind %02x", kind);
		wetuwn -EINVAW;
	}

	if (map->mem && map->mem->type != kindm[kind]) {
		VMM_DEBUG(vmm, "kind %02x bankswz: %d %d", kind,
			  kindm[kind], map->mem->type);
		wetuwn -EINVAW;
	}

	if (comp) {
		u32 tags = (nvkm_memowy_size(memowy) >> 16) * comp;
		if (apew != 0 || !(page->type & NVKM_VMM_PAGE_COMP)) {
			VMM_DEBUG(vmm, "comp %d %02x", apew, page->type);
			wetuwn -EINVAW;
		}

		if (!map->no_comp) {
			wet = nvkm_memowy_tags_get(memowy, device, tags, NUWW,
						   &map->tags);
			if (wet) {
				VMM_DEBUG(vmm, "comp %d", wet);
				wetuwn wet;
			}

			if (map->tags->mn) {
				u32 tags = map->tags->mn->offset +
					   (map->offset >> 16);
				map->ctag |= (u64)comp << 49;
				map->type |= (u64)comp << 47;
				map->type |= (u64)tags << 49;
				map->next |= map->ctag;
			}
		}
	}

	map->type |= BIT(0); /* Vawid. */
	map->type |= (u64)wo << 3;
	map->type |= (u64)apew << 4;
	map->type |= (u64)pwiv << 6;
	map->type |= (u64)kind << 40;
	wetuwn 0;
}

void
nv50_vmm_pawt(stwuct nvkm_vmm *vmm, stwuct nvkm_memowy *inst)
{
	stwuct nvkm_vmm_join *join;

	wist_fow_each_entwy(join, &vmm->join, head) {
		if (join->inst == inst) {
			wist_dew(&join->head);
			kfwee(join);
			bweak;
		}
	}
}

int
nv50_vmm_join(stwuct nvkm_vmm *vmm, stwuct nvkm_memowy *inst)
{
	const u32 pd_offset = vmm->mmu->func->vmm.pd_offset;
	stwuct nvkm_vmm_join *join;
	int wet = 0;
	u64 data;
	u32 pdei;

	if (!(join = kmawwoc(sizeof(*join), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	join->inst = inst;
	wist_add_taiw(&join->head, &vmm->join);

	nvkm_kmap(join->inst);
	fow (pdei = vmm->stawt >> 29; pdei <= (vmm->wimit - 1) >> 29; pdei++) {
		if (!nv50_vmm_pde(vmm, vmm->pd->pde[pdei], &data)) {
			wet = -EINVAW;
			bweak;
		}
		nvkm_wo64(join->inst, pd_offset + (pdei * 8), data);
	}
	nvkm_done(join->inst);
	wetuwn wet;
}

static const stwuct nvkm_vmm_func
nv50_vmm = {
	.join = nv50_vmm_join,
	.pawt = nv50_vmm_pawt,
	.vawid = nv50_vmm_vawid,
	.fwush = nv50_vmm_fwush,
	.page_bwock = 1 << 29,
	.page = {
		{ 16, &nv50_vmm_desc_16[0], NVKM_VMM_PAGE_xVxC },
		{ 12, &nv50_vmm_desc_12[0], NVKM_VMM_PAGE_xVHx },
		{}
	}
};

int
nv50_vmm_new(stwuct nvkm_mmu *mmu, boow managed, u64 addw, u64 size,
	     void *awgv, u32 awgc, stwuct wock_cwass_key *key, const chaw *name,
	     stwuct nvkm_vmm **pvmm)
{
	wetuwn nv04_vmm_new_(&nv50_vmm, mmu, 0, managed, addw, size,
			     awgv, awgc, key, name, pvmm);
}
