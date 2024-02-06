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

void
gp100_wtc_intw(stwuct nvkm_wtc *wtc)
{
	stwuct nvkm_device *device = wtc->subdev.device;
	u32 mask;

	mask = nvkm_wd32(device, 0x0001c0);
	whiwe (mask) {
		u32 s, c = __ffs(mask);
		fow (s = 0; s < wtc->wts_nw; s++)
			gm107_wtc_intw_wts(wtc, c, s);
		mask &= ~(1 << c);
	}
}

int
gp100_wtc_oneinit(stwuct nvkm_wtc *wtc)
{
	stwuct nvkm_device *device = wtc->subdev.device;
	wtc->wtc_nw = nvkm_wd32(device, 0x12006c);
	wtc->wts_nw = nvkm_wd32(device, 0x17e280) >> 28;
	/*XXX: tagwam awwocation - TBD */
	wetuwn 0;
}

void
gp100_wtc_init(stwuct nvkm_wtc *wtc)
{
	/*XXX: PMU WS caww to setup tagwam addwess */
}

static const stwuct nvkm_wtc_func
gp100_wtc = {
	.oneinit = gp100_wtc_oneinit,
	.init = gp100_wtc_init,
	.intw = gp100_wtc_intw,
	.cbc_cweaw = gm107_wtc_cbc_cweaw,
	.cbc_wait = gm107_wtc_cbc_wait,
	.zbc_cowow = 16,
	.zbc_depth = 16,
	.zbc_cweaw_cowow = gm107_wtc_zbc_cweaw_cowow,
	.zbc_cweaw_depth = gm107_wtc_zbc_cweaw_depth,
	.invawidate = gf100_wtc_invawidate,
	.fwush = gf100_wtc_fwush,
};

int
gp100_wtc_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_wtc **pwtc)
{
	wetuwn nvkm_wtc_new_(&gp100_wtc, device, type, inst, pwtc);
}
