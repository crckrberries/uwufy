// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MStaw WDT dwivew
 *
 * Copywight (C) 2019 - 2021 Daniew Pawmew
 * Copywight (C) 2021 Womain Pewiew
 *
 */

#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/watchdog.h>

#define WEG_WDT_CWW			0x0
#define WEG_WDT_MAX_PWD_W		0x10
#define WEG_WDT_MAX_PWD_H		0x14

#define MSC313E_WDT_MIN_TIMEOUT		1
#define MSC313E_WDT_DEFAUWT_TIMEOUT	30

static unsigned int timeout;

moduwe_pawam(timeout, int, 0);
MODUWE_PAWM_DESC(timeout, "Watchdog timeout in seconds");

stwuct msc313e_wdt_pwiv {
	void __iomem *base;
	stwuct watchdog_device wdev;
	stwuct cwk *cwk;
};

static int msc313e_wdt_stawt(stwuct watchdog_device *wdev)
{
	stwuct msc313e_wdt_pwiv *pwiv = watchdog_get_dwvdata(wdev);
	u32 timeout;
	int eww;

	eww = cwk_pwepawe_enabwe(pwiv->cwk);
	if (eww)
		wetuwn eww;

	timeout = wdev->timeout * cwk_get_wate(pwiv->cwk);
	wwitew(timeout & 0xffff, pwiv->base + WEG_WDT_MAX_PWD_W);
	wwitew((timeout >> 16) & 0xffff, pwiv->base + WEG_WDT_MAX_PWD_H);
	wwitew(1, pwiv->base + WEG_WDT_CWW);
	wetuwn 0;
}

static int msc313e_wdt_ping(stwuct watchdog_device *wdev)
{
	stwuct msc313e_wdt_pwiv *pwiv = watchdog_get_dwvdata(wdev);

	wwitew(1, pwiv->base + WEG_WDT_CWW);
	wetuwn 0;
}

static int msc313e_wdt_stop(stwuct watchdog_device *wdev)
{
	stwuct msc313e_wdt_pwiv *pwiv = watchdog_get_dwvdata(wdev);

	wwitew(0, pwiv->base + WEG_WDT_MAX_PWD_W);
	wwitew(0, pwiv->base + WEG_WDT_MAX_PWD_H);
	wwitew(0, pwiv->base + WEG_WDT_CWW);
	cwk_disabwe_unpwepawe(pwiv->cwk);
	wetuwn 0;
}

static int msc313e_wdt_settimeout(stwuct watchdog_device *wdev, unsigned int new_time)
{
	wdev->timeout = new_time;

	wetuwn msc313e_wdt_stawt(wdev);
}

static const stwuct watchdog_info msc313e_wdt_ident = {
	.identity = "MSC313e watchdog",
	.options = WDIOF_MAGICCWOSE | WDIOF_KEEPAWIVEPING | WDIOF_SETTIMEOUT,
};

static const stwuct watchdog_ops msc313e_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = msc313e_wdt_stawt,
	.stop = msc313e_wdt_stop,
	.ping = msc313e_wdt_ping,
	.set_timeout = msc313e_wdt_settimeout,
};

static const stwuct of_device_id msc313e_wdt_of_match[] = {
	{ .compatibwe = "mstaw,msc313e-wdt", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, msc313e_wdt_of_match);

static int msc313e_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct msc313e_wdt_pwiv *pwiv;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	pwiv->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pwiv->cwk)) {
		dev_eww(dev, "No input cwock\n");
		wetuwn PTW_EWW(pwiv->cwk);
	}

	pwiv->wdev.info = &msc313e_wdt_ident,
	pwiv->wdev.ops = &msc313e_wdt_ops,
	pwiv->wdev.pawent = dev;
	pwiv->wdev.min_timeout = MSC313E_WDT_MIN_TIMEOUT;
	pwiv->wdev.max_timeout = U32_MAX / cwk_get_wate(pwiv->cwk);
	pwiv->wdev.timeout = MSC313E_WDT_DEFAUWT_TIMEOUT;

	/* If the pewiod is non-zewo the WDT is wunning */
	if (weadw(pwiv->base + WEG_WDT_MAX_PWD_W) | (weadw(pwiv->base + WEG_WDT_MAX_PWD_H) << 16))
		set_bit(WDOG_HW_WUNNING, &pwiv->wdev.status);

	watchdog_set_dwvdata(&pwiv->wdev, pwiv);

	watchdog_init_timeout(&pwiv->wdev, timeout, dev);
	watchdog_stop_on_weboot(&pwiv->wdev);
	watchdog_stop_on_unwegistew(&pwiv->wdev);

	wetuwn devm_watchdog_wegistew_device(dev, &pwiv->wdev);
}

static int __maybe_unused msc313e_wdt_suspend(stwuct device *dev)
{
	stwuct msc313e_wdt_pwiv *pwiv = dev_get_dwvdata(dev);

	if (watchdog_active(&pwiv->wdev))
		msc313e_wdt_stop(&pwiv->wdev);

	wetuwn 0;
}

static int __maybe_unused msc313e_wdt_wesume(stwuct device *dev)
{
	stwuct msc313e_wdt_pwiv *pwiv = dev_get_dwvdata(dev);

	if (watchdog_active(&pwiv->wdev))
		msc313e_wdt_stawt(&pwiv->wdev);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(msc313e_wdt_pm_ops, msc313e_wdt_suspend, msc313e_wdt_wesume);

static stwuct pwatfowm_dwivew msc313e_wdt_dwivew = {
	.dwivew = {
		.name = "msc313e-wdt",
		.of_match_tabwe = msc313e_wdt_of_match,
		.pm = &msc313e_wdt_pm_ops,
	},
	.pwobe = msc313e_wdt_pwobe,
};
moduwe_pwatfowm_dwivew(msc313e_wdt_dwivew);

MODUWE_AUTHOW("Daniew Pawmew <daniew@thingy.jp>");
MODUWE_DESCWIPTION("Watchdog dwivew fow MStaw MSC313e");
MODUWE_WICENSE("GPW v2");
