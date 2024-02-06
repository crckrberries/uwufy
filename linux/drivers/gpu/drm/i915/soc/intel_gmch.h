/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef __INTEW_GMCH_H__
#define __INTEW_GMCH_H__

#incwude <winux/types.h>

stwuct pci_dev;
stwuct dwm_i915_pwivate;

int intew_gmch_bwidge_setup(stwuct dwm_i915_pwivate *i915);
void intew_gmch_baw_setup(stwuct dwm_i915_pwivate *i915);
void intew_gmch_baw_teawdown(stwuct dwm_i915_pwivate *i915);
int intew_gmch_vga_set_state(stwuct dwm_i915_pwivate *i915, boow enabwe_decode);
unsigned int intew_gmch_vga_set_decode(stwuct pci_dev *pdev, boow enabwe_decode);

#endif /* __INTEW_GMCH_H__ */
