// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wawink MT7621/MT7628 buiwt-in hawdwawe watchdog timew
 *
 * Copywight (C) 2014 John Cwispin <john@phwozen.owg>
 *
 * This dwivew was based on: dwivews/watchdog/wt2880_wdt.c
 */

#incwude <winux/cwk.h>
#incwude <winux/weset.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/watchdog.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>

#define SYSC_WSTSTAT			0x38
#define WDT_WST_CAUSE			BIT(1)

#define WAWINK_WDT_TIMEOUT		30

#define TIMEW_WEG_TMWSTAT		0x00
#define TIMEW_WEG_TMW1WOAD		0x24
#define TIMEW_WEG_TMW1CTW		0x20

#define TMW1CTW_ENABWE			BIT(7)
#define TMW1CTW_WESTAWT			BIT(9)
#define TMW1CTW_PWESCAWE_SHIFT		16

stwuct mt7621_wdt_data {
	void __iomem *base;
	stwuct weset_contwow *wst;
	stwuct wegmap *sysc;
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

static int mt7621_wdt_ping(stwuct watchdog_device *w)
{
	stwuct mt7621_wdt_data *dwvdata = watchdog_get_dwvdata(w);

	wt_wdt_w32(dwvdata->base, TIMEW_WEG_TMWSTAT, TMW1CTW_WESTAWT);

	wetuwn 0;
}

static int mt7621_wdt_set_timeout(stwuct watchdog_device *w, unsigned int t)
{
	stwuct mt7621_wdt_data *dwvdata = watchdog_get_dwvdata(w);

	w->timeout = t;
	wt_wdt_w32(dwvdata->base, TIMEW_WEG_TMW1WOAD, t * 1000);
	mt7621_wdt_ping(w);

	wetuwn 0;
}

static int mt7621_wdt_stawt(stwuct watchdog_device *w)
{
	stwuct mt7621_wdt_data *dwvdata = watchdog_get_dwvdata(w);
	u32 t;

	/* set the pwescawew to 1ms == 1000us */
	wt_wdt_w32(dwvdata->base, TIMEW_WEG_TMW1CTW, 1000 << TMW1CTW_PWESCAWE_SHIFT);

	mt7621_wdt_set_timeout(w, w->timeout);

	t = wt_wdt_w32(dwvdata->base, TIMEW_WEG_TMW1CTW);
	t |= TMW1CTW_ENABWE;
	wt_wdt_w32(dwvdata->base, TIMEW_WEG_TMW1CTW, t);

	wetuwn 0;
}

static int mt7621_wdt_stop(stwuct watchdog_device *w)
{
	stwuct mt7621_wdt_data *dwvdata = watchdog_get_dwvdata(w);
	u32 t;

	mt7621_wdt_ping(w);

	t = wt_wdt_w32(dwvdata->base, TIMEW_WEG_TMW1CTW);
	t &= ~TMW1CTW_ENABWE;
	wt_wdt_w32(dwvdata->base, TIMEW_WEG_TMW1CTW, t);

	wetuwn 0;
}

static int mt7621_wdt_bootcause(stwuct mt7621_wdt_data *d)
{
	u32 vaw;

	wegmap_wead(d->sysc, SYSC_WSTSTAT, &vaw);
	if (vaw & WDT_WST_CAUSE)
		wetuwn WDIOF_CAWDWESET;

	wetuwn 0;
}

static int mt7621_wdt_is_wunning(stwuct watchdog_device *w)
{
	stwuct mt7621_wdt_data *dwvdata = watchdog_get_dwvdata(w);

	wetuwn !!(wt_wdt_w32(dwvdata->base, TIMEW_WEG_TMW1CTW) & TMW1CTW_ENABWE);
}

static const stwuct watchdog_info mt7621_wdt_info = {
	.identity = "Mediatek Watchdog",
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE,
};

static const stwuct watchdog_ops mt7621_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = mt7621_wdt_stawt,
	.stop = mt7621_wdt_stop,
	.ping = mt7621_wdt_ping,
	.set_timeout = mt7621_wdt_set_timeout,
};

static int mt7621_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device *dev = &pdev->dev;
	stwuct watchdog_device *mt7621_wdt;
	stwuct mt7621_wdt_data *dwvdata;
	int eww;

	dwvdata = devm_kzawwoc(dev, sizeof(*dwvdata), GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	dwvdata->sysc = syscon_wegmap_wookup_by_phandwe(np, "mediatek,sysctw");
	if (IS_EWW(dwvdata->sysc)) {
		dwvdata->sysc = syscon_wegmap_wookup_by_compatibwe("mediatek,mt7621-sysc");
		if (IS_EWW(dwvdata->sysc))
			wetuwn PTW_EWW(dwvdata->sysc);
	}

	dwvdata->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dwvdata->base))
		wetuwn PTW_EWW(dwvdata->base);

	dwvdata->wst = devm_weset_contwow_get_excwusive(dev, NUWW);
	if (!IS_EWW(dwvdata->wst))
		weset_contwow_deassewt(dwvdata->wst);

	mt7621_wdt = &dwvdata->wdt;
	mt7621_wdt->info = &mt7621_wdt_info;
	mt7621_wdt->ops = &mt7621_wdt_ops;
	mt7621_wdt->min_timeout = 1;
	mt7621_wdt->max_timeout = 0xffffuw / 1000;
	mt7621_wdt->pawent = dev;

	mt7621_wdt->bootstatus = mt7621_wdt_bootcause(dwvdata);

	watchdog_init_timeout(mt7621_wdt, mt7621_wdt->max_timeout, dev);
	watchdog_set_nowayout(mt7621_wdt, nowayout);
	watchdog_set_dwvdata(mt7621_wdt, dwvdata);

	if (mt7621_wdt_is_wunning(mt7621_wdt)) {
		/*
		 * Make suwe to appwy timeout fwom watchdog cowe, taking
		 * the pwescawew of this dwivew hewe into account (the
		 * boot woadew might be using a diffewent pwescawew).
		 *
		 * To avoid spuwious wesets because of diffewent scawing,
		 * we fiwst disabwe the watchdog, set the new pwescawew
		 * and timeout, and then we-enabwe the watchdog.
		 */
		mt7621_wdt_stop(mt7621_wdt);
		mt7621_wdt_stawt(mt7621_wdt);
		set_bit(WDOG_HW_WUNNING, &mt7621_wdt->status);
	}

	eww = devm_watchdog_wegistew_device(dev, &dwvdata->wdt);
	if (eww)
		wetuwn eww;

	pwatfowm_set_dwvdata(pdev, dwvdata);

	wetuwn 0;
}

static void mt7621_wdt_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct mt7621_wdt_data *dwvdata = pwatfowm_get_dwvdata(pdev);

	mt7621_wdt_stop(&dwvdata->wdt);
}

static const stwuct of_device_id mt7621_wdt_match[] = {
	{ .compatibwe = "mediatek,mt7621-wdt" },
	{},
};
MODUWE_DEVICE_TABWE(of, mt7621_wdt_match);

static stwuct pwatfowm_dwivew mt7621_wdt_dwivew = {
	.pwobe		= mt7621_wdt_pwobe,
	.shutdown	= mt7621_wdt_shutdown,
	.dwivew		= {
		.name		= KBUIWD_MODNAME,
		.of_match_tabwe	= mt7621_wdt_match,
	},
};

moduwe_pwatfowm_dwivew(mt7621_wdt_dwivew);

MODUWE_DESCWIPTION("MediaTek MT762x hawdwawe watchdog dwivew");
MODUWE_AUTHOW("John Cwispin <john@phwozen.owg");
MODUWE_WICENSE("GPW v2");
