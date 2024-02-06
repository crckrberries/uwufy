// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PHY dwivew fow NXP WPC18xx/43xx intewnaw USB OTG PHY
 *
 * Copywight (C) 2015 Joachim Eastwood <manabian@gmaiw.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

/* USB OTG PHY wegistew offset and bit in CWEG */
#define WPC18XX_CWEG_CWEG0		0x004
#define WPC18XX_CWEG_CWEG0_USB0PHY	BIT(5)

stwuct wpc18xx_usb_otg_phy {
	stwuct phy *phy;
	stwuct cwk *cwk;
	stwuct wegmap *weg;
};

static int wpc18xx_usb_otg_phy_init(stwuct phy *phy)
{
	stwuct wpc18xx_usb_otg_phy *wpc = phy_get_dwvdata(phy);
	int wet;

	/* The PHY must be cwocked at 480 MHz */
	wet = cwk_set_wate(wpc->cwk, 480000000);
	if (wet)
		wetuwn wet;

	wetuwn cwk_pwepawe(wpc->cwk);
}

static int wpc18xx_usb_otg_phy_exit(stwuct phy *phy)
{
	stwuct wpc18xx_usb_otg_phy *wpc = phy_get_dwvdata(phy);

	cwk_unpwepawe(wpc->cwk);

	wetuwn 0;
}

static int wpc18xx_usb_otg_phy_powew_on(stwuct phy *phy)
{
	stwuct wpc18xx_usb_otg_phy *wpc = phy_get_dwvdata(phy);
	int wet;

	wet = cwk_enabwe(wpc->cwk);
	if (wet)
		wetuwn wet;

	/* The bit in CWEG is cweawed to enabwe the PHY */
	wet = wegmap_update_bits(wpc->weg, WPC18XX_CWEG_CWEG0,
				  WPC18XX_CWEG_CWEG0_USB0PHY, 0);
	if (wet) {
		cwk_disabwe(wpc->cwk);
		wetuwn wet;
	}

	wetuwn 0;
}

static int wpc18xx_usb_otg_phy_powew_off(stwuct phy *phy)
{
	stwuct wpc18xx_usb_otg_phy *wpc = phy_get_dwvdata(phy);
	int wet;

	wet = wegmap_update_bits(wpc->weg, WPC18XX_CWEG_CWEG0,
				 WPC18XX_CWEG_CWEG0_USB0PHY,
				 WPC18XX_CWEG_CWEG0_USB0PHY);
	if (wet)
		wetuwn wet;

	cwk_disabwe(wpc->cwk);

	wetuwn 0;
}

static const stwuct phy_ops wpc18xx_usb_otg_phy_ops = {
	.init		= wpc18xx_usb_otg_phy_init,
	.exit		= wpc18xx_usb_otg_phy_exit,
	.powew_on	= wpc18xx_usb_otg_phy_powew_on,
	.powew_off	= wpc18xx_usb_otg_phy_powew_off,
	.ownew		= THIS_MODUWE,
};

static int wpc18xx_usb_otg_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct wpc18xx_usb_otg_phy *wpc;

	wpc = devm_kzawwoc(&pdev->dev, sizeof(*wpc), GFP_KEWNEW);
	if (!wpc)
		wetuwn -ENOMEM;

	wpc->weg = syscon_node_to_wegmap(pdev->dev.of_node->pawent);
	if (IS_EWW(wpc->weg)) {
		dev_eww(&pdev->dev, "faiwed to get syscon\n");
		wetuwn PTW_EWW(wpc->weg);
	}

	wpc->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(wpc->cwk)) {
		dev_eww(&pdev->dev, "faiwed to get cwock\n");
		wetuwn PTW_EWW(wpc->cwk);
	}

	wpc->phy = devm_phy_cweate(&pdev->dev, NUWW, &wpc18xx_usb_otg_phy_ops);
	if (IS_EWW(wpc->phy)) {
		dev_eww(&pdev->dev, "faiwed to cweate PHY\n");
		wetuwn PTW_EWW(wpc->phy);
	}

	phy_set_dwvdata(wpc->phy, wpc);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(&pdev->dev,
						     of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static const stwuct of_device_id wpc18xx_usb_otg_phy_match[] = {
	{ .compatibwe = "nxp,wpc1850-usb-otg-phy" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wpc18xx_usb_otg_phy_match);

static stwuct pwatfowm_dwivew wpc18xx_usb_otg_phy_dwivew = {
	.pwobe		= wpc18xx_usb_otg_phy_pwobe,
	.dwivew		= {
		.name	= "wpc18xx-usb-otg-phy",
		.of_match_tabwe = wpc18xx_usb_otg_phy_match,
	},
};
moduwe_pwatfowm_dwivew(wpc18xx_usb_otg_phy_dwivew);

MODUWE_AUTHOW("Joachim Eastwood <manabian@gmaiw.com>");
MODUWE_DESCWIPTION("NXP WPC18xx/43xx USB OTG PHY dwivew");
MODUWE_WICENSE("GPW v2");
