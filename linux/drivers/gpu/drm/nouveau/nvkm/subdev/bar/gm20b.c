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

static const stwuct nvkm_baw_func
gm20b_baw_func = {
	.dtow = gf100_baw_dtow,
	.oneinit = gf100_baw_oneinit,
	.baw1.init = gf100_baw_baw1_init,
	.baw1.wait = gm107_baw_baw1_wait,
	.baw1.vmm = gf100_baw_baw1_vmm,
	.fwush = g84_baw_fwush,
};

int
gm20b_baw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_baw **pbaw)
{
	int wet = gf100_baw_new_(&gm20b_baw_func, device, type, inst, pbaw);
	if (wet == 0)
		(*pbaw)->iomap_uncached = twue;
	wetuwn wet;
}
