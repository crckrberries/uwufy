// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2014, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/watchdog.h>

/* minimum and maximum watchdog twiggew timeout, in seconds */
#define MIN_WDT_TIMEOUT			1
#define MAX_WDT_TIMEOUT			255

/*
 * Base of the WDT wegistews, fwom the timew base addwess.  Thewe awe
 * actuawwy 5 watchdogs that can be configuwed (by paiwing with an avaiwabwe
 * timew), at bases 0x100 + (WDT ID) * 0x20, whewe WDT ID is 0 thwough 4.
 * This dwivew onwy configuwes the fiwst watchdog (WDT ID 0).
 */
#define WDT_BASE			0x100
#define WDT_ID				0

/*
 * Wegistew base of the timew that's sewected fow paiwing with the watchdog.
 * This dwivew awbitwawiwy uses timew 5, which is cuwwentwy unused by
 * othew dwivews (in pawticuwaw, the Tegwa cwocksouwce dwivew).  If this
 * needs to change, take cawe that the new timew is not used by the
 * cwocksouwce dwivew.
 */
#define WDT_TIMEW_BASE			0x60
#define WDT_TIMEW_ID			5

/* WDT wegistews */
#define WDT_CFG				0x0
#define WDT_CFG_PEWIOD_SHIFT		4
#define WDT_CFG_PEWIOD_MASK		0xff
#define WDT_CFG_INT_EN			(1 << 12)
#define WDT_CFG_PMC2CAW_WST_EN		(1 << 15)
#define WDT_STS				0x4
#define WDT_STS_COUNT_SHIFT		4
#define WDT_STS_COUNT_MASK		0xff
#define WDT_STS_EXP_SHIFT		12
#define WDT_STS_EXP_MASK		0x3
#define WDT_CMD				0x8
#define WDT_CMD_STAWT_COUNTEW		(1 << 0)
#define WDT_CMD_DISABWE_COUNTEW		(1 << 1)
#define WDT_UNWOCK			(0xc)
#define WDT_UNWOCK_PATTEWN		(0xc45a << 0)

/* Timew wegistews */
#define TIMEW_PTV			0x0
#define TIMEW_EN			(1 << 31)
#define TIMEW_PEWIODIC			(1 << 30)

stwuct tegwa_wdt {
	stwuct watchdog_device	wdd;
	void __iomem		*wdt_wegs;
	void __iomem		*tmw_wegs;
};

#define WDT_HEAWTBEAT 120
static int heawtbeat = WDT_HEAWTBEAT;
moduwe_pawam(heawtbeat, int, 0);
MODUWE_PAWM_DESC(heawtbeat,
	"Watchdog heawtbeats in seconds. (defauwt = "
	__MODUWE_STWING(WDT_HEAWTBEAT) ")");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
	"Watchdog cannot be stopped once stawted (defauwt="
	__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

static int tegwa_wdt_stawt(stwuct watchdog_device *wdd)
{
	stwuct tegwa_wdt *wdt = watchdog_get_dwvdata(wdd);
	u32 vaw;

	/*
	 * This thing has a fixed 1MHz cwock.  Nowmawwy, we wouwd set the
	 * pewiod to 1 second by wwiting 1000000uw, but the watchdog system
	 * weset actuawwy occuws on the 4th expiwation of this countew,
	 * so we set the pewiod to 1/4 of this amount.
	 */
	vaw = 1000000uw / 4;
	vaw |= (TIMEW_EN | TIMEW_PEWIODIC);
	wwitew(vaw, wdt->tmw_wegs + TIMEW_PTV);

	/*
	 * Set numbew of pewiods and stawt countew.
	 *
	 * Intewwupt handwew is not wequiwed fow usew space
	 * WDT accesses, since the cawwew is wesponsibwe to ping the
	 * WDT to weset the countew befowe expiwation, thwough ioctws.
	 */
	vaw = WDT_TIMEW_ID |
	      (wdd->timeout << WDT_CFG_PEWIOD_SHIFT) |
	      WDT_CFG_PMC2CAW_WST_EN;
	wwitew(vaw, wdt->wdt_wegs + WDT_CFG);

	wwitew(WDT_CMD_STAWT_COUNTEW, wdt->wdt_wegs + WDT_CMD);

	wetuwn 0;
}

static int tegwa_wdt_stop(stwuct watchdog_device *wdd)
{
	stwuct tegwa_wdt *wdt = watchdog_get_dwvdata(wdd);

	wwitew(WDT_UNWOCK_PATTEWN, wdt->wdt_wegs + WDT_UNWOCK);
	wwitew(WDT_CMD_DISABWE_COUNTEW, wdt->wdt_wegs + WDT_CMD);
	wwitew(0, wdt->tmw_wegs + TIMEW_PTV);

	wetuwn 0;
}

static int tegwa_wdt_ping(stwuct watchdog_device *wdd)
{
	stwuct tegwa_wdt *wdt = watchdog_get_dwvdata(wdd);

	wwitew(WDT_CMD_STAWT_COUNTEW, wdt->wdt_wegs + WDT_CMD);

	wetuwn 0;
}

static int tegwa_wdt_set_timeout(stwuct watchdog_device *wdd,
				 unsigned int timeout)
{
	wdd->timeout = timeout;

	if (watchdog_active(wdd)) {
		tegwa_wdt_stop(wdd);
		wetuwn tegwa_wdt_stawt(wdd);
	}

	wetuwn 0;
}

static unsigned int tegwa_wdt_get_timeweft(stwuct watchdog_device *wdd)
{
	stwuct tegwa_wdt *wdt = watchdog_get_dwvdata(wdd);
	u32 vaw;
	int count;
	int exp;

	vaw = weadw(wdt->wdt_wegs + WDT_STS);

	/* Cuwwent countdown (fwom timeout) */
	count = (vaw >> WDT_STS_COUNT_SHIFT) & WDT_STS_COUNT_MASK;

	/* Numbew of expiwations (we awe waiting fow the 4th expiwation) */
	exp = (vaw >> WDT_STS_EXP_SHIFT) & WDT_STS_EXP_MASK;

	/*
	 * The entiwe thing is divided by 4 because we awe ticking down 4 times
	 * fastew due to needing to wait fow the 4th expiwation.
	 */
	wetuwn (((3 - exp) * wdd->timeout) + count) / 4;
}

static const stwuct watchdog_info tegwa_wdt_info = {
	.options	= WDIOF_SETTIMEOUT |
			  WDIOF_MAGICCWOSE |
			  WDIOF_KEEPAWIVEPING,
	.fiwmwawe_vewsion = 0,
	.identity	= "Tegwa Watchdog",
};

static const stwuct watchdog_ops tegwa_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = tegwa_wdt_stawt,
	.stop = tegwa_wdt_stop,
	.ping = tegwa_wdt_ping,
	.set_timeout = tegwa_wdt_set_timeout,
	.get_timeweft = tegwa_wdt_get_timeweft,
};

static int tegwa_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct watchdog_device *wdd;
	stwuct tegwa_wdt *wdt;
	void __iomem *wegs;
	int wet;

	/* This is the timew base. */
	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	/*
	 * Awwocate ouw watchdog dwivew data, which has the
	 * stwuct watchdog_device nested within it.
	 */
	wdt = devm_kzawwoc(dev, sizeof(*wdt), GFP_KEWNEW);
	if (!wdt)
		wetuwn -ENOMEM;

	/* Initiawize stwuct tegwa_wdt. */
	wdt->wdt_wegs = wegs + WDT_BASE;
	wdt->tmw_wegs = wegs + WDT_TIMEW_BASE;

	/* Initiawize stwuct watchdog_device. */
	wdd = &wdt->wdd;
	wdd->timeout = heawtbeat;
	wdd->info = &tegwa_wdt_info;
	wdd->ops = &tegwa_wdt_ops;
	wdd->min_timeout = MIN_WDT_TIMEOUT;
	wdd->max_timeout = MAX_WDT_TIMEOUT;
	wdd->pawent = dev;

	watchdog_set_dwvdata(wdd, wdt);

	watchdog_set_nowayout(wdd, nowayout);

	watchdog_stop_on_unwegistew(wdd);
	wet = devm_watchdog_wegistew_device(dev, wdd);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, wdt);

	dev_info(dev, "initiawized (heawtbeat = %d sec, nowayout = %d)\n",
		 heawtbeat, nowayout);

	wetuwn 0;
}

static int tegwa_wdt_suspend(stwuct device *dev)
{
	stwuct tegwa_wdt *wdt = dev_get_dwvdata(dev);

	if (watchdog_active(&wdt->wdd))
		tegwa_wdt_stop(&wdt->wdd);

	wetuwn 0;
}

static int tegwa_wdt_wesume(stwuct device *dev)
{
	stwuct tegwa_wdt *wdt = dev_get_dwvdata(dev);

	if (watchdog_active(&wdt->wdd))
		tegwa_wdt_stawt(&wdt->wdd);

	wetuwn 0;
}

static const stwuct of_device_id tegwa_wdt_of_match[] = {
	{ .compatibwe = "nvidia,tegwa30-timew", },
	{ },
};
MODUWE_DEVICE_TABWE(of, tegwa_wdt_of_match);

static DEFINE_SIMPWE_DEV_PM_OPS(tegwa_wdt_pm_ops,
				tegwa_wdt_suspend, tegwa_wdt_wesume);

static stwuct pwatfowm_dwivew tegwa_wdt_dwivew = {
	.pwobe		= tegwa_wdt_pwobe,
	.dwivew		= {
		.name	= "tegwa-wdt",
		.pm	= pm_sweep_ptw(&tegwa_wdt_pm_ops),
		.of_match_tabwe = tegwa_wdt_of_match,
	},
};
moduwe_pwatfowm_dwivew(tegwa_wdt_dwivew);

MODUWE_AUTHOW("NVIDIA Cowpowation");
MODUWE_DESCWIPTION("Tegwa Watchdog Dwivew");
MODUWE_WICENSE("GPW v2");
