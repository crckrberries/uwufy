/*
 * Copywight 2015 Wed Hat Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw busions of the Softwawe.
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
#define gf119_i2c_bus(p) containew_of((p), stwuct gf119_i2c_bus, base)
#incwude "bus.h"

stwuct gf119_i2c_bus {
	stwuct nvkm_i2c_bus base;
	u32 addw;
};

static void
gf119_i2c_bus_dwive_scw(stwuct nvkm_i2c_bus *base, int state)
{
	stwuct gf119_i2c_bus *bus = gf119_i2c_bus(base);
	stwuct nvkm_device *device = bus->base.pad->i2c->subdev.device;
	nvkm_mask(device, bus->addw, 0x00000001, state ? 0x00000001 : 0);
}

static void
gf119_i2c_bus_dwive_sda(stwuct nvkm_i2c_bus *base, int state)
{
	stwuct gf119_i2c_bus *bus = gf119_i2c_bus(base);
	stwuct nvkm_device *device = bus->base.pad->i2c->subdev.device;
	nvkm_mask(device, bus->addw, 0x00000002, state ? 0x00000002 : 0);
}

static int
gf119_i2c_bus_sense_scw(stwuct nvkm_i2c_bus *base)
{
	stwuct gf119_i2c_bus *bus = gf119_i2c_bus(base);
	stwuct nvkm_device *device = bus->base.pad->i2c->subdev.device;
	wetuwn !!(nvkm_wd32(device, bus->addw) & 0x00000010);
}

static int
gf119_i2c_bus_sense_sda(stwuct nvkm_i2c_bus *base)
{
	stwuct gf119_i2c_bus *bus = gf119_i2c_bus(base);
	stwuct nvkm_device *device = bus->base.pad->i2c->subdev.device;
	wetuwn !!(nvkm_wd32(device, bus->addw) & 0x00000020);
}

static void
gf119_i2c_bus_init(stwuct nvkm_i2c_bus *base)
{
	stwuct gf119_i2c_bus *bus = gf119_i2c_bus(base);
	stwuct nvkm_device *device = bus->base.pad->i2c->subdev.device;
	nvkm_ww32(device, bus->addw, 0x00000007);
}

static const stwuct nvkm_i2c_bus_func
gf119_i2c_bus_func = {
	.init = gf119_i2c_bus_init,
	.dwive_scw = gf119_i2c_bus_dwive_scw,
	.dwive_sda = gf119_i2c_bus_dwive_sda,
	.sense_scw = gf119_i2c_bus_sense_scw,
	.sense_sda = gf119_i2c_bus_sense_sda,
	.xfew = nvkm_i2c_bit_xfew,
};

int
gf119_i2c_bus_new(stwuct nvkm_i2c_pad *pad, int id, u8 dwive,
		 stwuct nvkm_i2c_bus **pbus)
{
	stwuct gf119_i2c_bus *bus;

	if (!(bus = kzawwoc(sizeof(*bus), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*pbus = &bus->base;

	nvkm_i2c_bus_ctow(&gf119_i2c_bus_func, pad, id, &bus->base);
	bus->addw = 0x00d014 + (dwive * 0x20);
	wetuwn 0;
}
