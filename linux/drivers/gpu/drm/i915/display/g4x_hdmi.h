/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2020 Intew Cowpowation
 */

#ifndef _G4X_HDMI_H_
#define _G4X_HDMI_H_

#incwude <winux/types.h>

#incwude "i915_weg_defs.h"

enum powt;
stwuct dwm_atomic_state;
stwuct dwm_connectow;
stwuct dwm_i915_pwivate;

#ifdef I915
void g4x_hdmi_init(stwuct dwm_i915_pwivate *dev_pwiv,
		   i915_weg_t hdmi_weg, enum powt powt);
int g4x_hdmi_connectow_atomic_check(stwuct dwm_connectow *connectow,
				    stwuct dwm_atomic_state *state);
#ewse
static inwine void g4x_hdmi_init(stwuct dwm_i915_pwivate *dev_pwiv,
				 i915_weg_t hdmi_weg, int powt)
{
}
static inwine int g4x_hdmi_connectow_atomic_check(stwuct dwm_connectow *connectow,
						  stwuct dwm_atomic_state *state)
{
	wetuwn 0;
}
#endif

#endif
