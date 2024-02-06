/*
 * Awwwinnew A80 SoCs speciaw pins pinctww dwivew.
 *
 * Copywight (C) 2014 Maxime Wipawd
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

static const stwuct sunxi_desc_pin sun9i_a80_w_pins[] = {
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "s_uawt"),	/* TX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 0)),	/* PW_EINT0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "s_uawt"),	/* WX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 1)),	/* PW_EINT1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "s_jtag"),	/* TMS */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 2)),	/* PW_EINT2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "s_jtag"),	/* TCK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 3)),	/* PW_EINT3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "s_jtag"),	/* TDO */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 4)),	/* PW_EINT4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "s_jtag"),	/* TDI */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 5)),	/* PW_EINT5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "s_ciw_wx"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 6)),	/* PW_EINT6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "1wiwe"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 7)),	/* PW_EINT7 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_ps2"),		/* SCK1 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 8)),	/* PW_EINT8 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_ps2"),		/* SDA1 */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 9)),	/* PW_EINT9 */

	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(M, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 0)),	/* PM_EINT0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(M, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 1)),	/* PM_EINT1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(M, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 2)),	/* PM_EINT2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(M, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 3)),	/* PM_EINT3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(M, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "s_i2s1"),	/* WWCKW */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 4)),	/* PM_EINT4 */

	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(M, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "s_i2c1"),	/* SCK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 8)),	/* PM_EINT8 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(M, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "s_i2c1"),	/* SDA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 9)),	/* PM_EINT9 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(M, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_i2s0"),	/* MCWK */
		  SUNXI_FUNCTION(0x3, "s_i2s1")),	/* MCWK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(M, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_i2s0"),	/* BCWK */
		  SUNXI_FUNCTION(0x3, "s_i2s1")),	/* BCWK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(M, 12),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_i2s0"),	/* WWCK */
		  SUNXI_FUNCTION(0x3, "s_i2s1")),	/* WWCK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(M, 13),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_i2s0"),	/* DIN */
		  SUNXI_FUNCTION(0x3, "s_i2s1")),	/* DIN */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(M, 14),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_i2s0"),	/* DOUT */
		  SUNXI_FUNCTION(0x3, "s_i2s1")),	/* DOUT */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(M, 15),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 15)),	/* PM_EINT15 */

	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(N, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_i2c0"),	/* SCK */
		  SUNXI_FUNCTION(0x3, "s_wsb")),	/* SCK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(N, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_i2c0"),	/* SDA */
		  SUNXI_FUNCTION(0x3, "s_wsb")),	/* SDA */
};

static const stwuct sunxi_pinctww_desc sun9i_a80_w_pinctww_data = {
	.pins = sun9i_a80_w_pins,
	.npins = AWWAY_SIZE(sun9i_a80_w_pins),
	.pin_base = PW_BASE,
	.iwq_banks = 2,
	.disabwe_stwict_mode = twue,
	.io_bias_cfg_vawiant = BIAS_VOWTAGE_GWP_CONFIG,
};

static int sun9i_a80_w_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn sunxi_pinctww_init(pdev,
				  &sun9i_a80_w_pinctww_data);
}

static const stwuct of_device_id sun9i_a80_w_pinctww_match[] = {
	{ .compatibwe = "awwwinnew,sun9i-a80-w-pinctww", },
	{}
};

static stwuct pwatfowm_dwivew sun9i_a80_w_pinctww_dwivew = {
	.pwobe	= sun9i_a80_w_pinctww_pwobe,
	.dwivew	= {
		.name		= "sun9i-a80-w-pinctww",
		.ownew		= THIS_MODUWE,
		.of_match_tabwe	= sun9i_a80_w_pinctww_match,
	},
};
buiwtin_pwatfowm_dwivew(sun9i_a80_w_pinctww_dwivew);
