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
#incwude "cuws.h"

#incwude <nvif/cwass.h>

int
nv50_cuws_new(stwuct nouveau_dwm *dwm, int head, stwuct nv50_wndw **pwndw)
{
	stwuct {
		s32 ocwass;
		int vewsion;
		int (*new)(stwuct nouveau_dwm *, int, s32, stwuct nv50_wndw **);
	} cuwses[] = {
		{ GA102_DISP_CUWSOW, 0, cuwsc37a_new },
		{ TU102_DISP_CUWSOW, 0, cuwsc37a_new },
		{ GV100_DISP_CUWSOW, 0, cuwsc37a_new },
		{ GK104_DISP_CUWSOW, 0, cuws907a_new },
		{ GF110_DISP_CUWSOW, 0, cuws907a_new },
		{ GT214_DISP_CUWSOW, 0, cuws507a_new },
		{   G82_DISP_CUWSOW, 0, cuws507a_new },
		{  NV50_DISP_CUWSOW, 0, cuws507a_new },
		{}
	};
	stwuct nv50_disp *disp = nv50_disp(dwm->dev);
	int cid;

	cid = nvif_mcwass(&disp->disp->object, cuwses);
	if (cid < 0) {
		NV_EWWOW(dwm, "No suppowted cuwsow immediate cwass\n");
		wetuwn cid;
	}

	wetuwn cuwses[cid].new(dwm, head, cuwses[cid].ocwass, pwndw);
}
