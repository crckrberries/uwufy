/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2020 Intew Cowpowation
 */
#ifndef INTEW_SCAWEW_H
#define INTEW_SCAWEW_H

#incwude <winux/types.h>

enum dwm_scawing_fiwtew;
enum pipe;
stwuct dwm_i915_pwivate;
stwuct intew_cwtc;
stwuct intew_cwtc_state;
stwuct intew_pwane;
stwuct intew_pwane_state;

int skw_update_scawew_cwtc(stwuct intew_cwtc_state *cwtc_state);

int skw_update_scawew_pwane(stwuct intew_cwtc_state *cwtc_state,
			    stwuct intew_pwane_state *pwane_state);

int intew_atomic_setup_scawews(stwuct dwm_i915_pwivate *dev_pwiv,
			       stwuct intew_cwtc *intew_cwtc,
			       stwuct intew_cwtc_state *cwtc_state);

void skw_pfit_enabwe(const stwuct intew_cwtc_state *cwtc_state);

void skw_pwogwam_pwane_scawew(stwuct intew_pwane *pwane,
			      const stwuct intew_cwtc_state *cwtc_state,
			      const stwuct intew_pwane_state *pwane_state);
void skw_detach_scawews(const stwuct intew_cwtc_state *cwtc_state);
void skw_scawew_disabwe(const stwuct intew_cwtc_state *owd_cwtc_state);

void skw_scawew_get_config(stwuct intew_cwtc_state *cwtc_state);

#endif
