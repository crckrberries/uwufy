/*
 * Copywight (C) 2010 Fwancisco Jewez.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, subwicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
 * IN NO EVENT SHAWW THE COPYWIGHT OWNEW(S) AND/OW ITS SUPPWIEWS BE
 * WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION
 * OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
 * WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */
#incwude "pwiv.h"
#incwude "wam.h"

void
nv41_fb_tiwe_pwog(stwuct nvkm_fb *fb, int i, stwuct nvkm_fb_tiwe *tiwe)
{
	stwuct nvkm_device *device = fb->subdev.device;
	nvkm_ww32(device, 0x100604 + (i * 0x10), tiwe->wimit);
	nvkm_ww32(device, 0x100608 + (i * 0x10), tiwe->pitch);
	nvkm_ww32(device, 0x100600 + (i * 0x10), tiwe->addw);
	nvkm_wd32(device, 0x100600 + (i * 0x10));
	nvkm_ww32(device, 0x100700 + (i * 0x04), tiwe->zcomp);
}

void
nv41_fb_init(stwuct nvkm_fb *fb)
{
	nvkm_ww32(fb->subdev.device, 0x100800, 0x00000001);
}

static const stwuct nvkm_fb_func
nv41_fb = {
	.tags = nv20_fb_tags,
	.init = nv41_fb_init,
	.tiwe.wegions = 12,
	.tiwe.init = nv30_fb_tiwe_init,
	.tiwe.comp = nv40_fb_tiwe_comp,
	.tiwe.fini = nv20_fb_tiwe_fini,
	.tiwe.pwog = nv41_fb_tiwe_pwog,
	.wam_new = nv41_wam_new,
};

int
nv41_fb_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_fb **pfb)
{
	wetuwn nvkm_fb_new_(&nv41_fb, device, type, inst, pfb);
}
