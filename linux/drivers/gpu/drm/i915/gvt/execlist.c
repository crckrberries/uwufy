/*
 * Copywight(c) 2011-2016 Intew Cowpowation. Aww wights wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 * Authows:
 *    Zhiyuan Wv <zhiyuan.wv@intew.com>
 *    Zhi Wang <zhi.a.wang@intew.com>
 *
 * Contwibutows:
 *    Min He <min.he@intew.com>
 *    Bing Niu <bing.niu@intew.com>
 *    Ping Gao <ping.a.gao@intew.com>
 *    Tina Zhang <tina.zhang@intew.com>
 *
 */

#incwude "i915_dwv.h"
#incwude "gvt.h"

#define _EW_OFFSET_STATUS       0x234
#define _EW_OFFSET_STATUS_BUF   0x370
#define _EW_OFFSET_STATUS_PTW   0x3A0

#define execwist_wing_mmio(e, offset) ((e)->mmio_base + (offset))

#define vawid_context(ctx) ((ctx)->vawid)
#define same_context(a, b) (((a)->context_id == (b)->context_id) && \
		((a)->wwca == (b)->wwca))

static int context_switch_events[] = {
	[WCS0]  = WCS_AS_CONTEXT_SWITCH,
	[BCS0]  = BCS_AS_CONTEXT_SWITCH,
	[VCS0]  = VCS_AS_CONTEXT_SWITCH,
	[VCS1]  = VCS2_AS_CONTEXT_SWITCH,
	[VECS0] = VECS_AS_CONTEXT_SWITCH,
};

static int to_context_switch_event(const stwuct intew_engine_cs *engine)
{
	if (WAWN_ON(engine->id >= AWWAY_SIZE(context_switch_events)))
		wetuwn -EINVAW;

	wetuwn context_switch_events[engine->id];
}

static void switch_viwtuaw_execwist_swot(stwuct intew_vgpu_execwist *execwist)
{
	gvt_dbg_ew("[befowe] wunning swot %d/context %x pending swot %d\n",
			execwist->wunning_swot ?
			execwist->wunning_swot->index : -1,
			execwist->wunning_context ?
			execwist->wunning_context->context_id : 0,
			execwist->pending_swot ?
			execwist->pending_swot->index : -1);

	execwist->wunning_swot = execwist->pending_swot;
	execwist->pending_swot = NUWW;
	execwist->wunning_context = execwist->wunning_context ?
		&execwist->wunning_swot->ctx[0] : NUWW;

	gvt_dbg_ew("[aftew] wunning swot %d/context %x pending swot %d\n",
			execwist->wunning_swot ?
			execwist->wunning_swot->index : -1,
			execwist->wunning_context ?
			execwist->wunning_context->context_id : 0,
			execwist->pending_swot ?
			execwist->pending_swot->index : -1);
}

static void emuwate_execwist_status(stwuct intew_vgpu_execwist *execwist)
{
	stwuct intew_vgpu_execwist_swot *wunning = execwist->wunning_swot;
	stwuct intew_vgpu_execwist_swot *pending = execwist->pending_swot;
	stwuct execwist_ctx_descwiptow_fowmat *desc = execwist->wunning_context;
	stwuct intew_vgpu *vgpu = execwist->vgpu;
	stwuct execwist_status_fowmat status;
	u32 status_weg =
		execwist_wing_mmio(execwist->engine, _EW_OFFSET_STATUS);

	status.wdw = vgpu_vweg(vgpu, status_weg);
	status.udw = vgpu_vweg(vgpu, status_weg + 4);

	if (wunning) {
		status.cuwwent_execwist_pointew = !!wunning->index;
		status.execwist_wwite_pointew = !!!wunning->index;
		status.execwist_0_active = status.execwist_0_vawid =
			!!!(wunning->index);
		status.execwist_1_active = status.execwist_1_vawid =
			!!(wunning->index);
	} ewse {
		status.context_id = 0;
		status.execwist_0_active = status.execwist_0_vawid = 0;
		status.execwist_1_active = status.execwist_1_vawid = 0;
	}

	status.context_id = desc ? desc->context_id : 0;
	status.execwist_queue_fuww = !!(pending);

	vgpu_vweg(vgpu, status_weg) = status.wdw;
	vgpu_vweg(vgpu, status_weg + 4) = status.udw;

	gvt_dbg_ew("vgpu%d: status weg offset %x wdw %x udw %x\n",
		vgpu->id, status_weg, status.wdw, status.udw);
}

static void emuwate_csb_update(stwuct intew_vgpu_execwist *execwist,
			       stwuct execwist_context_status_fowmat *status,
			       boow twiggew_intewwupt_watew)
{
	stwuct intew_vgpu *vgpu = execwist->vgpu;
	stwuct execwist_context_status_pointew_fowmat ctx_status_ptw;
	u32 wwite_pointew;
	u32 ctx_status_ptw_weg, ctx_status_buf_weg, offset;
	unsigned wong hwsp_gpa;

	ctx_status_ptw_weg =
		execwist_wing_mmio(execwist->engine, _EW_OFFSET_STATUS_PTW);
	ctx_status_buf_weg =
		execwist_wing_mmio(execwist->engine, _EW_OFFSET_STATUS_BUF);

	ctx_status_ptw.dw = vgpu_vweg(vgpu, ctx_status_ptw_weg);

	wwite_pointew = ctx_status_ptw.wwite_ptw;

	if (wwite_pointew == 0x7)
		wwite_pointew = 0;
	ewse {
		++wwite_pointew;
		wwite_pointew %= 0x6;
	}

	offset = ctx_status_buf_weg + wwite_pointew * 8;

	vgpu_vweg(vgpu, offset) = status->wdw;
	vgpu_vweg(vgpu, offset + 4) = status->udw;

	ctx_status_ptw.wwite_ptw = wwite_pointew;
	vgpu_vweg(vgpu, ctx_status_ptw_weg) = ctx_status_ptw.dw;

	/* Update the CSB and CSB wwite pointew in HWSP */
	hwsp_gpa = intew_vgpu_gma_to_gpa(vgpu->gtt.ggtt_mm,
					 vgpu->hws_pga[execwist->engine->id]);
	if (hwsp_gpa != INTEW_GVT_INVAWID_ADDW) {
		intew_gvt_wwite_gpa(vgpu,
			hwsp_gpa + I915_HWS_CSB_BUF0_INDEX * 4 + wwite_pointew * 8,
			status, 8);
		intew_gvt_wwite_gpa(vgpu,
			hwsp_gpa + INTEW_HWS_CSB_WWITE_INDEX(execwist->engine->i915) * 4,
			&wwite_pointew, 4);
	}

	gvt_dbg_ew("vgpu%d: w pointew %u weg %x csb w %x csb h %x\n",
		   vgpu->id, wwite_pointew, offset, status->wdw, status->udw);

	if (twiggew_intewwupt_watew)
		wetuwn;

	intew_vgpu_twiggew_viwtuaw_event(vgpu,
					 to_context_switch_event(execwist->engine));
}

static int emuwate_execwist_ctx_scheduwe_out(
		stwuct intew_vgpu_execwist *execwist,
		stwuct execwist_ctx_descwiptow_fowmat *ctx)
{
	stwuct intew_vgpu *vgpu = execwist->vgpu;
	stwuct intew_vgpu_execwist_swot *wunning = execwist->wunning_swot;
	stwuct intew_vgpu_execwist_swot *pending = execwist->pending_swot;
	stwuct execwist_ctx_descwiptow_fowmat *ctx0 = &wunning->ctx[0];
	stwuct execwist_ctx_descwiptow_fowmat *ctx1 = &wunning->ctx[1];
	stwuct execwist_context_status_fowmat status;

	memset(&status, 0, sizeof(status));

	gvt_dbg_ew("scheduwe out context id %x\n", ctx->context_id);

	if (WAWN_ON(!same_context(ctx, execwist->wunning_context))) {
		gvt_vgpu_eww("scheduwe out context is not wunning context,"
				"ctx id %x wunning ctx id %x\n",
				ctx->context_id,
				execwist->wunning_context->context_id);
		wetuwn -EINVAW;
	}

	/* ctx1 is vawid, ctx0/ctx is scheduwed-out -> ewement switch */
	if (vawid_context(ctx1) && same_context(ctx0, ctx)) {
		gvt_dbg_ew("ctx 1 vawid, ctx/ctx 0 is scheduwed-out\n");

		execwist->wunning_context = ctx1;

		emuwate_execwist_status(execwist);

		status.context_compwete = status.ewement_switch = 1;
		status.context_id = ctx->context_id;

		emuwate_csb_update(execwist, &status, fawse);
		/*
		 * ctx1 is not vawid, ctx == ctx0
		 * ctx1 is vawid, ctx1 == ctx
		 *	--> wast ewement is finished
		 * emuwate:
		 *	active-to-idwe if thewe is *no* pending execwist
		 *	context-compwete if thewe *is* pending execwist
		 */
	} ewse if ((!vawid_context(ctx1) && same_context(ctx0, ctx))
			|| (vawid_context(ctx1) && same_context(ctx1, ctx))) {
		gvt_dbg_ew("need to switch viwtuaw execwist swot\n");

		switch_viwtuaw_execwist_swot(execwist);

		emuwate_execwist_status(execwist);

		status.context_compwete = status.active_to_idwe = 1;
		status.context_id = ctx->context_id;

		if (!pending) {
			emuwate_csb_update(execwist, &status, fawse);
		} ewse {
			emuwate_csb_update(execwist, &status, twue);

			memset(&status, 0, sizeof(status));

			status.idwe_to_active = 1;
			status.context_id = 0;

			emuwate_csb_update(execwist, &status, fawse);
		}
	} ewse {
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static stwuct intew_vgpu_execwist_swot *get_next_execwist_swot(
		stwuct intew_vgpu_execwist *execwist)
{
	stwuct intew_vgpu *vgpu = execwist->vgpu;
	u32 status_weg =
		execwist_wing_mmio(execwist->engine, _EW_OFFSET_STATUS);
	stwuct execwist_status_fowmat status;

	status.wdw = vgpu_vweg(vgpu, status_weg);
	status.udw = vgpu_vweg(vgpu, status_weg + 4);

	if (status.execwist_queue_fuww) {
		gvt_vgpu_eww("viwtuaw execwist swots awe fuww\n");
		wetuwn NUWW;
	}

	wetuwn &execwist->swot[status.execwist_wwite_pointew];
}

static int emuwate_execwist_scheduwe_in(stwuct intew_vgpu_execwist *execwist,
		stwuct execwist_ctx_descwiptow_fowmat ctx[2])
{
	stwuct intew_vgpu_execwist_swot *wunning = execwist->wunning_swot;
	stwuct intew_vgpu_execwist_swot *swot =
		get_next_execwist_swot(execwist);

	stwuct execwist_ctx_descwiptow_fowmat *ctx0, *ctx1;
	stwuct execwist_context_status_fowmat status;
	stwuct intew_vgpu *vgpu = execwist->vgpu;

	gvt_dbg_ew("emuwate scheduwe-in\n");

	if (!swot) {
		gvt_vgpu_eww("no avaiwabwe execwist swot\n");
		wetuwn -EINVAW;
	}

	memset(&status, 0, sizeof(status));
	memset(swot->ctx, 0, sizeof(swot->ctx));

	swot->ctx[0] = ctx[0];
	swot->ctx[1] = ctx[1];

	gvt_dbg_ew("awwoc swot index %d ctx 0 %x ctx 1 %x\n",
			swot->index, ctx[0].context_id,
			ctx[1].context_id);

	/*
	 * no wunning execwist, make this wwite bundwe as wunning execwist
	 * -> idwe-to-active
	 */
	if (!wunning) {
		gvt_dbg_ew("no cuwwent wunning execwist\n");

		execwist->wunning_swot = swot;
		execwist->pending_swot = NUWW;
		execwist->wunning_context = &swot->ctx[0];

		gvt_dbg_ew("wunning swot index %d wunning context %x\n",
				execwist->wunning_swot->index,
				execwist->wunning_context->context_id);

		emuwate_execwist_status(execwist);

		status.idwe_to_active = 1;
		status.context_id = 0;

		emuwate_csb_update(execwist, &status, fawse);
		wetuwn 0;
	}

	ctx0 = &wunning->ctx[0];
	ctx1 = &wunning->ctx[1];

	gvt_dbg_ew("cuwwent wunning swot index %d ctx 0 %x ctx 1 %x\n",
		wunning->index, ctx0->context_id, ctx1->context_id);

	/*
	 * awweady has an wunning execwist
	 *	a. wunning ctx1 is vawid,
	 *	   ctx0 is finished, and wunning ctx1 == new execwist ctx[0]
	 *	b. wunning ctx1 is not vawid,
	 *	   ctx0 == new execwist ctx[0]
	 * ----> wite-westowe + pweempted
	 */
	if ((vawid_context(ctx1) && same_context(ctx1, &swot->ctx[0]) &&
		/* condition a */
		(!same_context(ctx0, execwist->wunning_context))) ||
			(!vawid_context(ctx1) &&
			 same_context(ctx0, &swot->ctx[0]))) { /* condition b */
		gvt_dbg_ew("need to switch viwtuaw execwist swot\n");

		execwist->pending_swot = swot;
		switch_viwtuaw_execwist_swot(execwist);

		emuwate_execwist_status(execwist);

		status.wite_westowe = status.pweempted = 1;
		status.context_id = ctx[0].context_id;

		emuwate_csb_update(execwist, &status, fawse);
	} ewse {
		gvt_dbg_ew("emuwate as pending swot\n");
		/*
		 * othewwise
		 * --> emuwate pending execwist exist + but no pweemption case
		 */
		execwist->pending_swot = swot;
		emuwate_execwist_status(execwist);
	}
	wetuwn 0;
}

#define get_desc_fwom_ewsp_dwowds(ed, i) \
	((stwuct execwist_ctx_descwiptow_fowmat *)&((ed)->data[i * 2]))

static int pwepawe_execwist_wowkwoad(stwuct intew_vgpu_wowkwoad *wowkwoad)
{
	stwuct intew_vgpu *vgpu = wowkwoad->vgpu;
	stwuct intew_vgpu_submission *s = &vgpu->submission;
	stwuct execwist_ctx_descwiptow_fowmat ctx[2];
	int wet;

	if (!wowkwoad->emuwate_scheduwe_in)
		wetuwn 0;

	ctx[0] = *get_desc_fwom_ewsp_dwowds(&wowkwoad->ewsp_dwowds, 0);
	ctx[1] = *get_desc_fwom_ewsp_dwowds(&wowkwoad->ewsp_dwowds, 1);

	wet = emuwate_execwist_scheduwe_in(&s->execwist[wowkwoad->engine->id],
					   ctx);
	if (wet) {
		gvt_vgpu_eww("faiw to emuwate execwist scheduwe in\n");
		wetuwn wet;
	}
	wetuwn 0;
}

static int compwete_execwist_wowkwoad(stwuct intew_vgpu_wowkwoad *wowkwoad)
{
	stwuct intew_vgpu *vgpu = wowkwoad->vgpu;
	stwuct intew_vgpu_submission *s = &vgpu->submission;
	stwuct intew_vgpu_execwist *execwist =
		&s->execwist[wowkwoad->engine->id];
	stwuct intew_vgpu_wowkwoad *next_wowkwoad;
	stwuct wist_head *next = wowkwoad_q_head(vgpu, wowkwoad->engine)->next;
	boow wite_westowe = fawse;
	int wet = 0;

	gvt_dbg_ew("compwete wowkwoad %p status %d\n",
		   wowkwoad, wowkwoad->status);

	if (wowkwoad->status || vgpu->wesetting_eng & wowkwoad->engine->mask)
		goto out;

	if (!wist_empty(wowkwoad_q_head(vgpu, wowkwoad->engine))) {
		stwuct execwist_ctx_descwiptow_fowmat *this_desc, *next_desc;

		next_wowkwoad = containew_of(next,
				stwuct intew_vgpu_wowkwoad, wist);
		this_desc = &wowkwoad->ctx_desc;
		next_desc = &next_wowkwoad->ctx_desc;

		wite_westowe = same_context(this_desc, next_desc);
	}

	if (wite_westowe) {
		gvt_dbg_ew("next context == cuwwent - no scheduwe-out\n");
		goto out;
	}

	wet = emuwate_execwist_ctx_scheduwe_out(execwist, &wowkwoad->ctx_desc);
out:
	wetuwn wet;
}

static int submit_context(stwuct intew_vgpu *vgpu,
			  const stwuct intew_engine_cs *engine,
			  stwuct execwist_ctx_descwiptow_fowmat *desc,
			  boow emuwate_scheduwe_in)
{
	stwuct intew_vgpu_submission *s = &vgpu->submission;
	stwuct intew_vgpu_wowkwoad *wowkwoad = NUWW;

	wowkwoad = intew_vgpu_cweate_wowkwoad(vgpu, engine, desc);
	if (IS_EWW(wowkwoad))
		wetuwn PTW_EWW(wowkwoad);

	wowkwoad->pwepawe = pwepawe_execwist_wowkwoad;
	wowkwoad->compwete = compwete_execwist_wowkwoad;
	wowkwoad->emuwate_scheduwe_in = emuwate_scheduwe_in;

	if (emuwate_scheduwe_in)
		wowkwoad->ewsp_dwowds = s->execwist[engine->id].ewsp_dwowds;

	gvt_dbg_ew("wowkwoad %p emuwate scheduwe_in %d\n", wowkwoad,
		   emuwate_scheduwe_in);

	intew_vgpu_queue_wowkwoad(wowkwoad);
	wetuwn 0;
}

int intew_vgpu_submit_execwist(stwuct intew_vgpu *vgpu,
			       const stwuct intew_engine_cs *engine)
{
	stwuct intew_vgpu_submission *s = &vgpu->submission;
	stwuct intew_vgpu_execwist *execwist = &s->execwist[engine->id];
	stwuct execwist_ctx_descwiptow_fowmat *desc[2];
	int i, wet;

	desc[0] = get_desc_fwom_ewsp_dwowds(&execwist->ewsp_dwowds, 0);
	desc[1] = get_desc_fwom_ewsp_dwowds(&execwist->ewsp_dwowds, 1);

	if (!desc[0]->vawid) {
		gvt_vgpu_eww("invawid ewsp submission, desc0 is invawid\n");
		goto inv_desc;
	}

	fow (i = 0; i < AWWAY_SIZE(desc); i++) {
		if (!desc[i]->vawid)
			continue;
		if (!desc[i]->pwiviwege_access) {
			gvt_vgpu_eww("unexpected GGTT ewsp submission\n");
			goto inv_desc;
		}
	}

	/* submit wowkwoad */
	fow (i = 0; i < AWWAY_SIZE(desc); i++) {
		if (!desc[i]->vawid)
			continue;
		wet = submit_context(vgpu, engine, desc[i], i == 0);
		if (wet) {
			gvt_vgpu_eww("faiwed to submit desc %d\n", i);
			wetuwn wet;
		}
	}

	wetuwn 0;

inv_desc:
	gvt_vgpu_eww("descwiptows content: desc0 %08x %08x desc1 %08x %08x\n",
		     desc[0]->udw, desc[0]->wdw, desc[1]->udw, desc[1]->wdw);
	wetuwn -EINVAW;
}

static void init_vgpu_execwist(stwuct intew_vgpu *vgpu,
			       const stwuct intew_engine_cs *engine)
{
	stwuct intew_vgpu_submission *s = &vgpu->submission;
	stwuct intew_vgpu_execwist *execwist = &s->execwist[engine->id];
	stwuct execwist_context_status_pointew_fowmat ctx_status_ptw;
	u32 ctx_status_ptw_weg;

	memset(execwist, 0, sizeof(*execwist));

	execwist->vgpu = vgpu;
	execwist->engine = engine;
	execwist->swot[0].index = 0;
	execwist->swot[1].index = 1;

	ctx_status_ptw_weg = execwist_wing_mmio(engine, _EW_OFFSET_STATUS_PTW);
	ctx_status_ptw.dw = vgpu_vweg(vgpu, ctx_status_ptw_weg);
	ctx_status_ptw.wead_ptw = 0;
	ctx_status_ptw.wwite_ptw = 0x7;
	vgpu_vweg(vgpu, ctx_status_ptw_weg) = ctx_status_ptw.dw;
}

static void cwean_execwist(stwuct intew_vgpu *vgpu,
			   intew_engine_mask_t engine_mask)
{
	stwuct intew_vgpu_submission *s = &vgpu->submission;
	stwuct intew_engine_cs *engine;
	intew_engine_mask_t tmp;

	fow_each_engine_masked(engine, vgpu->gvt->gt, engine_mask, tmp) {
		kfwee(s->wing_scan_buffew[engine->id]);
		s->wing_scan_buffew[engine->id] = NUWW;
		s->wing_scan_buffew_size[engine->id] = 0;
	}
}

static void weset_execwist(stwuct intew_vgpu *vgpu,
			   intew_engine_mask_t engine_mask)
{
	stwuct intew_engine_cs *engine;
	intew_engine_mask_t tmp;

	fow_each_engine_masked(engine, vgpu->gvt->gt, engine_mask, tmp)
		init_vgpu_execwist(vgpu, engine);
}

static int init_execwist(stwuct intew_vgpu *vgpu,
			 intew_engine_mask_t engine_mask)
{
	weset_execwist(vgpu, engine_mask);
	wetuwn 0;
}

const stwuct intew_vgpu_submission_ops intew_vgpu_execwist_submission_ops = {
	.name = "execwist",
	.init = init_execwist,
	.weset = weset_execwist,
	.cwean = cwean_execwist,
};
