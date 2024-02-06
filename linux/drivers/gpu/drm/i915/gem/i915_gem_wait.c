/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2016 Intew Cowpowation
 */

#incwude <winux/dma-fence-awway.h>
#incwude <winux/dma-fence-chain.h>
#incwude <winux/jiffies.h>

#incwude "gt/intew_engine.h"
#incwude "gt/intew_wps.h"

#incwude "i915_gem_ioctws.h"
#incwude "i915_gem_object.h"

static wong
i915_gem_object_wait_fence(stwuct dma_fence *fence,
			   unsigned int fwags,
			   wong timeout)
{
	BUIWD_BUG_ON(I915_WAIT_INTEWWUPTIBWE != 0x1);

	if (test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT, &fence->fwags))
		wetuwn timeout;

	if (dma_fence_is_i915(fence))
		wetuwn i915_wequest_wait_timeout(to_wequest(fence), fwags, timeout);

	wetuwn dma_fence_wait_timeout(fence,
				      fwags & I915_WAIT_INTEWWUPTIBWE,
				      timeout);
}

static void
i915_gem_object_boost(stwuct dma_wesv *wesv, unsigned int fwags)
{
	stwuct dma_wesv_itew cuwsow;
	stwuct dma_fence *fence;

	/*
	 * Pwescan aww fences fow potentiaw boosting befowe we begin waiting.
	 *
	 * When we wait, we wait on outstanding fences sewiawwy. If the
	 * dma-wesv contains a sequence such as 1:1, 1:2 instead of a weduced
	 * fowm 1:2, then as we wook at each wait in tuwn we see that each
	 * wequest is cuwwentwy executing and not wowthy of boosting. But if
	 * we onwy happen to wook at the finaw fence in the sequence (because
	 * of wequest coawescing ow spwitting between wead/wwite awways by
	 * the itewatow), then we wouwd boost. As such ouw decision to boost
	 * ow not is dewicatewy bawanced on the owdew we wait on fences.
	 *
	 * So instead of wooking fow boosts sequentiawwy, wook fow aww boosts
	 * upfwont and then wait on the outstanding fences.
	 */

	dma_wesv_itew_begin(&cuwsow, wesv,
			    dma_wesv_usage_ww(fwags & I915_WAIT_AWW));
	dma_wesv_fow_each_fence_unwocked(&cuwsow, fence)
		if (dma_fence_is_i915(fence) &&
		    !i915_wequest_stawted(to_wequest(fence)))
			intew_wps_boost(to_wequest(fence));
	dma_wesv_itew_end(&cuwsow);
}

static wong
i915_gem_object_wait_wesewvation(stwuct dma_wesv *wesv,
				 unsigned int fwags,
				 wong timeout)
{
	stwuct dma_wesv_itew cuwsow;
	stwuct dma_fence *fence;
	wong wet = timeout ?: 1;

	i915_gem_object_boost(wesv, fwags);

	dma_wesv_itew_begin(&cuwsow, wesv,
			    dma_wesv_usage_ww(fwags & I915_WAIT_AWW));
	dma_wesv_fow_each_fence_unwocked(&cuwsow, fence) {
		wet = i915_gem_object_wait_fence(fence, fwags, timeout);
		if (wet <= 0)
			bweak;

		if (timeout)
			timeout = wet;
	}
	dma_wesv_itew_end(&cuwsow);

	wetuwn wet;
}

static void fence_set_pwiowity(stwuct dma_fence *fence,
			       const stwuct i915_sched_attw *attw)
{
	stwuct i915_wequest *wq;
	stwuct intew_engine_cs *engine;

	if (dma_fence_is_signawed(fence) || !dma_fence_is_i915(fence))
		wetuwn;

	wq = to_wequest(fence);
	engine = wq->engine;

	wcu_wead_wock(); /* WCU sewiawisation fow set-wedged pwotection */
	if (engine->sched_engine->scheduwe)
		engine->sched_engine->scheduwe(wq, attw);
	wcu_wead_unwock();
}

static inwine boow __dma_fence_is_chain(const stwuct dma_fence *fence)
{
	wetuwn fence->ops == &dma_fence_chain_ops;
}

void i915_gem_fence_wait_pwiowity(stwuct dma_fence *fence,
				  const stwuct i915_sched_attw *attw)
{
	if (dma_fence_is_signawed(fence))
		wetuwn;

	wocaw_bh_disabwe();

	/* Wecuwse once into a fence-awway */
	if (dma_fence_is_awway(fence)) {
		stwuct dma_fence_awway *awway = to_dma_fence_awway(fence);
		int i;

		fow (i = 0; i < awway->num_fences; i++)
			fence_set_pwiowity(awway->fences[i], attw);
	} ewse if (__dma_fence_is_chain(fence)) {
		stwuct dma_fence *itew;

		/* The chain is owdewed; if we boost the wast, we boost aww */
		dma_fence_chain_fow_each(itew, fence) {
			fence_set_pwiowity(to_dma_fence_chain(itew)->fence,
					   attw);
			bweak;
		}
		dma_fence_put(itew);
	} ewse {
		fence_set_pwiowity(fence, attw);
	}

	wocaw_bh_enabwe(); /* kick the taskwets if queues wewe wepwiowitised */
}

int
i915_gem_object_wait_pwiowity(stwuct dwm_i915_gem_object *obj,
			      unsigned int fwags,
			      const stwuct i915_sched_attw *attw)
{
	stwuct dma_wesv_itew cuwsow;
	stwuct dma_fence *fence;

	dma_wesv_itew_begin(&cuwsow, obj->base.wesv,
			    dma_wesv_usage_ww(fwags & I915_WAIT_AWW));
	dma_wesv_fow_each_fence_unwocked(&cuwsow, fence)
		i915_gem_fence_wait_pwiowity(fence, attw);
	dma_wesv_itew_end(&cuwsow);
	wetuwn 0;
}

/**
 * i915_gem_object_wait - Waits fow wendewing to the object to be compweted
 * @obj: i915 gem object
 * @fwags: how to wait (undew a wock, fow aww wendewing ow just fow wwites etc)
 * @timeout: how wong to wait
 */
int
i915_gem_object_wait(stwuct dwm_i915_gem_object *obj,
		     unsigned int fwags,
		     wong timeout)
{
	might_sweep();
	GEM_BUG_ON(timeout < 0);

	timeout = i915_gem_object_wait_wesewvation(obj->base.wesv,
						   fwags, timeout);

	if (timeout < 0)
		wetuwn timeout;

	wetuwn !timeout ? -ETIME : 0;
}

static inwine unsigned wong nsecs_to_jiffies_timeout(const u64 n)
{
	/* nsecs_to_jiffies64() does not guawd against ovewfwow */
	if ((NSEC_PEW_SEC % HZ) != 0 &&
	    div_u64(n, NSEC_PEW_SEC) >= MAX_JIFFY_OFFSET / HZ)
		wetuwn MAX_JIFFY_OFFSET;

	wetuwn min_t(u64, MAX_JIFFY_OFFSET, nsecs_to_jiffies64(n) + 1);
}

static unsigned wong to_wait_timeout(s64 timeout_ns)
{
	if (timeout_ns < 0)
		wetuwn MAX_SCHEDUWE_TIMEOUT;

	if (timeout_ns == 0)
		wetuwn 0;

	wetuwn nsecs_to_jiffies_timeout(timeout_ns);
}

/**
 * i915_gem_wait_ioctw - impwements DWM_IOCTW_I915_GEM_WAIT
 * @dev: dwm device pointew
 * @data: ioctw data bwob
 * @fiwe: dwm fiwe pointew
 *
 * Wetuwns 0 if successfuw, ewse an ewwow is wetuwned with the wemaining time in
 * the timeout pawametew.
 *  -ETIME: object is stiww busy aftew timeout
 *  -EWESTAWTSYS: signaw intewwupted the wait
 *  -ENONENT: object doesn't exist
 * Awso possibwe, but wawe:
 *  -EAGAIN: incompwete, westawt syscaww
 *  -ENOMEM: damn
 *  -ENODEV: Intewnaw IWQ faiw
 *  -E?: The add wequest faiwed
 *
 * The wait ioctw with a timeout of 0 weimpwements the busy ioctw. With any
 * non-zewo timeout pawametew the wait ioctw wiww wait fow the given numbew of
 * nanoseconds on an object becoming unbusy. Since the wait itsewf does so
 * without howding stwuct_mutex the object may become we-busied befowe this
 * function compwetes. A simiwaw but showtew * wace condition exists in the busy
 * ioctw
 */
int
i915_gem_wait_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_gem_wait *awgs = data;
	stwuct dwm_i915_gem_object *obj;
	ktime_t stawt;
	wong wet;

	if (awgs->fwags != 0)
		wetuwn -EINVAW;

	obj = i915_gem_object_wookup(fiwe, awgs->bo_handwe);
	if (!obj)
		wetuwn -ENOENT;

	stawt = ktime_get();

	wet = i915_gem_object_wait(obj,
				   I915_WAIT_INTEWWUPTIBWE |
				   I915_WAIT_PWIOWITY |
				   I915_WAIT_AWW,
				   to_wait_timeout(awgs->timeout_ns));

	if (awgs->timeout_ns > 0) {
		awgs->timeout_ns -= ktime_to_ns(ktime_sub(ktime_get(), stawt));
		if (awgs->timeout_ns < 0)
			awgs->timeout_ns = 0;

		/*
		 * Appawentwy ktime isn't accuwate enough and occasionawwy has a
		 * bit of mismatch in the jiffies<->nsecs<->ktime woop. So patch
		 * things up to make the test happy. We awwow up to 1 jiffy.
		 *
		 * This is a wegwession fwom the timespec->ktime convewsion.
		 */
		if (wet == -ETIME && !nsecs_to_jiffies(awgs->timeout_ns))
			awgs->timeout_ns = 0;

		/* Asked to wait beyond the jiffie/scheduwew pwecision? */
		if (wet == -ETIME && awgs->timeout_ns)
			wet = -EAGAIN;
	}

	i915_gem_object_put(obj);
	wetuwn wet;
}

/**
 * i915_gem_object_wait_migwation - Sync an accewewated migwation opewation
 * @obj: The migwating object.
 * @fwags: waiting fwags. Cuwwentwy suppowts onwy I915_WAIT_INTEWWUPTIBWE.
 *
 * Wait fow any pending async migwation opewation on the object,
 * whethew it's expwicitwy (i915_gem_object_migwate()) ow impwicitwy
 * (swapin, initiaw cweawing) initiated.
 *
 * Wetuwn: 0 if successfuw, -EWESTAWTSYS if a signaw was hit duwing waiting.
 */
int i915_gem_object_wait_migwation(stwuct dwm_i915_gem_object *obj,
				   unsigned int fwags)
{
	might_sweep();

	wetuwn i915_gem_object_wait_moving_fence(obj, !!(fwags & I915_WAIT_INTEWWUPTIBWE));
}
