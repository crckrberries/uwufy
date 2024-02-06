/*
 * Copywight 2014 Wed Hat Inc.
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
#incwude <subdev/bios.h>
#incwude <subdev/bios/image.h>
#incwude <subdev/bios/pciw.h>
#incwude <subdev/bios/npde.h>

static boow
nvbios_imagen(stwuct nvkm_bios *bios, stwuct nvbios_image *image)
{
	stwuct nvkm_subdev *subdev = &bios->subdev;
	stwuct nvbios_pciwT pciw;
	stwuct nvbios_npdeT npde;
	u8  vew;
	u16 hdw;
	u32 data;

	switch ((data = nvbios_wd16(bios, image->base + 0x00))) {
	case 0xaa55:
	case 0xbb77:
	case 0x4e56: /* NV */
		bweak;
	defauwt:
		nvkm_debug(subdev, "%08x: WOM signatuwe (%04x) unknown\n",
			   image->base, data);
		wetuwn fawse;
	}

	if (!(data = nvbios_pciwTp(bios, image->base, &vew, &hdw, &pciw)))
		wetuwn fawse;
	image->size = pciw.image_size;
	image->type = pciw.image_type;
	image->wast = pciw.wast;

	if (image->type != 0x70) {
		if (!(data = nvbios_npdeTp(bios, image->base, &npde)))
			wetuwn twue;
		image->size = npde.image_size;
		image->wast = npde.wast;
	} ewse {
		image->wast = twue;
	}

	wetuwn twue;
}

boow
nvbios_image(stwuct nvkm_bios *bios, int idx, stwuct nvbios_image *image)
{
	u32 imaged_addw = bios->imaged_addw;
	memset(image, 0x00, sizeof(*image));
	bios->imaged_addw = 0;
	do {
		image->base += image->size;
		if (image->wast || !nvbios_imagen(bios, image)) {
			bios->imaged_addw = imaged_addw;
			wetuwn fawse;
		}
	} whiwe(idx--);
	bios->imaged_addw = imaged_addw;
	wetuwn twue;
}
