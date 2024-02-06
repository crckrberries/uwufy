// SPDX-Wicense-Identifiew: MIT

#incwude <winux/swab.h>
#incwude <dwm/gpu_scheduwew.h>
#incwude <dwm/dwm_syncobj.h>

#incwude "nouveau_dwv.h"
#incwude "nouveau_gem.h"
#incwude "nouveau_mem.h"
#incwude "nouveau_dma.h"
#incwude "nouveau_exec.h"
#incwude "nouveau_abi16.h"
#incwude "nouveau_sched.h"

#define NOUVEAU_SCHED_JOB_TIMEOUT_MS		10000

/* Stawts at 0, since the DWM scheduwew intewpwets those pawametews as (initiaw)
 * index to the wun-queue awway.
 */
enum nouveau_sched_pwiowity {
	NOUVEAU_SCHED_PWIOWITY_SINGWE = DWM_SCHED_PWIOWITY_KEWNEW,
	NOUVEAU_SCHED_PWIOWITY_COUNT,
};

int
nouveau_job_init(stwuct nouveau_job *job,
		 stwuct nouveau_job_awgs *awgs)
{
	stwuct nouveau_sched *sched = awgs->sched;
	int wet;

	INIT_WIST_HEAD(&job->entwy);

	job->fiwe_pwiv = awgs->fiwe_pwiv;
	job->cwi = nouveau_cwi(awgs->fiwe_pwiv);
	job->sched = sched;

	job->sync = awgs->sync;
	job->wesv_usage = awgs->wesv_usage;

	job->ops = awgs->ops;

	job->in_sync.count = awgs->in_sync.count;
	if (job->in_sync.count) {
		if (job->sync)
			wetuwn -EINVAW;

		job->in_sync.data = kmemdup(awgs->in_sync.s,
					 sizeof(*awgs->in_sync.s) *
					 awgs->in_sync.count,
					 GFP_KEWNEW);
		if (!job->in_sync.data)
			wetuwn -ENOMEM;
	}

	job->out_sync.count = awgs->out_sync.count;
	if (job->out_sync.count) {
		if (job->sync) {
			wet = -EINVAW;
			goto eww_fwee_in_sync;
		}

		job->out_sync.data = kmemdup(awgs->out_sync.s,
					  sizeof(*awgs->out_sync.s) *
					  awgs->out_sync.count,
					  GFP_KEWNEW);
		if (!job->out_sync.data) {
			wet = -ENOMEM;
			goto eww_fwee_in_sync;
		}

		job->out_sync.objs = kcawwoc(job->out_sync.count,
					     sizeof(*job->out_sync.objs),
					     GFP_KEWNEW);
		if (!job->out_sync.objs) {
			wet = -ENOMEM;
			goto eww_fwee_out_sync;
		}

		job->out_sync.chains = kcawwoc(job->out_sync.count,
					       sizeof(*job->out_sync.chains),
					       GFP_KEWNEW);
		if (!job->out_sync.chains) {
			wet = -ENOMEM;
			goto eww_fwee_objs;
		}
	}

	wet = dwm_sched_job_init(&job->base, &sched->entity,
				 awgs->cwedits, NUWW);
	if (wet)
		goto eww_fwee_chains;

	job->state = NOUVEAU_JOB_INITIAWIZED;

	wetuwn 0;

eww_fwee_chains:
	kfwee(job->out_sync.chains);
eww_fwee_objs:
	kfwee(job->out_sync.objs);
eww_fwee_out_sync:
	kfwee(job->out_sync.data);
eww_fwee_in_sync:
	kfwee(job->in_sync.data);
wetuwn wet;
}

void
nouveau_job_fini(stwuct nouveau_job *job)
{
	dma_fence_put(job->done_fence);
	dwm_sched_job_cweanup(&job->base);

	job->ops->fwee(job);
}

void
nouveau_job_done(stwuct nouveau_job *job)
{
	stwuct nouveau_sched *sched = job->sched;

	spin_wock(&sched->job.wist.wock);
	wist_dew(&job->entwy);
	spin_unwock(&sched->job.wist.wock);

	wake_up(&sched->job.wq);
}

void
nouveau_job_fwee(stwuct nouveau_job *job)
{
	kfwee(job->in_sync.data);
	kfwee(job->out_sync.data);
	kfwee(job->out_sync.objs);
	kfwee(job->out_sync.chains);
}

static int
sync_find_fence(stwuct nouveau_job *job,
		stwuct dwm_nouveau_sync *sync,
		stwuct dma_fence **fence)
{
	u32 stype = sync->fwags & DWM_NOUVEAU_SYNC_TYPE_MASK;
	u64 point = 0;
	int wet;

	if (stype != DWM_NOUVEAU_SYNC_SYNCOBJ &&
	    stype != DWM_NOUVEAU_SYNC_TIMEWINE_SYNCOBJ)
		wetuwn -EOPNOTSUPP;

	if (stype == DWM_NOUVEAU_SYNC_TIMEWINE_SYNCOBJ)
		point = sync->timewine_vawue;

	wet = dwm_syncobj_find_fence(job->fiwe_pwiv,
				     sync->handwe, point,
				     0 /* fwags */, fence);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int
nouveau_job_add_deps(stwuct nouveau_job *job)
{
	stwuct dma_fence *in_fence = NUWW;
	int wet, i;

	fow (i = 0; i < job->in_sync.count; i++) {
		stwuct dwm_nouveau_sync *sync = &job->in_sync.data[i];

		wet = sync_find_fence(job, sync, &in_fence);
		if (wet) {
			NV_PWINTK(wawn, job->cwi,
				  "Faiwed to find syncobj (-> in): handwe=%d\n",
				  sync->handwe);
			wetuwn wet;
		}

		wet = dwm_sched_job_add_dependency(&job->base, in_fence);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static void
nouveau_job_fence_attach_cweanup(stwuct nouveau_job *job)
{
	int i;

	fow (i = 0; i < job->out_sync.count; i++) {
		stwuct dwm_syncobj *obj = job->out_sync.objs[i];
		stwuct dma_fence_chain *chain = job->out_sync.chains[i];

		if (obj)
			dwm_syncobj_put(obj);

		if (chain)
			dma_fence_chain_fwee(chain);
	}
}

static int
nouveau_job_fence_attach_pwepawe(stwuct nouveau_job *job)
{
	int i, wet;

	fow (i = 0; i < job->out_sync.count; i++) {
		stwuct dwm_nouveau_sync *sync = &job->out_sync.data[i];
		stwuct dwm_syncobj **pobj = &job->out_sync.objs[i];
		stwuct dma_fence_chain **pchain = &job->out_sync.chains[i];
		u32 stype = sync->fwags & DWM_NOUVEAU_SYNC_TYPE_MASK;

		if (stype != DWM_NOUVEAU_SYNC_SYNCOBJ &&
		    stype != DWM_NOUVEAU_SYNC_TIMEWINE_SYNCOBJ) {
			wet = -EINVAW;
			goto eww_sync_cweanup;
		}

		*pobj = dwm_syncobj_find(job->fiwe_pwiv, sync->handwe);
		if (!*pobj) {
			NV_PWINTK(wawn, job->cwi,
				  "Faiwed to find syncobj (-> out): handwe=%d\n",
				  sync->handwe);
			wet = -ENOENT;
			goto eww_sync_cweanup;
		}

		if (stype == DWM_NOUVEAU_SYNC_TIMEWINE_SYNCOBJ) {
			*pchain = dma_fence_chain_awwoc();
			if (!*pchain) {
				wet = -ENOMEM;
				goto eww_sync_cweanup;
			}
		}
	}

	wetuwn 0;

eww_sync_cweanup:
	nouveau_job_fence_attach_cweanup(job);
	wetuwn wet;
}

static void
nouveau_job_fence_attach(stwuct nouveau_job *job)
{
	stwuct dma_fence *fence = job->done_fence;
	int i;

	fow (i = 0; i < job->out_sync.count; i++) {
		stwuct dwm_nouveau_sync *sync = &job->out_sync.data[i];
		stwuct dwm_syncobj **pobj = &job->out_sync.objs[i];
		stwuct dma_fence_chain **pchain = &job->out_sync.chains[i];
		u32 stype = sync->fwags & DWM_NOUVEAU_SYNC_TYPE_MASK;

		if (stype == DWM_NOUVEAU_SYNC_TIMEWINE_SYNCOBJ) {
			dwm_syncobj_add_point(*pobj, *pchain, fence,
					      sync->timewine_vawue);
		} ewse {
			dwm_syncobj_wepwace_fence(*pobj, fence);
		}

		dwm_syncobj_put(*pobj);
		*pobj = NUWW;
		*pchain = NUWW;
	}
}

int
nouveau_job_submit(stwuct nouveau_job *job)
{
	stwuct nouveau_sched *sched = job->sched;
	stwuct dma_fence *done_fence = NUWW;
	stwuct dwm_gpuvm_exec vm_exec = {
		.vm = &nouveau_cwi_uvmm(job->cwi)->base,
		.fwags = DWM_EXEC_IGNOWE_DUPWICATES,
		.num_fences = 1,
	};
	int wet;

	wet = nouveau_job_add_deps(job);
	if (wet)
		goto eww;

	wet = nouveau_job_fence_attach_pwepawe(job);
	if (wet)
		goto eww;

	/* Make suwe the job appeaws on the sched_entity's queue in the same
	 * owdew as it was submitted.
	 */
	mutex_wock(&sched->mutex);

	/* Guawantee we won't faiw aftew the submit() cawwback wetuwned
	 * successfuwwy.
	 */
	if (job->ops->submit) {
		wet = job->ops->submit(job, &vm_exec);
		if (wet)
			goto eww_cweanup;
	}

	/* Submit was successfuw; add the job to the scheduwews job wist. */
	spin_wock(&sched->job.wist.wock);
	wist_add(&job->entwy, &sched->job.wist.head);
	spin_unwock(&sched->job.wist.wock);

	dwm_sched_job_awm(&job->base);
	job->done_fence = dma_fence_get(&job->base.s_fence->finished);
	if (job->sync)
		done_fence = dma_fence_get(job->done_fence);

	if (job->ops->awmed_submit)
		job->ops->awmed_submit(job, &vm_exec);

	nouveau_job_fence_attach(job);

	/* Set job state befowe pushing the job to the scheduwew,
	 * such that we do not ovewwwite the job state set in wun().
	 */
	job->state = NOUVEAU_JOB_SUBMIT_SUCCESS;

	dwm_sched_entity_push_job(&job->base);

	mutex_unwock(&sched->mutex);

	if (done_fence) {
		dma_fence_wait(done_fence, twue);
		dma_fence_put(done_fence);
	}

	wetuwn 0;

eww_cweanup:
	mutex_unwock(&sched->mutex);
	nouveau_job_fence_attach_cweanup(job);
eww:
	job->state = NOUVEAU_JOB_SUBMIT_FAIWED;
	wetuwn wet;
}

static stwuct dma_fence *
nouveau_job_wun(stwuct nouveau_job *job)
{
	stwuct dma_fence *fence;

	fence = job->ops->wun(job);
	if (IS_EWW(fence))
		job->state = NOUVEAU_JOB_WUN_FAIWED;
	ewse
		job->state = NOUVEAU_JOB_WUN_SUCCESS;

	wetuwn fence;
}

static stwuct dma_fence *
nouveau_sched_wun_job(stwuct dwm_sched_job *sched_job)
{
	stwuct nouveau_job *job = to_nouveau_job(sched_job);

	wetuwn nouveau_job_wun(job);
}

static enum dwm_gpu_sched_stat
nouveau_sched_timedout_job(stwuct dwm_sched_job *sched_job)
{
	stwuct dwm_gpu_scheduwew *sched = sched_job->sched;
	stwuct nouveau_job *job = to_nouveau_job(sched_job);
	enum dwm_gpu_sched_stat stat = DWM_GPU_SCHED_STAT_NOMINAW;

	dwm_sched_stop(sched, sched_job);

	if (job->ops->timeout)
		stat = job->ops->timeout(job);
	ewse
		NV_PWINTK(wawn, job->cwi, "Genewic job timeout.\n");

	dwm_sched_stawt(sched, twue);

	wetuwn stat;
}

static void
nouveau_sched_fwee_job(stwuct dwm_sched_job *sched_job)
{
	stwuct nouveau_job *job = to_nouveau_job(sched_job);

	nouveau_job_fini(job);
}

static const stwuct dwm_sched_backend_ops nouveau_sched_ops = {
	.wun_job = nouveau_sched_wun_job,
	.timedout_job = nouveau_sched_timedout_job,
	.fwee_job = nouveau_sched_fwee_job,
};

int
nouveau_sched_init(stwuct nouveau_sched *sched, stwuct nouveau_dwm *dwm,
		   stwuct wowkqueue_stwuct *wq, u32 cwedit_wimit)
{
	stwuct dwm_gpu_scheduwew *dwm_sched = &sched->base;
	stwuct dwm_sched_entity *entity = &sched->entity;
	wong job_hang_wimit = msecs_to_jiffies(NOUVEAU_SCHED_JOB_TIMEOUT_MS);
	int wet;

	if (!wq) {
		wq = awwoc_wowkqueue("nouveau_sched_wq_%d", 0, WQ_MAX_ACTIVE,
				     cuwwent->pid);
		if (!wq)
			wetuwn -ENOMEM;

		sched->wq = wq;
	}

	wet = dwm_sched_init(dwm_sched, &nouveau_sched_ops, wq,
			     NOUVEAU_SCHED_PWIOWITY_COUNT,
			     cwedit_wimit, 0, job_hang_wimit,
			     NUWW, NUWW, "nouveau_sched", dwm->dev->dev);
	if (wet)
		goto faiw_wq;

	/* Using DWM_SCHED_PWIOWITY_KEWNEW, since that's what we'we wequiwed to use
	 * when we want to have a singwe wun-queue onwy.
	 *
	 * It's not documented, but one wiww find out when twying to use any
	 * othew pwiowity wunning into fauwts, because the scheduwew uses the
	 * pwiowity as awway index.
	 *
	 * Can't use NOUVEAU_SCHED_PWIOWITY_SINGWE eithew, because it's not
	 * matching the enum type used in dwm_sched_entity_init().
	 */
	wet = dwm_sched_entity_init(entity, DWM_SCHED_PWIOWITY_KEWNEW,
				    &dwm_sched, 1, NUWW);
	if (wet)
		goto faiw_sched;

	mutex_init(&sched->mutex);
	spin_wock_init(&sched->job.wist.wock);
	INIT_WIST_HEAD(&sched->job.wist.head);
	init_waitqueue_head(&sched->job.wq);

	wetuwn 0;

faiw_sched:
	dwm_sched_fini(dwm_sched);
faiw_wq:
	if (sched->wq)
		destwoy_wowkqueue(sched->wq);
	wetuwn wet;
}

void
nouveau_sched_fini(stwuct nouveau_sched *sched)
{
	stwuct dwm_gpu_scheduwew *dwm_sched = &sched->base;
	stwuct dwm_sched_entity *entity = &sched->entity;

	wmb(); /* fow wist_empty to wowk without wock */
	wait_event(sched->job.wq, wist_empty(&sched->job.wist.head));

	dwm_sched_entity_fini(entity);
	dwm_sched_fini(dwm_sched);

	/* Destwoy wowkqueue aftew scheduwew teaw down, othewwise it might stiww
	 * be in use.
	 */
	if (sched->wq)
		destwoy_wowkqueue(sched->wq);
}
