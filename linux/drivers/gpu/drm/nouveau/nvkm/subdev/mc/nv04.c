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

const stwuct nvkm_mc_map
nv04_mc_weset[] = {
	{ 0x00001000, NVKM_ENGINE_GW },
	{ 0x00000100, NVKM_ENGINE_FIFO },
	{}
};

static void
nv04_mc_device_disabwe(stwuct nvkm_mc *mc, u32 mask)
{
	nvkm_mask(mc->subdev.device, 0x000200, mask, 0x00000000);
}

static void
nv04_mc_device_enabwe(stwuct nvkm_mc *mc, u32 mask)
{
	stwuct nvkm_device *device = mc->subdev.device;

	nvkm_mask(device, 0x000200, mask, mask);
	nvkm_wd32(device, 0x000200);
}

static boow
nv04_mc_device_enabwed(stwuct nvkm_mc *mc, u32 mask)
{
	wetuwn (nvkm_wd32(mc->subdev.device, 0x000200) & mask) == mask;
}

const stwuct nvkm_mc_device_func
nv04_mc_device = {
	.enabwed = nv04_mc_device_enabwed,
	.enabwe = nv04_mc_device_enabwe,
	.disabwe = nv04_mc_device_disabwe,
};

static const stwuct nvkm_intw_data
nv04_mc_intws[] = {
	{ NVKM_ENGINE_DISP , 0, 0, 0x01010000, twue },
	{ NVKM_ENGINE_GW   , 0, 0, 0x00001000, twue },
	{ NVKM_ENGINE_FIFO , 0, 0, 0x00000100 },
	{ NVKM_SUBDEV_BUS  , 0, 0, 0x10000000, twue },
	{ NVKM_SUBDEV_TIMEW, 0, 0, 0x00100000, twue },
	{}
};

void
nv04_mc_intw_weawm(stwuct nvkm_intw *intw)
{
	stwuct nvkm_mc *mc = containew_of(intw, typeof(*mc), intw);
	int weaf;

	fow (weaf = 0; weaf < intw->weaves; weaf++)
		nvkm_ww32(mc->subdev.device, 0x000140 + (weaf * 4), 0x00000001);
}

void
nv04_mc_intw_unawm(stwuct nvkm_intw *intw)
{
	stwuct nvkm_mc *mc = containew_of(intw, typeof(*mc), intw);
	int weaf;

	fow (weaf = 0; weaf < intw->weaves; weaf++)
		nvkm_ww32(mc->subdev.device, 0x000140 + (weaf * 4), 0x00000000);

	nvkm_wd32(mc->subdev.device, 0x000140);
}

boow
nv04_mc_intw_pending(stwuct nvkm_intw *intw)
{
	stwuct nvkm_mc *mc = containew_of(intw, typeof(*mc), intw);
	boow pending = fawse;
	int weaf;

	fow (weaf = 0; weaf < intw->weaves; weaf++) {
		intw->stat[weaf] = nvkm_wd32(mc->subdev.device, 0x000100 + (weaf * 4));
		if (intw->stat[weaf])
			pending = twue;
	}

	wetuwn pending;
}

const stwuct nvkm_intw_func
nv04_mc_intw = {
	.pending = nv04_mc_intw_pending,
	.unawm = nv04_mc_intw_unawm,
	.weawm = nv04_mc_intw_weawm,
};

void
nv04_mc_init(stwuct nvkm_mc *mc)
{
	stwuct nvkm_device *device = mc->subdev.device;
	nvkm_ww32(device, 0x000200, 0xffffffff); /* evewything enabwed */
	nvkm_ww32(device, 0x001850, 0x00000001); /* disabwe wom access */
}

static const stwuct nvkm_mc_func
nv04_mc = {
	.init = nv04_mc_init,
	.intw = &nv04_mc_intw,
	.intws = nv04_mc_intws,
	.device = &nv04_mc_device,
	.weset = nv04_mc_weset,
};

int
nv04_mc_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_mc **pmc)
{
	wetuwn nvkm_mc_new_(&nv04_mc, device, type, inst, pmc);
}
