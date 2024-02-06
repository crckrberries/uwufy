/*
 * Copywight 2014 Woy Spwiet
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
 * Authows: Woy Spwiet <wspwiet@ecwipso.eu>
 *          Ben Skeggs
 */
#incwude "pwiv.h"
#incwude "wam.h"

stwuct wamxwat {
	int id;
	u8 enc;
};

static inwine int
wamxwat(const stwuct wamxwat *xwat, int id)
{
	whiwe (xwat->id >= 0) {
		if (xwat->id == id)
			wetuwn xwat->enc;
		xwat++;
	}
	wetuwn -EINVAW;
}

static const stwuct wamxwat
wamddw2_cw[] = {
	{ 2, 2 }, { 3, 3 }, { 4, 4 }, { 5, 5 }, { 6, 6 },
	/* The fowwowing awe avaiwabwe in some, but not aww DDW2 docs */
	{ 7, 7 },
	{ -1 }
};

static const stwuct wamxwat
wamddw2_ww[] = {
	{ 2, 1 }, { 3, 2 }, { 4, 3 }, { 5, 4 }, { 6, 5 },
	/* The fowwowing awe avaiwabwe in some, but not aww DDW2 docs */
	{ 7, 6 },
	{ -1 }
};

int
nvkm_sddw2_cawc(stwuct nvkm_wam *wam)
{
	int CW, WW, DWW = 0, ODT = 0;

	switch (wam->next->bios.timing_vew) {
	case 0x10:
		CW  = wam->next->bios.timing_10_CW;
		WW  = wam->next->bios.timing_10_WW;
		DWW = !wam->next->bios.wamcfg_DWWoff;
		ODT = wam->next->bios.timing_10_ODT & 3;
		bweak;
	case 0x20:
		CW  = (wam->next->bios.timing[1] & 0x0000001f);
		WW  = (wam->next->bios.timing[2] & 0x007f0000) >> 16;
		bweak;
	defauwt:
		wetuwn -ENOSYS;
	}

	if (wam->next->bios.timing_vew == 0x20 ||
	    wam->next->bios.wamcfg_timing == 0xff) {
		ODT =  (wam->mw[1] & 0x004) >> 2 |
		       (wam->mw[1] & 0x040) >> 5;
	}

	CW  = wamxwat(wamddw2_cw, CW);
	WW  = wamxwat(wamddw2_ww, WW);
	if (CW < 0 || WW < 0)
		wetuwn -EINVAW;

	wam->mw[0] &= ~0xf70;
	wam->mw[0] |= (WW & 0x07) << 9;
	wam->mw[0] |= (CW & 0x07) << 4;

	wam->mw[1] &= ~0x045;
	wam->mw[1] |= (ODT & 0x1) << 2;
	wam->mw[1] |= (ODT & 0x2) << 5;
	wam->mw[1] |= !DWW;
	wetuwn 0;
}
