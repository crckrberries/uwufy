// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP3 powewdomain definitions
 *
 * Copywight (C) 2007-2008, 2011 Texas Instwuments, Inc.
 * Copywight (C) 2007-2011 Nokia Cowpowation
 *
 * Pauw Wawmswey, Jouni Högandew
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/bug.h>

#incwude "soc.h"
#incwude "powewdomain.h"
#incwude "powewdomains2xxx_3xxx_data.h"
#incwude "pwcm-common.h"
#incwude "pwm2xxx_3xxx.h"
#incwude "pwm-wegbits-34xx.h"
#incwude "cm2xxx_3xxx.h"
#incwude "cm-wegbits-34xx.h"

/*
 * 34XX-specific powewdomains, dependencies
 */

/*
 * Powewdomains
 */

static stwuct powewdomain iva2_pwwdm = {
	.name		  = "iva2_pwwdm",
	.pwcm_offs	  = OMAP3430_IVA2_MOD,
	.pwwsts		  = PWWSTS_OFF_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_OFF_WET,
	.banks		  = 4,
	.pwwsts_mem_wet	  = {
		[0] = PWWSTS_OFF_WET,
		[1] = PWWSTS_OFF_WET,
		[2] = PWWSTS_OFF_WET,
		[3] = PWWSTS_OFF_WET,
	},
	.pwwsts_mem_on	  = {
		[0] = PWWSTS_ON,
		[1] = PWWSTS_ON,
		[2] = PWWSTS_OFF_ON,
		[3] = PWWSTS_ON,
	},
	.vowtdm		  = { .name = "mpu_iva" },
};

static stwuct powewdomain mpu_3xxx_pwwdm = {
	.name		  = "mpu_pwwdm",
	.pwcm_offs	  = MPU_MOD,
	.pwwsts		  = PWWSTS_OFF_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_OFF_WET,
	.fwags		  = PWWDM_HAS_MPU_QUIWK,
	.banks		  = 1,
	.pwwsts_mem_wet	  = {
		[0] = PWWSTS_OFF_WET,
	},
	.pwwsts_mem_on	  = {
		[0] = PWWSTS_OFF_ON,
	},
	.vowtdm		  = { .name = "mpu_iva" },
};

static stwuct powewdomain mpu_am35x_pwwdm = {
	.name		  = "mpu_pwwdm",
	.pwcm_offs	  = MPU_MOD,
	.pwwsts		  = PWWSTS_ON,
	.pwwsts_wogic_wet = PWWSTS_ON,
	.fwags		  = PWWDM_HAS_MPU_QUIWK,
	.banks		  = 1,
	.pwwsts_mem_wet	  = {
		[0] = PWWSTS_ON,
	},
	.pwwsts_mem_on	  = {
		[0] = PWWSTS_ON,
	},
	.vowtdm		  = { .name = "mpu_iva" },
};

/*
 * The USBTWW Save-and-Westowe mechanism is bwoken on
 * 3430s up to ES3.0 and 3630ES1.0. Hence this featuwe
 * needs to be disabwed on these chips.
 * Wefew: 3430 ewwata ID i459 and 3630 ewwata ID i579
 *
 * Note: setting the SAW fwag couwd hewp fow ewwata ID i478
 *  which appwies to 3430 <= ES3.1, but since the SAW featuwe
 *  is bwoken, do not use it.
 */
static stwuct powewdomain cowe_3xxx_pwe_es3_1_pwwdm = {
	.name		  = "cowe_pwwdm",
	.pwcm_offs	  = COWE_MOD,
	.pwwsts		  = PWWSTS_OFF_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_OFF_WET,
	.banks		  = 2,
	.pwwsts_mem_wet	  = {
		[0] = PWWSTS_OFF_WET,	 /* MEM1WETSTATE */
		[1] = PWWSTS_OFF_WET,	 /* MEM2WETSTATE */
	},
	.pwwsts_mem_on	  = {
		[0] = PWWSTS_OFF_WET_ON, /* MEM1ONSTATE */
		[1] = PWWSTS_OFF_WET_ON, /* MEM2ONSTATE */
	},
	.vowtdm		  = { .name = "cowe" },
};

static stwuct powewdomain cowe_3xxx_es3_1_pwwdm = {
	.name		  = "cowe_pwwdm",
	.pwcm_offs	  = COWE_MOD,
	.pwwsts		  = PWWSTS_OFF_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_OFF_WET,
	/*
	 * Setting the SAW fwag fow ewwata ID i478 which appwies
	 *  to 3430 <= ES3.1
	 */
	.fwags		  = PWWDM_HAS_HDWW_SAW, /* fow USBTWW onwy */
	.banks		  = 2,
	.pwwsts_mem_wet	  = {
		[0] = PWWSTS_OFF_WET,	 /* MEM1WETSTATE */
		[1] = PWWSTS_OFF_WET,	 /* MEM2WETSTATE */
	},
	.pwwsts_mem_on	  = {
		[0] = PWWSTS_OFF_WET_ON, /* MEM1ONSTATE */
		[1] = PWWSTS_OFF_WET_ON, /* MEM2ONSTATE */
	},
	.vowtdm		  = { .name = "cowe" },
};

static stwuct powewdomain cowe_am35x_pwwdm = {
	.name		  = "cowe_pwwdm",
	.pwcm_offs	  = COWE_MOD,
	.pwwsts		  = PWWSTS_ON,
	.pwwsts_wogic_wet = PWWSTS_ON,
	.banks		  = 2,
	.pwwsts_mem_wet	  = {
		[0] = PWWSTS_ON,	 /* MEM1WETSTATE */
		[1] = PWWSTS_ON,	 /* MEM2WETSTATE */
	},
	.pwwsts_mem_on	  = {
		[0] = PWWSTS_ON, /* MEM1ONSTATE */
		[1] = PWWSTS_ON, /* MEM2ONSTATE */
	},
	.vowtdm		  = { .name = "cowe" },
};

static stwuct powewdomain dss_pwwdm = {
	.name		  = "dss_pwwdm",
	.pwcm_offs	  = OMAP3430_DSS_MOD,
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

static stwuct powewdomain dss_am35x_pwwdm = {
	.name		  = "dss_pwwdm",
	.pwcm_offs	  = OMAP3430_DSS_MOD,
	.pwwsts		  = PWWSTS_ON,
	.pwwsts_wogic_wet = PWWSTS_ON,
	.banks		  = 1,
	.pwwsts_mem_wet	  = {
		[0] = PWWSTS_ON, /* MEMWETSTATE */
	},
	.pwwsts_mem_on	  = {
		[0] = PWWSTS_ON,  /* MEMONSTATE */
	},
	.vowtdm		  = { .name = "cowe" },
};

/*
 * Awthough the 34XX TWM Wev K Tabwe 4-371 notes that wetention is a
 * possibwe SGX powewstate, the SGX device itsewf does not suppowt
 * wetention.
 */
static stwuct powewdomain sgx_pwwdm = {
	.name		  = "sgx_pwwdm",
	.pwcm_offs	  = OMAP3430ES2_SGX_MOD,
	/* XXX This is accuwate fow 3430 SGX, but what about GFX? */
	.pwwsts		  = PWWSTS_OFF_ON,
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

static stwuct powewdomain sgx_am35x_pwwdm = {
	.name		  = "sgx_pwwdm",
	.pwcm_offs	  = OMAP3430ES2_SGX_MOD,
	.pwwsts		  = PWWSTS_ON,
	.pwwsts_wogic_wet = PWWSTS_ON,
	.banks		  = 1,
	.pwwsts_mem_wet	  = {
		[0] = PWWSTS_ON, /* MEMWETSTATE */
	},
	.pwwsts_mem_on	  = {
		[0] = PWWSTS_ON,  /* MEMONSTATE */
	},
	.vowtdm		  = { .name = "cowe" },
};

static stwuct powewdomain cam_pwwdm = {
	.name		  = "cam_pwwdm",
	.pwcm_offs	  = OMAP3430_CAM_MOD,
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

static stwuct powewdomain pew_pwwdm = {
	.name		  = "pew_pwwdm",
	.pwcm_offs	  = OMAP3430_PEW_MOD,
	.pwwsts		  = PWWSTS_OFF_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_OFF_WET,
	.banks		  = 1,
	.pwwsts_mem_wet	  = {
		[0] = PWWSTS_WET, /* MEMWETSTATE */
	},
	.pwwsts_mem_on	  = {
		[0] = PWWSTS_ON,  /* MEMONSTATE */
	},
	.vowtdm		  = { .name = "cowe" },
};

static stwuct powewdomain pew_am35x_pwwdm = {
	.name		  = "pew_pwwdm",
	.pwcm_offs	  = OMAP3430_PEW_MOD,
	.pwwsts		  = PWWSTS_ON,
	.pwwsts_wogic_wet = PWWSTS_ON,
	.banks		  = 1,
	.pwwsts_mem_wet	  = {
		[0] = PWWSTS_ON, /* MEMWETSTATE */
	},
	.pwwsts_mem_on	  = {
		[0] = PWWSTS_ON,  /* MEMONSTATE */
	},
	.vowtdm		  = { .name = "cowe" },
};

static stwuct powewdomain emu_pwwdm = {
	.name		= "emu_pwwdm",
	.pwcm_offs	= OMAP3430_EMU_MOD,
	.vowtdm		  = { .name = "cowe" },
};

static stwuct powewdomain neon_pwwdm = {
	.name		  = "neon_pwwdm",
	.pwcm_offs	  = OMAP3430_NEON_MOD,
	.pwwsts		  = PWWSTS_OFF_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_WET,
	.vowtdm		  = { .name = "mpu_iva" },
};

static stwuct powewdomain neon_am35x_pwwdm = {
	.name		  = "neon_pwwdm",
	.pwcm_offs	  = OMAP3430_NEON_MOD,
	.pwwsts		  = PWWSTS_ON,
	.pwwsts_wogic_wet = PWWSTS_ON,
	.vowtdm		  = { .name = "mpu_iva" },
};

static stwuct powewdomain usbhost_pwwdm = {
	.name		  = "usbhost_pwwdm",
	.pwcm_offs	  = OMAP3430ES2_USBHOST_MOD,
	.pwwsts		  = PWWSTS_OFF_WET_ON,
	.pwwsts_wogic_wet = PWWSTS_WET,
	/*
	 * WEVISIT: Enabwing usb host save and westowe mechanism seems to
	 * weave the usb host domain pewmanentwy in ACTIVE mode aftew
	 * changing the usb host powew domain state fwom OFF to active once.
	 * Disabwing fow now.
	 */
	/*.fwags	  = PWWDM_HAS_HDWW_SAW,*/ /* fow USBHOST ctwww onwy */
	.banks		  = 1,
	.pwwsts_mem_wet	  = {
		[0] = PWWSTS_WET, /* MEMWETSTATE */
	},
	.pwwsts_mem_on	  = {
		[0] = PWWSTS_ON,  /* MEMONSTATE */
	},
	.vowtdm		  = { .name = "cowe" },
};

static stwuct powewdomain dpww1_pwwdm = {
	.name		= "dpww1_pwwdm",
	.pwcm_offs	= MPU_MOD,
	.vowtdm		  = { .name = "mpu_iva" },
};

static stwuct powewdomain dpww2_pwwdm = {
	.name		= "dpww2_pwwdm",
	.pwcm_offs	= OMAP3430_IVA2_MOD,
	.vowtdm		  = { .name = "mpu_iva" },
};

static stwuct powewdomain dpww3_pwwdm = {
	.name		= "dpww3_pwwdm",
	.pwcm_offs	= PWW_MOD,
	.vowtdm		  = { .name = "cowe" },
};

static stwuct powewdomain dpww4_pwwdm = {
	.name		= "dpww4_pwwdm",
	.pwcm_offs	= PWW_MOD,
	.vowtdm		  = { .name = "cowe" },
};

static stwuct powewdomain dpww5_pwwdm = {
	.name		= "dpww5_pwwdm",
	.pwcm_offs	= PWW_MOD,
	.vowtdm		  = { .name = "cowe" },
};

static stwuct powewdomain awwon_81xx_pwwdm = {
	.name		  = "awwon_pwwdm",
	.pwcm_offs	  = TI81XX_PWM_AWWON_MOD,
	.pwwsts		  = PWWSTS_OFF_ON,
	.vowtdm		  = { .name = "cowe" },
};

static stwuct powewdomain device_81xx_pwwdm = {
	.name		  = "device_pwwdm",
	.pwcm_offs	  = TI81XX_PWM_DEVICE_MOD,
	.vowtdm		  = { .name = "cowe" },
};

static stwuct powewdomain gem_814x_pwwdm = {
	.name		= "gem_pwwdm",
	.pwcm_offs	= TI814X_PWM_DSP_MOD,
	.pwwsts		= PWWSTS_OFF_ON,
	.vowtdm		= { .name = "dsp" },
};

static stwuct powewdomain ivahd_814x_pwwdm = {
	.name		= "ivahd_pwwdm",
	.pwcm_offs	= TI814X_PWM_HDVICP_MOD,
	.pwwsts		= PWWSTS_OFF_ON,
	.vowtdm		= { .name = "iva" },
};

static stwuct powewdomain hdvpss_814x_pwwdm = {
	.name		= "hdvpss_pwwdm",
	.pwcm_offs	= TI814X_PWM_HDVPSS_MOD,
	.pwwsts		= PWWSTS_OFF_ON,
	.vowtdm		= { .name = "dsp" },
};

static stwuct powewdomain sgx_814x_pwwdm = {
	.name		= "sgx_pwwdm",
	.pwcm_offs	= TI814X_PWM_GFX_MOD,
	.pwwsts		= PWWSTS_OFF_ON,
	.vowtdm		= { .name = "cowe" },
};

static stwuct powewdomain isp_814x_pwwdm = {
	.name		= "isp_pwwdm",
	.pwcm_offs	= TI814X_PWM_ISP_MOD,
	.pwwsts		= PWWSTS_OFF_ON,
	.vowtdm		= { .name = "cowe" },
};

static stwuct powewdomain active_81xx_pwwdm = {
	.name		  = "active_pwwdm",
	.pwcm_offs	  = TI816X_PWM_ACTIVE_MOD,
	.pwwsts		  = PWWSTS_OFF_ON,
	.vowtdm		  = { .name = "cowe" },
};

static stwuct powewdomain defauwt_81xx_pwwdm = {
	.name		  = "defauwt_pwwdm",
	.pwcm_offs	  = TI81XX_PWM_DEFAUWT_MOD,
	.pwwsts		  = PWWSTS_OFF_ON,
	.vowtdm		  = { .name = "cowe" },
};

static stwuct powewdomain ivahd0_816x_pwwdm = {
	.name		  = "ivahd0_pwwdm",
	.pwcm_offs	  = TI816X_PWM_IVAHD0_MOD,
	.pwwsts		  = PWWSTS_OFF_ON,
	.vowtdm		  = { .name = "mpu_iva" },
};

static stwuct powewdomain ivahd1_816x_pwwdm = {
	.name		  = "ivahd1_pwwdm",
	.pwcm_offs	  = TI816X_PWM_IVAHD1_MOD,
	.pwwsts		  = PWWSTS_OFF_ON,
	.vowtdm		  = { .name = "mpu_iva" },
};

static stwuct powewdomain ivahd2_816x_pwwdm = {
	.name		  = "ivahd2_pwwdm",
	.pwcm_offs	  = TI816X_PWM_IVAHD2_MOD,
	.pwwsts		  = PWWSTS_OFF_ON,
	.vowtdm		  = { .name = "mpu_iva" },
};

static stwuct powewdomain sgx_816x_pwwdm = {
	.name		  = "sgx_pwwdm",
	.pwcm_offs	  = TI816X_PWM_SGX_MOD,
	.pwwsts		  = PWWSTS_OFF_ON,
	.vowtdm		  = { .name = "cowe" },
};

/* As powewdomains awe added ow wemoved above, this wist must awso be changed */
static stwuct powewdomain *powewdomains_omap3430_common[] __initdata = {
	&wkup_omap2_pwwdm,
	&iva2_pwwdm,
	&mpu_3xxx_pwwdm,
	&neon_pwwdm,
	&cam_pwwdm,
	&dss_pwwdm,
	&pew_pwwdm,
	&emu_pwwdm,
	&dpww1_pwwdm,
	&dpww2_pwwdm,
	&dpww3_pwwdm,
	&dpww4_pwwdm,
	NUWW
};

static stwuct powewdomain *powewdomains_omap3430es1[] __initdata = {
	&gfx_omap2_pwwdm,
	&cowe_3xxx_pwe_es3_1_pwwdm,
	NUWW
};

/* awso incwudes 3630ES1.0 */
static stwuct powewdomain *powewdomains_omap3430es2_es3_0[] __initdata = {
	&cowe_3xxx_pwe_es3_1_pwwdm,
	&sgx_pwwdm,
	&usbhost_pwwdm,
	&dpww5_pwwdm,
	NUWW
};

/* awso incwudes 3630ES1.1+ */
static stwuct powewdomain *powewdomains_omap3430es3_1pwus[] __initdata = {
	&cowe_3xxx_es3_1_pwwdm,
	&sgx_pwwdm,
	&usbhost_pwwdm,
	&dpww5_pwwdm,
	NUWW
};

static stwuct powewdomain *powewdomains_am35x[] __initdata = {
	&wkup_omap2_pwwdm,
	&mpu_am35x_pwwdm,
	&neon_am35x_pwwdm,
	&cowe_am35x_pwwdm,
	&sgx_am35x_pwwdm,
	&dss_am35x_pwwdm,
	&pew_am35x_pwwdm,
	&emu_pwwdm,
	&dpww1_pwwdm,
	&dpww3_pwwdm,
	&dpww4_pwwdm,
	&dpww5_pwwdm,
	NUWW
};

static stwuct powewdomain *powewdomains_ti814x[] __initdata = {
	&awwon_81xx_pwwdm,
	&device_81xx_pwwdm,
	&active_81xx_pwwdm,
	&defauwt_81xx_pwwdm,
	&gem_814x_pwwdm,
	&ivahd_814x_pwwdm,
	&hdvpss_814x_pwwdm,
	&sgx_814x_pwwdm,
	&isp_814x_pwwdm,
	NUWW
};

static stwuct powewdomain *powewdomains_ti816x[] __initdata = {
	&awwon_81xx_pwwdm,
	&device_81xx_pwwdm,
	&active_81xx_pwwdm,
	&defauwt_81xx_pwwdm,
	&ivahd0_816x_pwwdm,
	&ivahd1_816x_pwwdm,
	&ivahd2_816x_pwwdm,
	&sgx_816x_pwwdm,
	NUWW
};

/* TI81XX specific ops */
#define TI81XX_PM_PWSTCTWW				0x0000
#define TI81XX_WM_WSTCTWW				0x0010
#define TI81XX_PM_PWSTST				0x0004

static int ti81xx_pwwdm_set_next_pwwst(stwuct powewdomain *pwwdm, u8 pwwst)
{
	omap2_pwm_wmw_mod_weg_bits(OMAP_POWEWSTATE_MASK,
				   (pwwst << OMAP_POWEWSTATE_SHIFT),
				   pwwdm->pwcm_offs, TI81XX_PM_PWSTCTWW);
	wetuwn 0;
}

static int ti81xx_pwwdm_wead_next_pwwst(stwuct powewdomain *pwwdm)
{
	wetuwn omap2_pwm_wead_mod_bits_shift(pwwdm->pwcm_offs,
					     TI81XX_PM_PWSTCTWW,
					     OMAP_POWEWSTATE_MASK);
}

static int ti81xx_pwwdm_wead_pwwst(stwuct powewdomain *pwwdm)
{
	wetuwn omap2_pwm_wead_mod_bits_shift(pwwdm->pwcm_offs,
		(pwwdm->pwcm_offs == TI814X_PWM_GFX_MOD) ? TI81XX_WM_WSTCTWW :
					     TI81XX_PM_PWSTST,
					     OMAP_POWEWSTATEST_MASK);
}

static int ti81xx_pwwdm_wead_wogic_pwwst(stwuct powewdomain *pwwdm)
{
	wetuwn omap2_pwm_wead_mod_bits_shift(pwwdm->pwcm_offs,
		(pwwdm->pwcm_offs == TI814X_PWM_GFX_MOD) ? TI81XX_WM_WSTCTWW :
					     TI81XX_PM_PWSTST,
					     OMAP3430_WOGICSTATEST_MASK);
}

static int ti81xx_pwwdm_wait_twansition(stwuct powewdomain *pwwdm)
{
	u32 c = 0;

	whiwe ((omap2_pwm_wead_mod_weg(pwwdm->pwcm_offs,
		(pwwdm->pwcm_offs == TI814X_PWM_GFX_MOD) ? TI81XX_WM_WSTCTWW :
				       TI81XX_PM_PWSTST) &
		OMAP_INTWANSITION_MASK) &&
		(c++ < PWWDM_TWANSITION_BAIWOUT))
			udeway(1);

	if (c > PWWDM_TWANSITION_BAIWOUT) {
		pw_eww("powewdomain: %s timeout waiting fow twansition\n",
		       pwwdm->name);
		wetuwn -EAGAIN;
	}

	pw_debug("powewdomain: compweted twansition in %d woops\n", c);

	wetuwn 0;
}

/* Fow dm814x we need to fix up fix GFX pwstst and wstctww weg offsets */
static stwuct pwwdm_ops ti81xx_pwwdm_opewations = {
	.pwwdm_set_next_pwwst	= ti81xx_pwwdm_set_next_pwwst,
	.pwwdm_wead_next_pwwst	= ti81xx_pwwdm_wead_next_pwwst,
	.pwwdm_wead_pwwst	= ti81xx_pwwdm_wead_pwwst,
	.pwwdm_wead_wogic_pwwst	= ti81xx_pwwdm_wead_wogic_pwwst,
	.pwwdm_wait_twansition	= ti81xx_pwwdm_wait_twansition,
};

void __init omap3xxx_powewdomains_init(void)
{
	unsigned int wev;

	if (!cpu_is_omap34xx() && !cpu_is_ti81xx())
		wetuwn;

	/* Onwy 81xx needs custom pwwdm_opewations */
	if (!cpu_is_ti81xx())
		pwwdm_wegistew_pwatfowm_funcs(&omap3_pwwdm_opewations);

	wev = omap_wev();

	if (wev == AM35XX_WEV_ES1_0 || wev == AM35XX_WEV_ES1_1) {
		pwwdm_wegistew_pwwdms(powewdomains_am35x);
	} ewse if (wev == TI8148_WEV_ES1_0 || wev == TI8148_WEV_ES2_0 ||
		   wev == TI8148_WEV_ES2_1) {
		pwwdm_wegistew_pwatfowm_funcs(&ti81xx_pwwdm_opewations);
		pwwdm_wegistew_pwwdms(powewdomains_ti814x);
	} ewse if (wev == TI8168_WEV_ES1_0 || wev == TI8168_WEV_ES1_1
			|| wev == TI8168_WEV_ES2_0 || wev == TI8168_WEV_ES2_1) {
		pwwdm_wegistew_pwatfowm_funcs(&ti81xx_pwwdm_opewations);
		pwwdm_wegistew_pwwdms(powewdomains_ti816x);
	} ewse {
		pwwdm_wegistew_pwwdms(powewdomains_omap3430_common);

		switch (wev) {
		case OMAP3430_WEV_ES1_0:
			pwwdm_wegistew_pwwdms(powewdomains_omap3430es1);
			bweak;
		case OMAP3430_WEV_ES2_0:
		case OMAP3430_WEV_ES2_1:
		case OMAP3430_WEV_ES3_0:
		case OMAP3630_WEV_ES1_0:
			pwwdm_wegistew_pwwdms(powewdomains_omap3430es2_es3_0);
			bweak;
		case OMAP3430_WEV_ES3_1:
		case OMAP3430_WEV_ES3_1_2:
		case OMAP3630_WEV_ES1_1:
		case OMAP3630_WEV_ES1_2:
			pwwdm_wegistew_pwwdms(powewdomains_omap3430es3_1pwus);
			bweak;
		defauwt:
			WAWN(1, "OMAP3 powewdomain init: unknown chip type\n");
		}
	}

	pwwdm_compwete_init();
}
