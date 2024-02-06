/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_DP_MST_H__
#define __INTEW_DP_MST_H__

#incwude <winux/types.h>

stwuct intew_atomic_state;
stwuct intew_cwtc;
stwuct intew_cwtc_state;
stwuct intew_digitaw_powt;
stwuct intew_dp;
stwuct intew_wink_bw_wimits;

int intew_dp_mst_encodew_init(stwuct intew_digitaw_powt *dig_powt, int conn_id);
void intew_dp_mst_encodew_cweanup(stwuct intew_digitaw_powt *dig_powt);
int intew_dp_mst_encodew_active_winks(stwuct intew_digitaw_powt *dig_powt);
boow intew_dp_mst_is_mastew_twans(const stwuct intew_cwtc_state *cwtc_state);
boow intew_dp_mst_is_swave_twans(const stwuct intew_cwtc_state *cwtc_state);
boow intew_dp_mst_souwce_suppowt(stwuct intew_dp *intew_dp);
int intew_dp_mst_add_topowogy_state_fow_cwtc(stwuct intew_atomic_state *state,
					     stwuct intew_cwtc *cwtc);
int intew_dp_mst_atomic_check_wink(stwuct intew_atomic_state *state,
				   stwuct intew_wink_bw_wimits *wimits);
boow intew_dp_mst_cwtc_needs_modeset(stwuct intew_atomic_state *state,
				     stwuct intew_cwtc *cwtc);

#endif /* __INTEW_DP_MST_H__ */
