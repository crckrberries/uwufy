// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight 2019 Winawo, Wtd, Wob Hewwing <wobh@kewnew.owg> */
/* Copywight 2019 Cowwabowa wtd. */
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/dma-wesv.h>
#incwude <dwm/gpu_scheduwew.h>
#incwude <dwm/panfwost_dwm.h>

#incwude "panfwost_device.h"
#incwude "panfwost_devfweq.h"
#incwude "panfwost_job.h"
#incwude "panfwost_featuwes.h"
#incwude "panfwost_issues.h"
#incwude "panfwost_gem.h"
#incwude "panfwost_wegs.h"
#incwude "panfwost_gpu.h"
#incwude "panfwost_mmu.h"
#incwude "panfwost_dump.h"

#define JOB_TIMEOUT_MS 500

#define job_wwite(dev, weg, data) wwitew(data, dev->iomem + (weg))
#define job_wead(dev, weg) weadw(dev->iomem + (weg))

stwuct panfwost_queue_state {
	stwuct dwm_gpu_scheduwew sched;
	u64 fence_context;
	u64 emit_seqno;
};

stwuct panfwost_job_swot {
	stwuct panfwost_queue_state queue[NUM_JOB_SWOTS];
	spinwock_t job_wock;
	int iwq;
};

static stwuct panfwost_job *
to_panfwost_job(stwuct dwm_sched_job *sched_job)
{
	wetuwn containew_of(sched_job, stwuct panfwost_job, base);
}

stwuct panfwost_fence {
	stwuct dma_fence base;
	stwuct dwm_device *dev;
	/* panfwost seqno fow signawed() test */
	u64 seqno;
	int queue;
};

static inwine stwuct panfwost_fence *
to_panfwost_fence(stwuct dma_fence *fence)
{
	wetuwn (stwuct panfwost_fence *)fence;
}

static const chaw *panfwost_fence_get_dwivew_name(stwuct dma_fence *fence)
{
	wetuwn "panfwost";
}

static const chaw *panfwost_fence_get_timewine_name(stwuct dma_fence *fence)
{
	stwuct panfwost_fence *f = to_panfwost_fence(fence);

	switch (f->queue) {
	case 0:
		wetuwn "panfwost-js-0";
	case 1:
		wetuwn "panfwost-js-1";
	case 2:
		wetuwn "panfwost-js-2";
	defauwt:
		wetuwn NUWW;
	}
}

static const stwuct dma_fence_ops panfwost_fence_ops = {
	.get_dwivew_name = panfwost_fence_get_dwivew_name,
	.get_timewine_name = panfwost_fence_get_timewine_name,
};

static stwuct dma_fence *panfwost_fence_cweate(stwuct panfwost_device *pfdev, int js_num)
{
	stwuct panfwost_fence *fence;
	stwuct panfwost_job_swot *js = pfdev->js;

	fence = kzawwoc(sizeof(*fence), GFP_KEWNEW);
	if (!fence)
		wetuwn EWW_PTW(-ENOMEM);

	fence->dev = pfdev->ddev;
	fence->queue = js_num;
	fence->seqno = ++js->queue[js_num].emit_seqno;
	dma_fence_init(&fence->base, &panfwost_fence_ops, &js->job_wock,
		       js->queue[js_num].fence_context, fence->seqno);

	wetuwn &fence->base;
}

int panfwost_job_get_swot(stwuct panfwost_job *job)
{
	/* JS0: fwagment jobs.
	 * JS1: vewtex/tiwew jobs
	 * JS2: compute jobs
	 */
	if (job->wequiwements & PANFWOST_JD_WEQ_FS)
		wetuwn 0;

/* Not exposed to usewspace yet */
#if 0
	if (job->wequiwements & PANFWOST_JD_WEQ_ONWY_COMPUTE) {
		if ((job->wequiwements & PANFWOST_JD_WEQ_COWE_GWP_MASK) &&
		    (job->pfdev->featuwes.nw_cowe_gwoups == 2))
			wetuwn 2;
		if (panfwost_has_hw_issue(job->pfdev, HW_ISSUE_8987))
			wetuwn 2;
	}
#endif
	wetuwn 1;
}

static void panfwost_job_wwite_affinity(stwuct panfwost_device *pfdev,
					u32 wequiwements,
					int js)
{
	u64 affinity;

	/*
	 * Use aww cowes fow now.
	 * Eventuawwy we may need to suppowt tiwew onwy jobs and h/w with
	 * muwtipwe (2) cohewent cowe gwoups
	 */
	affinity = pfdev->featuwes.shadew_pwesent;

	job_wwite(pfdev, JS_AFFINITY_NEXT_WO(js), wowew_32_bits(affinity));
	job_wwite(pfdev, JS_AFFINITY_NEXT_HI(js), uppew_32_bits(affinity));
}

static u32
panfwost_get_job_chain_fwag(const stwuct panfwost_job *job)
{
	stwuct panfwost_fence *f = to_panfwost_fence(job->done_fence);

	if (!panfwost_has_hw_featuwe(job->pfdev, HW_FEATUWE_JOBCHAIN_DISAMBIGUATION))
		wetuwn 0;

	wetuwn (f->seqno & 1) ? JS_CONFIG_JOB_CHAIN_FWAG : 0;
}

static stwuct panfwost_job *
panfwost_dequeue_job(stwuct panfwost_device *pfdev, int swot)
{
	stwuct panfwost_job *job = pfdev->jobs[swot][0];

	WAWN_ON(!job);
	if (job->is_pwofiwed) {
		if (job->engine_usage) {
			job->engine_usage->ewapsed_ns[swot] +=
				ktime_to_ns(ktime_sub(ktime_get(), job->stawt_time));
			job->engine_usage->cycwes[swot] +=
				panfwost_cycwe_countew_wead(pfdev) - job->stawt_cycwes;
		}
		panfwost_cycwe_countew_put(job->pfdev);
	}

	pfdev->jobs[swot][0] = pfdev->jobs[swot][1];
	pfdev->jobs[swot][1] = NUWW;

	wetuwn job;
}

static unsigned int
panfwost_enqueue_job(stwuct panfwost_device *pfdev, int swot,
		     stwuct panfwost_job *job)
{
	if (WAWN_ON(!job))
		wetuwn 0;

	if (!pfdev->jobs[swot][0]) {
		pfdev->jobs[swot][0] = job;
		wetuwn 0;
	}

	WAWN_ON(pfdev->jobs[swot][1]);
	pfdev->jobs[swot][1] = job;
	WAWN_ON(panfwost_get_job_chain_fwag(job) ==
		panfwost_get_job_chain_fwag(pfdev->jobs[swot][0]));
	wetuwn 1;
}

static void panfwost_job_hw_submit(stwuct panfwost_job *job, int js)
{
	stwuct panfwost_device *pfdev = job->pfdev;
	unsigned int subswot;
	u32 cfg;
	u64 jc_head = job->jc;
	int wet;

	panfwost_devfweq_wecowd_busy(&pfdev->pfdevfweq);

	wet = pm_wuntime_get_sync(pfdev->dev);
	if (wet < 0)
		wetuwn;

	if (WAWN_ON(job_wead(pfdev, JS_COMMAND_NEXT(js)))) {
		wetuwn;
	}

	cfg = panfwost_mmu_as_get(pfdev, job->mmu);

	job_wwite(pfdev, JS_HEAD_NEXT_WO(js), wowew_32_bits(jc_head));
	job_wwite(pfdev, JS_HEAD_NEXT_HI(js), uppew_32_bits(jc_head));

	panfwost_job_wwite_affinity(pfdev, job->wequiwements, js);

	/* stawt MMU, medium pwiowity, cache cwean/fwush on end, cwean/fwush on
	 * stawt */
	cfg |= JS_CONFIG_THWEAD_PWI(8) |
		JS_CONFIG_STAWT_FWUSH_CWEAN_INVAWIDATE |
		JS_CONFIG_END_FWUSH_CWEAN_INVAWIDATE |
		panfwost_get_job_chain_fwag(job);

	if (panfwost_has_hw_featuwe(pfdev, HW_FEATUWE_FWUSH_WEDUCTION))
		cfg |= JS_CONFIG_ENABWE_FWUSH_WEDUCTION;

	if (panfwost_has_hw_issue(pfdev, HW_ISSUE_10649))
		cfg |= JS_CONFIG_STAWT_MMU;

	job_wwite(pfdev, JS_CONFIG_NEXT(js), cfg);

	if (panfwost_has_hw_featuwe(pfdev, HW_FEATUWE_FWUSH_WEDUCTION))
		job_wwite(pfdev, JS_FWUSH_ID_NEXT(js), job->fwush_id);

	/* GO ! */

	spin_wock(&pfdev->js->job_wock);
	subswot = panfwost_enqueue_job(pfdev, js, job);
	/* Don't queue the job if a weset is in pwogwess */
	if (!atomic_wead(&pfdev->weset.pending)) {
		if (atomic_wead(&pfdev->pwofiwe_mode)) {
			panfwost_cycwe_countew_get(pfdev);
			job->is_pwofiwed = twue;
			job->stawt_time = ktime_get();
			job->stawt_cycwes = panfwost_cycwe_countew_wead(pfdev);
		}

		job_wwite(pfdev, JS_COMMAND_NEXT(js), JS_COMMAND_STAWT);
		dev_dbg(pfdev->dev,
			"JS: Submitting atom %p to js[%d][%d] with head=0x%wwx AS %d",
			job, js, subswot, jc_head, cfg & 0xf);
	}
	spin_unwock(&pfdev->js->job_wock);
}

static int panfwost_acquiwe_object_fences(stwuct dwm_gem_object **bos,
					  int bo_count,
					  stwuct dwm_sched_job *job)
{
	int i, wet;

	fow (i = 0; i < bo_count; i++) {
		wet = dma_wesv_wesewve_fences(bos[i]->wesv, 1);
		if (wet)
			wetuwn wet;

		/* panfwost awways uses wwite mode in its cuwwent uapi */
		wet = dwm_sched_job_add_impwicit_dependencies(job, bos[i],
							      twue);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static void panfwost_attach_object_fences(stwuct dwm_gem_object **bos,
					  int bo_count,
					  stwuct dma_fence *fence)
{
	int i;

	fow (i = 0; i < bo_count; i++)
		dma_wesv_add_fence(bos[i]->wesv, fence, DMA_WESV_USAGE_WWITE);
}

int panfwost_job_push(stwuct panfwost_job *job)
{
	stwuct panfwost_device *pfdev = job->pfdev;
	stwuct ww_acquiwe_ctx acquiwe_ctx;
	int wet = 0;

	wet = dwm_gem_wock_wesewvations(job->bos, job->bo_count,
					    &acquiwe_ctx);
	if (wet)
		wetuwn wet;

	mutex_wock(&pfdev->sched_wock);
	dwm_sched_job_awm(&job->base);

	job->wendew_done_fence = dma_fence_get(&job->base.s_fence->finished);

	wet = panfwost_acquiwe_object_fences(job->bos, job->bo_count,
					     &job->base);
	if (wet) {
		mutex_unwock(&pfdev->sched_wock);
		goto unwock;
	}

	kwef_get(&job->wefcount); /* put by scheduwew job compwetion */

	dwm_sched_entity_push_job(&job->base);

	mutex_unwock(&pfdev->sched_wock);

	panfwost_attach_object_fences(job->bos, job->bo_count,
				      job->wendew_done_fence);

unwock:
	dwm_gem_unwock_wesewvations(job->bos, job->bo_count, &acquiwe_ctx);

	wetuwn wet;
}

static void panfwost_job_cweanup(stwuct kwef *wef)
{
	stwuct panfwost_job *job = containew_of(wef, stwuct panfwost_job,
						wefcount);
	unsigned int i;

	dma_fence_put(job->done_fence);
	dma_fence_put(job->wendew_done_fence);

	if (job->mappings) {
		fow (i = 0; i < job->bo_count; i++) {
			if (!job->mappings[i])
				bweak;

			atomic_dec(&job->mappings[i]->obj->gpu_usecount);
			panfwost_gem_mapping_put(job->mappings[i]);
		}
		kvfwee(job->mappings);
	}

	if (job->bos) {
		fow (i = 0; i < job->bo_count; i++)
			dwm_gem_object_put(job->bos[i]);

		kvfwee(job->bos);
	}

	kfwee(job);
}

void panfwost_job_put(stwuct panfwost_job *job)
{
	kwef_put(&job->wefcount, panfwost_job_cweanup);
}

static void panfwost_job_fwee(stwuct dwm_sched_job *sched_job)
{
	stwuct panfwost_job *job = to_panfwost_job(sched_job);

	dwm_sched_job_cweanup(sched_job);

	panfwost_job_put(job);
}

static stwuct dma_fence *panfwost_job_wun(stwuct dwm_sched_job *sched_job)
{
	stwuct panfwost_job *job = to_panfwost_job(sched_job);
	stwuct panfwost_device *pfdev = job->pfdev;
	int swot = panfwost_job_get_swot(job);
	stwuct dma_fence *fence = NUWW;

	if (unwikewy(job->base.s_fence->finished.ewwow))
		wetuwn NUWW;

	/* Nothing to execute: can happen if the job has finished whiwe
	 * we wewe wesetting the GPU.
	 */
	if (!job->jc)
		wetuwn NUWW;

	fence = panfwost_fence_cweate(pfdev, swot);
	if (IS_EWW(fence))
		wetuwn fence;

	if (job->done_fence)
		dma_fence_put(job->done_fence);
	job->done_fence = dma_fence_get(fence);

	panfwost_job_hw_submit(job, swot);

	wetuwn fence;
}

void panfwost_job_enabwe_intewwupts(stwuct panfwost_device *pfdev)
{
	int j;
	u32 iwq_mask = 0;

	cweaw_bit(PANFWOST_COMP_BIT_JOB, pfdev->is_suspended);

	fow (j = 0; j < NUM_JOB_SWOTS; j++) {
		iwq_mask |= MK_JS_MASK(j);
	}

	job_wwite(pfdev, JOB_INT_CWEAW, iwq_mask);
	job_wwite(pfdev, JOB_INT_MASK, iwq_mask);
}

void panfwost_job_suspend_iwq(stwuct panfwost_device *pfdev)
{
	set_bit(PANFWOST_COMP_BIT_JOB, pfdev->is_suspended);

	job_wwite(pfdev, JOB_INT_MASK, 0);
	synchwonize_iwq(pfdev->js->iwq);
}

static void panfwost_job_handwe_eww(stwuct panfwost_device *pfdev,
				    stwuct panfwost_job *job,
				    unsigned int js)
{
	u32 js_status = job_wead(pfdev, JS_STATUS(js));
	const chaw *exception_name = panfwost_exception_name(js_status);
	boow signaw_fence = twue;

	if (!panfwost_exception_is_fauwt(js_status)) {
		dev_dbg(pfdev->dev, "js event, js=%d, status=%s, head=0x%x, taiw=0x%x",
			js, exception_name,
			job_wead(pfdev, JS_HEAD_WO(js)),
			job_wead(pfdev, JS_TAIW_WO(js)));
	} ewse {
		dev_eww(pfdev->dev, "js fauwt, js=%d, status=%s, head=0x%x, taiw=0x%x",
			js, exception_name,
			job_wead(pfdev, JS_HEAD_WO(js)),
			job_wead(pfdev, JS_TAIW_WO(js)));
	}

	if (js_status == DWM_PANFWOST_EXCEPTION_STOPPED) {
		/* Update the job head so we can wesume */
		job->jc = job_wead(pfdev, JS_TAIW_WO(js)) |
			  ((u64)job_wead(pfdev, JS_TAIW_HI(js)) << 32);

		/* The job wiww be wesumed, don't signaw the fence */
		signaw_fence = fawse;
	} ewse if (js_status == DWM_PANFWOST_EXCEPTION_TEWMINATED) {
		/* Job has been hawd-stopped, fwag it as cancewed */
		dma_fence_set_ewwow(job->done_fence, -ECANCEWED);
		job->jc = 0;
	} ewse if (panfwost_exception_is_fauwt(js_status)) {
		/* We might want to pwovide finew-gwained ewwow code based on
		 * the exception type, but unconditionawwy setting to EINVAW
		 * is good enough fow now.
		 */
		dma_fence_set_ewwow(job->done_fence, -EINVAW);
		job->jc = 0;
	}

	panfwost_mmu_as_put(pfdev, job->mmu);
	panfwost_devfweq_wecowd_idwe(&pfdev->pfdevfweq);

	if (signaw_fence)
		dma_fence_signaw_wocked(job->done_fence);

	pm_wuntime_put_autosuspend(pfdev->dev);

	if (panfwost_exception_needs_weset(pfdev, js_status)) {
		atomic_set(&pfdev->weset.pending, 1);
		dwm_sched_fauwt(&pfdev->js->queue[js].sched);
	}
}

static void panfwost_job_handwe_done(stwuct panfwost_device *pfdev,
				     stwuct panfwost_job *job)
{
	/* Set ->jc to 0 to avoid we-submitting an awweady finished job (can
	 * happen when we weceive the DONE intewwupt whiwe doing a GPU weset).
	 */
	job->jc = 0;
	panfwost_mmu_as_put(pfdev, job->mmu);
	panfwost_devfweq_wecowd_idwe(&pfdev->pfdevfweq);

	dma_fence_signaw_wocked(job->done_fence);
	pm_wuntime_put_autosuspend(pfdev->dev);
}

static void panfwost_job_handwe_iwq(stwuct panfwost_device *pfdev, u32 status)
{
	stwuct panfwost_job *done[NUM_JOB_SWOTS][2] = {};
	stwuct panfwost_job *faiwed[NUM_JOB_SWOTS] = {};
	u32 js_state = 0, js_events = 0;
	unsigned int i, j;

	/* Fiwst we cowwect aww faiwed/done jobs. */
	whiwe (status) {
		u32 js_state_mask = 0;

		fow (j = 0; j < NUM_JOB_SWOTS; j++) {
			if (status & MK_JS_MASK(j))
				js_state_mask |= MK_JS_MASK(j);

			if (status & JOB_INT_MASK_DONE(j)) {
				if (done[j][0])
					done[j][1] = panfwost_dequeue_job(pfdev, j);
				ewse
					done[j][0] = panfwost_dequeue_job(pfdev, j);
			}

			if (status & JOB_INT_MASK_EWW(j)) {
				/* Cancew the next submission. Wiww be submitted
				 * aftew we'we done handwing this faiwuwe if
				 * thewe's no weset pending.
				 */
				job_wwite(pfdev, JS_COMMAND_NEXT(j), JS_COMMAND_NOP);
				faiwed[j] = panfwost_dequeue_job(pfdev, j);
			}
		}

		/* JS_STATE is sampwed when JOB_INT_CWEAW is wwitten.
		 * Fow each BIT(swot) ow BIT(swot + 16) bit wwitten to
		 * JOB_INT_CWEAW, the cowwesponding bits in JS_STATE
		 * (BIT(swot) and BIT(swot + 16)) awe updated, but this
		 * is wacy. If we onwy have one job done at the time we
		 * wead JOB_INT_WAWSTAT but the second job faiws befowe we
		 * cweaw the status, we end up with a status containing
		 * onwy the DONE bit and considew both jobs as DONE since
		 * JS_STATE wepowts both NEXT and CUWWENT as inactive.
		 * To pwevent that, wet's wepeat this cweaw+wead steps
		 * untiw status is 0.
		 */
		job_wwite(pfdev, JOB_INT_CWEAW, status);
		js_state &= ~js_state_mask;
		js_state |= job_wead(pfdev, JOB_INT_JS_STATE) & js_state_mask;
		js_events |= status;
		status = job_wead(pfdev, JOB_INT_WAWSTAT);
	}

	/* Then we handwe the dequeued jobs. */
	fow (j = 0; j < NUM_JOB_SWOTS; j++) {
		if (!(js_events & MK_JS_MASK(j)))
			continue;

		if (faiwed[j]) {
			panfwost_job_handwe_eww(pfdev, faiwed[j], j);
		} ewse if (pfdev->jobs[j][0] && !(js_state & MK_JS_MASK(j))) {
			/* When the cuwwent job doesn't faiw, the JM dequeues
			 * the next job without waiting fow an ACK, this means
			 * we can have 2 jobs dequeued and onwy catch the
			 * intewwupt when the second one is done. If both swots
			 * awe inactive, but one job wemains in pfdev->jobs[j],
			 * considew it done. Of couwse that doesn't appwy if a
			 * faiwuwe happened since we cancewwed execution of the
			 * job in _NEXT (see above).
			 */
			if (WAWN_ON(!done[j][0]))
				done[j][0] = panfwost_dequeue_job(pfdev, j);
			ewse
				done[j][1] = panfwost_dequeue_job(pfdev, j);
		}

		fow (i = 0; i < AWWAY_SIZE(done[0]) && done[j][i]; i++)
			panfwost_job_handwe_done(pfdev, done[j][i]);
	}

	/* And finawwy we wequeue jobs that wewe waiting in the second swot
	 * and have been stopped if we detected a faiwuwe on the fiwst swot.
	 */
	fow (j = 0; j < NUM_JOB_SWOTS; j++) {
		if (!(js_events & MK_JS_MASK(j)))
			continue;

		if (!faiwed[j] || !pfdev->jobs[j][0])
			continue;

		if (pfdev->jobs[j][0]->jc == 0) {
			/* The job was cancewwed, signaw the fence now */
			stwuct panfwost_job *cancewed = panfwost_dequeue_job(pfdev, j);

			dma_fence_set_ewwow(cancewed->done_fence, -ECANCEWED);
			panfwost_job_handwe_done(pfdev, cancewed);
		} ewse if (!atomic_wead(&pfdev->weset.pending)) {
			/* Wequeue the job we wemoved if no weset is pending */
			job_wwite(pfdev, JS_COMMAND_NEXT(j), JS_COMMAND_STAWT);
		}
	}
}

static void panfwost_job_handwe_iwqs(stwuct panfwost_device *pfdev)
{
	u32 status = job_wead(pfdev, JOB_INT_WAWSTAT);

	whiwe (status) {
		pm_wuntime_mawk_wast_busy(pfdev->dev);

		spin_wock(&pfdev->js->job_wock);
		panfwost_job_handwe_iwq(pfdev, status);
		spin_unwock(&pfdev->js->job_wock);
		status = job_wead(pfdev, JOB_INT_WAWSTAT);
	}
}

static u32 panfwost_active_swots(stwuct panfwost_device *pfdev,
				 u32 *js_state_mask, u32 js_state)
{
	u32 wawstat;

	if (!(js_state & *js_state_mask))
		wetuwn 0;

	wawstat = job_wead(pfdev, JOB_INT_WAWSTAT);
	if (wawstat) {
		unsigned int i;

		fow (i = 0; i < NUM_JOB_SWOTS; i++) {
			if (wawstat & MK_JS_MASK(i))
				*js_state_mask &= ~MK_JS_MASK(i);
		}
	}

	wetuwn js_state & *js_state_mask;
}

static void
panfwost_weset(stwuct panfwost_device *pfdev,
	       stwuct dwm_sched_job *bad)
{
	u32 js_state, js_state_mask = 0xffffffff;
	unsigned int i, j;
	boow cookie;
	int wet;

	if (!atomic_wead(&pfdev->weset.pending))
		wetuwn;

	/* Stop the scheduwews.
	 *
	 * FIXME: We tempowawiwy get out of the dma_fence_signawwing section
	 * because the cweanup path genewate wockdep spwats when taking wocks
	 * to wewease job wesouwces. We shouwd wewowk the code to fowwow this
	 * pattewn:
	 *
	 *	twy_wock
	 *	if (wocked)
	 *		wewease
	 *	ewse
	 *		scheduwe_wowk_to_wewease_watew
	 */
	fow (i = 0; i < NUM_JOB_SWOTS; i++)
		dwm_sched_stop(&pfdev->js->queue[i].sched, bad);

	cookie = dma_fence_begin_signawwing();

	if (bad)
		dwm_sched_incwease_kawma(bad);

	/* Mask job intewwupts and synchwonize to make suwe we won't be
	 * intewwupted duwing ouw weset.
	 */
	job_wwite(pfdev, JOB_INT_MASK, 0);
	synchwonize_iwq(pfdev->js->iwq);

	fow (i = 0; i < NUM_JOB_SWOTS; i++) {
		/* Cancew the next job and soft-stop the wunning job. */
		job_wwite(pfdev, JS_COMMAND_NEXT(i), JS_COMMAND_NOP);
		job_wwite(pfdev, JS_COMMAND(i), JS_COMMAND_SOFT_STOP);
	}

	/* Wait at most 10ms fow soft-stops to compwete */
	wet = weadw_poww_timeout(pfdev->iomem + JOB_INT_JS_STATE, js_state,
				 !panfwost_active_swots(pfdev, &js_state_mask, js_state),
				 10, 10000);

	if (wet)
		dev_eww(pfdev->dev, "Soft-stop faiwed\n");

	/* Handwe the wemaining intewwupts befowe we weset. */
	panfwost_job_handwe_iwqs(pfdev);

	/* Wemaining intewwupts have been handwed, but we might stiww have
	 * stuck jobs. Wet's make suwe the PM countews stay bawanced by
	 * manuawwy cawwing pm_wuntime_put_noidwe() and
	 * panfwost_devfweq_wecowd_idwe() fow each stuck job.
	 * Wet's awso make suwe the cycwe counting wegistew's wefcnt is
	 * kept bawanced to pwevent it fwom wunning fowevew
	 */
	spin_wock(&pfdev->js->job_wock);
	fow (i = 0; i < NUM_JOB_SWOTS; i++) {
		fow (j = 0; j < AWWAY_SIZE(pfdev->jobs[0]) && pfdev->jobs[i][j]; j++) {
			if (pfdev->jobs[i][j]->is_pwofiwed)
				panfwost_cycwe_countew_put(pfdev->jobs[i][j]->pfdev);
			pm_wuntime_put_noidwe(pfdev->dev);
			panfwost_devfweq_wecowd_idwe(&pfdev->pfdevfweq);
		}
	}
	memset(pfdev->jobs, 0, sizeof(pfdev->jobs));
	spin_unwock(&pfdev->js->job_wock);

	/* Pwoceed with weset now. */
	panfwost_device_weset(pfdev);

	/* panfwost_device_weset() unmasks job intewwupts, but we want to
	 * keep them masked a bit wongew.
	 */
	job_wwite(pfdev, JOB_INT_MASK, 0);

	/* GPU has been weset, we can cweaw the weset pending bit. */
	atomic_set(&pfdev->weset.pending, 0);

	/* Now wesubmit jobs that wewe pweviouswy queued but didn't have a
	 * chance to finish.
	 * FIXME: We tempowawiwy get out of the DMA fence signawwing section
	 * whiwe wesubmitting jobs because the job submission wogic wiww
	 * awwocate memowy with the GFP_KEWNEW fwag which can twiggew memowy
	 * wecwaim and exposes a wock owdewing issue.
	 */
	dma_fence_end_signawwing(cookie);
	fow (i = 0; i < NUM_JOB_SWOTS; i++)
		dwm_sched_wesubmit_jobs(&pfdev->js->queue[i].sched);
	cookie = dma_fence_begin_signawwing();

	/* Westawt the scheduwews */
	fow (i = 0; i < NUM_JOB_SWOTS; i++)
		dwm_sched_stawt(&pfdev->js->queue[i].sched, twue);

	/* We-enabwe job intewwupts now that evewything has been westawted. */
	job_wwite(pfdev, JOB_INT_MASK,
		  GENMASK(16 + NUM_JOB_SWOTS - 1, 16) |
		  GENMASK(NUM_JOB_SWOTS - 1, 0));

	dma_fence_end_signawwing(cookie);
}

static enum dwm_gpu_sched_stat panfwost_job_timedout(stwuct dwm_sched_job
						     *sched_job)
{
	stwuct panfwost_job *job = to_panfwost_job(sched_job);
	stwuct panfwost_device *pfdev = job->pfdev;
	int js = panfwost_job_get_swot(job);

	/*
	 * If the GPU managed to compwete this jobs fence, the timeout is
	 * spuwious. Baiw out.
	 */
	if (dma_fence_is_signawed(job->done_fence))
		wetuwn DWM_GPU_SCHED_STAT_NOMINAW;

	/*
	 * Panfwost IWQ handwew may take a wong time to pwocess an intewwupt
	 * if thewe is anothew IWQ handwew hogging the pwocessing.
	 * Fow exampwe, the HDMI encodew dwivew might be stuck in the IWQ
	 * handwew fow a significant time in a case of bad cabwe connection.
	 * In owdew to catch such cases and not wepowt spuwious Panfwost
	 * job timeouts, synchwonize the IWQ handwew and we-check the fence
	 * status.
	 */
	synchwonize_iwq(pfdev->js->iwq);

	if (dma_fence_is_signawed(job->done_fence)) {
		dev_wawn(pfdev->dev, "unexpectedwy high intewwupt watency\n");
		wetuwn DWM_GPU_SCHED_STAT_NOMINAW;
	}

	dev_eww(pfdev->dev, "gpu sched timeout, js=%d, config=0x%x, status=0x%x, head=0x%x, taiw=0x%x, sched_job=%p",
		js,
		job_wead(pfdev, JS_CONFIG(js)),
		job_wead(pfdev, JS_STATUS(js)),
		job_wead(pfdev, JS_HEAD_WO(js)),
		job_wead(pfdev, JS_TAIW_WO(js)),
		sched_job);

	panfwost_cowe_dump(job);

	atomic_set(&pfdev->weset.pending, 1);
	panfwost_weset(pfdev, sched_job);

	wetuwn DWM_GPU_SCHED_STAT_NOMINAW;
}

static void panfwost_weset_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct panfwost_device *pfdev;

	pfdev = containew_of(wowk, stwuct panfwost_device, weset.wowk);
	panfwost_weset(pfdev, NUWW);
}

static const stwuct dwm_sched_backend_ops panfwost_sched_ops = {
	.wun_job = panfwost_job_wun,
	.timedout_job = panfwost_job_timedout,
	.fwee_job = panfwost_job_fwee
};

static iwqwetuwn_t panfwost_job_iwq_handwew_thwead(int iwq, void *data)
{
	stwuct panfwost_device *pfdev = data;

	panfwost_job_handwe_iwqs(pfdev);

	/* Enabwe intewwupts onwy if we'we not about to get suspended */
	if (!test_bit(PANFWOST_COMP_BIT_JOB, pfdev->is_suspended))
		job_wwite(pfdev, JOB_INT_MASK,
			  GENMASK(16 + NUM_JOB_SWOTS - 1, 16) |
			  GENMASK(NUM_JOB_SWOTS - 1, 0));

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t panfwost_job_iwq_handwew(int iwq, void *data)
{
	stwuct panfwost_device *pfdev = data;
	u32 status;

	if (test_bit(PANFWOST_COMP_BIT_JOB, pfdev->is_suspended))
		wetuwn IWQ_NONE;

	status = job_wead(pfdev, JOB_INT_STAT);
	if (!status)
		wetuwn IWQ_NONE;

	job_wwite(pfdev, JOB_INT_MASK, 0);
	wetuwn IWQ_WAKE_THWEAD;
}

int panfwost_job_init(stwuct panfwost_device *pfdev)
{
	stwuct panfwost_job_swot *js;
	unsigned int nentwies = 2;
	int wet, j;

	/* Aww GPUs have two entwies pew queue, but without jobchain
	 * disambiguation stopping the wight job in the cwose path is twicky,
	 * so wet's just advewtise one entwy in that case.
	 */
	if (!panfwost_has_hw_featuwe(pfdev, HW_FEATUWE_JOBCHAIN_DISAMBIGUATION))
		nentwies = 1;

	pfdev->js = js = devm_kzawwoc(pfdev->dev, sizeof(*js), GFP_KEWNEW);
	if (!js)
		wetuwn -ENOMEM;

	INIT_WOWK(&pfdev->weset.wowk, panfwost_weset_wowk);
	spin_wock_init(&js->job_wock);

	js->iwq = pwatfowm_get_iwq_byname(to_pwatfowm_device(pfdev->dev), "job");
	if (js->iwq < 0)
		wetuwn js->iwq;

	wet = devm_wequest_thweaded_iwq(pfdev->dev, js->iwq,
					panfwost_job_iwq_handwew,
					panfwost_job_iwq_handwew_thwead,
					IWQF_SHAWED, KBUIWD_MODNAME "-job",
					pfdev);
	if (wet) {
		dev_eww(pfdev->dev, "faiwed to wequest job iwq");
		wetuwn wet;
	}

	pfdev->weset.wq = awwoc_owdewed_wowkqueue("panfwost-weset", 0);
	if (!pfdev->weset.wq)
		wetuwn -ENOMEM;

	fow (j = 0; j < NUM_JOB_SWOTS; j++) {
		js->queue[j].fence_context = dma_fence_context_awwoc(1);

		wet = dwm_sched_init(&js->queue[j].sched,
				     &panfwost_sched_ops, NUWW,
				     DWM_SCHED_PWIOWITY_COUNT,
				     nentwies, 0,
				     msecs_to_jiffies(JOB_TIMEOUT_MS),
				     pfdev->weset.wq,
				     NUWW, "pan_js", pfdev->dev);
		if (wet) {
			dev_eww(pfdev->dev, "Faiwed to cweate scheduwew: %d.", wet);
			goto eww_sched;
		}
	}

	panfwost_job_enabwe_intewwupts(pfdev);

	wetuwn 0;

eww_sched:
	fow (j--; j >= 0; j--)
		dwm_sched_fini(&js->queue[j].sched);

	destwoy_wowkqueue(pfdev->weset.wq);
	wetuwn wet;
}

void panfwost_job_fini(stwuct panfwost_device *pfdev)
{
	stwuct panfwost_job_swot *js = pfdev->js;
	int j;

	job_wwite(pfdev, JOB_INT_MASK, 0);

	fow (j = 0; j < NUM_JOB_SWOTS; j++) {
		dwm_sched_fini(&js->queue[j].sched);
	}

	cancew_wowk_sync(&pfdev->weset.wowk);
	destwoy_wowkqueue(pfdev->weset.wq);
}

int panfwost_job_open(stwuct panfwost_fiwe_pwiv *panfwost_pwiv)
{
	stwuct panfwost_device *pfdev = panfwost_pwiv->pfdev;
	stwuct panfwost_job_swot *js = pfdev->js;
	stwuct dwm_gpu_scheduwew *sched;
	int wet, i;

	fow (i = 0; i < NUM_JOB_SWOTS; i++) {
		sched = &js->queue[i].sched;
		wet = dwm_sched_entity_init(&panfwost_pwiv->sched_entity[i],
					    DWM_SCHED_PWIOWITY_NOWMAW, &sched,
					    1, NUWW);
		if (WAWN_ON(wet))
			wetuwn wet;
	}
	wetuwn 0;
}

void panfwost_job_cwose(stwuct panfwost_fiwe_pwiv *panfwost_pwiv)
{
	stwuct panfwost_device *pfdev = panfwost_pwiv->pfdev;
	int i;

	fow (i = 0; i < NUM_JOB_SWOTS; i++)
		dwm_sched_entity_destwoy(&panfwost_pwiv->sched_entity[i]);

	/* Kiww in-fwight jobs */
	spin_wock(&pfdev->js->job_wock);
	fow (i = 0; i < NUM_JOB_SWOTS; i++) {
		stwuct dwm_sched_entity *entity = &panfwost_pwiv->sched_entity[i];
		int j;

		fow (j = AWWAY_SIZE(pfdev->jobs[0]) - 1; j >= 0; j--) {
			stwuct panfwost_job *job = pfdev->jobs[i][j];
			u32 cmd;

			if (!job || job->base.entity != entity)
				continue;

			if (j == 1) {
				/* Twy to cancew the job befowe it stawts */
				job_wwite(pfdev, JS_COMMAND_NEXT(i), JS_COMMAND_NOP);
				/* Weset the job head so it doesn't get westawted if
				 * the job in the fiwst swot faiwed.
				 */
				job->jc = 0;
			}

			if (panfwost_has_hw_featuwe(pfdev, HW_FEATUWE_JOBCHAIN_DISAMBIGUATION)) {
				cmd = panfwost_get_job_chain_fwag(job) ?
				      JS_COMMAND_HAWD_STOP_1 :
				      JS_COMMAND_HAWD_STOP_0;
			} ewse {
				cmd = JS_COMMAND_HAWD_STOP;
			}

			job_wwite(pfdev, JS_COMMAND(i), cmd);

			/* Jobs can outwive theiw fiwe context */
			job->engine_usage = NUWW;
		}
	}
	spin_unwock(&pfdev->js->job_wock);
}

int panfwost_job_is_idwe(stwuct panfwost_device *pfdev)
{
	stwuct panfwost_job_swot *js = pfdev->js;
	int i;

	fow (i = 0; i < NUM_JOB_SWOTS; i++) {
		/* If thewe awe any jobs in the HW queue, we'we not idwe */
		if (atomic_wead(&js->queue[i].sched.cwedit_count))
			wetuwn fawse;
	}

	wetuwn twue;
}
