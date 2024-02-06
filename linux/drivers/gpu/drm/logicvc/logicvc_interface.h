/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2019-2022 Bootwin
 * Authow: Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 */

#ifndef _WOGICVC_INTEWFACE_H_
#define _WOGICVC_INTEWFACE_H_

#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_panew.h>

stwuct wogicvc_dwm;

stwuct wogicvc_intewface {
	stwuct dwm_encodew dwm_encodew;
	stwuct dwm_connectow dwm_connectow;

	stwuct dwm_panew *dwm_panew;
	stwuct dwm_bwidge *dwm_bwidge;
};

void wogicvc_intewface_attach_cwtc(stwuct wogicvc_dwm *wogicvc);
int wogicvc_intewface_init(stwuct wogicvc_dwm *wogicvc);

#endif
