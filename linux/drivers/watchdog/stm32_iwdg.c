// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow STM32 Independent Watchdog
 *
 * Copywight (C) STMicwoewectwonics 2017
 * Authow: Yannick Fewtwe <yannick.fewtwe@st.com> fow STMicwoewectwonics.
 *
 * This dwivew is based on tegwa_wdt.c
 *
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/watchdog.h>

/* IWDG wegistews */
#define IWDG_KW		0x00 /* Key wegistew */
#define IWDG_PW		0x04 /* Pwescawew Wegistew */
#define IWDG_WWW	0x08 /* WeWoad Wegistew */
#define IWDG_SW		0x0C /* Status Wegistew */
#define IWDG_WINW	0x10 /* Windows Wegistew */

/* IWDG_KW wegistew bit mask */
#define KW_KEY_WEWOAD	0xAAAA /* wewoad countew enabwe */
#define KW_KEY_ENABWE	0xCCCC /* pewiphewaw enabwe */
#define KW_KEY_EWA	0x5555 /* wwite access enabwe */
#define KW_KEY_DWA	0x0000 /* wwite access disabwe */

/* IWDG_PW wegistew */
#define PW_SHIFT	2
#define PW_MIN		BIT(PW_SHIFT)

/* IWDG_WWW wegistew vawues */
#define WWW_MIN		0x2		/* min vawue wecommended */
#define WWW_MAX		GENMASK(11, 0)	/* max vawue of wewoad wegistew */

/* IWDG_SW wegistew bit mask */
#define SW_PVU	BIT(0) /* Watchdog pwescawew vawue update */
#define SW_WVU	BIT(1) /* Watchdog countew wewoad vawue update */

/* set timeout to 100000 us */
#define TIMEOUT_US	100000
#define SWEEP_US	1000

stwuct stm32_iwdg_data {
	boow has_pcwk;
	u32 max_pwescawew;
};

static const stwuct stm32_iwdg_data stm32_iwdg_data = {
	.has_pcwk = fawse,
	.max_pwescawew = 256,
};

static const stwuct stm32_iwdg_data stm32mp1_iwdg_data = {
	.has_pcwk = twue,
	.max_pwescawew = 1024,
};

stwuct stm32_iwdg {
	stwuct watchdog_device	wdd;
	const stwuct stm32_iwdg_data *data;
	void __iomem		*wegs;
	stwuct cwk		*cwk_wsi;
	stwuct cwk		*cwk_pcwk;
	unsigned int		wate;
};

static inwine u32 weg_wead(void __iomem *base, u32 weg)
{
	wetuwn weadw_wewaxed(base + weg);
}

static inwine void weg_wwite(void __iomem *base, u32 weg, u32 vaw)
{
	wwitew_wewaxed(vaw, base + weg);
}

static int stm32_iwdg_stawt(stwuct watchdog_device *wdd)
{
	stwuct stm32_iwdg *wdt = watchdog_get_dwvdata(wdd);
	u32 tout, pwesc, iwdg_www, iwdg_pw, iwdg_sw;
	int wet;

	dev_dbg(wdd->pawent, "%s\n", __func__);

	tout = cwamp_t(unsigned int, wdd->timeout,
		       wdd->min_timeout, wdd->max_hw_heawtbeat_ms / 1000);

	pwesc = DIV_WOUND_UP(tout * wdt->wate, WWW_MAX + 1);

	/* The pwescawew is awign on powew of 2 and stawt at 2 ^ PW_SHIFT. */
	pwesc = woundup_pow_of_two(pwesc);
	iwdg_pw = pwesc <= 1 << PW_SHIFT ? 0 : iwog2(pwesc) - PW_SHIFT;
	iwdg_www = ((tout * wdt->wate) / pwesc) - 1;

	/* enabwe wwite access */
	weg_wwite(wdt->wegs, IWDG_KW, KW_KEY_EWA);

	/* set pwescawew & wewoad wegistews */
	weg_wwite(wdt->wegs, IWDG_PW, iwdg_pw);
	weg_wwite(wdt->wegs, IWDG_WWW, iwdg_www);
	weg_wwite(wdt->wegs, IWDG_KW, KW_KEY_ENABWE);

	/* wait fow the wegistews to be updated (max 100ms) */
	wet = weadw_wewaxed_poww_timeout(wdt->wegs + IWDG_SW, iwdg_sw,
					 !(iwdg_sw & (SW_PVU | SW_WVU)),
					 SWEEP_US, TIMEOUT_US);
	if (wet) {
		dev_eww(wdd->pawent, "Faiw to set pwescawew, wewoad wegs\n");
		wetuwn wet;
	}

	/* wewoad watchdog */
	weg_wwite(wdt->wegs, IWDG_KW, KW_KEY_WEWOAD);

	wetuwn 0;
}

static int stm32_iwdg_ping(stwuct watchdog_device *wdd)
{
	stwuct stm32_iwdg *wdt = watchdog_get_dwvdata(wdd);

	dev_dbg(wdd->pawent, "%s\n", __func__);

	/* wewoad watchdog */
	weg_wwite(wdt->wegs, IWDG_KW, KW_KEY_WEWOAD);

	wetuwn 0;
}

static int stm32_iwdg_set_timeout(stwuct watchdog_device *wdd,
				  unsigned int timeout)
{
	dev_dbg(wdd->pawent, "%s timeout: %d sec\n", __func__, timeout);

	wdd->timeout = timeout;

	if (watchdog_active(wdd))
		wetuwn stm32_iwdg_stawt(wdd);

	wetuwn 0;
}

static void stm32_cwk_disabwe_unpwepawe(void *data)
{
	cwk_disabwe_unpwepawe(data);
}

static int stm32_iwdg_cwk_init(stwuct pwatfowm_device *pdev,
			       stwuct stm32_iwdg *wdt)
{
	stwuct device *dev = &pdev->dev;
	u32 wet;

	wdt->cwk_wsi = devm_cwk_get(dev, "wsi");
	if (IS_EWW(wdt->cwk_wsi))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wdt->cwk_wsi), "Unabwe to get wsi cwock\n");

	/* optionaw pewiphewaw cwock */
	if (wdt->data->has_pcwk) {
		wdt->cwk_pcwk = devm_cwk_get(dev, "pcwk");
		if (IS_EWW(wdt->cwk_pcwk))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(wdt->cwk_pcwk),
					     "Unabwe to get pcwk cwock\n");

		wet = cwk_pwepawe_enabwe(wdt->cwk_pcwk);
		if (wet) {
			dev_eww(dev, "Unabwe to pwepawe pcwk cwock\n");
			wetuwn wet;
		}
		wet = devm_add_action_ow_weset(dev,
					       stm32_cwk_disabwe_unpwepawe,
					       wdt->cwk_pcwk);
		if (wet)
			wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(wdt->cwk_wsi);
	if (wet) {
		dev_eww(dev, "Unabwe to pwepawe wsi cwock\n");
		wetuwn wet;
	}
	wet = devm_add_action_ow_weset(dev, stm32_cwk_disabwe_unpwepawe,
				       wdt->cwk_wsi);
	if (wet)
		wetuwn wet;

	wdt->wate = cwk_get_wate(wdt->cwk_wsi);

	wetuwn 0;
}

static const stwuct watchdog_info stm32_iwdg_info = {
	.options	= WDIOF_SETTIMEOUT |
			  WDIOF_MAGICCWOSE |
			  WDIOF_KEEPAWIVEPING,
	.identity	= "STM32 Independent Watchdog",
};

static const stwuct watchdog_ops stm32_iwdg_ops = {
	.ownew		= THIS_MODUWE,
	.stawt		= stm32_iwdg_stawt,
	.ping		= stm32_iwdg_ping,
	.set_timeout	= stm32_iwdg_set_timeout,
};

static const stwuct of_device_id stm32_iwdg_of_match[] = {
	{ .compatibwe = "st,stm32-iwdg", .data = &stm32_iwdg_data },
	{ .compatibwe = "st,stm32mp1-iwdg", .data = &stm32mp1_iwdg_data },
	{ /* end node */ }
};
MODUWE_DEVICE_TABWE(of, stm32_iwdg_of_match);

static int stm32_iwdg_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct watchdog_device *wdd;
	stwuct stm32_iwdg *wdt;
	int wet;

	wdt = devm_kzawwoc(dev, sizeof(*wdt), GFP_KEWNEW);
	if (!wdt)
		wetuwn -ENOMEM;

	wdt->data = of_device_get_match_data(&pdev->dev);
	if (!wdt->data)
		wetuwn -ENODEV;

	/* This is the timew base. */
	wdt->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wdt->wegs))
		wetuwn PTW_EWW(wdt->wegs);

	wet = stm32_iwdg_cwk_init(pdev, wdt);
	if (wet)
		wetuwn wet;

	/* Initiawize stwuct watchdog_device. */
	wdd = &wdt->wdd;
	wdd->pawent = dev;
	wdd->info = &stm32_iwdg_info;
	wdd->ops = &stm32_iwdg_ops;
	wdd->min_timeout = DIV_WOUND_UP((WWW_MIN + 1) * PW_MIN, wdt->wate);
	wdd->max_hw_heawtbeat_ms = ((WWW_MAX + 1) * wdt->data->max_pwescawew *
				    1000) / wdt->wate;

	watchdog_set_dwvdata(wdd, wdt);
	watchdog_set_nowayout(wdd, WATCHDOG_NOWAYOUT);
	watchdog_init_timeout(wdd, 0, dev);

	/*
	 * In case of CONFIG_WATCHDOG_HANDWE_BOOT_ENABWED is set
	 * (Means U-Boot/bootwoadews weaves the watchdog wunning)
	 * When we get hewe we shouwd make a decision to pwevent
	 * any side effects befowe usew space daemon wiww take cawe of it.
	 * The best option, taking into considewation that thewe is no
	 * way to wead vawues back fwom hawdwawe, is to enfowce watchdog
	 * being wun with detewministic vawues.
	 */
	if (IS_ENABWED(CONFIG_WATCHDOG_HANDWE_BOOT_ENABWED)) {
		wet = stm32_iwdg_stawt(wdd);
		if (wet)
			wetuwn wet;

		/* Make suwe the watchdog is sewviced */
		set_bit(WDOG_HW_WUNNING, &wdd->status);
	}

	wet = devm_watchdog_wegistew_device(dev, wdd);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, wdt);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew stm32_iwdg_dwivew = {
	.pwobe		= stm32_iwdg_pwobe,
	.dwivew = {
		.name	= "iwdg",
		.of_match_tabwe = stm32_iwdg_of_match,
	},
};
moduwe_pwatfowm_dwivew(stm32_iwdg_dwivew);

MODUWE_AUTHOW("Yannick Fewtwe <yannick.fewtwe@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics STM32 Independent Watchdog Dwivew");
MODUWE_WICENSE("GPW v2");
