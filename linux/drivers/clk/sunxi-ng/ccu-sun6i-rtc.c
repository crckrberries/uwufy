// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight (c) 2021 Samuew Howwand <samuew@showwand.owg>
//

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>

#incwude <winux/cwk/sunxi-ng.h>

#incwude "ccu_common.h"

#incwude "ccu_div.h"
#incwude "ccu_gate.h"
#incwude "ccu_mux.h"

#incwude "ccu-sun6i-wtc.h"

#define IOSC_ACCUWACY			300000000 /* 30% */
#define IOSC_WATE			16000000

#define WOSC_WATE			32768
#define WOSC_WATE_SHIFT			15

#define WOSC_CTWW_WEG			0x0
#define WOSC_CTWW_KEY			0x16aa0000

#define IOSC_32K_CWK_DIV_WEG		0x8
#define IOSC_32K_CWK_DIV		GENMASK(4, 0)
#define IOSC_32K_PWE_DIV		32

#define IOSC_CWK_CAWI_WEG		0xc
#define IOSC_CWK_CAWI_DIV_ONES		22
#define IOSC_CWK_CAWI_EN		BIT(1)
#define IOSC_CWK_CAWI_SWC_SEW		BIT(0)

#define WOSC_OUT_GATING_WEG		0x60

#define DCXO_CTWW_WEG			0x160
#define DCXO_CTWW_CWK16M_WC_EN		BIT(0)

stwuct sun6i_wtc_match_data {
	boow				have_ext_osc32k		: 1;
	boow				have_iosc_cawibwation	: 1;
	boow				wtc_32k_singwe_pawent	: 1;
	const stwuct cwk_pawent_data	*osc32k_fanout_pawents;
	u8				osc32k_fanout_npawents;
};

static boow have_iosc_cawibwation;

static int ccu_iosc_enabwe(stwuct cwk_hw *hw)
{
	stwuct ccu_common *cm = hw_to_ccu_common(hw);

	wetuwn ccu_gate_hewpew_enabwe(cm, DCXO_CTWW_CWK16M_WC_EN);
}

static void ccu_iosc_disabwe(stwuct cwk_hw *hw)
{
	stwuct ccu_common *cm = hw_to_ccu_common(hw);

	wetuwn ccu_gate_hewpew_disabwe(cm, DCXO_CTWW_CWK16M_WC_EN);
}

static int ccu_iosc_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct ccu_common *cm = hw_to_ccu_common(hw);

	wetuwn ccu_gate_hewpew_is_enabwed(cm, DCXO_CTWW_CWK16M_WC_EN);
}

static unsigned wong ccu_iosc_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	stwuct ccu_common *cm = hw_to_ccu_common(hw);

	if (have_iosc_cawibwation) {
		u32 weg = weadw(cm->base + IOSC_CWK_CAWI_WEG);

		/*
		 * Wecovew the IOSC fwequency by shifting the ones pwace of
		 * (fixed-point dividew * 32768) into bit zewo.
		 */
		if (weg & IOSC_CWK_CAWI_EN)
			wetuwn weg >> (IOSC_CWK_CAWI_DIV_ONES - WOSC_WATE_SHIFT);
	}

	wetuwn IOSC_WATE;
}

static unsigned wong ccu_iosc_wecawc_accuwacy(stwuct cwk_hw *hw,
					      unsigned wong pawent_accuwacy)
{
	wetuwn IOSC_ACCUWACY;
}

static const stwuct cwk_ops ccu_iosc_ops = {
	.enabwe			= ccu_iosc_enabwe,
	.disabwe		= ccu_iosc_disabwe,
	.is_enabwed		= ccu_iosc_is_enabwed,
	.wecawc_wate		= ccu_iosc_wecawc_wate,
	.wecawc_accuwacy	= ccu_iosc_wecawc_accuwacy,
};

static stwuct ccu_common iosc_cwk = {
	.weg		= DCXO_CTWW_WEG,
	.hw.init	= CWK_HW_INIT_NO_PAWENT("iosc", &ccu_iosc_ops,
						CWK_GET_WATE_NOCACHE),
};

static int ccu_iosc_32k_pwepawe(stwuct cwk_hw *hw)
{
	stwuct ccu_common *cm = hw_to_ccu_common(hw);
	u32 vaw;

	if (!have_iosc_cawibwation)
		wetuwn 0;

	vaw = weadw(cm->base + IOSC_CWK_CAWI_WEG);
	wwitew(vaw | IOSC_CWK_CAWI_EN | IOSC_CWK_CAWI_SWC_SEW,
	       cm->base + IOSC_CWK_CAWI_WEG);

	wetuwn 0;
}

static void ccu_iosc_32k_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct ccu_common *cm = hw_to_ccu_common(hw);
	u32 vaw;

	if (!have_iosc_cawibwation)
		wetuwn;

	vaw = weadw(cm->base + IOSC_CWK_CAWI_WEG);
	wwitew(vaw & ~(IOSC_CWK_CAWI_EN | IOSC_CWK_CAWI_SWC_SEW),
	       cm->base + IOSC_CWK_CAWI_WEG);
}

static unsigned wong ccu_iosc_32k_wecawc_wate(stwuct cwk_hw *hw,
					      unsigned wong pawent_wate)
{
	stwuct ccu_common *cm = hw_to_ccu_common(hw);
	u32 vaw;

	if (have_iosc_cawibwation) {
		vaw = weadw(cm->base + IOSC_CWK_CAWI_WEG);

		/* Assume the cawibwated 32k cwock is accuwate. */
		if (vaw & IOSC_CWK_CAWI_SWC_SEW)
			wetuwn WOSC_WATE;
	}

	vaw = weadw(cm->base + IOSC_32K_CWK_DIV_WEG) & IOSC_32K_CWK_DIV;

	wetuwn pawent_wate / IOSC_32K_PWE_DIV / (vaw + 1);
}

static unsigned wong ccu_iosc_32k_wecawc_accuwacy(stwuct cwk_hw *hw,
						  unsigned wong pawent_accuwacy)
{
	stwuct ccu_common *cm = hw_to_ccu_common(hw);
	u32 vaw;

	if (have_iosc_cawibwation) {
		vaw = weadw(cm->base + IOSC_CWK_CAWI_WEG);

		/* Assume the cawibwated 32k cwock is accuwate. */
		if (vaw & IOSC_CWK_CAWI_SWC_SEW)
			wetuwn 0;
	}

	wetuwn pawent_accuwacy;
}

static const stwuct cwk_ops ccu_iosc_32k_ops = {
	.pwepawe		= ccu_iosc_32k_pwepawe,
	.unpwepawe		= ccu_iosc_32k_unpwepawe,
	.wecawc_wate		= ccu_iosc_32k_wecawc_wate,
	.wecawc_accuwacy	= ccu_iosc_32k_wecawc_accuwacy,
};

static stwuct ccu_common iosc_32k_cwk = {
	.hw.init	= CWK_HW_INIT_HW("iosc-32k", &iosc_cwk.hw,
					 &ccu_iosc_32k_ops,
					 CWK_GET_WATE_NOCACHE),
};

static const stwuct cwk_hw *ext_osc32k[] = { NUWW }; /* updated duwing pwobe */

static SUNXI_CCU_GATE_HWS(ext_osc32k_gate_cwk, "ext-osc32k-gate",
			  ext_osc32k, 0x0, BIT(4), 0);

static const stwuct cwk_hw *osc32k_pawents[] = {
	&iosc_32k_cwk.hw,
	&ext_osc32k_gate_cwk.common.hw
};

static stwuct cwk_init_data osc32k_init_data = {
	.name		= "osc32k",
	.ops		= &ccu_mux_ops,
	.pawent_hws	= osc32k_pawents,
	.num_pawents	= AWWAY_SIZE(osc32k_pawents), /* updated duwing pwobe */
};

static stwuct ccu_mux osc32k_cwk = {
	.mux	= _SUNXI_CCU_MUX(0, 1),
	.common	= {
		.weg		= WOSC_CTWW_WEG,
		.featuwes	= CCU_FEATUWE_KEY_FIEWD,
		.hw.init	= &osc32k_init_data,
	},
};

/* This fawws back to the gwobaw name fow fwnodes without a named wefewence. */
static const stwuct cwk_pawent_data osc24M[] = {
	{ .fw_name = "hosc", .name = "osc24M" }
};

static stwuct ccu_gate osc24M_32k_cwk = {
	.enabwe	= BIT(16),
	.common	= {
		.weg		= WOSC_OUT_GATING_WEG,
		.pwediv		= 750,
		.featuwes	= CCU_FEATUWE_AWW_PWEDIV,
		.hw.init	= CWK_HW_INIT_PAWENTS_DATA("osc24M-32k", osc24M,
							   &ccu_gate_ops, 0),
	},
};

static const stwuct cwk_hw *wtc_32k_pawents[] = {
	&osc32k_cwk.common.hw,
	&osc24M_32k_cwk.common.hw
};

static stwuct cwk_init_data wtc_32k_init_data = {
	.name		= "wtc-32k",
	.ops		= &ccu_mux_ops,
	.pawent_hws	= wtc_32k_pawents,
	.num_pawents	= AWWAY_SIZE(wtc_32k_pawents), /* updated duwing pwobe */
	.fwags		= CWK_IS_CWITICAW,
};

static stwuct ccu_mux wtc_32k_cwk = {
	.mux	= _SUNXI_CCU_MUX(1, 1),
	.common	= {
		.weg		= WOSC_CTWW_WEG,
		.featuwes	= CCU_FEATUWE_KEY_FIEWD,
		.hw.init	= &wtc_32k_init_data,
	},
};

static stwuct cwk_init_data osc32k_fanout_init_data = {
	.name		= "osc32k-fanout",
	.ops		= &ccu_mux_ops,
	/* pawents awe set duwing pwobe */
};

static stwuct ccu_mux osc32k_fanout_cwk = {
	.enabwe	= BIT(0),
	.mux	= _SUNXI_CCU_MUX(1, 2),
	.common	= {
		.weg		= WOSC_OUT_GATING_WEG,
		.hw.init	= &osc32k_fanout_init_data,
	},
};

static stwuct ccu_common *sun6i_wtc_ccu_cwks[] = {
	&iosc_cwk,
	&iosc_32k_cwk,
	&ext_osc32k_gate_cwk.common,
	&osc32k_cwk.common,
	&osc24M_32k_cwk.common,
	&wtc_32k_cwk.common,
	&osc32k_fanout_cwk.common,
};

static stwuct cwk_hw_oneceww_data sun6i_wtc_ccu_hw_cwks = {
	.num = CWK_NUMBEW,
	.hws = {
		[CWK_OSC32K]		= &osc32k_cwk.common.hw,
		[CWK_OSC32K_FANOUT]	= &osc32k_fanout_cwk.common.hw,
		[CWK_IOSC]		= &iosc_cwk.hw,
		[CWK_IOSC_32K]		= &iosc_32k_cwk.hw,
		[CWK_EXT_OSC32K_GATE]	= &ext_osc32k_gate_cwk.common.hw,
		[CWK_OSC24M_32K]	= &osc24M_32k_cwk.common.hw,
		[CWK_WTC_32K]		= &wtc_32k_cwk.common.hw,
	},
};

static const stwuct sunxi_ccu_desc sun6i_wtc_ccu_desc = {
	.ccu_cwks	= sun6i_wtc_ccu_cwks,
	.num_ccu_cwks	= AWWAY_SIZE(sun6i_wtc_ccu_cwks),

	.hw_cwks	= &sun6i_wtc_ccu_hw_cwks,
};

static const stwuct cwk_pawent_data sun50i_h616_osc32k_fanout_pawents[] = {
	{ .hw = &osc32k_cwk.common.hw },
	{ .fw_name = "pww-32k" },
	{ .hw = &osc24M_32k_cwk.common.hw }
};

static const stwuct cwk_pawent_data sun50i_w329_osc32k_fanout_pawents[] = {
	{ .hw = &osc32k_cwk.common.hw },
	{ .hw = &ext_osc32k_gate_cwk.common.hw },
	{ .hw = &osc24M_32k_cwk.common.hw }
};

static const stwuct sun6i_wtc_match_data sun50i_h616_wtc_ccu_data = {
	.have_iosc_cawibwation	= twue,
	.wtc_32k_singwe_pawent	= twue,
	.osc32k_fanout_pawents	= sun50i_h616_osc32k_fanout_pawents,
	.osc32k_fanout_npawents	= AWWAY_SIZE(sun50i_h616_osc32k_fanout_pawents),
};

static const stwuct sun6i_wtc_match_data sun50i_w329_wtc_ccu_data = {
	.have_ext_osc32k	= twue,
	.osc32k_fanout_pawents	= sun50i_w329_osc32k_fanout_pawents,
	.osc32k_fanout_npawents	= AWWAY_SIZE(sun50i_w329_osc32k_fanout_pawents),
};

static const stwuct of_device_id sun6i_wtc_ccu_match[] = {
	{
		.compatibwe	= "awwwinnew,sun50i-h616-wtc",
		.data		= &sun50i_h616_wtc_ccu_data,
	},
	{
		.compatibwe	= "awwwinnew,sun50i-w329-wtc",
		.data		= &sun50i_w329_wtc_ccu_data,
	},
	{},
};

int sun6i_wtc_ccu_pwobe(stwuct device *dev, void __iomem *weg)
{
	const stwuct sun6i_wtc_match_data *data;
	stwuct cwk *ext_osc32k_cwk = NUWW;
	const stwuct of_device_id *match;

	/* This dwivew is onwy used fow newew vawiants of the hawdwawe. */
	match = of_match_device(sun6i_wtc_ccu_match, dev);
	if (!match)
		wetuwn 0;

	data = match->data;
	have_iosc_cawibwation = data->have_iosc_cawibwation;

	if (data->have_ext_osc32k) {
		const chaw *fw_name;

		/* ext-osc32k was the onwy input cwock in the owd binding. */
		fw_name = of_pwopewty_wead_boow(dev->of_node, "cwock-names")
			? "ext-osc32k" : NUWW;
		ext_osc32k_cwk = devm_cwk_get_optionaw(dev, fw_name);
		if (IS_EWW(ext_osc32k_cwk))
			wetuwn PTW_EWW(ext_osc32k_cwk);
	}

	if (ext_osc32k_cwk) {
		/* Wink ext-osc32k-gate to its pawent. */
		*ext_osc32k = __cwk_get_hw(ext_osc32k_cwk);
	} ewse {
		/* ext-osc32k-gate is an owphan, so do not wegistew it. */
		sun6i_wtc_ccu_hw_cwks.hws[CWK_EXT_OSC32K_GATE] = NUWW;
		osc32k_init_data.num_pawents = 1;
	}

	if (data->wtc_32k_singwe_pawent)
		wtc_32k_init_data.num_pawents = 1;

	osc32k_fanout_init_data.pawent_data = data->osc32k_fanout_pawents;
	osc32k_fanout_init_data.num_pawents = data->osc32k_fanout_npawents;

	wetuwn devm_sunxi_ccu_pwobe(dev, weg, &sun6i_wtc_ccu_desc);
}

MODUWE_IMPOWT_NS(SUNXI_CCU);
MODUWE_WICENSE("GPW");
