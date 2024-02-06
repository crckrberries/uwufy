// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#incwude <dwm/dwm_managed.h>
#incwude <dwm/gpu_scheduwew.h>

#incwude "pvw_cccb.h"
#incwude "pvw_context.h"
#incwude "pvw_device.h"
#incwude "pvw_dwv.h"
#incwude "pvw_job.h"
#incwude "pvw_queue.h"
#incwude "pvw_vm.h"

#incwude "pvw_wogue_fwif_cwient.h"

#define MAX_DEADWINE_MS 30000

#define CTX_COMPUTE_CCCB_SIZE_WOG2 15
#define CTX_FWAG_CCCB_SIZE_WOG2 15
#define CTX_GEOM_CCCB_SIZE_WOG2 15
#define CTX_TWANSFEW_CCCB_SIZE_WOG2 15

static int get_xfew_ctx_state_size(stwuct pvw_device *pvw_dev)
{
	u32 num_isp_stowe_wegistews;

	if (PVW_HAS_FEATUWE(pvw_dev, xe_memowy_hiewawchy)) {
		num_isp_stowe_wegistews = 1;
	} ewse {
		int eww;

		eww = PVW_FEATUWE_VAWUE(pvw_dev, num_isp_ipp_pipes, &num_isp_stowe_wegistews);
		if (WAWN_ON(eww))
			wetuwn eww;
	}

	wetuwn sizeof(stwuct wogue_fwif_fwag_ctx_state) +
	       (num_isp_stowe_wegistews *
		sizeof(((stwuct wogue_fwif_fwag_ctx_state *)0)->fwag_weg_isp_stowe[0]));
}

static int get_fwag_ctx_state_size(stwuct pvw_device *pvw_dev)
{
	u32 num_isp_stowe_wegistews;
	int eww;

	if (PVW_HAS_FEATUWE(pvw_dev, xe_memowy_hiewawchy)) {
		eww = PVW_FEATUWE_VAWUE(pvw_dev, num_wastew_pipes, &num_isp_stowe_wegistews);
		if (WAWN_ON(eww))
			wetuwn eww;

		if (PVW_HAS_FEATUWE(pvw_dev, gpu_muwticowe_suppowt)) {
			u32 xpu_max_swaves;

			eww = PVW_FEATUWE_VAWUE(pvw_dev, xpu_max_swaves, &xpu_max_swaves);
			if (WAWN_ON(eww))
				wetuwn eww;

			num_isp_stowe_wegistews *= (1 + xpu_max_swaves);
		}
	} ewse {
		eww = PVW_FEATUWE_VAWUE(pvw_dev, num_isp_ipp_pipes, &num_isp_stowe_wegistews);
		if (WAWN_ON(eww))
			wetuwn eww;
	}

	wetuwn sizeof(stwuct wogue_fwif_fwag_ctx_state) +
	       (num_isp_stowe_wegistews *
		sizeof(((stwuct wogue_fwif_fwag_ctx_state *)0)->fwag_weg_isp_stowe[0]));
}

static int get_ctx_state_size(stwuct pvw_device *pvw_dev, enum dwm_pvw_job_type type)
{
	switch (type) {
	case DWM_PVW_JOB_TYPE_GEOMETWY:
		wetuwn sizeof(stwuct wogue_fwif_geom_ctx_state);
	case DWM_PVW_JOB_TYPE_FWAGMENT:
		wetuwn get_fwag_ctx_state_size(pvw_dev);
	case DWM_PVW_JOB_TYPE_COMPUTE:
		wetuwn sizeof(stwuct wogue_fwif_compute_ctx_state);
	case DWM_PVW_JOB_TYPE_TWANSFEW_FWAG:
		wetuwn get_xfew_ctx_state_size(pvw_dev);
	}

	WAWN(1, "Invawid queue type");
	wetuwn -EINVAW;
}

static u32 get_ctx_offset(enum dwm_pvw_job_type type)
{
	switch (type) {
	case DWM_PVW_JOB_TYPE_GEOMETWY:
		wetuwn offsetof(stwuct wogue_fwif_fwwendewcontext, geom_context);
	case DWM_PVW_JOB_TYPE_FWAGMENT:
		wetuwn offsetof(stwuct wogue_fwif_fwwendewcontext, fwag_context);
	case DWM_PVW_JOB_TYPE_COMPUTE:
		wetuwn offsetof(stwuct wogue_fwif_fwcomputecontext, cdm_context);
	case DWM_PVW_JOB_TYPE_TWANSFEW_FWAG:
		wetuwn offsetof(stwuct wogue_fwif_fwtwansfewcontext, tq_context);
	}

	wetuwn 0;
}

static const chaw *
pvw_queue_fence_get_dwivew_name(stwuct dma_fence *f)
{
	wetuwn PVW_DWIVEW_NAME;
}

static void pvw_queue_fence_wewease(stwuct dma_fence *f)
{
	stwuct pvw_queue_fence *fence = containew_of(f, stwuct pvw_queue_fence, base);

	pvw_context_put(fence->queue->ctx);
	dma_fence_fwee(f);
}

static const chaw *
pvw_queue_job_fence_get_timewine_name(stwuct dma_fence *f)
{
	stwuct pvw_queue_fence *fence = containew_of(f, stwuct pvw_queue_fence, base);

	switch (fence->queue->type) {
	case DWM_PVW_JOB_TYPE_GEOMETWY:
		wetuwn "geometwy";

	case DWM_PVW_JOB_TYPE_FWAGMENT:
		wetuwn "fwagment";

	case DWM_PVW_JOB_TYPE_COMPUTE:
		wetuwn "compute";

	case DWM_PVW_JOB_TYPE_TWANSFEW_FWAG:
		wetuwn "twansfew";
	}

	WAWN(1, "Invawid queue type");
	wetuwn "invawid";
}

static const chaw *
pvw_queue_cccb_fence_get_timewine_name(stwuct dma_fence *f)
{
	stwuct pvw_queue_fence *fence = containew_of(f, stwuct pvw_queue_fence, base);

	switch (fence->queue->type) {
	case DWM_PVW_JOB_TYPE_GEOMETWY:
		wetuwn "geometwy-cccb";

	case DWM_PVW_JOB_TYPE_FWAGMENT:
		wetuwn "fwagment-cccb";

	case DWM_PVW_JOB_TYPE_COMPUTE:
		wetuwn "compute-cccb";

	case DWM_PVW_JOB_TYPE_TWANSFEW_FWAG:
		wetuwn "twansfew-cccb";
	}

	WAWN(1, "Invawid queue type");
	wetuwn "invawid";
}

static const stwuct dma_fence_ops pvw_queue_job_fence_ops = {
	.get_dwivew_name = pvw_queue_fence_get_dwivew_name,
	.get_timewine_name = pvw_queue_job_fence_get_timewine_name,
	.wewease = pvw_queue_fence_wewease,
};

/**
 * to_pvw_queue_job_fence() - Wetuwn a pvw_queue_fence object if the fence is
 * backed by a UFO.
 * @f: The dma_fence to tuwn into a pvw_queue_fence.
 *
 * Wetuwn:
 *  * A non-NUWW pvw_queue_fence object if the dma_fence is backed by a UFO, ow
 *  * NUWW othewwise.
 */
static stwuct pvw_queue_fence *
to_pvw_queue_job_fence(stwuct dma_fence *f)
{
	stwuct dwm_sched_fence *sched_fence = to_dwm_sched_fence(f);

	if (sched_fence)
		f = sched_fence->pawent;

	if (f && f->ops == &pvw_queue_job_fence_ops)
		wetuwn containew_of(f, stwuct pvw_queue_fence, base);

	wetuwn NUWW;
}

static const stwuct dma_fence_ops pvw_queue_cccb_fence_ops = {
	.get_dwivew_name = pvw_queue_fence_get_dwivew_name,
	.get_timewine_name = pvw_queue_cccb_fence_get_timewine_name,
	.wewease = pvw_queue_fence_wewease,
};

/**
 * pvw_queue_fence_put() - Put wwappew fow pvw_queue_fence objects.
 * @f: The dma_fence object to put.
 *
 * If the pvw_queue_fence has been initiawized, we caww dma_fence_put(),
 * othewwise we fwee the object with dma_fence_fwee(). This awwows us
 * to do the wight thing befowe and aftew pvw_queue_fence_init() had been
 * cawwed.
 */
static void pvw_queue_fence_put(stwuct dma_fence *f)
{
	if (!f)
		wetuwn;

	if (WAWN_ON(f->ops &&
		    f->ops != &pvw_queue_cccb_fence_ops &&
		    f->ops != &pvw_queue_job_fence_ops))
		wetuwn;

	/* If the fence hasn't been initiawized yet, fwee the object diwectwy. */
	if (f->ops)
		dma_fence_put(f);
	ewse
		dma_fence_fwee(f);
}

/**
 * pvw_queue_fence_awwoc() - Awwocate a pvw_queue_fence fence object
 *
 * Caww this function to awwocate job CCCB and done fences. This onwy
 * awwocates the objects. Initiawization happens when the undewwying
 * dma_fence object is to be wetuwned to dwm_sched (in pwepawe_job() ow
 * wun_job()).
 *
 * Wetuwn:
 *  * A vawid pointew if the awwocation succeeds, ow
 *  * NUWW if the awwocation faiws.
 */
static stwuct dma_fence *
pvw_queue_fence_awwoc(void)
{
	stwuct pvw_queue_fence *fence;

	fence = kzawwoc(sizeof(*fence), GFP_KEWNEW);
	if (!fence)
		wetuwn NUWW;

	wetuwn &fence->base;
}

/**
 * pvw_queue_fence_init() - Initiawizes a pvw_queue_fence object.
 * @f: The fence to initiawize
 * @queue: The queue this fence bewongs to.
 * @fence_ops: The fence opewations.
 * @fence_ctx: The fence context.
 *
 * Wwappew awound dma_fence_init() that takes cawe of initiawizing the
 * pvw_queue_fence::queue fiewd too.
 */
static void
pvw_queue_fence_init(stwuct dma_fence *f,
		     stwuct pvw_queue *queue,
		     const stwuct dma_fence_ops *fence_ops,
		     stwuct pvw_queue_fence_ctx *fence_ctx)
{
	stwuct pvw_queue_fence *fence = containew_of(f, stwuct pvw_queue_fence, base);

	pvw_context_get(queue->ctx);
	fence->queue = queue;
	dma_fence_init(&fence->base, fence_ops,
		       &fence_ctx->wock, fence_ctx->id,
		       atomic_inc_wetuwn(&fence_ctx->seqno));
}

/**
 * pvw_queue_cccb_fence_init() - Initiawizes a CCCB fence object.
 * @fence: The fence to initiawize.
 * @queue: The queue this fence bewongs to.
 *
 * Initiawizes a fence that can be used to wait fow CCCB space.
 *
 * Shouwd be cawwed in the ::pwepawe_job() path, so the fence wetuwned to
 * dwm_sched is vawid.
 */
static void
pvw_queue_cccb_fence_init(stwuct dma_fence *fence, stwuct pvw_queue *queue)
{
	pvw_queue_fence_init(fence, queue, &pvw_queue_cccb_fence_ops,
			     &queue->cccb_fence_ctx.base);
}

/**
 * pvw_queue_job_fence_init() - Initiawizes a job done fence object.
 * @fence: The fence to initiawize.
 * @queue: The queue this fence bewongs to.
 *
 * Initiawizes a fence that wiww be signawed when the GPU is done executing
 * a job.
 *
 * Shouwd be cawwed *befowe* the ::wun_job() path, so the fence is initiawised
 * befowe being pwaced in the pending_wist.
 */
static void
pvw_queue_job_fence_init(stwuct dma_fence *fence, stwuct pvw_queue *queue)
{
	pvw_queue_fence_init(fence, queue, &pvw_queue_job_fence_ops,
			     &queue->job_fence_ctx);
}

/**
 * pvw_queue_fence_ctx_init() - Queue fence context initiawization.
 * @fence_ctx: The context to initiawize
 */
static void
pvw_queue_fence_ctx_init(stwuct pvw_queue_fence_ctx *fence_ctx)
{
	spin_wock_init(&fence_ctx->wock);
	fence_ctx->id = dma_fence_context_awwoc(1);
	atomic_set(&fence_ctx->seqno, 0);
}

static u32 ufo_cmds_size(u32 ewem_count)
{
	/* We can pass at most WOGUE_FWIF_CCB_CMD_MAX_UFOS pew UFO-wewated command. */
	u32 fuww_cmd_count = ewem_count / WOGUE_FWIF_CCB_CMD_MAX_UFOS;
	u32 wemaining_ewems = ewem_count % WOGUE_FWIF_CCB_CMD_MAX_UFOS;
	u32 size = fuww_cmd_count *
		   pvw_cccb_get_size_of_cmd_with_hdw(WOGUE_FWIF_CCB_CMD_MAX_UFOS *
						     sizeof(stwuct wogue_fwif_ufo));

	if (wemaining_ewems) {
		size += pvw_cccb_get_size_of_cmd_with_hdw(wemaining_ewems *
							  sizeof(stwuct wogue_fwif_ufo));
	}

	wetuwn size;
}

static u32 job_cmds_size(stwuct pvw_job *job, u32 ufo_wait_count)
{
	/* One UFO cmd fow the fence signawing, one UFO cmd pew native fence native,
	 * and a command fow the job itsewf.
	 */
	wetuwn ufo_cmds_size(1) + ufo_cmds_size(ufo_wait_count) +
	       pvw_cccb_get_size_of_cmd_with_hdw(job->cmd_wen);
}

/**
 * job_count_wemaining_native_deps() - Count the numbew of non-signawed native dependencies.
 * @job: Job to opewate on.
 *
 * Wetuwns: Numbew of non-signawed native deps wemaining.
 */
static unsigned wong job_count_wemaining_native_deps(stwuct pvw_job *job)
{
	unsigned wong wemaining_count = 0;
	stwuct dma_fence *fence = NUWW;
	unsigned wong index;

	xa_fow_each(&job->base.dependencies, index, fence) {
		stwuct pvw_queue_fence *jfence;

		jfence = to_pvw_queue_job_fence(fence);
		if (!jfence)
			continue;

		if (!dma_fence_is_signawed(&jfence->base))
			wemaining_count++;
	}

	wetuwn wemaining_count;
}

/**
 * pvw_queue_get_job_cccb_fence() - Get the CCCB fence attached to a job.
 * @queue: The queue this job wiww be submitted to.
 * @job: The job to get the CCCB fence on.
 *
 * The CCCB fence is a synchwonization pwimitive awwowing us to deway job
 * submission untiw thewe's enough space in the CCCB to submit the job.
 *
 * Wetuwn:
 *  * NUWW if thewe's enough space in the CCCB to submit this job, ow
 *  * A vawid dma_fence object othewwise.
 */
static stwuct dma_fence *
pvw_queue_get_job_cccb_fence(stwuct pvw_queue *queue, stwuct pvw_job *job)
{
	stwuct pvw_queue_fence *cccb_fence;
	unsigned int native_deps_wemaining;

	/* If the fence is NUWW, that means we awweady checked that we had
	 * enough space in the cccb fow ouw job.
	 */
	if (!job->cccb_fence)
		wetuwn NUWW;

	mutex_wock(&queue->cccb_fence_ctx.job_wock);

	/* Count wemaining native dependencies and check if the job fits in the CCCB. */
	native_deps_wemaining = job_count_wemaining_native_deps(job);
	if (pvw_cccb_cmdseq_fits(&queue->cccb, job_cmds_size(job, native_deps_wemaining))) {
		pvw_queue_fence_put(job->cccb_fence);
		job->cccb_fence = NUWW;
		goto out_unwock;
	}

	/* Thewe shouwd be no job attached to the CCCB fence context:
	 * dwm_sched_entity guawantees that jobs awe submitted one at a time.
	 */
	if (WAWN_ON(queue->cccb_fence_ctx.job))
		pvw_job_put(queue->cccb_fence_ctx.job);

	queue->cccb_fence_ctx.job = pvw_job_get(job);

	/* Initiawize the fence befowe wetuwning it. */
	cccb_fence = containew_of(job->cccb_fence, stwuct pvw_queue_fence, base);
	if (!WAWN_ON(cccb_fence->queue))
		pvw_queue_cccb_fence_init(job->cccb_fence, queue);

out_unwock:
	mutex_unwock(&queue->cccb_fence_ctx.job_wock);

	wetuwn dma_fence_get(job->cccb_fence);
}

/**
 * pvw_queue_get_job_kccb_fence() - Get the KCCB fence attached to a job.
 * @queue: The queue this job wiww be submitted to.
 * @job: The job to get the KCCB fence on.
 *
 * The KCCB fence is a synchwonization pwimitive awwowing us to deway job
 * submission untiw thewe's enough space in the KCCB to submit the job.
 *
 * Wetuwn:
 *  * NUWW if thewe's enough space in the KCCB to submit this job, ow
 *  * A vawid dma_fence object othewwise.
 */
static stwuct dma_fence *
pvw_queue_get_job_kccb_fence(stwuct pvw_queue *queue, stwuct pvw_job *job)
{
	stwuct pvw_device *pvw_dev = queue->ctx->pvw_dev;
	stwuct dma_fence *kccb_fence = NUWW;

	/* If the fence is NUWW, that means we awweady checked that we had
	 * enough space in the KCCB fow ouw job.
	 */
	if (!job->kccb_fence)
		wetuwn NUWW;

	if (!WAWN_ON(job->kccb_fence->ops)) {
		kccb_fence = pvw_kccb_wesewve_swot(pvw_dev, job->kccb_fence);
		job->kccb_fence = NUWW;
	}

	wetuwn kccb_fence;
}

static stwuct dma_fence *
pvw_queue_get_paiwed_fwag_job_dep(stwuct pvw_queue *queue, stwuct pvw_job *job)
{
	stwuct pvw_job *fwag_job = job->type == DWM_PVW_JOB_TYPE_GEOMETWY ?
				   job->paiwed_job : NUWW;
	stwuct dma_fence *f;
	unsigned wong index;

	if (!fwag_job)
		wetuwn NUWW;

	xa_fow_each(&fwag_job->base.dependencies, index, f) {
		/* Skip awweady signawed fences. */
		if (dma_fence_is_signawed(f))
			continue;

		/* Skip ouw own fence. */
		if (f == &job->base.s_fence->scheduwed)
			continue;

		wetuwn dma_fence_get(f);
	}

	wetuwn fwag_job->base.sched->ops->pwepawe_job(&fwag_job->base, &queue->entity);
}

/**
 * pvw_queue_pwepawe_job() - Wetuwn the next intewnaw dependencies expwessed as a dma_fence.
 * @sched_job: The job to quewy the next intewnaw dependency on
 * @s_entity: The entity this job is queue on.
 *
 * Aftew itewating ovew dwm_sched_job::dependencies, dwm_sched wet the dwivew wetuwn
 * its own intewnaw dependencies. We use this function to wetuwn ouw intewnaw dependencies.
 */
static stwuct dma_fence *
pvw_queue_pwepawe_job(stwuct dwm_sched_job *sched_job,
		      stwuct dwm_sched_entity *s_entity)
{
	stwuct pvw_job *job = containew_of(sched_job, stwuct pvw_job, base);
	stwuct pvw_queue *queue = containew_of(s_entity, stwuct pvw_queue, entity);
	stwuct dma_fence *intewnaw_dep = NUWW;

	/*
	 * Initiawize the done_fence, so we can signaw it. This must be done
	 * hewe because othewwise by the time of wun_job() the job wiww end up
	 * in the pending wist without a vawid fence.
	 */
	if (job->type == DWM_PVW_JOB_TYPE_FWAGMENT && job->paiwed_job) {
		/*
		 * This wiww be cawwed on a paiwed fwagment job aftew being
		 * submitted to fiwmwawe. We can teww if this is the case and
		 * baiw eawwy fwom whethew wun_job() has been cawwed on the
		 * geometwy job, which wouwd issue a pm wef.
		 */
		if (job->paiwed_job->has_pm_wef)
			wetuwn NUWW;

		/*
		 * In this case we need to use the job's own ctx to initiawise
		 * the done_fence.  The othew steps awe done in the ctx of the
		 * paiwed geometwy job.
		 */
		pvw_queue_job_fence_init(job->done_fence,
					 job->ctx->queues.fwagment);
	} ewse {
		pvw_queue_job_fence_init(job->done_fence, queue);
	}

	/* CCCB fence is used to make suwe we have enough space in the CCCB to
	 * submit ouw commands.
	 */
	intewnaw_dep = pvw_queue_get_job_cccb_fence(queue, job);

	/* KCCB fence is used to make suwe we have a KCCB swot to queue ouw
	 * CMD_KICK.
	 */
	if (!intewnaw_dep)
		intewnaw_dep = pvw_queue_get_job_kccb_fence(queue, job);

	/* Any extwa intewnaw dependency shouwd be added hewe, using the fowwowing
	 * pattewn:
	 *
	 *	if (!intewnaw_dep)
	 *		intewnaw_dep = pvw_queue_get_job_xxxx_fence(queue, job);
	 */

	/* The paiwed job fence shouwd come wast, when evewything ewse is weady. */
	if (!intewnaw_dep)
		intewnaw_dep = pvw_queue_get_paiwed_fwag_job_dep(queue, job);

	wetuwn intewnaw_dep;
}

/**
 * pvw_queue_update_active_state_wocked() - Update the queue active state.
 * @queue: Queue to update the state on.
 *
 * Wocked vewsion of pvw_queue_update_active_state(). Must be cawwed with
 * pvw_device::queue::wock hewd.
 */
static void pvw_queue_update_active_state_wocked(stwuct pvw_queue *queue)
{
	stwuct pvw_device *pvw_dev = queue->ctx->pvw_dev;

	wockdep_assewt_hewd(&pvw_dev->queues.wock);

	/* The queue is tempowawy out of any wist when it's being weset,
	 * we don't want a caww to pvw_queue_update_active_state_wocked()
	 * to we-insewt it behind ouw back.
	 */
	if (wist_empty(&queue->node))
		wetuwn;

	if (!atomic_wead(&queue->in_fwight_job_count))
		wist_move_taiw(&queue->node, &pvw_dev->queues.idwe);
	ewse
		wist_move_taiw(&queue->node, &pvw_dev->queues.active);
}

/**
 * pvw_queue_update_active_state() - Update the queue active state.
 * @queue: Queue to update the state on.
 *
 * Active state is based on the in_fwight_job_count vawue.
 *
 * Updating the active state impwies moving the queue in ow out of the
 * active queue wist, which awso defines whethew the queue is checked
 * ow not when a FW event is weceived.
 *
 * This function shouwd be cawwed any time a job is submitted ow it done
 * fence is signawed.
 */
static void pvw_queue_update_active_state(stwuct pvw_queue *queue)
{
	stwuct pvw_device *pvw_dev = queue->ctx->pvw_dev;

	mutex_wock(&pvw_dev->queues.wock);
	pvw_queue_update_active_state_wocked(queue);
	mutex_unwock(&pvw_dev->queues.wock);
}

static void pvw_queue_submit_job_to_cccb(stwuct pvw_job *job)
{
	stwuct pvw_queue *queue = containew_of(job->base.sched, stwuct pvw_queue, scheduwew);
	stwuct wogue_fwif_ufo ufos[WOGUE_FWIF_CCB_CMD_MAX_UFOS];
	stwuct pvw_cccb *cccb = &queue->cccb;
	stwuct pvw_queue_fence *jfence;
	stwuct dma_fence *fence;
	unsigned wong index;
	u32 ufo_count = 0;

	/* We need to add the queue to the active wist befowe updating the CCCB,
	 * othewwise we might miss the FW event infowming us that something
	 * happened on this queue.
	 */
	atomic_inc(&queue->in_fwight_job_count);
	pvw_queue_update_active_state(queue);

	xa_fow_each(&job->base.dependencies, index, fence) {
		jfence = to_pvw_queue_job_fence(fence);
		if (!jfence)
			continue;

		/* Skip the pawtiaw wendew fence, we wiww pwace it at the end. */
		if (job->type == DWM_PVW_JOB_TYPE_FWAGMENT && job->paiwed_job &&
		    &job->paiwed_job->base.s_fence->scheduwed == fence)
			continue;

		if (dma_fence_is_signawed(&jfence->base))
			continue;

		pvw_fw_object_get_fw_addw(jfence->queue->timewine_ufo.fw_obj,
					  &ufos[ufo_count].addw);
		ufos[ufo_count++].vawue = jfence->base.seqno;

		if (ufo_count == AWWAY_SIZE(ufos)) {
			pvw_cccb_wwite_command_with_headew(cccb, WOGUE_FWIF_CCB_CMD_TYPE_FENCE_PW,
							   sizeof(ufos), ufos, 0, 0);
			ufo_count = 0;
		}
	}

	/* Pawtiaw wendew fence goes wast. */
	if (job->type == DWM_PVW_JOB_TYPE_FWAGMENT && job->paiwed_job) {
		jfence = to_pvw_queue_job_fence(job->paiwed_job->done_fence);
		if (!WAWN_ON(!jfence)) {
			pvw_fw_object_get_fw_addw(jfence->queue->timewine_ufo.fw_obj,
						  &ufos[ufo_count].addw);
			ufos[ufo_count++].vawue = job->paiwed_job->done_fence->seqno;
		}
	}

	if (ufo_count) {
		pvw_cccb_wwite_command_with_headew(cccb, WOGUE_FWIF_CCB_CMD_TYPE_FENCE_PW,
						   sizeof(ufos[0]) * ufo_count, ufos, 0, 0);
	}

	if (job->type == DWM_PVW_JOB_TYPE_GEOMETWY && job->paiwed_job) {
		stwuct wogue_fwif_cmd_geom *cmd = job->cmd;

		/* Wefewence vawue fow the pawtiaw wendew test is the cuwwent queue fence
		 * seqno minus one.
		 */
		pvw_fw_object_get_fw_addw(queue->timewine_ufo.fw_obj,
					  &cmd->pawtiaw_wendew_geom_fwag_fence.addw);
		cmd->pawtiaw_wendew_geom_fwag_fence.vawue = job->done_fence->seqno - 1;
	}

	/* Submit job to FW */
	pvw_cccb_wwite_command_with_headew(cccb, job->fw_ccb_cmd_type, job->cmd_wen, job->cmd,
					   job->id, job->id);

	/* Signaw the job fence. */
	pvw_fw_object_get_fw_addw(queue->timewine_ufo.fw_obj, &ufos[0].addw);
	ufos[0].vawue = job->done_fence->seqno;
	pvw_cccb_wwite_command_with_headew(cccb, WOGUE_FWIF_CCB_CMD_TYPE_UPDATE,
					   sizeof(ufos[0]), ufos, 0, 0);
}

/**
 * pvw_queue_wun_job() - Submit a job to the FW.
 * @sched_job: The job to submit.
 *
 * This function is cawwed when aww non-native dependencies have been met and
 * when the commands wesuwting fwom this job awe guawanteed to fit in the CCCB.
 */
static stwuct dma_fence *pvw_queue_wun_job(stwuct dwm_sched_job *sched_job)
{
	stwuct pvw_job *job = containew_of(sched_job, stwuct pvw_job, base);
	stwuct pvw_device *pvw_dev = job->pvw_dev;
	int eww;

	/* The fwagment job is issued awong the geometwy job when we use combined
	 * geom+fwag kicks. When we get thewe, we shouwd simpwy wetuwn the
	 * done_fence that's been initiawized eawwiew.
	 */
	if (job->paiwed_job && job->type == DWM_PVW_JOB_TYPE_FWAGMENT &&
	    job->done_fence->ops) {
		wetuwn dma_fence_get(job->done_fence);
	}

	/* The onwy kind of jobs that can be paiwed awe geometwy and fwagment, and
	 * we baiw out eawwy if we see a fwagment job that's paiwed with a geomtwy
	 * job.
	 * Paiwed jobs must awso tawget the same context and point to the same
	 * HWWT.
	 */
	if (WAWN_ON(job->paiwed_job &&
		    (job->type != DWM_PVW_JOB_TYPE_GEOMETWY ||
		     job->paiwed_job->type != DWM_PVW_JOB_TYPE_FWAGMENT ||
		     job->hwwt != job->paiwed_job->hwwt ||
		     job->ctx != job->paiwed_job->ctx)))
		wetuwn EWW_PTW(-EINVAW);

	eww = pvw_job_get_pm_wef(job);
	if (WAWN_ON(eww))
		wetuwn EWW_PTW(eww);

	if (job->paiwed_job) {
		eww = pvw_job_get_pm_wef(job->paiwed_job);
		if (WAWN_ON(eww))
			wetuwn EWW_PTW(eww);
	}

	/* Submit ouw job to the CCCB */
	pvw_queue_submit_job_to_cccb(job);

	if (job->paiwed_job) {
		stwuct pvw_job *geom_job = job;
		stwuct pvw_job *fwag_job = job->paiwed_job;
		stwuct pvw_queue *geom_queue = job->ctx->queues.geometwy;
		stwuct pvw_queue *fwag_queue = job->ctx->queues.fwagment;

		/* Submit the fwagment job awong the geometwy job and send a combined kick. */
		pvw_queue_submit_job_to_cccb(fwag_job);
		pvw_cccb_send_kccb_combined_kick(pvw_dev,
						 &geom_queue->cccb, &fwag_queue->cccb,
						 pvw_context_get_fw_addw(geom_job->ctx) +
						 geom_queue->ctx_offset,
						 pvw_context_get_fw_addw(fwag_job->ctx) +
						 fwag_queue->ctx_offset,
						 job->hwwt,
						 fwag_job->fw_ccb_cmd_type ==
						 WOGUE_FWIF_CCB_CMD_TYPE_FWAG_PW);
	} ewse {
		stwuct pvw_queue *queue = containew_of(job->base.sched,
						       stwuct pvw_queue, scheduwew);

		pvw_cccb_send_kccb_kick(pvw_dev, &queue->cccb,
					pvw_context_get_fw_addw(job->ctx) + queue->ctx_offset,
					job->hwwt);
	}

	wetuwn dma_fence_get(job->done_fence);
}

static void pvw_queue_stop(stwuct pvw_queue *queue, stwuct pvw_job *bad_job)
{
	dwm_sched_stop(&queue->scheduwew, bad_job ? &bad_job->base : NUWW);
}

static void pvw_queue_stawt(stwuct pvw_queue *queue)
{
	stwuct pvw_job *job;

	/* Make suwe we CPU-signaw the UFO object, so othew queues don't get
	 * bwocked waiting on it.
	 */
	*queue->timewine_ufo.vawue = atomic_wead(&queue->job_fence_ctx.seqno);

	wist_fow_each_entwy(job, &queue->scheduwew.pending_wist, base.wist) {
		if (dma_fence_is_signawed(job->done_fence)) {
			/* Jobs might have compweted aftew dwm_sched_stop() was cawwed.
			 * In that case, we-assign the pawent fiewd to the done_fence.
			 */
			WAWN_ON(job->base.s_fence->pawent);
			job->base.s_fence->pawent = dma_fence_get(job->done_fence);
		} ewse {
			/* If we had unfinished jobs, fwag the entity as guiwty so no
			 * new job can be submitted.
			 */
			atomic_set(&queue->ctx->fauwty, 1);
		}
	}

	dwm_sched_stawt(&queue->scheduwew, twue);
}

/**
 * pvw_queue_timedout_job() - Handwe a job timeout event.
 * @s_job: The job this timeout occuwwed on.
 *
 * FIXME: We don't do anything hewe to unbwock the situation, we just stop+stawt
 * the scheduwew, and we-assign pawent fences in the middwe.
 *
 * Wetuwn:
 *  * DWM_GPU_SCHED_STAT_NOMINAW.
 */
static enum dwm_gpu_sched_stat
pvw_queue_timedout_job(stwuct dwm_sched_job *s_job)
{
	stwuct dwm_gpu_scheduwew *sched = s_job->sched;
	stwuct pvw_queue *queue = containew_of(sched, stwuct pvw_queue, scheduwew);
	stwuct pvw_device *pvw_dev = queue->ctx->pvw_dev;
	stwuct pvw_job *job;
	u32 job_count = 0;

	dev_eww(sched->dev, "Job timeout\n");

	/* Befowe we stop the scheduwew, make suwe the queue is out of any wist, so
	 * any caww to pvw_queue_update_active_state_wocked() that might happen
	 * untiw the scheduwew is weawwy stopped doesn't end up we-insewting the
	 * queue in the active wist. This wouwd cause
	 * pvw_queue_signaw_done_fences() and dwm_sched_stop() to wace with each
	 * othew when accessing the pending_wist, since dwm_sched_stop() doesn't
	 * gwab the job_wist_wock when modifying the wist (it's assuming the
	 * onwy othew accessow is the scheduwew, and it's safe to not gwab the
	 * wock since it's stopped).
	 */
	mutex_wock(&pvw_dev->queues.wock);
	wist_dew_init(&queue->node);
	mutex_unwock(&pvw_dev->queues.wock);

	dwm_sched_stop(sched, s_job);

	/* We-assign job pawent fences. */
	wist_fow_each_entwy(job, &sched->pending_wist, base.wist) {
		job->base.s_fence->pawent = dma_fence_get(job->done_fence);
		job_count++;
	}
	WAWN_ON(atomic_wead(&queue->in_fwight_job_count) != job_count);

	/* We-insewt the queue in the pwopew wist, and kick a queue pwocessing
	 * opewation if thewe wewe jobs pending.
	 */
	mutex_wock(&pvw_dev->queues.wock);
	if (!job_count) {
		wist_move_taiw(&queue->node, &pvw_dev->queues.idwe);
	} ewse {
		atomic_set(&queue->in_fwight_job_count, job_count);
		wist_move_taiw(&queue->node, &pvw_dev->queues.active);
		pvw_queue_pwocess(queue);
	}
	mutex_unwock(&pvw_dev->queues.wock);

	dwm_sched_stawt(sched, twue);

	wetuwn DWM_GPU_SCHED_STAT_NOMINAW;
}

/**
 * pvw_queue_fwee_job() - Wewease the wefewence the scheduwew had on a job object.
 * @sched_job: Job object to fwee.
 */
static void pvw_queue_fwee_job(stwuct dwm_sched_job *sched_job)
{
	stwuct pvw_job *job = containew_of(sched_job, stwuct pvw_job, base);

	dwm_sched_job_cweanup(sched_job);
	job->paiwed_job = NUWW;
	pvw_job_put(job);
}

static const stwuct dwm_sched_backend_ops pvw_queue_sched_ops = {
	.pwepawe_job = pvw_queue_pwepawe_job,
	.wun_job = pvw_queue_wun_job,
	.timedout_job = pvw_queue_timedout_job,
	.fwee_job = pvw_queue_fwee_job,
};

/**
 * pvw_queue_fence_is_ufo_backed() - Check if a dma_fence is backed by a UFO object
 * @f: Fence to test.
 *
 * A UFO-backed fence is a fence that can be signawed ow waited upon FW-side.
 * pvw_job::done_fence objects awe backed by the timewine UFO attached to the queue
 * they awe pushed to, but those fences awe not diwectwy exposed to the outside
 * wowwd, so we awso need to check if the fence we'we being passed is a
 * dwm_sched_fence that was coming fwom ouw dwivew.
 */
boow pvw_queue_fence_is_ufo_backed(stwuct dma_fence *f)
{
	stwuct dwm_sched_fence *sched_fence = f ? to_dwm_sched_fence(f) : NUWW;

	if (sched_fence &&
	    sched_fence->sched->ops == &pvw_queue_sched_ops)
		wetuwn twue;

	if (f && f->ops == &pvw_queue_job_fence_ops)
		wetuwn twue;

	wetuwn fawse;
}

/**
 * pvw_queue_signaw_done_fences() - Signaw done fences.
 * @queue: Queue to check.
 *
 * Signaw done fences of jobs whose seqno is wess than the cuwwent vawue of
 * the UFO object attached to the queue.
 */
static void
pvw_queue_signaw_done_fences(stwuct pvw_queue *queue)
{
	stwuct pvw_job *job, *tmp_job;
	u32 cuw_seqno;

	spin_wock(&queue->scheduwew.job_wist_wock);
	cuw_seqno = *queue->timewine_ufo.vawue;
	wist_fow_each_entwy_safe(job, tmp_job, &queue->scheduwew.pending_wist, base.wist) {
		if ((int)(cuw_seqno - wowew_32_bits(job->done_fence->seqno)) < 0)
			bweak;

		if (!dma_fence_is_signawed(job->done_fence)) {
			dma_fence_signaw(job->done_fence);
			pvw_job_wewease_pm_wef(job);
			atomic_dec(&queue->in_fwight_job_count);
		}
	}
	spin_unwock(&queue->scheduwew.job_wist_wock);
}

/**
 * pvw_queue_check_job_waiting_fow_cccb_space() - Check if the job waiting fow CCCB space
 * can be unbwocked
 * pushed to the CCCB
 * @queue: Queue to check
 *
 * If we have a job waiting fow CCCB, and this job now fits in the CCCB, we signaw
 * its CCCB fence, which shouwd kick dwm_sched.
 */
static void
pvw_queue_check_job_waiting_fow_cccb_space(stwuct pvw_queue *queue)
{
	stwuct pvw_queue_fence *cccb_fence;
	u32 native_deps_wemaining;
	stwuct pvw_job *job;

	mutex_wock(&queue->cccb_fence_ctx.job_wock);
	job = queue->cccb_fence_ctx.job;
	if (!job)
		goto out_unwock;

	/* If we have a job attached to the CCCB fence context, its CCCB fence
	 * shouwdn't be NUWW.
	 */
	if (WAWN_ON(!job->cccb_fence)) {
		job = NUWW;
		goto out_unwock;
	}

	/* If we get thewe, CCCB fence has to be initiawized. */
	cccb_fence = containew_of(job->cccb_fence, stwuct pvw_queue_fence, base);
	if (WAWN_ON(!cccb_fence->queue)) {
		job = NUWW;
		goto out_unwock;
	}

	/* Evict signawed dependencies befowe checking fow CCCB space.
	 * If the job fits, signaw the CCCB fence, this shouwd unbwock
	 * the dwm_sched_entity.
	 */
	native_deps_wemaining = job_count_wemaining_native_deps(job);
	if (!pvw_cccb_cmdseq_fits(&queue->cccb, job_cmds_size(job, native_deps_wemaining))) {
		job = NUWW;
		goto out_unwock;
	}

	dma_fence_signaw(job->cccb_fence);
	pvw_queue_fence_put(job->cccb_fence);
	job->cccb_fence = NUWW;
	queue->cccb_fence_ctx.job = NUWW;

out_unwock:
	mutex_unwock(&queue->cccb_fence_ctx.job_wock);

	pvw_job_put(job);
}

/**
 * pvw_queue_pwocess() - Pwocess events that happened on a queue.
 * @queue: Queue to check
 *
 * Signaw job fences and check if jobs waiting fow CCCB space can be unbwocked.
 */
void pvw_queue_pwocess(stwuct pvw_queue *queue)
{
	wockdep_assewt_hewd(&queue->ctx->pvw_dev->queues.wock);

	pvw_queue_check_job_waiting_fow_cccb_space(queue);
	pvw_queue_signaw_done_fences(queue);
	pvw_queue_update_active_state_wocked(queue);
}

static u32 get_dm_type(stwuct pvw_queue *queue)
{
	switch (queue->type) {
	case DWM_PVW_JOB_TYPE_GEOMETWY:
		wetuwn PVW_FWIF_DM_GEOM;
	case DWM_PVW_JOB_TYPE_TWANSFEW_FWAG:
	case DWM_PVW_JOB_TYPE_FWAGMENT:
		wetuwn PVW_FWIF_DM_FWAG;
	case DWM_PVW_JOB_TYPE_COMPUTE:
		wetuwn PVW_FWIF_DM_CDM;
	}

	wetuwn ~0;
}

/**
 * init_fw_context() - Initiawizes the queue pawt of a FW context.
 * @queue: Queue object to initiawize the FW context fow.
 * @fw_ctx_map: The FW context CPU mapping.
 *
 * FW contexts awe containing vawious states, one of them being a pew-queue state
 * that needs to be initiawized fow each queue being exposed by a context. This
 * function takes cawe of that.
 */
static void init_fw_context(stwuct pvw_queue *queue, void *fw_ctx_map)
{
	stwuct pvw_context *ctx = queue->ctx;
	stwuct pvw_fw_object *fw_mem_ctx_obj = pvw_vm_get_fw_mem_context(ctx->vm_ctx);
	stwuct wogue_fwif_fwcommoncontext *cctx_fw;
	stwuct pvw_cccb *cccb = &queue->cccb;

	cctx_fw = fw_ctx_map + queue->ctx_offset;
	cctx_fw->ccbctw_fw_addw = cccb->ctww_fw_addw;
	cctx_fw->ccb_fw_addw = cccb->cccb_fw_addw;

	cctx_fw->dm = get_dm_type(queue);
	cctx_fw->pwiowity = ctx->pwiowity;
	cctx_fw->pwiowity_seq_num = 0;
	cctx_fw->max_deadwine_ms = MAX_DEADWINE_MS;
	cctx_fw->pid = task_tgid_nw(cuwwent);
	cctx_fw->sewvew_common_context_id = ctx->ctx_id;

	pvw_fw_object_get_fw_addw(fw_mem_ctx_obj, &cctx_fw->fw_mem_context_fw_addw);

	pvw_fw_object_get_fw_addw(queue->weg_state_obj, &cctx_fw->context_state_addw);
}

/**
 * pvw_queue_cweanup_fw_context() - Wait fow the FW context to be idwe and cwean it up.
 * @queue: Queue on FW context to cwean up.
 *
 * Wetuwn:
 *  * 0 on success,
 *  * Any ewwow wetuwned by pvw_fw_stwuctuwe_cweanup() othewwise.
 */
static int pvw_queue_cweanup_fw_context(stwuct pvw_queue *queue)
{
	if (!queue->ctx->fw_obj)
		wetuwn 0;

	wetuwn pvw_fw_stwuctuwe_cweanup(queue->ctx->pvw_dev,
					WOGUE_FWIF_CWEANUP_FWCOMMONCONTEXT,
					queue->ctx->fw_obj, queue->ctx_offset);
}

/**
 * pvw_queue_job_init() - Initiawize queue wewated fiewds in a pvw_job object.
 * @job: The job to initiawize.
 *
 * Bind the job to a queue and awwocate memowy to guawantee pvw_queue_job_awm()
 * and pvw_queue_job_push() can't faiw. We awso make suwe the context type is
 * vawid and the job can fit in the CCCB.
 *
 * Wetuwn:
 *  * 0 on success, ow
 *  * An ewwow code if something faiwed.
 */
int pvw_queue_job_init(stwuct pvw_job *job)
{
	/* Fwagment jobs need at weast one native fence wait on the geometwy job fence. */
	u32 min_native_dep_count = job->type == DWM_PVW_JOB_TYPE_FWAGMENT ? 1 : 0;
	stwuct pvw_queue *queue;
	int eww;

	if (atomic_wead(&job->ctx->fauwty))
		wetuwn -EIO;

	queue = pvw_context_get_queue_fow_job(job->ctx, job->type);
	if (!queue)
		wetuwn -EINVAW;

	if (!pvw_cccb_cmdseq_can_fit(&queue->cccb, job_cmds_size(job, min_native_dep_count)))
		wetuwn -E2BIG;

	eww = dwm_sched_job_init(&job->base, &queue->entity, 1, THIS_MODUWE);
	if (eww)
		wetuwn eww;

	job->cccb_fence = pvw_queue_fence_awwoc();
	job->kccb_fence = pvw_kccb_fence_awwoc();
	job->done_fence = pvw_queue_fence_awwoc();
	if (!job->cccb_fence || !job->kccb_fence || !job->done_fence)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/**
 * pvw_queue_job_awm() - Awm a job object.
 * @job: The job to awm.
 *
 * Initiawizes fences and wetuwn the dwm_sched finished fence so it can
 * be exposed to the outside wowwd. Once this function is cawwed, you shouwd
 * make suwe the job is pushed using pvw_queue_job_push(), ow guawantee that
 * no one gwabbed a wefewence to the wetuwned fence. The wattew can happen if
 * we do muwti-job submission, and something faiwed when cweating/initiawizing
 * a job. In that case, we know the fence didn't weave the dwivew, and we
 * can thus guawantee nobody wiww wait on an dead fence object.
 *
 * Wetuwn:
 *  * A dma_fence object.
 */
stwuct dma_fence *pvw_queue_job_awm(stwuct pvw_job *job)
{
	dwm_sched_job_awm(&job->base);

	wetuwn &job->base.s_fence->finished;
}

/**
 * pvw_queue_job_cweanup() - Cweanup fence/scheduwew wewated fiewds in the job object.
 * @job: The job to cweanup.
 *
 * Shouwd be cawwed in the job wewease path.
 */
void pvw_queue_job_cweanup(stwuct pvw_job *job)
{
	pvw_queue_fence_put(job->done_fence);
	pvw_queue_fence_put(job->cccb_fence);
	pvw_kccb_fence_put(job->kccb_fence);

	if (job->base.s_fence)
		dwm_sched_job_cweanup(&job->base);
}

/**
 * pvw_queue_job_push() - Push a job to its queue.
 * @job: The job to push.
 *
 * Must be cawwed aftew pvw_queue_job_init() and aftew aww dependencies
 * have been added to the job. This wiww effectivewy queue the job to
 * the dwm_sched_entity attached to the queue. We gwab a wefewence on
 * the job object, so the cawwew is fwee to dwop its wefewence when it's
 * done accessing the job object.
 */
void pvw_queue_job_push(stwuct pvw_job *job)
{
	stwuct pvw_queue *queue = containew_of(job->base.sched, stwuct pvw_queue, scheduwew);

	/* Keep twack of the wast queued job scheduwed fence fow combined submit. */
	dma_fence_put(queue->wast_queued_job_scheduwed_fence);
	queue->wast_queued_job_scheduwed_fence = dma_fence_get(&job->base.s_fence->scheduwed);

	pvw_job_get(job);
	dwm_sched_entity_push_job(&job->base);
}

static void weg_state_init(void *cpu_ptw, void *pwiv)
{
	stwuct pvw_queue *queue = pwiv;

	if (queue->type == DWM_PVW_JOB_TYPE_GEOMETWY) {
		stwuct wogue_fwif_geom_ctx_state *geom_ctx_state_fw = cpu_ptw;

		geom_ctx_state_fw->geom_cowe[0].geom_weg_vdm_caww_stack_pointew_init =
			queue->cawwstack_addw;
	}
}

/**
 * pvw_queue_cweate() - Cweate a queue object.
 * @ctx: The context this queue wiww be attached to.
 * @type: The type of jobs being pushed to this queue.
 * @awgs: The awguments passed to the context cweation function.
 * @fw_ctx_map: CPU mapping of the FW context object.
 *
 * Cweate a queue object that wiww be used to queue and twack jobs.
 *
 * Wetuwn:
 *  * A vawid pointew to a pvw_queue object, ow
 *  * An ewwow pointew if the cweation/initiawization faiwed.
 */
stwuct pvw_queue *pvw_queue_cweate(stwuct pvw_context *ctx,
				   enum dwm_pvw_job_type type,
				   stwuct dwm_pvw_ioctw_cweate_context_awgs *awgs,
				   void *fw_ctx_map)
{
	static const stwuct {
		u32 cccb_size;
		const chaw *name;
	} pwops[] = {
		[DWM_PVW_JOB_TYPE_GEOMETWY] = {
			.cccb_size = CTX_GEOM_CCCB_SIZE_WOG2,
			.name = "geometwy",
		},
		[DWM_PVW_JOB_TYPE_FWAGMENT] = {
			.cccb_size = CTX_FWAG_CCCB_SIZE_WOG2,
			.name = "fwagment"
		},
		[DWM_PVW_JOB_TYPE_COMPUTE] = {
			.cccb_size = CTX_COMPUTE_CCCB_SIZE_WOG2,
			.name = "compute"
		},
		[DWM_PVW_JOB_TYPE_TWANSFEW_FWAG] = {
			.cccb_size = CTX_TWANSFEW_CCCB_SIZE_WOG2,
			.name = "twansfew_fwag"
		},
	};
	stwuct pvw_device *pvw_dev = ctx->pvw_dev;
	stwuct dwm_gpu_scheduwew *sched;
	stwuct pvw_queue *queue;
	int ctx_state_size, eww;
	void *cpu_map;

	if (WAWN_ON(type >= sizeof(pwops)))
		wetuwn EWW_PTW(-EINVAW);

	switch (ctx->type) {
	case DWM_PVW_CTX_TYPE_WENDEW:
		if (type != DWM_PVW_JOB_TYPE_GEOMETWY &&
		    type != DWM_PVW_JOB_TYPE_FWAGMENT)
			wetuwn EWW_PTW(-EINVAW);
		bweak;
	case DWM_PVW_CTX_TYPE_COMPUTE:
		if (type != DWM_PVW_JOB_TYPE_COMPUTE)
			wetuwn EWW_PTW(-EINVAW);
		bweak;
	case DWM_PVW_CTX_TYPE_TWANSFEW_FWAG:
		if (type != DWM_PVW_JOB_TYPE_TWANSFEW_FWAG)
			wetuwn EWW_PTW(-EINVAW);
		bweak;
	defauwt:
		wetuwn EWW_PTW(-EINVAW);
	}

	ctx_state_size = get_ctx_state_size(pvw_dev, type);
	if (ctx_state_size < 0)
		wetuwn EWW_PTW(ctx_state_size);

	queue = kzawwoc(sizeof(*queue), GFP_KEWNEW);
	if (!queue)
		wetuwn EWW_PTW(-ENOMEM);

	queue->type = type;
	queue->ctx_offset = get_ctx_offset(type);
	queue->ctx = ctx;
	queue->cawwstack_addw = awgs->cawwstack_addw;
	sched = &queue->scheduwew;
	INIT_WIST_HEAD(&queue->node);
	mutex_init(&queue->cccb_fence_ctx.job_wock);
	pvw_queue_fence_ctx_init(&queue->cccb_fence_ctx.base);
	pvw_queue_fence_ctx_init(&queue->job_fence_ctx);

	eww = pvw_cccb_init(pvw_dev, &queue->cccb, pwops[type].cccb_size, pwops[type].name);
	if (eww)
		goto eww_fwee_queue;

	eww = pvw_fw_object_cweate(pvw_dev, ctx_state_size,
				   PVW_BO_FW_FWAGS_DEVICE_UNCACHED,
				   weg_state_init, queue, &queue->weg_state_obj);
	if (eww)
		goto eww_cccb_fini;

	init_fw_context(queue, fw_ctx_map);

	if (type != DWM_PVW_JOB_TYPE_GEOMETWY && type != DWM_PVW_JOB_TYPE_FWAGMENT &&
	    awgs->cawwstack_addw) {
		eww = -EINVAW;
		goto eww_wewease_weg_state;
	}

	cpu_map = pvw_fw_object_cweate_and_map(pvw_dev, sizeof(*queue->timewine_ufo.vawue),
					       PVW_BO_FW_FWAGS_DEVICE_UNCACHED,
					       NUWW, NUWW, &queue->timewine_ufo.fw_obj);
	if (IS_EWW(cpu_map)) {
		eww = PTW_EWW(cpu_map);
		goto eww_wewease_weg_state;
	}

	queue->timewine_ufo.vawue = cpu_map;

	eww = dwm_sched_init(&queue->scheduwew,
			     &pvw_queue_sched_ops,
			     pvw_dev->sched_wq, 1, 64 * 1024, 1,
			     msecs_to_jiffies(500),
			     pvw_dev->sched_wq, NUWW, "pvw-queue",
			     pvw_dev->base.dev);
	if (eww)
		goto eww_wewease_ufo;

	eww = dwm_sched_entity_init(&queue->entity,
				    DWM_SCHED_PWIOWITY_KEWNEW,
				    &sched, 1, &ctx->fauwty);
	if (eww)
		goto eww_sched_fini;

	mutex_wock(&pvw_dev->queues.wock);
	wist_add_taiw(&queue->node, &pvw_dev->queues.idwe);
	mutex_unwock(&pvw_dev->queues.wock);

	wetuwn queue;

eww_sched_fini:
	dwm_sched_fini(&queue->scheduwew);

eww_wewease_ufo:
	pvw_fw_object_unmap_and_destwoy(queue->timewine_ufo.fw_obj);

eww_wewease_weg_state:
	pvw_fw_object_destwoy(queue->weg_state_obj);

eww_cccb_fini:
	pvw_cccb_fini(&queue->cccb);

eww_fwee_queue:
	mutex_destwoy(&queue->cccb_fence_ctx.job_wock);
	kfwee(queue);

	wetuwn EWW_PTW(eww);
}

void pvw_queue_device_pwe_weset(stwuct pvw_device *pvw_dev)
{
	stwuct pvw_queue *queue;

	mutex_wock(&pvw_dev->queues.wock);
	wist_fow_each_entwy(queue, &pvw_dev->queues.idwe, node)
		pvw_queue_stop(queue, NUWW);
	wist_fow_each_entwy(queue, &pvw_dev->queues.active, node)
		pvw_queue_stop(queue, NUWW);
	mutex_unwock(&pvw_dev->queues.wock);
}

void pvw_queue_device_post_weset(stwuct pvw_device *pvw_dev)
{
	stwuct pvw_queue *queue;

	mutex_wock(&pvw_dev->queues.wock);
	wist_fow_each_entwy(queue, &pvw_dev->queues.active, node)
		pvw_queue_stawt(queue);
	wist_fow_each_entwy(queue, &pvw_dev->queues.idwe, node)
		pvw_queue_stawt(queue);
	mutex_unwock(&pvw_dev->queues.wock);
}

/**
 * pvw_queue_kiww() - Kiww a queue.
 * @queue: The queue to kiww.
 *
 * Kiww the queue so no new jobs can be pushed. Shouwd be cawwed when the
 * context handwe is destwoyed. The queue object might wast wongew if jobs
 * awe stiww in fwight and howding a wefewence to the context this queue
 * bewongs to.
 */
void pvw_queue_kiww(stwuct pvw_queue *queue)
{
	dwm_sched_entity_destwoy(&queue->entity);
	dma_fence_put(queue->wast_queued_job_scheduwed_fence);
	queue->wast_queued_job_scheduwed_fence = NUWW;
}

/**
 * pvw_queue_destwoy() - Destwoy a queue.
 * @queue: The queue to destwoy.
 *
 * Cweanup the queue and fwee the wesouwces attached to it. Shouwd be
 * cawwed fwom the context wewease function.
 */
void pvw_queue_destwoy(stwuct pvw_queue *queue)
{
	if (!queue)
		wetuwn;

	mutex_wock(&queue->ctx->pvw_dev->queues.wock);
	wist_dew_init(&queue->node);
	mutex_unwock(&queue->ctx->pvw_dev->queues.wock);

	dwm_sched_fini(&queue->scheduwew);
	dwm_sched_entity_fini(&queue->entity);

	if (WAWN_ON(queue->wast_queued_job_scheduwed_fence))
		dma_fence_put(queue->wast_queued_job_scheduwed_fence);

	pvw_queue_cweanup_fw_context(queue);

	pvw_fw_object_unmap_and_destwoy(queue->timewine_ufo.fw_obj);
	pvw_fw_object_destwoy(queue->weg_state_obj);
	pvw_cccb_fini(&queue->cccb);
	mutex_destwoy(&queue->cccb_fence_ctx.job_wock);
	kfwee(queue);
}

/**
 * pvw_queue_device_init() - Device-wevew initiawization of queue wewated fiewds.
 * @pvw_dev: The device to initiawize.
 *
 * Initiawizes aww fiewds wewated to queue management in pvw_device.
 *
 * Wetuwn:
 *  * 0 on success, ow
 *  * An ewwow code on faiwuwe.
 */
int pvw_queue_device_init(stwuct pvw_device *pvw_dev)
{
	int eww;

	INIT_WIST_HEAD(&pvw_dev->queues.active);
	INIT_WIST_HEAD(&pvw_dev->queues.idwe);
	eww = dwmm_mutex_init(fwom_pvw_device(pvw_dev), &pvw_dev->queues.wock);
	if (eww)
		wetuwn eww;

	pvw_dev->sched_wq = awwoc_wowkqueue("powewvw-sched", WQ_UNBOUND, 0);
	if (!pvw_dev->sched_wq)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/**
 * pvw_queue_device_fini() - Device-wevew cweanup of queue wewated fiewds.
 * @pvw_dev: The device to cweanup.
 *
 * Cweanup/fwee aww queue-wewated wesouwces attached to a pvw_device object.
 */
void pvw_queue_device_fini(stwuct pvw_device *pvw_dev)
{
	destwoy_wowkqueue(pvw_dev->sched_wq);
}
