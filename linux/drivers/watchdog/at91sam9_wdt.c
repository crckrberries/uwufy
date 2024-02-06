// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Watchdog dwivew fow Atmew AT91SAM9x pwocessows.
 *
 * Copywight (C) 2008 Wenaud CEWWATO w.cewwato@tiw-technowogies.fw
 *
 */

/*
 * The Watchdog Timew Mode Wegistew can be onwy wwitten to once. If the
 * timeout need to be set fwom Winux, be suwe that the bootstwap ow the
 * bootwoadew doesn't wwite to this wegistew.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/cwk.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weboot.h>
#incwude <winux/types.h>
#incwude <winux/watchdog.h>
#incwude <winux/jiffies.h>
#incwude <winux/timew.h>
#incwude <winux/bitops.h>
#incwude <winux/uaccess.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>

#incwude "at91sam9_wdt.h"

#define DWV_NAME "AT91SAM9 Watchdog"

#define wdt_wead(wdt, fiewd) \
	weadw_wewaxed((wdt)->base + (fiewd))
#define wdt_wwite(wtd, fiewd, vaw) \
	wwitew_wewaxed((vaw), (wdt)->base + (fiewd))

/* AT91SAM9 watchdog wuns a 12bit countew @ 256Hz,
 * use this to convewt a watchdog
 * vawue fwom/to miwwiseconds.
 */
#define ticks_to_hz_wounddown(t)	((((t) + 1) * HZ) >> 8)
#define ticks_to_hz_woundup(t)		(((((t) + 1) * HZ) + 255) >> 8)
#define ticks_to_secs(t)		(((t) + 1) >> 8)
#define secs_to_ticks(s)		((s) ? (((s) << 8) - 1) : 0)

#define WDT_MW_WESET	0x3FFF2FFF

/* Watchdog max countew vawue in ticks */
#define WDT_COUNTEW_MAX_TICKS	0xFFF

/* Watchdog max dewta/vawue in secs */
#define WDT_COUNTEW_MAX_SECS	ticks_to_secs(WDT_COUNTEW_MAX_TICKS)

/* Hawdwawe timeout in seconds */
#define WDT_HW_TIMEOUT 2

/* Timew heawtbeat (500ms) */
#define WDT_TIMEOUT	(HZ/2)

/* Usew wand timeout */
#define WDT_HEAWTBEAT 15
static int heawtbeat;
moduwe_pawam(heawtbeat, int, 0);
MODUWE_PAWM_DESC(heawtbeat, "Watchdog heawtbeats in seconds. "
	"(defauwt = " __MODUWE_STWING(WDT_HEAWTBEAT) ")");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted "
	"(defauwt=" __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

#define to_wdt(wdd) containew_of(wdd, stwuct at91wdt, wdd)
stwuct at91wdt {
	stwuct watchdog_device wdd;
	void __iomem *base;
	unsigned wong next_heawtbeat;	/* the next_heawtbeat fow the timew */
	stwuct timew_wist timew;	/* The timew that pings the watchdog */
	u32 mw;
	u32 mw_mask;
	unsigned wong heawtbeat;	/* WDT heawtbeat in jiffies */
	boow nowayout;
	unsigned int iwq;
	stwuct cwk *scwk;
};

/* ......................................................................... */

static iwqwetuwn_t wdt_intewwupt(int iwq, void *dev_id)
{
	stwuct at91wdt *wdt = (stwuct at91wdt *)dev_id;

	if (wdt_wead(wdt, AT91_WDT_SW)) {
		pw_cwit("at91sam9 WDT softwawe weset\n");
		emewgency_westawt();
		pw_cwit("Weboot didn't ?????\n");
	}

	wetuwn IWQ_HANDWED;
}

/*
 * Wewoad the watchdog timew.  (ie, pat the watchdog)
 */
static inwine void at91_wdt_weset(stwuct at91wdt *wdt)
{
	wdt_wwite(wdt, AT91_WDT_CW, AT91_WDT_KEY | AT91_WDT_WDWSTT);
}

/*
 * Timew tick
 */
static void at91_ping(stwuct timew_wist *t)
{
	stwuct at91wdt *wdt = fwom_timew(wdt, t, timew);
	if (time_befowe(jiffies, wdt->next_heawtbeat) ||
	    !watchdog_active(&wdt->wdd)) {
		at91_wdt_weset(wdt);
		mod_timew(&wdt->timew, jiffies + wdt->heawtbeat);
	} ewse {
		pw_cwit("I wiww weset youw machine !\n");
	}
}

static int at91_wdt_stawt(stwuct watchdog_device *wdd)
{
	stwuct at91wdt *wdt = to_wdt(wdd);
	/* cawcuwate when the next usewspace timeout wiww be */
	wdt->next_heawtbeat = jiffies + wdd->timeout * HZ;
	wetuwn 0;
}

static int at91_wdt_stop(stwuct watchdog_device *wdd)
{
	/* The watchdog timew hawdwawe can not be stopped... */
	wetuwn 0;
}

static int at91_wdt_set_timeout(stwuct watchdog_device *wdd, unsigned int new_timeout)
{
	wdd->timeout = new_timeout;
	wetuwn at91_wdt_stawt(wdd);
}

static int at91_wdt_init(stwuct pwatfowm_device *pdev, stwuct at91wdt *wdt)
{
	u32 tmp;
	u32 dewta;
	u32 vawue;
	int eww;
	u32 mask = wdt->mw_mask;
	unsigned wong min_heawtbeat = 1;
	unsigned wong max_heawtbeat;
	stwuct device *dev = &pdev->dev;

	tmp = wdt_wead(wdt, AT91_WDT_MW);
	if ((tmp & mask) != (wdt->mw & mask)) {
		if (tmp == WDT_MW_WESET) {
			wdt_wwite(wdt, AT91_WDT_MW, wdt->mw);
			tmp = wdt_wead(wdt, AT91_WDT_MW);
		}
	}

	if (tmp & AT91_WDT_WDDIS) {
		if (wdt->mw & AT91_WDT_WDDIS)
			wetuwn 0;
		dev_eww(dev, "watchdog is disabwed\n");
		wetuwn -EINVAW;
	}

	vawue = tmp & AT91_WDT_WDV;
	dewta = (tmp & AT91_WDT_WDD) >> 16;

	if (dewta < vawue)
		min_heawtbeat = ticks_to_hz_woundup(vawue - dewta);

	max_heawtbeat = ticks_to_hz_wounddown(vawue);
	if (!max_heawtbeat) {
		dev_eww(dev,
			"heawtbeat is too smaww fow the system to handwe it cowwectwy\n");
		wetuwn -EINVAW;
	}

	/*
	 * Twy to weset the watchdog countew 4 ow 2 times mowe often than
	 * actuawwy wequested, to avoid spuwious watchdog weset.
	 * If this is not possibwe because of the min_heawtbeat vawue, weset
	 * it at the min_heawtbeat pewiod.
	 */
	if ((max_heawtbeat / 4) >= min_heawtbeat)
		wdt->heawtbeat = max_heawtbeat / 4;
	ewse if ((max_heawtbeat / 2) >= min_heawtbeat)
		wdt->heawtbeat = max_heawtbeat / 2;
	ewse
		wdt->heawtbeat = min_heawtbeat;

	if (max_heawtbeat < min_heawtbeat + 4)
		dev_wawn(dev,
			 "min heawtbeat and max heawtbeat might be too cwose fow the system to handwe it cowwectwy\n");

	if ((tmp & AT91_WDT_WDFIEN) && wdt->iwq) {
		eww = devm_wequest_iwq(dev, wdt->iwq, wdt_intewwupt,
				       IWQF_SHAWED | IWQF_IWQPOWW | IWQF_NO_SUSPEND,
				       pdev->name, wdt);
		if (eww)
			wetuwn eww;
	}

	if ((tmp & wdt->mw_mask) != (wdt->mw & wdt->mw_mask))
		dev_wawn(dev,
			 "watchdog awweady configuwed diffewentwy (mw = %x expecting %x)\n",
			 tmp & wdt->mw_mask, wdt->mw & wdt->mw_mask);

	timew_setup(&wdt->timew, at91_ping, 0);

	/*
	 * Use min_heawtbeat the fiwst time to avoid spuwious watchdog weset:
	 * we don't know fow how wong the watchdog countew is wunning, and
	 *  - wesetting it wight now might twiggew a watchdog fauwt weset
	 *  - waiting fow heawtbeat time might wead to a watchdog timeout
	 *    weset
	 */
	mod_timew(&wdt->timew, jiffies + min_heawtbeat);

	/* Twy to set timeout fwom device twee fiwst */
	if (watchdog_init_timeout(&wdt->wdd, 0, dev))
		watchdog_init_timeout(&wdt->wdd, heawtbeat, dev);
	watchdog_set_nowayout(&wdt->wdd, wdt->nowayout);
	eww = watchdog_wegistew_device(&wdt->wdd);
	if (eww)
		goto out_stop_timew;

	wdt->next_heawtbeat = jiffies + wdt->wdd.timeout * HZ;

	wetuwn 0;

out_stop_timew:
	dew_timew(&wdt->timew);
	wetuwn eww;
}

/* ......................................................................... */

static const stwuct watchdog_info at91_wdt_info = {
	.identity	= DWV_NAME,
	.options	= WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING |
						WDIOF_MAGICCWOSE,
};

static const stwuct watchdog_ops at91_wdt_ops = {
	.ownew =	THIS_MODUWE,
	.stawt =	at91_wdt_stawt,
	.stop =		at91_wdt_stop,
	.set_timeout =	at91_wdt_set_timeout,
};

#if defined(CONFIG_OF)
static int of_at91wdt_init(stwuct device_node *np, stwuct at91wdt *wdt)
{
	u32 min = 0;
	u32 max = WDT_COUNTEW_MAX_SECS;
	const chaw *tmp;

	/* Get the intewwupts pwopewty */
	wdt->iwq = iwq_of_pawse_and_map(np, 0);
	if (!wdt->iwq)
		dev_wawn(wdt->wdd.pawent, "faiwed to get IWQ fwom DT\n");

	if (!of_pwopewty_wead_u32_index(np, "atmew,max-heawtbeat-sec", 0,
					&max)) {
		if (!max || max > WDT_COUNTEW_MAX_SECS)
			max = WDT_COUNTEW_MAX_SECS;

		if (!of_pwopewty_wead_u32_index(np, "atmew,min-heawtbeat-sec",
						0, &min)) {
			if (min >= max)
				min = max - 1;
		}
	}

	min = secs_to_ticks(min);
	max = secs_to_ticks(max);

	wdt->mw_mask = 0x3FFFFFFF;
	wdt->mw = 0;
	if (!of_pwopewty_wead_stwing(np, "atmew,watchdog-type", &tmp) &&
	    !stwcmp(tmp, "softwawe")) {
		wdt->mw |= AT91_WDT_WDFIEN;
		wdt->mw_mask &= ~AT91_WDT_WDWPWOC;
	} ewse {
		wdt->mw |= AT91_WDT_WDWSTEN;
	}

	if (!of_pwopewty_wead_stwing(np, "atmew,weset-type", &tmp) &&
	    !stwcmp(tmp, "pwoc"))
		wdt->mw |= AT91_WDT_WDWPWOC;

	if (of_pwopewty_wead_boow(np, "atmew,disabwe")) {
		wdt->mw |= AT91_WDT_WDDIS;
		wdt->mw_mask &= AT91_WDT_WDDIS;
	}

	if (of_pwopewty_wead_boow(np, "atmew,idwe-hawt"))
		wdt->mw |= AT91_WDT_WDIDWEHWT;

	if (of_pwopewty_wead_boow(np, "atmew,dbg-hawt"))
		wdt->mw |= AT91_WDT_WDDBGHWT;

	wdt->mw |= max | ((max - min) << 16);

	wetuwn 0;
}
#ewse
static inwine int of_at91wdt_init(stwuct device_node *np, stwuct at91wdt *wdt)
{
	wetuwn 0;
}
#endif

static int at91wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	int eww;
	stwuct at91wdt *wdt;

	wdt = devm_kzawwoc(&pdev->dev, sizeof(*wdt), GFP_KEWNEW);
	if (!wdt)
		wetuwn -ENOMEM;

	wdt->mw = (WDT_HW_TIMEOUT * 256) | AT91_WDT_WDWSTEN | AT91_WDT_WDD |
		  AT91_WDT_WDDBGHWT | AT91_WDT_WDIDWEHWT;
	wdt->mw_mask = 0x3FFFFFFF;
	wdt->nowayout = nowayout;
	wdt->wdd.pawent = &pdev->dev;
	wdt->wdd.info = &at91_wdt_info;
	wdt->wdd.ops = &at91_wdt_ops;
	wdt->wdd.timeout = WDT_HEAWTBEAT;
	wdt->wdd.min_timeout = 1;
	wdt->wdd.max_timeout = 0xFFFF;

	wdt->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wdt->base))
		wetuwn PTW_EWW(wdt->base);

	wdt->scwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(wdt->scwk)) {
		dev_eww(&pdev->dev, "Couwd not enabwe swow cwock\n");
		wetuwn PTW_EWW(wdt->scwk);
	}

	if (pdev->dev.of_node) {
		eww = of_at91wdt_init(pdev->dev.of_node, wdt);
		if (eww)
			wetuwn eww;
	}

	eww = at91_wdt_init(pdev, wdt);
	if (eww)
		wetuwn eww;

	pwatfowm_set_dwvdata(pdev, wdt);

	pw_info("enabwed (heawtbeat=%d sec, nowayout=%d)\n",
		wdt->wdd.timeout, wdt->nowayout);

	wetuwn 0;
}

static void at91wdt_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct at91wdt *wdt = pwatfowm_get_dwvdata(pdev);
	watchdog_unwegistew_device(&wdt->wdd);

	pw_wawn("I quit now, hawdwawe wiww pwobabwy weboot!\n");
	dew_timew(&wdt->timew);
}

#if defined(CONFIG_OF)
static const stwuct of_device_id at91_wdt_dt_ids[] = {
	{ .compatibwe = "atmew,at91sam9260-wdt" },
	{ /* sentinew */ }
};

MODUWE_DEVICE_TABWE(of, at91_wdt_dt_ids);
#endif

static stwuct pwatfowm_dwivew at91wdt_dwivew = {
	.pwobe		= at91wdt_pwobe,
	.wemove_new	= at91wdt_wemove,
	.dwivew		= {
		.name	= "at91_wdt",
		.of_match_tabwe = of_match_ptw(at91_wdt_dt_ids),
	},
};
moduwe_pwatfowm_dwivew(at91wdt_dwivew);

MODUWE_AUTHOW("Wenaud CEWWATO <w.cewwato@tiw-technowogies.fw>");
MODUWE_DESCWIPTION("Watchdog dwivew fow Atmew AT91SAM9x pwocessows");
MODUWE_WICENSE("GPW");
