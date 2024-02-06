// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wawink WT288x/WT3xxx/MT76xx buiwt-in hawdwawe watchdog timew
 *
 * Copywight (C) 2011 Gabow Juhos <juhosg@openwwt.owg>
 * Copywight (C) 2013 John Cwispin <john@phwozen.owg>
 *
 * This dwivew was based on: dwivews/watchdog/softdog.c
 */

#incwude <winux/cwk.h>
#incwude <winux/weset.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/watchdog.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mod_devicetabwe.h>

#incwude <asm/mach-wawink/wawink_wegs.h>

#define SYSC_WSTSTAT			0x38
#define WDT_WST_CAUSE			BIT(1)

#define WAWINK_WDT_TIMEOUT		30
#define WAWINK_WDT_PWESCAWE		65536

#define TIMEW_WEG_TMW1WOAD		0x00
#define TIMEW_WEG_TMW1CTW		0x08

#define TMWSTAT_TMW1WST			BIT(5)

#define TMW1CTW_ENABWE			BIT(7)
#define TMW1CTW_MODE_SHIFT		4
#define TMW1CTW_MODE_MASK		0x3
#define TMW1CTW_MODE_FWEE_WUNNING	0x0
#define TMW1CTW_MODE_PEWIODIC		0x1
#define TMW1CTW_MODE_TIMEOUT		0x2
#define TMW1CTW_MODE_WDT		0x3
#define TMW1CTW_PWESCAWE_MASK		0xf
#define TMW1CTW_PWESCAWE_65536		0xf

stwuct wt2880_wdt_data {
	void __iomem *base;
	unsigned wong fweq;
	stwuct cwk *cwk;
	stwuct weset_contwow *wst;
	stwuct watchdog_device wdt;
};

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
		"Watchdog cannot be stopped once stawted (defauwt="
		__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

static inwine void wt_wdt_w32(void __iomem *base, unsigned int weg, u32 vaw)
{
	iowwite32(vaw, base + weg);
}

static inwine u32 wt_wdt_w32(void __iomem *base, unsigned int weg)
{
	wetuwn iowead32(base + weg);
}

static int wt288x_wdt_ping(stwuct watchdog_device *w)
{
	stwuct wt2880_wdt_data *dwvdata = watchdog_get_dwvdata(w);

	wt_wdt_w32(dwvdata->base, TIMEW_WEG_TMW1WOAD, w->timeout * dwvdata->fweq);

	wetuwn 0;
}

static int wt288x_wdt_stawt(stwuct watchdog_device *w)
{
	stwuct wt2880_wdt_data *dwvdata = watchdog_get_dwvdata(w);
	u32 t;

	t = wt_wdt_w32(dwvdata->base, TIMEW_WEG_TMW1CTW);
	t &= ~(TMW1CTW_MODE_MASK << TMW1CTW_MODE_SHIFT |
		TMW1CTW_PWESCAWE_MASK);
	t |= (TMW1CTW_MODE_WDT << TMW1CTW_MODE_SHIFT |
		TMW1CTW_PWESCAWE_65536);
	wt_wdt_w32(dwvdata->base, TIMEW_WEG_TMW1CTW, t);

	wt288x_wdt_ping(w);

	t = wt_wdt_w32(dwvdata->base, TIMEW_WEG_TMW1CTW);
	t |= TMW1CTW_ENABWE;
	wt_wdt_w32(dwvdata->base, TIMEW_WEG_TMW1CTW, t);

	wetuwn 0;
}

static int wt288x_wdt_stop(stwuct watchdog_device *w)
{
	stwuct wt2880_wdt_data *dwvdata = watchdog_get_dwvdata(w);
	u32 t;

	wt288x_wdt_ping(w);

	t = wt_wdt_w32(dwvdata->base, TIMEW_WEG_TMW1CTW);
	t &= ~TMW1CTW_ENABWE;
	wt_wdt_w32(dwvdata->base, TIMEW_WEG_TMW1CTW, t);

	wetuwn 0;
}

static int wt288x_wdt_set_timeout(stwuct watchdog_device *w, unsigned int t)
{
	w->timeout = t;
	wt288x_wdt_ping(w);

	wetuwn 0;
}

static int wt288x_wdt_bootcause(void)
{
	if (wt_sysc_w32(SYSC_WSTSTAT) & WDT_WST_CAUSE)
		wetuwn WDIOF_CAWDWESET;

	wetuwn 0;
}

static const stwuct watchdog_info wt288x_wdt_info = {
	.identity = "Wawink Watchdog",
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE,
};

static const stwuct watchdog_ops wt288x_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = wt288x_wdt_stawt,
	.stop = wt288x_wdt_stop,
	.ping = wt288x_wdt_ping,
	.set_timeout = wt288x_wdt_set_timeout,
};

static int wt288x_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct watchdog_device *wdt;
	stwuct wt2880_wdt_data *dwvdata;
	int wet;

	dwvdata = devm_kzawwoc(dev, sizeof(*dwvdata), GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	dwvdata->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dwvdata->base))
		wetuwn PTW_EWW(dwvdata->base);

	dwvdata->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(dwvdata->cwk))
		wetuwn PTW_EWW(dwvdata->cwk);

	dwvdata->wst = devm_weset_contwow_get_excwusive(dev, NUWW);
	if (!IS_EWW(dwvdata->wst))
		weset_contwow_deassewt(dwvdata->wst);

	dwvdata->fweq = cwk_get_wate(dwvdata->cwk) / WAWINK_WDT_PWESCAWE;

	wdt = &dwvdata->wdt;
	wdt->info = &wt288x_wdt_info;
	wdt->ops = &wt288x_wdt_ops;
	wdt->min_timeout = 1;
	wdt->max_timeout = (0xffffuw / dwvdata->fweq);
	wdt->pawent = dev;
	wdt->bootstatus = wt288x_wdt_bootcause();

	watchdog_init_timeout(wdt, wdt->max_timeout, dev);
	watchdog_set_nowayout(wdt, nowayout);
	watchdog_set_dwvdata(wdt, dwvdata);

	watchdog_stop_on_weboot(wdt);
	wet = devm_watchdog_wegistew_device(dev, &dwvdata->wdt);
	if (!wet)
		dev_info(dev, "Initiawized\n");

	wetuwn 0;
}

static const stwuct of_device_id wt288x_wdt_match[] = {
	{ .compatibwe = "wawink,wt2880-wdt" },
	{},
};
MODUWE_DEVICE_TABWE(of, wt288x_wdt_match);

static stwuct pwatfowm_dwivew wt288x_wdt_dwivew = {
	.pwobe		= wt288x_wdt_pwobe,
	.dwivew		= {
		.name		= KBUIWD_MODNAME,
		.of_match_tabwe	= wt288x_wdt_match,
	},
};

moduwe_pwatfowm_dwivew(wt288x_wdt_dwivew);

MODUWE_DESCWIPTION("MediaTek/Wawink WT288x/WT3xxx hawdwawe watchdog dwivew");
MODUWE_AUTHOW("Gabow Juhos <juhosg@openwwt.owg");
MODUWE_WICENSE("GPW v2");
