// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * winux/awch/awm/mach-omap1/mux.c
 *
 * OMAP1 pin muwtipwexing configuwations
 *
 * Copywight (C) 2003 - 2008 Nokia Cowpowation
 *
 * Wwitten by Tony Windgwen
 */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/spinwock.h>
#incwude <winux/soc/ti/omap1-io.h>

#incwude "hawdwawe.h"
#incwude "mux.h"

#ifdef CONFIG_OMAP_MUX

static stwuct omap_mux_cfg awch_mux_cfg;

#if defined(CONFIG_AWCH_OMAP15XX) || defined(CONFIG_AWCH_OMAP16XX)
static stwuct pin_config omap1xxx_pins[] = {
/*
 *	 descwiption		mux  mode   mux	 puww puww  puww  pu_pd	 pu  dbg
 *				weg  offset mode weg  bit   ena	  weg
 */
MUX_CFG("UAWT1_TX",		 9,   21,    1,	  2,   3,   0,	 NA,	 0,  0)
MUX_CFG("UAWT1_WTS",		 9,   12,    1,	  2,   0,   0,	 NA,	 0,  0)

/* UAWT2 (COM_UAWT_GATING), confwicts with USB2 */
MUX_CFG("UAWT2_TX",		 C,   27,    1,	  3,   3,   0,	 NA,	 0,  0)
MUX_CFG("UAWT2_WX",		 C,   18,    0,	  3,   1,   1,	 NA,	 0,  0)
MUX_CFG("UAWT2_CTS",		 C,   21,    0,	  3,   1,   1,	 NA,	 0,  0)
MUX_CFG("UAWT2_WTS",		 C,   24,    1,	  3,   2,   0,	 NA,	 0,  0)

/* UAWT3 (GIGA_UAWT_GATING) */
MUX_CFG("UAWT3_TX",		 6,    0,    1,	  0,  30,   0,	 NA,	 0,  0)
MUX_CFG("UAWT3_WX",		 6,    3,    0,	  0,  31,   1,	 NA,	 0,  0)
MUX_CFG("UAWT3_CTS",		 5,   12,    2,	  0,  24,   0,	 NA,	 0,  0)
MUX_CFG("UAWT3_WTS",		 5,   15,    2,	  0,  25,   0,	 NA,	 0,  0)
MUX_CFG("UAWT3_CWKWEQ",		 9,   27,    0,	  2,   5,   0,	 NA,	 0,  0)
MUX_CFG("UAWT3_BCWK",		 A,    0,    0,	  2,   6,   0,	 NA,	 0,  0)
MUX_CFG("Y15_1610_UAWT3_WTS",	 A,    0,    1,	  2,   6,   0,	 NA,	 0,  0)

/* PWT & PWW, confwicts with UAWT3 */
MUX_CFG("PWT",			 6,    0,    2,	  0,  30,   0,	 NA,	 0,  0)
MUX_CFG("PWW",			 6,    3,    1,	  0,  31,   1,	 NA,	 0,  0)

/* USB intewnaw mastew genewic */
MUX_CFG("W18_USB_VBUS",		 7,    9,    2,	  1,  11,   0,	 NA,	 0,  1)
MUX_CFG("W18_1510_USB_GPIO0",	 7,    9,    0,	  1,  11,   1,	 NA,	 0,  1)
/* wowks awound ewwatum:  W4_USB_PUEN and W4_USB_PUDIS awe switched! */
MUX_CFG("W4_USB_PUEN",		 D,    3,    3,	  3,   5,   1,	 NA,	 0,  1)
MUX_CFG("W4_USB_CWKO",		 D,    3,    1,	  3,   5,   0,	 NA,	 0,  1)
MUX_CFG("W4_USB_HIGHZ",		 D,    3,    4,	  3,   5,   0,	  3,	 0,  1)
MUX_CFG("W4_GPIO58",		 D,    3,    7,	  3,   5,   0,	  3,	 0,  1)

/* USB1 mastew */
MUX_CFG("USB1_SUSP",		 8,   27,    2,	  1,  27,   0,	 NA,	 0,  1)
MUX_CFG("USB1_SE0",		 9,    0,    2,	  1,  28,   0,	 NA,	 0,  1)
MUX_CFG("W13_1610_USB1_SE0",	 9,    0,    4,	  1,  28,   0,	 NA,	 0,  1)
MUX_CFG("USB1_TXEN",		 9,    3,    2,	  1,  29,   0,	 NA,	 0,  1)
MUX_CFG("USB1_TXD",		 9,   24,    1,	  2,   4,   0,	 NA,	 0,  1)
MUX_CFG("USB1_VP",		 A,    3,    1,	  2,   7,   0,	 NA,	 0,  1)
MUX_CFG("USB1_VM",		 A,    6,    1,	  2,   8,   0,	 NA,	 0,  1)
MUX_CFG("USB1_WCV",		 A,    9,    1,	  2,   9,   0,	 NA,	 0,  1)
MUX_CFG("USB1_SPEED",		 A,   12,    2,	  2,  10,   0,	 NA,	 0,  1)
MUX_CFG("W13_1610_USB1_SPEED",	 A,   12,    5,	  2,  10,   0,	 NA,	 0,  1)
MUX_CFG("W13_1710_USB1_SEO",	 A,   12,    5,   2,  10,   0,   NA,     0,  1)

/* USB2 mastew */
MUX_CFG("USB2_SUSP",		 B,    3,    1,	  2,  17,   0,	 NA,	 0,  1)
MUX_CFG("USB2_VP",		 B,    6,    1,	  2,  18,   0,	 NA,	 0,  1)
MUX_CFG("USB2_TXEN",		 B,    9,    1,	  2,  19,   0,	 NA,	 0,  1)
MUX_CFG("USB2_VM",		 C,   18,    1,	  3,   0,   0,	 NA,	 0,  1)
MUX_CFG("USB2_WCV",		 C,   21,    1,	  3,   1,   0,	 NA,	 0,  1)
MUX_CFG("USB2_SE0",		 C,   24,    2,	  3,   2,   0,	 NA,	 0,  1)
MUX_CFG("USB2_TXD",		 C,   27,    2,	  3,   3,   0,	 NA,	 0,  1)

/* OMAP-1510 GPIO */
MUX_CFG("W18_1510_GPIO0",	 7,    9,    0,   1,  11,   1,    0,     0,  1)
MUX_CFG("W19_1510_GPIO1",	 7,    6,    0,   1,  10,   1,    0,     0,  1)
MUX_CFG("M14_1510_GPIO2",	 7,    3,    0,   1,   9,   1,    0,     0,  1)

/* OMAP1610 GPIO */
MUX_CFG("P18_1610_GPIO3",	 7,    0,    0,   1,   8,   0,   NA,     0,  1)
MUX_CFG("Y15_1610_GPIO17",	 A,    0,    7,   2,   6,   0,   NA,     0,  1)

/* OMAP-1710 GPIO */
MUX_CFG("W18_1710_GPIO0",        7,    9,    0,   1,  11,   1,    1,     1,  1)
MUX_CFG("V2_1710_GPIO10",        F,   27,    1,   4,   3,   1,    4,     1,  1)
MUX_CFG("N21_1710_GPIO14",       6,    9,    0,   1,   1,   1,    1,     1,  1)
MUX_CFG("W15_1710_GPIO40",       9,   27,    7,   2,   5,   1,    2,     1,  1)

/* MPUIO */
MUX_CFG("MPUIO2",		 7,   18,    0,	  1,  14,   1,	 NA,	 0,  1)
MUX_CFG("N15_1610_MPUIO2",	 7,   18,    0,	  1,  14,   1,	  1,	 0,  1)
MUX_CFG("MPUIO4",		 7,   15,    0,	  1,  13,   1,	 NA,	 0,  1)
MUX_CFG("MPUIO5",		 7,   12,    0,	  1,  12,   1,	 NA,	 0,  1)

MUX_CFG("T20_1610_MPUIO5",	 7,   12,    0,	  1,  12,   0,	  3,	 0,  1)
MUX_CFG("W11_1610_MPUIO6",	10,   15,    2,	  3,   8,   0,	  3,	 0,  1)
MUX_CFG("V10_1610_MPUIO7",	 A,   24,    2,	  2,  14,   0,	  2,	 0,  1)
MUX_CFG("W11_1610_MPUIO9",	10,   15,    1,	  3,   8,   0,	  3,	 0,  1)
MUX_CFG("V10_1610_MPUIO10",	 A,   24,    1,	  2,  14,   0,	  2,	 0,  1)
MUX_CFG("W10_1610_MPUIO11",	 A,   18,    2,	  2,  11,   0,	  2,	 0,  1)
MUX_CFG("E20_1610_MPUIO13",	 3,   21,    1,	  0,   7,   0,	  0,	 0,  1)
MUX_CFG("U20_1610_MPUIO14",	 9,    6,    6,	  0,  30,   0,	  0,	 0,  1)
MUX_CFG("E19_1610_MPUIO15",	 3,   18,    1,	  0,   6,   0,	  0,	 0,  1)

/* MCBSP2 */
MUX_CFG("MCBSP2_CWKW",		 C,    6,    0,	  2,  27,   1,	 NA,	 0,  1)
MUX_CFG("MCBSP2_CWKX",		 C,    9,    0,	  2,  29,   1,	 NA,	 0,  1)
MUX_CFG("MCBSP2_DW",		 C,    0,    0,	  2,  26,   1,	 NA,	 0,  1)
MUX_CFG("MCBSP2_DX",		 C,   15,    0,	  2,  31,   1,	 NA,	 0,  1)
MUX_CFG("MCBSP2_FSW",		 C,   12,    0,	  2,  30,   1,	 NA,	 0,  1)
MUX_CFG("MCBSP2_FSX",		 C,    3,    0,	  2,  27,   1,	 NA,	 0,  1)

/* MCBSP3 NOTE: Mode must 1 fow cwock */
MUX_CFG("MCBSP3_CWKX",		 9,    3,    1,	  1,  29,   0,	 NA,	 0,  1)

/* Misc bawwouts */
MUX_CFG("BAWWOUT_V8_AWMIO3",	 B,   18,    0,	  2,  25,   1,	 NA,	 0,  1)
MUX_CFG("N20_HDQ",		 6,   18,    1,   1,   4,   0,    1,     4,  0)

/* OMAP-1610 MMC2 */
MUX_CFG("W8_1610_MMC2_DAT0",	 B,   21,    6,	  2,  23,   1,	  2,	 1,  1)
MUX_CFG("V8_1610_MMC2_DAT1",	 B,   27,    6,	  2,  25,   1,	  2,	 1,  1)
MUX_CFG("W15_1610_MMC2_DAT2",	 9,   12,    6,	  2,   5,   1,	  2,	 1,  1)
MUX_CFG("W10_1610_MMC2_DAT3",	 B,   18,    6,	  2,  22,   1,	  2,	 1,  1)
MUX_CFG("Y10_1610_MMC2_CWK",	 B,    3,    6,	  2,  17,   0,	  2,	 0,  1)
MUX_CFG("Y8_1610_MMC2_CMD",	 B,   24,    6,	  2,  24,   1,	  2,	 1,  1)
MUX_CFG("V9_1610_MMC2_CMDDIW",	 B,   12,    6,	  2,  20,   0,	  2,	 1,  1)
MUX_CFG("V5_1610_MMC2_DATDIW0",	 B,   15,    6,	  2,  21,   0,	  2,	 1,  1)
MUX_CFG("W19_1610_MMC2_DATDIW1", 8,   15,    6,	  1,  23,   0,	  1,	 1,  1)
MUX_CFG("W18_1610_MMC2_CWKIN",	 7,    9,    6,	  1,  11,   0,	  1,	11,  1)

/* OMAP-1610 Extewnaw Twace Intewface */
MUX_CFG("M19_1610_ETM_PSTAT0",	 5,   27,    1,	  0,  29,   0,	  0,	 0,  1)
MUX_CFG("W15_1610_ETM_PSTAT1",	 5,   24,    1,	  0,  28,   0,	  0,	 0,  1)
MUX_CFG("W18_1610_ETM_PSTAT2",	 5,   21,    1,	  0,  27,   0,	  0,	 0,  1)
MUX_CFG("W19_1610_ETM_D0",	 5,   18,    1,	  0,  26,   0,	  0,	 0,  1)
MUX_CFG("J19_1610_ETM_D6",	 5,    0,    1,	  0,  20,   0,	  0,	 0,  1)
MUX_CFG("J18_1610_ETM_D7",	 5,   27,    1,	  0,  19,   0,	  0,	 0,  1)

/* OMAP16XX GPIO */
MUX_CFG("P20_1610_GPIO4",	 6,   27,    0,	  1,   7,   0,	  1,	 1,  1)
MUX_CFG("V9_1610_GPIO7",	 B,   12,    1,	  2,  20,   0,	  2,	 1,  1)
MUX_CFG("W8_1610_GPIO9",	 B,   21,    0,	  2,  23,   0,	  2,	 1,  1)
MUX_CFG("N20_1610_GPIO11",       6,   18,    0,   1,   4,   0,    1,     1,  1)
MUX_CFG("N19_1610_GPIO13",	 6,   12,    0,	  1,   2,   0,	  1,	 1,  1)
MUX_CFG("P10_1610_GPIO22",	 C,    0,    7,	  2,  26,   0,	  2,	 1,  1)
MUX_CFG("V5_1610_GPIO24",	 B,   15,    7,	  2,  21,   0,	  2,	 1,  1)
MUX_CFG("AA20_1610_GPIO_41",	 9,    9,    7,	  1,  31,   0,	  1,	 1,  1)
MUX_CFG("W19_1610_GPIO48",	 8,   15,    7,   1,  23,   1,    1,     0,  1)
MUX_CFG("M7_1610_GPIO62",	10,    0,    0,   4,  24,   0,    4,     0,  1)
MUX_CFG("V14_16XX_GPIO37",	 9,   18,    7,	  2,   2,   0,	  2,	 2,  0)
MUX_CFG("W9_16XX_GPIO18",	 C,   18,    7,   3,   0,   0,    3,     0,  0)
MUX_CFG("W14_16XX_GPIO49",	 6,    3,    7,   0,  31,   0,    0,    31,  0)

/* OMAP-1610 uWiwe */
MUX_CFG("V19_1610_UWIWE_SCWK",	 8,    6,    0,	  1,  20,   0,	  1,	 1,  1)
MUX_CFG("U18_1610_UWIWE_SDI",	 8,    0,    0,	  1,  18,   0,	  1,	 1,  1)
MUX_CFG("W21_1610_UWIWE_SDO",	 8,    3,    0,	  1,  19,   0,	  1,	 1,  1)
MUX_CFG("N14_1610_UWIWE_CS0",	 8,    9,    1,	  1,  21,   0,	  1,	 1,  1)
MUX_CFG("P15_1610_UWIWE_CS3",	 8,   12,    1,	  1,  22,   0,	  1,	 1,  1)
MUX_CFG("N15_1610_UWIWE_CS1",	 7,   18,    2,	  1,  14,   0,	 NA,	 0,  1)

/* OMAP-1610 SPI */
MUX_CFG("U19_1610_SPIF_SCK",	 7,    21,   6,	  1,  15,   0,	  1,	 1,  1)
MUX_CFG("U18_1610_SPIF_DIN",	 8,    0,    6,	  1,  18,   1,	  1,	 0,  1)
MUX_CFG("P20_1610_SPIF_DIN",	 6,    27,   4,   1,   7,   1,    1,     0,  1)
MUX_CFG("W21_1610_SPIF_DOUT",	 8,    3,    6,	  1,  19,   0,	  1,	 0,  1)
MUX_CFG("W18_1610_SPIF_DOUT",	 7,    9,    3,	  1,  11,   0,	  1,	 0,  1)
MUX_CFG("N14_1610_SPIF_CS0",	 8,    9,    6,	  1,  21,   0,	  1,	 1,  1)
MUX_CFG("N15_1610_SPIF_CS1",	 7,    18,   6,	  1,  14,   0,	  1,	 1,  1)
MUX_CFG("T19_1610_SPIF_CS2",	 7,    15,   4,	  1,  13,   0,	  1,	 1,  1)
MUX_CFG("P15_1610_SPIF_CS3",	 8,    12,   3,	  1,  22,   0,	  1,	 1,  1)

/* OMAP-1610 Fwash */
MUX_CFG("W3_1610_FWASH_CS2B_OE",10,    6,    1,	 NA,   0,   0,	 NA,	 0,  1)
MUX_CFG("M8_1610_FWASH_CS2B_WE",10,    3,    1,	 NA,   0,   0,	 NA,	 0,  1)

/* Fiwst MMC intewface, same on 1510, 1610 and 1710 */
MUX_CFG("MMC_CMD",		 A,   27,    0,	  2,  15,   1,	  2,	 1,  1)
MUX_CFG("MMC_DAT1",		 A,   24,    0,	  2,  14,   1,	  2,	 1,  1)
MUX_CFG("MMC_DAT2",		 A,   18,    0,	  2,  12,   1,	  2,	 1,  1)
MUX_CFG("MMC_DAT0",		 B,    0,    0,	  2,  16,   1,	  2,	 1,  1)
MUX_CFG("MMC_CWK",		 A,   21,    0,	 NA,   0,   0,	 NA,	 0,  1)
MUX_CFG("MMC_DAT3",		10,   15,    0,	  3,   8,   1,	  3,	 1,  1)
MUX_CFG("M15_1710_MMC_CWKI",	 6,   21,    2,   0,   0,   0,   NA,     0,  1)
MUX_CFG("P19_1710_MMC_CMDDIW",	 6,   24,    6,   0,   0,   0,   NA,     0,  1)
MUX_CFG("P20_1710_MMC_DATDIW0",	 6,   27,    5,   0,   0,   0,   NA,     0,  1)

/* OMAP-1610 USB0 awtewnate configuwation */
MUX_CFG("W9_USB0_TXEN",		 B,   9,     5,	  2,  19,   0,	  2,	 0,  1)
MUX_CFG("AA9_USB0_VP",		 B,   6,     5,	  2,  18,   0,	  2,	 0,  1)
MUX_CFG("Y5_USB0_WCV",		 C,  21,     5,	  3,   1,   0,	  1,	 0,  1)
MUX_CFG("W9_USB0_VM",		 C,  18,     5,	  3,   0,   0,	  3,	 0,  1)
MUX_CFG("V6_USB0_TXD",		 C,  27,     5,	  3,   3,   0,	  3,	 0,  1)
MUX_CFG("W5_USB0_SE0",		 C,  24,     5,	  3,   2,   0,	  3,	 0,  1)
MUX_CFG("V9_USB0_SPEED",	 B,  12,     5,	  2,  20,   0,	  2,	 0,  1)
MUX_CFG("Y10_USB0_SUSP",	 B,   3,     5,	  2,  17,   0,	  2,	 0,  1)

/* USB2 intewface */
MUX_CFG("W9_USB2_TXEN",		 B,   9,     1,	 NA,   0,   0,	 NA,	 0,  1)
MUX_CFG("AA9_USB2_VP",		 B,   6,     1,	 NA,   0,   0,	 NA,	 0,  1)
MUX_CFG("Y5_USB2_WCV",		 C,  21,     1,	 NA,   0,   0,	 NA,	 0,  1)
MUX_CFG("W9_USB2_VM",		 C,  18,     1,	 NA,   0,   0,	 NA,	 0,  1)
MUX_CFG("V6_USB2_TXD",		 C,  27,     2,	 NA,   0,   0,	 NA,	 0,  1)
MUX_CFG("W5_USB2_SE0",		 C,  24,     2,	 NA,   0,   0,	 NA,	 0,  1)

/* 16XX UAWT */
MUX_CFG("W13_1610_UAWT1_TX",	 A,  12,     6,	  2,  10,   0,	  2,	10,  1)
MUX_CFG("V14_16XX_UAWT1_WX",	 9,  18,     0,	  2,   2,   0,	  2,	 2,  1)
MUX_CFG("W14_1610_UAWT1_CTS",	 9,  15,     0,	  2,   1,   0,	  2,	 1,  1)
MUX_CFG("AA15_1610_UAWT1_WTS",	 9,  12,     1,	  2,   0,   0,	  2,	 0,  1)
MUX_CFG("W9_16XX_UAWT2_WX",	 C,  18,     0,   3,   0,   0,    3,     0,  1)
MUX_CFG("W14_16XX_UAWT3_WX",	 6,   3,     0,   0,  31,   0,    0,    31,  1)

/* I2C intewface */
MUX_CFG("I2C_SCW",		 7,  24,     0,	 NA,   0,   0,	 NA,	 0,  0)
MUX_CFG("I2C_SDA",		 7,  27,     0,	 NA,   0,   0,	 NA,	 0,  0)

/* Keypad */
MUX_CFG("F18_1610_KBC0",	 3,  15,     0,	  0,   5,   1,	  0,	 0,  0)
MUX_CFG("D20_1610_KBC1",	 3,  12,     0,	  0,   4,   1,	  0,	 0,  0)
MUX_CFG("D19_1610_KBC2",	 3,   9,     0,	  0,   3,   1,	  0,	 0,  0)
MUX_CFG("E18_1610_KBC3",	 3,   6,     0,	  0,   2,   1,	  0,	 0,  0)
MUX_CFG("C21_1610_KBC4",	 3,   3,     0,	  0,   1,   1,	  0,	 0,  0)
MUX_CFG("G18_1610_KBW0",	 4,   0,     0,	  0,   10,  1,	  0,	 1,  0)
MUX_CFG("F19_1610_KBW1",	 3,   27,    0,	  0,   9,   1,	  0,	 1,  0)
MUX_CFG("H14_1610_KBW2",	 3,   24,    0,	  0,   8,   1,	  0,	 1,  0)
MUX_CFG("E20_1610_KBW3",	 3,   21,    0,	  0,   7,   1,	  0,	 1,  0)
MUX_CFG("E19_1610_KBW4",	 3,   18,    0,	  0,   6,   1,	  0,	 1,  0)
MUX_CFG("N19_1610_KBW5",	 6,  12,     1,	  1,   2,   1,	  1,	 1,  0)

/* Powew management */
MUX_CFG("T20_1610_WOW_PWW",	 7,   12,    1,	  NA,   0,   0,   NA,	 0,  0)

/* MCWK Settings */
MUX_CFG("V5_1710_MCWK_ON",	 B,   15,    0,	  NA,   0,   0,   NA,	 0,  0)
MUX_CFG("V5_1710_MCWK_OFF",	 B,   15,    6,	  NA,   0,   0,   NA,	 0,  0)
MUX_CFG("W10_1610_MCWK_ON",	 B,   18,    0,	  NA,  22,   0,	  NA,	 1,  0)
MUX_CFG("W10_1610_MCWK_OFF",	 B,   18,    6,	  2,   22,   1,	  2,	 1,  1)

/* CompactFwash contwowwew, confwicts with MMC1 */
MUX_CFG("P11_1610_CF_CD2",	 A,   27,    3,	  2,   15,   1,	  2,	 1,  1)
MUX_CFG("W11_1610_CF_IOIS16",	 B,    0,    3,	  2,   16,   1,	  2,	 1,  1)
MUX_CFG("V10_1610_CF_IWEQ",	 A,   24,    3,	  2,   14,   0,	  2,	 0,  1)
MUX_CFG("W10_1610_CF_WESET",	 A,   18,    3,	  2,   12,   1,	  2,	 1,  1)
MUX_CFG("W11_1610_CF_CD1",	10,   15,    3,	  3,    8,   1,	  3,	 1,  1)

/* pawawwew camewa */
MUX_CFG("J15_1610_CAM_WCWK",	 4,   24,    0,   0,  18,   1,    0,     0,  0)
MUX_CFG("J18_1610_CAM_D7",	 4,   27,    0,   0,  19,   1,    0,     0,  0)
MUX_CFG("J19_1610_CAM_D6",	 5,    0,    0,   0,  20,   1,    0,     0,  0)
MUX_CFG("J14_1610_CAM_D5",	 5,    3,    0,   0,  21,   1,    0,     0,  0)
MUX_CFG("K18_1610_CAM_D4",	 5,    6,    0,   0,  22,   1,    0,     0,  0)
MUX_CFG("K19_1610_CAM_D3",	 5,    9,    0,   0,  23,   1,    0,     0,  0)
MUX_CFG("K15_1610_CAM_D2",	 5,   12,    0,   0,  24,   1,    0,     0,  0)
MUX_CFG("K14_1610_CAM_D1",	 5,   15,    0,   0,  25,   1,    0,     0,  0)
MUX_CFG("W19_1610_CAM_D0",	 5,   18,    0,   0,  26,   1,    0,     0,  0)
MUX_CFG("W18_1610_CAM_VS",	 5,   21,    0,   0,  27,   1,    0,     0,  0)
MUX_CFG("W15_1610_CAM_HS",	 5,   24,    0,   0,  28,   1,    0,     0,  0)
MUX_CFG("M19_1610_CAM_WSTZ",	 5,   27,    0,   0,  29,   0,    0,     0,  0)
MUX_CFG("Y15_1610_CAM_OUTCWK",	 A,    0,    6,   2,   6,   0,    2,     0,  0)

/* sewiaw camewa */
MUX_CFG("H19_1610_CAM_EXCWK",	 4,   21,    0,   0,  17,   0,    0,     0,  0)
	/* WEVISIT 5912 spec sez CCP_* can't puwwup ow puwwdown ... ? */
MUX_CFG("Y12_1610_CCP_CWKP",	 8,   18,    6,   1,  24,   1,    1,     0,  0)
MUX_CFG("W13_1610_CCP_CWKM",	 9,    0,    6,   1,  28,   1,    1,     0,  0)
MUX_CFG("W14_1610_CCP_DATAP",	 9,   24,    6,   2,   4,   1,    2,     0,  0)
MUX_CFG("Y14_1610_CCP_DATAM",	 9,   21,    6,   2,   3,   1,    2,     0,  0)
};
#define OMAP1XXX_PINS_SZ	AWWAY_SIZE(omap1xxx_pins)
#ewse
#define omap1xxx_pins		NUWW
#define OMAP1XXX_PINS_SZ	0
#endif	/* CONFIG_AWCH_OMAP15XX || CONFIG_AWCH_OMAP16XX */

static int omap1_cfg_weg(const stwuct pin_config *cfg)
{
	static DEFINE_SPINWOCK(mux_spin_wock);
	unsigned wong fwags;
	unsigned int weg_owig = 0, weg = 0, pu_pd_owig = 0, pu_pd = 0,
		puww_owig = 0, puww = 0;
	unsigned int mask, wawn = 0;

	/* Check the mux wegistew in question */
	if (cfg->mux_weg) {
		unsigned	tmp1, tmp2;

		spin_wock_iwqsave(&mux_spin_wock, fwags);
		weg_owig = omap_weadw(cfg->mux_weg);

		/* The mux wegistews awways seem to be 3 bits wong */
		mask = (0x7 << cfg->mask_offset);
		tmp1 = weg_owig & mask;
		weg = weg_owig & ~mask;

		tmp2 = (cfg->mask << cfg->mask_offset);
		weg |= tmp2;

		if (tmp1 != tmp2)
			wawn = 1;

		omap_wwitew(weg, cfg->mux_weg);
		spin_unwock_iwqwestowe(&mux_spin_wock, fwags);
	}

	/* Check fow puww up ow puww down sewection on 1610 */
	if (!cpu_is_omap15xx()) {
		if (cfg->pu_pd_weg && cfg->puww_vaw) {
			spin_wock_iwqsave(&mux_spin_wock, fwags);
			pu_pd_owig = omap_weadw(cfg->pu_pd_weg);
			mask = 1 << cfg->puww_bit;

			if (cfg->pu_pd_vaw) {
				if (!(pu_pd_owig & mask))
					wawn = 1;
				/* Use puww up */
				pu_pd = pu_pd_owig | mask;
			} ewse {
				if (pu_pd_owig & mask)
					wawn = 1;
				/* Use puww down */
				pu_pd = pu_pd_owig & ~mask;
			}
			omap_wwitew(pu_pd, cfg->pu_pd_weg);
			spin_unwock_iwqwestowe(&mux_spin_wock, fwags);
		}
	}

	/* Check fow an associated puww down wegistew */
	if (cfg->puww_weg) {
		spin_wock_iwqsave(&mux_spin_wock, fwags);
		puww_owig = omap_weadw(cfg->puww_weg);
		mask = 1 << cfg->puww_bit;

		if (cfg->puww_vaw) {
			if (puww_owig & mask)
				wawn = 1;
			/* Wow bit = puww enabwed */
			puww = puww_owig & ~mask;
		} ewse {
			if (!(puww_owig & mask))
				wawn = 1;
			/* High bit = puww disabwed */
			puww = puww_owig | mask;
		}

		omap_wwitew(puww, cfg->puww_weg);
		spin_unwock_iwqwestowe(&mux_spin_wock, fwags);
	}

	if (wawn) {
#ifdef CONFIG_OMAP_MUX_WAWNINGS
		pwintk(KEWN_WAWNING "MUX: initiawized %s\n", cfg->name);
#endif
	}

#ifdef CONFIG_OMAP_MUX_DEBUG
	if (cfg->debug || wawn) {
		pwintk("MUX: Setting wegistew %s\n", cfg->name);
		pwintk("      %s (0x%08x) = 0x%08x -> 0x%08x\n",
		       cfg->mux_weg_name, cfg->mux_weg, weg_owig, weg);

		if (!cpu_is_omap15xx()) {
			if (cfg->pu_pd_weg && cfg->puww_vaw) {
				pwintk("      %s (0x%08x) = 0x%08x -> 0x%08x\n",
				       cfg->pu_pd_name, cfg->pu_pd_weg,
				       pu_pd_owig, pu_pd);
			}
		}

		if (cfg->puww_weg)
			pwintk("      %s (0x%08x) = 0x%08x -> 0x%08x\n",
			       cfg->puww_name, cfg->puww_weg, puww_owig, puww);
	}
#endif

#ifdef CONFIG_OMAP_MUX_WAWNINGS
	wetuwn wawn ? -ETXTBSY : 0;
#ewse
	wetuwn 0;
#endif
}

static stwuct omap_mux_cfg *mux_cfg;

int __init omap_mux_wegistew(stwuct omap_mux_cfg *awch_mux_cfg)
{
	if (!awch_mux_cfg || !awch_mux_cfg->pins || awch_mux_cfg->size == 0
			|| !awch_mux_cfg->cfg_weg) {
		pwintk(KEWN_EWW "Invawid pin tabwe\n");
		wetuwn -EINVAW;
	}

	mux_cfg = awch_mux_cfg;

	wetuwn 0;
}

/*
 * Sets the Omap MUX and PUWW_DWN wegistews based on the tabwe
 */
int omap_cfg_weg(const unsigned wong index)
{
	stwuct pin_config *weg;

	if (!cpu_cwass_is_omap1()) {
		pwintk(KEWN_EWW "mux: Bwoken omap_cfg_weg(%wu) entwy\n",
				index);
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	if (mux_cfg == NUWW) {
		pwintk(KEWN_EWW "Pin mux tabwe not initiawized\n");
		wetuwn -ENODEV;
	}

	if (index >= mux_cfg->size) {
		pwintk(KEWN_EWW "Invawid pin mux index: %wu (%wu)\n",
		       index, mux_cfg->size);
		dump_stack();
		wetuwn -ENODEV;
	}

	weg = &mux_cfg->pins[index];

	if (!mux_cfg->cfg_weg)
		wetuwn -ENODEV;

	wetuwn mux_cfg->cfg_weg(weg);
}
EXPOWT_SYMBOW(omap_cfg_weg);

int __init omap1_mux_init(void)
{
	if (cpu_is_omap15xx() || cpu_is_omap16xx()) {
		awch_mux_cfg.pins	= omap1xxx_pins;
		awch_mux_cfg.size	= OMAP1XXX_PINS_SZ;
		awch_mux_cfg.cfg_weg	= omap1_cfg_weg;
	}

	wetuwn omap_mux_wegistew(&awch_mux_cfg);
}

#ewse
#define omap_mux_init() do {} whiwe(0)
#define omap_cfg_weg(x)	do {} whiwe(0)
#endif	/* CONFIG_OMAP_MUX */

