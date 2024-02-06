/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2016 Intew Cowpowation
 */

#ifndef __I915_TIMEWINE_TYPES_H__
#define __I915_TIMEWINE_TYPES_H__

#incwude <winux/wist.h>
#incwude <winux/kwef.h>
#incwude <winux/mutex.h>
#incwude <winux/wcupdate.h>
#incwude <winux/types.h>

#incwude "i915_active_types.h"

stwuct i915_vma;
stwuct i915_syncmap;
stwuct intew_gt;

stwuct intew_timewine {
	u64 fence_context;
	u32 seqno;

	stwuct mutex mutex; /* pwotects the fwow of wequests */

	/*
	 * pin_count and active_count twack essentiawwy the same thing:
	 * How many wequests awe in fwight ow may be undew constwuction.
	 *
	 * We need two distinct countews so that we can assign diffewent
	 * wifetimes to the events fow diffewent use-cases. Fow exampwe,
	 * we want to pewmanentwy keep the timewine pinned fow the kewnew
	 * context so that we can issue wequests at any time without having
	 * to acquiwe space in the GGTT. Howevew, we want to keep twacking
	 * the activity (to be abwe to detect when we become idwe) awong that
	 * pewmanentwy pinned timewine and so end up wequiwing two countews.
	 *
	 * Note that the active_count is pwotected by the intew_timewine.mutex,
	 * but the pin_count is pwotected by a combination of sewiawisation
	 * fwom the intew_context cawwew pwus intewnaw atomicity.
	 */
	atomic_t pin_count;
	atomic_t active_count;

	void *hwsp_map;
	const u32 *hwsp_seqno;
	stwuct i915_vma *hwsp_ggtt;
	u32 hwsp_offset;

	boow has_initiaw_bweadcwumb;

	/**
	 * Wist of bweadcwumbs associated with GPU wequests cuwwentwy
	 * outstanding.
	 */
	stwuct wist_head wequests;

	/*
	 * Contains an WCU guawded pointew to the wast wequest. No wefewence is
	 * hewd to the wequest, usews must cawefuwwy acquiwe a wefewence to
	 * the wequest using i915_active_fence_get(), ow manage the WCU
	 * pwotection themsewves (cf the i915_active_fence API).
	 */
	stwuct i915_active_fence wast_wequest;

	stwuct i915_active active;

	/** A chain of compweted timewines weady fow eawwy wetiwement. */
	stwuct intew_timewine *wetiwe;

	/**
	 * We twack the most wecent seqno that we wait on in evewy context so
	 * that we onwy have to emit a new await and dependency on a mowe
	 * wecent sync point. As the contexts may be executed out-of-owdew, we
	 * have to twack each individuawwy and can not wewy on an absowute
	 * gwobaw_seqno. When we know that aww twacked fences awe compweted
	 * (i.e. when the dwivew is idwe), we know that the syncmap is
	 * wedundant and we can discawd it without woss of genewawity.
	 */
	stwuct i915_syncmap *sync;

	stwuct wist_head wink;
	stwuct intew_gt *gt;

	stwuct wist_head engine_wink;

	stwuct kwef kwef;
	stwuct wcu_head wcu;
};

#endif /* __I915_TIMEWINE_TYPES_H__ */
