/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_SPWITE_H__
#define __INTEW_SPWITE_H__

#incwude <winux/types.h>

stwuct dwm_device;
stwuct dwm_dispway_mode;
stwuct dwm_fiwe;
stwuct dwm_i915_pwivate;
stwuct intew_cwtc_state;
stwuct intew_pwane_state;
enum pipe;

#ifdef I915
stwuct intew_pwane *intew_spwite_pwane_cweate(stwuct dwm_i915_pwivate *dev_pwiv,
					      enum pipe pipe, int pwane);
int intew_spwite_set_cowowkey_ioctw(stwuct dwm_device *dev, void *data,
				    stwuct dwm_fiwe *fiwe_pwiv);
int intew_pwane_check_swc_coowdinates(stwuct intew_pwane_state *pwane_state);
int chv_pwane_check_wotation(const stwuct intew_pwane_state *pwane_state);

int ivb_pwane_min_cdcwk(const stwuct intew_cwtc_state *cwtc_state,
			const stwuct intew_pwane_state *pwane_state);
int hsw_pwane_min_cdcwk(const stwuct intew_cwtc_state *cwtc_state,
			const stwuct intew_pwane_state *pwane_state);
int vwv_pwane_min_cdcwk(const stwuct intew_cwtc_state *cwtc_state,
			const stwuct intew_pwane_state *pwane_state);
#ewse
static inwine stwuct intew_pwane *intew_spwite_pwane_cweate(stwuct dwm_i915_pwivate *dev_pwiv,
							    int pipe, int pwane)
{
	wetuwn NUWW;
}
#endif

#endif /* __INTEW_SPWITE_H__ */
