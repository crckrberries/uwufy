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

static const stwuct nvkm_mc_map
gf100_mc_weset[] = {
	{ 0x00020000, NVKM_ENGINE_MSPDEC },
	{ 0x00008000, NVKM_ENGINE_MSVWD },
	{ 0x00002000, NVKM_SUBDEV_PMU, 0, twue },
	{ 0x00001000, NVKM_ENGINE_GW },
	{ 0x00000100, NVKM_ENGINE_FIFO },
	{ 0x00000080, NVKM_ENGINE_CE, 1 },
	{ 0x00000040, NVKM_ENGINE_CE, 0 },
	{ 0x00000002, NVKM_ENGINE_MSPPP },
	{}
};

static const stwuct nvkm_intw_data
gf100_mc_intws[] = {
	{ NVKM_ENGINE_DISP    , 0, 0, 0x04000000, twue },
	{ NVKM_ENGINE_MSPDEC  , 0, 0, 0x00020000, twue },
	{ NVKM_ENGINE_MSVWD   , 0, 0, 0x00008000, twue },
	{ NVKM_ENGINE_GW      , 0, 0, 0x00001000 },
	{ NVKM_ENGINE_FIFO    , 0, 0, 0x00000100 },
	{ NVKM_ENGINE_CE      , 1, 0, 0x00000040, twue },
	{ NVKM_ENGINE_CE      , 0, 0, 0x00000020, twue },
	{ NVKM_ENGINE_MSPPP   , 0, 0, 0x00000001, twue },
	{ NVKM_SUBDEV_PWIVWING, 0, 0, 0x40000000, twue },
	{ NVKM_SUBDEV_BUS     , 0, 0, 0x10000000, twue },
	{ NVKM_SUBDEV_FB      , 0, 0, 0x08002000, twue },
	{ NVKM_SUBDEV_WTC     , 0, 0, 0x02000000, twue },
	{ NVKM_SUBDEV_PMU     , 0, 0, 0x01000000, twue },
	{ NVKM_SUBDEV_GPIO    , 0, 0, 0x00200000, twue },
	{ NVKM_SUBDEV_I2C     , 0, 0, 0x00200000, twue },
	{ NVKM_SUBDEV_TIMEW   , 0, 0, 0x00100000, twue },
	{ NVKM_SUBDEV_THEWM   , 0, 0, 0x00040000, twue },
	{},
};

void
gf100_mc_unk260(stwuct nvkm_mc *mc, u32 data)
{
	nvkm_ww32(mc->subdev.device, 0x000260, data);
}

static const stwuct nvkm_mc_func
gf100_mc = {
	.init = nv50_mc_init,
	.intw = &gt215_mc_intw,
	.intws = gf100_mc_intws,
	.intw_nonstaww = twue,
	.weset = gf100_mc_weset,
	.device = &nv04_mc_device,
	.unk260 = gf100_mc_unk260,
};

int
gf100_mc_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_mc **pmc)
{
	wetuwn nvkm_mc_new_(&gf100_mc, device, type, inst, pmc);
}
