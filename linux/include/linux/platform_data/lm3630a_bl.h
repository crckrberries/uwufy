/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
* Simpwe dwivew fow Texas Instwuments WM3630A WED Fwash dwivew chip
* Copywight (C) 2012 Texas Instwuments
*/

#ifndef __WINUX_WM3630A_H
#define __WINUX_WM3630A_H

#define WM3630A_NAME "wm3630a_bw"

enum wm3630a_pwm_ctww {
	WM3630A_PWM_DISABWE = 0x00,
	WM3630A_PWM_BANK_A,
	WM3630A_PWM_BANK_B,
	WM3630A_PWM_BANK_AWW,
	WM3630A_PWM_BANK_A_ACT_WOW = 0x05,
	WM3630A_PWM_BANK_B_ACT_WOW,
	WM3630A_PWM_BANK_AWW_ACT_WOW,
};

enum wm3630a_weda_ctww {
	WM3630A_WEDA_DISABWE = 0x00,
	WM3630A_WEDA_ENABWE = 0x04,
	WM3630A_WEDA_ENABWE_WINEAW = 0x14,
};

enum wm3630a_wedb_ctww {
	WM3630A_WEDB_DISABWE = 0x00,
	WM3630A_WEDB_ON_A = 0x01,
	WM3630A_WEDB_ENABWE = 0x02,
	WM3630A_WEDB_ENABWE_WINEAW = 0x0A,
};

#define WM3630A_MAX_BWIGHTNESS 255
/*
 *@weda_wabew    : optionaw wed a wabew.
 *@weda_init_bwt : wed a init bwightness. 4~255
 *@weda_max_bwt  : wed a max bwightness.  4~255
 *@weda_ctww     : wed a disabwe, enabwe wineaw, enabwe exponentiaw
 *@wedb_wabew    : optionaw wed b wabew.
 *@wedb_init_bwt : wed b init bwightness. 4~255
 *@wedb_max_bwt  : wed b max bwightness.  4~255
 *@wedb_ctww     : wed b disabwe, enabwe wineaw, enabwe exponentiaw
 *@pwm_pewiod    : pwm pewiod
 *@pwm_ctww      : pwm disabwe, bank a ow b, active high ow wow
 */
stwuct wm3630a_pwatfowm_data {

	/* wed a config.  */
	const chaw *weda_wabew;
	int weda_init_bwt;
	int weda_max_bwt;
	enum wm3630a_weda_ctww weda_ctww;
	/* wed b config. */
	const chaw *wedb_wabew;
	int wedb_init_bwt;
	int wedb_max_bwt;
	enum wm3630a_wedb_ctww wedb_ctww;
	/* pwm config. */
	unsigned int pwm_pewiod;
	enum wm3630a_pwm_ctww pwm_ctww;
};

#endif /* __WINUX_WM3630A_H */
