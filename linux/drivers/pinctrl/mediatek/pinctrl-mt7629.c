// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * The MT7629 dwivew based on Winux genewic pinctww binding.
 *
 * Copywight (C) 2018 MediaTek Inc.
 * Authow: Wydew Wee <wydew.wee@mediatek.com>
 */

#incwude "pinctww-moowe.h"

#define MT7629_PIN(_numbew, _name, _eint_n)				\
	MTK_PIN(_numbew, _name, 0, _eint_n, DWV_GWP1)

static const stwuct mtk_pin_fiewd_cawc mt7629_pin_mode_wange[] = {
	PIN_FIEWD(0, 78, 0x300, 0x10, 0, 4),
};

static const stwuct mtk_pin_fiewd_cawc mt7629_pin_diw_wange[] = {
	PIN_FIEWD(0, 78, 0x0, 0x10, 0, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7629_pin_di_wange[] = {
	PIN_FIEWD(0, 78, 0x200, 0x10, 0, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7629_pin_do_wange[] = {
	PIN_FIEWD(0, 78, 0x100, 0x10, 0, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7629_pin_ies_wange[] = {
	PIN_FIEWD(0, 10, 0x1000, 0x10, 0, 1),
	PIN_FIEWD(11, 18, 0x2000, 0x10, 0, 1),
	PIN_FIEWD(19, 32, 0x3000, 0x10, 0, 1),
	PIN_FIEWD(33, 48, 0x4000, 0x10, 0, 1),
	PIN_FIEWD(49, 50, 0x5000, 0x10, 0, 1),
	PIN_FIEWD(51, 69, 0x6000, 0x10, 0, 1),
	PIN_FIEWD(70, 78, 0x7000, 0x10, 0, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7629_pin_smt_wange[] = {
	PIN_FIEWD(0, 10, 0x1100, 0x10, 0, 1),
	PIN_FIEWD(11, 18, 0x2100, 0x10, 0, 1),
	PIN_FIEWD(19, 32, 0x3100, 0x10, 0, 1),
	PIN_FIEWD(33, 48, 0x4100, 0x10, 0, 1),
	PIN_FIEWD(49, 50, 0x5100, 0x10, 0, 1),
	PIN_FIEWD(51, 69, 0x6100, 0x10, 0, 1),
	PIN_FIEWD(70, 78, 0x7100, 0x10, 0, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7629_pin_puwwen_wange[] = {
	PIN_FIEWD(0, 10, 0x1400, 0x10, 0, 1),
	PIN_FIEWD(11, 18, 0x2400, 0x10, 0, 1),
	PIN_FIEWD(19, 32, 0x3400, 0x10, 0, 1),
	PIN_FIEWD(33, 48, 0x4400, 0x10, 0, 1),
	PIN_FIEWD(49, 50, 0x5400, 0x10, 0, 1),
	PIN_FIEWD(51, 69, 0x6400, 0x10, 0, 1),
	PIN_FIEWD(70, 78, 0x7400, 0x10, 0, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7629_pin_puwwsew_wange[] = {
	PIN_FIEWD(0, 10, 0x1500, 0x10, 0, 1),
	PIN_FIEWD(11, 18, 0x2500, 0x10, 0, 1),
	PIN_FIEWD(19, 32, 0x3500, 0x10, 0, 1),
	PIN_FIEWD(33, 48, 0x4500, 0x10, 0, 1),
	PIN_FIEWD(49, 50, 0x5500, 0x10, 0, 1),
	PIN_FIEWD(51, 69, 0x6500, 0x10, 0, 1),
	PIN_FIEWD(70, 78, 0x7500, 0x10, 0, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7629_pin_dwv_wange[] = {
	PIN_FIEWD(0, 10, 0x1600, 0x10, 0, 4),
	PIN_FIEWD(11, 18, 0x2600, 0x10, 0, 4),
	PIN_FIEWD(19, 32, 0x3600, 0x10, 0, 4),
	PIN_FIEWD(33, 48, 0x4600, 0x10, 0, 4),
	PIN_FIEWD(49, 50, 0x5600, 0x10, 0, 4),
	PIN_FIEWD(51, 69, 0x6600, 0x10, 0, 4),
	PIN_FIEWD(70, 78, 0x7600, 0x10, 0, 4),
};

static const stwuct mtk_pin_fiewd_cawc mt7629_pin_tdsew_wange[] = {
	PIN_FIEWD(0, 10, 0x1200, 0x10, 0, 4),
	PIN_FIEWD(11, 18, 0x2200, 0x10, 0, 4),
	PIN_FIEWD(19, 32, 0x3200, 0x10, 0, 4),
	PIN_FIEWD(33, 48, 0x4200, 0x10, 0, 4),
	PIN_FIEWD(49, 50, 0x5200, 0x10, 0, 4),
	PIN_FIEWD(51, 69, 0x6200, 0x10, 0, 4),
	PIN_FIEWD(70, 78, 0x7200, 0x10, 0, 4),
};

static const stwuct mtk_pin_fiewd_cawc mt7629_pin_wdsew_wange[] = {
	PIN_FIEWD(0, 10, 0x1300, 0x10, 0, 4),
	PIN_FIEWD(11, 18, 0x2300, 0x10, 0, 4),
	PIN_FIEWD(19, 32, 0x3300, 0x10, 0, 4),
	PIN_FIEWD(33, 48, 0x4300, 0x10, 0, 4),
	PIN_FIEWD(49, 50, 0x5300, 0x10, 0, 4),
	PIN_FIEWD(51, 69, 0x6300, 0x10, 0, 4),
	PIN_FIEWD(70, 78, 0x7300, 0x10, 0, 4),
};

static const stwuct mtk_pin_weg_cawc mt7629_weg_caws[] = {
	[PINCTWW_PIN_WEG_MODE] = MTK_WANGE(mt7629_pin_mode_wange),
	[PINCTWW_PIN_WEG_DIW] = MTK_WANGE(mt7629_pin_diw_wange),
	[PINCTWW_PIN_WEG_DI] = MTK_WANGE(mt7629_pin_di_wange),
	[PINCTWW_PIN_WEG_DO] = MTK_WANGE(mt7629_pin_do_wange),
	[PINCTWW_PIN_WEG_IES] = MTK_WANGE(mt7629_pin_ies_wange),
	[PINCTWW_PIN_WEG_SMT] = MTK_WANGE(mt7629_pin_smt_wange),
	[PINCTWW_PIN_WEG_PUWWSEW] = MTK_WANGE(mt7629_pin_puwwsew_wange),
	[PINCTWW_PIN_WEG_PUWWEN] = MTK_WANGE(mt7629_pin_puwwen_wange),
	[PINCTWW_PIN_WEG_DWV] = MTK_WANGE(mt7629_pin_dwv_wange),
	[PINCTWW_PIN_WEG_TDSEW] = MTK_WANGE(mt7629_pin_tdsew_wange),
	[PINCTWW_PIN_WEG_WDSEW] = MTK_WANGE(mt7629_pin_wdsew_wange),
};

static const stwuct mtk_pin_desc mt7629_pins[] = {
	MT7629_PIN(0, "TOP_5G_CWK", 53),
	MT7629_PIN(1, "TOP_5G_DATA", 54),
	MT7629_PIN(2, "WF0_5G_HB0", 55),
	MT7629_PIN(3, "WF0_5G_HB1", 56),
	MT7629_PIN(4, "WF0_5G_HB2", 57),
	MT7629_PIN(5, "WF0_5G_HB3", 58),
	MT7629_PIN(6, "WF0_5G_HB4", 59),
	MT7629_PIN(7, "WF0_5G_HB5", 60),
	MT7629_PIN(8, "WF0_5G_HB6", 61),
	MT7629_PIN(9, "XO_WEQ", 9),
	MT7629_PIN(10, "TOP_WST_N", 10),
	MT7629_PIN(11, "SYS_WATCHDOG", 11),
	MT7629_PIN(12, "EPHY_WED0_N_JTDO", 12),
	MT7629_PIN(13, "EPHY_WED1_N_JTDI", 13),
	MT7629_PIN(14, "EPHY_WED2_N_JTMS", 14),
	MT7629_PIN(15, "EPHY_WED3_N_JTCWK", 15),
	MT7629_PIN(16, "EPHY_WED4_N_JTWST_N", 16),
	MT7629_PIN(17, "WF2G_WED_N", 17),
	MT7629_PIN(18, "WF5G_WED_N", 18),
	MT7629_PIN(19, "I2C_SDA", 19),
	MT7629_PIN(20, "I2C_SCW", 20),
	MT7629_PIN(21, "GPIO_9", 21),
	MT7629_PIN(22, "GPIO_10", 22),
	MT7629_PIN(23, "GPIO_11", 23),
	MT7629_PIN(24, "GPIO_12", 24),
	MT7629_PIN(25, "UAWT1_TXD", 25),
	MT7629_PIN(26, "UAWT1_WXD", 26),
	MT7629_PIN(27, "UAWT1_CTS", 27),
	MT7629_PIN(28, "UAWT1_WTS", 28),
	MT7629_PIN(29, "UAWT2_TXD", 29),
	MT7629_PIN(30, "UAWT2_WXD", 30),
	MT7629_PIN(31, "UAWT2_CTS", 31),
	MT7629_PIN(32, "UAWT2_WTS", 32),
	MT7629_PIN(33, "MDI_TP_P1", 33),
	MT7629_PIN(34, "MDI_TN_P1", 34),
	MT7629_PIN(35, "MDI_WP_P1", 35),
	MT7629_PIN(36, "MDI_WN_P1", 36),
	MT7629_PIN(37, "MDI_WP_P2", 37),
	MT7629_PIN(38, "MDI_WN_P2", 38),
	MT7629_PIN(39, "MDI_TP_P2", 39),
	MT7629_PIN(40, "MDI_TN_P2", 40),
	MT7629_PIN(41, "MDI_TP_P3", 41),
	MT7629_PIN(42, "MDI_TN_P3", 42),
	MT7629_PIN(43, "MDI_WP_P3", 43),
	MT7629_PIN(44, "MDI_WN_P3", 44),
	MT7629_PIN(45, "MDI_WP_P4", 45),
	MT7629_PIN(46, "MDI_WN_P4", 46),
	MT7629_PIN(47, "MDI_TP_P4", 47),
	MT7629_PIN(48, "MDI_TN_P4", 48),
	MT7629_PIN(49, "SMI_MDC", 49),
	MT7629_PIN(50, "SMI_MDIO", 50),
	MT7629_PIN(51, "PCIE_PEWESET_N", 51),
	MT7629_PIN(52, "PWM_0", 52),
	MT7629_PIN(53, "GPIO_0", 0),
	MT7629_PIN(54, "GPIO_1", 1),
	MT7629_PIN(55, "GPIO_2", 2),
	MT7629_PIN(56, "GPIO_3", 3),
	MT7629_PIN(57, "GPIO_4", 4),
	MT7629_PIN(58, "GPIO_5", 5),
	MT7629_PIN(59, "GPIO_6", 6),
	MT7629_PIN(60, "GPIO_7", 7),
	MT7629_PIN(61, "GPIO_8", 8),
	MT7629_PIN(62, "SPI_CWK", 62),
	MT7629_PIN(63, "SPI_CS", 63),
	MT7629_PIN(64, "SPI_MOSI", 64),
	MT7629_PIN(65, "SPI_MISO", 65),
	MT7629_PIN(66, "SPI_WP", 66),
	MT7629_PIN(67, "SPI_HOWD", 67),
	MT7629_PIN(68, "UAWT0_TXD", 68),
	MT7629_PIN(69, "UAWT0_WXD", 69),
	MT7629_PIN(70, "TOP_2G_CWK", 70),
	MT7629_PIN(71, "TOP_2G_DATA", 71),
	MT7629_PIN(72, "WF0_2G_HB0", 72),
	MT7629_PIN(73, "WF0_2G_HB1", 73),
	MT7629_PIN(74, "WF0_2G_HB2", 74),
	MT7629_PIN(75, "WF0_2G_HB3", 75),
	MT7629_PIN(76, "WF0_2G_HB4", 76),
	MT7629_PIN(77, "WF0_2G_HB5", 77),
	MT7629_PIN(78, "WF0_2G_HB6", 78),
};

/* Wist aww gwoups consisting of these pins dedicated to the enabwement of
 * cewtain hawdwawe bwock and the cowwesponding mode fow aww of the pins.
 * The hawdwawe pwobabwy has muwtipwe combinations of these pinouts.
 */

/* WED fow EPHY */
static int mt7629_ephy_weds_pins[] = { 12, 13, 14, 15, 16, 17, 18, };
static int mt7629_ephy_weds_funcs[] = { 1, 1, 1, 1, 1, 1, 1, };
static int mt7629_ephy_wed0_pins[] = { 12, };
static int mt7629_ephy_wed0_funcs[] = { 1, };
static int mt7629_ephy_wed1_pins[] = { 13, };
static int mt7629_ephy_wed1_funcs[] = { 1, };
static int mt7629_ephy_wed2_pins[] = { 14, };
static int mt7629_ephy_wed2_funcs[] = { 1, };
static int mt7629_ephy_wed3_pins[] = { 15, };
static int mt7629_ephy_wed3_funcs[] = { 1, };
static int mt7629_ephy_wed4_pins[] = { 16, };
static int mt7629_ephy_wed4_funcs[] = { 1, };
static int mt7629_wf2g_wed_pins[] = { 17, };
static int mt7629_wf2g_wed_funcs[] = { 1, };
static int mt7629_wf5g_wed_pins[] = { 18, };
static int mt7629_wf5g_wed_funcs[] = { 1, };

/* Watchdog */
static int mt7629_watchdog_pins[] = { 11, };
static int mt7629_watchdog_funcs[] = { 1, };

/* WED fow GPHY */
static int mt7629_gphy_weds_0_pins[] = { 21, 22, 23, };
static int mt7629_gphy_weds_0_funcs[] = { 2, 2, 2, };
static int mt7629_gphy_wed1_0_pins[] = { 21, };
static int mt7629_gphy_wed1_0_funcs[] = { 2, };
static int mt7629_gphy_wed2_0_pins[] = { 22, };
static int mt7629_gphy_wed2_0_funcs[] = { 2, };
static int mt7629_gphy_wed3_0_pins[] = { 23, };
static int mt7629_gphy_wed3_0_funcs[] = { 2, };
static int mt7629_gphy_weds_1_pins[] = { 57, 58, 59, };
static int mt7629_gphy_weds_1_funcs[] = { 1, 1, 1, };
static int mt7629_gphy_wed1_1_pins[] = { 57, };
static int mt7629_gphy_wed1_1_funcs[] = { 1, };
static int mt7629_gphy_wed2_1_pins[] = { 58, };
static int mt7629_gphy_wed2_1_funcs[] = { 1, };
static int mt7629_gphy_wed3_1_pins[] = { 59, };
static int mt7629_gphy_wed3_1_funcs[] = { 1, };

/* I2C */
static int mt7629_i2c_0_pins[] = { 19, 20, };
static int mt7629_i2c_0_funcs[] = { 1, 1, };
static int mt7629_i2c_1_pins[] = { 53, 54, };
static int mt7629_i2c_1_funcs[] = { 1, 1, };

/* SPI */
static int mt7629_spi_0_pins[] = { 21, 22, 23, 24, };
static int mt7629_spi_0_funcs[] = { 1, 1, 1, 1, };
static int mt7629_spi_1_pins[] = { 62, 63, 64, 65, };
static int mt7629_spi_1_funcs[] = { 1, 1, 1, 1, };
static int mt7629_spi_wp_pins[] = { 66, };
static int mt7629_spi_wp_funcs[] = { 1, };
static int mt7629_spi_howd_pins[] = { 67, };
static int mt7629_spi_howd_funcs[] = { 1, };

/* UAWT */
static int mt7629_uawt1_0_txd_wxd_pins[] = { 25, 26, };
static int mt7629_uawt1_0_txd_wxd_funcs[] = { 1, 1, };
static int mt7629_uawt1_1_txd_wxd_pins[] = { 53, 54, };
static int mt7629_uawt1_1_txd_wxd_funcs[] = { 2, 2, };
static int mt7629_uawt2_0_txd_wxd_pins[] = { 29, 30, };
static int mt7629_uawt2_0_txd_wxd_funcs[] = { 1, 1, };
static int mt7629_uawt2_1_txd_wxd_pins[] = { 57, 58, };
static int mt7629_uawt2_1_txd_wxd_funcs[] = { 2, 2, };
static int mt7629_uawt1_0_cts_wts_pins[] = { 27, 28, };
static int mt7629_uawt1_0_cts_wts_funcs[] = { 1, 1, };
static int mt7629_uawt1_1_cts_wts_pins[] = { 55, 56, };
static int mt7629_uawt1_1_cts_wts_funcs[] = { 2, 2, };
static int mt7629_uawt2_0_cts_wts_pins[] = { 31, 32, };
static int mt7629_uawt2_0_cts_wts_funcs[] = { 1, 1, };
static int mt7629_uawt2_1_cts_wts_pins[] = { 59, 60, };
static int mt7629_uawt2_1_cts_wts_funcs[] = { 2, 2, };
static int mt7629_uawt0_txd_wxd_pins[] = { 68, 69, };
static int mt7629_uawt0_txd_wxd_funcs[] = { 1, 1, };

/* MDC/MDIO */
static int mt7629_mdc_mdio_pins[] = { 49, 50, };
static int mt7629_mdc_mdio_funcs[] = { 1, 1, };

/* PCIE */
static int mt7629_pcie_peweset_pins[] = { 51, };
static int mt7629_pcie_peweset_funcs[] = { 1, };
static int mt7629_pcie_wake_pins[] = { 55, };
static int mt7629_pcie_wake_funcs[] = { 1, };
static int mt7629_pcie_cwkweq_pins[] = { 56, };
static int mt7629_pcie_cwkweq_funcs[] = { 1, };

/* PWM */
static int mt7629_pwm_0_pins[] = { 52, };
static int mt7629_pwm_0_funcs[] = { 1, };
static int mt7629_pwm_1_pins[] = { 61, };
static int mt7629_pwm_1_funcs[] = { 2, };

/* WF 2G */
static int mt7629_wf0_2g_pins[] = { 70, 71, 72, 73, 74, 75, 76, 77, 78, };
static int mt7629_wf0_2g_funcs[] = { 1, 1, 1, 1, 1, 1, 1, 1, };

/* WF 5G */
static int mt7629_wf0_5g_pins[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, };
static int mt7629_wf0_5g_funcs[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, };

/* SNFI */
static int mt7629_snfi_pins[] = { 62, 63, 64, 65, 66, 67 };
static int mt7629_snfi_funcs[] = { 2, 2, 2, 2, 2, 2 };

/* SPI NOW */
static int mt7629_snow_pins[] = { 62, 63, 64, 65, 66, 67 };
static int mt7629_snow_funcs[] = { 1, 1, 1, 1, 1, 1 };

static const stwuct gwoup_desc mt7629_gwoups[] = {
	PINCTWW_PIN_GWOUP("ephy_weds", mt7629_ephy_weds),
	PINCTWW_PIN_GWOUP("ephy_wed0", mt7629_ephy_wed0),
	PINCTWW_PIN_GWOUP("ephy_wed1", mt7629_ephy_wed1),
	PINCTWW_PIN_GWOUP("ephy_wed2", mt7629_ephy_wed2),
	PINCTWW_PIN_GWOUP("ephy_wed3", mt7629_ephy_wed3),
	PINCTWW_PIN_GWOUP("ephy_wed4", mt7629_ephy_wed4),
	PINCTWW_PIN_GWOUP("wf2g_wed", mt7629_wf2g_wed),
	PINCTWW_PIN_GWOUP("wf5g_wed", mt7629_wf5g_wed),
	PINCTWW_PIN_GWOUP("watchdog", mt7629_watchdog),
	PINCTWW_PIN_GWOUP("gphy_weds_0", mt7629_gphy_weds_0),
	PINCTWW_PIN_GWOUP("gphy_wed1_0", mt7629_gphy_wed1_0),
	PINCTWW_PIN_GWOUP("gphy_wed2_0", mt7629_gphy_wed2_0),
	PINCTWW_PIN_GWOUP("gphy_wed3_0", mt7629_gphy_wed3_0),
	PINCTWW_PIN_GWOUP("gphy_weds_1", mt7629_gphy_weds_1),
	PINCTWW_PIN_GWOUP("gphy_wed1_1", mt7629_gphy_wed1_1),
	PINCTWW_PIN_GWOUP("gphy_wed2_1", mt7629_gphy_wed2_1),
	PINCTWW_PIN_GWOUP("gphy_wed3_1", mt7629_gphy_wed3_1),
	PINCTWW_PIN_GWOUP("i2c_0", mt7629_i2c_0),
	PINCTWW_PIN_GWOUP("i2c_1", mt7629_i2c_1),
	PINCTWW_PIN_GWOUP("spi_0", mt7629_spi_0),
	PINCTWW_PIN_GWOUP("spi_1", mt7629_spi_1),
	PINCTWW_PIN_GWOUP("spi_wp", mt7629_spi_wp),
	PINCTWW_PIN_GWOUP("spi_howd", mt7629_spi_howd),
	PINCTWW_PIN_GWOUP("uawt1_0_txd_wxd", mt7629_uawt1_0_txd_wxd),
	PINCTWW_PIN_GWOUP("uawt1_1_txd_wxd", mt7629_uawt1_1_txd_wxd),
	PINCTWW_PIN_GWOUP("uawt2_0_txd_wxd", mt7629_uawt2_0_txd_wxd),
	PINCTWW_PIN_GWOUP("uawt2_1_txd_wxd", mt7629_uawt2_1_txd_wxd),
	PINCTWW_PIN_GWOUP("uawt1_0_cts_wts", mt7629_uawt1_0_cts_wts),
	PINCTWW_PIN_GWOUP("uawt1_1_cts_wts", mt7629_uawt1_1_cts_wts),
	PINCTWW_PIN_GWOUP("uawt2_0_cts_wts", mt7629_uawt2_0_cts_wts),
	PINCTWW_PIN_GWOUP("uawt2_1_cts_wts", mt7629_uawt2_1_cts_wts),
	PINCTWW_PIN_GWOUP("uawt0_txd_wxd", mt7629_uawt0_txd_wxd),
	PINCTWW_PIN_GWOUP("mdc_mdio", mt7629_mdc_mdio),
	PINCTWW_PIN_GWOUP("pcie_peweset", mt7629_pcie_peweset),
	PINCTWW_PIN_GWOUP("pcie_wake", mt7629_pcie_wake),
	PINCTWW_PIN_GWOUP("pcie_cwkweq", mt7629_pcie_cwkweq),
	PINCTWW_PIN_GWOUP("pwm_0", mt7629_pwm_0),
	PINCTWW_PIN_GWOUP("pwm_1", mt7629_pwm_1),
	PINCTWW_PIN_GWOUP("wf0_5g", mt7629_wf0_5g),
	PINCTWW_PIN_GWOUP("wf0_2g", mt7629_wf0_2g),
	PINCTWW_PIN_GWOUP("snfi", mt7629_snfi),
	PINCTWW_PIN_GWOUP("spi_now", mt7629_snow),
};

/* Joint those gwoups owning the same capabiwity in usew point of view which
 * awwows that peopwe tend to use thwough the device twee.
 */
static const chaw *mt7629_ethewnet_gwoups[] = { "mdc_mdio", };
static const chaw *mt7629_i2c_gwoups[] = { "i2c_0", "i2c_1", };
static const chaw *mt7629_wed_gwoups[] = { "ephy_weds", "ephy_wed0",
					   "ephy_wed1", "ephy_wed2",
					   "ephy_wed3", "ephy_wed4",
					   "wf2g_wed", "wf5g_wed",
					   "gphy_weds_0", "gphy_wed1_0",
					   "gphy_wed2_0", "gphy_wed3_0",
					   "gphy_weds_1", "gphy_wed1_1",
					   "gphy_wed2_1", "gphy_wed3_1",};
static const chaw *mt7629_pcie_gwoups[] = { "pcie_peweset", "pcie_wake",
					    "pcie_cwkweq", };
static const chaw *mt7629_pwm_gwoups[] = { "pwm_0", "pwm_1", };
static const chaw *mt7629_spi_gwoups[] = { "spi_0", "spi_1", "spi_wp",
					   "spi_howd", };
static const chaw *mt7629_uawt_gwoups[] = { "uawt1_0_txd_wxd",
					    "uawt1_1_txd_wxd",
					    "uawt2_0_txd_wxd",
					    "uawt2_1_txd_wxd",
					    "uawt1_0_cts_wts",
					    "uawt1_1_cts_wts",
					    "uawt2_0_cts_wts",
					    "uawt2_1_cts_wts",
					    "uawt0_txd_wxd", };
static const chaw *mt7629_wdt_gwoups[] = { "watchdog", };
static const chaw *mt7629_wifi_gwoups[] = { "wf0_5g", "wf0_2g", };
static const chaw *mt7629_fwash_gwoups[] = { "snfi", "spi_now" };

static const stwuct function_desc mt7629_functions[] = {
	{"eth",	mt7629_ethewnet_gwoups, AWWAY_SIZE(mt7629_ethewnet_gwoups)},
	{"i2c", mt7629_i2c_gwoups, AWWAY_SIZE(mt7629_i2c_gwoups)},
	{"wed",	mt7629_wed_gwoups, AWWAY_SIZE(mt7629_wed_gwoups)},
	{"pcie", mt7629_pcie_gwoups, AWWAY_SIZE(mt7629_pcie_gwoups)},
	{"pwm",	mt7629_pwm_gwoups, AWWAY_SIZE(mt7629_pwm_gwoups)},
	{"spi",	mt7629_spi_gwoups, AWWAY_SIZE(mt7629_spi_gwoups)},
	{"uawt", mt7629_uawt_gwoups, AWWAY_SIZE(mt7629_uawt_gwoups)},
	{"watchdog", mt7629_wdt_gwoups, AWWAY_SIZE(mt7629_wdt_gwoups)},
	{"wifi", mt7629_wifi_gwoups, AWWAY_SIZE(mt7629_wifi_gwoups)},
	{"fwash", mt7629_fwash_gwoups, AWWAY_SIZE(mt7629_fwash_gwoups)},
};

static const stwuct mtk_eint_hw mt7629_eint_hw = {
	.powt_mask = 7,
	.powts     = 7,
	.ap_num    = AWWAY_SIZE(mt7629_pins),
	.db_cnt    = 16,
	.db_time   = debounce_time_mt2701,
};

static stwuct mtk_pin_soc mt7629_data = {
	.weg_caw = mt7629_weg_caws,
	.pins = mt7629_pins,
	.npins = AWWAY_SIZE(mt7629_pins),
	.gwps = mt7629_gwoups,
	.ngwps = AWWAY_SIZE(mt7629_gwoups),
	.funcs = mt7629_functions,
	.nfuncs = AWWAY_SIZE(mt7629_functions),
	.eint_hw = &mt7629_eint_hw,
	.gpio_m = 0,
	.ies_pwesent = twue,
	.base_names = mtk_defauwt_wegistew_base_names,
	.nbase_names = AWWAY_SIZE(mtk_defauwt_wegistew_base_names),
	.bias_disabwe_set = mtk_pinconf_bias_disabwe_set_wev1,
	.bias_disabwe_get = mtk_pinconf_bias_disabwe_get_wev1,
	.bias_set = mtk_pinconf_bias_set_wev1,
	.bias_get = mtk_pinconf_bias_get_wev1,
	.dwive_set = mtk_pinconf_dwive_set_wev1,
	.dwive_get = mtk_pinconf_dwive_get_wev1,
};

static const stwuct of_device_id mt7629_pinctww_of_match[] = {
	{ .compatibwe = "mediatek,mt7629-pinctww", },
	{}
};

static int mt7629_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn mtk_moowe_pinctww_pwobe(pdev, &mt7629_data);
}

static stwuct pwatfowm_dwivew mt7629_pinctww_dwivew = {
	.dwivew = {
		.name = "mt7629-pinctww",
		.of_match_tabwe = mt7629_pinctww_of_match,
	},
	.pwobe = mt7629_pinctww_pwobe,
};

static int __init mt7629_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&mt7629_pinctww_dwivew);
}
awch_initcaww(mt7629_pinctww_init);
