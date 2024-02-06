/*
 * Awwwinnew A10 SoCs pinctww dwivew.
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

static const stwuct sunxi_desc_pin sun4i_a10_pins[] = {
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* EWXD3 */
		  SUNXI_FUNCTION(0x3, "spi1"),		/* CS0 */
		  SUNXI_FUNCTION(0x4, "uawt2"),		/* WTS */
		  SUNXI_FUNCTION_VAWIANT(0x5, "gmac",	/* GWXD3 */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* EWXD2 */
		  SUNXI_FUNCTION(0x3, "spi1"),		/* CWK */
		  SUNXI_FUNCTION(0x4, "uawt2"),		/* CTS */
		  SUNXI_FUNCTION_VAWIANT(0x5, "gmac",	/* GWXD2 */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* EWXD1 */
		  SUNXI_FUNCTION(0x3, "spi1"),		/* MOSI */
		  SUNXI_FUNCTION(0x4, "uawt2"),		/* TX */
		  SUNXI_FUNCTION_VAWIANT(0x5, "gmac",	/* GWXD1 */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* EWXD0 */
		  SUNXI_FUNCTION(0x3, "spi1"),		/* MISO */
		  SUNXI_FUNCTION(0x4, "uawt2"),		/* WX */
		  SUNXI_FUNCTION_VAWIANT(0x5, "gmac",	/* GWXD0 */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* ETXD3 */
		  SUNXI_FUNCTION(0x3, "spi1"),		/* CS1 */
		  SUNXI_FUNCTION_VAWIANT(0x5, "gmac",	/* GTXD3 */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* ETXD2 */
		  SUNXI_FUNCTION(0x3, "spi3"),		/* CS0 */
		  SUNXI_FUNCTION_VAWIANT(0x5, "gmac",	/* GTXD2 */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* ETXD1 */
		  SUNXI_FUNCTION(0x3, "spi3"),		/* CWK */
		  SUNXI_FUNCTION_VAWIANT(0x5, "gmac",	/* GTXD1 */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* ETXD0 */
		  SUNXI_FUNCTION(0x3, "spi3"),		/* MOSI */
		  SUNXI_FUNCTION_VAWIANT(0x5, "gmac",	/* GTXD0 */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* EWXCK */
		  SUNXI_FUNCTION(0x3, "spi3"),		/* MISO */
		  SUNXI_FUNCTION_VAWIANT(0x5, "gmac",	/* GWXCK */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* EWXEWW */
		  SUNXI_FUNCTION(0x3, "spi3"),		/* CS1 */
		  SUNXI_FUNCTION_VAWIANT(0x5, "gmac",	/* GNUWW / EWXEWW */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION_VAWIANT(0x6, "i2s1",	/* MCWK */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* EWXDV */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* TX */
		  SUNXI_FUNCTION_VAWIANT(0x5, "gmac",	/* GWXDV */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* EMDC */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* WX */
		  SUNXI_FUNCTION_VAWIANT(0x5, "gmac",	/* EMDC */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* EMDIO */
		  SUNXI_FUNCTION(0x3, "uawt6"),		/* TX */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* WTS */
		  SUNXI_FUNCTION_VAWIANT(0x5, "gmac",	/* EMDIO */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* ETXEN */
		  SUNXI_FUNCTION(0x3, "uawt6"),		/* WX */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* CTS */
		  SUNXI_FUNCTION_VAWIANT(0x5, "gmac",	/* GTXCTW / ETXEN */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* ETXCK */
		  SUNXI_FUNCTION(0x3, "uawt7"),		/* TX */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* DTW */
		  SUNXI_FUNCTION_VAWIANT(0x5, "gmac",	/* GNUWW / ETXCK */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION_VAWIANT(0x6, "i2s1",	/* BCWK */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* ECWS */
		  SUNXI_FUNCTION(0x3, "uawt7"),		/* WX */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* DSW */
		  SUNXI_FUNCTION_VAWIANT(0x5, "gmac",	/* GTXCK / ECWS */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION_VAWIANT(0x6, "i2s1",	/* WWCK */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 16),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* ECOW */
		  SUNXI_FUNCTION(0x3, "can"),		/* TX */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* DCD */
		  SUNXI_FUNCTION_VAWIANT(0x5, "gmac",	/* GCWKIN / ECOW */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION_VAWIANT(0x6, "i2s1",	/* DO */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(A, 17),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "emac"),		/* ETXEWW */
		  SUNXI_FUNCTION(0x3, "can"),		/* WX */
		  SUNXI_FUNCTION(0x4, "uawt1"),		/* WING */
		  SUNXI_FUNCTION_VAWIANT(0x5, "gmac",	/* GNUWW / ETXEWW */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION_VAWIANT(0x6, "i2s1",	/* DI */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40)),
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c0"),		/* SCK */
		  SUNXI_FUNCTION_VAWIANT(0x3, "pww_wock_dbg",
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c0")),		/* SDA */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_VAWIANT(0x2, "pwm",	/* PWM0 */
					 PINCTWW_SUN4I_A10 |
					 PINCTWW_SUN7I_A20),
		  SUNXI_FUNCTION_VAWIANT(0x3, "pwm",	/* PWM0 */
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_VAWIANT(0x2, "iw0",	/* TX */
					 PINCTWW_SUN4I_A10 |
					 PINCTWW_SUN7I_A20),
		  SUNXI_FUNCTION_VAWIANT(0x3, "pwm",	/* PWM1 */
					 PINCTWW_SUN8I_W40),
		/*
		 * The SPDIF bwock is not wefewenced at aww in the A10 usew
		 * manuaw. Howevew it is descwibed in the code weaked and the
		 * pin descwiptions awe decwawed in the A20 usew manuaw which
		 * is pin compatibwe with this device.
		 */
		  SUNXI_FUNCTION(0x4, "spdif")),        /* SPDIF MCWK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "iw0")),		/* WX */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  /*
		   * On A10 thewe's onwy one I2S contwowwew and the pin gwoup
		   * is simpwy named "i2s". On A20 thewe's two and thus it's
		   * wenamed to "i2s0". Deaw with these name hewe, in owdew
		   * to satisfy existing device twees.
		   */
		  SUNXI_FUNCTION_VAWIANT(0x2, "i2s",	/* MCWK */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION_VAWIANT(0x2, "i2s0",	/* MCWK */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION(0x3, "ac97")),		/* MCWK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_VAWIANT(0x2, "i2s",	/* BCWK */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION_VAWIANT(0x2, "i2s0",	/* BCWK */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION(0x3, "ac97")),		/* BCWK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_VAWIANT(0x2, "i2s",	/* WWCK */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION_VAWIANT(0x2, "i2s0",	/* WWCK */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION(0x3, "ac97")),		/* SYNC */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_VAWIANT(0x2, "i2s",	/* DO0 */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION_VAWIANT(0x2, "i2s0",	/* DO0 */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION(0x3, "ac97")),		/* DO */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_VAWIANT(0x2, "i2s",	/* DO1 */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION_VAWIANT(0x2, "i2s0",	/* DO1 */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION_VAWIANT(0x4, "pwm",	/* PWM6 */
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_VAWIANT(0x2, "i2s",	/* DO2 */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION_VAWIANT(0x2, "i2s0",	/* DO2 */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION_VAWIANT(0x4, "pwm",	/* PWM7 */
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_VAWIANT(0x2, "i2s",	/* DO3 */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION_VAWIANT(0x2, "i2s0",	/* DO3 */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_VAWIANT(0x2, "i2s",	/* DI */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION_VAWIANT(0x2, "i2s0",	/* DI */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION(0x3, "ac97"),		/* DI */
		/* Undocumented mux function on A10 - See SPDIF MCWK above */
		  SUNXI_FUNCTION_VAWIANT(0x4, "spdif",	/* SPDIF IN */
					 PINCTWW_SUN4I_A10 |
					 PINCTWW_SUN7I_A20)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi2"),		/* CS1 */
		/* Undocumented mux function on A10 - See SPDIF MCWK above */
		  SUNXI_FUNCTION(0x4, "spdif")),        /* SPDIF OUT */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi2"),		/* CS0 */
		  SUNXI_FUNCTION(0x3, "jtag")),		/* MS0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi2"),		/* CWK */
		  SUNXI_FUNCTION(0x3, "jtag")),		/* CK0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 16),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi2"),		/* MOSI */
		  SUNXI_FUNCTION(0x3, "jtag")),		/* DO0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 17),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi2"),		/* MISO */
		  SUNXI_FUNCTION(0x3, "jtag")),		/* DI0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 18),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c1")),		/* SCK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 19),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c1")),		/* SDA */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 20),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c2"),		/* SCK */
		  SUNXI_FUNCTION_VAWIANT(0x4, "pwm",	/* PWM4 */
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 21),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "i2c2"),		/* SDA */
		  SUNXI_FUNCTION_VAWIANT(0x4, "pwm",	/* PWM5 */
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 22),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt0"),		/* TX */
		  SUNXI_FUNCTION_VAWIANT(0x3, "iw1",	/* TX */
					 PINCTWW_SUN4I_A10 |
					 PINCTWW_SUN7I_A20)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(B, 23),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "uawt0"),		/* WX */
		  SUNXI_FUNCTION(0x3, "iw1")),		/* WX */
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
		  SUNXI_FUNCTION(0x3, "spi0")),		/* SCK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0")),	/* NCE1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0")),	/* NCE0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NWE# */
		  SUNXI_FUNCTION_VAWIANT(0x3, "mmc2",	/* DS */
					 PINCTWW_SUN8I_W40)),
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
		  SUNXI_FUNCTION_VAWIANT(0x3, "mmc2",	/* D4 */
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NDQ5 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "mmc2",	/* D5 */
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NDQ6 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "mmc2",	/* D6 */
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NDQ7 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "mmc2",	/* D7 */
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 16),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0")),	/* NWP */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 17),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0")),	/* NCE2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 18),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0")),	/* NCE3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 19),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NCE4 */
		  SUNXI_FUNCTION(0x3, "spi2")),		/* CS0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 20),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NCE5 */
		  SUNXI_FUNCTION(0x3, "spi2")),		/* CWK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 21),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NCE6 */
		  SUNXI_FUNCTION(0x3, "spi2")),		/* MOSI */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 22),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NCE7 */
		  SUNXI_FUNCTION(0x3, "spi2")),		/* MISO */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 23),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "spi0")),		/* CS0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(C, 24),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "nand0"),		/* NDQS */
		  SUNXI_FUNCTION_VAWIANT(0x3, "mmc2",	/* WST */
					 PINCTWW_SUN8I_W40)),
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
		  SUNXI_FUNCTION(0x3, "wvds0")),	/* VM3 */
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
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D20 */
		  SUNXI_FUNCTION(0x3, "csi1")),		/* MCWK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 21),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D21 */
		  SUNXI_FUNCTION(0x3, "sim")),		/* VPPEN */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 22),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D22 */
		  SUNXI_FUNCTION(0x3, "sim")),		/* VPPPP */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 23),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* D23 */
		  SUNXI_FUNCTION(0x3, "sim")),		/* DET */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 24),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* CWK */
		  SUNXI_FUNCTION(0x3, "sim")),		/* VCCEN */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 25),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* DE */
		  SUNXI_FUNCTION(0x3, "sim")),		/* WST */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 26),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* HSYNC */
		  SUNXI_FUNCTION(0x3, "sim")),		/* SCK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(D, 27),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd0"),		/* VSYNC */
		  SUNXI_FUNCTION(0x3, "sim")),		/* SDA */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts0"),		/* CWK */
		  SUNXI_FUNCTION(0x3, "csi0")),		/* PCK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts0"),		/* EWW */
		  SUNXI_FUNCTION(0x3, "csi0")),		/* CK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts0"),		/* SYNC */
		  SUNXI_FUNCTION(0x3, "csi0")),		/* HSYNC */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts0"),		/* DVWD */
		  SUNXI_FUNCTION(0x3, "csi0")),		/* VSYNC */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts0"),		/* D0 */
		  SUNXI_FUNCTION(0x3, "csi0")),		/* D0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts0"),		/* D1 */
		  SUNXI_FUNCTION(0x3, "csi0"),		/* D1 */
		  SUNXI_FUNCTION(0x4, "sim")),		/* VPPEN */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts0"),		/* D2 */
		  SUNXI_FUNCTION(0x3, "csi0")),		/* D2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts0"),		/* D3 */
		  SUNXI_FUNCTION(0x3, "csi0")),		/* D3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts0"),		/* D4 */
		  SUNXI_FUNCTION(0x3, "csi0")),		/* D4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts0"),		/* D5 */
		  SUNXI_FUNCTION(0x3, "csi0")),		/* D5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts0"),		/* D6 */
		  SUNXI_FUNCTION(0x3, "csi0")),		/* D6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(E, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts0"),		/* D7 */
		  SUNXI_FUNCTION(0x3, "csi0")),		/* D7 */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(F, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc0"),		/* D1 */
		  SUNXI_FUNCTION(0x4, "jtag")),		/* MSI */
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
		  SUNXI_FUNCTION(0x2, "ts1"),		/* CWK */
		  SUNXI_FUNCTION(0x3, "csi1"),		/* PCK */
		  SUNXI_FUNCTION(0x4, "mmc1")),		/* CMD */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts1"),		/* EWW */
		  SUNXI_FUNCTION(0x3, "csi1"),		/* CK */
		  SUNXI_FUNCTION(0x4, "mmc1")),		/* CWK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts1"),		/* SYNC */
		  SUNXI_FUNCTION(0x3, "csi1"),		/* HSYNC */
		  SUNXI_FUNCTION(0x4, "mmc1")),		/* D0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts1"),		/* DVWD */
		  SUNXI_FUNCTION(0x3, "csi1"),		/* VSYNC */
		  SUNXI_FUNCTION(0x4, "mmc1")),		/* D1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts1"),		/* D0 */
		  SUNXI_FUNCTION(0x3, "csi1"),		/* D0 */
		  SUNXI_FUNCTION(0x4, "mmc1"),		/* D2 */
		  SUNXI_FUNCTION(0x5, "csi0")),		/* D8 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts1"),		/* D1 */
		  SUNXI_FUNCTION(0x3, "csi1"),		/* D1 */
		  SUNXI_FUNCTION(0x4, "mmc1"),		/* D3 */
		  SUNXI_FUNCTION(0x5, "csi0")),		/* D9 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts1"),		/* D2 */
		  SUNXI_FUNCTION(0x3, "csi1"),		/* D2 */
		  SUNXI_FUNCTION(0x4, "uawt3"),		/* TX */
		  SUNXI_FUNCTION(0x5, "csi0")),		/* D10 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts1"),		/* D3 */
		  SUNXI_FUNCTION(0x3, "csi1"),		/* D3 */
		  SUNXI_FUNCTION(0x4, "uawt3"),		/* WX */
		  SUNXI_FUNCTION(0x5, "csi0")),		/* D11 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts1"),		/* D4 */
		  SUNXI_FUNCTION(0x3, "csi1"),		/* D4 */
		  SUNXI_FUNCTION(0x4, "uawt3"),		/* WTS */
		  SUNXI_FUNCTION(0x5, "csi0")),		/* D12 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts1"),		/* D5 */
		  SUNXI_FUNCTION(0x3, "csi1"),		/* D5 */
		  SUNXI_FUNCTION(0x4, "uawt3"),		/* CTS */
		  SUNXI_FUNCTION(0x5, "csi0"),		/* D13 */
		  SUNXI_FUNCTION_VAWIANT(0x6, "bist",	/* WESUWT0 */
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts1"),		/* D6 */
		  SUNXI_FUNCTION(0x3, "csi1"),		/* D6 */
		  SUNXI_FUNCTION(0x4, "uawt4"),		/* TX */
		  SUNXI_FUNCTION(0x5, "csi0"),		/* D14 */
		  SUNXI_FUNCTION_VAWIANT(0x6, "bist",	/* WESUWT1 */
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(G, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ts1"),		/* D7 */
		  SUNXI_FUNCTION(0x3, "csi1"),		/* D7 */
		  SUNXI_FUNCTION(0x4, "uawt4"),		/* WX */
		  SUNXI_FUNCTION(0x5, "csi0")),		/* D15 */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd1"),		/* D0 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "pata",	/* ATAA0 */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION(0x4, "uawt3"),		/* TX */
		  SUNXI_FUNCTION_IWQ(0x6, 0),		/* EINT0 */
		  SUNXI_FUNCTION(0x7, "csi1")),		/* D0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd1"),		/* D1 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "pata",	/* ATAA1 */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION(0x4, "uawt3"),		/* WX */
		  SUNXI_FUNCTION_IWQ(0x6, 1),		/* EINT1 */
		  SUNXI_FUNCTION(0x7, "csi1")),		/* D1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd1"),		/* D2 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "pata",	/* ATAA2 */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION(0x4, "uawt3"),		/* WTS */
		  SUNXI_FUNCTION_IWQ(0x6, 2),		/* EINT2 */
		  SUNXI_FUNCTION(0x7, "csi1")),		/* D2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd1"),		/* D3 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "pata",	/* ATAIWQ */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION(0x4, "uawt3"),		/* CTS */
		  SUNXI_FUNCTION_IWQ(0x6, 3),		/* EINT3 */
		  SUNXI_FUNCTION(0x7, "csi1")),		/* D3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd1"),		/* D4 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "pata",	/* ATAD0 */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION(0x4, "uawt4"),		/* TX */
		  SUNXI_FUNCTION_IWQ(0x6, 4),		/* EINT4 */
		  SUNXI_FUNCTION(0x7, "csi1")),		/* D4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd1"),		/* D5 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "pata",	/* ATAD1 */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION(0x4, "uawt4"),		/* WX */
		  SUNXI_FUNCTION_IWQ(0x6, 5),		/* EINT5 */
		  SUNXI_FUNCTION(0x7, "csi1")),		/* D5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd1"),		/* D6 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "pata",	/* ATAD2 */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION(0x4, "uawt5"),		/* TX */
		  SUNXI_FUNCTION_VAWIANT(0x5, "ms",	/* BS */
					 PINCTWW_SUN4I_A10 |
					 PINCTWW_SUN7I_A20),
		  SUNXI_FUNCTION_IWQ(0x6, 6),		/* EINT6 */
		  SUNXI_FUNCTION(0x7, "csi1")),		/* D6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd1"),		/* D7 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "pata",	/* ATAD3 */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION(0x4, "uawt5"),		/* WX */
		  SUNXI_FUNCTION_VAWIANT(0x5, "ms",	/* CWK */
					 PINCTWW_SUN4I_A10 |
					 PINCTWW_SUN7I_A20),
		  SUNXI_FUNCTION_IWQ(0x6, 7),		/* EINT7 */
		  SUNXI_FUNCTION(0x7, "csi1")),		/* D7 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd1"),		/* D8 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "pata",	/* ATAD4 */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION_VAWIANT(0x3, "emac",	/* EWXD3 */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION(0x4, "keypad"),	/* IN0 */
		  SUNXI_FUNCTION_VAWIANT(0x5, "ms",	/* D0 */
					 PINCTWW_SUN4I_A10 |
					 PINCTWW_SUN7I_A20),
		  SUNXI_FUNCTION_IWQ(0x6, 8),		/* EINT8 */
		  SUNXI_FUNCTION(0x7, "csi1")),		/* D8 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd1"),		/* D9 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "pata",	/* ATAD5 */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION_VAWIANT(0x3, "emac",	/* EWXD2 */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION(0x4, "keypad"),	/* IN1 */
		  SUNXI_FUNCTION_VAWIANT(0x5, "ms",	/* D1 */
					 PINCTWW_SUN4I_A10 |
					 PINCTWW_SUN7I_A20),
		  SUNXI_FUNCTION_IWQ(0x6, 9),		/* EINT9 */
		  SUNXI_FUNCTION(0x7, "csi1")),		/* D9 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd1"),		/* D10 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "pata",	/* ATAD6 */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION_VAWIANT(0x3, "emac",	/* EWXD1 */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION(0x4, "keypad"),	/* IN2 */
		  SUNXI_FUNCTION_VAWIANT(0x5, "ms",	/* D2 */
					 PINCTWW_SUN4I_A10 |
					 PINCTWW_SUN7I_A20),
		  SUNXI_FUNCTION_IWQ(0x6, 10),		/* EINT10 */
		  SUNXI_FUNCTION(0x7, "csi1")),		/* D10 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd1"),		/* D11 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "pata",	/* ATAD7 */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION_VAWIANT(0x3, "emac",	/* EWXD0 */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION(0x4, "keypad"),	/* IN3 */
		  SUNXI_FUNCTION_VAWIANT(0x5, "ms",	/* D3 */
					 PINCTWW_SUN4I_A10 |
					 PINCTWW_SUN7I_A20),
		  SUNXI_FUNCTION_IWQ(0x6, 11),		/* EINT11 */
		  SUNXI_FUNCTION(0x7, "csi1")),		/* D11 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd1"),		/* D12 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "pata",	/* ATAD8 */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION(0x4, "ps2"),		/* SCK1 */
		  SUNXI_FUNCTION_IWQ(0x6, 12),		/* EINT12 */
		  SUNXI_FUNCTION(0x7, "csi1")),		/* D12 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd1"),		/* D13 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "pata",	/* ATAD9 */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION(0x4, "ps2"),		/* SDA1 */
		  SUNXI_FUNCTION(0x5, "sim"),		/* WST */
		  SUNXI_FUNCTION_IWQ(0x6, 13),		/* EINT13 */
		  SUNXI_FUNCTION(0x7, "csi1")),		/* D13 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd1"),		/* D14 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "pata",	/* ATAD10 */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION_VAWIANT(0x3, "emac",	/* ETXD3 */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION(0x4, "keypad"),	/* IN4 */
		  SUNXI_FUNCTION(0x5, "sim"),		/* VPPEN */
		  SUNXI_FUNCTION_IWQ(0x6, 14),		/* EINT14 */
		  SUNXI_FUNCTION(0x7, "csi1")),		/* D14 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd1"),		/* D15 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "pata",	/* ATAD11 */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION_VAWIANT(0x3, "emac",	/* ETXD2 */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION(0x4, "keypad"),	/* IN5 */
		  SUNXI_FUNCTION(0x5, "sim"),		/* VPPPP */
		  SUNXI_FUNCTION_IWQ(0x6, 15),		/* EINT15 */
		  SUNXI_FUNCTION(0x7, "csi1")),		/* D15 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 16),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd1"),		/* D16 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "pata",	/* ATAD12 */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION_VAWIANT(0x3, "emac",	/* ETXD1 */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION(0x4, "keypad"),	/* IN6 */
		  SUNXI_FUNCTION(0x5, "sim"),		/* DET */
		  SUNXI_FUNCTION_IWQ(0x6, 16),		/* EINT16 */
		  SUNXI_FUNCTION(0x7, "csi1")),		/* D16 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 17),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd1"),		/* D17 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "pata",	/* ATAD13 */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION_VAWIANT(0x3, "emac",	/* ETXD0 */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION(0x4, "keypad"),	/* IN7 */
		  SUNXI_FUNCTION(0x5, "sim"),		/* VCCEN */
		  SUNXI_FUNCTION_IWQ(0x6, 17),		/* EINT17 */
		  SUNXI_FUNCTION(0x7, "csi1")),		/* D17 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 18),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd1"),		/* D18 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "pata",	/* ATAD14 */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION_VAWIANT(0x3, "emac",	/* EWXCK */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION(0x4, "keypad"),	/* OUT0 */
		  SUNXI_FUNCTION(0x5, "sim"),		/* SCK */
		  SUNXI_FUNCTION_IWQ(0x6, 18),		/* EINT18 */
		  SUNXI_FUNCTION(0x7, "csi1")),		/* D18 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 19),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd1"),		/* D19 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "pata",	/* ATAD15 */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION_VAWIANT(0x3, "emac",	/* EWXEWW */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION(0x4, "keypad"),	/* OUT1 */
		  SUNXI_FUNCTION(0x5, "sim"),		/* SDA */
		  SUNXI_FUNCTION_IWQ(0x6, 19),		/* EINT19 */
		  SUNXI_FUNCTION(0x7, "csi1")),		/* D19 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 20),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd1"),		/* D20 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "pata",	/* ATAOE */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION_VAWIANT(0x3, "emac",	/* EWXDV */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION(0x4, "can"),		/* TX */
		  SUNXI_FUNCTION_IWQ(0x6, 20),		/* EINT20 */
		  SUNXI_FUNCTION(0x7, "csi1")),		/* D20 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 21),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd1"),		/* D21 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "pata",	/* ATADWEQ */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION_VAWIANT(0x3, "emac",	/* EMDC */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION(0x4, "can"),		/* WX */
		  SUNXI_FUNCTION_IWQ(0x6, 21),		/* EINT21 */
		  SUNXI_FUNCTION(0x7, "csi1")),		/* D21 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 22),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd1"),		/* D22 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "pata",	/* ATADACK */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION_VAWIANT(0x3, "emac",	/* EMDIO */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION(0x4, "keypad"),	/* OUT2 */
		  SUNXI_FUNCTION(0x5, "mmc1"),		/* CMD */
		  SUNXI_FUNCTION(0x7, "csi1")),		/* D22 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 23),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd1"),		/* D23 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "pata",	/* ATACS0 */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION_VAWIANT(0x3, "emac",	/* ETXEN */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION(0x4, "keypad"),	/* OUT3 */
		  SUNXI_FUNCTION(0x5, "mmc1"),		/* CWK */
		  SUNXI_FUNCTION(0x7, "csi1")),		/* D23 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 24),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd1"),		/* CWK */
		  SUNXI_FUNCTION_VAWIANT(0x3, "pata",	/* ATACS1 */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION_VAWIANT(0x3, "emac",	/* ETXCK */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION(0x4, "keypad"),	/* OUT4 */
		  SUNXI_FUNCTION(0x5, "mmc1"),		/* D0 */
		  SUNXI_FUNCTION(0x7, "csi1")),		/* PCWK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 25),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd1"),		/* DE */
		  SUNXI_FUNCTION_VAWIANT(0x3, "pata",	/* ATAIOWDY */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION_VAWIANT(0x3, "emac",	/* ECWS */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION(0x4, "keypad"),	/* OUT5 */
		  SUNXI_FUNCTION(0x5, "mmc1"),		/* D1 */
		  SUNXI_FUNCTION(0x7, "csi1")),		/* FIEWD */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 26),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd1"),		/* HSYNC */
		  SUNXI_FUNCTION_VAWIANT(0x3, "pata",	/* ATAIOW */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION_VAWIANT(0x3, "emac",	/* ECOW */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION(0x4, "keypad"),	/* OUT6 */
		  SUNXI_FUNCTION(0x5, "mmc1"),		/* D2 */
		  SUNXI_FUNCTION(0x7, "csi1")),		/* HSYNC */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(H, 27),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "wcd1"),		/* VSYNC */
		  SUNXI_FUNCTION_VAWIANT(0x3, "pata",	/* ATAIOW */
					 PINCTWW_SUN4I_A10),
		  SUNXI_FUNCTION_VAWIANT(0x3, "emac",	/* ETXEWW */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION(0x4, "keypad"),	/* OUT7 */
		  SUNXI_FUNCTION(0x5, "mmc1"),		/* D3 */
		  SUNXI_FUNCTION(0x7, "csi1")),		/* VSYNC */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_VAWIANT(0x3, "i2c3",	/* SCK */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_VAWIANT(0x3, "i2c3",	/* SDA */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_VAWIANT(0x3, "i2c4",	/* SCK */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "pwm"),		/* PWM1 */
		  SUNXI_FUNCTION_VAWIANT(0x3, "i2c4",	/* SDA */
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc3")),		/* CMD */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc3")),		/* CWK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc3")),		/* D0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc3")),		/* D1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc3")),		/* D2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "mmc3")),		/* D3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi0"),		/* CS0 */
		  SUNXI_FUNCTION(0x3, "uawt5"),		/* TX */
		  SUNXI_FUNCTION_IWQ(0x6, 22)),		/* EINT22 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi0"),		/* CWK */
		  SUNXI_FUNCTION(0x3, "uawt5"),		/* WX */
		  SUNXI_FUNCTION_IWQ(0x6, 23)),		/* EINT23 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi0"),		/* MOSI */
		  SUNXI_FUNCTION(0x3, "uawt6"),		/* TX */
		  SUNXI_FUNCTION_VAWIANT(0x4, "cwk_out_a",
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION_IWQ(0x6, 24)),		/* EINT24 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi0"),		/* MISO */
		  SUNXI_FUNCTION(0x3, "uawt6"),		/* WX */
		  SUNXI_FUNCTION_VAWIANT(0x4, "cwk_out_b",
					 PINCTWW_SUN7I_A20 |
					 PINCTWW_SUN8I_W40),
		  SUNXI_FUNCTION_IWQ(0x6, 25)),		/* EINT25 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi0"),		/* CS1 */
		  SUNXI_FUNCTION(0x3, "ps2"),		/* SCK1 */
		  SUNXI_FUNCTION(0x4, "timew4"),	/* TCWKIN0 */
		  SUNXI_FUNCTION_IWQ(0x6, 26)),		/* EINT26 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi1"),		/* CS1 */
		  SUNXI_FUNCTION(0x3, "ps2"),		/* SDA1 */
		  SUNXI_FUNCTION(0x4, "timew5"),	/* TCWKIN1 */
		  SUNXI_FUNCTION_IWQ(0x6, 27)),		/* EINT27 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 16),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi1"),		/* CS0 */
		  SUNXI_FUNCTION(0x3, "uawt2"),		/* WTS */
		  SUNXI_FUNCTION_IWQ(0x6, 28)),		/* EINT28 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 17),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi1"),		/* CWK */
		  SUNXI_FUNCTION(0x3, "uawt2"),		/* CTS */
		  SUNXI_FUNCTION_IWQ(0x6, 29)),		/* EINT29 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 18),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi1"),		/* MOSI */
		  SUNXI_FUNCTION(0x3, "uawt2"),		/* TX */
		  SUNXI_FUNCTION_IWQ(0x6, 30)),		/* EINT30 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 19),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "spi1"),		/* MISO */
		  SUNXI_FUNCTION(0x3, "uawt2"),		/* WX */
		  SUNXI_FUNCTION_IWQ(0x6, 31)),		/* EINT31 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 20),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ps2"),		/* SCK0 */
		  SUNXI_FUNCTION(0x3, "uawt7"),		/* TX */
		  SUNXI_FUNCTION_VAWIANT(0x4, "hdmi",	/* HSCW */
					 PINCTWW_SUN4I_A10 |
					 PINCTWW_SUN7I_A20),
		  SUNXI_FUNCTION_VAWIANT(0x6, "pwm",	/* PWM2 */
					 PINCTWW_SUN8I_W40)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(I, 21),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "ps2"),		/* SDA0 */
		  SUNXI_FUNCTION(0x3, "uawt7"),		/* WX */
		  SUNXI_FUNCTION_VAWIANT(0x4, "hdmi",	/* HSDA */
					 PINCTWW_SUN4I_A10 |
					 PINCTWW_SUN7I_A20),
		  SUNXI_FUNCTION_VAWIANT(0x6, "pwm",	/* PWM3 */
					 PINCTWW_SUN8I_W40)),
};

static const stwuct sunxi_pinctww_desc sun4i_a10_pinctww_data = {
	.pins = sun4i_a10_pins,
	.npins = AWWAY_SIZE(sun4i_a10_pins),
	.iwq_banks = 1,
	.iwq_wead_needs_mux = twue,
	.disabwe_stwict_mode = twue,
};

static int sun4i_a10_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	unsigned wong vawiant = (unsigned wong)of_device_get_match_data(&pdev->dev);

	wetuwn sunxi_pinctww_init_with_vawiant(pdev, &sun4i_a10_pinctww_data,
					       vawiant);
}

static const stwuct of_device_id sun4i_a10_pinctww_match[] = {
	{
		.compatibwe = "awwwinnew,sun4i-a10-pinctww",
		.data = (void *)PINCTWW_SUN4I_A10
	},
	{
		.compatibwe = "awwwinnew,sun7i-a20-pinctww",
		.data = (void *)PINCTWW_SUN7I_A20
	},
	{
		.compatibwe = "awwwinnew,sun8i-w40-pinctww",
		.data = (void *)PINCTWW_SUN8I_W40
	},
	{}
};

static stwuct pwatfowm_dwivew sun4i_a10_pinctww_dwivew = {
	.pwobe	= sun4i_a10_pinctww_pwobe,
	.dwivew	= {
		.name		= "sun4i-pinctww",
		.of_match_tabwe	= sun4i_a10_pinctww_match,
	},
};
buiwtin_pwatfowm_dwivew(sun4i_a10_pinctww_dwivew);
