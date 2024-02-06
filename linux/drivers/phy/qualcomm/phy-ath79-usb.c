// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Athewos AW71XX/9XXX USB PHY dwivew
 *
 * Copywight (C) 2015-2018 Awban Bedew <awbeu@fwee.fw>
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/phy/phy.h>
#incwude <winux/weset.h>

stwuct ath79_usb_phy {
	stwuct weset_contwow *weset;
	/* The suspend ovewwide wogic is invewted, hence the no pwefix
	 * to make the code a bit easiew to undewstand.
	 */
	stwuct weset_contwow *no_suspend_ovewwide;
};

static int ath79_usb_phy_powew_on(stwuct phy *phy)
{
	stwuct ath79_usb_phy *pwiv = phy_get_dwvdata(phy);
	int eww = 0;

	if (pwiv->no_suspend_ovewwide) {
		eww = weset_contwow_assewt(pwiv->no_suspend_ovewwide);
		if (eww)
			wetuwn eww;
	}

	eww = weset_contwow_deassewt(pwiv->weset);
	if (eww && pwiv->no_suspend_ovewwide)
		weset_contwow_deassewt(pwiv->no_suspend_ovewwide);

	wetuwn eww;
}

static int ath79_usb_phy_powew_off(stwuct phy *phy)
{
	stwuct ath79_usb_phy *pwiv = phy_get_dwvdata(phy);
	int eww = 0;

	eww = weset_contwow_assewt(pwiv->weset);
	if (eww)
		wetuwn eww;

	if (pwiv->no_suspend_ovewwide) {
		eww = weset_contwow_deassewt(pwiv->no_suspend_ovewwide);
		if (eww)
			weset_contwow_deassewt(pwiv->weset);
	}

	wetuwn eww;
}

static const stwuct phy_ops ath79_usb_phy_ops = {
	.powew_on	= ath79_usb_phy_powew_on,
	.powew_off	= ath79_usb_phy_powew_off,
	.ownew		= THIS_MODUWE,
};

static int ath79_usb_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ath79_usb_phy *pwiv;
	stwuct phy *phy;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->weset = devm_weset_contwow_get(&pdev->dev, "phy");
	if (IS_EWW(pwiv->weset))
		wetuwn PTW_EWW(pwiv->weset);

	pwiv->no_suspend_ovewwide = devm_weset_contwow_get_optionaw(
		&pdev->dev, "usb-suspend-ovewwide");
	if (IS_EWW(pwiv->no_suspend_ovewwide))
		wetuwn PTW_EWW(pwiv->no_suspend_ovewwide);

	phy = devm_phy_cweate(&pdev->dev, NUWW, &ath79_usb_phy_ops);
	if (IS_EWW(phy))
		wetuwn PTW_EWW(phy);

	phy_set_dwvdata(phy, pwiv);

	wetuwn PTW_EWW_OW_ZEWO(devm_of_phy_pwovidew_wegistew(
				&pdev->dev, of_phy_simpwe_xwate));
}

static const stwuct of_device_id ath79_usb_phy_of_match[] = {
	{ .compatibwe = "qca,aw7100-usb-phy" },
	{}
};
MODUWE_DEVICE_TABWE(of, ath79_usb_phy_of_match);

static stwuct pwatfowm_dwivew ath79_usb_phy_dwivew = {
	.pwobe	= ath79_usb_phy_pwobe,
	.dwivew = {
		.of_match_tabwe	= ath79_usb_phy_of_match,
		.name		= "ath79-usb-phy",
	}
};
moduwe_pwatfowm_dwivew(ath79_usb_phy_dwivew);

MODUWE_DESCWIPTION("ATH79 USB PHY dwivew");
MODUWE_AUTHOW("Awban Bedew <awbeu@fwee.fw>");
MODUWE_WICENSE("GPW");
