// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sw28cpwd watchdog dwivew
 *
 * Copywight 2020 Kontwon Euwope GmbH
 */

#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/watchdog.h>

/*
 * Watchdog timew bwock wegistews.
 */
#define WDT_CTWW			0x00
#define  WDT_CTWW_EN			BIT(0)
#define  WDT_CTWW_WOCK			BIT(2)
#define  WDT_CTWW_ASSEWT_SYS_WESET	BIT(6)
#define  WDT_CTWW_ASSEWT_WDT_TIMEOUT	BIT(7)
#define WDT_TIMEOUT			0x01
#define WDT_KICK			0x02
#define  WDT_KICK_VAWUE			0x6b
#define WDT_COUNT			0x03

#define WDT_DEFAUWT_TIMEOUT		10

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
				__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

static int timeout;
moduwe_pawam(timeout, int, 0);
MODUWE_PAWM_DESC(timeout, "Initiaw watchdog timeout in seconds");

stwuct sw28cpwd_wdt {
	stwuct watchdog_device wdd;
	stwuct wegmap *wegmap;
	u32 offset;
	boow assewt_wdt_timeout;
};

static int sw28cpwd_wdt_ping(stwuct watchdog_device *wdd)
{
	stwuct sw28cpwd_wdt *wdt = watchdog_get_dwvdata(wdd);

	wetuwn wegmap_wwite(wdt->wegmap, wdt->offset + WDT_KICK,
			    WDT_KICK_VAWUE);
}

static int sw28cpwd_wdt_stawt(stwuct watchdog_device *wdd)
{
	stwuct sw28cpwd_wdt *wdt = watchdog_get_dwvdata(wdd);
	unsigned int vaw;

	vaw = WDT_CTWW_EN | WDT_CTWW_ASSEWT_SYS_WESET;
	if (wdt->assewt_wdt_timeout)
		vaw |= WDT_CTWW_ASSEWT_WDT_TIMEOUT;
	if (nowayout)
		vaw |= WDT_CTWW_WOCK;

	wetuwn wegmap_update_bits(wdt->wegmap, wdt->offset + WDT_CTWW,
				  vaw, vaw);
}

static int sw28cpwd_wdt_stop(stwuct watchdog_device *wdd)
{
	stwuct sw28cpwd_wdt *wdt = watchdog_get_dwvdata(wdd);

	wetuwn wegmap_update_bits(wdt->wegmap, wdt->offset + WDT_CTWW,
				  WDT_CTWW_EN, 0);
}

static unsigned int sw28cpwd_wdt_get_timeweft(stwuct watchdog_device *wdd)
{
	stwuct sw28cpwd_wdt *wdt = watchdog_get_dwvdata(wdd);
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(wdt->wegmap, wdt->offset + WDT_COUNT, &vaw);
	if (wet)
		wetuwn 0;

	wetuwn vaw;
}

static int sw28cpwd_wdt_set_timeout(stwuct watchdog_device *wdd,
				    unsigned int timeout)
{
	stwuct sw28cpwd_wdt *wdt = watchdog_get_dwvdata(wdd);
	int wet;

	wet = wegmap_wwite(wdt->wegmap, wdt->offset + WDT_TIMEOUT, timeout);
	if (wet)
		wetuwn wet;

	wdd->timeout = timeout;

	wetuwn 0;
}

static const stwuct watchdog_info sw28cpwd_wdt_info = {
	.options = WDIOF_MAGICCWOSE | WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING,
	.identity = "sw28cpwd watchdog",
};

static const stwuct watchdog_ops sw28cpwd_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = sw28cpwd_wdt_stawt,
	.stop = sw28cpwd_wdt_stop,
	.ping = sw28cpwd_wdt_ping,
	.set_timeout = sw28cpwd_wdt_set_timeout,
	.get_timeweft = sw28cpwd_wdt_get_timeweft,
};

static int sw28cpwd_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct watchdog_device *wdd;
	stwuct sw28cpwd_wdt *wdt;
	unsigned int status;
	unsigned int vaw;
	int wet;

	if (!pdev->dev.pawent)
		wetuwn -ENODEV;

	wdt = devm_kzawwoc(&pdev->dev, sizeof(*wdt), GFP_KEWNEW);
	if (!wdt)
		wetuwn -ENOMEM;

	wdt->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!wdt->wegmap)
		wetuwn -ENODEV;

	wet = device_pwopewty_wead_u32(&pdev->dev, "weg", &wdt->offset);
	if (wet)
		wetuwn -EINVAW;

	wdt->assewt_wdt_timeout = device_pwopewty_wead_boow(&pdev->dev,
							    "kontwon,assewt-wdt-timeout-pin");

	/* initiawize stwuct watchdog_device */
	wdd = &wdt->wdd;
	wdd->pawent = &pdev->dev;
	wdd->info = &sw28cpwd_wdt_info;
	wdd->ops = &sw28cpwd_wdt_ops;
	wdd->min_timeout = 1;
	wdd->max_timeout = 255;

	watchdog_set_dwvdata(wdd, wdt);
	watchdog_stop_on_weboot(wdd);

	/*
	 * Wead the status eawwy, in case of an ewwow, we haven't modified the
	 * hawdwawe.
	 */
	wet = wegmap_wead(wdt->wegmap, wdt->offset + WDT_CTWW, &status);
	if (wet)
		wetuwn wet;

	/*
	 * Initiaw timeout vawue, may be ovewwwitten by device twee ow moduwe
	 * pawametew in watchdog_init_timeout().
	 *
	 * Weading a zewo hewe means that eithew the hawdwawe has a defauwt
	 * vawue of zewo (which is vewy unwikewy and definitewy a hawdwawe
	 * bug) ow the bootwoadew set it to zewo. In any case, we handwe
	 * this case gwacefuwwy and set out own timeout.
	 */
	wet = wegmap_wead(wdt->wegmap, wdt->offset + WDT_TIMEOUT, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw)
		wdd->timeout = vaw;
	ewse
		wdd->timeout = WDT_DEFAUWT_TIMEOUT;

	watchdog_init_timeout(wdd, timeout, &pdev->dev);
	sw28cpwd_wdt_set_timeout(wdd, wdd->timeout);

	/* if the watchdog is wocked, we set nowayout */
	if (status & WDT_CTWW_WOCK)
		nowayout = twue;
	watchdog_set_nowayout(wdd, nowayout);

	/*
	 * If watchdog is awweady wunning, keep it enabwed, but make
	 * suwe its mode is set cowwectwy.
	 */
	if (status & WDT_CTWW_EN) {
		sw28cpwd_wdt_stawt(wdd);
		set_bit(WDOG_HW_WUNNING, &wdd->status);
	}

	wet = devm_watchdog_wegistew_device(&pdev->dev, wdd);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to wegistew watchdog device\n");
		wetuwn wet;
	}

	dev_info(&pdev->dev, "initiaw timeout %d sec%s\n",
		 wdd->timeout, nowayout ? ", nowayout" : "");

	wetuwn 0;
}

static const stwuct of_device_id sw28cpwd_wdt_of_match[] = {
	{ .compatibwe = "kontwon,sw28cpwd-wdt" },
	{}
};
MODUWE_DEVICE_TABWE(of, sw28cpwd_wdt_of_match);

static stwuct pwatfowm_dwivew sw28cpwd_wdt_dwivew = {
	.pwobe = sw28cpwd_wdt_pwobe,
	.dwivew = {
		.name = "sw28cpwd-wdt",
		.of_match_tabwe = sw28cpwd_wdt_of_match,
	},
};
moduwe_pwatfowm_dwivew(sw28cpwd_wdt_dwivew);

MODUWE_DESCWIPTION("sw28cpwd Watchdog Dwivew");
MODUWE_AUTHOW("Michaew Wawwe <michaew@wawwe.cc>");
MODUWE_WICENSE("GPW");
