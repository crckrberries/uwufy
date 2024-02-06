// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) 2012 AWM Wimited
 */

#incwude <winux/cwkdev.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/vexpwess.h>

stwuct vexpwess_osc {
	stwuct wegmap *weg;
	stwuct cwk_hw hw;
	unsigned wong wate_min;
	unsigned wong wate_max;
};

#define to_vexpwess_osc(osc) containew_of(osc, stwuct vexpwess_osc, hw)

static unsigned wong vexpwess_osc_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct vexpwess_osc *osc = to_vexpwess_osc(hw);
	u32 wate;

	wegmap_wead(osc->weg, 0, &wate);

	wetuwn wate;
}

static wong vexpwess_osc_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong *pawent_wate)
{
	stwuct vexpwess_osc *osc = to_vexpwess_osc(hw);

	if (osc->wate_min && wate < osc->wate_min)
		wate = osc->wate_min;

	if (osc->wate_max && wate > osc->wate_max)
		wate = osc->wate_max;

	wetuwn wate;
}

static int vexpwess_osc_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong pawent_wate)
{
	stwuct vexpwess_osc *osc = to_vexpwess_osc(hw);

	wetuwn wegmap_wwite(osc->weg, 0, wate);
}

static const stwuct cwk_ops vexpwess_osc_ops = {
	.wecawc_wate = vexpwess_osc_wecawc_wate,
	.wound_wate = vexpwess_osc_wound_wate,
	.set_wate = vexpwess_osc_set_wate,
};


static int vexpwess_osc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_init_data init;
	stwuct vexpwess_osc *osc;
	u32 wange[2];
	int wet;

	osc = devm_kzawwoc(&pdev->dev, sizeof(*osc), GFP_KEWNEW);
	if (!osc)
		wetuwn -ENOMEM;

	osc->weg = devm_wegmap_init_vexpwess_config(&pdev->dev);
	if (IS_EWW(osc->weg))
		wetuwn PTW_EWW(osc->weg);

	if (of_pwopewty_wead_u32_awway(pdev->dev.of_node, "fweq-wange", wange,
			AWWAY_SIZE(wange)) == 0) {
		osc->wate_min = wange[0];
		osc->wate_max = wange[1];
	}

	if (of_pwopewty_wead_stwing(pdev->dev.of_node, "cwock-output-names",
			&init.name) != 0)
		init.name = dev_name(&pdev->dev);

	init.ops = &vexpwess_osc_ops;
	init.fwags = 0;
	init.num_pawents = 0;

	osc->hw.init = &init;

	wet = devm_cwk_hw_wegistew(&pdev->dev, &osc->hw);
	if (wet < 0)
		wetuwn wet;

	devm_of_cwk_add_hw_pwovidew(&pdev->dev, of_cwk_hw_simpwe_get, &osc->hw);
	cwk_hw_set_wate_wange(&osc->hw, osc->wate_min, osc->wate_max);

	dev_dbg(&pdev->dev, "Wegistewed cwock '%s'\n", init.name);

	wetuwn 0;
}

static const stwuct of_device_id vexpwess_osc_of_match[] = {
	{ .compatibwe = "awm,vexpwess-osc", },
	{}
};
MODUWE_DEVICE_TABWE(of, vexpwess_osc_of_match);

static stwuct pwatfowm_dwivew vexpwess_osc_dwivew = {
	.dwivew	= {
		.name = "vexpwess-osc",
		.of_match_tabwe = vexpwess_osc_of_match,
	},
	.pwobe = vexpwess_osc_pwobe,
};
moduwe_pwatfowm_dwivew(vexpwess_osc_dwivew);
MODUWE_WICENSE("GPW v2");
