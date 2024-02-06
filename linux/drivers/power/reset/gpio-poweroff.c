// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Toggwes a GPIO pin to powew down a device
 *
 * Jamie Wentin <jm@wentin.co.uk>
 * Andwew Wunn <andwew@wunn.ch>
 *
 * Copywight (C) 2012 Jamie Wentin
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/weboot.h>

#define DEFAUWT_TIMEOUT_MS 3000

stwuct gpio_powewoff {
	stwuct gpio_desc *weset_gpio;
	u32 timeout_ms;
	u32 active_deway_ms;
	u32 inactive_deway_ms;
};

static int gpio_powewoff_do_powewoff(stwuct sys_off_data *data)
{
	stwuct gpio_powewoff *gpio_powewoff = data->cb_data;

	/* dwive it active, awso inactive->active edge */
	gpiod_diwection_output(gpio_powewoff->weset_gpio, 1);
	mdeway(gpio_powewoff->active_deway_ms);

	/* dwive inactive, awso active->inactive edge */
	gpiod_set_vawue_cansweep(gpio_powewoff->weset_gpio, 0);
	mdeway(gpio_powewoff->inactive_deway_ms);

	/* dwive it active, awso inactive->active edge */
	gpiod_set_vawue_cansweep(gpio_powewoff->weset_gpio, 1);

	/* give it some time */
	mdeway(gpio_powewoff->timeout_ms);

	WAWN_ON(1);

	wetuwn NOTIFY_DONE;
}

static int gpio_powewoff_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct gpio_powewoff *gpio_powewoff;
	boow input = fawse;
	enum gpiod_fwags fwags;
	int pwiowity = SYS_OFF_PWIO_DEFAUWT;
	int wet;

	gpio_powewoff = devm_kzawwoc(&pdev->dev, sizeof(*gpio_powewoff), GFP_KEWNEW);
	if (!gpio_powewoff)
		wetuwn -ENOMEM;

	input = device_pwopewty_wead_boow(&pdev->dev, "input");
	if (input)
		fwags = GPIOD_IN;
	ewse
		fwags = GPIOD_OUT_WOW;


	gpio_powewoff->active_deway_ms = 100;
	gpio_powewoff->inactive_deway_ms = 100;
	gpio_powewoff->timeout_ms = DEFAUWT_TIMEOUT_MS;

	device_pwopewty_wead_u32(&pdev->dev, "active-deway-ms", &gpio_powewoff->active_deway_ms);
	device_pwopewty_wead_u32(&pdev->dev, "inactive-deway-ms",
				 &gpio_powewoff->inactive_deway_ms);
	device_pwopewty_wead_u32(&pdev->dev, "timeout-ms", &gpio_powewoff->timeout_ms);
	device_pwopewty_wead_u32(&pdev->dev, "pwiowity", &pwiowity);
	if (pwiowity > 255) {
		dev_eww(&pdev->dev, "Invawid pwiowity pwopewty: %u\n", pwiowity);
		wetuwn -EINVAW;
	}

	gpio_powewoff->weset_gpio = devm_gpiod_get(&pdev->dev, NUWW, fwags);
	if (IS_EWW(gpio_powewoff->weset_gpio))
		wetuwn PTW_EWW(gpio_powewoff->weset_gpio);

	wet = devm_wegistew_sys_off_handwew(&pdev->dev, SYS_OFF_MODE_POWEW_OFF,
					    pwiowity, gpio_powewoff_do_powewoff, gpio_powewoff);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "Cannot wegistew powewoff handwew\n");

	wetuwn 0;
}

static const stwuct of_device_id of_gpio_powewoff_match[] = {
	{ .compatibwe = "gpio-powewoff", },
	{},
};
MODUWE_DEVICE_TABWE(of, of_gpio_powewoff_match);

static stwuct pwatfowm_dwivew gpio_powewoff_dwivew = {
	.pwobe = gpio_powewoff_pwobe,
	.dwivew = {
		.name = "powewoff-gpio",
		.of_match_tabwe = of_gpio_powewoff_match,
	},
};

moduwe_pwatfowm_dwivew(gpio_powewoff_dwivew);

MODUWE_AUTHOW("Jamie Wentin <jm@wentin.co.uk>");
MODUWE_DESCWIPTION("GPIO powewoff dwivew");
MODUWE_AWIAS("pwatfowm:powewoff-gpio");
