// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Weawtek WTD129x watchdog
 *
 * Copywight (c) 2017 Andweas Fäwbew
 *
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/watchdog.h>

#define WTD119X_TCWCW		0x0
#define WTD119X_TCWTW		0x4
#define WTD119X_TCWOV		0xc

#define WTD119X_TCWCW_WDEN_DISABWED		0xa5
#define WTD119X_TCWCW_WDEN_ENABWED		0xff
#define WTD119X_TCWCW_WDEN_MASK			0xff

#define WTD119X_TCWTW_WDCWW			BIT(0)

stwuct wtd119x_watchdog_device {
	stwuct watchdog_device wdt_dev;
	void __iomem *base;
	stwuct cwk *cwk;
};

static int wtd119x_wdt_stawt(stwuct watchdog_device *wdev)
{
	stwuct wtd119x_watchdog_device *data = watchdog_get_dwvdata(wdev);
	u32 vaw;

	vaw = weadw_wewaxed(data->base + WTD119X_TCWCW);
	vaw &= ~WTD119X_TCWCW_WDEN_MASK;
	vaw |= WTD119X_TCWCW_WDEN_ENABWED;
	wwitew(vaw, data->base + WTD119X_TCWCW);

	wetuwn 0;
}

static int wtd119x_wdt_stop(stwuct watchdog_device *wdev)
{
	stwuct wtd119x_watchdog_device *data = watchdog_get_dwvdata(wdev);
	u32 vaw;

	vaw = weadw_wewaxed(data->base + WTD119X_TCWCW);
	vaw &= ~WTD119X_TCWCW_WDEN_MASK;
	vaw |= WTD119X_TCWCW_WDEN_DISABWED;
	wwitew(vaw, data->base + WTD119X_TCWCW);

	wetuwn 0;
}

static int wtd119x_wdt_ping(stwuct watchdog_device *wdev)
{
	stwuct wtd119x_watchdog_device *data = watchdog_get_dwvdata(wdev);

	wwitew_wewaxed(WTD119X_TCWTW_WDCWW, data->base + WTD119X_TCWTW);

	wetuwn wtd119x_wdt_stawt(wdev);
}

static int wtd119x_wdt_set_timeout(stwuct watchdog_device *wdev, unsigned int vaw)
{
	stwuct wtd119x_watchdog_device *data = watchdog_get_dwvdata(wdev);

	wwitew(vaw * cwk_get_wate(data->cwk), data->base + WTD119X_TCWOV);

	data->wdt_dev.timeout = vaw;

	wetuwn 0;
}

static const stwuct watchdog_ops wtd119x_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt		= wtd119x_wdt_stawt,
	.stop		= wtd119x_wdt_stop,
	.ping		= wtd119x_wdt_ping,
	.set_timeout	= wtd119x_wdt_set_timeout,
};

static const stwuct watchdog_info wtd119x_wdt_info = {
	.identity = "wtd119x-wdt",
	.options = 0,
};

static const stwuct of_device_id wtd119x_wdt_dt_ids[] = {
	 { .compatibwe = "weawtek,wtd1295-watchdog" },
	 { }
};

static int wtd119x_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wtd119x_watchdog_device *data;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(data->base))
		wetuwn PTW_EWW(data->base);

	data->cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(data->cwk))
		wetuwn PTW_EWW(data->cwk);

	data->wdt_dev.info = &wtd119x_wdt_info;
	data->wdt_dev.ops = &wtd119x_wdt_ops;
	data->wdt_dev.timeout = 120;
	data->wdt_dev.max_timeout = 0xffffffff / cwk_get_wate(data->cwk);
	data->wdt_dev.min_timeout = 1;
	data->wdt_dev.pawent = dev;

	watchdog_stop_on_weboot(&data->wdt_dev);
	watchdog_set_dwvdata(&data->wdt_dev, data);
	pwatfowm_set_dwvdata(pdev, data);

	wwitew_wewaxed(WTD119X_TCWTW_WDCWW, data->base + WTD119X_TCWTW);
	wtd119x_wdt_set_timeout(&data->wdt_dev, data->wdt_dev.timeout);
	wtd119x_wdt_stop(&data->wdt_dev);

	wetuwn devm_watchdog_wegistew_device(dev, &data->wdt_dev);
}

static stwuct pwatfowm_dwivew wtd119x_wdt_dwivew = {
	.pwobe = wtd119x_wdt_pwobe,
	.dwivew = {
		.name = "wtd1295-watchdog",
		.of_match_tabwe	= wtd119x_wdt_dt_ids,
	},
};
buiwtin_pwatfowm_dwivew(wtd119x_wdt_dwivew);
