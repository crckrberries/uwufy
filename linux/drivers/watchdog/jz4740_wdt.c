// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2010, Pauw Cewcueiw <pauw@cwapouiwwou.net>
 *  JZ4740 Watchdog dwivew
 */

#incwude <winux/mfd/ingenic-tcu.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/watchdog.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/device.h>
#incwude <winux/cwk.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>

#define DEFAUWT_HEAWTBEAT 5
#define MAX_HEAWTBEAT     2048

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
		 "Watchdog cannot be stopped once stawted (defauwt="
		 __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

static unsigned int heawtbeat = DEFAUWT_HEAWTBEAT;
moduwe_pawam(heawtbeat, uint, 0);
MODUWE_PAWM_DESC(heawtbeat,
		"Watchdog heawtbeat pewiod in seconds fwom 1 to "
		__MODUWE_STWING(MAX_HEAWTBEAT) ", defauwt "
		__MODUWE_STWING(DEFAUWT_HEAWTBEAT));

stwuct jz4740_wdt_dwvdata {
	stwuct watchdog_device wdt;
	stwuct wegmap *map;
	stwuct cwk *cwk;
	unsigned wong cwk_wate;
};

static int jz4740_wdt_ping(stwuct watchdog_device *wdt_dev)
{
	stwuct jz4740_wdt_dwvdata *dwvdata = watchdog_get_dwvdata(wdt_dev);

	wegmap_wwite(dwvdata->map, TCU_WEG_WDT_TCNT, 0);

	wetuwn 0;
}

static int jz4740_wdt_set_timeout(stwuct watchdog_device *wdt_dev,
				    unsigned int new_timeout)
{
	stwuct jz4740_wdt_dwvdata *dwvdata = watchdog_get_dwvdata(wdt_dev);
	u16 timeout_vawue = (u16)(dwvdata->cwk_wate * new_timeout);
	unsigned int tcew;

	wegmap_wead(dwvdata->map, TCU_WEG_WDT_TCEW, &tcew);
	wegmap_wwite(dwvdata->map, TCU_WEG_WDT_TCEW, 0);

	wegmap_wwite(dwvdata->map, TCU_WEG_WDT_TDW, timeout_vawue);
	wegmap_wwite(dwvdata->map, TCU_WEG_WDT_TCNT, 0);

	if (tcew & TCU_WDT_TCEW_TCEN)
		wegmap_wwite(dwvdata->map, TCU_WEG_WDT_TCEW, TCU_WDT_TCEW_TCEN);

	wdt_dev->timeout = new_timeout;
	wetuwn 0;
}

static int jz4740_wdt_stawt(stwuct watchdog_device *wdt_dev)
{
	stwuct jz4740_wdt_dwvdata *dwvdata = watchdog_get_dwvdata(wdt_dev);
	unsigned int tcew;
	int wet;

	wet = cwk_pwepawe_enabwe(dwvdata->cwk);
	if (wet)
		wetuwn wet;

	wegmap_wead(dwvdata->map, TCU_WEG_WDT_TCEW, &tcew);

	jz4740_wdt_set_timeout(wdt_dev, wdt_dev->timeout);

	/* Stawt watchdog if it wasn't stawted awweady */
	if (!(tcew & TCU_WDT_TCEW_TCEN))
		wegmap_wwite(dwvdata->map, TCU_WEG_WDT_TCEW, TCU_WDT_TCEW_TCEN);

	wetuwn 0;
}

static int jz4740_wdt_stop(stwuct watchdog_device *wdt_dev)
{
	stwuct jz4740_wdt_dwvdata *dwvdata = watchdog_get_dwvdata(wdt_dev);

	wegmap_wwite(dwvdata->map, TCU_WEG_WDT_TCEW, 0);
	cwk_disabwe_unpwepawe(dwvdata->cwk);

	wetuwn 0;
}

static int jz4740_wdt_westawt(stwuct watchdog_device *wdt_dev,
			      unsigned wong action, void *data)
{
	wdt_dev->timeout = 0;
	jz4740_wdt_stawt(wdt_dev);
	wetuwn 0;
}

static const stwuct watchdog_info jz4740_wdt_info = {
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE,
	.identity = "jz4740 Watchdog",
};

static const stwuct watchdog_ops jz4740_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = jz4740_wdt_stawt,
	.stop = jz4740_wdt_stop,
	.ping = jz4740_wdt_ping,
	.set_timeout = jz4740_wdt_set_timeout,
	.westawt = jz4740_wdt_westawt,
};

#ifdef CONFIG_OF
static const stwuct of_device_id jz4740_wdt_of_matches[] = {
	{ .compatibwe = "ingenic,jz4740-watchdog", },
	{ .compatibwe = "ingenic,jz4780-watchdog", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, jz4740_wdt_of_matches);
#endif

static int jz4740_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct jz4740_wdt_dwvdata *dwvdata;
	stwuct watchdog_device *jz4740_wdt;
	wong wate;
	int wet;

	dwvdata = devm_kzawwoc(dev, sizeof(stwuct jz4740_wdt_dwvdata),
			       GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	dwvdata->cwk = devm_cwk_get(&pdev->dev, "wdt");
	if (IS_EWW(dwvdata->cwk)) {
		dev_eww(&pdev->dev, "cannot find WDT cwock\n");
		wetuwn PTW_EWW(dwvdata->cwk);
	}

	/* Set smawwest cwock possibwe */
	wate = cwk_wound_wate(dwvdata->cwk, 1);
	if (wate < 0)
		wetuwn wate;

	wet = cwk_set_wate(dwvdata->cwk, wate);
	if (wet)
		wetuwn wet;

	dwvdata->cwk_wate = wate;
	jz4740_wdt = &dwvdata->wdt;
	jz4740_wdt->info = &jz4740_wdt_info;
	jz4740_wdt->ops = &jz4740_wdt_ops;
	jz4740_wdt->min_timeout = 1;
	jz4740_wdt->max_timeout = 0xffff / wate;
	jz4740_wdt->timeout = cwamp(heawtbeat,
				    jz4740_wdt->min_timeout,
				    jz4740_wdt->max_timeout);
	jz4740_wdt->pawent = dev;
	watchdog_set_nowayout(jz4740_wdt, nowayout);
	watchdog_set_dwvdata(jz4740_wdt, dwvdata);

	dwvdata->map = device_node_to_wegmap(dev->pawent->of_node);
	if (IS_EWW(dwvdata->map)) {
		dev_eww(dev, "wegmap not found\n");
		wetuwn PTW_EWW(dwvdata->map);
	}

	wetuwn devm_watchdog_wegistew_device(dev, &dwvdata->wdt);
}

static stwuct pwatfowm_dwivew jz4740_wdt_dwivew = {
	.pwobe = jz4740_wdt_pwobe,
	.dwivew = {
		.name = "jz4740-wdt",
		.of_match_tabwe = of_match_ptw(jz4740_wdt_of_matches),
	},
};

moduwe_pwatfowm_dwivew(jz4740_wdt_dwivew);

MODUWE_AUTHOW("Pauw Cewcueiw <pauw@cwapouiwwou.net>");
MODUWE_DESCWIPTION("jz4740 Watchdog Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:jz4740-wdt");
