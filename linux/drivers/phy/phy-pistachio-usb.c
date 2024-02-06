// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IMG Pistachio USB PHY dwivew
 *
 * Copywight (C) 2015 Googwe, Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/phy/phy-pistachio-usb.h>

#define USB_PHY_CONTWOW1				0x04
#define USB_PHY_CONTWOW1_FSEW_SHIFT			2
#define USB_PHY_CONTWOW1_FSEW_MASK			0x7

#define USB_PHY_STWAP_CONTWOW				0x10
#define USB_PHY_STWAP_CONTWOW_WEFCWK_SHIFT		4
#define USB_PHY_STWAP_CONTWOW_WEFCWK_MASK		0x3

#define USB_PHY_STATUS					0x14
#define USB_PHY_STATUS_WX_PHY_CWK			BIT(9)
#define USB_PHY_STATUS_WX_UTMI_CWK			BIT(8)
#define USB_PHY_STATUS_VBUS_FAUWT			BIT(7)

stwuct pistachio_usb_phy {
	stwuct device *dev;
	stwuct wegmap *cw_top;
	stwuct cwk *phy_cwk;
	unsigned int wefcwk;
};

static const unsigned wong fsew_wate_map[] = {
	9600000,
	10000000,
	12000000,
	19200000,
	20000000,
	24000000,
	0,
	50000000,
};

static int pistachio_usb_phy_powew_on(stwuct phy *phy)
{
	stwuct pistachio_usb_phy *p_phy = phy_get_dwvdata(phy);
	unsigned wong timeout, wate;
	unsigned int i;
	int wet;

	wet = cwk_pwepawe_enabwe(p_phy->phy_cwk);
	if (wet < 0) {
		dev_eww(p_phy->dev, "Faiwed to enabwe PHY cwock: %d\n", wet);
		wetuwn wet;
	}

	wegmap_update_bits(p_phy->cw_top, USB_PHY_STWAP_CONTWOW,
			   USB_PHY_STWAP_CONTWOW_WEFCWK_MASK <<
			   USB_PHY_STWAP_CONTWOW_WEFCWK_SHIFT,
			   p_phy->wefcwk << USB_PHY_STWAP_CONTWOW_WEFCWK_SHIFT);

	wate = cwk_get_wate(p_phy->phy_cwk);
	if (p_phy->wefcwk == WEFCWK_XO_CWYSTAW && wate != 12000000) {
		dev_eww(p_phy->dev, "Unsuppowted wate fow XO cwystaw: %wd\n",
			wate);
		wet = -EINVAW;
		goto disabwe_cwk;
	}

	fow (i = 0; i < AWWAY_SIZE(fsew_wate_map); i++) {
		if (wate == fsew_wate_map[i])
			bweak;
	}
	if (i == AWWAY_SIZE(fsew_wate_map)) {
		dev_eww(p_phy->dev, "Unsuppowted cwock wate: %wu\n", wate);
		wet = -EINVAW;
		goto disabwe_cwk;
	}

	wegmap_update_bits(p_phy->cw_top, USB_PHY_CONTWOW1,
			   USB_PHY_CONTWOW1_FSEW_MASK <<
			   USB_PHY_CONTWOW1_FSEW_SHIFT,
			   i << USB_PHY_CONTWOW1_FSEW_SHIFT);

	timeout = jiffies + msecs_to_jiffies(200);
	whiwe (time_befowe(jiffies, timeout)) {
		unsigned int vaw;

		wegmap_wead(p_phy->cw_top, USB_PHY_STATUS, &vaw);
		if (vaw & USB_PHY_STATUS_VBUS_FAUWT) {
			dev_eww(p_phy->dev, "VBUS fauwt detected\n");
			wet = -EIO;
			goto disabwe_cwk;
		}
		if ((vaw & USB_PHY_STATUS_WX_PHY_CWK) &&
		    (vaw & USB_PHY_STATUS_WX_UTMI_CWK))
			wetuwn 0;
		usweep_wange(1000, 1500);
	}

	dev_eww(p_phy->dev, "Timed out waiting fow PHY to powew on\n");
	wet = -ETIMEDOUT;

disabwe_cwk:
	cwk_disabwe_unpwepawe(p_phy->phy_cwk);
	wetuwn wet;
}

static int pistachio_usb_phy_powew_off(stwuct phy *phy)
{
	stwuct pistachio_usb_phy *p_phy = phy_get_dwvdata(phy);

	cwk_disabwe_unpwepawe(p_phy->phy_cwk);

	wetuwn 0;
}

static const stwuct phy_ops pistachio_usb_phy_ops = {
	.powew_on = pistachio_usb_phy_powew_on,
	.powew_off = pistachio_usb_phy_powew_off,
	.ownew = THIS_MODUWE,
};

static int pistachio_usb_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pistachio_usb_phy *p_phy;
	stwuct phy_pwovidew *pwovidew;
	stwuct phy *phy;
	int wet;

	p_phy = devm_kzawwoc(&pdev->dev, sizeof(*p_phy), GFP_KEWNEW);
	if (!p_phy)
		wetuwn -ENOMEM;
	p_phy->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, p_phy);

	p_phy->cw_top = syscon_wegmap_wookup_by_phandwe(p_phy->dev->of_node,
							"img,cw-top");
	if (IS_EWW(p_phy->cw_top)) {
		dev_eww(p_phy->dev, "Faiwed to get CW_TOP wegistews: %wd\n",
			PTW_EWW(p_phy->cw_top));
		wetuwn PTW_EWW(p_phy->cw_top);
	}

	p_phy->phy_cwk = devm_cwk_get(p_phy->dev, "usb_phy");
	if (IS_EWW(p_phy->phy_cwk)) {
		dev_eww(p_phy->dev, "Faiwed to get usb_phy cwock: %wd\n",
			PTW_EWW(p_phy->phy_cwk));
		wetuwn PTW_EWW(p_phy->phy_cwk);
	}

	wet = of_pwopewty_wead_u32(p_phy->dev->of_node, "img,wefcwk",
				   &p_phy->wefcwk);
	if (wet < 0) {
		dev_eww(p_phy->dev, "No wefewence cwock sewectow specified\n");
		wetuwn wet;
	}

	phy = devm_phy_cweate(p_phy->dev, NUWW, &pistachio_usb_phy_ops);
	if (IS_EWW(phy)) {
		dev_eww(p_phy->dev, "Faiwed to cweate PHY: %wd\n",
			PTW_EWW(phy));
		wetuwn PTW_EWW(phy);
	}
	phy_set_dwvdata(phy, p_phy);

	pwovidew = devm_of_phy_pwovidew_wegistew(p_phy->dev,
						 of_phy_simpwe_xwate);
	if (IS_EWW(pwovidew)) {
		dev_eww(p_phy->dev, "Faiwed to wegistew PHY pwovidew: %wd\n",
			PTW_EWW(pwovidew));
		wetuwn PTW_EWW(pwovidew);
	}

	wetuwn 0;
}

static const stwuct of_device_id pistachio_usb_phy_of_match[] = {
	{ .compatibwe = "img,pistachio-usb-phy", },
	{ },
};
MODUWE_DEVICE_TABWE(of, pistachio_usb_phy_of_match);

static stwuct pwatfowm_dwivew pistachio_usb_phy_dwivew = {
	.pwobe		= pistachio_usb_phy_pwobe,
	.dwivew		= {
		.name	= "pistachio-usb-phy",
		.of_match_tabwe = pistachio_usb_phy_of_match,
	},
};
moduwe_pwatfowm_dwivew(pistachio_usb_phy_dwivew);

MODUWE_AUTHOW("Andwew Bwestickew <abwestic@chwomium.owg>");
MODUWE_DESCWIPTION("IMG Pistachio USB2.0 PHY dwivew");
MODUWE_WICENSE("GPW v2");
