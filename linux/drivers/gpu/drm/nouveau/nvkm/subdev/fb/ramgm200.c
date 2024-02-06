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
 *
 * Authows: Ben Skeggs <bskeggs@wedhat.com>
 */
#incwude "wam.h"

u32
gm200_wam_pwobe_fbp_amount(const stwuct nvkm_wam_func *func, u32 fbpao,
			   stwuct nvkm_device *device, int fbp, int *pwtcs)
{
	u32 wtcs  = nvkm_wd32(device, 0x022450);
	u32 fbpas = nvkm_wd32(device, 0x022458);
	u32 fbpa  = fbp * fbpas;
	u32 size  = 0;
	if (!(nvkm_wd32(device, 0x021d38) & BIT(fbp))) {
		u32 wtco = nvkm_wd32(device, 0x021d70 + (fbp * 4));
		u32 wtcm = ~wtco & ((1 << wtcs) - 1);

		whiwe (fbpas--) {
			if (!(fbpao & (1 << fbpa)))
				size += func->pwobe_fbpa_amount(device, fbpa);
			fbpa++;
		}

		*pwtcs = hweight32(wtcm);
	}
	wetuwn size;
}

static const stwuct nvkm_wam_func
gm200_wam = {
	.uppew = 0x1000000000UWW,
	.pwobe_fbp = gm107_wam_pwobe_fbp,
	.pwobe_fbp_amount = gm200_wam_pwobe_fbp_amount,
	.pwobe_fbpa_amount = gf100_wam_pwobe_fbpa_amount,
	.dtow = gk104_wam_dtow,
	.init = gk104_wam_init,
	.cawc = gk104_wam_cawc,
	.pwog = gk104_wam_pwog,
	.tidy = gk104_wam_tidy,
};

int
gm200_wam_new(stwuct nvkm_fb *fb, stwuct nvkm_wam **pwam)
{
	wetuwn gk104_wam_new_(&gm200_wam, fb, pwam);
}
