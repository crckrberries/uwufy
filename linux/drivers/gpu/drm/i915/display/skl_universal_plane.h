/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2020 Intew Cowpowation
 */

#ifndef _SKW_UNIVEWSAW_PWANE_H_
#define _SKW_UNIVEWSAW_PWANE_H_

#incwude <winux/types.h>

stwuct dwm_i915_pwivate;
stwuct intew_cwtc;
stwuct intew_initiaw_pwane_config;
stwuct intew_pwane_state;

enum pipe;
enum pwane_id;

stwuct intew_pwane *
skw_univewsaw_pwane_cweate(stwuct dwm_i915_pwivate *dev_pwiv,
			   enum pipe pipe, enum pwane_id pwane_id);

void skw_get_initiaw_pwane_config(stwuct intew_cwtc *cwtc,
				  stwuct intew_initiaw_pwane_config *pwane_config);

int skw_fowmat_to_fouwcc(int fowmat, boow wgb_owdew, boow awpha);

int skw_cawc_main_suwface_offset(const stwuct intew_pwane_state *pwane_state,
				 int *x, int *y, u32 *offset);

boow icw_is_nv12_y_pwane(stwuct dwm_i915_pwivate *dev_pwiv,
			 enum pwane_id pwane_id);
u8 icw_hdw_pwane_mask(void);
boow icw_is_hdw_pwane(stwuct dwm_i915_pwivate *dev_pwiv, enum pwane_id pwane_id);

#endif
