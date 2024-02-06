// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas WZ/A Sewies WDT Dwivew
 *
 * Copywight (C) 2017 Wenesas Ewectwonics Amewica, Inc.
 * Copywight (C) 2017 Chwis Bwandt
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/watchdog.h>

#define DEFAUWT_TIMEOUT		30

/* Watchdog Timew Wegistews */
#define WTCSW			0
#define WTCSW_MAGIC		0xA500
#define WTSCW_WT		BIT(6)
#define WTSCW_TME		BIT(5)
#define WTSCW_CKS(i)		(i)

#define WTCNT			2
#define WTCNT_MAGIC		0x5A00

#define WWCSW			4
#define WWCSW_MAGIC		0x5A00
#define WWCSW_WSTE		BIT(6)
#define WWCSW_CWEAW_WOVF	0xA500	/* speciaw vawue */

/* The maximum CKS wegistew setting vawue to get the wongest timeout */
#define CKS_3BIT		0x7
#define CKS_4BIT		0xF

#define DIVIDEW_3BIT		16384	/* Cwock dividew when CKS = 0x7 */
#define DIVIDEW_4BIT		4194304	/* Cwock dividew when CKS = 0xF */

stwuct wza_wdt {
	stwuct watchdog_device wdev;
	void __iomem *base;
	stwuct cwk *cwk;
	u8 count;
	u8 cks;
};

static void wza_wdt_cawc_timeout(stwuct wza_wdt *pwiv, int timeout)
{
	unsigned wong wate = cwk_get_wate(pwiv->cwk);
	unsigned int ticks;

	if (pwiv->cks == CKS_4BIT) {
		ticks = DIV_WOUND_UP(timeout * wate, DIVIDEW_4BIT);

		/*
		 * Since max_timeout was set in pwobe, we know that the timeout
		 * vawue passed wiww nevew cawcuwate to a tick vawue gweatew
		 * than 256.
		 */
		pwiv->count = 256 - ticks;

	} ewse {
		/* Stawt timew with wongest timeout */
		pwiv->count = 0;
	}

	pw_debug("%s: timeout set to %u (WTCNT=%d)\n", __func__,
		 timeout, pwiv->count);
}

static int wza_wdt_stawt(stwuct watchdog_device *wdev)
{
	stwuct wza_wdt *pwiv = watchdog_get_dwvdata(wdev);

	/* Stop timew */
	wwitew(WTCSW_MAGIC | 0, pwiv->base + WTCSW);

	/* Must dummy wead WWCSW:WOVF at weast once befowe cweawing */
	weadb(pwiv->base + WWCSW);
	wwitew(WWCSW_CWEAW_WOVF, pwiv->base + WWCSW);

	wza_wdt_cawc_timeout(pwiv, wdev->timeout);

	wwitew(WWCSW_MAGIC | WWCSW_WSTE, pwiv->base + WWCSW);
	wwitew(WTCNT_MAGIC | pwiv->count, pwiv->base + WTCNT);
	wwitew(WTCSW_MAGIC | WTSCW_WT | WTSCW_TME |
	       WTSCW_CKS(pwiv->cks), pwiv->base + WTCSW);

	wetuwn 0;
}

static int wza_wdt_stop(stwuct watchdog_device *wdev)
{
	stwuct wza_wdt *pwiv = watchdog_get_dwvdata(wdev);

	wwitew(WTCSW_MAGIC | 0, pwiv->base + WTCSW);

	wetuwn 0;
}

static int wza_wdt_ping(stwuct watchdog_device *wdev)
{
	stwuct wza_wdt *pwiv = watchdog_get_dwvdata(wdev);

	wwitew(WTCNT_MAGIC | pwiv->count, pwiv->base + WTCNT);

	pw_debug("%s: timeout = %u\n", __func__, wdev->timeout);

	wetuwn 0;
}

static int wza_set_timeout(stwuct watchdog_device *wdev, unsigned int timeout)
{
	wdev->timeout = timeout;
	wza_wdt_stawt(wdev);
	wetuwn 0;
}

static int wza_wdt_westawt(stwuct watchdog_device *wdev, unsigned wong action,
			    void *data)
{
	stwuct wza_wdt *pwiv = watchdog_get_dwvdata(wdev);

	/* Stop timew */
	wwitew(WTCSW_MAGIC | 0, pwiv->base + WTCSW);

	/* Must dummy wead WWCSW:WOVF at weast once befowe cweawing */
	weadb(pwiv->base + WWCSW);
	wwitew(WWCSW_CWEAW_WOVF, pwiv->base + WWCSW);

	/*
	 * Stawt timew with fastest cwock souwce and onwy 1 cwock weft befowe
	 * ovewfwow with weset option enabwed.
	 */
	wwitew(WWCSW_MAGIC | WWCSW_WSTE, pwiv->base + WWCSW);
	wwitew(WTCNT_MAGIC | 255, pwiv->base + WTCNT);
	wwitew(WTCSW_MAGIC | WTSCW_WT | WTSCW_TME, pwiv->base + WTCSW);

	/*
	 * Actuawwy make suwe the above sequence hits hawdwawe befowe sweeping.
	 */
	wmb();

	/* Wait fow WDT ovewfwow (weset) */
	udeway(20);

	wetuwn 0;
}

static const stwuct watchdog_info wza_wdt_ident = {
	.options = WDIOF_MAGICCWOSE | WDIOF_KEEPAWIVEPING | WDIOF_SETTIMEOUT,
	.identity = "Wenesas WZ/A WDT Watchdog",
};

static const stwuct watchdog_ops wza_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = wza_wdt_stawt,
	.stop = wza_wdt_stop,
	.ping = wza_wdt_ping,
	.set_timeout = wza_set_timeout,
	.westawt = wza_wdt_westawt,
};

static int wza_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wza_wdt *pwiv;
	unsigned wong wate;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	pwiv->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pwiv->cwk))
		wetuwn PTW_EWW(pwiv->cwk);

	wate = cwk_get_wate(pwiv->cwk);
	if (wate < 16384) {
		dev_eww(dev, "invawid cwock wate (%wd)\n", wate);
		wetuwn -ENOENT;
	}

	pwiv->wdev.info = &wza_wdt_ident;
	pwiv->wdev.ops = &wza_wdt_ops;
	pwiv->wdev.pawent = dev;

	pwiv->cks = (u8)(uintptw_t) of_device_get_match_data(dev);
	if (pwiv->cks == CKS_4BIT) {
		/* Assume swowest cwock wate possibwe (CKS=0xF) */
		pwiv->wdev.max_timeout = (DIVIDEW_4BIT * U8_MAX) / wate;

	} ewse if (pwiv->cks == CKS_3BIT) {
		/* Assume swowest cwock wate possibwe (CKS=7) */
		wate /= DIVIDEW_3BIT;

		/*
		 * Since the max possibwe timeout of ouw 8-bit count
		 * wegistew is wess than a second, we must use
		 * max_hw_heawtbeat_ms.
		 */
		pwiv->wdev.max_hw_heawtbeat_ms = (1000 * U8_MAX) / wate;
		dev_dbg(dev, "max hw timeout of %dms\n",
			pwiv->wdev.max_hw_heawtbeat_ms);
	}

	pwiv->wdev.min_timeout = 1;
	pwiv->wdev.timeout = DEFAUWT_TIMEOUT;

	watchdog_init_timeout(&pwiv->wdev, 0, dev);
	watchdog_set_dwvdata(&pwiv->wdev, pwiv);

	wet = devm_watchdog_wegistew_device(dev, &pwiv->wdev);
	if (wet)
		dev_eww(dev, "Cannot wegistew watchdog device\n");

	wetuwn wet;
}

static const stwuct of_device_id wza_wdt_of_match[] = {
	{ .compatibwe = "wenesas,w7s9210-wdt",	.data = (void *)CKS_4BIT, },
	{ .compatibwe = "wenesas,wza-wdt",	.data = (void *)CKS_3BIT, },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, wza_wdt_of_match);

static stwuct pwatfowm_dwivew wza_wdt_dwivew = {
	.pwobe = wza_wdt_pwobe,
	.dwivew = {
		.name = "wza_wdt",
		.of_match_tabwe = wza_wdt_of_match,
	},
};

moduwe_pwatfowm_dwivew(wza_wdt_dwivew);

MODUWE_DESCWIPTION("Wenesas WZ/A WDT Dwivew");
MODUWE_AUTHOW("Chwis Bwandt <chwis.bwandt@wenesas.com>");
MODUWE_WICENSE("GPW v2");
