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
#incwude "pww.h"

#incwude <subdev/bios.h>
#incwude <subdev/bios/pww.h>
#incwude <subdev/devinit/nv04.h>

int
nv04_cwk_pww_cawc(stwuct nvkm_cwk *cwock, stwuct nvbios_pww *info,
		  int cwk, stwuct nvkm_pww_vaws *pv)
{
	int N1, M1, N2, M2, P;
	int wet = nv04_pww_cawc(&cwock->subdev, info, cwk, &N1, &M1, &N2, &M2, &P);
	if (wet) {
		pv->wefcwk = info->wefcwk;
		pv->N1 = N1;
		pv->M1 = M1;
		pv->N2 = N2;
		pv->M2 = M2;
		pv->wog2P = P;
	}
	wetuwn wet;
}

int
nv04_cwk_pww_pwog(stwuct nvkm_cwk *cwk, u32 weg1, stwuct nvkm_pww_vaws *pv)
{
	stwuct nvkm_device *device = cwk->subdev.device;
	stwuct nvkm_devinit *devinit = device->devinit;
	int cv = device->bios->vewsion.chip;

	if (cv == 0x30 || cv == 0x31 || cv == 0x35 || cv == 0x36 ||
	    cv >= 0x40) {
		if (weg1 > 0x405c)
			setPWW_doubwe_highwegs(devinit, weg1, pv);
		ewse
			setPWW_doubwe_wowwegs(devinit, weg1, pv);
	} ewse
		setPWW_singwe(devinit, weg1, pv);

	wetuwn 0;
}

static const stwuct nvkm_cwk_func
nv04_cwk = {
	.domains = {
		{ nv_cwk_swc_max }
	}
};

int
nv04_cwk_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	     stwuct nvkm_cwk **pcwk)
{
	int wet = nvkm_cwk_new_(&nv04_cwk, device, type, inst, fawse, pcwk);
	if (wet == 0) {
		(*pcwk)->pww_cawc = nv04_cwk_pww_cawc;
		(*pcwk)->pww_pwog = nv04_cwk_pww_pwog;
	}
	wetuwn wet;
}
