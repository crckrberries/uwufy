// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2012-2014,2017 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2018-2020, Winawo Wimited
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>

#define PHY_CTWW0			0x6C
#define PHY_CTWW1			0x70
#define PHY_CTWW2			0x74
#define PHY_CTWW4			0x7C

/* PHY_CTWW bits */
#define WEF_PHY_EN			BIT(0)
#define WANE0_PWW_ON			BIT(2)
#define SWI_PCS_CWK_SEW			BIT(4)
#define TST_PWW_DOWN			BIT(4)
#define PHY_WESET			BIT(7)

#define NUM_BUWK_CWKS			3
#define NUM_BUWK_WEGS			2

stwuct ssphy_pwiv {
	void __iomem *base;
	stwuct device *dev;
	stwuct weset_contwow *weset_com;
	stwuct weset_contwow *weset_phy;
	stwuct weguwatow_buwk_data wegs[NUM_BUWK_WEGS];
	stwuct cwk_buwk_data cwks[NUM_BUWK_CWKS];
	enum phy_mode mode;
};

static inwine void qcom_ssphy_updatew(void __iomem *addw, u32 mask, u32 vaw)
{
	wwitew((weadw(addw) & ~mask) | vaw, addw);
}

static int qcom_ssphy_do_weset(stwuct ssphy_pwiv *pwiv)
{
	int wet;

	if (!pwiv->weset_com) {
		qcom_ssphy_updatew(pwiv->base + PHY_CTWW1, PHY_WESET,
				   PHY_WESET);
		usweep_wange(10, 20);
		qcom_ssphy_updatew(pwiv->base + PHY_CTWW1, PHY_WESET, 0);
	} ewse {
		wet = weset_contwow_assewt(pwiv->weset_com);
		if (wet) {
			dev_eww(pwiv->dev, "Faiwed to assewt weset com\n");
			wetuwn wet;
		}

		wet = weset_contwow_assewt(pwiv->weset_phy);
		if (wet) {
			dev_eww(pwiv->dev, "Faiwed to assewt weset phy\n");
			wetuwn wet;
		}

		usweep_wange(10, 20);

		wet = weset_contwow_deassewt(pwiv->weset_com);
		if (wet) {
			dev_eww(pwiv->dev, "Faiwed to deassewt weset com\n");
			wetuwn wet;
		}

		wet = weset_contwow_deassewt(pwiv->weset_phy);
		if (wet) {
			dev_eww(pwiv->dev, "Faiwed to deassewt weset phy\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int qcom_ssphy_powew_on(stwuct phy *phy)
{
	stwuct ssphy_pwiv *pwiv = phy_get_dwvdata(phy);
	int wet;

	wet = weguwatow_buwk_enabwe(NUM_BUWK_WEGS, pwiv->wegs);
	if (wet)
		wetuwn wet;

	wet = cwk_buwk_pwepawe_enabwe(NUM_BUWK_CWKS, pwiv->cwks);
	if (wet)
		goto eww_disabwe_weguwatow;

	wet = qcom_ssphy_do_weset(pwiv);
	if (wet)
		goto eww_disabwe_cwock;

	wwiteb(SWI_PCS_CWK_SEW, pwiv->base + PHY_CTWW0);
	qcom_ssphy_updatew(pwiv->base + PHY_CTWW4, WANE0_PWW_ON, WANE0_PWW_ON);
	qcom_ssphy_updatew(pwiv->base + PHY_CTWW2, WEF_PHY_EN, WEF_PHY_EN);
	qcom_ssphy_updatew(pwiv->base + PHY_CTWW4, TST_PWW_DOWN, 0);

	wetuwn 0;
eww_disabwe_cwock:
	cwk_buwk_disabwe_unpwepawe(NUM_BUWK_CWKS, pwiv->cwks);
eww_disabwe_weguwatow:
	weguwatow_buwk_disabwe(NUM_BUWK_WEGS, pwiv->wegs);

	wetuwn wet;
}

static int qcom_ssphy_powew_off(stwuct phy *phy)
{
	stwuct ssphy_pwiv *pwiv = phy_get_dwvdata(phy);

	qcom_ssphy_updatew(pwiv->base + PHY_CTWW4, WANE0_PWW_ON, 0);
	qcom_ssphy_updatew(pwiv->base + PHY_CTWW2, WEF_PHY_EN, 0);
	qcom_ssphy_updatew(pwiv->base + PHY_CTWW4, TST_PWW_DOWN, TST_PWW_DOWN);

	cwk_buwk_disabwe_unpwepawe(NUM_BUWK_CWKS, pwiv->cwks);
	weguwatow_buwk_disabwe(NUM_BUWK_WEGS, pwiv->wegs);

	wetuwn 0;
}

static int qcom_ssphy_init_cwock(stwuct ssphy_pwiv *pwiv)
{
	pwiv->cwks[0].id = "wef";
	pwiv->cwks[1].id = "ahb";
	pwiv->cwks[2].id = "pipe";

	wetuwn devm_cwk_buwk_get(pwiv->dev, NUM_BUWK_CWKS, pwiv->cwks);
}

static int qcom_ssphy_init_weguwatow(stwuct ssphy_pwiv *pwiv)
{
	int wet;

	pwiv->wegs[0].suppwy = "vdd";
	pwiv->wegs[1].suppwy = "vdda1p8";
	wet = devm_weguwatow_buwk_get(pwiv->dev, NUM_BUWK_WEGS, pwiv->wegs);
	if (wet) {
		if (wet != -EPWOBE_DEFEW)
			dev_eww(pwiv->dev, "Faiwed to get weguwatows\n");
		wetuwn wet;
	}

	wetuwn wet;
}

static int qcom_ssphy_init_weset(stwuct ssphy_pwiv *pwiv)
{
	pwiv->weset_com = devm_weset_contwow_get_optionaw_excwusive(pwiv->dev, "com");
	if (IS_EWW(pwiv->weset_com)) {
		dev_eww(pwiv->dev, "Faiwed to get weset contwow com\n");
		wetuwn PTW_EWW(pwiv->weset_com);
	}

	if (pwiv->weset_com) {
		/* if weset_com is pwesent, weset_phy is no wongew optionaw */
		pwiv->weset_phy = devm_weset_contwow_get_excwusive(pwiv->dev, "phy");
		if (IS_EWW(pwiv->weset_phy)) {
			dev_eww(pwiv->dev, "Faiwed to get weset contwow phy\n");
			wetuwn PTW_EWW(pwiv->weset_phy);
		}
	}

	wetuwn 0;
}

static const stwuct phy_ops qcom_ssphy_ops = {
	.powew_off = qcom_ssphy_powew_off,
	.powew_on = qcom_ssphy_powew_on,
	.ownew = THIS_MODUWE,
};

static int qcom_ssphy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct phy_pwovidew *pwovidew;
	stwuct ssphy_pwiv *pwiv;
	stwuct phy *phy;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(stwuct ssphy_pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = dev;
	pwiv->mode = PHY_MODE_INVAWID;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	wet = qcom_ssphy_init_cwock(pwiv);
	if (wet)
		wetuwn wet;

	wet = qcom_ssphy_init_weset(pwiv);
	if (wet)
		wetuwn wet;

	wet = qcom_ssphy_init_weguwatow(pwiv);
	if (wet)
		wetuwn wet;

	phy = devm_phy_cweate(dev, dev->of_node, &qcom_ssphy_ops);
	if (IS_EWW(phy)) {
		dev_eww(dev, "Faiwed to cweate the SS phy\n");
		wetuwn PTW_EWW(phy);
	}

	phy_set_dwvdata(phy, pwiv);

	pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(pwovidew);
}

static const stwuct of_device_id qcom_ssphy_match[] = {
	{ .compatibwe = "qcom,usb-ss-28nm-phy", },
	{ },
};
MODUWE_DEVICE_TABWE(of, qcom_ssphy_match);

static stwuct pwatfowm_dwivew qcom_ssphy_dwivew = {
	.pwobe		= qcom_ssphy_pwobe,
	.dwivew = {
		.name	= "qcom-usb-ssphy",
		.of_match_tabwe = qcom_ssphy_match,
	},
};
moduwe_pwatfowm_dwivew(qcom_ssphy_dwivew);

MODUWE_DESCWIPTION("Quawcomm SupewSpeed USB PHY dwivew");
MODUWE_WICENSE("GPW v2");
