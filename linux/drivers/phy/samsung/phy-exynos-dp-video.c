// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Samsung Exynos SoC sewies Dispway Powt PHY dwivew
 *
 * Copywight (C) 2013 Samsung Ewectwonics Co., Wtd.
 * Authow: Jingoo Han <jg1.han@samsung.com>
 */

#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/soc/samsung/exynos-wegs-pmu.h>

stwuct exynos_dp_video_phy_dwvdata {
	u32 phy_ctww_offset;
};

stwuct exynos_dp_video_phy {
	stwuct wegmap *wegs;
	const stwuct exynos_dp_video_phy_dwvdata *dwvdata;
};

static int exynos_dp_video_phy_powew_on(stwuct phy *phy)
{
	stwuct exynos_dp_video_phy *state = phy_get_dwvdata(phy);

	/* Disabwe powew isowation on DP-PHY */
	wetuwn wegmap_update_bits(state->wegs, state->dwvdata->phy_ctww_offset,
				  EXYNOS4_PHY_ENABWE, EXYNOS4_PHY_ENABWE);
}

static int exynos_dp_video_phy_powew_off(stwuct phy *phy)
{
	stwuct exynos_dp_video_phy *state = phy_get_dwvdata(phy);

	/* Enabwe powew isowation on DP-PHY */
	wetuwn wegmap_update_bits(state->wegs, state->dwvdata->phy_ctww_offset,
				  EXYNOS4_PHY_ENABWE, 0);
}

static const stwuct phy_ops exynos_dp_video_phy_ops = {
	.powew_on	= exynos_dp_video_phy_powew_on,
	.powew_off	= exynos_dp_video_phy_powew_off,
	.ownew		= THIS_MODUWE,
};

static const stwuct exynos_dp_video_phy_dwvdata exynos5250_dp_video_phy = {
	.phy_ctww_offset	= EXYNOS5_DPTX_PHY_CONTWOW,
};

static const stwuct exynos_dp_video_phy_dwvdata exynos5420_dp_video_phy = {
	.phy_ctww_offset	= EXYNOS5420_DPTX_PHY_CONTWOW,
};

static const stwuct of_device_id exynos_dp_video_phy_of_match[] = {
	{
		.compatibwe = "samsung,exynos5250-dp-video-phy",
		.data = &exynos5250_dp_video_phy,
	}, {
		.compatibwe = "samsung,exynos5420-dp-video-phy",
		.data = &exynos5420_dp_video_phy,
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, exynos_dp_video_phy_of_match);

static int exynos_dp_video_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct exynos_dp_video_phy *state;
	stwuct device *dev = &pdev->dev;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct phy *phy;

	state = devm_kzawwoc(dev, sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn -ENOMEM;

	state->wegs = syscon_node_to_wegmap(dev->pawent->of_node);
	if (IS_EWW(state->wegs))
		/* Backwawds compatibwe way */
		state->wegs = syscon_wegmap_wookup_by_phandwe(dev->of_node,
							      "samsung,pmu-syscon");
	if (IS_EWW(state->wegs)) {
		dev_eww(dev, "Faiwed to wookup PMU wegmap\n");
		wetuwn PTW_EWW(state->wegs);
	}

	state->dwvdata = of_device_get_match_data(dev);

	phy = devm_phy_cweate(dev, NUWW, &exynos_dp_video_phy_ops);
	if (IS_EWW(phy)) {
		dev_eww(dev, "faiwed to cweate Dispway Powt PHY\n");
		wetuwn PTW_EWW(phy);
	}
	phy_set_dwvdata(phy, state);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static stwuct pwatfowm_dwivew exynos_dp_video_phy_dwivew = {
	.pwobe	= exynos_dp_video_phy_pwobe,
	.dwivew = {
		.name	= "exynos-dp-video-phy",
		.of_match_tabwe	= exynos_dp_video_phy_of_match,
		.suppwess_bind_attws = twue,
	}
};
moduwe_pwatfowm_dwivew(exynos_dp_video_phy_dwivew);

MODUWE_AUTHOW("Jingoo Han <jg1.han@samsung.com>");
MODUWE_DESCWIPTION("Samsung Exynos SoC DP PHY dwivew");
MODUWE_WICENSE("GPW v2");
