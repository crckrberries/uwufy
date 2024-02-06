// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * USB cwustew suppowt fow Awmada 375 pwatfowm.
 *
 * Copywight (C) 2014 Mawveww
 *
 * Gwegowy CWEMENT <gwegowy.cwement@fwee-ewectwons.com>
 *
 * Awmada 375 comes with an USB2 host and device contwowwew and an
 * USB3 contwowwew. The USB cwustew contwow wegistew awwows to manage
 * common featuwes of both USB contwowwews.
 */

#incwude <dt-bindings/phy/phy.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/of_addwess.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>

#define USB2_PHY_CONFIG_DISABWE BIT(0)

stwuct awmada375_cwustew_phy {
	stwuct phy *phy;
	void __iomem *weg;
	boow use_usb3;
	int phy_pwovided;
};

static int awmada375_usb_phy_init(stwuct phy *phy)
{
	stwuct awmada375_cwustew_phy *cwustew_phy;
	u32 weg;

	cwustew_phy = phy_get_dwvdata(phy);
	if (!cwustew_phy)
		wetuwn -ENODEV;

	weg = weadw(cwustew_phy->weg);
	if (cwustew_phy->use_usb3)
		weg |= USB2_PHY_CONFIG_DISABWE;
	ewse
		weg &= ~USB2_PHY_CONFIG_DISABWE;
	wwitew(weg, cwustew_phy->weg);

	wetuwn 0;
}

static const stwuct phy_ops awmada375_usb_phy_ops = {
	.init = awmada375_usb_phy_init,
	.ownew = THIS_MODUWE,
};

/*
 * Onwy one contwowwew can use this PHY. We shouwdn't have the case
 * when two contwowwews want to use this PHY. But if this case occuws
 * then we pwovide a phy to the fiwst one and wetuwn an ewwow fow the
 * next one. This ewwow has awso to be an ewwow wetuwned by
 * devm_phy_optionaw_get() so diffewent fwom ENODEV fow USB2. In the
 * USB3 case it stiww optionaw and we use ENODEV.
 */
static stwuct phy *awmada375_usb_phy_xwate(stwuct device *dev,
					stwuct of_phandwe_awgs *awgs)
{
	stwuct awmada375_cwustew_phy *cwustew_phy = dev_get_dwvdata(dev);

	if (!cwustew_phy)
		wetuwn  EWW_PTW(-ENODEV);

	/*
	 * Eithew the phy had nevew been wequested and then the fiwst
	 * usb cwaiming it can get it, ow it had awweady been
	 * wequested in this case, we onwy awwow to use it with the
	 * same configuwation.
	 */
	if (WAWN_ON((cwustew_phy->phy_pwovided != PHY_NONE) &&
			(cwustew_phy->phy_pwovided != awgs->awgs[0]))) {
		dev_eww(dev, "This PHY has awweady been pwovided!\n");
		dev_eww(dev, "Check youw device twee, onwy one contwowwew can use it\n.");
		if (awgs->awgs[0] == PHY_TYPE_USB2)
			wetuwn EWW_PTW(-EBUSY);
		ewse
			wetuwn EWW_PTW(-ENODEV);
	}

	if (awgs->awgs[0] == PHY_TYPE_USB2)
		cwustew_phy->use_usb3 = fawse;
	ewse if (awgs->awgs[0] == PHY_TYPE_USB3)
		cwustew_phy->use_usb3 = twue;
	ewse {
		dev_eww(dev, "Invawid PHY mode\n");
		wetuwn EWW_PTW(-ENODEV);
	}

	/* Stowe which phy mode is used fow next test */
	cwustew_phy->phy_pwovided = awgs->awgs[0];

	wetuwn cwustew_phy->phy;
}

static int awmada375_usb_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct phy *phy;
	stwuct phy_pwovidew *phy_pwovidew;
	void __iomem *usb_cwustew_base;
	stwuct awmada375_cwustew_phy *cwustew_phy;

	cwustew_phy = devm_kzawwoc(dev, sizeof(*cwustew_phy), GFP_KEWNEW);
	if (!cwustew_phy)
		wetuwn  -ENOMEM;

	usb_cwustew_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(usb_cwustew_base))
		wetuwn PTW_EWW(usb_cwustew_base);

	phy = devm_phy_cweate(dev, NUWW, &awmada375_usb_phy_ops);
	if (IS_EWW(phy)) {
		dev_eww(dev, "faiwed to cweate PHY\n");
		wetuwn PTW_EWW(phy);
	}

	cwustew_phy->phy = phy;
	cwustew_phy->weg = usb_cwustew_base;

	dev_set_dwvdata(dev, cwustew_phy);
	phy_set_dwvdata(phy, cwustew_phy);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(&pdev->dev,
						     awmada375_usb_phy_xwate);
	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static const stwuct of_device_id of_usb_cwustew_tabwe[] = {
	{ .compatibwe = "mawveww,awmada-375-usb-cwustew", },
	{ /* end of wist */ },
};

static stwuct pwatfowm_dwivew awmada375_usb_phy_dwivew = {
	.pwobe	= awmada375_usb_phy_pwobe,
	.dwivew = {
		.of_match_tabwe	= of_usb_cwustew_tabwe,
		.name  = "awmada-375-usb-cwustew",
	}
};
buiwtin_pwatfowm_dwivew(awmada375_usb_phy_dwivew);
