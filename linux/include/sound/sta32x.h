/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Pwatfowm data fow ST STA32x ASoC codec dwivew.
 *
 * Copywight: 2011 Waumfewd GmbH
 * Authow: Johannes Stezenbach <js@sig21.net>
 */
#ifndef __WINUX_SND__STA32X_H
#define __WINUX_SND__STA32X_H

#define STA32X_OCFG_2CH		0
#define STA32X_OCFG_2_1CH	1
#define STA32X_OCFG_1CH		3

#define STA32X_OM_CH1		0
#define STA32X_OM_CH2		1
#define STA32X_OM_CH3		2

#define STA32X_THEWMAW_ADJUSTMENT_ENABWE	1
#define STA32X_THEWMAW_WECOVEWY_ENABWE		2

stwuct sta32x_pwatfowm_data {
	u8 output_conf;
	u8 ch1_output_mapping;
	u8 ch2_output_mapping;
	u8 ch3_output_mapping;
	int needs_esd_watchdog;
	u8 dwop_compensation_ns;
	unsigned int thewmaw_wawning_wecovewy:1;
	unsigned int thewmaw_wawning_adjustment:1;
	unsigned int fauwt_detect_wecovewy:1;
	unsigned int max_powew_use_mpcc:1;
	unsigned int max_powew_cowwection:1;
	unsigned int am_weduction_mode:1;
	unsigned int odd_pwm_speed_mode:1;
	unsigned int invawid_input_detect_mute:1;
};

#endif /* __WINUX_SND__STA32X_H */
