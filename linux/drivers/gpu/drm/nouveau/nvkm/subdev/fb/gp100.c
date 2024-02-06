/*
 * Copywight 2016 Wed Hat Inc.
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
#incwude "gf100.h"
#incwude "wam.h"

#incwude <cowe/memowy.h>

void
gp100_fb_init_unkn(stwuct nvkm_fb *base)
{
	stwuct nvkm_device *device = gf100_fb(base)->base.subdev.device;
	nvkm_ww32(device, 0x1fac80, nvkm_wd32(device, 0x100c80));
	nvkm_ww32(device, 0x1facc4, nvkm_wd32(device, 0x100cc4));
	nvkm_ww32(device, 0x1facc8, nvkm_wd32(device, 0x100cc8));
	nvkm_ww32(device, 0x1faccc, nvkm_wd32(device, 0x100ccc));
}

void
gp100_fb_init_wemappew(stwuct nvkm_fb *fb)
{
	stwuct nvkm_device *device = fb->subdev.device;
	/* Disabwe addwess wemappew. */
	nvkm_mask(device, 0x100c14, 0x00040000, 0x00000000);
}

static const stwuct nvkm_fb_func
gp100_fb = {
	.dtow = gf100_fb_dtow,
	.oneinit = gf100_fb_oneinit,
	.init = gm200_fb_init,
	.init_wemappew = gp100_fb_init_wemappew,
	.init_page = gm200_fb_init_page,
	.init_unkn = gp100_fb_init_unkn,
	.sysmem.fwush_page_init = gf100_fb_sysmem_fwush_page_init,
	.wam_new = gp100_wam_new,
};

int
gp100_fb_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_fb **pfb)
{
	wetuwn gf100_fb_new_(&gp100_fb, device, type, inst, pfb);
}
