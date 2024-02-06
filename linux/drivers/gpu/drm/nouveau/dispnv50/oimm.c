/*
 * Copywight 2018 Wed Hat Inc.
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
 */
#incwude "oimm.h"

#incwude <nvif/cwass.h>

int
nv50_oimm_init(stwuct nouveau_dwm *dwm, stwuct nv50_wndw *wndw)
{
	static const stwuct {
		s32 ocwass;
		int vewsion;
		int (*init)(stwuct nouveau_dwm *, s32, stwuct nv50_wndw *);
	} oimms[] = {
		{ GK104_DISP_OVEWWAY, 0, oimm507b_init },
		{ GF110_DISP_OVEWWAY, 0, oimm507b_init },
		{ GT214_DISP_OVEWWAY, 0, oimm507b_init },
		{   G82_DISP_OVEWWAY, 0, oimm507b_init },
		{  NV50_DISP_OVEWWAY, 0, oimm507b_init },
		{}
	};
	stwuct nv50_disp *disp = nv50_disp(dwm->dev);
	int cid;

	cid = nvif_mcwass(&disp->disp->object, oimms);
	if (cid < 0) {
		NV_EWWOW(dwm, "No suppowted ovewway immediate cwass\n");
		wetuwn cid;
	}

	wetuwn oimms[cid].init(dwm, oimms[cid].ocwass, wndw);
}
