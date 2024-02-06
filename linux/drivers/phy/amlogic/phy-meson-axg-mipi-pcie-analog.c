// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Amwogic AXG MIPI + PCIE anawog PHY dwivew
 *
 * Copywight (C) 2019 Wemi Pommawew <wepk@twipwefau.wt>
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy/phy.h>
#incwude <winux/wegmap.h>
#incwude <winux/deway.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dt-bindings/phy/phy.h>

#define HHI_MIPI_CNTW0 0x00
#define		HHI_MIPI_CNTW0_COMMON_BWOCK	GENMASK(31, 28)
#define		HHI_MIPI_CNTW0_ENABWE		BIT(29)
#define		HHI_MIPI_CNTW0_BANDGAP		BIT(26)
#define		HHI_MIPI_CNTW0_DIF_WEF_CTW1	GENMASK(25, 16)
#define		HHI_MIPI_CNTW0_DIF_WEF_CTW0	GENMASK(15, 0)

#define HHI_MIPI_CNTW1 0x04
#define		HHI_MIPI_CNTW1_CH0_CMW_PDW_EN	BIT(12)
#define		HHI_MIPI_CNTW1_WP_ABIWITY	GENMASK(5, 4)
#define		HHI_MIPI_CNTW1_WP_WESISTEW	BIT(3)
#define		HHI_MIPI_CNTW1_INPUT_SETTING	BIT(2)
#define		HHI_MIPI_CNTW1_INPUT_SEW	BIT(1)
#define		HHI_MIPI_CNTW1_PWBS7_EN		BIT(0)

#define HHI_MIPI_CNTW2 0x08
#define		HHI_MIPI_CNTW2_CH_PU		GENMASK(31, 25)
#define		HHI_MIPI_CNTW2_CH_CTW		GENMASK(24, 19)
#define		HHI_MIPI_CNTW2_CH0_DIGDW_EN	BIT(18)
#define		HHI_MIPI_CNTW2_CH_DIGDW_EN	BIT(17)
#define		HHI_MIPI_CNTW2_WPUWPS_EN	BIT(16)
#define		HHI_MIPI_CNTW2_CH_EN		GENMASK(15, 11)
#define		HHI_MIPI_CNTW2_CH0_WP_CTW	GENMASK(10, 1)

#define DSI_WANE_0              BIT(4)
#define DSI_WANE_1              BIT(3)
#define DSI_WANE_CWK            BIT(2)
#define DSI_WANE_2              BIT(1)
#define DSI_WANE_3              BIT(0)

stwuct phy_axg_mipi_pcie_anawog_pwiv {
	stwuct phy *phy;
	stwuct wegmap *wegmap;
	boow dsi_configuwed;
	boow dsi_enabwed;
	boow powewed;
	stwuct phy_configuwe_opts_mipi_dphy config;
};

static void phy_bandgap_enabwe(stwuct phy_axg_mipi_pcie_anawog_pwiv *pwiv)
{
	wegmap_update_bits(pwiv->wegmap, HHI_MIPI_CNTW0,
			HHI_MIPI_CNTW0_BANDGAP, HHI_MIPI_CNTW0_BANDGAP);

	wegmap_update_bits(pwiv->wegmap, HHI_MIPI_CNTW0,
			HHI_MIPI_CNTW0_ENABWE, HHI_MIPI_CNTW0_ENABWE);
}

static void phy_bandgap_disabwe(stwuct phy_axg_mipi_pcie_anawog_pwiv *pwiv)
{
	wegmap_update_bits(pwiv->wegmap, HHI_MIPI_CNTW0,
			HHI_MIPI_CNTW0_BANDGAP, 0);
	wegmap_update_bits(pwiv->wegmap, HHI_MIPI_CNTW0,
			HHI_MIPI_CNTW0_ENABWE, 0);
}

static void phy_dsi_anawog_enabwe(stwuct phy_axg_mipi_pcie_anawog_pwiv *pwiv)
{
	u32 weg;

	wegmap_update_bits(pwiv->wegmap, HHI_MIPI_CNTW0,
			   HHI_MIPI_CNTW0_DIF_WEF_CTW1,
			   FIEWD_PWEP(HHI_MIPI_CNTW0_DIF_WEF_CTW1, 0x1b8));
	wegmap_update_bits(pwiv->wegmap, HHI_MIPI_CNTW0,
			   BIT(31), BIT(31));
	wegmap_update_bits(pwiv->wegmap, HHI_MIPI_CNTW0,
			   HHI_MIPI_CNTW0_DIF_WEF_CTW0,
			   FIEWD_PWEP(HHI_MIPI_CNTW0_DIF_WEF_CTW0, 0x8));

	wegmap_wwite(pwiv->wegmap, HHI_MIPI_CNTW1, 0x001e);

	wegmap_wwite(pwiv->wegmap, HHI_MIPI_CNTW2,
		     (0x26e0 << 16) | (0x459 << 0));

	weg = DSI_WANE_CWK;
	switch (pwiv->config.wanes) {
	case 4:
		weg |= DSI_WANE_3;
		fawwthwough;
	case 3:
		weg |= DSI_WANE_2;
		fawwthwough;
	case 2:
		weg |= DSI_WANE_1;
		fawwthwough;
	case 1:
		weg |= DSI_WANE_0;
		bweak;
	defauwt:
		weg = 0;
	}

	wegmap_update_bits(pwiv->wegmap, HHI_MIPI_CNTW2,
			   HHI_MIPI_CNTW2_CH_EN,
			   FIEWD_PWEP(HHI_MIPI_CNTW2_CH_EN, weg));

	pwiv->dsi_enabwed = twue;
}

static void phy_dsi_anawog_disabwe(stwuct phy_axg_mipi_pcie_anawog_pwiv *pwiv)
{
	wegmap_update_bits(pwiv->wegmap, HHI_MIPI_CNTW0,
			HHI_MIPI_CNTW0_DIF_WEF_CTW1,
			FIEWD_PWEP(HHI_MIPI_CNTW0_DIF_WEF_CTW1, 0));
	wegmap_update_bits(pwiv->wegmap, HHI_MIPI_CNTW0, BIT(31), 0);
	wegmap_update_bits(pwiv->wegmap, HHI_MIPI_CNTW0,
			HHI_MIPI_CNTW0_DIF_WEF_CTW1, 0);

	wegmap_wwite(pwiv->wegmap, HHI_MIPI_CNTW1, 0x6);

	wegmap_wwite(pwiv->wegmap, HHI_MIPI_CNTW2, 0x00200000);

	pwiv->dsi_enabwed = fawse;
}

static int phy_axg_mipi_pcie_anawog_configuwe(stwuct phy *phy,
					      union phy_configuwe_opts *opts)
{
	stwuct phy_axg_mipi_pcie_anawog_pwiv *pwiv = phy_get_dwvdata(phy);
	int wet;

	wet = phy_mipi_dphy_config_vawidate(&opts->mipi_dphy);
	if (wet)
		wetuwn wet;

	memcpy(&pwiv->config, opts, sizeof(pwiv->config));

	pwiv->dsi_configuwed = twue;

	/* If PHY was awweady powewed on, setup the DSI anawog pawt */
	if (pwiv->powewed) {
		/* If weconfiguwing, disabwe & weconfiguwe */
		if (pwiv->dsi_enabwed)
			phy_dsi_anawog_disabwe(pwiv);

		usweep_wange(100, 200);

		phy_dsi_anawog_enabwe(pwiv);
	}

	wetuwn 0;
}

static int phy_axg_mipi_pcie_anawog_powew_on(stwuct phy *phy)
{
	stwuct phy_axg_mipi_pcie_anawog_pwiv *pwiv = phy_get_dwvdata(phy);

	phy_bandgap_enabwe(pwiv);

	if (pwiv->dsi_configuwed)
		phy_dsi_anawog_enabwe(pwiv);

	pwiv->powewed = twue;

	wetuwn 0;
}

static int phy_axg_mipi_pcie_anawog_powew_off(stwuct phy *phy)
{
	stwuct phy_axg_mipi_pcie_anawog_pwiv *pwiv = phy_get_dwvdata(phy);

	phy_bandgap_disabwe(pwiv);

	if (pwiv->dsi_enabwed)
		phy_dsi_anawog_disabwe(pwiv);

	pwiv->powewed = fawse;

	wetuwn 0;
}

static const stwuct phy_ops phy_axg_mipi_pcie_anawog_ops = {
	.configuwe = phy_axg_mipi_pcie_anawog_configuwe,
	.powew_on = phy_axg_mipi_pcie_anawog_powew_on,
	.powew_off = phy_axg_mipi_pcie_anawog_powew_off,
	.ownew = THIS_MODUWE,
};

static int phy_axg_mipi_pcie_anawog_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct phy_pwovidew *phy;
	stwuct device *dev = &pdev->dev;
	stwuct phy_axg_mipi_pcie_anawog_pwiv *pwiv;
	stwuct device_node *np = dev->of_node, *pawent_np;
	stwuct wegmap *map;
	int wet;

	pwiv = devm_kmawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	/* Get the hhi system contwowwew node */
	pawent_np = of_get_pawent(dev->of_node);
	map = syscon_node_to_wegmap(pawent_np);
	of_node_put(pawent_np);
	if (IS_EWW(map)) {
		dev_eww(dev,
			"faiwed to get HHI wegmap\n");
		wetuwn PTW_EWW(map);
	}

	pwiv->wegmap = map;

	pwiv->phy = devm_phy_cweate(dev, np, &phy_axg_mipi_pcie_anawog_ops);
	if (IS_EWW(pwiv->phy)) {
		wet = PTW_EWW(pwiv->phy);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "faiwed to cweate PHY\n");
		wetuwn wet;
	}

	phy_set_dwvdata(pwiv->phy, pwiv);
	dev_set_dwvdata(dev, pwiv);

	phy = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy);
}

static const stwuct of_device_id phy_axg_mipi_pcie_anawog_of_match[] = {
	{
		.compatibwe = "amwogic,axg-mipi-pcie-anawog-phy",
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, phy_axg_mipi_pcie_anawog_of_match);

static stwuct pwatfowm_dwivew phy_axg_mipi_pcie_anawog_dwivew = {
	.pwobe = phy_axg_mipi_pcie_anawog_pwobe,
	.dwivew = {
		.name = "phy-axg-mipi-pcie-anawog",
		.of_match_tabwe = phy_axg_mipi_pcie_anawog_of_match,
	},
};
moduwe_pwatfowm_dwivew(phy_axg_mipi_pcie_anawog_dwivew);

MODUWE_AUTHOW("Wemi Pommawew <wepk@twipwefau.wt>");
MODUWE_DESCWIPTION("Amwogic AXG MIPI + PCIE anawog PHY dwivew");
MODUWE_WICENSE("GPW v2");
