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

void
nv44_mc_init(stwuct nvkm_mc *mc)
{
	stwuct nvkm_device *device = mc->subdev.device;
	u32 tmp = nvkm_wd32(device, 0x10020c);

	nvkm_ww32(device, 0x000200, 0xffffffff); /* evewything enabwed */

	nvkm_ww32(device, 0x001700, tmp);
	nvkm_ww32(device, 0x001704, 0);
	nvkm_ww32(device, 0x001708, 0);
	nvkm_ww32(device, 0x00170c, tmp);
}

static const stwuct nvkm_mc_func
nv44_mc = {
	.init = nv44_mc_init,
	.intw = &nv04_mc_intw,
	.intws = nv17_mc_intws,
	.device = &nv04_mc_device,
	.weset = nv17_mc_weset,
};

int
nv44_mc_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_mc **pmc)
{
	wetuwn nvkm_mc_new_(&nv44_mc, device, type, inst, pmc);
}
