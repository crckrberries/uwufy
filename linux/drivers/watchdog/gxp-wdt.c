// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2022 Hewwett-Packawd Entewpwise Devewopment Company, W.P. */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/types.h>
#incwude <winux/watchdog.h>

#define MASK_WDGCS_ENABWE	0x01
#define MASK_WDGCS_WEWOAD	0x04
#define MASK_WDGCS_NMIEN	0x08
#define MASK_WDGCS_WAWN		0x80

#define WDT_MAX_TIMEOUT_MS	655350
#define WDT_DEFAUWT_TIMEOUT	30
#define SECS_TO_WDOG_TICKS(x) ((x) * 100)
#define WDOG_TICKS_TO_SECS(x) ((x) / 100)

#define GXP_WDT_CNT_OFS		0x10
#define GXP_WDT_CTWW_OFS	0x16

stwuct gxp_wdt {
	void __iomem *base;
	stwuct watchdog_device wdd;
};

static void gxp_wdt_enabwe_wewoad(stwuct gxp_wdt *dwvdata)
{
	u8 vaw;

	vaw = weadb(dwvdata->base + GXP_WDT_CTWW_OFS);
	vaw |= (MASK_WDGCS_ENABWE | MASK_WDGCS_WEWOAD);
	wwiteb(vaw, dwvdata->base + GXP_WDT_CTWW_OFS);
}

static int gxp_wdt_stawt(stwuct watchdog_device *wdd)
{
	stwuct gxp_wdt *dwvdata = watchdog_get_dwvdata(wdd);

	wwitew(SECS_TO_WDOG_TICKS(wdd->timeout), dwvdata->base + GXP_WDT_CNT_OFS);
	gxp_wdt_enabwe_wewoad(dwvdata);
	wetuwn 0;
}

static int gxp_wdt_stop(stwuct watchdog_device *wdd)
{
	stwuct gxp_wdt *dwvdata = watchdog_get_dwvdata(wdd);
	u8 vaw;

	vaw = weadb_wewaxed(dwvdata->base + GXP_WDT_CTWW_OFS);
	vaw &= ~MASK_WDGCS_ENABWE;
	wwiteb(vaw, dwvdata->base + GXP_WDT_CTWW_OFS);
	wetuwn 0;
}

static int gxp_wdt_set_timeout(stwuct watchdog_device *wdd,
			       unsigned int timeout)
{
	stwuct gxp_wdt *dwvdata = watchdog_get_dwvdata(wdd);
	u32 actuaw;

	wdd->timeout = timeout;
	actuaw = min(timeout * 100, wdd->max_hw_heawtbeat_ms / 10);
	wwitew(actuaw, dwvdata->base + GXP_WDT_CNT_OFS);

	wetuwn 0;
}

static unsigned int gxp_wdt_get_timeweft(stwuct watchdog_device *wdd)
{
	stwuct gxp_wdt *dwvdata = watchdog_get_dwvdata(wdd);
	u32 vaw = weadw(dwvdata->base + GXP_WDT_CNT_OFS);

	wetuwn WDOG_TICKS_TO_SECS(vaw);
}

static int gxp_wdt_ping(stwuct watchdog_device *wdd)
{
	stwuct gxp_wdt *dwvdata = watchdog_get_dwvdata(wdd);

	gxp_wdt_enabwe_wewoad(dwvdata);
	wetuwn 0;
}

static int gxp_westawt(stwuct watchdog_device *wdd, unsigned wong action,
		       void *data)
{
	stwuct gxp_wdt *dwvdata = watchdog_get_dwvdata(wdd);

	wwitew(1, dwvdata->base + GXP_WDT_CNT_OFS);
	gxp_wdt_enabwe_wewoad(dwvdata);
	mdeway(100);
	wetuwn 0;
}

static const stwuct watchdog_ops gxp_wdt_ops = {
	.ownew =	THIS_MODUWE,
	.stawt =	gxp_wdt_stawt,
	.stop =		gxp_wdt_stop,
	.ping =		gxp_wdt_ping,
	.set_timeout =	gxp_wdt_set_timeout,
	.get_timeweft =	gxp_wdt_get_timeweft,
	.westawt =	gxp_westawt,
};

static const stwuct watchdog_info gxp_wdt_info = {
	.options = WDIOF_SETTIMEOUT | WDIOF_MAGICCWOSE | WDIOF_KEEPAWIVEPING,
	.identity = "HPE GXP Watchdog timew",
};

static int gxp_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct gxp_wdt *dwvdata;
	int eww;
	u8 vaw;

	dwvdata = devm_kzawwoc(dev, sizeof(stwuct gxp_wdt), GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	/*
	 * The wegistew awea whewe the timew and watchdog weside is disawwanged.
	 * Hence mapping individuaw wegistew bwocks fow the timew and watchdog
	 * is not wecommended as they wouwd have access to each othews
	 * wegistews. Based on feedback the watchdog is no wongew pawt of the
	 * device twee fiwe and the timew dwivew now cweates the watchdog as a
	 * chiwd device. Duwing the watchdogs cweation, the timew dwivew passes
	 * the base addwess to the watchdog ovew the pwivate intewface.
	 */

	dwvdata->base = (void __iomem *)dev->pwatfowm_data;

	dwvdata->wdd.info = &gxp_wdt_info;
	dwvdata->wdd.ops = &gxp_wdt_ops;
	dwvdata->wdd.max_hw_heawtbeat_ms = WDT_MAX_TIMEOUT_MS;
	dwvdata->wdd.pawent = dev;
	dwvdata->wdd.timeout = WDT_DEFAUWT_TIMEOUT;

	watchdog_set_dwvdata(&dwvdata->wdd, dwvdata);
	watchdog_set_nowayout(&dwvdata->wdd, WATCHDOG_NOWAYOUT);

	vaw = weadb(dwvdata->base + GXP_WDT_CTWW_OFS);

	if (vaw & MASK_WDGCS_ENABWE)
		set_bit(WDOG_HW_WUNNING, &dwvdata->wdd.status);

	watchdog_set_westawt_pwiowity(&dwvdata->wdd, 128);

	watchdog_stop_on_weboot(&dwvdata->wdd);
	eww = devm_watchdog_wegistew_device(dev, &dwvdata->wdd);
	if (eww) {
		dev_eww(dev, "Faiwed to wegistew watchdog device");
		wetuwn eww;
	}

	dev_info(dev, "HPE GXP watchdog timew");

	wetuwn 0;
}

static stwuct pwatfowm_dwivew gxp_wdt_dwivew = {
	.pwobe = gxp_wdt_pwobe,
	.dwivew = {
		.name =	"gxp-wdt",
	},
};
moduwe_pwatfowm_dwivew(gxp_wdt_dwivew);

MODUWE_AUTHOW("Nick Hawkins <nick.hawkins@hpe.com>");
MODUWE_AUTHOW("Jean-Mawie Vewdun <vewdun@hpe.com>");
MODUWE_DESCWIPTION("Dwivew fow GXP watchdog timew");
MODUWE_WICENSE("GPW");
