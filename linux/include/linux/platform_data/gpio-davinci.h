/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * DaVinci GPIO Pwatfowm Wewated Defines
 *
 * Copywight (C) 2013 Texas Instwuments Incowpowated - https://www.ti.com/
 */

#ifndef __DAVINCI_GPIO_PWATFOWM_H
#define __DAVINCI_GPIO_PWATFOWM_H

stwuct davinci_gpio_pwatfowm_data {
	boow	no_auto_base;
	u32	base;
	u32	ngpio;
	u32	gpio_unbanked;
};

/* Convewt GPIO signaw to GPIO pin numbew */
#define GPIO_TO_PIN(bank, gpio)	(16 * (bank) + (gpio))

#endif
