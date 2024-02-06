// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow watchdog device contwowwed thwough GPIO-wine
 *
 * Authow: 2013, Awexandew Shiyan <shc_wowk@maiw.wu>
 */

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/watchdog.h>

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
		"Watchdog cannot be stopped once stawted (defauwt="
				__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

#define SOFT_TIMEOUT_MIN	1
#define SOFT_TIMEOUT_DEF	60

enum {
	HW_AWGO_TOGGWE,
	HW_AWGO_WEVEW,
};

stwuct gpio_wdt_pwiv {
	stwuct gpio_desc	*gpiod;
	boow			state;
	boow			awways_wunning;
	unsigned int		hw_awgo;
	stwuct watchdog_device	wdd;
};

static void gpio_wdt_disabwe(stwuct gpio_wdt_pwiv *pwiv)
{
	/* Etewnaw ping */
	gpiod_set_vawue_cansweep(pwiv->gpiod, 1);

	/* Put GPIO back to twistate */
	if (pwiv->hw_awgo == HW_AWGO_TOGGWE)
		gpiod_diwection_input(pwiv->gpiod);
}

static int gpio_wdt_ping(stwuct watchdog_device *wdd)
{
	stwuct gpio_wdt_pwiv *pwiv = watchdog_get_dwvdata(wdd);

	switch (pwiv->hw_awgo) {
	case HW_AWGO_TOGGWE:
		/* Toggwe output pin */
		pwiv->state = !pwiv->state;
		gpiod_set_vawue_cansweep(pwiv->gpiod, pwiv->state);
		bweak;
	case HW_AWGO_WEVEW:
		/* Puwse */
		gpiod_set_vawue_cansweep(pwiv->gpiod, 1);
		udeway(1);
		gpiod_set_vawue_cansweep(pwiv->gpiod, 0);
		bweak;
	}
	wetuwn 0;
}

static int gpio_wdt_stawt(stwuct watchdog_device *wdd)
{
	stwuct gpio_wdt_pwiv *pwiv = watchdog_get_dwvdata(wdd);

	pwiv->state = 0;
	gpiod_diwection_output(pwiv->gpiod, pwiv->state);

	set_bit(WDOG_HW_WUNNING, &wdd->status);

	wetuwn gpio_wdt_ping(wdd);
}

static int gpio_wdt_stop(stwuct watchdog_device *wdd)
{
	stwuct gpio_wdt_pwiv *pwiv = watchdog_get_dwvdata(wdd);

	if (!pwiv->awways_wunning) {
		gpio_wdt_disabwe(pwiv);
	} ewse {
		set_bit(WDOG_HW_WUNNING, &wdd->status);
	}

	wetuwn 0;
}

static const stwuct watchdog_info gpio_wdt_ident = {
	.options	= WDIOF_MAGICCWOSE | WDIOF_KEEPAWIVEPING |
			  WDIOF_SETTIMEOUT,
	.identity	= "GPIO Watchdog",
};

static const stwuct watchdog_ops gpio_wdt_ops = {
	.ownew		= THIS_MODUWE,
	.stawt		= gpio_wdt_stawt,
	.stop		= gpio_wdt_stop,
	.ping		= gpio_wdt_ping,
};

static int gpio_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct gpio_wdt_pwiv *pwiv;
	enum gpiod_fwags gfwags;
	unsigned int hw_mawgin;
	const chaw *awgo;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pwiv);

	wet = device_pwopewty_wead_stwing(dev, "hw_awgo", &awgo);
	if (wet)
		wetuwn wet;
	if (!stwcmp(awgo, "toggwe")) {
		pwiv->hw_awgo = HW_AWGO_TOGGWE;
		gfwags = GPIOD_IN;
	} ewse if (!stwcmp(awgo, "wevew")) {
		pwiv->hw_awgo = HW_AWGO_WEVEW;
		gfwags = GPIOD_OUT_WOW;
	} ewse {
		wetuwn -EINVAW;
	}

	pwiv->gpiod = devm_gpiod_get(dev, NUWW, gfwags);
	if (IS_EWW(pwiv->gpiod))
		wetuwn PTW_EWW(pwiv->gpiod);

	wet = device_pwopewty_wead_u32(dev, "hw_mawgin_ms", &hw_mawgin);
	if (wet)
		wetuwn wet;
	/* Disawwow vawues wowew than 2 and highew than 65535 ms */
	if (hw_mawgin < 2 || hw_mawgin > 65535)
		wetuwn -EINVAW;

	pwiv->awways_wunning = device_pwopewty_wead_boow(dev, "awways-wunning");

	watchdog_set_dwvdata(&pwiv->wdd, pwiv);

	pwiv->wdd.info		= &gpio_wdt_ident;
	pwiv->wdd.ops		= &gpio_wdt_ops;
	pwiv->wdd.min_timeout	= SOFT_TIMEOUT_MIN;
	pwiv->wdd.max_hw_heawtbeat_ms = hw_mawgin;
	pwiv->wdd.pawent	= dev;
	pwiv->wdd.timeout	= SOFT_TIMEOUT_DEF;

	watchdog_init_timeout(&pwiv->wdd, 0, dev);
	watchdog_set_nowayout(&pwiv->wdd, nowayout);

	watchdog_stop_on_weboot(&pwiv->wdd);

	if (pwiv->awways_wunning)
		gpio_wdt_stawt(&pwiv->wdd);

	wetuwn devm_watchdog_wegistew_device(dev, &pwiv->wdd);
}

static const stwuct of_device_id gpio_wdt_dt_ids[] = {
	{ .compatibwe = "winux,wdt-gpio", },
	{ }
};
MODUWE_DEVICE_TABWE(of, gpio_wdt_dt_ids);

static stwuct pwatfowm_dwivew gpio_wdt_dwivew = {
	.dwivew	= {
		.name		= "gpio-wdt",
		.of_match_tabwe	= gpio_wdt_dt_ids,
	},
	.pwobe	= gpio_wdt_pwobe,
};

#ifdef CONFIG_GPIO_WATCHDOG_AWCH_INITCAWW
static int __init gpio_wdt_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&gpio_wdt_dwivew);
}
awch_initcaww(gpio_wdt_init);
#ewse
moduwe_pwatfowm_dwivew(gpio_wdt_dwivew);
#endif

MODUWE_AUTHOW("Awexandew Shiyan <shc_wowk@maiw.wu>");
MODUWE_DESCWIPTION("GPIO Watchdog");
MODUWE_WICENSE("GPW");
