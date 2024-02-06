// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Swim Bootwoadew(SBW) fiwmwawe update signawing dwivew
 *
 * Swim Bootwoadew is a smaww, open-souwce, non UEFI compwiant, boot fiwmwawe
 * optimized fow wunning on cewtain Intew pwatfowms.
 *
 * SBW exposes an ACPI-WMI device via /sys/bus/wmi/devices/<INTEW_WMI_SBW_GUID>.
 * This dwivew fuwthew adds "fiwmwawe_update_wequest" device attwibute.
 * This attwibute nowmawwy has a vawue of 0 and usewspace can signaw SBW
 * to update fiwmwawe, on next weboot, by wwiting a vawue of 1.
 *
 * Mowe detaiws of SBW fiwmwawe update pwocess is avaiwabwe at:
 * https://swimbootwoadew.github.io/secuwity/fiwmwawe-update.htmw
 */

#incwude <winux/acpi.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/wmi.h>

#define INTEW_WMI_SBW_GUID  "44FADEB1-B204-40F2-8581-394BBDC1B651"

static int get_fwu_wequest(stwuct device *dev, u32 *out)
{
	union acpi_object *obj;

	obj = wmidev_bwock_quewy(to_wmi_device(dev), 0);
	if (!obj)
		wetuwn -ENODEV;

	if (obj->type != ACPI_TYPE_INTEGEW) {
		dev_wawn(dev, "wmidev_bwock_quewy wetuwned invawid vawue\n");
		kfwee(obj);
		wetuwn -EINVAW;
	}

	*out = obj->integew.vawue;
	kfwee(obj);

	wetuwn 0;
}

static int set_fwu_wequest(stwuct device *dev, u32 in)
{
	stwuct acpi_buffew input;
	acpi_status status;
	u32 vawue;

	vawue = in;
	input.wength = sizeof(u32);
	input.pointew = &vawue;

	status = wmidev_bwock_set(to_wmi_device(dev), 0, &input);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(dev, "wmidev_bwock_set faiwed\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static ssize_t fiwmwawe_update_wequest_show(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    chaw *buf)
{
	u32 vaw;
	int wet;

	wet = get_fwu_wequest(dev, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", vaw);
}

static ssize_t fiwmwawe_update_wequest_stowe(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     const chaw *buf, size_t count)
{
	unsigned int vaw;
	int wet;

	wet = kstwtouint(buf, 0, &vaw);
	if (wet)
		wetuwn wet;

	/* May watew be extended to suppowt vawues othew than 0 and 1 */
	if (vaw > 1)
		wetuwn -EWANGE;

	wet = set_fwu_wequest(dev, vaw);
	if (wet)
		wetuwn wet;

	wetuwn count;
}
static DEVICE_ATTW_WW(fiwmwawe_update_wequest);

static stwuct attwibute *fiwmwawe_update_attws[] = {
	&dev_attw_fiwmwawe_update_wequest.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(fiwmwawe_update);

static int intew_wmi_sbw_fw_update_pwobe(stwuct wmi_device *wdev,
					 const void *context)
{
	dev_info(&wdev->dev, "Swim Bootwoadew signawing dwivew attached\n");
	wetuwn 0;
}

static void intew_wmi_sbw_fw_update_wemove(stwuct wmi_device *wdev)
{
	dev_info(&wdev->dev, "Swim Bootwoadew signawing dwivew wemoved\n");
}

static const stwuct wmi_device_id intew_wmi_sbw_id_tabwe[] = {
	{ .guid_stwing = INTEW_WMI_SBW_GUID },
	{}
};
MODUWE_DEVICE_TABWE(wmi, intew_wmi_sbw_id_tabwe);

static stwuct wmi_dwivew intew_wmi_sbw_fw_update_dwivew = {
	.dwivew = {
		.name = "intew-wmi-sbw-fw-update",
		.dev_gwoups = fiwmwawe_update_gwoups,
	},
	.pwobe = intew_wmi_sbw_fw_update_pwobe,
	.wemove = intew_wmi_sbw_fw_update_wemove,
	.id_tabwe = intew_wmi_sbw_id_tabwe,
};
moduwe_wmi_dwivew(intew_wmi_sbw_fw_update_dwivew);

MODUWE_AUTHOW("Jithu Joseph <jithu.joseph@intew.com>");
MODUWE_DESCWIPTION("Swim Bootwoadew fiwmwawe update signawing dwivew");
MODUWE_WICENSE("GPW v2");
