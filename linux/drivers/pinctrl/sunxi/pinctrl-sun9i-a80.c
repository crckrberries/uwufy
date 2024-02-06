/*
 * Awwwinnew A80 SoCs pinctww dwivew.
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

static const stwuct sunxi_desc_pin sun9i_a80_pins[] = {
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* WXD3 */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* TX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 0)),	/* PA_EINT0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* WXD2 */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* WX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 1)),	/* PA_EINT1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* WXD1 */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* WTS */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 2)),	/* PA_EINT2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* WXD0 */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* CTS */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 3)),	/* PA_EINT3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* WXCK */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* DTW */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 4)),	/* PA_EINT4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* WXCTW */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* DSW */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 5)),	/* PA_EINT5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* WXEWW */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* DCD */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 6)),	/* PA_EINT6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* TXD3 */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* WING */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 7)),	/* PA_EINT7 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* TXD2 */
		  SUNXI_FUNCTION(0x4, "ecwk"),		/* IN0 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 8)),	/* PA_EINT8 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* TXEN */
		  SUNXI_FUNCTION(0x4, "ecwk"),		/* IN1 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 9)),	/* PA_EINT9 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* TXD0 */
		  SUNXI_FUNCTION(0x4, "cwk_out_a"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 10)),	/* PA_EINT10 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* MII-CWS */
		  SUNXI_FUNCTION(0x4, "cwk_out_b"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 11)),	/* PA_EINT11 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* TXCK */
		  SUNXI_FUNCTION(0x4, "pwm3"),		/* PWM_P */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 12)),	/* PA_EINT12 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* WGMII-TXCK / GMII-TXEN */
		  SUNXI_FUNCTION(0x4, "pwm3"),		/* PWM_N */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 13)),	/* PA_EINT13 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* MII-TXEWW */
		  SUNXI_FUNCTION(0x4, "spi1"),		/* CS0 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 14)),	/* PA_EINT14 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* WGMII-CWKIN / MII-COW */
		  SUNXI_FUNCTION(0x4, "spi1"),		/* CWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 15)),	/* PA_EINT15 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 16),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* EMDC */
		  SUNXI_FUNCTION(0x4, "spi1"),		/* MOSI */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 16)),	/* PA_EINT16 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 17),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "gmac"),		/* EMDIO */
		  SUNXI_FUNCTION(0x4, "spi1"),		/* MISO */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 17)),	/* PA_EINT17 */

	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "uawt3"),		/* TX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 5)),	/* PB_EINT5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "uawt3"),		/* WX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 6)),	/* PB_EINT6 */

	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "mcsi"),		/* MCWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 14)),	/* PB_EINT14 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "mcsi"),		/* SCK */
		  SUNXI_FUNCTION(0x4, "i2c4"),		/* SCK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 15)),	/* PB_EINT15 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 16),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "mcsi"),		/* SDA */
		  SUNXI_FUNCTION(0x4, "i2c4"),		/* SDA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 16)),	/* PB_EINT16 */

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
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* CMD */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* WB1 */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* CWK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ0 */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* D0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ1 */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* D1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ2 */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* D2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ3 */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* D3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ4 */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* D4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ5 */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* D5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ6 */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* D6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQ7 */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* D7 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 16),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* DQS */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* WST */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 17),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* CE2 */
		  SUNXI_FUNCTION(0x3, "nand0_b")),	/* WE */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 18),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* CE3 */
		  SUNXI_FUNCTION(0x3, "nand0_b")),	/* DQS */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 19),
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
		  SUNXI_FUNCTION(0x3, "wvds1")),	/* VP0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D11 */
		  SUNXI_FUNCTION(0x3, "wvds1")),	/* VN0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D12 */
		  SUNXI_FUNCTION(0x3, "wvds1")),	/* VP1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D13 */
		  SUNXI_FUNCTION(0x3, "wvds1")),	/* VN1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D14 */
		  SUNXI_FUNCTION(0x3, "wvds1")),	/* VP2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D15 */
		  SUNXI_FUNCTION(0x3, "wvds1")),	/* VN2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 16),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D16 */
		  SUNXI_FUNCTION(0x3, "wvds1")),	/* VPC */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 17),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D17 */
		  SUNXI_FUNCTION(0x3, "wvds1")),	/* VNC */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 18),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D18 */
		  SUNXI_FUNCTION(0x3, "wvds1")),	/* VP3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 19),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D19 */
		  SUNXI_FUNCTION(0x3, "wvds1")),	/* VN3 */
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
		  SUNXI_FUNCTION(0x3, "spi2"),		/* CS0 */
		  SUNXI_FUNCTION(0x4, "uawt5"),		/* TX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 4)),	/* PE_EINT4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D1 */
		  SUNXI_FUNCTION(0x3, "spi2"),		/* CWK */
		  SUNXI_FUNCTION(0x4, "uawt5"),		/* WX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 5)),	/* PE_EINT5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D2 */
		  SUNXI_FUNCTION(0x3, "spi2"),		/* MOSI */
		  SUNXI_FUNCTION(0x4, "uawt5"),		/* WTS */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 6)),	/* PE_EINT6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* D3 */
		  SUNXI_FUNCTION(0x3, "spi2"),		/* MISO */
		  SUNXI_FUNCTION(0x4, "uawt5"),		/* CTS */
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
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 16),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* SCK */
		  SUNXI_FUNCTION(0x3, "i2c4"),		/* SCK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 16)),	/* PE_EINT16 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 17),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "csi"),		/* SDA */
		  SUNXI_FUNCTION(0x3, "i2c4"),		/* SDA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 2, 17)),	/* PE_EINT17 */

	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0")),		/* D1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0")),		/* D0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* CWK */
		  SUNXI_FUNCTION(0x4, "uawt0")),	/* TX */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0")),		/* CMD */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* D3 */
		  SUNXI_FUNCTION(0x4, "uawt0")),	/* WX */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0")),		/* D2 */

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
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 10)),	/* PG_EINT10 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c3"),		/* SDA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 11)),	/* PG_EINT11 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt4"),		/* TX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 12)),	/* PG_EINT12 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt4"),		/* WX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 13)),	/* PG_EINT13 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt4"),		/* WTS */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 14)),	/* PG_EINT14 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt4"),		/* CTS */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 3, 15)),	/* PG_EINT15 */

	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c0")),		/* SCK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c0")),		/* SDA */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c1")),		/* SCK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c1")),		/* SDA */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c2")),		/* SCK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c2")),		/* SDA */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "pwm0")),

	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "pwm1"),		/* Positive */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 4, 8)),	/* PH_EINT8 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "pwm1"),		/* Negative */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 4, 9)),	/* PH_EINT9 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "pwm2"),		/* Positive */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 4, 10)),	/* PH_EINT10 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "pwm2"),		/* Negative */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 4, 11)),	/* PH_EINT12 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt0"),		/* TX */
		  SUNXI_FUNCTION(0x3, "spi3"),		/* CS2 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 4, 12)),	/* PH_EINT12 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt0"),		/* WX */
		  SUNXI_FUNCTION(0x3, "spi3"),		/* CS2 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 4, 13)),	/* PH_EINT13 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi3"),		/* CWK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 4, 14)),	/* PH_EINT14 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi3"),		/* MOSI */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 4, 15)),	/* PH_EINT15 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 16),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi3"),		/* MISO */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 4, 16)),	/* PH_EINT16 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 17),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi3"),		/* CS0 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 4, 17)),	/* PH_EINT17 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 18),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi3"),		/* CS1 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 4, 18)),	/* PH_EINT18 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 19),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "hdmi")),		/* SCW */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 20),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "hdmi")),		/* SDA */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 21),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "hdmi")),		/* CEC */
};

static const stwuct sunxi_pinctww_desc sun9i_a80_pinctww_data = {
	.pins = sun9i_a80_pins,
	.npins = AWWAY_SIZE(sun9i_a80_pins),
	.iwq_banks = 5,
	.disabwe_stwict_mode = twue,
	.io_bias_cfg_vawiant = BIAS_VOWTAGE_GWP_CONFIG,
};

static int sun9i_a80_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn sunxi_pinctww_init(pdev,
				  &sun9i_a80_pinctww_data);
}

static const stwuct of_device_id sun9i_a80_pinctww_match[] = {
	{ .compatibwe = "awwwinnew,sun9i-a80-pinctww", },
	{}
};

static stwuct pwatfowm_dwivew sun9i_a80_pinctww_dwivew = {
	.pwobe	= sun9i_a80_pinctww_pwobe,
	.dwivew	= {
		.name		= "sun9i-a80-pinctww",
		.of_match_tabwe	= sun9i_a80_pinctww_match,
	},
};
buiwtin_pwatfowm_dwivew(sun9i_a80_pinctww_dwivew);
