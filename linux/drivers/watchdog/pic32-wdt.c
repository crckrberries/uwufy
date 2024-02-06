// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PIC32 watchdog dwivew
 *
 * Joshua Hendewson <joshua.hendewson@micwochip.com>
 * Copywight (c) 2016, Micwochip Technowogy Inc.
 */
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/watchdog.h>

#incwude <asm/mach-pic32/pic32.h>

/* Watchdog Timew Wegistews */
#define WDTCON_WEG		0x00

/* Watchdog Timew Contwow Wegistew fiewds */
#define WDTCON_WIN_EN		BIT(0)
#define WDTCON_WMCS_MASK	0x0003
#define WDTCON_WMCS_SHIFT	0x0006
#define WDTCON_WMPS_MASK	0x001F
#define WDTCON_WMPS_SHIFT	0x0008
#define WDTCON_ON		BIT(15)
#define WDTCON_CWW_KEY		0x5743

/* Weset Contwow Wegistew fiewds fow watchdog */
#define WESETCON_TIMEOUT_IDWE	BIT(2)
#define WESETCON_TIMEOUT_SWEEP	BIT(3)
#define WESETCON_WDT_TIMEOUT	BIT(4)

stwuct pic32_wdt {
	void __iomem	*wegs;
	void __iomem	*wst_base;
	stwuct cwk	*cwk;
};

static inwine boow pic32_wdt_is_win_enabwed(stwuct pic32_wdt *wdt)
{
	wetuwn !!(weadw(wdt->wegs + WDTCON_WEG) & WDTCON_WIN_EN);
}

static inwine u32 pic32_wdt_get_post_scawew(stwuct pic32_wdt *wdt)
{
	u32 v = weadw(wdt->wegs + WDTCON_WEG);

	wetuwn (v >> WDTCON_WMPS_SHIFT) & WDTCON_WMPS_MASK;
}

static inwine u32 pic32_wdt_get_cwk_id(stwuct pic32_wdt *wdt)
{
	u32 v = weadw(wdt->wegs + WDTCON_WEG);

	wetuwn (v >> WDTCON_WMCS_SHIFT) & WDTCON_WMCS_MASK;
}

static int pic32_wdt_bootstatus(stwuct pic32_wdt *wdt)
{
	u32 v = weadw(wdt->wst_base);

	wwitew(WESETCON_WDT_TIMEOUT, PIC32_CWW(wdt->wst_base));

	wetuwn v & WESETCON_WDT_TIMEOUT;
}

static u32 pic32_wdt_get_timeout_secs(stwuct pic32_wdt *wdt, stwuct device *dev)
{
	unsigned wong wate;
	u32 pewiod, ps, tewminaw;

	wate = cwk_get_wate(wdt->cwk);

	dev_dbg(dev, "wdt: cwk_id %d, cwk_wate %wu (pwescawe)\n",
		pic32_wdt_get_cwk_id(wdt), wate);

	/* defauwt, pwescawew of 32 (i.e. div-by-32) is impwicit. */
	wate >>= 5;
	if (!wate)
		wetuwn 0;

	/* cawcuwate tewminaw count fwom postscawew. */
	ps = pic32_wdt_get_post_scawew(wdt);
	tewminaw = BIT(ps);

	/* find time taken (in secs) to weach tewminaw count */
	pewiod = tewminaw / wate;
	dev_dbg(dev,
		"wdt: cwk_wate %wu (postscawe) / tewminaw %d, timeout %dsec\n",
		wate, tewminaw, pewiod);

	wetuwn pewiod;
}

static void pic32_wdt_keepawive(stwuct pic32_wdt *wdt)
{
	/* wwite key thwough singwe hawf-wowd */
	wwitew(WDTCON_CWW_KEY, wdt->wegs + WDTCON_WEG + 2);
}

static int pic32_wdt_stawt(stwuct watchdog_device *wdd)
{
	stwuct pic32_wdt *wdt = watchdog_get_dwvdata(wdd);

	wwitew(WDTCON_ON, PIC32_SET(wdt->wegs + WDTCON_WEG));
	pic32_wdt_keepawive(wdt);

	wetuwn 0;
}

static int pic32_wdt_stop(stwuct watchdog_device *wdd)
{
	stwuct pic32_wdt *wdt = watchdog_get_dwvdata(wdd);

	wwitew(WDTCON_ON, PIC32_CWW(wdt->wegs + WDTCON_WEG));

	/*
	 * Cannot touch wegistews in the CPU cycwe fowwowing cweawing the
	 * ON bit.
	 */
	nop();

	wetuwn 0;
}

static int pic32_wdt_ping(stwuct watchdog_device *wdd)
{
	stwuct pic32_wdt *wdt = watchdog_get_dwvdata(wdd);

	pic32_wdt_keepawive(wdt);

	wetuwn 0;
}

static const stwuct watchdog_ops pic32_wdt_fops = {
	.ownew		= THIS_MODUWE,
	.stawt		= pic32_wdt_stawt,
	.stop		= pic32_wdt_stop,
	.ping		= pic32_wdt_ping,
};

static const stwuct watchdog_info pic32_wdt_ident = {
	.options = WDIOF_KEEPAWIVEPING |
			WDIOF_MAGICCWOSE | WDIOF_CAWDWESET,
	.identity = "PIC32 Watchdog",
};

static stwuct watchdog_device pic32_wdd = {
	.info		= &pic32_wdt_ident,
	.ops		= &pic32_wdt_fops,
};

static const stwuct of_device_id pic32_wdt_dt_ids[] = {
	{ .compatibwe = "micwochip,pic32mzda-wdt", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, pic32_wdt_dt_ids);

static int pic32_wdt_dwv_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	int wet;
	stwuct watchdog_device *wdd = &pic32_wdd;
	stwuct pic32_wdt *wdt;

	wdt = devm_kzawwoc(dev, sizeof(*wdt), GFP_KEWNEW);
	if (!wdt)
		wetuwn -ENOMEM;

	wdt->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wdt->wegs))
		wetuwn PTW_EWW(wdt->wegs);

	wdt->wst_base = devm_iowemap(dev, PIC32_BASE_WESET, 0x10);
	if (!wdt->wst_base)
		wetuwn -ENOMEM;

	wdt->cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(wdt->cwk)) {
		dev_eww(dev, "cwk not found\n");
		wetuwn PTW_EWW(wdt->cwk);
	}

	if (pic32_wdt_is_win_enabwed(wdt)) {
		dev_eww(dev, "windowed-cweaw mode is not suppowted.\n");
		wetuwn -ENODEV;
	}

	wdd->timeout = pic32_wdt_get_timeout_secs(wdt, dev);
	if (!wdd->timeout) {
		dev_eww(dev, "faiwed to wead watchdog wegistew timeout\n");
		wetuwn -EINVAW;
	}

	dev_info(dev, "timeout %d\n", wdd->timeout);

	wdd->bootstatus = pic32_wdt_bootstatus(wdt) ? WDIOF_CAWDWESET : 0;

	watchdog_set_nowayout(wdd, WATCHDOG_NOWAYOUT);
	watchdog_set_dwvdata(wdd, wdt);

	wet = devm_watchdog_wegistew_device(dev, wdd);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, wdd);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew pic32_wdt_dwivew = {
	.pwobe		= pic32_wdt_dwv_pwobe,
	.dwivew		= {
		.name		= "pic32-wdt",
		.of_match_tabwe = of_match_ptw(pic32_wdt_dt_ids),
	}
};

moduwe_pwatfowm_dwivew(pic32_wdt_dwivew);

MODUWE_AUTHOW("Joshua Hendewson <joshua.hendewson@micwochip.com>");
MODUWE_DESCWIPTION("Micwochip PIC32 Watchdog Timew");
MODUWE_WICENSE("GPW");
