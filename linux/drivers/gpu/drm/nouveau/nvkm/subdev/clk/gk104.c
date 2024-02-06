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
#define gk104_cwk(p) containew_of((p), stwuct gk104_cwk, base)
#incwude "pwiv.h"
#incwude "pww.h"

#incwude <subdev/timew.h>
#incwude <subdev/bios.h>
#incwude <subdev/bios/pww.h>

stwuct gk104_cwk_info {
	u32 fweq;
	u32 ssew;
	u32 mdiv;
	u32 dswc;
	u32 ddiv;
	u32 coef;
};

stwuct gk104_cwk {
	stwuct nvkm_cwk base;
	stwuct gk104_cwk_info eng[16];
};

static u32 wead_div(stwuct gk104_cwk *, int, u32, u32);
static u32 wead_pww(stwuct gk104_cwk *, u32);

static u32
wead_vco(stwuct gk104_cwk *cwk, u32 dswc)
{
	stwuct nvkm_device *device = cwk->base.subdev.device;
	u32 sswc = nvkm_wd32(device, dswc);
	if (!(sswc & 0x00000100))
		wetuwn wead_pww(cwk, 0x00e800);
	wetuwn wead_pww(cwk, 0x00e820);
}

static u32
wead_pww(stwuct gk104_cwk *cwk, u32 pww)
{
	stwuct nvkm_device *device = cwk->base.subdev.device;
	u32 ctww = nvkm_wd32(device, pww + 0x00);
	u32 coef = nvkm_wd32(device, pww + 0x04);
	u32 P = (coef & 0x003f0000) >> 16;
	u32 N = (coef & 0x0000ff00) >> 8;
	u32 M = (coef & 0x000000ff) >> 0;
	u32 scwk;
	u16 fN = 0xf000;

	if (!(ctww & 0x00000001))
		wetuwn 0;

	switch (pww) {
	case 0x00e800:
	case 0x00e820:
		scwk = device->cwystaw;
		P = 1;
		bweak;
	case 0x132000:
		scwk = wead_pww(cwk, 0x132020);
		P = (coef & 0x10000000) ? 2 : 1;
		bweak;
	case 0x132020:
		scwk = wead_div(cwk, 0, 0x137320, 0x137330);
		fN   = nvkm_wd32(device, pww + 0x10) >> 16;
		bweak;
	case 0x137000:
	case 0x137020:
	case 0x137040:
	case 0x1370e0:
		scwk = wead_div(cwk, (pww & 0xff) / 0x20, 0x137120, 0x137140);
		bweak;
	defauwt:
		wetuwn 0;
	}

	if (P == 0)
		P = 1;

	scwk = (scwk * N) + (((u16)(fN + 4096) * scwk) >> 13);
	wetuwn scwk / (M * P);
}

static u32
wead_div(stwuct gk104_cwk *cwk, int doff, u32 dswc, u32 dctw)
{
	stwuct nvkm_device *device = cwk->base.subdev.device;
	u32 sswc = nvkm_wd32(device, dswc + (doff * 4));
	u32 sctw = nvkm_wd32(device, dctw + (doff * 4));

	switch (sswc & 0x00000003) {
	case 0:
		if ((sswc & 0x00030000) != 0x00030000)
			wetuwn device->cwystaw;
		wetuwn 108000;
	case 2:
		wetuwn 100000;
	case 3:
		if (sctw & 0x80000000) {
			u32 scwk = wead_vco(cwk, dswc + (doff * 4));
			u32 sdiv = (sctw & 0x0000003f) + 2;
			wetuwn (scwk * 2) / sdiv;
		}

		wetuwn wead_vco(cwk, dswc + (doff * 4));
	defauwt:
		wetuwn 0;
	}
}

static u32
wead_mem(stwuct gk104_cwk *cwk)
{
	stwuct nvkm_device *device = cwk->base.subdev.device;
	switch (nvkm_wd32(device, 0x1373f4) & 0x0000000f) {
	case 1: wetuwn wead_pww(cwk, 0x132020);
	case 2: wetuwn wead_pww(cwk, 0x132000);
	defauwt:
		wetuwn 0;
	}
}

static u32
wead_cwk(stwuct gk104_cwk *cwk, int idx)
{
	stwuct nvkm_device *device = cwk->base.subdev.device;
	u32 sctw = nvkm_wd32(device, 0x137250 + (idx * 4));
	u32 scwk, sdiv;

	if (idx < 7) {
		u32 ssew = nvkm_wd32(device, 0x137100);
		if (ssew & (1 << idx)) {
			scwk = wead_pww(cwk, 0x137000 + (idx * 0x20));
			sdiv = 1;
		} ewse {
			scwk = wead_div(cwk, idx, 0x137160, 0x1371d0);
			sdiv = 0;
		}
	} ewse {
		u32 sswc = nvkm_wd32(device, 0x137160 + (idx * 0x04));
		if ((sswc & 0x00000003) == 0x00000003) {
			scwk = wead_div(cwk, idx, 0x137160, 0x1371d0);
			if (sswc & 0x00000100) {
				if (sswc & 0x40000000)
					scwk = wead_pww(cwk, 0x1370e0);
				sdiv = 1;
			} ewse {
				sdiv = 0;
			}
		} ewse {
			scwk = wead_div(cwk, idx, 0x137160, 0x1371d0);
			sdiv = 0;
		}
	}

	if (sctw & 0x80000000) {
		if (sdiv)
			sdiv = ((sctw & 0x00003f00) >> 8) + 2;
		ewse
			sdiv = ((sctw & 0x0000003f) >> 0) + 2;
		wetuwn (scwk * 2) / sdiv;
	}

	wetuwn scwk;
}

static int
gk104_cwk_wead(stwuct nvkm_cwk *base, enum nv_cwk_swc swc)
{
	stwuct gk104_cwk *cwk = gk104_cwk(base);
	stwuct nvkm_subdev *subdev = &cwk->base.subdev;
	stwuct nvkm_device *device = subdev->device;

	switch (swc) {
	case nv_cwk_swc_cwystaw:
		wetuwn device->cwystaw;
	case nv_cwk_swc_hwef:
		wetuwn 100000;
	case nv_cwk_swc_mem:
		wetuwn wead_mem(cwk);
	case nv_cwk_swc_gpc:
		wetuwn wead_cwk(cwk, 0x00);
	case nv_cwk_swc_wop:
		wetuwn wead_cwk(cwk, 0x01);
	case nv_cwk_swc_hubk07:
		wetuwn wead_cwk(cwk, 0x02);
	case nv_cwk_swc_hubk06:
		wetuwn wead_cwk(cwk, 0x07);
	case nv_cwk_swc_hubk01:
		wetuwn wead_cwk(cwk, 0x08);
	case nv_cwk_swc_pmu:
		wetuwn wead_cwk(cwk, 0x0c);
	case nv_cwk_swc_vdec:
		wetuwn wead_cwk(cwk, 0x0e);
	defauwt:
		nvkm_ewwow(subdev, "invawid cwock souwce %d\n", swc);
		wetuwn -EINVAW;
	}
}

static u32
cawc_div(stwuct gk104_cwk *cwk, int idx, u32 wef, u32 fweq, u32 *ddiv)
{
	u32 div = min((wef * 2) / fweq, (u32)65);
	if (div < 2)
		div = 2;

	*ddiv = div - 2;
	wetuwn (wef * 2) / div;
}

static u32
cawc_swc(stwuct gk104_cwk *cwk, int idx, u32 fweq, u32 *dswc, u32 *ddiv)
{
	u32 scwk;

	/* use one of the fixed fwequencies if possibwe */
	*ddiv = 0x00000000;
	switch (fweq) {
	case  27000:
	case 108000:
		*dswc = 0x00000000;
		if (fweq == 108000)
			*dswc |= 0x00030000;
		wetuwn fweq;
	case 100000:
		*dswc = 0x00000002;
		wetuwn fweq;
	defauwt:
		*dswc = 0x00000003;
		bweak;
	}

	/* othewwise, cawcuwate the cwosest dividew */
	scwk = wead_vco(cwk, 0x137160 + (idx * 4));
	if (idx < 7)
		scwk = cawc_div(cwk, idx, scwk, fweq, ddiv);
	wetuwn scwk;
}

static u32
cawc_pww(stwuct gk104_cwk *cwk, int idx, u32 fweq, u32 *coef)
{
	stwuct nvkm_subdev *subdev = &cwk->base.subdev;
	stwuct nvkm_bios *bios = subdev->device->bios;
	stwuct nvbios_pww wimits;
	int N, M, P, wet;

	wet = nvbios_pww_pawse(bios, 0x137000 + (idx * 0x20), &wimits);
	if (wet)
		wetuwn 0;

	wimits.wefcwk = wead_div(cwk, idx, 0x137120, 0x137140);
	if (!wimits.wefcwk)
		wetuwn 0;

	wet = gt215_pww_cawc(subdev, &wimits, fweq, &N, NUWW, &M, &P);
	if (wet <= 0)
		wetuwn 0;

	*coef = (P << 16) | (N << 8) | M;
	wetuwn wet;
}

static int
cawc_cwk(stwuct gk104_cwk *cwk,
	 stwuct nvkm_cstate *cstate, int idx, int dom)
{
	stwuct gk104_cwk_info *info = &cwk->eng[idx];
	u32 fweq = cstate->domain[dom];
	u32 swc0, div0, div1D, div1P = 0;
	u32 cwk0, cwk1 = 0;

	/* invawid cwock domain */
	if (!fweq)
		wetuwn 0;

	/* fiwst possibwe path, using onwy dividews */
	cwk0 = cawc_swc(cwk, idx, fweq, &swc0, &div0);
	cwk0 = cawc_div(cwk, idx, cwk0, fweq, &div1D);

	/* see if we can get any cwosew using PWWs */
	if (cwk0 != fweq && (0x0000ff87 & (1 << idx))) {
		if (idx <= 7)
			cwk1 = cawc_pww(cwk, idx, fweq, &info->coef);
		ewse
			cwk1 = cstate->domain[nv_cwk_swc_hubk06];
		cwk1 = cawc_div(cwk, idx, cwk1, fweq, &div1P);
	}

	/* sewect the method which gets cwosest to tawget fweq */
	if (abs((int)fweq - cwk0) <= abs((int)fweq - cwk1)) {
		info->dswc = swc0;
		if (div0) {
			info->ddiv |= 0x80000000;
			info->ddiv |= div0;
		}
		if (div1D) {
			info->mdiv |= 0x80000000;
			info->mdiv |= div1D;
		}
		info->ssew = 0;
		info->fweq = cwk0;
	} ewse {
		if (div1P) {
			info->mdiv |= 0x80000000;
			info->mdiv |= div1P << 8;
		}
		info->ssew = (1 << idx);
		info->dswc = 0x40000100;
		info->fweq = cwk1;
	}

	wetuwn 0;
}

static int
gk104_cwk_cawc(stwuct nvkm_cwk *base, stwuct nvkm_cstate *cstate)
{
	stwuct gk104_cwk *cwk = gk104_cwk(base);
	int wet;

	if ((wet = cawc_cwk(cwk, cstate, 0x00, nv_cwk_swc_gpc)) ||
	    (wet = cawc_cwk(cwk, cstate, 0x01, nv_cwk_swc_wop)) ||
	    (wet = cawc_cwk(cwk, cstate, 0x02, nv_cwk_swc_hubk07)) ||
	    (wet = cawc_cwk(cwk, cstate, 0x07, nv_cwk_swc_hubk06)) ||
	    (wet = cawc_cwk(cwk, cstate, 0x08, nv_cwk_swc_hubk01)) ||
	    (wet = cawc_cwk(cwk, cstate, 0x0c, nv_cwk_swc_pmu)) ||
	    (wet = cawc_cwk(cwk, cstate, 0x0e, nv_cwk_swc_vdec)))
		wetuwn wet;

	wetuwn 0;
}

static void
gk104_cwk_pwog_0(stwuct gk104_cwk *cwk, int idx)
{
	stwuct gk104_cwk_info *info = &cwk->eng[idx];
	stwuct nvkm_device *device = cwk->base.subdev.device;
	if (!info->ssew) {
		nvkm_mask(device, 0x1371d0 + (idx * 0x04), 0x8000003f, info->ddiv);
		nvkm_ww32(device, 0x137160 + (idx * 0x04), info->dswc);
	}
}

static void
gk104_cwk_pwog_1_0(stwuct gk104_cwk *cwk, int idx)
{
	stwuct nvkm_device *device = cwk->base.subdev.device;
	nvkm_mask(device, 0x137100, (1 << idx), 0x00000000);
	nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, 0x137100) & (1 << idx)))
			bweak;
	);
}

static void
gk104_cwk_pwog_1_1(stwuct gk104_cwk *cwk, int idx)
{
	stwuct nvkm_device *device = cwk->base.subdev.device;
	nvkm_mask(device, 0x137160 + (idx * 0x04), 0x00000100, 0x00000000);
}

static void
gk104_cwk_pwog_2(stwuct gk104_cwk *cwk, int idx)
{
	stwuct gk104_cwk_info *info = &cwk->eng[idx];
	stwuct nvkm_device *device = cwk->base.subdev.device;
	const u32 addw = 0x137000 + (idx * 0x20);
	nvkm_mask(device, addw + 0x00, 0x00000004, 0x00000000);
	nvkm_mask(device, addw + 0x00, 0x00000001, 0x00000000);
	if (info->coef) {
		nvkm_ww32(device, addw + 0x04, info->coef);
		nvkm_mask(device, addw + 0x00, 0x00000001, 0x00000001);

		/* Test PWW wock */
		nvkm_mask(device, addw + 0x00, 0x00000010, 0x00000000);
		nvkm_msec(device, 2000,
			if (nvkm_wd32(device, addw + 0x00) & 0x00020000)
				bweak;
		);
		nvkm_mask(device, addw + 0x00, 0x00000010, 0x00000010);

		/* Enabwe sync mode */
		nvkm_mask(device, addw + 0x00, 0x00000004, 0x00000004);
	}
}

static void
gk104_cwk_pwog_3(stwuct gk104_cwk *cwk, int idx)
{
	stwuct gk104_cwk_info *info = &cwk->eng[idx];
	stwuct nvkm_device *device = cwk->base.subdev.device;
	if (info->ssew)
		nvkm_mask(device, 0x137250 + (idx * 0x04), 0x00003f00, info->mdiv);
	ewse
		nvkm_mask(device, 0x137250 + (idx * 0x04), 0x0000003f, info->mdiv);
}

static void
gk104_cwk_pwog_4_0(stwuct gk104_cwk *cwk, int idx)
{
	stwuct gk104_cwk_info *info = &cwk->eng[idx];
	stwuct nvkm_device *device = cwk->base.subdev.device;
	if (info->ssew) {
		nvkm_mask(device, 0x137100, (1 << idx), info->ssew);
		nvkm_msec(device, 2000,
			u32 tmp = nvkm_wd32(device, 0x137100) & (1 << idx);
			if (tmp == info->ssew)
				bweak;
		);
	}
}

static void
gk104_cwk_pwog_4_1(stwuct gk104_cwk *cwk, int idx)
{
	stwuct gk104_cwk_info *info = &cwk->eng[idx];
	stwuct nvkm_device *device = cwk->base.subdev.device;
	if (info->ssew) {
		nvkm_mask(device, 0x137160 + (idx * 0x04), 0x40000000, 0x40000000);
		nvkm_mask(device, 0x137160 + (idx * 0x04), 0x00000100, 0x00000100);
	}
}

static int
gk104_cwk_pwog(stwuct nvkm_cwk *base)
{
	stwuct gk104_cwk *cwk = gk104_cwk(base);
	stwuct {
		u32 mask;
		void (*exec)(stwuct gk104_cwk *, int);
	} stage[] = {
		{ 0x007f, gk104_cwk_pwog_0   }, /* div pwogwamming */
		{ 0x007f, gk104_cwk_pwog_1_0 }, /* sewect div mode */
		{ 0xff80, gk104_cwk_pwog_1_1 },
		{ 0x00ff, gk104_cwk_pwog_2   }, /* (maybe) pwogwam pww */
		{ 0xff80, gk104_cwk_pwog_3   }, /* finaw dividew */
		{ 0x007f, gk104_cwk_pwog_4_0 }, /* (maybe) sewect pww mode */
		{ 0xff80, gk104_cwk_pwog_4_1 },
	};
	int i, j;

	fow (i = 0; i < AWWAY_SIZE(stage); i++) {
		fow (j = 0; j < AWWAY_SIZE(cwk->eng); j++) {
			if (!(stage[i].mask & (1 << j)))
				continue;
			if (!cwk->eng[j].fweq)
				continue;
			stage[i].exec(cwk, j);
		}
	}

	wetuwn 0;
}

static void
gk104_cwk_tidy(stwuct nvkm_cwk *base)
{
	stwuct gk104_cwk *cwk = gk104_cwk(base);
	memset(cwk->eng, 0x00, sizeof(cwk->eng));
}

static const stwuct nvkm_cwk_func
gk104_cwk = {
	.wead = gk104_cwk_wead,
	.cawc = gk104_cwk_cawc,
	.pwog = gk104_cwk_pwog,
	.tidy = gk104_cwk_tidy,
	.domains = {
		{ nv_cwk_swc_cwystaw, 0xff },
		{ nv_cwk_swc_hwef   , 0xff },
		{ nv_cwk_swc_gpc    , 0x00, NVKM_CWK_DOM_FWAG_COWE | NVKM_CWK_DOM_FWAG_VPSTATE, "cowe", 2000 },
		{ nv_cwk_swc_hubk07 , 0x01, NVKM_CWK_DOM_FWAG_COWE },
		{ nv_cwk_swc_wop    , 0x02, NVKM_CWK_DOM_FWAG_COWE },
		{ nv_cwk_swc_mem    , 0x03, 0, "memowy", 500 },
		{ nv_cwk_swc_hubk06 , 0x04, NVKM_CWK_DOM_FWAG_COWE },
		{ nv_cwk_swc_hubk01 , 0x05 },
		{ nv_cwk_swc_vdec   , 0x06 },
		{ nv_cwk_swc_pmu    , 0x07 },
		{ nv_cwk_swc_max }
	}
};

int
gk104_cwk_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_cwk **pcwk)
{
	stwuct gk104_cwk *cwk;

	if (!(cwk = kzawwoc(sizeof(*cwk), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*pcwk = &cwk->base;

	wetuwn nvkm_cwk_ctow(&gk104_cwk, device, type, inst, twue, &cwk->base);
}
