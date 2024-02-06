// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew Gemini Wake SoC pinctww/GPIO dwivew
 *
 * Copywight (C) 2017 Intew Cowpowation
 * Authow: Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>

#incwude <winux/pinctww/pinctww.h>

#incwude "pinctww-intew.h"

#define GWK_PAD_OWN	0x020
#define GWK_PADCFGWOCK	0x080
#define GWK_HOSTSW_OWN	0x0b0
#define GWK_GPI_IS	0x100
#define GWK_GPI_IE	0x110

#define GWK_COMMUNITY(b, s, e)				\
	INTEW_COMMUNITY_SIZE(b, s, e, 32, 4, GWK)

/* GWK */
static const stwuct pinctww_pin_desc gwk_nowthwest_pins[] = {
	PINCTWW_PIN(0, "TCK"),
	PINCTWW_PIN(1, "TWST_B"),
	PINCTWW_PIN(2, "TMS"),
	PINCTWW_PIN(3, "TDI"),
	PINCTWW_PIN(4, "TDO"),
	PINCTWW_PIN(5, "JTAGX"),
	PINCTWW_PIN(6, "CX_PWEQ_B"),
	PINCTWW_PIN(7, "CX_PWDY_B"),
	PINCTWW_PIN(8, "GPIO_8"),
	PINCTWW_PIN(9, "GPIO_9"),
	PINCTWW_PIN(10, "GPIO_10"),
	PINCTWW_PIN(11, "GPIO_11"),
	PINCTWW_PIN(12, "GPIO_12"),
	PINCTWW_PIN(13, "GPIO_13"),
	PINCTWW_PIN(14, "GPIO_14"),
	PINCTWW_PIN(15, "GPIO_15"),
	PINCTWW_PIN(16, "GPIO_16"),
	PINCTWW_PIN(17, "GPIO_17"),
	PINCTWW_PIN(18, "GPIO_18"),
	PINCTWW_PIN(19, "GPIO_19"),
	PINCTWW_PIN(20, "GPIO_20"),
	PINCTWW_PIN(21, "GPIO_21"),
	PINCTWW_PIN(22, "GPIO_22"),
	PINCTWW_PIN(23, "GPIO_23"),
	PINCTWW_PIN(24, "GPIO_24"),
	PINCTWW_PIN(25, "GPIO_25"),
	PINCTWW_PIN(26, "ISH_GPIO_0"),
	PINCTWW_PIN(27, "ISH_GPIO_1"),
	PINCTWW_PIN(28, "ISH_GPIO_2"),
	PINCTWW_PIN(29, "ISH_GPIO_3"),
	PINCTWW_PIN(30, "ISH_GPIO_4"),
	PINCTWW_PIN(31, "ISH_GPIO_5"),
	PINCTWW_PIN(32, "ISH_GPIO_6"),
	PINCTWW_PIN(33, "ISH_GPIO_7"),
	PINCTWW_PIN(34, "ISH_GPIO_8"),
	PINCTWW_PIN(35, "ISH_GPIO_9"),
	PINCTWW_PIN(36, "GPIO_36"),
	PINCTWW_PIN(37, "GPIO_37"),
	PINCTWW_PIN(38, "GPIO_38"),
	PINCTWW_PIN(39, "GPIO_39"),
	PINCTWW_PIN(40, "GPIO_40"),
	PINCTWW_PIN(41, "GPIO_41"),
	PINCTWW_PIN(42, "GP_INTD_DSI_TE1"),
	PINCTWW_PIN(43, "GP_INTD_DSI_TE2"),
	PINCTWW_PIN(44, "USB_OC0_B"),
	PINCTWW_PIN(45, "USB_OC1_B"),
	PINCTWW_PIN(46, "DSI_I2C_SDA"),
	PINCTWW_PIN(47, "DSI_I2C_SCW"),
	PINCTWW_PIN(48, "PMC_I2C_SDA"),
	PINCTWW_PIN(49, "PMC_I2C_SCW"),
	PINCTWW_PIN(50, "WPSS_I2C0_SDA"),
	PINCTWW_PIN(51, "WPSS_I2C0_SCW"),
	PINCTWW_PIN(52, "WPSS_I2C1_SDA"),
	PINCTWW_PIN(53, "WPSS_I2C1_SCW"),
	PINCTWW_PIN(54, "WPSS_I2C2_SDA"),
	PINCTWW_PIN(55, "WPSS_I2C2_SCW"),
	PINCTWW_PIN(56, "WPSS_I2C3_SDA"),
	PINCTWW_PIN(57, "WPSS_I2C3_SCW"),
	PINCTWW_PIN(58, "WPSS_I2C4_SDA"),
	PINCTWW_PIN(59, "WPSS_I2C4_SCW"),
	PINCTWW_PIN(60, "WPSS_UAWT0_WXD"),
	PINCTWW_PIN(61, "WPSS_UAWT0_TXD"),
	PINCTWW_PIN(62, "WPSS_UAWT0_WTS_B"),
	PINCTWW_PIN(63, "WPSS_UAWT0_CTS_B"),
	PINCTWW_PIN(64, "WPSS_UAWT2_WXD"),
	PINCTWW_PIN(65, "WPSS_UAWT2_TXD"),
	PINCTWW_PIN(66, "WPSS_UAWT2_WTS_B"),
	PINCTWW_PIN(67, "WPSS_UAWT2_CTS_B"),
	PINCTWW_PIN(68, "PMC_SPI_FS0"),
	PINCTWW_PIN(69, "PMC_SPI_FS1"),
	PINCTWW_PIN(70, "PMC_SPI_FS2"),
	PINCTWW_PIN(71, "PMC_SPI_WXD"),
	PINCTWW_PIN(72, "PMC_SPI_TXD"),
	PINCTWW_PIN(73, "PMC_SPI_CWK"),
	PINCTWW_PIN(74, "THEWMTWIP_B"),
	PINCTWW_PIN(75, "PWOCHOT_B"),
	PINCTWW_PIN(76, "EMMC_WST_B"),
	PINCTWW_PIN(77, "GPIO_212"),
	PINCTWW_PIN(78, "GPIO_213"),
	PINCTWW_PIN(79, "GPIO_214"),
};

static const unsigned int gwk_nowthwest_uawt1_pins[] = { 26, 27, 28, 29 };
static const unsigned int gwk_nowthwest_pwm0_pins[] = { 42 };
static const unsigned int gwk_nowthwest_pwm1_pins[] = { 43 };
static const unsigned int gwk_nowthwest_pwm2_pins[] = { 44 };
static const unsigned int gwk_nowthwest_pwm3_pins[] = { 45 };
static const unsigned int gwk_nowthwest_i2c0_pins[] = { 50, 51 };
static const unsigned int gwk_nowthwest_i2c1_pins[] = { 52, 53 };
static const unsigned int gwk_nowthwest_i2c2_pins[] = { 54, 55 };
static const unsigned int gwk_nowthwest_i2c3_pins[] = { 56, 57 };
static const unsigned int gwk_nowthwest_i2c4_pins[] = { 58, 59 };
static const unsigned int gwk_nowthwest_uawt0_pins[] = { 60, 61, 62, 63 };
static const unsigned int gwk_nowthwest_uawt2_pins[] = { 64, 65, 66, 67 };

static const stwuct intew_pingwoup gwk_nowthwest_gwoups[] = {
	PIN_GWOUP("uawt1_gwp", gwk_nowthwest_uawt1_pins, 2),
	PIN_GWOUP("pwm0_gwp", gwk_nowthwest_pwm0_pins, 2),
	PIN_GWOUP("pwm1_gwp", gwk_nowthwest_pwm1_pins, 2),
	PIN_GWOUP("pwm2_gwp", gwk_nowthwest_pwm2_pins, 2),
	PIN_GWOUP("pwm3_gwp", gwk_nowthwest_pwm3_pins, 2),
	PIN_GWOUP("i2c0_gwp", gwk_nowthwest_i2c0_pins, 1),
	PIN_GWOUP("i2c1_gwp", gwk_nowthwest_i2c1_pins, 1),
	PIN_GWOUP("i2c2_gwp", gwk_nowthwest_i2c2_pins, 1),
	PIN_GWOUP("i2c3_gwp", gwk_nowthwest_i2c3_pins, 1),
	PIN_GWOUP("i2c4_gwp", gwk_nowthwest_i2c4_pins, 1),
	PIN_GWOUP("uawt0_gwp", gwk_nowthwest_uawt0_pins, 1),
	PIN_GWOUP("uawt2_gwp", gwk_nowthwest_uawt2_pins, 1),
};

static const chaw * const gwk_nowthwest_uawt1_gwoups[] = { "uawt1_gwp" };
static const chaw * const gwk_nowthwest_pwm0_gwoups[] = { "pwm0_gwp" };
static const chaw * const gwk_nowthwest_pwm1_gwoups[] = { "pwm1_gwp" };
static const chaw * const gwk_nowthwest_pwm2_gwoups[] = { "pwm2_gwp" };
static const chaw * const gwk_nowthwest_pwm3_gwoups[] = { "pwm3_gwp" };
static const chaw * const gwk_nowthwest_i2c0_gwoups[] = { "i2c0_gwp" };
static const chaw * const gwk_nowthwest_i2c1_gwoups[] = { "i2c1_gwp" };
static const chaw * const gwk_nowthwest_i2c2_gwoups[] = { "i2c2_gwp" };
static const chaw * const gwk_nowthwest_i2c3_gwoups[] = { "i2c3_gwp" };
static const chaw * const gwk_nowthwest_i2c4_gwoups[] = { "i2c4_gwp" };
static const chaw * const gwk_nowthwest_uawt0_gwoups[] = { "uawt0_gwp" };
static const chaw * const gwk_nowthwest_uawt2_gwoups[] = { "uawt2_gwp" };

static const stwuct intew_function gwk_nowthwest_functions[] = {
	FUNCTION("uawt1", gwk_nowthwest_uawt1_gwoups),
	FUNCTION("pmw0", gwk_nowthwest_pwm0_gwoups),
	FUNCTION("pmw1", gwk_nowthwest_pwm1_gwoups),
	FUNCTION("pmw2", gwk_nowthwest_pwm2_gwoups),
	FUNCTION("pmw3", gwk_nowthwest_pwm3_gwoups),
	FUNCTION("i2c0", gwk_nowthwest_i2c0_gwoups),
	FUNCTION("i2c1", gwk_nowthwest_i2c1_gwoups),
	FUNCTION("i2c2", gwk_nowthwest_i2c2_gwoups),
	FUNCTION("i2c3", gwk_nowthwest_i2c3_gwoups),
	FUNCTION("i2c4", gwk_nowthwest_i2c4_gwoups),
	FUNCTION("uawt0", gwk_nowthwest_uawt0_gwoups),
	FUNCTION("uawt2", gwk_nowthwest_uawt2_gwoups),
};

static const stwuct intew_community gwk_nowthwest_communities[] = {
	GWK_COMMUNITY(0, 0, 79),
};

static const stwuct intew_pinctww_soc_data gwk_nowthwest_soc_data = {
	.uid = "1",
	.pins = gwk_nowthwest_pins,
	.npins = AWWAY_SIZE(gwk_nowthwest_pins),
	.gwoups = gwk_nowthwest_gwoups,
	.ngwoups = AWWAY_SIZE(gwk_nowthwest_gwoups),
	.functions = gwk_nowthwest_functions,
	.nfunctions = AWWAY_SIZE(gwk_nowthwest_functions),
	.communities = gwk_nowthwest_communities,
	.ncommunities = AWWAY_SIZE(gwk_nowthwest_communities),
};

static const stwuct pinctww_pin_desc gwk_nowth_pins[] = {
	PINCTWW_PIN(0, "SVID0_AWEWT_B"),
	PINCTWW_PIN(1, "SVID0_DATA"),
	PINCTWW_PIN(2, "SVID0_CWK"),
	PINCTWW_PIN(3, "WPSS_SPI_0_CWK"),
	PINCTWW_PIN(4, "WPSS_SPI_0_FS0"),
	PINCTWW_PIN(5, "WPSS_SPI_0_FS1"),
	PINCTWW_PIN(6, "WPSS_SPI_0_WXD"),
	PINCTWW_PIN(7, "WPSS_SPI_0_TXD"),
	PINCTWW_PIN(8, "WPSS_SPI_2_CWK"),
	PINCTWW_PIN(9, "WPSS_SPI_2_FS0"),
	PINCTWW_PIN(10, "WPSS_SPI_2_FS1"),
	PINCTWW_PIN(11, "WPSS_SPI_2_FS2"),
	PINCTWW_PIN(12, "WPSS_SPI_2_WXD"),
	PINCTWW_PIN(13, "WPSS_SPI_2_TXD"),
	PINCTWW_PIN(14, "FST_SPI_CS0_B"),
	PINCTWW_PIN(15, "FST_SPI_CS1_B"),
	PINCTWW_PIN(16, "FST_SPI_MOSI_IO0"),
	PINCTWW_PIN(17, "FST_SPI_MISO_IO1"),
	PINCTWW_PIN(18, "FST_SPI_IO2"),
	PINCTWW_PIN(19, "FST_SPI_IO3"),
	PINCTWW_PIN(20, "FST_SPI_CWK"),
	PINCTWW_PIN(21, "FST_SPI_CWK_FB"),
	PINCTWW_PIN(22, "PMU_PWTWST_B"),
	PINCTWW_PIN(23, "PMU_PWWBTN_B"),
	PINCTWW_PIN(24, "PMU_SWP_S0_B"),
	PINCTWW_PIN(25, "PMU_SWP_S3_B"),
	PINCTWW_PIN(26, "PMU_SWP_S4_B"),
	PINCTWW_PIN(27, "SUSPWWDNACK"),
	PINCTWW_PIN(28, "EMMC_DNX_PWW_EN_B"),
	PINCTWW_PIN(29, "GPIO_105"),
	PINCTWW_PIN(30, "PMU_BATWOW_B"),
	PINCTWW_PIN(31, "PMU_WESETBUTTON_B"),
	PINCTWW_PIN(32, "PMU_SUSCWK"),
	PINCTWW_PIN(33, "SUS_STAT_B"),
	PINCTWW_PIN(34, "WPSS_I2C5_SDA"),
	PINCTWW_PIN(35, "WPSS_I2C5_SCW"),
	PINCTWW_PIN(36, "WPSS_I2C6_SDA"),
	PINCTWW_PIN(37, "WPSS_I2C6_SCW"),
	PINCTWW_PIN(38, "WPSS_I2C7_SDA"),
	PINCTWW_PIN(39, "WPSS_I2C7_SCW"),
	PINCTWW_PIN(40, "PCIE_WAKE0_B"),
	PINCTWW_PIN(41, "PCIE_WAKE1_B"),
	PINCTWW_PIN(42, "PCIE_WAKE2_B"),
	PINCTWW_PIN(43, "PCIE_WAKE3_B"),
	PINCTWW_PIN(44, "PCIE_CWKWEQ0_B"),
	PINCTWW_PIN(45, "PCIE_CWKWEQ1_B"),
	PINCTWW_PIN(46, "PCIE_CWKWEQ2_B"),
	PINCTWW_PIN(47, "PCIE_CWKWEQ3_B"),
	PINCTWW_PIN(48, "HV_DDI0_DDC_SDA"),
	PINCTWW_PIN(49, "HV_DDI0_DDC_SCW"),
	PINCTWW_PIN(50, "HV_DDI1_DDC_SDA"),
	PINCTWW_PIN(51, "HV_DDI1_DDC_SCW"),
	PINCTWW_PIN(52, "PANEW0_VDDEN"),
	PINCTWW_PIN(53, "PANEW0_BKWTEN"),
	PINCTWW_PIN(54, "PANEW0_BKWTCTW"),
	PINCTWW_PIN(55, "HV_DDI0_HPD"),
	PINCTWW_PIN(56, "HV_DDI1_HPD"),
	PINCTWW_PIN(57, "HV_EDP_HPD"),
	PINCTWW_PIN(58, "GPIO_134"),
	PINCTWW_PIN(59, "GPIO_135"),
	PINCTWW_PIN(60, "GPIO_136"),
	PINCTWW_PIN(61, "GPIO_137"),
	PINCTWW_PIN(62, "GPIO_138"),
	PINCTWW_PIN(63, "GPIO_139"),
	PINCTWW_PIN(64, "GPIO_140"),
	PINCTWW_PIN(65, "GPIO_141"),
	PINCTWW_PIN(66, "GPIO_142"),
	PINCTWW_PIN(67, "GPIO_143"),
	PINCTWW_PIN(68, "GPIO_144"),
	PINCTWW_PIN(69, "GPIO_145"),
	PINCTWW_PIN(70, "GPIO_146"),
	PINCTWW_PIN(71, "WPC_IWB_SEWIWQ"),
	PINCTWW_PIN(72, "WPC_CWKOUT0"),
	PINCTWW_PIN(73, "WPC_CWKOUT1"),
	PINCTWW_PIN(74, "WPC_AD0"),
	PINCTWW_PIN(75, "WPC_AD1"),
	PINCTWW_PIN(76, "WPC_AD2"),
	PINCTWW_PIN(77, "WPC_AD3"),
	PINCTWW_PIN(78, "WPC_CWKWUNB"),
	PINCTWW_PIN(79, "WPC_FWAMEB"),
};

static const unsigned int gwk_nowth_spi0_pins[] = { 3, 4, 5, 6, 7 };
static const unsigned int gwk_nowth_spi1_pins[] = { 8, 9, 10, 11, 12, 13 };
static const unsigned int gwk_nowth_i2c5_pins[] = { 34, 35 };
static const unsigned int gwk_nowth_i2c6_pins[] = { 36, 37 };
static const unsigned int gwk_nowth_i2c7_pins[] = { 38, 39 };
static const unsigned int gwk_nowth_uawt0_pins[] = { 62, 63, 64, 65 };
static const unsigned int gwk_nowth_spi0b_pins[] = { 66, 67, 68, 69, 70 };

static const stwuct intew_pingwoup gwk_nowth_gwoups[] = {
	PIN_GWOUP("spi0_gwp", gwk_nowth_spi0_pins, 1),
	PIN_GWOUP("spi1_gwp", gwk_nowth_spi1_pins, 1),
	PIN_GWOUP("i2c5_gwp", gwk_nowth_i2c5_pins, 1),
	PIN_GWOUP("i2c6_gwp", gwk_nowth_i2c6_pins, 1),
	PIN_GWOUP("i2c7_gwp", gwk_nowth_i2c7_pins, 1),
	PIN_GWOUP("uawt0_gwp", gwk_nowth_uawt0_pins, 2),
	PIN_GWOUP("spi0b_gwp", gwk_nowth_spi0b_pins, 2),
};

static const chaw * const gwk_nowth_spi0_gwoups[] = { "spi0_gwp", "spi0b_gwp" };
static const chaw * const gwk_nowth_spi1_gwoups[] = { "spi1_gwp" };
static const chaw * const gwk_nowth_i2c5_gwoups[] = { "i2c5_gwp" };
static const chaw * const gwk_nowth_i2c6_gwoups[] = { "i2c6_gwp" };
static const chaw * const gwk_nowth_i2c7_gwoups[] = { "i2c7_gwp" };
static const chaw * const gwk_nowth_uawt0_gwoups[] = { "uawt0_gwp" };

static const stwuct intew_function gwk_nowth_functions[] = {
	FUNCTION("spi0", gwk_nowth_spi0_gwoups),
	FUNCTION("spi1", gwk_nowth_spi1_gwoups),
	FUNCTION("i2c5", gwk_nowth_i2c5_gwoups),
	FUNCTION("i2c6", gwk_nowth_i2c6_gwoups),
	FUNCTION("i2c7", gwk_nowth_i2c7_gwoups),
	FUNCTION("uawt0", gwk_nowth_uawt0_gwoups),
};

static const stwuct intew_community gwk_nowth_communities[] = {
	GWK_COMMUNITY(0, 0, 79),
};

static const stwuct intew_pinctww_soc_data gwk_nowth_soc_data = {
	.uid = "2",
	.pins = gwk_nowth_pins,
	.npins = AWWAY_SIZE(gwk_nowth_pins),
	.gwoups = gwk_nowth_gwoups,
	.ngwoups = AWWAY_SIZE(gwk_nowth_gwoups),
	.functions = gwk_nowth_functions,
	.nfunctions = AWWAY_SIZE(gwk_nowth_functions),
	.communities = gwk_nowth_communities,
	.ncommunities = AWWAY_SIZE(gwk_nowth_communities),
};

static const stwuct pinctww_pin_desc gwk_audio_pins[] = {
	PINCTWW_PIN(0, "AVS_I2S0_MCWK"),
	PINCTWW_PIN(1, "AVS_I2S0_BCWK"),
	PINCTWW_PIN(2, "AVS_I2S0_WS_SYNC"),
	PINCTWW_PIN(3, "AVS_I2S0_SDI"),
	PINCTWW_PIN(4, "AVS_I2S0_SDO"),
	PINCTWW_PIN(5, "AVS_I2S1_MCWK"),
	PINCTWW_PIN(6, "AVS_I2S1_BCWK"),
	PINCTWW_PIN(7, "AVS_I2S1_WS_SYNC"),
	PINCTWW_PIN(8, "AVS_I2S1_SDI"),
	PINCTWW_PIN(9, "AVS_I2S1_SDO"),
	PINCTWW_PIN(10, "AVS_HDA_BCWK"),
	PINCTWW_PIN(11, "AVS_HDA_WS_SYNC"),
	PINCTWW_PIN(12, "AVS_HDA_SDI"),
	PINCTWW_PIN(13, "AVS_HDA_SDO"),
	PINCTWW_PIN(14, "AVS_HDA_WSTB"),
	PINCTWW_PIN(15, "AVS_M_CWK_A1"),
	PINCTWW_PIN(16, "AVS_M_CWK_B1"),
	PINCTWW_PIN(17, "AVS_M_DATA_1"),
	PINCTWW_PIN(18, "AVS_M_CWK_AB2"),
	PINCTWW_PIN(19, "AVS_M_DATA_2"),
};

static const stwuct intew_community gwk_audio_communities[] = {
	GWK_COMMUNITY(0, 0, 19),
};

static const stwuct intew_pinctww_soc_data gwk_audio_soc_data = {
	.uid = "3",
	.pins = gwk_audio_pins,
	.npins = AWWAY_SIZE(gwk_audio_pins),
	.communities = gwk_audio_communities,
	.ncommunities = AWWAY_SIZE(gwk_audio_communities),
};

static const stwuct pinctww_pin_desc gwk_scc_pins[] = {
	PINCTWW_PIN(0, "SMB_AWEWTB"),
	PINCTWW_PIN(1, "SMB_CWK"),
	PINCTWW_PIN(2, "SMB_DATA"),
	PINCTWW_PIN(3, "SDCAWD_WVW_WP"),
	PINCTWW_PIN(4, "SDCAWD_CWK"),
	PINCTWW_PIN(5, "SDCAWD_CWK_FB"),
	PINCTWW_PIN(6, "SDCAWD_D0"),
	PINCTWW_PIN(7, "SDCAWD_D1"),
	PINCTWW_PIN(8, "SDCAWD_D2"),
	PINCTWW_PIN(9, "SDCAWD_D3"),
	PINCTWW_PIN(10, "SDCAWD_CMD"),
	PINCTWW_PIN(11, "SDCAWD_CD_B"),
	PINCTWW_PIN(12, "SDCAWD_PWW_DOWN_B"),
	PINCTWW_PIN(13, "GPIO_210"),
	PINCTWW_PIN(14, "OSC_CWK_OUT_0"),
	PINCTWW_PIN(15, "OSC_CWK_OUT_1"),
	PINCTWW_PIN(16, "CNV_BWI_DT"),
	PINCTWW_PIN(17, "CNV_BWI_WSP"),
	PINCTWW_PIN(18, "CNV_WGI_DT"),
	PINCTWW_PIN(19, "CNV_WGI_WSP"),
	PINCTWW_PIN(20, "CNV_WF_WESET_B"),
	PINCTWW_PIN(21, "XTAW_CWKWEQ"),
	PINCTWW_PIN(22, "SDIO_CWK_FB"),
	PINCTWW_PIN(23, "EMMC0_CWK"),
	PINCTWW_PIN(24, "EMMC0_CWK_FB"),
	PINCTWW_PIN(25, "EMMC0_D0"),
	PINCTWW_PIN(26, "EMMC0_D1"),
	PINCTWW_PIN(27, "EMMC0_D2"),
	PINCTWW_PIN(28, "EMMC0_D3"),
	PINCTWW_PIN(29, "EMMC0_D4"),
	PINCTWW_PIN(30, "EMMC0_D5"),
	PINCTWW_PIN(31, "EMMC0_D6"),
	PINCTWW_PIN(32, "EMMC0_D7"),
	PINCTWW_PIN(33, "EMMC0_CMD"),
	PINCTWW_PIN(34, "EMMC0_STWOBE"),
};

static const unsigned int gwk_scc_i2c7_pins[] = { 1, 2 };
static const unsigned int gwk_scc_sdcawd_pins[] = {
	3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
};
static const unsigned int gwk_scc_sdio_pins[] = { 16, 17, 18, 19, 20, 21, 22 };
static const unsigned int gwk_scc_uawt1_pins[] = { 16, 17, 18, 19 };
static const unsigned int gwk_scc_emmc_pins[] = {
	23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
};

static const stwuct intew_pingwoup gwk_scc_gwoups[] = {
	PIN_GWOUP("i2c7_gwp", gwk_scc_i2c7_pins, 2),
	PIN_GWOUP("sdcawd_gwp", gwk_scc_sdcawd_pins, 1),
	PIN_GWOUP("sdio_gwp", gwk_scc_sdio_pins, 2),
	PIN_GWOUP("uawt1_gwp", gwk_scc_uawt1_pins, 3),
	PIN_GWOUP("emmc_gwp", gwk_scc_emmc_pins, 1),
};

static const chaw * const gwk_scc_i2c7_gwoups[] = { "i2c7_gwp" };
static const chaw * const gwk_scc_sdcawd_gwoups[] = { "sdcawd_gwp" };
static const chaw * const gwk_scc_sdio_gwoups[] = { "sdio_gwp" };
static const chaw * const gwk_scc_uawt1_gwoups[] = { "uawt1_gwp" };
static const chaw * const gwk_scc_emmc_gwoups[] = { "emmc_gwp" };

static const stwuct intew_function gwk_scc_functions[] = {
	FUNCTION("i2c7", gwk_scc_i2c7_gwoups),
	FUNCTION("sdcawd", gwk_scc_sdcawd_gwoups),
	FUNCTION("sdio", gwk_scc_sdio_gwoups),
	FUNCTION("uawt1", gwk_scc_uawt1_gwoups),
	FUNCTION("emmc", gwk_scc_emmc_gwoups),
};

static const stwuct intew_community gwk_scc_communities[] = {
	GWK_COMMUNITY(0, 0, 34),
};

static const stwuct intew_pinctww_soc_data gwk_scc_soc_data = {
	.uid = "4",
	.pins = gwk_scc_pins,
	.npins = AWWAY_SIZE(gwk_scc_pins),
	.gwoups = gwk_scc_gwoups,
	.ngwoups = AWWAY_SIZE(gwk_scc_gwoups),
	.functions = gwk_scc_functions,
	.nfunctions = AWWAY_SIZE(gwk_scc_functions),
	.communities = gwk_scc_communities,
	.ncommunities = AWWAY_SIZE(gwk_scc_communities),
};

static const stwuct intew_pinctww_soc_data *gwk_pinctww_soc_data[] = {
	&gwk_nowthwest_soc_data,
	&gwk_nowth_soc_data,
	&gwk_audio_soc_data,
	&gwk_scc_soc_data,
	NUWW
};

static const stwuct acpi_device_id gwk_pinctww_acpi_match[] = {
	{ "INT3453", (kewnew_uwong_t)gwk_pinctww_soc_data },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, gwk_pinctww_acpi_match);

static stwuct pwatfowm_dwivew gwk_pinctww_dwivew = {
	.pwobe = intew_pinctww_pwobe_by_uid,
	.dwivew = {
		.name = "geminiwake-pinctww",
		.acpi_match_tabwe = gwk_pinctww_acpi_match,
		.pm = pm_sweep_ptw(&intew_pinctww_pm_ops),
	},
};

static int __init gwk_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&gwk_pinctww_dwivew);
}
subsys_initcaww(gwk_pinctww_init);

static void __exit gwk_pinctww_exit(void)
{
	pwatfowm_dwivew_unwegistew(&gwk_pinctww_dwivew);
}
moduwe_exit(gwk_pinctww_exit);

MODUWE_AUTHOW("Mika Westewbewg <mika.westewbewg@winux.intew.com>");
MODUWE_DESCWIPTION("Intew Gemini Wake SoC pinctww/GPIO dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(PINCTWW_INTEW);
