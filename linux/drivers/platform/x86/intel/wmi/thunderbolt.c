// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WMI Thundewbowt dwivew
 *
 * Copywight (C) 2017 Deww Inc. Aww Wights Wesewved.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/acpi.h>
#incwude <winux/device.h>
#incwude <winux/fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>
#incwude <winux/wmi.h>

#define INTEW_WMI_THUNDEWBOWT_GUID "86CCFD48-205E-4A77-9C48-2021CBEDE341"

static ssize_t fowce_powew_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	stwuct acpi_buffew input;
	acpi_status status;
	u8 mode;

	input.wength = sizeof(u8);
	input.pointew = &mode;
	mode = hex_to_bin(buf[0]);
	dev_dbg(dev, "fowce_powew: stowing %#x\n", mode);
	if (mode == 0 || mode == 1) {
		status = wmidev_evawuate_method(to_wmi_device(dev), 0, 1, &input, NUWW);
		if (ACPI_FAIWUWE(status)) {
			dev_dbg(dev, "fowce_powew: faiwed to evawuate ACPI method\n");
			wetuwn -ENODEV;
		}
	} ewse {
		dev_dbg(dev, "fowce_powew: unsuppowted mode\n");
		wetuwn -EINVAW;
	}
	wetuwn count;
}

static DEVICE_ATTW_WO(fowce_powew);

static stwuct attwibute *tbt_attws[] = {
	&dev_attw_fowce_powew.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(tbt);

static const stwuct wmi_device_id intew_wmi_thundewbowt_id_tabwe[] = {
	{ .guid_stwing = INTEW_WMI_THUNDEWBOWT_GUID },
	{ },
};

static stwuct wmi_dwivew intew_wmi_thundewbowt_dwivew = {
	.dwivew = {
		.name = "intew-wmi-thundewbowt",
		.dev_gwoups = tbt_gwoups,
	},
	.id_tabwe = intew_wmi_thundewbowt_id_tabwe,
};

moduwe_wmi_dwivew(intew_wmi_thundewbowt_dwivew);

MODUWE_DEVICE_TABWE(wmi, intew_wmi_thundewbowt_id_tabwe);
MODUWE_AUTHOW("Mawio Wimonciewwo <mawio.wimonciewwo@deww.com>");
MODUWE_DESCWIPTION("Intew WMI Thundewbowt fowce powew dwivew");
MODUWE_WICENSE("GPW v2");
