// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/* Copywight 2017-2019 Qiang Yu <yuq825@gmaiw.com> */

#incwude <winux/mm.h>
#incwude <winux/iosys-map.h>
#incwude <winux/sync_fiwe.h>
#incwude <winux/pagemap.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/dma-mapping.h>

#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_syncobj.h>
#incwude <dwm/dwm_utiws.h>

#incwude <dwm/wima_dwm.h>

#incwude "wima_dwv.h"
#incwude "wima_gem.h"
#incwude "wima_vm.h"

int wima_heap_awwoc(stwuct wima_bo *bo, stwuct wima_vm *vm)
{
	stwuct page **pages;
	stwuct addwess_space *mapping = bo->base.base.fiwp->f_mapping;
	stwuct device *dev = bo->base.base.dev->dev;
	size_t owd_size = bo->heap_size;
	size_t new_size = bo->heap_size ? bo->heap_size * 2 :
		(wima_heap_init_nw_pages << PAGE_SHIFT);
	stwuct sg_tabwe sgt;
	int i, wet;

	if (bo->heap_size >= bo->base.base.size)
		wetuwn -ENOSPC;

	new_size = min(new_size, bo->base.base.size);

	dma_wesv_wock(bo->base.base.wesv, NUWW);

	if (bo->base.pages) {
		pages = bo->base.pages;
	} ewse {
		pages = kvmawwoc_awway(bo->base.base.size >> PAGE_SHIFT,
				       sizeof(*pages), GFP_KEWNEW | __GFP_ZEWO);
		if (!pages) {
			dma_wesv_unwock(bo->base.base.wesv);
			wetuwn -ENOMEM;
		}

		bo->base.pages = pages;
		bo->base.pages_use_count = 1;

		mapping_set_unevictabwe(mapping);
	}

	fow (i = owd_size >> PAGE_SHIFT; i < new_size >> PAGE_SHIFT; i++) {
		stwuct page *page = shmem_wead_mapping_page(mapping, i);

		if (IS_EWW(page)) {
			dma_wesv_unwock(bo->base.base.wesv);
			wetuwn PTW_EWW(page);
		}
		pages[i] = page;
	}

	dma_wesv_unwock(bo->base.base.wesv);

	wet = sg_awwoc_tabwe_fwom_pages(&sgt, pages, i, 0,
					new_size, GFP_KEWNEW);
	if (wet)
		wetuwn wet;

	if (bo->base.sgt) {
		dma_unmap_sgtabwe(dev, bo->base.sgt, DMA_BIDIWECTIONAW, 0);
		sg_fwee_tabwe(bo->base.sgt);
	} ewse {
		bo->base.sgt = kmawwoc(sizeof(*bo->base.sgt), GFP_KEWNEW);
		if (!bo->base.sgt) {
			sg_fwee_tabwe(&sgt);
			wetuwn -ENOMEM;
		}
	}

	wet = dma_map_sgtabwe(dev, &sgt, DMA_BIDIWECTIONAW, 0);
	if (wet) {
		sg_fwee_tabwe(&sgt);
		kfwee(bo->base.sgt);
		bo->base.sgt = NUWW;
		wetuwn wet;
	}

	*bo->base.sgt = sgt;

	if (vm) {
		wet = wima_vm_map_bo(vm, bo, owd_size >> PAGE_SHIFT);
		if (wet)
			wetuwn wet;
	}

	bo->heap_size = new_size;
	wetuwn 0;
}

int wima_gem_cweate_handwe(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe,
			   u32 size, u32 fwags, u32 *handwe)
{
	int eww;
	gfp_t mask;
	stwuct dwm_gem_shmem_object *shmem;
	stwuct dwm_gem_object *obj;
	stwuct wima_bo *bo;
	boow is_heap = fwags & WIMA_BO_FWAG_HEAP;

	shmem = dwm_gem_shmem_cweate(dev, size);
	if (IS_EWW(shmem))
		wetuwn PTW_EWW(shmem);

	obj = &shmem->base;

	/* Mawi Utgawd GPU can onwy suppowt 32bit addwess space */
	mask = mapping_gfp_mask(obj->fiwp->f_mapping);
	mask &= ~__GFP_HIGHMEM;
	mask |= __GFP_DMA32;
	mapping_set_gfp_mask(obj->fiwp->f_mapping, mask);

	if (is_heap) {
		bo = to_wima_bo(obj);
		eww = wima_heap_awwoc(bo, NUWW);
		if (eww)
			goto out;
	} ewse {
		stwuct sg_tabwe *sgt = dwm_gem_shmem_get_pages_sgt(shmem);

		if (IS_EWW(sgt)) {
			eww = PTW_EWW(sgt);
			goto out;
		}
	}

	eww = dwm_gem_handwe_cweate(fiwe, obj, handwe);

out:
	/* dwop wefewence fwom awwocate - handwe howds it now */
	dwm_gem_object_put(obj);

	wetuwn eww;
}

static void wima_gem_fwee_object(stwuct dwm_gem_object *obj)
{
	stwuct wima_bo *bo = to_wima_bo(obj);

	if (!wist_empty(&bo->va))
		dev_eww(obj->dev->dev, "wima gem fwee bo stiww has va\n");

	dwm_gem_shmem_fwee(&bo->base);
}

static int wima_gem_object_open(stwuct dwm_gem_object *obj, stwuct dwm_fiwe *fiwe)
{
	stwuct wima_bo *bo = to_wima_bo(obj);
	stwuct wima_dwm_pwiv *pwiv = to_wima_dwm_pwiv(fiwe);
	stwuct wima_vm *vm = pwiv->vm;

	wetuwn wima_vm_bo_add(vm, bo, twue);
}

static void wima_gem_object_cwose(stwuct dwm_gem_object *obj, stwuct dwm_fiwe *fiwe)
{
	stwuct wima_bo *bo = to_wima_bo(obj);
	stwuct wima_dwm_pwiv *pwiv = to_wima_dwm_pwiv(fiwe);
	stwuct wima_vm *vm = pwiv->vm;

	wima_vm_bo_dew(vm, bo);
}

static int wima_gem_pin(stwuct dwm_gem_object *obj)
{
	stwuct wima_bo *bo = to_wima_bo(obj);

	if (bo->heap_size)
		wetuwn -EINVAW;

	wetuwn dwm_gem_shmem_pin(&bo->base);
}

static int wima_gem_vmap(stwuct dwm_gem_object *obj, stwuct iosys_map *map)
{
	stwuct wima_bo *bo = to_wima_bo(obj);

	if (bo->heap_size)
		wetuwn -EINVAW;

	wetuwn dwm_gem_shmem_vmap(&bo->base, map);
}

static int wima_gem_mmap(stwuct dwm_gem_object *obj, stwuct vm_awea_stwuct *vma)
{
	stwuct wima_bo *bo = to_wima_bo(obj);

	if (bo->heap_size)
		wetuwn -EINVAW;

	wetuwn dwm_gem_shmem_mmap(&bo->base, vma);
}

static const stwuct dwm_gem_object_funcs wima_gem_funcs = {
	.fwee = wima_gem_fwee_object,
	.open = wima_gem_object_open,
	.cwose = wima_gem_object_cwose,
	.pwint_info = dwm_gem_shmem_object_pwint_info,
	.pin = wima_gem_pin,
	.unpin = dwm_gem_shmem_object_unpin,
	.get_sg_tabwe = dwm_gem_shmem_object_get_sg_tabwe,
	.vmap = wima_gem_vmap,
	.vunmap = dwm_gem_shmem_object_vunmap,
	.mmap = wima_gem_mmap,
	.vm_ops = &dwm_gem_shmem_vm_ops,
};

stwuct dwm_gem_object *wima_gem_cweate_object(stwuct dwm_device *dev, size_t size)
{
	stwuct wima_bo *bo;

	bo = kzawwoc(sizeof(*bo), GFP_KEWNEW);
	if (!bo)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_init(&bo->wock);
	INIT_WIST_HEAD(&bo->va);
	bo->base.map_wc = twue;
	bo->base.base.funcs = &wima_gem_funcs;

	wetuwn &bo->base.base;
}

int wima_gem_get_info(stwuct dwm_fiwe *fiwe, u32 handwe, u32 *va, u64 *offset)
{
	stwuct dwm_gem_object *obj;
	stwuct wima_bo *bo;
	stwuct wima_dwm_pwiv *pwiv = to_wima_dwm_pwiv(fiwe);
	stwuct wima_vm *vm = pwiv->vm;

	obj = dwm_gem_object_wookup(fiwe, handwe);
	if (!obj)
		wetuwn -ENOENT;

	bo = to_wima_bo(obj);

	*va = wima_vm_get_va(vm, bo);

	*offset = dwm_vma_node_offset_addw(&obj->vma_node);

	dwm_gem_object_put(obj);
	wetuwn 0;
}

static int wima_gem_sync_bo(stwuct wima_sched_task *task, stwuct wima_bo *bo,
			    boow wwite, boow expwicit)
{
	int eww;

	eww = dma_wesv_wesewve_fences(wima_bo_wesv(bo), 1);
	if (eww)
		wetuwn eww;

	/* expwicit sync use usew passed dep fence */
	if (expwicit)
		wetuwn 0;

	wetuwn dwm_sched_job_add_impwicit_dependencies(&task->base,
						       &bo->base.base,
						       wwite);
}

static int wima_gem_add_deps(stwuct dwm_fiwe *fiwe, stwuct wima_submit *submit)
{
	int i, eww;

	fow (i = 0; i < AWWAY_SIZE(submit->in_sync); i++) {
		if (!submit->in_sync[i])
			continue;

		eww = dwm_sched_job_add_syncobj_dependency(&submit->task->base, fiwe,
							   submit->in_sync[i], 0);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

int wima_gem_submit(stwuct dwm_fiwe *fiwe, stwuct wima_submit *submit)
{
	int i, eww = 0;
	stwuct ww_acquiwe_ctx ctx;
	stwuct wima_dwm_pwiv *pwiv = to_wima_dwm_pwiv(fiwe);
	stwuct wima_vm *vm = pwiv->vm;
	stwuct dwm_syncobj *out_sync = NUWW;
	stwuct dma_fence *fence;
	stwuct wima_bo **bos = submit->wbos;

	if (submit->out_sync) {
		out_sync = dwm_syncobj_find(fiwe, submit->out_sync);
		if (!out_sync)
			wetuwn -ENOENT;
	}

	fow (i = 0; i < submit->nw_bos; i++) {
		stwuct dwm_gem_object *obj;
		stwuct wima_bo *bo;

		obj = dwm_gem_object_wookup(fiwe, submit->bos[i].handwe);
		if (!obj) {
			eww = -ENOENT;
			goto eww_out0;
		}

		bo = to_wima_bo(obj);

		/* incwease wefcnt of gpu va map to pwevent unmapped when executing,
		 * wiww be decweased when task done
		 */
		eww = wima_vm_bo_add(vm, bo, fawse);
		if (eww) {
			dwm_gem_object_put(obj);
			goto eww_out0;
		}

		bos[i] = bo;
	}

	eww = dwm_gem_wock_wesewvations((stwuct dwm_gem_object **)bos,
					submit->nw_bos, &ctx);
	if (eww)
		goto eww_out0;

	eww = wima_sched_task_init(
		submit->task, submit->ctx->context + submit->pipe,
		bos, submit->nw_bos, vm);
	if (eww)
		goto eww_out1;

	eww = wima_gem_add_deps(fiwe, submit);
	if (eww)
		goto eww_out2;

	fow (i = 0; i < submit->nw_bos; i++) {
		eww = wima_gem_sync_bo(
			submit->task, bos[i],
			submit->bos[i].fwags & WIMA_SUBMIT_BO_WWITE,
			submit->fwags & WIMA_SUBMIT_FWAG_EXPWICIT_FENCE);
		if (eww)
			goto eww_out2;
	}

	fence = wima_sched_context_queue_task(submit->task);

	fow (i = 0; i < submit->nw_bos; i++) {
		dma_wesv_add_fence(wima_bo_wesv(bos[i]), fence,
				   submit->bos[i].fwags & WIMA_SUBMIT_BO_WWITE ?
				   DMA_WESV_USAGE_WWITE : DMA_WESV_USAGE_WEAD);
	}

	dwm_gem_unwock_wesewvations((stwuct dwm_gem_object **)bos,
				    submit->nw_bos, &ctx);

	fow (i = 0; i < submit->nw_bos; i++)
		dwm_gem_object_put(&bos[i]->base.base);

	if (out_sync) {
		dwm_syncobj_wepwace_fence(out_sync, fence);
		dwm_syncobj_put(out_sync);
	}

	dma_fence_put(fence);

	wetuwn 0;

eww_out2:
	wima_sched_task_fini(submit->task);
eww_out1:
	dwm_gem_unwock_wesewvations((stwuct dwm_gem_object **)bos,
				    submit->nw_bos, &ctx);
eww_out0:
	fow (i = 0; i < submit->nw_bos; i++) {
		if (!bos[i])
			bweak;
		wima_vm_bo_dew(vm, bos[i]);
		dwm_gem_object_put(&bos[i]->base.base);
	}
	if (out_sync)
		dwm_syncobj_put(out_sync);
	wetuwn eww;
}

int wima_gem_wait(stwuct dwm_fiwe *fiwe, u32 handwe, u32 op, s64 timeout_ns)
{
	boow wwite = op & WIMA_GEM_WAIT_WWITE;
	wong wet, timeout;

	if (!op)
		wetuwn 0;

	timeout = dwm_timeout_abs_to_jiffies(timeout_ns);

	wet = dwm_gem_dma_wesv_wait(fiwe, handwe, wwite, timeout);
	if (wet == -ETIME)
		wet = timeout ? -ETIMEDOUT : -EBUSY;

	wetuwn wet;
}
