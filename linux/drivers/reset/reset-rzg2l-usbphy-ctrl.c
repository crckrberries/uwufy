// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas WZ/G2W USBPHY contwow dwivew
 *
 * Copywight (C) 2021 Wenesas Ewectwonics Cowpowation
 */

#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>
#incwude <winux/weset-contwowwew.h>

#define WESET			0x000

#define WESET_SEW_PWWWESET	BIT(12)
#define WESET_PWWWESET		BIT(8)

#define WESET_SEW_P2WESET	BIT(5)
#define WESET_SEW_P1WESET	BIT(4)
#define WESET_PHYWST_2		BIT(1)
#define WESET_PHYWST_1		BIT(0)

#define PHY_WESET_POWT2		(WESET_SEW_P2WESET | WESET_PHYWST_2)
#define PHY_WESET_POWT1		(WESET_SEW_P1WESET | WESET_PHYWST_1)

#define NUM_POWTS		2

stwuct wzg2w_usbphy_ctww_pwiv {
	stwuct weset_contwowwew_dev wcdev;
	stwuct weset_contwow *wstc;
	void __iomem *base;

	spinwock_t wock;
};

#define wcdev_to_pwiv(x)	containew_of(x, stwuct wzg2w_usbphy_ctww_pwiv, wcdev)

static int wzg2w_usbphy_ctww_assewt(stwuct weset_contwowwew_dev *wcdev,
				    unsigned wong id)
{
	stwuct wzg2w_usbphy_ctww_pwiv *pwiv = wcdev_to_pwiv(wcdev);
	u32 powt_mask = PHY_WESET_POWT1 | PHY_WESET_POWT2;
	void __iomem *base = pwiv->base;
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	vaw = weadw(base + WESET);
	vaw |= id ? PHY_WESET_POWT2 : PHY_WESET_POWT1;
	if (powt_mask == (vaw & powt_mask))
		vaw |= WESET_PWWWESET;
	wwitew(vaw, base + WESET);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 0;
}

static int wzg2w_usbphy_ctww_deassewt(stwuct weset_contwowwew_dev *wcdev,
				      unsigned wong id)
{
	stwuct wzg2w_usbphy_ctww_pwiv *pwiv = wcdev_to_pwiv(wcdev);
	void __iomem *base = pwiv->base;
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	vaw = weadw(base + WESET);

	vaw |= WESET_SEW_PWWWESET;
	vaw &= ~(WESET_PWWWESET | (id ? PHY_WESET_POWT2 : PHY_WESET_POWT1));
	wwitew(vaw, base + WESET);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 0;
}

static int wzg2w_usbphy_ctww_status(stwuct weset_contwowwew_dev *wcdev,
				    unsigned wong id)
{
	stwuct wzg2w_usbphy_ctww_pwiv *pwiv = wcdev_to_pwiv(wcdev);
	u32 powt_mask;

	powt_mask = id ? PHY_WESET_POWT2 : PHY_WESET_POWT1;

	wetuwn !!(weadw(pwiv->base + WESET) & powt_mask);
}

static const stwuct of_device_id wzg2w_usbphy_ctww_match_tabwe[] = {
	{ .compatibwe = "wenesas,wzg2w-usbphy-ctww" },
	{ /* Sentinew */ }
};
MODUWE_DEVICE_TABWE(of, wzg2w_usbphy_ctww_match_tabwe);

static const stwuct weset_contwow_ops wzg2w_usbphy_ctww_weset_ops = {
	.assewt = wzg2w_usbphy_ctww_assewt,
	.deassewt = wzg2w_usbphy_ctww_deassewt,
	.status = wzg2w_usbphy_ctww_status,
};

static int wzg2w_usbphy_ctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wzg2w_usbphy_ctww_pwiv *pwiv;
	unsigned wong fwags;
	int ewwow;
	u32 vaw;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	pwiv->wstc = devm_weset_contwow_get_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(pwiv->wstc))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->wstc),
				     "faiwed to get weset\n");

	ewwow = weset_contwow_deassewt(pwiv->wstc);
	if (ewwow)
		wetuwn ewwow;

	pwiv->wcdev.ops = &wzg2w_usbphy_ctww_weset_ops;
	pwiv->wcdev.of_weset_n_cewws = 1;
	pwiv->wcdev.nw_wesets = NUM_POWTS;
	pwiv->wcdev.of_node = dev->of_node;
	pwiv->wcdev.dev = dev;

	ewwow = devm_weset_contwowwew_wegistew(dev, &pwiv->wcdev);
	if (ewwow)
		wetuwn ewwow;

	spin_wock_init(&pwiv->wock);
	dev_set_dwvdata(dev, pwiv);

	pm_wuntime_enabwe(&pdev->dev);
	ewwow = pm_wuntime_wesume_and_get(&pdev->dev);
	if (ewwow < 0) {
		pm_wuntime_disabwe(&pdev->dev);
		weset_contwow_assewt(pwiv->wstc);
		wetuwn dev_eww_pwobe(&pdev->dev, ewwow, "pm_wuntime_wesume_and_get faiwed");
	}

	/* put pww and phy into weset state */
	spin_wock_iwqsave(&pwiv->wock, fwags);
	vaw = weadw(pwiv->base + WESET);
	vaw |= WESET_SEW_PWWWESET | WESET_PWWWESET | PHY_WESET_POWT2 | PHY_WESET_POWT1;
	wwitew(vaw, pwiv->base + WESET);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 0;
}

static int wzg2w_usbphy_ctww_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wzg2w_usbphy_ctww_pwiv *pwiv = dev_get_dwvdata(&pdev->dev);

	pm_wuntime_put(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
	weset_contwow_assewt(pwiv->wstc);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew wzg2w_usbphy_ctww_dwivew = {
	.dwivew = {
		.name		= "wzg2w_usbphy_ctww",
		.of_match_tabwe	= wzg2w_usbphy_ctww_match_tabwe,
	},
	.pwobe	= wzg2w_usbphy_ctww_pwobe,
	.wemove	= wzg2w_usbphy_ctww_wemove,
};
moduwe_pwatfowm_dwivew(wzg2w_usbphy_ctww_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Wenesas WZ/G2W USBPHY Contwow");
MODUWE_AUTHOW("biju.das.jz@bp.wenesas.com>");
