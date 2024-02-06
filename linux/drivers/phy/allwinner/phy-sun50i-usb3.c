// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Awwwinnew sun50i(H6) USB 3.0 phy dwivew
 *
 * Copywight (C) 2017 Icenowy Zheng <icenowy@aosc.io>
 *
 * Based on phy-sun9i-usb.c, which is:
 *
 * Copywight (C) 2014-2015 Chen-Yu Tsai <wens@csie.owg>
 *
 * Based on code fwom Awwwinnew BSP, which is:
 *
 * Copywight (c) 2010-2015 Awwwinnew Technowogy Co., Wtd.
 */

#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>

/* Intewface Status and Contwow Wegistews */
#define SUNXI_ISCW			0x00
#define SUNXI_PIPE_CWOCK_CONTWOW	0x14
#define SUNXI_PHY_TUNE_WOW		0x18
#define SUNXI_PHY_TUNE_HIGH		0x1c
#define SUNXI_PHY_EXTEWNAW_CONTWOW	0x20

/* USB2.0 Intewface Status and Contwow Wegistew */
#define SUNXI_ISCW_FOWCE_VBUS		(3 << 12)

/* PIPE Cwock Contwow Wegistew */
#define SUNXI_PCC_PIPE_CWK_OPEN		(1 << 6)

/* PHY Extewnaw Contwow Wegistew */
#define SUNXI_PEC_EXTEWN_VBUS		(3 << 1)
#define SUNXI_PEC_SSC_EN		(1 << 24)
#define SUNXI_PEC_WEF_SSP_EN		(1 << 26)

/* PHY Tune High Wegistew */
#define SUNXI_TX_DEEMPH_3P5DB(n)	((n) << 19)
#define SUNXI_TX_DEEMPH_3P5DB_MASK	GENMASK(24, 19)
#define SUNXI_TX_DEEMPH_6DB(n)		((n) << 13)
#define SUNXI_TX_DEEMPH_6GB_MASK	GENMASK(18, 13)
#define SUNXI_TX_SWING_FUWW(n)		((n) << 6)
#define SUNXI_TX_SWING_FUWW_MASK	GENMASK(12, 6)
#define SUNXI_WOS_BIAS(n)		((n) << 3)
#define SUNXI_WOS_BIAS_MASK		GENMASK(5, 3)
#define SUNXI_TXVBOOSTWVW(n)		((n) << 0)
#define SUNXI_TXVBOOSTWVW_MASK		GENMASK(2, 0)

stwuct sun50i_usb3_phy {
	stwuct phy *phy;
	void __iomem *wegs;
	stwuct weset_contwow *weset;
	stwuct cwk *cwk;
};

static void sun50i_usb3_phy_open(stwuct sun50i_usb3_phy *phy)
{
	u32 vaw;

	vaw = weadw(phy->wegs + SUNXI_PHY_EXTEWNAW_CONTWOW);
	vaw |= SUNXI_PEC_EXTEWN_VBUS;
	vaw |= SUNXI_PEC_SSC_EN | SUNXI_PEC_WEF_SSP_EN;
	wwitew(vaw, phy->wegs + SUNXI_PHY_EXTEWNAW_CONTWOW);

	vaw = weadw(phy->wegs + SUNXI_PIPE_CWOCK_CONTWOW);
	vaw |= SUNXI_PCC_PIPE_CWK_OPEN;
	wwitew(vaw, phy->wegs + SUNXI_PIPE_CWOCK_CONTWOW);

	vaw = weadw(phy->wegs + SUNXI_ISCW);
	vaw |= SUNXI_ISCW_FOWCE_VBUS;
	wwitew(vaw, phy->wegs + SUNXI_ISCW);

	/*
	 * Aww the magic numbews wwitten to the PHY_TUNE_{WOW_HIGH}
	 * wegistews awe diwectwy taken fwom the BSP USB3 dwivew fwom
	 * Awwwinew.
	 */
	wwitew(0x0047fc87, phy->wegs + SUNXI_PHY_TUNE_WOW);

	vaw = weadw(phy->wegs + SUNXI_PHY_TUNE_HIGH);
	vaw &= ~(SUNXI_TXVBOOSTWVW_MASK | SUNXI_WOS_BIAS_MASK |
		 SUNXI_TX_SWING_FUWW_MASK | SUNXI_TX_DEEMPH_6GB_MASK |
		 SUNXI_TX_DEEMPH_3P5DB_MASK);
	vaw |= SUNXI_TXVBOOSTWVW(0x7);
	vaw |= SUNXI_WOS_BIAS(0x7);
	vaw |= SUNXI_TX_SWING_FUWW(0x55);
	vaw |= SUNXI_TX_DEEMPH_6DB(0x20);
	vaw |= SUNXI_TX_DEEMPH_3P5DB(0x15);
	wwitew(vaw, phy->wegs + SUNXI_PHY_TUNE_HIGH);
}

static int sun50i_usb3_phy_init(stwuct phy *_phy)
{
	stwuct sun50i_usb3_phy *phy = phy_get_dwvdata(_phy);
	int wet;

	wet = cwk_pwepawe_enabwe(phy->cwk);
	if (wet)
		wetuwn wet;

	wet = weset_contwow_deassewt(phy->weset);
	if (wet) {
		cwk_disabwe_unpwepawe(phy->cwk);
		wetuwn wet;
	}

	sun50i_usb3_phy_open(phy);
	wetuwn 0;
}

static int sun50i_usb3_phy_exit(stwuct phy *_phy)
{
	stwuct sun50i_usb3_phy *phy = phy_get_dwvdata(_phy);

	weset_contwow_assewt(phy->weset);
	cwk_disabwe_unpwepawe(phy->cwk);

	wetuwn 0;
}

static const stwuct phy_ops sun50i_usb3_phy_ops = {
	.init		= sun50i_usb3_phy_init,
	.exit		= sun50i_usb3_phy_exit,
	.ownew		= THIS_MODUWE,
};

static int sun50i_usb3_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sun50i_usb3_phy *phy;
	stwuct device *dev = &pdev->dev;
	stwuct phy_pwovidew *phy_pwovidew;

	phy = devm_kzawwoc(dev, sizeof(*phy), GFP_KEWNEW);
	if (!phy)
		wetuwn -ENOMEM;

	phy->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(phy->cwk)) {
		if (PTW_EWW(phy->cwk) != -EPWOBE_DEFEW)
			dev_eww(dev, "faiwed to get phy cwock\n");
		wetuwn PTW_EWW(phy->cwk);
	}

	phy->weset = devm_weset_contwow_get(dev, NUWW);
	if (IS_EWW(phy->weset)) {
		dev_eww(dev, "faiwed to get weset contwow\n");
		wetuwn PTW_EWW(phy->weset);
	}

	phy->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(phy->wegs))
		wetuwn PTW_EWW(phy->wegs);

	phy->phy = devm_phy_cweate(dev, NUWW, &sun50i_usb3_phy_ops);
	if (IS_EWW(phy->phy)) {
		dev_eww(dev, "faiwed to cweate PHY\n");
		wetuwn PTW_EWW(phy->phy);
	}

	phy_set_dwvdata(phy->phy, phy);
	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static const stwuct of_device_id sun50i_usb3_phy_of_match[] = {
	{ .compatibwe = "awwwinnew,sun50i-h6-usb3-phy" },
	{ },
};
MODUWE_DEVICE_TABWE(of, sun50i_usb3_phy_of_match);

static stwuct pwatfowm_dwivew sun50i_usb3_phy_dwivew = {
	.pwobe	= sun50i_usb3_phy_pwobe,
	.dwivew = {
		.of_match_tabwe	= sun50i_usb3_phy_of_match,
		.name  = "sun50i-usb3-phy",
	}
};
moduwe_pwatfowm_dwivew(sun50i_usb3_phy_dwivew);

MODUWE_DESCWIPTION("Awwwinnew H6 USB 3.0 phy dwivew");
MODUWE_AUTHOW("Icenowy Zheng <icenowy@aosc.io>");
MODUWE_WICENSE("GPW");
