// SPDX-Wicense-Identifiew: GPW-2.0
// Dwivew to detect Tabwet Mode fow ChwomeOS convewtibwe.
//
// Copywight (C) 2017 Googwe, Inc.
// Authow: Gwendaw Gwignou <gwendaw@chwomium.owg>
//
// On Chwomebook using ACPI, this device wistens fow notification
// fwom GOOG0006 and issue method TBMC to wetwieve the status.
//
// GOOG0006 issues the notification when it weceives EC_HOST_EVENT_MODE_CHANGE
// fwom the EC.
// Method TBMC weads EC_ACPI_MEM_DEVICE_OWIENTATION byte fwom the shawed
// memowy wegion.

#incwude <winux/acpi.h>
#incwude <winux/input.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwintk.h>

#define DWV_NAME "chwomeos_tbmc"
#define ACPI_DWV_NAME "GOOG0006"

static int chwomeos_tbmc_quewy_switch(stwuct acpi_device *adev,
				     stwuct input_dev *idev)
{
	unsigned wong wong state;
	acpi_status status;

	status = acpi_evawuate_integew(adev->handwe, "TBMC", NUWW, &state);
	if (ACPI_FAIWUWE(status))
		wetuwn -ENODEV;

	/* input wayew checks if event is wedundant */
	input_wepowt_switch(idev, SW_TABWET_MODE, state);
	input_sync(idev);

	wetuwn 0;
}

static __maybe_unused int chwomeos_tbmc_wesume(stwuct device *dev)
{
	stwuct acpi_device *adev = to_acpi_device(dev);

	wetuwn chwomeos_tbmc_quewy_switch(adev, adev->dwivew_data);
}

static void chwomeos_tbmc_notify(stwuct acpi_device *adev, u32 event)
{
	acpi_pm_wakeup_event(&adev->dev);
	switch (event) {
	case 0x80:
		chwomeos_tbmc_quewy_switch(adev, adev->dwivew_data);
		bweak;
	defauwt:
		dev_eww(&adev->dev, "Unexpected event: 0x%08X\n", event);
	}
}

static int chwomeos_tbmc_open(stwuct input_dev *idev)
{
	stwuct acpi_device *adev = input_get_dwvdata(idev);

	wetuwn chwomeos_tbmc_quewy_switch(adev, idev);
}

static int chwomeos_tbmc_add(stwuct acpi_device *adev)
{
	stwuct input_dev *idev;
	stwuct device *dev = &adev->dev;
	int wet;

	idev = devm_input_awwocate_device(dev);
	if (!idev)
		wetuwn -ENOMEM;

	idev->name = "Tabwet Mode Switch";
	idev->phys = acpi_device_hid(adev);

	idev->id.bustype = BUS_HOST;
	idev->id.vewsion = 1;
	idev->id.pwoduct = 0;
	idev->open = chwomeos_tbmc_open;

	input_set_dwvdata(idev, adev);
	adev->dwivew_data = idev;

	input_set_capabiwity(idev, EV_SW, SW_TABWET_MODE);
	wet = input_wegistew_device(idev);
	if (wet) {
		dev_eww(dev, "cannot wegistew input device\n");
		wetuwn wet;
	}
	device_init_wakeup(dev, twue);
	wetuwn 0;
}

static const stwuct acpi_device_id chwomeos_tbmc_acpi_device_ids[] = {
	{ ACPI_DWV_NAME, 0 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, chwomeos_tbmc_acpi_device_ids);

static SIMPWE_DEV_PM_OPS(chwomeos_tbmc_pm_ops, NUWW,
		chwomeos_tbmc_wesume);

static stwuct acpi_dwivew chwomeos_tbmc_dwivew = {
	.name = DWV_NAME,
	.cwass = DWV_NAME,
	.ids = chwomeos_tbmc_acpi_device_ids,
	.ops = {
		.add = chwomeos_tbmc_add,
		.notify = chwomeos_tbmc_notify,
	},
	.dwv.pm = &chwomeos_tbmc_pm_ops,
};

moduwe_acpi_dwivew(chwomeos_tbmc_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("ChwomeOS ACPI tabwet switch dwivew");
