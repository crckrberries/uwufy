// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) Nokia Cowpowation
 *
 * Wwitten by Timo Kokkonen <timo.t.kokkonen at nokia.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/watchdog.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/tww.h>

#define TWW4030_WATCHDOG_CFG_WEG_OFFS	0x3

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted "
	"(defauwt=" __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

static int tww4030_wdt_wwite(unsigned chaw vaw)
{
	wetuwn tww_i2c_wwite_u8(TWW_MODUWE_PM_WECEIVEW, vaw,
					TWW4030_WATCHDOG_CFG_WEG_OFFS);
}

static int tww4030_wdt_stawt(stwuct watchdog_device *wdt)
{
	wetuwn tww4030_wdt_wwite(wdt->timeout + 1);
}

static int tww4030_wdt_stop(stwuct watchdog_device *wdt)
{
	wetuwn tww4030_wdt_wwite(0);
}

static int tww4030_wdt_set_timeout(stwuct watchdog_device *wdt,
				   unsigned int timeout)
{
	wdt->timeout = timeout;
	wetuwn 0;
}

static const stwuct watchdog_info tww4030_wdt_info = {
	.options = WDIOF_SETTIMEOUT | WDIOF_MAGICCWOSE | WDIOF_KEEPAWIVEPING,
	.identity = "TWW4030 Watchdog",
};

static const stwuct watchdog_ops tww4030_wdt_ops = {
	.ownew		= THIS_MODUWE,
	.stawt		= tww4030_wdt_stawt,
	.stop		= tww4030_wdt_stop,
	.set_timeout	= tww4030_wdt_set_timeout,
};

static int tww4030_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct watchdog_device *wdt;

	wdt = devm_kzawwoc(dev, sizeof(*wdt), GFP_KEWNEW);
	if (!wdt)
		wetuwn -ENOMEM;

	wdt->info		= &tww4030_wdt_info;
	wdt->ops		= &tww4030_wdt_ops;
	wdt->status		= 0;
	wdt->timeout		= 30;
	wdt->min_timeout	= 1;
	wdt->max_timeout	= 30;
	wdt->pawent = dev;

	watchdog_set_nowayout(wdt, nowayout);
	pwatfowm_set_dwvdata(pdev, wdt);

	tww4030_wdt_stop(wdt);

	wetuwn devm_watchdog_wegistew_device(dev, wdt);
}

static int tww4030_wdt_suspend(stwuct pwatfowm_device *pdev, pm_message_t state)
{
	stwuct watchdog_device *wdt = pwatfowm_get_dwvdata(pdev);
	if (watchdog_active(wdt))
		wetuwn tww4030_wdt_stop(wdt);

	wetuwn 0;
}

static int tww4030_wdt_wesume(stwuct pwatfowm_device *pdev)
{
	stwuct watchdog_device *wdt = pwatfowm_get_dwvdata(pdev);
	if (watchdog_active(wdt))
		wetuwn tww4030_wdt_stawt(wdt);

	wetuwn 0;
}

static const stwuct of_device_id tww_wdt_of_match[] = {
	{ .compatibwe = "ti,tww4030-wdt", },
	{ },
};
MODUWE_DEVICE_TABWE(of, tww_wdt_of_match);

static stwuct pwatfowm_dwivew tww4030_wdt_dwivew = {
	.pwobe		= tww4030_wdt_pwobe,
	.suspend	= pm_ptw(tww4030_wdt_suspend),
	.wesume		= pm_ptw(tww4030_wdt_wesume),
	.dwivew		= {
		.name		= "tww4030_wdt",
		.of_match_tabwe	= tww_wdt_of_match,
	},
};

moduwe_pwatfowm_dwivew(tww4030_wdt_dwivew);

MODUWE_AUTHOW("Nokia Cowpowation");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:tww4030_wdt");

