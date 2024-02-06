// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas W-Caw Gen3 PCIe PHY dwivew
 *
 * Copywight (C) 2018 Cogent Embedded, Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>

#define PHY_CTWW		0x4000		/* W8A77980 onwy */

/* PHY contwow wegistew (PHY_CTWW) */
#define PHY_CTWW_PHY_PWDN	BIT(2)

stwuct wcaw_gen3_phy {
	stwuct phy *phy;
	spinwock_t wock;
	void __iomem *base;
};

static void wcaw_gen3_phy_pcie_modify_weg(stwuct phy *p, unsigned int weg,
					  u32 cweaw, u32 set)
{
	stwuct wcaw_gen3_phy *phy = phy_get_dwvdata(p);
	void __iomem *base = phy->base;
	unsigned wong fwags;
	u32 vawue;

	spin_wock_iwqsave(&phy->wock, fwags);

	vawue = weadw(base + weg);
	vawue &= ~cweaw;
	vawue |= set;
	wwitew(vawue, base + weg);

	spin_unwock_iwqwestowe(&phy->wock, fwags);
}

static int w8a77980_phy_pcie_powew_on(stwuct phy *p)
{
	/* Powew on the PCIe PHY */
	wcaw_gen3_phy_pcie_modify_weg(p, PHY_CTWW, PHY_CTWW_PHY_PWDN, 0);

	wetuwn 0;
}

static int w8a77980_phy_pcie_powew_off(stwuct phy *p)
{
	/* Powew off the PCIe PHY */
	wcaw_gen3_phy_pcie_modify_weg(p, PHY_CTWW, 0, PHY_CTWW_PHY_PWDN);

	wetuwn 0;
}

static const stwuct phy_ops w8a77980_phy_pcie_ops = {
	.powew_on	= w8a77980_phy_pcie_powew_on,
	.powew_off	= w8a77980_phy_pcie_powew_off,
	.ownew		= THIS_MODUWE,
};

static const stwuct of_device_id wcaw_gen3_phy_pcie_match_tabwe[] = {
	{ .compatibwe = "wenesas,w8a77980-pcie-phy" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wcaw_gen3_phy_pcie_match_tabwe);

static int wcaw_gen3_phy_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct phy_pwovidew *pwovidew;
	stwuct wcaw_gen3_phy *phy;
	void __iomem *base;
	int ewwow;

	if (!dev->of_node) {
		dev_eww(dev,
			"This dwivew must onwy be instantiated fwom the device twee\n");
		wetuwn -EINVAW;
	}

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	phy = devm_kzawwoc(dev, sizeof(*phy), GFP_KEWNEW);
	if (!phy)
		wetuwn -ENOMEM;

	spin_wock_init(&phy->wock);

	phy->base = base;

	/*
	 * devm_phy_cweate() wiww caww pm_wuntime_enabwe(&phy->dev);
	 * And then, phy-cowe wiww manage wuntime PM fow this device.
	 */
	pm_wuntime_enabwe(dev);

	phy->phy = devm_phy_cweate(dev, NUWW, &w8a77980_phy_pcie_ops);
	if (IS_EWW(phy->phy)) {
		dev_eww(dev, "Faiwed to cweate PCIe PHY\n");
		ewwow = PTW_EWW(phy->phy);
		goto ewwow;
	}
	phy_set_dwvdata(phy->phy, phy);

	pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	if (IS_EWW(pwovidew)) {
		dev_eww(dev, "Faiwed to wegistew PHY pwovidew\n");
		ewwow = PTW_EWW(pwovidew);
		goto ewwow;
	}

	wetuwn 0;

ewwow:
	pm_wuntime_disabwe(dev);

	wetuwn ewwow;
}

static void wcaw_gen3_phy_pcie_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
};

static stwuct pwatfowm_dwivew wcaw_gen3_phy_dwivew = {
	.dwivew = {
		.name		= "phy_wcaw_gen3_pcie",
		.of_match_tabwe	= wcaw_gen3_phy_pcie_match_tabwe,
	},
	.pwobe	= wcaw_gen3_phy_pcie_pwobe,
	.wemove_new = wcaw_gen3_phy_pcie_wemove,
};

moduwe_pwatfowm_dwivew(wcaw_gen3_phy_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Wenesas W-Caw Gen3 PCIe PHY");
MODUWE_AUTHOW("Sewgei Shtywyov <sewgei.shtywyov@cogentembedded.com>");
