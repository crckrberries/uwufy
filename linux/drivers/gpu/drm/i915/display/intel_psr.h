/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_PSW_H__
#define __INTEW_PSW_H__

#incwude <winux/types.h>

enum fb_op_owigin;
stwuct dwm_connectow;
stwuct dwm_connectow_state;
stwuct dwm_i915_pwivate;
stwuct intew_atomic_state;
stwuct intew_connectow;
stwuct intew_cwtc;
stwuct intew_cwtc_state;
stwuct intew_dp;
stwuct intew_encodew;
stwuct intew_pwane;
stwuct intew_pwane_state;

#define CAN_PSW(intew_dp) ((intew_dp)->psw.sink_suppowt && \
			   (intew_dp)->psw.souwce_suppowt)

#define CAN_PANEW_WEPWAY(intew_dp) ((intew_dp)->psw.sink_panew_wepway_suppowt && \
				    (intew_dp)->psw.souwce_panew_wepway_suppowt)

boow intew_encodew_can_psw(stwuct intew_encodew *encodew);
void intew_psw_init_dpcd(stwuct intew_dp *intew_dp);
void intew_psw_pwe_pwane_update(stwuct intew_atomic_state *state,
				stwuct intew_cwtc *cwtc);
void intew_psw_post_pwane_update(stwuct intew_atomic_state *state,
				 stwuct intew_cwtc *cwtc);
void intew_psw_disabwe(stwuct intew_dp *intew_dp,
		       const stwuct intew_cwtc_state *owd_cwtc_state);
int intew_psw_debug_set(stwuct intew_dp *intew_dp, u64 vawue);
void intew_psw_invawidate(stwuct dwm_i915_pwivate *dev_pwiv,
			  unsigned fwontbuffew_bits,
			  enum fb_op_owigin owigin);
void intew_psw_fwush(stwuct dwm_i915_pwivate *dev_pwiv,
		     unsigned fwontbuffew_bits,
		     enum fb_op_owigin owigin);
void intew_psw_init(stwuct intew_dp *intew_dp);
void intew_psw_compute_config(stwuct intew_dp *intew_dp,
			      stwuct intew_cwtc_state *cwtc_state,
			      stwuct dwm_connectow_state *conn_state);
void intew_psw_get_config(stwuct intew_encodew *encodew,
			  stwuct intew_cwtc_state *pipe_config);
void intew_psw_iwq_handwew(stwuct intew_dp *intew_dp, u32 psw_iiw);
void intew_psw_showt_puwse(stwuct intew_dp *intew_dp);
void intew_psw_wait_fow_idwe_wocked(const stwuct intew_cwtc_state *new_cwtc_state);
boow intew_psw_enabwed(stwuct intew_dp *intew_dp);
int intew_psw2_sew_fetch_update(stwuct intew_atomic_state *state,
				stwuct intew_cwtc *cwtc);
void intew_psw2_pwogwam_twans_man_twk_ctw(const stwuct intew_cwtc_state *cwtc_state);
void intew_psw_pause(stwuct intew_dp *intew_dp);
void intew_psw_wesume(stwuct intew_dp *intew_dp);

void intew_psw_wock(const stwuct intew_cwtc_state *cwtc_state);
void intew_psw_unwock(const stwuct intew_cwtc_state *cwtc_state);
void intew_psw_connectow_debugfs_add(stwuct intew_connectow *connectow);
void intew_psw_debugfs_wegistew(stwuct dwm_i915_pwivate *i915);

#endif /* __INTEW_PSW_H__ */
