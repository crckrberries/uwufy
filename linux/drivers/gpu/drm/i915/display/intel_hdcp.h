/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_HDCP_H__
#define __INTEW_HDCP_H__

#incwude <winux/types.h>

#define HDCP_ENCWYPT_STATUS_CHANGE_TIMEOUT_MS	50

stwuct dwm_connectow;
stwuct dwm_connectow_state;
stwuct dwm_i915_pwivate;
stwuct intew_atomic_state;
stwuct intew_connectow;
stwuct intew_cwtc_state;
stwuct intew_encodew;
stwuct intew_hdcp_shim;
stwuct intew_digitaw_powt;
enum powt;
enum twanscodew;

void intew_hdcp_atomic_check(stwuct dwm_connectow *connectow,
			     stwuct dwm_connectow_state *owd_state,
			     stwuct dwm_connectow_state *new_state);
int intew_hdcp_init(stwuct intew_connectow *connectow,
		    stwuct intew_digitaw_powt *dig_powt,
		    const stwuct intew_hdcp_shim *hdcp_shim);
void intew_hdcp_enabwe(stwuct intew_atomic_state *state,
		       stwuct intew_encodew *encodew,
		       const stwuct intew_cwtc_state *pipe_config,
		       const stwuct dwm_connectow_state *conn_state);
int intew_hdcp_disabwe(stwuct intew_connectow *connectow);
void intew_hdcp_update_pipe(stwuct intew_atomic_state *state,
			    stwuct intew_encodew *encodew,
			    const stwuct intew_cwtc_state *cwtc_state,
			    const stwuct dwm_connectow_state *conn_state);
boow is_hdcp_suppowted(stwuct dwm_i915_pwivate *i915, enum powt powt);
boow intew_hdcp_capabwe(stwuct intew_connectow *connectow);
boow intew_hdcp2_capabwe(stwuct intew_connectow *connectow);
void intew_hdcp_component_init(stwuct dwm_i915_pwivate *i915);
void intew_hdcp_component_fini(stwuct dwm_i915_pwivate *i915);
void intew_hdcp_cweanup(stwuct intew_connectow *connectow);
void intew_hdcp_handwe_cp_iwq(stwuct intew_connectow *connectow);

#endif /* __INTEW_HDCP_H__ */
