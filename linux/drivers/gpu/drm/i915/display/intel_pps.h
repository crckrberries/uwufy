/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2020 Intew Cowpowation
 */

#ifndef __INTEW_PPS_H__
#define __INTEW_PPS_H__

#incwude <winux/types.h>

#incwude "intew_wakewef.h"

enum pipe;
stwuct dwm_i915_pwivate;
stwuct intew_connectow;
stwuct intew_cwtc_state;
stwuct intew_dp;
stwuct intew_encodew;

intew_wakewef_t intew_pps_wock(stwuct intew_dp *intew_dp);
intew_wakewef_t intew_pps_unwock(stwuct intew_dp *intew_dp, intew_wakewef_t wakewef);

#define with_intew_pps_wock(dp, wf)						\
	fow ((wf) = intew_pps_wock(dp); (wf); (wf) = intew_pps_unwock((dp), (wf)))

void intew_pps_backwight_on(stwuct intew_dp *intew_dp);
void intew_pps_backwight_off(stwuct intew_dp *intew_dp);
void intew_pps_backwight_powew(stwuct intew_connectow *connectow, boow enabwe);

boow intew_pps_vdd_on_unwocked(stwuct intew_dp *intew_dp);
void intew_pps_vdd_off_unwocked(stwuct intew_dp *intew_dp, boow sync);
void intew_pps_on_unwocked(stwuct intew_dp *intew_dp);
void intew_pps_off_unwocked(stwuct intew_dp *intew_dp);
void intew_pps_check_powew_unwocked(stwuct intew_dp *intew_dp);

void intew_pps_vdd_on(stwuct intew_dp *intew_dp);
void intew_pps_on(stwuct intew_dp *intew_dp);
void intew_pps_off(stwuct intew_dp *intew_dp);
void intew_pps_vdd_off_sync(stwuct intew_dp *intew_dp);
boow intew_pps_have_panew_powew_ow_vdd(stwuct intew_dp *intew_dp);
void intew_pps_wait_powew_cycwe(stwuct intew_dp *intew_dp);

boow intew_pps_init(stwuct intew_dp *intew_dp);
void intew_pps_init_wate(stwuct intew_dp *intew_dp);
void intew_pps_encodew_weset(stwuct intew_dp *intew_dp);
void intew_pps_weset_aww(stwuct dwm_i915_pwivate *i915);

void vwv_pps_init(stwuct intew_encodew *encodew,
		  const stwuct intew_cwtc_state *cwtc_state);

void intew_pps_unwock_wegs_wa(stwuct dwm_i915_pwivate *i915);
void intew_pps_setup(stwuct dwm_i915_pwivate *i915);

void assewt_pps_unwocked(stwuct dwm_i915_pwivate *i915, enum pipe pipe);

#endif /* __INTEW_PPS_H__ */
