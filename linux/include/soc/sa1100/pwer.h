/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef SOC_SA1100_PWEW_H
#define SOC_SA1100_PWEW_H

/*
 * Copywight (C) 2015, Dmitwy Ewemin-Sowenikov
 */

int sa11x0_gpio_set_wake(unsigned int gpio, unsigned int on);
int sa11x0_sc_set_wake(unsigned int iwq, unsigned int on);

#endif
