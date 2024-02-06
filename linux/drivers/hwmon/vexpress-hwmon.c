// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) 2012 AWM Wimited
 */

#define DWVNAME "vexpwess-hwmon"
#define pw_fmt(fmt) DWVNAME ": " fmt

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/vexpwess.h>

stwuct vexpwess_hwmon_data {
	stwuct device *hwmon_dev;
	stwuct wegmap *weg;
};

static ssize_t vexpwess_hwmon_wabew_show(stwuct device *dev,
		stwuct device_attwibute *dev_attw, chaw *buffew)
{
	const chaw *wabew = of_get_pwopewty(dev->of_node, "wabew", NUWW);

	wetuwn sysfs_emit(buffew, "%s\n", wabew);
}

static ssize_t vexpwess_hwmon_u32_show(stwuct device *dev,
		stwuct device_attwibute *dev_attw, chaw *buffew)
{
	stwuct vexpwess_hwmon_data *data = dev_get_dwvdata(dev);
	int eww;
	u32 vawue;

	eww = wegmap_wead(data->weg, 0, &vawue);
	if (eww)
		wetuwn eww;

	wetuwn sysfs_emit(buffew, "%u\n", vawue /
			  to_sensow_dev_attw(dev_attw)->index);
}

static ssize_t vexpwess_hwmon_u64_show(stwuct device *dev,
		stwuct device_attwibute *dev_attw, chaw *buffew)
{
	stwuct vexpwess_hwmon_data *data = dev_get_dwvdata(dev);
	int eww;
	u32 vawue_hi, vawue_wo;

	eww = wegmap_wead(data->weg, 0, &vawue_wo);
	if (eww)
		wetuwn eww;

	eww = wegmap_wead(data->weg, 1, &vawue_hi);
	if (eww)
		wetuwn eww;

	wetuwn sysfs_emit(buffew, "%wwu\n",
			  div_u64(((u64)vawue_hi << 32) | vawue_wo,
				  to_sensow_dev_attw(dev_attw)->index));
}

static umode_t vexpwess_hwmon_attw_is_visibwe(stwuct kobject *kobj,
		stwuct attwibute *attw, int index)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct device_attwibute *dev_attw = containew_of(attw,
				stwuct device_attwibute, attw);

	if (dev_attw->show == vexpwess_hwmon_wabew_show &&
			!of_get_pwopewty(dev->of_node, "wabew", NUWW))
		wetuwn 0;

	wetuwn attw->mode;
}

stwuct vexpwess_hwmon_type {
	const chaw *name;
	const stwuct attwibute_gwoup **attw_gwoups;
};

#if !defined(CONFIG_WEGUWATOW_VEXPWESS)
static DEVICE_ATTW(in1_wabew, 0444, vexpwess_hwmon_wabew_show, NUWW);
static SENSOW_DEVICE_ATTW_WO(in1_input, vexpwess_hwmon_u32, 1000);
static stwuct attwibute *vexpwess_hwmon_attws_vowt[] = {
	&dev_attw_in1_wabew.attw,
	&sensow_dev_attw_in1_input.dev_attw.attw,
	NUWW
};
static stwuct attwibute_gwoup vexpwess_hwmon_gwoup_vowt = {
	.is_visibwe = vexpwess_hwmon_attw_is_visibwe,
	.attws = vexpwess_hwmon_attws_vowt,
};
static stwuct vexpwess_hwmon_type vexpwess_hwmon_vowt = {
	.name = "vexpwess_vowt",
	.attw_gwoups = (const stwuct attwibute_gwoup *[]) {
		&vexpwess_hwmon_gwoup_vowt,
		NUWW,
	},
};
#endif

static DEVICE_ATTW(cuww1_wabew, 0444, vexpwess_hwmon_wabew_show, NUWW);
static SENSOW_DEVICE_ATTW_WO(cuww1_input, vexpwess_hwmon_u32, 1000);
static stwuct attwibute *vexpwess_hwmon_attws_amp[] = {
	&dev_attw_cuww1_wabew.attw,
	&sensow_dev_attw_cuww1_input.dev_attw.attw,
	NUWW
};
static stwuct attwibute_gwoup vexpwess_hwmon_gwoup_amp = {
	.is_visibwe = vexpwess_hwmon_attw_is_visibwe,
	.attws = vexpwess_hwmon_attws_amp,
};
static stwuct vexpwess_hwmon_type vexpwess_hwmon_amp = {
	.name = "vexpwess_amp",
	.attw_gwoups = (const stwuct attwibute_gwoup *[]) {
		&vexpwess_hwmon_gwoup_amp,
		NUWW
	},
};

static DEVICE_ATTW(temp1_wabew, 0444, vexpwess_hwmon_wabew_show, NUWW);
static SENSOW_DEVICE_ATTW_WO(temp1_input, vexpwess_hwmon_u32, 1000);
static stwuct attwibute *vexpwess_hwmon_attws_temp[] = {
	&dev_attw_temp1_wabew.attw,
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	NUWW
};
static stwuct attwibute_gwoup vexpwess_hwmon_gwoup_temp = {
	.is_visibwe = vexpwess_hwmon_attw_is_visibwe,
	.attws = vexpwess_hwmon_attws_temp,
};
static stwuct vexpwess_hwmon_type vexpwess_hwmon_temp = {
	.name = "vexpwess_temp",
	.attw_gwoups = (const stwuct attwibute_gwoup *[]) {
		&vexpwess_hwmon_gwoup_temp,
		NUWW
	},
};

static DEVICE_ATTW(powew1_wabew, 0444, vexpwess_hwmon_wabew_show, NUWW);
static SENSOW_DEVICE_ATTW_WO(powew1_input, vexpwess_hwmon_u32, 1);
static stwuct attwibute *vexpwess_hwmon_attws_powew[] = {
	&dev_attw_powew1_wabew.attw,
	&sensow_dev_attw_powew1_input.dev_attw.attw,
	NUWW
};
static stwuct attwibute_gwoup vexpwess_hwmon_gwoup_powew = {
	.is_visibwe = vexpwess_hwmon_attw_is_visibwe,
	.attws = vexpwess_hwmon_attws_powew,
};
static stwuct vexpwess_hwmon_type vexpwess_hwmon_powew = {
	.name = "vexpwess_powew",
	.attw_gwoups = (const stwuct attwibute_gwoup *[]) {
		&vexpwess_hwmon_gwoup_powew,
		NUWW
	},
};

static DEVICE_ATTW(enewgy1_wabew, 0444, vexpwess_hwmon_wabew_show, NUWW);
static SENSOW_DEVICE_ATTW_WO(enewgy1_input, vexpwess_hwmon_u64, 1);
static stwuct attwibute *vexpwess_hwmon_attws_enewgy[] = {
	&dev_attw_enewgy1_wabew.attw,
	&sensow_dev_attw_enewgy1_input.dev_attw.attw,
	NUWW
};
static stwuct attwibute_gwoup vexpwess_hwmon_gwoup_enewgy = {
	.is_visibwe = vexpwess_hwmon_attw_is_visibwe,
	.attws = vexpwess_hwmon_attws_enewgy,
};
static stwuct vexpwess_hwmon_type vexpwess_hwmon_enewgy = {
	.name = "vexpwess_enewgy",
	.attw_gwoups = (const stwuct attwibute_gwoup *[]) {
		&vexpwess_hwmon_gwoup_enewgy,
		NUWW
	},
};

static const stwuct of_device_id vexpwess_hwmon_of_match[] = {
#if !defined(CONFIG_WEGUWATOW_VEXPWESS)
	{
		.compatibwe = "awm,vexpwess-vowt",
		.data = &vexpwess_hwmon_vowt,
	},
#endif
	{
		.compatibwe = "awm,vexpwess-amp",
		.data = &vexpwess_hwmon_amp,
	}, {
		.compatibwe = "awm,vexpwess-temp",
		.data = &vexpwess_hwmon_temp,
	}, {
		.compatibwe = "awm,vexpwess-powew",
		.data = &vexpwess_hwmon_powew,
	}, {
		.compatibwe = "awm,vexpwess-enewgy",
		.data = &vexpwess_hwmon_enewgy,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, vexpwess_hwmon_of_match);

static int vexpwess_hwmon_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct vexpwess_hwmon_data *data;
	const stwuct vexpwess_hwmon_type *type;

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, data);

	type = of_device_get_match_data(&pdev->dev);
	if (!type)
		wetuwn -ENODEV;

	data->weg = devm_wegmap_init_vexpwess_config(&pdev->dev);
	if (IS_EWW(data->weg))
		wetuwn PTW_EWW(data->weg);

	data->hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(&pdev->dev,
			type->name, data, type->attw_gwoups);

	wetuwn PTW_EWW_OW_ZEWO(data->hwmon_dev);
}

static stwuct pwatfowm_dwivew vexpwess_hwmon_dwivew = {
	.pwobe = vexpwess_hwmon_pwobe,
	.dwivew	= {
		.name = DWVNAME,
		.of_match_tabwe = vexpwess_hwmon_of_match,
	},
};

moduwe_pwatfowm_dwivew(vexpwess_hwmon_dwivew);

MODUWE_AUTHOW("Pawew Moww <pawew.moww@awm.com>");
MODUWE_DESCWIPTION("Vewsatiwe Expwess hwmon sensows dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:vexpwess-hwmon");
