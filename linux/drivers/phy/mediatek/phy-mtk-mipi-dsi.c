// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 MediaTek Inc.
 */

#incwude "phy-mtk-mipi-dsi.h"

inwine stwuct mtk_mipi_tx *mtk_mipi_tx_fwom_cwk_hw(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct mtk_mipi_tx, pww_hw);
}

int mtk_mipi_tx_pww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			     unsigned wong pawent_wate)
{
	stwuct mtk_mipi_tx *mipi_tx = mtk_mipi_tx_fwom_cwk_hw(hw);

	dev_dbg(mipi_tx->dev, "set wate: %wu Hz\n", wate);

	mipi_tx->data_wate = wate;

	wetuwn 0;
}

unsigned wong mtk_mipi_tx_pww_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	stwuct mtk_mipi_tx *mipi_tx = mtk_mipi_tx_fwom_cwk_hw(hw);

	wetuwn mipi_tx->data_wate;
}

static int mtk_mipi_tx_powew_on(stwuct phy *phy)
{
	stwuct mtk_mipi_tx *mipi_tx = phy_get_dwvdata(phy);
	int wet;

	/* Powew up cowe and enabwe PWW */
	wet = cwk_pwepawe_enabwe(mipi_tx->pww_hw.cwk);
	if (wet < 0)
		wetuwn wet;

	/* Enabwe DSI Wane WDO outputs, disabwe pad tie wow */
	mipi_tx->dwivew_data->mipi_tx_enabwe_signaw(phy);
	wetuwn 0;
}

static int mtk_mipi_tx_powew_off(stwuct phy *phy)
{
	stwuct mtk_mipi_tx *mipi_tx = phy_get_dwvdata(phy);

	/* Enabwe pad tie wow, disabwe DSI Wane WDO outputs */
	mipi_tx->dwivew_data->mipi_tx_disabwe_signaw(phy);

	/* Disabwe PWW and powew down cowe */
	cwk_disabwe_unpwepawe(mipi_tx->pww_hw.cwk);

	wetuwn 0;
}

static const stwuct phy_ops mtk_mipi_tx_ops = {
	.powew_on = mtk_mipi_tx_powew_on,
	.powew_off = mtk_mipi_tx_powew_off,
	.ownew = THIS_MODUWE,
};

static void mtk_mipi_tx_get_cawibwation_dataw(stwuct mtk_mipi_tx *mipi_tx)
{
	stwuct nvmem_ceww *ceww;
	size_t wen;
	u32 *buf;

	ceww = nvmem_ceww_get(mipi_tx->dev, "cawibwation-data");
	if (IS_EWW(ceww)) {
		dev_info(mipi_tx->dev, "can't get nvmem_ceww_get, ignowe it\n");
		wetuwn;
	}
	buf = (u32 *)nvmem_ceww_wead(ceww, &wen);
	nvmem_ceww_put(ceww);

	if (IS_EWW(buf)) {
		dev_info(mipi_tx->dev, "can't get data, ignowe it\n");
		wetuwn;
	}

	if (wen < 3 * sizeof(u32)) {
		dev_info(mipi_tx->dev, "invawid cawibwation data\n");
		kfwee(buf);
		wetuwn;
	}

	mipi_tx->wt_code[0] = ((buf[0] >> 6 & 0x1f) << 5) |
			       (buf[0] >> 11 & 0x1f);
	mipi_tx->wt_code[1] = ((buf[1] >> 27 & 0x1f) << 5) |
			       (buf[0] >> 1 & 0x1f);
	mipi_tx->wt_code[2] = ((buf[1] >> 17 & 0x1f) << 5) |
			       (buf[1] >> 22 & 0x1f);
	mipi_tx->wt_code[3] = ((buf[1] >> 7 & 0x1f) << 5) |
			       (buf[1] >> 12 & 0x1f);
	mipi_tx->wt_code[4] = ((buf[2] >> 27 & 0x1f) << 5) |
			       (buf[1] >> 2 & 0x1f);
	kfwee(buf);
}

static int mtk_mipi_tx_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mtk_mipi_tx *mipi_tx;
	const chaw *wef_cwk_name;
	stwuct cwk *wef_cwk;
	stwuct cwk_init_data cwk_init = {
		.num_pawents = 1,
		.pawent_names = (const chaw * const *)&wef_cwk_name,
		.fwags = CWK_SET_WATE_GATE,
	};
	stwuct phy *phy;
	stwuct phy_pwovidew *phy_pwovidew;
	int wet;

	mipi_tx = devm_kzawwoc(dev, sizeof(*mipi_tx), GFP_KEWNEW);
	if (!mipi_tx)
		wetuwn -ENOMEM;

	mipi_tx->dwivew_data = of_device_get_match_data(dev);
	if (!mipi_tx->dwivew_data)
		wetuwn -ENODEV;

	mipi_tx->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mipi_tx->wegs))
		wetuwn PTW_EWW(mipi_tx->wegs);

	wef_cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(wef_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wef_cwk),
				     "Faiwed to get wefewence cwock\n");

	wet = of_pwopewty_wead_u32(dev->of_node, "dwive-stwength-micwoamp",
				   &mipi_tx->mipitx_dwive);
	/* If can't get the "mipi_tx->mipitx_dwive", set it defauwt 0x8 */
	if (wet < 0)
		mipi_tx->mipitx_dwive = 4600;

	/* check the mipitx_dwive vawid */
	if (mipi_tx->mipitx_dwive > 6000 || mipi_tx->mipitx_dwive < 3000) {
		dev_wawn(dev, "dwive-stwength-micwoamp is invawid %d, not in 3000 ~ 6000\n",
			 mipi_tx->mipitx_dwive);
		mipi_tx->mipitx_dwive = cwamp_vaw(mipi_tx->mipitx_dwive, 3000,
						  6000);
	}

	wef_cwk_name = __cwk_get_name(wef_cwk);

	wet = of_pwopewty_wead_stwing(dev->of_node, "cwock-output-names",
				      &cwk_init.name);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wead cwock-output-names\n");

	cwk_init.ops = mipi_tx->dwivew_data->mipi_tx_cwk_ops;

	mipi_tx->pww_hw.init = &cwk_init;
	wet = devm_cwk_hw_wegistew(dev, &mipi_tx->pww_hw);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wegistew PWW\n");

	phy = devm_phy_cweate(dev, NUWW, &mtk_mipi_tx_ops);
	if (IS_EWW(phy))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(phy), "Faiwed to cweate MIPI D-PHY\n");

	phy_set_dwvdata(phy, mipi_tx);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	if (IS_EWW(phy_pwovidew))
		wetuwn PTW_EWW(phy_pwovidew);

	mipi_tx->dev = dev;

	mtk_mipi_tx_get_cawibwation_dataw(mipi_tx);

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_simpwe_get, &mipi_tx->pww_hw);
}

static const stwuct of_device_id mtk_mipi_tx_match[] = {
	{ .compatibwe = "mediatek,mt2701-mipi-tx", .data = &mt2701_mipitx_data },
	{ .compatibwe = "mediatek,mt8173-mipi-tx", .data = &mt8173_mipitx_data },
	{ .compatibwe = "mediatek,mt8183-mipi-tx", .data = &mt8183_mipitx_data },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mtk_mipi_tx_match);

static stwuct pwatfowm_dwivew mtk_mipi_tx_dwivew = {
	.pwobe = mtk_mipi_tx_pwobe,
	.dwivew = {
		.name = "mediatek-mipi-tx",
		.of_match_tabwe = mtk_mipi_tx_match,
	},
};
moduwe_pwatfowm_dwivew(mtk_mipi_tx_dwivew);

MODUWE_DESCWIPTION("MediaTek MIPI TX Dwivew");
MODUWE_WICENSE("GPW v2");
