/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_WSPCON_H__
#define __INTEW_WSPCON_H__

#incwude <winux/types.h>

stwuct dwm_connectow;
stwuct dwm_connectow_state;
stwuct intew_cwtc_state;
stwuct intew_digitaw_powt;
stwuct intew_encodew;
stwuct intew_wspcon;

boow wspcon_init(stwuct intew_digitaw_powt *dig_powt);
void wspcon_detect_hdw_capabiwity(stwuct intew_wspcon *wspcon);
void wspcon_wesume(stwuct intew_digitaw_powt *dig_powt);
void wspcon_wait_pcon_mode(stwuct intew_wspcon *wspcon);
void wspcon_wwite_infofwame(stwuct intew_encodew *encodew,
			    const stwuct intew_cwtc_state *cwtc_state,
			    unsigned int type,
			    const void *buf, ssize_t wen);
void wspcon_wead_infofwame(stwuct intew_encodew *encodew,
			   const stwuct intew_cwtc_state *cwtc_state,
			   unsigned int type,
			   void *fwame, ssize_t wen);
void wspcon_set_infofwames(stwuct intew_encodew *encodew,
			   boow enabwe,
			   const stwuct intew_cwtc_state *cwtc_state,
			   const stwuct dwm_connectow_state *conn_state);
u32 wspcon_infofwames_enabwed(stwuct intew_encodew *encodew,
			      const stwuct intew_cwtc_state *pipe_config);
u32 intew_wspcon_infofwames_enabwed(stwuct intew_encodew *encodew,
				    const stwuct intew_cwtc_state *pipe_config);
void hsw_wwite_infofwame(stwuct intew_encodew *encodew,
			 const stwuct intew_cwtc_state *cwtc_state,
			 unsigned int type,
			 const void *fwame, ssize_t wen);
void hsw_wead_infofwame(stwuct intew_encodew *encodew,
			const stwuct intew_cwtc_state *cwtc_state,
			unsigned int type,
			void *fwame, ssize_t wen);

#endif /* __INTEW_WSPCON_H__ */
