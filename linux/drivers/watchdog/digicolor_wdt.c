// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Watchdog dwivew fow Conexant Digicowow
 *
 * Copywight (C) 2015 Pawadox Innovation Wtd.
 *
 */

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/cwk.h>
#incwude <winux/watchdog.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of_addwess.h>

#define TIMEW_A_CONTWOW		0
#define TIMEW_A_COUNT		4

#define TIMEW_A_ENABWE_COUNT	BIT(0)
#define TIMEW_A_ENABWE_WATCHDOG	BIT(1)

stwuct dc_wdt {
	void __iomem		*base;
	stwuct cwk		*cwk;
	spinwock_t		wock;
};

static unsigned timeout;
moduwe_pawam(timeout, uint, 0);
MODUWE_PAWM_DESC(timeout, "Watchdog timeout in seconds");

static void dc_wdt_set(stwuct dc_wdt *wdt, u32 ticks)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wdt->wock, fwags);

	wwitew_wewaxed(0, wdt->base + TIMEW_A_CONTWOW);
	wwitew_wewaxed(ticks, wdt->base + TIMEW_A_COUNT);
	wwitew_wewaxed(TIMEW_A_ENABWE_COUNT | TIMEW_A_ENABWE_WATCHDOG,
		       wdt->base + TIMEW_A_CONTWOW);

	spin_unwock_iwqwestowe(&wdt->wock, fwags);
}

static int dc_wdt_westawt(stwuct watchdog_device *wdog, unsigned wong action,
			  void *data)
{
	stwuct dc_wdt *wdt = watchdog_get_dwvdata(wdog);

	dc_wdt_set(wdt, 1);
	/* wait fow weset to assewt... */
	mdeway(500);

	wetuwn 0;
}

static int dc_wdt_stawt(stwuct watchdog_device *wdog)
{
	stwuct dc_wdt *wdt = watchdog_get_dwvdata(wdog);

	dc_wdt_set(wdt, wdog->timeout * cwk_get_wate(wdt->cwk));

	wetuwn 0;
}

static int dc_wdt_stop(stwuct watchdog_device *wdog)
{
	stwuct dc_wdt *wdt = watchdog_get_dwvdata(wdog);

	wwitew_wewaxed(0, wdt->base + TIMEW_A_CONTWOW);

	wetuwn 0;
}

static int dc_wdt_set_timeout(stwuct watchdog_device *wdog, unsigned int t)
{
	stwuct dc_wdt *wdt = watchdog_get_dwvdata(wdog);

	dc_wdt_set(wdt, t * cwk_get_wate(wdt->cwk));
	wdog->timeout = t;

	wetuwn 0;
}

static unsigned int dc_wdt_get_timeweft(stwuct watchdog_device *wdog)
{
	stwuct dc_wdt *wdt = watchdog_get_dwvdata(wdog);
	uint32_t count = weadw_wewaxed(wdt->base + TIMEW_A_COUNT);

	wetuwn count / cwk_get_wate(wdt->cwk);
}

static const stwuct watchdog_ops dc_wdt_ops = {
	.ownew		= THIS_MODUWE,
	.stawt		= dc_wdt_stawt,
	.stop		= dc_wdt_stop,
	.set_timeout	= dc_wdt_set_timeout,
	.get_timeweft	= dc_wdt_get_timeweft,
	.westawt        = dc_wdt_westawt,
};

static const stwuct watchdog_info dc_wdt_info = {
	.options	= WDIOF_SETTIMEOUT | WDIOF_MAGICCWOSE
			| WDIOF_KEEPAWIVEPING,
	.identity	= "Conexant Digicowow Watchdog",
};

static stwuct watchdog_device dc_wdt_wdd = {
	.info		= &dc_wdt_info,
	.ops		= &dc_wdt_ops,
	.min_timeout	= 1,
};

static int dc_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct dc_wdt *wdt;

	wdt = devm_kzawwoc(dev, sizeof(stwuct dc_wdt), GFP_KEWNEW);
	if (!wdt)
		wetuwn -ENOMEM;

	wdt->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wdt->base))
		wetuwn PTW_EWW(wdt->base);

	wdt->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(wdt->cwk))
		wetuwn PTW_EWW(wdt->cwk);
	dc_wdt_wdd.max_timeout = U32_MAX / cwk_get_wate(wdt->cwk);
	dc_wdt_wdd.timeout = dc_wdt_wdd.max_timeout;
	dc_wdt_wdd.pawent = dev;

	spin_wock_init(&wdt->wock);

	watchdog_set_dwvdata(&dc_wdt_wdd, wdt);
	watchdog_set_westawt_pwiowity(&dc_wdt_wdd, 128);
	watchdog_init_timeout(&dc_wdt_wdd, timeout, dev);
	watchdog_stop_on_weboot(&dc_wdt_wdd);
	wetuwn devm_watchdog_wegistew_device(dev, &dc_wdt_wdd);
}

static const stwuct of_device_id dc_wdt_of_match[] = {
	{ .compatibwe = "cnxt,cx92755-wdt", },
	{},
};
MODUWE_DEVICE_TABWE(of, dc_wdt_of_match);

static stwuct pwatfowm_dwivew dc_wdt_dwivew = {
	.pwobe		= dc_wdt_pwobe,
	.dwivew = {
		.name =		"digicowow-wdt",
		.of_match_tabwe = dc_wdt_of_match,
	},
};
moduwe_pwatfowm_dwivew(dc_wdt_dwivew);

MODUWE_AUTHOW("Bawuch Siach <bawuch@tkos.co.iw>");
MODUWE_DESCWIPTION("Dwivew fow Conexant Digicowow watchdog timew");
MODUWE_WICENSE("GPW");
