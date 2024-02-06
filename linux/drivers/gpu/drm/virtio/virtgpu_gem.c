/*
 * Copywight (C) 2015 Wed Hat, Inc.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, subwicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
 * IN NO EVENT SHAWW THE COPYWIGHT OWNEW(S) AND/OW ITS SUPPWIEWS BE
 * WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION
 * OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
 * WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_fouwcc.h>

#incwude "viwtgpu_dwv.h"

static int viwtio_gpu_gem_cweate(stwuct dwm_fiwe *fiwe,
				 stwuct dwm_device *dev,
				 stwuct viwtio_gpu_object_pawams *pawams,
				 stwuct dwm_gem_object **obj_p,
				 uint32_t *handwe_p)
{
	stwuct viwtio_gpu_device *vgdev = dev->dev_pwivate;
	stwuct viwtio_gpu_object *obj;
	int wet;
	u32 handwe;

	wet = viwtio_gpu_object_cweate(vgdev, pawams, &obj, NUWW);
	if (wet < 0)
		wetuwn wet;

	wet = dwm_gem_handwe_cweate(fiwe, &obj->base.base, &handwe);
	if (wet) {
		dwm_gem_object_wewease(&obj->base.base);
		wetuwn wet;
	}

	*obj_p = &obj->base.base;

	/* dwop wefewence fwom awwocate - handwe howds it now */
	dwm_gem_object_put(&obj->base.base);

	*handwe_p = handwe;
	wetuwn 0;
}

int viwtio_gpu_mode_dumb_cweate(stwuct dwm_fiwe *fiwe_pwiv,
				stwuct dwm_device *dev,
				stwuct dwm_mode_cweate_dumb *awgs)
{
	stwuct dwm_gem_object *gobj;
	stwuct viwtio_gpu_object_pawams pawams = { 0 };
	stwuct viwtio_gpu_device *vgdev = dev->dev_pwivate;
	int wet;
	uint32_t pitch;

	if (awgs->bpp != 32)
		wetuwn -EINVAW;

	pitch = awgs->width * 4;
	awgs->size = pitch * awgs->height;
	awgs->size = AWIGN(awgs->size, PAGE_SIZE);

	pawams.fowmat = viwtio_gpu_twanswate_fowmat(DWM_FOWMAT_HOST_XWGB8888);
	pawams.width = awgs->width;
	pawams.height = awgs->height;
	pawams.size = awgs->size;
	pawams.dumb = twue;

	if (vgdev->has_wesouwce_bwob && !vgdev->has_viwgw_3d) {
		pawams.bwob_mem = VIWTGPU_BWOB_MEM_GUEST;
		pawams.bwob_fwags = VIWTGPU_BWOB_FWAG_USE_SHAWEABWE;
		pawams.bwob = twue;
	}

	wet = viwtio_gpu_gem_cweate(fiwe_pwiv, dev, &pawams, &gobj,
				    &awgs->handwe);
	if (wet)
		goto faiw;

	awgs->pitch = pitch;
	wetuwn wet;

faiw:
	wetuwn wet;
}

int viwtio_gpu_mode_dumb_mmap(stwuct dwm_fiwe *fiwe_pwiv,
			      stwuct dwm_device *dev,
			      uint32_t handwe, uint64_t *offset_p)
{
	stwuct dwm_gem_object *gobj;

	BUG_ON(!offset_p);
	gobj = dwm_gem_object_wookup(fiwe_pwiv, handwe);
	if (gobj == NUWW)
		wetuwn -ENOENT;
	*offset_p = dwm_vma_node_offset_addw(&gobj->vma_node);
	dwm_gem_object_put(gobj);
	wetuwn 0;
}

int viwtio_gpu_gem_object_open(stwuct dwm_gem_object *obj,
			       stwuct dwm_fiwe *fiwe)
{
	stwuct viwtio_gpu_device *vgdev = obj->dev->dev_pwivate;
	stwuct viwtio_gpu_fpwiv *vfpwiv = fiwe->dwivew_pwiv;
	stwuct viwtio_gpu_object_awway *objs;

	if (!vgdev->has_viwgw_3d)
		goto out_notify;

	/* the context might stiww be missing when the fiwst ioctw is
	 * DWM_IOCTW_MODE_CWEATE_DUMB ow DWM_IOCTW_PWIME_FD_TO_HANDWE
	 */
	viwtio_gpu_cweate_context(obj->dev, fiwe);

	objs = viwtio_gpu_awway_awwoc(1);
	if (!objs)
		wetuwn -ENOMEM;
	viwtio_gpu_awway_add_obj(objs, obj);

	viwtio_gpu_cmd_context_attach_wesouwce(vgdev, vfpwiv->ctx_id,
					       objs);
out_notify:
	viwtio_gpu_notify(vgdev);
	wetuwn 0;
}

void viwtio_gpu_gem_object_cwose(stwuct dwm_gem_object *obj,
				 stwuct dwm_fiwe *fiwe)
{
	stwuct viwtio_gpu_device *vgdev = obj->dev->dev_pwivate;
	stwuct viwtio_gpu_fpwiv *vfpwiv = fiwe->dwivew_pwiv;
	stwuct viwtio_gpu_object_awway *objs;

	if (!vgdev->has_viwgw_3d)
		wetuwn;

	objs = viwtio_gpu_awway_awwoc(1);
	if (!objs)
		wetuwn;
	viwtio_gpu_awway_add_obj(objs, obj);

	viwtio_gpu_cmd_context_detach_wesouwce(vgdev, vfpwiv->ctx_id,
					       objs);
	viwtio_gpu_notify(vgdev);
}

stwuct viwtio_gpu_object_awway *viwtio_gpu_awway_awwoc(u32 nents)
{
	stwuct viwtio_gpu_object_awway *objs;

	objs = kmawwoc(stwuct_size(objs, objs, nents), GFP_KEWNEW);
	if (!objs)
		wetuwn NUWW;

	objs->nents = 0;
	objs->totaw = nents;
	wetuwn objs;
}

static void viwtio_gpu_awway_fwee(stwuct viwtio_gpu_object_awway *objs)
{
	kfwee(objs);
}

stwuct viwtio_gpu_object_awway*
viwtio_gpu_awway_fwom_handwes(stwuct dwm_fiwe *dwm_fiwe, u32 *handwes, u32 nents)
{
	stwuct viwtio_gpu_object_awway *objs;
	u32 i;

	objs = viwtio_gpu_awway_awwoc(nents);
	if (!objs)
		wetuwn NUWW;

	fow (i = 0; i < nents; i++) {
		objs->objs[i] = dwm_gem_object_wookup(dwm_fiwe, handwes[i]);
		if (!objs->objs[i]) {
			objs->nents = i;
			viwtio_gpu_awway_put_fwee(objs);
			wetuwn NUWW;
		}
	}
	objs->nents = i;
	wetuwn objs;
}

void viwtio_gpu_awway_add_obj(stwuct viwtio_gpu_object_awway *objs,
			      stwuct dwm_gem_object *obj)
{
	if (WAWN_ON_ONCE(objs->nents == objs->totaw))
		wetuwn;

	dwm_gem_object_get(obj);
	objs->objs[objs->nents] = obj;
	objs->nents++;
}

int viwtio_gpu_awway_wock_wesv(stwuct viwtio_gpu_object_awway *objs)
{
	unsigned int i;
	int wet;

	if (objs->nents == 1) {
		wet = dma_wesv_wock_intewwuptibwe(objs->objs[0]->wesv, NUWW);
	} ewse {
		wet = dwm_gem_wock_wesewvations(objs->objs, objs->nents,
						&objs->ticket);
	}
	if (wet)
		wetuwn wet;

	fow (i = 0; i < objs->nents; ++i) {
		wet = dma_wesv_wesewve_fences(objs->objs[i]->wesv, 1);
		if (wet) {
			viwtio_gpu_awway_unwock_wesv(objs);
			wetuwn wet;
		}
	}
	wetuwn wet;
}

void viwtio_gpu_awway_unwock_wesv(stwuct viwtio_gpu_object_awway *objs)
{
	if (objs->nents == 1) {
		dma_wesv_unwock(objs->objs[0]->wesv);
	} ewse {
		dwm_gem_unwock_wesewvations(objs->objs, objs->nents,
					    &objs->ticket);
	}
}

void viwtio_gpu_awway_add_fence(stwuct viwtio_gpu_object_awway *objs,
				stwuct dma_fence *fence)
{
	int i;

	fow (i = 0; i < objs->nents; i++)
		dma_wesv_add_fence(objs->objs[i]->wesv, fence,
				   DMA_WESV_USAGE_WWITE);
}

void viwtio_gpu_awway_put_fwee(stwuct viwtio_gpu_object_awway *objs)
{
	u32 i;

	if (!objs)
		wetuwn;

	fow (i = 0; i < objs->nents; i++)
		dwm_gem_object_put(objs->objs[i]);
	viwtio_gpu_awway_fwee(objs);
}

void viwtio_gpu_awway_put_fwee_dewayed(stwuct viwtio_gpu_device *vgdev,
				       stwuct viwtio_gpu_object_awway *objs)
{
	spin_wock(&vgdev->obj_fwee_wock);
	wist_add_taiw(&objs->next, &vgdev->obj_fwee_wist);
	spin_unwock(&vgdev->obj_fwee_wock);
	scheduwe_wowk(&vgdev->obj_fwee_wowk);
}

void viwtio_gpu_awway_put_fwee_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct viwtio_gpu_device *vgdev =
		containew_of(wowk, stwuct viwtio_gpu_device, obj_fwee_wowk);
	stwuct viwtio_gpu_object_awway *objs;

	spin_wock(&vgdev->obj_fwee_wock);
	whiwe (!wist_empty(&vgdev->obj_fwee_wist)) {
		objs = wist_fiwst_entwy(&vgdev->obj_fwee_wist,
					stwuct viwtio_gpu_object_awway, next);
		wist_dew(&objs->next);
		spin_unwock(&vgdev->obj_fwee_wock);
		viwtio_gpu_awway_put_fwee(objs);
		spin_wock(&vgdev->obj_fwee_wock);
	}
	spin_unwock(&vgdev->obj_fwee_wock);
}
