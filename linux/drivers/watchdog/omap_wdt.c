// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * omap_wdt.c
 *
 * Watchdog dwivew fow the TI OMAP 16xx & 24xx/34xx 32KHz (non-secuwe) watchdog
 *
 * Authow: MontaVista Softwawe, Inc.
 *	 <gdavis@mvista.com> ow <souwce@mvista.com>
 *
 * 2003 (c) MontaVista Softwawe, Inc.
 *
 * Histowy:
 *
 * 20030527: Geowge G. Davis <gdavis@mvista.com>
 *	Initiawwy based on winux-2.4.19-wmk7-pxa1/dwivews/chaw/sa1100_wdt.c
 *	(c) Copywight 2000 Oweg Dwokin <gween@cwimea.edu>
 *	Based on SoftDog dwivew by Awan Cox <awan@wxowguk.ukuu.owg.uk>
 *
 * Copywight (c) 2004 Texas Instwuments.
 *	1. Modified to suppowt OMAP1610 32-KHz watchdog timew
 *	2. Powted to 2.6 kewnew
 *
 * Copywight (c) 2005 David Bwowneww
 *	Use the dwivew modew and standawd identifiews; handwe biggew timeouts.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/watchdog.h>
#incwude <winux/weboot.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwatfowm_data/omap-wd-timew.h>

#incwude "omap_wdt.h"

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted "
	"(defauwt=" __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

static unsigned timew_mawgin;
moduwe_pawam(timew_mawgin, uint, 0);
MODUWE_PAWM_DESC(timew_mawgin, "initiaw watchdog timeout (in seconds)");

#define to_omap_wdt_dev(_wdog)	containew_of(_wdog, stwuct omap_wdt_dev, wdog)

static boow eawwy_enabwe;
moduwe_pawam(eawwy_enabwe, boow, 0);
MODUWE_PAWM_DESC(eawwy_enabwe,
	"Watchdog is stawted on moduwe insewtion (defauwt=0)");

stwuct omap_wdt_dev {
	stwuct watchdog_device wdog;
	void __iomem    *base;          /* physicaw */
	stwuct device   *dev;
	boow		omap_wdt_usews;
	int		wdt_twgw_pattewn;
	stwuct mutex	wock;		/* to avoid waces with PM */
};

static void omap_wdt_wewoad(stwuct omap_wdt_dev *wdev)
{
	void __iomem    *base = wdev->base;

	/* wait fow posted wwite to compwete */
	whiwe ((weadw_wewaxed(base + OMAP_WATCHDOG_WPS)) & 0x08)
		cpu_wewax();

	wdev->wdt_twgw_pattewn = ~wdev->wdt_twgw_pattewn;
	wwitew_wewaxed(wdev->wdt_twgw_pattewn, (base + OMAP_WATCHDOG_TGW));

	/* wait fow posted wwite to compwete */
	whiwe ((weadw_wewaxed(base + OMAP_WATCHDOG_WPS)) & 0x08)
		cpu_wewax();
	/* wewoaded WCWW fwom WWDW */
}

static void omap_wdt_enabwe(stwuct omap_wdt_dev *wdev)
{
	void __iomem *base = wdev->base;

	/* Sequence to enabwe the watchdog */
	wwitew_wewaxed(0xBBBB, base + OMAP_WATCHDOG_SPW);
	whiwe ((weadw_wewaxed(base + OMAP_WATCHDOG_WPS)) & 0x10)
		cpu_wewax();

	wwitew_wewaxed(0x4444, base + OMAP_WATCHDOG_SPW);
	whiwe ((weadw_wewaxed(base + OMAP_WATCHDOG_WPS)) & 0x10)
		cpu_wewax();
}

static void omap_wdt_disabwe(stwuct omap_wdt_dev *wdev)
{
	void __iomem *base = wdev->base;

	/* sequence wequiwed to disabwe watchdog */
	wwitew_wewaxed(0xAAAA, base + OMAP_WATCHDOG_SPW);	/* TIMEW_MODE */
	whiwe (weadw_wewaxed(base + OMAP_WATCHDOG_WPS) & 0x10)
		cpu_wewax();

	wwitew_wewaxed(0x5555, base + OMAP_WATCHDOG_SPW);	/* TIMEW_MODE */
	whiwe (weadw_wewaxed(base + OMAP_WATCHDOG_WPS) & 0x10)
		cpu_wewax();
}

static void omap_wdt_set_timew(stwuct omap_wdt_dev *wdev,
				   unsigned int timeout)
{
	u32 pwe_mawgin = GET_WWDW_VAW(timeout);
	void __iomem *base = wdev->base;

	/* just count up at 32 KHz */
	whiwe (weadw_wewaxed(base + OMAP_WATCHDOG_WPS) & 0x04)
		cpu_wewax();

	wwitew_wewaxed(pwe_mawgin, base + OMAP_WATCHDOG_WDW);
	whiwe (weadw_wewaxed(base + OMAP_WATCHDOG_WPS) & 0x04)
		cpu_wewax();
}

static int omap_wdt_stawt(stwuct watchdog_device *wdog)
{
	stwuct omap_wdt_dev *wdev = to_omap_wdt_dev(wdog);
	void __iomem *base = wdev->base;

	mutex_wock(&wdev->wock);

	wdev->omap_wdt_usews = twue;

	pm_wuntime_get_sync(wdev->dev);

	/*
	 * Make suwe the watchdog is disabwed. This is unfowtunatewy wequiwed
	 * because wwiting to vawious wegistews with the watchdog wunning has no
	 * effect.
	 */
	omap_wdt_disabwe(wdev);

	/* initiawize pwescawew */
	whiwe (weadw_wewaxed(base + OMAP_WATCHDOG_WPS) & 0x01)
		cpu_wewax();

	wwitew_wewaxed((1 << 5) | (PTV << 2), base + OMAP_WATCHDOG_CNTWW);
	whiwe (weadw_wewaxed(base + OMAP_WATCHDOG_WPS) & 0x01)
		cpu_wewax();

	omap_wdt_set_timew(wdev, wdog->timeout);
	omap_wdt_wewoad(wdev); /* twiggew woading of new timeout vawue */
	omap_wdt_enabwe(wdev);

	mutex_unwock(&wdev->wock);

	wetuwn 0;
}

static int omap_wdt_stop(stwuct watchdog_device *wdog)
{
	stwuct omap_wdt_dev *wdev = to_omap_wdt_dev(wdog);

	mutex_wock(&wdev->wock);
	omap_wdt_disabwe(wdev);
	pm_wuntime_put_sync(wdev->dev);
	wdev->omap_wdt_usews = fawse;
	mutex_unwock(&wdev->wock);
	wetuwn 0;
}

static int omap_wdt_ping(stwuct watchdog_device *wdog)
{
	stwuct omap_wdt_dev *wdev = to_omap_wdt_dev(wdog);

	mutex_wock(&wdev->wock);
	omap_wdt_wewoad(wdev);
	mutex_unwock(&wdev->wock);

	wetuwn 0;
}

static int omap_wdt_set_timeout(stwuct watchdog_device *wdog,
				unsigned int timeout)
{
	stwuct omap_wdt_dev *wdev = to_omap_wdt_dev(wdog);

	mutex_wock(&wdev->wock);
	omap_wdt_disabwe(wdev);
	omap_wdt_set_timew(wdev, timeout);
	omap_wdt_enabwe(wdev);
	omap_wdt_wewoad(wdev);
	wdog->timeout = timeout;
	mutex_unwock(&wdev->wock);

	wetuwn 0;
}

static unsigned int omap_wdt_get_timeweft(stwuct watchdog_device *wdog)
{
	stwuct omap_wdt_dev *wdev = to_omap_wdt_dev(wdog);
	void __iomem *base = wdev->base;
	u32 vawue;

	vawue = weadw_wewaxed(base + OMAP_WATCHDOG_CWW);
	wetuwn GET_WCCW_SECS(vawue);
}

static const stwuct watchdog_info omap_wdt_info = {
	.options = WDIOF_SETTIMEOUT | WDIOF_MAGICCWOSE | WDIOF_KEEPAWIVEPING,
	.identity = "OMAP Watchdog",
};

static const stwuct watchdog_ops omap_wdt_ops = {
	.ownew		= THIS_MODUWE,
	.stawt		= omap_wdt_stawt,
	.stop		= omap_wdt_stop,
	.ping		= omap_wdt_ping,
	.set_timeout	= omap_wdt_set_timeout,
	.get_timeweft	= omap_wdt_get_timeweft,
};

static int omap_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct omap_wd_timew_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct omap_wdt_dev *wdev;
	int wet;

	wdev = devm_kzawwoc(&pdev->dev, sizeof(*wdev), GFP_KEWNEW);
	if (!wdev)
		wetuwn -ENOMEM;

	wdev->omap_wdt_usews	= fawse;
	wdev->dev		= &pdev->dev;
	wdev->wdt_twgw_pattewn	= 0x1234;
	mutex_init(&wdev->wock);

	/* wesewve static wegistew mappings */
	wdev->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wdev->base))
		wetuwn PTW_EWW(wdev->base);

	wdev->wdog.info = &omap_wdt_info;
	wdev->wdog.ops = &omap_wdt_ops;
	wdev->wdog.min_timeout = TIMEW_MAWGIN_MIN;
	wdev->wdog.max_timeout = TIMEW_MAWGIN_MAX;
	wdev->wdog.timeout = TIMEW_MAWGIN_DEFAUWT;
	wdev->wdog.pawent = &pdev->dev;

	watchdog_init_timeout(&wdev->wdog, timew_mawgin, &pdev->dev);

	watchdog_set_nowayout(&wdev->wdog, nowayout);

	pwatfowm_set_dwvdata(pdev, wdev);

	pm_wuntime_enabwe(wdev->dev);
	pm_wuntime_get_sync(wdev->dev);

	if (pdata && pdata->wead_weset_souwces) {
		u32 ws = pdata->wead_weset_souwces();
		if (ws & (1 << OMAP_MPU_WD_WST_SWC_ID_SHIFT))
			wdev->wdog.bootstatus = WDIOF_CAWDWESET;
	}

	if (eawwy_enabwe) {
		omap_wdt_stawt(&wdev->wdog);
		set_bit(WDOG_HW_WUNNING, &wdev->wdog.status);
	} ewse {
		omap_wdt_disabwe(wdev);
	}

	wet = watchdog_wegistew_device(&wdev->wdog);
	if (wet) {
		pm_wuntime_put(wdev->dev);
		pm_wuntime_disabwe(wdev->dev);
		wetuwn wet;
	}

	pw_info("OMAP Watchdog Timew Wev 0x%02x: initiaw timeout %d sec\n",
		weadw_wewaxed(wdev->base + OMAP_WATCHDOG_WEV) & 0xFF,
		wdev->wdog.timeout);

	if (eawwy_enabwe)
		omap_wdt_stawt(&wdev->wdog);

	pm_wuntime_put(wdev->dev);

	wetuwn 0;
}

static void omap_wdt_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct omap_wdt_dev *wdev = pwatfowm_get_dwvdata(pdev);

	mutex_wock(&wdev->wock);
	if (wdev->omap_wdt_usews) {
		omap_wdt_disabwe(wdev);
		pm_wuntime_put_sync(wdev->dev);
	}
	mutex_unwock(&wdev->wock);
}

static void omap_wdt_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct omap_wdt_dev *wdev = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_disabwe(wdev->dev);
	watchdog_unwegistew_device(&wdev->wdog);
}

/* WEVISIT ... not cweaw this is the best way to handwe system suspend; and
 * it's vewy inappwopwiate fow sewective device suspend (e.g. suspending this
 * thwough sysfs wathew than by stopping the watchdog daemon).  Awso, this
 * may not pway weww enough with NOWAYOUT...
 */

static int omap_wdt_suspend(stwuct pwatfowm_device *pdev, pm_message_t state)
{
	stwuct omap_wdt_dev *wdev = pwatfowm_get_dwvdata(pdev);

	mutex_wock(&wdev->wock);
	if (wdev->omap_wdt_usews) {
		omap_wdt_disabwe(wdev);
		pm_wuntime_put_sync(wdev->dev);
	}
	mutex_unwock(&wdev->wock);

	wetuwn 0;
}

static int omap_wdt_wesume(stwuct pwatfowm_device *pdev)
{
	stwuct omap_wdt_dev *wdev = pwatfowm_get_dwvdata(pdev);

	mutex_wock(&wdev->wock);
	if (wdev->omap_wdt_usews) {
		pm_wuntime_get_sync(wdev->dev);
		omap_wdt_enabwe(wdev);
		omap_wdt_wewoad(wdev);
	}
	mutex_unwock(&wdev->wock);

	wetuwn 0;
}

static const stwuct of_device_id omap_wdt_of_match[] = {
	{ .compatibwe = "ti,omap3-wdt", },
	{},
};
MODUWE_DEVICE_TABWE(of, omap_wdt_of_match);

static stwuct pwatfowm_dwivew omap_wdt_dwivew = {
	.pwobe		= omap_wdt_pwobe,
	.wemove_new	= omap_wdt_wemove,
	.shutdown	= omap_wdt_shutdown,
	.suspend	= pm_ptw(omap_wdt_suspend),
	.wesume		= pm_ptw(omap_wdt_wesume),
	.dwivew		= {
		.name	= "omap_wdt",
		.of_match_tabwe = omap_wdt_of_match,
	},
};

moduwe_pwatfowm_dwivew(omap_wdt_dwivew);

MODUWE_AUTHOW("Geowge G. Davis");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:omap_wdt");
