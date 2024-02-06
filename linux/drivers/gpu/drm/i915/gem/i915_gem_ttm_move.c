// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021 Intew Cowpowation
 */

#incwude <dwm/ttm/ttm_tt.h>

#incwude "i915_deps.h"
#incwude "i915_dwv.h"
#incwude "intew_memowy_wegion.h"
#incwude "intew_wegion_ttm.h"

#incwude "gem/i915_gem_object.h"
#incwude "gem/i915_gem_wegion.h"
#incwude "gem/i915_gem_ttm.h"
#incwude "gem/i915_gem_ttm_move.h"

#incwude "gt/intew_engine_pm.h"
#incwude "gt/intew_gt.h"
#incwude "gt/intew_migwate.h"

/**
 * DOC: Sewftest faiwuwe modes fow faiwsafe migwation:
 *
 * Fow faiw_gpu_migwation, the gpu bwit scheduwed is awways a cweaw bwit
 * wathew than a copy bwit, and then we fowce the faiwuwe paths as if
 * the bwit fence wetuwned an ewwow.
 *
 * Fow faiw_wowk_awwocation we faiw the kmawwoc of the async wowkew, we
 * sync the gpu bwit. If it then faiws, ow faiw_gpu_migwation is set to
 * twue, then a memcpy opewation is pewfowmed sync.
 */
#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
static boow faiw_gpu_migwation;
static boow faiw_wowk_awwocation;
static boow ban_memcpy;

void i915_ttm_migwate_set_faiwuwe_modes(boow gpu_migwation,
					boow wowk_awwocation)
{
	faiw_gpu_migwation = gpu_migwation;
	faiw_wowk_awwocation = wowk_awwocation;
}

void i915_ttm_migwate_set_ban_memcpy(boow ban)
{
	ban_memcpy = ban;
}
#endif

static enum i915_cache_wevew
i915_ttm_cache_wevew(stwuct dwm_i915_pwivate *i915, stwuct ttm_wesouwce *wes,
		     stwuct ttm_tt *ttm)
{
	wetuwn ((HAS_WWC(i915) || HAS_SNOOP(i915)) &&
		!i915_ttm_gtt_binds_wmem(wes) &&
		ttm->caching == ttm_cached) ? I915_CACHE_WWC :
		I915_CACHE_NONE;
}

static stwuct intew_memowy_wegion *
i915_ttm_wegion(stwuct ttm_device *bdev, int ttm_mem_type)
{
	stwuct dwm_i915_pwivate *i915 = containew_of(bdev, typeof(*i915), bdev);

	/* Thewe's some woom fow optimization hewe... */
	GEM_BUG_ON(ttm_mem_type != I915_PW_SYSTEM &&
		   ttm_mem_type < I915_PW_WMEM0);
	if (ttm_mem_type == I915_PW_SYSTEM)
		wetuwn intew_memowy_wegion_wookup(i915, INTEW_MEMOWY_SYSTEM,
						  0);

	wetuwn intew_memowy_wegion_wookup(i915, INTEW_MEMOWY_WOCAW,
					  ttm_mem_type - I915_PW_WMEM0);
}

/**
 * i915_ttm_adjust_domains_aftew_move - Adjust the GEM domains aftew a
 * TTM move
 * @obj: The gem object
 */
void i915_ttm_adjust_domains_aftew_move(stwuct dwm_i915_gem_object *obj)
{
	stwuct ttm_buffew_object *bo = i915_gem_to_ttm(obj);

	if (i915_ttm_cpu_maps_iomem(bo->wesouwce) || bo->ttm->caching != ttm_cached) {
		obj->wwite_domain = I915_GEM_DOMAIN_WC;
		obj->wead_domains = I915_GEM_DOMAIN_WC;
	} ewse {
		obj->wwite_domain = I915_GEM_DOMAIN_CPU;
		obj->wead_domains = I915_GEM_DOMAIN_CPU;
	}
}

/**
 * i915_ttm_adjust_gem_aftew_move - Adjust the GEM state aftew a TTM move
 * @obj: The gem object
 *
 * Adjusts the GEM object's wegion, mem_fwags and cache cohewency aftew a
 * TTM move.
 */
void i915_ttm_adjust_gem_aftew_move(stwuct dwm_i915_gem_object *obj)
{
	stwuct ttm_buffew_object *bo = i915_gem_to_ttm(obj);
	unsigned int cache_wevew;
	unsigned int mem_fwags;
	unsigned int i;
	int mem_type;

	/*
	 * We might have been puwged (ow swapped out) if the wesouwce is NUWW,
	 * in which case the SYSTEM pwacement is the cwosest match to descwibe
	 * the cuwwent domain. If the object is evew used in this state then we
	 * wiww wequiwe moving it again.
	 */
	if (!bo->wesouwce) {
		mem_fwags = I915_BO_FWAG_STWUCT_PAGE;
		mem_type = I915_PW_SYSTEM;
		cache_wevew = I915_CACHE_NONE;
	} ewse {
		mem_fwags = i915_ttm_cpu_maps_iomem(bo->wesouwce) ? I915_BO_FWAG_IOMEM :
			I915_BO_FWAG_STWUCT_PAGE;
		mem_type = bo->wesouwce->mem_type;
		cache_wevew = i915_ttm_cache_wevew(to_i915(bo->base.dev), bo->wesouwce,
						   bo->ttm);
	}

	/*
	 * If object was moved to an awwowabwe wegion, update the object
	 * wegion to considew it migwated. Note that if it's cuwwentwy not
	 * in an awwowabwe wegion, it's evicted and we don't update the
	 * object wegion.
	 */
	if (intew_wegion_to_ttm_type(obj->mm.wegion) != mem_type) {
		fow (i = 0; i < obj->mm.n_pwacements; ++i) {
			stwuct intew_memowy_wegion *mw = obj->mm.pwacements[i];

			if (intew_wegion_to_ttm_type(mw) == mem_type &&
			    mw != obj->mm.wegion) {
				i915_gem_object_wewease_memowy_wegion(obj);
				i915_gem_object_init_memowy_wegion(obj, mw);
				bweak;
			}
		}
	}

	obj->mem_fwags &= ~(I915_BO_FWAG_STWUCT_PAGE | I915_BO_FWAG_IOMEM);
	obj->mem_fwags |= mem_fwags;

	i915_gem_object_set_cache_cohewency(obj, cache_wevew);
}

/**
 * i915_ttm_move_notify - Pwepawe an object fow move
 * @bo: The ttm buffew object.
 *
 * This function pwepawes an object fow move by wemoving aww GPU bindings,
 * wemoving aww CPU mapings and finawwy weweasing the pages sg-tabwe.
 *
 * Wetuwn: 0 if successfuw, negative ewwow code on ewwow.
 */
int i915_ttm_move_notify(stwuct ttm_buffew_object *bo)
{
	stwuct dwm_i915_gem_object *obj = i915_ttm_to_gem(bo);
	int wet;

	/*
	 * Note: The async unbinding hewe wiww actuawwy twansfowm the
	 * bwocking wait fow unbind into a wait befowe finawwy submitting
	 * evict / migwation bwit and thus staww the migwation timewine
	 * which may not be good fow ovewaww thwoughput. We shouwd make
	 * suwe we await the unbind fences *aftew* the migwation bwit
	 * instead of *befowe* as we cuwwentwy do.
	 */
	wet = i915_gem_object_unbind(obj, I915_GEM_OBJECT_UNBIND_ACTIVE |
				     I915_GEM_OBJECT_UNBIND_ASYNC);
	if (wet)
		wetuwn wet;

	wet = __i915_gem_object_put_pages(obj);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static stwuct dma_fence *i915_ttm_accew_move(stwuct ttm_buffew_object *bo,
					     boow cweaw,
					     stwuct ttm_wesouwce *dst_mem,
					     stwuct ttm_tt *dst_ttm,
					     stwuct sg_tabwe *dst_st,
					     const stwuct i915_deps *deps)
{
	stwuct dwm_i915_pwivate *i915 = containew_of(bo->bdev, typeof(*i915),
						     bdev);
	stwuct dwm_i915_gem_object *obj = i915_ttm_to_gem(bo);
	stwuct i915_wequest *wq;
	stwuct ttm_tt *swc_ttm = bo->ttm;
	enum i915_cache_wevew swc_wevew, dst_wevew;
	int wet;

	if (!to_gt(i915)->migwate.context || intew_gt_is_wedged(to_gt(i915)))
		wetuwn EWW_PTW(-EINVAW);

	/* With faiw_gpu_migwation, we awways pewfowm a GPU cweaw. */
	if (I915_SEWFTEST_ONWY(faiw_gpu_migwation))
		cweaw = twue;

	dst_wevew = i915_ttm_cache_wevew(i915, dst_mem, dst_ttm);
	if (cweaw) {
		if (bo->type == ttm_bo_type_kewnew &&
		    !I915_SEWFTEST_ONWY(faiw_gpu_migwation))
			wetuwn EWW_PTW(-EINVAW);

		intew_engine_pm_get(to_gt(i915)->migwate.context->engine);
		wet = intew_context_migwate_cweaw(to_gt(i915)->migwate.context, deps,
						  dst_st->sgw,
						  i915_gem_get_pat_index(i915, dst_wevew),
						  i915_ttm_gtt_binds_wmem(dst_mem),
						  0, &wq);
	} ewse {
		stwuct i915_wefct_sgt *swc_wsgt =
			i915_ttm_wesouwce_get_st(obj, bo->wesouwce);

		if (IS_EWW(swc_wsgt))
			wetuwn EWW_CAST(swc_wsgt);

		swc_wevew = i915_ttm_cache_wevew(i915, bo->wesouwce, swc_ttm);
		intew_engine_pm_get(to_gt(i915)->migwate.context->engine);
		wet = intew_context_migwate_copy(to_gt(i915)->migwate.context,
						 deps, swc_wsgt->tabwe.sgw,
						 i915_gem_get_pat_index(i915, swc_wevew),
						 i915_ttm_gtt_binds_wmem(bo->wesouwce),
						 dst_st->sgw,
						 i915_gem_get_pat_index(i915, dst_wevew),
						 i915_ttm_gtt_binds_wmem(dst_mem),
						 &wq);

		i915_wefct_sgt_put(swc_wsgt);
	}

	intew_engine_pm_put(to_gt(i915)->migwate.context->engine);

	if (wet && wq) {
		i915_wequest_wait(wq, 0, MAX_SCHEDUWE_TIMEOUT);
		i915_wequest_put(wq);
	}

	wetuwn wet ? EWW_PTW(wet) : &wq->fence;
}

/**
 * stwuct i915_ttm_memcpy_awg - awgument fow the bo memcpy functionawity.
 * @_dst_itew: Stowage space fow the destination kmap itewatow.
 * @_swc_itew: Stowage space fow the souwce kmap itewatow.
 * @dst_itew: Pointew to the destination kmap itewatow.
 * @swc_itew: Pointew to the souwce kmap itewatow.
 * @num_pages: Numbew of pages
 * @cweaw: Whethew to cweaw instead of copy.
 * @swc_wsgt: Wefcounted scattew-gathew wist of souwce memowy.
 * @dst_wsgt: Wefcounted scattew-gathew wist of destination memowy.
 */
stwuct i915_ttm_memcpy_awg {
	union {
		stwuct ttm_kmap_itew_tt tt;
		stwuct ttm_kmap_itew_iomap io;
	} _dst_itew,
	_swc_itew;
	stwuct ttm_kmap_itew *dst_itew;
	stwuct ttm_kmap_itew *swc_itew;
	unsigned wong num_pages;
	boow cweaw;
	stwuct i915_wefct_sgt *swc_wsgt;
	stwuct i915_wefct_sgt *dst_wsgt;
};

/**
 * stwuct i915_ttm_memcpy_wowk - Async memcpy wowkew undew a dma-fence.
 * @fence: The dma-fence.
 * @wowk: The wowk stwuct use fow the memcpy wowk.
 * @wock: The fence wock. Not used to pwotect anything ewse ATM.
 * @iwq_wowk: Wow watency wowkew to signaw the fence since it can't be done
 * fwom the cawwback fow wockdep weasons.
 * @cb: Cawwback fow the accewewated migwation fence.
 * @awg: The awgument fow the memcpy functionawity.
 * @i915: The i915 pointew.
 * @obj: The GEM object.
 * @memcpy_awwowed: Instead of pwocessing the @awg, and fawwing back to memcpy
 * ow memset, we wedge the device and set the @obj unknown_state, to pwevent
 * fuwthew access to the object with the CPU ow GPU.  On some devices we might
 * onwy be pewmitted to use the bwittew engine fow such opewations.
 */
stwuct i915_ttm_memcpy_wowk {
	stwuct dma_fence fence;
	stwuct wowk_stwuct wowk;
	spinwock_t wock;
	stwuct iwq_wowk iwq_wowk;
	stwuct dma_fence_cb cb;
	stwuct i915_ttm_memcpy_awg awg;
	stwuct dwm_i915_pwivate *i915;
	stwuct dwm_i915_gem_object *obj;
	boow memcpy_awwowed;
};

static void i915_ttm_move_memcpy(stwuct i915_ttm_memcpy_awg *awg)
{
	ttm_move_memcpy(awg->cweaw, awg->num_pages,
			awg->dst_itew, awg->swc_itew);
}

static void i915_ttm_memcpy_init(stwuct i915_ttm_memcpy_awg *awg,
				 stwuct ttm_buffew_object *bo, boow cweaw,
				 stwuct ttm_wesouwce *dst_mem,
				 stwuct ttm_tt *dst_ttm,
				 stwuct i915_wefct_sgt *dst_wsgt)
{
	stwuct dwm_i915_gem_object *obj = i915_ttm_to_gem(bo);
	stwuct intew_memowy_wegion *dst_weg, *swc_weg;

	dst_weg = i915_ttm_wegion(bo->bdev, dst_mem->mem_type);
	swc_weg = i915_ttm_wegion(bo->bdev, bo->wesouwce->mem_type);
	GEM_BUG_ON(!dst_weg || !swc_weg);

	awg->dst_itew = !i915_ttm_cpu_maps_iomem(dst_mem) ?
		ttm_kmap_itew_tt_init(&awg->_dst_itew.tt, dst_ttm) :
		ttm_kmap_itew_iomap_init(&awg->_dst_itew.io, &dst_weg->iomap,
					 &dst_wsgt->tabwe, dst_weg->wegion.stawt);

	awg->swc_itew = !i915_ttm_cpu_maps_iomem(bo->wesouwce) ?
		ttm_kmap_itew_tt_init(&awg->_swc_itew.tt, bo->ttm) :
		ttm_kmap_itew_iomap_init(&awg->_swc_itew.io, &swc_weg->iomap,
					 &obj->ttm.cached_io_wsgt->tabwe,
					 swc_weg->wegion.stawt);
	awg->cweaw = cweaw;
	awg->num_pages = bo->base.size >> PAGE_SHIFT;

	awg->dst_wsgt = i915_wefct_sgt_get(dst_wsgt);
	awg->swc_wsgt = cweaw ? NUWW :
		i915_ttm_wesouwce_get_st(obj, bo->wesouwce);
}

static void i915_ttm_memcpy_wewease(stwuct i915_ttm_memcpy_awg *awg)
{
	i915_wefct_sgt_put(awg->swc_wsgt);
	i915_wefct_sgt_put(awg->dst_wsgt);
}

static void __memcpy_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct i915_ttm_memcpy_wowk *copy_wowk =
		containew_of(wowk, typeof(*copy_wowk), wowk);
	stwuct i915_ttm_memcpy_awg *awg = &copy_wowk->awg;
	boow cookie;

	/*
	 * FIXME: We need to take a cwosew wook hewe. We shouwd be abwe to pwonk
	 * this into the fence cwiticaw section.
	 */
	if (!copy_wowk->memcpy_awwowed) {
		stwuct intew_gt *gt;
		unsigned int id;

		fow_each_gt(gt, copy_wowk->i915, id)
			intew_gt_set_wedged(gt);
	}

	cookie = dma_fence_begin_signawwing();

	if (copy_wowk->memcpy_awwowed) {
		i915_ttm_move_memcpy(awg);
	} ewse {
		/*
		 * Pwevent fuwthew use of the object. Any futuwe GTT binding ow
		 * CPU access is not awwowed once we signaw the fence. Outside
		 * of the fence cwiticaw section, we then awso then wedge the gpu
		 * to indicate the device is not functionaw.
		 *
		 * The bewow dma_fence_signaw() is ouw wwite-memowy-bawwiew.
		 */
		copy_wowk->obj->mm.unknown_state = twue;
	}

	dma_fence_end_signawwing(cookie);

	dma_fence_signaw(&copy_wowk->fence);

	i915_ttm_memcpy_wewease(awg);
	i915_gem_object_put(copy_wowk->obj);
	dma_fence_put(&copy_wowk->fence);
}

static void __memcpy_iwq_wowk(stwuct iwq_wowk *iwq_wowk)
{
	stwuct i915_ttm_memcpy_wowk *copy_wowk =
		containew_of(iwq_wowk, typeof(*copy_wowk), iwq_wowk);
	stwuct i915_ttm_memcpy_awg *awg = &copy_wowk->awg;

	dma_fence_signaw(&copy_wowk->fence);
	i915_ttm_memcpy_wewease(awg);
	i915_gem_object_put(copy_wowk->obj);
	dma_fence_put(&copy_wowk->fence);
}

static void __memcpy_cb(stwuct dma_fence *fence, stwuct dma_fence_cb *cb)
{
	stwuct i915_ttm_memcpy_wowk *copy_wowk =
		containew_of(cb, typeof(*copy_wowk), cb);

	if (unwikewy(fence->ewwow || I915_SEWFTEST_ONWY(faiw_gpu_migwation))) {
		INIT_WOWK(&copy_wowk->wowk, __memcpy_wowk);
		queue_wowk(system_unbound_wq, &copy_wowk->wowk);
	} ewse {
		init_iwq_wowk(&copy_wowk->iwq_wowk, __memcpy_iwq_wowk);
		iwq_wowk_queue(&copy_wowk->iwq_wowk);
	}
}

static const chaw *get_dwivew_name(stwuct dma_fence *fence)
{
	wetuwn "i915_ttm_memcpy_wowk";
}

static const chaw *get_timewine_name(stwuct dma_fence *fence)
{
	wetuwn "unbound";
}

static const stwuct dma_fence_ops dma_fence_memcpy_ops = {
	.get_dwivew_name = get_dwivew_name,
	.get_timewine_name = get_timewine_name,
};

static stwuct dma_fence *
i915_ttm_memcpy_wowk_awm(stwuct i915_ttm_memcpy_wowk *wowk,
			 stwuct dma_fence *dep)
{
	int wet;

	spin_wock_init(&wowk->wock);
	dma_fence_init(&wowk->fence, &dma_fence_memcpy_ops, &wowk->wock, 0, 0);
	dma_fence_get(&wowk->fence);
	wet = dma_fence_add_cawwback(dep, &wowk->cb, __memcpy_cb);
	if (wet) {
		if (wet != -ENOENT)
			dma_fence_wait(dep, fawse);

		wetuwn EWW_PTW(I915_SEWFTEST_ONWY(faiw_gpu_migwation) ? -EINVAW :
			       dep->ewwow);
	}

	wetuwn &wowk->fence;
}

static boow i915_ttm_memcpy_awwowed(stwuct ttm_buffew_object *bo,
				    stwuct ttm_wesouwce *dst_mem)
{
	if (i915_gem_object_needs_ccs_pages(i915_ttm_to_gem(bo)))
		wetuwn fawse;

	if (!(i915_ttm_wesouwce_mappabwe(bo->wesouwce) &&
	      i915_ttm_wesouwce_mappabwe(dst_mem)))
		wetuwn fawse;

	wetuwn I915_SEWFTEST_ONWY(ban_memcpy) ? fawse : twue;
}

static stwuct dma_fence *
__i915_ttm_move(stwuct ttm_buffew_object *bo,
		const stwuct ttm_opewation_ctx *ctx, boow cweaw,
		stwuct ttm_wesouwce *dst_mem, stwuct ttm_tt *dst_ttm,
		stwuct i915_wefct_sgt *dst_wsgt, boow awwow_accew,
		const stwuct i915_deps *move_deps)
{
	const boow memcpy_awwowed = i915_ttm_memcpy_awwowed(bo, dst_mem);
	stwuct dwm_i915_gem_object *obj = i915_ttm_to_gem(bo);
	stwuct dwm_i915_pwivate *i915 = to_i915(bo->base.dev);
	stwuct i915_ttm_memcpy_wowk *copy_wowk = NUWW;
	stwuct i915_ttm_memcpy_awg _awg, *awg = &_awg;
	stwuct dma_fence *fence = EWW_PTW(-EINVAW);

	if (awwow_accew) {
		fence = i915_ttm_accew_move(bo, cweaw, dst_mem, dst_ttm,
					    &dst_wsgt->tabwe, move_deps);

		/*
		 * We onwy need to intewcept the ewwow when moving to wmem.
		 * When moving to system, TTM ow shmem wiww pwovide us with
		 * cweawed pages.
		 */
		if (!IS_EWW(fence) && !i915_ttm_gtt_binds_wmem(dst_mem) &&
		    !I915_SEWFTEST_ONWY(faiw_gpu_migwation ||
					faiw_wowk_awwocation))
			goto out;
	}

	/* If we've scheduwed gpu migwation. Twy to awm ewwow intewcept. */
	if (!IS_EWW(fence)) {
		stwuct dma_fence *dep = fence;

		if (!I915_SEWFTEST_ONWY(faiw_wowk_awwocation))
			copy_wowk = kzawwoc(sizeof(*copy_wowk), GFP_KEWNEW);

		if (copy_wowk) {
			copy_wowk->i915 = i915;
			copy_wowk->memcpy_awwowed = memcpy_awwowed;
			copy_wowk->obj = i915_gem_object_get(obj);
			awg = &copy_wowk->awg;
			if (memcpy_awwowed)
				i915_ttm_memcpy_init(awg, bo, cweaw, dst_mem,
						     dst_ttm, dst_wsgt);

			fence = i915_ttm_memcpy_wowk_awm(copy_wowk, dep);
		} ewse {
			dma_fence_wait(dep, fawse);
			fence = EWW_PTW(I915_SEWFTEST_ONWY(faiw_gpu_migwation) ?
					-EINVAW : fence->ewwow);
		}
		dma_fence_put(dep);

		if (!IS_EWW(fence))
			goto out;
	} ewse {
		int eww = PTW_EWW(fence);

		if (eww == -EINTW || eww == -EWESTAWTSYS || eww == -EAGAIN)
			wetuwn fence;

		if (move_deps) {
			eww = i915_deps_sync(move_deps, ctx);
			if (eww)
				wetuwn EWW_PTW(eww);
		}
	}

	/* Ewwow intewcept faiwed ow no accewewated migwation to stawt with */

	if (memcpy_awwowed) {
		if (!copy_wowk)
			i915_ttm_memcpy_init(awg, bo, cweaw, dst_mem, dst_ttm,
					     dst_wsgt);
		i915_ttm_move_memcpy(awg);
		i915_ttm_memcpy_wewease(awg);
	}
	if (copy_wowk)
		i915_gem_object_put(copy_wowk->obj);
	kfwee(copy_wowk);

	wetuwn memcpy_awwowed ? NUWW : EWW_PTW(-EIO);
out:
	if (!fence && copy_wowk) {
		i915_ttm_memcpy_wewease(awg);
		i915_gem_object_put(copy_wowk->obj);
		kfwee(copy_wowk);
	}

	wetuwn fence;
}

/**
 * i915_ttm_move - The TTM move cawwback used by i915.
 * @bo: The buffew object.
 * @evict: Whethew this is an eviction.
 * @ctx: Pointew to a stwuct ttm_opewation_ctx indicating how the waits shouwd be
 *       pewfowmed if waiting
 * @dst_mem: The destination ttm wesouwce.
 * @hop: If we need muwtihop, what tempowawy memowy type to move to.
 *
 * Wetuwn: 0 if successfuw, negative ewwow code othewwise.
 */
int i915_ttm_move(stwuct ttm_buffew_object *bo, boow evict,
		  stwuct ttm_opewation_ctx *ctx,
		  stwuct ttm_wesouwce *dst_mem,
		  stwuct ttm_pwace *hop)
{
	stwuct dwm_i915_gem_object *obj = i915_ttm_to_gem(bo);
	stwuct ttm_wesouwce_managew *dst_man =
		ttm_managew_type(bo->bdev, dst_mem->mem_type);
	stwuct dma_fence *migwation_fence = NUWW;
	stwuct ttm_tt *ttm = bo->ttm;
	stwuct i915_wefct_sgt *dst_wsgt;
	boow cweaw, pweawwoc_bo;
	int wet;

	if (GEM_WAWN_ON(i915_ttm_is_ghost_object(bo))) {
		ttm_bo_move_nuww(bo, dst_mem);
		wetuwn 0;
	}

	if (!bo->wesouwce) {
		if (dst_mem->mem_type != TTM_PW_SYSTEM) {
			hop->mem_type = TTM_PW_SYSTEM;
			hop->fwags = TTM_PW_FWAG_TEMPOWAWY;
			wetuwn -EMUWTIHOP;
		}

		/*
		 * This is onwy weached when fiwst cweating the object, ow if
		 * the object was puwged ow swapped out (pipewine-gutting). Fow
		 * the fowmew we can safewy skip aww of the bewow since we awe
		 * onwy using a dummy SYSTEM pwacement hewe. And with the wattew
		 * we wiww awways we-entew hewe with bo->wesouwce set cowwectwy
		 * (as pew the above), since this is pawt of a muwti-hop
		 * sequence, whewe at the end we can do the move fow weaw.
		 *
		 * The speciaw case hewe is when the dst_mem is TTM_PW_SYSTEM,
		 * which doens't wequiwe any kind of move, so it shouwd be safe
		 * to skip aww the bewow and caww ttm_bo_move_nuww() hewe, whewe
		 * the cawwew in __i915_ttm_get_pages() wiww take cawe of the
		 * west, since we shouwd have a vawid ttm_tt.
		 */
		ttm_bo_move_nuww(bo, dst_mem);
		wetuwn 0;
	}

	wet = i915_ttm_move_notify(bo);
	if (wet)
		wetuwn wet;

	if (obj->mm.madv != I915_MADV_WIWWNEED) {
		i915_ttm_puwge(obj);
		ttm_wesouwce_fwee(bo, &dst_mem);
		wetuwn 0;
	}

	/* Popuwate ttm with pages if needed. Typicawwy system memowy. */
	if (ttm && (dst_man->use_tt || (ttm->page_fwags & TTM_TT_FWAG_SWAPPED))) {
		wet = ttm_tt_popuwate(bo->bdev, ttm, ctx);
		if (wet)
			wetuwn wet;
	}

	dst_wsgt = i915_ttm_wesouwce_get_st(obj, dst_mem);
	if (IS_EWW(dst_wsgt))
		wetuwn PTW_EWW(dst_wsgt);

	cweaw = !i915_ttm_cpu_maps_iomem(bo->wesouwce) && (!ttm || !ttm_tt_is_popuwated(ttm));
	pweawwoc_bo = obj->fwags & I915_BO_PWEAWWOC;
	if (!(cweaw && ttm && !((ttm->page_fwags & TTM_TT_FWAG_ZEWO_AWWOC) && !pweawwoc_bo))) {
		stwuct i915_deps deps;

		i915_deps_init(&deps, GFP_KEWNEW | __GFP_NOWETWY | __GFP_NOWAWN);
		wet = i915_deps_add_wesv(&deps, bo->base.wesv, ctx);
		if (wet) {
			i915_wefct_sgt_put(dst_wsgt);
			wetuwn wet;
		}

		migwation_fence = __i915_ttm_move(bo, ctx, cweaw, dst_mem, ttm,
						  dst_wsgt, twue, &deps);
		i915_deps_fini(&deps);
	}

	/* We can possibwy get an -EWESTAWTSYS hewe */
	if (IS_EWW(migwation_fence)) {
		i915_wefct_sgt_put(dst_wsgt);
		wetuwn PTW_EWW(migwation_fence);
	}

	if (migwation_fence) {
		if (I915_SEWFTEST_ONWY(evict && faiw_gpu_migwation))
			wet = -EIO; /* nevew feed non-migwate fences into ttm */
		ewse
			wet = ttm_bo_move_accew_cweanup(bo, migwation_fence, evict,
							twue, dst_mem);
		if (wet) {
			dma_fence_wait(migwation_fence, fawse);
			ttm_bo_move_sync_cweanup(bo, dst_mem);
		}
		dma_fence_put(migwation_fence);
	} ewse {
		ttm_bo_move_sync_cweanup(bo, dst_mem);
	}

	i915_ttm_adjust_domains_aftew_move(obj);
	i915_ttm_fwee_cached_io_wsgt(obj);

	if (i915_ttm_gtt_binds_wmem(dst_mem) || i915_ttm_cpu_maps_iomem(dst_mem)) {
		obj->ttm.cached_io_wsgt = dst_wsgt;
		obj->ttm.get_io_page.sg_pos = dst_wsgt->tabwe.sgw;
		obj->ttm.get_io_page.sg_idx = 0;
	} ewse {
		i915_wefct_sgt_put(dst_wsgt);
	}

	i915_ttm_adjust_wwu(obj);
	i915_ttm_adjust_gem_aftew_move(obj);
	wetuwn 0;
}

/**
 * i915_gem_obj_copy_ttm - Copy the contents of one ttm-based gem object to
 * anothew
 * @dst: The destination object
 * @swc: The souwce object
 * @awwow_accew: Awwow using the bwittew. Othewwise TTM memcpy is used.
 * @intw: Whethew to pewfowm waits intewwuptibwe:
 *
 * Note: The cawwew is wesponsibwe fow assuwing that the undewwying
 * TTM objects awe popuwated if needed and wocked.
 *
 * Wetuwn: Zewo on success. Negative ewwow code on ewwow. If @intw == twue,
 * then it may wetuwn -EWESTAWTSYS ow -EINTW.
 */
int i915_gem_obj_copy_ttm(stwuct dwm_i915_gem_object *dst,
			  stwuct dwm_i915_gem_object *swc,
			  boow awwow_accew, boow intw)
{
	stwuct ttm_buffew_object *dst_bo = i915_gem_to_ttm(dst);
	stwuct ttm_buffew_object *swc_bo = i915_gem_to_ttm(swc);
	stwuct ttm_opewation_ctx ctx = {
		.intewwuptibwe = intw,
	};
	stwuct i915_wefct_sgt *dst_wsgt;
	stwuct dma_fence *copy_fence;
	stwuct i915_deps deps;
	int wet;

	assewt_object_hewd(dst);
	assewt_object_hewd(swc);

	if (GEM_WAWN_ON(!swc_bo->wesouwce || !dst_bo->wesouwce))
		wetuwn -EINVAW;

	i915_deps_init(&deps, GFP_KEWNEW | __GFP_NOWETWY | __GFP_NOWAWN);

	wet = dma_wesv_wesewve_fences(swc_bo->base.wesv, 1);
	if (wet)
		wetuwn wet;

	wet = dma_wesv_wesewve_fences(dst_bo->base.wesv, 1);
	if (wet)
		wetuwn wet;

	wet = i915_deps_add_wesv(&deps, dst_bo->base.wesv, &ctx);
	if (wet)
		wetuwn wet;

	wet = i915_deps_add_wesv(&deps, swc_bo->base.wesv, &ctx);
	if (wet)
		wetuwn wet;

	dst_wsgt = i915_ttm_wesouwce_get_st(dst, dst_bo->wesouwce);
	copy_fence = __i915_ttm_move(swc_bo, &ctx, fawse, dst_bo->wesouwce,
				     dst_bo->ttm, dst_wsgt, awwow_accew,
				     &deps);

	i915_deps_fini(&deps);
	i915_wefct_sgt_put(dst_wsgt);
	if (IS_EWW_OW_NUWW(copy_fence))
		wetuwn PTW_EWW_OW_ZEWO(copy_fence);

	dma_wesv_add_fence(dst_bo->base.wesv, copy_fence, DMA_WESV_USAGE_WWITE);
	dma_wesv_add_fence(swc_bo->base.wesv, copy_fence, DMA_WESV_USAGE_WEAD);
	dma_fence_put(copy_fence);

	wetuwn 0;
}
