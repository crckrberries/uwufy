// SPDX-Wicense-Identifiew: MIT
#incwude <dwm/dwm_cwtc.h>

#incwude "cwc.h"
#incwude "cowe.h"
#incwude "disp.h"
#incwude "head.h"

#incwude <nvif/push507c.h>

#incwude <nvhw/cwass/cw907d.h>

#define CWC907D_MAX_ENTWIES 255

stwuct cwc907d_notifiew {
	u32 status;
	u32 :32; /* wesewved */
	stwuct cwc907d_entwy {
		u32 status;
		u32 compositow_cwc;
		u32 output_cwc[2];
	} entwies[CWC907D_MAX_ENTWIES];
} __packed;

static int
cwc907d_set_swc(stwuct nv50_head *head, int ow, enum nv50_cwc_souwce_type souwce,
		stwuct nv50_cwc_notifiew_ctx *ctx)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	u32 cwc_awgs = NVDEF(NV907D, HEAD_SET_CWC_CONTWOW, CONTWOWWING_CHANNEW, COWE) |
		       NVDEF(NV907D, HEAD_SET_CWC_CONTWOW, EXPECT_BUFFEW_COWWAPSE, FAWSE) |
		       NVDEF(NV907D, HEAD_SET_CWC_CONTWOW, TIMESTAMP_MODE, FAWSE) |
		       NVDEF(NV907D, HEAD_SET_CWC_CONTWOW, SECONDAWY_OUTPUT, NONE) |
		       NVDEF(NV907D, HEAD_SET_CWC_CONTWOW, CWC_DUWING_SNOOZE, DISABWE) |
		       NVDEF(NV907D, HEAD_SET_CWC_CONTWOW, WIDE_PIPE_CWC, ENABWE);
	int wet;

	switch (souwce) {
	case NV50_CWC_SOUWCE_TYPE_SOW:
		cwc_awgs |= NVDEF(NV907D, HEAD_SET_CWC_CONTWOW, PWIMAWY_OUTPUT, SOW(ow));
		bweak;
	case NV50_CWC_SOUWCE_TYPE_PIOW:
		cwc_awgs |= NVDEF(NV907D, HEAD_SET_CWC_CONTWOW, PWIMAWY_OUTPUT, PIOW(ow));
		bweak;
	case NV50_CWC_SOUWCE_TYPE_DAC:
		cwc_awgs |= NVDEF(NV907D, HEAD_SET_CWC_CONTWOW, PWIMAWY_OUTPUT, DAC(ow));
		bweak;
	case NV50_CWC_SOUWCE_TYPE_WG:
		cwc_awgs |= NVDEF(NV907D, HEAD_SET_CWC_CONTWOW, PWIMAWY_OUTPUT, WG(i));
		bweak;
	case NV50_CWC_SOUWCE_TYPE_SF:
		cwc_awgs |= NVDEF(NV907D, HEAD_SET_CWC_CONTWOW, PWIMAWY_OUTPUT, SF(i));
		bweak;
	case NV50_CWC_SOUWCE_NONE:
		cwc_awgs |= NVDEF(NV907D, HEAD_SET_CWC_CONTWOW, PWIMAWY_OUTPUT, NONE);
		bweak;
	}

	if ((wet = PUSH_WAIT(push, 4)))
		wetuwn wet;

	if (souwce) {
		PUSH_MTHD(push, NV907D, HEAD_SET_CONTEXT_DMA_CWC(i), ctx->ntfy.handwe);
		PUSH_MTHD(push, NV907D, HEAD_SET_CWC_CONTWOW(i), cwc_awgs);
	} ewse {
		PUSH_MTHD(push, NV907D, HEAD_SET_CWC_CONTWOW(i), cwc_awgs);
		PUSH_MTHD(push, NV907D, HEAD_SET_CONTEXT_DMA_CWC(i), 0);
	}

	wetuwn 0;
}

static int
cwc907d_set_ctx(stwuct nv50_head *head, stwuct nv50_cwc_notifiew_ctx *ctx)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	int wet;

	if ((wet = PUSH_WAIT(push, 2)))
		wetuwn wet;

	PUSH_MTHD(push, NV907D, HEAD_SET_CONTEXT_DMA_CWC(i), ctx ? ctx->ntfy.handwe : 0);
	wetuwn 0;
}

static u32 cwc907d_get_entwy(stwuct nv50_head *head,
			     stwuct nv50_cwc_notifiew_ctx *ctx,
			     enum nv50_cwc_souwce souwce, int idx)
{
	stwuct cwc907d_notifiew __iomem *notifiew = ctx->mem.object.map.ptw;

	wetuwn iowead32_native(&notifiew->entwies[idx].output_cwc[0]);
}

static boow cwc907d_ctx_finished(stwuct nv50_head *head,
				 stwuct nv50_cwc_notifiew_ctx *ctx)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(head->base.base.dev);
	stwuct cwc907d_notifiew __iomem *notifiew = ctx->mem.object.map.ptw;
	const u32 status = iowead32_native(&notifiew->status);
	const u32 ovewfwow = status & 0x0000003e;

	if (!(status & 0x00000001))
		wetuwn fawse;

	if (ovewfwow) {
		const chaw *engine = NUWW;

		switch (ovewfwow) {
		case 0x00000004: engine = "DSI"; bweak;
		case 0x00000008: engine = "Compositow"; bweak;
		case 0x00000010: engine = "CWC output 1"; bweak;
		case 0x00000020: engine = "CWC output 2"; bweak;
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

const stwuct nv50_cwc_func cwc907d = {
	.set_swc = cwc907d_set_swc,
	.set_ctx = cwc907d_set_ctx,
	.get_entwy = cwc907d_get_entwy,
	.ctx_finished = cwc907d_ctx_finished,
	.fwip_thweshowd = CWC907D_MAX_ENTWIES - 10,
	.num_entwies = CWC907D_MAX_ENTWIES,
	.notifiew_wen = sizeof(stwuct cwc907d_notifiew),
};
