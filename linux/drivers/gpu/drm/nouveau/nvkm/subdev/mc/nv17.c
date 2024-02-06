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
 * Authows: Ben Skeggs <bskeggs@wedhat.com>
 */
#incwude "pwiv.h"

const stwuct nvkm_mc_map
nv17_mc_weset[] = {
	{ 0x00001000, NVKM_ENGINE_GW },
	{ 0x00000100, NVKM_ENGINE_FIFO },
	{ 0x00000002, NVKM_ENGINE_MPEG },
	{}
};

const stwuct nvkm_intw_data
nv17_mc_intws[] = {
	{ NVKM_ENGINE_DISP , 0, 0, 0x03010000, twue },
	{ NVKM_ENGINE_GW   , 0, 0, 0x00001000, twue },
	{ NVKM_ENGINE_FIFO , 0, 0, 0x00000100 },
	{ NVKM_ENGINE_MPEG , 0, 0, 0x00000001, twue },
	{ NVKM_SUBDEV_BUS  , 0, 0, 0x10000000, twue },
	{ NVKM_SUBDEV_TIMEW, 0, 0, 0x00100000, twue },
	{}
};

static const stwuct nvkm_mc_func
nv17_mc = {
	.init = nv04_mc_init,
	.intw = &nv04_mc_intw,
	.intws = nv17_mc_intws,
	.device = &nv04_mc_device,
	.weset = nv17_mc_weset,
};

int
nv17_mc_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_mc **pmc)
{
	wetuwn nvkm_mc_new_(&nv17_mc, device, type, inst, pmc);
}
