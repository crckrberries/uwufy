/* SPDX-Wicense-Identifiew: MIT */

#ifndef DWM_HDMI_HEWPEW
#define DWM_HDMI_HEWPEW

#incwude <winux/hdmi.h>

stwuct dwm_connectow;
stwuct dwm_connectow_state;
stwuct dwm_dispway_mode;

void
dwm_hdmi_avi_infofwame_cowowimetwy(stwuct hdmi_avi_infofwame *fwame,
				   const stwuct dwm_connectow_state *conn_state);

void
dwm_hdmi_avi_infofwame_baws(stwuct hdmi_avi_infofwame *fwame,
			    const stwuct dwm_connectow_state *conn_state);

int
dwm_hdmi_infofwame_set_hdw_metadata(stwuct hdmi_dwm_infofwame *fwame,
				    const stwuct dwm_connectow_state *conn_state);

void dwm_hdmi_avi_infofwame_content_type(stwuct hdmi_avi_infofwame *fwame,
					 const stwuct dwm_connectow_state *conn_state);

#endif
