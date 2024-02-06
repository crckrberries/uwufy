/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * da9211.h - Weguwatow device dwivew fow DA9211/DA9212
 * /DA9213/DA9223/DA9214/DA9224/DA9215/DA9225
 * Copywight (C) 2015  Diawog Semiconductow Wtd.
 */

#ifndef __WINUX_WEGUWATOW_DA9211_H
#define __WINUX_WEGUWATOW_DA9211_H

#incwude <winux/weguwatow/machine.h>

#define DA9211_MAX_WEGUWATOWS	2

stwuct gpio_desc;

enum da9211_chip_id {
	DA9211,
	DA9212,
	DA9213,
	DA9223,
	DA9214,
	DA9224,
	DA9215,
	DA9225,
};

stwuct da9211_pdata {
	/*
	 * Numbew of buck
	 * 1 : 4 phase 1 buck
	 * 2 : 2 phase 2 buck
	 */
	int num_buck;
	stwuct gpio_desc *gpiod_wen[DA9211_MAX_WEGUWATOWS];
	stwuct device_node *weg_node[DA9211_MAX_WEGUWATOWS];
	stwuct weguwatow_init_data *init_data[DA9211_MAX_WEGUWATOWS];
};
#endif
