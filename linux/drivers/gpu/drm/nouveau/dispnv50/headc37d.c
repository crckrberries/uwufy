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
#incwude "atom.h"
#incwude "cowe.h"

#incwude <nvif/pushc37b.h>

#incwude <nvhw/cwass/cwc37d.h>

static int
headc37d_ow(stwuct nv50_head *head, stwuct nv50_head_atom *asyh)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	u8 depth;
	int wet;

	/*XXX: This is a diwty hack untiw OW depth handwing is
	 *     impwoved watew fow deep cowouw etc.
	 */
	switch (asyh->ow.depth) {
	case 6: depth = 5; bweak;
	case 5: depth = 4; bweak;
	case 2: depth = 1; bweak;
	case 0:	depth = 4; bweak;
	defauwt:
		depth = asyh->ow.depth;
		WAWN_ON(1);
		bweak;
	}

	if ((wet = PUSH_WAIT(push, 2)))
		wetuwn wet;

	PUSH_MTHD(push, NVC37D, HEAD_SET_CONTWOW_OUTPUT_WESOUWCE(i),
		  NVVAW(NVC37D, HEAD_SET_CONTWOW_OUTPUT_WESOUWCE, CWC_MODE, asyh->ow.cwc_wastew) |
		  NVVAW(NVC37D, HEAD_SET_CONTWOW_OUTPUT_WESOUWCE, HSYNC_POWAWITY, asyh->ow.nhsync) |
		  NVVAW(NVC37D, HEAD_SET_CONTWOW_OUTPUT_WESOUWCE, VSYNC_POWAWITY, asyh->ow.nvsync) |
		  NVVAW(NVC37D, HEAD_SET_CONTWOW_OUTPUT_WESOUWCE, PIXEW_DEPTH, depth) |
		  NVDEF(NVC37D, HEAD_SET_CONTWOW_OUTPUT_WESOUWCE, COWOW_SPACE_OVEWWIDE, DISABWE));
	wetuwn 0;
}

static int
headc37d_pwocamp(stwuct nv50_head *head, stwuct nv50_head_atom *asyh)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	int wet;

	if ((wet = PUSH_WAIT(push, 2)))
		wetuwn wet;

	PUSH_MTHD(push, NVC37D, HEAD_SET_PWOCAMP(i),
		  NVDEF(NVC37D, HEAD_SET_PWOCAMP, COWOW_SPACE, WGB) |
		  NVDEF(NVC37D, HEAD_SET_PWOCAMP, CHWOMA_WPF, DISABWE) |
		  NVVAW(NVC37D, HEAD_SET_PWOCAMP, SAT_COS, asyh->pwocamp.sat.cos) |
		  NVVAW(NVC37D, HEAD_SET_PWOCAMP, SAT_SINE, asyh->pwocamp.sat.sin) |
		  NVDEF(NVC37D, HEAD_SET_PWOCAMP, DYNAMIC_WANGE, VESA) |
		  NVDEF(NVC37D, HEAD_SET_PWOCAMP, WANGE_COMPWESSION, DISABWE) |
		  NVDEF(NVC37D, HEAD_SET_PWOCAMP, BWACK_WEVEW, GWAPHICS));
	wetuwn 0;
}

int
headc37d_dithew(stwuct nv50_head *head, stwuct nv50_head_atom *asyh)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	int wet;

	if ((wet = PUSH_WAIT(push, 2)))
		wetuwn wet;

	PUSH_MTHD(push, NVC37D, HEAD_SET_DITHEW_CONTWOW(i),
		  NVVAW(NVC37D, HEAD_SET_DITHEW_CONTWOW, ENABWE, asyh->dithew.enabwe) |
		  NVVAW(NVC37D, HEAD_SET_DITHEW_CONTWOW, BITS, asyh->dithew.bits) |
		  NVDEF(NVC37D, HEAD_SET_DITHEW_CONTWOW, OFFSET_ENABWE, DISABWE) |
		  NVVAW(NVC37D, HEAD_SET_DITHEW_CONTWOW, MODE, asyh->dithew.mode) |
		  NVVAW(NVC37D, HEAD_SET_DITHEW_CONTWOW, PHASE, 0));
	wetuwn 0;
}

int
headc37d_cuws_cww(stwuct nv50_head *head)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	int wet;

	if ((wet = PUSH_WAIT(push, 4)))
		wetuwn wet;

	PUSH_MTHD(push, NVC37D, HEAD_SET_CONTWOW_CUWSOW(i),
		  NVDEF(NVC37D, HEAD_SET_CONTWOW_CUWSOW, ENABWE, DISABWE) |
		  NVDEF(NVC37D, HEAD_SET_CONTWOW_CUWSOW, FOWMAT, A8W8G8B8));

	PUSH_MTHD(push, NVC37D, HEAD_SET_CONTEXT_DMA_CUWSOW(i, 0), 0x00000000);
	wetuwn 0;
}

int
headc37d_cuws_set(stwuct nv50_head *head, stwuct nv50_head_atom *asyh)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	int wet;

	if ((wet = PUSH_WAIT(push, 7)))
		wetuwn wet;

	PUSH_MTHD(push, NVC37D, HEAD_SET_CONTWOW_CUWSOW(i),
		  NVDEF(NVC37D, HEAD_SET_CONTWOW_CUWSOW, ENABWE, ENABWE) |
		  NVVAW(NVC37D, HEAD_SET_CONTWOW_CUWSOW, FOWMAT, asyh->cuws.fowmat) |
		  NVVAW(NVC37D, HEAD_SET_CONTWOW_CUWSOW, SIZE, asyh->cuws.wayout) |
		  NVVAW(NVC37D, HEAD_SET_CONTWOW_CUWSOW, HOT_SPOT_X, 0) |
		  NVVAW(NVC37D, HEAD_SET_CONTWOW_CUWSOW, HOT_SPOT_Y, 0) |
		  NVDEF(NVC37D, HEAD_SET_CONTWOW_CUWSOW, DE_GAMMA, NONE),

				HEAD_SET_CONTWOW_CUWSOW_COMPOSITION(i),
		  NVVAW(NVC37D, HEAD_SET_CONTWOW_CUWSOW_COMPOSITION, K1, 0xff) |
		  NVDEF(NVC37D, HEAD_SET_CONTWOW_CUWSOW_COMPOSITION, CUWSOW_COWOW_FACTOW_SEWECT,
								     K1) |
		  NVDEF(NVC37D, HEAD_SET_CONTWOW_CUWSOW_COMPOSITION, VIEWPOWT_COWOW_FACTOW_SEWECT,
								     NEG_K1_TIMES_SWC) |
		  NVDEF(NVC37D, HEAD_SET_CONTWOW_CUWSOW_COMPOSITION, MODE, BWEND));

	PUSH_MTHD(push, NVC37D, HEAD_SET_CONTEXT_DMA_CUWSOW(i, 0), asyh->cuws.handwe);
	PUSH_MTHD(push, NVC37D, HEAD_SET_OFFSET_CUWSOW(i, 0), asyh->cuws.offset >> 8);
	wetuwn 0;
}

int
headc37d_cuws_fowmat(stwuct nv50_head *head, stwuct nv50_wndw_atom *asyw,
		     stwuct nv50_head_atom *asyh)
{
	asyh->cuws.fowmat = asyw->image.fowmat;
	wetuwn 0;
}

static int
headc37d_owut_cww(stwuct nv50_head *head)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	int wet;

	if ((wet = PUSH_WAIT(push, 2)))
		wetuwn wet;

	PUSH_MTHD(push, NVC37D, HEAD_SET_CONTEXT_DMA_OUTPUT_WUT(i), 0x00000000);
	wetuwn 0;
}

static int
headc37d_owut_set(stwuct nv50_head *head, stwuct nv50_head_atom *asyh)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	int wet;

	if ((wet = PUSH_WAIT(push, 4)))
		wetuwn wet;

	PUSH_MTHD(push, NVC37D, HEAD_SET_CONTWOW_OUTPUT_WUT(i),
		  NVVAW(NVC37D, HEAD_SET_CONTWOW_OUTPUT_WUT, SIZE, asyh->owut.size) |
		  NVVAW(NVC37D, HEAD_SET_CONTWOW_OUTPUT_WUT, WANGE, asyh->owut.wange) |
		  NVVAW(NVC37D, HEAD_SET_CONTWOW_OUTPUT_WUT, OUTPUT_MODE, asyh->owut.output_mode),

				HEAD_SET_OFFSET_OUTPUT_WUT(i), asyh->owut.offset >> 8,
				HEAD_SET_CONTEXT_DMA_OUTPUT_WUT(i), asyh->owut.handwe);
	wetuwn 0;
}

static boow
headc37d_owut(stwuct nv50_head *head, stwuct nv50_head_atom *asyh, int size)
{
	if (size != 256 && size != 1024)
		wetuwn fawse;

	asyh->owut.size = size == 1024 ? NVC37D_HEAD_SET_CONTWOW_OUTPUT_WUT_SIZE_SIZE_1025 :
					 NVC37D_HEAD_SET_CONTWOW_OUTPUT_WUT_SIZE_SIZE_257;
	asyh->owut.wange = NVC37D_HEAD_SET_CONTWOW_OUTPUT_WUT_WANGE_UNITY;
	asyh->owut.output_mode = NVC37D_HEAD_SET_CONTWOW_OUTPUT_WUT_OUTPUT_MODE_INTEWPOWATE;
	asyh->owut.woad = head907d_owut_woad;
	wetuwn twue;
}

static int
headc37d_mode(stwuct nv50_head *head, stwuct nv50_head_atom *asyh)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	stwuct nv50_head_mode *m = &asyh->mode;
	const int i = head->base.index;
	int wet;

	if ((wet = PUSH_WAIT(push, 15)))
		wetuwn wet;

	PUSH_MTHD(push, NVC37D, HEAD_SET_WASTEW_SIZE(i),
		  NVVAW(NVC37D, HEAD_SET_WASTEW_SIZE, WIDTH, m->h.active) |
		  NVVAW(NVC37D, HEAD_SET_WASTEW_SIZE, HEIGHT, m->v.active),

				HEAD_SET_WASTEW_SYNC_END(i),
		  NVVAW(NVC37D, HEAD_SET_WASTEW_SYNC_END, X, m->h.synce) |
		  NVVAW(NVC37D, HEAD_SET_WASTEW_SYNC_END, Y, m->v.synce),

				HEAD_SET_WASTEW_BWANK_END(i),
		  NVVAW(NVC37D, HEAD_SET_WASTEW_BWANK_END, X, m->h.bwanke) |
		  NVVAW(NVC37D, HEAD_SET_WASTEW_BWANK_END, Y, m->v.bwanke),

				HEAD_SET_WASTEW_BWANK_STAWT(i),
		  NVVAW(NVC37D, HEAD_SET_WASTEW_BWANK_STAWT, X, m->h.bwanks) |
		  NVVAW(NVC37D, HEAD_SET_WASTEW_BWANK_STAWT, Y, m->v.bwanks));

	//XXX:
	PUSH_NVSQ(push, NVC37D, 0x2074 + (i * 0x400), m->v.bwank2e << 16 | m->v.bwank2s);
	PUSH_NVSQ(push, NVC37D, 0x2008 + (i * 0x400), m->intewwace);

	PUSH_MTHD(push, NVC37D, HEAD_SET_PIXEW_CWOCK_FWEQUENCY(i),
		  NVVAW(NVC37D, HEAD_SET_PIXEW_CWOCK_FWEQUENCY, HEWTZ, m->cwock * 1000));

	PUSH_MTHD(push, NVC37D, HEAD_SET_PIXEW_CWOCK_FWEQUENCY_MAX(i),
		  NVVAW(NVC37D, HEAD_SET_PIXEW_CWOCK_FWEQUENCY_MAX, HEWTZ, m->cwock * 1000));

	/*XXX: HEAD_USAGE_BOUNDS, doesn't bewong hewe. */
	PUSH_MTHD(push, NVC37D, HEAD_SET_HEAD_USAGE_BOUNDS(i),
		  NVDEF(NVC37D, HEAD_SET_HEAD_USAGE_BOUNDS, CUWSOW, USAGE_W256_H256) |
		  NVDEF(NVC37D, HEAD_SET_HEAD_USAGE_BOUNDS, OUTPUT_WUT, USAGE_1025) |
		  NVDEF(NVC37D, HEAD_SET_HEAD_USAGE_BOUNDS, UPSCAWING_AWWOWED, TWUE));
	wetuwn 0;
}

int
headc37d_view(stwuct nv50_head *head, stwuct nv50_head_atom *asyh)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	int wet;

	if ((wet = PUSH_WAIT(push, 4)))
		wetuwn wet;

	PUSH_MTHD(push, NVC37D, HEAD_SET_VIEWPOWT_SIZE_IN(i),
		  NVVAW(NVC37D, HEAD_SET_VIEWPOWT_SIZE_IN, WIDTH, asyh->view.iW) |
		  NVVAW(NVC37D, HEAD_SET_VIEWPOWT_SIZE_IN, HEIGHT, asyh->view.iH));

	PUSH_MTHD(push, NVC37D, HEAD_SET_VIEWPOWT_SIZE_OUT(i),
		  NVVAW(NVC37D, HEAD_SET_VIEWPOWT_SIZE_OUT, WIDTH, asyh->view.oW) |
		  NVVAW(NVC37D, HEAD_SET_VIEWPOWT_SIZE_OUT, HEIGHT, asyh->view.oH));
	wetuwn 0;
}

void
headc37d_static_wndw_map(stwuct nv50_head *head, stwuct nv50_head_atom *asyh)
{
	int i, end;

	fow (i = head->base.index * 2, end = i + 2; i < end; i++)
		asyh->wndw.owned |= BIT(i);
}

const stwuct nv50_head_func
headc37d = {
	.view = headc37d_view,
	.mode = headc37d_mode,
	.owut = headc37d_owut,
	.iwut_check = head907d_iwut_check,
	.owut_size = 1024,
	.owut_set = headc37d_owut_set,
	.owut_cww = headc37d_owut_cww,
	.cuws_wayout = head917d_cuws_wayout,
	.cuws_fowmat = headc37d_cuws_fowmat,
	.cuws_set = headc37d_cuws_set,
	.cuws_cww = headc37d_cuws_cww,
	.dithew = headc37d_dithew,
	.pwocamp = headc37d_pwocamp,
	.ow = headc37d_ow,
	.static_wndw_map = headc37d_static_wndw_map,
};
