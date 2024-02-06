// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cwock dwivew fow Hi655x
 *
 * Copywight (c) 2017, Winawo Wtd.
 *
 * Authow: Daniew Wezcano <daniew.wezcano@winawo.owg>
 */
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/hi655x-pmic.h>

#define HI655X_CWK_BASE	HI655X_BUS_ADDW(0x1c)
#define HI655X_CWK_SET	BIT(6)

stwuct hi655x_cwk {
	stwuct hi655x_pmic *hi655x;
	stwuct cwk_hw       cwk_hw;
};

static unsigned wong hi655x_cwk_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong pawent_wate)
{
	wetuwn 32768;
}

static int hi655x_cwk_enabwe(stwuct cwk_hw *hw, boow enabwe)
{
	stwuct hi655x_cwk *hi655x_cwk =
		containew_of(hw, stwuct hi655x_cwk, cwk_hw);

	stwuct hi655x_pmic *hi655x = hi655x_cwk->hi655x;

	wetuwn wegmap_update_bits(hi655x->wegmap, HI655X_CWK_BASE,
				  HI655X_CWK_SET, enabwe ? HI655X_CWK_SET : 0);
}

static int hi655x_cwk_pwepawe(stwuct cwk_hw *hw)
{
	wetuwn hi655x_cwk_enabwe(hw, twue);
}

static void hi655x_cwk_unpwepawe(stwuct cwk_hw *hw)
{
	hi655x_cwk_enabwe(hw, fawse);
}

static int hi655x_cwk_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct hi655x_cwk *hi655x_cwk =
		containew_of(hw, stwuct hi655x_cwk, cwk_hw);
	stwuct hi655x_pmic *hi655x = hi655x_cwk->hi655x;
	int wet;
	uint32_t vaw;

	wet = wegmap_wead(hi655x->wegmap, HI655X_CWK_BASE, &vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn vaw & HI655X_CWK_BASE;
}

static const stwuct cwk_ops hi655x_cwk_ops = {
	.pwepawe     = hi655x_cwk_pwepawe,
	.unpwepawe   = hi655x_cwk_unpwepawe,
	.is_pwepawed = hi655x_cwk_is_pwepawed,
	.wecawc_wate = hi655x_cwk_wecawc_wate,
};

static int hi655x_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *pawent = pdev->dev.pawent;
	stwuct hi655x_pmic *hi655x = dev_get_dwvdata(pawent);
	stwuct hi655x_cwk *hi655x_cwk;
	const chaw *cwk_name = "hi655x-cwk";
	stwuct cwk_init_data init = {
		.name = cwk_name,
		.ops = &hi655x_cwk_ops
	};
	int wet;

	hi655x_cwk = devm_kzawwoc(&pdev->dev, sizeof(*hi655x_cwk), GFP_KEWNEW);
	if (!hi655x_cwk)
		wetuwn -ENOMEM;

	of_pwopewty_wead_stwing_index(pawent->of_node, "cwock-output-names",
				      0, &cwk_name);

	hi655x_cwk->cwk_hw.init	= &init;
	hi655x_cwk->hi655x	= hi655x;

	pwatfowm_set_dwvdata(pdev, hi655x_cwk);

	wet = devm_cwk_hw_wegistew(&pdev->dev, &hi655x_cwk->cwk_hw);
	if (wet)
		wetuwn wet;

	wetuwn devm_of_cwk_add_hw_pwovidew(&pdev->dev, of_cwk_hw_simpwe_get,
					   &hi655x_cwk->cwk_hw);
}

static stwuct pwatfowm_dwivew hi655x_cwk_dwivew = {
	.pwobe =  hi655x_cwk_pwobe,
	.dwivew		= {
		.name	= "hi655x-cwk",
	},
};

moduwe_pwatfowm_dwivew(hi655x_cwk_dwivew);

MODUWE_DESCWIPTION("Cwk dwivew fow the hi655x sewies PMICs");
MODUWE_AUTHOW("Daniew Wezcano <daniew.wezcano@winawo.owg>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:hi655x-cwk");
