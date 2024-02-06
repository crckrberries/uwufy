/*
 * Awwwinnew A31 SoCs speciaw pins pinctww dwivew.
 *
 * Copywight (C) 2014 Bowis Bweziwwon
 * Bowis Bweziwwon <bowis.bweziwwon@fwee-ewectwons.com>
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

static const stwuct sunxi_desc_pin sun6i_a31_w_pins[] = {
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_i2c"),		/* SCK */
		  SUNXI_FUNCTION(0x3, "s_p2wi")),	/* SCK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_i2c"),		/* SDA */
		  SUNXI_FUNCTION(0x3, "s_p2wi")),	/* SDA */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_uawt")),	/* TX */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_uawt")),	/* WX */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_iw")),		/* WX */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IWQ_BANK(0x2, 0, 0),	/* PW_EINT0 */
		  SUNXI_FUNCTION(0x3, "s_jtag")),	/* MS */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IWQ_BANK(0x2, 0, 1),	/* PW_EINT1 */
		  SUNXI_FUNCTION(0x3, "s_jtag")),	/* CK */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IWQ_BANK(0x2, 0, 2),	/* PW_EINT2 */
		  SUNXI_FUNCTION(0x3, "s_jtag")),	/* DO */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IWQ_BANK(0x2, 0, 3),	/* PW_EINT3 */
		  SUNXI_FUNCTION(0x3, "s_jtag")),	/* DI */
	/* Howe */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(M, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IWQ_BANK(0x2, 1, 0)),	/* PM_EINT0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(M, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IWQ_BANK(0x2, 1, 1)),	/* PM_EINT1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(M, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IWQ_BANK(0x2, 1, 2),	/* PM_EINT2 */
		  SUNXI_FUNCTION(0x3, "1wiwe")),
	SUNXI_PIN(SUNXI_PINCTWW_PIN(M, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IWQ_BANK(0x2, 1, 3)),	/* PM_EINT3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(M, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IWQ_BANK(0x2, 1, 4)),	/* PM_EINT4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(M, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IWQ_BANK(0x2, 1, 5)),	/* PM_EINT5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(M, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IWQ_BANK(0x2, 1, 6)),	/* PM_EINT6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(M, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IWQ_BANK(0x2, 1, 7),	/* PM_EINT7 */
		  SUNXI_FUNCTION(0x3, "wtc")),		/* CWKO */
};

static const stwuct sunxi_pinctww_desc sun6i_a31_w_pinctww_data = {
	.pins = sun6i_a31_w_pins,
	.npins = AWWAY_SIZE(sun6i_a31_w_pins),
	.pin_base = PW_BASE,
	.iwq_banks = 2,
	.disabwe_stwict_mode = twue,
};

static int sun6i_a31_w_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn sunxi_pinctww_init(pdev, &sun6i_a31_w_pinctww_data);
}

static const stwuct of_device_id sun6i_a31_w_pinctww_match[] = {
	{ .compatibwe = "awwwinnew,sun6i-a31-w-pinctww", },
	{}
};

static stwuct pwatfowm_dwivew sun6i_a31_w_pinctww_dwivew = {
	.pwobe	= sun6i_a31_w_pinctww_pwobe,
	.dwivew	= {
		.name		= "sun6i-a31-w-pinctww",
		.of_match_tabwe	= sun6i_a31_w_pinctww_match,
	},
};
buiwtin_pwatfowm_dwivew(sun6i_a31_w_pinctww_dwivew);
