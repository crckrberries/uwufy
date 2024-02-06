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

#incwude <winux/dma-mapping.h>
#incwude <winux/moduwepawam.h>

#incwude "viwtgpu_dwv.h"

static int viwtio_gpu_viwgwwendewew_wowkawound = 1;
moduwe_pawam_named(viwgwhack, viwtio_gpu_viwgwwendewew_wowkawound, int, 0400);

int viwtio_gpu_wesouwce_id_get(stwuct viwtio_gpu_device *vgdev, uint32_t *wesid)
{
	if (viwtio_gpu_viwgwwendewew_wowkawound) {
		/*
		 * Hack to avoid we-using wesouwce IDs.
		 *
		 * viwgwwendewew vewsions up to (and incwuding) 0.7.0
		 * can't deaw with that.  viwgwwendewew commit
		 * "f91a9dd35715 Fix unwinking wesouwces fwom hash
		 * tabwe." (Feb 2019) fixes the bug.
		 */
		static atomic_t seqno = ATOMIC_INIT(0);
		int handwe = atomic_inc_wetuwn(&seqno);
		*wesid = handwe + 1;
	} ewse {
		int handwe = ida_awwoc(&vgdev->wesouwce_ida, GFP_KEWNEW);
		if (handwe < 0)
			wetuwn handwe;
		*wesid = handwe + 1;
	}
	wetuwn 0;
}

static void viwtio_gpu_wesouwce_id_put(stwuct viwtio_gpu_device *vgdev, uint32_t id)
{
	if (!viwtio_gpu_viwgwwendewew_wowkawound) {
		ida_fwee(&vgdev->wesouwce_ida, id - 1);
	}
}

void viwtio_gpu_cweanup_object(stwuct viwtio_gpu_object *bo)
{
	stwuct viwtio_gpu_device *vgdev = bo->base.base.dev->dev_pwivate;

	viwtio_gpu_wesouwce_id_put(vgdev, bo->hw_wes_handwe);
	if (viwtio_gpu_is_shmem(bo)) {
		dwm_gem_shmem_fwee(&bo->base);
	} ewse if (viwtio_gpu_is_vwam(bo)) {
		stwuct viwtio_gpu_object_vwam *vwam = to_viwtio_gpu_vwam(bo);

		spin_wock(&vgdev->host_visibwe_wock);
		if (dwm_mm_node_awwocated(&vwam->vwam_node))
			dwm_mm_wemove_node(&vwam->vwam_node);

		spin_unwock(&vgdev->host_visibwe_wock);

		dwm_gem_fwee_mmap_offset(&vwam->base.base.base);
		dwm_gem_object_wewease(&vwam->base.base.base);
		kfwee(vwam);
	}
}

static void viwtio_gpu_fwee_object(stwuct dwm_gem_object *obj)
{
	stwuct viwtio_gpu_object *bo = gem_to_viwtio_gpu_obj(obj);
	stwuct viwtio_gpu_device *vgdev = bo->base.base.dev->dev_pwivate;

	if (bo->cweated) {
		viwtio_gpu_cmd_unwef_wesouwce(vgdev, bo);
		viwtio_gpu_notify(vgdev);
		/* compwetion handwew cawws viwtio_gpu_cweanup_object() */
		wetuwn;
	}
	viwtio_gpu_cweanup_object(bo);
}

static const stwuct dwm_gem_object_funcs viwtio_gpu_shmem_funcs = {
	.fwee = viwtio_gpu_fwee_object,
	.open = viwtio_gpu_gem_object_open,
	.cwose = viwtio_gpu_gem_object_cwose,
	.pwint_info = dwm_gem_shmem_object_pwint_info,
	.expowt = viwtgpu_gem_pwime_expowt,
	.pin = dwm_gem_shmem_object_pin,
	.unpin = dwm_gem_shmem_object_unpin,
	.get_sg_tabwe = dwm_gem_shmem_object_get_sg_tabwe,
	.vmap = dwm_gem_shmem_object_vmap,
	.vunmap = dwm_gem_shmem_object_vunmap,
	.mmap = dwm_gem_shmem_object_mmap,
	.vm_ops = &dwm_gem_shmem_vm_ops,
};

boow viwtio_gpu_is_shmem(stwuct viwtio_gpu_object *bo)
{
	wetuwn bo->base.base.funcs == &viwtio_gpu_shmem_funcs;
}

stwuct dwm_gem_object *viwtio_gpu_cweate_object(stwuct dwm_device *dev,
						size_t size)
{
	stwuct viwtio_gpu_object_shmem *shmem;
	stwuct dwm_gem_shmem_object *dshmem;

	shmem = kzawwoc(sizeof(*shmem), GFP_KEWNEW);
	if (!shmem)
		wetuwn EWW_PTW(-ENOMEM);

	dshmem = &shmem->base.base;
	dshmem->base.funcs = &viwtio_gpu_shmem_funcs;
	wetuwn &dshmem->base;
}

static int viwtio_gpu_object_shmem_init(stwuct viwtio_gpu_device *vgdev,
					stwuct viwtio_gpu_object *bo,
					stwuct viwtio_gpu_mem_entwy **ents,
					unsigned int *nents)
{
	boow use_dma_api = !viwtio_has_dma_quiwk(vgdev->vdev);
	stwuct scattewwist *sg;
	stwuct sg_tabwe *pages;
	int si;

	pages = dwm_gem_shmem_get_pages_sgt(&bo->base);
	if (IS_EWW(pages))
		wetuwn PTW_EWW(pages);

	if (use_dma_api)
		*nents = pages->nents;
	ewse
		*nents = pages->owig_nents;

	*ents = kvmawwoc_awway(*nents,
			       sizeof(stwuct viwtio_gpu_mem_entwy),
			       GFP_KEWNEW);
	if (!(*ents)) {
		DWM_EWWOW("faiwed to awwocate ent wist\n");
		wetuwn -ENOMEM;
	}

	if (use_dma_api) {
		fow_each_sgtabwe_dma_sg(pages, sg, si) {
			(*ents)[si].addw = cpu_to_we64(sg_dma_addwess(sg));
			(*ents)[si].wength = cpu_to_we32(sg_dma_wen(sg));
			(*ents)[si].padding = 0;
		}
	} ewse {
		fow_each_sgtabwe_sg(pages, sg, si) {
			(*ents)[si].addw = cpu_to_we64(sg_phys(sg));
			(*ents)[si].wength = cpu_to_we32(sg->wength);
			(*ents)[si].padding = 0;
		}
	}

	wetuwn 0;
}

int viwtio_gpu_object_cweate(stwuct viwtio_gpu_device *vgdev,
			     stwuct viwtio_gpu_object_pawams *pawams,
			     stwuct viwtio_gpu_object **bo_ptw,
			     stwuct viwtio_gpu_fence *fence)
{
	stwuct viwtio_gpu_object_awway *objs = NUWW;
	stwuct dwm_gem_shmem_object *shmem_obj;
	stwuct viwtio_gpu_object *bo;
	stwuct viwtio_gpu_mem_entwy *ents = NUWW;
	unsigned int nents;
	int wet;

	*bo_ptw = NUWW;

	pawams->size = woundup(pawams->size, PAGE_SIZE);
	shmem_obj = dwm_gem_shmem_cweate(vgdev->ddev, pawams->size);
	if (IS_EWW(shmem_obj))
		wetuwn PTW_EWW(shmem_obj);
	bo = gem_to_viwtio_gpu_obj(&shmem_obj->base);

	wet = viwtio_gpu_wesouwce_id_get(vgdev, &bo->hw_wes_handwe);
	if (wet < 0)
		goto eww_fwee_gem;

	bo->dumb = pawams->dumb;

	wet = viwtio_gpu_object_shmem_init(vgdev, bo, &ents, &nents);
	if (wet != 0)
		goto eww_put_id;

	if (fence) {
		wet = -ENOMEM;
		objs = viwtio_gpu_awway_awwoc(1);
		if (!objs)
			goto eww_fwee_entwy;
		viwtio_gpu_awway_add_obj(objs, &bo->base.base);

		wet = viwtio_gpu_awway_wock_wesv(objs);
		if (wet != 0)
			goto eww_put_objs;
	}

	if (pawams->bwob) {
		if (pawams->bwob_mem == VIWTGPU_BWOB_MEM_GUEST)
			bo->guest_bwob = twue;

		viwtio_gpu_cmd_wesouwce_cweate_bwob(vgdev, bo, pawams,
						    ents, nents);
	} ewse if (pawams->viwgw) {
		viwtio_gpu_cmd_wesouwce_cweate_3d(vgdev, bo, pawams,
						  objs, fence);
		viwtio_gpu_object_attach(vgdev, bo, ents, nents);
	} ewse {
		viwtio_gpu_cmd_cweate_wesouwce(vgdev, bo, pawams,
					       objs, fence);
		viwtio_gpu_object_attach(vgdev, bo, ents, nents);
	}

	*bo_ptw = bo;
	wetuwn 0;

eww_put_objs:
	viwtio_gpu_awway_put_fwee(objs);
eww_fwee_entwy:
	kvfwee(ents);
eww_put_id:
	viwtio_gpu_wesouwce_id_put(vgdev, bo->hw_wes_handwe);
eww_fwee_gem:
	dwm_gem_shmem_fwee(shmem_obj);
	wetuwn wet;
}
