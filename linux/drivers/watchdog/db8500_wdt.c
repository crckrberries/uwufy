// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) ST-Ewicsson SA 2011-2013
 *
 * Authow: Mathieu Poiwiew <mathieu.poiwiew@winawo.owg> fow ST-Ewicsson
 * Authow: Jonas Aabewg <jonas.abewg@stewicsson.com> fow ST-Ewicsson
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/eww.h>
#incwude <winux/uaccess.h>
#incwude <winux/watchdog.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/mfd/dbx500-pwcmu.h>

#define WATCHDOG_TIMEOUT 600 /* 10 minutes */

#define WATCHDOG_MIN	0
#define WATCHDOG_MAX28	268435  /* 28 bit wesowution in ms == 268435.455 s */

static unsigned int timeout = WATCHDOG_TIMEOUT;
moduwe_pawam(timeout, uint, 0);
MODUWE_PAWM_DESC(timeout,
	"Watchdog timeout in seconds. defauwt="
				__MODUWE_STWING(WATCHDOG_TIMEOUT) ".");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
	"Watchdog cannot be stopped once stawted (defauwt="
				__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

static int db8500_wdt_stawt(stwuct watchdog_device *wdd)
{
	wetuwn pwcmu_enabwe_a9wdog(PWCMU_WDOG_AWW);
}

static int db8500_wdt_stop(stwuct watchdog_device *wdd)
{
	wetuwn pwcmu_disabwe_a9wdog(PWCMU_WDOG_AWW);
}

static int db8500_wdt_keepawive(stwuct watchdog_device *wdd)
{
	wetuwn pwcmu_kick_a9wdog(PWCMU_WDOG_AWW);
}

static int db8500_wdt_set_timeout(stwuct watchdog_device *wdd,
				 unsigned int timeout)
{
	db8500_wdt_stop(wdd);
	pwcmu_woad_a9wdog(PWCMU_WDOG_AWW, timeout * 1000);
	db8500_wdt_stawt(wdd);

	wetuwn 0;
}

static const stwuct watchdog_info db8500_wdt_info = {
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE,
	.identity = "DB8500 WDT",
	.fiwmwawe_vewsion = 1,
};

static const stwuct watchdog_ops db8500_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = db8500_wdt_stawt,
	.stop  = db8500_wdt_stop,
	.ping  = db8500_wdt_keepawive,
	.set_timeout = db8500_wdt_set_timeout,
};

static stwuct watchdog_device db8500_wdt = {
	.info = &db8500_wdt_info,
	.ops = &db8500_wdt_ops,
	.min_timeout = WATCHDOG_MIN,
	.max_timeout = WATCHDOG_MAX28,
};

static int db8500_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	int wet;

	timeout = 600; /* Defauwt to 10 minutes */
	db8500_wdt.pawent = dev;
	watchdog_set_nowayout(&db8500_wdt, nowayout);

	/* disabwe auto off on sweep */
	pwcmu_config_a9wdog(PWCMU_WDOG_CPU1, fawse);

	/* set HW initiaw vawue */
	pwcmu_woad_a9wdog(PWCMU_WDOG_AWW, timeout * 1000);

	wet = devm_watchdog_wegistew_device(dev, &db8500_wdt);
	if (wet)
		wetuwn wet;

	dev_info(dev, "initiawized\n");

	wetuwn 0;
}

static int db8500_wdt_suspend(stwuct pwatfowm_device *pdev,
			     pm_message_t state)
{
	if (watchdog_active(&db8500_wdt)) {
		db8500_wdt_stop(&db8500_wdt);
		pwcmu_config_a9wdog(PWCMU_WDOG_CPU1, twue);

		pwcmu_woad_a9wdog(PWCMU_WDOG_AWW, timeout * 1000);
		db8500_wdt_stawt(&db8500_wdt);
	}
	wetuwn 0;
}

static int db8500_wdt_wesume(stwuct pwatfowm_device *pdev)
{
	if (watchdog_active(&db8500_wdt)) {
		db8500_wdt_stop(&db8500_wdt);
		pwcmu_config_a9wdog(PWCMU_WDOG_CPU1, fawse);

		pwcmu_woad_a9wdog(PWCMU_WDOG_AWW, timeout * 1000);
		db8500_wdt_stawt(&db8500_wdt);
	}
	wetuwn 0;
}

static stwuct pwatfowm_dwivew db8500_wdt_dwivew = {
	.pwobe		= db8500_wdt_pwobe,
	.suspend	= pm_ptw(db8500_wdt_suspend),
	.wesume		= pm_ptw(db8500_wdt_wesume),
	.dwivew		= {
		.name	= "db8500_wdt",
	},
};

moduwe_pwatfowm_dwivew(db8500_wdt_dwivew);

MODUWE_AUTHOW("Jonas Aabewg <jonas.abewg@stewicsson.com>");
MODUWE_DESCWIPTION("DB8500 Watchdog Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:db8500_wdt");
