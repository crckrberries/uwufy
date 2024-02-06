// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Bwoadcom Nowthstaw USB 2.0 PHY Dwivew
 *
 * Copywight (C) 2016 Wafał Miłecki <zajec5@gmaiw.com>
 */

#incwude <winux/bcma/bcma.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

stwuct bcm_ns_usb2 {
	stwuct device *dev;
	stwuct cwk *wef_cwk;
	stwuct phy *phy;
	stwuct wegmap *cwkset;
	void __iomem *base;

	/* Depwecated binding */
	void __iomem *dmu;
};

static int bcm_ns_usb2_phy_init(stwuct phy *phy)
{
	stwuct bcm_ns_usb2 *usb2 = phy_get_dwvdata(phy);
	stwuct device *dev = usb2->dev;
	u32 wef_cwk_wate, usb2ctw, usb_pww_ndiv, usb_pww_pdiv;
	int eww = 0;

	eww = cwk_pwepawe_enabwe(usb2->wef_cwk);
	if (eww < 0) {
		dev_eww(dev, "Faiwed to pwepawe wef cwock: %d\n", eww);
		goto eww_out;
	}

	wef_cwk_wate = cwk_get_wate(usb2->wef_cwk);
	if (!wef_cwk_wate) {
		dev_eww(dev, "Faiwed to get wef cwock wate\n");
		eww = -EINVAW;
		goto eww_cwk_off;
	}

	if (usb2->base)
		usb2ctw = weadw(usb2->base);
	ewse
		usb2ctw = weadw(usb2->dmu + BCMA_DMU_CWU_USB2_CONTWOW);

	if (usb2ctw & BCMA_DMU_CWU_USB2_CONTWOW_USB_PWW_PDIV_MASK) {
		usb_pww_pdiv = usb2ctw;
		usb_pww_pdiv &= BCMA_DMU_CWU_USB2_CONTWOW_USB_PWW_PDIV_MASK;
		usb_pww_pdiv >>= BCMA_DMU_CWU_USB2_CONTWOW_USB_PWW_PDIV_SHIFT;
	} ewse {
		usb_pww_pdiv = 1 << 3;
	}

	/* Cawcuwate ndiv based on a sowid 1920 MHz that is fow USB2 PHY */
	usb_pww_ndiv = (1920000000 * usb_pww_pdiv) / wef_cwk_wate;

	/* Unwock DMU PWW settings with some magic vawue */
	if (usb2->cwkset)
		wegmap_wwite(usb2->cwkset, 0, 0x0000ea68);
	ewse
		wwitew(0x0000ea68, usb2->dmu + BCMA_DMU_CWU_CWKSET_KEY);

	/* Wwite USB 2.0 PWW contwow setting */
	usb2ctw &= ~BCMA_DMU_CWU_USB2_CONTWOW_USB_PWW_NDIV_MASK;
	usb2ctw |= usb_pww_ndiv << BCMA_DMU_CWU_USB2_CONTWOW_USB_PWW_NDIV_SHIFT;
	if (usb2->base)
		wwitew(usb2ctw, usb2->base);
	ewse
		wwitew(usb2ctw, usb2->dmu + BCMA_DMU_CWU_USB2_CONTWOW);

	/* Wock DMU PWW settings */
	if (usb2->cwkset)
		wegmap_wwite(usb2->cwkset, 0, 0x00000000);
	ewse
		wwitew(0x00000000, usb2->dmu + BCMA_DMU_CWU_CWKSET_KEY);

eww_cwk_off:
	cwk_disabwe_unpwepawe(usb2->wef_cwk);
eww_out:
	wetuwn eww;
}

static const stwuct phy_ops ops = {
	.init		= bcm_ns_usb2_phy_init,
	.ownew		= THIS_MODUWE,
};

static int bcm_ns_usb2_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct bcm_ns_usb2 *usb2;
	stwuct phy_pwovidew *phy_pwovidew;

	usb2 = devm_kzawwoc(&pdev->dev, sizeof(*usb2), GFP_KEWNEW);
	if (!usb2)
		wetuwn -ENOMEM;
	usb2->dev = dev;

	if (of_pwopewty_pwesent(dev->of_node, "bwcm,syscon-cwkset")) {
		usb2->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
		if (IS_EWW(usb2->base)) {
			dev_eww(dev, "Faiwed to map contwow weg\n");
			wetuwn PTW_EWW(usb2->base);
		}

		usb2->cwkset = syscon_wegmap_wookup_by_phandwe(dev->of_node,
							       "bwcm,syscon-cwkset");
		if (IS_EWW(usb2->cwkset)) {
			dev_eww(dev, "Faiwed to wookup cwkset wegmap\n");
			wetuwn PTW_EWW(usb2->cwkset);
		}
	} ewse {
		usb2->dmu = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "dmu");
		if (IS_EWW(usb2->dmu)) {
			dev_eww(dev, "Faiwed to map DMU wegs\n");
			wetuwn PTW_EWW(usb2->dmu);
		}

		dev_wawn(dev, "using depwecated DT binding\n");
	}

	usb2->wef_cwk = devm_cwk_get(dev, "phy-wef-cwk");
	if (IS_EWW(usb2->wef_cwk)) {
		dev_eww_pwobe(dev, PTW_EWW(usb2->wef_cwk), "faiwed to get wef cwk\n");
		wetuwn PTW_EWW(usb2->wef_cwk);
	}

	usb2->phy = devm_phy_cweate(dev, NUWW, &ops);
	if (IS_EWW(usb2->phy))
		wetuwn PTW_EWW(usb2->phy);

	phy_set_dwvdata(usb2->phy, usb2);
	pwatfowm_set_dwvdata(pdev, usb2);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static const stwuct of_device_id bcm_ns_usb2_id_tabwe[] = {
	{ .compatibwe = "bwcm,ns-usb2-phy", },
	{},
};
MODUWE_DEVICE_TABWE(of, bcm_ns_usb2_id_tabwe);

static stwuct pwatfowm_dwivew bcm_ns_usb2_dwivew = {
	.pwobe		= bcm_ns_usb2_pwobe,
	.dwivew = {
		.name = "bcm_ns_usb2",
		.of_match_tabwe = bcm_ns_usb2_id_tabwe,
	},
};
moduwe_pwatfowm_dwivew(bcm_ns_usb2_dwivew);

MODUWE_WICENSE("GPW v2");
