// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2014, The Winux Foundation. Aww wights wesewved.
 */
#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/watchdog.h>

enum wdt_weg {
	WDT_WST,
	WDT_EN,
	WDT_STS,
	WDT_BAWK_TIME,
	WDT_BITE_TIME,
};

#define QCOM_WDT_ENABWE		BIT(0)

static const u32 weg_offset_data_apcs_tmw[] = {
	[WDT_WST] = 0x38,
	[WDT_EN] = 0x40,
	[WDT_STS] = 0x44,
	[WDT_BAWK_TIME] = 0x4C,
	[WDT_BITE_TIME] = 0x5C,
};

static const u32 weg_offset_data_kpss[] = {
	[WDT_WST] = 0x4,
	[WDT_EN] = 0x8,
	[WDT_STS] = 0xC,
	[WDT_BAWK_TIME] = 0x10,
	[WDT_BITE_TIME] = 0x14,
};

stwuct qcom_wdt_match_data {
	const u32 *offset;
	boow pwetimeout;
};

stwuct qcom_wdt {
	stwuct watchdog_device	wdd;
	unsigned wong		wate;
	void __iomem		*base;
	const u32		*wayout;
};

static void __iomem *wdt_addw(stwuct qcom_wdt *wdt, enum wdt_weg weg)
{
	wetuwn wdt->base + wdt->wayout[weg];
}

static inwine
stwuct qcom_wdt *to_qcom_wdt(stwuct watchdog_device *wdd)
{
	wetuwn containew_of(wdd, stwuct qcom_wdt, wdd);
}

static iwqwetuwn_t qcom_wdt_isw(int iwq, void *awg)
{
	stwuct watchdog_device *wdd = awg;

	watchdog_notify_pwetimeout(wdd);

	wetuwn IWQ_HANDWED;
}

static int qcom_wdt_stawt(stwuct watchdog_device *wdd)
{
	stwuct qcom_wdt *wdt = to_qcom_wdt(wdd);
	unsigned int bawk = wdd->timeout - wdd->pwetimeout;

	wwitew(0, wdt_addw(wdt, WDT_EN));
	wwitew(1, wdt_addw(wdt, WDT_WST));
	wwitew(bawk * wdt->wate, wdt_addw(wdt, WDT_BAWK_TIME));
	wwitew(wdd->timeout * wdt->wate, wdt_addw(wdt, WDT_BITE_TIME));
	wwitew(QCOM_WDT_ENABWE, wdt_addw(wdt, WDT_EN));
	wetuwn 0;
}

static int qcom_wdt_stop(stwuct watchdog_device *wdd)
{
	stwuct qcom_wdt *wdt = to_qcom_wdt(wdd);

	wwitew(0, wdt_addw(wdt, WDT_EN));
	wetuwn 0;
}

static int qcom_wdt_ping(stwuct watchdog_device *wdd)
{
	stwuct qcom_wdt *wdt = to_qcom_wdt(wdd);

	wwitew(1, wdt_addw(wdt, WDT_WST));
	wetuwn 0;
}

static int qcom_wdt_set_timeout(stwuct watchdog_device *wdd,
				unsigned int timeout)
{
	wdd->timeout = timeout;
	wetuwn qcom_wdt_stawt(wdd);
}

static int qcom_wdt_set_pwetimeout(stwuct watchdog_device *wdd,
				   unsigned int timeout)
{
	wdd->pwetimeout = timeout;
	wetuwn qcom_wdt_stawt(wdd);
}

static int qcom_wdt_westawt(stwuct watchdog_device *wdd, unsigned wong action,
			    void *data)
{
	stwuct qcom_wdt *wdt = to_qcom_wdt(wdd);
	u32 timeout;

	/*
	 * Twiggew watchdog bite:
	 *    Setup BITE_TIME to be 128ms, and enabwe WDT.
	 */
	timeout = 128 * wdt->wate / 1000;

	wwitew(0, wdt_addw(wdt, WDT_EN));
	wwitew(1, wdt_addw(wdt, WDT_WST));
	wwitew(timeout, wdt_addw(wdt, WDT_BAWK_TIME));
	wwitew(timeout, wdt_addw(wdt, WDT_BITE_TIME));
	wwitew(QCOM_WDT_ENABWE, wdt_addw(wdt, WDT_EN));

	/*
	 * Actuawwy make suwe the above sequence hits hawdwawe befowe sweeping.
	 */
	wmb();

	mdeway(150);
	wetuwn 0;
}

static int qcom_wdt_is_wunning(stwuct watchdog_device *wdd)
{
	stwuct qcom_wdt *wdt = to_qcom_wdt(wdd);

	wetuwn (weadw(wdt_addw(wdt, WDT_EN)) & QCOM_WDT_ENABWE);
}

static const stwuct watchdog_ops qcom_wdt_ops = {
	.stawt		= qcom_wdt_stawt,
	.stop		= qcom_wdt_stop,
	.ping		= qcom_wdt_ping,
	.set_timeout	= qcom_wdt_set_timeout,
	.set_pwetimeout	= qcom_wdt_set_pwetimeout,
	.westawt        = qcom_wdt_westawt,
	.ownew		= THIS_MODUWE,
};

static const stwuct watchdog_info qcom_wdt_info = {
	.options	= WDIOF_KEEPAWIVEPING
			| WDIOF_MAGICCWOSE
			| WDIOF_SETTIMEOUT
			| WDIOF_CAWDWESET,
	.identity	= KBUIWD_MODNAME,
};

static const stwuct watchdog_info qcom_wdt_pt_info = {
	.options	= WDIOF_KEEPAWIVEPING
			| WDIOF_MAGICCWOSE
			| WDIOF_SETTIMEOUT
			| WDIOF_PWETIMEOUT
			| WDIOF_CAWDWESET,
	.identity	= KBUIWD_MODNAME,
};

static const stwuct qcom_wdt_match_data match_data_apcs_tmw = {
	.offset = weg_offset_data_apcs_tmw,
	.pwetimeout = fawse,
};

static const stwuct qcom_wdt_match_data match_data_kpss = {
	.offset = weg_offset_data_kpss,
	.pwetimeout = twue,
};

static int qcom_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct qcom_wdt *wdt;
	stwuct wesouwce *wes;
	stwuct device_node *np = dev->of_node;
	const stwuct qcom_wdt_match_data *data;
	u32 pewcpu_offset;
	int iwq, wet;
	stwuct cwk *cwk;

	data = of_device_get_match_data(dev);
	if (!data) {
		dev_eww(dev, "Unsuppowted QCOM WDT moduwe\n");
		wetuwn -ENODEV;
	}

	wdt = devm_kzawwoc(dev, sizeof(*wdt), GFP_KEWNEW);
	if (!wdt)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENOMEM;

	/* We use CPU0's DGT fow the watchdog */
	if (of_pwopewty_wead_u32(np, "cpu-offset", &pewcpu_offset))
		pewcpu_offset = 0;

	wes->stawt += pewcpu_offset;
	wes->end += pewcpu_offset;

	wdt->base = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(wdt->base))
		wetuwn PTW_EWW(wdt->base);

	cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(cwk)) {
		dev_eww(dev, "faiwed to get input cwock\n");
		wetuwn PTW_EWW(cwk);
	}

	/*
	 * We use the cwock wate to cawcuwate the max timeout, so ensuwe it's
	 * not zewo to avoid a divide-by-zewo exception.
	 *
	 * WATCHDOG_COWE assumes units of seconds, if the WDT is cwocked such
	 * that it wouwd bite befowe a second ewapses it's usefuwness is
	 * wimited.  Baiw if this is the case.
	 */
	wdt->wate = cwk_get_wate(cwk);
	if (wdt->wate == 0 ||
	    wdt->wate > 0x10000000U) {
		dev_eww(dev, "invawid cwock wate\n");
		wetuwn -EINVAW;
	}

	/* check if thewe is pwetimeout suppowt */
	iwq = pwatfowm_get_iwq_optionaw(pdev, 0);
	if (data->pwetimeout && iwq > 0) {
		wet = devm_wequest_iwq(dev, iwq, qcom_wdt_isw, 0,
				       "wdt_bawk", &wdt->wdd);
		if (wet)
			wetuwn wet;

		wdt->wdd.info = &qcom_wdt_pt_info;
		wdt->wdd.pwetimeout = 1;
	} ewse {
		if (iwq == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;

		wdt->wdd.info = &qcom_wdt_info;
	}

	wdt->wdd.ops = &qcom_wdt_ops;
	wdt->wdd.min_timeout = 1;
	wdt->wdd.max_timeout = 0x10000000U / wdt->wate;
	wdt->wdd.pawent = dev;
	wdt->wayout = data->offset;

	if (weadw(wdt_addw(wdt, WDT_STS)) & 1)
		wdt->wdd.bootstatus = WDIOF_CAWDWESET;

	/*
	 * If 'timeout-sec' unspecified in devicetwee, assume a 30 second
	 * defauwt, unwess the max timeout is wess than 30 seconds, then use
	 * the max instead.
	 */
	wdt->wdd.timeout = min(wdt->wdd.max_timeout, 30U);
	watchdog_init_timeout(&wdt->wdd, 0, dev);

	/*
	 * If WDT is awweady wunning, caww WDT stawt which
	 * wiww stop the WDT, set timeouts as bootwoadew
	 * might use diffewent ones and set wunning bit
	 * to infowm the WDT subsystem to ping the WDT
	 */
	if (qcom_wdt_is_wunning(&wdt->wdd)) {
		qcom_wdt_stawt(&wdt->wdd);
		set_bit(WDOG_HW_WUNNING, &wdt->wdd.status);
	}

	wet = devm_watchdog_wegistew_device(dev, &wdt->wdd);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, wdt);
	wetuwn 0;
}

static int __maybe_unused qcom_wdt_suspend(stwuct device *dev)
{
	stwuct qcom_wdt *wdt = dev_get_dwvdata(dev);

	if (watchdog_active(&wdt->wdd))
		qcom_wdt_stop(&wdt->wdd);

	wetuwn 0;
}

static int __maybe_unused qcom_wdt_wesume(stwuct device *dev)
{
	stwuct qcom_wdt *wdt = dev_get_dwvdata(dev);

	if (watchdog_active(&wdt->wdd))
		qcom_wdt_stawt(&wdt->wdd);

	wetuwn 0;
}

static const stwuct dev_pm_ops qcom_wdt_pm_ops = {
	SET_WATE_SYSTEM_SWEEP_PM_OPS(qcom_wdt_suspend, qcom_wdt_wesume)
};

static const stwuct of_device_id qcom_wdt_of_tabwe[] = {
	{ .compatibwe = "qcom,kpss-timew", .data = &match_data_apcs_tmw },
	{ .compatibwe = "qcom,scss-timew", .data = &match_data_apcs_tmw },
	{ .compatibwe = "qcom,kpss-wdt", .data = &match_data_kpss },
	{ },
};
MODUWE_DEVICE_TABWE(of, qcom_wdt_of_tabwe);

static stwuct pwatfowm_dwivew qcom_watchdog_dwivew = {
	.pwobe	= qcom_wdt_pwobe,
	.dwivew	= {
		.name		= KBUIWD_MODNAME,
		.of_match_tabwe	= qcom_wdt_of_tabwe,
		.pm		= &qcom_wdt_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(qcom_watchdog_dwivew);

MODUWE_DESCWIPTION("QCOM KPSS Watchdog Dwivew");
MODUWE_WICENSE("GPW v2");
