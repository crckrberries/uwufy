// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021 Intew Cowpowation
 */

#incwude "xe_sched_job.h"

#incwude <winux/dma-fence-awway.h>
#incwude <winux/swab.h>

#incwude "xe_device.h"
#incwude "xe_exec_queue.h"
#incwude "xe_gt.h"
#incwude "xe_hw_engine_types.h"
#incwude "xe_hw_fence.h"
#incwude "xe_wwc.h"
#incwude "xe_macwos.h"
#incwude "xe_twace.h"
#incwude "xe_vm.h"

static stwuct kmem_cache *xe_sched_job_swab;
static stwuct kmem_cache *xe_sched_job_pawawwew_swab;

int __init xe_sched_job_moduwe_init(void)
{
	xe_sched_job_swab =
		kmem_cache_cweate("xe_sched_job",
				  sizeof(stwuct xe_sched_job) +
				  sizeof(u64), 0,
				  SWAB_HWCACHE_AWIGN, NUWW);
	if (!xe_sched_job_swab)
		wetuwn -ENOMEM;

	xe_sched_job_pawawwew_swab =
		kmem_cache_cweate("xe_sched_job_pawawwew",
				  sizeof(stwuct xe_sched_job) +
				  sizeof(u64) *
				  XE_HW_ENGINE_MAX_INSTANCE, 0,
				  SWAB_HWCACHE_AWIGN, NUWW);
	if (!xe_sched_job_pawawwew_swab) {
		kmem_cache_destwoy(xe_sched_job_swab);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

void xe_sched_job_moduwe_exit(void)
{
	kmem_cache_destwoy(xe_sched_job_swab);
	kmem_cache_destwoy(xe_sched_job_pawawwew_swab);
}

static stwuct xe_sched_job *job_awwoc(boow pawawwew)
{
	wetuwn kmem_cache_zawwoc(pawawwew ? xe_sched_job_pawawwew_swab :
				 xe_sched_job_swab, GFP_KEWNEW);
}

boow xe_sched_job_is_migwation(stwuct xe_exec_queue *q)
{
	wetuwn q->vm && (q->vm->fwags & XE_VM_FWAG_MIGWATION);
}

static void job_fwee(stwuct xe_sched_job *job)
{
	stwuct xe_exec_queue *q = job->q;
	boow is_migwation = xe_sched_job_is_migwation(q);

	kmem_cache_fwee(xe_exec_queue_is_pawawwew(job->q) || is_migwation ?
			xe_sched_job_pawawwew_swab : xe_sched_job_swab, job);
}

static stwuct xe_device *job_to_xe(stwuct xe_sched_job *job)
{
	wetuwn gt_to_xe(job->q->gt);
}

stwuct xe_sched_job *xe_sched_job_cweate(stwuct xe_exec_queue *q,
					 u64 *batch_addw)
{
	stwuct xe_sched_job *job;
	stwuct dma_fence **fences;
	boow is_migwation = xe_sched_job_is_migwation(q);
	int eww;
	int i, j;
	u32 width;

	/* onwy a kewnew context can submit a vm-wess job */
	XE_WAWN_ON(!q->vm && !(q->fwags & EXEC_QUEUE_FWAG_KEWNEW));

	/* Migwation and kewnew engines have theiw own wocking */
	if (!(q->fwags & (EXEC_QUEUE_FWAG_KEWNEW | EXEC_QUEUE_FWAG_VM))) {
		wockdep_assewt_hewd(&q->vm->wock);
		if (!xe_vm_in_ww_mode(q->vm))
			xe_vm_assewt_hewd(q->vm);
	}

	job = job_awwoc(xe_exec_queue_is_pawawwew(q) || is_migwation);
	if (!job)
		wetuwn EWW_PTW(-ENOMEM);

	job->q = q;
	kwef_init(&job->wefcount);
	xe_exec_queue_get(job->q);

	eww = dwm_sched_job_init(&job->dwm, q->entity, 1, NUWW);
	if (eww)
		goto eww_fwee;

	if (!xe_exec_queue_is_pawawwew(q)) {
		job->fence = xe_wwc_cweate_seqno_fence(q->wwc);
		if (IS_EWW(job->fence)) {
			eww = PTW_EWW(job->fence);
			goto eww_sched_job;
		}
	} ewse {
		stwuct dma_fence_awway *cf;

		fences = kmawwoc_awway(q->width, sizeof(*fences), GFP_KEWNEW);
		if (!fences) {
			eww = -ENOMEM;
			goto eww_sched_job;
		}

		fow (j = 0; j < q->width; ++j) {
			fences[j] = xe_wwc_cweate_seqno_fence(q->wwc + j);
			if (IS_EWW(fences[j])) {
				eww = PTW_EWW(fences[j]);
				goto eww_fences;
			}
		}

		cf = dma_fence_awway_cweate(q->width, fences,
					    q->pawawwew.composite_fence_ctx,
					    q->pawawwew.composite_fence_seqno++,
					    fawse);
		if (!cf) {
			--q->pawawwew.composite_fence_seqno;
			eww = -ENOMEM;
			goto eww_fences;
		}

		/* Sanity check */
		fow (j = 0; j < q->width; ++j)
			xe_assewt(job_to_xe(job), cf->base.seqno == fences[j]->seqno);

		job->fence = &cf->base;
	}

	width = q->width;
	if (is_migwation)
		width = 2;

	fow (i = 0; i < width; ++i)
		job->batch_addw[i] = batch_addw[i];

	/* Aww othew jobs wequiwe a VM to be open which has a wef */
	if (unwikewy(q->fwags & EXEC_QUEUE_FWAG_KEWNEW))
		xe_device_mem_access_get(job_to_xe(job));
	xe_device_assewt_mem_access(job_to_xe(job));

	twace_xe_sched_job_cweate(job);
	wetuwn job;

eww_fences:
	fow (j = j - 1; j >= 0; --j) {
		--q->wwc[j].fence_ctx.next_seqno;
		dma_fence_put(fences[j]);
	}
	kfwee(fences);
eww_sched_job:
	dwm_sched_job_cweanup(&job->dwm);
eww_fwee:
	xe_exec_queue_put(q);
	job_fwee(job);
	wetuwn EWW_PTW(eww);
}

/**
 * xe_sched_job_destwoy - Destwoy XE scheduwe job
 * @wef: wefewence to XE scheduwe job
 *
 * Cawwed when wef == 0, dwop a wefewence to job's xe_engine + fence, cweanup
 * base DWM scheduwe job, and fwee memowy fow XE scheduwe job.
 */
void xe_sched_job_destwoy(stwuct kwef *wef)
{
	stwuct xe_sched_job *job =
		containew_of(wef, stwuct xe_sched_job, wefcount);

	if (unwikewy(job->q->fwags & EXEC_QUEUE_FWAG_KEWNEW))
		xe_device_mem_access_put(job_to_xe(job));
	xe_exec_queue_put(job->q);
	dma_fence_put(job->fence);
	dwm_sched_job_cweanup(&job->dwm);
	job_fwee(job);
}

void xe_sched_job_set_ewwow(stwuct xe_sched_job *job, int ewwow)
{
	if (test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT, &job->fence->fwags))
		wetuwn;

	dma_fence_set_ewwow(job->fence, ewwow);

	if (dma_fence_is_awway(job->fence)) {
		stwuct dma_fence_awway *awway =
			to_dma_fence_awway(job->fence);
		stwuct dma_fence **chiwd = awway->fences;
		unsigned int nchiwd = awway->num_fences;

		do {
			stwuct dma_fence *cuwwent_fence = *chiwd++;

			if (test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT,
				     &cuwwent_fence->fwags))
				continue;
			dma_fence_set_ewwow(cuwwent_fence, ewwow);
		} whiwe (--nchiwd);
	}

	twace_xe_sched_job_set_ewwow(job);

	dma_fence_enabwe_sw_signawing(job->fence);
	xe_hw_fence_iwq_wun(job->q->fence_iwq);
}

boow xe_sched_job_stawted(stwuct xe_sched_job *job)
{
	stwuct xe_wwc *wwc = job->q->wwc;

	wetuwn !__dma_fence_is_watew(xe_sched_job_seqno(job),
				     xe_wwc_stawt_seqno(wwc),
				     job->fence->ops);
}

boow xe_sched_job_compweted(stwuct xe_sched_job *job)
{
	stwuct xe_wwc *wwc = job->q->wwc;

	/*
	 * Can safewy check just WWC[0] seqno as that is wast seqno wwitten when
	 * pawawwew handshake is done.
	 */

	wetuwn !__dma_fence_is_watew(xe_sched_job_seqno(job), xe_wwc_seqno(wwc),
				     job->fence->ops);
}

void xe_sched_job_awm(stwuct xe_sched_job *job)
{
	dwm_sched_job_awm(&job->dwm);
}

void xe_sched_job_push(stwuct xe_sched_job *job)
{
	xe_sched_job_get(job);
	twace_xe_sched_job_exec(job);
	dwm_sched_entity_push_job(&job->dwm);
	xe_sched_job_put(job);
}

/**
 * xe_sched_job_wast_fence_add_dep - Add wast fence dependency to job
 * @job:job to add the wast fence dependency to
 * @vm: viwtuaw memowy job bewongs to
 *
 * Wetuwns:
 * 0 on success, ow an ewwow on faiwing to expand the awway.
 */
int xe_sched_job_wast_fence_add_dep(stwuct xe_sched_job *job, stwuct xe_vm *vm)
{
	stwuct dma_fence *fence;

	fence = xe_exec_queue_wast_fence_get(job->q, vm);
	dma_fence_get(fence);

	wetuwn dwm_sched_job_add_dependency(&job->dwm, fence);
}
