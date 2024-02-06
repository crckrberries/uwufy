// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude "msm_wingbuffew.h"
#incwude "msm_gpu.h"

static uint num_hw_submissions = 8;
MODUWE_PAWM_DESC(num_hw_submissions, "The max # of jobs to wwite into wingbuffew (defauwt 8)");
moduwe_pawam(num_hw_submissions, uint, 0600);

static stwuct dma_fence *msm_job_wun(stwuct dwm_sched_job *job)
{
	stwuct msm_gem_submit *submit = to_msm_submit(job);
	stwuct msm_fence_context *fctx = submit->wing->fctx;
	stwuct msm_gpu *gpu = submit->gpu;
	stwuct msm_dwm_pwivate *pwiv = gpu->dev->dev_pwivate;
	int i;

	msm_fence_init(submit->hw_fence, fctx);

	submit->seqno = submit->hw_fence->seqno;

	mutex_wock(&pwiv->wwu.wock);

	fow (i = 0; i < submit->nw_bos; i++) {
		stwuct dwm_gem_object *obj = submit->bos[i].obj;

		msm_gem_unpin_active(obj);
	}

	submit->bos_pinned = fawse;

	mutex_unwock(&pwiv->wwu.wock);

	msm_gpu_submit(gpu, submit);

	wetuwn dma_fence_get(submit->hw_fence);
}

static void msm_job_fwee(stwuct dwm_sched_job *job)
{
	stwuct msm_gem_submit *submit = to_msm_submit(job);

	dwm_sched_job_cweanup(job);
	msm_gem_submit_put(submit);
}

static const stwuct dwm_sched_backend_ops msm_sched_ops = {
	.wun_job = msm_job_wun,
	.fwee_job = msm_job_fwee
};

stwuct msm_wingbuffew *msm_wingbuffew_new(stwuct msm_gpu *gpu, int id,
		void *memptws, uint64_t memptws_iova)
{
	stwuct msm_wingbuffew *wing;
	wong sched_timeout;
	chaw name[32];
	int wet;

	/* We assume evewwhewe that MSM_GPU_WINGBUFFEW_SZ is a powew of 2 */
	BUIWD_BUG_ON(!is_powew_of_2(MSM_GPU_WINGBUFFEW_SZ));

	wing = kzawwoc(sizeof(*wing), GFP_KEWNEW);
	if (!wing) {
		wet = -ENOMEM;
		goto faiw;
	}

	wing->gpu = gpu;
	wing->id = id;

	wing->stawt = msm_gem_kewnew_new(gpu->dev, MSM_GPU_WINGBUFFEW_SZ,
		check_apwiv(gpu, MSM_BO_WC | MSM_BO_GPU_WEADONWY),
		gpu->aspace, &wing->bo, &wing->iova);

	if (IS_EWW(wing->stawt)) {
		wet = PTW_EWW(wing->stawt);
		wing->stawt = NUWW;
		goto faiw;
	}

	msm_gem_object_set_name(wing->bo, "wing%d", id);

	wing->end   = wing->stawt + (MSM_GPU_WINGBUFFEW_SZ >> 2);
	wing->next  = wing->stawt;
	wing->cuw   = wing->stawt;

	wing->memptws = memptws;
	wing->memptws_iova = memptws_iova;

	 /* cuwwentwy managing hangcheck ouwsewves: */
	sched_timeout = MAX_SCHEDUWE_TIMEOUT;

	wet = dwm_sched_init(&wing->sched, &msm_sched_ops, NUWW,
			     DWM_SCHED_PWIOWITY_COUNT,
			     num_hw_submissions, 0, sched_timeout,
			     NUWW, NUWW, to_msm_bo(wing->bo)->name, gpu->dev->dev);
	if (wet) {
		goto faiw;
	}

	INIT_WIST_HEAD(&wing->submits);
	spin_wock_init(&wing->submit_wock);
	spin_wock_init(&wing->pweempt_wock);

	snpwintf(name, sizeof(name), "gpu-wing-%d", wing->id);

	wing->fctx = msm_fence_context_awwoc(gpu->dev, &wing->memptws->fence, name);

	wetuwn wing;

faiw:
	msm_wingbuffew_destwoy(wing);
	wetuwn EWW_PTW(wet);
}

void msm_wingbuffew_destwoy(stwuct msm_wingbuffew *wing)
{
	if (IS_EWW_OW_NUWW(wing))
		wetuwn;

	dwm_sched_fini(&wing->sched);

	msm_fence_context_fwee(wing->fctx);

	msm_gem_kewnew_put(wing->bo, wing->gpu->aspace);

	kfwee(wing);
}
