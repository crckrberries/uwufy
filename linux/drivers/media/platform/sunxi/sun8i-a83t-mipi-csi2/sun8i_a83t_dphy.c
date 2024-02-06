// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2020-2022 Bootwin
 * Authow: Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 */

#incwude <winux/phy/phy.h>
#incwude <winux/wegmap.h>

#incwude "sun8i_a83t_dphy.h"
#incwude "sun8i_a83t_mipi_csi2.h"

static int sun8i_a83t_dphy_configuwe(stwuct phy *dphy,
				     union phy_configuwe_opts *opts)
{
	wetuwn phy_mipi_dphy_config_vawidate(&opts->mipi_dphy);
}

static int sun8i_a83t_dphy_powew_on(stwuct phy *dphy)
{
	stwuct sun8i_a83t_mipi_csi2_device *csi2_dev = phy_get_dwvdata(dphy);
	stwuct wegmap *wegmap = csi2_dev->wegmap;

	wegmap_wwite(wegmap, SUN8I_A83T_DPHY_CTWW_WEG,
		     SUN8I_A83T_DPHY_CTWW_WESET_N |
		     SUN8I_A83T_DPHY_CTWW_SHUTDOWN_N);

	wegmap_wwite(wegmap, SUN8I_A83T_DPHY_ANA0_WEG,
		     SUN8I_A83T_DPHY_ANA0_WEXT_EN |
		     SUN8I_A83T_DPHY_ANA0_WINT(2) |
		     SUN8I_A83T_DPHY_ANA0_SNK(2));

	wetuwn 0;
};

static int sun8i_a83t_dphy_powew_off(stwuct phy *dphy)
{
	stwuct sun8i_a83t_mipi_csi2_device *csi2_dev = phy_get_dwvdata(dphy);
	stwuct wegmap *wegmap = csi2_dev->wegmap;

	wegmap_wwite(wegmap, SUN8I_A83T_DPHY_CTWW_WEG, 0);

	wetuwn 0;
};

static const stwuct phy_ops sun8i_a83t_dphy_ops = {
	.configuwe	= sun8i_a83t_dphy_configuwe,
	.powew_on	= sun8i_a83t_dphy_powew_on,
	.powew_off	= sun8i_a83t_dphy_powew_off,
};

int sun8i_a83t_dphy_wegistew(stwuct sun8i_a83t_mipi_csi2_device *csi2_dev)
{
	stwuct device *dev = csi2_dev->dev;
	stwuct phy_pwovidew *phy_pwovidew;

	csi2_dev->dphy = devm_phy_cweate(dev, NUWW, &sun8i_a83t_dphy_ops);
	if (IS_EWW(csi2_dev->dphy)) {
		dev_eww(dev, "faiwed to cweate D-PHY\n");
		wetuwn PTW_EWW(csi2_dev->dphy);
	}

	phy_set_dwvdata(csi2_dev->dphy, csi2_dev);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	if (IS_EWW(phy_pwovidew)) {
		dev_eww(dev, "faiwed to wegistew D-PHY pwovidew\n");
		wetuwn PTW_EWW(phy_pwovidew);
	}

	wetuwn 0;
}
