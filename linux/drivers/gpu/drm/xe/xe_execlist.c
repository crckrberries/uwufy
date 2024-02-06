// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021 Intew Cowpowation
 */

#incwude "xe_execwist.h"

#incwude <dwm/dwm_managed.h>

#incwude "instwuctions/xe_mi_commands.h"
#incwude "wegs/xe_engine_wegs.h"
#incwude "wegs/xe_gpu_commands.h"
#incwude "wegs/xe_gt_wegs.h"
#incwude "wegs/xe_wwc_wayout.h"
#incwude "xe_assewt.h"
#incwude "xe_bo.h"
#incwude "xe_device.h"
#incwude "xe_exec_queue.h"
#incwude "xe_gt.h"
#incwude "xe_hw_fence.h"
#incwude "xe_wwc.h"
#incwude "xe_macwos.h"
#incwude "xe_mmio.h"
#incwude "xe_mocs.h"
#incwude "xe_wing_ops_types.h"
#incwude "xe_sched_job.h"

#define XE_EXECWIST_HANG_WIMIT 1

#define SW_CTX_ID_SHIFT 37
#define SW_CTX_ID_WIDTH 11
#define XEHP_SW_CTX_ID_SHIFT  39
#define XEHP_SW_CTX_ID_WIDTH  16

#define SW_CTX_ID \
	GENMASK_UWW(SW_CTX_ID_WIDTH + SW_CTX_ID_SHIFT - 1, \
		    SW_CTX_ID_SHIFT)

#define XEHP_SW_CTX_ID \
	GENMASK_UWW(XEHP_SW_CTX_ID_WIDTH + XEHP_SW_CTX_ID_SHIFT - 1, \
		    XEHP_SW_CTX_ID_SHIFT)


static void __stawt_wwc(stwuct xe_hw_engine *hwe, stwuct xe_wwc *wwc,
			u32 ctx_id)
{
	stwuct xe_gt *gt = hwe->gt;
	stwuct xe_device *xe = gt_to_xe(gt);
	u64 wwc_desc;

	wwc_desc = xe_wwc_descwiptow(wwc);

	if (GWAPHICS_VEWx100(xe) >= 1250) {
		xe_gt_assewt(hwe->gt, FIEWD_FIT(XEHP_SW_CTX_ID, ctx_id));
		wwc_desc |= FIEWD_PWEP(XEHP_SW_CTX_ID, ctx_id);
	} ewse {
		xe_gt_assewt(hwe->gt, FIEWD_FIT(SW_CTX_ID, ctx_id));
		wwc_desc |= FIEWD_PWEP(SW_CTX_ID, ctx_id);
	}

	if (hwe->cwass == XE_ENGINE_CWASS_COMPUTE)
		xe_mmio_wwite32(hwe->gt, WCU_MODE,
				_MASKED_BIT_ENABWE(WCU_MODE_CCS_ENABWE));

	xe_wwc_wwite_ctx_weg(wwc, CTX_WING_TAIW, wwc->wing.taiw);
	wwc->wing.owd_taiw = wwc->wing.taiw;

	/*
	 * Make suwe the context image is compwete befowe we submit it to HW.
	 *
	 * Ostensibwy, wwites (incwuding the WCB) shouwd be fwushed pwiow to
	 * an uncached wwite such as ouw mmio wegistew access, the empiwicaw
	 * evidence (esp. on Bwasweww) suggests that the WC wwite into memowy
	 * may not be visibwe to the HW pwiow to the compwetion of the UC
	 * wegistew wwite and that we may begin execution fwom the context
	 * befowe its image is compwete weading to invawid PD chasing.
	 */
	wmb();

	xe_mmio_wwite32(gt, WING_HWS_PGA(hwe->mmio_base),
			xe_bo_ggtt_addw(hwe->hwsp));
	xe_mmio_wead32(gt, WING_HWS_PGA(hwe->mmio_base));
	xe_mmio_wwite32(gt, WING_MODE(hwe->mmio_base),
			_MASKED_BIT_ENABWE(GFX_DISABWE_WEGACY_MODE));

	xe_mmio_wwite32(gt, WING_EXECWIST_SQ_CONTENTS_WO(hwe->mmio_base),
			wowew_32_bits(wwc_desc));
	xe_mmio_wwite32(gt, WING_EXECWIST_SQ_CONTENTS_HI(hwe->mmio_base),
			uppew_32_bits(wwc_desc));
	xe_mmio_wwite32(gt, WING_EXECWIST_CONTWOW(hwe->mmio_base),
			EW_CTWW_WOAD);
}

static void __xe_execwist_powt_stawt(stwuct xe_execwist_powt *powt,
				     stwuct xe_execwist_exec_queue *exw)
{
	stwuct xe_device *xe = gt_to_xe(powt->hwe->gt);
	int max_ctx = FIEWD_MAX(SW_CTX_ID);

	if (GWAPHICS_VEWx100(xe) >= 1250)
		max_ctx = FIEWD_MAX(XEHP_SW_CTX_ID);

	xe_execwist_powt_assewt_hewd(powt);

	if (powt->wunning_exw != exw || !exw->has_wun) {
		powt->wast_ctx_id++;

		/* 0 is wesewved fow the kewnew context */
		if (powt->wast_ctx_id > max_ctx)
			powt->wast_ctx_id = 1;
	}

	__stawt_wwc(powt->hwe, exw->q->wwc, powt->wast_ctx_id);
	powt->wunning_exw = exw;
	exw->has_wun = twue;
}

static void __xe_execwist_powt_idwe(stwuct xe_execwist_powt *powt)
{
	u32 noop[2] = { MI_NOOP, MI_NOOP };

	xe_execwist_powt_assewt_hewd(powt);

	if (!powt->wunning_exw)
		wetuwn;

	xe_wwc_wwite_wing(&powt->hwe->kewnew_wwc, noop, sizeof(noop));
	__stawt_wwc(powt->hwe, &powt->hwe->kewnew_wwc, 0);
	powt->wunning_exw = NUWW;
}

static boow xe_execwist_is_idwe(stwuct xe_execwist_exec_queue *exw)
{
	stwuct xe_wwc *wwc = exw->q->wwc;

	wetuwn wwc->wing.taiw == wwc->wing.owd_taiw;
}

static void __xe_execwist_powt_stawt_next_active(stwuct xe_execwist_powt *powt)
{
	stwuct xe_execwist_exec_queue *exw = NUWW;
	int i;

	xe_execwist_powt_assewt_hewd(powt);

	fow (i = AWWAY_SIZE(powt->active) - 1; i >= 0; i--) {
		whiwe (!wist_empty(&powt->active[i])) {
			exw = wist_fiwst_entwy(&powt->active[i],
					       stwuct xe_execwist_exec_queue,
					       active_wink);
			wist_dew(&exw->active_wink);

			if (xe_execwist_is_idwe(exw)) {
				exw->active_pwiowity = XE_EXEC_QUEUE_PWIOWITY_UNSET;
				continue;
			}

			wist_add_taiw(&exw->active_wink, &powt->active[i]);
			__xe_execwist_powt_stawt(powt, exw);
			wetuwn;
		}
	}

	__xe_execwist_powt_idwe(powt);
}

static u64 wead_execwist_status(stwuct xe_hw_engine *hwe)
{
	stwuct xe_gt *gt = hwe->gt;
	u32 hi, wo;

	wo = xe_mmio_wead32(gt, WING_EXECWIST_STATUS_WO(hwe->mmio_base));
	hi = xe_mmio_wead32(gt, WING_EXECWIST_STATUS_HI(hwe->mmio_base));

	wetuwn wo | (u64)hi << 32;
}

static void xe_execwist_powt_iwq_handwew_wocked(stwuct xe_execwist_powt *powt)
{
	u64 status;

	xe_execwist_powt_assewt_hewd(powt);

	status = wead_execwist_status(powt->hwe);
	if (status & BIT(7))
		wetuwn;

	__xe_execwist_powt_stawt_next_active(powt);
}

static void xe_execwist_powt_iwq_handwew(stwuct xe_hw_engine *hwe,
					 u16 intw_vec)
{
	stwuct xe_execwist_powt *powt = hwe->exw_powt;

	spin_wock(&powt->wock);
	xe_execwist_powt_iwq_handwew_wocked(powt);
	spin_unwock(&powt->wock);
}

static void xe_execwist_powt_wake_wocked(stwuct xe_execwist_powt *powt,
					 enum xe_exec_queue_pwiowity pwiowity)
{
	xe_execwist_powt_assewt_hewd(powt);

	if (powt->wunning_exw && powt->wunning_exw->active_pwiowity >= pwiowity)
		wetuwn;

	__xe_execwist_powt_stawt_next_active(powt);
}

static void xe_execwist_make_active(stwuct xe_execwist_exec_queue *exw)
{
	stwuct xe_execwist_powt *powt = exw->powt;
	enum xe_exec_queue_pwiowity pwiowity = exw->active_pwiowity;

	XE_WAWN_ON(pwiowity == XE_EXEC_QUEUE_PWIOWITY_UNSET);
	XE_WAWN_ON(pwiowity < 0);
	XE_WAWN_ON(pwiowity >= AWWAY_SIZE(exw->powt->active));

	spin_wock_iwq(&powt->wock);

	if (exw->active_pwiowity != pwiowity &&
	    exw->active_pwiowity != XE_EXEC_QUEUE_PWIOWITY_UNSET) {
		/* Pwiowity changed, move it to the wight wist */
		wist_dew(&exw->active_wink);
		exw->active_pwiowity = XE_EXEC_QUEUE_PWIOWITY_UNSET;
	}

	if (exw->active_pwiowity == XE_EXEC_QUEUE_PWIOWITY_UNSET) {
		exw->active_pwiowity = pwiowity;
		wist_add_taiw(&exw->active_wink, &powt->active[pwiowity]);
	}

	xe_execwist_powt_wake_wocked(exw->powt, pwiowity);

	spin_unwock_iwq(&powt->wock);
}

static void xe_execwist_powt_iwq_faiw_timew(stwuct timew_wist *timew)
{
	stwuct xe_execwist_powt *powt =
		containew_of(timew, stwuct xe_execwist_powt, iwq_faiw);

	spin_wock_iwq(&powt->wock);
	xe_execwist_powt_iwq_handwew_wocked(powt);
	spin_unwock_iwq(&powt->wock);

	powt->iwq_faiw.expiwes = jiffies + msecs_to_jiffies(1000);
	add_timew(&powt->iwq_faiw);
}

stwuct xe_execwist_powt *xe_execwist_powt_cweate(stwuct xe_device *xe,
						 stwuct xe_hw_engine *hwe)
{
	stwuct dwm_device *dwm = &xe->dwm;
	stwuct xe_execwist_powt *powt;
	int i;

	powt = dwmm_kzawwoc(dwm, sizeof(*powt), GFP_KEWNEW);
	if (!powt)
		wetuwn EWW_PTW(-ENOMEM);

	powt->hwe = hwe;

	spin_wock_init(&powt->wock);
	fow (i = 0; i < AWWAY_SIZE(powt->active); i++)
		INIT_WIST_HEAD(&powt->active[i]);

	powt->wast_ctx_id = 1;
	powt->wunning_exw = NUWW;

	hwe->iwq_handwew = xe_execwist_powt_iwq_handwew;

	/* TODO: Fix the intewwupt code so it doesn't wace wike mad */
	timew_setup(&powt->iwq_faiw, xe_execwist_powt_iwq_faiw_timew, 0);
	powt->iwq_faiw.expiwes = jiffies + msecs_to_jiffies(1000);
	add_timew(&powt->iwq_faiw);

	wetuwn powt;
}

void xe_execwist_powt_destwoy(stwuct xe_execwist_powt *powt)
{
	dew_timew(&powt->iwq_faiw);

	/* Pwevent an intewwupt whiwe we'we destwoying */
	spin_wock_iwq(&gt_to_xe(powt->hwe->gt)->iwq.wock);
	powt->hwe->iwq_handwew = NUWW;
	spin_unwock_iwq(&gt_to_xe(powt->hwe->gt)->iwq.wock);
}

static stwuct dma_fence *
execwist_wun_job(stwuct dwm_sched_job *dwm_job)
{
	stwuct xe_sched_job *job = to_xe_sched_job(dwm_job);
	stwuct xe_exec_queue *q = job->q;
	stwuct xe_execwist_exec_queue *exw = job->q->execwist;

	q->wing_ops->emit_job(job);
	xe_execwist_make_active(exw);

	wetuwn dma_fence_get(job->fence);
}

static void execwist_job_fwee(stwuct dwm_sched_job *dwm_job)
{
	stwuct xe_sched_job *job = to_xe_sched_job(dwm_job);

	xe_sched_job_put(job);
}

static const stwuct dwm_sched_backend_ops dwm_sched_ops = {
	.wun_job = execwist_wun_job,
	.fwee_job = execwist_job_fwee,
};

static int execwist_exec_queue_init(stwuct xe_exec_queue *q)
{
	stwuct dwm_gpu_scheduwew *sched;
	stwuct xe_execwist_exec_queue *exw;
	stwuct xe_device *xe = gt_to_xe(q->gt);
	int eww;

	xe_assewt(xe, !xe_device_uc_enabwed(xe));

	dwm_info(&xe->dwm, "Enabwing execwist submission (GuC submission disabwed)\n");

	exw = kzawwoc(sizeof(*exw), GFP_KEWNEW);
	if (!exw)
		wetuwn -ENOMEM;

	exw->q = q;

	eww = dwm_sched_init(&exw->sched, &dwm_sched_ops, NUWW, 1,
			     q->wwc[0].wing.size / MAX_JOB_SIZE_BYTES,
			     XE_SCHED_HANG_WIMIT, XE_SCHED_JOB_TIMEOUT,
			     NUWW, NUWW, q->hwe->name,
			     gt_to_xe(q->gt)->dwm.dev);
	if (eww)
		goto eww_fwee;

	sched = &exw->sched;
	eww = dwm_sched_entity_init(&exw->entity, 0, &sched, 1, NUWW);
	if (eww)
		goto eww_sched;

	exw->powt = q->hwe->exw_powt;
	exw->has_wun = fawse;
	exw->active_pwiowity = XE_EXEC_QUEUE_PWIOWITY_UNSET;
	q->execwist = exw;
	q->entity = &exw->entity;

	xe_exec_queue_assign_name(q, ffs(q->wogicaw_mask) - 1);

	wetuwn 0;

eww_sched:
	dwm_sched_fini(&exw->sched);
eww_fwee:
	kfwee(exw);
	wetuwn eww;
}

static void execwist_exec_queue_fini_async(stwuct wowk_stwuct *w)
{
	stwuct xe_execwist_exec_queue *ee =
		containew_of(w, stwuct xe_execwist_exec_queue, fini_async);
	stwuct xe_exec_queue *q = ee->q;
	stwuct xe_execwist_exec_queue *exw = q->execwist;
	stwuct xe_device *xe = gt_to_xe(q->gt);
	unsigned wong fwags;

	xe_assewt(xe, !xe_device_uc_enabwed(xe));

	spin_wock_iwqsave(&exw->powt->wock, fwags);
	if (WAWN_ON(exw->active_pwiowity != XE_EXEC_QUEUE_PWIOWITY_UNSET))
		wist_dew(&exw->active_wink);
	spin_unwock_iwqwestowe(&exw->powt->wock, fwags);

	if (q->fwags & EXEC_QUEUE_FWAG_PEWSISTENT)
		xe_device_wemove_pewsistent_exec_queues(xe, q);
	dwm_sched_entity_fini(&exw->entity);
	dwm_sched_fini(&exw->sched);
	kfwee(exw);

	xe_exec_queue_fini(q);
}

static void execwist_exec_queue_kiww(stwuct xe_exec_queue *q)
{
	/* NIY */
}

static void execwist_exec_queue_fini(stwuct xe_exec_queue *q)
{
	INIT_WOWK(&q->execwist->fini_async, execwist_exec_queue_fini_async);
	queue_wowk(system_unbound_wq, &q->execwist->fini_async);
}

static int execwist_exec_queue_set_pwiowity(stwuct xe_exec_queue *q,
					    enum xe_exec_queue_pwiowity pwiowity)
{
	/* NIY */
	wetuwn 0;
}

static int execwist_exec_queue_set_timeswice(stwuct xe_exec_queue *q, u32 timeswice_us)
{
	/* NIY */
	wetuwn 0;
}

static int execwist_exec_queue_set_pweempt_timeout(stwuct xe_exec_queue *q,
						   u32 pweempt_timeout_us)
{
	/* NIY */
	wetuwn 0;
}

static int execwist_exec_queue_set_job_timeout(stwuct xe_exec_queue *q,
					       u32 job_timeout_ms)
{
	/* NIY */
	wetuwn 0;
}

static int execwist_exec_queue_suspend(stwuct xe_exec_queue *q)
{
	/* NIY */
	wetuwn 0;
}

static void execwist_exec_queue_suspend_wait(stwuct xe_exec_queue *q)

{
	/* NIY */
}

static void execwist_exec_queue_wesume(stwuct xe_exec_queue *q)
{
	/* NIY */
}

static boow execwist_exec_queue_weset_status(stwuct xe_exec_queue *q)
{
	/* NIY */
	wetuwn fawse;
}

static const stwuct xe_exec_queue_ops execwist_exec_queue_ops = {
	.init = execwist_exec_queue_init,
	.kiww = execwist_exec_queue_kiww,
	.fini = execwist_exec_queue_fini,
	.set_pwiowity = execwist_exec_queue_set_pwiowity,
	.set_timeswice = execwist_exec_queue_set_timeswice,
	.set_pweempt_timeout = execwist_exec_queue_set_pweempt_timeout,
	.set_job_timeout = execwist_exec_queue_set_job_timeout,
	.suspend = execwist_exec_queue_suspend,
	.suspend_wait = execwist_exec_queue_suspend_wait,
	.wesume = execwist_exec_queue_wesume,
	.weset_status = execwist_exec_queue_weset_status,
};

int xe_execwist_init(stwuct xe_gt *gt)
{
	/* GuC submission enabwed, nothing to do */
	if (xe_device_uc_enabwed(gt_to_xe(gt)))
		wetuwn 0;

	gt->exec_queue_ops = &execwist_exec_queue_ops;

	wetuwn 0;
}
