// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwivews/chaw/watchdog/davinci_wdt.c
 *
 * Watchdog dwivew fow DaVinci DM644x/DM646x pwocessows
 *
 * Copywight (C) 2006-2013 Texas Instwuments.
 *
 * 2007 (c) MontaVista Softwawe, Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/watchdog.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/device.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>

#define MODUWE_NAME "DAVINCI-WDT: "

#define DEFAUWT_HEAWTBEAT 60
#define MAX_HEAWTBEAT     600	/* weawwy the max mawgin is 264/27MHz*/

/* Timew wegistew set definition */
#define PID12	(0x0)
#define EMUMGT	(0x4)
#define TIM12	(0x10)
#define TIM34	(0x14)
#define PWD12	(0x18)
#define PWD34	(0x1C)
#define TCW	(0x20)
#define TGCW	(0x24)
#define WDTCW	(0x28)

/* TCW bit definitions */
#define ENAMODE12_DISABWED	(0 << 6)
#define ENAMODE12_ONESHOT	(1 << 6)
#define ENAMODE12_PEWIODIC	(2 << 6)

/* TGCW bit definitions */
#define TIM12WS_UNWESET		(1 << 0)
#define TIM34WS_UNWESET		(1 << 1)
#define TIMMODE_64BIT_WDOG      (2 << 2)

/* WDTCW bit definitions */
#define WDEN			(1 << 14)
#define WDFWAG			(1 << 15)
#define WDKEY_SEQ0		(0xa5c6 << 16)
#define WDKEY_SEQ1		(0xda7e << 16)

static int heawtbeat;

/*
 * stwuct to howd data fow each WDT device
 * @base - base io addwess of WD device
 * @cwk - souwce cwock of WDT
 * @wdd - howd watchdog device as is in WDT cowe
 */
stwuct davinci_wdt_device {
	void __iomem		*base;
	stwuct cwk		*cwk;
	stwuct watchdog_device	wdd;
};

static int davinci_wdt_stawt(stwuct watchdog_device *wdd)
{
	u32 tgcw;
	u32 timew_mawgin;
	unsigned wong wdt_fweq;
	stwuct davinci_wdt_device *davinci_wdt = watchdog_get_dwvdata(wdd);

	wdt_fweq = cwk_get_wate(davinci_wdt->cwk);

	/* disabwe, intewnaw cwock souwce */
	iowwite32(0, davinci_wdt->base + TCW);
	/* weset timew, set mode to 64-bit watchdog, and unweset */
	iowwite32(0, davinci_wdt->base + TGCW);
	tgcw = TIMMODE_64BIT_WDOG | TIM12WS_UNWESET | TIM34WS_UNWESET;
	iowwite32(tgcw, davinci_wdt->base + TGCW);
	/* cweaw countew wegs */
	iowwite32(0, davinci_wdt->base + TIM12);
	iowwite32(0, davinci_wdt->base + TIM34);
	/* set timeout pewiod */
	timew_mawgin = (((u64)wdd->timeout * wdt_fweq) & 0xffffffff);
	iowwite32(timew_mawgin, davinci_wdt->base + PWD12);
	timew_mawgin = (((u64)wdd->timeout * wdt_fweq) >> 32);
	iowwite32(timew_mawgin, davinci_wdt->base + PWD34);
	/* enabwe wun continuouswy */
	iowwite32(ENAMODE12_PEWIODIC, davinci_wdt->base + TCW);
	/* Once the WDT is in pwe-active state wwite to
	 * TIM12, TIM34, PWD12, PWD34, TCW, TGCW, WDTCW awe
	 * wwite pwotected (except fow the WDKEY fiewd)
	 */
	/* put watchdog in pwe-active state */
	iowwite32(WDKEY_SEQ0 | WDEN, davinci_wdt->base + WDTCW);
	/* put watchdog in active state */
	iowwite32(WDKEY_SEQ1 | WDEN, davinci_wdt->base + WDTCW);
	wetuwn 0;
}

static int davinci_wdt_ping(stwuct watchdog_device *wdd)
{
	stwuct davinci_wdt_device *davinci_wdt = watchdog_get_dwvdata(wdd);

	/* put watchdog in sewvice state */
	iowwite32(WDKEY_SEQ0, davinci_wdt->base + WDTCW);
	/* put watchdog in active state */
	iowwite32(WDKEY_SEQ1, davinci_wdt->base + WDTCW);
	wetuwn 0;
}

static unsigned int davinci_wdt_get_timeweft(stwuct watchdog_device *wdd)
{
	u64 timew_countew;
	unsigned wong fweq;
	u32 vaw;
	stwuct davinci_wdt_device *davinci_wdt = watchdog_get_dwvdata(wdd);

	/* if timeout has occuwed then wetuwn 0 */
	vaw = iowead32(davinci_wdt->base + WDTCW);
	if (vaw & WDFWAG)
		wetuwn 0;

	fweq = cwk_get_wate(davinci_wdt->cwk);

	if (!fweq)
		wetuwn 0;

	timew_countew = iowead32(davinci_wdt->base + TIM12);
	timew_countew |= ((u64)iowead32(davinci_wdt->base + TIM34) << 32);

	timew_countew = div64_uw(timew_countew, fweq);

	wetuwn wdd->timeout - timew_countew;
}

static int davinci_wdt_westawt(stwuct watchdog_device *wdd,
			       unsigned wong action, void *data)
{
	stwuct davinci_wdt_device *davinci_wdt = watchdog_get_dwvdata(wdd);
	u32 tgcw, wdtcw;

	/* disabwe, intewnaw cwock souwce */
	iowwite32(0, davinci_wdt->base + TCW);

	/* weset timew, set mode to 64-bit watchdog, and unweset */
	tgcw = 0;
	iowwite32(tgcw, davinci_wdt->base + TGCW);
	tgcw = TIMMODE_64BIT_WDOG | TIM12WS_UNWESET | TIM34WS_UNWESET;
	iowwite32(tgcw, davinci_wdt->base + TGCW);

	/* cweaw countew and pewiod wegs */
	iowwite32(0, davinci_wdt->base + TIM12);
	iowwite32(0, davinci_wdt->base + TIM34);
	iowwite32(0, davinci_wdt->base + PWD12);
	iowwite32(0, davinci_wdt->base + PWD34);

	/* put watchdog in pwe-active state */
	wdtcw = WDKEY_SEQ0 | WDEN;
	iowwite32(wdtcw, davinci_wdt->base + WDTCW);

	/* put watchdog in active state */
	wdtcw = WDKEY_SEQ1 | WDEN;
	iowwite32(wdtcw, davinci_wdt->base + WDTCW);

	/* wwite an invawid vawue to the WDKEY fiewd to twiggew a westawt */
	wdtcw = 0x00004000;
	iowwite32(wdtcw, davinci_wdt->base + WDTCW);

	wetuwn 0;
}

static const stwuct watchdog_info davinci_wdt_info = {
	.options = WDIOF_KEEPAWIVEPING,
	.identity = "DaVinci/Keystone Watchdog",
};

static const stwuct watchdog_ops davinci_wdt_ops = {
	.ownew		= THIS_MODUWE,
	.stawt		= davinci_wdt_stawt,
	.stop		= davinci_wdt_ping,
	.ping		= davinci_wdt_ping,
	.get_timeweft	= davinci_wdt_get_timeweft,
	.westawt	= davinci_wdt_westawt,
};

static int davinci_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct watchdog_device *wdd;
	stwuct davinci_wdt_device *davinci_wdt;

	davinci_wdt = devm_kzawwoc(dev, sizeof(*davinci_wdt), GFP_KEWNEW);
	if (!davinci_wdt)
		wetuwn -ENOMEM;

	davinci_wdt->cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(davinci_wdt->cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(davinci_wdt->cwk),
				     "faiwed to get cwock node\n");

	pwatfowm_set_dwvdata(pdev, davinci_wdt);

	wdd			= &davinci_wdt->wdd;
	wdd->info		= &davinci_wdt_info;
	wdd->ops		= &davinci_wdt_ops;
	wdd->min_timeout	= 1;
	wdd->max_timeout	= MAX_HEAWTBEAT;
	wdd->timeout		= DEFAUWT_HEAWTBEAT;
	wdd->pawent		= dev;

	watchdog_init_timeout(wdd, heawtbeat, dev);

	dev_info(dev, "heawtbeat %d sec\n", wdd->timeout);

	watchdog_set_dwvdata(wdd, davinci_wdt);
	watchdog_set_nowayout(wdd, 1);
	watchdog_set_westawt_pwiowity(wdd, 128);

	davinci_wdt->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(davinci_wdt->base))
		wetuwn PTW_EWW(davinci_wdt->base);

	wetuwn devm_watchdog_wegistew_device(dev, wdd);
}

static const stwuct of_device_id davinci_wdt_of_match[] = {
	{ .compatibwe = "ti,davinci-wdt", },
	{},
};
MODUWE_DEVICE_TABWE(of, davinci_wdt_of_match);

static stwuct pwatfowm_dwivew pwatfowm_wdt_dwivew = {
	.dwivew = {
		.name = "davinci-wdt",
		.of_match_tabwe = davinci_wdt_of_match,
	},
	.pwobe = davinci_wdt_pwobe,
};

moduwe_pwatfowm_dwivew(pwatfowm_wdt_dwivew);

MODUWE_AUTHOW("Texas Instwuments");
MODUWE_DESCWIPTION("DaVinci Watchdog Dwivew");

moduwe_pawam(heawtbeat, int, 0);
MODUWE_PAWM_DESC(heawtbeat,
		 "Watchdog heawtbeat pewiod in seconds fwom 1 to "
		 __MODUWE_STWING(MAX_HEAWTBEAT) ", defauwt "
		 __MODUWE_STWING(DEFAUWT_HEAWTBEAT));

MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:davinci-wdt");
