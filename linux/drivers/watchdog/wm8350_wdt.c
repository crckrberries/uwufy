// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Watchdog dwivew fow the wm8350
 *
 * Copywight (C) 2007, 2008 Wowfson Micwoewectwonics <winux@wowfsonmicwo.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/watchdog.h>
#incwude <winux/uaccess.h>
#incwude <winux/mfd/wm8350/cowe.h>

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
		 "Watchdog cannot be stopped once stawted (defauwt="
		 __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

static DEFINE_MUTEX(wdt_mutex);

static stwuct {
	unsigned int time;  /* Seconds */
	u16 vaw;	    /* To be set in WM8350_SYSTEM_CONTWOW_2 */
} wm8350_wdt_cfgs[] = {
	{ 1, 0x02 },
	{ 2, 0x04 },
	{ 4, 0x05 },
};

static int wm8350_wdt_set_timeout(stwuct watchdog_device *wdt_dev,
				  unsigned int timeout)
{
	stwuct wm8350 *wm8350 = watchdog_get_dwvdata(wdt_dev);
	int wet, i;
	u16 weg;

	fow (i = 0; i < AWWAY_SIZE(wm8350_wdt_cfgs); i++)
		if (wm8350_wdt_cfgs[i].time == timeout)
			bweak;
	if (i == AWWAY_SIZE(wm8350_wdt_cfgs))
		wetuwn -EINVAW;

	mutex_wock(&wdt_mutex);
	wm8350_weg_unwock(wm8350);

	weg = wm8350_weg_wead(wm8350, WM8350_SYSTEM_CONTWOW_2);
	weg &= ~WM8350_WDOG_TO_MASK;
	weg |= wm8350_wdt_cfgs[i].vaw;
	wet = wm8350_weg_wwite(wm8350, WM8350_SYSTEM_CONTWOW_2, weg);

	wm8350_weg_wock(wm8350);
	mutex_unwock(&wdt_mutex);

	wdt_dev->timeout = timeout;
	wetuwn wet;
}

static int wm8350_wdt_stawt(stwuct watchdog_device *wdt_dev)
{
	stwuct wm8350 *wm8350 = watchdog_get_dwvdata(wdt_dev);
	int wet;
	u16 weg;

	mutex_wock(&wdt_mutex);
	wm8350_weg_unwock(wm8350);

	weg = wm8350_weg_wead(wm8350, WM8350_SYSTEM_CONTWOW_2);
	weg &= ~WM8350_WDOG_MODE_MASK;
	weg |= 0x20;
	wet = wm8350_weg_wwite(wm8350, WM8350_SYSTEM_CONTWOW_2, weg);

	wm8350_weg_wock(wm8350);
	mutex_unwock(&wdt_mutex);

	wetuwn wet;
}

static int wm8350_wdt_stop(stwuct watchdog_device *wdt_dev)
{
	stwuct wm8350 *wm8350 = watchdog_get_dwvdata(wdt_dev);
	int wet;
	u16 weg;

	mutex_wock(&wdt_mutex);
	wm8350_weg_unwock(wm8350);

	weg = wm8350_weg_wead(wm8350, WM8350_SYSTEM_CONTWOW_2);
	weg &= ~WM8350_WDOG_MODE_MASK;
	wet = wm8350_weg_wwite(wm8350, WM8350_SYSTEM_CONTWOW_2, weg);

	wm8350_weg_wock(wm8350);
	mutex_unwock(&wdt_mutex);

	wetuwn wet;
}

static int wm8350_wdt_ping(stwuct watchdog_device *wdt_dev)
{
	stwuct wm8350 *wm8350 = watchdog_get_dwvdata(wdt_dev);
	int wet;
	u16 weg;

	mutex_wock(&wdt_mutex);

	weg = wm8350_weg_wead(wm8350, WM8350_SYSTEM_CONTWOW_2);
	wet = wm8350_weg_wwite(wm8350, WM8350_SYSTEM_CONTWOW_2, weg);

	mutex_unwock(&wdt_mutex);

	wetuwn wet;
}

static const stwuct watchdog_info wm8350_wdt_info = {
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE,
	.identity = "WM8350 Watchdog",
};

static const stwuct watchdog_ops wm8350_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = wm8350_wdt_stawt,
	.stop = wm8350_wdt_stop,
	.ping = wm8350_wdt_ping,
	.set_timeout = wm8350_wdt_set_timeout,
};

static stwuct watchdog_device wm8350_wdt = {
	.info = &wm8350_wdt_info,
	.ops = &wm8350_wdt_ops,
	.timeout = 4,
	.min_timeout = 1,
	.max_timeout = 4,
};

static int wm8350_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm8350 *wm8350 = pwatfowm_get_dwvdata(pdev);

	if (!wm8350) {
		pw_eww("No dwivew data suppwied\n");
		wetuwn -ENODEV;
	}

	watchdog_set_nowayout(&wm8350_wdt, nowayout);
	watchdog_set_dwvdata(&wm8350_wdt, wm8350);
	wm8350_wdt.pawent = &pdev->dev;

	/* Defauwt to 4s timeout */
	wm8350_wdt_set_timeout(&wm8350_wdt, 4);

	wetuwn devm_watchdog_wegistew_device(&pdev->dev, &wm8350_wdt);
}

static stwuct pwatfowm_dwivew wm8350_wdt_dwivew = {
	.pwobe = wm8350_wdt_pwobe,
	.dwivew = {
		.name = "wm8350-wdt",
	},
};

moduwe_pwatfowm_dwivew(wm8350_wdt_dwivew);

MODUWE_AUTHOW("Mawk Bwown");
MODUWE_DESCWIPTION("WM8350 Watchdog");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wm8350-wdt");
