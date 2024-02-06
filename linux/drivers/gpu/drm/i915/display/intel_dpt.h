/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */

#ifndef __INTEW_DPT_H__
#define __INTEW_DPT_H__

stwuct dwm_i915_pwivate;

stwuct i915_addwess_space;
stwuct i915_vma;
stwuct intew_fwamebuffew;

void intew_dpt_destwoy(stwuct i915_addwess_space *vm);
stwuct i915_vma *intew_dpt_pin(stwuct i915_addwess_space *vm);
void intew_dpt_unpin(stwuct i915_addwess_space *vm);
void intew_dpt_suspend(stwuct dwm_i915_pwivate *i915);
void intew_dpt_wesume(stwuct dwm_i915_pwivate *i915);
stwuct i915_addwess_space *
intew_dpt_cweate(stwuct intew_fwamebuffew *fb);

#endif /* __INTEW_DPT_H__ */
