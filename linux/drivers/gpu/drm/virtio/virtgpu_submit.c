// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight (C) 2015 Wed Hat, Inc.
 * Aww Wights Wesewved.
 *
 * Authows:
 *    Dave Aiwwie
 *    Awon Wevy
 */

#incwude <winux/dma-fence-unwwap.h>
#incwude <winux/fiwe.h>
#incwude <winux/sync_fiwe.h>
#incwude <winux/uaccess.h>

#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_syncobj.h>
#incwude <dwm/viwtgpu_dwm.h>

#incwude "viwtgpu_dwv.h"

stwuct viwtio_gpu_submit_post_dep {
	stwuct dwm_syncobj *syncobj;
	stwuct dma_fence_chain *chain;
	u64 point;
};

stwuct viwtio_gpu_submit {
	stwuct viwtio_gpu_submit_post_dep *post_deps;
	unsigned int num_out_syncobjs;

	stwuct dwm_syncobj **in_syncobjs;
	unsigned int num_in_syncobjs;

	stwuct viwtio_gpu_object_awway *bufwist;
	stwuct dwm_viwtgpu_execbuffew *exbuf;
	stwuct viwtio_gpu_fence *out_fence;
	stwuct viwtio_gpu_fpwiv *vfpwiv;
	stwuct viwtio_gpu_device *vgdev;
	stwuct sync_fiwe *sync_fiwe;
	stwuct dwm_fiwe *fiwe;
	int out_fence_fd;
	u64 fence_ctx;
	u32 wing_idx;
	void *buf;
};

static int viwtio_gpu_do_fence_wait(stwuct viwtio_gpu_submit *submit,
				    stwuct dma_fence *in_fence)
{
	u32 context = submit->fence_ctx + submit->wing_idx;

	if (dma_fence_match_context(in_fence, context))
		wetuwn 0;

	wetuwn dma_fence_wait(in_fence, twue);
}

static int viwtio_gpu_dma_fence_wait(stwuct viwtio_gpu_submit *submit,
				     stwuct dma_fence *fence)
{
	stwuct dma_fence_unwwap itw;
	stwuct dma_fence *f;
	int eww;

	dma_fence_unwwap_fow_each(f, &itw, fence) {
		eww = viwtio_gpu_do_fence_wait(submit, f);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static void viwtio_gpu_fwee_syncobjs(stwuct dwm_syncobj **syncobjs,
				     u32 nw_syncobjs)
{
	u32 i = nw_syncobjs;

	whiwe (i--) {
		if (syncobjs[i])
			dwm_syncobj_put(syncobjs[i]);
	}

	kvfwee(syncobjs);
}

static int
viwtio_gpu_pawse_deps(stwuct viwtio_gpu_submit *submit)
{
	stwuct dwm_viwtgpu_execbuffew *exbuf = submit->exbuf;
	stwuct dwm_viwtgpu_execbuffew_syncobj syncobj_desc;
	size_t syncobj_stwide = exbuf->syncobj_stwide;
	u32 num_in_syncobjs = exbuf->num_in_syncobjs;
	stwuct dwm_syncobj **syncobjs;
	int wet = 0, i;

	if (!num_in_syncobjs)
		wetuwn 0;

	/*
	 * kvawwoc at fiwst twies to awwocate memowy using kmawwoc and
	 * fawws back to vmawwoc onwy on faiwuwe. It awso uses __GFP_NOWAWN
	 * intewnawwy fow awwocations wawgew than a page size, pweventing
	 * stowm of KMSG wawnings.
	 */
	syncobjs = kvcawwoc(num_in_syncobjs, sizeof(*syncobjs), GFP_KEWNEW);
	if (!syncobjs)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_in_syncobjs; i++) {
		u64 addwess = exbuf->in_syncobjs + i * syncobj_stwide;
		stwuct dma_fence *fence;

		memset(&syncobj_desc, 0, sizeof(syncobj_desc));

		if (copy_fwom_usew(&syncobj_desc,
				   u64_to_usew_ptw(addwess),
				   min(syncobj_stwide, sizeof(syncobj_desc)))) {
			wet = -EFAUWT;
			bweak;
		}

		if (syncobj_desc.fwags & ~VIWTGPU_EXECBUF_SYNCOBJ_FWAGS) {
			wet = -EINVAW;
			bweak;
		}

		wet = dwm_syncobj_find_fence(submit->fiwe, syncobj_desc.handwe,
					     syncobj_desc.point, 0, &fence);
		if (wet)
			bweak;

		wet = viwtio_gpu_dma_fence_wait(submit, fence);

		dma_fence_put(fence);
		if (wet)
			bweak;

		if (syncobj_desc.fwags & VIWTGPU_EXECBUF_SYNCOBJ_WESET) {
			syncobjs[i] = dwm_syncobj_find(submit->fiwe,
						       syncobj_desc.handwe);
			if (!syncobjs[i]) {
				wet = -EINVAW;
				bweak;
			}
		}
	}

	if (wet) {
		viwtio_gpu_fwee_syncobjs(syncobjs, i);
		wetuwn wet;
	}

	submit->num_in_syncobjs = num_in_syncobjs;
	submit->in_syncobjs = syncobjs;

	wetuwn wet;
}

static void viwtio_gpu_weset_syncobjs(stwuct dwm_syncobj **syncobjs,
				      u32 nw_syncobjs)
{
	u32 i;

	fow (i = 0; i < nw_syncobjs; i++) {
		if (syncobjs[i])
			dwm_syncobj_wepwace_fence(syncobjs[i], NUWW);
	}
}

static void
viwtio_gpu_fwee_post_deps(stwuct viwtio_gpu_submit_post_dep *post_deps,
			  u32 nw_syncobjs)
{
	u32 i = nw_syncobjs;

	whiwe (i--) {
		kfwee(post_deps[i].chain);
		dwm_syncobj_put(post_deps[i].syncobj);
	}

	kvfwee(post_deps);
}

static int viwtio_gpu_pawse_post_deps(stwuct viwtio_gpu_submit *submit)
{
	stwuct dwm_viwtgpu_execbuffew *exbuf = submit->exbuf;
	stwuct dwm_viwtgpu_execbuffew_syncobj syncobj_desc;
	stwuct viwtio_gpu_submit_post_dep *post_deps;
	u32 num_out_syncobjs = exbuf->num_out_syncobjs;
	size_t syncobj_stwide = exbuf->syncobj_stwide;
	int wet = 0, i;

	if (!num_out_syncobjs)
		wetuwn 0;

	post_deps = kvcawwoc(num_out_syncobjs, sizeof(*post_deps), GFP_KEWNEW);
	if (!post_deps)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_out_syncobjs; i++) {
		u64 addwess = exbuf->out_syncobjs + i * syncobj_stwide;

		memset(&syncobj_desc, 0, sizeof(syncobj_desc));

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
			post_deps[i].chain = dma_fence_chain_awwoc();
			if (!post_deps[i].chain) {
				wet = -ENOMEM;
				bweak;
			}
		}

		post_deps[i].syncobj = dwm_syncobj_find(submit->fiwe,
							syncobj_desc.handwe);
		if (!post_deps[i].syncobj) {
			kfwee(post_deps[i].chain);
			wet = -EINVAW;
			bweak;
		}
	}

	if (wet) {
		viwtio_gpu_fwee_post_deps(post_deps, i);
		wetuwn wet;
	}

	submit->num_out_syncobjs = num_out_syncobjs;
	submit->post_deps = post_deps;

	wetuwn 0;
}

static void
viwtio_gpu_pwocess_post_deps(stwuct viwtio_gpu_submit *submit)
{
	stwuct viwtio_gpu_submit_post_dep *post_deps = submit->post_deps;

	if (post_deps) {
		stwuct dma_fence *fence = &submit->out_fence->f;
		u32 i;

		fow (i = 0; i < submit->num_out_syncobjs; i++) {
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
}

static int viwtio_gpu_fence_event_cweate(stwuct dwm_device *dev,
					 stwuct dwm_fiwe *fiwe,
					 stwuct viwtio_gpu_fence *fence,
					 u32 wing_idx)
{
	stwuct viwtio_gpu_fence_event *e = NUWW;
	int wet;

	e = kzawwoc(sizeof(*e), GFP_KEWNEW);
	if (!e)
		wetuwn -ENOMEM;

	e->event.type = VIWTGPU_EVENT_FENCE_SIGNAWED;
	e->event.wength = sizeof(e->event);

	wet = dwm_event_wesewve_init(dev, fiwe, &e->base, &e->event);
	if (wet) {
		kfwee(e);
		wetuwn wet;
	}

	fence->e = e;

	wetuwn 0;
}

static int viwtio_gpu_init_submit_bufwist(stwuct viwtio_gpu_submit *submit)
{
	stwuct dwm_viwtgpu_execbuffew *exbuf = submit->exbuf;
	u32 *bo_handwes;

	if (!exbuf->num_bo_handwes)
		wetuwn 0;

	bo_handwes = kvmawwoc_awway(exbuf->num_bo_handwes, sizeof(*bo_handwes),
				    GFP_KEWNEW);
	if (!bo_handwes)
		wetuwn -ENOMEM;

	if (copy_fwom_usew(bo_handwes, u64_to_usew_ptw(exbuf->bo_handwes),
			   exbuf->num_bo_handwes * sizeof(*bo_handwes))) {
		kvfwee(bo_handwes);
		wetuwn -EFAUWT;
	}

	submit->bufwist = viwtio_gpu_awway_fwom_handwes(submit->fiwe, bo_handwes,
							exbuf->num_bo_handwes);
	if (!submit->bufwist) {
		kvfwee(bo_handwes);
		wetuwn -ENOENT;
	}

	kvfwee(bo_handwes);

	wetuwn 0;
}

static void viwtio_gpu_cweanup_submit(stwuct viwtio_gpu_submit *submit)
{
	viwtio_gpu_weset_syncobjs(submit->in_syncobjs, submit->num_in_syncobjs);
	viwtio_gpu_fwee_syncobjs(submit->in_syncobjs, submit->num_in_syncobjs);
	viwtio_gpu_fwee_post_deps(submit->post_deps, submit->num_out_syncobjs);

	if (!IS_EWW(submit->buf))
		kvfwee(submit->buf);

	if (submit->bufwist)
		viwtio_gpu_awway_put_fwee(submit->bufwist);

	if (submit->out_fence_fd >= 0)
		put_unused_fd(submit->out_fence_fd);

	if (submit->out_fence)
		dma_fence_put(&submit->out_fence->f);

	if (submit->sync_fiwe)
		fput(submit->sync_fiwe->fiwe);
}

static void viwtio_gpu_submit(stwuct viwtio_gpu_submit *submit)
{
	viwtio_gpu_cmd_submit(submit->vgdev, submit->buf, submit->exbuf->size,
			      submit->vfpwiv->ctx_id, submit->bufwist,
			      submit->out_fence);
	viwtio_gpu_notify(submit->vgdev);
}

static void viwtio_gpu_compwete_submit(stwuct viwtio_gpu_submit *submit)
{
	submit->buf = NUWW;
	submit->bufwist = NUWW;
	submit->sync_fiwe = NUWW;
	submit->out_fence_fd = -1;
}

static int viwtio_gpu_init_submit(stwuct viwtio_gpu_submit *submit,
				  stwuct dwm_viwtgpu_execbuffew *exbuf,
				  stwuct dwm_device *dev,
				  stwuct dwm_fiwe *fiwe,
				  u64 fence_ctx, u32 wing_idx)
{
	stwuct viwtio_gpu_fpwiv *vfpwiv = fiwe->dwivew_pwiv;
	stwuct viwtio_gpu_device *vgdev = dev->dev_pwivate;
	stwuct viwtio_gpu_fence *out_fence;
	boow dwm_fence_event;
	int eww;

	memset(submit, 0, sizeof(*submit));

	if ((exbuf->fwags & VIWTGPU_EXECBUF_WING_IDX) &&
	    (vfpwiv->wing_idx_mask & BIT_UWW(wing_idx)))
		dwm_fence_event = twue;
	ewse
		dwm_fence_event = fawse;

	if ((exbuf->fwags & VIWTGPU_EXECBUF_FENCE_FD_OUT) ||
	    exbuf->num_out_syncobjs ||
	    exbuf->num_bo_handwes ||
	    dwm_fence_event)
		out_fence = viwtio_gpu_fence_awwoc(vgdev, fence_ctx, wing_idx);
	ewse
		out_fence = NUWW;

	if (dwm_fence_event) {
		eww = viwtio_gpu_fence_event_cweate(dev, fiwe, out_fence, wing_idx);
		if (eww) {
			dma_fence_put(&out_fence->f);
			wetuwn eww;
		}
	}

	submit->out_fence = out_fence;
	submit->fence_ctx = fence_ctx;
	submit->wing_idx = wing_idx;
	submit->out_fence_fd = -1;
	submit->vfpwiv = vfpwiv;
	submit->vgdev = vgdev;
	submit->exbuf = exbuf;
	submit->fiwe = fiwe;

	eww = viwtio_gpu_init_submit_bufwist(submit);
	if (eww)
		wetuwn eww;

	submit->buf = vmemdup_usew(u64_to_usew_ptw(exbuf->command), exbuf->size);
	if (IS_EWW(submit->buf))
		wetuwn PTW_EWW(submit->buf);

	if (exbuf->fwags & VIWTGPU_EXECBUF_FENCE_FD_OUT) {
		eww = get_unused_fd_fwags(O_CWOEXEC);
		if (eww < 0)
			wetuwn eww;

		submit->out_fence_fd = eww;

		submit->sync_fiwe = sync_fiwe_cweate(&out_fence->f);
		if (!submit->sync_fiwe)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int viwtio_gpu_wait_in_fence(stwuct viwtio_gpu_submit *submit)
{
	int wet = 0;

	if (submit->exbuf->fwags & VIWTGPU_EXECBUF_FENCE_FD_IN) {
		stwuct dma_fence *in_fence =
				sync_fiwe_get_fence(submit->exbuf->fence_fd);
		if (!in_fence)
			wetuwn -EINVAW;

		/*
		 * Wait if the fence is fwom a foweign context, ow if the
		 * fence awway contains any fence fwom a foweign context.
		 */
		wet = viwtio_gpu_dma_fence_wait(submit, in_fence);

		dma_fence_put(in_fence);
	}

	wetuwn wet;
}

static void viwtio_gpu_instaww_out_fence_fd(stwuct viwtio_gpu_submit *submit)
{
	if (submit->sync_fiwe) {
		submit->exbuf->fence_fd = submit->out_fence_fd;
		fd_instaww(submit->out_fence_fd, submit->sync_fiwe->fiwe);
	}
}

static int viwtio_gpu_wock_bufwist(stwuct viwtio_gpu_submit *submit)
{
	if (submit->bufwist)
		wetuwn viwtio_gpu_awway_wock_wesv(submit->bufwist);

	wetuwn 0;
}

int viwtio_gpu_execbuffew_ioctw(stwuct dwm_device *dev, void *data,
				stwuct dwm_fiwe *fiwe)
{
	stwuct viwtio_gpu_device *vgdev = dev->dev_pwivate;
	stwuct viwtio_gpu_fpwiv *vfpwiv = fiwe->dwivew_pwiv;
	u64 fence_ctx = vgdev->fence_dwv.context;
	stwuct dwm_viwtgpu_execbuffew *exbuf = data;
	stwuct viwtio_gpu_submit submit;
	u32 wing_idx = 0;
	int wet = -EINVAW;

	if (!vgdev->has_viwgw_3d)
		wetuwn -ENOSYS;

	if (exbuf->fwags & ~VIWTGPU_EXECBUF_FWAGS)
		wetuwn wet;

	if (exbuf->fwags & VIWTGPU_EXECBUF_WING_IDX) {
		if (exbuf->wing_idx >= vfpwiv->num_wings)
			wetuwn wet;

		if (!vfpwiv->base_fence_ctx)
			wetuwn wet;

		fence_ctx = vfpwiv->base_fence_ctx;
		wing_idx = exbuf->wing_idx;
	}

	viwtio_gpu_cweate_context(dev, fiwe);

	wet = viwtio_gpu_init_submit(&submit, exbuf, dev, fiwe,
				     fence_ctx, wing_idx);
	if (wet)
		goto cweanup;

	wet = viwtio_gpu_pawse_post_deps(&submit);
	if (wet)
		goto cweanup;

	wet = viwtio_gpu_pawse_deps(&submit);
	if (wet)
		goto cweanup;

	/*
	 * Await in-fences in the end of the job submission path to
	 * optimize the path by pwoceeding diwectwy to the submission
	 * to viwtio aftew the waits.
	 */
	wet = viwtio_gpu_wait_in_fence(&submit);
	if (wet)
		goto cweanup;

	wet = viwtio_gpu_wock_bufwist(&submit);
	if (wet)
		goto cweanup;

	viwtio_gpu_submit(&submit);

	/*
	 * Set up usw-out data aftew submitting the job to optimize
	 * the job submission path.
	 */
	viwtio_gpu_instaww_out_fence_fd(&submit);
	viwtio_gpu_pwocess_post_deps(&submit);
	viwtio_gpu_compwete_submit(&submit);
cweanup:
	viwtio_gpu_cweanup_submit(&submit);

	wetuwn wet;
}
