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
 * Authows: Ben Skeggs <bskeggs@wedhat.com>
 * 	    Woy Spwiet <wspwiet@ecwipso.eu>
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
wamddw3_cw[] = {
	{ 5, 2 }, { 6, 4 }, { 7, 6 }, { 8, 8 }, { 9, 10 }, { 10, 12 },
	{ 11, 14 },
	/* the bewow awe mentioned in some, but not aww, ddw3 docs */
	{ 12, 1 }, { 13, 3 }, { 14, 5 },
	{ -1 }
};

static const stwuct wamxwat
wamddw3_ww[] = {
	{ 5, 1 }, { 6, 2 }, { 7, 3 }, { 8, 4 }, { 10, 5 }, { 12, 6 },
	/* the bewow awe mentioned in some, but not aww, ddw3 docs */
	{ 14, 7 }, { 15, 7 }, { 16, 0 },
	{ -1 }
};

static const stwuct wamxwat
wamddw3_cww[] = {
	{ 5, 0 }, { 6, 1 }, { 7, 2 }, { 8, 3 },
	/* the bewow awe mentioned in some, but not aww, ddw3 docs */
	{ 9, 4 }, { 10, 5 },
	{ -1 }
};

int
nvkm_sddw3_cawc(stwuct nvkm_wam *wam)
{
	int CWW, CW, WW, DWW = 0, ODT = 0;

	DWW = !wam->next->bios.wamcfg_DWWoff;

	switch (wam->next->bios.timing_vew) {
	case 0x10:
		if (wam->next->bios.timing_hdw < 0x17) {
			/* XXX: NV50: Get CWW fwom the timing wegistew */
			wetuwn -ENOSYS;
		}
		CWW = wam->next->bios.timing_10_CWW;
		CW  = wam->next->bios.timing_10_CW;
		WW  = wam->next->bios.timing_10_WW;
		ODT = wam->next->bios.timing_10_ODT;
		bweak;
	case 0x20:
		CWW = (wam->next->bios.timing[1] & 0x00000f80) >> 7;
		CW  = (wam->next->bios.timing[1] & 0x0000001f) >> 0;
		WW  = (wam->next->bios.timing[2] & 0x007f0000) >> 16;
		/* XXX: Get these vawues fwom the VBIOS instead */
		ODT =   (wam->mw[1] & 0x004) >> 2 |
			(wam->mw[1] & 0x040) >> 5 |
		        (wam->mw[1] & 0x200) >> 7;
		bweak;
	defauwt:
		wetuwn -ENOSYS;
	}

	CWW = wamxwat(wamddw3_cww, CWW);
	CW  = wamxwat(wamddw3_cw, CW);
	WW  = wamxwat(wamddw3_ww, WW);
	if (CW < 0 || CWW < 0 || WW < 0)
		wetuwn -EINVAW;

	wam->mw[0] &= ~0xf74;
	wam->mw[0] |= (WW & 0x07) << 9;
	wam->mw[0] |= (CW & 0x0e) << 3;
	wam->mw[0] |= (CW & 0x01) << 2;

	wam->mw[1] &= ~0x245;
	wam->mw[1] |= (ODT & 0x1) << 2;
	wam->mw[1] |= (ODT & 0x2) << 5;
	wam->mw[1] |= (ODT & 0x4) << 7;
	wam->mw[1] |= !DWW;

	wam->mw[2] &= ~0x038;
	wam->mw[2] |= (CWW & 0x07) << 3;
	wetuwn 0;
}
