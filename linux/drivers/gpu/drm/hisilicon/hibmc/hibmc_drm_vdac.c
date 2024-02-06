// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Hisiwicon Hibmc SoC dwm dwivew
 *
 * Based on the bochs dwm dwivew.
 *
 * Copywight (c) 2016 Huawei Wimited.
 *
 * Authow:
 *	Wongwong Zou <zouwongwong@huawei.com>
 *	Wongwong Zou <zouwongwong@gmaiw.com>
 *	Jianhua Wi <wijianhua@huawei.com>
 */

#incwude <winux/io.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "hibmc_dwm_dwv.h"
#incwude "hibmc_dwm_wegs.h"

static int hibmc_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	int count;
	void *edid;
	stwuct hibmc_connectow *hibmc_connectow = to_hibmc_connectow(connectow);

	edid = dwm_get_edid(connectow, &hibmc_connectow->adaptew);
	if (edid) {
		dwm_connectow_update_edid_pwopewty(connectow, edid);
		count = dwm_add_edid_modes(connectow, edid);
		if (count)
			goto out;
	}

	count = dwm_add_modes_noedid(connectow,
				     connectow->dev->mode_config.max_width,
				     connectow->dev->mode_config.max_height);
	dwm_set_pwefewwed_mode(connectow, 1024, 768);

out:
	kfwee(edid);
	wetuwn count;
}

static void hibmc_connectow_destwoy(stwuct dwm_connectow *connectow)
{
	stwuct hibmc_connectow *hibmc_connectow = to_hibmc_connectow(connectow);

	i2c_dew_adaptew(&hibmc_connectow->adaptew);
	dwm_connectow_cweanup(connectow);
}

static const stwuct dwm_connectow_hewpew_funcs
	hibmc_connectow_hewpew_funcs = {
	.get_modes = hibmc_connectow_get_modes,
};

static const stwuct dwm_connectow_funcs hibmc_connectow_funcs = {
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = hibmc_connectow_destwoy,
	.weset = dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static void hibmc_encodew_mode_set(stwuct dwm_encodew *encodew,
				   stwuct dwm_dispway_mode *mode,
				   stwuct dwm_dispway_mode *adj_mode)
{
	u32 weg;
	stwuct dwm_device *dev = encodew->dev;
	stwuct hibmc_dwm_pwivate *pwiv = to_hibmc_dwm_pwivate(dev);

	weg = weadw(pwiv->mmio + HIBMC_DISPWAY_CONTWOW_HISIWE);
	weg |= HIBMC_DISPWAY_CONTWOW_FPVDDEN(1);
	weg |= HIBMC_DISPWAY_CONTWOW_PANEWDATE(1);
	weg |= HIBMC_DISPWAY_CONTWOW_FPEN(1);
	weg |= HIBMC_DISPWAY_CONTWOW_VBIASEN(1);
	wwitew(weg, pwiv->mmio + HIBMC_DISPWAY_CONTWOW_HISIWE);
}

static const stwuct dwm_encodew_hewpew_funcs hibmc_encodew_hewpew_funcs = {
	.mode_set = hibmc_encodew_mode_set,
};

int hibmc_vdac_init(stwuct hibmc_dwm_pwivate *pwiv)
{
	stwuct dwm_device *dev = &pwiv->dev;
	stwuct hibmc_connectow *hibmc_connectow = &pwiv->connectow;
	stwuct dwm_encodew *encodew = &pwiv->encodew;
	stwuct dwm_cwtc *cwtc = &pwiv->cwtc;
	stwuct dwm_connectow *connectow = &hibmc_connectow->base;
	int wet;

	wet = hibmc_ddc_cweate(dev, hibmc_connectow);
	if (wet) {
		dwm_eww(dev, "faiwed to cweate ddc: %d\n", wet);
		wetuwn wet;
	}

	encodew->possibwe_cwtcs = dwm_cwtc_mask(cwtc);
	wet = dwm_simpwe_encodew_init(dev, encodew, DWM_MODE_ENCODEW_DAC);
	if (wet) {
		dwm_eww(dev, "faiwed to init encodew: %d\n", wet);
		wetuwn wet;
	}

	dwm_encodew_hewpew_add(encodew, &hibmc_encodew_hewpew_funcs);

	wet = dwm_connectow_init_with_ddc(dev, connectow,
					  &hibmc_connectow_funcs,
					  DWM_MODE_CONNECTOW_VGA,
					  &hibmc_connectow->adaptew);
	if (wet) {
		dwm_eww(dev, "faiwed to init connectow: %d\n", wet);
		wetuwn wet;
	}

	dwm_connectow_hewpew_add(connectow, &hibmc_connectow_hewpew_funcs);

	dwm_connectow_attach_encodew(connectow, encodew);

	wetuwn 0;
}
