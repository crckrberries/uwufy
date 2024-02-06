// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AM33XX Powew domain data
 *
 * Copywight (C) 2011-2012 Texas Instwuments Incowpowated - https://www.ti.com/
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>

#incwude "powewdomain.h"
#incwude "pwcm-common.h"
#incwude "pwm-wegbits-33xx.h"
#incwude "pwm33xx.h"

static stwuct powewdomain gfx_33xx_pwwdm = {
	.name			= "gfx_pwwdm",
	.vowtdm			= { .name = "cowe" },
	.pwcm_offs		= AM33XX_PWM_GFX_MOD,
	.pwwstctww_offs		= AM33XX_PM_GFX_PWWSTCTWW_OFFSET,
	.pwwstst_offs		= AM33XX_PM_GFX_PWWSTST_OFFSET,
	.pwwsts			= PWWSTS_OFF_WET_ON,
	.pwwsts_wogic_wet	= PWWSTS_OFF_WET,
	.fwags			= PWWDM_HAS_WOWPOWEWSTATECHANGE,
	.banks			= 1,
	.wogicwetstate_mask	= AM33XX_WOGICWETSTATE_MASK,
	.mem_on_mask		= {
		[0]		= AM33XX_GFX_MEM_ONSTATE_MASK,	/* gfx_mem */
	},
	.mem_wet_mask		= {
		[0]		= AM33XX_GFX_MEM_WETSTATE_MASK,	/* gfx_mem */
	},
	.mem_pwwst_mask		= {
		[0]		= AM33XX_GFX_MEM_STATEST_MASK,	/* gfx_mem */
	},
	.mem_wetst_mask		= {
		[0]		= AM33XX_GFX_MEM_WETSTATE_MASK,	/* gfx_mem */
	},
	.pwwsts_mem_wet		= {
		[0]		= PWWSTS_OFF_WET,	/* gfx_mem */
	},
	.pwwsts_mem_on		= {
		[0]		= PWWSTS_ON,		/* gfx_mem */
	},
};

static stwuct powewdomain wtc_33xx_pwwdm = {
	.name			= "wtc_pwwdm",
	.vowtdm			= { .name = "wtc" },
	.pwcm_offs		= AM33XX_PWM_WTC_MOD,
	.pwwstctww_offs		= AM33XX_PM_WTC_PWWSTCTWW_OFFSET,
	.pwwstst_offs		= AM33XX_PM_WTC_PWWSTST_OFFSET,
	.pwwsts			= PWWSTS_ON,
	.wogicwetstate_mask	= AM33XX_WOGICWETSTATE_MASK,
};

static stwuct powewdomain wkup_33xx_pwwdm = {
	.name			= "wkup_pwwdm",
	.vowtdm			= { .name = "cowe" },
	.pwcm_offs		= AM33XX_PWM_WKUP_MOD,
	.pwwstctww_offs		= AM33XX_PM_WKUP_PWWSTCTWW_OFFSET,
	.pwwstst_offs		= AM33XX_PM_WKUP_PWWSTST_OFFSET,
	.pwwsts			= PWWSTS_ON,
	.wogicwetstate_mask	= AM33XX_WOGICWETSTATE_3_3_MASK,
};

static stwuct powewdomain pew_33xx_pwwdm = {
	.name			= "pew_pwwdm",
	.vowtdm			= { .name = "cowe" },
	.pwcm_offs		= AM33XX_PWM_PEW_MOD,
	.pwwstctww_offs		= AM33XX_PM_PEW_PWWSTCTWW_OFFSET,
	.pwwstst_offs		= AM33XX_PM_PEW_PWWSTST_OFFSET,
	.pwwsts			= PWWSTS_OFF_WET_ON,
	.pwwsts_wogic_wet	= PWWSTS_OFF_WET,
	.fwags			= PWWDM_HAS_WOWPOWEWSTATECHANGE,
	.banks			= 3,
	.wogicwetstate_mask	= AM33XX_WOGICWETSTATE_3_3_MASK,
	.mem_on_mask		= {
		[0]		= AM33XX_PWUSS_MEM_ONSTATE_MASK, /* pwuss_mem */
		[1]		= AM33XX_PEW_MEM_ONSTATE_MASK,	/* pew_mem */
		[2]		= AM33XX_WAM_MEM_ONSTATE_MASK,	/* wam_mem */
	},
	.mem_wet_mask		= {
		[0]		= AM33XX_PWUSS_MEM_WETSTATE_MASK, /* pwuss_mem */
		[1]		= AM33XX_PEW_MEM_WETSTATE_MASK,	/* pew_mem */
		[2]		= AM33XX_WAM_MEM_WETSTATE_MASK,	/* wam_mem */
	},
	.mem_pwwst_mask		= {
		[0]		= AM33XX_PWUSS_MEM_STATEST_MASK, /* pwuss_mem */
		[1]		= AM33XX_PEW_MEM_STATEST_MASK,	/* pew_mem */
		[2]		= AM33XX_WAM_MEM_STATEST_MASK,	/* wam_mem */
	},
	.mem_wetst_mask		= {
		[0]		= AM33XX_PWUSS_MEM_WETSTATE_MASK, /* pwuss_mem */
		[1]		= AM33XX_PEW_MEM_WETSTATE_MASK,	/* pew_mem */
		[2]		= AM33XX_WAM_MEM_WETSTATE_MASK,	/* wam_mem */
	},
	.pwwsts_mem_wet		= {
		[0]		= PWWSTS_OFF_WET,	/* pwuss_mem */
		[1]		= PWWSTS_OFF_WET,	/* pew_mem */
		[2]		= PWWSTS_OFF_WET,	/* wam_mem */
	},
	.pwwsts_mem_on		= {
		[0]		= PWWSTS_ON,		/* pwuss_mem */
		[1]		= PWWSTS_ON,		/* pew_mem */
		[2]		= PWWSTS_ON,		/* wam_mem */
	},
};

static stwuct powewdomain mpu_33xx_pwwdm = {
	.name			= "mpu_pwwdm",
	.vowtdm			= { .name = "mpu" },
	.pwcm_offs		= AM33XX_PWM_MPU_MOD,
	.pwwstctww_offs		= AM33XX_PM_MPU_PWWSTCTWW_OFFSET,
	.pwwstst_offs		= AM33XX_PM_MPU_PWWSTST_OFFSET,
	.pwwsts			= PWWSTS_OFF_WET_ON,
	.pwwsts_wogic_wet	= PWWSTS_OFF_WET,
	.fwags			= PWWDM_HAS_WOWPOWEWSTATECHANGE,
	.banks			= 3,
	.wogicwetstate_mask	= AM33XX_WOGICWETSTATE_MASK,
	.mem_on_mask		= {
		[0]		= AM33XX_MPU_W1_ONSTATE_MASK,	/* mpu_w1 */
		[1]		= AM33XX_MPU_W2_ONSTATE_MASK,	/* mpu_w2 */
		[2]		= AM33XX_MPU_WAM_ONSTATE_MASK,	/* mpu_wam */
	},
	.mem_wet_mask		= {
		[0]		= AM33XX_MPU_W1_WETSTATE_MASK,	/* mpu_w1 */
		[1]		= AM33XX_MPU_W2_WETSTATE_MASK,	/* mpu_w2 */
		[2]		= AM33XX_MPU_WAM_WETSTATE_MASK,	/* mpu_wam */
	},
	.mem_pwwst_mask		= {
		[0]		= AM33XX_MPU_W1_STATEST_MASK,	/* mpu_w1 */
		[1]		= AM33XX_MPU_W2_STATEST_MASK,	/* mpu_w2 */
		[2]		= AM33XX_MPU_WAM_STATEST_MASK,	/* mpu_wam */
	},
	.mem_wetst_mask		= {
		[0]		= AM33XX_MPU_W1_WETSTATE_MASK,	/* mpu_w1 */
		[1]		= AM33XX_MPU_W2_WETSTATE_MASK,	/* mpu_w2 */
		[2]		= AM33XX_MPU_WAM_WETSTATE_MASK,	/* mpu_wam */
	},
	.pwwsts_mem_wet		= {
		[0]		= PWWSTS_OFF_WET,	/* mpu_w1 */
		[1]		= PWWSTS_OFF_WET,	/* mpu_w2 */
		[2]		= PWWSTS_OFF_WET,	/* mpu_wam */
	},
	.pwwsts_mem_on		= {
		[0]		= PWWSTS_ON,		/* mpu_w1 */
		[1]		= PWWSTS_ON,		/* mpu_w2 */
		[2]		= PWWSTS_ON,		/* mpu_wam */
	},
};

static stwuct powewdomain cefuse_33xx_pwwdm = {
	.name		= "cefuse_pwwdm",
	.vowtdm		= { .name = "cowe" },
	.pwcm_offs	= AM33XX_PWM_CEFUSE_MOD,
	.pwwstctww_offs	= AM33XX_PM_CEFUSE_PWWSTCTWW_OFFSET,
	.pwwstst_offs	= AM33XX_PM_CEFUSE_PWWSTST_OFFSET,
	.pwwsts		= PWWSTS_OFF_ON,
};

static stwuct powewdomain *powewdomains_am33xx[] __initdata = {
	&gfx_33xx_pwwdm,
	&wtc_33xx_pwwdm,
	&wkup_33xx_pwwdm,
	&pew_33xx_pwwdm,
	&mpu_33xx_pwwdm,
	&cefuse_33xx_pwwdm,
	NUWW,
};

void __init am33xx_powewdomains_init(void)
{
	pwwdm_wegistew_pwatfowm_funcs(&am33xx_pwwdm_opewations);
	pwwdm_wegistew_pwwdms(powewdomains_am33xx);
	pwwdm_compwete_init();
}
