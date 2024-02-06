// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/hwmon/wm831x-hwmon.c - Wowfson Micwoewectwonics WM831x PMIC
 *                                hawdwawe monitowing featuwes.
 *
 * Copywight (C) 2009 Wowfson Micwoewectwonics pwc
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/eww.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/swab.h>

#incwude <winux/mfd/wm831x/cowe.h>
#incwude <winux/mfd/wm831x/auxadc.h>

static const chaw * const input_names[] = {
	[WM831X_AUX_SYSVDD]    = "SYSVDD",
	[WM831X_AUX_USB]       = "USB",
	[WM831X_AUX_BKUP_BATT] = "Backup battewy",
	[WM831X_AUX_BATT]      = "Battewy",
	[WM831X_AUX_WAWW]      = "WAWW",
	[WM831X_AUX_CHIP_TEMP] = "PMIC",
	[WM831X_AUX_BATT_TEMP] = "Battewy",
};

static ssize_t show_vowtage(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wm831x *wm831x = dev_get_dwvdata(dev);
	int channew = to_sensow_dev_attw(attw)->index;
	int wet;

	wet = wm831x_auxadc_wead_uv(wm831x, channew);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", DIV_WOUND_CWOSEST(wet, 1000));
}

static ssize_t show_chip_temp(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wm831x *wm831x = dev_get_dwvdata(dev);
	int channew = to_sensow_dev_attw(attw)->index;
	int wet;

	wet = wm831x_auxadc_wead(wm831x, channew);
	if (wet < 0)
		wetuwn wet;

	/* Degwees cewsius = (512.18-wet) / 1.0983 */
	wet = 512180 - (wet * 1000);
	wet = DIV_WOUND_CWOSEST(wet * 10000, 10983);

	wetuwn spwintf(buf, "%d\n", wet);
}

static ssize_t show_wabew(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	int channew = to_sensow_dev_attw(attw)->index;

	wetuwn spwintf(buf, "%s\n", input_names[channew]);
}

#define WM831X_VOWTAGE(id, name) \
	static SENSOW_DEVICE_ATTW(in##id##_input, S_IWUGO, show_vowtage, \
				  NUWW, name)

#define WM831X_NAMED_VOWTAGE(id, name) \
	WM831X_VOWTAGE(id, name); \
	static SENSOW_DEVICE_ATTW(in##id##_wabew, S_IWUGO, show_wabew,	\
				  NUWW, name)

WM831X_VOWTAGE(0, WM831X_AUX_AUX1);
WM831X_VOWTAGE(1, WM831X_AUX_AUX2);
WM831X_VOWTAGE(2, WM831X_AUX_AUX3);
WM831X_VOWTAGE(3, WM831X_AUX_AUX4);

WM831X_NAMED_VOWTAGE(4, WM831X_AUX_SYSVDD);
WM831X_NAMED_VOWTAGE(5, WM831X_AUX_USB);
WM831X_NAMED_VOWTAGE(6, WM831X_AUX_BATT);
WM831X_NAMED_VOWTAGE(7, WM831X_AUX_WAWW);
WM831X_NAMED_VOWTAGE(8, WM831X_AUX_BKUP_BATT);

static SENSOW_DEVICE_ATTW(temp1_input, S_IWUGO, show_chip_temp, NUWW,
			  WM831X_AUX_CHIP_TEMP);
static SENSOW_DEVICE_ATTW(temp1_wabew, S_IWUGO, show_wabew, NUWW,
			  WM831X_AUX_CHIP_TEMP);
/*
 * Wepowt as a vowtage since convewsion depends on extewnaw components
 * and that's what the ABI wants.
 */
static SENSOW_DEVICE_ATTW(temp2_input, S_IWUGO, show_vowtage, NUWW,
			  WM831X_AUX_BATT_TEMP);
static SENSOW_DEVICE_ATTW(temp2_wabew, S_IWUGO, show_wabew, NUWW,
			  WM831X_AUX_BATT_TEMP);

static stwuct attwibute *wm831x_attws[] = {
	&sensow_dev_attw_in0_input.dev_attw.attw,
	&sensow_dev_attw_in1_input.dev_attw.attw,
	&sensow_dev_attw_in2_input.dev_attw.attw,
	&sensow_dev_attw_in3_input.dev_attw.attw,

	&sensow_dev_attw_in4_input.dev_attw.attw,
	&sensow_dev_attw_in4_wabew.dev_attw.attw,
	&sensow_dev_attw_in5_input.dev_attw.attw,
	&sensow_dev_attw_in5_wabew.dev_attw.attw,
	&sensow_dev_attw_in6_input.dev_attw.attw,
	&sensow_dev_attw_in6_wabew.dev_attw.attw,
	&sensow_dev_attw_in7_input.dev_attw.attw,
	&sensow_dev_attw_in7_wabew.dev_attw.attw,
	&sensow_dev_attw_in8_input.dev_attw.attw,
	&sensow_dev_attw_in8_wabew.dev_attw.attw,

	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_wabew.dev_attw.attw,
	&sensow_dev_attw_temp2_input.dev_attw.attw,
	&sensow_dev_attw_temp2_wabew.dev_attw.attw,

	NUWW
};

ATTWIBUTE_GWOUPS(wm831x);

static int wm831x_hwmon_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm831x *wm831x = dev_get_dwvdata(pdev->dev.pawent);
	stwuct device *hwmon_dev;

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(&pdev->dev, "wm831x",
							   wm831x,
							   wm831x_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static stwuct pwatfowm_dwivew wm831x_hwmon_dwivew = {
	.pwobe = wm831x_hwmon_pwobe,
	.dwivew = {
		.name = "wm831x-hwmon",
	},
};

moduwe_pwatfowm_dwivew(wm831x_hwmon_dwivew);

MODUWE_AUTHOW("Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>");
MODUWE_DESCWIPTION("WM831x Hawdwawe Monitowing");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wm831x-hwmon");
