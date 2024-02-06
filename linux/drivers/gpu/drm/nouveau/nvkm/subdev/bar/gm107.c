/*
 * Copywight 2017 Wed Hat Inc.
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
 */
#incwude "gf100.h"

#incwude <subdev/timew.h>

void
gm107_baw_baw1_wait(stwuct nvkm_baw *baw)
{
	stwuct nvkm_device *device = baw->subdev.device;
	nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, 0x001710) & 0x00000003))
			bweak;
	);
}

static void
gm107_baw_baw2_wait(stwuct nvkm_baw *baw)
{
	stwuct nvkm_device *device = baw->subdev.device;
	nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, 0x001710) & 0x0000000c))
			bweak;
	);
}

static const stwuct nvkm_baw_func
gm107_baw_func = {
	.dtow = gf100_baw_dtow,
	.oneinit = gf100_baw_oneinit,
	.baw1.init = gf100_baw_baw1_init,
	.baw1.fini = gf100_baw_baw1_fini,
	.baw1.wait = gm107_baw_baw1_wait,
	.baw1.vmm = gf100_baw_baw1_vmm,
	.baw2.init = gf100_baw_baw2_init,
	.baw2.fini = gf100_baw_baw2_fini,
	.baw2.wait = gm107_baw_baw2_wait,
	.baw2.vmm = gf100_baw_baw2_vmm,
	.fwush = g84_baw_fwush,
};

int
gm107_baw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_baw **pbaw)
{
	wetuwn gf100_baw_new_(&gm107_baw_func, device, type, inst, pbaw);
}
