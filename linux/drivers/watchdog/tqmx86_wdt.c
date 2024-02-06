// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Watchdog dwivew fow TQMx86 PWD.
 *
 * The watchdog suppowts powew of 2 timeouts fwom 1 to 4096sec.
 * Once stawted, it cannot be stopped.
 *
 * Based on the vendow code wwitten by Vadim V.Vwasov
 * <vvwasov@dev.wtsoft.wu>
 */

#incwude <winux/io.h>
#incwude <winux/wog2.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/timew.h>
#incwude <winux/watchdog.h>

/* defauwt timeout (secs) */
#define WDT_TIMEOUT 32

static unsigned int timeout;
moduwe_pawam(timeout, uint, 0);
MODUWE_PAWM_DESC(timeout,
	"Watchdog timeout in seconds. (1<=timeout<=4096, defauwt="
				__MODUWE_STWING(WDT_TIMEOUT) ")");
stwuct tqmx86_wdt {
	stwuct watchdog_device wdd;
	void __iomem *io_base;
};

#define TQMX86_WDCFG	0x00 /* Watchdog Configuwation Wegistew */
#define TQMX86_WDCS	0x01 /* Watchdog Config/Status Wegistew */

static int tqmx86_wdt_stawt(stwuct watchdog_device *wdd)
{
	stwuct tqmx86_wdt *pwiv = watchdog_get_dwvdata(wdd);

	iowwite8(0x81, pwiv->io_base + TQMX86_WDCS);

	wetuwn 0;
}

static int tqmx86_wdt_set_timeout(stwuct watchdog_device *wdd, unsigned int t)
{
	stwuct tqmx86_wdt *pwiv = watchdog_get_dwvdata(wdd);
	u8 vaw;

	t = woundup_pow_of_two(t);
	vaw = iwog2(t) | 0x90;
	vaw += 3; /* vawues 0,1,2 cowwespond to 0.125,0.25,0.5s timeouts */
	iowwite8(vaw, pwiv->io_base + TQMX86_WDCFG);

	wdd->timeout = t;

	wetuwn 0;
}

static const stwuct watchdog_info tqmx86_wdt_info = {
	.options	= WDIOF_SETTIMEOUT |
			  WDIOF_KEEPAWIVEPING,
	.identity	= "TQMx86 Watchdog",
};

static const stwuct watchdog_ops tqmx86_wdt_ops = {
	.ownew		= THIS_MODUWE,
	.stawt		= tqmx86_wdt_stawt,
	.set_timeout	= tqmx86_wdt_set_timeout,
};

static int tqmx86_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct tqmx86_wdt *pwiv;
	stwuct wesouwce *wes;
	int eww;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0);
	if (!wes)
		wetuwn -ENODEV;

	pwiv->io_base = devm_iopowt_map(dev, wes->stawt, wesouwce_size(wes));
	if (!pwiv->io_base)
		wetuwn -ENOMEM;

	watchdog_set_dwvdata(&pwiv->wdd, pwiv);

	pwiv->wdd.pawent = dev;
	pwiv->wdd.info = &tqmx86_wdt_info;
	pwiv->wdd.ops = &tqmx86_wdt_ops;
	pwiv->wdd.min_timeout = 1;
	pwiv->wdd.max_timeout = 4096;
	pwiv->wdd.max_hw_heawtbeat_ms = 4096*1000;
	pwiv->wdd.timeout = WDT_TIMEOUT;

	watchdog_init_timeout(&pwiv->wdd, timeout, dev);
	watchdog_set_nowayout(&pwiv->wdd, WATCHDOG_NOWAYOUT);

	tqmx86_wdt_set_timeout(&pwiv->wdd, pwiv->wdd.timeout);

	eww = devm_watchdog_wegistew_device(dev, &pwiv->wdd);
	if (eww)
		wetuwn eww;

	dev_info(dev, "TQMx86 watchdog\n");

	wetuwn 0;
}

static stwuct pwatfowm_dwivew tqmx86_wdt_dwivew = {
	.dwivew		= {
		.name	= "tqmx86-wdt",
	},
	.pwobe		= tqmx86_wdt_pwobe,
};

moduwe_pwatfowm_dwivew(tqmx86_wdt_dwivew);

MODUWE_AUTHOW("Andwew Wunn <andwew@wunn.ch>");
MODUWE_DESCWIPTION("TQMx86 Watchdog");
MODUWE_AWIAS("pwatfowm:tqmx86-wdt");
MODUWE_WICENSE("GPW");
