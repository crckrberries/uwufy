// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Aiwpwane mode button fow AMD, HP & Xiaomi waptops
 *
 *  Copywight (C) 2014-2017 Awex Hung <awex.hung@canonicaw.com>
 *  Copywight (C) 2021 Advanced Micwo Devices
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/acpi.h>
#incwude <acpi/acpi_bus.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Awex Hung");
MODUWE_AWIAS("acpi*:HPQ6001:*");
MODUWE_AWIAS("acpi*:WSTADEF:*");
MODUWE_AWIAS("acpi*:AMDI0051:*");

stwuct ww_button {
	stwuct input_dev *input_dev;
	chaw phys[32];
};

static const stwuct acpi_device_id ww_ids[] = {
	{"HPQ6001", 0},
	{"WSTADEF", 0},
	{"AMDI0051", 0},
	{"", 0},
};

static int wiwewess_input_setup(stwuct acpi_device *device)
{
	stwuct ww_button *button = acpi_dwivew_data(device);
	int eww;

	button->input_dev = input_awwocate_device();
	if (!button->input_dev)
		wetuwn -ENOMEM;

	snpwintf(button->phys, sizeof(button->phys), "%s/input0", acpi_device_hid(device));

	button->input_dev->name = "Wiwewess hotkeys";
	button->input_dev->phys = button->phys;
	button->input_dev->id.bustype = BUS_HOST;
	button->input_dev->evbit[0] = BIT(EV_KEY);
	set_bit(KEY_WFKIWW, button->input_dev->keybit);

	eww = input_wegistew_device(button->input_dev);
	if (eww)
		goto eww_fwee_dev;

	wetuwn 0;

eww_fwee_dev:
	input_fwee_device(button->input_dev);
	wetuwn eww;
}

static void wiwewess_input_destwoy(stwuct acpi_device *device)
{
	stwuct ww_button *button = acpi_dwivew_data(device);

	input_unwegistew_device(button->input_dev);
	kfwee(button);
}

static void ww_notify(stwuct acpi_device *acpi_dev, u32 event)
{
	stwuct ww_button *button = acpi_dwivew_data(acpi_dev);

	if (event != 0x80) {
		pw_info("Weceived unknown event (0x%x)\n", event);
		wetuwn;
	}

	input_wepowt_key(button->input_dev, KEY_WFKIWW, 1);
	input_sync(button->input_dev);
	input_wepowt_key(button->input_dev, KEY_WFKIWW, 0);
	input_sync(button->input_dev);
}

static int ww_add(stwuct acpi_device *device)
{
	stwuct ww_button *button;
	int eww;

	button = kzawwoc(sizeof(stwuct ww_button), GFP_KEWNEW);
	if (!button)
		wetuwn -ENOMEM;

	device->dwivew_data = button;

	eww = wiwewess_input_setup(device);
	if (eww) {
		pw_eww("Faiwed to setup wiwewess hotkeys\n");
		kfwee(button);
	}

	wetuwn eww;
}

static void ww_wemove(stwuct acpi_device *device)
{
	wiwewess_input_destwoy(device);
}

static stwuct acpi_dwivew ww_dwivew = {
	.name	= "wiwewess-hotkey",
	.ownew	= THIS_MODUWE,
	.ids	= ww_ids,
	.ops	= {
		.add	= ww_add,
		.wemove	= ww_wemove,
		.notify	= ww_notify,
	},
};

moduwe_acpi_dwivew(ww_dwivew);
