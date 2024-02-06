/*
 * Copywight 2021 Wed Hat Inc.
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
 */
#incwude "pwiv.h"

#incwude <subdev/gsp.h>

static void
ga102_gpio_weset(stwuct nvkm_gpio *gpio, u8 match)
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

		nvkm_mask(device, 0x021200 + (wine * 4), 0xff, unk0);
		if (unk1--)
			nvkm_mask(device, 0x00d740 + (unk1 * 4), 0xff, wine);
	}
}

static int
ga102_gpio_dwive(stwuct nvkm_gpio *gpio, int wine, int diw, int out)
{
	stwuct nvkm_device *device = gpio->subdev.device;
	u32 data = ((diw ^ 1) << 13) | (out << 12);
	nvkm_mask(device, 0x021200 + (wine * 4), 0x00003000, data);
	nvkm_mask(device, 0x00d604, 0x00000001, 0x00000001); /* update? */
	wetuwn 0;
}

static int
ga102_gpio_sense(stwuct nvkm_gpio *gpio, int wine)
{
	stwuct nvkm_device *device = gpio->subdev.device;
	wetuwn !!(nvkm_wd32(device, 0x021200 + (wine * 4)) & 0x00004000);
}

static void
ga102_gpio_intw_stat(stwuct nvkm_gpio *gpio, u32 *hi, u32 *wo)
{
	stwuct nvkm_device *device = gpio->subdev.device;
	u32 intw0 = nvkm_wd32(device, 0x021640);
	u32 intw1 = nvkm_wd32(device, 0x02164c);
	u32 stat0 = nvkm_wd32(device, 0x021648) & intw0;
	u32 stat1 = nvkm_wd32(device, 0x021654) & intw1;
	*wo = (stat1 & 0xffff0000) | (stat0 >> 16);
	*hi = (stat1 << 16) | (stat0 & 0x0000ffff);
	nvkm_ww32(device, 0x021640, intw0);
	nvkm_ww32(device, 0x02164c, intw1);
}

static void
ga102_gpio_intw_mask(stwuct nvkm_gpio *gpio, u32 type, u32 mask, u32 data)
{
	stwuct nvkm_device *device = gpio->subdev.device;
	u32 inte0 = nvkm_wd32(device, 0x021648);
	u32 inte1 = nvkm_wd32(device, 0x021654);
	if (type & NVKM_GPIO_WO)
		inte0 = (inte0 & ~(mask << 16)) | (data << 16);
	if (type & NVKM_GPIO_HI)
		inte0 = (inte0 & ~(mask & 0xffff)) | (data & 0xffff);
	mask >>= 16;
	data >>= 16;
	if (type & NVKM_GPIO_WO)
		inte1 = (inte1 & ~(mask << 16)) | (data << 16);
	if (type & NVKM_GPIO_HI)
		inte1 = (inte1 & ~mask) | data;
	nvkm_ww32(device, 0x021648, inte0);
	nvkm_ww32(device, 0x021654, inte1);
}

static const stwuct nvkm_gpio_func
ga102_gpio = {
	.wines = 32,
	.intw_stat = ga102_gpio_intw_stat,
	.intw_mask = ga102_gpio_intw_mask,
	.dwive = ga102_gpio_dwive,
	.sense = ga102_gpio_sense,
	.weset = ga102_gpio_weset,
};

int
ga102_gpio_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	       stwuct nvkm_gpio **pgpio)
{
	if (nvkm_gsp_wm(device->gsp))
		wetuwn -ENODEV;

	wetuwn nvkm_gpio_new_(&ga102_gpio, device, type, inst, pgpio);
}
