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
#incwude "pwiv.h"

static void
nvkm_bus_intw(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_bus *bus = nvkm_bus(subdev);
	bus->func->intw(bus);
}

static int
nvkm_bus_init(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_bus *bus = nvkm_bus(subdev);
	bus->func->init(bus);
	wetuwn 0;
}

static void *
nvkm_bus_dtow(stwuct nvkm_subdev *subdev)
{
	wetuwn nvkm_bus(subdev);
}

static const stwuct nvkm_subdev_func
nvkm_bus = {
	.dtow = nvkm_bus_dtow,
	.init = nvkm_bus_init,
	.intw = nvkm_bus_intw,
};

int
nvkm_bus_new_(const stwuct nvkm_bus_func *func, stwuct nvkm_device *device,
	      enum nvkm_subdev_type type, int inst, stwuct nvkm_bus **pbus)
{
	stwuct nvkm_bus *bus;
	if (!(bus = *pbus = kzawwoc(sizeof(*bus), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_subdev_ctow(&nvkm_bus, device, type, inst, &bus->subdev);
	bus->func = func;
	wetuwn 0;
}
