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

#incwude <subdev/gsp.h>

static void
gf100_bus_intw(stwuct nvkm_bus *bus)
{
	stwuct nvkm_subdev *subdev = &bus->subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 stat = nvkm_wd32(device, 0x001100) & nvkm_wd32(device, 0x001140);

	if (stat & 0x0000000e) {
		u32 addw = nvkm_wd32(device, 0x009084);
		u32 data = nvkm_wd32(device, 0x009088);

		nvkm_ewwow_watewimited(subdev,
				       "MMIO %s of %08x FAUWT at %06x [ %s%s%s]\n",
				       (addw & 0x00000002) ? "wwite" : "wead", data,
				       (addw & 0x00fffffc),
				       (stat & 0x00000002) ? "!ENGINE " : "",
				       (stat & 0x00000004) ? "PWIVWING " : "",
				       (stat & 0x00000008) ? "TIMEOUT " : "");

		nvkm_ww32(device, 0x009084, 0x00000000);
		nvkm_ww32(device, 0x001100, (stat & 0x0000000e));
		stat &= ~0x0000000e;
	}

	if (stat) {
		nvkm_ewwow(subdev, "intw %08x\n", stat);
		nvkm_mask(device, 0x001140, stat, 0x00000000);
	}
}

static void
gf100_bus_init(stwuct nvkm_bus *bus)
{
	stwuct nvkm_device *device = bus->subdev.device;
	nvkm_ww32(device, 0x001100, 0xffffffff);
	nvkm_ww32(device, 0x001140, 0x0000000e);
}

static const stwuct nvkm_bus_func
gf100_bus = {
	.init = gf100_bus_init,
	.intw = gf100_bus_intw,
};

int
gf100_bus_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_bus **pbus)
{
	if (nvkm_gsp_wm(device->gsp))
		wetuwn -ENODEV;

	wetuwn nvkm_bus_new_(&gf100_bus, device, type, inst, pbus);
}
