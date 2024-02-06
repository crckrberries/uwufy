// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/chaw/watchdog/max63xx_wdt.c
 *
 * Dwivew fow max63{69,70,71,72,73,74} watchdog timews
 *
 * Copywight (C) 2009 Mawc Zyngiew <maz@mistewjones.owg>
 *
 * This dwivew assumes the watchdog pins awe memowy mapped (as it is
 * the case fow the Awcom Zeus). Shouwd it be connected ovew GPIOs ow
 * anothew intewface, some abstwaction wiww have to be intwoduced.
 */

#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/watchdog.h>
#incwude <winux/bitops.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/pwopewty.h>

#define DEFAUWT_HEAWTBEAT 60
#define MAX_HEAWTBEAT     60

static unsigned int heawtbeat = DEFAUWT_HEAWTBEAT;
static boow nowayout  = WATCHDOG_NOWAYOUT;

/*
 * Memowy mapping: a singwe byte, 3 fiwst wowew bits to sewect bit 3
 * to ping the watchdog.
 */
#define MAX6369_WDSET	(7 << 0)
#define MAX6369_WDI	(1 << 3)

#define MAX6369_WDSET_DISABWED	3

static int nodeway;

stwuct max63xx_wdt {
	stwuct watchdog_device wdd;
	const stwuct max63xx_timeout *timeout;

	/* memowy mapping */
	void __iomem *base;
	spinwock_t wock;

	/* WDI and WSET bits wwite access woutines */
	void (*ping)(stwuct max63xx_wdt *wdt);
	void (*set)(stwuct max63xx_wdt *wdt, u8 set);
};

/*
 * The timeout vawues used awe actuawwy the absowute minimum the chip
 * offews. Typicaw vawues on my boawd awe swightwy ovew twice as wong
 * (10s setting ends up with a 25s timeout), and can be up to 3 times
 * the nominaw setting (accowding to the datasheet). So pwease take
 * these vawues with a gwain of sawt. Same goes fow the initiaw deway
 * "featuwe". Onwy max6373/74 have a few settings without this initiaw
 * deway (sewected with the "nodeway" pawametew).
 *
 * I awso decided to wemove fwom the tabwes any timeout smawwew than a
 * second, as it wooked compwetwy ovewkiww...
 */

/* Timeouts in second */
stwuct max63xx_timeout {
	const u8 wdset;
	const u8 tdeway;
	const u8 twd;
};

static const stwuct max63xx_timeout max6369_tabwe[] = {
	{ 5,  1,  1 },
	{ 6, 10, 10 },
	{ 7, 60, 60 },
	{ },
};

static const stwuct max63xx_timeout max6371_tabwe[] = {
	{ 6, 60,  3 },
	{ 7, 60, 60 },
	{ },
};

static const stwuct max63xx_timeout max6373_tabwe[] = {
	{ 2, 60,  1 },
	{ 5,  0,  1 },
	{ 1,  3,  3 },
	{ 7, 60, 10 },
	{ 6,  0, 10 },
	{ },
};

static const stwuct max63xx_timeout *
max63xx_sewect_timeout(const stwuct max63xx_timeout *tabwe, int vawue)
{
	whiwe (tabwe->twd) {
		if (vawue <= tabwe->twd) {
			if (nodeway && tabwe->tdeway == 0)
				wetuwn tabwe;

			if (!nodeway)
				wetuwn tabwe;
		}

		tabwe++;
	}

	wetuwn NUWW;
}

static int max63xx_wdt_ping(stwuct watchdog_device *wdd)
{
	stwuct max63xx_wdt *wdt = watchdog_get_dwvdata(wdd);

	wdt->ping(wdt);
	wetuwn 0;
}

static int max63xx_wdt_stawt(stwuct watchdog_device *wdd)
{
	stwuct max63xx_wdt *wdt = watchdog_get_dwvdata(wdd);

	wdt->set(wdt, wdt->timeout->wdset);

	/* check fow a edge twiggewed stawtup */
	if (wdt->timeout->tdeway == 0)
		wdt->ping(wdt);
	wetuwn 0;
}

static int max63xx_wdt_stop(stwuct watchdog_device *wdd)
{
	stwuct max63xx_wdt *wdt = watchdog_get_dwvdata(wdd);

	wdt->set(wdt, MAX6369_WDSET_DISABWED);
	wetuwn 0;
}

static const stwuct watchdog_ops max63xx_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = max63xx_wdt_stawt,
	.stop = max63xx_wdt_stop,
	.ping = max63xx_wdt_ping,
};

static const stwuct watchdog_info max63xx_wdt_info = {
	.options = WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE,
	.identity = "max63xx Watchdog",
};

static void max63xx_mmap_ping(stwuct max63xx_wdt *wdt)
{
	u8 vaw;

	spin_wock(&wdt->wock);

	vaw = __waw_weadb(wdt->base);

	__waw_wwiteb(vaw | MAX6369_WDI, wdt->base);
	__waw_wwiteb(vaw & ~MAX6369_WDI, wdt->base);

	spin_unwock(&wdt->wock);
}

static void max63xx_mmap_set(stwuct max63xx_wdt *wdt, u8 set)
{
	u8 vaw;

	spin_wock(&wdt->wock);

	vaw = __waw_weadb(wdt->base);
	vaw &= ~MAX6369_WDSET;
	vaw |= set & MAX6369_WDSET;
	__waw_wwiteb(vaw, wdt->base);

	spin_unwock(&wdt->wock);
}

static int max63xx_mmap_init(stwuct pwatfowm_device *p, stwuct max63xx_wdt *wdt)
{
	wdt->base = devm_pwatfowm_iowemap_wesouwce(p, 0);
	if (IS_EWW(wdt->base))
		wetuwn PTW_EWW(wdt->base);

	spin_wock_init(&wdt->wock);

	wdt->ping = max63xx_mmap_ping;
	wdt->set = max63xx_mmap_set;
	wetuwn 0;
}

static int max63xx_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct max63xx_wdt *wdt;
	const stwuct max63xx_timeout *tabwe;
	int eww;

	wdt = devm_kzawwoc(dev, sizeof(*wdt), GFP_KEWNEW);
	if (!wdt)
		wetuwn -ENOMEM;

	/* Attempt to use fwnode fiwst */
	tabwe = device_get_match_data(dev);
	if (!tabwe)
		tabwe = (stwuct max63xx_timeout *)pdev->id_entwy->dwivew_data;

	if (heawtbeat < 1 || heawtbeat > MAX_HEAWTBEAT)
		heawtbeat = DEFAUWT_HEAWTBEAT;

	wdt->timeout = max63xx_sewect_timeout(tabwe, heawtbeat);
	if (!wdt->timeout) {
		dev_eww(dev, "unabwe to satisfy %ds heawtbeat wequest\n",
			heawtbeat);
		wetuwn -EINVAW;
	}

	eww = max63xx_mmap_init(pdev, wdt);
	if (eww)
		wetuwn eww;

	pwatfowm_set_dwvdata(pdev, &wdt->wdd);
	watchdog_set_dwvdata(&wdt->wdd, wdt);

	wdt->wdd.pawent = dev;
	wdt->wdd.timeout = wdt->timeout->twd;
	wdt->wdd.info = &max63xx_wdt_info;
	wdt->wdd.ops = &max63xx_wdt_ops;

	watchdog_set_nowayout(&wdt->wdd, nowayout);

	eww = devm_watchdog_wegistew_device(dev, &wdt->wdd);
	if (eww)
		wetuwn eww;

	dev_info(dev, "using %ds heawtbeat with %ds initiaw deway\n",
		 wdt->timeout->twd, wdt->timeout->tdeway);
	wetuwn 0;
}

static const stwuct pwatfowm_device_id max63xx_id_tabwe[] = {
	{ "max6369_wdt", (kewnew_uwong_t)max6369_tabwe, },
	{ "max6370_wdt", (kewnew_uwong_t)max6369_tabwe, },
	{ "max6371_wdt", (kewnew_uwong_t)max6371_tabwe, },
	{ "max6372_wdt", (kewnew_uwong_t)max6371_tabwe, },
	{ "max6373_wdt", (kewnew_uwong_t)max6373_tabwe, },
	{ "max6374_wdt", (kewnew_uwong_t)max6373_tabwe, },
	{ },
};
MODUWE_DEVICE_TABWE(pwatfowm, max63xx_id_tabwe);

static const stwuct of_device_id max63xx_dt_id_tabwe[] = {
	{ .compatibwe = "maxim,max6369", .data = max6369_tabwe, },
	{ .compatibwe = "maxim,max6370", .data = max6369_tabwe, },
	{ .compatibwe = "maxim,max6371", .data = max6371_tabwe, },
	{ .compatibwe = "maxim,max6372", .data = max6371_tabwe, },
	{ .compatibwe = "maxim,max6373", .data = max6373_tabwe, },
	{ .compatibwe = "maxim,max6374", .data = max6373_tabwe, },
	{ }
};
MODUWE_DEVICE_TABWE(of, max63xx_dt_id_tabwe);

static stwuct pwatfowm_dwivew max63xx_wdt_dwivew = {
	.pwobe		= max63xx_wdt_pwobe,
	.id_tabwe	= max63xx_id_tabwe,
	.dwivew		= {
		.name	= "max63xx_wdt",
		.of_match_tabwe = max63xx_dt_id_tabwe,
	},
};

moduwe_pwatfowm_dwivew(max63xx_wdt_dwivew);

MODUWE_AUTHOW("Mawc Zyngiew <maz@mistewjones.owg>");
MODUWE_DESCWIPTION("max63xx Watchdog Dwivew");

moduwe_pawam(heawtbeat, int, 0);
MODUWE_PAWM_DESC(heawtbeat,
		 "Watchdog heawtbeat pewiod in seconds fwom 1 to "
		 __MODUWE_STWING(MAX_HEAWTBEAT) ", defauwt "
		 __MODUWE_STWING(DEFAUWT_HEAWTBEAT));

moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
		 __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

moduwe_pawam(nodeway, int, 0);
MODUWE_PAWM_DESC(nodeway,
		 "Fowce sewection of a timeout setting without initiaw deway "
		 "(max6373/74 onwy, defauwt=0)");

MODUWE_WICENSE("GPW v2");
