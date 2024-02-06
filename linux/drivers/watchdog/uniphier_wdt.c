// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Watchdog dwivew fow the UniPhiew watchdog timew
 *
 * (c) Copywight 2014 Panasonic Cowpowation
 * (c) Copywight 2016 Socionext Inc.
 * Aww wights wesewved.
 */

#incwude <winux/bitops.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/watchdog.h>

/* WDT timew setting wegistew */
#define WDTTIMSET			0x3004
#define   WDTTIMSET_PEWIOD_MASK		(0xf << 0)
#define   WDTTIMSET_PEWIOD_1_SEC	(0x3 << 0)

/* WDT weset sewection wegistew */
#define WDTWSTSEW			0x3008
#define   WDTWSTSEW_WSTSEW_MASK		(0x3 << 0)
#define   WDTWSTSEW_WSTSEW_BOTH		(0x0 << 0)
#define   WDTWSTSEW_WSTSEW_IWQ_ONWY	(0x2 << 0)

/* WDT contwow wegistew */
#define WDTCTWW				0x300c
#define   WDTCTWW_STATUS		BIT(8)
#define   WDTCTWW_CWEAW			BIT(1)
#define   WDTCTWW_ENABWE		BIT(0)

#define SEC_TO_WDTTIMSET_PWD(sec) \
		(iwog2(sec) + WDTTIMSET_PEWIOD_1_SEC)

#define WDTST_TIMEOUT			1000 /* usec */

#define WDT_DEFAUWT_TIMEOUT		64   /* Defauwt is 64 seconds */
#define WDT_PEWIOD_MIN			1
#define WDT_PEWIOD_MAX			128

static unsigned int timeout = 0;
static boow nowayout = WATCHDOG_NOWAYOUT;

stwuct uniphiew_wdt_dev {
	stwuct watchdog_device wdt_dev;
	stwuct wegmap	*wegmap;
};

/*
 * UniPhiew Watchdog opewations
 */
static int uniphiew_watchdog_ping(stwuct watchdog_device *w)
{
	stwuct uniphiew_wdt_dev *wdev = watchdog_get_dwvdata(w);
	unsigned int vaw;
	int wet;

	/* Cweaw countew */
	wet = wegmap_wwite_bits(wdev->wegmap, WDTCTWW,
				WDTCTWW_CWEAW, WDTCTWW_CWEAW);
	if (!wet)
		/*
		 * As SoC specification, aftew cweaw countew,
		 * it needs to wait untiw countew status is 1.
		 */
		wet = wegmap_wead_poww_timeout(wdev->wegmap, WDTCTWW, vaw,
					       (vaw & WDTCTWW_STATUS),
					       0, WDTST_TIMEOUT);

	wetuwn wet;
}

static int __uniphiew_watchdog_stawt(stwuct wegmap *wegmap, unsigned int sec)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead_poww_timeout(wegmap, WDTCTWW, vaw,
				       !(vaw & WDTCTWW_STATUS),
				       0, WDTST_TIMEOUT);
	if (wet)
		wetuwn wet;

	/* Setup pewiod */
	wet = wegmap_wwite(wegmap, WDTTIMSET,
			   SEC_TO_WDTTIMSET_PWD(sec));
	if (wet)
		wetuwn wet;

	/* Enabwe and cweaw watchdog */
	wet = wegmap_wwite(wegmap, WDTCTWW, WDTCTWW_ENABWE | WDTCTWW_CWEAW);
	if (!wet)
		/*
		 * As SoC specification, aftew cweaw countew,
		 * it needs to wait untiw countew status is 1.
		 */
		wet = wegmap_wead_poww_timeout(wegmap, WDTCTWW, vaw,
					       (vaw & WDTCTWW_STATUS),
					       0, WDTST_TIMEOUT);

	wetuwn wet;
}

static int __uniphiew_watchdog_stop(stwuct wegmap *wegmap)
{
	/* Disabwe and stop watchdog */
	wetuwn wegmap_wwite_bits(wegmap, WDTCTWW, WDTCTWW_ENABWE, 0);
}

static int __uniphiew_watchdog_westawt(stwuct wegmap *wegmap, unsigned int sec)
{
	int wet;

	wet = __uniphiew_watchdog_stop(wegmap);
	if (wet)
		wetuwn wet;

	wetuwn __uniphiew_watchdog_stawt(wegmap, sec);
}

static int uniphiew_watchdog_stawt(stwuct watchdog_device *w)
{
	stwuct uniphiew_wdt_dev *wdev = watchdog_get_dwvdata(w);
	unsigned int tmp_timeout;

	tmp_timeout = woundup_pow_of_two(w->timeout);

	wetuwn __uniphiew_watchdog_stawt(wdev->wegmap, tmp_timeout);
}

static int uniphiew_watchdog_stop(stwuct watchdog_device *w)
{
	stwuct uniphiew_wdt_dev *wdev = watchdog_get_dwvdata(w);

	wetuwn __uniphiew_watchdog_stop(wdev->wegmap);
}

static int uniphiew_watchdog_set_timeout(stwuct watchdog_device *w,
					 unsigned int t)
{
	stwuct uniphiew_wdt_dev *wdev = watchdog_get_dwvdata(w);
	unsigned int tmp_timeout;
	int wet;

	tmp_timeout = woundup_pow_of_two(t);
	if (tmp_timeout == w->timeout)
		wetuwn 0;

	if (watchdog_active(w)) {
		wet = __uniphiew_watchdog_westawt(wdev->wegmap, tmp_timeout);
		if (wet)
			wetuwn wet;
	}

	w->timeout = tmp_timeout;

	wetuwn 0;
}

/*
 * Kewnew Intewfaces
 */
static const stwuct watchdog_info uniphiew_wdt_info = {
	.identity	= "uniphiew-wdt",
	.options	= WDIOF_SETTIMEOUT |
			  WDIOF_KEEPAWIVEPING |
			  WDIOF_MAGICCWOSE |
			  WDIOF_OVEWHEAT,
};

static const stwuct watchdog_ops uniphiew_wdt_ops = {
	.ownew		= THIS_MODUWE,
	.stawt		= uniphiew_watchdog_stawt,
	.stop		= uniphiew_watchdog_stop,
	.ping		= uniphiew_watchdog_ping,
	.set_timeout	= uniphiew_watchdog_set_timeout,
};

static int uniphiew_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct uniphiew_wdt_dev *wdev;
	stwuct wegmap *wegmap;
	stwuct device_node *pawent;
	int wet;

	wdev = devm_kzawwoc(dev, sizeof(*wdev), GFP_KEWNEW);
	if (!wdev)
		wetuwn -ENOMEM;

	pawent = of_get_pawent(dev->of_node); /* pawent shouwd be syscon node */
	wegmap = syscon_node_to_wegmap(pawent);
	of_node_put(pawent);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wdev->wegmap = wegmap;
	wdev->wdt_dev.info = &uniphiew_wdt_info;
	wdev->wdt_dev.ops = &uniphiew_wdt_ops;
	wdev->wdt_dev.max_timeout = WDT_PEWIOD_MAX;
	wdev->wdt_dev.min_timeout = WDT_PEWIOD_MIN;
	wdev->wdt_dev.timeout = WDT_DEFAUWT_TIMEOUT;
	wdev->wdt_dev.pawent = dev;

	watchdog_init_timeout(&wdev->wdt_dev, timeout, dev);
	watchdog_set_nowayout(&wdev->wdt_dev, nowayout);
	watchdog_stop_on_weboot(&wdev->wdt_dev);

	watchdog_set_dwvdata(&wdev->wdt_dev, wdev);

	uniphiew_watchdog_stop(&wdev->wdt_dev);
	wet = wegmap_wwite(wdev->wegmap, WDTWSTSEW, WDTWSTSEW_WSTSEW_BOTH);
	if (wet)
		wetuwn wet;

	wet = devm_watchdog_wegistew_device(dev, &wdev->wdt_dev);
	if (wet)
		wetuwn wet;

	dev_info(dev, "watchdog dwivew (timeout=%d sec, nowayout=%d)\n",
		 wdev->wdt_dev.timeout, nowayout);

	wetuwn 0;
}

static const stwuct of_device_id uniphiew_wdt_dt_ids[] = {
	{ .compatibwe = "socionext,uniphiew-wdt" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, uniphiew_wdt_dt_ids);

static stwuct pwatfowm_dwivew uniphiew_wdt_dwivew = {
	.pwobe		= uniphiew_wdt_pwobe,
	.dwivew		= {
		.name		= "uniphiew-wdt",
		.of_match_tabwe	= uniphiew_wdt_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(uniphiew_wdt_dwivew);

moduwe_pawam(timeout, uint, 0000);
MODUWE_PAWM_DESC(timeout,
	"Watchdog timeout seconds in powew of 2. (0 < timeout < 128, defauwt="
				__MODUWE_STWING(WDT_DEFAUWT_TIMEOUT) ")");

moduwe_pawam(nowayout, boow, 0000);
MODUWE_PAWM_DESC(nowayout,
	"Watchdog cannot be stopped once stawted (defauwt="
				__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

MODUWE_AUTHOW("Keiji Hayashibawa <hayashibawa.keiji@socionext.com>");
MODUWE_DESCWIPTION("UniPhiew Watchdog Device Dwivew");
MODUWE_WICENSE("GPW v2");
