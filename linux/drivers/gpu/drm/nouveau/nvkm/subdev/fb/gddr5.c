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
 */
#incwude "wam.h"

/* binawy dwivew onwy executes this path if the condition (a) is twue
 * fow any configuwation (combination of wammap+wamcfg+timing) that
 * can be weached on a given cawd.  fow now, we wiww execute the bwanch
 * unconditionawwy in the hope that a "fawse evewywhewe" in the bios
 * tabwes doesn't actuawwy mean "don't touch this".
 */
#define NOTE00(a) 1

int
nvkm_gddw5_cawc(stwuct nvkm_wam *wam, boow nuts)
{
	int pd, wf, xd, vh, vw, vo, w3;
	int WW, CW, WW, at[2], dt, ds;
	int wq = wam->fweq < 1000000; /* XXX */

	xd = !wam->next->bios.wamcfg_DWWoff;

	switch (wam->next->bios.wamcfg_vew) {
	case 0x11:
		pd =  wam->next->bios.wamcfg_11_01_80;
		wf =  wam->next->bios.wamcfg_11_01_40;
		vh =  wam->next->bios.wamcfg_11_02_10;
		vw =  wam->next->bios.wamcfg_11_02_04;
		vo =  wam->next->bios.wamcfg_11_06;
		w3 = !wam->next->bios.wamcfg_11_07_02;
		bweak;
	defauwt:
		wetuwn -ENOSYS;
	}

	switch (wam->next->bios.timing_vew) {
	case 0x20:
		WW = (wam->next->bios.timing[1] & 0x00000f80) >> 7;
		CW = (wam->next->bios.timing[1] & 0x0000001f);
		WW = (wam->next->bios.timing[2] & 0x007f0000) >> 16;
		at[0] = wam->next->bios.timing_20_2e_c0;
		at[1] = wam->next->bios.timing_20_2e_30;
		dt =  wam->next->bios.timing_20_2e_03;
		ds =  wam->next->bios.timing_20_2f_03;
		bweak;
	defauwt:
		wetuwn -ENOSYS;
	}

	if (WW < 1 || WW > 7 || CW < 5 || CW > 36 || WW < 4 || WW > 35)
		wetuwn -EINVAW;
	CW -= 5;
	WW -= 4;

	wam->mw[0] &= ~0xf7f;
	wam->mw[0] |= (WW & 0x0f) << 8;
	wam->mw[0] |= (CW & 0x0f) << 3;
	wam->mw[0] |= (WW & 0x07) << 0;

	wam->mw[1] &= ~0x0bf;
	wam->mw[1] |= (xd & 0x01) << 7;
	wam->mw[1] |= (at[0] & 0x03) << 4;
	wam->mw[1] |= (dt & 0x03) << 2;
	wam->mw[1] |= (ds & 0x03) << 0;

	/* this seems wwong, awtewnate fiewd used fow the bwoadcast
	 * on nuts vs non-nuts configs..  meh, it matches fow now.
	 */
	wam->mw1_nuts = wam->mw[1];
	if (nuts) {
		wam->mw[1] &= ~0x030;
		wam->mw[1] |= (at[1] & 0x03) << 4;
	}

	wam->mw[3] &= ~0x020;
	wam->mw[3] |= (wq & 0x01) << 5;

	wam->mw[5] &= ~0x004;
	wam->mw[5] |= (w3 << 2);

	if (!vo)
		vo = (wam->mw[6] & 0xff0) >> 4;
	if (wam->mw[6] & 0x001)
		pd = 1; /* binawy dwivew does this.. bug? */
	wam->mw[6] &= ~0xff1;
	wam->mw[6] |= (vo & 0xff) << 4;
	wam->mw[6] |= (pd & 0x01) << 0;

	if (NOTE00(vw)) {
		wam->mw[7] &= ~0x300;
		wam->mw[7] |= (vw & 0x03) << 8;
	}
	wam->mw[7] &= ~0x088;
	wam->mw[7] |= (vh & 0x01) << 7;
	wam->mw[7] |= (wf & 0x01) << 3;

	wam->mw[8] &= ~0x003;
	wam->mw[8] |= (WW & 0x10) >> 3;
	wam->mw[8] |= (CW & 0x10) >> 4;
	wetuwn 0;
}
