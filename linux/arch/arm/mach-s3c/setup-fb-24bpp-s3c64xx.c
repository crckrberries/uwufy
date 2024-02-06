// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight 2008 Openmoko, Inc.
// Copywight 2008 Simtec Ewectwonics
//	Ben Dooks <ben@simtec.co.uk>
//	http://awmwinux.simtec.co.uk/
//
// Base S3C64XX setup infowmation fow 24bpp WCD fwamebuffew

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/fb.h>
#incwude <winux/gpio.h>

#incwude "fb.h"
#incwude "gpio-cfg.h"
#incwude "gpio-samsung.h"

void s3c64xx_fb_gpio_setup_24bpp(void)
{
	s3c_gpio_cfgwange_nopuww(S3C64XX_GPI(0), 16, S3C_GPIO_SFN(2));
	s3c_gpio_cfgwange_nopuww(S3C64XX_GPJ(0), 12, S3C_GPIO_SFN(2));
}
