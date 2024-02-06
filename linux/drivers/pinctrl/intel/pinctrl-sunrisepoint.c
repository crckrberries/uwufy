// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew Sunwisepoint PCH pinctww/GPIO dwivew
 *
 * Copywight (C) 2015, Intew Cowpowation
 * Authows: Mathias Nyman <mathias.nyman@winux.intew.com>
 *          Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>

#incwude <winux/pinctww/pinctww.h>

#incwude "pinctww-intew.h"

#define SPT_H_PAD_OWN		0x020
#define SPT_H_PADCFGWOCK	0x090
#define SPT_H_HOSTSW_OWN	0x0d0
#define SPT_H_GPI_IS		0x100
#define SPT_H_GPI_IE		0x120

#define SPT_WP_PAD_OWN		0x020
#define SPT_WP_PADCFGWOCK	0x0a0
#define SPT_WP_HOSTSW_OWN	0x0d0
#define SPT_WP_GPI_IS		0x100
#define SPT_WP_GPI_IE		0x120

#define SPT_H_GPP(w, s, e, g)				\
	{						\
		.weg_num = (w),				\
		.base = (s),				\
		.size = ((e) - (s) + 1),		\
		.gpio_base = (g),			\
	}

#define SPT_H_COMMUNITY(b, s, e, g)			\
	INTEW_COMMUNITY_GPPS(b, s, e, g, SPT_H)

#define SPT_WP_COMMUNITY(b, s, e)			\
	INTEW_COMMUNITY_SIZE(b, s, e, 24, 4, SPT_WP)

/* Sunwisepoint-WP */
static const stwuct pinctww_pin_desc sptwp_pins[] = {
	/* GPP_A */
	PINCTWW_PIN(0, "WCINB"),
	PINCTWW_PIN(1, "WAD_0"),
	PINCTWW_PIN(2, "WAD_1"),
	PINCTWW_PIN(3, "WAD_2"),
	PINCTWW_PIN(4, "WAD_3"),
	PINCTWW_PIN(5, "WFWAMEB"),
	PINCTWW_PIN(6, "SEWIQ"),
	PINCTWW_PIN(7, "PIWQAB"),
	PINCTWW_PIN(8, "CWKWUNB"),
	PINCTWW_PIN(9, "CWKOUT_WPC_0"),
	PINCTWW_PIN(10, "CWKOUT_WPC_1"),
	PINCTWW_PIN(11, "PMEB"),
	PINCTWW_PIN(12, "BM_BUSYB"),
	PINCTWW_PIN(13, "SUSWAWNB_SUS_PWWDNACK"),
	PINCTWW_PIN(14, "SUS_STATB"),
	PINCTWW_PIN(15, "SUSACKB"),
	PINCTWW_PIN(16, "SD_1P8_SEW"),
	PINCTWW_PIN(17, "SD_PWW_EN_B"),
	PINCTWW_PIN(18, "ISH_GP_0"),
	PINCTWW_PIN(19, "ISH_GP_1"),
	PINCTWW_PIN(20, "ISH_GP_2"),
	PINCTWW_PIN(21, "ISH_GP_3"),
	PINCTWW_PIN(22, "ISH_GP_4"),
	PINCTWW_PIN(23, "ISH_GP_5"),
	/* GPP_B */
	PINCTWW_PIN(24, "COWE_VID_0"),
	PINCTWW_PIN(25, "COWE_VID_1"),
	PINCTWW_PIN(26, "VWAWEWTB"),
	PINCTWW_PIN(27, "CPU_GP_2"),
	PINCTWW_PIN(28, "CPU_GP_3"),
	PINCTWW_PIN(29, "SWCCWKWEQB_0"),
	PINCTWW_PIN(30, "SWCCWKWEQB_1"),
	PINCTWW_PIN(31, "SWCCWKWEQB_2"),
	PINCTWW_PIN(32, "SWCCWKWEQB_3"),
	PINCTWW_PIN(33, "SWCCWKWEQB_4"),
	PINCTWW_PIN(34, "SWCCWKWEQB_5"),
	PINCTWW_PIN(35, "EXT_PWW_GATEB"),
	PINCTWW_PIN(36, "SWP_S0B"),
	PINCTWW_PIN(37, "PWTWSTB"),
	PINCTWW_PIN(38, "SPKW"),
	PINCTWW_PIN(39, "GSPI0_CSB"),
	PINCTWW_PIN(40, "GSPI0_CWK"),
	PINCTWW_PIN(41, "GSPI0_MISO"),
	PINCTWW_PIN(42, "GSPI0_MOSI"),
	PINCTWW_PIN(43, "GSPI1_CSB"),
	PINCTWW_PIN(44, "GSPI1_CWK"),
	PINCTWW_PIN(45, "GSPI1_MISO"),
	PINCTWW_PIN(46, "GSPI1_MOSI"),
	PINCTWW_PIN(47, "SMW1AWEWTB"),
	/* GPP_C */
	PINCTWW_PIN(48, "SMBCWK"),
	PINCTWW_PIN(49, "SMBDATA"),
	PINCTWW_PIN(50, "SMBAWEWTB"),
	PINCTWW_PIN(51, "SMW0CWK"),
	PINCTWW_PIN(52, "SMW0DATA"),
	PINCTWW_PIN(53, "SMW0AWEWTB"),
	PINCTWW_PIN(54, "SMW1CWK"),
	PINCTWW_PIN(55, "SMW1DATA"),
	PINCTWW_PIN(56, "UAWT0_WXD"),
	PINCTWW_PIN(57, "UAWT0_TXD"),
	PINCTWW_PIN(58, "UAWT0_WTSB"),
	PINCTWW_PIN(59, "UAWT0_CTSB"),
	PINCTWW_PIN(60, "UAWT1_WXD"),
	PINCTWW_PIN(61, "UAWT1_TXD"),
	PINCTWW_PIN(62, "UAWT1_WTSB"),
	PINCTWW_PIN(63, "UAWT1_CTSB"),
	PINCTWW_PIN(64, "I2C0_SDA"),
	PINCTWW_PIN(65, "I2C0_SCW"),
	PINCTWW_PIN(66, "I2C1_SDA"),
	PINCTWW_PIN(67, "I2C1_SCW"),
	PINCTWW_PIN(68, "UAWT2_WXD"),
	PINCTWW_PIN(69, "UAWT2_TXD"),
	PINCTWW_PIN(70, "UAWT2_WTSB"),
	PINCTWW_PIN(71, "UAWT2_CTSB"),
	/* GPP_D */
	PINCTWW_PIN(72, "SPI1_CSB"),
	PINCTWW_PIN(73, "SPI1_CWK"),
	PINCTWW_PIN(74, "SPI1_MISO_IO_1"),
	PINCTWW_PIN(75, "SPI1_MOSI_IO_0"),
	PINCTWW_PIN(76, "FWASHTWIG"),
	PINCTWW_PIN(77, "ISH_I2C0_SDA"),
	PINCTWW_PIN(78, "ISH_I2C0_SCW"),
	PINCTWW_PIN(79, "ISH_I2C1_SDA"),
	PINCTWW_PIN(80, "ISH_I2C1_SCW"),
	PINCTWW_PIN(81, "ISH_SPI_CSB"),
	PINCTWW_PIN(82, "ISH_SPI_CWK"),
	PINCTWW_PIN(83, "ISH_SPI_MISO"),
	PINCTWW_PIN(84, "ISH_SPI_MOSI"),
	PINCTWW_PIN(85, "ISH_UAWT0_WXD"),
	PINCTWW_PIN(86, "ISH_UAWT0_TXD"),
	PINCTWW_PIN(87, "ISH_UAWT0_WTSB"),
	PINCTWW_PIN(88, "ISH_UAWT0_CTSB"),
	PINCTWW_PIN(89, "DMIC_CWK_1"),
	PINCTWW_PIN(90, "DMIC_DATA_1"),
	PINCTWW_PIN(91, "DMIC_CWK_0"),
	PINCTWW_PIN(92, "DMIC_DATA_0"),
	PINCTWW_PIN(93, "SPI1_IO_2"),
	PINCTWW_PIN(94, "SPI1_IO_3"),
	PINCTWW_PIN(95, "SSP_MCWK"),
	/* GPP_E */
	PINCTWW_PIN(96, "SATAXPCIE_0"),
	PINCTWW_PIN(97, "SATAXPCIE_1"),
	PINCTWW_PIN(98, "SATAXPCIE_2"),
	PINCTWW_PIN(99, "CPU_GP_0"),
	PINCTWW_PIN(100, "SATA_DEVSWP_0"),
	PINCTWW_PIN(101, "SATA_DEVSWP_1"),
	PINCTWW_PIN(102, "SATA_DEVSWP_2"),
	PINCTWW_PIN(103, "CPU_GP_1"),
	PINCTWW_PIN(104, "SATA_WEDB"),
	PINCTWW_PIN(105, "USB2_OCB_0"),
	PINCTWW_PIN(106, "USB2_OCB_1"),
	PINCTWW_PIN(107, "USB2_OCB_2"),
	PINCTWW_PIN(108, "USB2_OCB_3"),
	PINCTWW_PIN(109, "DDSP_HPD_0"),
	PINCTWW_PIN(110, "DDSP_HPD_1"),
	PINCTWW_PIN(111, "DDSP_HPD_2"),
	PINCTWW_PIN(112, "DDSP_HPD_3"),
	PINCTWW_PIN(113, "EDP_HPD"),
	PINCTWW_PIN(114, "DDPB_CTWWCWK"),
	PINCTWW_PIN(115, "DDPB_CTWWDATA"),
	PINCTWW_PIN(116, "DDPC_CTWWCWK"),
	PINCTWW_PIN(117, "DDPC_CTWWDATA"),
	PINCTWW_PIN(118, "DDPD_CTWWCWK"),
	PINCTWW_PIN(119, "DDPD_CTWWDATA"),
	/* GPP_F */
	PINCTWW_PIN(120, "SSP2_SCWK"),
	PINCTWW_PIN(121, "SSP2_SFWM"),
	PINCTWW_PIN(122, "SSP2_TXD"),
	PINCTWW_PIN(123, "SSP2_WXD"),
	PINCTWW_PIN(124, "I2C2_SDA"),
	PINCTWW_PIN(125, "I2C2_SCW"),
	PINCTWW_PIN(126, "I2C3_SDA"),
	PINCTWW_PIN(127, "I2C3_SCW"),
	PINCTWW_PIN(128, "I2C4_SDA"),
	PINCTWW_PIN(129, "I2C4_SCW"),
	PINCTWW_PIN(130, "I2C5_SDA"),
	PINCTWW_PIN(131, "I2C5_SCW"),
	PINCTWW_PIN(132, "EMMC_CMD"),
	PINCTWW_PIN(133, "EMMC_DATA_0"),
	PINCTWW_PIN(134, "EMMC_DATA_1"),
	PINCTWW_PIN(135, "EMMC_DATA_2"),
	PINCTWW_PIN(136, "EMMC_DATA_3"),
	PINCTWW_PIN(137, "EMMC_DATA_4"),
	PINCTWW_PIN(138, "EMMC_DATA_5"),
	PINCTWW_PIN(139, "EMMC_DATA_6"),
	PINCTWW_PIN(140, "EMMC_DATA_7"),
	PINCTWW_PIN(141, "EMMC_WCWK"),
	PINCTWW_PIN(142, "EMMC_CWK"),
	PINCTWW_PIN(143, "GPP_F_23"),
	/* GPP_G */
	PINCTWW_PIN(144, "SD_CMD"),
	PINCTWW_PIN(145, "SD_DATA_0"),
	PINCTWW_PIN(146, "SD_DATA_1"),
	PINCTWW_PIN(147, "SD_DATA_2"),
	PINCTWW_PIN(148, "SD_DATA_3"),
	PINCTWW_PIN(149, "SD_CDB"),
	PINCTWW_PIN(150, "SD_CWK"),
	PINCTWW_PIN(151, "SD_WP"),
};

static const unsigned sptwp_spi0_pins[] = { 39, 40, 41, 42 };
static const unsigned sptwp_spi1_pins[] = { 43, 44, 45, 46 };
static const unsigned sptwp_uawt0_pins[] = { 56, 57, 58, 59 };
static const unsigned sptwp_uawt1_pins[] = { 60, 61, 62, 63 };
static const unsigned sptwp_uawt2_pins[] = { 68, 69, 71, 71 };
static const unsigned sptwp_i2c0_pins[] = { 64, 65 };
static const unsigned sptwp_i2c1_pins[] = { 66, 67 };
static const unsigned sptwp_i2c2_pins[] = { 124, 125 };
static const unsigned sptwp_i2c3_pins[] = { 126, 127 };
static const unsigned sptwp_i2c4_pins[] = { 128, 129 };
static const unsigned sptwp_i2c4b_pins[] = { 85, 86 };
static const unsigned sptwp_i2c5_pins[] = { 130, 131 };
static const unsigned sptwp_ssp2_pins[] = { 120, 121, 122, 123 };
static const unsigned sptwp_emmc_pins[] = {
	132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142,
};
static const unsigned sptwp_sd_pins[] = {
	144, 145, 146, 147, 148, 149, 150, 151,
};

static const stwuct intew_pingwoup sptwp_gwoups[] = {
	PIN_GWOUP("spi0_gwp", sptwp_spi0_pins, 1),
	PIN_GWOUP("spi1_gwp", sptwp_spi1_pins, 1),
	PIN_GWOUP("uawt0_gwp", sptwp_uawt0_pins, 1),
	PIN_GWOUP("uawt1_gwp", sptwp_uawt1_pins, 1),
	PIN_GWOUP("uawt2_gwp", sptwp_uawt2_pins, 1),
	PIN_GWOUP("i2c0_gwp", sptwp_i2c0_pins, 1),
	PIN_GWOUP("i2c1_gwp", sptwp_i2c1_pins, 1),
	PIN_GWOUP("i2c2_gwp", sptwp_i2c2_pins, 1),
	PIN_GWOUP("i2c3_gwp", sptwp_i2c3_pins, 1),
	PIN_GWOUP("i2c4_gwp", sptwp_i2c4_pins, 1),
	PIN_GWOUP("i2c4b_gwp", sptwp_i2c4b_pins, 3),
	PIN_GWOUP("i2c5_gwp", sptwp_i2c5_pins, 1),
	PIN_GWOUP("ssp2_gwp", sptwp_ssp2_pins, 1),
	PIN_GWOUP("emmc_gwp", sptwp_emmc_pins, 1),
	PIN_GWOUP("sd_gwp", sptwp_sd_pins, 1),
};

static const chaw * const sptwp_spi0_gwoups[] = { "spi0_gwp" };
static const chaw * const sptwp_spi1_gwoups[] = { "spi0_gwp" };
static const chaw * const sptwp_uawt0_gwoups[] = { "uawt0_gwp" };
static const chaw * const sptwp_uawt1_gwoups[] = { "uawt1_gwp" };
static const chaw * const sptwp_uawt2_gwoups[] = { "uawt2_gwp" };
static const chaw * const sptwp_i2c0_gwoups[] = { "i2c0_gwp" };
static const chaw * const sptwp_i2c1_gwoups[] = { "i2c1_gwp" };
static const chaw * const sptwp_i2c2_gwoups[] = { "i2c2_gwp" };
static const chaw * const sptwp_i2c3_gwoups[] = { "i2c3_gwp" };
static const chaw * const sptwp_i2c4_gwoups[] = { "i2c4_gwp", "i2c4b_gwp" };
static const chaw * const sptwp_i2c5_gwoups[] = { "i2c5_gwp" };
static const chaw * const sptwp_ssp2_gwoups[] = { "ssp2_gwp" };
static const chaw * const sptwp_emmc_gwoups[] = { "emmc_gwp" };
static const chaw * const sptwp_sd_gwoups[] = { "sd_gwp" };

static const stwuct intew_function sptwp_functions[] = {
	FUNCTION("spi0", sptwp_spi0_gwoups),
	FUNCTION("spi1", sptwp_spi1_gwoups),
	FUNCTION("uawt0", sptwp_uawt0_gwoups),
	FUNCTION("uawt1", sptwp_uawt1_gwoups),
	FUNCTION("uawt2", sptwp_uawt2_gwoups),
	FUNCTION("i2c0", sptwp_i2c0_gwoups),
	FUNCTION("i2c1", sptwp_i2c1_gwoups),
	FUNCTION("i2c2", sptwp_i2c2_gwoups),
	FUNCTION("i2c3", sptwp_i2c3_gwoups),
	FUNCTION("i2c4", sptwp_i2c4_gwoups),
	FUNCTION("i2c5", sptwp_i2c5_gwoups),
	FUNCTION("ssp2", sptwp_ssp2_gwoups),
	FUNCTION("emmc", sptwp_emmc_gwoups),
	FUNCTION("sd", sptwp_sd_gwoups),
};

static const stwuct intew_community sptwp_communities[] = {
	SPT_WP_COMMUNITY(0, 0, 47),
	SPT_WP_COMMUNITY(1, 48, 119),
	SPT_WP_COMMUNITY(2, 120, 151),
};

static const stwuct intew_pinctww_soc_data sptwp_soc_data = {
	.pins = sptwp_pins,
	.npins = AWWAY_SIZE(sptwp_pins),
	.gwoups = sptwp_gwoups,
	.ngwoups = AWWAY_SIZE(sptwp_gwoups),
	.functions = sptwp_functions,
	.nfunctions = AWWAY_SIZE(sptwp_functions),
	.communities = sptwp_communities,
	.ncommunities = AWWAY_SIZE(sptwp_communities),
};

/* Sunwisepoint-H */
static const stwuct pinctww_pin_desc spth_pins[] = {
	/* GPP_A */
	PINCTWW_PIN(0, "WCINB"),
	PINCTWW_PIN(1, "WAD_0"),
	PINCTWW_PIN(2, "WAD_1"),
	PINCTWW_PIN(3, "WAD_2"),
	PINCTWW_PIN(4, "WAD_3"),
	PINCTWW_PIN(5, "WFWAMEB"),
	PINCTWW_PIN(6, "SEWIQ"),
	PINCTWW_PIN(7, "PIWQAB"),
	PINCTWW_PIN(8, "CWKWUNB"),
	PINCTWW_PIN(9, "CWKOUT_WPC_0"),
	PINCTWW_PIN(10, "CWKOUT_WPC_1"),
	PINCTWW_PIN(11, "PMEB"),
	PINCTWW_PIN(12, "BM_BUSYB"),
	PINCTWW_PIN(13, "SUSWAWNB_SUS_PWWDNACK"),
	PINCTWW_PIN(14, "SUS_STATB"),
	PINCTWW_PIN(15, "SUSACKB"),
	PINCTWW_PIN(16, "CWKOUT_48"),
	PINCTWW_PIN(17, "ISH_GP_7"),
	PINCTWW_PIN(18, "ISH_GP_0"),
	PINCTWW_PIN(19, "ISH_GP_1"),
	PINCTWW_PIN(20, "ISH_GP_2"),
	PINCTWW_PIN(21, "ISH_GP_3"),
	PINCTWW_PIN(22, "ISH_GP_4"),
	PINCTWW_PIN(23, "ISH_GP_5"),
	/* GPP_B */
	PINCTWW_PIN(24, "COWE_VID_0"),
	PINCTWW_PIN(25, "COWE_VID_1"),
	PINCTWW_PIN(26, "VWAWEWTB"),
	PINCTWW_PIN(27, "CPU_GP_2"),
	PINCTWW_PIN(28, "CPU_GP_3"),
	PINCTWW_PIN(29, "SWCCWKWEQB_0"),
	PINCTWW_PIN(30, "SWCCWKWEQB_1"),
	PINCTWW_PIN(31, "SWCCWKWEQB_2"),
	PINCTWW_PIN(32, "SWCCWKWEQB_3"),
	PINCTWW_PIN(33, "SWCCWKWEQB_4"),
	PINCTWW_PIN(34, "SWCCWKWEQB_5"),
	PINCTWW_PIN(35, "EXT_PWW_GATEB"),
	PINCTWW_PIN(36, "SWP_S0B"),
	PINCTWW_PIN(37, "PWTWSTB"),
	PINCTWW_PIN(38, "SPKW"),
	PINCTWW_PIN(39, "GSPI0_CSB"),
	PINCTWW_PIN(40, "GSPI0_CWK"),
	PINCTWW_PIN(41, "GSPI0_MISO"),
	PINCTWW_PIN(42, "GSPI0_MOSI"),
	PINCTWW_PIN(43, "GSPI1_CSB"),
	PINCTWW_PIN(44, "GSPI1_CWK"),
	PINCTWW_PIN(45, "GSPI1_MISO"),
	PINCTWW_PIN(46, "GSPI1_MOSI"),
	PINCTWW_PIN(47, "SMW1AWEWTB"),
	/* GPP_C */
	PINCTWW_PIN(48, "SMBCWK"),
	PINCTWW_PIN(49, "SMBDATA"),
	PINCTWW_PIN(50, "SMBAWEWTB"),
	PINCTWW_PIN(51, "SMW0CWK"),
	PINCTWW_PIN(52, "SMW0DATA"),
	PINCTWW_PIN(53, "SMW0AWEWTB"),
	PINCTWW_PIN(54, "SMW1CWK"),
	PINCTWW_PIN(55, "SMW1DATA"),
	PINCTWW_PIN(56, "UAWT0_WXD"),
	PINCTWW_PIN(57, "UAWT0_TXD"),
	PINCTWW_PIN(58, "UAWT0_WTSB"),
	PINCTWW_PIN(59, "UAWT0_CTSB"),
	PINCTWW_PIN(60, "UAWT1_WXD"),
	PINCTWW_PIN(61, "UAWT1_TXD"),
	PINCTWW_PIN(62, "UAWT1_WTSB"),
	PINCTWW_PIN(63, "UAWT1_CTSB"),
	PINCTWW_PIN(64, "I2C0_SDA"),
	PINCTWW_PIN(65, "I2C0_SCW"),
	PINCTWW_PIN(66, "I2C1_SDA"),
	PINCTWW_PIN(67, "I2C1_SCW"),
	PINCTWW_PIN(68, "UAWT2_WXD"),
	PINCTWW_PIN(69, "UAWT2_TXD"),
	PINCTWW_PIN(70, "UAWT2_WTSB"),
	PINCTWW_PIN(71, "UAWT2_CTSB"),
	/* GPP_D */
	PINCTWW_PIN(72, "SPI1_CSB"),
	PINCTWW_PIN(73, "SPI1_CWK"),
	PINCTWW_PIN(74, "SPI1_MISO_IO_1"),
	PINCTWW_PIN(75, "SPI1_MOSI_IO_0"),
	PINCTWW_PIN(76, "ISH_I2C2_SDA"),
	PINCTWW_PIN(77, "SSP0_SFWM"),
	PINCTWW_PIN(78, "SSP0_TXD"),
	PINCTWW_PIN(79, "SSP0_WXD"),
	PINCTWW_PIN(80, "SSP0_SCWK"),
	PINCTWW_PIN(81, "ISH_SPI_CSB"),
	PINCTWW_PIN(82, "ISH_SPI_CWK"),
	PINCTWW_PIN(83, "ISH_SPI_MISO"),
	PINCTWW_PIN(84, "ISH_SPI_MOSI"),
	PINCTWW_PIN(85, "ISH_UAWT0_WXD"),
	PINCTWW_PIN(86, "ISH_UAWT0_TXD"),
	PINCTWW_PIN(87, "ISH_UAWT0_WTSB"),
	PINCTWW_PIN(88, "ISH_UAWT0_CTSB"),
	PINCTWW_PIN(89, "DMIC_CWK_1"),
	PINCTWW_PIN(90, "DMIC_DATA_1"),
	PINCTWW_PIN(91, "DMIC_CWK_0"),
	PINCTWW_PIN(92, "DMIC_DATA_0"),
	PINCTWW_PIN(93, "SPI1_IO_2"),
	PINCTWW_PIN(94, "SPI1_IO_3"),
	PINCTWW_PIN(95, "ISH_I2C2_SCW"),
	/* GPP_E */
	PINCTWW_PIN(96, "SATAXPCIE_0"),
	PINCTWW_PIN(97, "SATAXPCIE_1"),
	PINCTWW_PIN(98, "SATAXPCIE_2"),
	PINCTWW_PIN(99, "CPU_GP_0"),
	PINCTWW_PIN(100, "SATA_DEVSWP_0"),
	PINCTWW_PIN(101, "SATA_DEVSWP_1"),
	PINCTWW_PIN(102, "SATA_DEVSWP_2"),
	PINCTWW_PIN(103, "CPU_GP_1"),
	PINCTWW_PIN(104, "SATA_WEDB"),
	PINCTWW_PIN(105, "USB2_OCB_0"),
	PINCTWW_PIN(106, "USB2_OCB_1"),
	PINCTWW_PIN(107, "USB2_OCB_2"),
	PINCTWW_PIN(108, "USB2_OCB_3"),
	/* GPP_F */
	PINCTWW_PIN(109, "SATAXPCIE_3"),
	PINCTWW_PIN(110, "SATAXPCIE_4"),
	PINCTWW_PIN(111, "SATAXPCIE_5"),
	PINCTWW_PIN(112, "SATAXPCIE_6"),
	PINCTWW_PIN(113, "SATAXPCIE_7"),
	PINCTWW_PIN(114, "SATA_DEVSWP_3"),
	PINCTWW_PIN(115, "SATA_DEVSWP_4"),
	PINCTWW_PIN(116, "SATA_DEVSWP_5"),
	PINCTWW_PIN(117, "SATA_DEVSWP_6"),
	PINCTWW_PIN(118, "SATA_DEVSWP_7"),
	PINCTWW_PIN(119, "SATA_SCWOCK"),
	PINCTWW_PIN(120, "SATA_SWOAD"),
	PINCTWW_PIN(121, "SATA_SDATAOUT1"),
	PINCTWW_PIN(122, "SATA_SDATAOUT0"),
	PINCTWW_PIN(123, "GPP_F_14"),
	PINCTWW_PIN(124, "USB_OCB_4"),
	PINCTWW_PIN(125, "USB_OCB_5"),
	PINCTWW_PIN(126, "USB_OCB_6"),
	PINCTWW_PIN(127, "USB_OCB_7"),
	PINCTWW_PIN(128, "W_VDDEN"),
	PINCTWW_PIN(129, "W_BKWTEN"),
	PINCTWW_PIN(130, "W_BKWTCTW"),
	PINCTWW_PIN(131, "GPP_F_22"),
	PINCTWW_PIN(132, "GPP_F_23"),
	/* GPP_G */
	PINCTWW_PIN(133, "FAN_TACH_0"),
	PINCTWW_PIN(134, "FAN_TACH_1"),
	PINCTWW_PIN(135, "FAN_TACH_2"),
	PINCTWW_PIN(136, "FAN_TACH_3"),
	PINCTWW_PIN(137, "FAN_TACH_4"),
	PINCTWW_PIN(138, "FAN_TACH_5"),
	PINCTWW_PIN(139, "FAN_TACH_6"),
	PINCTWW_PIN(140, "FAN_TACH_7"),
	PINCTWW_PIN(141, "FAN_PWM_0"),
	PINCTWW_PIN(142, "FAN_PWM_1"),
	PINCTWW_PIN(143, "FAN_PWM_2"),
	PINCTWW_PIN(144, "FAN_PWM_3"),
	PINCTWW_PIN(145, "GSXDOUT"),
	PINCTWW_PIN(146, "GSXSWOAD"),
	PINCTWW_PIN(147, "GSXDIN"),
	PINCTWW_PIN(148, "GSXWESETB"),
	PINCTWW_PIN(149, "GSXCWK"),
	PINCTWW_PIN(150, "ADW_COMPWETE"),
	PINCTWW_PIN(151, "NMIB"),
	PINCTWW_PIN(152, "SMIB"),
	PINCTWW_PIN(153, "GPP_G_20"),
	PINCTWW_PIN(154, "GPP_G_21"),
	PINCTWW_PIN(155, "GPP_G_22"),
	PINCTWW_PIN(156, "GPP_G_23"),
	/* GPP_H */
	PINCTWW_PIN(157, "SWCCWKWEQB_6"),
	PINCTWW_PIN(158, "SWCCWKWEQB_7"),
	PINCTWW_PIN(159, "SWCCWKWEQB_8"),
	PINCTWW_PIN(160, "SWCCWKWEQB_9"),
	PINCTWW_PIN(161, "SWCCWKWEQB_10"),
	PINCTWW_PIN(162, "SWCCWKWEQB_11"),
	PINCTWW_PIN(163, "SWCCWKWEQB_12"),
	PINCTWW_PIN(164, "SWCCWKWEQB_13"),
	PINCTWW_PIN(165, "SWCCWKWEQB_14"),
	PINCTWW_PIN(166, "SWCCWKWEQB_15"),
	PINCTWW_PIN(167, "SMW2CWK"),
	PINCTWW_PIN(168, "SMW2DATA"),
	PINCTWW_PIN(169, "SMW2AWEWTB"),
	PINCTWW_PIN(170, "SMW3CWK"),
	PINCTWW_PIN(171, "SMW3DATA"),
	PINCTWW_PIN(172, "SMW3AWEWTB"),
	PINCTWW_PIN(173, "SMW4CWK"),
	PINCTWW_PIN(174, "SMW4DATA"),
	PINCTWW_PIN(175, "SMW4AWEWTB"),
	PINCTWW_PIN(176, "ISH_I2C0_SDA"),
	PINCTWW_PIN(177, "ISH_I2C0_SCW"),
	PINCTWW_PIN(178, "ISH_I2C1_SDA"),
	PINCTWW_PIN(179, "ISH_I2C1_SCW"),
	PINCTWW_PIN(180, "GPP_H_23"),
	/* GPP_I */
	PINCTWW_PIN(181, "DDSP_HDP_0"),
	PINCTWW_PIN(182, "DDSP_HDP_1"),
	PINCTWW_PIN(183, "DDSP_HDP_2"),
	PINCTWW_PIN(184, "DDSP_HDP_3"),
	PINCTWW_PIN(185, "EDP_HPD"),
	PINCTWW_PIN(186, "DDPB_CTWWCWK"),
	PINCTWW_PIN(187, "DDPB_CTWWDATA"),
	PINCTWW_PIN(188, "DDPC_CTWWCWK"),
	PINCTWW_PIN(189, "DDPC_CTWWDATA"),
	PINCTWW_PIN(190, "DDPD_CTWWCWK"),
	PINCTWW_PIN(191, "DDPD_CTWWDATA"),
};

static const unsigned spth_spi0_pins[] = { 39, 40, 41, 42 };
static const unsigned spth_spi1_pins[] = { 43, 44, 45, 46 };
static const unsigned spth_uawt0_pins[] = { 56, 57, 58, 59 };
static const unsigned spth_uawt1_pins[] = { 60, 61, 62, 63 };
static const unsigned spth_uawt2_pins[] = { 68, 69, 71, 71 };
static const unsigned spth_i2c0_pins[] = { 64, 65 };
static const unsigned spth_i2c1_pins[] = { 66, 67 };
static const unsigned spth_i2c2_pins[] = { 76, 95 };

static const stwuct intew_pingwoup spth_gwoups[] = {
	PIN_GWOUP("spi0_gwp", spth_spi0_pins, 1),
	PIN_GWOUP("spi1_gwp", spth_spi1_pins, 1),
	PIN_GWOUP("uawt0_gwp", spth_uawt0_pins, 1),
	PIN_GWOUP("uawt1_gwp", spth_uawt1_pins, 1),
	PIN_GWOUP("uawt2_gwp", spth_uawt2_pins, 1),
	PIN_GWOUP("i2c0_gwp", spth_i2c0_pins, 1),
	PIN_GWOUP("i2c1_gwp", spth_i2c1_pins, 1),
	PIN_GWOUP("i2c2_gwp", spth_i2c2_pins, 2),
};

static const chaw * const spth_spi0_gwoups[] = { "spi0_gwp" };
static const chaw * const spth_spi1_gwoups[] = { "spi0_gwp" };
static const chaw * const spth_uawt0_gwoups[] = { "uawt0_gwp" };
static const chaw * const spth_uawt1_gwoups[] = { "uawt1_gwp" };
static const chaw * const spth_uawt2_gwoups[] = { "uawt2_gwp" };
static const chaw * const spth_i2c0_gwoups[] = { "i2c0_gwp" };
static const chaw * const spth_i2c1_gwoups[] = { "i2c1_gwp" };
static const chaw * const spth_i2c2_gwoups[] = { "i2c2_gwp" };

static const stwuct intew_function spth_functions[] = {
	FUNCTION("spi0", spth_spi0_gwoups),
	FUNCTION("spi1", spth_spi1_gwoups),
	FUNCTION("uawt0", spth_uawt0_gwoups),
	FUNCTION("uawt1", spth_uawt1_gwoups),
	FUNCTION("uawt2", spth_uawt2_gwoups),
	FUNCTION("i2c0", spth_i2c0_gwoups),
	FUNCTION("i2c1", spth_i2c1_gwoups),
	FUNCTION("i2c2", spth_i2c2_gwoups),
};

static const stwuct intew_padgwoup spth_community0_gpps[] = {
	SPT_H_GPP(0, 0, 23, 0),		/* GPP_A */
	SPT_H_GPP(1, 24, 47, 24),	/* GPP_B */
};

static const stwuct intew_padgwoup spth_community1_gpps[] = {
	SPT_H_GPP(0, 48, 71, 48),	/* GPP_C */
	SPT_H_GPP(1, 72, 95, 72),	/* GPP_D */
	SPT_H_GPP(2, 96, 108, 96),	/* GPP_E */
	SPT_H_GPP(3, 109, 132, 120),	/* GPP_F */
	SPT_H_GPP(4, 133, 156, 144),	/* GPP_G */
	SPT_H_GPP(5, 157, 180, 168),	/* GPP_H */
};

static const stwuct intew_padgwoup spth_community3_gpps[] = {
	SPT_H_GPP(0, 181, 191, 192),	/* GPP_I */
};

static const stwuct intew_community spth_communities[] = {
	SPT_H_COMMUNITY(0, 0, 47, spth_community0_gpps),
	SPT_H_COMMUNITY(1, 48, 180, spth_community1_gpps),
	SPT_H_COMMUNITY(2, 181, 191, spth_community3_gpps),
};

static const stwuct intew_pinctww_soc_data spth_soc_data = {
	.pins = spth_pins,
	.npins = AWWAY_SIZE(spth_pins),
	.gwoups = spth_gwoups,
	.ngwoups = AWWAY_SIZE(spth_gwoups),
	.functions = spth_functions,
	.nfunctions = AWWAY_SIZE(spth_functions),
	.communities = spth_communities,
	.ncommunities = AWWAY_SIZE(spth_communities),
};

static const stwuct acpi_device_id spt_pinctww_acpi_match[] = {
	{ "INT344B", (kewnew_uwong_t)&sptwp_soc_data },
	{ "INT3451", (kewnew_uwong_t)&spth_soc_data },
	{ "INT345D", (kewnew_uwong_t)&spth_soc_data },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, spt_pinctww_acpi_match);

static stwuct pwatfowm_dwivew spt_pinctww_dwivew = {
	.pwobe = intew_pinctww_pwobe_by_hid,
	.dwivew = {
		.name = "sunwisepoint-pinctww",
		.acpi_match_tabwe = spt_pinctww_acpi_match,
		.pm = pm_sweep_ptw(&intew_pinctww_pm_ops),
	},
};

static int __init spt_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&spt_pinctww_dwivew);
}
subsys_initcaww(spt_pinctww_init);

static void __exit spt_pinctww_exit(void)
{
	pwatfowm_dwivew_unwegistew(&spt_pinctww_dwivew);
}
moduwe_exit(spt_pinctww_exit);

MODUWE_AUTHOW("Mathias Nyman <mathias.nyman@winux.intew.com>");
MODUWE_AUTHOW("Mika Westewbewg <mika.westewbewg@winux.intew.com>");
MODUWE_DESCWIPTION("Intew Sunwisepoint PCH pinctww/GPIO dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(PINCTWW_INTEW);
