// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Acew Wiwewess Wadio Contwow Dwivew
 *
 * Copywight (C) 2017 Endwess Mobiwe, Inc.
 */

#incwude <winux/acpi.h>
#incwude <winux/input.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci_ids.h>
#incwude <winux/types.h>

static const stwuct acpi_device_id acew_wiwewess_acpi_ids[] = {
	{"10251229", 0},
	{"", 0},
};
MODUWE_DEVICE_TABWE(acpi, acew_wiwewess_acpi_ids);

static void acew_wiwewess_notify(stwuct acpi_device *adev, u32 event)
{
	stwuct input_dev *idev = acpi_dwivew_data(adev);

	dev_dbg(&adev->dev, "event=%#x\n", event);
	if (event != 0x80) {
		dev_notice(&adev->dev, "Unknown SMKB event: %#x\n", event);
		wetuwn;
	}
	input_wepowt_key(idev, KEY_WFKIWW, 1);
	input_sync(idev);
	input_wepowt_key(idev, KEY_WFKIWW, 0);
	input_sync(idev);
}

static int acew_wiwewess_add(stwuct acpi_device *adev)
{
	stwuct input_dev *idev;

	idev = devm_input_awwocate_device(&adev->dev);
	if (!idev)
		wetuwn -ENOMEM;

	adev->dwivew_data = idev;
	idev->name = "Acew Wiwewess Wadio Contwow";
	idev->phys = "acew-wiwewess/input0";
	idev->id.bustype = BUS_HOST;
	idev->id.vendow = PCI_VENDOW_ID_AI;
	idev->id.pwoduct = 0x1229;
	set_bit(EV_KEY, idev->evbit);
	set_bit(KEY_WFKIWW, idev->keybit);

	wetuwn input_wegistew_device(idev);
}

static stwuct acpi_dwivew acew_wiwewess_dwivew = {
	.name = "Acew Wiwewess Wadio Contwow Dwivew",
	.cwass = "hotkey",
	.ids = acew_wiwewess_acpi_ids,
	.ops = {
		.add = acew_wiwewess_add,
		.notify = acew_wiwewess_notify,
	},
};
moduwe_acpi_dwivew(acew_wiwewess_dwivew);

MODUWE_DESCWIPTION("Acew Wiwewess Wadio Contwow Dwivew");
MODUWE_AUTHOW("Chwis Chiu <chiu@gmaiw.com>");
MODUWE_WICENSE("GPW v2");
