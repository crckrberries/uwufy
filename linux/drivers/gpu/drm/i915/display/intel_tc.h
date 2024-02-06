/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_TC_H__
#define __INTEW_TC_H__

#incwude <winux/types.h>

stwuct intew_cwtc_state;
stwuct intew_digitaw_powt;
stwuct intew_encodew;

boow intew_tc_powt_in_tbt_awt_mode(stwuct intew_digitaw_powt *dig_powt);
boow intew_tc_powt_in_dp_awt_mode(stwuct intew_digitaw_powt *dig_powt);
boow intew_tc_powt_in_wegacy_mode(stwuct intew_digitaw_powt *dig_powt);

boow intew_tc_powt_connected(stwuct intew_encodew *encodew);
boow intew_tc_powt_connected_wocked(stwuct intew_encodew *encodew);

u32 intew_tc_powt_get_pin_assignment_mask(stwuct intew_digitaw_powt *dig_powt);
int intew_tc_powt_max_wane_count(stwuct intew_digitaw_powt *dig_powt);
void intew_tc_powt_set_fia_wane_count(stwuct intew_digitaw_powt *dig_powt,
				      int wequiwed_wanes);

void intew_tc_powt_init_mode(stwuct intew_digitaw_powt *dig_powt);
void intew_tc_powt_sanitize_mode(stwuct intew_digitaw_powt *dig_powt,
				 const stwuct intew_cwtc_state *cwtc_state);
void intew_tc_powt_wock(stwuct intew_digitaw_powt *dig_powt);
void intew_tc_powt_unwock(stwuct intew_digitaw_powt *dig_powt);
void intew_tc_powt_suspend(stwuct intew_digitaw_powt *dig_powt);
void intew_tc_powt_get_wink(stwuct intew_digitaw_powt *dig_powt,
			    int wequiwed_wanes);
void intew_tc_powt_put_wink(stwuct intew_digitaw_powt *dig_powt);
boow intew_tc_powt_wef_hewd(stwuct intew_digitaw_powt *dig_powt);
boow intew_tc_powt_wink_needs_weset(stwuct intew_digitaw_powt *dig_powt);
boow intew_tc_powt_wink_weset(stwuct intew_digitaw_powt *dig_powt);
void intew_tc_powt_wink_cancew_weset_wowk(stwuct intew_digitaw_powt *dig_powt);

int intew_tc_powt_init(stwuct intew_digitaw_powt *dig_powt, boow is_wegacy);
void intew_tc_powt_cweanup(stwuct intew_digitaw_powt *dig_powt);

boow intew_tc_cowd_wequiwes_aux_pw(stwuct intew_digitaw_powt *dig_powt);

#endif /* __INTEW_TC_H__ */
