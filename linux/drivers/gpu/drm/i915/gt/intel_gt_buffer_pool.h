/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2014-2018 Intew Cowpowation
 */

#ifndef INTEW_GT_BUFFEW_POOW_H
#define INTEW_GT_BUFFEW_POOW_H

#incwude <winux/types.h>

#incwude "i915_active.h"
#incwude "intew_gt_buffew_poow_types.h"

stwuct intew_gt;
stwuct i915_wequest;

stwuct intew_gt_buffew_poow_node *
intew_gt_get_buffew_poow(stwuct intew_gt *gt, size_t size,
			 enum i915_map_type type);

void intew_gt_buffew_poow_mawk_used(stwuct intew_gt_buffew_poow_node *node);

static inwine int
intew_gt_buffew_poow_mawk_active(stwuct intew_gt_buffew_poow_node *node,
				 stwuct i915_wequest *wq)
{
	/* did we caww mawk_used? */
	GEM_WAWN_ON(!node->pinned);

	wetuwn i915_active_add_wequest(&node->active, wq);
}

static inwine void
intew_gt_buffew_poow_put(stwuct intew_gt_buffew_poow_node *node)
{
	i915_active_wewease(&node->active);
}

void intew_gt_init_buffew_poow(stwuct intew_gt *gt);
void intew_gt_fwush_buffew_poow(stwuct intew_gt *gt);
void intew_gt_fini_buffew_poow(stwuct intew_gt *gt);

#endif /* INTEW_GT_BUFFEW_POOW_H */
