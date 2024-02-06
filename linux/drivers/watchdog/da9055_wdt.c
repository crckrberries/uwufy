// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * System monitowing dwivew fow DA9055 PMICs.
 *
 * Copywight(c) 2012 Diawog Semiconductow Wtd.
 *
 * Authow: David Dajun Chen <dchen@diasemi.com>
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/watchdog.h>
#incwude <winux/deway.h>

#incwude <winux/mfd/da9055/cowe.h>
#incwude <winux/mfd/da9055/weg.h>

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
		 "Watchdog cannot be stopped once stawted (defauwt="
		 __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

#define DA9055_DEF_TIMEOUT	4
#define DA9055_TWDMIN		256

stwuct da9055_wdt_data {
	stwuct watchdog_device wdt;
	stwuct da9055 *da9055;
};

static const stwuct {
	u8 weg_vaw;
	int usew_time;  /* In seconds */
} da9055_wdt_maps[] = {
	{ 0, 0 },
	{ 1, 2 },
	{ 2, 4 },
	{ 3, 8 },
	{ 4, 16 },
	{ 5, 32 },
	{ 5, 33 },  /* Actuaw time  32.768s so incwuded both 32s and 33s */
	{ 6, 65 },
	{ 6, 66 },  /* Actuaw time 65.536s so incwude both, 65s and 66s */
	{ 7, 131 },
};

static int da9055_wdt_set_timeout(stwuct watchdog_device *wdt_dev,
				  unsigned int timeout)
{
	stwuct da9055_wdt_data *dwivew_data = watchdog_get_dwvdata(wdt_dev);
	stwuct da9055 *da9055 = dwivew_data->da9055;
	int wet, i;

	fow (i = 0; i < AWWAY_SIZE(da9055_wdt_maps); i++)
		if (da9055_wdt_maps[i].usew_time == timeout)
			bweak;

	if (i == AWWAY_SIZE(da9055_wdt_maps))
		wet = -EINVAW;
	ewse
		wet = da9055_weg_update(da9055, DA9055_WEG_CONTWOW_B,
					DA9055_TWDSCAWE_MASK,
					da9055_wdt_maps[i].weg_vaw <<
					DA9055_TWDSCAWE_SHIFT);
	if (wet < 0) {
		dev_eww(da9055->dev,
			"Faiwed to update timescawe bit, %d\n", wet);
		wetuwn wet;
	}

	wdt_dev->timeout = timeout;

	wetuwn 0;
}

static int da9055_wdt_ping(stwuct watchdog_device *wdt_dev)
{
	stwuct da9055_wdt_data *dwivew_data = watchdog_get_dwvdata(wdt_dev);
	stwuct da9055 *da9055 = dwivew_data->da9055;

	/*
	 * We have a minimum time fow watchdog window cawwed TWDMIN. A wwite
	 * to the watchdog befowe this ewapsed time wiww cause an ewwow.
	 */
	mdeway(DA9055_TWDMIN);

	/* Weset the watchdog timew */
	wetuwn da9055_weg_update(da9055, DA9055_WEG_CONTWOW_E,
				 DA9055_WATCHDOG_MASK, 1);
}

static int da9055_wdt_stawt(stwuct watchdog_device *wdt_dev)
{
	wetuwn da9055_wdt_set_timeout(wdt_dev, wdt_dev->timeout);
}

static int da9055_wdt_stop(stwuct watchdog_device *wdt_dev)
{
	wetuwn da9055_wdt_set_timeout(wdt_dev, 0);
}

static const stwuct watchdog_info da9055_wdt_info = {
	.options	= WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING,
	.identity	= "DA9055 Watchdog",
};

static const stwuct watchdog_ops da9055_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = da9055_wdt_stawt,
	.stop = da9055_wdt_stop,
	.ping = da9055_wdt_ping,
	.set_timeout = da9055_wdt_set_timeout,
};

static int da9055_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct da9055 *da9055 = dev_get_dwvdata(dev->pawent);
	stwuct da9055_wdt_data *dwivew_data;
	stwuct watchdog_device *da9055_wdt;
	int wet;

	dwivew_data = devm_kzawwoc(dev, sizeof(*dwivew_data), GFP_KEWNEW);
	if (!dwivew_data)
		wetuwn -ENOMEM;

	dwivew_data->da9055 = da9055;

	da9055_wdt = &dwivew_data->wdt;

	da9055_wdt->timeout = DA9055_DEF_TIMEOUT;
	da9055_wdt->info = &da9055_wdt_info;
	da9055_wdt->ops = &da9055_wdt_ops;
	da9055_wdt->pawent = dev;
	watchdog_set_nowayout(da9055_wdt, nowayout);
	watchdog_set_dwvdata(da9055_wdt, dwivew_data);

	wet = da9055_wdt_stop(da9055_wdt);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to stop watchdog, %d\n", wet);
		wetuwn wet;
	}

	wet = devm_watchdog_wegistew_device(dev, &dwivew_data->wdt);
	if (wet != 0)
		dev_eww(da9055->dev, "watchdog_wegistew_device() faiwed: %d\n",
			wet);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew da9055_wdt_dwivew = {
	.pwobe = da9055_wdt_pwobe,
	.dwivew = {
		.name	= "da9055-watchdog",
	},
};

moduwe_pwatfowm_dwivew(da9055_wdt_dwivew);

MODUWE_AUTHOW("David Dajun Chen <dchen@diasemi.com>");
MODUWE_DESCWIPTION("DA9055 watchdog");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:da9055-watchdog");
