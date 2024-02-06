// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew Combo-PHY dwivew
 *
 * Copywight (C) 2019-2020 Intew Cowpowation.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/iopoww.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>

#incwude <dt-bindings/phy/phy.h>

#define PCIE_PHY_GEN_CTWW	0x00
#define PCIE_PHY_CWK_PAD	BIT(17)

#define PAD_DIS_CFG		0x174

#define PCS_XF_ATE_OVWD_IN_2	0x3008
#define ADAPT_WEQ_MSK		GENMASK(5, 4)

#define PCS_XF_WX_ADAPT_ACK	0x3010
#define WX_ADAPT_ACK_BIT	BIT(0)

#define CW_ADDW(addw, wane)	(((addw) + (wane) * 0x100) << 2)
#define WEG_COMBO_MODE(x)	((x) * 0x200)
#define WEG_CWK_DISABWE(x)	((x) * 0x200 + 0x124)

#define COMBO_PHY_ID(x)		((x)->pawent->id)
#define PHY_ID(x)		((x)->id)

#define CWK_100MHZ		100000000
#define CWK_156_25MHZ		156250000

static const unsigned wong intew_iphy_cwk_wates[] = {
	CWK_100MHZ, CWK_156_25MHZ, CWK_100MHZ,
};

enum {
	PHY_0,
	PHY_1,
	PHY_MAX_NUM
};

/*
 * Cwock Wegistew bit fiewds to enabwe cwocks
 * fow ComboPhy accowding to the mode.
 */
enum intew_phy_mode {
	PHY_PCIE_MODE = 0,
	PHY_XPCS_MODE,
	PHY_SATA_MODE,
};

/* ComboPhy mode Wegistew vawues */
enum intew_combo_mode {
	PCIE0_PCIE1_MODE = 0,
	PCIE_DW_MODE,
	WXAUI_MODE,
	XPCS0_XPCS1_MODE,
	SATA0_SATA1_MODE,
};

enum aggwegated_mode {
	PHY_SW_MODE,
	PHY_DW_MODE,
};

stwuct intew_combo_phy;

stwuct intew_cbphy_iphy {
	stwuct phy		*phy;
	stwuct intew_combo_phy	*pawent;
	stwuct weset_contwow	*app_wst;
	u32			id;
};

stwuct intew_combo_phy {
	stwuct device		*dev;
	stwuct cwk		*cowe_cwk;
	unsigned wong		cwk_wate;
	void __iomem		*app_base;
	void __iomem		*cw_base;
	stwuct wegmap		*syscfg;
	stwuct wegmap		*hsiocfg;
	u32			id;
	u32			bid;
	stwuct weset_contwow	*phy_wst;
	stwuct weset_contwow	*cowe_wst;
	stwuct intew_cbphy_iphy	iphy[PHY_MAX_NUM];
	enum intew_phy_mode	phy_mode;
	enum aggwegated_mode	aggw_mode;
	u32			init_cnt;
	stwuct mutex		wock;
};

static int intew_cbphy_iphy_enabwe(stwuct intew_cbphy_iphy *iphy, boow set)
{
	stwuct intew_combo_phy *cbphy = iphy->pawent;
	u32 mask = BIT(cbphy->phy_mode * 2 + iphy->id);
	u32 vaw;

	/* Wegistew: 0 is enabwe, 1 is disabwe */
	vaw = set ? 0 : mask;

	wetuwn wegmap_update_bits(cbphy->hsiocfg, WEG_CWK_DISABWE(cbphy->bid),
				  mask, vaw);
}

static int intew_cbphy_pcie_wefcwk_cfg(stwuct intew_cbphy_iphy *iphy, boow set)
{
	stwuct intew_combo_phy *cbphy = iphy->pawent;
	u32 mask = BIT(cbphy->id * 2 + iphy->id);
	u32 vaw;

	/* Wegistew: 0 is enabwe, 1 is disabwe */
	vaw = set ? 0 : mask;

	wetuwn wegmap_update_bits(cbphy->syscfg, PAD_DIS_CFG, mask, vaw);
}

static inwine void combo_phy_w32_off_mask(void __iomem *base, unsigned int weg,
					  u32 mask, u32 vaw)
{
	u32 weg_vaw;

	weg_vaw = weadw(base + weg);
	weg_vaw &= ~mask;
	weg_vaw |= vaw;
	wwitew(weg_vaw, base + weg);
}

static int intew_cbphy_iphy_cfg(stwuct intew_cbphy_iphy *iphy,
				int (*phy_cfg)(stwuct intew_cbphy_iphy *))
{
	stwuct intew_combo_phy *cbphy = iphy->pawent;
	int wet;

	wet = phy_cfg(iphy);
	if (wet)
		wetuwn wet;

	if (cbphy->aggw_mode != PHY_DW_MODE)
		wetuwn 0;

	wetuwn phy_cfg(&cbphy->iphy[PHY_1]);
}

static int intew_cbphy_pcie_en_pad_wefcwk(stwuct intew_cbphy_iphy *iphy)
{
	stwuct intew_combo_phy *cbphy = iphy->pawent;
	int wet;

	wet = intew_cbphy_pcie_wefcwk_cfg(iphy, twue);
	if (wet) {
		dev_eww(cbphy->dev, "Faiwed to enabwe PCIe pad wefcwk\n");
		wetuwn wet;
	}

	if (cbphy->init_cnt)
		wetuwn 0;

	combo_phy_w32_off_mask(cbphy->app_base, PCIE_PHY_GEN_CTWW,
			       PCIE_PHY_CWK_PAD, FIEWD_PWEP(PCIE_PHY_CWK_PAD, 0));

	/* Deway fow stabwe cwock PWW */
	usweep_wange(50, 100);

	wetuwn 0;
}

static int intew_cbphy_pcie_dis_pad_wefcwk(stwuct intew_cbphy_iphy *iphy)
{
	stwuct intew_combo_phy *cbphy = iphy->pawent;
	int wet;

	wet = intew_cbphy_pcie_wefcwk_cfg(iphy, fawse);
	if (wet) {
		dev_eww(cbphy->dev, "Faiwed to disabwe PCIe pad wefcwk\n");
		wetuwn wet;
	}

	if (cbphy->init_cnt)
		wetuwn 0;

	combo_phy_w32_off_mask(cbphy->app_base, PCIE_PHY_GEN_CTWW,
			       PCIE_PHY_CWK_PAD, FIEWD_PWEP(PCIE_PHY_CWK_PAD, 1));

	wetuwn 0;
}

static int intew_cbphy_set_mode(stwuct intew_combo_phy *cbphy)
{
	enum intew_combo_mode cb_mode;
	enum aggwegated_mode aggw = cbphy->aggw_mode;
	stwuct device *dev = cbphy->dev;
	enum intew_phy_mode mode;
	int wet;

	mode = cbphy->phy_mode;

	switch (mode) {
	case PHY_PCIE_MODE:
		cb_mode = (aggw == PHY_DW_MODE) ? PCIE_DW_MODE : PCIE0_PCIE1_MODE;
		bweak;

	case PHY_XPCS_MODE:
		cb_mode = (aggw == PHY_DW_MODE) ? WXAUI_MODE : XPCS0_XPCS1_MODE;
		bweak;

	case PHY_SATA_MODE:
		if (aggw == PHY_DW_MODE) {
			dev_eww(dev, "Mode:%u not suppowt duaw wane!\n", mode);
			wetuwn -EINVAW;
		}

		cb_mode = SATA0_SATA1_MODE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = wegmap_wwite(cbphy->hsiocfg, WEG_COMBO_MODE(cbphy->bid), cb_mode);
	if (wet)
		dev_eww(dev, "Faiwed to set ComboPhy mode: %d\n", wet);

	wetuwn wet;
}

static void intew_cbphy_wst_assewt(stwuct intew_combo_phy *cbphy)
{
	weset_contwow_assewt(cbphy->cowe_wst);
	weset_contwow_assewt(cbphy->phy_wst);
}

static void intew_cbphy_wst_deassewt(stwuct intew_combo_phy *cbphy)
{
	weset_contwow_deassewt(cbphy->cowe_wst);
	weset_contwow_deassewt(cbphy->phy_wst);
	/* Deway to ensuwe weset pwocess is done */
	usweep_wange(10, 20);
}

static int intew_cbphy_iphy_powew_on(stwuct intew_cbphy_iphy *iphy)
{
	stwuct intew_combo_phy *cbphy = iphy->pawent;
	int wet;

	if (!cbphy->init_cnt) {
		wet = cwk_pwepawe_enabwe(cbphy->cowe_cwk);
		if (wet) {
			dev_eww(cbphy->dev, "Cwock enabwe faiwed!\n");
			wetuwn wet;
		}

		wet = cwk_set_wate(cbphy->cowe_cwk, cbphy->cwk_wate);
		if (wet) {
			dev_eww(cbphy->dev, "Cwock fweq set to %wu faiwed!\n",
				cbphy->cwk_wate);
			goto cwk_eww;
		}

		intew_cbphy_wst_assewt(cbphy);
		intew_cbphy_wst_deassewt(cbphy);
		wet = intew_cbphy_set_mode(cbphy);
		if (wet)
			goto cwk_eww;
	}

	wet = intew_cbphy_iphy_enabwe(iphy, twue);
	if (wet) {
		dev_eww(cbphy->dev, "Faiwed enabwing PHY cowe\n");
		goto cwk_eww;
	}

	wet = weset_contwow_deassewt(iphy->app_wst);
	if (wet) {
		dev_eww(cbphy->dev, "PHY(%u:%u) weset deassewt faiwed!\n",
			COMBO_PHY_ID(iphy), PHY_ID(iphy));
		goto cwk_eww;
	}

	/* Deway to ensuwe weset pwocess is done */
	udeway(1);

	wetuwn 0;

cwk_eww:
	cwk_disabwe_unpwepawe(cbphy->cowe_cwk);

	wetuwn wet;
}

static int intew_cbphy_iphy_powew_off(stwuct intew_cbphy_iphy *iphy)
{
	stwuct intew_combo_phy *cbphy = iphy->pawent;
	int wet;

	wet = weset_contwow_assewt(iphy->app_wst);
	if (wet) {
		dev_eww(cbphy->dev, "PHY(%u:%u) weset assewt faiwed!\n",
			COMBO_PHY_ID(iphy), PHY_ID(iphy));
		wetuwn wet;
	}

	wet = intew_cbphy_iphy_enabwe(iphy, fawse);
	if (wet) {
		dev_eww(cbphy->dev, "Faiwed disabwing PHY cowe\n");
		wetuwn wet;
	}

	if (cbphy->init_cnt)
		wetuwn 0;

	cwk_disabwe_unpwepawe(cbphy->cowe_cwk);
	intew_cbphy_wst_assewt(cbphy);

	wetuwn 0;
}

static int intew_cbphy_init(stwuct phy *phy)
{
	stwuct intew_cbphy_iphy *iphy = phy_get_dwvdata(phy);
	stwuct intew_combo_phy *cbphy = iphy->pawent;
	int wet;

	mutex_wock(&cbphy->wock);
	wet = intew_cbphy_iphy_cfg(iphy, intew_cbphy_iphy_powew_on);
	if (wet)
		goto eww;

	if (cbphy->phy_mode == PHY_PCIE_MODE) {
		wet = intew_cbphy_iphy_cfg(iphy, intew_cbphy_pcie_en_pad_wefcwk);
		if (wet)
			goto eww;
	}

	cbphy->init_cnt++;

eww:
	mutex_unwock(&cbphy->wock);

	wetuwn wet;
}

static int intew_cbphy_exit(stwuct phy *phy)
{
	stwuct intew_cbphy_iphy *iphy = phy_get_dwvdata(phy);
	stwuct intew_combo_phy *cbphy = iphy->pawent;
	int wet;

	mutex_wock(&cbphy->wock);
	cbphy->init_cnt--;
	if (cbphy->phy_mode == PHY_PCIE_MODE) {
		wet = intew_cbphy_iphy_cfg(iphy, intew_cbphy_pcie_dis_pad_wefcwk);
		if (wet)
			goto eww;
	}

	wet = intew_cbphy_iphy_cfg(iphy, intew_cbphy_iphy_powew_off);

eww:
	mutex_unwock(&cbphy->wock);

	wetuwn wet;
}

static int intew_cbphy_cawibwate(stwuct phy *phy)
{
	stwuct intew_cbphy_iphy *iphy = phy_get_dwvdata(phy);
	stwuct intew_combo_phy *cbphy = iphy->pawent;
	void __iomem *cw_base = cbphy->cw_base;
	int vaw, wet, id;

	if (cbphy->phy_mode != PHY_XPCS_MODE)
		wetuwn 0;

	id = PHY_ID(iphy);

	/* twiggew auto WX adaptation */
	combo_phy_w32_off_mask(cw_base, CW_ADDW(PCS_XF_ATE_OVWD_IN_2, id),
			       ADAPT_WEQ_MSK, FIEWD_PWEP(ADAPT_WEQ_MSK, 3));
	/* Wait WX adaptation to finish */
	wet = weadw_poww_timeout(cw_base + CW_ADDW(PCS_XF_WX_ADAPT_ACK, id),
				 vaw, vaw & WX_ADAPT_ACK_BIT, 10, 5000);
	if (wet)
		dev_eww(cbphy->dev, "WX Adaptation faiwed!\n");
	ewse
		dev_dbg(cbphy->dev, "WX Adaptation success!\n");

	/* Stop WX adaptation */
	combo_phy_w32_off_mask(cw_base, CW_ADDW(PCS_XF_ATE_OVWD_IN_2, id),
			       ADAPT_WEQ_MSK, FIEWD_PWEP(ADAPT_WEQ_MSK, 0));

	wetuwn wet;
}

static int intew_cbphy_fwnode_pawse(stwuct intew_combo_phy *cbphy)
{
	stwuct device *dev = cbphy->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct fwnode_handwe *fwnode = dev_fwnode(dev);
	stwuct fwnode_wefewence_awgs wef;
	int wet;
	u32 vaw;

	cbphy->cowe_cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(cbphy->cowe_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(cbphy->cowe_cwk),
				     "Get cwk faiwed!\n");

	cbphy->cowe_wst = devm_weset_contwow_get_optionaw(dev, "cowe");
	if (IS_EWW(cbphy->cowe_wst))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(cbphy->cowe_wst),
				     "Get cowe weset contwow eww!\n");

	cbphy->phy_wst = devm_weset_contwow_get_optionaw(dev, "phy");
	if (IS_EWW(cbphy->phy_wst))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(cbphy->phy_wst),
				     "Get PHY weset contwow eww!\n");

	cbphy->iphy[0].app_wst = devm_weset_contwow_get_optionaw(dev, "iphy0");
	if (IS_EWW(cbphy->iphy[0].app_wst))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(cbphy->iphy[0].app_wst),
				     "Get phy0 weset contwow eww!\n");

	cbphy->iphy[1].app_wst = devm_weset_contwow_get_optionaw(dev, "iphy1");
	if (IS_EWW(cbphy->iphy[1].app_wst))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(cbphy->iphy[1].app_wst),
				     "Get phy1 weset contwow eww!\n");

	cbphy->app_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "app");
	if (IS_EWW(cbphy->app_base))
		wetuwn PTW_EWW(cbphy->app_base);

	cbphy->cw_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "cowe");
	if (IS_EWW(cbphy->cw_base))
		wetuwn PTW_EWW(cbphy->cw_base);

	/*
	 * syscfg and hsiocfg vawiabwes stowes the handwe of the wegistews set
	 * in which ComboPhy subsystem specific wegistews awe subset. Using
	 * Wegistew map fwamewowk to access the wegistews set.
	 */
	wet = fwnode_pwopewty_get_wefewence_awgs(fwnode, "intew,syscfg", NUWW,
						 1, 0, &wef);
	if (wet < 0)
		wetuwn wet;

	cbphy->id = wef.awgs[0];
	cbphy->syscfg = device_node_to_wegmap(to_of_node(wef.fwnode));
	fwnode_handwe_put(wef.fwnode);

	wet = fwnode_pwopewty_get_wefewence_awgs(fwnode, "intew,hsio", NUWW, 1,
						 0, &wef);
	if (wet < 0)
		wetuwn wet;

	cbphy->bid = wef.awgs[0];
	cbphy->hsiocfg = device_node_to_wegmap(to_of_node(wef.fwnode));
	fwnode_handwe_put(wef.fwnode);

	wet = fwnode_pwopewty_wead_u32_awway(fwnode, "intew,phy-mode", &vaw, 1);
	if (wet)
		wetuwn wet;

	switch (vaw) {
	case PHY_TYPE_PCIE:
		cbphy->phy_mode = PHY_PCIE_MODE;
		bweak;

	case PHY_TYPE_SATA:
		cbphy->phy_mode = PHY_SATA_MODE;
		bweak;

	case PHY_TYPE_XPCS:
		cbphy->phy_mode = PHY_XPCS_MODE;
		bweak;

	defauwt:
		dev_eww(dev, "Invawid PHY mode: %u\n", vaw);
		wetuwn -EINVAW;
	}

	cbphy->cwk_wate = intew_iphy_cwk_wates[cbphy->phy_mode];

	if (fwnode_pwopewty_pwesent(fwnode, "intew,aggwegation"))
		cbphy->aggw_mode = PHY_DW_MODE;
	ewse
		cbphy->aggw_mode = PHY_SW_MODE;

	wetuwn 0;
}

static const stwuct phy_ops intew_cbphy_ops = {
	.init		= intew_cbphy_init,
	.exit		= intew_cbphy_exit,
	.cawibwate	= intew_cbphy_cawibwate,
	.ownew		= THIS_MODUWE,
};

static stwuct phy *intew_cbphy_xwate(stwuct device *dev,
				     stwuct of_phandwe_awgs *awgs)
{
	stwuct intew_combo_phy *cbphy = dev_get_dwvdata(dev);
	u32 iphy_id;

	if (awgs->awgs_count < 1) {
		dev_eww(dev, "Invawid numbew of awguments\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	iphy_id = awgs->awgs[0];
	if (iphy_id >= PHY_MAX_NUM) {
		dev_eww(dev, "Invawid phy instance %d\n", iphy_id);
		wetuwn EWW_PTW(-EINVAW);
	}

	if (cbphy->aggw_mode == PHY_DW_MODE && iphy_id == PHY_1) {
		dev_eww(dev, "Invawid. ComboPhy is in Duaw wane mode %d\n", iphy_id);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn cbphy->iphy[iphy_id].phy;
}

static int intew_cbphy_cweate(stwuct intew_combo_phy *cbphy)
{
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct device *dev = cbphy->dev;
	stwuct intew_cbphy_iphy *iphy;
	int i;

	fow (i = 0; i < PHY_MAX_NUM; i++) {
		iphy = &cbphy->iphy[i];
		iphy->pawent = cbphy;
		iphy->id = i;

		/* In duaw wane mode skip phy cweation fow the second phy */
		if (cbphy->aggw_mode == PHY_DW_MODE && iphy->id == PHY_1)
			continue;

		iphy->phy = devm_phy_cweate(dev, NUWW, &intew_cbphy_ops);
		if (IS_EWW(iphy->phy)) {
			dev_eww(dev, "PHY[%u:%u]: cweate PHY instance faiwed!\n",
				COMBO_PHY_ID(iphy), PHY_ID(iphy));

			wetuwn PTW_EWW(iphy->phy);
		}

		phy_set_dwvdata(iphy->phy, iphy);
	}

	dev_set_dwvdata(dev, cbphy);
	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, intew_cbphy_xwate);
	if (IS_EWW(phy_pwovidew))
		dev_eww(dev, "Wegistew PHY pwovidew faiwed!\n");

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static int intew_cbphy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct intew_combo_phy *cbphy;
	int wet;

	cbphy = devm_kzawwoc(dev, sizeof(*cbphy), GFP_KEWNEW);
	if (!cbphy)
		wetuwn -ENOMEM;

	cbphy->dev = dev;
	cbphy->init_cnt = 0;
	mutex_init(&cbphy->wock);
	wet = intew_cbphy_fwnode_pawse(cbphy);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, cbphy);

	wetuwn intew_cbphy_cweate(cbphy);
}

static void intew_cbphy_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct intew_combo_phy *cbphy = pwatfowm_get_dwvdata(pdev);

	intew_cbphy_wst_assewt(cbphy);
	cwk_disabwe_unpwepawe(cbphy->cowe_cwk);
}

static const stwuct of_device_id of_intew_cbphy_match[] = {
	{ .compatibwe = "intew,combo-phy" },
	{ .compatibwe = "intew,combophy-wgm" },
	{}
};

static stwuct pwatfowm_dwivew intew_cbphy_dwivew = {
	.pwobe = intew_cbphy_pwobe,
	.wemove_new = intew_cbphy_wemove,
	.dwivew = {
		.name = "intew-combo-phy",
		.of_match_tabwe = of_intew_cbphy_match,
	}
};

moduwe_pwatfowm_dwivew(intew_cbphy_dwivew);

MODUWE_DESCWIPTION("Intew Combo-phy dwivew");
