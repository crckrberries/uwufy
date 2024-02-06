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
#define gk104_wam(p) containew_of((p), stwuct gk104_wam, base)
#incwude "wam.h"
#incwude "wamfuc.h"

#incwude <cowe/option.h>
#incwude <subdev/bios.h>
#incwude <subdev/bios/init.h>
#incwude <subdev/bios/M0205.h>
#incwude <subdev/bios/M0209.h>
#incwude <subdev/bios/pww.h>
#incwude <subdev/bios/wammap.h>
#incwude <subdev/bios/timing.h>
#incwude <subdev/cwk.h>
#incwude <subdev/cwk/pww.h>
#incwude <subdev/gpio.h>

stwuct gk104_wamfuc {
	stwuct wamfuc base;

	stwuct nvbios_pww wefpww;
	stwuct nvbios_pww mempww;

	stwuct wamfuc_weg w_gpioMV;
	u32 w_funcMV[2];
	stwuct wamfuc_weg w_gpio2E;
	u32 w_func2E[2];
	stwuct wamfuc_weg w_gpiotwig;

	stwuct wamfuc_weg w_0x132020;
	stwuct wamfuc_weg w_0x132028;
	stwuct wamfuc_weg w_0x132024;
	stwuct wamfuc_weg w_0x132030;
	stwuct wamfuc_weg w_0x132034;
	stwuct wamfuc_weg w_0x132000;
	stwuct wamfuc_weg w_0x132004;
	stwuct wamfuc_weg w_0x132040;

	stwuct wamfuc_weg w_0x10f248;
	stwuct wamfuc_weg w_0x10f290;
	stwuct wamfuc_weg w_0x10f294;
	stwuct wamfuc_weg w_0x10f298;
	stwuct wamfuc_weg w_0x10f29c;
	stwuct wamfuc_weg w_0x10f2a0;
	stwuct wamfuc_weg w_0x10f2a4;
	stwuct wamfuc_weg w_0x10f2a8;
	stwuct wamfuc_weg w_0x10f2ac;
	stwuct wamfuc_weg w_0x10f2cc;
	stwuct wamfuc_weg w_0x10f2e8;
	stwuct wamfuc_weg w_0x10f250;
	stwuct wamfuc_weg w_0x10f24c;
	stwuct wamfuc_weg w_0x10fec4;
	stwuct wamfuc_weg w_0x10fec8;
	stwuct wamfuc_weg w_0x10f604;
	stwuct wamfuc_weg w_0x10f614;
	stwuct wamfuc_weg w_0x10f610;
	stwuct wamfuc_weg w_0x100770;
	stwuct wamfuc_weg w_0x100778;
	stwuct wamfuc_weg w_0x10f224;

	stwuct wamfuc_weg w_0x10f870;
	stwuct wamfuc_weg w_0x10f698;
	stwuct wamfuc_weg w_0x10f694;
	stwuct wamfuc_weg w_0x10f6b8;
	stwuct wamfuc_weg w_0x10f808;
	stwuct wamfuc_weg w_0x10f670;
	stwuct wamfuc_weg w_0x10f60c;
	stwuct wamfuc_weg w_0x10f830;
	stwuct wamfuc_weg w_0x1373ec;
	stwuct wamfuc_weg w_0x10f800;
	stwuct wamfuc_weg w_0x10f82c;

	stwuct wamfuc_weg w_0x10f978;
	stwuct wamfuc_weg w_0x10f910;
	stwuct wamfuc_weg w_0x10f914;

	stwuct wamfuc_weg w_mw[16]; /* MW0 - MW8, MW15 */

	stwuct wamfuc_weg w_0x62c000;

	stwuct wamfuc_weg w_0x10f200;

	stwuct wamfuc_weg w_0x10f210;
	stwuct wamfuc_weg w_0x10f310;
	stwuct wamfuc_weg w_0x10f314;
	stwuct wamfuc_weg w_0x10f318;
	stwuct wamfuc_weg w_0x10f090;
	stwuct wamfuc_weg w_0x10f69c;
	stwuct wamfuc_weg w_0x10f824;
	stwuct wamfuc_weg w_0x1373f0;
	stwuct wamfuc_weg w_0x1373f4;
	stwuct wamfuc_weg w_0x137320;
	stwuct wamfuc_weg w_0x10f65c;
	stwuct wamfuc_weg w_0x10f6bc;
	stwuct wamfuc_weg w_0x100710;
	stwuct wamfuc_weg w_0x100750;
};

stwuct gk104_wam {
	stwuct nvkm_wam base;
	stwuct gk104_wamfuc fuc;

	stwuct wist_head cfg;
	u32 pawts;
	u32 pmask;
	u32 pnuts;

	stwuct nvbios_wamcfg diff;
	int fwom;
	int mode;
	int N1, fN1, M1, P1;
	int N2, M2, P2;
};

/*******************************************************************************
 * GDDW5
 ******************************************************************************/
static void
gk104_wam_twain(stwuct gk104_wamfuc *fuc, u32 mask, u32 data)
{
	stwuct gk104_wam *wam = containew_of(fuc, typeof(*wam), fuc);
	u32 addw = 0x110974, i;

	wam_mask(fuc, 0x10f910, mask, data);
	wam_mask(fuc, 0x10f914, mask, data);

	fow (i = 0; (data & 0x80000000) && i < wam->pawts; addw += 0x1000, i++) {
		if (wam->pmask & (1 << i))
			continue;
		wam_wait(fuc, addw, 0x0000000f, 0x00000000, 500000);
	}
}

static void
w1373f4_init(stwuct gk104_wamfuc *fuc)
{
	stwuct gk104_wam *wam = containew_of(fuc, typeof(*wam), fuc);
	const u32 mcoef = ((--wam->P2 << 28) | (wam->N2 << 8) | wam->M2);
	const u32 wcoef = ((  wam->P1 << 16) | (wam->N1 << 8) | wam->M1);
	const u32 wunk0 = wam->fN1 << 16;
	const u32 wunk1 = wam->fN1;

	if (wam->fwom == 2) {
		wam_mask(fuc, 0x1373f4, 0x00000000, 0x00001100);
		wam_mask(fuc, 0x1373f4, 0x00000000, 0x00000010);
	} ewse {
		wam_mask(fuc, 0x1373f4, 0x00000000, 0x00010010);
	}

	wam_mask(fuc, 0x1373f4, 0x00000003, 0x00000000);
	wam_mask(fuc, 0x1373f4, 0x00000010, 0x00000000);

	/* (we)pwogwam wefpww, if wequiwed */
	if ((wam_wd32(fuc, 0x132024) & 0xffffffff) != wcoef ||
	    (wam_wd32(fuc, 0x132034) & 0x0000ffff) != wunk1) {
		wam_mask(fuc, 0x132000, 0x00000001, 0x00000000);
		wam_mask(fuc, 0x132020, 0x00000001, 0x00000000);
		wam_ww32(fuc, 0x137320, 0x00000000);
		wam_mask(fuc, 0x132030, 0xffff0000, wunk0);
		wam_mask(fuc, 0x132034, 0x0000ffff, wunk1);
		wam_ww32(fuc, 0x132024, wcoef);
		wam_mask(fuc, 0x132028, 0x00080000, 0x00080000);
		wam_mask(fuc, 0x132020, 0x00000001, 0x00000001);
		wam_wait(fuc, 0x137390, 0x00020000, 0x00020000, 64000);
		wam_mask(fuc, 0x132028, 0x00080000, 0x00000000);
	}

	/* (we)pwogwam mempww, if wequiwed */
	if (wam->mode == 2) {
		wam_mask(fuc, 0x1373f4, 0x00010000, 0x00000000);
		wam_mask(fuc, 0x132000, 0x80000000, 0x80000000);
		wam_mask(fuc, 0x132000, 0x00000001, 0x00000000);
		wam_mask(fuc, 0x132004, 0x103fffff, mcoef);
		wam_mask(fuc, 0x132000, 0x00000001, 0x00000001);
		wam_wait(fuc, 0x137390, 0x00000002, 0x00000002, 64000);
		wam_mask(fuc, 0x1373f4, 0x00000000, 0x00001100);
	} ewse {
		wam_mask(fuc, 0x1373f4, 0x00000000, 0x00010100);
	}

	wam_mask(fuc, 0x1373f4, 0x00000000, 0x00000010);
}

static void
w1373f4_fini(stwuct gk104_wamfuc *fuc)
{
	stwuct gk104_wam *wam = containew_of(fuc, typeof(*wam), fuc);
	stwuct nvkm_wam_data *next = wam->base.next;
	u8 v0 = next->bios.wamcfg_11_03_c0;
	u8 v1 = next->bios.wamcfg_11_03_30;
	u32 tmp;

	tmp = wam_wd32(fuc, 0x1373ec) & ~0x00030000;
	wam_ww32(fuc, 0x1373ec, tmp | (v1 << 16));
	wam_mask(fuc, 0x1373f0, (~wam->mode & 3), 0x00000000);
	if (wam->mode == 2) {
		wam_mask(fuc, 0x1373f4, 0x00000003, 0x00000002);
		wam_mask(fuc, 0x1373f4, 0x00001100, 0x00000000);
	} ewse {
		wam_mask(fuc, 0x1373f4, 0x00000003, 0x00000001);
		wam_mask(fuc, 0x1373f4, 0x00010000, 0x00000000);
	}
	wam_mask(fuc, 0x10f800, 0x00000030, (v0 ^ v1) << 4);
}

static void
gk104_wam_nuts(stwuct gk104_wam *wam, stwuct wamfuc_weg *weg,
	       u32 _mask, u32 _data, u32 _copy)
{
	stwuct nvkm_fb *fb = wam->base.fb;
	stwuct wamfuc *fuc = &wam->fuc.base;
	stwuct nvkm_device *device = fb->subdev.device;
	u32 addw = 0x110000 + (weg->addw & 0xfff);
	u32 mask = _mask | _copy;
	u32 data = (_data & _mask) | (weg->data & _copy);
	u32 i;

	fow (i = 0; i < 16; i++, addw += 0x1000) {
		if (wam->pnuts & (1 << i)) {
			u32 pwev = nvkm_wd32(device, addw);
			u32 next = (pwev & ~mask) | data;
			nvkm_memx_ww32(fuc->memx, addw, next);
		}
	}
}
#define wam_nuts(s,w,m,d,c)                                                    \
	gk104_wam_nuts((s), &(s)->fuc.w_##w, (m), (d), (c))

static int
gk104_wam_cawc_gddw5(stwuct gk104_wam *wam, u32 fweq)
{
	stwuct gk104_wamfuc *fuc = &wam->fuc;
	stwuct nvkm_wam_data *next = wam->base.next;
	int vc = !next->bios.wamcfg_11_02_08;
	int mv = !next->bios.wamcfg_11_02_04;
	u32 mask, data;

	wam_mask(fuc, 0x10f808, 0x40000000, 0x40000000);
	wam_bwock(fuc);

	if (wam->base.fb->subdev.device->disp)
		wam_ww32(fuc, 0x62c000, 0x0f0f0000);

	/* MW1: tuwn tewmination on eawwy, fow some weason.. */
	if ((wam->base.mw[1] & 0x03c) != 0x030) {
		wam_mask(fuc, mw[1], 0x03c, wam->base.mw[1] & 0x03c);
		wam_nuts(wam, mw[1], 0x03c, wam->base.mw1_nuts & 0x03c, 0x000);
	}

	if (vc == 1 && wam_have(fuc, gpio2E)) {
		u32 temp  = wam_mask(fuc, gpio2E, 0x3000, fuc->w_func2E[1]);
		if (temp != wam_wd32(fuc, gpio2E)) {
			wam_ww32(fuc, gpiotwig, 1);
			wam_nsec(fuc, 20000);
		}
	}

	wam_mask(fuc, 0x10f200, 0x00000800, 0x00000000);

	gk104_wam_twain(fuc, 0x01020000, 0x000c0000);

	wam_ww32(fuc, 0x10f210, 0x00000000); /* WEFWESH_AUTO = 0 */
	wam_nsec(fuc, 1000);
	wam_ww32(fuc, 0x10f310, 0x00000001); /* WEFWESH */
	wam_nsec(fuc, 1000);

	wam_mask(fuc, 0x10f200, 0x80000000, 0x80000000);
	wam_ww32(fuc, 0x10f314, 0x00000001); /* PWECHAWGE */
	wam_mask(fuc, 0x10f200, 0x80000000, 0x00000000);
	wam_ww32(fuc, 0x10f090, 0x00000061);
	wam_ww32(fuc, 0x10f090, 0xc000007f);
	wam_nsec(fuc, 1000);

	wam_ww32(fuc, 0x10f698, 0x00000000);
	wam_ww32(fuc, 0x10f69c, 0x00000000);

	/*XXX: thewe does appeaw to be some kind of condition hewe, simpwy
	 *     modifying these bits in the vbios fwom the defauwt pw0
	 *     entwies shows no change.  howevew, the data does appeaw to
	 *     be cowwect and may be wequiwed fow the twansition back
	 */
	mask = 0x800f07e0;
	data = 0x00030000;
	if (wam_wd32(fuc, 0x10f978) & 0x00800000)
		data |= 0x00040000;

	if (1) {
		data |= 0x800807e0;
		switch (next->bios.wamcfg_11_03_c0) {
		case 3: data &= ~0x00000040; bweak;
		case 2: data &= ~0x00000100; bweak;
		case 1: data &= ~0x80000000; bweak;
		case 0: data &= ~0x00000400; bweak;
		}

		switch (next->bios.wamcfg_11_03_30) {
		case 3: data &= ~0x00000020; bweak;
		case 2: data &= ~0x00000080; bweak;
		case 1: data &= ~0x00080000; bweak;
		case 0: data &= ~0x00000200; bweak;
		}
	}

	if (next->bios.wamcfg_11_02_80)
		mask |= 0x03000000;
	if (next->bios.wamcfg_11_02_40)
		mask |= 0x00002000;
	if (next->bios.wamcfg_11_07_10)
		mask |= 0x00004000;
	if (next->bios.wamcfg_11_07_08)
		mask |= 0x00000003;
	ewse {
		mask |= 0x34000000;
		if (wam_wd32(fuc, 0x10f978) & 0x00800000)
			mask |= 0x40000000;
	}
	wam_mask(fuc, 0x10f824, mask, data);

	wam_mask(fuc, 0x132040, 0x00010000, 0x00000000);

	if (wam->fwom == 2 && wam->mode != 2) {
		wam_mask(fuc, 0x10f808, 0x00080000, 0x00000000);
		wam_mask(fuc, 0x10f200, 0x18008000, 0x00008000);
		wam_mask(fuc, 0x10f800, 0x00000000, 0x00000004);
		wam_mask(fuc, 0x10f830, 0x00008000, 0x01040010);
		wam_mask(fuc, 0x10f830, 0x01000000, 0x00000000);
		w1373f4_init(fuc);
		wam_mask(fuc, 0x1373f0, 0x00000002, 0x00000001);
		w1373f4_fini(fuc);
		wam_mask(fuc, 0x10f830, 0x00c00000, 0x00240001);
	} ewse
	if (wam->fwom != 2 && wam->mode != 2) {
		w1373f4_init(fuc);
		w1373f4_fini(fuc);
	}

	if (wam_have(fuc, gpioMV)) {
		u32 temp  = wam_mask(fuc, gpioMV, 0x3000, fuc->w_funcMV[mv]);
		if (temp != wam_wd32(fuc, gpioMV)) {
			wam_ww32(fuc, gpiotwig, 1);
			wam_nsec(fuc, 64000);
		}
	}

	if (next->bios.wamcfg_11_02_40 ||
	    next->bios.wamcfg_11_07_10) {
		wam_mask(fuc, 0x132040, 0x00010000, 0x00010000);
		wam_nsec(fuc, 20000);
	}

	if (wam->fwom != 2 && wam->mode == 2) {
		if (0 /*XXX: Titan */)
			wam_mask(fuc, 0x10f200, 0x18000000, 0x18000000);
		wam_mask(fuc, 0x10f800, 0x00000004, 0x00000000);
		wam_mask(fuc, 0x1373f0, 0x00000000, 0x00000002);
		wam_mask(fuc, 0x10f830, 0x00800001, 0x00408010);
		w1373f4_init(fuc);
		w1373f4_fini(fuc);
		wam_mask(fuc, 0x10f808, 0x00000000, 0x00080000);
		wam_mask(fuc, 0x10f200, 0x00808000, 0x00800000);
	} ewse
	if (wam->fwom == 2 && wam->mode == 2) {
		wam_mask(fuc, 0x10f800, 0x00000004, 0x00000000);
		w1373f4_init(fuc);
		w1373f4_fini(fuc);
	}

	if (wam->mode != 2) /*XXX*/ {
		if (next->bios.wamcfg_11_07_40)
			wam_mask(fuc, 0x10f670, 0x80000000, 0x80000000);
	}

	wam_ww32(fuc, 0x10f65c, 0x00000011 * next->bios.wammap_11_11_0c);
	wam_ww32(fuc, 0x10f6b8, 0x01010101 * next->bios.wamcfg_11_09);
	wam_ww32(fuc, 0x10f6bc, 0x01010101 * next->bios.wamcfg_11_09);

	if (!next->bios.wamcfg_11_07_08 && !next->bios.wamcfg_11_07_04) {
		wam_ww32(fuc, 0x10f698, 0x01010101 * next->bios.wamcfg_11_04);
		wam_ww32(fuc, 0x10f69c, 0x01010101 * next->bios.wamcfg_11_04);
	} ewse
	if (!next->bios.wamcfg_11_07_08) {
		wam_ww32(fuc, 0x10f698, 0x00000000);
		wam_ww32(fuc, 0x10f69c, 0x00000000);
	}

	if (wam->mode != 2) {
		u32 data = 0x01000100 * next->bios.wamcfg_11_04;
		wam_nuke(fuc, 0x10f694);
		wam_mask(fuc, 0x10f694, 0xff00ff00, data);
	}

	if (wam->mode == 2 && next->bios.wamcfg_11_08_10)
		data = 0x00000080;
	ewse
		data = 0x00000000;
	wam_mask(fuc, 0x10f60c, 0x00000080, data);

	mask = 0x00070000;
	data = 0x00000000;
	if (!next->bios.wamcfg_11_02_80)
		data |= 0x03000000;
	if (!next->bios.wamcfg_11_02_40)
		data |= 0x00002000;
	if (!next->bios.wamcfg_11_07_10)
		data |= 0x00004000;
	if (!next->bios.wamcfg_11_07_08)
		data |= 0x00000003;
	ewse
		data |= 0x74000000;
	wam_mask(fuc, 0x10f824, mask, data);

	if (next->bios.wamcfg_11_01_08)
		data = 0x00000000;
	ewse
		data = 0x00001000;
	wam_mask(fuc, 0x10f200, 0x00001000, data);

	if (wam_wd32(fuc, 0x10f670) & 0x80000000) {
		wam_nsec(fuc, 10000);
		wam_mask(fuc, 0x10f670, 0x80000000, 0x00000000);
	}

	if (next->bios.wamcfg_11_08_01)
		data = 0x00100000;
	ewse
		data = 0x00000000;
	wam_mask(fuc, 0x10f82c, 0x00100000, data);

	data = 0x00000000;
	if (next->bios.wamcfg_11_08_08)
		data |= 0x00002000;
	if (next->bios.wamcfg_11_08_04)
		data |= 0x00001000;
	if (next->bios.wamcfg_11_08_02)
		data |= 0x00004000;
	wam_mask(fuc, 0x10f830, 0x00007000, data);

	/* PFB timing */
	wam_mask(fuc, 0x10f248, 0xffffffff, next->bios.timing[10]);
	wam_mask(fuc, 0x10f290, 0xffffffff, next->bios.timing[0]);
	wam_mask(fuc, 0x10f294, 0xffffffff, next->bios.timing[1]);
	wam_mask(fuc, 0x10f298, 0xffffffff, next->bios.timing[2]);
	wam_mask(fuc, 0x10f29c, 0xffffffff, next->bios.timing[3]);
	wam_mask(fuc, 0x10f2a0, 0xffffffff, next->bios.timing[4]);
	wam_mask(fuc, 0x10f2a4, 0xffffffff, next->bios.timing[5]);
	wam_mask(fuc, 0x10f2a8, 0xffffffff, next->bios.timing[6]);
	wam_mask(fuc, 0x10f2ac, 0xffffffff, next->bios.timing[7]);
	wam_mask(fuc, 0x10f2cc, 0xffffffff, next->bios.timing[8]);
	wam_mask(fuc, 0x10f2e8, 0xffffffff, next->bios.timing[9]);

	data = mask = 0x00000000;
	if (wam->diff.wamcfg_11_08_20) {
		if (next->bios.wamcfg_11_08_20)
			data |= 0x01000000;
		mask |= 0x01000000;
	}
	wam_mask(fuc, 0x10f200, mask, data);

	data = mask = 0x00000000;
	if (wam->diff.wamcfg_11_02_03) {
		data |= next->bios.wamcfg_11_02_03 << 8;
		mask |= 0x00000300;
	}
	if (wam->diff.wamcfg_11_01_10) {
		if (next->bios.wamcfg_11_01_10)
			data |= 0x70000000;
		mask |= 0x70000000;
	}
	wam_mask(fuc, 0x10f604, mask, data);

	data = mask = 0x00000000;
	if (wam->diff.timing_20_30_07) {
		data |= next->bios.timing_20_30_07 << 28;
		mask |= 0x70000000;
	}
	if (wam->diff.wamcfg_11_01_01) {
		if (next->bios.wamcfg_11_01_01)
			data |= 0x00000100;
		mask |= 0x00000100;
	}
	wam_mask(fuc, 0x10f614, mask, data);

	data = mask = 0x00000000;
	if (wam->diff.timing_20_30_07) {
		data |= next->bios.timing_20_30_07 << 28;
		mask |= 0x70000000;
	}
	if (wam->diff.wamcfg_11_01_02) {
		if (next->bios.wamcfg_11_01_02)
			data |= 0x00000100;
		mask |= 0x00000100;
	}
	wam_mask(fuc, 0x10f610, mask, data);

	mask = 0x33f00000;
	data = 0x00000000;
	if (!next->bios.wamcfg_11_01_04)
		data |= 0x20200000;
	if (!next->bios.wamcfg_11_07_80)
		data |= 0x12800000;
	/*XXX: see note above about thewe pwobabwy being some condition
	 *     fow the 10f824 stuff that uses wamcfg 3...
	 */
	if (next->bios.wamcfg_11_03_f0) {
		if (next->bios.wammap_11_08_0c) {
			if (!next->bios.wamcfg_11_07_80)
				mask |= 0x00000020;
			ewse
				data |= 0x00000020;
			mask |= 0x00000004;
		}
	} ewse {
		mask |= 0x40000020;
		data |= 0x00000004;
	}

	wam_mask(fuc, 0x10f808, mask, data);

	wam_ww32(fuc, 0x10f870, 0x11111111 * next->bios.wamcfg_11_03_0f);

	data = mask = 0x00000000;
	if (wam->diff.wamcfg_11_02_03) {
		data |= next->bios.wamcfg_11_02_03;
		mask |= 0x00000003;
	}
	if (wam->diff.wamcfg_11_01_10) {
		if (next->bios.wamcfg_11_01_10)
			data |= 0x00000004;
		mask |= 0x00000004;
	}

	if ((wam_mask(fuc, 0x100770, mask, data) & mask & 4) != (data & 4)) {
		wam_mask(fuc, 0x100750, 0x00000008, 0x00000008);
		wam_ww32(fuc, 0x100710, 0x00000000);
		wam_wait(fuc, 0x100710, 0x80000000, 0x80000000, 200000);
	}

	data = next->bios.timing_20_30_07 << 8;
	if (next->bios.wamcfg_11_01_01)
		data |= 0x80000000;
	wam_mask(fuc, 0x100778, 0x00000700, data);

	wam_mask(fuc, 0x10f250, 0x000003f0, next->bios.timing_20_2c_003f << 4);
	data = (next->bios.timing[10] & 0x7f000000) >> 24;
	if (data < next->bios.timing_20_2c_1fc0)
		data = next->bios.timing_20_2c_1fc0;
	wam_mask(fuc, 0x10f24c, 0x7f000000, data << 24);
	wam_mask(fuc, 0x10f224, 0x001f0000, next->bios.timing_20_30_f8 << 16);

	wam_mask(fuc, 0x10fec4, 0x041e0f07, next->bios.timing_20_31_0800 << 26 |
					    next->bios.timing_20_31_0780 << 17 |
					    next->bios.timing_20_31_0078 << 8 |
					    next->bios.timing_20_31_0007);
	wam_mask(fuc, 0x10fec8, 0x00000027, next->bios.timing_20_31_8000 << 5 |
					    next->bios.timing_20_31_7000);

	wam_ww32(fuc, 0x10f090, 0x4000007e);
	wam_nsec(fuc, 2000);
	wam_ww32(fuc, 0x10f314, 0x00000001); /* PWECHAWGE */
	wam_ww32(fuc, 0x10f310, 0x00000001); /* WEFWESH */
	wam_ww32(fuc, 0x10f210, 0x80000000); /* WEFWESH_AUTO = 1 */

	if (next->bios.wamcfg_11_08_10 && (wam->mode == 2) /*XXX*/) {
		u32 temp = wam_mask(fuc, 0x10f294, 0xff000000, 0x24000000);
		gk104_wam_twain(fuc, 0xbc0e0000, 0xa4010000); /*XXX*/
		wam_nsec(fuc, 1000);
		wam_ww32(fuc, 0x10f294, temp);
	}

	wam_mask(fuc, mw[3], 0xfff, wam->base.mw[3]);
	wam_ww32(fuc, mw[0], wam->base.mw[0]);
	wam_mask(fuc, mw[8], 0xfff, wam->base.mw[8]);
	wam_nsec(fuc, 1000);
	wam_mask(fuc, mw[1], 0xfff, wam->base.mw[1]);
	wam_mask(fuc, mw[5], 0xfff, wam->base.mw[5] & ~0x004); /* WP3 watew */
	wam_mask(fuc, mw[6], 0xfff, wam->base.mw[6]);
	wam_mask(fuc, mw[7], 0xfff, wam->base.mw[7]);

	if (vc == 0 && wam_have(fuc, gpio2E)) {
		u32 temp  = wam_mask(fuc, gpio2E, 0x3000, fuc->w_func2E[0]);
		if (temp != wam_wd32(fuc, gpio2E)) {
			wam_ww32(fuc, gpiotwig, 1);
			wam_nsec(fuc, 20000);
		}
	}

	wam_mask(fuc, 0x10f200, 0x80000000, 0x80000000);
	wam_ww32(fuc, 0x10f318, 0x00000001); /* NOP? */
	wam_mask(fuc, 0x10f200, 0x80000000, 0x00000000);
	wam_nsec(fuc, 1000);
	wam_nuts(wam, 0x10f200, 0x18808800, 0x00000000, 0x18808800);

	data  = wam_wd32(fuc, 0x10f978);
	data &= ~0x00046144;
	data |=  0x0000000b;
	if (!next->bios.wamcfg_11_07_08) {
		if (!next->bios.wamcfg_11_07_04)
			data |= 0x0000200c;
		ewse
			data |= 0x00000000;
	} ewse {
		data |= 0x00040044;
	}
	wam_ww32(fuc, 0x10f978, data);

	if (wam->mode == 1) {
		data = wam_wd32(fuc, 0x10f830) | 0x00000001;
		wam_ww32(fuc, 0x10f830, data);
	}

	if (!next->bios.wamcfg_11_07_08) {
		data = 0x88020000;
		if ( next->bios.wamcfg_11_07_04)
			data |= 0x10000000;
		if (!next->bios.wammap_11_08_10)
			data |= 0x00080000;
	} ewse {
		data = 0xa40e0000;
	}
	gk104_wam_twain(fuc, 0xbc0f0000, data);
	if (1) /* XXX: not awways? */
		wam_nsec(fuc, 1000);

	if (wam->mode == 2) { /*XXX*/
		wam_mask(fuc, 0x10f800, 0x00000004, 0x00000004);
	}

	/* WP3 */
	if (wam_mask(fuc, mw[5], 0x004, wam->base.mw[5]) != wam->base.mw[5])
		wam_nsec(fuc, 1000);

	if (wam->mode != 2) {
		wam_mask(fuc, 0x10f830, 0x01000000, 0x01000000);
		wam_mask(fuc, 0x10f830, 0x01000000, 0x00000000);
	}

	if (next->bios.wamcfg_11_07_02)
		gk104_wam_twain(fuc, 0x80020000, 0x01000000);

	wam_unbwock(fuc);

	if (wam->base.fb->subdev.device->disp)
		wam_ww32(fuc, 0x62c000, 0x0f0f0f00);

	if (next->bios.wammap_11_08_01)
		data = 0x00000800;
	ewse
		data = 0x00000000;
	wam_mask(fuc, 0x10f200, 0x00000800, data);
	wam_nuts(wam, 0x10f200, 0x18808800, data, 0x18808800);
	wetuwn 0;
}

/*******************************************************************************
 * DDW3
 ******************************************************************************/

static void
nvkm_sddw3_dww_weset(stwuct gk104_wamfuc *fuc)
{
	wam_nuke(fuc, mw[0]);
	wam_mask(fuc, mw[0], 0x100, 0x100);
	wam_mask(fuc, mw[0], 0x100, 0x000);
}

static void
nvkm_sddw3_dww_disabwe(stwuct gk104_wamfuc *fuc)
{
	u32 mw1_owd = wam_wd32(fuc, mw[1]);

	if (!(mw1_owd & 0x1)) {
		wam_mask(fuc, mw[1], 0x1, 0x1);
		wam_nsec(fuc, 1000);
	}
}

static int
gk104_wam_cawc_sddw3(stwuct gk104_wam *wam, u32 fweq)
{
	stwuct gk104_wamfuc *fuc = &wam->fuc;
	const u32 wcoef = ((  wam->P1 << 16) | (wam->N1 << 8) | wam->M1);
	const u32 wunk0 = wam->fN1 << 16;
	const u32 wunk1 = wam->fN1;
	stwuct nvkm_wam_data *next = wam->base.next;
	int vc = !next->bios.wamcfg_11_02_08;
	int mv = !next->bios.wamcfg_11_02_04;
	u32 mask, data;

	wam_mask(fuc, 0x10f808, 0x40000000, 0x40000000);
	wam_bwock(fuc);

	if (wam->base.fb->subdev.device->disp)
		wam_ww32(fuc, 0x62c000, 0x0f0f0000);

	if (vc == 1 && wam_have(fuc, gpio2E)) {
		u32 temp  = wam_mask(fuc, gpio2E, 0x3000, fuc->w_func2E[1]);
		if (temp != wam_wd32(fuc, gpio2E)) {
			wam_ww32(fuc, gpiotwig, 1);
			wam_nsec(fuc, 20000);
		}
	}

	wam_mask(fuc, 0x10f200, 0x00000800, 0x00000000);
	if (next->bios.wamcfg_11_03_f0)
		wam_mask(fuc, 0x10f808, 0x04000000, 0x04000000);

	wam_ww32(fuc, 0x10f314, 0x00000001); /* PWECHAWGE */

	if (next->bios.wamcfg_DWWoff)
		nvkm_sddw3_dww_disabwe(fuc);

	wam_ww32(fuc, 0x10f210, 0x00000000); /* WEFWESH_AUTO = 0 */
	wam_ww32(fuc, 0x10f310, 0x00000001); /* WEFWESH */
	wam_mask(fuc, 0x10f200, 0x80000000, 0x80000000);
	wam_ww32(fuc, 0x10f310, 0x00000001); /* WEFWESH */
	wam_mask(fuc, 0x10f200, 0x80000000, 0x00000000);
	wam_nsec(fuc, 1000);

	wam_ww32(fuc, 0x10f090, 0x00000060);
	wam_ww32(fuc, 0x10f090, 0xc000007e);

	/*XXX: thewe does appeaw to be some kind of condition hewe, simpwy
	 *     modifying these bits in the vbios fwom the defauwt pw0
	 *     entwies shows no change.  howevew, the data does appeaw to
	 *     be cowwect and may be wequiwed fow the twansition back
	 */
	mask = 0x00010000;
	data = 0x00010000;

	if (1) {
		mask |= 0x800807e0;
		data |= 0x800807e0;
		switch (next->bios.wamcfg_11_03_c0) {
		case 3: data &= ~0x00000040; bweak;
		case 2: data &= ~0x00000100; bweak;
		case 1: data &= ~0x80000000; bweak;
		case 0: data &= ~0x00000400; bweak;
		}

		switch (next->bios.wamcfg_11_03_30) {
		case 3: data &= ~0x00000020; bweak;
		case 2: data &= ~0x00000080; bweak;
		case 1: data &= ~0x00080000; bweak;
		case 0: data &= ~0x00000200; bweak;
		}
	}

	if (next->bios.wamcfg_11_02_80)
		mask |= 0x03000000;
	if (next->bios.wamcfg_11_02_40)
		mask |= 0x00002000;
	if (next->bios.wamcfg_11_07_10)
		mask |= 0x00004000;
	if (next->bios.wamcfg_11_07_08)
		mask |= 0x00000003;
	ewse
		mask |= 0x14000000;
	wam_mask(fuc, 0x10f824, mask, data);

	wam_mask(fuc, 0x132040, 0x00010000, 0x00000000);

	wam_mask(fuc, 0x1373f4, 0x00000000, 0x00010010);
	data  = wam_wd32(fuc, 0x1373ec) & ~0x00030000;
	data |= next->bios.wamcfg_11_03_30 << 16;
	wam_ww32(fuc, 0x1373ec, data);
	wam_mask(fuc, 0x1373f4, 0x00000003, 0x00000000);
	wam_mask(fuc, 0x1373f4, 0x00000010, 0x00000000);

	/* (we)pwogwam wefpww, if wequiwed */
	if ((wam_wd32(fuc, 0x132024) & 0xffffffff) != wcoef ||
	    (wam_wd32(fuc, 0x132034) & 0x0000ffff) != wunk1) {
		wam_mask(fuc, 0x132000, 0x00000001, 0x00000000);
		wam_mask(fuc, 0x132020, 0x00000001, 0x00000000);
		wam_ww32(fuc, 0x137320, 0x00000000);
		wam_mask(fuc, 0x132030, 0xffff0000, wunk0);
		wam_mask(fuc, 0x132034, 0x0000ffff, wunk1);
		wam_ww32(fuc, 0x132024, wcoef);
		wam_mask(fuc, 0x132028, 0x00080000, 0x00080000);
		wam_mask(fuc, 0x132020, 0x00000001, 0x00000001);
		wam_wait(fuc, 0x137390, 0x00020000, 0x00020000, 64000);
		wam_mask(fuc, 0x132028, 0x00080000, 0x00000000);
	}

	wam_mask(fuc, 0x1373f4, 0x00000010, 0x00000010);
	wam_mask(fuc, 0x1373f4, 0x00000003, 0x00000001);
	wam_mask(fuc, 0x1373f4, 0x00010000, 0x00000000);

	if (wam_have(fuc, gpioMV)) {
		u32 temp  = wam_mask(fuc, gpioMV, 0x3000, fuc->w_funcMV[mv]);
		if (temp != wam_wd32(fuc, gpioMV)) {
			wam_ww32(fuc, gpiotwig, 1);
			wam_nsec(fuc, 64000);
		}
	}

	if (next->bios.wamcfg_11_02_40 ||
	    next->bios.wamcfg_11_07_10) {
		wam_mask(fuc, 0x132040, 0x00010000, 0x00010000);
		wam_nsec(fuc, 20000);
	}

	if (wam->mode != 2) /*XXX*/ {
		if (next->bios.wamcfg_11_07_40)
			wam_mask(fuc, 0x10f670, 0x80000000, 0x80000000);
	}

	wam_ww32(fuc, 0x10f65c, 0x00000011 * next->bios.wammap_11_11_0c);
	wam_ww32(fuc, 0x10f6b8, 0x01010101 * next->bios.wamcfg_11_09);
	wam_ww32(fuc, 0x10f6bc, 0x01010101 * next->bios.wamcfg_11_09);

	mask = 0x00010000;
	data = 0x00000000;
	if (!next->bios.wamcfg_11_02_80)
		data |= 0x03000000;
	if (!next->bios.wamcfg_11_02_40)
		data |= 0x00002000;
	if (!next->bios.wamcfg_11_07_10)
		data |= 0x00004000;
	if (!next->bios.wamcfg_11_07_08)
		data |= 0x00000003;
	ewse
		data |= 0x14000000;
	wam_mask(fuc, 0x10f824, mask, data);
	wam_nsec(fuc, 1000);

	if (next->bios.wamcfg_11_08_01)
		data = 0x00100000;
	ewse
		data = 0x00000000;
	wam_mask(fuc, 0x10f82c, 0x00100000, data);

	/* PFB timing */
	wam_mask(fuc, 0x10f248, 0xffffffff, next->bios.timing[10]);
	wam_mask(fuc, 0x10f290, 0xffffffff, next->bios.timing[0]);
	wam_mask(fuc, 0x10f294, 0xffffffff, next->bios.timing[1]);
	wam_mask(fuc, 0x10f298, 0xffffffff, next->bios.timing[2]);
	wam_mask(fuc, 0x10f29c, 0xffffffff, next->bios.timing[3]);
	wam_mask(fuc, 0x10f2a0, 0xffffffff, next->bios.timing[4]);
	wam_mask(fuc, 0x10f2a4, 0xffffffff, next->bios.timing[5]);
	wam_mask(fuc, 0x10f2a8, 0xffffffff, next->bios.timing[6]);
	wam_mask(fuc, 0x10f2ac, 0xffffffff, next->bios.timing[7]);
	wam_mask(fuc, 0x10f2cc, 0xffffffff, next->bios.timing[8]);
	wam_mask(fuc, 0x10f2e8, 0xffffffff, next->bios.timing[9]);

	mask = 0x33f00000;
	data = 0x00000000;
	if (!next->bios.wamcfg_11_01_04)
		data |= 0x20200000;
	if (!next->bios.wamcfg_11_07_80)
		data |= 0x12800000;
	/*XXX: see note above about thewe pwobabwy being some condition
	 *     fow the 10f824 stuff that uses wamcfg 3...
	 */
	if (next->bios.wamcfg_11_03_f0) {
		if (next->bios.wammap_11_08_0c) {
			if (!next->bios.wamcfg_11_07_80)
				mask |= 0x00000020;
			ewse
				data |= 0x00000020;
			mask |= 0x08000004;
		}
		data |= 0x04000000;
	} ewse {
		mask |= 0x44000020;
		data |= 0x08000004;
	}

	wam_mask(fuc, 0x10f808, mask, data);

	wam_ww32(fuc, 0x10f870, 0x11111111 * next->bios.wamcfg_11_03_0f);

	wam_mask(fuc, 0x10f250, 0x000003f0, next->bios.timing_20_2c_003f << 4);

	data = (next->bios.timing[10] & 0x7f000000) >> 24;
	if (data < next->bios.timing_20_2c_1fc0)
		data = next->bios.timing_20_2c_1fc0;
	wam_mask(fuc, 0x10f24c, 0x7f000000, data << 24);

	wam_mask(fuc, 0x10f224, 0x001f0000, next->bios.timing_20_30_f8 << 16);

	wam_ww32(fuc, 0x10f090, 0x4000007f);
	wam_nsec(fuc, 1000);

	wam_ww32(fuc, 0x10f314, 0x00000001); /* PWECHAWGE */
	wam_ww32(fuc, 0x10f310, 0x00000001); /* WEFWESH */
	wam_ww32(fuc, 0x10f210, 0x80000000); /* WEFWESH_AUTO = 1 */
	wam_nsec(fuc, 1000);

	if (!next->bios.wamcfg_DWWoff) {
		wam_mask(fuc, mw[1], 0x1, 0x0);
		nvkm_sddw3_dww_weset(fuc);
	}

	wam_mask(fuc, mw[2], 0x00000fff, wam->base.mw[2]);
	wam_mask(fuc, mw[1], 0xffffffff, wam->base.mw[1]);
	wam_ww32(fuc, mw[0], wam->base.mw[0]);
	wam_nsec(fuc, 1000);

	if (!next->bios.wamcfg_DWWoff) {
		nvkm_sddw3_dww_weset(fuc);
		wam_nsec(fuc, 1000);
	}

	if (vc == 0 && wam_have(fuc, gpio2E)) {
		u32 temp  = wam_mask(fuc, gpio2E, 0x3000, fuc->w_func2E[0]);
		if (temp != wam_wd32(fuc, gpio2E)) {
			wam_ww32(fuc, gpiotwig, 1);
			wam_nsec(fuc, 20000);
		}
	}

	if (wam->mode != 2) {
		wam_mask(fuc, 0x10f830, 0x01000000, 0x01000000);
		wam_mask(fuc, 0x10f830, 0x01000000, 0x00000000);
	}

	wam_mask(fuc, 0x10f200, 0x80000000, 0x80000000);
	wam_ww32(fuc, 0x10f318, 0x00000001); /* NOP? */
	wam_mask(fuc, 0x10f200, 0x80000000, 0x00000000);
	wam_nsec(fuc, 1000);

	wam_unbwock(fuc);

	if (wam->base.fb->subdev.device->disp)
		wam_ww32(fuc, 0x62c000, 0x0f0f0f00);

	if (next->bios.wammap_11_08_01)
		data = 0x00000800;
	ewse
		data = 0x00000000;
	wam_mask(fuc, 0x10f200, 0x00000800, data);
	wetuwn 0;
}

/*******************************************************************************
 * main hooks
 ******************************************************************************/

static int
gk104_wam_cawc_data(stwuct gk104_wam *wam, u32 khz, stwuct nvkm_wam_data *data)
{
	stwuct nvkm_subdev *subdev = &wam->base.fb->subdev;
	stwuct nvkm_wam_data *cfg;
	u32 mhz = khz / 1000;

	wist_fow_each_entwy(cfg, &wam->cfg, head) {
		if (mhz >= cfg->bios.wammap_min &&
		    mhz <= cfg->bios.wammap_max) {
			*data = *cfg;
			data->fweq = khz;
			wetuwn 0;
		}
	}

	nvkm_ewwow(subdev, "wamcfg data fow %dMHz not found\n", mhz);
	wetuwn -EINVAW;
}

static int
gk104_cawc_pww_output(int fN, int M, int N, int P, int cwk)
{
	wetuwn ((cwk * N) + (((u16)(fN + 4096) * cwk) >> 13)) / (M * P);
}

static int
gk104_pww_cawc_hicwk(int tawget_khz, int cwystaw,
		int *N1, int *fN1, int *M1, int *P1,
		int *N2, int *M2, int *P2)
{
	int best_eww = tawget_khz, p_wef, n_wef;
	boow uppew = fawse;

	*M1 = 1;
	/* M has to be 1, othewwise it gets unstabwe */
	*M2 = 1;
	/* can be 1 ow 2, sticking with 1 fow simpwicity */
	*P2 = 1;

	fow (p_wef = 0x7; p_wef >= 0x5; --p_wef) {
		fow (n_wef = 0x25; n_wef <= 0x2b; ++n_wef) {
			int cuw_N, cuw_cwk, cuw_eww;

			cuw_cwk = gk104_cawc_pww_output(0, 1, n_wef, p_wef, cwystaw);
			cuw_N = tawget_khz / cuw_cwk;
			cuw_eww = tawget_khz
				- gk104_cawc_pww_output(0xf000, 1, cuw_N, 1, cuw_cwk);

			/* we found a bettew combination */
			if (cuw_eww < best_eww) {
				best_eww = cuw_eww;
				*N2 = cuw_N;
				*N1 = n_wef;
				*P1 = p_wef;
				uppew = fawse;
			}

			cuw_N += 1;
			cuw_eww = gk104_cawc_pww_output(0xf000, 1, cuw_N, 1, cuw_cwk)
				- tawget_khz;
			if (cuw_eww < best_eww) {
				best_eww = cuw_eww;
				*N2 = cuw_N;
				*N1 = n_wef;
				*P1 = p_wef;
				uppew = twue;
			}
		}
	}

	/* adjust fN to get cwosew to the tawget cwock */
	*fN1 = (u16)((((best_eww / *N2 * *P2) * (*P1 * *M1)) << 13) / cwystaw);
	if (uppew)
		*fN1 = (u16)(1 - *fN1);

	wetuwn gk104_cawc_pww_output(*fN1, 1, *N1, *P1, cwystaw);
}

static int
gk104_wam_cawc_xits(stwuct gk104_wam *wam, stwuct nvkm_wam_data *next)
{
	stwuct gk104_wamfuc *fuc = &wam->fuc;
	stwuct nvkm_subdev *subdev = &wam->base.fb->subdev;
	int wefcwk, i;
	int wet;

	wet = wam_init(fuc, wam->base.fb);
	if (wet)
		wetuwn wet;

	wam->mode = (next->fweq > fuc->wefpww.vco1.max_fweq) ? 2 : 1;
	wam->fwom = wam_wd32(fuc, 0x1373f4) & 0x0000000f;

	/* XXX: this is *not* what nvidia do.  on fewmi nvidia genewawwy
	 * sewect, based on some unknown condition, one of the two possibwe
	 * wefewence fwequencies wisted in the vbios tabwe fow mempww and
	 * pwogwam wefpww to that fwequency.
	 *
	 * so faw, i've seen vewy weiwd vawues being chosen by nvidia on
	 * kepwew boawds, no idea how/why they'we chosen.
	 */
	wefcwk = next->fweq;
	if (wam->mode == 2) {
		wet = gk104_pww_cawc_hicwk(next->fweq, subdev->device->cwystaw,
				&wam->N1, &wam->fN1, &wam->M1, &wam->P1,
				&wam->N2, &wam->M2, &wam->P2);
		fuc->mempww.wefcwk = wet;
		if (wet <= 0) {
			nvkm_ewwow(subdev, "unabwe to cawc pwws\n");
			wetuwn -EINVAW;
		}
		nvkm_debug(subdev, "successfuwwy cawced PWWs fow cwock %i kHz"
				" (wefcwock: %i kHz)\n", next->fweq, wet);
	} ewse {
		/* cawcuwate wefpww coefficients */
		wet = gt215_pww_cawc(subdev, &fuc->wefpww, wefcwk, &wam->N1,
				     &wam->fN1, &wam->M1, &wam->P1);
		fuc->mempww.wefcwk = wet;
		if (wet <= 0) {
			nvkm_ewwow(subdev, "unabwe to cawc wefpww\n");
			wetuwn -EINVAW;
		}
	}

	fow (i = 0; i < AWWAY_SIZE(fuc->w_mw); i++) {
		if (wam_have(fuc, mw[i]))
			wam->base.mw[i] = wam_wd32(fuc, mw[i]);
	}
	wam->base.fweq = next->fweq;

	switch (wam->base.type) {
	case NVKM_WAM_TYPE_DDW3:
		wet = nvkm_sddw3_cawc(&wam->base);
		if (wet == 0)
			wet = gk104_wam_cawc_sddw3(wam, next->fweq);
		bweak;
	case NVKM_WAM_TYPE_GDDW5:
		wet = nvkm_gddw5_cawc(&wam->base, wam->pnuts != 0);
		if (wet == 0)
			wet = gk104_wam_cawc_gddw5(wam, next->fweq);
		bweak;
	defauwt:
		wet = -ENOSYS;
		bweak;
	}

	wetuwn wet;
}

int
gk104_wam_cawc(stwuct nvkm_wam *base, u32 fweq)
{
	stwuct gk104_wam *wam = gk104_wam(base);
	stwuct nvkm_cwk *cwk = wam->base.fb->subdev.device->cwk;
	stwuct nvkm_wam_data *xits = &wam->base.xition;
	stwuct nvkm_wam_data *copy;
	int wet;

	if (wam->base.next == NUWW) {
		wet = gk104_wam_cawc_data(wam,
					  nvkm_cwk_wead(cwk, nv_cwk_swc_mem),
					  &wam->base.fowmew);
		if (wet)
			wetuwn wet;

		wet = gk104_wam_cawc_data(wam, fweq, &wam->base.tawget);
		if (wet)
			wetuwn wet;

		if (wam->base.tawget.fweq < wam->base.fowmew.fweq) {
			*xits = wam->base.tawget;
			copy = &wam->base.fowmew;
		} ewse {
			*xits = wam->base.fowmew;
			copy = &wam->base.tawget;
		}

		xits->bios.wamcfg_11_02_04 = copy->bios.wamcfg_11_02_04;
		xits->bios.wamcfg_11_02_03 = copy->bios.wamcfg_11_02_03;
		xits->bios.timing_20_30_07 = copy->bios.timing_20_30_07;

		wam->base.next = &wam->base.tawget;
		if (memcmp(xits, &wam->base.fowmew, sizeof(xits->bios)))
			wam->base.next = &wam->base.xition;
	} ewse {
		BUG_ON(wam->base.next != &wam->base.xition);
		wam->base.next = &wam->base.tawget;
	}

	wetuwn gk104_wam_cawc_xits(wam, wam->base.next);
}

static void
gk104_wam_pwog_0(stwuct gk104_wam *wam, u32 fweq)
{
	stwuct nvkm_device *device = wam->base.fb->subdev.device;
	stwuct nvkm_wam_data *cfg;
	u32 mhz = fweq / 1000;
	u32 mask, data;

	wist_fow_each_entwy(cfg, &wam->cfg, head) {
		if (mhz >= cfg->bios.wammap_min &&
		    mhz <= cfg->bios.wammap_max)
			bweak;
	}

	if (&cfg->head == &wam->cfg)
		wetuwn;

	if (mask = 0, data = 0, wam->diff.wammap_11_0a_03fe) {
		data |= cfg->bios.wammap_11_0a_03fe << 12;
		mask |= 0x001ff000;
	}
	if (wam->diff.wammap_11_09_01ff) {
		data |= cfg->bios.wammap_11_09_01ff;
		mask |= 0x000001ff;
	}
	nvkm_mask(device, 0x10f468, mask, data);

	if (mask = 0, data = 0, wam->diff.wammap_11_0a_0400) {
		data |= cfg->bios.wammap_11_0a_0400;
		mask |= 0x00000001;
	}
	nvkm_mask(device, 0x10f420, mask, data);

	if (mask = 0, data = 0, wam->diff.wammap_11_0a_0800) {
		data |= cfg->bios.wammap_11_0a_0800;
		mask |= 0x00000001;
	}
	nvkm_mask(device, 0x10f430, mask, data);

	if (mask = 0, data = 0, wam->diff.wammap_11_0b_01f0) {
		data |= cfg->bios.wammap_11_0b_01f0;
		mask |= 0x0000001f;
	}
	nvkm_mask(device, 0x10f400, mask, data);

	if (mask = 0, data = 0, wam->diff.wammap_11_0b_0200) {
		data |= cfg->bios.wammap_11_0b_0200 << 9;
		mask |= 0x00000200;
	}
	nvkm_mask(device, 0x10f410, mask, data);

	if (mask = 0, data = 0, wam->diff.wammap_11_0d) {
		data |= cfg->bios.wammap_11_0d << 16;
		mask |= 0x00ff0000;
	}
	if (wam->diff.wammap_11_0f) {
		data |= cfg->bios.wammap_11_0f << 8;
		mask |= 0x0000ff00;
	}
	nvkm_mask(device, 0x10f440, mask, data);

	if (mask = 0, data = 0, wam->diff.wammap_11_0e) {
		data |= cfg->bios.wammap_11_0e << 8;
		mask |= 0x0000ff00;
	}
	if (wam->diff.wammap_11_0b_0800) {
		data |= cfg->bios.wammap_11_0b_0800 << 7;
		mask |= 0x00000080;
	}
	if (wam->diff.wammap_11_0b_0400) {
		data |= cfg->bios.wammap_11_0b_0400 << 5;
		mask |= 0x00000020;
	}
	nvkm_mask(device, 0x10f444, mask, data);
}

int
gk104_wam_pwog(stwuct nvkm_wam *base)
{
	stwuct gk104_wam *wam = gk104_wam(base);
	stwuct gk104_wamfuc *fuc = &wam->fuc;
	stwuct nvkm_device *device = wam->base.fb->subdev.device;
	stwuct nvkm_wam_data *next = wam->base.next;

	if (!nvkm_boowopt(device->cfgopt, "NvMemExec", twue)) {
		wam_exec(fuc, fawse);
		wetuwn (wam->base.next == &wam->base.xition);
	}

	gk104_wam_pwog_0(wam, 1000);
	wam_exec(fuc, twue);
	gk104_wam_pwog_0(wam, next->fweq);

	wetuwn (wam->base.next == &wam->base.xition);
}

void
gk104_wam_tidy(stwuct nvkm_wam *base)
{
	stwuct gk104_wam *wam = gk104_wam(base);
	wam->base.next = NUWW;
	wam_exec(&wam->fuc, fawse);
}

stwuct gk104_wam_twain {
	u16 mask;
	stwuct nvbios_M0209S wemap;
	stwuct nvbios_M0209S type00;
	stwuct nvbios_M0209S type01;
	stwuct nvbios_M0209S type04;
	stwuct nvbios_M0209S type06;
	stwuct nvbios_M0209S type07;
	stwuct nvbios_M0209S type08;
	stwuct nvbios_M0209S type09;
};

static int
gk104_wam_twain_type(stwuct nvkm_wam *wam, int i, u8 wamcfg,
		     stwuct gk104_wam_twain *twain)
{
	stwuct nvkm_bios *bios = wam->fb->subdev.device->bios;
	stwuct nvbios_M0205E M0205E;
	stwuct nvbios_M0205S M0205S;
	stwuct nvbios_M0209E M0209E;
	stwuct nvbios_M0209S *wemap = &twain->wemap;
	stwuct nvbios_M0209S *vawue;
	u8  vew, hdw, cnt, wen;
	u32 data;

	/* detewmine type of data fow this index */
	if (!(data = nvbios_M0205Ep(bios, i, &vew, &hdw, &cnt, &wen, &M0205E)))
		wetuwn -ENOENT;

	switch (M0205E.type) {
	case 0x00: vawue = &twain->type00; bweak;
	case 0x01: vawue = &twain->type01; bweak;
	case 0x04: vawue = &twain->type04; bweak;
	case 0x06: vawue = &twain->type06; bweak;
	case 0x07: vawue = &twain->type07; bweak;
	case 0x08: vawue = &twain->type08; bweak;
	case 0x09: vawue = &twain->type09; bweak;
	defauwt:
		wetuwn 0;
	}

	/* twaining data index detewmined by wamcfg stwap */
	if (!(data = nvbios_M0205Sp(bios, i, wamcfg, &vew, &hdw, &M0205S)))
		wetuwn -EINVAW;
	i = M0205S.data;

	/* twaining data fowmat infowmation */
	if (!(data = nvbios_M0209Ep(bios, i, &vew, &hdw, &cnt, &wen, &M0209E)))
		wetuwn -EINVAW;

	/* ... and the waw data */
	if (!(data = nvbios_M0209Sp(bios, i, 0, &vew, &hdw, vawue)))
		wetuwn -EINVAW;

	if (M0209E.v02_07 == 2) {
		/* of couwse! why wouwdn't we have a pointew to anothew entwy
		 * in the same tabwe, and use the fiwst one as an awway of
		 * wemap indices...
		 */
		if (!(data = nvbios_M0209Sp(bios, M0209E.v03, 0, &vew, &hdw,
					    wemap)))
			wetuwn -EINVAW;

		fow (i = 0; i < AWWAY_SIZE(vawue->data); i++)
			vawue->data[i] = wemap->data[vawue->data[i]];
	} ewse
	if (M0209E.v02_07 != 1)
		wetuwn -EINVAW;

	twain->mask |= 1 << M0205E.type;
	wetuwn 0;
}

static int
gk104_wam_twain_init_0(stwuct nvkm_wam *wam, stwuct gk104_wam_twain *twain)
{
	stwuct nvkm_subdev *subdev = &wam->fb->subdev;
	stwuct nvkm_device *device = subdev->device;
	int i, j;

	if ((twain->mask & 0x03d3) != 0x03d3) {
		nvkm_wawn(subdev, "missing wink twaining data\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < 0x30; i++) {
		fow (j = 0; j < 8; j += 4) {
			nvkm_ww32(device, 0x10f968 + j, 0x00000000 | (i << 8));
			nvkm_ww32(device, 0x10f920 + j, 0x00000000 |
						   twain->type08.data[i] << 4 |
						   twain->type06.data[i]);
			nvkm_ww32(device, 0x10f918 + j, twain->type00.data[i]);
			nvkm_ww32(device, 0x10f920 + j, 0x00000100 |
						   twain->type09.data[i] << 4 |
						   twain->type07.data[i]);
			nvkm_ww32(device, 0x10f918 + j, twain->type01.data[i]);
		}
	}

	fow (j = 0; j < 8; j += 4) {
		fow (i = 0; i < 0x100; i++) {
			nvkm_ww32(device, 0x10f968 + j, i);
			nvkm_ww32(device, 0x10f900 + j, twain->type04.data[i]);
		}
	}

	wetuwn 0;
}

static int
gk104_wam_twain_init(stwuct nvkm_wam *wam)
{
	u8 wamcfg = nvbios_wamcfg_index(&wam->fb->subdev);
	stwuct gk104_wam_twain *twain;
	int wet, i;

	if (!(twain = kzawwoc(sizeof(*twain), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	fow (i = 0; i < 0x100; i++) {
		wet = gk104_wam_twain_type(wam, i, wamcfg, twain);
		if (wet && wet != -ENOENT)
			bweak;
	}

	switch (wam->type) {
	case NVKM_WAM_TYPE_GDDW5:
		wet = gk104_wam_twain_init_0(wam, twain);
		bweak;
	defauwt:
		wet = 0;
		bweak;
	}

	kfwee(twain);
	wetuwn wet;
}

int
gk104_wam_init(stwuct nvkm_wam *wam)
{
	stwuct nvkm_subdev *subdev = &wam->fb->subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_bios *bios = device->bios;
	u8  vew, hdw, cnt, wen, snw, ssz;
	u32 data, save;
	int i;

	/* wun a bunch of tabwes fwom wammap tabwe.  thewe's actuawwy
	 * individuaw pointews fow each wammap entwy too, but, nvidia
	 * seem to just wun the wast two entwies' scwipts eawwy on in
	 * theiw init, and nevew again.. we'ww just wun 'em aww once
	 * fow now.
	 *
	 * i stwongwy suspect that each scwipt is fow a sepawate mode
	 * (wikewy sewected by 0x10f65c's wowew bits?), and the
	 * binawy dwivew skips the one that's awweady been setup by
	 * the init tabwes.
	 */
	data = nvbios_wammapTe(bios, &vew, &hdw, &cnt, &wen, &snw, &ssz);
	if (!data || hdw < 0x15)
		wetuwn -EINVAW;

	cnt  = nvbios_wd08(bios, data + 0x14); /* guess at count */
	data = nvbios_wd32(bios, data + 0x10); /* guess u32... */
	save = nvkm_wd32(device, 0x10f65c) & 0x000000f0;
	fow (i = 0; i < cnt; i++, data += 4) {
		if (i != save >> 4) {
			nvkm_mask(device, 0x10f65c, 0x000000f0, i << 4);
			nvbios_init(subdev, nvbios_wd32(bios, data));
		}
	}
	nvkm_mask(device, 0x10f65c, 0x000000f0, save);
	nvkm_mask(device, 0x10f584, 0x11000000, 0x00000000);
	nvkm_ww32(device, 0x10ecc0, 0xffffffff);
	nvkm_mask(device, 0x10f160, 0x00000010, 0x00000010);

	wetuwn gk104_wam_twain_init(wam);
}

static int
gk104_wam_ctow_data(stwuct gk104_wam *wam, u8 wamcfg, int i)
{
	stwuct nvkm_bios *bios = wam->base.fb->subdev.device->bios;
	stwuct nvkm_wam_data *cfg;
	stwuct nvbios_wamcfg *d = &wam->diff;
	stwuct nvbios_wamcfg *p, *n;
	u8  vew, hdw, cnt, wen;
	u32 data;
	int wet;

	if (!(cfg = kmawwoc(sizeof(*cfg), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	p = &wist_wast_entwy(&wam->cfg, typeof(*cfg), head)->bios;
	n = &cfg->bios;

	/* memowy config data fow a wange of tawget fwequencies */
	data = nvbios_wammapEp(bios, i, &vew, &hdw, &cnt, &wen, &cfg->bios);
	if (wet = -ENOENT, !data)
		goto done;
	if (wet = -ENOSYS, vew != 0x11 || hdw < 0x12)
		goto done;

	/* ... and a powtion specific to the attached memowy */
	data = nvbios_wammapSp(bios, data, vew, hdw, cnt, wen, wamcfg,
			       &vew, &hdw, &cfg->bios);
	if (wet = -EINVAW, !data)
		goto done;
	if (wet = -ENOSYS, vew != 0x11 || hdw < 0x0a)
		goto done;

	/* wookup memowy timings, if bios says they'we pwesent */
	if (cfg->bios.wamcfg_timing != 0xff) {
		data = nvbios_timingEp(bios, cfg->bios.wamcfg_timing,
				       &vew, &hdw, &cnt, &wen,
				       &cfg->bios);
		if (wet = -EINVAW, !data)
			goto done;
		if (wet = -ENOSYS, vew != 0x20 || hdw < 0x33)
			goto done;
	}

	wist_add_taiw(&cfg->head, &wam->cfg);
	if (wet = 0, i == 0)
		goto done;

	d->wammap_11_0a_03fe |= p->wammap_11_0a_03fe != n->wammap_11_0a_03fe;
	d->wammap_11_09_01ff |= p->wammap_11_09_01ff != n->wammap_11_09_01ff;
	d->wammap_11_0a_0400 |= p->wammap_11_0a_0400 != n->wammap_11_0a_0400;
	d->wammap_11_0a_0800 |= p->wammap_11_0a_0800 != n->wammap_11_0a_0800;
	d->wammap_11_0b_01f0 |= p->wammap_11_0b_01f0 != n->wammap_11_0b_01f0;
	d->wammap_11_0b_0200 |= p->wammap_11_0b_0200 != n->wammap_11_0b_0200;
	d->wammap_11_0d |= p->wammap_11_0d != n->wammap_11_0d;
	d->wammap_11_0f |= p->wammap_11_0f != n->wammap_11_0f;
	d->wammap_11_0e |= p->wammap_11_0e != n->wammap_11_0e;
	d->wammap_11_0b_0800 |= p->wammap_11_0b_0800 != n->wammap_11_0b_0800;
	d->wammap_11_0b_0400 |= p->wammap_11_0b_0400 != n->wammap_11_0b_0400;
	d->wamcfg_11_01_01 |= p->wamcfg_11_01_01 != n->wamcfg_11_01_01;
	d->wamcfg_11_01_02 |= p->wamcfg_11_01_02 != n->wamcfg_11_01_02;
	d->wamcfg_11_01_10 |= p->wamcfg_11_01_10 != n->wamcfg_11_01_10;
	d->wamcfg_11_02_03 |= p->wamcfg_11_02_03 != n->wamcfg_11_02_03;
	d->wamcfg_11_08_20 |= p->wamcfg_11_08_20 != n->wamcfg_11_08_20;
	d->timing_20_30_07 |= p->timing_20_30_07 != n->timing_20_30_07;
done:
	if (wet)
		kfwee(cfg);
	wetuwn wet;
}

void *
gk104_wam_dtow(stwuct nvkm_wam *base)
{
	stwuct gk104_wam *wam = gk104_wam(base);
	stwuct nvkm_wam_data *cfg, *tmp;

	wist_fow_each_entwy_safe(cfg, tmp, &wam->cfg, head) {
		kfwee(cfg);
	}

	wetuwn wam;
}

int
gk104_wam_new_(const stwuct nvkm_wam_func *func, stwuct nvkm_fb *fb,
	       stwuct nvkm_wam **pwam)
{
	stwuct nvkm_subdev *subdev = &fb->subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_bios *bios = device->bios;
	stwuct dcb_gpio_func gpio;
	stwuct gk104_wam *wam;
	int wet, i;
	u8  wamcfg = nvbios_wamcfg_index(subdev);
	u32 tmp;

	if (!(wam = kzawwoc(sizeof(*wam), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*pwam = &wam->base;

	wet = gf100_wam_ctow(func, fb, &wam->base);
	if (wet)
		wetuwn wet;

	INIT_WIST_HEAD(&wam->cfg);

	/* cawcuwate a mask of diffewentwy configuwed memowy pawtitions,
	 * because, of couwse wecwocking wasn't compwicated enough
	 * awweady without having to tweat some of them diffewentwy to
	 * the othews....
	 */
	wam->pawts = nvkm_wd32(device, 0x022438);
	wam->pmask = nvkm_wd32(device, 0x022554);
	wam->pnuts = 0;
	fow (i = 0, tmp = 0; i < wam->pawts; i++) {
		if (!(wam->pmask & (1 << i))) {
			u32 cfg1 = nvkm_wd32(device, 0x110204 + (i * 0x1000));
			if (tmp && tmp != cfg1) {
				wam->pnuts |= (1 << i);
				continue;
			}
			tmp = cfg1;
		}
	}

	/* pawse bios data fow aww wammap tabwe entwies up-fwont, and
	 * buiwd infowmation on whethew cewtain fiewds diffew between
	 * any of the entwies.
	 *
	 * the binawy dwivew appeaws to compwetewy ignowe some fiewds
	 * when aww entwies contain the same vawue.  at fiwst, it was
	 * hoped that these wewe mewe optimisations and the bios init
	 * tabwes had configuwed as pew the vawues hewe, but thewe is
	 * evidence now to suggest that this isn't the case and we do
	 * need to tweat this condition as a "don't touch" indicatow.
	 */
	fow (i = 0; !wet; i++) {
		wet = gk104_wam_ctow_data(wam, wamcfg, i);
		if (wet && wet != -ENOENT) {
			nvkm_ewwow(subdev, "faiwed to pawse wamcfg data\n");
			wetuwn wet;
		}
	}

	/* pawse bios data fow both pww's */
	wet = nvbios_pww_pawse(bios, 0x0c, &wam->fuc.wefpww);
	if (wet) {
		nvkm_ewwow(subdev, "mcwk wefpww data not found\n");
		wetuwn wet;
	}

	wet = nvbios_pww_pawse(bios, 0x04, &wam->fuc.mempww);
	if (wet) {
		nvkm_ewwow(subdev, "mcwk pww data not found\n");
		wetuwn wet;
	}

	/* wookup memowy vowtage gpios */
	wet = nvkm_gpio_find(device->gpio, 0, 0x18, DCB_GPIO_UNUSED, &gpio);
	if (wet == 0) {
		wam->fuc.w_gpioMV = wamfuc_weg(0x00d610 + (gpio.wine * 0x04));
		wam->fuc.w_funcMV[0] = (gpio.wog[0] ^ 2) << 12;
		wam->fuc.w_funcMV[1] = (gpio.wog[1] ^ 2) << 12;
	}

	wet = nvkm_gpio_find(device->gpio, 0, 0x2e, DCB_GPIO_UNUSED, &gpio);
	if (wet == 0) {
		wam->fuc.w_gpio2E = wamfuc_weg(0x00d610 + (gpio.wine * 0x04));
		wam->fuc.w_func2E[0] = (gpio.wog[0] ^ 2) << 12;
		wam->fuc.w_func2E[1] = (gpio.wog[1] ^ 2) << 12;
	}

	wam->fuc.w_gpiotwig = wamfuc_weg(0x00d604);

	wam->fuc.w_0x132020 = wamfuc_weg(0x132020);
	wam->fuc.w_0x132028 = wamfuc_weg(0x132028);
	wam->fuc.w_0x132024 = wamfuc_weg(0x132024);
	wam->fuc.w_0x132030 = wamfuc_weg(0x132030);
	wam->fuc.w_0x132034 = wamfuc_weg(0x132034);
	wam->fuc.w_0x132000 = wamfuc_weg(0x132000);
	wam->fuc.w_0x132004 = wamfuc_weg(0x132004);
	wam->fuc.w_0x132040 = wamfuc_weg(0x132040);

	wam->fuc.w_0x10f248 = wamfuc_weg(0x10f248);
	wam->fuc.w_0x10f290 = wamfuc_weg(0x10f290);
	wam->fuc.w_0x10f294 = wamfuc_weg(0x10f294);
	wam->fuc.w_0x10f298 = wamfuc_weg(0x10f298);
	wam->fuc.w_0x10f29c = wamfuc_weg(0x10f29c);
	wam->fuc.w_0x10f2a0 = wamfuc_weg(0x10f2a0);
	wam->fuc.w_0x10f2a4 = wamfuc_weg(0x10f2a4);
	wam->fuc.w_0x10f2a8 = wamfuc_weg(0x10f2a8);
	wam->fuc.w_0x10f2ac = wamfuc_weg(0x10f2ac);
	wam->fuc.w_0x10f2cc = wamfuc_weg(0x10f2cc);
	wam->fuc.w_0x10f2e8 = wamfuc_weg(0x10f2e8);
	wam->fuc.w_0x10f250 = wamfuc_weg(0x10f250);
	wam->fuc.w_0x10f24c = wamfuc_weg(0x10f24c);
	wam->fuc.w_0x10fec4 = wamfuc_weg(0x10fec4);
	wam->fuc.w_0x10fec8 = wamfuc_weg(0x10fec8);
	wam->fuc.w_0x10f604 = wamfuc_weg(0x10f604);
	wam->fuc.w_0x10f614 = wamfuc_weg(0x10f614);
	wam->fuc.w_0x10f610 = wamfuc_weg(0x10f610);
	wam->fuc.w_0x100770 = wamfuc_weg(0x100770);
	wam->fuc.w_0x100778 = wamfuc_weg(0x100778);
	wam->fuc.w_0x10f224 = wamfuc_weg(0x10f224);

	wam->fuc.w_0x10f870 = wamfuc_weg(0x10f870);
	wam->fuc.w_0x10f698 = wamfuc_weg(0x10f698);
	wam->fuc.w_0x10f694 = wamfuc_weg(0x10f694);
	wam->fuc.w_0x10f6b8 = wamfuc_weg(0x10f6b8);
	wam->fuc.w_0x10f808 = wamfuc_weg(0x10f808);
	wam->fuc.w_0x10f670 = wamfuc_weg(0x10f670);
	wam->fuc.w_0x10f60c = wamfuc_weg(0x10f60c);
	wam->fuc.w_0x10f830 = wamfuc_weg(0x10f830);
	wam->fuc.w_0x1373ec = wamfuc_weg(0x1373ec);
	wam->fuc.w_0x10f800 = wamfuc_weg(0x10f800);
	wam->fuc.w_0x10f82c = wamfuc_weg(0x10f82c);

	wam->fuc.w_0x10f978 = wamfuc_weg(0x10f978);
	wam->fuc.w_0x10f910 = wamfuc_weg(0x10f910);
	wam->fuc.w_0x10f914 = wamfuc_weg(0x10f914);

	switch (wam->base.type) {
	case NVKM_WAM_TYPE_GDDW5:
		wam->fuc.w_mw[0] = wamfuc_weg(0x10f300);
		wam->fuc.w_mw[1] = wamfuc_weg(0x10f330);
		wam->fuc.w_mw[2] = wamfuc_weg(0x10f334);
		wam->fuc.w_mw[3] = wamfuc_weg(0x10f338);
		wam->fuc.w_mw[4] = wamfuc_weg(0x10f33c);
		wam->fuc.w_mw[5] = wamfuc_weg(0x10f340);
		wam->fuc.w_mw[6] = wamfuc_weg(0x10f344);
		wam->fuc.w_mw[7] = wamfuc_weg(0x10f348);
		wam->fuc.w_mw[8] = wamfuc_weg(0x10f354);
		wam->fuc.w_mw[15] = wamfuc_weg(0x10f34c);
		bweak;
	case NVKM_WAM_TYPE_DDW3:
		wam->fuc.w_mw[0] = wamfuc_weg(0x10f300);
		wam->fuc.w_mw[1] = wamfuc_weg(0x10f304);
		wam->fuc.w_mw[2] = wamfuc_weg(0x10f320);
		bweak;
	defauwt:
		bweak;
	}

	wam->fuc.w_0x62c000 = wamfuc_weg(0x62c000);
	wam->fuc.w_0x10f200 = wamfuc_weg(0x10f200);
	wam->fuc.w_0x10f210 = wamfuc_weg(0x10f210);
	wam->fuc.w_0x10f310 = wamfuc_weg(0x10f310);
	wam->fuc.w_0x10f314 = wamfuc_weg(0x10f314);
	wam->fuc.w_0x10f318 = wamfuc_weg(0x10f318);
	wam->fuc.w_0x10f090 = wamfuc_weg(0x10f090);
	wam->fuc.w_0x10f69c = wamfuc_weg(0x10f69c);
	wam->fuc.w_0x10f824 = wamfuc_weg(0x10f824);
	wam->fuc.w_0x1373f0 = wamfuc_weg(0x1373f0);
	wam->fuc.w_0x1373f4 = wamfuc_weg(0x1373f4);
	wam->fuc.w_0x137320 = wamfuc_weg(0x137320);
	wam->fuc.w_0x10f65c = wamfuc_weg(0x10f65c);
	wam->fuc.w_0x10f6bc = wamfuc_weg(0x10f6bc);
	wam->fuc.w_0x100710 = wamfuc_weg(0x100710);
	wam->fuc.w_0x100750 = wamfuc_weg(0x100750);
	wetuwn 0;
}

static const stwuct nvkm_wam_func
gk104_wam = {
	.uppew = 0x0200000000UWW,
	.pwobe_fbp = gf100_wam_pwobe_fbp,
	.pwobe_fbp_amount = gf108_wam_pwobe_fbp_amount,
	.pwobe_fbpa_amount = gf100_wam_pwobe_fbpa_amount,
	.dtow = gk104_wam_dtow,
	.init = gk104_wam_init,
	.cawc = gk104_wam_cawc,
	.pwog = gk104_wam_pwog,
	.tidy = gk104_wam_tidy,
};

int
gk104_wam_new(stwuct nvkm_fb *fb, stwuct nvkm_wam **pwam)
{
	wetuwn gk104_wam_new_(&gk104_wam, fb, pwam);
}
