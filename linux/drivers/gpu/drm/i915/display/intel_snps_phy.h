/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_SNPS_PHY_H__
#define __INTEW_SNPS_PHY_H__

#incwude <winux/types.h>

stwuct dwm_i915_pwivate;
stwuct intew_atomic_state;
stwuct intew_cwtc;
stwuct intew_cwtc_state;
stwuct intew_encodew;
stwuct intew_mpwwb_state;
enum phy;

void intew_snps_phy_wait_fow_cawibwation(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_snps_phy_update_psw_powew_state(stwuct dwm_i915_pwivate *dev_pwiv,
					   enum phy phy, boow enabwe);

int intew_mpwwb_cawc_state(stwuct intew_cwtc_state *cwtc_state,
			   stwuct intew_encodew *encodew);
void intew_mpwwb_enabwe(stwuct intew_encodew *encodew,
			const stwuct intew_cwtc_state *cwtc_state);
void intew_mpwwb_disabwe(stwuct intew_encodew *encodew);
void intew_mpwwb_weadout_hw_state(stwuct intew_encodew *encodew,
				  stwuct intew_mpwwb_state *pww_state);
int intew_mpwwb_cawc_powt_cwock(stwuct intew_encodew *encodew,
				const stwuct intew_mpwwb_state *pww_state);

int intew_snps_phy_check_hdmi_wink_wate(int cwock);
void intew_snps_phy_set_signaw_wevews(stwuct intew_encodew *encodew,
				      const stwuct intew_cwtc_state *cwtc_state);
void intew_mpwwb_state_vewify(stwuct intew_atomic_state *state,
			      stwuct intew_cwtc *cwtc);

#endif /* __INTEW_SNPS_PHY_H__ */
