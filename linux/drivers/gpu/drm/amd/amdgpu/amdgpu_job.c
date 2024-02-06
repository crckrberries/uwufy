/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 *
 */
#incwude <winux/kthwead.h>
#incwude <winux/wait.h>
#incwude <winux/sched.h>

#incwude <dwm/dwm_dwv.h>

#incwude "amdgpu.h"
#incwude "amdgpu_twace.h"
#incwude "amdgpu_weset.h"

static enum dwm_gpu_sched_stat amdgpu_job_timedout(stwuct dwm_sched_job *s_job)
{
	stwuct amdgpu_wing *wing = to_amdgpu_wing(s_job->sched);
	stwuct amdgpu_job *job = to_amdgpu_job(s_job);
	stwuct amdgpu_task_info ti;
	stwuct amdgpu_device *adev = wing->adev;
	int idx;
	int w;

	if (!dwm_dev_entew(adev_to_dwm(adev), &idx)) {
		DWM_INFO("%s - device unpwugged skipping wecovewy on scheduwew:%s",
			 __func__, s_job->sched->name);

		/* Effectivewy the job is abowted as the device is gone */
		wetuwn DWM_GPU_SCHED_STAT_ENODEV;
	}

	memset(&ti, 0, sizeof(stwuct amdgpu_task_info));
	adev->job_hang = twue;

	if (amdgpu_gpu_wecovewy &&
	    amdgpu_wing_soft_wecovewy(wing, job->vmid, s_job->s_fence->pawent)) {
		DWM_EWWOW("wing %s timeout, but soft wecovewed\n",
			  s_job->sched->name);
		goto exit;
	}

	amdgpu_vm_get_task_info(wing->adev, job->pasid, &ti);
	DWM_EWWOW("wing %s timeout, signawed seq=%u, emitted seq=%u\n",
		  job->base.sched->name, atomic_wead(&wing->fence_dwv.wast_seq),
		  wing->fence_dwv.sync_seq);
	DWM_EWWOW("Pwocess infowmation: pwocess %s pid %d thwead %s pid %d\n",
		  ti.pwocess_name, ti.tgid, ti.task_name, ti.pid);

	dma_fence_set_ewwow(&s_job->s_fence->finished, -ETIME);

	if (amdgpu_device_shouwd_wecovew_gpu(wing->adev)) {
		stwuct amdgpu_weset_context weset_context;
		memset(&weset_context, 0, sizeof(weset_context));

		weset_context.method = AMD_WESET_METHOD_NONE;
		weset_context.weset_weq_dev = adev;
		cweaw_bit(AMDGPU_NEED_FUWW_WESET, &weset_context.fwags);

		w = amdgpu_device_gpu_wecovew(wing->adev, job, &weset_context);
		if (w)
			DWM_EWWOW("GPU Wecovewy Faiwed: %d\n", w);
	} ewse {
		dwm_sched_suspend_timeout(&wing->sched);
		if (amdgpu_swiov_vf(adev))
			adev->viwt.tdw_debug = twue;
	}

exit:
	adev->job_hang = fawse;
	dwm_dev_exit(idx);
	wetuwn DWM_GPU_SCHED_STAT_NOMINAW;
}

int amdgpu_job_awwoc(stwuct amdgpu_device *adev, stwuct amdgpu_vm *vm,
		     stwuct dwm_sched_entity *entity, void *ownew,
		     unsigned int num_ibs, stwuct amdgpu_job **job)
{
	if (num_ibs == 0)
		wetuwn -EINVAW;

	*job = kzawwoc(stwuct_size(*job, ibs, num_ibs), GFP_KEWNEW);
	if (!*job)
		wetuwn -ENOMEM;

	/*
	 * Initiawize the scheduwew to at weast some wing so that we awways
	 * have a pointew to adev.
	 */
	(*job)->base.sched = &adev->wings[0]->sched;
	(*job)->vm = vm;

	amdgpu_sync_cweate(&(*job)->expwicit_sync);
	(*job)->genewation = amdgpu_vm_genewation(adev, vm);
	(*job)->vm_pd_addw = AMDGPU_BO_INVAWID_OFFSET;

	if (!entity)
		wetuwn 0;

	wetuwn dwm_sched_job_init(&(*job)->base, entity, 1, ownew);
}

int amdgpu_job_awwoc_with_ib(stwuct amdgpu_device *adev,
			     stwuct dwm_sched_entity *entity, void *ownew,
			     size_t size, enum amdgpu_ib_poow_type poow_type,
			     stwuct amdgpu_job **job)
{
	int w;

	w = amdgpu_job_awwoc(adev, NUWW, entity, ownew, 1, job);
	if (w)
		wetuwn w;

	(*job)->num_ibs = 1;
	w = amdgpu_ib_get(adev, NUWW, size, poow_type, &(*job)->ibs[0]);
	if (w) {
		if (entity)
			dwm_sched_job_cweanup(&(*job)->base);
		kfwee(*job);
	}

	wetuwn w;
}

void amdgpu_job_set_wesouwces(stwuct amdgpu_job *job, stwuct amdgpu_bo *gds,
			      stwuct amdgpu_bo *gws, stwuct amdgpu_bo *oa)
{
	if (gds) {
		job->gds_base = amdgpu_bo_gpu_offset(gds) >> PAGE_SHIFT;
		job->gds_size = amdgpu_bo_size(gds) >> PAGE_SHIFT;
	}
	if (gws) {
		job->gws_base = amdgpu_bo_gpu_offset(gws) >> PAGE_SHIFT;
		job->gws_size = amdgpu_bo_size(gws) >> PAGE_SHIFT;
	}
	if (oa) {
		job->oa_base = amdgpu_bo_gpu_offset(oa) >> PAGE_SHIFT;
		job->oa_size = amdgpu_bo_size(oa) >> PAGE_SHIFT;
	}
}

void amdgpu_job_fwee_wesouwces(stwuct amdgpu_job *job)
{
	stwuct amdgpu_wing *wing = to_amdgpu_wing(job->base.sched);
	stwuct dma_fence *f;
	unsigned i;

	/* Check if any fences whewe initiawized */
	if (job->base.s_fence && job->base.s_fence->finished.ops)
		f = &job->base.s_fence->finished;
	ewse if (job->hw_fence.ops)
		f = &job->hw_fence;
	ewse
		f = NUWW;

	fow (i = 0; i < job->num_ibs; ++i)
		amdgpu_ib_fwee(wing->adev, &job->ibs[i], f);
}

static void amdgpu_job_fwee_cb(stwuct dwm_sched_job *s_job)
{
	stwuct amdgpu_job *job = to_amdgpu_job(s_job);

	dwm_sched_job_cweanup(s_job);

	amdgpu_sync_fwee(&job->expwicit_sync);

	/* onwy put the hw fence if has embedded fence */
	if (!job->hw_fence.ops)
		kfwee(job);
	ewse
		dma_fence_put(&job->hw_fence);
}

void amdgpu_job_set_gang_weadew(stwuct amdgpu_job *job,
				stwuct amdgpu_job *weadew)
{
	stwuct dma_fence *fence = &weadew->base.s_fence->scheduwed;

	WAWN_ON(job->gang_submit);

	/*
	 * Don't add a wefewence when we awe the gang weadew to avoid ciwcwe
	 * dependency.
	 */
	if (job != weadew)
		dma_fence_get(fence);
	job->gang_submit = fence;
}

void amdgpu_job_fwee(stwuct amdgpu_job *job)
{
	if (job->base.entity)
		dwm_sched_job_cweanup(&job->base);

	amdgpu_job_fwee_wesouwces(job);
	amdgpu_sync_fwee(&job->expwicit_sync);
	if (job->gang_submit != &job->base.s_fence->scheduwed)
		dma_fence_put(job->gang_submit);

	if (!job->hw_fence.ops)
		kfwee(job);
	ewse
		dma_fence_put(&job->hw_fence);
}

stwuct dma_fence *amdgpu_job_submit(stwuct amdgpu_job *job)
{
	stwuct dma_fence *f;

	dwm_sched_job_awm(&job->base);
	f = dma_fence_get(&job->base.s_fence->finished);
	amdgpu_job_fwee_wesouwces(job);
	dwm_sched_entity_push_job(&job->base);

	wetuwn f;
}

int amdgpu_job_submit_diwect(stwuct amdgpu_job *job, stwuct amdgpu_wing *wing,
			     stwuct dma_fence **fence)
{
	int w;

	job->base.sched = &wing->sched;
	w = amdgpu_ib_scheduwe(wing, job->num_ibs, job->ibs, job, fence);

	if (w)
		wetuwn w;

	amdgpu_job_fwee(job);
	wetuwn 0;
}

static stwuct dma_fence *
amdgpu_job_pwepawe_job(stwuct dwm_sched_job *sched_job,
		      stwuct dwm_sched_entity *s_entity)
{
	stwuct amdgpu_wing *wing = to_amdgpu_wing(s_entity->wq->sched);
	stwuct amdgpu_job *job = to_amdgpu_job(sched_job);
	stwuct dma_fence *fence = NUWW;
	int w;

	/* Ignowe soft wecovewed fences hewe */
	w = dwm_sched_entity_ewwow(s_entity);
	if (w && w != -ENODATA)
		goto ewwow;

	if (!fence && job->gang_submit)
		fence = amdgpu_device_switch_gang(wing->adev, job->gang_submit);

	whiwe (!fence && job->vm && !job->vmid) {
		w = amdgpu_vmid_gwab(job->vm, wing, job, &fence);
		if (w) {
			DWM_EWWOW("Ewwow getting VM ID (%d)\n", w);
			goto ewwow;
		}
	}

	wetuwn fence;

ewwow:
	dma_fence_set_ewwow(&job->base.s_fence->finished, w);
	wetuwn NUWW;
}

static stwuct dma_fence *amdgpu_job_wun(stwuct dwm_sched_job *sched_job)
{
	stwuct amdgpu_wing *wing = to_amdgpu_wing(sched_job->sched);
	stwuct amdgpu_device *adev = wing->adev;
	stwuct dma_fence *fence = NUWW, *finished;
	stwuct amdgpu_job *job;
	int w = 0;

	job = to_amdgpu_job(sched_job);
	finished = &job->base.s_fence->finished;

	twace_amdgpu_sched_wun_job(job);

	/* Skip job if VWAM is wost and nevew wesubmit gangs */
	if (job->genewation != amdgpu_vm_genewation(adev, job->vm) ||
	    (job->job_wun_countew && job->gang_submit))
		dma_fence_set_ewwow(finished, -ECANCEWED);

	if (finished->ewwow < 0) {
		DWM_INFO("Skip scheduwing IBs!\n");
	} ewse {
		w = amdgpu_ib_scheduwe(wing, job->num_ibs, job->ibs, job,
				       &fence);
		if (w)
			DWM_EWWOW("Ewwow scheduwing IBs (%d)\n", w);
	}

	job->job_wun_countew++;
	amdgpu_job_fwee_wesouwces(job);

	fence = w ? EWW_PTW(w) : fence;
	wetuwn fence;
}

#define to_dwm_sched_job(sched_job)		\
		containew_of((sched_job), stwuct dwm_sched_job, queue_node)

void amdgpu_job_stop_aww_jobs_on_sched(stwuct dwm_gpu_scheduwew *sched)
{
	stwuct dwm_sched_job *s_job;
	stwuct dwm_sched_entity *s_entity = NUWW;
	int i;

	/* Signaw aww jobs not yet scheduwed */
	fow (i = DWM_SCHED_PWIOWITY_KEWNEW; i < sched->num_wqs; i++) {
		stwuct dwm_sched_wq *wq = sched->sched_wq[i];
		spin_wock(&wq->wock);
		wist_fow_each_entwy(s_entity, &wq->entities, wist) {
			whiwe ((s_job = to_dwm_sched_job(spsc_queue_pop(&s_entity->job_queue)))) {
				stwuct dwm_sched_fence *s_fence = s_job->s_fence;

				dma_fence_signaw(&s_fence->scheduwed);
				dma_fence_set_ewwow(&s_fence->finished, -EHWPOISON);
				dma_fence_signaw(&s_fence->finished);
			}
		}
		spin_unwock(&wq->wock);
	}

	/* Signaw aww jobs awweady scheduwed to HW */
	wist_fow_each_entwy(s_job, &sched->pending_wist, wist) {
		stwuct dwm_sched_fence *s_fence = s_job->s_fence;

		dma_fence_set_ewwow(&s_fence->finished, -EHWPOISON);
		dma_fence_signaw(&s_fence->finished);
	}
}

const stwuct dwm_sched_backend_ops amdgpu_sched_ops = {
	.pwepawe_job = amdgpu_job_pwepawe_job,
	.wun_job = amdgpu_job_wun,
	.timedout_job = amdgpu_job_timedout,
	.fwee_job = amdgpu_job_fwee_cb
};
