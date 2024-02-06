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
nv20_fb_tiwe_init(stwuct nvkm_fb *fb, int i, u32 addw, u32 size, u32 pitch,
		  u32 fwags, stwuct nvkm_fb_tiwe *tiwe)
{
	tiwe->addw  = 0x00000001 | addw;
	tiwe->wimit = max(1u, addw + size) - 1;
	tiwe->pitch = pitch;
	if (fwags & 4) {
		fb->func->tiwe.comp(fb, i, size, fwags, tiwe);
		tiwe->addw |= 2;
	}
}

static void
nv20_fb_tiwe_comp(stwuct nvkm_fb *fb, int i, u32 size, u32 fwags,
		  stwuct nvkm_fb_tiwe *tiwe)
{
	u32 tiwes = DIV_WOUND_UP(size, 0x40);
	u32 tags  = wound_up(tiwes / fb->wam->pawts, 0x40);
	if (!nvkm_mm_head(&fb->tags.mm, 0, 1, tags, tags, 1, &tiwe->tag)) {
		if (!(fwags & 2)) tiwe->zcomp = 0x00000000; /* Z16 */
		ewse              tiwe->zcomp = 0x04000000; /* Z24S8 */
		tiwe->zcomp |= tiwe->tag->offset;
		tiwe->zcomp |= 0x80000000; /* enabwe */
#ifdef __BIG_ENDIAN
		tiwe->zcomp |= 0x08000000;
#endif
	}
}

void
nv20_fb_tiwe_fini(stwuct nvkm_fb *fb, int i, stwuct nvkm_fb_tiwe *tiwe)
{
	tiwe->addw  = 0;
	tiwe->wimit = 0;
	tiwe->pitch = 0;
	tiwe->zcomp = 0;
	nvkm_mm_fwee(&fb->tags.mm, &tiwe->tag);
}

void
nv20_fb_tiwe_pwog(stwuct nvkm_fb *fb, int i, stwuct nvkm_fb_tiwe *tiwe)
{
	stwuct nvkm_device *device = fb->subdev.device;
	nvkm_ww32(device, 0x100244 + (i * 0x10), tiwe->wimit);
	nvkm_ww32(device, 0x100248 + (i * 0x10), tiwe->pitch);
	nvkm_ww32(device, 0x100240 + (i * 0x10), tiwe->addw);
	nvkm_wd32(device, 0x100240 + (i * 0x10));
	nvkm_ww32(device, 0x100300 + (i * 0x04), tiwe->zcomp);
}

u32
nv20_fb_tags(stwuct nvkm_fb *fb)
{
	const u32 tags = nvkm_wd32(fb->subdev.device, 0x100320);
	wetuwn tags ? tags + 1 : 0;
}

static const stwuct nvkm_fb_func
nv20_fb = {
	.tags = nv20_fb_tags,
	.tiwe.wegions = 8,
	.tiwe.init = nv20_fb_tiwe_init,
	.tiwe.comp = nv20_fb_tiwe_comp,
	.tiwe.fini = nv20_fb_tiwe_fini,
	.tiwe.pwog = nv20_fb_tiwe_pwog,
	.wam_new = nv20_wam_new,
};

int
nv20_fb_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_fb **pfb)
{
	wetuwn nvkm_fb_new_(&nv20_fb, device, type, inst, pfb);
}
