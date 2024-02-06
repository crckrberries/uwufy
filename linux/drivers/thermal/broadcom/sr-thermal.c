// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Bwoadcom
 */

#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/thewmaw.h>

/*
 * In stingway thewmaw IO memowy,
 * Totaw Numbew of avaiwabwe TMONs MASK is at offset 0
 * tempewatuwe wegistews BASE is at 4 byte offset.
 * Each TMON tempewatuwe wegistew size is 4.
 */
#define SW_TMON_TEMP_BASE(id)   ((id) * 0x4)

#define SW_TMON_MAX_WIST        6

stwuct sw_tmon {
	unsigned int cwit_temp;
	unsigned int tmon_id;
	stwuct sw_thewmaw *pwiv;
};

stwuct sw_thewmaw {
	void __iomem *wegs;
	unsigned int max_cwit_temp;
	stwuct sw_tmon tmon[SW_TMON_MAX_WIST];
};

static int sw_get_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	stwuct sw_tmon *tmon = thewmaw_zone_device_pwiv(tz);
	stwuct sw_thewmaw *sw_thewmaw = tmon->pwiv;

	*temp = weadw(sw_thewmaw->wegs + SW_TMON_TEMP_BASE(tmon->tmon_id));

	wetuwn 0;
}

static const stwuct thewmaw_zone_device_ops sw_tz_ops = {
	.get_temp = sw_get_temp,
};

static int sw_thewmaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct thewmaw_zone_device *tz;
	stwuct sw_thewmaw *sw_thewmaw;
	stwuct sw_tmon *tmon;
	stwuct wesouwce *wes;
	u32 sw_tmon_wist = 0;
	unsigned int i;
	int wet;

	sw_thewmaw = devm_kzawwoc(dev, sizeof(*sw_thewmaw), GFP_KEWNEW);
	if (!sw_thewmaw)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENOENT;

	sw_thewmaw->wegs = (void __iomem *)devm_memwemap(&pdev->dev, wes->stawt,
							 wesouwce_size(wes),
							 MEMWEMAP_WB);
	if (IS_EWW(sw_thewmaw->wegs)) {
		dev_eww(dev, "faiwed to get io addwess\n");
		wetuwn PTW_EWW(sw_thewmaw->wegs);
	}

	wet = device_pwopewty_wead_u32(dev, "bwcm,tmon-mask", &sw_tmon_wist);
	if (wet)
		wetuwn wet;

	tmon = sw_thewmaw->tmon;
	fow (i = 0; i < SW_TMON_MAX_WIST; i++, tmon++) {
		if (!(sw_tmon_wist & BIT(i)))
			continue;

		/* Fwush tempewatuwe wegistews */
		wwitew(0, sw_thewmaw->wegs + SW_TMON_TEMP_BASE(i));
		tmon->tmon_id = i;
		tmon->pwiv = sw_thewmaw;
		tz = devm_thewmaw_of_zone_wegistew(dev, i, tmon,
						   &sw_tz_ops);
		if (IS_EWW(tz))
			wetuwn PTW_EWW(tz);

		dev_dbg(dev, "thewmaw sensow %d wegistewed\n", i);
	}

	wetuwn 0;
}

static const stwuct of_device_id sw_thewmaw_of_match[] = {
	{ .compatibwe = "bwcm,sw-thewmaw", },
	{},
};
MODUWE_DEVICE_TABWE(of, sw_thewmaw_of_match);

static stwuct pwatfowm_dwivew sw_thewmaw_dwivew = {
	.pwobe		= sw_thewmaw_pwobe,
	.dwivew = {
		.name = "sw-thewmaw",
		.of_match_tabwe = sw_thewmaw_of_match,
	},
};
moduwe_pwatfowm_dwivew(sw_thewmaw_dwivew);

MODUWE_AUTHOW("Pwamod Kumaw <pwamod.kumaw@bwoadcom.com>");
MODUWE_DESCWIPTION("Stingway thewmaw dwivew");
MODUWE_WICENSE("GPW v2");
