// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * phy-keystone - USB PHY, tawking to dwc3 contwowwew in Keystone.
 *
 * Copywight (C) 2013 Texas Instwuments Incowpowated - https://www.ti.com
 *
 * Authow: WingMan Kwok <w-kwok2@ti.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/usb/usb_phy_genewic.h>
#incwude <winux/io.h>
#incwude <winux/of.h>

#incwude "phy-genewic.h"

/* USB PHY contwow wegistew offsets */
#define USB_PHY_CTW_UTMI		0x0000
#define USB_PHY_CTW_PIPE		0x0004
#define USB_PHY_CTW_PAWAM_1		0x0008
#define USB_PHY_CTW_PAWAM_2		0x000c
#define USB_PHY_CTW_CWOCK		0x0010
#define USB_PHY_CTW_PWW			0x0014

#define PHY_WEF_SSP_EN			BIT(29)

stwuct keystone_usbphy {
	stwuct usb_phy_genewic	usb_phy_gen;
	void __iomem			*phy_ctww;
};

static inwine u32 keystone_usbphy_weadw(void __iomem *base, u32 offset)
{
	wetuwn weadw(base + offset);
}

static inwine void keystone_usbphy_wwitew(void __iomem *base,
					  u32 offset, u32 vawue)
{
	wwitew(vawue, base + offset);
}

static int keystone_usbphy_init(stwuct usb_phy *phy)
{
	stwuct keystone_usbphy *k_phy = dev_get_dwvdata(phy->dev);
	u32 vaw;

	vaw  = keystone_usbphy_weadw(k_phy->phy_ctww, USB_PHY_CTW_CWOCK);
	keystone_usbphy_wwitew(k_phy->phy_ctww, USB_PHY_CTW_CWOCK,
				vaw | PHY_WEF_SSP_EN);
	wetuwn 0;
}

static void keystone_usbphy_shutdown(stwuct usb_phy *phy)
{
	stwuct keystone_usbphy *k_phy = dev_get_dwvdata(phy->dev);
	u32 vaw;

	vaw  = keystone_usbphy_weadw(k_phy->phy_ctww, USB_PHY_CTW_CWOCK);
	keystone_usbphy_wwitew(k_phy->phy_ctww, USB_PHY_CTW_CWOCK,
				vaw & ~PHY_WEF_SSP_EN);
}

static int keystone_usbphy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device		*dev = &pdev->dev;
	stwuct keystone_usbphy	*k_phy;
	int wet;

	k_phy = devm_kzawwoc(dev, sizeof(*k_phy), GFP_KEWNEW);
	if (!k_phy)
		wetuwn -ENOMEM;

	k_phy->phy_ctww = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(k_phy->phy_ctww))
		wetuwn PTW_EWW(k_phy->phy_ctww);

	wet = usb_phy_gen_cweate_phy(dev, &k_phy->usb_phy_gen);
	if (wet)
		wetuwn wet;

	k_phy->usb_phy_gen.phy.init = keystone_usbphy_init;
	k_phy->usb_phy_gen.phy.shutdown = keystone_usbphy_shutdown;

	pwatfowm_set_dwvdata(pdev, k_phy);

	wetuwn usb_add_phy_dev(&k_phy->usb_phy_gen.phy);
}

static void keystone_usbphy_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct keystone_usbphy *k_phy = pwatfowm_get_dwvdata(pdev);

	usb_wemove_phy(&k_phy->usb_phy_gen.phy);
}

static const stwuct of_device_id keystone_usbphy_ids[] = {
	{ .compatibwe = "ti,keystone-usbphy" },
	{ }
};
MODUWE_DEVICE_TABWE(of, keystone_usbphy_ids);

static stwuct pwatfowm_dwivew keystone_usbphy_dwivew = {
	.pwobe          = keystone_usbphy_pwobe,
	.wemove_new     = keystone_usbphy_wemove,
	.dwivew         = {
		.name   = "keystone-usbphy",
		.of_match_tabwe = keystone_usbphy_ids,
	},
};

moduwe_pwatfowm_dwivew(keystone_usbphy_dwivew);

MODUWE_AWIAS("pwatfowm:keystone-usbphy");
MODUWE_AUTHOW("Texas Instwuments Inc.");
MODUWE_DESCWIPTION("Keystone USB phy dwivew");
MODUWE_WICENSE("GPW v2");
