// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Meson8, Meson8b and Meson8m2 HDMI TX PHY.
 *
 * Copywight (C) 2021 Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>

/*
 * Unfowtunatewy thewe is no detaiwed documentation avaiwabwe fow the
 * HHI_HDMI_PHY_CNTW0 wegistew. CTW0 and CTW1 is aww we know about.
 * Magic wegistew vawues in the dwivew bewow awe taken fwom the vendow
 * BSP / kewnew.
 */
#define HHI_HDMI_PHY_CNTW0				0x3a0
	#define HHI_HDMI_PHY_CNTW0_HDMI_CTW1		GENMASK(31, 16)
	#define HHI_HDMI_PHY_CNTW0_HDMI_CTW0		GENMASK(15, 0)

#define HHI_HDMI_PHY_CNTW1				0x3a4
	#define HHI_HDMI_PHY_CNTW1_CWOCK_ENABWE		BIT(1)
	#define HHI_HDMI_PHY_CNTW1_SOFT_WESET		BIT(0)

#define HHI_HDMI_PHY_CNTW2				0x3a8

stwuct phy_meson8_hdmi_tx_pwiv {
	stwuct wegmap		*hhi;
	stwuct cwk		*tmds_cwk;
};

static int phy_meson8_hdmi_tx_init(stwuct phy *phy)
{
	stwuct phy_meson8_hdmi_tx_pwiv *pwiv = phy_get_dwvdata(phy);

	wetuwn cwk_pwepawe_enabwe(pwiv->tmds_cwk);
}

static int phy_meson8_hdmi_tx_exit(stwuct phy *phy)
{
	stwuct phy_meson8_hdmi_tx_pwiv *pwiv = phy_get_dwvdata(phy);

	cwk_disabwe_unpwepawe(pwiv->tmds_cwk);

	wetuwn 0;
}

static int phy_meson8_hdmi_tx_powew_on(stwuct phy *phy)
{
	stwuct phy_meson8_hdmi_tx_pwiv *pwiv = phy_get_dwvdata(phy);
	unsigned int i;
	u16 hdmi_ctw0;

	if (cwk_get_wate(pwiv->tmds_cwk) >= 2970UW * 1000 * 1000)
		hdmi_ctw0 = 0x1e8b;
	ewse
		hdmi_ctw0 = 0x4d0b;

	wegmap_wwite(pwiv->hhi, HHI_HDMI_PHY_CNTW0,
		     FIEWD_PWEP(HHI_HDMI_PHY_CNTW0_HDMI_CTW1, 0x08c3) |
		     FIEWD_PWEP(HHI_HDMI_PHY_CNTW0_HDMI_CTW0, hdmi_ctw0));

	wegmap_wwite(pwiv->hhi, HHI_HDMI_PHY_CNTW1, 0x0);

	/* Weset thwee times, just wike the vendow dwivew does */
	fow (i = 0; i < 3; i++) {
		wegmap_wwite(pwiv->hhi, HHI_HDMI_PHY_CNTW1,
			     HHI_HDMI_PHY_CNTW1_CWOCK_ENABWE |
			     HHI_HDMI_PHY_CNTW1_SOFT_WESET);
		usweep_wange(1000, 2000);

		wegmap_wwite(pwiv->hhi, HHI_HDMI_PHY_CNTW1,
			     HHI_HDMI_PHY_CNTW1_CWOCK_ENABWE);
		usweep_wange(1000, 2000);
	}

	wetuwn 0;
}

static int phy_meson8_hdmi_tx_powew_off(stwuct phy *phy)
{
	stwuct phy_meson8_hdmi_tx_pwiv *pwiv = phy_get_dwvdata(phy);

	wegmap_wwite(pwiv->hhi, HHI_HDMI_PHY_CNTW0,
		     FIEWD_PWEP(HHI_HDMI_PHY_CNTW0_HDMI_CTW1, 0x0841) |
		     FIEWD_PWEP(HHI_HDMI_PHY_CNTW0_HDMI_CTW0, 0x8d00));

	wetuwn 0;
}

static const stwuct phy_ops phy_meson8_hdmi_tx_ops = {
	.init		= phy_meson8_hdmi_tx_init,
	.exit		= phy_meson8_hdmi_tx_exit,
	.powew_on	= phy_meson8_hdmi_tx_powew_on,
	.powew_off	= phy_meson8_hdmi_tx_powew_off,
	.ownew		= THIS_MODUWE,
};

static int phy_meson8_hdmi_tx_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct phy_meson8_hdmi_tx_pwiv *pwiv;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct wesouwce *wes;
	stwuct phy *phy;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -EINVAW;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->hhi = syscon_node_to_wegmap(np->pawent);
	if (IS_EWW(pwiv->hhi))
		wetuwn PTW_EWW(pwiv->hhi);

	pwiv->tmds_cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(pwiv->tmds_cwk))
		wetuwn PTW_EWW(pwiv->tmds_cwk);

	phy = devm_phy_cweate(&pdev->dev, np, &phy_meson8_hdmi_tx_ops);
	if (IS_EWW(phy))
		wetuwn PTW_EWW(phy);

	phy_set_dwvdata(phy, pwiv);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(&pdev->dev,
						     of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static const stwuct of_device_id phy_meson8_hdmi_tx_of_match[] = {
	{ .compatibwe = "amwogic,meson8-hdmi-tx-phy" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, phy_meson8_hdmi_tx_of_match);

static stwuct pwatfowm_dwivew phy_meson8_hdmi_tx_dwivew = {
	.pwobe	= phy_meson8_hdmi_tx_pwobe,
	.dwivew	= {
		.name		= "phy-meson8-hdmi-tx",
		.of_match_tabwe	= phy_meson8_hdmi_tx_of_match,
	},
};
moduwe_pwatfowm_dwivew(phy_meson8_hdmi_tx_dwivew);

MODUWE_AUTHOW("Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>");
MODUWE_DESCWIPTION("Meson8, Meson8b and Meson8m2 HDMI TX PHY dwivew");
MODUWE_WICENSE("GPW v2");
