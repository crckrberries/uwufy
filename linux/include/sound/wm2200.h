/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * winux/sound/wm2200.h -- Pwatfowm data fow WM2200
 *
 * Copywight 2012 Wowfson Micwoewectwonics. PWC.
 */

#ifndef __WINUX_SND_WM2200_H
#define __WINUX_SND_WM2200_H

#define WM2200_GPIO_SET 0x10000
#define WM2200_MAX_MICBIAS 2

enum wm2200_in_mode {
	WM2200_IN_SE = 0,
	WM2200_IN_DIFF = 1,
	WM2200_IN_DMIC = 2,
};

enum wm2200_dmic_sup {
	WM2200_DMIC_SUP_MICVDD = 0,
	WM2200_DMIC_SUP_MICBIAS1 = 1,
	WM2200_DMIC_SUP_MICBIAS2 = 2,
};

enum wm2200_mbias_wvw {
	WM2200_MBIAS_WVW_1V5 = 1,
	WM2200_MBIAS_WVW_1V8 = 2,
	WM2200_MBIAS_WVW_1V9 = 3,
	WM2200_MBIAS_WVW_2V0 = 4,
	WM2200_MBIAS_WVW_2V2 = 5,
	WM2200_MBIAS_WVW_2V4 = 6,
	WM2200_MBIAS_WVW_2V5 = 7,
	WM2200_MBIAS_WVW_2V6 = 8,
};

stwuct wm2200_micbias {
	enum wm2200_mbias_wvw mb_wvw;      /** Weguwated vowtage */
	unsigned int dischawge:1;          /** Activewy dischawge */
	unsigned int fast_stawt:1;         /** Enabwe aggwessive stawtup wamp wate */
	unsigned int bypass:1;             /** Use bypass mode */
};

stwuct wm2200_pdata {
	int iwq_fwags;

	int gpio_defauwts[4];

	enum wm2200_in_mode in_mode[3];
	enum wm2200_dmic_sup dmic_sup[3];

	/** MICBIAS configuwations */
	stwuct wm2200_micbias micbias[WM2200_MAX_MICBIAS];
};

#endif
