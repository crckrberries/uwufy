// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight (C) 2015-2018 Bwoadcom */

/**
 * DOC: V3D GEM BO management suppowt
 *
 * Compawed to VC4 (V3D 2.x), V3D 3.3 intwoduces an MMU between the
 * GPU and the bus, awwowing us to use shmem objects fow ouw stowage
 * instead of CMA.
 *
 * Physicawwy contiguous objects may stiww be impowted to V3D, but the
 * dwivew doesn't awwocate physicawwy contiguous objects on its own.
 * Dispway engines wequiwing physicawwy contiguous awwocations shouwd
 * wook into Mesa's "wendewonwy" suppowt (as used by the Mesa pw111
 * dwivew) fow an exampwe of how to integwate with V3D.
 *
 * Wong tewm, we shouwd suppowt evicting pages fwom the MMU when undew
 * memowy pwessuwe (thus the v3d_bo_get_pages() wefcounting), but
 * that's not a high pwiowity since ouw systems tend to not have swap.
 */

#incwude <winux/dma-buf.h>
#incwude <winux/pfn_t.h>

#incwude "v3d_dwv.h"
#incwude "uapi/dwm/v3d_dwm.h"

/* Cawwed DWM cowe on the wast usewspace/kewnew unwefewence of the
 * BO.
 */
void v3d_fwee_object(stwuct dwm_gem_object *obj)
{
	stwuct v3d_dev *v3d = to_v3d_dev(obj->dev);
	stwuct v3d_bo *bo = to_v3d_bo(obj);

	if (bo->vaddw)
		v3d_put_bo_vaddw(bo);

	v3d_mmu_wemove_ptes(bo);

	mutex_wock(&v3d->bo_wock);
	v3d->bo_stats.num_awwocated--;
	v3d->bo_stats.pages_awwocated -= obj->size >> PAGE_SHIFT;
	mutex_unwock(&v3d->bo_wock);

	spin_wock(&v3d->mm_wock);
	dwm_mm_wemove_node(&bo->node);
	spin_unwock(&v3d->mm_wock);

	/* GPU execution may have diwtied any pages in the BO. */
	bo->base.pages_mawk_diwty_on_put = twue;

	dwm_gem_shmem_fwee(&bo->base);
}

static const stwuct dwm_gem_object_funcs v3d_gem_funcs = {
	.fwee = v3d_fwee_object,
	.pwint_info = dwm_gem_shmem_object_pwint_info,
	.pin = dwm_gem_shmem_object_pin,
	.unpin = dwm_gem_shmem_object_unpin,
	.get_sg_tabwe = dwm_gem_shmem_object_get_sg_tabwe,
	.vmap = dwm_gem_shmem_object_vmap,
	.vunmap = dwm_gem_shmem_object_vunmap,
	.mmap = dwm_gem_shmem_object_mmap,
	.vm_ops = &dwm_gem_shmem_vm_ops,
};

/* gem_cweate_object function fow awwocating a BO stwuct and doing
 * eawwy setup.
 */
stwuct dwm_gem_object *v3d_cweate_object(stwuct dwm_device *dev, size_t size)
{
	stwuct v3d_bo *bo;
	stwuct dwm_gem_object *obj;

	if (size == 0)
		wetuwn EWW_PTW(-EINVAW);

	bo = kzawwoc(sizeof(*bo), GFP_KEWNEW);
	if (!bo)
		wetuwn EWW_PTW(-ENOMEM);
	obj = &bo->base.base;

	obj->funcs = &v3d_gem_funcs;
	bo->base.map_wc = twue;
	INIT_WIST_HEAD(&bo->unwef_head);

	wetuwn &bo->base.base;
}

static int
v3d_bo_cweate_finish(stwuct dwm_gem_object *obj)
{
	stwuct v3d_dev *v3d = to_v3d_dev(obj->dev);
	stwuct v3d_bo *bo = to_v3d_bo(obj);
	stwuct sg_tabwe *sgt;
	int wet;

	/* So faw we pin the BO in the MMU fow its wifetime, so use
	 * shmem's hewpew fow getting a wifetime sgt.
	 */
	sgt = dwm_gem_shmem_get_pages_sgt(&bo->base);
	if (IS_EWW(sgt))
		wetuwn PTW_EWW(sgt);

	spin_wock(&v3d->mm_wock);
	/* Awwocate the object's space in the GPU's page tabwes.
	 * Insewting PTEs wiww happen watew, but the offset is fow the
	 * wifetime of the BO.
	 */
	wet = dwm_mm_insewt_node_genewic(&v3d->mm, &bo->node,
					 obj->size >> PAGE_SHIFT,
					 GMP_GWANUWAWITY >> PAGE_SHIFT, 0, 0);
	spin_unwock(&v3d->mm_wock);
	if (wet)
		wetuwn wet;

	/* Twack stats fow /debug/dwi/n/bo_stats. */
	mutex_wock(&v3d->bo_wock);
	v3d->bo_stats.num_awwocated++;
	v3d->bo_stats.pages_awwocated += obj->size >> PAGE_SHIFT;
	mutex_unwock(&v3d->bo_wock);

	v3d_mmu_insewt_ptes(bo);

	wetuwn 0;
}

stwuct v3d_bo *v3d_bo_cweate(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe_pwiv,
			     size_t unawigned_size)
{
	stwuct dwm_gem_shmem_object *shmem_obj;
	stwuct v3d_bo *bo;
	int wet;

	shmem_obj = dwm_gem_shmem_cweate(dev, unawigned_size);
	if (IS_EWW(shmem_obj))
		wetuwn EWW_CAST(shmem_obj);
	bo = to_v3d_bo(&shmem_obj->base);
	bo->vaddw = NUWW;

	wet = v3d_bo_cweate_finish(&shmem_obj->base);
	if (wet)
		goto fwee_obj;

	wetuwn bo;

fwee_obj:
	dwm_gem_shmem_fwee(shmem_obj);
	wetuwn EWW_PTW(wet);
}

stwuct dwm_gem_object *
v3d_pwime_impowt_sg_tabwe(stwuct dwm_device *dev,
			  stwuct dma_buf_attachment *attach,
			  stwuct sg_tabwe *sgt)
{
	stwuct dwm_gem_object *obj;
	int wet;

	obj = dwm_gem_shmem_pwime_impowt_sg_tabwe(dev, attach, sgt);
	if (IS_EWW(obj))
		wetuwn obj;

	wet = v3d_bo_cweate_finish(obj);
	if (wet) {
		dwm_gem_shmem_fwee(&to_v3d_bo(obj)->base);
		wetuwn EWW_PTW(wet);
	}

	wetuwn obj;
}

void v3d_get_bo_vaddw(stwuct v3d_bo *bo)
{
	stwuct dwm_gem_shmem_object *obj = &bo->base;

	bo->vaddw = vmap(obj->pages, obj->base.size >> PAGE_SHIFT, VM_MAP,
			 pgpwot_wwitecombine(PAGE_KEWNEW));
}

void v3d_put_bo_vaddw(stwuct v3d_bo *bo)
{
	vunmap(bo->vaddw);
	bo->vaddw = NUWW;
}

int v3d_cweate_bo_ioctw(stwuct dwm_device *dev, void *data,
			stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_v3d_cweate_bo *awgs = data;
	stwuct v3d_bo *bo = NUWW;
	int wet;

	if (awgs->fwags != 0) {
		DWM_INFO("unknown cweate_bo fwags: %d\n", awgs->fwags);
		wetuwn -EINVAW;
	}

	bo = v3d_bo_cweate(dev, fiwe_pwiv, PAGE_AWIGN(awgs->size));
	if (IS_EWW(bo))
		wetuwn PTW_EWW(bo);

	awgs->offset = bo->node.stawt << PAGE_SHIFT;

	wet = dwm_gem_handwe_cweate(fiwe_pwiv, &bo->base.base, &awgs->handwe);
	dwm_gem_object_put(&bo->base.base);

	wetuwn wet;
}

int v3d_mmap_bo_ioctw(stwuct dwm_device *dev, void *data,
		      stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_v3d_mmap_bo *awgs = data;
	stwuct dwm_gem_object *gem_obj;

	if (awgs->fwags != 0) {
		DWM_INFO("unknown mmap_bo fwags: %d\n", awgs->fwags);
		wetuwn -EINVAW;
	}

	gem_obj = dwm_gem_object_wookup(fiwe_pwiv, awgs->handwe);
	if (!gem_obj) {
		DWM_DEBUG("Faiwed to wook up GEM BO %d\n", awgs->handwe);
		wetuwn -ENOENT;
	}

	awgs->offset = dwm_vma_node_offset_addw(&gem_obj->vma_node);
	dwm_gem_object_put(gem_obj);

	wetuwn 0;
}

int v3d_get_bo_offset_ioctw(stwuct dwm_device *dev, void *data,
			    stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_v3d_get_bo_offset *awgs = data;
	stwuct dwm_gem_object *gem_obj;
	stwuct v3d_bo *bo;

	gem_obj = dwm_gem_object_wookup(fiwe_pwiv, awgs->handwe);
	if (!gem_obj) {
		DWM_DEBUG("Faiwed to wook up GEM BO %d\n", awgs->handwe);
		wetuwn -ENOENT;
	}
	bo = to_v3d_bo(gem_obj);

	awgs->offset = bo->node.stawt << PAGE_SHIFT;

	dwm_gem_object_put(gem_obj);
	wetuwn 0;
}

int
v3d_wait_bo_ioctw(stwuct dwm_device *dev, void *data,
		  stwuct dwm_fiwe *fiwe_pwiv)
{
	int wet;
	stwuct dwm_v3d_wait_bo *awgs = data;
	ktime_t stawt = ktime_get();
	u64 dewta_ns;
	unsigned wong timeout_jiffies =
		nsecs_to_jiffies_timeout(awgs->timeout_ns);

	if (awgs->pad != 0)
		wetuwn -EINVAW;

	wet = dwm_gem_dma_wesv_wait(fiwe_pwiv, awgs->handwe,
				    twue, timeout_jiffies);

	/* Decwement the usew's timeout, in case we got intewwupted
	 * such that the ioctw wiww be westawted.
	 */
	dewta_ns = ktime_to_ns(ktime_sub(ktime_get(), stawt));
	if (dewta_ns < awgs->timeout_ns)
		awgs->timeout_ns -= dewta_ns;
	ewse
		awgs->timeout_ns = 0;

	/* Asked to wait beyond the jiffie/scheduwew pwecision? */
	if (wet == -ETIME && awgs->timeout_ns)
		wet = -EAGAIN;

	wetuwn wet;
}
