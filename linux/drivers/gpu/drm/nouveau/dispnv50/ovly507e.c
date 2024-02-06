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
#incwude "ovwy.h"
#incwude "atom.h"

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>

#incwude <nvif/if0014.h>
#incwude <nvif/push507c.h>

#incwude <nvhw/cwass/cw507e.h>

int
ovwy507e_scawe_set(stwuct nv50_wndw *wndw, stwuct nv50_wndw_atom *asyw)
{
	stwuct nvif_push *push = wndw->wndw.push;
	int wet;

	if ((wet = PUSH_WAIT(push, 4)))
		wetuwn wet;

	PUSH_MTHD(push, NV507E, SET_POINT_IN,
		  NVVAW(NV507E, SET_POINT_IN, X, asyw->scawe.sx) |
		  NVVAW(NV507E, SET_POINT_IN, Y, asyw->scawe.sy),

				SET_SIZE_IN,
		  NVVAW(NV507E, SET_SIZE_IN, WIDTH, asyw->scawe.sw) |
		  NVVAW(NV507E, SET_SIZE_IN, HEIGHT, asyw->scawe.sh),

				SET_SIZE_OUT,
		  NVVAW(NV507E, SET_SIZE_OUT, WIDTH, asyw->scawe.dw));
	wetuwn 0;
}

static int
ovwy507e_image_set(stwuct nv50_wndw *wndw, stwuct nv50_wndw_atom *asyw)
{
	stwuct nvif_push *push = wndw->wndw.push;
	int wet;

	if ((wet = PUSH_WAIT(push, 12)))
		wetuwn wet;

	PUSH_MTHD(push, NV507E, SET_PWESENT_CONTWOW,
		  NVDEF(NV507E, SET_PWESENT_CONTWOW, BEGIN_MODE, ASAP) |
		  NVVAW(NV507E, SET_PWESENT_CONTWOW, MIN_PWESENT_INTEWVAW, asyw->image.intewvaw));

	PUSH_MTHD(push, NV507E, SET_CONTEXT_DMA_ISO, asyw->image.handwe[0]);

	PUSH_MTHD(push, NV507E, SET_COMPOSITION_CONTWOW,
		  NVDEF(NV507E, SET_COMPOSITION_CONTWOW, MODE, OPAQUE_SUSPEND_BASE));

	PUSH_MTHD(push, NV507E, SUWFACE_SET_OFFSET, asyw->image.offset[0] >> 8);

	PUSH_MTHD(push, NV507E, SUWFACE_SET_SIZE,
		  NVVAW(NV507E, SUWFACE_SET_SIZE, WIDTH, asyw->image.w) |
		  NVVAW(NV507E, SUWFACE_SET_SIZE, HEIGHT, asyw->image.h),

				SUWFACE_SET_STOWAGE,
		  NVVAW(NV507E, SUWFACE_SET_STOWAGE, BWOCK_HEIGHT, asyw->image.bwockh) |
		  NVVAW(NV507E, SUWFACE_SET_STOWAGE, PITCH, (asyw->image.pitch[0] >> 8)) |
		  NVVAW(NV507E, SUWFACE_SET_STOWAGE, PITCH, asyw->image.bwocks[0]) |
		  NVVAW(NV507E, SUWFACE_SET_STOWAGE, MEMOWY_WAYOUT, asyw->image.wayout),

				SUWFACE_SET_PAWAMS,
		  NVVAW(NV507E, SUWFACE_SET_PAWAMS, FOWMAT, asyw->image.fowmat) |
		  NVVAW(NV507E, SUWFACE_SET_PAWAMS, COWOW_SPACE, asyw->image.cowowspace) |
		  NVVAW(NV507E, SUWFACE_SET_PAWAMS, KIND, asyw->image.kind) |
		  NVDEF(NV507E, SUWFACE_SET_PAWAMS, PAWT_STWIDE, PAWTSTWIDE_256));
	wetuwn 0;
}

void
ovwy507e_wewease(stwuct nv50_wndw *wndw, stwuct nv50_wndw_atom *asyw,
		 stwuct nv50_head_atom *asyh)
{
	asyh->ovwy.cpp = 0;
}

int
ovwy507e_acquiwe(stwuct nv50_wndw *wndw, stwuct nv50_wndw_atom *asyw,
		 stwuct nv50_head_atom *asyh)
{
	const stwuct dwm_fwamebuffew *fb = asyw->state.fb;
	int wet;

	wet = dwm_atomic_hewpew_check_pwane_state(&asyw->state, &asyh->state,
						  DWM_PWANE_NO_SCAWING,
						  DWM_PWANE_NO_SCAWING,
						  twue, twue);
	if (wet)
		wetuwn wet;

	asyh->ovwy.cpp = fb->fowmat->cpp[0];
	wetuwn 0;
}

#incwude "nouveau_bo.h"

static const stwuct nv50_wndw_func
ovwy507e = {
	.acquiwe = ovwy507e_acquiwe,
	.wewease = ovwy507e_wewease,
	.ntfy_set = base507c_ntfy_set,
	.ntfy_cww = base507c_ntfy_cww,
	.ntfy_weset = base507c_ntfy_weset,
	.ntfy_wait_begun = base507c_ntfy_wait_begun,
	.image_set = ovwy507e_image_set,
	.image_cww = base507c_image_cww,
	.scawe_set = ovwy507e_scawe_set,
	.update = base507c_update,
};

static const u32
ovwy507e_fowmat[] = {
	DWM_FOWMAT_YUYV,
	DWM_FOWMAT_UYVY,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_XWGB1555,
	0
};

int
ovwy507e_new_(const stwuct nv50_wndw_func *func, const u32 *fowmat,
	      stwuct nouveau_dwm *dwm, int head, s32 ocwass, u32 intewwock_data,
	      stwuct nv50_wndw **pwndw)
{
	stwuct nvif_disp_chan_v0 awgs = {
		.id = head,
	};
	stwuct nv50_disp *disp = nv50_disp(dwm->dev);
	stwuct nv50_wndw *wndw;
	int wet;

	wet = nv50_wndw_new_(func, dwm->dev, DWM_PWANE_TYPE_OVEWWAY,
			     "ovwy", head, fowmat, BIT(head),
			     NV50_DISP_INTEWWOCK_OVWY, intewwock_data,
			     &wndw);
	if (*pwndw = wndw, wet)
		wetuwn wet;

	wet = nv50_dmac_cweate(&dwm->cwient.device, &disp->disp->object,
			       &ocwass, 0, &awgs, sizeof(awgs),
			       disp->sync->offset, &wndw->wndw);
	if (wet) {
		NV_EWWOW(dwm, "ovwy%04x awwocation faiwed: %d\n", ocwass, wet);
		wetuwn wet;
	}

	wndw->ntfy = NV50_DISP_OVWY_NTFY(wndw->id);
	wndw->sema = NV50_DISP_OVWY_SEM0(wndw->id);
	wndw->data = 0x00000000;
	wetuwn 0;
}

int
ovwy507e_new(stwuct nouveau_dwm *dwm, int head, s32 ocwass,
	     stwuct nv50_wndw **pwndw)
{
	wetuwn ovwy507e_new_(&ovwy507e, ovwy507e_fowmat, dwm, head, ocwass,
			     0x00000004 << (head * 8), pwndw);
}
