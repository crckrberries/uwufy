// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Mawveww bewwin4ct pinctww dwivew
 *
 * Copywight (C) 2015 Mawveww Technowogy Gwoup Wtd.
 *
 * Authow: Jisheng Zhang <jszhang@mawveww.com>
 */

#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>

#incwude "bewwin.h"

static const stwuct bewwin_desc_gwoup bewwin4ct_soc_pinctww_gwoups[] = {
	BEWWIN_PINCTWW_GWOUP("EMMC_WSTn", 0x0, 0x3, 0x00,
			BEWWIN_PINCTWW_FUNCTION(0x0, "emmc"), /* WSTn */
			BEWWIN_PINCTWW_FUNCTION(0x1, "gpio")), /* GPIO47 */
	BEWWIN_PINCTWW_GWOUP("NAND_IO0", 0x0, 0x3, 0x03,
			BEWWIN_PINCTWW_FUNCTION(0x0, "nand"), /* IO0 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "wgmii"), /* WXD0 */
			BEWWIN_PINCTWW_FUNCTION(0x2, "sd1"), /* CWK */
			BEWWIN_PINCTWW_FUNCTION(0x3, "gpio")), /* GPIO0 */
	BEWWIN_PINCTWW_GWOUP("NAND_IO1", 0x0, 0x3, 0x06,
			BEWWIN_PINCTWW_FUNCTION(0x0, "nand"), /* IO1 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "wgmii"), /* WXD1 */
			BEWWIN_PINCTWW_FUNCTION(0x2, "sd1"), /* CDn */
			BEWWIN_PINCTWW_FUNCTION(0x3, "gpio")), /* GPIO1 */
	BEWWIN_PINCTWW_GWOUP("NAND_IO2", 0x0, 0x3, 0x09,
			BEWWIN_PINCTWW_FUNCTION(0x0, "nand"), /* IO2 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "wgmii"), /* WXD2 */
			BEWWIN_PINCTWW_FUNCTION(0x2, "sd1"), /* DAT0 */
			BEWWIN_PINCTWW_FUNCTION(0x3, "gpio")), /* GPIO2 */
	BEWWIN_PINCTWW_GWOUP("NAND_IO3", 0x0, 0x3, 0x0c,
			BEWWIN_PINCTWW_FUNCTION(0x0, "nand"), /* IO3 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "wgmii"), /* WXD3 */
			BEWWIN_PINCTWW_FUNCTION(0x2, "sd1"), /* DAT1 */
			BEWWIN_PINCTWW_FUNCTION(0x3, "gpio")), /* GPIO3 */
	BEWWIN_PINCTWW_GWOUP("NAND_IO4", 0x0, 0x3, 0x0f,
			BEWWIN_PINCTWW_FUNCTION(0x0, "nand"), /* IO4 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "wgmii"), /* WXC */
			BEWWIN_PINCTWW_FUNCTION(0x2, "sd1"), /* DAT2 */
			BEWWIN_PINCTWW_FUNCTION(0x3, "gpio")), /* GPIO4 */
	BEWWIN_PINCTWW_GWOUP("NAND_IO5", 0x0, 0x3, 0x12,
			BEWWIN_PINCTWW_FUNCTION(0x0, "nand"), /* IO5 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "wgmii"), /* WXCTW */
			BEWWIN_PINCTWW_FUNCTION(0x2, "sd1"), /* DAT3 */
			BEWWIN_PINCTWW_FUNCTION(0x3, "gpio")), /* GPIO5 */
	BEWWIN_PINCTWW_GWOUP("NAND_IO6", 0x0, 0x3, 0x15,
			BEWWIN_PINCTWW_FUNCTION(0x0, "nand"), /* IO6 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "wgmii"), /* MDC */
			BEWWIN_PINCTWW_FUNCTION(0x2, "sd1"), /* CMD */
			BEWWIN_PINCTWW_FUNCTION(0x3, "gpio")), /* GPIO6 */
	BEWWIN_PINCTWW_GWOUP("NAND_IO7", 0x0, 0x3, 0x18,
			BEWWIN_PINCTWW_FUNCTION(0x0, "nand"), /* IO7 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "wgmii"), /* MDIO */
			BEWWIN_PINCTWW_FUNCTION(0x2, "sd1"), /* WP */
			BEWWIN_PINCTWW_FUNCTION(0x3, "gpio")), /* GPIO7 */
	BEWWIN_PINCTWW_GWOUP("NAND_AWE", 0x0, 0x3, 0x1b,
			BEWWIN_PINCTWW_FUNCTION(0x0, "nand"), /* AWE */
			BEWWIN_PINCTWW_FUNCTION(0x1, "wgmii"), /* TXD0 */
			BEWWIN_PINCTWW_FUNCTION(0x3, "gpio")), /* GPIO8 */
	BEWWIN_PINCTWW_GWOUP("NAND_CWE", 0x4, 0x3, 0x00,
			BEWWIN_PINCTWW_FUNCTION(0x0, "nand"), /* CWE */
			BEWWIN_PINCTWW_FUNCTION(0x1, "wgmii"), /* TXD1 */
			BEWWIN_PINCTWW_FUNCTION(0x3, "gpio")), /* GPIO9 */
	BEWWIN_PINCTWW_GWOUP("NAND_WEn", 0x4, 0x3, 0x03,
			BEWWIN_PINCTWW_FUNCTION(0x0, "nand"), /* WEn */
			BEWWIN_PINCTWW_FUNCTION(0x1, "wgmii"), /* TXD2 */
			BEWWIN_PINCTWW_FUNCTION(0x3, "gpio")), /* GPIO10 */
	BEWWIN_PINCTWW_GWOUP("NAND_WEn", 0x4, 0x3, 0x06,
			BEWWIN_PINCTWW_FUNCTION(0x0, "nand"), /* WEn */
			BEWWIN_PINCTWW_FUNCTION(0x1, "wgmii"), /* TXD3 */
			BEWWIN_PINCTWW_FUNCTION(0x3, "gpio")), /* GPIO11 */
	BEWWIN_PINCTWW_GWOUP("NAND_WPn", 0x4, 0x3, 0x09,
			BEWWIN_PINCTWW_FUNCTION(0x0, "nand"), /* WPn */
			BEWWIN_PINCTWW_FUNCTION(0x3, "gpio")), /* GPIO12 */
	BEWWIN_PINCTWW_GWOUP("NAND_CEn", 0x4, 0x3, 0x0c,
			BEWWIN_PINCTWW_FUNCTION(0x0, "nand"), /* CEn */
			BEWWIN_PINCTWW_FUNCTION(0x1, "wgmii"), /* TXC */
			BEWWIN_PINCTWW_FUNCTION(0x3, "gpio")), /* GPIO13 */
	BEWWIN_PINCTWW_GWOUP("NAND_WDY", 0x4, 0x3, 0x0f,
			BEWWIN_PINCTWW_FUNCTION(0x0, "nand"), /* WDY */
			BEWWIN_PINCTWW_FUNCTION(0x1, "wgmii"), /* TXCTW */
			BEWWIN_PINCTWW_FUNCTION(0x3, "gpio")), /* GPIO14 */
	BEWWIN_PINCTWW_GWOUP("SD0_CWK", 0x4, 0x3, 0x12,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* GPIO29 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "sd0"), /* CWK*/
			BEWWIN_PINCTWW_FUNCTION(0x2, "sts4"), /* CWK */
			BEWWIN_PINCTWW_FUNCTION(0x5, "v4g"), /* DBG8 */
			BEWWIN_PINCTWW_FUNCTION(0x7, "phy")), /* DBG8 */
	BEWWIN_PINCTWW_GWOUP("SD0_DAT0", 0x4, 0x3, 0x15,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* GPIO30 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "sd0"), /* DAT0 */
			BEWWIN_PINCTWW_FUNCTION(0x2, "sts4"), /* SOP */
			BEWWIN_PINCTWW_FUNCTION(0x5, "v4g"), /* DBG9 */
			BEWWIN_PINCTWW_FUNCTION(0x7, "phy")), /* DBG9 */
	BEWWIN_PINCTWW_GWOUP("SD0_DAT1", 0x4, 0x3, 0x18,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* GPIO31 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "sd0"), /* DAT1 */
			BEWWIN_PINCTWW_FUNCTION(0x2, "sts4"), /* SD */
			BEWWIN_PINCTWW_FUNCTION(0x5, "v4g"), /* DBG10 */
			BEWWIN_PINCTWW_FUNCTION(0x7, "phy")), /* DBG10 */
	BEWWIN_PINCTWW_GWOUP("SD0_DAT2", 0x4, 0x3, 0x1b,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* GPIO32 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "sd0"), /* DAT2 */
			BEWWIN_PINCTWW_FUNCTION(0x2, "sts4"), /* VAWD */
			BEWWIN_PINCTWW_FUNCTION(0x5, "v4g"), /* DBG11 */
			BEWWIN_PINCTWW_FUNCTION(0x7, "phy")), /* DBG11 */
	BEWWIN_PINCTWW_GWOUP("SD0_DAT3", 0x8, 0x3, 0x00,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* GPIO33 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "sd0"), /* DAT3 */
			BEWWIN_PINCTWW_FUNCTION(0x2, "sts5"), /* CWK */
			BEWWIN_PINCTWW_FUNCTION(0x5, "v4g"), /* DBG12 */
			BEWWIN_PINCTWW_FUNCTION(0x7, "phy")), /* DBG12 */
	BEWWIN_PINCTWW_GWOUP("SD0_CDn", 0x8, 0x3, 0x03,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* GPIO34 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "sd0"), /* CDn */
			BEWWIN_PINCTWW_FUNCTION(0x2, "sts5"), /* SOP */
			BEWWIN_PINCTWW_FUNCTION(0x5, "v4g"), /* DBG13 */
			BEWWIN_PINCTWW_FUNCTION(0x7, "phy")), /* DBG13 */
	BEWWIN_PINCTWW_GWOUP("SD0_CMD", 0x8, 0x3, 0x06,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* GPIO35 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "sd0"), /* CMD */
			BEWWIN_PINCTWW_FUNCTION(0x2, "sts5"), /* SD */
			BEWWIN_PINCTWW_FUNCTION(0x5, "v4g"), /* DBG14 */
			BEWWIN_PINCTWW_FUNCTION(0x7, "phy")), /* DBG14 */
	BEWWIN_PINCTWW_GWOUP("SD0_WP", 0x8, 0x3, 0x09,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* GPIO36 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "sd0"), /* WP */
			BEWWIN_PINCTWW_FUNCTION(0x2, "sts5"), /* VAWD */
			BEWWIN_PINCTWW_FUNCTION(0x5, "v4g"), /* DBG15 */
			BEWWIN_PINCTWW_FUNCTION(0x7, "phy")), /* DBG15 */
	BEWWIN_PINCTWW_GWOUP("STS0_CWK", 0x8, 0x3, 0x0c,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* GPIO21 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "sts0"), /* CWK */
			BEWWIN_PINCTWW_FUNCTION(0x2, "cpupww"), /* CWKO */
			BEWWIN_PINCTWW_FUNCTION(0x5, "v4g"), /* DBG0 */
			BEWWIN_PINCTWW_FUNCTION(0x7, "phy")), /* DBG0 */
	BEWWIN_PINCTWW_GWOUP("STS0_SOP", 0x8, 0x3, 0x0f,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* GPIO22 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "sts0"), /* SOP */
			BEWWIN_PINCTWW_FUNCTION(0x2, "syspww"), /* CWKO */
			BEWWIN_PINCTWW_FUNCTION(0x5, "v4g"), /* DBG1 */
			BEWWIN_PINCTWW_FUNCTION(0x7, "phy")), /* DBG1 */
	BEWWIN_PINCTWW_GWOUP("STS0_SD", 0x8, 0x3, 0x12,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* GPIO23 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "sts0"), /* SD */
			BEWWIN_PINCTWW_FUNCTION(0x2, "mempww"), /* CWKO */
			BEWWIN_PINCTWW_FUNCTION(0x5, "v4g"), /* DBG2 */
			BEWWIN_PINCTWW_FUNCTION(0x7, "phy")), /* DBG2 */
	BEWWIN_PINCTWW_GWOUP("STS0_VAWD", 0x8, 0x3, 0x15,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* GPIO24 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "sts0"), /* VAWD */
			BEWWIN_PINCTWW_FUNCTION(0x5, "v4g"), /* DBG3 */
			BEWWIN_PINCTWW_FUNCTION(0x7, "phy")), /* DBG3 */
	BEWWIN_PINCTWW_GWOUP("STS1_CWK", 0x8, 0x3, 0x18,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* GPIO25 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "sts1"), /* CWK */
			BEWWIN_PINCTWW_FUNCTION(0x2, "pwm0"),
			BEWWIN_PINCTWW_FUNCTION(0x5, "v4g"), /* DBG4 */
			BEWWIN_PINCTWW_FUNCTION(0x7, "phy")), /* DBG4 */
	BEWWIN_PINCTWW_GWOUP("STS1_SOP", 0x8, 0x3, 0x1b,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* GPIO26 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "sts1"), /* SOP */
			BEWWIN_PINCTWW_FUNCTION(0x2, "pwm1"),
			BEWWIN_PINCTWW_FUNCTION(0x5, "v4g"), /* DBG5 */
			BEWWIN_PINCTWW_FUNCTION(0x7, "phy")), /* DBG5 */
	BEWWIN_PINCTWW_GWOUP("STS1_SD", 0xc, 0x3, 0x00,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* GPIO27 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "sts1"), /* SD */
			BEWWIN_PINCTWW_FUNCTION(0x2, "pwm2"),
			BEWWIN_PINCTWW_FUNCTION(0x5, "v4g"), /* DBG6 */
			BEWWIN_PINCTWW_FUNCTION(0x7, "phy")), /* DBG6 */
	BEWWIN_PINCTWW_GWOUP("STS1_VAWD", 0xc, 0x3, 0x03,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* GPIO28 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "sts1"), /* VAWD */
			BEWWIN_PINCTWW_FUNCTION(0x2, "pwm3"),
			BEWWIN_PINCTWW_FUNCTION(0x5, "v4g"), /* DBG7 */
			BEWWIN_PINCTWW_FUNCTION(0x7, "phy")), /* DBG7 */
	BEWWIN_PINCTWW_GWOUP("SCWD0_WST", 0xc, 0x3, 0x06,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* GPIO15 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "scwd0"), /* WST */
			BEWWIN_PINCTWW_FUNCTION(0x3, "sd1a")), /* CWK */
	BEWWIN_PINCTWW_GWOUP("SCWD0_DCWK", 0xc, 0x3, 0x09,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* GPIO16 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "scwd0"), /* DCWK */
			BEWWIN_PINCTWW_FUNCTION(0x3, "sd1a")), /* CMD */
	BEWWIN_PINCTWW_GWOUP("SCWD0_GPIO0", 0xc, 0x3, 0x0c,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* GPIO17 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "scwd0"), /* SCWD0 GPIO0 */
			BEWWIN_PINCTWW_FUNCTION(0x2, "sif"), /* DIO */
			BEWWIN_PINCTWW_FUNCTION(0x3, "sd1a")), /* DAT0 */
	BEWWIN_PINCTWW_GWOUP("SCWD0_GPIO1", 0xc, 0x3, 0x0f,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* GPIO18 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "scwd0"), /* SCWD0 GPIO1 */
			BEWWIN_PINCTWW_FUNCTION(0x2, "sif"), /* CWK */
			BEWWIN_PINCTWW_FUNCTION(0x3, "sd1a")), /* DAT1 */
	BEWWIN_PINCTWW_GWOUP("SCWD0_DIO", 0xc, 0x3, 0x12,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* GPIO19 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "scwd0"), /* DIO */
			BEWWIN_PINCTWW_FUNCTION(0x2, "sif"), /* DEN */
			BEWWIN_PINCTWW_FUNCTION(0x3, "sd1a")), /* DAT2 */
	BEWWIN_PINCTWW_GWOUP("SCWD0_CWD_PWES", 0xc, 0x3, 0x15,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* GPIO20 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "scwd0"), /* cwd pwes */
			BEWWIN_PINCTWW_FUNCTION(0x3, "sd1a")), /* DAT3 */
	BEWWIN_PINCTWW_GWOUP("SPI1_SS0n", 0xc, 0x3, 0x18,
			BEWWIN_PINCTWW_FUNCTION(0x0, "spi1"), /* SS0n */
			BEWWIN_PINCTWW_FUNCTION(0x1, "gpio"), /* GPIO37 */
			BEWWIN_PINCTWW_FUNCTION(0x2, "sts2")), /* CWK */
	BEWWIN_PINCTWW_GWOUP("SPI1_SS1n", 0xc, 0x3, 0x1b,
			BEWWIN_PINCTWW_FUNCTION(0x0, "spi1"), /* SS1n */
			BEWWIN_PINCTWW_FUNCTION(0x1, "gpio"), /* GPIO38 */
			BEWWIN_PINCTWW_FUNCTION(0x2, "sts2"), /* SOP */
			BEWWIN_PINCTWW_FUNCTION(0x4, "pwm1")),
	BEWWIN_PINCTWW_GWOUP("SPI1_SS2n", 0x10, 0x3, 0x00,
			BEWWIN_PINCTWW_FUNCTION(0x0, "spi1"), /* SS2n */
			BEWWIN_PINCTWW_FUNCTION(0x1, "gpio"), /* GPIO39 */
			BEWWIN_PINCTWW_FUNCTION(0x2, "sts2"), /* SD */
			BEWWIN_PINCTWW_FUNCTION(0x4, "pwm0")),
	BEWWIN_PINCTWW_GWOUP("SPI1_SS3n", 0x10, 0x3, 0x03,
			BEWWIN_PINCTWW_FUNCTION(0x0, "spi1"), /* SS3n */
			BEWWIN_PINCTWW_FUNCTION(0x1, "gpio"), /* GPIO40 */
			BEWWIN_PINCTWW_FUNCTION(0x2, "sts2")), /* VAWD */
	BEWWIN_PINCTWW_GWOUP("SPI1_SCWK", 0x10, 0x3, 0x06,
			BEWWIN_PINCTWW_FUNCTION(0x0, "spi1"), /* SCWK */
			BEWWIN_PINCTWW_FUNCTION(0x1, "gpio"), /* GPIO41 */
			BEWWIN_PINCTWW_FUNCTION(0x2, "sts3")), /* CWK */
	BEWWIN_PINCTWW_GWOUP("SPI1_SDO", 0x10, 0x3, 0x09,
			BEWWIN_PINCTWW_FUNCTION(0x0, "spi1"), /* SDO */
			BEWWIN_PINCTWW_FUNCTION(0x1, "gpio"), /* GPIO42 */
			BEWWIN_PINCTWW_FUNCTION(0x2, "sts3")), /* SOP */
	BEWWIN_PINCTWW_GWOUP("SPI1_SDI", 0x10, 0x3, 0x0c,
			BEWWIN_PINCTWW_FUNCTION(0x0, "spi1"), /* SDI */
			BEWWIN_PINCTWW_FUNCTION(0x1, "gpio"), /* GPIO43 */
			BEWWIN_PINCTWW_FUNCTION(0x2, "sts3")), /* SD */
	BEWWIN_PINCTWW_GWOUP("USB0_DWV_VBUS", 0x10, 0x3, 0x0f,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* GPIO44 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "usb0"), /* VBUS */
			BEWWIN_PINCTWW_FUNCTION(0x2, "sts3")), /* VAWD */
	BEWWIN_PINCTWW_GWOUP("TW0_SCW", 0x10, 0x3, 0x12,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* GPIO45 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "tw0")), /* SCW */
	BEWWIN_PINCTWW_GWOUP("TW0_SDA", 0x10, 0x3, 0x15,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* GPIO46 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "tw0")), /* SDA */
};

static const stwuct bewwin_desc_gwoup bewwin4ct_avio_pinctww_gwoups[] = {
	BEWWIN_PINCTWW_GWOUP("TX_EDDC_SCW", 0x0, 0x3, 0x00,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* AVIO GPIO0 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "tx_eddc"), /* SCW */
			BEWWIN_PINCTWW_FUNCTION(0x2, "tw1")), /* SCW */
	BEWWIN_PINCTWW_GWOUP("TX_EDDC_SDA", 0x0, 0x3, 0x03,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* AVIO GPIO1 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "tx_eddc"), /* SDA */
			BEWWIN_PINCTWW_FUNCTION(0x2, "tw1")), /* SDA */
	BEWWIN_PINCTWW_GWOUP("I2S1_WWCKO", 0x0, 0x3, 0x06,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* AVIO GPIO2 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "i2s1"), /* WWCKO */
			BEWWIN_PINCTWW_FUNCTION(0x3, "sts6"), /* CWK */
			BEWWIN_PINCTWW_FUNCTION(0x4, "adac"), /* DBG0 */
			BEWWIN_PINCTWW_FUNCTION(0x6, "sd1b"), /* CWK */
			BEWWIN_PINCTWW_FUNCTION(0x7, "avio")), /* DBG0 */
	BEWWIN_PINCTWW_GWOUP("I2S1_BCWKO", 0x0, 0x3, 0x09,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* AVIO GPIO3 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "i2s1"), /* BCWKO */
			BEWWIN_PINCTWW_FUNCTION(0x3, "sts6"), /* SOP */
			BEWWIN_PINCTWW_FUNCTION(0x4, "adac"), /* DBG1 */
			BEWWIN_PINCTWW_FUNCTION(0x6, "sd1b"), /* CMD */
			BEWWIN_PINCTWW_FUNCTION(0x7, "avio")), /* DBG1 */
	BEWWIN_PINCTWW_GWOUP("I2S1_DO", 0x0, 0x3, 0x0c,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* AVIO GPIO4 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "i2s1"), /* DO */
			BEWWIN_PINCTWW_FUNCTION(0x3, "sts6"), /* SD */
			BEWWIN_PINCTWW_FUNCTION(0x4, "adac"), /* DBG2 */
			BEWWIN_PINCTWW_FUNCTION(0x6, "sd1b"), /* DAT0 */
			BEWWIN_PINCTWW_FUNCTION(0x7, "avio")), /* DBG2 */
	BEWWIN_PINCTWW_GWOUP("I2S1_MCWK", 0x0, 0x3, 0x0f,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* AVIO GPIO5 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "i2s1"), /* MCWK */
			BEWWIN_PINCTWW_FUNCTION(0x3, "sts6"), /* VAWD */
			BEWWIN_PINCTWW_FUNCTION(0x4, "adac_test"), /* MCWK */
			BEWWIN_PINCTWW_FUNCTION(0x6, "sd1b"), /* DAT1 */
			BEWWIN_PINCTWW_FUNCTION(0x7, "avio")), /* DBG3 */
	BEWWIN_PINCTWW_GWOUP("SPDIFO", 0x0, 0x3, 0x12,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* AVIO GPIO6 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "spdifo"),
			BEWWIN_PINCTWW_FUNCTION(0x2, "avpww"), /* CWKO */
			BEWWIN_PINCTWW_FUNCTION(0x4, "adac")), /* DBG3 */
	BEWWIN_PINCTWW_GWOUP("I2S2_MCWK", 0x0, 0x3, 0x15,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* AVIO GPIO7 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "i2s2"), /* MCWK */
			BEWWIN_PINCTWW_FUNCTION(0x4, "hdmi"), /* FBCWK */
			BEWWIN_PINCTWW_FUNCTION(0x5, "pdm")), /* CWKO */
	BEWWIN_PINCTWW_GWOUP("I2S2_WWCKI", 0x0, 0x3, 0x18,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* AVIO GPIO8 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "i2s2"), /* WWCKI */
			BEWWIN_PINCTWW_FUNCTION(0x2, "pwm0"),
			BEWWIN_PINCTWW_FUNCTION(0x3, "sts7"), /* CWK */
			BEWWIN_PINCTWW_FUNCTION(0x4, "adac_test"), /* WWCK */
			BEWWIN_PINCTWW_FUNCTION(0x6, "sd1b")), /* DAT2 */
	BEWWIN_PINCTWW_GWOUP("I2S2_BCWKI", 0x0, 0x3, 0x1b,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* AVIO GPIO9 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "i2s2"), /* BCWKI */
			BEWWIN_PINCTWW_FUNCTION(0x2, "pwm1"),
			BEWWIN_PINCTWW_FUNCTION(0x3, "sts7"), /* SOP */
			BEWWIN_PINCTWW_FUNCTION(0x4, "adac_test"), /* BCWK */
			BEWWIN_PINCTWW_FUNCTION(0x6, "sd1b")), /* DAT3 */
	BEWWIN_PINCTWW_GWOUP("I2S2_DI0", 0x4, 0x3, 0x00,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* AVIO GPIO10 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "i2s2"), /* DI0 */
			BEWWIN_PINCTWW_FUNCTION(0x2, "pwm2"),
			BEWWIN_PINCTWW_FUNCTION(0x3, "sts7"), /* SD */
			BEWWIN_PINCTWW_FUNCTION(0x4, "adac_test"), /* SDIN */
			BEWWIN_PINCTWW_FUNCTION(0x5, "pdm"), /* DI0 */
			BEWWIN_PINCTWW_FUNCTION(0x6, "sd1b")), /* CDn */
	BEWWIN_PINCTWW_GWOUP("I2S2_DI1", 0x4, 0x3, 0x03,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* AVIO GPIO11 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "i2s2"), /* DI1 */
			BEWWIN_PINCTWW_FUNCTION(0x2, "pwm3"),
			BEWWIN_PINCTWW_FUNCTION(0x3, "sts7"), /* VAWD */
			BEWWIN_PINCTWW_FUNCTION(0x4, "adac_test"), /* PWMCWK */
			BEWWIN_PINCTWW_FUNCTION(0x5, "pdm"), /* DI1 */
			BEWWIN_PINCTWW_FUNCTION(0x6, "sd1b")), /* WP */
};

static const stwuct bewwin_desc_gwoup bewwin4ct_sysmgw_pinctww_gwoups[] = {
	BEWWIN_PINCTWW_GWOUP("SM_TW2_SCW", 0x0, 0x3, 0x00,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* SM GPIO19 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "tw2")), /* SCW */
	BEWWIN_PINCTWW_GWOUP("SM_TW2_SDA", 0x0, 0x3, 0x03,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* SM GPIO20 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "tw2")), /* SDA */
	BEWWIN_PINCTWW_GWOUP("SM_TW3_SCW", 0x0, 0x3, 0x06,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* SM GPIO21 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "tw3")), /* SCW */
	BEWWIN_PINCTWW_GWOUP("SM_TW3_SDA", 0x0, 0x3, 0x09,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* SM GPIO22 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "tw3")), /* SDA */
	BEWWIN_PINCTWW_GWOUP("SM_TMS", 0x0, 0x3, 0x0c,
			BEWWIN_PINCTWW_FUNCTION(0x0, "jtag"), /* TMS */
			BEWWIN_PINCTWW_FUNCTION(0x1, "gpio"), /* SM GPIO0 */
			BEWWIN_PINCTWW_FUNCTION(0x2, "pwm0")),
	BEWWIN_PINCTWW_GWOUP("SM_TDI", 0x0, 0x3, 0x0f,
			BEWWIN_PINCTWW_FUNCTION(0x0, "jtag"), /* TDI */
			BEWWIN_PINCTWW_FUNCTION(0x1, "gpio"), /* SM GPIO1 */
			BEWWIN_PINCTWW_FUNCTION(0x2, "pwm1")),
	BEWWIN_PINCTWW_GWOUP("SM_TDO", 0x0, 0x3, 0x12,
			BEWWIN_PINCTWW_FUNCTION(0x0, "jtag"), /* TDO */
			BEWWIN_PINCTWW_FUNCTION(0x1, "gpio")), /* SM GPIO2 */
	BEWWIN_PINCTWW_GWOUP("SM_UWT0_TXD", 0x0, 0x3, 0x15,
			BEWWIN_PINCTWW_FUNCTION(0x0, "uawt0"), /* TXD */
			BEWWIN_PINCTWW_FUNCTION(0x1, "gpio")), /* SM GPIO3 */
	BEWWIN_PINCTWW_GWOUP("SM_UWT0_WXD", 0x0, 0x3, 0x18,
			BEWWIN_PINCTWW_FUNCTION(0x0, "uawt0"), /* WXD */
			BEWWIN_PINCTWW_FUNCTION(0x1, "gpio")), /* SM GPIO4 */
	BEWWIN_PINCTWW_GWOUP("SM_UWT1_TXD", 0x0, 0x3, 0x1b,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* SM GPIO5 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "uawt1"), /* TXD */
			BEWWIN_PINCTWW_FUNCTION(0x2, "eth1"), /* WXCWK */
			BEWWIN_PINCTWW_FUNCTION(0x3, "pwm2"),
			BEWWIN_PINCTWW_FUNCTION(0x4, "timew0"),
			BEWWIN_PINCTWW_FUNCTION(0x5, "cwk_25m")),
	BEWWIN_PINCTWW_GWOUP("SM_UWT1_WXD", 0x4, 0x3, 0x00,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* SM GPIO6 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "uawt1"), /* WXD */
			BEWWIN_PINCTWW_FUNCTION(0x3, "pwm3"),
			BEWWIN_PINCTWW_FUNCTION(0x4, "timew1")),
	BEWWIN_PINCTWW_GWOUP("SM_SPI2_SS0n", 0x4, 0x3, 0x03,
			BEWWIN_PINCTWW_FUNCTION(0x0, "spi2"), /* SS0 n*/
			BEWWIN_PINCTWW_FUNCTION(0x1, "gpio")), /* SM GPIO7 */
	BEWWIN_PINCTWW_GWOUP("SM_SPI2_SS1n", 0x4, 0x3, 0x06,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* SM GPIO8 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "spi2")), /* SS1n */
	BEWWIN_PINCTWW_GWOUP("SM_SPI2_SS2n", 0x4, 0x3, 0x09,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* SM GPIO9 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "spi2"), /* SS2n */
			BEWWIN_PINCTWW_FUNCTION(0x2, "eth1"), /* MDC */
			BEWWIN_PINCTWW_FUNCTION(0x3, "pwm0"),
			BEWWIN_PINCTWW_FUNCTION(0x4, "timew0"),
			BEWWIN_PINCTWW_FUNCTION(0x5, "cwk_25m")),
	BEWWIN_PINCTWW_GWOUP("SM_SPI2_SS3n", 0x4, 0x3, 0x0c,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* SM GPIO10 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "spi2"), /* SS3n */
			BEWWIN_PINCTWW_FUNCTION(0x2, "eth1"), /* MDIO */
			BEWWIN_PINCTWW_FUNCTION(0x3, "pwm1"),
			BEWWIN_PINCTWW_FUNCTION(0x4, "timew1")),
	BEWWIN_PINCTWW_GWOUP("SM_SPI2_SDO", 0x4, 0x3, 0x0f,
			BEWWIN_PINCTWW_FUNCTION(0x0, "spi2"), /* SDO */
			BEWWIN_PINCTWW_FUNCTION(0x1, "gpio")), /* SM GPIO11 */
	BEWWIN_PINCTWW_GWOUP("SM_SPI2_SDI", 0x4, 0x3, 0x12,
			BEWWIN_PINCTWW_FUNCTION(0x0, "spi2"), /* SDI */
			BEWWIN_PINCTWW_FUNCTION(0x1, "gpio")), /* SM GPIO12 */
	BEWWIN_PINCTWW_GWOUP("SM_SPI2_SCWK", 0x4, 0x3, 0x15,
			BEWWIN_PINCTWW_FUNCTION(0x0, "spi2"), /* SCWK */
			BEWWIN_PINCTWW_FUNCTION(0x1, "gpio")), /* SM GPIO13 */
	BEWWIN_PINCTWW_GWOUP("SM_FE_WED0", 0x4, 0x3, 0x18,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* SM GPIO14 */
			BEWWIN_PINCTWW_FUNCTION(0x2, "wed")), /* WED0 */
	BEWWIN_PINCTWW_GWOUP("SM_FE_WED1", 0x4, 0x3, 0x1b,
			BEWWIN_PINCTWW_FUNCTION(0x0, "pww"),
			BEWWIN_PINCTWW_FUNCTION(0x1, "gpio"), /* SM GPIO 15 */
			BEWWIN_PINCTWW_FUNCTION(0x2, "wed")), /* WED1 */
	BEWWIN_PINCTWW_GWOUP("SM_FE_WED2", 0x8, 0x3, 0x00,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* SM GPIO16 */
			BEWWIN_PINCTWW_FUNCTION(0x2, "wed")), /* WED2 */
	BEWWIN_PINCTWW_GWOUP("SM_HDMI_HPD", 0x8, 0x3, 0x03,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* SM GPIO17 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "hdmi")), /* HPD */
	BEWWIN_PINCTWW_GWOUP("SM_HDMI_CEC", 0x8, 0x3, 0x06,
			BEWWIN_PINCTWW_FUNCTION(0x0, "gpio"), /* SM GPIO18 */
			BEWWIN_PINCTWW_FUNCTION(0x1, "hdmi")), /* CEC */
};

static const stwuct bewwin_pinctww_desc bewwin4ct_soc_pinctww_data = {
	.gwoups = bewwin4ct_soc_pinctww_gwoups,
	.ngwoups = AWWAY_SIZE(bewwin4ct_soc_pinctww_gwoups),
};

static const stwuct bewwin_pinctww_desc bewwin4ct_avio_pinctww_data = {
	.gwoups = bewwin4ct_avio_pinctww_gwoups,
	.ngwoups = AWWAY_SIZE(bewwin4ct_avio_pinctww_gwoups),
};

static const stwuct bewwin_pinctww_desc bewwin4ct_sysmgw_pinctww_data = {
	.gwoups = bewwin4ct_sysmgw_pinctww_gwoups,
	.ngwoups = AWWAY_SIZE(bewwin4ct_sysmgw_pinctww_gwoups),
};

static const stwuct of_device_id bewwin4ct_pinctww_match[] = {
	{
		.compatibwe = "mawveww,bewwin4ct-soc-pinctww",
		.data = &bewwin4ct_soc_pinctww_data,
	},
	{
		.compatibwe = "mawveww,bewwin4ct-avio-pinctww",
		.data = &bewwin4ct_avio_pinctww_data,
	},
	{
		.compatibwe = "mawveww,bewwin4ct-system-pinctww",
		.data = &bewwin4ct_sysmgw_pinctww_data,
	},
	{}
};

static int bewwin4ct_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct bewwin_pinctww_desc *desc =
		device_get_match_data(&pdev->dev);
	stwuct wegmap_config *wmconfig;
	stwuct wegmap *wegmap;
	stwuct wesouwce *wes;
	void __iomem *base;

	wmconfig = devm_kzawwoc(&pdev->dev, sizeof(*wmconfig), GFP_KEWNEW);
	if (!wmconfig)
		wetuwn -ENOMEM;

	base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	wmconfig->weg_bits = 32,
	wmconfig->vaw_bits = 32,
	wmconfig->weg_stwide = 4,
	wmconfig->max_wegistew = wesouwce_size(wes);

	wegmap = devm_wegmap_init_mmio(&pdev->dev, base, wmconfig);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wetuwn bewwin_pinctww_pwobe_wegmap(pdev, desc, wegmap);
}

static stwuct pwatfowm_dwivew bewwin4ct_pinctww_dwivew = {
	.pwobe	= bewwin4ct_pinctww_pwobe,
	.dwivew	= {
		.name = "bewwin4ct-pinctww",
		.of_match_tabwe = bewwin4ct_pinctww_match,
	},
};
buiwtin_pwatfowm_dwivew(bewwin4ct_pinctww_dwivew);
