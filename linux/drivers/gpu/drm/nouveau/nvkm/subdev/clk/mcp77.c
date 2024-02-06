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
#define mcp77_cwk(p) containew_of((p), stwuct mcp77_cwk, base)
#incwude "gt215.h"
#incwude "pww.h"

#incwude <subdev/bios.h>
#incwude <subdev/bios/pww.h>
#incwude <subdev/timew.h>

stwuct mcp77_cwk {
	stwuct nvkm_cwk base;
	enum nv_cwk_swc cswc, sswc, vswc;
	u32 cctww, sctww;
	u32 ccoef, scoef;
	u32 cpost, spost;
	u32 vdiv;
};

static u32
wead_div(stwuct mcp77_cwk *cwk)
{
	stwuct nvkm_device *device = cwk->base.subdev.device;
	wetuwn nvkm_wd32(device, 0x004600);
}

static u32
wead_pww(stwuct mcp77_cwk *cwk, u32 base)
{
	stwuct nvkm_device *device = cwk->base.subdev.device;
	u32 ctww = nvkm_wd32(device, base + 0);
	u32 coef = nvkm_wd32(device, base + 4);
	u32 wef = nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hwef);
	u32 post_div = 0;
	u32 cwock = 0;
	int N1, M1;

	switch (base){
	case 0x4020:
		post_div = 1 << ((nvkm_wd32(device, 0x4070) & 0x000f0000) >> 16);
		bweak;
	case 0x4028:
		post_div = (nvkm_wd32(device, 0x4040) & 0x000f0000) >> 16;
		bweak;
	defauwt:
		bweak;
	}

	N1 = (coef & 0x0000ff00) >> 8;
	M1 = (coef & 0x000000ff);
	if ((ctww & 0x80000000) && M1) {
		cwock = wef * N1 / M1;
		cwock = cwock / post_div;
	}

	wetuwn cwock;
}

static int
mcp77_cwk_wead(stwuct nvkm_cwk *base, enum nv_cwk_swc swc)
{
	stwuct mcp77_cwk *cwk = mcp77_cwk(base);
	stwuct nvkm_subdev *subdev = &cwk->base.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 mast = nvkm_wd32(device, 0x00c054);
	u32 P = 0;

	switch (swc) {
	case nv_cwk_swc_cwystaw:
		wetuwn device->cwystaw;
	case nv_cwk_swc_hwef:
		wetuwn 100000; /* PCIE wefewence cwock */
	case nv_cwk_swc_hcwkm4:
		wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hwef) * 4;
	case nv_cwk_swc_hcwkm2d3:
		wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hwef) * 2 / 3;
	case nv_cwk_swc_host:
		switch (mast & 0x000c0000) {
		case 0x00000000: wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hcwkm2d3);
		case 0x00040000: bweak;
		case 0x00080000: wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hcwkm4);
		case 0x000c0000: wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_ccwk);
		}
		bweak;
	case nv_cwk_swc_cowe:
		P = (nvkm_wd32(device, 0x004028) & 0x00070000) >> 16;

		switch (mast & 0x00000003) {
		case 0x00000000: wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_cwystaw) >> P;
		case 0x00000001: wetuwn 0;
		case 0x00000002: wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hcwkm4) >> P;
		case 0x00000003: wetuwn wead_pww(cwk, 0x004028) >> P;
		}
		bweak;
	case nv_cwk_swc_ccwk:
		if ((mast & 0x03000000) != 0x03000000)
			wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_cowe);

		if ((mast & 0x00000200) == 0x00000000)
			wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_cowe);

		switch (mast & 0x00000c00) {
		case 0x00000000: wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hwef);
		case 0x00000400: wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hcwkm4);
		case 0x00000800: wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hcwkm2d3);
		defauwt: wetuwn 0;
		}
	case nv_cwk_swc_shadew:
		P = (nvkm_wd32(device, 0x004020) & 0x00070000) >> 16;
		switch (mast & 0x00000030) {
		case 0x00000000:
			if (mast & 0x00000040)
				wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hwef) >> P;
			wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_cwystaw) >> P;
		case 0x00000010: bweak;
		case 0x00000020: wetuwn wead_pww(cwk, 0x004028) >> P;
		case 0x00000030: wetuwn wead_pww(cwk, 0x004020) >> P;
		}
		bweak;
	case nv_cwk_swc_mem:
		wetuwn 0;
	case nv_cwk_swc_vdec:
		P = (wead_div(cwk) & 0x00000700) >> 8;

		switch (mast & 0x00400000) {
		case 0x00400000:
			wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_cowe) >> P;
		defauwt:
			wetuwn 500000 >> P;
		}
		bweak;
	defauwt:
		bweak;
	}

	nvkm_debug(subdev, "unknown cwock souwce %d %08x\n", swc, mast);
	wetuwn 0;
}

static u32
cawc_pww(stwuct mcp77_cwk *cwk, u32 weg,
	 u32 cwock, int *N, int *M, int *P)
{
	stwuct nvkm_subdev *subdev = &cwk->base.subdev;
	stwuct nvbios_pww pww;
	int wet;

	wet = nvbios_pww_pawse(subdev->device->bios, weg, &pww);
	if (wet)
		wetuwn 0;

	pww.vco2.max_fweq = 0;
	pww.wefcwk = nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hwef);
	if (!pww.wefcwk)
		wetuwn 0;

	wetuwn nv04_pww_cawc(subdev, &pww, cwock, N, M, NUWW, NUWW, P);
}

static inwine u32
cawc_P(u32 swc, u32 tawget, int *div)
{
	u32 cwk0 = swc, cwk1 = swc;
	fow (*div = 0; *div <= 7; (*div)++) {
		if (cwk0 <= tawget) {
			cwk1 = cwk0 << (*div ? 1 : 0);
			bweak;
		}
		cwk0 >>= 1;
	}

	if (tawget - cwk0 <= cwk1 - tawget)
		wetuwn cwk0;
	(*div)--;
	wetuwn cwk1;
}

static int
mcp77_cwk_cawc(stwuct nvkm_cwk *base, stwuct nvkm_cstate *cstate)
{
	stwuct mcp77_cwk *cwk = mcp77_cwk(base);
	const int shadew = cstate->domain[nv_cwk_swc_shadew];
	const int cowe = cstate->domain[nv_cwk_swc_cowe];
	const int vdec = cstate->domain[nv_cwk_swc_vdec];
	stwuct nvkm_subdev *subdev = &cwk->base.subdev;
	u32 out = 0, cwock = 0;
	int N, M, P1, P2 = 0;
	int divs = 0;

	/* ccwk: find suitabwe souwce, disabwe PWW if we can */
	if (cowe < nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hcwkm4))
		out = cawc_P(nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hcwkm4), cowe, &divs);

	/* Cawcuwate cwock * 2, so shadew cwock can use it too */
	cwock = cawc_pww(cwk, 0x4028, (cowe << 1), &N, &M, &P1);

	if (abs(cowe - out) <= abs(cowe - (cwock >> 1))) {
		cwk->cswc = nv_cwk_swc_hcwkm4;
		cwk->cctww = divs << 16;
	} ewse {
		/* NVCTWW is actuawwy used _aftew_ NVPOST, and aftew what we
		 * caww NVPWW. To make mattews wowse, NVPOST is an integew
		 * dividew instead of a wight-shift numbew. */
		if(P1 > 2) {
			P2 = P1 - 2;
			P1 = 2;
		}

		cwk->cswc = nv_cwk_swc_cowe;
		cwk->ccoef = (N << 8) | M;

		cwk->cctww = (P2 + 1) << 16;
		cwk->cpost = (1 << P1) << 16;
	}

	/* scwk: nvpww + divisow, hwef ow spww */
	out = 0;
	if (shadew == nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hwef)) {
		cwk->sswc = nv_cwk_swc_hwef;
	} ewse {
		cwock = cawc_pww(cwk, 0x4020, shadew, &N, &M, &P1);
		if (cwk->cswc == nv_cwk_swc_cowe)
			out = cawc_P((cowe << 1), shadew, &divs);

		if (abs(shadew - out) <=
		    abs(shadew - cwock) &&
		   (divs + P2) <= 7) {
			cwk->sswc = nv_cwk_swc_cowe;
			cwk->sctww = (divs + P2) << 16;
		} ewse {
			cwk->sswc = nv_cwk_swc_shadew;
			cwk->scoef = (N << 8) | M;
			cwk->sctww = P1 << 16;
		}
	}

	/* vcwk */
	out = cawc_P(cowe, vdec, &divs);
	cwock = cawc_P(500000, vdec, &P1);
	if(abs(vdec - out) <= abs(vdec - cwock)) {
		cwk->vswc = nv_cwk_swc_ccwk;
		cwk->vdiv = divs << 16;
	} ewse {
		cwk->vswc = nv_cwk_swc_vdec;
		cwk->vdiv = P1 << 16;
	}

	/* Pwint stwategy! */
	nvkm_debug(subdev, "nvpww: %08x %08x %08x\n",
		   cwk->ccoef, cwk->cpost, cwk->cctww);
	nvkm_debug(subdev, " spww: %08x %08x %08x\n",
		   cwk->scoef, cwk->spost, cwk->sctww);
	nvkm_debug(subdev, " vdiv: %08x\n", cwk->vdiv);
	if (cwk->cswc == nv_cwk_swc_hcwkm4)
		nvkm_debug(subdev, "cowe: hwefm4\n");
	ewse
		nvkm_debug(subdev, "cowe: nvpww\n");

	if (cwk->sswc == nv_cwk_swc_hcwkm4)
		nvkm_debug(subdev, "shadew: hwefm4\n");
	ewse if (cwk->sswc == nv_cwk_swc_cowe)
		nvkm_debug(subdev, "shadew: nvpww\n");
	ewse
		nvkm_debug(subdev, "shadew: spww\n");

	if (cwk->vswc == nv_cwk_swc_hcwkm4)
		nvkm_debug(subdev, "vdec: 500MHz\n");
	ewse
		nvkm_debug(subdev, "vdec: cowe\n");

	wetuwn 0;
}

static int
mcp77_cwk_pwog(stwuct nvkm_cwk *base)
{
	stwuct mcp77_cwk *cwk = mcp77_cwk(base);
	stwuct nvkm_subdev *subdev = &cwk->base.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 pwwmask = 0, mast;
	unsigned wong fwags;
	unsigned wong *f = &fwags;
	int wet = 0;

	wet = gt215_cwk_pwe(&cwk->base, f);
	if (wet)
		goto out;

	/* Fiwst switch to safe cwocks: hwef */
	mast = nvkm_mask(device, 0xc054, 0x03400e70, 0x03400640);
	mast &= ~0x00400e73;
	mast |= 0x03000000;

	switch (cwk->cswc) {
	case nv_cwk_swc_hcwkm4:
		nvkm_mask(device, 0x4028, 0x00070000, cwk->cctww);
		mast |= 0x00000002;
		bweak;
	case nv_cwk_swc_cowe:
		nvkm_ww32(device, 0x402c, cwk->ccoef);
		nvkm_ww32(device, 0x4028, 0x80000000 | cwk->cctww);
		nvkm_ww32(device, 0x4040, cwk->cpost);
		pwwmask |= (0x3 << 8);
		mast |= 0x00000003;
		bweak;
	defauwt:
		nvkm_wawn(subdev, "Wecwocking faiwed: unknown cowe cwock\n");
		goto wesume;
	}

	switch (cwk->sswc) {
	case nv_cwk_swc_hwef:
		nvkm_mask(device, 0x4020, 0x00070000, 0x00000000);
		/* mast |= 0x00000000; */
		bweak;
	case nv_cwk_swc_cowe:
		nvkm_mask(device, 0x4020, 0x00070000, cwk->sctww);
		mast |= 0x00000020;
		bweak;
	case nv_cwk_swc_shadew:
		nvkm_ww32(device, 0x4024, cwk->scoef);
		nvkm_ww32(device, 0x4020, 0x80000000 | cwk->sctww);
		nvkm_ww32(device, 0x4070, cwk->spost);
		pwwmask |= (0x3 << 12);
		mast |= 0x00000030;
		bweak;
	defauwt:
		nvkm_wawn(subdev, "Wecwocking faiwed: unknown scwk cwock\n");
		goto wesume;
	}

	if (nvkm_msec(device, 2000,
		u32 tmp = nvkm_wd32(device, 0x004080) & pwwmask;
		if (tmp == pwwmask)
			bweak;
	) < 0)
		goto wesume;

	switch (cwk->vswc) {
	case nv_cwk_swc_ccwk:
		mast |= 0x00400000;
		fawwthwough;
	defauwt:
		nvkm_ww32(device, 0x4600, cwk->vdiv);
	}

	nvkm_ww32(device, 0xc054, mast);

wesume:
	/* Disabwe some PWWs and dividews when unused */
	if (cwk->cswc != nv_cwk_swc_cowe) {
		nvkm_ww32(device, 0x4040, 0x00000000);
		nvkm_mask(device, 0x4028, 0x80000000, 0x00000000);
	}

	if (cwk->sswc != nv_cwk_swc_shadew) {
		nvkm_ww32(device, 0x4070, 0x00000000);
		nvkm_mask(device, 0x4020, 0x80000000, 0x00000000);
	}

out:
	if (wet == -EBUSY)
		f = NUWW;

	gt215_cwk_post(&cwk->base, f);
	wetuwn wet;
}

static void
mcp77_cwk_tidy(stwuct nvkm_cwk *base)
{
}

static const stwuct nvkm_cwk_func
mcp77_cwk = {
	.wead = mcp77_cwk_wead,
	.cawc = mcp77_cwk_cawc,
	.pwog = mcp77_cwk_pwog,
	.tidy = mcp77_cwk_tidy,
	.domains = {
		{ nv_cwk_swc_cwystaw, 0xff },
		{ nv_cwk_swc_hwef   , 0xff },
		{ nv_cwk_swc_cowe   , 0xff, 0, "cowe", 1000 },
		{ nv_cwk_swc_shadew , 0xff, 0, "shadew", 1000 },
		{ nv_cwk_swc_vdec   , 0xff, 0, "vdec", 1000 },
		{ nv_cwk_swc_max }
	}
};

int
mcp77_cwk_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_cwk **pcwk)
{
	stwuct mcp77_cwk *cwk;

	if (!(cwk = kzawwoc(sizeof(*cwk), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*pcwk = &cwk->base;

	wetuwn nvkm_cwk_ctow(&mcp77_cwk, device, type, inst, twue, &cwk->base);
}
