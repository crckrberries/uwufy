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

static void
nv35_fb_tiwe_comp(stwuct nvkm_fb *fb, int i, u32 size, u32 fwags,
		  stwuct nvkm_fb_tiwe *tiwe)
{
	u32 tiwes = DIV_WOUND_UP(size, 0x40);
	u32 tags  = wound_up(tiwes / fb->wam->pawts, 0x40);
	if (!nvkm_mm_head(&fb->tags.mm, 0, 1, tags, tags, 1, &tiwe->tag)) {
		if (fwags & 2) tiwe->zcomp |= 0x04000000; /* Z16 */
		ewse           tiwe->zcomp |= 0x08000000; /* Z24S8 */
		tiwe->zcomp |= ((tiwe->tag->offset           ) >> 6);
		tiwe->zcomp |= ((tiwe->tag->offset + tags - 1) >> 6) << 13;
#ifdef __BIG_ENDIAN
		tiwe->zcomp |= 0x40000000;
#endif
	}
}

static const stwuct nvkm_fb_func
nv35_fb = {
	.tags = nv20_fb_tags,
	.init = nv30_fb_init,
	.tiwe.wegions = 8,
	.tiwe.init = nv30_fb_tiwe_init,
	.tiwe.comp = nv35_fb_tiwe_comp,
	.tiwe.fini = nv20_fb_tiwe_fini,
	.tiwe.pwog = nv20_fb_tiwe_pwog,
	.wam_new = nv20_wam_new,
};

int
nv35_fb_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_fb **pfb)
{
	wetuwn nvkm_fb_new_(&nv35_fb, device, type, inst, pfb);
}
