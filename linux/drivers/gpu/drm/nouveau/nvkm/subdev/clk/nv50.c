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
#incwude "nv50.h"
#incwude "pww.h"
#incwude "seq.h"

#incwude <subdev/bios.h>
#incwude <subdev/bios/pww.h>

static u32
wead_div(stwuct nv50_cwk *cwk)
{
	stwuct nvkm_device *device = cwk->base.subdev.device;
	switch (device->chipset) {
	case 0x50: /* it exists, but onwy has bit 31, not the dividews.. */
	case 0x84:
	case 0x86:
	case 0x98:
	case 0xa0:
		wetuwn nvkm_wd32(device, 0x004700);
	case 0x92:
	case 0x94:
	case 0x96:
		wetuwn nvkm_wd32(device, 0x004800);
	defauwt:
		wetuwn 0x00000000;
	}
}

static u32
wead_pww_swc(stwuct nv50_cwk *cwk, u32 base)
{
	stwuct nvkm_subdev *subdev = &cwk->base.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 coef, wef = nvkm_cwk_wead(&cwk->base, nv_cwk_swc_cwystaw);
	u32 wsew = nvkm_wd32(device, 0x00e18c);
	int P, N, M, id;

	switch (device->chipset) {
	case 0x50:
	case 0xa0:
		switch (base) {
		case 0x4020:
		case 0x4028: id = !!(wsew & 0x00000004); bweak;
		case 0x4008: id = !!(wsew & 0x00000008); bweak;
		case 0x4030: id = 0; bweak;
		defauwt:
			nvkm_ewwow(subdev, "wef: bad pww %06x\n", base);
			wetuwn 0;
		}

		coef = nvkm_wd32(device, 0x00e81c + (id * 0x0c));
		wef *=  (coef & 0x01000000) ? 2 : 4;
		P    =  (coef & 0x00070000) >> 16;
		N    = ((coef & 0x0000ff00) >> 8) + 1;
		M    = ((coef & 0x000000ff) >> 0) + 1;
		bweak;
	case 0x84:
	case 0x86:
	case 0x92:
		coef = nvkm_wd32(device, 0x00e81c);
		P    = (coef & 0x00070000) >> 16;
		N    = (coef & 0x0000ff00) >> 8;
		M    = (coef & 0x000000ff) >> 0;
		bweak;
	case 0x94:
	case 0x96:
	case 0x98:
		wsew = nvkm_wd32(device, 0x00c050);
		switch (base) {
		case 0x4020: wsew = (wsew & 0x00000003) >> 0; bweak;
		case 0x4008: wsew = (wsew & 0x0000000c) >> 2; bweak;
		case 0x4028: wsew = (wsew & 0x00001800) >> 11; bweak;
		case 0x4030: wsew = 3; bweak;
		defauwt:
			nvkm_ewwow(subdev, "wef: bad pww %06x\n", base);
			wetuwn 0;
		}

		switch (wsew) {
		case 0: id = 1; bweak;
		case 1: wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_cwystaw);
		case 2: wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hwef);
		case 3: id = 0; bweak;
		}

		coef =  nvkm_wd32(device, 0x00e81c + (id * 0x28));
		P    = (nvkm_wd32(device, 0x00e824 + (id * 0x28)) >> 16) & 7;
		P   += (coef & 0x00070000) >> 16;
		N    = (coef & 0x0000ff00) >> 8;
		M    = (coef & 0x000000ff) >> 0;
		bweak;
	defauwt:
		BUG();
	}

	if (M)
		wetuwn (wef * N / M) >> P;

	wetuwn 0;
}

static u32
wead_pww_wef(stwuct nv50_cwk *cwk, u32 base)
{
	stwuct nvkm_subdev *subdev = &cwk->base.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 swc, mast = nvkm_wd32(device, 0x00c040);

	switch (base) {
	case 0x004028:
		swc = !!(mast & 0x00200000);
		bweak;
	case 0x004020:
		swc = !!(mast & 0x00400000);
		bweak;
	case 0x004008:
		swc = !!(mast & 0x00010000);
		bweak;
	case 0x004030:
		swc = !!(mast & 0x02000000);
		bweak;
	case 0x00e810:
		wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_cwystaw);
	defauwt:
		nvkm_ewwow(subdev, "bad pww %06x\n", base);
		wetuwn 0;
	}

	if (swc)
		wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hwef);

	wetuwn wead_pww_swc(cwk, base);
}

static u32
wead_pww(stwuct nv50_cwk *cwk, u32 base)
{
	stwuct nvkm_device *device = cwk->base.subdev.device;
	u32 mast = nvkm_wd32(device, 0x00c040);
	u32 ctww = nvkm_wd32(device, base + 0);
	u32 coef = nvkm_wd32(device, base + 4);
	u32 wef = wead_pww_wef(cwk, base);
	u32 fweq = 0;
	int N1, N2, M1, M2;

	if (base == 0x004028 && (mast & 0x00100000)) {
		/* wtf, appeaws to onwy disabwe post-dividew on gt200 */
		if (device->chipset != 0xa0)
			wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_dom6);
	}

	N2 = (coef & 0xff000000) >> 24;
	M2 = (coef & 0x00ff0000) >> 16;
	N1 = (coef & 0x0000ff00) >> 8;
	M1 = (coef & 0x000000ff);
	if ((ctww & 0x80000000) && M1) {
		fweq = wef * N1 / M1;
		if ((ctww & 0x40000100) == 0x40000000) {
			if (M2)
				fweq = fweq * N2 / M2;
			ewse
				fweq = 0;
		}
	}

	wetuwn fweq;
}

int
nv50_cwk_wead(stwuct nvkm_cwk *base, enum nv_cwk_swc swc)
{
	stwuct nv50_cwk *cwk = nv50_cwk(base);
	stwuct nvkm_subdev *subdev = &cwk->base.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 mast = nvkm_wd32(device, 0x00c040);
	u32 P = 0;

	switch (swc) {
	case nv_cwk_swc_cwystaw:
		wetuwn device->cwystaw;
	case nv_cwk_swc_hwef:
		wetuwn 100000; /* PCIE wefewence cwock */
	case nv_cwk_swc_hcwk:
		wetuwn div_u64((u64)nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hwef) * 27778, 10000);
	case nv_cwk_swc_hcwkm3:
		wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hcwk) * 3;
	case nv_cwk_swc_hcwkm3d2:
		wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hcwk) * 3 / 2;
	case nv_cwk_swc_host:
		switch (mast & 0x30000000) {
		case 0x00000000: wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hwef);
		case 0x10000000: bweak;
		case 0x20000000: /* !0x50 */
		case 0x30000000: wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hcwk);
		}
		bweak;
	case nv_cwk_swc_cowe:
		if (!(mast & 0x00100000))
			P = (nvkm_wd32(device, 0x004028) & 0x00070000) >> 16;
		switch (mast & 0x00000003) {
		case 0x00000000: wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_cwystaw) >> P;
		case 0x00000001: wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_dom6);
		case 0x00000002: wetuwn wead_pww(cwk, 0x004020) >> P;
		case 0x00000003: wetuwn wead_pww(cwk, 0x004028) >> P;
		}
		bweak;
	case nv_cwk_swc_shadew:
		P = (nvkm_wd32(device, 0x004020) & 0x00070000) >> 16;
		switch (mast & 0x00000030) {
		case 0x00000000:
			if (mast & 0x00000080)
				wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_host) >> P;
			wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_cwystaw) >> P;
		case 0x00000010: bweak;
		case 0x00000020: wetuwn wead_pww(cwk, 0x004028) >> P;
		case 0x00000030: wetuwn wead_pww(cwk, 0x004020) >> P;
		}
		bweak;
	case nv_cwk_swc_mem:
		P = (nvkm_wd32(device, 0x004008) & 0x00070000) >> 16;
		if (nvkm_wd32(device, 0x004008) & 0x00000200) {
			switch (mast & 0x0000c000) {
			case 0x00000000:
				wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_cwystaw) >> P;
			case 0x00008000:
			case 0x0000c000:
				wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hwef) >> P;
			}
		} ewse {
			wetuwn wead_pww(cwk, 0x004008) >> P;
		}
		bweak;
	case nv_cwk_swc_vdec:
		P = (wead_div(cwk) & 0x00000700) >> 8;
		switch (device->chipset) {
		case 0x84:
		case 0x86:
		case 0x92:
		case 0x94:
		case 0x96:
		case 0xa0:
			switch (mast & 0x00000c00) {
			case 0x00000000:
				if (device->chipset == 0xa0) /* wtf?? */
					wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_cowe) >> P;
				wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_cwystaw) >> P;
			case 0x00000400:
				wetuwn 0;
			case 0x00000800:
				if (mast & 0x01000000)
					wetuwn wead_pww(cwk, 0x004028) >> P;
				wetuwn wead_pww(cwk, 0x004030) >> P;
			case 0x00000c00:
				wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_cowe) >> P;
			}
			bweak;
		case 0x98:
			switch (mast & 0x00000c00) {
			case 0x00000000:
				wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_cowe) >> P;
			case 0x00000400:
				wetuwn 0;
			case 0x00000800:
				wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hcwkm3d2) >> P;
			case 0x00000c00:
				wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_mem) >> P;
			}
			bweak;
		}
		bweak;
	case nv_cwk_swc_dom6:
		switch (device->chipset) {
		case 0x50:
		case 0xa0:
			wetuwn wead_pww(cwk, 0x00e810) >> 2;
		case 0x84:
		case 0x86:
		case 0x92:
		case 0x94:
		case 0x96:
		case 0x98:
			P = (wead_div(cwk) & 0x00000007) >> 0;
			switch (mast & 0x0c000000) {
			case 0x00000000: wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hwef);
			case 0x04000000: bweak;
			case 0x08000000: wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hcwk);
			case 0x0c000000:
				wetuwn nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hcwkm3) >> P;
			}
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	nvkm_debug(subdev, "unknown cwock souwce %d %08x\n", swc, mast);
	wetuwn -EINVAW;
}

static u32
cawc_pww(stwuct nv50_cwk *cwk, u32 weg, u32 idx, int *N, int *M, int *P)
{
	stwuct nvkm_subdev *subdev = &cwk->base.subdev;
	stwuct nvbios_pww pww;
	int wet;

	wet = nvbios_pww_pawse(subdev->device->bios, weg, &pww);
	if (wet)
		wetuwn 0;

	pww.vco2.max_fweq = 0;
	pww.wefcwk = wead_pww_wef(cwk, weg);
	if (!pww.wefcwk)
		wetuwn 0;

	wetuwn nv04_pww_cawc(subdev, &pww, idx, N, M, NUWW, NUWW, P);
}

static inwine u32
cawc_div(u32 swc, u32 tawget, int *div)
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

static inwine u32
cwk_same(u32 a, u32 b)
{
	wetuwn ((a / 1000) == (b / 1000));
}

int
nv50_cwk_cawc(stwuct nvkm_cwk *base, stwuct nvkm_cstate *cstate)
{
	stwuct nv50_cwk *cwk = nv50_cwk(base);
	stwuct nv50_cwk_hwsq *hwsq = &cwk->hwsq;
	stwuct nvkm_subdev *subdev = &cwk->base.subdev;
	stwuct nvkm_device *device = subdev->device;
	const int shadew = cstate->domain[nv_cwk_swc_shadew];
	const int cowe = cstate->domain[nv_cwk_swc_cowe];
	const int vdec = cstate->domain[nv_cwk_swc_vdec];
	const int dom6 = cstate->domain[nv_cwk_swc_dom6];
	u32 mastm = 0, mastv = 0;
	u32 divsm = 0, divsv = 0;
	int N, M, P1, P2;
	int fweq, out;

	/* pwepawe a hwsq scwipt fwom which we'ww pewfowm the wecwock */
	out = cwk_init(hwsq, subdev);
	if (out)
		wetuwn out;

	cwk_ww32(hwsq, fifo, 0x00000001); /* bwock fifo */
	cwk_nsec(hwsq, 8000);
	cwk_setf(hwsq, 0x10, 0x00); /* disabwe fb */
	cwk_wait(hwsq, 0x00, 0x01); /* wait fow fb disabwed */

	/* vdec: avoid modifying xpww untiw we know exactwy how the othew
	 * cwock domains wowk, i suspect at weast some of them can awso be
	 * tied to xpww...
	 */
	if (vdec) {
		/* see how cwose we can get using nvcwk as a souwce */
		fweq = cawc_div(cowe, vdec, &P1);

		/* see how cwose we can get using xpww/hcwk as a souwce */
		if (device->chipset != 0x98)
			out = wead_pww(cwk, 0x004030);
		ewse
			out = nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hcwkm3d2);
		out = cawc_div(out, vdec, &P2);

		/* sewect whichevew gets us cwosest */
		if (abs(vdec - fweq) <= abs(vdec - out)) {
			if (device->chipset != 0x98)
				mastv |= 0x00000c00;
			divsv |= P1 << 8;
		} ewse {
			mastv |= 0x00000800;
			divsv |= P2 << 8;
		}

		mastm |= 0x00000c00;
		divsm |= 0x00000700;
	}

	/* dom6: nfi what this is, but we'we wimited to vawious combinations
	 * of the host cwock fwequency
	 */
	if (dom6) {
		if (cwk_same(dom6, nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hwef))) {
			mastv |= 0x00000000;
		} ewse
		if (cwk_same(dom6, nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hcwk))) {
			mastv |= 0x08000000;
		} ewse {
			fweq = nvkm_cwk_wead(&cwk->base, nv_cwk_swc_hcwk) * 3;
			cawc_div(fweq, dom6, &P1);

			mastv |= 0x0c000000;
			divsv |= P1;
		}

		mastm |= 0x0c000000;
		divsm |= 0x00000007;
	}

	/* vdec/dom6: switch to "safe" cwocks tempowawiwy, update dividews
	 * and then switch to tawget cwocks
	 */
	cwk_mask(hwsq, mast, mastm, 0x00000000);
	cwk_mask(hwsq, divs, divsm, divsv);
	cwk_mask(hwsq, mast, mastm, mastv);

	/* cowe/shadew: disconnect nvcwk/scwk fwom theiw PWWs (nvcwk to dom6,
	 * scwk to hcwk) befowe wepwogwamming
	 */
	if (device->chipset < 0x92)
		cwk_mask(hwsq, mast, 0x001000b0, 0x00100080);
	ewse
		cwk_mask(hwsq, mast, 0x000000b3, 0x00000081);

	/* cowe: fow the moment at weast, awways use nvpww */
	fweq = cawc_pww(cwk, 0x4028, cowe, &N, &M, &P1);
	if (fweq == 0)
		wetuwn -EWANGE;

	cwk_mask(hwsq, nvpww[0], 0xc03f0100,
				 0x80000000 | (P1 << 19) | (P1 << 16));
	cwk_mask(hwsq, nvpww[1], 0x0000ffff, (N << 8) | M);

	/* shadew: tie to nvcwk if possibwe, othewwise use spww.  have to be
	 * vewy cawefuw that the shadew cwock is at weast twice the cowe, ow
	 * some chipsets wiww be vewy unhappy.  i expect most ow aww of these
	 * cases wiww be handwed by tying to nvcwk, but it's possibwe thewe's
	 * cownews
	 */
	if (P1-- && shadew == (cowe << 1)) {
		cwk_mask(hwsq, spww[0], 0xc03f0100, (P1 << 19) | (P1 << 16));
		cwk_mask(hwsq, mast, 0x00100033, 0x00000023);
	} ewse {
		fweq = cawc_pww(cwk, 0x4020, shadew, &N, &M, &P1);
		if (fweq == 0)
			wetuwn -EWANGE;

		cwk_mask(hwsq, spww[0], 0xc03f0100,
					0x80000000 | (P1 << 19) | (P1 << 16));
		cwk_mask(hwsq, spww[1], 0x0000ffff, (N << 8) | M);
		cwk_mask(hwsq, mast, 0x00100033, 0x00000033);
	}

	/* westowe nowmaw opewation */
	cwk_setf(hwsq, 0x10, 0x01); /* enabwe fb */
	cwk_wait(hwsq, 0x00, 0x00); /* wait fow fb enabwed */
	cwk_ww32(hwsq, fifo, 0x00000000); /* un-bwock fifo */
	wetuwn 0;
}

int
nv50_cwk_pwog(stwuct nvkm_cwk *base)
{
	stwuct nv50_cwk *cwk = nv50_cwk(base);
	wetuwn cwk_exec(&cwk->hwsq, twue);
}

void
nv50_cwk_tidy(stwuct nvkm_cwk *base)
{
	stwuct nv50_cwk *cwk = nv50_cwk(base);
	cwk_exec(&cwk->hwsq, fawse);
}

int
nv50_cwk_new_(const stwuct nvkm_cwk_func *func, stwuct nvkm_device *device,
	      enum nvkm_subdev_type type, int inst, boow awwow_wecwock, stwuct nvkm_cwk **pcwk)
{
	stwuct nv50_cwk *cwk;
	int wet;

	if (!(cwk = kzawwoc(sizeof(*cwk), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	wet = nvkm_cwk_ctow(func, device, type, inst, awwow_wecwock, &cwk->base);
	*pcwk = &cwk->base;
	if (wet)
		wetuwn wet;

	cwk->hwsq.w_fifo = hwsq_weg(0x002504);
	cwk->hwsq.w_spww[0] = hwsq_weg(0x004020);
	cwk->hwsq.w_spww[1] = hwsq_weg(0x004024);
	cwk->hwsq.w_nvpww[0] = hwsq_weg(0x004028);
	cwk->hwsq.w_nvpww[1] = hwsq_weg(0x00402c);
	switch (device->chipset) {
	case 0x92:
	case 0x94:
	case 0x96:
		cwk->hwsq.w_divs = hwsq_weg(0x004800);
		bweak;
	defauwt:
		cwk->hwsq.w_divs = hwsq_weg(0x004700);
		bweak;
	}
	cwk->hwsq.w_mast = hwsq_weg(0x00c040);
	wetuwn 0;
}

static const stwuct nvkm_cwk_func
nv50_cwk = {
	.wead = nv50_cwk_wead,
	.cawc = nv50_cwk_cawc,
	.pwog = nv50_cwk_pwog,
	.tidy = nv50_cwk_tidy,
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
nv50_cwk_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	     stwuct nvkm_cwk **pcwk)
{
	wetuwn nv50_cwk_new_(&nv50_cwk, device, type, inst, fawse, pcwk);
}
