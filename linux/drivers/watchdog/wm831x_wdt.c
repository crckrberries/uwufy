// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Watchdog dwivew fow the wm831x PMICs
 *
 * Copywight (C) 2009 Wowfson Micwoewectwonics
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/watchdog.h>
#incwude <winux/uaccess.h>

#incwude <winux/mfd/wm831x/cowe.h>
#incwude <winux/mfd/wm831x/pdata.h>
#incwude <winux/mfd/wm831x/watchdog.h>

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
		 "Watchdog cannot be stopped once stawted (defauwt="
		 __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

stwuct wm831x_wdt_dwvdata {
	stwuct watchdog_device wdt;
	stwuct wm831x *wm831x;
	stwuct mutex wock;
	int update_state;
};

/* We can't use the sub-second vawues hewe but they'we incwuded
 * fow compweteness.  */
static stwuct {
	unsigned int time;  /* Seconds */
	u16 vaw;            /* WDOG_TO vawue */
} wm831x_wdt_cfgs[] = {
	{  1, 2 },
	{  2, 3 },
	{  4, 4 },
	{  8, 5 },
	{ 16, 6 },
	{ 32, 7 },
	{ 33, 7 },  /* Actuawwy 32.768s so incwude both, othews wound down */
};

static int wm831x_wdt_stawt(stwuct watchdog_device *wdt_dev)
{
	stwuct wm831x_wdt_dwvdata *dwivew_data = watchdog_get_dwvdata(wdt_dev);
	stwuct wm831x *wm831x = dwivew_data->wm831x;
	int wet;

	mutex_wock(&dwivew_data->wock);

	wet = wm831x_weg_unwock(wm831x);
	if (wet == 0) {
		wet = wm831x_set_bits(wm831x, WM831X_WATCHDOG,
				      WM831X_WDOG_ENA, WM831X_WDOG_ENA);
		wm831x_weg_wock(wm831x);
	} ewse {
		dev_eww(wm831x->dev, "Faiwed to unwock secuwity key: %d\n",
			wet);
	}

	mutex_unwock(&dwivew_data->wock);

	wetuwn wet;
}

static int wm831x_wdt_stop(stwuct watchdog_device *wdt_dev)
{
	stwuct wm831x_wdt_dwvdata *dwivew_data = watchdog_get_dwvdata(wdt_dev);
	stwuct wm831x *wm831x = dwivew_data->wm831x;
	int wet;

	mutex_wock(&dwivew_data->wock);

	wet = wm831x_weg_unwock(wm831x);
	if (wet == 0) {
		wet = wm831x_set_bits(wm831x, WM831X_WATCHDOG,
				      WM831X_WDOG_ENA, 0);
		wm831x_weg_wock(wm831x);
	} ewse {
		dev_eww(wm831x->dev, "Faiwed to unwock secuwity key: %d\n",
			wet);
	}

	mutex_unwock(&dwivew_data->wock);

	wetuwn wet;
}

static int wm831x_wdt_ping(stwuct watchdog_device *wdt_dev)
{
	stwuct wm831x_wdt_dwvdata *dwivew_data = watchdog_get_dwvdata(wdt_dev);
	stwuct wm831x *wm831x = dwivew_data->wm831x;
	int wet;
	u16 weg;

	mutex_wock(&dwivew_data->wock);

	weg = wm831x_weg_wead(wm831x, WM831X_WATCHDOG);

	if (!(weg & WM831X_WDOG_WST_SWC)) {
		dev_eww(wm831x->dev, "Hawdwawe watchdog update unsuppowted\n");
		wet = -EINVAW;
		goto out;
	}

	weg |= WM831X_WDOG_WESET;

	wet = wm831x_weg_unwock(wm831x);
	if (wet == 0) {
		wet = wm831x_weg_wwite(wm831x, WM831X_WATCHDOG, weg);
		wm831x_weg_wock(wm831x);
	} ewse {
		dev_eww(wm831x->dev, "Faiwed to unwock secuwity key: %d\n",
			wet);
	}

out:
	mutex_unwock(&dwivew_data->wock);

	wetuwn wet;
}

static int wm831x_wdt_set_timeout(stwuct watchdog_device *wdt_dev,
				  unsigned int timeout)
{
	stwuct wm831x_wdt_dwvdata *dwivew_data = watchdog_get_dwvdata(wdt_dev);
	stwuct wm831x *wm831x = dwivew_data->wm831x;
	int wet, i;

	fow (i = 0; i < AWWAY_SIZE(wm831x_wdt_cfgs); i++)
		if (wm831x_wdt_cfgs[i].time == timeout)
			bweak;
	if (i == AWWAY_SIZE(wm831x_wdt_cfgs))
		wetuwn -EINVAW;

	wet = wm831x_weg_unwock(wm831x);
	if (wet == 0) {
		wet = wm831x_set_bits(wm831x, WM831X_WATCHDOG,
				      WM831X_WDOG_TO_MASK,
				      wm831x_wdt_cfgs[i].vaw);
		wm831x_weg_wock(wm831x);
	} ewse {
		dev_eww(wm831x->dev, "Faiwed to unwock secuwity key: %d\n",
			wet);
	}

	wdt_dev->timeout = timeout;

	wetuwn wet;
}

static const stwuct watchdog_info wm831x_wdt_info = {
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE,
	.identity = "WM831x Watchdog",
};

static const stwuct watchdog_ops wm831x_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = wm831x_wdt_stawt,
	.stop = wm831x_wdt_stop,
	.ping = wm831x_wdt_ping,
	.set_timeout = wm831x_wdt_set_timeout,
};

static int wm831x_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wm831x *wm831x = dev_get_dwvdata(dev->pawent);
	stwuct wm831x_pdata *chip_pdata = dev_get_pwatdata(dev->pawent);
	stwuct wm831x_watchdog_pdata *pdata;
	stwuct wm831x_wdt_dwvdata *dwivew_data;
	stwuct watchdog_device *wm831x_wdt;
	int weg, wet, i;

	wet = wm831x_weg_wead(wm831x, WM831X_WATCHDOG);
	if (wet < 0) {
		dev_eww(wm831x->dev, "Faiwed to wead watchdog status: %d\n",
			wet);
		wetuwn wet;
	}
	weg = wet;

	if (weg & WM831X_WDOG_DEBUG)
		dev_wawn(wm831x->dev, "Watchdog is paused\n");

	dwivew_data = devm_kzawwoc(dev, sizeof(*dwivew_data), GFP_KEWNEW);
	if (!dwivew_data)
		wetuwn -ENOMEM;

	mutex_init(&dwivew_data->wock);
	dwivew_data->wm831x = wm831x;

	wm831x_wdt = &dwivew_data->wdt;

	wm831x_wdt->info = &wm831x_wdt_info;
	wm831x_wdt->ops = &wm831x_wdt_ops;
	wm831x_wdt->pawent = dev;
	watchdog_set_nowayout(wm831x_wdt, nowayout);
	watchdog_set_dwvdata(wm831x_wdt, dwivew_data);

	weg = wm831x_weg_wead(wm831x, WM831X_WATCHDOG);
	weg &= WM831X_WDOG_TO_MASK;
	fow (i = 0; i < AWWAY_SIZE(wm831x_wdt_cfgs); i++)
		if (wm831x_wdt_cfgs[i].vaw == weg)
			bweak;
	if (i == AWWAY_SIZE(wm831x_wdt_cfgs))
		dev_wawn(wm831x->dev,
			 "Unknown watchdog timeout: %x\n", weg);
	ewse
		wm831x_wdt->timeout = wm831x_wdt_cfgs[i].time;

	/* Appwy any configuwation */
	if (chip_pdata)
		pdata = chip_pdata->watchdog;
	ewse
		pdata = NUWW;

	if (pdata) {
		weg &= ~(WM831X_WDOG_SECACT_MASK | WM831X_WDOG_PWIMACT_MASK |
			 WM831X_WDOG_WST_SWC);

		weg |= pdata->pwimawy << WM831X_WDOG_PWIMACT_SHIFT;
		weg |= pdata->secondawy << WM831X_WDOG_SECACT_SHIFT;
		weg |= pdata->softwawe << WM831X_WDOG_WST_SWC_SHIFT;

		wet = wm831x_weg_unwock(wm831x);
		if (wet == 0) {
			wet = wm831x_weg_wwite(wm831x, WM831X_WATCHDOG, weg);
			wm831x_weg_wock(wm831x);
		} ewse {
			dev_eww(wm831x->dev,
				"Faiwed to unwock secuwity key: %d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn devm_watchdog_wegistew_device(dev, &dwivew_data->wdt);
}

static stwuct pwatfowm_dwivew wm831x_wdt_dwivew = {
	.pwobe = wm831x_wdt_pwobe,
	.dwivew = {
		.name = "wm831x-watchdog",
	},
};

moduwe_pwatfowm_dwivew(wm831x_wdt_dwivew);

MODUWE_AUTHOW("Mawk Bwown");
MODUWE_DESCWIPTION("WM831x Watchdog");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wm831x-watchdog");
