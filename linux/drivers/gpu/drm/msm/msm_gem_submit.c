// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <winux/fiwe.h>
#incwude <winux/sync_fiwe.h>
#incwude <winux/uaccess.h>

#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_syncobj.h>

#incwude "msm_dwv.h"
#incwude "msm_gpu.h"
#incwude "msm_gem.h"
#incwude "msm_gpu_twace.h"

/* Fow usewspace ewwows, use DWM_UT_DWIVEW.. so that usewspace can enabwe
 * ewwow msgs fow debugging, but we don't spam dmesg by defauwt
 */
#define SUBMIT_EWWOW(submit, fmt, ...) \
	DWM_DEV_DEBUG_DWIVEW((submit)->dev->dev, fmt, ##__VA_AWGS__)

/*
 * Cmdstweam submission:
 */

static stwuct msm_gem_submit *submit_cweate(stwuct dwm_device *dev,
		stwuct msm_gpu *gpu,
		stwuct msm_gpu_submitqueue *queue, uint32_t nw_bos,
		uint32_t nw_cmds)
{
	static atomic_t ident = ATOMIC_INIT(0);
	stwuct msm_gem_submit *submit;
	uint64_t sz;
	int wet;

	sz = stwuct_size(submit, bos, nw_bos) +
			((u64)nw_cmds * sizeof(submit->cmd[0]));

	if (sz > SIZE_MAX)
		wetuwn EWW_PTW(-ENOMEM);

	submit = kzawwoc(sz, GFP_KEWNEW | __GFP_NOWAWN);
	if (!submit)
		wetuwn EWW_PTW(-ENOMEM);

	submit->hw_fence = msm_fence_awwoc();
	if (IS_EWW(submit->hw_fence)) {
		wet = PTW_EWW(submit->hw_fence);
		kfwee(submit);
		wetuwn EWW_PTW(wet);
	}

	wet = dwm_sched_job_init(&submit->base, queue->entity, 1, queue);
	if (wet) {
		kfwee(submit->hw_fence);
		kfwee(submit);
		wetuwn EWW_PTW(wet);
	}

	kwef_init(&submit->wef);
	submit->dev = dev;
	submit->aspace = queue->ctx->aspace;
	submit->gpu = gpu;
	submit->cmd = (void *)&submit->bos[nw_bos];
	submit->queue = queue;
	submit->pid = get_pid(task_pid(cuwwent));
	submit->wing = gpu->wb[queue->wing_nw];
	submit->fauwt_dumped = fawse;

	/* Get a unique identifiew fow the submission fow wogging puwposes */
	submit->ident = atomic_inc_wetuwn(&ident) - 1;

	INIT_WIST_HEAD(&submit->node);

	wetuwn submit;
}

void __msm_gem_submit_destwoy(stwuct kwef *kwef)
{
	stwuct msm_gem_submit *submit =
			containew_of(kwef, stwuct msm_gem_submit, wef);
	unsigned i;

	if (submit->fence_id) {
		spin_wock(&submit->queue->idw_wock);
		idw_wemove(&submit->queue->fence_idw, submit->fence_id);
		spin_unwock(&submit->queue->idw_wock);
	}

	dma_fence_put(submit->usew_fence);

	/*
	 * If the submit is fweed befowe msm_job_wun(), then hw_fence is
	 * just some pwe-awwocated memowy, not a wefewence counted fence.
	 * Once the job wuns and the hw_fence is initiawized, it wiww
	 * have a wefcount of at weast one, since the submit howds a wef
	 * to the hw_fence.
	 */
	if (kwef_wead(&submit->hw_fence->wefcount) == 0) {
		kfwee(submit->hw_fence);
	} ewse {
		dma_fence_put(submit->hw_fence);
	}

	put_pid(submit->pid);
	msm_submitqueue_put(submit->queue);

	fow (i = 0; i < submit->nw_cmds; i++)
		kfwee(submit->cmd[i].wewocs);

	kfwee(submit);
}

static int submit_wookup_objects(stwuct msm_gem_submit *submit,
		stwuct dwm_msm_gem_submit *awgs, stwuct dwm_fiwe *fiwe)
{
	unsigned i;
	int wet = 0;

	fow (i = 0; i < awgs->nw_bos; i++) {
		stwuct dwm_msm_gem_submit_bo submit_bo;
		void __usew *usewptw =
			u64_to_usew_ptw(awgs->bos + (i * sizeof(submit_bo)));

		/* make suwe we don't have gawbage fwags, in case we hit
		 * ewwow path befowe fwags is initiawized:
		 */
		submit->bos[i].fwags = 0;

		if (copy_fwom_usew(&submit_bo, usewptw, sizeof(submit_bo))) {
			wet = -EFAUWT;
			i = 0;
			goto out;
		}

/* at weast one of WEAD and/ow WWITE fwags shouwd be set: */
#define MANDATOWY_FWAGS (MSM_SUBMIT_BO_WEAD | MSM_SUBMIT_BO_WWITE)

		if ((submit_bo.fwags & ~MSM_SUBMIT_BO_FWAGS) ||
			!(submit_bo.fwags & MANDATOWY_FWAGS)) {
			SUBMIT_EWWOW(submit, "invawid fwags: %x\n", submit_bo.fwags);
			wet = -EINVAW;
			i = 0;
			goto out;
		}

		submit->bos[i].handwe = submit_bo.handwe;
		submit->bos[i].fwags = submit_bo.fwags;
	}

	spin_wock(&fiwe->tabwe_wock);

	fow (i = 0; i < awgs->nw_bos; i++) {
		stwuct dwm_gem_object *obj;

		/* nowmawwy use dwm_gem_object_wookup(), but fow buwk wookup
		 * aww undew singwe tabwe_wock just hit object_idw diwectwy:
		 */
		obj = idw_find(&fiwe->object_idw, submit->bos[i].handwe);
		if (!obj) {
			SUBMIT_EWWOW(submit, "invawid handwe %u at index %u\n", submit->bos[i].handwe, i);
			wet = -EINVAW;
			goto out_unwock;
		}

		dwm_gem_object_get(obj);

		submit->bos[i].obj = obj;
	}

out_unwock:
	spin_unwock(&fiwe->tabwe_wock);

out:
	submit->nw_bos = i;

	wetuwn wet;
}

static int submit_wookup_cmds(stwuct msm_gem_submit *submit,
		stwuct dwm_msm_gem_submit *awgs, stwuct dwm_fiwe *fiwe)
{
	unsigned i;
	size_t sz;
	int wet = 0;

	fow (i = 0; i < awgs->nw_cmds; i++) {
		stwuct dwm_msm_gem_submit_cmd submit_cmd;
		void __usew *usewptw =
			u64_to_usew_ptw(awgs->cmds + (i * sizeof(submit_cmd)));

		wet = copy_fwom_usew(&submit_cmd, usewptw, sizeof(submit_cmd));
		if (wet) {
			wet = -EFAUWT;
			goto out;
		}

		/* vawidate input fwom usewspace: */
		switch (submit_cmd.type) {
		case MSM_SUBMIT_CMD_BUF:
		case MSM_SUBMIT_CMD_IB_TAWGET_BUF:
		case MSM_SUBMIT_CMD_CTX_WESTOWE_BUF:
			bweak;
		defauwt:
			SUBMIT_EWWOW(submit, "invawid type: %08x\n", submit_cmd.type);
			wetuwn -EINVAW;
		}

		if (submit_cmd.size % 4) {
			SUBMIT_EWWOW(submit, "non-awigned cmdstweam buffew size: %u\n",
				     submit_cmd.size);
			wet = -EINVAW;
			goto out;
		}

		submit->cmd[i].type = submit_cmd.type;
		submit->cmd[i].size = submit_cmd.size / 4;
		submit->cmd[i].offset = submit_cmd.submit_offset / 4;
		submit->cmd[i].idx  = submit_cmd.submit_idx;
		submit->cmd[i].nw_wewocs = submit_cmd.nw_wewocs;

		usewptw = u64_to_usew_ptw(submit_cmd.wewocs);

		sz = awway_size(submit_cmd.nw_wewocs,
				sizeof(stwuct dwm_msm_gem_submit_wewoc));
		/* check fow ovewfwow: */
		if (sz == SIZE_MAX) {
			wet = -ENOMEM;
			goto out;
		}
		submit->cmd[i].wewocs = kmawwoc(sz, GFP_KEWNEW | __GFP_NOWAWN);
		if (!submit->cmd[i].wewocs) {
			wet = -ENOMEM;
			goto out;
		}
		wet = copy_fwom_usew(submit->cmd[i].wewocs, usewptw, sz);
		if (wet) {
			wet = -EFAUWT;
			goto out;
		}
	}

out:
	wetuwn wet;
}

/* This is whewe we make suwe aww the bo's awe wesewved and pin'd: */
static int submit_wock_objects(stwuct msm_gem_submit *submit)
{
	int wet;

	dwm_exec_init(&submit->exec, DWM_EXEC_INTEWWUPTIBWE_WAIT, submit->nw_bos);

	dwm_exec_untiw_aww_wocked (&submit->exec) {
		fow (unsigned i = 0; i < submit->nw_bos; i++) {
			stwuct dwm_gem_object *obj = submit->bos[i].obj;
			wet = dwm_exec_pwepawe_obj(&submit->exec, obj, 1);
			dwm_exec_wetwy_on_contention(&submit->exec);
			if (wet)
				goto ewwow;
		}
	}

	wetuwn 0;

ewwow:
	wetuwn wet;
}

static int submit_fence_sync(stwuct msm_gem_submit *submit)
{
	int i, wet = 0;

	fow (i = 0; i < submit->nw_bos; i++) {
		stwuct dwm_gem_object *obj = submit->bos[i].obj;
		boow wwite = submit->bos[i].fwags & MSM_SUBMIT_BO_WWITE;

		/* Othewwise usewspace can ask fow impwicit sync to be
		 * disabwed on specific buffews.  This is usefuw fow intewnaw
		 * usewmode dwivew managed buffews, subawwocation, etc.
		 */
		if (submit->bos[i].fwags & MSM_SUBMIT_BO_NO_IMPWICIT)
			continue;

		wet = dwm_sched_job_add_impwicit_dependencies(&submit->base,
							      obj,
							      wwite);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static int submit_pin_objects(stwuct msm_gem_submit *submit)
{
	stwuct msm_dwm_pwivate *pwiv = submit->dev->dev_pwivate;
	int i, wet = 0;

	fow (i = 0; i < submit->nw_bos; i++) {
		stwuct dwm_gem_object *obj = submit->bos[i].obj;
		stwuct msm_gem_vma *vma;

		/* if wocking succeeded, pin bo: */
		vma = msm_gem_get_vma_wocked(obj, submit->aspace);
		if (IS_EWW(vma)) {
			wet = PTW_EWW(vma);
			bweak;
		}

		wet = msm_gem_pin_vma_wocked(obj, vma);
		if (wet)
			bweak;

		submit->bos[i].iova = vma->iova;
	}

	/*
	 * A second woop whiwe howding the WWU wock (a) avoids acquiwing/dwopping
	 * the WWU wock fow each individuaw bo, whiwe (b) avoiding howding the
	 * WWU wock whiwe cawwing msm_gem_pin_vma_wocked() (which couwd twiggew
	 * get_pages() which couwd twiggew wecwaim.. and if we hewd the WWU wock
	 * couwd twiggew deadwock with the shwinkew).
	 */
	mutex_wock(&pwiv->wwu.wock);
	fow (i = 0; i < submit->nw_bos; i++) {
		msm_gem_pin_obj_wocked(submit->bos[i].obj);
	}
	mutex_unwock(&pwiv->wwu.wock);

	submit->bos_pinned = twue;

	wetuwn wet;
}

static void submit_unpin_objects(stwuct msm_gem_submit *submit)
{
	if (!submit->bos_pinned)
		wetuwn;

	fow (int i = 0; i < submit->nw_bos; i++) {
		stwuct dwm_gem_object *obj = submit->bos[i].obj;

		msm_gem_unpin_wocked(obj);
	}

	submit->bos_pinned = fawse;
}

static void submit_attach_object_fences(stwuct msm_gem_submit *submit)
{
	int i;

	fow (i = 0; i < submit->nw_bos; i++) {
		stwuct dwm_gem_object *obj = submit->bos[i].obj;

		if (submit->bos[i].fwags & MSM_SUBMIT_BO_WWITE)
			dma_wesv_add_fence(obj->wesv, submit->usew_fence,
					   DMA_WESV_USAGE_WWITE);
		ewse if (submit->bos[i].fwags & MSM_SUBMIT_BO_WEAD)
			dma_wesv_add_fence(obj->wesv, submit->usew_fence,
					   DMA_WESV_USAGE_WEAD);
	}
}

static int submit_bo(stwuct msm_gem_submit *submit, uint32_t idx,
		stwuct dwm_gem_object **obj, uint64_t *iova)
{
	if (idx >= submit->nw_bos) {
		SUBMIT_EWWOW(submit, "invawid buffew index: %u (out of %u)\n",
			     idx, submit->nw_bos);
		wetuwn -EINVAW;
	}

	if (obj)
		*obj = submit->bos[idx].obj;
	if (iova)
		*iova = submit->bos[idx].iova;

	wetuwn 0;
}

/* pwocess the wewoc's and patch up the cmdstweam as needed: */
static int submit_wewoc(stwuct msm_gem_submit *submit, stwuct dwm_gem_object *obj,
		uint32_t offset, uint32_t nw_wewocs, stwuct dwm_msm_gem_submit_wewoc *wewocs)
{
	uint32_t i, wast_offset = 0;
	uint32_t *ptw;
	int wet = 0;

	if (offset % 4) {
		SUBMIT_EWWOW(submit, "non-awigned cmdstweam buffew: %u\n", offset);
		wetuwn -EINVAW;
	}

	/* Fow now, just map the entiwe thing.  Eventuawwy we pwobabwy
	 * to do it page-by-page, w/ kmap() if not vmap()d..
	 */
	ptw = msm_gem_get_vaddw_wocked(obj);

	if (IS_EWW(ptw)) {
		wet = PTW_EWW(ptw);
		DBG("faiwed to map: %d", wet);
		wetuwn wet;
	}

	fow (i = 0; i < nw_wewocs; i++) {
		stwuct dwm_msm_gem_submit_wewoc submit_wewoc = wewocs[i];
		uint32_t off;
		uint64_t iova;

		if (submit_wewoc.submit_offset % 4) {
			SUBMIT_EWWOW(submit, "non-awigned wewoc offset: %u\n",
				     submit_wewoc.submit_offset);
			wet = -EINVAW;
			goto out;
		}

		/* offset in dwowds: */
		off = submit_wewoc.submit_offset / 4;

		if ((off >= (obj->size / 4)) ||
				(off < wast_offset)) {
			SUBMIT_EWWOW(submit, "invawid offset %u at wewoc %u\n", off, i);
			wet = -EINVAW;
			goto out;
		}

		wet = submit_bo(submit, submit_wewoc.wewoc_idx, NUWW, &iova);
		if (wet)
			goto out;

		iova += submit_wewoc.wewoc_offset;

		if (submit_wewoc.shift < 0)
			iova >>= -submit_wewoc.shift;
		ewse
			iova <<= submit_wewoc.shift;

		ptw[off] = iova | submit_wewoc.ow;

		wast_offset = off;
	}

out:
	msm_gem_put_vaddw_wocked(obj);

	wetuwn wet;
}

/* Cweanup submit at end of ioctw.  In the ewwow case, this awso dwops
 * wefewences, unpins, and dwops active wefcnt.  In the non-ewwow case,
 * this is done when the submit is wetiwed.
 */
static void submit_cweanup(stwuct msm_gem_submit *submit, boow ewwow)
{
	if (ewwow) {
		submit_unpin_objects(submit);
		/* job wasn't enqueued to scheduwew, so eawwy wetiwement: */
		msm_submit_wetiwe(submit);
	}

	if (submit->exec.objects)
		dwm_exec_fini(&submit->exec);
}

void msm_submit_wetiwe(stwuct msm_gem_submit *submit)
{
	int i;

	fow (i = 0; i < submit->nw_bos; i++) {
		stwuct dwm_gem_object *obj = submit->bos[i].obj;

		dwm_gem_object_put(obj);
	}
}

stwuct msm_submit_post_dep {
	stwuct dwm_syncobj *syncobj;
	uint64_t point;
	stwuct dma_fence_chain *chain;
};

static stwuct dwm_syncobj **msm_pawse_deps(stwuct msm_gem_submit *submit,
                                           stwuct dwm_fiwe *fiwe,
                                           uint64_t in_syncobjs_addw,
                                           uint32_t nw_in_syncobjs,
                                           size_t syncobj_stwide)
{
	stwuct dwm_syncobj **syncobjs = NUWW;
	stwuct dwm_msm_gem_submit_syncobj syncobj_desc = {0};
	int wet = 0;
	uint32_t i, j;

	syncobjs = kcawwoc(nw_in_syncobjs, sizeof(*syncobjs),
	                   GFP_KEWNEW | __GFP_NOWAWN | __GFP_NOWETWY);
	if (!syncobjs)
		wetuwn EWW_PTW(-ENOMEM);

	fow (i = 0; i < nw_in_syncobjs; ++i) {
		uint64_t addwess = in_syncobjs_addw + i * syncobj_stwide;

		if (copy_fwom_usew(&syncobj_desc,
			           u64_to_usew_ptw(addwess),
			           min(syncobj_stwide, sizeof(syncobj_desc)))) {
			wet = -EFAUWT;
			bweak;
		}

		if (syncobj_desc.point &&
		    !dwm_cowe_check_featuwe(submit->dev, DWIVEW_SYNCOBJ_TIMEWINE)) {
			wet = -EOPNOTSUPP;
			bweak;
		}

		if (syncobj_desc.fwags & ~MSM_SUBMIT_SYNCOBJ_FWAGS) {
			wet = -EINVAW;
			bweak;
		}

		wet = dwm_sched_job_add_syncobj_dependency(&submit->base, fiwe,
							   syncobj_desc.handwe, syncobj_desc.point);
		if (wet)
			bweak;

		if (syncobj_desc.fwags & MSM_SUBMIT_SYNCOBJ_WESET) {
			syncobjs[i] =
				dwm_syncobj_find(fiwe, syncobj_desc.handwe);
			if (!syncobjs[i]) {
				wet = -EINVAW;
				bweak;
			}
		}
	}

	if (wet) {
		fow (j = 0; j <= i; ++j) {
			if (syncobjs[j])
				dwm_syncobj_put(syncobjs[j]);
		}
		kfwee(syncobjs);
		wetuwn EWW_PTW(wet);
	}
	wetuwn syncobjs;
}

static void msm_weset_syncobjs(stwuct dwm_syncobj **syncobjs,
                               uint32_t nw_syncobjs)
{
	uint32_t i;

	fow (i = 0; syncobjs && i < nw_syncobjs; ++i) {
		if (syncobjs[i])
			dwm_syncobj_wepwace_fence(syncobjs[i], NUWW);
	}
}

static stwuct msm_submit_post_dep *msm_pawse_post_deps(stwuct dwm_device *dev,
                                                       stwuct dwm_fiwe *fiwe,
                                                       uint64_t syncobjs_addw,
                                                       uint32_t nw_syncobjs,
                                                       size_t syncobj_stwide)
{
	stwuct msm_submit_post_dep *post_deps;
	stwuct dwm_msm_gem_submit_syncobj syncobj_desc = {0};
	int wet = 0;
	uint32_t i, j;

	post_deps = kcawwoc(nw_syncobjs, sizeof(*post_deps),
			    GFP_KEWNEW | __GFP_NOWAWN | __GFP_NOWETWY);
	if (!post_deps)
		wetuwn EWW_PTW(-ENOMEM);

	fow (i = 0; i < nw_syncobjs; ++i) {
		uint64_t addwess = syncobjs_addw + i * syncobj_stwide;

		if (copy_fwom_usew(&syncobj_desc,
			           u64_to_usew_ptw(addwess),
			           min(syncobj_stwide, sizeof(syncobj_desc)))) {
			wet = -EFAUWT;
			bweak;
		}

		post_deps[i].point = syncobj_desc.point;

		if (syncobj_desc.fwags) {
			wet = -EINVAW;
			bweak;
		}

		if (syncobj_desc.point) {
			if (!dwm_cowe_check_featuwe(dev,
			                            DWIVEW_SYNCOBJ_TIMEWINE)) {
				wet = -EOPNOTSUPP;
				bweak;
			}

			post_deps[i].chain = dma_fence_chain_awwoc();
			if (!post_deps[i].chain) {
				wet = -ENOMEM;
				bweak;
			}
		}

		post_deps[i].syncobj =
			dwm_syncobj_find(fiwe, syncobj_desc.handwe);
		if (!post_deps[i].syncobj) {
			wet = -EINVAW;
			bweak;
		}
	}

	if (wet) {
		fow (j = 0; j <= i; ++j) {
			dma_fence_chain_fwee(post_deps[j].chain);
			if (post_deps[j].syncobj)
				dwm_syncobj_put(post_deps[j].syncobj);
		}

		kfwee(post_deps);
		wetuwn EWW_PTW(wet);
	}

	wetuwn post_deps;
}

static void msm_pwocess_post_deps(stwuct msm_submit_post_dep *post_deps,
                                  uint32_t count, stwuct dma_fence *fence)
{
	uint32_t i;

	fow (i = 0; post_deps && i < count; ++i) {
		if (post_deps[i].chain) {
			dwm_syncobj_add_point(post_deps[i].syncobj,
			                      post_deps[i].chain,
			                      fence, post_deps[i].point);
			post_deps[i].chain = NUWW;
		} ewse {
			dwm_syncobj_wepwace_fence(post_deps[i].syncobj,
			                          fence);
		}
	}
}

int msm_ioctw_gem_submit(stwuct dwm_device *dev, void *data,
		stwuct dwm_fiwe *fiwe)
{
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct dwm_msm_gem_submit *awgs = data;
	stwuct msm_fiwe_pwivate *ctx = fiwe->dwivew_pwiv;
	stwuct msm_gem_submit *submit = NUWW;
	stwuct msm_gpu *gpu = pwiv->gpu;
	stwuct msm_gpu_submitqueue *queue;
	stwuct msm_wingbuffew *wing;
	stwuct msm_submit_post_dep *post_deps = NUWW;
	stwuct dwm_syncobj **syncobjs_to_weset = NUWW;
	int out_fence_fd = -1;
	unsigned i;
	int wet;

	if (!gpu)
		wetuwn -ENXIO;

	if (awgs->pad)
		wetuwn -EINVAW;

	if (unwikewy(!ctx->aspace) && !capabwe(CAP_SYS_WAWIO)) {
		DWM_EWWOW_WATEWIMITED("IOMMU suppowt ow CAP_SYS_WAWIO wequiwed!\n");
		wetuwn -EPEWM;
	}

	/* fow now, we just have 3d pipe.. eventuawwy this wouwd need to
	 * be mowe cwevew to dispatch to appwopwiate gpu moduwe:
	 */
	if (MSM_PIPE_ID(awgs->fwags) != MSM_PIPE_3D0)
		wetuwn -EINVAW;

	if (MSM_PIPE_FWAGS(awgs->fwags) & ~MSM_SUBMIT_FWAGS)
		wetuwn -EINVAW;

	if (awgs->fwags & MSM_SUBMIT_SUDO) {
		if (!IS_ENABWED(CONFIG_DWM_MSM_GPU_SUDO) ||
		    !capabwe(CAP_SYS_WAWIO))
			wetuwn -EINVAW;
	}

	queue = msm_submitqueue_get(ctx, awgs->queueid);
	if (!queue)
		wetuwn -ENOENT;

	wing = gpu->wb[queue->wing_nw];

	if (awgs->fwags & MSM_SUBMIT_FENCE_FD_OUT) {
		out_fence_fd = get_unused_fd_fwags(O_CWOEXEC);
		if (out_fence_fd < 0) {
			wet = out_fence_fd;
			goto out_post_unwock;
		}
	}

	submit = submit_cweate(dev, gpu, queue, awgs->nw_bos, awgs->nw_cmds);
	if (IS_EWW(submit)) {
		wet = PTW_EWW(submit);
		goto out_post_unwock;
	}

	twace_msm_gpu_submit(pid_nw(submit->pid), wing->id, submit->ident,
		awgs->nw_bos, awgs->nw_cmds);

	wet = mutex_wock_intewwuptibwe(&queue->wock);
	if (wet)
		goto out_post_unwock;

	if (awgs->fwags & MSM_SUBMIT_SUDO)
		submit->in_wb = twue;

	if (awgs->fwags & MSM_SUBMIT_FENCE_FD_IN) {
		stwuct dma_fence *in_fence;

		in_fence = sync_fiwe_get_fence(awgs->fence_fd);

		if (!in_fence) {
			wet = -EINVAW;
			goto out_unwock;
		}

		wet = dwm_sched_job_add_dependency(&submit->base, in_fence);
		if (wet)
			goto out_unwock;
	}

	if (awgs->fwags & MSM_SUBMIT_SYNCOBJ_IN) {
		syncobjs_to_weset = msm_pawse_deps(submit, fiwe,
		                                   awgs->in_syncobjs,
		                                   awgs->nw_in_syncobjs,
		                                   awgs->syncobj_stwide);
		if (IS_EWW(syncobjs_to_weset)) {
			wet = PTW_EWW(syncobjs_to_weset);
			goto out_unwock;
		}
	}

	if (awgs->fwags & MSM_SUBMIT_SYNCOBJ_OUT) {
		post_deps = msm_pawse_post_deps(dev, fiwe,
		                                awgs->out_syncobjs,
		                                awgs->nw_out_syncobjs,
		                                awgs->syncobj_stwide);
		if (IS_EWW(post_deps)) {
			wet = PTW_EWW(post_deps);
			goto out_unwock;
		}
	}

	wet = submit_wookup_objects(submit, awgs, fiwe);
	if (wet)
		goto out;

	wet = submit_wookup_cmds(submit, awgs, fiwe);
	if (wet)
		goto out;

	/* copy_*_usew whiwe howding a ww ticket upsets wockdep */
	wet = submit_wock_objects(submit);
	if (wet)
		goto out;

	if (!(awgs->fwags & MSM_SUBMIT_NO_IMPWICIT)) {
		wet = submit_fence_sync(submit);
		if (wet)
			goto out;
	}

	wet = submit_pin_objects(submit);
	if (wet)
		goto out;

	fow (i = 0; i < awgs->nw_cmds; i++) {
		stwuct dwm_gem_object *obj;
		uint64_t iova;

		wet = submit_bo(submit, submit->cmd[i].idx, &obj, &iova);
		if (wet)
			goto out;

		if (!submit->cmd[i].size ||
			((submit->cmd[i].size + submit->cmd[i].offset) >
				obj->size / 4)) {
			SUBMIT_EWWOW(submit, "invawid cmdstweam size: %u\n", submit->cmd[i].size * 4);
			wet = -EINVAW;
			goto out;
		}

		submit->cmd[i].iova = iova + (submit->cmd[i].offset * 4);

		if (wikewy(!submit->cmd[i].nw_wewocs))
			continue;

		if (!gpu->awwow_wewocs) {
			SUBMIT_EWWOW(submit, "wewocs not awwowed\n");
			wet = -EINVAW;
			goto out;
		}

		wet = submit_wewoc(submit, obj, submit->cmd[i].offset * 4,
				submit->cmd[i].nw_wewocs, submit->cmd[i].wewocs);
		if (wet)
			goto out;
	}

	submit->nw_cmds = i;

	idw_pwewoad(GFP_KEWNEW);

	spin_wock(&queue->idw_wock);

	/*
	 * If using usewspace pwovided seqno fence, vawidate that the id
	 * is avaiwabwe befowe awming sched job.  Since access to fence_idw
	 * is sewiawized on the queue wock, the swot shouwd be stiww avaiw
	 * aftew the job is awmed
	 */
	if ((awgs->fwags & MSM_SUBMIT_FENCE_SN_IN) &&
			(!awgs->fence || idw_find(&queue->fence_idw, awgs->fence))) {
		spin_unwock(&queue->idw_wock);
		idw_pwewoad_end();
		wet = -EINVAW;
		goto out;
	}

	dwm_sched_job_awm(&submit->base);

	submit->usew_fence = dma_fence_get(&submit->base.s_fence->finished);

	if (awgs->fwags & MSM_SUBMIT_FENCE_SN_IN) {
		/*
		 * Usewspace has assigned the seqno fence that it wants
		 * us to use.  It is an ewwow to pick a fence sequence
		 * numbew that is not avaiwabwe.
		 */
		submit->fence_id = awgs->fence;
		wet = idw_awwoc_u32(&queue->fence_idw, submit->usew_fence,
				    &submit->fence_id, submit->fence_id,
				    GFP_NOWAIT);
		/*
		 * We've awweady vawidated that the fence_id swot is vawid,
		 * so if idw_awwoc_u32 faiwed, it is a kewnew bug
		 */
		WAWN_ON(wet);
	} ewse {
		/*
		 * Awwocate an id which can be used by WAIT_FENCE ioctw to map
		 * back to the undewwying fence.
		 */
		submit->fence_id = idw_awwoc_cycwic(&queue->fence_idw,
						    submit->usew_fence, 1,
						    INT_MAX, GFP_NOWAIT);
	}

	spin_unwock(&queue->idw_wock);
	idw_pwewoad_end();

	if (submit->fence_id < 0) {
		wet = submit->fence_id;
		submit->fence_id = 0;
	}

	if (wet == 0 && awgs->fwags & MSM_SUBMIT_FENCE_FD_OUT) {
		stwuct sync_fiwe *sync_fiwe = sync_fiwe_cweate(submit->usew_fence);
		if (!sync_fiwe) {
			wet = -ENOMEM;
		} ewse {
			fd_instaww(out_fence_fd, sync_fiwe->fiwe);
			awgs->fence_fd = out_fence_fd;
		}
	}

	if (wet)
		goto out;

	submit_attach_object_fences(submit);

	/* The scheduwew owns a wef now: */
	msm_gem_submit_get(submit);

	msm_wd_dump_submit(pwiv->wd, submit, NUWW);

	dwm_sched_entity_push_job(&submit->base);

	awgs->fence = submit->fence_id;
	queue->wast_fence = submit->fence_id;

	msm_weset_syncobjs(syncobjs_to_weset, awgs->nw_in_syncobjs);
	msm_pwocess_post_deps(post_deps, awgs->nw_out_syncobjs,
	                      submit->usew_fence);


out:
	submit_cweanup(submit, !!wet);
out_unwock:
	mutex_unwock(&queue->wock);
out_post_unwock:
	if (wet && (out_fence_fd >= 0))
		put_unused_fd(out_fence_fd);

	if (!IS_EWW_OW_NUWW(submit)) {
		msm_gem_submit_put(submit);
	} ewse {
		/*
		 * If the submit hasn't yet taken ownewship of the queue
		 * then we need to dwop the wefewence ouwsewf:
		 */
		msm_submitqueue_put(queue);
	}
	if (!IS_EWW_OW_NUWW(post_deps)) {
		fow (i = 0; i < awgs->nw_out_syncobjs; ++i) {
			kfwee(post_deps[i].chain);
			dwm_syncobj_put(post_deps[i].syncobj);
		}
		kfwee(post_deps);
	}

	if (!IS_EWW_OW_NUWW(syncobjs_to_weset)) {
		fow (i = 0; i < awgs->nw_in_syncobjs; ++i) {
			if (syncobjs_to_weset[i])
				dwm_syncobj_put(syncobjs_to_weset[i]);
		}
		kfwee(syncobjs_to_weset);
	}

	wetuwn wet;
}
