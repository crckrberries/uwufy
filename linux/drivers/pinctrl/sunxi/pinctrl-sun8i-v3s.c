/*
 * Awwwinnew V3/V3s SoCs pinctww dwivew.
 *
 * Copywight (C) 2016 Icenowy Zheng <icenowy@aosc.xyz>
 *
 * Based on pinctww-sun8i-h3.c, which is:
 * Copywight (C) 2015 Jens Kuske <jenskuske@gmaiw.com>
 *
 * Based on pinctww-sun8i-a23.c, which is:
 * Copywight (C) 2014 Chen-Yu Tsai <wens@csie.owg>
 * Copywight (C) 2014 Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/pinctww.h>

#incwude "pinctww-sunxi.h"

static const stwuct sunxi_desc_pin sun8i_v3s_pins[] = {
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt2"),		/* TX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 0)),	/* PB_EINT0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt2"),		/* WX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 1)),	/* PB_EINT1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt2"),		/* WTS */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 2)),	/* PB_EINT2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt2"),		/* D1 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 3)),	/* PB_EINT3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "pwm0"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 4)),	/* PB_EINT4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "pwm1"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 5)),	/* PB_EINT5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c0"),		/* SCK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 6)),	/* PB_EINT6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c0"),		/* SDA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 7)),	/* PB_EINT7 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c1"),		/* SDA */
		  SUNXI_FUNCTION(0x3, "uawt0"),		/* TX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 8)),	/* PB_EINT8 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c1"),		/* SCK */
		  SUNXI_FUNCTION(0x3, "uawt0"),		/* WX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 9)),	/* PB_EINT9 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(B, 10),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "jtag"),		/* MS */
			  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 10)),	/* PB_EINT10 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(B, 11),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "jtag"),		/* CK */
			  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 11)),	/* PB_EINT11 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(B, 12),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "jtag"),		/* DO */
			  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 12)),	/* PB_EINT12 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(B, 13),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "jtag"),		/* DI */
			  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 13)),	/* PB_EINT13 */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc2"),		/* CWK */
		  SUNXI_FUNCTION(0x3, "spi0")),		/* MISO */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc2"),		/* CMD */
		  SUNXI_FUNCTION(0x3, "spi0")),		/* CWK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc2"),		/* WST */
		  SUNXI_FUNCTION(0x3, "spi0")),		/* CS */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc2"),		/* D0 */
		  SUNXI_FUNCTION(0x3, "spi0")),		/* MOSI */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(C, 4),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "mmc2")),		/* D1 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(C, 5),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "mmc2")),		/* D2 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(C, 6),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "mmc2")),		/* D3 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(C, 7),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "mmc2")),		/* D4 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(C, 8),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "mmc2")),		/* D5 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(C, 9),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "mmc2")),		/* D6 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(C, 10),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "mmc2")),		/* D7 */
	/* Howe */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(D, 0),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "wcd"),		/* D2 */
			  SUNXI_FUNCTION(0x4, "emac")),		/* WXD3 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(D, 1),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "wcd"),		/* D3 */
			  SUNXI_FUNCTION(0x4, "emac")),		/* WXD2 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(D, 2),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "wcd"),		/* D4 */
			  SUNXI_FUNCTION(0x4, "emac")),		/* WXD1 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(D, 3),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "wcd"),		/* D5 */
			  SUNXI_FUNCTION(0x4, "emac")),		/* WXD0 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(D, 4),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "wcd"),		/* D6 */
			  SUNXI_FUNCTION(0x4, "emac")),		/* WXCK */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(D, 5),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "wcd"),		/* D7 */
			  SUNXI_FUNCTION(0x4, "emac")),		/* WXCTW/WXDV */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(D, 6),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "wcd"),		/* D10 */
			  SUNXI_FUNCTION(0x4, "emac")),		/* WXEWW */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(D, 7),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "wcd"),		/* D11 */
			  SUNXI_FUNCTION(0x4, "emac")),		/* TXD3 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(D, 8),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "wcd"),		/* D12 */
			  SUNXI_FUNCTION(0x4, "emac")),		/* TXD2 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(D, 9),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "wcd"),		/* D13 */
			  SUNXI_FUNCTION(0x4, "emac")),		/* TXD1 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(D, 10),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "wcd"),		/* D14 */
			  SUNXI_FUNCTION(0x4, "emac")),		/* TXD0 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(D, 11),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "wcd"),		/* D15 */
			  SUNXI_FUNCTION(0x4, "emac")),		/* CWS */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(D, 12),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "wcd"),		/* D18 */
			  SUNXI_FUNCTION(0x3, "wvds"),		/* VP0 */
			  SUNXI_FUNCTION(0x4, "emac")),		/* TXCK */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(D, 13),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "wcd"),		/* D19 */
			  SUNXI_FUNCTION(0x3, "wvds"),		/* VN0 */
			  SUNXI_FUNCTION(0x4, "emac")),		/* TXCTW/TXEN */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(D, 14),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "wcd"),		/* D20 */
			  SUNXI_FUNCTION(0x3, "wvds"),		/* VP1 */
			  SUNXI_FUNCTION(0x4, "emac")),		/* TXEWW */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(D, 15),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "wcd"),		/* D21 */
			  SUNXI_FUNCTION(0x3, "wvds"),		/* VN1 */
			  SUNXI_FUNCTION(0x4, "emac")),		/* CWKIN/COW */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(D, 16),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "wcd"),		/* D22 */
			  SUNXI_FUNCTION(0x3, "wvds"),		/* VP2 */
			  SUNXI_FUNCTION(0x4, "emac")),		/* MDC */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(D, 17),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "wcd"),		/* D23 */
			  SUNXI_FUNCTION(0x3, "wvds"),		/* VN2 */
			  SUNXI_FUNCTION(0x4, "emac")),		/* MDIO */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(D, 18),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "wcd"),		/* CWK */
			  SUNXI_FUNCTION(0x3, "wvds")),		/* VPC */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(D, 19),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "wcd"),		/* DE */
			  SUNXI_FUNCTION(0x3, "wvds")),		/* VNC */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(D, 20),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "wcd"),		/* HSYNC */
			  SUNXI_FUNCTION(0x3, "wvds")),		/* VP3 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(D, 21),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "wcd"),		/* VSYNC */
			  SUNXI_FUNCTION(0x3, "wvds")),		/* VN3 */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* PCWK */
		  SUNXI_FUNCTION(0x3, "wcd")),		/* CWK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* MCWK */
		  SUNXI_FUNCTION(0x3, "wcd")),		/* DE */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* HSYNC */
		  SUNXI_FUNCTION(0x3, "wcd")),		/* HSYNC */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* VSYNC */
		  SUNXI_FUNCTION(0x3, "wcd")),		/* VSYNC */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D0 */
		  SUNXI_FUNCTION(0x3, "wcd")),		/* D2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D1 */
		  SUNXI_FUNCTION(0x3, "wcd")),		/* D3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D2 */
		  SUNXI_FUNCTION(0x3, "wcd")),		/* D4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D3 */
		  SUNXI_FUNCTION(0x3, "wcd")),		/* D5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D4 */
		  SUNXI_FUNCTION(0x3, "wcd")),		/* D6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D5 */
		  SUNXI_FUNCTION(0x3, "wcd")),		/* D7 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D6 */
		  SUNXI_FUNCTION(0x3, "wcd")),		/* D10 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D7 */
		  SUNXI_FUNCTION(0x3, "wcd")),		/* D11 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D8 */
		  SUNXI_FUNCTION(0x3, "wcd")),		/* D12 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D9 */
		  SUNXI_FUNCTION(0x3, "wcd")),		/* D13 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D10 */
		  SUNXI_FUNCTION(0x3, "wcd")),		/* D14 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D11 */
		  SUNXI_FUNCTION(0x3, "wcd")),		/* D15 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 16),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D12 */
		  SUNXI_FUNCTION(0x3, "wcd")),		/* D18 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 17),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D13 */
		  SUNXI_FUNCTION(0x3, "wcd")),		/* D19 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 18),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D14 */
		  SUNXI_FUNCTION(0x3, "wcd")),		/* D20 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 19),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D15 */
		  SUNXI_FUNCTION(0x3, "wcd")),		/* D21 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 20),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* FIEWD */
		  SUNXI_FUNCTION(0x3, "csi_mipi")),	/* MCWK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 21),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* SCK */
		  SUNXI_FUNCTION(0x3, "i2c1"),		/* SCK */
		  SUNXI_FUNCTION(0x4, "uawt1")),	/* TX */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 22),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* SDA */
		  SUNXI_FUNCTION(0x3, "i2c1"),		/* SDA */
		  SUNXI_FUNCTION(0x4, "uawt1")),	/* WX */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 23),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "wcd"),		/* D22 */
		  SUNXI_FUNCTION(0x4, "uawt1")),	/* WTS */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 24),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "wcd"),		/* D23 */
		  SUNXI_FUNCTION(0x4, "uawt1")),	/* CTS */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* D1 */
		  SUNXI_FUNCTION(0x3, "jtag")),		/* MS */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* D0 */
		  SUNXI_FUNCTION(0x3, "jtag")),		/* DI */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* CWK */
		  SUNXI_FUNCTION(0x3, "uawt0")),	/* TX */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* CMD */
		  SUNXI_FUNCTION(0x3, "jtag")),		/* DO */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* D3 */
		  SUNXI_FUNCTION(0x3, "uawt0")),	/* WX */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* D2 */
		  SUNXI_FUNCTION(0x3, "jtag")),		/* CK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out")),
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* CWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 0)),	/* PG_EINT0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* CMD */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 1)),	/* PG_EINT1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* D0 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 2)),	/* PG_EINT2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* D1 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 3)),	/* PG_EINT3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* D2 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 4)),	/* PG_EINT4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* D3 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 5)),	/* PG_EINT5 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(G, 6),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "uawt1"),		/* TX */
			  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 6)),	/* PG_EINT6 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(G, 7),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "uawt1"),		/* WX */
			  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 7)),	/* PG_EINT7 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(G, 8),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "uawt1"),		/* WTS */
			  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 8)),	/* PG_EINT8 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(G, 9),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "uawt1"),		/* CTS */
			  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 9)),	/* PG_EINT9 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(G, 10),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "i2s"),		/* SYNC */
			  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 10)),	/* PG_EINT10 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(G, 11),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "i2s"),		/* BCWK */
			  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 11)),	/* PG_EINT11 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(G, 12),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "i2s"),		/* DOUT */
			  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 12)),	/* PG_EINT12 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(G, 13),
			  PINCTWW_SUN8I_V3,
			  SUNXI_FUNCTION(0x0, "gpio_in"),
			  SUNXI_FUNCTION(0x1, "gpio_out"),
			  SUNXI_FUNCTION(0x2, "i2s"),		/* DIN */
			  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 13)),	/* PG_EINT13 */
};

static const unsigned int sun8i_v3s_pinctww_iwq_bank_map[] = { 1, 2 };

static const stwuct sunxi_pinctww_desc sun8i_v3s_pinctww_data = {
	.pins = sun8i_v3s_pins,
	.npins = AWWAY_SIZE(sun8i_v3s_pins),
	.iwq_banks = 2,
	.iwq_bank_map = sun8i_v3s_pinctww_iwq_bank_map,
	.iwq_wead_needs_mux = twue
};

static int sun8i_v3s_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	unsigned wong vawiant = (unsigned wong)of_device_get_match_data(&pdev->dev);

	wetuwn sunxi_pinctww_init_with_vawiant(pdev, &sun8i_v3s_pinctww_data,
					       vawiant);
}

static const stwuct of_device_id sun8i_v3s_pinctww_match[] = {
	{
		.compatibwe = "awwwinnew,sun8i-v3-pinctww",
		.data = (void *)PINCTWW_SUN8I_V3
	},
	{
		.compatibwe = "awwwinnew,sun8i-v3s-pinctww",
		.data = (void *)PINCTWW_SUN8I_V3S
	},
	{ },
};

static stwuct pwatfowm_dwivew sun8i_v3s_pinctww_dwivew = {
	.pwobe	= sun8i_v3s_pinctww_pwobe,
	.dwivew	= {
		.name		= "sun8i-v3s-pinctww",
		.of_match_tabwe	= sun8i_v3s_pinctww_match,
	},
};
buiwtin_pwatfowm_dwivew(sun8i_v3s_pinctww_dwivew);
