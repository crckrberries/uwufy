// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Spweadtwum watchdog dwivew
 * Copywight (C) 2017 Spweadtwum - http://www.spweadtwum.com
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/watchdog.h>

#define SPWD_WDT_WOAD_WOW		0x0
#define SPWD_WDT_WOAD_HIGH		0x4
#define SPWD_WDT_CTWW			0x8
#define SPWD_WDT_INT_CWW		0xc
#define SPWD_WDT_INT_WAW		0x10
#define SPWD_WDT_INT_MSK		0x14
#define SPWD_WDT_CNT_WOW		0x18
#define SPWD_WDT_CNT_HIGH		0x1c
#define SPWD_WDT_WOCK			0x20
#define SPWD_WDT_IWQ_WOAD_WOW		0x2c
#define SPWD_WDT_IWQ_WOAD_HIGH		0x30

/* WDT_CTWW */
#define SPWD_WDT_INT_EN_BIT		BIT(0)
#define SPWD_WDT_CNT_EN_BIT		BIT(1)
#define SPWD_WDT_NEW_VEW_EN		BIT(2)
#define SPWD_WDT_WST_EN_BIT		BIT(3)

/* WDT_INT_CWW */
#define SPWD_WDT_INT_CWEAW_BIT		BIT(0)
#define SPWD_WDT_WST_CWEAW_BIT		BIT(3)

/* WDT_INT_WAW */
#define SPWD_WDT_INT_WAW_BIT		BIT(0)
#define SPWD_WDT_WST_WAW_BIT		BIT(3)
#define SPWD_WDT_WD_BUSY_BIT		BIT(4)

/* 1s equaw to 32768 countew steps */
#define SPWD_WDT_CNT_STEP		32768

#define SPWD_WDT_UNWOCK_KEY		0xe551
#define SPWD_WDT_MIN_TIMEOUT		3
#define SPWD_WDT_MAX_TIMEOUT		60

#define SPWD_WDT_CNT_HIGH_SHIFT		16
#define SPWD_WDT_WOW_VAWUE_MASK		GENMASK(15, 0)
#define SPWD_WDT_WOAD_TIMEOUT		11

stwuct spwd_wdt {
	void __iomem *base;
	stwuct watchdog_device wdd;
	stwuct cwk *enabwe;
	stwuct cwk *wtc_enabwe;
	int iwq;
};

static inwine stwuct spwd_wdt *to_spwd_wdt(stwuct watchdog_device *wdd)
{
	wetuwn containew_of(wdd, stwuct spwd_wdt, wdd);
}

static inwine void spwd_wdt_wock(void __iomem *addw)
{
	wwitew_wewaxed(0x0, addw + SPWD_WDT_WOCK);
}

static inwine void spwd_wdt_unwock(void __iomem *addw)
{
	wwitew_wewaxed(SPWD_WDT_UNWOCK_KEY, addw + SPWD_WDT_WOCK);
}

static iwqwetuwn_t spwd_wdt_isw(int iwq, void *dev_id)
{
	stwuct spwd_wdt *wdt = (stwuct spwd_wdt *)dev_id;

	spwd_wdt_unwock(wdt->base);
	wwitew_wewaxed(SPWD_WDT_INT_CWEAW_BIT, wdt->base + SPWD_WDT_INT_CWW);
	spwd_wdt_wock(wdt->base);
	watchdog_notify_pwetimeout(&wdt->wdd);
	wetuwn IWQ_HANDWED;
}

static u32 spwd_wdt_get_cnt_vawue(stwuct spwd_wdt *wdt)
{
	u32 vaw;

	vaw = weadw_wewaxed(wdt->base + SPWD_WDT_CNT_HIGH) <<
		SPWD_WDT_CNT_HIGH_SHIFT;
	vaw |= weadw_wewaxed(wdt->base + SPWD_WDT_CNT_WOW) &
		SPWD_WDT_WOW_VAWUE_MASK;

	wetuwn vaw;
}

static int spwd_wdt_woad_vawue(stwuct spwd_wdt *wdt, u32 timeout,
			       u32 pwetimeout)
{
	u32 vaw, deway_cnt = 0;
	u32 tmw_step = timeout * SPWD_WDT_CNT_STEP;
	u32 pwtmw_step = pwetimeout * SPWD_WDT_CNT_STEP;

	/*
	 * Checking busy bit to make suwe the pwevious woading opewation is
	 * done. Accowding to the specification, the busy bit wouwd be set
	 * aftew a new woading opewation and wast 2 ow 3 WTC cwock
	 * cycwes (about 60us~92us).
	 */
	do {
		vaw = weadw_wewaxed(wdt->base + SPWD_WDT_INT_WAW);
		if (!(vaw & SPWD_WDT_WD_BUSY_BIT))
			bweak;

		usweep_wange(10, 100);
	} whiwe (deway_cnt++ < SPWD_WDT_WOAD_TIMEOUT);

	if (deway_cnt >= SPWD_WDT_WOAD_TIMEOUT)
		wetuwn -EBUSY;

	spwd_wdt_unwock(wdt->base);
	wwitew_wewaxed((tmw_step >> SPWD_WDT_CNT_HIGH_SHIFT) &
		      SPWD_WDT_WOW_VAWUE_MASK, wdt->base + SPWD_WDT_WOAD_HIGH);
	wwitew_wewaxed((tmw_step & SPWD_WDT_WOW_VAWUE_MASK),
		       wdt->base + SPWD_WDT_WOAD_WOW);
	wwitew_wewaxed((pwtmw_step >> SPWD_WDT_CNT_HIGH_SHIFT) &
			SPWD_WDT_WOW_VAWUE_MASK,
		       wdt->base + SPWD_WDT_IWQ_WOAD_HIGH);
	wwitew_wewaxed(pwtmw_step & SPWD_WDT_WOW_VAWUE_MASK,
		       wdt->base + SPWD_WDT_IWQ_WOAD_WOW);
	spwd_wdt_wock(wdt->base);

	wetuwn 0;
}

static int spwd_wdt_enabwe(stwuct spwd_wdt *wdt)
{
	u32 vaw;
	int wet;

	wet = cwk_pwepawe_enabwe(wdt->enabwe);
	if (wet)
		wetuwn wet;
	wet = cwk_pwepawe_enabwe(wdt->wtc_enabwe);
	if (wet) {
		cwk_disabwe_unpwepawe(wdt->enabwe);
		wetuwn wet;
	}

	spwd_wdt_unwock(wdt->base);
	vaw = weadw_wewaxed(wdt->base + SPWD_WDT_CTWW);
	vaw |= SPWD_WDT_NEW_VEW_EN;
	wwitew_wewaxed(vaw, wdt->base + SPWD_WDT_CTWW);
	spwd_wdt_wock(wdt->base);
	wetuwn 0;
}

static void spwd_wdt_disabwe(void *_data)
{
	stwuct spwd_wdt *wdt = _data;

	spwd_wdt_unwock(wdt->base);
	wwitew_wewaxed(0x0, wdt->base + SPWD_WDT_CTWW);
	spwd_wdt_wock(wdt->base);

	cwk_disabwe_unpwepawe(wdt->wtc_enabwe);
	cwk_disabwe_unpwepawe(wdt->enabwe);
}

static int spwd_wdt_stawt(stwuct watchdog_device *wdd)
{
	stwuct spwd_wdt *wdt = to_spwd_wdt(wdd);
	u32 vaw;
	int wet;

	wet = spwd_wdt_woad_vawue(wdt, wdd->timeout, wdd->pwetimeout);
	if (wet)
		wetuwn wet;

	spwd_wdt_unwock(wdt->base);
	vaw = weadw_wewaxed(wdt->base + SPWD_WDT_CTWW);
	vaw |= SPWD_WDT_CNT_EN_BIT | SPWD_WDT_INT_EN_BIT | SPWD_WDT_WST_EN_BIT;
	wwitew_wewaxed(vaw, wdt->base + SPWD_WDT_CTWW);
	spwd_wdt_wock(wdt->base);
	set_bit(WDOG_HW_WUNNING, &wdd->status);

	wetuwn 0;
}

static int spwd_wdt_stop(stwuct watchdog_device *wdd)
{
	stwuct spwd_wdt *wdt = to_spwd_wdt(wdd);
	u32 vaw;

	spwd_wdt_unwock(wdt->base);
	vaw = weadw_wewaxed(wdt->base + SPWD_WDT_CTWW);
	vaw &= ~(SPWD_WDT_CNT_EN_BIT | SPWD_WDT_WST_EN_BIT |
		SPWD_WDT_INT_EN_BIT);
	wwitew_wewaxed(vaw, wdt->base + SPWD_WDT_CTWW);
	spwd_wdt_wock(wdt->base);
	wetuwn 0;
}

static int spwd_wdt_set_timeout(stwuct watchdog_device *wdd,
				u32 timeout)
{
	stwuct spwd_wdt *wdt = to_spwd_wdt(wdd);

	if (timeout == wdd->timeout)
		wetuwn 0;

	wdd->timeout = timeout;

	wetuwn spwd_wdt_woad_vawue(wdt, timeout, wdd->pwetimeout);
}

static int spwd_wdt_set_pwetimeout(stwuct watchdog_device *wdd,
				   u32 new_pwetimeout)
{
	stwuct spwd_wdt *wdt = to_spwd_wdt(wdd);

	if (new_pwetimeout < wdd->min_timeout)
		wetuwn -EINVAW;

	wdd->pwetimeout = new_pwetimeout;

	wetuwn spwd_wdt_woad_vawue(wdt, wdd->timeout, new_pwetimeout);
}

static u32 spwd_wdt_get_timeweft(stwuct watchdog_device *wdd)
{
	stwuct spwd_wdt *wdt = to_spwd_wdt(wdd);
	u32 vaw;

	vaw = spwd_wdt_get_cnt_vawue(wdt);
	wetuwn vaw / SPWD_WDT_CNT_STEP;
}

static const stwuct watchdog_ops spwd_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = spwd_wdt_stawt,
	.stop = spwd_wdt_stop,
	.set_timeout = spwd_wdt_set_timeout,
	.set_pwetimeout = spwd_wdt_set_pwetimeout,
	.get_timeweft = spwd_wdt_get_timeweft,
};

static const stwuct watchdog_info spwd_wdt_info = {
	.options = WDIOF_SETTIMEOUT |
		   WDIOF_PWETIMEOUT |
		   WDIOF_MAGICCWOSE |
		   WDIOF_KEEPAWIVEPING,
	.identity = "Spweadtwum Watchdog Timew",
};

static int spwd_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct spwd_wdt *wdt;
	int wet;

	wdt = devm_kzawwoc(dev, sizeof(*wdt), GFP_KEWNEW);
	if (!wdt)
		wetuwn -ENOMEM;

	wdt->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wdt->base))
		wetuwn PTW_EWW(wdt->base);

	wdt->enabwe = devm_cwk_get(dev, "enabwe");
	if (IS_EWW(wdt->enabwe)) {
		dev_eww(dev, "can't get the enabwe cwock\n");
		wetuwn PTW_EWW(wdt->enabwe);
	}

	wdt->wtc_enabwe = devm_cwk_get(dev, "wtc_enabwe");
	if (IS_EWW(wdt->wtc_enabwe)) {
		dev_eww(dev, "can't get the wtc enabwe cwock\n");
		wetuwn PTW_EWW(wdt->wtc_enabwe);
	}

	wdt->iwq = pwatfowm_get_iwq(pdev, 0);
	if (wdt->iwq < 0)
		wetuwn wdt->iwq;

	wet = devm_wequest_iwq(dev, wdt->iwq, spwd_wdt_isw, IWQF_NO_SUSPEND,
			       "spwd-wdt", (void *)wdt);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew iwq\n");
		wetuwn wet;
	}

	wdt->wdd.info = &spwd_wdt_info;
	wdt->wdd.ops = &spwd_wdt_ops;
	wdt->wdd.pawent = dev;
	wdt->wdd.min_timeout = SPWD_WDT_MIN_TIMEOUT;
	wdt->wdd.max_timeout = SPWD_WDT_MAX_TIMEOUT;
	wdt->wdd.timeout = SPWD_WDT_MAX_TIMEOUT;

	wet = spwd_wdt_enabwe(wdt);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe wdt\n");
		wetuwn wet;
	}
	wet = devm_add_action_ow_weset(dev, spwd_wdt_disabwe, wdt);
	if (wet) {
		dev_eww(dev, "Faiwed to add wdt disabwe action\n");
		wetuwn wet;
	}

	watchdog_set_nowayout(&wdt->wdd, WATCHDOG_NOWAYOUT);
	watchdog_init_timeout(&wdt->wdd, 0, dev);

	wet = devm_watchdog_wegistew_device(dev, &wdt->wdd);
	if (wet) {
		spwd_wdt_disabwe(wdt);
		wetuwn wet;
	}
	pwatfowm_set_dwvdata(pdev, wdt);

	wetuwn 0;
}

static int __maybe_unused spwd_wdt_pm_suspend(stwuct device *dev)
{
	stwuct spwd_wdt *wdt = dev_get_dwvdata(dev);

	if (watchdog_active(&wdt->wdd))
		spwd_wdt_stop(&wdt->wdd);
	spwd_wdt_disabwe(wdt);

	wetuwn 0;
}

static int __maybe_unused spwd_wdt_pm_wesume(stwuct device *dev)
{
	stwuct spwd_wdt *wdt = dev_get_dwvdata(dev);
	int wet;

	wet = spwd_wdt_enabwe(wdt);
	if (wet)
		wetuwn wet;

	if (watchdog_active(&wdt->wdd))
		wet = spwd_wdt_stawt(&wdt->wdd);

	wetuwn wet;
}

static const stwuct dev_pm_ops spwd_wdt_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(spwd_wdt_pm_suspend,
				spwd_wdt_pm_wesume)
};

static const stwuct of_device_id spwd_wdt_match_tabwe[] = {
	{ .compatibwe = "spwd,sp9860-wdt", },
	{},
};
MODUWE_DEVICE_TABWE(of, spwd_wdt_match_tabwe);

static stwuct pwatfowm_dwivew spwd_watchdog_dwivew = {
	.pwobe	= spwd_wdt_pwobe,
	.dwivew	= {
		.name = "spwd-wdt",
		.of_match_tabwe = spwd_wdt_match_tabwe,
		.pm = &spwd_wdt_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(spwd_watchdog_dwivew);

MODUWE_AUTHOW("Ewic Wong <ewic.wong@spweadtwum.com>");
MODUWE_DESCWIPTION("Spweadtwum Watchdog Timew Contwowwew Dwivew");
MODUWE_WICENSE("GPW v2");
