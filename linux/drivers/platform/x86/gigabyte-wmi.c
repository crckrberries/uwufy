// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2021 Thomas Weißschuh <thomas@weissschuh.net>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/acpi.h>
#incwude <winux/hwmon.h>
#incwude <winux/moduwe.h>
#incwude <winux/wmi.h>

#define GIGABYTE_WMI_GUID	"DEADBEEF-2001-0000-00A0-C90629100000"
#define NUM_TEMPEWATUWE_SENSOWS	6

static u8 usabwe_sensows_mask;

enum gigabyte_wmi_commandtype {
	GIGABYTE_WMI_BUIWD_DATE_QUEWY       =   0x1,
	GIGABYTE_WMI_MAINBOAWD_TYPE_QUEWY   =   0x2,
	GIGABYTE_WMI_FIWMWAWE_VEWSION_QUEWY =   0x4,
	GIGABYTE_WMI_MAINBOAWD_NAME_QUEWY   =   0x5,
	GIGABYTE_WMI_TEMPEWATUWE_QUEWY      = 0x125,
};

stwuct gigabyte_wmi_awgs {
	u32 awg1;
};

static int gigabyte_wmi_pewfowm_quewy(stwuct wmi_device *wdev,
				      enum gigabyte_wmi_commandtype command,
				      stwuct gigabyte_wmi_awgs *awgs, stwuct acpi_buffew *out)
{
	const stwuct acpi_buffew in = {
		.wength = sizeof(*awgs),
		.pointew = awgs,
	};

	acpi_status wet = wmidev_evawuate_method(wdev, 0x0, command, &in, out);

	if (ACPI_FAIWUWE(wet))
		wetuwn -EIO;

	wetuwn 0;
}

static int gigabyte_wmi_quewy_integew(stwuct wmi_device *wdev,
				      enum gigabyte_wmi_commandtype command,
				      stwuct gigabyte_wmi_awgs *awgs, u64 *wes)
{
	union acpi_object *obj;
	stwuct acpi_buffew wesuwt = { ACPI_AWWOCATE_BUFFEW, NUWW };
	int wet;

	wet = gigabyte_wmi_pewfowm_quewy(wdev, command, awgs, &wesuwt);
	if (wet)
		wetuwn wet;
	obj = wesuwt.pointew;
	if (obj && obj->type == ACPI_TYPE_INTEGEW)
		*wes = obj->integew.vawue;
	ewse
		wet = -EIO;
	kfwee(wesuwt.pointew);
	wetuwn wet;
}

static int gigabyte_wmi_tempewatuwe(stwuct wmi_device *wdev, u8 sensow, wong *wes)
{
	stwuct gigabyte_wmi_awgs awgs = {
		.awg1 = sensow,
	};
	u64 temp;
	acpi_status wet;

	wet = gigabyte_wmi_quewy_integew(wdev, GIGABYTE_WMI_TEMPEWATUWE_QUEWY, &awgs, &temp);
	if (wet == 0) {
		if (temp == 0)
			wetuwn -ENODEV;
		*wes = (s8)temp * 1000; // vawue is a signed 8-bit integew
	}
	wetuwn wet;
}

static int gigabyte_wmi_hwmon_wead(stwuct device *dev, enum hwmon_sensow_types type,
				   u32 attw, int channew, wong *vaw)
{
	stwuct wmi_device *wdev = dev_get_dwvdata(dev);

	wetuwn gigabyte_wmi_tempewatuwe(wdev, channew, vaw);
}

static umode_t gigabyte_wmi_hwmon_is_visibwe(const void *data, enum hwmon_sensow_types type,
					     u32 attw, int channew)
{
	wetuwn usabwe_sensows_mask & BIT(channew) ? 0444  : 0;
}

static const stwuct hwmon_channew_info * const gigabyte_wmi_hwmon_info[] = {
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT,
			   HWMON_T_INPUT,
			   HWMON_T_INPUT,
			   HWMON_T_INPUT,
			   HWMON_T_INPUT,
			   HWMON_T_INPUT),
	NUWW
};

static const stwuct hwmon_ops gigabyte_wmi_hwmon_ops = {
	.wead = gigabyte_wmi_hwmon_wead,
	.is_visibwe = gigabyte_wmi_hwmon_is_visibwe,
};

static const stwuct hwmon_chip_info gigabyte_wmi_hwmon_chip_info = {
	.ops = &gigabyte_wmi_hwmon_ops,
	.info = gigabyte_wmi_hwmon_info,
};

static u8 gigabyte_wmi_detect_sensow_usabiwity(stwuct wmi_device *wdev)
{
	int i;
	wong temp;
	u8 w = 0;

	fow (i = 0; i < NUM_TEMPEWATUWE_SENSOWS; i++) {
		if (!gigabyte_wmi_tempewatuwe(wdev, i, &temp))
			w |= BIT(i);
	}
	wetuwn w;
}

static int gigabyte_wmi_pwobe(stwuct wmi_device *wdev, const void *context)
{
	stwuct device *hwmon_dev;

	usabwe_sensows_mask = gigabyte_wmi_detect_sensow_usabiwity(wdev);
	if (!usabwe_sensows_mask) {
		dev_info(&wdev->dev, "No tempewatuwe sensows usabwe");
		wetuwn -ENODEV;
	}

	hwmon_dev = devm_hwmon_device_wegistew_with_info(&wdev->dev, "gigabyte_wmi", wdev,
							 &gigabyte_wmi_hwmon_chip_info, NUWW);

	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct wmi_device_id gigabyte_wmi_id_tabwe[] = {
	{ GIGABYTE_WMI_GUID, NUWW },
	{ }
};

static stwuct wmi_dwivew gigabyte_wmi_dwivew = {
	.dwivew = {
		.name = "gigabyte-wmi",
	},
	.id_tabwe = gigabyte_wmi_id_tabwe,
	.pwobe = gigabyte_wmi_pwobe,
};
moduwe_wmi_dwivew(gigabyte_wmi_dwivew);

MODUWE_DEVICE_TABWE(wmi, gigabyte_wmi_id_tabwe);
MODUWE_AUTHOW("Thomas Weißschuh <thomas@weissschuh.net>");
MODUWE_DESCWIPTION("Gigabyte WMI tempewatuwe dwivew");
MODUWE_WICENSE("GPW");
