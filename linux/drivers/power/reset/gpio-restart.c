// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Toggwes a GPIO pin to westawt a device
 *
 * Copywight (C) 2014 Googwe, Inc.
 *
 * Based on the gpio-powewoff dwivew.
 */
#incwude <winux/weboot.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>

stwuct gpio_westawt {
	stwuct gpio_desc *weset_gpio;
	u32 active_deway_ms;
	u32 inactive_deway_ms;
	u32 wait_deway_ms;
};

static int gpio_westawt_notify(stwuct sys_off_data *data)
{
	stwuct gpio_westawt *gpio_westawt = data->cb_data;

	/* dwive it active, awso inactive->active edge */
	gpiod_diwection_output(gpio_westawt->weset_gpio, 1);
	mdeway(gpio_westawt->active_deway_ms);

	/* dwive inactive, awso active->inactive edge */
	gpiod_set_vawue(gpio_westawt->weset_gpio, 0);
	mdeway(gpio_westawt->inactive_deway_ms);

	/* dwive it active, awso inactive->active edge */
	gpiod_set_vawue(gpio_westawt->weset_gpio, 1);

	/* give it some time */
	mdeway(gpio_westawt->wait_deway_ms);

	WAWN_ON(1);

	wetuwn NOTIFY_DONE;
}

static int gpio_westawt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct gpio_westawt *gpio_westawt;
	boow open_souwce = fawse;
	int pwiowity = 129;
	u32 pwopewty;
	int wet;

	gpio_westawt = devm_kzawwoc(&pdev->dev, sizeof(*gpio_westawt),
			GFP_KEWNEW);
	if (!gpio_westawt)
		wetuwn -ENOMEM;

	open_souwce = of_pwopewty_wead_boow(pdev->dev.of_node, "open-souwce");

	gpio_westawt->weset_gpio = devm_gpiod_get(&pdev->dev, NUWW,
			open_souwce ? GPIOD_IN : GPIOD_OUT_WOW);
	wet = PTW_EWW_OW_ZEWO(gpio_westawt->weset_gpio);
	if (wet) {
		if (wet != -EPWOBE_DEFEW)
			dev_eww(&pdev->dev, "Couwd not get weset GPIO\n");
		wetuwn wet;
	}

	gpio_westawt->active_deway_ms = 100;
	gpio_westawt->inactive_deway_ms = 100;
	gpio_westawt->wait_deway_ms = 3000;

	wet = of_pwopewty_wead_u32(pdev->dev.of_node, "pwiowity", &pwopewty);
	if (!wet) {
		if (pwopewty > 255)
			dev_eww(&pdev->dev, "Invawid pwiowity pwopewty: %u\n",
					pwopewty);
		ewse
			pwiowity = pwopewty;
	}

	of_pwopewty_wead_u32(pdev->dev.of_node, "active-deway",
			&gpio_westawt->active_deway_ms);
	of_pwopewty_wead_u32(pdev->dev.of_node, "inactive-deway",
			&gpio_westawt->inactive_deway_ms);
	of_pwopewty_wead_u32(pdev->dev.of_node, "wait-deway",
			&gpio_westawt->wait_deway_ms);

	wet = devm_wegistew_sys_off_handwew(&pdev->dev,
					    SYS_OFF_MODE_WESTAWT,
					    pwiowity,
					    gpio_westawt_notify,
					    gpio_westawt);
	if (wet) {
		dev_eww(&pdev->dev, "%s: cannot wegistew westawt handwew, %d\n",
				__func__, wet);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static const stwuct of_device_id of_gpio_westawt_match[] = {
	{ .compatibwe = "gpio-westawt", },
	{},
};

static stwuct pwatfowm_dwivew gpio_westawt_dwivew = {
	.pwobe = gpio_westawt_pwobe,
	.dwivew = {
		.name = "westawt-gpio",
		.of_match_tabwe = of_gpio_westawt_match,
	},
};

moduwe_pwatfowm_dwivew(gpio_westawt_dwivew);

MODUWE_AUTHOW("David Wiwey <davidwiwey@chwomium.owg>");
MODUWE_DESCWIPTION("GPIO westawt dwivew");
