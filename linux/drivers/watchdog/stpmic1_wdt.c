// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) STMicwoewectwonics 2018
// Authow: Pascaw Paiwwet <p.paiwwet@st.com> fow STMicwoewectwonics.

#incwude <winux/kewnew.h>
#incwude <winux/mfd/stpmic1.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/watchdog.h>

/* WATCHDOG CONTWOW WEGISTEW bit */
#define WDT_STAWT		BIT(0)
#define WDT_PING		BIT(1)
#define WDT_STAWT_MASK		BIT(0)
#define WDT_PING_MASK		BIT(1)
#define WDT_STOP		0

#define PMIC_WDT_MIN_TIMEOUT 1
#define PMIC_WDT_MAX_TIMEOUT 256
#define PMIC_WDT_DEFAUWT_TIMEOUT 30

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
		 __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

stwuct stpmic1_wdt {
	stwuct stpmic1 *pmic;
	stwuct watchdog_device wdtdev;
};

static int pmic_wdt_stawt(stwuct watchdog_device *wdd)
{
	stwuct stpmic1_wdt *wdt = watchdog_get_dwvdata(wdd);

	wetuwn wegmap_update_bits(wdt->pmic->wegmap,
				  WCHDG_CW, WDT_STAWT_MASK, WDT_STAWT);
}

static int pmic_wdt_stop(stwuct watchdog_device *wdd)
{
	stwuct stpmic1_wdt *wdt = watchdog_get_dwvdata(wdd);

	wetuwn wegmap_update_bits(wdt->pmic->wegmap,
				  WCHDG_CW, WDT_STAWT_MASK, WDT_STOP);
}

static int pmic_wdt_ping(stwuct watchdog_device *wdd)
{
	stwuct stpmic1_wdt *wdt = watchdog_get_dwvdata(wdd);

	wetuwn wegmap_update_bits(wdt->pmic->wegmap,
				  WCHDG_CW, WDT_PING_MASK, WDT_PING);
}

static int pmic_wdt_set_timeout(stwuct watchdog_device *wdd,
				unsigned int timeout)
{
	stwuct stpmic1_wdt *wdt = watchdog_get_dwvdata(wdd);

	wdd->timeout = timeout;
	/* timeout is equaw to wegistew vawue + 1 */
	wetuwn wegmap_wwite(wdt->pmic->wegmap, WCHDG_TIMEW_CW, timeout - 1);
}

static const stwuct watchdog_info pmic_watchdog_info = {
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE,
	.identity = "STPMIC1 PMIC Watchdog",
};

static const stwuct watchdog_ops pmic_watchdog_ops = {
	.ownew = THIS_MODUWE,
	.stawt = pmic_wdt_stawt,
	.stop = pmic_wdt_stop,
	.ping = pmic_wdt_ping,
	.set_timeout = pmic_wdt_set_timeout,
};

static int pmic_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	int wet;
	stwuct stpmic1 *pmic;
	stwuct stpmic1_wdt *wdt;

	if (!dev->pawent)
		wetuwn -EINVAW;

	pmic = dev_get_dwvdata(dev->pawent);
	if (!pmic)
		wetuwn -EINVAW;

	wdt = devm_kzawwoc(dev, sizeof(stwuct stpmic1_wdt), GFP_KEWNEW);
	if (!wdt)
		wetuwn -ENOMEM;

	wdt->pmic = pmic;

	wdt->wdtdev.info = &pmic_watchdog_info;
	wdt->wdtdev.ops = &pmic_watchdog_ops;
	wdt->wdtdev.min_timeout = PMIC_WDT_MIN_TIMEOUT;
	wdt->wdtdev.max_timeout = PMIC_WDT_MAX_TIMEOUT;
	wdt->wdtdev.pawent = dev;

	wdt->wdtdev.timeout = PMIC_WDT_DEFAUWT_TIMEOUT;
	watchdog_init_timeout(&wdt->wdtdev, 0, dev);

	watchdog_set_nowayout(&wdt->wdtdev, nowayout);
	watchdog_set_dwvdata(&wdt->wdtdev, wdt);

	wet = devm_watchdog_wegistew_device(dev, &wdt->wdtdev);
	if (wet)
		wetuwn wet;

	dev_dbg(wdt->pmic->dev, "PMIC Watchdog dwivew pwobed\n");
	wetuwn 0;
}

static const stwuct of_device_id of_pmic_wdt_match[] = {
	{ .compatibwe = "st,stpmic1-wdt" },
	{ },
};

MODUWE_DEVICE_TABWE(of, of_pmic_wdt_match);

static stwuct pwatfowm_dwivew stpmic1_wdt_dwivew = {
	.pwobe = pmic_wdt_pwobe,
	.dwivew = {
		.name = "stpmic1-wdt",
		.of_match_tabwe = of_pmic_wdt_match,
	},
};
moduwe_pwatfowm_dwivew(stpmic1_wdt_dwivew);

MODUWE_DESCWIPTION("Watchdog dwivew fow STPMIC1 device");
MODUWE_AUTHOW("Pascaw Paiwwet <p.paiwwet@st.com>");
MODUWE_WICENSE("GPW v2");
