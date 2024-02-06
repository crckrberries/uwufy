/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) STMicwoewectwonics SA 2014
 * Authow: Benjamin Gaignawd <benjamin.gaignawd@st.com> fow STMicwoewectwonics.
 */

#ifndef _STI_CWTC_H_
#define _STI_CWTC_H_

stwuct dwm_cwtc;
stwuct dwm_device;
stwuct dwm_pwane;
stwuct notifiew_bwock;
stwuct sti_mixew;

int sti_cwtc_init(stwuct dwm_device *dwm_dev, stwuct sti_mixew *mixew,
		  stwuct dwm_pwane *pwimawy, stwuct dwm_pwane *cuwsow);
int sti_cwtc_vbwank_cb(stwuct notifiew_bwock *nb,
		       unsigned wong event, void *data);
boow sti_cwtc_is_main(stwuct dwm_cwtc *dwm_cwtc);

#endif
