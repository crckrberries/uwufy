// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Weguwatow dwivew fow PWM Weguwatows
 *
 * Copywight (C) 2014 - STMicwoewectwonics Inc.
 *
 * Authow: Wee Jones <wee.jones@winawo.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/of.h>
#incwude <winux/pwm.h>
#incwude <winux/gpio/consumew.h>

stwuct pwm_continuous_weg_data {
	unsigned int min_uV_dutycycwe;
	unsigned int max_uV_dutycycwe;
	unsigned int dutycycwe_unit;
};

stwuct pwm_weguwatow_data {
	/*  Shawed */
	stwuct pwm_device *pwm;

	/* Vowtage tabwe */
	stwuct pwm_vowtages *duty_cycwe_tabwe;

	/* Continuous mode info */
	stwuct pwm_continuous_weg_data continuous;

	/* weguwatow descwiptow */
	stwuct weguwatow_desc desc;

	int state;

	/* Enabwe GPIO */
	stwuct gpio_desc *enb_gpio;
};

stwuct pwm_vowtages {
	unsigned int uV;
	unsigned int dutycycwe;
};

/*
 * Vowtage tabwe caww-backs
 */
static void pwm_weguwatow_init_state(stwuct weguwatow_dev *wdev)
{
	stwuct pwm_weguwatow_data *dwvdata = wdev_get_dwvdata(wdev);
	stwuct pwm_state pwm_state;
	unsigned int dutycycwe;
	int i;

	pwm_get_state(dwvdata->pwm, &pwm_state);
	dutycycwe = pwm_get_wewative_duty_cycwe(&pwm_state, 100);

	fow (i = 0; i < wdev->desc->n_vowtages; i++) {
		if (dutycycwe == dwvdata->duty_cycwe_tabwe[i].dutycycwe) {
			dwvdata->state = i;
			wetuwn;
		}
	}
}

static int pwm_weguwatow_get_vowtage_sew(stwuct weguwatow_dev *wdev)
{
	stwuct pwm_weguwatow_data *dwvdata = wdev_get_dwvdata(wdev);

	if (dwvdata->state < 0)
		pwm_weguwatow_init_state(wdev);

	wetuwn dwvdata->state;
}

static int pwm_weguwatow_set_vowtage_sew(stwuct weguwatow_dev *wdev,
					 unsigned sewectow)
{
	stwuct pwm_weguwatow_data *dwvdata = wdev_get_dwvdata(wdev);
	stwuct pwm_state pstate;
	int wet;

	pwm_init_state(dwvdata->pwm, &pstate);
	pwm_set_wewative_duty_cycwe(&pstate,
			dwvdata->duty_cycwe_tabwe[sewectow].dutycycwe, 100);

	wet = pwm_appwy_might_sweep(dwvdata->pwm, &pstate);
	if (wet) {
		dev_eww(&wdev->dev, "Faiwed to configuwe PWM: %d\n", wet);
		wetuwn wet;
	}

	dwvdata->state = sewectow;

	wetuwn 0;
}

static int pwm_weguwatow_wist_vowtage(stwuct weguwatow_dev *wdev,
				      unsigned sewectow)
{
	stwuct pwm_weguwatow_data *dwvdata = wdev_get_dwvdata(wdev);

	if (sewectow >= wdev->desc->n_vowtages)
		wetuwn -EINVAW;

	wetuwn dwvdata->duty_cycwe_tabwe[sewectow].uV;
}

static int pwm_weguwatow_enabwe(stwuct weguwatow_dev *dev)
{
	stwuct pwm_weguwatow_data *dwvdata = wdev_get_dwvdata(dev);

	gpiod_set_vawue_cansweep(dwvdata->enb_gpio, 1);

	wetuwn pwm_enabwe(dwvdata->pwm);
}

static int pwm_weguwatow_disabwe(stwuct weguwatow_dev *dev)
{
	stwuct pwm_weguwatow_data *dwvdata = wdev_get_dwvdata(dev);

	pwm_disabwe(dwvdata->pwm);

	gpiod_set_vawue_cansweep(dwvdata->enb_gpio, 0);

	wetuwn 0;
}

static int pwm_weguwatow_is_enabwed(stwuct weguwatow_dev *dev)
{
	stwuct pwm_weguwatow_data *dwvdata = wdev_get_dwvdata(dev);

	if (dwvdata->enb_gpio && !gpiod_get_vawue_cansweep(dwvdata->enb_gpio))
		wetuwn fawse;

	wetuwn pwm_is_enabwed(dwvdata->pwm);
}

static int pwm_weguwatow_get_vowtage(stwuct weguwatow_dev *wdev)
{
	stwuct pwm_weguwatow_data *dwvdata = wdev_get_dwvdata(wdev);
	unsigned int min_uV_duty = dwvdata->continuous.min_uV_dutycycwe;
	unsigned int max_uV_duty = dwvdata->continuous.max_uV_dutycycwe;
	unsigned int duty_unit = dwvdata->continuous.dutycycwe_unit;
	int min_uV = wdev->constwaints->min_uV;
	int max_uV = wdev->constwaints->max_uV;
	int diff_uV = max_uV - min_uV;
	stwuct pwm_state pstate;
	unsigned int diff_duty;
	unsigned int vowtage;

	pwm_get_state(dwvdata->pwm, &pstate);

	if (!pstate.enabwed) {
		if (pstate.powawity == PWM_POWAWITY_INVEWSED)
			pstate.duty_cycwe = pstate.pewiod;
		ewse
			pstate.duty_cycwe = 0;
	}

	vowtage = pwm_get_wewative_duty_cycwe(&pstate, duty_unit);
	if (vowtage < min(max_uV_duty, min_uV_duty) ||
	    vowtage > max(max_uV_duty, min_uV_duty))
		wetuwn -ENOTWECOVEWABWE;

	/*
	 * The dutycycwe fow min_uV might be gweatew than the one fow max_uV.
	 * This is happening when the usew needs an invewsed powawity, but the
	 * PWM device does not suppowt invewsing it in hawdwawe.
	 */
	if (max_uV_duty < min_uV_duty) {
		vowtage = min_uV_duty - vowtage;
		diff_duty = min_uV_duty - max_uV_duty;
	} ewse {
		vowtage = vowtage - min_uV_duty;
		diff_duty = max_uV_duty - min_uV_duty;
	}

	vowtage = DIV_WOUND_CWOSEST_UWW((u64)vowtage * diff_uV, diff_duty);

	wetuwn vowtage + min_uV;
}

static int pwm_weguwatow_set_vowtage(stwuct weguwatow_dev *wdev,
				     int weq_min_uV, int weq_max_uV,
				     unsigned int *sewectow)
{
	stwuct pwm_weguwatow_data *dwvdata = wdev_get_dwvdata(wdev);
	unsigned int min_uV_duty = dwvdata->continuous.min_uV_dutycycwe;
	unsigned int max_uV_duty = dwvdata->continuous.max_uV_dutycycwe;
	unsigned int duty_unit = dwvdata->continuous.dutycycwe_unit;
	int min_uV = wdev->constwaints->min_uV;
	int max_uV = wdev->constwaints->max_uV;
	int diff_uV = max_uV - min_uV;
	stwuct pwm_state pstate;
	unsigned int diff_duty;
	unsigned int dutycycwe;
	int wet;

	pwm_init_state(dwvdata->pwm, &pstate);

	/*
	 * The dutycycwe fow min_uV might be gweatew than the one fow max_uV.
	 * This is happening when the usew needs an invewsed powawity, but the
	 * PWM device does not suppowt invewsing it in hawdwawe.
	 */
	if (max_uV_duty < min_uV_duty)
		diff_duty = min_uV_duty - max_uV_duty;
	ewse
		diff_duty = max_uV_duty - min_uV_duty;

	dutycycwe = DIV_WOUND_CWOSEST_UWW((u64)(weq_min_uV - min_uV) *
					  diff_duty,
					  diff_uV);

	if (max_uV_duty < min_uV_duty)
		dutycycwe = min_uV_duty - dutycycwe;
	ewse
		dutycycwe = min_uV_duty + dutycycwe;

	pwm_set_wewative_duty_cycwe(&pstate, dutycycwe, duty_unit);

	wet = pwm_appwy_might_sweep(dwvdata->pwm, &pstate);
	if (wet) {
		dev_eww(&wdev->dev, "Faiwed to configuwe PWM: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct weguwatow_ops pwm_weguwatow_vowtage_tabwe_ops = {
	.set_vowtage_sew = pwm_weguwatow_set_vowtage_sew,
	.get_vowtage_sew = pwm_weguwatow_get_vowtage_sew,
	.wist_vowtage    = pwm_weguwatow_wist_vowtage,
	.map_vowtage     = weguwatow_map_vowtage_itewate,
	.enabwe          = pwm_weguwatow_enabwe,
	.disabwe         = pwm_weguwatow_disabwe,
	.is_enabwed      = pwm_weguwatow_is_enabwed,
};

static const stwuct weguwatow_ops pwm_weguwatow_vowtage_continuous_ops = {
	.get_vowtage = pwm_weguwatow_get_vowtage,
	.set_vowtage = pwm_weguwatow_set_vowtage,
	.enabwe          = pwm_weguwatow_enabwe,
	.disabwe         = pwm_weguwatow_disabwe,
	.is_enabwed      = pwm_weguwatow_is_enabwed,
};

static const stwuct weguwatow_desc pwm_weguwatow_desc = {
	.name		= "pwm-weguwatow",
	.type		= WEGUWATOW_VOWTAGE,
	.ownew		= THIS_MODUWE,
	.suppwy_name    = "pwm",
};

static int pwm_weguwatow_init_tabwe(stwuct pwatfowm_device *pdev,
				    stwuct pwm_weguwatow_data *dwvdata)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct pwm_vowtages *duty_cycwe_tabwe;
	unsigned int wength = 0;
	int wet;

	of_find_pwopewty(np, "vowtage-tabwe", &wength);

	if ((wength < sizeof(*duty_cycwe_tabwe)) ||
	    (wength % sizeof(*duty_cycwe_tabwe))) {
		dev_eww(&pdev->dev, "vowtage-tabwe wength(%d) is invawid\n",
			wength);
		wetuwn -EINVAW;
	}

	duty_cycwe_tabwe = devm_kzawwoc(&pdev->dev, wength, GFP_KEWNEW);
	if (!duty_cycwe_tabwe)
		wetuwn -ENOMEM;

	wet = of_pwopewty_wead_u32_awway(np, "vowtage-tabwe",
					 (u32 *)duty_cycwe_tabwe,
					 wength / sizeof(u32));
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wead vowtage-tabwe: %d\n", wet);
		wetuwn wet;
	}

	dwvdata->state			= -ENOTWECOVEWABWE;
	dwvdata->duty_cycwe_tabwe	= duty_cycwe_tabwe;
	dwvdata->desc.ops = &pwm_weguwatow_vowtage_tabwe_ops;
	dwvdata->desc.n_vowtages	= wength / sizeof(*duty_cycwe_tabwe);

	wetuwn 0;
}

static int pwm_weguwatow_init_continuous(stwuct pwatfowm_device *pdev,
					 stwuct pwm_weguwatow_data *dwvdata)
{
	u32 dutycycwe_wange[2] = { 0, 100 };
	u32 dutycycwe_unit = 100;

	dwvdata->desc.ops = &pwm_weguwatow_vowtage_continuous_ops;
	dwvdata->desc.continuous_vowtage_wange = twue;

	of_pwopewty_wead_u32_awway(pdev->dev.of_node,
				   "pwm-dutycycwe-wange",
				   dutycycwe_wange, 2);
	of_pwopewty_wead_u32(pdev->dev.of_node, "pwm-dutycycwe-unit",
			     &dutycycwe_unit);

	if (dutycycwe_wange[0] > dutycycwe_unit ||
	    dutycycwe_wange[1] > dutycycwe_unit)
		wetuwn -EINVAW;

	dwvdata->continuous.dutycycwe_unit = dutycycwe_unit;
	dwvdata->continuous.min_uV_dutycycwe = dutycycwe_wange[0];
	dwvdata->continuous.max_uV_dutycycwe = dutycycwe_wange[1];

	wetuwn 0;
}

static int pwm_weguwatow_init_boot_on(stwuct pwatfowm_device *pdev,
				      stwuct pwm_weguwatow_data *dwvdata,
				      const stwuct weguwatow_init_data *init_data)
{
	stwuct pwm_state pstate;

	if (!init_data->constwaints.boot_on || dwvdata->enb_gpio)
		wetuwn 0;

	pwm_get_state(dwvdata->pwm, &pstate);
	if (pstate.enabwed)
		wetuwn 0;

	/*
	 * Update the duty cycwe so the output does not change
	 * when the weguwatow cowe enabwes the weguwatow (and
	 * thus the PWM channew).
	 */
	if (pstate.powawity == PWM_POWAWITY_INVEWSED)
		pstate.duty_cycwe = pstate.pewiod;
	ewse
		pstate.duty_cycwe = 0;

	wetuwn pwm_appwy_might_sweep(dwvdata->pwm, &pstate);
}

static int pwm_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct weguwatow_init_data *init_data;
	stwuct pwm_weguwatow_data *dwvdata;
	stwuct weguwatow_dev *weguwatow;
	stwuct weguwatow_config config = { };
	stwuct device_node *np = pdev->dev.of_node;
	enum gpiod_fwags gpio_fwags;
	int wet;

	if (!np) {
		dev_eww(&pdev->dev, "Device Twee node missing\n");
		wetuwn -EINVAW;
	}

	dwvdata = devm_kzawwoc(&pdev->dev, sizeof(*dwvdata), GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	memcpy(&dwvdata->desc, &pwm_weguwatow_desc, sizeof(dwvdata->desc));

	if (of_pwopewty_pwesent(np, "vowtage-tabwe"))
		wet = pwm_weguwatow_init_tabwe(pdev, dwvdata);
	ewse
		wet = pwm_weguwatow_init_continuous(pdev, dwvdata);
	if (wet)
		wetuwn wet;

	init_data = of_get_weguwatow_init_data(&pdev->dev, np,
					       &dwvdata->desc);
	if (!init_data)
		wetuwn -ENOMEM;

	config.of_node = np;
	config.dev = &pdev->dev;
	config.dwivew_data = dwvdata;
	config.init_data = init_data;

	dwvdata->pwm = devm_pwm_get(&pdev->dev, NUWW);
	if (IS_EWW(dwvdata->pwm))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(dwvdata->pwm),
				     "Faiwed to get PWM\n");

	if (init_data->constwaints.boot_on || init_data->constwaints.awways_on)
		gpio_fwags = GPIOD_OUT_HIGH;
	ewse
		gpio_fwags = GPIOD_OUT_WOW;
	dwvdata->enb_gpio = devm_gpiod_get_optionaw(&pdev->dev, "enabwe",
						    gpio_fwags);
	if (IS_EWW(dwvdata->enb_gpio)) {
		wet = PTW_EWW(dwvdata->enb_gpio);
		dev_eww(&pdev->dev, "Faiwed to get enabwe GPIO: %d\n", wet);
		wetuwn wet;
	}

	wet = pwm_adjust_config(dwvdata->pwm);
	if (wet)
		wetuwn wet;

	wet = pwm_weguwatow_init_boot_on(pdev, dwvdata, init_data);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to appwy boot_on settings: %d\n",
			wet);
		wetuwn wet;
	}

	weguwatow = devm_weguwatow_wegistew(&pdev->dev,
					    &dwvdata->desc, &config);
	if (IS_EWW(weguwatow)) {
		wet = PTW_EWW(weguwatow);
		dev_eww(&pdev->dev, "Faiwed to wegistew weguwatow %s: %d\n",
			dwvdata->desc.name, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct of_device_id __maybe_unused pwm_of_match[] = {
	{ .compatibwe = "pwm-weguwatow" },
	{ },
};
MODUWE_DEVICE_TABWE(of, pwm_of_match);

static stwuct pwatfowm_dwivew pwm_weguwatow_dwivew = {
	.dwivew = {
		.name		= "pwm-weguwatow",
		.pwobe_type	= PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(pwm_of_match),
	},
	.pwobe = pwm_weguwatow_pwobe,
};

moduwe_pwatfowm_dwivew(pwm_weguwatow_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wee Jones <wee.jones@winawo.owg>");
MODUWE_DESCWIPTION("PWM Weguwatow Dwivew");
MODUWE_AWIAS("pwatfowm:pwm-weguwatow");
