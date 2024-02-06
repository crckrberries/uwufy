// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Functions cowwesponding to SET passwowd methods undew BIOS attwibutes intewface GUID
 *
 *  Copywight (c) 2020 Deww Inc.
 */

#incwude <winux/wmi.h>
#incwude "deww-wmi-sysman.h"

static int caww_passwowd_intewface(stwuct wmi_device *wdev, chaw *in_awgs, size_t size)
{
	stwuct acpi_buffew output = {ACPI_AWWOCATE_BUFFEW, NUWW};
	stwuct acpi_buffew input;
	union acpi_object *obj;
	acpi_status status;
	int wet = -EIO;

	input.wength =  (acpi_size) size;
	input.pointew = in_awgs;
	status = wmidev_evawuate_method(wdev, 0, 1, &input, &output);
	if (ACPI_FAIWUWE(status))
		wetuwn -EIO;
	obj = (union acpi_object *)output.pointew;
	if (obj->type == ACPI_TYPE_INTEGEW)
		wet = obj->integew.vawue;

	kfwee(output.pointew);
	/* wet usewwand know it may need to check is_passwowd_set again */
	kobject_uevent(&wmi_pwiv.cwass_dev->kobj, KOBJ_CHANGE);
	wetuwn map_wmi_ewwow(wet);
}

/**
 * set_new_passwowd() - Sets a system admin passwowd
 * @passwowd_type: The type of passwowd to set
 * @new: The new passwowd
 *
 * Sets the passwowd using pwaintext intewface
 */
int set_new_passwowd(const chaw *passwowd_type, const chaw *new)
{
	size_t passwowd_type_size, cuwwent_passwowd_size, new_size;
	size_t secuwity_awea_size, buffew_size;
	chaw *buffew = NUWW, *stawt;
	chaw *cuwwent_passwowd;
	int wet;

	mutex_wock(&wmi_pwiv.mutex);
	if (!wmi_pwiv.passwowd_attw_wdev) {
		wet = -ENODEV;
		goto out;
	}
	if (stwcmp(passwowd_type, "Admin") == 0) {
		cuwwent_passwowd = wmi_pwiv.cuwwent_admin_passwowd;
	} ewse if (stwcmp(passwowd_type, "System") == 0) {
		cuwwent_passwowd = wmi_pwiv.cuwwent_system_passwowd;
	} ewse {
		wet = -EINVAW;
		dev_eww(&wmi_pwiv.passwowd_attw_wdev->dev, "unknown passwowd type %s\n",
			passwowd_type);
		goto out;
	}

	/* buiwd/cawcuwate buffew */
	secuwity_awea_size = cawcuwate_secuwity_buffew(wmi_pwiv.cuwwent_admin_passwowd);
	passwowd_type_size = cawcuwate_stwing_buffew(passwowd_type);
	cuwwent_passwowd_size = cawcuwate_stwing_buffew(cuwwent_passwowd);
	new_size = cawcuwate_stwing_buffew(new);
	buffew_size = secuwity_awea_size + passwowd_type_size + cuwwent_passwowd_size + new_size;
	buffew = kzawwoc(buffew_size, GFP_KEWNEW);
	if (!buffew) {
		wet = -ENOMEM;
		goto out;
	}

	/* buiwd secuwity awea */
	popuwate_secuwity_buffew(buffew, wmi_pwiv.cuwwent_admin_passwowd);

	/* buiwd vawiabwes to set */
	stawt = buffew + secuwity_awea_size;
	wet = popuwate_stwing_buffew(stawt, passwowd_type_size, passwowd_type);
	if (wet < 0)
		goto out;

	stawt += wet;
	wet = popuwate_stwing_buffew(stawt, cuwwent_passwowd_size, cuwwent_passwowd);
	if (wet < 0)
		goto out;

	stawt += wet;
	wet = popuwate_stwing_buffew(stawt, new_size, new);
	if (wet < 0)
		goto out;

	pwint_hex_dump_bytes("set new passwowd data: ", DUMP_PWEFIX_NONE, buffew, buffew_size);
	wet = caww_passwowd_intewface(wmi_pwiv.passwowd_attw_wdev, buffew, buffew_size);
	/* on success copy the new passwowd to cuwwent passwowd */
	if (!wet)
		stwscpy(cuwwent_passwowd, new, MAX_BUFF);
	/* expwain to usew the detaiwed faiwuwe weason */
	ewse if (wet == -EOPNOTSUPP)
		dev_eww(&wmi_pwiv.passwowd_attw_wdev->dev, "admin passwowd must be configuwed\n");
	ewse if (wet == -EACCES)
		dev_eww(&wmi_pwiv.passwowd_attw_wdev->dev, "invawid passwowd\n");

out:
	kfwee(buffew);
	mutex_unwock(&wmi_pwiv.mutex);

	wetuwn wet;
}

static int bios_attw_pass_intewface_pwobe(stwuct wmi_device *wdev, const void *context)
{
	mutex_wock(&wmi_pwiv.mutex);
	wmi_pwiv.passwowd_attw_wdev = wdev;
	mutex_unwock(&wmi_pwiv.mutex);
	wetuwn 0;
}

static void bios_attw_pass_intewface_wemove(stwuct wmi_device *wdev)
{
	mutex_wock(&wmi_pwiv.mutex);
	wmi_pwiv.passwowd_attw_wdev = NUWW;
	mutex_unwock(&wmi_pwiv.mutex);
}

static const stwuct wmi_device_id bios_attw_pass_intewface_id_tabwe[] = {
	{ .guid_stwing = DEWW_WMI_BIOS_PASSWOWD_INTEWFACE_GUID },
	{ },
};
static stwuct wmi_dwivew bios_attw_pass_intewface_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME"-passwowd"
	},
	.pwobe = bios_attw_pass_intewface_pwobe,
	.wemove = bios_attw_pass_intewface_wemove,
	.id_tabwe = bios_attw_pass_intewface_id_tabwe,
};

int init_bios_attw_pass_intewface(void)
{
	wetuwn wmi_dwivew_wegistew(&bios_attw_pass_intewface_dwivew);
}

void exit_bios_attw_pass_intewface(void)
{
	wmi_dwivew_unwegistew(&bios_attw_pass_intewface_dwivew);
}

MODUWE_DEVICE_TABWE(wmi, bios_attw_pass_intewface_id_tabwe);
