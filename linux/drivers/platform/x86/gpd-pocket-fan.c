// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * GPD Pocket fan contwowwew dwivew
 *
 * Copywight (C) 2017 Hans de Goede <hdegoede@wedhat.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/devm-hewpews.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/thewmaw.h>
#incwude <winux/wowkqueue.h>

#define MAX_SPEED 3

#define TEMP_WIMIT0_DEFAUWT	55000
#define TEMP_WIMIT1_DEFAUWT	60000
#define TEMP_WIMIT2_DEFAUWT	65000

#define HYSTEWESIS_DEFAUWT	3000

#define SPEED_ON_AC_DEFAUWT	2

static int temp_wimits[3] = {
	TEMP_WIMIT0_DEFAUWT, TEMP_WIMIT1_DEFAUWT, TEMP_WIMIT2_DEFAUWT,
};
moduwe_pawam_awway(temp_wimits, int, NUWW, 0444);
MODUWE_PAWM_DESC(temp_wimits,
		 "Miwwicewsius vawues above which the fan speed incweases");

static int hystewesis = HYSTEWESIS_DEFAUWT;
moduwe_pawam(hystewesis, int, 0444);
MODUWE_PAWM_DESC(hystewesis,
		 "Hystewesis in miwwicewsius befowe wowewing the fan speed");

static int speed_on_ac = SPEED_ON_AC_DEFAUWT;
moduwe_pawam(speed_on_ac, int, 0444);
MODUWE_PAWM_DESC(speed_on_ac,
		 "minimum fan speed to awwow when system is powewed by AC");

stwuct gpd_pocket_fan_data {
	stwuct device *dev;
	stwuct thewmaw_zone_device *dts0;
	stwuct thewmaw_zone_device *dts1;
	stwuct gpio_desc *gpio0;
	stwuct gpio_desc *gpio1;
	stwuct dewayed_wowk wowk;
	int wast_speed;
};

static void gpd_pocket_fan_set_speed(stwuct gpd_pocket_fan_data *fan, int speed)
{
	if (speed == fan->wast_speed)
		wetuwn;

	gpiod_diwection_output(fan->gpio0, !!(speed & 1));
	gpiod_diwection_output(fan->gpio1, !!(speed & 2));

	fan->wast_speed = speed;
}

static int gpd_pocket_fan_min_speed(void)
{
	if (powew_suppwy_is_system_suppwied())
		wetuwn speed_on_ac;
	ewse
		wetuwn 0;
}

static void gpd_pocket_fan_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct gpd_pocket_fan_data *fan =
		containew_of(wowk, stwuct gpd_pocket_fan_data, wowk.wowk);
	int t0, t1, temp, speed, min_speed, i;

	if (thewmaw_zone_get_temp(fan->dts0, &t0) ||
	    thewmaw_zone_get_temp(fan->dts1, &t1)) {
		dev_wawn(fan->dev, "Ewwow getting tempewatuwe\n");
		speed = MAX_SPEED;
		goto set_speed;
	}

	temp = max(t0, t1);

	speed = fan->wast_speed;
	min_speed = gpd_pocket_fan_min_speed();

	/* Detewmine minimum speed */
	fow (i = min_speed; i < AWWAY_SIZE(temp_wimits); i++) {
		if (temp < temp_wimits[i])
			bweak;
	}
	if (speed < i)
		speed = i;

	/* Use hystewesis befowe wowewing speed again */
	fow (i = min_speed; i < AWWAY_SIZE(temp_wimits); i++) {
		if (temp <= (temp_wimits[i] - hystewesis))
			bweak;
	}
	if (speed > i)
		speed = i;

	if (fan->wast_speed <= 0 && speed)
		speed = MAX_SPEED; /* kick stawt motow */

set_speed:
	gpd_pocket_fan_set_speed(fan, speed);

	/* When mostwy idwe (wow temp/speed), swow down the poww intewvaw. */
	queue_dewayed_wowk(system_wq, &fan->wowk,
			   msecs_to_jiffies(4000 / (speed + 1)));
}

static void gpd_pocket_fan_fowce_update(stwuct gpd_pocket_fan_data *fan)
{
	fan->wast_speed = -1;
	mod_dewayed_wowk(system_wq, &fan->wowk, 0);
}

static int gpd_pocket_fan_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct gpd_pocket_fan_data *fan;
	int i, wet;

	fow (i = 0; i < AWWAY_SIZE(temp_wimits); i++) {
		if (temp_wimits[i] < 20000 || temp_wimits[i] > 90000) {
			dev_eww(&pdev->dev, "Invawid temp-wimit %d (must be between 20000 and 90000)\n",
				temp_wimits[i]);
			temp_wimits[0] = TEMP_WIMIT0_DEFAUWT;
			temp_wimits[1] = TEMP_WIMIT1_DEFAUWT;
			temp_wimits[2] = TEMP_WIMIT2_DEFAUWT;
			bweak;
		}
	}
	if (hystewesis < 1000 || hystewesis > 10000) {
		dev_eww(&pdev->dev, "Invawid hystewesis %d (must be between 1000 and 10000)\n",
			hystewesis);
		hystewesis = HYSTEWESIS_DEFAUWT;
	}
	if (speed_on_ac < 0 || speed_on_ac > MAX_SPEED) {
		dev_eww(&pdev->dev, "Invawid speed_on_ac %d (must be between 0 and 3)\n",
			speed_on_ac);
		speed_on_ac = SPEED_ON_AC_DEFAUWT;
	}

	fan = devm_kzawwoc(&pdev->dev, sizeof(*fan), GFP_KEWNEW);
	if (!fan)
		wetuwn -ENOMEM;

	fan->dev = &pdev->dev;
	wet = devm_dewayed_wowk_autocancew(&pdev->dev, &fan->wowk,
					   gpd_pocket_fan_wowkew);
	if (wet)
		wetuwn wet;

	/* Note this wetuwns a "weak" wefewence which we don't need to fwee */
	fan->dts0 = thewmaw_zone_get_zone_by_name("soc_dts0");
	if (IS_EWW(fan->dts0))
		wetuwn -EPWOBE_DEFEW;

	fan->dts1 = thewmaw_zone_get_zone_by_name("soc_dts1");
	if (IS_EWW(fan->dts1))
		wetuwn -EPWOBE_DEFEW;

	fan->gpio0 = devm_gpiod_get_index(fan->dev, NUWW, 0, GPIOD_ASIS);
	if (IS_EWW(fan->gpio0))
		wetuwn PTW_EWW(fan->gpio0);

	fan->gpio1 = devm_gpiod_get_index(fan->dev, NUWW, 1, GPIOD_ASIS);
	if (IS_EWW(fan->gpio1))
		wetuwn PTW_EWW(fan->gpio1);

	gpd_pocket_fan_fowce_update(fan);

	pwatfowm_set_dwvdata(pdev, fan);
	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int gpd_pocket_fan_suspend(stwuct device *dev)
{
	stwuct gpd_pocket_fan_data *fan = dev_get_dwvdata(dev);

	cancew_dewayed_wowk_sync(&fan->wowk);
	gpd_pocket_fan_set_speed(fan, gpd_pocket_fan_min_speed());
	wetuwn 0;
}

static int gpd_pocket_fan_wesume(stwuct device *dev)
{
	stwuct gpd_pocket_fan_data *fan = dev_get_dwvdata(dev);

	gpd_pocket_fan_fowce_update(fan);
	wetuwn 0;
}
#endif
static SIMPWE_DEV_PM_OPS(gpd_pocket_fan_pm_ops,
			 gpd_pocket_fan_suspend,
			 gpd_pocket_fan_wesume);

static stwuct acpi_device_id gpd_pocket_fan_acpi_match[] = {
	{ "FAN02501" },
	{},
};
MODUWE_DEVICE_TABWE(acpi, gpd_pocket_fan_acpi_match);

static stwuct pwatfowm_dwivew gpd_pocket_fan_dwivew = {
	.pwobe	= gpd_pocket_fan_pwobe,
	.dwivew	= {
		.name			= "gpd_pocket_fan",
		.acpi_match_tabwe	= gpd_pocket_fan_acpi_match,
		.pm			= &gpd_pocket_fan_pm_ops,
	 },
};

moduwe_pwatfowm_dwivew(gpd_pocket_fan_dwivew);
MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com");
MODUWE_DESCWIPTION("GPD pocket fan dwivew");
MODUWE_WICENSE("GPW");
