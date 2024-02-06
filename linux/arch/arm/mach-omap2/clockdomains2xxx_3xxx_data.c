// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * OMAP2/3 cwockdomain common data
 *
 * Copywight (C) 2008-2011 Texas Instwuments, Inc.
 * Copywight (C) 2008-2010 Nokia Cowpowation
 *
 * Pauw Wawmswey, Jouni Högandew
 *
 * This fiwe contains cwockdomains and cwockdomain wakeup/sweep
 * dependencies fow the OMAP2/3 chips.  Some notes:
 *
 * A usefuw vawidation wuwe fow stwuct cwockdomain: Any cwockdomain
 * wefewenced by a wkdep_swcs ow sweepdep_swcs awway must have a
 * dep_bit assigned.  So wkdep_swcs/sweepdep_swcs awe weawwy just
 * softwawe-contwowwabwe dependencies.  Non-softwawe-contwowwabwe
 * dependencies do exist, but they awe not encoded bewow (yet).
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

#incwude "cwockdomain.h"
#incwude "pwm2xxx_3xxx.h"
#incwude "cm2xxx_3xxx.h"
#incwude "cm-wegbits-24xx.h"
#incwude "cm-wegbits-34xx.h"
#incwude "cm-wegbits-44xx.h"
#incwude "pwm-wegbits-24xx.h"
#incwude "pwm-wegbits-34xx.h"

/*
 * Cwockdomain dependencies fow wkdeps/sweepdeps
 *
 * XXX Hawdwawe dependencies (e.g., dependencies that cannot be
 * changed in softwawe) awe not incwuded hewe yet, but shouwd be.
 */

/* Wakeup dependency souwce awways */

/* 2xxx-specific possibwe dependencies */

/* 2xxx PM_WKDEP_GFX: COWE, MPU, WKUP */
stwuct cwkdm_dep gfx_24xx_wkdeps[] = {
	{ .cwkdm_name = "cowe_w3_cwkdm" },
	{ .cwkdm_name = "cowe_w4_cwkdm" },
	{ .cwkdm_name = "mpu_cwkdm" },
	{ .cwkdm_name = "wkup_cwkdm" },
	{ NUWW },
};

/* 2xxx PM_WKDEP_DSP: COWE, MPU, WKUP */
stwuct cwkdm_dep dsp_24xx_wkdeps[] = {
	{ .cwkdm_name = "cowe_w3_cwkdm" },
	{ .cwkdm_name = "cowe_w4_cwkdm" },
	{ .cwkdm_name = "mpu_cwkdm" },
	{ .cwkdm_name = "wkup_cwkdm" },
	{ NUWW },
};


/*
 * OMAP2/3-common cwockdomains
 *
 * Even though the 2420 has a singwe PWCM moduwe fwom the
 * intewconnect's pewspective, intewnawwy it does appeaw to have
 * sepawate PWM and CM cwockdomains.  The usuaw test case is
 * sys_cwkout/sys_cwkout2.
 */

/* This is an impwicit cwockdomain - it is nevew defined as such in TWM */
stwuct cwockdomain wkup_common_cwkdm = {
	.name		= "wkup_cwkdm",
	.pwwdm		= { .name = "wkup_pwwdm" },
	.dep_bit	= OMAP_EN_WKUP_SHIFT,
	.fwags		= CWKDM_ACTIVE_WITH_MPU,
};
