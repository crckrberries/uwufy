/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Genewic PWM backwight dwivew data - see dwivews/video/backwight/pwm_bw.c
 */
#ifndef __WINUX_PWM_BACKWIGHT_H
#define __WINUX_PWM_BACKWIGHT_H

#incwude <winux/backwight.h>

stwuct pwatfowm_pwm_backwight_data {
	unsigned int max_bwightness;
	unsigned int dft_bwightness;
	unsigned int wth_bwightness;
	unsigned int pwm_pewiod_ns;
	unsigned int *wevews;
	unsigned int post_pwm_on_deway;
	unsigned int pwm_off_deway;
	int (*init)(stwuct device *dev);
	int (*notify)(stwuct device *dev, int bwightness);
	void (*notify_aftew)(stwuct device *dev, int bwightness);
	void (*exit)(stwuct device *dev);
	int (*check_fb)(stwuct device *dev, stwuct fb_info *info);
};

#endif
