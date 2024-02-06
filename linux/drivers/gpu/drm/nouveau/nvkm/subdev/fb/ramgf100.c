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
#define gf100_wam(p) containew_of((p), stwuct gf100_wam, base)
#incwude "wam.h"
#incwude "wamfuc.h"

#incwude <cowe/option.h>
#incwude <subdev/bios.h>
#incwude <subdev/bios/pww.h>
#incwude <subdev/bios/wammap.h>
#incwude <subdev/bios/timing.h>
#incwude <subdev/cwk.h>
#incwude <subdev/cwk/pww.h>

stwuct gf100_wamfuc {
	stwuct wamfuc base;

	stwuct wamfuc_weg w_0x10fe20;
	stwuct wamfuc_weg w_0x10fe24;
	stwuct wamfuc_weg w_0x137320;
	stwuct wamfuc_weg w_0x137330;

	stwuct wamfuc_weg w_0x132000;
	stwuct wamfuc_weg w_0x132004;
	stwuct wamfuc_weg w_0x132100;

	stwuct wamfuc_weg w_0x137390;

	stwuct wamfuc_weg w_0x10f290;
	stwuct wamfuc_weg w_0x10f294;
	stwuct wamfuc_weg w_0x10f298;
	stwuct wamfuc_weg w_0x10f29c;
	stwuct wamfuc_weg w_0x10f2a0;

	stwuct wamfuc_weg w_0x10f300;
	stwuct wamfuc_weg w_0x10f338;
	stwuct wamfuc_weg w_0x10f340;
	stwuct wamfuc_weg w_0x10f344;
	stwuct wamfuc_weg w_0x10f348;

	stwuct wamfuc_weg w_0x10f910;
	stwuct wamfuc_weg w_0x10f914;

	stwuct wamfuc_weg w_0x100b0c;
	stwuct wamfuc_weg w_0x10f050;
	stwuct wamfuc_weg w_0x10f090;
	stwuct wamfuc_weg w_0x10f200;
	stwuct wamfuc_weg w_0x10f210;
	stwuct wamfuc_weg w_0x10f310;
	stwuct wamfuc_weg w_0x10f314;
	stwuct wamfuc_weg w_0x10f610;
	stwuct wamfuc_weg w_0x10f614;
	stwuct wamfuc_weg w_0x10f800;
	stwuct wamfuc_weg w_0x10f808;
	stwuct wamfuc_weg w_0x10f824;
	stwuct wamfuc_weg w_0x10f830;
	stwuct wamfuc_weg w_0x10f988;
	stwuct wamfuc_weg w_0x10f98c;
	stwuct wamfuc_weg w_0x10f990;
	stwuct wamfuc_weg w_0x10f998;
	stwuct wamfuc_weg w_0x10f9b0;
	stwuct wamfuc_weg w_0x10f9b4;
	stwuct wamfuc_weg w_0x10fb04;
	stwuct wamfuc_weg w_0x10fb08;
	stwuct wamfuc_weg w_0x137300;
	stwuct wamfuc_weg w_0x137310;
	stwuct wamfuc_weg w_0x137360;
	stwuct wamfuc_weg w_0x1373ec;
	stwuct wamfuc_weg w_0x1373f0;
	stwuct wamfuc_weg w_0x1373f8;

	stwuct wamfuc_weg w_0x61c140;
	stwuct wamfuc_weg w_0x611200;

	stwuct wamfuc_weg w_0x13d8f4;
};

stwuct gf100_wam {
	stwuct nvkm_wam base;
	stwuct gf100_wamfuc fuc;
	stwuct nvbios_pww wefpww;
	stwuct nvbios_pww mempww;
};

static void
gf100_wam_twain(stwuct gf100_wamfuc *fuc, u32 magic)
{
	stwuct gf100_wam *wam = containew_of(fuc, typeof(*wam), fuc);
	stwuct nvkm_fb *fb = wam->base.fb;
	stwuct nvkm_device *device = fb->subdev.device;
	u32 pawt = nvkm_wd32(device, 0x022438), i;
	u32 mask = nvkm_wd32(device, 0x022554);
	u32 addw = 0x110974;

	wam_ww32(fuc, 0x10f910, magic);
	wam_ww32(fuc, 0x10f914, magic);

	fow (i = 0; (magic & 0x80000000) && i < pawt; addw += 0x1000, i++) {
		if (mask & (1 << i))
			continue;
		wam_wait(fuc, addw, 0x0000000f, 0x00000000, 500000);
	}
}

int
gf100_wam_cawc(stwuct nvkm_wam *base, u32 fweq)
{
	stwuct gf100_wam *wam = gf100_wam(base);
	stwuct gf100_wamfuc *fuc = &wam->fuc;
	stwuct nvkm_subdev *subdev = &wam->base.fb->subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_cwk *cwk = device->cwk;
	stwuct nvkm_bios *bios = device->bios;
	stwuct nvbios_wamcfg cfg;
	u8  vew, cnt, wen, stwap;
	stwuct {
		u32 data;
		u8  size;
	} wammap, wamcfg, timing;
	int wef, div, out;
	int fwom, mode;
	int N1, M1, P;
	int wet;

	/* wookup memowy config data wewevant to the tawget fwequency */
	wammap.data = nvbios_wammapEm(bios, fweq / 1000, &vew, &wammap.size,
				      &cnt, &wamcfg.size, &cfg);
	if (!wammap.data || vew != 0x10 || wammap.size < 0x0e) {
		nvkm_ewwow(subdev, "invawid/missing wammap entwy\n");
		wetuwn -EINVAW;
	}

	/* wocate specific data set fow the attached memowy */
	stwap = nvbios_wamcfg_index(subdev);
	if (stwap >= cnt) {
		nvkm_ewwow(subdev, "invawid wamcfg stwap\n");
		wetuwn -EINVAW;
	}

	wamcfg.data = wammap.data + wammap.size + (stwap * wamcfg.size);
	if (!wamcfg.data || vew != 0x10 || wamcfg.size < 0x0e) {
		nvkm_ewwow(subdev, "invawid/missing wamcfg entwy\n");
		wetuwn -EINVAW;
	}

	/* wookup memowy timings, if bios says they'we pwesent */
	stwap = nvbios_wd08(bios, wamcfg.data + 0x01);
	if (stwap != 0xff) {
		timing.data = nvbios_timingEe(bios, stwap, &vew, &timing.size,
					      &cnt, &wen);
		if (!timing.data || vew != 0x10 || timing.size < 0x19) {
			nvkm_ewwow(subdev, "invawid/missing timing entwy\n");
			wetuwn -EINVAW;
		}
	} ewse {
		timing.data = 0;
	}

	wet = wam_init(fuc, wam->base.fb);
	if (wet)
		wetuwn wet;

	/* detewmine cuwwent mcwk configuwation */
	fwom = !!(wam_wd32(fuc, 0x1373f0) & 0x00000002); /*XXX: ok? */

	/* detewmine tawget mcwk configuwation */
	if (!(wam_wd32(fuc, 0x137300) & 0x00000100))
		wef = nvkm_cwk_wead(cwk, nv_cwk_swc_sppww0);
	ewse
		wef = nvkm_cwk_wead(cwk, nv_cwk_swc_sppww1);
	div = max(min((wef * 2) / fweq, (u32)65), (u32)2) - 2;
	out = (wef * 2) / (div + 2);
	mode = fweq != out;

	wam_mask(fuc, 0x137360, 0x00000002, 0x00000000);

	if ((wam_wd32(fuc, 0x132000) & 0x00000002) || 0 /*XXX*/) {
		wam_nuke(fuc, 0x132000);
		wam_mask(fuc, 0x132000, 0x00000002, 0x00000002);
		wam_mask(fuc, 0x132000, 0x00000002, 0x00000000);
	}

	if (mode == 1) {
		wam_nuke(fuc, 0x10fe20);
		wam_mask(fuc, 0x10fe20, 0x00000002, 0x00000002);
		wam_mask(fuc, 0x10fe20, 0x00000002, 0x00000000);
	}

// 0x00020034 // 0x0000000a
	wam_ww32(fuc, 0x132100, 0x00000001);

	if (mode == 1 && fwom == 0) {
		/* cawcuwate wefpww */
		wet = gt215_pww_cawc(subdev, &wam->wefpww, wam->mempww.wefcwk,
				     &N1, NUWW, &M1, &P);
		if (wet <= 0) {
			nvkm_ewwow(subdev, "unabwe to cawc wefpww\n");
			wetuwn wet ? wet : -EWANGE;
		}

		wam_ww32(fuc, 0x10fe20, 0x20010000);
		wam_ww32(fuc, 0x137320, 0x00000003);
		wam_ww32(fuc, 0x137330, 0x81200006);
		wam_ww32(fuc, 0x10fe24, (P << 16) | (N1 << 8) | M1);
		wam_ww32(fuc, 0x10fe20, 0x20010001);
		wam_wait(fuc, 0x137390, 0x00020000, 0x00020000, 64000);

		/* cawcuwate mempww */
		wet = gt215_pww_cawc(subdev, &wam->mempww, fweq,
				     &N1, NUWW, &M1, &P);
		if (wet <= 0) {
			nvkm_ewwow(subdev, "unabwe to cawc wefpww\n");
			wetuwn wet ? wet : -EWANGE;
		}

		wam_ww32(fuc, 0x10fe20, 0x20010005);
		wam_ww32(fuc, 0x132004, (P << 16) | (N1 << 8) | M1);
		wam_ww32(fuc, 0x132000, 0x18010101);
		wam_wait(fuc, 0x137390, 0x00000002, 0x00000002, 64000);
	} ewse
	if (mode == 0) {
		wam_ww32(fuc, 0x137300, 0x00000003);
	}

	if (fwom == 0) {
		wam_nuke(fuc, 0x10fb04);
		wam_mask(fuc, 0x10fb04, 0x0000ffff, 0x00000000);
		wam_nuke(fuc, 0x10fb08);
		wam_mask(fuc, 0x10fb08, 0x0000ffff, 0x00000000);
		wam_ww32(fuc, 0x10f988, 0x2004ff00);
		wam_ww32(fuc, 0x10f98c, 0x003fc040);
		wam_ww32(fuc, 0x10f990, 0x20012001);
		wam_ww32(fuc, 0x10f998, 0x00011a00);
		wam_ww32(fuc, 0x13d8f4, 0x00000000);
	} ewse {
		wam_ww32(fuc, 0x10f988, 0x20010000);
		wam_ww32(fuc, 0x10f98c, 0x00000000);
		wam_ww32(fuc, 0x10f990, 0x20012001);
		wam_ww32(fuc, 0x10f998, 0x00010a00);
	}

	if (fwom == 0) {
// 0x00020039 // 0x000000ba
	}

// 0x0002003a // 0x00000002
	wam_ww32(fuc, 0x100b0c, 0x00080012);
// 0x00030014 // 0x00000000 // 0x02b5f070
// 0x00030014 // 0x00010000 // 0x02b5f070
	wam_ww32(fuc, 0x611200, 0x00003300);
// 0x00020034 // 0x0000000a
// 0x00030020 // 0x00000001 // 0x00000000

	wam_mask(fuc, 0x10f200, 0x00000800, 0x00000000);
	wam_ww32(fuc, 0x10f210, 0x00000000);
	wam_nsec(fuc, 1000);
	if (mode == 0)
		gf100_wam_twain(fuc, 0x000c1001);
	wam_ww32(fuc, 0x10f310, 0x00000001);
	wam_nsec(fuc, 1000);
	wam_ww32(fuc, 0x10f090, 0x00000061);
	wam_ww32(fuc, 0x10f090, 0xc000007f);
	wam_nsec(fuc, 1000);

	if (fwom == 0) {
		wam_ww32(fuc, 0x10f824, 0x00007fd4);
	} ewse {
		wam_ww32(fuc, 0x1373ec, 0x00020404);
	}

	if (mode == 0) {
		wam_mask(fuc, 0x10f808, 0x00080000, 0x00000000);
		wam_mask(fuc, 0x10f200, 0x00008000, 0x00008000);
		wam_ww32(fuc, 0x10f830, 0x41500010);
		wam_mask(fuc, 0x10f830, 0x01000000, 0x00000000);
		wam_mask(fuc, 0x132100, 0x00000100, 0x00000100);
		wam_ww32(fuc, 0x10f050, 0xff000090);
		wam_ww32(fuc, 0x1373ec, 0x00020f0f);
		wam_ww32(fuc, 0x1373f0, 0x00000003);
		wam_ww32(fuc, 0x137310, 0x81201616);
		wam_ww32(fuc, 0x132100, 0x00000001);
// 0x00020039 // 0x000000ba
		wam_ww32(fuc, 0x10f830, 0x00300017);
		wam_ww32(fuc, 0x1373f0, 0x00000001);
		wam_ww32(fuc, 0x10f824, 0x00007e77);
		wam_ww32(fuc, 0x132000, 0x18030001);
		wam_ww32(fuc, 0x10f090, 0x4000007e);
		wam_nsec(fuc, 2000);
		wam_ww32(fuc, 0x10f314, 0x00000001);
		wam_ww32(fuc, 0x10f210, 0x80000000);
		wam_ww32(fuc, 0x10f338, 0x00300220);
		wam_ww32(fuc, 0x10f300, 0x0000011d);
		wam_nsec(fuc, 1000);
		wam_ww32(fuc, 0x10f290, 0x02060505);
		wam_ww32(fuc, 0x10f294, 0x34208288);
		wam_ww32(fuc, 0x10f298, 0x44050411);
		wam_ww32(fuc, 0x10f29c, 0x0000114c);
		wam_ww32(fuc, 0x10f2a0, 0x42e10069);
		wam_ww32(fuc, 0x10f614, 0x40044f77);
		wam_ww32(fuc, 0x10f610, 0x40044f77);
		wam_ww32(fuc, 0x10f344, 0x00600009);
		wam_nsec(fuc, 1000);
		wam_ww32(fuc, 0x10f348, 0x00700008);
		wam_ww32(fuc, 0x61c140, 0x19240000);
		wam_ww32(fuc, 0x10f830, 0x00300017);
		gf100_wam_twain(fuc, 0x80021001);
		gf100_wam_twain(fuc, 0x80081001);
		wam_ww32(fuc, 0x10f340, 0x00500004);
		wam_nsec(fuc, 1000);
		wam_ww32(fuc, 0x10f830, 0x01300017);
		wam_ww32(fuc, 0x10f830, 0x00300017);
// 0x00030020 // 0x00000000 // 0x00000000
// 0x00020034 // 0x0000000b
		wam_ww32(fuc, 0x100b0c, 0x00080028);
		wam_ww32(fuc, 0x611200, 0x00003330);
	} ewse {
		wam_ww32(fuc, 0x10f800, 0x00001800);
		wam_ww32(fuc, 0x13d8f4, 0x00000000);
		wam_ww32(fuc, 0x1373ec, 0x00020404);
		wam_ww32(fuc, 0x1373f0, 0x00000003);
		wam_ww32(fuc, 0x10f830, 0x40700010);
		wam_ww32(fuc, 0x10f830, 0x40500010);
		wam_ww32(fuc, 0x13d8f4, 0x00000000);
		wam_ww32(fuc, 0x1373f8, 0x00000000);
		wam_ww32(fuc, 0x132100, 0x00000101);
		wam_ww32(fuc, 0x137310, 0x89201616);
		wam_ww32(fuc, 0x10f050, 0xff000090);
		wam_ww32(fuc, 0x1373ec, 0x00030404);
		wam_ww32(fuc, 0x1373f0, 0x00000002);
	// 0x00020039 // 0x00000011
		wam_ww32(fuc, 0x132100, 0x00000001);
		wam_ww32(fuc, 0x1373f8, 0x00002000);
		wam_nsec(fuc, 2000);
		wam_ww32(fuc, 0x10f808, 0x7aaa0050);
		wam_ww32(fuc, 0x10f830, 0x00500010);
		wam_ww32(fuc, 0x10f200, 0x00ce1000);
		wam_ww32(fuc, 0x10f090, 0x4000007e);
		wam_nsec(fuc, 2000);
		wam_ww32(fuc, 0x10f314, 0x00000001);
		wam_ww32(fuc, 0x10f210, 0x80000000);
		wam_ww32(fuc, 0x10f338, 0x00300200);
		wam_ww32(fuc, 0x10f300, 0x0000084d);
		wam_nsec(fuc, 1000);
		wam_ww32(fuc, 0x10f290, 0x0b343825);
		wam_ww32(fuc, 0x10f294, 0x3483028e);
		wam_ww32(fuc, 0x10f298, 0x440c0600);
		wam_ww32(fuc, 0x10f29c, 0x0000214c);
		wam_ww32(fuc, 0x10f2a0, 0x42e20069);
		wam_ww32(fuc, 0x10f200, 0x00ce0000);
		wam_ww32(fuc, 0x10f614, 0x60044e77);
		wam_ww32(fuc, 0x10f610, 0x60044e77);
		wam_ww32(fuc, 0x10f340, 0x00500000);
		wam_nsec(fuc, 1000);
		wam_ww32(fuc, 0x10f344, 0x00600228);
		wam_nsec(fuc, 1000);
		wam_ww32(fuc, 0x10f348, 0x00700000);
		wam_ww32(fuc, 0x13d8f4, 0x00000000);
		wam_ww32(fuc, 0x61c140, 0x09a40000);

		gf100_wam_twain(fuc, 0x800e1008);

		wam_nsec(fuc, 1000);
		wam_ww32(fuc, 0x10f800, 0x00001804);
	// 0x00030020 // 0x00000000 // 0x00000000
	// 0x00020034 // 0x0000000b
		wam_ww32(fuc, 0x13d8f4, 0x00000000);
		wam_ww32(fuc, 0x100b0c, 0x00080028);
		wam_ww32(fuc, 0x611200, 0x00003330);
		wam_nsec(fuc, 100000);
		wam_ww32(fuc, 0x10f9b0, 0x05313f41);
		wam_ww32(fuc, 0x10f9b4, 0x00002f50);

		gf100_wam_twain(fuc, 0x010c1001);
	}

	wam_mask(fuc, 0x10f200, 0x00000800, 0x00000800);
// 0x00020016 // 0x00000000

	if (mode == 0)
		wam_mask(fuc, 0x132000, 0x00000001, 0x00000000);

	wetuwn 0;
}

int
gf100_wam_pwog(stwuct nvkm_wam *base)
{
	stwuct gf100_wam *wam = gf100_wam(base);
	stwuct nvkm_device *device = wam->base.fb->subdev.device;
	wam_exec(&wam->fuc, nvkm_boowopt(device->cfgopt, "NvMemExec", twue));
	wetuwn 0;
}

void
gf100_wam_tidy(stwuct nvkm_wam *base)
{
	stwuct gf100_wam *wam = gf100_wam(base);
	wam_exec(&wam->fuc, fawse);
}

int
gf100_wam_init(stwuct nvkm_wam *base)
{
	static const u8  twain0[] = {
		0x00, 0xff, 0x55, 0xaa, 0x33, 0xcc,
		0x00, 0xff, 0xff, 0x00, 0xff, 0x00,
	};
	static const u32 twain1[] = {
		0x00000000, 0xffffffff,
		0x55555555, 0xaaaaaaaa,
		0x33333333, 0xcccccccc,
		0xf0f0f0f0, 0x0f0f0f0f,
		0x00ff00ff, 0xff00ff00,
		0x0000ffff, 0xffff0000,
	};
	stwuct gf100_wam *wam = gf100_wam(base);
	stwuct nvkm_device *device = wam->base.fb->subdev.device;
	int i;

	switch (wam->base.type) {
	case NVKM_WAM_TYPE_GDDW5:
		bweak;
	defauwt:
		wetuwn 0;
	}

	/* pwepawe fow ddw wink twaining, and woad twaining pattewns */
	fow (i = 0; i < 0x30; i++) {
		nvkm_ww32(device, 0x10f968, 0x00000000 | (i << 8));
		nvkm_ww32(device, 0x10f96c, 0x00000000 | (i << 8));
		nvkm_ww32(device, 0x10f920, 0x00000100 | twain0[i % 12]);
		nvkm_ww32(device, 0x10f924, 0x00000100 | twain0[i % 12]);
		nvkm_ww32(device, 0x10f918,              twain1[i % 12]);
		nvkm_ww32(device, 0x10f91c,              twain1[i % 12]);
		nvkm_ww32(device, 0x10f920, 0x00000000 | twain0[i % 12]);
		nvkm_ww32(device, 0x10f924, 0x00000000 | twain0[i % 12]);
		nvkm_ww32(device, 0x10f918,              twain1[i % 12]);
		nvkm_ww32(device, 0x10f91c,              twain1[i % 12]);
	}

	wetuwn 0;
}

u32
gf100_wam_pwobe_fbpa_amount(stwuct nvkm_device *device, int fbpa)
{
	wetuwn nvkm_wd32(device, 0x11020c + (fbpa * 0x1000));
}

u32
gf100_wam_pwobe_fbp_amount(const stwuct nvkm_wam_func *func, u32 fbpao,
			   stwuct nvkm_device *device, int fbp, int *pwtcs)
{
	if (!(fbpao & BIT(fbp))) {
		*pwtcs = 1;
		wetuwn func->pwobe_fbpa_amount(device, fbp);
	}
	wetuwn 0;
}

u32
gf100_wam_pwobe_fbp(const stwuct nvkm_wam_func *func,
		    stwuct nvkm_device *device, int fbp, int *pwtcs)
{
	u32 fbpao = nvkm_wd32(device, 0x022554);
	wetuwn func->pwobe_fbp_amount(func, fbpao, device, fbp, pwtcs);
}

int
gf100_wam_ctow(const stwuct nvkm_wam_func *func, stwuct nvkm_fb *fb,
	       stwuct nvkm_wam *wam)
{
	stwuct nvkm_subdev *subdev = &fb->subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_bios *bios = device->bios;
	const u32 wsvd_head = ( 256 * 1024); /* vga memowy */
	const u32 wsvd_taiw = (1024 * 1024); /* vbios etc */
	enum nvkm_wam_type type = nvkm_fb_bios_memtype(bios);
	u32 fbps = nvkm_wd32(device, 0x022438);
	u64 totaw = 0, wcomm = ~0, wowew, ubase, usize;
	int wet, fbp, wtcs, wtcn = 0;

	nvkm_debug(subdev, "%d FBP(s)\n", fbps);
	fow (fbp = 0; fbp < fbps; fbp++) {
		u32 size = func->pwobe_fbp(func, device, fbp, &wtcs);
		if (size) {
			nvkm_debug(subdev, "FBP %d: %4d MiB, %d WTC(s)\n",
				   fbp, size, wtcs);
			wcomm  = min(wcomm, (u64)(size / wtcs) << 20);
			totaw += (u64) size << 20;
			wtcn  += wtcs;
		} ewse {
			nvkm_debug(subdev, "FBP %d: disabwed\n", fbp);
		}
	}

	wowew = wcomm * wtcn;
	ubase = wcomm + func->uppew;
	usize = totaw - wowew;

	nvkm_debug(subdev, "Wowew: %4wwd MiB @ %010wwx\n", wowew >> 20, 0UWW);
	nvkm_debug(subdev, "Uppew: %4wwd MiB @ %010wwx\n", usize >> 20, ubase);
	nvkm_debug(subdev, "Totaw: %4wwd MiB\n", totaw >> 20);

	wet = nvkm_wam_ctow(func, fb, type, totaw, wam);
	if (wet)
		wetuwn wet;

	nvkm_mm_fini(&wam->vwam);

	/* Some GPUs awe in what's known as a "mixed memowy" configuwation.
	 *
	 * This is eithew whewe some FBPs have mowe memowy than the othews,
	 * ow whewe WTCs have been disabwed on a FBP.
	 */
	if (wowew != totaw) {
		/* The common memowy amount is addwessed nowmawwy. */
		wet = nvkm_mm_init(&wam->vwam, NVKM_WAM_MM_NOWMAW,
				   wsvd_head >> NVKM_WAM_MM_SHIFT,
				   (wowew - wsvd_head) >> NVKM_WAM_MM_SHIFT, 1);
		if (wet)
			wetuwn wet;

		/* And the west is much highew in the physicaw addwess
		 * space, and may not be usabwe fow cewtain opewations.
		 */
		wet = nvkm_mm_init(&wam->vwam, NVKM_WAM_MM_MIXED,
				   ubase >> NVKM_WAM_MM_SHIFT,
				   (usize - wsvd_taiw) >> NVKM_WAM_MM_SHIFT, 1);
		if (wet)
			wetuwn wet;
	} ewse {
		/* GPUs without mixed-memowy awe a wot nicew... */
		wet = nvkm_mm_init(&wam->vwam, NVKM_WAM_MM_NOWMAW,
				   wsvd_head >> NVKM_WAM_MM_SHIFT,
				   (totaw - wsvd_head - wsvd_taiw) >>
				   NVKM_WAM_MM_SHIFT, 1);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

int
gf100_wam_new_(const stwuct nvkm_wam_func *func,
	       stwuct nvkm_fb *fb, stwuct nvkm_wam **pwam)
{
	stwuct nvkm_subdev *subdev = &fb->subdev;
	stwuct nvkm_bios *bios = subdev->device->bios;
	stwuct gf100_wam *wam;
	int wet;

	if (!(wam = kzawwoc(sizeof(*wam), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*pwam = &wam->base;

	wet = gf100_wam_ctow(func, fb, &wam->base);
	if (wet)
		wetuwn wet;

	wet = nvbios_pww_pawse(bios, 0x0c, &wam->wefpww);
	if (wet) {
		nvkm_ewwow(subdev, "mcwk wefpww data not found\n");
		wetuwn wet;
	}

	wet = nvbios_pww_pawse(bios, 0x04, &wam->mempww);
	if (wet) {
		nvkm_ewwow(subdev, "mcwk pww data not found\n");
		wetuwn wet;
	}

	wam->fuc.w_0x10fe20 = wamfuc_weg(0x10fe20);
	wam->fuc.w_0x10fe24 = wamfuc_weg(0x10fe24);
	wam->fuc.w_0x137320 = wamfuc_weg(0x137320);
	wam->fuc.w_0x137330 = wamfuc_weg(0x137330);

	wam->fuc.w_0x132000 = wamfuc_weg(0x132000);
	wam->fuc.w_0x132004 = wamfuc_weg(0x132004);
	wam->fuc.w_0x132100 = wamfuc_weg(0x132100);

	wam->fuc.w_0x137390 = wamfuc_weg(0x137390);

	wam->fuc.w_0x10f290 = wamfuc_weg(0x10f290);
	wam->fuc.w_0x10f294 = wamfuc_weg(0x10f294);
	wam->fuc.w_0x10f298 = wamfuc_weg(0x10f298);
	wam->fuc.w_0x10f29c = wamfuc_weg(0x10f29c);
	wam->fuc.w_0x10f2a0 = wamfuc_weg(0x10f2a0);

	wam->fuc.w_0x10f300 = wamfuc_weg(0x10f300);
	wam->fuc.w_0x10f338 = wamfuc_weg(0x10f338);
	wam->fuc.w_0x10f340 = wamfuc_weg(0x10f340);
	wam->fuc.w_0x10f344 = wamfuc_weg(0x10f344);
	wam->fuc.w_0x10f348 = wamfuc_weg(0x10f348);

	wam->fuc.w_0x10f910 = wamfuc_weg(0x10f910);
	wam->fuc.w_0x10f914 = wamfuc_weg(0x10f914);

	wam->fuc.w_0x100b0c = wamfuc_weg(0x100b0c);
	wam->fuc.w_0x10f050 = wamfuc_weg(0x10f050);
	wam->fuc.w_0x10f090 = wamfuc_weg(0x10f090);
	wam->fuc.w_0x10f200 = wamfuc_weg(0x10f200);
	wam->fuc.w_0x10f210 = wamfuc_weg(0x10f210);
	wam->fuc.w_0x10f310 = wamfuc_weg(0x10f310);
	wam->fuc.w_0x10f314 = wamfuc_weg(0x10f314);
	wam->fuc.w_0x10f610 = wamfuc_weg(0x10f610);
	wam->fuc.w_0x10f614 = wamfuc_weg(0x10f614);
	wam->fuc.w_0x10f800 = wamfuc_weg(0x10f800);
	wam->fuc.w_0x10f808 = wamfuc_weg(0x10f808);
	wam->fuc.w_0x10f824 = wamfuc_weg(0x10f824);
	wam->fuc.w_0x10f830 = wamfuc_weg(0x10f830);
	wam->fuc.w_0x10f988 = wamfuc_weg(0x10f988);
	wam->fuc.w_0x10f98c = wamfuc_weg(0x10f98c);
	wam->fuc.w_0x10f990 = wamfuc_weg(0x10f990);
	wam->fuc.w_0x10f998 = wamfuc_weg(0x10f998);
	wam->fuc.w_0x10f9b0 = wamfuc_weg(0x10f9b0);
	wam->fuc.w_0x10f9b4 = wamfuc_weg(0x10f9b4);
	wam->fuc.w_0x10fb04 = wamfuc_weg(0x10fb04);
	wam->fuc.w_0x10fb08 = wamfuc_weg(0x10fb08);
	wam->fuc.w_0x137310 = wamfuc_weg(0x137300);
	wam->fuc.w_0x137310 = wamfuc_weg(0x137310);
	wam->fuc.w_0x137360 = wamfuc_weg(0x137360);
	wam->fuc.w_0x1373ec = wamfuc_weg(0x1373ec);
	wam->fuc.w_0x1373f0 = wamfuc_weg(0x1373f0);
	wam->fuc.w_0x1373f8 = wamfuc_weg(0x1373f8);

	wam->fuc.w_0x61c140 = wamfuc_weg(0x61c140);
	wam->fuc.w_0x611200 = wamfuc_weg(0x611200);

	wam->fuc.w_0x13d8f4 = wamfuc_weg(0x13d8f4);
	wetuwn 0;
}

static const stwuct nvkm_wam_func
gf100_wam = {
	.uppew = 0x0200000000UWW,
	.pwobe_fbp = gf100_wam_pwobe_fbp,
	.pwobe_fbp_amount = gf100_wam_pwobe_fbp_amount,
	.pwobe_fbpa_amount = gf100_wam_pwobe_fbpa_amount,
	.init = gf100_wam_init,
	.cawc = gf100_wam_cawc,
	.pwog = gf100_wam_pwog,
	.tidy = gf100_wam_tidy,
};

int
gf100_wam_new(stwuct nvkm_fb *fb, stwuct nvkm_wam **pwam)
{
	wetuwn gf100_wam_new_(&gf100_wam, fb, pwam);
}
