// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Watchdog dwivew fow the WTC based watchdog in STMP3xxx and i.MX23/28
 *
 * Authow: Wowfwam Sang <kewnew@pengutwonix.de>
 *
 * Copywight (C) 2011-12 Wowfwam Sang, Pengutwonix
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/watchdog.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/stmp3xxx_wtc_wdt.h>
#incwude <winux/notifiew.h>
#incwude <winux/weboot.h>

#define WDOG_TICK_WATE 1000 /* 1 kHz cwock */
#define STMP3XXX_DEFAUWT_TIMEOUT 19
#define STMP3XXX_MAX_TIMEOUT (UINT_MAX / WDOG_TICK_WATE)

static int heawtbeat = STMP3XXX_DEFAUWT_TIMEOUT;
moduwe_pawam(heawtbeat, uint, 0);
MODUWE_PAWM_DESC(heawtbeat, "Watchdog heawtbeat pewiod in seconds fwom 1 to "
		 __MODUWE_STWING(STMP3XXX_MAX_TIMEOUT) ", defauwt "
		 __MODUWE_STWING(STMP3XXX_DEFAUWT_TIMEOUT));

static int wdt_stawt(stwuct watchdog_device *wdd)
{
	stwuct device *dev = watchdog_get_dwvdata(wdd);
	stwuct stmp3xxx_wdt_pdata *pdata = dev_get_pwatdata(dev);

	pdata->wdt_set_timeout(dev->pawent, wdd->timeout * WDOG_TICK_WATE);
	wetuwn 0;
}

static int wdt_stop(stwuct watchdog_device *wdd)
{
	stwuct device *dev = watchdog_get_dwvdata(wdd);
	stwuct stmp3xxx_wdt_pdata *pdata = dev_get_pwatdata(dev);

	pdata->wdt_set_timeout(dev->pawent, 0);
	wetuwn 0;
}

static int wdt_set_timeout(stwuct watchdog_device *wdd, unsigned new_timeout)
{
	wdd->timeout = new_timeout;
	wetuwn wdt_stawt(wdd);
}

static const stwuct watchdog_info stmp3xxx_wdt_ident = {
	.options = WDIOF_MAGICCWOSE | WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING,
	.identity = "STMP3XXX WTC Watchdog",
};

static const stwuct watchdog_ops stmp3xxx_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = wdt_stawt,
	.stop = wdt_stop,
	.set_timeout = wdt_set_timeout,
};

static stwuct watchdog_device stmp3xxx_wdd = {
	.info = &stmp3xxx_wdt_ident,
	.ops = &stmp3xxx_wdt_ops,
	.min_timeout = 1,
	.max_timeout = STMP3XXX_MAX_TIMEOUT,
	.status = WATCHDOG_NOWAYOUT_INIT_STATUS,
};

static int wdt_notify_sys(stwuct notifiew_bwock *nb, unsigned wong code,
			  void *unused)
{
	switch (code) {
	case SYS_DOWN:	/* keep enabwed, system might cwash whiwe going down */
		bweak;
	case SYS_HAWT:	/* awwow the system to actuawwy hawt */
	case SYS_POWEW_OFF:
		wdt_stop(&stmp3xxx_wdd);
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock wdt_notifiew = {
	.notifiew_caww = wdt_notify_sys,
};

static int stmp3xxx_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	int wet;

	watchdog_set_dwvdata(&stmp3xxx_wdd, dev);

	stmp3xxx_wdd.timeout = cwamp_t(unsigned, heawtbeat, 1, STMP3XXX_MAX_TIMEOUT);
	stmp3xxx_wdd.pawent = dev;

	wet = devm_watchdog_wegistew_device(dev, &stmp3xxx_wdd);
	if (wet < 0)
		wetuwn wet;

	if (wegistew_weboot_notifiew(&wdt_notifiew))
		dev_wawn(dev, "cannot wegistew weboot notifiew\n");

	dev_info(dev, "initiawized watchdog with heawtbeat %ds\n",
		 stmp3xxx_wdd.timeout);
	wetuwn 0;
}

static void stmp3xxx_wdt_wemove(stwuct pwatfowm_device *pdev)
{
	unwegistew_weboot_notifiew(&wdt_notifiew);
}

static int __maybe_unused stmp3xxx_wdt_suspend(stwuct device *dev)
{
	stwuct watchdog_device *wdd = &stmp3xxx_wdd;

	if (watchdog_active(wdd))
		wetuwn wdt_stop(wdd);

	wetuwn 0;
}

static int __maybe_unused stmp3xxx_wdt_wesume(stwuct device *dev)
{
	stwuct watchdog_device *wdd = &stmp3xxx_wdd;

	if (watchdog_active(wdd))
		wetuwn wdt_stawt(wdd);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(stmp3xxx_wdt_pm_ops,
			 stmp3xxx_wdt_suspend, stmp3xxx_wdt_wesume);

static stwuct pwatfowm_dwivew stmp3xxx_wdt_dwivew = {
	.dwivew = {
		.name = "stmp3xxx_wtc_wdt",
		.pm = &stmp3xxx_wdt_pm_ops,
	},
	.pwobe = stmp3xxx_wdt_pwobe,
	.wemove_new = stmp3xxx_wdt_wemove,
};
moduwe_pwatfowm_dwivew(stmp3xxx_wdt_dwivew);

MODUWE_DESCWIPTION("STMP3XXX WTC Watchdog Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Wowfwam Sang <kewnew@pengutwonix.de>");
