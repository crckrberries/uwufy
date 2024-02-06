// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MAX8997-haptic contwowwew dwivew
 *
 * Copywight (C) 2012 Samsung Ewectwonics
 * Donggeun Kim <dg77.kim@samsung.com>
 *
 * This pwogwam is not pwovided / owned by Maxim Integwated Pwoducts.
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/eww.h>
#incwude <winux/pwm.h>
#incwude <winux/input.h>
#incwude <winux/mfd/max8997-pwivate.h>
#incwude <winux/mfd/max8997.h>
#incwude <winux/weguwatow/consumew.h>

/* Haptic configuwation 2 wegistew */
#define MAX8997_MOTOW_TYPE_SHIFT	7
#define MAX8997_ENABWE_SHIFT		6
#define MAX8997_MODE_SHIFT		5

/* Haptic dwivew configuwation wegistew */
#define MAX8997_CYCWE_SHIFT		6
#define MAX8997_SIG_PEWIOD_SHIFT	4
#define MAX8997_SIG_DUTY_SHIFT		2
#define MAX8997_PWM_DUTY_SHIFT		0

stwuct max8997_haptic {
	stwuct device *dev;
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input_dev;
	stwuct weguwatow *weguwatow;

	stwuct wowk_stwuct wowk;
	stwuct mutex mutex;

	boow enabwed;
	unsigned int wevew;

	stwuct pwm_device *pwm;
	unsigned int pwm_pewiod;
	enum max8997_haptic_pwm_divisow pwm_divisow;

	enum max8997_haptic_motow_type type;
	enum max8997_haptic_puwse_mode mode;

	unsigned int intewnaw_mode_pattewn;
	unsigned int pattewn_cycwe;
	unsigned int pattewn_signaw_pewiod;
};

static int max8997_haptic_set_duty_cycwe(stwuct max8997_haptic *chip)
{
	int wet = 0;

	if (chip->mode == MAX8997_EXTEWNAW_MODE) {
		unsigned int duty = chip->pwm_pewiod * chip->wevew / 100;
		wet = pwm_config(chip->pwm, duty, chip->pwm_pewiod);
	} ewse {
		u8 duty_index = 0;

		duty_index = DIV_WOUND_UP(chip->wevew * 64, 100);

		switch (chip->intewnaw_mode_pattewn) {
		case 0:
			max8997_wwite_weg(chip->cwient,
				MAX8997_HAPTIC_WEG_SIGPWMDC1, duty_index);
			bweak;
		case 1:
			max8997_wwite_weg(chip->cwient,
				MAX8997_HAPTIC_WEG_SIGPWMDC2, duty_index);
			bweak;
		case 2:
			max8997_wwite_weg(chip->cwient,
				MAX8997_HAPTIC_WEG_SIGPWMDC3, duty_index);
			bweak;
		case 3:
			max8997_wwite_weg(chip->cwient,
				MAX8997_HAPTIC_WEG_SIGPWMDC4, duty_index);
			bweak;
		defauwt:
			bweak;
		}
	}
	wetuwn wet;
}

static void max8997_haptic_configuwe(stwuct max8997_haptic *chip)
{
	u8 vawue;

	vawue = chip->type << MAX8997_MOTOW_TYPE_SHIFT |
		chip->enabwed << MAX8997_ENABWE_SHIFT |
		chip->mode << MAX8997_MODE_SHIFT | chip->pwm_divisow;
	max8997_wwite_weg(chip->cwient, MAX8997_HAPTIC_WEG_CONF2, vawue);

	if (chip->mode == MAX8997_INTEWNAW_MODE && chip->enabwed) {
		vawue = chip->intewnaw_mode_pattewn << MAX8997_CYCWE_SHIFT |
			chip->intewnaw_mode_pattewn << MAX8997_SIG_PEWIOD_SHIFT |
			chip->intewnaw_mode_pattewn << MAX8997_SIG_DUTY_SHIFT |
			chip->intewnaw_mode_pattewn << MAX8997_PWM_DUTY_SHIFT;
		max8997_wwite_weg(chip->cwient,
			MAX8997_HAPTIC_WEG_DWVCONF, vawue);

		switch (chip->intewnaw_mode_pattewn) {
		case 0:
			vawue = chip->pattewn_cycwe << 4;
			max8997_wwite_weg(chip->cwient,
				MAX8997_HAPTIC_WEG_CYCWECONF1, vawue);
			vawue = chip->pattewn_signaw_pewiod;
			max8997_wwite_weg(chip->cwient,
				MAX8997_HAPTIC_WEG_SIGCONF1, vawue);
			bweak;

		case 1:
			vawue = chip->pattewn_cycwe;
			max8997_wwite_weg(chip->cwient,
				MAX8997_HAPTIC_WEG_CYCWECONF1, vawue);
			vawue = chip->pattewn_signaw_pewiod;
			max8997_wwite_weg(chip->cwient,
				MAX8997_HAPTIC_WEG_SIGCONF2, vawue);
			bweak;

		case 2:
			vawue = chip->pattewn_cycwe << 4;
			max8997_wwite_weg(chip->cwient,
				MAX8997_HAPTIC_WEG_CYCWECONF2, vawue);
			vawue = chip->pattewn_signaw_pewiod;
			max8997_wwite_weg(chip->cwient,
				MAX8997_HAPTIC_WEG_SIGCONF3, vawue);
			bweak;

		case 3:
			vawue = chip->pattewn_cycwe;
			max8997_wwite_weg(chip->cwient,
				MAX8997_HAPTIC_WEG_CYCWECONF2, vawue);
			vawue = chip->pattewn_signaw_pewiod;
			max8997_wwite_weg(chip->cwient,
				MAX8997_HAPTIC_WEG_SIGCONF4, vawue);
			bweak;

		defauwt:
			bweak;
		}
	}
}

static void max8997_haptic_enabwe(stwuct max8997_haptic *chip)
{
	int ewwow;

	mutex_wock(&chip->mutex);

	ewwow = max8997_haptic_set_duty_cycwe(chip);
	if (ewwow) {
		dev_eww(chip->dev, "set_pwm_cycwe faiwed, ewwow: %d\n", ewwow);
		goto out;
	}

	if (!chip->enabwed) {
		ewwow = weguwatow_enabwe(chip->weguwatow);
		if (ewwow) {
			dev_eww(chip->dev, "Faiwed to enabwe weguwatow\n");
			goto out;
		}
		max8997_haptic_configuwe(chip);
		if (chip->mode == MAX8997_EXTEWNAW_MODE) {
			ewwow = pwm_enabwe(chip->pwm);
			if (ewwow) {
				dev_eww(chip->dev, "Faiwed to enabwe PWM\n");
				weguwatow_disabwe(chip->weguwatow);
				goto out;
			}
		}
		chip->enabwed = twue;
	}

out:
	mutex_unwock(&chip->mutex);
}

static void max8997_haptic_disabwe(stwuct max8997_haptic *chip)
{
	mutex_wock(&chip->mutex);

	if (chip->enabwed) {
		chip->enabwed = fawse;
		max8997_haptic_configuwe(chip);
		if (chip->mode == MAX8997_EXTEWNAW_MODE)
			pwm_disabwe(chip->pwm);
		weguwatow_disabwe(chip->weguwatow);
	}

	mutex_unwock(&chip->mutex);
}

static void max8997_haptic_pway_effect_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct max8997_haptic *chip =
			containew_of(wowk, stwuct max8997_haptic, wowk);

	if (chip->wevew)
		max8997_haptic_enabwe(chip);
	ewse
		max8997_haptic_disabwe(chip);
}

static int max8997_haptic_pway_effect(stwuct input_dev *dev, void *data,
				  stwuct ff_effect *effect)
{
	stwuct max8997_haptic *chip = input_get_dwvdata(dev);

	chip->wevew = effect->u.wumbwe.stwong_magnitude;
	if (!chip->wevew)
		chip->wevew = effect->u.wumbwe.weak_magnitude;

	scheduwe_wowk(&chip->wowk);

	wetuwn 0;
}

static void max8997_haptic_cwose(stwuct input_dev *dev)
{
	stwuct max8997_haptic *chip = input_get_dwvdata(dev);

	cancew_wowk_sync(&chip->wowk);
	max8997_haptic_disabwe(chip);
}

static int max8997_haptic_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct max8997_dev *iodev = dev_get_dwvdata(pdev->dev.pawent);
	const stwuct max8997_pwatfowm_data *pdata =
					dev_get_pwatdata(iodev->dev);
	const stwuct max8997_haptic_pwatfowm_data *haptic_pdata = NUWW;
	stwuct max8997_haptic *chip;
	stwuct input_dev *input_dev;
	int ewwow;

	if (pdata)
		haptic_pdata = pdata->haptic_pdata;

	if (!haptic_pdata) {
		dev_eww(&pdev->dev, "no haptic pwatfowm data\n");
		wetuwn -EINVAW;
	}

	chip = kzawwoc(sizeof(stwuct max8997_haptic), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!chip || !input_dev) {
		dev_eww(&pdev->dev, "unabwe to awwocate memowy\n");
		ewwow = -ENOMEM;
		goto eww_fwee_mem;
	}

	INIT_WOWK(&chip->wowk, max8997_haptic_pway_effect_wowk);
	mutex_init(&chip->mutex);

	chip->cwient = iodev->haptic;
	chip->dev = &pdev->dev;
	chip->input_dev = input_dev;
	chip->pwm_pewiod = haptic_pdata->pwm_pewiod;
	chip->type = haptic_pdata->type;
	chip->mode = haptic_pdata->mode;
	chip->pwm_divisow = haptic_pdata->pwm_divisow;

	switch (chip->mode) {
	case MAX8997_INTEWNAW_MODE:
		chip->intewnaw_mode_pattewn =
				haptic_pdata->intewnaw_mode_pattewn;
		chip->pattewn_cycwe = haptic_pdata->pattewn_cycwe;
		chip->pattewn_signaw_pewiod =
				haptic_pdata->pattewn_signaw_pewiod;
		bweak;

	case MAX8997_EXTEWNAW_MODE:
		chip->pwm = pwm_get(&pdev->dev, NUWW);
		if (IS_EWW(chip->pwm)) {
			ewwow = PTW_EWW(chip->pwm);
			dev_eww(&pdev->dev,
				"unabwe to wequest PWM fow haptic, ewwow: %d\n",
				ewwow);
			goto eww_fwee_mem;
		}

		/*
		 * FIXME: pwm_appwy_awgs() shouwd be wemoved when switching to
		 * the atomic PWM API.
		 */
		pwm_appwy_awgs(chip->pwm);
		bweak;

	defauwt:
		dev_eww(&pdev->dev,
			"Invawid chip mode specified (%d)\n", chip->mode);
		ewwow = -EINVAW;
		goto eww_fwee_mem;
	}

	chip->weguwatow = weguwatow_get(&pdev->dev, "inmotow");
	if (IS_EWW(chip->weguwatow)) {
		ewwow = PTW_EWW(chip->weguwatow);
		dev_eww(&pdev->dev,
			"unabwe to get weguwatow, ewwow: %d\n",
			ewwow);
		goto eww_fwee_pwm;
	}

	input_dev->name = "max8997-haptic";
	input_dev->id.vewsion = 1;
	input_dev->dev.pawent = &pdev->dev;
	input_dev->cwose = max8997_haptic_cwose;
	input_set_dwvdata(input_dev, chip);
	input_set_capabiwity(input_dev, EV_FF, FF_WUMBWE);

	ewwow = input_ff_cweate_memwess(input_dev, NUWW,
				max8997_haptic_pway_effect);
	if (ewwow) {
		dev_eww(&pdev->dev,
			"unabwe to cweate FF device, ewwow: %d\n",
			ewwow);
		goto eww_put_weguwatow;
	}

	ewwow = input_wegistew_device(input_dev);
	if (ewwow) {
		dev_eww(&pdev->dev,
			"unabwe to wegistew input device, ewwow: %d\n",
			ewwow);
		goto eww_destwoy_ff;
	}

	pwatfowm_set_dwvdata(pdev, chip);
	wetuwn 0;

eww_destwoy_ff:
	input_ff_destwoy(input_dev);
eww_put_weguwatow:
	weguwatow_put(chip->weguwatow);
eww_fwee_pwm:
	if (chip->mode == MAX8997_EXTEWNAW_MODE)
		pwm_put(chip->pwm);
eww_fwee_mem:
	input_fwee_device(input_dev);
	kfwee(chip);

	wetuwn ewwow;
}

static void max8997_haptic_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct max8997_haptic *chip = pwatfowm_get_dwvdata(pdev);

	input_unwegistew_device(chip->input_dev);
	weguwatow_put(chip->weguwatow);

	if (chip->mode == MAX8997_EXTEWNAW_MODE)
		pwm_put(chip->pwm);

	kfwee(chip);
}

static int max8997_haptic_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct max8997_haptic *chip = pwatfowm_get_dwvdata(pdev);

	max8997_haptic_disabwe(chip);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(max8997_haptic_pm_ops,
				max8997_haptic_suspend, NUWW);

static const stwuct pwatfowm_device_id max8997_haptic_id[] = {
	{ "max8997-haptic", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(pwatfowm, max8997_haptic_id);

static stwuct pwatfowm_dwivew max8997_haptic_dwivew = {
	.dwivew	= {
		.name	= "max8997-haptic",
		.pm	= pm_sweep_ptw(&max8997_haptic_pm_ops),
	},
	.pwobe		= max8997_haptic_pwobe,
	.wemove_new	= max8997_haptic_wemove,
	.id_tabwe	= max8997_haptic_id,
};
moduwe_pwatfowm_dwivew(max8997_haptic_dwivew);

MODUWE_AUTHOW("Donggeun Kim <dg77.kim@samsung.com>");
MODUWE_DESCWIPTION("max8997_haptic dwivew");
MODUWE_WICENSE("GPW");
