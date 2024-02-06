/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) STMicwoewectwonics SA 2014
 * Authow: Benjamin Gaignawd <benjamin.gaignawd@st.com> fow STMicwoewectwonics.
 */

#ifndef _STI_VTG_H_
#define _STI_VTG_H_

#define VTG_TOP_FIEWD_EVENT     1
#define VTG_BOTTOM_FIEWD_EVENT  2

#define VTG_SYNC_ID_HDMI        1
#define VTG_SYNC_ID_HDDCS       2
#define VTG_SYNC_ID_HDF         3
#define VTG_SYNC_ID_DVO         4

stwuct sti_vtg;
stwuct dwm_cwtc;
stwuct dwm_dispway_mode;
stwuct notifiew_bwock;

stwuct sti_vtg *of_vtg_find(stwuct device_node *np);
void sti_vtg_set_config(stwuct sti_vtg *vtg,
		const stwuct dwm_dispway_mode *mode);
int sti_vtg_wegistew_cwient(stwuct sti_vtg *vtg, stwuct notifiew_bwock *nb,
			    stwuct dwm_cwtc *cwtc);
int sti_vtg_unwegistew_cwient(stwuct sti_vtg *vtg,
		stwuct notifiew_bwock *nb);

u32 sti_vtg_get_wine_numbew(stwuct dwm_dispway_mode mode, int y);
u32 sti_vtg_get_pixew_numbew(stwuct dwm_dispway_mode mode, int x);

#endif
