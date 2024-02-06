// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Awwwinnew H6 SoC pinctww dwivew.
 *
 * Copywight (C) 2017 Icenowy Zheng <icenowy@aosc.io>
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/pinctww.h>

#incwude "pinctww-sunxi.h"

static const stwuct sunxi_desc_pin h6_pins[] = {
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 0),
		  SUNXI_FUNCTION(0x2, "emac")),		/* EWXD1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 1),
		  SUNXI_FUNCTION(0x2, "emac")),		/* EWXD0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 2),
		  SUNXI_FUNCTION(0x2, "emac")),		/* ECWS_DV */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 3),
		  SUNXI_FUNCTION(0x2, "emac")),		/* EWXEWW */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 4),
		  SUNXI_FUNCTION(0x2, "emac")),		/* ETXD1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 5),
		  SUNXI_FUNCTION(0x2, "emac")),		/* ETXD0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 6),
		  SUNXI_FUNCTION(0x2, "emac")),		/* ETXCK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 7),
		  SUNXI_FUNCTION(0x2, "emac")),		/* ETXEN */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 8),
		  SUNXI_FUNCTION(0x2, "emac")),		/* EMDC */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 9),
		  SUNXI_FUNCTION(0x2, "emac")),		/* EMDIO */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 0),
		  SUNXI_FUNCTION(0x2, "cciw"),		/* CWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 0)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 1),
		  SUNXI_FUNCTION(0x2, "cciw"),		/* DE */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 1)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 2),
		  SUNXI_FUNCTION(0x2, "cciw"),		/* HSYNC */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 2)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 3),
		  SUNXI_FUNCTION(0x2, "cciw"),		/* VSYNC */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 3)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 4),
		  SUNXI_FUNCTION(0x2, "cciw"),		/* DO0 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 4)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 5),
		  SUNXI_FUNCTION(0x2, "cciw"),		/* DO1 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 5)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 6),
		  SUNXI_FUNCTION(0x2, "cciw"),		/* DO2 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 6)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 7),
		  SUNXI_FUNCTION(0x2, "cciw"),		/* DO3 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 7)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 8),
		  SUNXI_FUNCTION(0x2, "cciw"),		/* DO4 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 8)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 9),
		  SUNXI_FUNCTION(0x2, "cciw"),		/* DO5 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 9)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 10),
		  SUNXI_FUNCTION(0x2, "cciw"),		/* DO6 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 10)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 11),
		  SUNXI_FUNCTION(0x2, "cciw"),		/* DO7 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 11)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 12),
		  SUNXI_FUNCTION(0x2, "i2s3"),		/* SYNC */
		  SUNXI_FUNCTION(0x4, "h_i2s3"),	/* SYNC */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 12)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 13),
		  SUNXI_FUNCTION(0x2, "i2s3"),		/* CWK */
		  SUNXI_FUNCTION(0x4, "h_i2s3"),	/* CWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 13)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 14),
		  SUNXI_FUNCTION(0x2, "i2s3"),		/* DOUT */
		  SUNXI_FUNCTION(0x4, "h_i2s3"),	/* DOUT */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 14)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 15),
		  SUNXI_FUNCTION(0x2, "i2s3"),		/* DIN */
		  SUNXI_FUNCTION(0x4, "h_i2s3"),	/* DIN */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 15)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 16),
		  SUNXI_FUNCTION(0x2, "i2s3"),		/* MCWK */
		  SUNXI_FUNCTION(0x4, "h_i2s3"),	/* MCWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 16)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 17),
		  SUNXI_FUNCTION(0x2, "i2c3"),		/* SCK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 17)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 18),
		  SUNXI_FUNCTION(0x2, "i2c3"),		/* SDA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 18)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 19),
		  SUNXI_FUNCTION(0x2, "pwm1"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 19)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 20),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 20)),
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* WE */
		  SUNXI_FUNCTION(0x4, "spi0")),		/* CWK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* AWE */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* DS */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* CWE */
		  SUNXI_FUNCTION(0x4, "spi0")),		/* MOSI */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* CE0 */
		  SUNXI_FUNCTION(0x4, "spi0")),		/* MISO */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* WE */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* CWK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* WB0 */
		  SUNXI_FUNCTION(0x3, "mmc2"),		/* CMD */
		  SUNXI_FUNCTION(0x4, "spi0")),		/* CS */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ0 */
		  SUNXI_FUNCTION(0x3, "mmc2"),		/* D0 */
		  SUNXI_FUNCTION(0x4, "spi0")),		/* HOWD */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ1 */
		  SUNXI_FUNCTION(0x3, "mmc2"),		/* D1 */
		  SUNXI_FUNCTION(0x4, "spi0")),		/* WP */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ2 */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* D2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ3 */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* D3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ4 */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* D4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ5 */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* D5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ6 */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* D6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ7 */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* D7 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQS */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* WST */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0")),	/* CE1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 16),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0")),	/* WB1 */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D2 */
		  SUNXI_FUNCTION(0x3, "ts0"),		/* CWK */
		  SUNXI_FUNCTION(0x4, "csi"),		/* PCWK */
		  SUNXI_FUNCTION(0x5, "emac")),		/* EWXD3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D3 */
		  SUNXI_FUNCTION(0x3, "ts0"),		/* EWW */
		  SUNXI_FUNCTION(0x4, "csi"),		/* MCWK */
		  SUNXI_FUNCTION(0x5, "emac")),		/* EWXD2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D4 */
		  SUNXI_FUNCTION(0x3, "ts0"),		/* SYNC */
		  SUNXI_FUNCTION(0x4, "csi"),		/* HSYNC */
		  SUNXI_FUNCTION(0x5, "emac")),		/* EWXD1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D5 */
		  SUNXI_FUNCTION(0x3, "ts0"),		/* DVWD */
		  SUNXI_FUNCTION(0x4, "csi"),		/* VSYNC */
		  SUNXI_FUNCTION(0x5, "emac")),		/* EWXD0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D6 */
		  SUNXI_FUNCTION(0x3, "ts0"),		/* D0 */
		  SUNXI_FUNCTION(0x4, "csi"),		/* D0 */
		  SUNXI_FUNCTION(0x5, "emac")),		/* EWXCK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D7 */
		  SUNXI_FUNCTION(0x3, "ts0"),		/* D1 */
		  SUNXI_FUNCTION(0x4, "csi"),		/* D1 */
		  SUNXI_FUNCTION(0x5, "emac")),		/* EWXCTW */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D10 */
		  SUNXI_FUNCTION(0x3, "ts0"),		/* D2 */
		  SUNXI_FUNCTION(0x4, "csi"),		/* D2 */
		  SUNXI_FUNCTION(0x5, "emac")),		/* ENUWW */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D11 */
		  SUNXI_FUNCTION(0x3, "ts0"),		/* D3 */
		  SUNXI_FUNCTION(0x4, "csi"),		/* D3 */
		  SUNXI_FUNCTION(0x5, "emac")),		/* ETXD3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D12 */
		  SUNXI_FUNCTION(0x3, "ts0"),		/* D4 */
		  SUNXI_FUNCTION(0x4, "csi"),		/* D4 */
		  SUNXI_FUNCTION(0x5, "emac")),		/* ETXD2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D13 */
		  SUNXI_FUNCTION(0x3, "ts0"),		/* D5 */
		  SUNXI_FUNCTION(0x4, "csi"),		/* D5 */
		  SUNXI_FUNCTION(0x5, "emac")),		/* ETXD1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D14 */
		  SUNXI_FUNCTION(0x3, "ts0"),		/* D6 */
		  SUNXI_FUNCTION(0x4, "csi"),		/* D6 */
		  SUNXI_FUNCTION(0x5, "emac")),		/* ETXD0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D15 */
		  SUNXI_FUNCTION(0x3, "ts0"),		/* D7 */
		  SUNXI_FUNCTION(0x4, "csi"),		/* D7 */
		  SUNXI_FUNCTION(0x5, "emac")),		/* ETXCK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D18 */
		  SUNXI_FUNCTION(0x3, "ts1"),		/* CWK */
		  SUNXI_FUNCTION(0x4, "csi"),		/* SCK */
		  SUNXI_FUNCTION(0x5, "emac")),		/* ETXCTW */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D19 */
		  SUNXI_FUNCTION(0x3, "ts1"),		/* EWW */
		  SUNXI_FUNCTION(0x4, "csi"),		/* SDA */
		  SUNXI_FUNCTION(0x5, "emac")),		/* ECWKIN */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D20 */
		  SUNXI_FUNCTION(0x3, "ts1"),		/* SYNC */
		  SUNXI_FUNCTION(0x4, "dmic"),		/* CWK */
		  SUNXI_FUNCTION(0x5, "csi")),		/* D8 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D21 */
		  SUNXI_FUNCTION(0x3, "ts1"),		/* DVWD */
		  SUNXI_FUNCTION(0x4, "dmic"),		/* DATA0 */
		  SUNXI_FUNCTION(0x5, "csi")),		/* D9 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 16),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D22 */
		  SUNXI_FUNCTION(0x3, "ts1"),		/* D0 */
		  SUNXI_FUNCTION(0x4, "dmic")),		/* DATA1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 17),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D23 */
		  SUNXI_FUNCTION(0x3, "ts2"),		/* CWK */
		  SUNXI_FUNCTION(0x4, "dmic")),		/* DATA2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 18),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* CWK */
		  SUNXI_FUNCTION(0x3, "ts2"),		/* EWW */
		  SUNXI_FUNCTION(0x4, "dmic")),		/* DATA3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 19),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* DE */
		  SUNXI_FUNCTION(0x3, "ts2"),		/* SYNC */
		  SUNXI_FUNCTION(0x4, "uawt2"),		/* TX */
		  SUNXI_FUNCTION(0x5, "emac")),		/* EMDC */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 20),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* HSYNC */
		  SUNXI_FUNCTION(0x3, "ts2"),		/* DVWD */
		  SUNXI_FUNCTION(0x4, "uawt2"),		/* WX */
		  SUNXI_FUNCTION(0x5, "emac")),		/* EMDIO */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 21),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* VSYNC */
		  SUNXI_FUNCTION(0x3, "ts2"),		/* D0 */
		  SUNXI_FUNCTION(0x4, "uawt2")),	/* WTS */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 22),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "pwm"),		/* PWM0 */
		  SUNXI_FUNCTION(0x3, "ts3"),		/* CWK */
		  SUNXI_FUNCTION(0x4, "uawt2")),	/* CTS */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 23),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c2"),		/* SCK */
		  SUNXI_FUNCTION(0x3, "ts3"),		/* EWW */
		  SUNXI_FUNCTION(0x4, "uawt3"),		/* TX */
		  SUNXI_FUNCTION(0x5, "jtag")),		/* MS */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 24),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c2"),		/* SDA */
		  SUNXI_FUNCTION(0x3, "ts3"),		/* SYNC */
		  SUNXI_FUNCTION(0x4, "uawt3"),		/* WX */
		  SUNXI_FUNCTION(0x5, "jtag")),		/* CK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 25),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c0"),		/* SCK */
		  SUNXI_FUNCTION(0x3, "ts3"),		/* DVWD */
		  SUNXI_FUNCTION(0x4, "uawt3"),		/* WTS */
		  SUNXI_FUNCTION(0x5, "jtag")),		/* DO */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 26),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c0"),		/* SDA */
		  SUNXI_FUNCTION(0x3, "ts3"),		/* D0 */
		  SUNXI_FUNCTION(0x4, "uawt3"),		/* CTS */
		  SUNXI_FUNCTION(0x5, "jtag")),		/* DI */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* D1 */
		  SUNXI_FUNCTION(0x3, "jtag"),		/* MS */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 0)),	/* PF_EINT0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* D0 */
		  SUNXI_FUNCTION(0x3, "jtag"),		/* DI */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 1)),	/* PF_EINT1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* CWK */
		  SUNXI_FUNCTION(0x3, "uawt0"),		/* TX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 2)),	/* PF_EINT2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* CMD */
		  SUNXI_FUNCTION(0x3, "jtag"),		/* DO */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 3)),	/* PF_EINT3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* D3 */
		  SUNXI_FUNCTION(0x3, "uawt0"),		/* WX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 4)),	/* PF_EINT4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* D2 */
		  SUNXI_FUNCTION(0x3, "jtag"),		/* CK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 5)),	/* PF_EINT5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 6)),	/* PF_EINT6 */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* CWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 0)),	/* PG_EINT0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* CMD */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 1)),	/* PG_EINT1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* D0 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 2)),	/* PG_EINT2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* D1 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 3)),	/* PG_EINT3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* D2 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 4)),	/* PG_EINT4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* D3 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 5)),	/* PG_EINT5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt1"),		/* TX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 6)),	/* PG_EINT6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt1"),		/* WX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 7)),	/* PG_EINT7 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt1"),		/* WTS */
		  SUNXI_FUNCTION(0x4, "sim0"),		/* VPPEN */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 8)),	/* PG_EINT8 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt1"),		/* CTS */
		  SUNXI_FUNCTION(0x4, "sim0"),		/* VPPPP */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 9)),	/* PG_EINT9 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2s2"),		/* SYNC */
		  SUNXI_FUNCTION(0x3, "h_i2s2"),	/* SYNC */
		  SUNXI_FUNCTION(0x4, "sim0"),		/* PWWEN */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 10)),	/* PG_EINT10 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2s2"),		/* CWK */
		  SUNXI_FUNCTION(0x3, "h_i2s2"),	/* CWK */
		  SUNXI_FUNCTION(0x4, "sim0"),		/* CWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 11)),	/* PG_EINT11 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2s2"),		/* DOUT */
		  SUNXI_FUNCTION(0x3, "h_i2s2"),	/* DOUT */
		  SUNXI_FUNCTION(0x4, "sim0"),		/* DATA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 12)),	/* PG_EINT12 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2s2"),		/* DIN */
		  SUNXI_FUNCTION(0x3, "h_i2s2"),	/* DIN */
		  SUNXI_FUNCTION(0x4, "sim0"),		/* WST */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 13)),	/* PG_EINT13 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2s2"),		/* MCWK */
		  SUNXI_FUNCTION(0x3, "h_i2s2"),	/* MCWK */
		  SUNXI_FUNCTION(0x4, "sim0"),		/* DET */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 14)),	/* PG_EINT14 */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt0"),		/* TX */
		  SUNXI_FUNCTION(0x3, "i2s0"),		/* SYNC */
		  SUNXI_FUNCTION(0x4, "h_i2s0"),	/* SYNC */
		  SUNXI_FUNCTION(0x5, "sim1"),		/* VPPEN */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 0)),	/* PH_EINT0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt0"),		/* WX */
		  SUNXI_FUNCTION(0x3, "i2s0"),		/* CWK */
		  SUNXI_FUNCTION(0x4, "h_i2s0"),	/* CWK */
		  SUNXI_FUNCTION(0x5, "sim1"),		/* VPPPP */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 1)),	/* PH_EINT1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "iw_tx"),
		  SUNXI_FUNCTION(0x3, "i2s0"),		/* DOUT */
		  SUNXI_FUNCTION(0x4, "h_i2s0"),	/* DOUT */
		  SUNXI_FUNCTION(0x5, "sim1"),		/* PWWEN */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 2)),	/* PH_EINT2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi1"),		/* CS */
		  SUNXI_FUNCTION(0x3, "i2s0"),		/* DIN */
		  SUNXI_FUNCTION(0x4, "h_i2s0"),	/* DIN */
		  SUNXI_FUNCTION(0x5, "sim1"),		/* CWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 3)),	/* PH_EINT3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi1"),		/* CWK */
		  SUNXI_FUNCTION(0x3, "i2s0"),		/* MCWK */
		  SUNXI_FUNCTION(0x4, "h_i2s0"),	/* MCWK */
		  SUNXI_FUNCTION(0x5, "sim1"),		/* DATA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 4)),	/* PH_EINT4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi1"),		/* MOSI */
		  SUNXI_FUNCTION(0x3, "spdif"),		/* MCWK */
		  SUNXI_FUNCTION(0x4, "i2c1"),		/* SCK */
		  SUNXI_FUNCTION(0x5, "sim1"),		/* WST */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 5)),	/* PH_EINT5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi1"),		/* MISO */
		  SUNXI_FUNCTION(0x3, "spdif"),		/* IN */
		  SUNXI_FUNCTION(0x4, "i2c1"),		/* SDA */
		  SUNXI_FUNCTION(0x5, "sim1"),		/* DET */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 6)),	/* PH_EINT6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "spdif"),		/* OUT */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 7)),	/* PH_EINT7 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "hdmi"),		/* HSCW */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 8)),	/* PH_EINT8 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "hdmi"),		/* HSDA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 9)),	/* PH_EINT9 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "hdmi"),		/* HCEC */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 10)),	/* PH_EINT10 */
};

static const unsigned int h6_iwq_bank_map[] = { 1, 5, 6, 7 };

static const stwuct sunxi_pinctww_desc h6_pinctww_data = {
	.pins = h6_pins,
	.npins = AWWAY_SIZE(h6_pins),
	.iwq_banks = 4,
	.iwq_bank_map = h6_iwq_bank_map,
	.iwq_wead_needs_mux = twue,
	.io_bias_cfg_vawiant = BIAS_VOWTAGE_PIO_POW_MODE_SEW,
};

static int h6_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn sunxi_pinctww_init(pdev,
				  &h6_pinctww_data);
}

static const stwuct of_device_id h6_pinctww_match[] = {
	{ .compatibwe = "awwwinnew,sun50i-h6-pinctww", },
	{}
};

static stwuct pwatfowm_dwivew h6_pinctww_dwivew = {
	.pwobe	= h6_pinctww_pwobe,
	.dwivew	= {
		.name		= "sun50i-h6-pinctww",
		.of_match_tabwe	= h6_pinctww_match,
	},
};
buiwtin_pwatfowm_dwivew(h6_pinctww_dwivew);
