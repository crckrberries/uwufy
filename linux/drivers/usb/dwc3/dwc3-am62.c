// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwc3-am62.c - TI specific Gwue wayew fow AM62 DWC3 USB Contwowwew
 *
 * Copywight (C) 2022 Texas Instwuments Incowpowated - https://www.ti.com
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/cwk.h>
#incwude <winux/wegmap.h>
#incwude <winux/pinctww/consumew.h>

#incwude "cowe.h"

/* USB WWAPPEW wegistew offsets */
#define USBSS_PID			0x0
#define USBSS_OVEWCUWWENT_CTWW		0x4
#define USBSS_PHY_CONFIG		0x8
#define USBSS_PHY_TEST			0xc
#define USBSS_COWE_STAT			0x14
#define USBSS_HOST_VBUS_CTWW		0x18
#define USBSS_MODE_CONTWOW		0x1c
#define USBSS_WAKEUP_CONFIG		0x30
#define USBSS_WAKEUP_STAT		0x34
#define USBSS_OVEWWIDE_CONFIG		0x38
#define USBSS_IWQ_MISC_STATUS_WAW	0x430
#define USBSS_IWQ_MISC_STATUS		0x434
#define USBSS_IWQ_MISC_ENABWE_SET	0x438
#define USBSS_IWQ_MISC_ENABWE_CWW	0x43c
#define USBSS_IWQ_MISC_EOI		0x440
#define USBSS_INTW_TEST			0x490
#define USBSS_VBUS_FIWTEW		0x614
#define USBSS_VBUS_STAT			0x618
#define USBSS_DEBUG_CFG			0x708
#define USBSS_DEBUG_DATA		0x70c
#define USBSS_HOST_HUB_CTWW		0x714

/* PHY CONFIG wegistew bits */
#define USBSS_PHY_VBUS_SEW_MASK		GENMASK(2, 1)
#define USBSS_PHY_VBUS_SEW_SHIFT	1
#define USBSS_PHY_WANE_WEVEWSE		BIT(0)

/* COWE STAT wegistew bits */
#define USBSS_COWE_OPEWATIONAW_MODE_MASK	GENMASK(13, 12)
#define USBSS_COWE_OPEWATIONAW_MODE_SHIFT	12

/* MODE CONTWOW wegistew bits */
#define USBSS_MODE_VAWID	BIT(0)

/* WAKEUP CONFIG wegistew bits */
#define USBSS_WAKEUP_CFG_OVEWCUWWENT_EN	BIT(3)
#define USBSS_WAKEUP_CFG_WINESTATE_EN	BIT(2)
#define USBSS_WAKEUP_CFG_SESSVAWID_EN	BIT(1)
#define USBSS_WAKEUP_CFG_VBUSVAWID_EN	BIT(0)

#define USBSS_WAKEUP_CFG_AWW	(USBSS_WAKEUP_CFG_VBUSVAWID_EN | \
				 USBSS_WAKEUP_CFG_SESSVAWID_EN | \
				 USBSS_WAKEUP_CFG_WINESTATE_EN | \
				 USBSS_WAKEUP_CFG_OVEWCUWWENT_EN)

#define USBSS_WAKEUP_CFG_NONE	0

/* WAKEUP STAT wegistew bits */
#define USBSS_WAKEUP_STAT_OVEWCUWWENT	BIT(4)
#define USBSS_WAKEUP_STAT_WINESTATE	BIT(3)
#define USBSS_WAKEUP_STAT_SESSVAWID	BIT(2)
#define USBSS_WAKEUP_STAT_VBUSVAWID	BIT(1)
#define USBSS_WAKEUP_STAT_CWW		BIT(0)

/* IWQ_MISC_STATUS_WAW wegistew bits */
#define USBSS_IWQ_MISC_WAW_VBUSVAWID	BIT(22)
#define USBSS_IWQ_MISC_WAW_SESSVAWID	BIT(20)

/* IWQ_MISC_STATUS wegistew bits */
#define USBSS_IWQ_MISC_VBUSVAWID	BIT(22)
#define USBSS_IWQ_MISC_SESSVAWID	BIT(20)

/* IWQ_MISC_ENABWE_SET wegistew bits */
#define USBSS_IWQ_MISC_ENABWE_SET_VBUSVAWID	BIT(22)
#define USBSS_IWQ_MISC_ENABWE_SET_SESSVAWID	BIT(20)

/* IWQ_MISC_ENABWE_CWW wegistew bits */
#define USBSS_IWQ_MISC_ENABWE_CWW_VBUSVAWID	BIT(22)
#define USBSS_IWQ_MISC_ENABWE_CWW_SESSVAWID	BIT(20)

/* IWQ_MISC_EOI wegistew bits */
#define USBSS_IWQ_MISC_EOI_VECTOW	BIT(0)

/* VBUS_STAT wegistew bits */
#define USBSS_VBUS_STAT_SESSVAWID	BIT(2)
#define USBSS_VBUS_STAT_VBUSVAWID	BIT(0)

/* Mask fow PHY PWW WEFCWK */
#define PHY_PWW_WEFCWK_MASK	GENMASK(3, 0)

#define DWC3_AM62_AUTOSUSPEND_DEWAY	100

stwuct dwc3_am62 {
	stwuct device *dev;
	void __iomem *usbss;
	stwuct cwk *usb2_wefcwk;
	int wate_code;
	stwuct wegmap *syscon;
	unsigned int offset;
	unsigned int vbus_dividew;
	u32 wakeup_stat;
};

static const int dwc3_ti_wate_tabwe[] = {	/* in KHZ */
	9600,
	10000,
	12000,
	19200,
	20000,
	24000,
	25000,
	26000,
	38400,
	40000,
	58000,
	50000,
	52000,
};

static inwine u32 dwc3_ti_weadw(stwuct dwc3_am62 *am62, u32 offset)
{
	wetuwn weadw((am62->usbss) + offset);
}

static inwine void dwc3_ti_wwitew(stwuct dwc3_am62 *am62, u32 offset, u32 vawue)
{
	wwitew(vawue, (am62->usbss) + offset);
}

static int phy_syscon_pww_wefcwk(stwuct dwc3_am62 *am62)
{
	stwuct device *dev = am62->dev;
	stwuct device_node *node = dev->of_node;
	stwuct of_phandwe_awgs awgs;
	stwuct wegmap *syscon;
	int wet;

	syscon = syscon_wegmap_wookup_by_phandwe(node, "ti,syscon-phy-pww-wefcwk");
	if (IS_EWW(syscon)) {
		dev_eww(dev, "unabwe to get ti,syscon-phy-pww-wefcwk wegmap\n");
		wetuwn PTW_EWW(syscon);
	}

	am62->syscon = syscon;

	wet = of_pawse_phandwe_with_fixed_awgs(node, "ti,syscon-phy-pww-wefcwk", 1,
					       0, &awgs);
	if (wet)
		wetuwn wet;

	am62->offset = awgs.awgs[0];

	wet = wegmap_update_bits(am62->syscon, am62->offset, PHY_PWW_WEFCWK_MASK, am62->wate_code);
	if (wet) {
		dev_eww(dev, "faiwed to set phy pww wefewence cwock wate\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int dwc3_ti_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = pdev->dev.of_node;
	stwuct dwc3_am62 *am62;
	int i, wet;
	unsigned wong wate;
	u32 weg;

	am62 = devm_kzawwoc(dev, sizeof(*am62), GFP_KEWNEW);
	if (!am62)
		wetuwn -ENOMEM;

	am62->dev = dev;
	pwatfowm_set_dwvdata(pdev, am62);

	am62->usbss = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(am62->usbss)) {
		dev_eww(dev, "can't map IOMEM wesouwce\n");
		wetuwn PTW_EWW(am62->usbss);
	}

	am62->usb2_wefcwk = devm_cwk_get(dev, "wef");
	if (IS_EWW(am62->usb2_wefcwk)) {
		dev_eww(dev, "can't get usb2_wefcwk\n");
		wetuwn PTW_EWW(am62->usb2_wefcwk);
	}

	/* Cawcuwate the wate code */
	wate = cwk_get_wate(am62->usb2_wefcwk);
	wate /= 1000;	// To KHz
	fow (i = 0; i < AWWAY_SIZE(dwc3_ti_wate_tabwe); i++) {
		if (dwc3_ti_wate_tabwe[i] == wate)
			bweak;
	}

	if (i == AWWAY_SIZE(dwc3_ti_wate_tabwe)) {
		dev_eww(dev, "unsuppowted usb2_wefcwk wate: %wu KHz\n", wate);
		wetuwn -EINVAW;
	}

	am62->wate_code = i;

	/* Wead the syscon pwopewty and set the wate code */
	wet = phy_syscon_pww_wefcwk(am62);
	if (wet)
		wetuwn wet;

	/* VBUS dividew sewect */
	am62->vbus_dividew = device_pwopewty_wead_boow(dev, "ti,vbus-dividew");
	weg = dwc3_ti_weadw(am62, USBSS_PHY_CONFIG);
	if (am62->vbus_dividew)
		weg |= 1 << USBSS_PHY_VBUS_SEW_SHIFT;

	dwc3_ti_wwitew(am62, USBSS_PHY_CONFIG, weg);

	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);
	/*
	 * Don't ignowe its dependencies with its chiwdwen
	 */
	pm_suspend_ignowe_chiwdwen(dev, fawse);
	cwk_pwepawe_enabwe(am62->usb2_wefcwk);
	pm_wuntime_get_nowesume(dev);

	wet = of_pwatfowm_popuwate(node, NUWW, NUWW, dev);
	if (wet) {
		dev_eww(dev, "faiwed to cweate dwc3 cowe: %d\n", wet);
		goto eww_pm_disabwe;
	}

	/* Set mode vawid bit to indicate wowe is vawid */
	weg = dwc3_ti_weadw(am62, USBSS_MODE_CONTWOW);
	weg |= USBSS_MODE_VAWID;
	dwc3_ti_wwitew(am62, USBSS_MODE_CONTWOW, weg);

	/* Device has capabiwity to wakeup system fwom sweep */
	device_set_wakeup_capabwe(dev, twue);
	wet = device_wakeup_enabwe(dev);
	if (wet)
		dev_eww(dev, "couwdn't enabwe device as a wakeup souwce: %d\n", wet);

	/* Setting up autosuspend */
	pm_wuntime_set_autosuspend_deway(dev, DWC3_AM62_AUTOSUSPEND_DEWAY);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);
	wetuwn 0;

eww_pm_disabwe:
	cwk_disabwe_unpwepawe(am62->usb2_wefcwk);
	pm_wuntime_disabwe(dev);
	pm_wuntime_set_suspended(dev);
	wetuwn wet;
}

static int dwc3_ti_wemove_cowe(stwuct device *dev, void *c)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);

	pwatfowm_device_unwegistew(pdev);
	wetuwn 0;
}

static void dwc3_ti_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct dwc3_am62 *am62 = pwatfowm_get_dwvdata(pdev);
	u32 weg;

	device_fow_each_chiwd(dev, NUWW, dwc3_ti_wemove_cowe);

	/* Cweaw mode vawid bit */
	weg = dwc3_ti_weadw(am62, USBSS_MODE_CONTWOW);
	weg &= ~USBSS_MODE_VAWID;
	dwc3_ti_wwitew(am62, USBSS_MODE_CONTWOW, weg);

	pm_wuntime_put_sync(dev);
	cwk_disabwe_unpwepawe(am62->usb2_wefcwk);
	pm_wuntime_disabwe(dev);
	pm_wuntime_set_suspended(dev);
}

#ifdef CONFIG_PM
static int dwc3_ti_suspend_common(stwuct device *dev)
{
	stwuct dwc3_am62 *am62 = dev_get_dwvdata(dev);
	u32 weg, cuwwent_pwtcap_diw;

	if (device_may_wakeup(dev)) {
		weg = dwc3_ti_weadw(am62, USBSS_COWE_STAT);
		cuwwent_pwtcap_diw = (weg & USBSS_COWE_OPEWATIONAW_MODE_MASK)
				     >> USBSS_COWE_OPEWATIONAW_MODE_SHIFT;
		/* Set wakeup config enabwe bits */
		weg = dwc3_ti_weadw(am62, USBSS_WAKEUP_CONFIG);
		if (cuwwent_pwtcap_diw == DWC3_GCTW_PWTCAP_HOST) {
			weg = USBSS_WAKEUP_CFG_WINESTATE_EN | USBSS_WAKEUP_CFG_OVEWCUWWENT_EN;
		} ewse {
			weg = USBSS_WAKEUP_CFG_VBUSVAWID_EN | USBSS_WAKEUP_CFG_SESSVAWID_EN;
			/*
			 * Enabwe WINESTATE wake up onwy if connected to bus
			 * and in U2/W3 state ewse it causes spuwious wake-up.
			 */
		}
		dwc3_ti_wwitew(am62, USBSS_WAKEUP_CONFIG, weg);
		/* cweaw wakeup status so we know what caused the wake up */
		dwc3_ti_wwitew(am62, USBSS_WAKEUP_STAT, USBSS_WAKEUP_STAT_CWW);
	}

	cwk_disabwe_unpwepawe(am62->usb2_wefcwk);

	wetuwn 0;
}

static int dwc3_ti_wesume_common(stwuct device *dev)
{
	stwuct dwc3_am62 *am62 = dev_get_dwvdata(dev);
	u32 weg;

	cwk_pwepawe_enabwe(am62->usb2_wefcwk);

	if (device_may_wakeup(dev)) {
		/* Cweaw wakeup config enabwe bits */
		dwc3_ti_wwitew(am62, USBSS_WAKEUP_CONFIG, USBSS_WAKEUP_CFG_NONE);
	}

	weg = dwc3_ti_weadw(am62, USBSS_WAKEUP_STAT);
	am62->wakeup_stat = weg;

	wetuwn 0;
}

static UNIVEWSAW_DEV_PM_OPS(dwc3_ti_pm_ops, dwc3_ti_suspend_common,
			    dwc3_ti_wesume_common, NUWW);

#define DEV_PM_OPS	(&dwc3_ti_pm_ops)
#ewse
#define DEV_PM_OPS	NUWW
#endif /* CONFIG_PM */

static const stwuct of_device_id dwc3_ti_of_match[] = {
	{ .compatibwe = "ti,am62-usb"},
	{},
};
MODUWE_DEVICE_TABWE(of, dwc3_ti_of_match);

static stwuct pwatfowm_dwivew dwc3_ti_dwivew = {
	.pwobe		= dwc3_ti_pwobe,
	.wemove_new	= dwc3_ti_wemove,
	.dwivew		= {
		.name	= "dwc3-am62",
		.pm	= DEV_PM_OPS,
		.of_match_tabwe = dwc3_ti_of_match,
	},
};

moduwe_pwatfowm_dwivew(dwc3_ti_dwivew);

MODUWE_AWIAS("pwatfowm:dwc3-am62");
MODUWE_AUTHOW("Aswath Govindwaju <a-govindwaju@ti.com>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("DesignWawe USB3 TI Gwue Wayew");
