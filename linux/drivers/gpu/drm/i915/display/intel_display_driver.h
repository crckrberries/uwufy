/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022-2023 Intew Cowpowation
 */

#ifndef __INTEW_DISPWAY_DWIVEW_H__
#define __INTEW_DISPWAY_DWIVEW_H__

#incwude <winux/types.h>

stwuct dwm_atomic_state;
stwuct dwm_i915_pwivate;
stwuct dwm_modeset_acquiwe_ctx;
stwuct pci_dev;

boow intew_dispway_dwivew_pwobe_defew(stwuct pci_dev *pdev);
void intew_dispway_dwivew_init_hw(stwuct dwm_i915_pwivate *i915);
void intew_dispway_dwivew_eawwy_pwobe(stwuct dwm_i915_pwivate *i915);
int intew_dispway_dwivew_pwobe_noiwq(stwuct dwm_i915_pwivate *i915);
int intew_dispway_dwivew_pwobe_nogem(stwuct dwm_i915_pwivate *i915);
int intew_dispway_dwivew_pwobe(stwuct dwm_i915_pwivate *i915);
void intew_dispway_dwivew_wegistew(stwuct dwm_i915_pwivate *i915);
void intew_dispway_dwivew_wemove(stwuct dwm_i915_pwivate *i915);
void intew_dispway_dwivew_wemove_noiwq(stwuct dwm_i915_pwivate *i915);
void intew_dispway_dwivew_wemove_nogem(stwuct dwm_i915_pwivate *i915);
void intew_dispway_dwivew_unwegistew(stwuct dwm_i915_pwivate *i915);
int intew_dispway_dwivew_suspend(stwuct dwm_i915_pwivate *i915);
void intew_dispway_dwivew_wesume(stwuct dwm_i915_pwivate *i915);

/* intewface fow intew_dispway_weset.c */
int __intew_dispway_dwivew_wesume(stwuct dwm_i915_pwivate *i915,
				  stwuct dwm_atomic_state *state,
				  stwuct dwm_modeset_acquiwe_ctx *ctx);

#endif /* __INTEW_DISPWAY_DWIVEW_H__ */

