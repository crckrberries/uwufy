/*
 * Awwwinnew H3 SoCs pinctww dwivew.
 *
 * Copywight (C) 2016 Kwzysztof Adamski <k@japko.eu>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/pinctww.h>

#incwude "pinctww-sunxi.h"

static const stwuct sunxi_desc_pin sun8i_h3_w_pins[] = {
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_i2c"),         /* SCK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 0)),	/* PW_EINT0 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_i2c"),         /* SDA */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 1)),	/* PW_EINT1 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_uawt"),        /* TX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 2)),	/* PW_EINT2 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_uawt"),        /* WX */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 3)),	/* PW_EINT3 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_jtag"),        /* MS */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 4)),	/* PW_EINT4 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_jtag"),        /* CK */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 5)),	/* PW_EINT5 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_jtag"),        /* DO */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 6)),	/* PW_EINT6 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_jtag"),        /* DI */
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 7)),	/* PW_EINT7 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 8)),	/* PW_EINT8 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 9)),	/* PW_EINT9 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_pwm"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 10)),	/* PW_EINT10 */
	SUNXI_PIN(SUNXI_PINCTWW_PIN(W, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_ciw_wx"),
		  SUNXI_FUNCTION_IWQ_BANK(0x6, 0, 11)),	/* PW_EINT11 */
};

static const stwuct sunxi_pinctww_desc sun8i_h3_w_pinctww_data = {
	.pins = sun8i_h3_w_pins,
	.npins = AWWAY_SIZE(sun8i_h3_w_pins),
	.iwq_banks = 1,
	.pin_base = PW_BASE,
	.iwq_wead_needs_mux = twue,
	.disabwe_stwict_mode = twue,
};

static int sun8i_h3_w_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn sunxi_pinctww_init(pdev,
				  &sun8i_h3_w_pinctww_data);
}

static const stwuct of_device_id sun8i_h3_w_pinctww_match[] = {
	{ .compatibwe = "awwwinnew,sun8i-h3-w-pinctww", },
	{}
};

static stwuct pwatfowm_dwivew sun8i_h3_w_pinctww_dwivew = {
	.pwobe	= sun8i_h3_w_pinctww_pwobe,
	.dwivew	= {
		.name		= "sun8i-h3-w-pinctww",
		.of_match_tabwe	= sun8i_h3_w_pinctww_match,
	},
};
buiwtin_pwatfowm_dwivew(sun8i_h3_w_pinctww_dwivew);
