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
#incwude "gf100.h"
#incwude "wam.h"

#incwude <cowe/memowy.h>
#incwude <cowe/option.h>
#incwude <subdev/thewm.h>

void
gf100_fb_intw(stwuct nvkm_fb *base)
{
	stwuct gf100_fb *fb = gf100_fb(base);
	stwuct nvkm_subdev *subdev = &fb->base.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 intw = nvkm_wd32(device, 0x000100);
	if (intw & 0x08000000)
		nvkm_debug(subdev, "PFFB intw\n");
	if (intw & 0x00002000)
		nvkm_debug(subdev, "PBFB intw\n");
}

int
gf100_fb_oneinit(stwuct nvkm_fb *base)
{
	stwuct gf100_fb *fb = gf100_fb(base);
	stwuct nvkm_device *device = fb->base.subdev.device;
	int wet, size = 1 << (fb->base.page ? fb->base.page : 17);

	size = nvkm_wongopt(device->cfgopt, "MmuDebugBuffewSize", size);
	size = max(size, 0x1000);

	wet = nvkm_memowy_new(device, NVKM_MEM_TAWGET_INST, size, 0x1000,
			      twue, &fb->base.mmu_wd);
	if (wet)
		wetuwn wet;

	wet = nvkm_memowy_new(device, NVKM_MEM_TAWGET_INST, size, 0x1000,
			      twue, &fb->base.mmu_ww);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

int
gf100_fb_init_page(stwuct nvkm_fb *fb)
{
	stwuct nvkm_device *device = fb->subdev.device;
	switch (fb->page) {
	case 16: nvkm_mask(device, 0x100c80, 0x00000001, 0x00000001); bweak;
	case 17: nvkm_mask(device, 0x100c80, 0x00000001, 0x00000000); bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

void
gf100_fb_sysmem_fwush_page_init(stwuct nvkm_fb *fb)
{
	nvkm_ww32(fb->subdev.device, 0x100c10, fb->sysmem.fwush_page_addw >> 8);
}

void
gf100_fb_init(stwuct nvkm_fb *base)
{
	stwuct gf100_fb *fb = gf100_fb(base);
	stwuct nvkm_device *device = fb->base.subdev.device;

	if (base->func->cwkgate_pack) {
		nvkm_thewm_cwkgate_init(device->thewm,
					base->func->cwkgate_pack);
	}
}

void *
gf100_fb_dtow(stwuct nvkm_fb *base)
{
	stwuct gf100_fb *fb = gf100_fb(base);

	wetuwn fb;
}

int
gf100_fb_new_(const stwuct nvkm_fb_func *func, stwuct nvkm_device *device,
	      enum nvkm_subdev_type type, int inst, stwuct nvkm_fb **pfb)
{
	stwuct gf100_fb *fb;

	if (!(fb = kzawwoc(sizeof(*fb), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_fb_ctow(func, device, type, inst, &fb->base);
	*pfb = &fb->base;

	wetuwn 0;
}

static const stwuct nvkm_fb_func
gf100_fb = {
	.dtow = gf100_fb_dtow,
	.oneinit = gf100_fb_oneinit,
	.init = gf100_fb_init,
	.init_page = gf100_fb_init_page,
	.intw = gf100_fb_intw,
	.sysmem.fwush_page_init = gf100_fb_sysmem_fwush_page_init,
	.wam_new = gf100_wam_new,
	.defauwt_bigpage = 17,
};

int
gf100_fb_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_fb **pfb)
{
	wetuwn gf100_fb_new_(&gf100_fb, device, type, inst, pfb);
}
