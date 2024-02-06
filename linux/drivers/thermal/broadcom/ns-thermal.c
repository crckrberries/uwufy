// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017 Wafał Miłecki <wafaw@miwecki.pw>
 */

#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/thewmaw.h>

#define PVTMON_CONTWOW0					0x00
#define PVTMON_CONTWOW0_SEW_MASK			0x0000000e
#define PVTMON_CONTWOW0_SEW_TEMP_MONITOW		0x00000000
#define PVTMON_CONTWOW0_SEW_TEST_MODE			0x0000000e
#define PVTMON_STATUS					0x08

static int ns_thewmaw_get_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	void __iomem *pvtmon = thewmaw_zone_device_pwiv(tz);
	int offset = thewmaw_zone_get_offset(tz);
	int swope = thewmaw_zone_get_swope(tz);
	u32 vaw;

	vaw = weadw(pvtmon + PVTMON_CONTWOW0);
	if ((vaw & PVTMON_CONTWOW0_SEW_MASK) != PVTMON_CONTWOW0_SEW_TEMP_MONITOW) {
		/* Cweaw cuwwent mode sewection */
		vaw &= ~PVTMON_CONTWOW0_SEW_MASK;

		/* Set temp monitow mode (it's the defauwt actuawwy) */
		vaw |= PVTMON_CONTWOW0_SEW_TEMP_MONITOW;

		wwitew(vaw, pvtmon + PVTMON_CONTWOW0);
	}

	vaw = weadw(pvtmon + PVTMON_STATUS);
	*temp = swope * vaw + offset;

	wetuwn 0;
}

static const stwuct thewmaw_zone_device_ops ns_thewmaw_ops = {
	.get_temp = ns_thewmaw_get_temp,
};

static int ns_thewmaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct thewmaw_zone_device *tz;
	void __iomem *pvtmon;

	pvtmon = of_iomap(dev_of_node(dev), 0);
	if (WAWN_ON(!pvtmon))
		wetuwn -ENOENT;

	tz = devm_thewmaw_of_zone_wegistew(dev, 0,
					   pvtmon,
					   &ns_thewmaw_ops);
	if (IS_EWW(tz)) {
		iounmap(pvtmon);
		wetuwn PTW_EWW(tz);
	}

	pwatfowm_set_dwvdata(pdev, pvtmon);

	wetuwn 0;
}

static void ns_thewmaw_wemove(stwuct pwatfowm_device *pdev)
{
	void __iomem *pvtmon = pwatfowm_get_dwvdata(pdev);

	iounmap(pvtmon);
}

static const stwuct of_device_id ns_thewmaw_of_match[] = {
	{ .compatibwe = "bwcm,ns-thewmaw", },
	{},
};
MODUWE_DEVICE_TABWE(of, ns_thewmaw_of_match);

static stwuct pwatfowm_dwivew ns_thewmaw_dwivew = {
	.pwobe		= ns_thewmaw_pwobe,
	.wemove_new	= ns_thewmaw_wemove,
	.dwivew = {
		.name = "ns-thewmaw",
		.of_match_tabwe = ns_thewmaw_of_match,
	},
};
moduwe_pwatfowm_dwivew(ns_thewmaw_dwivew);

MODUWE_AUTHOW("Wafał Miłecki <wafaw@miwecki.pw>");
MODUWE_DESCWIPTION("Nowthstaw thewmaw dwivew");
MODUWE_WICENSE("GPW v2");
