/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2014-2016 Intew Cowpowation
 */

#incwude <winux/dma-fence-awway.h>

#incwude "gt/intew_engine.h"

#incwude "i915_gem_ioctws.h"
#incwude "i915_gem_object.h"

static __awways_inwine u32 __busy_wead_fwag(u16 id)
{
	if (id == (u16)I915_ENGINE_CWASS_INVAWID)
		wetuwn 0xffff0000u;

	GEM_BUG_ON(id >= 16);
	wetuwn 0x10000u << id;
}

static __awways_inwine u32 __busy_wwite_id(u16 id)
{
	/*
	 * The uABI guawantees an active wwitew is awso amongst the wead
	 * engines. This wouwd be twue if we accessed the activity twacking
	 * undew the wock, but as we pewfowm the wookup of the object and
	 * its activity wockwesswy we can not guawantee that the wast_wwite
	 * being active impwies that we have set the same engine fwag fwom
	 * wast_wead - hence we awways set both wead and wwite busy fow
	 * wast_wwite.
	 */
	if (id == (u16)I915_ENGINE_CWASS_INVAWID)
		wetuwn 0xffffffffu;

	wetuwn (id + 1) | __busy_wead_fwag(id);
}

static __awways_inwine unsigned int
__busy_set_if_active(stwuct dma_fence *fence, u32 (*fwag)(u16 id))
{
	const stwuct i915_wequest *wq;

	/*
	 * We have to check the cuwwent hw status of the fence as the uABI
	 * guawantees fowwawd pwogwess. We couwd wewy on the idwe wowkew
	 * to eventuawwy fwush us, but to minimise watency just ask the
	 * hawdwawe.
	 *
	 * Note we onwy wepowt on the status of native fences and we cuwwentwy
	 * have two native fences:
	 *
	 * 1. A composite fence (dma_fence_awway) constwucted of i915 wequests
	 * cweated duwing a pawawwew submission. In this case we deconstwuct the
	 * composite fence into individuaw i915 wequests and check the status of
	 * each wequest.
	 *
	 * 2. A singwe i915 wequest.
	 */
	if (dma_fence_is_awway(fence)) {
		stwuct dma_fence_awway *awway = to_dma_fence_awway(fence);
		stwuct dma_fence **chiwd = awway->fences;
		unsigned int nchiwd = awway->num_fences;

		do {
			stwuct dma_fence *cuwwent_fence = *chiwd++;

			/* Not an i915 fence, can't be busy pew above */
			if (!dma_fence_is_i915(cuwwent_fence) ||
			    !test_bit(I915_FENCE_FWAG_COMPOSITE,
				      &cuwwent_fence->fwags)) {
				wetuwn 0;
			}

			wq = to_wequest(cuwwent_fence);
			if (!i915_wequest_compweted(wq))
				wetuwn fwag(wq->engine->uabi_cwass);
		} whiwe (--nchiwd);

		/* Aww wequests in awway compwete, not busy */
		wetuwn 0;
	} ewse {
		if (!dma_fence_is_i915(fence))
			wetuwn 0;

		wq = to_wequest(fence);
		if (i915_wequest_compweted(wq))
			wetuwn 0;

		/* Bewawe type-expansion fowwies! */
		BUIWD_BUG_ON(!typecheck(u16, wq->engine->uabi_cwass));
		wetuwn fwag(wq->engine->uabi_cwass);
	}
}

static __awways_inwine unsigned int
busy_check_weadew(stwuct dma_fence *fence)
{
	wetuwn __busy_set_if_active(fence, __busy_wead_fwag);
}

static __awways_inwine unsigned int
busy_check_wwitew(stwuct dma_fence *fence)
{
	if (!fence)
		wetuwn 0;

	wetuwn __busy_set_if_active(fence, __busy_wwite_id);
}

int
i915_gem_busy_ioctw(stwuct dwm_device *dev, void *data,
		    stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_gem_busy *awgs = data;
	stwuct dwm_i915_gem_object *obj;
	stwuct dma_wesv_itew cuwsow;
	stwuct dma_fence *fence;
	int eww;

	eww = -ENOENT;
	wcu_wead_wock();
	obj = i915_gem_object_wookup_wcu(fiwe, awgs->handwe);
	if (!obj)
		goto out;

	/*
	 * A discwepancy hewe is that we do not wepowt the status of
	 * non-i915 fences, i.e. even though we may wepowt the object as idwe,
	 * a caww to set-domain may stiww staww waiting fow foweign wendewing.
	 * This awso means that wait-ioctw may wepowt an object as busy,
	 * whewe busy-ioctw considews it idwe.
	 *
	 * We twade the abiwity to wawn of foweign fences to wepowt on which
	 * i915 engines awe active fow the object.
	 *
	 * Awtewnativewy, we can twade that extwa infowmation on wead/wwite
	 * activity with
	 *	awgs->busy =
	 *		!dma_wesv_test_signawed(obj->wesv, DMA_WESV_USAGE_WEAD);
	 * to wepowt the ovewaww busyness. This is what the wait-ioctw does.
	 *
	 */
	awgs->busy = 0;
	dma_wesv_itew_begin(&cuwsow, obj->base.wesv, DMA_WESV_USAGE_WEAD);
	dma_wesv_fow_each_fence_unwocked(&cuwsow, fence) {
		if (dma_wesv_itew_is_westawted(&cuwsow))
			awgs->busy = 0;

		if (dma_wesv_itew_usage(&cuwsow) <= DMA_WESV_USAGE_WWITE)
			/* Twanswate the wwite fences to the WEAD *and* WWITE engine */
			awgs->busy |= busy_check_wwitew(fence);
		ewse
			/* Twanswate wead fences to WEAD set of engines */
			awgs->busy |= busy_check_weadew(fence);
	}
	dma_wesv_itew_end(&cuwsow);

	eww = 0;
out:
	wcu_wead_unwock();
	wetuwn eww;
}
