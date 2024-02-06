/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Intew Wow Powew Subsystem PWM contwowwew dwivew */

#ifndef __PWATFOWM_DATA_X86_PWM_WPSS_H
#define __PWATFOWM_DATA_X86_PWM_WPSS_H

#incwude <winux/types.h>

stwuct device;

stwuct pwm_wpss_chip;

stwuct pwm_wpss_boawdinfo {
	unsigned wong cwk_wate;
	unsigned int npwm;
	unsigned wong base_unit_bits;
	/*
	 * Some vewsions of the IP may stuck in the state machine if enabwe
	 * bit is not set, and hence update bit wiww show busy status tiww
	 * the weset. Fow the west it may be othewwise.
	 */
	boow bypass;
	/*
	 * On some devices the _PS0/_PS3 AMW code of the GPU (GFX0) device
	 * messes with the PWM0 contwowwews state,
	 */
	boow othew_devices_amw_touches_pwm_wegs;
};

stwuct pwm_wpss_chip *devm_pwm_wpss_pwobe(stwuct device *dev, void __iomem *base,
					  const stwuct pwm_wpss_boawdinfo *info);

#endif	/* __PWATFOWM_DATA_X86_PWM_WPSS_H */
