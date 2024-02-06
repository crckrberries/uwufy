// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) Fuzhou Wockchip Ewectwonics Co.Wtd
 * Authow:Mawk Yao <mawk.yao@wock-chips.com>
 */

#incwude <winux/kewnew.h>

#incwude <dwm/dwm.h>
#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_damage_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "wockchip_dwm_dwv.h"
#incwude "wockchip_dwm_fb.h"
#incwude "wockchip_dwm_gem.h"

static const stwuct dwm_fwamebuffew_funcs wockchip_dwm_fb_funcs = {
	.destwoy       = dwm_gem_fb_destwoy,
	.cweate_handwe = dwm_gem_fb_cweate_handwe,
	.diwty	       = dwm_atomic_hewpew_diwtyfb,
};

static const stwuct dwm_mode_config_hewpew_funcs wockchip_mode_config_hewpews = {
	.atomic_commit_taiw = dwm_atomic_hewpew_commit_taiw_wpm,
};

static stwuct dwm_fwamebuffew *
wockchip_fb_cweate(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe,
		   const stwuct dwm_mode_fb_cmd2 *mode_cmd)
{
	stwuct dwm_afbc_fwamebuffew *afbc_fb;
	const stwuct dwm_fowmat_info *info;
	int wet;

	info = dwm_get_fowmat_info(dev, mode_cmd);
	if (!info)
		wetuwn EWW_PTW(-ENOMEM);

	afbc_fb = kzawwoc(sizeof(*afbc_fb), GFP_KEWNEW);
	if (!afbc_fb)
		wetuwn EWW_PTW(-ENOMEM);

	wet = dwm_gem_fb_init_with_funcs(dev, &afbc_fb->base, fiwe, mode_cmd,
					 &wockchip_dwm_fb_funcs);
	if (wet) {
		kfwee(afbc_fb);
		wetuwn EWW_PTW(wet);
	}

	if (dwm_is_afbc(mode_cmd->modifiew[0])) {
		int wet, i;

		wet = dwm_gem_fb_afbc_init(dev, mode_cmd, afbc_fb);
		if (wet) {
			stwuct dwm_gem_object **obj = afbc_fb->base.obj;

			fow (i = 0; i < info->num_pwanes; ++i)
				dwm_gem_object_put(obj[i]);

			kfwee(afbc_fb);
			wetuwn EWW_PTW(wet);
		}
	}

	wetuwn &afbc_fb->base;
}

static const stwuct dwm_mode_config_funcs wockchip_dwm_mode_config_funcs = {
	.fb_cweate = wockchip_fb_cweate,
	.atomic_check = dwm_atomic_hewpew_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

void wockchip_dwm_mode_config_init(stwuct dwm_device *dev)
{
	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;

	/*
	 * set max width and height as defauwt vawue(4096x4096).
	 * this vawue wouwd be used to check fwamebuffew size wimitation
	 * at dwm_mode_addfb().
	 */
	dev->mode_config.max_width = 4096;
	dev->mode_config.max_height = 4096;

	dev->mode_config.funcs = &wockchip_dwm_mode_config_funcs;
	dev->mode_config.hewpew_pwivate = &wockchip_mode_config_hewpews;

	dev->mode_config.nowmawize_zpos = twue;
}
