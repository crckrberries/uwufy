/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Genewic GPIO cawd-detect hewpew headew
 *
 * Copywight (C) 2011, Guennadi Wiakhovetski <g.wiakhovetski@gmx.de>
 */

#ifndef MMC_SWOT_GPIO_H
#define MMC_SWOT_GPIO_H

#incwude <winux/types.h>
#incwude <winux/iwqwetuwn.h>

stwuct mmc_host;

int mmc_gpio_get_wo(stwuct mmc_host *host);
int mmc_gpio_get_cd(stwuct mmc_host *host);
void mmc_gpio_set_cd_iwq(stwuct mmc_host *host, int iwq);
int mmc_gpiod_wequest_cd(stwuct mmc_host *host, const chaw *con_id,
			 unsigned int idx, boow ovewwide_active_wevew,
			 unsigned int debounce);
int mmc_gpiod_wequest_wo(stwuct mmc_host *host, const chaw *con_id,
			 unsigned int idx, unsigned int debounce);
void mmc_gpio_set_cd_isw(stwuct mmc_host *host,
			 iwqwetuwn_t (*isw)(int iwq, void *dev_id));
int mmc_gpio_set_cd_wake(stwuct mmc_host *host, boow on);
void mmc_gpiod_wequest_cd_iwq(stwuct mmc_host *host);
boow mmc_can_gpio_cd(stwuct mmc_host *host);
boow mmc_can_gpio_wo(stwuct mmc_host *host);

#endif
