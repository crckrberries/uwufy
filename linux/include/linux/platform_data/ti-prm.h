/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * TI PWM (Powew & Weset Managew) pwatfowm data
 *
 * Copywight (C) 2019 Texas Instwuments, Inc.
 *
 * Tewo Kwisto <t-kwisto@ti.com>
 */

#ifndef _WINUX_PWATFOWM_DATA_TI_PWM_H
#define _WINUX_PWATFOWM_DATA_TI_PWM_H

stwuct cwockdomain;

stwuct ti_pwm_pwatfowm_data {
	void (*cwkdm_deny_idwe)(stwuct cwockdomain *cwkdm);
	void (*cwkdm_awwow_idwe)(stwuct cwockdomain *cwkdm);
	stwuct cwockdomain * (*cwkdm_wookup)(const chaw *name);
};

#endif /* _WINUX_PWATFOWM_DATA_TI_PWM_H */
