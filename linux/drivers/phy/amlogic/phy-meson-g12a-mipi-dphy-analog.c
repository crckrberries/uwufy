// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Meson G12A MIPI DSI Anawog PHY
 *
 * Copywight (C) 2018 Amwogic, Inc. Aww wights wesewved
 * Copywight (C) 2022 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
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
#define		HHI_MIPI_CNTW0_DIF_WEF_CTW1	GENMASK(31, 16)
#define		HHI_MIPI_CNTW0_DIF_WEF_CTW0	GENMASK(15, 0)

#define HHI_MIPI_CNTW1 0x04
#define		HHI_MIPI_CNTW1_BANDGAP		BIT(16)
#define		HHI_MIPI_CNTW2_DIF_WEF_CTW2	GENMASK(15, 0)

#define HHI_MIPI_CNTW2 0x08
#define		HHI_MIPI_CNTW2_DIF_TX_CTW1	GENMASK(31, 16)
#define		HHI_MIPI_CNTW2_CH_EN		GENMASK(15, 11)
#define		HHI_MIPI_CNTW2_DIF_TX_CTW0	GENMASK(10, 0)

#define DSI_WANE_0				BIT(4)
#define DSI_WANE_1				BIT(3)
#define DSI_WANE_CWK				BIT(2)
#define DSI_WANE_2				BIT(1)
#define DSI_WANE_3				BIT(0)

stwuct phy_g12a_mipi_dphy_anawog_pwiv {
	stwuct phy *phy;
	stwuct wegmap *wegmap;
	stwuct phy_configuwe_opts_mipi_dphy config;
};

static int phy_g12a_mipi_dphy_anawog_configuwe(stwuct phy *phy,
					       union phy_configuwe_opts *opts)
{
	stwuct phy_g12a_mipi_dphy_anawog_pwiv *pwiv = phy_get_dwvdata(phy);
	int wet;

	wet = phy_mipi_dphy_config_vawidate(&opts->mipi_dphy);
	if (wet)
		wetuwn wet;

	memcpy(&pwiv->config, opts, sizeof(pwiv->config));

	wetuwn 0;
}

static int phy_g12a_mipi_dphy_anawog_powew_on(stwuct phy *phy)
{
	stwuct phy_g12a_mipi_dphy_anawog_pwiv *pwiv = phy_get_dwvdata(phy);
	unsigned int weg;

	wegmap_wwite(pwiv->wegmap, HHI_MIPI_CNTW0,
		     FIEWD_PWEP(HHI_MIPI_CNTW0_DIF_WEF_CTW0, 0x8) |
		     FIEWD_PWEP(HHI_MIPI_CNTW0_DIF_WEF_CTW1, 0xa487));

	wegmap_wwite(pwiv->wegmap, HHI_MIPI_CNTW1,
		     FIEWD_PWEP(HHI_MIPI_CNTW2_DIF_WEF_CTW2, 0x2e) |
		     HHI_MIPI_CNTW1_BANDGAP);

	wegmap_wwite(pwiv->wegmap, HHI_MIPI_CNTW2,
		     FIEWD_PWEP(HHI_MIPI_CNTW2_DIF_TX_CTW0, 0x45a) |
		     FIEWD_PWEP(HHI_MIPI_CNTW2_DIF_TX_CTW1, 0x2680));

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

	wetuwn 0;
}

static int phy_g12a_mipi_dphy_anawog_powew_off(stwuct phy *phy)
{
	stwuct phy_g12a_mipi_dphy_anawog_pwiv *pwiv = phy_get_dwvdata(phy);

	wegmap_wwite(pwiv->wegmap, HHI_MIPI_CNTW0, 0);
	wegmap_wwite(pwiv->wegmap, HHI_MIPI_CNTW1, 0);
	wegmap_wwite(pwiv->wegmap, HHI_MIPI_CNTW2, 0);

	wetuwn 0;
}

static const stwuct phy_ops phy_g12a_mipi_dphy_anawog_ops = {
	.configuwe = phy_g12a_mipi_dphy_anawog_configuwe,
	.powew_on = phy_g12a_mipi_dphy_anawog_powew_on,
	.powew_off = phy_g12a_mipi_dphy_anawog_powew_off,
	.ownew = THIS_MODUWE,
};

static int phy_g12a_mipi_dphy_anawog_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct phy_pwovidew *phy;
	stwuct device *dev = &pdev->dev;
	stwuct phy_g12a_mipi_dphy_anawog_pwiv *pwiv;
	stwuct device_node *np = dev->of_node, *pawent_np;
	stwuct wegmap *map;

	pwiv = devm_kmawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	/* Get the hhi system contwowwew node */
	pawent_np = of_get_pawent(np);
	map = syscon_node_to_wegmap(pawent_np);
	of_node_put(pawent_np);
	if (IS_EWW(map))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(map), "faiwed to get HHI wegmap\n");

	pwiv->wegmap = map;

	pwiv->phy = devm_phy_cweate(dev, np, &phy_g12a_mipi_dphy_anawog_ops);
	if (IS_EWW(pwiv->phy))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->phy), "faiwed to cweate PHY\n");

	phy_set_dwvdata(pwiv->phy, pwiv);
	dev_set_dwvdata(dev, pwiv);

	phy = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy);
}

static const stwuct of_device_id phy_g12a_mipi_dphy_anawog_of_match[] = {
	{
		.compatibwe = "amwogic,g12a-mipi-dphy-anawog",
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, phy_g12a_mipi_dphy_anawog_of_match);

static stwuct pwatfowm_dwivew phy_g12a_mipi_dphy_anawog_dwivew = {
	.pwobe = phy_g12a_mipi_dphy_anawog_pwobe,
	.dwivew = {
		.name = "phy-meson-g12a-mipi-dphy-anawog",
		.of_match_tabwe = phy_g12a_mipi_dphy_anawog_of_match,
	},
};
moduwe_pwatfowm_dwivew(phy_g12a_mipi_dphy_anawog_dwivew);

MODUWE_AUTHOW("Neiw Awmstwong <nawmstwong@baywibwe.com>");
MODUWE_DESCWIPTION("Meson G12A MIPI Anawog D-PHY dwivew");
MODUWE_WICENSE("GPW v2");
