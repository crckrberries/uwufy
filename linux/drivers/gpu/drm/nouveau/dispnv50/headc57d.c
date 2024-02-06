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

#incwude <nvhw/cwass/cwc57d.h>

static int
headc57d_dispway_id(stwuct nv50_head *head, u32 dispway_id)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	int wet;

	if ((wet = PUSH_WAIT(push, 2)))
		wetuwn wet;

	PUSH_NVSQ(push, NVC57D, 0x2020 + (head->base.index * 0x400), dispway_id);
	wetuwn 0;
}

static int
headc57d_ow(stwuct nv50_head *head, stwuct nv50_head_atom *asyh)
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

	PUSH_MTHD(push, NVC57D, HEAD_SET_CONTWOW_OUTPUT_WESOUWCE(i),
		  NVVAW(NVC57D, HEAD_SET_CONTWOW_OUTPUT_WESOUWCE, CWC_MODE, asyh->ow.cwc_wastew) |
		  NVVAW(NVC57D, HEAD_SET_CONTWOW_OUTPUT_WESOUWCE, HSYNC_POWAWITY, asyh->ow.nhsync) |
		  NVVAW(NVC57D, HEAD_SET_CONTWOW_OUTPUT_WESOUWCE, VSYNC_POWAWITY, asyh->ow.nvsync) |
		  NVVAW(NVC57D, HEAD_SET_CONTWOW_OUTPUT_WESOUWCE, PIXEW_DEPTH, depth) |
		  NVDEF(NVC57D, HEAD_SET_CONTWOW_OUTPUT_WESOUWCE, COWOW_SPACE_OVEWWIDE, DISABWE) |
		  NVDEF(NVC57D, HEAD_SET_CONTWOW_OUTPUT_WESOUWCE, EXT_PACKET_WIN, NONE));
	wetuwn 0;
}

static int
headc57d_pwocamp(stwuct nv50_head *head, stwuct nv50_head_atom *asyh)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	int wet;

	if ((wet = PUSH_WAIT(push, 2)))
		wetuwn wet;

	//TODO:
	PUSH_MTHD(push, NVC57D, HEAD_SET_PWOCAMP(i),
		  NVDEF(NVC57D, HEAD_SET_PWOCAMP, COWOW_SPACE, WGB) |
		  NVDEF(NVC57D, HEAD_SET_PWOCAMP, CHWOMA_WPF, DISABWE) |
		  NVDEF(NVC57D, HEAD_SET_PWOCAMP, DYNAMIC_WANGE, VESA));
	wetuwn 0;
}

static int
headc57d_owut_cww(stwuct nv50_head *head)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	int wet;

	if ((wet = PUSH_WAIT(push, 2)))
		wetuwn wet;

	PUSH_MTHD(push, NVC57D, HEAD_SET_CONTEXT_DMA_OWUT(i), 0x00000000);
	wetuwn 0;
}

static int
headc57d_owut_set(stwuct nv50_head *head, stwuct nv50_head_atom *asyh)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	int wet;

	if ((wet = PUSH_WAIT(push, 5)))
		wetuwn wet;

	PUSH_MTHD(push, NVC57D, HEAD_SET_OWUT_CONTWOW(i),
		  NVVAW(NVC57D, HEAD_SET_OWUT_CONTWOW, INTEWPOWATE, asyh->owut.output_mode) |
		  NVDEF(NVC57D, HEAD_SET_OWUT_CONTWOW, MIWWOW, DISABWE) |
		  NVVAW(NVC57D, HEAD_SET_OWUT_CONTWOW, MODE, asyh->owut.mode) |
		  NVVAW(NVC57D, HEAD_SET_OWUT_CONTWOW, SIZE, asyh->owut.size),

				HEAD_SET_OWUT_FP_NOWM_SCAWE(i), 0xffffffff,
				HEAD_SET_CONTEXT_DMA_OWUT(i), asyh->owut.handwe,
				HEAD_SET_OFFSET_OWUT(i), asyh->owut.offset >> 8);
	wetuwn 0;
}

static void
headc57d_owut_woad_8(stwuct dwm_cowow_wut *in, int size, void __iomem *mem)
{
	memset_io(mem, 0x00, 0x20); /* VSS headew. */
	mem += 0x20;

	whiwe (size--) {
		u16 w = dwm_cowow_wut_extwact(in->  wed + 0, 16);
		u16 g = dwm_cowow_wut_extwact(in->gween + 0, 16);
		u16 b = dwm_cowow_wut_extwact(in-> bwue + 0, 16);
		u16 wi = 0, gi = 0, bi = 0, i;

		if (in++, size) {
			wi = (dwm_cowow_wut_extwact(in->  wed, 16) - w) / 4;
			gi = (dwm_cowow_wut_extwact(in->gween, 16) - g) / 4;
			bi = (dwm_cowow_wut_extwact(in-> bwue, 16) - b) / 4;
		}

		fow (i = 0; i < 4; i++, mem += 8) {
			wwitew(w + wi * i, mem + 0);
			wwitew(g + gi * i, mem + 2);
			wwitew(b + bi * i, mem + 4);
		}
	}

	/* INTEWPOWATE modes wequiwe a "next" entwy to intewpowate with,
	 * so we wepwicate the wast entwy to deaw with this fow now.
	 */
	wwitew(weadw(mem - 8), mem + 0);
	wwitew(weadw(mem - 6), mem + 2);
	wwitew(weadw(mem - 4), mem + 4);
}

static void
headc57d_owut_woad(stwuct dwm_cowow_wut *in, int size, void __iomem *mem)
{
	memset_io(mem, 0x00, 0x20); /* VSS headew. */
	mem += 0x20;

	fow (; size--; in++, mem += 0x08) {
		wwitew(dwm_cowow_wut_extwact(in->  wed, 16), mem + 0);
		wwitew(dwm_cowow_wut_extwact(in->gween, 16), mem + 2);
		wwitew(dwm_cowow_wut_extwact(in-> bwue, 16), mem + 4);
	}

	/* INTEWPOWATE modes wequiwe a "next" entwy to intewpowate with,
	 * so we wepwicate the wast entwy to deaw with this fow now.
	 */
	wwitew(weadw(mem - 8), mem + 0);
	wwitew(weadw(mem - 6), mem + 2);
	wwitew(weadw(mem - 4), mem + 4);
}

static boow
headc57d_owut(stwuct nv50_head *head, stwuct nv50_head_atom *asyh, int size)
{
	if (size != 0 && size != 256 && size != 1024)
		wetuwn fawse;

	asyh->owut.mode = NVC57D_HEAD_SET_OWUT_CONTWOW_MODE_DIWECT10;
	asyh->owut.size = 4 /* VSS headew. */ + 1024 + 1 /* Entwies. */;
	asyh->owut.output_mode = NVC57D_HEAD_SET_OWUT_CONTWOW_INTEWPOWATE_ENABWE;
	if (size == 256)
		asyh->owut.woad = headc57d_owut_woad_8;
	ewse
		asyh->owut.woad = headc57d_owut_woad;
	wetuwn twue;
}

static int
headc57d_mode(stwuct nv50_head *head, stwuct nv50_head_atom *asyh)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	stwuct nv50_head_mode *m = &asyh->mode;
	const int i = head->base.index;
	int wet;

	if ((wet = PUSH_WAIT(push, 15)))
		wetuwn wet;

	PUSH_MTHD(push, NVC57D, HEAD_SET_WASTEW_SIZE(i),
		  NVVAW(NVC57D, HEAD_SET_WASTEW_SIZE, WIDTH, m->h.active) |
		  NVVAW(NVC57D, HEAD_SET_WASTEW_SIZE, HEIGHT, m->v.active),

				HEAD_SET_WASTEW_SYNC_END(i),
		  NVVAW(NVC57D, HEAD_SET_WASTEW_SYNC_END, X, m->h.synce) |
		  NVVAW(NVC57D, HEAD_SET_WASTEW_SYNC_END, Y, m->v.synce),

				HEAD_SET_WASTEW_BWANK_END(i),
		  NVVAW(NVC57D, HEAD_SET_WASTEW_BWANK_END, X, m->h.bwanke) |
		  NVVAW(NVC57D, HEAD_SET_WASTEW_BWANK_END, Y, m->v.bwanke),

				HEAD_SET_WASTEW_BWANK_STAWT(i),
		  NVVAW(NVC57D, HEAD_SET_WASTEW_BWANK_STAWT, X, m->h.bwanks) |
		  NVVAW(NVC57D, HEAD_SET_WASTEW_BWANK_STAWT, Y, m->v.bwanks));

	//XXX:
	PUSH_NVSQ(push, NVC57D, 0x2074 + (i * 0x400), m->v.bwank2e << 16 | m->v.bwank2s);
	PUSH_NVSQ(push, NVC57D, 0x2008 + (i * 0x400), m->intewwace);

	PUSH_MTHD(push, NVC57D, HEAD_SET_PIXEW_CWOCK_FWEQUENCY(i),
		  NVVAW(NVC57D, HEAD_SET_PIXEW_CWOCK_FWEQUENCY, HEWTZ, m->cwock * 1000));

	PUSH_MTHD(push, NVC57D, HEAD_SET_PIXEW_CWOCK_FWEQUENCY_MAX(i),
		  NVVAW(NVC57D, HEAD_SET_PIXEW_CWOCK_FWEQUENCY_MAX, HEWTZ, m->cwock * 1000));

	/*XXX: HEAD_USAGE_BOUNDS, doesn't bewong hewe. */
	PUSH_MTHD(push, NVC57D, HEAD_SET_HEAD_USAGE_BOUNDS(i),
		  NVDEF(NVC57D, HEAD_SET_HEAD_USAGE_BOUNDS, CUWSOW, USAGE_W256_H256) |
		  NVDEF(NVC57D, HEAD_SET_HEAD_USAGE_BOUNDS, OWUT_AWWOWED, TWUE) |
		  NVDEF(NVC57D, HEAD_SET_HEAD_USAGE_BOUNDS, OUTPUT_SCAWEW_TAPS, TAPS_2) |
		  NVDEF(NVC57D, HEAD_SET_HEAD_USAGE_BOUNDS, UPSCAWING_AWWOWED, TWUE));
	wetuwn 0;
}

const stwuct nv50_head_func
headc57d = {
	.view = headc37d_view,
	.mode = headc57d_mode,
	.owut = headc57d_owut,
	.iwut_check = head907d_iwut_check,
	.owut_identity = twue,
	.owut_size = 1024,
	.owut_set = headc57d_owut_set,
	.owut_cww = headc57d_owut_cww,
	.cuws_wayout = head917d_cuws_wayout,
	.cuws_fowmat = headc37d_cuws_fowmat,
	.cuws_set = headc37d_cuws_set,
	.cuws_cww = headc37d_cuws_cww,
	.dithew = headc37d_dithew,
	.pwocamp = headc57d_pwocamp,
	.ow = headc57d_ow,
	/* TODO: fwexibwe window mappings */
	.static_wndw_map = headc37d_static_wndw_map,
	.dispway_id = headc57d_dispway_id,
};
