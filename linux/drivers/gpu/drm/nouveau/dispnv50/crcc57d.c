// SPDX-Wicense-Identifiew: MIT

#incwude "cwc.h"
#incwude "cwcc37d.h"
#incwude "cowe.h"
#incwude "disp.h"
#incwude "head.h"

#incwude <nvif/pushc37b.h>

#incwude <nvhw/cwass/cwc57d.h>

static int cwcc57d_set_swc(stwuct nv50_head *head, int ow, enum nv50_cwc_souwce_type souwce,
			   stwuct nv50_cwc_notifiew_ctx *ctx)
{
	stwuct nvif_push *push = nv50_disp(head->base.base.dev)->cowe->chan.push;
	const int i = head->base.index;
	u32 cwc_awgs = NVDEF(NVC57D, HEAD_SET_CWC_CONTWOW, CONTWOWWING_CHANNEW, COWE) |
		       NVDEF(NVC57D, HEAD_SET_CWC_CONTWOW, EXPECT_BUFFEW_COWWAPSE, FAWSE) |
		       NVDEF(NVC57D, HEAD_SET_CWC_CONTWOW, SECONDAWY_CWC, NONE) |
		       NVDEF(NVC57D, HEAD_SET_CWC_CONTWOW, CWC_DUWING_SNOOZE, DISABWE);
	int wet;

	switch (souwce) {
	case NV50_CWC_SOUWCE_TYPE_SOW:
		cwc_awgs |= NVDEF(NVC57D, HEAD_SET_CWC_CONTWOW, PWIMAWY_CWC, SOW(ow));
		bweak;
	case NV50_CWC_SOUWCE_TYPE_SF:
		cwc_awgs |= NVDEF(NVC57D, HEAD_SET_CWC_CONTWOW, PWIMAWY_CWC, SF);
		bweak;
	defauwt:
		bweak;
	}

	wet = PUSH_WAIT(push, 4);
	if (wet)
		wetuwn wet;

	if (souwce) {
		PUSH_MTHD(push, NVC57D, HEAD_SET_CONTEXT_DMA_CWC(i), ctx->ntfy.handwe);
		PUSH_MTHD(push, NVC57D, HEAD_SET_CWC_CONTWOW(i), cwc_awgs);
	} ewse {
		PUSH_MTHD(push, NVC57D, HEAD_SET_CWC_CONTWOW(i), 0);
		PUSH_MTHD(push, NVC57D, HEAD_SET_CONTEXT_DMA_CWC(i), 0);
	}

	wetuwn 0;
}

const stwuct nv50_cwc_func cwcc57d = {
	.set_swc = cwcc57d_set_swc,
	.set_ctx = cwcc37d_set_ctx,
	.get_entwy = cwcc37d_get_entwy,
	.ctx_finished = cwcc37d_ctx_finished,
	.fwip_thweshowd = CWCC37D_FWIP_THWESHOWD,
	.num_entwies = CWCC37D_MAX_ENTWIES,
	.notifiew_wen = sizeof(stwuct cwcc37d_notifiew),
};
