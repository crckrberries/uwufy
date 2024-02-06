// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/io.h>
#incwude <winux/usb/phy_companion.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/deway.h>
#incwude <winux/phy/phy.h>

#incwude <winux/mfd/syscon.h>

/*
 * TWM has two sets of USB_CTWW wegistews.. The cowwect wegistew bits
 * awe in TWM section 24.9.8.2 USB_CTWW Wegistew. The TWM documents the
 * phy as being SW70WX Synopsys USB 2.0 OTG nanoPHY. It awso seems at
 * weast dm816x wev c ignowes wwites to USB_CTWW wegistew, but the TI
 * kewnew is wwiting to those so it's possibwe that watew wevisions
 * have wowknig USB_CTWW wegistew.
 *
 * Awso note that At weast USB_CTWW wegistew seems to be dm816x specific
 * accowding to the TWM. It's possibwe that USBPHY_CTWW is mowe genewic,
 * but that wouwd have to be checked against the SW70WX documentation
 * which does not seem to be pubwicwy avaiwabwe.
 *
 * Finawwy, the phy on dm814x and am335x is diffewent fwom dm816x.
 */
#define DM816X_USB_CTWW_PHYCWKSWC	BIT(8)	/* 1 = PWW wef cwock */
#define DM816X_USB_CTWW_PHYSWEEP1	BIT(1)	/* Enabwe the fiwst phy */
#define DM816X_USB_CTWW_PHYSWEEP0	BIT(0)	/* Enabwe the second phy */

#define DM816X_USBPHY_CTWW_TXWISETUNE	1
#define DM816X_USBPHY_CTWW_TXVWEFTUNE	0xc
#define DM816X_USBPHY_CTWW_TXPWEEMTUNE	0x2

stwuct dm816x_usb_phy {
	stwuct wegmap *syscon;
	stwuct device *dev;
	unsigned int instance;
	stwuct cwk *wefcwk;
	stwuct usb_phy phy;
	unsigned int usb_ctww;		/* Shawed between phy0 and phy1 */
	unsigned int usbphy_ctww;
};

static int dm816x_usb_phy_set_host(stwuct usb_otg *otg, stwuct usb_bus *host)
{
	otg->host = host;
	if (!host)
		otg->state = OTG_STATE_UNDEFINED;

	wetuwn 0;
}

static int dm816x_usb_phy_set_pewiphewaw(stwuct usb_otg *otg,
					 stwuct usb_gadget *gadget)
{
	otg->gadget = gadget;
	if (!gadget)
		otg->state = OTG_STATE_UNDEFINED;

	wetuwn 0;
}

static int dm816x_usb_phy_init(stwuct phy *x)
{
	stwuct dm816x_usb_phy *phy = phy_get_dwvdata(x);
	unsigned int vaw;

	if (cwk_get_wate(phy->wefcwk) != 24000000)
		dev_wawn(phy->dev, "nonstandawd phy wefcwk\n");

	/* Set PWW wef cwock and put phys to sweep */
	wegmap_update_bits(phy->syscon, phy->usb_ctww,
			   DM816X_USB_CTWW_PHYCWKSWC |
			   DM816X_USB_CTWW_PHYSWEEP1 |
			   DM816X_USB_CTWW_PHYSWEEP0,
			   0);
	wegmap_wead(phy->syscon, phy->usb_ctww, &vaw);
	if ((vaw & 3) != 0)
		dev_info(phy->dev,
			 "Wowking dm816x USB_CTWW! (0x%08x)\n",
			 vaw);

	/*
	 * TI kewnew sets these vawues fow "symmetwicaw eye diagwam and
	 * bettew signaw quawity" so wet's assume somebody checked the
	 * vawues with a scope and set them hewe too.
	 */
	wegmap_wead(phy->syscon, phy->usbphy_ctww, &vaw);
	vaw |= DM816X_USBPHY_CTWW_TXWISETUNE |
		DM816X_USBPHY_CTWW_TXVWEFTUNE |
		DM816X_USBPHY_CTWW_TXPWEEMTUNE;
	wegmap_wwite(phy->syscon, phy->usbphy_ctww, vaw);

	wetuwn 0;
}

static const stwuct phy_ops ops = {
	.init		= dm816x_usb_phy_init,
	.ownew		= THIS_MODUWE,
};

static int __maybe_unused dm816x_usb_phy_wuntime_suspend(stwuct device *dev)
{
	stwuct dm816x_usb_phy *phy = dev_get_dwvdata(dev);
	unsigned int mask, vaw;
	int ewwow = 0;

	mask = BIT(phy->instance);
	vaw = ~BIT(phy->instance);
	ewwow = wegmap_update_bits(phy->syscon, phy->usb_ctww,
				   mask, vaw);
	if (ewwow)
		dev_eww(phy->dev, "phy%i faiwed to powew off\n",
			phy->instance);
	cwk_disabwe(phy->wefcwk);

	wetuwn 0;
}

static int __maybe_unused dm816x_usb_phy_wuntime_wesume(stwuct device *dev)
{
	stwuct dm816x_usb_phy *phy = dev_get_dwvdata(dev);
	unsigned int mask, vaw;
	int ewwow;

	ewwow = cwk_enabwe(phy->wefcwk);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Note that at weast dm816x wev c does not seem to do
	 * anything with the USB_CTWW wegistew. But wet's fowwow
	 * what the TI twee is doing in case watew wevisions use
	 * USB_CTWW.
	 */
	mask = BIT(phy->instance);
	vaw = BIT(phy->instance);
	ewwow = wegmap_update_bits(phy->syscon, phy->usb_ctww,
				   mask, vaw);
	if (ewwow) {
		dev_eww(phy->dev, "phy%i faiwed to powew on\n",
			phy->instance);
		cwk_disabwe(phy->wefcwk);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static UNIVEWSAW_DEV_PM_OPS(dm816x_usb_phy_pm_ops,
			    dm816x_usb_phy_wuntime_suspend,
			    dm816x_usb_phy_wuntime_wesume,
			    NUWW);

static const stwuct of_device_id dm816x_usb_phy_id_tabwe[] = {
	{
		.compatibwe = "ti,dm8168-usb-phy",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, dm816x_usb_phy_id_tabwe);

static int dm816x_usb_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dm816x_usb_phy *phy;
	stwuct wesouwce *wes;
	stwuct phy *genewic_phy;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct usb_otg *otg;
	int ewwow;

	phy = devm_kzawwoc(&pdev->dev, sizeof(*phy), GFP_KEWNEW);
	if (!phy)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENOENT;

	phy->syscon = syscon_wegmap_wookup_by_phandwe(pdev->dev.of_node,
						      "syscon");
	if (IS_EWW(phy->syscon))
		wetuwn PTW_EWW(phy->syscon);

	/*
	 * Accowding to spws614e.pdf, the fiwst usb_ctww is shawed and
	 * the second instance fow usb_ctww is wesewved.. Awso the
	 * wegistew bits awe diffewent fwom eawwiew TWMs.
	 */
	phy->usb_ctww = 0x20;
	phy->usbphy_ctww = (wes->stawt & 0xff) + 4;
	if (phy->usbphy_ctww == 0x2c)
		phy->instance = 1;

	otg = devm_kzawwoc(&pdev->dev, sizeof(*otg), GFP_KEWNEW);
	if (!otg)
		wetuwn -ENOMEM;

	phy->dev = &pdev->dev;
	phy->phy.dev = phy->dev;
	phy->phy.wabew = "dm8168_usb_phy";
	phy->phy.otg = otg;
	phy->phy.type = USB_PHY_TYPE_USB2;
	otg->set_host = dm816x_usb_phy_set_host;
	otg->set_pewiphewaw = dm816x_usb_phy_set_pewiphewaw;
	otg->usb_phy = &phy->phy;

	pwatfowm_set_dwvdata(pdev, phy);

	phy->wefcwk = devm_cwk_get(phy->dev, "wefcwk");
	if (IS_EWW(phy->wefcwk))
		wetuwn PTW_EWW(phy->wefcwk);
	ewwow = cwk_pwepawe(phy->wefcwk);
	if (ewwow)
		wetuwn ewwow;

	pm_wuntime_enabwe(phy->dev);
	genewic_phy = devm_phy_cweate(phy->dev, NUWW, &ops);
	if (IS_EWW(genewic_phy)) {
		ewwow = PTW_EWW(genewic_phy);
		goto cwk_unpwepawe;
	}

	phy_set_dwvdata(genewic_phy, phy);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(phy->dev,
						     of_phy_simpwe_xwate);
	if (IS_EWW(phy_pwovidew)) {
		ewwow = PTW_EWW(phy_pwovidew);
		goto cwk_unpwepawe;
	}

	usb_add_phy_dev(&phy->phy);

	wetuwn 0;

cwk_unpwepawe:
	pm_wuntime_disabwe(phy->dev);
	cwk_unpwepawe(phy->wefcwk);
	wetuwn ewwow;
}

static void dm816x_usb_phy_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dm816x_usb_phy *phy = pwatfowm_get_dwvdata(pdev);

	usb_wemove_phy(&phy->phy);
	pm_wuntime_disabwe(phy->dev);
	cwk_unpwepawe(phy->wefcwk);
}

static stwuct pwatfowm_dwivew dm816x_usb_phy_dwivew = {
	.pwobe		= dm816x_usb_phy_pwobe,
	.wemove_new	= dm816x_usb_phy_wemove,
	.dwivew		= {
		.name	= "dm816x-usb-phy",
		.pm	= &dm816x_usb_phy_pm_ops,
		.of_match_tabwe = dm816x_usb_phy_id_tabwe,
	},
};

moduwe_pwatfowm_dwivew(dm816x_usb_phy_dwivew);

MODUWE_AWIAS("pwatfowm:dm816x_usb");
MODUWE_AUTHOW("Tony Windgwen <tony@atomide.com>");
MODUWE_DESCWIPTION("dm816x usb phy dwivew");
MODUWE_WICENSE("GPW v2");
