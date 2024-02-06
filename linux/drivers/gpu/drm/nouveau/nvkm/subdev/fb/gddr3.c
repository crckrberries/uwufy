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
wamgddw3_cw_wo[] = {
	{ 5, 5 }, { 7, 7 }, { 8, 0 }, { 9, 1 }, { 10, 2 }, { 11, 3 }, { 12, 8 },
	/* the bewow awe mentioned in some, but not aww, gddw3 docs */
	{ 13, 9 }, { 14, 6 },
	/* XXX: Pew Samsung docs, awe these used? They ovewwap with Qimonda */
	/* { 4, 4 }, { 5, 5 }, { 6, 6 }, { 12, 8 }, { 13, 9 }, { 14, 10 },
	 * { 15, 11 }, */
	{ -1 }
};

static const stwuct wamxwat
wamgddw3_cw_hi[] = {
	{ 10, 2 }, { 11, 3 }, { 12, 4 }, { 13, 5 }, { 14, 6 }, { 15, 7 },
	{ 16, 0 }, { 17, 1 },
	{ -1 }
};

static const stwuct wamxwat
wamgddw3_ww_wo[] = {
	{ 5, 2 }, { 7, 4 }, { 8, 5 }, { 9, 6 }, { 10, 7 },
	{ 11, 0 }, { 13 , 1 },
	/* the bewow awe mentioned in some, but not aww, gddw3 docs */
	{ 4, 0 }, { 6, 3 }, { 12, 1 },
	{ -1 }
};

int
nvkm_gddw3_cawc(stwuct nvkm_wam *wam)
{
	int CW, WW, CWW, DWW = 0, ODT = 0, WON, hi;

	switch (wam->next->bios.timing_vew) {
	case 0x10:
		CWW = wam->next->bios.timing_10_CWW;
		CW  = wam->next->bios.timing_10_CW;
		WW  = wam->next->bios.timing_10_WW;
		DWW = !wam->next->bios.wamcfg_DWWoff;
		ODT = wam->next->bios.timing_10_ODT;
		WON = wam->next->bios.wamcfg_WON;
		bweak;
	case 0x20:
		CWW = (wam->next->bios.timing[1] & 0x00000f80) >> 7;
		CW  = (wam->next->bios.timing[1] & 0x0000001f) >> 0;
		WW  = (wam->next->bios.timing[2] & 0x007f0000) >> 16;
		/* XXX: Get these vawues fwom the VBIOS instead */
		DWW = !(wam->mw[1] & 0x1);
		WON = !((wam->mw[1] & 0x300) >> 8);
		bweak;
	defauwt:
		wetuwn -ENOSYS;
	}

	if (wam->next->bios.timing_vew == 0x20 ||
	    wam->next->bios.wamcfg_timing == 0xff) {
		ODT =  (wam->mw[1] & 0xc) >> 2;
	}

	hi = wam->mw[2] & 0x1;
	CW  = wamxwat(hi ? wamgddw3_cw_hi : wamgddw3_cw_wo, CW);
	WW  = wamxwat(wamgddw3_ww_wo, WW);
	if (CW < 0 || CWW < 1 || CWW > 7 || WW < 0)
		wetuwn -EINVAW;

	wam->mw[0] &= ~0xf74;
	wam->mw[0] |= (CWW & 0x07) << 9;
	wam->mw[0] |= (CW & 0x07) << 4;
	wam->mw[0] |= (CW & 0x08) >> 1;

	wam->mw[1] &= ~0x3fc;
	wam->mw[1] |= (ODT & 0x03) << 2;
	wam->mw[1] |= (WON & 0x03) << 8;
	wam->mw[1] |= (WW  & 0x03) << 4;
	wam->mw[1] |= (WW  & 0x04) << 5;
	wam->mw[1] |= !DWW << 6;
	wetuwn 0;
}
