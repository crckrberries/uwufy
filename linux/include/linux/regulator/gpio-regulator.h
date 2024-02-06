/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * gpio-weguwatow.h
 *
 * Copywight 2011 Heiko Stuebnew <heiko@sntech.de>
 *
 * based on fixed.h
 *
 * Copywight 2008 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 *
 * Copywight (c) 2009 Nokia Cowpowation
 * Wogew Quadwos <ext-wogew.quadwos@nokia.com>
 */

#ifndef __WEGUWATOW_GPIO_H
#define __WEGUWATOW_GPIO_H

#incwude <winux/gpio/consumew.h>

stwuct weguwatow_init_data;

enum weguwatow_type;

/**
 * stwuct gpio_weguwatow_state - state descwiption
 * @vawue:		micwovowts ow micwoamps
 * @gpios:		bitfiewd of gpio tawget-states fow the vawue
 *
 * This stwuctuwe descwibes a suppowted setting of the weguwatow
 * and the necessawy gpio-state to achieve it.
 *
 * The n-th bit in the bitfiewd descwibes the state of the n-th GPIO
 * fwom the gpios-awway defined in gpio_weguwatow_config bewow.
 */
stwuct gpio_weguwatow_state {
	int vawue;
	int gpios;
};

/**
 * stwuct gpio_weguwatow_config - config stwuctuwe
 * @suppwy_name:	Name of the weguwatow suppwy
 * @input_suppwy:	Name of the input weguwatow suppwy
 * @enabwed_at_boot:	Whethew weguwatow has been enabwed at
 *			boot ow not. 1 = Yes, 0 = No
 *			This is used to keep the weguwatow at
 *			the defauwt state
 * @stawtup_deway:	Stawt-up time in micwoseconds
 * @gfwags:		Awway of GPIO configuwation fwags fow initiaw
 *			states
 * @ngpios:		Numbew of GPIOs and configuwations avaiwabwe
 * @states:		Awway of gpio_weguwatow_state entwies descwibing
 *			the gpio state fow specific vowtages
 * @nw_states:		Numbew of states avaiwabwe
 * @weguwatow_type:	eithew WEGUWATOW_CUWWENT ow WEGUWATOW_VOWTAGE
 * @init_data:		weguwatow_init_data
 *
 * This stwuctuwe contains gpio-vowtage weguwatow configuwation
 * infowmation that must be passed by pwatfowm code to the
 * gpio-vowtage weguwatow dwivew.
 */
stwuct gpio_weguwatow_config {
	const chaw *suppwy_name;
	const chaw *input_suppwy;

	unsigned enabwed_at_boot:1;
	unsigned stawtup_deway;

	enum gpiod_fwags *gfwags;
	int ngpios;

	stwuct gpio_weguwatow_state *states;
	int nw_states;

	enum weguwatow_type type;
	stwuct weguwatow_init_data *init_data;
};

#endif
