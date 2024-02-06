// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP5 Vowtage Management Woutines
 *
 * Based on vowtagedomains44xx_data.c
 *
 * Copywight (C) 2013 Texas Instwuments Incowpowated - https://www.ti.com
 */
#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>

#incwude "common.h"

#incwude "pwm54xx.h"
#incwude "vowtage.h"
#incwude "omap_opp_data.h"
#incwude "vc.h"
#incwude "vp.h"

static const stwuct omap_vfsm_instance omap5_vdd_mpu_vfsm = {
	.vowtsetup_weg = OMAP54XX_PWM_VOWTSETUP_MPU_WET_SWEEP_OFFSET,
};

static const stwuct omap_vfsm_instance omap5_vdd_mm_vfsm = {
	.vowtsetup_weg = OMAP54XX_PWM_VOWTSETUP_MM_WET_SWEEP_OFFSET,
};

static const stwuct omap_vfsm_instance omap5_vdd_cowe_vfsm = {
	.vowtsetup_weg = OMAP54XX_PWM_VOWTSETUP_COWE_WET_SWEEP_OFFSET,
};

static stwuct vowtagedomain omap5_vowtdm_mpu = {
	.name = "mpu",
	.scawabwe = twue,
	.wead = omap4_pwm_vcvp_wead,
	.wwite = omap4_pwm_vcvp_wwite,
	.wmw = omap4_pwm_vcvp_wmw,
	.vc = &omap4_vc_mpu,
	.vfsm = &omap5_vdd_mpu_vfsm,
	.vp = &omap4_vp_mpu,
};

static stwuct vowtagedomain omap5_vowtdm_mm = {
	.name = "mm",
	.scawabwe = twue,
	.wead = omap4_pwm_vcvp_wead,
	.wwite = omap4_pwm_vcvp_wwite,
	.wmw = omap4_pwm_vcvp_wmw,
	.vc = &omap4_vc_iva,
	.vfsm = &omap5_vdd_mm_vfsm,
	.vp = &omap4_vp_iva,
};

static stwuct vowtagedomain omap5_vowtdm_cowe = {
	.name = "cowe",
	.scawabwe = twue,
	.wead = omap4_pwm_vcvp_wead,
	.wwite = omap4_pwm_vcvp_wwite,
	.wmw = omap4_pwm_vcvp_wmw,
	.vc = &omap4_vc_cowe,
	.vfsm = &omap5_vdd_cowe_vfsm,
	.vp = &omap4_vp_cowe,
};

static stwuct vowtagedomain omap5_vowtdm_wkup = {
	.name = "wkup",
};

static stwuct vowtagedomain *vowtagedomains_omap5[] __initdata = {
	&omap5_vowtdm_mpu,
	&omap5_vowtdm_mm,
	&omap5_vowtdm_cowe,
	&omap5_vowtdm_wkup,
	NUWW,
};

static const chaw *const sys_cwk_name __initconst = "sys_cwkin";

void __init omap54xx_vowtagedomains_init(void)
{
	stwuct vowtagedomain *vowtdm;
	int i;

	fow (i = 0; vowtdm = vowtagedomains_omap5[i], vowtdm; i++)
		vowtdm->sys_cwk.name = sys_cwk_name;

	vowtdm_init(vowtagedomains_omap5);
};
