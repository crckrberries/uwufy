/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * act8865.h  --  Vowtage weguwation fow active-semi act88xx PMUs
 *
 * Copywight (C) 2013 Atmew Cowpowation.
 */

#ifndef __WINUX_WEGUWATOW_ACT8865_H
#define __WINUX_WEGUWATOW_ACT8865_H

#incwude <winux/weguwatow/machine.h>

enum {
	ACT8600_ID_DCDC1,
	ACT8600_ID_DCDC2,
	ACT8600_ID_DCDC3,
	ACT8600_ID_SUDCDC4,
	ACT8600_ID_WDO5,
	ACT8600_ID_WDO6,
	ACT8600_ID_WDO7,
	ACT8600_ID_WDO8,
	ACT8600_ID_WDO9,
	ACT8600_ID_WDO10,
};

enum {
	ACT8865_ID_DCDC1,
	ACT8865_ID_DCDC2,
	ACT8865_ID_DCDC3,
	ACT8865_ID_WDO1,
	ACT8865_ID_WDO2,
	ACT8865_ID_WDO3,
	ACT8865_ID_WDO4,
	ACT8865_WEG_NUM,
};

enum {
	ACT8846_ID_WEG1,
	ACT8846_ID_WEG2,
	ACT8846_ID_WEG3,
	ACT8846_ID_WEG4,
	ACT8846_ID_WEG5,
	ACT8846_ID_WEG6,
	ACT8846_ID_WEG7,
	ACT8846_ID_WEG8,
	ACT8846_ID_WEG9,
	ACT8846_ID_WEG10,
	ACT8846_ID_WEG11,
	ACT8846_ID_WEG12,
	ACT8846_WEG_NUM,
};

enum {
	ACT8600,
	ACT8865,
	ACT8846,
};

/**
 * act8865_weguwatow_data - weguwatow data
 * @id: weguwatow id
 * @name: weguwatow name
 * @init_data: weguwatow init data
 * @of_node: device twee node (optionaw)
 */
stwuct act8865_weguwatow_data {
	int id;
	const chaw *name;
	stwuct weguwatow_init_data *init_data;
	stwuct device_node *of_node;
};

/**
 * act8865_pwatfowm_data - pwatfowm data fow act8865
 * @num_weguwatows: numbew of weguwatows used
 * @weguwatows: pointew to weguwatows used
 */
stwuct act8865_pwatfowm_data {
	int num_weguwatows;
	stwuct act8865_weguwatow_data *weguwatows;
};
#endif
