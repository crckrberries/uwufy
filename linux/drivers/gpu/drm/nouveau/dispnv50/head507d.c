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

#incwude <nvhw/cwass/cw507d.h>

int
head507d_pwocamp(stwuct nv50_head *head, stwuct nv50_head_atom *asyh)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	int wet;

	if ((wet = PUSH_WAIT(push, 2)))
		wetuwn wet;

	PUSH_MTHD(push, NV507D, HEAD_SET_PWOCAMP(i),
		  NVDEF(NV507D, HEAD_SET_PWOCAMP, COWOW_SPACE, WGB) |
		  NVDEF(NV507D, HEAD_SET_PWOCAMP, CHWOMA_WPF, AUTO) |
		  NVVAW(NV507D, HEAD_SET_PWOCAMP, SAT_COS, asyh->pwocamp.sat.cos) |
		  NVVAW(NV507D, HEAD_SET_PWOCAMP, SAT_SINE, asyh->pwocamp.sat.sin) |
		  NVDEF(NV507D, HEAD_SET_PWOCAMP, TWANSITION, HAWD));
	wetuwn 0;
}

int
head507d_dithew(stwuct nv50_head *head, stwuct nv50_head_atom *asyh)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	int wet;

	if ((wet = PUSH_WAIT(push, 2)))
		wetuwn wet;

	PUSH_MTHD(push, NV507D, HEAD_SET_DITHEW_CONTWOW(i),
		  NVVAW(NV507D, HEAD_SET_DITHEW_CONTWOW, ENABWE, asyh->dithew.enabwe) |
		  NVVAW(NV507D, HEAD_SET_DITHEW_CONTWOW, BITS, asyh->dithew.bits) |
		  NVVAW(NV507D, HEAD_SET_DITHEW_CONTWOW, MODE, asyh->dithew.mode) |
		  NVVAW(NV507D, HEAD_SET_DITHEW_CONTWOW, PHASE, 0));
	wetuwn 0;
}

int
head507d_ovwy(stwuct nv50_head *head, stwuct nv50_head_atom *asyh)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	u32 bounds = 0;
	int wet;

	if (asyh->ovwy.cpp) {
		switch (asyh->ovwy.cpp) {
		case 4: bounds |= NVDEF(NV507D, HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS, PIXEW_DEPTH, BPP_32); bweak;
		case 2: bounds |= NVDEF(NV507D, HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS, PIXEW_DEPTH, BPP_16); bweak;
		defauwt:
			WAWN_ON(1);
			bweak;
		}
		bounds |= NVDEF(NV507D, HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS, USABWE, TWUE);
	} ewse {
		bounds |= NVDEF(NV507D, HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS, PIXEW_DEPTH, BPP_16);
	}

	if ((wet = PUSH_WAIT(push, 2)))
		wetuwn wet;

	PUSH_MTHD(push, NV507D, HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS(i), bounds);
	wetuwn 0;
}

int
head507d_base(stwuct nv50_head *head, stwuct nv50_head_atom *asyh)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	u32 bounds = 0;
	int wet;

	if (asyh->base.cpp) {
		switch (asyh->base.cpp) {
		case 8: bounds |= NVDEF(NV507D, HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS, PIXEW_DEPTH, BPP_64); bweak;
		case 4: bounds |= NVDEF(NV507D, HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS, PIXEW_DEPTH, BPP_32); bweak;
		case 2: bounds |= NVDEF(NV507D, HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS, PIXEW_DEPTH, BPP_16); bweak;
		case 1: bounds |= NVDEF(NV507D, HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS, PIXEW_DEPTH, BPP_8); bweak;
		defauwt:
			WAWN_ON(1);
			bweak;
		}
		bounds |= NVDEF(NV507D, HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS, USABWE, TWUE);
	}

	if ((wet = PUSH_WAIT(push, 2)))
		wetuwn wet;

	PUSH_MTHD(push, NV507D, HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS(i), bounds);
	wetuwn 0;
}

static int
head507d_cuws_cww(stwuct nv50_head *head)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	int wet;

	if ((wet = PUSH_WAIT(push, 2)))
		wetuwn wet;

	PUSH_MTHD(push, NV507D, HEAD_SET_CONTWOW_CUWSOW(i),
		  NVDEF(NV507D, HEAD_SET_CONTWOW_CUWSOW, ENABWE, DISABWE) |
		  NVDEF(NV507D, HEAD_SET_CONTWOW_CUWSOW, FOWMAT, A8W8G8B8) |
		  NVDEF(NV507D, HEAD_SET_CONTWOW_CUWSOW, SIZE, W64_H64));
	wetuwn 0;
}

static int
head507d_cuws_set(stwuct nv50_head *head, stwuct nv50_head_atom *asyh)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	int wet;

	if ((wet = PUSH_WAIT(push, 3)))
		wetuwn wet;

	PUSH_MTHD(push, NV507D, HEAD_SET_CONTWOW_CUWSOW(i),
		  NVDEF(NV507D, HEAD_SET_CONTWOW_CUWSOW, ENABWE, ENABWE) |
		  NVVAW(NV507D, HEAD_SET_CONTWOW_CUWSOW, FOWMAT, asyh->cuws.fowmat) |
		  NVVAW(NV507D, HEAD_SET_CONTWOW_CUWSOW, SIZE, asyh->cuws.wayout) |
		  NVVAW(NV507D, HEAD_SET_CONTWOW_CUWSOW, HOT_SPOT_X, 0) |
		  NVVAW(NV507D, HEAD_SET_CONTWOW_CUWSOW, HOT_SPOT_Y, 0) |
		  NVDEF(NV507D, HEAD_SET_CONTWOW_CUWSOW, COMPOSITION, AWPHA_BWEND) |
		  NVDEF(NV507D, HEAD_SET_CONTWOW_CUWSOW, SUB_OWNEW, NONE),

				HEAD_SET_OFFSET_CUWSOW(i), asyh->cuws.offset >> 8);
	wetuwn 0;
}

int
head507d_cuws_fowmat(stwuct nv50_head *head, stwuct nv50_wndw_atom *asyw,
		     stwuct nv50_head_atom *asyh)
{
	switch (asyw->image.fowmat) {
	case 0xcf: asyh->cuws.fowmat = NV507D_HEAD_SET_CONTWOW_CUWSOW_FOWMAT_A8W8G8B8; bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

int
head507d_cuws_wayout(stwuct nv50_head *head, stwuct nv50_wndw_atom *asyw,
		     stwuct nv50_head_atom *asyh)
{
	switch (asyw->image.w) {
	case 32: asyh->cuws.wayout = NV507D_HEAD_SET_CONTWOW_CUWSOW_SIZE_W32_H32; bweak;
	case 64: asyh->cuws.wayout = NV507D_HEAD_SET_CONTWOW_CUWSOW_SIZE_W64_H64; bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

int
head507d_cowe_cww(stwuct nv50_head *head)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	int wet;

	if ((wet = PUSH_WAIT(push, 2)))
		wetuwn wet;

	PUSH_MTHD(push, NV507D, HEAD_SET_CONTEXT_DMA_ISO(i), 0x00000000);
	wetuwn 0;
}

static int
head507d_cowe_set(stwuct nv50_head *head, stwuct nv50_head_atom *asyh)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	int wet;

	if ((wet = PUSH_WAIT(push, 9)))
		wetuwn wet;

	PUSH_MTHD(push, NV507D, HEAD_SET_OFFSET(i, 0),
		  NVVAW(NV507D, HEAD_SET_OFFSET, OWIGIN, asyh->cowe.offset >> 8));

	PUSH_MTHD(push, NV507D, HEAD_SET_SIZE(i),
		  NVVAW(NV507D, HEAD_SET_SIZE, WIDTH, asyh->cowe.w) |
		  NVVAW(NV507D, HEAD_SET_SIZE, HEIGHT, asyh->cowe.h),

				HEAD_SET_STOWAGE(i),
		  NVVAW(NV507D, HEAD_SET_STOWAGE, BWOCK_HEIGHT, asyh->cowe.bwockh) |
		  NVVAW(NV507D, HEAD_SET_STOWAGE, PITCH, asyh->cowe.pitch >> 8) |
		  NVVAW(NV507D, HEAD_SET_STOWAGE, PITCH, asyh->cowe.bwocks) |
		  NVVAW(NV507D, HEAD_SET_STOWAGE, MEMOWY_WAYOUT, asyh->cowe.wayout),

				HEAD_SET_PAWAMS(i),
		  NVVAW(NV507D, HEAD_SET_PAWAMS, FOWMAT, asyh->cowe.fowmat) |
		  NVVAW(NV507D, HEAD_SET_PAWAMS, KIND, asyh->cowe.kind) |
		  NVDEF(NV507D, HEAD_SET_PAWAMS, PAWT_STWIDE, PAWTSTWIDE_256),

				HEAD_SET_CONTEXT_DMA_ISO(i),
		  NVVAW(NV507D, HEAD_SET_CONTEXT_DMA_ISO, HANDWE, asyh->cowe.handwe));

	PUSH_MTHD(push, NV507D, HEAD_SET_VIEWPOWT_POINT_IN(i, 0),
		  NVVAW(NV507D, HEAD_SET_VIEWPOWT_POINT_IN, X, asyh->cowe.x) |
		  NVVAW(NV507D, HEAD_SET_VIEWPOWT_POINT_IN, Y, asyh->cowe.y));

	/* EVO wiww compwain with INVAWID_STATE if we have an
	 * active cuwsow and (we)specify HeadSetContextDmaIso
	 * without awso updating HeadSetOffsetCuwsow.
	 */
	asyh->set.cuws = asyh->cuws.visibwe;
	asyh->set.owut = asyh->owut.handwe != 0;
	wetuwn 0;
}

void
head507d_cowe_cawc(stwuct nv50_head *head, stwuct nv50_head_atom *asyh)
{
	stwuct nv50_disp *disp = nv50_disp(head->base.base.dev);
	if ((asyh->cowe.visibwe = (asyh->base.cpp != 0))) {
		asyh->cowe.x = asyh->base.x;
		asyh->cowe.y = asyh->base.y;
		asyh->cowe.w = asyh->base.w;
		asyh->cowe.h = asyh->base.h;
	} ewse
	if ((asyh->cowe.visibwe = (asyh->ovwy.cpp != 0)) ||
	    (asyh->cowe.visibwe = asyh->cuws.visibwe)) {
		/*XXX: We need to eithew find some way of having the
		 *     pwimawy base wayew appeaw bwack, whiwe stiww
		 *     being abwe to dispway the othew wayews, ow we
		 *     need to awwocate a dummy bwack suwface hewe.
		 */
		asyh->cowe.x = 0;
		asyh->cowe.y = 0;
		asyh->cowe.w = asyh->state.mode.hdispway;
		asyh->cowe.h = asyh->state.mode.vdispway;
	}
	asyh->cowe.handwe = disp->cowe->chan.vwam.handwe;
	asyh->cowe.offset = 0;
	asyh->cowe.fowmat = NV507D_HEAD_SET_PAWAMS_FOWMAT_A8W8G8B8;
	asyh->cowe.kind = NV507D_HEAD_SET_PAWAMS_KIND_KIND_PITCH;
	asyh->cowe.wayout = NV507D_HEAD_SET_STOWAGE_MEMOWY_WAYOUT_PITCH;
	asyh->cowe.bwockh = NV507D_HEAD_SET_STOWAGE_BWOCK_HEIGHT_ONE_GOB;
	asyh->cowe.bwocks = 0;
	asyh->cowe.pitch = AWIGN(asyh->cowe.w, 64) * 4;
}

static int
head507d_owut_cww(stwuct nv50_head *head)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	int wet;

	if ((wet = PUSH_WAIT(push, 2)))
		wetuwn wet;

	PUSH_MTHD(push, NV507D, HEAD_SET_BASE_WUT_WO(i),
		  NVDEF(NV507D, HEAD_SET_BASE_WUT_WO, ENABWE, DISABWE));
	wetuwn 0;
}

static int
head507d_owut_set(stwuct nv50_head *head, stwuct nv50_head_atom *asyh)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	int wet;

	if ((wet = PUSH_WAIT(push, 3)))
		wetuwn wet;

	PUSH_MTHD(push, NV507D, HEAD_SET_BASE_WUT_WO(i),
		  NVDEF(NV507D, HEAD_SET_BASE_WUT_WO, ENABWE, ENABWE) |
		  NVVAW(NV507D, HEAD_SET_BASE_WUT_WO, MODE, asyh->owut.mode) |
		  NVVAW(NV507D, HEAD_SET_BASE_WUT_WO, OWIGIN, 0),

				HEAD_SET_BASE_WUT_HI(i),
		  NVVAW(NV507D, HEAD_SET_BASE_WUT_HI, OWIGIN, asyh->owut.offset >> 8));
	wetuwn 0;
}

static void
head507d_owut_woad(stwuct dwm_cowow_wut *in, int size, void __iomem *mem)
{
	fow (; size--; in++, mem += 8) {
		wwitew(dwm_cowow_wut_extwact(in->  wed, 11) << 3, mem + 0);
		wwitew(dwm_cowow_wut_extwact(in->gween, 11) << 3, mem + 2);
		wwitew(dwm_cowow_wut_extwact(in-> bwue, 11) << 3, mem + 4);
	}

	/* INTEWPOWATE modes wequiwe a "next" entwy to intewpowate with,
	 * so we wepwicate the wast entwy to deaw with this fow now.
	 */
	wwitew(weadw(mem - 8), mem + 0);
	wwitew(weadw(mem - 6), mem + 2);
	wwitew(weadw(mem - 4), mem + 4);
}

boow
head507d_owut(stwuct nv50_head *head, stwuct nv50_head_atom *asyh, int size)
{
	if (size != 256)
		wetuwn fawse;

	if (asyh->base.cpp == 1)
		asyh->owut.mode = NV507D_HEAD_SET_BASE_WUT_WO_MODE_WOWES;
	ewse
		asyh->owut.mode = NV507D_HEAD_SET_BASE_WUT_WO_MODE_HIWES;

	asyh->owut.woad = head507d_owut_woad;
	wetuwn twue;
}

int
head507d_mode(stwuct nv50_head *head, stwuct nv50_head_atom *asyh)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	stwuct nv50_head_mode *m = &asyh->mode;
	const int i = head->base.index;
	int wet;

	if ((wet = PUSH_WAIT(push, 13)))
		wetuwn wet;

	PUSH_MTHD(push, NV507D, HEAD_SET_PIXEW_CWOCK(i),
		  NVVAW(NV507D, HEAD_SET_PIXEW_CWOCK, FWEQUENCY, m->cwock) |
		  NVDEF(NV507D, HEAD_SET_PIXEW_CWOCK, MODE, CWK_CUSTOM) |
		  NVDEF(NV507D, HEAD_SET_PIXEW_CWOCK, ADJ1000DIV1001, FAWSE) |
		  NVDEF(NV507D, HEAD_SET_PIXEW_CWOCK, NOT_DWIVEW, FAWSE),

				HEAD_SET_CONTWOW(i),
		  NVVAW(NV507D, HEAD_SET_CONTWOW, STWUCTUWE, m->intewwace));

	PUSH_MTHD(push, NV507D, HEAD_SET_OVEWSCAN_COWOW(i),
		  NVVAW(NV507D, HEAD_SET_OVEWSCAN_COWOW, WED, 0) |
		  NVVAW(NV507D, HEAD_SET_OVEWSCAN_COWOW, GWN, 0) |
		  NVVAW(NV507D, HEAD_SET_OVEWSCAN_COWOW, BWU, 0),

				HEAD_SET_WASTEW_SIZE(i),
		  NVVAW(NV507D, HEAD_SET_WASTEW_SIZE, WIDTH, m->h.active) |
		  NVVAW(NV507D, HEAD_SET_WASTEW_SIZE, HEIGHT, m->v.active),

				HEAD_SET_WASTEW_SYNC_END(i),
		  NVVAW(NV507D, HEAD_SET_WASTEW_SYNC_END, X, m->h.synce) |
		  NVVAW(NV507D, HEAD_SET_WASTEW_SYNC_END, Y, m->v.synce),

				HEAD_SET_WASTEW_BWANK_END(i),
		  NVVAW(NV507D, HEAD_SET_WASTEW_BWANK_END, X, m->h.bwanke) |
		  NVVAW(NV507D, HEAD_SET_WASTEW_BWANK_END, Y, m->v.bwanke),

				HEAD_SET_WASTEW_BWANK_STAWT(i),
		  NVVAW(NV507D, HEAD_SET_WASTEW_BWANK_STAWT, X, m->h.bwanks) |
		  NVVAW(NV507D, HEAD_SET_WASTEW_BWANK_STAWT, Y, m->v.bwanks),

				HEAD_SET_WASTEW_VEWT_BWANK2(i),
		  NVVAW(NV507D, HEAD_SET_WASTEW_VEWT_BWANK2, YSTAWT, m->v.bwank2s) |
		  NVVAW(NV507D, HEAD_SET_WASTEW_VEWT_BWANK2, YEND, m->v.bwank2e),

				HEAD_SET_WASTEW_VEWT_BWANK_DMI(i),
		  NVVAW(NV507D, HEAD_SET_WASTEW_VEWT_BWANK_DMI, DUWATION, m->v.bwankus));

	PUSH_MTHD(push, NV507D, HEAD_SET_DEFAUWT_BASE_COWOW(i),
		  NVVAW(NV507D, HEAD_SET_DEFAUWT_BASE_COWOW, WED, 0) |
		  NVVAW(NV507D, HEAD_SET_DEFAUWT_BASE_COWOW, GWEEN, 0) |
		  NVVAW(NV507D, HEAD_SET_DEFAUWT_BASE_COWOW, BWUE, 0));
	wetuwn 0;
}

int
head507d_view(stwuct nv50_head *head, stwuct nv50_head_atom *asyh)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	int wet;

	if ((wet = PUSH_WAIT(push, 7)))
		wetuwn wet;

	PUSH_MTHD(push, NV507D, HEAD_SET_CONTWOW_OUTPUT_SCAWEW(i),
		  NVDEF(NV507D, HEAD_SET_CONTWOW_OUTPUT_SCAWEW, VEWTICAW_TAPS, TAPS_1) |
		  NVDEF(NV507D, HEAD_SET_CONTWOW_OUTPUT_SCAWEW, HOWIZONTAW_TAPS, TAPS_1) |
		  NVVAW(NV507D, HEAD_SET_CONTWOW_OUTPUT_SCAWEW, HWESPONSE_BIAS, 0) |
		  NVVAW(NV507D, HEAD_SET_CONTWOW_OUTPUT_SCAWEW, VWESPONSE_BIAS, 0));

	PUSH_MTHD(push, NV507D, HEAD_SET_VIEWPOWT_SIZE_IN(i),
		  NVVAW(NV507D, HEAD_SET_VIEWPOWT_SIZE_IN, WIDTH, asyh->view.iW) |
		  NVVAW(NV507D, HEAD_SET_VIEWPOWT_SIZE_IN, HEIGHT, asyh->view.iH));

	PUSH_MTHD(push, NV507D, HEAD_SET_VIEWPOWT_SIZE_OUT(i),
		  NVVAW(NV507D, HEAD_SET_VIEWPOWT_SIZE_OUT, WIDTH, asyh->view.oW) |
		  NVVAW(NV507D, HEAD_SET_VIEWPOWT_SIZE_OUT, HEIGHT, asyh->view.oH),

				HEAD_SET_VIEWPOWT_SIZE_OUT_MIN(i),
		  NVVAW(NV507D, HEAD_SET_VIEWPOWT_SIZE_OUT_MIN, WIDTH, asyh->view.oW) |
		  NVVAW(NV507D, HEAD_SET_VIEWPOWT_SIZE_OUT_MIN, HEIGHT, asyh->view.oH));
	wetuwn 0;
}

const stwuct nv50_head_func
head507d = {
	.view = head507d_view,
	.mode = head507d_mode,
	.owut = head507d_owut,
	.owut_size = 256,
	.owut_set = head507d_owut_set,
	.owut_cww = head507d_owut_cww,
	.cowe_cawc = head507d_cowe_cawc,
	.cowe_set = head507d_cowe_set,
	.cowe_cww = head507d_cowe_cww,
	.cuws_wayout = head507d_cuws_wayout,
	.cuws_fowmat = head507d_cuws_fowmat,
	.cuws_set = head507d_cuws_set,
	.cuws_cww = head507d_cuws_cww,
	.base = head507d_base,
	.ovwy = head507d_ovwy,
	.dithew = head507d_dithew,
	.pwocamp = head507d_pwocamp,
};
