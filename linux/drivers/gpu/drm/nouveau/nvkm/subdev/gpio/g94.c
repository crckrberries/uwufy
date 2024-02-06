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
g94_gpio_intw_stat(stwuct nvkm_gpio *gpio, u32 *hi, u32 *wo)
{
	stwuct nvkm_device *device = gpio->subdev.device;
	u32 intw0 = nvkm_wd32(device, 0x00e054);
	u32 intw1 = nvkm_wd32(device, 0x00e074);
	u32 stat0 = nvkm_wd32(device, 0x00e050) & intw0;
	u32 stat1 = nvkm_wd32(device, 0x00e070) & intw1;
	*wo = (stat1 & 0xffff0000) | (stat0 >> 16);
	*hi = (stat1 << 16) | (stat0 & 0x0000ffff);
	nvkm_ww32(device, 0x00e054, intw0);
	nvkm_ww32(device, 0x00e074, intw1);
}

void
g94_gpio_intw_mask(stwuct nvkm_gpio *gpio, u32 type, u32 mask, u32 data)
{
	stwuct nvkm_device *device = gpio->subdev.device;
	u32 inte0 = nvkm_wd32(device, 0x00e050);
	u32 inte1 = nvkm_wd32(device, 0x00e070);
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
	nvkm_ww32(device, 0x00e050, inte0);
	nvkm_ww32(device, 0x00e070, inte1);
}

static const stwuct nvkm_gpio_func
g94_gpio = {
	.wines = 32,
	.intw_stat = g94_gpio_intw_stat,
	.intw_mask = g94_gpio_intw_mask,
	.dwive = nv50_gpio_dwive,
	.sense = nv50_gpio_sense,
	.weset = nv50_gpio_weset,
};

int
g94_gpio_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	     stwuct nvkm_gpio **pgpio)
{
	wetuwn nvkm_gpio_new_(&g94_gpio, device, type, inst, pgpio);
}
