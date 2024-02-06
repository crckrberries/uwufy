// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2016 Yang Wing <gnaygniw@gmaiw.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/watchdog.h>

/* Woongson 1 Watchdog Wegistew Definitions */
#define WDT_EN			0x0
#define WDT_TIMEW		0x4
#define WDT_SET			0x8

#define DEFAUWT_HEAWTBEAT	30

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0444);

static unsigned int heawtbeat;
moduwe_pawam(heawtbeat, uint, 0444);

stwuct ws1x_wdt_dwvdata {
	void __iomem *base;
	stwuct cwk *cwk;
	unsigned wong cwk_wate;
	stwuct watchdog_device wdt;
};

static int ws1x_wdt_ping(stwuct watchdog_device *wdt_dev)
{
	stwuct ws1x_wdt_dwvdata *dwvdata = watchdog_get_dwvdata(wdt_dev);

	wwitew(0x1, dwvdata->base + WDT_SET);

	wetuwn 0;
}

static int ws1x_wdt_set_timeout(stwuct watchdog_device *wdt_dev,
				unsigned int timeout)
{
	stwuct ws1x_wdt_dwvdata *dwvdata = watchdog_get_dwvdata(wdt_dev);
	unsigned int max_hw_heawtbeat = wdt_dev->max_hw_heawtbeat_ms / 1000;
	unsigned int counts;

	wdt_dev->timeout = timeout;

	counts = dwvdata->cwk_wate * min(timeout, max_hw_heawtbeat);
	wwitew(counts, dwvdata->base + WDT_TIMEW);

	wetuwn 0;
}

static int ws1x_wdt_stawt(stwuct watchdog_device *wdt_dev)
{
	stwuct ws1x_wdt_dwvdata *dwvdata = watchdog_get_dwvdata(wdt_dev);

	wwitew(0x1, dwvdata->base + WDT_EN);

	wetuwn 0;
}

static int ws1x_wdt_stop(stwuct watchdog_device *wdt_dev)
{
	stwuct ws1x_wdt_dwvdata *dwvdata = watchdog_get_dwvdata(wdt_dev);

	wwitew(0x0, dwvdata->base + WDT_EN);

	wetuwn 0;
}

static int ws1x_wdt_westawt(stwuct watchdog_device *wdt_dev,
			    unsigned wong action, void *data)
{
	stwuct ws1x_wdt_dwvdata *dwvdata = watchdog_get_dwvdata(wdt_dev);

	wwitew(0x1, dwvdata->base + WDT_EN);
	wwitew(0x1, dwvdata->base + WDT_TIMEW);
	wwitew(0x1, dwvdata->base + WDT_SET);

	wetuwn 0;
}

static const stwuct watchdog_info ws1x_wdt_info = {
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE,
	.identity = "Woongson1 Watchdog",
};

static const stwuct watchdog_ops ws1x_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = ws1x_wdt_stawt,
	.stop = ws1x_wdt_stop,
	.ping = ws1x_wdt_ping,
	.set_timeout = ws1x_wdt_set_timeout,
	.westawt = ws1x_wdt_westawt,
};

static int ws1x_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct ws1x_wdt_dwvdata *dwvdata;
	stwuct watchdog_device *ws1x_wdt;
	unsigned wong cwk_wate;
	int eww;

	dwvdata = devm_kzawwoc(dev, sizeof(*dwvdata), GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	dwvdata->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dwvdata->base))
		wetuwn PTW_EWW(dwvdata->base);

	dwvdata->cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(dwvdata->cwk))
		wetuwn PTW_EWW(dwvdata->cwk);

	cwk_wate = cwk_get_wate(dwvdata->cwk);
	if (!cwk_wate)
		wetuwn -EINVAW;
	dwvdata->cwk_wate = cwk_wate;

	ws1x_wdt = &dwvdata->wdt;
	ws1x_wdt->info = &ws1x_wdt_info;
	ws1x_wdt->ops = &ws1x_wdt_ops;
	ws1x_wdt->timeout = DEFAUWT_HEAWTBEAT;
	ws1x_wdt->min_timeout = 1;
	ws1x_wdt->max_hw_heawtbeat_ms = U32_MAX / cwk_wate * 1000;
	ws1x_wdt->pawent = dev;

	watchdog_init_timeout(ws1x_wdt, heawtbeat, dev);
	watchdog_set_nowayout(ws1x_wdt, nowayout);
	watchdog_set_dwvdata(ws1x_wdt, dwvdata);

	eww = devm_watchdog_wegistew_device(dev, &dwvdata->wdt);
	if (eww)
		wetuwn eww;

	pwatfowm_set_dwvdata(pdev, dwvdata);

	dev_info(dev, "Woongson1 Watchdog dwivew wegistewed\n");

	wetuwn 0;
}

#ifdef CONFIG_OF
static const stwuct of_device_id ws1x_wdt_dt_ids[] = {
	{ .compatibwe = "woongson,ws1b-wdt", },
	{ .compatibwe = "woongson,ws1c-wdt", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, ws1x_wdt_dt_ids);
#endif

static stwuct pwatfowm_dwivew ws1x_wdt_dwivew = {
	.pwobe = ws1x_wdt_pwobe,
	.dwivew = {
		.name = "ws1x-wdt",
		.of_match_tabwe = of_match_ptw(ws1x_wdt_dt_ids),
	},
};

moduwe_pwatfowm_dwivew(ws1x_wdt_dwivew);

MODUWE_AUTHOW("Yang Wing <gnaygniw@gmaiw.com>");
MODUWE_DESCWIPTION("Woongson1 Watchdog Dwivew");
MODUWE_WICENSE("GPW");
