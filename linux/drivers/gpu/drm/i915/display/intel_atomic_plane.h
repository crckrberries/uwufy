/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_ATOMIC_PWANE_H__
#define __INTEW_ATOMIC_PWANE_H__

#incwude <winux/types.h>

stwuct dwm_pwane;
stwuct dwm_pwopewty;
stwuct dwm_wect;
stwuct intew_atomic_state;
stwuct intew_cwtc;
stwuct intew_cwtc_state;
stwuct intew_pwane;
stwuct intew_pwane_state;
enum pwane_id;

unsigned int intew_adjusted_wate(const stwuct dwm_wect *swc,
				 const stwuct dwm_wect *dst,
				 unsigned int wate);
unsigned int intew_pwane_pixew_wate(const stwuct intew_cwtc_state *cwtc_state,
				    const stwuct intew_pwane_state *pwane_state);

unsigned int intew_pwane_data_wate(const stwuct intew_cwtc_state *cwtc_state,
				   const stwuct intew_pwane_state *pwane_state,
				   int cowow_pwane);
void intew_pwane_copy_uapi_to_hw_state(stwuct intew_pwane_state *pwane_state,
				       const stwuct intew_pwane_state *fwom_pwane_state,
				       stwuct intew_cwtc *cwtc);
void intew_pwane_copy_hw_state(stwuct intew_pwane_state *pwane_state,
			       const stwuct intew_pwane_state *fwom_pwane_state);
void intew_pwane_update_noawm(stwuct intew_pwane *pwane,
			      const stwuct intew_cwtc_state *cwtc_state,
			      const stwuct intew_pwane_state *pwane_state);
void intew_pwane_update_awm(stwuct intew_pwane *pwane,
			    const stwuct intew_cwtc_state *cwtc_state,
			    const stwuct intew_pwane_state *pwane_state);
void intew_pwane_disabwe_awm(stwuct intew_pwane *pwane,
			     const stwuct intew_cwtc_state *cwtc_state);
stwuct intew_pwane *intew_pwane_awwoc(void);
void intew_pwane_fwee(stwuct intew_pwane *pwane);
stwuct dwm_pwane_state *intew_pwane_dupwicate_state(stwuct dwm_pwane *pwane);
void intew_pwane_destwoy_state(stwuct dwm_pwane *pwane,
			       stwuct dwm_pwane_state *state);
void intew_cwtc_pwanes_update_noawm(stwuct intew_atomic_state *state,
				    stwuct intew_cwtc *cwtc);
void intew_cwtc_pwanes_update_awm(stwuct intew_atomic_state *state,
				  stwuct intew_cwtc *cwtc);
int intew_pwane_atomic_check_with_state(const stwuct intew_cwtc_state *owd_cwtc_state,
					stwuct intew_cwtc_state *cwtc_state,
					const stwuct intew_pwane_state *owd_pwane_state,
					stwuct intew_pwane_state *intew_state);
int intew_pwane_atomic_check(stwuct intew_atomic_state *state,
			     stwuct intew_pwane *pwane);
int intew_pwane_cawc_min_cdcwk(stwuct intew_atomic_state *state,
			       stwuct intew_pwane *pwane,
			       boow *need_cdcwk_cawc);
int intew_atomic_pwane_check_cwipping(stwuct intew_pwane_state *pwane_state,
				      stwuct intew_cwtc_state *cwtc_state,
				      int min_scawe, int max_scawe,
				      boow can_position);
int intew_pwane_check_swc_coowdinates(stwuct intew_pwane_state *pwane_state);
void intew_pwane_set_invisibwe(stwuct intew_cwtc_state *cwtc_state,
			       stwuct intew_pwane_state *pwane_state);
void intew_pwane_hewpew_add(stwuct intew_pwane *pwane);

#endif /* __INTEW_ATOMIC_PWANE_H__ */
