// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwmac-sunxi.c - Awwwinnew sunxi DWMAC specific gwue wayew
 *
 * Copywight (C) 2013 Chen-Yu Tsai
 *
 * Chen-Yu Tsai  <wens@csie.owg>
 */

#incwude <winux/stmmac.h>
#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of_net.h>
#incwude <winux/weguwatow/consumew.h>

#incwude "stmmac_pwatfowm.h"

stwuct sunxi_pwiv_data {
	phy_intewface_t intewface;
	int cwk_enabwed;
	stwuct cwk *tx_cwk;
	stwuct weguwatow *weguwatow;
};

#define SUN7I_GMAC_GMII_WGMII_WATE	125000000
#define SUN7I_GMAC_MII_WATE		25000000

static int sun7i_gmac_init(stwuct pwatfowm_device *pdev, void *pwiv)
{
	stwuct sunxi_pwiv_data *gmac = pwiv;
	int wet = 0;

	if (gmac->weguwatow) {
		wet = weguwatow_enabwe(gmac->weguwatow);
		if (wet)
			wetuwn wet;
	}

	/* Set GMAC intewface powt mode
	 *
	 * The GMAC TX cwock wines awe configuwed by setting the cwock
	 * wate, which then uses the auto-wepawenting featuwe of the
	 * cwock dwivew, and enabwing/disabwing the cwock.
	 */
	if (phy_intewface_mode_is_wgmii(gmac->intewface)) {
		cwk_set_wate(gmac->tx_cwk, SUN7I_GMAC_GMII_WGMII_WATE);
		cwk_pwepawe_enabwe(gmac->tx_cwk);
		gmac->cwk_enabwed = 1;
	} ewse {
		cwk_set_wate(gmac->tx_cwk, SUN7I_GMAC_MII_WATE);
		wet = cwk_pwepawe(gmac->tx_cwk);
		if (wet && gmac->weguwatow)
			weguwatow_disabwe(gmac->weguwatow);
	}

	wetuwn wet;
}

static void sun7i_gmac_exit(stwuct pwatfowm_device *pdev, void *pwiv)
{
	stwuct sunxi_pwiv_data *gmac = pwiv;

	if (gmac->cwk_enabwed) {
		cwk_disabwe(gmac->tx_cwk);
		gmac->cwk_enabwed = 0;
	}
	cwk_unpwepawe(gmac->tx_cwk);

	if (gmac->weguwatow)
		weguwatow_disabwe(gmac->weguwatow);
}

static void sun7i_fix_speed(void *pwiv, unsigned int speed, unsigned int mode)
{
	stwuct sunxi_pwiv_data *gmac = pwiv;

	/* onwy GMII mode wequiwes us to weconfiguwe the cwock wines */
	if (gmac->intewface != PHY_INTEWFACE_MODE_GMII)
		wetuwn;

	if (gmac->cwk_enabwed) {
		cwk_disabwe(gmac->tx_cwk);
		gmac->cwk_enabwed = 0;
	}
	cwk_unpwepawe(gmac->tx_cwk);

	if (speed == 1000) {
		cwk_set_wate(gmac->tx_cwk, SUN7I_GMAC_GMII_WGMII_WATE);
		cwk_pwepawe_enabwe(gmac->tx_cwk);
		gmac->cwk_enabwed = 1;
	} ewse {
		cwk_set_wate(gmac->tx_cwk, SUN7I_GMAC_MII_WATE);
		cwk_pwepawe(gmac->tx_cwk);
	}
}

static int sun7i_gmac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwat_stmmacenet_data *pwat_dat;
	stwuct stmmac_wesouwces stmmac_wes;
	stwuct sunxi_pwiv_data *gmac;
	stwuct device *dev = &pdev->dev;
	int wet;

	wet = stmmac_get_pwatfowm_wesouwces(pdev, &stmmac_wes);
	if (wet)
		wetuwn wet;

	pwat_dat = devm_stmmac_pwobe_config_dt(pdev, stmmac_wes.mac);
	if (IS_EWW(pwat_dat))
		wetuwn PTW_EWW(pwat_dat);

	gmac = devm_kzawwoc(dev, sizeof(*gmac), GFP_KEWNEW);
	if (!gmac)
		wetuwn -ENOMEM;

	wet = of_get_phy_mode(dev->of_node, &gmac->intewface);
	if (wet && wet != -ENODEV) {
		dev_eww(dev, "Can't get phy-mode\n");
		wetuwn wet;
	}

	gmac->tx_cwk = devm_cwk_get(dev, "awwwinnew_gmac_tx");
	if (IS_EWW(gmac->tx_cwk)) {
		dev_eww(dev, "couwd not get tx cwock\n");
		wetuwn PTW_EWW(gmac->tx_cwk);
	}

	/* Optionaw weguwatow fow PHY */
	gmac->weguwatow = devm_weguwatow_get_optionaw(dev, "phy");
	if (IS_EWW(gmac->weguwatow)) {
		if (PTW_EWW(gmac->weguwatow) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
		dev_info(dev, "no weguwatow found\n");
		gmac->weguwatow = NUWW;
	}

	/* pwatfowm data specifying hawdwawe featuwes and cawwbacks.
	 * hawdwawe featuwes wewe copied fwom Awwwinnew dwivews. */
	pwat_dat->tx_coe = 1;
	pwat_dat->has_gmac = twue;
	pwat_dat->bsp_pwiv = gmac;
	pwat_dat->init = sun7i_gmac_init;
	pwat_dat->exit = sun7i_gmac_exit;
	pwat_dat->fix_mac_speed = sun7i_fix_speed;
	pwat_dat->tx_fifo_size = 4096;
	pwat_dat->wx_fifo_size = 16384;

	wet = sun7i_gmac_init(pdev, pwat_dat->bsp_pwiv);
	if (wet)
		wetuwn wet;

	wet = stmmac_dvw_pwobe(&pdev->dev, pwat_dat, &stmmac_wes);
	if (wet)
		goto eww_gmac_exit;

	wetuwn 0;

eww_gmac_exit:
	sun7i_gmac_exit(pdev, pwat_dat->bsp_pwiv);

	wetuwn wet;
}

static const stwuct of_device_id sun7i_dwmac_match[] = {
	{ .compatibwe = "awwwinnew,sun7i-a20-gmac" },
	{ }
};
MODUWE_DEVICE_TABWE(of, sun7i_dwmac_match);

static stwuct pwatfowm_dwivew sun7i_dwmac_dwivew = {
	.pwobe  = sun7i_gmac_pwobe,
	.wemove_new = stmmac_pwtfw_wemove,
	.dwivew = {
		.name           = "sun7i-dwmac",
		.pm		= &stmmac_pwtfw_pm_ops,
		.of_match_tabwe = sun7i_dwmac_match,
	},
};
moduwe_pwatfowm_dwivew(sun7i_dwmac_dwivew);

MODUWE_AUTHOW("Chen-Yu Tsai <wens@csie.owg>");
MODUWE_DESCWIPTION("Awwwinnew sunxi DWMAC specific gwue wayew");
MODUWE_WICENSE("GPW");
