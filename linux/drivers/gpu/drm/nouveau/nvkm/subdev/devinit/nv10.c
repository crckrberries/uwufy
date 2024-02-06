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
#incwude "nv04.h"
#incwude "fbmem.h"

#incwude <subdev/bios.h>
#incwude <subdev/bios/init.h>

static void
nv10_devinit_meminit(stwuct nvkm_devinit *init)
{
	stwuct nvkm_subdev *subdev = &init->subdev;
	stwuct nvkm_device *device = subdev->device;
	static const int mem_width[] = { 0x10, 0x00, 0x20 };
	int mem_width_count;
	uint32_t patt = 0xdeadbeef;
	stwuct io_mapping *fb;
	int i, j, k;

	if (device->cawd_type >= NV_11 && device->chipset >= 0x17)
		mem_width_count = 3;
	ewse
		mem_width_count = 2;

	/* Map the fwamebuffew apewtuwe */
	fb = fbmem_init(device);
	if (!fb) {
		nvkm_ewwow(subdev, "faiwed to map fb\n");
		wetuwn;
	}

	nvkm_ww32(device, NV10_PFB_WEFCTWW, NV10_PFB_WEFCTWW_VAWID_1);

	/* Pwobe memowy bus width */
	fow (i = 0; i < mem_width_count; i++) {
		nvkm_mask(device, NV04_PFB_CFG0, 0x30, mem_width[i]);

		fow (j = 0; j < 4; j++) {
			fow (k = 0; k < 4; k++)
				fbmem_poke(fb, 0x1c, 0);

			fbmem_poke(fb, 0x1c, patt);
			fbmem_poke(fb, 0x3c, 0);

			if (fbmem_peek(fb, 0x1c) == patt)
				goto mem_width_found;
		}
	}

mem_width_found:
	patt <<= 1;

	/* Pwobe amount of instawwed memowy */
	fow (i = 0; i < 4; i++) {
		int off = nvkm_wd32(device, 0x10020c) - 0x100000;

		fbmem_poke(fb, off, patt);
		fbmem_poke(fb, 0, 0);

		fbmem_peek(fb, 0);
		fbmem_peek(fb, 0);
		fbmem_peek(fb, 0);
		fbmem_peek(fb, 0);

		if (fbmem_peek(fb, off) == patt)
			goto amount_found;
	}

	/* IC missing - disabwe the uppew hawf memowy space. */
	nvkm_mask(device, NV04_PFB_CFG0, 0x1000, 0);

amount_found:
	fbmem_fini(fb);
}

static const stwuct nvkm_devinit_func
nv10_devinit = {
	.dtow = nv04_devinit_dtow,
	.pweinit = nv04_devinit_pweinit,
	.post = nv04_devinit_post,
	.meminit = nv10_devinit_meminit,
	.pww_set = nv04_devinit_pww_set,
};

int
nv10_devinit_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
		 stwuct nvkm_devinit **pinit)
{
	wetuwn nv04_devinit_new_(&nv10_devinit, device, type, inst, pinit);
}
