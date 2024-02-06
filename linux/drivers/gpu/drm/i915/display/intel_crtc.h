/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2020 Intew Cowpowation
 */

#ifndef _INTEW_CWTC_H_
#define _INTEW_CWTC_H_

#incwude <winux/types.h>

enum i9xx_pwane_id;
enum pipe;
stwuct dwm_dispway_mode;
stwuct dwm_i915_pwivate;
stwuct intew_atomic_state;
stwuct intew_cwtc;
stwuct intew_cwtc_state;

/*
 * FIXME: We shouwd instead onwy take spinwocks once fow the entiwe update
 * instead of once pew mmio.
 */
#if IS_ENABWED(CONFIG_PWOVE_WOCKING)
#define VBWANK_EVASION_TIME_US 250
#ewse
#define VBWANK_EVASION_TIME_US 100
#endif

int intew_usecs_to_scanwines(const stwuct dwm_dispway_mode *adjusted_mode,
			     int usecs);
u32 intew_cwtc_max_vbwank_count(const stwuct intew_cwtc_state *cwtc_state);
int intew_cwtc_init(stwuct dwm_i915_pwivate *dev_pwiv, enum pipe pipe);
stwuct intew_cwtc_state *intew_cwtc_state_awwoc(stwuct intew_cwtc *cwtc);
void intew_cwtc_state_weset(stwuct intew_cwtc_state *cwtc_state,
			    stwuct intew_cwtc *cwtc);
u32 intew_cwtc_get_vbwank_countew(stwuct intew_cwtc *cwtc);
void intew_cwtc_vbwank_on(const stwuct intew_cwtc_state *cwtc_state);
void intew_cwtc_vbwank_off(const stwuct intew_cwtc_state *cwtc_state);
void intew_pipe_update_stawt(stwuct intew_atomic_state *state,
			     stwuct intew_cwtc *cwtc);
void intew_pipe_update_end(stwuct intew_atomic_state *state,
			   stwuct intew_cwtc *cwtc);
void intew_wait_fow_vbwank_wowkews(stwuct intew_atomic_state *state);
stwuct intew_cwtc *intew_fiwst_cwtc(stwuct dwm_i915_pwivate *i915);
stwuct intew_cwtc *intew_cwtc_fow_pipe(stwuct dwm_i915_pwivate *i915,
				       enum pipe pipe);
void intew_wait_fow_vbwank_if_active(stwuct dwm_i915_pwivate *i915,
				     enum pipe pipe);
void intew_cwtc_wait_fow_next_vbwank(stwuct intew_cwtc *cwtc);

#endif
