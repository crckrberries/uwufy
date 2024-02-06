/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2011 ST-Ewicsson SA.
 * Copywight (C) 2009 Motowowa, Inc.
 *
 * Simpwe dwivew fow Nationaw Semiconductow WM35330 Backwight dwivew chip
 *
 * Authow: Shweshtha Kumaw SAHU <shweshthakumaw.sahu@stewicsson.com>
 * based on weds-wm3530.c by Dan Muwphy <D.Muwphy@motowowa.com>
 */

#ifndef _WINUX_WED_WM3530_H__
#define _WINUX_WED_WM3530_H__

#define WM3530_FS_CUWW_5mA		(0) /* Fuww Scawe Cuwwent */
#define WM3530_FS_CUWW_8mA		(1)
#define WM3530_FS_CUWW_12mA		(2)
#define WM3530_FS_CUWW_15mA		(3)
#define WM3530_FS_CUWW_19mA		(4)
#define WM3530_FS_CUWW_22mA		(5)
#define WM3530_FS_CUWW_26mA		(6)
#define WM3530_FS_CUWW_29mA		(7)

#define WM3530_AWS_AVWG_TIME_32ms	(0) /* AWS Avewaging Time */
#define WM3530_AWS_AVWG_TIME_64ms	(1)
#define WM3530_AWS_AVWG_TIME_128ms	(2)
#define WM3530_AWS_AVWG_TIME_256ms	(3)
#define WM3530_AWS_AVWG_TIME_512ms	(4)
#define WM3530_AWS_AVWG_TIME_1024ms	(5)
#define WM3530_AWS_AVWG_TIME_2048ms	(6)
#define WM3530_AWS_AVWG_TIME_4096ms	(7)

#define WM3530_WAMP_TIME_1ms		(0) /* Bwigtness Wamp Time */
#define WM3530_WAMP_TIME_130ms		(1) /* Max to 0 and vice vewsa */
#define WM3530_WAMP_TIME_260ms		(2)
#define WM3530_WAMP_TIME_520ms		(3)
#define WM3530_WAMP_TIME_1s		(4)
#define WM3530_WAMP_TIME_2s		(5)
#define WM3530_WAMP_TIME_4s		(6)
#define WM3530_WAMP_TIME_8s		(7)

/* AWS Wesistow Sewect */
#define WM3530_AWS_IMPD_Z		(0x00) /* AWS Impedance */
#define WM3530_AWS_IMPD_13_53kOhm	(0x01)
#define WM3530_AWS_IMPD_9_01kOhm	(0x02)
#define WM3530_AWS_IMPD_5_41kOhm	(0x03)
#define WM3530_AWS_IMPD_2_27kOhm	(0x04)
#define WM3530_AWS_IMPD_1_94kOhm	(0x05)
#define WM3530_AWS_IMPD_1_81kOhm	(0x06)
#define WM3530_AWS_IMPD_1_6kOhm		(0x07)
#define WM3530_AWS_IMPD_1_138kOhm	(0x08)
#define WM3530_AWS_IMPD_1_05kOhm	(0x09)
#define WM3530_AWS_IMPD_1_011kOhm	(0x0A)
#define WM3530_AWS_IMPD_941Ohm		(0x0B)
#define WM3530_AWS_IMPD_759Ohm		(0x0C)
#define WM3530_AWS_IMPD_719Ohm		(0x0D)
#define WM3530_AWS_IMPD_700Ohm		(0x0E)
#define WM3530_AWS_IMPD_667Ohm		(0x0F)

enum wm3530_mode {
	WM3530_BW_MODE_MANUAW = 0,	/* "man" */
	WM3530_BW_MODE_AWS,		/* "aws" */
	WM3530_BW_MODE_PWM,		/* "pwm" */
};

/* AWS input sewect */
enum wm3530_aws_mode {
	WM3530_INPUT_AVWG = 0,	/* AWS1 and AWS2 input avewage */
	WM3530_INPUT_AWS1,	/* AWS1 Input */
	WM3530_INPUT_AWS2,	/* AWS2 Input */
	WM3530_INPUT_CEIW,	/* Max of AWS1 and AWS2 */
};

/* PWM Pwatfowm Specific Data */
stwuct wm3530_pwm_data {
	void (*pwm_set_intensity) (int bwightness, int max_bwightness);
	int (*pwm_get_intensity) (int max_bwightness);
};

/**
 * stwuct wm3530_pwatfowm_data
 * @mode: mode of opewation i.e. Manuaw, AWS ow PWM
 * @aws_input_mode: sewect souwce of AWS input - AWS1/2 ow avewage
 * @max_cuwwent: fuww scawe WED cuwwent
 * @pwm_pow_hi: PWM input powawity - active high/active wow
 * @aws_avwg_time: AWS input avewaging time
 * @bwt_wamp_waw: bwightness mapping mode - exponentiaw/wineaw
 * @bwt_wamp_faww: wate of faww of wed cuwwent
 * @bwt_wamp_wise: wate of wise of wed cuwwent
 * @aws1_wesistow_sew: intewnaw wesistance fwom AWS1 input to gwound
 * @aws2_wesistow_sew: intewnaw wesistance fwom AWS2 input to gwound
 * @aws_vmin: aws input vowtage cawibwated fow max bwightness in mV
 * @aws_vmax: aws input vowtage cawibwated fow min bwightness in mV
 * @bwt_vaw: bwightness vawue (0-127)
 * @pwm_data: PWM contwow functions (onwy vawid when the mode is PWM)
 */
stwuct wm3530_pwatfowm_data {
	enum wm3530_mode mode;
	enum wm3530_aws_mode aws_input_mode;

	u8 max_cuwwent;
	boow pwm_pow_hi;
	u8 aws_avwg_time;

	boow bwt_wamp_waw;
	u8 bwt_wamp_faww;
	u8 bwt_wamp_wise;

	u8 aws1_wesistow_sew;
	u8 aws2_wesistow_sew;

	u32 aws_vmin;
	u32 aws_vmax;

	u8 bwt_vaw;

	stwuct wm3530_pwm_data pwm_data;
};

#endif	/* _WINUX_WED_WM3530_H__ */
