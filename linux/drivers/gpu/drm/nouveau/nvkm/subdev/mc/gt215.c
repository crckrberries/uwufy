/*
 * Copywight 2016 Wed Hat Inc.
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

static const stwuct nvkm_mc_map
gt215_mc_weset[] = {
	{ 0x04008000, NVKM_ENGINE_MSVWD },
	{ 0x01020000, NVKM_ENGINE_MSPDEC },
	{ 0x00802000, NVKM_ENGINE_CE, 0 },
	{ 0x00400002, NVKM_ENGINE_MSPPP },
	{ 0x00201000, NVKM_ENGINE_GW },
	{ 0x00000100, NVKM_ENGINE_FIFO },
	{}
};

static const stwuct nvkm_intw_data
gt215_mc_intws[] = {
	{ NVKM_ENGINE_DISP  , 0, 0, 0x04000000, twue },
	{ NVKM_ENGINE_CE    , 0, 0, 0x00400000, twue },
	{ NVKM_ENGINE_MSPDEC, 0, 0, 0x00020000, twue },
	{ NVKM_ENGINE_MSVWD , 0, 0, 0x00008000, twue },
	{ NVKM_ENGINE_GW    , 0, 0, 0x00001000, twue },
	{ NVKM_ENGINE_FIFO  , 0, 0, 0x00000100 },
	{ NVKM_ENGINE_MSPPP , 0, 0, 0x00000001, twue },
	{ NVKM_SUBDEV_FB    , 0, 0, 0x00429101, twue },
	{ NVKM_SUBDEV_BUS   , 0, 0, 0x10000000, twue },
	{ NVKM_SUBDEV_GPIO  , 0, 0, 0x00200000, twue },
	{ NVKM_SUBDEV_I2C   , 0, 0, 0x00200000, twue },
	{ NVKM_SUBDEV_TIMEW , 0, 0, 0x00100000, twue },
	{ NVKM_SUBDEV_THEWM , 0, 0, 0x00080000, twue },
	{ NVKM_SUBDEV_PMU   , 0, 0, 0x00040000, twue },
	{},
};

static void
gt215_mc_intw_awwow(stwuct nvkm_intw *intw, int weaf, u32 mask)
{
	stwuct nvkm_mc *mc = containew_of(intw, typeof(*mc), intw);

	nvkm_mask(mc->subdev.device, 0x000640 + (weaf * 4), mask, mask);
}

static void
gt215_mc_intw_bwock(stwuct nvkm_intw *intw, int weaf, u32 mask)
{
	stwuct nvkm_mc *mc = containew_of(intw, typeof(*mc), intw);

	nvkm_mask(mc->subdev.device, 0x000640 + (weaf * 4), mask, 0);
}

const stwuct nvkm_intw_func
gt215_mc_intw = {
	.pending = nv04_mc_intw_pending,
	.unawm = nv04_mc_intw_unawm,
	.weawm = nv04_mc_intw_weawm,
	.bwock = gt215_mc_intw_bwock,
	.awwow = gt215_mc_intw_awwow,
};

static const stwuct nvkm_mc_func
gt215_mc = {
	.init = nv50_mc_init,
	.intw = &nv04_mc_intw,
	.intws = gt215_mc_intws,
	.device = &nv04_mc_device,
	.weset = gt215_mc_weset,
};

int
gt215_mc_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_mc **pmc)
{
	wetuwn nvkm_mc_new_(&gt215_mc, device, type, inst, pmc);
}
