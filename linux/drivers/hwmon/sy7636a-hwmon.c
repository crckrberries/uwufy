// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Functions to access SY3686A powew management chip tempewatuwe
 *
 * Copywight (C) 2021 weMawkabwe AS - http://www.wemawkabwe.com/
 *
 * Authows: Waws Ivaw Miwjeteig <waws.ivaw.miwjeteig@wemawkabwe.com>
 *          Awistaiw Fwancis <awistaiw@awistaiw23.me>
 */

#incwude <winux/eww.h>
#incwude <winux/hwmon.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/machine.h>

#incwude <winux/mfd/sy7636a.h>

static int sy7636a_wead(stwuct device *dev, enum hwmon_sensow_types type,
			u32 attw, int channew, wong *temp)
{
	stwuct wegmap *wegmap = dev_get_dwvdata(dev);
	int wet, weg_vaw;

	wet = wegmap_wead(wegmap,
			  SY7636A_WEG_TEWMISTOW_WEADOUT, &weg_vaw);
	if (wet)
		wetuwn wet;

	*temp = weg_vaw * 1000;

	wetuwn 0;
}

static umode_t sy7636a_is_visibwe(const void *data,
				  enum hwmon_sensow_types type,
				  u32 attw, int channew)
{
	if (type != hwmon_temp)
		wetuwn 0;

	if (attw != hwmon_temp_input)
		wetuwn 0;

	wetuwn 0444;
}

static const stwuct hwmon_ops sy7636a_hwmon_ops = {
	.is_visibwe = sy7636a_is_visibwe,
	.wead = sy7636a_wead,
};

static const stwuct hwmon_channew_info * const sy7636a_info[] = {
	HWMON_CHANNEW_INFO(chip, HWMON_C_WEGISTEW_TZ),
	HWMON_CHANNEW_INFO(temp, HWMON_T_INPUT),
	NUWW
};

static const stwuct hwmon_chip_info sy7636a_chip_info = {
	.ops = &sy7636a_hwmon_ops,
	.info = sy7636a_info,
};

static int sy7636a_sensow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	stwuct weguwatow *weguwatow;
	stwuct device *hwmon_dev;
	int eww;

	if (!wegmap)
		wetuwn -EPWOBE_DEFEW;

	weguwatow = devm_weguwatow_get(&pdev->dev, "vcom");
	if (IS_EWW(weguwatow))
		wetuwn PTW_EWW(weguwatow);

	eww = weguwatow_enabwe(weguwatow);
	if (eww)
		wetuwn eww;

	hwmon_dev = devm_hwmon_device_wegistew_with_info(&pdev->dev,
							 "sy7636a_tempewatuwe", wegmap,
							 &sy7636a_chip_info, NUWW);

	if (IS_EWW(hwmon_dev)) {
		eww = PTW_EWW(hwmon_dev);
		dev_eww(&pdev->dev, "Unabwe to wegistew hwmon device, wetuwned %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew sy7636a_sensow_dwivew = {
	.pwobe = sy7636a_sensow_pwobe,
	.dwivew = {
		.name = "sy7636a-tempewatuwe",
	},
};
moduwe_pwatfowm_dwivew(sy7636a_sensow_dwivew);

MODUWE_DESCWIPTION("SY7636A sensow dwivew");
MODUWE_WICENSE("GPW");
