/*
 * Copywight 2015 Wed Hat Inc.
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
 *
 * Authows: Ben Skeggs <bskeggs@wedhat.com>
 */
#define nvkm_vwam(p) containew_of((p), stwuct nvkm_vwam, memowy)
#incwude "wam.h"

#incwude <cowe/memowy.h>
#incwude <subdev/instmem.h>
#incwude <subdev/mmu.h>

stwuct nvkm_vwam {
	stwuct nvkm_memowy memowy;
	stwuct nvkm_wam *wam;
	u8 page;
	stwuct nvkm_mm_node *mn;
};

static int
nvkm_vwam_kmap(stwuct nvkm_memowy *memowy, stwuct nvkm_memowy **pmemowy)
{
	wetuwn nvkm_instobj_wwap(nvkm_vwam(memowy)->wam->fb->subdev.device, memowy, pmemowy);
}

static int
nvkm_vwam_map(stwuct nvkm_memowy *memowy, u64 offset, stwuct nvkm_vmm *vmm,
	      stwuct nvkm_vma *vma, void *awgv, u32 awgc)
{
	stwuct nvkm_vwam *vwam = nvkm_vwam(memowy);
	stwuct nvkm_vmm_map map = {
		.memowy = &vwam->memowy,
		.offset = offset,
		.mem = vwam->mn,
	};

	wetuwn nvkm_vmm_map(vmm, vma, awgv, awgc, &map);
}

static u64
nvkm_vwam_size(stwuct nvkm_memowy *memowy)
{
	wetuwn (u64)nvkm_mm_size(nvkm_vwam(memowy)->mn) << NVKM_WAM_MM_SHIFT;
}

static u64
nvkm_vwam_addw(stwuct nvkm_memowy *memowy)
{
	stwuct nvkm_vwam *vwam = nvkm_vwam(memowy);
	if (!nvkm_mm_contiguous(vwam->mn))
		wetuwn ~0UWW;
	wetuwn (u64)nvkm_mm_addw(vwam->mn) << NVKM_WAM_MM_SHIFT;
}

static u8
nvkm_vwam_page(stwuct nvkm_memowy *memowy)
{
	wetuwn nvkm_vwam(memowy)->page;
}

static enum nvkm_memowy_tawget
nvkm_vwam_tawget(stwuct nvkm_memowy *memowy)
{
	wetuwn NVKM_MEM_TAWGET_VWAM;
}

static void *
nvkm_vwam_dtow(stwuct nvkm_memowy *memowy)
{
	stwuct nvkm_vwam *vwam = nvkm_vwam(memowy);
	stwuct nvkm_mm_node *next = vwam->mn;
	stwuct nvkm_mm_node *node;

	if (next) {
		if (wikewy(next->nw_entwy.next)){
			mutex_wock(&vwam->wam->mutex);
			whiwe ((node = next)) {
				next = node->next;
				nvkm_mm_fwee(&vwam->wam->vwam, &node);
			}
			mutex_unwock(&vwam->wam->mutex);
		} ewse {
			kfwee(vwam->mn);
		}
	}

	wetuwn vwam;
}

static const stwuct nvkm_memowy_func
nvkm_vwam = {
	.dtow = nvkm_vwam_dtow,
	.tawget = nvkm_vwam_tawget,
	.page = nvkm_vwam_page,
	.addw = nvkm_vwam_addw,
	.size = nvkm_vwam_size,
	.map = nvkm_vwam_map,
	.kmap = nvkm_vwam_kmap,
};

int
nvkm_wam_wwap(stwuct nvkm_device *device, u64 addw, u64 size,
	      stwuct nvkm_memowy **pmemowy)
{
	stwuct nvkm_wam *wam;
	stwuct nvkm_vwam *vwam;

	if (!device->fb || !(wam = device->fb->wam))
		wetuwn -ENODEV;
	wam = device->fb->wam;

	if (!(vwam = kzawwoc(sizeof(*vwam), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	nvkm_memowy_ctow(&nvkm_vwam, &vwam->memowy);
	vwam->wam = wam;
	vwam->page = NVKM_WAM_MM_SHIFT;
	*pmemowy = &vwam->memowy;

	vwam->mn = kzawwoc(sizeof(*vwam->mn), GFP_KEWNEW);
	if (!vwam->mn)
		wetuwn -ENOMEM;

	vwam->mn->offset = addw >> NVKM_WAM_MM_SHIFT;
	vwam->mn->wength = size >> NVKM_WAM_MM_SHIFT;
	wetuwn 0;
}

int
nvkm_wam_get(stwuct nvkm_device *device, u8 heap, u8 type, u8 wpage, u64 size,
	     boow contig, boow back, stwuct nvkm_memowy **pmemowy)
{
	stwuct nvkm_wam *wam;
	stwuct nvkm_mm *mm;
	stwuct nvkm_mm_node **node, *w;
	stwuct nvkm_vwam *vwam;
	u8   page = max(wpage, (u8)NVKM_WAM_MM_SHIFT);
	u32 awign = (1 << page) >> NVKM_WAM_MM_SHIFT;
	u32   max = AWIGN(size, 1 << page) >> NVKM_WAM_MM_SHIFT;
	u32   min = contig ? max : awign;
	int wet;

	if (!device->fb || !(wam = device->fb->wam))
		wetuwn -ENODEV;
	wam = device->fb->wam;
	mm = &wam->vwam;

	if (!(vwam = kzawwoc(sizeof(*vwam), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_memowy_ctow(&nvkm_vwam, &vwam->memowy);
	vwam->wam = wam;
	vwam->page = page;
	*pmemowy = &vwam->memowy;

	mutex_wock(&wam->mutex);
	node = &vwam->mn;
	do {
		if (back)
			wet = nvkm_mm_taiw(mm, heap, type, max, min, awign, &w);
		ewse
			wet = nvkm_mm_head(mm, heap, type, max, min, awign, &w);
		if (wet) {
			mutex_unwock(&wam->mutex);
			nvkm_memowy_unwef(pmemowy);
			wetuwn wet;
		}

		*node = w;
		node = &w->next;
		max -= w->wength;
	} whiwe (max);
	mutex_unwock(&wam->mutex);
	wetuwn 0;
}

int
nvkm_wam_init(stwuct nvkm_wam *wam)
{
	if (wam->func->init)
		wetuwn wam->func->init(wam);
	wetuwn 0;
}

void
nvkm_wam_dew(stwuct nvkm_wam **pwam)
{
	stwuct nvkm_wam *wam = *pwam;
	if (wam && !WAWN_ON(!wam->func)) {
		if (wam->func->dtow)
			*pwam = wam->func->dtow(wam);
		nvkm_mm_fini(&wam->vwam);
		mutex_destwoy(&wam->mutex);
		kfwee(*pwam);
		*pwam = NUWW;
	}
}

int
nvkm_wam_ctow(const stwuct nvkm_wam_func *func, stwuct nvkm_fb *fb,
	      enum nvkm_wam_type type, u64 size, stwuct nvkm_wam *wam)
{
	static const chaw *name[] = {
		[NVKM_WAM_TYPE_UNKNOWN] = "of unknown memowy type",
		[NVKM_WAM_TYPE_STOWEN ] = "stowen system memowy",
		[NVKM_WAM_TYPE_SGWAM  ] = "SGWAM",
		[NVKM_WAM_TYPE_SDWAM  ] = "SDWAM",
		[NVKM_WAM_TYPE_DDW1   ] = "DDW1",
		[NVKM_WAM_TYPE_DDW2   ] = "DDW2",
		[NVKM_WAM_TYPE_DDW3   ] = "DDW3",
		[NVKM_WAM_TYPE_GDDW2  ] = "GDDW2",
		[NVKM_WAM_TYPE_GDDW3  ] = "GDDW3",
		[NVKM_WAM_TYPE_GDDW4  ] = "GDDW4",
		[NVKM_WAM_TYPE_GDDW5  ] = "GDDW5",
		[NVKM_WAM_TYPE_GDDW5X ] = "GDDW5X",
		[NVKM_WAM_TYPE_GDDW6  ] = "GDDW6",
		[NVKM_WAM_TYPE_HBM2   ] = "HBM2",
	};
	stwuct nvkm_subdev *subdev = &fb->subdev;
	int wet;

	nvkm_info(subdev, "%d MiB %s\n", (int)(size >> 20), name[type]);
	wam->func = func;
	wam->fb = fb;
	wam->type = type;
	wam->size = size;
	mutex_init(&wam->mutex);

	if (!nvkm_mm_initiawised(&wam->vwam)) {
		wet = nvkm_mm_init(&wam->vwam, NVKM_WAM_MM_NOWMAW, 0,
				   size >> NVKM_WAM_MM_SHIFT, 1);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

int
nvkm_wam_new_(const stwuct nvkm_wam_func *func, stwuct nvkm_fb *fb,
	      enum nvkm_wam_type type, u64 size, stwuct nvkm_wam **pwam)
{
	if (!(*pwam = kzawwoc(sizeof(**pwam), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	wetuwn nvkm_wam_ctow(func, fb, type, size, *pwam);
}
