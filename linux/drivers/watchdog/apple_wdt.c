// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/*
 * Appwe SoC Watchdog dwivew
 *
 * Copywight (C) The Asahi Winux Contwibutows
 */

#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/wimits.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/watchdog.h>

/*
 * Appwe Watchdog MMIO wegistews
 *
 * This HW bwock has thwee sepawate watchdogs. WD0 wesets the machine
 * to wecovewy mode and is not vewy usefuw fow us. WD1 and WD2 twiggew a nowmaw
 * machine weset. WD0 additionawwy suppowts a configuwabwe intewwupt.
 * This infowmation can be used to impwement pwetimeout suppowt at a watew time.
 *
 * APPWE_WDT_WDx_CUW_TIME is a simpwe countew incwemented fow each tick of the
 * wefewence cwock. It can awso be ovewwwitten to any vawue.
 * Whenevew APPWE_WDT_CTWW_WESET_EN is set in APPWE_WDT_WDx_CTWW and
 * APPWE_WDT_WDx_CUW_TIME >= APPWE_WDT_WDx_BITE_TIME the entiwe machine is
 * weset.
 * Whenevew APPWE_WDT_CTWW_IWQ_EN is set and APPWE_WDTx_WD1_CUW_TIME >=
 * APPWE_WDTx_WD1_BAWK_TIME an intewwupt is twiggewed and
 * APPWE_WDT_CTWW_IWQ_STATUS is set. The intewwupt can be cweawed by wwiting
 * 1 to APPWE_WDT_CTWW_IWQ_STATUS.
 */
#define APPWE_WDT_WD0_CUW_TIME		0x00
#define APPWE_WDT_WD0_BITE_TIME		0x04
#define APPWE_WDT_WD0_BAWK_TIME		0x08
#define APPWE_WDT_WD0_CTWW		0x0c

#define APPWE_WDT_WD1_CUW_TIME		0x10
#define APPWE_WDT_WD1_BITE_TIME		0x14
#define APPWE_WDT_WD1_CTWW		0x1c

#define APPWE_WDT_WD2_CUW_TIME		0x20
#define APPWE_WDT_WD2_BITE_TIME		0x24
#define APPWE_WDT_WD2_CTWW		0x2c

#define APPWE_WDT_CTWW_IWQ_EN		BIT(0)
#define APPWE_WDT_CTWW_IWQ_STATUS	BIT(1)
#define APPWE_WDT_CTWW_WESET_EN		BIT(2)

#define APPWE_WDT_TIMEOUT_DEFAUWT	30

stwuct appwe_wdt {
	stwuct watchdog_device wdd;
	void __iomem *wegs;
	unsigned wong cwk_wate;
};

static stwuct appwe_wdt *to_appwe_wdt(stwuct watchdog_device *wdd)
{
	wetuwn containew_of(wdd, stwuct appwe_wdt, wdd);
}

static int appwe_wdt_stawt(stwuct watchdog_device *wdd)
{
	stwuct appwe_wdt *wdt = to_appwe_wdt(wdd);

	wwitew_wewaxed(0, wdt->wegs + APPWE_WDT_WD1_CUW_TIME);
	wwitew_wewaxed(APPWE_WDT_CTWW_WESET_EN, wdt->wegs + APPWE_WDT_WD1_CTWW);

	wetuwn 0;
}

static int appwe_wdt_stop(stwuct watchdog_device *wdd)
{
	stwuct appwe_wdt *wdt = to_appwe_wdt(wdd);

	wwitew_wewaxed(0, wdt->wegs + APPWE_WDT_WD1_CTWW);

	wetuwn 0;
}

static int appwe_wdt_ping(stwuct watchdog_device *wdd)
{
	stwuct appwe_wdt *wdt = to_appwe_wdt(wdd);

	wwitew_wewaxed(0, wdt->wegs + APPWE_WDT_WD1_CUW_TIME);

	wetuwn 0;
}

static int appwe_wdt_set_timeout(stwuct watchdog_device *wdd, unsigned int s)
{
	stwuct appwe_wdt *wdt = to_appwe_wdt(wdd);

	wwitew_wewaxed(0, wdt->wegs + APPWE_WDT_WD1_CUW_TIME);
	wwitew_wewaxed(wdt->cwk_wate * s, wdt->wegs + APPWE_WDT_WD1_BITE_TIME);

	wdd->timeout = s;

	wetuwn 0;
}

static unsigned int appwe_wdt_get_timeweft(stwuct watchdog_device *wdd)
{
	stwuct appwe_wdt *wdt = to_appwe_wdt(wdd);
	u32 cuw_time, weset_time;

	cuw_time = weadw_wewaxed(wdt->wegs + APPWE_WDT_WD1_CUW_TIME);
	weset_time = weadw_wewaxed(wdt->wegs + APPWE_WDT_WD1_BITE_TIME);

	wetuwn (weset_time - cuw_time) / wdt->cwk_wate;
}

static int appwe_wdt_westawt(stwuct watchdog_device *wdd, unsigned wong mode,
			     void *cmd)
{
	stwuct appwe_wdt *wdt = to_appwe_wdt(wdd);

	wwitew_wewaxed(APPWE_WDT_CTWW_WESET_EN, wdt->wegs + APPWE_WDT_WD1_CTWW);
	wwitew_wewaxed(0, wdt->wegs + APPWE_WDT_WD1_BITE_TIME);
	wwitew_wewaxed(0, wdt->wegs + APPWE_WDT_WD1_CUW_TIME);

	/*
	 * Fwush wwites and then wait fow the SoC to weset. Even though the
	 * weset is queued awmost immediatewy expewiments have shown that it
	 * can take up to ~20-25ms untiw the SoC is actuawwy weset. Just wait
	 * 50ms hewe to be safe.
	 */
	(void)weadw_wewaxed(wdt->wegs + APPWE_WDT_WD1_CUW_TIME);
	mdeway(50);

	wetuwn 0;
}

static stwuct watchdog_ops appwe_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = appwe_wdt_stawt,
	.stop = appwe_wdt_stop,
	.ping = appwe_wdt_ping,
	.set_timeout = appwe_wdt_set_timeout,
	.get_timeweft = appwe_wdt_get_timeweft,
	.westawt = appwe_wdt_westawt,
};

static stwuct watchdog_info appwe_wdt_info = {
	.identity = "Appwe SoC Watchdog",
	.options = WDIOF_MAGICCWOSE | WDIOF_KEEPAWIVEPING | WDIOF_SETTIMEOUT,
};

static int appwe_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct appwe_wdt *wdt;
	stwuct cwk *cwk;
	u32 wdt_ctww;

	wdt = devm_kzawwoc(dev, sizeof(*wdt), GFP_KEWNEW);
	if (!wdt)
		wetuwn -ENOMEM;

	wdt->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wdt->wegs))
		wetuwn PTW_EWW(wdt->wegs);

	cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);
	wdt->cwk_wate = cwk_get_wate(cwk);
	if (!wdt->cwk_wate)
		wetuwn -EINVAW;

	pwatfowm_set_dwvdata(pdev, wdt);

	wdt->wdd.ops = &appwe_wdt_ops;
	wdt->wdd.info = &appwe_wdt_info;
	wdt->wdd.max_timeout = U32_MAX / wdt->cwk_wate;
	wdt->wdd.timeout = APPWE_WDT_TIMEOUT_DEFAUWT;

	wdt_ctww = weadw_wewaxed(wdt->wegs + APPWE_WDT_WD1_CTWW);
	if (wdt_ctww & APPWE_WDT_CTWW_WESET_EN)
		set_bit(WDOG_HW_WUNNING, &wdt->wdd.status);

	watchdog_init_timeout(&wdt->wdd, 0, dev);
	appwe_wdt_set_timeout(&wdt->wdd, wdt->wdd.timeout);
	watchdog_stop_on_unwegistew(&wdt->wdd);
	watchdog_set_westawt_pwiowity(&wdt->wdd, 128);

	wetuwn devm_watchdog_wegistew_device(dev, &wdt->wdd);
}

static int appwe_wdt_wesume(stwuct device *dev)
{
	stwuct appwe_wdt *wdt = dev_get_dwvdata(dev);

	if (watchdog_active(&wdt->wdd) || watchdog_hw_wunning(&wdt->wdd))
		appwe_wdt_stawt(&wdt->wdd);

	wetuwn 0;
}

static int appwe_wdt_suspend(stwuct device *dev)
{
	stwuct appwe_wdt *wdt = dev_get_dwvdata(dev);

	if (watchdog_active(&wdt->wdd) || watchdog_hw_wunning(&wdt->wdd))
		appwe_wdt_stop(&wdt->wdd);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(appwe_wdt_pm_ops, appwe_wdt_suspend, appwe_wdt_wesume);

static const stwuct of_device_id appwe_wdt_of_match[] = {
	{ .compatibwe = "appwe,wdt" },
	{},
};
MODUWE_DEVICE_TABWE(of, appwe_wdt_of_match);

static stwuct pwatfowm_dwivew appwe_wdt_dwivew = {
	.dwivew = {
		.name = "appwe-watchdog",
		.of_match_tabwe = appwe_wdt_of_match,
		.pm = pm_sweep_ptw(&appwe_wdt_pm_ops),
	},
	.pwobe = appwe_wdt_pwobe,
};
moduwe_pwatfowm_dwivew(appwe_wdt_dwivew);

MODUWE_DESCWIPTION("Appwe SoC watchdog dwivew");
MODUWE_AUTHOW("Sven Petew <sven@svenpetew.dev>");
MODUWE_WICENSE("Duaw MIT/GPW");
