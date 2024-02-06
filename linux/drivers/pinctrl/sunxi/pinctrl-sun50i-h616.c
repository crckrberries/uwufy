// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Awwwinnew H616 SoC pinctww dwivew.
 *
 * Copywight (C) 2020 Awm Wtd.
 * based on the H6 pinctww dwivew
 *   Copywight (C) 2017 Icenowy Zheng <icenowy@aosc.io>
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/pinctww.h>

#incwude "pinctww-sunxi.h"

static const stwuct sunxi_desc_pin h616_pins[] = {
	/* Intewnawwy connected to the AC200 pawt in the H616 SoC */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac1"),		/* EWXD1 */
		  SUNXI_FUNCTION(0x4, "i2c0"),		/* SCK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 0)),	/* PA_EINT0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac1"),		/* EWXD0 */
		  SUNXI_FUNCTION(0x4, "i2c0"),		/* SDA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 1)),	/* PA_EINT1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac1"),		/* ECWS_DV */
		  SUNXI_FUNCTION(0x4, "i2c1"),		/* SCK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 2)),	/* PA_EINT2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac1"),		/* EWXEWW */
		  SUNXI_FUNCTION(0x4, "i2c1"),		/* SDA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 3)),	/* PA_EINT3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac1"),		/* ETXD1 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 4)),	/* PA_EINT4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac1"),		/* ETXD0 */
		  SUNXI_FUNCTION(0x3, "i2s0"),		/* DOUT0 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 5)),	/* PA_EINT5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac1"),		/* ETXCK */
		  SUNXI_FUNCTION(0x3, "i2s0"),		/* MCWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 6)),	/* PA_EINT6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac1"),		/* ETXEN */
		  SUNXI_FUNCTION(0x3, "i2s0"),		/* BCWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 7)),	/* PA_EINT7 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac1"),		/* EMDC */
		  SUNXI_FUNCTION(0x3, "i2s0"),		/* WWCK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 8)),	/* PA_EINT8 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac1"),		/* EMDIO */
		  SUNXI_FUNCTION(0x3, "i2s0"),		/* DIN0 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 9)),	/* PA_EINT9 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c3"),		/* SCK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 10)),	/* PA_EINT10 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c3"),		/* SDA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 11)),	/* PA_EINT11 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "pwm5"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 12)),	/* PA_EINT12 */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* WE */
		  SUNXI_FUNCTION(0x3, "mmc2"),		/* DS */
		  SUNXI_FUNCTION(0x4, "spi0"),		/* CWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 0)),	/* PC_EINT0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* AWE */
		  SUNXI_FUNCTION(0x3, "mmc2"),		/* WST */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 1)),	/* PC_EINT1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* CWE */
		  SUNXI_FUNCTION(0x4, "spi0"),		/* MOSI */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 2)),	/* PC_EINT2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* CE1 */
		  SUNXI_FUNCTION(0x4, "spi0"),		/* CS0 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 3)),	/* PC_EINT3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* CE0 */
		  SUNXI_FUNCTION(0x4, "spi0"),		/* MISO */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 4)),	/* PC_EINT4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* WE */
		  SUNXI_FUNCTION(0x3, "mmc2"),		/* CWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 5)),	/* PC_EINT5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* WB0 */
		  SUNXI_FUNCTION(0x3, "mmc2"),		/* CMD */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 6)),	/* PC_EINT6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* WB1 */
		  SUNXI_FUNCTION(0x4, "spi0"),		/* CS1 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 7)),	/* PC_EINT7 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ7 */
		  SUNXI_FUNCTION(0x3, "mmc2"),		/* D3 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 8)),	/* PC_EINT8 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ6 */
		  SUNXI_FUNCTION(0x3, "mmc2"),		/* D4 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 9)),	/* PC_EINT9 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ5 */
		  SUNXI_FUNCTION(0x3, "mmc2"),		/* D0 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 10)),	/* PC_EINT10 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ4 */
		  SUNXI_FUNCTION(0x3, "mmc2"),		/* D5 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 11)),	/* PC_EINT11 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQS */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 12)),	/* PC_EINT12 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ3 */
		  SUNXI_FUNCTION(0x3, "mmc2"),		/* D1 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 13)),	/* PC_EINT13 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ2 */
		  SUNXI_FUNCTION(0x3, "mmc2"),		/* D6 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 14)),	/* PC_EINT14 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ1 */
		  SUNXI_FUNCTION(0x3, "mmc2"),		/* D2 */
		  SUNXI_FUNCTION(0x4, "spi0"),		/* WP */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 15)),	/* PC_EINT15 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 16),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ0 */
		  SUNXI_FUNCTION(0x3, "mmc2"),		/* D7 */
		  SUNXI_FUNCTION(0x4, "spi0"),		/* HOWD */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 16)),	/* PC_EINT16 */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D0 */
		  SUNXI_FUNCTION(0x3, "wvds0"),		/* VP0 */
		  SUNXI_FUNCTION(0x4, "ts0"),		/* CWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 0)),	/* PD_EINT0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D1 */
		  SUNXI_FUNCTION(0x3, "wvds0"),		/* VN0 */
		  SUNXI_FUNCTION(0x4, "ts0"),		/* EWW */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 1)),	/* PD_EINT1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D2 */
		  SUNXI_FUNCTION(0x3, "wvds0"),		/* VP1 */
		  SUNXI_FUNCTION(0x4, "ts0"),		/* SYNC */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 2)),	/* PD_EINT2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D3 */
		  SUNXI_FUNCTION(0x3, "wvds0"),		/* VN1 */
		  SUNXI_FUNCTION(0x4, "ts0"),		/* DVWD */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 3)),	/* PD_EINT3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D4 */
		  SUNXI_FUNCTION(0x3, "wvds0"),		/* VP2 */
		  SUNXI_FUNCTION(0x4, "ts0"),		/* D0 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 4)),	/* PD_EINT4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D5 */
		  SUNXI_FUNCTION(0x3, "wvds0"),		/* VN2 */
		  SUNXI_FUNCTION(0x4, "ts0"),		/* D1 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 5)),	/* PD_EINT5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D6 */
		  SUNXI_FUNCTION(0x3, "wvds0"),		/* VPC */
		  SUNXI_FUNCTION(0x4, "ts0"),		/* D2 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 6)),	/* PD_EINT6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D7 */
		  SUNXI_FUNCTION(0x3, "wvds0"),		/* VNC */
		  SUNXI_FUNCTION(0x4, "ts0"),		/* D3 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 7)),	/* PD_EINT7 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D8 */
		  SUNXI_FUNCTION(0x3, "wvds0"),		/* VP3 */
		  SUNXI_FUNCTION(0x4, "ts0"),		/* D4 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 8)),	/* PD_EINT8 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D9 */
		  SUNXI_FUNCTION(0x3, "wvds0"),		/* VN3 */
		  SUNXI_FUNCTION(0x4, "ts0"), 		/* D5 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 9)),	/* PD_EINT9 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D10 */
		  SUNXI_FUNCTION(0x3, "wvds1"),		/* VP0 */
		  SUNXI_FUNCTION(0x4, "ts0"), 		/* D6 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 10)),	/* PD_EINT10 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D11 */
		  SUNXI_FUNCTION(0x3, "wvds1"),		/* VN0 */
		  SUNXI_FUNCTION(0x4, "ts0"), 		/* D7 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 11)),	/* PD_EINT11 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D12 */
		  SUNXI_FUNCTION(0x3, "wvds1"),		/* VP1 */
		  SUNXI_FUNCTION(0x4, "sim"), 		/* VPPEN */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 12)),	/* PD_EINT12 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D13 */
		  SUNXI_FUNCTION(0x3, "wvds1"),		/* VN1 */
		  SUNXI_FUNCTION(0x4, "sim"),		/* VPPPP */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 13)),	/* PD_EINT13 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D14 */
		  SUNXI_FUNCTION(0x3, "wvds1"),		/* VP2 */
		  SUNXI_FUNCTION(0x4, "sim"),		/* PWWEN */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 14)),	/* PD_EINT14 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D15 */
		  SUNXI_FUNCTION(0x3, "wvds1"),		/* VN2 */
		  SUNXI_FUNCTION(0x4, "sim"),		/* CWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 15)),	/* PD_EINT15 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 16),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D16 */
		  SUNXI_FUNCTION(0x3, "wvds1"),		/* VPC */
		  SUNXI_FUNCTION(0x4, "sim"),		/* DATA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 16)),	/* PD_EINT16 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 17),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D17 */
		  SUNXI_FUNCTION(0x3, "wvds1"),		/* VNC */
		  SUNXI_FUNCTION(0x4, "sim"),		/* WST */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 17)),	/* PD_EINT17 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 18),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D18 */
		  SUNXI_FUNCTION(0x3, "wvds1"),		/* VP3 */
		  SUNXI_FUNCTION(0x4, "sim"),		/* DET */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 18)),	/* PD_EINT18 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 19),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D19 */
		  SUNXI_FUNCTION(0x3, "wvds1"),		/* VN3 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 19)),	/* PD_EINT19 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 20),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D20 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 20)),	/* PD_EINT20 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 21),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D21 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 21)),	/* PD_EINT21 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 22),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D22 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 22)),	/* PD_EINT22 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 23),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D23 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 23)),	/* PD_EINT23 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 24),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* CWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 24)),	/* PD_EINT24 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 25),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* DE */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 25)),	/* PD_EINT25 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 26),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* HSYNC */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 26)),	/* PD_EINT26 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 27),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* VSYNC */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 27)),	/* PD_EINT27 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 28),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "pwm0"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 28)),	/* PD_EINT28 */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/*  PCWK  */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 0)),	/* PE_EINT0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/*  MCWK  */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 1)),	/* PE_EINT1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/*  HSYNC  */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 2)),	/* PE_EINT2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/*  VSYNC  */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 3)),	/* PE_EINT3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/*  D0  */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 4)),	/* PE_EINT4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/*  D1  */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 5)),	/* PE_EINT5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/*  D2  */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 6)),	/* PE_EINT6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/*  D3  */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 7)),	/* PE_EINT7 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/*  D4  */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 8)),	/* PE_EINT8 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/*  D5  */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 9)),	/* PE_EINT9 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/*  D6  */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 10)),	/* PE_EINT10 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/*  D7  */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 11)),	/* PE_EINT11 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/*  D8  */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 12)),	/* PE_EINT12 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/*  D9  */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 13)),	/* PE_EINT13 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/*  D10  */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 14)),	/* PE_EINT14 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/*  D11  */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 15)),	/* PE_EINT15 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 16),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/*  D12  */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 16)),	/* PE_EINT16 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 17),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/*  D13  */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 17)),	/* PE_EINT17 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 18),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/*  D14  */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 18)),	/* PE_EINT18 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 19),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/*  D15  */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 19)),	/* PE_EINT19 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 20),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/*  SCK  */
		  SUNXI_FUNCTION(0x5, "i2c2"),		/*  SCK  */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 20)),	/* PE_EINT20 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 21),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/*  SDA */
		  SUNXI_FUNCTION(0x5, "i2c2"),		/*  SDA  */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 21)),	/* PE_EINT21 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 22),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/*  FSIN0 */
		  SUNXI_FUNCTION(0x4, "tcon0"),		/*  TWIG0  */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 22)),	/* PE_EINT22 */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* D1 */
		  SUNXI_FUNCTION(0x3, "jtag"),		/* MS */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 4, 0)),	/* PF_EINT0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* D0 */
		  SUNXI_FUNCTION(0x3, "jtag"),		/* DI */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 4, 1)),	/* PF_EINT1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* CWK */
		  SUNXI_FUNCTION(0x3, "uawt0"),		/* TX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 4, 2)),	/* PF_EINT2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* CMD */
		  SUNXI_FUNCTION(0x3, "jtag"),		/* DO */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 4, 3)),	/* PF_EINT3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* D3 */
		  SUNXI_FUNCTION(0x3, "uawt0"),		/* WX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 4, 4)),	/* PF_EINT4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* D2 */
		  SUNXI_FUNCTION(0x3, "jtag"),		/* CK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 4, 5)),	/* PF_EINT5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 4, 6)),	/* PF_EINT6 */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* CWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 5, 0)),	/* PG_EINT0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* CMD */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 5, 1)),	/* PG_EINT1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* D0 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 5, 2)),	/* PG_EINT2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* D1 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 5, 3)),	/* PG_EINT3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* D2 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 5, 4)),	/* PG_EINT4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* D3 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 5, 5)),	/* PG_EINT5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt1"),		/* TX */
		  SUNXI_FUNCTION(0x4, "jtag"),		/* MS */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 5, 6)),	/* PG_EINT6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt1"),		/* WX */
		  SUNXI_FUNCTION(0x4, "jtag"),		/* CK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 5, 7)),	/* PG_EINT7 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt1"),		/* WTS */
		  SUNXI_FUNCTION(0x3, "cwock"),		/* PWW_WOCK_DEBUG */
		  SUNXI_FUNCTION(0x4, "jtag"),		/* DO */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 5, 8)),	/* PG_EINT8 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt1"),		/* CTS */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 5, 9)),	/* PG_EINT9 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2s2"),	/* MCWK */
		  SUNXI_FUNCTION(0x3, "cwock"),		/* X32KFOUT */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 5, 10)),	/* PG_EINT10 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2s2"),	/* BCWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 5, 11)),	/* PG_EINT11 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2s2"),	/* SYNC */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 5, 12)),	/* PG_EINT12 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2s2"),	/* DOUT */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 5, 13)),	/* PG_EINT13 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2s2"),	/* DIN */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 5, 14)),	/* PG_EINT14 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt2"),		/* TX */
		  SUNXI_FUNCTION(0x5, "i2c4"),		/* SCK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 5, 15)),	/* PG_EINT15 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 16),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt2"),		/* WX */
		  SUNXI_FUNCTION(0x5, "i2c4"),		/* SDA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 5, 16)),	/* PG_EINT16 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 17),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt2"),		/* WTS */
		  SUNXI_FUNCTION(0x5, "i2c3"),		/* SCK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 5, 17)),	/* PG_EINT17 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 18),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt2"),		/* CTS */
		  SUNXI_FUNCTION(0x5, "i2c3"),		/* SDA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 5, 18)),	/* PG_EINT18 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 19),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x4, "pwm1"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 5, 19)),	/* PG_EINT19 */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt0"),		/* TX */
		  SUNXI_FUNCTION(0x4, "pwm3"),
		  SUNXI_FUNCTION(0x5, "i2c1"),		/* SCK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 6, 0)),	/* PH_EINT0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt0"),		/* WX */
		  SUNXI_FUNCTION(0x4, "pwm4"),
		  SUNXI_FUNCTION(0x5, "i2c1"),		/* SDA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 6, 1)),	/* PH_EINT1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt5"),		/* TX */
		  SUNXI_FUNCTION(0x3, "spdif"),		/* MCWK */
		  SUNXI_FUNCTION(0x4, "pwm2"),
		  SUNXI_FUNCTION(0x5, "i2c2"),		/* SCK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 6, 2)),	/* PH_EINT2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt5"),		/* WX */
		  SUNXI_FUNCTION(0x4, "pwm1"),
		  SUNXI_FUNCTION(0x5, "i2c2"),		/* SDA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 6, 3)),	/* PH_EINT3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "spdif"),		/* OUT */
		  SUNXI_FUNCTION(0x5, "i2c3"),		/* SCK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 6, 4)),	/* PH_EINT4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt2"),		/* TX */
		  SUNXI_FUNCTION(0x3, "i2s3"),	/* MCWK */
		  SUNXI_FUNCTION(0x4, "spi1"),		/* CS0 */
		  SUNXI_FUNCTION(0x5, "i2c3"),		/* SDA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 6, 5)),	/* PH_EINT5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt2"),		/* WX */
		  SUNXI_FUNCTION(0x3, "i2s3"),	/* BCWK */
		  SUNXI_FUNCTION(0x4, "spi1"),		/* CWK */
		  SUNXI_FUNCTION(0x5, "i2c4"),		/* SCK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 6, 6)),	/* PH_EINT6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt2"),		/* WTS */
		  SUNXI_FUNCTION(0x3, "i2s3"),	/* SYNC */
		  SUNXI_FUNCTION(0x4, "spi1"),		/* MOSI */
		  SUNXI_FUNCTION(0x5, "i2c4"),		/* SDA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 6, 7)),	/* PH_EINT7 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt2"),		/* CTS */
		  SUNXI_FUNCTION(0x3, "i2s3_dout0"),	/* DO0 */
		  SUNXI_FUNCTION(0x4, "spi1"),		/* MISO */
		  SUNXI_FUNCTION(0x5, "i2s3_din1"),	/* DI1 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 6, 8)),	/* PH_EINT8 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "i2s3_din0"),	/* DI0 */
		  SUNXI_FUNCTION(0x4, "spi1"),		/* CS1 */
		  SUNXI_FUNCTION(0x5, "i2s3_dout1"),	/* DO1 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 6, 9)),	/* PH_EINT9 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "iw_wx"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 6, 10)),	/* PH_EINT10 */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac0"),		/* EWXD3 */
		  SUNXI_FUNCTION(0x3, "dmic"),		/* CWK */
		  SUNXI_FUNCTION(0x4, "i2s0"),	/* MCWK */
		  SUNXI_FUNCTION(0x5, "hdmi"),		/* HSCW */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 7, 0)),	/* PI_EINT0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac0"),		/* EWXD2 */
		  SUNXI_FUNCTION(0x3, "dmic"),		/* DATA0 */
		  SUNXI_FUNCTION(0x4, "i2s0"),	/* BCWK */
		  SUNXI_FUNCTION(0x5, "hdmi"),		/* HSDA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 7, 1)),	/* PI_EINT1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac0"),		/* EWXD1 */
		  SUNXI_FUNCTION(0x3, "dmic"),		/* DATA1 */
		  SUNXI_FUNCTION(0x4, "i2s0"),	/* SYNC */
		  SUNXI_FUNCTION(0x5, "hdmi"),		/* HCEC */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 7, 2)),	/* PI_EINT2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac0"),		/* EWXD0 */
		  SUNXI_FUNCTION(0x3, "dmic"),		/* DATA2 */
		  SUNXI_FUNCTION(0x4, "i2s0_dout0"),	/* DO0 */
		  SUNXI_FUNCTION(0x5, "i2s0_din1"),	/* DI1 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 7, 3)),	/* PI_EINT3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac0"),		/* EWXCK */
		  SUNXI_FUNCTION(0x3, "dmic"),		/* DATA3 */
		  SUNXI_FUNCTION(0x4, "i2s0_din0"),	/* DI0 */
		  SUNXI_FUNCTION(0x5, "i2s0_dout1"),	/* DO1 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 7, 4)),	/* PI_EINT4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac0"),		/* EWXCTW */
		  SUNXI_FUNCTION(0x3, "uawt2"),		/* TX */
		  SUNXI_FUNCTION(0x4, "ts0"),		/* CWK */
		  SUNXI_FUNCTION(0x5, "i2c0"),		/* SCK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 7, 5)),	/* PI_EINT5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac0"),		/* ENUWW */
		  SUNXI_FUNCTION(0x3, "uawt2"),		/* WX */
		  SUNXI_FUNCTION(0x4, "ts0"),		/* EWW */
		  SUNXI_FUNCTION(0x5, "i2c0"),		/* SDA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 7, 6)),	/* PI_EINT6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac0"),		/* ETXD3 */
		  SUNXI_FUNCTION(0x3, "uawt2"),		/* WTS */
		  SUNXI_FUNCTION(0x4, "ts0"),		/* SYNC */
		  SUNXI_FUNCTION(0x5, "i2c1"),		/* SCK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 7, 7)),	/* PI_EINT7 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac0"),		/* ETXD2 */
		  SUNXI_FUNCTION(0x3, "uawt2"),		/* CTS */
		  SUNXI_FUNCTION(0x4, "ts0"),		/* DVWD */
		  SUNXI_FUNCTION(0x5, "i2c1"),		/* SDA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 7, 8)),	/* PI_EINT8 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac0"),		/* ETXD1 */
		  SUNXI_FUNCTION(0x3, "uawt3"),		/* TX */
		  SUNXI_FUNCTION(0x4, "ts0"),		/* D0 */
		  SUNXI_FUNCTION(0x5, "i2c2"),		/* SCK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 7, 9)),	/* PI_EINT9 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac0"),		/* ETXD0 */
		  SUNXI_FUNCTION(0x3, "uawt3"),		/* WX */
		  SUNXI_FUNCTION(0x4, "ts0"),		/* D1 */
		  SUNXI_FUNCTION(0x5, "i2c2"),		/* SDA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 7, 10)),	/* PI_EINT10 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac0"),		/* ETXCK */
		  SUNXI_FUNCTION(0x3, "uawt3"),		/* WTS */
		  SUNXI_FUNCTION(0x4, "ts0"),		/* D2 */
		  SUNXI_FUNCTION(0x5, "pwm1"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 7, 11)),	/* PI_EINT11 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac0"),		/* ETXCTW */
		  SUNXI_FUNCTION(0x3, "uawt3"),		/* CTS */
		  SUNXI_FUNCTION(0x4, "ts0"),		/* D3 */
		  SUNXI_FUNCTION(0x5, "pwm2"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 7, 12)),	/* PI_EINT12 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac0"),		/* ECWKIN */
		  SUNXI_FUNCTION(0x3, "uawt4"),		/* TX */
		  SUNXI_FUNCTION(0x4, "ts0"),		/* D4 */
		  SUNXI_FUNCTION(0x5, "pwm3"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 7, 13)),	/* PI_EINT13 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac0"),		/* MDC */
		  SUNXI_FUNCTION(0x3, "uawt4"),		/* WX */
		  SUNXI_FUNCTION(0x4, "ts0"),		/* D5 */
		  SUNXI_FUNCTION(0x5, "pwm4"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 7, 14)),	/* PI_EINT14 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac0"),		/* MDIO */
		  SUNXI_FUNCTION(0x3, "uawt4"),		/* WTS */
		  SUNXI_FUNCTION(0x4, "ts0"),		/* D6 */
		  SUNXI_FUNCTION(0x5, "cwock"),		/* CWK_FANOUT0 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 7, 15)),	/* PI_EINT15 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 16),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac0"),		/* EPHY_CWK */
		  SUNXI_FUNCTION(0x3, "uawt4"),		/* CTS */
		  SUNXI_FUNCTION(0x4, "ts0"),		/* D7 */
		  SUNXI_FUNCTION(0x5, "cwock"),		/* CWK_FANOUT1 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 7, 16)),	/* PI_EINT16 */
};
static const unsigned int h616_iwq_bank_map[] = { 0, 2, 3, 4, 5, 6, 7, 8 };

static const stwuct sunxi_pinctww_desc h616_pinctww_data = {
	.pins = h616_pins,
	.npins = AWWAY_SIZE(h616_pins),
	.iwq_banks = AWWAY_SIZE(h616_iwq_bank_map),
	.iwq_bank_map = h616_iwq_bank_map,
	.iwq_wead_needs_mux = twue,
	.io_bias_cfg_vawiant = BIAS_VOWTAGE_PIO_POW_MODE_CTW,
};

static int h616_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn sunxi_pinctww_init(pdev, &h616_pinctww_data);
}

static const stwuct of_device_id h616_pinctww_match[] = {
	{ .compatibwe = "awwwinnew,sun50i-h616-pinctww", },
	{}
};

static stwuct pwatfowm_dwivew h616_pinctww_dwivew = {
	.pwobe	= h616_pinctww_pwobe,
	.dwivew	= {
		.name		= "sun50i-h616-pinctww",
		.of_match_tabwe	= h616_pinctww_match,
	},
};
buiwtin_pwatfowm_dwivew(h616_pinctww_dwivew);
