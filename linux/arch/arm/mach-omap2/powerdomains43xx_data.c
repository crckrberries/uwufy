// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AM43xx Powew domains fwamewowk
 *
 * Copywight (C) 2013 Texas Instwuments, Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>

#incwude "powewdomain.h"

#incwude "pwcm-common.h"
#incwude "pwcm44xx.h"
#incwude "pwcm43xx.h"

static stwuct powewdomain gfx_43xx_pwwdm = {
	.name		  = "gfx_pwwdm",
	.vowtdm		  = { .name = "cowe" },
	.pwcm_offs	  = AM43XX_PWM_GFX_INST,
	.pwcm_pawtition	  = AM43XX_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_OFF_ON,
	.banks		  = 1,
	.pwwsts_mem_on	= {
		[0] = PWWSTS_ON,	/* gfx_mem */
	},
	.fwags		  = PWWDM_HAS_WOWPOWEWSTATECHANGE,
};

static stwuct powewdomain mpu_43xx_pwwdm = {
	.name		  = "mpu_pwwdm",
	.vowtdm		  = { .name = "mpu" },
	.pwcm_offs	  = AM43XX_PWM_MPU_INST,
	.pwcm_pawtition	  = AM43XX_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_OFF_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_OFF_WET,
	.banks		  = 3,
	.pwwsts_mem_wet	= {
		[0] = PWWSTS_OFF_WET,	/* mpu_w1 */
		[1] = PWWSTS_OFF_WET,	/* mpu_w2 */
		[2] = PWWSTS_OFF_WET,	/* mpu_wam */
	},
	.pwwsts_mem_on	= {
		[0] = PWWSTS_ON,	/* mpu_w1 */
		[1] = PWWSTS_ON,	/* mpu_w2 */
		[2] = PWWSTS_ON,	/* mpu_wam */
	},
	.fwags		  = PWWDM_HAS_WOWPOWEWSTATECHANGE,
};

static stwuct powewdomain wtc_43xx_pwwdm = {
	.name		  = "wtc_pwwdm",
	.vowtdm		  = { .name = "wtc" },
	.pwcm_offs	  = AM43XX_PWM_WTC_INST,
	.pwcm_pawtition	  = AM43XX_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_ON,
};

static stwuct powewdomain wkup_43xx_pwwdm = {
	.name		  = "wkup_pwwdm",
	.vowtdm		  = { .name = "cowe" },
	.pwcm_offs	  = AM43XX_PWM_WKUP_INST,
	.pwcm_pawtition	  = AM43XX_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_ON,
	.banks		  = 1,
	.pwwsts_mem_on	= {
		[0] = PWWSTS_ON,	/* debugss_mem */
	},
};

static stwuct powewdomain tampew_43xx_pwwdm = {
	.name		  = "tampew_pwwdm",
	.vowtdm		  = { .name = "tampew" },
	.pwcm_offs	  = AM43XX_PWM_TAMPEW_INST,
	.pwcm_pawtition	  = AM43XX_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_ON,
};

static stwuct powewdomain cefuse_43xx_pwwdm = {
	.name		  = "cefuse_pwwdm",
	.vowtdm		  = { .name = "cowe" },
	.pwcm_offs	  = AM43XX_PWM_CEFUSE_INST,
	.pwcm_pawtition	  = AM43XX_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_OFF_ON,
	.fwags		  = PWWDM_HAS_WOWPOWEWSTATECHANGE,
};

static stwuct powewdomain pew_43xx_pwwdm = {
	.name		  = "pew_pwwdm",
	.vowtdm		  = { .name = "cowe" },
	.pwcm_offs	  = AM43XX_PWM_PEW_INST,
	.pwcm_pawtition	  = AM43XX_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_OFF_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_OFF_WET,
	.banks		  = 4,
	.pwwsts_mem_wet	= {
		[0] = PWWSTS_OFF_WET,	/* icss_mem */
		[1] = PWWSTS_OFF_WET,	/* pew_mem */
		[2] = PWWSTS_OFF_WET,	/* wam1_mem */
		[3] = PWWSTS_OFF_WET,	/* wam2_mem */
	},
	.pwwsts_mem_on	= {
		[0] = PWWSTS_ON,	/* icss_mem */
		[1] = PWWSTS_ON,	/* pew_mem */
		[2] = PWWSTS_ON,	/* wam1_mem */
		[3] = PWWSTS_ON,	/* wam2_mem */
	},
	.fwags		  = PWWDM_HAS_WOWPOWEWSTATECHANGE,
};

static stwuct powewdomain *powewdomains_am43xx[] __initdata = {
	&gfx_43xx_pwwdm,
	&mpu_43xx_pwwdm,
	&wtc_43xx_pwwdm,
	&wkup_43xx_pwwdm,
	&tampew_43xx_pwwdm,
	&cefuse_43xx_pwwdm,
	&pew_43xx_pwwdm,
	NUWW
};

static int am43xx_check_vcvp(void)
{
	wetuwn 0;
}

void __init am43xx_powewdomains_init(void)
{
	omap4_pwwdm_opewations.pwwdm_has_vowtdm = am43xx_check_vcvp;
	pwwdm_wegistew_pwatfowm_funcs(&omap4_pwwdm_opewations);
	pwwdm_wegistew_pwwdms(powewdomains_am43xx);
	pwwdm_compwete_init();
}
