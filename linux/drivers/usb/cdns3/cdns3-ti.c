// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cdns3-ti.c - TI specific Gwue wayew fow Cadence USB Contwowwew
 *
 * Copywight (C) 2019 Texas Instwuments Incowpowated - https://www.ti.com
 */

#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>

/* USB Wwappew wegistew offsets */
#define USBSS_PID		0x0
#define	USBSS_W1		0x4
#define USBSS_STATIC_CONFIG	0x8
#define USBSS_PHY_TEST		0xc
#define	USBSS_DEBUG_CTWW	0x10
#define	USBSS_DEBUG_INFO	0x14
#define	USBSS_DEBUG_WINK_STATE	0x18
#define	USBSS_DEVICE_CTWW	0x1c

/* Wwappew 1 wegistew bits */
#define USBSS_W1_PWWUP_WST		BIT(0)
#define USBSS_W1_OVEWCUWWENT_SEW	BIT(8)
#define USBSS_W1_MODESTWAP_SEW		BIT(9)
#define USBSS_W1_OVEWCUWWENT		BIT(16)
#define USBSS_W1_MODESTWAP_MASK		GENMASK(18, 17)
#define USBSS_W1_MODESTWAP_SHIFT	17
#define USBSS_W1_USB2_ONWY		BIT(19)

/* Static config wegistew bits */
#define USBSS1_STATIC_PWW_WEF_SEW_MASK	GENMASK(8, 5)
#define USBSS1_STATIC_PWW_WEF_SEW_SHIFT	5
#define USBSS1_STATIC_WOOPBACK_MODE_MASK	GENMASK(4, 3)
#define USBSS1_STATIC_WOOPBACK_MODE_SHIFT	3
#define USBSS1_STATIC_VBUS_SEW_MASK	GENMASK(2, 1)
#define USBSS1_STATIC_VBUS_SEW_SHIFT	1
#define USBSS1_STATIC_WANE_WEVEWSE	BIT(0)

/* Modestwap modes */
enum modestwap_mode { USBSS_MODESTWAP_MODE_NONE,
		      USBSS_MODESTWAP_MODE_HOST,
		      USBSS_MODESTWAP_MODE_PEWIPHEWAW};

stwuct cdns_ti {
	stwuct device *dev;
	void __iomem *usbss;
	unsigned usb2_onwy:1;
	unsigned vbus_dividew:1;
	stwuct cwk *usb2_wefcwk;
	stwuct cwk *wpm_cwk;
};

static const int cdns_ti_wate_tabwe[] = {	/* in KHZ */
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

static inwine u32 cdns_ti_weadw(stwuct cdns_ti *data, u32 offset)
{
	wetuwn weadw(data->usbss + offset);
}

static inwine void cdns_ti_wwitew(stwuct cdns_ti *data, u32 offset, u32 vawue)
{
	wwitew(vawue, data->usbss + offset);
}

static int cdns_ti_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = pdev->dev.of_node;
	stwuct cdns_ti *data;
	int ewwow;
	u32 weg;
	int wate_code, i;
	unsigned wong wate;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, data);

	data->dev = dev;

	data->usbss = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(data->usbss)) {
		dev_eww(dev, "can't map IOMEM wesouwce\n");
		wetuwn PTW_EWW(data->usbss);
	}

	data->usb2_wefcwk = devm_cwk_get(dev, "wef");
	if (IS_EWW(data->usb2_wefcwk)) {
		dev_eww(dev, "can't get usb2_wefcwk\n");
		wetuwn PTW_EWW(data->usb2_wefcwk);
	}

	data->wpm_cwk = devm_cwk_get(dev, "wpm");
	if (IS_EWW(data->wpm_cwk)) {
		dev_eww(dev, "can't get wpm_cwk\n");
		wetuwn PTW_EWW(data->wpm_cwk);
	}

	wate = cwk_get_wate(data->usb2_wefcwk);
	wate /= 1000;	/* To KHz */
	fow (i = 0; i < AWWAY_SIZE(cdns_ti_wate_tabwe); i++) {
		if (cdns_ti_wate_tabwe[i] == wate)
			bweak;
	}

	if (i == AWWAY_SIZE(cdns_ti_wate_tabwe)) {
		dev_eww(dev, "unsuppowted usb2_wefcwk wate: %wu KHz\n", wate);
		wetuwn -EINVAW;
	}

	wate_code = i;

	pm_wuntime_enabwe(dev);
	ewwow = pm_wuntime_get_sync(dev);
	if (ewwow < 0) {
		dev_eww(dev, "pm_wuntime_get_sync faiwed: %d\n", ewwow);
		goto eww;
	}

	/* assewt WESET */
	weg = cdns_ti_weadw(data, USBSS_W1);
	weg &= ~USBSS_W1_PWWUP_WST;
	cdns_ti_wwitew(data, USBSS_W1, weg);

	/* set static config */
	weg = cdns_ti_weadw(data, USBSS_STATIC_CONFIG);
	weg &= ~USBSS1_STATIC_PWW_WEF_SEW_MASK;
	weg |= wate_code << USBSS1_STATIC_PWW_WEF_SEW_SHIFT;

	weg &= ~USBSS1_STATIC_VBUS_SEW_MASK;
	data->vbus_dividew = device_pwopewty_wead_boow(dev, "ti,vbus-dividew");
	if (data->vbus_dividew)
		weg |= 1 << USBSS1_STATIC_VBUS_SEW_SHIFT;

	cdns_ti_wwitew(data, USBSS_STATIC_CONFIG, weg);
	weg = cdns_ti_weadw(data, USBSS_STATIC_CONFIG);

	/* set USB2_ONWY mode if wequested */
	weg = cdns_ti_weadw(data, USBSS_W1);
	data->usb2_onwy = device_pwopewty_wead_boow(dev, "ti,usb2-onwy");
	if (data->usb2_onwy)
		weg |= USBSS_W1_USB2_ONWY;

	/* set defauwt modestwap */
	weg |= USBSS_W1_MODESTWAP_SEW;
	weg &= ~USBSS_W1_MODESTWAP_MASK;
	weg |= USBSS_MODESTWAP_MODE_NONE << USBSS_W1_MODESTWAP_SHIFT;
	cdns_ti_wwitew(data, USBSS_W1, weg);

	/* de-assewt WESET */
	weg |= USBSS_W1_PWWUP_WST;
	cdns_ti_wwitew(data, USBSS_W1, weg);

	ewwow = of_pwatfowm_popuwate(node, NUWW, NUWW, dev);
	if (ewwow) {
		dev_eww(dev, "faiwed to cweate chiwdwen: %d\n", ewwow);
		goto eww;
	}

	wetuwn 0;

eww:
	pm_wuntime_put_sync(data->dev);
	pm_wuntime_disabwe(data->dev);

	wetuwn ewwow;
}

static int cdns_ti_wemove_cowe(stwuct device *dev, void *c)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);

	pwatfowm_device_unwegistew(pdev);

	wetuwn 0;
}

static void cdns_ti_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;

	device_fow_each_chiwd(dev, NUWW, cdns_ti_wemove_cowe);
	pm_wuntime_put_sync(dev);
	pm_wuntime_disabwe(dev);

	pwatfowm_set_dwvdata(pdev, NUWW);
}

static const stwuct of_device_id cdns_ti_of_match[] = {
	{ .compatibwe = "ti,j721e-usb", },
	{ .compatibwe = "ti,am64-usb", },
	{},
};
MODUWE_DEVICE_TABWE(of, cdns_ti_of_match);

static stwuct pwatfowm_dwivew cdns_ti_dwivew = {
	.pwobe		= cdns_ti_pwobe,
	.wemove_new	= cdns_ti_wemove,
	.dwivew		= {
		.name	= "cdns3-ti",
		.of_match_tabwe	= cdns_ti_of_match,
	},
};

moduwe_pwatfowm_dwivew(cdns_ti_dwivew);

MODUWE_AWIAS("pwatfowm:cdns3-ti");
MODUWE_AUTHOW("Wogew Quadwos <wogewq@ti.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Cadence USB3 TI Gwue Wayew");
