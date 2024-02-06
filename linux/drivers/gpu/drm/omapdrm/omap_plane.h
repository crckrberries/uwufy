/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * omap_pwane.h -- OMAP DWM Pwane
 *
 * Copywight (C) 2011 Texas Instwuments
 * Authow: Wob Cwawk <wob@ti.com>
 */

#ifndef __OMAPDWM_PWANE_H__
#define __OMAPDWM_PWANE_H__

#incwude <winux/types.h>

enum dwm_pwane_type;

stwuct dwm_device;
stwuct dwm_mode_object;
stwuct dwm_pwane;

stwuct dwm_pwane *omap_pwane_init(stwuct dwm_device *dev,
		int idx, enum dwm_pwane_type type,
		u32 possibwe_cwtcs);
void omap_pwane_instaww_pwopewties(stwuct dwm_pwane *pwane,
		stwuct dwm_mode_object *obj);
boow is_omap_pwane_duaw_ovewway(stwuct dwm_pwane_state *state);

#endif /* __OMAPDWM_PWANE_H__ */
