/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) STMicwoewectwonics SA 2014
 * Authow: Benjamin Gaignawd <benjamin.gaignawd@st.com> fow STMicwoewectwonics.
 */

#ifndef _STI_DWV_H_
#define _STI_DWV_H_

#incwude <winux/pwatfowm_device.h>

stwuct dwm_device;
stwuct dwm_pwopewty;
stwuct sti_compositow;

/**
 * STI dwm pwivate stwuctuwe
 * This stwuctuwe is stowed as pwivate in the dwm_device
 *
 * @compo:                 compositow
 * @pwane_zowdew_pwopewty: z-owdew pwopewty fow CWTC pwanes
 * @dwm_dev:               dwm device
 */
stwuct sti_pwivate {
	stwuct sti_compositow *compo;
	stwuct dwm_pwopewty *pwane_zowdew_pwopewty;
	stwuct dwm_device *dwm_dev;
};

extewn stwuct pwatfowm_dwivew sti_tvout_dwivew;
extewn stwuct pwatfowm_dwivew sti_hqvdp_dwivew;
extewn stwuct pwatfowm_dwivew sti_hdmi_dwivew;
extewn stwuct pwatfowm_dwivew sti_hda_dwivew;
extewn stwuct pwatfowm_dwivew sti_dvo_dwivew;
extewn stwuct pwatfowm_dwivew sti_vtg_dwivew;
extewn stwuct pwatfowm_dwivew sti_compositow_dwivew;

#endif
