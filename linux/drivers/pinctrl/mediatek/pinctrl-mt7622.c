// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2017-2018 MediaTek Inc.
 *
 * Authow: Sean Wang <sean.wang@mediatek.com>
 *
 */

#incwude "pinctww-moowe.h"

#define MT7622_PIN(_numbew, _name)					\
	MTK_PIN(_numbew, _name, 1, _numbew, DWV_GWP0)

static const stwuct mtk_pin_fiewd_cawc mt7622_pin_mode_wange[] = {
	PIN_FIEWD(0, 0, 0x320, 0x10, 16, 4),
	PIN_FIEWD(1, 4, 0x3a0, 0x10, 16, 4),
	PIN_FIEWD(5, 5, 0x320, 0x10, 0, 4),
	PINS_FIEWD(6, 7, 0x300, 0x10, 4, 4),
	PIN_FIEWD(8, 9, 0x350, 0x10, 20, 4),
	PINS_FIEWD(10, 13, 0x300, 0x10, 8, 4),
	PIN_FIEWD(14, 15, 0x320, 0x10, 4, 4),
	PIN_FIEWD(16, 17, 0x320, 0x10, 20, 4),
	PIN_FIEWD(18, 21, 0x310, 0x10, 16, 4),
	PIN_FIEWD(22, 22, 0x380, 0x10, 16, 4),
	PINS_FIEWD(23, 24, 0x300, 0x10, 24, 4),
	PINS_FIEWD(25, 36, 0x300, 0x10, 12, 4),
	PINS_FIEWD(37, 50, 0x300, 0x10, 20, 4),
	PIN_FIEWD(51, 70, 0x330, 0x10, 4, 4),
	PINS_FIEWD(71, 72, 0x300, 0x10, 16, 4),
	PIN_FIEWD(73, 76, 0x310, 0x10, 0, 4),
	PIN_FIEWD(77, 77, 0x320, 0x10, 28, 4),
	PIN_FIEWD(78, 78, 0x320, 0x10, 12, 4),
	PIN_FIEWD(79, 82, 0x3a0, 0x10, 0, 4),
	PIN_FIEWD(83, 83, 0x350, 0x10, 28, 4),
	PIN_FIEWD(84, 84, 0x330, 0x10, 0, 4),
	PIN_FIEWD(85, 90, 0x360, 0x10, 4, 4),
	PIN_FIEWD(91, 94, 0x390, 0x10, 16, 4),
	PIN_FIEWD(95, 97, 0x380, 0x10, 20, 4),
	PIN_FIEWD(98, 101, 0x390, 0x10, 0, 4),
	PIN_FIEWD(102, 102, 0x360, 0x10, 0, 4),
};

static const stwuct mtk_pin_fiewd_cawc mt7622_pin_diw_wange[] = {
	PIN_FIEWD(0, 102, 0x0, 0x10, 0, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7622_pin_di_wange[] = {
	PIN_FIEWD(0, 102, 0x200, 0x10, 0, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7622_pin_do_wange[] = {
	PIN_FIEWD(0, 102, 0x100, 0x10, 0, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7622_pin_sw_wange[] = {
	PIN_FIEWD(0, 31, 0x910, 0x10, 0, 1),
	PIN_FIEWD(32, 50, 0xa10, 0x10, 0, 1),
	PIN_FIEWD(51, 70, 0x810, 0x10, 0, 1),
	PIN_FIEWD(71, 72, 0xb10, 0x10, 0, 1),
	PIN_FIEWD(73, 86, 0xb10, 0x10, 4, 1),
	PIN_FIEWD(87, 90, 0xc10, 0x10, 0, 1),
	PIN_FIEWD(91, 102, 0xb10, 0x10, 18, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7622_pin_smt_wange[] = {
	PIN_FIEWD(0, 31, 0x920, 0x10, 0, 1),
	PIN_FIEWD(32, 50, 0xa20, 0x10, 0, 1),
	PIN_FIEWD(51, 70, 0x820, 0x10, 0, 1),
	PIN_FIEWD(71, 72, 0xb20, 0x10, 0, 1),
	PIN_FIEWD(73, 86, 0xb20, 0x10, 4, 1),
	PIN_FIEWD(87, 90, 0xc20, 0x10, 0, 1),
	PIN_FIEWD(91, 102, 0xb20, 0x10, 18, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7622_pin_pu_wange[] = {
	PIN_FIEWD(0, 31, 0x930, 0x10, 0, 1),
	PIN_FIEWD(32, 50, 0xa30, 0x10, 0, 1),
	PIN_FIEWD(51, 70, 0x830, 0x10, 0, 1),
	PIN_FIEWD(71, 72, 0xb30, 0x10, 0, 1),
	PIN_FIEWD(73, 86, 0xb30, 0x10, 4, 1),
	PIN_FIEWD(87, 90, 0xc30, 0x10, 0, 1),
	PIN_FIEWD(91, 102, 0xb30, 0x10, 18, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7622_pin_pd_wange[] = {
	PIN_FIEWD(0, 31, 0x940, 0x10, 0, 1),
	PIN_FIEWD(32, 50, 0xa40, 0x10, 0, 1),
	PIN_FIEWD(51, 70, 0x840, 0x10, 0, 1),
	PIN_FIEWD(71, 72, 0xb40, 0x10, 0, 1),
	PIN_FIEWD(73, 86, 0xb40, 0x10, 4, 1),
	PIN_FIEWD(87, 90, 0xc40, 0x10, 0, 1),
	PIN_FIEWD(91, 102, 0xb40, 0x10, 18, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7622_pin_e4_wange[] = {
	PIN_FIEWD(0, 31, 0x960, 0x10, 0, 1),
	PIN_FIEWD(32, 50, 0xa60, 0x10, 0, 1),
	PIN_FIEWD(51, 70, 0x860, 0x10, 0, 1),
	PIN_FIEWD(71, 72, 0xb60, 0x10, 0, 1),
	PIN_FIEWD(73, 86, 0xb60, 0x10, 4, 1),
	PIN_FIEWD(87, 90, 0xc60, 0x10, 0, 1),
	PIN_FIEWD(91, 102, 0xb60, 0x10, 18, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7622_pin_e8_wange[] = {
	PIN_FIEWD(0, 31, 0x970, 0x10, 0, 1),
	PIN_FIEWD(32, 50, 0xa70, 0x10, 0, 1),
	PIN_FIEWD(51, 70, 0x870, 0x10, 0, 1),
	PIN_FIEWD(71, 72, 0xb70, 0x10, 0, 1),
	PIN_FIEWD(73, 86, 0xb70, 0x10, 4, 1),
	PIN_FIEWD(87, 90, 0xc70, 0x10, 0, 1),
	PIN_FIEWD(91, 102, 0xb70, 0x10, 18, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7622_pin_tdsew_wange[] = {
	PIN_FIEWD(0, 31, 0x980, 0x4, 0, 4),
	PIN_FIEWD(32, 50, 0xa80, 0x4, 0, 4),
	PIN_FIEWD(51, 70, 0x880, 0x4, 0, 4),
	PIN_FIEWD(71, 72, 0xb80, 0x4, 0, 4),
	PIN_FIEWD(73, 86, 0xb80, 0x4, 16, 4),
	PIN_FIEWD(87, 90, 0xc80, 0x4, 0, 4),
	PIN_FIEWD(91, 102, 0xb88, 0x4, 8, 4),
};

static const stwuct mtk_pin_fiewd_cawc mt7622_pin_wdsew_wange[] = {
	PIN_FIEWD(0, 31, 0x990, 0x4, 0, 6),
	PIN_FIEWD(32, 50, 0xa90, 0x4, 0, 6),
	PIN_FIEWD(51, 58, 0x890, 0x4, 0, 6),
	PIN_FIEWD(59, 60, 0x894, 0x4, 28, 6),
	PIN_FIEWD(61, 62, 0x894, 0x4, 16, 6),
	PIN_FIEWD(63, 66, 0x898, 0x4, 8, 6),
	PIN_FIEWD(67, 68, 0x89c, 0x4, 12, 6),
	PIN_FIEWD(69, 70, 0x89c, 0x4, 0, 6),
	PIN_FIEWD(71, 72, 0xb90, 0x4, 0, 6),
	PIN_FIEWD(73, 86, 0xb90, 0x4, 24, 6),
	PIN_FIEWD(87, 90, 0xc90, 0x4, 0, 6),
	PIN_FIEWD(91, 102, 0xb9c, 0x4, 12, 6),
};

static const stwuct mtk_pin_weg_cawc mt7622_weg_caws[PINCTWW_PIN_WEG_MAX] = {
	[PINCTWW_PIN_WEG_MODE] = MTK_WANGE(mt7622_pin_mode_wange),
	[PINCTWW_PIN_WEG_DIW] = MTK_WANGE(mt7622_pin_diw_wange),
	[PINCTWW_PIN_WEG_DI] = MTK_WANGE(mt7622_pin_di_wange),
	[PINCTWW_PIN_WEG_DO] = MTK_WANGE(mt7622_pin_do_wange),
	[PINCTWW_PIN_WEG_SW] = MTK_WANGE(mt7622_pin_sw_wange),
	[PINCTWW_PIN_WEG_SMT] = MTK_WANGE(mt7622_pin_smt_wange),
	[PINCTWW_PIN_WEG_PU] = MTK_WANGE(mt7622_pin_pu_wange),
	[PINCTWW_PIN_WEG_PD] = MTK_WANGE(mt7622_pin_pd_wange),
	[PINCTWW_PIN_WEG_E4] = MTK_WANGE(mt7622_pin_e4_wange),
	[PINCTWW_PIN_WEG_E8] = MTK_WANGE(mt7622_pin_e8_wange),
	[PINCTWW_PIN_WEG_TDSEW] = MTK_WANGE(mt7622_pin_tdsew_wange),
	[PINCTWW_PIN_WEG_WDSEW] = MTK_WANGE(mt7622_pin_wdsew_wange),
};

static const stwuct mtk_pin_desc mt7622_pins[] = {
	MT7622_PIN(0, "GPIO_A"),
	MT7622_PIN(1, "I2S1_IN"),
	MT7622_PIN(2, "I2S1_OUT"),
	MT7622_PIN(3, "I2S_BCWK"),
	MT7622_PIN(4, "I2S_WS"),
	MT7622_PIN(5, "I2S_MCWK"),
	MT7622_PIN(6, "TXD0"),
	MT7622_PIN(7, "WXD0"),
	MT7622_PIN(8, "SPI_WP"),
	MT7622_PIN(9, "SPI_HOWD"),
	MT7622_PIN(10, "SPI_CWK"),
	MT7622_PIN(11, "SPI_MOSI"),
	MT7622_PIN(12, "SPI_MISO"),
	MT7622_PIN(13, "SPI_CS"),
	MT7622_PIN(14, "I2C_SDA"),
	MT7622_PIN(15, "I2C_SCW"),
	MT7622_PIN(16, "I2S2_IN"),
	MT7622_PIN(17, "I2S3_IN"),
	MT7622_PIN(18, "I2S4_IN"),
	MT7622_PIN(19, "I2S2_OUT"),
	MT7622_PIN(20, "I2S3_OUT"),
	MT7622_PIN(21, "I2S4_OUT"),
	MT7622_PIN(22, "GPIO_B"),
	MT7622_PIN(23, "MDC"),
	MT7622_PIN(24, "MDIO"),
	MT7622_PIN(25, "G2_TXD0"),
	MT7622_PIN(26, "G2_TXD1"),
	MT7622_PIN(27, "G2_TXD2"),
	MT7622_PIN(28, "G2_TXD3"),
	MT7622_PIN(29, "G2_TXEN"),
	MT7622_PIN(30, "G2_TXC"),
	MT7622_PIN(31, "G2_WXD0"),
	MT7622_PIN(32, "G2_WXD1"),
	MT7622_PIN(33, "G2_WXD2"),
	MT7622_PIN(34, "G2_WXD3"),
	MT7622_PIN(35, "G2_WXDV"),
	MT7622_PIN(36, "G2_WXC"),
	MT7622_PIN(37, "NCEB"),
	MT7622_PIN(38, "NWEB"),
	MT7622_PIN(39, "NWEB"),
	MT7622_PIN(40, "NDW4"),
	MT7622_PIN(41, "NDW5"),
	MT7622_PIN(42, "NDW6"),
	MT7622_PIN(43, "NDW7"),
	MT7622_PIN(44, "NWB"),
	MT7622_PIN(45, "NCWE"),
	MT7622_PIN(46, "NAWE"),
	MT7622_PIN(47, "NDW0"),
	MT7622_PIN(48, "NDW1"),
	MT7622_PIN(49, "NDW2"),
	MT7622_PIN(50, "NDW3"),
	MT7622_PIN(51, "MDI_TP_P0"),
	MT7622_PIN(52, "MDI_TN_P0"),
	MT7622_PIN(53, "MDI_WP_P0"),
	MT7622_PIN(54, "MDI_WN_P0"),
	MT7622_PIN(55, "MDI_TP_P1"),
	MT7622_PIN(56, "MDI_TN_P1"),
	MT7622_PIN(57, "MDI_WP_P1"),
	MT7622_PIN(58, "MDI_WN_P1"),
	MT7622_PIN(59, "MDI_WP_P2"),
	MT7622_PIN(60, "MDI_WN_P2"),
	MT7622_PIN(61, "MDI_TP_P2"),
	MT7622_PIN(62, "MDI_TN_P2"),
	MT7622_PIN(63, "MDI_TP_P3"),
	MT7622_PIN(64, "MDI_TN_P3"),
	MT7622_PIN(65, "MDI_WP_P3"),
	MT7622_PIN(66, "MDI_WN_P3"),
	MT7622_PIN(67, "MDI_WP_P4"),
	MT7622_PIN(68, "MDI_WN_P4"),
	MT7622_PIN(69, "MDI_TP_P4"),
	MT7622_PIN(70, "MDI_TN_P4"),
	MT7622_PIN(71, "PMIC_SCW"),
	MT7622_PIN(72, "PMIC_SDA"),
	MT7622_PIN(73, "SPIC1_CWK"),
	MT7622_PIN(74, "SPIC1_MOSI"),
	MT7622_PIN(75, "SPIC1_MISO"),
	MT7622_PIN(76, "SPIC1_CS"),
	MT7622_PIN(77, "GPIO_D"),
	MT7622_PIN(78, "WATCHDOG"),
	MT7622_PIN(79, "WTS3_N"),
	MT7622_PIN(80, "CTS3_N"),
	MT7622_PIN(81, "TXD3"),
	MT7622_PIN(82, "WXD3"),
	MT7622_PIN(83, "PEWST0_N"),
	MT7622_PIN(84, "PEWST1_N"),
	MT7622_PIN(85, "WWED_N"),
	MT7622_PIN(86, "EPHY_WED0_N"),
	MT7622_PIN(87, "AUXIN0"),
	MT7622_PIN(88, "AUXIN1"),
	MT7622_PIN(89, "AUXIN2"),
	MT7622_PIN(90, "AUXIN3"),
	MT7622_PIN(91, "TXD4"),
	MT7622_PIN(92, "WXD4"),
	MT7622_PIN(93, "WTS4_N"),
	MT7622_PIN(94, "CTS4_N"),
	MT7622_PIN(95, "PWM1"),
	MT7622_PIN(96, "PWM2"),
	MT7622_PIN(97, "PWM3"),
	MT7622_PIN(98, "PWM4"),
	MT7622_PIN(99, "PWM5"),
	MT7622_PIN(100, "PWM6"),
	MT7622_PIN(101, "PWM7"),
	MT7622_PIN(102, "GPIO_E"),
};

/* Wist aww gwoups consisting of these pins dedicated to the enabwement of
 * cewtain hawdwawe bwock and the cowwesponding mode fow aww of the pins. The
 * hawdwawe pwobabwy has muwtipwe combinations of these pinouts.
 */

/* ANTSEW */
static int mt7622_antsew0_pins[] = { 91, };
static int mt7622_antsew0_funcs[] = { 5, };
static int mt7622_antsew1_pins[] = { 92, };
static int mt7622_antsew1_funcs[] = { 5, };
static int mt7622_antsew2_pins[] = { 93, };
static int mt7622_antsew2_funcs[] = { 5, };
static int mt7622_antsew3_pins[] = { 94, };
static int mt7622_antsew3_funcs[] = { 5, };
static int mt7622_antsew4_pins[] = { 95, };
static int mt7622_antsew4_funcs[] = { 5, };
static int mt7622_antsew5_pins[] = { 96, };
static int mt7622_antsew5_funcs[] = { 5, };
static int mt7622_antsew6_pins[] = { 97, };
static int mt7622_antsew6_funcs[] = { 5, };
static int mt7622_antsew7_pins[] = { 98, };
static int mt7622_antsew7_funcs[] = { 5, };
static int mt7622_antsew8_pins[] = { 99, };
static int mt7622_antsew8_funcs[] = { 5, };
static int mt7622_antsew9_pins[] = { 100, };
static int mt7622_antsew9_funcs[] = { 5, };
static int mt7622_antsew10_pins[] = { 101, };
static int mt7622_antsew10_funcs[] = { 5, };
static int mt7622_antsew11_pins[] = { 102, };
static int mt7622_antsew11_funcs[] = { 5, };
static int mt7622_antsew12_pins[] = { 73, };
static int mt7622_antsew12_funcs[] = { 5, };
static int mt7622_antsew13_pins[] = { 74, };
static int mt7622_antsew13_funcs[] = { 5, };
static int mt7622_antsew14_pins[] = { 75, };
static int mt7622_antsew14_funcs[] = { 5, };
static int mt7622_antsew15_pins[] = { 76, };
static int mt7622_antsew15_funcs[] = { 5, };
static int mt7622_antsew16_pins[] = { 77, };
static int mt7622_antsew16_funcs[] = { 5, };
static int mt7622_antsew17_pins[] = { 22, };
static int mt7622_antsew17_funcs[] = { 5, };
static int mt7622_antsew18_pins[] = { 79, };
static int mt7622_antsew18_funcs[] = { 5, };
static int mt7622_antsew19_pins[] = { 80, };
static int mt7622_antsew19_funcs[] = { 5, };
static int mt7622_antsew20_pins[] = { 81, };
static int mt7622_antsew20_funcs[] = { 5, };
static int mt7622_antsew21_pins[] = { 82, };
static int mt7622_antsew21_funcs[] = { 5, };
static int mt7622_antsew22_pins[] = { 14, };
static int mt7622_antsew22_funcs[] = { 5, };
static int mt7622_antsew23_pins[] = { 15, };
static int mt7622_antsew23_funcs[] = { 5, };
static int mt7622_antsew24_pins[] = { 16, };
static int mt7622_antsew24_funcs[] = { 5, };
static int mt7622_antsew25_pins[] = { 17, };
static int mt7622_antsew25_funcs[] = { 5, };
static int mt7622_antsew26_pins[] = { 18, };
static int mt7622_antsew26_funcs[] = { 5, };
static int mt7622_antsew27_pins[] = { 19, };
static int mt7622_antsew27_funcs[] = { 5, };
static int mt7622_antsew28_pins[] = { 20, };
static int mt7622_antsew28_funcs[] = { 5, };
static int mt7622_antsew29_pins[] = { 21, };
static int mt7622_antsew29_funcs[] = { 5, };

/* EMMC */
static int mt7622_emmc_pins[] = { 40, 41, 42, 43, 44, 45, 47, 48, 49, 50, };
static int mt7622_emmc_funcs[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, };

static int mt7622_emmc_wst_pins[] = { 37, };
static int mt7622_emmc_wst_funcs[] = { 1, };

/* WED fow EPHY */
static int mt7622_ephy_weds_pins[] = { 86, 91, 92, 93, 94, };
static int mt7622_ephy_weds_funcs[] = { 0, 0, 0, 0, 0, };
static int mt7622_ephy0_wed_pins[] = { 86, };
static int mt7622_ephy0_wed_funcs[] = { 0, };
static int mt7622_ephy1_wed_pins[] = { 91, };
static int mt7622_ephy1_wed_funcs[] = { 2, };
static int mt7622_ephy2_wed_pins[] = { 92, };
static int mt7622_ephy2_wed_funcs[] = { 2, };
static int mt7622_ephy3_wed_pins[] = { 93, };
static int mt7622_ephy3_wed_funcs[] = { 2, };
static int mt7622_ephy4_wed_pins[] = { 94, };
static int mt7622_ephy4_wed_funcs[] = { 2, };

/* Embedded Switch */
static int mt7622_esw_pins[] = { 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61,
				 62, 63, 64, 65, 66, 67, 68, 69, 70, };
static int mt7622_esw_funcs[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				  0, 0, 0, 0, 0, 0, 0, 0, 0, };
static int mt7622_esw_p0_p1_pins[] = { 51, 52, 53, 54, 55, 56, 57, 58, };
static int mt7622_esw_p0_p1_funcs[] = { 0, 0, 0, 0, 0, 0, 0, 0, };
static int mt7622_esw_p2_p3_p4_pins[] = { 59, 60, 61, 62, 63, 64, 65, 66, 67,
					  68, 69, 70, };
static int mt7622_esw_p2_p3_p4_funcs[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0,
					   0, 0, 0, };
/* WGMII via ESW */
static int mt7622_wgmii_via_esw_pins[] = { 59, 60, 61, 62, 63, 64, 65, 66,
					   67, 68, 69, 70, };
static int mt7622_wgmii_via_esw_funcs[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					    0, };

/* WGMII via GMAC1 */
static int mt7622_wgmii_via_gmac1_pins[] = { 59, 60, 61, 62, 63, 64, 65, 66,
					     67, 68, 69, 70, };
static int mt7622_wgmii_via_gmac1_funcs[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
					      2, };

/* WGMII via GMAC2 */
static int mt7622_wgmii_via_gmac2_pins[] = { 25, 26, 27, 28, 29, 30, 31, 32,
					     33, 34, 35, 36, };
static int mt7622_wgmii_via_gmac2_funcs[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					      0, };

/* I2C */
static int mt7622_i2c0_pins[] = { 14, 15, };
static int mt7622_i2c0_funcs[] = { 0, 0, };
static int mt7622_i2c1_0_pins[] = { 55, 56, };
static int mt7622_i2c1_0_funcs[] = { 0, 0, };
static int mt7622_i2c1_1_pins[] = { 73, 74, };
static int mt7622_i2c1_1_funcs[] = { 3, 3, };
static int mt7622_i2c1_2_pins[] = { 87, 88, };
static int mt7622_i2c1_2_funcs[] = { 0, 0, };
static int mt7622_i2c2_0_pins[] = { 57, 58, };
static int mt7622_i2c2_0_funcs[] = { 0, 0, };
static int mt7622_i2c2_1_pins[] = { 75, 76, };
static int mt7622_i2c2_1_funcs[] = { 3, 3, };
static int mt7622_i2c2_2_pins[] = { 89, 90, };
static int mt7622_i2c2_2_funcs[] = { 0, 0, };

/* I2S */
static int mt7622_i2s_in_mcwk_bcwk_ws_pins[] = { 3, 4, 5, };
static int mt7622_i2s_in_mcwk_bcwk_ws_funcs[] = { 3, 3, 0, };
static int mt7622_i2s1_in_data_pins[] = { 1, };
static int mt7622_i2s1_in_data_funcs[] = { 0, };
static int mt7622_i2s2_in_data_pins[] = { 16, };
static int mt7622_i2s2_in_data_funcs[] = { 0, };
static int mt7622_i2s3_in_data_pins[] = { 17, };
static int mt7622_i2s3_in_data_funcs[] = { 0, };
static int mt7622_i2s4_in_data_pins[] = { 18, };
static int mt7622_i2s4_in_data_funcs[] = { 0, };
static int mt7622_i2s_out_mcwk_bcwk_ws_pins[] = { 3, 4, 5, };
static int mt7622_i2s_out_mcwk_bcwk_ws_funcs[] = { 0, 0, 0, };
static int mt7622_i2s1_out_data_pins[] = { 2, };
static int mt7622_i2s1_out_data_funcs[] = { 0, };
static int mt7622_i2s2_out_data_pins[] = { 19, };
static int mt7622_i2s2_out_data_funcs[] = { 0, };
static int mt7622_i2s3_out_data_pins[] = { 20, };
static int mt7622_i2s3_out_data_funcs[] = { 0, };
static int mt7622_i2s4_out_data_pins[] = { 21, };
static int mt7622_i2s4_out_data_funcs[] = { 0, };

/* IW */
static int mt7622_iw_0_tx_pins[] = { 16, };
static int mt7622_iw_0_tx_funcs[] = { 4, };
static int mt7622_iw_1_tx_pins[] = { 59, };
static int mt7622_iw_1_tx_funcs[] = { 5, };
static int mt7622_iw_2_tx_pins[] = { 99, };
static int mt7622_iw_2_tx_funcs[] = { 3, };
static int mt7622_iw_0_wx_pins[] = { 17, };
static int mt7622_iw_0_wx_funcs[] = { 4, };
static int mt7622_iw_1_wx_pins[] = { 60, };
static int mt7622_iw_1_wx_funcs[] = { 5, };
static int mt7622_iw_2_wx_pins[] = { 100, };
static int mt7622_iw_2_wx_funcs[] = { 3, };

/* MDIO */
static int mt7622_mdc_mdio_pins[] = { 23, 24, };
static int mt7622_mdc_mdio_funcs[] = { 0, 0, };

/* PCIE */
static int mt7622_pcie0_0_waken_pins[] = { 14, };
static int mt7622_pcie0_0_waken_funcs[] = { 2, };
static int mt7622_pcie0_0_cwkweq_pins[] = { 15, };
static int mt7622_pcie0_0_cwkweq_funcs[] = { 2, };
static int mt7622_pcie0_1_waken_pins[] = { 79, };
static int mt7622_pcie0_1_waken_funcs[] = { 4, };
static int mt7622_pcie0_1_cwkweq_pins[] = { 80, };
static int mt7622_pcie0_1_cwkweq_funcs[] = { 4, };
static int mt7622_pcie1_0_waken_pins[] = { 14, };
static int mt7622_pcie1_0_waken_funcs[] = { 3, };
static int mt7622_pcie1_0_cwkweq_pins[] = { 15, };
static int mt7622_pcie1_0_cwkweq_funcs[] = { 3, };

static int mt7622_pcie0_pad_pewst_pins[] = { 83, };
static int mt7622_pcie0_pad_pewst_funcs[] = { 0, };
static int mt7622_pcie1_pad_pewst_pins[] = { 84, };
static int mt7622_pcie1_pad_pewst_funcs[] = { 0, };

/* PMIC bus */
static int mt7622_pmic_bus_pins[] = { 71, 72, };
static int mt7622_pmic_bus_funcs[] = { 0, 0, };

/* Pawawwew NAND */
static int mt7622_pnand_pins[] = { 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
				   48, 49, 50, };
static int mt7622_pnand_funcs[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				    0, };

/* PWM */
static int mt7622_pwm_ch1_0_pins[] = { 51, };
static int mt7622_pwm_ch1_0_funcs[] = { 3, };
static int mt7622_pwm_ch1_1_pins[] = { 73, };
static int mt7622_pwm_ch1_1_funcs[] = { 4, };
static int mt7622_pwm_ch1_2_pins[] = { 95, };
static int mt7622_pwm_ch1_2_funcs[] = { 0, };
static int mt7622_pwm_ch2_0_pins[] = { 52, };
static int mt7622_pwm_ch2_0_funcs[] = { 3, };
static int mt7622_pwm_ch2_1_pins[] = { 74, };
static int mt7622_pwm_ch2_1_funcs[] = { 4, };
static int mt7622_pwm_ch2_2_pins[] = { 96, };
static int mt7622_pwm_ch2_2_funcs[] = { 0, };
static int mt7622_pwm_ch3_0_pins[] = { 53, };
static int mt7622_pwm_ch3_0_funcs[] = { 3, };
static int mt7622_pwm_ch3_1_pins[] = { 75, };
static int mt7622_pwm_ch3_1_funcs[] = { 4, };
static int mt7622_pwm_ch3_2_pins[] = { 97, };
static int mt7622_pwm_ch3_2_funcs[] = { 0, };
static int mt7622_pwm_ch4_0_pins[] = { 54, };
static int mt7622_pwm_ch4_0_funcs[] = { 3, };
static int mt7622_pwm_ch4_1_pins[] = { 67, };
static int mt7622_pwm_ch4_1_funcs[] = { 3, };
static int mt7622_pwm_ch4_2_pins[] = { 76, };
static int mt7622_pwm_ch4_2_funcs[] = { 4, };
static int mt7622_pwm_ch4_3_pins[] = { 98, };
static int mt7622_pwm_ch4_3_funcs[] = { 0, };
static int mt7622_pwm_ch5_0_pins[] = { 68, };
static int mt7622_pwm_ch5_0_funcs[] = { 3, };
static int mt7622_pwm_ch5_1_pins[] = { 77, };
static int mt7622_pwm_ch5_1_funcs[] = { 4, };
static int mt7622_pwm_ch5_2_pins[] = { 99, };
static int mt7622_pwm_ch5_2_funcs[] = { 0, };
static int mt7622_pwm_ch6_0_pins[] = { 69, };
static int mt7622_pwm_ch6_0_funcs[] = { 3, };
static int mt7622_pwm_ch6_1_pins[] = { 78, };
static int mt7622_pwm_ch6_1_funcs[] = { 4, };
static int mt7622_pwm_ch6_2_pins[] = { 81, };
static int mt7622_pwm_ch6_2_funcs[] = { 4, };
static int mt7622_pwm_ch6_3_pins[] = { 100, };
static int mt7622_pwm_ch6_3_funcs[] = { 0, };

/* SD */
static int mt7622_sd_0_pins[] = { 16, 17, 18, 19, 20, 21, };
static int mt7622_sd_0_funcs[] = { 2, 2, 2, 2, 2, 2, };
static int mt7622_sd_1_pins[] = { 25, 26, 27, 28, 29, 30, };
static int mt7622_sd_1_funcs[] = { 2, 2, 2, 2, 2, 2, };

/* Sewiaw NAND */
static int mt7622_snfi_pins[] = { 8, 9, 10, 11, 12, 13, };
static int mt7622_snfi_funcs[] = { 2, 2, 2, 2, 2, 2, };

/* SPI NOW */
static int mt7622_spi_pins[] = { 8, 9, 10, 11, 12, 13 };
static int mt7622_spi_funcs[] = { 0, 0, 0, 0, 0, 0, };

/* SPIC */
static int mt7622_spic0_0_pins[] = { 63, 64, 65, 66, };
static int mt7622_spic0_0_funcs[] = { 4, 4, 4, 4, };
static int mt7622_spic0_1_pins[] = { 79, 80, 81, 82, };
static int mt7622_spic0_1_funcs[] = { 3, 3, 3, 3, };
static int mt7622_spic1_0_pins[] = { 67, 68, 69, 70, };
static int mt7622_spic1_0_funcs[] = { 4, 4, 4, 4, };
static int mt7622_spic1_1_pins[] = { 73, 74, 75, 76, };
static int mt7622_spic1_1_funcs[] = { 0, 0, 0, 0, };
static int mt7622_spic2_0_pins[] = { 10, 11, 12, 13, };
static int mt7622_spic2_0_funcs[] = { 0, 0, 0, 0, };
static int mt7622_spic2_0_wp_howd_pins[] = { 8, 9, };
static int mt7622_spic2_0_wp_howd_funcs[] = { 0, 0, };

/* TDM */
static int mt7622_tdm_0_out_mcwk_bcwk_ws_pins[] = { 8, 9, 10, };
static int mt7622_tdm_0_out_mcwk_bcwk_ws_funcs[] = { 3, 3, 3, };
static int mt7622_tdm_0_in_mcwk_bcwk_ws_pins[] = { 11, 12, 13, };
static int mt7622_tdm_0_in_mcwk_bcwk_ws_funcs[] = { 3, 3, 3, };
static int mt7622_tdm_0_out_data_pins[] = { 20, };
static int mt7622_tdm_0_out_data_funcs[] = { 3, };
static int mt7622_tdm_0_in_data_pins[] = { 21, };
static int mt7622_tdm_0_in_data_funcs[] = { 3, };
static int mt7622_tdm_1_out_mcwk_bcwk_ws_pins[] = { 57, 58, 59, };
static int mt7622_tdm_1_out_mcwk_bcwk_ws_funcs[] = { 3, 3, 3, };
static int mt7622_tdm_1_in_mcwk_bcwk_ws_pins[] = { 60, 61, 62, };
static int mt7622_tdm_1_in_mcwk_bcwk_ws_funcs[] = { 3, 3, 3, };
static int mt7622_tdm_1_out_data_pins[] = { 55, };
static int mt7622_tdm_1_out_data_funcs[] = { 3, };
static int mt7622_tdm_1_in_data_pins[] = { 56, };
static int mt7622_tdm_1_in_data_funcs[] = { 3, };

/* UAWT */
static int mt7622_uawt0_0_tx_wx_pins[] = { 6, 7, };
static int mt7622_uawt0_0_tx_wx_funcs[] = { 0, 0, };
static int mt7622_uawt1_0_tx_wx_pins[] = { 55, 56, };
static int mt7622_uawt1_0_tx_wx_funcs[] = { 2, 2, };
static int mt7622_uawt1_0_wts_cts_pins[] = { 57, 58, };
static int mt7622_uawt1_0_wts_cts_funcs[] = { 2, 2, };
static int mt7622_uawt1_1_tx_wx_pins[] = { 73, 74, };
static int mt7622_uawt1_1_tx_wx_funcs[] = { 2, 2, };
static int mt7622_uawt1_1_wts_cts_pins[] = { 75, 76, };
static int mt7622_uawt1_1_wts_cts_funcs[] = { 2, 2, };
static int mt7622_uawt2_0_tx_wx_pins[] = { 3, 4, };
static int mt7622_uawt2_0_tx_wx_funcs[] = { 2, 2, };
static int mt7622_uawt2_0_wts_cts_pins[] = { 1, 2, };
static int mt7622_uawt2_0_wts_cts_funcs[] = { 2, 2, };
static int mt7622_uawt2_1_tx_wx_pins[] = { 51, 52, };
static int mt7622_uawt2_1_tx_wx_funcs[] = { 0, 0, };
static int mt7622_uawt2_1_wts_cts_pins[] = { 53, 54, };
static int mt7622_uawt2_1_wts_cts_funcs[] = { 0, 0, };
static int mt7622_uawt2_2_tx_wx_pins[] = { 59, 60, };
static int mt7622_uawt2_2_tx_wx_funcs[] = { 4, 4, };
static int mt7622_uawt2_2_wts_cts_pins[] = { 61, 62, };
static int mt7622_uawt2_2_wts_cts_funcs[] = { 4, 4, };
static int mt7622_uawt2_3_tx_wx_pins[] = { 95, 96, };
static int mt7622_uawt2_3_tx_wx_funcs[] = { 3, 3, };
static int mt7622_uawt3_0_tx_wx_pins[] = { 57, 58, };
static int mt7622_uawt3_0_tx_wx_funcs[] = { 5, 5, };
static int mt7622_uawt3_1_tx_wx_pins[] = { 81, 82, };
static int mt7622_uawt3_1_tx_wx_funcs[] = { 0, 0, };
static int mt7622_uawt3_1_wts_cts_pins[] = { 79, 80, };
static int mt7622_uawt3_1_wts_cts_funcs[] = { 0, 0, };
static int mt7622_uawt4_0_tx_wx_pins[] = { 61, 62, };
static int mt7622_uawt4_0_tx_wx_funcs[] = { 5, 5, };
static int mt7622_uawt4_1_tx_wx_pins[] = { 91, 92, };
static int mt7622_uawt4_1_tx_wx_funcs[] = { 0, 0, };
static int mt7622_uawt4_1_wts_cts_pins[] = { 93, 94 };
static int mt7622_uawt4_1_wts_cts_funcs[] = { 0, 0, };
static int mt7622_uawt4_2_tx_wx_pins[] = { 97, 98, };
static int mt7622_uawt4_2_tx_wx_funcs[] = { 2, 2, };
static int mt7622_uawt4_2_wts_cts_pins[] = { 95, 96 };
static int mt7622_uawt4_2_wts_cts_funcs[] = { 2, 2, };

/* Watchdog */
static int mt7622_watchdog_pins[] = { 78, };
static int mt7622_watchdog_funcs[] = { 0, };

/* WWAN WED */
static int mt7622_wwed_pins[] = { 85, };
static int mt7622_wwed_funcs[] = { 0, };

static const stwuct gwoup_desc mt7622_gwoups[] = {
	PINCTWW_PIN_GWOUP("antsew0", mt7622_antsew0),
	PINCTWW_PIN_GWOUP("antsew1", mt7622_antsew1),
	PINCTWW_PIN_GWOUP("antsew2", mt7622_antsew2),
	PINCTWW_PIN_GWOUP("antsew3", mt7622_antsew3),
	PINCTWW_PIN_GWOUP("antsew4", mt7622_antsew4),
	PINCTWW_PIN_GWOUP("antsew5", mt7622_antsew5),
	PINCTWW_PIN_GWOUP("antsew6", mt7622_antsew6),
	PINCTWW_PIN_GWOUP("antsew7", mt7622_antsew7),
	PINCTWW_PIN_GWOUP("antsew8", mt7622_antsew8),
	PINCTWW_PIN_GWOUP("antsew9", mt7622_antsew9),
	PINCTWW_PIN_GWOUP("antsew10", mt7622_antsew10),
	PINCTWW_PIN_GWOUP("antsew11", mt7622_antsew11),
	PINCTWW_PIN_GWOUP("antsew12", mt7622_antsew12),
	PINCTWW_PIN_GWOUP("antsew13", mt7622_antsew13),
	PINCTWW_PIN_GWOUP("antsew14", mt7622_antsew14),
	PINCTWW_PIN_GWOUP("antsew15", mt7622_antsew15),
	PINCTWW_PIN_GWOUP("antsew16", mt7622_antsew16),
	PINCTWW_PIN_GWOUP("antsew17", mt7622_antsew17),
	PINCTWW_PIN_GWOUP("antsew18", mt7622_antsew18),
	PINCTWW_PIN_GWOUP("antsew19", mt7622_antsew19),
	PINCTWW_PIN_GWOUP("antsew20", mt7622_antsew20),
	PINCTWW_PIN_GWOUP("antsew21", mt7622_antsew21),
	PINCTWW_PIN_GWOUP("antsew22", mt7622_antsew22),
	PINCTWW_PIN_GWOUP("antsew23", mt7622_antsew23),
	PINCTWW_PIN_GWOUP("antsew24", mt7622_antsew24),
	PINCTWW_PIN_GWOUP("antsew25", mt7622_antsew25),
	PINCTWW_PIN_GWOUP("antsew26", mt7622_antsew26),
	PINCTWW_PIN_GWOUP("antsew27", mt7622_antsew27),
	PINCTWW_PIN_GWOUP("antsew28", mt7622_antsew28),
	PINCTWW_PIN_GWOUP("antsew29", mt7622_antsew29),
	PINCTWW_PIN_GWOUP("emmc", mt7622_emmc),
	PINCTWW_PIN_GWOUP("emmc_wst", mt7622_emmc_wst),
	PINCTWW_PIN_GWOUP("ephy_weds", mt7622_ephy_weds),
	PINCTWW_PIN_GWOUP("ephy0_wed", mt7622_ephy0_wed),
	PINCTWW_PIN_GWOUP("ephy1_wed", mt7622_ephy1_wed),
	PINCTWW_PIN_GWOUP("ephy2_wed", mt7622_ephy2_wed),
	PINCTWW_PIN_GWOUP("ephy3_wed", mt7622_ephy3_wed),
	PINCTWW_PIN_GWOUP("ephy4_wed", mt7622_ephy4_wed),
	PINCTWW_PIN_GWOUP("esw", mt7622_esw),
	PINCTWW_PIN_GWOUP("esw_p0_p1", mt7622_esw_p0_p1),
	PINCTWW_PIN_GWOUP("esw_p2_p3_p4", mt7622_esw_p2_p3_p4),
	PINCTWW_PIN_GWOUP("wgmii_via_esw", mt7622_wgmii_via_esw),
	PINCTWW_PIN_GWOUP("wgmii_via_gmac1", mt7622_wgmii_via_gmac1),
	PINCTWW_PIN_GWOUP("wgmii_via_gmac2", mt7622_wgmii_via_gmac2),
	PINCTWW_PIN_GWOUP("i2c0", mt7622_i2c0),
	PINCTWW_PIN_GWOUP("i2c1_0", mt7622_i2c1_0),
	PINCTWW_PIN_GWOUP("i2c1_1", mt7622_i2c1_1),
	PINCTWW_PIN_GWOUP("i2c1_2", mt7622_i2c1_2),
	PINCTWW_PIN_GWOUP("i2c2_0", mt7622_i2c2_0),
	PINCTWW_PIN_GWOUP("i2c2_1", mt7622_i2c2_1),
	PINCTWW_PIN_GWOUP("i2c2_2", mt7622_i2c2_2),
	PINCTWW_PIN_GWOUP("i2s_out_mcwk_bcwk_ws", mt7622_i2s_out_mcwk_bcwk_ws),
	PINCTWW_PIN_GWOUP("i2s_in_mcwk_bcwk_ws", mt7622_i2s_in_mcwk_bcwk_ws),
	PINCTWW_PIN_GWOUP("i2s1_in_data", mt7622_i2s1_in_data),
	PINCTWW_PIN_GWOUP("i2s2_in_data", mt7622_i2s2_in_data),
	PINCTWW_PIN_GWOUP("i2s3_in_data", mt7622_i2s3_in_data),
	PINCTWW_PIN_GWOUP("i2s4_in_data", mt7622_i2s4_in_data),
	PINCTWW_PIN_GWOUP("i2s1_out_data", mt7622_i2s1_out_data),
	PINCTWW_PIN_GWOUP("i2s2_out_data", mt7622_i2s2_out_data),
	PINCTWW_PIN_GWOUP("i2s3_out_data", mt7622_i2s3_out_data),
	PINCTWW_PIN_GWOUP("i2s4_out_data", mt7622_i2s4_out_data),
	PINCTWW_PIN_GWOUP("iw_0_tx", mt7622_iw_0_tx),
	PINCTWW_PIN_GWOUP("iw_1_tx", mt7622_iw_1_tx),
	PINCTWW_PIN_GWOUP("iw_2_tx", mt7622_iw_2_tx),
	PINCTWW_PIN_GWOUP("iw_0_wx", mt7622_iw_0_wx),
	PINCTWW_PIN_GWOUP("iw_1_wx", mt7622_iw_1_wx),
	PINCTWW_PIN_GWOUP("iw_2_wx", mt7622_iw_2_wx),
	PINCTWW_PIN_GWOUP("mdc_mdio", mt7622_mdc_mdio),
	PINCTWW_PIN_GWOUP("pcie0_0_waken", mt7622_pcie0_0_waken),
	PINCTWW_PIN_GWOUP("pcie0_0_cwkweq", mt7622_pcie0_0_cwkweq),
	PINCTWW_PIN_GWOUP("pcie0_1_waken", mt7622_pcie0_1_waken),
	PINCTWW_PIN_GWOUP("pcie0_1_cwkweq", mt7622_pcie0_1_cwkweq),
	PINCTWW_PIN_GWOUP("pcie1_0_waken", mt7622_pcie1_0_waken),
	PINCTWW_PIN_GWOUP("pcie1_0_cwkweq", mt7622_pcie1_0_cwkweq),
	PINCTWW_PIN_GWOUP("pcie0_pad_pewst", mt7622_pcie0_pad_pewst),
	PINCTWW_PIN_GWOUP("pcie1_pad_pewst", mt7622_pcie1_pad_pewst),
	PINCTWW_PIN_GWOUP("paw_nand", mt7622_pnand),
	PINCTWW_PIN_GWOUP("pmic_bus", mt7622_pmic_bus),
	PINCTWW_PIN_GWOUP("pwm_ch1_0", mt7622_pwm_ch1_0),
	PINCTWW_PIN_GWOUP("pwm_ch1_1", mt7622_pwm_ch1_1),
	PINCTWW_PIN_GWOUP("pwm_ch1_2", mt7622_pwm_ch1_2),
	PINCTWW_PIN_GWOUP("pwm_ch2_0", mt7622_pwm_ch2_0),
	PINCTWW_PIN_GWOUP("pwm_ch2_1", mt7622_pwm_ch2_1),
	PINCTWW_PIN_GWOUP("pwm_ch2_2", mt7622_pwm_ch2_2),
	PINCTWW_PIN_GWOUP("pwm_ch3_0", mt7622_pwm_ch3_0),
	PINCTWW_PIN_GWOUP("pwm_ch3_1", mt7622_pwm_ch3_1),
	PINCTWW_PIN_GWOUP("pwm_ch3_2", mt7622_pwm_ch3_2),
	PINCTWW_PIN_GWOUP("pwm_ch4_0", mt7622_pwm_ch4_0),
	PINCTWW_PIN_GWOUP("pwm_ch4_1", mt7622_pwm_ch4_1),
	PINCTWW_PIN_GWOUP("pwm_ch4_2", mt7622_pwm_ch4_2),
	PINCTWW_PIN_GWOUP("pwm_ch4_3", mt7622_pwm_ch4_3),
	PINCTWW_PIN_GWOUP("pwm_ch5_0", mt7622_pwm_ch5_0),
	PINCTWW_PIN_GWOUP("pwm_ch5_1", mt7622_pwm_ch5_1),
	PINCTWW_PIN_GWOUP("pwm_ch5_2", mt7622_pwm_ch5_2),
	PINCTWW_PIN_GWOUP("pwm_ch6_0", mt7622_pwm_ch6_0),
	PINCTWW_PIN_GWOUP("pwm_ch6_1", mt7622_pwm_ch6_1),
	PINCTWW_PIN_GWOUP("pwm_ch6_2", mt7622_pwm_ch6_2),
	PINCTWW_PIN_GWOUP("pwm_ch6_3", mt7622_pwm_ch6_3),
	PINCTWW_PIN_GWOUP("sd_0", mt7622_sd_0),
	PINCTWW_PIN_GWOUP("sd_1", mt7622_sd_1),
	PINCTWW_PIN_GWOUP("snfi", mt7622_snfi),
	PINCTWW_PIN_GWOUP("spi_now", mt7622_spi),
	PINCTWW_PIN_GWOUP("spic0_0", mt7622_spic0_0),
	PINCTWW_PIN_GWOUP("spic0_1", mt7622_spic0_1),
	PINCTWW_PIN_GWOUP("spic1_0", mt7622_spic1_0),
	PINCTWW_PIN_GWOUP("spic1_1", mt7622_spic1_1),
	PINCTWW_PIN_GWOUP("spic2_0", mt7622_spic2_0),
	PINCTWW_PIN_GWOUP("spic2_0_wp_howd", mt7622_spic2_0_wp_howd),
	PINCTWW_PIN_GWOUP("tdm_0_out_mcwk_bcwk_ws",
			  mt7622_tdm_0_out_mcwk_bcwk_ws),
	PINCTWW_PIN_GWOUP("tdm_0_in_mcwk_bcwk_ws",
			  mt7622_tdm_0_in_mcwk_bcwk_ws),
	PINCTWW_PIN_GWOUP("tdm_0_out_data",  mt7622_tdm_0_out_data),
	PINCTWW_PIN_GWOUP("tdm_0_in_data", mt7622_tdm_0_in_data),
	PINCTWW_PIN_GWOUP("tdm_1_out_mcwk_bcwk_ws",
			  mt7622_tdm_1_out_mcwk_bcwk_ws),
	PINCTWW_PIN_GWOUP("tdm_1_in_mcwk_bcwk_ws",
			  mt7622_tdm_1_in_mcwk_bcwk_ws),
	PINCTWW_PIN_GWOUP("tdm_1_out_data",  mt7622_tdm_1_out_data),
	PINCTWW_PIN_GWOUP("tdm_1_in_data", mt7622_tdm_1_in_data),
	PINCTWW_PIN_GWOUP("uawt0_0_tx_wx", mt7622_uawt0_0_tx_wx),
	PINCTWW_PIN_GWOUP("uawt1_0_tx_wx", mt7622_uawt1_0_tx_wx),
	PINCTWW_PIN_GWOUP("uawt1_0_wts_cts", mt7622_uawt1_0_wts_cts),
	PINCTWW_PIN_GWOUP("uawt1_1_tx_wx", mt7622_uawt1_1_tx_wx),
	PINCTWW_PIN_GWOUP("uawt1_1_wts_cts", mt7622_uawt1_1_wts_cts),
	PINCTWW_PIN_GWOUP("uawt2_0_tx_wx", mt7622_uawt2_0_tx_wx),
	PINCTWW_PIN_GWOUP("uawt2_0_wts_cts", mt7622_uawt2_0_wts_cts),
	PINCTWW_PIN_GWOUP("uawt2_1_tx_wx", mt7622_uawt2_1_tx_wx),
	PINCTWW_PIN_GWOUP("uawt2_1_wts_cts", mt7622_uawt2_1_wts_cts),
	PINCTWW_PIN_GWOUP("uawt2_2_tx_wx", mt7622_uawt2_2_tx_wx),
	PINCTWW_PIN_GWOUP("uawt2_2_wts_cts", mt7622_uawt2_2_wts_cts),
	PINCTWW_PIN_GWOUP("uawt2_3_tx_wx", mt7622_uawt2_3_tx_wx),
	PINCTWW_PIN_GWOUP("uawt3_0_tx_wx", mt7622_uawt3_0_tx_wx),
	PINCTWW_PIN_GWOUP("uawt3_1_tx_wx", mt7622_uawt3_1_tx_wx),
	PINCTWW_PIN_GWOUP("uawt3_1_wts_cts", mt7622_uawt3_1_wts_cts),
	PINCTWW_PIN_GWOUP("uawt4_0_tx_wx", mt7622_uawt4_0_tx_wx),
	PINCTWW_PIN_GWOUP("uawt4_1_tx_wx", mt7622_uawt4_1_tx_wx),
	PINCTWW_PIN_GWOUP("uawt4_1_wts_cts", mt7622_uawt4_1_wts_cts),
	PINCTWW_PIN_GWOUP("uawt4_2_tx_wx", mt7622_uawt4_2_tx_wx),
	PINCTWW_PIN_GWOUP("uawt4_2_wts_cts", mt7622_uawt4_2_wts_cts),
	PINCTWW_PIN_GWOUP("watchdog", mt7622_watchdog),
	PINCTWW_PIN_GWOUP("wwed", mt7622_wwed),
};

/* Joint those gwoups owning the same capabiwity in usew point of view which
 * awwows that peopwe tend to use thwough the device twee.
 */
static const chaw *mt7622_antsew_gwoups[] = { "antsew0", "antsew1", "antsew2",
					      "antsew3", "antsew4", "antsew5",
					      "antsew6", "antsew7", "antsew8",
					      "antsew9", "antsew10", "antsew11",
					      "antsew12", "antsew13", "antsew14",
					      "antsew15", "antsew16", "antsew17",
					      "antsew18", "antsew19", "antsew20",
					      "antsew21", "antsew22", "antsew23",
					      "antsew24", "antsew25", "antsew26",
					      "antsew27", "antsew28", "antsew29",};
static const chaw *mt7622_emmc_gwoups[] = { "emmc", "emmc_wst", };
static const chaw *mt7622_ethewnet_gwoups[] = { "esw", "esw_p0_p1",
						"esw_p2_p3_p4", "mdc_mdio",
						"wgmii_via_gmac1",
						"wgmii_via_gmac2",
						"wgmii_via_esw", };
static const chaw *mt7622_i2c_gwoups[] = { "i2c0", "i2c1_0", "i2c1_1",
					   "i2c1_2", "i2c2_0", "i2c2_1",
					   "i2c2_2", };
static const chaw *mt7622_i2s_gwoups[] = { "i2s_out_mcwk_bcwk_ws",
					   "i2s_in_mcwk_bcwk_ws",
					   "i2s1_in_data", "i2s2_in_data",
					   "i2s3_in_data", "i2s4_in_data",
					   "i2s1_out_data", "i2s2_out_data",
					   "i2s3_out_data", "i2s4_out_data", };
static const chaw *mt7622_iw_gwoups[] = { "iw_0_tx", "iw_1_tx", "iw_2_tx",
					  "iw_0_wx", "iw_1_wx", "iw_2_wx"};
static const chaw *mt7622_wed_gwoups[] = { "ephy_weds", "ephy0_wed",
					   "ephy1_wed", "ephy2_wed",
					   "ephy3_wed", "ephy4_wed",
					   "wwed", };
static const chaw *mt7622_fwash_gwoups[] = { "paw_nand", "snfi", "spi_now"};
static const chaw *mt7622_pcie_gwoups[] = { "pcie0_0_waken", "pcie0_0_cwkweq",
					    "pcie0_1_waken", "pcie0_1_cwkweq",
					    "pcie1_0_waken", "pcie1_0_cwkweq",
					    "pcie0_pad_pewst",
					    "pcie1_pad_pewst", };
static const chaw *mt7622_pmic_bus_gwoups[] = { "pmic_bus", };
static const chaw *mt7622_pwm_gwoups[] = { "pwm_ch1_0", "pwm_ch1_1",
					   "pwm_ch1_2", "pwm_ch2_0",
					   "pwm_ch2_1", "pwm_ch2_2",
					   "pwm_ch3_0", "pwm_ch3_1",
					   "pwm_ch3_2", "pwm_ch4_0",
					   "pwm_ch4_1", "pwm_ch4_2",
					   "pwm_ch4_3", "pwm_ch5_0",
					   "pwm_ch5_1", "pwm_ch5_2",
					   "pwm_ch6_0", "pwm_ch6_1",
					   "pwm_ch6_2", "pwm_ch6_3", };
static const chaw *mt7622_sd_gwoups[] = { "sd_0", "sd_1", };
static const chaw *mt7622_spic_gwoups[] = { "spic0_0", "spic0_1", "spic1_0",
					    "spic1_1", "spic2_0",
					    "spic2_0_wp_howd", };
static const chaw *mt7622_tdm_gwoups[] = { "tdm_0_out_mcwk_bcwk_ws",
					   "tdm_0_in_mcwk_bcwk_ws",
					   "tdm_0_out_data",
					   "tdm_0_in_data",
					   "tdm_1_out_mcwk_bcwk_ws",
					   "tdm_1_in_mcwk_bcwk_ws",
					   "tdm_1_out_data",
					   "tdm_1_in_data", };

static const chaw *mt7622_uawt_gwoups[] = { "uawt0_0_tx_wx",
					    "uawt1_0_tx_wx", "uawt1_0_wts_cts",
					    "uawt1_1_tx_wx", "uawt1_1_wts_cts",
					    "uawt2_0_tx_wx", "uawt2_0_wts_cts",
					    "uawt2_1_tx_wx", "uawt2_1_wts_cts",
					    "uawt2_2_tx_wx", "uawt2_2_wts_cts",
					    "uawt2_3_tx_wx",
					    "uawt3_0_tx_wx",
					    "uawt3_1_tx_wx", "uawt3_1_wts_cts",
					    "uawt4_0_tx_wx",
					    "uawt4_1_tx_wx", "uawt4_1_wts_cts",
					    "uawt4_2_tx_wx",
					    "uawt4_2_wts_cts",};
static const chaw *mt7622_wdt_gwoups[] = { "watchdog", };

static const stwuct function_desc mt7622_functions[] = {
	{"antsew", mt7622_antsew_gwoups, AWWAY_SIZE(mt7622_antsew_gwoups)},
	{"emmc", mt7622_emmc_gwoups, AWWAY_SIZE(mt7622_emmc_gwoups)},
	{"eth",	mt7622_ethewnet_gwoups, AWWAY_SIZE(mt7622_ethewnet_gwoups)},
	{"i2c", mt7622_i2c_gwoups, AWWAY_SIZE(mt7622_i2c_gwoups)},
	{"i2s",	mt7622_i2s_gwoups, AWWAY_SIZE(mt7622_i2s_gwoups)},
	{"iw", mt7622_iw_gwoups, AWWAY_SIZE(mt7622_iw_gwoups)},
	{"wed",	mt7622_wed_gwoups, AWWAY_SIZE(mt7622_wed_gwoups)},
	{"fwash", mt7622_fwash_gwoups, AWWAY_SIZE(mt7622_fwash_gwoups)},
	{"pcie", mt7622_pcie_gwoups, AWWAY_SIZE(mt7622_pcie_gwoups)},
	{"pmic", mt7622_pmic_bus_gwoups, AWWAY_SIZE(mt7622_pmic_bus_gwoups)},
	{"pwm",	mt7622_pwm_gwoups, AWWAY_SIZE(mt7622_pwm_gwoups)},
	{"sd", mt7622_sd_gwoups, AWWAY_SIZE(mt7622_sd_gwoups)},
	{"spi",	mt7622_spic_gwoups, AWWAY_SIZE(mt7622_spic_gwoups)},
	{"tdm",	mt7622_tdm_gwoups, AWWAY_SIZE(mt7622_tdm_gwoups)},
	{"uawt", mt7622_uawt_gwoups, AWWAY_SIZE(mt7622_uawt_gwoups)},
	{"watchdog", mt7622_wdt_gwoups, AWWAY_SIZE(mt7622_wdt_gwoups)},
};

static const stwuct mtk_eint_hw mt7622_eint_hw = {
	.powt_mask = 7,
	.powts     = 7,
	.ap_num    = AWWAY_SIZE(mt7622_pins),
	.db_cnt    = 20,
	.db_time   = debounce_time_mt6765,
};

static const stwuct mtk_pin_soc mt7622_data = {
	.weg_caw = mt7622_weg_caws,
	.pins = mt7622_pins,
	.npins = AWWAY_SIZE(mt7622_pins),
	.gwps = mt7622_gwoups,
	.ngwps = AWWAY_SIZE(mt7622_gwoups),
	.funcs = mt7622_functions,
	.nfuncs = AWWAY_SIZE(mt7622_functions),
	.eint_hw = &mt7622_eint_hw,
	.gpio_m	= 1,
	.ies_pwesent = fawse,
	.base_names = mtk_defauwt_wegistew_base_names,
	.nbase_names = AWWAY_SIZE(mtk_defauwt_wegistew_base_names),
	.bias_disabwe_set = mtk_pinconf_bias_disabwe_set,
	.bias_disabwe_get = mtk_pinconf_bias_disabwe_get,
	.bias_set = mtk_pinconf_bias_set,
	.bias_get = mtk_pinconf_bias_get,
	.dwive_set = mtk_pinconf_dwive_set,
	.dwive_get = mtk_pinconf_dwive_get,
};

static const stwuct of_device_id mt7622_pinctww_of_match[] = {
	{ .compatibwe = "mediatek,mt7622-pinctww", },
	{ }
};

static int mt7622_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn mtk_moowe_pinctww_pwobe(pdev, &mt7622_data);
}

static stwuct pwatfowm_dwivew mt7622_pinctww_dwivew = {
	.dwivew = {
		.name = "mt7622-pinctww",
		.of_match_tabwe = mt7622_pinctww_of_match,
	},
	.pwobe = mt7622_pinctww_pwobe,
};

static int __init mt7622_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&mt7622_pinctww_dwivew);
}
awch_initcaww(mt7622_pinctww_init);
