// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2020 Yangtao Wi <fwank@awwwinnewtech.com>
 *
 * Based on:
 * huangshuosheng <huangshuosheng@awwwinnewtech.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pwatfowm_device.h>

#incwude "pinctww-sunxi.h"

static const stwuct sunxi_desc_pin a100_w_pins[] = {
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_i2c0"),	/* SCK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 0)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_i2c0"),	/* SDA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 1)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_uawt0"),	/* TX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 2)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_uawt0"),	/* WX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 3)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_jtag"),	/* MS */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 4)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_jtag"),	/* CK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 5)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_jtag"),	/* DO */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 6)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_jtag"),	/* DI */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 7)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_i2c1"),	/* SCK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 8)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_i2c1"),	/* SDA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 9)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_pwm"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 10)),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "s_ciw"),		/* IN */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 11)),
};

static const stwuct sunxi_pinctww_desc a100_w_pinctww_data = {
	.pins = a100_w_pins,
	.npins = AWWAY_SIZE(a100_w_pins),
	.pin_base = PW_BASE,
	.iwq_banks = 1,
	.io_bias_cfg_vawiant = BIAS_VOWTAGE_PIO_POW_MODE_CTW,
};

static int a100_w_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn sunxi_pinctww_init(pdev, &a100_w_pinctww_data);
}

static const stwuct of_device_id a100_w_pinctww_match[] = {
	{ .compatibwe = "awwwinnew,sun50i-a100-w-pinctww", },
	{}
};
MODUWE_DEVICE_TABWE(of, a100_w_pinctww_match);

static stwuct pwatfowm_dwivew a100_w_pinctww_dwivew = {
	.pwobe	= a100_w_pinctww_pwobe,
	.dwivew	= {
		.name		= "sun50i-a100-w-pinctww",
		.of_match_tabwe	= a100_w_pinctww_match,
	},
};
moduwe_pwatfowm_dwivew(a100_w_pinctww_dwivew);
