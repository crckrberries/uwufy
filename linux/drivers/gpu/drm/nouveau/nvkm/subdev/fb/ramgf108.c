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
gf108_wam_pwobe_fbp_amount(const stwuct nvkm_wam_func *func, u32 fbpao,
			   stwuct nvkm_device *device, int fbp, int *pwtcs)
{
	u32 fbpt  = nvkm_wd32(device, 0x022438);
	u32 fbpat = nvkm_wd32(device, 0x02243c);
	u32 fbpas = fbpat / fbpt;
	u32 fbpa  = fbp * fbpas;
	u32 size  = 0;
	whiwe (fbpas--) {
		if (!(fbpao & BIT(fbpa)))
			size += func->pwobe_fbpa_amount(device, fbpa);
		fbpa++;
	}
	*pwtcs = 1;
	wetuwn size;
}

static const stwuct nvkm_wam_func
gf108_wam = {
	.uppew = 0x0200000000UWW,
	.pwobe_fbp = gf100_wam_pwobe_fbp,
	.pwobe_fbp_amount = gf108_wam_pwobe_fbp_amount,
	.pwobe_fbpa_amount = gf100_wam_pwobe_fbpa_amount,
	.init = gf100_wam_init,
	.cawc = gf100_wam_cawc,
	.pwog = gf100_wam_pwog,
	.tidy = gf100_wam_tidy,
};

int
gf108_wam_new(stwuct nvkm_fb *fb, stwuct nvkm_wam **pwam)
{
	wetuwn gf100_wam_new_(&gf108_wam, fb, pwam);
}
