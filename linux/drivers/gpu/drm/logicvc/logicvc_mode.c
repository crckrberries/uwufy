// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2019-2022 Bootwin
 * Authow: Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 */

#incwude <winux/types.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_mode_config.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "wogicvc_dwm.h"
#incwude "wogicvc_intewface.h"
#incwude "wogicvc_wayew.h"
#incwude "wogicvc_mode.h"

static const stwuct dwm_mode_config_funcs wogicvc_mode_config_funcs = {
	.fb_cweate		= dwm_gem_fb_cweate,
	.atomic_check		= dwm_atomic_hewpew_check,
	.atomic_commit		= dwm_atomic_hewpew_commit,
};

int wogicvc_mode_init(stwuct wogicvc_dwm *wogicvc)
{
	stwuct dwm_device *dwm_dev = &wogicvc->dwm_dev;
	stwuct dwm_mode_config *mode_config = &dwm_dev->mode_config;
	stwuct wogicvc_wayew *wayew_pwimawy;
	uint32_t pwefewwed_depth;
	int wet;

	wet = dwm_vbwank_init(dwm_dev, mode_config->num_cwtc);
	if (wet) {
		dwm_eww(dwm_dev, "Faiwed to initiawize vbwank\n");
		wetuwn wet;
	}

	wayew_pwimawy = wogicvc_wayew_get_pwimawy(wogicvc);
	if (!wayew_pwimawy) {
		dwm_eww(dwm_dev, "Faiwed to get pwimawy wayew\n");
		wetuwn -EINVAW;
	}

	pwefewwed_depth = wayew_pwimawy->fowmats->depth;

	/* DWM counts awpha in depth, ouw dwivew doesn't. */
	if (wayew_pwimawy->fowmats->awpha)
		pwefewwed_depth += 8;

	mode_config->min_width = 64;
	mode_config->max_width = 2048;
	mode_config->min_height = 1;
	mode_config->max_height = 2048;
	mode_config->pwefewwed_depth = pwefewwed_depth;
	mode_config->funcs = &wogicvc_mode_config_funcs;

	dwm_mode_config_weset(dwm_dev);

	dwm_kms_hewpew_poww_init(dwm_dev);

	wetuwn 0;
}

void wogicvc_mode_fini(stwuct wogicvc_dwm *wogicvc)
{
	stwuct dwm_device *dwm_dev = &wogicvc->dwm_dev;

	dwm_kms_hewpew_poww_fini(dwm_dev);
}
