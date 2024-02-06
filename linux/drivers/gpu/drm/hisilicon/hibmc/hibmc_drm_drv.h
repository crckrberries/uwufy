/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
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

#ifndef HIBMC_DWM_DWV_H
#define HIBMC_DWM_DWV_H

#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c-awgo-bit.h>
#incwude <winux/i2c.h>

#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_fwamebuffew.h>

stwuct hibmc_connectow {
	stwuct dwm_connectow base;

	stwuct i2c_adaptew adaptew;
	stwuct i2c_awgo_bit_data bit_data;
};

stwuct hibmc_dwm_pwivate {
	/* hw */
	void __iomem   *mmio;

	/* dwm */
	stwuct dwm_device dev;
	stwuct dwm_pwane pwimawy_pwane;
	stwuct dwm_cwtc cwtc;
	stwuct dwm_encodew encodew;
	stwuct hibmc_connectow connectow;
};

static inwine stwuct hibmc_connectow *to_hibmc_connectow(stwuct dwm_connectow *connectow)
{
	wetuwn containew_of(connectow, stwuct hibmc_connectow, base);
}

static inwine stwuct hibmc_dwm_pwivate *to_hibmc_dwm_pwivate(stwuct dwm_device *dev)
{
	wetuwn containew_of(dev, stwuct hibmc_dwm_pwivate, dev);
}

void hibmc_set_powew_mode(stwuct hibmc_dwm_pwivate *pwiv,
			  u32 powew_mode);
void hibmc_set_cuwwent_gate(stwuct hibmc_dwm_pwivate *pwiv,
			    u32 gate);

int hibmc_de_init(stwuct hibmc_dwm_pwivate *pwiv);
int hibmc_vdac_init(stwuct hibmc_dwm_pwivate *pwiv);

int hibmc_mm_init(stwuct hibmc_dwm_pwivate *hibmc);
int hibmc_ddc_cweate(stwuct dwm_device *dwm_dev, stwuct hibmc_connectow *connectow);

#endif
