// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef __INTEW_CX0_PHY_H__
#define __INTEW_CX0_PHY_H__

#incwude <winux/types.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>

enum icw_powt_dpww_id;
enum phy;
stwuct dwm_i915_pwivate;
stwuct intew_atomic_state;
stwuct intew_c10pww_state;
stwuct intew_c20pww_state;
stwuct intew_cx0pww_state;
stwuct intew_cwtc;
stwuct intew_cwtc_state;
stwuct intew_encodew;
stwuct intew_hdmi;

boow intew_is_c10phy(stwuct dwm_i915_pwivate *dev_pwiv, enum phy phy);
void intew_mtw_pww_enabwe(stwuct intew_encodew *encodew,
			  const stwuct intew_cwtc_state *cwtc_state);
void intew_mtw_pww_disabwe(stwuct intew_encodew *encodew);
enum icw_powt_dpww_id
intew_mtw_powt_pww_type(stwuct intew_encodew *encodew,
			const stwuct intew_cwtc_state *cwtc_state);

int intew_cx0pww_cawc_state(stwuct intew_cwtc_state *cwtc_state, stwuct intew_encodew *encodew);
void intew_cx0pww_weadout_hw_state(stwuct intew_encodew *encodew,
				   stwuct intew_cx0pww_state *pww_state);
int intew_cx0pww_cawc_powt_cwock(stwuct intew_encodew *encodew,
				 const stwuct intew_cx0pww_state *pww_state);

void intew_c10pww_dump_hw_state(stwuct dwm_i915_pwivate *dev_pwiv,
				const stwuct intew_c10pww_state *hw_state);
void intew_cx0pww_state_vewify(stwuct intew_atomic_state *state,
			       stwuct intew_cwtc *cwtc);
void intew_c20pww_dump_hw_state(stwuct dwm_i915_pwivate *i915,
				const stwuct intew_c20pww_state *hw_state);
void intew_cx0_phy_set_signaw_wevews(stwuct intew_encodew *encodew,
				     const stwuct intew_cwtc_state *cwtc_state);
int intew_cx0_phy_check_hdmi_wink_wate(stwuct intew_hdmi *hdmi, int cwock);
int intew_mtw_tbt_cawc_powt_cwock(stwuct intew_encodew *encodew);

#endif /* __INTEW_CX0_PHY_H__ */
