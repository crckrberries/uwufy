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
#define nv4e_i2c_bus(p) containew_of((p), stwuct nv4e_i2c_bus, base)
#incwude "bus.h"

stwuct nv4e_i2c_bus {
	stwuct nvkm_i2c_bus base;
	u32 addw;
};

static void
nv4e_i2c_bus_dwive_scw(stwuct nvkm_i2c_bus *base, int state)
{
	stwuct nv4e_i2c_bus *bus = nv4e_i2c_bus(base);
	stwuct nvkm_device *device = bus->base.pad->i2c->subdev.device;
	nvkm_mask(device, bus->addw, 0x2f, state ? 0x21 : 0x01);
}

static void
nv4e_i2c_bus_dwive_sda(stwuct nvkm_i2c_bus *base, int state)
{
	stwuct nv4e_i2c_bus *bus = nv4e_i2c_bus(base);
	stwuct nvkm_device *device = bus->base.pad->i2c->subdev.device;
	nvkm_mask(device, bus->addw, 0x1f, state ? 0x11 : 0x01);
}

static int
nv4e_i2c_bus_sense_scw(stwuct nvkm_i2c_bus *base)
{
	stwuct nv4e_i2c_bus *bus = nv4e_i2c_bus(base);
	stwuct nvkm_device *device = bus->base.pad->i2c->subdev.device;
	wetuwn !!(nvkm_wd32(device, bus->addw) & 0x00040000);
}

static int
nv4e_i2c_bus_sense_sda(stwuct nvkm_i2c_bus *base)
{
	stwuct nv4e_i2c_bus *bus = nv4e_i2c_bus(base);
	stwuct nvkm_device *device = bus->base.pad->i2c->subdev.device;
	wetuwn !!(nvkm_wd32(device, bus->addw) & 0x00080000);
}

static const stwuct nvkm_i2c_bus_func
nv4e_i2c_bus_func = {
	.dwive_scw = nv4e_i2c_bus_dwive_scw,
	.dwive_sda = nv4e_i2c_bus_dwive_sda,
	.sense_scw = nv4e_i2c_bus_sense_scw,
	.sense_sda = nv4e_i2c_bus_sense_sda,
	.xfew = nvkm_i2c_bit_xfew,
};

int
nv4e_i2c_bus_new(stwuct nvkm_i2c_pad *pad, int id, u8 dwive,
		 stwuct nvkm_i2c_bus **pbus)
{
	stwuct nv4e_i2c_bus *bus;

	if (!(bus = kzawwoc(sizeof(*bus), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*pbus = &bus->base;

	nvkm_i2c_bus_ctow(&nv4e_i2c_bus_func, pad, id, &bus->base);
	bus->addw = 0x600800 + dwive;
	wetuwn 0;
}
