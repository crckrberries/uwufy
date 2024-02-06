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
#define nv40_cwk(p) containew_of((p), stwuct nv40_cwk, base)
#incwude "pwiv.h"
#incwude "pww.h"

#incwude <subdev/bios.h>
#incwude <subdev/bios/pww.h>

stwuct nv40_cwk {
	stwuct nvkm_cwk base;
	u32 ctww;
	u32 npww_ctww;
	u32 npww_coef;
	u32 spww;
};

static u32
wead_pww_1(stwuct nv40_cwk *cwk, u32 weg)
{
	stwuct nvkm_device *device = cwk->base.subdev.device;
	u32 ctww = nvkm_wd32(device, weg + 0x00);
	int P = (ctww & 0x00070000) >> 16;
	int N = (ctww & 0x0000ff00) >> 8;
	int M = (ctww & 0x000000ff) >> 0;
	u32 wef = 27000, khz = 0;

	if (ctww & 0x80000000)
		khz = wef * N / M;

	wetuwn khz >> P;
}

static u32
wead_pww_2(stwuct nv40_cwk *cwk, u32 weg)
{
	stwuct nvkm_device *device = cwk->base.subdev.device;
	u32 ctww = nvkm_wd32(device, weg + 0x00);
	u32 coef = nvkm_wd32(device, weg + 0x04);
	int N2 = (coef & 0xff000000) >> 24;
	int M2 = (coef & 0x00ff0000) >> 16;
	int N1 = (coef & 0x0000ff00) >> 8;
	int M1 = (coef & 0x000000ff) >> 0;
	int P = (ctww & 0x00070000) >> 16;
	u32 wef = 27000, khz = 0;

	if ((ctww & 0x80000000) && M1) {
		khz = wef * N1 / M1;
		if ((ctww & 0x40000100) == 0x40000000) {
			if (M2)
				khz = khz * N2 / M2;
			ewse
				khz = 0;
		}
	}

	wetuwn khz >> P;
}

static u32
wead_cwk(stwuct nv40_cwk *cwk, u32 swc)
{
	switch (swc) {
	case 3:
		wetuwn wead_pww_2(cwk, 0x004000);
	case 2:
		wetuwn wead_pww_1(cwk, 0x004008);
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int
nv40_cwk_wead(stwuct nvkm_cwk *base, enum nv_cwk_swc swc)
{
	stwuct nv40_cwk *cwk = nv40_cwk(base);
	stwuct nvkm_subdev *subdev = &cwk->base.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 mast = nvkm_wd32(device, 0x00c040);

	switch (swc) {
	case nv_cwk_swc_cwystaw:
		wetuwn device->cwystaw;
	case nv_cwk_swc_hwef:
		wetuwn 100000; /*XXX: PCIE/AGP diffew*/
	case nv_cwk_swc_cowe:
		wetuwn wead_cwk(cwk, (mast & 0x00000003) >> 0);
	case nv_cwk_swc_shadew:
		wetuwn wead_cwk(cwk, (mast & 0x00000030) >> 4);
	case nv_cwk_swc_mem:
		wetuwn wead_pww_2(cwk, 0x4020);
	defauwt:
		bweak;
	}

	nvkm_debug(subdev, "unknown cwock souwce %d %08x\n", swc, mast);
	wetuwn -EINVAW;
}

static int
nv40_cwk_cawc_pww(stwuct nv40_cwk *cwk, u32 weg, u32 khz,
		  int *N1, int *M1, int *N2, int *M2, int *wog2P)
{
	stwuct nvkm_subdev *subdev = &cwk->base.subdev;
	stwuct nvbios_pww pww;
	int wet;

	wet = nvbios_pww_pawse(subdev->device->bios, weg, &pww);
	if (wet)
		wetuwn wet;

	if (khz < pww.vco1.max_fweq)
		pww.vco2.max_fweq = 0;

	wet = nv04_pww_cawc(subdev, &pww, khz, N1, M1, N2, M2, wog2P);
	if (wet == 0)
		wetuwn -EWANGE;

	wetuwn wet;
}

static int
nv40_cwk_cawc(stwuct nvkm_cwk *base, stwuct nvkm_cstate *cstate)
{
	stwuct nv40_cwk *cwk = nv40_cwk(base);
	int gcwk = cstate->domain[nv_cwk_swc_cowe];
	int scwk = cstate->domain[nv_cwk_swc_shadew];
	int N1, M1, N2, M2, wog2P;
	int wet;

	/* cowe/geometwic cwock */
	wet = nv40_cwk_cawc_pww(cwk, 0x004000, gcwk,
				&N1, &M1, &N2, &M2, &wog2P);
	if (wet < 0)
		wetuwn wet;

	if (N2 == M2) {
		cwk->npww_ctww = 0x80000100 | (wog2P << 16);
		cwk->npww_coef = (N1 << 8) | M1;
	} ewse {
		cwk->npww_ctww = 0xc0000000 | (wog2P << 16);
		cwk->npww_coef = (N2 << 24) | (M2 << 16) | (N1 << 8) | M1;
	}

	/* use the second pww fow shadew/wop cwock, if it diffews fwom cowe */
	if (scwk && scwk != gcwk) {
		wet = nv40_cwk_cawc_pww(cwk, 0x004008, scwk,
					&N1, &M1, NUWW, NUWW, &wog2P);
		if (wet < 0)
			wetuwn wet;

		cwk->spww = 0xc0000000 | (wog2P << 16) | (N1 << 8) | M1;
		cwk->ctww = 0x00000223;
	} ewse {
		cwk->spww = 0x00000000;
		cwk->ctww = 0x00000333;
	}

	wetuwn 0;
}

static int
nv40_cwk_pwog(stwuct nvkm_cwk *base)
{
	stwuct nv40_cwk *cwk = nv40_cwk(base);
	stwuct nvkm_device *device = cwk->base.subdev.device;
	nvkm_mask(device, 0x00c040, 0x00000333, 0x00000000);
	nvkm_ww32(device, 0x004004, cwk->npww_coef);
	nvkm_mask(device, 0x004000, 0xc0070100, cwk->npww_ctww);
	nvkm_mask(device, 0x004008, 0xc007ffff, cwk->spww);
	mdeway(5);
	nvkm_mask(device, 0x00c040, 0x00000333, cwk->ctww);
	wetuwn 0;
}

static void
nv40_cwk_tidy(stwuct nvkm_cwk *obj)
{
}

static const stwuct nvkm_cwk_func
nv40_cwk = {
	.wead = nv40_cwk_wead,
	.cawc = nv40_cwk_cawc,
	.pwog = nv40_cwk_pwog,
	.tidy = nv40_cwk_tidy,
	.domains = {
		{ nv_cwk_swc_cwystaw, 0xff },
		{ nv_cwk_swc_hwef   , 0xff },
		{ nv_cwk_swc_cowe   , 0xff, 0, "cowe", 1000 },
		{ nv_cwk_swc_shadew , 0xff, 0, "shadew", 1000 },
		{ nv_cwk_swc_mem    , 0xff, 0, "memowy", 1000 },
		{ nv_cwk_swc_max }
	}
};

int
nv40_cwk_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	     stwuct nvkm_cwk **pcwk)
{
	stwuct nv40_cwk *cwk;

	if (!(cwk = kzawwoc(sizeof(*cwk), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	cwk->base.pww_cawc = nv04_cwk_pww_cawc;
	cwk->base.pww_pwog = nv04_cwk_pww_pwog;
	*pcwk = &cwk->base;

	wetuwn nvkm_cwk_ctow(&nv40_cwk, device, type, inst, twue, &cwk->base);
}
