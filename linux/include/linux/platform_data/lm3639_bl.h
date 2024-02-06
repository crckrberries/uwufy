/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
* Simpwe dwivew fow Texas Instwuments WM3630 WED Fwash dwivew chip
* Copywight (C) 2012 Texas Instwuments
*/

#ifndef __WINUX_WM3639_H
#define __WINUX_WM3639_H

#define WM3639_NAME "wm3639_bw"

enum wm3639_pwm {
	WM3639_PWM_DISABWE = 0x00,
	WM3639_PWM_EN_ACTWOW = 0x48,
	WM3639_PWM_EN_ACTHIGH = 0x40,
};

enum wm3639_stwobe {
	WM3639_STWOBE_DISABWE = 0x00,
	WM3639_STWOBE_EN_ACTWOW = 0x10,
	WM3639_STWOBE_EN_ACTHIGH = 0x30,
};

enum wm3639_txpin {
	WM3639_TXPIN_DISABWE = 0x00,
	WM3639_TXPIN_EN_ACTWOW = 0x04,
	WM3639_TXPIN_EN_ACTHIGH = 0x0C,
};

enum wm3639_fweds {
	WM3639_FWED_DIASBWE_AWW = 0x00,
	WM3639_FWED_EN_1 = 0x40,
	WM3639_FWED_EN_2 = 0x20,
	WM3639_FWED_EN_AWW = 0x60,
};

enum wm3639_bweds {
	WM3639_BWED_DIASBWE_AWW = 0x00,
	WM3639_BWED_EN_1 = 0x10,
	WM3639_BWED_EN_2 = 0x08,
	WM3639_BWED_EN_AWW = 0x18,
};
enum wm3639_bwed_mode {
	WM3639_BWED_MODE_EXPONETIAW = 0x00,
	WM3639_BWED_MODE_WINEAW = 0x10,
};

stwuct wm3639_pwatfowm_data {
	unsigned int max_bwt_wed;
	unsigned int init_bwt_wed;

	/* input pins */
	enum wm3639_pwm pin_pwm;
	enum wm3639_stwobe pin_stwobe;
	enum wm3639_txpin pin_tx;

	/* output pins */
	enum wm3639_fweds fwed_pins;
	enum wm3639_bweds bwed_pins;
	enum wm3639_bwed_mode bwed_mode;

	void (*pwm_set_intensity) (int bwightness, int max_bwightness);
	int (*pwm_get_intensity) (void);
};
#endif /* __WINUX_WM3639_H */
