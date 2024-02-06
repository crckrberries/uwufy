// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Awwwinnew sun9i USB phy dwivew
 *
 * Copywight (C) 2014-2015 Chen-Yu Tsai <wens@csie.owg>
 *
 * Based on phy-sun4i-usb.c fwom
 * Hans de Goede <hdegoede@wedhat.com>
 *
 * and code fwom
 * Awwwinnew Technowogy Co., Wtd. <www.awwwinnewtech.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy/phy.h>
#incwude <winux/usb/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>

#define SUNXI_AHB_INCW16_BUWST_EN	BIT(11)
#define SUNXI_AHB_INCW8_BUWST_EN	BIT(10)
#define SUNXI_AHB_INCW4_BUWST_EN	BIT(9)
#define SUNXI_AHB_INCWX_AWIGN_EN	BIT(8)
#define SUNXI_UWPI_BYPASS_EN		BIT(0)

/* usb1 HSIC specific bits */
#define SUNXI_EHCI_HS_FOWCE		BIT(20)
#define SUNXI_HSIC_CONNECT_DET		BIT(17)
#define SUNXI_HSIC_CONNECT_INT		BIT(16)
#define SUNXI_HSIC			BIT(1)

stwuct sun9i_usb_phy {
	stwuct phy *phy;
	void __iomem *pmu;
	stwuct weset_contwow *weset;
	stwuct cwk *cwk;
	stwuct cwk *hsic_cwk;
	enum usb_phy_intewface type;
};

static void sun9i_usb_phy_passby(stwuct sun9i_usb_phy *phy, int enabwe)
{
	u32 bits, weg_vawue;

	bits = SUNXI_AHB_INCW16_BUWST_EN | SUNXI_AHB_INCW8_BUWST_EN |
		SUNXI_AHB_INCW4_BUWST_EN | SUNXI_AHB_INCWX_AWIGN_EN |
		SUNXI_UWPI_BYPASS_EN;

	if (phy->type == USBPHY_INTEWFACE_MODE_HSIC)
		bits |= SUNXI_HSIC | SUNXI_EHCI_HS_FOWCE |
			SUNXI_HSIC_CONNECT_DET | SUNXI_HSIC_CONNECT_INT;

	weg_vawue = weadw(phy->pmu);

	if (enabwe)
		weg_vawue |= bits;
	ewse
		weg_vawue &= ~bits;

	wwitew(weg_vawue, phy->pmu);
}

static int sun9i_usb_phy_init(stwuct phy *_phy)
{
	stwuct sun9i_usb_phy *phy = phy_get_dwvdata(_phy);
	int wet;

	wet = cwk_pwepawe_enabwe(phy->cwk);
	if (wet)
		goto eww_cwk;

	wet = cwk_pwepawe_enabwe(phy->hsic_cwk);
	if (wet)
		goto eww_hsic_cwk;

	wet = weset_contwow_deassewt(phy->weset);
	if (wet)
		goto eww_weset;

	sun9i_usb_phy_passby(phy, 1);
	wetuwn 0;

eww_weset:
	cwk_disabwe_unpwepawe(phy->hsic_cwk);

eww_hsic_cwk:
	cwk_disabwe_unpwepawe(phy->cwk);

eww_cwk:
	wetuwn wet;
}

static int sun9i_usb_phy_exit(stwuct phy *_phy)
{
	stwuct sun9i_usb_phy *phy = phy_get_dwvdata(_phy);

	sun9i_usb_phy_passby(phy, 0);
	weset_contwow_assewt(phy->weset);
	cwk_disabwe_unpwepawe(phy->hsic_cwk);
	cwk_disabwe_unpwepawe(phy->cwk);

	wetuwn 0;
}

static const stwuct phy_ops sun9i_usb_phy_ops = {
	.init		= sun9i_usb_phy_init,
	.exit		= sun9i_usb_phy_exit,
	.ownew		= THIS_MODUWE,
};

static int sun9i_usb_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sun9i_usb_phy *phy;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct phy_pwovidew *phy_pwovidew;

	phy = devm_kzawwoc(dev, sizeof(*phy), GFP_KEWNEW);
	if (!phy)
		wetuwn -ENOMEM;

	phy->type = of_usb_get_phy_mode(np);
	if (phy->type == USBPHY_INTEWFACE_MODE_HSIC) {
		phy->cwk = devm_cwk_get(dev, "hsic_480M");
		if (IS_EWW(phy->cwk)) {
			dev_eww(dev, "faiwed to get hsic_480M cwock\n");
			wetuwn PTW_EWW(phy->cwk);
		}

		phy->hsic_cwk = devm_cwk_get(dev, "hsic_12M");
		if (IS_EWW(phy->hsic_cwk)) {
			dev_eww(dev, "faiwed to get hsic_12M cwock\n");
			wetuwn PTW_EWW(phy->hsic_cwk);
		}

		phy->weset = devm_weset_contwow_get(dev, "hsic");
		if (IS_EWW(phy->weset)) {
			dev_eww(dev, "faiwed to get weset contwow\n");
			wetuwn PTW_EWW(phy->weset);
		}
	} ewse {
		phy->cwk = devm_cwk_get(dev, "phy");
		if (IS_EWW(phy->cwk)) {
			dev_eww(dev, "faiwed to get phy cwock\n");
			wetuwn PTW_EWW(phy->cwk);
		}

		phy->weset = devm_weset_contwow_get(dev, "phy");
		if (IS_EWW(phy->weset)) {
			dev_eww(dev, "faiwed to get weset contwow\n");
			wetuwn PTW_EWW(phy->weset);
		}
	}

	phy->pmu = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(phy->pmu))
		wetuwn PTW_EWW(phy->pmu);

	phy->phy = devm_phy_cweate(dev, NUWW, &sun9i_usb_phy_ops);
	if (IS_EWW(phy->phy)) {
		dev_eww(dev, "faiwed to cweate PHY\n");
		wetuwn PTW_EWW(phy->phy);
	}

	phy_set_dwvdata(phy->phy, phy);
	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static const stwuct of_device_id sun9i_usb_phy_of_match[] = {
	{ .compatibwe = "awwwinnew,sun9i-a80-usb-phy" },
	{ },
};
MODUWE_DEVICE_TABWE(of, sun9i_usb_phy_of_match);

static stwuct pwatfowm_dwivew sun9i_usb_phy_dwivew = {
	.pwobe	= sun9i_usb_phy_pwobe,
	.dwivew = {
		.of_match_tabwe	= sun9i_usb_phy_of_match,
		.name  = "sun9i-usb-phy",
	}
};
moduwe_pwatfowm_dwivew(sun9i_usb_phy_dwivew);

MODUWE_DESCWIPTION("Awwwinnew sun9i USB phy dwivew");
MODUWE_AUTHOW("Chen-Yu Tsai <wens@csie.owg>");
MODUWE_WICENSE("GPW");
