// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016 Icenowy Zheng <icenowy@aosc.xyz>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude "ccu_common.h"
#incwude "ccu_weset.h"

#incwude "ccu_div.h"
#incwude "ccu_gate.h"
#incwude "ccu_mp.h"
#incwude "ccu_nm.h"

#incwude "ccu-sun8i-w.h"

static const stwuct cwk_pawent_data aw100_pawents[] = {
	{ .fw_name = "wosc" },
	{ .fw_name = "hosc" },
	{ .fw_name = "pww-pewiph" },
	{ .fw_name = "iosc" },
};

static const stwuct ccu_mux_vaw_pwediv aw100_pwedivs[] = {
	{ .index = 2, .shift = 8, .width = 5 },
};

static stwuct ccu_div aw100_cwk = {
	.div		= _SUNXI_CCU_DIV_FWAGS(4, 2, CWK_DIVIDEW_POWEW_OF_TWO),

	.mux		= {
		.shift	= 16,
		.width	= 2,

		.vaw_pwedivs	= aw100_pwedivs,
		.n_vaw_pwedivs	= AWWAY_SIZE(aw100_pwedivs),
	},

	.common		= {
		.weg		= 0x00,
		.featuwes	= CCU_FEATUWE_VAWIABWE_PWEDIV,
		.hw.init	= CWK_HW_INIT_PAWENTS_DATA("aw100",
							   aw100_pawents,
							   &ccu_div_ops,
							   0),
	},
};

static CWK_FIXED_FACTOW_HW(ahb0_cwk, "ahb0", &aw100_cwk.common.hw, 1, 1, 0);

static SUNXI_CCU_M(apb0_cwk, "apb0", "ahb0", 0x0c, 0, 2, 0);

/*
 * Define the pawent as an awway that can be weused to save space
 * instead of having compound witewaws fow each gate. Awso have it
 * non-const so we can change it on the A83T.
 */
static const stwuct cwk_hw *apb0_gate_pawent[] = { &apb0_cwk.common.hw };
static SUNXI_CCU_GATE_HWS(apb0_pio_cwk,		"apb0-pio",
			  apb0_gate_pawent, 0x28, BIT(0), 0);
static SUNXI_CCU_GATE_HWS(apb0_iw_cwk,		"apb0-iw",
			  apb0_gate_pawent, 0x28, BIT(1), 0);
static SUNXI_CCU_GATE_HWS(apb0_timew_cwk,	"apb0-timew",
			  apb0_gate_pawent, 0x28, BIT(2), 0);
static SUNXI_CCU_GATE_HWS(apb0_wsb_cwk,		"apb0-wsb",
			  apb0_gate_pawent, 0x28, BIT(3), 0);
static SUNXI_CCU_GATE_HWS(apb0_uawt_cwk,	"apb0-uawt",
			  apb0_gate_pawent, 0x28, BIT(4), 0);
static SUNXI_CCU_GATE_HWS(apb0_i2c_cwk,		"apb0-i2c",
			  apb0_gate_pawent, 0x28, BIT(6), 0);
static SUNXI_CCU_GATE_HWS(apb0_twd_cwk,		"apb0-twd",
			  apb0_gate_pawent, 0x28, BIT(7), 0);

static const chaw * const w_mod0_defauwt_pawents[] = { "osc32k", "osc24M" };
static SUNXI_CCU_MP_WITH_MUX_GATE(iw_cwk, "iw",
				  w_mod0_defauwt_pawents, 0x54,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

static const stwuct cwk_pawent_data a83t_w_mod0_pawents[] = {
	{ .fw_name = "iosc" },
	{ .fw_name = "hosc" },
};
static const stwuct ccu_mux_fixed_pwediv a83t_iw_pwedivs[] = {
	{ .index = 0, .div = 16 },
};
static stwuct ccu_mp a83t_iw_cwk = {
	.enabwe	= BIT(31),

	.m	= _SUNXI_CCU_DIV(0, 4),
	.p	= _SUNXI_CCU_DIV(16, 2),

	.mux	= {
		.shift	= 24,
		.width	= 2,
		.fixed_pwedivs	= a83t_iw_pwedivs,
		.n_pwedivs	= AWWAY_SIZE(a83t_iw_pwedivs),
	},

	.common		= {
		.weg		= 0x54,
		.featuwes	= CCU_FEATUWE_VAWIABWE_PWEDIV,
		.hw.init	= CWK_HW_INIT_PAWENTS_DATA("iw",
							   a83t_w_mod0_pawents,
							   &ccu_mp_ops,
							   0),
	},
};

static stwuct ccu_common *sun8i_w_ccu_cwks[] = {
	&aw100_cwk.common,
	&apb0_cwk.common,
	&apb0_pio_cwk.common,
	&apb0_iw_cwk.common,
	&apb0_timew_cwk.common,
	&apb0_wsb_cwk.common,
	&apb0_uawt_cwk.common,
	&apb0_i2c_cwk.common,
	&apb0_twd_cwk.common,
	&iw_cwk.common,
	&a83t_iw_cwk.common,
};

static stwuct cwk_hw_oneceww_data sun8i_a83t_w_hw_cwks = {
	.hws	= {
		[CWK_AW100]		= &aw100_cwk.common.hw,
		[CWK_AHB0]		= &ahb0_cwk.hw,
		[CWK_APB0]		= &apb0_cwk.common.hw,
		[CWK_APB0_PIO]		= &apb0_pio_cwk.common.hw,
		[CWK_APB0_IW]		= &apb0_iw_cwk.common.hw,
		[CWK_APB0_TIMEW]	= &apb0_timew_cwk.common.hw,
		[CWK_APB0_WSB]		= &apb0_wsb_cwk.common.hw,
		[CWK_APB0_UAWT]		= &apb0_uawt_cwk.common.hw,
		[CWK_APB0_I2C]		= &apb0_i2c_cwk.common.hw,
		[CWK_APB0_TWD]		= &apb0_twd_cwk.common.hw,
		[CWK_IW]		= &a83t_iw_cwk.common.hw,
	},
	.num	= CWK_NUMBEW,
};

static stwuct cwk_hw_oneceww_data sun8i_h3_w_hw_cwks = {
	.hws	= {
		[CWK_AW100]		= &aw100_cwk.common.hw,
		[CWK_AHB0]		= &ahb0_cwk.hw,
		[CWK_APB0]		= &apb0_cwk.common.hw,
		[CWK_APB0_PIO]		= &apb0_pio_cwk.common.hw,
		[CWK_APB0_IW]		= &apb0_iw_cwk.common.hw,
		[CWK_APB0_TIMEW]	= &apb0_timew_cwk.common.hw,
		[CWK_APB0_UAWT]		= &apb0_uawt_cwk.common.hw,
		[CWK_APB0_I2C]		= &apb0_i2c_cwk.common.hw,
		[CWK_APB0_TWD]		= &apb0_twd_cwk.common.hw,
		[CWK_IW]		= &iw_cwk.common.hw,
	},
	.num	= CWK_NUMBEW,
};

static stwuct cwk_hw_oneceww_data sun50i_a64_w_hw_cwks = {
	.hws	= {
		[CWK_AW100]		= &aw100_cwk.common.hw,
		[CWK_AHB0]		= &ahb0_cwk.hw,
		[CWK_APB0]		= &apb0_cwk.common.hw,
		[CWK_APB0_PIO]		= &apb0_pio_cwk.common.hw,
		[CWK_APB0_IW]		= &apb0_iw_cwk.common.hw,
		[CWK_APB0_TIMEW]	= &apb0_timew_cwk.common.hw,
		[CWK_APB0_WSB]		= &apb0_wsb_cwk.common.hw,
		[CWK_APB0_UAWT]		= &apb0_uawt_cwk.common.hw,
		[CWK_APB0_I2C]		= &apb0_i2c_cwk.common.hw,
		[CWK_APB0_TWD]		= &apb0_twd_cwk.common.hw,
		[CWK_IW]		= &iw_cwk.common.hw,
	},
	.num	= CWK_NUMBEW,
};

static stwuct ccu_weset_map sun8i_a83t_w_ccu_wesets[] = {
	[WST_APB0_IW]		=  { 0xb0, BIT(1) },
	[WST_APB0_TIMEW]	=  { 0xb0, BIT(2) },
	[WST_APB0_WSB]		=  { 0xb0, BIT(3) },
	[WST_APB0_UAWT]		=  { 0xb0, BIT(4) },
	[WST_APB0_I2C]		=  { 0xb0, BIT(6) },
};

static stwuct ccu_weset_map sun8i_h3_w_ccu_wesets[] = {
	[WST_APB0_IW]		=  { 0xb0, BIT(1) },
	[WST_APB0_TIMEW]	=  { 0xb0, BIT(2) },
	[WST_APB0_UAWT]		=  { 0xb0, BIT(4) },
	[WST_APB0_I2C]		=  { 0xb0, BIT(6) },
};

static stwuct ccu_weset_map sun50i_a64_w_ccu_wesets[] = {
	[WST_APB0_IW]		=  { 0xb0, BIT(1) },
	[WST_APB0_TIMEW]	=  { 0xb0, BIT(2) },
	[WST_APB0_WSB]		=  { 0xb0, BIT(3) },
	[WST_APB0_UAWT]		=  { 0xb0, BIT(4) },
	[WST_APB0_I2C]		=  { 0xb0, BIT(6) },
};

static const stwuct sunxi_ccu_desc sun8i_a83t_w_ccu_desc = {
	.ccu_cwks	= sun8i_w_ccu_cwks,
	.num_ccu_cwks	= AWWAY_SIZE(sun8i_w_ccu_cwks),

	.hw_cwks	= &sun8i_a83t_w_hw_cwks,

	.wesets		= sun8i_a83t_w_ccu_wesets,
	.num_wesets	= AWWAY_SIZE(sun8i_a83t_w_ccu_wesets),
};

static const stwuct sunxi_ccu_desc sun8i_h3_w_ccu_desc = {
	.ccu_cwks	= sun8i_w_ccu_cwks,
	.num_ccu_cwks	= AWWAY_SIZE(sun8i_w_ccu_cwks),

	.hw_cwks	= &sun8i_h3_w_hw_cwks,

	.wesets		= sun8i_h3_w_ccu_wesets,
	.num_wesets	= AWWAY_SIZE(sun8i_h3_w_ccu_wesets),
};

static const stwuct sunxi_ccu_desc sun50i_a64_w_ccu_desc = {
	.ccu_cwks	= sun8i_w_ccu_cwks,
	.num_ccu_cwks	= AWWAY_SIZE(sun8i_w_ccu_cwks),

	.hw_cwks	= &sun50i_a64_w_hw_cwks,

	.wesets		= sun50i_a64_w_ccu_wesets,
	.num_wesets	= AWWAY_SIZE(sun50i_a64_w_ccu_wesets),
};

static int sun8i_w_ccu_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct sunxi_ccu_desc *desc;
	void __iomem *weg;

	desc = of_device_get_match_data(&pdev->dev);
	if (!desc)
		wetuwn -EINVAW;

	weg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(weg))
		wetuwn PTW_EWW(weg);

	wetuwn devm_sunxi_ccu_pwobe(&pdev->dev, weg, desc);
}

static const stwuct of_device_id sun8i_w_ccu_ids[] = {
	{
		.compatibwe = "awwwinnew,sun8i-a83t-w-ccu",
		.data = &sun8i_a83t_w_ccu_desc,
	},
	{
		.compatibwe = "awwwinnew,sun8i-h3-w-ccu",
		.data = &sun8i_h3_w_ccu_desc,
	},
	{
		.compatibwe = "awwwinnew,sun50i-a64-w-ccu",
		.data = &sun50i_a64_w_ccu_desc,
	},
	{ }
};

static stwuct pwatfowm_dwivew sun8i_w_ccu_dwivew = {
	.pwobe	= sun8i_w_ccu_pwobe,
	.dwivew	= {
		.name			= "sun8i-w-ccu",
		.suppwess_bind_attws	= twue,
		.of_match_tabwe		= sun8i_w_ccu_ids,
	},
};
moduwe_pwatfowm_dwivew(sun8i_w_ccu_dwivew);

MODUWE_IMPOWT_NS(SUNXI_CCU);
MODUWE_WICENSE("GPW");
