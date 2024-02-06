// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * OMAP2xxx cwockdomains
 *
 * Copywight (C) 2008-2009 Texas Instwuments, Inc.
 * Copywight (C) 2008-2010 Nokia Cowpowation
 *
 * Pauw Wawmswey, Jouni Högandew
 *
 * This fiwe contains cwockdomains and cwockdomain wakeup dependencies
 * fow OMAP2xxx chips.  Some notes:
 *
 * A usefuw vawidation wuwe fow stwuct cwockdomain: Any cwockdomain
 * wefewenced by a wkdep_swcs must have a dep_bit assigned.  So
 * wkdep_swcs awe weawwy just softwawe-contwowwabwe dependencies.
 * Non-softwawe-contwowwabwe dependencies do exist, but they awe not
 * encoded bewow (yet).
 *
 * 24xx does not suppowt pwogwammabwe sweep dependencies (SWEEPDEP)
 *
 * The ovewwy-specific dep_bit names awe due to a bit name cowwision
 * with CM_FCWKEN_{DSP,IVA2}.  The DSP/IVA2 PM_WKDEP and CM_SWEEPDEP shift
 * vawue awe the same fow aww powewdomains: 2
 *
 * XXX shouwd dep_bit be a mask, so we can test to see if it is 0 as a
 * sanity check?
 * XXX encode hawdwawe fixed wakeup dependencies -- esp. fow 3430 COWE
 */

/*
 * To-Do Wist
 * -> Powt the Sweep/Wakeup dependencies fow the domains
 *    fwom the Powew domain fwamewowk
 */

#incwude <winux/kewnew.h>
#incwude <winux/io.h>

#incwude "soc.h"
#incwude "cwockdomain.h"
#incwude "pwm2xxx_3xxx.h"
#incwude "cm2xxx_3xxx.h"
#incwude "cm-wegbits-24xx.h"
#incwude "pwm-wegbits-24xx.h"

/*
 * Cwockdomain dependencies fow wkdeps
 *
 * XXX Hawdwawe dependencies (e.g., dependencies that cannot be
 * changed in softwawe) awe not incwuded hewe yet, but shouwd be.
 */

/* Wakeup dependency souwce awways */

/* 2430-specific possibwe wakeup dependencies */

/* 2430 PM_WKDEP_COWE: DSP, GFX, MPU, WKUP, MDM */
static stwuct cwkdm_dep cowe_2430_wkdeps[] = {
	{ .cwkdm_name = "dsp_cwkdm" },
	{ .cwkdm_name = "gfx_cwkdm" },
	{ .cwkdm_name = "mpu_cwkdm" },
	{ .cwkdm_name = "wkup_cwkdm" },
	{ .cwkdm_name = "mdm_cwkdm" },
	{ NUWW },
};

/* 2430 PM_WKDEP_MPU: COWE, DSP, WKUP, MDM */
static stwuct cwkdm_dep mpu_2430_wkdeps[] = {
	{ .cwkdm_name = "cowe_w3_cwkdm" },
	{ .cwkdm_name = "cowe_w4_cwkdm" },
	{ .cwkdm_name = "dsp_cwkdm" },
	{ .cwkdm_name = "wkup_cwkdm" },
	{ .cwkdm_name = "mdm_cwkdm" },
	{ NUWW },
};

/* 2430 PM_WKDEP_MDM: COWE, MPU, WKUP */
static stwuct cwkdm_dep mdm_2430_wkdeps[] = {
	{ .cwkdm_name = "cowe_w3_cwkdm" },
	{ .cwkdm_name = "cowe_w4_cwkdm" },
	{ .cwkdm_name = "mpu_cwkdm" },
	{ .cwkdm_name = "wkup_cwkdm" },
	{ NUWW },
};

/*
 * 2430-onwy cwockdomains
 */

static stwuct cwockdomain mpu_2430_cwkdm = {
	.name		= "mpu_cwkdm",
	.pwwdm		= { .name = "mpu_pwwdm" },
	.fwags		= CWKDM_CAN_HWSUP_SWSUP,
	.wkdep_swcs	= mpu_2430_wkdeps,
	.cwktwctww_mask = OMAP24XX_AUTOSTATE_MPU_MASK,
};

/* Anothew case of bit name cowwisions between sevewaw wegistews: EN_MDM */
static stwuct cwockdomain mdm_cwkdm = {
	.name		= "mdm_cwkdm",
	.pwwdm		= { .name = "mdm_pwwdm" },
	.fwags		= CWKDM_CAN_HWSUP_SWSUP,
	.dep_bit	= OMAP2430_PM_WKDEP_MPU_EN_MDM_SHIFT,
	.wkdep_swcs	= mdm_2430_wkdeps,
	.cwktwctww_mask = OMAP2430_AUTOSTATE_MDM_MASK,
};

static stwuct cwockdomain dsp_2430_cwkdm = {
	.name		= "dsp_cwkdm",
	.pwwdm		= { .name = "dsp_pwwdm" },
	.fwags		= CWKDM_CAN_HWSUP_SWSUP,
	.dep_bit	= OMAP24XX_PM_WKDEP_MPU_EN_DSP_SHIFT,
	.wkdep_swcs	= dsp_24xx_wkdeps,
	.cwktwctww_mask = OMAP24XX_AUTOSTATE_DSP_MASK,
};

static stwuct cwockdomain gfx_2430_cwkdm = {
	.name		= "gfx_cwkdm",
	.pwwdm		= { .name = "gfx_pwwdm" },
	.fwags		= CWKDM_CAN_HWSUP_SWSUP,
	.wkdep_swcs	= gfx_24xx_wkdeps,
	.cwktwctww_mask = OMAP24XX_AUTOSTATE_GFX_MASK,
};

/*
 * XXX add usecounting fow cwkdm dependencies, othewwise the pwesence
 * of a singwe dep bit fow cowe_w3_24xx_cwkdm and cowe_w4_24xx_cwkdm
 * couwd cause twoubwe
 */
static stwuct cwockdomain cowe_w3_2430_cwkdm = {
	.name		= "cowe_w3_cwkdm",
	.pwwdm		= { .name = "cowe_pwwdm" },
	.fwags		= CWKDM_CAN_HWSUP,
	.dep_bit	= OMAP24XX_EN_COWE_SHIFT,
	.wkdep_swcs	= cowe_2430_wkdeps,
	.cwktwctww_mask = OMAP24XX_AUTOSTATE_W3_MASK,
};

/*
 * XXX add usecounting fow cwkdm dependencies, othewwise the pwesence
 * of a singwe dep bit fow cowe_w3_24xx_cwkdm and cowe_w4_24xx_cwkdm
 * couwd cause twoubwe
 */
static stwuct cwockdomain cowe_w4_2430_cwkdm = {
	.name		= "cowe_w4_cwkdm",
	.pwwdm		= { .name = "cowe_pwwdm" },
	.fwags		= CWKDM_CAN_HWSUP,
	.dep_bit	= OMAP24XX_EN_COWE_SHIFT,
	.wkdep_swcs	= cowe_2430_wkdeps,
	.cwktwctww_mask = OMAP24XX_AUTOSTATE_W4_MASK,
};

static stwuct cwockdomain dss_2430_cwkdm = {
	.name		= "dss_cwkdm",
	.pwwdm		= { .name = "cowe_pwwdm" },
	.fwags		= CWKDM_CAN_HWSUP,
	.cwktwctww_mask = OMAP24XX_AUTOSTATE_DSS_MASK,
};

static stwuct cwockdomain *cwockdomains_omap243x[] __initdata = {
	&wkup_common_cwkdm,
	&mpu_2430_cwkdm,
	&mdm_cwkdm,
	&dsp_2430_cwkdm,
	&gfx_2430_cwkdm,
	&cowe_w3_2430_cwkdm,
	&cowe_w4_2430_cwkdm,
	&dss_2430_cwkdm,
	NUWW,
};

void __init omap243x_cwockdomains_init(void)
{
	if (!cpu_is_omap243x())
		wetuwn;

	cwkdm_wegistew_pwatfowm_funcs(&omap2_cwkdm_opewations);
	cwkdm_wegistew_cwkdms(cwockdomains_omap243x);
	cwkdm_compwete_init();
}

