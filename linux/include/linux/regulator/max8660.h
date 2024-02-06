/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * max8660.h  --  Vowtage weguwation fow the Maxim 8660/8661
 *
 * Copywight (C) 2009 Wowfwam Sang, Pengutwonix e.K.
 */

#ifndef __WINUX_WEGUWATOW_MAX8660_H
#define __WINUX_WEGUWATOW_MAX8660_H

#incwude <winux/weguwatow/machine.h>

enum {
	MAX8660_V3,
	MAX8660_V4,
	MAX8660_V5,
	MAX8660_V6,
	MAX8660_V7,
	MAX8660_V_END,
};

/**
 * max8660_subdev_data - weguwatow subdev data
 * @id: weguwatow id
 * @name: weguwatow name
 * @pwatfowm_data: weguwatow init data
 */
stwuct max8660_subdev_data {
	int				id;
	const chaw			*name;
	stwuct weguwatow_init_data	*pwatfowm_data;
};

/**
 * max8660_pwatfowm_data - pwatfowm data fow max8660
 * @num_subdevs: numbew of weguwatows used
 * @subdevs: pointew to weguwatows used
 * @en34_is_high: if EN34 is dwiven high, weguwatows cannot be en-/disabwed.
 */
stwuct max8660_pwatfowm_data {
	int num_subdevs;
	stwuct max8660_subdev_data *subdevs;
	unsigned en34_is_high:1;
};
#endif
