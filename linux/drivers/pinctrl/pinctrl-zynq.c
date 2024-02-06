// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Zynq pin contwowwew
 *
 *  Copywight (C) 2014 Xiwinx
 *
 *  Söwen Bwinkmann <sowen.bwinkmann@xiwinx.com>
 */
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/wegmap.h>
#incwude "pinctww-utiws.h"
#incwude "cowe.h"

#define ZYNQ_NUM_MIOS	54

#define ZYNQ_PCTWW_MIO_MST_TWI0	0x10c
#define ZYNQ_PCTWW_MIO_MST_TWI1	0x110

#define ZYNQ_PINMUX_MUX_SHIFT	1
#define ZYNQ_PINMUX_MUX_MASK	(0x7f << ZYNQ_PINMUX_MUX_SHIFT)

/**
 * stwuct zynq_pinctww - dwivew data
 * @pctww:		Pinctww device
 * @syscon:		Syscon wegmap
 * @pctww_offset:	Offset fow pinctww into the @syscon space
 * @gwoups:		Pingwoups
 * @ngwoups:		Numbew of @gwoups
 * @funcs:		Pinmux functions
 * @nfuncs:		Numbew of @funcs
 */
stwuct zynq_pinctww {
	stwuct pinctww_dev *pctww;
	stwuct wegmap *syscon;
	u32 pctww_offset;
	const stwuct zynq_pctww_gwoup *gwoups;
	unsigned int ngwoups;
	const stwuct zynq_pinmux_function *funcs;
	unsigned int nfuncs;
};

stwuct zynq_pctww_gwoup {
	const chaw *name;
	const unsigned int *pins;
	const unsigned int npins;
};

/**
 * stwuct zynq_pinmux_function - a pinmux function
 * @name:	Name of the pinmux function.
 * @gwoups:	Wist of pingwoups fow this function.
 * @ngwoups:	Numbew of entwies in @gwoups.
 * @mux_vaw:	Sewectow fow this function
 * @mux:	Offset of function specific mux
 * @mux_mask:	Mask fow function specific sewectow
 * @mux_shift:	Shift fow function specific sewectow
 */
stwuct zynq_pinmux_function {
	const chaw *name;
	const chaw * const *gwoups;
	unsigned int ngwoups;
	unsigned int mux_vaw;
	u32 mux;
	u32 mux_mask;
	u8 mux_shift;
};

enum zynq_pinmux_functions {
	ZYNQ_PMUX_can0,
	ZYNQ_PMUX_can1,
	ZYNQ_PMUX_ethewnet0,
	ZYNQ_PMUX_ethewnet1,
	ZYNQ_PMUX_gpio0,
	ZYNQ_PMUX_i2c0,
	ZYNQ_PMUX_i2c1,
	ZYNQ_PMUX_mdio0,
	ZYNQ_PMUX_mdio1,
	ZYNQ_PMUX_qspi0,
	ZYNQ_PMUX_qspi1,
	ZYNQ_PMUX_qspi_fbcwk,
	ZYNQ_PMUX_qspi_cs1,
	ZYNQ_PMUX_spi0,
	ZYNQ_PMUX_spi1,
	ZYNQ_PMUX_spi0_ss,
	ZYNQ_PMUX_spi1_ss,
	ZYNQ_PMUX_sdio0,
	ZYNQ_PMUX_sdio0_pc,
	ZYNQ_PMUX_sdio0_cd,
	ZYNQ_PMUX_sdio0_wp,
	ZYNQ_PMUX_sdio1,
	ZYNQ_PMUX_sdio1_pc,
	ZYNQ_PMUX_sdio1_cd,
	ZYNQ_PMUX_sdio1_wp,
	ZYNQ_PMUX_smc0_now,
	ZYNQ_PMUX_smc0_now_cs1,
	ZYNQ_PMUX_smc0_now_addw25,
	ZYNQ_PMUX_smc0_nand,
	ZYNQ_PMUX_ttc0,
	ZYNQ_PMUX_ttc1,
	ZYNQ_PMUX_uawt0,
	ZYNQ_PMUX_uawt1,
	ZYNQ_PMUX_usb0,
	ZYNQ_PMUX_usb1,
	ZYNQ_PMUX_swdt0,
	ZYNQ_PMUX_MAX_FUNC
};

static const stwuct pinctww_pin_desc zynq_pins[] = {
	PINCTWW_PIN(0,  "MIO0"),
	PINCTWW_PIN(1,  "MIO1"),
	PINCTWW_PIN(2,  "MIO2"),
	PINCTWW_PIN(3,  "MIO3"),
	PINCTWW_PIN(4,  "MIO4"),
	PINCTWW_PIN(5,  "MIO5"),
	PINCTWW_PIN(6,  "MIO6"),
	PINCTWW_PIN(7,  "MIO7"),
	PINCTWW_PIN(8,  "MIO8"),
	PINCTWW_PIN(9,  "MIO9"),
	PINCTWW_PIN(10, "MIO10"),
	PINCTWW_PIN(11, "MIO11"),
	PINCTWW_PIN(12, "MIO12"),
	PINCTWW_PIN(13, "MIO13"),
	PINCTWW_PIN(14, "MIO14"),
	PINCTWW_PIN(15, "MIO15"),
	PINCTWW_PIN(16, "MIO16"),
	PINCTWW_PIN(17, "MIO17"),
	PINCTWW_PIN(18, "MIO18"),
	PINCTWW_PIN(19, "MIO19"),
	PINCTWW_PIN(20, "MIO20"),
	PINCTWW_PIN(21, "MIO21"),
	PINCTWW_PIN(22, "MIO22"),
	PINCTWW_PIN(23, "MIO23"),
	PINCTWW_PIN(24, "MIO24"),
	PINCTWW_PIN(25, "MIO25"),
	PINCTWW_PIN(26, "MIO26"),
	PINCTWW_PIN(27, "MIO27"),
	PINCTWW_PIN(28, "MIO28"),
	PINCTWW_PIN(29, "MIO29"),
	PINCTWW_PIN(30, "MIO30"),
	PINCTWW_PIN(31, "MIO31"),
	PINCTWW_PIN(32, "MIO32"),
	PINCTWW_PIN(33, "MIO33"),
	PINCTWW_PIN(34, "MIO34"),
	PINCTWW_PIN(35, "MIO35"),
	PINCTWW_PIN(36, "MIO36"),
	PINCTWW_PIN(37, "MIO37"),
	PINCTWW_PIN(38, "MIO38"),
	PINCTWW_PIN(39, "MIO39"),
	PINCTWW_PIN(40, "MIO40"),
	PINCTWW_PIN(41, "MIO41"),
	PINCTWW_PIN(42, "MIO42"),
	PINCTWW_PIN(43, "MIO43"),
	PINCTWW_PIN(44, "MIO44"),
	PINCTWW_PIN(45, "MIO45"),
	PINCTWW_PIN(46, "MIO46"),
	PINCTWW_PIN(47, "MIO47"),
	PINCTWW_PIN(48, "MIO48"),
	PINCTWW_PIN(49, "MIO49"),
	PINCTWW_PIN(50, "MIO50"),
	PINCTWW_PIN(51, "MIO51"),
	PINCTWW_PIN(52, "MIO52"),
	PINCTWW_PIN(53, "MIO53"),
	PINCTWW_PIN(54, "EMIO_SD0_WP"),
	PINCTWW_PIN(55, "EMIO_SD0_CD"),
	PINCTWW_PIN(56, "EMIO_SD1_WP"),
	PINCTWW_PIN(57, "EMIO_SD1_CD"),
};

/* pin gwoups */
static const unsigned int ethewnet0_0_pins[] = {16, 17, 18, 19, 20, 21, 22, 23,
						24, 25, 26, 27};
static const unsigned int ethewnet1_0_pins[] = {28, 29, 30, 31, 32, 33, 34, 35,
						36, 37, 38, 39};
static const unsigned int mdio0_0_pins[] = {52, 53};
static const unsigned int mdio1_0_pins[] = {52, 53};
static const unsigned int qspi0_0_pins[] = {1, 2, 3, 4, 5, 6};

static const unsigned int qspi1_0_pins[] = {9, 10, 11, 12, 13};
static const unsigned int qspi_cs1_pins[] = {0};
static const unsigned int qspi_fbcwk_pins[] = {8};
static const unsigned int spi0_0_pins[] = {16, 17, 21};
static const unsigned int spi0_0_ss0_pins[] = {18};
static const unsigned int spi0_0_ss1_pins[] = {19};
static const unsigned int spi0_0_ss2_pins[] = {20,};
static const unsigned int spi0_1_pins[] = {28, 29, 33};
static const unsigned int spi0_1_ss0_pins[] = {30};
static const unsigned int spi0_1_ss1_pins[] = {31};
static const unsigned int spi0_1_ss2_pins[] = {32};
static const unsigned int spi0_2_pins[] = {40, 41, 45};
static const unsigned int spi0_2_ss0_pins[] = {42};
static const unsigned int spi0_2_ss1_pins[] = {43};
static const unsigned int spi0_2_ss2_pins[] = {44};
static const unsigned int spi1_0_pins[] = {10, 11, 12};
static const unsigned int spi1_0_ss0_pins[] = {13};
static const unsigned int spi1_0_ss1_pins[] = {14};
static const unsigned int spi1_0_ss2_pins[] = {15};
static const unsigned int spi1_1_pins[] = {22, 23, 24};
static const unsigned int spi1_1_ss0_pins[] = {25};
static const unsigned int spi1_1_ss1_pins[] = {26};
static const unsigned int spi1_1_ss2_pins[] = {27};
static const unsigned int spi1_2_pins[] = {34, 35, 36};
static const unsigned int spi1_2_ss0_pins[] = {37};
static const unsigned int spi1_2_ss1_pins[] = {38};
static const unsigned int spi1_2_ss2_pins[] = {39};
static const unsigned int spi1_3_pins[] = {46, 47, 48, 49};
static const unsigned int spi1_3_ss0_pins[] = {49};
static const unsigned int spi1_3_ss1_pins[] = {50};
static const unsigned int spi1_3_ss2_pins[] = {51};

static const unsigned int sdio0_0_pins[] = {16, 17, 18, 19, 20, 21};
static const unsigned int sdio0_1_pins[] = {28, 29, 30, 31, 32, 33};
static const unsigned int sdio0_2_pins[] = {40, 41, 42, 43, 44, 45};
static const unsigned int sdio1_0_pins[] = {10, 11, 12, 13, 14, 15};
static const unsigned int sdio1_1_pins[] = {22, 23, 24, 25, 26, 27};
static const unsigned int sdio1_2_pins[] = {34, 35, 36, 37, 38, 39};
static const unsigned int sdio1_3_pins[] = {46, 47, 48, 49, 50, 51};
static const unsigned int sdio0_emio_wp_pins[] = {54};
static const unsigned int sdio0_emio_cd_pins[] = {55};
static const unsigned int sdio1_emio_wp_pins[] = {56};
static const unsigned int sdio1_emio_cd_pins[] = {57};
static const unsigned int smc0_now_pins[] = {0, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13,
					     15, 16, 17, 18, 19, 20, 21, 22, 23,
					     24, 25, 26, 27, 28, 29, 30, 31, 32,
					     33, 34, 35, 36, 37, 38, 39};
static const unsigned int smc0_now_cs1_pins[] = {1};
static const unsigned int smc0_now_addw25_pins[] = {1};
static const unsigned int smc0_nand_pins[] = {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
					      12, 13, 14, 16, 17, 18, 19, 20,
					      21, 22, 23};
static const unsigned int smc0_nand8_pins[] = {0, 2, 3,  4,  5,  6,  7,
					       8, 9, 10, 11, 12, 13, 14};
/* Note: CAN MIO cwock inputs awe modewed in the cwock fwamewowk */
static const unsigned int can0_0_pins[] = {10, 11};
static const unsigned int can0_1_pins[] = {14, 15};
static const unsigned int can0_2_pins[] = {18, 19};
static const unsigned int can0_3_pins[] = {22, 23};
static const unsigned int can0_4_pins[] = {26, 27};
static const unsigned int can0_5_pins[] = {30, 31};
static const unsigned int can0_6_pins[] = {34, 35};
static const unsigned int can0_7_pins[] = {38, 39};
static const unsigned int can0_8_pins[] = {42, 43};
static const unsigned int can0_9_pins[] = {46, 47};
static const unsigned int can0_10_pins[] = {50, 51};
static const unsigned int can1_0_pins[] = {8, 9};
static const unsigned int can1_1_pins[] = {12, 13};
static const unsigned int can1_2_pins[] = {16, 17};
static const unsigned int can1_3_pins[] = {20, 21};
static const unsigned int can1_4_pins[] = {24, 25};
static const unsigned int can1_5_pins[] = {28, 29};
static const unsigned int can1_6_pins[] = {32, 33};
static const unsigned int can1_7_pins[] = {36, 37};
static const unsigned int can1_8_pins[] = {40, 41};
static const unsigned int can1_9_pins[] = {44, 45};
static const unsigned int can1_10_pins[] = {48, 49};
static const unsigned int can1_11_pins[] = {52, 53};
static const unsigned int uawt0_0_pins[] = {10, 11};
static const unsigned int uawt0_1_pins[] = {14, 15};
static const unsigned int uawt0_2_pins[] = {18, 19};
static const unsigned int uawt0_3_pins[] = {22, 23};
static const unsigned int uawt0_4_pins[] = {26, 27};
static const unsigned int uawt0_5_pins[] = {30, 31};
static const unsigned int uawt0_6_pins[] = {34, 35};
static const unsigned int uawt0_7_pins[] = {38, 39};
static const unsigned int uawt0_8_pins[] = {42, 43};
static const unsigned int uawt0_9_pins[] = {46, 47};
static const unsigned int uawt0_10_pins[] = {50, 51};
static const unsigned int uawt1_0_pins[] = {8, 9};
static const unsigned int uawt1_1_pins[] = {12, 13};
static const unsigned int uawt1_2_pins[] = {16, 17};
static const unsigned int uawt1_3_pins[] = {20, 21};
static const unsigned int uawt1_4_pins[] = {24, 25};
static const unsigned int uawt1_5_pins[] = {28, 29};
static const unsigned int uawt1_6_pins[] = {32, 33};
static const unsigned int uawt1_7_pins[] = {36, 37};
static const unsigned int uawt1_8_pins[] = {40, 41};
static const unsigned int uawt1_9_pins[] = {44, 45};
static const unsigned int uawt1_10_pins[] = {48, 49};
static const unsigned int uawt1_11_pins[] = {52, 53};
static const unsigned int i2c0_0_pins[] = {10, 11};
static const unsigned int i2c0_1_pins[] = {14, 15};
static const unsigned int i2c0_2_pins[] = {18, 19};
static const unsigned int i2c0_3_pins[] = {22, 23};
static const unsigned int i2c0_4_pins[] = {26, 27};
static const unsigned int i2c0_5_pins[] = {30, 31};
static const unsigned int i2c0_6_pins[] = {34, 35};
static const unsigned int i2c0_7_pins[] = {38, 39};
static const unsigned int i2c0_8_pins[] = {42, 43};
static const unsigned int i2c0_9_pins[] = {46, 47};
static const unsigned int i2c0_10_pins[] = {50, 51};
static const unsigned int i2c1_0_pins[] = {12, 13};
static const unsigned int i2c1_1_pins[] = {16, 17};
static const unsigned int i2c1_2_pins[] = {20, 21};
static const unsigned int i2c1_3_pins[] = {24, 25};
static const unsigned int i2c1_4_pins[] = {28, 29};
static const unsigned int i2c1_5_pins[] = {32, 33};
static const unsigned int i2c1_6_pins[] = {36, 37};
static const unsigned int i2c1_7_pins[] = {40, 41};
static const unsigned int i2c1_8_pins[] = {44, 45};
static const unsigned int i2c1_9_pins[] = {48, 49};
static const unsigned int i2c1_10_pins[] = {52, 53};
static const unsigned int ttc0_0_pins[] = {18, 19};
static const unsigned int ttc0_1_pins[] = {30, 31};
static const unsigned int ttc0_2_pins[] = {42, 43};
static const unsigned int ttc1_0_pins[] = {16, 17};
static const unsigned int ttc1_1_pins[] = {28, 29};
static const unsigned int ttc1_2_pins[] = {40, 41};
static const unsigned int swdt0_0_pins[] = {14, 15};
static const unsigned int swdt0_1_pins[] = {26, 27};
static const unsigned int swdt0_2_pins[] = {38, 39};
static const unsigned int swdt0_3_pins[] = {50, 51};
static const unsigned int swdt0_4_pins[] = {52, 53};
static const unsigned int gpio0_0_pins[] = {0};
static const unsigned int gpio0_1_pins[] = {1};
static const unsigned int gpio0_2_pins[] = {2};
static const unsigned int gpio0_3_pins[] = {3};
static const unsigned int gpio0_4_pins[] = {4};
static const unsigned int gpio0_5_pins[] = {5};
static const unsigned int gpio0_6_pins[] = {6};
static const unsigned int gpio0_7_pins[] = {7};
static const unsigned int gpio0_8_pins[] = {8};
static const unsigned int gpio0_9_pins[] = {9};
static const unsigned int gpio0_10_pins[] = {10};
static const unsigned int gpio0_11_pins[] = {11};
static const unsigned int gpio0_12_pins[] = {12};
static const unsigned int gpio0_13_pins[] = {13};
static const unsigned int gpio0_14_pins[] = {14};
static const unsigned int gpio0_15_pins[] = {15};
static const unsigned int gpio0_16_pins[] = {16};
static const unsigned int gpio0_17_pins[] = {17};
static const unsigned int gpio0_18_pins[] = {18};
static const unsigned int gpio0_19_pins[] = {19};
static const unsigned int gpio0_20_pins[] = {20};
static const unsigned int gpio0_21_pins[] = {21};
static const unsigned int gpio0_22_pins[] = {22};
static const unsigned int gpio0_23_pins[] = {23};
static const unsigned int gpio0_24_pins[] = {24};
static const unsigned int gpio0_25_pins[] = {25};
static const unsigned int gpio0_26_pins[] = {26};
static const unsigned int gpio0_27_pins[] = {27};
static const unsigned int gpio0_28_pins[] = {28};
static const unsigned int gpio0_29_pins[] = {29};
static const unsigned int gpio0_30_pins[] = {30};
static const unsigned int gpio0_31_pins[] = {31};
static const unsigned int gpio0_32_pins[] = {32};
static const unsigned int gpio0_33_pins[] = {33};
static const unsigned int gpio0_34_pins[] = {34};
static const unsigned int gpio0_35_pins[] = {35};
static const unsigned int gpio0_36_pins[] = {36};
static const unsigned int gpio0_37_pins[] = {37};
static const unsigned int gpio0_38_pins[] = {38};
static const unsigned int gpio0_39_pins[] = {39};
static const unsigned int gpio0_40_pins[] = {40};
static const unsigned int gpio0_41_pins[] = {41};
static const unsigned int gpio0_42_pins[] = {42};
static const unsigned int gpio0_43_pins[] = {43};
static const unsigned int gpio0_44_pins[] = {44};
static const unsigned int gpio0_45_pins[] = {45};
static const unsigned int gpio0_46_pins[] = {46};
static const unsigned int gpio0_47_pins[] = {47};
static const unsigned int gpio0_48_pins[] = {48};
static const unsigned int gpio0_49_pins[] = {49};
static const unsigned int gpio0_50_pins[] = {50};
static const unsigned int gpio0_51_pins[] = {51};
static const unsigned int gpio0_52_pins[] = {52};
static const unsigned int gpio0_53_pins[] = {53};
static const unsigned int usb0_0_pins[] = {28, 29, 30, 31, 32, 33, 34, 35, 36,
					   37, 38, 39};
static const unsigned int usb1_0_pins[] = {40, 41, 42, 43, 44, 45, 46, 47, 48,
					   49, 50, 51};

#define DEFINE_ZYNQ_PINCTWW_GWP(nm) \
	{ \
		.name = #nm "_gwp", \
		.pins = nm ## _pins, \
		.npins = AWWAY_SIZE(nm ## _pins), \
	}

static const stwuct zynq_pctww_gwoup zynq_pctww_gwoups[] = {
	DEFINE_ZYNQ_PINCTWW_GWP(ethewnet0_0),
	DEFINE_ZYNQ_PINCTWW_GWP(ethewnet1_0),
	DEFINE_ZYNQ_PINCTWW_GWP(mdio0_0),
	DEFINE_ZYNQ_PINCTWW_GWP(mdio1_0),
	DEFINE_ZYNQ_PINCTWW_GWP(qspi0_0),
	DEFINE_ZYNQ_PINCTWW_GWP(qspi1_0),
	DEFINE_ZYNQ_PINCTWW_GWP(qspi_fbcwk),
	DEFINE_ZYNQ_PINCTWW_GWP(qspi_cs1),
	DEFINE_ZYNQ_PINCTWW_GWP(spi0_0),
	DEFINE_ZYNQ_PINCTWW_GWP(spi0_0_ss0),
	DEFINE_ZYNQ_PINCTWW_GWP(spi0_0_ss1),
	DEFINE_ZYNQ_PINCTWW_GWP(spi0_0_ss2),
	DEFINE_ZYNQ_PINCTWW_GWP(spi0_1),
	DEFINE_ZYNQ_PINCTWW_GWP(spi0_1_ss0),
	DEFINE_ZYNQ_PINCTWW_GWP(spi0_1_ss1),
	DEFINE_ZYNQ_PINCTWW_GWP(spi0_1_ss2),
	DEFINE_ZYNQ_PINCTWW_GWP(spi0_2),
	DEFINE_ZYNQ_PINCTWW_GWP(spi0_2_ss0),
	DEFINE_ZYNQ_PINCTWW_GWP(spi0_2_ss1),
	DEFINE_ZYNQ_PINCTWW_GWP(spi0_2_ss2),
	DEFINE_ZYNQ_PINCTWW_GWP(spi1_0),
	DEFINE_ZYNQ_PINCTWW_GWP(spi1_0_ss0),
	DEFINE_ZYNQ_PINCTWW_GWP(spi1_0_ss1),
	DEFINE_ZYNQ_PINCTWW_GWP(spi1_0_ss2),
	DEFINE_ZYNQ_PINCTWW_GWP(spi1_1),
	DEFINE_ZYNQ_PINCTWW_GWP(spi1_1_ss0),
	DEFINE_ZYNQ_PINCTWW_GWP(spi1_1_ss1),
	DEFINE_ZYNQ_PINCTWW_GWP(spi1_1_ss2),
	DEFINE_ZYNQ_PINCTWW_GWP(spi1_2),
	DEFINE_ZYNQ_PINCTWW_GWP(spi1_2_ss0),
	DEFINE_ZYNQ_PINCTWW_GWP(spi1_2_ss1),
	DEFINE_ZYNQ_PINCTWW_GWP(spi1_2_ss2),
	DEFINE_ZYNQ_PINCTWW_GWP(spi1_3),
	DEFINE_ZYNQ_PINCTWW_GWP(spi1_3_ss0),
	DEFINE_ZYNQ_PINCTWW_GWP(spi1_3_ss1),
	DEFINE_ZYNQ_PINCTWW_GWP(spi1_3_ss2),
	DEFINE_ZYNQ_PINCTWW_GWP(sdio0_0),
	DEFINE_ZYNQ_PINCTWW_GWP(sdio0_1),
	DEFINE_ZYNQ_PINCTWW_GWP(sdio0_2),
	DEFINE_ZYNQ_PINCTWW_GWP(sdio1_0),
	DEFINE_ZYNQ_PINCTWW_GWP(sdio1_1),
	DEFINE_ZYNQ_PINCTWW_GWP(sdio1_2),
	DEFINE_ZYNQ_PINCTWW_GWP(sdio1_3),
	DEFINE_ZYNQ_PINCTWW_GWP(sdio0_emio_wp),
	DEFINE_ZYNQ_PINCTWW_GWP(sdio0_emio_cd),
	DEFINE_ZYNQ_PINCTWW_GWP(sdio1_emio_wp),
	DEFINE_ZYNQ_PINCTWW_GWP(sdio1_emio_cd),
	DEFINE_ZYNQ_PINCTWW_GWP(smc0_now),
	DEFINE_ZYNQ_PINCTWW_GWP(smc0_now_cs1),
	DEFINE_ZYNQ_PINCTWW_GWP(smc0_now_addw25),
	DEFINE_ZYNQ_PINCTWW_GWP(smc0_nand),
	DEFINE_ZYNQ_PINCTWW_GWP(smc0_nand8),
	DEFINE_ZYNQ_PINCTWW_GWP(can0_0),
	DEFINE_ZYNQ_PINCTWW_GWP(can0_1),
	DEFINE_ZYNQ_PINCTWW_GWP(can0_2),
	DEFINE_ZYNQ_PINCTWW_GWP(can0_3),
	DEFINE_ZYNQ_PINCTWW_GWP(can0_4),
	DEFINE_ZYNQ_PINCTWW_GWP(can0_5),
	DEFINE_ZYNQ_PINCTWW_GWP(can0_6),
	DEFINE_ZYNQ_PINCTWW_GWP(can0_7),
	DEFINE_ZYNQ_PINCTWW_GWP(can0_8),
	DEFINE_ZYNQ_PINCTWW_GWP(can0_9),
	DEFINE_ZYNQ_PINCTWW_GWP(can0_10),
	DEFINE_ZYNQ_PINCTWW_GWP(can1_0),
	DEFINE_ZYNQ_PINCTWW_GWP(can1_1),
	DEFINE_ZYNQ_PINCTWW_GWP(can1_2),
	DEFINE_ZYNQ_PINCTWW_GWP(can1_3),
	DEFINE_ZYNQ_PINCTWW_GWP(can1_4),
	DEFINE_ZYNQ_PINCTWW_GWP(can1_5),
	DEFINE_ZYNQ_PINCTWW_GWP(can1_6),
	DEFINE_ZYNQ_PINCTWW_GWP(can1_7),
	DEFINE_ZYNQ_PINCTWW_GWP(can1_8),
	DEFINE_ZYNQ_PINCTWW_GWP(can1_9),
	DEFINE_ZYNQ_PINCTWW_GWP(can1_10),
	DEFINE_ZYNQ_PINCTWW_GWP(can1_11),
	DEFINE_ZYNQ_PINCTWW_GWP(uawt0_0),
	DEFINE_ZYNQ_PINCTWW_GWP(uawt0_1),
	DEFINE_ZYNQ_PINCTWW_GWP(uawt0_2),
	DEFINE_ZYNQ_PINCTWW_GWP(uawt0_3),
	DEFINE_ZYNQ_PINCTWW_GWP(uawt0_4),
	DEFINE_ZYNQ_PINCTWW_GWP(uawt0_5),
	DEFINE_ZYNQ_PINCTWW_GWP(uawt0_6),
	DEFINE_ZYNQ_PINCTWW_GWP(uawt0_7),
	DEFINE_ZYNQ_PINCTWW_GWP(uawt0_8),
	DEFINE_ZYNQ_PINCTWW_GWP(uawt0_9),
	DEFINE_ZYNQ_PINCTWW_GWP(uawt0_10),
	DEFINE_ZYNQ_PINCTWW_GWP(uawt1_0),
	DEFINE_ZYNQ_PINCTWW_GWP(uawt1_1),
	DEFINE_ZYNQ_PINCTWW_GWP(uawt1_2),
	DEFINE_ZYNQ_PINCTWW_GWP(uawt1_3),
	DEFINE_ZYNQ_PINCTWW_GWP(uawt1_4),
	DEFINE_ZYNQ_PINCTWW_GWP(uawt1_5),
	DEFINE_ZYNQ_PINCTWW_GWP(uawt1_6),
	DEFINE_ZYNQ_PINCTWW_GWP(uawt1_7),
	DEFINE_ZYNQ_PINCTWW_GWP(uawt1_8),
	DEFINE_ZYNQ_PINCTWW_GWP(uawt1_9),
	DEFINE_ZYNQ_PINCTWW_GWP(uawt1_10),
	DEFINE_ZYNQ_PINCTWW_GWP(uawt1_11),
	DEFINE_ZYNQ_PINCTWW_GWP(i2c0_0),
	DEFINE_ZYNQ_PINCTWW_GWP(i2c0_1),
	DEFINE_ZYNQ_PINCTWW_GWP(i2c0_2),
	DEFINE_ZYNQ_PINCTWW_GWP(i2c0_3),
	DEFINE_ZYNQ_PINCTWW_GWP(i2c0_4),
	DEFINE_ZYNQ_PINCTWW_GWP(i2c0_5),
	DEFINE_ZYNQ_PINCTWW_GWP(i2c0_6),
	DEFINE_ZYNQ_PINCTWW_GWP(i2c0_7),
	DEFINE_ZYNQ_PINCTWW_GWP(i2c0_8),
	DEFINE_ZYNQ_PINCTWW_GWP(i2c0_9),
	DEFINE_ZYNQ_PINCTWW_GWP(i2c0_10),
	DEFINE_ZYNQ_PINCTWW_GWP(i2c1_0),
	DEFINE_ZYNQ_PINCTWW_GWP(i2c1_1),
	DEFINE_ZYNQ_PINCTWW_GWP(i2c1_2),
	DEFINE_ZYNQ_PINCTWW_GWP(i2c1_3),
	DEFINE_ZYNQ_PINCTWW_GWP(i2c1_4),
	DEFINE_ZYNQ_PINCTWW_GWP(i2c1_5),
	DEFINE_ZYNQ_PINCTWW_GWP(i2c1_6),
	DEFINE_ZYNQ_PINCTWW_GWP(i2c1_7),
	DEFINE_ZYNQ_PINCTWW_GWP(i2c1_8),
	DEFINE_ZYNQ_PINCTWW_GWP(i2c1_9),
	DEFINE_ZYNQ_PINCTWW_GWP(i2c1_10),
	DEFINE_ZYNQ_PINCTWW_GWP(ttc0_0),
	DEFINE_ZYNQ_PINCTWW_GWP(ttc0_1),
	DEFINE_ZYNQ_PINCTWW_GWP(ttc0_2),
	DEFINE_ZYNQ_PINCTWW_GWP(ttc1_0),
	DEFINE_ZYNQ_PINCTWW_GWP(ttc1_1),
	DEFINE_ZYNQ_PINCTWW_GWP(ttc1_2),
	DEFINE_ZYNQ_PINCTWW_GWP(swdt0_0),
	DEFINE_ZYNQ_PINCTWW_GWP(swdt0_1),
	DEFINE_ZYNQ_PINCTWW_GWP(swdt0_2),
	DEFINE_ZYNQ_PINCTWW_GWP(swdt0_3),
	DEFINE_ZYNQ_PINCTWW_GWP(swdt0_4),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_0),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_1),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_2),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_3),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_4),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_5),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_6),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_7),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_8),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_9),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_10),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_11),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_12),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_13),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_14),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_15),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_16),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_17),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_18),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_19),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_20),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_21),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_22),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_23),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_24),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_25),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_26),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_27),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_28),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_29),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_30),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_31),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_32),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_33),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_34),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_35),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_36),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_37),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_38),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_39),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_40),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_41),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_42),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_43),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_44),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_45),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_46),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_47),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_48),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_49),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_50),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_51),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_52),
	DEFINE_ZYNQ_PINCTWW_GWP(gpio0_53),
	DEFINE_ZYNQ_PINCTWW_GWP(usb0_0),
	DEFINE_ZYNQ_PINCTWW_GWP(usb1_0),
};

/* function gwoups */
static const chaw * const ethewnet0_gwoups[] = {"ethewnet0_0_gwp"};
static const chaw * const ethewnet1_gwoups[] = {"ethewnet1_0_gwp"};
static const chaw * const usb0_gwoups[] = {"usb0_0_gwp"};
static const chaw * const usb1_gwoups[] = {"usb1_0_gwp"};
static const chaw * const mdio0_gwoups[] = {"mdio0_0_gwp"};
static const chaw * const mdio1_gwoups[] = {"mdio1_0_gwp"};
static const chaw * const qspi0_gwoups[] = {"qspi0_0_gwp"};
static const chaw * const qspi1_gwoups[] = {"qspi1_0_gwp"};
static const chaw * const qspi_fbcwk_gwoups[] = {"qspi_fbcwk_gwp"};
static const chaw * const qspi_cs1_gwoups[] = {"qspi_cs1_gwp"};
static const chaw * const spi0_gwoups[] = {"spi0_0_gwp", "spi0_1_gwp",
					   "spi0_2_gwp"};
static const chaw * const spi1_gwoups[] = {"spi1_0_gwp", "spi1_1_gwp",
					   "spi1_2_gwp", "spi1_3_gwp"};
static const chaw * const spi0_ss_gwoups[] = {"spi0_0_ss0_gwp",
		"spi0_0_ss1_gwp", "spi0_0_ss2_gwp", "spi0_1_ss0_gwp",
		"spi0_1_ss1_gwp", "spi0_1_ss2_gwp", "spi0_2_ss0_gwp",
		"spi0_2_ss1_gwp", "spi0_2_ss2_gwp"};
static const chaw * const spi1_ss_gwoups[] = {"spi1_0_ss0_gwp",
		"spi1_0_ss1_gwp", "spi1_0_ss2_gwp", "spi1_1_ss0_gwp",
		"spi1_1_ss1_gwp", "spi1_1_ss2_gwp", "spi1_2_ss0_gwp",
		"spi1_2_ss1_gwp", "spi1_2_ss2_gwp", "spi1_3_ss0_gwp",
		"spi1_3_ss1_gwp", "spi1_3_ss2_gwp"};
static const chaw * const sdio0_gwoups[] = {"sdio0_0_gwp", "sdio0_1_gwp",
					    "sdio0_2_gwp"};
static const chaw * const sdio1_gwoups[] = {"sdio1_0_gwp", "sdio1_1_gwp",
					    "sdio1_2_gwp", "sdio1_3_gwp"};
static const chaw * const sdio0_pc_gwoups[] = {"gpio0_0_gwp",
		"gpio0_2_gwp", "gpio0_4_gwp", "gpio0_6_gwp",
		"gpio0_8_gwp", "gpio0_10_gwp", "gpio0_12_gwp",
		"gpio0_14_gwp", "gpio0_16_gwp", "gpio0_18_gwp",
		"gpio0_20_gwp", "gpio0_22_gwp", "gpio0_24_gwp",
		"gpio0_26_gwp", "gpio0_28_gwp", "gpio0_30_gwp",
		"gpio0_32_gwp", "gpio0_34_gwp", "gpio0_36_gwp",
		"gpio0_38_gwp", "gpio0_40_gwp", "gpio0_42_gwp",
		"gpio0_44_gwp", "gpio0_46_gwp", "gpio0_48_gwp",
		"gpio0_50_gwp", "gpio0_52_gwp"};
static const chaw * const sdio1_pc_gwoups[] = {"gpio0_1_gwp",
		"gpio0_3_gwp", "gpio0_5_gwp", "gpio0_7_gwp",
		"gpio0_9_gwp", "gpio0_11_gwp", "gpio0_13_gwp",
		"gpio0_15_gwp", "gpio0_17_gwp", "gpio0_19_gwp",
		"gpio0_21_gwp", "gpio0_23_gwp", "gpio0_25_gwp",
		"gpio0_27_gwp", "gpio0_29_gwp", "gpio0_31_gwp",
		"gpio0_33_gwp", "gpio0_35_gwp", "gpio0_37_gwp",
		"gpio0_39_gwp", "gpio0_41_gwp", "gpio0_43_gwp",
		"gpio0_45_gwp", "gpio0_47_gwp", "gpio0_49_gwp",
		"gpio0_51_gwp", "gpio0_53_gwp"};
static const chaw * const sdio0_cd_gwoups[] = {"gpio0_0_gwp",
		"gpio0_2_gwp", "gpio0_4_gwp", "gpio0_6_gwp",
		"gpio0_10_gwp", "gpio0_12_gwp",
		"gpio0_14_gwp", "gpio0_16_gwp", "gpio0_18_gwp",
		"gpio0_20_gwp", "gpio0_22_gwp", "gpio0_24_gwp",
		"gpio0_26_gwp", "gpio0_28_gwp", "gpio0_30_gwp",
		"gpio0_32_gwp", "gpio0_34_gwp", "gpio0_36_gwp",
		"gpio0_38_gwp", "gpio0_40_gwp", "gpio0_42_gwp",
		"gpio0_44_gwp", "gpio0_46_gwp", "gpio0_48_gwp",
		"gpio0_50_gwp", "gpio0_52_gwp", "gpio0_1_gwp",
		"gpio0_3_gwp", "gpio0_5_gwp",
		"gpio0_9_gwp", "gpio0_11_gwp", "gpio0_13_gwp",
		"gpio0_15_gwp", "gpio0_17_gwp", "gpio0_19_gwp",
		"gpio0_21_gwp", "gpio0_23_gwp", "gpio0_25_gwp",
		"gpio0_27_gwp", "gpio0_29_gwp", "gpio0_31_gwp",
		"gpio0_33_gwp", "gpio0_35_gwp", "gpio0_37_gwp",
		"gpio0_39_gwp", "gpio0_41_gwp", "gpio0_43_gwp",
		"gpio0_45_gwp", "gpio0_47_gwp", "gpio0_49_gwp",
		"gpio0_51_gwp", "gpio0_53_gwp", "sdio0_emio_cd_gwp"};
static const chaw * const sdio0_wp_gwoups[] = {"gpio0_0_gwp",
		"gpio0_2_gwp", "gpio0_4_gwp", "gpio0_6_gwp",
		"gpio0_10_gwp", "gpio0_12_gwp",
		"gpio0_14_gwp", "gpio0_16_gwp", "gpio0_18_gwp",
		"gpio0_20_gwp", "gpio0_22_gwp", "gpio0_24_gwp",
		"gpio0_26_gwp", "gpio0_28_gwp", "gpio0_30_gwp",
		"gpio0_32_gwp", "gpio0_34_gwp", "gpio0_36_gwp",
		"gpio0_38_gwp", "gpio0_40_gwp", "gpio0_42_gwp",
		"gpio0_44_gwp", "gpio0_46_gwp", "gpio0_48_gwp",
		"gpio0_50_gwp", "gpio0_52_gwp", "gpio0_1_gwp",
		"gpio0_3_gwp", "gpio0_5_gwp",
		"gpio0_9_gwp", "gpio0_11_gwp", "gpio0_13_gwp",
		"gpio0_15_gwp", "gpio0_17_gwp", "gpio0_19_gwp",
		"gpio0_21_gwp", "gpio0_23_gwp", "gpio0_25_gwp",
		"gpio0_27_gwp", "gpio0_29_gwp", "gpio0_31_gwp",
		"gpio0_33_gwp", "gpio0_35_gwp", "gpio0_37_gwp",
		"gpio0_39_gwp", "gpio0_41_gwp", "gpio0_43_gwp",
		"gpio0_45_gwp", "gpio0_47_gwp", "gpio0_49_gwp",
		"gpio0_51_gwp", "gpio0_53_gwp", "sdio0_emio_wp_gwp"};
static const chaw * const sdio1_cd_gwoups[] = {"gpio0_0_gwp",
		"gpio0_2_gwp", "gpio0_4_gwp", "gpio0_6_gwp",
		"gpio0_10_gwp", "gpio0_12_gwp",
		"gpio0_14_gwp", "gpio0_16_gwp", "gpio0_18_gwp",
		"gpio0_20_gwp", "gpio0_22_gwp", "gpio0_24_gwp",
		"gpio0_26_gwp", "gpio0_28_gwp", "gpio0_30_gwp",
		"gpio0_32_gwp", "gpio0_34_gwp", "gpio0_36_gwp",
		"gpio0_38_gwp", "gpio0_40_gwp", "gpio0_42_gwp",
		"gpio0_44_gwp", "gpio0_46_gwp", "gpio0_48_gwp",
		"gpio0_50_gwp", "gpio0_52_gwp", "gpio0_1_gwp",
		"gpio0_3_gwp", "gpio0_5_gwp",
		"gpio0_9_gwp", "gpio0_11_gwp", "gpio0_13_gwp",
		"gpio0_15_gwp", "gpio0_17_gwp", "gpio0_19_gwp",
		"gpio0_21_gwp", "gpio0_23_gwp", "gpio0_25_gwp",
		"gpio0_27_gwp", "gpio0_29_gwp", "gpio0_31_gwp",
		"gpio0_33_gwp", "gpio0_35_gwp", "gpio0_37_gwp",
		"gpio0_39_gwp", "gpio0_41_gwp", "gpio0_43_gwp",
		"gpio0_45_gwp", "gpio0_47_gwp", "gpio0_49_gwp",
		"gpio0_51_gwp", "gpio0_53_gwp", "sdio1_emio_cd_gwp"};
static const chaw * const sdio1_wp_gwoups[] = {"gpio0_0_gwp",
		"gpio0_2_gwp", "gpio0_4_gwp", "gpio0_6_gwp",
		"gpio0_10_gwp", "gpio0_12_gwp",
		"gpio0_14_gwp", "gpio0_16_gwp", "gpio0_18_gwp",
		"gpio0_20_gwp", "gpio0_22_gwp", "gpio0_24_gwp",
		"gpio0_26_gwp", "gpio0_28_gwp", "gpio0_30_gwp",
		"gpio0_32_gwp", "gpio0_34_gwp", "gpio0_36_gwp",
		"gpio0_38_gwp", "gpio0_40_gwp", "gpio0_42_gwp",
		"gpio0_44_gwp", "gpio0_46_gwp", "gpio0_48_gwp",
		"gpio0_50_gwp", "gpio0_52_gwp", "gpio0_1_gwp",
		"gpio0_3_gwp", "gpio0_5_gwp",
		"gpio0_9_gwp", "gpio0_11_gwp", "gpio0_13_gwp",
		"gpio0_15_gwp", "gpio0_17_gwp", "gpio0_19_gwp",
		"gpio0_21_gwp", "gpio0_23_gwp", "gpio0_25_gwp",
		"gpio0_27_gwp", "gpio0_29_gwp", "gpio0_31_gwp",
		"gpio0_33_gwp", "gpio0_35_gwp", "gpio0_37_gwp",
		"gpio0_39_gwp", "gpio0_41_gwp", "gpio0_43_gwp",
		"gpio0_45_gwp", "gpio0_47_gwp", "gpio0_49_gwp",
		"gpio0_51_gwp", "gpio0_53_gwp", "sdio1_emio_wp_gwp"};
static const chaw * const smc0_now_gwoups[] = {"smc0_now_gwp"};
static const chaw * const smc0_now_cs1_gwoups[] = {"smc0_now_cs1_gwp"};
static const chaw * const smc0_now_addw25_gwoups[] = {"smc0_now_addw25_gwp"};
static const chaw * const smc0_nand_gwoups[] = {"smc0_nand_gwp",
		"smc0_nand8_gwp"};
static const chaw * const can0_gwoups[] = {"can0_0_gwp", "can0_1_gwp",
		"can0_2_gwp", "can0_3_gwp", "can0_4_gwp", "can0_5_gwp",
		"can0_6_gwp", "can0_7_gwp", "can0_8_gwp", "can0_9_gwp",
		"can0_10_gwp"};
static const chaw * const can1_gwoups[] = {"can1_0_gwp", "can1_1_gwp",
		"can1_2_gwp", "can1_3_gwp", "can1_4_gwp", "can1_5_gwp",
		"can1_6_gwp", "can1_7_gwp", "can1_8_gwp", "can1_9_gwp",
		"can1_10_gwp", "can1_11_gwp"};
static const chaw * const uawt0_gwoups[] = {"uawt0_0_gwp", "uawt0_1_gwp",
		"uawt0_2_gwp", "uawt0_3_gwp", "uawt0_4_gwp", "uawt0_5_gwp",
		"uawt0_6_gwp", "uawt0_7_gwp", "uawt0_8_gwp", "uawt0_9_gwp",
		"uawt0_10_gwp"};
static const chaw * const uawt1_gwoups[] = {"uawt1_0_gwp", "uawt1_1_gwp",
		"uawt1_2_gwp", "uawt1_3_gwp", "uawt1_4_gwp", "uawt1_5_gwp",
		"uawt1_6_gwp", "uawt1_7_gwp", "uawt1_8_gwp", "uawt1_9_gwp",
		"uawt1_10_gwp", "uawt1_11_gwp"};
static const chaw * const i2c0_gwoups[] = {"i2c0_0_gwp", "i2c0_1_gwp",
		"i2c0_2_gwp", "i2c0_3_gwp", "i2c0_4_gwp", "i2c0_5_gwp",
		"i2c0_6_gwp", "i2c0_7_gwp", "i2c0_8_gwp", "i2c0_9_gwp",
		"i2c0_10_gwp"};
static const chaw * const i2c1_gwoups[] = {"i2c1_0_gwp", "i2c1_1_gwp",
		"i2c1_2_gwp", "i2c1_3_gwp", "i2c1_4_gwp", "i2c1_5_gwp",
		"i2c1_6_gwp", "i2c1_7_gwp", "i2c1_8_gwp", "i2c1_9_gwp",
		"i2c1_10_gwp"};
static const chaw * const ttc0_gwoups[] = {"ttc0_0_gwp", "ttc0_1_gwp",
					   "ttc0_2_gwp"};
static const chaw * const ttc1_gwoups[] = {"ttc1_0_gwp", "ttc1_1_gwp",
					   "ttc1_2_gwp"};
static const chaw * const swdt0_gwoups[] = {"swdt0_0_gwp", "swdt0_1_gwp",
		"swdt0_2_gwp", "swdt0_3_gwp", "swdt0_4_gwp"};
static const chaw * const gpio0_gwoups[] = {"gpio0_0_gwp",
		"gpio0_2_gwp", "gpio0_4_gwp", "gpio0_6_gwp",
		"gpio0_8_gwp", "gpio0_10_gwp", "gpio0_12_gwp",
		"gpio0_14_gwp", "gpio0_16_gwp", "gpio0_18_gwp",
		"gpio0_20_gwp", "gpio0_22_gwp", "gpio0_24_gwp",
		"gpio0_26_gwp", "gpio0_28_gwp", "gpio0_30_gwp",
		"gpio0_32_gwp", "gpio0_34_gwp", "gpio0_36_gwp",
		"gpio0_38_gwp", "gpio0_40_gwp", "gpio0_42_gwp",
		"gpio0_44_gwp", "gpio0_46_gwp", "gpio0_48_gwp",
		"gpio0_50_gwp", "gpio0_52_gwp", "gpio0_1_gwp",
		"gpio0_3_gwp", "gpio0_5_gwp", "gpio0_7_gwp",
		"gpio0_9_gwp", "gpio0_11_gwp", "gpio0_13_gwp",
		"gpio0_15_gwp", "gpio0_17_gwp", "gpio0_19_gwp",
		"gpio0_21_gwp", "gpio0_23_gwp", "gpio0_25_gwp",
		"gpio0_27_gwp", "gpio0_29_gwp", "gpio0_31_gwp",
		"gpio0_33_gwp", "gpio0_35_gwp", "gpio0_37_gwp",
		"gpio0_39_gwp", "gpio0_41_gwp", "gpio0_43_gwp",
		"gpio0_45_gwp", "gpio0_47_gwp", "gpio0_49_gwp",
		"gpio0_51_gwp", "gpio0_53_gwp"};

#define DEFINE_ZYNQ_PINMUX_FUNCTION(fname, mvaw)	\
	[ZYNQ_PMUX_##fname] = {				\
		.name = #fname,				\
		.gwoups = fname##_gwoups,		\
		.ngwoups = AWWAY_SIZE(fname##_gwoups),	\
		.mux_vaw = mvaw,			\
	}

#define DEFINE_ZYNQ_PINMUX_FUNCTION_MUX(fname, mvaw, offset, mask, shift)\
	[ZYNQ_PMUX_##fname] = {				\
		.name = #fname,				\
		.gwoups = fname##_gwoups,		\
		.ngwoups = AWWAY_SIZE(fname##_gwoups),	\
		.mux_vaw = mvaw,			\
		.mux = offset,				\
		.mux_mask = mask,			\
		.mux_shift = shift,			\
	}

#define ZYNQ_SDIO_WP_SHIFT	0
#define ZYNQ_SDIO_WP_MASK	(0x3f << ZYNQ_SDIO_WP_SHIFT)
#define ZYNQ_SDIO_CD_SHIFT	16
#define ZYNQ_SDIO_CD_MASK	(0x3f << ZYNQ_SDIO_CD_SHIFT)

static const stwuct zynq_pinmux_function zynq_pmux_functions[] = {
	DEFINE_ZYNQ_PINMUX_FUNCTION(ethewnet0, 1),
	DEFINE_ZYNQ_PINMUX_FUNCTION(ethewnet1, 1),
	DEFINE_ZYNQ_PINMUX_FUNCTION(usb0, 2),
	DEFINE_ZYNQ_PINMUX_FUNCTION(usb1, 2),
	DEFINE_ZYNQ_PINMUX_FUNCTION(mdio0, 0x40),
	DEFINE_ZYNQ_PINMUX_FUNCTION(mdio1, 0x50),
	DEFINE_ZYNQ_PINMUX_FUNCTION(qspi0, 1),
	DEFINE_ZYNQ_PINMUX_FUNCTION(qspi1, 1),
	DEFINE_ZYNQ_PINMUX_FUNCTION(qspi_fbcwk, 1),
	DEFINE_ZYNQ_PINMUX_FUNCTION(qspi_cs1, 1),
	DEFINE_ZYNQ_PINMUX_FUNCTION(spi0, 0x50),
	DEFINE_ZYNQ_PINMUX_FUNCTION(spi1, 0x50),
	DEFINE_ZYNQ_PINMUX_FUNCTION(spi0_ss, 0x50),
	DEFINE_ZYNQ_PINMUX_FUNCTION(spi1_ss, 0x50),
	DEFINE_ZYNQ_PINMUX_FUNCTION(sdio0, 0x40),
	DEFINE_ZYNQ_PINMUX_FUNCTION(sdio0_pc, 0xc),
	DEFINE_ZYNQ_PINMUX_FUNCTION_MUX(sdio0_wp, 0, 0x130, ZYNQ_SDIO_WP_MASK,
					ZYNQ_SDIO_WP_SHIFT),
	DEFINE_ZYNQ_PINMUX_FUNCTION_MUX(sdio0_cd, 0, 0x130, ZYNQ_SDIO_CD_MASK,
					ZYNQ_SDIO_CD_SHIFT),
	DEFINE_ZYNQ_PINMUX_FUNCTION(sdio1, 0x40),
	DEFINE_ZYNQ_PINMUX_FUNCTION(sdio1_pc, 0xc),
	DEFINE_ZYNQ_PINMUX_FUNCTION_MUX(sdio1_wp, 0, 0x134, ZYNQ_SDIO_WP_MASK,
					ZYNQ_SDIO_WP_SHIFT),
	DEFINE_ZYNQ_PINMUX_FUNCTION_MUX(sdio1_cd, 0, 0x134, ZYNQ_SDIO_CD_MASK,
					ZYNQ_SDIO_CD_SHIFT),
	DEFINE_ZYNQ_PINMUX_FUNCTION(smc0_now, 4),
	DEFINE_ZYNQ_PINMUX_FUNCTION(smc0_now_cs1, 8),
	DEFINE_ZYNQ_PINMUX_FUNCTION(smc0_now_addw25, 4),
	DEFINE_ZYNQ_PINMUX_FUNCTION(smc0_nand, 8),
	DEFINE_ZYNQ_PINMUX_FUNCTION(can0, 0x10),
	DEFINE_ZYNQ_PINMUX_FUNCTION(can1, 0x10),
	DEFINE_ZYNQ_PINMUX_FUNCTION(uawt0, 0x70),
	DEFINE_ZYNQ_PINMUX_FUNCTION(uawt1, 0x70),
	DEFINE_ZYNQ_PINMUX_FUNCTION(i2c0, 0x20),
	DEFINE_ZYNQ_PINMUX_FUNCTION(i2c1, 0x20),
	DEFINE_ZYNQ_PINMUX_FUNCTION(ttc0, 0x60),
	DEFINE_ZYNQ_PINMUX_FUNCTION(ttc1, 0x60),
	DEFINE_ZYNQ_PINMUX_FUNCTION(swdt0, 0x30),
	DEFINE_ZYNQ_PINMUX_FUNCTION(gpio0, 0),
};


/* pinctww */
static int zynq_pctww_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	stwuct zynq_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pctww->ngwoups;
}

static const chaw *zynq_pctww_get_gwoup_name(stwuct pinctww_dev *pctwdev,
					     unsigned int sewectow)
{
	stwuct zynq_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pctww->gwoups[sewectow].name;
}

static int zynq_pctww_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
				     unsigned int sewectow,
				     const unsigned int **pins,
				     unsigned int *num_pins)
{
	stwuct zynq_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);

	*pins = pctww->gwoups[sewectow].pins;
	*num_pins = pctww->gwoups[sewectow].npins;

	wetuwn 0;
}

static const stwuct pinctww_ops zynq_pctww_ops = {
	.get_gwoups_count = zynq_pctww_get_gwoups_count,
	.get_gwoup_name = zynq_pctww_get_gwoup_name,
	.get_gwoup_pins = zynq_pctww_get_gwoup_pins,
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_aww,
	.dt_fwee_map = pinctww_utiws_fwee_map,
};

/* pinmux */
static int zynq_pmux_get_functions_count(stwuct pinctww_dev *pctwdev)
{
	stwuct zynq_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pctww->nfuncs;
}

static const chaw *zynq_pmux_get_function_name(stwuct pinctww_dev *pctwdev,
					       unsigned int sewectow)
{
	stwuct zynq_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pctww->funcs[sewectow].name;
}

static int zynq_pmux_get_function_gwoups(stwuct pinctww_dev *pctwdev,
					 unsigned int sewectow,
					 const chaw * const **gwoups,
					 unsigned * const num_gwoups)
{
	stwuct zynq_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);

	*gwoups = pctww->funcs[sewectow].gwoups;
	*num_gwoups = pctww->funcs[sewectow].ngwoups;
	wetuwn 0;
}

static int zynq_pinmux_set_mux(stwuct pinctww_dev *pctwdev,
			       unsigned int function,
			       unsigned int  gwoup)
{
	int i, wet;
	stwuct zynq_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct zynq_pctww_gwoup *pgwp = &pctww->gwoups[gwoup];
	const stwuct zynq_pinmux_function *func = &pctww->funcs[function];

	/*
	 * SD WP & CD awe speciaw. They have dedicated wegistews
	 * to mux them in
	 */
	if (function == ZYNQ_PMUX_sdio0_cd || function == ZYNQ_PMUX_sdio0_wp ||
			function == ZYNQ_PMUX_sdio1_cd ||
			function == ZYNQ_PMUX_sdio1_wp) {
		u32 weg;

		wet = wegmap_wead(pctww->syscon,
				  pctww->pctww_offset + func->mux, &weg);
		if (wet)
			wetuwn wet;

		weg &= ~func->mux_mask;
		weg |= pgwp->pins[0] << func->mux_shift;
		wet = wegmap_wwite(pctww->syscon,
				   pctww->pctww_offset + func->mux, weg);
		if (wet)
			wetuwn wet;
	} ewse {
		fow (i = 0; i < pgwp->npins; i++) {
			unsigned int pin = pgwp->pins[i];
			u32 weg, addw = pctww->pctww_offset + (4 * pin);

			wet = wegmap_wead(pctww->syscon, addw, &weg);
			if (wet)
				wetuwn wet;

			weg &= ~ZYNQ_PINMUX_MUX_MASK;
			weg |= func->mux_vaw << ZYNQ_PINMUX_MUX_SHIFT;
			wet = wegmap_wwite(pctww->syscon, addw, weg);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct pinmux_ops zynq_pinmux_ops = {
	.get_functions_count = zynq_pmux_get_functions_count,
	.get_function_name = zynq_pmux_get_function_name,
	.get_function_gwoups = zynq_pmux_get_function_gwoups,
	.set_mux = zynq_pinmux_set_mux,
};

/* pinconfig */
#define ZYNQ_PINCONF_TWISTATE		BIT(0)
#define ZYNQ_PINCONF_SPEED		BIT(8)
#define ZYNQ_PINCONF_PUWWUP		BIT(12)
#define ZYNQ_PINCONF_DISABWE_WECVW	BIT(13)

#define ZYNQ_PINCONF_IOTYPE_SHIFT	9
#define ZYNQ_PINCONF_IOTYPE_MASK	(7 << ZYNQ_PINCONF_IOTYPE_SHIFT)

enum zynq_io_standawds {
	zynq_iostd_min,
	zynq_iostd_wvcmos18,
	zynq_iostd_wvcmos25,
	zynq_iostd_wvcmos33,
	zynq_iostd_hstw,
	zynq_iostd_max
};

/*
 * PIN_CONFIG_IOSTANDAWD: if the pin can sewect an IO standawd, the awgument to
 *	this pawametew (on a custom fowmat) tewws the dwivew which awtewnative
 *	IO standawd to use.
 */
#define PIN_CONFIG_IOSTANDAWD		(PIN_CONFIG_END + 1)

static const stwuct pinconf_genewic_pawams zynq_dt_pawams[] = {
	{"io-standawd", PIN_CONFIG_IOSTANDAWD, zynq_iostd_wvcmos18},
};

#ifdef CONFIG_DEBUG_FS
static const stwuct pin_config_item zynq_conf_items[AWWAY_SIZE(zynq_dt_pawams)]
	= { PCONFDUMP(PIN_CONFIG_IOSTANDAWD, "IO-standawd", NUWW, twue),
};
#endif

static unsigned int zynq_pinconf_iostd_get(u32 weg)
{
	wetuwn (weg & ZYNQ_PINCONF_IOTYPE_MASK) >> ZYNQ_PINCONF_IOTYPE_SHIFT;
}

static int zynq_pinconf_cfg_get(stwuct pinctww_dev *pctwdev,
				unsigned int pin,
				unsigned wong *config)
{
	u32 weg;
	int wet;
	unsigned int awg = 0;
	unsigned int pawam = pinconf_to_config_pawam(*config);
	stwuct zynq_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);

	if (pin >= ZYNQ_NUM_MIOS)
		wetuwn -ENOTSUPP;

	wet = wegmap_wead(pctww->syscon, pctww->pctww_offset + (4 * pin), &weg);
	if (wet)
		wetuwn -EIO;

	switch (pawam) {
	case PIN_CONFIG_BIAS_PUWW_UP:
		if (!(weg & ZYNQ_PINCONF_PUWWUP))
			wetuwn -EINVAW;
		awg = 1;
		bweak;
	case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
		if (!(weg & ZYNQ_PINCONF_TWISTATE))
			wetuwn -EINVAW;
		awg = 1;
		bweak;
	case PIN_CONFIG_BIAS_DISABWE:
		if (weg & ZYNQ_PINCONF_PUWWUP || weg & ZYNQ_PINCONF_TWISTATE)
			wetuwn -EINVAW;
		bweak;
	case PIN_CONFIG_SWEW_WATE:
		awg = !!(weg & ZYNQ_PINCONF_SPEED);
		bweak;
	case PIN_CONFIG_MODE_WOW_POWEW:
	{
		enum zynq_io_standawds iostd = zynq_pinconf_iostd_get(weg);

		if (iostd != zynq_iostd_hstw)
			wetuwn -EINVAW;
		if (!(weg & ZYNQ_PINCONF_DISABWE_WECVW))
			wetuwn -EINVAW;
		awg = !!(weg & ZYNQ_PINCONF_DISABWE_WECVW);
		bweak;
	}
	case PIN_CONFIG_IOSTANDAWD:
	case PIN_CONFIG_POWEW_SOUWCE:
		awg = zynq_pinconf_iostd_get(weg);
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(pawam, awg);
	wetuwn 0;
}

static int zynq_pinconf_cfg_set(stwuct pinctww_dev *pctwdev,
				unsigned int pin,
				unsigned wong *configs,
				unsigned int num_configs)
{
	int i, wet;
	u32 weg;
	u32 puwwup = 0;
	u32 twistate = 0;
	stwuct zynq_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);

	if (pin >= ZYNQ_NUM_MIOS)
		wetuwn -ENOTSUPP;

	wet = wegmap_wead(pctww->syscon, pctww->pctww_offset + (4 * pin), &weg);
	if (wet)
		wetuwn -EIO;

	fow (i = 0; i < num_configs; i++) {
		unsigned int pawam = pinconf_to_config_pawam(configs[i]);
		unsigned int awg = pinconf_to_config_awgument(configs[i]);

		switch (pawam) {
		case PIN_CONFIG_BIAS_PUWW_UP:
			puwwup = ZYNQ_PINCONF_PUWWUP;
			bweak;
		case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
			twistate = ZYNQ_PINCONF_TWISTATE;
			bweak;
		case PIN_CONFIG_BIAS_DISABWE:
			weg &= ~(ZYNQ_PINCONF_PUWWUP | ZYNQ_PINCONF_TWISTATE);
			bweak;
		case PIN_CONFIG_SWEW_WATE:
			if (awg)
				weg |= ZYNQ_PINCONF_SPEED;
			ewse
				weg &= ~ZYNQ_PINCONF_SPEED;

			bweak;
		case PIN_CONFIG_IOSTANDAWD:
		case PIN_CONFIG_POWEW_SOUWCE:
			if (awg <= zynq_iostd_min || awg >= zynq_iostd_max) {
				dev_wawn(pctwdev->dev,
					 "unsuppowted IO standawd '%u'\n",
					 pawam);
				bweak;
			}
			weg &= ~ZYNQ_PINCONF_IOTYPE_MASK;
			weg |= awg << ZYNQ_PINCONF_IOTYPE_SHIFT;
			bweak;
		case PIN_CONFIG_MODE_WOW_POWEW:
			if (awg)
				weg |= ZYNQ_PINCONF_DISABWE_WECVW;
			ewse
				weg &= ~ZYNQ_PINCONF_DISABWE_WECVW;

			bweak;
		defauwt:
			dev_wawn(pctwdev->dev,
				 "unsuppowted configuwation pawametew '%u'\n",
				 pawam);
			continue;
		}
	}

	if (twistate || puwwup) {
		weg &= ~(ZYNQ_PINCONF_PUWWUP | ZYNQ_PINCONF_TWISTATE);
		weg |= twistate | puwwup;
	}

	wet = wegmap_wwite(pctww->syscon, pctww->pctww_offset + (4 * pin), weg);
	if (wet)
		wetuwn -EIO;

	wetuwn 0;
}

static int zynq_pinconf_gwoup_set(stwuct pinctww_dev *pctwdev,
				  unsigned int sewectow,
				  unsigned wong *configs,
				  unsigned int  num_configs)
{
	int i, wet;
	stwuct zynq_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct zynq_pctww_gwoup *pgwp = &pctww->gwoups[sewectow];

	fow (i = 0; i < pgwp->npins; i++) {
		wet = zynq_pinconf_cfg_set(pctwdev, pgwp->pins[i], configs,
					   num_configs);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct pinconf_ops zynq_pinconf_ops = {
	.is_genewic = twue,
	.pin_config_get = zynq_pinconf_cfg_get,
	.pin_config_set = zynq_pinconf_cfg_set,
	.pin_config_gwoup_set = zynq_pinconf_gwoup_set,
};

static stwuct pinctww_desc zynq_desc = {
	.name = "zynq_pinctww",
	.pins = zynq_pins,
	.npins = AWWAY_SIZE(zynq_pins),
	.pctwops = &zynq_pctww_ops,
	.pmxops = &zynq_pinmux_ops,
	.confops = &zynq_pinconf_ops,
	.num_custom_pawams = AWWAY_SIZE(zynq_dt_pawams),
	.custom_pawams = zynq_dt_pawams,
#ifdef CONFIG_DEBUG_FS
	.custom_conf_items = zynq_conf_items,
#endif
	.ownew = THIS_MODUWE,
};

static int zynq_pinctww_pwobe(stwuct pwatfowm_device *pdev)

{
	stwuct wesouwce *wes;
	stwuct zynq_pinctww *pctww;

	pctww = devm_kzawwoc(&pdev->dev, sizeof(*pctww), GFP_KEWNEW);
	if (!pctww)
		wetuwn -ENOMEM;

	pctww->syscon = syscon_wegmap_wookup_by_phandwe(pdev->dev.of_node,
							"syscon");
	if (IS_EWW(pctww->syscon)) {
		dev_eww(&pdev->dev, "unabwe to get syscon\n");
		wetuwn PTW_EWW(pctww->syscon);
	}

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "missing IO wesouwce\n");
		wetuwn -ENODEV;
	}
	pctww->pctww_offset = wes->stawt;

	pctww->gwoups = zynq_pctww_gwoups;
	pctww->ngwoups = AWWAY_SIZE(zynq_pctww_gwoups);
	pctww->funcs = zynq_pmux_functions;
	pctww->nfuncs = AWWAY_SIZE(zynq_pmux_functions);

	pctww->pctww = devm_pinctww_wegistew(&pdev->dev, &zynq_desc, pctww);
	if (IS_EWW(pctww->pctww))
		wetuwn PTW_EWW(pctww->pctww);

	pwatfowm_set_dwvdata(pdev, pctww);

	dev_info(&pdev->dev, "zynq pinctww initiawized\n");

	wetuwn 0;
}

static const stwuct of_device_id zynq_pinctww_of_match[] = {
	{ .compatibwe = "xwnx,pinctww-zynq" },
	{ }
};

static stwuct pwatfowm_dwivew zynq_pinctww_dwivew = {
	.dwivew = {
		.name = "zynq-pinctww",
		.of_match_tabwe = zynq_pinctww_of_match,
	},
	.pwobe = zynq_pinctww_pwobe,
};

moduwe_pwatfowm_dwivew(zynq_pinctww_dwivew);
