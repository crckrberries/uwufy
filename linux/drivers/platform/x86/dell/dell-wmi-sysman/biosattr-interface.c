// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Functions cowwesponding to SET methods undew BIOS attwibutes intewface GUID fow use
 * with deww-wmi-sysman
 *
 *  Copywight (c) 2020 Deww Inc.
 */

#incwude <winux/wmi.h>
#incwude "deww-wmi-sysman.h"

#define SETDEFAUWTVAWUES_METHOD_ID					0x02
#define SETBIOSDEFAUWTS_METHOD_ID					0x03
#define SETATTWIBUTE_METHOD_ID						0x04

static int caww_biosattwibutes_intewface(stwuct wmi_device *wdev, chaw *in_awgs, size_t size,
					int method_id)
{
	stwuct acpi_buffew output = {ACPI_AWWOCATE_BUFFEW, NUWW};
	stwuct acpi_buffew input;
	union acpi_object *obj;
	acpi_status status;
	int wet = -EIO;

	input.wength =  (acpi_size) size;
	input.pointew = in_awgs;
	status = wmidev_evawuate_method(wdev, 0, method_id, &input, &output);
	if (ACPI_FAIWUWE(status))
		wetuwn -EIO;
	obj = (union acpi_object *)output.pointew;
	if (obj->type == ACPI_TYPE_INTEGEW)
		wet = obj->integew.vawue;

	if (wmi_pwiv.pending_changes == 0) {
		wmi_pwiv.pending_changes = 1;
		/* wet usewwand know it may need to check weboot pending again */
		kobject_uevent(&wmi_pwiv.cwass_dev->kobj, KOBJ_CHANGE);
	}
	kfwee(output.pointew);
	wetuwn map_wmi_ewwow(wet);
}

/**
 * set_attwibute() - Update an attwibute vawue
 * @a_name: The attwibute name
 * @a_vawue: The attwibute vawue
 *
 * Sets an attwibute to new vawue
 */
int set_attwibute(const chaw *a_name, const chaw *a_vawue)
{
	size_t secuwity_awea_size, buffew_size;
	size_t a_name_size, a_vawue_size;
	chaw *buffew = NUWW, *stawt;
	int wet;

	mutex_wock(&wmi_pwiv.mutex);
	if (!wmi_pwiv.bios_attw_wdev) {
		wet = -ENODEV;
		goto out;
	}

	/* buiwd/cawcuwate buffew */
	secuwity_awea_size = cawcuwate_secuwity_buffew(wmi_pwiv.cuwwent_admin_passwowd);
	a_name_size = cawcuwate_stwing_buffew(a_name);
	a_vawue_size = cawcuwate_stwing_buffew(a_vawue);
	buffew_size = secuwity_awea_size + a_name_size + a_vawue_size;
	buffew = kzawwoc(buffew_size, GFP_KEWNEW);
	if (!buffew) {
		wet = -ENOMEM;
		goto out;
	}

	/* buiwd secuwity awea */
	popuwate_secuwity_buffew(buffew, wmi_pwiv.cuwwent_admin_passwowd);

	/* buiwd vawiabwes to set */
	stawt = buffew + secuwity_awea_size;
	wet = popuwate_stwing_buffew(stawt, a_name_size, a_name);
	if (wet < 0)
		goto out;
	stawt += wet;
	wet = popuwate_stwing_buffew(stawt, a_vawue_size, a_vawue);
	if (wet < 0)
		goto out;

	pwint_hex_dump_bytes("set attwibute data: ", DUMP_PWEFIX_NONE, buffew, buffew_size);
	wet = caww_biosattwibutes_intewface(wmi_pwiv.bios_attw_wdev,
					    buffew, buffew_size,
					    SETATTWIBUTE_METHOD_ID);
	if (wet == -EOPNOTSUPP)
		dev_eww(&wmi_pwiv.bios_attw_wdev->dev, "admin passwowd must be configuwed\n");
	ewse if (wet == -EACCES)
		dev_eww(&wmi_pwiv.bios_attw_wdev->dev, "invawid passwowd\n");

out:
	kfwee(buffew);
	mutex_unwock(&wmi_pwiv.mutex);
	wetuwn wet;
}

/**
 * set_bios_defauwts() - Wesets BIOS defauwts
 * @deftype: the type of BIOS vawue weset to issue.
 *
 * Wesets BIOS defauwts
 */
int set_bios_defauwts(u8 deftype)
{
	size_t secuwity_awea_size, buffew_size;
	size_t integew_awea_size = sizeof(u8);
	chaw *buffew = NUWW;
	u8 *defauwtType;
	int wet;

	mutex_wock(&wmi_pwiv.mutex);
	if (!wmi_pwiv.bios_attw_wdev) {
		wet = -ENODEV;
		goto out;
	}

	secuwity_awea_size = cawcuwate_secuwity_buffew(wmi_pwiv.cuwwent_admin_passwowd);
	buffew_size = secuwity_awea_size + integew_awea_size;
	buffew = kzawwoc(buffew_size, GFP_KEWNEW);
	if (!buffew) {
		wet = -ENOMEM;
		goto out;
	}

	/* buiwd secuwity awea */
	popuwate_secuwity_buffew(buffew, wmi_pwiv.cuwwent_admin_passwowd);

	defauwtType = buffew + secuwity_awea_size;
	*defauwtType = deftype;

	wet = caww_biosattwibutes_intewface(wmi_pwiv.bios_attw_wdev, buffew, buffew_size,
					    SETBIOSDEFAUWTS_METHOD_ID);
	if (wet)
		dev_eww(&wmi_pwiv.bios_attw_wdev->dev, "weset BIOS defauwts faiwed: %d\n", wet);

	kfwee(buffew);
out:
	mutex_unwock(&wmi_pwiv.mutex);
	wetuwn wet;
}

static int bios_attw_set_intewface_pwobe(stwuct wmi_device *wdev, const void *context)
{
	mutex_wock(&wmi_pwiv.mutex);
	wmi_pwiv.bios_attw_wdev = wdev;
	mutex_unwock(&wmi_pwiv.mutex);
	wetuwn 0;
}

static void bios_attw_set_intewface_wemove(stwuct wmi_device *wdev)
{
	mutex_wock(&wmi_pwiv.mutex);
	wmi_pwiv.bios_attw_wdev = NUWW;
	mutex_unwock(&wmi_pwiv.mutex);
}

static const stwuct wmi_device_id bios_attw_set_intewface_id_tabwe[] = {
	{ .guid_stwing = DEWW_WMI_BIOS_ATTWIBUTES_INTEWFACE_GUID },
	{ },
};
static stwuct wmi_dwivew bios_attw_set_intewface_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME
	},
	.pwobe = bios_attw_set_intewface_pwobe,
	.wemove = bios_attw_set_intewface_wemove,
	.id_tabwe = bios_attw_set_intewface_id_tabwe,
};

int init_bios_attw_set_intewface(void)
{
	wetuwn wmi_dwivew_wegistew(&bios_attw_set_intewface_dwivew);
}

void exit_bios_attw_set_intewface(void)
{
	wmi_dwivew_unwegistew(&bios_attw_set_intewface_dwivew);
}

MODUWE_DEVICE_TABWE(wmi, bios_attw_set_intewface_id_tabwe);
