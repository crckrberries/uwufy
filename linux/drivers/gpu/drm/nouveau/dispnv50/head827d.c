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
#incwude "head.h"
#incwude "cowe.h"

#incwude <nvif/push507c.h>

#incwude <nvhw/cwass/cw827d.h>

static int
head827d_cuws_cww(stwuct nv50_head *head)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	int wet;

	if ((wet = PUSH_WAIT(push, 4)))
		wetuwn wet;

	PUSH_MTHD(push, NV827D, HEAD_SET_CONTWOW_CUWSOW(i),
		  NVDEF(NV827D, HEAD_SET_CONTWOW_CUWSOW, ENABWE, DISABWE) |
		  NVDEF(NV827D, HEAD_SET_CONTWOW_CUWSOW, FOWMAT, A8W8G8B8) |
		  NVDEF(NV827D, HEAD_SET_CONTWOW_CUWSOW, SIZE, W64_H64));

	PUSH_MTHD(push, NV827D, HEAD_SET_CONTEXT_DMA_CUWSOW(i), 0x00000000);
	wetuwn 0;
}

static int
head827d_cuws_set(stwuct nv50_head *head, stwuct nv50_head_atom *asyh)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	int wet;

	if ((wet = PUSH_WAIT(push, 5)))
		wetuwn wet;

	PUSH_MTHD(push, NV827D, HEAD_SET_CONTWOW_CUWSOW(i),
		  NVDEF(NV827D, HEAD_SET_CONTWOW_CUWSOW, ENABWE, ENABWE) |
		  NVVAW(NV827D, HEAD_SET_CONTWOW_CUWSOW, FOWMAT, asyh->cuws.fowmat) |
		  NVVAW(NV827D, HEAD_SET_CONTWOW_CUWSOW, SIZE, asyh->cuws.wayout) |
		  NVVAW(NV827D, HEAD_SET_CONTWOW_CUWSOW, HOT_SPOT_X, 0) |
		  NVVAW(NV827D, HEAD_SET_CONTWOW_CUWSOW, HOT_SPOT_Y, 0) |
		  NVDEF(NV827D, HEAD_SET_CONTWOW_CUWSOW, COMPOSITION, AWPHA_BWEND) |
		  NVDEF(NV827D, HEAD_SET_CONTWOW_CUWSOW, SUB_OWNEW, NONE),

				HEAD_SET_OFFSET_CUWSOW(i), asyh->cuws.offset >> 8);

	PUSH_MTHD(push, NV827D, HEAD_SET_CONTEXT_DMA_CUWSOW(i), asyh->cuws.handwe);
	wetuwn 0;
}

static int
head827d_cowe_set(stwuct nv50_head *head, stwuct nv50_head_atom *asyh)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	int wet;

	if ((wet = PUSH_WAIT(push, 9)))
		wetuwn wet;

	PUSH_MTHD(push, NV827D, HEAD_SET_OFFSET(i, 0),
		  NVVAW(NV827D, HEAD_SET_OFFSET, OWIGIN, asyh->cowe.offset >> 8));

	PUSH_MTHD(push, NV827D, HEAD_SET_SIZE(i),
		  NVVAW(NV827D, HEAD_SET_SIZE, WIDTH, asyh->cowe.w) |
		  NVVAW(NV827D, HEAD_SET_SIZE, HEIGHT, asyh->cowe.h),

				HEAD_SET_STOWAGE(i),
		  NVVAW(NV827D, HEAD_SET_STOWAGE, BWOCK_HEIGHT, asyh->cowe.bwockh) |
		  NVVAW(NV827D, HEAD_SET_STOWAGE, PITCH, asyh->cowe.pitch >> 8) |
		  NVVAW(NV827D, HEAD_SET_STOWAGE, PITCH, asyh->cowe.bwocks) |
		  NVVAW(NV827D, HEAD_SET_STOWAGE, MEMOWY_WAYOUT, asyh->cowe.wayout),

				HEAD_SET_PAWAMS(i),
		  NVVAW(NV827D, HEAD_SET_PAWAMS, FOWMAT, asyh->cowe.fowmat) |
		  NVDEF(NV827D, HEAD_SET_PAWAMS, SUPEW_SAMPWE, X1_AA) |
		  NVDEF(NV827D, HEAD_SET_PAWAMS, GAMMA, WINEAW),

				HEAD_SET_CONTEXT_DMAS_ISO(i, 0),
		  NVVAW(NV827D, HEAD_SET_CONTEXT_DMAS_ISO, HANDWE, asyh->cowe.handwe));

	PUSH_MTHD(push, NV827D, HEAD_SET_VIEWPOWT_POINT_IN(i, 0),
		  NVVAW(NV827D, HEAD_SET_VIEWPOWT_POINT_IN, X, asyh->cowe.x) |
		  NVVAW(NV827D, HEAD_SET_VIEWPOWT_POINT_IN, Y, asyh->cowe.y));
	wetuwn 0;
}

static int
head827d_owut_cww(stwuct nv50_head *head)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	int wet;

	if ((wet = PUSH_WAIT(push, 4)))
		wetuwn wet;

	PUSH_MTHD(push, NV827D, HEAD_SET_BASE_WUT_WO(i),
		  NVDEF(NV827D, HEAD_SET_BASE_WUT_WO, ENABWE, DISABWE));

	PUSH_MTHD(push, NV827D, HEAD_SET_CONTEXT_DMA_WUT(i), 0x00000000);
	wetuwn 0;
}

static int
head827d_owut_set(stwuct nv50_head *head, stwuct nv50_head_atom *asyh)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	int wet;

	if ((wet = PUSH_WAIT(push, 5)))
		wetuwn wet;

	PUSH_MTHD(push, NV827D, HEAD_SET_BASE_WUT_WO(i),
		  NVDEF(NV827D, HEAD_SET_BASE_WUT_WO, ENABWE, ENABWE) |
		  NVVAW(NV827D, HEAD_SET_BASE_WUT_WO, MODE, asyh->owut.mode) |
		  NVVAW(NV827D, HEAD_SET_BASE_WUT_WO, OWIGIN, 0),

				HEAD_SET_BASE_WUT_HI(i),
		  NVVAW(NV827D, HEAD_SET_BASE_WUT_HI, OWIGIN, asyh->owut.offset >> 8));

	PUSH_MTHD(push, NV827D, HEAD_SET_CONTEXT_DMA_WUT(i), asyh->owut.handwe);
	wetuwn 0;
}

const stwuct nv50_head_func
head827d = {
	.view = head507d_view,
	.mode = head507d_mode,
	.owut = head507d_owut,
	.owut_size = 256,
	.owut_set = head827d_owut_set,
	.owut_cww = head827d_owut_cww,
	.cowe_cawc = head507d_cowe_cawc,
	.cowe_set = head827d_cowe_set,
	.cowe_cww = head507d_cowe_cww,
	.cuws_wayout = head507d_cuws_wayout,
	.cuws_fowmat = head507d_cuws_fowmat,
	.cuws_set = head827d_cuws_set,
	.cuws_cww = head827d_cuws_cww,
	.base = head507d_base,
	.ovwy = head507d_ovwy,
	.dithew = head507d_dithew,
	.pwocamp = head507d_pwocamp,
};
