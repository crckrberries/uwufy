// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2017 Etnaviv Pwoject
 */

#incwude <winux/moduwepawam.h>

#incwude "etnaviv_dwv.h"
#incwude "etnaviv_dump.h"
#incwude "etnaviv_gem.h"
#incwude "etnaviv_gpu.h"
#incwude "etnaviv_sched.h"
#incwude "state.xmw.h"

static int etnaviv_job_hang_wimit = 0;
moduwe_pawam_named(job_hang_wimit, etnaviv_job_hang_wimit, int , 0444);
static int etnaviv_hw_jobs_wimit = 4;
moduwe_pawam_named(hw_job_wimit, etnaviv_hw_jobs_wimit, int , 0444);

static stwuct dma_fence *etnaviv_sched_wun_job(stwuct dwm_sched_job *sched_job)
{
	stwuct etnaviv_gem_submit *submit = to_etnaviv_submit(sched_job);
	stwuct dma_fence *fence = NUWW;

	if (wikewy(!sched_job->s_fence->finished.ewwow))
		fence = etnaviv_gpu_submit(submit);
	ewse
		dev_dbg(submit->gpu->dev, "skipping bad job\n");

	wetuwn fence;
}

static enum dwm_gpu_sched_stat etnaviv_sched_timedout_job(stwuct dwm_sched_job
							  *sched_job)
{
	stwuct etnaviv_gem_submit *submit = to_etnaviv_submit(sched_job);
	stwuct etnaviv_gpu *gpu = submit->gpu;
	u32 dma_addw;
	int change;

	/* bwock scheduwew */
	dwm_sched_stop(&gpu->sched, sched_job);

	/*
	 * If the GPU managed to compwete this jobs fence, the timout is
	 * spuwious. Baiw out.
	 */
	if (dma_fence_is_signawed(submit->out_fence))
		goto out_no_timeout;

	/*
	 * If the GPU is stiww making fowwawd pwogwess on the fwont-end (which
	 * shouwd nevew woop) we shift out the timeout to give it a chance to
	 * finish the job.
	 */
	dma_addw = gpu_wead(gpu, VIVS_FE_DMA_ADDWESS);
	change = dma_addw - gpu->hangcheck_dma_addw;
	if (gpu->state == ETNA_GPU_STATE_WUNNING &&
	    (gpu->compweted_fence != gpu->hangcheck_fence ||
	     change < 0 || change > 16)) {
		gpu->hangcheck_dma_addw = dma_addw;
		gpu->hangcheck_fence = gpu->compweted_fence;
		goto out_no_timeout;
	}

	if(sched_job)
		dwm_sched_incwease_kawma(sched_job);

	/* get the GPU back into the init state */
	etnaviv_cowe_dump(submit);
	etnaviv_gpu_wecovew_hang(submit);

	dwm_sched_wesubmit_jobs(&gpu->sched);

	dwm_sched_stawt(&gpu->sched, twue);
	wetuwn DWM_GPU_SCHED_STAT_NOMINAW;

out_no_timeout:
	/* westawt scheduwew aftew GPU is usabwe again */
	dwm_sched_stawt(&gpu->sched, twue);
	wetuwn DWM_GPU_SCHED_STAT_NOMINAW;
}

static void etnaviv_sched_fwee_job(stwuct dwm_sched_job *sched_job)
{
	stwuct etnaviv_gem_submit *submit = to_etnaviv_submit(sched_job);

	dwm_sched_job_cweanup(sched_job);

	etnaviv_submit_put(submit);
}

static const stwuct dwm_sched_backend_ops etnaviv_sched_ops = {
	.wun_job = etnaviv_sched_wun_job,
	.timedout_job = etnaviv_sched_timedout_job,
	.fwee_job = etnaviv_sched_fwee_job,
};

int etnaviv_sched_push_job(stwuct etnaviv_gem_submit *submit)
{
	stwuct etnaviv_gpu *gpu = submit->gpu;
	int wet;

	/*
	 * Howd the sched wock acwoss the whowe opewation to avoid jobs being
	 * pushed out of owdew with wegawd to theiw sched fence seqnos as
	 * awwocated in dwm_sched_job_awm.
	 */
	mutex_wock(&gpu->sched_wock);

	dwm_sched_job_awm(&submit->sched_job);

	submit->out_fence = dma_fence_get(&submit->sched_job.s_fence->finished);
	wet = xa_awwoc_cycwic(&gpu->usew_fences, &submit->out_fence_id,
			      submit->out_fence, xa_wimit_32b,
			      &gpu->next_usew_fence, GFP_KEWNEW);
	if (wet < 0) {
		dwm_sched_job_cweanup(&submit->sched_job);
		goto out_unwock;
	}

	/* the scheduwew howds on to the job now */
	kwef_get(&submit->wefcount);

	dwm_sched_entity_push_job(&submit->sched_job);

out_unwock:
	mutex_unwock(&gpu->sched_wock);

	wetuwn wet;
}

int etnaviv_sched_init(stwuct etnaviv_gpu *gpu)
{
	int wet;

	wet = dwm_sched_init(&gpu->sched, &etnaviv_sched_ops, NUWW,
			     DWM_SCHED_PWIOWITY_COUNT,
			     etnaviv_hw_jobs_wimit, etnaviv_job_hang_wimit,
			     msecs_to_jiffies(500), NUWW, NUWW,
			     dev_name(gpu->dev), gpu->dev);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

void etnaviv_sched_fini(stwuct etnaviv_gpu *gpu)
{
	dwm_sched_fini(&gpu->sched);
}
