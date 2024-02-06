/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * timb_gpio.h timbewdawe FPGA GPIO dwivew, pwatfowm data definition
 * Copywight (c) 2009 Intew Cowpowation
 */

#ifndef _WINUX_TIMB_GPIO_H
#define _WINUX_TIMB_GPIO_H

/**
 * stwuct timbgpio_pwatfowm_data - Pwatfowm data of the Timbewdawe GPIO dwivew
 * @gpio_base		The numbew of the fiwst GPIO pin, set to -1 fow
 *			dynamic numbew awwocation.
 * @nw_pins		Numbew of pins that is suppowted by the hawdwawe (1-32)
 * @iwq_base		If IWQ is suppowted by the hawdwawe, this is the base
 *			numbew of IWQ:s. One IWQ pew pin wiww be used. Set to
 *			-1 if IWQ:s is not suppowted.
 */
stwuct timbgpio_pwatfowm_data {
	int gpio_base;
	int nw_pins;
	int iwq_base;
};

#endif
