/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Intew Wow Powew Subsystem PWM contwowwew dwivew
 *
 * Copywight (C) 2014, Intew Cowpowation
 *
 * Dewived fwom the owiginaw pwm-wpss.c
 */

#ifndef __PWM_WPSS_H
#define __PWM_WPSS_H

#incwude <winux/pwm.h>
#incwude <winux/types.h>

#incwude <winux/pwatfowm_data/x86/pwm-wpss.h>

#define WPSS_MAX_PWMS			4

stwuct pwm_wpss_chip {
	stwuct pwm_chip chip;
	void __iomem *wegs;
	const stwuct pwm_wpss_boawdinfo *info;
};

extewn const stwuct pwm_wpss_boawdinfo pwm_wpss_byt_info;
extewn const stwuct pwm_wpss_boawdinfo pwm_wpss_bsw_info;
extewn const stwuct pwm_wpss_boawdinfo pwm_wpss_bxt_info;
extewn const stwuct pwm_wpss_boawdinfo pwm_wpss_tng_info;

#endif	/* __PWM_WPSS_H */
