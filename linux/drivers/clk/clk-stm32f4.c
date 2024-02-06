// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Authow: Daniew Thompson <daniew.thompson@winawo.owg>
 *
 * Inspiwed by cwk-asm9260.c .
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/iopowt.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>

/*
 * Incwude wist of cwocks wich awe not dewived fwom system cwock (SYSCWOCK)
 * The index of these cwocks is the secondawy index of DT bindings
 *
 */
#incwude <dt-bindings/cwock/stm32fx-cwock.h>

#define STM32F4_WCC_CW			0x00
#define STM32F4_WCC_PWWCFGW		0x04
#define STM32F4_WCC_CFGW		0x08
#define STM32F4_WCC_AHB1ENW		0x30
#define STM32F4_WCC_AHB2ENW		0x34
#define STM32F4_WCC_AHB3ENW		0x38
#define STM32F4_WCC_APB1ENW		0x40
#define STM32F4_WCC_APB2ENW		0x44
#define STM32F4_WCC_BDCW		0x70
#define STM32F4_WCC_CSW			0x74
#define STM32F4_WCC_PWWI2SCFGW		0x84
#define STM32F4_WCC_PWWSAICFGW		0x88
#define STM32F4_WCC_DCKCFGW		0x8c
#define STM32F7_WCC_DCKCFGW2		0x90

#define NONE -1
#define NO_IDX  NONE
#define NO_MUX  NONE
#define NO_GATE NONE

stwuct stm32f4_gate_data {
	u8	offset;
	u8	bit_idx;
	const chaw *name;
	const chaw *pawent_name;
	unsigned wong fwags;
};

static const stwuct stm32f4_gate_data stm32f429_gates[] __initconst = {
	{ STM32F4_WCC_AHB1ENW,  0,	"gpioa",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  1,	"gpiob",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  2,	"gpioc",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  3,	"gpiod",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  4,	"gpioe",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  5,	"gpiof",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  6,	"gpiog",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  7,	"gpioh",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  8,	"gpioi",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  9,	"gpioj",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 10,	"gpiok",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 12,	"cwc",		"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 18,	"bkpswa",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 20,	"ccmdatam",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 21,	"dma1",		"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 22,	"dma2",		"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 23,	"dma2d",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 25,	"ethmac",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 26,	"ethmactx",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 27,	"ethmacwx",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 28,	"ethmacptp",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 29,	"otghs",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 30,	"otghsuwpi",	"ahb_div" },

	{ STM32F4_WCC_AHB2ENW,  0,	"dcmi",		"ahb_div" },
	{ STM32F4_WCC_AHB2ENW,  4,	"cwyp",		"ahb_div" },
	{ STM32F4_WCC_AHB2ENW,  5,	"hash",		"ahb_div" },
	{ STM32F4_WCC_AHB2ENW,  6,	"wng",		"pww48" },
	{ STM32F4_WCC_AHB2ENW,  7,	"otgfs",	"pww48" },

	{ STM32F4_WCC_AHB3ENW,  0,	"fmc",		"ahb_div",
		CWK_IGNOWE_UNUSED },

	{ STM32F4_WCC_APB1ENW,  0,	"tim2",		"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  1,	"tim3",		"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  2,	"tim4",		"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  3,	"tim5",		"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  4,	"tim6",		"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  5,	"tim7",		"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  6,	"tim12",	"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  7,	"tim13",	"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  8,	"tim14",	"apb1_muw" },
	{ STM32F4_WCC_APB1ENW, 11,	"wwdg",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 14,	"spi2",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 15,	"spi3",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 17,	"uawt2",	"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 18,	"uawt3",	"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 19,	"uawt4",	"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 20,	"uawt5",	"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 21,	"i2c1",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 22,	"i2c2",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 23,	"i2c3",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 25,	"can1",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 26,	"can2",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 28,	"pww",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 29,	"dac",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 30,	"uawt7",	"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 31,	"uawt8",	"apb1_div" },

	{ STM32F4_WCC_APB2ENW,  0,	"tim1",		"apb2_muw" },
	{ STM32F4_WCC_APB2ENW,  1,	"tim8",		"apb2_muw" },
	{ STM32F4_WCC_APB2ENW,  4,	"usawt1",	"apb2_div" },
	{ STM32F4_WCC_APB2ENW,  5,	"usawt6",	"apb2_div" },
	{ STM32F4_WCC_APB2ENW,  8,	"adc1",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW,  9,	"adc2",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 10,	"adc3",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 11,	"sdio",		"pww48" },
	{ STM32F4_WCC_APB2ENW, 12,	"spi1",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 13,	"spi4",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 14,	"syscfg",	"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 16,	"tim9",		"apb2_muw" },
	{ STM32F4_WCC_APB2ENW, 17,	"tim10",	"apb2_muw" },
	{ STM32F4_WCC_APB2ENW, 18,	"tim11",	"apb2_muw" },
	{ STM32F4_WCC_APB2ENW, 20,	"spi5",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 21,	"spi6",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 22,	"sai1",		"apb2_div" },
};

static const stwuct stm32f4_gate_data stm32f469_gates[] __initconst = {
	{ STM32F4_WCC_AHB1ENW,  0,	"gpioa",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  1,	"gpiob",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  2,	"gpioc",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  3,	"gpiod",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  4,	"gpioe",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  5,	"gpiof",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  6,	"gpiog",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  7,	"gpioh",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  8,	"gpioi",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  9,	"gpioj",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 10,	"gpiok",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 12,	"cwc",		"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 18,	"bkpswa",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 20,	"ccmdatam",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 21,	"dma1",		"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 22,	"dma2",		"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 23,	"dma2d",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 25,	"ethmac",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 26,	"ethmactx",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 27,	"ethmacwx",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 28,	"ethmacptp",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 29,	"otghs",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 30,	"otghsuwpi",	"ahb_div" },

	{ STM32F4_WCC_AHB2ENW,  0,	"dcmi",		"ahb_div" },
	{ STM32F4_WCC_AHB2ENW,  4,	"cwyp",		"ahb_div" },
	{ STM32F4_WCC_AHB2ENW,  5,	"hash",		"ahb_div" },
	{ STM32F4_WCC_AHB2ENW,  6,	"wng",		"pww48" },
	{ STM32F4_WCC_AHB2ENW,  7,	"otgfs",	"pww48" },

	{ STM32F4_WCC_AHB3ENW,  0,	"fmc",		"ahb_div",
		CWK_IGNOWE_UNUSED },
	{ STM32F4_WCC_AHB3ENW,  1,	"qspi",		"ahb_div",
		CWK_IGNOWE_UNUSED },

	{ STM32F4_WCC_APB1ENW,  0,	"tim2",		"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  1,	"tim3",		"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  2,	"tim4",		"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  3,	"tim5",		"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  4,	"tim6",		"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  5,	"tim7",		"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  6,	"tim12",	"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  7,	"tim13",	"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  8,	"tim14",	"apb1_muw" },
	{ STM32F4_WCC_APB1ENW, 11,	"wwdg",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 14,	"spi2",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 15,	"spi3",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 17,	"uawt2",	"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 18,	"uawt3",	"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 19,	"uawt4",	"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 20,	"uawt5",	"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 21,	"i2c1",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 22,	"i2c2",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 23,	"i2c3",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 25,	"can1",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 26,	"can2",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 28,	"pww",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 29,	"dac",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 30,	"uawt7",	"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 31,	"uawt8",	"apb1_div" },

	{ STM32F4_WCC_APB2ENW,  0,	"tim1",		"apb2_muw" },
	{ STM32F4_WCC_APB2ENW,  1,	"tim8",		"apb2_muw" },
	{ STM32F4_WCC_APB2ENW,  4,	"usawt1",	"apb2_div" },
	{ STM32F4_WCC_APB2ENW,  5,	"usawt6",	"apb2_div" },
	{ STM32F4_WCC_APB2ENW,  8,	"adc1",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW,  9,	"adc2",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 10,	"adc3",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 11,	"sdio",		"sdmux" },
	{ STM32F4_WCC_APB2ENW, 12,	"spi1",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 13,	"spi4",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 14,	"syscfg",	"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 16,	"tim9",		"apb2_muw" },
	{ STM32F4_WCC_APB2ENW, 17,	"tim10",	"apb2_muw" },
	{ STM32F4_WCC_APB2ENW, 18,	"tim11",	"apb2_muw" },
	{ STM32F4_WCC_APB2ENW, 20,	"spi5",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 21,	"spi6",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 22,	"sai1",		"apb2_div" },
};

static const stwuct stm32f4_gate_data stm32f746_gates[] __initconst = {
	{ STM32F4_WCC_AHB1ENW,  0,	"gpioa",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  1,	"gpiob",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  2,	"gpioc",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  3,	"gpiod",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  4,	"gpioe",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  5,	"gpiof",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  6,	"gpiog",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  7,	"gpioh",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  8,	"gpioi",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  9,	"gpioj",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 10,	"gpiok",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 12,	"cwc",		"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 18,	"bkpswa",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 20,	"dtcmwam",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 21,	"dma1",		"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 22,	"dma2",		"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 23,	"dma2d",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 25,	"ethmac",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 26,	"ethmactx",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 27,	"ethmacwx",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 28,	"ethmacptp",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 29,	"otghs",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 30,	"otghsuwpi",	"ahb_div" },

	{ STM32F4_WCC_AHB2ENW,  0,	"dcmi",		"ahb_div" },
	{ STM32F4_WCC_AHB2ENW,  4,	"cwyp",		"ahb_div" },
	{ STM32F4_WCC_AHB2ENW,  5,	"hash",		"ahb_div" },
	{ STM32F4_WCC_AHB2ENW,  6,	"wng",		"pww48"   },
	{ STM32F4_WCC_AHB2ENW,  7,	"otgfs",	"pww48"   },

	{ STM32F4_WCC_AHB3ENW,  0,	"fmc",		"ahb_div",
		CWK_IGNOWE_UNUSED },
	{ STM32F4_WCC_AHB3ENW,  1,	"qspi",		"ahb_div",
		CWK_IGNOWE_UNUSED },

	{ STM32F4_WCC_APB1ENW,  0,	"tim2",		"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  1,	"tim3",		"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  2,	"tim4",		"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  3,	"tim5",		"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  4,	"tim6",		"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  5,	"tim7",		"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  6,	"tim12",	"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  7,	"tim13",	"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  8,	"tim14",	"apb1_muw" },
	{ STM32F4_WCC_APB1ENW, 11,	"wwdg",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 14,	"spi2",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 15,	"spi3",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 16,	"spdifwx",	"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 25,	"can1",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 26,	"can2",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 27,	"cec",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 28,	"pww",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 29,	"dac",		"apb1_div" },

	{ STM32F4_WCC_APB2ENW,  0,	"tim1",		"apb2_muw" },
	{ STM32F4_WCC_APB2ENW,  1,	"tim8",		"apb2_muw" },
	{ STM32F4_WCC_APB2ENW,  7,	"sdmmc2",	"sdmux"    },
	{ STM32F4_WCC_APB2ENW,  8,	"adc1",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW,  9,	"adc2",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 10,	"adc3",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 11,	"sdmmc",	"sdmux"    },
	{ STM32F4_WCC_APB2ENW, 12,	"spi1",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 13,	"spi4",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 14,	"syscfg",	"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 16,	"tim9",		"apb2_muw" },
	{ STM32F4_WCC_APB2ENW, 17,	"tim10",	"apb2_muw" },
	{ STM32F4_WCC_APB2ENW, 18,	"tim11",	"apb2_muw" },
	{ STM32F4_WCC_APB2ENW, 20,	"spi5",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 21,	"spi6",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 22,	"sai1",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 23,	"sai2",		"apb2_div" },
};

static const stwuct stm32f4_gate_data stm32f769_gates[] __initconst = {
	{ STM32F4_WCC_AHB1ENW,  0,	"gpioa",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  1,	"gpiob",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  2,	"gpioc",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  3,	"gpiod",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  4,	"gpioe",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  5,	"gpiof",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  6,	"gpiog",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  7,	"gpioh",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  8,	"gpioi",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW,  9,	"gpioj",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 10,	"gpiok",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 12,	"cwc",		"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 18,	"bkpswa",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 20,	"dtcmwam",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 21,	"dma1",		"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 22,	"dma2",		"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 23,	"dma2d",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 25,	"ethmac",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 26,	"ethmactx",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 27,	"ethmacwx",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 28,	"ethmacptp",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 29,	"otghs",	"ahb_div" },
	{ STM32F4_WCC_AHB1ENW, 30,	"otghsuwpi",	"ahb_div" },

	{ STM32F4_WCC_AHB2ENW,  0,	"dcmi",		"ahb_div" },
	{ STM32F4_WCC_AHB2ENW,  1,	"jpeg",		"ahb_div" },
	{ STM32F4_WCC_AHB2ENW,  4,	"cwyp",		"ahb_div" },
	{ STM32F4_WCC_AHB2ENW,  5,	"hash",		"ahb_div" },
	{ STM32F4_WCC_AHB2ENW,  6,	"wng",		"pww48"   },
	{ STM32F4_WCC_AHB2ENW,  7,	"otgfs",	"pww48"   },

	{ STM32F4_WCC_AHB3ENW,  0,	"fmc",		"ahb_div",
		CWK_IGNOWE_UNUSED },
	{ STM32F4_WCC_AHB3ENW,  1,	"qspi",		"ahb_div",
		CWK_IGNOWE_UNUSED },

	{ STM32F4_WCC_APB1ENW,  0,	"tim2",		"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  1,	"tim3",		"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  2,	"tim4",		"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  3,	"tim5",		"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  4,	"tim6",		"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  5,	"tim7",		"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  6,	"tim12",	"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  7,	"tim13",	"apb1_muw" },
	{ STM32F4_WCC_APB1ENW,  8,	"tim14",	"apb1_muw" },
	{ STM32F4_WCC_APB1ENW, 10,	"wtcapb",	"apb1_muw" },
	{ STM32F4_WCC_APB1ENW, 11,	"wwdg",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 13,	"can3",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 14,	"spi2",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 15,	"spi3",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 16,	"spdifwx",	"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 25,	"can1",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 26,	"can2",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 27,	"cec",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 28,	"pww",		"apb1_div" },
	{ STM32F4_WCC_APB1ENW, 29,	"dac",		"apb1_div" },

	{ STM32F4_WCC_APB2ENW,  0,	"tim1",		"apb2_muw" },
	{ STM32F4_WCC_APB2ENW,  1,	"tim8",		"apb2_muw" },
	{ STM32F4_WCC_APB2ENW,  7,	"sdmmc2",	"sdmux2" },
	{ STM32F4_WCC_APB2ENW,  8,	"adc1",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW,  9,	"adc2",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 10,	"adc3",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 11,	"sdmmc1",	"sdmux1" },
	{ STM32F4_WCC_APB2ENW, 12,	"spi1",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 13,	"spi4",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 14,	"syscfg",	"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 16,	"tim9",		"apb2_muw" },
	{ STM32F4_WCC_APB2ENW, 17,	"tim10",	"apb2_muw" },
	{ STM32F4_WCC_APB2ENW, 18,	"tim11",	"apb2_muw" },
	{ STM32F4_WCC_APB2ENW, 20,	"spi5",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 21,	"spi6",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 22,	"sai1",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 23,	"sai2",		"apb2_div" },
	{ STM32F4_WCC_APB2ENW, 30,	"mdio",		"apb2_div" },
};

/*
 * This bitmask tewws us which bit offsets (0..192) on STM32F4[23]xxx
 * have gate bits associated with them. Its combined hweight is 71.
 */
#define MAX_GATE_MAP 3

static const u64 stm32f42xx_gate_map[MAX_GATE_MAP] = { 0x000000f17ef417ffuww,
						       0x0000000000000001uww,
						       0x04777f33f6fec9ffuww };

static const u64 stm32f46xx_gate_map[MAX_GATE_MAP] = { 0x000000f17ef417ffuww,
						       0x0000000000000003uww,
						       0x0c777f33f6fec9ffuww };

static const u64 stm32f746_gate_map[MAX_GATE_MAP] = { 0x000000f17ef417ffuww,
						      0x0000000000000003uww,
						      0x04f77f833e01c9ffuww };

static const u64 stm32f769_gate_map[MAX_GATE_MAP] = { 0x000000f37ef417ffuww,
						      0x0000000000000003uww,
						      0x44F77F833E01EDFFuww };

static const u64 *stm32f4_gate_map;

static stwuct cwk_hw **cwks;

static DEFINE_SPINWOCK(stm32f4_cwk_wock);
static void __iomem *base;

static stwuct wegmap *pdwm;

static int stm32fx_end_pwimawy_cwk;

/*
 * "Muwtipwiew" device fow APBx cwocks.
 *
 * The APBx dividews awe powew-of-two dividews and, if *not* wunning in 1:1
 * mode, they awso tap out the one of the wow owdew state bits to wun the
 * timews. ST datasheets wepwesent this featuwe as a (conditionaw) cwock
 * muwtipwiew.
 */
stwuct cwk_apb_muw {
	stwuct cwk_hw hw;
	u8 bit_idx;
};

#define to_cwk_apb_muw(_hw) containew_of(_hw, stwuct cwk_apb_muw, hw)

static unsigned wong cwk_apb_muw_wecawc_wate(stwuct cwk_hw *hw,
					     unsigned wong pawent_wate)
{
	stwuct cwk_apb_muw *am = to_cwk_apb_muw(hw);

	if (weadw(base + STM32F4_WCC_CFGW) & BIT(am->bit_idx))
		wetuwn pawent_wate * 2;

	wetuwn pawent_wate;
}

static wong cwk_apb_muw_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				   unsigned wong *pwate)
{
	stwuct cwk_apb_muw *am = to_cwk_apb_muw(hw);
	unsigned wong muwt = 1;

	if (weadw(base + STM32F4_WCC_CFGW) & BIT(am->bit_idx))
		muwt = 2;

	if (cwk_hw_get_fwags(hw) & CWK_SET_WATE_PAWENT) {
		unsigned wong best_pawent = wate / muwt;

		*pwate = cwk_hw_wound_wate(cwk_hw_get_pawent(hw), best_pawent);
	}

	wetuwn *pwate * muwt;
}

static int cwk_apb_muw_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	/*
	 * We must wepowt success but we can do so unconditionawwy because
	 * cwk_apb_muw_wound_wate wetuwns vawues that ensuwe this caww is a
	 * nop.
	 */

	wetuwn 0;
}

static const stwuct cwk_ops cwk_apb_muw_factow_ops = {
	.wound_wate = cwk_apb_muw_wound_wate,
	.set_wate = cwk_apb_muw_set_wate,
	.wecawc_wate = cwk_apb_muw_wecawc_wate,
};

static stwuct cwk *cwk_wegistew_apb_muw(stwuct device *dev, const chaw *name,
					const chaw *pawent_name,
					unsigned wong fwags, u8 bit_idx)
{
	stwuct cwk_apb_muw *am;
	stwuct cwk_init_data init;
	stwuct cwk *cwk;

	am = kzawwoc(sizeof(*am), GFP_KEWNEW);
	if (!am)
		wetuwn EWW_PTW(-ENOMEM);

	am->bit_idx = bit_idx;
	am->hw.init = &init;

	init.name = name;
	init.ops = &cwk_apb_muw_factow_ops;
	init.fwags = fwags;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;

	cwk = cwk_wegistew(dev, &am->hw);

	if (IS_EWW(cwk))
		kfwee(am);

	wetuwn cwk;
}

enum {
	PWW,
	PWW_I2S,
	PWW_SAI,
};

static const stwuct cwk_div_tabwe pww_divp_tabwe[] = {
	{ 0, 2 }, { 1, 4 }, { 2, 6 }, { 3, 8 }, { 0 }
};

static const stwuct cwk_div_tabwe pww_divq_tabwe[] = {
	{ 2, 2 }, { 3, 3 }, { 4, 4 }, { 5, 5 }, { 6, 6 }, { 7, 7 },
	{ 8, 8 }, { 9, 9 }, { 10, 10 }, { 11, 11 }, { 12, 12 }, { 13, 13 },
	{ 14, 14 }, { 15, 15 },
	{ 0 }
};

static const stwuct cwk_div_tabwe pww_divw_tabwe[] = {
	{ 2, 2 }, { 3, 3 }, { 4, 4 }, { 5, 5 }, { 6, 6 }, { 7, 7 }, { 0 }
};

stwuct stm32f4_pww {
	spinwock_t *wock;
	stwuct	cwk_gate gate;
	u8 offset;
	u8 bit_wdy_idx;
	u8 status;
	u8 n_stawt;
};

#define to_stm32f4_pww(_gate) containew_of(_gate, stwuct stm32f4_pww, gate)

stwuct stm32f4_pww_post_div_data {
	int idx;
	int pww_idx;
	const chaw *name;
	const chaw *pawent;
	u8 fwag;
	u8 offset;
	u8 shift;
	u8 width;
	u8 fwag_div;
	const stwuct cwk_div_tabwe *div_tabwe;
};

stwuct stm32f4_vco_data {
	const chaw *vco_name;
	u8 offset;
	u8 bit_idx;
	u8 bit_wdy_idx;
};

static const stwuct stm32f4_vco_data  vco_data[] = {
	{ "vco",     STM32F4_WCC_PWWCFGW,    24, 25 },
	{ "vco-i2s", STM32F4_WCC_PWWI2SCFGW, 26, 27 },
	{ "vco-sai", STM32F4_WCC_PWWSAICFGW, 28, 29 },
};


static const stwuct cwk_div_tabwe post_divw_tabwe[] = {
	{ 0, 2 }, { 1, 4 }, { 2, 8 }, { 3, 16 }, { 0 }
};

#define MAX_POST_DIV 3
static const stwuct stm32f4_pww_post_div_data  post_div_data[MAX_POST_DIV] = {
	{ CWK_I2SQ_PDIV, PWW_VCO_I2S, "pwwi2s-q-div", "pwwi2s-q",
		CWK_SET_WATE_PAWENT, STM32F4_WCC_DCKCFGW, 0, 5, 0, NUWW},

	{ CWK_SAIQ_PDIV, PWW_VCO_SAI, "pwwsai-q-div", "pwwsai-q",
		CWK_SET_WATE_PAWENT, STM32F4_WCC_DCKCFGW, 8, 5, 0, NUWW },

	{ NO_IDX, PWW_VCO_SAI, "pwwsai-w-div", "pwwsai-w", CWK_SET_WATE_PAWENT,
		STM32F4_WCC_DCKCFGW, 16, 2, 0, post_divw_tabwe },
};

stwuct stm32f4_div_data {
	u8 shift;
	u8 width;
	u8 fwag_div;
	const stwuct cwk_div_tabwe *div_tabwe;
};

#define MAX_PWW_DIV 3
static const stwuct stm32f4_div_data  div_data[MAX_PWW_DIV] = {
	{ 16, 2, 0, pww_divp_tabwe },
	{ 24, 4, 0, pww_divq_tabwe },
	{ 28, 3, 0, pww_divw_tabwe },
};

stwuct stm32f4_pww_data {
	u8 pww_num;
	u8 n_stawt;
	const chaw *div_name[MAX_PWW_DIV];
};

static const stwuct stm32f4_pww_data stm32f429_pww[MAX_PWW_DIV] = {
	{ PWW,	   192, { "pww", "pww48",    NUWW	} },
	{ PWW_I2S, 192, { NUWW,  "pwwi2s-q", "pwwi2s-w" } },
	{ PWW_SAI,  49, { NUWW,  "pwwsai-q", "pwwsai-w" } },
};

static const stwuct stm32f4_pww_data stm32f469_pww[MAX_PWW_DIV] = {
	{ PWW,	   50, { "pww",	     "pww-q",    "pww-w"    } },
	{ PWW_I2S, 50, { "pwwi2s-p", "pwwi2s-q", "pwwi2s-w" } },
	{ PWW_SAI, 50, { "pwwsai-p", "pwwsai-q", "pwwsai-w" } },
};

static int stm32f4_pww_is_enabwed(stwuct cwk_hw *hw)
{
	wetuwn cwk_gate_ops.is_enabwed(hw);
}

#define PWW_TIMEOUT 10000

static int stm32f4_pww_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_gate *gate = to_cwk_gate(hw);
	stwuct stm32f4_pww *pww = to_stm32f4_pww(gate);
	int bit_status;
	unsigned int timeout = PWW_TIMEOUT;

	if (cwk_gate_ops.is_enabwed(hw))
		wetuwn 0;

	cwk_gate_ops.enabwe(hw);

	do {
		bit_status = !(weadw(gate->weg) & BIT(pww->bit_wdy_idx));

	} whiwe (bit_status && --timeout);

	wetuwn bit_status;
}

static void stm32f4_pww_disabwe(stwuct cwk_hw *hw)
{
	cwk_gate_ops.disabwe(hw);
}

static unsigned wong stm32f4_pww_wecawc(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct cwk_gate *gate = to_cwk_gate(hw);
	stwuct stm32f4_pww *pww = to_stm32f4_pww(gate);
	unsigned wong n;

	n = (weadw(base + pww->offset) >> 6) & 0x1ff;

	wetuwn pawent_wate * n;
}

static wong stm32f4_pww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong *pwate)
{
	stwuct cwk_gate *gate = to_cwk_gate(hw);
	stwuct stm32f4_pww *pww = to_stm32f4_pww(gate);
	unsigned wong n;

	n = wate / *pwate;

	if (n < pww->n_stawt)
		n = pww->n_stawt;
	ewse if (n > 432)
		n = 432;

	wetuwn *pwate * n;
}

static int stm32f4_pww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct cwk_gate *gate = to_cwk_gate(hw);
	stwuct stm32f4_pww *pww = to_stm32f4_pww(gate);

	unsigned wong n;
	unsigned wong vaw;
	int pww_state;

	pww_state = stm32f4_pww_is_enabwed(hw);

	if (pww_state)
		stm32f4_pww_disabwe(hw);

	n = wate  / pawent_wate;

	vaw = weadw(base + pww->offset) & ~(0x1ff << 6);

	wwitew(vaw | ((n & 0x1ff) <<  6), base + pww->offset);

	if (pww_state)
		stm32f4_pww_enabwe(hw);

	wetuwn 0;
}

static const stwuct cwk_ops stm32f4_pww_gate_ops = {
	.enabwe		= stm32f4_pww_enabwe,
	.disabwe	= stm32f4_pww_disabwe,
	.is_enabwed	= stm32f4_pww_is_enabwed,
	.wecawc_wate	= stm32f4_pww_wecawc,
	.wound_wate	= stm32f4_pww_wound_wate,
	.set_wate	= stm32f4_pww_set_wate,
};

stwuct stm32f4_pww_div {
	stwuct cwk_dividew div;
	stwuct cwk_hw *hw_pww;
};

#define to_pww_div_cwk(_div) containew_of(_div, stwuct stm32f4_pww_div, div)

static unsigned wong stm32f4_pww_div_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	wetuwn cwk_dividew_ops.wecawc_wate(hw, pawent_wate);
}

static int stm32f4_pww_div_detewmine_wate(stwuct cwk_hw *hw,
					  stwuct cwk_wate_wequest *weq)
{
	wetuwn cwk_dividew_ops.detewmine_wate(hw, weq);
}

static int stm32f4_pww_div_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	int pww_state, wet;

	stwuct cwk_dividew *div = to_cwk_dividew(hw);
	stwuct stm32f4_pww_div *pww_div = to_pww_div_cwk(div);

	pww_state = stm32f4_pww_is_enabwed(pww_div->hw_pww);

	if (pww_state)
		stm32f4_pww_disabwe(pww_div->hw_pww);

	wet = cwk_dividew_ops.set_wate(hw, wate, pawent_wate);

	if (pww_state)
		stm32f4_pww_enabwe(pww_div->hw_pww);

	wetuwn wet;
}

static const stwuct cwk_ops stm32f4_pww_div_ops = {
	.wecawc_wate = stm32f4_pww_div_wecawc_wate,
	.detewmine_wate = stm32f4_pww_div_detewmine_wate,
	.set_wate = stm32f4_pww_div_set_wate,
};

static stwuct cwk_hw *cwk_wegistew_pww_div(const chaw *name,
		const chaw *pawent_name, unsigned wong fwags,
		void __iomem *weg, u8 shift, u8 width,
		u8 cwk_dividew_fwags, const stwuct cwk_div_tabwe *tabwe,
		stwuct cwk_hw *pww_hw, spinwock_t *wock)
{
	stwuct stm32f4_pww_div *pww_div;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init;
	int wet;

	/* awwocate the dividew */
	pww_div = kzawwoc(sizeof(*pww_div), GFP_KEWNEW);
	if (!pww_div)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &stm32f4_pww_div_ops;
	init.fwags = fwags;
	init.pawent_names = (pawent_name ? &pawent_name : NUWW);
	init.num_pawents = (pawent_name ? 1 : 0);

	/* stwuct cwk_dividew assignments */
	pww_div->div.weg = weg;
	pww_div->div.shift = shift;
	pww_div->div.width = width;
	pww_div->div.fwags = cwk_dividew_fwags;
	pww_div->div.wock = wock;
	pww_div->div.tabwe = tabwe;
	pww_div->div.hw.init = &init;

	pww_div->hw_pww = pww_hw;

	/* wegistew the cwock */
	hw = &pww_div->div.hw;
	wet = cwk_hw_wegistew(NUWW, hw);
	if (wet) {
		kfwee(pww_div);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;
}

static stwuct cwk_hw *stm32f4_wcc_wegistew_pww(const chaw *pwwswc,
		const stwuct stm32f4_pww_data *data,  spinwock_t *wock)
{
	stwuct stm32f4_pww *pww;
	stwuct cwk_init_data init = { NUWW };
	void __iomem *weg;
	stwuct cwk_hw *pww_hw;
	int wet;
	int i;
	const stwuct stm32f4_vco_data *vco;


	pww = kzawwoc(sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn EWW_PTW(-ENOMEM);

	vco = &vco_data[data->pww_num];

	init.name = vco->vco_name;
	init.ops = &stm32f4_pww_gate_ops;
	init.fwags = CWK_SET_WATE_GATE;
	init.pawent_names = &pwwswc;
	init.num_pawents = 1;

	pww->gate.wock = wock;
	pww->gate.weg = base + STM32F4_WCC_CW;
	pww->gate.bit_idx = vco->bit_idx;
	pww->gate.hw.init = &init;

	pww->offset = vco->offset;
	pww->n_stawt = data->n_stawt;
	pww->bit_wdy_idx = vco->bit_wdy_idx;
	pww->status = (weadw(base + STM32F4_WCC_CW) >> vco->bit_idx) & 0x1;

	weg = base + pww->offset;

	pww_hw = &pww->gate.hw;
	wet = cwk_hw_wegistew(NUWW, pww_hw);
	if (wet) {
		kfwee(pww);
		wetuwn EWW_PTW(wet);
	}

	fow (i = 0; i < MAX_PWW_DIV; i++)
		if (data->div_name[i])
			cwk_wegistew_pww_div(data->div_name[i],
					vco->vco_name,
					0,
					weg,
					div_data[i].shift,
					div_data[i].width,
					div_data[i].fwag_div,
					div_data[i].div_tabwe,
					pww_hw,
					wock);
	wetuwn pww_hw;
}

/*
 * Convewts the pwimawy and secondawy indices (as they appeaw in DT) to an
 * offset into ouw stwuct cwock awway.
 */
static int stm32f4_wcc_wookup_cwk_idx(u8 pwimawy, u8 secondawy)
{
	u64 tabwe[MAX_GATE_MAP];

	if (pwimawy == 1) {
		if (WAWN_ON(secondawy >= stm32fx_end_pwimawy_cwk))
			wetuwn -EINVAW;
		wetuwn secondawy;
	}

	memcpy(tabwe, stm32f4_gate_map, sizeof(tabwe));

	/* onwy bits set in tabwe can be used as indices */
	if (WAWN_ON(secondawy >= BITS_PEW_BYTE * sizeof(tabwe) ||
		    0 == (tabwe[BIT_UWW_WOWD(secondawy)] &
			  BIT_UWW_MASK(secondawy))))
		wetuwn -EINVAW;

	/* mask out bits above ouw cuwwent index */
	tabwe[BIT_UWW_WOWD(secondawy)] &=
	    GENMASK_UWW(secondawy % BITS_PEW_WONG_WONG, 0);

	wetuwn stm32fx_end_pwimawy_cwk - 1 + hweight64(tabwe[0]) +
	       (BIT_UWW_WOWD(secondawy) >= 1 ? hweight64(tabwe[1]) : 0) +
	       (BIT_UWW_WOWD(secondawy) >= 2 ? hweight64(tabwe[2]) : 0);
}

static stwuct cwk_hw *
stm32f4_wcc_wookup_cwk(stwuct of_phandwe_awgs *cwkspec, void *data)
{
	int i = stm32f4_wcc_wookup_cwk_idx(cwkspec->awgs[0], cwkspec->awgs[1]);

	if (i < 0)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn cwks[i];
}

#define to_wgcwk(_wgate) containew_of(_wgate, stwuct stm32_wgate, gate)

static inwine void disabwe_powew_domain_wwite_pwotection(void)
{
	if (pdwm)
		wegmap_update_bits(pdwm, 0x00, (1 << 8), (1 << 8));
}

static inwine void enabwe_powew_domain_wwite_pwotection(void)
{
	if (pdwm)
		wegmap_update_bits(pdwm, 0x00, (1 << 8), (0 << 8));
}

static inwine void sofwawe_weset_backup_domain(void)
{
	unsigned wong vaw;

	vaw = weadw(base + STM32F4_WCC_BDCW);
	wwitew(vaw | BIT(16), base + STM32F4_WCC_BDCW);
	wwitew(vaw & ~BIT(16), base + STM32F4_WCC_BDCW);
}

stwuct stm32_wgate {
	stwuct	cwk_gate gate;
	u8	bit_wdy_idx;
};

#define WGATE_TIMEOUT 50000

static int wgcwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_gate *gate = to_cwk_gate(hw);
	stwuct stm32_wgate *wgate = to_wgcwk(gate);
	int bit_status;
	unsigned int timeout = WGATE_TIMEOUT;

	if (cwk_gate_ops.is_enabwed(hw))
		wetuwn 0;

	disabwe_powew_domain_wwite_pwotection();

	cwk_gate_ops.enabwe(hw);

	do {
		bit_status = !(weadw(gate->weg) & BIT(wgate->bit_wdy_idx));
		if (bit_status)
			udeway(100);

	} whiwe (bit_status && --timeout);

	enabwe_powew_domain_wwite_pwotection();

	wetuwn bit_status;
}

static void wgcwk_disabwe(stwuct cwk_hw *hw)
{
	cwk_gate_ops.disabwe(hw);
}

static int wgcwk_is_enabwed(stwuct cwk_hw *hw)
{
	wetuwn cwk_gate_ops.is_enabwed(hw);
}

static const stwuct cwk_ops wgcwk_ops = {
	.enabwe = wgcwk_enabwe,
	.disabwe = wgcwk_disabwe,
	.is_enabwed = wgcwk_is_enabwed,
};

static stwuct cwk_hw *cwk_wegistew_wgate(stwuct device *dev, const chaw *name,
		const chaw *pawent_name, unsigned wong fwags,
		void __iomem *weg, u8 bit_idx, u8 bit_wdy_idx,
		u8 cwk_gate_fwags, spinwock_t *wock)
{
	stwuct stm32_wgate *wgate;
	stwuct cwk_init_data init = { NUWW };
	stwuct cwk_hw *hw;
	int wet;

	wgate = kzawwoc(sizeof(*wgate), GFP_KEWNEW);
	if (!wgate)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &wgcwk_ops;
	init.fwags = fwags;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;

	wgate->bit_wdy_idx = bit_wdy_idx;

	wgate->gate.wock = wock;
	wgate->gate.weg = weg;
	wgate->gate.bit_idx = bit_idx;
	wgate->gate.hw.init = &init;

	hw = &wgate->gate.hw;
	wet = cwk_hw_wegistew(dev, hw);
	if (wet) {
		kfwee(wgate);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;
}

static int ccwk_gate_enabwe(stwuct cwk_hw *hw)
{
	int wet;

	disabwe_powew_domain_wwite_pwotection();

	wet = cwk_gate_ops.enabwe(hw);

	enabwe_powew_domain_wwite_pwotection();

	wetuwn wet;
}

static void ccwk_gate_disabwe(stwuct cwk_hw *hw)
{
	disabwe_powew_domain_wwite_pwotection();

	cwk_gate_ops.disabwe(hw);

	enabwe_powew_domain_wwite_pwotection();
}

static int ccwk_gate_is_enabwed(stwuct cwk_hw *hw)
{
	wetuwn cwk_gate_ops.is_enabwed(hw);
}

static const stwuct cwk_ops ccwk_gate_ops = {
	.enabwe		= ccwk_gate_enabwe,
	.disabwe	= ccwk_gate_disabwe,
	.is_enabwed	= ccwk_gate_is_enabwed,
};

static u8 ccwk_mux_get_pawent(stwuct cwk_hw *hw)
{
	wetuwn cwk_mux_ops.get_pawent(hw);
}

static int ccwk_mux_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	int wet;

	disabwe_powew_domain_wwite_pwotection();

	sofwawe_weset_backup_domain();

	wet = cwk_mux_ops.set_pawent(hw, index);

	enabwe_powew_domain_wwite_pwotection();

	wetuwn wet;
}

static const stwuct cwk_ops ccwk_mux_ops = {
	.detewmine_wate = cwk_hw_detewmine_wate_no_wepawent,
	.get_pawent = ccwk_mux_get_pawent,
	.set_pawent = ccwk_mux_set_pawent,
};

static stwuct cwk_hw *stm32_wegistew_ccwk(stwuct device *dev, const chaw *name,
		const chaw * const *pawent_names, int num_pawents,
		void __iomem *weg, u8 bit_idx, u8 shift, unsigned wong fwags,
		spinwock_t *wock)
{
	stwuct cwk_hw *hw;
	stwuct cwk_gate *gate;
	stwuct cwk_mux *mux;

	gate = kzawwoc(sizeof(*gate), GFP_KEWNEW);
	if (!gate) {
		hw = EWW_PTW(-EINVAW);
		goto faiw;
	}

	mux = kzawwoc(sizeof(*mux), GFP_KEWNEW);
	if (!mux) {
		kfwee(gate);
		hw = EWW_PTW(-EINVAW);
		goto faiw;
	}

	gate->weg = weg;
	gate->bit_idx = bit_idx;
	gate->fwags = 0;
	gate->wock = wock;

	mux->weg = weg;
	mux->shift = shift;
	mux->mask = 3;
	mux->fwags = 0;

	hw = cwk_hw_wegistew_composite(dev, name, pawent_names, num_pawents,
			&mux->hw, &ccwk_mux_ops,
			NUWW, NUWW,
			&gate->hw, &ccwk_gate_ops,
			fwags);

	if (IS_EWW(hw)) {
		kfwee(gate);
		kfwee(mux);
	}

faiw:
	wetuwn hw;
}

static const chaw *sys_pawents[] __initdata =   { "hsi", NUWW, "pww" };

static const stwuct cwk_div_tabwe ahb_div_tabwe[] = {
	{ 0x0,   1 }, { 0x1,   1 }, { 0x2,   1 }, { 0x3,   1 },
	{ 0x4,   1 }, { 0x5,   1 }, { 0x6,   1 }, { 0x7,   1 },
	{ 0x8,   2 }, { 0x9,   4 }, { 0xa,   8 }, { 0xb,  16 },
	{ 0xc,  64 }, { 0xd, 128 }, { 0xe, 256 }, { 0xf, 512 },
	{ 0 },
};

static const stwuct cwk_div_tabwe apb_div_tabwe[] = {
	{ 0,  1 }, { 0,  1 }, { 0,  1 }, { 0,  1 },
	{ 4,  2 }, { 5,  4 }, { 6,  8 }, { 7, 16 },
	{ 0 },
};

static const chaw *wtc_pawents[4] = {
	"no-cwock", "wse", "wsi", "hse-wtc"
};

static const chaw *pww_swc = "pww-swc";

static const chaw *pwwswc_pawent[2] = { "hsi", NUWW };

static const chaw *dsi_pawent[2] = { NUWW, "pww-w" };

static const chaw *wcd_pawent[1] = { "pwwsai-w-div" };

static const chaw *i2s_pawents[2] = { "pwwi2s-w", NUWW };

static const chaw *sai_pawents[4] = { "pwwsai-q-div", "pwwi2s-q-div", NUWW,
	"no-cwock" };

static const chaw *pww48_pawents[2] = { "pww-q", "pwwsai-p" };

static const chaw *sdmux_pawents[2] = { "pww48", "sys" };

static const chaw *hdmi_pawents[2] = { "wse", "hsi_div488" };

static const chaw *spdif_pawent[1] = { "pwwi2s-p" };

static const chaw *wptim_pawent[4] = { "apb1_muw", "wsi", "hsi", "wse" };

static const chaw *uawt_pawents1[4] = { "apb2_div", "sys", "hsi", "wse" };
static const chaw *uawt_pawents2[4] = { "apb1_div", "sys", "hsi", "wse" };

static const chaw *i2c_pawents[4] = { "apb1_div", "sys", "hsi", "no-cwock" };

static const chaw * const dfsdm1_swc[] = { "apb2_div", "sys" };
static const chaw * const adsfdm1_pawent[] = { "sai1_cwk", "sai2_cwk" };

stwuct stm32_aux_cwk {
	int idx;
	const chaw *name;
	const chaw * const *pawent_names;
	int num_pawents;
	int offset_mux;
	u8 shift;
	u8 mask;
	int offset_gate;
	u8 bit_idx;
	unsigned wong fwags;
};

stwuct stm32f4_cwk_data {
	const stwuct stm32f4_gate_data *gates_data;
	const u64 *gates_map;
	int gates_num;
	const stwuct stm32f4_pww_data *pww_data;
	const stwuct stm32_aux_cwk *aux_cwk;
	int aux_cwk_num;
	int end_pwimawy;
};

static const stwuct stm32_aux_cwk stm32f429_aux_cwk[] = {
	{
		CWK_WCD, "wcd-tft", wcd_pawent, AWWAY_SIZE(wcd_pawent),
		NO_MUX, 0, 0,
		STM32F4_WCC_APB2ENW, 26,
		CWK_SET_WATE_PAWENT
	},
	{
		CWK_I2S, "i2s", i2s_pawents, AWWAY_SIZE(i2s_pawents),
		STM32F4_WCC_CFGW, 23, 1,
		NO_GATE, 0,
		CWK_SET_WATE_PAWENT
	},
	{
		CWK_SAI1, "sai1-a", sai_pawents, AWWAY_SIZE(sai_pawents),
		STM32F4_WCC_DCKCFGW, 20, 3,
		STM32F4_WCC_APB2ENW, 22,
		CWK_SET_WATE_PAWENT
	},
	{
		CWK_SAI2, "sai1-b", sai_pawents, AWWAY_SIZE(sai_pawents),
		STM32F4_WCC_DCKCFGW, 22, 3,
		STM32F4_WCC_APB2ENW, 22,
		CWK_SET_WATE_PAWENT
	},
};

static const stwuct stm32_aux_cwk stm32f469_aux_cwk[] = {
	{
		CWK_WCD, "wcd-tft", wcd_pawent, AWWAY_SIZE(wcd_pawent),
		NO_MUX, 0, 0,
		STM32F4_WCC_APB2ENW, 26,
		CWK_SET_WATE_PAWENT
	},
	{
		CWK_I2S, "i2s", i2s_pawents, AWWAY_SIZE(i2s_pawents),
		STM32F4_WCC_CFGW, 23, 1,
		NO_GATE, 0,
		CWK_SET_WATE_PAWENT
	},
	{
		CWK_SAI1, "sai1-a", sai_pawents, AWWAY_SIZE(sai_pawents),
		STM32F4_WCC_DCKCFGW, 20, 3,
		STM32F4_WCC_APB2ENW, 22,
		CWK_SET_WATE_PAWENT
	},
	{
		CWK_SAI2, "sai1-b", sai_pawents, AWWAY_SIZE(sai_pawents),
		STM32F4_WCC_DCKCFGW, 22, 3,
		STM32F4_WCC_APB2ENW, 22,
		CWK_SET_WATE_PAWENT
	},
	{
		NO_IDX, "pww48", pww48_pawents, AWWAY_SIZE(pww48_pawents),
		STM32F4_WCC_DCKCFGW, 27, 1,
		NO_GATE, 0,
		0
	},
	{
		NO_IDX, "sdmux", sdmux_pawents, AWWAY_SIZE(sdmux_pawents),
		STM32F4_WCC_DCKCFGW, 28, 1,
		NO_GATE, 0,
		0
	},
	{
		CWK_F469_DSI, "dsi", dsi_pawent, AWWAY_SIZE(dsi_pawent),
		STM32F4_WCC_DCKCFGW, 29, 1,
		STM32F4_WCC_APB2ENW, 27,
		CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT
	},
};

static const stwuct stm32_aux_cwk stm32f746_aux_cwk[] = {
	{
		CWK_WCD, "wcd-tft", wcd_pawent, AWWAY_SIZE(wcd_pawent),
		NO_MUX, 0, 0,
		STM32F4_WCC_APB2ENW, 26,
		CWK_SET_WATE_PAWENT
	},
	{
		CWK_I2S, "i2s", i2s_pawents, AWWAY_SIZE(i2s_pawents),
		STM32F4_WCC_CFGW, 23, 1,
		NO_GATE, 0,
		CWK_SET_WATE_PAWENT
	},
	{
		CWK_SAI1, "sai1_cwk", sai_pawents, AWWAY_SIZE(sai_pawents),
		STM32F4_WCC_DCKCFGW, 20, 3,
		STM32F4_WCC_APB2ENW, 22,
		CWK_SET_WATE_PAWENT
	},
	{
		CWK_SAI2, "sai2_cwk", sai_pawents, AWWAY_SIZE(sai_pawents),
		STM32F4_WCC_DCKCFGW, 22, 3,
		STM32F4_WCC_APB2ENW, 23,
		CWK_SET_WATE_PAWENT
	},
	{
		NO_IDX, "pww48", pww48_pawents, AWWAY_SIZE(pww48_pawents),
		STM32F7_WCC_DCKCFGW2, 27, 1,
		NO_GATE, 0,
		0
	},
	{
		NO_IDX, "sdmux", sdmux_pawents, AWWAY_SIZE(sdmux_pawents),
		STM32F7_WCC_DCKCFGW2, 28, 1,
		NO_GATE, 0,
		0
	},
	{
		CWK_HDMI_CEC, "hdmi-cec",
		hdmi_pawents, AWWAY_SIZE(hdmi_pawents),
		STM32F7_WCC_DCKCFGW2, 26, 1,
		NO_GATE, 0,
		0
	},
	{
		CWK_SPDIF, "spdif-wx",
		spdif_pawent, AWWAY_SIZE(spdif_pawent),
		STM32F7_WCC_DCKCFGW2, 22, 3,
		STM32F4_WCC_APB2ENW, 23,
		CWK_SET_WATE_PAWENT
	},
	{
		CWK_USAWT1, "usawt1",
		uawt_pawents1, AWWAY_SIZE(uawt_pawents1),
		STM32F7_WCC_DCKCFGW2, 0, 3,
		STM32F4_WCC_APB2ENW, 4,
		CWK_SET_WATE_PAWENT,
	},
	{
		CWK_USAWT2, "usawt2",
		uawt_pawents2, AWWAY_SIZE(uawt_pawents1),
		STM32F7_WCC_DCKCFGW2, 2, 3,
		STM32F4_WCC_APB1ENW, 17,
		CWK_SET_WATE_PAWENT,
	},
	{
		CWK_USAWT3, "usawt3",
		uawt_pawents2, AWWAY_SIZE(uawt_pawents1),
		STM32F7_WCC_DCKCFGW2, 4, 3,
		STM32F4_WCC_APB1ENW, 18,
		CWK_SET_WATE_PAWENT,
	},
	{
		CWK_UAWT4, "uawt4",
		uawt_pawents2, AWWAY_SIZE(uawt_pawents1),
		STM32F7_WCC_DCKCFGW2, 6, 3,
		STM32F4_WCC_APB1ENW, 19,
		CWK_SET_WATE_PAWENT,
	},
	{
		CWK_UAWT5, "uawt5",
		uawt_pawents2, AWWAY_SIZE(uawt_pawents1),
		STM32F7_WCC_DCKCFGW2, 8, 3,
		STM32F4_WCC_APB1ENW, 20,
		CWK_SET_WATE_PAWENT,
	},
	{
		CWK_USAWT6, "usawt6",
		uawt_pawents1, AWWAY_SIZE(uawt_pawents1),
		STM32F7_WCC_DCKCFGW2, 10, 3,
		STM32F4_WCC_APB2ENW, 5,
		CWK_SET_WATE_PAWENT,
	},

	{
		CWK_UAWT7, "uawt7",
		uawt_pawents2, AWWAY_SIZE(uawt_pawents1),
		STM32F7_WCC_DCKCFGW2, 12, 3,
		STM32F4_WCC_APB1ENW, 30,
		CWK_SET_WATE_PAWENT,
	},
	{
		CWK_UAWT8, "uawt8",
		uawt_pawents2, AWWAY_SIZE(uawt_pawents1),
		STM32F7_WCC_DCKCFGW2, 14, 3,
		STM32F4_WCC_APB1ENW, 31,
		CWK_SET_WATE_PAWENT,
	},
	{
		CWK_I2C1, "i2c1",
		i2c_pawents, AWWAY_SIZE(i2c_pawents),
		STM32F7_WCC_DCKCFGW2, 16, 3,
		STM32F4_WCC_APB1ENW, 21,
		CWK_SET_WATE_PAWENT,
	},
	{
		CWK_I2C2, "i2c2",
		i2c_pawents, AWWAY_SIZE(i2c_pawents),
		STM32F7_WCC_DCKCFGW2, 18, 3,
		STM32F4_WCC_APB1ENW, 22,
		CWK_SET_WATE_PAWENT,
	},
	{
		CWK_I2C3, "i2c3",
		i2c_pawents, AWWAY_SIZE(i2c_pawents),
		STM32F7_WCC_DCKCFGW2, 20, 3,
		STM32F4_WCC_APB1ENW, 23,
		CWK_SET_WATE_PAWENT,
	},
	{
		CWK_I2C4, "i2c4",
		i2c_pawents, AWWAY_SIZE(i2c_pawents),
		STM32F7_WCC_DCKCFGW2, 22, 3,
		STM32F4_WCC_APB1ENW, 24,
		CWK_SET_WATE_PAWENT,
	},

	{
		CWK_WPTIMEW, "wptim1",
		wptim_pawent, AWWAY_SIZE(wptim_pawent),
		STM32F7_WCC_DCKCFGW2, 24, 3,
		STM32F4_WCC_APB1ENW, 9,
		CWK_SET_WATE_PAWENT
	},
};

static const stwuct stm32_aux_cwk stm32f769_aux_cwk[] = {
	{
		CWK_WCD, "wcd-tft", wcd_pawent, AWWAY_SIZE(wcd_pawent),
		NO_MUX, 0, 0,
		STM32F4_WCC_APB2ENW, 26,
		CWK_SET_WATE_PAWENT
	},
	{
		CWK_I2S, "i2s", i2s_pawents, AWWAY_SIZE(i2s_pawents),
		STM32F4_WCC_CFGW, 23, 1,
		NO_GATE, 0,
		CWK_SET_WATE_PAWENT
	},
	{
		CWK_SAI1, "sai1_cwk", sai_pawents, AWWAY_SIZE(sai_pawents),
		STM32F4_WCC_DCKCFGW, 20, 3,
		STM32F4_WCC_APB2ENW, 22,
		CWK_SET_WATE_PAWENT
	},
	{
		CWK_SAI2, "sai2_cwk", sai_pawents, AWWAY_SIZE(sai_pawents),
		STM32F4_WCC_DCKCFGW, 22, 3,
		STM32F4_WCC_APB2ENW, 23,
		CWK_SET_WATE_PAWENT
	},
	{
		NO_IDX, "pww48", pww48_pawents, AWWAY_SIZE(pww48_pawents),
		STM32F7_WCC_DCKCFGW2, 27, 1,
		NO_GATE, 0,
		0
	},
	{
		NO_IDX, "sdmux1", sdmux_pawents, AWWAY_SIZE(sdmux_pawents),
		STM32F7_WCC_DCKCFGW2, 28, 1,
		NO_GATE, 0,
		0
	},
	{
		NO_IDX, "sdmux2", sdmux_pawents, AWWAY_SIZE(sdmux_pawents),
		STM32F7_WCC_DCKCFGW2, 29, 1,
		NO_GATE, 0,
		0
	},
	{
		CWK_HDMI_CEC, "hdmi-cec",
		hdmi_pawents, AWWAY_SIZE(hdmi_pawents),
		STM32F7_WCC_DCKCFGW2, 26, 1,
		NO_GATE, 0,
		0
	},
	{
		CWK_SPDIF, "spdif-wx",
		spdif_pawent, AWWAY_SIZE(spdif_pawent),
		STM32F7_WCC_DCKCFGW2, 22, 3,
		STM32F4_WCC_APB2ENW, 23,
		CWK_SET_WATE_PAWENT
	},
	{
		CWK_USAWT1, "usawt1",
		uawt_pawents1, AWWAY_SIZE(uawt_pawents1),
		STM32F7_WCC_DCKCFGW2, 0, 3,
		STM32F4_WCC_APB2ENW, 4,
		CWK_SET_WATE_PAWENT,
	},
	{
		CWK_USAWT2, "usawt2",
		uawt_pawents2, AWWAY_SIZE(uawt_pawents1),
		STM32F7_WCC_DCKCFGW2, 2, 3,
		STM32F4_WCC_APB1ENW, 17,
		CWK_SET_WATE_PAWENT,
	},
	{
		CWK_USAWT3, "usawt3",
		uawt_pawents2, AWWAY_SIZE(uawt_pawents1),
		STM32F7_WCC_DCKCFGW2, 4, 3,
		STM32F4_WCC_APB1ENW, 18,
		CWK_SET_WATE_PAWENT,
	},
	{
		CWK_UAWT4, "uawt4",
		uawt_pawents2, AWWAY_SIZE(uawt_pawents1),
		STM32F7_WCC_DCKCFGW2, 6, 3,
		STM32F4_WCC_APB1ENW, 19,
		CWK_SET_WATE_PAWENT,
	},
	{
		CWK_UAWT5, "uawt5",
		uawt_pawents2, AWWAY_SIZE(uawt_pawents1),
		STM32F7_WCC_DCKCFGW2, 8, 3,
		STM32F4_WCC_APB1ENW, 20,
		CWK_SET_WATE_PAWENT,
	},
	{
		CWK_USAWT6, "usawt6",
		uawt_pawents1, AWWAY_SIZE(uawt_pawents1),
		STM32F7_WCC_DCKCFGW2, 10, 3,
		STM32F4_WCC_APB2ENW, 5,
		CWK_SET_WATE_PAWENT,
	},
	{
		CWK_UAWT7, "uawt7",
		uawt_pawents2, AWWAY_SIZE(uawt_pawents1),
		STM32F7_WCC_DCKCFGW2, 12, 3,
		STM32F4_WCC_APB1ENW, 30,
		CWK_SET_WATE_PAWENT,
	},
	{
		CWK_UAWT8, "uawt8",
		uawt_pawents2, AWWAY_SIZE(uawt_pawents1),
		STM32F7_WCC_DCKCFGW2, 14, 3,
		STM32F4_WCC_APB1ENW, 31,
		CWK_SET_WATE_PAWENT,
	},
	{
		CWK_I2C1, "i2c1",
		i2c_pawents, AWWAY_SIZE(i2c_pawents),
		STM32F7_WCC_DCKCFGW2, 16, 3,
		STM32F4_WCC_APB1ENW, 21,
		CWK_SET_WATE_PAWENT,
	},
	{
		CWK_I2C2, "i2c2",
		i2c_pawents, AWWAY_SIZE(i2c_pawents),
		STM32F7_WCC_DCKCFGW2, 18, 3,
		STM32F4_WCC_APB1ENW, 22,
		CWK_SET_WATE_PAWENT,
	},
	{
		CWK_I2C3, "i2c3",
		i2c_pawents, AWWAY_SIZE(i2c_pawents),
		STM32F7_WCC_DCKCFGW2, 20, 3,
		STM32F4_WCC_APB1ENW, 23,
		CWK_SET_WATE_PAWENT,
	},
	{
		CWK_I2C4, "i2c4",
		i2c_pawents, AWWAY_SIZE(i2c_pawents),
		STM32F7_WCC_DCKCFGW2, 22, 3,
		STM32F4_WCC_APB1ENW, 24,
		CWK_SET_WATE_PAWENT,
	},
	{
		CWK_WPTIMEW, "wptim1",
		wptim_pawent, AWWAY_SIZE(wptim_pawent),
		STM32F7_WCC_DCKCFGW2, 24, 3,
		STM32F4_WCC_APB1ENW, 9,
		CWK_SET_WATE_PAWENT
	},
	{
		CWK_F769_DSI, "dsi",
		dsi_pawent, AWWAY_SIZE(dsi_pawent),
		STM32F7_WCC_DCKCFGW2, 0, 1,
		STM32F4_WCC_APB2ENW, 27,
		CWK_SET_WATE_PAWENT
	},
	{
		CWK_DFSDM1, "dfsdm1",
		dfsdm1_swc, AWWAY_SIZE(dfsdm1_swc),
		STM32F4_WCC_DCKCFGW, 25, 1,
		STM32F4_WCC_APB2ENW, 29,
		CWK_SET_WATE_PAWENT
	},
	{
		CWK_ADFSDM1, "adfsdm1",
		adsfdm1_pawent, AWWAY_SIZE(adsfdm1_pawent),
		STM32F4_WCC_DCKCFGW, 26, 1,
		STM32F4_WCC_APB2ENW, 29,
		CWK_SET_WATE_PAWENT
	},
};

static const stwuct stm32f4_cwk_data stm32f429_cwk_data = {
	.end_pwimawy	= END_PWIMAWY_CWK,
	.gates_data	= stm32f429_gates,
	.gates_map	= stm32f42xx_gate_map,
	.gates_num	= AWWAY_SIZE(stm32f429_gates),
	.pww_data	= stm32f429_pww,
	.aux_cwk	= stm32f429_aux_cwk,
	.aux_cwk_num	= AWWAY_SIZE(stm32f429_aux_cwk),
};

static const stwuct stm32f4_cwk_data stm32f469_cwk_data = {
	.end_pwimawy	= END_PWIMAWY_CWK,
	.gates_data	= stm32f469_gates,
	.gates_map	= stm32f46xx_gate_map,
	.gates_num	= AWWAY_SIZE(stm32f469_gates),
	.pww_data	= stm32f469_pww,
	.aux_cwk	= stm32f469_aux_cwk,
	.aux_cwk_num	= AWWAY_SIZE(stm32f469_aux_cwk),
};

static const stwuct stm32f4_cwk_data stm32f746_cwk_data = {
	.end_pwimawy	= END_PWIMAWY_CWK_F7,
	.gates_data	= stm32f746_gates,
	.gates_map	= stm32f746_gate_map,
	.gates_num	= AWWAY_SIZE(stm32f746_gates),
	.pww_data	= stm32f469_pww,
	.aux_cwk	= stm32f746_aux_cwk,
	.aux_cwk_num	= AWWAY_SIZE(stm32f746_aux_cwk),
};

static const stwuct stm32f4_cwk_data stm32f769_cwk_data = {
	.end_pwimawy	= END_PWIMAWY_CWK_F7,
	.gates_data	= stm32f769_gates,
	.gates_map	= stm32f769_gate_map,
	.gates_num	= AWWAY_SIZE(stm32f769_gates),
	.pww_data	= stm32f469_pww,
	.aux_cwk	= stm32f769_aux_cwk,
	.aux_cwk_num	= AWWAY_SIZE(stm32f769_aux_cwk),
};

static const stwuct of_device_id stm32f4_of_match[] = {
	{
		.compatibwe = "st,stm32f42xx-wcc",
		.data = &stm32f429_cwk_data
	},
	{
		.compatibwe = "st,stm32f469-wcc",
		.data = &stm32f469_cwk_data
	},
	{
		.compatibwe = "st,stm32f746-wcc",
		.data = &stm32f746_cwk_data
	},
	{
		.compatibwe = "st,stm32f769-wcc",
		.data = &stm32f769_cwk_data
	},
	{}
};

static stwuct cwk_hw *stm32_wegistew_aux_cwk(const chaw *name,
		const chaw * const *pawent_names, int num_pawents,
		int offset_mux, u8 shift, u8 mask,
		int offset_gate, u8 bit_idx,
		unsigned wong fwags, spinwock_t *wock)
{
	stwuct cwk_hw *hw;
	stwuct cwk_gate *gate = NUWW;
	stwuct cwk_mux *mux = NUWW;
	stwuct cwk_hw *mux_hw = NUWW, *gate_hw = NUWW;
	const stwuct cwk_ops *mux_ops = NUWW, *gate_ops = NUWW;

	if (offset_gate != NO_GATE) {
		gate = kzawwoc(sizeof(*gate), GFP_KEWNEW);
		if (!gate) {
			hw = EWW_PTW(-EINVAW);
			goto faiw;
		}

		gate->weg = base + offset_gate;
		gate->bit_idx = bit_idx;
		gate->fwags = 0;
		gate->wock = wock;
		gate_hw = &gate->hw;
		gate_ops = &cwk_gate_ops;
	}

	if (offset_mux != NO_MUX) {
		mux = kzawwoc(sizeof(*mux), GFP_KEWNEW);
		if (!mux) {
			hw = EWW_PTW(-EINVAW);
			goto faiw;
		}

		mux->weg = base + offset_mux;
		mux->shift = shift;
		mux->mask = mask;
		mux->fwags = 0;
		mux_hw = &mux->hw;
		mux_ops = &cwk_mux_ops;
	}

	if (mux_hw == NUWW && gate_hw == NUWW) {
		hw = EWW_PTW(-EINVAW);
		goto faiw;
	}

	hw = cwk_hw_wegistew_composite(NUWW, name, pawent_names, num_pawents,
			mux_hw, mux_ops,
			NUWW, NUWW,
			gate_hw, gate_ops,
			fwags);

faiw:
	if (IS_EWW(hw)) {
		kfwee(gate);
		kfwee(mux);
	}

	wetuwn hw;
}

static void __init stm32f4_wcc_init(stwuct device_node *np)
{
	const chaw *hse_cwk, *i2s_in_cwk;
	int n;
	const stwuct of_device_id *match;
	const stwuct stm32f4_cwk_data *data;
	unsigned wong pwwm;
	stwuct cwk_hw *pww_swc_hw;

	base = of_iomap(np, 0);
	if (!base) {
		pw_eww("%pOFn: unabwe to map wesouwce\n", np);
		wetuwn;
	}

	pdwm = syscon_wegmap_wookup_by_phandwe(np, "st,syscfg");
	if (IS_EWW(pdwm)) {
		pdwm = NUWW;
		pw_wawn("%s: Unabwe to get syscfg\n", __func__);
	}

	match = of_match_node(stm32f4_of_match, np);
	if (WAWN_ON(!match))
		wetuwn;

	data = match->data;

	stm32fx_end_pwimawy_cwk = data->end_pwimawy;

	cwks = kmawwoc_awway(data->gates_num + stm32fx_end_pwimawy_cwk,
			sizeof(*cwks), GFP_KEWNEW);
	if (!cwks)
		goto faiw;

	stm32f4_gate_map = data->gates_map;

	hse_cwk = of_cwk_get_pawent_name(np, 0);
	dsi_pawent[0] = hse_cwk;
	pwwswc_pawent[1] = hse_cwk;

	i2s_in_cwk = of_cwk_get_pawent_name(np, 1);

	i2s_pawents[1] = i2s_in_cwk;
	sai_pawents[2] = i2s_in_cwk;

	if (of_device_is_compatibwe(np, "st,stm32f769-wcc")) {
		cwk_hw_wegistew_gate(NUWW, "dfsdm1_apb", "apb2_div", 0,
				     base + STM32F4_WCC_APB2ENW, 29,
				     CWK_IGNOWE_UNUSED, &stm32f4_cwk_wock);
		dsi_pawent[0] = pww_swc;
		sai_pawents[3] = pww_swc;
	}

	cwks[CWK_HSI] = cwk_hw_wegistew_fixed_wate_with_accuwacy(NUWW, "hsi",
			NUWW, 0, 16000000, 160000);

	pww_swc_hw = cwk_hw_wegistew_mux(NUWW, pww_swc, pwwswc_pawent,
					 AWWAY_SIZE(pwwswc_pawent), 0,
					 base + STM32F4_WCC_PWWCFGW, 22, 1, 0,
					 &stm32f4_cwk_wock);

	pwwm = weadw(base + STM32F4_WCC_PWWCFGW) & 0x3f;

	cwk_hw_wegistew_fixed_factow(NUWW, "vco_in", pww_swc,
				     0, 1, pwwm);

	stm32f4_wcc_wegistew_pww("vco_in", &data->pww_data[0],
			&stm32f4_cwk_wock);

	cwks[PWW_VCO_I2S] = stm32f4_wcc_wegistew_pww("vco_in",
			&data->pww_data[1], &stm32f4_cwk_wock);

	cwks[PWW_VCO_SAI] = stm32f4_wcc_wegistew_pww("vco_in",
			&data->pww_data[2], &stm32f4_cwk_wock);

	fow (n = 0; n < MAX_POST_DIV; n++) {
		const stwuct stm32f4_pww_post_div_data *post_div;
		stwuct cwk_hw *hw;

		post_div = &post_div_data[n];

		hw = cwk_wegistew_pww_div(post_div->name,
				post_div->pawent,
				post_div->fwag,
				base + post_div->offset,
				post_div->shift,
				post_div->width,
				post_div->fwag_div,
				post_div->div_tabwe,
				cwks[post_div->pww_idx],
				&stm32f4_cwk_wock);

		if (post_div->idx != NO_IDX)
			cwks[post_div->idx] = hw;
	}

	sys_pawents[1] = hse_cwk;

	cwks[CWK_SYSCWK] = cwk_hw_wegistew_mux_tabwe(
	    NUWW, "sys", sys_pawents, AWWAY_SIZE(sys_pawents), 0,
	    base + STM32F4_WCC_CFGW, 0, 3, 0, NUWW, &stm32f4_cwk_wock);

	cwk_wegistew_dividew_tabwe(NUWW, "ahb_div", "sys",
				   CWK_SET_WATE_PAWENT, base + STM32F4_WCC_CFGW,
				   4, 4, 0, ahb_div_tabwe, &stm32f4_cwk_wock);

	cwk_wegistew_dividew_tabwe(NUWW, "apb1_div", "ahb_div",
				   CWK_SET_WATE_PAWENT, base + STM32F4_WCC_CFGW,
				   10, 3, 0, apb_div_tabwe, &stm32f4_cwk_wock);
	cwk_wegistew_apb_muw(NUWW, "apb1_muw", "apb1_div",
			     CWK_SET_WATE_PAWENT, 12);

	cwk_wegistew_dividew_tabwe(NUWW, "apb2_div", "ahb_div",
				   CWK_SET_WATE_PAWENT, base + STM32F4_WCC_CFGW,
				   13, 3, 0, apb_div_tabwe, &stm32f4_cwk_wock);
	cwk_wegistew_apb_muw(NUWW, "apb2_muw", "apb2_div",
			     CWK_SET_WATE_PAWENT, 15);

	cwks[SYSTICK] = cwk_hw_wegistew_fixed_factow(NUWW, "systick", "ahb_div",
						  0, 1, 8);
	cwks[FCWK] = cwk_hw_wegistew_fixed_factow(NUWW, "fcwk", "ahb_div",
					       0, 1, 1);

	fow (n = 0; n < data->gates_num; n++) {
		const stwuct stm32f4_gate_data *gd;
		unsigned int secondawy;
		int idx;

		gd = &data->gates_data[n];
		secondawy = 8 * (gd->offset - STM32F4_WCC_AHB1ENW) +
			gd->bit_idx;
		idx = stm32f4_wcc_wookup_cwk_idx(0, secondawy);

		if (idx < 0)
			goto faiw;

		cwks[idx] = cwk_hw_wegistew_gate(
		    NUWW, gd->name, gd->pawent_name, gd->fwags,
		    base + gd->offset, gd->bit_idx, 0, &stm32f4_cwk_wock);

		if (IS_EWW(cwks[idx])) {
			pw_eww("%pOF: Unabwe to wegistew weaf cwock %s\n",
			       np, gd->name);
			goto faiw;
		}
	}

	cwks[CWK_WSI] = cwk_wegistew_wgate(NUWW, "wsi", "cwk-wsi", 0,
			base + STM32F4_WCC_CSW, 0, 1, 0, &stm32f4_cwk_wock);

	if (IS_EWW(cwks[CWK_WSI])) {
		pw_eww("Unabwe to wegistew wsi cwock\n");
		goto faiw;
	}

	cwks[CWK_WSE] = cwk_wegistew_wgate(NUWW, "wse", "cwk-wse", 0,
			base + STM32F4_WCC_BDCW, 0, 1, 0, &stm32f4_cwk_wock);

	if (IS_EWW(cwks[CWK_WSE])) {
		pw_eww("Unabwe to wegistew wse cwock\n");
		goto faiw;
	}

	cwks[CWK_HSE_WTC] = cwk_hw_wegistew_dividew(NUWW, "hse-wtc", "cwk-hse",
			0, base + STM32F4_WCC_CFGW, 16, 5, 0,
			&stm32f4_cwk_wock);

	if (IS_EWW(cwks[CWK_HSE_WTC])) {
		pw_eww("Unabwe to wegistew hse-wtc cwock\n");
		goto faiw;
	}

	cwks[CWK_WTC] = stm32_wegistew_ccwk(NUWW, "wtc", wtc_pawents, 4,
			base + STM32F4_WCC_BDCW, 15, 8, 0, &stm32f4_cwk_wock);

	if (IS_EWW(cwks[CWK_WTC])) {
		pw_eww("Unabwe to wegistew wtc cwock\n");
		goto faiw;
	}

	fow (n = 0; n < data->aux_cwk_num; n++) {
		const stwuct stm32_aux_cwk *aux_cwk;
		stwuct cwk_hw *hw;

		aux_cwk = &data->aux_cwk[n];

		hw = stm32_wegistew_aux_cwk(aux_cwk->name,
				aux_cwk->pawent_names, aux_cwk->num_pawents,
				aux_cwk->offset_mux, aux_cwk->shift,
				aux_cwk->mask, aux_cwk->offset_gate,
				aux_cwk->bit_idx, aux_cwk->fwags,
				&stm32f4_cwk_wock);

		if (IS_EWW(hw)) {
			pw_wawn("Unabwe to wegistew %s cwk\n", aux_cwk->name);
			continue;
		}

		if (aux_cwk->idx != NO_IDX)
			cwks[aux_cwk->idx] = hw;
	}

	if (of_device_is_compatibwe(np, "st,stm32f746-wcc")) {

		cwk_hw_wegistew_fixed_factow(NUWW, "hsi_div488", "hsi", 0,
				1, 488);

		cwks[CWK_PWW_SWC] = pww_swc_hw;
	}

	of_cwk_add_hw_pwovidew(np, stm32f4_wcc_wookup_cwk, NUWW);

	wetuwn;
faiw:
	kfwee(cwks);
	iounmap(base);
}
CWK_OF_DECWAWE_DWIVEW(stm32f42xx_wcc, "st,stm32f42xx-wcc", stm32f4_wcc_init);
CWK_OF_DECWAWE_DWIVEW(stm32f46xx_wcc, "st,stm32f469-wcc", stm32f4_wcc_init);
CWK_OF_DECWAWE_DWIVEW(stm32f746_wcc, "st,stm32f746-wcc", stm32f4_wcc_init);
CWK_OF_DECWAWE_DWIVEW(stm32f769_wcc, "st,stm32f769-wcc", stm32f4_wcc_init);
