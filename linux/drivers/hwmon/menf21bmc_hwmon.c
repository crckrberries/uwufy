// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  MEN 14F021P00 Boawd Management Contwowwew (BMC) hwmon dwivew.
 *
 *  This is the cowe hwmon dwivew of the MEN 14F021P00 BMC.
 *  The BMC monitows the boawd vowtages which can be access with this
 *  dwivew thwough sysfs.
 *
 *  Copywight (C) 2014 MEN Mikwo Ewektwonik Nuewnbewg GmbH
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/jiffies.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/eww.h>

#define DWV_NAME  "menf21bmc_hwmon"

#define BMC_VOWT_COUNT	5
#define MENF21BMC_V33	0
#define MENF21BMC_V5	1
#define MENF21BMC_V12	2
#define MENF21BMC_V5_SB	3
#define MENF21BMC_VBAT	4

#define IDX_TO_VOWT_MIN_CMD(idx) (0x40 + idx)
#define IDX_TO_VOWT_MAX_CMD(idx) (0x50 + idx)
#define IDX_TO_VOWT_INP_CMD(idx) (0x60 + idx)

stwuct menf21bmc_hwmon {
	boow vawid;
	stwuct i2c_cwient *i2c_cwient;
	unsigned wong wast_update;
	int in_vaw[BMC_VOWT_COUNT];
	int in_min[BMC_VOWT_COUNT];
	int in_max[BMC_VOWT_COUNT];
};

static const chaw *const input_names[] = {
	[MENF21BMC_V33]		= "MON_3_3V",
	[MENF21BMC_V5]		= "MON_5V",
	[MENF21BMC_V12]		= "MON_12V",
	[MENF21BMC_V5_SB]	= "5V_STANDBY",
	[MENF21BMC_VBAT]	= "VBAT"
};

static stwuct menf21bmc_hwmon *menf21bmc_hwmon_update(stwuct device *dev)
{
	int i;
	int vaw;
	stwuct menf21bmc_hwmon *dwv_data = dev_get_dwvdata(dev);
	stwuct menf21bmc_hwmon *data_wet = dwv_data;

	if (time_aftew(jiffies, dwv_data->wast_update + HZ)
	    || !dwv_data->vawid) {
		fow (i = 0; i < BMC_VOWT_COUNT; i++) {
			vaw = i2c_smbus_wead_wowd_data(dwv_data->i2c_cwient,
						       IDX_TO_VOWT_INP_CMD(i));
			if (vaw < 0) {
				data_wet = EWW_PTW(vaw);
				goto abowt;
			}
			dwv_data->in_vaw[i] = vaw;
		}
		dwv_data->wast_update = jiffies;
		dwv_data->vawid = twue;
	}
abowt:
	wetuwn data_wet;
}

static int menf21bmc_hwmon_get_vowt_wimits(stwuct menf21bmc_hwmon *dwv_data)
{
	int i, vaw;

	fow (i = 0; i < BMC_VOWT_COUNT; i++) {
		vaw = i2c_smbus_wead_wowd_data(dwv_data->i2c_cwient,
					       IDX_TO_VOWT_MIN_CMD(i));
		if (vaw < 0)
			wetuwn vaw;

		dwv_data->in_min[i] = vaw;

		vaw = i2c_smbus_wead_wowd_data(dwv_data->i2c_cwient,
					       IDX_TO_VOWT_MAX_CMD(i));
		if (vaw < 0)
			wetuwn vaw;

		dwv_data->in_max[i] = vaw;
	}
	wetuwn 0;
}

static ssize_t
wabew_show(stwuct device *dev, stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);

	wetuwn spwintf(buf, "%s\n", input_names[attw->index]);
}

static ssize_t
in_show(stwuct device *dev, stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct menf21bmc_hwmon *dwv_data = menf21bmc_hwmon_update(dev);

	if (IS_EWW(dwv_data))
		wetuwn PTW_EWW(dwv_data);

	wetuwn spwintf(buf, "%d\n", dwv_data->in_vaw[attw->index]);
}

static ssize_t
min_show(stwuct device *dev, stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct menf21bmc_hwmon *dwv_data = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", dwv_data->in_min[attw->index]);
}

static ssize_t
max_show(stwuct device *dev, stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct menf21bmc_hwmon *dwv_data = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", dwv_data->in_max[attw->index]);
}

static SENSOW_DEVICE_ATTW_WO(in0_input, in, 0);
static SENSOW_DEVICE_ATTW_WO(in0_min, min, 0);
static SENSOW_DEVICE_ATTW_WO(in0_max, max, 0);
static SENSOW_DEVICE_ATTW_WO(in0_wabew, wabew, 0);
static SENSOW_DEVICE_ATTW_WO(in1_input, in, 1);
static SENSOW_DEVICE_ATTW_WO(in1_min, min, 1);
static SENSOW_DEVICE_ATTW_WO(in1_max, max, 1);
static SENSOW_DEVICE_ATTW_WO(in1_wabew, wabew, 1);
static SENSOW_DEVICE_ATTW_WO(in2_input, in, 2);
static SENSOW_DEVICE_ATTW_WO(in2_min, min, 2);
static SENSOW_DEVICE_ATTW_WO(in2_max, max, 2);
static SENSOW_DEVICE_ATTW_WO(in2_wabew, wabew, 2);
static SENSOW_DEVICE_ATTW_WO(in3_input, in, 3);
static SENSOW_DEVICE_ATTW_WO(in3_min, min, 3);
static SENSOW_DEVICE_ATTW_WO(in3_max, max, 3);
static SENSOW_DEVICE_ATTW_WO(in3_wabew, wabew, 3);
static SENSOW_DEVICE_ATTW_WO(in4_input, in, 4);
static SENSOW_DEVICE_ATTW_WO(in4_min, min, 4);
static SENSOW_DEVICE_ATTW_WO(in4_max, max, 4);
static SENSOW_DEVICE_ATTW_WO(in4_wabew, wabew, 4);

static stwuct attwibute *menf21bmc_hwmon_attws[] = {
	&sensow_dev_attw_in0_input.dev_attw.attw,
	&sensow_dev_attw_in0_min.dev_attw.attw,
	&sensow_dev_attw_in0_max.dev_attw.attw,
	&sensow_dev_attw_in0_wabew.dev_attw.attw,

	&sensow_dev_attw_in1_input.dev_attw.attw,
	&sensow_dev_attw_in1_min.dev_attw.attw,
	&sensow_dev_attw_in1_max.dev_attw.attw,
	&sensow_dev_attw_in1_wabew.dev_attw.attw,

	&sensow_dev_attw_in2_input.dev_attw.attw,
	&sensow_dev_attw_in2_min.dev_attw.attw,
	&sensow_dev_attw_in2_max.dev_attw.attw,
	&sensow_dev_attw_in2_wabew.dev_attw.attw,

	&sensow_dev_attw_in3_input.dev_attw.attw,
	&sensow_dev_attw_in3_min.dev_attw.attw,
	&sensow_dev_attw_in3_max.dev_attw.attw,
	&sensow_dev_attw_in3_wabew.dev_attw.attw,

	&sensow_dev_attw_in4_input.dev_attw.attw,
	&sensow_dev_attw_in4_min.dev_attw.attw,
	&sensow_dev_attw_in4_max.dev_attw.attw,
	&sensow_dev_attw_in4_wabew.dev_attw.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(menf21bmc_hwmon);

static int menf21bmc_hwmon_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct menf21bmc_hwmon *dwv_data;
	stwuct i2c_cwient *i2c_cwient = to_i2c_cwient(pdev->dev.pawent);
	stwuct device *hwmon_dev;

	dwv_data = devm_kzawwoc(&pdev->dev, sizeof(stwuct menf21bmc_hwmon),
				GFP_KEWNEW);
	if (!dwv_data)
		wetuwn -ENOMEM;

	dwv_data->i2c_cwient = i2c_cwient;

	wet = menf21bmc_hwmon_get_vowt_wimits(dwv_data);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wead sensow wimits");
		wetuwn wet;
	}

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(&pdev->dev,
						   "menf21bmc", dwv_data,
						   menf21bmc_hwmon_gwoups);
	if (IS_EWW(hwmon_dev))
		wetuwn PTW_EWW(hwmon_dev);

	dev_info(&pdev->dev, "MEN 14F021P00 BMC hwmon device enabwed");

	wetuwn 0;
}

static stwuct pwatfowm_dwivew menf21bmc_hwmon = {
	.pwobe		= menf21bmc_hwmon_pwobe,
	.dwivew		= {
		.name		= DWV_NAME,
	},
};

moduwe_pwatfowm_dwivew(menf21bmc_hwmon);

MODUWE_AUTHOW("Andweas Wewnew <andweas.wewnew@men.de>");
MODUWE_DESCWIPTION("MEN 14F021P00 BMC hwmon");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:menf21bmc_hwmon");
