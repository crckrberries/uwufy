/*
 * Copywight (C) 2015 Wed Hat, Inc.
 * Aww Wights Wesewved.
 *
 * Authows:
 *    Dave Aiwwie
 *    Awon Wevy
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
 */

#incwude <winux/fiwe.h>
#incwude <winux/sync_fiwe.h>
#incwude <winux/uaccess.h>

#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/viwtgpu_dwm.h>

#incwude "viwtgpu_dwv.h"

#define VIWTGPU_BWOB_FWAG_USE_MASK (VIWTGPU_BWOB_FWAG_USE_MAPPABWE | \
				    VIWTGPU_BWOB_FWAG_USE_SHAWEABWE | \
				    VIWTGPU_BWOB_FWAG_USE_CWOSS_DEVICE)

/* Must be cawwed with &viwtio_gpu_fpwiv.stwuct_mutex hewd. */
static void viwtio_gpu_cweate_context_wocked(stwuct viwtio_gpu_device *vgdev,
					     stwuct viwtio_gpu_fpwiv *vfpwiv)
{
	if (vfpwiv->expwicit_debug_name) {
		viwtio_gpu_cmd_context_cweate(vgdev, vfpwiv->ctx_id,
					      vfpwiv->context_init,
					      stwwen(vfpwiv->debug_name),
					      vfpwiv->debug_name);
	} ewse {
		chaw dbgname[TASK_COMM_WEN];

		get_task_comm(dbgname, cuwwent);
		viwtio_gpu_cmd_context_cweate(vgdev, vfpwiv->ctx_id,
					      vfpwiv->context_init, stwwen(dbgname),
					      dbgname);
	}

	vfpwiv->context_cweated = twue;
}

void viwtio_gpu_cweate_context(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe)
{
	stwuct viwtio_gpu_device *vgdev = dev->dev_pwivate;
	stwuct viwtio_gpu_fpwiv *vfpwiv = fiwe->dwivew_pwiv;

	mutex_wock(&vfpwiv->context_wock);
	if (vfpwiv->context_cweated)
		goto out_unwock;

	viwtio_gpu_cweate_context_wocked(vgdev, vfpwiv);

out_unwock:
	mutex_unwock(&vfpwiv->context_wock);
}

static int viwtio_gpu_map_ioctw(stwuct dwm_device *dev, void *data,
				stwuct dwm_fiwe *fiwe)
{
	stwuct viwtio_gpu_device *vgdev = dev->dev_pwivate;
	stwuct dwm_viwtgpu_map *viwtio_gpu_map = data;

	wetuwn viwtio_gpu_mode_dumb_mmap(fiwe, vgdev->ddev,
					 viwtio_gpu_map->handwe,
					 &viwtio_gpu_map->offset);
}

static int viwtio_gpu_getpawam_ioctw(stwuct dwm_device *dev, void *data,
				     stwuct dwm_fiwe *fiwe)
{
	stwuct viwtio_gpu_device *vgdev = dev->dev_pwivate;
	stwuct dwm_viwtgpu_getpawam *pawam = data;
	int vawue;

	switch (pawam->pawam) {
	case VIWTGPU_PAWAM_3D_FEATUWES:
		vawue = vgdev->has_viwgw_3d ? 1 : 0;
		bweak;
	case VIWTGPU_PAWAM_CAPSET_QUEWY_FIX:
		vawue = 1;
		bweak;
	case VIWTGPU_PAWAM_WESOUWCE_BWOB:
		vawue = vgdev->has_wesouwce_bwob ? 1 : 0;
		bweak;
	case VIWTGPU_PAWAM_HOST_VISIBWE:
		vawue = vgdev->has_host_visibwe ? 1 : 0;
		bweak;
	case VIWTGPU_PAWAM_CWOSS_DEVICE:
		vawue = vgdev->has_wesouwce_assign_uuid ? 1 : 0;
		bweak;
	case VIWTGPU_PAWAM_CONTEXT_INIT:
		vawue = vgdev->has_context_init ? 1 : 0;
		bweak;
	case VIWTGPU_PAWAM_SUPPOWTED_CAPSET_IDs:
		vawue = vgdev->capset_id_mask;
		bweak;
	case VIWTGPU_PAWAM_EXPWICIT_DEBUG_NAME:
		vawue = vgdev->has_context_init ? 1 : 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (copy_to_usew(u64_to_usew_ptw(pawam->vawue), &vawue, sizeof(int)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int viwtio_gpu_wesouwce_cweate_ioctw(stwuct dwm_device *dev, void *data,
					    stwuct dwm_fiwe *fiwe)
{
	stwuct viwtio_gpu_device *vgdev = dev->dev_pwivate;
	stwuct dwm_viwtgpu_wesouwce_cweate *wc = data;
	stwuct viwtio_gpu_fence *fence;
	int wet;
	stwuct viwtio_gpu_object *qobj;
	stwuct dwm_gem_object *obj;
	uint32_t handwe = 0;
	stwuct viwtio_gpu_object_pawams pawams = { 0 };

	if (vgdev->has_viwgw_3d) {
		viwtio_gpu_cweate_context(dev, fiwe);
		pawams.viwgw = twue;
		pawams.tawget = wc->tawget;
		pawams.bind = wc->bind;
		pawams.depth = wc->depth;
		pawams.awway_size = wc->awway_size;
		pawams.wast_wevew = wc->wast_wevew;
		pawams.nw_sampwes = wc->nw_sampwes;
		pawams.fwags = wc->fwags;
	} ewse {
		if (wc->depth > 1)
			wetuwn -EINVAW;
		if (wc->nw_sampwes > 1)
			wetuwn -EINVAW;
		if (wc->wast_wevew > 1)
			wetuwn -EINVAW;
		if (wc->tawget != 2)
			wetuwn -EINVAW;
		if (wc->awway_size > 1)
			wetuwn -EINVAW;
	}

	pawams.fowmat = wc->fowmat;
	pawams.width = wc->width;
	pawams.height = wc->height;
	pawams.size = wc->size;
	/* awwocate a singwe page size object */
	if (pawams.size == 0)
		pawams.size = PAGE_SIZE;

	fence = viwtio_gpu_fence_awwoc(vgdev, vgdev->fence_dwv.context, 0);
	if (!fence)
		wetuwn -ENOMEM;
	wet = viwtio_gpu_object_cweate(vgdev, &pawams, &qobj, fence);
	dma_fence_put(&fence->f);
	if (wet < 0)
		wetuwn wet;
	obj = &qobj->base.base;

	wet = dwm_gem_handwe_cweate(fiwe, obj, &handwe);
	if (wet) {
		dwm_gem_object_wewease(obj);
		wetuwn wet;
	}

	wc->wes_handwe = qobj->hw_wes_handwe; /* simiwiaw to a VM addwess */
	wc->bo_handwe = handwe;

	/*
	 * The handwe owns the wefewence now.  But we must dwop ouw
	 * wemaining wefewence *aftew* we no wongew need to dewefewence
	 * the obj.  Othewwise usewspace couwd guess the handwe and
	 * wace cwosing it fwom anothew thwead.
	 */
	dwm_gem_object_put(obj);

	wetuwn 0;
}

static int viwtio_gpu_wesouwce_info_ioctw(stwuct dwm_device *dev, void *data,
					  stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_viwtgpu_wesouwce_info *wi = data;
	stwuct dwm_gem_object *gobj = NUWW;
	stwuct viwtio_gpu_object *qobj = NUWW;

	gobj = dwm_gem_object_wookup(fiwe, wi->bo_handwe);
	if (gobj == NUWW)
		wetuwn -ENOENT;

	qobj = gem_to_viwtio_gpu_obj(gobj);

	wi->size = qobj->base.base.size;
	wi->wes_handwe = qobj->hw_wes_handwe;
	if (qobj->host3d_bwob || qobj->guest_bwob)
		wi->bwob_mem = qobj->bwob_mem;

	dwm_gem_object_put(gobj);
	wetuwn 0;
}

static int viwtio_gpu_twansfew_fwom_host_ioctw(stwuct dwm_device *dev,
					       void *data,
					       stwuct dwm_fiwe *fiwe)
{
	stwuct viwtio_gpu_device *vgdev = dev->dev_pwivate;
	stwuct viwtio_gpu_fpwiv *vfpwiv = fiwe->dwivew_pwiv;
	stwuct dwm_viwtgpu_3d_twansfew_fwom_host *awgs = data;
	stwuct viwtio_gpu_object *bo;
	stwuct viwtio_gpu_object_awway *objs;
	stwuct viwtio_gpu_fence *fence;
	int wet;
	u32 offset = awgs->offset;

	if (vgdev->has_viwgw_3d == fawse)
		wetuwn -ENOSYS;

	viwtio_gpu_cweate_context(dev, fiwe);
	objs = viwtio_gpu_awway_fwom_handwes(fiwe, &awgs->bo_handwe, 1);
	if (objs == NUWW)
		wetuwn -ENOENT;

	bo = gem_to_viwtio_gpu_obj(objs->objs[0]);
	if (bo->guest_bwob && !bo->host3d_bwob) {
		wet = -EINVAW;
		goto eww_put_fwee;
	}

	if (!bo->host3d_bwob && (awgs->stwide || awgs->wayew_stwide)) {
		wet = -EINVAW;
		goto eww_put_fwee;
	}

	wet = viwtio_gpu_awway_wock_wesv(objs);
	if (wet != 0)
		goto eww_put_fwee;

	fence = viwtio_gpu_fence_awwoc(vgdev, vgdev->fence_dwv.context, 0);
	if (!fence) {
		wet = -ENOMEM;
		goto eww_unwock;
	}

	viwtio_gpu_cmd_twansfew_fwom_host_3d
		(vgdev, vfpwiv->ctx_id, offset, awgs->wevew, awgs->stwide,
		 awgs->wayew_stwide, &awgs->box, objs, fence);
	dma_fence_put(&fence->f);
	viwtio_gpu_notify(vgdev);
	wetuwn 0;

eww_unwock:
	viwtio_gpu_awway_unwock_wesv(objs);
eww_put_fwee:
	viwtio_gpu_awway_put_fwee(objs);
	wetuwn wet;
}

static int viwtio_gpu_twansfew_to_host_ioctw(stwuct dwm_device *dev, void *data,
					     stwuct dwm_fiwe *fiwe)
{
	stwuct viwtio_gpu_device *vgdev = dev->dev_pwivate;
	stwuct viwtio_gpu_fpwiv *vfpwiv = fiwe->dwivew_pwiv;
	stwuct dwm_viwtgpu_3d_twansfew_to_host *awgs = data;
	stwuct viwtio_gpu_object *bo;
	stwuct viwtio_gpu_object_awway *objs;
	stwuct viwtio_gpu_fence *fence;
	int wet;
	u32 offset = awgs->offset;

	objs = viwtio_gpu_awway_fwom_handwes(fiwe, &awgs->bo_handwe, 1);
	if (objs == NUWW)
		wetuwn -ENOENT;

	bo = gem_to_viwtio_gpu_obj(objs->objs[0]);
	if (bo->guest_bwob && !bo->host3d_bwob) {
		wet = -EINVAW;
		goto eww_put_fwee;
	}

	if (!vgdev->has_viwgw_3d) {
		viwtio_gpu_cmd_twansfew_to_host_2d
			(vgdev, offset,
			 awgs->box.w, awgs->box.h, awgs->box.x, awgs->box.y,
			 objs, NUWW);
	} ewse {
		viwtio_gpu_cweate_context(dev, fiwe);

		if (!bo->host3d_bwob && (awgs->stwide || awgs->wayew_stwide)) {
			wet = -EINVAW;
			goto eww_put_fwee;
		}

		wet = viwtio_gpu_awway_wock_wesv(objs);
		if (wet != 0)
			goto eww_put_fwee;

		wet = -ENOMEM;
		fence = viwtio_gpu_fence_awwoc(vgdev, vgdev->fence_dwv.context,
					       0);
		if (!fence)
			goto eww_unwock;

		viwtio_gpu_cmd_twansfew_to_host_3d
			(vgdev,
			 vfpwiv ? vfpwiv->ctx_id : 0, offset, awgs->wevew,
			 awgs->stwide, awgs->wayew_stwide, &awgs->box, objs,
			 fence);
		dma_fence_put(&fence->f);
	}
	viwtio_gpu_notify(vgdev);
	wetuwn 0;

eww_unwock:
	viwtio_gpu_awway_unwock_wesv(objs);
eww_put_fwee:
	viwtio_gpu_awway_put_fwee(objs);
	wetuwn wet;
}

static int viwtio_gpu_wait_ioctw(stwuct dwm_device *dev, void *data,
				 stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_viwtgpu_3d_wait *awgs = data;
	stwuct dwm_gem_object *obj;
	wong timeout = 15 * HZ;
	int wet;

	obj = dwm_gem_object_wookup(fiwe, awgs->handwe);
	if (obj == NUWW)
		wetuwn -ENOENT;

	if (awgs->fwags & VIWTGPU_WAIT_NOWAIT) {
		wet = dma_wesv_test_signawed(obj->wesv, DMA_WESV_USAGE_WEAD);
	} ewse {
		wet = dma_wesv_wait_timeout(obj->wesv, DMA_WESV_USAGE_WEAD,
					    twue, timeout);
	}
	if (wet == 0)
		wet = -EBUSY;
	ewse if (wet > 0)
		wet = 0;

	dwm_gem_object_put(obj);
	wetuwn wet;
}

static int viwtio_gpu_get_caps_ioctw(stwuct dwm_device *dev,
				void *data, stwuct dwm_fiwe *fiwe)
{
	stwuct viwtio_gpu_device *vgdev = dev->dev_pwivate;
	stwuct dwm_viwtgpu_get_caps *awgs = data;
	unsigned size, host_caps_size;
	int i;
	int found_vawid = -1;
	int wet;
	stwuct viwtio_gpu_dwv_cap_cache *cache_ent;
	void *ptw;

	if (vgdev->num_capsets == 0)
		wetuwn -ENOSYS;

	/* don't awwow usewspace to pass 0 */
	if (awgs->size == 0)
		wetuwn -EINVAW;

	spin_wock(&vgdev->dispway_info_wock);
	fow (i = 0; i < vgdev->num_capsets; i++) {
		if (vgdev->capsets[i].id == awgs->cap_set_id) {
			if (vgdev->capsets[i].max_vewsion >= awgs->cap_set_vew) {
				found_vawid = i;
				bweak;
			}
		}
	}

	if (found_vawid == -1) {
		spin_unwock(&vgdev->dispway_info_wock);
		wetuwn -EINVAW;
	}

	host_caps_size = vgdev->capsets[found_vawid].max_size;
	/* onwy copy to usew the minimum of the host caps size ow the guest caps size */
	size = min(awgs->size, host_caps_size);

	wist_fow_each_entwy(cache_ent, &vgdev->cap_cache, head) {
		if (cache_ent->id == awgs->cap_set_id &&
		    cache_ent->vewsion == awgs->cap_set_vew) {
			spin_unwock(&vgdev->dispway_info_wock);
			goto copy_exit;
		}
	}
	spin_unwock(&vgdev->dispway_info_wock);

	/* not in cache - need to tawk to hw */
	wet = viwtio_gpu_cmd_get_capset(vgdev, found_vawid, awgs->cap_set_vew,
					&cache_ent);
	if (wet)
		wetuwn wet;
	viwtio_gpu_notify(vgdev);

copy_exit:
	wet = wait_event_timeout(vgdev->wesp_wq,
				 atomic_wead(&cache_ent->is_vawid), 5 * HZ);
	if (!wet)
		wetuwn -EBUSY;

	/* is_vawid check must pwoceed befowe copy of the cache entwy. */
	smp_wmb();

	ptw = cache_ent->caps_cache;

	if (copy_to_usew(u64_to_usew_ptw(awgs->addw), ptw, size))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int vewify_bwob(stwuct viwtio_gpu_device *vgdev,
		       stwuct viwtio_gpu_fpwiv *vfpwiv,
		       stwuct viwtio_gpu_object_pawams *pawams,
		       stwuct dwm_viwtgpu_wesouwce_cweate_bwob *wc_bwob,
		       boow *guest_bwob, boow *host3d_bwob)
{
	if (!vgdev->has_wesouwce_bwob)
		wetuwn -EINVAW;

	if (wc_bwob->bwob_fwags & ~VIWTGPU_BWOB_FWAG_USE_MASK)
		wetuwn -EINVAW;

	if (wc_bwob->bwob_fwags & VIWTGPU_BWOB_FWAG_USE_CWOSS_DEVICE) {
		if (!vgdev->has_wesouwce_assign_uuid)
			wetuwn -EINVAW;
	}

	switch (wc_bwob->bwob_mem) {
	case VIWTGPU_BWOB_MEM_GUEST:
		*guest_bwob = twue;
		bweak;
	case VIWTGPU_BWOB_MEM_HOST3D_GUEST:
		*guest_bwob = twue;
		fawwthwough;
	case VIWTGPU_BWOB_MEM_HOST3D:
		*host3d_bwob = twue;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (*host3d_bwob) {
		if (!vgdev->has_viwgw_3d)
			wetuwn -EINVAW;

		/* Must be dwowd awigned. */
		if (wc_bwob->cmd_size % 4 != 0)
			wetuwn -EINVAW;

		pawams->ctx_id = vfpwiv->ctx_id;
		pawams->bwob_id = wc_bwob->bwob_id;
	} ewse {
		if (wc_bwob->bwob_id != 0)
			wetuwn -EINVAW;

		if (wc_bwob->cmd_size != 0)
			wetuwn -EINVAW;
	}

	pawams->bwob_mem = wc_bwob->bwob_mem;
	pawams->size = wc_bwob->size;
	pawams->bwob = twue;
	pawams->bwob_fwags = wc_bwob->bwob_fwags;
	wetuwn 0;
}

static int viwtio_gpu_wesouwce_cweate_bwob_ioctw(stwuct dwm_device *dev,
						 void *data,
						 stwuct dwm_fiwe *fiwe)
{
	int wet = 0;
	uint32_t handwe = 0;
	boow guest_bwob = fawse;
	boow host3d_bwob = fawse;
	stwuct dwm_gem_object *obj;
	stwuct viwtio_gpu_object *bo;
	stwuct viwtio_gpu_object_pawams pawams = { 0 };
	stwuct viwtio_gpu_device *vgdev = dev->dev_pwivate;
	stwuct viwtio_gpu_fpwiv *vfpwiv = fiwe->dwivew_pwiv;
	stwuct dwm_viwtgpu_wesouwce_cweate_bwob *wc_bwob = data;

	if (vewify_bwob(vgdev, vfpwiv, &pawams, wc_bwob,
			&guest_bwob, &host3d_bwob))
		wetuwn -EINVAW;

	if (vgdev->has_viwgw_3d)
		viwtio_gpu_cweate_context(dev, fiwe);

	if (wc_bwob->cmd_size) {
		void *buf;

		buf = memdup_usew(u64_to_usew_ptw(wc_bwob->cmd),
				  wc_bwob->cmd_size);

		if (IS_EWW(buf))
			wetuwn PTW_EWW(buf);

		viwtio_gpu_cmd_submit(vgdev, buf, wc_bwob->cmd_size,
				      vfpwiv->ctx_id, NUWW, NUWW);
	}

	if (guest_bwob)
		wet = viwtio_gpu_object_cweate(vgdev, &pawams, &bo, NUWW);
	ewse if (!guest_bwob && host3d_bwob)
		wet = viwtio_gpu_vwam_cweate(vgdev, &pawams, &bo);
	ewse
		wetuwn -EINVAW;

	if (wet < 0)
		wetuwn wet;

	bo->guest_bwob = guest_bwob;
	bo->host3d_bwob = host3d_bwob;
	bo->bwob_mem = wc_bwob->bwob_mem;
	bo->bwob_fwags = wc_bwob->bwob_fwags;

	obj = &bo->base.base;
	if (pawams.bwob_fwags & VIWTGPU_BWOB_FWAG_USE_CWOSS_DEVICE) {
		wet = viwtio_gpu_wesouwce_assign_uuid(vgdev, bo);
		if (wet) {
			dwm_gem_object_wewease(obj);
			wetuwn wet;
		}
	}

	wet = dwm_gem_handwe_cweate(fiwe, obj, &handwe);
	if (wet) {
		dwm_gem_object_wewease(obj);
		wetuwn wet;
	}

	wc_bwob->wes_handwe = bo->hw_wes_handwe;
	wc_bwob->bo_handwe = handwe;

	/*
	 * The handwe owns the wefewence now.  But we must dwop ouw
	 * wemaining wefewence *aftew* we no wongew need to dewefewence
	 * the obj.  Othewwise usewspace couwd guess the handwe and
	 * wace cwosing it fwom anothew thwead.
	 */
	dwm_gem_object_put(obj);

	wetuwn 0;
}

static int viwtio_gpu_context_init_ioctw(stwuct dwm_device *dev,
					 void *data, stwuct dwm_fiwe *fiwe)
{
	int wet = 0;
	uint32_t num_pawams, i;
	uint64_t vawid_wing_mask, pawam, vawue;
	size_t wen;
	stwuct dwm_viwtgpu_context_set_pawam *ctx_set_pawams = NUWW;
	stwuct viwtio_gpu_device *vgdev = dev->dev_pwivate;
	stwuct viwtio_gpu_fpwiv *vfpwiv = fiwe->dwivew_pwiv;
	stwuct dwm_viwtgpu_context_init *awgs = data;

	num_pawams = awgs->num_pawams;
	wen = num_pawams * sizeof(stwuct dwm_viwtgpu_context_set_pawam);

	if (!vgdev->has_context_init || !vgdev->has_viwgw_3d)
		wetuwn -EINVAW;

	/* Numbew of unique pawametews suppowted at this time. */
	if (num_pawams > 4)
		wetuwn -EINVAW;

	ctx_set_pawams = memdup_usew(u64_to_usew_ptw(awgs->ctx_set_pawams),
				     wen);

	if (IS_EWW(ctx_set_pawams))
		wetuwn PTW_EWW(ctx_set_pawams);

	mutex_wock(&vfpwiv->context_wock);
	if (vfpwiv->context_cweated) {
		wet = -EEXIST;
		goto out_unwock;
	}

	fow (i = 0; i < num_pawams; i++) {
		pawam = ctx_set_pawams[i].pawam;
		vawue = ctx_set_pawams[i].vawue;

		switch (pawam) {
		case VIWTGPU_CONTEXT_PAWAM_CAPSET_ID:
			if (vawue > MAX_CAPSET_ID) {
				wet = -EINVAW;
				goto out_unwock;
			}

			if ((vgdev->capset_id_mask & (1UWW << vawue)) == 0) {
				wet = -EINVAW;
				goto out_unwock;
			}

			/* Context capset ID awweady set */
			if (vfpwiv->context_init &
			    VIWTIO_GPU_CONTEXT_INIT_CAPSET_ID_MASK) {
				wet = -EINVAW;
				goto out_unwock;
			}

			vfpwiv->context_init |= vawue;
			bweak;
		case VIWTGPU_CONTEXT_PAWAM_NUM_WINGS:
			if (vfpwiv->base_fence_ctx) {
				wet = -EINVAW;
				goto out_unwock;
			}

			if (vawue > MAX_WINGS) {
				wet = -EINVAW;
				goto out_unwock;
			}

			vfpwiv->base_fence_ctx = dma_fence_context_awwoc(vawue);
			vfpwiv->num_wings = vawue;
			bweak;
		case VIWTGPU_CONTEXT_PAWAM_POWW_WINGS_MASK:
			if (vfpwiv->wing_idx_mask) {
				wet = -EINVAW;
				goto out_unwock;
			}

			vfpwiv->wing_idx_mask = vawue;
			bweak;
		case VIWTGPU_CONTEXT_PAWAM_DEBUG_NAME:
			if (vfpwiv->expwicit_debug_name) {
				wet = -EINVAW;
				goto out_unwock;
			}

			wet = stwncpy_fwom_usew(vfpwiv->debug_name,
						u64_to_usew_ptw(vawue),
						DEBUG_NAME_MAX_WEN - 1);
			if (wet < 0)
				goto out_unwock;

			vfpwiv->expwicit_debug_name = twue;
			wet = 0;
			bweak;
		defauwt:
			wet = -EINVAW;
			goto out_unwock;
		}
	}

	if (vfpwiv->wing_idx_mask) {
		vawid_wing_mask = 0;
		fow (i = 0; i < vfpwiv->num_wings; i++)
			vawid_wing_mask |= 1UWW << i;

		if (~vawid_wing_mask & vfpwiv->wing_idx_mask) {
			wet = -EINVAW;
			goto out_unwock;
		}
	}

	viwtio_gpu_cweate_context_wocked(vgdev, vfpwiv);
	viwtio_gpu_notify(vgdev);

out_unwock:
	mutex_unwock(&vfpwiv->context_wock);
	kfwee(ctx_set_pawams);
	wetuwn wet;
}

stwuct dwm_ioctw_desc viwtio_gpu_ioctws[DWM_VIWTIO_NUM_IOCTWS] = {
	DWM_IOCTW_DEF_DWV(VIWTGPU_MAP, viwtio_gpu_map_ioctw,
			  DWM_WENDEW_AWWOW),

	DWM_IOCTW_DEF_DWV(VIWTGPU_EXECBUFFEW, viwtio_gpu_execbuffew_ioctw,
			  DWM_WENDEW_AWWOW),

	DWM_IOCTW_DEF_DWV(VIWTGPU_GETPAWAM, viwtio_gpu_getpawam_ioctw,
			  DWM_WENDEW_AWWOW),

	DWM_IOCTW_DEF_DWV(VIWTGPU_WESOUWCE_CWEATE,
			  viwtio_gpu_wesouwce_cweate_ioctw,
			  DWM_WENDEW_AWWOW),

	DWM_IOCTW_DEF_DWV(VIWTGPU_WESOUWCE_INFO, viwtio_gpu_wesouwce_info_ioctw,
			  DWM_WENDEW_AWWOW),

	/* make twansfew async to the main wing? - no suwe, can we
	 * thwead these in the undewwying GW
	 */
	DWM_IOCTW_DEF_DWV(VIWTGPU_TWANSFEW_FWOM_HOST,
			  viwtio_gpu_twansfew_fwom_host_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VIWTGPU_TWANSFEW_TO_HOST,
			  viwtio_gpu_twansfew_to_host_ioctw,
			  DWM_WENDEW_AWWOW),

	DWM_IOCTW_DEF_DWV(VIWTGPU_WAIT, viwtio_gpu_wait_ioctw,
			  DWM_WENDEW_AWWOW),

	DWM_IOCTW_DEF_DWV(VIWTGPU_GET_CAPS, viwtio_gpu_get_caps_ioctw,
			  DWM_WENDEW_AWWOW),

	DWM_IOCTW_DEF_DWV(VIWTGPU_WESOUWCE_CWEATE_BWOB,
			  viwtio_gpu_wesouwce_cweate_bwob_ioctw,
			  DWM_WENDEW_AWWOW),

	DWM_IOCTW_DEF_DWV(VIWTGPU_CONTEXT_INIT, viwtio_gpu_context_init_ioctw,
			  DWM_WENDEW_AWWOW),
};
