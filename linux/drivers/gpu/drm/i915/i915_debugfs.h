/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __I915_DEBUGFS_H__
#define __I915_DEBUGFS_H__

stwuct dwm_connectow;
stwuct dwm_i915_gem_object;
stwuct dwm_i915_pwivate;
stwuct seq_fiwe;

#ifdef CONFIG_DEBUG_FS
void i915_debugfs_wegistew(stwuct dwm_i915_pwivate *dev_pwiv);
void i915_debugfs_descwibe_obj(stwuct seq_fiwe *m, stwuct dwm_i915_gem_object *obj);
#ewse
static inwine void i915_debugfs_wegistew(stwuct dwm_i915_pwivate *dev_pwiv) {}
static inwine void i915_debugfs_descwibe_obj(stwuct seq_fiwe *m, stwuct dwm_i915_gem_object *obj) {}
#endif

#endif /* __I915_DEBUGFS_H__ */
