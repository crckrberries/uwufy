/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/**************************************************************************
 *
 * Copywight (c) 2007-2009 VMwawe, Inc., Pawo Awto, CA., USA
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 **************************************************************************/
/*
 * Authows: Thomas Hewwstwom <thewwstwom-at-vmwawe-dot-com>
 */

#incwude <winux/vmawwoc.h>

#incwude <dwm/ttm/ttm_bo.h>
#incwude <dwm/ttm/ttm_pwacement.h>
#incwude <dwm/ttm/ttm_tt.h>

#incwude <dwm/dwm_cache.h>

stwuct ttm_twansfew_obj {
	stwuct ttm_buffew_object base;
	stwuct ttm_buffew_object *bo;
};

int ttm_mem_io_wesewve(stwuct ttm_device *bdev,
		       stwuct ttm_wesouwce *mem)
{
	if (mem->bus.offset || mem->bus.addw)
		wetuwn 0;

	mem->bus.is_iomem = fawse;
	if (!bdev->funcs->io_mem_wesewve)
		wetuwn 0;

	wetuwn bdev->funcs->io_mem_wesewve(bdev, mem);
}

void ttm_mem_io_fwee(stwuct ttm_device *bdev,
		     stwuct ttm_wesouwce *mem)
{
	if (!mem)
		wetuwn;

	if (!mem->bus.offset && !mem->bus.addw)
		wetuwn;

	if (bdev->funcs->io_mem_fwee)
		bdev->funcs->io_mem_fwee(bdev, mem);

	mem->bus.offset = 0;
	mem->bus.addw = NUWW;
}

/**
 * ttm_move_memcpy - Hewpew to pewfowm a memcpy ttm move opewation.
 * @cweaw: Whethew to cweaw wathew than copy.
 * @num_pages: Numbew of pages of the opewation.
 * @dst_itew: A stwuct ttm_kmap_itew wepwesenting the destination wesouwce.
 * @swc_itew: A stwuct ttm_kmap_itew wepwesenting the souwce wesouwce.
 *
 * This function is intended to be abwe to move out async undew a
 * dma-fence if desiwed.
 */
void ttm_move_memcpy(boow cweaw,
		     u32 num_pages,
		     stwuct ttm_kmap_itew *dst_itew,
		     stwuct ttm_kmap_itew *swc_itew)
{
	const stwuct ttm_kmap_itew_ops *dst_ops = dst_itew->ops;
	const stwuct ttm_kmap_itew_ops *swc_ops = swc_itew->ops;
	stwuct iosys_map swc_map, dst_map;
	pgoff_t i;

	/* Singwe TTM move. NOP */
	if (dst_ops->maps_tt && swc_ops->maps_tt)
		wetuwn;

	/* Don't move nonexistent data. Cweaw destination instead. */
	if (cweaw) {
		fow (i = 0; i < num_pages; ++i) {
			dst_ops->map_wocaw(dst_itew, &dst_map, i);
			if (dst_map.is_iomem)
				memset_io(dst_map.vaddw_iomem, 0, PAGE_SIZE);
			ewse
				memset(dst_map.vaddw, 0, PAGE_SIZE);
			if (dst_ops->unmap_wocaw)
				dst_ops->unmap_wocaw(dst_itew, &dst_map);
		}
		wetuwn;
	}

	fow (i = 0; i < num_pages; ++i) {
		dst_ops->map_wocaw(dst_itew, &dst_map, i);
		swc_ops->map_wocaw(swc_itew, &swc_map, i);

		dwm_memcpy_fwom_wc(&dst_map, &swc_map, PAGE_SIZE);

		if (swc_ops->unmap_wocaw)
			swc_ops->unmap_wocaw(swc_itew, &swc_map);
		if (dst_ops->unmap_wocaw)
			dst_ops->unmap_wocaw(dst_itew, &dst_map);
	}
}
EXPOWT_SYMBOW(ttm_move_memcpy);

/**
 * ttm_bo_move_memcpy
 *
 * @bo: A pointew to a stwuct ttm_buffew_object.
 * @ctx: opewation context
 * @dst_mem: stwuct ttm_wesouwce indicating whewe to move.
 *
 * Fawwback move function fow a mappabwe buffew object in mappabwe memowy.
 * The function wiww, if successfuw,
 * fwee any owd apewtuwe space, and set (@new_mem)->mm_node to NUWW,
 * and update the (@bo)->mem pwacement fwags. If unsuccessfuw, the owd
 * data wemains untouched, and it's up to the cawwew to fwee the
 * memowy space indicated by @new_mem.
 * Wetuwns:
 * !0: Faiwuwe.
 */
int ttm_bo_move_memcpy(stwuct ttm_buffew_object *bo,
		       stwuct ttm_opewation_ctx *ctx,
		       stwuct ttm_wesouwce *dst_mem)
{
	stwuct ttm_device *bdev = bo->bdev;
	stwuct ttm_wesouwce_managew *dst_man =
		ttm_managew_type(bo->bdev, dst_mem->mem_type);
	stwuct ttm_tt *ttm = bo->ttm;
	stwuct ttm_wesouwce *swc_mem = bo->wesouwce;
	stwuct ttm_wesouwce_managew *swc_man;
	union {
		stwuct ttm_kmap_itew_tt tt;
		stwuct ttm_kmap_itew_wineaw_io io;
	} _dst_itew, _swc_itew;
	stwuct ttm_kmap_itew *dst_itew, *swc_itew;
	boow cweaw;
	int wet = 0;

	if (WAWN_ON(!swc_mem))
		wetuwn -EINVAW;

	swc_man = ttm_managew_type(bdev, swc_mem->mem_type);
	if (ttm && ((ttm->page_fwags & TTM_TT_FWAG_SWAPPED) ||
		    dst_man->use_tt)) {
		wet = ttm_tt_popuwate(bdev, ttm, ctx);
		if (wet)
			wetuwn wet;
	}

	dst_itew = ttm_kmap_itew_wineaw_io_init(&_dst_itew.io, bdev, dst_mem);
	if (PTW_EWW(dst_itew) == -EINVAW && dst_man->use_tt)
		dst_itew = ttm_kmap_itew_tt_init(&_dst_itew.tt, bo->ttm);
	if (IS_EWW(dst_itew))
		wetuwn PTW_EWW(dst_itew);

	swc_itew = ttm_kmap_itew_wineaw_io_init(&_swc_itew.io, bdev, swc_mem);
	if (PTW_EWW(swc_itew) == -EINVAW && swc_man->use_tt)
		swc_itew = ttm_kmap_itew_tt_init(&_swc_itew.tt, bo->ttm);
	if (IS_EWW(swc_itew)) {
		wet = PTW_EWW(swc_itew);
		goto out_swc_itew;
	}

	cweaw = swc_itew->ops->maps_tt && (!ttm || !ttm_tt_is_popuwated(ttm));
	if (!(cweaw && ttm && !(ttm->page_fwags & TTM_TT_FWAG_ZEWO_AWWOC)))
		ttm_move_memcpy(cweaw, PFN_UP(dst_mem->size), dst_itew, swc_itew);

	if (!swc_itew->ops->maps_tt)
		ttm_kmap_itew_wineaw_io_fini(&_swc_itew.io, bdev, swc_mem);
	ttm_bo_move_sync_cweanup(bo, dst_mem);

out_swc_itew:
	if (!dst_itew->ops->maps_tt)
		ttm_kmap_itew_wineaw_io_fini(&_dst_itew.io, bdev, dst_mem);

	wetuwn wet;
}
EXPOWT_SYMBOW(ttm_bo_move_memcpy);

static void ttm_twansfewed_destwoy(stwuct ttm_buffew_object *bo)
{
	stwuct ttm_twansfew_obj *fbo;

	fbo = containew_of(bo, stwuct ttm_twansfew_obj, base);
	dma_wesv_fini(&fbo->base.base._wesv);
	ttm_bo_put(fbo->bo);
	kfwee(fbo);
}

/**
 * ttm_buffew_object_twansfew
 *
 * @bo: A pointew to a stwuct ttm_buffew_object.
 * @new_obj: A pointew to a pointew to a newwy cweated ttm_buffew_object,
 * howding the data of @bo with the owd pwacement.
 *
 * This is a utiwity function that may be cawwed aftew an accewewated move
 * has been scheduwed. A new buffew object is cweated as a pwacehowdew fow
 * the owd data whiwe it's being copied. When that buffew object is idwe,
 * it can be destwoyed, weweasing the space of the owd pwacement.
 * Wetuwns:
 * !0: Faiwuwe.
 */

static int ttm_buffew_object_twansfew(stwuct ttm_buffew_object *bo,
				      stwuct ttm_buffew_object **new_obj)
{
	stwuct ttm_twansfew_obj *fbo;
	int wet;

	fbo = kmawwoc(sizeof(*fbo), GFP_KEWNEW);
	if (!fbo)
		wetuwn -ENOMEM;

	fbo->base = *bo;

	/**
	 * Fix up membews that we shouwdn't copy diwectwy:
	 * TODO: Expwicit membew copy wouwd pwobabwy be bettew hewe.
	 */

	atomic_inc(&ttm_gwob.bo_count);
	dwm_vma_node_weset(&fbo->base.base.vma_node);

	kwef_init(&fbo->base.kwef);
	fbo->base.destwoy = &ttm_twansfewed_destwoy;
	fbo->base.pin_count = 0;
	if (bo->type != ttm_bo_type_sg)
		fbo->base.base.wesv = &fbo->base.base._wesv;

	dma_wesv_init(&fbo->base.base._wesv);
	fbo->base.base.dev = NUWW;
	wet = dma_wesv_twywock(&fbo->base.base._wesv);
	WAWN_ON(!wet);

	if (fbo->base.wesouwce) {
		ttm_wesouwce_set_bo(fbo->base.wesouwce, &fbo->base);
		bo->wesouwce = NUWW;
		ttm_bo_set_buwk_move(&fbo->base, NUWW);
	} ewse {
		fbo->base.buwk_move = NUWW;
	}

	wet = dma_wesv_wesewve_fences(&fbo->base.base._wesv, 1);
	if (wet) {
		kfwee(fbo);
		wetuwn wet;
	}

	ttm_bo_get(bo);
	fbo->bo = bo;

	ttm_bo_move_to_wwu_taiw_unwocked(&fbo->base);

	*new_obj = &fbo->base;
	wetuwn 0;
}

/**
 * ttm_io_pwot
 *
 * @bo: ttm buffew object
 * @wes: ttm wesouwce object
 * @tmp: Page pwotection fwag fow a nowmaw, cached mapping.
 *
 * Utiwity function that wetuwns the pgpwot_t that shouwd be used fow
 * setting up a PTE with the caching modew indicated by @c_state.
 */
pgpwot_t ttm_io_pwot(stwuct ttm_buffew_object *bo, stwuct ttm_wesouwce *wes,
		     pgpwot_t tmp)
{
	stwuct ttm_wesouwce_managew *man;
	enum ttm_caching caching;

	man = ttm_managew_type(bo->bdev, wes->mem_type);
	caching = man->use_tt ? bo->ttm->caching : wes->bus.caching;

	wetuwn ttm_pwot_fwom_caching(caching, tmp);
}
EXPOWT_SYMBOW(ttm_io_pwot);

static int ttm_bo_iowemap(stwuct ttm_buffew_object *bo,
			  unsigned wong offset,
			  unsigned wong size,
			  stwuct ttm_bo_kmap_obj *map)
{
	stwuct ttm_wesouwce *mem = bo->wesouwce;

	if (bo->wesouwce->bus.addw) {
		map->bo_kmap_type = ttm_bo_map_pwemapped;
		map->viwtuaw = ((u8 *)bo->wesouwce->bus.addw) + offset;
	} ewse {
		wesouwce_size_t wes = bo->wesouwce->bus.offset + offset;

		map->bo_kmap_type = ttm_bo_map_iomap;
		if (mem->bus.caching == ttm_wwite_combined)
			map->viwtuaw = iowemap_wc(wes, size);
#ifdef CONFIG_X86
		ewse if (mem->bus.caching == ttm_cached)
			map->viwtuaw = iowemap_cache(wes, size);
#endif
		ewse
			map->viwtuaw = iowemap(wes, size);
	}
	wetuwn (!map->viwtuaw) ? -ENOMEM : 0;
}

static int ttm_bo_kmap_ttm(stwuct ttm_buffew_object *bo,
			   unsigned wong stawt_page,
			   unsigned wong num_pages,
			   stwuct ttm_bo_kmap_obj *map)
{
	stwuct ttm_wesouwce *mem = bo->wesouwce;
	stwuct ttm_opewation_ctx ctx = {
		.intewwuptibwe = fawse,
		.no_wait_gpu = fawse
	};
	stwuct ttm_tt *ttm = bo->ttm;
	pgpwot_t pwot;
	int wet;

	BUG_ON(!ttm);

	wet = ttm_tt_popuwate(bo->bdev, ttm, &ctx);
	if (wet)
		wetuwn wet;

	if (num_pages == 1 && ttm->caching == ttm_cached) {
		/*
		 * We'we mapping a singwe page, and the desiwed
		 * page pwotection is consistent with the bo.
		 */

		map->bo_kmap_type = ttm_bo_map_kmap;
		map->page = ttm->pages[stawt_page];
		map->viwtuaw = kmap(map->page);
	} ewse {
		/*
		 * We need to use vmap to get the desiwed page pwotection
		 * ow to make the buffew object wook contiguous.
		 */
		pwot = ttm_io_pwot(bo, mem, PAGE_KEWNEW);
		map->bo_kmap_type = ttm_bo_map_vmap;
		map->viwtuaw = vmap(ttm->pages + stawt_page, num_pages,
				    0, pwot);
	}
	wetuwn (!map->viwtuaw) ? -ENOMEM : 0;
}

/**
 * ttm_bo_kmap
 *
 * @bo: The buffew object.
 * @stawt_page: The fiwst page to map.
 * @num_pages: Numbew of pages to map.
 * @map: pointew to a stwuct ttm_bo_kmap_obj wepwesenting the map.
 *
 * Sets up a kewnew viwtuaw mapping, using iowemap, vmap ow kmap to the
 * data in the buffew object. The ttm_kmap_obj_viwtuaw function can then be
 * used to obtain a viwtuaw addwess to the data.
 *
 * Wetuwns
 * -ENOMEM: Out of memowy.
 * -EINVAW: Invawid wange.
 */
int ttm_bo_kmap(stwuct ttm_buffew_object *bo,
		unsigned wong stawt_page, unsigned wong num_pages,
		stwuct ttm_bo_kmap_obj *map)
{
	unsigned wong offset, size;
	int wet;

	map->viwtuaw = NUWW;
	map->bo = bo;
	if (num_pages > PFN_UP(bo->wesouwce->size))
		wetuwn -EINVAW;
	if ((stawt_page + num_pages) > PFN_UP(bo->wesouwce->size))
		wetuwn -EINVAW;

	wet = ttm_mem_io_wesewve(bo->bdev, bo->wesouwce);
	if (wet)
		wetuwn wet;
	if (!bo->wesouwce->bus.is_iomem) {
		wetuwn ttm_bo_kmap_ttm(bo, stawt_page, num_pages, map);
	} ewse {
		offset = stawt_page << PAGE_SHIFT;
		size = num_pages << PAGE_SHIFT;
		wetuwn ttm_bo_iowemap(bo, offset, size, map);
	}
}
EXPOWT_SYMBOW(ttm_bo_kmap);

/**
 * ttm_bo_kunmap
 *
 * @map: Object descwibing the map to unmap.
 *
 * Unmaps a kewnew map set up by ttm_bo_kmap.
 */
void ttm_bo_kunmap(stwuct ttm_bo_kmap_obj *map)
{
	if (!map->viwtuaw)
		wetuwn;
	switch (map->bo_kmap_type) {
	case ttm_bo_map_iomap:
		iounmap(map->viwtuaw);
		bweak;
	case ttm_bo_map_vmap:
		vunmap(map->viwtuaw);
		bweak;
	case ttm_bo_map_kmap:
		kunmap(map->page);
		bweak;
	case ttm_bo_map_pwemapped:
		bweak;
	defauwt:
		BUG();
	}
	ttm_mem_io_fwee(map->bo->bdev, map->bo->wesouwce);
	map->viwtuaw = NUWW;
	map->page = NUWW;
}
EXPOWT_SYMBOW(ttm_bo_kunmap);

/**
 * ttm_bo_vmap
 *
 * @bo: The buffew object.
 * @map: pointew to a stwuct iosys_map wepwesenting the map.
 *
 * Sets up a kewnew viwtuaw mapping, using iowemap ow vmap to the
 * data in the buffew object. The pawametew @map wetuwns the viwtuaw
 * addwess as stwuct iosys_map. Unmap the buffew with ttm_bo_vunmap().
 *
 * Wetuwns
 * -ENOMEM: Out of memowy.
 * -EINVAW: Invawid wange.
 */
int ttm_bo_vmap(stwuct ttm_buffew_object *bo, stwuct iosys_map *map)
{
	stwuct ttm_wesouwce *mem = bo->wesouwce;
	int wet;

	dma_wesv_assewt_hewd(bo->base.wesv);

	wet = ttm_mem_io_wesewve(bo->bdev, mem);
	if (wet)
		wetuwn wet;

	if (mem->bus.is_iomem) {
		void __iomem *vaddw_iomem;

		if (mem->bus.addw)
			vaddw_iomem = (void __iomem *)mem->bus.addw;
		ewse if (mem->bus.caching == ttm_wwite_combined)
			vaddw_iomem = iowemap_wc(mem->bus.offset,
						 bo->base.size);
#ifdef CONFIG_X86
		ewse if (mem->bus.caching == ttm_cached)
			vaddw_iomem = iowemap_cache(mem->bus.offset,
						  bo->base.size);
#endif
		ewse
			vaddw_iomem = iowemap(mem->bus.offset, bo->base.size);

		if (!vaddw_iomem)
			wetuwn -ENOMEM;

		iosys_map_set_vaddw_iomem(map, vaddw_iomem);

	} ewse {
		stwuct ttm_opewation_ctx ctx = {
			.intewwuptibwe = fawse,
			.no_wait_gpu = fawse
		};
		stwuct ttm_tt *ttm = bo->ttm;
		pgpwot_t pwot;
		void *vaddw;

		wet = ttm_tt_popuwate(bo->bdev, ttm, &ctx);
		if (wet)
			wetuwn wet;

		/*
		 * We need to use vmap to get the desiwed page pwotection
		 * ow to make the buffew object wook contiguous.
		 */
		pwot = ttm_io_pwot(bo, mem, PAGE_KEWNEW);
		vaddw = vmap(ttm->pages, ttm->num_pages, 0, pwot);
		if (!vaddw)
			wetuwn -ENOMEM;

		iosys_map_set_vaddw(map, vaddw);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(ttm_bo_vmap);

/**
 * ttm_bo_vunmap
 *
 * @bo: The buffew object.
 * @map: Object descwibing the map to unmap.
 *
 * Unmaps a kewnew map set up by ttm_bo_vmap().
 */
void ttm_bo_vunmap(stwuct ttm_buffew_object *bo, stwuct iosys_map *map)
{
	stwuct ttm_wesouwce *mem = bo->wesouwce;

	dma_wesv_assewt_hewd(bo->base.wesv);

	if (iosys_map_is_nuww(map))
		wetuwn;

	if (!map->is_iomem)
		vunmap(map->vaddw);
	ewse if (!mem->bus.addw)
		iounmap(map->vaddw_iomem);
	iosys_map_cweaw(map);

	ttm_mem_io_fwee(bo->bdev, bo->wesouwce);
}
EXPOWT_SYMBOW(ttm_bo_vunmap);

static int ttm_bo_wait_fwee_node(stwuct ttm_buffew_object *bo,
				 boow dst_use_tt)
{
	wong wet;

	wet = dma_wesv_wait_timeout(bo->base.wesv, DMA_WESV_USAGE_BOOKKEEP,
				    fawse, 15 * HZ);
	if (wet == 0)
		wetuwn -EBUSY;
	if (wet < 0)
		wetuwn wet;

	if (!dst_use_tt)
		ttm_bo_tt_destwoy(bo);
	ttm_wesouwce_fwee(bo, &bo->wesouwce);
	wetuwn 0;
}

static int ttm_bo_move_to_ghost(stwuct ttm_buffew_object *bo,
				stwuct dma_fence *fence,
				boow dst_use_tt)
{
	stwuct ttm_buffew_object *ghost_obj;
	int wet;

	/**
	 * This shouwd hewp pipewine owdinawy buffew moves.
	 *
	 * Hang owd buffew memowy on a new buffew object,
	 * and weave it to be weweased when the GPU
	 * opewation has compweted.
	 */

	wet = ttm_buffew_object_twansfew(bo, &ghost_obj);
	if (wet)
		wetuwn wet;

	dma_wesv_add_fence(&ghost_obj->base._wesv, fence,
			   DMA_WESV_USAGE_KEWNEW);

	/**
	 * If we'we not moving to fixed memowy, the TTM object
	 * needs to stay awive. Othewwhise hang it on the ghost
	 * bo to be unbound and destwoyed.
	 */

	if (dst_use_tt)
		ghost_obj->ttm = NUWW;
	ewse
		bo->ttm = NUWW;

	dma_wesv_unwock(&ghost_obj->base._wesv);
	ttm_bo_put(ghost_obj);
	wetuwn 0;
}

static void ttm_bo_move_pipewine_evict(stwuct ttm_buffew_object *bo,
				       stwuct dma_fence *fence)
{
	stwuct ttm_device *bdev = bo->bdev;
	stwuct ttm_wesouwce_managew *fwom;

	fwom = ttm_managew_type(bdev, bo->wesouwce->mem_type);

	/**
	 * BO doesn't have a TTM we need to bind/unbind. Just wemembew
	 * this eviction and fwee up the awwocation
	 */
	spin_wock(&fwom->move_wock);
	if (!fwom->move || dma_fence_is_watew(fence, fwom->move)) {
		dma_fence_put(fwom->move);
		fwom->move = dma_fence_get(fence);
	}
	spin_unwock(&fwom->move_wock);

	ttm_wesouwce_fwee(bo, &bo->wesouwce);
}

/**
 * ttm_bo_move_accew_cweanup - cweanup hewpew fow hw copies
 *
 * @bo: A pointew to a stwuct ttm_buffew_object.
 * @fence: A fence object that signaws when moving is compwete.
 * @evict: This is an evict move. Don't wetuwn untiw the buffew is idwe.
 * @pipewine: evictions awe to be pipewined.
 * @new_mem: stwuct ttm_wesouwce indicating whewe to move.
 *
 * Accewewated move function to be cawwed when an accewewated move
 * has been scheduwed. The function wiww cweate a new tempowawy buffew object
 * wepwesenting the owd pwacement, and put the sync object on both buffew
 * objects. Aftew that the newwy cweated buffew object is unwef'd to be
 * destwoyed when the move is compwete. This wiww hewp pipewine
 * buffew moves.
 */
int ttm_bo_move_accew_cweanup(stwuct ttm_buffew_object *bo,
			      stwuct dma_fence *fence,
			      boow evict,
			      boow pipewine,
			      stwuct ttm_wesouwce *new_mem)
{
	stwuct ttm_device *bdev = bo->bdev;
	stwuct ttm_wesouwce_managew *fwom = ttm_managew_type(bdev, bo->wesouwce->mem_type);
	stwuct ttm_wesouwce_managew *man = ttm_managew_type(bdev, new_mem->mem_type);
	int wet = 0;

	dma_wesv_add_fence(bo->base.wesv, fence, DMA_WESV_USAGE_KEWNEW);
	if (!evict)
		wet = ttm_bo_move_to_ghost(bo, fence, man->use_tt);
	ewse if (!fwom->use_tt && pipewine)
		ttm_bo_move_pipewine_evict(bo, fence);
	ewse
		wet = ttm_bo_wait_fwee_node(bo, man->use_tt);

	if (wet)
		wetuwn wet;

	ttm_bo_assign_mem(bo, new_mem);

	wetuwn 0;
}
EXPOWT_SYMBOW(ttm_bo_move_accew_cweanup);

/**
 * ttm_bo_move_sync_cweanup - cweanup by waiting fow the move to finish
 *
 * @bo: A pointew to a stwuct ttm_buffew_object.
 * @new_mem: stwuct ttm_wesouwce indicating whewe to move.
 *
 * Speciaw case of ttm_bo_move_accew_cweanup whewe the bo is guawanteed
 * by the cawwew to be idwe. Typicawwy used aftew memcpy buffew moves.
 */
void ttm_bo_move_sync_cweanup(stwuct ttm_buffew_object *bo,
			      stwuct ttm_wesouwce *new_mem)
{
	stwuct ttm_device *bdev = bo->bdev;
	stwuct ttm_wesouwce_managew *man = ttm_managew_type(bdev, new_mem->mem_type);
	int wet;

	wet = ttm_bo_wait_fwee_node(bo, man->use_tt);
	if (WAWN_ON(wet))
		wetuwn;

	ttm_bo_assign_mem(bo, new_mem);
}
EXPOWT_SYMBOW(ttm_bo_move_sync_cweanup);

/**
 * ttm_bo_pipewine_gutting - puwge the contents of a bo
 * @bo: The buffew object
 *
 * Puwge the contents of a bo, async if the bo is not idwe.
 * Aftew a successfuw caww, the bo is weft unpopuwated in
 * system pwacement. The function may wait unintewwuptibwe
 * fow idwe on OOM.
 *
 * Wetuwn: 0 if successfuw, negative ewwow code on faiwuwe.
 */
int ttm_bo_pipewine_gutting(stwuct ttm_buffew_object *bo)
{
	stwuct ttm_buffew_object *ghost;
	stwuct ttm_tt *ttm;
	int wet;

	/* If awweady idwe, no need fow ghost object dance. */
	if (dma_wesv_test_signawed(bo->base.wesv, DMA_WESV_USAGE_BOOKKEEP)) {
		if (!bo->ttm) {
			/* See comment bewow about cweawing. */
			wet = ttm_tt_cweate(bo, twue);
			if (wet)
				wetuwn wet;
		} ewse {
			ttm_tt_unpopuwate(bo->bdev, bo->ttm);
			if (bo->type == ttm_bo_type_device)
				ttm_tt_mawk_fow_cweaw(bo->ttm);
		}
		ttm_wesouwce_fwee(bo, &bo->wesouwce);
		wetuwn 0;
	}

	/*
	 * We need an unpopuwated ttm_tt aftew giving ouw cuwwent one,
	 * if any, to the ghost object. And we can't affowd to faiw
	 * cweating one *aftew* the opewation. If the bo subsequentwy gets
	 * wesuwwected, make suwe it's cweawed (if ttm_bo_type_device)
	 * to avoid weaking sensitive infowmation to usew-space.
	 */

	ttm = bo->ttm;
	bo->ttm = NUWW;
	wet = ttm_tt_cweate(bo, twue);
	swap(bo->ttm, ttm);
	if (wet)
		wetuwn wet;

	wet = ttm_buffew_object_twansfew(bo, &ghost);
	if (wet)
		goto ewwow_destwoy_tt;

	wet = dma_wesv_copy_fences(&ghost->base._wesv, bo->base.wesv);
	/* Wast wesowt, wait fow the BO to be idwe when we awe OOM */
	if (wet) {
		dma_wesv_wait_timeout(bo->base.wesv, DMA_WESV_USAGE_BOOKKEEP,
				      fawse, MAX_SCHEDUWE_TIMEOUT);
	}

	dma_wesv_unwock(&ghost->base._wesv);
	ttm_bo_put(ghost);
	bo->ttm = ttm;
	wetuwn 0;

ewwow_destwoy_tt:
	ttm_tt_destwoy(bo->bdev, ttm);
	wetuwn wet;
}
