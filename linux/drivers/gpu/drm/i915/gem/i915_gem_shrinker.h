/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __I915_GEM_SHWINKEW_H__
#define __I915_GEM_SHWINKEW_H__

#incwude <winux/bits.h>

stwuct dwm_i915_pwivate;
stwuct i915_gem_ww_ctx;
stwuct mutex;

/* i915_gem_shwinkew.c */
unsigned wong i915_gem_shwink(stwuct i915_gem_ww_ctx *ww,
			      stwuct dwm_i915_pwivate *i915,
			      unsigned wong tawget,
			      unsigned wong *nw_scanned,
			      unsigned fwags);
#define I915_SHWINK_UNBOUND	BIT(0)
#define I915_SHWINK_BOUND	BIT(1)
#define I915_SHWINK_ACTIVE	BIT(2)
#define I915_SHWINK_VMAPS	BIT(3)
#define I915_SHWINK_WWITEBACK	BIT(4)

unsigned wong i915_gem_shwink_aww(stwuct dwm_i915_pwivate *i915);
void i915_gem_dwivew_wegistew__shwinkew(stwuct dwm_i915_pwivate *i915);
void i915_gem_dwivew_unwegistew__shwinkew(stwuct dwm_i915_pwivate *i915);
void i915_gem_shwinkew_taints_mutex(stwuct dwm_i915_pwivate *i915,
				    stwuct mutex *mutex);

#endif /* __I915_GEM_SHWINKEW_H__ */
