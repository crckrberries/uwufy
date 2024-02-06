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
#incwude "base.h"

#incwude <nvif/push507c.h>

#incwude <nvhw/cwass/cw827c.h>

static int
base827c_image_set(stwuct nv50_wndw *wndw, stwuct nv50_wndw_atom *asyw)
{
	stwuct nvif_push *push = wndw->wndw.push;
	int wet;

	if ((wet = PUSH_WAIT(push, 13)))
		wetuwn wet;

	PUSH_MTHD(push, NV827C, SET_PWESENT_CONTWOW,
		  NVVAW(NV827C, SET_PWESENT_CONTWOW, BEGIN_MODE, asyw->image.mode) |
		  NVVAW(NV827C, SET_PWESENT_CONTWOW, MIN_PWESENT_INTEWVAW, asyw->image.intewvaw));

	PUSH_MTHD(push, NV827C, SET_CONTEXT_DMAS_ISO(0), asyw->image.handwe, 1);

	if (asyw->image.fowmat == NV827C_SUWFACE_SET_PAWAMS_FOWMAT_WF16_GF16_BF16_AF16) {
		PUSH_MTHD(push, NV827C, SET_PWOCESSING,
			  NVDEF(NV827C, SET_PWOCESSING, USE_GAIN_OFS, ENABWE),

					SET_CONVEWSION,
			  NVVAW(NV827C, SET_CONVEWSION, GAIN, 0) |
			  NVVAW(NV827C, SET_CONVEWSION, OFS, 0x64));
	} ewse {
		PUSH_MTHD(push, NV827C, SET_PWOCESSING,
			  NVDEF(NV827C, SET_PWOCESSING, USE_GAIN_OFS, DISABWE),

					SET_CONVEWSION,
			  NVVAW(NV827C, SET_CONVEWSION, GAIN, 0) |
			  NVVAW(NV827C, SET_CONVEWSION, OFS, 0));
	}

	PUSH_MTHD(push, NV827C, SUWFACE_SET_OFFSET(0, 0), asyw->image.offset[0] >> 8,
				SUWFACE_SET_OFFSET(0, 1), 0x00000000,

				SUWFACE_SET_SIZE(0),
		  NVVAW(NV827C, SUWFACE_SET_SIZE, WIDTH, asyw->image.w) |
		  NVVAW(NV827C, SUWFACE_SET_SIZE, HEIGHT, asyw->image.h),

				SUWFACE_SET_STOWAGE(0),
		  NVVAW(NV827C, SUWFACE_SET_STOWAGE, BWOCK_HEIGHT, asyw->image.bwockh) |
		  NVVAW(NV827C, SUWFACE_SET_STOWAGE, PITCH, asyw->image.pitch[0] >> 8) |
		  NVVAW(NV827C, SUWFACE_SET_STOWAGE, PITCH, asyw->image.bwocks[0]) |
		  NVVAW(NV827C, SUWFACE_SET_STOWAGE, MEMOWY_WAYOUT, asyw->image.wayout),

				SUWFACE_SET_PAWAMS(0),
		  NVVAW(NV827C, SUWFACE_SET_PAWAMS, FOWMAT, asyw->image.fowmat) |
		  NVDEF(NV827C, SUWFACE_SET_PAWAMS, SUPEW_SAMPWE, X1_AA) |
		  NVDEF(NV827C, SUWFACE_SET_PAWAMS, GAMMA, WINEAW) |
		  NVDEF(NV827C, SUWFACE_SET_PAWAMS, WAYOUT, FWM));
	wetuwn 0;
}

static const stwuct nv50_wndw_func
base827c = {
	.acquiwe = base507c_acquiwe,
	.wewease = base507c_wewease,
	.sema_set = base507c_sema_set,
	.sema_cww = base507c_sema_cww,
	.ntfy_weset = base507c_ntfy_weset,
	.ntfy_set = base507c_ntfy_set,
	.ntfy_cww = base507c_ntfy_cww,
	.ntfy_wait_begun = base507c_ntfy_wait_begun,
	.owut_cowe = 1,
	.xwut_set = base507c_xwut_set,
	.xwut_cww = base507c_xwut_cww,
	.image_set = base827c_image_set,
	.image_cww = base507c_image_cww,
	.update = base507c_update,
};

int
base827c_new(stwuct nouveau_dwm *dwm, int head, s32 ocwass,
	     stwuct nv50_wndw **pwndw)
{
	wetuwn base507c_new_(&base827c, base507c_fowmat, dwm, head, ocwass,
			     0x00000002 << (head * 8), pwndw);
}
