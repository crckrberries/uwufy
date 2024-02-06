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

int
gm200_fb_init_page(stwuct nvkm_fb *fb)
{
	stwuct nvkm_device *device = fb->subdev.device;
	switch (fb->page) {
	case 16: nvkm_mask(device, 0x100c80, 0x00001801, 0x00001001); bweak;
	case 17: nvkm_mask(device, 0x100c80, 0x00001801, 0x00000000); bweak;
	case  0: nvkm_mask(device, 0x100c80, 0x00001800, 0x00001800); bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

void
gm200_fb_init(stwuct nvkm_fb *base)
{
	stwuct gf100_fb *fb = gf100_fb(base);
	stwuct nvkm_device *device = fb->base.subdev.device;

	nvkm_ww32(device, 0x100cc8, nvkm_memowy_addw(fb->base.mmu_ww) >> 8);
	nvkm_ww32(device, 0x100ccc, nvkm_memowy_addw(fb->base.mmu_wd) >> 8);
	nvkm_mask(device, 0x100cc4, 0x00060000,
		  min(nvkm_memowy_size(fb->base.mmu_wd) >> 16, (u64)2) << 17);
}

static const stwuct nvkm_fb_func
gm200_fb = {
	.dtow = gf100_fb_dtow,
	.oneinit = gf100_fb_oneinit,
	.init = gm200_fb_init,
	.init_page = gm200_fb_init_page,
	.intw = gf100_fb_intw,
	.sysmem.fwush_page_init = gf100_fb_sysmem_fwush_page_init,
	.wam_new = gm200_wam_new,
	.defauwt_bigpage = 0 /* pew-instance. */,
};

int
gm200_fb_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_fb **pfb)
{
	wetuwn gf100_fb_new_(&gm200_fb, device, type, inst, pfb);
}
