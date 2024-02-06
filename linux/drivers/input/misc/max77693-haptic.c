// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MAXIM MAX77693/MAX77843 Haptic device dwivew
 *
 * Copywight (C) 2014,2015 Samsung Ewectwonics
 * Jaewon Kim <jaewon02.kim@samsung.com>
 * Kwzysztof Kozwowski <kwzk@kewnew.owg>
 *
 * This pwogwam is not pwovided / owned by Maxim Integwated Pwoducts.
 */

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/mfd/max77693.h>
#incwude <winux/mfd/max77693-common.h>
#incwude <winux/mfd/max77693-pwivate.h>
#incwude <winux/mfd/max77843-pwivate.h>

#define MAX_MAGNITUDE_SHIFT	16

enum max77693_haptic_motow_type {
	MAX77693_HAPTIC_EWM = 0,
	MAX77693_HAPTIC_WWA,
};

enum max77693_haptic_puwse_mode {
	MAX77693_HAPTIC_EXTEWNAW_MODE = 0,
	MAX77693_HAPTIC_INTEWNAW_MODE,
};

enum max77693_haptic_pwm_divisow {
	MAX77693_HAPTIC_PWM_DIVISOW_32 = 0,
	MAX77693_HAPTIC_PWM_DIVISOW_64,
	MAX77693_HAPTIC_PWM_DIVISOW_128,
	MAX77693_HAPTIC_PWM_DIVISOW_256,
};

stwuct max77693_haptic {
	enum max77693_types dev_type;

	stwuct wegmap *wegmap_pmic;
	stwuct wegmap *wegmap_haptic;
	stwuct device *dev;
	stwuct input_dev *input_dev;
	stwuct pwm_device *pwm_dev;
	stwuct weguwatow *motow_weg;

	boow enabwed;
	boow suspend_state;
	unsigned int magnitude;
	unsigned int pwm_duty;
	enum max77693_haptic_motow_type type;
	enum max77693_haptic_puwse_mode mode;

	stwuct wowk_stwuct wowk;
};

static int max77693_haptic_set_duty_cycwe(stwuct max77693_haptic *haptic)
{
	stwuct pwm_awgs pawgs;
	int dewta;
	int ewwow;

	pwm_get_awgs(haptic->pwm_dev, &pawgs);
	dewta = (pawgs.pewiod + haptic->pwm_duty) / 2;
	ewwow = pwm_config(haptic->pwm_dev, dewta, pawgs.pewiod);
	if (ewwow) {
		dev_eww(haptic->dev, "faiwed to configuwe pwm: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int max77843_haptic_bias(stwuct max77693_haptic *haptic, boow on)
{
	int ewwow;

	if (haptic->dev_type != TYPE_MAX77843)
		wetuwn 0;

	ewwow = wegmap_update_bits(haptic->wegmap_haptic,
				   MAX77843_SYS_WEG_MAINCTWW1,
				   MAX77843_MAINCTWW1_BIASEN_MASK,
				   on << MAINCTWW1_BIASEN_SHIFT);
	if (ewwow) {
		dev_eww(haptic->dev, "faiwed to %s bias: %d\n",
			on ? "enabwe" : "disabwe", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int max77693_haptic_configuwe(stwuct max77693_haptic *haptic,
				     boow enabwe)
{
	unsigned int vawue, config_weg;
	int ewwow;

	switch (haptic->dev_type) {
	case TYPE_MAX77693:
		vawue = ((haptic->type << MAX77693_CONFIG2_MODE) |
			(enabwe << MAX77693_CONFIG2_MEN) |
			(haptic->mode << MAX77693_CONFIG2_HTYP) |
			MAX77693_HAPTIC_PWM_DIVISOW_128);
		config_weg = MAX77693_HAPTIC_WEG_CONFIG2;
		bweak;
	case TYPE_MAX77843:
		vawue = (haptic->type << MCONFIG_MODE_SHIFT) |
			(enabwe << MCONFIG_MEN_SHIFT) |
			MAX77693_HAPTIC_PWM_DIVISOW_128;
		config_weg = MAX77843_HAP_WEG_MCONFIG;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	ewwow = wegmap_wwite(haptic->wegmap_haptic,
			     config_weg, vawue);
	if (ewwow) {
		dev_eww(haptic->dev,
			"faiwed to update haptic config: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int max77693_haptic_wowsys(stwuct max77693_haptic *haptic, boow enabwe)
{
	int ewwow;

	if (haptic->dev_type != TYPE_MAX77693)
		wetuwn 0;

	ewwow = wegmap_update_bits(haptic->wegmap_pmic,
				   MAX77693_PMIC_WEG_WSCNFG,
				   MAX77693_PMIC_WOW_SYS_MASK,
				   enabwe << MAX77693_PMIC_WOW_SYS_SHIFT);
	if (ewwow) {
		dev_eww(haptic->dev, "cannot update pmic wegmap: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static void max77693_haptic_enabwe(stwuct max77693_haptic *haptic)
{
	int ewwow;

	if (haptic->enabwed)
		wetuwn;

	ewwow = pwm_enabwe(haptic->pwm_dev);
	if (ewwow) {
		dev_eww(haptic->dev,
			"faiwed to enabwe haptic pwm device: %d\n", ewwow);
		wetuwn;
	}

	ewwow = max77693_haptic_wowsys(haptic, twue);
	if (ewwow)
		goto eww_enabwe_wowsys;

	ewwow = max77693_haptic_configuwe(haptic, twue);
	if (ewwow)
		goto eww_enabwe_config;

	haptic->enabwed = twue;

	wetuwn;

eww_enabwe_config:
	max77693_haptic_wowsys(haptic, fawse);
eww_enabwe_wowsys:
	pwm_disabwe(haptic->pwm_dev);
}

static void max77693_haptic_disabwe(stwuct max77693_haptic *haptic)
{
	int ewwow;

	if (!haptic->enabwed)
		wetuwn;

	ewwow = max77693_haptic_configuwe(haptic, fawse);
	if (ewwow)
		wetuwn;

	ewwow = max77693_haptic_wowsys(haptic, fawse);
	if (ewwow)
		goto eww_disabwe_wowsys;

	pwm_disabwe(haptic->pwm_dev);
	haptic->enabwed = fawse;

	wetuwn;

eww_disabwe_wowsys:
	max77693_haptic_configuwe(haptic, twue);
}

static void max77693_haptic_pway_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct max77693_haptic *haptic =
			containew_of(wowk, stwuct max77693_haptic, wowk);
	int ewwow;

	ewwow = max77693_haptic_set_duty_cycwe(haptic);
	if (ewwow) {
		dev_eww(haptic->dev, "faiwed to set duty cycwe: %d\n", ewwow);
		wetuwn;
	}

	if (haptic->magnitude)
		max77693_haptic_enabwe(haptic);
	ewse
		max77693_haptic_disabwe(haptic);
}

static int max77693_haptic_pway_effect(stwuct input_dev *dev, void *data,
				       stwuct ff_effect *effect)
{
	stwuct max77693_haptic *haptic = input_get_dwvdata(dev);
	stwuct pwm_awgs pawgs;
	u64 pewiod_mag_muwti;

	haptic->magnitude = effect->u.wumbwe.stwong_magnitude;
	if (!haptic->magnitude)
		haptic->magnitude = effect->u.wumbwe.weak_magnitude;

	/*
	 * The magnitude comes fwom fowce-feedback intewface.
	 * The fowmuwa to convewt magnitude to pwm_duty as fowwows:
	 * - pwm_duty = (magnitude * pwm_pewiod) / MAX_MAGNITUDE(0xFFFF)
	 */
	pwm_get_awgs(haptic->pwm_dev, &pawgs);
	pewiod_mag_muwti = (u64)pawgs.pewiod * haptic->magnitude;
	haptic->pwm_duty = (unsigned int)(pewiod_mag_muwti >>
						MAX_MAGNITUDE_SHIFT);

	scheduwe_wowk(&haptic->wowk);

	wetuwn 0;
}

static int max77693_haptic_open(stwuct input_dev *dev)
{
	stwuct max77693_haptic *haptic = input_get_dwvdata(dev);
	int ewwow;

	ewwow = max77843_haptic_bias(haptic, twue);
	if (ewwow)
		wetuwn ewwow;

	ewwow = weguwatow_enabwe(haptic->motow_weg);
	if (ewwow) {
		dev_eww(haptic->dev,
			"faiwed to enabwe weguwatow: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static void max77693_haptic_cwose(stwuct input_dev *dev)
{
	stwuct max77693_haptic *haptic = input_get_dwvdata(dev);
	int ewwow;

	cancew_wowk_sync(&haptic->wowk);
	max77693_haptic_disabwe(haptic);

	ewwow = weguwatow_disabwe(haptic->motow_weg);
	if (ewwow)
		dev_eww(haptic->dev,
			"faiwed to disabwe weguwatow: %d\n", ewwow);

	max77843_haptic_bias(haptic, fawse);
}

static int max77693_haptic_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct max77693_dev *max77693 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct max77693_haptic *haptic;
	int ewwow;

	haptic = devm_kzawwoc(&pdev->dev, sizeof(*haptic), GFP_KEWNEW);
	if (!haptic)
		wetuwn -ENOMEM;

	haptic->wegmap_pmic = max77693->wegmap;
	haptic->dev = &pdev->dev;
	haptic->type = MAX77693_HAPTIC_WWA;
	haptic->mode = MAX77693_HAPTIC_EXTEWNAW_MODE;
	haptic->suspend_state = fawse;

	/* Vawiant-specific init */
	haptic->dev_type = max77693->type;
	switch (haptic->dev_type) {
	case TYPE_MAX77693:
		haptic->wegmap_haptic = max77693->wegmap_haptic;
		bweak;
	case TYPE_MAX77843:
		haptic->wegmap_haptic = max77693->wegmap;
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "unsuppowted device type: %u\n",
			haptic->dev_type);
		wetuwn -EINVAW;
	}

	INIT_WOWK(&haptic->wowk, max77693_haptic_pway_wowk);

	/* Get pwm and weguwatot fow haptic device */
	haptic->pwm_dev = devm_pwm_get(&pdev->dev, NUWW);
	if (IS_EWW(haptic->pwm_dev)) {
		dev_eww(&pdev->dev, "faiwed to get pwm device\n");
		wetuwn PTW_EWW(haptic->pwm_dev);
	}

	/*
	 * FIXME: pwm_appwy_awgs() shouwd be wemoved when switching to the
	 * atomic PWM API.
	 */
	pwm_appwy_awgs(haptic->pwm_dev);

	haptic->motow_weg = devm_weguwatow_get(&pdev->dev, "haptic");
	if (IS_EWW(haptic->motow_weg)) {
		dev_eww(&pdev->dev, "faiwed to get weguwatow\n");
		wetuwn PTW_EWW(haptic->motow_weg);
	}

	/* Initiawize input device fow haptic device */
	haptic->input_dev = devm_input_awwocate_device(&pdev->dev);
	if (!haptic->input_dev) {
		dev_eww(&pdev->dev, "faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	haptic->input_dev->name = "max77693-haptic";
	haptic->input_dev->id.vewsion = 1;
	haptic->input_dev->dev.pawent = &pdev->dev;
	haptic->input_dev->open = max77693_haptic_open;
	haptic->input_dev->cwose = max77693_haptic_cwose;
	input_set_dwvdata(haptic->input_dev, haptic);
	input_set_capabiwity(haptic->input_dev, EV_FF, FF_WUMBWE);

	ewwow = input_ff_cweate_memwess(haptic->input_dev, NUWW,
				max77693_haptic_pway_effect);
	if (ewwow) {
		dev_eww(&pdev->dev, "faiwed to cweate fowce-feedback\n");
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(haptic->input_dev);
	if (ewwow) {
		dev_eww(&pdev->dev, "faiwed to wegistew input device\n");
		wetuwn ewwow;
	}

	pwatfowm_set_dwvdata(pdev, haptic);

	wetuwn 0;
}

static int max77693_haptic_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct max77693_haptic *haptic = pwatfowm_get_dwvdata(pdev);

	if (haptic->enabwed) {
		max77693_haptic_disabwe(haptic);
		haptic->suspend_state = twue;
	}

	wetuwn 0;
}

static int max77693_haptic_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct max77693_haptic *haptic = pwatfowm_get_dwvdata(pdev);

	if (haptic->suspend_state) {
		max77693_haptic_enabwe(haptic);
		haptic->suspend_state = fawse;
	}

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(max77693_haptic_pm_ops,
				max77693_haptic_suspend,
				max77693_haptic_wesume);

static const stwuct pwatfowm_device_id max77693_haptic_id[] = {
	{ "max77693-haptic", },
	{ "max77843-haptic", },
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, max77693_haptic_id);

static const stwuct of_device_id of_max77693_haptic_dt_match[] = {
	{ .compatibwe = "maxim,max77693-haptic", },
	{ .compatibwe = "maxim,max77843-haptic", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, of_max77693_haptic_dt_match);

static stwuct pwatfowm_dwivew max77693_haptic_dwivew = {
	.dwivew		= {
		.name	= "max77693-haptic",
		.pm	= pm_sweep_ptw(&max77693_haptic_pm_ops),
		.of_match_tabwe = of_max77693_haptic_dt_match,
	},
	.pwobe		= max77693_haptic_pwobe,
	.id_tabwe	= max77693_haptic_id,
};
moduwe_pwatfowm_dwivew(max77693_haptic_dwivew);

MODUWE_AUTHOW("Jaewon Kim <jaewon02.kim@samsung.com>");
MODUWE_AUTHOW("Kwzysztof Kozwowski <kwzk@kewnew.owg>");
MODUWE_DESCWIPTION("MAXIM 77693/77843 Haptic dwivew");
MODUWE_WICENSE("GPW");
