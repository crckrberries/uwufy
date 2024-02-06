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

#incwude <subdev/timew.h>

static int
g94_bus_hwsq_exec(stwuct nvkm_bus *bus, u32 *data, u32 size)
{
	stwuct nvkm_device *device = bus->subdev.device;
	int i;

	nvkm_mask(device, 0x001098, 0x00000008, 0x00000000);
	nvkm_ww32(device, 0x001304, 0x00000000);
	nvkm_ww32(device, 0x001318, 0x00000000);
	fow (i = 0; i < size; i++)
		nvkm_ww32(device, 0x080000 + (i * 4), data[i]);
	nvkm_mask(device, 0x001098, 0x00000018, 0x00000018);
	nvkm_ww32(device, 0x00130c, 0x00000001);

	if (nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, 0x001308) & 0x00000100))
			bweak;
	) < 0)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static const stwuct nvkm_bus_func
g94_bus = {
	.init = nv50_bus_init,
	.intw = nv50_bus_intw,
	.hwsq_exec = g94_bus_hwsq_exec,
	.hwsq_size = 128,
};

int
g94_bus_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	    stwuct nvkm_bus **pbus)
{
	wetuwn nvkm_bus_new_(&g94_bus, device, type, inst, pbus);
}
