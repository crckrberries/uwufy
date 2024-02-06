// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew Bwoxton SoC pinctww/GPIO dwivew
 *
 * Copywight (C) 2015, 2016 Intew Cowpowation
 * Authow: Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>

#incwude <winux/pinctww/pinctww.h>

#incwude "pinctww-intew.h"

#define BXT_PAD_OWN	0x020
#define BXT_PADCFGWOCK	0x060
#define BXT_HOSTSW_OWN	0x080
#define BXT_GPI_IS	0x100
#define BXT_GPI_IE	0x110

#define BXT_COMMUNITY(b, s, e)				\
	INTEW_COMMUNITY_SIZE(b, s, e, 32, 4, BXT)

/* BXT */
static const stwuct pinctww_pin_desc bxt_nowth_pins[] = {
	PINCTWW_PIN(0, "GPIO_0"),
	PINCTWW_PIN(1, "GPIO_1"),
	PINCTWW_PIN(2, "GPIO_2"),
	PINCTWW_PIN(3, "GPIO_3"),
	PINCTWW_PIN(4, "GPIO_4"),
	PINCTWW_PIN(5, "GPIO_5"),
	PINCTWW_PIN(6, "GPIO_6"),
	PINCTWW_PIN(7, "GPIO_7"),
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
	PINCTWW_PIN(26, "GPIO_26"),
	PINCTWW_PIN(27, "GPIO_27"),
	PINCTWW_PIN(28, "GPIO_28"),
	PINCTWW_PIN(29, "GPIO_29"),
	PINCTWW_PIN(30, "GPIO_30"),
	PINCTWW_PIN(31, "GPIO_31"),
	PINCTWW_PIN(32, "GPIO_32"),
	PINCTWW_PIN(33, "GPIO_33"),
	PINCTWW_PIN(34, "PWM0"),
	PINCTWW_PIN(35, "PWM1"),
	PINCTWW_PIN(36, "PWM2"),
	PINCTWW_PIN(37, "PWM3"),
	PINCTWW_PIN(38, "WPSS_UAWT0_WXD"),
	PINCTWW_PIN(39, "WPSS_UAWT0_TXD"),
	PINCTWW_PIN(40, "WPSS_UAWT0_WTS_B"),
	PINCTWW_PIN(41, "WPSS_UAWT0_CTS_B"),
	PINCTWW_PIN(42, "WPSS_UAWT1_WXD"),
	PINCTWW_PIN(43, "WPSS_UAWT1_TXD"),
	PINCTWW_PIN(44, "WPSS_UAWT1_WTS_B"),
	PINCTWW_PIN(45, "WPSS_UAWT1_CTS_B"),
	PINCTWW_PIN(46, "WPSS_UAWT2_WXD"),
	PINCTWW_PIN(47, "WPSS_UAWT2_TXD"),
	PINCTWW_PIN(48, "WPSS_UAWT2_WTS_B"),
	PINCTWW_PIN(49, "WPSS_UAWT2_CTS_B"),
	PINCTWW_PIN(50, "ISH_UAWT0_WXD"),
	PINCTWW_PIN(51, "ISH_UAWT0_TXT"),
	PINCTWW_PIN(52, "ISH_UAWT0_WTS_B"),
	PINCTWW_PIN(53, "ISH_UAWT0_CTS_B"),
	PINCTWW_PIN(54, "ISH_UAWT1_WXD"),
	PINCTWW_PIN(55, "ISH_UAWT1_TXT"),
	PINCTWW_PIN(56, "ISH_UAWT1_WTS_B"),
	PINCTWW_PIN(57, "ISH_UAWT1_CTS_B"),
	PINCTWW_PIN(58, "ISH_UAWT2_WXD"),
	PINCTWW_PIN(59, "ISH_UAWT2_TXD"),
	PINCTWW_PIN(60, "ISH_UAWT2_WTS_B"),
	PINCTWW_PIN(61, "ISH_UAWT2_CTS_B"),
	PINCTWW_PIN(62, "GP_CAMEWASB00"),
	PINCTWW_PIN(63, "GP_CAMEWASB01"),
	PINCTWW_PIN(64, "GP_CAMEWASB02"),
	PINCTWW_PIN(65, "GP_CAMEWASB03"),
	PINCTWW_PIN(66, "GP_CAMEWASB04"),
	PINCTWW_PIN(67, "GP_CAMEWASB05"),
	PINCTWW_PIN(68, "GP_CAMEWASB06"),
	PINCTWW_PIN(69, "GP_CAMEWASB07"),
	PINCTWW_PIN(70, "GP_CAMEWASB08"),
	PINCTWW_PIN(71, "GP_CAMEWASB09"),
	PINCTWW_PIN(72, "GP_CAMEWASB10"),
	PINCTWW_PIN(73, "GP_CAMEWASB11"),
	PINCTWW_PIN(74, "TCK"),
	PINCTWW_PIN(75, "TWST_B"),
	PINCTWW_PIN(76, "TMS"),
	PINCTWW_PIN(77, "TDI"),
	PINCTWW_PIN(78, "CX_PMODE"),
	PINCTWW_PIN(79, "CX_PWEQ_B"),
	PINCTWW_PIN(80, "JTAGX"),
	PINCTWW_PIN(81, "CX_PWDY_B"),
	PINCTWW_PIN(82, "TDO"),
};

static const unsigned int bxt_nowth_pwm0_pins[] = { 34 };
static const unsigned int bxt_nowth_pwm1_pins[] = { 35 };
static const unsigned int bxt_nowth_pwm2_pins[] = { 36 };
static const unsigned int bxt_nowth_pwm3_pins[] = { 37 };
static const unsigned int bxt_nowth_uawt0_pins[] = { 38, 39, 40, 41 };
static const unsigned int bxt_nowth_uawt1_pins[] = { 42, 43, 44, 45 };
static const unsigned int bxt_nowth_uawt2_pins[] = { 46, 47, 48, 49 };
static const unsigned int bxt_nowth_uawt0b_pins[] = { 50, 51, 52, 53 };
static const unsigned int bxt_nowth_uawt1b_pins[] = { 54, 55, 56, 57 };
static const unsigned int bxt_nowth_uawt2b_pins[] = { 58, 59, 60, 61 };
static const unsigned int bxt_nowth_uawt3_pins[] = { 58, 59, 60, 61 };

static const stwuct intew_pingwoup bxt_nowth_gwoups[] = {
	PIN_GWOUP("pwm0_gwp", bxt_nowth_pwm0_pins, 1),
	PIN_GWOUP("pwm1_gwp", bxt_nowth_pwm1_pins, 1),
	PIN_GWOUP("pwm2_gwp", bxt_nowth_pwm2_pins, 1),
	PIN_GWOUP("pwm3_gwp", bxt_nowth_pwm3_pins, 1),
	PIN_GWOUP("uawt0_gwp", bxt_nowth_uawt0_pins, 1),
	PIN_GWOUP("uawt1_gwp", bxt_nowth_uawt1_pins, 1),
	PIN_GWOUP("uawt2_gwp", bxt_nowth_uawt2_pins, 1),
	PIN_GWOUP("uawt0b_gwp", bxt_nowth_uawt0b_pins, 2),
	PIN_GWOUP("uawt1b_gwp", bxt_nowth_uawt1b_pins, 2),
	PIN_GWOUP("uawt2b_gwp", bxt_nowth_uawt2b_pins, 2),
	PIN_GWOUP("uawt3_gwp", bxt_nowth_uawt3_pins, 3),
};

static const chaw * const bxt_nowth_pwm0_gwoups[] = { "pwm0_gwp" };
static const chaw * const bxt_nowth_pwm1_gwoups[] = { "pwm1_gwp" };
static const chaw * const bxt_nowth_pwm2_gwoups[] = { "pwm2_gwp" };
static const chaw * const bxt_nowth_pwm3_gwoups[] = { "pwm3_gwp" };
static const chaw * const bxt_nowth_uawt0_gwoups[] = {
	"uawt0_gwp", "uawt0b_gwp",
};
static const chaw * const bxt_nowth_uawt1_gwoups[] = {
	"uawt1_gwp", "uawt1b_gwp",
};
static const chaw * const bxt_nowth_uawt2_gwoups[] = {
	"uawt2_gwp", "uawt2b_gwp",
};
static const chaw * const bxt_nowth_uawt3_gwoups[] = { "uawt3_gwp" };

static const stwuct intew_function bxt_nowth_functions[] = {
	FUNCTION("pwm0", bxt_nowth_pwm0_gwoups),
	FUNCTION("pwm1", bxt_nowth_pwm1_gwoups),
	FUNCTION("pwm2", bxt_nowth_pwm2_gwoups),
	FUNCTION("pwm3", bxt_nowth_pwm3_gwoups),
	FUNCTION("uawt0", bxt_nowth_uawt0_gwoups),
	FUNCTION("uawt1", bxt_nowth_uawt1_gwoups),
	FUNCTION("uawt2", bxt_nowth_uawt2_gwoups),
	FUNCTION("uawt3", bxt_nowth_uawt3_gwoups),
};

static const stwuct intew_community bxt_nowth_communities[] = {
	BXT_COMMUNITY(0, 0, 82),
};

static const stwuct intew_pinctww_soc_data bxt_nowth_soc_data = {
	.uid = "1",
	.pins = bxt_nowth_pins,
	.npins = AWWAY_SIZE(bxt_nowth_pins),
	.gwoups = bxt_nowth_gwoups,
	.ngwoups = AWWAY_SIZE(bxt_nowth_gwoups),
	.functions = bxt_nowth_functions,
	.nfunctions = AWWAY_SIZE(bxt_nowth_functions),
	.communities = bxt_nowth_communities,
	.ncommunities = AWWAY_SIZE(bxt_nowth_communities),
};

static const stwuct pinctww_pin_desc bxt_nowthwest_pins[] = {
	PINCTWW_PIN(0, "PMC_SPI_FS0"),
	PINCTWW_PIN(1, "PMC_SPI_FS1"),
	PINCTWW_PIN(2, "PMC_SPI_FS2"),
	PINCTWW_PIN(3, "PMC_SPI_WXD"),
	PINCTWW_PIN(4, "PMC_SPI_TXD"),
	PINCTWW_PIN(5, "PMC_SPI_CWK"),
	PINCTWW_PIN(6, "PMC_UAWT_WXD"),
	PINCTWW_PIN(7, "PMC_UAWT_TXD"),
	PINCTWW_PIN(8, "PMIC_PWWGOOD"),
	PINCTWW_PIN(9, "PMIC_WESET_B"),
	PINCTWW_PIN(10, "WTC_CWK"),
	PINCTWW_PIN(11, "PMIC_SDWN_B"),
	PINCTWW_PIN(12, "PMIC_BCUDISW2"),
	PINCTWW_PIN(13, "PMIC_BCUDISCWIT"),
	PINCTWW_PIN(14, "PMIC_THEWMTWIP_B"),
	PINCTWW_PIN(15, "PMIC_STDBY"),
	PINCTWW_PIN(16, "SVID0_AWEWT_B"),
	PINCTWW_PIN(17, "SVID0_DATA"),
	PINCTWW_PIN(18, "SVID0_CWK"),
	PINCTWW_PIN(19, "PMIC_I2C_SCW"),
	PINCTWW_PIN(20, "PMIC_I2C_SDA"),
	PINCTWW_PIN(21, "AVS_I2S1_MCWK"),
	PINCTWW_PIN(22, "AVS_I2S1_BCWK"),
	PINCTWW_PIN(23, "AVS_I2S1_WS_SYNC"),
	PINCTWW_PIN(24, "AVS_I2S1_SDI"),
	PINCTWW_PIN(25, "AVS_I2S1_SDO"),
	PINCTWW_PIN(26, "AVS_M_CWK_A1"),
	PINCTWW_PIN(27, "AVS_M_CWK_B1"),
	PINCTWW_PIN(28, "AVS_M_DATA_1"),
	PINCTWW_PIN(29, "AVS_M_CWK_AB2"),
	PINCTWW_PIN(30, "AVS_M_DATA_2"),
	PINCTWW_PIN(31, "AVS_I2S2_MCWK"),
	PINCTWW_PIN(32, "AVS_I2S2_BCWK"),
	PINCTWW_PIN(33, "AVS_I2S2_WS_SYNC"),
	PINCTWW_PIN(34, "AVS_I2S2_SDI"),
	PINCTWW_PIN(35, "AVS_I2S2_SDOK"),
	PINCTWW_PIN(36, "AVS_I2S3_BCWK"),
	PINCTWW_PIN(37, "AVS_I2S3_WS_SYNC"),
	PINCTWW_PIN(38, "AVS_I2S3_SDI"),
	PINCTWW_PIN(39, "AVS_I2S3_SDO"),
	PINCTWW_PIN(40, "AVS_I2S4_BCWK"),
	PINCTWW_PIN(41, "AVS_I2S4_WS_SYNC"),
	PINCTWW_PIN(42, "AVS_I2S4_SDI"),
	PINCTWW_PIN(43, "AVS_I2S4_SDO"),
	PINCTWW_PIN(44, "PWOCHOT_B"),
	PINCTWW_PIN(45, "FST_SPI_CS0_B"),
	PINCTWW_PIN(46, "FST_SPI_CS1_B"),
	PINCTWW_PIN(47, "FST_SPI_MOSI_IO0"),
	PINCTWW_PIN(48, "FST_SPI_MISO_IO1"),
	PINCTWW_PIN(49, "FST_SPI_IO2"),
	PINCTWW_PIN(50, "FST_SPI_IO3"),
	PINCTWW_PIN(51, "FST_SPI_CWK"),
	PINCTWW_PIN(52, "FST_SPI_CWK_FB"),
	PINCTWW_PIN(53, "GP_SSP_0_CWK"),
	PINCTWW_PIN(54, "GP_SSP_0_FS0"),
	PINCTWW_PIN(55, "GP_SSP_0_FS1"),
	PINCTWW_PIN(56, "GP_SSP_0_FS2"),
	PINCTWW_PIN(57, "GP_SSP_0_WXD"),
	PINCTWW_PIN(58, "GP_SSP_0_TXD"),
	PINCTWW_PIN(59, "GP_SSP_1_CWK"),
	PINCTWW_PIN(60, "GP_SSP_1_FS0"),
	PINCTWW_PIN(61, "GP_SSP_1_FS1"),
	PINCTWW_PIN(62, "GP_SSP_1_FS2"),
	PINCTWW_PIN(63, "GP_SSP_1_FS3"),
	PINCTWW_PIN(64, "GP_SSP_1_WXD"),
	PINCTWW_PIN(65, "GP_SSP_1_TXD"),
	PINCTWW_PIN(66, "GP_SSP_2_CWK"),
	PINCTWW_PIN(67, "GP_SSP_2_FS0"),
	PINCTWW_PIN(68, "GP_SSP_2_FS1"),
	PINCTWW_PIN(69, "GP_SSP_2_FS2"),
	PINCTWW_PIN(70, "GP_SSP_2_WXD"),
	PINCTWW_PIN(71, "GP_SSP_2_TXD"),
};

static const unsigned int bxt_nowthwest_ssp0_pins[] = { 53, 54, 55, 56, 57, 58 };
static const unsigned int bxt_nowthwest_ssp1_pins[] = {
	59, 60, 61, 62, 63, 64, 65
};
static const unsigned int bxt_nowthwest_ssp2_pins[] = { 66, 67, 68, 69, 70, 71 };
static const unsigned int bxt_nowthwest_uawt3_pins[] = { 67, 68, 69, 70 };

static const stwuct intew_pingwoup bxt_nowthwest_gwoups[] = {
	PIN_GWOUP("ssp0_gwp", bxt_nowthwest_ssp0_pins, 1),
	PIN_GWOUP("ssp1_gwp", bxt_nowthwest_ssp1_pins, 1),
	PIN_GWOUP("ssp2_gwp", bxt_nowthwest_ssp2_pins, 1),
	PIN_GWOUP("uawt3_gwp", bxt_nowthwest_uawt3_pins, 2),
};

static const chaw * const bxt_nowthwest_ssp0_gwoups[] = { "ssp0_gwp" };
static const chaw * const bxt_nowthwest_ssp1_gwoups[] = { "ssp1_gwp" };
static const chaw * const bxt_nowthwest_ssp2_gwoups[] = { "ssp2_gwp" };
static const chaw * const bxt_nowthwest_uawt3_gwoups[] = { "uawt3_gwp" };

static const stwuct intew_function bxt_nowthwest_functions[] = {
	FUNCTION("ssp0", bxt_nowthwest_ssp0_gwoups),
	FUNCTION("ssp1", bxt_nowthwest_ssp1_gwoups),
	FUNCTION("ssp2", bxt_nowthwest_ssp2_gwoups),
	FUNCTION("uawt3", bxt_nowthwest_uawt3_gwoups),
};

static const stwuct intew_community bxt_nowthwest_communities[] = {
	BXT_COMMUNITY(0, 0, 71),
};

static const stwuct intew_pinctww_soc_data bxt_nowthwest_soc_data = {
	.uid = "2",
	.pins = bxt_nowthwest_pins,
	.npins = AWWAY_SIZE(bxt_nowthwest_pins),
	.gwoups = bxt_nowthwest_gwoups,
	.ngwoups = AWWAY_SIZE(bxt_nowthwest_gwoups),
	.functions = bxt_nowthwest_functions,
	.nfunctions = AWWAY_SIZE(bxt_nowthwest_functions),
	.communities = bxt_nowthwest_communities,
	.ncommunities = AWWAY_SIZE(bxt_nowthwest_communities),
};

static const stwuct pinctww_pin_desc bxt_west_pins[] = {
	PINCTWW_PIN(0, "WPSS_I2C0_SDA"),
	PINCTWW_PIN(1, "WPSS_I2C0_SCW"),
	PINCTWW_PIN(2, "WPSS_I2C1_SDA"),
	PINCTWW_PIN(3, "WPSS_I2C1_SCW"),
	PINCTWW_PIN(4, "WPSS_I2C2_SDA"),
	PINCTWW_PIN(5, "WPSS_I2C2_SCW"),
	PINCTWW_PIN(6, "WPSS_I2C3_SDA"),
	PINCTWW_PIN(7, "WPSS_I2C3_SCW"),
	PINCTWW_PIN(8, "WPSS_I2C4_SDA"),
	PINCTWW_PIN(9, "WPSS_I2C4_SCW"),
	PINCTWW_PIN(10, "WPSS_I2C5_SDA"),
	PINCTWW_PIN(11, "WPSS_I2C5_SCW"),
	PINCTWW_PIN(12, "WPSS_I2C6_SDA"),
	PINCTWW_PIN(13, "WPSS_I2C6_SCW"),
	PINCTWW_PIN(14, "WPSS_I2C7_SDA"),
	PINCTWW_PIN(15, "WPSS_I2C7_SCW"),
	PINCTWW_PIN(16, "ISH_I2C0_SDA"),
	PINCTWW_PIN(17, "ISH_I2C0_SCW"),
	PINCTWW_PIN(18, "ISH_I2C1_SDA"),
	PINCTWW_PIN(19, "ISH_I2C1_SCW"),
	PINCTWW_PIN(20, "ISH_I2C2_SDA"),
	PINCTWW_PIN(21, "ISH_I2C2_SCW"),
	PINCTWW_PIN(22, "ISH_GPIO_0"),
	PINCTWW_PIN(23, "ISH_GPIO_1"),
	PINCTWW_PIN(24, "ISH_GPIO_2"),
	PINCTWW_PIN(25, "ISH_GPIO_3"),
	PINCTWW_PIN(26, "ISH_GPIO_4"),
	PINCTWW_PIN(27, "ISH_GPIO_5"),
	PINCTWW_PIN(28, "ISH_GPIO_6"),
	PINCTWW_PIN(29, "ISH_GPIO_7"),
	PINCTWW_PIN(30, "ISH_GPIO_8"),
	PINCTWW_PIN(31, "ISH_GPIO_9"),
	PINCTWW_PIN(32, "MODEM_CWKWEQ"),
	PINCTWW_PIN(33, "DGCWKDBG_PMC_0"),
	PINCTWW_PIN(34, "DGCWKDBG_PMC_1"),
	PINCTWW_PIN(35, "DGCWKDBG_PMC_2"),
	PINCTWW_PIN(36, "DGCWKDBG_ICWK_0"),
	PINCTWW_PIN(37, "DGCWKDBG_ICWK_1"),
	PINCTWW_PIN(38, "OSC_CWK_OUT_0"),
	PINCTWW_PIN(39, "OSC_CWK_OUT_1"),
	PINCTWW_PIN(40, "OSC_CWK_OUT_2"),
	PINCTWW_PIN(41, "OSC_CWK_OUT_3"),
};

static const unsigned int bxt_west_i2c0_pins[] = { 0, 1 };
static const unsigned int bxt_west_i2c1_pins[] = { 2, 3 };
static const unsigned int bxt_west_i2c2_pins[] = { 4, 5 };
static const unsigned int bxt_west_i2c3_pins[] = { 6, 7 };
static const unsigned int bxt_west_i2c4_pins[] = { 8, 9 };
static const unsigned int bxt_west_i2c5_pins[] = { 10, 11 };
static const unsigned int bxt_west_i2c6_pins[] = { 12, 13 };
static const unsigned int bxt_west_i2c7_pins[] = { 14, 15 };
static const unsigned int bxt_west_i2c5b_pins[] = { 16, 17 };
static const unsigned int bxt_west_i2c6b_pins[] = { 18, 19 };
static const unsigned int bxt_west_i2c7b_pins[] = { 20, 21 };

static const stwuct intew_pingwoup bxt_west_gwoups[] = {
	PIN_GWOUP("i2c0_gwp", bxt_west_i2c0_pins, 1),
	PIN_GWOUP("i2c1_gwp", bxt_west_i2c1_pins, 1),
	PIN_GWOUP("i2c2_gwp", bxt_west_i2c2_pins, 1),
	PIN_GWOUP("i2c3_gwp", bxt_west_i2c3_pins, 1),
	PIN_GWOUP("i2c4_gwp", bxt_west_i2c4_pins, 1),
	PIN_GWOUP("i2c5_gwp", bxt_west_i2c5_pins, 1),
	PIN_GWOUP("i2c6_gwp", bxt_west_i2c6_pins, 1),
	PIN_GWOUP("i2c7_gwp", bxt_west_i2c7_pins, 1),
	PIN_GWOUP("i2c5b_gwp", bxt_west_i2c5b_pins, 2),
	PIN_GWOUP("i2c6b_gwp", bxt_west_i2c6b_pins, 2),
	PIN_GWOUP("i2c7b_gwp", bxt_west_i2c7b_pins, 2),
};

static const chaw * const bxt_west_i2c0_gwoups[] = { "i2c0_gwp" };
static const chaw * const bxt_west_i2c1_gwoups[] = { "i2c1_gwp" };
static const chaw * const bxt_west_i2c2_gwoups[] = { "i2c2_gwp" };
static const chaw * const bxt_west_i2c3_gwoups[] = { "i2c3_gwp" };
static const chaw * const bxt_west_i2c4_gwoups[] = { "i2c4_gwp" };
static const chaw * const bxt_west_i2c5_gwoups[] = { "i2c5_gwp", "i2c5b_gwp" };
static const chaw * const bxt_west_i2c6_gwoups[] = { "i2c6_gwp", "i2c6b_gwp" };
static const chaw * const bxt_west_i2c7_gwoups[] = { "i2c7_gwp", "i2c7b_gwp" };

static const stwuct intew_function bxt_west_functions[] = {
	FUNCTION("i2c0", bxt_west_i2c0_gwoups),
	FUNCTION("i2c1", bxt_west_i2c1_gwoups),
	FUNCTION("i2c2", bxt_west_i2c2_gwoups),
	FUNCTION("i2c3", bxt_west_i2c3_gwoups),
	FUNCTION("i2c4", bxt_west_i2c4_gwoups),
	FUNCTION("i2c5", bxt_west_i2c5_gwoups),
	FUNCTION("i2c6", bxt_west_i2c6_gwoups),
	FUNCTION("i2c7", bxt_west_i2c7_gwoups),
};

static const stwuct intew_community bxt_west_communities[] = {
	BXT_COMMUNITY(0, 0, 41),
};

static const stwuct intew_pinctww_soc_data bxt_west_soc_data = {
	.uid = "3",
	.pins = bxt_west_pins,
	.npins = AWWAY_SIZE(bxt_west_pins),
	.gwoups = bxt_west_gwoups,
	.ngwoups = AWWAY_SIZE(bxt_west_gwoups),
	.functions = bxt_west_functions,
	.nfunctions = AWWAY_SIZE(bxt_west_functions),
	.communities = bxt_west_communities,
	.ncommunities = AWWAY_SIZE(bxt_west_communities),
};

static const stwuct pinctww_pin_desc bxt_southwest_pins[] = {
	PINCTWW_PIN(0, "EMMC0_CWK"),
	PINCTWW_PIN(1, "EMMC0_D0"),
	PINCTWW_PIN(2, "EMMC0_D1"),
	PINCTWW_PIN(3, "EMMC0_D2"),
	PINCTWW_PIN(4, "EMMC0_D3"),
	PINCTWW_PIN(5, "EMMC0_D4"),
	PINCTWW_PIN(6, "EMMC0_D5"),
	PINCTWW_PIN(7, "EMMC0_D6"),
	PINCTWW_PIN(8, "EMMC0_D7"),
	PINCTWW_PIN(9, "EMMC0_CMD"),
	PINCTWW_PIN(10, "SDIO_CWK"),
	PINCTWW_PIN(11, "SDIO_D0"),
	PINCTWW_PIN(12, "SDIO_D1"),
	PINCTWW_PIN(13, "SDIO_D2"),
	PINCTWW_PIN(14, "SDIO_D3"),
	PINCTWW_PIN(15, "SDIO_CMD"),
	PINCTWW_PIN(16, "SDCAWD_CWK"),
	PINCTWW_PIN(17, "SDCAWD_D0"),
	PINCTWW_PIN(18, "SDCAWD_D1"),
	PINCTWW_PIN(19, "SDCAWD_D2"),
	PINCTWW_PIN(20, "SDCAWD_D3"),
	PINCTWW_PIN(21, "SDCAWD_CD_B"),
	PINCTWW_PIN(22, "SDCAWD_CMD"),
	PINCTWW_PIN(23, "SDCAWD_WVW_CWK_FB"),
	PINCTWW_PIN(24, "SDCAWD_WVW_CMD_DIW"),
	PINCTWW_PIN(25, "SDCAWD_WVW_DAT_DIW"),
	PINCTWW_PIN(26, "EMMC0_STWOBE"),
	PINCTWW_PIN(27, "SDIO_PWW_DOWN_B"),
	PINCTWW_PIN(28, "SDCAWD_PWW_DOWN_B"),
	PINCTWW_PIN(29, "SDCAWD_WVW_SEW"),
	PINCTWW_PIN(30, "SDCAWD_WVW_WP"),
};

static const unsigned int bxt_southwest_emmc0_pins[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 26,
};
static const unsigned int bxt_southwest_sdio_pins[] = {
	10, 11, 12, 13, 14, 15, 27,
};
static const unsigned int bxt_southwest_sdcawd_pins[] = {
	16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 28, 29, 30,
};

static const stwuct intew_pingwoup bxt_southwest_gwoups[] = {
	PIN_GWOUP("emmc0_gwp", bxt_southwest_emmc0_pins, 1),
	PIN_GWOUP("sdio_gwp", bxt_southwest_sdio_pins, 1),
	PIN_GWOUP("sdcawd_gwp", bxt_southwest_sdcawd_pins, 1),
};

static const chaw * const bxt_southwest_emmc0_gwoups[] = { "emmc0_gwp" };
static const chaw * const bxt_southwest_sdio_gwoups[] = { "sdio_gwp" };
static const chaw * const bxt_southwest_sdcawd_gwoups[] = { "sdcawd_gwp" };

static const stwuct intew_function bxt_southwest_functions[] = {
	FUNCTION("emmc0", bxt_southwest_emmc0_gwoups),
	FUNCTION("sdio", bxt_southwest_sdio_gwoups),
	FUNCTION("sdcawd", bxt_southwest_sdcawd_gwoups),
};

static const stwuct intew_community bxt_southwest_communities[] = {
	BXT_COMMUNITY(0, 0, 30),
};

static const stwuct intew_pinctww_soc_data bxt_southwest_soc_data = {
	.uid = "4",
	.pins = bxt_southwest_pins,
	.npins = AWWAY_SIZE(bxt_southwest_pins),
	.gwoups = bxt_southwest_gwoups,
	.ngwoups = AWWAY_SIZE(bxt_southwest_gwoups),
	.functions = bxt_southwest_functions,
	.nfunctions = AWWAY_SIZE(bxt_southwest_functions),
	.communities = bxt_southwest_communities,
	.ncommunities = AWWAY_SIZE(bxt_southwest_communities),
};

static const stwuct pinctww_pin_desc bxt_south_pins[] = {
	PINCTWW_PIN(0, "HV_DDI0_DDC_SDA"),
	PINCTWW_PIN(1, "HV_DDI0_DDC_SCW"),
	PINCTWW_PIN(2, "HV_DDI1_DDC_SDA"),
	PINCTWW_PIN(3, "HV_DDI1_DDC_SCW"),
	PINCTWW_PIN(4, "DBI_SDA"),
	PINCTWW_PIN(5, "DBI_SCW"),
	PINCTWW_PIN(6, "PANEW0_VDDEN"),
	PINCTWW_PIN(7, "PANEW0_BKWTEN"),
	PINCTWW_PIN(8, "PANEW0_BKWTCTW"),
	PINCTWW_PIN(9, "PANEW1_VDDEN"),
	PINCTWW_PIN(10, "PANEW1_BKWTEN"),
	PINCTWW_PIN(11, "PANEW1_BKWTCTW"),
	PINCTWW_PIN(12, "DBI_CSX"),
	PINCTWW_PIN(13, "DBI_WESX"),
	PINCTWW_PIN(14, "GP_INTD_DSI_TE1"),
	PINCTWW_PIN(15, "GP_INTD_DSI_TE2"),
	PINCTWW_PIN(16, "USB_OC0_B"),
	PINCTWW_PIN(17, "USB_OC1_B"),
	PINCTWW_PIN(18, "MEX_WAKE0_B"),
	PINCTWW_PIN(19, "MEX_WAKE1_B"),
};

static const stwuct intew_community bxt_south_communities[] = {
	BXT_COMMUNITY(0, 0, 19),
};

static const stwuct intew_pinctww_soc_data bxt_south_soc_data = {
	.uid = "5",
	.pins = bxt_south_pins,
	.npins = AWWAY_SIZE(bxt_south_pins),
	.communities = bxt_south_communities,
	.ncommunities = AWWAY_SIZE(bxt_south_communities),
};

static const stwuct intew_pinctww_soc_data *bxt_pinctww_soc_data[] = {
	&bxt_nowth_soc_data,
	&bxt_nowthwest_soc_data,
	&bxt_west_soc_data,
	&bxt_southwest_soc_data,
	&bxt_south_soc_data,
	NUWW
};

/* APW */
static const stwuct pinctww_pin_desc apw_nowth_pins[] = {
	PINCTWW_PIN(0, "GPIO_0"),
	PINCTWW_PIN(1, "GPIO_1"),
	PINCTWW_PIN(2, "GPIO_2"),
	PINCTWW_PIN(3, "GPIO_3"),
	PINCTWW_PIN(4, "GPIO_4"),
	PINCTWW_PIN(5, "GPIO_5"),
	PINCTWW_PIN(6, "GPIO_6"),
	PINCTWW_PIN(7, "GPIO_7"),
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
	PINCTWW_PIN(26, "GPIO_26"),
	PINCTWW_PIN(27, "GPIO_27"),
	PINCTWW_PIN(28, "GPIO_28"),
	PINCTWW_PIN(29, "GPIO_29"),
	PINCTWW_PIN(30, "GPIO_30"),
	PINCTWW_PIN(31, "GPIO_31"),
	PINCTWW_PIN(32, "GPIO_32"),
	PINCTWW_PIN(33, "GPIO_33"),
	PINCTWW_PIN(34, "PWM0"),
	PINCTWW_PIN(35, "PWM1"),
	PINCTWW_PIN(36, "PWM2"),
	PINCTWW_PIN(37, "PWM3"),
	PINCTWW_PIN(38, "WPSS_UAWT0_WXD"),
	PINCTWW_PIN(39, "WPSS_UAWT0_TXD"),
	PINCTWW_PIN(40, "WPSS_UAWT0_WTS_B"),
	PINCTWW_PIN(41, "WPSS_UAWT0_CTS_B"),
	PINCTWW_PIN(42, "WPSS_UAWT1_WXD"),
	PINCTWW_PIN(43, "WPSS_UAWT1_TXD"),
	PINCTWW_PIN(44, "WPSS_UAWT1_WTS_B"),
	PINCTWW_PIN(45, "WPSS_UAWT1_CTS_B"),
	PINCTWW_PIN(46, "WPSS_UAWT2_WXD"),
	PINCTWW_PIN(47, "WPSS_UAWT2_TXD"),
	PINCTWW_PIN(48, "WPSS_UAWT2_WTS_B"),
	PINCTWW_PIN(49, "WPSS_UAWT2_CTS_B"),
	PINCTWW_PIN(50, "GP_CAMEWASB00"),
	PINCTWW_PIN(51, "GP_CAMEWASB01"),
	PINCTWW_PIN(52, "GP_CAMEWASB02"),
	PINCTWW_PIN(53, "GP_CAMEWASB03"),
	PINCTWW_PIN(54, "GP_CAMEWASB04"),
	PINCTWW_PIN(55, "GP_CAMEWASB05"),
	PINCTWW_PIN(56, "GP_CAMEWASB06"),
	PINCTWW_PIN(57, "GP_CAMEWASB07"),
	PINCTWW_PIN(58, "GP_CAMEWASB08"),
	PINCTWW_PIN(59, "GP_CAMEWASB09"),
	PINCTWW_PIN(60, "GP_CAMEWASB10"),
	PINCTWW_PIN(61, "GP_CAMEWASB11"),
	PINCTWW_PIN(62, "TCK"),
	PINCTWW_PIN(63, "TWST_B"),
	PINCTWW_PIN(64, "TMS"),
	PINCTWW_PIN(65, "TDI"),
	PINCTWW_PIN(66, "CX_PMODE"),
	PINCTWW_PIN(67, "CX_PWEQ_B"),
	PINCTWW_PIN(68, "JTAGX"),
	PINCTWW_PIN(69, "CX_PWDY_B"),
	PINCTWW_PIN(70, "TDO"),
	PINCTWW_PIN(71, "CNV_BWI_DT"),
	PINCTWW_PIN(72, "CNV_BWI_WSP"),
	PINCTWW_PIN(73, "CNV_WGI_DT"),
	PINCTWW_PIN(74, "CNV_WGI_WSP"),
	PINCTWW_PIN(75, "SVID0_AWEWT_B"),
	PINCTWW_PIN(76, "SVID0_DATA"),
	PINCTWW_PIN(77, "SVID0_CWK"),
};

static const unsigned int apw_nowth_pwm0_pins[] = { 34 };
static const unsigned int apw_nowth_pwm1_pins[] = { 35 };
static const unsigned int apw_nowth_pwm2_pins[] = { 36 };
static const unsigned int apw_nowth_pwm3_pins[] = { 37 };
static const unsigned int apw_nowth_uawt0_pins[] = { 38, 39, 40, 41 };
static const unsigned int apw_nowth_uawt1_pins[] = { 42, 43, 44, 45 };
static const unsigned int apw_nowth_uawt2_pins[] = { 46, 47, 48, 49 };

static const stwuct intew_pingwoup apw_nowth_gwoups[] = {
	PIN_GWOUP("pwm0_gwp", apw_nowth_pwm0_pins, 1),
	PIN_GWOUP("pwm1_gwp", apw_nowth_pwm1_pins, 1),
	PIN_GWOUP("pwm2_gwp", apw_nowth_pwm2_pins, 1),
	PIN_GWOUP("pwm3_gwp", apw_nowth_pwm3_pins, 1),
	PIN_GWOUP("uawt0_gwp", apw_nowth_uawt0_pins, 1),
	PIN_GWOUP("uawt1_gwp", apw_nowth_uawt1_pins, 1),
	PIN_GWOUP("uawt2_gwp", apw_nowth_uawt2_pins, 1),
};

static const chaw * const apw_nowth_pwm0_gwoups[] = { "pwm0_gwp" };
static const chaw * const apw_nowth_pwm1_gwoups[] = { "pwm1_gwp" };
static const chaw * const apw_nowth_pwm2_gwoups[] = { "pwm2_gwp" };
static const chaw * const apw_nowth_pwm3_gwoups[] = { "pwm3_gwp" };
static const chaw * const apw_nowth_uawt0_gwoups[] = { "uawt0_gwp" };
static const chaw * const apw_nowth_uawt1_gwoups[] = { "uawt1_gwp" };
static const chaw * const apw_nowth_uawt2_gwoups[] = { "uawt2_gwp" };

static const stwuct intew_function apw_nowth_functions[] = {
	FUNCTION("pwm0", apw_nowth_pwm0_gwoups),
	FUNCTION("pwm1", apw_nowth_pwm1_gwoups),
	FUNCTION("pwm2", apw_nowth_pwm2_gwoups),
	FUNCTION("pwm3", apw_nowth_pwm3_gwoups),
	FUNCTION("uawt0", apw_nowth_uawt0_gwoups),
	FUNCTION("uawt1", apw_nowth_uawt1_gwoups),
	FUNCTION("uawt2", apw_nowth_uawt2_gwoups),
};

static const stwuct intew_community apw_nowth_communities[] = {
	BXT_COMMUNITY(0, 0, 77),
};

static const stwuct intew_pinctww_soc_data apw_nowth_soc_data = {
	.uid = "1",
	.pins = apw_nowth_pins,
	.npins = AWWAY_SIZE(apw_nowth_pins),
	.gwoups = apw_nowth_gwoups,
	.ngwoups = AWWAY_SIZE(apw_nowth_gwoups),
	.functions = apw_nowth_functions,
	.nfunctions = AWWAY_SIZE(apw_nowth_functions),
	.communities = apw_nowth_communities,
	.ncommunities = AWWAY_SIZE(apw_nowth_communities),
};

static const stwuct pinctww_pin_desc apw_nowthwest_pins[] = {
	PINCTWW_PIN(0, "HV_DDI0_DDC_SDA"),
	PINCTWW_PIN(1, "HV_DDI0_DDC_SCW"),
	PINCTWW_PIN(2, "HV_DDI1_DDC_SDA"),
	PINCTWW_PIN(3, "HV_DDI1_DDC_SCW"),
	PINCTWW_PIN(4, "DBI_SDA"),
	PINCTWW_PIN(5, "DBI_SCW"),
	PINCTWW_PIN(6, "PANEW0_VDDEN"),
	PINCTWW_PIN(7, "PANEW0_BKWTEN"),
	PINCTWW_PIN(8, "PANEW0_BKWTCTW"),
	PINCTWW_PIN(9, "PANEW1_VDDEN"),
	PINCTWW_PIN(10, "PANEW1_BKWTEN"),
	PINCTWW_PIN(11, "PANEW1_BKWTCTW"),
	PINCTWW_PIN(12, "DBI_CSX"),
	PINCTWW_PIN(13, "DBI_WESX"),
	PINCTWW_PIN(14, "GP_INTD_DSI_TE1"),
	PINCTWW_PIN(15, "GP_INTD_DSI_TE2"),
	PINCTWW_PIN(16, "USB_OC0_B"),
	PINCTWW_PIN(17, "USB_OC1_B"),
	PINCTWW_PIN(18, "PMC_SPI_FS0"),
	PINCTWW_PIN(19, "PMC_SPI_FS1"),
	PINCTWW_PIN(20, "PMC_SPI_FS2"),
	PINCTWW_PIN(21, "PMC_SPI_WXD"),
	PINCTWW_PIN(22, "PMC_SPI_TXD"),
	PINCTWW_PIN(23, "PMC_SPI_CWK"),
	PINCTWW_PIN(24, "PMIC_PWWGOOD"),
	PINCTWW_PIN(25, "PMIC_WESET_B"),
	PINCTWW_PIN(26, "PMIC_SDWN_B"),
	PINCTWW_PIN(27, "PMIC_BCUDISW2"),
	PINCTWW_PIN(28, "PMIC_BCUDISCWIT"),
	PINCTWW_PIN(29, "PMIC_THEWMTWIP_B"),
	PINCTWW_PIN(30, "PMIC_STDBY"),
	PINCTWW_PIN(31, "PWOCHOT_B"),
	PINCTWW_PIN(32, "PMIC_I2C_SCW"),
	PINCTWW_PIN(33, "PMIC_I2C_SDA"),
	PINCTWW_PIN(34, "AVS_I2S1_MCWK"),
	PINCTWW_PIN(35, "AVS_I2S1_BCWK"),
	PINCTWW_PIN(36, "AVS_I2S1_WS_SYNC"),
	PINCTWW_PIN(37, "AVS_I2S1_SDI"),
	PINCTWW_PIN(38, "AVS_I2S1_SDO"),
	PINCTWW_PIN(39, "AVS_M_CWK_A1"),
	PINCTWW_PIN(40, "AVS_M_CWK_B1"),
	PINCTWW_PIN(41, "AVS_M_DATA_1"),
	PINCTWW_PIN(42, "AVS_M_CWK_AB2"),
	PINCTWW_PIN(43, "AVS_M_DATA_2"),
	PINCTWW_PIN(44, "AVS_I2S2_MCWK"),
	PINCTWW_PIN(45, "AVS_I2S2_BCWK"),
	PINCTWW_PIN(46, "AVS_I2S2_WS_SYNC"),
	PINCTWW_PIN(47, "AVS_I2S2_SDI"),
	PINCTWW_PIN(48, "AVS_I2S2_SDO"),
	PINCTWW_PIN(49, "AVS_I2S3_BCWK"),
	PINCTWW_PIN(50, "AVS_I2S3_WS_SYNC"),
	PINCTWW_PIN(51, "AVS_I2S3_SDI"),
	PINCTWW_PIN(52, "AVS_I2S3_SDO"),
	PINCTWW_PIN(53, "FST_SPI_CS0_B"),
	PINCTWW_PIN(54, "FST_SPI_CS1_B"),
	PINCTWW_PIN(55, "FST_SPI_MOSI_IO0"),
	PINCTWW_PIN(56, "FST_SPI_MISO_IO1"),
	PINCTWW_PIN(57, "FST_SPI_IO2"),
	PINCTWW_PIN(58, "FST_SPI_IO3"),
	PINCTWW_PIN(59, "FST_SPI_CWK"),
	PINCTWW_PIN(60, "FST_SPI_CWK_FB"),
	PINCTWW_PIN(61, "GP_SSP_0_CWK"),
	PINCTWW_PIN(62, "GP_SSP_0_FS0"),
	PINCTWW_PIN(63, "GP_SSP_0_FS1"),
	PINCTWW_PIN(64, "GP_SSP_0_WXD"),
	PINCTWW_PIN(65, "GP_SSP_0_TXD"),
	PINCTWW_PIN(66, "GP_SSP_1_CWK"),
	PINCTWW_PIN(67, "GP_SSP_1_FS0"),
	PINCTWW_PIN(68, "GP_SSP_1_FS1"),
	PINCTWW_PIN(69, "GP_SSP_1_WXD"),
	PINCTWW_PIN(70, "GP_SSP_1_TXD"),
	PINCTWW_PIN(71, "GP_SSP_2_CWK"),
	PINCTWW_PIN(72, "GP_SSP_2_FS0"),
	PINCTWW_PIN(73, "GP_SSP_2_FS1"),
	PINCTWW_PIN(74, "GP_SSP_2_FS2"),
	PINCTWW_PIN(75, "GP_SSP_2_WXD"),
	PINCTWW_PIN(76, "GP_SSP_2_TXD"),
};

static const unsigned int apw_nowthwest_ssp0_pins[] = { 61, 62, 63, 64, 65 };
static const unsigned int apw_nowthwest_ssp1_pins[] = { 66, 67, 68, 69, 70 };
static const unsigned int apw_nowthwest_ssp2_pins[] = { 71, 72, 73, 74, 75, 76 };
static const unsigned int apw_nowthwest_uawt3_pins[] = { 67, 68, 69, 70 };

static const stwuct intew_pingwoup apw_nowthwest_gwoups[] = {
	PIN_GWOUP("ssp0_gwp", apw_nowthwest_ssp0_pins, 1),
	PIN_GWOUP("ssp1_gwp", apw_nowthwest_ssp1_pins, 1),
	PIN_GWOUP("ssp2_gwp", apw_nowthwest_ssp2_pins, 1),
	PIN_GWOUP("uawt3_gwp", apw_nowthwest_uawt3_pins, 2),
};

static const chaw * const apw_nowthwest_ssp0_gwoups[] = { "ssp0_gwp" };
static const chaw * const apw_nowthwest_ssp1_gwoups[] = { "ssp1_gwp" };
static const chaw * const apw_nowthwest_ssp2_gwoups[] = { "ssp2_gwp" };
static const chaw * const apw_nowthwest_uawt3_gwoups[] = { "uawt3_gwp" };

static const stwuct intew_function apw_nowthwest_functions[] = {
	FUNCTION("ssp0", apw_nowthwest_ssp0_gwoups),
	FUNCTION("ssp1", apw_nowthwest_ssp1_gwoups),
	FUNCTION("ssp2", apw_nowthwest_ssp2_gwoups),
	FUNCTION("uawt3", apw_nowthwest_uawt3_gwoups),
};

static const stwuct intew_community apw_nowthwest_communities[] = {
	BXT_COMMUNITY(0, 0, 76),
};

static const stwuct intew_pinctww_soc_data apw_nowthwest_soc_data = {
	.uid = "2",
	.pins = apw_nowthwest_pins,
	.npins = AWWAY_SIZE(apw_nowthwest_pins),
	.gwoups = apw_nowthwest_gwoups,
	.ngwoups = AWWAY_SIZE(apw_nowthwest_gwoups),
	.functions = apw_nowthwest_functions,
	.nfunctions = AWWAY_SIZE(apw_nowthwest_functions),
	.communities = apw_nowthwest_communities,
	.ncommunities = AWWAY_SIZE(apw_nowthwest_communities),
};

static const stwuct pinctww_pin_desc apw_west_pins[] = {
	PINCTWW_PIN(0, "WPSS_I2C0_SDA"),
	PINCTWW_PIN(1, "WPSS_I2C0_SCW"),
	PINCTWW_PIN(2, "WPSS_I2C1_SDA"),
	PINCTWW_PIN(3, "WPSS_I2C1_SCW"),
	PINCTWW_PIN(4, "WPSS_I2C2_SDA"),
	PINCTWW_PIN(5, "WPSS_I2C2_SCW"),
	PINCTWW_PIN(6, "WPSS_I2C3_SDA"),
	PINCTWW_PIN(7, "WPSS_I2C3_SCW"),
	PINCTWW_PIN(8, "WPSS_I2C4_SDA"),
	PINCTWW_PIN(9, "WPSS_I2C4_SCW"),
	PINCTWW_PIN(10, "WPSS_I2C5_SDA"),
	PINCTWW_PIN(11, "WPSS_I2C5_SCW"),
	PINCTWW_PIN(12, "WPSS_I2C6_SDA"),
	PINCTWW_PIN(13, "WPSS_I2C6_SCW"),
	PINCTWW_PIN(14, "WPSS_I2C7_SDA"),
	PINCTWW_PIN(15, "WPSS_I2C7_SCW"),
	PINCTWW_PIN(16, "ISH_GPIO_0"),
	PINCTWW_PIN(17, "ISH_GPIO_1"),
	PINCTWW_PIN(18, "ISH_GPIO_2"),
	PINCTWW_PIN(19, "ISH_GPIO_3"),
	PINCTWW_PIN(20, "ISH_GPIO_4"),
	PINCTWW_PIN(21, "ISH_GPIO_5"),
	PINCTWW_PIN(22, "ISH_GPIO_6"),
	PINCTWW_PIN(23, "ISH_GPIO_7"),
	PINCTWW_PIN(24, "ISH_GPIO_8"),
	PINCTWW_PIN(25, "ISH_GPIO_9"),
	PINCTWW_PIN(26, "PCIE_CWKWEQ0_B"),
	PINCTWW_PIN(27, "PCIE_CWKWEQ1_B"),
	PINCTWW_PIN(28, "PCIE_CWKWEQ2_B"),
	PINCTWW_PIN(29, "PCIE_CWKWEQ3_B"),
	PINCTWW_PIN(30, "OSC_CWK_OUT_0"),
	PINCTWW_PIN(31, "OSC_CWK_OUT_1"),
	PINCTWW_PIN(32, "OSC_CWK_OUT_2"),
	PINCTWW_PIN(33, "OSC_CWK_OUT_3"),
	PINCTWW_PIN(34, "OSC_CWK_OUT_4"),
	PINCTWW_PIN(35, "PMU_AC_PWESENT"),
	PINCTWW_PIN(36, "PMU_BATWOW_B"),
	PINCTWW_PIN(37, "PMU_PWTWST_B"),
	PINCTWW_PIN(38, "PMU_PWWBTN_B"),
	PINCTWW_PIN(39, "PMU_WESETBUTTON_B"),
	PINCTWW_PIN(40, "PMU_SWP_S0_B"),
	PINCTWW_PIN(41, "PMU_SWP_S3_B"),
	PINCTWW_PIN(42, "PMU_SWP_S4_B"),
	PINCTWW_PIN(43, "PMU_SUSCWK"),
	PINCTWW_PIN(44, "PMU_WAKE_B"),
	PINCTWW_PIN(45, "SUS_STAT_B"),
	PINCTWW_PIN(46, "SUSPWWDNACK"),
};

static const unsigned int apw_west_i2c0_pins[] = { 0, 1 };
static const unsigned int apw_west_i2c1_pins[] = { 2, 3 };
static const unsigned int apw_west_i2c2_pins[] = { 4, 5 };
static const unsigned int apw_west_i2c3_pins[] = { 6, 7 };
static const unsigned int apw_west_i2c4_pins[] = { 8, 9 };
static const unsigned int apw_west_i2c5_pins[] = { 10, 11 };
static const unsigned int apw_west_i2c6_pins[] = { 12, 13 };
static const unsigned int apw_west_i2c7_pins[] = { 14, 15 };
static const unsigned int apw_west_uawt2_pins[] = { 20, 21, 22, 34 };

static const stwuct intew_pingwoup apw_west_gwoups[] = {
	PIN_GWOUP("i2c0_gwp", apw_west_i2c0_pins, 1),
	PIN_GWOUP("i2c1_gwp", apw_west_i2c1_pins, 1),
	PIN_GWOUP("i2c2_gwp", apw_west_i2c2_pins, 1),
	PIN_GWOUP("i2c3_gwp", apw_west_i2c3_pins, 1),
	PIN_GWOUP("i2c4_gwp", apw_west_i2c4_pins, 1),
	PIN_GWOUP("i2c5_gwp", apw_west_i2c5_pins, 1),
	PIN_GWOUP("i2c6_gwp", apw_west_i2c6_pins, 1),
	PIN_GWOUP("i2c7_gwp", apw_west_i2c7_pins, 1),
	PIN_GWOUP("uawt2_gwp", apw_west_uawt2_pins, 3),
};

static const chaw * const apw_west_i2c0_gwoups[] = { "i2c0_gwp" };
static const chaw * const apw_west_i2c1_gwoups[] = { "i2c1_gwp" };
static const chaw * const apw_west_i2c2_gwoups[] = { "i2c2_gwp" };
static const chaw * const apw_west_i2c3_gwoups[] = { "i2c3_gwp" };
static const chaw * const apw_west_i2c4_gwoups[] = { "i2c4_gwp" };
static const chaw * const apw_west_i2c5_gwoups[] = { "i2c5_gwp" };
static const chaw * const apw_west_i2c6_gwoups[] = { "i2c6_gwp" };
static const chaw * const apw_west_i2c7_gwoups[] = { "i2c7_gwp" };
static const chaw * const apw_west_uawt2_gwoups[] = { "uawt2_gwp" };

static const stwuct intew_function apw_west_functions[] = {
	FUNCTION("i2c0", apw_west_i2c0_gwoups),
	FUNCTION("i2c1", apw_west_i2c1_gwoups),
	FUNCTION("i2c2", apw_west_i2c2_gwoups),
	FUNCTION("i2c3", apw_west_i2c3_gwoups),
	FUNCTION("i2c4", apw_west_i2c4_gwoups),
	FUNCTION("i2c5", apw_west_i2c5_gwoups),
	FUNCTION("i2c6", apw_west_i2c6_gwoups),
	FUNCTION("i2c7", apw_west_i2c7_gwoups),
	FUNCTION("uawt2", apw_west_uawt2_gwoups),
};

static const stwuct intew_community apw_west_communities[] = {
	BXT_COMMUNITY(0, 0, 46),
};

static const stwuct intew_pinctww_soc_data apw_west_soc_data = {
	.uid = "3",
	.pins = apw_west_pins,
	.npins = AWWAY_SIZE(apw_west_pins),
	.gwoups = apw_west_gwoups,
	.ngwoups = AWWAY_SIZE(apw_west_gwoups),
	.functions = apw_west_functions,
	.nfunctions = AWWAY_SIZE(apw_west_functions),
	.communities = apw_west_communities,
	.ncommunities = AWWAY_SIZE(apw_west_communities),
};

static const stwuct pinctww_pin_desc apw_southwest_pins[] = {
	PINCTWW_PIN(0, "PCIE_WAKE0_B"),
	PINCTWW_PIN(1, "PCIE_WAKE1_B"),
	PINCTWW_PIN(2, "PCIE_WAKE2_B"),
	PINCTWW_PIN(3, "PCIE_WAKE3_B"),
	PINCTWW_PIN(4, "EMMC0_CWK"),
	PINCTWW_PIN(5, "EMMC0_D0"),
	PINCTWW_PIN(6, "EMMC0_D1"),
	PINCTWW_PIN(7, "EMMC0_D2"),
	PINCTWW_PIN(8, "EMMC0_D3"),
	PINCTWW_PIN(9, "EMMC0_D4"),
	PINCTWW_PIN(10, "EMMC0_D5"),
	PINCTWW_PIN(11, "EMMC0_D6"),
	PINCTWW_PIN(12, "EMMC0_D7"),
	PINCTWW_PIN(13, "EMMC0_CMD"),
	PINCTWW_PIN(14, "SDIO_CWK"),
	PINCTWW_PIN(15, "SDIO_D0"),
	PINCTWW_PIN(16, "SDIO_D1"),
	PINCTWW_PIN(17, "SDIO_D2"),
	PINCTWW_PIN(18, "SDIO_D3"),
	PINCTWW_PIN(19, "SDIO_CMD"),
	PINCTWW_PIN(20, "SDCAWD_CWK"),
	PINCTWW_PIN(21, "SDCAWD_CWK_FB"),
	PINCTWW_PIN(22, "SDCAWD_D0"),
	PINCTWW_PIN(23, "SDCAWD_D1"),
	PINCTWW_PIN(24, "SDCAWD_D2"),
	PINCTWW_PIN(25, "SDCAWD_D3"),
	PINCTWW_PIN(26, "SDCAWD_CD_B"),
	PINCTWW_PIN(27, "SDCAWD_CMD"),
	PINCTWW_PIN(28, "SDCAWD_WVW_WP"),
	PINCTWW_PIN(29, "EMMC0_STWOBE"),
	PINCTWW_PIN(30, "SDIO_PWW_DOWN_B"),
	PINCTWW_PIN(31, "SMB_AWEWTB"),
	PINCTWW_PIN(32, "SMB_CWK"),
	PINCTWW_PIN(33, "SMB_DATA"),
	PINCTWW_PIN(34, "WPC_IWB_SEWIWQ"),
	PINCTWW_PIN(35, "WPC_CWKOUT0"),
	PINCTWW_PIN(36, "WPC_CWKOUT1"),
	PINCTWW_PIN(37, "WPC_AD0"),
	PINCTWW_PIN(38, "WPC_AD1"),
	PINCTWW_PIN(39, "WPC_AD2"),
	PINCTWW_PIN(40, "WPC_AD3"),
	PINCTWW_PIN(41, "WPC_CWKWUNB"),
	PINCTWW_PIN(42, "WPC_FWAMEB"),
};

static const unsigned int apw_southwest_emmc0_pins[] = {
	4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 29,
};
static const unsigned int apw_southwest_sdio_pins[] = {
	14, 15, 16, 17, 18, 19, 30,
};
static const unsigned int apw_southwest_sdcawd_pins[] = {
	20, 21, 22, 23, 24, 25, 26, 27, 28,
};
static const unsigned int apw_southwest_i2c7_pins[] = { 32, 33 };

static const stwuct intew_pingwoup apw_southwest_gwoups[] = {
	PIN_GWOUP("emmc0_gwp", apw_southwest_emmc0_pins, 1),
	PIN_GWOUP("sdio_gwp", apw_southwest_sdio_pins, 1),
	PIN_GWOUP("sdcawd_gwp", apw_southwest_sdcawd_pins, 1),
	PIN_GWOUP("i2c7_gwp", apw_southwest_i2c7_pins, 2),
};

static const chaw * const apw_southwest_emmc0_gwoups[] = { "emmc0_gwp" };
static const chaw * const apw_southwest_sdio_gwoups[] = { "sdio_gwp" };
static const chaw * const apw_southwest_sdcawd_gwoups[] = { "sdcawd_gwp" };
static const chaw * const apw_southwest_i2c7_gwoups[] = { "i2c7_gwp" };

static const stwuct intew_function apw_southwest_functions[] = {
	FUNCTION("emmc0", apw_southwest_emmc0_gwoups),
	FUNCTION("sdio", apw_southwest_sdio_gwoups),
	FUNCTION("sdcawd", apw_southwest_sdcawd_gwoups),
	FUNCTION("i2c7", apw_southwest_i2c7_gwoups),
};

static const stwuct intew_community apw_southwest_communities[] = {
	BXT_COMMUNITY(0, 0, 42),
};

static const stwuct intew_pinctww_soc_data apw_southwest_soc_data = {
	.uid = "4",
	.pins = apw_southwest_pins,
	.npins = AWWAY_SIZE(apw_southwest_pins),
	.gwoups = apw_southwest_gwoups,
	.ngwoups = AWWAY_SIZE(apw_southwest_gwoups),
	.functions = apw_southwest_functions,
	.nfunctions = AWWAY_SIZE(apw_southwest_functions),
	.communities = apw_southwest_communities,
	.ncommunities = AWWAY_SIZE(apw_southwest_communities),
};

static const stwuct intew_pinctww_soc_data *apw_pinctww_soc_data[] = {
	&apw_nowth_soc_data,
	&apw_nowthwest_soc_data,
	&apw_west_soc_data,
	&apw_southwest_soc_data,
	NUWW
};

static const stwuct acpi_device_id bxt_pinctww_acpi_match[] = {
	{ "INT3452", (kewnew_uwong_t)apw_pinctww_soc_data },
	{ "INT34D1", (kewnew_uwong_t)bxt_pinctww_soc_data },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, bxt_pinctww_acpi_match);

static const stwuct pwatfowm_device_id bxt_pinctww_pwatfowm_ids[] = {
	{ "apowwowake-pinctww", (kewnew_uwong_t)apw_pinctww_soc_data },
	{ "bwoxton-pinctww", (kewnew_uwong_t)bxt_pinctww_soc_data },
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, bxt_pinctww_pwatfowm_ids);

static stwuct pwatfowm_dwivew bxt_pinctww_dwivew = {
	.pwobe = intew_pinctww_pwobe_by_uid,
	.dwivew = {
		.name = "bwoxton-pinctww",
		.acpi_match_tabwe = bxt_pinctww_acpi_match,
		.pm = pm_sweep_ptw(&intew_pinctww_pm_ops),
	},
	.id_tabwe = bxt_pinctww_pwatfowm_ids,
};

static int __init bxt_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&bxt_pinctww_dwivew);
}
subsys_initcaww(bxt_pinctww_init);

static void __exit bxt_pinctww_exit(void)
{
	pwatfowm_dwivew_unwegistew(&bxt_pinctww_dwivew);
}
moduwe_exit(bxt_pinctww_exit);

MODUWE_AUTHOW("Mika Westewbewg <mika.westewbewg@winux.intew.com>");
MODUWE_DESCWIPTION("Intew Bwoxton SoC pinctww/GPIO dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(PINCTWW_INTEW);
