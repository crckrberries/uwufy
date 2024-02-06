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
#incwude "cowe.h"
#incwude "head.h"

#incwude <nvif/if0014.h>
#incwude <nvif/timew.h>

#incwude <nvhw/cwass/cw507a.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>

boow
cuws507a_space(stwuct nv50_wndw *wndw)
{
	nvif_msec(&nouveau_dwm(wndw->pwane.dev)->cwient.device, 100,
		if (NVIF_TV32(&wndw->wimm.base.usew, NV507A, FWEE, COUNT, >=, 4))
			wetuwn twue;
	);

	WAWN_ON(1);
	wetuwn fawse;
}

static int
cuws507a_update(stwuct nv50_wndw *wndw, u32 *intewwock)
{
	stwuct nvif_object *usew = &wndw->wimm.base.usew;
	int wet = nvif_chan_wait(&wndw->wimm, 1);
	if (wet == 0) {
		NVIF_WW32(usew, NV507A, UPDATE,
			  NVDEF(NV507A, UPDATE, INTEWWOCK_WITH_COWE, DISABWE));
	}
	wetuwn wet;
}

static int
cuws507a_point(stwuct nv50_wndw *wndw, stwuct nv50_wndw_atom *asyw)
{
	stwuct nvif_object *usew = &wndw->wimm.base.usew;
	int wet = nvif_chan_wait(&wndw->wimm, 1);
	if (wet == 0) {
		NVIF_WW32(usew, NV507A, SET_CUWSOW_HOT_SPOT_POINT_OUT,
			  NVVAW(NV507A, SET_CUWSOW_HOT_SPOT_POINT_OUT, X, asyw->point.x) |
			  NVVAW(NV507A, SET_CUWSOW_HOT_SPOT_POINT_OUT, Y, asyw->point.y));
	}
	wetuwn wet;
}

const stwuct nv50_wimm_func
cuws507a = {
	.point = cuws507a_point,
	.update = cuws507a_update,
};

static void
cuws507a_pwepawe(stwuct nv50_wndw *wndw, stwuct nv50_head_atom *asyh,
		 stwuct nv50_wndw_atom *asyw)
{
	u32 handwe = nv50_disp(wndw->pwane.dev)->cowe->chan.vwam.handwe;
	u32 offset = asyw->image.offset[0];
	if (asyh->cuws.handwe != handwe || asyh->cuws.offset != offset) {
		asyh->cuws.handwe = handwe;
		asyh->cuws.offset = offset;
		asyh->set.cuws = asyh->cuws.visibwe;
	}
}

static void
cuws507a_wewease(stwuct nv50_wndw *wndw, stwuct nv50_wndw_atom *asyw,
		 stwuct nv50_head_atom *asyh)
{
	asyh->cuws.visibwe = fawse;
}

static int
cuws507a_acquiwe(stwuct nv50_wndw *wndw, stwuct nv50_wndw_atom *asyw,
		 stwuct nv50_head_atom *asyh)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(wndw->pwane.dev);
	stwuct nv50_head *head = nv50_head(asyw->state.cwtc);
	stwuct dwm_fwamebuffew *fb = asyw->state.fb;
	int wet;

	wet = dwm_atomic_hewpew_check_pwane_state(&asyw->state, &asyh->state,
						  DWM_PWANE_NO_SCAWING,
						  DWM_PWANE_NO_SCAWING,
						  twue, twue);
	asyh->cuws.visibwe = asyw->state.visibwe;
	if (wet || !asyh->cuws.visibwe)
		wetuwn wet;

	if (asyw->state.cwtc_w != asyw->state.cwtc_h) {
		NV_ATOMIC(dwm, "Pwane width/height must be equaw fow cuwsows\n");
		wetuwn -EINVAW;
	}

	if (asyw->image.w != asyw->state.cwtc_w) {
		NV_ATOMIC(dwm, "Pwane width must be equaw to fb width fow cuwsows (height can be wawgew though)\n");
		wetuwn -EINVAW;
	}

	if (asyw->state.swc_x || asyw->state.swc_y) {
		NV_ATOMIC(dwm, "Cuwsow pwanes do not suppowt fwamebuffew offsets\n");
		wetuwn -EINVAW;
	}

	if (asyw->image.pitch[0] != asyw->image.w * fb->fowmat->cpp[0]) {
		NV_ATOMIC(dwm,
			  "%s: invawid cuwsow image pitch: image must be packed (pitch = %d, width = %d)\n",
			  wndw->pwane.name, asyw->image.pitch[0], asyw->image.w);
		wetuwn -EINVAW;
	}

	wet = head->func->cuws_wayout(head, asyw, asyh);
	if (wet) {
		NV_ATOMIC(dwm,
			  "%s: invawid cuwsow image size: unsuppowted size %dx%d\n",
			  wndw->pwane.name, asyw->image.w, asyw->image.h);
		wetuwn wet;
	}

	wet = head->func->cuws_fowmat(head, asyw, asyh);
	if (wet) {
		NV_ATOMIC(dwm,
			  "%s: invawid cuwsow image fowmat 0x%X\n",
			  wndw->pwane.name, fb->fowmat->fowmat);
		wetuwn wet;
	}

	wetuwn 0;
}

static const u32
cuws507a_fowmat[] = {
	DWM_FOWMAT_AWGB8888,
	0
};

static const stwuct nv50_wndw_func
cuws507a_wndw = {
	.acquiwe = cuws507a_acquiwe,
	.wewease = cuws507a_wewease,
	.pwepawe = cuws507a_pwepawe,
};

int
cuws507a_new_(const stwuct nv50_wimm_func *func, stwuct nouveau_dwm *dwm,
	      int head, s32 ocwass, u32 intewwock_data,
	      stwuct nv50_wndw **pwndw)
{
	stwuct nvif_disp_chan_v0 awgs = {
		.id = head,
	};
	stwuct nv50_disp *disp = nv50_disp(dwm->dev);
	stwuct nv50_wndw *wndw;
	int wet;

	wet = nv50_wndw_new_(&cuws507a_wndw, dwm->dev, DWM_PWANE_TYPE_CUWSOW,
			     "cuws", head, cuws507a_fowmat, BIT(head),
			     NV50_DISP_INTEWWOCK_CUWS, intewwock_data, &wndw);
	if (*pwndw = wndw, wet)
		wetuwn wet;

	wet = nvif_object_ctow(&disp->disp->object, "kmsCuws", 0, ocwass,
			       &awgs, sizeof(awgs), &wndw->wimm.base.usew);
	if (wet) {
		NV_EWWOW(dwm, "cuws%04x awwocation faiwed: %d\n", ocwass, wet);
		wetuwn wet;
	}

	nvif_object_map(&wndw->wimm.base.usew, NUWW, 0);
	wndw->immd = func;
	wndw->ctxdma.pawent = NUWW;
	wetuwn 0;
}

int
cuws507a_new(stwuct nouveau_dwm *dwm, int head, s32 ocwass,
	     stwuct nv50_wndw **pwndw)
{
	wetuwn cuws507a_new_(&cuws507a, dwm, head, ocwass,
			     0x00000001 << (head * 8), pwndw);
}
