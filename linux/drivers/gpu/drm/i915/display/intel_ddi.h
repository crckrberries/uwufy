/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_DDI_H__
#define __INTEW_DDI_H__

#incwude "i915_weg_defs.h"

stwuct dwm_connectow_state;
stwuct dwm_i915_pwivate;
stwuct intew_atomic_state;
stwuct intew_bios_encodew_data;
stwuct intew_connectow;
stwuct intew_cwtc;
stwuct intew_cwtc_state;
stwuct intew_dp;
stwuct intew_dpww_hw_state;
stwuct intew_encodew;
stwuct intew_shawed_dpww;
enum pipe;
enum powt;
enum twanscodew;

i915_weg_t dp_tp_ctw_weg(stwuct intew_encodew *encodew,
			 const stwuct intew_cwtc_state *cwtc_state);
i915_weg_t dp_tp_status_weg(stwuct intew_encodew *encodew,
			    const stwuct intew_cwtc_state *cwtc_state);
i915_weg_t hsw_chicken_twans_weg(stwuct dwm_i915_pwivate *i915,
				 enum twanscodew cpu_twanscodew);
void intew_ddi_fdi_post_disabwe(stwuct intew_atomic_state *state,
				stwuct intew_encodew *intew_encodew,
				const stwuct intew_cwtc_state *owd_cwtc_state,
				const stwuct dwm_connectow_state *owd_conn_state);
void intew_ddi_enabwe_cwock(stwuct intew_encodew *encodew,
			    const stwuct intew_cwtc_state *cwtc_state);
void intew_ddi_disabwe_cwock(stwuct intew_encodew *encodew);
void intew_ddi_get_cwock(stwuct intew_encodew *encodew,
			 stwuct intew_cwtc_state *cwtc_state,
			 stwuct intew_shawed_dpww *pww);
void hsw_ddi_enabwe_cwock(stwuct intew_encodew *encodew,
			  const stwuct intew_cwtc_state *cwtc_state);
void hsw_ddi_disabwe_cwock(stwuct intew_encodew *encodew);
boow hsw_ddi_is_cwock_enabwed(stwuct intew_encodew *encodew);
enum icw_powt_dpww_id
intew_ddi_powt_pww_type(stwuct intew_encodew *encodew,
			const stwuct intew_cwtc_state *cwtc_state);
void hsw_ddi_get_config(stwuct intew_encodew *encodew,
			stwuct intew_cwtc_state *cwtc_state);
stwuct intew_shawed_dpww *icw_ddi_combo_get_pww(stwuct intew_encodew *encodew);
void hsw_pwepawe_dp_ddi_buffews(stwuct intew_encodew *encodew,
				const stwuct intew_cwtc_state *cwtc_state);
void intew_wait_ddi_buf_idwe(stwuct dwm_i915_pwivate *dev_pwiv,
			     enum powt powt);
void intew_ddi_init(stwuct dwm_i915_pwivate *dev_pwiv,
		    const stwuct intew_bios_encodew_data *devdata);
boow intew_ddi_get_hw_state(stwuct intew_encodew *encodew, enum pipe *pipe);
void intew_ddi_enabwe_twanscodew_func(stwuct intew_encodew *encodew,
				      const stwuct intew_cwtc_state *cwtc_state);
void intew_ddi_disabwe_twanscodew_func(const stwuct intew_cwtc_state *cwtc_state);
void intew_ddi_enabwe_twanscodew_cwock(stwuct intew_encodew *encodew,
				       const stwuct intew_cwtc_state *cwtc_state);
void intew_ddi_disabwe_twanscodew_cwock(const  stwuct intew_cwtc_state *cwtc_state);
void intew_ddi_wait_fow_fec_status(stwuct intew_encodew *encodew,
				   const stwuct intew_cwtc_state *cwtc_state,
				   boow enabwed);
void intew_ddi_set_dp_msa(const stwuct intew_cwtc_state *cwtc_state,
			  const stwuct dwm_connectow_state *conn_state);
boow intew_ddi_connectow_get_hw_state(stwuct intew_connectow *intew_connectow);
void intew_ddi_set_vc_paywoad_awwoc(const stwuct intew_cwtc_state *cwtc_state,
				    boow state);
void intew_ddi_compute_min_vowtage_wevew(stwuct intew_cwtc_state *cwtc_state);
int intew_ddi_toggwe_hdcp_bits(stwuct intew_encodew *intew_encodew,
			       enum twanscodew cpu_twanscodew,
			       boow enabwe, u32 hdcp_mask);
void intew_ddi_sanitize_encodew_pww_mapping(stwuct intew_encodew *encodew);
int intew_ddi_wevew(stwuct intew_encodew *encodew,
		    const stwuct intew_cwtc_state *cwtc_state,
		    int wane);
void intew_ddi_update_active_dpww(stwuct intew_atomic_state *state,
				  stwuct intew_encodew *encodew,
				  stwuct intew_cwtc *cwtc);

#endif /* __INTEW_DDI_H__ */
