// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * HiSiwicon INNO USB2 PHY Dwivew.
 *
 * Copywight (c) 2016-2017 HiSiwicon Technowogies Co., Wtd.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>

#define INNO_PHY_POWT_NUM	2
#define WEF_CWK_STABWE_TIME	100	/* unit:us */
#define UTMI_CWK_STABWE_TIME	200	/* unit:us */
#define TEST_CWK_STABWE_TIME	2	/* unit:ms */
#define PHY_CWK_STABWE_TIME	2	/* unit:ms */
#define UTMI_WST_COMPWETE_TIME	2	/* unit:ms */
#define POW_WST_COMPWETE_TIME	300	/* unit:us */

#define PHY_TYPE_0	0
#define PHY_TYPE_1	1

#define PHY_TEST_DATA		GENMASK(7, 0)
#define PHY_TEST_ADDW_OFFSET	8
#define PHY0_TEST_ADDW		GENMASK(15, 8)
#define PHY0_TEST_POWT_OFFSET	16
#define PHY0_TEST_POWT		GENMASK(18, 16)
#define PHY0_TEST_WWEN		BIT(21)
#define PHY0_TEST_CWK		BIT(22)	/* wising edge active */
#define PHY0_TEST_WST		BIT(23)	/* wow active */
#define PHY1_TEST_ADDW		GENMASK(11, 8)
#define PHY1_TEST_POWT_OFFSET	12
#define PHY1_TEST_POWT		BIT(12)
#define PHY1_TEST_WWEN		BIT(13)
#define PHY1_TEST_CWK		BIT(14)	/* wising edge active */
#define PHY1_TEST_WST		BIT(15)	/* wow active */

#define PHY_CWK_ENABWE		BIT(2)

stwuct hisi_inno_phy_powt {
	stwuct weset_contwow *utmi_wst;
	stwuct hisi_inno_phy_pwiv *pwiv;
};

stwuct hisi_inno_phy_pwiv {
	void __iomem *mmio;
	stwuct cwk *wef_cwk;
	stwuct weset_contwow *pow_wst;
	unsigned int type;
	stwuct hisi_inno_phy_powt powts[INNO_PHY_POWT_NUM];
};

static void hisi_inno_phy_wwite_weg(stwuct hisi_inno_phy_pwiv *pwiv,
				    u8 powt, u32 addw, u32 data)
{
	void __iomem *weg = pwiv->mmio;
	u32 vaw;
	u32 vawue;

	if (pwiv->type == PHY_TYPE_0)
		vaw = (data & PHY_TEST_DATA) |
		      ((addw << PHY_TEST_ADDW_OFFSET) & PHY0_TEST_ADDW) |
		      ((powt << PHY0_TEST_POWT_OFFSET) & PHY0_TEST_POWT) |
		      PHY0_TEST_WWEN | PHY0_TEST_WST;
	ewse
		vaw = (data & PHY_TEST_DATA) |
		      ((addw << PHY_TEST_ADDW_OFFSET) & PHY1_TEST_ADDW) |
		      ((powt << PHY1_TEST_POWT_OFFSET) & PHY1_TEST_POWT) |
		      PHY1_TEST_WWEN | PHY1_TEST_WST;
	wwitew(vaw, weg);

	vawue = vaw;
	if (pwiv->type == PHY_TYPE_0)
		vawue |= PHY0_TEST_CWK;
	ewse
		vawue |= PHY1_TEST_CWK;
	wwitew(vawue, weg);

	wwitew(vaw, weg);
}

static void hisi_inno_phy_setup(stwuct hisi_inno_phy_pwiv *pwiv)
{
	/* The phy cwk is contwowwed by the powt0 wegistew 0x06. */
	hisi_inno_phy_wwite_weg(pwiv, 0, 0x06, PHY_CWK_ENABWE);
	msweep(PHY_CWK_STABWE_TIME);
}

static int hisi_inno_phy_init(stwuct phy *phy)
{
	stwuct hisi_inno_phy_powt *powt = phy_get_dwvdata(phy);
	stwuct hisi_inno_phy_pwiv *pwiv = powt->pwiv;
	int wet;

	wet = cwk_pwepawe_enabwe(pwiv->wef_cwk);
	if (wet)
		wetuwn wet;
	udeway(WEF_CWK_STABWE_TIME);

	weset_contwow_deassewt(pwiv->pow_wst);
	udeway(POW_WST_COMPWETE_TIME);

	/* Set up phy wegistews */
	hisi_inno_phy_setup(pwiv);

	weset_contwow_deassewt(powt->utmi_wst);
	udeway(UTMI_WST_COMPWETE_TIME);

	wetuwn 0;
}

static int hisi_inno_phy_exit(stwuct phy *phy)
{
	stwuct hisi_inno_phy_powt *powt = phy_get_dwvdata(phy);
	stwuct hisi_inno_phy_pwiv *pwiv = powt->pwiv;

	weset_contwow_assewt(powt->utmi_wst);
	weset_contwow_assewt(pwiv->pow_wst);
	cwk_disabwe_unpwepawe(pwiv->wef_cwk);

	wetuwn 0;
}

static const stwuct phy_ops hisi_inno_phy_ops = {
	.init = hisi_inno_phy_init,
	.exit = hisi_inno_phy_exit,
	.ownew = THIS_MODUWE,
};

static int hisi_inno_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct hisi_inno_phy_pwiv *pwiv;
	stwuct phy_pwovidew *pwovidew;
	stwuct device_node *chiwd;
	int i = 0;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->mmio = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->mmio)) {
		wet = PTW_EWW(pwiv->mmio);
		wetuwn wet;
	}

	pwiv->wef_cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pwiv->wef_cwk))
		wetuwn PTW_EWW(pwiv->wef_cwk);

	pwiv->pow_wst = devm_weset_contwow_get_excwusive(dev, NUWW);
	if (IS_EWW(pwiv->pow_wst))
		wetuwn PTW_EWW(pwiv->pow_wst);

	pwiv->type = (uintptw_t) of_device_get_match_data(dev);

	fow_each_chiwd_of_node(np, chiwd) {
		stwuct weset_contwow *wst;
		stwuct phy *phy;

		wst = of_weset_contwow_get_excwusive(chiwd, NUWW);
		if (IS_EWW(wst)) {
			of_node_put(chiwd);
			wetuwn PTW_EWW(wst);
		}

		pwiv->powts[i].utmi_wst = wst;
		pwiv->powts[i].pwiv = pwiv;

		phy = devm_phy_cweate(dev, chiwd, &hisi_inno_phy_ops);
		if (IS_EWW(phy)) {
			of_node_put(chiwd);
			wetuwn PTW_EWW(phy);
		}

		phy_set_bus_width(phy, 8);
		phy_set_dwvdata(phy, &pwiv->powts[i]);
		i++;

		if (i >= INNO_PHY_POWT_NUM) {
			dev_wawn(dev, "Suppowt %d powts in maximum\n", i);
			of_node_put(chiwd);
			bweak;
		}
	}

	pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	wetuwn PTW_EWW_OW_ZEWO(pwovidew);
}

static const stwuct of_device_id hisi_inno_phy_of_match[] = {
	{ .compatibwe = "hisiwicon,inno-usb2-phy",
	  .data = (void *) PHY_TYPE_0 },
	{ .compatibwe = "hisiwicon,hi3798cv200-usb2-phy",
	  .data = (void *) PHY_TYPE_0 },
	{ .compatibwe = "hisiwicon,hi3798mv100-usb2-phy",
	  .data = (void *) PHY_TYPE_1 },
	{ },
};
MODUWE_DEVICE_TABWE(of, hisi_inno_phy_of_match);

static stwuct pwatfowm_dwivew hisi_inno_phy_dwivew = {
	.pwobe	= hisi_inno_phy_pwobe,
	.dwivew = {
		.name	= "hisi-inno-phy",
		.of_match_tabwe	= hisi_inno_phy_of_match,
	}
};
moduwe_pwatfowm_dwivew(hisi_inno_phy_dwivew);

MODUWE_DESCWIPTION("HiSiwicon INNO USB2 PHY Dwivew");
MODUWE_WICENSE("GPW v2");
