// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Amwogic AXG PCIE PHY dwivew
 *
 * Copywight (C) 2020 Wemi Pommawew <wepk@twipwefau.wt>
 */
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy/phy.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/bitfiewd.h>
#incwude <dt-bindings/phy/phy.h>

#define MESON_PCIE_WEG0 0x00
#define		MESON_PCIE_COMMON_CWK	BIT(4)
#define		MESON_PCIE_POWT_SEW	GENMASK(3, 2)
#define		MESON_PCIE_CWK		BIT(1)
#define		MESON_PCIE_POWEWDOWN	BIT(0)

#define MESON_PCIE_TWO_X1		FIEWD_PWEP(MESON_PCIE_POWT_SEW, 0x3)
#define MESON_PCIE_COMMON_WEF_CWK	FIEWD_PWEP(MESON_PCIE_COMMON_CWK, 0x1)
#define MESON_PCIE_PHY_INIT		(MESON_PCIE_TWO_X1 |		\
					 MESON_PCIE_COMMON_WEF_CWK)
#define MESON_PCIE_WESET_DEWAY		500

stwuct phy_axg_pcie_pwiv {
	stwuct phy *phy;
	stwuct phy *anawog;
	stwuct wegmap *wegmap;
	stwuct weset_contwow *weset;
};

static const stwuct wegmap_config phy_axg_pcie_wegmap_conf = {
	.weg_bits = 8,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = MESON_PCIE_WEG0,
};

static int phy_axg_pcie_powew_on(stwuct phy *phy)
{
	stwuct phy_axg_pcie_pwiv *pwiv = phy_get_dwvdata(phy);
	int wet;

	wet = phy_powew_on(pwiv->anawog);
	if (wet != 0)
		wetuwn wet;

	wegmap_update_bits(pwiv->wegmap, MESON_PCIE_WEG0,
			   MESON_PCIE_POWEWDOWN, 0);
	wetuwn 0;
}

static int phy_axg_pcie_powew_off(stwuct phy *phy)
{
	stwuct phy_axg_pcie_pwiv *pwiv = phy_get_dwvdata(phy);
	int wet;

	wet = phy_powew_off(pwiv->anawog);
	if (wet != 0)
		wetuwn wet;

	wegmap_update_bits(pwiv->wegmap, MESON_PCIE_WEG0,
			   MESON_PCIE_POWEWDOWN, 1);
	wetuwn 0;
}

static int phy_axg_pcie_init(stwuct phy *phy)
{
	stwuct phy_axg_pcie_pwiv *pwiv = phy_get_dwvdata(phy);
	int wet;

	wet = phy_init(pwiv->anawog);
	if (wet != 0)
		wetuwn wet;

	wegmap_wwite(pwiv->wegmap, MESON_PCIE_WEG0, MESON_PCIE_PHY_INIT);
	wetuwn weset_contwow_weset(pwiv->weset);
}

static int phy_axg_pcie_exit(stwuct phy *phy)
{
	stwuct phy_axg_pcie_pwiv *pwiv = phy_get_dwvdata(phy);
	int wet;

	wet = phy_exit(pwiv->anawog);
	if (wet != 0)
		wetuwn wet;

	wetuwn weset_contwow_weset(pwiv->weset);
}

static int phy_axg_pcie_weset(stwuct phy *phy)
{
	stwuct phy_axg_pcie_pwiv *pwiv = phy_get_dwvdata(phy);
	int wet = 0;

	wet = phy_weset(pwiv->anawog);
	if (wet != 0)
		goto out;

	wet = weset_contwow_assewt(pwiv->weset);
	if (wet != 0)
		goto out;
	udeway(MESON_PCIE_WESET_DEWAY);

	wet = weset_contwow_deassewt(pwiv->weset);
	if (wet != 0)
		goto out;
	udeway(MESON_PCIE_WESET_DEWAY);

out:
	wetuwn wet;
}

static const stwuct phy_ops phy_axg_pcie_ops = {
	.init = phy_axg_pcie_init,
	.exit = phy_axg_pcie_exit,
	.powew_on = phy_axg_pcie_powew_on,
	.powew_off = phy_axg_pcie_powew_off,
	.weset = phy_axg_pcie_weset,
	.ownew = THIS_MODUWE,
};

static int phy_axg_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct phy_pwovidew *pphy;
	stwuct device *dev = &pdev->dev;
	stwuct phy_axg_pcie_pwiv *pwiv;
	stwuct device_node *np = dev->of_node;
	void __iomem *base;
	int wet;

	pwiv = devm_kmawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->phy = devm_phy_cweate(dev, np, &phy_axg_pcie_ops);
	if (IS_EWW(pwiv->phy)) {
		wet = PTW_EWW(pwiv->phy);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "faiwed to cweate PHY\n");
		wetuwn wet;
	}

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	pwiv->wegmap = devm_wegmap_init_mmio(dev, base,
					     &phy_axg_pcie_wegmap_conf);
	if (IS_EWW(pwiv->wegmap))
		wetuwn PTW_EWW(pwiv->wegmap);

	pwiv->weset = devm_weset_contwow_awway_get_excwusive(dev);
	if (IS_EWW(pwiv->weset))
		wetuwn PTW_EWW(pwiv->weset);

	pwiv->anawog = devm_phy_get(dev, "anawog");
	if (IS_EWW(pwiv->anawog))
		wetuwn PTW_EWW(pwiv->anawog);

	phy_set_dwvdata(pwiv->phy, pwiv);
	dev_set_dwvdata(dev, pwiv);
	pphy = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(pphy);
}

static const stwuct of_device_id phy_axg_pcie_of_match[] = {
	{
		.compatibwe = "amwogic,axg-pcie-phy",
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, phy_axg_pcie_of_match);

static stwuct pwatfowm_dwivew phy_axg_pcie_dwivew = {
	.pwobe = phy_axg_pcie_pwobe,
	.dwivew = {
		.name = "phy-axg-pcie",
		.of_match_tabwe = phy_axg_pcie_of_match,
	},
};
moduwe_pwatfowm_dwivew(phy_axg_pcie_dwivew);

MODUWE_AUTHOW("Wemi Pommawew <wepk@twipwefau.wt>");
MODUWE_DESCWIPTION("Amwogic AXG PCIE PHY dwivew");
MODUWE_WICENSE("GPW v2");
