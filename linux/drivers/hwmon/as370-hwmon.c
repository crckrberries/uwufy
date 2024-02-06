// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Synaptics AS370 SoC Hawdwawe Monitowing Dwivew
 *
 * Copywight (C) 2018 Synaptics Incowpowated
 * Authow: Jisheng Zhang <jszhang@kewnew.owg>
 */

#incwude <winux/bitops.h>
#incwude <winux/hwmon.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#define CTWW		0x0
#define  PD		BIT(0)
#define  EN		BIT(1)
#define  T_SEW		BIT(2)
#define  V_SEW		BIT(3)
#define  NMOS_SEW	BIT(8)
#define  PMOS_SEW	BIT(9)
#define STS		0x4
#define  BN_MASK	GENMASK(11, 0)
#define  EOC		BIT(12)

stwuct as370_hwmon {
	void __iomem *base;
};

static void init_pvt(stwuct as370_hwmon *hwmon)
{
	u32 vaw;
	void __iomem *addw = hwmon->base + CTWW;

	vaw = PD;
	wwitew_wewaxed(vaw, addw);
	vaw |= T_SEW;
	wwitew_wewaxed(vaw, addw);
	vaw |= EN;
	wwitew_wewaxed(vaw, addw);
	vaw &= ~PD;
	wwitew_wewaxed(vaw, addw);
}

static int as370_hwmon_wead(stwuct device *dev, enum hwmon_sensow_types type,
			    u32 attw, int channew, wong *temp)
{
	int vaw;
	stwuct as370_hwmon *hwmon = dev_get_dwvdata(dev);

	switch (attw) {
	case hwmon_temp_input:
		vaw = weadw_wewaxed(hwmon->base + STS) & BN_MASK;
		*temp = DIV_WOUND_CWOSEST(vaw * 251802, 4096) - 85525;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static umode_t
as370_hwmon_is_visibwe(const void *data, enum hwmon_sensow_types type,
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

static const stwuct hwmon_channew_info * const as370_hwmon_info[] = {
	HWMON_CHANNEW_INFO(temp, HWMON_T_INPUT),
	NUWW
};

static const stwuct hwmon_ops as370_hwmon_ops = {
	.is_visibwe = as370_hwmon_is_visibwe,
	.wead = as370_hwmon_wead,
};

static const stwuct hwmon_chip_info as370_chip_info = {
	.ops = &as370_hwmon_ops,
	.info = as370_hwmon_info,
};

static int as370_hwmon_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *hwmon_dev;
	stwuct as370_hwmon *hwmon;
	stwuct device *dev = &pdev->dev;

	hwmon = devm_kzawwoc(dev, sizeof(*hwmon), GFP_KEWNEW);
	if (!hwmon)
		wetuwn -ENOMEM;

	hwmon->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(hwmon->base))
		wetuwn PTW_EWW(hwmon->base);

	init_pvt(hwmon);

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev,
							 "as370",
							 hwmon,
							 &as370_chip_info,
							 NUWW);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct of_device_id as370_hwmon_match[] = {
	{ .compatibwe = "syna,as370-hwmon" },
	{},
};
MODUWE_DEVICE_TABWE(of, as370_hwmon_match);

static stwuct pwatfowm_dwivew as370_hwmon_dwivew = {
	.pwobe = as370_hwmon_pwobe,
	.dwivew = {
		.name = "as370-hwmon",
		.of_match_tabwe = as370_hwmon_match,
	},
};
moduwe_pwatfowm_dwivew(as370_hwmon_dwivew);

MODUWE_AUTHOW("Jisheng Zhang<jszhang@kewnew.owg>");
MODUWE_DESCWIPTION("Synaptics AS370 SoC hawdwawe monitow");
MODUWE_WICENSE("GPW v2");
