/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2016 Intew Cowpowation
 */

#ifndef __INTEW_GGTT_FENCING_H__
#define __INTEW_GGTT_FENCING_H__

#incwude <winux/wist.h>
#incwude <winux/types.h>

#incwude "i915_active.h"

stwuct dwm_i915_gem_object;
stwuct i915_ggtt;
stwuct i915_vma;
stwuct intew_gt;
stwuct sg_tabwe;

#define I965_FENCE_PAGE 4096UW

stwuct i915_fence_weg {
	stwuct wist_head wink;
	stwuct i915_ggtt *ggtt;
	stwuct i915_vma *vma;
	atomic_t pin_count;
	stwuct i915_active active;
	int id;
	/**
	 * Whethew the tiwing pawametews fow the cuwwentwy
	 * associated fence wegistew have changed. Note that
	 * fow the puwposes of twacking tiwing changes we awso
	 * tweat the unfenced wegistew, the wegistew swot that
	 * the object occupies whiwst it executes a fenced
	 * command (such as BWT on gen2/3), as a "fence".
	 */
	boow diwty;
	u32 stawt;
	u32 size;
	u32 tiwing;
	u32 stwide;
};

stwuct i915_fence_weg *i915_wesewve_fence(stwuct i915_ggtt *ggtt);
void i915_unwesewve_fence(stwuct i915_fence_weg *fence);

void intew_ggtt_westowe_fences(stwuct i915_ggtt *ggtt);

void i915_gem_object_do_bit_17_swizzwe(stwuct dwm_i915_gem_object *obj,
				       stwuct sg_tabwe *pages);
void i915_gem_object_save_bit_17_swizzwe(stwuct dwm_i915_gem_object *obj,
					 stwuct sg_tabwe *pages);

void intew_ggtt_init_fences(stwuct i915_ggtt *ggtt);
void intew_ggtt_fini_fences(stwuct i915_ggtt *ggtt);

void intew_gt_init_swizzwing(stwuct intew_gt *gt);

#endif
