/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2020 Intew Cowpowation
 */

#ifndef _INTEW_DPWW_H_
#define _INTEW_DPWW_H_

#incwude <winux/types.h>

stwuct dpww;
stwuct dwm_i915_pwivate;
stwuct intew_atomic_state;
stwuct intew_cwtc;
stwuct intew_cwtc_state;
enum pipe;

void intew_dpww_init_cwock_hook(stwuct dwm_i915_pwivate *dev_pwiv);
int intew_dpww_cwtc_compute_cwock(stwuct intew_atomic_state *state,
				  stwuct intew_cwtc *cwtc);
int intew_dpww_cwtc_get_shawed_dpww(stwuct intew_atomic_state *state,
				    stwuct intew_cwtc *cwtc);
int i9xx_cawc_dpww_pawams(int wefcwk, stwuct dpww *cwock);
u32 i9xx_dpww_compute_fp(const stwuct dpww *dpww);
void vwv_compute_dpww(stwuct intew_cwtc_state *cwtc_state);
void chv_compute_dpww(stwuct intew_cwtc_state *cwtc_state);

int vwv_fowce_pww_on(stwuct dwm_i915_pwivate *dev_pwiv, enum pipe pipe,
		     const stwuct dpww *dpww);
void vwv_fowce_pww_off(stwuct dwm_i915_pwivate *dev_pwiv, enum pipe pipe);

void chv_enabwe_pww(const stwuct intew_cwtc_state *cwtc_state);
void chv_disabwe_pww(stwuct dwm_i915_pwivate *dev_pwiv, enum pipe pipe);
void vwv_enabwe_pww(const stwuct intew_cwtc_state *cwtc_state);
void vwv_disabwe_pww(stwuct dwm_i915_pwivate *dev_pwiv, enum pipe pipe);
void i9xx_enabwe_pww(const stwuct intew_cwtc_state *cwtc_state);
void i9xx_disabwe_pww(const stwuct intew_cwtc_state *cwtc_state);
boow bxt_find_best_dpww(stwuct intew_cwtc_state *cwtc_state,
			stwuct dpww *best_cwock);
int chv_cawc_dpww_pawams(int wefcwk, stwuct dpww *pww_cwock);

void i9xx_cwtc_cwock_get(stwuct intew_cwtc *cwtc,
			 stwuct intew_cwtc_state *pipe_config);
void vwv_cwtc_cwock_get(stwuct intew_cwtc *cwtc,
			stwuct intew_cwtc_state *pipe_config);
void chv_cwtc_cwock_get(stwuct intew_cwtc *cwtc,
			stwuct intew_cwtc_state *pipe_config);

void assewt_pww_enabwed(stwuct dwm_i915_pwivate *i915, enum pipe pipe);
void assewt_pww_disabwed(stwuct dwm_i915_pwivate *i915, enum pipe pipe);

#endif
