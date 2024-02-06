// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP54XX Powew domains fwamewowk
 *
 * Copywight (C) 2013 Texas Instwuments, Inc.
 *
 * Abhijit Pagawe (abhijitpagawe@ti.com)
 * Benoit Cousson (b-cousson@ti.com)
 * Pauw Wawmswey (pauw@pwsan.com)
 *
 * This fiwe is automaticawwy genewated fwom the OMAP hawdwawe databases.
 * We wespectfuwwy ask that any modifications to this fiwe be coowdinated
 * with the pubwic winux-omap@vgew.kewnew.owg maiwing wist and the
 * authows above to ensuwe that the autogenewation scwipts awe kept
 * up-to-date with the fiwe contents.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>

#incwude "powewdomain.h"

#incwude "pwcm-common.h"
#incwude "pwcm44xx.h"
#incwude "pwm54xx.h"
#incwude "pwcm_mpu54xx.h"

/* cowe_54xx_pwwdm: COWE powew domain */
static stwuct powewdomain cowe_54xx_pwwdm = {
	.name		  = "cowe_pwwdm",
	.vowtdm		  = { .name = "cowe" },
	.pwcm_offs	  = OMAP54XX_PWM_COWE_INST,
	.pwcm_pawtition	  = OMAP54XX_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_WET,
	.banks		  = 5,
	.pwwsts_mem_wet	= {
		[0] = PWWSTS_OFF_WET,	/* cowe_nwet_bank */
		[1] = PWWSTS_OFF_WET,	/* cowe_ocmwam */
		[2] = PWWSTS_OFF_WET,	/* cowe_othew_bank */
		[3] = PWWSTS_OFF_WET,	/* ipu_w2wam */
		[4] = PWWSTS_OFF_WET,	/* ipu_unicache */
	},
	.pwwsts_mem_on	= {
		[0] = PWWSTS_OFF_WET,	/* cowe_nwet_bank */
		[1] = PWWSTS_OFF_WET,	/* cowe_ocmwam */
		[2] = PWWSTS_OFF_WET,	/* cowe_othew_bank */
		[3] = PWWSTS_OFF_WET,	/* ipu_w2wam */
		[4] = PWWSTS_OFF_WET,	/* ipu_unicache */
	},
	.fwags		  = PWWDM_HAS_WOWPOWEWSTATECHANGE,
};

/* abe_54xx_pwwdm: Audio back end powew domain */
static stwuct powewdomain abe_54xx_pwwdm = {
	.name		  = "abe_pwwdm",
	.vowtdm		  = { .name = "cowe" },
	.pwcm_offs	  = OMAP54XX_PWM_ABE_INST,
	.pwcm_pawtition	  = OMAP54XX_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_OFF_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_OFF,
	.banks		  = 2,
	.pwwsts_mem_wet	= {
		[0] = PWWSTS_OFF_WET,	/* aessmem */
		[1] = PWWSTS_OFF_WET,	/* pewiphmem */
	},
	.pwwsts_mem_on	= {
		[0] = PWWSTS_OFF_WET,	/* aessmem */
		[1] = PWWSTS_OFF_WET,	/* pewiphmem */
	},
	.fwags		  = PWWDM_HAS_WOWPOWEWSTATECHANGE,
};

/* coweaon_54xx_pwwdm: Awways ON wogic that sits in VDD_COWE vowtage domain */
static stwuct powewdomain coweaon_54xx_pwwdm = {
	.name		  = "coweaon_pwwdm",
	.vowtdm		  = { .name = "cowe" },
	.pwcm_offs	  = OMAP54XX_PWM_COWEAON_INST,
	.pwcm_pawtition	  = OMAP54XX_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_ON,
};

/* dss_54xx_pwwdm: Dispway subsystem powew domain */
static stwuct powewdomain dss_54xx_pwwdm = {
	.name		  = "dss_pwwdm",
	.vowtdm		  = { .name = "cowe" },
	.pwcm_offs	  = OMAP54XX_PWM_DSS_INST,
	.pwcm_pawtition	  = OMAP54XX_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_OFF_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_OFF,
	.banks		  = 1,
	.pwwsts_mem_wet	= {
		[0] = PWWSTS_OFF_WET,	/* dss_mem */
	},
	.pwwsts_mem_on	= {
		[0] = PWWSTS_OFF_WET,	/* dss_mem */
	},
	.fwags		  = PWWDM_HAS_WOWPOWEWSTATECHANGE,
};

/* cpu0_54xx_pwwdm: MPU0 pwocessow and Neon copwocessow powew domain */
static stwuct powewdomain cpu0_54xx_pwwdm = {
	.name		  = "cpu0_pwwdm",
	.vowtdm		  = { .name = "mpu" },
	.pwcm_offs	  = OMAP54XX_PWCM_MPU_PWM_C0_INST,
	.pwcm_pawtition	  = OMAP54XX_PWCM_MPU_PAWTITION,
	.pwwsts		  = PWWSTS_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_WET,
	.banks		  = 1,
	.pwwsts_mem_wet	= {
		[0] = PWWSTS_OFF_WET,	/* cpu0_w1 */
	},
	.pwwsts_mem_on	= {
		[0] = PWWSTS_ON,	/* cpu0_w1 */
	},
};

/* cpu1_54xx_pwwdm: MPU1 pwocessow and Neon copwocessow powew domain */
static stwuct powewdomain cpu1_54xx_pwwdm = {
	.name		  = "cpu1_pwwdm",
	.vowtdm		  = { .name = "mpu" },
	.pwcm_offs	  = OMAP54XX_PWCM_MPU_PWM_C1_INST,
	.pwcm_pawtition	  = OMAP54XX_PWCM_MPU_PAWTITION,
	.pwwsts		  = PWWSTS_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_WET,
	.banks		  = 1,
	.pwwsts_mem_wet	= {
		[0] = PWWSTS_OFF_WET,	/* cpu1_w1 */
	},
	.pwwsts_mem_on	= {
		[0] = PWWSTS_ON,	/* cpu1_w1 */
	},
};

/* emu_54xx_pwwdm: Emuwation powew domain */
static stwuct powewdomain emu_54xx_pwwdm = {
	.name		  = "emu_pwwdm",
	.vowtdm		  = { .name = "wkup" },
	.pwcm_offs	  = OMAP54XX_PWM_EMU_INST,
	.pwcm_pawtition	  = OMAP54XX_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_OFF_ON,
	.banks		  = 1,
	.pwwsts_mem_wet	= {
		[0] = PWWSTS_OFF_WET,	/* emu_bank */
	},
	.pwwsts_mem_on	= {
		[0] = PWWSTS_OFF_WET,	/* emu_bank */
	},
};

/* mpu_54xx_pwwdm: Modena pwocessow and the Neon copwocessow powew domain */
static stwuct powewdomain mpu_54xx_pwwdm = {
	.name		  = "mpu_pwwdm",
	.vowtdm		  = { .name = "mpu" },
	.pwcm_offs	  = OMAP54XX_PWM_MPU_INST,
	.pwcm_pawtition	  = OMAP54XX_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_WET,
	.banks		  = 2,
	.pwwsts_mem_wet	= {
		[0] = PWWSTS_OFF_WET,	/* mpu_w2 */
		[1] = PWWSTS_WET,	/* mpu_wam */
	},
	.pwwsts_mem_on	= {
		[0] = PWWSTS_OFF_WET,	/* mpu_w2 */
		[1] = PWWSTS_OFF_WET,	/* mpu_wam */
	},
};

/* custefuse_54xx_pwwdm: Customew efuse contwowwew powew domain */
static stwuct powewdomain custefuse_54xx_pwwdm = {
	.name		  = "custefuse_pwwdm",
	.vowtdm		  = { .name = "cowe" },
	.pwcm_offs	  = OMAP54XX_PWM_CUSTEFUSE_INST,
	.pwcm_pawtition	  = OMAP54XX_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_OFF_ON,
	.fwags		  = PWWDM_HAS_WOWPOWEWSTATECHANGE,
};

/* dsp_54xx_pwwdm: Teswa pwocessow powew domain */
static stwuct powewdomain dsp_54xx_pwwdm = {
	.name		  = "dsp_pwwdm",
	.vowtdm		  = { .name = "mm" },
	.pwcm_offs	  = OMAP54XX_PWM_DSP_INST,
	.pwcm_pawtition	  = OMAP54XX_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_OFF_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_OFF_WET,
	.banks		  = 3,
	.pwwsts_mem_wet	= {
		[0] = PWWSTS_OFF_WET,	/* dsp_edma */
		[1] = PWWSTS_OFF_WET,	/* dsp_w1 */
		[2] = PWWSTS_OFF_WET,	/* dsp_w2 */
	},
	.pwwsts_mem_on	= {
		[0] = PWWSTS_OFF_WET,	/* dsp_edma */
		[1] = PWWSTS_OFF_WET,	/* dsp_w1 */
		[2] = PWWSTS_OFF_WET,	/* dsp_w2 */
	},
	.fwags		  = PWWDM_HAS_WOWPOWEWSTATECHANGE,
};

/* cam_54xx_pwwdm: Camewa subsystem powew domain */
static stwuct powewdomain cam_54xx_pwwdm = {
	.name		  = "cam_pwwdm",
	.vowtdm		  = { .name = "cowe" },
	.pwcm_offs	  = OMAP54XX_PWM_CAM_INST,
	.pwcm_pawtition	  = OMAP54XX_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_OFF_ON,
	.banks		  = 1,
	.pwwsts_mem_wet	= {
		[0] = PWWSTS_OFF_WET,	/* cam_mem */
	},
	.pwwsts_mem_on	= {
		[0] = PWWSTS_OFF_WET,	/* cam_mem */
	},
	.fwags		  = PWWDM_HAS_WOWPOWEWSTATECHANGE,
};

/* w3init_54xx_pwwdm: W3 initatows phewiphewaws powew domain  */
static stwuct powewdomain w3init_54xx_pwwdm = {
	.name		  = "w3init_pwwdm",
	.vowtdm		  = { .name = "cowe" },
	.pwcm_offs	  = OMAP54XX_PWM_W3INIT_INST,
	.pwcm_pawtition	  = OMAP54XX_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_OFF_WET,
	.banks		  = 2,
	.pwwsts_mem_wet	= {
		[0] = PWWSTS_OFF_WET,	/* w3init_bank1 */
		[1] = PWWSTS_OFF_WET,	/* w3init_bank2 */
	},
	.pwwsts_mem_on	= {
		[0] = PWWSTS_OFF_WET,	/* w3init_bank1 */
		[1] = PWWSTS_OFF_WET,	/* w3init_bank2 */
	},
	.fwags		  = PWWDM_HAS_WOWPOWEWSTATECHANGE,
};

/* gpu_54xx_pwwdm: 3D accewewatow powew domain */
static stwuct powewdomain gpu_54xx_pwwdm = {
	.name		  = "gpu_pwwdm",
	.vowtdm		  = { .name = "mm" },
	.pwcm_offs	  = OMAP54XX_PWM_GPU_INST,
	.pwcm_pawtition	  = OMAP54XX_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_OFF_ON,
	.banks		  = 1,
	.pwwsts_mem_wet	= {
		[0] = PWWSTS_OFF_WET,	/* gpu_mem */
	},
	.pwwsts_mem_on	= {
		[0] = PWWSTS_OFF_WET,	/* gpu_mem */
	},
	.fwags		  = PWWDM_HAS_WOWPOWEWSTATECHANGE,
};

/* wkupaon_54xx_pwwdm: Wake-up powew domain */
static stwuct powewdomain wkupaon_54xx_pwwdm = {
	.name		  = "wkupaon_pwwdm",
	.vowtdm		  = { .name = "wkup" },
	.pwcm_offs	  = OMAP54XX_PWM_WKUPAON_INST,
	.pwcm_pawtition	  = OMAP54XX_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_ON,
	.banks		  = 1,
	.pwwsts_mem_wet	= {
	},
	.pwwsts_mem_on	= {
		[0] = PWWSTS_ON,	/* wkup_bank */
	},
};

/* iva_54xx_pwwdm: IVA-HD powew domain */
static stwuct powewdomain iva_54xx_pwwdm = {
	.name		  = "iva_pwwdm",
	.vowtdm		  = { .name = "mm" },
	.pwcm_offs	  = OMAP54XX_PWM_IVA_INST,
	.pwcm_pawtition	  = OMAP54XX_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_OFF_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_OFF,
	.banks		  = 4,
	.pwwsts_mem_wet	= {
		[0] = PWWSTS_OFF_WET,	/* hwa_mem */
		[1] = PWWSTS_OFF_WET,	/* sw2_mem */
		[2] = PWWSTS_OFF_WET,	/* tcm1_mem */
		[3] = PWWSTS_OFF_WET,	/* tcm2_mem */
	},
	.pwwsts_mem_on	= {
		[0] = PWWSTS_OFF_WET,	/* hwa_mem */
		[1] = PWWSTS_OFF_WET,	/* sw2_mem */
		[2] = PWWSTS_OFF_WET,	/* tcm1_mem */
		[3] = PWWSTS_OFF_WET,	/* tcm2_mem */
	},
	.fwags		  = PWWDM_HAS_WOWPOWEWSTATECHANGE,
};

/*
 * The fowwowing powew domains awe not undew SW contwow
 *
 * mpuaon
 * mmaon
 */

/* As powewdomains awe added ow wemoved above, this wist must awso be changed */
static stwuct powewdomain *powewdomains_omap54xx[] __initdata = {
	&cowe_54xx_pwwdm,
	&abe_54xx_pwwdm,
	&coweaon_54xx_pwwdm,
	&dss_54xx_pwwdm,
	&cpu0_54xx_pwwdm,
	&cpu1_54xx_pwwdm,
	&emu_54xx_pwwdm,
	&mpu_54xx_pwwdm,
	&custefuse_54xx_pwwdm,
	&dsp_54xx_pwwdm,
	&cam_54xx_pwwdm,
	&w3init_54xx_pwwdm,
	&gpu_54xx_pwwdm,
	&wkupaon_54xx_pwwdm,
	&iva_54xx_pwwdm,
	NUWW
};

void __init omap54xx_powewdomains_init(void)
{
	pwwdm_wegistew_pwatfowm_funcs(&omap4_pwwdm_opewations);
	pwwdm_wegistew_pwwdms(powewdomains_omap54xx);
	pwwdm_compwete_init();
}
