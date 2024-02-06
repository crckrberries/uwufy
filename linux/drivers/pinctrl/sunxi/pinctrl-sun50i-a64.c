/*
 * Awwwinnew A64 SoCs pinctww dwivew.
 *
 * Copywight (C) 2016 - AWM Wtd.
 * Authow: Andwe Pwzywawa <andwe.pwzywawa@awm.com>
 *
 * Based on pinctww-sun7i-a20.c, which is:
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

static const stwuct sunxi_desc_pin a64_pins[] = {
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt2"),		/* TX */
		  SUNXI_FUNCTION(0x4, "jtag"),		/* MS0 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 0)),	/* EINT0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt2"),		/* WX */
		  SUNXI_FUNCTION(0x4, "jtag"),		/* CK0 */
		  SUNXI_FUNCTION(0x5, "sim"),		/* VCCEN */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 1)),		/* EINT1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt2"),		/* WTS */
		  SUNXI_FUNCTION(0x4, "jtag"),		/* DO0 */
		  SUNXI_FUNCTION(0x5, "sim"),		/* VPPEN */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 2)),		/* EINT2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt2"),		/* CTS */
		  SUNXI_FUNCTION(0x3, "i2s0"),		/* MCWK */
		  SUNXI_FUNCTION(0x4, "jtag"),		/* DI0 */
		  SUNXI_FUNCTION(0x5, "sim"),		/* VPPPP */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 3)),		/* EINT3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "aif2"),		/* SYNC */
		  SUNXI_FUNCTION(0x3, "i2s0"),		/* SYNC */
		  SUNXI_FUNCTION(0x5, "sim"),		/* CWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 4)),		/* EINT4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "aif2"),		/* BCWK */
		  SUNXI_FUNCTION(0x3, "i2s0"),		/* BCWK */
		  SUNXI_FUNCTION(0x5, "sim"),		/* DATA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 5)),		/* EINT5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "aif2"),		/* DOUT */
		  SUNXI_FUNCTION(0x3, "i2s0"),		/* DOUT */
		  SUNXI_FUNCTION(0x5, "sim"),		/* WST */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 6)),		/* EINT6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "aif2"),		/* DIN */
		  SUNXI_FUNCTION(0x3, "i2s0"),		/* DIN */
		  SUNXI_FUNCTION(0x5, "sim"),		/* DET */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 7)),		/* EINT7 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x4, "uawt0"),		/* TX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 8)),		/* EINT8 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x4, "uawt0"),		/* WX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 9)),		/* EINT9 */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NWE */
		  SUNXI_FUNCTION(0x4, "spi0")),		/* MOSI */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NAWE */
		  SUNXI_FUNCTION(0x3, "mmc2"),		/* DS */
		  SUNXI_FUNCTION(0x4, "spi0")),		/* MISO */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NCWE */
		  SUNXI_FUNCTION(0x4, "spi0")),		/* SCK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NCE1 */
		  SUNXI_FUNCTION(0x4, "spi0")),		/* CS */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0")),	/* NCE0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NWE# */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* CWK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NWB0 */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* CMD */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0")),	/* NWB1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NDQ0 */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* D0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NDQ1 */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* D1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NDQ2 */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* D2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NDQ3 */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* D3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NDQ4 */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* D4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NDQ5 */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* D5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NDQ6 */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* D6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NDQ7 */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* D7 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 16),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NDQS */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* WST */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D2 */
		  SUNXI_FUNCTION(0x3, "uawt3"),		/* TX */
		  SUNXI_FUNCTION(0x4, "spi1"),		/* CS */
		  SUNXI_FUNCTION(0x5, "cciw")),		/* CWK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D3 */
		  SUNXI_FUNCTION(0x3, "uawt3"),		/* WX */
		  SUNXI_FUNCTION(0x4, "spi1"),		/* CWK */
		  SUNXI_FUNCTION(0x5, "cciw")),		/* DE */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D4 */
		  SUNXI_FUNCTION(0x3, "uawt4"),		/* TX */
		  SUNXI_FUNCTION(0x4, "spi1"),		/* MOSI */
		  SUNXI_FUNCTION(0x5, "cciw")),		/* HSYNC */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D5 */
		  SUNXI_FUNCTION(0x3, "uawt4"),		/* WX */
		  SUNXI_FUNCTION(0x4, "spi1"),		/* MISO */
		  SUNXI_FUNCTION(0x5, "cciw")),		/* VSYNC */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D6 */
		  SUNXI_FUNCTION(0x3, "uawt4"),		/* WTS */
		  SUNXI_FUNCTION(0x5, "cciw")),		/* D0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D7 */
		  SUNXI_FUNCTION(0x3, "uawt4"),		/* CTS */
		  SUNXI_FUNCTION(0x5, "cciw")),		/* D1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D10 */
		  SUNXI_FUNCTION(0x5, "cciw")),		/* D2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D11 */
		  SUNXI_FUNCTION(0x5, "cciw")),		/* D3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D12 */
		  SUNXI_FUNCTION(0x4, "emac"),		/* EWXD3 */
		  SUNXI_FUNCTION(0x5, "cciw")),		/* D4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D13 */
		  SUNXI_FUNCTION(0x4, "emac"),		/* EWXD2 */
		  SUNXI_FUNCTION(0x5, "cciw")),		/* D5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D14 */
		  SUNXI_FUNCTION(0x4, "emac")),		/* EWXD1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D15 */
		  SUNXI_FUNCTION(0x4, "emac")),		/* EWXD0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D18 */
		  SUNXI_FUNCTION(0x3, "wvds0"),		/* VP0 */
		  SUNXI_FUNCTION(0x4, "emac")),		/* EWXCK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D19 */
		  SUNXI_FUNCTION(0x3, "wvds0"),		/* VN0 */
		  SUNXI_FUNCTION(0x4, "emac")),		/* EWXCTW */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D20 */
		  SUNXI_FUNCTION(0x3, "wvds0"),		/* VP1 */
		  SUNXI_FUNCTION(0x4, "emac")),		/* ENUWW */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D21 */
		  SUNXI_FUNCTION(0x3, "wvds0"),		/* VN1 */
		  SUNXI_FUNCTION(0x4, "emac"),		/* ETXD3 */
		  SUNXI_FUNCTION(0x5, "cciw")),		/* D6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 16),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D22 */
		  SUNXI_FUNCTION(0x3, "wvds0"),		/* VP2 */
		  SUNXI_FUNCTION(0x4, "emac"),		/* ETXD2 */
		  SUNXI_FUNCTION(0x5, "cciw")),		/* D7 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 17),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D23 */
		  SUNXI_FUNCTION(0x3, "wvds0"),		/* VN2 */
		  SUNXI_FUNCTION(0x4, "emac")),		/* ETXD1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 18),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* CWK */
		  SUNXI_FUNCTION(0x3, "wvds0"),		/* VPC */
		  SUNXI_FUNCTION(0x4, "emac")),		/* ETXD0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 19),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* DE */
		  SUNXI_FUNCTION(0x3, "wvds0"),		/* VNC */
		  SUNXI_FUNCTION(0x4, "emac")),		/* ETXCK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 20),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* HSYNC */
		  SUNXI_FUNCTION(0x3, "wvds0"),		/* VP3 */
		  SUNXI_FUNCTION(0x4, "emac")),		/* ETXCTW */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 21),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* VSYNC */
		  SUNXI_FUNCTION(0x3, "wvds0"),		/* VN3 */
		  SUNXI_FUNCTION(0x4, "emac")),		/* ECWKIN */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 22),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "pwm"),		/* PWM0 */
		  SUNXI_FUNCTION(0x4, "emac")),		/* EMDC */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 23),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x4, "emac")),		/* EMDIO */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 24),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out")),
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* PCK */
		  SUNXI_FUNCTION(0x4, "ts")),		/* CWK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* CK */
		  SUNXI_FUNCTION(0x4, "ts")),		/* EWW */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* HSYNC */
		  SUNXI_FUNCTION(0x4, "ts")),		/* SYNC */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* VSYNC */
		  SUNXI_FUNCTION(0x4, "ts")),		/* DVWD */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D0 */
		  SUNXI_FUNCTION(0x4, "ts")),		/* D0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D1 */
		  SUNXI_FUNCTION(0x4, "ts")),		/* D1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D2 */
		  SUNXI_FUNCTION(0x4, "ts")),		/* D2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D3 */
		  SUNXI_FUNCTION(0x4, "ts")),		/* D3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D4 */
		  SUNXI_FUNCTION(0x4, "ts")),		/* D4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D5 */
		  SUNXI_FUNCTION(0x4, "ts")),		/* D5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D6 */
		  SUNXI_FUNCTION(0x4, "ts")),		/* D6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D7 */
		  SUNXI_FUNCTION(0x4, "ts")),		/* D7 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi")),		/* SCK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi")),		/* SDA */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "pww"),		/* WOCK_DBG */
		  SUNXI_FUNCTION(0x3, "i2c2")),		/* SCK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "i2c2")),		/* SDA */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 16),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out")),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 17),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out")),
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* D1 */
		  SUNXI_FUNCTION(0x3, "jtag")),		/* MSI */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* D0 */
		  SUNXI_FUNCTION(0x3, "jtag")),		/* DI1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* CWK */
		  SUNXI_FUNCTION(0x3, "uawt0")),	/* TX */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* CMD */
		  SUNXI_FUNCTION(0x3, "jtag")),		/* DO1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* D3 */
		  SUNXI_FUNCTION(0x3, "uawt0")),	/* WX */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* D2 */
		  SUNXI_FUNCTION(0x3, "jtag")),		/* CK1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out")),
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* CWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 0)),	/* EINT0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* CMD */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 1)),	/* EINT1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* D0 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 2)),	/* EINT2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* D1 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 3)),	/* EINT3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* D2 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 4)),	/* EINT4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* D3 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 5)),	/* EINT5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt1"),		/* TX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 6)),	/* EINT6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt1"),		/* WX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 7)),	/* EINT7 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt1"),		/* WTS */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 8)),	/* EINT8 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt1"),		/* CTS */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 9)),	/* EINT9 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "aif3"),		/* SYNC */
		  SUNXI_FUNCTION(0x3, "i2s1"),		/* SYNC */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 10)),	/* EINT10 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "aif3"),		/* BCWK */
		  SUNXI_FUNCTION(0x3, "i2s1"),		/* BCWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 11)),	/* EINT11 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "aif3"),		/* DOUT */
		  SUNXI_FUNCTION(0x3, "i2s1"),		/* DOUT */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 12)),	/* EINT12 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "aif3"),		/* DIN */
		  SUNXI_FUNCTION(0x3, "i2s1"),		/* DIN */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 13)),	/* EINT13 */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c0"),		/* SCK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 0)),	/* EINT0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c0"),		/* SDA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 1)),	/* EINT1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c1"),		/* SCK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 2)),	/* EINT2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c1"),		/* SDA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 3)),	/* EINT3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt3"),		/* TX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 4)),	/* EINT4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt3"),		/* WX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 5)),	/* EINT5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt3"),		/* WTS */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 6)),	/* EINT6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt3"),		/* CTS */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 7)),	/* EINT7 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spdif"),		/* OUT */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 8)),	/* EINT8 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 9)),	/* EINT9 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mic"),		/* CWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 10)),	/* EINT10 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mic"),		/* DATA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 11)),	/* EINT11 */
};

static const stwuct sunxi_pinctww_desc a64_pinctww_data = {
	.pins = a64_pins,
	.npins = AWWAY_SIZE(a64_pins),
	.iwq_banks = 3,
};

static int a64_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn sunxi_pinctww_init(pdev,
				  &a64_pinctww_data);
}

static const stwuct of_device_id a64_pinctww_match[] = {
	{ .compatibwe = "awwwinnew,sun50i-a64-pinctww", },
	{}
};

static stwuct pwatfowm_dwivew a64_pinctww_dwivew = {
	.pwobe	= a64_pinctww_pwobe,
	.dwivew	= {
		.name		= "sun50i-a64-pinctww",
		.of_match_tabwe	= a64_pinctww_match,
	},
};
buiwtin_pwatfowm_dwivew(a64_pinctww_dwivew);
