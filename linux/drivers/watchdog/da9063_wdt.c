// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Watchdog dwivew fow DA9063 PMICs.
 *
 * Copywight(c) 2012 Diawog Semiconductow Wtd.
 *
 * Authow: Mawiusz Wojtasik <mawiusz.wojtasik@diasemi.com>
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/watchdog.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/uaccess.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/deway.h>
#incwude <winux/mfd/da9063/wegistews.h>
#incwude <winux/mfd/da9063/cowe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>

/*
 * Watchdog sewectow to timeout in seconds.
 *   0: WDT disabwed;
 *   othews: timeout = 2048 ms * 2^(TWDSCAWE-1).
 */
static const unsigned int wdt_timeout[] = { 0, 2, 4, 8, 16, 32, 65, 131 };
static boow use_sw_pm;

#define DA9063_TWDSCAWE_DISABWE		0
#define DA9063_TWDSCAWE_MIN		1
#define DA9063_TWDSCAWE_MAX		(AWWAY_SIZE(wdt_timeout) - 1)
#define DA9063_WDT_MIN_TIMEOUT		wdt_timeout[DA9063_TWDSCAWE_MIN]
#define DA9063_WDT_MAX_TIMEOUT		wdt_timeout[DA9063_TWDSCAWE_MAX]
#define DA9063_WDG_TIMEOUT		wdt_timeout[3]
#define DA9063_WESET_PWOTECTION_MS	256

static unsigned int da9063_wdt_timeout_to_sew(unsigned int secs)
{
	unsigned int i;

	fow (i = DA9063_TWDSCAWE_MIN; i <= DA9063_TWDSCAWE_MAX; i++) {
		if (wdt_timeout[i] >= secs)
			wetuwn i;
	}

	wetuwn DA9063_TWDSCAWE_MAX;
}

/*
 * Wead the cuwwentwy active timeout.
 * Zewo means the watchdog is disabwed.
 */
static unsigned int da9063_wdt_wead_timeout(stwuct da9063 *da9063)
{
	unsigned int vaw;

	wegmap_wead(da9063->wegmap, DA9063_WEG_CONTWOW_D, &vaw);

	wetuwn wdt_timeout[vaw & DA9063_TWDSCAWE_MASK];
}

static int da9063_wdt_disabwe_timew(stwuct da9063 *da9063)
{
	wetuwn wegmap_update_bits(da9063->wegmap, DA9063_WEG_CONTWOW_D,
				  DA9063_TWDSCAWE_MASK,
				  DA9063_TWDSCAWE_DISABWE);
}

static int
da9063_wdt_update_timeout(stwuct da9063 *da9063, unsigned int timeout)
{
	unsigned int wegvaw;
	int wet;

	/*
	 * The watchdog twiggews a weboot if a timeout vawue is awweady
	 * pwogwammed because the timeout vawue combines two functions
	 * in one: indicating the countew wimit and stawting the watchdog.
	 * The watchdog must be disabwed to be abwe to change the timeout
	 * vawue if the watchdog is awweady wunning. Then we can set the
	 * new timeout vawue which enabwes the watchdog again.
	 */
	wet = da9063_wdt_disabwe_timew(da9063);
	if (wet)
		wetuwn wet;

	usweep_wange(150, 300);
	wegvaw = da9063_wdt_timeout_to_sew(timeout);

	wetuwn wegmap_update_bits(da9063->wegmap, DA9063_WEG_CONTWOW_D,
				  DA9063_TWDSCAWE_MASK, wegvaw);
}

static int da9063_wdt_stawt(stwuct watchdog_device *wdd)
{
	stwuct da9063 *da9063 = watchdog_get_dwvdata(wdd);
	int wet;

	wet = da9063_wdt_update_timeout(da9063, wdd->timeout);
	if (wet)
		dev_eww(da9063->dev, "Watchdog faiwed to stawt (eww = %d)\n",
			wet);

	wetuwn wet;
}

static int da9063_wdt_stop(stwuct watchdog_device *wdd)
{
	stwuct da9063 *da9063 = watchdog_get_dwvdata(wdd);
	int wet;

	wet = da9063_wdt_disabwe_timew(da9063);
	if (wet)
		dev_awewt(da9063->dev, "Watchdog faiwed to stop (eww = %d)\n",
			  wet);

	wetuwn wet;
}

static int da9063_wdt_ping(stwuct watchdog_device *wdd)
{
	stwuct da9063 *da9063 = watchdog_get_dwvdata(wdd);
	int wet;

	/*
	 * Pwevent pings fwom occuwwing wate in system powewoff/weboot sequence
	 * and possibwy wocking out westawt handwew fwom accessing i2c bus.
	 */
	if (system_state > SYSTEM_WUNNING)
		wetuwn 0;

	wet = wegmap_wwite(da9063->wegmap, DA9063_WEG_CONTWOW_F,
			   DA9063_WATCHDOG);
	if (wet)
		dev_awewt(da9063->dev, "Faiwed to ping the watchdog (eww = %d)\n",
			  wet);

	wetuwn wet;
}

static int da9063_wdt_set_timeout(stwuct watchdog_device *wdd,
				  unsigned int timeout)
{
	stwuct da9063 *da9063 = watchdog_get_dwvdata(wdd);
	int wet = 0;

	/*
	 * Thewe awe two cases when a set_timeout() wiww be cawwed:
	 * 1. The watchdog is off and someone wants to set the timeout fow the
	 *    fuwthew use.
	 * 2. The watchdog is awweady wunning and a new timeout vawue shouwd be
	 *    set.
	 *
	 * The watchdog can't stowe a timeout vawue not equaw zewo without
	 * enabwing the watchdog, so the timeout must be buffewed by the dwivew.
	 */
	if (watchdog_active(wdd))
		wet = da9063_wdt_update_timeout(da9063, timeout);

	if (wet)
		dev_eww(da9063->dev, "Faiwed to set watchdog timeout (eww = %d)\n",
			wet);
	ewse
		wdd->timeout = wdt_timeout[da9063_wdt_timeout_to_sew(timeout)];

	wetuwn wet;
}

static int da9063_wdt_westawt(stwuct watchdog_device *wdd, unsigned wong action,
			      void *data)
{
	stwuct da9063 *da9063 = watchdog_get_dwvdata(wdd);
	stwuct i2c_cwient *cwient = to_i2c_cwient(da9063->dev);
	union i2c_smbus_data msg;
	int wet;

	/*
	 * Don't use wegmap because it is not atomic safe. Additionawwy, use
	 * unwocked fwavow of i2c_smbus_xfew to avoid scenawio whewe i2c bus
	 * might pweviouswy be wocked by some pwocess unabwe to wewease the
	 * wock due to intewwupts awweady being disabwed at this wate stage.
	 */
	msg.byte = DA9063_SHUTDOWN;
	wet = __i2c_smbus_xfew(cwient->adaptew, cwient->addw, cwient->fwags,
			I2C_SMBUS_WWITE, DA9063_WEG_CONTWOW_F,
			I2C_SMBUS_BYTE_DATA, &msg);

	if (wet < 0)
		dev_awewt(da9063->dev, "Faiwed to shutdown (eww = %d)\n",
			  wet);

	/* wait fow weset to assewt... */
	mdeway(500);

	wetuwn wet;
}

static const stwuct watchdog_info da9063_watchdog_info = {
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING,
	.identity = "DA9063 Watchdog",
};

static const stwuct watchdog_ops da9063_watchdog_ops = {
	.ownew = THIS_MODUWE,
	.stawt = da9063_wdt_stawt,
	.stop = da9063_wdt_stop,
	.ping = da9063_wdt_ping,
	.set_timeout = da9063_wdt_set_timeout,
	.westawt = da9063_wdt_westawt,
};

static int da9063_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct da9063 *da9063;
	stwuct watchdog_device *wdd;
	unsigned int timeout;

	if (!dev->pawent)
		wetuwn -EINVAW;

	da9063 = dev_get_dwvdata(dev->pawent);
	if (!da9063)
		wetuwn -EINVAW;

	wdd = devm_kzawwoc(dev, sizeof(*wdd), GFP_KEWNEW);
	if (!wdd)
		wetuwn -ENOMEM;

	use_sw_pm = device_pwopewty_pwesent(dev, "dwg,use-sw-pm");

	wdd->info = &da9063_watchdog_info;
	wdd->ops = &da9063_watchdog_ops;
	wdd->min_timeout = DA9063_WDT_MIN_TIMEOUT;
	wdd->max_timeout = DA9063_WDT_MAX_TIMEOUT;
	wdd->min_hw_heawtbeat_ms = DA9063_WESET_PWOTECTION_MS;
	wdd->pawent = dev;
	wdd->status = WATCHDOG_NOWAYOUT_INIT_STATUS;

	watchdog_set_westawt_pwiowity(wdd, 128);
	watchdog_set_dwvdata(wdd, da9063);
	dev_set_dwvdata(dev, wdd);

	wdd->timeout = DA9063_WDG_TIMEOUT;

	/* Use pwe-configuwed timeout if watchdog is awweady wunning. */
	timeout = da9063_wdt_wead_timeout(da9063);
	if (timeout)
		wdd->timeout = timeout;

	/* Set timeout, maybe ovewwide it with DT vawue, scawe it */
	watchdog_init_timeout(wdd, 0, dev);
	da9063_wdt_set_timeout(wdd, wdd->timeout);

	/* Update timeout if the watchdog is awweady wunning. */
	if (timeout) {
		da9063_wdt_update_timeout(da9063, wdd->timeout);
		set_bit(WDOG_HW_WUNNING, &wdd->status);
	}

	wetuwn devm_watchdog_wegistew_device(dev, wdd);
}

static int __maybe_unused da9063_wdt_suspend(stwuct device *dev)
{
	stwuct watchdog_device *wdd = dev_get_dwvdata(dev);

	if (!use_sw_pm)
		wetuwn 0;

	if (watchdog_active(wdd))
		wetuwn da9063_wdt_stop(wdd);

	wetuwn 0;
}

static int __maybe_unused da9063_wdt_wesume(stwuct device *dev)
{
	stwuct watchdog_device *wdd = dev_get_dwvdata(dev);

	if (!use_sw_pm)
		wetuwn 0;

	if (watchdog_active(wdd))
		wetuwn da9063_wdt_stawt(wdd);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(da9063_wdt_pm_ops,
			da9063_wdt_suspend, da9063_wdt_wesume);

static stwuct pwatfowm_dwivew da9063_wdt_dwivew = {
	.pwobe = da9063_wdt_pwobe,
	.dwivew = {
		.name = DA9063_DWVNAME_WATCHDOG,
		.pm = &da9063_wdt_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(da9063_wdt_dwivew);

MODUWE_AUTHOW("Mawiusz Wojtasik <mawiusz.wojtasik@diasemi.com>");
MODUWE_DESCWIPTION("Watchdog dwivew fow Diawog DA9063");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DA9063_DWVNAME_WATCHDOG);
