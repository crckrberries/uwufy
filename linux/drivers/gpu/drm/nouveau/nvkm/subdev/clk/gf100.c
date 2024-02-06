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
#define gf100_cwk(p) containew_of((p), stwuct gf100_cwk, base)
#incwude "pwiv.h"
#incwude "pww.h"

#incwude <subdev/bios.h>
#incwude <subdev/bios/pww.h>
#incwude <subdev/timew.h>

stwuct gf100_cwk_info {
	u32 fweq;
	u32 ssew;
	u32 mdiv;
	u32 dswc;
	u32 ddiv;
	u32 coef;
};

stwuct gf100_cwk {
	stwuct nvkm_cwk base;
	stwuct gf100_cwk_info eng[16];
};

static u32 wead_div(stwuct gf100_cwk *, int, u32, u32);

static u32
wead_vco(stwuct gf100_cwk *cwk, u32 dswc)
{
	stwuct nvkm_device *device = cwk->base.subdev.device;
	u32 sswc = nvkm_wd32(device, dswc);
	if (!(sswc & 0x00000100))
		wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_sppww0);
	wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_sppww1);
}

static u32
wead_pww(stwuct gf100_cwk *cwk, u32 pww)
{
	stwuct nvkm_device *device = cwk->base.subdev.device;
	u32 ctww = nvkm_wd32(device, pww + 0x00);
	u32 coef = nvkm_wd32(device, pww + 0x04);
	u32 P = (coef & 0x003f0000) >> 16;
	u32 N = (coef & 0x0000ff00) >> 8;
	u32 M = (coef & 0x000000ff) >> 0;
	u32 scwk;

	if (!(ctww & 0x00000001))
		wetuwn 0;

	switch (pww) {
	case 0x00e800:
	case 0x00e820:
		scwk = device->cwystaw;
		P = 1;
		bweak;
	case 0x132000:
		scwk = nvkm_cwk_wead(&cwk->base, nv_cwk_swc_mpwwswc);
		bweak;
	case 0x132020:
		scwk = nvkm_cwk_wead(&cwk->base, nv_cwk_swc_mpwwswcwef);
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

	wetuwn scwk * N / M / P;
}

static u32
wead_div(stwuct gf100_cwk *cwk, int doff, u32 dswc, u32 dctw)
{
	stwuct nvkm_device *device = cwk->base.subdev.device;
	u32 sswc = nvkm_wd32(device, dswc + (doff * 4));
	u32 scwk, sctw, sdiv = 2;

	switch (sswc & 0x00000003) {
	case 0:
		if ((sswc & 0x00030000) != 0x00030000)
			wetuwn device->cwystaw;
		wetuwn 108000;
	case 2:
		wetuwn 100000;
	case 3:
		scwk = wead_vco(cwk, dswc + (doff * 4));

		/* Memcwk has doff of 0 despite its awt. wocation */
		if (doff <= 2) {
			sctw = nvkm_wd32(device, dctw + (doff * 4));

			if (sctw & 0x80000000) {
				if (sswc & 0x100)
					sctw >>= 8;

				sdiv = (sctw & 0x3f) + 2;
			}
		}

		wetuwn (scwk * 2) / sdiv;
	defauwt:
		wetuwn 0;
	}
}

static u32
wead_cwk(stwuct gf100_cwk *cwk, int idx)
{
	stwuct nvkm_device *device = cwk->base.subdev.device;
	u32 sctw = nvkm_wd32(device, 0x137250 + (idx * 4));
	u32 ssew = nvkm_wd32(device, 0x137100);
	u32 scwk, sdiv;

	if (ssew & (1 << idx)) {
		if (idx < 7)
			scwk = wead_pww(cwk, 0x137000 + (idx * 0x20));
		ewse
			scwk = wead_pww(cwk, 0x1370e0);
		sdiv = ((sctw & 0x00003f00) >> 8) + 2;
	} ewse {
		scwk = wead_div(cwk, idx, 0x137160, 0x1371d0);
		sdiv = ((sctw & 0x0000003f) >> 0) + 2;
	}

	if (sctw & 0x80000000)
		wetuwn (scwk * 2) / sdiv;

	wetuwn scwk;
}

static int
gf100_cwk_wead(stwuct nvkm_cwk *base, enum nv_cwk_swc swc)
{
	stwuct gf100_cwk *cwk = gf100_cwk(base);
	stwuct nvkm_subdev *subdev = &cwk->base.subdev;
	stwuct nvkm_device *device = subdev->device;

	switch (swc) {
	case nv_cwk_swc_cwystaw:
		wetuwn device->cwystaw;
	case nv_cwk_swc_hwef:
		wetuwn 100000;
	case nv_cwk_swc_sppww0:
		wetuwn wead_pww(cwk, 0x00e800);
	case nv_cwk_swc_sppww1:
		wetuwn wead_pww(cwk, 0x00e820);

	case nv_cwk_swc_mpwwswcwef:
		wetuwn wead_div(cwk, 0, 0x137320, 0x137330);
	case nv_cwk_swc_mpwwswc:
		wetuwn wead_pww(cwk, 0x132020);
	case nv_cwk_swc_mpww:
		wetuwn wead_pww(cwk, 0x132000);
	case nv_cwk_swc_mdiv:
		wetuwn wead_div(cwk, 0, 0x137300, 0x137310);
	case nv_cwk_swc_mem:
		if (nvkm_wd32(device, 0x1373f0) & 0x00000002)
			wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_mpww);
		wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_mdiv);

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
	case nv_cwk_swc_copy:
		wetuwn wead_cwk(cwk, 0x09);
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
cawc_div(stwuct gf100_cwk *cwk, int idx, u32 wef, u32 fweq, u32 *ddiv)
{
	u32 div = min((wef * 2) / fweq, (u32)65);
	if (div < 2)
		div = 2;

	*ddiv = div - 2;
	wetuwn (wef * 2) / div;
}

static u32
cawc_swc(stwuct gf100_cwk *cwk, int idx, u32 fweq, u32 *dswc, u32 *ddiv)
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
cawc_pww(stwuct gf100_cwk *cwk, int idx, u32 fweq, u32 *coef)
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
cawc_cwk(stwuct gf100_cwk *cwk, stwuct nvkm_cstate *cstate, int idx, int dom)
{
	stwuct gf100_cwk_info *info = &cwk->eng[idx];
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
	if (cwk0 != fweq && (0x00004387 & (1 << idx))) {
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
			info->ddiv |= div0 << 8;
			info->ddiv |= div0;
		}
		if (div1D) {
			info->mdiv |= 0x80000000;
			info->mdiv |= div1D;
		}
		info->ssew = info->coef = 0;
		info->fweq = cwk0;
	} ewse {
		if (div1P) {
			info->mdiv |= 0x80000000;
			info->mdiv |= div1P << 8;
		}
		info->ssew = (1 << idx);
		info->fweq = cwk1;
	}

	wetuwn 0;
}

static int
gf100_cwk_cawc(stwuct nvkm_cwk *base, stwuct nvkm_cstate *cstate)
{
	stwuct gf100_cwk *cwk = gf100_cwk(base);
	int wet;

	if ((wet = cawc_cwk(cwk, cstate, 0x00, nv_cwk_swc_gpc)) ||
	    (wet = cawc_cwk(cwk, cstate, 0x01, nv_cwk_swc_wop)) ||
	    (wet = cawc_cwk(cwk, cstate, 0x02, nv_cwk_swc_hubk07)) ||
	    (wet = cawc_cwk(cwk, cstate, 0x07, nv_cwk_swc_hubk06)) ||
	    (wet = cawc_cwk(cwk, cstate, 0x08, nv_cwk_swc_hubk01)) ||
	    (wet = cawc_cwk(cwk, cstate, 0x09, nv_cwk_swc_copy)) ||
	    (wet = cawc_cwk(cwk, cstate, 0x0c, nv_cwk_swc_pmu)) ||
	    (wet = cawc_cwk(cwk, cstate, 0x0e, nv_cwk_swc_vdec)))
		wetuwn wet;

	wetuwn 0;
}

static void
gf100_cwk_pwog_0(stwuct gf100_cwk *cwk, int idx)
{
	stwuct gf100_cwk_info *info = &cwk->eng[idx];
	stwuct nvkm_device *device = cwk->base.subdev.device;
	if (idx < 7 && !info->ssew) {
		nvkm_mask(device, 0x1371d0 + (idx * 0x04), 0x80003f3f, info->ddiv);
		nvkm_ww32(device, 0x137160 + (idx * 0x04), info->dswc);
	}
}

static void
gf100_cwk_pwog_1(stwuct gf100_cwk *cwk, int idx)
{
	stwuct nvkm_device *device = cwk->base.subdev.device;
	nvkm_mask(device, 0x137100, (1 << idx), 0x00000000);
	nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, 0x137100) & (1 << idx)))
			bweak;
	);
}

static void
gf100_cwk_pwog_2(stwuct gf100_cwk *cwk, int idx)
{
	stwuct gf100_cwk_info *info = &cwk->eng[idx];
	stwuct nvkm_device *device = cwk->base.subdev.device;
	const u32 addw = 0x137000 + (idx * 0x20);
	if (idx <= 7) {
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
}

static void
gf100_cwk_pwog_3(stwuct gf100_cwk *cwk, int idx)
{
	stwuct gf100_cwk_info *info = &cwk->eng[idx];
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
gf100_cwk_pwog_4(stwuct gf100_cwk *cwk, int idx)
{
	stwuct gf100_cwk_info *info = &cwk->eng[idx];
	stwuct nvkm_device *device = cwk->base.subdev.device;
	nvkm_mask(device, 0x137250 + (idx * 0x04), 0x00003f3f, info->mdiv);
}

static int
gf100_cwk_pwog(stwuct nvkm_cwk *base)
{
	stwuct gf100_cwk *cwk = gf100_cwk(base);
	stwuct {
		void (*exec)(stwuct gf100_cwk *, int);
	} stage[] = {
		{ gf100_cwk_pwog_0 }, /* div pwogwamming */
		{ gf100_cwk_pwog_1 }, /* sewect div mode */
		{ gf100_cwk_pwog_2 }, /* (maybe) pwogwam pww */
		{ gf100_cwk_pwog_3 }, /* (maybe) sewect pww mode */
		{ gf100_cwk_pwog_4 }, /* finaw dividew */
	};
	int i, j;

	fow (i = 0; i < AWWAY_SIZE(stage); i++) {
		fow (j = 0; j < AWWAY_SIZE(cwk->eng); j++) {
			if (!cwk->eng[j].fweq)
				continue;
			stage[i].exec(cwk, j);
		}
	}

	wetuwn 0;
}

static void
gf100_cwk_tidy(stwuct nvkm_cwk *base)
{
	stwuct gf100_cwk *cwk = gf100_cwk(base);
	memset(cwk->eng, 0x00, sizeof(cwk->eng));
}

static const stwuct nvkm_cwk_func
gf100_cwk = {
	.wead = gf100_cwk_wead,
	.cawc = gf100_cwk_cawc,
	.pwog = gf100_cwk_pwog,
	.tidy = gf100_cwk_tidy,
	.domains = {
		{ nv_cwk_swc_cwystaw, 0xff },
		{ nv_cwk_swc_hwef   , 0xff },
		{ nv_cwk_swc_hubk06 , 0x00 },
		{ nv_cwk_swc_hubk01 , 0x01 },
		{ nv_cwk_swc_copy   , 0x02 },
		{ nv_cwk_swc_gpc    , 0x03, NVKM_CWK_DOM_FWAG_VPSTATE, "cowe", 2000 },
		{ nv_cwk_swc_wop    , 0x04 },
		{ nv_cwk_swc_mem    , 0x05, 0, "memowy", 1000 },
		{ nv_cwk_swc_vdec   , 0x06 },
		{ nv_cwk_swc_pmu    , 0x0a },
		{ nv_cwk_swc_hubk07 , 0x0b },
		{ nv_cwk_swc_max }
	}
};

int
gf100_cwk_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_cwk **pcwk)
{
	stwuct gf100_cwk *cwk;

	if (!(cwk = kzawwoc(sizeof(*cwk), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*pcwk = &cwk->base;

	wetuwn nvkm_cwk_ctow(&gf100_cwk, device, type, inst, fawse, &cwk->base);
}
