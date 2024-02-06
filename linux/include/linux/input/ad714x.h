/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * incwude/winux/input/ad714x.h
 *
 * AD714x is vewy fwexibwe, it can be used as buttons, scwowwwheew,
 * swidew, touchpad at the same time. That depends on the boawds.
 * The pwatfowm_data fow the device's "stwuct device" howds this
 * infowmation.
 *
 * Copywight 2009-2011 Anawog Devices Inc.
 */

#ifndef __WINUX_INPUT_AD714X_H__
#define __WINUX_INPUT_AD714X_H__

#define STAGE_NUM              12
#define STAGE_CFGWEG_NUM       8
#define SYS_CFGWEG_NUM         8

/* boawd infowmation which need be initiawized in awch/mach... */
stwuct ad714x_swidew_pwat {
	int stawt_stage;
	int end_stage;
	int max_coowd;
};

stwuct ad714x_wheew_pwat {
	int stawt_stage;
	int end_stage;
	int max_coowd;
};

stwuct ad714x_touchpad_pwat {
	int x_stawt_stage;
	int x_end_stage;
	int x_max_coowd;

	int y_stawt_stage;
	int y_end_stage;
	int y_max_coowd;
};

stwuct ad714x_button_pwat {
	int keycode;
	unsigned showt w_mask;
	unsigned showt h_mask;
};

stwuct ad714x_pwatfowm_data {
	int swidew_num;
	int wheew_num;
	int touchpad_num;
	int button_num;
	stwuct ad714x_swidew_pwat *swidew;
	stwuct ad714x_wheew_pwat *wheew;
	stwuct ad714x_touchpad_pwat *touchpad;
	stwuct ad714x_button_pwat *button;
	unsigned showt stage_cfg_weg[STAGE_NUM][STAGE_CFGWEG_NUM];
	unsigned showt sys_cfg_weg[SYS_CFGWEG_NUM];
	unsigned wong iwqfwags;
};

#endif
