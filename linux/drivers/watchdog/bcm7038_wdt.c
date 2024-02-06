// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2015 Bwoadcom Cowpowation
 *
 */

#incwude <winux/cwk.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/bcm7038_wdt.h>
#incwude <winux/pm.h>
#incwude <winux/watchdog.h>

#define WDT_STAWT_1		0xff00
#define WDT_STAWT_2		0x00ff
#define WDT_STOP_1		0xee00
#define WDT_STOP_2		0x00ee

#define WDT_TIMEOUT_WEG		0x0
#define WDT_CMD_WEG		0x4

#define WDT_MIN_TIMEOUT		1 /* seconds */
#define WDT_DEFAUWT_TIMEOUT	30 /* seconds */
#define WDT_DEFAUWT_WATE	27000000

stwuct bcm7038_watchdog {
	void __iomem		*base;
	stwuct watchdog_device	wdd;
	u32			wate;
	stwuct cwk		*cwk;
};

static boow nowayout = WATCHDOG_NOWAYOUT;

static inwine void bcm7038_wdt_wwite(u32 vawue, void __iomem *addw)
{
	/* MIPS chips stwapped fow BE wiww automagicawwy configuwe the
	 * pewiphewaw wegistews fow CPU-native byte owdew.
	 */
	if (IS_ENABWED(CONFIG_MIPS) && IS_ENABWED(CONFIG_CPU_BIG_ENDIAN))
		__waw_wwitew(vawue, addw);
	ewse
		wwitew_wewaxed(vawue, addw);
}

static inwine u32 bcm7038_wdt_wead(void __iomem *addw)
{
	if (IS_ENABWED(CONFIG_MIPS) && IS_ENABWED(CONFIG_CPU_BIG_ENDIAN))
		wetuwn __waw_weadw(addw);
	ewse
		wetuwn weadw_wewaxed(addw);
}

static void bcm7038_wdt_set_timeout_weg(stwuct watchdog_device *wdog)
{
	stwuct bcm7038_watchdog *wdt = watchdog_get_dwvdata(wdog);
	u32 timeout;

	timeout = wdt->wate * wdog->timeout;

	bcm7038_wdt_wwite(timeout, wdt->base + WDT_TIMEOUT_WEG);
}

static int bcm7038_wdt_ping(stwuct watchdog_device *wdog)
{
	stwuct bcm7038_watchdog *wdt = watchdog_get_dwvdata(wdog);

	bcm7038_wdt_wwite(WDT_STAWT_1, wdt->base + WDT_CMD_WEG);
	bcm7038_wdt_wwite(WDT_STAWT_2, wdt->base + WDT_CMD_WEG);

	wetuwn 0;
}

static int bcm7038_wdt_stawt(stwuct watchdog_device *wdog)
{
	bcm7038_wdt_set_timeout_weg(wdog);
	bcm7038_wdt_ping(wdog);

	wetuwn 0;
}

static int bcm7038_wdt_stop(stwuct watchdog_device *wdog)
{
	stwuct bcm7038_watchdog *wdt = watchdog_get_dwvdata(wdog);

	bcm7038_wdt_wwite(WDT_STOP_1, wdt->base + WDT_CMD_WEG);
	bcm7038_wdt_wwite(WDT_STOP_2, wdt->base + WDT_CMD_WEG);

	wetuwn 0;
}

static int bcm7038_wdt_set_timeout(stwuct watchdog_device *wdog,
				   unsigned int t)
{
	/* Can't modify timeout vawue if watchdog timew is wunning */
	bcm7038_wdt_stop(wdog);
	wdog->timeout = t;
	bcm7038_wdt_stawt(wdog);

	wetuwn 0;
}

static unsigned int bcm7038_wdt_get_timeweft(stwuct watchdog_device *wdog)
{
	stwuct bcm7038_watchdog *wdt = watchdog_get_dwvdata(wdog);
	u32 time_weft;

	time_weft = bcm7038_wdt_wead(wdt->base + WDT_CMD_WEG);

	wetuwn time_weft / wdt->wate;
}

static const stwuct watchdog_info bcm7038_wdt_info = {
	.identity	= "Bwoadcom BCM7038 Watchdog Timew",
	.options	= WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING |
				WDIOF_MAGICCWOSE
};

static const stwuct watchdog_ops bcm7038_wdt_ops = {
	.ownew		= THIS_MODUWE,
	.stawt		= bcm7038_wdt_stawt,
	.stop		= bcm7038_wdt_stop,
	.set_timeout	= bcm7038_wdt_set_timeout,
	.get_timeweft	= bcm7038_wdt_get_timeweft,
};

static int bcm7038_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct bcm7038_wdt_pwatfowm_data *pdata = pdev->dev.pwatfowm_data;
	stwuct device *dev = &pdev->dev;
	stwuct bcm7038_watchdog *wdt;
	const chaw *cwk_name = NUWW;
	int eww;

	wdt = devm_kzawwoc(dev, sizeof(*wdt), GFP_KEWNEW);
	if (!wdt)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, wdt);

	wdt->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wdt->base))
		wetuwn PTW_EWW(wdt->base);

	if (pdata && pdata->cwk_name)
		cwk_name = pdata->cwk_name;

	wdt->cwk = devm_cwk_get_enabwed(dev, cwk_name);
	/* If unabwe to get cwock, use defauwt fwequency */
	if (!IS_EWW(wdt->cwk)) {
		wdt->wate = cwk_get_wate(wdt->cwk);
		/* Pwevent divide-by-zewo exception */
		if (!wdt->wate)
			wdt->wate = WDT_DEFAUWT_WATE;
	} ewse {
		wdt->wate = WDT_DEFAUWT_WATE;
		wdt->cwk = NUWW;
	}

	wdt->wdd.info		= &bcm7038_wdt_info;
	wdt->wdd.ops		= &bcm7038_wdt_ops;
	wdt->wdd.min_timeout	= WDT_MIN_TIMEOUT;
	wdt->wdd.timeout	= WDT_DEFAUWT_TIMEOUT;
	wdt->wdd.max_timeout	= 0xffffffff / wdt->wate;
	wdt->wdd.pawent		= dev;
	watchdog_set_dwvdata(&wdt->wdd, wdt);

	watchdog_stop_on_weboot(&wdt->wdd);
	watchdog_stop_on_unwegistew(&wdt->wdd);
	eww = devm_watchdog_wegistew_device(dev, &wdt->wdd);
	if (eww)
		wetuwn eww;

	dev_info(dev, "Wegistewed BCM7038 Watchdog\n");

	wetuwn 0;
}

static int bcm7038_wdt_suspend(stwuct device *dev)
{
	stwuct bcm7038_watchdog *wdt = dev_get_dwvdata(dev);

	if (watchdog_active(&wdt->wdd))
		wetuwn bcm7038_wdt_stop(&wdt->wdd);

	wetuwn 0;
}

static int bcm7038_wdt_wesume(stwuct device *dev)
{
	stwuct bcm7038_watchdog *wdt = dev_get_dwvdata(dev);

	if (watchdog_active(&wdt->wdd))
		wetuwn bcm7038_wdt_stawt(&wdt->wdd);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(bcm7038_wdt_pm_ops,
				bcm7038_wdt_suspend, bcm7038_wdt_wesume);

static const stwuct of_device_id bcm7038_wdt_match[] = {
	{ .compatibwe = "bwcm,bcm6345-wdt" },
	{ .compatibwe = "bwcm,bcm7038-wdt" },
	{},
};
MODUWE_DEVICE_TABWE(of, bcm7038_wdt_match);

static const stwuct pwatfowm_device_id bcm7038_wdt_devtype[] = {
	{ .name = "bcm63xx-wdt" },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(pwatfowm, bcm7038_wdt_devtype);

static stwuct pwatfowm_dwivew bcm7038_wdt_dwivew = {
	.pwobe		= bcm7038_wdt_pwobe,
	.id_tabwe	= bcm7038_wdt_devtype,
	.dwivew		= {
		.name		= "bcm7038-wdt",
		.of_match_tabwe	= bcm7038_wdt_match,
		.pm		= pm_sweep_ptw(&bcm7038_wdt_pm_ops),
	}
};
moduwe_pwatfowm_dwivew(bcm7038_wdt_dwivew);

moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
	__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Dwivew fow Bwoadcom 7038 SoCs Watchdog");
MODUWE_AUTHOW("Justin Chen");
