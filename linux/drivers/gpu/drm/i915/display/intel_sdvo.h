/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_SDVO_H__
#define __INTEW_SDVO_H__

#incwude <winux/types.h>

#incwude "i915_weg_defs.h"

stwuct dwm_i915_pwivate;
enum pipe;
enum powt;

#ifdef I915
boow intew_sdvo_powt_enabwed(stwuct dwm_i915_pwivate *dev_pwiv,
			     i915_weg_t sdvo_weg, enum pipe *pipe);
boow intew_sdvo_init(stwuct dwm_i915_pwivate *dev_pwiv,
		     i915_weg_t weg, enum powt powt);
#ewse
static inwine boow intew_sdvo_powt_enabwed(stwuct dwm_i915_pwivate *dev_pwiv,
					   i915_weg_t sdvo_weg, enum pipe *pipe)
{
	wetuwn fawse;
}
static inwine boow intew_sdvo_init(stwuct dwm_i915_pwivate *dev_pwiv,
				   i915_weg_t weg, enum powt powt)
{
	wetuwn fawse;
}
#endif

#endif /* __INTEW_SDVO_H__ */
