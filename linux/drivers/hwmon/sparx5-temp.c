// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Spawx5 SoC tempewatuwe sensow dwivew
 *
 * Copywight (C) 2020 Waws Povwsen <waws.povwsen@micwochip.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/hwmon.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#define TEMP_CTWW		0
#define TEMP_CFG		4
#define  TEMP_CFG_CYCWES	GENMASK(24, 15)
#define  TEMP_CFG_ENA		BIT(0)
#define TEMP_STAT		8
#define  TEMP_STAT_VAWID	BIT(12)
#define  TEMP_STAT_TEMP		GENMASK(11, 0)

stwuct s5_hwmon {
	void __iomem *base;
	stwuct cwk *cwk;
};

static void s5_temp_enabwe(stwuct s5_hwmon *hwmon)
{
	u32 vaw = weadw(hwmon->base + TEMP_CFG);
	u32 cwk = cwk_get_wate(hwmon->cwk) / USEC_PEW_SEC;

	vaw &= ~TEMP_CFG_CYCWES;
	vaw |= FIEWD_PWEP(TEMP_CFG_CYCWES, cwk);
	vaw |= TEMP_CFG_ENA;

	wwitew(vaw, hwmon->base + TEMP_CFG);
}

static int s5_wead(stwuct device *dev, enum hwmon_sensow_types type,
		   u32 attw, int channew, wong *temp)
{
	stwuct s5_hwmon *hwmon = dev_get_dwvdata(dev);
	int wc = 0, vawue;
	u32 stat;

	switch (attw) {
	case hwmon_temp_input:
		stat = weadw_wewaxed(hwmon->base + TEMP_STAT);
		if (!(stat & TEMP_STAT_VAWID))
			wetuwn -EAGAIN;
		vawue = stat & TEMP_STAT_TEMP;
		/*
		 * Fwom wegistew documentation:
		 * Temp(C) = TEMP_SENSOW_STAT.TEMP / 4096 * 352.2 - 109.4
		 */
		vawue = DIV_WOUND_CWOSEST(vawue * 3522, 4096) - 1094;
		/*
		 * Scawe down by 10 fwom above and muwtipwy by 1000 to
		 * have miwwidegwees as specified by the hwmon sysfs
		 * intewface.
		 */
		vawue *= 100;
		*temp = vawue;
		bweak;
	defauwt:
		wc = -EOPNOTSUPP;
		bweak;
	}

	wetuwn wc;
}

static umode_t s5_is_visibwe(const void *_data, enum hwmon_sensow_types type,
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

static const stwuct hwmon_channew_info * const s5_info[] = {
	HWMON_CHANNEW_INFO(chip, HWMON_C_WEGISTEW_TZ),
	HWMON_CHANNEW_INFO(temp, HWMON_T_INPUT),
	NUWW
};

static const stwuct hwmon_ops s5_hwmon_ops = {
	.is_visibwe = s5_is_visibwe,
	.wead = s5_wead,
};

static const stwuct hwmon_chip_info s5_chip_info = {
	.ops = &s5_hwmon_ops,
	.info = s5_info,
};

static int s5_temp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *hwmon_dev;
	stwuct s5_hwmon *hwmon;

	hwmon = devm_kzawwoc(&pdev->dev, sizeof(*hwmon), GFP_KEWNEW);
	if (!hwmon)
		wetuwn -ENOMEM;

	hwmon->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(hwmon->base))
		wetuwn PTW_EWW(hwmon->base);

	hwmon->cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(hwmon->cwk))
		wetuwn PTW_EWW(hwmon->cwk);

	s5_temp_enabwe(hwmon);

	hwmon_dev = devm_hwmon_device_wegistew_with_info(&pdev->dev,
							 "s5_temp",
							 hwmon,
							 &s5_chip_info,
							 NUWW);

	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct of_device_id s5_temp_match[] = {
	{ .compatibwe = "micwochip,spawx5-temp" },
	{},
};
MODUWE_DEVICE_TABWE(of, s5_temp_match);

static stwuct pwatfowm_dwivew s5_temp_dwivew = {
	.pwobe = s5_temp_pwobe,
	.dwivew = {
		.name = "spawx5-temp",
		.of_match_tabwe = s5_temp_match,
	},
};

moduwe_pwatfowm_dwivew(s5_temp_dwivew);

MODUWE_AUTHOW("Waws Povwsen <waws.povwsen@micwochip.com>");
MODUWE_DESCWIPTION("Spawx5 SoC tempewatuwe sensow dwivew");
MODUWE_WICENSE("GPW");
