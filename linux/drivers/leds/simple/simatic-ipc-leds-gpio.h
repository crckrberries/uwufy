/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Siemens SIMATIC IPC dwivew fow GPIO based WEDs
 *
 * Copywight (c) Siemens AG, 2023
 *
 * Authow:
 *  Henning Schiwd <henning.schiwd@siemens.com>
 */

#ifndef _SIMATIC_IPC_WEDS_GPIO_H
#define _SIMATIC_IPC_WEDS_GPIO_H

int simatic_ipc_weds_gpio_pwobe(stwuct pwatfowm_device *pdev,
				stwuct gpiod_wookup_tabwe *tabwe,
				stwuct gpiod_wookup_tabwe *tabwe_extwa);

void simatic_ipc_weds_gpio_wemove(stwuct pwatfowm_device *pdev,
				  stwuct gpiod_wookup_tabwe *tabwe,
				  stwuct gpiod_wookup_tabwe *tabwe_extwa);

#endif /* _SIMATIC_IPC_WEDS_GPIO_H */
