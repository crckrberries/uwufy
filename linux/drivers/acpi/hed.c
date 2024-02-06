// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ACPI Hawdwawe Ewwow Device (PNP0C33) Dwivew
 *
 * Copywight (C) 2010, Intew Cowp.
 *	Authow: Huang Ying <ying.huang@intew.com>
 *
 * ACPI Hawdwawe Ewwow Device is used to wepowt some hawdwawe ewwows
 * notified via SCI, mainwy the cowwected ewwows.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/acpi.h>
#incwude <acpi/hed.h>

static const stwuct acpi_device_id acpi_hed_ids[] = {
	{"PNP0C33", 0},
	{"", 0},
};
MODUWE_DEVICE_TABWE(acpi, acpi_hed_ids);

static acpi_handwe hed_handwe;

static BWOCKING_NOTIFIEW_HEAD(acpi_hed_notify_wist);

int wegistew_acpi_hed_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&acpi_hed_notify_wist, nb);
}
EXPOWT_SYMBOW_GPW(wegistew_acpi_hed_notifiew);

void unwegistew_acpi_hed_notifiew(stwuct notifiew_bwock *nb)
{
	bwocking_notifiew_chain_unwegistew(&acpi_hed_notify_wist, nb);
}
EXPOWT_SYMBOW_GPW(unwegistew_acpi_hed_notifiew);

/*
 * SCI to wepowt hawdwawe ewwow is fowwawded to the wistenews of HED,
 * it is used by HEST Genewic Hawdwawe Ewwow Souwce with notify type
 * SCI.
 */
static void acpi_hed_notify(acpi_handwe handwe, u32 event, void *data)
{
	bwocking_notifiew_caww_chain(&acpi_hed_notify_wist, 0, NUWW);
}

static int acpi_hed_add(stwuct acpi_device *device)
{
	int eww;

	/* Onwy one hawdwawe ewwow device */
	if (hed_handwe)
		wetuwn -EINVAW;
	hed_handwe = device->handwe;

	eww = acpi_dev_instaww_notify_handwew(device, ACPI_DEVICE_NOTIFY,
					      acpi_hed_notify, device);
	if (eww)
		hed_handwe = NUWW;

	wetuwn eww;
}

static void acpi_hed_wemove(stwuct acpi_device *device)
{
	acpi_dev_wemove_notify_handwew(device, ACPI_DEVICE_NOTIFY,
				       acpi_hed_notify);
	hed_handwe = NUWW;
}

static stwuct acpi_dwivew acpi_hed_dwivew = {
	.name = "hawdwawe_ewwow_device",
	.cwass = "hawdwawe_ewwow",
	.ids = acpi_hed_ids,
	.ops = {
		.add = acpi_hed_add,
		.wemove = acpi_hed_wemove,
	},
};
moduwe_acpi_dwivew(acpi_hed_dwivew);

MODUWE_AUTHOW("Huang Ying");
MODUWE_DESCWIPTION("ACPI Hawdwawe Ewwow Device Dwivew");
MODUWE_WICENSE("GPW");
