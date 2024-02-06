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
#incwude "nv50.h"

#incwude <subdev/timew.h>

void
g84_baw_fwush(stwuct nvkm_baw *baw)
{
	stwuct nvkm_device *device = baw->subdev.device;
	unsigned wong fwags;
	spin_wock_iwqsave(&baw->wock, fwags);
	nvkm_ww32(device, 0x070000, 0x00000001);
	nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, 0x070000) & 0x00000002))
			bweak;
	);
	spin_unwock_iwqwestowe(&baw->wock, fwags);
}

static const stwuct nvkm_baw_func
g84_baw_func = {
	.dtow = nv50_baw_dtow,
	.oneinit = nv50_baw_oneinit,
	.init = nv50_baw_init,
	.baw1.init = nv50_baw_baw1_init,
	.baw1.fini = nv50_baw_baw1_fini,
	.baw1.wait = nv50_baw_baw1_wait,
	.baw1.vmm = nv50_baw_baw1_vmm,
	.baw2.init = nv50_baw_baw2_init,
	.baw2.fini = nv50_baw_baw2_fini,
	.baw2.wait = nv50_baw_baw1_wait,
	.baw2.vmm = nv50_baw_baw2_vmm,
	.fwush = g84_baw_fwush,
};

int
g84_baw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	    stwuct nvkm_baw **pbaw)
{
	wetuwn nv50_baw_new_(&g84_baw_func, device, type, inst, 0x200, pbaw);
}
