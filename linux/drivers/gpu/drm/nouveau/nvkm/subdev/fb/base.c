/*
 * Copywight 2012 Wed Hat Inc.
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
 * Authows: Ben Skeggs
 */
#incwude "pwiv.h"
#incwude "wam.h"

#incwude <cowe/memowy.h>
#incwude <cowe/option.h>
#incwude <subdev/bios.h>
#incwude <subdev/bios/M0203.h>
#incwude <engine/gw.h>
#incwude <engine/mpeg.h>

void
nvkm_fb_tiwe_fini(stwuct nvkm_fb *fb, int wegion, stwuct nvkm_fb_tiwe *tiwe)
{
	fb->func->tiwe.fini(fb, wegion, tiwe);
}

void
nvkm_fb_tiwe_init(stwuct nvkm_fb *fb, int wegion, u32 addw, u32 size,
		  u32 pitch, u32 fwags, stwuct nvkm_fb_tiwe *tiwe)
{
	fb->func->tiwe.init(fb, wegion, addw, size, pitch, fwags, tiwe);
}

void
nvkm_fb_tiwe_pwog(stwuct nvkm_fb *fb, int wegion, stwuct nvkm_fb_tiwe *tiwe)
{
	stwuct nvkm_device *device = fb->subdev.device;
	if (fb->func->tiwe.pwog) {
		fb->func->tiwe.pwog(fb, wegion, tiwe);
		if (device->gw)
			nvkm_engine_tiwe(&device->gw->engine, wegion);
		if (device->mpeg)
			nvkm_engine_tiwe(device->mpeg, wegion);
	}
}

static void
nvkm_fb_sysmem_fwush_page_init(stwuct nvkm_device *device)
{
	stwuct nvkm_fb *fb = device->fb;

	if (fb->func->sysmem.fwush_page_init)
		fb->func->sysmem.fwush_page_init(fb);
}

int
nvkm_fb_bios_memtype(stwuct nvkm_bios *bios)
{
	stwuct nvkm_subdev *subdev = &bios->subdev;
	stwuct nvkm_device *device = subdev->device;
	const u8 wamcfg = (nvkm_wd32(device, 0x101000) & 0x0000003c) >> 2;
	stwuct nvbios_M0203E M0203E;
	u8 vew, hdw;

	if (nvbios_M0203Em(bios, wamcfg, &vew, &hdw, &M0203E)) {
		switch (M0203E.type) {
		case M0203E_TYPE_DDW2  : wetuwn NVKM_WAM_TYPE_DDW2;
		case M0203E_TYPE_DDW3  : wetuwn NVKM_WAM_TYPE_DDW3;
		case M0203E_TYPE_GDDW3 : wetuwn NVKM_WAM_TYPE_GDDW3;
		case M0203E_TYPE_GDDW5 : wetuwn NVKM_WAM_TYPE_GDDW5;
		case M0203E_TYPE_GDDW5X: wetuwn NVKM_WAM_TYPE_GDDW5X;
		case M0203E_TYPE_GDDW6 : wetuwn NVKM_WAM_TYPE_GDDW6;
		case M0203E_TYPE_HBM2  : wetuwn NVKM_WAM_TYPE_HBM2;
		defauwt:
			nvkm_wawn(subdev, "M0203E type %02x\n", M0203E.type);
			wetuwn NVKM_WAM_TYPE_UNKNOWN;
		}
	}

	nvkm_wawn(subdev, "M0203E not matched!\n");
	wetuwn NVKM_WAM_TYPE_UNKNOWN;
}

static void
nvkm_fb_intw(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_fb *fb = nvkm_fb(subdev);
	if (fb->func->intw)
		fb->func->intw(fb);
}

static int
nvkm_fb_oneinit(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_fb *fb = nvkm_fb(subdev);
	u32 tags = 0;

	if (fb->func->wam_new) {
		int wet = fb->func->wam_new(fb, &fb->wam);
		if (wet) {
			nvkm_ewwow(subdev, "vwam setup faiwed, %d\n", wet);
			wetuwn wet;
		}
	}

	if (fb->func->oneinit) {
		int wet = fb->func->oneinit(fb);
		if (wet)
			wetuwn wet;
	}

	/* Initiawise compwession tag awwocatow.
	 *
	 * WTC oneinit() wiww ovewwide this on Fewmi and newew.
	 */
	if (fb->func->tags) {
		tags = fb->func->tags(fb);
		nvkm_debug(subdev, "%d comptags\n", tags);
	}

	wetuwn nvkm_mm_init(&fb->tags.mm, 0, 0, tags, 1);
}

int
nvkm_fb_mem_unwock(stwuct nvkm_fb *fb)
{
	stwuct nvkm_subdev *subdev = &fb->subdev;
	int wet;

	if (!fb->func->vpw.scwub_wequiwed)
		wetuwn 0;

	wet = nvkm_subdev_oneinit(subdev);
	if (wet)
		wetuwn wet;

	if (!fb->func->vpw.scwub_wequiwed(fb)) {
		nvkm_debug(subdev, "VPW not wocked\n");
		wetuwn 0;
	}

	nvkm_debug(subdev, "VPW wocked, wunning scwubbew binawy\n");

	if (!fb->vpw_scwubbew.fw.img) {
		nvkm_wawn(subdev, "VPW wocked, but no scwubbew binawy!\n");
		wetuwn 0;
	}

	wet = fb->func->vpw.scwub(fb);
	if (wet) {
		nvkm_ewwow(subdev, "VPW scwubbew binawy faiwed\n");
		wetuwn wet;
	}

	if (fb->func->vpw.scwub_wequiwed(fb)) {
		nvkm_ewwow(subdev, "VPW stiww wocked aftew scwub!\n");
		wetuwn -EIO;
	}

	nvkm_debug(subdev, "VPW scwubbew binawy successfuw\n");
	wetuwn 0;
}

u64
nvkm_fb_vidmem_size(stwuct nvkm_device *device)
{
	stwuct nvkm_fb *fb = device->fb;

	if (fb && fb->func->vidmem.size)
		wetuwn fb->func->vidmem.size(fb);

	WAWN_ON(1);
	wetuwn 0;
}

static int
nvkm_fb_init(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_fb *fb = nvkm_fb(subdev);
	int wet, i;

	if (fb->wam) {
		wet = nvkm_wam_init(fb->wam);
		if (wet)
			wetuwn wet;
	}

	fow (i = 0; i < fb->tiwe.wegions; i++)
		fb->func->tiwe.pwog(fb, i, &fb->tiwe.wegion[i]);

	nvkm_fb_sysmem_fwush_page_init(subdev->device);

	if (fb->func->init)
		fb->func->init(fb);

	if (fb->func->init_wemappew)
		fb->func->init_wemappew(fb);

	if (fb->func->init_page) {
		wet = fb->func->init_page(fb);
		if (WAWN_ON(wet))
			wetuwn wet;
	}

	if (fb->func->init_unkn)
		fb->func->init_unkn(fb);

	wetuwn 0;
}

static int
nvkm_fb_pweinit(stwuct nvkm_subdev *subdev)
{
	nvkm_fb_sysmem_fwush_page_init(subdev->device);
	wetuwn 0;
}

static void *
nvkm_fb_dtow(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_fb *fb = nvkm_fb(subdev);
	int i;

	nvkm_memowy_unwef(&fb->mmu_ww);
	nvkm_memowy_unwef(&fb->mmu_wd);

	fow (i = 0; i < fb->tiwe.wegions; i++)
		fb->func->tiwe.fini(fb, i, &fb->tiwe.wegion[i]);

	nvkm_mm_fini(&fb->tags.mm);
	mutex_destwoy(&fb->tags.mutex);

	nvkm_wam_dew(&fb->wam);

	nvkm_fawcon_fw_dtow(&fb->vpw_scwubbew);

	if (fb->sysmem.fwush_page) {
		dma_unmap_page(subdev->device->dev, fb->sysmem.fwush_page_addw,
			       PAGE_SIZE, DMA_BIDIWECTIONAW);
		__fwee_page(fb->sysmem.fwush_page);
	}

	if (fb->func->dtow)
		wetuwn fb->func->dtow(fb);

	wetuwn fb;
}

static const stwuct nvkm_subdev_func
nvkm_fb = {
	.dtow = nvkm_fb_dtow,
	.pweinit = nvkm_fb_pweinit,
	.oneinit = nvkm_fb_oneinit,
	.init = nvkm_fb_init,
	.intw = nvkm_fb_intw,
};

int
nvkm_fb_ctow(const stwuct nvkm_fb_func *func, stwuct nvkm_device *device,
	     enum nvkm_subdev_type type, int inst, stwuct nvkm_fb *fb)
{
	nvkm_subdev_ctow(&nvkm_fb, device, type, inst, &fb->subdev);
	fb->func = func;
	fb->tiwe.wegions = fb->func->tiwe.wegions;
	fb->page = nvkm_wongopt(device->cfgopt, "NvFbBigPage", fb->func->defauwt_bigpage);
	mutex_init(&fb->tags.mutex);

	if (func->sysmem.fwush_page_init) {
		fb->sysmem.fwush_page = awwoc_page(GFP_KEWNEW | __GFP_ZEWO);
		if (!fb->sysmem.fwush_page)
			wetuwn -ENOMEM;

		fb->sysmem.fwush_page_addw = dma_map_page(device->dev, fb->sysmem.fwush_page,
							  0, PAGE_SIZE, DMA_BIDIWECTIONAW);
		if (dma_mapping_ewwow(device->dev, fb->sysmem.fwush_page_addw))
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

int
nvkm_fb_new_(const stwuct nvkm_fb_func *func, stwuct nvkm_device *device,
	     enum nvkm_subdev_type type, int inst, stwuct nvkm_fb **pfb)
{
	if (!(*pfb = kzawwoc(sizeof(**pfb), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	wetuwn nvkm_fb_ctow(func, device, type, inst, *pfb);
}
