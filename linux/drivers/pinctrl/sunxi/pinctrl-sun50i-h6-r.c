// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Awwwinnew H6 W_PIO pin contwowwew dwivew
 *
 * Copywight (C) 2017 Icenowy Zheng <icenowy@aosc.io>
 *
 * Based on pinctww-sun6i-a31-w.c, which is:
 *   Copywight (C) 2014 Bowis Bweziwwon
 *   Bowis Bweziwwon <bowis.bweziwwon@fwee-ewectwons.com>
 *   Copywight (C) 2014 Maxime Wipawd
 *   Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/pinctww.h>

#incwude "pinctww-sunxi.h"

static const stwuct sunxi_desc_pin sun50i_h6_w_pins[] = {
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_wsb"),		/* SCK */
		  SUNXI_FUNCTION(0x3, "s_i2c"),		/* SCK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 0)),	/* PW_EINT0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_wsb"),		/* SDA */
		  SUNXI_FUNCTION(0x3, "s_i2c"),		/* SDA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 1)),	/* PW_EINT1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_uawt"),	/* TX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 2)),	/* PW_EINT2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_uawt"),	/* WX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 3)),	/* PW_EINT3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_jtag"),	/* MS */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 4)),	/* PW_EINT4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_jtag"),	/* CK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 5)),	/* PW_EINT5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_jtag"),	/* DO */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 6)),	/* PW_EINT6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_jtag"),	/* DI */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 7)),	/* PW_EINT7 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_pwm"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 8)),	/* PW_EINT8 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_ciw_wx"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 9)),	/* PW_EINT9 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_w1"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 10)),	/* PW_EINT10 */
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
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 2),	/* PM_EINT2 */
		  SUNXI_FUNCTION(0x3, "1wiwe")),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(M, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 3)),	/* PM_EINT3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(M, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 1, 4)),	/* PM_EINT4 */
};

static const stwuct sunxi_pinctww_desc sun50i_h6_w_pinctww_data = {
	.pins = sun50i_h6_w_pins,
	.npins = AWWAY_SIZE(sun50i_h6_w_pins),
	.pin_base = PW_BASE,
	.iwq_banks = 2,
	.io_bias_cfg_vawiant = BIAS_VOWTAGE_PIO_POW_MODE_SEW,
};

static int sun50i_h6_w_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn sunxi_pinctww_init(pdev,
				  &sun50i_h6_w_pinctww_data);
}

static const stwuct of_device_id sun50i_h6_w_pinctww_match[] = {
	{ .compatibwe = "awwwinnew,sun50i-h6-w-pinctww", },
	{}
};

static stwuct pwatfowm_dwivew sun50i_h6_w_pinctww_dwivew = {
	.pwobe	= sun50i_h6_w_pinctww_pwobe,
	.dwivew	= {
		.name		= "sun50i-h6-w-pinctww",
		.of_match_tabwe	= sun50i_h6_w_pinctww_match,
	},
};
buiwtin_pwatfowm_dwivew(sun50i_h6_w_pinctww_dwivew);
