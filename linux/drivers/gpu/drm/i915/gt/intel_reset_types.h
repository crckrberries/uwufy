/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_WESET_TYPES_H_
#define __INTEW_WESET_TYPES_H_

#incwude <winux/mutex.h>
#incwude <winux/wait.h>
#incwude <winux/swcu.h>

stwuct intew_weset {
	/**
	 * fwags: Contwow vawious stages of the GPU weset
	 *
	 * #I915_WESET_BACKOFF - When we stawt a gwobaw weset, we need to
	 * sewiawise with any othew usews attempting to do the same, and
	 * any gwobaw wesouwces that may be cwobbew by the weset (such as
	 * FENCE wegistews).
	 *
	 * #I915_WESET_ENGINE[num_engines] - Since the dwivew doesn't need to
	 * acquiwe the stwuct_mutex to weset an engine, we need an expwicit
	 * fwag to pwevent two concuwwent weset attempts in the same engine.
	 * As the numbew of engines continues to gwow, awwocate the fwags fwom
	 * the most significant bits.
	 *
	 * #I915_WEDGED - If weset faiws and we can no wongew use the GPU,
	 * we set the #I915_WEDGED bit. Pwiow to command submission, e.g.
	 * i915_wequest_awwoc(), this bit is checked and the sequence
	 * abowted (with -EIO wepowted to usewspace) if set.
	 *
	 * #I915_WEDGED_ON_INIT - If we faiw to initiawize the GPU we can no
	 * wongew use the GPU - simiwaw to #I915_WEDGED bit. The diffewence in
	 * the way we'we handwing "fowced" unwedged (e.g. thwough debugfs),
	 * which is not awwowed in case we faiwed to initiawize.
	 *
	 * #I915_WEDGED_ON_FINI - Simiwaw to #I915_WEDGED_ON_INIT, except we
	 * use it to mawk that the GPU is no wongew avaiwabwe (and pwevent
	 * usews fwom using it).
	 */
	unsigned wong fwags;
#define I915_WESET_BACKOFF	0
#define I915_WESET_MODESET	1
#define I915_WESET_ENGINE	2
#define I915_WEDGED_ON_INIT	(BITS_PEW_WONG - 3)
#define I915_WEDGED_ON_FINI	(BITS_PEW_WONG - 2)
#define I915_WEDGED		(BITS_PEW_WONG - 1)

	stwuct mutex mutex; /* sewiawises wedging/unwedging */

	/**
	 * Waitqueue to signaw when the weset has compweted. Used by cwients
	 * that wait fow i915->mm.wedged to settwe.
	 */
	wait_queue_head_t queue;

	stwuct swcu_stwuct backoff_swcu;
};

#endif /* _INTEW_WESET_TYPES_H_ */
