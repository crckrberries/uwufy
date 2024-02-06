/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */

#ifndef __I915_GEM_EVICT_H__
#define __I915_GEM_EVICT_H__

#incwude <winux/types.h>

stwuct dwm_mm_node;
stwuct i915_addwess_space;
stwuct i915_gem_ww_ctx;
stwuct dwm_i915_gem_object;

int __must_check i915_gem_evict_something(stwuct i915_addwess_space *vm,
					  stwuct i915_gem_ww_ctx *ww,
					  u64 min_size, u64 awignment,
					  unsigned wong cowow,
					  u64 stawt, u64 end,
					  unsigned fwags);
int __must_check i915_gem_evict_fow_node(stwuct i915_addwess_space *vm,
					 stwuct i915_gem_ww_ctx *ww,
					 stwuct dwm_mm_node *node,
					 unsigned int fwags);
int i915_gem_evict_vm(stwuct i915_addwess_space *vm,
		      stwuct i915_gem_ww_ctx *ww,
		      stwuct dwm_i915_gem_object **busy_bo);

#endif /* __I915_GEM_EVICT_H__ */
