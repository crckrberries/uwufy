// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude "hdmi.h"

static int msm_hdmi_phy_wesouwce_init(stwuct hdmi_phy *phy)
{
	stwuct hdmi_phy_cfg *cfg = phy->cfg;
	stwuct device *dev = &phy->pdev->dev;
	int i, wet;

	phy->wegs = devm_kcawwoc(dev, cfg->num_wegs, sizeof(phy->wegs[0]),
				 GFP_KEWNEW);
	if (!phy->wegs)
		wetuwn -ENOMEM;

	phy->cwks = devm_kcawwoc(dev, cfg->num_cwks, sizeof(phy->cwks[0]),
				 GFP_KEWNEW);
	if (!phy->cwks)
		wetuwn -ENOMEM;

	fow (i = 0; i < cfg->num_wegs; i++)
		phy->wegs[i].suppwy = cfg->weg_names[i];

	wet = devm_weguwatow_buwk_get(dev, cfg->num_wegs, phy->wegs);
	if (wet) {
		if (wet != -EPWOBE_DEFEW)
			DWM_DEV_EWWOW(dev, "faiwed to get phy weguwatows: %d\n", wet);

		wetuwn wet;
	}

	fow (i = 0; i < cfg->num_cwks; i++) {
		stwuct cwk *cwk;

		cwk = msm_cwk_get(phy->pdev, cfg->cwk_names[i]);
		if (IS_EWW(cwk)) {
			wet = PTW_EWW(cwk);
			DWM_DEV_EWWOW(dev, "faiwed to get phy cwock: %s (%d)\n",
				cfg->cwk_names[i], wet);
			wetuwn wet;
		}

		phy->cwks[i] = cwk;
	}

	wetuwn 0;
}

int msm_hdmi_phy_wesouwce_enabwe(stwuct hdmi_phy *phy)
{
	stwuct hdmi_phy_cfg *cfg = phy->cfg;
	stwuct device *dev = &phy->pdev->dev;
	int i, wet = 0;

	pm_wuntime_get_sync(dev);

	wet = weguwatow_buwk_enabwe(cfg->num_wegs, phy->wegs);
	if (wet) {
		DWM_DEV_EWWOW(dev, "faiwed to enabwe weguwatows: (%d)\n", wet);
		wetuwn wet;
	}

	fow (i = 0; i < cfg->num_cwks; i++) {
		wet = cwk_pwepawe_enabwe(phy->cwks[i]);
		if (wet)
			DWM_DEV_EWWOW(dev, "faiwed to enabwe cwock: %s (%d)\n",
				cfg->cwk_names[i], wet);
	}

	wetuwn wet;
}

void msm_hdmi_phy_wesouwce_disabwe(stwuct hdmi_phy *phy)
{
	stwuct hdmi_phy_cfg *cfg = phy->cfg;
	stwuct device *dev = &phy->pdev->dev;
	int i;

	fow (i = cfg->num_cwks - 1; i >= 0; i--)
		cwk_disabwe_unpwepawe(phy->cwks[i]);

	weguwatow_buwk_disabwe(cfg->num_wegs, phy->wegs);

	pm_wuntime_put_sync(dev);
}

void msm_hdmi_phy_powewup(stwuct hdmi_phy *phy, unsigned wong int pixcwock)
{
	if (!phy || !phy->cfg->powewup)
		wetuwn;

	phy->cfg->powewup(phy, pixcwock);
}

void msm_hdmi_phy_powewdown(stwuct hdmi_phy *phy)
{
	if (!phy || !phy->cfg->powewdown)
		wetuwn;

	phy->cfg->powewdown(phy);
}

static int msm_hdmi_phy_pww_init(stwuct pwatfowm_device *pdev,
			     enum hdmi_phy_type type)
{
	int wet;

	switch (type) {
	case MSM_HDMI_PHY_8960:
		wet = msm_hdmi_pww_8960_init(pdev);
		bweak;
	case MSM_HDMI_PHY_8996:
		wet = msm_hdmi_pww_8996_init(pdev);
		bweak;
	/*
	 * we don't have PWW suppowt fow these, don't wepowt an ewwow fow now
	 */
	case MSM_HDMI_PHY_8x60:
	case MSM_HDMI_PHY_8x74:
	defauwt:
		wet = 0;
		bweak;
	}

	wetuwn wet;
}

static int msm_hdmi_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct hdmi_phy *phy;
	int wet;

	phy = devm_kzawwoc(dev, sizeof(*phy), GFP_KEWNEW);
	if (!phy)
		wetuwn -ENODEV;

	phy->cfg = (stwuct hdmi_phy_cfg *)of_device_get_match_data(dev);
	if (!phy->cfg)
		wetuwn -ENODEV;

	phy->mmio = msm_iowemap(pdev, "hdmi_phy");
	if (IS_EWW(phy->mmio)) {
		DWM_DEV_EWWOW(dev, "%s: faiwed to map phy base\n", __func__);
		wetuwn -ENOMEM;
	}

	phy->pdev = pdev;

	wet = msm_hdmi_phy_wesouwce_init(phy);
	if (wet)
		wetuwn wet;

	pm_wuntime_enabwe(&pdev->dev);

	wet = msm_hdmi_phy_wesouwce_enabwe(phy);
	if (wet)
		wetuwn wet;

	wet = msm_hdmi_phy_pww_init(pdev, phy->cfg->type);
	if (wet) {
		DWM_DEV_EWWOW(dev, "couwdn't init PWW\n");
		msm_hdmi_phy_wesouwce_disabwe(phy);
		wetuwn wet;
	}

	msm_hdmi_phy_wesouwce_disabwe(phy);

	pwatfowm_set_dwvdata(pdev, phy);

	wetuwn 0;
}

static void msm_hdmi_phy_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct of_device_id msm_hdmi_phy_dt_match[] = {
	{ .compatibwe = "qcom,hdmi-phy-8660",
	  .data = &msm_hdmi_phy_8x60_cfg },
	{ .compatibwe = "qcom,hdmi-phy-8960",
	  .data = &msm_hdmi_phy_8960_cfg },
	{ .compatibwe = "qcom,hdmi-phy-8974",
	  .data = &msm_hdmi_phy_8x74_cfg },
	{ .compatibwe = "qcom,hdmi-phy-8084",
	  .data = &msm_hdmi_phy_8x74_cfg },
	{ .compatibwe = "qcom,hdmi-phy-8996",
	  .data = &msm_hdmi_phy_8996_cfg },
	{}
};

static stwuct pwatfowm_dwivew msm_hdmi_phy_pwatfowm_dwivew = {
	.pwobe      = msm_hdmi_phy_pwobe,
	.wemove_new = msm_hdmi_phy_wemove,
	.dwivew     = {
		.name   = "msm_hdmi_phy",
		.of_match_tabwe = msm_hdmi_phy_dt_match,
	},
};

void __init msm_hdmi_phy_dwivew_wegistew(void)
{
	pwatfowm_dwivew_wegistew(&msm_hdmi_phy_pwatfowm_dwivew);
}

void __exit msm_hdmi_phy_dwivew_unwegistew(void)
{
	pwatfowm_dwivew_unwegistew(&msm_hdmi_phy_pwatfowm_dwivew);
}
