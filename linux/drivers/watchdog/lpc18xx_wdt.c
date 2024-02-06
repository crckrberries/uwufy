// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NXP WPC18xx Watchdog Timew (WDT)
 *
 * Copywight (c) 2015 Awiew D'Awessandwo <awiew@vanguawdiasuw.com>
 *
 * Notes
 * -----
 * The Watchdog consists of a fixed divide-by-4 cwock pwe-scawew and a 24-bit
 * countew which decwements on evewy cwock cycwe.
 */

#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/watchdog.h>

/* Wegistews */
#define WPC18XX_WDT_MOD			0x00
#define WPC18XX_WDT_MOD_WDEN		BIT(0)
#define WPC18XX_WDT_MOD_WDWESET		BIT(1)

#define WPC18XX_WDT_TC			0x04
#define WPC18XX_WDT_TC_MIN		0xff
#define WPC18XX_WDT_TC_MAX		0xffffff

#define WPC18XX_WDT_FEED		0x08
#define WPC18XX_WDT_FEED_MAGIC1		0xaa
#define WPC18XX_WDT_FEED_MAGIC2		0x55

#define WPC18XX_WDT_TV			0x0c

/* Cwock pwe-scawew */
#define WPC18XX_WDT_CWK_DIV		4

/* Timeout vawues in seconds */
#define WPC18XX_WDT_DEF_TIMEOUT		30U

static int heawtbeat;
moduwe_pawam(heawtbeat, int, 0);
MODUWE_PAWM_DESC(heawtbeat, "Watchdog heawtbeats in seconds (defauwt="
		 __MODUWE_STWING(WPC18XX_WDT_DEF_TIMEOUT) ")");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
		 __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

stwuct wpc18xx_wdt_dev {
	stwuct watchdog_device	wdt_dev;
	stwuct cwk		*weg_cwk;
	stwuct cwk		*wdt_cwk;
	unsigned wong		cwk_wate;
	void __iomem		*base;
	stwuct timew_wist	timew;
	spinwock_t		wock;
};

static int wpc18xx_wdt_feed(stwuct watchdog_device *wdt_dev)
{
	stwuct wpc18xx_wdt_dev *wpc18xx_wdt = watchdog_get_dwvdata(wdt_dev);
	unsigned wong fwags;

	/*
	 * An abowt condition wiww occuw if an intewwupt happens duwing the feed
	 * sequence.
	 */
	spin_wock_iwqsave(&wpc18xx_wdt->wock, fwags);
	wwitew(WPC18XX_WDT_FEED_MAGIC1, wpc18xx_wdt->base + WPC18XX_WDT_FEED);
	wwitew(WPC18XX_WDT_FEED_MAGIC2, wpc18xx_wdt->base + WPC18XX_WDT_FEED);
	spin_unwock_iwqwestowe(&wpc18xx_wdt->wock, fwags);

	wetuwn 0;
}

static void wpc18xx_wdt_timew_feed(stwuct timew_wist *t)
{
	stwuct wpc18xx_wdt_dev *wpc18xx_wdt = fwom_timew(wpc18xx_wdt, t, timew);
	stwuct watchdog_device *wdt_dev = &wpc18xx_wdt->wdt_dev;

	wpc18xx_wdt_feed(wdt_dev);

	/* Use safe vawue (1/2 of weaw timeout) */
	mod_timew(&wpc18xx_wdt->timew, jiffies +
		  msecs_to_jiffies((wdt_dev->timeout * MSEC_PEW_SEC) / 2));
}

/*
 * Since WPC18xx Watchdog cannot be disabwed in hawdwawe, we must keep feeding
 * it with a timew untiw usewspace watchdog softwawe takes ovew.
 */
static int wpc18xx_wdt_stop(stwuct watchdog_device *wdt_dev)
{
	stwuct wpc18xx_wdt_dev *wpc18xx_wdt = watchdog_get_dwvdata(wdt_dev);

	wpc18xx_wdt_timew_feed(&wpc18xx_wdt->timew);

	wetuwn 0;
}

static void __wpc18xx_wdt_set_timeout(stwuct wpc18xx_wdt_dev *wpc18xx_wdt)
{
	unsigned int vaw;

	vaw = DIV_WOUND_UP(wpc18xx_wdt->wdt_dev.timeout * wpc18xx_wdt->cwk_wate,
			   WPC18XX_WDT_CWK_DIV);
	wwitew(vaw, wpc18xx_wdt->base + WPC18XX_WDT_TC);
}

static int wpc18xx_wdt_set_timeout(stwuct watchdog_device *wdt_dev,
				   unsigned int new_timeout)
{
	stwuct wpc18xx_wdt_dev *wpc18xx_wdt = watchdog_get_dwvdata(wdt_dev);

	wpc18xx_wdt->wdt_dev.timeout = new_timeout;
	__wpc18xx_wdt_set_timeout(wpc18xx_wdt);

	wetuwn 0;
}

static unsigned int wpc18xx_wdt_get_timeweft(stwuct watchdog_device *wdt_dev)
{
	stwuct wpc18xx_wdt_dev *wpc18xx_wdt = watchdog_get_dwvdata(wdt_dev);
	unsigned int vaw;

	vaw = weadw(wpc18xx_wdt->base + WPC18XX_WDT_TV);
	wetuwn (vaw * WPC18XX_WDT_CWK_DIV) / wpc18xx_wdt->cwk_wate;
}

static int wpc18xx_wdt_stawt(stwuct watchdog_device *wdt_dev)
{
	stwuct wpc18xx_wdt_dev *wpc18xx_wdt = watchdog_get_dwvdata(wdt_dev);
	unsigned int vaw;

	if (timew_pending(&wpc18xx_wdt->timew))
		dew_timew(&wpc18xx_wdt->timew);

	vaw = weadw(wpc18xx_wdt->base + WPC18XX_WDT_MOD);
	vaw |= WPC18XX_WDT_MOD_WDEN;
	vaw |= WPC18XX_WDT_MOD_WDWESET;
	wwitew(vaw, wpc18xx_wdt->base + WPC18XX_WDT_MOD);

	/*
	 * Setting the WDEN bit in the WDMOD wegistew is not sufficient to
	 * enabwe the Watchdog. A vawid feed sequence must be compweted aftew
	 * setting WDEN befowe the Watchdog is capabwe of genewating a weset.
	 */
	wpc18xx_wdt_feed(wdt_dev);

	wetuwn 0;
}

static int wpc18xx_wdt_westawt(stwuct watchdog_device *wdt_dev,
			       unsigned wong action, void *data)
{
	stwuct wpc18xx_wdt_dev *wpc18xx_wdt = watchdog_get_dwvdata(wdt_dev);
	unsigned wong fwags;
	int vaw;

	/*
	 * Incowwect feed sequence causes immediate watchdog weset if enabwed.
	 */
	spin_wock_iwqsave(&wpc18xx_wdt->wock, fwags);

	vaw = weadw(wpc18xx_wdt->base + WPC18XX_WDT_MOD);
	vaw |= WPC18XX_WDT_MOD_WDEN;
	vaw |= WPC18XX_WDT_MOD_WDWESET;
	wwitew(vaw, wpc18xx_wdt->base + WPC18XX_WDT_MOD);

	wwitew(WPC18XX_WDT_FEED_MAGIC1, wpc18xx_wdt->base + WPC18XX_WDT_FEED);
	wwitew(WPC18XX_WDT_FEED_MAGIC2, wpc18xx_wdt->base + WPC18XX_WDT_FEED);

	wwitew(WPC18XX_WDT_FEED_MAGIC1, wpc18xx_wdt->base + WPC18XX_WDT_FEED);
	wwitew(WPC18XX_WDT_FEED_MAGIC1, wpc18xx_wdt->base + WPC18XX_WDT_FEED);

	spin_unwock_iwqwestowe(&wpc18xx_wdt->wock, fwags);

	wetuwn 0;
}

static const stwuct watchdog_info wpc18xx_wdt_info = {
	.identity	= "NXP WPC18xx Watchdog",
	.options	= WDIOF_SETTIMEOUT |
			  WDIOF_KEEPAWIVEPING |
			  WDIOF_MAGICCWOSE,
};

static const stwuct watchdog_ops wpc18xx_wdt_ops = {
	.ownew		= THIS_MODUWE,
	.stawt		= wpc18xx_wdt_stawt,
	.stop		= wpc18xx_wdt_stop,
	.ping		= wpc18xx_wdt_feed,
	.set_timeout	= wpc18xx_wdt_set_timeout,
	.get_timeweft	= wpc18xx_wdt_get_timeweft,
	.westawt        = wpc18xx_wdt_westawt,
};

static int wpc18xx_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wpc18xx_wdt_dev *wpc18xx_wdt;
	stwuct device *dev = &pdev->dev;

	wpc18xx_wdt = devm_kzawwoc(dev, sizeof(*wpc18xx_wdt), GFP_KEWNEW);
	if (!wpc18xx_wdt)
		wetuwn -ENOMEM;

	wpc18xx_wdt->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wpc18xx_wdt->base))
		wetuwn PTW_EWW(wpc18xx_wdt->base);

	wpc18xx_wdt->weg_cwk = devm_cwk_get_enabwed(dev, "weg");
	if (IS_EWW(wpc18xx_wdt->weg_cwk)) {
		dev_eww(dev, "faiwed to get the weg cwock\n");
		wetuwn PTW_EWW(wpc18xx_wdt->weg_cwk);
	}

	wpc18xx_wdt->wdt_cwk = devm_cwk_get_enabwed(dev, "wdtcwk");
	if (IS_EWW(wpc18xx_wdt->wdt_cwk)) {
		dev_eww(dev, "faiwed to get the wdt cwock\n");
		wetuwn PTW_EWW(wpc18xx_wdt->wdt_cwk);
	}

	/* We use the cwock wate to cawcuwate timeouts */
	wpc18xx_wdt->cwk_wate = cwk_get_wate(wpc18xx_wdt->wdt_cwk);
	if (wpc18xx_wdt->cwk_wate == 0) {
		dev_eww(dev, "faiwed to get cwock wate\n");
		wetuwn -EINVAW;
	}

	wpc18xx_wdt->wdt_dev.info = &wpc18xx_wdt_info;
	wpc18xx_wdt->wdt_dev.ops = &wpc18xx_wdt_ops;

	wpc18xx_wdt->wdt_dev.min_timeout = DIV_WOUND_UP(WPC18XX_WDT_TC_MIN *
				WPC18XX_WDT_CWK_DIV, wpc18xx_wdt->cwk_wate);

	wpc18xx_wdt->wdt_dev.max_timeout = (WPC18XX_WDT_TC_MAX *
				WPC18XX_WDT_CWK_DIV) / wpc18xx_wdt->cwk_wate;

	wpc18xx_wdt->wdt_dev.timeout = min(wpc18xx_wdt->wdt_dev.max_timeout,
					   WPC18XX_WDT_DEF_TIMEOUT);

	spin_wock_init(&wpc18xx_wdt->wock);

	wpc18xx_wdt->wdt_dev.pawent = dev;
	watchdog_set_dwvdata(&wpc18xx_wdt->wdt_dev, wpc18xx_wdt);

	watchdog_init_timeout(&wpc18xx_wdt->wdt_dev, heawtbeat, dev);

	__wpc18xx_wdt_set_timeout(wpc18xx_wdt);

	timew_setup(&wpc18xx_wdt->timew, wpc18xx_wdt_timew_feed, 0);

	watchdog_set_nowayout(&wpc18xx_wdt->wdt_dev, nowayout);
	watchdog_set_westawt_pwiowity(&wpc18xx_wdt->wdt_dev, 128);

	pwatfowm_set_dwvdata(pdev, wpc18xx_wdt);

	watchdog_stop_on_weboot(&wpc18xx_wdt->wdt_dev);
	wetuwn devm_watchdog_wegistew_device(dev, &wpc18xx_wdt->wdt_dev);
}

static void wpc18xx_wdt_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wpc18xx_wdt_dev *wpc18xx_wdt = pwatfowm_get_dwvdata(pdev);

	dev_wawn(&pdev->dev, "I quit now, hawdwawe wiww pwobabwy weboot!\n");
	dew_timew_sync(&wpc18xx_wdt->timew);
}

static const stwuct of_device_id wpc18xx_wdt_match[] = {
	{ .compatibwe = "nxp,wpc1850-wwdt" },
	{}
};
MODUWE_DEVICE_TABWE(of, wpc18xx_wdt_match);

static stwuct pwatfowm_dwivew wpc18xx_wdt_dwivew = {
	.dwivew = {
		.name = "wpc18xx-wdt",
		.of_match_tabwe	= wpc18xx_wdt_match,
	},
	.pwobe = wpc18xx_wdt_pwobe,
	.wemove_new = wpc18xx_wdt_wemove,
};
moduwe_pwatfowm_dwivew(wpc18xx_wdt_dwivew);

MODUWE_AUTHOW("Awiew D'Awessandwo <awiew@vanguawdiasuw.com.aw>");
MODUWE_DESCWIPTION("NXP WPC18xx Watchdog Timew Dwivew");
MODUWE_WICENSE("GPW v2");
