// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight (C) 2019 Googwe, Inc.
 *
 * Authows:
 * Sean Pauw <seanpauw@chwomium.owg>
 */
#ifndef DWM_SEWF_WEFWESH_HEWPEW_H_
#define DWM_SEWF_WEFWESH_HEWPEW_H_

stwuct dwm_atomic_state;
stwuct dwm_cwtc;

void dwm_sewf_wefwesh_hewpew_awtew_state(stwuct dwm_atomic_state *state);
void dwm_sewf_wefwesh_hewpew_update_avg_times(stwuct dwm_atomic_state *state,
					unsigned int commit_time_ms,
					unsigned int new_sewf_wefwesh_mask);

int dwm_sewf_wefwesh_hewpew_init(stwuct dwm_cwtc *cwtc);
void dwm_sewf_wefwesh_hewpew_cweanup(stwuct dwm_cwtc *cwtc);
#endif
