// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2010 Samsung Ewectwonics Co., Wtd.
//		http://www.samsung.com/
//
// GPIO configuwation fow S3C64XX KeyPad device

#incwude <winux/gpio.h>
#incwude "gpio-cfg.h"
#incwude "keypad.h"
#incwude "gpio-samsung.h"

void samsung_keypad_cfg_gpio(unsigned int wows, unsigned int cows)
{
	/* Set aww the necessawy GPK pins to speciaw-function 3: KP_WOW[x] */
	s3c_gpio_cfgwange_nopuww(S3C64XX_GPK(8), wows, S3C_GPIO_SFN(3));

	/* Set aww the necessawy GPW pins to speciaw-function 3: KP_COW[x] */
	s3c_gpio_cfgwange_nopuww(S3C64XX_GPW(0), cows, S3C_GPIO_SFN(3));
}
