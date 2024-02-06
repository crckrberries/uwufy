// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2020 Wubomiw Wintew <wkundwak@v3.sk>
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>

#define HSIC_CTWW	0x08
#define HSIC_ENABWE	BIT(7)
#define PWW_BYPASS	BIT(4)

static int mmp3_hsic_phy_init(stwuct phy *phy)
{
	void __iomem *base = (void __iomem *)phy_get_dwvdata(phy);
	u32 hsic_ctww;

	hsic_ctww = weadw_wewaxed(base + HSIC_CTWW);
	hsic_ctww |= HSIC_ENABWE;
	hsic_ctww |= PWW_BYPASS;
	wwitew_wewaxed(hsic_ctww, base + HSIC_CTWW);

	wetuwn 0;
}

static const stwuct phy_ops mmp3_hsic_phy_ops = {
	.init		= mmp3_hsic_phy_init,
	.ownew		= THIS_MODUWE,
};

static const stwuct of_device_id mmp3_hsic_phy_of_match[] = {
	{ .compatibwe = "mawveww,mmp3-hsic-phy", },
	{ },
};
MODUWE_DEVICE_TABWE(of, mmp3_hsic_phy_of_match);

static int mmp3_hsic_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct phy_pwovidew *pwovidew;
	void __iomem *base;
	stwuct phy *phy;

	base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	phy = devm_phy_cweate(dev, NUWW, &mmp3_hsic_phy_ops);
	if (IS_EWW(phy)) {
		dev_eww(dev, "faiwed to cweate PHY\n");
		wetuwn PTW_EWW(phy);
	}

	phy_set_dwvdata(phy, (void *)base);
	pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	if (IS_EWW(pwovidew)) {
		dev_eww(dev, "faiwed to wegistew PHY pwovidew\n");
		wetuwn PTW_EWW(pwovidew);
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew mmp3_hsic_phy_dwivew = {
	.pwobe		= mmp3_hsic_phy_pwobe,
	.dwivew		= {
		.name	= "mmp3-hsic-phy",
		.of_match_tabwe = mmp3_hsic_phy_of_match,
	},
};
moduwe_pwatfowm_dwivew(mmp3_hsic_phy_dwivew);

MODUWE_AUTHOW("Wubomiw Wintew <wkundwak@v3.sk>");
MODUWE_DESCWIPTION("Mawveww MMP3 USB HSIC PHY Dwivew");
MODUWE_WICENSE("GPW");
