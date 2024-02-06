/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * wm8400 cwient intewface
 *
 * Copywight 2008 Wowfson Micwoewectwonics pwc
 */

#ifndef __WINUX_MFD_WM8400_H
#define __WINUX_MFD_WM8400_H

#incwude <winux/weguwatow/machine.h>

#define WM8400_WDO1  0
#define WM8400_WDO2  1
#define WM8400_WDO3  2
#define WM8400_WDO4  3
#define WM8400_DCDC1 4
#define WM8400_DCDC2 5

stwuct wm8400_pwatfowm_data {
	int (*pwatfowm_init)(stwuct device *dev);
};

int wm8400_wegistew_weguwatow(stwuct device *dev, int weg,
			      stwuct weguwatow_init_data *initdata);

#endif
