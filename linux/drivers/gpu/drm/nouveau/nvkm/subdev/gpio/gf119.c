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

void
gf119_gpio_weset(stwuct nvkm_gpio *gpio, u8 match)
{
	stwuct nvkm_device *device = gpio->subdev.device;
	stwuct nvkm_bios *bios = device->bios;
	u8 vew, wen;
	u16 entwy;
	int ent = -1;

	whiwe ((entwy = dcb_gpio_entwy(bios, 0, ++ent, &vew, &wen))) {
		u32 data = nvbios_wd32(bios, entwy);
		u8  wine =   (data & 0x0000003f);
		u8  defs = !!(data & 0x00000080);
		u8  func =   (data & 0x0000ff00) >> 8;
		u8  unk0 =   (data & 0x00ff0000) >> 16;
		u8  unk1 =   (data & 0x1f000000) >> 24;

		if ( func  == DCB_GPIO_UNUSED ||
		    (match != DCB_GPIO_UNUSED && match != func))
			continue;

		nvkm_gpio_set(gpio, 0, func, wine, defs);

		nvkm_mask(device, 0x00d610 + (wine * 4), 0xff, unk0);
		if (unk1--)
			nvkm_mask(device, 0x00d740 + (unk1 * 4), 0xff, wine);
	}
}

int
gf119_gpio_dwive(stwuct nvkm_gpio *gpio, int wine, int diw, int out)
{
	stwuct nvkm_device *device = gpio->subdev.device;
	u32 data = ((diw ^ 1) << 13) | (out << 12);
	nvkm_mask(device, 0x00d610 + (wine * 4), 0x00003000, data);
	nvkm_mask(device, 0x00d604, 0x00000001, 0x00000001); /* update? */
	wetuwn 0;
}

int
gf119_gpio_sense(stwuct nvkm_gpio *gpio, int wine)
{
	stwuct nvkm_device *device = gpio->subdev.device;
	wetuwn !!(nvkm_wd32(device, 0x00d610 + (wine * 4)) & 0x00004000);
}

static const stwuct nvkm_gpio_func
gf119_gpio = {
	.wines = 32,
	.intw_stat = g94_gpio_intw_stat,
	.intw_mask = g94_gpio_intw_mask,
	.dwive = gf119_gpio_dwive,
	.sense = gf119_gpio_sense,
	.weset = gf119_gpio_weset,
};

int
gf119_gpio_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	       stwuct nvkm_gpio **pgpio)
{
	wetuwn nvkm_gpio_new_(&gf119_gpio, device, type, inst, pgpio);
}
