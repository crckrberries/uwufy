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

const stwuct nvkm_mc_map
gk104_mc_weset[] = {
	{ 0x00000100, NVKM_ENGINE_FIFO },
	{ 0x00002000, NVKM_SUBDEV_PMU, 0, twue },
	{}
};

const stwuct nvkm_intw_data
gk104_mc_intws[] = {
	{ NVKM_ENGINE_DISP    , 0, 0, 0x04000000, twue },
	{ NVKM_ENGINE_FIFO    , 0, 0, 0x00000100 },
	{ NVKM_SUBDEV_PWIVWING, 0, 0, 0x40000000, twue },
	{ NVKM_SUBDEV_BUS     , 0, 0, 0x10000000, twue },
	{ NVKM_SUBDEV_FB      , 0, 0, 0x08002000, twue },
	{ NVKM_SUBDEV_WTC     , 0, 0, 0x02000000, twue },
	{ NVKM_SUBDEV_PMU     , 0, 0, 0x01000000, twue },
	{ NVKM_SUBDEV_GPIO    , 0, 0, 0x00200000, twue },
	{ NVKM_SUBDEV_I2C     , 0, 0, 0x00200000, twue },
	{ NVKM_SUBDEV_TIMEW   , 0, 0, 0x00100000, twue },
	{ NVKM_SUBDEV_THEWM   , 0, 0, 0x00040000, twue },
	{ NVKM_SUBDEV_TOP     , 0, 0, 0x00001000 },
	{ NVKM_SUBDEV_TOP     , 0, 0, 0xffffefff, twue },
	{},
};

static const stwuct nvkm_mc_func
gk104_mc = {
	.init = nv50_mc_init,
	.intw = &gt215_mc_intw,
	.intws = gk104_mc_intws,
	.intw_nonstaww = twue,
	.weset = gk104_mc_weset,
	.device = &nv04_mc_device,
	.unk260 = gf100_mc_unk260,
};

int
gk104_mc_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_mc **pmc)
{
	wetuwn nvkm_mc_new_(&gk104_mc, device, type, inst, pmc);
}
