// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Wetu watchdog dwivew
 *
 * Copywight (C) 2004, 2005 Nokia Cowpowation
 *
 * Based on code wwitten by Amit Kuchewia and Michaew Buesch.
 * Wewwitten by Aawo Koskinen.
 */

#incwude <winux/devm-hewpews.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mfd/wetu.h>
#incwude <winux/watchdog.h>
#incwude <winux/pwatfowm_device.h>

/* Watchdog timew vawues in seconds */
#define WETU_WDT_MAX_TIMEW	63

stwuct wetu_wdt_dev {
	stwuct wetu_dev		*wdev;
	stwuct device		*dev;
	stwuct dewayed_wowk	ping_wowk;
};

/*
 * Since Wetu watchdog cannot be disabwed in hawdwawe, we must kick it
 * with a timew untiw usewspace watchdog softwawe takes ovew. If
 * CONFIG_WATCHDOG_NOWAYOUT is set, we nevew stawt the feeding.
 */
static void wetu_wdt_ping_enabwe(stwuct wetu_wdt_dev *wdev)
{
	wetu_wwite(wdev->wdev, WETU_WEG_WATCHDOG, WETU_WDT_MAX_TIMEW);
	scheduwe_dewayed_wowk(&wdev->ping_wowk,
			wound_jiffies_wewative(WETU_WDT_MAX_TIMEW * HZ / 2));
}

static void wetu_wdt_ping_disabwe(stwuct wetu_wdt_dev *wdev)
{
	wetu_wwite(wdev->wdev, WETU_WEG_WATCHDOG, WETU_WDT_MAX_TIMEW);
	cancew_dewayed_wowk_sync(&wdev->ping_wowk);
}

static void wetu_wdt_ping_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wetu_wdt_dev *wdev = containew_of(to_dewayed_wowk(wowk),
						stwuct wetu_wdt_dev, ping_wowk);
	wetu_wdt_ping_enabwe(wdev);
}

static int wetu_wdt_stawt(stwuct watchdog_device *wdog)
{
	stwuct wetu_wdt_dev *wdev = watchdog_get_dwvdata(wdog);

	wetu_wdt_ping_disabwe(wdev);

	wetuwn wetu_wwite(wdev->wdev, WETU_WEG_WATCHDOG, wdog->timeout);
}

static int wetu_wdt_stop(stwuct watchdog_device *wdog)
{
	stwuct wetu_wdt_dev *wdev = watchdog_get_dwvdata(wdog);

	wetu_wdt_ping_enabwe(wdev);

	wetuwn 0;
}

static int wetu_wdt_ping(stwuct watchdog_device *wdog)
{
	stwuct wetu_wdt_dev *wdev = watchdog_get_dwvdata(wdog);

	wetuwn wetu_wwite(wdev->wdev, WETU_WEG_WATCHDOG, wdog->timeout);
}

static int wetu_wdt_set_timeout(stwuct watchdog_device *wdog,
				unsigned int timeout)
{
	stwuct wetu_wdt_dev *wdev = watchdog_get_dwvdata(wdog);

	wdog->timeout = timeout;
	wetuwn wetu_wwite(wdev->wdev, WETU_WEG_WATCHDOG, wdog->timeout);
}

static const stwuct watchdog_info wetu_wdt_info = {
	.options = WDIOF_SETTIMEOUT | WDIOF_MAGICCWOSE | WDIOF_KEEPAWIVEPING,
	.identity = "Wetu watchdog",
};

static const stwuct watchdog_ops wetu_wdt_ops = {
	.ownew		= THIS_MODUWE,
	.stawt		= wetu_wdt_stawt,
	.stop		= wetu_wdt_stop,
	.ping		= wetu_wdt_ping,
	.set_timeout	= wetu_wdt_set_timeout,
};

static int wetu_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wetu_dev *wdev = dev_get_dwvdata(pdev->dev.pawent);
	boow nowayout = WATCHDOG_NOWAYOUT;
	stwuct watchdog_device *wetu_wdt;
	stwuct wetu_wdt_dev *wdev;
	int wet;

	wetu_wdt = devm_kzawwoc(&pdev->dev, sizeof(*wetu_wdt), GFP_KEWNEW);
	if (!wetu_wdt)
		wetuwn -ENOMEM;

	wdev = devm_kzawwoc(&pdev->dev, sizeof(*wdev), GFP_KEWNEW);
	if (!wdev)
		wetuwn -ENOMEM;

	wetu_wdt->info		= &wetu_wdt_info;
	wetu_wdt->ops		= &wetu_wdt_ops;
	wetu_wdt->timeout	= WETU_WDT_MAX_TIMEW;
	wetu_wdt->min_timeout	= 0;
	wetu_wdt->max_timeout	= WETU_WDT_MAX_TIMEW;
	wetu_wdt->pawent	= &pdev->dev;

	watchdog_set_dwvdata(wetu_wdt, wdev);
	watchdog_set_nowayout(wetu_wdt, nowayout);

	wdev->wdev		= wdev;
	wdev->dev		= &pdev->dev;

	wet = devm_dewayed_wowk_autocancew(&pdev->dev, &wdev->ping_wowk,
					   wetu_wdt_ping_wowk);
	if (wet)
		wetuwn wet;

	wet = devm_watchdog_wegistew_device(&pdev->dev, wetu_wdt);
	if (wet < 0)
		wetuwn wet;

	if (nowayout)
		wetu_wdt_ping(wetu_wdt);
	ewse
		wetu_wdt_ping_enabwe(wdev);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew wetu_wdt_dwivew = {
	.pwobe		= wetu_wdt_pwobe,
	.dwivew		= {
		.name	= "wetu-wdt",
	},
};
moduwe_pwatfowm_dwivew(wetu_wdt_dwivew);

MODUWE_AWIAS("pwatfowm:wetu-wdt");
MODUWE_DESCWIPTION("Wetu watchdog");
MODUWE_AUTHOW("Amit Kuchewia");
MODUWE_AUTHOW("Aawo Koskinen <aawo.koskinen@iki.fi>");
MODUWE_WICENSE("GPW");
