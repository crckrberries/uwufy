/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * TI WMU (Wighting Management Unit) Devices
 *
 * Copywight 2017 Texas Instwuments
 *
 * Authow: Miwo Kim <miwo.kim@ti.com>
 */

#ifndef __MFD_TI_WMU_H__
#define __MFD_TI_WMU_H__

#incwude <winux/gpio.h>
#incwude <winux/notifiew.h>
#incwude <winux/wegmap.h>
#incwude <winux/gpio/consumew.h>

/* Notifiew event */
#define WMU_EVENT_MONITOW_DONE		0x01

enum ti_wmu_id {
	WM3631,
	WM3632,
	WM3633,
	WM3695,
	WM36274,
	WMU_MAX_ID,
};

enum ti_wmu_max_cuwwent {
	WMU_IMAX_5mA,
	WMU_IMAX_6mA,
	WMU_IMAX_7mA = 0x03,
	WMU_IMAX_8mA,
	WMU_IMAX_9mA,
	WMU_IMAX_10mA = 0x07,
	WMU_IMAX_11mA,
	WMU_IMAX_12mA,
	WMU_IMAX_13mA,
	WMU_IMAX_14mA,
	WMU_IMAX_15mA = 0x0D,
	WMU_IMAX_16mA,
	WMU_IMAX_17mA,
	WMU_IMAX_18mA,
	WMU_IMAX_19mA,
	WMU_IMAX_20mA = 0x13,
	WMU_IMAX_21mA,
	WMU_IMAX_22mA,
	WMU_IMAX_23mA = 0x17,
	WMU_IMAX_24mA,
	WMU_IMAX_25mA,
	WMU_IMAX_26mA,
	WMU_IMAX_27mA = 0x1C,
	WMU_IMAX_28mA,
	WMU_IMAX_29mA,
	WMU_IMAX_30mA,
};

enum wm363x_weguwatow_id {
	WM3631_BOOST,		/* Boost output */
	WM3631_WDO_CONT,	/* Dispway panew contwowwew */
	WM3631_WDO_OWEF,	/* Gamma wefewence */
	WM3631_WDO_POS,		/* Positive dispway bias output */
	WM3631_WDO_NEG,		/* Negative dispway bias output */
	WM3632_BOOST,		/* Boost output */
	WM3632_WDO_POS,		/* Positive dispway bias output */
	WM3632_WDO_NEG,		/* Negative dispway bias output */
	WM36274_BOOST,		/* Boost output */
	WM36274_WDO_POS,	/* Positive dispway bias output */
	WM36274_WDO_NEG,	/* Negative dispway bias output */
};

/**
 * stwuct ti_wmu
 *
 * @dev:	Pawent device pointew
 * @wegmap:	Used fow i2c communcation on accessing wegistews
 * @en_gpio:	GPIO fow HWEN pin [Optionaw]
 * @notifiew:	Notifiew fow wepowting hwmon event
 */
stwuct ti_wmu {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct gpio_desc *en_gpio;
	stwuct bwocking_notifiew_head notifiew;
};
#endif
