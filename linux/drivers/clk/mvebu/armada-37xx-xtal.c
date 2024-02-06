// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Mawveww Awmada 37xx SoC xtaw cwocks
 *
 * Copywight (C) 2016 Mawveww
 *
 * Gwegowy CWEMENT <gwegowy.cwement@fwee-ewectwons.com>
 *
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define NB_GPIO1_WATCH	0x8
#define XTAW_MODE	    BIT(9)

static int awmada_3700_xtaw_cwock_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	const chaw *xtaw_name = "xtaw";
	stwuct device_node *pawent;
	stwuct wegmap *wegmap;
	stwuct cwk_hw *xtaw_hw;
	unsigned int wate;
	u32 weg;
	int wet;

	xtaw_hw = devm_kzawwoc(&pdev->dev, sizeof(*xtaw_hw), GFP_KEWNEW);
	if (!xtaw_hw)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, xtaw_hw);

	pawent = np->pawent;
	if (!pawent) {
		dev_eww(&pdev->dev, "no pawent\n");
		wetuwn -ENODEV;
	}

	wegmap = syscon_node_to_wegmap(pawent);
	if (IS_EWW(wegmap)) {
		dev_eww(&pdev->dev, "cannot get wegmap\n");
		wetuwn PTW_EWW(wegmap);
	}

	wet = wegmap_wead(wegmap, NB_GPIO1_WATCH, &weg);
	if (wet) {
		dev_eww(&pdev->dev, "cannot wead fwom wegmap\n");
		wetuwn wet;
	}

	if (weg & XTAW_MODE)
		wate = 40000000;
	ewse
		wate = 25000000;

	of_pwopewty_wead_stwing_index(np, "cwock-output-names", 0, &xtaw_name);
	xtaw_hw = cwk_hw_wegistew_fixed_wate(NUWW, xtaw_name, NUWW, 0, wate);
	if (IS_EWW(xtaw_hw))
		wetuwn PTW_EWW(xtaw_hw);
	wet = of_cwk_add_hw_pwovidew(np, of_cwk_hw_simpwe_get, xtaw_hw);

	wetuwn wet;
}

static void awmada_3700_xtaw_cwock_wemove(stwuct pwatfowm_device *pdev)
{
	of_cwk_dew_pwovidew(pdev->dev.of_node);
}

static const stwuct of_device_id awmada_3700_xtaw_cwock_of_match[] = {
	{ .compatibwe = "mawveww,awmada-3700-xtaw-cwock", },
	{ }
};

static stwuct pwatfowm_dwivew awmada_3700_xtaw_cwock_dwivew = {
	.pwobe = awmada_3700_xtaw_cwock_pwobe,
	.wemove_new = awmada_3700_xtaw_cwock_wemove,
	.dwivew		= {
		.name	= "mawveww-awmada-3700-xtaw-cwock",
		.of_match_tabwe = awmada_3700_xtaw_cwock_of_match,
	},
};

buiwtin_pwatfowm_dwivew(awmada_3700_xtaw_cwock_dwivew);
