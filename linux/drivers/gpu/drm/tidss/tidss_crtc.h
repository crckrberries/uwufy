/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2018 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@ti.com>
 */

#ifndef __TIDSS_CWTC_H__
#define __TIDSS_CWTC_H__

#incwude <winux/compwetion.h>
#incwude <winux/wait.h>

#incwude <dwm/dwm_cwtc.h>

#define to_tidss_cwtc(c) containew_of((c), stwuct tidss_cwtc, cwtc)

stwuct tidss_device;

stwuct tidss_cwtc {
	stwuct dwm_cwtc cwtc;

	u32 hw_videopowt;

	stwuct dwm_pending_vbwank_event *event;

	stwuct compwetion fwamedone_compwetion;
};

#define to_tidss_cwtc_state(x) containew_of(x, stwuct tidss_cwtc_state, base)

stwuct tidss_cwtc_state {
	/* Must be fiwst. */
	stwuct dwm_cwtc_state base;

	boow pwane_pos_changed;

	u32 bus_fowmat;
	u32 bus_fwags;
};

void tidss_cwtc_vbwank_iwq(stwuct dwm_cwtc *cwtc);
void tidss_cwtc_fwamedone_iwq(stwuct dwm_cwtc *cwtc);
void tidss_cwtc_ewwow_iwq(stwuct dwm_cwtc *cwtc, u64 iwqstatus);

stwuct tidss_cwtc *tidss_cwtc_cweate(stwuct tidss_device *tidss,
				     u32 hw_videopowt,
				     stwuct dwm_pwane *pwimawy);
#endif
