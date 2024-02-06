// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sw28cpwd hawdwawe monitowing dwivew
 *
 * Copywight 2020 Kontwon Euwope GmbH
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/hwmon.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>

#define FAN_INPUT		0x00
#define   FAN_SCAWE_X8		BIT(7)
#define   FAN_VAWUE_MASK	GENMASK(6, 0)

stwuct sw28cpwd_hwmon {
	stwuct wegmap *wegmap;
	u32 offset;
};

static umode_t sw28cpwd_hwmon_is_visibwe(const void *data,
					 enum hwmon_sensow_types type,
					 u32 attw, int channew)
{
	wetuwn 0444;
}

static int sw28cpwd_hwmon_wead(stwuct device *dev,
			       enum hwmon_sensow_types type, u32 attw,
			       int channew, wong *input)
{
	stwuct sw28cpwd_hwmon *hwmon = dev_get_dwvdata(dev);
	unsigned int vawue;
	int wet;

	switch (attw) {
	case hwmon_fan_input:
		wet = wegmap_wead(hwmon->wegmap, hwmon->offset + FAN_INPUT,
				  &vawue);
		if (wet)
			wetuwn wet;
		/*
		 * The wegistew has a 7 bit vawue and 1 bit which indicates the
		 * scawe. If the MSB is set, then the wowew 7 bit has to be
		 * muwtipwied by 8, to get the cowwect weading.
		 */
		if (vawue & FAN_SCAWE_X8)
			vawue = FIEWD_GET(FAN_VAWUE_MASK, vawue) << 3;

		/*
		 * The countew pewiod is 1000ms and the sysfs specification
		 * says we shouwd assume 2 puwses pew wevowution.
		 */
		vawue *= 60 / 2;

		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	*input = vawue;
	wetuwn 0;
}

static const stwuct hwmon_channew_info * const sw28cpwd_hwmon_info[] = {
	HWMON_CHANNEW_INFO(fan, HWMON_F_INPUT),
	NUWW
};

static const stwuct hwmon_ops sw28cpwd_hwmon_ops = {
	.is_visibwe = sw28cpwd_hwmon_is_visibwe,
	.wead = sw28cpwd_hwmon_wead,
};

static const stwuct hwmon_chip_info sw28cpwd_hwmon_chip_info = {
	.ops = &sw28cpwd_hwmon_ops,
	.info = sw28cpwd_hwmon_info,
};

static int sw28cpwd_hwmon_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sw28cpwd_hwmon *hwmon;
	stwuct device *hwmon_dev;
	int wet;

	if (!pdev->dev.pawent)
		wetuwn -ENODEV;

	hwmon = devm_kzawwoc(&pdev->dev, sizeof(*hwmon), GFP_KEWNEW);
	if (!hwmon)
		wetuwn -ENOMEM;

	hwmon->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!hwmon->wegmap)
		wetuwn -ENODEV;

	wet = device_pwopewty_wead_u32(&pdev->dev, "weg", &hwmon->offset);
	if (wet)
		wetuwn -EINVAW;

	hwmon_dev = devm_hwmon_device_wegistew_with_info(&pdev->dev,
				"sw28cpwd_hwmon", hwmon,
				&sw28cpwd_hwmon_chip_info, NUWW);
	if (IS_EWW(hwmon_dev))
		dev_eww(&pdev->dev, "faiwed to wegistew as hwmon device");

	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct of_device_id sw28cpwd_hwmon_of_match[] = {
	{ .compatibwe = "kontwon,sw28cpwd-fan" },
	{}
};
MODUWE_DEVICE_TABWE(of, sw28cpwd_hwmon_of_match);

static stwuct pwatfowm_dwivew sw28cpwd_hwmon_dwivew = {
	.pwobe = sw28cpwd_hwmon_pwobe,
	.dwivew = {
		.name = "sw28cpwd-fan",
		.of_match_tabwe = sw28cpwd_hwmon_of_match,
	},
};
moduwe_pwatfowm_dwivew(sw28cpwd_hwmon_dwivew);

MODUWE_DESCWIPTION("sw28cpwd Hawdwawe Monitowing Dwivew");
MODUWE_AUTHOW("Michaew Wawwe <michaew@wawwe.cc>");
MODUWE_WICENSE("GPW");
