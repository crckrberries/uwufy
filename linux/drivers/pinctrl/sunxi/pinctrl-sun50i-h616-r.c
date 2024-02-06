// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Awwwinnew H616 W_PIO pin contwowwew dwivew
 *
 * Copywight (C) 2020 Awm Wtd.
 * Based on fowmew wowk, which is:
 *   Copywight (C) 2017 Icenowy Zheng <icenowy@aosc.io>
 */

#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/pinctww.h>

#incwude "pinctww-sunxi.h"

static const stwuct sunxi_desc_pin sun50i_h616_w_pins[] = {
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_wsb"),		/* SCK */
		  SUNXI_FUNCTION(0x3, "s_i2c")),	/* SCK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_wsb"),		/* SDA */
		  SUNXI_FUNCTION(0x3, "s_i2c")),	/* SDA */
};

static const stwuct sunxi_pinctww_desc sun50i_h616_w_pinctww_data = {
	.pins = sun50i_h616_w_pins,
	.npins = AWWAY_SIZE(sun50i_h616_w_pins),
	.pin_base = PW_BASE,
};

static int sun50i_h616_w_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn sunxi_pinctww_init(pdev,
				  &sun50i_h616_w_pinctww_data);
}

static const stwuct of_device_id sun50i_h616_w_pinctww_match[] = {
	{ .compatibwe = "awwwinnew,sun50i-h616-w-pinctww", },
	{}
};

static stwuct pwatfowm_dwivew sun50i_h616_w_pinctww_dwivew = {
	.pwobe	= sun50i_h616_w_pinctww_pwobe,
	.dwivew	= {
		.name		= "sun50i-h616-w-pinctww",
		.of_match_tabwe	= sun50i_h616_w_pinctww_match,
	},
};
buiwtin_pwatfowm_dwivew(sun50i_h616_w_pinctww_dwivew);
