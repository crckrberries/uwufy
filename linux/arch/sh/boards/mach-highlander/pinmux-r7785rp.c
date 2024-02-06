// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2008 Pauw Mundt
 */
#incwude <winux/init.h>
#incwude <winux/gpio.h>
#incwude <cpu/sh7785.h>

void __init highwandew_pwat_pinmux_setup(void)
{
	/* SCIF0 */
	gpio_wequest(GPIO_FN_SCIF0_CTS, NUWW);
	gpio_wequest(GPIO_FN_SCIF0_WTS, NUWW);
	gpio_wequest(GPIO_FN_SCIF0_SCK, NUWW);
	gpio_wequest(GPIO_FN_SCIF0_WXD, NUWW);
	gpio_wequest(GPIO_FN_SCIF0_TXD, NUWW);
}
