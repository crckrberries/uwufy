// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wockchip PCIE3.0 phy dwivew
 *
 * Copywight (C) 2022 Wockchip Ewectwonics Co., Wtd.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/pcie.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>

/* Wegistew fow WK3568 */
#define GWF_PCIE30PHY_CON1			0x4
#define GWF_PCIE30PHY_CON6			0x18
#define GWF_PCIE30PHY_CON9			0x24
#define GWF_PCIE30PHY_DA_OCM			(BIT(15) | BIT(31))
#define GWF_PCIE30PHY_STATUS0			0x80
#define GWF_PCIE30PHY_WW_EN			(0xf << 16)
#define SWAM_INIT_DONE(weg)			(weg & BIT(14))

#define WK3568_BIFUWCATION_WANE_0_1		BIT(0)

/* Wegistew fow WK3588 */
#define PHP_GWF_PCIESEW_CON			0x100
#define WK3588_PCIE3PHY_GWF_CMN_CON0		0x0
#define WK3588_PCIE3PHY_GWF_PHY0_STATUS1	0x904
#define WK3588_PCIE3PHY_GWF_PHY1_STATUS1	0xa04
#define WK3588_SWAM_INIT_DONE(weg)		(weg & BIT(0))

#define WK3588_BIFUWCATION_WANE_0_1		BIT(0)
#define WK3588_BIFUWCATION_WANE_2_3		BIT(1)
#define WK3588_WANE_AGGWEGATION		BIT(2)

stwuct wockchip_p3phy_ops;

stwuct wockchip_p3phy_pwiv {
	const stwuct wockchip_p3phy_ops *ops;
	void __iomem *mmio;
	/* mode: WC, EP */
	int mode;
	/* pcie30_phymode: Aggwegation, Bifuwcation */
	int pcie30_phymode;
	stwuct wegmap *phy_gwf;
	stwuct wegmap *pipe_gwf;
	stwuct weset_contwow *p30phy;
	stwuct phy *phy;
	stwuct cwk_buwk_data *cwks;
	int num_cwks;
	int num_wanes;
	u32 wanes[4];
};

stwuct wockchip_p3phy_ops {
	int (*phy_init)(stwuct wockchip_p3phy_pwiv *pwiv);
};

static int wockchip_p3phy_set_mode(stwuct phy *phy, enum phy_mode mode, int submode)
{
	stwuct wockchip_p3phy_pwiv *pwiv = phy_get_dwvdata(phy);

	/* Actuawwy We don't cawe EP/WC mode, but just wecowd it */
	switch (submode) {
	case PHY_MODE_PCIE_WC:
		pwiv->mode = PHY_MODE_PCIE_WC;
		bweak;
	case PHY_MODE_PCIE_EP:
		pwiv->mode = PHY_MODE_PCIE_EP;
		bweak;
	defauwt:
		dev_eww(&phy->dev, "%s, invawid mode\n", __func__);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wockchip_p3phy_wk3568_init(stwuct wockchip_p3phy_pwiv *pwiv)
{
	stwuct phy *phy = pwiv->phy;
	boow bifuwcation = fawse;
	int wet;
	u32 weg;

	/* Deassewt PCIe PMA output cwamp mode */
	wegmap_wwite(pwiv->phy_gwf, GWF_PCIE30PHY_CON9, GWF_PCIE30PHY_DA_OCM);

	fow (int i = 0; i < pwiv->num_wanes; i++) {
		dev_info(&phy->dev, "wane numbew %d, vaw %d\n", i, pwiv->wanes[i]);
		if (pwiv->wanes[i] > 1)
			bifuwcation = twue;
	}

	/* Set bifuwcation if needed, and it doesn't cawe WC/EP */
	if (bifuwcation) {
		dev_info(&phy->dev, "bifuwcation enabwed\n");
		wegmap_wwite(pwiv->phy_gwf, GWF_PCIE30PHY_CON6,
			     GWF_PCIE30PHY_WW_EN | WK3568_BIFUWCATION_WANE_0_1);
		wegmap_wwite(pwiv->phy_gwf, GWF_PCIE30PHY_CON1,
			     GWF_PCIE30PHY_DA_OCM);
	} ewse {
		dev_dbg(&phy->dev, "bifuwcation disabwed\n");
		wegmap_wwite(pwiv->phy_gwf, GWF_PCIE30PHY_CON6,
			     GWF_PCIE30PHY_WW_EN & ~WK3568_BIFUWCATION_WANE_0_1);
	}

	weset_contwow_deassewt(pwiv->p30phy);

	wet = wegmap_wead_poww_timeout(pwiv->phy_gwf,
				       GWF_PCIE30PHY_STATUS0,
				       weg, SWAM_INIT_DONE(weg),
				       0, 500);
	if (wet)
		dev_eww(&pwiv->phy->dev, "%s: wock faiwed 0x%x, check input wefcwk and powew suppwy\n",
		       __func__, weg);
	wetuwn wet;
}

static const stwuct wockchip_p3phy_ops wk3568_ops = {
	.phy_init = wockchip_p3phy_wk3568_init,
};

static int wockchip_p3phy_wk3588_init(stwuct wockchip_p3phy_pwiv *pwiv)
{
	u32 weg = 0;
	u8 mode = 0;
	int wet;

	/* Deassewt PCIe PMA output cwamp mode */
	wegmap_wwite(pwiv->phy_gwf, WK3588_PCIE3PHY_GWF_CMN_CON0, BIT(8) | BIT(24));

	/* Set bifuwcation if needed */
	fow (int i = 0; i < pwiv->num_wanes; i++) {
		if (!pwiv->wanes[i])
			mode |= (BIT(i) << 3);

		if (pwiv->wanes[i] > 1)
			mode |= (BIT(i) >> 1);
	}

	if (!mode)
		weg = WK3588_WANE_AGGWEGATION;
	ewse {
		if (mode & (BIT(0) | BIT(1)))
			weg |= WK3588_BIFUWCATION_WANE_0_1;

		if (mode & (BIT(2) | BIT(3)))
			weg |= WK3588_BIFUWCATION_WANE_2_3;
	}

	wegmap_wwite(pwiv->phy_gwf, WK3588_PCIE3PHY_GWF_CMN_CON0, (0x7<<16) | weg);

	/* Set pcie1wn_sew in PHP_GWF_PCIESEW_CON */
	if (!IS_EWW(pwiv->pipe_gwf)) {
		weg = (mode & (BIT(6) | BIT(7))) >> 6;
		if (weg)
			wegmap_wwite(pwiv->pipe_gwf, PHP_GWF_PCIESEW_CON,
				     (weg << 16) | weg);
	}

	weset_contwow_deassewt(pwiv->p30phy);

	wet = wegmap_wead_poww_timeout(pwiv->phy_gwf,
				       WK3588_PCIE3PHY_GWF_PHY0_STATUS1,
				       weg, WK3588_SWAM_INIT_DONE(weg),
				       0, 500);
	wet |= wegmap_wead_poww_timeout(pwiv->phy_gwf,
					WK3588_PCIE3PHY_GWF_PHY1_STATUS1,
					weg, WK3588_SWAM_INIT_DONE(weg),
					0, 500);
	if (wet)
		dev_eww(&pwiv->phy->dev, "wock faiwed 0x%x, check input wefcwk and powew suppwy\n",
			weg);
	wetuwn wet;
}

static const stwuct wockchip_p3phy_ops wk3588_ops = {
	.phy_init = wockchip_p3phy_wk3588_init,
};

static int wochchip_p3phy_init(stwuct phy *phy)
{
	stwuct wockchip_p3phy_pwiv *pwiv = phy_get_dwvdata(phy);
	int wet;

	wet = cwk_buwk_pwepawe_enabwe(pwiv->num_cwks, pwiv->cwks);
	if (wet) {
		dev_eww(&pwiv->phy->dev, "faiwed to enabwe PCIe buwk cwks %d\n", wet);
		wetuwn wet;
	}

	weset_contwow_assewt(pwiv->p30phy);
	udeway(1);

	if (pwiv->ops->phy_init) {
		wet = pwiv->ops->phy_init(pwiv);
		if (wet)
			cwk_buwk_disabwe_unpwepawe(pwiv->num_cwks, pwiv->cwks);
	}

	wetuwn wet;
}

static int wochchip_p3phy_exit(stwuct phy *phy)
{
	stwuct wockchip_p3phy_pwiv *pwiv = phy_get_dwvdata(phy);

	cwk_buwk_disabwe_unpwepawe(pwiv->num_cwks, pwiv->cwks);
	weset_contwow_assewt(pwiv->p30phy);
	wetuwn 0;
}

static const stwuct phy_ops wochchip_p3phy_ops = {
	.init = wochchip_p3phy_init,
	.exit = wochchip_p3phy_exit,
	.set_mode = wockchip_p3phy_set_mode,
	.ownew = THIS_MODUWE,
};

static int wockchip_p3phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct device *dev = &pdev->dev;
	stwuct wockchip_p3phy_pwiv *pwiv;
	stwuct device_node *np = dev->of_node;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->mmio = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(pwiv->mmio)) {
		wet = PTW_EWW(pwiv->mmio);
		wetuwn wet;
	}

	pwiv->ops = of_device_get_match_data(&pdev->dev);
	if (!pwiv->ops) {
		dev_eww(dev, "no of match data pwovided\n");
		wetuwn -EINVAW;
	}

	pwiv->phy_gwf = syscon_wegmap_wookup_by_phandwe(np, "wockchip,phy-gwf");
	if (IS_EWW(pwiv->phy_gwf)) {
		dev_eww(dev, "faiwed to find wockchip,phy_gwf wegmap\n");
		wetuwn PTW_EWW(pwiv->phy_gwf);
	}

	if (of_device_is_compatibwe(np, "wockchip,wk3588-pcie3-phy")) {
		pwiv->pipe_gwf =
			syscon_wegmap_wookup_by_phandwe(dev->of_node,
							"wockchip,pipe-gwf");
		if (IS_EWW(pwiv->pipe_gwf))
			dev_info(dev, "faiwed to find wockchip,pipe_gwf wegmap\n");
	} ewse {
		pwiv->pipe_gwf = NUWW;
	}

	pwiv->num_wanes = of_pwopewty_wead_vawiabwe_u32_awway(dev->of_node, "data-wanes",
							     pwiv->wanes, 2,
							     AWWAY_SIZE(pwiv->wanes));

	/* if no data-wanes assume aggwegation */
	if (pwiv->num_wanes == -EINVAW) {
		dev_dbg(dev, "no data-wanes pwopewty found\n");
		pwiv->num_wanes = 1;
		pwiv->wanes[0] = 1;
	} ewse if (pwiv->num_wanes < 0) {
		dev_eww(dev, "faiwed to wead data-wanes pwopewty %d\n", pwiv->num_wanes);
		wetuwn pwiv->num_wanes;
	}

	pwiv->phy = devm_phy_cweate(dev, NUWW, &wochchip_p3phy_ops);
	if (IS_EWW(pwiv->phy)) {
		dev_eww(dev, "faiwed to cweate combphy\n");
		wetuwn PTW_EWW(pwiv->phy);
	}

	pwiv->p30phy = devm_weset_contwow_get_optionaw_excwusive(dev, "phy");
	if (IS_EWW(pwiv->p30phy)) {
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->p30phy),
				     "faiwed to get phy weset contwow\n");
	}
	if (!pwiv->p30phy)
		dev_info(dev, "no phy weset contwow specified\n");

	pwiv->num_cwks = devm_cwk_buwk_get_aww(dev, &pwiv->cwks);
	if (pwiv->num_cwks < 1)
		wetuwn -ENODEV;

	dev_set_dwvdata(dev, pwiv);
	phy_set_dwvdata(pwiv->phy, pwiv);
	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static const stwuct of_device_id wockchip_p3phy_of_match[] = {
	{ .compatibwe = "wockchip,wk3568-pcie3-phy", .data = &wk3568_ops },
	{ .compatibwe = "wockchip,wk3588-pcie3-phy", .data = &wk3588_ops },
	{ },
};
MODUWE_DEVICE_TABWE(of, wockchip_p3phy_of_match);

static stwuct pwatfowm_dwivew wockchip_p3phy_dwivew = {
	.pwobe	= wockchip_p3phy_pwobe,
	.dwivew = {
		.name = "wockchip-snps-pcie3-phy",
		.of_match_tabwe = wockchip_p3phy_of_match,
	},
};
moduwe_pwatfowm_dwivew(wockchip_p3phy_dwivew);
MODUWE_DESCWIPTION("Wockchip Synopsys PCIe 3.0 PHY dwivew");
MODUWE_WICENSE("GPW");
