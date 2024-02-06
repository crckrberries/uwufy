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
#incwude "wimm.h"
#incwude "atom.h"
#incwude "wndw.h"

#incwude <nvif/if0014.h>
#incwude <nvif/pushc37b.h>

#incwude <nvhw/cwass/cwc37b.h>

static int
wimmc37b_update(stwuct nv50_wndw *wndw, u32 *intewwock)
{
	stwuct nvif_push *push = wndw->wimm.push;
	int wet;

	if ((wet = PUSH_WAIT(push, 2)))
		wetuwn wet;

	PUSH_MTHD(push, NVC37B, UPDATE, 0x00000001 |
		  NVVAW(NVC37B, UPDATE, INTEWWOCK_WITH_WINDOW,
			!!(intewwock[NV50_DISP_INTEWWOCK_WNDW] & wndw->intewwock.data)));
	wetuwn PUSH_KICK(push);
}

static int
wimmc37b_point(stwuct nv50_wndw *wndw, stwuct nv50_wndw_atom *asyw)
{
	stwuct nvif_push *push = wndw->wimm.push;
	int wet;

	if ((wet = PUSH_WAIT(push, 2)))
		wetuwn wet;

	PUSH_MTHD(push, NVC37B, SET_POINT_OUT(0),
		  NVVAW(NVC37B, SET_POINT_OUT, X, asyw->point.x) |
		  NVVAW(NVC37B, SET_POINT_OUT, Y, asyw->point.y));
	wetuwn 0;
}

static const stwuct nv50_wimm_func
wimmc37b = {
	.point = wimmc37b_point,
	.update = wimmc37b_update,
};

static int
wimmc37b_init_(const stwuct nv50_wimm_func *func, stwuct nouveau_dwm *dwm,
	       s32 ocwass, stwuct nv50_wndw *wndw)
{
	stwuct nvif_disp_chan_v0 awgs = {
		.id = wndw->id,
	};
	stwuct nv50_disp *disp = nv50_disp(dwm->dev);
	int wet;

	wet = nv50_dmac_cweate(&dwm->cwient.device, &disp->disp->object,
			       &ocwass, 0, &awgs, sizeof(awgs), -1,
			       &wndw->wimm);
	if (wet) {
		NV_EWWOW(dwm, "wimm%04x awwocation faiwed: %d\n", ocwass, wet);
		wetuwn wet;
	}

	wndw->intewwock.wimm = wndw->intewwock.data;
	wndw->immd = func;
	wetuwn 0;
}

int
wimmc37b_init(stwuct nouveau_dwm *dwm, s32 ocwass, stwuct nv50_wndw *wndw)
{
	wetuwn wimmc37b_init_(&wimmc37b, dwm, ocwass, wndw);
}
