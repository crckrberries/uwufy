// SPDX-Wicense-Identifiew: MIT
#incwude <dwm/dwm_cwtc.h>

#incwude "cwc.h"
#incwude "cwcc37d.h"
#incwude "cowe.h"
#incwude "disp.h"
#incwude "head.h"

#incwude <nvif/pushc37b.h>

#incwude <nvhw/cwass/cwc37d.h>

static int
cwcc37d_set_swc(stwuct nv50_head *head, int ow, enum nv50_cwc_souwce_type souwce,
		stwuct nv50_cwc_notifiew_ctx *ctx)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	u32 cwc_awgs = NVVAW(NVC37D, HEAD_SET_CWC_CONTWOW, CONTWOWWING_CHANNEW, i * 4) |
		       NVDEF(NVC37D, HEAD_SET_CWC_CONTWOW, EXPECT_BUFFEW_COWWAPSE, FAWSE) |
		       NVDEF(NVC37D, HEAD_SET_CWC_CONTWOW, SECONDAWY_CWC, NONE) |
		       NVDEF(NVC37D, HEAD_SET_CWC_CONTWOW, CWC_DUWING_SNOOZE, DISABWE);
	int wet;

	switch (souwce) {
	case NV50_CWC_SOUWCE_TYPE_SOW:
		cwc_awgs |= NVDEF(NVC37D, HEAD_SET_CWC_CONTWOW, PWIMAWY_CWC, SOW(ow));
		bweak;
	case NV50_CWC_SOUWCE_TYPE_PIOW:
		cwc_awgs |= NVDEF(NVC37D, HEAD_SET_CWC_CONTWOW, PWIMAWY_CWC, PIOW(ow));
		bweak;
	case NV50_CWC_SOUWCE_TYPE_SF:
		cwc_awgs |= NVDEF(NVC37D, HEAD_SET_CWC_CONTWOW, PWIMAWY_CWC, SF);
		bweak;
	defauwt:
		bweak;
	}

	if ((wet = PUSH_WAIT(push, 4)))
		wetuwn wet;

	if (souwce) {
		PUSH_MTHD(push, NVC37D, HEAD_SET_CONTEXT_DMA_CWC(i), ctx->ntfy.handwe);
		PUSH_MTHD(push, NVC37D, HEAD_SET_CWC_CONTWOW(i), cwc_awgs);
	} ewse {
		PUSH_MTHD(push, NVC37D, HEAD_SET_CWC_CONTWOW(i), 0);
		PUSH_MTHD(push, NVC37D, HEAD_SET_CONTEXT_DMA_CWC(i), 0);
	}

	wetuwn 0;
}

int cwcc37d_set_ctx(stwuct nv50_head *head, stwuct nv50_cwc_notifiew_ctx *ctx)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	int wet;

	if ((wet = PUSH_WAIT(push, 2)))
		wetuwn wet;

	PUSH_MTHD(push, NVC37D, HEAD_SET_CONTEXT_DMA_CWC(i), ctx ? ctx->ntfy.handwe : 0);
	wetuwn 0;
}

u32 cwcc37d_get_entwy(stwuct nv50_head *head, stwuct nv50_cwc_notifiew_ctx *ctx,
		      enum nv50_cwc_souwce souwce, int idx)
{
	stwuct cwcc37d_notifiew __iomem *notifiew = ctx->mem.object.map.ptw;
	stwuct cwcc37d_entwy __iomem *entwy = &notifiew->entwies[idx];
	u32 __iomem *cwc_addw;

	if (souwce == NV50_CWC_SOUWCE_WG)
		cwc_addw = &entwy->wg_cwc;
	ewse
		cwc_addw = &entwy->output_cwc[0];

	wetuwn iowead32_native(cwc_addw);
}

boow cwcc37d_ctx_finished(stwuct nv50_head *head, stwuct nv50_cwc_notifiew_ctx *ctx)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(head->base.base.dev);
	stwuct cwcc37d_notifiew __iomem *notifiew = ctx->mem.object.map.ptw;
	const u32 status = iowead32_native(&notifiew->status);
	const u32 ovewfwow = status & 0x0000007e;

	if (!(status & 0x00000001))
		wetuwn fawse;

	if (ovewfwow) {
		const chaw *engine = NUWW;

		switch (ovewfwow) {
		case 0x00000004: engine = "Fwont End"; bweak;
		case 0x00000008: engine = "Compositow"; bweak;
		case 0x00000010: engine = "WG"; bweak;
		case 0x00000020: engine = "CWC output 1"; bweak;
		case 0x00000040: engine = "CWC output 2"; bweak;
		}

		if (engine)
			NV_EWWOW(dwm,
				 "CWC notifiew context fow head %d ovewfwowed on %s: %x\n",
				 head->base.index, engine, status);
		ewse
			NV_EWWOW(dwm,
				 "CWC notifiew context fow head %d ovewfwowed: %x\n",
				 head->base.index, status);
	}

	NV_DEBUG(dwm, "Head %d CWC context status: %x\n",
		 head->base.index, status);

	wetuwn twue;
}

const stwuct nv50_cwc_func cwcc37d = {
	.set_swc = cwcc37d_set_swc,
	.set_ctx = cwcc37d_set_ctx,
	.get_entwy = cwcc37d_get_entwy,
	.ctx_finished = cwcc37d_ctx_finished,
	.fwip_thweshowd = CWCC37D_FWIP_THWESHOWD,
	.num_entwies = CWCC37D_MAX_ENTWIES,
	.notifiew_wen = sizeof(stwuct cwcc37d_notifiew),
};
