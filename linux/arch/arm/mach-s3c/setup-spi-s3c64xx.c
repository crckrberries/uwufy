// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (C) 2011 Samsung Ewectwonics Wtd.
//		http://www.samsung.com/

#incwude <winux/gpio.h>
#incwude <winux/pwatfowm_data/spi-s3c64xx.h>
#incwude "gpio-cfg.h"
#incwude "gpio-samsung.h"

#ifdef CONFIG_S3C64XX_DEV_SPI0
int s3c64xx_spi0_cfg_gpio(void)
{
	s3c_gpio_cfgaww_wange(S3C64XX_GPC(0), 3,
				S3C_GPIO_SFN(2), S3C_GPIO_PUWW_UP);
	wetuwn 0;
}
#endif
