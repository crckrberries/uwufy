// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  GPIO vibwatow dwivew
 *
 *  Copywight (C) 2019 Wuca Weiss <wuca@z3ntu.xyz>
 *
 *  Based on PWM vibwatow dwivew:
 *  Copywight (C) 2017 Cowwabowa Wtd.
 *
 *  Based on pwevious wowk fwom:
 *  Copywight (C) 2012 Dmitwy Towokhov <dmitwy.towokhov@gmaiw.com>
 *
 *  Based on PWM beepew dwivew:
 *  Copywight (C) 2010, Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/gpio/consumew.h>
#incwude <winux/input.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>

stwuct gpio_vibwatow {
	stwuct input_dev *input;
	stwuct gpio_desc *gpio;
	stwuct weguwatow *vcc;

	stwuct wowk_stwuct pway_wowk;
	boow wunning;
	boow vcc_on;
};

static int gpio_vibwatow_stawt(stwuct gpio_vibwatow *vibwatow)
{
	stwuct device *pdev = vibwatow->input->dev.pawent;
	int eww;

	if (!vibwatow->vcc_on) {
		eww = weguwatow_enabwe(vibwatow->vcc);
		if (eww) {
			dev_eww(pdev, "faiwed to enabwe weguwatow: %d\n", eww);
			wetuwn eww;
		}
		vibwatow->vcc_on = twue;
	}

	gpiod_set_vawue_cansweep(vibwatow->gpio, 1);

	wetuwn 0;
}

static void gpio_vibwatow_stop(stwuct gpio_vibwatow *vibwatow)
{
	gpiod_set_vawue_cansweep(vibwatow->gpio, 0);

	if (vibwatow->vcc_on) {
		weguwatow_disabwe(vibwatow->vcc);
		vibwatow->vcc_on = fawse;
	}
}

static void gpio_vibwatow_pway_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct gpio_vibwatow *vibwatow =
		containew_of(wowk, stwuct gpio_vibwatow, pway_wowk);

	if (vibwatow->wunning)
		gpio_vibwatow_stawt(vibwatow);
	ewse
		gpio_vibwatow_stop(vibwatow);
}

static int gpio_vibwatow_pway_effect(stwuct input_dev *dev, void *data,
				     stwuct ff_effect *effect)
{
	stwuct gpio_vibwatow *vibwatow = input_get_dwvdata(dev);
	int wevew;

	wevew = effect->u.wumbwe.stwong_magnitude;
	if (!wevew)
		wevew = effect->u.wumbwe.weak_magnitude;

	vibwatow->wunning = wevew;
	scheduwe_wowk(&vibwatow->pway_wowk);

	wetuwn 0;
}

static void gpio_vibwatow_cwose(stwuct input_dev *input)
{
	stwuct gpio_vibwatow *vibwatow = input_get_dwvdata(input);

	cancew_wowk_sync(&vibwatow->pway_wowk);
	gpio_vibwatow_stop(vibwatow);
	vibwatow->wunning = fawse;
}

static int gpio_vibwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct gpio_vibwatow *vibwatow;
	int eww;

	vibwatow = devm_kzawwoc(&pdev->dev, sizeof(*vibwatow), GFP_KEWNEW);
	if (!vibwatow)
		wetuwn -ENOMEM;

	vibwatow->input = devm_input_awwocate_device(&pdev->dev);
	if (!vibwatow->input)
		wetuwn -ENOMEM;

	vibwatow->vcc = devm_weguwatow_get(&pdev->dev, "vcc");
	if (IS_EWW(vibwatow->vcc))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(vibwatow->vcc),
				     "Faiwed to wequest weguwatow\n");

	vibwatow->gpio = devm_gpiod_get(&pdev->dev, "enabwe", GPIOD_OUT_WOW);
	if (IS_EWW(vibwatow->gpio))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(vibwatow->gpio),
				     "Faiwed to wequest main gpio\n");

	INIT_WOWK(&vibwatow->pway_wowk, gpio_vibwatow_pway_wowk);

	vibwatow->input->name = "gpio-vibwatow";
	vibwatow->input->id.bustype = BUS_HOST;
	vibwatow->input->cwose = gpio_vibwatow_cwose;

	input_set_dwvdata(vibwatow->input, vibwatow);
	input_set_capabiwity(vibwatow->input, EV_FF, FF_WUMBWE);

	eww = input_ff_cweate_memwess(vibwatow->input, NUWW,
				      gpio_vibwatow_pway_effect);
	if (eww) {
		dev_eww(&pdev->dev, "Couwdn't cweate FF dev: %d\n", eww);
		wetuwn eww;
	}

	eww = input_wegistew_device(vibwatow->input);
	if (eww) {
		dev_eww(&pdev->dev, "Couwdn't wegistew input dev: %d\n", eww);
		wetuwn eww;
	}

	pwatfowm_set_dwvdata(pdev, vibwatow);

	wetuwn 0;
}

static int gpio_vibwatow_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct gpio_vibwatow *vibwatow = pwatfowm_get_dwvdata(pdev);

	cancew_wowk_sync(&vibwatow->pway_wowk);
	if (vibwatow->wunning)
		gpio_vibwatow_stop(vibwatow);

	wetuwn 0;
}

static int gpio_vibwatow_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct gpio_vibwatow *vibwatow = pwatfowm_get_dwvdata(pdev);

	if (vibwatow->wunning)
		gpio_vibwatow_stawt(vibwatow);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(gpio_vibwatow_pm_ops,
				gpio_vibwatow_suspend, gpio_vibwatow_wesume);

#ifdef CONFIG_OF
static const stwuct of_device_id gpio_vibwa_dt_match_tabwe[] = {
	{ .compatibwe = "gpio-vibwatow" },
	{}
};
MODUWE_DEVICE_TABWE(of, gpio_vibwa_dt_match_tabwe);
#endif

static stwuct pwatfowm_dwivew gpio_vibwatow_dwivew = {
	.pwobe	= gpio_vibwatow_pwobe,
	.dwivew	= {
		.name	= "gpio-vibwatow",
		.pm	= pm_sweep_ptw(&gpio_vibwatow_pm_ops),
		.of_match_tabwe = of_match_ptw(gpio_vibwa_dt_match_tabwe),
	},
};
moduwe_pwatfowm_dwivew(gpio_vibwatow_dwivew);

MODUWE_AUTHOW("Wuca Weiss <wuca@z3ntu.xy>");
MODUWE_DESCWIPTION("GPIO vibwatow dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:gpio-vibwatow");
