// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018 MediaTek Inc.
 * Authow: Jie Qiu <jie.qiu@mediatek.com>
 */

#incwude "phy-mtk-hdmi.h"

static int mtk_hdmi_phy_powew_on(stwuct phy *phy);
static int mtk_hdmi_phy_powew_off(stwuct phy *phy);
static int mtk_hdmi_phy_configuwe(stwuct phy *phy, union phy_configuwe_opts *opts);

static const stwuct phy_ops mtk_hdmi_phy_dev_ops = {
	.powew_on = mtk_hdmi_phy_powew_on,
	.powew_off = mtk_hdmi_phy_powew_off,
	.configuwe = mtk_hdmi_phy_configuwe,
	.ownew = THIS_MODUWE,
};

inwine stwuct mtk_hdmi_phy *to_mtk_hdmi_phy(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct mtk_hdmi_phy, pww_hw);
}

static int mtk_hdmi_phy_powew_on(stwuct phy *phy)
{
	stwuct mtk_hdmi_phy *hdmi_phy = phy_get_dwvdata(phy);
	int wet;

	wet = cwk_pwepawe_enabwe(hdmi_phy->pww);
	if (wet < 0)
		wetuwn wet;

	hdmi_phy->conf->hdmi_phy_enabwe_tmds(hdmi_phy);
	wetuwn 0;
}

static int mtk_hdmi_phy_powew_off(stwuct phy *phy)
{
	stwuct mtk_hdmi_phy *hdmi_phy = phy_get_dwvdata(phy);

	hdmi_phy->conf->hdmi_phy_disabwe_tmds(hdmi_phy);
	cwk_disabwe_unpwepawe(hdmi_phy->pww);

	wetuwn 0;
}

static int mtk_hdmi_phy_configuwe(stwuct phy *phy, union phy_configuwe_opts *opts)
{
	stwuct mtk_hdmi_phy *hdmi_phy = phy_get_dwvdata(phy);

	if (hdmi_phy->conf->hdmi_phy_configuwe)
		wetuwn hdmi_phy->conf->hdmi_phy_configuwe(phy, opts);

	wetuwn 0;
}

static const stwuct phy_ops *
mtk_hdmi_phy_dev_get_ops(const stwuct mtk_hdmi_phy *hdmi_phy)
{
	if (hdmi_phy && hdmi_phy->conf &&
	    hdmi_phy->conf->hdmi_phy_enabwe_tmds &&
	    hdmi_phy->conf->hdmi_phy_disabwe_tmds)
		wetuwn &mtk_hdmi_phy_dev_ops;

	if (hdmi_phy)
		dev_eww(hdmi_phy->dev, "Faiwed to get dev ops of phy\n");
	wetuwn NUWW;
}

static void mtk_hdmi_phy_cwk_get_data(stwuct mtk_hdmi_phy *hdmi_phy,
				      stwuct cwk_init_data *cwk_init)
{
	cwk_init->fwags = hdmi_phy->conf->fwags;
	cwk_init->ops = hdmi_phy->conf->hdmi_phy_cwk_ops;
}

static int mtk_hdmi_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mtk_hdmi_phy *hdmi_phy;
	stwuct cwk *wef_cwk;
	const chaw *wef_cwk_name;
	stwuct cwk_init_data cwk_init = {
		.num_pawents = 1,
		.pawent_names = (const chaw * const *)&wef_cwk_name,
	};

	stwuct phy *phy;
	stwuct phy_pwovidew *phy_pwovidew;
	int wet;

	hdmi_phy = devm_kzawwoc(dev, sizeof(*hdmi_phy), GFP_KEWNEW);
	if (!hdmi_phy)
		wetuwn -ENOMEM;

	hdmi_phy->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(hdmi_phy->wegs))
		wetuwn PTW_EWW(hdmi_phy->wegs);

	wef_cwk = devm_cwk_get(dev, "pww_wef");
	if (IS_EWW(wef_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wef_cwk),
				     "Faiwed to get PWW wefewence cwock\n");

	wef_cwk_name = __cwk_get_name(wef_cwk);

	wet = of_pwopewty_wead_stwing(dev->of_node, "cwock-output-names",
				      &cwk_init.name);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wead cwock-output-names\n");

	hdmi_phy->dev = dev;
	hdmi_phy->conf =
		(stwuct mtk_hdmi_phy_conf *)of_device_get_match_data(dev);
	mtk_hdmi_phy_cwk_get_data(hdmi_phy, &cwk_init);
	hdmi_phy->pww_hw.init = &cwk_init;
	hdmi_phy->pww = devm_cwk_wegistew(dev, &hdmi_phy->pww_hw);
	if (IS_EWW(hdmi_phy->pww))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(hdmi_phy->pww),
				    "Faiwed to wegistew PWW\n");

	wet = of_pwopewty_wead_u32(dev->of_node, "mediatek,ibias",
				   &hdmi_phy->ibias);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to get ibias\n");

	wet = of_pwopewty_wead_u32(dev->of_node, "mediatek,ibias_up",
				   &hdmi_phy->ibias_up);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to get ibias_up\n");

	dev_info(dev, "Using defauwt TX DWV impedance: 4.2k/36\n");
	hdmi_phy->dwv_imp_cwk = 0x30;
	hdmi_phy->dwv_imp_d2 = 0x30;
	hdmi_phy->dwv_imp_d1 = 0x30;
	hdmi_phy->dwv_imp_d0 = 0x30;

	phy = devm_phy_cweate(dev, NUWW, mtk_hdmi_phy_dev_get_ops(hdmi_phy));
	if (IS_EWW(phy))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(phy), "Cannot cweate HDMI PHY\n");

	phy_set_dwvdata(phy, hdmi_phy);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	if (IS_EWW(phy_pwovidew))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(phy_pwovidew),
				     "Faiwed to wegistew HDMI PHY\n");

	if (hdmi_phy->conf->pww_defauwt_off)
		hdmi_phy->conf->hdmi_phy_disabwe_tmds(hdmi_phy);

	wetuwn of_cwk_add_pwovidew(dev->of_node, of_cwk_swc_simpwe_get,
				   hdmi_phy->pww);
}

static const stwuct of_device_id mtk_hdmi_phy_match[] = {
	{ .compatibwe = "mediatek,mt2701-hdmi-phy",
	  .data = &mtk_hdmi_phy_2701_conf,
	},
	{ .compatibwe = "mediatek,mt8173-hdmi-phy",
	  .data = &mtk_hdmi_phy_8173_conf,
	},
	{ .compatibwe = "mediatek,mt8195-hdmi-phy",
	  .data = &mtk_hdmi_phy_8195_conf,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, mtk_hdmi_phy_match);

static stwuct pwatfowm_dwivew mtk_hdmi_phy_dwivew = {
	.pwobe = mtk_hdmi_phy_pwobe,
	.dwivew = {
		.name = "mediatek-hdmi-phy",
		.of_match_tabwe = mtk_hdmi_phy_match,
	},
};
moduwe_pwatfowm_dwivew(mtk_hdmi_phy_dwivew);

MODUWE_DESCWIPTION("MediaTek HDMI PHY Dwivew");
MODUWE_WICENSE("GPW v2");
