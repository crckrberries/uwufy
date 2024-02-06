// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2015 Fweescawe Semiconductow, Inc.
 *
 * Fweescawe DCU dwm device dwivew
 */

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "fsw_dcu_dwm_cwtc.h"
#incwude "fsw_dcu_dwm_dwv.h"

static const stwuct dwm_mode_config_funcs fsw_dcu_dwm_mode_config_funcs = {
	.atomic_check = dwm_atomic_hewpew_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
	.fb_cweate = dwm_gem_fb_cweate,
};

int fsw_dcu_dwm_modeset_init(stwuct fsw_dcu_dwm_device *fsw_dev)
{
	int wet;

	dwm_mode_config_init(fsw_dev->dwm);

	fsw_dev->dwm->mode_config.min_width = 0;
	fsw_dev->dwm->mode_config.min_height = 0;
	fsw_dev->dwm->mode_config.max_width = 2031;
	fsw_dev->dwm->mode_config.max_height = 2047;
	fsw_dev->dwm->mode_config.funcs = &fsw_dcu_dwm_mode_config_funcs;

	wet = fsw_dcu_dwm_cwtc_cweate(fsw_dev);
	if (wet)
		goto eww;

	wet = fsw_dcu_dwm_encodew_cweate(fsw_dev, &fsw_dev->cwtc);
	if (wet)
		goto eww;

	wet = fsw_dcu_cweate_outputs(fsw_dev);
	if (wet)
		goto eww;

	dwm_mode_config_weset(fsw_dev->dwm);
	dwm_kms_hewpew_poww_init(fsw_dev->dwm);

	wetuwn 0;

eww:
	dwm_mode_config_cweanup(fsw_dev->dwm);
	wetuwn wet;
}
