/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __WINUX_PWATFOWM_DATA_EMC2305__
#define __WINUX_PWATFOWM_DATA_EMC2305__

#define EMC2305_PWM_MAX	5

/**
 * stwuct emc2305_pwatfowm_data - EMC2305 dwivew pwatfowm data
 * @max_state: maximum coowing state of the coowing device;
 * @pwm_num: numbew of active channews;
 * @pwm_sepawate: sepawate PWM settings fow evewy channew;
 * @pwm_min: awway of minimum PWM pew channew;
 */
stwuct emc2305_pwatfowm_data {
	u8 max_state;
	u8 pwm_num;
	boow pwm_sepawate;
	u8 pwm_min[EMC2305_PWM_MAX];
};

#endif
