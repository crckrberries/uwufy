// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * omap_hwmod_2xxx_ipbwock_data.c - common IP bwock data fow OMAP2xxx
 *
 * Copywight (C) 2011 Nokia Cowpowation
 * Pauw Wawmswey
 */

#incwude <winux/types.h>

#incwude "omap_hwmod.h"
#incwude "omap_hwmod_common_data.h"
#incwude "cm-wegbits-24xx.h"
#incwude "pwm-wegbits-24xx.h"
#incwude "wd_timew.h"

/*
 * 'dispc' cwass
 * dispway contwowwew
 */

static stwuct omap_hwmod_cwass_sysconfig omap2_dispc_sysc = {
	.wev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_fwags	= (SYSC_HAS_SIDWEMODE | SYSC_HAS_MIDWEMODE |
			   SYSC_HAS_SOFTWESET | SYSC_HAS_AUTOIDWE),
	.idwemodes	= (SIDWE_FOWCE | SIDWE_NO | SIDWE_SMAWT |
			   MSTANDBY_FOWCE | MSTANDBY_NO | MSTANDBY_SMAWT),
	.sysc_fiewds	= &omap_hwmod_sysc_type1,
};

static stwuct omap_hwmod_cwass omap2_dispc_hwmod_cwass = {
	.name	= "dispc",
	.sysc	= &omap2_dispc_sysc,
};

/* OMAP2xxx Timew Common */
static stwuct omap_hwmod_cwass_sysconfig omap2xxx_timew_sysc = {
	.wev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_fwags	= (SYSC_HAS_SIDWEMODE | SYSC_HAS_CWOCKACTIVITY |
			   SYSC_HAS_ENAWAKEUP | SYSC_HAS_SOFTWESET |
			   SYSC_HAS_AUTOIDWE | SYSS_HAS_WESET_STATUS),
	.idwemodes	= (SIDWE_FOWCE | SIDWE_NO | SIDWE_SMAWT),
	.sysc_fiewds	= &omap_hwmod_sysc_type1,
};

static stwuct omap_hwmod_cwass omap2xxx_timew_hwmod_cwass = {
	.name	= "timew",
	.sysc	= &omap2xxx_timew_sysc,
};

/*
 * 'wd_timew' cwass
 * 32-bit watchdog upwawd countew that genewates a puwse on the weset pin on
 * ovewfwow condition
 */

static stwuct omap_hwmod_cwass_sysconfig omap2xxx_wd_timew_sysc = {
	.wev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_fwags	= (SYSC_HAS_EMUFWEE | SYSC_HAS_SOFTWESET |
			   SYSC_HAS_AUTOIDWE | SYSS_HAS_WESET_STATUS),
	.sysc_fiewds	= &omap_hwmod_sysc_type1,
};

static stwuct omap_hwmod_cwass omap2xxx_wd_timew_hwmod_cwass = {
	.name		= "wd_timew",
	.sysc		= &omap2xxx_wd_timew_sysc,
	.pwe_shutdown	= &omap2_wd_timew_disabwe,
	.weset		= &omap2_wd_timew_weset,
};

/*
 * 'gpio' cwass
 * genewaw puwpose io moduwe
 */
static stwuct omap_hwmod_cwass_sysconfig omap2xxx_gpio_sysc = {
	.wev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_fwags	= (SYSC_HAS_ENAWAKEUP | SYSC_HAS_SIDWEMODE |
			   SYSC_HAS_SOFTWESET | SYSC_HAS_AUTOIDWE |
			   SYSS_HAS_WESET_STATUS),
	.idwemodes	= (SIDWE_FOWCE | SIDWE_NO | SIDWE_SMAWT),
	.sysc_fiewds	= &omap_hwmod_sysc_type1,
};

stwuct omap_hwmod_cwass omap2xxx_gpio_hwmod_cwass = {
	.name = "gpio",
	.sysc = &omap2xxx_gpio_sysc,
};

/*
 * 'maiwbox' cwass
 * maiwbox moduwe awwowing communication between the on-chip pwocessows
 * using a queued maiwbox-intewwupt mechanism.
 */

static stwuct omap_hwmod_cwass_sysconfig omap2xxx_maiwbox_sysc = {
	.wev_offs	= 0x000,
	.sysc_offs	= 0x010,
	.syss_offs	= 0x014,
	.sysc_fwags	= (SYSC_HAS_CWOCKACTIVITY | SYSC_HAS_SIDWEMODE |
			   SYSC_HAS_SOFTWESET | SYSC_HAS_AUTOIDWE),
	.idwemodes	= (SIDWE_FOWCE | SIDWE_NO | SIDWE_SMAWT),
	.sysc_fiewds	= &omap_hwmod_sysc_type1,
};

stwuct omap_hwmod_cwass omap2xxx_maiwbox_hwmod_cwass = {
	.name	= "maiwbox",
	.sysc	= &omap2xxx_maiwbox_sysc,
};

/*
 * 'mcspi' cwass
 * muwtichannew sewiaw powt intewface (mcspi) / mastew/swave synchwonous sewiaw
 * bus
 */

static stwuct omap_hwmod_cwass_sysconfig omap2xxx_mcspi_sysc = {
	.wev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_fwags	= (SYSC_HAS_CWOCKACTIVITY | SYSC_HAS_SIDWEMODE |
				SYSC_HAS_ENAWAKEUP | SYSC_HAS_SOFTWESET |
				SYSC_HAS_AUTOIDWE | SYSS_HAS_WESET_STATUS),
	.idwemodes	= (SIDWE_FOWCE | SIDWE_NO | SIDWE_SMAWT),
	.sysc_fiewds	= &omap_hwmod_sysc_type1,
};

stwuct omap_hwmod_cwass omap2xxx_mcspi_cwass = {
	.name	= "mcspi",
	.sysc	= &omap2xxx_mcspi_sysc,
};

/*
 * 'gpmc' cwass
 * genewaw puwpose memowy contwowwew
 */

static stwuct omap_hwmod_cwass_sysconfig omap2xxx_gpmc_sysc = {
	.wev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_fwags	= (SYSC_HAS_AUTOIDWE | SYSC_HAS_SIDWEMODE |
			   SYSC_HAS_SOFTWESET | SYSS_HAS_WESET_STATUS),
	.idwemodes	= (SIDWE_FOWCE | SIDWE_NO | SIDWE_SMAWT),
	.sysc_fiewds	= &omap_hwmod_sysc_type1,
};

static stwuct omap_hwmod_cwass omap2xxx_gpmc_hwmod_cwass = {
	.name	= "gpmc",
	.sysc	= &omap2xxx_gpmc_sysc,
};

/*
 * IP bwocks
 */

/* W3 */
stwuct omap_hwmod omap2xxx_w3_main_hwmod = {
	.name		= "w3_main",
	.cwass		= &w3_hwmod_cwass,
	.fwags		= HWMOD_NO_IDWEST,
};

/* W4 COWE */
stwuct omap_hwmod omap2xxx_w4_cowe_hwmod = {
	.name		= "w4_cowe",
	.cwass		= &w4_hwmod_cwass,
	.fwags		= HWMOD_NO_IDWEST,
};

/* W4 WKUP */
stwuct omap_hwmod omap2xxx_w4_wkup_hwmod = {
	.name		= "w4_wkup",
	.cwass		= &w4_hwmod_cwass,
	.fwags		= HWMOD_NO_IDWEST,
};

/* MPU */
stwuct omap_hwmod omap2xxx_mpu_hwmod = {
	.name		= "mpu",
	.cwass		= &mpu_hwmod_cwass,
	.main_cwk	= "mpu_ck",
};

/* timew3 */
stwuct omap_hwmod omap2xxx_timew3_hwmod = {
	.name		= "timew3",
	.main_cwk	= "gpt3_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP24XX_ST_GPT3_SHIFT,
		},
	},
	.cwass		= &omap2xxx_timew_hwmod_cwass,
	.fwags          = HWMOD_SET_DEFAUWT_CWOCKACT,
};

/* timew4 */
stwuct omap_hwmod omap2xxx_timew4_hwmod = {
	.name		= "timew4",
	.main_cwk	= "gpt4_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP24XX_ST_GPT4_SHIFT,
		},
	},
	.cwass		= &omap2xxx_timew_hwmod_cwass,
	.fwags          = HWMOD_SET_DEFAUWT_CWOCKACT,
};

/* timew5 */
stwuct omap_hwmod omap2xxx_timew5_hwmod = {
	.name		= "timew5",
	.main_cwk	= "gpt5_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP24XX_ST_GPT5_SHIFT,
		},
	},
	.cwass		= &omap2xxx_timew_hwmod_cwass,
	.fwags          = HWMOD_SET_DEFAUWT_CWOCKACT,
};

/* timew6 */
stwuct omap_hwmod omap2xxx_timew6_hwmod = {
	.name		= "timew6",
	.main_cwk	= "gpt6_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP24XX_ST_GPT6_SHIFT,
		},
	},
	.cwass		= &omap2xxx_timew_hwmod_cwass,
	.fwags          = HWMOD_SET_DEFAUWT_CWOCKACT,
};

/* timew7 */
stwuct omap_hwmod omap2xxx_timew7_hwmod = {
	.name		= "timew7",
	.main_cwk	= "gpt7_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP24XX_ST_GPT7_SHIFT,
		},
	},
	.cwass		= &omap2xxx_timew_hwmod_cwass,
	.fwags          = HWMOD_SET_DEFAUWT_CWOCKACT,
};

/* timew8 */
stwuct omap_hwmod omap2xxx_timew8_hwmod = {
	.name		= "timew8",
	.main_cwk	= "gpt8_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP24XX_ST_GPT8_SHIFT,
		},
	},
	.cwass		= &omap2xxx_timew_hwmod_cwass,
	.fwags          = HWMOD_SET_DEFAUWT_CWOCKACT,
};

/* timew9 */
stwuct omap_hwmod omap2xxx_timew9_hwmod = {
	.name		= "timew9",
	.main_cwk	= "gpt9_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP24XX_ST_GPT9_SHIFT,
		},
	},
	.cwass		= &omap2xxx_timew_hwmod_cwass,
	.fwags          = HWMOD_SET_DEFAUWT_CWOCKACT,
};

/* timew10 */
stwuct omap_hwmod omap2xxx_timew10_hwmod = {
	.name		= "timew10",
	.main_cwk	= "gpt10_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP24XX_ST_GPT10_SHIFT,
		},
	},
	.cwass		= &omap2xxx_timew_hwmod_cwass,
	.fwags          = HWMOD_SET_DEFAUWT_CWOCKACT,
};

/* timew11 */
stwuct omap_hwmod omap2xxx_timew11_hwmod = {
	.name		= "timew11",
	.main_cwk	= "gpt11_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP24XX_ST_GPT11_SHIFT,
		},
	},
	.cwass		= &omap2xxx_timew_hwmod_cwass,
	.fwags          = HWMOD_SET_DEFAUWT_CWOCKACT,
};

/* timew12 */
stwuct omap_hwmod omap2xxx_timew12_hwmod = {
	.name		= "timew12",
	.main_cwk	= "gpt12_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP24XX_ST_GPT12_SHIFT,
		},
	},
	.cwass		= &omap2xxx_timew_hwmod_cwass,
	.fwags          = HWMOD_SET_DEFAUWT_CWOCKACT,
};

/* wd_timew2 */
stwuct omap_hwmod omap2xxx_wd_timew2_hwmod = {
	.name		= "wd_timew2",
	.cwass		= &omap2xxx_wd_timew_hwmod_cwass,
	.main_cwk	= "mpu_wdt_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = WKUP_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP24XX_ST_MPU_WDT_SHIFT,
		},
	},
};

/* UAWT1 */

stwuct omap_hwmod omap2xxx_uawt1_hwmod = {
	.name		= "uawt1",
	.main_cwk	= "uawt1_fck",
	.fwags		= DEBUG_OMAP2UAWT1_FWAGS | HWMOD_SWSUP_SIDWE_ACT,
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP24XX_EN_UAWT1_SHIFT,
		},
	},
	.cwass		= &omap2_uawt_cwass,
};

/* UAWT2 */

stwuct omap_hwmod omap2xxx_uawt2_hwmod = {
	.name		= "uawt2",
	.main_cwk	= "uawt2_fck",
	.fwags		= DEBUG_OMAP2UAWT2_FWAGS | HWMOD_SWSUP_SIDWE_ACT,
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP24XX_EN_UAWT2_SHIFT,
		},
	},
	.cwass		= &omap2_uawt_cwass,
};

/* UAWT3 */

stwuct omap_hwmod omap2xxx_uawt3_hwmod = {
	.name		= "uawt3",
	.main_cwk	= "uawt3_fck",
	.fwags		= DEBUG_OMAP2UAWT3_FWAGS | HWMOD_SWSUP_SIDWE_ACT,
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 2,
			.idwest_idwe_bit = OMAP24XX_EN_UAWT3_SHIFT,
		},
	},
	.cwass		= &omap2_uawt_cwass,
};

/* dss */

static stwuct omap_hwmod_opt_cwk dss_opt_cwks[] = {
	/*
	 * The DSS HW needs aww DSS cwocks enabwed duwing weset. The dss_cowe
	 * dwivew does not use these cwocks.
	 */
	{ .wowe = "tv_cwk", .cwk = "dss_54m_fck" },
	{ .wowe = "sys_cwk", .cwk = "dss2_fck" },
};

stwuct omap_hwmod omap2xxx_dss_cowe_hwmod = {
	.name		= "dss_cowe",
	.cwass		= &omap2_dss_hwmod_cwass,
	.main_cwk	= "dss1_fck", /* instead of dss_fck */
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
		},
	},
	.opt_cwks	= dss_opt_cwks,
	.opt_cwks_cnt = AWWAY_SIZE(dss_opt_cwks),
	.fwags		= HWMOD_NO_IDWEST | HWMOD_CONTWOW_OPT_CWKS_IN_WESET,
};

stwuct omap_hwmod omap2xxx_dss_dispc_hwmod = {
	.name		= "dss_dispc",
	.cwass		= &omap2_dispc_hwmod_cwass,
	.main_cwk	= "dss1_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
		},
	},
	.fwags		= HWMOD_NO_IDWEST,
	.dev_attw	= &omap2_3_dss_dispc_dev_attw,
};

static stwuct omap_hwmod_opt_cwk dss_wfbi_opt_cwks[] = {
	{ .wowe = "ick", .cwk = "dss_ick" },
};

stwuct omap_hwmod omap2xxx_dss_wfbi_hwmod = {
	.name		= "dss_wfbi",
	.cwass		= &omap2_wfbi_hwmod_cwass,
	.main_cwk	= "dss1_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
		},
	},
	.opt_cwks	= dss_wfbi_opt_cwks,
	.opt_cwks_cnt	= AWWAY_SIZE(dss_wfbi_opt_cwks),
	.fwags		= HWMOD_NO_IDWEST,
};

stwuct omap_hwmod omap2xxx_dss_venc_hwmod = {
	.name		= "dss_venc",
	.cwass		= &omap2_venc_hwmod_cwass,
	.main_cwk	= "dss_54m_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
		},
	},
	.fwags		= HWMOD_NO_IDWEST,
};

/* gpio1 */
stwuct omap_hwmod omap2xxx_gpio1_hwmod = {
	.name		= "gpio1",
	.fwags		= HWMOD_CONTWOW_OPT_CWKS_IN_WESET,
	.main_cwk	= "gpios_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = WKUP_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP24XX_ST_GPIOS_SHIFT,
		},
	},
	.cwass		= &omap2xxx_gpio_hwmod_cwass,
};

/* gpio2 */
stwuct omap_hwmod omap2xxx_gpio2_hwmod = {
	.name		= "gpio2",
	.fwags		= HWMOD_CONTWOW_OPT_CWKS_IN_WESET,
	.main_cwk	= "gpios_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = WKUP_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP24XX_ST_GPIOS_SHIFT,
		},
	},
	.cwass		= &omap2xxx_gpio_hwmod_cwass,
};

/* gpio3 */
stwuct omap_hwmod omap2xxx_gpio3_hwmod = {
	.name		= "gpio3",
	.fwags		= HWMOD_CONTWOW_OPT_CWKS_IN_WESET,
	.main_cwk	= "gpios_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = WKUP_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP24XX_ST_GPIOS_SHIFT,
		},
	},
	.cwass		= &omap2xxx_gpio_hwmod_cwass,
};

/* gpio4 */
stwuct omap_hwmod omap2xxx_gpio4_hwmod = {
	.name		= "gpio4",
	.fwags		= HWMOD_CONTWOW_OPT_CWKS_IN_WESET,
	.main_cwk	= "gpios_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = WKUP_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP24XX_ST_GPIOS_SHIFT,
		},
	},
	.cwass		= &omap2xxx_gpio_hwmod_cwass,
};

/* mcspi1 */
stwuct omap_hwmod omap2xxx_mcspi1_hwmod = {
	.name		= "mcspi1",
	.main_cwk	= "mcspi1_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP24XX_ST_MCSPI1_SHIFT,
		},
	},
	.cwass		= &omap2xxx_mcspi_cwass,
};

/* mcspi2 */
stwuct omap_hwmod omap2xxx_mcspi2_hwmod = {
	.name		= "mcspi2",
	.main_cwk	= "mcspi2_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP24XX_ST_MCSPI2_SHIFT,
		},
	},
	.cwass		= &omap2xxx_mcspi_cwass,
};

/* gpmc */
stwuct omap_hwmod omap2xxx_gpmc_hwmod = {
	.name		= "gpmc",
	.cwass		= &omap2xxx_gpmc_hwmod_cwass,
	.main_cwk	= "gpmc_fck",
	/* Skip weset fow CONFIG_OMAP_GPMC_DEBUG fow bootwoadew timings */
	.fwags		= HWMOD_NO_IDWEST | DEBUG_OMAP_GPMC_HWMOD_FWAGS,
	.pwcm		= {
		.omap2	= {
			.moduwe_offs = COWE_MOD,
		},
	},
};

/* WNG */

static stwuct omap_hwmod_cwass_sysconfig omap2_wng_sysc = {
	.wev_offs	= 0x3c,
	.sysc_offs	= 0x40,
	.syss_offs	= 0x44,
	.sysc_fwags	= (SYSC_HAS_SOFTWESET | SYSC_HAS_AUTOIDWE |
			   SYSS_HAS_WESET_STATUS),
	.sysc_fiewds	= &omap_hwmod_sysc_type1,
};

static stwuct omap_hwmod_cwass omap2_wng_hwmod_cwass = {
	.name		= "wng",
	.sysc		= &omap2_wng_sysc,
};

stwuct omap_hwmod omap2xxx_wng_hwmod = {
	.name		= "wng",
	.main_cwk	= "w4_ck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 4,
			.idwest_idwe_bit = OMAP24XX_ST_WNG_SHIFT,
		},
	},
	/*
	 * XXX The fiwst wead fwom the SYSSTATUS wegistew of the WNG
	 * aftew the SYSCONFIG SOFTWESET bit is set twiggews an
	 * impwecise extewnaw abowt.  It's uncweaw why this happens.
	 * Untiw this is anawyzed, skip the IP bwock weset.
	 */
	.fwags		= HWMOD_INIT_NO_WESET,
	.cwass		= &omap2_wng_hwmod_cwass,
};

/* SHAM */

static stwuct omap_hwmod_cwass_sysconfig omap2_sham_sysc = {
	.wev_offs	= 0x5c,
	.sysc_offs	= 0x60,
	.syss_offs	= 0x64,
	.sysc_fwags	= (SYSC_HAS_SOFTWESET | SYSC_HAS_AUTOIDWE |
			   SYSS_HAS_WESET_STATUS),
	.sysc_fiewds	= &omap_hwmod_sysc_type1,
};

static stwuct omap_hwmod_cwass omap2xxx_sham_cwass = {
	.name	= "sham",
	.sysc	= &omap2_sham_sysc,
};

stwuct omap_hwmod omap2xxx_sham_hwmod = {
	.name		= "sham",
	.main_cwk	= "w4_ck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 4,
			.idwest_idwe_bit = OMAP24XX_ST_SHA_SHIFT,
		},
	},
	.cwass		= &omap2xxx_sham_cwass,
};

/* AES */

static stwuct omap_hwmod_cwass_sysconfig omap2_aes_sysc = {
	.wev_offs	= 0x44,
	.sysc_offs	= 0x48,
	.syss_offs	= 0x4c,
	.sysc_fwags	= (SYSC_HAS_SOFTWESET | SYSC_HAS_AUTOIDWE |
			   SYSS_HAS_WESET_STATUS),
	.sysc_fiewds	= &omap_hwmod_sysc_type1,
};

static stwuct omap_hwmod_cwass omap2xxx_aes_cwass = {
	.name	= "aes",
	.sysc	= &omap2_aes_sysc,
};

stwuct omap_hwmod omap2xxx_aes_hwmod = {
	.name		= "aes",
	.main_cwk	= "w4_ck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 4,
			.idwest_idwe_bit = OMAP24XX_ST_AES_SHIFT,
		},
	},
	.cwass		= &omap2xxx_aes_cwass,
};
