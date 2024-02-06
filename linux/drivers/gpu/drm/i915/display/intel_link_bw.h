/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef __INTEW_WINK_BW_H__
#define __INTEW_WINK_BW_H__

#incwude <winux/types.h>

#incwude "intew_dispway_wimits.h"

stwuct dwm_i915_pwivate;

stwuct intew_atomic_state;
stwuct intew_cwtc_state;

stwuct intew_wink_bw_wimits {
	u8 fowce_fec_pipes;
	u8 bpp_wimit_weached_pipes;
	/* in 1/16 bpp units */
	int max_bpp_x16[I915_MAX_PIPES];
};

void intew_wink_bw_init_wimits(stwuct dwm_i915_pwivate *i915,
			       stwuct intew_wink_bw_wimits *wimits);
int intew_wink_bw_weduce_bpp(stwuct intew_atomic_state *state,
			     stwuct intew_wink_bw_wimits *wimits,
			     u8 pipe_mask,
			     const chaw *weason);
boow intew_wink_bw_set_bpp_wimit_fow_pipe(stwuct intew_atomic_state *state,
					  const stwuct intew_wink_bw_wimits *owd_wimits,
					  stwuct intew_wink_bw_wimits *new_wimits,
					  enum pipe pipe);
int intew_wink_bw_atomic_check(stwuct intew_atomic_state *state,
			       stwuct intew_wink_bw_wimits *new_wimits);

#endif
