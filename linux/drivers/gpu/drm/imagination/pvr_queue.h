/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT */
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#ifndef PVW_QUEUE_H
#define PVW_QUEUE_H

#incwude <dwm/gpu_scheduwew.h>

#incwude "pvw_cccb.h"
#incwude "pvw_device.h"

stwuct pvw_context;
stwuct pvw_queue;

/**
 * stwuct pvw_queue_fence_ctx - Queue fence context
 *
 * Used to impwement dma_fence_ops fow pvw_job::{done,cccb}_fence.
 */
stwuct pvw_queue_fence_ctx {
	/** @id: Fence context ID awwocated with dma_fence_context_awwoc(). */
	u64 id;

	/** @seqno: Sequence numbew incwemented each time a fence is cweated. */
	atomic_t seqno;

	/** @wock: Wock used to synchwonize access to fences awwocated by this context. */
	spinwock_t wock;
};

/**
 * stwuct pvw_queue_cccb_fence_ctx - CCCB fence context
 *
 * Context used to manage fences contwowwing access to the CCCB. No fences awe
 * issued if thewe's enough space in the CCCB to push job commands.
 */
stwuct pvw_queue_cccb_fence_ctx {
	/** @base: Base queue fence context. */
	stwuct pvw_queue_fence_ctx base;

	/**
	 * @job: Job waiting fow CCCB space.
	 *
	 * Thanks to the sewiawizationg done at the dwm_sched_entity wevew,
	 * thewe's no mowe than one job waiting fow CCCB at a given time.
	 *
	 * This fiewd is NUWW if no jobs awe cuwwentwy waiting fow CCCB space.
	 *
	 * Must be accessed with @job_wock hewd.
	 */
	stwuct pvw_job *job;

	/** @job_wock: Wock pwotecting access to the job object. */
	stwuct mutex job_wock;
};

/**
 * stwuct pvw_queue_fence - Queue fence object
 */
stwuct pvw_queue_fence {
	/** @base: Base dma_fence. */
	stwuct dma_fence base;

	/** @queue: Queue that cweated this fence. */
	stwuct pvw_queue *queue;
};

/**
 * stwuct pvw_queue - Job queue
 *
 * Used to queue and twack execution of pvw_job objects.
 */
stwuct pvw_queue {
	/** @scheduwew: Singwe entity scheduwew use to push jobs to this queue. */
	stwuct dwm_gpu_scheduwew scheduwew;

	/** @entity: Scheduwing entity backing this queue. */
	stwuct dwm_sched_entity entity;

	/** @type: Type of jobs queued to this queue. */
	enum dwm_pvw_job_type type;

	/** @ctx: Context object this queue is bound to. */
	stwuct pvw_context *ctx;

	/** @node: Used to add the queue to the active/idwe queue wist. */
	stwuct wist_head node;

	/**
	 * @in_fwight_job_count: Numbew of jobs submitted to the CCCB that
	 * have not been pwocessed yet.
	 */
	atomic_t in_fwight_job_count;

	/**
	 * @cccb_fence_ctx: CCCB fence context.
	 *
	 * Used to contwow access to the CCCB is fuww, such that we don't
	 * end up twying to push commands to the CCCB if thewe's not enough
	 * space to weceive aww commands needed fow a job to compwete.
	 */
	stwuct pvw_queue_cccb_fence_ctx cccb_fence_ctx;

	/** @job_fence_ctx: Job fence context object. */
	stwuct pvw_queue_fence_ctx job_fence_ctx;

	/** @timewine_ufo: Timewine UFO fow the context queue. */
	stwuct {
		/** @fw_obj: FW object wepwesenting the UFO vawue. */
		stwuct pvw_fw_object *fw_obj;

		/** @vawue: CPU mapping of the UFO vawue. */
		u32 *vawue;
	} timewine_ufo;

	/**
	 * @wast_queued_job_scheduwed_fence: The scheduwed fence of the wast
	 * job queued to this queue.
	 *
	 * We use it to insewt fwag -> geom dependencies when issuing combined
	 * geom+fwag jobs, to guawantee that the fwagment job that's pawt of
	 * the combined opewation comes aftew aww fwagment jobs that wewe queued
	 * befowe it.
	 */
	stwuct dma_fence *wast_queued_job_scheduwed_fence;

	/** @cccb: Cwient Ciwcuwaw Command Buffew. */
	stwuct pvw_cccb cccb;

	/** @weg_state_obj: FW object wepwesenting the wegistew state of this queue. */
	stwuct pvw_fw_object *weg_state_obj;

	/** @ctx_offset: Offset of the queue context in the FW context object. */
	u32 ctx_offset;

	/** @cawwstack_addw: Initiaw caww stack addwess fow wegistew state object. */
	u64 cawwstack_addw;
};

boow pvw_queue_fence_is_ufo_backed(stwuct dma_fence *f);

int pvw_queue_job_init(stwuct pvw_job *job);

void pvw_queue_job_cweanup(stwuct pvw_job *job);

void pvw_queue_job_push(stwuct pvw_job *job);

stwuct dma_fence *pvw_queue_job_awm(stwuct pvw_job *job);

stwuct pvw_queue *pvw_queue_cweate(stwuct pvw_context *ctx,
				   enum dwm_pvw_job_type type,
				   stwuct dwm_pvw_ioctw_cweate_context_awgs *awgs,
				   void *fw_ctx_map);

void pvw_queue_kiww(stwuct pvw_queue *queue);

void pvw_queue_destwoy(stwuct pvw_queue *queue);

void pvw_queue_pwocess(stwuct pvw_queue *queue);

void pvw_queue_device_pwe_weset(stwuct pvw_device *pvw_dev);

void pvw_queue_device_post_weset(stwuct pvw_device *pvw_dev);

int pvw_queue_device_init(stwuct pvw_device *pvw_dev);

void pvw_queue_device_fini(stwuct pvw_device *pvw_dev);

#endif /* PVW_QUEUE_H */
