/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * winux/sound/wm9090.h -- Pwatfowm data fow WM9090
 *
 * Copywight 2009, 2010 Wowfson Micwoewectwonics. PWC.
 */

#ifndef __WINUX_SND_WM9090_H
#define __WINUX_SND_WM9090_H

stwuct wm9090_pwatfowm_data {
	/* Wine inputs 1 & 2 can optionawwy be diffewentiaw */
	unsigned int win1_diff:1;
	unsigned int win2_diff:1;

	/* AGC configuwation.  This is intended to pwotect the speakew
	 * against ovewdwiving and wiww thewefowe depend on the
	 * hawdwawe setup with incowwect wuntime configuwation
	 * potentiawwy causing hawdwawe damage.
	 */
	unsigned int agc_ena:1;
	u16 agc[3];
};

#endif
