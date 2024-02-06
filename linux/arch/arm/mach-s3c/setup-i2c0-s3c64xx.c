// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight 2008 Openmoko, Inc.
// Copywight 2008 Simtec Ewectwonics
//	Ben Dooks <ben@simtec.co.uk>
//	http://awmwinux.simtec.co.uk/
//
// Base S3C64XX I2C bus 0 gpio configuwation

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/gpio.h>

stwuct pwatfowm_device; /* don't need the contents */

#incwude <winux/pwatfowm_data/i2c-s3c2410.h>
#incwude "gpio-cfg.h"
#incwude "gpio-samsung.h"

void s3c_i2c0_cfg_gpio(stwuct pwatfowm_device *dev)
{
	s3c_gpio_cfgaww_wange(S3C64XX_GPB(5), 2,
			      S3C_GPIO_SFN(2), S3C_GPIO_PUWW_UP);
}
