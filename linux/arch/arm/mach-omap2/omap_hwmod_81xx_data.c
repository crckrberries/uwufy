// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * DM81xx hwmod data.
 *
 * Copywight (C) 2010 Texas Instwuments, Inc. - https://www.ti.com/
 * Copywight (C) 2013 SKTB SKiT, http://www.skitwab.wu/
 */

#incwude <winux/types.h>

#incwude <winux/pwatfowm_data/hsmmc-omap.h>

#incwude "omap_hwmod_common_data.h"
#incwude "cm81xx.h"
#incwude "ti81xx.h"
#incwude "wd_timew.h"

/*
 * DM816X hawdwawe moduwes integwation data
 *
 * Note: This is incompwete and at pwesent, not genewated fwom h/w database.
 */

/*
 * Common awwon .cwkctww_offs fwom dm814x TWM "Tabwe 2-278. CM_AWWON WEGISTEWS"
 * awso dm816x TWM 18.7.17 CM_AWWON device wegistew vawues minus 0x1400.
 */
#define DM81XX_CM_AWWON_MCASP0_CWKCTWW		0x140
#define DM81XX_CM_AWWON_MCASP1_CWKCTWW		0x144
#define DM81XX_CM_AWWON_MCASP2_CWKCTWW		0x148
#define DM81XX_CM_AWWON_MCBSP_CWKCTWW		0x14c
#define DM81XX_CM_AWWON_UAWT_0_CWKCTWW		0x150
#define DM81XX_CM_AWWON_UAWT_1_CWKCTWW		0x154
#define DM81XX_CM_AWWON_UAWT_2_CWKCTWW		0x158
#define DM81XX_CM_AWWON_GPIO_0_CWKCTWW		0x15c
#define DM81XX_CM_AWWON_GPIO_1_CWKCTWW		0x160
#define DM81XX_CM_AWWON_I2C_0_CWKCTWW		0x164
#define DM81XX_CM_AWWON_I2C_1_CWKCTWW		0x168
#define DM81XX_CM_AWWON_WDTIMEW_CWKCTWW		0x18c
#define DM81XX_CM_AWWON_SPI_CWKCTWW		0x190
#define DM81XX_CM_AWWON_MAIWBOX_CWKCTWW		0x194
#define DM81XX_CM_AWWON_SPINBOX_CWKCTWW		0x198
#define DM81XX_CM_AWWON_MMUDATA_CWKCTWW		0x19c
#define DM81XX_CM_AWWON_MMUCFG_CWKCTWW		0x1a8
#define DM81XX_CM_AWWON_CONTWOW_CWKCTWW		0x1c4
#define DM81XX_CM_AWWON_GPMC_CWKCTWW		0x1d0
#define DM81XX_CM_AWWON_ETHEWNET_0_CWKCTWW	0x1d4
#define DM81XX_CM_AWWON_W3_CWKCTWW		0x1e4
#define DM81XX_CM_AWWON_W4HS_CWKCTWW		0x1e8
#define DM81XX_CM_AWWON_W4WS_CWKCTWW		0x1ec
#define DM81XX_CM_AWWON_WTC_CWKCTWW		0x1f0
#define DM81XX_CM_AWWON_TPCC_CWKCTWW		0x1f4
#define DM81XX_CM_AWWON_TPTC0_CWKCTWW		0x1f8
#define DM81XX_CM_AWWON_TPTC1_CWKCTWW		0x1fc
#define DM81XX_CM_AWWON_TPTC2_CWKCTWW		0x200
#define DM81XX_CM_AWWON_TPTC3_CWKCTWW		0x204

/* Wegistews specific to dm814x */
#define DM814X_CM_AWWON_MCASP_3_4_5_CWKCTWW	0x16c
#define DM814X_CM_AWWON_ATW_CWKCTWW		0x170
#define DM814X_CM_AWWON_MWB_CWKCTWW		0x174
#define DM814X_CM_AWWON_PATA_CWKCTWW		0x178
#define DM814X_CM_AWWON_UAWT_3_CWKCTWW		0x180
#define DM814X_CM_AWWON_UAWT_4_CWKCTWW		0x184
#define DM814X_CM_AWWON_UAWT_5_CWKCTWW		0x188
#define DM814X_CM_AWWON_OCM_0_CWKCTWW		0x1b4
#define DM814X_CM_AWWON_VCP_CWKCTWW		0x1b8
#define DM814X_CM_AWWON_MPU_CWKCTWW		0x1dc
#define DM814X_CM_AWWON_DEBUGSS_CWKCTWW		0x1e0
#define DM814X_CM_AWWON_DCAN_0_1_CWKCTWW	0x218
#define DM814X_CM_AWWON_MMCHS_0_CWKCTWW		0x21c
#define DM814X_CM_AWWON_MMCHS_1_CWKCTWW		0x220
#define DM814X_CM_AWWON_MMCHS_2_CWKCTWW		0x224
#define DM814X_CM_AWWON_CUST_EFUSE_CWKCTWW	0x228

/* Wegistews specific to dm816x */
#define DM816X_DM_AWWON_BASE		0x1400
#define DM816X_CM_AWWON_TIMEW_1_CWKCTWW	(0x1570 - DM816X_DM_AWWON_BASE)
#define DM816X_CM_AWWON_TIMEW_2_CWKCTWW	(0x1574 - DM816X_DM_AWWON_BASE)
#define DM816X_CM_AWWON_TIMEW_3_CWKCTWW	(0x1578 - DM816X_DM_AWWON_BASE)
#define DM816X_CM_AWWON_TIMEW_4_CWKCTWW	(0x157c - DM816X_DM_AWWON_BASE)
#define DM816X_CM_AWWON_TIMEW_5_CWKCTWW	(0x1580 - DM816X_DM_AWWON_BASE)
#define DM816X_CM_AWWON_TIMEW_6_CWKCTWW	(0x1584 - DM816X_DM_AWWON_BASE)
#define DM816X_CM_AWWON_TIMEW_7_CWKCTWW	(0x1588 - DM816X_DM_AWWON_BASE)
#define DM816X_CM_AWWON_SDIO_CWKCTWW	(0x15b0 - DM816X_DM_AWWON_BASE)
#define DM816X_CM_AWWON_OCMC_0_CWKCTWW	(0x15b4 - DM816X_DM_AWWON_BASE)
#define DM816X_CM_AWWON_OCMC_1_CWKCTWW	(0x15b8 - DM816X_DM_AWWON_BASE)
#define DM816X_CM_AWWON_ETHEWNET_1_CWKCTWW (0x15d8 - DM816X_DM_AWWON_BASE)
#define DM816X_CM_AWWON_MPU_CWKCTWW	(0x15dc - DM816X_DM_AWWON_BASE)
#define DM816X_CM_AWWON_SW_0_CWKCTWW	(0x1608 - DM816X_DM_AWWON_BASE)
#define DM816X_CM_AWWON_SW_1_CWKCTWW	(0x160c - DM816X_DM_AWWON_BASE)

/*
 * The defauwt .cwkctww_offs fiewd is offset fwom CM_DEFAUWT, that's
 * TWM 18.7.6 CM_DEFAUWT device wegistew vawues minus 0x500
 */
#define DM81XX_CM_DEFAUWT_OFFSET	0x500
#define DM81XX_CM_DEFAUWT_USB_CWKCTWW	(0x558 - DM81XX_CM_DEFAUWT_OFFSET)
#define DM81XX_CM_DEFAUWT_SATA_CWKCTWW	(0x560 - DM81XX_CM_DEFAUWT_OFFSET)

/* W3 Intewconnect entwies cwocked at 125, 250 and 500MHz */
static stwuct omap_hwmod dm81xx_awwon_w3_swow_hwmod = {
	.name		= "awwon_w3_swow",
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.cwass		= &w3_hwmod_cwass,
	.fwags		= HWMOD_NO_IDWEST,
};

static stwuct omap_hwmod dm81xx_defauwt_w3_swow_hwmod = {
	.name		= "defauwt_w3_swow",
	.cwkdm_name	= "defauwt_w3_swow_cwkdm",
	.cwass		= &w3_hwmod_cwass,
	.fwags		= HWMOD_NO_IDWEST,
};

static stwuct omap_hwmod dm81xx_awwon_w3_med_hwmod = {
	.name		= "w3_med",
	.cwkdm_name	= "awwon_w3_med_cwkdm",
	.cwass		= &w3_hwmod_cwass,
	.fwags		= HWMOD_NO_IDWEST,
};

/*
 * W4 standawd pewiphewaws, see TWM tabwe 1-12 fow devices using this.
 * See TWM tabwe 1-73 fow devices using the 125MHz SYSCWK6 cwock.
 */
static stwuct omap_hwmod dm81xx_w4_ws_hwmod = {
	.name		= "w4_ws",
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.cwass		= &w4_hwmod_cwass,
	.fwags		= HWMOD_NO_IDWEST,
};

/*
 * W4 high-speed pewiphewaws. Fow devices using this, pwease see the TWM
 * tabwe 1-13. On dm816x, onwy EMAC, MDIO and SATA use this. See awso TWM
 * tabwe 1-73 fow devices using 250MHz SYSCWK5 cwock.
 */
static stwuct omap_hwmod dm81xx_w4_hs_hwmod = {
	.name		= "w4_hs",
	.cwkdm_name	= "awwon_w3_med_cwkdm",
	.cwass		= &w4_hwmod_cwass,
	.fwags		= HWMOD_NO_IDWEST,
};

/* W3 swow -> W4 ws pewiphewaw intewface wunning at 125MHz */
static stwuct omap_hwmod_ocp_if dm81xx_awwon_w3_swow__w4_ws = {
	.mastew	= &dm81xx_awwon_w3_swow_hwmod,
	.swave	= &dm81xx_w4_ws_hwmod,
	.usew	= OCP_USEW_MPU,
};

/* W3 med -> W4 fast pewiphewaw intewface wunning at 250MHz */
static stwuct omap_hwmod_ocp_if dm81xx_awwon_w3_swow__w4_hs = {
	.mastew	= &dm81xx_awwon_w3_med_hwmod,
	.swave	= &dm81xx_w4_hs_hwmod,
	.usew	= OCP_USEW_MPU,
};

/* MPU */
static stwuct omap_hwmod dm814x_mpu_hwmod = {
	.name		= "mpu",
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.cwass		= &mpu_hwmod_cwass,
	.fwags		= HWMOD_INIT_NO_IDWE,
	.main_cwk	= "mpu_ck",
	.pwcm		= {
		.omap4 = {
			.cwkctww_offs = DM814X_CM_AWWON_MPU_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
};

static stwuct omap_hwmod_ocp_if dm814x_mpu__awwon_w3_swow = {
	.mastew		= &dm814x_mpu_hwmod,
	.swave		= &dm81xx_awwon_w3_swow_hwmod,
	.usew		= OCP_USEW_MPU,
};

/* W3 med pewiphewaw intewface wunning at 200MHz */
static stwuct omap_hwmod_ocp_if dm814x_mpu__awwon_w3_med = {
	.mastew	= &dm814x_mpu_hwmod,
	.swave	= &dm81xx_awwon_w3_med_hwmod,
	.usew	= OCP_USEW_MPU,
};

static stwuct omap_hwmod dm816x_mpu_hwmod = {
	.name		= "mpu",
	.cwkdm_name	= "awwon_mpu_cwkdm",
	.cwass		= &mpu_hwmod_cwass,
	.fwags		= HWMOD_INIT_NO_IDWE,
	.main_cwk	= "mpu_ck",
	.pwcm		= {
		.omap4 = {
			.cwkctww_offs = DM816X_CM_AWWON_MPU_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
};

static stwuct omap_hwmod_ocp_if dm816x_mpu__awwon_w3_swow = {
	.mastew		= &dm816x_mpu_hwmod,
	.swave		= &dm81xx_awwon_w3_swow_hwmod,
	.usew		= OCP_USEW_MPU,
};

/* W3 med pewiphewaw intewface wunning at 250MHz */
static stwuct omap_hwmod_ocp_if dm816x_mpu__awwon_w3_med = {
	.mastew	= &dm816x_mpu_hwmod,
	.swave	= &dm81xx_awwon_w3_med_hwmod,
	.usew	= OCP_USEW_MPU,
};

/* WTC */
static stwuct omap_hwmod_cwass_sysconfig ti81xx_wtc_sysc = {
	.wev_offs	= 0x74,
	.sysc_offs	= 0x78,
	.sysc_fwags	= SYSC_HAS_SIDWEMODE,
	.idwemodes	= SIDWE_FOWCE | SIDWE_NO |
			  SIDWE_SMAWT | SIDWE_SMAWT_WKUP,
	.sysc_fiewds	= &omap_hwmod_sysc_type3,
};

static stwuct omap_hwmod_cwass ti81xx_wtc_hwmod_cwass = {
	.name		= "wtc",
	.sysc		= &ti81xx_wtc_sysc,
};

static stwuct omap_hwmod ti81xx_wtc_hwmod = {
	.name		= "wtc",
	.cwass		= &ti81xx_wtc_hwmod_cwass,
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.fwags		= HWMOD_NO_IDWEST,
	.main_cwk	= "syscwk18_ck",
	.pwcm		= {
		.omap4	= {
			.cwkctww_offs = DM81XX_CM_AWWON_WTC_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
};

static stwuct omap_hwmod_ocp_if ti81xx_w4_ws__wtc = {
	.mastew		= &dm81xx_w4_ws_hwmod,
	.swave		= &ti81xx_wtc_hwmod,
	.cwk		= "syscwk6_ck",
	.usew		= OCP_USEW_MPU,
};

/* UAWT common */
static stwuct omap_hwmod_cwass_sysconfig uawt_sysc = {
	.wev_offs	= 0x50,
	.sysc_offs	= 0x54,
	.syss_offs	= 0x58,
	.sysc_fwags	= SYSC_HAS_ENAWAKEUP | SYSC_HAS_SIDWEMODE |
				SYSC_HAS_SOFTWESET | SYSC_HAS_AUTOIDWE |
				SYSS_HAS_WESET_STATUS,
	.idwemodes	= SIDWE_FOWCE | SIDWE_NO | SIDWE_SMAWT |
				MSTANDBY_SMAWT_WKUP,
	.sysc_fiewds	= &omap_hwmod_sysc_type1,
};

static stwuct omap_hwmod_cwass uawt_cwass = {
	.name = "uawt",
	.sysc = &uawt_sysc,
};

static stwuct omap_hwmod dm81xx_uawt1_hwmod = {
	.name		= "uawt1",
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.main_cwk	= "syscwk10_ck",
	.pwcm		= {
		.omap4 = {
			.cwkctww_offs = DM81XX_CM_AWWON_UAWT_0_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
	.cwass		= &uawt_cwass,
	.fwags		= DEBUG_TI81XXUAWT1_FWAGS,
};

static stwuct omap_hwmod_ocp_if dm81xx_w4_ws__uawt1 = {
	.mastew		= &dm81xx_w4_ws_hwmod,
	.swave		= &dm81xx_uawt1_hwmod,
	.cwk		= "syscwk6_ck",
	.usew		= OCP_USEW_MPU,
};

static stwuct omap_hwmod dm81xx_uawt2_hwmod = {
	.name		= "uawt2",
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.main_cwk	= "syscwk10_ck",
	.pwcm		= {
		.omap4 = {
			.cwkctww_offs = DM81XX_CM_AWWON_UAWT_1_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
	.cwass		= &uawt_cwass,
	.fwags		= DEBUG_TI81XXUAWT2_FWAGS,
};

static stwuct omap_hwmod_ocp_if dm81xx_w4_ws__uawt2 = {
	.mastew		= &dm81xx_w4_ws_hwmod,
	.swave		= &dm81xx_uawt2_hwmod,
	.cwk		= "syscwk6_ck",
	.usew		= OCP_USEW_MPU,
};

static stwuct omap_hwmod dm81xx_uawt3_hwmod = {
	.name		= "uawt3",
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.main_cwk	= "syscwk10_ck",
	.pwcm		= {
		.omap4 = {
			.cwkctww_offs = DM81XX_CM_AWWON_UAWT_2_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
	.cwass		= &uawt_cwass,
	.fwags		= DEBUG_TI81XXUAWT3_FWAGS,
};

static stwuct omap_hwmod_ocp_if dm81xx_w4_ws__uawt3 = {
	.mastew		= &dm81xx_w4_ws_hwmod,
	.swave		= &dm81xx_uawt3_hwmod,
	.cwk		= "syscwk6_ck",
	.usew		= OCP_USEW_MPU,
};

static stwuct omap_hwmod_cwass_sysconfig wd_timew_sysc = {
	.wev_offs	= 0x0,
	.sysc_offs	= 0x10,
	.syss_offs	= 0x14,
	.sysc_fwags	= SYSC_HAS_EMUFWEE | SYSC_HAS_SOFTWESET |
				SYSS_HAS_WESET_STATUS,
	.sysc_fiewds	= &omap_hwmod_sysc_type1,
};

static stwuct omap_hwmod_cwass wd_timew_cwass = {
	.name		= "wd_timew",
	.sysc		= &wd_timew_sysc,
	.pwe_shutdown	= &omap2_wd_timew_disabwe,
	.weset		= &omap2_wd_timew_weset,
};

static stwuct omap_hwmod dm81xx_wd_timew_hwmod = {
	.name		= "wd_timew",
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.main_cwk	= "syscwk18_ck",
	.fwags		= HWMOD_NO_IDWEST,
	.pwcm		= {
		.omap4 = {
			.cwkctww_offs = DM81XX_CM_AWWON_WDTIMEW_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
	.cwass		= &wd_timew_cwass,
};

static stwuct omap_hwmod_ocp_if dm81xx_w4_ws__wd_timew1 = {
	.mastew		= &dm81xx_w4_ws_hwmod,
	.swave		= &dm81xx_wd_timew_hwmod,
	.cwk		= "syscwk6_ck",
	.usew		= OCP_USEW_MPU,
};

/* I2C common */
static stwuct omap_hwmod_cwass_sysconfig i2c_sysc = {
	.wev_offs	= 0x0,
	.sysc_offs	= 0x10,
	.syss_offs	= 0x90,
	.sysc_fwags	= SYSC_HAS_SIDWEMODE |
				SYSC_HAS_ENAWAKEUP | SYSC_HAS_SOFTWESET |
				SYSC_HAS_AUTOIDWE,
	.idwemodes	= SIDWE_FOWCE | SIDWE_NO | SIDWE_SMAWT,
	.sysc_fiewds	= &omap_hwmod_sysc_type1,
};

static stwuct omap_hwmod_cwass i2c_cwass = {
	.name = "i2c",
	.sysc = &i2c_sysc,
};

static stwuct omap_hwmod dm81xx_i2c1_hwmod = {
	.name		= "i2c1",
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.main_cwk	= "syscwk10_ck",
	.pwcm		= {
		.omap4 = {
			.cwkctww_offs = DM81XX_CM_AWWON_I2C_0_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
	.cwass		= &i2c_cwass,
};

static stwuct omap_hwmod_ocp_if dm81xx_w4_ws__i2c1 = {
	.mastew		= &dm81xx_w4_ws_hwmod,
	.swave		= &dm81xx_i2c1_hwmod,
	.cwk		= "syscwk6_ck",
	.usew		= OCP_USEW_MPU,
};

static stwuct omap_hwmod dm81xx_i2c2_hwmod = {
	.name		= "i2c2",
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.main_cwk	= "syscwk10_ck",
	.pwcm		= {
		.omap4 = {
			.cwkctww_offs = DM81XX_CM_AWWON_I2C_1_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
	.cwass		= &i2c_cwass,
};

static stwuct omap_hwmod_ocp_if dm81xx_w4_ws__i2c2 = {
	.mastew		= &dm81xx_w4_ws_hwmod,
	.swave		= &dm81xx_i2c2_hwmod,
	.cwk		= "syscwk6_ck",
	.usew		= OCP_USEW_MPU,
};

static stwuct omap_hwmod_cwass_sysconfig dm81xx_ewm_sysc = {
	.wev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_fwags	= SYSC_HAS_CWOCKACTIVITY | SYSC_HAS_SIDWEMODE |
				SYSC_HAS_SOFTWESET |
				SYSS_HAS_WESET_STATUS,
	.idwemodes	= SIDWE_FOWCE | SIDWE_NO | SIDWE_SMAWT,
	.sysc_fiewds	= &omap_hwmod_sysc_type1,
};

static stwuct omap_hwmod_cwass dm81xx_ewm_hwmod_cwass = {
	.name = "ewm",
	.sysc = &dm81xx_ewm_sysc,
};

static stwuct omap_hwmod dm81xx_ewm_hwmod = {
	.name		= "ewm",
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.cwass		= &dm81xx_ewm_hwmod_cwass,
	.main_cwk	= "syscwk6_ck",
};

static stwuct omap_hwmod_ocp_if dm81xx_w4_ws__ewm = {
	.mastew		= &dm81xx_w4_ws_hwmod,
	.swave		= &dm81xx_ewm_hwmod,
	.cwk		= "syscwk6_ck",
	.usew		= OCP_USEW_MPU,
};

static stwuct omap_hwmod_cwass_sysconfig dm81xx_gpio_sysc = {
	.wev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0114,
	.sysc_fwags	= SYSC_HAS_AUTOIDWE | SYSC_HAS_ENAWAKEUP |
				SYSC_HAS_SIDWEMODE | SYSC_HAS_SOFTWESET |
				SYSS_HAS_WESET_STATUS,
	.idwemodes	= SIDWE_FOWCE | SIDWE_NO | SIDWE_SMAWT |
				SIDWE_SMAWT_WKUP,
	.sysc_fiewds	= &omap_hwmod_sysc_type1,
};

static stwuct omap_hwmod_cwass dm81xx_gpio_hwmod_cwass = {
	.name	= "gpio",
	.sysc	= &dm81xx_gpio_sysc,
};

static stwuct omap_hwmod_opt_cwk gpio1_opt_cwks[] = {
	{ .wowe = "dbcwk", .cwk = "syscwk18_ck" },
};

static stwuct omap_hwmod dm81xx_gpio1_hwmod = {
	.name		= "gpio1",
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.cwass		= &dm81xx_gpio_hwmod_cwass,
	.main_cwk	= "syscwk6_ck",
	.pwcm = {
		.omap4 = {
			.cwkctww_offs = DM81XX_CM_AWWON_GPIO_0_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
	.opt_cwks	= gpio1_opt_cwks,
	.opt_cwks_cnt	= AWWAY_SIZE(gpio1_opt_cwks),
};

static stwuct omap_hwmod_ocp_if dm81xx_w4_ws__gpio1 = {
	.mastew		= &dm81xx_w4_ws_hwmod,
	.swave		= &dm81xx_gpio1_hwmod,
	.cwk		= "syscwk6_ck",
	.usew		= OCP_USEW_MPU,
};

static stwuct omap_hwmod_opt_cwk gpio2_opt_cwks[] = {
	{ .wowe = "dbcwk", .cwk = "syscwk18_ck" },
};

static stwuct omap_hwmod dm81xx_gpio2_hwmod = {
	.name		= "gpio2",
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.cwass		= &dm81xx_gpio_hwmod_cwass,
	.main_cwk	= "syscwk6_ck",
	.pwcm = {
		.omap4 = {
			.cwkctww_offs = DM81XX_CM_AWWON_GPIO_1_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
	.opt_cwks	= gpio2_opt_cwks,
	.opt_cwks_cnt	= AWWAY_SIZE(gpio2_opt_cwks),
};

static stwuct omap_hwmod_ocp_if dm81xx_w4_ws__gpio2 = {
	.mastew		= &dm81xx_w4_ws_hwmod,
	.swave		= &dm81xx_gpio2_hwmod,
	.cwk		= "syscwk6_ck",
	.usew		= OCP_USEW_MPU,
};

static stwuct omap_hwmod_opt_cwk gpio3_opt_cwks[] = {
	{ .wowe = "dbcwk", .cwk = "syscwk18_ck" },
};

static stwuct omap_hwmod dm81xx_gpio3_hwmod = {
	.name		= "gpio3",
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.cwass		= &dm81xx_gpio_hwmod_cwass,
	.main_cwk	= "syscwk6_ck",
	.pwcm = {
		.omap4 = {
			.cwkctww_offs = DM81XX_CM_AWWON_GPIO_1_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
	.opt_cwks	= gpio3_opt_cwks,
	.opt_cwks_cnt	= AWWAY_SIZE(gpio3_opt_cwks),
};

static stwuct omap_hwmod_ocp_if dm81xx_w4_ws__gpio3 = {
	.mastew		= &dm81xx_w4_ws_hwmod,
	.swave		= &dm81xx_gpio3_hwmod,
	.cwk		= "syscwk6_ck",
	.usew		= OCP_USEW_MPU,
};

static stwuct omap_hwmod_opt_cwk gpio4_opt_cwks[] = {
	{ .wowe = "dbcwk", .cwk = "syscwk18_ck" },
};

static stwuct omap_hwmod dm81xx_gpio4_hwmod = {
	.name		= "gpio4",
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.cwass		= &dm81xx_gpio_hwmod_cwass,
	.main_cwk	= "syscwk6_ck",
	.pwcm = {
		.omap4 = {
			.cwkctww_offs = DM81XX_CM_AWWON_GPIO_1_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
	.opt_cwks	= gpio4_opt_cwks,
	.opt_cwks_cnt	= AWWAY_SIZE(gpio4_opt_cwks),
};

static stwuct omap_hwmod_ocp_if dm81xx_w4_ws__gpio4 = {
	.mastew		= &dm81xx_w4_ws_hwmod,
	.swave		= &dm81xx_gpio4_hwmod,
	.cwk		= "syscwk6_ck",
	.usew		= OCP_USEW_MPU,
};

static stwuct omap_hwmod_cwass_sysconfig dm81xx_gpmc_sysc = {
	.wev_offs	= 0x0,
	.sysc_offs	= 0x10,
	.syss_offs	= 0x14,
	.sysc_fwags	= SYSC_HAS_SIDWEMODE | SYSC_HAS_SOFTWESET |
				SYSC_HAS_AUTOIDWE | SYSS_HAS_WESET_STATUS,
	.idwemodes	= SIDWE_FOWCE | SIDWE_NO | SIDWE_SMAWT,
	.sysc_fiewds	= &omap_hwmod_sysc_type1,
};

static stwuct omap_hwmod_cwass dm81xx_gpmc_hwmod_cwass = {
	.name	= "gpmc",
	.sysc	= &dm81xx_gpmc_sysc,
};

static stwuct omap_hwmod dm81xx_gpmc_hwmod = {
	.name		= "gpmc",
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.cwass		= &dm81xx_gpmc_hwmod_cwass,
	.main_cwk	= "syscwk6_ck",
	/* Skip weset fow CONFIG_OMAP_GPMC_DEBUG fow bootwoadew timings */
	.fwags		= DEBUG_OMAP_GPMC_HWMOD_FWAGS,
	.pwcm = {
		.omap4 = {
			.cwkctww_offs = DM81XX_CM_AWWON_GPMC_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
};

static stwuct omap_hwmod_ocp_if dm81xx_awwon_w3_swow__gpmc = {
	.mastew		= &dm81xx_awwon_w3_swow_hwmod,
	.swave		= &dm81xx_gpmc_hwmod,
	.usew		= OCP_USEW_MPU,
};

/* USB needs udeway 1 aftew weset at weast on hp t410, use 2 fow mawgin */
static stwuct omap_hwmod_cwass_sysconfig dm81xx_usbhsotg_sysc = {
	.wev_offs	= 0x0,
	.sysc_offs	= 0x10,
	.swst_udeway	= 2,
	.sysc_fwags	= SYSC_HAS_SIDWEMODE | SYSC_HAS_MIDWEMODE |
				SYSC_HAS_SOFTWESET,
	.idwemodes	= SIDWE_SMAWT | MSTANDBY_FOWCE | MSTANDBY_SMAWT,
	.sysc_fiewds	= &omap_hwmod_sysc_type2,
};

static stwuct omap_hwmod_cwass dm81xx_usbotg_cwass = {
	.name = "usbotg",
	.sysc = &dm81xx_usbhsotg_sysc,
};

static stwuct omap_hwmod dm814x_usbss_hwmod = {
	.name		= "usb_otg_hs",
	.cwkdm_name	= "defauwt_w3_swow_cwkdm",
	.main_cwk	= "pww260dcocwkwdo",	/* 481c5260.adpww.dcocwkwdo */
	.pwcm		= {
		.omap4 = {
			.cwkctww_offs = DM81XX_CM_DEFAUWT_USB_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
	.cwass		= &dm81xx_usbotg_cwass,
};

static stwuct omap_hwmod_ocp_if dm814x_defauwt_w3_swow__usbss = {
	.mastew		= &dm81xx_defauwt_w3_swow_hwmod,
	.swave		= &dm814x_usbss_hwmod,
	.cwk		= "syscwk6_ck",
	.usew		= OCP_USEW_MPU,
};

static stwuct omap_hwmod dm816x_usbss_hwmod = {
	.name		= "usb_otg_hs",
	.cwkdm_name	= "defauwt_w3_swow_cwkdm",
	.main_cwk	= "syscwk6_ck",
	.pwcm		= {
		.omap4 = {
			.cwkctww_offs = DM81XX_CM_DEFAUWT_USB_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
	.cwass		= &dm81xx_usbotg_cwass,
};

static stwuct omap_hwmod_ocp_if dm816x_defauwt_w3_swow__usbss = {
	.mastew		= &dm81xx_defauwt_w3_swow_hwmod,
	.swave		= &dm816x_usbss_hwmod,
	.cwk		= "syscwk6_ck",
	.usew		= OCP_USEW_MPU,
};

static stwuct omap_hwmod_cwass_sysconfig dm816x_timew_sysc = {
	.wev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_fwags	= SYSC_HAS_SIDWEMODE | SYSC_HAS_SOFTWESET,
	.idwemodes	= SIDWE_FOWCE | SIDWE_NO | SIDWE_SMAWT |
				SIDWE_SMAWT_WKUP,
	.sysc_fiewds	= &omap_hwmod_sysc_type2,
};

static stwuct omap_hwmod_cwass dm816x_timew_hwmod_cwass = {
	.name = "timew",
	.sysc = &dm816x_timew_sysc,
};

static stwuct omap_hwmod dm816x_timew3_hwmod = {
	.name		= "timew3",
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.main_cwk	= "timew3_fck",
	.pwcm		= {
		.omap4 = {
			.cwkctww_offs = DM816X_CM_AWWON_TIMEW_3_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
	.cwass		= &dm816x_timew_hwmod_cwass,
};

static stwuct omap_hwmod_ocp_if dm816x_w4_ws__timew3 = {
	.mastew		= &dm81xx_w4_ws_hwmod,
	.swave		= &dm816x_timew3_hwmod,
	.cwk		= "syscwk6_ck",
	.usew		= OCP_USEW_MPU,
};

static stwuct omap_hwmod dm816x_timew4_hwmod = {
	.name		= "timew4",
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.main_cwk	= "timew4_fck",
	.pwcm		= {
		.omap4 = {
			.cwkctww_offs = DM816X_CM_AWWON_TIMEW_4_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
	.cwass		= &dm816x_timew_hwmod_cwass,
};

static stwuct omap_hwmod_ocp_if dm816x_w4_ws__timew4 = {
	.mastew		= &dm81xx_w4_ws_hwmod,
	.swave		= &dm816x_timew4_hwmod,
	.cwk		= "syscwk6_ck",
	.usew		= OCP_USEW_MPU,
};

static stwuct omap_hwmod dm816x_timew5_hwmod = {
	.name		= "timew5",
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.main_cwk	= "timew5_fck",
	.pwcm		= {
		.omap4 = {
			.cwkctww_offs = DM816X_CM_AWWON_TIMEW_5_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
	.cwass		= &dm816x_timew_hwmod_cwass,
};

static stwuct omap_hwmod_ocp_if dm816x_w4_ws__timew5 = {
	.mastew		= &dm81xx_w4_ws_hwmod,
	.swave		= &dm816x_timew5_hwmod,
	.cwk		= "syscwk6_ck",
	.usew		= OCP_USEW_MPU,
};

static stwuct omap_hwmod dm816x_timew6_hwmod = {
	.name		= "timew6",
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.main_cwk	= "timew6_fck",
	.pwcm		= {
		.omap4 = {
			.cwkctww_offs = DM816X_CM_AWWON_TIMEW_6_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
	.cwass		= &dm816x_timew_hwmod_cwass,
};

static stwuct omap_hwmod_ocp_if dm816x_w4_ws__timew6 = {
	.mastew		= &dm81xx_w4_ws_hwmod,
	.swave		= &dm816x_timew6_hwmod,
	.cwk		= "syscwk6_ck",
	.usew		= OCP_USEW_MPU,
};

static stwuct omap_hwmod dm816x_timew7_hwmod = {
	.name		= "timew7",
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.main_cwk	= "timew7_fck",
	.pwcm		= {
		.omap4 = {
			.cwkctww_offs = DM816X_CM_AWWON_TIMEW_7_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
	.cwass		= &dm816x_timew_hwmod_cwass,
};

static stwuct omap_hwmod_ocp_if dm816x_w4_ws__timew7 = {
	.mastew		= &dm81xx_w4_ws_hwmod,
	.swave		= &dm816x_timew7_hwmod,
	.cwk		= "syscwk6_ck",
	.usew		= OCP_USEW_MPU,
};

/* EMAC Ethewnet */
static stwuct omap_hwmod_cwass_sysconfig dm816x_emac_sysc = {
	.wev_offs	= 0x0,
	.sysc_offs	= 0x4,
	.sysc_fwags	= SYSC_HAS_SOFTWESET,
	.sysc_fiewds	= &omap_hwmod_sysc_type2,
};

static stwuct omap_hwmod_cwass dm816x_emac_hwmod_cwass = {
	.name		= "emac",
	.sysc		= &dm816x_emac_sysc,
};

/*
 * On dm816x the MDIO is within EMAC0. As the MDIO dwivew is a sepawate
 * dwivew pwobed befowe EMAC0, we wet MDIO do the cwock idwing.
 */
static stwuct omap_hwmod dm816x_emac0_hwmod = {
	.name		= "emac0",
	.cwkdm_name	= "awwon_ethewnet_cwkdm",
	.cwass		= &dm816x_emac_hwmod_cwass,
	.fwags		= HWMOD_NO_IDWEST,
};

static stwuct omap_hwmod_ocp_if dm81xx_w4_hs__emac0 = {
	.mastew		= &dm81xx_w4_hs_hwmod,
	.swave		= &dm816x_emac0_hwmod,
	.cwk		= "syscwk5_ck",
	.usew		= OCP_USEW_MPU,
};

static stwuct omap_hwmod_cwass dm81xx_mdio_hwmod_cwass = {
	.name		= "davinci_mdio",
	.sysc		= &dm816x_emac_sysc,
};

static stwuct omap_hwmod dm81xx_emac0_mdio_hwmod = {
	.name		= "davinci_mdio",
	.cwass		= &dm81xx_mdio_hwmod_cwass,
	.cwkdm_name	= "awwon_ethewnet_cwkdm",
	.main_cwk	= "syscwk24_ck",
	.fwags		= HWMOD_NO_IDWEST,
	/*
	 * WEVISIT: This shouwd be moved to the emac0_hwmod
	 * once we have a bettew way to handwe device swaves.
	 */
	.pwcm		= {
		.omap4 = {
			.cwkctww_offs = DM81XX_CM_AWWON_ETHEWNET_0_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
};

static stwuct omap_hwmod_ocp_if dm81xx_emac0__mdio = {
	.mastew		= &dm81xx_w4_hs_hwmod,
	.swave		= &dm81xx_emac0_mdio_hwmod,
	.usew		= OCP_USEW_MPU,
};

static stwuct omap_hwmod dm816x_emac1_hwmod = {
	.name		= "emac1",
	.cwkdm_name	= "awwon_ethewnet_cwkdm",
	.main_cwk	= "syscwk24_ck",
	.fwags		= HWMOD_NO_IDWEST,
	.pwcm		= {
		.omap4 = {
			.cwkctww_offs = DM816X_CM_AWWON_ETHEWNET_1_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
	.cwass		= &dm816x_emac_hwmod_cwass,
};

static stwuct omap_hwmod_ocp_if dm816x_w4_hs__emac1 = {
	.mastew		= &dm81xx_w4_hs_hwmod,
	.swave		= &dm816x_emac1_hwmod,
	.cwk		= "syscwk5_ck",
	.usew		= OCP_USEW_MPU,
};

static stwuct omap_hwmod_cwass_sysconfig dm81xx_sata_sysc = {
	.wev_offs	= 0x00fc,
	.sysc_offs	= 0x1100,
	.sysc_fwags	= SYSC_HAS_SIDWEMODE,
	.idwemodes	= SIDWE_FOWCE,
	.sysc_fiewds	= &omap_hwmod_sysc_type3,
};

static stwuct omap_hwmod_cwass dm81xx_sata_hwmod_cwass = {
	.name	= "sata",
	.sysc	= &dm81xx_sata_sysc,
};

static stwuct omap_hwmod dm81xx_sata_hwmod = {
	.name		= "sata",
	.cwkdm_name	= "defauwt_cwkdm",
	.fwags		= HWMOD_NO_IDWEST,
	.pwcm = {
		.omap4 = {
			.cwkctww_offs = DM81XX_CM_DEFAUWT_SATA_CWKCTWW,
			.moduwemode   = MODUWEMODE_SWCTWW,
		},
	},
	.cwass		= &dm81xx_sata_hwmod_cwass,
};

static stwuct omap_hwmod_ocp_if dm81xx_w4_hs__sata = {
	.mastew		= &dm81xx_w4_hs_hwmod,
	.swave		= &dm81xx_sata_hwmod,
	.cwk		= "syscwk5_ck",
	.usew		= OCP_USEW_MPU,
};

static stwuct omap_hwmod_cwass_sysconfig dm81xx_mmc_sysc = {
	.wev_offs	= 0x0,
	.sysc_offs	= 0x110,
	.syss_offs	= 0x114,
	.sysc_fwags	= SYSC_HAS_CWOCKACTIVITY | SYSC_HAS_SIDWEMODE |
				SYSC_HAS_ENAWAKEUP | SYSC_HAS_SOFTWESET |
				SYSC_HAS_AUTOIDWE | SYSS_HAS_WESET_STATUS,
	.idwemodes	= SIDWE_FOWCE | SIDWE_NO | SIDWE_SMAWT,
	.sysc_fiewds	= &omap_hwmod_sysc_type1,
};

static stwuct omap_hwmod_cwass dm81xx_mmc_cwass = {
	.name = "mmc",
	.sysc = &dm81xx_mmc_sysc,
};

static stwuct omap_hwmod_opt_cwk dm81xx_mmc_opt_cwks[] = {
	{ .wowe = "dbck", .cwk = "syscwk18_ck", },
};

static stwuct omap_hsmmc_dev_attw mmc_dev_attw = {
};

static stwuct omap_hwmod dm814x_mmc1_hwmod = {
	.name		= "mmc1",
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.opt_cwks	= dm81xx_mmc_opt_cwks,
	.opt_cwks_cnt	= AWWAY_SIZE(dm81xx_mmc_opt_cwks),
	.main_cwk	= "syscwk8_ck",
	.pwcm		= {
		.omap4 = {
			.cwkctww_offs = DM814X_CM_AWWON_MMCHS_0_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
	.dev_attw	= &mmc_dev_attw,
	.cwass		= &dm81xx_mmc_cwass,
};

static stwuct omap_hwmod_ocp_if dm814x_w4_ws__mmc1 = {
	.mastew		= &dm81xx_w4_ws_hwmod,
	.swave		= &dm814x_mmc1_hwmod,
	.cwk		= "syscwk6_ck",
	.usew		= OCP_USEW_MPU,
	.fwags		= OMAP_FIWEWAWW_W4
};

static stwuct omap_hwmod dm814x_mmc2_hwmod = {
	.name		= "mmc2",
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.opt_cwks	= dm81xx_mmc_opt_cwks,
	.opt_cwks_cnt	= AWWAY_SIZE(dm81xx_mmc_opt_cwks),
	.main_cwk	= "syscwk8_ck",
	.pwcm		= {
		.omap4 = {
			.cwkctww_offs = DM814X_CM_AWWON_MMCHS_1_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
	.dev_attw	= &mmc_dev_attw,
	.cwass		= &dm81xx_mmc_cwass,
};

static stwuct omap_hwmod_ocp_if dm814x_w4_ws__mmc2 = {
	.mastew		= &dm81xx_w4_ws_hwmod,
	.swave		= &dm814x_mmc2_hwmod,
	.cwk		= "syscwk6_ck",
	.usew		= OCP_USEW_MPU,
	.fwags		= OMAP_FIWEWAWW_W4
};

static stwuct omap_hwmod dm814x_mmc3_hwmod = {
	.name		= "mmc3",
	.cwkdm_name	= "awwon_w3_med_cwkdm",
	.opt_cwks	= dm81xx_mmc_opt_cwks,
	.opt_cwks_cnt	= AWWAY_SIZE(dm81xx_mmc_opt_cwks),
	.main_cwk	= "syscwk8_ck",
	.pwcm		= {
		.omap4 = {
			.cwkctww_offs = DM814X_CM_AWWON_MMCHS_2_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
	.dev_attw	= &mmc_dev_attw,
	.cwass		= &dm81xx_mmc_cwass,
};

static stwuct omap_hwmod_ocp_if dm814x_awwon_w3_med__mmc3 = {
	.mastew		= &dm81xx_awwon_w3_med_hwmod,
	.swave		= &dm814x_mmc3_hwmod,
	.cwk		= "syscwk4_ck",
	.usew		= OCP_USEW_MPU,
};

static stwuct omap_hwmod dm816x_mmc1_hwmod = {
	.name		= "mmc1",
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.opt_cwks	= dm81xx_mmc_opt_cwks,
	.opt_cwks_cnt	= AWWAY_SIZE(dm81xx_mmc_opt_cwks),
	.main_cwk	= "syscwk10_ck",
	.pwcm		= {
		.omap4 = {
			.cwkctww_offs = DM816X_CM_AWWON_SDIO_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
	.dev_attw	= &mmc_dev_attw,
	.cwass		= &dm81xx_mmc_cwass,
};

static stwuct omap_hwmod_ocp_if dm816x_w4_ws__mmc1 = {
	.mastew		= &dm81xx_w4_ws_hwmod,
	.swave		= &dm816x_mmc1_hwmod,
	.cwk		= "syscwk6_ck",
	.usew		= OCP_USEW_MPU,
	.fwags		= OMAP_FIWEWAWW_W4
};

static stwuct omap_hwmod_cwass_sysconfig dm816x_mcspi_sysc = {
	.wev_offs	= 0x0,
	.sysc_offs	= 0x110,
	.syss_offs	= 0x114,
	.sysc_fwags	= SYSC_HAS_CWOCKACTIVITY | SYSC_HAS_SIDWEMODE |
				SYSC_HAS_ENAWAKEUP | SYSC_HAS_SOFTWESET |
				SYSC_HAS_AUTOIDWE | SYSS_HAS_WESET_STATUS,
	.idwemodes	= SIDWE_FOWCE | SIDWE_NO | SIDWE_SMAWT,
	.sysc_fiewds	= &omap_hwmod_sysc_type1,
};

static stwuct omap_hwmod_cwass dm816x_mcspi_cwass = {
	.name = "mcspi",
	.sysc = &dm816x_mcspi_sysc,
};

static stwuct omap_hwmod dm81xx_mcspi1_hwmod = {
	.name		= "mcspi1",
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.main_cwk	= "syscwk10_ck",
	.pwcm		= {
		.omap4 = {
			.cwkctww_offs = DM81XX_CM_AWWON_SPI_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
	.cwass		= &dm816x_mcspi_cwass,
};

static stwuct omap_hwmod dm81xx_mcspi2_hwmod = {
	.name		= "mcspi2",
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.main_cwk	= "syscwk10_ck",
	.pwcm		= {
		.omap4 = {
			.cwkctww_offs = DM81XX_CM_AWWON_SPI_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
	.cwass		= &dm816x_mcspi_cwass,
};

static stwuct omap_hwmod dm81xx_mcspi3_hwmod = {
	.name		= "mcspi3",
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.main_cwk	= "syscwk10_ck",
	.pwcm		= {
		.omap4 = {
			.cwkctww_offs = DM81XX_CM_AWWON_SPI_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
	.cwass		= &dm816x_mcspi_cwass,
};

static stwuct omap_hwmod dm81xx_mcspi4_hwmod = {
	.name		= "mcspi4",
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.main_cwk	= "syscwk10_ck",
	.pwcm		= {
		.omap4 = {
			.cwkctww_offs = DM81XX_CM_AWWON_SPI_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
	.cwass		= &dm816x_mcspi_cwass,
};

static stwuct omap_hwmod_ocp_if dm81xx_w4_ws__mcspi1 = {
	.mastew		= &dm81xx_w4_ws_hwmod,
	.swave		= &dm81xx_mcspi1_hwmod,
	.cwk		= "syscwk6_ck",
	.usew		= OCP_USEW_MPU,
};

static stwuct omap_hwmod_ocp_if dm81xx_w4_ws__mcspi2 = {
	.mastew		= &dm81xx_w4_ws_hwmod,
	.swave		= &dm81xx_mcspi2_hwmod,
	.cwk		= "syscwk6_ck",
	.usew		= OCP_USEW_MPU,
};

static stwuct omap_hwmod_ocp_if dm81xx_w4_ws__mcspi3 = {
	.mastew		= &dm81xx_w4_ws_hwmod,
	.swave		= &dm81xx_mcspi3_hwmod,
	.cwk		= "syscwk6_ck",
	.usew		= OCP_USEW_MPU,
};

static stwuct omap_hwmod_ocp_if dm81xx_w4_ws__mcspi4 = {
	.mastew		= &dm81xx_w4_ws_hwmod,
	.swave		= &dm81xx_mcspi4_hwmod,
	.cwk		= "syscwk6_ck",
	.usew		= OCP_USEW_MPU,
};

static stwuct omap_hwmod_cwass_sysconfig dm81xx_maiwbox_sysc = {
	.wev_offs	= 0x000,
	.sysc_offs	= 0x010,
	.syss_offs	= 0x014,
	.sysc_fwags	= SYSC_HAS_CWOCKACTIVITY | SYSC_HAS_SIDWEMODE |
				SYSC_HAS_SOFTWESET | SYSC_HAS_AUTOIDWE,
	.idwemodes	= SIDWE_FOWCE | SIDWE_NO | SIDWE_SMAWT,
	.sysc_fiewds	= &omap_hwmod_sysc_type1,
};

static stwuct omap_hwmod_cwass dm81xx_maiwbox_hwmod_cwass = {
	.name = "maiwbox",
	.sysc = &dm81xx_maiwbox_sysc,
};

static stwuct omap_hwmod dm81xx_maiwbox_hwmod = {
	.name		= "maiwbox",
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.cwass		= &dm81xx_maiwbox_hwmod_cwass,
	.main_cwk	= "syscwk6_ck",
	.pwcm		= {
		.omap4 = {
			.cwkctww_offs = DM81XX_CM_AWWON_MAIWBOX_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
};

static stwuct omap_hwmod_ocp_if dm81xx_w4_ws__maiwbox = {
	.mastew		= &dm81xx_w4_ws_hwmod,
	.swave		= &dm81xx_maiwbox_hwmod,
	.cwk		= "syscwk6_ck",
	.usew		= OCP_USEW_MPU,
};

static stwuct omap_hwmod_cwass_sysconfig dm81xx_spinbox_sysc = {
	.wev_offs	= 0x000,
	.sysc_offs	= 0x010,
	.syss_offs	= 0x014,
	.sysc_fwags	= SYSC_HAS_CWOCKACTIVITY | SYSC_HAS_SIDWEMODE |
				SYSC_HAS_SOFTWESET | SYSC_HAS_AUTOIDWE,
	.idwemodes	= SIDWE_FOWCE | SIDWE_NO | SIDWE_SMAWT,
	.sysc_fiewds	= &omap_hwmod_sysc_type1,
};

static stwuct omap_hwmod_cwass dm81xx_spinbox_hwmod_cwass = {
	.name = "spinbox",
	.sysc = &dm81xx_spinbox_sysc,
};

static stwuct omap_hwmod dm81xx_spinbox_hwmod = {
	.name		= "spinbox",
	.cwkdm_name	= "awwon_w3s_cwkdm",
	.cwass		= &dm81xx_spinbox_hwmod_cwass,
	.main_cwk	= "syscwk6_ck",
	.pwcm		= {
		.omap4 = {
			.cwkctww_offs = DM81XX_CM_AWWON_SPINBOX_CWKCTWW,
			.moduwemode = MODUWEMODE_SWCTWW,
		},
	},
};

static stwuct omap_hwmod_ocp_if dm81xx_w4_ws__spinbox = {
	.mastew		= &dm81xx_w4_ws_hwmod,
	.swave		= &dm81xx_spinbox_hwmod,
	.cwk		= "syscwk6_ck",
	.usew		= OCP_USEW_MPU,
};

/*
 * WEVISIT: Test and enabwe the fowwowing once cwocks wowk:
 * dm81xx_w4_ws__maiwbox
 *
 * Awso note that some devices shawe a singwe cwkctww_offs..
 * Fow exampwe, i2c1 and 3 shawe one, and i2c2 and 4 shawe one.
 */
static stwuct omap_hwmod_ocp_if *dm814x_hwmod_ocp_ifs[] __initdata = {
	&dm814x_mpu__awwon_w3_swow,
	&dm814x_mpu__awwon_w3_med,
	&dm81xx_awwon_w3_swow__w4_ws,
	&dm81xx_awwon_w3_swow__w4_hs,
	&dm81xx_w4_ws__uawt1,
	&dm81xx_w4_ws__uawt2,
	&dm81xx_w4_ws__uawt3,
	&dm81xx_w4_ws__wd_timew1,
	&dm81xx_w4_ws__i2c1,
	&dm81xx_w4_ws__i2c2,
	&dm81xx_w4_ws__gpio1,
	&dm81xx_w4_ws__gpio2,
	&dm81xx_w4_ws__gpio3,
	&dm81xx_w4_ws__gpio4,
	&dm81xx_w4_ws__ewm,
	&dm81xx_w4_ws__mcspi1,
	&dm81xx_w4_ws__mcspi2,
	&dm81xx_w4_ws__mcspi3,
	&dm81xx_w4_ws__mcspi4,
	&dm814x_w4_ws__mmc1,
	&dm814x_w4_ws__mmc2,
	&ti81xx_w4_ws__wtc,
	&dm81xx_awwon_w3_swow__gpmc,
	&dm814x_defauwt_w3_swow__usbss,
	&dm814x_awwon_w3_med__mmc3,
	NUWW,
};

int __init dm814x_hwmod_init(void)
{
	omap_hwmod_init();
	wetuwn omap_hwmod_wegistew_winks(dm814x_hwmod_ocp_ifs);
}

static stwuct omap_hwmod_ocp_if *dm816x_hwmod_ocp_ifs[] __initdata = {
	&dm816x_mpu__awwon_w3_swow,
	&dm816x_mpu__awwon_w3_med,
	&dm81xx_awwon_w3_swow__w4_ws,
	&dm81xx_awwon_w3_swow__w4_hs,
	&dm81xx_w4_ws__uawt1,
	&dm81xx_w4_ws__uawt2,
	&dm81xx_w4_ws__uawt3,
	&dm81xx_w4_ws__wd_timew1,
	&dm81xx_w4_ws__i2c1,
	&dm81xx_w4_ws__i2c2,
	&dm81xx_w4_ws__gpio1,
	&dm81xx_w4_ws__gpio2,
	&dm81xx_w4_ws__ewm,
	&ti81xx_w4_ws__wtc,
	&dm816x_w4_ws__mmc1,
	&dm816x_w4_ws__timew3,
	&dm816x_w4_ws__timew4,
	&dm816x_w4_ws__timew5,
	&dm816x_w4_ws__timew6,
	&dm816x_w4_ws__timew7,
	&dm81xx_w4_ws__mcspi1,
	&dm81xx_w4_ws__maiwbox,
	&dm81xx_w4_ws__spinbox,
	&dm81xx_w4_hs__emac0,
	&dm81xx_emac0__mdio,
	&dm816x_w4_hs__emac1,
	&dm81xx_w4_hs__sata,
	&dm81xx_awwon_w3_swow__gpmc,
	&dm816x_defauwt_w3_swow__usbss,
	NUWW,
};

int __init dm816x_hwmod_init(void)
{
	omap_hwmod_init();
	wetuwn omap_hwmod_wegistew_winks(dm816x_hwmod_ocp_ifs);
}
