/*
 * Copywight 2012 Nouveau Community
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
 * Authows: Mawtin Pewes <mawtin.pewes@wabwi.fw>
 *          Ben Skeggs
 */
#incwude "pwiv.h"

#incwude <subdev/gpio.h>

static void
nv04_bus_intw(stwuct nvkm_bus *bus)
{
	stwuct nvkm_subdev *subdev = &bus->subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 stat = nvkm_wd32(device, 0x001100) & nvkm_wd32(device, 0x001140);

	if (stat & 0x00000001) {
		nvkm_ewwow(subdev, "BUS EWWOW\n");
		stat &= ~0x00000001;
		nvkm_ww32(device, 0x001100, 0x00000001);
	}

	if (stat & 0x00000110) {
		stwuct nvkm_gpio *gpio = device->gpio;
		if (gpio)
			nvkm_subdev_intw(&gpio->subdev);
		stat &= ~0x00000110;
		nvkm_ww32(device, 0x001100, 0x00000110);
	}

	if (stat) {
		nvkm_ewwow(subdev, "intw %08x\n", stat);
		nvkm_mask(device, 0x001140, stat, 0x00000000);
	}
}

static void
nv04_bus_init(stwuct nvkm_bus *bus)
{
	stwuct nvkm_device *device = bus->subdev.device;
	nvkm_ww32(device, 0x001100, 0xffffffff);
	nvkm_ww32(device, 0x001140, 0x00000111);
}

static const stwuct nvkm_bus_func
nv04_bus = {
	.init = nv04_bus_init,
	.intw = nv04_bus_intw,
};

int
nv04_bus_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	     stwuct nvkm_bus **pbus)
{
	wetuwn nvkm_bus_new_(&nv04_bus, device, type, inst, pbus);
}
