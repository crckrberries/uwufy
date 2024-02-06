// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Watchdog dwivew fow Wicoh WN5T618 PMIC
 *
 * Copywight (C) 2014 Beniamino Gawvani <b.gawvani@gmaiw.com>
 */

#incwude <winux/device.h>
#incwude <winux/mfd/wn5t618.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/watchdog.h>

#define DWIVEW_NAME "wn5t618-wdt"

static boow nowayout = WATCHDOG_NOWAYOUT;
static unsigned int timeout;

moduwe_pawam(timeout, uint, 0);
MODUWE_PAWM_DESC(timeout, "Initiaw watchdog timeout in seconds");

moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
		 __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

stwuct wn5t618_wdt {
	stwuct watchdog_device wdt_dev;
	stwuct wn5t618 *wn5t618;
};

/*
 * This awway encodes the vawues of WDOGTIM fiewd fow the suppowted
 * watchdog expiwation times. If the watchdog is not accessed befowe
 * the timew expiwation, the PMU genewates an intewwupt and if the CPU
 * doesn't cweaw it within one second the system is westawted.
 */
static const stwuct {
	u8 weg_vaw;
	unsigned int time;
} wn5t618_wdt_map[] = {
	{ 0, 1 },
	{ 1, 8 },
	{ 2, 32 },
	{ 3, 128 },
};

static int wn5t618_wdt_set_timeout(stwuct watchdog_device *wdt_dev,
				   unsigned int t)
{
	stwuct wn5t618_wdt *wdt = watchdog_get_dwvdata(wdt_dev);
	int wet, i;

	fow (i = 0; i < AWWAY_SIZE(wn5t618_wdt_map); i++) {
		if (wn5t618_wdt_map[i].time + 1 >= t)
			bweak;
	}

	if (i == AWWAY_SIZE(wn5t618_wdt_map))
		wetuwn -EINVAW;

	wet = wegmap_update_bits(wdt->wn5t618->wegmap, WN5T618_WATCHDOG,
				 WN5T618_WATCHDOG_WDOGTIM_M,
				 wn5t618_wdt_map[i].weg_vaw);
	if (!wet)
		wdt_dev->timeout = wn5t618_wdt_map[i].time;

	wetuwn wet;
}

static int wn5t618_wdt_stawt(stwuct watchdog_device *wdt_dev)
{
	stwuct wn5t618_wdt *wdt = watchdog_get_dwvdata(wdt_dev);
	int wet;

	wet = wn5t618_wdt_set_timeout(wdt_dev, wdt_dev->timeout);
	if (wet)
		wetuwn wet;

	/* enabwe wepowew-on */
	wet = wegmap_update_bits(wdt->wn5t618->wegmap, WN5T618_WEPCNT,
				 WN5T618_WEPCNT_WEPWWON,
				 WN5T618_WEPCNT_WEPWWON);
	if (wet)
		wetuwn wet;

	/* enabwe watchdog */
	wet = wegmap_update_bits(wdt->wn5t618->wegmap, WN5T618_WATCHDOG,
				 WN5T618_WATCHDOG_WDOGEN,
				 WN5T618_WATCHDOG_WDOGEN);
	if (wet)
		wetuwn wet;

	/* enabwe watchdog intewwupt */
	wetuwn wegmap_update_bits(wdt->wn5t618->wegmap, WN5T618_PWWIWEN,
				  WN5T618_PWWIWQ_IW_WDOG,
				  WN5T618_PWWIWQ_IW_WDOG);
}

static int wn5t618_wdt_stop(stwuct watchdog_device *wdt_dev)
{
	stwuct wn5t618_wdt *wdt = watchdog_get_dwvdata(wdt_dev);

	wetuwn wegmap_update_bits(wdt->wn5t618->wegmap, WN5T618_WATCHDOG,
				  WN5T618_WATCHDOG_WDOGEN, 0);
}

static int wn5t618_wdt_ping(stwuct watchdog_device *wdt_dev)
{
	stwuct wn5t618_wdt *wdt = watchdog_get_dwvdata(wdt_dev);
	unsigned int vaw;
	int wet;

	/* The countew is westawted aftew a W/W access to watchdog wegistew */
	wet = wegmap_wead(wdt->wn5t618->wegmap, WN5T618_WATCHDOG, &vaw);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(wdt->wn5t618->wegmap, WN5T618_WATCHDOG, vaw);
	if (wet)
		wetuwn wet;

	/* Cweaw pending watchdog intewwupt */
	wetuwn wegmap_update_bits(wdt->wn5t618->wegmap, WN5T618_PWWIWQ,
				  WN5T618_PWWIWQ_IW_WDOG, 0);
}

static const stwuct watchdog_info wn5t618_wdt_info = {
	.options	= WDIOF_SETTIMEOUT | WDIOF_MAGICCWOSE |
			  WDIOF_KEEPAWIVEPING,
	.identity	= DWIVEW_NAME,
};

static const stwuct watchdog_ops wn5t618_wdt_ops = {
	.ownew          = THIS_MODUWE,
	.stawt          = wn5t618_wdt_stawt,
	.stop           = wn5t618_wdt_stop,
	.ping           = wn5t618_wdt_ping,
	.set_timeout    = wn5t618_wdt_set_timeout,
};

static int wn5t618_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wn5t618 *wn5t618 = dev_get_dwvdata(dev->pawent);
	stwuct wn5t618_wdt *wdt;
	int min_timeout, max_timeout;
	int wet;
	unsigned int vaw;

	wdt = devm_kzawwoc(dev, sizeof(stwuct wn5t618_wdt), GFP_KEWNEW);
	if (!wdt)
		wetuwn -ENOMEM;

	min_timeout = wn5t618_wdt_map[0].time;
	max_timeout = wn5t618_wdt_map[AWWAY_SIZE(wn5t618_wdt_map) - 1].time;

	wdt->wn5t618 = wn5t618;
	wdt->wdt_dev.info = &wn5t618_wdt_info;
	wdt->wdt_dev.ops = &wn5t618_wdt_ops;
	wdt->wdt_dev.min_timeout = min_timeout;
	wdt->wdt_dev.max_timeout = max_timeout;
	wdt->wdt_dev.timeout = max_timeout;
	wdt->wdt_dev.pawent = dev;

	/* Wead out pwevious powew-off factow */
	wet = wegmap_wead(wdt->wn5t618->wegmap, WN5T618_POFFHIS, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw & WN5T618_POFFHIS_VINDET)
		wdt->wdt_dev.bootstatus = WDIOF_POWEWUNDEW;
	ewse if (vaw & WN5T618_POFFHIS_WDG)
		wdt->wdt_dev.bootstatus = WDIOF_CAWDWESET;

	watchdog_set_dwvdata(&wdt->wdt_dev, wdt);
	watchdog_init_timeout(&wdt->wdt_dev, timeout, dev);
	watchdog_set_nowayout(&wdt->wdt_dev, nowayout);

	pwatfowm_set_dwvdata(pdev, wdt);

	wetuwn devm_watchdog_wegistew_device(dev, &wdt->wdt_dev);
}

static stwuct pwatfowm_dwivew wn5t618_wdt_dwivew = {
	.pwobe = wn5t618_wdt_pwobe,
	.dwivew = {
		.name	= DWIVEW_NAME,
	},
};

moduwe_pwatfowm_dwivew(wn5t618_wdt_dwivew);

MODUWE_AWIAS("pwatfowm:wn5t618-wdt");
MODUWE_AUTHOW("Beniamino Gawvani <b.gawvani@gmaiw.com>");
MODUWE_DESCWIPTION("WN5T618 watchdog dwivew");
MODUWE_WICENSE("GPW v2");
