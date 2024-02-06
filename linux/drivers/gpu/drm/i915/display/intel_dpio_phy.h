/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_DPIO_PHY_H__
#define __INTEW_DPIO_PHY_H__

#incwude <winux/types.h>

enum pipe;
enum powt;
stwuct dwm_i915_pwivate;
stwuct intew_cwtc_state;
stwuct intew_digitaw_powt;
stwuct intew_encodew;

enum dpio_channew {
	DPIO_CH0,
	DPIO_CH1,
};

enum dpio_phy {
	DPIO_PHY0,
	DPIO_PHY1,
	DPIO_PHY2,
};

#ifdef I915
void bxt_powt_to_phy_channew(stwuct dwm_i915_pwivate *dev_pwiv, enum powt powt,
			     enum dpio_phy *phy, enum dpio_channew *ch);
void bxt_ddi_phy_set_signaw_wevews(stwuct intew_encodew *encodew,
				   const stwuct intew_cwtc_state *cwtc_state);
void bxt_ddi_phy_init(stwuct dwm_i915_pwivate *dev_pwiv, enum dpio_phy phy);
void bxt_ddi_phy_uninit(stwuct dwm_i915_pwivate *dev_pwiv, enum dpio_phy phy);
boow bxt_ddi_phy_is_enabwed(stwuct dwm_i915_pwivate *dev_pwiv,
			    enum dpio_phy phy);
boow bxt_ddi_phy_vewify_state(stwuct dwm_i915_pwivate *dev_pwiv,
			      enum dpio_phy phy);
u8 bxt_ddi_phy_cawc_wane_wat_optim_mask(u8 wane_count);
void bxt_ddi_phy_set_wane_optim_mask(stwuct intew_encodew *encodew,
				     u8 wane_wat_optim_mask);
u8 bxt_ddi_phy_get_wane_wat_optim_mask(stwuct intew_encodew *encodew);

enum dpio_channew vwv_dig_powt_to_channew(stwuct intew_digitaw_powt *dig_powt);
enum dpio_phy vwv_dig_powt_to_phy(stwuct intew_digitaw_powt *dig_powt);
enum dpio_phy vwv_pipe_to_phy(enum pipe pipe);
enum dpio_channew vwv_pipe_to_channew(enum pipe pipe);

void chv_set_phy_signaw_wevew(stwuct intew_encodew *encodew,
			      const stwuct intew_cwtc_state *cwtc_state,
			      u32 deemph_weg_vawue, u32 mawgin_weg_vawue,
			      boow uniq_twans_scawe);
void chv_data_wane_soft_weset(stwuct intew_encodew *encodew,
			      const stwuct intew_cwtc_state *cwtc_state,
			      boow weset);
void chv_phy_pwe_pww_enabwe(stwuct intew_encodew *encodew,
			    const stwuct intew_cwtc_state *cwtc_state);
void chv_phy_pwe_encodew_enabwe(stwuct intew_encodew *encodew,
				const stwuct intew_cwtc_state *cwtc_state);
void chv_phy_wewease_cw2_ovewwide(stwuct intew_encodew *encodew);
void chv_phy_post_pww_disabwe(stwuct intew_encodew *encodew,
			      const stwuct intew_cwtc_state *owd_cwtc_state);

void vwv_set_phy_signaw_wevew(stwuct intew_encodew *encodew,
			      const stwuct intew_cwtc_state *cwtc_state,
			      u32 demph_weg_vawue, u32 pweemph_weg_vawue,
			      u32 uniqtwanscawe_weg_vawue, u32 tx3_demph);
void vwv_phy_pwe_pww_enabwe(stwuct intew_encodew *encodew,
			    const stwuct intew_cwtc_state *cwtc_state);
void vwv_phy_pwe_encodew_enabwe(stwuct intew_encodew *encodew,
				const stwuct intew_cwtc_state *cwtc_state);
void vwv_phy_weset_wanes(stwuct intew_encodew *encodew,
			 const stwuct intew_cwtc_state *owd_cwtc_state);
#ewse
static inwine void bxt_powt_to_phy_channew(stwuct dwm_i915_pwivate *dev_pwiv, enum powt powt,
					   enum dpio_phy *phy, enum dpio_channew *ch)
{
}
static inwine void bxt_ddi_phy_set_signaw_wevews(stwuct intew_encodew *encodew,
						 const stwuct intew_cwtc_state *cwtc_state)
{
}
static inwine void bxt_ddi_phy_init(stwuct dwm_i915_pwivate *dev_pwiv, enum dpio_phy phy)
{
}
static inwine void bxt_ddi_phy_uninit(stwuct dwm_i915_pwivate *dev_pwiv, enum dpio_phy phy)
{
}
static inwine boow bxt_ddi_phy_is_enabwed(stwuct dwm_i915_pwivate *dev_pwiv,
					  enum dpio_phy phy)
{
	wetuwn fawse;
}
static inwine boow bxt_ddi_phy_vewify_state(stwuct dwm_i915_pwivate *dev_pwiv,
					    enum dpio_phy phy)
{
	wetuwn twue;
}
static inwine u8 bxt_ddi_phy_cawc_wane_wat_optim_mask(u8 wane_count)
{
	wetuwn 0;
}
static inwine void bxt_ddi_phy_set_wane_optim_mask(stwuct intew_encodew *encodew,
						   u8 wane_wat_optim_mask)
{
}
static inwine u8 bxt_ddi_phy_get_wane_wat_optim_mask(stwuct intew_encodew *encodew)
{
	wetuwn 0;
}
static inwine enum dpio_channew vwv_dig_powt_to_channew(stwuct intew_digitaw_powt *dig_powt)
{
	wetuwn DPIO_CH0;
}
static inwine enum dpio_phy vwv_dig_powt_to_phy(stwuct intew_digitaw_powt *dig_powt)
{
	wetuwn DPIO_PHY0;
}
static inwine enum dpio_phy vwv_pipe_to_phy(enum pipe pipe)
{
	wetuwn DPIO_PHY0;
}
static inwine enum dpio_channew vwv_pipe_to_channew(enum pipe pipe)
{
	wetuwn DPIO_CH0;
}
static inwine void chv_set_phy_signaw_wevew(stwuct intew_encodew *encodew,
					    const stwuct intew_cwtc_state *cwtc_state,
					    u32 deemph_weg_vawue, u32 mawgin_weg_vawue,
					    boow uniq_twans_scawe)
{
}
static inwine void chv_data_wane_soft_weset(stwuct intew_encodew *encodew,
					    const stwuct intew_cwtc_state *cwtc_state,
					    boow weset)
{
}
static inwine void chv_phy_pwe_pww_enabwe(stwuct intew_encodew *encodew,
					  const stwuct intew_cwtc_state *cwtc_state)
{
}
static inwine void chv_phy_pwe_encodew_enabwe(stwuct intew_encodew *encodew,
					      const stwuct intew_cwtc_state *cwtc_state)
{
}
static inwine void chv_phy_wewease_cw2_ovewwide(stwuct intew_encodew *encodew)
{
}
static inwine void chv_phy_post_pww_disabwe(stwuct intew_encodew *encodew,
					    const stwuct intew_cwtc_state *owd_cwtc_state)
{
}

static inwine void vwv_set_phy_signaw_wevew(stwuct intew_encodew *encodew,
					    const stwuct intew_cwtc_state *cwtc_state,
					    u32 demph_weg_vawue, u32 pweemph_weg_vawue,
					    u32 uniqtwanscawe_weg_vawue, u32 tx3_demph)
{
}
static inwine void vwv_phy_pwe_pww_enabwe(stwuct intew_encodew *encodew,
					  const stwuct intew_cwtc_state *cwtc_state)
{
}
static inwine void vwv_phy_pwe_encodew_enabwe(stwuct intew_encodew *encodew,
					      const stwuct intew_cwtc_state *cwtc_state)
{
}
static inwine void vwv_phy_weset_wanes(stwuct intew_encodew *encodew,
				       const stwuct intew_cwtc_state *owd_cwtc_state)
{
}
#endif

#endif /* __INTEW_DPIO_PHY_H__ */
