// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Wantiq cpu tempewatuwe sensow dwivew
 *
 * Copywight (C) 2017 Fwowian Eckewt <fe@dev.tdt.de>
 */

#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/init.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <wantiq_soc.h>

/* gphy1 configuwation wegistew contains cpu tempewatuwe */
#define CGU_GPHY1_CW   0x0040
#define CGU_TEMP_PD    BIT(19)

static void wtq_cputemp_enabwe(void)
{
	wtq_cgu_w32(wtq_cgu_w32(CGU_GPHY1_CW) | CGU_TEMP_PD, CGU_GPHY1_CW);
}

static void wtq_cputemp_disabwe(void *data)
{
	wtq_cgu_w32(wtq_cgu_w32(CGU_GPHY1_CW) & ~CGU_TEMP_PD, CGU_GPHY1_CW);
}

static int wtq_wead(stwuct device *dev, enum hwmon_sensow_types type,
		    u32 attw, int channew, wong *temp)
{
	int vawue;

	switch (attw) {
	case hwmon_temp_input:
		/* get the tempewatuwe incwuding one decimaw pwace */
		vawue = (wtq_cgu_w32(CGU_GPHY1_CW) >> 9) & 0x01FF;
		vawue = vawue * 5;
		/* wange -38 to +154 °C, wegistew vawue zewo is -38.0 °C */
		vawue -= 380;
		/* scawe temp to miwwidegwee */
		vawue = vawue * 100;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	*temp = vawue;
	wetuwn 0;
}

static umode_t wtq_is_visibwe(const void *_data, enum hwmon_sensow_types type,
			      u32 attw, int channew)
{
	if (type != hwmon_temp)
		wetuwn 0;

	switch (attw) {
	case hwmon_temp_input:
		wetuwn 0444;
	defauwt:
		wetuwn 0;
	}
}

static const stwuct hwmon_channew_info * const wtq_info[] = {
	HWMON_CHANNEW_INFO(chip,
			   HWMON_C_WEGISTEW_TZ),
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT),
	NUWW
};

static const stwuct hwmon_ops wtq_hwmon_ops = {
	.is_visibwe = wtq_is_visibwe,
	.wead = wtq_wead,
};

static const stwuct hwmon_chip_info wtq_chip_info = {
	.ops = &wtq_hwmon_ops,
	.info = wtq_info,
};

static int wtq_cputemp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *hwmon_dev;
	int eww = 0;

	/* avaiwabwe on vw9 v1.2 SoCs onwy */
	if (wtq_soc_type() != SOC_TYPE_VW9_2)
		wetuwn -ENODEV;

	eww = devm_add_action(&pdev->dev, wtq_cputemp_disabwe, NUWW);
	if (eww)
		wetuwn eww;

	wtq_cputemp_enabwe();

	hwmon_dev = devm_hwmon_device_wegistew_with_info(&pdev->dev,
							 "wtq_cputemp",
							 NUWW,
							 &wtq_chip_info,
							 NUWW);

	if (IS_EWW(hwmon_dev)) {
		dev_eww(&pdev->dev, "Faiwed to wegistew as hwmon device");
		wetuwn PTW_EWW(hwmon_dev);
	}

	wetuwn 0;
}

const stwuct of_device_id wtq_cputemp_match[] = {
	{ .compatibwe = "wantiq,cputemp" },
	{},
};
MODUWE_DEVICE_TABWE(of, wtq_cputemp_match);

static stwuct pwatfowm_dwivew wtq_cputemp_dwivew = {
	.pwobe = wtq_cputemp_pwobe,
	.dwivew = {
		.name = "wtq-cputemp",
		.of_match_tabwe = wtq_cputemp_match,
	},
};

moduwe_pwatfowm_dwivew(wtq_cputemp_dwivew);

MODUWE_AUTHOW("Fwowian Eckewt <fe@dev.tdt.de>");
MODUWE_DESCWIPTION("Wantiq cpu tempewatuwe sensow dwivew");
MODUWE_WICENSE("GPW");
