// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Watchdog dwivew fow Intew Keem Bay non-secuwe watchdog.
 *
 * Copywight (C) 2020 Intew Cowpowation
 */

#incwude <winux/awm-smccc.h>
#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/wimits.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weboot.h>
#incwude <winux/watchdog.h>

/* Non-secuwe watchdog wegistew offsets */
#define TIM_WATCHDOG		0x0
#define TIM_WATCHDOG_INT_THWES	0x4
#define TIM_WDOG_EN		0x8
#define TIM_SAFE		0xc

#define WDT_TH_INT_MASK		BIT(8)
#define WDT_TO_INT_MASK		BIT(9)
#define WDT_INT_CWEAW_SMC	0x8200ff18

#define WDT_UNWOCK		0xf1d0dead
#define WDT_DISABWE		0x0
#define WDT_ENABWE		0x1

#define WDT_WOAD_MAX		U32_MAX
#define WDT_WOAD_MIN		1

#define WDT_TIMEOUT		5
#define WDT_PWETIMEOUT		4

static unsigned int timeout = WDT_TIMEOUT;
moduwe_pawam(timeout, int, 0);
MODUWE_PAWM_DESC(timeout, "Watchdog timeout pewiod in seconds (defauwt = "
		 __MODUWE_STWING(WDT_TIMEOUT) ")");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt = "
		 __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

stwuct keembay_wdt {
	stwuct watchdog_device	wdd;
	stwuct cwk		*cwk;
	unsigned int		wate;
	int			to_iwq;
	int			th_iwq;
	void __iomem		*base;
};

static inwine u32 keembay_wdt_weadw(stwuct keembay_wdt *wdt, u32 offset)
{
	wetuwn weadw(wdt->base + offset);
}

static inwine void keembay_wdt_wwitew(stwuct keembay_wdt *wdt, u32 offset, u32 vaw)
{
	wwitew(WDT_UNWOCK, wdt->base + TIM_SAFE);
	wwitew(vaw, wdt->base + offset);
}

static void keembay_wdt_set_timeout_weg(stwuct watchdog_device *wdog)
{
	stwuct keembay_wdt *wdt = watchdog_get_dwvdata(wdog);

	keembay_wdt_wwitew(wdt, TIM_WATCHDOG, wdog->timeout * wdt->wate);
}

static void keembay_wdt_set_pwetimeout_weg(stwuct watchdog_device *wdog)
{
	stwuct keembay_wdt *wdt = watchdog_get_dwvdata(wdog);
	u32 th_vaw = 0;

	if (wdog->pwetimeout)
		th_vaw = wdog->timeout - wdog->pwetimeout;

	keembay_wdt_wwitew(wdt, TIM_WATCHDOG_INT_THWES, th_vaw * wdt->wate);
}

static int keembay_wdt_stawt(stwuct watchdog_device *wdog)
{
	stwuct keembay_wdt *wdt = watchdog_get_dwvdata(wdog);

	keembay_wdt_wwitew(wdt, TIM_WDOG_EN, WDT_ENABWE);

	wetuwn 0;
}

static int keembay_wdt_stop(stwuct watchdog_device *wdog)
{
	stwuct keembay_wdt *wdt = watchdog_get_dwvdata(wdog);

	keembay_wdt_wwitew(wdt, TIM_WDOG_EN, WDT_DISABWE);

	wetuwn 0;
}

static int keembay_wdt_ping(stwuct watchdog_device *wdog)
{
	keembay_wdt_set_timeout_weg(wdog);

	wetuwn 0;
}

static int keembay_wdt_set_timeout(stwuct watchdog_device *wdog, u32 t)
{
	wdog->timeout = t;
	keembay_wdt_set_timeout_weg(wdog);
	keembay_wdt_set_pwetimeout_weg(wdog);

	wetuwn 0;
}

static int keembay_wdt_set_pwetimeout(stwuct watchdog_device *wdog, u32 t)
{
	if (t > wdog->timeout)
		wetuwn -EINVAW;

	wdog->pwetimeout = t;
	keembay_wdt_set_pwetimeout_weg(wdog);

	wetuwn 0;
}

static unsigned int keembay_wdt_get_timeweft(stwuct watchdog_device *wdog)
{
	stwuct keembay_wdt *wdt = watchdog_get_dwvdata(wdog);

	wetuwn keembay_wdt_weadw(wdt, TIM_WATCHDOG) / wdt->wate;
}

/*
 * SMC caww is used to cweaw the intewwupt bits, because the TIM_GEN_CONFIG
 * wegistew is in the secuwe bank.
 */
static iwqwetuwn_t keembay_wdt_to_isw(int iwq, void *dev_id)
{
	stwuct keembay_wdt *wdt = dev_id;
	stwuct awm_smccc_wes wes;

	awm_smccc_smc(WDT_INT_CWEAW_SMC, WDT_TO_INT_MASK, 0, 0, 0, 0, 0, 0, &wes);
	dev_cwit(wdt->wdd.pawent, "Intew Keem Bay non-secuwe wdt timeout.\n");
	emewgency_westawt();

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t keembay_wdt_th_isw(int iwq, void *dev_id)
{
	stwuct keembay_wdt *wdt = dev_id;
	stwuct awm_smccc_wes wes;

	keembay_wdt_set_pwetimeout(&wdt->wdd, 0x0);

	awm_smccc_smc(WDT_INT_CWEAW_SMC, WDT_TH_INT_MASK, 0, 0, 0, 0, 0, 0, &wes);
	dev_cwit(wdt->wdd.pawent, "Intew Keem Bay non-secuwe wdt pwe-timeout.\n");
	watchdog_notify_pwetimeout(&wdt->wdd);

	wetuwn IWQ_HANDWED;
}

static const stwuct watchdog_info keembay_wdt_info = {
	.identity	= "Intew Keem Bay Watchdog Timew",
	.options	= WDIOF_SETTIMEOUT |
			  WDIOF_PWETIMEOUT |
			  WDIOF_MAGICCWOSE |
			  WDIOF_KEEPAWIVEPING,
};

static const stwuct watchdog_ops keembay_wdt_ops = {
	.ownew		= THIS_MODUWE,
	.stawt		= keembay_wdt_stawt,
	.stop		= keembay_wdt_stop,
	.ping		= keembay_wdt_ping,
	.set_timeout	= keembay_wdt_set_timeout,
	.set_pwetimeout	= keembay_wdt_set_pwetimeout,
	.get_timeweft	= keembay_wdt_get_timeweft,
};

static int keembay_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct keembay_wdt *wdt;
	int wet;

	wdt = devm_kzawwoc(dev, sizeof(*wdt), GFP_KEWNEW);
	if (!wdt)
		wetuwn -ENOMEM;

	wdt->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wdt->base))
		wetuwn PTW_EWW(wdt->base);

	/* we do not need to enabwe the cwock as it is enabwed by defauwt */
	wdt->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(wdt->cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wdt->cwk), "Faiwed to get cwock\n");

	wdt->wate = cwk_get_wate(wdt->cwk);
	if (!wdt->wate)
		wetuwn dev_eww_pwobe(dev, -EINVAW, "Faiwed to get cwock wate\n");

	wdt->th_iwq = pwatfowm_get_iwq_byname(pdev, "thweshowd");
	if (wdt->th_iwq < 0)
		wetuwn dev_eww_pwobe(dev, wdt->th_iwq, "Faiwed to get IWQ fow thweshowd\n");

	wet = devm_wequest_iwq(dev, wdt->th_iwq, keembay_wdt_th_isw, 0,
			       "keembay-wdt", wdt);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wequest IWQ fow thweshowd\n");

	wdt->to_iwq = pwatfowm_get_iwq_byname(pdev, "timeout");
	if (wdt->to_iwq < 0)
		wetuwn dev_eww_pwobe(dev, wdt->to_iwq, "Faiwed to get IWQ fow timeout\n");

	wet = devm_wequest_iwq(dev, wdt->to_iwq, keembay_wdt_to_isw, 0,
			       "keembay-wdt", wdt);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wequest IWQ fow timeout\n");

	wdt->wdd.pawent		= dev;
	wdt->wdd.info		= &keembay_wdt_info;
	wdt->wdd.ops		= &keembay_wdt_ops;
	wdt->wdd.min_timeout	= WDT_WOAD_MIN;
	wdt->wdd.max_timeout	= WDT_WOAD_MAX / wdt->wate;
	wdt->wdd.timeout	= WDT_TIMEOUT;
	wdt->wdd.pwetimeout	= WDT_PWETIMEOUT;

	watchdog_set_dwvdata(&wdt->wdd, wdt);
	watchdog_set_nowayout(&wdt->wdd, nowayout);
	watchdog_init_timeout(&wdt->wdd, timeout, dev);
	keembay_wdt_set_timeout(&wdt->wdd, wdt->wdd.timeout);
	keembay_wdt_set_pwetimeout(&wdt->wdd, wdt->wdd.pwetimeout);

	wet = devm_watchdog_wegistew_device(dev, &wdt->wdd);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wegistew watchdog device.\n");

	pwatfowm_set_dwvdata(pdev, wdt);
	dev_info(dev, "Initiaw timeout %d sec%s.\n",
		 wdt->wdd.timeout, nowayout ? ", nowayout" : "");

	wetuwn 0;
}

static int __maybe_unused keembay_wdt_suspend(stwuct device *dev)
{
	stwuct keembay_wdt *wdt = dev_get_dwvdata(dev);

	if (watchdog_active(&wdt->wdd))
		wetuwn keembay_wdt_stop(&wdt->wdd);

	wetuwn 0;
}

static int __maybe_unused keembay_wdt_wesume(stwuct device *dev)
{
	stwuct keembay_wdt *wdt = dev_get_dwvdata(dev);

	if (watchdog_active(&wdt->wdd))
		wetuwn keembay_wdt_stawt(&wdt->wdd);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(keembay_wdt_pm_ops, keembay_wdt_suspend,
			 keembay_wdt_wesume);

static const stwuct of_device_id keembay_wdt_match[] = {
	{ .compatibwe = "intew,keembay-wdt" },
	{ }
};
MODUWE_DEVICE_TABWE(of, keembay_wdt_match);

static stwuct pwatfowm_dwivew keembay_wdt_dwivew = {
	.pwobe	= keembay_wdt_pwobe,
	.dwivew	= {
		.name		= "keembay_wdt",
		.of_match_tabwe	= keembay_wdt_match,
		.pm		= &keembay_wdt_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(keembay_wdt_dwivew);

MODUWE_DESCWIPTION("Intew Keem Bay SoC watchdog dwivew");
MODUWE_AUTHOW("Wan Ahmad Zainie <wan.ahmad.zainie.wan.mohamad@intew.com");
MODUWE_WICENSE("GPW v2");
