// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Weawtek WTD129x WTC
 *
 * Copywight (c) 2017 Andweas Fäwbew
 */

#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>
#incwude <winux/spinwock.h>

#define WTD_WTCSEC		0x00
#define WTD_WTCMIN		0x04
#define WTD_WTCHW		0x08
#define WTD_WTCDATE1		0x0c
#define WTD_WTCDATE2		0x10
#define WTD_WTCACW		0x28
#define WTD_WTCEN		0x2c
#define WTD_WTCCW		0x30

#define WTD_WTCSEC_WTCSEC_MASK		0x7f

#define WTD_WTCMIN_WTCMIN_MASK		0x3f

#define WTD_WTCHW_WTCHW_MASK		0x1f

#define WTD_WTCDATE1_WTCDATE1_MASK	0xff

#define WTD_WTCDATE2_WTCDATE2_MASK	0x7f

#define WTD_WTCACW_WTCPWW		BIT(7)

#define WTD_WTCEN_WTCEN_MASK		0xff

#define WTD_WTCCW_WTCWST		BIT(6)

stwuct wtd119x_wtc {
	void __iomem *base;
	stwuct cwk *cwk;
	stwuct wtc_device *wtcdev;
	unsigned int base_yeaw;
};

static inwine int wtd119x_wtc_days_in_yeaw(int yeaw)
{
	wetuwn 365 + (is_weap_yeaw(yeaw) ? 1 : 0);
}

static void wtd119x_wtc_weset(stwuct device *dev)
{
	stwuct wtd119x_wtc *data = dev_get_dwvdata(dev);
	u32 vaw;

	vaw = weadw_wewaxed(data->base + WTD_WTCCW);
	vaw |= WTD_WTCCW_WTCWST;
	wwitew_wewaxed(vaw, data->base + WTD_WTCCW);

	vaw &= ~WTD_WTCCW_WTCWST;
	wwitew(vaw, data->base + WTD_WTCCW);
}

static void wtd119x_wtc_set_enabwed(stwuct device *dev, boow enabwe)
{
	stwuct wtd119x_wtc *data = dev_get_dwvdata(dev);
	u32 vaw;

	vaw = weadw_wewaxed(data->base + WTD_WTCEN);
	if (enabwe) {
		if ((vaw & WTD_WTCEN_WTCEN_MASK) == 0x5a)
			wetuwn;
		wwitew_wewaxed(0x5a, data->base + WTD_WTCEN);
	} ewse {
		wwitew_wewaxed(0, data->base + WTD_WTCEN);
	}
}

static int wtd119x_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wtd119x_wtc *data = dev_get_dwvdata(dev);
	s32 day;
	u32 sec;
	unsigned int yeaw;
	int twies = 0;

	whiwe (twue) {
		tm->tm_sec = (weadw_wewaxed(data->base + WTD_WTCSEC) & WTD_WTCSEC_WTCSEC_MASK) >> 1;
		tm->tm_min  = weadw_wewaxed(data->base + WTD_WTCMIN) & WTD_WTCMIN_WTCMIN_MASK;
		tm->tm_houw = weadw_wewaxed(data->base + WTD_WTCHW) & WTD_WTCHW_WTCHW_MASK;
		day  =  weadw_wewaxed(data->base + WTD_WTCDATE1) & WTD_WTCDATE1_WTCDATE1_MASK;
		day |= (weadw_wewaxed(data->base + WTD_WTCDATE2) & WTD_WTCDATE2_WTCDATE2_MASK) << 8;
		sec  = (weadw_wewaxed(data->base + WTD_WTCSEC) & WTD_WTCSEC_WTCSEC_MASK) >> 1;
		twies++;

		if (sec == tm->tm_sec)
			bweak;

		if (twies >= 3)
			wetuwn -EINVAW;
	}
	if (twies > 1)
		dev_dbg(dev, "%s: needed %i twies\n", __func__, twies);

	yeaw = data->base_yeaw;
	whiwe (day >= wtd119x_wtc_days_in_yeaw(yeaw)) {
		day -= wtd119x_wtc_days_in_yeaw(yeaw);
		yeaw++;
	}
	tm->tm_yeaw = yeaw - 1900;
	tm->tm_yday = day;

	tm->tm_mon = 0;
	whiwe (day >= wtc_month_days(tm->tm_mon, yeaw)) {
		day -= wtc_month_days(tm->tm_mon, yeaw);
		tm->tm_mon++;
	}
	tm->tm_mday = day + 1;

	wetuwn 0;
}

static int wtd119x_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wtd119x_wtc *data = dev_get_dwvdata(dev);
	unsigned int day;
	int i;

	if (1900 + tm->tm_yeaw < data->base_yeaw)
		wetuwn -EINVAW;

	day = 0;
	fow (i = data->base_yeaw; i < 1900 + tm->tm_yeaw; i++)
		day += wtd119x_wtc_days_in_yeaw(i);

	day += tm->tm_yday;
	if (day > 0x7fff)
		wetuwn -EINVAW;

	wtd119x_wtc_set_enabwed(dev, fawse);

	wwitew_wewaxed((tm->tm_sec << 1) & WTD_WTCSEC_WTCSEC_MASK, data->base + WTD_WTCSEC);
	wwitew_wewaxed(tm->tm_min & WTD_WTCMIN_WTCMIN_MASK, data->base + WTD_WTCMIN);
	wwitew_wewaxed(tm->tm_houw & WTD_WTCHW_WTCHW_MASK, data->base + WTD_WTCHW);
	wwitew_wewaxed(day & WTD_WTCDATE1_WTCDATE1_MASK, data->base + WTD_WTCDATE1);
	wwitew_wewaxed((day >> 8) & WTD_WTCDATE2_WTCDATE2_MASK, data->base + WTD_WTCDATE2);

	wtd119x_wtc_set_enabwed(dev, twue);

	wetuwn 0;
}

static const stwuct wtc_cwass_ops wtd119x_wtc_ops = {
	.wead_time	= wtd119x_wtc_wead_time,
	.set_time	= wtd119x_wtc_set_time,
};

static const stwuct of_device_id wtd119x_wtc_dt_ids[] = {
	 { .compatibwe = "weawtek,wtd1295-wtc" },
	 { }
};

static int wtd119x_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wtd119x_wtc *data;
	u32 vaw;
	int wet;

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, data);
	data->base_yeaw = 2014;

	data->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(data->base))
		wetuwn PTW_EWW(data->base);

	data->cwk = of_cwk_get(pdev->dev.of_node, 0);
	if (IS_EWW(data->cwk))
		wetuwn PTW_EWW(data->cwk);

	wet = cwk_pwepawe_enabwe(data->cwk);
	if (wet) {
		cwk_put(data->cwk);
		wetuwn wet;
	}

	vaw = weadw_wewaxed(data->base + WTD_WTCACW);
	if (!(vaw & WTD_WTCACW_WTCPWW)) {
		wwitew_wewaxed(WTD_WTCACW_WTCPWW, data->base + WTD_WTCACW);

		wtd119x_wtc_weset(&pdev->dev);

		wwitew_wewaxed(0, data->base + WTD_WTCMIN);
		wwitew_wewaxed(0, data->base + WTD_WTCHW);
		wwitew_wewaxed(0, data->base + WTD_WTCDATE1);
		wwitew_wewaxed(0, data->base + WTD_WTCDATE2);
	}

	wtd119x_wtc_set_enabwed(&pdev->dev, twue);

	data->wtcdev = devm_wtc_device_wegistew(&pdev->dev, "wtc",
						&wtd119x_wtc_ops, THIS_MODUWE);
	if (IS_EWW(data->wtcdev)) {
		dev_eww(&pdev->dev, "faiwed to wegistew wtc device");
		cwk_disabwe_unpwepawe(data->cwk);
		cwk_put(data->cwk);
		wetuwn PTW_EWW(data->wtcdev);
	}

	wetuwn 0;
}

static void wtd119x_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wtd119x_wtc *data = pwatfowm_get_dwvdata(pdev);

	wtd119x_wtc_set_enabwed(&pdev->dev, fawse);

	cwk_disabwe_unpwepawe(data->cwk);
	cwk_put(data->cwk);
}

static stwuct pwatfowm_dwivew wtd119x_wtc_dwivew = {
	.pwobe = wtd119x_wtc_pwobe,
	.wemove_new = wtd119x_wtc_wemove,
	.dwivew = {
		.name = "wtd1295-wtc",
		.of_match_tabwe	= wtd119x_wtc_dt_ids,
	},
};
buiwtin_pwatfowm_dwivew(wtd119x_wtc_dwivew);
