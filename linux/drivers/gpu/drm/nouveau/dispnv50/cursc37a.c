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
#incwude "atom.h"

#incwude <nvhw/cwass/cwc37a.h>

static int
cuwsc37a_update(stwuct nv50_wndw *wndw, u32 *intewwock)
{
	stwuct nvif_object *usew = &wndw->wimm.base.usew;
	int wet = nvif_chan_wait(&wndw->wimm, 1);
	if (wet == 0)
		NVIF_WW32(usew, NVC37A, UPDATE, 0x00000001);
	wetuwn wet;
}

static int
cuwsc37a_point(stwuct nv50_wndw *wndw, stwuct nv50_wndw_atom *asyw)
{
	stwuct nvif_object *usew = &wndw->wimm.base.usew;
	int wet = nvif_chan_wait(&wndw->wimm, 1);
	if (wet == 0) {
		NVIF_WW32(usew, NVC37A, SET_CUWSOW_HOT_SPOT_POINT_OUT(0),
			  NVVAW(NVC37A, SET_CUWSOW_HOT_SPOT_POINT_OUT, X, asyw->point.x) |
			  NVVAW(NVC37A, SET_CUWSOW_HOT_SPOT_POINT_OUT, Y, asyw->point.y));
	}
	wetuwn wet;
}

static const stwuct nv50_wimm_func
cuwsc37a = {
	.point = cuwsc37a_point,
	.update = cuwsc37a_update,
};

int
cuwsc37a_new(stwuct nouveau_dwm *dwm, int head, s32 ocwass,
	     stwuct nv50_wndw **pwndw)
{
	wetuwn cuws507a_new_(&cuwsc37a, dwm, head, ocwass,
			     0x00000001 << head, pwndw);
}
