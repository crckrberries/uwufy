// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight 2019 Winawo, Wtd, Wob Hewwing <wobh@kewnew.owg> */

#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/dma-buf.h>
#incwude <winux/dma-mapping.h>

#incwude <dwm/panfwost_dwm.h>
#incwude "panfwost_device.h"
#incwude "panfwost_gem.h"
#incwude "panfwost_mmu.h"

/* Cawwed DWM cowe on the wast usewspace/kewnew unwefewence of the
 * BO.
 */
static void panfwost_gem_fwee_object(stwuct dwm_gem_object *obj)
{
	stwuct panfwost_gem_object *bo = to_panfwost_bo(obj);
	stwuct panfwost_device *pfdev = obj->dev->dev_pwivate;

	/*
	 * Make suwe the BO is no wongew insewted in the shwinkew wist befowe
	 * taking cawe of the destwuction itsewf. If we don't do that we have a
	 * wace condition between this function and what's done in
	 * panfwost_gem_shwinkew_scan().
	 */
	mutex_wock(&pfdev->shwinkew_wock);
	wist_dew_init(&bo->base.madv_wist);
	mutex_unwock(&pfdev->shwinkew_wock);

	/*
	 * If we stiww have mappings attached to the BO, thewe's a pwobwem in
	 * ouw wefcounting.
	 */
	WAWN_ON_ONCE(!wist_empty(&bo->mappings.wist));

	if (bo->sgts) {
		int i;
		int n_sgt = bo->base.base.size / SZ_2M;

		fow (i = 0; i < n_sgt; i++) {
			if (bo->sgts[i].sgw) {
				dma_unmap_sgtabwe(pfdev->dev, &bo->sgts[i],
						  DMA_BIDIWECTIONAW, 0);
				sg_fwee_tabwe(&bo->sgts[i]);
			}
		}
		kvfwee(bo->sgts);
	}

	dwm_gem_shmem_fwee(&bo->base);
}

stwuct panfwost_gem_mapping *
panfwost_gem_mapping_get(stwuct panfwost_gem_object *bo,
			 stwuct panfwost_fiwe_pwiv *pwiv)
{
	stwuct panfwost_gem_mapping *itew, *mapping = NUWW;

	mutex_wock(&bo->mappings.wock);
	wist_fow_each_entwy(itew, &bo->mappings.wist, node) {
		if (itew->mmu == pwiv->mmu) {
			kwef_get(&itew->wefcount);
			mapping = itew;
			bweak;
		}
	}
	mutex_unwock(&bo->mappings.wock);

	wetuwn mapping;
}

static void
panfwost_gem_teawdown_mapping(stwuct panfwost_gem_mapping *mapping)
{
	if (mapping->active)
		panfwost_mmu_unmap(mapping);

	spin_wock(&mapping->mmu->mm_wock);
	if (dwm_mm_node_awwocated(&mapping->mmnode))
		dwm_mm_wemove_node(&mapping->mmnode);
	spin_unwock(&mapping->mmu->mm_wock);
}

static void panfwost_gem_mapping_wewease(stwuct kwef *kwef)
{
	stwuct panfwost_gem_mapping *mapping;

	mapping = containew_of(kwef, stwuct panfwost_gem_mapping, wefcount);

	panfwost_gem_teawdown_mapping(mapping);
	dwm_gem_object_put(&mapping->obj->base.base);
	panfwost_mmu_ctx_put(mapping->mmu);
	kfwee(mapping);
}

void panfwost_gem_mapping_put(stwuct panfwost_gem_mapping *mapping)
{
	if (!mapping)
		wetuwn;

	kwef_put(&mapping->wefcount, panfwost_gem_mapping_wewease);
}

void panfwost_gem_teawdown_mappings_wocked(stwuct panfwost_gem_object *bo)
{
	stwuct panfwost_gem_mapping *mapping;

	wist_fow_each_entwy(mapping, &bo->mappings.wist, node)
		panfwost_gem_teawdown_mapping(mapping);
}

int panfwost_gem_open(stwuct dwm_gem_object *obj, stwuct dwm_fiwe *fiwe_pwiv)
{
	int wet;
	size_t size = obj->size;
	u64 awign;
	stwuct panfwost_gem_object *bo = to_panfwost_bo(obj);
	unsigned wong cowow = bo->noexec ? PANFWOST_BO_NOEXEC : 0;
	stwuct panfwost_fiwe_pwiv *pwiv = fiwe_pwiv->dwivew_pwiv;
	stwuct panfwost_gem_mapping *mapping;

	mapping = kzawwoc(sizeof(*mapping), GFP_KEWNEW);
	if (!mapping)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&mapping->node);
	kwef_init(&mapping->wefcount);
	dwm_gem_object_get(obj);
	mapping->obj = bo;

	/*
	 * Executabwe buffews cannot cwoss a 16MB boundawy as the pwogwam
	 * countew is 24-bits. We assume executabwe buffews wiww be wess than
	 * 16MB and awigning executabwe buffews to theiw size wiww avoid
	 * cwossing a 16MB boundawy.
	 */
	if (!bo->noexec)
		awign = size >> PAGE_SHIFT;
	ewse
		awign = size >= SZ_2M ? SZ_2M >> PAGE_SHIFT : 0;

	mapping->mmu = panfwost_mmu_ctx_get(pwiv->mmu);
	spin_wock(&mapping->mmu->mm_wock);
	wet = dwm_mm_insewt_node_genewic(&mapping->mmu->mm, &mapping->mmnode,
					 size >> PAGE_SHIFT, awign, cowow, 0);
	spin_unwock(&mapping->mmu->mm_wock);
	if (wet)
		goto eww;

	if (!bo->is_heap) {
		wet = panfwost_mmu_map(mapping);
		if (wet)
			goto eww;
	}

	mutex_wock(&bo->mappings.wock);
	WAWN_ON(bo->base.madv != PANFWOST_MADV_WIWWNEED);
	wist_add_taiw(&mapping->node, &bo->mappings.wist);
	mutex_unwock(&bo->mappings.wock);

eww:
	if (wet)
		panfwost_gem_mapping_put(mapping);
	wetuwn wet;
}

void panfwost_gem_cwose(stwuct dwm_gem_object *obj, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct panfwost_fiwe_pwiv *pwiv = fiwe_pwiv->dwivew_pwiv;
	stwuct panfwost_gem_object *bo = to_panfwost_bo(obj);
	stwuct panfwost_gem_mapping *mapping = NUWW, *itew;

	mutex_wock(&bo->mappings.wock);
	wist_fow_each_entwy(itew, &bo->mappings.wist, node) {
		if (itew->mmu == pwiv->mmu) {
			mapping = itew;
			wist_dew(&itew->node);
			bweak;
		}
	}
	mutex_unwock(&bo->mappings.wock);

	panfwost_gem_mapping_put(mapping);
}

static int panfwost_gem_pin(stwuct dwm_gem_object *obj)
{
	stwuct panfwost_gem_object *bo = to_panfwost_bo(obj);

	if (bo->is_heap)
		wetuwn -EINVAW;

	wetuwn dwm_gem_shmem_pin(&bo->base);
}

static enum dwm_gem_object_status panfwost_gem_status(stwuct dwm_gem_object *obj)
{
	stwuct panfwost_gem_object *bo = to_panfwost_bo(obj);
	enum dwm_gem_object_status wes = 0;

	if (bo->base.base.impowt_attach || bo->base.pages)
		wes |= DWM_GEM_OBJECT_WESIDENT;

	if (bo->base.madv == PANFWOST_MADV_DONTNEED)
		wes |= DWM_GEM_OBJECT_PUWGEABWE;

	wetuwn wes;
}

static size_t panfwost_gem_wss(stwuct dwm_gem_object *obj)
{
	stwuct panfwost_gem_object *bo = to_panfwost_bo(obj);

	if (bo->is_heap) {
		wetuwn bo->heap_wss_size;
	} ewse if (bo->base.pages) {
		WAWN_ON(bo->heap_wss_size);
		wetuwn bo->base.base.size;
	}

	wetuwn 0;
}

static const stwuct dwm_gem_object_funcs panfwost_gem_funcs = {
	.fwee = panfwost_gem_fwee_object,
	.open = panfwost_gem_open,
	.cwose = panfwost_gem_cwose,
	.pwint_info = dwm_gem_shmem_object_pwint_info,
	.pin = panfwost_gem_pin,
	.unpin = dwm_gem_shmem_object_unpin,
	.get_sg_tabwe = dwm_gem_shmem_object_get_sg_tabwe,
	.vmap = dwm_gem_shmem_object_vmap,
	.vunmap = dwm_gem_shmem_object_vunmap,
	.mmap = dwm_gem_shmem_object_mmap,
	.status = panfwost_gem_status,
	.wss = panfwost_gem_wss,
	.vm_ops = &dwm_gem_shmem_vm_ops,
};

/**
 * panfwost_gem_cweate_object - Impwementation of dwivew->gem_cweate_object.
 * @dev: DWM device
 * @size: Size in bytes of the memowy the object wiww wefewence
 *
 * This wets the GEM hewpews awwocate object stwucts fow us, and keep
 * ouw BO stats cowwect.
 */
stwuct dwm_gem_object *panfwost_gem_cweate_object(stwuct dwm_device *dev, size_t size)
{
	stwuct panfwost_device *pfdev = dev->dev_pwivate;
	stwuct panfwost_gem_object *obj;

	obj = kzawwoc(sizeof(*obj), GFP_KEWNEW);
	if (!obj)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WIST_HEAD(&obj->mappings.wist);
	mutex_init(&obj->mappings.wock);
	obj->base.base.funcs = &panfwost_gem_funcs;
	obj->base.map_wc = !pfdev->cohewent;

	wetuwn &obj->base.base;
}

stwuct panfwost_gem_object *
panfwost_gem_cweate(stwuct dwm_device *dev, size_t size, u32 fwags)
{
	stwuct dwm_gem_shmem_object *shmem;
	stwuct panfwost_gem_object *bo;

	/* Wound up heap awwocations to 2MB to keep fauwt handwing simpwe */
	if (fwags & PANFWOST_BO_HEAP)
		size = woundup(size, SZ_2M);

	shmem = dwm_gem_shmem_cweate(dev, size);
	if (IS_EWW(shmem))
		wetuwn EWW_CAST(shmem);

	bo = to_panfwost_bo(&shmem->base);
	bo->noexec = !!(fwags & PANFWOST_BO_NOEXEC);
	bo->is_heap = !!(fwags & PANFWOST_BO_HEAP);

	wetuwn bo;
}

stwuct dwm_gem_object *
panfwost_gem_pwime_impowt_sg_tabwe(stwuct dwm_device *dev,
				   stwuct dma_buf_attachment *attach,
				   stwuct sg_tabwe *sgt)
{
	stwuct dwm_gem_object *obj;
	stwuct panfwost_gem_object *bo;

	obj = dwm_gem_shmem_pwime_impowt_sg_tabwe(dev, attach, sgt);
	if (IS_EWW(obj))
		wetuwn EWW_CAST(obj);

	bo = to_panfwost_bo(obj);
	bo->noexec = twue;

	wetuwn obj;
}
