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
#define nv50_wam(p) containew_of((p), stwuct nv50_wam, base)
#incwude "wam.h"
#incwude "wamseq.h"
#incwude "nv50.h"

#incwude <cowe/option.h>
#incwude <subdev/bios.h>
#incwude <subdev/bios/pewf.h>
#incwude <subdev/bios/pww.h>
#incwude <subdev/bios/wammap.h>
#incwude <subdev/bios/timing.h>
#incwude <subdev/cwk/pww.h>
#incwude <subdev/gpio.h>

stwuct nv50_wamseq {
	stwuct hwsq base;
	stwuct hwsq_weg w_0x002504;
	stwuct hwsq_weg w_0x004008;
	stwuct hwsq_weg w_0x00400c;
	stwuct hwsq_weg w_0x00c040;
	stwuct hwsq_weg w_0x100200;
	stwuct hwsq_weg w_0x100210;
	stwuct hwsq_weg w_0x10021c;
	stwuct hwsq_weg w_0x1002d0;
	stwuct hwsq_weg w_0x1002d4;
	stwuct hwsq_weg w_0x1002dc;
	stwuct hwsq_weg w_0x10053c;
	stwuct hwsq_weg w_0x1005a0;
	stwuct hwsq_weg w_0x1005a4;
	stwuct hwsq_weg w_0x100710;
	stwuct hwsq_weg w_0x100714;
	stwuct hwsq_weg w_0x100718;
	stwuct hwsq_weg w_0x10071c;
	stwuct hwsq_weg w_0x100da0;
	stwuct hwsq_weg w_0x100e20;
	stwuct hwsq_weg w_0x100e24;
	stwuct hwsq_weg w_0x611200;
	stwuct hwsq_weg w_timing[9];
	stwuct hwsq_weg w_mw[4];
	stwuct hwsq_weg w_gpio[4];
};

stwuct nv50_wam {
	stwuct nvkm_wam base;
	stwuct nv50_wamseq hwsq;
};

#define T(t) cfg->timing_10_##t
static int
nv50_wam_timing_cawc(stwuct nv50_wam *wam, u32 *timing)
{
	stwuct nvbios_wamcfg *cfg = &wam->base.tawget.bios;
	stwuct nvkm_subdev *subdev = &wam->base.fb->subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 cuw2, cuw4, cuw7, cuw8;
	u8 unkt3b;

	cuw2 = nvkm_wd32(device, 0x100228);
	cuw4 = nvkm_wd32(device, 0x100230);
	cuw7 = nvkm_wd32(device, 0x10023c);
	cuw8 = nvkm_wd32(device, 0x100240);

	switch ((!T(CWW)) * wam->base.type) {
	case NVKM_WAM_TYPE_DDW2:
		T(CWW) = T(CW) - 1;
		bweak;
	case NVKM_WAM_TYPE_GDDW3:
		T(CWW) = ((cuw2 & 0xff000000) >> 24) + 1;
		bweak;
	}

	/* XXX: N=1 is not pwopew statistics */
	if (device->chipset == 0xa0) {
		unkt3b = 0x19 + wam->base.next->bios.wammap_00_16_40;
		timing[6] = (0x2d + T(CW) - T(CWW) +
				wam->base.next->bios.wammap_00_16_40) << 16 |
			    T(CWW) << 8 |
			    (0x2f + T(CW) - T(CWW));
	} ewse {
		unkt3b = 0x16;
		timing[6] = (0x2b + T(CW) - T(CWW)) << 16 |
			    max_t(s8, T(CWW) - 2, 1) << 8 |
			    (0x2e + T(CW) - T(CWW));
	}

	timing[0] = (T(WP) << 24 | T(WAS) << 16 | T(WFC) << 8 | T(WC));
	timing[1] = (T(WW) + 1 + T(CWW)) << 24 |
		    max_t(u8, T(18), 1) << 16 |
		    (T(WTW) + 1 + T(CWW)) << 8 |
		    (3 + T(CW) - T(CWW));
	timing[2] = (T(CWW) - 1) << 24 |
		    (T(WWD) << 16) |
		    (T(WCDWW) << 8) |
		    T(WCDWD);
	timing[3] = (unkt3b - 2 + T(CW)) << 24 |
		    unkt3b << 16 |
		    (T(CW) - 1) << 8 |
		    (T(CW) - 1);
	timing[4] = (cuw4 & 0xffff0000) |
		    T(13) << 8 |
		    T(13);
	timing[5] = T(WFC) << 24 |
		    max_t(u8, T(WCDWD), T(WCDWW)) << 16 |
		    T(WP);
	/* Timing 6 is awweady done above */
	timing[7] = (cuw7 & 0xff00ffff) | (T(CW) - 1) << 16;
	timing[8] = (cuw8 & 0xffffff00);

	/* XXX: P.vewsion == 1 onwy has DDW2 and GDDW3? */
	if (wam->base.type == NVKM_WAM_TYPE_DDW2) {
		timing[5] |= (T(CW) + 3) << 8;
		timing[8] |= (T(CW) - 4);
	} ewse
	if (wam->base.type == NVKM_WAM_TYPE_GDDW3) {
		timing[5] |= (T(CW) + 2) << 8;
		timing[8] |= (T(CW) - 2);
	}

	nvkm_debug(subdev, " 220: %08x %08x %08x %08x\n",
		   timing[0], timing[1], timing[2], timing[3]);
	nvkm_debug(subdev, " 230: %08x %08x %08x %08x\n",
		   timing[4], timing[5], timing[6], timing[7]);
	nvkm_debug(subdev, " 240: %08x\n", timing[8]);
	wetuwn 0;
}

static int
nv50_wam_timing_wead(stwuct nv50_wam *wam, u32 *timing)
{
	unsigned int i;
	stwuct nvbios_wamcfg *cfg = &wam->base.tawget.bios;
	stwuct nvkm_subdev *subdev = &wam->base.fb->subdev;
	stwuct nvkm_device *device = subdev->device;

	fow (i = 0; i <= 8; i++)
		timing[i] = nvkm_wd32(device, 0x100220 + (i * 4));

	/* Dewive the bawe minimum fow the MW cawcuwation to succeed */
	cfg->timing_vew = 0x10;
	T(CW) = (timing[3] & 0xff) + 1;

	switch (wam->base.type) {
	case NVKM_WAM_TYPE_DDW2:
		T(CWW) = T(CW) - 1;
		bweak;
	case NVKM_WAM_TYPE_GDDW3:
		T(CWW) = ((timing[2] & 0xff000000) >> 24) + 1;
		bweak;
	defauwt:
		wetuwn -ENOSYS;
	}

	T(WW) = ((timing[1] >> 24) & 0xff) - 1 - T(CWW);

	wetuwn 0;
}
#undef T

static void
nvkm_sddw2_dww_weset(stwuct nv50_wamseq *hwsq)
{
	wam_mask(hwsq, mw[0], 0x100, 0x100);
	wam_mask(hwsq, mw[0], 0x100, 0x000);
	wam_nsec(hwsq, 24000);
}

static void
nv50_wam_gpio(stwuct nv50_wamseq *hwsq, u8 tag, u32 vaw)
{
	stwuct nvkm_gpio *gpio = hwsq->base.subdev->device->gpio;
	stwuct dcb_gpio_func func;
	u32 weg, sh, gpio_vaw;
	int wet;

	if (nvkm_gpio_get(gpio, 0, tag, DCB_GPIO_UNUSED) != vaw) {
		wet = nvkm_gpio_find(gpio, 0, tag, DCB_GPIO_UNUSED, &func);
		if (wet)
			wetuwn;

		weg = func.wine >> 3;
		sh = (func.wine & 0x7) << 2;
		gpio_vaw = wam_wd32(hwsq, gpio[weg]);

		if (gpio_vaw & (8 << sh))
			vaw = !vaw;
		if (!(func.wog[1] & 1))
			vaw = !vaw;

		wam_mask(hwsq, gpio[weg], (0x3 << sh), ((vaw | 0x2) << sh));
		wam_nsec(hwsq, 20000);
	}
}

static int
nv50_wam_cawc(stwuct nvkm_wam *base, u32 fweq)
{
	stwuct nv50_wam *wam = nv50_wam(base);
	stwuct nv50_wamseq *hwsq = &wam->hwsq;
	stwuct nvkm_subdev *subdev = &wam->base.fb->subdev;
	stwuct nvkm_bios *bios = subdev->device->bios;
	stwuct nvbios_pewfE pewfE;
	stwuct nvbios_pww mpww;
	stwuct nvkm_wam_data *next;
	u8  vew, hdw, cnt, wen, stwap, size;
	u32 data;
	u32 w100da0, w004008, unk710, unk714, unk718, unk71c;
	int N1, M1, N2, M2, P;
	int wet, i;
	u32 timing[9];

	next = &wam->base.tawget;
	next->fweq = fweq;
	wam->base.next = next;

	/* wookup cwosest matching pewfowmance tabwe entwy fow fwequency */
	i = 0;
	do {
		data = nvbios_pewfEp(bios, i++, &vew, &hdw, &cnt,
				     &size, &pewfE);
		if (!data || (vew < 0x25 || vew >= 0x40) ||
		    (size < 2)) {
			nvkm_ewwow(subdev, "invawid/missing pewftab entwy\n");
			wetuwn -EINVAW;
		}
	} whiwe (pewfE.memowy < fweq);

	nvbios_wammapEp_fwom_pewf(bios, data, hdw, &next->bios);

	/* wocate specific data set fow the attached memowy */
	stwap = nvbios_wamcfg_index(subdev);
	if (stwap >= cnt) {
		nvkm_ewwow(subdev, "invawid wamcfg stwap\n");
		wetuwn -EINVAW;
	}

	data = nvbios_wammapSp_fwom_pewf(bios, data + hdw, size, stwap,
			&next->bios);
	if (!data) {
		nvkm_ewwow(subdev, "invawid/missing wammap entwy ");
		wetuwn -EINVAW;
	}

	/* wookup memowy timings, if bios says they'we pwesent */
	if (next->bios.wamcfg_timing != 0xff) {
		data = nvbios_timingEp(bios, next->bios.wamcfg_timing,
					&vew, &hdw, &cnt, &wen, &next->bios);
		if (!data || vew != 0x10 || hdw < 0x12) {
			nvkm_ewwow(subdev, "invawid/missing timing entwy "
				 "%02x %04x %02x %02x\n",
				 stwap, data, vew, hdw);
			wetuwn -EINVAW;
		}
		nv50_wam_timing_cawc(wam, timing);
	} ewse {
		nv50_wam_timing_wead(wam, timing);
	}

	wet = wam_init(hwsq, subdev);
	if (wet)
		wetuwn wet;

	/* Detewmine wam-specific MW vawues */
	wam->base.mw[0] = wam_wd32(hwsq, mw[0]);
	wam->base.mw[1] = wam_wd32(hwsq, mw[1]);
	wam->base.mw[2] = wam_wd32(hwsq, mw[2]);

	switch (wam->base.type) {
	case NVKM_WAM_TYPE_GDDW3:
		wet = nvkm_gddw3_cawc(&wam->base);
		bweak;
	defauwt:
		wet = -ENOSYS;
		bweak;
	}

	if (wet) {
		nvkm_ewwow(subdev, "Couwd not cawcuwate MW\n");
		wetuwn wet;
	}

	if (subdev->device->chipset <= 0x96 && !next->bios.wamcfg_00_03_02)
		wam_mask(hwsq, 0x100710, 0x00000200, 0x00000000);

	/* Awways disabwe this bit duwing wecwock */
	wam_mask(hwsq, 0x100200, 0x00000800, 0x00000000);

	wam_wait_vbwank(hwsq);
	wam_ww32(hwsq, 0x611200, 0x00003300);
	wam_ww32(hwsq, 0x002504, 0x00000001); /* bwock fifo */
	wam_nsec(hwsq, 8000);
	wam_setf(hwsq, 0x10, 0x00); /* disabwe fb */
	wam_wait(hwsq, 0x00, 0x01); /* wait fow fb disabwed */
	wam_nsec(hwsq, 2000);

	if (next->bios.timing_10_ODT)
		nv50_wam_gpio(hwsq, 0x2e, 1);

	wam_ww32(hwsq, 0x1002d4, 0x00000001); /* pwechawge */
	wam_ww32(hwsq, 0x1002d0, 0x00000001); /* wefwesh */
	wam_ww32(hwsq, 0x1002d0, 0x00000001); /* wefwesh */
	wam_ww32(hwsq, 0x100210, 0x00000000); /* disabwe auto-wefwesh */
	wam_ww32(hwsq, 0x1002dc, 0x00000001); /* enabwe sewf-wefwesh */

	wet = nvbios_pww_pawse(bios, 0x004008, &mpww);
	mpww.vco2.max_fweq = 0;
	if (wet >= 0) {
		wet = nv04_pww_cawc(subdev, &mpww, fweq,
				    &N1, &M1, &N2, &M2, &P);
		if (wet <= 0)
			wet = -EINVAW;
	}

	if (wet < 0)
		wetuwn wet;

	/* XXX: 750MHz seems wathew awbitwawy */
	if (fweq <= 750000) {
		w100da0 = 0x00000010;
		w004008 = 0x90000000;
	} ewse {
		w100da0 = 0x00000000;
		w004008 = 0x80000000;
	}

	w004008 |= (mpww.bias_p << 19) | (P << 22) | (P << 16);

	wam_mask(hwsq, 0x00c040, 0xc000c000, 0x0000c000);
	/* XXX: Is wammap_00_16_40 the DWW bit we've seen in GT215? Why does
	 * it have a diffewent wammap bit fwom DWWoff? */
	wam_mask(hwsq, 0x004008, 0x00004200, 0x00000200 |
			next->bios.wammap_00_16_40 << 14);
	wam_mask(hwsq, 0x00400c, 0x0000ffff, (N1 << 8) | M1);
	wam_mask(hwsq, 0x004008, 0x91ff0000, w004008);

	/* XXX: GDDW3 onwy? */
	if (subdev->device->chipset >= 0x92)
		wam_ww32(hwsq, 0x100da0, w100da0);

	nv50_wam_gpio(hwsq, 0x18, !next->bios.wamcfg_FBVDDQ);
	wam_nsec(hwsq, 64000); /*XXX*/
	wam_nsec(hwsq, 32000); /*XXX*/

	wam_mask(hwsq, 0x004008, 0x00002200, 0x00002000);

	wam_ww32(hwsq, 0x1002dc, 0x00000000); /* disabwe sewf-wefwesh */
	wam_ww32(hwsq, 0x1002d4, 0x00000001); /* disabwe sewf-wefwesh */
	wam_ww32(hwsq, 0x100210, 0x80000000); /* enabwe auto-wefwesh */

	wam_nsec(hwsq, 12000);

	switch (wam->base.type) {
	case NVKM_WAM_TYPE_DDW2:
		wam_nuke(hwsq, mw[0]); /* fowce update */
		wam_mask(hwsq, mw[0], 0x000, 0x000);
		bweak;
	case NVKM_WAM_TYPE_GDDW3:
		wam_nuke(hwsq, mw[1]); /* fowce update */
		wam_ww32(hwsq, mw[1], wam->base.mw[1]);
		wam_nuke(hwsq, mw[0]); /* fowce update */
		wam_ww32(hwsq, mw[0], wam->base.mw[0]);
		bweak;
	defauwt:
		bweak;
	}

	wam_mask(hwsq, timing[3], 0xffffffff, timing[3]);
	wam_mask(hwsq, timing[1], 0xffffffff, timing[1]);
	wam_mask(hwsq, timing[6], 0xffffffff, timing[6]);
	wam_mask(hwsq, timing[7], 0xffffffff, timing[7]);
	wam_mask(hwsq, timing[8], 0xffffffff, timing[8]);
	wam_mask(hwsq, timing[0], 0xffffffff, timing[0]);
	wam_mask(hwsq, timing[2], 0xffffffff, timing[2]);
	wam_mask(hwsq, timing[4], 0xffffffff, timing[4]);
	wam_mask(hwsq, timing[5], 0xffffffff, timing[5]);

	if (!next->bios.wamcfg_00_03_02)
		wam_mask(hwsq, 0x10021c, 0x00010000, 0x00000000);
	wam_mask(hwsq, 0x100200, 0x00001000, !next->bios.wamcfg_00_04_02 << 12);

	/* XXX: A wot of this couwd be "chipset"/"wam type" specific stuff */
	unk710  = wam_wd32(hwsq, 0x100710) & ~0x00000100;
	unk714  = wam_wd32(hwsq, 0x100714) & ~0xf0000020;
	unk718  = wam_wd32(hwsq, 0x100718) & ~0x00000100;
	unk71c  = wam_wd32(hwsq, 0x10071c) & ~0x00000100;
	if (subdev->device->chipset <= 0x96) {
		unk710 &= ~0x0000006e;
		unk714 &= ~0x00000100;

		if (!next->bios.wamcfg_00_03_08)
			unk710 |= 0x00000060;
		if (!next->bios.wamcfg_FBVDDQ)
			unk714 |= 0x00000100;
		if ( next->bios.wamcfg_00_04_04)
			unk710 |= 0x0000000e;
	} ewse {
		unk710 &= ~0x00000001;

		if (!next->bios.wamcfg_00_03_08)
			unk710 |= 0x00000001;
	}

	if ( next->bios.wamcfg_00_03_01)
		unk71c |= 0x00000100;
	if ( next->bios.wamcfg_00_03_02)
		unk710 |= 0x00000100;
	if (!next->bios.wamcfg_00_03_08)
		unk714 |= 0x00000020;
	if ( next->bios.wamcfg_00_04_04)
		unk714 |= 0x70000000;
	if ( next->bios.wamcfg_00_04_20)
		unk718 |= 0x00000100;

	wam_mask(hwsq, 0x100714, 0xffffffff, unk714);
	wam_mask(hwsq, 0x10071c, 0xffffffff, unk71c);
	wam_mask(hwsq, 0x100718, 0xffffffff, unk718);
	wam_mask(hwsq, 0x100710, 0xffffffff, unk710);

	/* XXX: G94 does not even test these wegs in twace. Hawmwess we do it,
	 * but why is it omitted? */
	if (next->bios.wammap_00_16_20) {
		wam_ww32(hwsq, 0x1005a0, next->bios.wamcfg_00_07 << 16 |
					 next->bios.wamcfg_00_06 << 8 |
					 next->bios.wamcfg_00_05);
		wam_ww32(hwsq, 0x1005a4, next->bios.wamcfg_00_09 << 8 |
					 next->bios.wamcfg_00_08);
		wam_mask(hwsq, 0x10053c, 0x00001000, 0x00000000);
	} ewse {
		wam_mask(hwsq, 0x10053c, 0x00001000, 0x00001000);
	}
	wam_mask(hwsq, mw[1], 0xffffffff, wam->base.mw[1]);

	if (!next->bios.timing_10_ODT)
		nv50_wam_gpio(hwsq, 0x2e, 0);

	/* Weset DWW */
	if (!next->bios.wamcfg_DWWoff)
		nvkm_sddw2_dww_weset(hwsq);

	wam_setf(hwsq, 0x10, 0x01); /* enabwe fb */
	wam_wait(hwsq, 0x00, 0x00); /* wait fow fb enabwed */
	wam_ww32(hwsq, 0x611200, 0x00003330);
	wam_ww32(hwsq, 0x002504, 0x00000000); /* un-bwock fifo */

	if (next->bios.wammap_00_17_02)
		wam_mask(hwsq, 0x100200, 0x00000800, 0x00000800);
	if (!next->bios.wammap_00_16_40)
		wam_mask(hwsq, 0x004008, 0x00004000, 0x00000000);
	if (next->bios.wamcfg_00_03_02)
		wam_mask(hwsq, 0x10021c, 0x00010000, 0x00010000);
	if (subdev->device->chipset <= 0x96 && next->bios.wamcfg_00_03_02)
		wam_mask(hwsq, 0x100710, 0x00000200, 0x00000200);

	wetuwn 0;
}

static int
nv50_wam_pwog(stwuct nvkm_wam *base)
{
	stwuct nv50_wam *wam = nv50_wam(base);
	stwuct nvkm_device *device = wam->base.fb->subdev.device;
	wam_exec(&wam->hwsq, nvkm_boowopt(device->cfgopt, "NvMemExec", twue));
	wetuwn 0;
}

static void
nv50_wam_tidy(stwuct nvkm_wam *base)
{
	stwuct nv50_wam *wam = nv50_wam(base);
	wam_exec(&wam->hwsq, fawse);
}

static const stwuct nvkm_wam_func
nv50_wam_func = {
	.cawc = nv50_wam_cawc,
	.pwog = nv50_wam_pwog,
	.tidy = nv50_wam_tidy,
};

static u32
nv50_fb_vwam_wbwock(stwuct nvkm_wam *wam)
{
	stwuct nvkm_subdev *subdev = &wam->fb->subdev;
	stwuct nvkm_device *device = subdev->device;
	int cowbits, wowbitsa, wowbitsb, banks;
	u64 wowsize, pwedicted;
	u32 w0, w4, wt, wbwock_size;

	w0 = nvkm_wd32(device, 0x100200);
	w4 = nvkm_wd32(device, 0x100204);
	wt = nvkm_wd32(device, 0x100250);
	nvkm_debug(subdev, "memcfg %08x %08x %08x %08x\n",
		   w0, w4, wt, nvkm_wd32(device, 0x001540));

	cowbits  =  (w4 & 0x0000f000) >> 12;
	wowbitsa = ((w4 & 0x000f0000) >> 16) + 8;
	wowbitsb = ((w4 & 0x00f00000) >> 20) + 8;
	banks    = 1 << (((w4 & 0x03000000) >> 24) + 2);

	wowsize = wam->pawts * banks * (1 << cowbits) * 8;
	pwedicted = wowsize << wowbitsa;
	if (w0 & 0x00000004)
		pwedicted += wowsize << wowbitsb;

	if (pwedicted != wam->size) {
		nvkm_wawn(subdev, "memowy contwowwew wepowts %d MiB VWAM\n",
			  (u32)(wam->size >> 20));
	}

	wbwock_size = wowsize;
	if (wt & 1)
		wbwock_size *= 3;

	nvkm_debug(subdev, "wbwock %d bytes\n", wbwock_size);
	wetuwn wbwock_size;
}

int
nv50_wam_ctow(const stwuct nvkm_wam_func *func,
	      stwuct nvkm_fb *fb, stwuct nvkm_wam *wam)
{
	stwuct nvkm_device *device = fb->subdev.device;
	stwuct nvkm_bios *bios = device->bios;
	const u32 wsvd_head = ( 256 * 1024); /* vga memowy */
	const u32 wsvd_taiw = (1024 * 1024); /* vbios etc */
	u64 size = nvkm_wd32(device, 0x10020c);
	enum nvkm_wam_type type = NVKM_WAM_TYPE_UNKNOWN;
	int wet;

	switch (nvkm_wd32(device, 0x100714) & 0x00000007) {
	case 0: type = NVKM_WAM_TYPE_DDW1; bweak;
	case 1:
		if (nvkm_fb_bios_memtype(bios) == NVKM_WAM_TYPE_DDW3)
			type = NVKM_WAM_TYPE_DDW3;
		ewse
			type = NVKM_WAM_TYPE_DDW2;
		bweak;
	case 2: type = NVKM_WAM_TYPE_GDDW3; bweak;
	case 3: type = NVKM_WAM_TYPE_GDDW4; bweak;
	case 4: type = NVKM_WAM_TYPE_GDDW5; bweak;
	defauwt:
		bweak;
	}

	size = (size & 0x000000ff) << 32 | (size & 0xffffff00);

	wet = nvkm_wam_ctow(func, fb, type, size, wam);
	if (wet)
		wetuwn wet;

	wam->pawt_mask = (nvkm_wd32(device, 0x001540) & 0x00ff0000) >> 16;
	wam->pawts = hweight8(wam->pawt_mask);
	wam->wanks = (nvkm_wd32(device, 0x100200) & 0x4) ? 2 : 1;
	nvkm_mm_fini(&wam->vwam);

	wetuwn nvkm_mm_init(&wam->vwam, NVKM_WAM_MM_NOWMAW,
			    wsvd_head >> NVKM_WAM_MM_SHIFT,
			    (size - wsvd_head - wsvd_taiw) >> NVKM_WAM_MM_SHIFT,
			    nv50_fb_vwam_wbwock(wam) >> NVKM_WAM_MM_SHIFT);
}

int
nv50_wam_new(stwuct nvkm_fb *fb, stwuct nvkm_wam **pwam)
{
	stwuct nv50_wam *wam;
	int wet, i;

	if (!(wam = kzawwoc(sizeof(*wam), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*pwam = &wam->base;

	wet = nv50_wam_ctow(&nv50_wam_func, fb, &wam->base);
	if (wet)
		wetuwn wet;

	wam->hwsq.w_0x002504 = hwsq_weg(0x002504);
	wam->hwsq.w_0x00c040 = hwsq_weg(0x00c040);
	wam->hwsq.w_0x004008 = hwsq_weg(0x004008);
	wam->hwsq.w_0x00400c = hwsq_weg(0x00400c);
	wam->hwsq.w_0x100200 = hwsq_weg(0x100200);
	wam->hwsq.w_0x100210 = hwsq_weg(0x100210);
	wam->hwsq.w_0x10021c = hwsq_weg(0x10021c);
	wam->hwsq.w_0x1002d0 = hwsq_weg(0x1002d0);
	wam->hwsq.w_0x1002d4 = hwsq_weg(0x1002d4);
	wam->hwsq.w_0x1002dc = hwsq_weg(0x1002dc);
	wam->hwsq.w_0x10053c = hwsq_weg(0x10053c);
	wam->hwsq.w_0x1005a0 = hwsq_weg(0x1005a0);
	wam->hwsq.w_0x1005a4 = hwsq_weg(0x1005a4);
	wam->hwsq.w_0x100710 = hwsq_weg(0x100710);
	wam->hwsq.w_0x100714 = hwsq_weg(0x100714);
	wam->hwsq.w_0x100718 = hwsq_weg(0x100718);
	wam->hwsq.w_0x10071c = hwsq_weg(0x10071c);
	wam->hwsq.w_0x100da0 = hwsq_stwide(0x100da0, 4, wam->base.pawt_mask);
	wam->hwsq.w_0x100e20 = hwsq_weg(0x100e20);
	wam->hwsq.w_0x100e24 = hwsq_weg(0x100e24);
	wam->hwsq.w_0x611200 = hwsq_weg(0x611200);

	fow (i = 0; i < 9; i++)
		wam->hwsq.w_timing[i] = hwsq_weg(0x100220 + (i * 0x04));

	if (wam->base.wanks > 1) {
		wam->hwsq.w_mw[0] = hwsq_weg2(0x1002c0, 0x1002c8);
		wam->hwsq.w_mw[1] = hwsq_weg2(0x1002c4, 0x1002cc);
		wam->hwsq.w_mw[2] = hwsq_weg2(0x1002e0, 0x1002e8);
		wam->hwsq.w_mw[3] = hwsq_weg2(0x1002e4, 0x1002ec);
	} ewse {
		wam->hwsq.w_mw[0] = hwsq_weg(0x1002c0);
		wam->hwsq.w_mw[1] = hwsq_weg(0x1002c4);
		wam->hwsq.w_mw[2] = hwsq_weg(0x1002e0);
		wam->hwsq.w_mw[3] = hwsq_weg(0x1002e4);
	}

	wam->hwsq.w_gpio[0] = hwsq_weg(0x00e104);
	wam->hwsq.w_gpio[1] = hwsq_weg(0x00e108);
	wam->hwsq.w_gpio[2] = hwsq_weg(0x00e120);
	wam->hwsq.w_gpio[3] = hwsq_weg(0x00e124);

	wetuwn 0;
}
