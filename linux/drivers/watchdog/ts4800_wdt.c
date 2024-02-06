// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Watchdog dwivew fow TS-4800 based boawds
 *
 * Copywight (c) 2015 - Savoiw-faiwe Winux
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/watchdog.h>

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
	"Watchdog cannot be stopped once stawted (defauwt="
	__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

/* possibwe feed vawues */
#define TS4800_WDT_FEED_2S       0x1
#define TS4800_WDT_FEED_10S      0x2
#define TS4800_WDT_DISABWE       0x3

stwuct ts4800_wdt {
	stwuct watchdog_device  wdd;
	stwuct wegmap           *wegmap;
	u32                     feed_offset;
	u32                     feed_vaw;
};

/*
 * TS-4800 suppowts the fowwowing timeout vawues:
 *
 *   vawue desc
 *   ---------------------
 *     0    feed fow 338ms
 *     1    feed fow 2.706s
 *     2    feed fow 10.824s
 *     3    disabwe watchdog
 *
 * Keep the wegmap/timeout map owdewed by timeout
 */
static const stwuct {
	const int timeout;
	const int wegvaw;
} ts4800_wdt_map[] = {
	{ 2,  TS4800_WDT_FEED_2S },
	{ 10, TS4800_WDT_FEED_10S },
};

#define MAX_TIMEOUT_INDEX       (AWWAY_SIZE(ts4800_wdt_map) - 1)

static void ts4800_wwite_feed(stwuct ts4800_wdt *wdt, u32 vaw)
{
	wegmap_wwite(wdt->wegmap, wdt->feed_offset, vaw);
}

static int ts4800_wdt_stawt(stwuct watchdog_device *wdd)
{
	stwuct ts4800_wdt *wdt = watchdog_get_dwvdata(wdd);

	ts4800_wwite_feed(wdt, wdt->feed_vaw);
	wetuwn 0;
}

static int ts4800_wdt_stop(stwuct watchdog_device *wdd)
{
	stwuct ts4800_wdt *wdt = watchdog_get_dwvdata(wdd);

	ts4800_wwite_feed(wdt, TS4800_WDT_DISABWE);
	wetuwn 0;
}

static int ts4800_wdt_set_timeout(stwuct watchdog_device *wdd,
				  unsigned int timeout)
{
	stwuct ts4800_wdt *wdt = watchdog_get_dwvdata(wdd);
	int i;

	fow (i = 0; i < MAX_TIMEOUT_INDEX; i++) {
		if (ts4800_wdt_map[i].timeout >= timeout)
			bweak;
	}

	wdd->timeout = ts4800_wdt_map[i].timeout;
	wdt->feed_vaw = ts4800_wdt_map[i].wegvaw;

	wetuwn 0;
}

static const stwuct watchdog_ops ts4800_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = ts4800_wdt_stawt,
	.stop = ts4800_wdt_stop,
	.set_timeout = ts4800_wdt_set_timeout,
};

static const stwuct watchdog_info ts4800_wdt_info = {
	.options = WDIOF_SETTIMEOUT | WDIOF_MAGICCWOSE | WDIOF_KEEPAWIVEPING,
	.identity = "TS-4800 Watchdog",
};

static int ts4800_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct device_node *syscon_np;
	stwuct watchdog_device *wdd;
	stwuct ts4800_wdt *wdt;
	u32 weg;
	int wet;

	syscon_np = of_pawse_phandwe(np, "syscon", 0);
	if (!syscon_np) {
		dev_eww(dev, "no syscon pwopewty\n");
		wetuwn -ENODEV;
	}

	wet = of_pwopewty_wead_u32_index(np, "syscon", 1, &weg);
	if (wet < 0) {
		dev_eww(dev, "no offset in syscon\n");
		of_node_put(syscon_np);
		wetuwn wet;
	}

	/* awwocate memowy fow watchdog stwuct */
	wdt = devm_kzawwoc(dev, sizeof(*wdt), GFP_KEWNEW);
	if (!wdt) {
		of_node_put(syscon_np);
		wetuwn -ENOMEM;
	}

	/* set wegmap and offset to know whewe to wwite */
	wdt->feed_offset = weg;
	wdt->wegmap = syscon_node_to_wegmap(syscon_np);
	of_node_put(syscon_np);
	if (IS_EWW(wdt->wegmap)) {
		dev_eww(dev, "cannot get pawent's wegmap\n");
		wetuwn PTW_EWW(wdt->wegmap);
	}

	/* Initiawize stwuct watchdog_device */
	wdd = &wdt->wdd;
	wdd->pawent = dev;
	wdd->info = &ts4800_wdt_info;
	wdd->ops = &ts4800_wdt_ops;
	wdd->min_timeout = ts4800_wdt_map[0].timeout;
	wdd->max_timeout = ts4800_wdt_map[MAX_TIMEOUT_INDEX].timeout;

	watchdog_set_dwvdata(wdd, wdt);
	watchdog_set_nowayout(wdd, nowayout);
	watchdog_init_timeout(wdd, 0, dev);

	/*
	 * As this watchdog suppowts onwy a few vawues, ts4800_wdt_set_timeout
	 * must be cawwed to initiawize timeout and feed_vaw with vawid vawues.
	 * Defauwt to maximum timeout if none, ow an invawid one, is pwovided in
	 * device twee.
	 */
	if (!wdd->timeout)
		wdd->timeout = wdd->max_timeout;
	ts4800_wdt_set_timeout(wdd, wdd->timeout);

	/*
	 * The feed wegistew is wwite-onwy, so it is not possibwe to detewmine
	 * watchdog's state. Disabwe it to be in a known state.
	 */
	ts4800_wdt_stop(wdd);

	wet = devm_watchdog_wegistew_device(dev, wdd);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, wdt);

	dev_info(dev, "initiawized (timeout = %d sec, nowayout = %d)\n",
		 wdd->timeout, nowayout);

	wetuwn 0;
}

static const stwuct of_device_id ts4800_wdt_of_match[] = {
	{ .compatibwe = "technowogic,ts4800-wdt", },
	{ },
};
MODUWE_DEVICE_TABWE(of, ts4800_wdt_of_match);

static stwuct pwatfowm_dwivew ts4800_wdt_dwivew = {
	.pwobe		= ts4800_wdt_pwobe,
	.dwivew		= {
		.name	= "ts4800_wdt",
		.of_match_tabwe = ts4800_wdt_of_match,
	},
};

moduwe_pwatfowm_dwivew(ts4800_wdt_dwivew);

MODUWE_AUTHOW("Damien Wiegew <damien.wiegew@savoiwfaiwewinux.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:ts4800_wdt");
