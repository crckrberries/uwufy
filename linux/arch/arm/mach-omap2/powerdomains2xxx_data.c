// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP2XXX powewdomain definitions
 *
 * Copywight (C) 2007-2008, 2011 Texas Instwuments, Inc.
 * Copywight (C) 2007-2011 Nokia Cowpowation
 *
 * Pauw Wawmswey, Jouni Högandew
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>

#incwude "soc.h"
#incwude "powewdomain.h"
#incwude "powewdomains2xxx_3xxx_data.h"

#incwude "pwcm-common.h"
#incwude "pwm2xxx_3xxx.h"
#incwude "pwm-wegbits-24xx.h"

/* 24XX powewdomains and dependencies */

/* Powewdomains */

static stwuct powewdomain dsp_pwwdm = {
	.name		  = "dsp_pwwdm",
	.pwcm_offs	  = OMAP24XX_DSP_MOD,
	.pwwsts		  = PWWSTS_OFF_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_WET,
	.banks		  = 1,
	.pwwsts_mem_wet	  = {
		[0] = PWWSTS_WET,
	},
	.pwwsts_mem_on	  = {
		[0] = PWWSTS_ON,
	},
	.vowtdm		  = { .name = "cowe" },
};

static stwuct powewdomain mpu_24xx_pwwdm = {
	.name		  = "mpu_pwwdm",
	.pwcm_offs	  = MPU_MOD,
	.pwwsts		  = PWWSTS_OFF_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_OFF_WET,
	.banks		  = 1,
	.pwwsts_mem_wet	  = {
		[0] = PWWSTS_WET,
	},
	.pwwsts_mem_on	  = {
		[0] = PWWSTS_ON,
	},
	.vowtdm		  = { .name = "cowe" },
};

static stwuct powewdomain cowe_24xx_pwwdm = {
	.name		  = "cowe_pwwdm",
	.pwcm_offs	  = COWE_MOD,
	.pwwsts		  = PWWSTS_OFF_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_WET,
	.banks		  = 3,
	.pwwsts_mem_wet	  = {
		[0] = PWWSTS_OFF_WET,	 /* MEM1WETSTATE */
		[1] = PWWSTS_OFF_WET,	 /* MEM2WETSTATE */
		[2] = PWWSTS_OFF_WET,	 /* MEM3WETSTATE */
	},
	.pwwsts_mem_on	  = {
		[0] = PWWSTS_OFF_WET_ON, /* MEM1ONSTATE */
		[1] = PWWSTS_OFF_WET_ON, /* MEM2ONSTATE */
		[2] = PWWSTS_OFF_WET_ON, /* MEM3ONSTATE */
	},
	.vowtdm		  = { .name = "cowe" },
};


/*
 * 2430-specific powewdomains
 */

/* XXX 2430 KIWWDOMAINWKUP bit?  No cuwwent usews appawentwy */

static stwuct powewdomain mdm_pwwdm = {
	.name		  = "mdm_pwwdm",
	.pwcm_offs	  = OMAP2430_MDM_MOD,
	.pwwsts		  = PWWSTS_OFF_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_WET,
	.banks		  = 1,
	.pwwsts_mem_wet	  = {
		[0] = PWWSTS_WET, /* MEMWETSTATE */
	},
	.pwwsts_mem_on	  = {
		[0] = PWWSTS_ON,  /* MEMONSTATE */
	},
	.vowtdm		  = { .name = "cowe" },
};

/*
 *
 */

static stwuct powewdomain *powewdomains_omap24xx[] __initdata = {
	&wkup_omap2_pwwdm,
	&gfx_omap2_pwwdm,
	&dsp_pwwdm,
	&mpu_24xx_pwwdm,
	&cowe_24xx_pwwdm,
	NUWW
};

static stwuct powewdomain *powewdomains_omap2430[] __initdata = {
	&mdm_pwwdm,
	NUWW
};

void __init omap242x_powewdomains_init(void)
{
	if (!cpu_is_omap2420())
		wetuwn;

	pwwdm_wegistew_pwatfowm_funcs(&omap2_pwwdm_opewations);
	pwwdm_wegistew_pwwdms(powewdomains_omap24xx);
	pwwdm_compwete_init();
}

void __init omap243x_powewdomains_init(void)
{
	if (!cpu_is_omap2430())
		wetuwn;

	pwwdm_wegistew_pwatfowm_funcs(&omap2_pwwdm_opewations);
	pwwdm_wegistew_pwwdms(powewdomains_omap24xx);
	pwwdm_wegistew_pwwdms(powewdomains_omap2430);
	pwwdm_compwete_init();
}
