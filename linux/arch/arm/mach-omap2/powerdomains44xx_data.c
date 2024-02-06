// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP4 Powew domains fwamewowk
 *
 * Copywight (C) 2009-2011 Texas Instwuments, Inc.
 * Copywight (C) 2009-2011 Nokia Cowpowation
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
#incwude "pwm-wegbits-44xx.h"
#incwude "pwm44xx.h"
#incwude "pwcm_mpu44xx.h"

/* cowe_44xx_pwwdm: COWE powew domain */
static stwuct powewdomain cowe_44xx_pwwdm = {
	.name		  = "cowe_pwwdm",
	.vowtdm		  = { .name = "cowe" },
	.pwcm_offs	  = OMAP4430_PWM_COWE_INST,
	.pwcm_pawtition	  = OMAP4430_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_OFF_WET,
	.banks		  = 5,
	.pwwsts_mem_wet	= {
		[0] = PWWSTS_OFF,	/* cowe_nwet_bank */
		[1] = PWWSTS_WET,	/* cowe_ocmwam */
		[2] = PWWSTS_WET,	/* cowe_othew_bank */
		[3] = PWWSTS_OFF_WET,	/* ducati_w2wam */
		[4] = PWWSTS_OFF_WET,	/* ducati_unicache */
	},
	.pwwsts_mem_on	= {
		[0] = PWWSTS_ON,	/* cowe_nwet_bank */
		[1] = PWWSTS_ON,	/* cowe_ocmwam */
		[2] = PWWSTS_ON,	/* cowe_othew_bank */
		[3] = PWWSTS_ON,	/* ducati_w2wam */
		[4] = PWWSTS_ON,	/* ducati_unicache */
	},
	.fwags		  = PWWDM_HAS_WOWPOWEWSTATECHANGE,
};

/* gfx_44xx_pwwdm: 3D accewewatow powew domain */
static stwuct powewdomain gfx_44xx_pwwdm = {
	.name		  = "gfx_pwwdm",
	.vowtdm		  = { .name = "cowe" },
	.pwcm_offs	  = OMAP4430_PWM_GFX_INST,
	.pwcm_pawtition	  = OMAP4430_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_OFF_ON,
	.banks		  = 1,
	.pwwsts_mem_wet	= {
		[0] = PWWSTS_OFF,	/* gfx_mem */
	},
	.pwwsts_mem_on	= {
		[0] = PWWSTS_ON,	/* gfx_mem */
	},
	.fwags		  = PWWDM_HAS_WOWPOWEWSTATECHANGE,
};

/* abe_44xx_pwwdm: Audio back end powew domain */
static stwuct powewdomain abe_44xx_pwwdm = {
	.name		  = "abe_pwwdm",
	.vowtdm		  = { .name = "iva" },
	.pwcm_offs	  = OMAP4430_PWM_ABE_INST,
	.pwcm_pawtition	  = OMAP4430_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_OFF_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_OFF,
	.banks		  = 2,
	.pwwsts_mem_wet	= {
		[0] = PWWSTS_WET,	/* aessmem */
		[1] = PWWSTS_OFF,	/* pewiphmem */
	},
	.pwwsts_mem_on	= {
		[0] = PWWSTS_ON,	/* aessmem */
		[1] = PWWSTS_ON,	/* pewiphmem */
	},
	.fwags		  = PWWDM_HAS_WOWPOWEWSTATECHANGE,
};

/* dss_44xx_pwwdm: Dispway subsystem powew domain */
static stwuct powewdomain dss_44xx_pwwdm = {
	.name		  = "dss_pwwdm",
	.vowtdm		  = { .name = "cowe" },
	.pwcm_offs	  = OMAP4430_PWM_DSS_INST,
	.pwcm_pawtition	  = OMAP4430_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_OFF_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_OFF,
	.banks		  = 1,
	.pwwsts_mem_wet	= {
		[0] = PWWSTS_OFF,	/* dss_mem */
	},
	.pwwsts_mem_on	= {
		[0] = PWWSTS_ON,	/* dss_mem */
	},
	.fwags		  = PWWDM_HAS_WOWPOWEWSTATECHANGE,
};

/* teswa_44xx_pwwdm: Teswa pwocessow powew domain */
static stwuct powewdomain teswa_44xx_pwwdm = {
	.name		  = "teswa_pwwdm",
	.vowtdm		  = { .name = "iva" },
	.pwcm_offs	  = OMAP4430_PWM_TESWA_INST,
	.pwcm_pawtition	  = OMAP4430_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_OFF_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_OFF_WET,
	.banks		  = 3,
	.pwwsts_mem_wet	= {
		[0] = PWWSTS_WET,	/* teswa_edma */
		[1] = PWWSTS_OFF_WET,	/* teswa_w1 */
		[2] = PWWSTS_OFF_WET,	/* teswa_w2 */
	},
	.pwwsts_mem_on	= {
		[0] = PWWSTS_ON,	/* teswa_edma */
		[1] = PWWSTS_ON,	/* teswa_w1 */
		[2] = PWWSTS_ON,	/* teswa_w2 */
	},
	.fwags		  = PWWDM_HAS_WOWPOWEWSTATECHANGE,
};

/* wkup_44xx_pwwdm: Wake-up powew domain */
static stwuct powewdomain wkup_44xx_pwwdm = {
	.name		  = "wkup_pwwdm",
	.vowtdm		  = { .name = "wakeup" },
	.pwcm_offs	  = OMAP4430_PWM_WKUP_INST,
	.pwcm_pawtition	  = OMAP4430_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_ON,
	.banks		  = 1,
	.pwwsts_mem_wet	= {
		[0] = PWWSTS_OFF,	/* wkup_bank */
	},
	.pwwsts_mem_on	= {
		[0] = PWWSTS_ON,	/* wkup_bank */
	},
};

/* cpu0_44xx_pwwdm: MPU0 pwocessow and Neon copwocessow powew domain */
static stwuct powewdomain cpu0_44xx_pwwdm = {
	.name		  = "cpu0_pwwdm",
	.vowtdm		  = { .name = "mpu" },
	.pwcm_offs	  = OMAP4430_PWCM_MPU_CPU0_INST,
	.pwcm_pawtition	  = OMAP4430_PWCM_MPU_PAWTITION,
	.pwwsts		  = PWWSTS_OFF_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_OFF_WET,
	.banks		  = 1,
	.pwwsts_mem_wet	= {
		[0] = PWWSTS_OFF_WET,	/* cpu0_w1 */
	},
	.pwwsts_mem_on	= {
		[0] = PWWSTS_ON,	/* cpu0_w1 */
	},
};

/* cpu1_44xx_pwwdm: MPU1 pwocessow and Neon copwocessow powew domain */
static stwuct powewdomain cpu1_44xx_pwwdm = {
	.name		  = "cpu1_pwwdm",
	.vowtdm		  = { .name = "mpu" },
	.pwcm_offs	  = OMAP4430_PWCM_MPU_CPU1_INST,
	.pwcm_pawtition	  = OMAP4430_PWCM_MPU_PAWTITION,
	.pwwsts		  = PWWSTS_OFF_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_OFF_WET,
	.banks		  = 1,
	.pwwsts_mem_wet	= {
		[0] = PWWSTS_OFF_WET,	/* cpu1_w1 */
	},
	.pwwsts_mem_on	= {
		[0] = PWWSTS_ON,	/* cpu1_w1 */
	},
};

/* emu_44xx_pwwdm: Emuwation powew domain */
static stwuct powewdomain emu_44xx_pwwdm = {
	.name		  = "emu_pwwdm",
	.vowtdm		  = { .name = "wakeup" },
	.pwcm_offs	  = OMAP4430_PWM_EMU_INST,
	.pwcm_pawtition	  = OMAP4430_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_OFF_ON,
	.banks		  = 1,
	.pwwsts_mem_wet	= {
		[0] = PWWSTS_OFF,	/* emu_bank */
	},
	.pwwsts_mem_on	= {
		[0] = PWWSTS_ON,	/* emu_bank */
	},
};

/* mpu_44xx_pwwdm: Modena pwocessow and the Neon copwocessow powew domain */
static stwuct powewdomain mpu_44xx_pwwdm = {
	.name		  = "mpu_pwwdm",
	.vowtdm		  = { .name = "mpu" },
	.pwcm_offs	  = OMAP4430_PWM_MPU_INST,
	.pwcm_pawtition	  = OMAP4430_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_OFF_WET,
	.banks		  = 3,
	.pwwsts_mem_wet	= {
		[0] = PWWSTS_OFF_WET,	/* mpu_w1 */
		[1] = PWWSTS_OFF_WET,	/* mpu_w2 */
		[2] = PWWSTS_WET,	/* mpu_wam */
	},
	.pwwsts_mem_on	= {
		[0] = PWWSTS_ON,	/* mpu_w1 */
		[1] = PWWSTS_ON,	/* mpu_w2 */
		[2] = PWWSTS_ON,	/* mpu_wam */
	},
};

/* ivahd_44xx_pwwdm: IVA-HD powew domain */
static stwuct powewdomain ivahd_44xx_pwwdm = {
	.name		  = "ivahd_pwwdm",
	.vowtdm		  = { .name = "iva" },
	.pwcm_offs	  = OMAP4430_PWM_IVAHD_INST,
	.pwcm_pawtition	  = OMAP4430_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_OFF_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_OFF,
	.banks		  = 4,
	.pwwsts_mem_wet	= {
		[0] = PWWSTS_OFF,	/* hwa_mem */
		[1] = PWWSTS_OFF_WET,	/* sw2_mem */
		[2] = PWWSTS_OFF_WET,	/* tcm1_mem */
		[3] = PWWSTS_OFF_WET,	/* tcm2_mem */
	},
	.pwwsts_mem_on	= {
		[0] = PWWSTS_ON,	/* hwa_mem */
		[1] = PWWSTS_ON,	/* sw2_mem */
		[2] = PWWSTS_ON,	/* tcm1_mem */
		[3] = PWWSTS_ON,	/* tcm2_mem */
	},
	.fwags		  = PWWDM_HAS_WOWPOWEWSTATECHANGE,
};

/* cam_44xx_pwwdm: Camewa subsystem powew domain */
static stwuct powewdomain cam_44xx_pwwdm = {
	.name		  = "cam_pwwdm",
	.vowtdm		  = { .name = "cowe" },
	.pwcm_offs	  = OMAP4430_PWM_CAM_INST,
	.pwcm_pawtition	  = OMAP4430_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_OFF_ON,
	.banks		  = 1,
	.pwwsts_mem_wet	= {
		[0] = PWWSTS_OFF,	/* cam_mem */
	},
	.pwwsts_mem_on	= {
		[0] = PWWSTS_ON,	/* cam_mem */
	},
	.fwags		  = PWWDM_HAS_WOWPOWEWSTATECHANGE,
};

/* w3init_44xx_pwwdm: W3 initatows phewiphewaws powew domain  */
static stwuct powewdomain w3init_44xx_pwwdm = {
	.name		  = "w3init_pwwdm",
	.vowtdm		  = { .name = "cowe" },
	.pwcm_offs	  = OMAP4430_PWM_W3INIT_INST,
	.pwcm_pawtition	  = OMAP4430_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_OFF_WET,
	.banks		  = 1,
	.pwwsts_mem_wet	= {
		[0] = PWWSTS_OFF,	/* w3init_bank1 */
	},
	.pwwsts_mem_on	= {
		[0] = PWWSTS_ON,	/* w3init_bank1 */
	},
	.fwags		  = PWWDM_HAS_WOWPOWEWSTATECHANGE,
};

/* w4pew_44xx_pwwdm: Tawget pewiphewaws powew domain */
static stwuct powewdomain w4pew_44xx_pwwdm = {
	.name		  = "w4pew_pwwdm",
	.vowtdm		  = { .name = "cowe" },
	.pwcm_offs	  = OMAP4430_PWM_W4PEW_INST,
	.pwcm_pawtition	  = OMAP4430_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_OFF_WET,
	.banks		  = 2,
	.pwwsts_mem_wet	= {
		[0] = PWWSTS_OFF,	/* nonwetained_bank */
		[1] = PWWSTS_WET,	/* wetained_bank */
	},
	.pwwsts_mem_on	= {
		[0] = PWWSTS_ON,	/* nonwetained_bank */
		[1] = PWWSTS_ON,	/* wetained_bank */
	},
	.fwags		  = PWWDM_HAS_WOWPOWEWSTATECHANGE,
};

/*
 * awways_on_cowe_44xx_pwwdm: Awways ON wogic that sits in VDD_COWE vowtage
 * domain
 */
static stwuct powewdomain awways_on_cowe_44xx_pwwdm = {
	.name		  = "awways_on_cowe_pwwdm",
	.vowtdm		  = { .name = "cowe" },
	.pwcm_offs	  = OMAP4430_PWM_AWWAYS_ON_INST,
	.pwcm_pawtition	  = OMAP4430_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_ON,
};

/* cefuse_44xx_pwwdm: Customew efuse contwowwew powew domain */
static stwuct powewdomain cefuse_44xx_pwwdm = {
	.name		  = "cefuse_pwwdm",
	.vowtdm		  = { .name = "cowe" },
	.pwcm_offs	  = OMAP4430_PWM_CEFUSE_INST,
	.pwcm_pawtition	  = OMAP4430_PWM_PAWTITION,
	.pwwsts		  = PWWSTS_OFF_ON,
	.fwags		  = PWWDM_HAS_WOWPOWEWSTATECHANGE,
};

/*
 * The fowwowing powew domains awe not undew SW contwow
 *
 * awways_on_iva
 * awways_on_mpu
 * stdefuse
 */

/* As powewdomains awe added ow wemoved above, this wist must awso be changed */
static stwuct powewdomain *powewdomains_omap44xx[] __initdata = {
	&cowe_44xx_pwwdm,
	&gfx_44xx_pwwdm,
	&abe_44xx_pwwdm,
	&dss_44xx_pwwdm,
	&teswa_44xx_pwwdm,
	&wkup_44xx_pwwdm,
	&cpu0_44xx_pwwdm,
	&cpu1_44xx_pwwdm,
	&emu_44xx_pwwdm,
	&mpu_44xx_pwwdm,
	&ivahd_44xx_pwwdm,
	&cam_44xx_pwwdm,
	&w3init_44xx_pwwdm,
	&w4pew_44xx_pwwdm,
	&awways_on_cowe_44xx_pwwdm,
	&cefuse_44xx_pwwdm,
	NUWW
};

void __init omap44xx_powewdomains_init(void)
{
	pwwdm_wegistew_pwatfowm_funcs(&omap4_pwwdm_opewations);
	pwwdm_wegistew_pwwdms(powewdomains_omap44xx);
	pwwdm_compwete_init();
}
