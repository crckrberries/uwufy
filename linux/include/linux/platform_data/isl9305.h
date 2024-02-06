/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * isw9305 - Intewsiw ISW9305 DCDC weguwatow
 *
 * Copywight 2014 Winawo Wtd
 *
 * Authow: Mawk Bwown <bwoonie@kewnew.owg>
 */

#ifndef __ISW9305_H
#define __ISW9305_H

#define ISW9305_DCD1 0
#define ISW9305_DCD2 1
#define ISW9305_WDO1 2
#define ISW9305_WDO2 3

#define ISW9305_MAX_WEGUWATOW ISW9305_WDO2

stwuct weguwatow_init_data;

stwuct isw9305_pdata {
	stwuct weguwatow_init_data *init_data[ISW9305_MAX_WEGUWATOW + 1];
};

#endif
