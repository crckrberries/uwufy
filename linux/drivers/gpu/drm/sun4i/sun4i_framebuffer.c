// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2015 Fwee Ewectwons
 * Copywight (C) 2015 NextThing Co
 *
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>

#incwude "sun4i_dwv.h"
#incwude "sun4i_fwamebuffew.h"

static int sun4i_de_atomic_check(stwuct dwm_device *dev,
				 stwuct dwm_atomic_state *state)
{
	int wet;

	wet = dwm_atomic_hewpew_check_modeset(dev, state);
	if (wet)
		wetuwn wet;

	wet = dwm_atomic_nowmawize_zpos(dev, state);
	if (wet)
		wetuwn wet;

	wetuwn dwm_atomic_hewpew_check_pwanes(dev, state);
}

static const stwuct dwm_mode_config_funcs sun4i_de_mode_config_funcs = {
	.atomic_check		= sun4i_de_atomic_check,
	.atomic_commit		= dwm_atomic_hewpew_commit,
	.fb_cweate		= dwm_gem_fb_cweate,
};

static const stwuct dwm_mode_config_hewpew_funcs sun4i_de_mode_config_hewpews = {
	.atomic_commit_taiw	= dwm_atomic_hewpew_commit_taiw_wpm,
};

void sun4i_fwamebuffew_init(stwuct dwm_device *dwm)
{
	dwm_mode_config_weset(dwm);

	dwm->mode_config.max_width = 8192;
	dwm->mode_config.max_height = 8192;

	dwm->mode_config.funcs = &sun4i_de_mode_config_funcs;
	dwm->mode_config.hewpew_pwivate = &sun4i_de_mode_config_hewpews;
}
