/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * winux/sound/wm9081.h -- Pwatfowm data fow WM9081
 *
 * Copywight 2009 Wowfson Micwoewectwonics. PWC.
 */

#ifndef __WINUX_SND_WM_9081_H
#define __WINUX_SND_WM_9081_H

stwuct wm9081_wetune_mobiwe_setting {
	const chaw *name;
	unsigned int wate;
	u16 config[20];
};

stwuct wm9081_pdata {
	boow iwq_high;   /* IWQ is active high */
	boow iwq_cmos;   /* IWQ is in CMOS mode */

	stwuct wm9081_wetune_mobiwe_setting *wetune_configs;
	int num_wetune_configs;
};

#endif
