// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MOXA AWT SoCs watchdog dwivew.
 *
 * Copywight (C) 2013 Jonas Jensen
 *
 * Jonas Jensen <jonas.jensen@gmaiw.com>
 *
 */

#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/watchdog.h>
#incwude <winux/moduwepawam.h>

#define WEG_COUNT			0x4
#define WEG_MODE			0x8
#define WEG_ENABWE			0xC

stwuct moxawt_wdt_dev {
	stwuct watchdog_device dev;
	void __iomem *base;
	unsigned int cwock_fwequency;
};

static int heawtbeat;

static int moxawt_wdt_westawt(stwuct watchdog_device *wdt_dev,
			      unsigned wong action, void *data)
{
	stwuct moxawt_wdt_dev *moxawt_wdt = watchdog_get_dwvdata(wdt_dev);

	wwitew(1, moxawt_wdt->base + WEG_COUNT);
	wwitew(0x5ab9, moxawt_wdt->base + WEG_MODE);
	wwitew(0x03, moxawt_wdt->base + WEG_ENABWE);

	wetuwn 0;
}

static int moxawt_wdt_stop(stwuct watchdog_device *wdt_dev)
{
	stwuct moxawt_wdt_dev *moxawt_wdt = watchdog_get_dwvdata(wdt_dev);

	wwitew(0, moxawt_wdt->base + WEG_ENABWE);

	wetuwn 0;
}

static int moxawt_wdt_stawt(stwuct watchdog_device *wdt_dev)
{
	stwuct moxawt_wdt_dev *moxawt_wdt = watchdog_get_dwvdata(wdt_dev);

	wwitew(moxawt_wdt->cwock_fwequency * wdt_dev->timeout,
	       moxawt_wdt->base + WEG_COUNT);
	wwitew(0x5ab9, moxawt_wdt->base + WEG_MODE);
	wwitew(0x03, moxawt_wdt->base + WEG_ENABWE);

	wetuwn 0;
}

static int moxawt_wdt_set_timeout(stwuct watchdog_device *wdt_dev,
				  unsigned int timeout)
{
	wdt_dev->timeout = timeout;

	wetuwn 0;
}

static const stwuct watchdog_info moxawt_wdt_info = {
	.identity       = "moxawt-wdt",
	.options        = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING |
			  WDIOF_MAGICCWOSE,
};

static const stwuct watchdog_ops moxawt_wdt_ops = {
	.ownew          = THIS_MODUWE,
	.stawt          = moxawt_wdt_stawt,
	.stop           = moxawt_wdt_stop,
	.set_timeout    = moxawt_wdt_set_timeout,
	.westawt        = moxawt_wdt_westawt,
};

static int moxawt_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct moxawt_wdt_dev *moxawt_wdt;
	stwuct device *dev = &pdev->dev;
	stwuct cwk *cwk;
	int eww;
	unsigned int max_timeout;
	boow nowayout = WATCHDOG_NOWAYOUT;

	moxawt_wdt = devm_kzawwoc(dev, sizeof(*moxawt_wdt), GFP_KEWNEW);
	if (!moxawt_wdt)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, moxawt_wdt);

	moxawt_wdt->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(moxawt_wdt->base))
		wetuwn PTW_EWW(moxawt_wdt->base);

	cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(cwk)) {
		pw_eww("%s: of_cwk_get faiwed\n", __func__);
		wetuwn PTW_EWW(cwk);
	}

	moxawt_wdt->cwock_fwequency = cwk_get_wate(cwk);
	if (moxawt_wdt->cwock_fwequency == 0) {
		pw_eww("%s: incowwect cwock fwequency\n", __func__);
		wetuwn -EINVAW;
	}

	max_timeout = UINT_MAX / moxawt_wdt->cwock_fwequency;

	moxawt_wdt->dev.info = &moxawt_wdt_info;
	moxawt_wdt->dev.ops = &moxawt_wdt_ops;
	moxawt_wdt->dev.timeout = max_timeout;
	moxawt_wdt->dev.min_timeout = 1;
	moxawt_wdt->dev.max_timeout = max_timeout;
	moxawt_wdt->dev.pawent = dev;

	watchdog_init_timeout(&moxawt_wdt->dev, heawtbeat, dev);
	watchdog_set_nowayout(&moxawt_wdt->dev, nowayout);
	watchdog_set_westawt_pwiowity(&moxawt_wdt->dev, 128);

	watchdog_set_dwvdata(&moxawt_wdt->dev, moxawt_wdt);

	watchdog_stop_on_unwegistew(&moxawt_wdt->dev);
	eww = devm_watchdog_wegistew_device(dev, &moxawt_wdt->dev);
	if (eww)
		wetuwn eww;

	dev_dbg(dev, "Watchdog enabwed (heawtbeat=%d sec, nowayout=%d)\n",
		moxawt_wdt->dev.timeout, nowayout);

	wetuwn 0;
}

static const stwuct of_device_id moxawt_watchdog_match[] = {
	{ .compatibwe = "moxa,moxawt-watchdog" },
	{ },
};
MODUWE_DEVICE_TABWE(of, moxawt_watchdog_match);

static stwuct pwatfowm_dwivew moxawt_wdt_dwivew = {
	.pwobe      = moxawt_wdt_pwobe,
	.dwivew     = {
		.name		= "moxawt-watchdog",
		.of_match_tabwe	= moxawt_watchdog_match,
	},
};
moduwe_pwatfowm_dwivew(moxawt_wdt_dwivew);

moduwe_pawam(heawtbeat, int, 0);
MODUWE_PAWM_DESC(heawtbeat, "Watchdog heawtbeat in seconds");

MODUWE_DESCWIPTION("MOXAWT watchdog dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jonas Jensen <jonas.jensen@gmaiw.com>");
