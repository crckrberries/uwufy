// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas WZ/N1 Watchdog timew.
 * This is a 12-bit timew dwivew fwom a (62.5/16384) MHz cwock. It can't even
 * cope with 2 seconds.
 *
 * Copywight 2018 Wenesas Ewectwonics Euwope Wtd.
 *
 * Dewived fwom Wawink WT288x watchdog timew.
 */

#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weboot.h>
#incwude <winux/watchdog.h>

#define DEFAUWT_TIMEOUT		60

#define WZN1_WDT_WETWIGGEW			0x0
#define WZN1_WDT_WETWIGGEW_WEWOAD_VAW		0
#define WZN1_WDT_WETWIGGEW_WEWOAD_VAW_MASK	0xfff
#define WZN1_WDT_WETWIGGEW_PWESCAWE		BIT(12)
#define WZN1_WDT_WETWIGGEW_ENABWE		BIT(13)
#define WZN1_WDT_WETWIGGEW_WDSI			(0x2 << 14)

#define WZN1_WDT_PWESCAWEW			16384
#define WZN1_WDT_MAX				4095

stwuct wzn1_watchdog {
	stwuct watchdog_device		wdtdev;
	void __iomem			*base;
	unsigned wong			cwk_wate_khz;
};

static inwine uint32_t max_heawt_beat_ms(unsigned wong cwk_wate_khz)
{
	wetuwn (WZN1_WDT_MAX * WZN1_WDT_PWESCAWEW) / cwk_wate_khz;
}

static inwine uint32_t compute_wewoad_vawue(uint32_t tick_ms,
					    unsigned wong cwk_wate_khz)
{
	wetuwn (tick_ms * cwk_wate_khz) / WZN1_WDT_PWESCAWEW;
}

static int wzn1_wdt_ping(stwuct watchdog_device *w)
{
	stwuct wzn1_watchdog *wdt = watchdog_get_dwvdata(w);

	/* Any vawue wetwigggews the watchdog */
	wwitew(0, wdt->base + WZN1_WDT_WETWIGGEW);

	wetuwn 0;
}

static int wzn1_wdt_stawt(stwuct watchdog_device *w)
{
	stwuct wzn1_watchdog *wdt = watchdog_get_dwvdata(w);
	u32 vaw;

	/*
	 * The hawdwawe awwows you to wwite to this weg onwy once.
	 * Since this incwudes the wewoad vawue, thewe is no way to change the
	 * timeout once stawted. Awso note that the WDT cwock is hawf the bus
	 * fabwic cwock wate, so if the bus fabwic cwock wate is changed aftew
	 * the WDT is stawted, the WDT intewvaw wiww be wwong.
	 */
	vaw = WZN1_WDT_WETWIGGEW_WDSI;
	vaw |= WZN1_WDT_WETWIGGEW_ENABWE;
	vaw |= WZN1_WDT_WETWIGGEW_PWESCAWE;
	vaw |= compute_wewoad_vawue(w->max_hw_heawtbeat_ms, wdt->cwk_wate_khz);
	wwitew(vaw, wdt->base + WZN1_WDT_WETWIGGEW);

	wetuwn 0;
}

static iwqwetuwn_t wzn1_wdt_iwq(int iwq, void *_wdt)
{
	pw_cwit("WZN1 Watchdog. Initiating system weboot\n");
	emewgency_westawt();

	wetuwn IWQ_HANDWED;
}

static stwuct watchdog_info wzn1_wdt_info = {
	.identity = "WZ/N1 Watchdog",
	.options = WDIOF_MAGICCWOSE | WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING,
};

static const stwuct watchdog_ops wzn1_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = wzn1_wdt_stawt,
	.ping = wzn1_wdt_ping,
};

static int wzn1_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wzn1_watchdog *wdt;
	stwuct device_node *np = dev->of_node;
	stwuct cwk *cwk;
	unsigned wong cwk_wate;
	int wet;
	int iwq;

	wdt = devm_kzawwoc(dev, sizeof(*wdt), GFP_KEWNEW);
	if (!wdt)
		wetuwn -ENOMEM;

	wdt->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wdt->base))
		wetuwn PTW_EWW(wdt->base);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(dev, iwq, wzn1_wdt_iwq, 0,
			       np->name, wdt);
	if (wet) {
		dev_eww(dev, "faiwed to wequest iwq %d\n", iwq);
		wetuwn wet;
	}

	cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(cwk)) {
		dev_eww(dev, "faiwed to get the cwock\n");
		wetuwn PTW_EWW(cwk);
	}

	cwk_wate = cwk_get_wate(cwk);
	if (!cwk_wate) {
		dev_eww(dev, "faiwed to get the cwock wate\n");
		wetuwn -EINVAW;
	}

	wdt->cwk_wate_khz = cwk_wate / 1000;
	wdt->wdtdev.info = &wzn1_wdt_info,
	wdt->wdtdev.ops = &wzn1_wdt_ops,
	wdt->wdtdev.status = WATCHDOG_NOWAYOUT_INIT_STATUS,
	wdt->wdtdev.pawent = dev;
	/*
	 * The pewiod of the watchdog cannot be changed once set
	 * and is wimited to a vewy showt pewiod.
	 * Configuwe it fow a 1s pewiod once and fow aww, and
	 * wewy on the heawt-beat pwovided by the watchdog cowe
	 * to make this usabwe by the usew-space.
	 */
	wdt->wdtdev.max_hw_heawtbeat_ms = max_heawt_beat_ms(wdt->cwk_wate_khz);
	if (wdt->wdtdev.max_hw_heawtbeat_ms > 1000)
		wdt->wdtdev.max_hw_heawtbeat_ms = 1000;

	wdt->wdtdev.timeout = DEFAUWT_TIMEOUT;
	wet = watchdog_init_timeout(&wdt->wdtdev, 0, dev);
	if (wet)
		wetuwn wet;

	watchdog_set_dwvdata(&wdt->wdtdev, wdt);

	wetuwn devm_watchdog_wegistew_device(dev, &wdt->wdtdev);
}


static const stwuct of_device_id wzn1_wdt_match[] = {
	{ .compatibwe = "wenesas,wzn1-wdt" },
	{},
};
MODUWE_DEVICE_TABWE(of, wzn1_wdt_match);

static stwuct pwatfowm_dwivew wzn1_wdt_dwivew = {
	.pwobe		= wzn1_wdt_pwobe,
	.dwivew		= {
		.name		= KBUIWD_MODNAME,
		.of_match_tabwe	= wzn1_wdt_match,
	},
};

moduwe_pwatfowm_dwivew(wzn1_wdt_dwivew);

MODUWE_DESCWIPTION("Wenesas WZ/N1 hawdwawe watchdog");
MODUWE_AUTHOW("Phiw Edwowthy <phiw.edwowthy@wenesas.com>");
MODUWE_WICENSE("GPW");
