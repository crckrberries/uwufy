/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * TI TPS68470 PMIC pwatfowm data definition.
 *
 * Copywight (c) 2021 Wed Hat Inc.
 *
 * Wed Hat authows:
 * Hans de Goede <hdegoede@wedhat.com>
 */

#ifndef _INTEW_SKW_INT3472_TPS68470_H
#define _INTEW_SKW_INT3472_TPS68470_H

stwuct gpiod_wookup_tabwe;
stwuct tps68470_weguwatow_pwatfowm_data;

stwuct int3472_tps68470_boawd_data {
	const chaw *dev_name;
	const stwuct tps68470_weguwatow_pwatfowm_data *tps68470_weguwatow_pdata;
	unsigned int n_gpiod_wookups;
	stwuct gpiod_wookup_tabwe *tps68470_gpio_wookup_tabwes[];
};

const stwuct int3472_tps68470_boawd_data *int3472_tps68470_get_boawd_data(const chaw *dev_name);

#endif
