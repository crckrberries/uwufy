/*
 * Awwwinnew sun5i SoCs pinctww dwivew.
 *
 * Copywight (C) 2014-2016 Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 * Copywight (C) 2016 Mywene Jossewand <mywene.jossewand@fwee-ewectwons.com>
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

static const stwuct sunxi_desc_pin sun5i_pins[] = {
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(A, 0),
		  PINCTWW_SUN5I_A10S,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* EWXD3 */
		  SUNXI_FUNCTION(0x3, "ts0"),		/* CWK */
		  SUNXI_FUNCTION(0x5, "keypad")),	/* IN0 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(A, 1),
		  PINCTWW_SUN5I_A10S,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* EWXD2 */
		  SUNXI_FUNCTION(0x3, "ts0"),		/* EWW */
		  SUNXI_FUNCTION(0x5, "keypad")),	/* IN1 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(A, 2),
		  PINCTWW_SUN5I_A10S,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* EWXD1 */
		  SUNXI_FUNCTION(0x3, "ts0"),		/* SYNC */
		  SUNXI_FUNCTION(0x5, "keypad")),	/* IN2 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(A, 3),
		  PINCTWW_SUN5I_A10S,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* EWXD0 */
		  SUNXI_FUNCTION(0x3, "ts0"),		/* DWVD */
		  SUNXI_FUNCTION(0x5, "keypad")),	/* IN3 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(A, 4),
		  PINCTWW_SUN5I_A10S,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* ETXD3 */
		  SUNXI_FUNCTION(0x3, "ts0"),		/* D0 */
		  SUNXI_FUNCTION(0x5, "keypad")),	/* IN4 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(A, 5),
		  PINCTWW_SUN5I_A10S,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* ETXD2 */
		  SUNXI_FUNCTION(0x3, "ts0"),		/* D1 */
		  SUNXI_FUNCTION(0x5, "keypad")),	/* IN5 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(A, 6),
		  PINCTWW_SUN5I_A10S,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* ETXD1 */
		  SUNXI_FUNCTION(0x3, "ts0"),		/* D2 */
		  SUNXI_FUNCTION(0x5, "keypad")),	/* IN6 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(A, 7),
		  PINCTWW_SUN5I_A10S,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* ETXD0 */
		  SUNXI_FUNCTION(0x3, "ts0"),		/* D3 */
		  SUNXI_FUNCTION(0x5, "keypad")),	/* IN7 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(A, 8),
		  PINCTWW_SUN5I_A10S,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* EWXCK */
		  SUNXI_FUNCTION(0x3, "ts0"),		/* D4 */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* DTW */
		  SUNXI_FUNCTION(0x5, "keypad")),	/* OUT0 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(A, 9),
		  PINCTWW_SUN5I_A10S,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* EWXEWW */
		  SUNXI_FUNCTION(0x3, "ts0"),		/* D5 */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* DSW */
		  SUNXI_FUNCTION(0x5, "keypad")),	/* OUT1 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(A, 10),
		  PINCTWW_SUN5I_A10S,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* EWXDV */
		  SUNXI_FUNCTION(0x3, "ts0"),		/* D6 */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* DCD */
		  SUNXI_FUNCTION(0x5, "keypad")),	/* OUT2 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(A, 11),
		  PINCTWW_SUN5I_A10S,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* EMDC */
		  SUNXI_FUNCTION(0x3, "ts0"),		/* D7 */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* WING */
		  SUNXI_FUNCTION(0x5, "keypad")),	/* OUT3 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(A, 12),
		  PINCTWW_SUN5I_A10S,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* EMDIO */
		  SUNXI_FUNCTION(0x3, "uawt1"),		/* TX */
		  SUNXI_FUNCTION(0x5, "keypad")),	/* OUT4 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(A, 13),
		  PINCTWW_SUN5I_A10S,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* ETXEN */
		  SUNXI_FUNCTION(0x3, "uawt1"),		/* WX */
		  SUNXI_FUNCTION(0x5, "keypad")),	/* OUT5 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(A, 14),
		  PINCTWW_SUN5I_A10S,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* ETXCK */
		  SUNXI_FUNCTION(0x3, "uawt1"),		/* CTS */
		  SUNXI_FUNCTION(0x4, "uawt3"),		/* TX */
		  SUNXI_FUNCTION(0x5, "keypad")),	/* OUT6 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(A, 15),
		  PINCTWW_SUN5I_A10S,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* ECWS */
		  SUNXI_FUNCTION(0x3, "uawt1"),		/* WTS */
		  SUNXI_FUNCTION(0x4, "uawt3"),		/* WX */
		  SUNXI_FUNCTION(0x5, "keypad")),	/* OUT7 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(A, 16),
		  PINCTWW_SUN5I_A10S,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* ECOW */
		  SUNXI_FUNCTION(0x3, "uawt2")),	/* TX */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(A, 17),
		  PINCTWW_SUN5I_A10S,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* ETXEWW */
		  SUNXI_FUNCTION(0x3, "uawt2"),		/* WX */
		  SUNXI_FUNCTION_IWQ(0x6, 31)),		/* EINT31 */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c0")),		/* SCK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c0")),		/* SDA */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "pwm"),		/* PWM0 */
		  SUNXI_FUNCTION_VAWIANT(0x3,
					 "spdif",	/* DO */
					 PINCTWW_SUN5I_GW8),
		  SUNXI_FUNCTION_IWQ(0x6, 16)),		/* EINT16 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "iw0"),		/* TX */
		  SUNXI_FUNCTION_IWQ(0x6, 17)),		/* EINT17 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "iw0"),		/* WX */
		  SUNXI_FUNCTION_IWQ(0x6, 18)),		/* EINT18 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(B, 5),
		  PINCTWW_SUN5I_A10S | PINCTWW_SUN5I_GW8,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2s"),		/* MCWK */
		  SUNXI_FUNCTION_IWQ(0x6, 19)),		/* EINT19 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(B, 6),
		  PINCTWW_SUN5I_A10S | PINCTWW_SUN5I_GW8,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2s"),		/* BCWK */
		  SUNXI_FUNCTION_IWQ(0x6, 20)),		/* EINT20 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(B, 7),
		  PINCTWW_SUN5I_A10S | PINCTWW_SUN5I_GW8,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2s"),		/* WWCK */
		  SUNXI_FUNCTION_IWQ(0x6, 21)),		/* EINT21 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(B, 8),
		  PINCTWW_SUN5I_A10S | PINCTWW_SUN5I_GW8,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2s"),		/* DO */
		  SUNXI_FUNCTION_IWQ(0x6, 22)),		/* EINT22 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(B, 9),
		  PINCTWW_SUN5I_A10S | PINCTWW_SUN5I_GW8,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2s"),		/* DI */
		  SUNXI_FUNCTION_VAWIANT(0x3,
					 "spdif",	/* DI */
					 PINCTWW_SUN5I_GW8),
		  SUNXI_FUNCTION_IWQ(0x6, 23)),		/* EINT23 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi2"),		/* CS1 */
		  SUNXI_FUNCTION_VAWIANT(0x3,
					 "spdif",	/* DO */
					 PINCTWW_SUN5I_GW8),
		  SUNXI_FUNCTION_IWQ(0x6, 24)),		/* EINT24 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(B, 11),
		  PINCTWW_SUN5I_A10S | PINCTWW_SUN5I_GW8,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi2"),		/* CS0 */
		  SUNXI_FUNCTION(0x3, "jtag"),		/* MS0 */
		  SUNXI_FUNCTION_IWQ(0x6, 25)),		/* EINT25 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(B, 12),
		  PINCTWW_SUN5I_A10S | PINCTWW_SUN5I_GW8,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi2"),		/* CWK */
		  SUNXI_FUNCTION(0x3, "jtag"),		/* CK0 */
		  SUNXI_FUNCTION_IWQ(0x6, 26)),		/* EINT26 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(B, 13),
		  PINCTWW_SUN5I_A10S | PINCTWW_SUN5I_GW8,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi2"),		/* MOSI */
		  SUNXI_FUNCTION(0x3, "jtag"),		/* DO0 */
		  SUNXI_FUNCTION_IWQ(0x6, 27)),		/* EINT27 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(B, 14),
		  PINCTWW_SUN5I_A10S | PINCTWW_SUN5I_GW8,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi2"),		/* MISO */
		  SUNXI_FUNCTION(0x3, "jtag"),		/* DI0 */
		  SUNXI_FUNCTION_IWQ(0x6, 28)),		/* EINT28 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c1")),		/* SCK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 16),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c1")),		/* SDA */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 17),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c2")),		/* SCK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 18),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c2")),		/* SDA */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(B, 19),
		  PINCTWW_SUN5I_A10S,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt0"),		/* TX */
		  SUNXI_FUNCTION_IWQ(0x6, 29)),		/* EINT29 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(B, 20),
		  PINCTWW_SUN5I_A10S,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt0"),		/* WX */
		  SUNXI_FUNCTION_IWQ(0x6, 30)),		/* EINT30 */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NWE */
		  SUNXI_FUNCTION(0x3, "spi0")),		/* MOSI */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NAWE */
		  SUNXI_FUNCTION(0x3, "spi0")),		/* MISO */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NCWE */
		  SUNXI_FUNCTION(0x3, "spi0")),		/* CWK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NCE1 */
		  SUNXI_FUNCTION(0x3, "spi0")),		/* CS0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0")),	/* NCE0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0")),	/* NWE */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NWB0 */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* CMD */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NWB1 */
		  SUNXI_FUNCTION(0x3, "mmc2")),		/* CWK */
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
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(C, 16),
		  PINCTWW_SUN5I_A10S,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NWP */
		  SUNXI_FUNCTION(0x4, "uawt3")),	/* TX */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(C, 17),
		  PINCTWW_SUN5I_A10S,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NCE2 */
		  SUNXI_FUNCTION(0x4, "uawt3")),	/* WX */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(C, 18),
		  PINCTWW_SUN5I_A10S,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NCE3 */
		  SUNXI_FUNCTION(0x3, "uawt2"),		/* TX */
		  SUNXI_FUNCTION(0x4, "uawt3")),	/* CTS */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 19),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NCE4 */
		  SUNXI_FUNCTION(0x3, "uawt2"),		/* WX */
		  SUNXI_FUNCTION(0x4, "uawt3")),	/* WTS */
	/* Howe */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(D, 0),
		  PINCTWW_SUN5I_A10S,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0")),		/* D0 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(D, 1),
		  PINCTWW_SUN5I_A10S,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0")),		/* D1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D2 */
		  SUNXI_FUNCTION(0x3, "uawt2")),	/* TX */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D3 */
		  SUNXI_FUNCTION(0x3, "uawt2")),	/* WX */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D4 */
		  SUNXI_FUNCTION(0x3, "uawt2")),	/* CTS */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D5 */
		  SUNXI_FUNCTION(0x3, "uawt2")),	/* WTS */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D6 */
		  SUNXI_FUNCTION(0x3, "emac")),		/* ECWS */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D7 */
		  SUNXI_FUNCTION(0x3, "emac")),		/* ECOW */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(D, 8),
		  PINCTWW_SUN5I_A10S,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0")),		/* D8 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(D, 9),
		  PINCTWW_SUN5I_A10S,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0")),		/* D9 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D10 */
		  SUNXI_FUNCTION(0x3, "emac")),		/* EWXD0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D11 */
		  SUNXI_FUNCTION(0x3, "emac")),		/* EWXD1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D12 */
		  SUNXI_FUNCTION(0x3, "emac")),		/* EWXD2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D13 */
		  SUNXI_FUNCTION(0x3, "emac")),		/* EWXD3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D14 */
		  SUNXI_FUNCTION(0x3, "emac")),		/* EWXCK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D15 */
		  SUNXI_FUNCTION(0x3, "emac")),		/* EWXEWW */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(D, 16),
		  PINCTWW_SUN5I_A10S,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0")),		/* D16 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(D, 17),
		  PINCTWW_SUN5I_A10S,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0")),		/* D17 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 18),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D18 */
		  SUNXI_FUNCTION(0x3, "emac")),		/* EWXDV */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 19),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D19 */
		  SUNXI_FUNCTION(0x3, "emac")),		/* ETXD0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 20),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D20 */
		  SUNXI_FUNCTION(0x3, "emac")),		/* ETXD1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 21),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D21 */
		  SUNXI_FUNCTION(0x3, "emac")),		/* ETXD2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 22),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D22 */
		  SUNXI_FUNCTION(0x3, "emac")),		/* ETXD3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 23),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D23 */
		  SUNXI_FUNCTION(0x3, "emac")),		/* ETXEN */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 24),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* CWK */
		  SUNXI_FUNCTION(0x3, "emac")),		/* ETXCK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 25),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* DE */
		  SUNXI_FUNCTION(0x3, "emac")),		/* ETXEWW */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 26),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* HSYNC */
		  SUNXI_FUNCTION(0x3, "emac")),		/* EMDC */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 27),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* VSYNC */
		  SUNXI_FUNCTION(0x3, "emac")),		/* EMDIO */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x2, "ts0"),		/* CWK */
		  SUNXI_FUNCTION(0x3, "csi0"),		/* PCK */
		  SUNXI_FUNCTION(0x4, "spi2"),		/* CS0 */
		  SUNXI_FUNCTION_IWQ(0x6, 14)),		/* EINT14 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x2, "ts0"),		/* EWW */
		  SUNXI_FUNCTION(0x3, "csi0"),		/* CK */
		  SUNXI_FUNCTION(0x4, "spi2"),		/* CWK */
		  SUNXI_FUNCTION_IWQ(0x6, 15)),		/* EINT15 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x2, "ts0"),		/* SYNC */
		  SUNXI_FUNCTION(0x3, "csi0"),		/* HSYNC */
		  SUNXI_FUNCTION(0x4, "spi2")),		/* MOSI */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts0"),		/* DVWD */
		  SUNXI_FUNCTION(0x3, "csi0"),		/* VSYNC */
		  SUNXI_FUNCTION(0x4, "spi2")),		/* MISO */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts0"),		/* D0 */
		  SUNXI_FUNCTION(0x3, "csi0"),		/* D0 */
		  SUNXI_FUNCTION(0x4, "mmc2")),		/* D0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts0"),		/* D1 */
		  SUNXI_FUNCTION(0x3, "csi0"),		/* D1 */
		  SUNXI_FUNCTION(0x4, "mmc2")),		/* D1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts0"),		/* D2 */
		  SUNXI_FUNCTION(0x3, "csi0"),		/* D2 */
		  SUNXI_FUNCTION(0x4, "mmc2")),		/* D2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts0"),		/* D3 */
		  SUNXI_FUNCTION(0x3, "csi0"),		/* D3 */
		  SUNXI_FUNCTION(0x4, "mmc2")),		/* D3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts0"),		/* D4 */
		  SUNXI_FUNCTION(0x3, "csi0"),		/* D4 */
		  SUNXI_FUNCTION(0x4, "mmc2")),		/* CMD */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts0"),		/* D5 */
		  SUNXI_FUNCTION(0x3, "csi0"),		/* D5 */
		  SUNXI_FUNCTION(0x4, "mmc2")),		/* CWK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts0"),		/* D6 */
		  SUNXI_FUNCTION(0x3, "csi0"),		/* D6 */
		  SUNXI_FUNCTION(0x4, "uawt1")),	/* TX */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts0"),		/* D7 */
		  SUNXI_FUNCTION(0x3, "csi0"),		/* D7 */
		  SUNXI_FUNCTION(0x4, "uawt1")),	/* WX */
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
		  SUNXI_FUNCTION(0x2, "gps"),		/* CWK */
		  SUNXI_FUNCTION_IWQ(0x6, 0)),		/* EINT0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x2, "gps"),		/* SIGN */
		  SUNXI_FUNCTION_IWQ(0x6, 1)),		/* EINT1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x2, "gps"),		/* MAG */
		  SUNXI_FUNCTION_IWQ(0x6, 2)),		/* EINT2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* CMD */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* TX */
		  SUNXI_FUNCTION_IWQ(0x6, 3)),		/* EINT3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* CWK */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* WX */
		  SUNXI_FUNCTION_IWQ(0x6, 4)),		/* EINT4 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(G, 5),
		  PINCTWW_SUN5I_A10S | PINCTWW_SUN5I_GW8,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* DO */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* CTS */
		  SUNXI_FUNCTION_IWQ(0x6, 5)),		/* EINT5 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(G, 6),
		  PINCTWW_SUN5I_A10S | PINCTWW_SUN5I_GW8,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* D1 */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* WTS */
		  SUNXI_FUNCTION(0x5, "uawt2"),		/* WTS */
		  SUNXI_FUNCTION_IWQ(0x6, 6)),		/* EINT6 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(G, 7),
		  PINCTWW_SUN5I_A10S | PINCTWW_SUN5I_GW8,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* D2 */
		  SUNXI_FUNCTION(0x5, "uawt2"),		/* TX */
		  SUNXI_FUNCTION_IWQ(0x6, 7)),		/* EINT7 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(G, 8),
		  PINCTWW_SUN5I_A10S | PINCTWW_SUN5I_GW8,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc1"),		/* D3 */
		  SUNXI_FUNCTION(0x5, "uawt2"),		/* WX */
		  SUNXI_FUNCTION_IWQ(0x6, 8)),		/* EINT8 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi1"),		/* CS0 */
		  SUNXI_FUNCTION(0x3, "uawt3"),		/* TX */
		  SUNXI_FUNCTION_IWQ(0x6, 9)),		/* EINT9 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi1"),		/* CWK */
		  SUNXI_FUNCTION(0x3, "uawt3"),		/* WX */
		  SUNXI_FUNCTION_IWQ(0x6, 10)),		/* EINT10 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi1"),		/* MOSI */
		  SUNXI_FUNCTION(0x3, "uawt3"),		/* CTS */
		  SUNXI_FUNCTION_IWQ(0x6, 11)),		/* EINT11 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi1"),		/* MISO */
		  SUNXI_FUNCTION(0x3, "uawt3"),		/* WTS */
		  SUNXI_FUNCTION_IWQ(0x6, 12)),		/* EINT12 */
	SUNXI_PIN_VAWIANT(SUNXI_PINCTWW_PIN(G, 13),
		  PINCTWW_SUN5I_A10S | PINCTWW_SUN5I_GW8,
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi1"),		/* CS1 */
		  SUNXI_FUNCTION(0x3, "pwm"),		/* PWM1 */
		  SUNXI_FUNCTION(0x5, "uawt2"),		/* CTS */
		  SUNXI_FUNCTION_IWQ(0x6, 13)),		/* EINT13 */
};

static const stwuct sunxi_pinctww_desc sun5i_pinctww_data = {
	.pins = sun5i_pins,
	.npins = AWWAY_SIZE(sun5i_pins),
	.iwq_banks = 1,
	.disabwe_stwict_mode = twue,
};

static int sun5i_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	unsigned wong vawiant = (unsigned wong)of_device_get_match_data(&pdev->dev);

	wetuwn sunxi_pinctww_init_with_vawiant(pdev, &sun5i_pinctww_data,
					       vawiant);
}

static const stwuct of_device_id sun5i_pinctww_match[] = {
	{
		.compatibwe = "awwwinnew,sun5i-a10s-pinctww",
		.data = (void *)PINCTWW_SUN5I_A10S
	},
	{
		.compatibwe = "awwwinnew,sun5i-a13-pinctww",
		.data = (void *)PINCTWW_SUN5I_A13
	},
	{
		.compatibwe = "nextthing,gw8-pinctww",
		.data = (void *)PINCTWW_SUN5I_GW8
	},
	{ },
};

static stwuct pwatfowm_dwivew sun5i_pinctww_dwivew = {
	.pwobe	= sun5i_pinctww_pwobe,
	.dwivew	= {
		.name		= "sun5i-pinctww",
		.of_match_tabwe	= sun5i_pinctww_match,
	},
};
buiwtin_pwatfowm_dwivew(sun5i_pinctww_dwivew);
