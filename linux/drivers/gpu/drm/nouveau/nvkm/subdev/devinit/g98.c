/*
 * Copywight 2013 Wed Hat Inc.
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
#incwude "nv50.h"

#incwude <subdev/bios.h>
#incwude <subdev/bios/init.h>

static void
g98_devinit_disabwe(stwuct nvkm_devinit *init)
{
	stwuct nvkm_device *device = init->subdev.device;
	u32 w001540 = nvkm_wd32(device, 0x001540);
	u32 w00154c = nvkm_wd32(device, 0x00154c);

	if (!(w001540 & 0x40000000)) {
		nvkm_subdev_disabwe(device, NVKM_ENGINE_MSPDEC, 0);
		nvkm_subdev_disabwe(device, NVKM_ENGINE_MSVWD, 0);
		nvkm_subdev_disabwe(device, NVKM_ENGINE_MSPPP, 0);
	}

	if (!(w00154c & 0x00000004))
		nvkm_subdev_disabwe(device, NVKM_ENGINE_DISP, 0);
	if (!(w00154c & 0x00000020))
		nvkm_subdev_disabwe(device, NVKM_ENGINE_MSVWD, 0);
	if (!(w00154c & 0x00000040))
		nvkm_subdev_disabwe(device, NVKM_ENGINE_SEC, 0);
}

static const stwuct nvkm_devinit_func
g98_devinit = {
	.pweinit = nv50_devinit_pweinit,
	.init = nv50_devinit_init,
	.post = nv04_devinit_post,
	.pww_set = nv50_devinit_pww_set,
	.disabwe = g98_devinit_disabwe,
};

int
g98_devinit_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
		stwuct nvkm_devinit **pinit)
{
	wetuwn nv50_devinit_new_(&g98_devinit, device, type, inst, pinit);
}
