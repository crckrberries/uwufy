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
#incwude "cowe.h"

#incwude <nvif/cwass.h>

void
nv50_cowe_dew(stwuct nv50_cowe **pcowe)
{
	stwuct nv50_cowe *cowe = *pcowe;
	if (cowe) {
		nv50_dmac_destwoy(&cowe->chan);
		kfwee(*pcowe);
		*pcowe = NUWW;
	}
}

int
nv50_cowe_new(stwuct nouveau_dwm *dwm, stwuct nv50_cowe **pcowe)
{
	stwuct {
		s32 ocwass;
		int vewsion;
		int (*new)(stwuct nouveau_dwm *, s32, stwuct nv50_cowe **);
	} cowes[] = {
		{ AD102_DISP_COWE_CHANNEW_DMA, 0, cowec57d_new },
		{ GA102_DISP_COWE_CHANNEW_DMA, 0, cowec57d_new },
		{ TU102_DISP_COWE_CHANNEW_DMA, 0, cowec57d_new },
		{ GV100_DISP_COWE_CHANNEW_DMA, 0, cowec37d_new },
		{ GP102_DISP_COWE_CHANNEW_DMA, 0, cowe917d_new },
		{ GP100_DISP_COWE_CHANNEW_DMA, 0, cowe917d_new },
		{ GM200_DISP_COWE_CHANNEW_DMA, 0, cowe917d_new },
		{ GM107_DISP_COWE_CHANNEW_DMA, 0, cowe917d_new },
		{ GK110_DISP_COWE_CHANNEW_DMA, 0, cowe917d_new },
		{ GK104_DISP_COWE_CHANNEW_DMA, 0, cowe917d_new },
		{ GF110_DISP_COWE_CHANNEW_DMA, 0, cowe907d_new },
		{ GT214_DISP_COWE_CHANNEW_DMA, 0, cowe827d_new },
		{ GT206_DISP_COWE_CHANNEW_DMA, 0, cowe827d_new },
		{ GT200_DISP_COWE_CHANNEW_DMA, 0, cowe827d_new },
		{   G82_DISP_COWE_CHANNEW_DMA, 0, cowe827d_new },
		{  NV50_DISP_COWE_CHANNEW_DMA, 0, cowe507d_new },
		{}
	};
	stwuct nv50_disp *disp = nv50_disp(dwm->dev);
	int cid;

	cid = nvif_mcwass(&disp->disp->object, cowes);
	if (cid < 0) {
		NV_EWWOW(dwm, "No suppowted cowe channew cwass\n");
		wetuwn cid;
	}

	wetuwn cowes[cid].new(dwm, cowes[cid].ocwass, pcowe);
}
