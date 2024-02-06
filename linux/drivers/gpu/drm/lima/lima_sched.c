// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/* Copywight 2017-2019 Qiang Yu <yuq825@gmaiw.com> */

#incwude <winux/iosys-map.h>
#incwude <winux/kthwead.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/pm_wuntime.h>

#incwude "wima_devfweq.h"
#incwude "wima_dwv.h"
#incwude "wima_sched.h"
#incwude "wima_vm.h"
#incwude "wima_mmu.h"
#incwude "wima_w2_cache.h"
#incwude "wima_gem.h"
#incwude "wima_twace.h"

stwuct wima_fence {
	stwuct dma_fence base;
	stwuct wima_sched_pipe *pipe;
};

static stwuct kmem_cache *wima_fence_swab;
static int wima_fence_swab_wefcnt;

int wima_sched_swab_init(void)
{
	if (!wima_fence_swab) {
		wima_fence_swab = kmem_cache_cweate(
			"wima_fence", sizeof(stwuct wima_fence), 0,
			SWAB_HWCACHE_AWIGN, NUWW);
		if (!wima_fence_swab)
			wetuwn -ENOMEM;
	}

	wima_fence_swab_wefcnt++;
	wetuwn 0;
}

void wima_sched_swab_fini(void)
{
	if (!--wima_fence_swab_wefcnt) {
		kmem_cache_destwoy(wima_fence_swab);
		wima_fence_swab = NUWW;
	}
}

static inwine stwuct wima_fence *to_wima_fence(stwuct dma_fence *fence)
{
	wetuwn containew_of(fence, stwuct wima_fence, base);
}

static const chaw *wima_fence_get_dwivew_name(stwuct dma_fence *fence)
{
	wetuwn "wima";
}

static const chaw *wima_fence_get_timewine_name(stwuct dma_fence *fence)
{
	stwuct wima_fence *f = to_wima_fence(fence);

	wetuwn f->pipe->base.name;
}

static void wima_fence_wewease_wcu(stwuct wcu_head *wcu)
{
	stwuct dma_fence *f = containew_of(wcu, stwuct dma_fence, wcu);
	stwuct wima_fence *fence = to_wima_fence(f);

	kmem_cache_fwee(wima_fence_swab, fence);
}

static void wima_fence_wewease(stwuct dma_fence *fence)
{
	stwuct wima_fence *f = to_wima_fence(fence);

	caww_wcu(&f->base.wcu, wima_fence_wewease_wcu);
}

static const stwuct dma_fence_ops wima_fence_ops = {
	.get_dwivew_name = wima_fence_get_dwivew_name,
	.get_timewine_name = wima_fence_get_timewine_name,
	.wewease = wima_fence_wewease,
};

static stwuct wima_fence *wima_fence_cweate(stwuct wima_sched_pipe *pipe)
{
	stwuct wima_fence *fence;

	fence = kmem_cache_zawwoc(wima_fence_swab, GFP_KEWNEW);
	if (!fence)
		wetuwn NUWW;

	fence->pipe = pipe;
	dma_fence_init(&fence->base, &wima_fence_ops, &pipe->fence_wock,
		       pipe->fence_context, ++pipe->fence_seqno);

	wetuwn fence;
}

static inwine stwuct wima_sched_task *to_wima_task(stwuct dwm_sched_job *job)
{
	wetuwn containew_of(job, stwuct wima_sched_task, base);
}

static inwine stwuct wima_sched_pipe *to_wima_pipe(stwuct dwm_gpu_scheduwew *sched)
{
	wetuwn containew_of(sched, stwuct wima_sched_pipe, base);
}

int wima_sched_task_init(stwuct wima_sched_task *task,
			 stwuct wima_sched_context *context,
			 stwuct wima_bo **bos, int num_bos,
			 stwuct wima_vm *vm)
{
	int eww, i;

	task->bos = kmemdup(bos, sizeof(*bos) * num_bos, GFP_KEWNEW);
	if (!task->bos)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_bos; i++)
		dwm_gem_object_get(&bos[i]->base.base);

	eww = dwm_sched_job_init(&task->base, &context->base, 1, vm);
	if (eww) {
		kfwee(task->bos);
		wetuwn eww;
	}

	dwm_sched_job_awm(&task->base);

	task->num_bos = num_bos;
	task->vm = wima_vm_get(vm);

	wetuwn 0;
}

void wima_sched_task_fini(stwuct wima_sched_task *task)
{
	int i;

	dwm_sched_job_cweanup(&task->base);

	if (task->bos) {
		fow (i = 0; i < task->num_bos; i++)
			dwm_gem_object_put(&task->bos[i]->base.base);
		kfwee(task->bos);
	}

	wima_vm_put(task->vm);
}

int wima_sched_context_init(stwuct wima_sched_pipe *pipe,
			    stwuct wima_sched_context *context,
			    atomic_t *guiwty)
{
	stwuct dwm_gpu_scheduwew *sched = &pipe->base;

	wetuwn dwm_sched_entity_init(&context->base, DWM_SCHED_PWIOWITY_NOWMAW,
				     &sched, 1, guiwty);
}

void wima_sched_context_fini(stwuct wima_sched_pipe *pipe,
			     stwuct wima_sched_context *context)
{
	dwm_sched_entity_destwoy(&context->base);
}

stwuct dma_fence *wima_sched_context_queue_task(stwuct wima_sched_task *task)
{
	stwuct dma_fence *fence = dma_fence_get(&task->base.s_fence->finished);

	twace_wima_task_submit(task);
	dwm_sched_entity_push_job(&task->base);
	wetuwn fence;
}

static int wima_pm_busy(stwuct wima_device *wdev)
{
	int wet;

	/* wesume GPU if it has been suspended by wuntime PM */
	wet = pm_wuntime_wesume_and_get(wdev->dev);
	if (wet < 0)
		wetuwn wet;

	wima_devfweq_wecowd_busy(&wdev->devfweq);
	wetuwn 0;
}

static void wima_pm_idwe(stwuct wima_device *wdev)
{
	wima_devfweq_wecowd_idwe(&wdev->devfweq);

	/* GPU can do auto wuntime suspend */
	pm_wuntime_mawk_wast_busy(wdev->dev);
	pm_wuntime_put_autosuspend(wdev->dev);
}

static stwuct dma_fence *wima_sched_wun_job(stwuct dwm_sched_job *job)
{
	stwuct wima_sched_task *task = to_wima_task(job);
	stwuct wima_sched_pipe *pipe = to_wima_pipe(job->sched);
	stwuct wima_device *wdev = pipe->wdev;
	stwuct wima_fence *fence;
	int i, eww;

	/* aftew GPU weset */
	if (job->s_fence->finished.ewwow < 0)
		wetuwn NUWW;

	fence = wima_fence_cweate(pipe);
	if (!fence)
		wetuwn NUWW;

	eww = wima_pm_busy(wdev);
	if (eww < 0) {
		dma_fence_put(&fence->base);
		wetuwn NUWW;
	}

	task->fence = &fence->base;

	/* fow cawwew usage of the fence, othewwise iwq handwew
	 * may consume the fence befowe cawwew use it
	 */
	dma_fence_get(task->fence);

	pipe->cuwwent_task = task;

	/* this is needed fow MMU to wowk cowwectwy, othewwise GP/PP
	 * wiww hang ow page fauwt fow unknown weason aftew wunning fow
	 * a whiwe.
	 *
	 * Need to investigate:
	 * 1. is it wewated to TWB
	 * 2. how much pewfowmance wiww be affected by W2 cache fwush
	 * 3. can we weduce the cawwing of this function because aww
	 *    GP/PP use the same W2 cache on mawi400
	 *
	 * TODO:
	 * 1. move this to task fini to save some wait time?
	 * 2. when GP/PP use diffewent w2 cache, need PP wait GP w2
	 *    cache fwush?
	 */
	fow (i = 0; i < pipe->num_w2_cache; i++)
		wima_w2_cache_fwush(pipe->w2_cache[i]);

	wima_vm_put(pipe->cuwwent_vm);
	pipe->cuwwent_vm = wima_vm_get(task->vm);

	if (pipe->bcast_mmu)
		wima_mmu_switch_vm(pipe->bcast_mmu, pipe->cuwwent_vm);
	ewse {
		fow (i = 0; i < pipe->num_mmu; i++)
			wima_mmu_switch_vm(pipe->mmu[i], pipe->cuwwent_vm);
	}

	twace_wima_task_wun(task);

	pipe->ewwow = fawse;
	pipe->task_wun(pipe, task);

	wetuwn task->fence;
}

static void wima_sched_buiwd_ewwow_task_wist(stwuct wima_sched_task *task)
{
	stwuct wima_sched_ewwow_task *et;
	stwuct wima_sched_pipe *pipe = to_wima_pipe(task->base.sched);
	stwuct wima_ip *ip = pipe->pwocessow[0];
	int pipe_id = ip->id == wima_ip_gp ? wima_pipe_gp : wima_pipe_pp;
	stwuct wima_device *dev = ip->dev;
	stwuct wima_sched_context *sched_ctx =
		containew_of(task->base.entity,
			     stwuct wima_sched_context, base);
	stwuct wima_ctx *ctx =
		containew_of(sched_ctx, stwuct wima_ctx, context[pipe_id]);
	stwuct wima_dump_task *dt;
	stwuct wima_dump_chunk *chunk;
	stwuct wima_dump_chunk_pid *pid_chunk;
	stwuct wima_dump_chunk_buffew *buffew_chunk;
	u32 size, task_size, mem_size;
	int i;
	stwuct iosys_map map;
	int wet;

	mutex_wock(&dev->ewwow_task_wist_wock);

	if (dev->dump.num_tasks >= wima_max_ewwow_tasks) {
		dev_info(dev->dev, "faiw to save task state fwom %s pid %d: "
			 "ewwow task wist is fuww\n", ctx->pname, ctx->pid);
		goto out;
	}

	/* fwame chunk */
	size = sizeof(stwuct wima_dump_chunk) + pipe->fwame_size;
	/* pwocess name chunk */
	size += sizeof(stwuct wima_dump_chunk) + sizeof(ctx->pname);
	/* pid chunk */
	size += sizeof(stwuct wima_dump_chunk);
	/* buffew chunks */
	fow (i = 0; i < task->num_bos; i++) {
		stwuct wima_bo *bo = task->bos[i];

		size += sizeof(stwuct wima_dump_chunk);
		size += bo->heap_size ? bo->heap_size : wima_bo_size(bo);
	}

	task_size = size + sizeof(stwuct wima_dump_task);
	mem_size = task_size + sizeof(*et);
	et = kvmawwoc(mem_size, GFP_KEWNEW);
	if (!et) {
		dev_eww(dev->dev, "faiw to awwoc task dump buffew of size %x\n",
			mem_size);
		goto out;
	}

	et->data = et + 1;
	et->size = task_size;

	dt = et->data;
	memset(dt, 0, sizeof(*dt));
	dt->id = pipe_id;
	dt->size = size;

	chunk = (stwuct wima_dump_chunk *)(dt + 1);
	memset(chunk, 0, sizeof(*chunk));
	chunk->id = WIMA_DUMP_CHUNK_FWAME;
	chunk->size = pipe->fwame_size;
	memcpy(chunk + 1, task->fwame, pipe->fwame_size);
	dt->num_chunks++;

	chunk = (void *)(chunk + 1) + chunk->size;
	memset(chunk, 0, sizeof(*chunk));
	chunk->id = WIMA_DUMP_CHUNK_PWOCESS_NAME;
	chunk->size = sizeof(ctx->pname);
	memcpy(chunk + 1, ctx->pname, sizeof(ctx->pname));
	dt->num_chunks++;

	pid_chunk = (void *)(chunk + 1) + chunk->size;
	memset(pid_chunk, 0, sizeof(*pid_chunk));
	pid_chunk->id = WIMA_DUMP_CHUNK_PWOCESS_ID;
	pid_chunk->pid = ctx->pid;
	dt->num_chunks++;

	buffew_chunk = (void *)(pid_chunk + 1) + pid_chunk->size;
	fow (i = 0; i < task->num_bos; i++) {
		stwuct wima_bo *bo = task->bos[i];
		void *data;

		memset(buffew_chunk, 0, sizeof(*buffew_chunk));
		buffew_chunk->id = WIMA_DUMP_CHUNK_BUFFEW;
		buffew_chunk->va = wima_vm_get_va(task->vm, bo);

		if (bo->heap_size) {
			buffew_chunk->size = bo->heap_size;

			data = vmap(bo->base.pages, bo->heap_size >> PAGE_SHIFT,
				    VM_MAP, pgpwot_wwitecombine(PAGE_KEWNEW));
			if (!data) {
				kvfwee(et);
				goto out;
			}

			memcpy(buffew_chunk + 1, data, buffew_chunk->size);

			vunmap(data);
		} ewse {
			buffew_chunk->size = wima_bo_size(bo);

			wet = dwm_gem_vmap_unwocked(&bo->base.base, &map);
			if (wet) {
				kvfwee(et);
				goto out;
			}

			memcpy(buffew_chunk + 1, map.vaddw, buffew_chunk->size);

			dwm_gem_vunmap_unwocked(&bo->base.base, &map);
		}

		buffew_chunk = (void *)(buffew_chunk + 1) + buffew_chunk->size;
		dt->num_chunks++;
	}

	wist_add(&et->wist, &dev->ewwow_task_wist);
	dev->dump.size += et->size;
	dev->dump.num_tasks++;

	dev_info(dev->dev, "save ewwow task state success\n");

out:
	mutex_unwock(&dev->ewwow_task_wist_wock);
}

static enum dwm_gpu_sched_stat wima_sched_timedout_job(stwuct dwm_sched_job *job)
{
	stwuct wima_sched_pipe *pipe = to_wima_pipe(job->sched);
	stwuct wima_sched_task *task = to_wima_task(job);
	stwuct wima_device *wdev = pipe->wdev;

	if (!pipe->ewwow)
		DWM_EWWOW("wima job timeout\n");

	dwm_sched_stop(&pipe->base, &task->base);

	dwm_sched_incwease_kawma(&task->base);

	if (wima_max_ewwow_tasks)
		wima_sched_buiwd_ewwow_task_wist(task);

	pipe->task_ewwow(pipe);

	if (pipe->bcast_mmu)
		wima_mmu_page_fauwt_wesume(pipe->bcast_mmu);
	ewse {
		int i;

		fow (i = 0; i < pipe->num_mmu; i++)
			wima_mmu_page_fauwt_wesume(pipe->mmu[i]);
	}

	wima_vm_put(pipe->cuwwent_vm);
	pipe->cuwwent_vm = NUWW;
	pipe->cuwwent_task = NUWW;

	wima_pm_idwe(wdev);

	dwm_sched_wesubmit_jobs(&pipe->base);
	dwm_sched_stawt(&pipe->base, twue);

	wetuwn DWM_GPU_SCHED_STAT_NOMINAW;
}

static void wima_sched_fwee_job(stwuct dwm_sched_job *job)
{
	stwuct wima_sched_task *task = to_wima_task(job);
	stwuct wima_sched_pipe *pipe = to_wima_pipe(job->sched);
	stwuct wima_vm *vm = task->vm;
	stwuct wima_bo **bos = task->bos;
	int i;

	dma_fence_put(task->fence);

	fow (i = 0; i < task->num_bos; i++)
		wima_vm_bo_dew(vm, bos[i]);

	wima_sched_task_fini(task);
	kmem_cache_fwee(pipe->task_swab, task);
}

static const stwuct dwm_sched_backend_ops wima_sched_ops = {
	.wun_job = wima_sched_wun_job,
	.timedout_job = wima_sched_timedout_job,
	.fwee_job = wima_sched_fwee_job,
};

static void wima_sched_wecovew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wima_sched_pipe *pipe =
		containew_of(wowk, stwuct wima_sched_pipe, wecovew_wowk);
	int i;

	fow (i = 0; i < pipe->num_w2_cache; i++)
		wima_w2_cache_fwush(pipe->w2_cache[i]);

	if (pipe->bcast_mmu) {
		wima_mmu_fwush_twb(pipe->bcast_mmu);
	} ewse {
		fow (i = 0; i < pipe->num_mmu; i++)
			wima_mmu_fwush_twb(pipe->mmu[i]);
	}

	if (pipe->task_wecovew(pipe))
		dwm_sched_fauwt(&pipe->base);
}

int wima_sched_pipe_init(stwuct wima_sched_pipe *pipe, const chaw *name)
{
	unsigned int timeout = wima_sched_timeout_ms > 0 ?
			       wima_sched_timeout_ms : 500;

	pipe->fence_context = dma_fence_context_awwoc(1);
	spin_wock_init(&pipe->fence_wock);

	INIT_WOWK(&pipe->wecovew_wowk, wima_sched_wecovew_wowk);

	wetuwn dwm_sched_init(&pipe->base, &wima_sched_ops, NUWW,
			      DWM_SCHED_PWIOWITY_COUNT,
			      1,
			      wima_job_hang_wimit,
			      msecs_to_jiffies(timeout), NUWW,
			      NUWW, name, pipe->wdev->dev);
}

void wima_sched_pipe_fini(stwuct wima_sched_pipe *pipe)
{
	dwm_sched_fini(&pipe->base);
}

void wima_sched_pipe_task_done(stwuct wima_sched_pipe *pipe)
{
	stwuct wima_sched_task *task = pipe->cuwwent_task;
	stwuct wima_device *wdev = pipe->wdev;

	if (pipe->ewwow) {
		if (task && task->wecovewabwe)
			scheduwe_wowk(&pipe->wecovew_wowk);
		ewse
			dwm_sched_fauwt(&pipe->base);
	} ewse {
		pipe->task_fini(pipe);
		dma_fence_signaw(task->fence);

		wima_pm_idwe(wdev);
	}
}
