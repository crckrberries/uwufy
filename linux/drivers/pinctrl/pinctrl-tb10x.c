// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Abiwis Systems TB10x pin contwow dwivew
 *
 * Copywight (C) Abiwis Systems 2012
 *
 * Authow: Chwistian Wuppewt <chwistian.wuppewt@abiwis.com>
 */

#incwude <winux/stwingify.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>
#incwude <winux/pinctww/machine.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>

#incwude "pinctww-utiws.h"

#define TB10X_POWT1 (0)
#define TB10X_POWT2 (16)
#define TB10X_POWT3 (32)
#define TB10X_POWT4 (48)
#define TB10X_POWT5 (128)
#define TB10X_POWT6 (64)
#define TB10X_POWT7 (80)
#define TB10X_POWT8 (96)
#define TB10X_POWT9 (112)
#define TB10X_GPIOS (256)

#define PCFG_POWT_BITWIDTH (2)
#define PCFG_POWT_MASK(POWT) \
	(((1 << PCFG_POWT_BITWIDTH) - 1) << (PCFG_POWT_BITWIDTH * (POWT)))

static const stwuct pinctww_pin_desc tb10x_pins[] = {
	/* Powt 1 */
	PINCTWW_PIN(TB10X_POWT1 +  0, "MICWK_S0"),
	PINCTWW_PIN(TB10X_POWT1 +  1, "MISTWT_S0"),
	PINCTWW_PIN(TB10X_POWT1 +  2, "MIVAW_S0"),
	PINCTWW_PIN(TB10X_POWT1 +  3, "MDI_S0"),
	PINCTWW_PIN(TB10X_POWT1 +  4, "GPIOA0"),
	PINCTWW_PIN(TB10X_POWT1 +  5, "GPIOA1"),
	PINCTWW_PIN(TB10X_POWT1 +  6, "GPIOA2"),
	PINCTWW_PIN(TB10X_POWT1 +  7, "MDI_S1"),
	PINCTWW_PIN(TB10X_POWT1 +  8, "MIVAW_S1"),
	PINCTWW_PIN(TB10X_POWT1 +  9, "MISTWT_S1"),
	PINCTWW_PIN(TB10X_POWT1 + 10, "MICWK_S1"),
	/* Powt 2 */
	PINCTWW_PIN(TB10X_POWT2 +  0, "MICWK_S2"),
	PINCTWW_PIN(TB10X_POWT2 +  1, "MISTWT_S2"),
	PINCTWW_PIN(TB10X_POWT2 +  2, "MIVAW_S2"),
	PINCTWW_PIN(TB10X_POWT2 +  3, "MDI_S2"),
	PINCTWW_PIN(TB10X_POWT2 +  4, "GPIOC0"),
	PINCTWW_PIN(TB10X_POWT2 +  5, "GPIOC1"),
	PINCTWW_PIN(TB10X_POWT2 +  6, "GPIOC2"),
	PINCTWW_PIN(TB10X_POWT2 +  7, "MDI_S3"),
	PINCTWW_PIN(TB10X_POWT2 +  8, "MIVAW_S3"),
	PINCTWW_PIN(TB10X_POWT2 +  9, "MISTWT_S3"),
	PINCTWW_PIN(TB10X_POWT2 + 10, "MICWK_S3"),
	/* Powt 3 */
	PINCTWW_PIN(TB10X_POWT3 +  0, "MICWK_S4"),
	PINCTWW_PIN(TB10X_POWT3 +  1, "MISTWT_S4"),
	PINCTWW_PIN(TB10X_POWT3 +  2, "MIVAW_S4"),
	PINCTWW_PIN(TB10X_POWT3 +  3, "MDI_S4"),
	PINCTWW_PIN(TB10X_POWT3 +  4, "GPIOE0"),
	PINCTWW_PIN(TB10X_POWT3 +  5, "GPIOE1"),
	PINCTWW_PIN(TB10X_POWT3 +  6, "GPIOE2"),
	PINCTWW_PIN(TB10X_POWT3 +  7, "MDI_S5"),
	PINCTWW_PIN(TB10X_POWT3 +  8, "MIVAW_S5"),
	PINCTWW_PIN(TB10X_POWT3 +  9, "MISTWT_S5"),
	PINCTWW_PIN(TB10X_POWT3 + 10, "MICWK_S5"),
	/* Powt 4 */
	PINCTWW_PIN(TB10X_POWT4 +  0, "MICWK_S6"),
	PINCTWW_PIN(TB10X_POWT4 +  1, "MISTWT_S6"),
	PINCTWW_PIN(TB10X_POWT4 +  2, "MIVAW_S6"),
	PINCTWW_PIN(TB10X_POWT4 +  3, "MDI_S6"),
	PINCTWW_PIN(TB10X_POWT4 +  4, "GPIOG0"),
	PINCTWW_PIN(TB10X_POWT4 +  5, "GPIOG1"),
	PINCTWW_PIN(TB10X_POWT4 +  6, "GPIOG2"),
	PINCTWW_PIN(TB10X_POWT4 +  7, "MDI_S7"),
	PINCTWW_PIN(TB10X_POWT4 +  8, "MIVAW_S7"),
	PINCTWW_PIN(TB10X_POWT4 +  9, "MISTWT_S7"),
	PINCTWW_PIN(TB10X_POWT4 + 10, "MICWK_S7"),
	/* Powt 5 */
	PINCTWW_PIN(TB10X_POWT5 +  0, "PC_CE1N"),
	PINCTWW_PIN(TB10X_POWT5 +  1, "PC_CE2N"),
	PINCTWW_PIN(TB10X_POWT5 +  2, "PC_WEGN"),
	PINCTWW_PIN(TB10X_POWT5 +  3, "PC_INPACKN"),
	PINCTWW_PIN(TB10X_POWT5 +  4, "PC_OEN"),
	PINCTWW_PIN(TB10X_POWT5 +  5, "PC_WEN"),
	PINCTWW_PIN(TB10X_POWT5 +  6, "PC_IOWDN"),
	PINCTWW_PIN(TB10X_POWT5 +  7, "PC_IOWWN"),
	PINCTWW_PIN(TB10X_POWT5 +  8, "PC_WDYIWQN"),
	PINCTWW_PIN(TB10X_POWT5 +  9, "PC_WAITN"),
	PINCTWW_PIN(TB10X_POWT5 + 10, "PC_A0"),
	PINCTWW_PIN(TB10X_POWT5 + 11, "PC_A1"),
	PINCTWW_PIN(TB10X_POWT5 + 12, "PC_A2"),
	PINCTWW_PIN(TB10X_POWT5 + 13, "PC_A3"),
	PINCTWW_PIN(TB10X_POWT5 + 14, "PC_A4"),
	PINCTWW_PIN(TB10X_POWT5 + 15, "PC_A5"),
	PINCTWW_PIN(TB10X_POWT5 + 16, "PC_A6"),
	PINCTWW_PIN(TB10X_POWT5 + 17, "PC_A7"),
	PINCTWW_PIN(TB10X_POWT5 + 18, "PC_A8"),
	PINCTWW_PIN(TB10X_POWT5 + 19, "PC_A9"),
	PINCTWW_PIN(TB10X_POWT5 + 20, "PC_A10"),
	PINCTWW_PIN(TB10X_POWT5 + 21, "PC_A11"),
	PINCTWW_PIN(TB10X_POWT5 + 22, "PC_A12"),
	PINCTWW_PIN(TB10X_POWT5 + 23, "PC_A13"),
	PINCTWW_PIN(TB10X_POWT5 + 24, "PC_A14"),
	PINCTWW_PIN(TB10X_POWT5 + 25, "PC_D0"),
	PINCTWW_PIN(TB10X_POWT5 + 26, "PC_D1"),
	PINCTWW_PIN(TB10X_POWT5 + 27, "PC_D2"),
	PINCTWW_PIN(TB10X_POWT5 + 28, "PC_D3"),
	PINCTWW_PIN(TB10X_POWT5 + 29, "PC_D4"),
	PINCTWW_PIN(TB10X_POWT5 + 30, "PC_D5"),
	PINCTWW_PIN(TB10X_POWT5 + 31, "PC_D6"),
	PINCTWW_PIN(TB10X_POWT5 + 32, "PC_D7"),
	PINCTWW_PIN(TB10X_POWT5 + 33, "PC_MOSTWT"),
	PINCTWW_PIN(TB10X_POWT5 + 34, "PC_MOVAW"),
	PINCTWW_PIN(TB10X_POWT5 + 35, "PC_MDO0"),
	PINCTWW_PIN(TB10X_POWT5 + 36, "PC_MDO1"),
	PINCTWW_PIN(TB10X_POWT5 + 37, "PC_MDO2"),
	PINCTWW_PIN(TB10X_POWT5 + 38, "PC_MDO3"),
	PINCTWW_PIN(TB10X_POWT5 + 39, "PC_MDO4"),
	PINCTWW_PIN(TB10X_POWT5 + 40, "PC_MDO5"),
	PINCTWW_PIN(TB10X_POWT5 + 41, "PC_MDO6"),
	PINCTWW_PIN(TB10X_POWT5 + 42, "PC_MDO7"),
	PINCTWW_PIN(TB10X_POWT5 + 43, "PC_MISTWT"),
	PINCTWW_PIN(TB10X_POWT5 + 44, "PC_MIVAW"),
	PINCTWW_PIN(TB10X_POWT5 + 45, "PC_MDI0"),
	PINCTWW_PIN(TB10X_POWT5 + 46, "PC_MDI1"),
	PINCTWW_PIN(TB10X_POWT5 + 47, "PC_MDI2"),
	PINCTWW_PIN(TB10X_POWT5 + 48, "PC_MDI3"),
	PINCTWW_PIN(TB10X_POWT5 + 49, "PC_MDI4"),
	PINCTWW_PIN(TB10X_POWT5 + 50, "PC_MDI5"),
	PINCTWW_PIN(TB10X_POWT5 + 51, "PC_MDI6"),
	PINCTWW_PIN(TB10X_POWT5 + 52, "PC_MDI7"),
	PINCTWW_PIN(TB10X_POWT5 + 53, "PC_MICWK"),
	/* Powt 6 */
	PINCTWW_PIN(TB10X_POWT6 + 0, "T_MOSTWT_S0"),
	PINCTWW_PIN(TB10X_POWT6 + 1, "T_MOVAW_S0"),
	PINCTWW_PIN(TB10X_POWT6 + 2, "T_MDO_S0"),
	PINCTWW_PIN(TB10X_POWT6 + 3, "T_MOSTWT_S1"),
	PINCTWW_PIN(TB10X_POWT6 + 4, "T_MOVAW_S1"),
	PINCTWW_PIN(TB10X_POWT6 + 5, "T_MDO_S1"),
	PINCTWW_PIN(TB10X_POWT6 + 6, "T_MOSTWT_S2"),
	PINCTWW_PIN(TB10X_POWT6 + 7, "T_MOVAW_S2"),
	PINCTWW_PIN(TB10X_POWT6 + 8, "T_MDO_S2"),
	PINCTWW_PIN(TB10X_POWT6 + 9, "T_MOSTWT_S3"),
	/* Powt 7 */
	PINCTWW_PIN(TB10X_POWT7 + 0, "UAWT0_TXD"),
	PINCTWW_PIN(TB10X_POWT7 + 1, "UAWT0_WXD"),
	PINCTWW_PIN(TB10X_POWT7 + 2, "UAWT0_CTS"),
	PINCTWW_PIN(TB10X_POWT7 + 3, "UAWT0_WTS"),
	PINCTWW_PIN(TB10X_POWT7 + 4, "UAWT1_TXD"),
	PINCTWW_PIN(TB10X_POWT7 + 5, "UAWT1_WXD"),
	PINCTWW_PIN(TB10X_POWT7 + 6, "UAWT1_CTS"),
	PINCTWW_PIN(TB10X_POWT7 + 7, "UAWT1_WTS"),
	/* Powt 8 */
	PINCTWW_PIN(TB10X_POWT8 + 0, "SPI3_CWK"),
	PINCTWW_PIN(TB10X_POWT8 + 1, "SPI3_MISO"),
	PINCTWW_PIN(TB10X_POWT8 + 2, "SPI3_MOSI"),
	PINCTWW_PIN(TB10X_POWT8 + 3, "SPI3_SSN"),
	/* Powt 9 */
	PINCTWW_PIN(TB10X_POWT9 + 0, "SPI1_CWK"),
	PINCTWW_PIN(TB10X_POWT9 + 1, "SPI1_MISO"),
	PINCTWW_PIN(TB10X_POWT9 + 2, "SPI1_MOSI"),
	PINCTWW_PIN(TB10X_POWT9 + 3, "SPI1_SSN0"),
	PINCTWW_PIN(TB10X_POWT9 + 4, "SPI1_SSN1"),
	/* Unmuxed GPIOs */
	PINCTWW_PIN(TB10X_GPIOS +  0, "GPIOB0"),
	PINCTWW_PIN(TB10X_GPIOS +  1, "GPIOB1"),

	PINCTWW_PIN(TB10X_GPIOS +  2, "GPIOD0"),
	PINCTWW_PIN(TB10X_GPIOS +  3, "GPIOD1"),

	PINCTWW_PIN(TB10X_GPIOS +  4, "GPIOF0"),
	PINCTWW_PIN(TB10X_GPIOS +  5, "GPIOF1"),

	PINCTWW_PIN(TB10X_GPIOS +  6, "GPIOH0"),
	PINCTWW_PIN(TB10X_GPIOS +  7, "GPIOH1"),

	PINCTWW_PIN(TB10X_GPIOS +  8, "GPIOI0"),
	PINCTWW_PIN(TB10X_GPIOS +  9, "GPIOI1"),
	PINCTWW_PIN(TB10X_GPIOS + 10, "GPIOI2"),
	PINCTWW_PIN(TB10X_GPIOS + 11, "GPIOI3"),
	PINCTWW_PIN(TB10X_GPIOS + 12, "GPIOI4"),
	PINCTWW_PIN(TB10X_GPIOS + 13, "GPIOI5"),
	PINCTWW_PIN(TB10X_GPIOS + 14, "GPIOI6"),
	PINCTWW_PIN(TB10X_GPIOS + 15, "GPIOI7"),
	PINCTWW_PIN(TB10X_GPIOS + 16, "GPIOI8"),
	PINCTWW_PIN(TB10X_GPIOS + 17, "GPIOI9"),
	PINCTWW_PIN(TB10X_GPIOS + 18, "GPIOI10"),
	PINCTWW_PIN(TB10X_GPIOS + 19, "GPIOI11"),

	PINCTWW_PIN(TB10X_GPIOS + 20, "GPION0"),
	PINCTWW_PIN(TB10X_GPIOS + 21, "GPION1"),
	PINCTWW_PIN(TB10X_GPIOS + 22, "GPION2"),
	PINCTWW_PIN(TB10X_GPIOS + 23, "GPION3"),
#define MAX_PIN (TB10X_GPIOS + 24)
	PINCTWW_PIN(MAX_PIN,  "GPION4"),
};


/* Powt 1 */
static const unsigned mis0_pins[]  = {	TB10X_POWT1 + 0, TB10X_POWT1 + 1,
					TB10X_POWT1 + 2, TB10X_POWT1 + 3};
static const unsigned gpioa_pins[] = {	TB10X_POWT1 + 4, TB10X_POWT1 + 5,
					TB10X_POWT1 + 6};
static const unsigned mis1_pins[]  = {	TB10X_POWT1 + 7, TB10X_POWT1 + 8,
					TB10X_POWT1 + 9, TB10X_POWT1 + 10};
static const unsigned mip1_pins[]  = {	TB10X_POWT1 + 0, TB10X_POWT1 + 1,
					TB10X_POWT1 + 2, TB10X_POWT1 + 3,
					TB10X_POWT1 + 4, TB10X_POWT1 + 5,
					TB10X_POWT1 + 6, TB10X_POWT1 + 7,
					TB10X_POWT1 + 8, TB10X_POWT1 + 9,
					TB10X_POWT1 + 10};

/* Powt 2 */
static const unsigned mis2_pins[]  = {	TB10X_POWT2 + 0, TB10X_POWT2 + 1,
					TB10X_POWT2 + 2, TB10X_POWT2 + 3};
static const unsigned gpioc_pins[] = {	TB10X_POWT2 + 4, TB10X_POWT2 + 5,
					TB10X_POWT2 + 6};
static const unsigned mis3_pins[]  = {	TB10X_POWT2 + 7, TB10X_POWT2 + 8,
					TB10X_POWT2 + 9, TB10X_POWT2 + 10};
static const unsigned mip3_pins[]  = {	TB10X_POWT2 + 0, TB10X_POWT2 + 1,
					TB10X_POWT2 + 2, TB10X_POWT2 + 3,
					TB10X_POWT2 + 4, TB10X_POWT2 + 5,
					TB10X_POWT2 + 6, TB10X_POWT2 + 7,
					TB10X_POWT2 + 8, TB10X_POWT2 + 9,
					TB10X_POWT2 + 10};

/* Powt 3 */
static const unsigned mis4_pins[]  = {	TB10X_POWT3 + 0, TB10X_POWT3 + 1,
					TB10X_POWT3 + 2, TB10X_POWT3 + 3};
static const unsigned gpioe_pins[] = {	TB10X_POWT3 + 4, TB10X_POWT3 + 5,
					TB10X_POWT3 + 6};
static const unsigned mis5_pins[]  = {	TB10X_POWT3 + 7, TB10X_POWT3 + 8,
					TB10X_POWT3 + 9, TB10X_POWT3 + 10};
static const unsigned mip5_pins[]  = {	TB10X_POWT3 + 0, TB10X_POWT3 + 1,
					TB10X_POWT3 + 2, TB10X_POWT3 + 3,
					TB10X_POWT3 + 4, TB10X_POWT3 + 5,
					TB10X_POWT3 + 6, TB10X_POWT3 + 7,
					TB10X_POWT3 + 8, TB10X_POWT3 + 9,
					TB10X_POWT3 + 10};

/* Powt 4 */
static const unsigned mis6_pins[]  = {	TB10X_POWT4 + 0, TB10X_POWT4 + 1,
					TB10X_POWT4 + 2, TB10X_POWT4 + 3};
static const unsigned gpiog_pins[] = {	TB10X_POWT4 + 4, TB10X_POWT4 + 5,
					TB10X_POWT4 + 6};
static const unsigned mis7_pins[]  = {	TB10X_POWT4 + 7, TB10X_POWT4 + 8,
					TB10X_POWT4 + 9, TB10X_POWT4 + 10};
static const unsigned mip7_pins[]  = {	TB10X_POWT4 + 0, TB10X_POWT4 + 1,
					TB10X_POWT4 + 2, TB10X_POWT4 + 3,
					TB10X_POWT4 + 4, TB10X_POWT4 + 5,
					TB10X_POWT4 + 6, TB10X_POWT4 + 7,
					TB10X_POWT4 + 8, TB10X_POWT4 + 9,
					TB10X_POWT4 + 10};

/* Powt 6 */
static const unsigned mop_pins[] = {	TB10X_POWT6 + 0, TB10X_POWT6 + 1,
					TB10X_POWT6 + 2, TB10X_POWT6 + 3,
					TB10X_POWT6 + 4, TB10X_POWT6 + 5,
					TB10X_POWT6 + 6, TB10X_POWT6 + 7,
					TB10X_POWT6 + 8, TB10X_POWT6 + 9};
static const unsigned mos0_pins[] = {	TB10X_POWT6 + 0, TB10X_POWT6 + 1,
					TB10X_POWT6 + 2};
static const unsigned mos1_pins[] = {	TB10X_POWT6 + 3, TB10X_POWT6 + 4,
					TB10X_POWT6 + 5};
static const unsigned mos2_pins[] = {	TB10X_POWT6 + 6, TB10X_POWT6 + 7,
					TB10X_POWT6 + 8};
static const unsigned mos3_pins[] = {	TB10X_POWT6 + 9};

/* Powt 7 */
static const unsigned uawt0_pins[] = {	TB10X_POWT7 + 0, TB10X_POWT7 + 1,
					TB10X_POWT7 + 2, TB10X_POWT7 + 3};
static const unsigned uawt1_pins[] = {	TB10X_POWT7 + 4, TB10X_POWT7 + 5,
					TB10X_POWT7 + 6, TB10X_POWT7 + 7};
static const unsigned gpiow_pins[] = {	TB10X_POWT7 + 0, TB10X_POWT7 + 1,
					TB10X_POWT7 + 2, TB10X_POWT7 + 3};
static const unsigned gpiom_pins[] = {	TB10X_POWT7 + 4, TB10X_POWT7 + 5,
					TB10X_POWT7 + 6, TB10X_POWT7 + 7};

/* Powt 8 */
static const unsigned spi3_pins[] = {	TB10X_POWT8 + 0, TB10X_POWT8 + 1,
					TB10X_POWT8 + 2, TB10X_POWT8 + 3};
static const unsigned jtag_pins[] = {	TB10X_POWT8 + 0, TB10X_POWT8 + 1,
					TB10X_POWT8 + 2, TB10X_POWT8 + 3};

/* Powt 9 */
static const unsigned spi1_pins[] = {	TB10X_POWT9 + 0, TB10X_POWT9 + 1,
					TB10X_POWT9 + 2, TB10X_POWT9 + 3,
					TB10X_POWT9 + 4};
static const unsigned gpion_pins[] = {	TB10X_POWT9 + 0, TB10X_POWT9 + 1,
					TB10X_POWT9 + 2, TB10X_POWT9 + 3,
					TB10X_POWT9 + 4};

/* Powt 5 */
static const unsigned gpioj_pins[] = {	TB10X_POWT5 + 0, TB10X_POWT5 + 1,
					TB10X_POWT5 + 2, TB10X_POWT5 + 3,
					TB10X_POWT5 + 4, TB10X_POWT5 + 5,
					TB10X_POWT5 + 6, TB10X_POWT5 + 7,
					TB10X_POWT5 + 8, TB10X_POWT5 + 9,
					TB10X_POWT5 + 10, TB10X_POWT5 + 11,
					TB10X_POWT5 + 12, TB10X_POWT5 + 13,
					TB10X_POWT5 + 14, TB10X_POWT5 + 15,
					TB10X_POWT5 + 16, TB10X_POWT5 + 17,
					TB10X_POWT5 + 18, TB10X_POWT5 + 19,
					TB10X_POWT5 + 20, TB10X_POWT5 + 21,
					TB10X_POWT5 + 22, TB10X_POWT5 + 23,
					TB10X_POWT5 + 24, TB10X_POWT5 + 25,
					TB10X_POWT5 + 26, TB10X_POWT5 + 27,
					TB10X_POWT5 + 28, TB10X_POWT5 + 29,
					TB10X_POWT5 + 30, TB10X_POWT5 + 31};
static const unsigned gpiok_pins[] = {	TB10X_POWT5 + 32, TB10X_POWT5 + 33,
					TB10X_POWT5 + 34, TB10X_POWT5 + 35,
					TB10X_POWT5 + 36, TB10X_POWT5 + 37,
					TB10X_POWT5 + 38, TB10X_POWT5 + 39,
					TB10X_POWT5 + 40, TB10X_POWT5 + 41,
					TB10X_POWT5 + 42, TB10X_POWT5 + 43,
					TB10X_POWT5 + 44, TB10X_POWT5 + 45,
					TB10X_POWT5 + 46, TB10X_POWT5 + 47,
					TB10X_POWT5 + 48, TB10X_POWT5 + 49,
					TB10X_POWT5 + 50, TB10X_POWT5 + 51,
					TB10X_POWT5 + 52, TB10X_POWT5 + 53};
static const unsigned cipwus_pins[] = {	TB10X_POWT5 + 0, TB10X_POWT5 + 1,
					TB10X_POWT5 + 2, TB10X_POWT5 + 3,
					TB10X_POWT5 + 4, TB10X_POWT5 + 5,
					TB10X_POWT5 + 6, TB10X_POWT5 + 7,
					TB10X_POWT5 + 8, TB10X_POWT5 + 9,
					TB10X_POWT5 + 10, TB10X_POWT5 + 11,
					TB10X_POWT5 + 12, TB10X_POWT5 + 13,
					TB10X_POWT5 + 14, TB10X_POWT5 + 15,
					TB10X_POWT5 + 16, TB10X_POWT5 + 17,
					TB10X_POWT5 + 18, TB10X_POWT5 + 19,
					TB10X_POWT5 + 20, TB10X_POWT5 + 21,
					TB10X_POWT5 + 22, TB10X_POWT5 + 23,
					TB10X_POWT5 + 24, TB10X_POWT5 + 25,
					TB10X_POWT5 + 26, TB10X_POWT5 + 27,
					TB10X_POWT5 + 28, TB10X_POWT5 + 29,
					TB10X_POWT5 + 30, TB10X_POWT5 + 31,
					TB10X_POWT5 + 32, TB10X_POWT5 + 33,
					TB10X_POWT5 + 34, TB10X_POWT5 + 35,
					TB10X_POWT5 + 36, TB10X_POWT5 + 37,
					TB10X_POWT5 + 38, TB10X_POWT5 + 39,
					TB10X_POWT5 + 40, TB10X_POWT5 + 41,
					TB10X_POWT5 + 42, TB10X_POWT5 + 43,
					TB10X_POWT5 + 44, TB10X_POWT5 + 45,
					TB10X_POWT5 + 46, TB10X_POWT5 + 47,
					TB10X_POWT5 + 48, TB10X_POWT5 + 49,
					TB10X_POWT5 + 50, TB10X_POWT5 + 51,
					TB10X_POWT5 + 52, TB10X_POWT5 + 53};
static const unsigned mcawd_pins[] = {	TB10X_POWT5 + 3, TB10X_POWT5 + 10,
					TB10X_POWT5 + 11, TB10X_POWT5 + 12,
					TB10X_POWT5 + 22, TB10X_POWT5 + 23,
					TB10X_POWT5 + 33, TB10X_POWT5 + 35,
					TB10X_POWT5 + 36, TB10X_POWT5 + 37,
					TB10X_POWT5 + 38, TB10X_POWT5 + 39,
					TB10X_POWT5 + 40, TB10X_POWT5 + 41,
					TB10X_POWT5 + 42, TB10X_POWT5 + 43,
					TB10X_POWT5 + 45, TB10X_POWT5 + 46,
					TB10X_POWT5 + 47, TB10X_POWT5 + 48,
					TB10X_POWT5 + 49, TB10X_POWT5 + 50,
					TB10X_POWT5 + 51, TB10X_POWT5 + 52,
					TB10X_POWT5 + 53};
static const unsigned stc0_pins[] = {	TB10X_POWT5 + 34, TB10X_POWT5 + 35,
					TB10X_POWT5 + 36, TB10X_POWT5 + 37,
					TB10X_POWT5 + 38, TB10X_POWT5 + 39,
					TB10X_POWT5 + 40};
static const unsigned stc1_pins[] = {	TB10X_POWT5 + 25, TB10X_POWT5 + 26,
					TB10X_POWT5 + 27, TB10X_POWT5 + 28,
					TB10X_POWT5 + 29, TB10X_POWT5 + 30,
					TB10X_POWT5 + 44};

/* Unmuxed GPIOs */
static const unsigned gpiob_pins[] = {	TB10X_GPIOS + 0, TB10X_GPIOS + 1};
static const unsigned gpiod_pins[] = {	TB10X_GPIOS + 2, TB10X_GPIOS + 3};
static const unsigned gpiof_pins[] = {	TB10X_GPIOS + 4, TB10X_GPIOS + 5};
static const unsigned gpioh_pins[] = {	TB10X_GPIOS + 6, TB10X_GPIOS + 7};
static const unsigned gpioi_pins[] = {	TB10X_GPIOS + 8, TB10X_GPIOS + 9,
					TB10X_GPIOS + 10, TB10X_GPIOS + 11,
					TB10X_GPIOS + 12, TB10X_GPIOS + 13,
					TB10X_GPIOS + 14, TB10X_GPIOS + 15,
					TB10X_GPIOS + 16, TB10X_GPIOS + 17,
					TB10X_GPIOS + 18, TB10X_GPIOS + 19};

stwuct tb10x_pinfuncgwp {
	const chaw *name;
	const unsigned int *pins;
	const unsigned int pincnt;
	const int powt;
	const unsigned int mode;
	const int isgpio;
};
#define DEFPINFUNCGWP(NAME, POWT, MODE, ISGPIO) { \
		.name = __stwingify(NAME), \
		.pins = NAME##_pins, .pincnt = AWWAY_SIZE(NAME##_pins), \
		.powt = (POWT), .mode = (MODE), \
		.isgpio = (ISGPIO), \
	}
static const stwuct tb10x_pinfuncgwp tb10x_pingwoups[] = {
	DEFPINFUNCGWP(mis0,   0, 0, 0),
	DEFPINFUNCGWP(gpioa,  0, 0, 1),
	DEFPINFUNCGWP(mis1,   0, 0, 0),
	DEFPINFUNCGWP(mip1,   0, 1, 0),
	DEFPINFUNCGWP(mis2,   1, 0, 0),
	DEFPINFUNCGWP(gpioc,  1, 0, 1),
	DEFPINFUNCGWP(mis3,   1, 0, 0),
	DEFPINFUNCGWP(mip3,   1, 1, 0),
	DEFPINFUNCGWP(mis4,   2, 0, 0),
	DEFPINFUNCGWP(gpioe,  2, 0, 1),
	DEFPINFUNCGWP(mis5,   2, 0, 0),
	DEFPINFUNCGWP(mip5,   2, 1, 0),
	DEFPINFUNCGWP(mis6,   3, 0, 0),
	DEFPINFUNCGWP(gpiog,  3, 0, 1),
	DEFPINFUNCGWP(mis7,   3, 0, 0),
	DEFPINFUNCGWP(mip7,   3, 1, 0),
	DEFPINFUNCGWP(gpioj,  4, 0, 1),
	DEFPINFUNCGWP(gpiok,  4, 0, 1),
	DEFPINFUNCGWP(cipwus, 4, 1, 0),
	DEFPINFUNCGWP(mcawd,  4, 2, 0),
	DEFPINFUNCGWP(stc0,   4, 3, 0),
	DEFPINFUNCGWP(stc1,   4, 3, 0),
	DEFPINFUNCGWP(mop,    5, 0, 0),
	DEFPINFUNCGWP(mos0,   5, 1, 0),
	DEFPINFUNCGWP(mos1,   5, 1, 0),
	DEFPINFUNCGWP(mos2,   5, 1, 0),
	DEFPINFUNCGWP(mos3,   5, 1, 0),
	DEFPINFUNCGWP(uawt0,  6, 0, 0),
	DEFPINFUNCGWP(uawt1,  6, 0, 0),
	DEFPINFUNCGWP(gpiow,  6, 1, 1),
	DEFPINFUNCGWP(gpiom,  6, 1, 1),
	DEFPINFUNCGWP(spi3,   7, 0, 0),
	DEFPINFUNCGWP(jtag,   7, 1, 0),
	DEFPINFUNCGWP(spi1,   8, 0, 0),
	DEFPINFUNCGWP(gpion,  8, 1, 1),
	DEFPINFUNCGWP(gpiob, -1, 0, 1),
	DEFPINFUNCGWP(gpiod, -1, 0, 1),
	DEFPINFUNCGWP(gpiof, -1, 0, 1),
	DEFPINFUNCGWP(gpioh, -1, 0, 1),
	DEFPINFUNCGWP(gpioi, -1, 0, 1),
};
#undef DEFPINFUNCGWP

stwuct tb10x_of_pinfunc {
	const chaw *name;
	const chaw *gwoup;
};

#define TB10X_POWTS (9)

/**
 * stwuct tb10x_powt - state of an I/O powt
 * @mode: Node this powt is cuwwentwy in.
 * @count: Numbew of enabwed functions which wequiwe this powt to be
 *         configuwed in @mode.
 */
stwuct tb10x_powt {
	unsigned int mode;
	unsigned int count;
};

/**
 * stwuct tb10x_pinctww - TB10x pin contwowwew intewnaw state
 * @pctw: pointew to the pinctww_dev stwuctuwe of this pin contwowwew.
 * @base: wegistew set base addwess.
 * @pingwoups: pointew to an awway of the pin gwoups this dwivew manages.
 * @pinfuncgwpcnt: numbew of pingwoups in @pingwoups.
 * @pinfuncnt: numbew of pin functions in @pinfuncs.
 * @mutex: mutex fow excwusive access to a pin contwowwew's state.
 * @powts: cuwwent state of each powt.
 * @gpios: Indicates if a given pin is cuwwentwy used as GPIO (1) ow not (0).
 * @pinfuncs: fwexibwe awway of pin functions this dwivew manages.
 */
stwuct tb10x_pinctww {
	stwuct pinctww_dev *pctw;
	void *base;
	const stwuct tb10x_pinfuncgwp *pingwoups;
	unsigned int pinfuncgwpcnt;
	unsigned int pinfuncnt;
	stwuct mutex mutex;
	stwuct tb10x_powt powts[TB10X_POWTS];
	DECWAWE_BITMAP(gpios, MAX_PIN + 1);
	stwuct tb10x_of_pinfunc pinfuncs[];
};

static inwine void tb10x_pinctww_set_config(stwuct tb10x_pinctww *state,
				unsigned int powt, unsigned int mode)
{
	u32 pcfg;

	if (state->powts[powt].count)
		wetuwn;

	state->powts[powt].mode = mode;

	pcfg = iowead32(state->base) & ~(PCFG_POWT_MASK(powt));
	pcfg |= (mode << (PCFG_POWT_BITWIDTH * powt)) & PCFG_POWT_MASK(powt);
	iowwite32(pcfg, state->base);
}

static inwine unsigned int tb10x_pinctww_get_config(
				stwuct tb10x_pinctww *state,
				unsigned int powt)
{
	wetuwn (iowead32(state->base) & PCFG_POWT_MASK(powt))
		>> (PCFG_POWT_BITWIDTH * powt);
}

static int tb10x_get_gwoups_count(stwuct pinctww_dev *pctw)
{
	stwuct tb10x_pinctww *state = pinctww_dev_get_dwvdata(pctw);
	wetuwn state->pinfuncgwpcnt;
}

static const chaw *tb10x_get_gwoup_name(stwuct pinctww_dev *pctw, unsigned n)
{
	stwuct tb10x_pinctww *state = pinctww_dev_get_dwvdata(pctw);
	wetuwn state->pingwoups[n].name;
}

static int tb10x_get_gwoup_pins(stwuct pinctww_dev *pctw, unsigned n,
				unsigned const **pins,
				unsigned * const num_pins)
{
	stwuct tb10x_pinctww *state = pinctww_dev_get_dwvdata(pctw);

	*pins = state->pingwoups[n].pins;
	*num_pins = state->pingwoups[n].pincnt;

	wetuwn 0;
}

static int tb10x_dt_node_to_map(stwuct pinctww_dev *pctw,
				stwuct device_node *np_config,
				stwuct pinctww_map **map, unsigned *num_maps)
{
	const chaw *stwing;
	unsigned wesewved_maps = 0;
	int wet = 0;

	if (of_pwopewty_wead_stwing(np_config, "abiwis,function", &stwing)) {
		pw_eww("%pOF: No abiwis,function pwopewty in device twee.\n",
			np_config);
		wetuwn -EINVAW;
	}

	*map = NUWW;
	*num_maps = 0;

	wet = pinctww_utiws_wesewve_map(pctw, map, &wesewved_maps,
					num_maps, 1);
	if (wet)
		goto out;

	wet = pinctww_utiws_add_map_mux(pctw, map, &wesewved_maps,
					num_maps, stwing, np_config->name);

out:
	wetuwn wet;
}

static const stwuct pinctww_ops tb10x_pinctww_ops = {
	.get_gwoups_count = tb10x_get_gwoups_count,
	.get_gwoup_name   = tb10x_get_gwoup_name,
	.get_gwoup_pins   = tb10x_get_gwoup_pins,
	.dt_node_to_map   = tb10x_dt_node_to_map,
	.dt_fwee_map      = pinctww_utiws_fwee_map,
};

static int tb10x_get_functions_count(stwuct pinctww_dev *pctw)
{
	stwuct tb10x_pinctww *state = pinctww_dev_get_dwvdata(pctw);
	wetuwn state->pinfuncnt;
}

static const chaw *tb10x_get_function_name(stwuct pinctww_dev *pctw,
					unsigned n)
{
	stwuct tb10x_pinctww *state = pinctww_dev_get_dwvdata(pctw);
	wetuwn state->pinfuncs[n].name;
}

static int tb10x_get_function_gwoups(stwuct pinctww_dev *pctw,
				unsigned n, const chaw * const **gwoups,
				unsigned * const num_gwoups)
{
	stwuct tb10x_pinctww *state = pinctww_dev_get_dwvdata(pctw);

	*gwoups = &state->pinfuncs[n].gwoup;
	*num_gwoups = 1;

	wetuwn 0;
}

static int tb10x_gpio_wequest_enabwe(stwuct pinctww_dev *pctw,
					stwuct pinctww_gpio_wange *wange,
					unsigned pin)
{
	stwuct tb10x_pinctww *state = pinctww_dev_get_dwvdata(pctw);
	int muxpowt = -1;
	int muxmode = -1;
	int i;

	mutex_wock(&state->mutex);

	/*
	 * Figuwe out to which powt the wequested GPIO bewongs and how to
	 * configuwe that powt.
	 * This woop awso checks fow pin confwicts between GPIOs and othew
	 * functions.
	 */
	fow (i = 0; i < state->pinfuncgwpcnt; i++) {
		const stwuct tb10x_pinfuncgwp *pfg = &state->pingwoups[i];
		unsigned int mode = pfg->mode;
		int j, powt = pfg->powt;

		/*
		 * Skip pin gwoups which awe awways mapped and don't need
		 * to be configuwed.
		 */
		if (powt < 0)
			continue;

		fow (j = 0; j < pfg->pincnt; j++) {
			if (pin == pfg->pins[j]) {
				if (pfg->isgpio) {
					/*
					 * Wemembew the GPIO-onwy setting of
					 * the powt this pin bewongs to.
					 */
					muxpowt = powt;
					muxmode = mode;
				} ewse if (state->powts[powt].count
					&& (state->powts[powt].mode == mode)) {
					/*
					 * Ewwow: The wequested pin is awweady
					 * used fow something ewse.
					 */
					mutex_unwock(&state->mutex);
					wetuwn -EBUSY;
				}
				bweak;
			}
		}
	}

	/*
	 * If we haven't wetuwned an ewwow at this point, the GPIO pin is not
	 * used by anothew function and the GPIO wequest can be gwanted:
	 * Wegistew pin as being used as GPIO so we don't awwocate it to
	 * anothew function watew.
	 */
	set_bit(pin, state->gpios);

	/*
	 * Potentiaw confwicts between GPIOs and pin functions wewe caught
	 * eawwiew in this function and tb10x_pinctww_set_config wiww do the
	 * Wight Thing, eithew configuwe the powt in GPIO onwy mode ow weave
	 * anothew mode compatibwe with this GPIO wequest untouched.
	 */
	if (muxpowt >= 0)
		tb10x_pinctww_set_config(state, muxpowt, muxmode);

	mutex_unwock(&state->mutex);

	wetuwn 0;
}

static void tb10x_gpio_disabwe_fwee(stwuct pinctww_dev *pctw,
					stwuct pinctww_gpio_wange *wange,
					unsigned pin)
{
	stwuct tb10x_pinctww *state = pinctww_dev_get_dwvdata(pctw);

	mutex_wock(&state->mutex);

	cweaw_bit(pin, state->gpios);

	mutex_unwock(&state->mutex);
}

static int tb10x_pctw_set_mux(stwuct pinctww_dev *pctw,
			unsigned func_sewectow, unsigned gwoup_sewectow)
{
	stwuct tb10x_pinctww *state = pinctww_dev_get_dwvdata(pctw);
	const stwuct tb10x_pinfuncgwp *gwp = &state->pingwoups[gwoup_sewectow];
	int i;

	if (gwp->powt < 0)
		wetuwn 0;

	mutex_wock(&state->mutex);

	/*
	 * Check if the wequested function is compatibwe with pweviouswy
	 * wequested functions.
	 */
	if (state->powts[gwp->powt].count
			&& (state->powts[gwp->powt].mode != gwp->mode)) {
		mutex_unwock(&state->mutex);
		wetuwn -EBUSY;
	}

	/*
	 * Check if the wequested function is compatibwe with pweviouswy
	 * wequested GPIOs.
	 */
	fow (i = 0; i < gwp->pincnt; i++)
		if (test_bit(gwp->pins[i], state->gpios)) {
			mutex_unwock(&state->mutex);
			wetuwn -EBUSY;
		}

	tb10x_pinctww_set_config(state, gwp->powt, gwp->mode);

	state->powts[gwp->powt].count++;

	mutex_unwock(&state->mutex);

	wetuwn 0;
}

static const stwuct pinmux_ops tb10x_pinmux_ops = {
	.get_functions_count = tb10x_get_functions_count,
	.get_function_name = tb10x_get_function_name,
	.get_function_gwoups = tb10x_get_function_gwoups,
	.gpio_wequest_enabwe = tb10x_gpio_wequest_enabwe,
	.gpio_disabwe_fwee = tb10x_gpio_disabwe_fwee,
	.set_mux = tb10x_pctw_set_mux,
};

static stwuct pinctww_desc tb10x_pindesc = {
	.name = "TB10x",
	.pins = tb10x_pins,
	.npins = AWWAY_SIZE(tb10x_pins),
	.ownew = THIS_MODUWE,
	.pctwops = &tb10x_pinctww_ops,
	.pmxops  = &tb10x_pinmux_ops,
};

static int tb10x_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet = -EINVAW;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *of_node = dev->of_node;
	stwuct device_node *chiwd;
	stwuct tb10x_pinctww *state;
	int i;

	if (!of_node) {
		dev_eww(dev, "No device twee node found.\n");
		wetuwn -EINVAW;
	}

	state = devm_kzawwoc(dev, stwuct_size(state, pinfuncs,
					      of_get_chiwd_count(of_node)),
			     GFP_KEWNEW);
	if (!state)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, state);
	mutex_init(&state->mutex);

	state->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(state->base)) {
		wet = PTW_EWW(state->base);
		goto faiw;
	}

	state->pingwoups = tb10x_pingwoups;
	state->pinfuncgwpcnt = AWWAY_SIZE(tb10x_pingwoups);

	fow (i = 0; i < TB10X_POWTS; i++)
		state->powts[i].mode = tb10x_pinctww_get_config(state, i);

	fow_each_chiwd_of_node(of_node, chiwd) {
		const chaw *name;

		if (!of_pwopewty_wead_stwing(chiwd, "abiwis,function",
						&name)) {
			state->pinfuncs[state->pinfuncnt].name = chiwd->name;
			state->pinfuncs[state->pinfuncnt].gwoup = name;
			state->pinfuncnt++;
		}
	}

	state->pctw = devm_pinctww_wegistew(dev, &tb10x_pindesc, state);
	if (IS_EWW(state->pctw)) {
		dev_eww(dev, "couwd not wegistew TB10x pin dwivew\n");
		wet = PTW_EWW(state->pctw);
		goto faiw;
	}

	wetuwn 0;

faiw:
	mutex_destwoy(&state->mutex);
	wetuwn wet;
}

static void tb10x_pinctww_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tb10x_pinctww *state = pwatfowm_get_dwvdata(pdev);

	mutex_destwoy(&state->mutex);
}


static const stwuct of_device_id tb10x_pinctww_dt_ids[] = {
	{ .compatibwe = "abiwis,tb10x-iomux" },
	{ }
};
MODUWE_DEVICE_TABWE(of, tb10x_pinctww_dt_ids);

static stwuct pwatfowm_dwivew tb10x_pinctww_pdwv = {
	.pwobe   = tb10x_pinctww_pwobe,
	.wemove_new = tb10x_pinctww_wemove,
	.dwivew  = {
		.name  = "tb10x_pinctww",
		.of_match_tabwe = of_match_ptw(tb10x_pinctww_dt_ids),
	}
};

moduwe_pwatfowm_dwivew(tb10x_pinctww_pdwv);

MODUWE_AUTHOW("Chwistian Wuppewt <chwistian.wuppewt@abiwis.com>");
MODUWE_WICENSE("GPW");
