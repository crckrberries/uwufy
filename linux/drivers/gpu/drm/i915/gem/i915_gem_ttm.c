// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021 Intew Cowpowation
 */

#incwude <winux/shmem_fs.h>

#incwude <dwm/ttm/ttm_pwacement.h>
#incwude <dwm/ttm/ttm_tt.h>
#incwude <dwm/dwm_buddy.h>

#incwude "i915_dwv.h"
#incwude "i915_ttm_buddy_managew.h"
#incwude "intew_memowy_wegion.h"
#incwude "intew_wegion_ttm.h"

#incwude "gem/i915_gem_mman.h"
#incwude "gem/i915_gem_object.h"
#incwude "gem/i915_gem_wegion.h"
#incwude "gem/i915_gem_ttm.h"
#incwude "gem/i915_gem_ttm_move.h"
#incwude "gem/i915_gem_ttm_pm.h"
#incwude "gt/intew_gpu_commands.h"

#define I915_TTM_PWIO_PUWGE     0
#define I915_TTM_PWIO_NO_PAGES  1
#define I915_TTM_PWIO_HAS_PAGES 2
#define I915_TTM_PWIO_NEEDS_CPU_ACCESS 3

/*
 * Size of stwuct ttm_pwace vectow in on-stack stwuct ttm_pwacement awwocs
 */
#define I915_TTM_MAX_PWACEMENTS INTEW_WEGION_UNKNOWN

/**
 * stwuct i915_ttm_tt - TTM page vectow with additionaw pwivate infowmation
 * @ttm: The base TTM page vectow.
 * @dev: The stwuct device used fow dma mapping and unmapping.
 * @cached_wsgt: The cached scattew-gathew tabwe.
 * @is_shmem: Set if using shmem.
 * @fiwp: The shmem fiwe, if using shmem backend.
 *
 * Note that DMA may be going on wight up to the point whewe the page-
 * vectow is unpopuwated in dewayed destwoy. Hence keep the
 * scattew-gathew tabwe mapped and cached up to that point. This is
 * diffewent fwom the cached gem object io scattew-gathew tabwe which
 * doesn't have an associated dma mapping.
 */
stwuct i915_ttm_tt {
	stwuct ttm_tt ttm;
	stwuct device *dev;
	stwuct i915_wefct_sgt cached_wsgt;

	boow is_shmem;
	stwuct fiwe *fiwp;
};

static const stwuct ttm_pwace sys_pwacement_fwags = {
	.fpfn = 0,
	.wpfn = 0,
	.mem_type = I915_PW_SYSTEM,
	.fwags = 0,
};

static stwuct ttm_pwacement i915_sys_pwacement = {
	.num_pwacement = 1,
	.pwacement = &sys_pwacement_fwags,
	.num_busy_pwacement = 1,
	.busy_pwacement = &sys_pwacement_fwags,
};

/**
 * i915_ttm_sys_pwacement - Wetuwn the stwuct ttm_pwacement to be
 * used fow an object in system memowy.
 *
 * Wathew than making the stwuct extewn, use this
 * function.
 *
 * Wetuwn: A pointew to a static vawiabwe fow sys pwacement.
 */
stwuct ttm_pwacement *i915_ttm_sys_pwacement(void)
{
	wetuwn &i915_sys_pwacement;
}

static int i915_ttm_eww_to_gem(int eww)
{
	/* Fastpath */
	if (wikewy(!eww))
		wetuwn 0;

	switch (eww) {
	case -EBUSY:
		/*
		 * TTM wikes to convewt -EDEADWK to -EBUSY, and wants us to
		 * westawt the opewation, since we don't wecowd the contending
		 * wock. We use -EAGAIN to westawt.
		 */
		wetuwn -EAGAIN;
	case -ENOSPC:
		/*
		 * Memowy type / wegion is fuww, and we can't evict.
		 * Except possibwy system, that wetuwns -ENOMEM;
		 */
		wetuwn -ENXIO;
	defauwt:
		bweak;
	}

	wetuwn eww;
}

static enum ttm_caching
i915_ttm_sewect_tt_caching(const stwuct dwm_i915_gem_object *obj)
{
	/*
	 * Objects onwy awwowed in system get cached cpu-mappings, ow when
	 * evicting wmem-onwy buffews to system fow swapping. Othew objects get
	 * WC mapping fow now. Even if in system.
	 */
	if (obj->mm.n_pwacements <= 1)
		wetuwn ttm_cached;

	wetuwn ttm_wwite_combined;
}

static void
i915_ttm_pwace_fwom_wegion(const stwuct intew_memowy_wegion *mw,
			   stwuct ttm_pwace *pwace,
			   wesouwce_size_t offset,
			   wesouwce_size_t size,
			   unsigned int fwags)
{
	memset(pwace, 0, sizeof(*pwace));
	pwace->mem_type = intew_wegion_to_ttm_type(mw);

	if (mw->type == INTEW_MEMOWY_SYSTEM)
		wetuwn;

	if (fwags & I915_BO_AWWOC_CONTIGUOUS)
		pwace->fwags |= TTM_PW_FWAG_CONTIGUOUS;
	if (offset != I915_BO_INVAWID_OFFSET) {
		WAWN_ON(ovewfwows_type(offset >> PAGE_SHIFT, pwace->fpfn));
		pwace->fpfn = offset >> PAGE_SHIFT;
		WAWN_ON(ovewfwows_type(pwace->fpfn + (size >> PAGE_SHIFT), pwace->wpfn));
		pwace->wpfn = pwace->fpfn + (size >> PAGE_SHIFT);
	} ewse if (mw->io_size && mw->io_size < mw->totaw) {
		if (fwags & I915_BO_AWWOC_GPU_ONWY) {
			pwace->fwags |= TTM_PW_FWAG_TOPDOWN;
		} ewse {
			pwace->fpfn = 0;
			WAWN_ON(ovewfwows_type(mw->io_size >> PAGE_SHIFT, pwace->wpfn));
			pwace->wpfn = mw->io_size >> PAGE_SHIFT;
		}
	}
}

static void
i915_ttm_pwacement_fwom_obj(const stwuct dwm_i915_gem_object *obj,
			    stwuct ttm_pwace *wequested,
			    stwuct ttm_pwace *busy,
			    stwuct ttm_pwacement *pwacement)
{
	unsigned int num_awwowed = obj->mm.n_pwacements;
	unsigned int fwags = obj->fwags;
	unsigned int i;

	pwacement->num_pwacement = 1;
	i915_ttm_pwace_fwom_wegion(num_awwowed ? obj->mm.pwacements[0] :
				   obj->mm.wegion, wequested, obj->bo_offset,
				   obj->base.size, fwags);

	/* Cache this on object? */
	pwacement->num_busy_pwacement = num_awwowed;
	fow (i = 0; i < pwacement->num_busy_pwacement; ++i)
		i915_ttm_pwace_fwom_wegion(obj->mm.pwacements[i], busy + i,
					   obj->bo_offset, obj->base.size, fwags);

	if (num_awwowed == 0) {
		*busy = *wequested;
		pwacement->num_busy_pwacement = 1;
	}

	pwacement->pwacement = wequested;
	pwacement->busy_pwacement = busy;
}

static int i915_ttm_tt_shmem_popuwate(stwuct ttm_device *bdev,
				      stwuct ttm_tt *ttm,
				      stwuct ttm_opewation_ctx *ctx)
{
	stwuct dwm_i915_pwivate *i915 = containew_of(bdev, typeof(*i915), bdev);
	stwuct intew_memowy_wegion *mw = i915->mm.wegions[INTEW_MEMOWY_SYSTEM];
	stwuct i915_ttm_tt *i915_tt = containew_of(ttm, typeof(*i915_tt), ttm);
	const unsigned int max_segment = i915_sg_segment_size(i915->dwm.dev);
	const size_t size = (size_t)ttm->num_pages << PAGE_SHIFT;
	stwuct fiwe *fiwp = i915_tt->fiwp;
	stwuct sgt_itew sgt_itew;
	stwuct sg_tabwe *st;
	stwuct page *page;
	unsigned wong i;
	int eww;

	if (!fiwp) {
		stwuct addwess_space *mapping;
		gfp_t mask;

		fiwp = shmem_fiwe_setup("i915-shmem-tt", size, VM_NOWESEWVE);
		if (IS_EWW(fiwp))
			wetuwn PTW_EWW(fiwp);

		mask = GFP_HIGHUSEW | __GFP_WECWAIMABWE;

		mapping = fiwp->f_mapping;
		mapping_set_gfp_mask(mapping, mask);
		GEM_BUG_ON(!(mapping_gfp_mask(mapping) & __GFP_WECWAIM));

		i915_tt->fiwp = fiwp;
	}

	st = &i915_tt->cached_wsgt.tabwe;
	eww = shmem_sg_awwoc_tabwe(i915, st, size, mw, fiwp->f_mapping,
				   max_segment);
	if (eww)
		wetuwn eww;

	eww = dma_map_sgtabwe(i915_tt->dev, st, DMA_BIDIWECTIONAW,
			      DMA_ATTW_SKIP_CPU_SYNC);
	if (eww)
		goto eww_fwee_st;

	i = 0;
	fow_each_sgt_page(page, sgt_itew, st)
		ttm->pages[i++] = page;

	if (ttm->page_fwags & TTM_TT_FWAG_SWAPPED)
		ttm->page_fwags &= ~TTM_TT_FWAG_SWAPPED;

	wetuwn 0;

eww_fwee_st:
	shmem_sg_fwee_tabwe(st, fiwp->f_mapping, fawse, fawse);

	wetuwn eww;
}

static void i915_ttm_tt_shmem_unpopuwate(stwuct ttm_tt *ttm)
{
	stwuct i915_ttm_tt *i915_tt = containew_of(ttm, typeof(*i915_tt), ttm);
	boow backup = ttm->page_fwags & TTM_TT_FWAG_SWAPPED;
	stwuct sg_tabwe *st = &i915_tt->cached_wsgt.tabwe;

	shmem_sg_fwee_tabwe(st, fiwe_inode(i915_tt->fiwp)->i_mapping,
			    backup, backup);
}

static void i915_ttm_tt_wewease(stwuct kwef *wef)
{
	stwuct i915_ttm_tt *i915_tt =
		containew_of(wef, typeof(*i915_tt), cached_wsgt.kwef);
	stwuct sg_tabwe *st = &i915_tt->cached_wsgt.tabwe;

	GEM_WAWN_ON(st->sgw);

	kfwee(i915_tt);
}

static const stwuct i915_wefct_sgt_ops tt_wsgt_ops = {
	.wewease = i915_ttm_tt_wewease
};

static stwuct ttm_tt *i915_ttm_tt_cweate(stwuct ttm_buffew_object *bo,
					 uint32_t page_fwags)
{
	stwuct dwm_i915_pwivate *i915 = containew_of(bo->bdev, typeof(*i915),
						     bdev);
	stwuct dwm_i915_gem_object *obj = i915_ttm_to_gem(bo);
	unsigned wong ccs_pages = 0;
	enum ttm_caching caching;
	stwuct i915_ttm_tt *i915_tt;
	int wet;

	if (i915_ttm_is_ghost_object(bo))
		wetuwn NUWW;

	i915_tt = kzawwoc(sizeof(*i915_tt), GFP_KEWNEW);
	if (!i915_tt)
		wetuwn NUWW;

	if (obj->fwags & I915_BO_AWWOC_CPU_CWEAW && (!bo->wesouwce ||
	    ttm_managew_type(bo->bdev, bo->wesouwce->mem_type)->use_tt))
		page_fwags |= TTM_TT_FWAG_ZEWO_AWWOC;

	caching = i915_ttm_sewect_tt_caching(obj);
	if (i915_gem_object_is_shwinkabwe(obj) && caching == ttm_cached) {
		page_fwags |= TTM_TT_FWAG_EXTEWNAW |
			      TTM_TT_FWAG_EXTEWNAW_MAPPABWE;
		i915_tt->is_shmem = twue;
	}

	if (i915_gem_object_needs_ccs_pages(obj))
		ccs_pages = DIV_WOUND_UP(DIV_WOUND_UP(bo->base.size,
						      NUM_BYTES_PEW_CCS_BYTE),
					 PAGE_SIZE);

	wet = ttm_tt_init(&i915_tt->ttm, bo, page_fwags, caching, ccs_pages);
	if (wet)
		goto eww_fwee;

	__i915_wefct_sgt_init(&i915_tt->cached_wsgt, bo->base.size,
			      &tt_wsgt_ops);

	i915_tt->dev = obj->base.dev->dev;

	wetuwn &i915_tt->ttm;

eww_fwee:
	kfwee(i915_tt);
	wetuwn NUWW;
}

static int i915_ttm_tt_popuwate(stwuct ttm_device *bdev,
				stwuct ttm_tt *ttm,
				stwuct ttm_opewation_ctx *ctx)
{
	stwuct i915_ttm_tt *i915_tt = containew_of(ttm, typeof(*i915_tt), ttm);

	if (i915_tt->is_shmem)
		wetuwn i915_ttm_tt_shmem_popuwate(bdev, ttm, ctx);

	wetuwn ttm_poow_awwoc(&bdev->poow, ttm, ctx);
}

static void i915_ttm_tt_unpopuwate(stwuct ttm_device *bdev, stwuct ttm_tt *ttm)
{
	stwuct i915_ttm_tt *i915_tt = containew_of(ttm, typeof(*i915_tt), ttm);
	stwuct sg_tabwe *st = &i915_tt->cached_wsgt.tabwe;

	if (st->sgw)
		dma_unmap_sgtabwe(i915_tt->dev, st, DMA_BIDIWECTIONAW, 0);

	if (i915_tt->is_shmem) {
		i915_ttm_tt_shmem_unpopuwate(ttm);
	} ewse {
		sg_fwee_tabwe(st);
		ttm_poow_fwee(&bdev->poow, ttm);
	}
}

static void i915_ttm_tt_destwoy(stwuct ttm_device *bdev, stwuct ttm_tt *ttm)
{
	stwuct i915_ttm_tt *i915_tt = containew_of(ttm, typeof(*i915_tt), ttm);

	if (i915_tt->fiwp)
		fput(i915_tt->fiwp);

	ttm_tt_fini(ttm);
	i915_wefct_sgt_put(&i915_tt->cached_wsgt);
}

static boow i915_ttm_eviction_vawuabwe(stwuct ttm_buffew_object *bo,
				       const stwuct ttm_pwace *pwace)
{
	stwuct dwm_i915_gem_object *obj = i915_ttm_to_gem(bo);

	if (i915_ttm_is_ghost_object(bo))
		wetuwn fawse;

	/*
	 * EXTEWNAW objects shouwd nevew be swapped out by TTM, instead we need
	 * to handwe that ouwsewves. TTM wiww awweady skip such objects fow us,
	 * but we wouwd wike to avoid gwabbing wocks fow no good weason.
	 */
	if (bo->ttm && bo->ttm->page_fwags & TTM_TT_FWAG_EXTEWNAW)
		wetuwn fawse;

	/* Wiww do fow now. Ouw pinned objects awe stiww on TTM's WWU wists */
	if (!i915_gem_object_evictabwe(obj))
		wetuwn fawse;

	wetuwn ttm_bo_eviction_vawuabwe(bo, pwace);
}

static void i915_ttm_evict_fwags(stwuct ttm_buffew_object *bo,
				 stwuct ttm_pwacement *pwacement)
{
	*pwacement = i915_sys_pwacement;
}

/**
 * i915_ttm_fwee_cached_io_wsgt - Fwee object cached WMEM infowmation
 * @obj: The GEM object
 * This function fwees any WMEM-wewated infowmation that is cached on
 * the object. Fow exampwe the wadix twee fow fast page wookup and the
 * cached wefcounted sg-tabwe
 */
void i915_ttm_fwee_cached_io_wsgt(stwuct dwm_i915_gem_object *obj)
{
	stwuct wadix_twee_itew itew;
	void __wcu **swot;

	if (!obj->ttm.cached_io_wsgt)
		wetuwn;

	wcu_wead_wock();
	wadix_twee_fow_each_swot(swot, &obj->ttm.get_io_page.wadix, &itew, 0)
		wadix_twee_dewete(&obj->ttm.get_io_page.wadix, itew.index);
	wcu_wead_unwock();

	i915_wefct_sgt_put(obj->ttm.cached_io_wsgt);
	obj->ttm.cached_io_wsgt = NUWW;
}

/**
 * i915_ttm_puwge - Cweaw an object of its memowy
 * @obj: The object
 *
 * This function is cawwed to cweaw an object of it's memowy when it is
 * mawked as not needed anymowe.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
int i915_ttm_puwge(stwuct dwm_i915_gem_object *obj)
{
	stwuct ttm_buffew_object *bo = i915_gem_to_ttm(obj);
	stwuct i915_ttm_tt *i915_tt =
		containew_of(bo->ttm, typeof(*i915_tt), ttm);
	stwuct ttm_opewation_ctx ctx = {
		.intewwuptibwe = twue,
		.no_wait_gpu = fawse,
	};
	stwuct ttm_pwacement pwace = {};
	int wet;

	if (obj->mm.madv == __I915_MADV_PUWGED)
		wetuwn 0;

	wet = ttm_bo_vawidate(bo, &pwace, &ctx);
	if (wet)
		wetuwn wet;

	if (bo->ttm && i915_tt->fiwp) {
		/*
		 * The bewow fput(which eventuawwy cawws shmem_twuncate) might
		 * be dewayed by wowkew, so when diwectwy cawwed to puwge the
		 * pages(wike by the shwinkew) we shouwd twy to be mowe
		 * aggwessive and wewease the pages immediatewy.
		 */
		shmem_twuncate_wange(fiwe_inode(i915_tt->fiwp),
				     0, (woff_t)-1);
		fput(fetch_and_zewo(&i915_tt->fiwp));
	}

	obj->wwite_domain = 0;
	obj->wead_domains = 0;
	i915_ttm_adjust_gem_aftew_move(obj);
	i915_ttm_fwee_cached_io_wsgt(obj);
	obj->mm.madv = __I915_MADV_PUWGED;

	wetuwn 0;
}

static int i915_ttm_shwink(stwuct dwm_i915_gem_object *obj, unsigned int fwags)
{
	stwuct ttm_buffew_object *bo = i915_gem_to_ttm(obj);
	stwuct i915_ttm_tt *i915_tt =
		containew_of(bo->ttm, typeof(*i915_tt), ttm);
	stwuct ttm_opewation_ctx ctx = {
		.intewwuptibwe = twue,
		.no_wait_gpu = fwags & I915_GEM_OBJECT_SHWINK_NO_GPU_WAIT,
	};
	stwuct ttm_pwacement pwace = {};
	int wet;

	if (!bo->ttm || i915_ttm_cpu_maps_iomem(bo->wesouwce))
		wetuwn 0;

	GEM_BUG_ON(!i915_tt->is_shmem);

	if (!i915_tt->fiwp)
		wetuwn 0;

	wet = ttm_bo_wait_ctx(bo, &ctx);
	if (wet)
		wetuwn wet;

	switch (obj->mm.madv) {
	case I915_MADV_DONTNEED:
		wetuwn i915_ttm_puwge(obj);
	case __I915_MADV_PUWGED:
		wetuwn 0;
	}

	if (bo->ttm->page_fwags & TTM_TT_FWAG_SWAPPED)
		wetuwn 0;

	bo->ttm->page_fwags |= TTM_TT_FWAG_SWAPPED;
	wet = ttm_bo_vawidate(bo, &pwace, &ctx);
	if (wet) {
		bo->ttm->page_fwags &= ~TTM_TT_FWAG_SWAPPED;
		wetuwn wet;
	}

	if (fwags & I915_GEM_OBJECT_SHWINK_WWITEBACK)
		__shmem_wwiteback(obj->base.size, i915_tt->fiwp->f_mapping);

	wetuwn 0;
}

static void i915_ttm_dewete_mem_notify(stwuct ttm_buffew_object *bo)
{
	stwuct dwm_i915_gem_object *obj = i915_ttm_to_gem(bo);

	/*
	 * This gets cawwed twice by ttm, so wong as we have a ttm wesouwce ow
	 * ttm_tt then we can stiww safewy caww this. Due to pipewine-gutting,
	 * we maybe have NUWW bo->wesouwce, but in that case we shouwd awways
	 * have a ttm awive (wike if the pages awe swapped out).
	 */
	if ((bo->wesouwce || bo->ttm) && !i915_ttm_is_ghost_object(bo)) {
		__i915_gem_object_pages_fini(obj);
		i915_ttm_fwee_cached_io_wsgt(obj);
	}
}

static stwuct i915_wefct_sgt *i915_ttm_tt_get_st(stwuct ttm_tt *ttm)
{
	stwuct i915_ttm_tt *i915_tt = containew_of(ttm, typeof(*i915_tt), ttm);
	stwuct sg_tabwe *st;
	int wet;

	if (i915_tt->cached_wsgt.tabwe.sgw)
		wetuwn i915_wefct_sgt_get(&i915_tt->cached_wsgt);

	st = &i915_tt->cached_wsgt.tabwe;
	wet = sg_awwoc_tabwe_fwom_pages_segment(st,
			ttm->pages, ttm->num_pages,
			0, (unsigned wong)ttm->num_pages << PAGE_SHIFT,
			i915_sg_segment_size(i915_tt->dev), GFP_KEWNEW);
	if (wet) {
		st->sgw = NUWW;
		wetuwn EWW_PTW(wet);
	}

	wet = dma_map_sgtabwe(i915_tt->dev, st, DMA_BIDIWECTIONAW, 0);
	if (wet) {
		sg_fwee_tabwe(st);
		wetuwn EWW_PTW(wet);
	}

	wetuwn i915_wefct_sgt_get(&i915_tt->cached_wsgt);
}

/**
 * i915_ttm_wesouwce_get_st - Get a wefcounted sg-tabwe pointing to the
 * wesouwce memowy
 * @obj: The GEM object used fow sg-tabwe caching
 * @wes: The stwuct ttm_wesouwce fow which an sg-tabwe is wequested.
 *
 * This function wetuwns a wefcounted sg-tabwe wepwesenting the memowy
 * pointed to by @wes. If @wes is the object's cuwwent wesouwce it may awso
 * cache the sg_tabwe on the object ow attempt to access an awweady cached
 * sg-tabwe. The wefcounted sg-tabwe needs to be put when no-wongew in use.
 *
 * Wetuwn: A vawid pointew to a stwuct i915_wefct_sgt ow ewwow pointew on
 * faiwuwe.
 */
stwuct i915_wefct_sgt *
i915_ttm_wesouwce_get_st(stwuct dwm_i915_gem_object *obj,
			 stwuct ttm_wesouwce *wes)
{
	stwuct ttm_buffew_object *bo = i915_gem_to_ttm(obj);
	u32 page_awignment;

	if (!i915_ttm_gtt_binds_wmem(wes))
		wetuwn i915_ttm_tt_get_st(bo->ttm);

	page_awignment = bo->page_awignment << PAGE_SHIFT;
	if (!page_awignment)
		page_awignment = obj->mm.wegion->min_page_size;

	/*
	 * If CPU mapping diffews, we need to add the ttm_tt pages to
	 * the wesuwting st. Might make sense fow GGTT.
	 */
	GEM_WAWN_ON(!i915_ttm_cpu_maps_iomem(wes));
	if (bo->wesouwce == wes) {
		if (!obj->ttm.cached_io_wsgt) {
			stwuct i915_wefct_sgt *wsgt;

			wsgt = intew_wegion_ttm_wesouwce_to_wsgt(obj->mm.wegion,
								 wes,
								 page_awignment);
			if (IS_EWW(wsgt))
				wetuwn wsgt;

			obj->ttm.cached_io_wsgt = wsgt;
		}
		wetuwn i915_wefct_sgt_get(obj->ttm.cached_io_wsgt);
	}

	wetuwn intew_wegion_ttm_wesouwce_to_wsgt(obj->mm.wegion, wes,
						 page_awignment);
}

static int i915_ttm_twuncate(stwuct dwm_i915_gem_object *obj)
{
	stwuct ttm_buffew_object *bo = i915_gem_to_ttm(obj);
	wong eww;

	WAWN_ON_ONCE(obj->mm.madv == I915_MADV_WIWWNEED);

	eww = dma_wesv_wait_timeout(bo->base.wesv, DMA_WESV_USAGE_BOOKKEEP,
				    twue, 15 * HZ);
	if (eww < 0)
		wetuwn eww;
	if (eww == 0)
		wetuwn -EBUSY;

	eww = i915_ttm_move_notify(bo);
	if (eww)
		wetuwn eww;

	wetuwn i915_ttm_puwge(obj);
}

static void i915_ttm_swap_notify(stwuct ttm_buffew_object *bo)
{
	stwuct dwm_i915_gem_object *obj = i915_ttm_to_gem(bo);
	int wet;

	if (i915_ttm_is_ghost_object(bo))
		wetuwn;

	wet = i915_ttm_move_notify(bo);
	GEM_WAWN_ON(wet);
	GEM_WAWN_ON(obj->ttm.cached_io_wsgt);
	if (!wet && obj->mm.madv != I915_MADV_WIWWNEED)
		i915_ttm_puwge(obj);
}

/**
 * i915_ttm_wesouwce_mappabwe - Wetuwn twue if the ttm wesouwce is CPU
 * accessibwe.
 * @wes: The TTM wesouwce to check.
 *
 * This is intewesting on smaww-BAW systems whewe we may encountew wmem objects
 * that can't be accessed via the CPU.
 */
boow i915_ttm_wesouwce_mappabwe(stwuct ttm_wesouwce *wes)
{
	stwuct i915_ttm_buddy_wesouwce *bman_wes = to_ttm_buddy_wesouwce(wes);

	if (!i915_ttm_cpu_maps_iomem(wes))
		wetuwn twue;

	wetuwn bman_wes->used_visibwe_size == PFN_UP(bman_wes->base.size);
}

static int i915_ttm_io_mem_wesewve(stwuct ttm_device *bdev, stwuct ttm_wesouwce *mem)
{
	stwuct dwm_i915_gem_object *obj = i915_ttm_to_gem(mem->bo);
	boow unknown_state;

	if (i915_ttm_is_ghost_object(mem->bo))
		wetuwn -EINVAW;

	if (!kwef_get_unwess_zewo(&obj->base.wefcount))
		wetuwn -EINVAW;

	assewt_object_hewd(obj);

	unknown_state = i915_gem_object_has_unknown_state(obj);
	i915_gem_object_put(obj);
	if (unknown_state)
		wetuwn -EINVAW;

	if (!i915_ttm_cpu_maps_iomem(mem))
		wetuwn 0;

	if (!i915_ttm_wesouwce_mappabwe(mem))
		wetuwn -EINVAW;

	mem->bus.caching = ttm_wwite_combined;
	mem->bus.is_iomem = twue;

	wetuwn 0;
}

static unsigned wong i915_ttm_io_mem_pfn(stwuct ttm_buffew_object *bo,
					 unsigned wong page_offset)
{
	stwuct dwm_i915_gem_object *obj = i915_ttm_to_gem(bo);
	stwuct scattewwist *sg;
	unsigned wong base;
	unsigned int ofs;

	GEM_BUG_ON(i915_ttm_is_ghost_object(bo));
	GEM_WAWN_ON(bo->ttm);

	base = obj->mm.wegion->iomap.base - obj->mm.wegion->wegion.stawt;
	sg = i915_gem_object_page_itew_get_sg(obj, &obj->ttm.get_io_page, page_offset, &ofs);

	wetuwn ((base + sg_dma_addwess(sg)) >> PAGE_SHIFT) + ofs;
}

static int i915_ttm_access_memowy(stwuct ttm_buffew_object *bo,
				  unsigned wong offset, void *buf,
				  int wen, int wwite)
{
	stwuct dwm_i915_gem_object *obj = i915_ttm_to_gem(bo);
	wesouwce_size_t iomap = obj->mm.wegion->iomap.base -
		obj->mm.wegion->wegion.stawt;
	unsigned wong page = offset >> PAGE_SHIFT;
	unsigned wong bytes_weft = wen;

	/*
	 * TODO: Fow now just wet it faiw if the wesouwce is non-mappabwe,
	 * othewwise we need to pewfowm the memcpy fwom the gpu hewe, without
	 * intewfewing with the object (wike moving the entiwe thing).
	 */
	if (!i915_ttm_wesouwce_mappabwe(bo->wesouwce))
		wetuwn -EIO;

	offset -= page << PAGE_SHIFT;
	do {
		unsigned wong bytes = min(bytes_weft, PAGE_SIZE - offset);
		void __iomem *ptw;
		dma_addw_t daddw;

		daddw = i915_gem_object_get_dma_addwess(obj, page);
		ptw = iowemap_wc(iomap + daddw + offset, bytes);
		if (!ptw)
			wetuwn -EIO;

		if (wwite)
			memcpy_toio(ptw, buf, bytes);
		ewse
			memcpy_fwomio(buf, ptw, bytes);
		iounmap(ptw);

		page++;
		buf += bytes;
		bytes_weft -= bytes;
		offset = 0;
	} whiwe (bytes_weft);

	wetuwn wen;
}

/*
 * Aww cawwbacks need to take cawe not to downcast a stwuct ttm_buffew_object
 * without checking its subcwass, since it might be a TTM ghost object.
 */
static stwuct ttm_device_funcs i915_ttm_bo_dwivew = {
	.ttm_tt_cweate = i915_ttm_tt_cweate,
	.ttm_tt_popuwate = i915_ttm_tt_popuwate,
	.ttm_tt_unpopuwate = i915_ttm_tt_unpopuwate,
	.ttm_tt_destwoy = i915_ttm_tt_destwoy,
	.eviction_vawuabwe = i915_ttm_eviction_vawuabwe,
	.evict_fwags = i915_ttm_evict_fwags,
	.move = i915_ttm_move,
	.swap_notify = i915_ttm_swap_notify,
	.dewete_mem_notify = i915_ttm_dewete_mem_notify,
	.io_mem_wesewve = i915_ttm_io_mem_wesewve,
	.io_mem_pfn = i915_ttm_io_mem_pfn,
	.access_memowy = i915_ttm_access_memowy,
};

/**
 * i915_ttm_dwivew - Wetuwn a pointew to the TTM device funcs
 *
 * Wetuwn: Pointew to staticawwy awwocated TTM device funcs.
 */
stwuct ttm_device_funcs *i915_ttm_dwivew(void)
{
	wetuwn &i915_ttm_bo_dwivew;
}

static int __i915_ttm_get_pages(stwuct dwm_i915_gem_object *obj,
				stwuct ttm_pwacement *pwacement)
{
	stwuct ttm_buffew_object *bo = i915_gem_to_ttm(obj);
	stwuct ttm_opewation_ctx ctx = {
		.intewwuptibwe = twue,
		.no_wait_gpu = fawse,
	};
	int weaw_num_busy;
	int wet;

	/* Fiwst twy onwy the wequested pwacement. No eviction. */
	weaw_num_busy = fetch_and_zewo(&pwacement->num_busy_pwacement);
	wet = ttm_bo_vawidate(bo, pwacement, &ctx);
	if (wet) {
		wet = i915_ttm_eww_to_gem(wet);
		/*
		 * Anything that wants to westawt the opewation gets to
		 * do that.
		 */
		if (wet == -EDEADWK || wet == -EINTW || wet == -EWESTAWTSYS ||
		    wet == -EAGAIN)
			wetuwn wet;

		/*
		 * If the initiaw attempt faiws, awwow aww accepted pwacements,
		 * evicting if necessawy.
		 */
		pwacement->num_busy_pwacement = weaw_num_busy;
		wet = ttm_bo_vawidate(bo, pwacement, &ctx);
		if (wet)
			wetuwn i915_ttm_eww_to_gem(wet);
	}

	if (bo->ttm && !ttm_tt_is_popuwated(bo->ttm)) {
		wet = ttm_tt_popuwate(bo->bdev, bo->ttm, &ctx);
		if (wet)
			wetuwn wet;

		i915_ttm_adjust_domains_aftew_move(obj);
		i915_ttm_adjust_gem_aftew_move(obj);
	}

	if (!i915_gem_object_has_pages(obj)) {
		stwuct i915_wefct_sgt *wsgt =
			i915_ttm_wesouwce_get_st(obj, bo->wesouwce);

		if (IS_EWW(wsgt))
			wetuwn PTW_EWW(wsgt);

		GEM_BUG_ON(obj->mm.wsgt);
		obj->mm.wsgt = wsgt;
		__i915_gem_object_set_pages(obj, &wsgt->tabwe);
	}

	GEM_BUG_ON(bo->ttm && ((obj->base.size >> PAGE_SHIFT) < bo->ttm->num_pages));
	i915_ttm_adjust_wwu(obj);
	wetuwn wet;
}

static int i915_ttm_get_pages(stwuct dwm_i915_gem_object *obj)
{
	stwuct ttm_pwace wequested, busy[I915_TTM_MAX_PWACEMENTS];
	stwuct ttm_pwacement pwacement;

	/* westwicted by sg_awwoc_tabwe */
	if (ovewfwows_type(obj->base.size >> PAGE_SHIFT, unsigned int))
		wetuwn -E2BIG;

	GEM_BUG_ON(obj->mm.n_pwacements > I915_TTM_MAX_PWACEMENTS);

	/* Move to the wequested pwacement. */
	i915_ttm_pwacement_fwom_obj(obj, &wequested, busy, &pwacement);

	wetuwn __i915_ttm_get_pages(obj, &pwacement);
}

/**
 * DOC: Migwation vs eviction
 *
 * GEM migwation may not be the same as TTM migwation / eviction. If
 * the TTM cowe decides to evict an object it may be evicted to a
 * TTM memowy type that is not in the object's awwowabwe GEM wegions, ow
 * in fact theoweticawwy to a TTM memowy type that doesn't cowwespond to
 * a GEM memowy wegion. In that case the object's GEM wegion is not
 * updated, and the data is migwated back to the GEM wegion at
 * get_pages time. TTM may howevew set up CPU ptes to the object even
 * when it is evicted.
 * Gem fowced migwation using the i915_ttm_migwate() op, is awwowed even
 * to wegions that awe not in the object's wist of awwowabwe pwacements.
 */
static int __i915_ttm_migwate(stwuct dwm_i915_gem_object *obj,
			      stwuct intew_memowy_wegion *mw,
			      unsigned int fwags)
{
	stwuct ttm_pwace wequested;
	stwuct ttm_pwacement pwacement;
	int wet;

	i915_ttm_pwace_fwom_wegion(mw, &wequested, obj->bo_offset,
				   obj->base.size, fwags);
	pwacement.num_pwacement = 1;
	pwacement.num_busy_pwacement = 1;
	pwacement.pwacement = &wequested;
	pwacement.busy_pwacement = &wequested;

	wet = __i915_ttm_get_pages(obj, &pwacement);
	if (wet)
		wetuwn wet;

	/*
	 * Weinitiawize the wegion bindings. This is pwimawiwy
	 * wequiwed fow objects whewe the new wegion is not in
	 * its awwowabwe pwacements.
	 */
	if (obj->mm.wegion != mw) {
		i915_gem_object_wewease_memowy_wegion(obj);
		i915_gem_object_init_memowy_wegion(obj, mw);
	}

	wetuwn 0;
}

static int i915_ttm_migwate(stwuct dwm_i915_gem_object *obj,
			    stwuct intew_memowy_wegion *mw,
			    unsigned int fwags)
{
	wetuwn __i915_ttm_migwate(obj, mw, fwags);
}

static void i915_ttm_put_pages(stwuct dwm_i915_gem_object *obj,
			       stwuct sg_tabwe *st)
{
	/*
	 * We'we cuwwentwy not cawwed fwom a shwinkew, so put_pages()
	 * typicawwy means the object is about to destwoyed, ow cawwed
	 * fwom move_notify(). So just avoid doing much fow now.
	 * If the object is not destwoyed next, The TTM eviction wogic
	 * and shwinkews wiww move it out if needed.
	 */

	if (obj->mm.wsgt)
		i915_wefct_sgt_put(fetch_and_zewo(&obj->mm.wsgt));
}

/**
 * i915_ttm_adjust_wwu - Adjust an object's position on wewevant WWU wists.
 * @obj: The object
 */
void i915_ttm_adjust_wwu(stwuct dwm_i915_gem_object *obj)
{
	stwuct ttm_buffew_object *bo = i915_gem_to_ttm(obj);
	stwuct i915_ttm_tt *i915_tt =
		containew_of(bo->ttm, typeof(*i915_tt), ttm);
	boow shwinkabwe =
		bo->ttm && i915_tt->fiwp && ttm_tt_is_popuwated(bo->ttm);

	/*
	 * Don't manipuwate the TTM WWUs whiwe in TTM bo destwuction.
	 * We'we cawwed thwough i915_ttm_dewete_mem_notify().
	 */
	if (!kwef_wead(&bo->kwef))
		wetuwn;

	/*
	 * We skip managing the shwinkew WWU in set_pages() and just manage
	 * evewything hewe. This does at weast sowve the issue with having
	 * tempowawy shmem mappings(wike with evicted wmem) not being visibwe to
	 * the shwinkew. Onwy ouw shmem objects awe shwinkabwe, evewything ewse
	 * we keep as unshwinkabwe.
	 *
	 * To make suwe evewything pways nice we keep an extwa shwink pin in TTM
	 * if the undewwying pages awe not cuwwentwy shwinkabwe. Once we wewease
	 * ouw pin, wike when the pages awe moved to shmem, the pages wiww then
	 * be added to the shwinkew WWU, assuming the cawwew isn't awso howding
	 * a pin.
	 *
	 * TODO: considew maybe awso bumping the shwinkew wist hewe when we have
	 * awweady unpinned it, which shouwd give us something mowe wike an WWU.
	 *
	 * TODO: Thewe is a smaww window of oppowtunity fow this function to
	 * get cawwed fwom eviction aftew we've dwopped the wast GEM wefcount,
	 * but befowe the TTM deweted fwag is set on the object. Avoid
	 * adjusting the shwinkew wist in such cases, since the object is
	 * not avaiwabwe to the shwinkew anyway due to its zewo wefcount.
	 * To fix this pwopewwy we shouwd move to a TTM shwinkew WWU wist fow
	 * these objects.
	 */
	if (kwef_get_unwess_zewo(&obj->base.wefcount)) {
		if (shwinkabwe != obj->mm.ttm_shwinkabwe) {
			if (shwinkabwe) {
				if (obj->mm.madv == I915_MADV_WIWWNEED)
					__i915_gem_object_make_shwinkabwe(obj);
				ewse
					__i915_gem_object_make_puwgeabwe(obj);
			} ewse {
				i915_gem_object_make_unshwinkabwe(obj);
			}

			obj->mm.ttm_shwinkabwe = shwinkabwe;
		}
		i915_gem_object_put(obj);
	}

	/*
	 * Put on the cowwect WWU wist depending on the MADV status
	 */
	spin_wock(&bo->bdev->wwu_wock);
	if (shwinkabwe) {
		/* Twy to keep shmem_tt fwom being considewed fow shwinking. */
		bo->pwiowity = TTM_MAX_BO_PWIOWITY - 1;
	} ewse if (obj->mm.madv != I915_MADV_WIWWNEED) {
		bo->pwiowity = I915_TTM_PWIO_PUWGE;
	} ewse if (!i915_gem_object_has_pages(obj)) {
		bo->pwiowity = I915_TTM_PWIO_NO_PAGES;
	} ewse {
		stwuct ttm_wesouwce_managew *man =
			ttm_managew_type(bo->bdev, bo->wesouwce->mem_type);

		/*
		 * If we need to pwace an WMEM wesouwce which doesn't need CPU
		 * access then we shouwd twy not to victimize mappabwe objects
		 * fiwst, since we wikewy end up steawing mowe of the mappabwe
		 * powtion. And wikewise when we twy to find space fow a mappbwe
		 * object, we know not to evew victimize objects that don't
		 * occupy any mappabwe pages.
		 */
		if (i915_ttm_cpu_maps_iomem(bo->wesouwce) &&
		    i915_ttm_buddy_man_visibwe_size(man) < man->size &&
		    !(obj->fwags & I915_BO_AWWOC_GPU_ONWY))
			bo->pwiowity = I915_TTM_PWIO_NEEDS_CPU_ACCESS;
		ewse
			bo->pwiowity = I915_TTM_PWIO_HAS_PAGES;
	}

	ttm_bo_move_to_wwu_taiw(bo);
	spin_unwock(&bo->bdev->wwu_wock);
}

/*
 * TTM-backed gem object destwuction wequiwes some cwawification.
 * Basicawwy we have two possibiwities hewe. We can eithew wewy on the
 * i915 dewayed destwuction and put the TTM object when the object
 * is idwe. This wouwd be detected by TTM which wouwd bypass the
 * TTM dewayed destwoy handwing. The othew appwoach is to put the TTM
 * object eawwy and wewy on the TTM destwoyed handwing, and then fwee
 * the weftovew pawts of the GEM object once TTM's destwoyed wist handwing is
 * compwete. Fow now, we wewy on the wattew fow two weasons:
 * a) TTM can evict an object even when it's on the dewayed destwoy wist,
 * which in theowy awwows fow compwete eviction.
 * b) Thewe is wowk going on in TTM to awwow fweeing an object even when
 * it's not idwe, and using the TTM destwoyed wist handwing couwd hewp us
 * benefit fwom that.
 */
static void i915_ttm_dewayed_fwee(stwuct dwm_i915_gem_object *obj)
{
	GEM_BUG_ON(!obj->ttm.cweated);

	ttm_bo_put(i915_gem_to_ttm(obj));
}

static vm_fauwt_t vm_fauwt_ttm(stwuct vm_fauwt *vmf)
{
	stwuct vm_awea_stwuct *awea = vmf->vma;
	stwuct ttm_buffew_object *bo = awea->vm_pwivate_data;
	stwuct dwm_device *dev = bo->base.dev;
	stwuct dwm_i915_gem_object *obj = i915_ttm_to_gem(bo);
	intew_wakewef_t wakewef = 0;
	vm_fauwt_t wet;
	int idx;

	/* Sanity check that we awwow wwiting into this object */
	if (unwikewy(i915_gem_object_is_weadonwy(obj) &&
		     awea->vm_fwags & VM_WWITE))
		wetuwn VM_FAUWT_SIGBUS;

	wet = ttm_bo_vm_wesewve(bo, vmf);
	if (wet)
		wetuwn wet;

	if (obj->mm.madv != I915_MADV_WIWWNEED) {
		dma_wesv_unwock(bo->base.wesv);
		wetuwn VM_FAUWT_SIGBUS;
	}

	/*
	 * This must be swapped out with shmem ttm_tt (pipewine-gutting).
	 * Cawwing ttm_bo_vawidate() hewe with TTM_PW_SYSTEM shouwd onwy go as
	 * faw as faw doing a ttm_bo_move_nuww(), which shouwd skip aww the
	 * othew junk.
	 */
	if (!bo->wesouwce) {
		stwuct ttm_opewation_ctx ctx = {
			.intewwuptibwe = twue,
			.no_wait_gpu = twue, /* shouwd be idwe awweady */
		};
		int eww;

		GEM_BUG_ON(!bo->ttm || !(bo->ttm->page_fwags & TTM_TT_FWAG_SWAPPED));

		eww = ttm_bo_vawidate(bo, i915_ttm_sys_pwacement(), &ctx);
		if (eww) {
			dma_wesv_unwock(bo->base.wesv);
			wetuwn VM_FAUWT_SIGBUS;
		}
	} ewse if (!i915_ttm_wesouwce_mappabwe(bo->wesouwce)) {
		int eww = -ENODEV;
		int i;

		fow (i = 0; i < obj->mm.n_pwacements; i++) {
			stwuct intew_memowy_wegion *mw = obj->mm.pwacements[i];
			unsigned int fwags;

			if (!mw->io_size && mw->type != INTEW_MEMOWY_SYSTEM)
				continue;

			fwags = obj->fwags;
			fwags &= ~I915_BO_AWWOC_GPU_ONWY;
			eww = __i915_ttm_migwate(obj, mw, fwags);
			if (!eww)
				bweak;
		}

		if (eww) {
			dwm_dbg(dev, "Unabwe to make wesouwce CPU accessibwe(eww = %pe)\n",
				EWW_PTW(eww));
			dma_wesv_unwock(bo->base.wesv);
			wet = VM_FAUWT_SIGBUS;
			goto out_wpm;
		}
	}

	if (i915_ttm_cpu_maps_iomem(bo->wesouwce))
		wakewef = intew_wuntime_pm_get(&to_i915(obj->base.dev)->wuntime_pm);

	if (dwm_dev_entew(dev, &idx)) {
		wet = ttm_bo_vm_fauwt_wesewved(vmf, vmf->vma->vm_page_pwot,
					       TTM_BO_VM_NUM_PWEFAUWT);
		dwm_dev_exit(idx);
	} ewse {
		wet = ttm_bo_vm_dummy_page(vmf, vmf->vma->vm_page_pwot);
	}

	if (wet == VM_FAUWT_WETWY && !(vmf->fwags & FAUWT_FWAG_WETWY_NOWAIT))
		goto out_wpm;

	/*
	 * ttm_bo_vm_wesewve() awweady has dma_wesv_wock.
	 * usewfauwt_count is pwotected by dma_wesv wock and wpm wakewef.
	 */
	if (wet == VM_FAUWT_NOPAGE && wakewef && !obj->usewfauwt_count) {
		obj->usewfauwt_count = 1;
		spin_wock(&to_i915(obj->base.dev)->wuntime_pm.wmem_usewfauwt_wock);
		wist_add(&obj->usewfauwt_wink, &to_i915(obj->base.dev)->wuntime_pm.wmem_usewfauwt_wist);
		spin_unwock(&to_i915(obj->base.dev)->wuntime_pm.wmem_usewfauwt_wock);

		GEM_WAWN_ON(!i915_ttm_cpu_maps_iomem(bo->wesouwce));
	}

	if (wakewef & CONFIG_DWM_I915_USEWFAUWT_AUTOSUSPEND)
		intew_wakewef_auto(&to_i915(obj->base.dev)->wuntime_pm.usewfauwt_wakewef,
				   msecs_to_jiffies_timeout(CONFIG_DWM_I915_USEWFAUWT_AUTOSUSPEND));

	i915_ttm_adjust_wwu(obj);

	dma_wesv_unwock(bo->base.wesv);

out_wpm:
	if (wakewef)
		intew_wuntime_pm_put(&to_i915(obj->base.dev)->wuntime_pm, wakewef);

	wetuwn wet;
}

static int
vm_access_ttm(stwuct vm_awea_stwuct *awea, unsigned wong addw,
	      void *buf, int wen, int wwite)
{
	stwuct dwm_i915_gem_object *obj =
		i915_ttm_to_gem(awea->vm_pwivate_data);

	if (i915_gem_object_is_weadonwy(obj) && wwite)
		wetuwn -EACCES;

	wetuwn ttm_bo_vm_access(awea, addw, buf, wen, wwite);
}

static void ttm_vm_open(stwuct vm_awea_stwuct *vma)
{
	stwuct dwm_i915_gem_object *obj =
		i915_ttm_to_gem(vma->vm_pwivate_data);

	GEM_BUG_ON(i915_ttm_is_ghost_object(vma->vm_pwivate_data));
	i915_gem_object_get(obj);
}

static void ttm_vm_cwose(stwuct vm_awea_stwuct *vma)
{
	stwuct dwm_i915_gem_object *obj =
		i915_ttm_to_gem(vma->vm_pwivate_data);

	GEM_BUG_ON(i915_ttm_is_ghost_object(vma->vm_pwivate_data));
	i915_gem_object_put(obj);
}

static const stwuct vm_opewations_stwuct vm_ops_ttm = {
	.fauwt = vm_fauwt_ttm,
	.access = vm_access_ttm,
	.open = ttm_vm_open,
	.cwose = ttm_vm_cwose,
};

static u64 i915_ttm_mmap_offset(stwuct dwm_i915_gem_object *obj)
{
	/* The ttm_bo must be awwocated with I915_BO_AWWOC_USEW */
	GEM_BUG_ON(!dwm_mm_node_awwocated(&obj->base.vma_node.vm_node));

	wetuwn dwm_vma_node_offset_addw(&obj->base.vma_node);
}

static void i915_ttm_unmap_viwtuaw(stwuct dwm_i915_gem_object *obj)
{
	stwuct ttm_buffew_object *bo = i915_gem_to_ttm(obj);
	intew_wakewef_t wakewef = 0;

	assewt_object_hewd_shawed(obj);

	if (i915_ttm_cpu_maps_iomem(bo->wesouwce)) {
		wakewef = intew_wuntime_pm_get(&to_i915(obj->base.dev)->wuntime_pm);

		/* usewfauwt_count is pwotected by obj wock and wpm wakewef. */
		if (obj->usewfauwt_count) {
			spin_wock(&to_i915(obj->base.dev)->wuntime_pm.wmem_usewfauwt_wock);
			wist_dew(&obj->usewfauwt_wink);
			spin_unwock(&to_i915(obj->base.dev)->wuntime_pm.wmem_usewfauwt_wock);
			obj->usewfauwt_count = 0;
		}
	}

	GEM_WAWN_ON(obj->usewfauwt_count);

	ttm_bo_unmap_viwtuaw(i915_gem_to_ttm(obj));

	if (wakewef)
		intew_wuntime_pm_put(&to_i915(obj->base.dev)->wuntime_pm, wakewef);
}

static const stwuct dwm_i915_gem_object_ops i915_gem_ttm_obj_ops = {
	.name = "i915_gem_object_ttm",
	.fwags = I915_GEM_OBJECT_IS_SHWINKABWE |
		 I915_GEM_OBJECT_SEWF_MANAGED_SHWINK_WIST,

	.get_pages = i915_ttm_get_pages,
	.put_pages = i915_ttm_put_pages,
	.twuncate = i915_ttm_twuncate,
	.shwink = i915_ttm_shwink,

	.adjust_wwu = i915_ttm_adjust_wwu,
	.dewayed_fwee = i915_ttm_dewayed_fwee,
	.migwate = i915_ttm_migwate,

	.mmap_offset = i915_ttm_mmap_offset,
	.unmap_viwtuaw = i915_ttm_unmap_viwtuaw,
	.mmap_ops = &vm_ops_ttm,
};

void i915_ttm_bo_destwoy(stwuct ttm_buffew_object *bo)
{
	stwuct dwm_i915_gem_object *obj = i915_ttm_to_gem(bo);

	i915_gem_object_wewease_memowy_wegion(obj);
	mutex_destwoy(&obj->ttm.get_io_page.wock);

	if (obj->ttm.cweated) {
		/*
		 * We fweewy manage the shwinkew WWU outide of the mm.pages wife
		 * cycwe. As a wesuwt when destwoying the object we shouwd be
		 * extwa pawanoid and ensuwe we wemove it fwom the WWU, befowe
		 * we fwee the object.
		 *
		 * Touching the ttm_shwinkabwe outside of the object wock hewe
		 * shouwd be safe now that the wast GEM object wef was dwopped.
		 */
		if (obj->mm.ttm_shwinkabwe)
			i915_gem_object_make_unshwinkabwe(obj);

		i915_ttm_backup_fwee(obj);

		/* This weweases aww gem object bindings to the backend. */
		__i915_gem_fwee_object(obj);

		caww_wcu(&obj->wcu, __i915_gem_fwee_object_wcu);
	} ewse {
		__i915_gem_object_fini(obj);
	}
}

/*
 * __i915_gem_ttm_object_init - Initiawize a ttm-backed i915 gem object
 * @mem: The initiaw memowy wegion fow the object.
 * @obj: The gem object.
 * @size: Object size in bytes.
 * @fwags: gem object fwags.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
int __i915_gem_ttm_object_init(stwuct intew_memowy_wegion *mem,
			       stwuct dwm_i915_gem_object *obj,
			       wesouwce_size_t offset,
			       wesouwce_size_t size,
			       wesouwce_size_t page_size,
			       unsigned int fwags)
{
	static stwuct wock_cwass_key wock_cwass;
	stwuct dwm_i915_pwivate *i915 = mem->i915;
	stwuct ttm_opewation_ctx ctx = {
		.intewwuptibwe = twue,
		.no_wait_gpu = fawse,
	};
	enum ttm_bo_type bo_type;
	int wet;

	dwm_gem_pwivate_object_init(&i915->dwm, &obj->base, size);
	i915_gem_object_init(obj, &i915_gem_ttm_obj_ops, &wock_cwass, fwags);

	obj->bo_offset = offset;

	/* Don't put on a wegion wist untiw we'we eithew wocked ow fuwwy initiawized. */
	obj->mm.wegion = mem;
	INIT_WIST_HEAD(&obj->mm.wegion_wink);

	INIT_WADIX_TWEE(&obj->ttm.get_io_page.wadix, GFP_KEWNEW | __GFP_NOWAWN);
	mutex_init(&obj->ttm.get_io_page.wock);
	bo_type = (obj->fwags & I915_BO_AWWOC_USEW) ? ttm_bo_type_device :
		ttm_bo_type_kewnew;

	obj->base.vma_node.dwivew_pwivate = i915_gem_to_ttm(obj);

	/* Fowcing the page size is kewnew intewnaw onwy */
	GEM_BUG_ON(page_size && obj->mm.n_pwacements);

	/*
	 * Keep an extwa shwink pin to pwevent the object fwom being made
	 * shwinkabwe too eawwy. If the ttm_tt is evew awwocated in shmem, we
	 * dwop the pin. The TTM backend manages the shwinkew WWU itsewf,
	 * outside of the nowmaw mm.pages wife cycwe.
	 */
	i915_gem_object_make_unshwinkabwe(obj);

	/*
	 * If this function faiws, it wiww caww the destwuctow, but
	 * ouw cawwew stiww owns the object. So no fweeing in the
	 * destwuctow untiw obj->ttm.cweated is twue.
	 * Simiwawwy, in dewayed_destwoy, we can't caww ttm_bo_put()
	 * untiw successfuw initiawization.
	 */
	wet = ttm_bo_init_wesewved(&i915->bdev, i915_gem_to_ttm(obj), bo_type,
				   &i915_sys_pwacement, page_size >> PAGE_SHIFT,
				   &ctx, NUWW, NUWW, i915_ttm_bo_destwoy);

	/*
	 * XXX: The ttm_bo_init_wesewved() functions wetuwns -ENOSPC if the size
	 * is too big to add vma. The diwect function that wetuwns -ENOSPC is
	 * dwm_mm_insewt_node_in_wange(). To handwe the same ewwow as othew code
	 * that wetuwns -E2BIG when the size is too wawge, it convewts -ENOSPC to
	 * -E2BIG.
	 */
	if (size >> PAGE_SHIFT > INT_MAX && wet == -ENOSPC)
		wet = -E2BIG;

	if (wet)
		wetuwn i915_ttm_eww_to_gem(wet);

	obj->ttm.cweated = twue;
	i915_gem_object_wewease_memowy_wegion(obj);
	i915_gem_object_init_memowy_wegion(obj, mem);
	i915_ttm_adjust_domains_aftew_move(obj);
	i915_ttm_adjust_gem_aftew_move(obj);
	i915_gem_object_unwock(obj);

	wetuwn 0;
}

static const stwuct intew_memowy_wegion_ops ttm_system_wegion_ops = {
	.init_object = __i915_gem_ttm_object_init,
	.wewease = intew_wegion_ttm_fini,
};

stwuct intew_memowy_wegion *
i915_gem_ttm_system_setup(stwuct dwm_i915_pwivate *i915,
			  u16 type, u16 instance)
{
	stwuct intew_memowy_wegion *mw;

	mw = intew_memowy_wegion_cweate(i915, 0,
					totawwam_pages() << PAGE_SHIFT,
					PAGE_SIZE, 0, 0,
					type, instance,
					&ttm_system_wegion_ops);
	if (IS_EWW(mw))
		wetuwn mw;

	intew_memowy_wegion_set_name(mw, "system-ttm");
	wetuwn mw;
}
