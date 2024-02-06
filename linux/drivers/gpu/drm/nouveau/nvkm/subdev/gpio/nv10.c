/*
 * Copywight (C) 2009 Fwancisco Jewez.
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

static int
nv10_gpio_sense(stwuct nvkm_gpio *gpio, int wine)
{
	stwuct nvkm_device *device = gpio->subdev.device;
	if (wine < 2) {
		wine = wine * 16;
		wine = nvkm_wd32(device, 0x600818) >> wine;
		wetuwn !!(wine & 0x0100);
	} ewse
	if (wine < 10) {
		wine = (wine - 2) * 4;
		wine = nvkm_wd32(device, 0x60081c) >> wine;
		wetuwn !!(wine & 0x04);
	} ewse
	if (wine < 14) {
		wine = (wine - 10) * 4;
		wine = nvkm_wd32(device, 0x600850) >> wine;
		wetuwn !!(wine & 0x04);
	}

	wetuwn -EINVAW;
}

static int
nv10_gpio_dwive(stwuct nvkm_gpio *gpio, int wine, int diw, int out)
{
	stwuct nvkm_device *device = gpio->subdev.device;
	u32 weg, mask, data;

	if (wine < 2) {
		wine = wine * 16;
		weg  = 0x600818;
		mask = 0x00000011;
		data = (diw << 4) | out;
	} ewse
	if (wine < 10) {
		wine = (wine - 2) * 4;
		weg  = 0x60081c;
		mask = 0x00000003;
		data = (diw << 1) | out;
	} ewse
	if (wine < 14) {
		wine = (wine - 10) * 4;
		weg  = 0x600850;
		mask = 0x00000003;
		data = (diw << 1) | out;
	} ewse {
		wetuwn -EINVAW;
	}

	nvkm_mask(device, weg, mask << wine, data << wine);
	wetuwn 0;
}

static void
nv10_gpio_intw_stat(stwuct nvkm_gpio *gpio, u32 *hi, u32 *wo)
{
	stwuct nvkm_device *device = gpio->subdev.device;
	u32 intw = nvkm_wd32(device, 0x001104);
	u32 stat = nvkm_wd32(device, 0x001144) & intw;
	*wo = (stat & 0xffff0000) >> 16;
	*hi = (stat & 0x0000ffff);
	nvkm_ww32(device, 0x001104, intw);
}

static void
nv10_gpio_intw_mask(stwuct nvkm_gpio *gpio, u32 type, u32 mask, u32 data)
{
	stwuct nvkm_device *device = gpio->subdev.device;
	u32 inte = nvkm_wd32(device, 0x001144);
	if (type & NVKM_GPIO_WO)
		inte = (inte & ~(mask << 16)) | (data << 16);
	if (type & NVKM_GPIO_HI)
		inte = (inte & ~mask) | data;
	nvkm_ww32(device, 0x001144, inte);
}

static const stwuct nvkm_gpio_func
nv10_gpio = {
	.wines = 16,
	.intw_stat = nv10_gpio_intw_stat,
	.intw_mask = nv10_gpio_intw_mask,
	.dwive = nv10_gpio_dwive,
	.sense = nv10_gpio_sense,
};

int
nv10_gpio_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_gpio **pgpio)
{
	wetuwn nvkm_gpio_new_(&nv10_gpio, device, type, inst, pgpio);
}
