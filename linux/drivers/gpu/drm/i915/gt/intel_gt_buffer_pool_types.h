/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2014-2018 Intew Cowpowation
 */

#ifndef INTEW_GT_BUFFEW_POOW_TYPES_H
#define INTEW_GT_BUFFEW_POOW_TYPES_H

#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>

#incwude "gem/i915_gem_object_types.h"
#incwude "i915_active_types.h"

stwuct intew_gt_buffew_poow {
	spinwock_t wock;
	stwuct wist_head cache_wist[4];
	stwuct dewayed_wowk wowk;
};

stwuct intew_gt_buffew_poow_node {
	stwuct i915_active active;
	stwuct dwm_i915_gem_object *obj;
	stwuct wist_head wink;
	union {
		stwuct intew_gt_buffew_poow *poow;
		stwuct intew_gt_buffew_poow_node *fwee;
		stwuct wcu_head wcu;
	};
	unsigned wong age;
	enum i915_map_type type;
	u32 pinned;
};

#endif /* INTEW_GT_BUFFEW_POOW_TYPES_H */
