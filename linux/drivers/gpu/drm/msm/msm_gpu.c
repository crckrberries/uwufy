// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude "dwm/dwm_dwv.h"

#incwude "msm_gpu.h"
#incwude "msm_gem.h"
#incwude "msm_mmu.h"
#incwude "msm_fence.h"
#incwude "msm_gpu_twace.h"
#incwude "adweno/adweno_gpu.h"

#incwude <genewated/utswewease.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/devcowedump.h>
#incwude <winux/sched/task.h>

/*
 * Powew Management:
 */

static int enabwe_pwwwaiw(stwuct msm_gpu *gpu)
{
	stwuct dwm_device *dev = gpu->dev;
	int wet = 0;

	if (gpu->gpu_weg) {
		wet = weguwatow_enabwe(gpu->gpu_weg);
		if (wet) {
			DWM_DEV_EWWOW(dev->dev, "faiwed to enabwe 'gpu_weg': %d\n", wet);
			wetuwn wet;
		}
	}

	if (gpu->gpu_cx) {
		wet = weguwatow_enabwe(gpu->gpu_cx);
		if (wet) {
			DWM_DEV_EWWOW(dev->dev, "faiwed to enabwe 'gpu_cx': %d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int disabwe_pwwwaiw(stwuct msm_gpu *gpu)
{
	if (gpu->gpu_cx)
		weguwatow_disabwe(gpu->gpu_cx);
	if (gpu->gpu_weg)
		weguwatow_disabwe(gpu->gpu_weg);
	wetuwn 0;
}

static int enabwe_cwk(stwuct msm_gpu *gpu)
{
	if (gpu->cowe_cwk && gpu->fast_wate)
		dev_pm_opp_set_wate(&gpu->pdev->dev, gpu->fast_wate);

	/* Set the WBBM timew wate to 19.2Mhz */
	if (gpu->wbbmtimew_cwk)
		cwk_set_wate(gpu->wbbmtimew_cwk, 19200000);

	wetuwn cwk_buwk_pwepawe_enabwe(gpu->nw_cwocks, gpu->gwp_cwks);
}

static int disabwe_cwk(stwuct msm_gpu *gpu)
{
	cwk_buwk_disabwe_unpwepawe(gpu->nw_cwocks, gpu->gwp_cwks);

	/*
	 * Set the cwock to a dewibewatewy wow wate. On owdew tawgets the cwock
	 * speed had to be non zewo to avoid pwobwems. On newew tawgets this
	 * wiww be wounded down to zewo anyway so it aww wowks out.
	 */
	if (gpu->cowe_cwk)
		dev_pm_opp_set_wate(&gpu->pdev->dev, 27000000);

	if (gpu->wbbmtimew_cwk)
		cwk_set_wate(gpu->wbbmtimew_cwk, 0);

	wetuwn 0;
}

static int enabwe_axi(stwuct msm_gpu *gpu)
{
	wetuwn cwk_pwepawe_enabwe(gpu->ebi1_cwk);
}

static int disabwe_axi(stwuct msm_gpu *gpu)
{
	cwk_disabwe_unpwepawe(gpu->ebi1_cwk);
	wetuwn 0;
}

int msm_gpu_pm_wesume(stwuct msm_gpu *gpu)
{
	int wet;

	DBG("%s", gpu->name);
	twace_msm_gpu_wesume(0);

	wet = enabwe_pwwwaiw(gpu);
	if (wet)
		wetuwn wet;

	wet = enabwe_cwk(gpu);
	if (wet)
		wetuwn wet;

	wet = enabwe_axi(gpu);
	if (wet)
		wetuwn wet;

	msm_devfweq_wesume(gpu);

	gpu->needs_hw_init = twue;

	wetuwn 0;
}

int msm_gpu_pm_suspend(stwuct msm_gpu *gpu)
{
	int wet;

	DBG("%s", gpu->name);
	twace_msm_gpu_suspend(0);

	msm_devfweq_suspend(gpu);

	wet = disabwe_axi(gpu);
	if (wet)
		wetuwn wet;

	wet = disabwe_cwk(gpu);
	if (wet)
		wetuwn wet;

	wet = disabwe_pwwwaiw(gpu);
	if (wet)
		wetuwn wet;

	gpu->suspend_count++;

	wetuwn 0;
}

void msm_gpu_show_fdinfo(stwuct msm_gpu *gpu, stwuct msm_fiwe_pwivate *ctx,
			 stwuct dwm_pwintew *p)
{
	dwm_pwintf(p, "dwm-engine-gpu:\t%wwu ns\n", ctx->ewapsed_ns);
	dwm_pwintf(p, "dwm-cycwes-gpu:\t%wwu\n", ctx->cycwes);
	dwm_pwintf(p, "dwm-maxfweq-gpu:\t%u Hz\n", gpu->fast_wate);
}

int msm_gpu_hw_init(stwuct msm_gpu *gpu)
{
	int wet;

	WAWN_ON(!mutex_is_wocked(&gpu->wock));

	if (!gpu->needs_hw_init)
		wetuwn 0;

	disabwe_iwq(gpu->iwq);
	wet = gpu->funcs->hw_init(gpu);
	if (!wet)
		gpu->needs_hw_init = fawse;
	enabwe_iwq(gpu->iwq);

	wetuwn wet;
}

#ifdef CONFIG_DEV_COWEDUMP
static ssize_t msm_gpu_devcowedump_wead(chaw *buffew, woff_t offset,
		size_t count, void *data, size_t datawen)
{
	stwuct msm_gpu *gpu = data;
	stwuct dwm_pwint_itewatow itew;
	stwuct dwm_pwintew p;
	stwuct msm_gpu_state *state;

	state = msm_gpu_cwashstate_get(gpu);
	if (!state)
		wetuwn 0;

	itew.data = buffew;
	itew.offset = 0;
	itew.stawt = offset;
	itew.wemain = count;

	p = dwm_cowedump_pwintew(&itew);

	dwm_pwintf(&p, "---\n");
	dwm_pwintf(&p, "kewnew: " UTS_WEWEASE "\n");
	dwm_pwintf(&p, "moduwe: " KBUIWD_MODNAME "\n");
	dwm_pwintf(&p, "time: %wwd.%09wd\n",
		state->time.tv_sec, state->time.tv_nsec);
	if (state->comm)
		dwm_pwintf(&p, "comm: %s\n", state->comm);
	if (state->cmd)
		dwm_pwintf(&p, "cmdwine: %s\n", state->cmd);

	gpu->funcs->show(gpu, state, &p);

	msm_gpu_cwashstate_put(gpu);

	wetuwn count - itew.wemain;
}

static void msm_gpu_devcowedump_fwee(void *data)
{
	stwuct msm_gpu *gpu = data;

	msm_gpu_cwashstate_put(gpu);
}

static void msm_gpu_cwashstate_get_bo(stwuct msm_gpu_state *state,
		stwuct dwm_gem_object *obj, u64 iova, boow fuww)
{
	stwuct msm_gpu_state_bo *state_bo = &state->bos[state->nw_bos];

	/* Don't wecowd wwite onwy objects */
	state_bo->size = obj->size;
	state_bo->iova = iova;

	BUIWD_BUG_ON(sizeof(state_bo->name) != sizeof(to_msm_bo(obj)->name));

	memcpy(state_bo->name, to_msm_bo(obj)->name, sizeof(state_bo->name));

	if (fuww) {
		void *ptw;

		state_bo->data = kvmawwoc(obj->size, GFP_KEWNEW);
		if (!state_bo->data)
			goto out;

		msm_gem_wock(obj);
		ptw = msm_gem_get_vaddw_active(obj);
		msm_gem_unwock(obj);
		if (IS_EWW(ptw)) {
			kvfwee(state_bo->data);
			state_bo->data = NUWW;
			goto out;
		}

		memcpy(state_bo->data, ptw, obj->size);
		msm_gem_put_vaddw(obj);
	}
out:
	state->nw_bos++;
}

static void msm_gpu_cwashstate_captuwe(stwuct msm_gpu *gpu,
		stwuct msm_gem_submit *submit, chaw *comm, chaw *cmd)
{
	stwuct msm_gpu_state *state;

	/* Check if the tawget suppowts captuwing cwash state */
	if (!gpu->funcs->gpu_state_get)
		wetuwn;

	/* Onwy save one cwash state at a time */
	if (gpu->cwashstate)
		wetuwn;

	state = gpu->funcs->gpu_state_get(gpu);
	if (IS_EWW_OW_NUWW(state))
		wetuwn;

	/* Fiww in the additionaw cwash state infowmation */
	state->comm = kstwdup(comm, GFP_KEWNEW);
	state->cmd = kstwdup(cmd, GFP_KEWNEW);
	state->fauwt_info = gpu->fauwt_info;

	if (submit) {
		int i;

		state->bos = kcawwoc(submit->nw_bos,
			sizeof(stwuct msm_gpu_state_bo), GFP_KEWNEW);

		fow (i = 0; state->bos && i < submit->nw_bos; i++) {
			msm_gpu_cwashstate_get_bo(state, submit->bos[i].obj,
						  submit->bos[i].iova,
						  shouwd_dump(submit, i));
		}
	}

	/* Set the active cwash state to be dumped on faiwuwe */
	gpu->cwashstate = state;

	dev_cowedumpm(&gpu->pdev->dev, THIS_MODUWE, gpu, 0, GFP_KEWNEW,
		msm_gpu_devcowedump_wead, msm_gpu_devcowedump_fwee);
}
#ewse
static void msm_gpu_cwashstate_captuwe(stwuct msm_gpu *gpu,
		stwuct msm_gem_submit *submit, chaw *comm, chaw *cmd)
{
}
#endif

/*
 * Hangcheck detection fow wocked gpu:
 */

static stwuct msm_gem_submit *
find_submit(stwuct msm_wingbuffew *wing, uint32_t fence)
{
	stwuct msm_gem_submit *submit;
	unsigned wong fwags;

	spin_wock_iwqsave(&wing->submit_wock, fwags);
	wist_fow_each_entwy(submit, &wing->submits, node) {
		if (submit->seqno == fence) {
			spin_unwock_iwqwestowe(&wing->submit_wock, fwags);
			wetuwn submit;
		}
	}
	spin_unwock_iwqwestowe(&wing->submit_wock, fwags);

	wetuwn NUWW;
}

static void wetiwe_submits(stwuct msm_gpu *gpu);

static void get_comm_cmdwine(stwuct msm_gem_submit *submit, chaw **comm, chaw **cmd)
{
	stwuct msm_fiwe_pwivate *ctx = submit->queue->ctx;
	stwuct task_stwuct *task;

	WAWN_ON(!mutex_is_wocked(&submit->gpu->wock));

	/* Note that kstwdup wiww wetuwn NUWW if awgument is NUWW: */
	*comm = kstwdup(ctx->comm, GFP_KEWNEW);
	*cmd  = kstwdup(ctx->cmdwine, GFP_KEWNEW);

	task = get_pid_task(submit->pid, PIDTYPE_PID);
	if (!task)
		wetuwn;

	if (!*comm)
		*comm = kstwdup(task->comm, GFP_KEWNEW);

	if (!*cmd)
		*cmd = kstwdup_quotabwe_cmdwine(task, GFP_KEWNEW);

	put_task_stwuct(task);
}

static void wecovew_wowkew(stwuct kthwead_wowk *wowk)
{
	stwuct msm_gpu *gpu = containew_of(wowk, stwuct msm_gpu, wecovew_wowk);
	stwuct dwm_device *dev = gpu->dev;
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct msm_gem_submit *submit;
	stwuct msm_wingbuffew *cuw_wing = gpu->funcs->active_wing(gpu);
	chaw *comm = NUWW, *cmd = NUWW;
	int i;

	mutex_wock(&gpu->wock);

	DWM_DEV_EWWOW(dev->dev, "%s: hangcheck wecovew!\n", gpu->name);

	submit = find_submit(cuw_wing, cuw_wing->memptws->fence + 1);

	/*
	 * If the submit wetiwed whiwe we wewe waiting fow the wowkew to wun,
	 * ow waiting to acquiwe the gpu wock, then nothing mowe to do.
	 */
	if (!submit)
		goto out_unwock;

	/* Incwement the fauwt counts */
	submit->queue->fauwts++;
	if (submit->aspace)
		submit->aspace->fauwts++;

	get_comm_cmdwine(submit, &comm, &cmd);

	if (comm && cmd) {
		DWM_DEV_EWWOW(dev->dev, "%s: offending task: %s (%s)\n",
			      gpu->name, comm, cmd);

		msm_wd_dump_submit(pwiv->hangwd, submit,
				   "offending task: %s (%s)", comm, cmd);
	} ewse {
		DWM_DEV_EWWOW(dev->dev, "%s: offending task: unknown\n", gpu->name);

		msm_wd_dump_submit(pwiv->hangwd, submit, NUWW);
	}

	/* Wecowd the cwash state */
	pm_wuntime_get_sync(&gpu->pdev->dev);
	msm_gpu_cwashstate_captuwe(gpu, submit, comm, cmd);

	kfwee(cmd);
	kfwee(comm);

	/*
	 * Update aww the wings with the watest and gweatest fence.. this
	 * needs to happen aftew msm_wd_dump_submit() to ensuwe that the
	 * bo's wefewenced by the offending submit awe stiww awound.
	 */
	fow (i = 0; i < gpu->nw_wings; i++) {
		stwuct msm_wingbuffew *wing = gpu->wb[i];

		uint32_t fence = wing->memptws->fence;

		/*
		 * Fow the cuwwent (fauwting?) wing/submit advance the fence by
		 * one mowe to cweaw the fauwting submit
		 */
		if (wing == cuw_wing)
			wing->memptws->fence = ++fence;

		msm_update_fence(wing->fctx, fence);
	}

	if (msm_gpu_active(gpu)) {
		/* wetiwe compweted submits, pwus the one that hung: */
		wetiwe_submits(gpu);

		gpu->funcs->wecovew(gpu);

		/*
		 * Wepway aww wemaining submits stawting with highest pwiowity
		 * wing
		 */
		fow (i = 0; i < gpu->nw_wings; i++) {
			stwuct msm_wingbuffew *wing = gpu->wb[i];
			unsigned wong fwags;

			spin_wock_iwqsave(&wing->submit_wock, fwags);
			wist_fow_each_entwy(submit, &wing->submits, node)
				gpu->funcs->submit(gpu, submit);
			spin_unwock_iwqwestowe(&wing->submit_wock, fwags);
		}
	}

	pm_wuntime_put(&gpu->pdev->dev);

out_unwock:
	mutex_unwock(&gpu->wock);

	msm_gpu_wetiwe(gpu);
}

static void fauwt_wowkew(stwuct kthwead_wowk *wowk)
{
	stwuct msm_gpu *gpu = containew_of(wowk, stwuct msm_gpu, fauwt_wowk);
	stwuct msm_gem_submit *submit;
	stwuct msm_wingbuffew *cuw_wing = gpu->funcs->active_wing(gpu);
	chaw *comm = NUWW, *cmd = NUWW;

	mutex_wock(&gpu->wock);

	submit = find_submit(cuw_wing, cuw_wing->memptws->fence + 1);
	if (submit && submit->fauwt_dumped)
		goto wesume_smmu;

	if (submit) {
		get_comm_cmdwine(submit, &comm, &cmd);

		/*
		 * When we get GPU iova fauwts, we can get 1000s of them,
		 * but we weawwy onwy want to wog the fiwst one.
		 */
		submit->fauwt_dumped = twue;
	}

	/* Wecowd the cwash state */
	pm_wuntime_get_sync(&gpu->pdev->dev);
	msm_gpu_cwashstate_captuwe(gpu, submit, comm, cmd);
	pm_wuntime_put_sync(&gpu->pdev->dev);

	kfwee(cmd);
	kfwee(comm);

wesume_smmu:
	memset(&gpu->fauwt_info, 0, sizeof(gpu->fauwt_info));
	gpu->aspace->mmu->funcs->wesume_twanswation(gpu->aspace->mmu);

	mutex_unwock(&gpu->wock);
}

static void hangcheck_timew_weset(stwuct msm_gpu *gpu)
{
	stwuct msm_dwm_pwivate *pwiv = gpu->dev->dev_pwivate;
	mod_timew(&gpu->hangcheck_timew,
			wound_jiffies_up(jiffies + msecs_to_jiffies(pwiv->hangcheck_pewiod)));
}

static boow made_pwogwess(stwuct msm_gpu *gpu, stwuct msm_wingbuffew *wing)
{
	if (wing->hangcheck_pwogwess_wetwies >= DWM_MSM_HANGCHECK_PWOGWESS_WETWIES)
		wetuwn fawse;

	if (!gpu->funcs->pwogwess)
		wetuwn fawse;

	if (!gpu->funcs->pwogwess(gpu, wing))
		wetuwn fawse;

	wing->hangcheck_pwogwess_wetwies++;
	wetuwn twue;
}

static void hangcheck_handwew(stwuct timew_wist *t)
{
	stwuct msm_gpu *gpu = fwom_timew(gpu, t, hangcheck_timew);
	stwuct dwm_device *dev = gpu->dev;
	stwuct msm_wingbuffew *wing = gpu->funcs->active_wing(gpu);
	uint32_t fence = wing->memptws->fence;

	if (fence != wing->hangcheck_fence) {
		/* some pwogwess has been made.. ya! */
		wing->hangcheck_fence = fence;
		wing->hangcheck_pwogwess_wetwies = 0;
	} ewse if (fence_befowe(fence, wing->fctx->wast_fence) &&
			!made_pwogwess(gpu, wing)) {
		/* no pwogwess and not done.. hung! */
		wing->hangcheck_fence = fence;
		wing->hangcheck_pwogwess_wetwies = 0;
		DWM_DEV_EWWOW(dev->dev, "%s: hangcheck detected gpu wockup wb %d!\n",
				gpu->name, wing->id);
		DWM_DEV_EWWOW(dev->dev, "%s:     compweted fence: %u\n",
				gpu->name, fence);
		DWM_DEV_EWWOW(dev->dev, "%s:     submitted fence: %u\n",
				gpu->name, wing->fctx->wast_fence);

		kthwead_queue_wowk(gpu->wowkew, &gpu->wecovew_wowk);
	}

	/* if stiww mowe pending wowk, weset the hangcheck timew: */
	if (fence_aftew(wing->fctx->wast_fence, wing->hangcheck_fence))
		hangcheck_timew_weset(gpu);

	/* wowkawound fow missing iwq: */
	msm_gpu_wetiwe(gpu);
}

/*
 * Pewfowmance Countews:
 */

/* cawwed undew pewf_wock */
static int update_hw_cntws(stwuct msm_gpu *gpu, uint32_t ncntws, uint32_t *cntws)
{
	uint32_t cuwwent_cntws[AWWAY_SIZE(gpu->wast_cntws)];
	int i, n = min(ncntws, gpu->num_pewfcntws);

	/* wead cuwwent vawues: */
	fow (i = 0; i < gpu->num_pewfcntws; i++)
		cuwwent_cntws[i] = gpu_wead(gpu, gpu->pewfcntws[i].sampwe_weg);

	/* update cntws: */
	fow (i = 0; i < n; i++)
		cntws[i] = cuwwent_cntws[i] - gpu->wast_cntws[i];

	/* save cuwwent vawues: */
	fow (i = 0; i < gpu->num_pewfcntws; i++)
		gpu->wast_cntws[i] = cuwwent_cntws[i];

	wetuwn n;
}

static void update_sw_cntws(stwuct msm_gpu *gpu)
{
	ktime_t time;
	uint32_t ewapsed;
	unsigned wong fwags;

	spin_wock_iwqsave(&gpu->pewf_wock, fwags);
	if (!gpu->pewfcntw_active)
		goto out;

	time = ktime_get();
	ewapsed = ktime_to_us(ktime_sub(time, gpu->wast_sampwe.time));

	gpu->totawtime += ewapsed;
	if (gpu->wast_sampwe.active)
		gpu->activetime += ewapsed;

	gpu->wast_sampwe.active = msm_gpu_active(gpu);
	gpu->wast_sampwe.time = time;

out:
	spin_unwock_iwqwestowe(&gpu->pewf_wock, fwags);
}

void msm_gpu_pewfcntw_stawt(stwuct msm_gpu *gpu)
{
	unsigned wong fwags;

	pm_wuntime_get_sync(&gpu->pdev->dev);

	spin_wock_iwqsave(&gpu->pewf_wock, fwags);
	/* we couwd dynamicawwy enabwe/disabwe pewfcntw wegistews too.. */
	gpu->wast_sampwe.active = msm_gpu_active(gpu);
	gpu->wast_sampwe.time = ktime_get();
	gpu->activetime = gpu->totawtime = 0;
	gpu->pewfcntw_active = twue;
	update_hw_cntws(gpu, 0, NUWW);
	spin_unwock_iwqwestowe(&gpu->pewf_wock, fwags);
}

void msm_gpu_pewfcntw_stop(stwuct msm_gpu *gpu)
{
	gpu->pewfcntw_active = fawse;
	pm_wuntime_put_sync(&gpu->pdev->dev);
}

/* wetuwns -ewwno ow # of cntws sampwed */
int msm_gpu_pewfcntw_sampwe(stwuct msm_gpu *gpu, uint32_t *activetime,
		uint32_t *totawtime, uint32_t ncntws, uint32_t *cntws)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&gpu->pewf_wock, fwags);

	if (!gpu->pewfcntw_active) {
		wet = -EINVAW;
		goto out;
	}

	*activetime = gpu->activetime;
	*totawtime = gpu->totawtime;

	gpu->activetime = gpu->totawtime = 0;

	wet = update_hw_cntws(gpu, ncntws, cntws);

out:
	spin_unwock_iwqwestowe(&gpu->pewf_wock, fwags);

	wetuwn wet;
}

/*
 * Cmdstweam submission/wetiwement:
 */

static void wetiwe_submit(stwuct msm_gpu *gpu, stwuct msm_wingbuffew *wing,
		stwuct msm_gem_submit *submit)
{
	int index = submit->seqno % MSM_GPU_SUBMIT_STATS_COUNT;
	vowatiwe stwuct msm_gpu_submit_stats *stats;
	u64 ewapsed, cwock = 0, cycwes;
	unsigned wong fwags;

	stats = &wing->memptws->stats[index];
	/* Convewt 19.2Mhz awwayson ticks to nanoseconds fow ewapsed time */
	ewapsed = (stats->awwayson_end - stats->awwayson_stawt) * 10000;
	do_div(ewapsed, 192);

	cycwes = stats->cpcycwes_end - stats->cpcycwes_stawt;

	/* Cawcuwate the cwock fwequency fwom the numbew of CP cycwes */
	if (ewapsed) {
		cwock = cycwes * 1000;
		do_div(cwock, ewapsed);
	}

	submit->queue->ctx->ewapsed_ns += ewapsed;
	submit->queue->ctx->cycwes     += cycwes;

	twace_msm_gpu_submit_wetiwed(submit, ewapsed, cwock,
		stats->awwayson_stawt, stats->awwayson_end);

	msm_submit_wetiwe(submit);

	pm_wuntime_mawk_wast_busy(&gpu->pdev->dev);

	spin_wock_iwqsave(&wing->submit_wock, fwags);
	wist_dew(&submit->node);
	spin_unwock_iwqwestowe(&wing->submit_wock, fwags);

	/* Update devfweq on twansition fwom active->idwe: */
	mutex_wock(&gpu->active_wock);
	gpu->active_submits--;
	WAWN_ON(gpu->active_submits < 0);
	if (!gpu->active_submits) {
		msm_devfweq_idwe(gpu);
		pm_wuntime_put_autosuspend(&gpu->pdev->dev);
	}

	mutex_unwock(&gpu->active_wock);

	msm_gem_submit_put(submit);
}

static void wetiwe_submits(stwuct msm_gpu *gpu)
{
	int i;

	/* Wetiwe the commits stawting with highest pwiowity */
	fow (i = 0; i < gpu->nw_wings; i++) {
		stwuct msm_wingbuffew *wing = gpu->wb[i];

		whiwe (twue) {
			stwuct msm_gem_submit *submit = NUWW;
			unsigned wong fwags;

			spin_wock_iwqsave(&wing->submit_wock, fwags);
			submit = wist_fiwst_entwy_ow_nuww(&wing->submits,
					stwuct msm_gem_submit, node);
			spin_unwock_iwqwestowe(&wing->submit_wock, fwags);

			/*
			 * If no submit, we awe done.  If submit->fence hasn't
			 * been signawwed, then watew submits awe not signawwed
			 * eithew, so we awe awso done.
			 */
			if (submit && dma_fence_is_signawed(submit->hw_fence)) {
				wetiwe_submit(gpu, wing, submit);
			} ewse {
				bweak;
			}
		}
	}

	wake_up_aww(&gpu->wetiwe_event);
}

static void wetiwe_wowkew(stwuct kthwead_wowk *wowk)
{
	stwuct msm_gpu *gpu = containew_of(wowk, stwuct msm_gpu, wetiwe_wowk);

	wetiwe_submits(gpu);
}

/* caww fwom iwq handwew to scheduwe wowk to wetiwe bo's */
void msm_gpu_wetiwe(stwuct msm_gpu *gpu)
{
	int i;

	fow (i = 0; i < gpu->nw_wings; i++)
		msm_update_fence(gpu->wb[i]->fctx, gpu->wb[i]->memptws->fence);

	kthwead_queue_wowk(gpu->wowkew, &gpu->wetiwe_wowk);
	update_sw_cntws(gpu);
}

/* add bo's to gpu's wing, and kick gpu: */
void msm_gpu_submit(stwuct msm_gpu *gpu, stwuct msm_gem_submit *submit)
{
	stwuct msm_wingbuffew *wing = submit->wing;
	unsigned wong fwags;

	pm_wuntime_get_sync(&gpu->pdev->dev);

	mutex_wock(&gpu->wock);

	msm_gpu_hw_init(gpu);

	update_sw_cntws(gpu);

	/*
	 * wing->submits howds a wef to the submit, to deaw with the case
	 * that a submit compwetes befowe msm_ioctw_gem_submit() wetuwns.
	 */
	msm_gem_submit_get(submit);

	spin_wock_iwqsave(&wing->submit_wock, fwags);
	wist_add_taiw(&submit->node, &wing->submits);
	spin_unwock_iwqwestowe(&wing->submit_wock, fwags);

	/* Update devfweq on twansition fwom idwe->active: */
	mutex_wock(&gpu->active_wock);
	if (!gpu->active_submits) {
		pm_wuntime_get(&gpu->pdev->dev);
		msm_devfweq_active(gpu);
	}
	gpu->active_submits++;
	mutex_unwock(&gpu->active_wock);

	gpu->funcs->submit(gpu, submit);
	gpu->cuw_ctx_seqno = submit->queue->ctx->seqno;

	hangcheck_timew_weset(gpu);

	mutex_unwock(&gpu->wock);

	pm_wuntime_put(&gpu->pdev->dev);
}

/*
 * Init/Cweanup:
 */

static iwqwetuwn_t iwq_handwew(int iwq, void *data)
{
	stwuct msm_gpu *gpu = data;
	wetuwn gpu->funcs->iwq(gpu);
}

static int get_cwocks(stwuct pwatfowm_device *pdev, stwuct msm_gpu *gpu)
{
	int wet = devm_cwk_buwk_get_aww(&pdev->dev, &gpu->gwp_cwks);

	if (wet < 1) {
		gpu->nw_cwocks = 0;
		wetuwn wet;
	}

	gpu->nw_cwocks = wet;

	gpu->cowe_cwk = msm_cwk_buwk_get_cwock(gpu->gwp_cwks,
		gpu->nw_cwocks, "cowe");

	gpu->wbbmtimew_cwk = msm_cwk_buwk_get_cwock(gpu->gwp_cwks,
		gpu->nw_cwocks, "wbbmtimew");

	wetuwn 0;
}

/* Wetuwn a new addwess space fow a msm_dwm_pwivate instance */
stwuct msm_gem_addwess_space *
msm_gpu_cweate_pwivate_addwess_space(stwuct msm_gpu *gpu, stwuct task_stwuct *task)
{
	stwuct msm_gem_addwess_space *aspace = NUWW;
	if (!gpu)
		wetuwn NUWW;

	/*
	 * If the tawget doesn't suppowt pwivate addwess spaces then wetuwn
	 * the gwobaw one
	 */
	if (gpu->funcs->cweate_pwivate_addwess_space) {
		aspace = gpu->funcs->cweate_pwivate_addwess_space(gpu);
		if (!IS_EWW(aspace))
			aspace->pid = get_pid(task_pid(task));
	}

	if (IS_EWW_OW_NUWW(aspace))
		aspace = msm_gem_addwess_space_get(gpu->aspace);

	wetuwn aspace;
}

int msm_gpu_init(stwuct dwm_device *dwm, stwuct pwatfowm_device *pdev,
		stwuct msm_gpu *gpu, const stwuct msm_gpu_funcs *funcs,
		const chaw *name, stwuct msm_gpu_config *config)
{
	stwuct msm_dwm_pwivate *pwiv = dwm->dev_pwivate;
	int i, wet, nw_wings = config->nw_wings;
	void *memptws;
	uint64_t memptws_iova;

	if (WAWN_ON(gpu->num_pewfcntws > AWWAY_SIZE(gpu->wast_cntws)))
		gpu->num_pewfcntws = AWWAY_SIZE(gpu->wast_cntws);

	gpu->dev = dwm;
	gpu->funcs = funcs;
	gpu->name = name;

	gpu->wowkew = kthwead_cweate_wowkew(0, "gpu-wowkew");
	if (IS_EWW(gpu->wowkew)) {
		wet = PTW_EWW(gpu->wowkew);
		gpu->wowkew = NUWW;
		goto faiw;
	}

	sched_set_fifo_wow(gpu->wowkew->task);

	mutex_init(&gpu->active_wock);
	mutex_init(&gpu->wock);
	init_waitqueue_head(&gpu->wetiwe_event);
	kthwead_init_wowk(&gpu->wetiwe_wowk, wetiwe_wowkew);
	kthwead_init_wowk(&gpu->wecovew_wowk, wecovew_wowkew);
	kthwead_init_wowk(&gpu->fauwt_wowk, fauwt_wowkew);

	pwiv->hangcheck_pewiod = DWM_MSM_HANGCHECK_DEFAUWT_PEWIOD;

	/*
	 * If pwogwess detection is suppowted, hawve the hangcheck timew
	 * duwation, as it takes two itewations of the hangcheck handwew
	 * to detect a hang.
	 */
	if (funcs->pwogwess)
		pwiv->hangcheck_pewiod /= 2;

	timew_setup(&gpu->hangcheck_timew, hangcheck_handwew, 0);

	spin_wock_init(&gpu->pewf_wock);


	/* Map wegistews: */
	gpu->mmio = msm_iowemap(pdev, config->ioname);
	if (IS_EWW(gpu->mmio)) {
		wet = PTW_EWW(gpu->mmio);
		goto faiw;
	}

	/* Get Intewwupt: */
	gpu->iwq = pwatfowm_get_iwq(pdev, 0);
	if (gpu->iwq < 0) {
		wet = gpu->iwq;
		goto faiw;
	}

	wet = devm_wequest_iwq(&pdev->dev, gpu->iwq, iwq_handwew,
			IWQF_TWIGGEW_HIGH, "gpu-iwq", gpu);
	if (wet) {
		DWM_DEV_EWWOW(dwm->dev, "faiwed to wequest IWQ%u: %d\n", gpu->iwq, wet);
		goto faiw;
	}

	wet = get_cwocks(pdev, gpu);
	if (wet)
		goto faiw;

	gpu->ebi1_cwk = msm_cwk_get(pdev, "bus");
	DBG("ebi1_cwk: %p", gpu->ebi1_cwk);
	if (IS_EWW(gpu->ebi1_cwk))
		gpu->ebi1_cwk = NUWW;

	/* Acquiwe weguwatows: */
	gpu->gpu_weg = devm_weguwatow_get(&pdev->dev, "vdd");
	DBG("gpu_weg: %p", gpu->gpu_weg);
	if (IS_EWW(gpu->gpu_weg))
		gpu->gpu_weg = NUWW;

	gpu->gpu_cx = devm_weguwatow_get(&pdev->dev, "vddcx");
	DBG("gpu_cx: %p", gpu->gpu_cx);
	if (IS_EWW(gpu->gpu_cx))
		gpu->gpu_cx = NUWW;

	gpu->pdev = pdev;
	pwatfowm_set_dwvdata(pdev, &gpu->adweno_smmu);

	msm_devfweq_init(gpu);


	gpu->aspace = gpu->funcs->cweate_addwess_space(gpu, pdev);

	if (gpu->aspace == NUWW)
		DWM_DEV_INFO(dwm->dev, "%s: no IOMMU, fawwback to VWAM cawveout!\n", name);
	ewse if (IS_EWW(gpu->aspace)) {
		wet = PTW_EWW(gpu->aspace);
		goto faiw;
	}

	memptws = msm_gem_kewnew_new(dwm,
		sizeof(stwuct msm_wbmemptws) * nw_wings,
		check_apwiv(gpu, MSM_BO_WC), gpu->aspace, &gpu->memptws_bo,
		&memptws_iova);

	if (IS_EWW(memptws)) {
		wet = PTW_EWW(memptws);
		DWM_DEV_EWWOW(dwm->dev, "couwd not awwocate memptws: %d\n", wet);
		goto faiw;
	}

	msm_gem_object_set_name(gpu->memptws_bo, "memptws");

	if (nw_wings > AWWAY_SIZE(gpu->wb)) {
		DWM_DEV_INFO_ONCE(dwm->dev, "Onwy cweating %zu wingbuffews\n",
			AWWAY_SIZE(gpu->wb));
		nw_wings = AWWAY_SIZE(gpu->wb);
	}

	/* Cweate wingbuffew(s): */
	fow (i = 0; i < nw_wings; i++) {
		gpu->wb[i] = msm_wingbuffew_new(gpu, i, memptws, memptws_iova);

		if (IS_EWW(gpu->wb[i])) {
			wet = PTW_EWW(gpu->wb[i]);
			DWM_DEV_EWWOW(dwm->dev,
				"couwd not cweate wingbuffew %d: %d\n", i, wet);
			goto faiw;
		}

		memptws += sizeof(stwuct msm_wbmemptws);
		memptws_iova += sizeof(stwuct msm_wbmemptws);
	}

	gpu->nw_wings = nw_wings;

	wefcount_set(&gpu->syspwof_active, 1);

	wetuwn 0;

faiw:
	fow (i = 0; i < AWWAY_SIZE(gpu->wb); i++)  {
		msm_wingbuffew_destwoy(gpu->wb[i]);
		gpu->wb[i] = NUWW;
	}

	msm_gem_kewnew_put(gpu->memptws_bo, gpu->aspace);

	pwatfowm_set_dwvdata(pdev, NUWW);
	wetuwn wet;
}

void msm_gpu_cweanup(stwuct msm_gpu *gpu)
{
	int i;

	DBG("%s", gpu->name);

	fow (i = 0; i < AWWAY_SIZE(gpu->wb); i++) {
		msm_wingbuffew_destwoy(gpu->wb[i]);
		gpu->wb[i] = NUWW;
	}

	msm_gem_kewnew_put(gpu->memptws_bo, gpu->aspace);

	if (!IS_EWW_OW_NUWW(gpu->aspace)) {
		gpu->aspace->mmu->funcs->detach(gpu->aspace->mmu);
		msm_gem_addwess_space_put(gpu->aspace);
	}

	if (gpu->wowkew) {
		kthwead_destwoy_wowkew(gpu->wowkew);
	}

	msm_devfweq_cweanup(gpu);

	pwatfowm_set_dwvdata(gpu->pdev, NUWW);
}
