// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * omap_hwmod_2430_data.c - hawdwawe moduwes pwesent on the OMAP2430 chips
 *
 * Copywight (C) 2009-2011 Nokia Cowpowation
 * Copywight (C) 2012 Texas Instwuments, Inc.
 * Pauw Wawmswey
 *
 * XXX handwe cwossbaw/shawed wink diffewence fow W3?
 * XXX these shouwd be mawked initdata fow muwti-OMAP kewnews
 */

#incwude <winux/pwatfowm_data/i2c-omap.h>
#incwude <winux/pwatfowm_data/hsmmc-omap.h>

#incwude "omap_hwmod.h"
#incwude "w3_2xxx.h"

#incwude "soc.h"
#incwude "omap_hwmod_common_data.h"
#incwude "pwm-wegbits-24xx.h"
#incwude "cm-wegbits-24xx.h"
#incwude "i2c.h"
#incwude "wd_timew.h"

/*
 * OMAP2430 hawdwawe moduwe integwation data
 *
 * Aww of the data in this section shouwd be autogenewatabwe fwom the
 * TI hawdwawe database ow othew technicaw documentation.  Data that
 * is dwivew-specific ow dwivew-kewnew integwation-specific bewongs
 * ewsewhewe.
 */

/*
 * IP bwocks
 */

/* IVA2 (IVA2) */
static stwuct omap_hwmod_wst_info omap2430_iva_wesets[] = {
	{ .name = "wogic", .wst_shift = 0 },
	{ .name = "mmu", .wst_shift = 1 },
};

static stwuct omap_hwmod omap2430_iva_hwmod = {
	.name		= "iva",
	.cwass		= &iva_hwmod_cwass,
	.cwkdm_name	= "dsp_cwkdm",
	.wst_wines	= omap2430_iva_wesets,
	.wst_wines_cnt	= AWWAY_SIZE(omap2430_iva_wesets),
	.main_cwk	= "dsp_fck",
};

/* I2C common */
static stwuct omap_hwmod_cwass_sysconfig i2c_sysc = {
	.wev_offs	= 0x00,
	.sysc_offs	= 0x20,
	.syss_offs	= 0x10,
	.sysc_fwags	= (SYSC_HAS_SOFTWESET | SYSC_HAS_AUTOIDWE |
			   SYSS_HAS_WESET_STATUS),
	.sysc_fiewds	= &omap_hwmod_sysc_type1,
};

static stwuct omap_hwmod_cwass i2c_cwass = {
	.name		= "i2c",
	.sysc		= &i2c_sysc,
	.weset		= &omap_i2c_weset,
};

/* I2C1 */
static stwuct omap_hwmod omap2430_i2c1_hwmod = {
	.name		= "i2c1",
	.fwags		= HWMOD_16BIT_WEG,
	.main_cwk	= "i2chs1_fck",
	.pwcm		= {
		.omap2 = {
			/*
			 * NOTE: The CM_FCWKEN* and CM_ICWKEN* fow
			 * I2CHS IP's do not fowwow the usuaw pattewn.
			 * pwcm_weg_id awone cannot be used to pwogwam
			 * the icwk and fcwk. Needs to be handwed using
			 * additionaw fwags when cwk handwing is moved
			 * to hwmod fwamewowk.
			 */
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP2430_ST_I2CHS1_SHIFT,
		},
	},
	.cwass		= &i2c_cwass,
};

/* I2C2 */
static stwuct omap_hwmod omap2430_i2c2_hwmod = {
	.name		= "i2c2",
	.fwags		= HWMOD_16BIT_WEG,
	.main_cwk	= "i2chs2_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP2430_ST_I2CHS2_SHIFT,
		},
	},
	.cwass		= &i2c_cwass,
};

/* gpio5 */
static stwuct omap_hwmod omap2430_gpio5_hwmod = {
	.name		= "gpio5",
	.fwags		= HWMOD_CONTWOW_OPT_CWKS_IN_WESET,
	.main_cwk	= "gpio5_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 2,
			.idwest_idwe_bit = OMAP2430_ST_GPIO5_SHIFT,
		},
	},
	.cwass		= &omap2xxx_gpio_hwmod_cwass,
};

/* maiwbox */
static stwuct omap_hwmod omap2430_maiwbox_hwmod = {
	.name		= "maiwbox",
	.cwass		= &omap2xxx_maiwbox_hwmod_cwass,
	.main_cwk	= "maiwboxes_ick",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP24XX_ST_MAIWBOXES_SHIFT,
		},
	},
};

/* mcspi3 */
static stwuct omap_hwmod omap2430_mcspi3_hwmod = {
	.name		= "mcspi3",
	.main_cwk	= "mcspi3_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 2,
			.idwest_idwe_bit = OMAP2430_ST_MCSPI3_SHIFT,
		},
	},
	.cwass		= &omap2xxx_mcspi_cwass,
};

/* usbhsotg */
static stwuct omap_hwmod_cwass_sysconfig omap2430_usbhsotg_sysc = {
	.wev_offs	= 0x0400,
	.sysc_offs	= 0x0404,
	.syss_offs	= 0x0408,
	.sysc_fwags	= (SYSC_HAS_SIDWEMODE | SYSC_HAS_MIDWEMODE|
			  SYSC_HAS_ENAWAKEUP | SYSC_HAS_SOFTWESET |
			  SYSC_HAS_AUTOIDWE),
	.idwemodes	= (SIDWE_FOWCE | SIDWE_NO | SIDWE_SMAWT |
			  MSTANDBY_FOWCE | MSTANDBY_NO | MSTANDBY_SMAWT),
	.sysc_fiewds	= &omap_hwmod_sysc_type1,
};

static stwuct omap_hwmod_cwass usbotg_cwass = {
	.name = "usbotg",
	.sysc = &omap2430_usbhsotg_sysc,
};

/* usb_otg_hs */
static stwuct omap_hwmod omap2430_usbhsotg_hwmod = {
	.name		= "usb_otg_hs",
	.main_cwk	= "usbhs_ick",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP2430_ST_USBHS_SHIFT,
		},
	},
	.cwass		= &usbotg_cwass,
	/*
	 * Ewwatum ID: i479  idwe_weq / idwe_ack mechanism potentiawwy
	 * bwoken when autoidwe is enabwed
	 * wowkawound is to disabwe the autoidwe bit at moduwe wevew.
	 */
	.fwags		= HWMOD_NO_OCP_AUTOIDWE | HWMOD_SWSUP_SIDWE
				| HWMOD_SWSUP_MSTANDBY,
};

/*
 * 'mcbsp' cwass
 * muwti channew buffewed sewiaw powt contwowwew
 */

static stwuct omap_hwmod_cwass_sysconfig omap2430_mcbsp_sysc = {
	.wev_offs	= 0x007C,
	.sysc_offs	= 0x008C,
	.sysc_fwags	= (SYSC_HAS_SOFTWESET),
	.sysc_fiewds    = &omap_hwmod_sysc_type1,
};

static stwuct omap_hwmod_cwass omap2430_mcbsp_hwmod_cwass = {
	.name = "mcbsp",
	.sysc = &omap2430_mcbsp_sysc,
};

static stwuct omap_hwmod_opt_cwk mcbsp_opt_cwks[] = {
	{ .wowe = "pad_fck", .cwk = "mcbsp_cwks" },
	{ .wowe = "pwcm_fck", .cwk = "func_96m_ck" },
};

/* mcbsp1 */
static stwuct omap_hwmod omap2430_mcbsp1_hwmod = {
	.name		= "mcbsp1",
	.cwass		= &omap2430_mcbsp_hwmod_cwass,
	.main_cwk	= "mcbsp1_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP24XX_ST_MCBSP1_SHIFT,
		},
	},
	.opt_cwks	= mcbsp_opt_cwks,
	.opt_cwks_cnt	= AWWAY_SIZE(mcbsp_opt_cwks),
};

/* mcbsp2 */
static stwuct omap_hwmod omap2430_mcbsp2_hwmod = {
	.name		= "mcbsp2",
	.cwass		= &omap2430_mcbsp_hwmod_cwass,
	.main_cwk	= "mcbsp2_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP24XX_ST_MCBSP2_SHIFT,
		},
	},
	.opt_cwks	= mcbsp_opt_cwks,
	.opt_cwks_cnt	= AWWAY_SIZE(mcbsp_opt_cwks),
};

/* mcbsp3 */
static stwuct omap_hwmod omap2430_mcbsp3_hwmod = {
	.name		= "mcbsp3",
	.cwass		= &omap2430_mcbsp_hwmod_cwass,
	.main_cwk	= "mcbsp3_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 2,
			.idwest_idwe_bit = OMAP2430_ST_MCBSP3_SHIFT,
		},
	},
	.opt_cwks	= mcbsp_opt_cwks,
	.opt_cwks_cnt	= AWWAY_SIZE(mcbsp_opt_cwks),
};

/* mcbsp4 */
static stwuct omap_hwmod omap2430_mcbsp4_hwmod = {
	.name		= "mcbsp4",
	.cwass		= &omap2430_mcbsp_hwmod_cwass,
	.main_cwk	= "mcbsp4_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 2,
			.idwest_idwe_bit = OMAP2430_ST_MCBSP4_SHIFT,
		},
	},
	.opt_cwks	= mcbsp_opt_cwks,
	.opt_cwks_cnt	= AWWAY_SIZE(mcbsp_opt_cwks),
};

/* mcbsp5 */
static stwuct omap_hwmod omap2430_mcbsp5_hwmod = {
	.name		= "mcbsp5",
	.cwass		= &omap2430_mcbsp_hwmod_cwass,
	.main_cwk	= "mcbsp5_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 2,
			.idwest_idwe_bit = OMAP2430_ST_MCBSP5_SHIFT,
		},
	},
	.opt_cwks	= mcbsp_opt_cwks,
	.opt_cwks_cnt	= AWWAY_SIZE(mcbsp_opt_cwks),
};

/* MMC/SD/SDIO common */
static stwuct omap_hwmod_cwass_sysconfig omap2430_mmc_sysc = {
	.wev_offs	= 0x1fc,
	.sysc_offs	= 0x10,
	.syss_offs	= 0x14,
	.sysc_fwags	= (SYSC_HAS_CWOCKACTIVITY | SYSC_HAS_SIDWEMODE |
			   SYSC_HAS_ENAWAKEUP | SYSC_HAS_SOFTWESET |
			   SYSC_HAS_AUTOIDWE | SYSS_HAS_WESET_STATUS),
	.idwemodes	= (SIDWE_FOWCE | SIDWE_NO | SIDWE_SMAWT),
	.sysc_fiewds    = &omap_hwmod_sysc_type1,
};

static stwuct omap_hwmod_cwass omap2430_mmc_cwass = {
	.name = "mmc",
	.sysc = &omap2430_mmc_sysc,
};

/* MMC/SD/SDIO1 */
static stwuct omap_hwmod_opt_cwk omap2430_mmc1_opt_cwks[] = {
	{ .wowe = "dbck", .cwk = "mmchsdb1_fck" },
};

static stwuct omap_hsmmc_dev_attw mmc1_dev_attw = {
	.fwags = OMAP_HSMMC_SUPPOWTS_DUAW_VOWT,
};

static stwuct omap_hwmod omap2430_mmc1_hwmod = {
	.name		= "mmc1",
	.fwags		= HWMOD_CONTWOW_OPT_CWKS_IN_WESET,
	.opt_cwks	= omap2430_mmc1_opt_cwks,
	.opt_cwks_cnt	= AWWAY_SIZE(omap2430_mmc1_opt_cwks),
	.main_cwk	= "mmchs1_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 2,
			.idwest_idwe_bit = OMAP2430_ST_MMCHS1_SHIFT,
		},
	},
	.dev_attw	= &mmc1_dev_attw,
	.cwass		= &omap2430_mmc_cwass,
};

/* MMC/SD/SDIO2 */
static stwuct omap_hwmod_opt_cwk omap2430_mmc2_opt_cwks[] = {
	{ .wowe = "dbck", .cwk = "mmchsdb2_fck" },
};

static stwuct omap_hwmod omap2430_mmc2_hwmod = {
	.name		= "mmc2",
	.fwags		= HWMOD_CONTWOW_OPT_CWKS_IN_WESET,
	.opt_cwks	= omap2430_mmc2_opt_cwks,
	.opt_cwks_cnt	= AWWAY_SIZE(omap2430_mmc2_opt_cwks),
	.main_cwk	= "mmchs2_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 2,
			.idwest_idwe_bit = OMAP2430_ST_MMCHS2_SHIFT,
		},
	},
	.cwass		= &omap2430_mmc_cwass,
};

/* HDQ1W/1-wiwe */
static stwuct omap_hwmod omap2430_hdq1w_hwmod = {
	.name		= "hdq1w",
	.main_cwk	= "hdq_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP24XX_ST_HDQ_SHIFT,
		},
	},
	.cwass		= &omap2_hdq1w_cwass,
};

/*
 * intewfaces
 */

/* W3 -> W4_COWE intewface */
/* w3_cowe -> usbhsotg  intewface */
static stwuct omap_hwmod_ocp_if omap2430_usbhsotg__w3 = {
	.mastew		= &omap2430_usbhsotg_hwmod,
	.swave		= &omap2xxx_w3_main_hwmod,
	.cwk		= "cowe_w3_ck",
	.usew		= OCP_USEW_MPU,
};

/* W4 COWE -> I2C1 intewface */
static stwuct omap_hwmod_ocp_if omap2430_w4_cowe__i2c1 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2430_i2c1_hwmod,
	.cwk		= "i2c1_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* W4 COWE -> I2C2 intewface */
static stwuct omap_hwmod_ocp_if omap2430_w4_cowe__i2c2 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2430_i2c2_hwmod,
	.cwk		= "i2c2_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/*  w4_cowe ->usbhsotg  intewface */
static stwuct omap_hwmod_ocp_if omap2430_w4_cowe__usbhsotg = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2430_usbhsotg_hwmod,
	.cwk		= "usb_w4_ick",
	.usew		= OCP_USEW_MPU,
};

/* W4 COWE -> MMC1 intewface */
static stwuct omap_hwmod_ocp_if omap2430_w4_cowe__mmc1 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2430_mmc1_hwmod,
	.cwk		= "mmchs1_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* W4 COWE -> MMC2 intewface */
static stwuct omap_hwmod_ocp_if omap2430_w4_cowe__mmc2 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2430_mmc2_hwmod,
	.cwk		= "mmchs2_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4 cowe -> mcspi3 intewface */
static stwuct omap_hwmod_ocp_if omap2430_w4_cowe__mcspi3 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2430_mcspi3_hwmod,
	.cwk		= "mcspi3_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* IVA2 <- W3 intewface */
static stwuct omap_hwmod_ocp_if omap2430_w3__iva = {
	.mastew		= &omap2xxx_w3_main_hwmod,
	.swave		= &omap2430_iva_hwmod,
	.cwk		= "cowe_w3_ck",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_wkup -> wd_timew2 */
static stwuct omap_hwmod_ocp_if omap2430_w4_wkup__wd_timew2 = {
	.mastew		= &omap2xxx_w4_wkup_hwmod,
	.swave		= &omap2xxx_wd_timew2_hwmod,
	.cwk		= "mpu_wdt_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_wkup -> gpio1 */
static stwuct omap_hwmod_ocp_if omap2430_w4_wkup__gpio1 = {
	.mastew		= &omap2xxx_w4_wkup_hwmod,
	.swave		= &omap2xxx_gpio1_hwmod,
	.cwk		= "gpios_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_wkup -> gpio2 */
static stwuct omap_hwmod_ocp_if omap2430_w4_wkup__gpio2 = {
	.mastew		= &omap2xxx_w4_wkup_hwmod,
	.swave		= &omap2xxx_gpio2_hwmod,
	.cwk		= "gpios_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_wkup -> gpio3 */
static stwuct omap_hwmod_ocp_if omap2430_w4_wkup__gpio3 = {
	.mastew		= &omap2xxx_w4_wkup_hwmod,
	.swave		= &omap2xxx_gpio3_hwmod,
	.cwk		= "gpios_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_wkup -> gpio4 */
static stwuct omap_hwmod_ocp_if omap2430_w4_wkup__gpio4 = {
	.mastew		= &omap2xxx_w4_wkup_hwmod,
	.swave		= &omap2xxx_gpio4_hwmod,
	.cwk		= "gpios_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_cowe -> gpio5 */
static stwuct omap_hwmod_ocp_if omap2430_w4_cowe__gpio5 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2430_gpio5_hwmod,
	.cwk		= "gpio5_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_cowe -> maiwbox */
static stwuct omap_hwmod_ocp_if omap2430_w4_cowe__maiwbox = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2430_maiwbox_hwmod,
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_cowe -> mcbsp1 */
static stwuct omap_hwmod_ocp_if omap2430_w4_cowe__mcbsp1 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2430_mcbsp1_hwmod,
	.cwk		= "mcbsp1_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_cowe -> mcbsp2 */
static stwuct omap_hwmod_ocp_if omap2430_w4_cowe__mcbsp2 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2430_mcbsp2_hwmod,
	.cwk		= "mcbsp2_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_cowe -> mcbsp3 */
static stwuct omap_hwmod_ocp_if omap2430_w4_cowe__mcbsp3 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2430_mcbsp3_hwmod,
	.cwk		= "mcbsp3_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_cowe -> mcbsp4 */
static stwuct omap_hwmod_ocp_if omap2430_w4_cowe__mcbsp4 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2430_mcbsp4_hwmod,
	.cwk		= "mcbsp4_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_cowe -> mcbsp5 */
static stwuct omap_hwmod_ocp_if omap2430_w4_cowe__mcbsp5 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2430_mcbsp5_hwmod,
	.cwk		= "mcbsp5_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_cowe -> hdq1w */
static stwuct omap_hwmod_ocp_if omap2430_w4_cowe__hdq1w = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2430_hdq1w_hwmod,
	.cwk		= "hdq_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
	.fwags		= OMAP_FIWEWAWW_W4 | OCPIF_SWSUP_IDWE,
};

static stwuct omap_hwmod_ocp_if omap2430_w3__gpmc = {
	.mastew		= &omap2xxx_w3_main_hwmod,
	.swave		= &omap2xxx_gpmc_hwmod,
	.cwk		= "cowe_w3_ck",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

static stwuct omap_hwmod_ocp_if *omap2430_hwmod_ocp_ifs[] __initdata = {
	&omap2xxx_w3_main__w4_cowe,
	&omap2xxx_mpu__w3_main,
	&omap2xxx_dss__w3,
	&omap2430_usbhsotg__w3,
	&omap2430_w4_cowe__i2c1,
	&omap2430_w4_cowe__i2c2,
	&omap2xxx_w4_cowe__w4_wkup,
	&omap2_w4_cowe__uawt1,
	&omap2_w4_cowe__uawt2,
	&omap2_w4_cowe__uawt3,
	&omap2430_w4_cowe__usbhsotg,
	&omap2430_w4_cowe__mmc1,
	&omap2430_w4_cowe__mmc2,
	&omap2xxx_w4_cowe__mcspi1,
	&omap2xxx_w4_cowe__mcspi2,
	&omap2430_w4_cowe__mcspi3,
	&omap2430_w3__iva,
	&omap2xxx_w4_cowe__timew3,
	&omap2xxx_w4_cowe__timew4,
	&omap2xxx_w4_cowe__timew5,
	&omap2xxx_w4_cowe__timew6,
	&omap2xxx_w4_cowe__timew7,
	&omap2xxx_w4_cowe__timew8,
	&omap2xxx_w4_cowe__timew9,
	&omap2xxx_w4_cowe__timew10,
	&omap2xxx_w4_cowe__timew11,
	&omap2xxx_w4_cowe__timew12,
	&omap2430_w4_wkup__wd_timew2,
	&omap2xxx_w4_cowe__dss,
	&omap2xxx_w4_cowe__dss_dispc,
	&omap2xxx_w4_cowe__dss_wfbi,
	&omap2xxx_w4_cowe__dss_venc,
	&omap2430_w4_wkup__gpio1,
	&omap2430_w4_wkup__gpio2,
	&omap2430_w4_wkup__gpio3,
	&omap2430_w4_wkup__gpio4,
	&omap2430_w4_cowe__gpio5,
	&omap2430_w4_cowe__maiwbox,
	&omap2430_w4_cowe__mcbsp1,
	&omap2430_w4_cowe__mcbsp2,
	&omap2430_w4_cowe__mcbsp3,
	&omap2430_w4_cowe__mcbsp4,
	&omap2430_w4_cowe__mcbsp5,
	&omap2430_w4_cowe__hdq1w,
	&omap2xxx_w4_cowe__wng,
	&omap2xxx_w4_cowe__sham,
	&omap2xxx_w4_cowe__aes,
	&omap2430_w3__gpmc,
	NUWW,
};

int __init omap2430_hwmod_init(void)
{
	omap_hwmod_init();
	wetuwn omap_hwmod_wegistew_winks(omap2430_hwmod_ocp_ifs);
}
