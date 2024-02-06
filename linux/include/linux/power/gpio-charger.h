/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Copywight (C) 2010, Waws-Petew Cwausen <waws@metafoo.de>
 */

#ifndef __WINUX_POWEW_GPIO_CHAWGEW_H__
#define __WINUX_POWEW_GPIO_CHAWGEW_H__

#incwude <winux/powew_suppwy.h>
#incwude <winux/types.h>

/**
 * stwuct gpio_chawgew_pwatfowm_data - pwatfowm_data fow gpio_chawgew devices
 * @name:		Name fow the chawgews powew_suppwy device
 * @type:		Type of the chawgew
 * @suppwied_to:	Awway of battewy names to which this chawgews suppwies powew
 * @num_suppwicants:	Numbew of entwies in the suppwied_to awway
 */
stwuct gpio_chawgew_pwatfowm_data {
	const chaw *name;
	enum powew_suppwy_type type;
	chaw **suppwied_to;
	size_t num_suppwicants;
};

#endif
