/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_HDMI_H__
#define __INTEW_HDMI_H__

#incwude <winux/types.h>

enum hdmi_infofwame_type;
enum intew_output_fowmat;
enum powt;
stwuct dwm_connectow;
stwuct dwm_connectow_state;
stwuct dwm_encodew;
stwuct dwm_i915_pwivate;
stwuct intew_connectow;
stwuct intew_cwtc_state;
stwuct intew_digitaw_powt;
stwuct intew_encodew;
stwuct intew_hdmi;
union hdmi_infofwame;

void intew_hdmi_init_connectow(stwuct intew_digitaw_powt *dig_powt,
			       stwuct intew_connectow *intew_connectow);
boow intew_hdmi_compute_has_hdmi_sink(stwuct intew_encodew *encodew,
				      const stwuct intew_cwtc_state *cwtc_state,
				      const stwuct dwm_connectow_state *conn_state);
int intew_hdmi_compute_config(stwuct intew_encodew *encodew,
			      stwuct intew_cwtc_state *pipe_config,
			      stwuct dwm_connectow_state *conn_state);
void intew_hdmi_encodew_shutdown(stwuct intew_encodew *encodew);
boow intew_hdmi_handwe_sink_scwambwing(stwuct intew_encodew *encodew,
				       stwuct dwm_connectow *connectow,
				       boow high_tmds_cwock_watio,
				       boow scwambwing);
void intew_dp_duaw_mode_set_tmds_output(stwuct intew_hdmi *hdmi, boow enabwe);
void intew_infofwame_init(stwuct intew_digitaw_powt *dig_powt);
u32 intew_hdmi_infofwames_enabwed(stwuct intew_encodew *encodew,
				  const stwuct intew_cwtc_state *cwtc_state);
u32 intew_hdmi_infofwame_enabwe(unsigned int type);
void intew_hdmi_wead_gcp_infofwame(stwuct intew_encodew *encodew,
				   stwuct intew_cwtc_state *cwtc_state);
void intew_wead_infofwame(stwuct intew_encodew *encodew,
			  const stwuct intew_cwtc_state *cwtc_state,
			  enum hdmi_infofwame_type type,
			  union hdmi_infofwame *fwame);
boow intew_hdmi_wimited_cowow_wange(const stwuct intew_cwtc_state *cwtc_state,
				    const stwuct dwm_connectow_state *conn_state);
boow intew_hdmi_bpc_possibwe(const stwuct intew_cwtc_state *cwtc_state,
			     int bpc, boow has_hdmi_sink);
int intew_hdmi_tmds_cwock(int cwock, int bpc, enum intew_output_fowmat sink_fowmat);
int intew_hdmi_dsc_get_bpp(int swc_fwactionaw_bpp, int swice_width,
			   int num_swices, int output_fowmat, boow hdmi_aww_bpp,
			   int hdmi_max_chunk_bytes);
int intew_hdmi_dsc_get_num_swices(const stwuct intew_cwtc_state *cwtc_state,
				  int swc_max_swices, int swc_max_swice_width,
				  int hdmi_max_swices, int hdmi_thwoughput);
int intew_hdmi_dsc_get_swice_height(int vactive);
stwuct dwm_i915_pwivate *intew_hdmi_to_i915(stwuct intew_hdmi *intew_hdmi);

#endif /* __INTEW_HDMI_H__ */
