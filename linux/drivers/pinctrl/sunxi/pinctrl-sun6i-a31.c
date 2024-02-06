/*
 * Awwwinnew A31 SoCs pinctww dwivew.
 *
 * Copywight (C) 2014 Maxime Wipawd
 *
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/pinctww.h>

#incwude "pinctww-sunxi.h"

static const stwuct sunxi_desc_pin sun6i_a31_pins[] = {
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* TXD0 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wcd1",
					 PINCTWW_SUN6I_A31),	/* D0 */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* DTW */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 0)),	/* PA_EINT0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* TXD1 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wcd1",
					 PINCTWW_SUN6I_A31),	/* D1 */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* DSW */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 1)),	/* PA_EINT1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* TXD2 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wcd1",
					 PINCTWW_SUN6I_A31),	/* D2 */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* DCD */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 2)),	/* PA_EINT2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* TXD3 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wcd1",
					 PINCTWW_SUN6I_A31),	/* D3 */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* WING */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 3)),	/* PA_EINT3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* TXD4 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wcd1",
					 PINCTWW_SUN6I_A31),	/* D4 */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* TX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 4)),	/* PA_EINT4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* TXD5 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wcd1",
					 PINCTWW_SUN6I_A31),	/* D5 */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* WX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 5)),	/* PA_EINT5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* TXD6 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wcd1",
					 PINCTWW_SUN6I_A31),	/* D6 */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* WTS */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 6)),	/* PA_EINT6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* TXD7 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wcd1",
					 PINCTWW_SUN6I_A31),	/* D7 */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* CTS */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 7)),	/* PA_EINT7 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* TXCWK */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wcd1",
					 PINCTWW_SUN6I_A31),	/* D8 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 8)),	/* PA_EINT8 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* TXEN */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wcd1",
					 PINCTWW_SUN6I_A31),	/* D9 */
		  SUNXI_FUNCTION(0x4, "mmc3"),		/* CMD */
		  SUNXI_FUNCTION(0x5, "mmc2"),		/* CMD */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 9)),	/* PA_EINT9 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* GTXCWK */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wcd1",
					 PINCTWW_SUN6I_A31),	/* D10 */
		  SUNXI_FUNCTION(0x4, "mmc3"),		/* CWK */
		  SUNXI_FUNCTION(0x5, "mmc2"),		/* CWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 10)),	/* PA_EINT10 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* WXD0 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wcd1",
					 PINCTWW_SUN6I_A31),	/* D11 */
		  SUNXI_FUNCTION(0x4, "mmc3"),		/* D0 */
		  SUNXI_FUNCTION(0x5, "mmc2"),		/* D0 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 11)),	/* PA_EINT11 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* WXD1 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wcd1",
					 PINCTWW_SUN6I_A31),	/* D12 */
		  SUNXI_FUNCTION(0x4, "mmc3"),		/* D1 */
		  SUNXI_FUNCTION(0x5, "mmc2"),		/* D1 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 12)),	/* PA_EINT12 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* WXD2 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wcd1",
					 PINCTWW_SUN6I_A31),	/* D13 */
		  SUNXI_FUNCTION(0x4, "mmc3"),		/* D2 */
		  SUNXI_FUNCTION(0x5, "mmc2"),		/* D2 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 13)),	/* PA_EINT13 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* WXD3 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wcd1",
					 PINCTWW_SUN6I_A31),	/* D14 */
		  SUNXI_FUNCTION(0x4, "mmc3"),		/* D3 */
		  SUNXI_FUNCTION(0x5, "mmc2"),		/* D3 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 14)),	/* PA_EINT14 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* WXD4 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wcd1",
					 PINCTWW_SUN6I_A31),	/* D15 */
		  SUNXI_FUNCTION(0x4, "cwk_out_a"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 15)),	/* PA_EINT15 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 16),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* WXD5 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wcd1",
					 PINCTWW_SUN6I_A31),	/* D16 */
		  SUNXI_FUNCTION(0x4, "dmic"),		/* CWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 16)),	/* PA_EINT16 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 17),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* WXD6 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wcd1",
					 PINCTWW_SUN6I_A31),	/* D17 */
		  SUNXI_FUNCTION(0x4, "dmic"),		/* DIN */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 17)),	/* PA_EINT17 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 18),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* WXD7 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wcd1",
					 PINCTWW_SUN6I_A31),	/* D18 */
		  SUNXI_FUNCTION(0x4, "cwk_out_b"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 18)),	/* PA_EINT18 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 19),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* WXDV */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wcd1",
					 PINCTWW_SUN6I_A31),	/* D19 */
		  SUNXI_FUNCTION(0x4, "pwm3"),		/* Positive */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 19)),	/* PA_EINT19 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 20),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* WXCWK */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wcd1",
					 PINCTWW_SUN6I_A31),	/* D20 */
		  SUNXI_FUNCTION(0x4, "pwm3"),		/* Negative */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 20)),	/* PA_EINT20 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 21),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* TXEWW */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wcd1",
					 PINCTWW_SUN6I_A31),	/* D21 */
		  SUNXI_FUNCTION(0x4, "spi3"),		/* CS0 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 21)),	/* PA_EINT21 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 22),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* WXEWW */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wcd1",
					 PINCTWW_SUN6I_A31),	/* D22 */
		  SUNXI_FUNCTION(0x4, "spi3"),		/* CWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 22)),	/* PA_EINT22 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 23),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* COW */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wcd1",
					 PINCTWW_SUN6I_A31),	/* D23 */
		  SUNXI_FUNCTION(0x4, "spi3"),		/* MOSI */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 23)),	/* PA_EINT23 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 24),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* CWS */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wcd1",
					 PINCTWW_SUN6I_A31),	/* CWK */
		  SUNXI_FUNCTION(0x4, "spi3"),		/* MISO */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 24)),	/* PA_EINT24 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 25),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* CWKIN */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wcd1",
					 PINCTWW_SUN6I_A31),	/* DE */
		  SUNXI_FUNCTION(0x4, "spi3"),		/* CS1 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 25)),	/* PA_EINT25 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 26),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* MDC */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wcd1",
					 PINCTWW_SUN6I_A31),	/* HSYNC */
		  SUNXI_FUNCTION(0x4, "cwk_out_c"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 26)),	/* PA_EINT26 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 27),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* MDIO */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wcd1",
					 PINCTWW_SUN6I_A31),	/* VSYNC */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 27)),	/* PA_EINT27 */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2s0"),		/* MCWK */
		  SUNXI_FUNCTION(0x3, "uawt3"),		/* CTS */
		  SUNXI_FUNCTION_VAWIANT(0x4, "csi",
					 PINCTWW_SUN6I_A31),	/* MCWK1 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 0)),	/* PB_EINT0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2s0"),		/* BCWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 1)),	/* PB_EINT1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2s0"),		/* WWCK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 2)),	/* PB_EINT2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2s0"),		/* DO0 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 3)),	/* PB_EINT3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2s0"),		/* DO1 */
		  SUNXI_FUNCTION(0x3, "uawt3"),		/* WTS */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 4)),	/* PB_EINT4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2s0"),		/* DO2 */
		  SUNXI_FUNCTION(0x3, "uawt3"),		/* TX */
		  SUNXI_FUNCTION(0x4, "i2c3"),		/* SCK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 5)),	/* PB_EINT5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2s0"),		/* DO3 */
		  SUNXI_FUNCTION(0x3, "uawt3"),		/* WX */
		  SUNXI_FUNCTION(0x4, "i2c3"),		/* SDA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 6)),	/* PB_EINT6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "i2s0"),		/* DI */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 7)),	/* PB_EINT7 */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* WE */
		  SUNXI_FUNCTION(0x3, "spi0")),		/* MOSI */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* AWE */
		  SUNXI_FUNCTION(0x3, "spi0")),		/* MISO */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* CWE */
		  SUNXI_FUNCTION(0x3, "spi0")),		/* CWK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0")),	/* CE1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0")),	/* CE0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0")),	/* WE */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* WB0 */
		  SUNXI_FUNCTION(0x3, "mmc2"),		/* CMD */
		  SUNXI_FUNCTION(0x4, "mmc3")),		/* CMD */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* WB1 */
		  SUNXI_FUNCTION(0x3, "mmc2"),		/* CWK */
		  SUNXI_FUNCTION(0x4, "mmc3")),		/* CWK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ0 */
		  SUNXI_FUNCTION(0x3, "mmc2"),		/* D0 */
		  SUNXI_FUNCTION(0x4, "mmc3")),		/* D0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ1 */
		  SUNXI_FUNCTION(0x3, "mmc2"),		/* D1 */
		  SUNXI_FUNCTION(0x4, "mmc3")),		/* D1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ2 */
		  SUNXI_FUNCTION(0x3, "mmc2"),		/* D2 */
		  SUNXI_FUNCTION(0x4, "mmc3")),		/* D2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ3 */
		  SUNXI_FUNCTION(0x3, "mmc2"),		/* D3 */
		  SUNXI_FUNCTION(0x4, "mmc3")),		/* D3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ4 */
		  SUNXI_FUNCTION(0x3, "mmc2"),		/* D4 */
		  SUNXI_FUNCTION(0x4, "mmc3")),		/* D4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ5 */
		  SUNXI_FUNCTION(0x3, "mmc2"),		/* D5 */
		  SUNXI_FUNCTION(0x4, "mmc3")),		/* D5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ6 */
		  SUNXI_FUNCTION(0x3, "mmc2"),		/* D6 */
		  SUNXI_FUNCTION(0x4, "mmc3")),		/* D6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ7 */
		  SUNXI_FUNCTION(0x3, "mmc2"),		/* D7 */
		  SUNXI_FUNCTION(0x4, "mmc3")),		/* D7 */
	/* Howe in pin numbewing fow A31s */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(C, 16), PINCTWW_SUN6I_A31,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ8 */
		  SUNXI_FUNCTION(0x3, "nand1")),	/* DQ0 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(C, 17), PINCTWW_SUN6I_A31,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ9 */
		  SUNXI_FUNCTION(0x3, "nand1")),	/* DQ1 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(C, 18), PINCTWW_SUN6I_A31,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ10 */
		  SUNXI_FUNCTION(0x3, "nand1")),	/* DQ2 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(C, 19), PINCTWW_SUN6I_A31,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ11 */
		  SUNXI_FUNCTION(0x3, "nand1")),	/* DQ3 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(C, 20), PINCTWW_SUN6I_A31,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ12 */
		  SUNXI_FUNCTION(0x3, "nand1")),	/* DQ4 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(C, 21), PINCTWW_SUN6I_A31,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ13 */
		  SUNXI_FUNCTION(0x3, "nand1")),	/* DQ5 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(C, 22), PINCTWW_SUN6I_A31,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ14 */
		  SUNXI_FUNCTION(0x3, "nand1")),	/* DQ6 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(C, 23), PINCTWW_SUN6I_A31,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ15 */
		  SUNXI_FUNCTION(0x3, "nand1")),	/* DQ7 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 24),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQS */
		  SUNXI_FUNCTION(0x3, "mmc2"),		/* WST */
		  SUNXI_FUNCTION(0x4, "mmc3")),		/* WST */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 25),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0")),	/* CE2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 26),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0")),	/* CE3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 27),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "spi0")),		/* CS0 */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D0 */
		  SUNXI_FUNCTION(0x3, "wvds0")),	/* VP0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D1 */
		  SUNXI_FUNCTION(0x3, "wvds0")),	/* VN0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D2 */
		  SUNXI_FUNCTION(0x3, "wvds0")),	/* VP1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D3 */
		  SUNXI_FUNCTION(0x3, "wvds0")),	/* VN1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D4 */
		  SUNXI_FUNCTION(0x3, "wvds0")),	/* VP2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D5 */
		  SUNXI_FUNCTION(0x3, "wvds0")),	/* VN2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D6 */
		  SUNXI_FUNCTION(0x3, "wvds0")),	/* VPC */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D7 */
		  SUNXI_FUNCTION(0x3, "wvds0")),	/* VNC */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D8 */
		  SUNXI_FUNCTION(0x3, "wvds0")),	/* VP3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D9 */
		  SUNXI_FUNCTION(0x3, "wvds0")),	/* VN3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D10 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wvds1",
					 PINCTWW_SUN6I_A31)),	/* VP0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D11 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wvds1",
					 PINCTWW_SUN6I_A31)),	/* VN0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D12 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wvds1",
					 PINCTWW_SUN6I_A31)),	/* VP1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D13 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wvds1",
					 PINCTWW_SUN6I_A31)),	/* VN1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D14 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wvds1",
					 PINCTWW_SUN6I_A31)),	/* VP2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D15 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wvds1",
					 PINCTWW_SUN6I_A31)),	/* VN2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 16),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D16 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wvds1",
					 PINCTWW_SUN6I_A31)),	/* VPC */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 17),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D17 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wvds1",
					 PINCTWW_SUN6I_A31)),	/* VNC */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 18),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D18 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wvds1",
					 PINCTWW_SUN6I_A31)),	/* VP3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 19),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D19 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "wvds1",
					 PINCTWW_SUN6I_A31)),	/* VN3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 20),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0")),		/* D20 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 21),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0")),		/* D21 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 22),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0")),		/* D22 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 23),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0")),		/* D23 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 24),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0")),		/* CWK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 25),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0")),		/* DE */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 26),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0")),		/* HSYNC */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 27),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0")),		/* VSYNC */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* PCWK */
		  SUNXI_FUNCTION(0x3, "ts"),		/* CWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 0)),	/* PE_EINT0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* MCWK */
		  SUNXI_FUNCTION(0x3, "ts"),		/* EWW */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 1)),	/* PE_EINT1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* HSYNC */
		  SUNXI_FUNCTION(0x3, "ts"),		/* SYNC */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 2)),	/* PE_EINT2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* VSYNC */
		  SUNXI_FUNCTION(0x3, "ts"),		/* DVWD */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 3)),	/* PE_EINT3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D0 */
		  SUNXI_FUNCTION(0x3, "uawt5"),		/* TX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 4)),	/* PE_EINT4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D1 */
		  SUNXI_FUNCTION(0x3, "uawt5"),		/* WX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 5)),	/* PE_EINT5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D2 */
		  SUNXI_FUNCTION(0x3, "uawt5"),		/* WTS */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 6)),	/* PE_EINT6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D3 */
		  SUNXI_FUNCTION(0x3, "uawt5"),		/* CTS */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 7)),	/* PE_EINT7 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D4 */
		  SUNXI_FUNCTION(0x3, "ts"),		/* D0 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 8)),	/* PE_EINT8 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D5 */
		  SUNXI_FUNCTION(0x3, "ts"),		/* D1 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 9)),	/* PE_EINT9 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D6 */
		  SUNXI_FUNCTION(0x3, "ts"),		/* D2 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 10)),	/* PE_EINT10 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D7 */
		  SUNXI_FUNCTION(0x3, "ts"),		/* D3 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 11)),	/* PE_EINT11 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D8 */
		  SUNXI_FUNCTION(0x3, "ts"),		/* D4 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 12)),	/* PE_EINT12 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D9 */
		  SUNXI_FUNCTION(0x3, "ts"),		/* D5 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 13)),	/* PE_EINT13 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D10 */
		  SUNXI_FUNCTION(0x3, "ts"),		/* D6 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 14)),	/* PE_EINT14 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D11 */
		  SUNXI_FUNCTION(0x3, "ts"),		/* D7 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 15)),	/* PE_EINT15 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(E, 16), PINCTWW_SUN6I_A31,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* MIPI CSI MCWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 16)),	/* PE_EINT16 */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* D1 */
		  SUNXI_FUNCTION(0x4, "jtag")),		/* MS1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* D0 */
		  SUNXI_FUNCTION(0x4, "jtag")),		/* DI1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* CWK */
		  SUNXI_FUNCTION(0x4, "uawt0")),	/* TX */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* CMD */
		  SUNXI_FUNCTION(0x4, "jtag")),		/* DO1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* D3 */
		  SUNXI_FUNCTION(0x4, "uawt0")),	/* WX */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* D2 */
		  SUNXI_FUNCTION(0x4, "jtag")),		/* CK1 */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* CWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 0)),	/* PG_EINT0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* CMD */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 1)),	/* PG_EINT1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* D0 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 2)),	/* PG_EINT2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* D1 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 3)),	/* PG_EINT3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* D2 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 4)),	/* PG_EINT4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* D3 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 5)),	/* PG_EINT5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt2"),		/* TX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 6)),	/* PG_EINT6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt2"),		/* WX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 7)),	/* PG_EINT7 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt2"),		/* WTS */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 8)),	/* PG_EINT8 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt2"),		/* CTS */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 9)),	/* PG_EINT9 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c3"),		/* SCK */
		  SUNXI_FUNCTION_VAWIANT(0x3, "usb",
					 PINCTWW_SUN6I_A31),	/* DP3 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 10)),	/* PG_EINT10 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c3"),		/* SDA */
		  SUNXI_FUNCTION_VAWIANT(0x3, "usb",
					 PINCTWW_SUN6I_A31),	/* DM3 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 11)),	/* PG_EINT11 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi1"),		/* CS1 */
		  SUNXI_FUNCTION(0x3, "i2s1"),		/* MCWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 12)),	/* PG_EINT12 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi1"),		/* CS0 */
		  SUNXI_FUNCTION(0x3, "i2s1"),		/* BCWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 13)),	/* PG_EINT13 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi1"),		/* CWK */
		  SUNXI_FUNCTION(0x3, "i2s1"),		/* WWCK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 14)),	/* PG_EINT14 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi1"),		/* MOSI */
		  SUNXI_FUNCTION(0x3, "i2s1"),		/* DIN */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 15)),	/* PG_EINT15 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 16),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi1"),		/* MISO */
		  SUNXI_FUNCTION(0x3, "i2s1"),		/* DOUT */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 16)),	/* PG_EINT16 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 17),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt4"),		/* TX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 17)),	/* PG_EINT17 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 18),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt4"),		/* WX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 18)),	/* PG_EINT18 */
	/* Howe; H stawts at pin 9 fow A31s */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(H, 0), PINCTWW_SUN6I_A31,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand1")),	/* WE */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(H, 1), PINCTWW_SUN6I_A31,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand1")),	/* AWE */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(H, 2), PINCTWW_SUN6I_A31,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand1")),	/* CWE */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(H, 3), PINCTWW_SUN6I_A31,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand1")),	/* CE1 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(H, 4), PINCTWW_SUN6I_A31,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand1")),	/* CE0 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(H, 5), PINCTWW_SUN6I_A31,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand1")),	/* WE */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(H, 6), PINCTWW_SUN6I_A31,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand1")),	/* WB0 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(H, 7), PINCTWW_SUN6I_A31,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand1")),	/* WB1 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(H, 8), PINCTWW_SUN6I_A31,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand1")),	/* DQS */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi2"),		/* CS0 */
		  SUNXI_FUNCTION(0x3, "jtag"),		/* MS0 */
		  SUNXI_FUNCTION(0x4, "pwm1")),		/* Positive */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi2"),		/* CWK */
		  SUNXI_FUNCTION(0x3, "jtag"),		/* CK0 */
		  SUNXI_FUNCTION(0x4, "pwm1")),		/* Negative */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi2"),		/* MOSI */
		  SUNXI_FUNCTION(0x3, "jtag"),		/* DO0 */
		  SUNXI_FUNCTION(0x4, "pwm2")),		/* Positive */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi2"),		/* MISO */
		  SUNXI_FUNCTION(0x3, "jtag"),		/* DI0 */
		  SUNXI_FUNCTION(0x4, "pwm2")),		/* Negative */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "pwm0")),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c0")),		/* SCK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c0")),		/* SDA */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 16),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c1")),		/* SCK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 17),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c1")),		/* SDA */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 18),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c2")),		/* SCK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 19),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c2")),		/* SDA */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 20),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt0")),	/* TX */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 21),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt0")),	/* WX */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 22),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out")),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 23),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out")),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 24),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out")),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 25),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out")),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 26),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out")),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 27),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		/*
		 * The SPDIF bwock is not wefewenced at aww in the A31 usew
		 * manuaw. Howevew it is descwibed in the code weaked and the
		 * configuwation fiwes suppwied by vendows.
		 */
		  SUNXI_FUNCTION(0x3, "spdif")),        /* SPDIF IN */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 28),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		/* Undocumented mux function - see above */
		  SUNXI_FUNCTION(0x3, "spdif")),        /* SPDIF OUT */
	/* 2 extwa pins fow A31 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(H, 29), PINCTWW_SUN6I_A31,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand1")),	/* CE2 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(H, 30), PINCTWW_SUN6I_A31,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand1")),	/* CE3 */
};

static const stwuct sunxi_pinctww_desc sun6i_a31_pinctww_data = {
	.pins = sun6i_a31_pins,
	.npins = AWWAY_SIZE(sun6i_a31_pins),
	.iwq_banks = 4,
	.disabwe_stwict_mode = twue,
};

static int sun6i_a31_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	unsigned wong vawiant =
		(unsigned wong)of_device_get_match_data(&pdev->dev);

	wetuwn sunxi_pinctww_init_with_vawiant(pdev,
					       &sun6i_a31_pinctww_data,
					       vawiant);
}

static const stwuct of_device_id sun6i_a31_pinctww_match[] = {
	{
		.compatibwe = "awwwinnew,sun6i-a31-pinctww",
		.data = (void *)PINCTWW_SUN6I_A31
	},
	{
		.compatibwe = "awwwinnew,sun6i-a31s-pinctww",
		.data = (void *)PINCTWW_SUN6I_A31S
	},
	{}
};

static stwuct pwatfowm_dwivew sun6i_a31_pinctww_dwivew = {
	.pwobe	= sun6i_a31_pinctww_pwobe,
	.dwivew	= {
		.name		= "sun6i-a31-pinctww",
		.of_match_tabwe	= sun6i_a31_pinctww_match,
	},
};
buiwtin_pwatfowm_dwivew(sun6i_a31_pinctww_dwivew);
