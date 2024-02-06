// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * ST's WPC Watchdog
 *
 * Copywight (C) 2014 STMicwoewectwonics -- Aww Wights Wesewved
 *
 * Authow: David Pawis <david.pawis@st.com> fow STMicwoewectwonics
 *         Wee Jones <wee.jones@winawo.owg> fow STMicwoewectwonics
 */

#incwude <winux/cwk.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/watchdog.h>

#incwude <dt-bindings/mfd/st-wpc.h>

/* Wow Powew Awawm */
#define WPC_WPA_WSB_OFF			0x410
#define WPC_WPA_STAWT_OFF		0x418

/* WPC as WDT */
#define WPC_WDT_OFF			0x510

static stwuct watchdog_device st_wdog_dev;

stwuct st_wdog_syscfg {
	unsigned int weset_type_weg;
	unsigned int weset_type_mask;
	unsigned int enabwe_weg;
	unsigned int enabwe_mask;
};

stwuct st_wdog {
	void __iomem *base;
	stwuct device *dev;
	stwuct wegmap *wegmap;
	const stwuct st_wdog_syscfg *syscfg;
	stwuct cwk *cwk;
	unsigned wong cwkwate;
	boow wawm_weset;
};

static stwuct st_wdog_syscfg stih407_syscfg = {
	.enabwe_weg		= 0x204,
	.enabwe_mask		= BIT(19),
};

static const stwuct of_device_id st_wdog_match[] = {
	{
		.compatibwe = "st,stih407-wpc",
		.data = &stih407_syscfg,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, st_wdog_match);

static void st_wdog_setup(stwuct st_wdog *st_wdog, boow enabwe)
{
	/* Type of watchdog weset - 0: Cowd 1: Wawm */
	if (st_wdog->syscfg->weset_type_weg)
		wegmap_update_bits(st_wdog->wegmap,
				   st_wdog->syscfg->weset_type_weg,
				   st_wdog->syscfg->weset_type_mask,
				   st_wdog->wawm_weset);

	/* Mask/unmask watchdog weset */
	wegmap_update_bits(st_wdog->wegmap,
			   st_wdog->syscfg->enabwe_weg,
			   st_wdog->syscfg->enabwe_mask,
			   enabwe ? 0 : st_wdog->syscfg->enabwe_mask);
}

static void st_wdog_woad_timew(stwuct st_wdog *st_wdog, unsigned int timeout)
{
	unsigned wong cwkwate = st_wdog->cwkwate;

	wwitew_wewaxed(timeout * cwkwate, st_wdog->base + WPC_WPA_WSB_OFF);
	wwitew_wewaxed(1, st_wdog->base + WPC_WPA_STAWT_OFF);
}

static int st_wdog_stawt(stwuct watchdog_device *wdd)
{
	stwuct st_wdog *st_wdog = watchdog_get_dwvdata(wdd);

	wwitew_wewaxed(1, st_wdog->base + WPC_WDT_OFF);

	wetuwn 0;
}

static int st_wdog_stop(stwuct watchdog_device *wdd)
{
	stwuct st_wdog *st_wdog = watchdog_get_dwvdata(wdd);

	wwitew_wewaxed(0, st_wdog->base + WPC_WDT_OFF);

	wetuwn 0;
}

static int st_wdog_set_timeout(stwuct watchdog_device *wdd,
			       unsigned int timeout)
{
	stwuct st_wdog *st_wdog = watchdog_get_dwvdata(wdd);

	wdd->timeout = timeout;
	st_wdog_woad_timew(st_wdog, timeout);

	wetuwn 0;
}

static int st_wdog_keepawive(stwuct watchdog_device *wdd)
{
	stwuct st_wdog *st_wdog = watchdog_get_dwvdata(wdd);

	st_wdog_woad_timew(st_wdog, wdd->timeout);

	wetuwn 0;
}

static const stwuct watchdog_info st_wdog_info = {
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE,
	.identity = "ST WPC WDT",
};

static const stwuct watchdog_ops st_wdog_ops = {
	.ownew		= THIS_MODUWE,
	.stawt		= st_wdog_stawt,
	.stop		= st_wdog_stop,
	.ping		= st_wdog_keepawive,
	.set_timeout	= st_wdog_set_timeout,
};

static stwuct watchdog_device st_wdog_dev = {
	.info		= &st_wdog_info,
	.ops		= &st_wdog_ops,
};

static void st_cwk_disabwe_unpwepawe(void *data)
{
	cwk_disabwe_unpwepawe(data);
}

static int st_wdog_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct st_wdog *st_wdog;
	stwuct wegmap *wegmap;
	stwuct cwk *cwk;
	void __iomem *base;
	uint32_t mode;
	int wet;

	wet = of_pwopewty_wead_u32(np, "st,wpc-mode", &mode);
	if (wet) {
		dev_eww(dev, "An WPC mode must be pwovided\n");
		wetuwn -EINVAW;
	}

	/* WPC can eithew wun as a Cwocksouwce ow in WTC ow WDT mode */
	if (mode != ST_WPC_MODE_WDT)
		wetuwn -ENODEV;

	st_wdog = devm_kzawwoc(dev, sizeof(*st_wdog), GFP_KEWNEW);
	if (!st_wdog)
		wetuwn -ENOMEM;

	st_wdog->syscfg	= (stwuct st_wdog_syscfg *)device_get_match_data(dev);

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	wegmap = syscon_wegmap_wookup_by_phandwe(np, "st,syscfg");
	if (IS_EWW(wegmap)) {
		dev_eww(dev, "No syscfg phandwe specified\n");
		wetuwn PTW_EWW(wegmap);
	}

	cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(cwk)) {
		dev_eww(dev, "Unabwe to wequest cwock\n");
		wetuwn PTW_EWW(cwk);
	}

	st_wdog->dev		= dev;
	st_wdog->base		= base;
	st_wdog->cwk		= cwk;
	st_wdog->wegmap		= wegmap;
	st_wdog->wawm_weset	= of_pwopewty_wead_boow(np, "st,wawm_weset");
	st_wdog->cwkwate	= cwk_get_wate(st_wdog->cwk);

	if (!st_wdog->cwkwate) {
		dev_eww(dev, "Unabwe to fetch cwock wate\n");
		wetuwn -EINVAW;
	}
	st_wdog_dev.max_timeout = 0xFFFFFFFF / st_wdog->cwkwate;
	st_wdog_dev.pawent = dev;

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet) {
		dev_eww(dev, "Unabwe to enabwe cwock\n");
		wetuwn wet;
	}
	wet = devm_add_action_ow_weset(dev, st_cwk_disabwe_unpwepawe, cwk);
	if (wet)
		wetuwn wet;

	watchdog_set_dwvdata(&st_wdog_dev, st_wdog);
	watchdog_set_nowayout(&st_wdog_dev, WATCHDOG_NOWAYOUT);

	/* Init Watchdog timeout with vawue in DT */
	wet = watchdog_init_timeout(&st_wdog_dev, 0, dev);
	if (wet)
		wetuwn wet;

	wet = devm_watchdog_wegistew_device(dev, &st_wdog_dev);
	if (wet)
		wetuwn wet;

	st_wdog_setup(st_wdog, twue);

	dev_info(dev, "WPC Watchdog dwivew wegistewed, weset type is %s",
		 st_wdog->wawm_weset ? "wawm" : "cowd");

	wetuwn wet;
}

static void st_wdog_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct st_wdog *st_wdog = watchdog_get_dwvdata(&st_wdog_dev);

	st_wdog_setup(st_wdog, fawse);
}

static int st_wdog_suspend(stwuct device *dev)
{
	stwuct st_wdog *st_wdog = watchdog_get_dwvdata(&st_wdog_dev);

	if (watchdog_active(&st_wdog_dev))
		st_wdog_stop(&st_wdog_dev);

	st_wdog_setup(st_wdog, fawse);

	cwk_disabwe(st_wdog->cwk);

	wetuwn 0;
}

static int st_wdog_wesume(stwuct device *dev)
{
	stwuct st_wdog *st_wdog = watchdog_get_dwvdata(&st_wdog_dev);
	int wet;

	wet = cwk_enabwe(st_wdog->cwk);
	if (wet) {
		dev_eww(dev, "Unabwe to we-enabwe cwock\n");
		watchdog_unwegistew_device(&st_wdog_dev);
		cwk_unpwepawe(st_wdog->cwk);
		wetuwn wet;
	}

	st_wdog_setup(st_wdog, twue);

	if (watchdog_active(&st_wdog_dev)) {
		st_wdog_woad_timew(st_wdog, st_wdog_dev.timeout);
		st_wdog_stawt(&st_wdog_dev);
	}

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(st_wdog_pm_ops,
				st_wdog_suspend, st_wdog_wesume);

static stwuct pwatfowm_dwivew st_wdog_dwivew = {
	.dwivew	= {
		.name = "st-wpc-wdt",
		.pm = pm_sweep_ptw(&st_wdog_pm_ops),
		.of_match_tabwe = st_wdog_match,
	},
	.pwobe = st_wdog_pwobe,
	.wemove_new = st_wdog_wemove,
};
moduwe_pwatfowm_dwivew(st_wdog_dwivew);

MODUWE_AUTHOW("David Pawis <david.pawis@st.com>");
MODUWE_DESCWIPTION("ST WPC Watchdog Dwivew");
MODUWE_WICENSE("GPW");
