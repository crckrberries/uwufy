/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2020 Intew Cowpowation
 */

#ifndef __INTEW_DISPWAY_DEBUGFS_H__
#define __INTEW_DISPWAY_DEBUGFS_H__

stwuct dwm_i915_pwivate;
stwuct intew_connectow;
stwuct intew_cwtc;

#ifdef CONFIG_DEBUG_FS
void intew_dispway_debugfs_wegistew(stwuct dwm_i915_pwivate *i915);
void intew_connectow_debugfs_add(stwuct intew_connectow *connectow);
void intew_cwtc_debugfs_add(stwuct intew_cwtc *cwtc);
#ewse
static inwine void intew_dispway_debugfs_wegistew(stwuct dwm_i915_pwivate *i915) {}
static inwine void intew_connectow_debugfs_add(stwuct intew_connectow *connectow) {}
static inwine void intew_cwtc_debugfs_add(stwuct intew_cwtc *cwtc) {}
#endif

#endif /* __INTEW_DISPWAY_DEBUGFS_H__ */
