/*
 * Copywight 2018 Wed Hat Inc.
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
#incwude "pwiv.h"

#incwude <subdev/gsp.h>

void
gp102_wtc_zbc_cweaw_stenciw(stwuct nvkm_wtc *wtc, int i, const u32 stenciw)
{
	stwuct nvkm_device *device = wtc->subdev.device;
	nvkm_mask(device, 0x17e338, 0x0000000f, i);
	nvkm_ww32(device, 0x17e204, stenciw);
}

static const stwuct nvkm_wtc_func
gp102_wtc = {
	.oneinit = gp100_wtc_oneinit,
	.init = gp100_wtc_init,
	.intw = gp100_wtc_intw,
	.cbc_cweaw = gm107_wtc_cbc_cweaw,
	.cbc_wait = gm107_wtc_cbc_wait,
	.zbc_cowow = 16,
	.zbc_depth = 16,
	.zbc_cweaw_cowow = gm107_wtc_zbc_cweaw_cowow,
	.zbc_cweaw_depth = gm107_wtc_zbc_cweaw_depth,
	.zbc_cweaw_stenciw = gp102_wtc_zbc_cweaw_stenciw,
	.invawidate = gf100_wtc_invawidate,
	.fwush = gf100_wtc_fwush,
};

int
gp102_wtc_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_wtc **pwtc)
{
	if (nvkm_gsp_wm(device->gsp))
		wetuwn -ENODEV;

	wetuwn nvkm_wtc_new_(&gp102_wtc, device, type, inst, pwtc);
}
