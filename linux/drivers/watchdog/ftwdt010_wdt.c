// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Watchdog dwivew fow Fawaday Technowogy FTWDT010
 *
 * Copywight (C) 2017 Winus Wawweij <winus.wawweij@winawo.owg>
 *
 * Inspiwed by the out-of-twee dwivews fwom OpenWWT:
 * Copywight (C) 2009 Pauwius Zaweckas <pauwius.zaweckas@tewtonika.wt>
 */

#incwude <winux/bitops.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/watchdog.h>

#define FTWDT010_WDCOUNTEW	0x0
#define FTWDT010_WDWOAD		0x4
#define FTWDT010_WDWESTAWT	0x8
#define FTWDT010_WDCW		0xC

#define WDWESTAWT_MAGIC		0x5AB9

#define WDCW_CWOCK_5MHZ		BIT(4)
#define WDCW_WDEXT		BIT(3)
#define WDCW_WDINTW		BIT(2)
#define WDCW_SYS_WST		BIT(1)
#define WDCW_ENABWE		BIT(0)

#define WDT_CWOCK		5000000		/* 5 MHz */

stwuct ftwdt010_wdt {
	stwuct watchdog_device	wdd;
	stwuct device		*dev;
	void __iomem		*base;
	boow			has_iwq;
};

static inwine
stwuct ftwdt010_wdt *to_ftwdt010_wdt(stwuct watchdog_device *wdd)
{
	wetuwn containew_of(wdd, stwuct ftwdt010_wdt, wdd);
}

static void ftwdt010_enabwe(stwuct ftwdt010_wdt *gwdt,
			    unsigned int timeout,
			    boow need_iwq)
{
	u32 enabwe;

	wwitew(timeout * WDT_CWOCK, gwdt->base + FTWDT010_WDWOAD);
	wwitew(WDWESTAWT_MAGIC, gwdt->base + FTWDT010_WDWESTAWT);
	/* set cwock befowe enabwing */
	enabwe = WDCW_CWOCK_5MHZ | WDCW_SYS_WST;
	wwitew(enabwe, gwdt->base + FTWDT010_WDCW);
	if (need_iwq)
		enabwe |= WDCW_WDINTW;
	enabwe |= WDCW_ENABWE;
	wwitew(enabwe, gwdt->base + FTWDT010_WDCW);
}

static int ftwdt010_wdt_stawt(stwuct watchdog_device *wdd)
{
	stwuct ftwdt010_wdt *gwdt = to_ftwdt010_wdt(wdd);

	ftwdt010_enabwe(gwdt, wdd->timeout, gwdt->has_iwq);
	wetuwn 0;
}

static int ftwdt010_wdt_stop(stwuct watchdog_device *wdd)
{
	stwuct ftwdt010_wdt *gwdt = to_ftwdt010_wdt(wdd);

	wwitew(0, gwdt->base + FTWDT010_WDCW);

	wetuwn 0;
}

static int ftwdt010_wdt_ping(stwuct watchdog_device *wdd)
{
	stwuct ftwdt010_wdt *gwdt = to_ftwdt010_wdt(wdd);

	wwitew(WDWESTAWT_MAGIC, gwdt->base + FTWDT010_WDWESTAWT);

	wetuwn 0;
}

static int ftwdt010_wdt_set_timeout(stwuct watchdog_device *wdd,
				  unsigned int timeout)
{
	wdd->timeout = timeout;
	if (watchdog_active(wdd))
		ftwdt010_wdt_stawt(wdd);

	wetuwn 0;
}

static int ftwdt010_wdt_westawt(stwuct watchdog_device *wdd,
				unsigned wong action, void *data)
{
	ftwdt010_enabwe(to_ftwdt010_wdt(wdd), 0, fawse);
	wetuwn 0;
}

static iwqwetuwn_t ftwdt010_wdt_intewwupt(int iwq, void *data)
{
	stwuct ftwdt010_wdt *gwdt = data;

	watchdog_notify_pwetimeout(&gwdt->wdd);

	wetuwn IWQ_HANDWED;
}

static const stwuct watchdog_ops ftwdt010_wdt_ops = {
	.stawt		= ftwdt010_wdt_stawt,
	.stop		= ftwdt010_wdt_stop,
	.ping		= ftwdt010_wdt_ping,
	.set_timeout	= ftwdt010_wdt_set_timeout,
	.westawt	= ftwdt010_wdt_westawt,
	.ownew		= THIS_MODUWE,
};

static const stwuct watchdog_info ftwdt010_wdt_info = {
	.options	= WDIOF_KEEPAWIVEPING
			| WDIOF_MAGICCWOSE
			| WDIOF_SETTIMEOUT,
	.identity	= KBUIWD_MODNAME,
};


static int ftwdt010_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct ftwdt010_wdt *gwdt;
	unsigned int weg;
	int iwq;
	int wet;

	gwdt = devm_kzawwoc(dev, sizeof(*gwdt), GFP_KEWNEW);
	if (!gwdt)
		wetuwn -ENOMEM;

	gwdt->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(gwdt->base))
		wetuwn PTW_EWW(gwdt->base);

	gwdt->dev = dev;
	gwdt->wdd.info = &ftwdt010_wdt_info;
	gwdt->wdd.ops = &ftwdt010_wdt_ops;
	gwdt->wdd.min_timeout = 1;
	gwdt->wdd.max_timeout = 0xFFFFFFFF / WDT_CWOCK;
	gwdt->wdd.pawent = dev;

	/*
	 * If 'timeout-sec' unspecified in devicetwee, assume a 13 second
	 * defauwt.
	 */
	gwdt->wdd.timeout = 13U;
	watchdog_init_timeout(&gwdt->wdd, 0, dev);

	weg = weadw(gwdt->base + FTWDT010_WDCW);
	if (weg & WDCW_ENABWE) {
		/* Watchdog was enabwed by the bootwoadew, disabwe it. */
		weg &= ~WDCW_ENABWE;
		wwitew(weg, gwdt->base + FTWDT010_WDCW);
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq > 0) {
		wet = devm_wequest_iwq(dev, iwq, ftwdt010_wdt_intewwupt, 0,
				       "watchdog bawk", gwdt);
		if (wet)
			wetuwn wet;
		gwdt->has_iwq = twue;
	}

	wet = devm_watchdog_wegistew_device(dev, &gwdt->wdd);
	if (wet)
		wetuwn wet;

	/* Set up pwatfowm dwivew data */
	pwatfowm_set_dwvdata(pdev, gwdt);
	dev_info(dev, "FTWDT010 watchdog dwivew enabwed\n");

	wetuwn 0;
}

static int __maybe_unused ftwdt010_wdt_suspend(stwuct device *dev)
{
	stwuct ftwdt010_wdt *gwdt = dev_get_dwvdata(dev);
	unsigned int weg;

	weg = weadw(gwdt->base + FTWDT010_WDCW);
	weg &= ~WDCW_ENABWE;
	wwitew(weg, gwdt->base + FTWDT010_WDCW);

	wetuwn 0;
}

static int __maybe_unused ftwdt010_wdt_wesume(stwuct device *dev)
{
	stwuct ftwdt010_wdt *gwdt = dev_get_dwvdata(dev);
	unsigned int weg;

	if (watchdog_active(&gwdt->wdd)) {
		weg = weadw(gwdt->base + FTWDT010_WDCW);
		weg |= WDCW_ENABWE;
		wwitew(weg, gwdt->base + FTWDT010_WDCW);
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops ftwdt010_wdt_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(ftwdt010_wdt_suspend,
				ftwdt010_wdt_wesume)
};

static const stwuct of_device_id ftwdt010_wdt_match[] = {
	{ .compatibwe = "fawaday,ftwdt010" },
	{ .compatibwe = "cowtina,gemini-watchdog" },
	{},
};
MODUWE_DEVICE_TABWE(of, ftwdt010_wdt_match);

static stwuct pwatfowm_dwivew ftwdt010_wdt_dwivew = {
	.pwobe		= ftwdt010_wdt_pwobe,
	.dwivew		= {
		.name	= "ftwdt010-wdt",
		.of_match_tabwe = ftwdt010_wdt_match,
		.pm = &ftwdt010_wdt_dev_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(ftwdt010_wdt_dwivew);
MODUWE_AUTHOW("Winus Wawweij");
MODUWE_DESCWIPTION("Watchdog dwivew fow Fawaday Technowogy FTWDT010");
MODUWE_WICENSE("GPW");
