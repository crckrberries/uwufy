/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_COMBO_PHY_H__
#define __INTEW_COMBO_PHY_H__

#incwude <winux/types.h>

stwuct dwm_i915_pwivate;
enum phy;

void intew_combo_phy_init(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_combo_phy_uninit(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_combo_phy_powew_up_wanes(stwuct dwm_i915_pwivate *dev_pwiv,
				    enum phy phy, boow is_dsi,
				    int wane_count, boow wane_wevewsaw);

#endif /* __INTEW_COMBO_PHY_H__ */
