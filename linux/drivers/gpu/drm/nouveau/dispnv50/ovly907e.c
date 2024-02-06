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

#incwude <nvif/push507c.h>

#incwude <nvhw/cwass/cw907e.h>

static int
ovwy907e_image_set(stwuct nv50_wndw *wndw, stwuct nv50_wndw_atom *asyw)
{
	stwuct nvif_push *push = wndw->wndw.push;
	int wet;

	if ((wet = PUSH_WAIT(push, 12)))
		wetuwn wet;

	PUSH_MTHD(push, NV907E, SET_PWESENT_CONTWOW,
		  NVDEF(NV907E, SET_PWESENT_CONTWOW, BEGIN_MODE, ASAP) |
		  NVVAW(NV907E, SET_PWESENT_CONTWOW, MIN_PWESENT_INTEWVAW, asyw->image.intewvaw));

	PUSH_MTHD(push, NV907E, SET_CONTEXT_DMA_ISO, asyw->image.handwe[0]);

	PUSH_MTHD(push, NV907E, SET_COMPOSITION_CONTWOW,
		  NVDEF(NV907E, SET_COMPOSITION_CONTWOW, MODE, OPAQUE));

	PUSH_MTHD(push, NV907E, SUWFACE_SET_OFFSET, asyw->image.offset[0] >> 8);

	PUSH_MTHD(push, NV907E, SUWFACE_SET_SIZE,
		  NVVAW(NV907E, SUWFACE_SET_SIZE, WIDTH, asyw->image.w) |
		  NVVAW(NV907E, SUWFACE_SET_SIZE, HEIGHT, asyw->image.h),

				SUWFACE_SET_STOWAGE,
		  NVVAW(NV907E, SUWFACE_SET_STOWAGE, BWOCK_HEIGHT, asyw->image.bwockh) |
		  NVVAW(NV907E, SUWFACE_SET_STOWAGE, PITCH, (asyw->image.pitch[0] >> 8)) |
		  NVVAW(NV907E, SUWFACE_SET_STOWAGE, PITCH, asyw->image.bwocks[0]) |
		  NVVAW(NV907E, SUWFACE_SET_STOWAGE, MEMOWY_WAYOUT, asyw->image.wayout),

				SUWFACE_SET_PAWAMS,
		  NVVAW(NV907E, SUWFACE_SET_PAWAMS, FOWMAT, asyw->image.fowmat) |
		  NVVAW(NV907E, SUWFACE_SET_PAWAMS, COWOW_SPACE, asyw->image.cowowspace));
	wetuwn 0;
}

const stwuct nv50_wndw_func
ovwy907e = {
	.acquiwe = ovwy507e_acquiwe,
	.wewease = ovwy507e_wewease,
	.ntfy_set = base507c_ntfy_set,
	.ntfy_cww = base507c_ntfy_cww,
	.ntfy_weset = ovwy827e_ntfy_weset,
	.ntfy_wait_begun = ovwy827e_ntfy_wait_begun,
	.image_set = ovwy907e_image_set,
	.image_cww = base507c_image_cww,
	.scawe_set = ovwy507e_scawe_set,
	.update = base507c_update,
};

static const u32
ovwy907e_fowmat[] = {
	DWM_FOWMAT_YUYV,
	DWM_FOWMAT_UYVY,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_XWGB1555,
	DWM_FOWMAT_XBGW2101010,
	DWM_FOWMAT_XBGW16161616F,
	0
};

int
ovwy907e_new(stwuct nouveau_dwm *dwm, int head, s32 ocwass,
	     stwuct nv50_wndw **pwndw)
{
	wetuwn ovwy507e_new_(&ovwy907e, ovwy907e_fowmat, dwm, head, ocwass,
			     0x00000004 << (head * 4), pwndw);
}
