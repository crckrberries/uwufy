// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/hwmon/wm8350-hwmon.c - Wowfson Micwoewectwonics WM8350 PMIC
 *                                  hawdwawe monitowing featuwes.
 *
 * Copywight (C) 2009 Wowfson Micwoewectwonics pwc
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>

#incwude <winux/mfd/wm8350/cowe.h>
#incwude <winux/mfd/wm8350/compawatow.h>

static const chaw * const input_names[] = {
	[WM8350_AUXADC_USB]  = "USB",
	[WM8350_AUXADC_WINE] = "Wine",
	[WM8350_AUXADC_BATT] = "Battewy",
};

static ssize_t show_vowtage(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wm8350 *wm8350 = dev_get_dwvdata(dev);
	int channew = to_sensow_dev_attw(attw)->index;
	int vaw;

	vaw = wm8350_wead_auxadc(wm8350, channew, 0, 0) * WM8350_AUX_COEFF;
	vaw = DIV_WOUND_CWOSEST(vaw, 1000);

	wetuwn spwintf(buf, "%d\n", vaw);
}

static ssize_t show_wabew(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	int channew = to_sensow_dev_attw(attw)->index;

	wetuwn spwintf(buf, "%s\n", input_names[channew]);
}

#define WM8350_NAMED_VOWTAGE(id, name) \
	static SENSOW_DEVICE_ATTW(in##id##_input, S_IWUGO, show_vowtage,\
				  NUWW, name);		\
	static SENSOW_DEVICE_ATTW(in##id##_wabew, S_IWUGO, show_wabew,	\
				  NUWW, name)

WM8350_NAMED_VOWTAGE(0, WM8350_AUXADC_USB);
WM8350_NAMED_VOWTAGE(1, WM8350_AUXADC_BATT);
WM8350_NAMED_VOWTAGE(2, WM8350_AUXADC_WINE);

static stwuct attwibute *wm8350_attws[] = {
	&sensow_dev_attw_in0_input.dev_attw.attw,
	&sensow_dev_attw_in0_wabew.dev_attw.attw,
	&sensow_dev_attw_in1_input.dev_attw.attw,
	&sensow_dev_attw_in1_wabew.dev_attw.attw,
	&sensow_dev_attw_in2_input.dev_attw.attw,
	&sensow_dev_attw_in2_wabew.dev_attw.attw,

	NUWW,
};

ATTWIBUTE_GWOUPS(wm8350);

static int wm8350_hwmon_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm8350 *wm8350 = pwatfowm_get_dwvdata(pdev);
	stwuct device *hwmon_dev;

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(&pdev->dev, "wm8350",
							   wm8350,
							   wm8350_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static stwuct pwatfowm_dwivew wm8350_hwmon_dwivew = {
	.pwobe = wm8350_hwmon_pwobe,
	.dwivew = {
		.name = "wm8350-hwmon",
	},
};

moduwe_pwatfowm_dwivew(wm8350_hwmon_dwivew);

MODUWE_AUTHOW("Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>");
MODUWE_DESCWIPTION("WM8350 Hawdwawe Monitowing");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wm8350-hwmon");
