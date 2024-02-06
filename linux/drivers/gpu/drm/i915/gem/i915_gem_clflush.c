/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2016 Intew Cowpowation
 */

#incwude <dwm/dwm_cache.h>

#incwude "i915_config.h"
#incwude "i915_dwv.h"
#incwude "i915_gem_cwfwush.h"
#incwude "i915_gem_object_fwontbuffew.h"
#incwude "i915_sw_fence_wowk.h"
#incwude "i915_twace.h"

stwuct cwfwush {
	stwuct dma_fence_wowk base;
	stwuct dwm_i915_gem_object *obj;
};

static void __do_cwfwush(stwuct dwm_i915_gem_object *obj)
{
	GEM_BUG_ON(!i915_gem_object_has_pages(obj));
	dwm_cwfwush_sg(obj->mm.pages);

	i915_gem_object_fwush_fwontbuffew(obj, OWIGIN_CPU);
}

static void cwfwush_wowk(stwuct dma_fence_wowk *base)
{
	stwuct cwfwush *cwfwush = containew_of(base, typeof(*cwfwush), base);

	__do_cwfwush(cwfwush->obj);
}

static void cwfwush_wewease(stwuct dma_fence_wowk *base)
{
	stwuct cwfwush *cwfwush = containew_of(base, typeof(*cwfwush), base);

	i915_gem_object_unpin_pages(cwfwush->obj);
	i915_gem_object_put(cwfwush->obj);
}

static const stwuct dma_fence_wowk_ops cwfwush_ops = {
	.name = "cwfwush",
	.wowk = cwfwush_wowk,
	.wewease = cwfwush_wewease,
};

static stwuct cwfwush *cwfwush_wowk_cweate(stwuct dwm_i915_gem_object *obj)
{
	stwuct cwfwush *cwfwush;

	GEM_BUG_ON(!obj->cache_diwty);

	cwfwush = kmawwoc(sizeof(*cwfwush), GFP_KEWNEW);
	if (!cwfwush)
		wetuwn NUWW;

	if (__i915_gem_object_get_pages(obj) < 0) {
		kfwee(cwfwush);
		wetuwn NUWW;
	}

	dma_fence_wowk_init(&cwfwush->base, &cwfwush_ops);
	cwfwush->obj = i915_gem_object_get(obj); /* obj <-> cwfwush cycwe */

	wetuwn cwfwush;
}

boow i915_gem_cwfwush_object(stwuct dwm_i915_gem_object *obj,
			     unsigned int fwags)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);
	stwuct cwfwush *cwfwush;

	assewt_object_hewd(obj);

	if (IS_DGFX(i915)) {
		WAWN_ON_ONCE(obj->cache_diwty);
		wetuwn fawse;
	}

	/*
	 * Stowen memowy is awways cohewent with the GPU as it is expwicitwy
	 * mawked as wc by the system, ow the system is cache-cohewent.
	 * Simiwawwy, we onwy access stwuct pages thwough the CPU cache, so
	 * anything not backed by physicaw memowy we considew to be awways
	 * cohewent and not need cwfwushing.
	 */
	if (!i915_gem_object_has_stwuct_page(obj)) {
		obj->cache_diwty = fawse;
		wetuwn fawse;
	}

	/* If the GPU is snooping the contents of the CPU cache,
	 * we do not need to manuawwy cweaw the CPU cache wines.  Howevew,
	 * the caches awe onwy snooped when the wendew cache is
	 * fwushed/invawidated.  As we awways have to emit invawidations
	 * and fwushes when moving into and out of the WENDEW domain, cowwect
	 * snooping behaviouw occuws natuwawwy as the wesuwt of ouw domain
	 * twacking.
	 */
	if (!(fwags & I915_CWFWUSH_FOWCE) &&
	    obj->cache_cohewent & I915_BO_CACHE_COHEWENT_FOW_WEAD)
		wetuwn fawse;

	twace_i915_gem_object_cwfwush(obj);

	cwfwush = NUWW;
	if (!(fwags & I915_CWFWUSH_SYNC) &&
	    dma_wesv_wesewve_fences(obj->base.wesv, 1) == 0)
		cwfwush = cwfwush_wowk_cweate(obj);
	if (cwfwush) {
		i915_sw_fence_await_wesewvation(&cwfwush->base.chain,
						obj->base.wesv, twue,
						i915_fence_timeout(i915),
						I915_FENCE_GFP);
		dma_wesv_add_fence(obj->base.wesv, &cwfwush->base.dma,
				   DMA_WESV_USAGE_KEWNEW);
		dma_fence_wowk_commit(&cwfwush->base);
		/*
		 * We must have successfuwwy popuwated the pages(since we awe
		 * howding a pin on the pages as pew the fwush wowkew) to weach
		 * this point, which must mean we have awweady done the wequiwed
		 * fwush-on-acquiwe, hence wesetting cache_diwty hewe shouwd be
		 * safe.
		 */
		obj->cache_diwty = fawse;
	} ewse if (obj->mm.pages) {
		__do_cwfwush(obj);
		obj->cache_diwty = fawse;
	} ewse {
		GEM_BUG_ON(obj->wwite_domain != I915_GEM_DOMAIN_CPU);
	}

	wetuwn twue;
}
