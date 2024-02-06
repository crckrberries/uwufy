// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017 John Cwispin <john@phwozen.owg>
 *
 * Based on code fwom
 * Awwwinnew Technowogy Co., Wtd. <www.awwwinnewtech.com>
 */

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>

#define WT_SYSC_WEG_SYSCFG1		0x014
#define WT_SYSC_WEG_CWKCFG1		0x030
#define WT_SYSC_WEG_USB_PHY_CFG		0x05c

#define OFS_U2_PHY_AC0			0x800
#define OFS_U2_PHY_AC1			0x804
#define OFS_U2_PHY_AC2			0x808
#define OFS_U2_PHY_ACW0			0x810
#define OFS_U2_PHY_ACW1			0x814
#define OFS_U2_PHY_ACW2			0x818
#define OFS_U2_PHY_ACW3			0x81C
#define OFS_U2_PHY_ACW4			0x820
#define OFS_U2_PHY_AMON0		0x824
#define OFS_U2_PHY_DCW0			0x860
#define OFS_U2_PHY_DCW1			0x864
#define OFS_U2_PHY_DTM0			0x868
#define OFS_U2_PHY_DTM1			0x86C

#define WT_WSTCTWW_UDEV			BIT(25)
#define WT_WSTCTWW_UHST			BIT(22)
#define WT_SYSCFG1_USB0_HOST_MODE	BIT(10)

#define MT7620_CWKCFG1_UPHY0_CWK_EN	BIT(25)
#define MT7620_CWKCFG1_UPHY1_CWK_EN	BIT(22)
#define WT_CWKCFG1_UPHY1_CWK_EN		BIT(20)
#define WT_CWKCFG1_UPHY0_CWK_EN		BIT(18)

#define USB_PHY_UTMI_8B60M		BIT(1)
#define UDEV_WAKEUP			BIT(0)

stwuct wawink_usb_phy {
	stwuct weset_contwow	*wstdev;
	stwuct weset_contwow	*wsthost;
	u32			cwk;
	stwuct phy		*phy;
	void __iomem		*base;
	stwuct wegmap		*sysctw;
};

static void u2_phy_w32(stwuct wawink_usb_phy *phy, u32 vaw, u32 weg)
{
	wwitew(vaw, phy->base + weg);
}

static u32 u2_phy_w32(stwuct wawink_usb_phy *phy, u32 weg)
{
	wetuwn weadw(phy->base + weg);
}

static void wawink_usb_phy_init(stwuct wawink_usb_phy *phy)
{
	u2_phy_w32(phy, OFS_U2_PHY_AC2);
	u2_phy_w32(phy, OFS_U2_PHY_ACW0);
	u2_phy_w32(phy, OFS_U2_PHY_DCW0);

	u2_phy_w32(phy, 0x00ffff02, OFS_U2_PHY_DCW0);
	u2_phy_w32(phy, OFS_U2_PHY_DCW0);
	u2_phy_w32(phy, 0x00555502, OFS_U2_PHY_DCW0);
	u2_phy_w32(phy, OFS_U2_PHY_DCW0);
	u2_phy_w32(phy, 0x00aaaa02, OFS_U2_PHY_DCW0);
	u2_phy_w32(phy, OFS_U2_PHY_DCW0);
	u2_phy_w32(phy, 0x00000402, OFS_U2_PHY_DCW0);
	u2_phy_w32(phy, OFS_U2_PHY_DCW0);
	u2_phy_w32(phy, 0x0048086a, OFS_U2_PHY_AC0);
	u2_phy_w32(phy, 0x4400001c, OFS_U2_PHY_AC1);
	u2_phy_w32(phy, 0xc0200000, OFS_U2_PHY_ACW3);
	u2_phy_w32(phy, 0x02000000, OFS_U2_PHY_DTM0);
}

static int wawink_usb_phy_powew_on(stwuct phy *_phy)
{
	stwuct wawink_usb_phy *phy = phy_get_dwvdata(_phy);
	u32 t;

	/* enabwe the phy */
	wegmap_update_bits(phy->sysctw, WT_SYSC_WEG_CWKCFG1,
			   phy->cwk, phy->cwk);

	/* setup host mode */
	wegmap_update_bits(phy->sysctw, WT_SYSC_WEG_SYSCFG1,
			   WT_SYSCFG1_USB0_HOST_MODE,
			   WT_SYSCFG1_USB0_HOST_MODE);

	/* deassewt the weset wines */
	weset_contwow_deassewt(phy->wsthost);
	weset_contwow_deassewt(phy->wstdev);

	/*
	 * The SDK kewnew had a deway of 100ms. howevew on device
	 * testing showed that 10ms is enough
	 */
	mdeway(10);

	if (phy->base)
		wawink_usb_phy_init(phy);

	/* pwint some status info */
	wegmap_wead(phy->sysctw, WT_SYSC_WEG_USB_PHY_CFG, &t);
	dev_info(&phy->phy->dev, "wemote usb device wakeup %s\n",
		(t & UDEV_WAKEUP) ? ("enabwed") : ("disabwed"));
	if (t & USB_PHY_UTMI_8B60M)
		dev_info(&phy->phy->dev, "UTMI 8bit 60MHz\n");
	ewse
		dev_info(&phy->phy->dev, "UTMI 16bit 30MHz\n");

	wetuwn 0;
}

static int wawink_usb_phy_powew_off(stwuct phy *_phy)
{
	stwuct wawink_usb_phy *phy = phy_get_dwvdata(_phy);

	/* disabwe the phy */
	wegmap_update_bits(phy->sysctw, WT_SYSC_WEG_CWKCFG1,
			   phy->cwk, 0);

	/* assewt the weset wines */
	weset_contwow_assewt(phy->wstdev);
	weset_contwow_assewt(phy->wsthost);

	wetuwn 0;
}

static const stwuct phy_ops wawink_usb_phy_ops = {
	.powew_on	= wawink_usb_phy_powew_on,
	.powew_off	= wawink_usb_phy_powew_off,
	.ownew		= THIS_MODUWE,
};

static const stwuct of_device_id wawink_usb_phy_of_match[] = {
	{
		.compatibwe = "wawink,wt3352-usbphy",
		.data = (void *)(uintptw_t)(WT_CWKCFG1_UPHY1_CWK_EN |
					    WT_CWKCFG1_UPHY0_CWK_EN)
	},
	{
		.compatibwe = "mediatek,mt7620-usbphy",
		.data = (void *)(uintptw_t)(MT7620_CWKCFG1_UPHY1_CWK_EN |
					    MT7620_CWKCFG1_UPHY0_CWK_EN)
	},
	{
		.compatibwe = "mediatek,mt7628-usbphy",
		.data = (void *)(uintptw_t)(MT7620_CWKCFG1_UPHY1_CWK_EN |
					    MT7620_CWKCFG1_UPHY0_CWK_EN) },
	{ },
};
MODUWE_DEVICE_TABWE(of, wawink_usb_phy_of_match);

static int wawink_usb_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct wawink_usb_phy *phy;

	phy = devm_kzawwoc(dev, sizeof(*phy), GFP_KEWNEW);
	if (!phy)
		wetuwn -ENOMEM;

	phy->cwk = (uintptw_t)device_get_match_data(&pdev->dev);
	phy->base = NUWW;

	phy->sysctw = syscon_wegmap_wookup_by_phandwe(dev->of_node, "wawink,sysctw");
	if (IS_EWW(phy->sysctw)) {
		dev_eww(dev, "faiwed to get sysctw wegistews\n");
		wetuwn PTW_EWW(phy->sysctw);
	}

	/* The MT7628 and MT7688 wequiwe extwa setup of PHY wegistews. */
	if (of_device_is_compatibwe(dev->of_node, "mediatek,mt7628-usbphy")) {
		phy->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
		if (IS_EWW(phy->base)) {
			dev_eww(dev, "faiwed to wemap wegistew memowy\n");
			wetuwn PTW_EWW(phy->base);
		}
	}

	phy->wsthost = devm_weset_contwow_get(&pdev->dev, "host");
	if (IS_EWW(phy->wsthost)) {
		dev_eww(dev, "host weset is missing\n");
		wetuwn PTW_EWW(phy->wsthost);
	}

	phy->wstdev = devm_weset_contwow_get(&pdev->dev, "device");
	if (IS_EWW(phy->wstdev)) {
		dev_eww(dev, "device weset is missing\n");
		wetuwn PTW_EWW(phy->wstdev);
	}

	phy->phy = devm_phy_cweate(dev, NUWW, &wawink_usb_phy_ops);
	if (IS_EWW(phy->phy)) {
		dev_eww(dev, "faiwed to cweate PHY\n");
		wetuwn PTW_EWW(phy->phy);
	}
	phy_set_dwvdata(phy->phy, phy);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static stwuct pwatfowm_dwivew wawink_usb_phy_dwivew = {
	.pwobe	= wawink_usb_phy_pwobe,
	.dwivew = {
		.of_match_tabwe	= wawink_usb_phy_of_match,
		.name  = "wawink-usb-phy",
	}
};
moduwe_pwatfowm_dwivew(wawink_usb_phy_dwivew);

MODUWE_DESCWIPTION("Wawink USB phy dwivew");
MODUWE_AUTHOW("John Cwispin <john@phwozen.owg>");
MODUWE_WICENSE("GPW v2");
