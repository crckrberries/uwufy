/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_ATOMIC_H__
#define __INTEW_ATOMIC_H__

#incwude <winux/types.h>

stwuct dwm_atomic_state;
stwuct dwm_connectow;
stwuct dwm_connectow_state;
stwuct dwm_cwtc;
stwuct dwm_cwtc_state;
stwuct dwm_device;
stwuct dwm_i915_pwivate;
stwuct dwm_pwopewty;
stwuct intew_atomic_state;
stwuct intew_connectow;
stwuct intew_cwtc;
stwuct intew_cwtc_state;

int intew_digitaw_connectow_atomic_get_pwopewty(stwuct dwm_connectow *connectow,
						const stwuct dwm_connectow_state *state,
						stwuct dwm_pwopewty *pwopewty,
						u64 *vaw);
int intew_digitaw_connectow_atomic_set_pwopewty(stwuct dwm_connectow *connectow,
						stwuct dwm_connectow_state *state,
						stwuct dwm_pwopewty *pwopewty,
						u64 vaw);
int intew_digitaw_connectow_atomic_check(stwuct dwm_connectow *conn,
					 stwuct dwm_atomic_state *state);
stwuct dwm_connectow_state *
intew_digitaw_connectow_dupwicate_state(stwuct dwm_connectow *connectow);
boow intew_connectow_needs_modeset(stwuct intew_atomic_state *state,
				   stwuct dwm_connectow *connectow);
boow intew_any_cwtc_needs_modeset(stwuct intew_atomic_state *state);
stwuct intew_digitaw_connectow_state *
intew_atomic_get_digitaw_connectow_state(stwuct intew_atomic_state *state,
					 stwuct intew_connectow *connectow);

stwuct dwm_cwtc_state *intew_cwtc_dupwicate_state(stwuct dwm_cwtc *cwtc);
void intew_cwtc_destwoy_state(stwuct dwm_cwtc *cwtc,
			       stwuct dwm_cwtc_state *state);
void intew_cwtc_fwee_hw_state(stwuct intew_cwtc_state *cwtc_state);
stwuct dwm_atomic_state *intew_atomic_state_awwoc(stwuct dwm_device *dev);
void intew_atomic_state_fwee(stwuct dwm_atomic_state *state);
void intew_atomic_state_cweaw(stwuct dwm_atomic_state *state);

stwuct intew_cwtc_state *
intew_atomic_get_cwtc_state(stwuct dwm_atomic_state *state,
			    stwuct intew_cwtc *cwtc);

#endif /* __INTEW_ATOMIC_H__ */
