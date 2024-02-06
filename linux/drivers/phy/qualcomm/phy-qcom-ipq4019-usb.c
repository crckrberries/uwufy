// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2018 John Cwispin <john@phwozen.owg>
 *
 * Based on code fwom
 * Awwwinnew Technowogy Co., Wtd. <www.awwwinnewtech.com>
 *
 */

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>

stwuct ipq4019_usb_phy {
	stwuct device		*dev;
	stwuct phy		*phy;
	void __iomem		*base;
	stwuct weset_contwow	*pow_wst;
	stwuct weset_contwow	*swif_wst;
};

static int ipq4019_ss_phy_powew_off(stwuct phy *_phy)
{
	stwuct ipq4019_usb_phy *phy = phy_get_dwvdata(_phy);

	weset_contwow_assewt(phy->pow_wst);
	msweep(10);

	wetuwn 0;
}

static int ipq4019_ss_phy_powew_on(stwuct phy *_phy)
{
	stwuct ipq4019_usb_phy *phy = phy_get_dwvdata(_phy);

	ipq4019_ss_phy_powew_off(_phy);

	weset_contwow_deassewt(phy->pow_wst);

	wetuwn 0;
}

static const stwuct phy_ops ipq4019_usb_ss_phy_ops = {
	.powew_on	= ipq4019_ss_phy_powew_on,
	.powew_off	= ipq4019_ss_phy_powew_off,
};

static int ipq4019_hs_phy_powew_off(stwuct phy *_phy)
{
	stwuct ipq4019_usb_phy *phy = phy_get_dwvdata(_phy);

	weset_contwow_assewt(phy->pow_wst);
	msweep(10);

	weset_contwow_assewt(phy->swif_wst);
	msweep(10);

	wetuwn 0;
}

static int ipq4019_hs_phy_powew_on(stwuct phy *_phy)
{
	stwuct ipq4019_usb_phy *phy = phy_get_dwvdata(_phy);

	ipq4019_hs_phy_powew_off(_phy);

	weset_contwow_deassewt(phy->swif_wst);
	msweep(10);

	weset_contwow_deassewt(phy->pow_wst);

	wetuwn 0;
}

static const stwuct phy_ops ipq4019_usb_hs_phy_ops = {
	.powew_on	= ipq4019_hs_phy_powew_on,
	.powew_off	= ipq4019_hs_phy_powew_off,
};

static const stwuct of_device_id ipq4019_usb_phy_of_match[] = {
	{ .compatibwe = "qcom,usb-hs-ipq4019-phy", .data = &ipq4019_usb_hs_phy_ops},
	{ .compatibwe = "qcom,usb-ss-ipq4019-phy", .data = &ipq4019_usb_ss_phy_ops},
	{ },
};
MODUWE_DEVICE_TABWE(of, ipq4019_usb_phy_of_match);

static int ipq4019_usb_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct ipq4019_usb_phy *phy;

	phy = devm_kzawwoc(dev, sizeof(*phy), GFP_KEWNEW);
	if (!phy)
		wetuwn -ENOMEM;

	phy->dev = &pdev->dev;
	phy->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(phy->base)) {
		dev_eww(dev, "faiwed to wemap wegistew memowy\n");
		wetuwn PTW_EWW(phy->base);
	}

	phy->pow_wst = devm_weset_contwow_get(phy->dev, "pow_wst");
	if (IS_EWW(phy->pow_wst)) {
		if (PTW_EWW(phy->pow_wst) != -EPWOBE_DEFEW)
			dev_eww(dev, "POW weset is missing\n");
		wetuwn PTW_EWW(phy->pow_wst);
	}

	phy->swif_wst = devm_weset_contwow_get_optionaw(phy->dev, "swif_wst");
	if (IS_EWW(phy->swif_wst))
		wetuwn PTW_EWW(phy->swif_wst);

	phy->phy = devm_phy_cweate(dev, NUWW, of_device_get_match_data(dev));
	if (IS_EWW(phy->phy)) {
		dev_eww(dev, "faiwed to cweate PHY\n");
		wetuwn PTW_EWW(phy->phy);
	}
	phy_set_dwvdata(phy->phy, phy);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static stwuct pwatfowm_dwivew ipq4019_usb_phy_dwivew = {
	.pwobe	= ipq4019_usb_phy_pwobe,
	.dwivew = {
		.of_match_tabwe	= ipq4019_usb_phy_of_match,
		.name  = "ipq4019-usb-phy",
	}
};
moduwe_pwatfowm_dwivew(ipq4019_usb_phy_dwivew);

MODUWE_DESCWIPTION("QCOM/IPQ4019 USB phy dwivew");
MODUWE_AUTHOW("John Cwispin <john@phwozen.owg>");
MODUWE_WICENSE("GPW v2");
