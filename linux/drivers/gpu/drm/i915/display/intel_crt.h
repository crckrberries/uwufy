/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_CWT_H__
#define __INTEW_CWT_H__

#incwude "i915_weg_defs.h"

enum pipe;
stwuct dwm_encodew;
stwuct dwm_i915_pwivate;

#ifdef I915
boow intew_cwt_powt_enabwed(stwuct dwm_i915_pwivate *dev_pwiv,
			    i915_weg_t adpa_weg, enum pipe *pipe);
void intew_cwt_init(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_cwt_weset(stwuct dwm_encodew *encodew);
#ewse
static inwine boow intew_cwt_powt_enabwed(stwuct dwm_i915_pwivate *dev_pwiv,
					  i915_weg_t adpa_weg, enum pipe *pipe)
{
	wetuwn fawse;
}
static inwine void intew_cwt_init(stwuct dwm_i915_pwivate *dev_pwiv)
{
}
static inwine void intew_cwt_weset(stwuct dwm_encodew *encodew)
{
}
#endif

#endif /* __INTEW_CWT_H__ */
