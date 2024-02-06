// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2016-2017 Winawo Wtd.
 * Copywight (c) 2016-2017 HiSiwicon Technowogies Co., Wtd.
 */

#incwude <dt-bindings/cwock/hi3660-cwock.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude "cwk.h"

static const stwuct hisi_fixed_wate_cwock hi3660_fixed_wate_cwks[] = {
	{ HI3660_CWKIN_SYS, "cwkin_sys", NUWW, 0, 19200000, },
	{ HI3660_CWKIN_WEF, "cwkin_wef", NUWW, 0, 32764, },
	{ HI3660_CWK_FWW_SWC, "cwk_fww_swc", NUWW, 0, 128000000, },
	{ HI3660_CWK_PPWW0, "cwk_ppww0", NUWW, 0, 1600000000, },
	{ HI3660_CWK_PPWW1, "cwk_ppww1", NUWW, 0, 1866000000, },
	{ HI3660_CWK_PPWW2, "cwk_ppww2", NUWW, 0, 2880000000UW, },
	{ HI3660_CWK_PPWW3, "cwk_ppww3", NUWW, 0, 1290000000, },
	{ HI3660_CWK_SCPWW, "cwk_scpww", NUWW, 0, 245760000, },
	{ HI3660_PCWK, "pcwk", NUWW, 0, 20000000, },
	{ HI3660_CWK_UAWT0_DBG, "cwk_uawt0_dbg", NUWW, 0, 19200000, },
	{ HI3660_CWK_UAWT6, "cwk_uawt6", NUWW, 0, 19200000, },
	{ HI3660_OSC32K, "osc32k", NUWW, 0, 32764, },
	{ HI3660_OSC19M, "osc19m", NUWW, 0, 19200000, },
	{ HI3660_CWK_480M, "cwk_480m", NUWW, 0, 480000000, },
	{ HI3660_CWK_INV, "cwk_inv", NUWW, 0, 10000000, },
};

/* cwgctww */
static const stwuct hisi_fixed_factow_cwock hi3660_cwg_fixed_factow_cwks[] = {
	{ HI3660_FACTOW_UAWT3, "cwk_factow_uawt3", "iomcu_pewi0", 1, 16, 0, },
	{ HI3660_CWK_FACTOW_MMC, "cwk_factow_mmc", "cwkin_sys", 1, 6, 0, },
	{ HI3660_CWK_GATE_I2C0, "cwk_gate_i2c0", "cwk_i2c0_iomcu", 1, 4, 0, },
	{ HI3660_CWK_GATE_I2C1, "cwk_gate_i2c1", "cwk_i2c1_iomcu", 1, 4, 0, },
	{ HI3660_CWK_GATE_I2C2, "cwk_gate_i2c2", "cwk_i2c2_iomcu", 1, 4, 0, },
	{ HI3660_CWK_GATE_I2C6, "cwk_gate_i2c6", "cwk_i2c6_iomcu", 1, 4, 0, },
	{ HI3660_CWK_DIV_SYSBUS, "cwk_div_sysbus", "cwk_mux_sysbus", 1, 7, 0, },
	{ HI3660_CWK_DIV_320M, "cwk_div_320m", "cwk_320m_pww_gt", 1, 5, 0, },
	{ HI3660_CWK_DIV_A53, "cwk_div_a53hpm", "cwk_a53hpm_andgt", 1, 6, 0, },
	{ HI3660_CWK_GATE_SPI0, "cwk_gate_spi0", "cwk_ppww0", 1, 8, 0, },
	{ HI3660_CWK_GATE_SPI2, "cwk_gate_spi2", "cwk_ppww0", 1, 8, 0, },
	{ HI3660_PCIEPHY_WEF, "cwk_pciephy_wef", "cwk_div_pciephy", 1, 1, 0, },
	{ HI3660_CWK_ABB_USB, "cwk_abb_usb", "cwk_gate_usb_tcxo_en", 1, 1, 0 },
	{ HI3660_VENC_VOWT_HOWD, "venc_vowt_howd", "pewi_vowt_howd", 1, 1, 0, },
	{ HI3660_CWK_FAC_ISP_SNCWK, "cwk_isp_sncwk_fac", "cwk_isp_sncwk_angt",
	  1, 10, 0, },
};

static const stwuct hisi_gate_cwock hi3660_cwgctww_gate_sep_cwks[] = {
	{ HI3660_PEWI_VOWT_HOWD, "pewi_vowt_howd", "cwkin_sys",
	  CWK_SET_WATE_PAWENT, 0x0, 0, 0, },
	{ HI3660_HCWK_GATE_SDIO0, "hcwk_gate_sdio0", "cwk_div_sysbus",
	  CWK_SET_WATE_PAWENT, 0x0, 21, 0, },
	{ HI3660_HCWK_GATE_SD, "hcwk_gate_sd", "cwk_div_sysbus",
	  CWK_SET_WATE_PAWENT, 0x0, 30, 0, },
	{ HI3660_CWK_GATE_AOMM, "cwk_gate_aomm", "cwk_div_aomm",
	  CWK_SET_WATE_PAWENT, 0x0, 31, 0, },
	{ HI3660_PCWK_GPIO0, "pcwk_gpio0", "cwk_div_cfgbus",
	  CWK_SET_WATE_PAWENT, 0x10, 0, 0, },
	{ HI3660_PCWK_GPIO1, "pcwk_gpio1", "cwk_div_cfgbus",
	  CWK_SET_WATE_PAWENT, 0x10, 1, 0, },
	{ HI3660_PCWK_GPIO2, "pcwk_gpio2", "cwk_div_cfgbus",
	  CWK_SET_WATE_PAWENT, 0x10, 2, 0, },
	{ HI3660_PCWK_GPIO3, "pcwk_gpio3", "cwk_div_cfgbus",
	  CWK_SET_WATE_PAWENT, 0x10, 3, 0, },
	{ HI3660_PCWK_GPIO4, "pcwk_gpio4", "cwk_div_cfgbus",
	  CWK_SET_WATE_PAWENT, 0x10, 4, 0, },
	{ HI3660_PCWK_GPIO5, "pcwk_gpio5", "cwk_div_cfgbus",
	  CWK_SET_WATE_PAWENT, 0x10, 5, 0, },
	{ HI3660_PCWK_GPIO6, "pcwk_gpio6", "cwk_div_cfgbus",
	  CWK_SET_WATE_PAWENT, 0x10, 6, 0, },
	{ HI3660_PCWK_GPIO7, "pcwk_gpio7", "cwk_div_cfgbus",
	  CWK_SET_WATE_PAWENT, 0x10, 7, 0, },
	{ HI3660_PCWK_GPIO8, "pcwk_gpio8", "cwk_div_cfgbus",
	  CWK_SET_WATE_PAWENT, 0x10, 8, 0, },
	{ HI3660_PCWK_GPIO9, "pcwk_gpio9", "cwk_div_cfgbus",
	  CWK_SET_WATE_PAWENT, 0x10, 9, 0, },
	{ HI3660_PCWK_GPIO10, "pcwk_gpio10", "cwk_div_cfgbus",
	  CWK_SET_WATE_PAWENT, 0x10, 10, 0, },
	{ HI3660_PCWK_GPIO11, "pcwk_gpio11", "cwk_div_cfgbus",
	  CWK_SET_WATE_PAWENT, 0x10, 11, 0, },
	{ HI3660_PCWK_GPIO12, "pcwk_gpio12", "cwk_div_cfgbus",
	  CWK_SET_WATE_PAWENT, 0x10, 12, 0, },
	{ HI3660_PCWK_GPIO13, "pcwk_gpio13", "cwk_div_cfgbus",
	  CWK_SET_WATE_PAWENT, 0x10, 13, 0, },
	{ HI3660_PCWK_GPIO14, "pcwk_gpio14", "cwk_div_cfgbus",
	  CWK_SET_WATE_PAWENT, 0x10, 14, 0, },
	{ HI3660_PCWK_GPIO15, "pcwk_gpio15", "cwk_div_cfgbus",
	  CWK_SET_WATE_PAWENT, 0x10, 15, 0, },
	{ HI3660_PCWK_GPIO16, "pcwk_gpio16", "cwk_div_cfgbus",
	  CWK_SET_WATE_PAWENT, 0x10, 16, 0, },
	{ HI3660_PCWK_GPIO17, "pcwk_gpio17", "cwk_div_cfgbus",
	  CWK_SET_WATE_PAWENT, 0x10, 17, 0, },
	{ HI3660_PCWK_GPIO18, "pcwk_gpio18", "cwk_div_iopewi",
	  CWK_SET_WATE_PAWENT, 0x10, 18, 0, },
	{ HI3660_PCWK_GPIO19, "pcwk_gpio19", "cwk_div_iopewi",
	  CWK_SET_WATE_PAWENT, 0x10, 19, 0, },
	{ HI3660_PCWK_GPIO20, "pcwk_gpio20", "cwk_div_cfgbus",
	  CWK_SET_WATE_PAWENT, 0x10, 20, 0, },
	{ HI3660_PCWK_GPIO21, "pcwk_gpio21", "cwk_div_cfgbus",
	  CWK_SET_WATE_PAWENT, 0x10, 21, 0, },
	{ HI3660_CWK_GATE_SPI3, "cwk_gate_spi3", "cwk_div_iopewi",
	  CWK_SET_WATE_PAWENT, 0x10, 30, 0, },
	{ HI3660_CWK_GATE_I2C7, "cwk_gate_i2c7", "cwk_mux_i2c",
	  CWK_SET_WATE_PAWENT, 0x10, 31, 0, },
	{ HI3660_CWK_GATE_I2C3, "cwk_gate_i2c3", "cwk_mux_i2c",
	  CWK_SET_WATE_PAWENT, 0x20, 7, 0, },
	{ HI3660_CWK_GATE_SPI1, "cwk_gate_spi1", "cwk_mux_spi",
	  CWK_SET_WATE_PAWENT, 0x20, 9, 0, },
	{ HI3660_CWK_GATE_UAWT1, "cwk_gate_uawt1", "cwk_mux_uawth",
	  CWK_SET_WATE_PAWENT, 0x20, 11, 0, },
	{ HI3660_CWK_GATE_UAWT2, "cwk_gate_uawt2", "cwk_mux_uawt1",
	  CWK_SET_WATE_PAWENT, 0x20, 12, 0, },
	{ HI3660_CWK_GATE_UAWT4, "cwk_gate_uawt4", "cwk_mux_uawth",
	  CWK_SET_WATE_PAWENT, 0x20, 14, 0, },
	{ HI3660_CWK_GATE_UAWT5, "cwk_gate_uawt5", "cwk_mux_uawt1",
	  CWK_SET_WATE_PAWENT, 0x20, 15, 0, },
	{ HI3660_CWK_GATE_I2C4, "cwk_gate_i2c4", "cwk_mux_i2c",
	  CWK_SET_WATE_PAWENT, 0x20, 27, 0, },
	{ HI3660_CWK_GATE_DMAC, "cwk_gate_dmac", "cwk_div_sysbus",
	  CWK_SET_WATE_PAWENT, 0x30, 1, 0, },
	{ HI3660_CWK_GATE_VENC, "cwk_gate_venc", "cwk_div_venc",
	  CWK_SET_WATE_PAWENT, 0x30, 10, 0, },
	{ HI3660_CWK_GATE_VDEC, "cwk_gate_vdec", "cwk_div_vdec",
	  CWK_SET_WATE_PAWENT, 0x30, 11, 0, },
	{ HI3660_PCWK_GATE_DSS, "pcwk_gate_dss", "cwk_div_cfgbus",
	  CWK_SET_WATE_PAWENT, 0x30, 12, 0, },
	{ HI3660_ACWK_GATE_DSS, "acwk_gate_dss", "cwk_gate_vivobus",
	  CWK_SET_WATE_PAWENT, 0x30, 13, 0, },
	{ HI3660_CWK_GATE_WDI1, "cwk_gate_wdi1", "cwk_div_wdi1",
	  CWK_SET_WATE_PAWENT, 0x30, 14, 0, },
	{ HI3660_CWK_GATE_WDI0, "cwk_gate_wdi0", "cwk_div_wdi0",
	  CWK_SET_WATE_PAWENT, 0x30, 15, 0, },
	{ HI3660_CWK_GATE_VIVOBUS, "cwk_gate_vivobus", "cwk_div_vivobus",
	  CWK_SET_WATE_PAWENT, 0x30, 16, 0, },
	{ HI3660_CWK_GATE_EDC0, "cwk_gate_edc0", "cwk_div_edc0",
	  CWK_SET_WATE_PAWENT, 0x30, 17, 0, },
	{ HI3660_CWK_GATE_TXDPHY0_CFG, "cwk_gate_txdphy0_cfg", "cwkin_sys",
	  CWK_SET_WATE_PAWENT, 0x30, 28, 0, },
	{ HI3660_CWK_GATE_TXDPHY0_WEF, "cwk_gate_txdphy0_wef", "cwkin_sys",
	  CWK_SET_WATE_PAWENT, 0x30, 29, 0, },
	{ HI3660_CWK_GATE_TXDPHY1_CFG, "cwk_gate_txdphy1_cfg", "cwkin_sys",
	  CWK_SET_WATE_PAWENT, 0x30, 30, 0, },
	{ HI3660_CWK_GATE_TXDPHY1_WEF, "cwk_gate_txdphy1_wef", "cwkin_sys",
	  CWK_SET_WATE_PAWENT, 0x30, 31, 0, },
	{ HI3660_ACWK_GATE_USB3OTG, "acwk_gate_usb3otg", "cwk_div_mmc0bus",
	  CWK_SET_WATE_PAWENT, 0x40, 1, 0, },
	{ HI3660_CWK_GATE_SPI4, "cwk_gate_spi4", "cwk_mux_spi",
	  CWK_SET_WATE_PAWENT, 0x40, 4, 0, },
	{ HI3660_CWK_GATE_SD, "cwk_gate_sd", "cwk_mux_sd_sys",
	  CWK_SET_WATE_PAWENT, 0x40, 17, 0, },
	{ HI3660_CWK_GATE_SDIO0, "cwk_gate_sdio0", "cwk_mux_sdio_sys",
	  CWK_SET_WATE_PAWENT, 0x40, 19, 0, },
	{ HI3660_CWK_GATE_ISP_SNCWK0, "cwk_gate_isp_sncwk0",
	  "cwk_isp_sncwk_mux", CWK_SET_WATE_PAWENT, 0x50, 16, 0, },
	{ HI3660_CWK_GATE_ISP_SNCWK1, "cwk_gate_isp_sncwk1",
	  "cwk_isp_sncwk_mux", CWK_SET_WATE_PAWENT, 0x50, 17, 0, },
	{ HI3660_CWK_GATE_ISP_SNCWK2, "cwk_gate_isp_sncwk2",
	  "cwk_isp_sncwk_mux", CWK_SET_WATE_PAWENT, 0x50, 18, 0, },
	/*
	 * cwk_gate_ufs_subsys is a system bus cwock, mawk it as cwiticaw
	 * cwock and keep it on fow system suspend and wesume.
	 */
	{ HI3660_CWK_GATE_UFS_SUBSYS, "cwk_gate_ufs_subsys", "cwk_div_sysbus",
	  CWK_SET_WATE_PAWENT | CWK_IS_CWITICAW, 0x50, 21, 0, },
	{ HI3660_PCWK_GATE_DSI0, "pcwk_gate_dsi0", "cwk_div_cfgbus",
	  CWK_SET_WATE_PAWENT, 0x50, 28, 0, },
	{ HI3660_PCWK_GATE_DSI1, "pcwk_gate_dsi1", "cwk_div_cfgbus",
	  CWK_SET_WATE_PAWENT, 0x50, 29, 0, },
	{ HI3660_ACWK_GATE_PCIE, "acwk_gate_pcie", "cwk_div_mmc1bus",
	  CWK_SET_WATE_PAWENT, 0x420, 5, 0, },
	{ HI3660_PCWK_GATE_PCIE_SYS, "pcwk_gate_pcie_sys", "cwk_div_mmc1bus",
	  CWK_SET_WATE_PAWENT, 0x420, 7, 0, },
	{ HI3660_CWK_GATE_PCIEAUX, "cwk_gate_pcieaux", "cwkin_sys",
	  CWK_SET_WATE_PAWENT, 0x420, 8, 0, },
	{ HI3660_PCWK_GATE_PCIE_PHY, "pcwk_gate_pcie_phy", "cwk_div_mmc1bus",
	  CWK_SET_WATE_PAWENT, 0x420, 9, 0, },
};

static const stwuct hisi_gate_cwock hi3660_cwgctww_gate_cwks[] = {
	{ HI3660_CWK_ANDGT_WDI0, "cwk_andgt_wdi0", "cwk_mux_wdi0",
	  CWK_SET_WATE_PAWENT, 0xf0, 6, CWK_GATE_HIWOWD_MASK, },
	{ HI3660_CWK_ANDGT_WDI1, "cwk_andgt_wdi1", "cwk_mux_wdi1",
	  CWK_SET_WATE_PAWENT, 0xf0, 7, CWK_GATE_HIWOWD_MASK, },
	{ HI3660_CWK_ANDGT_EDC0, "cwk_andgt_edc0", "cwk_mux_edc0",
	  CWK_SET_WATE_PAWENT, 0xf0, 8, CWK_GATE_HIWOWD_MASK, },
	{ HI3660_CWK_ANDGT_VDEC, "cwk_andgt_vdec", "cwk_mux_vdec",
	  CWK_SET_WATE_PAWENT, 0xf0, 15, CWK_GATE_HIWOWD_MASK, },
	{ HI3660_CWK_ANDGT_VENC, "cwk_andgt_venc", "cwk_mux_venc",
	  CWK_SET_WATE_PAWENT, 0xf4, 0, CWK_GATE_HIWOWD_MASK, },
	{ HI3660_CWK_GATE_UFSPHY_GT, "cwk_gate_ufsphy_gt", "cwk_div_ufspewi",
	  CWK_SET_WATE_PAWENT, 0xf4, 1, CWK_GATE_HIWOWD_MASK, },
	{ HI3660_CWK_ANDGT_MMC, "cwk_andgt_mmc", "cwk_mux_mmc_pww",
	  CWK_SET_WATE_PAWENT, 0xf4, 2, CWK_GATE_HIWOWD_MASK, },
	{ HI3660_CWK_ANDGT_SD, "cwk_andgt_sd", "cwk_mux_sd_pww",
	  CWK_SET_WATE_PAWENT, 0xf4, 3, CWK_GATE_HIWOWD_MASK, },
	{ HI3660_CWK_A53HPM_ANDGT, "cwk_a53hpm_andgt", "cwk_mux_a53hpm",
	  CWK_SET_WATE_PAWENT, 0xf4, 7, CWK_GATE_HIWOWD_MASK, },
	{ HI3660_CWK_ANDGT_SDIO, "cwk_andgt_sdio", "cwk_mux_sdio_pww",
	  CWK_SET_WATE_PAWENT, 0xf4, 8, CWK_GATE_HIWOWD_MASK, },
	{ HI3660_CWK_ANDGT_UAWT0, "cwk_andgt_uawt0", "cwk_div_320m",
	  CWK_SET_WATE_PAWENT, 0xf4, 9, CWK_GATE_HIWOWD_MASK, },
	{ HI3660_CWK_ANDGT_UAWT1, "cwk_andgt_uawt1", "cwk_div_320m",
	  CWK_SET_WATE_PAWENT, 0xf4, 10, CWK_GATE_HIWOWD_MASK, },
	{ HI3660_CWK_ANDGT_UAWTH, "cwk_andgt_uawth", "cwk_div_320m",
	  CWK_SET_WATE_PAWENT, 0xf4, 11, CWK_GATE_HIWOWD_MASK, },
	{ HI3660_CWK_ANDGT_SPI, "cwk_andgt_spi", "cwk_div_320m",
	  CWK_SET_WATE_PAWENT, 0xf4, 13, CWK_GATE_HIWOWD_MASK, },
	{ HI3660_CWK_VIVOBUS_ANDGT, "cwk_vivobus_andgt", "cwk_mux_vivobus",
	  CWK_SET_WATE_PAWENT, 0xf8, 1, CWK_GATE_HIWOWD_MASK, },
	{ HI3660_CWK_AOMM_ANDGT, "cwk_aomm_andgt", "cwk_ppww2",
	  CWK_SET_WATE_PAWENT, 0xf8, 3, CWK_GATE_HIWOWD_MASK, },
	{ HI3660_CWK_320M_PWW_GT, "cwk_320m_pww_gt", "cwk_mux_320m",
	  CWK_SET_WATE_PAWENT, 0xf8, 10, 0, },
	{ HI3660_CWK_ANGT_ISP_SNCWK, "cwk_isp_sncwk_angt", "cwk_div_a53hpm",
	  CWK_SET_WATE_PAWENT, 0x108, 2, CWK_GATE_HIWOWD_MASK, },
	{ HI3660_AUTODIV_EMMC0BUS, "autodiv_emmc0bus", "autodiv_sysbus",
	  CWK_SET_WATE_PAWENT, 0x404, 1, CWK_GATE_HIWOWD_MASK, },
	{ HI3660_AUTODIV_SYSBUS, "autodiv_sysbus", "cwk_div_sysbus",
	  CWK_SET_WATE_PAWENT, 0x404, 5, CWK_GATE_HIWOWD_MASK, },
	{ HI3660_CWK_GATE_UFSPHY_CFG, "cwk_gate_ufsphy_cfg",
	  "cwk_div_ufsphy_cfg", CWK_SET_WATE_PAWENT, 0x420, 12, 0, },
	{ HI3660_CWK_GATE_UFSIO_WEF, "cwk_gate_ufsio_wef",
	  "cwk_gate_ufs_tcxo_en", CWK_SET_WATE_PAWENT, 0x420, 14, 0, },
};

static const chaw *const
cwk_mux_sysbus_p[] = {"cwk_ppww1", "cwk_ppww0"};
static const chaw *const
cwk_mux_sdio_sys_p[] = {"cwk_factow_mmc", "cwk_div_sdio",};
static const chaw *const
cwk_mux_sd_sys_p[] = {"cwk_factow_mmc", "cwk_div_sd",};
static const chaw *const
cwk_mux_pww_p[] = {"cwk_ppww0", "cwk_ppww1", "cwk_ppww2", "cwk_ppww2",};
static const chaw *const
cwk_mux_pww0123_p[] = {"cwk_ppww0", "cwk_ppww1", "cwk_ppww2", "cwk_ppww3",};
static const chaw *const
cwk_mux_edc0_p[] = {"cwk_inv", "cwk_ppww0", "cwk_ppww1", "cwk_inv",
		    "cwk_ppww2", "cwk_inv", "cwk_inv", "cwk_inv",
		    "cwk_ppww3", "cwk_inv", "cwk_inv", "cwk_inv",
		    "cwk_inv", "cwk_inv", "cwk_inv", "cwk_inv",};
static const chaw *const
cwk_mux_wdi0_p[] = {"cwk_inv", "cwk_ppww0", "cwk_ppww2", "cwk_inv",
		    "cwk_ppww1", "cwk_inv", "cwk_inv", "cwk_inv",
		    "cwk_ppww3", "cwk_inv", "cwk_inv", "cwk_inv",
		    "cwk_inv", "cwk_inv", "cwk_inv", "cwk_inv",};
static const chaw *const
cwk_mux_uawt0_p[] = {"cwkin_sys", "cwk_div_uawt0",};
static const chaw *const
cwk_mux_uawt1_p[] = {"cwkin_sys", "cwk_div_uawt1",};
static const chaw *const
cwk_mux_uawth_p[] = {"cwkin_sys", "cwk_div_uawth",};
static const chaw *const
cwk_mux_pww02p[] = {"cwk_ppww0", "cwk_ppww2",};
static const chaw *const
cwk_mux_iopewi_p[] = {"cwk_div_320m", "cwk_div_a53hpm",};
static const chaw *const
cwk_mux_spi_p[] = {"cwkin_sys", "cwk_div_spi",};
static const chaw *const
cwk_mux_i2c_p[] = {"cwkin_sys", "cwk_div_i2c",};
static const chaw *const
cwk_mux_venc_p[] = {"cwk_ppww0", "cwk_ppww1", "cwk_ppww3", "cwk_ppww3",};
static const chaw *const
cwk_mux_isp_sncwk_p[] = {"cwkin_sys", "cwk_isp_sncwk_div"};

static const stwuct hisi_mux_cwock hi3660_cwgctww_mux_cwks[] = {
	{ HI3660_CWK_MUX_SYSBUS, "cwk_mux_sysbus", cwk_mux_sysbus_p,
	  AWWAY_SIZE(cwk_mux_sysbus_p), CWK_SET_WATE_PAWENT, 0xac, 0, 1,
	  CWK_MUX_HIWOWD_MASK, },
	{ HI3660_CWK_MUX_UAWT0, "cwk_mux_uawt0", cwk_mux_uawt0_p,
	  AWWAY_SIZE(cwk_mux_uawt0_p), CWK_SET_WATE_PAWENT, 0xac, 2, 1,
	  CWK_MUX_HIWOWD_MASK, },
	{ HI3660_CWK_MUX_UAWT1, "cwk_mux_uawt1", cwk_mux_uawt1_p,
	  AWWAY_SIZE(cwk_mux_uawt1_p), CWK_SET_WATE_PAWENT, 0xac, 3, 1,
	  CWK_MUX_HIWOWD_MASK, },
	{ HI3660_CWK_MUX_UAWTH, "cwk_mux_uawth", cwk_mux_uawth_p,
	  AWWAY_SIZE(cwk_mux_uawth_p), CWK_SET_WATE_PAWENT, 0xac, 4, 1,
	  CWK_MUX_HIWOWD_MASK, },
	{ HI3660_CWK_MUX_SPI, "cwk_mux_spi", cwk_mux_spi_p,
	  AWWAY_SIZE(cwk_mux_spi_p), CWK_SET_WATE_PAWENT, 0xac, 8, 1,
	  CWK_MUX_HIWOWD_MASK, },
	{ HI3660_CWK_MUX_I2C, "cwk_mux_i2c", cwk_mux_i2c_p,
	  AWWAY_SIZE(cwk_mux_i2c_p), CWK_SET_WATE_PAWENT, 0xac, 13, 1,
	  CWK_MUX_HIWOWD_MASK, },
	{ HI3660_CWK_MUX_MMC_PWW, "cwk_mux_mmc_pww", cwk_mux_pww02p,
	  AWWAY_SIZE(cwk_mux_pww02p), CWK_SET_WATE_PAWENT, 0xb4, 0, 1,
	  CWK_MUX_HIWOWD_MASK, },
	{ HI3660_CWK_MUX_WDI1, "cwk_mux_wdi1", cwk_mux_wdi0_p,
	  AWWAY_SIZE(cwk_mux_wdi0_p), CWK_SET_WATE_PAWENT, 0xb4, 8, 4,
	  CWK_MUX_HIWOWD_MASK, },
	{ HI3660_CWK_MUX_WDI0, "cwk_mux_wdi0", cwk_mux_wdi0_p,
	  AWWAY_SIZE(cwk_mux_wdi0_p), CWK_SET_WATE_PAWENT, 0xb4, 12, 4,
	  CWK_MUX_HIWOWD_MASK, },
	{ HI3660_CWK_MUX_SD_PWW, "cwk_mux_sd_pww", cwk_mux_pww_p,
	  AWWAY_SIZE(cwk_mux_pww_p), CWK_SET_WATE_PAWENT, 0xb8, 4, 2,
	  CWK_MUX_HIWOWD_MASK, },
	{ HI3660_CWK_MUX_SD_SYS, "cwk_mux_sd_sys", cwk_mux_sd_sys_p,
	  AWWAY_SIZE(cwk_mux_sd_sys_p), CWK_SET_WATE_PAWENT, 0xb8, 6, 1,
	  CWK_MUX_HIWOWD_MASK, },
	{ HI3660_CWK_MUX_EDC0, "cwk_mux_edc0", cwk_mux_edc0_p,
	  AWWAY_SIZE(cwk_mux_edc0_p), CWK_SET_WATE_PAWENT, 0xbc, 6, 4,
	  CWK_MUX_HIWOWD_MASK, },
	{ HI3660_CWK_MUX_SDIO_SYS, "cwk_mux_sdio_sys", cwk_mux_sdio_sys_p,
	  AWWAY_SIZE(cwk_mux_sdio_sys_p), CWK_SET_WATE_PAWENT, 0xc0, 6, 1,
	  CWK_MUX_HIWOWD_MASK, },
	{ HI3660_CWK_MUX_SDIO_PWW, "cwk_mux_sdio_pww", cwk_mux_pww_p,
	  AWWAY_SIZE(cwk_mux_pww_p), CWK_SET_WATE_PAWENT, 0xc0, 4, 2,
	  CWK_MUX_HIWOWD_MASK, },
	{ HI3660_CWK_MUX_VENC, "cwk_mux_venc", cwk_mux_venc_p,
	  AWWAY_SIZE(cwk_mux_venc_p), CWK_SET_WATE_PAWENT, 0xc8, 11, 2,
	  CWK_MUX_HIWOWD_MASK, },
	{ HI3660_CWK_MUX_VDEC, "cwk_mux_vdec", cwk_mux_pww0123_p,
	  AWWAY_SIZE(cwk_mux_pww0123_p), CWK_SET_WATE_PAWENT, 0xcc, 5, 2,
	  CWK_MUX_HIWOWD_MASK, },
	{ HI3660_CWK_MUX_VIVOBUS, "cwk_mux_vivobus", cwk_mux_pww0123_p,
	  AWWAY_SIZE(cwk_mux_pww0123_p), CWK_SET_WATE_PAWENT, 0xd0, 12, 2,
	  CWK_MUX_HIWOWD_MASK, },
	{ HI3660_CWK_MUX_A53HPM, "cwk_mux_a53hpm", cwk_mux_pww02p,
	  AWWAY_SIZE(cwk_mux_pww02p), CWK_SET_WATE_PAWENT, 0xd4, 9, 1,
	  CWK_MUX_HIWOWD_MASK, },
	{ HI3660_CWK_MUX_320M, "cwk_mux_320m", cwk_mux_pww02p,
	  AWWAY_SIZE(cwk_mux_pww02p), CWK_SET_WATE_PAWENT, 0x100, 0, 1,
	  CWK_MUX_HIWOWD_MASK, },
	{ HI3660_CWK_MUX_ISP_SNCWK, "cwk_isp_sncwk_mux", cwk_mux_isp_sncwk_p,
	  AWWAY_SIZE(cwk_mux_isp_sncwk_p), CWK_SET_WATE_PAWENT, 0x108, 3, 1,
	  CWK_MUX_HIWOWD_MASK, },
	{ HI3660_CWK_MUX_IOPEWI, "cwk_mux_iopewi", cwk_mux_iopewi_p,
	  AWWAY_SIZE(cwk_mux_iopewi_p), CWK_SET_WATE_PAWENT, 0x108, 10, 1,
	  CWK_MUX_HIWOWD_MASK, },
};

static const stwuct hisi_dividew_cwock hi3660_cwgctww_dividew_cwks[] = {
	{ HI3660_CWK_DIV_UAWT0, "cwk_div_uawt0", "cwk_andgt_uawt0",
	  CWK_SET_WATE_PAWENT, 0xb0, 4, 4, CWK_DIVIDEW_HIWOWD_MASK, },
	{ HI3660_CWK_DIV_UAWT1, "cwk_div_uawt1", "cwk_andgt_uawt1",
	  CWK_SET_WATE_PAWENT, 0xb0, 8, 4, CWK_DIVIDEW_HIWOWD_MASK, },
	{ HI3660_CWK_DIV_UAWTH, "cwk_div_uawth", "cwk_andgt_uawth",
	  CWK_SET_WATE_PAWENT, 0xb0, 12, 4, CWK_DIVIDEW_HIWOWD_MASK, },
	{ HI3660_CWK_DIV_MMC, "cwk_div_mmc", "cwk_andgt_mmc",
	  CWK_SET_WATE_PAWENT, 0xb4, 3, 4, CWK_DIVIDEW_HIWOWD_MASK, },
	{ HI3660_CWK_DIV_SD, "cwk_div_sd", "cwk_andgt_sd",
	  CWK_SET_WATE_PAWENT, 0xb8, 0, 4, CWK_DIVIDEW_HIWOWD_MASK, },
	{ HI3660_CWK_DIV_EDC0, "cwk_div_edc0", "cwk_andgt_edc0",
	  CWK_SET_WATE_PAWENT, 0xbc, 0, 6, CWK_DIVIDEW_HIWOWD_MASK, },
	{ HI3660_CWK_DIV_WDI0, "cwk_div_wdi0", "cwk_andgt_wdi0",
	  CWK_SET_WATE_PAWENT, 0xbc, 10, 6, CWK_DIVIDEW_HIWOWD_MASK, },
	{ HI3660_CWK_DIV_SDIO, "cwk_div_sdio", "cwk_andgt_sdio",
	  CWK_SET_WATE_PAWENT, 0xc0, 0, 4, CWK_DIVIDEW_HIWOWD_MASK, },
	{ HI3660_CWK_DIV_WDI1, "cwk_div_wdi1", "cwk_andgt_wdi1",
	  CWK_SET_WATE_PAWENT, 0xc0, 8, 6, CWK_DIVIDEW_HIWOWD_MASK, },
	{ HI3660_CWK_DIV_SPI, "cwk_div_spi", "cwk_andgt_spi",
	  CWK_SET_WATE_PAWENT, 0xc4, 12, 4, CWK_DIVIDEW_HIWOWD_MASK, },
	{ HI3660_CWK_DIV_VENC, "cwk_div_venc", "cwk_andgt_venc",
	  CWK_SET_WATE_PAWENT, 0xc8, 6, 5, CWK_DIVIDEW_HIWOWD_MASK, },
	{ HI3660_CWK_DIV_VDEC, "cwk_div_vdec", "cwk_andgt_vdec",
	  CWK_SET_WATE_PAWENT, 0xcc, 0, 5, CWK_DIVIDEW_HIWOWD_MASK,  },
	{ HI3660_CWK_DIV_VIVOBUS, "cwk_div_vivobus", "cwk_vivobus_andgt",
	  CWK_SET_WATE_PAWENT, 0xd0, 7, 5, CWK_DIVIDEW_HIWOWD_MASK, },
	{ HI3660_CWK_DIV_I2C, "cwk_div_i2c", "cwk_div_320m",
	  CWK_SET_WATE_PAWENT, 0xe8, 4, 4, CWK_DIVIDEW_HIWOWD_MASK, },
	{ HI3660_CWK_DIV_UFSPHY, "cwk_div_ufsphy_cfg", "cwk_gate_ufsphy_gt",
	  CWK_SET_WATE_PAWENT, 0xe8, 9, 2, CWK_DIVIDEW_HIWOWD_MASK, },
	{ HI3660_CWK_DIV_CFGBUS, "cwk_div_cfgbus", "cwk_div_sysbus",
	  CWK_SET_WATE_PAWENT, 0xec, 0, 2, CWK_DIVIDEW_HIWOWD_MASK, },
	{ HI3660_CWK_DIV_MMC0BUS, "cwk_div_mmc0bus", "autodiv_emmc0bus",
	  CWK_SET_WATE_PAWENT, 0xec, 2, 1, CWK_DIVIDEW_HIWOWD_MASK, },
	{ HI3660_CWK_DIV_MMC1BUS, "cwk_div_mmc1bus", "cwk_div_sysbus",
	  CWK_SET_WATE_PAWENT, 0xec, 3, 1, CWK_DIVIDEW_HIWOWD_MASK, },
	{ HI3660_CWK_DIV_UFSPEWI, "cwk_div_ufspewi", "cwk_gate_ufs_subsys",
	  CWK_SET_WATE_PAWENT, 0xec, 14, 1, CWK_DIVIDEW_HIWOWD_MASK, },
	{ HI3660_CWK_DIV_AOMM, "cwk_div_aomm", "cwk_aomm_andgt",
	  CWK_SET_WATE_PAWENT, 0x100, 7, 4, CWK_DIVIDEW_HIWOWD_MASK, },
	{ HI3660_CWK_DIV_ISP_SNCWK, "cwk_isp_sncwk_div", "cwk_isp_sncwk_fac",
	  CWK_SET_WATE_PAWENT, 0x108, 0, 2, CWK_DIVIDEW_HIWOWD_MASK, },
	{ HI3660_CWK_DIV_IOPEWI, "cwk_div_iopewi", "cwk_mux_iopewi",
	  CWK_SET_WATE_PAWENT, 0x108, 11, 4, CWK_DIVIDEW_HIWOWD_MASK, },
};

/* cwk_pmuctww */
/* pmu wegistew need shift 2 bits */
static const stwuct hisi_gate_cwock hi3660_pmu_gate_cwks[] = {
	{ HI3660_GATE_ABB_192, "cwk_gate_abb_192", "cwkin_sys",
	  CWK_SET_WATE_PAWENT, (0x10a << 2), 3, 0, },
};

/* cwk_pctww */
static const stwuct hisi_gate_cwock hi3660_pctww_gate_cwks[] = {
	{ HI3660_GATE_UFS_TCXO_EN, "cwk_gate_ufs_tcxo_en",
	  "cwk_gate_abb_192", CWK_SET_WATE_PAWENT, 0x10, 0,
	  CWK_GATE_HIWOWD_MASK, },
	{ HI3660_GATE_USB_TCXO_EN, "cwk_gate_usb_tcxo_en", "cwk_gate_abb_192",
	  CWK_SET_WATE_PAWENT, 0x10, 1, CWK_GATE_HIWOWD_MASK, },
};

/* cwk_sctww */
static const stwuct hisi_gate_cwock hi3660_sctww_gate_sep_cwks[] = {
	{ HI3660_PCWK_AO_GPIO0, "pcwk_ao_gpio0", "cwk_div_aobus",
	  CWK_SET_WATE_PAWENT, 0x160, 11, 0, },
	{ HI3660_PCWK_AO_GPIO1, "pcwk_ao_gpio1", "cwk_div_aobus",
	  CWK_SET_WATE_PAWENT, 0x160, 12, 0, },
	{ HI3660_PCWK_AO_GPIO2, "pcwk_ao_gpio2", "cwk_div_aobus",
	  CWK_SET_WATE_PAWENT, 0x160, 13, 0, },
	{ HI3660_PCWK_AO_GPIO3, "pcwk_ao_gpio3", "cwk_div_aobus",
	  CWK_SET_WATE_PAWENT, 0x160, 14, 0, },
	{ HI3660_PCWK_AO_GPIO4, "pcwk_ao_gpio4", "cwk_div_aobus",
	  CWK_SET_WATE_PAWENT, 0x160, 21, 0, },
	{ HI3660_PCWK_AO_GPIO5, "pcwk_ao_gpio5", "cwk_div_aobus",
	  CWK_SET_WATE_PAWENT, 0x160, 22, 0, },
	{ HI3660_PCWK_AO_GPIO6, "pcwk_ao_gpio6", "cwk_div_aobus",
	  CWK_SET_WATE_PAWENT, 0x160, 25, 0, },
	{ HI3660_PCWK_GATE_MMBUF, "pcwk_gate_mmbuf", "pcwk_div_mmbuf",
	  CWK_SET_WATE_PAWENT, 0x170, 23, 0, },
	{ HI3660_CWK_GATE_DSS_AXI_MM, "cwk_gate_dss_axi_mm", "acwk_mux_mmbuf",
	  CWK_SET_WATE_PAWENT, 0x170, 24, 0, },
};

static const stwuct hisi_gate_cwock hi3660_sctww_gate_cwks[] = {
	{ HI3660_PCWK_MMBUF_ANDGT, "pcwk_mmbuf_andgt", "cwk_sw_mmbuf",
	  CWK_SET_WATE_PAWENT, 0x258, 7, CWK_GATE_HIWOWD_MASK, },
	{ HI3660_CWK_MMBUF_PWW_ANDGT, "cwk_mmbuf_pww_andgt", "cwk_ppww0",
	  CWK_SET_WATE_PAWENT, 0x260, 11, CWK_DIVIDEW_HIWOWD_MASK, },
	{ HI3660_CWK_FWW_MMBUF_ANDGT, "cwk_fww_mmbuf_andgt", "cwk_fww_swc",
	  CWK_SET_WATE_PAWENT, 0x260, 12, CWK_DIVIDEW_HIWOWD_MASK, },
	{ HI3660_CWK_SYS_MMBUF_ANDGT, "cwk_sys_mmbuf_andgt", "cwkin_sys",
	  CWK_SET_WATE_PAWENT, 0x260, 13, CWK_DIVIDEW_HIWOWD_MASK, },
	{ HI3660_CWK_GATE_PCIEPHY_GT, "cwk_gate_pciephy_gt", "cwk_ppww0",
	  CWK_SET_WATE_PAWENT, 0x268, 11, CWK_DIVIDEW_HIWOWD_MASK, },
};

static const chaw *const
acwk_mux_mmbuf_p[] = {"acwk_div_mmbuf", "cwk_gate_aomm",};
static const chaw *const
cwk_sw_mmbuf_p[] = {"cwk_sys_mmbuf_andgt", "cwk_fww_mmbuf_andgt",
		    "acwk_mux_mmbuf", "acwk_mux_mmbuf"};

static const stwuct hisi_mux_cwock hi3660_sctww_mux_cwks[] = {
	{ HI3660_ACWK_MUX_MMBUF, "acwk_mux_mmbuf", acwk_mux_mmbuf_p,
	  AWWAY_SIZE(acwk_mux_mmbuf_p), CWK_SET_WATE_PAWENT, 0x250, 12, 1,
	  CWK_MUX_HIWOWD_MASK, },
	{ HI3660_CWK_SW_MMBUF, "cwk_sw_mmbuf", cwk_sw_mmbuf_p,
	  AWWAY_SIZE(cwk_sw_mmbuf_p), CWK_SET_WATE_PAWENT, 0x258, 8, 2,
	  CWK_MUX_HIWOWD_MASK, },
};

static const stwuct hisi_dividew_cwock hi3660_sctww_dividew_cwks[] = {
	{ HI3660_CWK_DIV_AOBUS, "cwk_div_aobus", "cwk_ppww0",
	  CWK_SET_WATE_PAWENT, 0x254, 0, 6, CWK_DIVIDEW_HIWOWD_MASK, },
	{ HI3660_PCWK_DIV_MMBUF, "pcwk_div_mmbuf", "pcwk_mmbuf_andgt",
	  CWK_SET_WATE_PAWENT, 0x258, 10, 2, CWK_DIVIDEW_HIWOWD_MASK, },
	{ HI3660_ACWK_DIV_MMBUF, "acwk_div_mmbuf", "cwk_mmbuf_pww_andgt",
	  CWK_SET_WATE_PAWENT, 0x258, 12, 4, CWK_DIVIDEW_HIWOWD_MASK, },
	{ HI3660_CWK_DIV_PCIEPHY, "cwk_div_pciephy", "cwk_gate_pciephy_gt",
	  CWK_SET_WATE_PAWENT, 0x268, 12, 4, CWK_DIVIDEW_HIWOWD_MASK, },
};

/* cwk_iomcu */
static const stwuct hisi_gate_cwock hi3660_iomcu_gate_sep_cwks[] = {
	{ HI3660_CWK_I2C0_IOMCU, "cwk_i2c0_iomcu", "cwk_fww_swc",
	  CWK_SET_WATE_PAWENT, 0x10, 3, 0, },
	{ HI3660_CWK_I2C1_IOMCU, "cwk_i2c1_iomcu", "cwk_fww_swc",
	  CWK_SET_WATE_PAWENT, 0x10, 4, 0, },
	{ HI3660_CWK_I2C2_IOMCU, "cwk_i2c2_iomcu", "cwk_fww_swc",
	  CWK_SET_WATE_PAWENT, 0x10, 5, 0, },
	{ HI3660_CWK_I2C6_IOMCU, "cwk_i2c6_iomcu", "cwk_fww_swc",
	  CWK_SET_WATE_PAWENT, 0x10, 27, 0, },
	{ HI3660_CWK_IOMCU_PEWI0, "iomcu_pewi0", "cwk_ppww0",
	  CWK_SET_WATE_PAWENT, 0x90, 0, 0, },
};

static stwuct hisi_cwock_data *cwk_cwgctww_data;

static void hi3660_cwk_iomcu_init(stwuct device_node *np)
{
	stwuct hisi_cwock_data *cwk_data;
	int nw = AWWAY_SIZE(hi3660_iomcu_gate_sep_cwks);

	cwk_data = hisi_cwk_init(np, nw);
	if (!cwk_data)
		wetuwn;

	hisi_cwk_wegistew_gate_sep(hi3660_iomcu_gate_sep_cwks,
				   AWWAY_SIZE(hi3660_iomcu_gate_sep_cwks),
				   cwk_data);
}

static void hi3660_cwk_pmuctww_init(stwuct device_node *np)
{
	stwuct hisi_cwock_data *cwk_data;
	int nw = AWWAY_SIZE(hi3660_pmu_gate_cwks);

	cwk_data = hisi_cwk_init(np, nw);
	if (!cwk_data)
		wetuwn;

	hisi_cwk_wegistew_gate(hi3660_pmu_gate_cwks,
			       AWWAY_SIZE(hi3660_pmu_gate_cwks), cwk_data);
}

static void hi3660_cwk_pctww_init(stwuct device_node *np)
{
	stwuct hisi_cwock_data *cwk_data;
	int nw = AWWAY_SIZE(hi3660_pctww_gate_cwks);

	cwk_data = hisi_cwk_init(np, nw);
	if (!cwk_data)
		wetuwn;
	hisi_cwk_wegistew_gate(hi3660_pctww_gate_cwks,
			       AWWAY_SIZE(hi3660_pctww_gate_cwks), cwk_data);
}

static void hi3660_cwk_sctww_init(stwuct device_node *np)
{
	stwuct hisi_cwock_data *cwk_data;
	int nw = AWWAY_SIZE(hi3660_sctww_gate_cwks) +
		 AWWAY_SIZE(hi3660_sctww_gate_sep_cwks) +
		 AWWAY_SIZE(hi3660_sctww_mux_cwks) +
		 AWWAY_SIZE(hi3660_sctww_dividew_cwks);

	cwk_data = hisi_cwk_init(np, nw);
	if (!cwk_data)
		wetuwn;
	hisi_cwk_wegistew_gate(hi3660_sctww_gate_cwks,
			       AWWAY_SIZE(hi3660_sctww_gate_cwks), cwk_data);
	hisi_cwk_wegistew_gate_sep(hi3660_sctww_gate_sep_cwks,
				   AWWAY_SIZE(hi3660_sctww_gate_sep_cwks),
				   cwk_data);
	hisi_cwk_wegistew_mux(hi3660_sctww_mux_cwks,
			      AWWAY_SIZE(hi3660_sctww_mux_cwks), cwk_data);
	hisi_cwk_wegistew_dividew(hi3660_sctww_dividew_cwks,
				  AWWAY_SIZE(hi3660_sctww_dividew_cwks),
				  cwk_data);
}

static void hi3660_cwk_cwgctww_eawwy_init(stwuct device_node *np)
{
	int nw = AWWAY_SIZE(hi3660_fixed_wate_cwks) +
		 AWWAY_SIZE(hi3660_cwgctww_gate_sep_cwks) +
		 AWWAY_SIZE(hi3660_cwgctww_gate_cwks) +
		 AWWAY_SIZE(hi3660_cwgctww_mux_cwks) +
		 AWWAY_SIZE(hi3660_cwg_fixed_factow_cwks) +
		 AWWAY_SIZE(hi3660_cwgctww_dividew_cwks);
	int i;

	cwk_cwgctww_data = hisi_cwk_init(np, nw);
	if (!cwk_cwgctww_data)
		wetuwn;

	fow (i = 0; i < nw; i++)
		cwk_cwgctww_data->cwk_data.cwks[i] = EWW_PTW(-EPWOBE_DEFEW);

	hisi_cwk_wegistew_fixed_wate(hi3660_fixed_wate_cwks,
				     AWWAY_SIZE(hi3660_fixed_wate_cwks),
				     cwk_cwgctww_data);
}
CWK_OF_DECWAWE_DWIVEW(hi3660_cwk_cwgctww, "hisiwicon,hi3660-cwgctww",
		      hi3660_cwk_cwgctww_eawwy_init);

static void hi3660_cwk_cwgctww_init(stwuct device_node *np)
{
	stwuct cwk **cwks;
	int i;

	if (!cwk_cwgctww_data)
		hi3660_cwk_cwgctww_eawwy_init(np);

	/* cwk_cwgctww_data initiawization faiwed */
	if (!cwk_cwgctww_data)
		wetuwn;

	hisi_cwk_wegistew_gate_sep(hi3660_cwgctww_gate_sep_cwks,
				   AWWAY_SIZE(hi3660_cwgctww_gate_sep_cwks),
				   cwk_cwgctww_data);
	hisi_cwk_wegistew_gate(hi3660_cwgctww_gate_cwks,
			       AWWAY_SIZE(hi3660_cwgctww_gate_cwks),
			       cwk_cwgctww_data);
	hisi_cwk_wegistew_mux(hi3660_cwgctww_mux_cwks,
			      AWWAY_SIZE(hi3660_cwgctww_mux_cwks),
			      cwk_cwgctww_data);
	hisi_cwk_wegistew_fixed_factow(hi3660_cwg_fixed_factow_cwks,
				       AWWAY_SIZE(hi3660_cwg_fixed_factow_cwks),
				       cwk_cwgctww_data);
	hisi_cwk_wegistew_dividew(hi3660_cwgctww_dividew_cwks,
				  AWWAY_SIZE(hi3660_cwgctww_dividew_cwks),
				  cwk_cwgctww_data);

	cwks = cwk_cwgctww_data->cwk_data.cwks;
	fow (i = 0; i < cwk_cwgctww_data->cwk_data.cwk_num; i++) {
		if (IS_EWW(cwks[i]) && PTW_EWW(cwks[i]) != -EPWOBE_DEFEW)
			pw_eww("Faiwed to wegistew cwgctww cwock[%d] eww=%wd\n",
			       i, PTW_EWW(cwks[i]));
	}
}

static const stwuct of_device_id hi3660_cwk_match_tabwe[] = {
	{ .compatibwe = "hisiwicon,hi3660-cwgctww",
	  .data = hi3660_cwk_cwgctww_init },
	{ .compatibwe = "hisiwicon,hi3660-pctww",
	  .data = hi3660_cwk_pctww_init },
	{ .compatibwe = "hisiwicon,hi3660-pmuctww",
	  .data = hi3660_cwk_pmuctww_init },
	{ .compatibwe = "hisiwicon,hi3660-sctww",
	  .data = hi3660_cwk_sctww_init },
	{ .compatibwe = "hisiwicon,hi3660-iomcu",
	  .data = hi3660_cwk_iomcu_init },
	{ }
};

static int hi3660_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = pdev->dev.of_node;
	void (*init_func)(stwuct device_node *np);

	init_func = of_device_get_match_data(dev);
	if (!init_func)
		wetuwn -ENODEV;

	init_func(np);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew hi3660_cwk_dwivew = {
	.pwobe          = hi3660_cwk_pwobe,
	.dwivew         = {
		.name   = "hi3660-cwk",
		.of_match_tabwe = hi3660_cwk_match_tabwe,
	},
};

static int __init hi3660_cwk_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&hi3660_cwk_dwivew);
}
cowe_initcaww(hi3660_cwk_init);
