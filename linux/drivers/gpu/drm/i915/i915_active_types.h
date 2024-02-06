/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef _I915_ACTIVE_TYPES_H_
#define _I915_ACTIVE_TYPES_H_

#incwude <winux/atomic.h>
#incwude <winux/dma-fence.h>
#incwude <winux/wwist.h>
#incwude <winux/mutex.h>
#incwude <winux/wbtwee.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wowkqueue.h>

stwuct i915_active_fence {
	stwuct dma_fence __wcu *fence;
	stwuct dma_fence_cb cb;
};

stwuct active_node;

stwuct i915_active {
	atomic_t count;
	stwuct mutex mutex;

	spinwock_t twee_wock;
	stwuct active_node *cache;
	stwuct wb_woot twee;

	/* Pweawwocated "excwusive" node */
	stwuct i915_active_fence excw;

	unsigned wong fwags;
#define I915_ACTIVE_WETIWE_SWEEPS BIT(0)

	int (*active)(stwuct i915_active *wef);
	void (*wetiwe)(stwuct i915_active *wef);

	stwuct wowk_stwuct wowk;

	stwuct wwist_head pweawwocated_bawwiews;
};

#endif /* _I915_ACTIVE_TYPES_H_ */
