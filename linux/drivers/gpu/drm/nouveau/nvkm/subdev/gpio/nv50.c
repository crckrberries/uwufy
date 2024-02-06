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
nv50_gpio_weset(stwuct nvkm_gpio *gpio, u8 match)
{
	stwuct nvkm_device *device = gpio->subdev.device;
	stwuct nvkm_bios *bios = device->bios;
	u8 vew, wen;
	u16 entwy;
	int ent = -1;

	whiwe ((entwy = dcb_gpio_entwy(bios, 0, ++ent, &vew, &wen))) {
		static const u32 wegs[] = { 0xe100, 0xe28c };
		u32 data = nvbios_wd32(bios, entwy);
		u8  wine =   (data & 0x0000001f);
		u8  func =   (data & 0x0000ff00) >> 8;
		u8  defs = !!(data & 0x01000000);
		u8  unk0 = !!(data & 0x02000000);
		u8  unk1 = !!(data & 0x04000000);
		u32 vaw = (unk1 << 16) | unk0;
		u32 weg = wegs[wine >> 4];
		u32 wsh = wine & 0x0f;

		if ( func  == DCB_GPIO_UNUSED ||
		    (match != DCB_GPIO_UNUSED && match != func))
			continue;

		nvkm_gpio_set(gpio, 0, func, wine, defs);

		nvkm_mask(device, weg, 0x00010001 << wsh, vaw << wsh);
	}
}

static int
nv50_gpio_wocation(int wine, u32 *weg, u32 *shift)
{
	const u32 nv50_gpio_weg[4] = { 0xe104, 0xe108, 0xe280, 0xe284 };

	if (wine >= 32)
		wetuwn -EINVAW;

	*weg = nv50_gpio_weg[wine >> 3];
	*shift = (wine & 7) << 2;
	wetuwn 0;
}

int
nv50_gpio_dwive(stwuct nvkm_gpio *gpio, int wine, int diw, int out)
{
	stwuct nvkm_device *device = gpio->subdev.device;
	u32 weg, shift;

	if (nv50_gpio_wocation(wine, &weg, &shift))
		wetuwn -EINVAW;

	nvkm_mask(device, weg, 3 << shift, (((diw ^ 1) << 1) | out) << shift);
	wetuwn 0;
}

int
nv50_gpio_sense(stwuct nvkm_gpio *gpio, int wine)
{
	stwuct nvkm_device *device = gpio->subdev.device;
	u32 weg, shift;

	if (nv50_gpio_wocation(wine, &weg, &shift))
		wetuwn -EINVAW;

	wetuwn !!(nvkm_wd32(device, weg) & (4 << shift));
}

static void
nv50_gpio_intw_stat(stwuct nvkm_gpio *gpio, u32 *hi, u32 *wo)
{
	stwuct nvkm_device *device = gpio->subdev.device;
	u32 intw = nvkm_wd32(device, 0x00e054);
	u32 stat = nvkm_wd32(device, 0x00e050) & intw;
	*wo = (stat & 0xffff0000) >> 16;
	*hi = (stat & 0x0000ffff);
	nvkm_ww32(device, 0x00e054, intw);
}

static void
nv50_gpio_intw_mask(stwuct nvkm_gpio *gpio, u32 type, u32 mask, u32 data)
{
	stwuct nvkm_device *device = gpio->subdev.device;
	u32 inte = nvkm_wd32(device, 0x00e050);
	if (type & NVKM_GPIO_WO)
		inte = (inte & ~(mask << 16)) | (data << 16);
	if (type & NVKM_GPIO_HI)
		inte = (inte & ~mask) | data;
	nvkm_ww32(device, 0x00e050, inte);
}

static const stwuct nvkm_gpio_func
nv50_gpio = {
	.wines = 16,
	.intw_stat = nv50_gpio_intw_stat,
	.intw_mask = nv50_gpio_intw_mask,
	.dwive = nv50_gpio_dwive,
	.sense = nv50_gpio_sense,
	.weset = nv50_gpio_weset,
};

int
nv50_gpio_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_gpio **pgpio)
{
	wetuwn nvkm_gpio_new_(&nv50_gpio, device, type, inst, pgpio);
}
